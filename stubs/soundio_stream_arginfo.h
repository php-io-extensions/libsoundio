/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: c08048dda72a903d510eb0a95c27589d3bef8872 */

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_outstream_create, 0, 1, SoundIoOutStream, 1)
	ZEND_ARG_OBJ_INFO(0, device, SoundIoDevice, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_outstream_destroy, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, outstream, SoundIoOutStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_outstream_open, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, outstream, SoundIoOutStream, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_outstream_start arginfo_soundio_outstream_open

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_outstream_begin_write, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, outstream, SoundIoOutStream, 0)
	ZEND_ARG_TYPE_INFO(1, areas, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(1, frame_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_outstream_end_write arginfo_soundio_outstream_open

#define arginfo_soundio_outstream_clear_buffer arginfo_soundio_outstream_open

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_outstream_pause, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, outstream, SoundIoOutStream, 0)
	ZEND_ARG_TYPE_INFO(0, pause, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_outstream_get_latency, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, outstream, SoundIoOutStream, 0)
	ZEND_ARG_TYPE_INFO(1, out_latency, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_outstream_set_volume, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, outstream, SoundIoOutStream, 0)
	ZEND_ARG_TYPE_INFO(0, volume, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_instream_create, 0, 1, SoundIoInStream, 1)
	ZEND_ARG_OBJ_INFO(0, device, SoundIoDevice, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_instream_destroy, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, instream, SoundIoInStream, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_instream_open, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, instream, SoundIoInStream, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_instream_start arginfo_soundio_instream_open

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_instream_begin_read, 0, 3, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, instream, SoundIoInStream, 0)
	ZEND_ARG_TYPE_INFO(1, areas, IS_ARRAY, 1)
	ZEND_ARG_TYPE_INFO(1, frame_count, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_instream_end_read arginfo_soundio_instream_open

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_instream_pause, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, instream, SoundIoInStream, 0)
	ZEND_ARG_TYPE_INFO(0, pause, _IS_BOOL, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_instream_get_latency, 0, 2, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, instream, SoundIoInStream, 0)
	ZEND_ARG_TYPE_INFO(1, out_latency, IS_DOUBLE, 1)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_soundio_ring_buffer_create, 0, 2, SoundIoRingBuffer, 1)
	ZEND_ARG_OBJ_INFO(0, soundio, SoundIo, 0)
	ZEND_ARG_TYPE_INFO(0, requested_capacity, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_ring_buffer_destroy, 0, 1, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, ring_buffer, SoundIoRingBuffer, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_ring_buffer_capacity, 0, 1, IS_LONG, 0)
	ZEND_ARG_OBJ_INFO(0, ring_buffer, SoundIoRingBuffer, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_ring_buffer_write_ptr arginfo_soundio_ring_buffer_capacity

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_ring_buffer_advance_write_ptr, 0, 2, IS_VOID, 0)
	ZEND_ARG_OBJ_INFO(0, ring_buffer, SoundIoRingBuffer, 0)
	ZEND_ARG_TYPE_INFO(0, count, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_ring_buffer_read_ptr arginfo_soundio_ring_buffer_capacity

#define arginfo_soundio_ring_buffer_advance_read_ptr arginfo_soundio_ring_buffer_advance_write_ptr

#define arginfo_soundio_ring_buffer_fill_count arginfo_soundio_ring_buffer_capacity

#define arginfo_soundio_ring_buffer_free_count arginfo_soundio_ring_buffer_capacity

#define arginfo_soundio_ring_buffer_clear arginfo_soundio_ring_buffer_destroy

ZEND_FUNCTION(soundio_outstream_create);
ZEND_FUNCTION(soundio_outstream_destroy);
ZEND_FUNCTION(soundio_outstream_open);
ZEND_FUNCTION(soundio_outstream_start);
ZEND_FUNCTION(soundio_outstream_begin_write);
ZEND_FUNCTION(soundio_outstream_end_write);
ZEND_FUNCTION(soundio_outstream_clear_buffer);
ZEND_FUNCTION(soundio_outstream_pause);
ZEND_FUNCTION(soundio_outstream_get_latency);
ZEND_FUNCTION(soundio_outstream_set_volume);
ZEND_FUNCTION(soundio_instream_create);
ZEND_FUNCTION(soundio_instream_destroy);
ZEND_FUNCTION(soundio_instream_open);
ZEND_FUNCTION(soundio_instream_start);
ZEND_FUNCTION(soundio_instream_begin_read);
ZEND_FUNCTION(soundio_instream_end_read);
ZEND_FUNCTION(soundio_instream_pause);
ZEND_FUNCTION(soundio_instream_get_latency);
ZEND_FUNCTION(soundio_ring_buffer_create);
ZEND_FUNCTION(soundio_ring_buffer_destroy);
ZEND_FUNCTION(soundio_ring_buffer_capacity);
ZEND_FUNCTION(soundio_ring_buffer_write_ptr);
ZEND_FUNCTION(soundio_ring_buffer_advance_write_ptr);
ZEND_FUNCTION(soundio_ring_buffer_read_ptr);
ZEND_FUNCTION(soundio_ring_buffer_advance_read_ptr);
ZEND_FUNCTION(soundio_ring_buffer_fill_count);
ZEND_FUNCTION(soundio_ring_buffer_free_count);
ZEND_FUNCTION(soundio_ring_buffer_clear);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(soundio_outstream_create, arginfo_soundio_outstream_create)
	ZEND_FE(soundio_outstream_destroy, arginfo_soundio_outstream_destroy)
	ZEND_FE(soundio_outstream_open, arginfo_soundio_outstream_open)
	ZEND_FE(soundio_outstream_start, arginfo_soundio_outstream_start)
	ZEND_FE(soundio_outstream_begin_write, arginfo_soundio_outstream_begin_write)
	ZEND_FE(soundio_outstream_end_write, arginfo_soundio_outstream_end_write)
	ZEND_FE(soundio_outstream_clear_buffer, arginfo_soundio_outstream_clear_buffer)
	ZEND_FE(soundio_outstream_pause, arginfo_soundio_outstream_pause)
	ZEND_FE(soundio_outstream_get_latency, arginfo_soundio_outstream_get_latency)
	ZEND_FE(soundio_outstream_set_volume, arginfo_soundio_outstream_set_volume)
	ZEND_FE(soundio_instream_create, arginfo_soundio_instream_create)
	ZEND_FE(soundio_instream_destroy, arginfo_soundio_instream_destroy)
	ZEND_FE(soundio_instream_open, arginfo_soundio_instream_open)
	ZEND_FE(soundio_instream_start, arginfo_soundio_instream_start)
	ZEND_FE(soundio_instream_begin_read, arginfo_soundio_instream_begin_read)
	ZEND_FE(soundio_instream_end_read, arginfo_soundio_instream_end_read)
	ZEND_FE(soundio_instream_pause, arginfo_soundio_instream_pause)
	ZEND_FE(soundio_instream_get_latency, arginfo_soundio_instream_get_latency)
	ZEND_FE(soundio_ring_buffer_create, arginfo_soundio_ring_buffer_create)
	ZEND_FE(soundio_ring_buffer_destroy, arginfo_soundio_ring_buffer_destroy)
	ZEND_FE(soundio_ring_buffer_capacity, arginfo_soundio_ring_buffer_capacity)
	ZEND_FE(soundio_ring_buffer_write_ptr, arginfo_soundio_ring_buffer_write_ptr)
	ZEND_FE(soundio_ring_buffer_advance_write_ptr, arginfo_soundio_ring_buffer_advance_write_ptr)
	ZEND_FE(soundio_ring_buffer_read_ptr, arginfo_soundio_ring_buffer_read_ptr)
	ZEND_FE(soundio_ring_buffer_advance_read_ptr, arginfo_soundio_ring_buffer_advance_read_ptr)
	ZEND_FE(soundio_ring_buffer_fill_count, arginfo_soundio_ring_buffer_fill_count)
	ZEND_FE(soundio_ring_buffer_free_count, arginfo_soundio_ring_buffer_free_count)
	ZEND_FE(soundio_ring_buffer_clear, arginfo_soundio_ring_buffer_clear)
	ZEND_FE_END
};
