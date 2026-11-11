<?php

declare(strict_types=1);

it('builds value structs zeroed, as C\'s {0}', function (): void {
    $layout = new SoundIoChannelLayout();
    $range = new SoundIoSampleRateRange();
    $area = new SoundIoChannelArea();

    expect($layout->name)->toBeNull()
        ->and($layout->channel_count)->toBe(0)
        ->and($layout->channels)->toBe([])
        ->and([$range->min, $range->max])->toBe([0, 0])
        ->and([$area->ptr, $area->step])->toBe([0, 0]);
});

it('holds what the script writes into each field', function (): void {
    $layout = new SoundIoChannelLayout();
    $layout->name = 'Stereo';
    $layout->channel_count = 2;
    $layout->channels = [SoundIoChannelIdFrontLeft, SoundIoChannelIdFrontRight];
    $range = new SoundIoSampleRateRange();
    [$range->min, $range->max] = [8000, 48000];
    $area = new SoundIoChannelArea();
    [$area->ptr, $area->step] = [4096, 8];

    expect($layout->name)->toBe('Stereo')
        ->and($layout->channel_count)->toBe(2)
        ->and($layout->channels)->toBe([SoundIoChannelIdFrontLeft, SoundIoChannelIdFrontRight])
        ->and([$range->min, $range->max])->toBe([8000, 48000])
        ->and([$area->ptr, $area->step])->toBe([4096, 8]);
});

it('gives no handle for address 0', function (string $class): void {
    expect($class::fromPointer(0))->toBeNull();
})->with(['SoundIo', 'SoundIoDevice', 'SoundIoOutStream', 'SoundIoInStream', 'SoundIoRingBuffer']);

it('does not construct a handle from PHP', function (string $class): void {
    expect(fn () => new $class())->toThrow(Error::class);
})->with(['SoundIo', 'SoundIoDevice', 'SoundIoOutStream', 'SoundIoInStream', 'SoundIoRingBuffer']);

it('keeps one PHP object per native address', function (): void {
    $address = 0x1000;

    expect(SoundIoRingBuffer::fromPointer($address))->toBe(SoundIoRingBuffer::fromPointer($address))
        ->and(SoundIoRingBuffer::fromPointer($address)->pointer())->toBe($address);
});

it('does not clone or serialize a handle', function (): void {
    $handle = SoundIoRingBuffer::fromPointer(0x2000);

    expect(fn () => clone $handle)->toThrow(Error::class)
        ->and(fn () => serialize($handle))->toThrow(Exception::class);
});
