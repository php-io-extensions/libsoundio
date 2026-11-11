# Security Policy

## Supported versions

ext-libsoundio is pre-1.0. No 0.x release receives security fixes or advisories; fixes land in
the next release line. Security support starts with 1.0.

| Version | Security fixes |
|---------|----------------|
| < 1.0   | No             |

## Reporting a vulnerability

Please don't open a public issue for a security problem.

Report it privately through GitHub: the **Report a vulnerability** button on the
[php-io-extensions/libsoundio](https://github.com/php-io-extensions/libsoundio) repository's
**Security** tab. If that isn't available, email **info@projectsaturnstudios.com**.

Include what you found, the affected version, your platform and audio backend (CoreAudio, ALSA,
PulseAudio or JACK), PHP build (NTS or ZTS) and the libsoundio version (`php --ri libsoundio`
shows it), and steps to reproduce. Reports are read and weighed for the release line in
development; before 1.0 there is no response-time commitment.

A defect in libsoundio itself belongs with that project. Report it here as well when
ext-libsoundio should guard against it.

## Security model

ext-libsoundio opens audio devices and streams on behalf of the PHP process. It reads no files
and makes no network requests.

- **Inputs.** A count past its list, a builtin layout index outside libsoundio's table, and
  `soundio_outstream_set_volume` on a backend without a volume are refused before libsoundio
  reads them. A channel layout copies at most `SOUNDIO_MAX_CHANNELS` channels.
- **Addresses.** `fromPointer()`, `userdata`, ring buffer pointers, channel area pointers and
  every callback field libsoundio calls off the PHP thread take addresses as ints and trust them:
  an address from another extension is passed through as given. Starting a stream whose
  `write_callback` / `read_callback` is 0 is refused.
- **Handles.** A destroyed context, stream or ring buffer, or a device whose last reference was
  dropped, throws `ValueError` instead of reaching libsoundio with a freed pointer.
- **Callbacks.** PHP callables run only inside `soundio_flush_events()` /
  `soundio_wait_events()` on the PHP thread, are held by the extension and released at request
  end, after libsoundio is given its own callbacks back.

A report is in scope when ext-libsoundio itself reads or writes memory it should not, leaks, or
crashes: a list copied past its length, a handle used after libsoundio freed it, PHP entered from
a libsoundio thread.
