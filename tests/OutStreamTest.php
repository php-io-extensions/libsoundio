<?php

declare(strict_types=1);

/*
 * No test starts a stream: write_callback is an address, and starting a stream whose
 * write_callback is 0 crashes libsoundio's audio thread (tests/Probes). soundio_outstream_set_volume
 * is not called either: the dummy backend has no volume, and libsoundio calls through NULL.
 */

it('creates an outstream on a device, fields zeroed as libsoundio leaves them', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);

    expect($out->device)->toBe($device)
        ->and($out->format)->toBe(SoundIoFormatInvalid)
        ->and($out->sample_rate)->toBe(0)
        ->and($out->write_callback)->toBe(0)
        ->and($out->underflow_callback)->not->toBe(0)
        ->and($out->error_callback)->not->toBe(0)
        ->and($out->name)->toBeNull()
        ->and($out->layout->channel_count)->toBe(0);

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('opens with the fields the script wrote', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);
    $out->format = SoundIoFormatFloat32NE;
    $out->sample_rate = 48000;
    $out->name = 'ext-libsoundio test';

    expect(soundio_outstream_open($out))->toBe(SoundIoErrorNone)
        ->and($out->format)->toBe(SoundIoFormatFloat32NE)
        ->and($out->sample_rate)->toBe(48000)
        ->and($out->name)->toBe('ext-libsoundio test')
        ->and($out->layout->name)->toBe('Stereo')
        ->and($out->layout->channel_count)->toBe(2)
        ->and($out->bytes_per_frame)->toBe(8)
        ->and($out->bytes_per_sample)->toBe(4)
        ->and($out->layout_error)->toBe(SoundIoErrorNone)
        ->and($out->software_latency)->toBe(1.024);

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('takes a layout written before open', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);
    $out->format = SoundIoFormatS16NE;
    $out->sample_rate = 44100;
    $out->layout = soundio_channel_layout_get_default(1);

    expect(soundio_outstream_open($out))->toBe(SoundIoErrorNone)
        ->and($out->layout->name)->toBe('Mono')
        ->and($out->bytes_per_frame)->toBe(2);

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('reports latency, clears and pauses an opened stream', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);
    $out->format = SoundIoFormatFloat32NE;
    soundio_outstream_open($out);

    expect(soundio_outstream_get_latency($out, $latency))->toBe(SoundIoErrorNone)
        ->and($latency)->toBe(0.0)
        ->and(soundio_outstream_clear_buffer($out))->toBe(SoundIoErrorNone)
        ->and(soundio_outstream_pause($out, true))->toBe(SoundIoErrorNone);

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('passes begin_write through on a stream that was never started', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);
    $out->format = SoundIoFormatFloat32NE;
    soundio_outstream_open($out);
    $frames = 16;

    expect(soundio_outstream_begin_write($out, $areas, $frames))->toBe(SoundIoErrorInvalid)
        ->and($areas)->toBeNull();

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('passes a field written after open through', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);
    $out->format = SoundIoFormatFloat32NE;
    soundio_outstream_open($out);
    $out->sample_rate = 1;

    expect($out->sample_rate)->toBe(1);

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('keeps the address fields as written', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);
    $out->userdata = 0x1234;
    $out->underflow_callback = 0;

    expect($out->userdata)->toBe(0x1234)
        ->and($out->underflow_callback)->toBe(0);

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('releases the handle on soundio_outstream_destroy', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);
    soundio_outstream_destroy($out);

    expect($out->pointer())->toBe(0);

    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('does not write the fields libsoundio fills', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    $out = soundio_outstream_create($device);

    expect(fn () => $out->bytes_per_frame = 4)->toThrow(Error::class);

    soundio_outstream_destroy($out);
    soundio_device_unref($device);
    soundio_destroy($soundio);
});
