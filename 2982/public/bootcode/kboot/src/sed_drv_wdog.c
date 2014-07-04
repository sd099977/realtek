#include "sed_common.h"
#include "sed_drv_common.h"
#include "sed_drv_wdog.h"

void sed_wdog_reset (void)
{
#if defined (SIRIUS_VERB)
	REG32(MIS_TCWCR) = 0xa5;	// disable watchdog
	REG32(MIS_TCWTR) = 0x1;		// clear watchdog counter

	// set overflow count
	REG32(MIS_TCWOV) = 0x29000;

	REG32(MIS_TCWCR) = 0;		// enable watchdog
#endif


#if defined (SIRIUS)
	REG32(0xb8017184) = 0x0;  // reset chip for CUTA only
	REG32(0xb80600E4) = 0xa;  // reset chip
#endif


}
