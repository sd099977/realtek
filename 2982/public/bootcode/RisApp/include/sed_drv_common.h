#ifndef __SED_DRV_COMMON_H__
#define __SED_DRV_COMMON_H__

#include "sed_types.h"

#define REG8( addr )		  (*(volatile uint8 *) (addr))
#define REG16( addr )		  (*(volatile uint16 *)(addr))
#define REG32( addr )		  (*(volatile uint32 *)(addr))

#define bitwise_AND_OR(addr, AND_filter, OR_filter)	\
	(REG32(addr) = (REG32(addr) & AND_filter) | OR_filter)

/* Sync */
#define MAGIC_SYNC_ADDRESS	0xB801A020	//for Lexra CPU only
#define sync()	REG32(MAGIC_SYNC_ADDRESS)=0

#endif
