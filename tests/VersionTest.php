<?php

declare(strict_types=1);

it('reports libsoundio 2.0.0', function (): void {
    expect(soundio_version_string())->toBe('2.0.0')
        ->and([soundio_version_major(), soundio_version_minor(), soundio_version_patch()])->toBe([2, 0, 0])
        ->and(phpversion('libsoundio'))->toBe('0.11.0');
});
