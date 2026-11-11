<?php

declare(strict_types=1);

// Site libsoundio-released-handle (outcome 1): a released handle's pointer is NULL, and every
// libsoundio function these calls reach dereferences its handle without checking it.

beforeEach(fn () => requireProbeBuild());

it('refuses a released handle, which libsoundio dereferences (SIGSEGV) without the refusal', function (string $call): void {
    $code = "\$s = soundio_create();\nsoundio_connect_backend(\$s, SoundIoBackendDummy);\nsoundio_flush_events(\$s);\n"
        . "\$d = soundio_get_output_device(\$s, 0);\n\$o = soundio_outstream_create(\$d);\n"
        . "soundio_outstream_destroy(\$o);\n{$call};";

    $kept = libsoundioProbe($code, null);
    $off = libsoundioProbe($code, 'libsoundio-released-handle');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($kept['stdout'])->toContain('has been released')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
})->with([
    'context' => ["soundio_destroy(\$s);\nsoundio_flush_events(\$s)"],
    'stream' => ['soundio_outstream_open($o)'],
    'device' => ["soundio_destroy(\$s);\nsoundio_device_unref(\$d);\nsoundio_device_supports_format(\$d, SoundIoFormatFloat32NE)"],
]);
