<?php

declare(strict_types=1);

$littleEndian = pack('S', 1) === "\x01\x00";

it('registers SOUNDIO_MAX_CHANNELS and the error, backend and aim enumerators', function (): void {
    expect(SOUNDIO_MAX_CHANNELS)->toBe(24)
        ->and(SoundIoErrorNone)->toBe(0)
        ->and(SoundIoBackendNone)->toBe(0)
        ->and(SoundIoBackendDummy)->toBeInt()
        ->and(SoundIoDeviceAimInput)->toBe(0)
        ->and(SoundIoDeviceAimOutput)->toBe(1)
        ->and(SoundIoFormatInvalid)->toBe(0)
        ->and(SoundIoChannelIdInvalid)->toBe(0)
        ->and(SoundIoChannelLayoutIdMono)->toBe(0);
});

it('maps the native-endian and foreign-endian format aliases to this machine', function () use ($littleEndian): void {
    expect(SoundIoFormatFloat32NE)->toBe($littleEndian ? SoundIoFormatFloat32LE : SoundIoFormatFloat32BE)
        ->and(SoundIoFormatFloat32FE)->toBe($littleEndian ? SoundIoFormatFloat32BE : SoundIoFormatFloat32LE)
        ->and(SoundIoFormatS16NE)->toBe($littleEndian ? SoundIoFormatS16LE : SoundIoFormatS16BE)
        ->and(SoundIoFormatU32FE)->toBe($littleEndian ? SoundIoFormatU32BE : SoundIoFormatU32LE)
        ->and(SoundIoFormatFloat64NE)->toBe($littleEndian ? SoundIoFormatFloat64LE : SoundIoFormatFloat64BE);
});
