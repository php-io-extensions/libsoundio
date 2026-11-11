<?php

declare(strict_types=1);

// Sites libsoundio-list-count and libsoundio-builtin-index (outcome 1): libsoundio reads (or sorts
// in place) as many elements as it is told, past the memory it was given.

beforeEach(fn () => requireProbeBuild());

it('refuses a count or index past what libsoundio was given, which it reads past (SIGSEGV) without the refusal', function (string $site, string $call, bool $gmalloc, array $signals): void {
    if ($gmalloc && PHP_OS_FAMILY !== 'Darwin') {
        test()->markTestSkipped('the over-read lands in the next heap block unless libgmalloc (macOS) guards it');
    }
    $code = "\$stereo = soundio_channel_layout_get_default(2);\n{$call};";

    $kept = libsoundioProbe($code, null, $gmalloc);
    $off = libsoundioProbe($code, $site, $gmalloc);

    expect($kept['signal'])->toBeNull()
        ->and($kept['stdout'])->toContain('REFUSED ValueError')
        ->and($off['signal'])->toBeIn($signals);
})->with([
    'sort count' => ['libsoundio-list-count', "\$list = [\$stereo];\nsoundio_sort_channel_layouts(\$list, 50000000)", false, [PROBE_SIGSEGV, PROBE_SIGBUS]],
    // The C arrays of both lists are heap blocks side by side: reading past the preferred one
    // finds the available one's layout and returns, unless a guard page stops the read.
    'best match count' => ['libsoundio-list-count', "\$odd = new SoundIoChannelLayout();\n\$odd->channel_count = 2;\n\$odd->channels = [60, 61];\nsoundio_best_matching_channel_layout([\$stereo], 50000000, [\$odd], 1)", true, [PROBE_SIGSEGV, PROBE_SIGBUS]],
    // Homebrew's libsoundio compiles its assert() out and reads past the table; Debian's keeps
    // it, and the assert aborts the process.
    'builtin index' => ['libsoundio-builtin-index', 'soundio_channel_layout_get_builtin(50000000)', false, [PROBE_SIGSEGV, PROBE_SIGBUS, PROBE_SIGABRT]],
]);
