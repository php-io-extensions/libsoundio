/*
 * libsoundio: 1:1 bindings of libsoundio 2.0. Handles and constants keep their C names; dropping
 * the last PHP reference does not destroy the native object.
 */
#include "runtime.h"
#include "ext/standard/info.h"
#include "../stubs/libsoundio_arginfo.h"

PHP_FUNCTION(soundio_version_string)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_STRING(soundio_version_string());
}

PHP_FUNCTION(soundio_version_major)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(soundio_version_major());
}

PHP_FUNCTION(soundio_version_minor)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(soundio_version_minor());
}

PHP_FUNCTION(soundio_version_patch)
{
	ZEND_PARSE_PARAMETERS_NONE();
	RETURN_LONG(soundio_version_patch());
}

void libsoundio_register_libsoundio(int module_number)
{
	zend_register_functions(NULL, ext_functions, NULL, MODULE_PERSISTENT);
}

ZEND_DECLARE_MODULE_GLOBALS(libsoundio)

static PHP_GINIT_FUNCTION(libsoundio)
{
#if defined(COMPILE_DL_LIBSOUNDIO) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	zend_hash_init(&libsoundio_globals->boxes, 32, NULL, NULL, 1);
	zend_hash_init(&libsoundio_globals->keep, 8, NULL, ZVAL_PTR_DTOR, 1);
	zend_hash_init(&libsoundio_globals->callouts, 8, NULL, NULL, 1);
}

static PHP_GSHUTDOWN_FUNCTION(libsoundio)
{
	zend_hash_destroy(&libsoundio_globals->boxes);
	zend_hash_destroy(&libsoundio_globals->keep);
	zend_hash_destroy(&libsoundio_globals->callouts);
}

PHP_MINIT_FUNCTION(libsoundio)
{
	libsoundio_register_libsoundio(module_number);
	libsoundio_register_types();
	libsoundio_register_constants(module_number);
	libsoundio_register_soundio();
	libsoundio_register_stream();
#ifdef LIBSOUNDIO_PROBES
	REGISTER_BOOL_CONSTANT("LIBSOUNDIO_PROBES", true, CONST_PERSISTENT);
#endif
	return SUCCESS;
}

PHP_RINIT_FUNCTION(libsoundio)
{
#if defined(COMPILE_DL_LIBSOUNDIO) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}

/*
 * What the request handed libsoundio dies with it: its callables (libsoundio gets its own
 * callbacks back) and its strings (libsoundio reads app_name only while connecting).
 */
PHP_RSHUTDOWN_FUNCTION(libsoundio)
{
	libsoundio_callouts_drop_all();
	zend_hash_clean(&LIBSOUNDIO_G(keep));
	return SUCCESS;
}

PHP_MINFO_FUNCTION(libsoundio)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "libsoundio support", "enabled");
	php_info_print_table_row(2, "Version", PHP_LIBSOUNDIO_VERSION);
	php_info_print_table_row(2, "libsoundio version", soundio_version_string());
	php_info_print_table_end();
}

zend_module_entry libsoundio_module_entry = {
	STANDARD_MODULE_HEADER,
	"libsoundio",
	NULL,
	PHP_MINIT(libsoundio),
	NULL,
	PHP_RINIT(libsoundio),
	PHP_RSHUTDOWN(libsoundio),
	PHP_MINFO(libsoundio),
	PHP_LIBSOUNDIO_VERSION,
	PHP_MODULE_GLOBALS(libsoundio),
	PHP_GINIT(libsoundio),
	PHP_GSHUTDOWN(libsoundio),
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_LIBSOUNDIO
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif
ZEND_GET_MODULE(libsoundio)
#endif
