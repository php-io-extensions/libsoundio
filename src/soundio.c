/*
 * Context, backends, channel layouts, formats and devices: stubs/soundio.stub.php. Each function
 * calls the soundio.h function of the same name with its arguments as given.
 */
#include "runtime.h"
#include "../stubs/soundio_arginfo.h"

#define SOUNDIO_ARG(var, zv, n) LIBSOUNDIO_ARG(struct SoundIo, var, zv, n)
#define DEVICE_ARG(var, zv, n) LIBSOUNDIO_ARG(struct SoundIoDevice, var, zv, n)

/* A layout parameter as a struct SoundIoChannelLayout, or RETURN_THROWS. */
#define LAYOUT_ARG(var, zv) struct SoundIoChannelLayout var; if (!libsoundio_layout_from(Z_OBJ_P(zv), &var)) { RETURN_THROWS(); }

/* Context */

PHP_FUNCTION(soundio_create)
{
	ZEND_PARSE_PARAMETERS_NONE();
	libsoundio_box(return_value, soundio_create(), libsoundio_ce_SoundIo);
}

PHP_FUNCTION(soundio_destroy)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	libsoundio_keep_drop(&s->app_name);
	libsoundio_callouts_drop(s);
	soundio_destroy(s);
	libsoundio_release(s);
}

PHP_FUNCTION(soundio_connect)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_connect(s));
}

PHP_FUNCTION(soundio_connect_backend)
{
	zval *zs;
	zend_long backend;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
		Z_PARAM_LONG(backend)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_connect_backend(s, (enum SoundIoBackend) backend));
}

PHP_FUNCTION(soundio_disconnect)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	soundio_disconnect(s);
}

PHP_FUNCTION(soundio_flush_events)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	libsoundio_dispatch_begin(s);
	soundio_flush_events(s);
	libsoundio_dispatch_end();
}

PHP_FUNCTION(soundio_wait_events)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	libsoundio_dispatch_begin(s);
	soundio_wait_events(s);
	libsoundio_dispatch_end();
}

PHP_FUNCTION(soundio_wakeup)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	soundio_wakeup(s);
}

PHP_FUNCTION(soundio_force_device_scan)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	soundio_force_device_scan(s);
}

PHP_FUNCTION(soundio_backend_count)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_backend_count(s));
}

PHP_FUNCTION(soundio_input_device_count)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_input_device_count(s));
}

PHP_FUNCTION(soundio_output_device_count)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_output_device_count(s));
}

PHP_FUNCTION(soundio_default_input_device_index)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_default_input_device_index(s));
}

PHP_FUNCTION(soundio_default_output_device_index)
{
	zval *zs;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_default_output_device_index(s));
}

PHP_FUNCTION(soundio_strerror)
{
	zend_long error;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(error)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_STRING(soundio_strerror((int) error));
}

PHP_FUNCTION(soundio_backend_name)
{
	zend_long backend;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(backend)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_STRING(soundio_backend_name((enum SoundIoBackend) backend));
}

PHP_FUNCTION(soundio_get_backend)
{
	zval *zs;
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	RETURN_LONG(soundio_get_backend(s, (int) index));
}

PHP_FUNCTION(soundio_have_backend)
{
	zend_long backend;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(backend)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_BOOL(soundio_have_backend((enum SoundIoBackend) backend));
}

/* Channel layouts */

PHP_FUNCTION(soundio_channel_layout_equal)
{
	zval *za, *zb;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(za, libsoundio_ce_SoundIoChannelLayout)
		Z_PARAM_OBJECT_OF_CLASS(zb, libsoundio_ce_SoundIoChannelLayout)
	ZEND_PARSE_PARAMETERS_END();

	LAYOUT_ARG(a, za);
	LAYOUT_ARG(b, zb);
	RETURN_BOOL(soundio_channel_layout_equal(&a, &b));
}

PHP_FUNCTION(soundio_get_channel_name)
{
	zend_long id;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(id)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_STRING(soundio_get_channel_name((enum SoundIoChannelId) id));
}

PHP_FUNCTION(soundio_parse_channel_id)
{
	zend_string *str;
	zend_long str_len;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_STR(str)
		Z_PARAM_LONG(str_len)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(soundio_parse_channel_id(ZSTR_VAL(str), (int) str_len));
}

PHP_FUNCTION(soundio_channel_layout_builtin_count)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(soundio_channel_layout_builtin_count());
}

static void libsoundio_layout_or_null(zval *rv, const struct SoundIoChannelLayout *layout)
{
	if (layout == NULL) {
		ZVAL_NULL(rv);
	} else {
		libsoundio_layout_to(layout, rv);
	}
}

PHP_FUNCTION(soundio_channel_layout_get_builtin)
{
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	/* libsoundio only assert()s the index, then reads past its builtin table. */
	if (!LIBSOUNDIO_PROBE_OFF("libsoundio-builtin-index") && (index < 0 || index >= soundio_channel_layout_builtin_count())) {
		zend_argument_value_error(1, "must be between 0 and soundio_channel_layout_builtin_count() - 1"); /* binding:libsoundio-builtin-index */
		RETURN_THROWS();
	}
	libsoundio_layout_or_null(return_value, soundio_channel_layout_get_builtin((int) index));
}

PHP_FUNCTION(soundio_channel_layout_get_default)
{
	zend_long channel_count;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(channel_count)
	ZEND_PARSE_PARAMETERS_END();

	libsoundio_layout_or_null(return_value, soundio_channel_layout_get_default((int) channel_count));
}

PHP_FUNCTION(soundio_channel_layout_find_channel)
{
	zval *zlayout;
	zend_long channel;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zlayout, libsoundio_ce_SoundIoChannelLayout)
		Z_PARAM_LONG(channel)
	ZEND_PARSE_PARAMETERS_END();

	LAYOUT_ARG(layout, zlayout);
	RETURN_LONG(soundio_channel_layout_find_channel(&layout, (enum SoundIoChannelId) channel));
}

PHP_FUNCTION(soundio_channel_layout_detect_builtin)
{
	zval *zlayout;
	bool found;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zlayout, libsoundio_ce_SoundIoChannelLayout)
	ZEND_PARSE_PARAMETERS_END();

	LAYOUT_ARG(layout, zlayout);
	found = soundio_channel_layout_detect_builtin(&layout);
	if (found) {
		zend_update_property_string(libsoundio_ce_SoundIoChannelLayout, Z_OBJ_P(zlayout), "name", sizeof("name") - 1, layout.name);
	}
	RETURN_BOOL(found);
}

PHP_FUNCTION(soundio_best_matching_channel_layout)
{
	HashTable *preferred_list, *available_list;
	zend_long preferred_count, available_count;
	struct SoundIoChannelLayout *preferred, *available;
	const struct SoundIoChannelLayout *best;

	ZEND_PARSE_PARAMETERS_START(4, 4)
		Z_PARAM_ARRAY_HT(preferred_list)
		Z_PARAM_LONG(preferred_count)
		Z_PARAM_ARRAY_HT(available_list)
		Z_PARAM_LONG(available_count)
	ZEND_PARSE_PARAMETERS_END();

	if (!libsoundio_list_count(preferred_count, zend_hash_num_elements(preferred_list), 2, 1)
		|| !libsoundio_list_count(available_count, zend_hash_num_elements(available_list), 4, 3)) {
		RETURN_THROWS();
	}
	preferred = libsoundio_layouts_from(preferred_list, 1);
	if (preferred == NULL) {
		RETURN_THROWS();
	}
	available = libsoundio_layouts_from(available_list, 3);
	if (available == NULL) {
		efree(preferred);
		RETURN_THROWS();
	}
	best = soundio_best_matching_channel_layout(preferred, (int) preferred_count, available, (int) available_count);
	libsoundio_layout_or_null(return_value, best);
	efree(preferred);
	efree(available);
}

PHP_FUNCTION(soundio_sort_channel_layouts)
{
	zval *zlist, layout, sorted;
	zend_long layout_count;
	struct SoundIoChannelLayout *layouts;
	uint32_t length;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_ARRAY_EX(zlist, 0, 1)
		Z_PARAM_LONG(layout_count)
	ZEND_PARSE_PARAMETERS_END();

	length = zend_hash_num_elements(Z_ARRVAL_P(zlist));
	if (!libsoundio_list_count(layout_count, length, 2, 1)) {
		RETURN_THROWS();
	}
	layouts = libsoundio_layouts_from(Z_ARRVAL_P(zlist), 1);
	if (layouts == NULL) {
		RETURN_THROWS();
	}
	soundio_sort_channel_layouts(layouts, (int) layout_count);

	/* The sorted structs come back as new SoundIoChannelLayout objects, in their new order. */
	array_init_size(&sorted, length);
	for (uint32_t i = 0; i < length; i++) {
		libsoundio_layout_to(&layouts[i], &layout);
		add_next_index_zval(&sorted, &layout);
	}
	efree(layouts);
	/* zlist is the separated array inside the reference: replace it, as sort() does. */
	zval_ptr_dtor(zlist);
	ZVAL_COPY_VALUE(zlist, &sorted);
}

/* Formats */

PHP_FUNCTION(soundio_get_bytes_per_sample)
{
	zend_long format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_LONG(soundio_get_bytes_per_sample((enum SoundIoFormat) format));
}

PHP_FUNCTION(soundio_format_string)
{
	zend_long format;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();

	RETURN_STRING(soundio_format_string((enum SoundIoFormat) format));
}

/* Devices */

PHP_FUNCTION(soundio_get_input_device)
{
	zval *zs;
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	libsoundio_box(return_value, soundio_get_input_device(s, (int) index), libsoundio_ce_SoundIoDevice);
}

PHP_FUNCTION(soundio_get_output_device)
{
	zval *zs;
	zend_long index;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
		Z_PARAM_LONG(index)
	ZEND_PARSE_PARAMETERS_END();

	SOUNDIO_ARG(s, zs, 1);
	libsoundio_box(return_value, soundio_get_output_device(s, (int) index), libsoundio_ce_SoundIoDevice);
}

PHP_FUNCTION(soundio_device_ref)
{
	zval *zd;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
	ZEND_PARSE_PARAMETERS_END();

	DEVICE_ARG(d, zd, 1);
	soundio_device_ref(d);
}

PHP_FUNCTION(soundio_device_unref)
{
	zval *zd;
	bool last;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
	ZEND_PARSE_PARAMETERS_END();

	struct SoundIoDevice *d = LIBSOUNDIO_PTR(zd);
	/* libsoundio frees the device when this reference was its last one; it takes NULL as a no-op. */
	last = d != NULL && d->ref_count == 1;
	soundio_device_unref(d);
	if (last) {
		libsoundio_release(d);
	}
}

PHP_FUNCTION(soundio_device_equal)
{
	zval *za, *zb;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(za, libsoundio_ce_SoundIoDevice)
		Z_PARAM_OBJECT_OF_CLASS(zb, libsoundio_ce_SoundIoDevice)
	ZEND_PARSE_PARAMETERS_END();

	DEVICE_ARG(a, za, 1);
	DEVICE_ARG(b, zb, 2);
	RETURN_BOOL(soundio_device_equal(a, b));
}

PHP_FUNCTION(soundio_device_sort_channel_layouts)
{
	zval *zd;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
	ZEND_PARSE_PARAMETERS_END();

	DEVICE_ARG(d, zd, 1);
	soundio_device_sort_channel_layouts(d);
}

PHP_FUNCTION(soundio_device_supports_format)
{
	zval *zd;
	zend_long format;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
		Z_PARAM_LONG(format)
	ZEND_PARSE_PARAMETERS_END();

	DEVICE_ARG(d, zd, 1);
	RETURN_BOOL(soundio_device_supports_format(d, (enum SoundIoFormat) format));
}

PHP_FUNCTION(soundio_device_supports_layout)
{
	zval *zd, *zlayout;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
		Z_PARAM_OBJECT_OF_CLASS(zlayout, libsoundio_ce_SoundIoChannelLayout)
	ZEND_PARSE_PARAMETERS_END();

	DEVICE_ARG(d, zd, 1);
	LAYOUT_ARG(layout, zlayout);
	RETURN_BOOL(soundio_device_supports_layout(d, &layout));
}

PHP_FUNCTION(soundio_device_supports_sample_rate)
{
	zval *zd;
	zend_long sample_rate;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
		Z_PARAM_LONG(sample_rate)
	ZEND_PARSE_PARAMETERS_END();

	DEVICE_ARG(d, zd, 1);
	RETURN_BOOL(soundio_device_supports_sample_rate(d, (int) sample_rate));
}

PHP_FUNCTION(soundio_device_nearest_sample_rate)
{
	zval *zd;
	zend_long sample_rate;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
		Z_PARAM_LONG(sample_rate)
	ZEND_PARSE_PARAMETERS_END();

	DEVICE_ARG(d, zd, 1);
	RETURN_LONG(soundio_device_nearest_sample_rate(d, (int) sample_rate));
}

void libsoundio_register_soundio(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
