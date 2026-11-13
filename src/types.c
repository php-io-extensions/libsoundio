/*
 * The handle classes and the value structs: stubs/soundio_types.stub.php. A handle's declared
 * properties are its C struct's fields: reads come from the native struct, writes go to it after
 * PHP has type-checked them into the property slot.
 */
#include "runtime.h"
#include "../stubs/soundio_types_arginfo.h"

zend_class_entry *libsoundio_ce_SoundIo;
zend_class_entry *libsoundio_ce_SoundIoDevice;
zend_class_entry *libsoundio_ce_SoundIoOutStream;
zend_class_entry *libsoundio_ce_SoundIoInStream;
zend_class_entry *libsoundio_ce_SoundIoRingBuffer;
zend_class_entry *libsoundio_ce_SoundIoChannelLayout;
zend_class_entry *libsoundio_ce_SoundIoSampleRateRange;
zend_class_entry *libsoundio_ce_SoundIoChannelArea;

LIBSOUNDIO_POINTER_METHODS(SoundIo)
LIBSOUNDIO_POINTER_METHODS(SoundIoDevice)
LIBSOUNDIO_POINTER_METHODS(SoundIoOutStream)
LIBSOUNDIO_POINTER_METHODS(SoundIoInStream)
LIBSOUNDIO_POINTER_METHODS(SoundIoRingBuffer)

static zend_object_handlers libsoundio_soundio_handlers;
static zend_object_handlers libsoundio_device_handlers;
static zend_object_handlers libsoundio_outstream_handlers;
static zend_object_handlers libsoundio_instream_handlers;

#define FIELD(n) zend_string_equals_literal(name, n)
#define ADDRESS(p) ((zend_long) (uintptr_t) (p))

static void libsoundio_string_or_null(zval *rv, const char *s)
{
	if (s == NULL) {
		ZVAL_NULL(rv);
	} else {
		ZVAL_STRING(rv, s);
	}
}

/* Callouts: SoundIo.on_devices_change and .on_backend_disconnect. */

typedef struct {
	zval devices_change;             /* the Closure, UNDEF when none */
	zval backend_disconnect;         /* the Closure, UNDEF when none */
	void (*own_devices_change)(struct SoundIo *);          /* libsoundio's own, put back by libsoundio_callouts_drop */
	void (*own_backend_disconnect)(struct SoundIo *, int);
} libsoundio_callouts;

/* The context soundio_flush_events() / soundio_wait_events() is dispatching on this thread; NULL outside them. */
static _Thread_local struct SoundIo *libsoundio_dispatching = NULL;

void libsoundio_dispatch_begin(struct SoundIo *s)
{
	libsoundio_dispatching = s;
}

void libsoundio_dispatch_end(void)
{
	libsoundio_dispatching = NULL;
}

static libsoundio_callouts *libsoundio_callouts_for(struct SoundIo *s, bool create)
{
	libsoundio_callouts *c = zend_hash_index_find_ptr(&LIBSOUNDIO_G(callouts), (zend_ulong) (uintptr_t) s);

	if (c == NULL && create) {
		c = emalloc(sizeof(*c));
		ZVAL_UNDEF(&c->devices_change);
		ZVAL_UNDEF(&c->backend_disconnect);
		c->own_devices_change = s->on_devices_change;
		c->own_backend_disconnect = s->on_backend_disconnect;
		zend_hash_index_add_new_ptr(&LIBSOUNDIO_G(callouts), (zend_ulong) (uintptr_t) s, c);
	}
	return c;
}

/* Calls the callable with the SoundIo object and argc - 1 more ints; nothing while an exception is pending. */
static void libsoundio_callout_call(zval *callable, struct SoundIo *s, uint32_t argc, zend_long err)
{
	zval args[2], retval;

	if (Z_TYPE_P(callable) == IS_UNDEF || EG(exception)) {
		return;
	}
	libsoundio_box(&args[0], s, libsoundio_ce_SoundIo);
	ZVAL_LONG(&args[1], err);
	ZVAL_UNDEF(&retval);
	call_user_function(NULL, NULL, callable, &retval, argc, args);
	zval_ptr_dtor(&retval);
	zval_ptr_dtor(&args[0]);
}

static void libsoundio_on_devices_change(struct SoundIo *s)
{
	libsoundio_callouts *c;

	if (libsoundio_dispatching != s) {
		return;
	}
	c = libsoundio_callouts_for(s, false);
	if (c != NULL) {
		libsoundio_callout_call(&c->devices_change, s, 1, 0);
	}
}

static void libsoundio_on_backend_disconnect(struct SoundIo *s, int err)
{
	libsoundio_callouts *c;

	if (libsoundio_dispatching != s) {
		return;
	}
	c = libsoundio_callouts_for(s, false);
	if (c != NULL) {
		libsoundio_callout_call(&c->backend_disconnect, s, 2, err);
	}
}

static void libsoundio_callouts_free(struct SoundIo *s, libsoundio_callouts *c)
{
	s->on_devices_change = c->own_devices_change;
	s->on_backend_disconnect = c->own_backend_disconnect;
	zval_ptr_dtor(&c->devices_change);
	zval_ptr_dtor(&c->backend_disconnect);
	efree(c);
}

void libsoundio_callouts_drop(struct SoundIo *s)
{
	libsoundio_callouts *c = libsoundio_callouts_for(s, false);

	if (c != NULL) {
		zend_hash_index_del(&LIBSOUNDIO_G(callouts), (zend_ulong) (uintptr_t) s);
		libsoundio_callouts_free(s, c);
	}
}

void libsoundio_callouts_drop_all(void)
{
	zend_ulong key;
	libsoundio_callouts *c;

	ZEND_HASH_FOREACH_NUM_KEY_PTR(&LIBSOUNDIO_G(callouts), key, c) {
		libsoundio_callouts_free((struct SoundIo *) (uintptr_t) key, c);
	} ZEND_HASH_FOREACH_END();
	zend_hash_clean(&LIBSOUNDIO_G(callouts));
}

/* The callout's Closure into rv, null when none is set. */
static void libsoundio_callout_read(zval *slot, zval *rv)
{
	if (slot == NULL || Z_TYPE_P(slot) == IS_UNDEF) {
		ZVAL_NULL(rv);
	} else {
		ZVAL_COPY(rv, slot);
	}
}

/* Holds value (a Closure, or null to clear) for the callout; slot is the record's zval. */
static void libsoundio_callout_store(zval *slot, zval *value)
{
	zval_ptr_dtor(slot);
	if (Z_TYPE_P(value) == IS_NULL) {
		ZVAL_UNDEF(slot);
	} else {
		ZVAL_COPY(slot, value);
	}
}

/* struct SoundIo's field `name` into rv; false for a name that is not a field. */
static bool libsoundio_soundio_field(struct SoundIo *s, zend_string *name, zval *rv)
{
	if (FIELD("userdata")) {
		ZVAL_LONG(rv, ADDRESS(s->userdata));
	} else if (FIELD("on_devices_change")) {
		libsoundio_callouts *c = libsoundio_callouts_for(s, false);
		libsoundio_callout_read(c != NULL ? &c->devices_change : NULL, rv);
	} else if (FIELD("on_backend_disconnect")) {
		libsoundio_callouts *c = libsoundio_callouts_for(s, false);
		libsoundio_callout_read(c != NULL ? &c->backend_disconnect : NULL, rv);
	} else if (FIELD("on_events_signal")) {
		ZVAL_LONG(rv, ADDRESS(s->on_events_signal));
	} else if (FIELD("current_backend")) {
		ZVAL_LONG(rv, s->current_backend);
	} else if (FIELD("app_name")) {
		libsoundio_string_or_null(rv, s->app_name);
	} else if (FIELD("emit_rtprio_warning")) {
		ZVAL_LONG(rv, ADDRESS(s->emit_rtprio_warning));
	} else if (FIELD("jack_info_callback")) {
		ZVAL_LONG(rv, ADDRESS(s->jack_info_callback));
	} else if (FIELD("jack_error_callback")) {
		ZVAL_LONG(rv, ADDRESS(s->jack_error_callback));
	} else {
		return false;
	}
	return true;
}

/* Writes the type-checked value of a writable struct SoundIo field; false for any other name. */
static bool libsoundio_soundio_store(struct SoundIo *s, zend_string *name, zval *value)
{
	if (FIELD("userdata")) {
		s->userdata = (void *) (uintptr_t) Z_LVAL_P(value);
	} else if (FIELD("on_devices_change")) {
		libsoundio_callouts *c = libsoundio_callouts_for(s, true);
		libsoundio_callout_store(&c->devices_change, value);
		s->on_devices_change = Z_TYPE(c->devices_change) == IS_UNDEF ? c->own_devices_change : libsoundio_on_devices_change;
	} else if (FIELD("on_backend_disconnect")) {
		libsoundio_callouts *c = libsoundio_callouts_for(s, true);
		libsoundio_callout_store(&c->backend_disconnect, value);
		s->on_backend_disconnect = Z_TYPE(c->backend_disconnect) == IS_UNDEF ? c->own_backend_disconnect : libsoundio_on_backend_disconnect;
	} else if (FIELD("on_events_signal")) {
		s->on_events_signal = (void (*)(struct SoundIo *)) (uintptr_t) Z_LVAL_P(value);
	} else if (FIELD("app_name")) {
		if (Z_TYPE_P(value) == IS_STRING) {
			s->app_name = libsoundio_keep_string(&s->app_name, Z_STR_P(value));
		} else {
			s->app_name = NULL;
			libsoundio_keep_drop(&s->app_name);
		}
	} else if (FIELD("emit_rtprio_warning")) {
		s->emit_rtprio_warning = (void (*)(void)) (uintptr_t) Z_LVAL_P(value);
	} else if (FIELD("jack_info_callback")) {
		s->jack_info_callback = (void (*)(const char *)) (uintptr_t) Z_LVAL_P(value);
	} else if (FIELD("jack_error_callback")) {
		s->jack_error_callback = (void (*)(const char *)) (uintptr_t) Z_LVAL_P(value);
	} else {
		return false;
	}
	return true;
}

/* struct SoundIoDevice's field `name` into rv; false for a name that is not a field. */
static bool libsoundio_device_field(struct SoundIoDevice *d, zend_string *name, zval *rv)
{
	if (FIELD("soundio")) {
		libsoundio_box(rv, d->soundio, libsoundio_ce_SoundIo);
	} else if (FIELD("id")) {
		libsoundio_string_or_null(rv, d->id);
	} else if (FIELD("name")) {
		libsoundio_string_or_null(rv, d->name);
	} else if (FIELD("aim")) {
		ZVAL_LONG(rv, d->aim);
	} else if (FIELD("layouts")) {
		zval layout;
		array_init_size(rv, (uint32_t) d->layout_count);
		for (int i = 0; i < d->layout_count; i++) {
			libsoundio_layout_to(&d->layouts[i], &layout);
			add_next_index_zval(rv, &layout);
		}
	} else if (FIELD("layout_count")) {
		ZVAL_LONG(rv, d->layout_count);
	} else if (FIELD("current_layout")) {
		libsoundio_layout_to(&d->current_layout, rv);
	} else if (FIELD("formats")) {
		array_init_size(rv, (uint32_t) d->format_count);
		for (int i = 0; i < d->format_count; i++) {
			add_next_index_long(rv, d->formats[i]);
		}
	} else if (FIELD("format_count")) {
		ZVAL_LONG(rv, d->format_count);
	} else if (FIELD("current_format")) {
		ZVAL_LONG(rv, d->current_format);
	} else if (FIELD("sample_rates")) {
		zval range;
		array_init_size(rv, (uint32_t) d->sample_rate_count);
		for (int i = 0; i < d->sample_rate_count; i++) {
			object_init_ex(&range, libsoundio_ce_SoundIoSampleRateRange);
			zend_update_property_long(libsoundio_ce_SoundIoSampleRateRange, Z_OBJ(range), "min", sizeof("min") - 1, d->sample_rates[i].min);
			zend_update_property_long(libsoundio_ce_SoundIoSampleRateRange, Z_OBJ(range), "max", sizeof("max") - 1, d->sample_rates[i].max);
			add_next_index_zval(rv, &range);
		}
	} else if (FIELD("sample_rate_count")) {
		ZVAL_LONG(rv, d->sample_rate_count);
	} else if (FIELD("sample_rate_current")) {
		ZVAL_LONG(rv, d->sample_rate_current);
	} else if (FIELD("software_latency_min")) {
		ZVAL_DOUBLE(rv, d->software_latency_min);
	} else if (FIELD("software_latency_max")) {
		ZVAL_DOUBLE(rv, d->software_latency_max);
	} else if (FIELD("software_latency_current")) {
		ZVAL_DOUBLE(rv, d->software_latency_current);
	} else if (FIELD("is_raw")) {
		ZVAL_BOOL(rv, d->is_raw);
	} else if (FIELD("ref_count")) {
		ZVAL_LONG(rv, d->ref_count);
	} else if (FIELD("probe_error")) {
		ZVAL_LONG(rv, d->probe_error);
	} else {
		return false;
	}
	return true;
}

static zval *libsoundio_soundio_read(zend_object *obj, zend_string *name, int type, void **cache_slot, zval *rv)
{
	struct SoundIo *s = libsoundio_handle_from(obj)->ptr;

	if (s != NULL && libsoundio_soundio_field(s, name, rv)) {
		return rv;
	}
	return zend_std_read_property(obj, name, type, cache_slot, rv);
}

static zval *libsoundio_soundio_write(zend_object *obj, zend_string *name, zval *value, void **cache_slot)
{
	struct SoundIo *s = libsoundio_handle_from(obj)->ptr;
	zval *stored = zend_std_write_property(obj, name, value, cache_slot);

	if (s != NULL && !EG(exception)) {
		libsoundio_soundio_store(s, name, stored);
	}
	return stored;
}

static zval *libsoundio_device_read(zend_object *obj, zend_string *name, int type, void **cache_slot, zval *rv)
{
	struct SoundIoDevice *d = libsoundio_handle_from(obj)->ptr;

	if (d != NULL && libsoundio_device_field(d, name, rv)) {
		return rv;
	}
	return zend_std_read_property(obj, name, type, cache_slot, rv);
}

/*
 * struct SoundIoOutStream and struct SoundIoInStream share their fields but volume and the names
 * of the callbacks: STREAM_FIELDS(prefix, type, data_cb, flow_cb) defines prefix_field() (read
 * field `name` into rv) and prefix_store() (write a type-checked value; layout and device are
 * copied in, name and layout.name held while the struct points into them).
 */
#define STREAM_FIELDS(prefix, type, data_cb, flow_cb, extra_read, extra_store) \
static bool prefix##_field(type *st, zend_string *name, zval *rv) \
{ \
	if (FIELD("device")) { \
		libsoundio_box(rv, st->device, libsoundio_ce_SoundIoDevice); \
	} else if (FIELD("format")) { \
		ZVAL_LONG(rv, st->format); \
	} else if (FIELD("sample_rate")) { \
		ZVAL_LONG(rv, st->sample_rate); \
	} else if (FIELD("layout")) { \
		libsoundio_layout_to(&st->layout, rv); \
	} else if (FIELD("software_latency")) { \
		ZVAL_DOUBLE(rv, st->software_latency); \
	} else if (FIELD("userdata")) { \
		ZVAL_LONG(rv, ADDRESS(st->userdata)); \
	} else if (FIELD(#data_cb)) { \
		ZVAL_LONG(rv, ADDRESS(st->data_cb)); \
	} else if (FIELD(#flow_cb)) { \
		ZVAL_LONG(rv, ADDRESS(st->flow_cb)); \
	} else if (FIELD("error_callback")) { \
		ZVAL_LONG(rv, ADDRESS(st->error_callback)); \
	} else if (FIELD("name")) { \
		libsoundio_string_or_null(rv, st->name); \
	} else if (FIELD("non_terminal_hint")) { \
		ZVAL_BOOL(rv, st->non_terminal_hint); \
	} else if (FIELD("bytes_per_frame")) { \
		ZVAL_LONG(rv, st->bytes_per_frame); \
	} else if (FIELD("bytes_per_sample")) { \
		ZVAL_LONG(rv, st->bytes_per_sample); \
	} else if (FIELD("layout_error")) { \
		ZVAL_LONG(rv, st->layout_error); \
	} extra_read else { \
		return false; \
	} \
	return true; \
} \
static void prefix##_store(type *st, zend_string *name, zval *value) \
{ \
	if (FIELD("device")) { \
		st->device = libsoundio_handle_from(Z_OBJ_P(value))->ptr; \
	} else if (FIELD("format")) { \
		st->format = (enum SoundIoFormat) Z_LVAL_P(value); \
	} else if (FIELD("sample_rate")) { \
		st->sample_rate = (int) Z_LVAL_P(value); \
	} else if (FIELD("layout")) { \
		struct SoundIoChannelLayout layout; \
		if (libsoundio_layout_from(Z_OBJ_P(value), &layout)) { \
			st->layout = layout; \
			if (layout.name != NULL) { \
				zval *kept = zend_read_property(libsoundio_ce_SoundIoChannelLayout, Z_OBJ_P(value), "name", sizeof("name") - 1, true, NULL); \
				st->layout.name = libsoundio_keep_string(&st->layout.name, Z_STR_P(kept)); \
			} else { \
				libsoundio_keep_drop(&st->layout.name); \
			} \
		} \
	} else if (FIELD("software_latency")) { \
		st->software_latency = Z_DVAL_P(value); \
	} else if (FIELD("userdata")) { \
		st->userdata = (void *) (uintptr_t) Z_LVAL_P(value); \
	} else if (FIELD(#data_cb)) { \
		st->data_cb = (void (*)(type *, int, int)) (uintptr_t) Z_LVAL_P(value); \
	} else if (FIELD(#flow_cb)) { \
		st->flow_cb = (void (*)(type *)) (uintptr_t) Z_LVAL_P(value); \
	} else if (FIELD("error_callback")) { \
		st->error_callback = (void (*)(type *, int)) (uintptr_t) Z_LVAL_P(value); \
	} else if (FIELD("name")) { \
		if (Z_TYPE_P(value) == IS_STRING) { \
			st->name = libsoundio_keep_string(&st->name, Z_STR_P(value)); \
		} else { \
			st->name = NULL; \
			libsoundio_keep_drop(&st->name); \
		} \
	} else if (FIELD("non_terminal_hint")) { \
		st->non_terminal_hint = Z_TYPE_P(value) == IS_TRUE; \
	} extra_store \
}

STREAM_FIELDS(libsoundio_outstream, struct SoundIoOutStream, write_callback, underflow_callback,
	else if (FIELD("volume")) { ZVAL_DOUBLE(rv, st->volume); },
	else if (FIELD("volume")) { st->volume = (float) Z_DVAL_P(value); })
STREAM_FIELDS(libsoundio_instream, struct SoundIoInStream, read_callback, overflow_callback, , )

static zval *libsoundio_outstream_read(zend_object *obj, zend_string *name, int type, void **cache_slot, zval *rv)
{
	struct SoundIoOutStream *st = libsoundio_handle_from(obj)->ptr;

	if (st != NULL && libsoundio_outstream_field(st, name, rv)) {
		return rv;
	}
	return zend_std_read_property(obj, name, type, cache_slot, rv);
}

static zval *libsoundio_outstream_write(zend_object *obj, zend_string *name, zval *value, void **cache_slot)
{
	struct SoundIoOutStream *st = libsoundio_handle_from(obj)->ptr;
	zval *stored = zend_std_write_property(obj, name, value, cache_slot);

	if (st != NULL && !EG(exception)) {
		libsoundio_outstream_store(st, name, stored);
	}
	return stored;
}

static zval *libsoundio_instream_read(zend_object *obj, zend_string *name, int type, void **cache_slot, zval *rv)
{
	struct SoundIoInStream *st = libsoundio_handle_from(obj)->ptr;

	if (st != NULL && libsoundio_instream_field(st, name, rv)) {
		return rv;
	}
	return zend_std_read_property(obj, name, type, cache_slot, rv);
}

static zval *libsoundio_instream_write(zend_object *obj, zend_string *name, zval *value, void **cache_slot)
{
	struct SoundIoInStream *st = libsoundio_handle_from(obj)->ptr;
	zval *stored = zend_std_write_property(obj, name, value, cache_slot);

	if (st != NULL && !EG(exception)) {
		libsoundio_instream_store(st, name, stored);
	}
	return stored;
}

/* Field properties have no slot to point into: the engine reads and writes them through the handlers above. */
static zval *libsoundio_no_ptr_ptr(zend_object *obj, zend_string *name, int type, void **cache_slot)
{
	if (libsoundio_handle_from(obj)->ptr != NULL && zend_hash_exists(&obj->ce->properties_info, name)) {
		return NULL;
	}
	return zend_std_get_property_ptr_ptr(obj, name, type, cache_slot);
}

static int libsoundio_field_isset(zend_object *obj, zend_string *name, int check_empty, void **cache_slot)
{
	zval rv, *value;
	int result;

	if (libsoundio_handle_from(obj)->ptr == NULL || !zend_hash_exists(&obj->ce->properties_info, name)) {
		return zend_std_has_property(obj, name, check_empty, cache_slot);
	}
	ZVAL_UNDEF(&rv);
	value = obj->handlers->read_property(obj, name, BP_VAR_IS, cache_slot, &rv);
	result = check_empty == ZEND_PROPERTY_NOT_EMPTY ? zend_is_true(value) : Z_TYPE_P(value) != IS_NULL;
	zval_ptr_dtor(&rv);

	return result;
}

static void libsoundio_field_handlers(zend_class_entry *ce, zend_object_handlers *handlers, zend_object_read_property_t read, zend_object_write_property_t write)
{
	memcpy(handlers, libsoundio_handlers(), sizeof(zend_object_handlers));
	handlers->read_property = read;
	if (write != NULL) {
		handlers->write_property = write;
	}
	handlers->get_property_ptr_ptr = libsoundio_no_ptr_ptr;
	handlers->has_property = libsoundio_field_isset;
	ce->default_object_handlers = handlers;
}

void libsoundio_register_types(void)
{
	libsoundio_ce_SoundIo = register_class_SoundIo();
	libsoundio_handle_setup(libsoundio_ce_SoundIo);
	libsoundio_field_handlers(libsoundio_ce_SoundIo, &libsoundio_soundio_handlers, libsoundio_soundio_read, libsoundio_soundio_write);
	libsoundio_ce_SoundIoDevice = register_class_SoundIoDevice();
	libsoundio_handle_setup(libsoundio_ce_SoundIoDevice);
	libsoundio_field_handlers(libsoundio_ce_SoundIoDevice, &libsoundio_device_handlers, libsoundio_device_read, NULL);
	libsoundio_ce_SoundIoOutStream = register_class_SoundIoOutStream();
	libsoundio_handle_setup(libsoundio_ce_SoundIoOutStream);
	libsoundio_ce_SoundIoInStream = register_class_SoundIoInStream();
	libsoundio_handle_setup(libsoundio_ce_SoundIoInStream);
	libsoundio_field_handlers(libsoundio_ce_SoundIoOutStream, &libsoundio_outstream_handlers, libsoundio_outstream_read, libsoundio_outstream_write);
	libsoundio_field_handlers(libsoundio_ce_SoundIoInStream, &libsoundio_instream_handlers, libsoundio_instream_read, libsoundio_instream_write);
	libsoundio_ce_SoundIoRingBuffer = register_class_SoundIoRingBuffer();
	libsoundio_handle_setup(libsoundio_ce_SoundIoRingBuffer);
	register_class_SoundIoRingBufferBridge();

	libsoundio_ce_SoundIoChannelLayout = register_class_SoundIoChannelLayout();
	libsoundio_ce_SoundIoSampleRateRange = register_class_SoundIoSampleRateRange();
	libsoundio_ce_SoundIoChannelArea = register_class_SoundIoChannelArea();
}
