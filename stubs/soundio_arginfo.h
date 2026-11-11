/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 850bb81305b040c12061a7e1f6933323a82a28d7 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_create, 0, 0, SoundIo, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_destroy, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, soundio, SoundIo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_connect, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, soundio, SoundIo, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_connect_backend, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, soundio, SoundIo, 0)
	ZEND_ARG_TYPE_INFO(0, backend, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_disconnect arginfo_soundio_destroy

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_strerror, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, error, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_backend_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, backend, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_backend_count arginfo_soundio_connect

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_get_backend, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, soundio, SoundIo, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_have_backend, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, backend, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_flush_events arginfo_soundio_destroy

#define arginfo_soundio_wait_events arginfo_soundio_destroy

#define arginfo_soundio_wakeup arginfo_soundio_destroy

#define arginfo_soundio_force_device_scan arginfo_soundio_destroy

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_channel_layout_equal, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, a, SoundIoChannelLayout, 0)
	ZEND_ARG_OBJ_INFO(0, b, SoundIoChannelLayout, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_get_channel_name, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, id, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_parse_channel_id, 0, 2, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, str, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, str_len, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_channel_layout_builtin_count, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_channel_layout_get_builtin, 0, 1, SoundIoChannelLayout, 1)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_channel_layout_get_default, 0, 1, SoundIoChannelLayout, 1)
	ZEND_ARG_TYPE_INFO(0, channel_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_channel_layout_find_channel, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, layout, SoundIoChannelLayout, 0)
	ZEND_ARG_TYPE_INFO(0, channel, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_channel_layout_detect_builtin, 0, 1, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, layout, SoundIoChannelLayout, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_best_matching_channel_layout, 0, 4, SoundIoChannelLayout, 1)
	ZEND_ARG_TYPE_INFO(0, preferred_layouts, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, preferred_layout_count, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, available_layouts, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, available_layout_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_sort_channel_layouts, 0, 2, IS_VOID, 0)
	ZEND_ARG_TYPE_INFO(1, layouts, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, layout_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_get_bytes_per_sample, 0, 1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_format_string, 0, 1, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_input_device_count arginfo_soundio_connect

#define arginfo_soundio_output_device_count arginfo_soundio_connect

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_get_input_device, 0, 2, SoundIoDevice, 1)
	ZEND_ARG_OBJ_INFO(0, soundio, SoundIo, 0)
	ZEND_ARG_TYPE_INFO(0, index, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_get_output_device arginfo_soundio_get_input_device

#define arginfo_soundio_default_input_device_index arginfo_soundio_connect

#define arginfo_soundio_default_output_device_index arginfo_soundio_connect

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_device_ref, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, device, SoundIoDevice, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_device_unref arginfo_soundio_device_ref

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_device_equal, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, a, SoundIoDevice, 0)
	ZEND_ARG_OBJ_INFO(0, b, SoundIoDevice, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_device_sort_channel_layouts arginfo_soundio_device_ref

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_device_supports_format, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SoundIoDevice, 0)
	ZEND_ARG_TYPE_INFO(0, format, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_device_supports_layout, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SoundIoDevice, 0)
	ZEND_ARG_OBJ_INFO(0, layout, SoundIoChannelLayout, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_device_supports_sample_rate, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_OBJ_INFO(0, device, SoundIoDevice, 0)
	ZEND_ARG_TYPE_INFO(0, sample_rate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_device_nearest_sample_rate, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, device, SoundIoDevice, 0)
	ZEND_ARG_TYPE_INFO(0, sample_rate, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_FUNCTION(soundio_create);
ZEND_FUNCTION(soundio_destroy);
ZEND_FUNCTION(soundio_connect);
ZEND_FUNCTION(soundio_connect_backend);
ZEND_FUNCTION(soundio_disconnect);
ZEND_FUNCTION(soundio_strerror);
ZEND_FUNCTION(soundio_backend_name);
ZEND_FUNCTION(soundio_backend_count);
ZEND_FUNCTION(soundio_get_backend);
ZEND_FUNCTION(soundio_have_backend);
ZEND_FUNCTION(soundio_flush_events);
ZEND_FUNCTION(soundio_wait_events);
ZEND_FUNCTION(soundio_wakeup);
ZEND_FUNCTION(soundio_force_device_scan);
ZEND_FUNCTION(soundio_channel_layout_equal);
ZEND_FUNCTION(soundio_get_channel_name);
ZEND_FUNCTION(soundio_parse_channel_id);
ZEND_FUNCTION(soundio_channel_layout_builtin_count);
ZEND_FUNCTION(soundio_channel_layout_get_builtin);
ZEND_FUNCTION(soundio_channel_layout_get_default);
ZEND_FUNCTION(soundio_channel_layout_find_channel);
ZEND_FUNCTION(soundio_channel_layout_detect_builtin);
ZEND_FUNCTION(soundio_best_matching_channel_layout);
ZEND_FUNCTION(soundio_sort_channel_layouts);
ZEND_FUNCTION(soundio_get_bytes_per_sample);
ZEND_FUNCTION(soundio_format_string);
ZEND_FUNCTION(soundio_input_device_count);
ZEND_FUNCTION(soundio_output_device_count);
ZEND_FUNCTION(soundio_get_input_device);
ZEND_FUNCTION(soundio_get_output_device);
ZEND_FUNCTION(soundio_default_input_device_index);
ZEND_FUNCTION(soundio_default_output_device_index);
ZEND_FUNCTION(soundio_device_ref);
ZEND_FUNCTION(soundio_device_unref);
ZEND_FUNCTION(soundio_device_equal);
ZEND_FUNCTION(soundio_device_sort_channel_layouts);
ZEND_FUNCTION(soundio_device_supports_format);
ZEND_FUNCTION(soundio_device_supports_layout);
ZEND_FUNCTION(soundio_device_supports_sample_rate);
ZEND_FUNCTION(soundio_device_nearest_sample_rate);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(soundio_create, arginfo_soundio_create)
	ZEND_FE(soundio_destroy, arginfo_soundio_destroy)
	ZEND_FE(soundio_connect, arginfo_soundio_connect)
	ZEND_FE(soundio_connect_backend, arginfo_soundio_connect_backend)
	ZEND_FE(soundio_disconnect, arginfo_soundio_disconnect)
	ZEND_FE(soundio_strerror, arginfo_soundio_strerror)
	ZEND_FE(soundio_backend_name, arginfo_soundio_backend_name)
	ZEND_FE(soundio_backend_count, arginfo_soundio_backend_count)
	ZEND_FE(soundio_get_backend, arginfo_soundio_get_backend)
	ZEND_FE(soundio_have_backend, arginfo_soundio_have_backend)
	ZEND_FE(soundio_flush_events, arginfo_soundio_flush_events)
	ZEND_FE(soundio_wait_events, arginfo_soundio_wait_events)
	ZEND_FE(soundio_wakeup, arginfo_soundio_wakeup)
	ZEND_FE(soundio_force_device_scan, arginfo_soundio_force_device_scan)
	ZEND_FE(soundio_channel_layout_equal, arginfo_soundio_channel_layout_equal)
	ZEND_FE(soundio_get_channel_name, arginfo_soundio_get_channel_name)
	ZEND_FE(soundio_parse_channel_id, arginfo_soundio_parse_channel_id)
	ZEND_FE(soundio_channel_layout_builtin_count, arginfo_soundio_channel_layout_builtin_count)
	ZEND_FE(soundio_channel_layout_get_builtin, arginfo_soundio_channel_layout_get_builtin)
	ZEND_FE(soundio_channel_layout_get_default, arginfo_soundio_channel_layout_get_default)
	ZEND_FE(soundio_channel_layout_find_channel, arginfo_soundio_channel_layout_find_channel)
	ZEND_FE(soundio_channel_layout_detect_builtin, arginfo_soundio_channel_layout_detect_builtin)
	ZEND_FE(soundio_best_matching_channel_layout, arginfo_soundio_best_matching_channel_layout)
	ZEND_FE(soundio_sort_channel_layouts, arginfo_soundio_sort_channel_layouts)
	ZEND_FE(soundio_get_bytes_per_sample, arginfo_soundio_get_bytes_per_sample)
	ZEND_FE(soundio_format_string, arginfo_soundio_format_string)
	ZEND_FE(soundio_input_device_count, arginfo_soundio_input_device_count)
	ZEND_FE(soundio_output_device_count, arginfo_soundio_output_device_count)
	ZEND_FE(soundio_get_input_device, arginfo_soundio_get_input_device)
	ZEND_FE(soundio_get_output_device, arginfo_soundio_get_output_device)
	ZEND_FE(soundio_default_input_device_index, arginfo_soundio_default_input_device_index)
	ZEND_FE(soundio_default_output_device_index, arginfo_soundio_default_output_device_index)
	ZEND_FE(soundio_device_ref, arginfo_soundio_device_ref)
	ZEND_FE(soundio_device_unref, arginfo_soundio_device_unref)
	ZEND_FE(soundio_device_equal, arginfo_soundio_device_equal)
	ZEND_FE(soundio_device_sort_channel_layouts, arginfo_soundio_device_sort_channel_layouts)
	ZEND_FE(soundio_device_supports_format, arginfo_soundio_device_supports_format)
	ZEND_FE(soundio_device_supports_layout, arginfo_soundio_device_supports_layout)
	ZEND_FE(soundio_device_supports_sample_rate, arginfo_soundio_device_supports_sample_rate)
	ZEND_FE(soundio_device_nearest_sample_rate, arginfo_soundio_device_nearest_sample_rate)
	ZEND_FE_END
};
