#ifndef PHP_LIBSOUNDIO_H
#define PHP_LIBSOUNDIO_H

extern zend_module_entry libsoundio_module_entry;
#define phpext_libsoundio_ptr &libsoundio_module_entry

#define PHP_LIBSOUNDIO_VERSION "0.11.0"

#if defined(ZTS) && defined(COMPILE_DL_LIBSOUNDIO)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
