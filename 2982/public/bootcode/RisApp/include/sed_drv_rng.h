#ifndef __SED_DRV_RNG_H__
#define __SED_DRV_RNG_H__

#define RNG_REG_BASE	0xB8001800

#define RNG_CTRL			(RNG_REG_BASE + 0x0)
#define RNG_RETURN0			(RNG_REG_BASE + 0x4)
#define RNG_RETURN1			(RNG_REG_BASE + 0x8)
#define RNG_RETURN2			(RNG_REG_BASE + 0xC)
#define RNG_RESULTN			(RNG_REG_BASE + 0x10)
#define RNG_ANA				(RNG_REG_BASE + 0x14)
#define RNG_CALI_CHK		(RNG_REG_BASE + 0x18)
#define RNG_CALI_CTRL		(RNG_REG_BASE + 0x1C)
#define RNG_CALI_RETURN		(RNG_REG_BASE + 0x20)
#define RNG_LOCK_CHK		(RNG_REG_BASE + 0x24)
#define RNG_LOCK_CTRL		(RNG_REG_BASE + 0x28)
#define RNG_RETURN3			(RNG_REG_BASE + 0x2C)
#define RNG_RETURN4			(RNG_REG_BASE + 0x30)
#define RNG_RETURN5			(RNG_REG_BASE + 0x34)
#define RNG_RESULTR			(RNG_REG_BASE + 0x38)
#define FOSC_ANA			(RNG_REG_BASE + 0x3C)
#define FOSC_CALI_CHK		(RNG_REG_BASE + 0x40)
#define FOSC_CALI_CTRL		(RNG_REG_BASE + 0x44)
#define FOSC_CALI_RETURN	(RNG_REG_BASE + 0x48)
#define FOSC_LOCK_ENTER_CHK	(RNG_REG_BASE + 0x4C)
#define FOSC_LOCK_CTRL		(RNG_REG_BASE + 0x50)
#define FOSC_LOCK_EXIT_CHK	(RNG_REG_BASE + 0x54)
#define EIP76_CTRL			(RNG_REG_BASE + 0x58)

#define ROSC_LOCK_MASK	0x20000

void sed_rng_init (void);
void sed_rng_get (uint32 *buf);

#endif
