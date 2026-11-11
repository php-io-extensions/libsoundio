<?php

declare(strict_types=1);

if (! extension_loaded('libsoundio')) {
    throw new RuntimeException('The libsoundio extension is not loaded; run ./install-macos.sh or ./install-debian-trixie.sh');
}

/** A context connected to the dummy backend, its first device scan done: one output and one input device, no hardware. */
function dummy(): SoundIo
{
    $soundio = soundio_create() ?? throw new RuntimeException('soundio_create returned NULL');
    $err = soundio_connect_backend($soundio, SoundIoBackendDummy);
    if ($err !== SoundIoErrorNone) {
        throw new RuntimeException('soundio_connect_backend: ' . soundio_strerror($err));
    }
    soundio_flush_events($soundio);

    return $soundio;
}

/** macOS and Linux signal numbers a kept refusal's probe dies by. */
const PROBE_SIGBUS = PHP_OS_FAMILY === 'Darwin' ? 10 : 7;
const PROBE_SIGSEGV = 11;
const PROBE_SIGABRT = 6;

/** Skips a tests/Probes test unless the loaded ext-libsoundio is a probe build (--enable-libsoundio-probes). */
function requireProbeBuild(): void
{
    if (! defined('LIBSOUNDIO_PROBES')) {
        test()->markTestSkipped('ext-libsoundio is not a probe build (configure --enable-libsoundio-probes): LIBSOUNDIO_PROBES is undefined');
    }
}

/**
 * Runs $code in a child of this PHP with only ext-libsoundio loaded. $siteOff names the kept site
 * LIBSOUNDIO_PROBE_OFF turns off, null keeps every site. $gmalloc runs the child under libgmalloc
 * (macOS) with Zend's allocator off, so an over-read faults at the guard page instead of reading
 * the next heap block.
 *
 * @return array{signal: ?int, stdout: string}
 */
function libsoundioProbe(string $code, ?string $siteOff, bool $gmalloc = false): array
{
    $script = "<?php\ndeclare(strict_types=1);\ntry {\n".$code."\n} catch (Throwable \$t) {\n    echo 'REFUSED ', get_class(\$t), ': ', \$t->getMessage(), \"\\n\";\n}\necho \"SURVIVED\\n\";\n";
    $file = tempnam(sys_get_temp_dir(), 'libsoundio-probe');
    file_put_contents($file, $script);

    $env = getenv();
    unset($env['LIBSOUNDIO_PROBE_OFF'], $env['DYLD_INSERT_LIBRARIES'], $env['USE_ZEND_ALLOC']);
    $env['XDEBUG_MODE'] = 'off';
    if ($siteOff !== null) {
        $env['LIBSOUNDIO_PROBE_OFF'] = $siteOff;
    }
    if ($gmalloc && PHP_OS_FAMILY === 'Darwin') {
        $env['DYLD_INSERT_LIBRARIES'] = '/usr/lib/libgmalloc.dylib';
        $env['USE_ZEND_ALLOC'] = '0';
    }

    $command = [PHP_BINARY, '-n', '-d', 'memory_limit=128M', '-d', 'extension='.ini_get('extension_dir').'/libsoundio.so', $file];
    $process = proc_open($command, [0 => ['file', '/dev/null', 'r'], 1 => ['pipe', 'w'], 2 => ['file', '/dev/null', 'w']], $pipes, null, $env);
    $stdout = (string) stream_get_contents($pipes[1]);
    fclose($pipes[1]);
    do {
        $status = proc_get_status($process);
        if ($status['running']) {
            usleep(20_000);
        }
    } while ($status['running']);
    proc_close($process);
    @unlink($file);

    return ['signal' => $status['signaled'] ? $status['termsig'] : null, 'stdout' => $stdout];
}
