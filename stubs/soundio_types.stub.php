<?php

/** @generate-class-entries */

/*
 * gen_stub.php declarations: PHP syntax needs a `{}` after each signature, and gen_stub turns each
 * one into arginfo. The implementations are in src/types.c.
 *
 * Handles hold a native pointer. fromPointer() trusts any non-zero address it is given: the
 * extension cannot check that an address is a live libsoundio object of that type.
 *
 * A handle's properties are its C struct's public fields, read from and written to the native
 * struct on every access (src/types.c). readonly marks the fields soundio.h says libsoundio fills.
 */

/**
 * A libsoundio context. Made by soundio_create().
 * @not-serializable
 */
final class SoundIo
{
    /** void *userdata, as an address. */
    public int $userdata;

    /** Called inside soundio_flush_events() / soundio_wait_events() as fn(SoundIo $soundio): void. */
    public ?Closure $on_devices_change;

    /** Called inside soundio_flush_events() / soundio_wait_events() as fn(SoundIo $soundio, int $err): void. */
    public ?Closure $on_backend_disconnect;

    /** void (*on_events_signal)(struct SoundIo *): an address; libsoundio calls it from its own threads. */
    public int $on_events_signal;

    public readonly int $current_backend;

    public ?string $app_name;

    /** void (*emit_rtprio_warning)(void): an address. */
    public int $emit_rtprio_warning;

    /** void (*jack_info_callback)(const char *): an address; JACK calls it from its own threads. */
    public int $jack_info_callback;

    /** void (*jack_error_callback)(const char *): an address; JACK calls it from its own threads. */
    public int $jack_error_callback;

    private function __construct() {}

    /** The struct SoundIo* address; 0 once soundio_destroy() released it. */
    public function pointer(): int {}

    /** The context at a struct SoundIo* address; null for 0. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An input or output device. Made by soundio_get_input_device() / soundio_get_output_device().
 * @not-serializable
 */
final class SoundIoDevice
{
    public readonly SoundIo $soundio;

    public readonly string $id;

    public readonly string $name;

    public readonly int $aim;

    /** layout_count SoundIoChannelLayout copies. */
    public readonly array $layouts;

    public readonly int $layout_count;

    public readonly SoundIoChannelLayout $current_layout;

    /** format_count SoundIoFormat values. */
    public readonly array $formats;

    public readonly int $format_count;

    public readonly int $current_format;

    /** sample_rate_count SoundIoSampleRateRange copies. */
    public readonly array $sample_rates;

    public readonly int $sample_rate_count;

    public readonly int $sample_rate_current;

    public readonly float $software_latency_min;

    public readonly float $software_latency_max;

    public readonly float $software_latency_current;

    public readonly bool $is_raw;

    public readonly int $ref_count;

    public readonly int $probe_error;

    private function __construct() {}

    /** The struct SoundIoDevice* address; 0 once soundio_device_unref() dropped the last reference. */
    public function pointer(): int {}

    /** The device at a struct SoundIoDevice* address; null for 0. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An output stream. Made by soundio_outstream_create().
 * @not-serializable
 */
final class SoundIoOutStream
{
    public SoundIoDevice $device;

    public int $format;

    public int $sample_rate;

    public SoundIoChannelLayout $layout;

    public float $software_latency;

    public float $volume;

    /** void *userdata, as an address. */
    public int $userdata;

    /** void (*write_callback)(struct SoundIoOutStream *, int frame_count_min, int frame_count_max): an address; libsoundio calls it from the stream's audio thread. */
    public int $write_callback;

    /** void (*underflow_callback)(struct SoundIoOutStream *): an address; libsoundio calls it from the stream's audio thread. */
    public int $underflow_callback;

    /** void (*error_callback)(struct SoundIoOutStream *, int err): an address; libsoundio calls it from the stream's audio thread. */
    public int $error_callback;

    public ?string $name;

    public bool $non_terminal_hint;

    public readonly int $bytes_per_frame;

    public readonly int $bytes_per_sample;

    public readonly int $layout_error;

    private function __construct() {}

    /** The struct SoundIoOutStream* address; 0 once soundio_outstream_destroy() released it. */
    public function pointer(): int {}

    /** The stream at a struct SoundIoOutStream* address; null for 0. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * An input stream. Made by soundio_instream_create().
 * @not-serializable
 */
final class SoundIoInStream
{
    public SoundIoDevice $device;

    public int $format;

    public int $sample_rate;

    public SoundIoChannelLayout $layout;

    public float $software_latency;

    /** void *userdata, as an address. */
    public int $userdata;

    /** void (*read_callback)(struct SoundIoInStream *, int frame_count_min, int frame_count_max): an address; libsoundio calls it from the stream's audio thread. */
    public int $read_callback;

    /** void (*overflow_callback)(struct SoundIoInStream *): an address; libsoundio calls it from the stream's audio thread. */
    public int $overflow_callback;

    /** void (*error_callback)(struct SoundIoInStream *, int err): an address; libsoundio calls it from the stream's audio thread. */
    public int $error_callback;

    public ?string $name;

    public bool $non_terminal_hint;

    public readonly int $bytes_per_frame;

    public readonly int $bytes_per_sample;

    public readonly int $layout_error;

    private function __construct() {}

    /** The struct SoundIoInStream* address; 0 once soundio_instream_destroy() released it. */
    public function pointer(): int {}

    /** The stream at a struct SoundIoInStream* address; null for 0. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * A ring buffer. Made by soundio_ring_buffer_create().
 * @not-serializable
 */
final class SoundIoRingBuffer
{
    private function __construct() {}

    /** The struct SoundIoRingBuffer* address; 0 once soundio_ring_buffer_destroy() released it. */
    public function pointer(): int {}

    /** The ring buffer at a struct SoundIoRingBuffer* address; null for 0. */
    public static function fromPointer(int $pointer): ?static {}
}

/**
 * Native callbacks that join a stream to a SoundIoRingBuffer, for the stream's
 * address fields. Set the stream's userdata to the ring buffer's pointer().
 * The ring holds interleaved frames in the stream's format and layout.
 */
final class SoundIoRingBufferBridge
{
    /**
     * A write_callback: each call takes up to frame_count_max frames from the
     * ring at userdata, and writes silence (zero bytes) for whatever part of
     * frame_count_min the ring does not hold.
     */
    public static function writeCallback(): int {}

    /**
     * A read_callback: each call puts the frames the device captured into the
     * ring at userdata, as many as it has room for, and drops the rest.
     */
    public static function readCallback(): int {}
}

/** struct SoundIoChannelLayout, zeroed as C's {0}. $channels holds channel_count SoundIoChannelId values, at most SOUNDIO_MAX_CHANNELS. */
final class SoundIoChannelLayout
{
    public ?string $name = null;

    public int $channel_count = 0;

    public array $channels = [];
}

/** struct SoundIoSampleRateRange, zeroed as C's {0}. */
final class SoundIoSampleRateRange
{
    public int $min = 0;

    public int $max = 0;
}

/** struct SoundIoChannelArea, zeroed as C's {0}. $ptr is the char* address of the channel's first sample. */
final class SoundIoChannelArea
{
    public int $ptr = 0;

    public int $step = 0;
}
