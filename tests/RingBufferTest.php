<?php

declare(strict_types=1);

it('creates a ring buffer at least as large as requested', function (): void {
    $soundio = soundio_create();
    $ring = soundio_ring_buffer_create($soundio, 4096);

    expect(soundio_ring_buffer_capacity($ring))->toBeGreaterThanOrEqual(4096)
        ->and(soundio_ring_buffer_fill_count($ring))->toBe(0)
        ->and(soundio_ring_buffer_free_count($ring))->toBe(soundio_ring_buffer_capacity($ring));

    soundio_ring_buffer_destroy($ring);
    soundio_destroy($soundio);
});

it('moves its read and write pointers', function (): void {
    $soundio = soundio_create();
    $ring = soundio_ring_buffer_create($soundio, 4096);
    $capacity = soundio_ring_buffer_capacity($ring);

    soundio_ring_buffer_advance_write_ptr($ring, 16);
    expect(soundio_ring_buffer_fill_count($ring))->toBe(16)
        ->and(soundio_ring_buffer_free_count($ring))->toBe($capacity - 16);

    soundio_ring_buffer_advance_read_ptr($ring, 6);
    expect(soundio_ring_buffer_fill_count($ring))->toBe(10);

    soundio_ring_buffer_clear($ring);
    expect(soundio_ring_buffer_fill_count($ring))->toBe(0);

    soundio_ring_buffer_destroy($ring);
    soundio_destroy($soundio);
});

it('gives its read and write positions as addresses', function (): void {
    $soundio = soundio_create();
    $ring = soundio_ring_buffer_create($soundio, 4096);

    soundio_ring_buffer_advance_write_ptr($ring, 16);

    expect(soundio_ring_buffer_read_ptr($ring))->toBeInt()->not->toBe(0)
        ->and(soundio_ring_buffer_write_ptr($ring) - soundio_ring_buffer_read_ptr($ring))->toBe(16);

    soundio_ring_buffer_destroy($ring);
    expect($ring->pointer())->toBe(0);

    soundio_destroy($soundio);
});
