<?php

declare(strict_types=1);

// Site libsoundio-set-volume-unsupported (outcome 1): libsoundio 2.0 calls the backend's
// set_volume without checking it; only CoreAudio and WASAPI set one, the dummy backend does not.

beforeEach(fn () => requireProbeBuild());

it('refuses set_volume on a backend without one, which libsoundio calls through NULL (SIGSEGV) without the refusal', function (): void {
    $code = "\$s = soundio_create();\nsoundio_connect_backend(\$s, SoundIoBackendDummy);\nsoundio_flush_events(\$s);\n"
        . "\$o = soundio_outstream_create(soundio_get_output_device(\$s, 0));\n\$o->format = SoundIoFormatFloat32NE;\n"
        . "soundio_outstream_open(\$o);\nsoundio_outstream_set_volume(\$o, 0.5);";

    $kept = libsoundioProbe($code, null);
    $off = libsoundioProbe($code, 'libsoundio-set-volume-unsupported');

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($off['signal'])->toBeIn([PROBE_SIGSEGV, PROBE_SIGBUS]);
});
