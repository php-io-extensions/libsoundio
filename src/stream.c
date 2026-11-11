/*
 * Output streams, input streams and ring buffers: stubs/soundio_stream.stub.php. Each function
 * calls the soundio.h function of the same name with its arguments as given.
 */
#include "runtime.h"
#include "../stubs/soundio_stream_arginfo.h"

#define OUT_ARG(var, zv) LIBSOUNDIO_ARG(struct SoundIoOutStream, var, zv, 1)
#define IN_ARG(var, zv) LIBSOUNDIO_ARG(struct SoundIoInStream, var, zv, 1)
#define RING_ARG(var, zv) LIBSOUNDIO_ARG(struct SoundIoRingBuffer, var, zv, 1)

/* areas[0..channel_count) as a list of SoundIoChannelArea into the by-reference zarea; null for NULL areas. */
static void libsoundio_areas_out(zval *zareas, struct SoundIoChannelArea *areas, int channel_count)
{
	zval list, area;

	if (areas == NULL) {
		ZEND_TRY_ASSIGN_REF_NULL(zareas);
		return;
	}
	array_init_size(&list, (uint32_t) (channel_count > 0 ? channel_count : 0));
	for (int i = 0; i < channel_count; i++) {
		object_init_ex(&area, libsoundio_ce_SoundIoChannelArea);
		zend_update_property_long(libsoundio_ce_SoundIoChannelArea, Z_OBJ(area), "ptr", sizeof("ptr") - 1, (zend_long) (uintptr_t) areas[i].ptr);
		zend_update_property_long(libsoundio_ce_SoundIoChannelArea, Z_OBJ(area), "step", sizeof("step") - 1, areas[i].step);
		add_next_index_zval(&list, &area);
	}
	ZEND_TRY_ASSIGN_REF_ARR(zareas, Z_ARR(list));
}

/* Output streams */

PHP_FUNCTION(soundio_outstream_create)
{
	zval *zd;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
	ZEND_PARSE_PARAMETERS_END();

	LIBSOUNDIO_ARG(struct SoundIoDevice, d, zd, 1);
	libsoundio_box(return_value, soundio_outstream_create(d), libsoundio_ce_SoundIoOutStream);
}

PHP_FUNCTION(soundio_outstream_destroy)
{
	zval *zo;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
	ZEND_PARSE_PARAMETERS_END();

	struct SoundIoOutStream *o = LIBSOUNDIO_PTR(zo);

	/* libsoundio takes NULL as a no-op. */
	if (o != NULL) {
		libsoundio_keep_drop(&o->name);
		libsoundio_keep_drop(&o->layout.name);
	}
	soundio_outstream_destroy(o);
	libsoundio_release(o);
}

PHP_FUNCTION(soundio_outstream_open)
{
	zval *zo;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	RETURN_LONG(soundio_outstream_open(o));
}

PHP_FUNCTION(soundio_outstream_start)
{
	zval *zo;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	/* libsoundio's audio thread calls write_callback without checking it. */
	if (!LIBSOUNDIO_PROBE_OFF("libsoundio-null-write-callback") && o->write_callback == NULL) {
		zend_argument_value_error(1, "has no write_callback: libsoundio's audio thread would call NULL"); /* binding:libsoundio-null-write-callback */
		RETURN_THROWS();
	}
	RETURN_LONG(soundio_outstream_start(o));
}

PHP_FUNCTION(soundio_outstream_begin_write)
{
	zval *zo, *zareas, *zframes;
	struct SoundIoChannelArea *areas = NULL;
	int frame_count, err;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
		Z_PARAM_ZVAL(zareas)
		Z_PARAM_ZVAL(zframes)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	frame_count = (int) zval_get_long(Z_REFVAL_P(zframes));
	err = soundio_outstream_begin_write(o, &areas, &frame_count);
	ZEND_TRY_ASSIGN_REF_LONG(zframes, frame_count);
	libsoundio_areas_out(zareas, areas, o != NULL ? o->layout.channel_count : 0);
	RETURN_LONG(err);
}

PHP_FUNCTION(soundio_outstream_end_write)
{
	zval *zo;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	RETURN_LONG(soundio_outstream_end_write(o));
}

PHP_FUNCTION(soundio_outstream_clear_buffer)
{
	zval *zo;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	RETURN_LONG(soundio_outstream_clear_buffer(o));
}

PHP_FUNCTION(soundio_outstream_pause)
{
	zval *zo;
	bool pause;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
		Z_PARAM_BOOL(pause)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	RETURN_LONG(soundio_outstream_pause(o, pause));
}

PHP_FUNCTION(soundio_outstream_get_latency)
{
	zval *zo, *zlatency;
	double latency = 0.0;
	int err;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
		Z_PARAM_ZVAL(zlatency)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	err = soundio_outstream_get_latency(o, &latency);
	ZEND_TRY_ASSIGN_REF_DOUBLE(zlatency, latency);
	RETURN_LONG(err);
}

PHP_FUNCTION(soundio_outstream_set_volume)
{
	zval *zo;
	double volume;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zo, libsoundio_ce_SoundIoOutStream)
		Z_PARAM_DOUBLE(volume)
	ZEND_PARSE_PARAMETERS_END();

	OUT_ARG(o, zo);
	/* libsoundio 2.0 calls the backend's set_volume unchecked; only CoreAudio and WASAPI have one. */
	if (!LIBSOUNDIO_PROBE_OFF("libsoundio-set-volume-unsupported") && o->device->soundio->current_backend != SoundIoBackendCoreAudio && o->device->soundio->current_backend != SoundIoBackendWasapi) {
		zend_argument_value_error(1, "is on a backend without a volume: libsoundio would call NULL"); /* binding:libsoundio-set-volume-unsupported */
		RETURN_THROWS();
	}
	RETURN_LONG(soundio_outstream_set_volume(o, volume));
}

/* Input streams */

PHP_FUNCTION(soundio_instream_create)
{
	zval *zd;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zd, libsoundio_ce_SoundIoDevice)
	ZEND_PARSE_PARAMETERS_END();

	LIBSOUNDIO_ARG(struct SoundIoDevice, d, zd, 1);
	libsoundio_box(return_value, soundio_instream_create(d), libsoundio_ce_SoundIoInStream);
}

PHP_FUNCTION(soundio_instream_destroy)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, libsoundio_ce_SoundIoInStream)
	ZEND_PARSE_PARAMETERS_END();

	struct SoundIoInStream *in = LIBSOUNDIO_PTR(zi);

	/* libsoundio takes NULL as a no-op. */
	if (in != NULL) {
		libsoundio_keep_drop(&in->name);
		libsoundio_keep_drop(&in->layout.name);
	}
	soundio_instream_destroy(in);
	libsoundio_release(in);
}

PHP_FUNCTION(soundio_instream_open)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, libsoundio_ce_SoundIoInStream)
	ZEND_PARSE_PARAMETERS_END();

	IN_ARG(in, zi);
	RETURN_LONG(soundio_instream_open(in));
}

PHP_FUNCTION(soundio_instream_start)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, libsoundio_ce_SoundIoInStream)
	ZEND_PARSE_PARAMETERS_END();

	IN_ARG(in, zi);
	/* libsoundio's audio thread calls read_callback without checking it. */
	if (!LIBSOUNDIO_PROBE_OFF("libsoundio-null-read-callback") && in->read_callback == NULL) {
		zend_argument_value_error(1, "has no read_callback: libsoundio's audio thread would call NULL"); /* binding:libsoundio-null-read-callback */
		RETURN_THROWS();
	}
	RETURN_LONG(soundio_instream_start(in));
}

PHP_FUNCTION(soundio_instream_begin_read)
{
	zval *zi, *zareas, *zframes;
	struct SoundIoChannelArea *areas = NULL;
	int frame_count, err;

	ZEND_PARSE_PARAMETERS_START(3, 3)
		Z_PARAM_OBJECT_OF_CLASS(zi, libsoundio_ce_SoundIoInStream)
		Z_PARAM_ZVAL(zareas)
		Z_PARAM_ZVAL(zframes)
	ZEND_PARSE_PARAMETERS_END();

	IN_ARG(in, zi);
	frame_count = (int) zval_get_long(Z_REFVAL_P(zframes));
	err = soundio_instream_begin_read(in, &areas, &frame_count);
	ZEND_TRY_ASSIGN_REF_LONG(zframes, frame_count);
	libsoundio_areas_out(zareas, areas, in != NULL ? in->layout.channel_count : 0);
	RETURN_LONG(err);
}

PHP_FUNCTION(soundio_instream_end_read)
{
	zval *zi;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zi, libsoundio_ce_SoundIoInStream)
	ZEND_PARSE_PARAMETERS_END();

	IN_ARG(in, zi);
	RETURN_LONG(soundio_instream_end_read(in));
}

PHP_FUNCTION(soundio_instream_pause)
{
	zval *zi;
	bool pause;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, libsoundio_ce_SoundIoInStream)
		Z_PARAM_BOOL(pause)
	ZEND_PARSE_PARAMETERS_END();

	IN_ARG(in, zi);
	RETURN_LONG(soundio_instream_pause(in, pause));
}

PHP_FUNCTION(soundio_instream_get_latency)
{
	zval *zi, *zlatency;
	double latency = 0.0;
	int err;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zi, libsoundio_ce_SoundIoInStream)
		Z_PARAM_ZVAL(zlatency)
	ZEND_PARSE_PARAMETERS_END();

	IN_ARG(in, zi);
	err = soundio_instream_get_latency(in, &latency);
	ZEND_TRY_ASSIGN_REF_DOUBLE(zlatency, latency);
	RETURN_LONG(err);
}

/* Ring buffers */

PHP_FUNCTION(soundio_ring_buffer_create)
{
	zval *zs;
	zend_long requested_capacity;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zs, libsoundio_ce_SoundIo)
		Z_PARAM_LONG(requested_capacity)
	ZEND_PARSE_PARAMETERS_END();

	libsoundio_box(return_value, soundio_ring_buffer_create(LIBSOUNDIO_PTR(zs), (int) requested_capacity), libsoundio_ce_SoundIoRingBuffer);
}

PHP_FUNCTION(soundio_ring_buffer_destroy)
{
	zval *zr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
	ZEND_PARSE_PARAMETERS_END();

	struct SoundIoRingBuffer *rb = LIBSOUNDIO_PTR(zr);

	/* libsoundio takes NULL as a no-op. */
	soundio_ring_buffer_destroy(rb);
	libsoundio_release(rb);
}

PHP_FUNCTION(soundio_ring_buffer_capacity)
{
	zval *zr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	RETURN_LONG(soundio_ring_buffer_capacity(rb));
}

PHP_FUNCTION(soundio_ring_buffer_write_ptr)
{
	zval *zr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	RETURN_LONG((zend_long) (uintptr_t) soundio_ring_buffer_write_ptr(rb));
}

PHP_FUNCTION(soundio_ring_buffer_advance_write_ptr)
{
	zval *zr;
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	soundio_ring_buffer_advance_write_ptr(rb, (int) count);
}

PHP_FUNCTION(soundio_ring_buffer_read_ptr)
{
	zval *zr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	RETURN_LONG((zend_long) (uintptr_t) soundio_ring_buffer_read_ptr(rb));
}

PHP_FUNCTION(soundio_ring_buffer_advance_read_ptr)
{
	zval *zr;
	zend_long count;

	ZEND_PARSE_PARAMETERS_START(2, 2)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
		Z_PARAM_LONG(count)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	soundio_ring_buffer_advance_read_ptr(rb, (int) count);
}

PHP_FUNCTION(soundio_ring_buffer_fill_count)
{
	zval *zr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	RETURN_LONG(soundio_ring_buffer_fill_count(rb));
}

PHP_FUNCTION(soundio_ring_buffer_free_count)
{
	zval *zr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	RETURN_LONG(soundio_ring_buffer_free_count(rb));
}

PHP_FUNCTION(soundio_ring_buffer_clear)
{
	zval *zr;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(zr, libsoundio_ce_SoundIoRingBuffer)
	ZEND_PARSE_PARAMETERS_END();

	RING_ARG(rb, zr);
	soundio_ring_buffer_clear(rb);
}

void libsoundio_register_stream(void)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}
