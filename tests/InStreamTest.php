<?php

declare(strict_types=1);

/* No test starts a stream: read_callback is an address, 0 unless a native callback is set. */

it('creates an instream on a device, fields zeroed as libsoundio leaves them', function (): void {
    $soundio = dummy();
    $device = soundio_get_input_device($soundio, 0);
    $in = soundio_instream_create($device);

    expect($in->device)->toBe($device)
        ->and($in->format)->toBe(SoundIoFormatInvalid)
        ->and($in->read_callback)->toBe(0)
        ->and($in->overflow_callback)->not->toBe(0)
        ->and($in->error_callback)->not->toBe(0)
        ->and($in->name)->toBeNull();

    soundio_instream_destroy($in);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('opens with the fields the script wrote, then reports latency and pauses', function (): void {
    $soundio = dummy();
    $device = soundio_get_input_device($soundio, 0);
    $in = soundio_instream_create($device);
    $in->format = SoundIoFormatFloat32NE;

    expect(soundio_instream_open($in))->toBe(SoundIoErrorNone)
        ->and($in->sample_rate)->toBe(48000)
        ->and($in->layout->name)->toBe('Stereo')
        ->and($in->bytes_per_frame)->toBe(8)
        ->and($in->bytes_per_sample)->toBe(4)
        ->and(soundio_instream_get_latency($in, $latency))->toBe(SoundIoErrorNone)
        ->and($latency)->toBe(0.0)
        ->and(soundio_instream_pause($in, true))->toBe(SoundIoErrorNone);

    soundio_instream_destroy($in);
    expect($in->pointer())->toBe(0);

    soundio_device_unref($device);
    soundio_destroy($soundio);
});
