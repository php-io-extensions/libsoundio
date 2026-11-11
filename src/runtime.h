#ifndef LIBSOUNDIO_RUNTIME_H
#define LIBSOUNDIO_RUNTIME_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <stdbool.h>
#include <stdint.h>
#include "php.h"
#include "zend_exceptions.h"
#include "php_libsoundio.h"

#include <soundio/soundio.h>

ZEND_BEGIN_MODULE_GLOBALS(libsoundio)
	HashTable boxes;                 /* native address => zend_object*, live handles only, not refcounted */
	HashTable keep;                  /* address of a native char* field => the zend_string it points into */
	HashTable callouts;              /* struct SoundIo* => libsoundio_callouts*: the PHP callables its callouts call */
ZEND_END_MODULE_GLOBALS(libsoundio)

ZEND_EXTERN_MODULE_GLOBALS(libsoundio)
#define LIBSOUNDIO_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(libsoundio, v)

typedef struct {
	void *ptr;                       /* the native object; NULL once released */
	zend_object std;
} libsoundio_handle;

static zend_always_inline libsoundio_handle *libsoundio_handle_from(zend_object *obj)
{
	return (libsoundio_handle *) ((char *) obj - XtOffsetOf(libsoundio_handle, std));
}

/* The native pointer a handle parameter holds; NULL once released. */
#define LIBSOUNDIO_PTR(zv) (libsoundio_handle_from(Z_OBJ_P(zv))->ptr)

/*
 * A handle parameter libsoundio dereferences: its native pointer, or a ValueError when the
 * handle was released (libsoundio would read NULL). Callers RETURN_THROWS on EG(exception).
 */
void *libsoundio_handle_arg(zval *zv, uint32_t arg_num);
#define LIBSOUNDIO_ARG(type, var, zv, n) type *var = libsoundio_handle_arg(zv, n); if (EG(exception)) { RETURN_THROWS(); }

/* A list's C count, given as its own parameter: false (and a ValueError) when it is past the list. */
bool libsoundio_list_count(zend_long given, uint32_t length, uint32_t count_arg, uint32_t list_arg);

extern zend_class_entry *libsoundio_ce_SoundIo;
extern zend_class_entry *libsoundio_ce_SoundIoDevice;
extern zend_class_entry *libsoundio_ce_SoundIoOutStream;
extern zend_class_entry *libsoundio_ce_SoundIoInStream;
extern zend_class_entry *libsoundio_ce_SoundIoRingBuffer;
extern zend_class_entry *libsoundio_ce_SoundIoChannelLayout;
extern zend_class_entry *libsoundio_ce_SoundIoSampleRateRange;
extern zend_class_entry *libsoundio_ce_SoundIoChannelArea;

/*
 * The probe switch. A kept refusal site reads `if (!LIBSOUNDIO_PROBE_OFF("<id>") && (<check>))`.
 * A build configured with --enable-libsoundio-probes lets env LIBSOUNDIO_PROBE_OFF=<id> turn that
 * one site off, so tests/Probes can show the crash the site prevents; any other build compiles
 * the switch out.
 */
#ifdef LIBSOUNDIO_PROBES
bool libsoundio_probe_off(const char *id);
# define LIBSOUNDIO_PROBE_OFF(id) libsoundio_probe_off(id)
#else
# define LIBSOUNDIO_PROBE_OFF(id) 0
#endif

/* The handlers every handle class starts from; src/types.c adds field properties on top. */
zend_object_handlers *libsoundio_handlers(void);

/* Handle object model: not constructable from PHP, not cloneable, not serializable. */
void libsoundio_handle_setup(zend_class_entry *ce);

/* The PHP object for ptr in class ce, the one already boxed when there is one; null for NULL. */
void libsoundio_box(zval *rv, void *ptr, zend_class_entry *ce);

/* The native object goes away: its PHP object reads 0 from pointer() from now on. */
void libsoundio_release(void *ptr);

/*
 * The string a native const char * field points into (SoundIo.app_name, a stream's name and
 * layout.name), held until the field is written again or libsoundio_keep_drop(&field).
 */
const char *libsoundio_keep_string(const char **field, zend_string *str);
void libsoundio_keep_drop(const char **field);

/*
 * pointer() and fromPointer() for a handle class: the address as is, 0 once released;
 * fromPointer(0) is null. __construct is private, so PHP refuses `new` before its body runs.
 */
#define LIBSOUNDIO_POINTER_METHODS(cls) \
	ZEND_METHOD(cls, pointer) { ZEND_PARSE_PARAMETERS_NONE(); RETURN_LONG((zend_long) (uintptr_t) libsoundio_handle_from(Z_OBJ_P(ZEND_THIS))->ptr); } \
	ZEND_METHOD(cls, fromPointer) { zend_long p; ZEND_PARSE_PARAMETERS_START(1, 1) Z_PARAM_LONG(p) ZEND_PARSE_PARAMETERS_END(); \
		libsoundio_box(return_value, (void *) (uintptr_t) p, zend_get_called_scope(execute_data)); } \
	ZEND_METHOD(cls, __construct) { ZEND_PARSE_PARAMETERS_NONE(); }

/*
 * struct SoundIoChannelLayout <-> SoundIoChannelLayout. _from points out->name into the object's
 * own string, so out lives no longer than obj; it copies at most SOUNDIO_MAX_CHANNELS channels
 * and throws TypeError for a channel that is not an int.
 */
bool libsoundio_layout_from(zend_object *obj, struct SoundIoChannelLayout *out);
void libsoundio_layout_to(const struct SoundIoChannelLayout *in, zval *rv);

/* A list of SoundIoChannelLayout as an emalloc'd C array of its length; NULL (TypeError) for another element. */
struct SoundIoChannelLayout *libsoundio_layouts_from(HashTable *list, uint32_t arg);

/*
 * SoundIo.on_devices_change and .on_backend_disconnect. libsoundio calls them only inside
 * soundio_flush_events() / soundio_wait_events(); those set the thread's dispatching context
 * around the call, and a callout fired anywhere else (another thread, another context) never
 * enters PHP. libsoundio_callouts_drop() gives the struct back libsoundio's own callbacks.
 */
void libsoundio_dispatch_begin(struct SoundIo *s);
void libsoundio_dispatch_end(void);
void libsoundio_callouts_drop(struct SoundIo *s);
void libsoundio_callouts_drop_all(void);

void libsoundio_register_libsoundio(int module_number);
void libsoundio_register_types(void);
void libsoundio_register_constants(int module_number);
void libsoundio_register_soundio(void);
void libsoundio_register_stream(void);

#endif
