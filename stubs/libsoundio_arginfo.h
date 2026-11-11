/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: 7254f85f3b16c4b298e46e81970f82ee6ed187be */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_version_string, 0, 0, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_soundio_version_major, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_soundio_version_minor arginfo_soundio_version_major

#define arginfo_soundio_version_patch arginfo_soundio_version_major

ZEND_FUNCTION(soundio_version_string);
ZEND_FUNCTION(soundio_version_major);
ZEND_FUNCTION(soundio_version_minor);
ZEND_FUNCTION(soundio_version_patch);

static const zend_function_entry ext_functions[] = {
	ZEND_FE(soundio_version_string, arginfo_soundio_version_string)
	ZEND_FE(soundio_version_major, arginfo_soundio_version_major)
	ZEND_FE(soundio_version_minor, arginfo_soundio_version_minor)
	ZEND_FE(soundio_version_patch, arginfo_soundio_version_patch)
	ZEND_FE_END
};
