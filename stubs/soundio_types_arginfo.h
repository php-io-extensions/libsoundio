/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: bb3074c7dd587af3a45ecdac541c2c863b8241d6 */

ZEND_BEGIN_ARG_INFO_EX(arginfo_class_SoundIo___construct, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SoundIo_pointer, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_class_SoundIo_fromPointer, 0, 1, IS_STATIC, 1)
	ZEND_ARG_TYPE_INFO(0, pointer, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_class_SoundIoDevice___construct arginfo_class_SoundIo___construct

#define arginfo_class_SoundIoDevice_pointer arginfo_class_SoundIo_pointer

#define arginfo_class_SoundIoDevice_fromPointer arginfo_class_SoundIo_fromPointer

#define arginfo_class_SoundIoOutStream___construct arginfo_class_SoundIo___construct

#define arginfo_class_SoundIoOutStream_pointer arginfo_class_SoundIo_pointer

#define arginfo_class_SoundIoOutStream_fromPointer arginfo_class_SoundIo_fromPointer

#define arginfo_class_SoundIoInStream___construct arginfo_class_SoundIo___construct

#define arginfo_class_SoundIoInStream_pointer arginfo_class_SoundIo_pointer

#define arginfo_class_SoundIoInStream_fromPointer arginfo_class_SoundIo_fromPointer

#define arginfo_class_SoundIoRingBuffer___construct arginfo_class_SoundIo___construct

#define arginfo_class_SoundIoRingBuffer_pointer arginfo_class_SoundIo_pointer

#define arginfo_class_SoundIoRingBuffer_fromPointer arginfo_class_SoundIo_fromPointer

ZEND_METHOD(SoundIo, __construct);
ZEND_METHOD(SoundIo, pointer);
ZEND_METHOD(SoundIo, fromPointer);
ZEND_METHOD(SoundIoDevice, __construct);
ZEND_METHOD(SoundIoDevice, pointer);
ZEND_METHOD(SoundIoDevice, fromPointer);
ZEND_METHOD(SoundIoOutStream, __construct);
ZEND_METHOD(SoundIoOutStream, pointer);
ZEND_METHOD(SoundIoOutStream, fromPointer);
ZEND_METHOD(SoundIoInStream, __construct);
ZEND_METHOD(SoundIoInStream, pointer);
ZEND_METHOD(SoundIoInStream, fromPointer);
ZEND_METHOD(SoundIoRingBuffer, __construct);
ZEND_METHOD(SoundIoRingBuffer, pointer);
ZEND_METHOD(SoundIoRingBuffer, fromPointer);

static const zend_function_entry class_SoundIo_methods[] = {
	ZEND_ME(SoundIo, __construct, arginfo_class_SoundIo___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SoundIo, pointer, arginfo_class_SoundIo_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SoundIo, fromPointer, arginfo_class_SoundIo_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SoundIoDevice_methods[] = {
	ZEND_ME(SoundIoDevice, __construct, arginfo_class_SoundIoDevice___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SoundIoDevice, pointer, arginfo_class_SoundIoDevice_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SoundIoDevice, fromPointer, arginfo_class_SoundIoDevice_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SoundIoOutStream_methods[] = {
	ZEND_ME(SoundIoOutStream, __construct, arginfo_class_SoundIoOutStream___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SoundIoOutStream, pointer, arginfo_class_SoundIoOutStream_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SoundIoOutStream, fromPointer, arginfo_class_SoundIoOutStream_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SoundIoInStream_methods[] = {
	ZEND_ME(SoundIoInStream, __construct, arginfo_class_SoundIoInStream___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SoundIoInStream, pointer, arginfo_class_SoundIoInStream_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SoundIoInStream, fromPointer, arginfo_class_SoundIoInStream_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static const zend_function_entry class_SoundIoRingBuffer_methods[] = {
	ZEND_ME(SoundIoRingBuffer, __construct, arginfo_class_SoundIoRingBuffer___construct, ZEND_ACC_PRIVATE)
	ZEND_ME(SoundIoRingBuffer, pointer, arginfo_class_SoundIoRingBuffer_pointer, ZEND_ACC_PUBLIC)
	ZEND_ME(SoundIoRingBuffer, fromPointer, arginfo_class_SoundIoRingBuffer_fromPointer, ZEND_ACC_PUBLIC|ZEND_ACC_STATIC)
	ZEND_FE_END
};

static zend_class_entry *register_class_SoundIo(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIo", class_SoundIo_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_userdata_default_value;
	ZVAL_UNDEF(&property_userdata_default_value);
	zend_string *property_userdata_name = zend_string_init("userdata", sizeof("userdata") - 1, 1);
	zend_declare_typed_property(class_entry, property_userdata_name, &property_userdata_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_userdata_name);

	zval property_on_devices_change_default_value;
	ZVAL_UNDEF(&property_on_devices_change_default_value);
	zend_string *property_on_devices_change_name = zend_string_init("on_devices_change", sizeof("on_devices_change") - 1, 1);
	zend_string *property_on_devices_change_class_Closure = zend_string_init("Closure", sizeof("Closure")-1, 1);
	zend_declare_typed_property(class_entry, property_on_devices_change_name, &property_on_devices_change_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_on_devices_change_class_Closure, 0, MAY_BE_NULL));
	zend_string_release(property_on_devices_change_name);

	zval property_on_backend_disconnect_default_value;
	ZVAL_UNDEF(&property_on_backend_disconnect_default_value);
	zend_string *property_on_backend_disconnect_name = zend_string_init("on_backend_disconnect", sizeof("on_backend_disconnect") - 1, 1);
	zend_string *property_on_backend_disconnect_class_Closure = zend_string_init("Closure", sizeof("Closure")-1, 1);
	zend_declare_typed_property(class_entry, property_on_backend_disconnect_name, &property_on_backend_disconnect_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_on_backend_disconnect_class_Closure, 0, MAY_BE_NULL));
	zend_string_release(property_on_backend_disconnect_name);

	zval property_on_events_signal_default_value;
	ZVAL_UNDEF(&property_on_events_signal_default_value);
	zend_string *property_on_events_signal_name = zend_string_init("on_events_signal", sizeof("on_events_signal") - 1, 1);
	zend_declare_typed_property(class_entry, property_on_events_signal_name, &property_on_events_signal_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_on_events_signal_name);

	zval property_current_backend_default_value;
	ZVAL_UNDEF(&property_current_backend_default_value);
	zend_string *property_current_backend_name = zend_string_init("current_backend", sizeof("current_backend") - 1, 1);
	zend_declare_typed_property(class_entry, property_current_backend_name, &property_current_backend_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_current_backend_name);

	zval property_app_name_default_value;
	ZVAL_UNDEF(&property_app_name_default_value);
	zend_string *property_app_name_name = zend_string_init("app_name", sizeof("app_name") - 1, 1);
	zend_declare_typed_property(class_entry, property_app_name_name, &property_app_name_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_app_name_name);

	zval property_emit_rtprio_warning_default_value;
	ZVAL_UNDEF(&property_emit_rtprio_warning_default_value);
	zend_string *property_emit_rtprio_warning_name = zend_string_init("emit_rtprio_warning", sizeof("emit_rtprio_warning") - 1, 1);
	zend_declare_typed_property(class_entry, property_emit_rtprio_warning_name, &property_emit_rtprio_warning_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_emit_rtprio_warning_name);

	zval property_jack_info_callback_default_value;
	ZVAL_UNDEF(&property_jack_info_callback_default_value);
	zend_string *property_jack_info_callback_name = zend_string_init("jack_info_callback", sizeof("jack_info_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_jack_info_callback_name, &property_jack_info_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_jack_info_callback_name);

	zval property_jack_error_callback_default_value;
	ZVAL_UNDEF(&property_jack_error_callback_default_value);
	zend_string *property_jack_error_callback_name = zend_string_init("jack_error_callback", sizeof("jack_error_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_jack_error_callback_name, &property_jack_error_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_jack_error_callback_name);

	return class_entry;
}

static zend_class_entry *register_class_SoundIoDevice(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIoDevice", class_SoundIoDevice_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_soundio_default_value;
	ZVAL_UNDEF(&property_soundio_default_value);
	zend_string *property_soundio_name = zend_string_init("soundio", sizeof("soundio") - 1, 1);
	zend_string *property_soundio_class_SoundIo = zend_string_init("SoundIo", sizeof("SoundIo")-1, 1);
	zend_declare_typed_property(class_entry, property_soundio_name, &property_soundio_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_soundio_class_SoundIo, 0, 0));
	zend_string_release(property_soundio_name);

	zval property_id_default_value;
	ZVAL_UNDEF(&property_id_default_value);
	zend_string *property_id_name = zend_string_init("id", sizeof("id") - 1, 1);
	zend_declare_typed_property(class_entry, property_id_name, &property_id_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_id_name);

	zval property_name_default_value;
	ZVAL_UNDEF(&property_name_default_value);
	zend_string *property_name_name = zend_string_init("name", sizeof("name") - 1, 1);
	zend_declare_typed_property(class_entry, property_name_name, &property_name_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
	zend_string_release(property_name_name);

	zval property_aim_default_value;
	ZVAL_UNDEF(&property_aim_default_value);
	zend_string *property_aim_name = zend_string_init("aim", sizeof("aim") - 1, 1);
	zend_declare_typed_property(class_entry, property_aim_name, &property_aim_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_aim_name);

	zval property_layouts_default_value;
	ZVAL_UNDEF(&property_layouts_default_value);
	zend_string *property_layouts_name = zend_string_init("layouts", sizeof("layouts") - 1, 1);
	zend_declare_typed_property(class_entry, property_layouts_name, &property_layouts_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_layouts_name);

	zval property_layout_count_default_value;
	ZVAL_UNDEF(&property_layout_count_default_value);
	zend_string *property_layout_count_name = zend_string_init("layout_count", sizeof("layout_count") - 1, 1);
	zend_declare_typed_property(class_entry, property_layout_count_name, &property_layout_count_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_layout_count_name);

	zval property_current_layout_default_value;
	ZVAL_UNDEF(&property_current_layout_default_value);
	zend_string *property_current_layout_name = zend_string_init("current_layout", sizeof("current_layout") - 1, 1);
	zend_string *property_current_layout_class_SoundIoChannelLayout = zend_string_init("SoundIoChannelLayout", sizeof("SoundIoChannelLayout")-1, 1);
	zend_declare_typed_property(class_entry, property_current_layout_name, &property_current_layout_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_current_layout_class_SoundIoChannelLayout, 0, 0));
	zend_string_release(property_current_layout_name);

	zval property_formats_default_value;
	ZVAL_UNDEF(&property_formats_default_value);
	zend_string *property_formats_name = zend_string_init("formats", sizeof("formats") - 1, 1);
	zend_declare_typed_property(class_entry, property_formats_name, &property_formats_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_formats_name);

	zval property_format_count_default_value;
	ZVAL_UNDEF(&property_format_count_default_value);
	zend_string *property_format_count_name = zend_string_init("format_count", sizeof("format_count") - 1, 1);
	zend_declare_typed_property(class_entry, property_format_count_name, &property_format_count_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_format_count_name);

	zval property_current_format_default_value;
	ZVAL_UNDEF(&property_current_format_default_value);
	zend_string *property_current_format_name = zend_string_init("current_format", sizeof("current_format") - 1, 1);
	zend_declare_typed_property(class_entry, property_current_format_name, &property_current_format_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_current_format_name);

	zval property_sample_rates_default_value;
	ZVAL_UNDEF(&property_sample_rates_default_value);
	zend_string *property_sample_rates_name = zend_string_init("sample_rates", sizeof("sample_rates") - 1, 1);
	zend_declare_typed_property(class_entry, property_sample_rates_name, &property_sample_rates_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_sample_rates_name);

	zval property_sample_rate_count_default_value;
	ZVAL_UNDEF(&property_sample_rate_count_default_value);
	zend_string *property_sample_rate_count_name = zend_string_init("sample_rate_count", sizeof("sample_rate_count") - 1, 1);
	zend_declare_typed_property(class_entry, property_sample_rate_count_name, &property_sample_rate_count_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_sample_rate_count_name);

	zval property_sample_rate_current_default_value;
	ZVAL_UNDEF(&property_sample_rate_current_default_value);
	zend_string *property_sample_rate_current_name = zend_string_init("sample_rate_current", sizeof("sample_rate_current") - 1, 1);
	zend_declare_typed_property(class_entry, property_sample_rate_current_name, &property_sample_rate_current_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_sample_rate_current_name);

	zval property_software_latency_min_default_value;
	ZVAL_UNDEF(&property_software_latency_min_default_value);
	zend_string *property_software_latency_min_name = zend_string_init("software_latency_min", sizeof("software_latency_min") - 1, 1);
	zend_declare_typed_property(class_entry, property_software_latency_min_name, &property_software_latency_min_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_software_latency_min_name);

	zval property_software_latency_max_default_value;
	ZVAL_UNDEF(&property_software_latency_max_default_value);
	zend_string *property_software_latency_max_name = zend_string_init("software_latency_max", sizeof("software_latency_max") - 1, 1);
	zend_declare_typed_property(class_entry, property_software_latency_max_name, &property_software_latency_max_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_software_latency_max_name);

	zval property_software_latency_current_default_value;
	ZVAL_UNDEF(&property_software_latency_current_default_value);
	zend_string *property_software_latency_current_name = zend_string_init("software_latency_current", sizeof("software_latency_current") - 1, 1);
	zend_declare_typed_property(class_entry, property_software_latency_current_name, &property_software_latency_current_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_software_latency_current_name);

	zval property_is_raw_default_value;
	ZVAL_UNDEF(&property_is_raw_default_value);
	zend_string *property_is_raw_name = zend_string_init("is_raw", sizeof("is_raw") - 1, 1);
	zend_declare_typed_property(class_entry, property_is_raw_name, &property_is_raw_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_is_raw_name);

	zval property_ref_count_default_value;
	ZVAL_UNDEF(&property_ref_count_default_value);
	zend_string *property_ref_count_name = zend_string_init("ref_count", sizeof("ref_count") - 1, 1);
	zend_declare_typed_property(class_entry, property_ref_count_name, &property_ref_count_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_ref_count_name);

	zval property_probe_error_default_value;
	ZVAL_UNDEF(&property_probe_error_default_value);
	zend_string *property_probe_error_name = zend_string_init("probe_error", sizeof("probe_error") - 1, 1);
	zend_declare_typed_property(class_entry, property_probe_error_name, &property_probe_error_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_probe_error_name);

	return class_entry;
}

static zend_class_entry *register_class_SoundIoOutStream(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIoOutStream", class_SoundIoOutStream_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_device_default_value;
	ZVAL_UNDEF(&property_device_default_value);
	zend_string *property_device_name = zend_string_init("device", sizeof("device") - 1, 1);
	zend_string *property_device_class_SoundIoDevice = zend_string_init("SoundIoDevice", sizeof("SoundIoDevice")-1, 1);
	zend_declare_typed_property(class_entry, property_device_name, &property_device_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_device_class_SoundIoDevice, 0, 0));
	zend_string_release(property_device_name);

	zval property_format_default_value;
	ZVAL_UNDEF(&property_format_default_value);
	zend_string *property_format_name = zend_string_init("format", sizeof("format") - 1, 1);
	zend_declare_typed_property(class_entry, property_format_name, &property_format_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_format_name);

	zval property_sample_rate_default_value;
	ZVAL_UNDEF(&property_sample_rate_default_value);
	zend_string *property_sample_rate_name = zend_string_init("sample_rate", sizeof("sample_rate") - 1, 1);
	zend_declare_typed_property(class_entry, property_sample_rate_name, &property_sample_rate_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_sample_rate_name);

	zval property_layout_default_value;
	ZVAL_UNDEF(&property_layout_default_value);
	zend_string *property_layout_name = zend_string_init("layout", sizeof("layout") - 1, 1);
	zend_string *property_layout_class_SoundIoChannelLayout = zend_string_init("SoundIoChannelLayout", sizeof("SoundIoChannelLayout")-1, 1);
	zend_declare_typed_property(class_entry, property_layout_name, &property_layout_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_layout_class_SoundIoChannelLayout, 0, 0));
	zend_string_release(property_layout_name);

	zval property_software_latency_default_value;
	ZVAL_UNDEF(&property_software_latency_default_value);
	zend_string *property_software_latency_name = zend_string_init("software_latency", sizeof("software_latency") - 1, 1);
	zend_declare_typed_property(class_entry, property_software_latency_name, &property_software_latency_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_software_latency_name);

	zval property_volume_default_value;
	ZVAL_UNDEF(&property_volume_default_value);
	zend_string *property_volume_name = zend_string_init("volume", sizeof("volume") - 1, 1);
	zend_declare_typed_property(class_entry, property_volume_name, &property_volume_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_volume_name);

	zval property_userdata_default_value;
	ZVAL_UNDEF(&property_userdata_default_value);
	zend_string *property_userdata_name = zend_string_init("userdata", sizeof("userdata") - 1, 1);
	zend_declare_typed_property(class_entry, property_userdata_name, &property_userdata_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_userdata_name);

	zval property_write_callback_default_value;
	ZVAL_UNDEF(&property_write_callback_default_value);
	zend_string *property_write_callback_name = zend_string_init("write_callback", sizeof("write_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_write_callback_name, &property_write_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_write_callback_name);

	zval property_underflow_callback_default_value;
	ZVAL_UNDEF(&property_underflow_callback_default_value);
	zend_string *property_underflow_callback_name = zend_string_init("underflow_callback", sizeof("underflow_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_underflow_callback_name, &property_underflow_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_underflow_callback_name);

	zval property_error_callback_default_value;
	ZVAL_UNDEF(&property_error_callback_default_value);
	zend_string *property_error_callback_name = zend_string_init("error_callback", sizeof("error_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_error_callback_name, &property_error_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_error_callback_name);

	zval property_name_default_value;
	ZVAL_UNDEF(&property_name_default_value);
	zend_string *property_name_name = zend_string_init("name", sizeof("name") - 1, 1);
	zend_declare_typed_property(class_entry, property_name_name, &property_name_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_name_name);

	zval property_non_terminal_hint_default_value;
	ZVAL_UNDEF(&property_non_terminal_hint_default_value);
	zend_string *property_non_terminal_hint_name = zend_string_init("non_terminal_hint", sizeof("non_terminal_hint") - 1, 1);
	zend_declare_typed_property(class_entry, property_non_terminal_hint_name, &property_non_terminal_hint_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_non_terminal_hint_name);

	zval property_bytes_per_frame_default_value;
	ZVAL_UNDEF(&property_bytes_per_frame_default_value);
	zend_string *property_bytes_per_frame_name = zend_string_init("bytes_per_frame", sizeof("bytes_per_frame") - 1, 1);
	zend_declare_typed_property(class_entry, property_bytes_per_frame_name, &property_bytes_per_frame_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_bytes_per_frame_name);

	zval property_bytes_per_sample_default_value;
	ZVAL_UNDEF(&property_bytes_per_sample_default_value);
	zend_string *property_bytes_per_sample_name = zend_string_init("bytes_per_sample", sizeof("bytes_per_sample") - 1, 1);
	zend_declare_typed_property(class_entry, property_bytes_per_sample_name, &property_bytes_per_sample_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_bytes_per_sample_name);

	zval property_layout_error_default_value;
	ZVAL_UNDEF(&property_layout_error_default_value);
	zend_string *property_layout_error_name = zend_string_init("layout_error", sizeof("layout_error") - 1, 1);
	zend_declare_typed_property(class_entry, property_layout_error_name, &property_layout_error_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_layout_error_name);

	return class_entry;
}

static zend_class_entry *register_class_SoundIoInStream(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIoInStream", class_SoundIoInStream_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	zval property_device_default_value;
	ZVAL_UNDEF(&property_device_default_value);
	zend_string *property_device_name = zend_string_init("device", sizeof("device") - 1, 1);
	zend_string *property_device_class_SoundIoDevice = zend_string_init("SoundIoDevice", sizeof("SoundIoDevice")-1, 1);
	zend_declare_typed_property(class_entry, property_device_name, &property_device_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_device_class_SoundIoDevice, 0, 0));
	zend_string_release(property_device_name);

	zval property_format_default_value;
	ZVAL_UNDEF(&property_format_default_value);
	zend_string *property_format_name = zend_string_init("format", sizeof("format") - 1, 1);
	zend_declare_typed_property(class_entry, property_format_name, &property_format_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_format_name);

	zval property_sample_rate_default_value;
	ZVAL_UNDEF(&property_sample_rate_default_value);
	zend_string *property_sample_rate_name = zend_string_init("sample_rate", sizeof("sample_rate") - 1, 1);
	zend_declare_typed_property(class_entry, property_sample_rate_name, &property_sample_rate_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_sample_rate_name);

	zval property_layout_default_value;
	ZVAL_UNDEF(&property_layout_default_value);
	zend_string *property_layout_name = zend_string_init("layout", sizeof("layout") - 1, 1);
	zend_string *property_layout_class_SoundIoChannelLayout = zend_string_init("SoundIoChannelLayout", sizeof("SoundIoChannelLayout")-1, 1);
	zend_declare_typed_property(class_entry, property_layout_name, &property_layout_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_layout_class_SoundIoChannelLayout, 0, 0));
	zend_string_release(property_layout_name);

	zval property_software_latency_default_value;
	ZVAL_UNDEF(&property_software_latency_default_value);
	zend_string *property_software_latency_name = zend_string_init("software_latency", sizeof("software_latency") - 1, 1);
	zend_declare_typed_property(class_entry, property_software_latency_name, &property_software_latency_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
	zend_string_release(property_software_latency_name);

	zval property_userdata_default_value;
	ZVAL_UNDEF(&property_userdata_default_value);
	zend_string *property_userdata_name = zend_string_init("userdata", sizeof("userdata") - 1, 1);
	zend_declare_typed_property(class_entry, property_userdata_name, &property_userdata_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_userdata_name);

	zval property_read_callback_default_value;
	ZVAL_UNDEF(&property_read_callback_default_value);
	zend_string *property_read_callback_name = zend_string_init("read_callback", sizeof("read_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_read_callback_name, &property_read_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_read_callback_name);

	zval property_overflow_callback_default_value;
	ZVAL_UNDEF(&property_overflow_callback_default_value);
	zend_string *property_overflow_callback_name = zend_string_init("overflow_callback", sizeof("overflow_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_overflow_callback_name, &property_overflow_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_overflow_callback_name);

	zval property_error_callback_default_value;
	ZVAL_UNDEF(&property_error_callback_default_value);
	zend_string *property_error_callback_name = zend_string_init("error_callback", sizeof("error_callback") - 1, 1);
	zend_declare_typed_property(class_entry, property_error_callback_name, &property_error_callback_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_error_callback_name);

	zval property_name_default_value;
	ZVAL_UNDEF(&property_name_default_value);
	zend_string *property_name_name = zend_string_init("name", sizeof("name") - 1, 1);
	zend_declare_typed_property(class_entry, property_name_name, &property_name_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_name_name);

	zval property_non_terminal_hint_default_value;
	ZVAL_UNDEF(&property_non_terminal_hint_default_value);
	zend_string *property_non_terminal_hint_name = zend_string_init("non_terminal_hint", sizeof("non_terminal_hint") - 1, 1);
	zend_declare_typed_property(class_entry, property_non_terminal_hint_name, &property_non_terminal_hint_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_BOOL));
	zend_string_release(property_non_terminal_hint_name);

	zval property_bytes_per_frame_default_value;
	ZVAL_UNDEF(&property_bytes_per_frame_default_value);
	zend_string *property_bytes_per_frame_name = zend_string_init("bytes_per_frame", sizeof("bytes_per_frame") - 1, 1);
	zend_declare_typed_property(class_entry, property_bytes_per_frame_name, &property_bytes_per_frame_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_bytes_per_frame_name);

	zval property_bytes_per_sample_default_value;
	ZVAL_UNDEF(&property_bytes_per_sample_default_value);
	zend_string *property_bytes_per_sample_name = zend_string_init("bytes_per_sample", sizeof("bytes_per_sample") - 1, 1);
	zend_declare_typed_property(class_entry, property_bytes_per_sample_name, &property_bytes_per_sample_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_bytes_per_sample_name);

	zval property_layout_error_default_value;
	ZVAL_UNDEF(&property_layout_error_default_value);
	zend_string *property_layout_error_name = zend_string_init("layout_error", sizeof("layout_error") - 1, 1);
	zend_declare_typed_property(class_entry, property_layout_error_name, &property_layout_error_default_value, ZEND_ACC_PUBLIC|ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_layout_error_name);

	return class_entry;
}

static zend_class_entry *register_class_SoundIoRingBuffer(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIoRingBuffer", class_SoundIoRingBuffer_methods);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL|ZEND_ACC_NOT_SERIALIZABLE);

	return class_entry;
}

static zend_class_entry *register_class_SoundIoChannelLayout(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIoChannelLayout", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_name_default_value;
	ZVAL_NULL(&property_name_default_value);
	zend_string *property_name_name = zend_string_init("name", sizeof("name") - 1, 1);
	zend_declare_typed_property(class_entry, property_name_name, &property_name_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING|MAY_BE_NULL));
	zend_string_release(property_name_name);

	zval property_channel_count_default_value;
	ZVAL_LONG(&property_channel_count_default_value, 0);
	zend_string *property_channel_count_name = zend_string_init("channel_count", sizeof("channel_count") - 1, 1);
	zend_declare_typed_property(class_entry, property_channel_count_name, &property_channel_count_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_channel_count_name);

	zval property_channels_default_value;
	ZVAL_EMPTY_ARRAY(&property_channels_default_value);
	zend_string *property_channels_name = zend_string_init("channels", sizeof("channels") - 1, 1);
	zend_declare_typed_property(class_entry, property_channels_name, &property_channels_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_channels_name);

	return class_entry;
}

static zend_class_entry *register_class_SoundIoSampleRateRange(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIoSampleRateRange", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_min_default_value;
	ZVAL_LONG(&property_min_default_value, 0);
	zend_string *property_min_name = zend_string_init("min", sizeof("min") - 1, 1);
	zend_declare_typed_property(class_entry, property_min_name, &property_min_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_min_name);

	zval property_max_default_value;
	ZVAL_LONG(&property_max_default_value, 0);
	zend_string *property_max_name = zend_string_init("max", sizeof("max") - 1, 1);
	zend_declare_typed_property(class_entry, property_max_name, &property_max_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_max_name);

	return class_entry;
}

static zend_class_entry *register_class_SoundIoChannelArea(void)
{
	zend_class_entry ce, *class_entry;

	INIT_CLASS_ENTRY(ce, "SoundIoChannelArea", NULL);
	class_entry = zend_register_internal_class_with_flags(&ce, NULL, ZEND_ACC_FINAL);

	zval property_ptr_default_value;
	ZVAL_LONG(&property_ptr_default_value, 0);
	zend_string *property_ptr_name = zend_string_init("ptr", sizeof("ptr") - 1, 1);
	zend_declare_typed_property(class_entry, property_ptr_name, &property_ptr_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_ptr_name);

	zval property_step_default_value;
	ZVAL_LONG(&property_step_default_value, 0);
	zend_string *property_step_name = zend_string_init("step", sizeof("step") - 1, 1);
	zend_declare_typed_property(class_entry, property_step_name, &property_step_default_value, ZEND_ACC_PUBLIC, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
	zend_string_release(property_step_name);

	return class_entry;
}
