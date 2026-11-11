<?php

declare(strict_types=1);

// Sites libsoundio-null-write-callback and libsoundio-null-read-callback (outcome 2): starting a
// stream whose data callback is 0 returns SoundIoErrorNone, then libsoundio's audio thread calls NULL.

beforeEach(fn () => requireProbeBuild());

it('refuses to start a stream with no data callback, whose audio thread calls NULL (SIGSEGV) without the refusal', function (string $site, string $make): void {
    $code = "\$s = soundio_create();\nsoundio_connect_backend(\$s, SoundIoBackendDummy);\nsoundio_flush_events(\$s);\n"
        . "{$make}\n\$st->format = SoundIoFormatFloat32NE;\n"
        // The dummy backend's period is software_latency (1.024 s by default): 50 ms makes the call come soon.
        . "\$st->software_latency = 0.05;\n"
        . "\$open = str_contains('{$site}', 'write') ? 'soundio_outstream_open' : 'soundio_instream_open';\n"
        . "\$start = str_contains('{$site}', 'write') ? 'soundio_outstream_start' : 'soundio_instream_start';\n"
        . "\$open(\$st);\n\$start(\$st);\nusleep(500000);";

    $kept = libsoundioProbe($code, null);
    $off = libsoundioProbe($code, $site);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
})->with([
    'outstream' => ['libsoundio-null-write-callback', '$st = soundio_outstream_create(soundio_get_output_device($s, 0));'],
    'instream' => ['libsoundio-null-read-callback', '$st = soundio_instream_create(soundio_get_input_device($s, 0));'],
]);
