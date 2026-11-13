<?php

declare(strict_types=1);

/* Dummy backend only: its devices make no sound and capture silence. */

it('hands out the two bridge callbacks as native addresses', function (): void {
    expect(SoundIoRingBufferBridge::writeCallback())->toBeGreaterThan(0)
        ->and(SoundIoRingBufferBridge::readCallback())->toBeGreaterThan(0)
        ->and(SoundIoRingBufferBridge::readCallback())->not->toBe(SoundIoRingBufferBridge::writeCallback())
        ->and((new ReflectionClass(SoundIoRingBufferBridge::class))->getExtensionName())->toBe('libsoundio');
});

it('fills a ring from a started instream and drains it through a started outstream', function (): void {
    $soundio = dummy();
    $input = soundio_get_input_device($soundio, 0);
    $output = soundio_get_output_device($soundio, 0);
    $ring = soundio_ring_buffer_create($soundio, 48000 * 8);

    $in = soundio_instream_create($input);
    $in->format = SoundIoFormatFloat32NE;
    $in->userdata = $ring->pointer();
    $in->read_callback = SoundIoRingBufferBridge::readCallback();
    expect(soundio_instream_open($in))->toBe(SoundIoErrorNone)
        ->and(soundio_instream_start($in))->toBe(SoundIoErrorNone);

    $filled = 0;
    $until = microtime(true) + 2.0;
    while (($filled = soundio_ring_buffer_fill_count($ring)) < 4800 * 8 && microtime(true) < $until) {
        usleep(10_000);
    }
    soundio_instream_destroy($in);
    expect($filled)->toBeGreaterThanOrEqual(4800 * 8)
        ->and($filled % 8)->toBe(0);

    $out = soundio_outstream_create($output);
    $out->format = SoundIoFormatFloat32NE;
    $out->userdata = $ring->pointer();
    $out->write_callback = SoundIoRingBufferBridge::writeCallback();
    expect(soundio_outstream_open($out))->toBe(SoundIoErrorNone)
        ->and(soundio_outstream_start($out))->toBe(SoundIoErrorNone);

    $left = $filled;
    $until = microtime(true) + 2.0;
    while (($left = soundio_ring_buffer_fill_count($ring)) > 0 && microtime(true) < $until) {
        usleep(10_000);
    }
    // Empty, the bridge keeps the stream fed with silence.
    usleep(50_000);
    soundio_outstream_destroy($out);

    expect($left)->toBe(0)
        ->and(soundio_ring_buffer_fill_count($ring))->toBe(0);

    soundio_ring_buffer_destroy($ring);
    soundio_device_unref($input);
    soundio_device_unref($output);
    soundio_destroy($soundio);
});
