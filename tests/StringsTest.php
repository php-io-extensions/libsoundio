<?php

declare(strict_types=1);

it('names channels and parses channel names', function (): void {
    expect(soundio_get_channel_name(SoundIoChannelIdFrontLeft))->toBe('Front Left')
        ->and(soundio_parse_channel_id('Front Left', 10))->toBe(SoundIoChannelIdFrontLeft)
        ->and(soundio_parse_channel_id('bogus', 5))->toBe(SoundIoChannelIdInvalid);
});

it('names formats and sizes their samples', function (): void {
    expect(soundio_format_string(SoundIoFormatS16LE))->toBe('signed 16-bit LE')
        ->and(soundio_get_bytes_per_sample(SoundIoFormatFloat64LE))->toBe(8)
        ->and(soundio_get_bytes_per_sample(SoundIoFormatS16LE))->toBe(2);
});
