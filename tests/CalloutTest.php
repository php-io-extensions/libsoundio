<?php

declare(strict_types=1);

it('calls on_devices_change inside soundio_flush_events with the same SoundIo object', function (): void {
    $soundio = soundio_create();
    $seen = [];
    $soundio->on_devices_change = function (SoundIo $s) use (&$seen): void {
        $seen[] = $s;
    };
    soundio_connect_backend($soundio, SoundIoBackendDummy);
    soundio_flush_events($soundio);

    expect($seen)->toHaveCount(1)
        ->and($seen[0])->toBe($soundio);

    soundio_destroy($soundio);
});

it('reads back the closure it was given, and null once cleared', function (): void {
    $soundio = soundio_create();
    $callout = fn (SoundIo $s, int $err): null => null;

    expect($soundio->on_devices_change)->toBeNull()
        ->and($soundio->on_backend_disconnect)->toBeNull();

    $soundio->on_backend_disconnect = $callout;
    expect($soundio->on_backend_disconnect)->toBe($callout);

    $soundio->on_backend_disconnect = null;
    expect($soundio->on_backend_disconnect)->toBeNull();

    soundio_destroy($soundio);
});

it('stops calling a cleared on_devices_change', function (): void {
    $soundio = soundio_create();
    $calls = 0;
    $soundio->on_devices_change = function () use (&$calls): void {
        $calls++;
    };
    $soundio->on_devices_change = null;
    soundio_connect_backend($soundio, SoundIoBackendDummy);
    soundio_flush_events($soundio);

    expect($calls)->toBe(0);

    soundio_destroy($soundio);
});

it('rethrows an exception from the callout when soundio_flush_events returns', function (): void {
    $soundio = soundio_create();
    $soundio->on_devices_change = function (): void {
        throw new RuntimeException('from the callout');
    };
    soundio_connect_backend($soundio, SoundIoBackendDummy);

    expect(fn () => soundio_flush_events($soundio))->toThrow(RuntimeException::class, 'from the callout');

    soundio_destroy($soundio);
});

it('keeps calling the callout after the script drops its SoundIo variable', function (): void {
    $calls = 0;
    $soundio = soundio_create();
    $soundio->on_devices_change = function () use (&$calls): void {
        $calls++;
    };
    $address = $soundio->pointer();
    unset($soundio);

    $again = SoundIo::fromPointer($address);
    soundio_connect_backend($again, SoundIoBackendDummy);
    soundio_flush_events($again);

    expect($calls)->toBe(1);

    soundio_destroy($again);
});

it('ends a request with a connected SoundIo and a live callout cleanly', function (): void {
    $run = libsoundioProbe(<<<'PHP'
        $soundio = soundio_create();
        $soundio->on_devices_change = function (SoundIo $s): void {};
        soundio_connect_backend($soundio, SoundIoBackendDummy);
        soundio_flush_events($soundio);
        PHP, null);

    expect($run['signal'])->toBeNull()
        ->and($run['stdout'])->toBe("SURVIVED\n");
});
