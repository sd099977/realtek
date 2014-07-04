#ifndef __QC_VERIFY_COMMON_H__
#define __QC_VERIFY_COMMON_H__

#include <common.h>
#include <asm/arch/system.h>
#include <rtd_types_qc.h>
#include "linux/compat.h"

#define	ew(reg_addr,para)			rtd_outl(reg_addr,para)
#define	dw(reg_addr)				rtd_inl(reg_addr)
#define ROSPrintf printk

#endif /* __QC_VERIFY_COMMON_H__ */

