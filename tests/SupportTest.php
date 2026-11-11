<?php

declare(strict_types=1);

require_once __DIR__ . '/../scripts/support.php';

it('counts the SOUNDIO_EXPORT functions of each header, sorted, once each', function (): void {
    $header = "SOUNDIO_EXPORT struct SoundIo *soundio_create(void);\nSOUNDIO_EXPORT const char *soundio_version_string(void);\n"
        . "SOUNDIO_EXPORT int soundio_connect(struct SoundIo *soundio);\n"
        . "SOUNDIO_EXPORT struct SoundIo *soundio_create(void);\n#define SOUNDIO_EXPORT SOUNDIO_EXTERN_C\n";

    expect(support_counted(['soundio.h' => $header, 'empty.h' => "#define X 1\n"]))
        ->toBe(['soundio.h' => ['soundio_connect', 'soundio_create', 'soundio_version_string']]);
});

it('reads the top-level functions of a stub, not class methods', function (): void {
    $stub = "<?php\nfunction soundio_create(): ?SoundIo {}\nfinal class SoundIo { public function pointer(): int {} }\nfunction soundio_destroy(SoundIo \$s): void {}\n";

    expect(support_functions($stub))->toBe(['soundio_create', 'soundio_destroy']);
});

it('renders one line per function and lists the bindings that match none', function (): void {
    $md = support_render(['soundio.h' => ['soundio_create', 'soundio_destroy']], ['soundio_create' => true, 'soundio_helper' => true], 'libsoundio 2.0.0', '2026-11-11');

    expect($md)->toContain('- [x] `soundio_create`')
        ->toContain('- [ ] `soundio_destroy`')
        ->toContain('## soundio.h (1 / 2)')
        ->toContain('libsoundio 2.0.0 — 1 / 2 members bound (50.0%) — 2026-11-11')
        ->toContain('- `soundio_helper`');
});

it('computes the badge from the counts', function (): void {
    expect(support_badge('libsoundio API', 72, 72))
        ->toBe('[![libsoundio API](https://img.shields.io/badge/libsoundio_API-100.0%25_%2872%2F72%29-blue?style=flat-square)](SUPPORT.md)');
});

it('sets the badge after the CI badge, then in place', function (): void {
    $readme = "# libsoundio\n\n[![CI](x)](y)\n\ntext\n";
    $once = support_readme($readme, '[![libsoundio API](a)](SUPPORT.md)');

    expect($once)->toBe("# libsoundio\n\n[![CI](x)](y)\n[![libsoundio API](a)](SUPPORT.md)\n\ntext\n")
        ->and(support_readme($once, '[![libsoundio API](b)](SUPPORT.md)'))->toBe("# libsoundio\n\n[![CI](x)](y)\n[![libsoundio API](b)](SUPPORT.md)\n\ntext\n");
});

it('binds every libsoundio 2.0.0 function, and SUPPORT.md and the badge are current', function (): void {
    $root = dirname(__DIR__);
    exec(PHP_BINARY . ' ' . escapeshellarg("{$root}/scripts/support.php") . ' --check', $out, $code);

    expect($code)->toBe(0)
        ->and(file_get_contents("{$root}/SUPPORT.md"))->toContain('libsoundio 2.0.0 — 72 / 72 members bound (100.0%)');
});
