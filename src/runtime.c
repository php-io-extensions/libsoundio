#include "runtime.h"

#include <stdlib.h>
#include <string.h>

static zend_object_handlers libsoundio_handle_handlers;

static zend_object *libsoundio_create_object(zend_class_entry *ce)
{
	libsoundio_handle *intern = zend_object_alloc(sizeof(libsoundio_handle), ce);

	zend_object_std_init(&intern->std, ce);
	object_properties_init(&intern->std, ce);
	intern->std.handlers = ce->default_object_handlers;
	intern->ptr = NULL;

	return &intern->std;
}

static void libsoundio_free_object(zend_object *object)
{
	libsoundio_handle *intern = libsoundio_handle_from(object);

	if (intern->ptr != NULL) {
		zend_hash_index_del(&LIBSOUNDIO_G(boxes), (zend_ulong) (uintptr_t) intern->ptr);
		intern->ptr = NULL;
	}
	zend_object_std_dtor(object);
}

zend_object_handlers *libsoundio_handlers(void)
{
	return &libsoundio_handle_handlers;
}

void libsoundio_handle_setup(zend_class_entry *ce)
{
	static bool handlers_ready = false;

	if (!handlers_ready) {
		memcpy(&libsoundio_handle_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
		libsoundio_handle_handlers.offset = XtOffsetOf(libsoundio_handle, std);
		libsoundio_handle_handlers.free_obj = libsoundio_free_object;
		libsoundio_handle_handlers.clone_obj = NULL;
		handlers_ready = true;
	}

	ce->create_object = libsoundio_create_object;
	ce->default_object_handlers = &libsoundio_handle_handlers;
	ce->ce_flags |= ZEND_ACC_NOT_SERIALIZABLE;
}

void libsoundio_box(zval *rv, void *ptr, zend_class_entry *ce)
{
	zend_object *existing;

	if (ptr == NULL) {
		ZVAL_NULL(rv);
		return;
	}

	existing = zend_hash_index_find_ptr(&LIBSOUNDIO_G(boxes), (zend_ulong) (uintptr_t) ptr);
	if (existing != NULL && instanceof_function(existing->ce, ce)) {
		ZVAL_OBJ_COPY(rv, existing);
		return;
	}
	if (existing != NULL) {
		/* Another class boxed this address. Detach it so its free_obj cannot drop the new entry. */
		libsoundio_handle_from(existing)->ptr = NULL;
	}

	object_init_ex(rv, ce);
	libsoundio_handle_from(Z_OBJ_P(rv))->ptr = ptr;
	zend_hash_index_update_ptr(&LIBSOUNDIO_G(boxes), (zend_ulong) (uintptr_t) ptr, Z_OBJ_P(rv));
}

void libsoundio_release(void *ptr)
{
	zend_object *existing = zend_hash_index_find_ptr(&LIBSOUNDIO_G(boxes), (zend_ulong) (uintptr_t) ptr);

	if (existing != NULL) {
		libsoundio_handle_from(existing)->ptr = NULL;
		zend_hash_index_del(&LIBSOUNDIO_G(boxes), (zend_ulong) (uintptr_t) ptr);
	}
}

const char *libsoundio_keep_string(const char **field, zend_string *str)
{
	zval kept;

	ZVAL_STR_COPY(&kept, str);
	zend_hash_index_update(&LIBSOUNDIO_G(keep), (zend_ulong) (uintptr_t) field, &kept);

	return ZSTR_VAL(str);
}

void libsoundio_keep_drop(const char **field)
{
	zend_hash_index_del(&LIBSOUNDIO_G(keep), (zend_ulong) (uintptr_t) field);
}

void *libsoundio_handle_arg(zval *zv, uint32_t arg_num)
{
	void *ptr = LIBSOUNDIO_PTR(zv);

	/* libsoundio dereferences every handle these functions are given; a released one is NULL. */
	if (!LIBSOUNDIO_PROBE_OFF("libsoundio-released-handle") && ptr == NULL) {
		zend_argument_value_error(arg_num, "%s has been released", ZSTR_VAL(Z_OBJCE_P(zv)->name)); /* binding:libsoundio-released-handle */
	}
	return ptr;
}

bool libsoundio_list_count(zend_long given, uint32_t length, uint32_t count_arg, uint32_t list_arg)
{
	/* libsoundio reads (and sorts in place) count elements of the C array built from the list. */
	if (!LIBSOUNDIO_PROBE_OFF("libsoundio-list-count") && (given < 0 || (zend_ulong) given > length)) {
		zend_argument_value_error(count_arg, "must be between 0 and the length of argument #%u ($%s)", list_arg, get_active_function_arg_name(list_arg)); /* binding:libsoundio-list-count */
		return false;
	}
	return true;
}

#ifdef LIBSOUNDIO_PROBES
bool libsoundio_probe_off(const char *id)
{
	const char *off = getenv("LIBSOUNDIO_PROBE_OFF");

	return off != NULL && strcmp(off, id) == 0;
}
#endif

static zval *libsoundio_prop(zend_object *obj, const char *name)
{
	return zend_read_property(obj->ce, obj, name, strlen(name), true, NULL);
}

bool libsoundio_layout_from(zend_object *obj, struct SoundIoChannelLayout *out)
{
	zval *name = libsoundio_prop(obj, "name");
	zval *channels = libsoundio_prop(obj, "channels");
	zval *channel;
	int i = 0;

	memset(out, 0, sizeof(*out));
	out->name = Z_TYPE_P(name) == IS_STRING ? Z_STRVAL_P(name) : NULL;
	out->channel_count = (int) Z_LVAL_P(libsoundio_prop(obj, "channel_count"));
	ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(channels), channel) {
		if (i == SOUNDIO_MAX_CHANNELS) {
			break;
		}
		if (Z_TYPE_P(channel) != IS_LONG) {
			zend_type_error("SoundIoChannelLayout::$channels must hold only int, %s given", zend_zval_value_name(channel));
			return false;
		}
		out->channels[i++] = (enum SoundIoChannelId) Z_LVAL_P(channel);
	} ZEND_HASH_FOREACH_END();

	return true;
}

void libsoundio_layout_to(const struct SoundIoChannelLayout *in, zval *rv)
{
	zval channels;
	int count = in->channel_count < SOUNDIO_MAX_CHANNELS ? in->channel_count : SOUNDIO_MAX_CHANNELS;

	object_init_ex(rv, libsoundio_ce_SoundIoChannelLayout);
	if (in->name != NULL) {
		zend_update_property_string(libsoundio_ce_SoundIoChannelLayout, Z_OBJ_P(rv), "name", sizeof("name") - 1, in->name);
	}
	zend_update_property_long(libsoundio_ce_SoundIoChannelLayout, Z_OBJ_P(rv), "channel_count", sizeof("channel_count") - 1, in->channel_count);
	array_init_size(&channels, (uint32_t) (count > 0 ? count : 0));
	for (int i = 0; i < count; i++) {
		add_next_index_long(&channels, in->channels[i]);
	}
	zend_update_property(libsoundio_ce_SoundIoChannelLayout, Z_OBJ_P(rv), "channels", sizeof("channels") - 1, &channels);
	zval_ptr_dtor(&channels);
}

struct SoundIoChannelLayout *libsoundio_layouts_from(HashTable *list, uint32_t arg)
{
	struct SoundIoChannelLayout *out = ecalloc(zend_hash_num_elements(list) + 1, sizeof(*out));
	zval *element;
	uint32_t i = 0;

	ZEND_HASH_FOREACH_VAL(list, element) {
		if (Z_TYPE_P(element) != IS_OBJECT || Z_OBJCE_P(element) != libsoundio_ce_SoundIoChannelLayout) {
			zend_argument_type_error(arg, "must be a list of SoundIoChannelLayout, %s given at index %u", zend_zval_value_name(element), i);
			efree(out);
			return NULL;
		}
		if (!libsoundio_layout_from(Z_OBJ_P(element), &out[i])) {
			efree(out);
			return NULL;
		}
		i++;
	} ZEND_HASH_FOREACH_END();

	return out;
}
