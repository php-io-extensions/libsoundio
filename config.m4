PHP_ARG_WITH([libsoundio],
  [whether to enable libsoundio support],
  [AS_HELP_STRING([[--with-libsoundio[=DIR]]], [Enable the libsoundio 2.0 bindings; DIR is the prefix holding include/soundio/soundio.h])],
  [no])

PHP_ARG_ENABLE([libsoundio-probes],
  [whether to build the libsoundio probe switch],
  [AS_HELP_STRING([--enable-libsoundio-probes],
    [Build the LIBSOUNDIO_PROBE_OFF switch that tests/Probes drives: env LIBSOUNDIO_PROBE_OFF=<site id> turns that kept refusal off. Never for a release build])],
  [no],
  [no])

if test "$PHP_LIBSOUNDIO" != "no"; then
  if test "$PHP_LIBSOUNDIO_PROBES" != "no"; then
    AC_DEFINE([LIBSOUNDIO_PROBES], [1], [Kept refusal sites can be turned off through env LIBSOUNDIO_PROBE_OFF])
  fi

  dnl libsoundio installs no pkg-config file: find the prefix by its header.
  AC_MSG_CHECKING([for libsoundio])
  SOUNDIO_DIR=
  for i in $PHP_LIBSOUNDIO /opt/homebrew /usr/local /usr; do
    if test "$i" != "yes" && test -r "$i/include/soundio/soundio.h"; then
      SOUNDIO_DIR=$i
      break
    fi
  done
  if test -z "$SOUNDIO_DIR"; then
    AC_MSG_RESULT([not found])
    AC_MSG_ERROR([include/soundio/soundio.h not found: install libsoundio (brew install libsoundio / apt install libsoundio-dev) or pass --with-libsoundio=DIR])
  fi
  AC_MSG_RESULT([$SOUNDIO_DIR])

  PHP_CHECK_LIBRARY([soundio], [soundio_create],
    [
      PHP_ADD_INCLUDE([$SOUNDIO_DIR/include])
      PHP_ADD_LIBRARY_WITH_PATH([soundio], [$SOUNDIO_DIR/$PHP_LIBDIR], [LIBSOUNDIO_SHARED_LIBADD])
    ],
    [AC_MSG_ERROR([libsoundio found at $SOUNDIO_DIR but soundio_create does not link])],
    [-L$SOUNDIO_DIR/$PHP_LIBDIR])
  PHP_SUBST([LIBSOUNDIO_SHARED_LIBADD])

  PHP_NEW_EXTENSION([libsoundio],
    [src/libsoundio.c src/runtime.c src/types.c src/constants.c src/soundio.c src/stream.c],
    [$ext_shared],, [-DZEND_ENABLE_STATIC_TSRMLS_CACHE=1])
  PHP_ADD_BUILD_DIR([$ext_builddir/src])
fi
