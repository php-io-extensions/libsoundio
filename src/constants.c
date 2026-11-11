/* The constants of soundio.h, as stubs/soundio_constants.stub.php (tools/constants.php) lists them. */
#include "runtime.h"
#include "../stubs/soundio_constants_arginfo.h"

void libsoundio_register_constants(int module_number)
{
	register_soundio_constants_symbols(module_number);
}
