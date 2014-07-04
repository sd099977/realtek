#include "sed_drv_common.h"
#include "sed_drv_rng.h"

void sed_rng_init (void)
{
	// enable RNG
	REG32(0xb800181c) = 0x01010b09;

#if defined (SIRIUS)
	/* Check ROSC is lock (CKOUT_ROSC is stable) */
	while (!(REG32(RNG_CALI_RETURN) & ROSC_LOCK_MASK));
#endif
}

void sed_rng_get (uint32 *rand) //Not used currently, access register directly
{
#if defined (SIRIUS)
	do {
		*rand = REG32(RNG_RESULTR);
	} while (*rand == 0x0);
#endif
	return;
}

