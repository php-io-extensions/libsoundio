<?php

declare(strict_types=1);

it('reads the dummy output device the way libsoundio fills it', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);

    expect($device->soundio)->toBe($soundio)
        ->and($device->id)->toBe('dummy-out')
        ->and($device->name)->toBe('Dummy Output Device')
        ->and($device->aim)->toBe(SoundIoDeviceAimOutput)
        ->and($device->ref_count)->toBe(2)
        ->and($device->is_raw)->toBeFalse()
        ->and($device->probe_error)->toBe(SoundIoErrorNone)
        ->and($device->layout_count)->toBe(26)
        ->and($device->layouts)->toHaveCount(26)
        ->and($device->layouts[0])->toBeInstanceOf(SoundIoChannelLayout::class)
        ->and($device->format_count)->toBe(18)
        ->and($device->formats)->toHaveCount(18)
        ->and($device->sample_rate_count)->toBe(1)
        ->and([$device->sample_rates[0]->min, $device->sample_rates[0]->max])->toBe([8000, 5644800])
        ->and($device->sample_rate_current)->toBe(48000)
        ->and($device->current_layout)->toBeInstanceOf(SoundIoChannelLayout::class)
        ->and($device->software_latency_min)->toBe(0.01)
        ->and($device->software_latency_max)->toBe(4.0)
        ->and($device->software_latency_current)->toBe(0.1);

    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('answers format, layout and sample rate questions', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);

    expect(soundio_device_supports_format($device, SoundIoFormatFloat32NE))->toBeTrue()
        ->and(soundio_device_supports_layout($device, soundio_channel_layout_get_default(2)))->toBeTrue()
        ->and(soundio_device_supports_sample_rate($device, 48000))->toBeTrue()
        ->and(soundio_device_nearest_sample_rate($device, 1))->toBe(8000)
        ->and(soundio_device_equal($device, $device))->toBeTrue()
        ->and(soundio_device_equal($device, soundio_get_input_device($soundio, 0)))->toBeFalse();

    soundio_device_sort_channel_layouts($device);
    expect($device->layout_count)->toBe(26);

    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('counts references with soundio_device_ref and soundio_device_unref', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    soundio_device_ref($device);

    expect($device->ref_count)->toBe(3);

    soundio_device_unref($device);
    expect($device->ref_count)->toBe(2)
        ->and($device->pointer())->not->toBe(0);

    soundio_device_unref($device);
    soundio_destroy($soundio);
});

it('releases the handle when the last reference goes', function (): void {
    $soundio = dummy();
    $device = soundio_get_output_device($soundio, 0);
    soundio_destroy($soundio);

    expect($device->ref_count)->toBe(1);

    soundio_device_unref($device);
    expect($device->pointer())->toBe(0);
});
