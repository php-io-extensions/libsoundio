<?php

/** @generate-class-entries */

/*
 * gen_stub.php declarations: PHP syntax needs a `{}` after each signature, and gen_stub turns each
 * one into arginfo. The implementations are the PHP_FUNCTIONs of the same name in src/soundio.c.
 *
 * Every function is the soundio.h function of the same name. A list stands for a C array and its
 * count stays its own parameter after it. A returned const struct SoundIoChannelLayout * is a copy.
 */

/* Context */

function soundio_create(): ?SoundIo {}

function soundio_destroy(SoundIo $soundio): void {}

function soundio_connect(SoundIo $soundio): int {}

function soundio_connect_backend(SoundIo $soundio, int $backend): int {}

function soundio_disconnect(SoundIo $soundio): void {}

function soundio_strerror(int $error): string {}

function soundio_backend_name(int $backend): string {}

function soundio_backend_count(SoundIo $soundio): int {}

function soundio_get_backend(SoundIo $soundio, int $index): int {}

function soundio_have_backend(int $backend): bool {}

function soundio_flush_events(SoundIo $soundio): void {}

function soundio_wait_events(SoundIo $soundio): void {}

function soundio_wakeup(SoundIo $soundio): void {}

function soundio_force_device_scan(SoundIo $soundio): void {}

/* Channel layouts */

function soundio_channel_layout_equal(SoundIoChannelLayout $a, SoundIoChannelLayout $b): bool {}

function soundio_get_channel_name(int $id): string {}

function soundio_parse_channel_id(string $str, int $str_len): int {}

function soundio_channel_layout_builtin_count(): int {}

function soundio_channel_layout_get_builtin(int $index): ?SoundIoChannelLayout {}

function soundio_channel_layout_get_default(int $channel_count): ?SoundIoChannelLayout {}

function soundio_channel_layout_find_channel(SoundIoChannelLayout $layout, int $channel): int {}

/** Writes the builtin layout's name into $layout->name when it matches one. */
function soundio_channel_layout_detect_builtin(SoundIoChannelLayout $layout): bool {}

/** $preferred_layouts and $available_layouts are lists of SoundIoChannelLayout. */
function soundio_best_matching_channel_layout(array $preferred_layouts, int $preferred_layout_count, array $available_layouts, int $available_layout_count): ?SoundIoChannelLayout {}

/** $layouts is a list of SoundIoChannelLayout, sorted in place. */
function soundio_sort_channel_layouts(array &$layouts, int $layout_count): void {}

/* Formats */

function soundio_get_bytes_per_sample(int $format): int {}

function soundio_format_string(int $format): string {}

/* Devices */

function soundio_input_device_count(SoundIo $soundio): int {}

function soundio_output_device_count(SoundIo $soundio): int {}

function soundio_get_input_device(SoundIo $soundio, int $index): ?SoundIoDevice {}

function soundio_get_output_device(SoundIo $soundio, int $index): ?SoundIoDevice {}

function soundio_default_input_device_index(SoundIo $soundio): int {}

function soundio_default_output_device_index(SoundIo $soundio): int {}

function soundio_device_ref(SoundIoDevice $device): void {}

function soundio_device_unref(SoundIoDevice $device): void {}

function soundio_device_equal(SoundIoDevice $a, SoundIoDevice $b): bool {}

function soundio_device_sort_channel_layouts(SoundIoDevice $device): void {}

function soundio_device_supports_format(SoundIoDevice $device, int $format): bool {}

function soundio_device_supports_layout(SoundIoDevice $device, SoundIoChannelLayout $layout): bool {}

function soundio_device_supports_sample_rate(SoundIoDevice $device, int $sample_rate): bool {}

function soundio_device_nearest_sample_rate(SoundIoDevice $device, int $sample_rate): int {}
