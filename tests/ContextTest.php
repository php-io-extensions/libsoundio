<?php

declare(strict_types=1);

it('knows the dummy backend before connecting', function (): void {
    expect(soundio_have_backend(SoundIoBackendDummy))->toBeTrue()
        ->and(soundio_backend_name(SoundIoBackendDummy))->toBe('Dummy')
        ->and(soundio_strerror(SoundIoErrorNone))->toBe('(no error)');
});

it('connects to the dummy backend with one output and one input device', function (): void {
    $soundio = dummy();

    expect($soundio->current_backend)->toBe(SoundIoBackendDummy)
        ->and($soundio->app_name)->toBe('SoundIo')
        ->and(soundio_output_device_count($soundio))->toBe(1)
        ->and(soundio_input_device_count($soundio))->toBe(1)
        ->and(soundio_default_output_device_index($soundio))->toBe(0)
        ->and(soundio_default_input_device_index($soundio))->toBe(0)
        ->and(soundio_backend_count($soundio))->toBeGreaterThanOrEqual(1)
        ->and(soundio_get_backend($soundio, soundio_backend_count($soundio) - 1))->toBe(SoundIoBackendDummy);

    soundio_destroy($soundio);
});

it('returns the same SoundIo object for the same context', function (): void {
    $soundio = dummy();

    expect(SoundIo::fromPointer($soundio->pointer()))->toBe($soundio);

    soundio_destroy($soundio);
});

it('releases the handle on soundio_destroy', function (): void {
    $soundio = soundio_create();
    soundio_destroy($soundio);

    expect($soundio->pointer())->toBe(0);
});

it('writes app_name into the native struct', function (): void {
    $soundio = soundio_create();
    $soundio->app_name = 'ext-libsoundio test';

    expect($soundio->app_name)->toBe('ext-libsoundio test');

    soundio_destroy($soundio);
});

it('disconnects back to no backend', function (): void {
    $soundio = dummy();
    soundio_disconnect($soundio);

    expect($soundio->current_backend)->toBe(SoundIoBackendNone);

    soundio_destroy($soundio);
});

it('returns from flush, wakeup and a forced scan', function (): void {
    $soundio = dummy();
    soundio_force_device_scan($soundio);
    soundio_wakeup($soundio);
    soundio_flush_events($soundio);

    expect(soundio_output_device_count($soundio))->toBe(1);

    soundio_destroy($soundio);
});
