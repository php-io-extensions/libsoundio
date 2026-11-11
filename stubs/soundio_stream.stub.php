<?php

/** @generate-class-entries */

/*
 * gen_stub.php declarations: PHP syntax needs a `{}` after each signature, and gen_stub turns each
 * one into arginfo. The implementations are the PHP_FUNCTIONs of the same name in src/stream.c.
 *
 * Every function is the soundio.h function of the same name. An out-parameter is by reference.
 * soundio.h documents begin_write/end_write and begin_read/end_read for use inside the stream's
 * callback, which runs on libsoundio's audio thread; PHP calls them on its own thread.
 */

/* Output streams */

function soundio_outstream_create(SoundIoDevice $device): ?SoundIoOutStream {}

function soundio_outstream_destroy(SoundIoOutStream $outstream): void {}

function soundio_outstream_open(SoundIoOutStream $outstream): int {}

function soundio_outstream_start(SoundIoOutStream $outstream): int {}

/**
 * $frame_count goes in as the frames wanted and comes back as the frames granted; $areas comes
 * back as one SoundIoChannelArea per channel of $outstream->layout.
 */
function soundio_outstream_begin_write(SoundIoOutStream $outstream, ?array &$areas, int &$frame_count): int {}

function soundio_outstream_end_write(SoundIoOutStream $outstream): int {}

function soundio_outstream_clear_buffer(SoundIoOutStream $outstream): int {}

function soundio_outstream_pause(SoundIoOutStream $outstream, bool $pause): int {}

function soundio_outstream_get_latency(SoundIoOutStream $outstream, ?float &$out_latency): int {}

function soundio_outstream_set_volume(SoundIoOutStream $outstream, float $volume): int {}

/* Input streams */

function soundio_instream_create(SoundIoDevice $device): ?SoundIoInStream {}

function soundio_instream_destroy(SoundIoInStream $instream): void {}

function soundio_instream_open(SoundIoInStream $instream): int {}

function soundio_instream_start(SoundIoInStream $instream): int {}

/**
 * $frame_count goes in as the frames wanted and comes back as the frames granted; $areas comes
 * back as one SoundIoChannelArea per channel of $instream->layout, or null for a hole.
 */
function soundio_instream_begin_read(SoundIoInStream $instream, ?array &$areas, int &$frame_count): int {}

function soundio_instream_end_read(SoundIoInStream $instream): int {}

function soundio_instream_pause(SoundIoInStream $instream, bool $pause): int {}

function soundio_instream_get_latency(SoundIoInStream $instream, ?float &$out_latency): int {}

/* Ring buffers */

function soundio_ring_buffer_create(SoundIo $soundio, int $requested_capacity): ?SoundIoRingBuffer {}

function soundio_ring_buffer_destroy(SoundIoRingBuffer $ring_buffer): void {}

function soundio_ring_buffer_capacity(SoundIoRingBuffer $ring_buffer): int {}

/** The char* address writing continues at. */
function soundio_ring_buffer_write_ptr(SoundIoRingBuffer $ring_buffer): int {}

function soundio_ring_buffer_advance_write_ptr(SoundIoRingBuffer $ring_buffer, int $count): void {}

/** The char* address reading continues at. */
function soundio_ring_buffer_read_ptr(SoundIoRingBuffer $ring_buffer): int {}

function soundio_ring_buffer_advance_read_ptr(SoundIoRingBuffer $ring_buffer, int $count): void {}

function soundio_ring_buffer_fill_count(SoundIoRingBuffer $ring_buffer): int {}

function soundio_ring_buffer_free_count(SoundIoRingBuffer $ring_buffer): int {}

function soundio_ring_buffer_clear(SoundIoRingBuffer $ring_buffer): void {}
