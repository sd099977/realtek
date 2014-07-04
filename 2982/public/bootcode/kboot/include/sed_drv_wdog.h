#ifndef __SED_DRV_WDOG_H__
#define __SED_DRV_WDOG_H__

/* "Sirius_MISC_Arch_Spec.doc" */
#define MIS_REG_BASE		0xb801b000

/* Timer */
#define MIS_TCWCR		(MIS_REG_BASE + 0x6f0)
#define MIS_TCWTR		(MIS_REG_BASE + 0x6f4)
#define MIS_TCWNMI		(MIS_REG_BASE + 0x6f8)
#define MIS_TCWOV		(MIS_REG_BASE + 0x6fc)

void sed_wdog_reset (void);

#endif
