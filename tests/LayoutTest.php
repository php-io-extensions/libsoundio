<?php

declare(strict_types=1);

function stereo(): SoundIoChannelLayout
{
    $layout = new SoundIoChannelLayout();
    $layout->channel_count = 2;
    $layout->channels = [SoundIoChannelIdFrontLeft, SoundIoChannelIdFrontRight];

    return $layout;
}

it('copies the builtin layouts', function (): void {
    $mono = soundio_channel_layout_get_builtin(0);

    expect(soundio_channel_layout_builtin_count())->toBe(26)
        ->and($mono->name)->toBe('Mono')
        ->and($mono->channel_count)->toBe(1)
        ->and($mono->channels)->toBe([SoundIoChannelIdFrontCenter]);
});

it('gives the default layout for a channel count, or null', function (): void {
    expect(soundio_channel_layout_get_default(2)->name)->toBe('Stereo')
        ->and(soundio_channel_layout_get_default(1)->name)->toBe('Mono')
        ->and(soundio_channel_layout_get_default(99))->toBeNull();
});

it('finds a channel in a layout', function (): void {
    expect(soundio_channel_layout_find_channel(stereo(), SoundIoChannelIdFrontRight))->toBe(1)
        ->and(soundio_channel_layout_find_channel(stereo(), SoundIoChannelIdLfe))->toBe(-1);
});

it('compares layouts by channels', function (): void {
    expect(soundio_channel_layout_equal(stereo(), soundio_channel_layout_get_default(2)))->toBeTrue()
        ->and(soundio_channel_layout_equal(stereo(), soundio_channel_layout_get_default(1)))->toBeFalse();
});

it('names a layout that matches a builtin one', function (): void {
    $layout = stereo();

    expect(soundio_channel_layout_detect_builtin($layout))->toBeTrue()
        ->and($layout->name)->toBe('Stereo');
});

it('picks the first preferred layout that is available', function (): void {
    $mono = soundio_channel_layout_get_default(1);
    $stereo = soundio_channel_layout_get_default(2);
    $surround = soundio_channel_layout_get_default(6);

    expect(soundio_best_matching_channel_layout([$surround, $stereo], 2, [$mono, $stereo], 2)->name)->toBe('Stereo')
        ->and(soundio_best_matching_channel_layout([$surround], 1, [$mono, $stereo], 2))->toBeNull();
});

it('sorts layouts by channel count, most first', function (): void {
    $layouts = [soundio_channel_layout_get_default(1), soundio_channel_layout_get_default(6), soundio_channel_layout_get_default(2)];
    soundio_sort_channel_layouts($layouts, 3);

    expect(array_map(fn (SoundIoChannelLayout $l): int => $l->channel_count, $layouts))->toBe([6, 2, 1]);
});
