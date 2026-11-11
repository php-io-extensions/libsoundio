---
type: Runbook
title: Build, install, test
description: Mac NTS/ZTS through Homebrew, the Pi through Debian's libsoundio-dev, and probe builds.
resource: install-macos.sh
tags: [libsoundio, build]
status: draft
generated: { by: claude-opus/5.5, at: 2026-11-11T00:00:00Z }
sources:
  - id: mac
    resource: install-macos.sh
    title: macOS installer
  - id: debian
    resource: install-debian-trixie.sh
    title: Debian trixie installer
---

# macOS

`./install-macos.sh` builds a disposable copy per PHP (default: Homebrew php@8.4 and php@8.4-zts), installs `libsoundio.so` into its extension_dir, ad-hoc signs it, writes `30-libsoundio.ini` unless an ini there already loads libsoundio.[^mac] Needs `brew install libsoundio` (2.0.1). libsoundio ships no `.pc` file: `config.m4` finds `include/soundio/soundio.h` under the usual prefixes or `--with-libsoundio=DIR`.

Tests: `composer install`, then `php84 -d memory_limit=128M vendor/bin/pest` and the same with php@8.4-zts's binary. Every test uses `SoundIoBackendDummy`: no hardware, no sound.

Probe build: `LIBSOUNDIO_CONFIGURE=--enable-libsoundio-probes ./install-macos.sh`, then the suite runs `tests/Probes`; reinstall without it afterwards (a normal build skips the probes).

# Pi (Debian trixie)

`apt install libsoundio-dev` (2.0.0; library in `/usr/lib/aarch64-linux-gnu`, header in `/usr/include/soundio`). Copy: `COPYFILE_DISABLE=1 tar --no-xattrs -czf - --exclude=.git --exclude=vendor . | fnk "mkdir -p ~/promote-0.11/libsoundio && tar -xzf - -C ~/promote-0.11/libsoundio"`. Install: `fnk 'cd ~/promote-0.11/libsoundio && ./install-debian-trixie.sh'`.[^debian]

[^mac]: macOS installer
[^debian]: Debian trixie installer
