/************************************************************************
 *
 *  iso_reg.h
 *
 *  Defines for MacArthur2 ISO registers
 *
 ************************************************************************/

#ifndef ISO_REG_H
#define ISO_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define ISO_REG_BASE				0xb8061000

#define ISO_ISR						(ISO_REG_BASE + 0x0)
//#define ISO_UMSK_ISR				(ISO_REG_BASE + 0x4)
//#define ISO_UMSK_ISR_GP_ASSERT		(ISO_REG_BASE + 0x8)
//#define ISO_UMSK_ISR_GP_ASSERT_1	(ISO_REG_BASE + 0xc)
//#define ISO_UMSK_ISR_GP_DEASSERT	(ISO_REG_BASE + 0x10)

#define ISO_DBG			(ISO_REG_BASE + 0x8)

#define ISO_SCPU_INT_EN		(ISO_REG_BASE + 0x4)


/* GPIO */
#define ISO_GPDIR		(ISO_REG_BASE + 0x100)
#define ISO_GPDIR1		(ISO_REG_BASE + 0x104)
#define ISO_GPDATO		(ISO_REG_BASE + 0x108)
#define ISO_GPDATO1		(ISO_REG_BASE + 0x10C)
#define ISO_GPDATI		(ISO_REG_BASE + 0x110)
#define ISO_GPDATI1		(ISO_REG_BASE + 0x114)
#define ISO_GPIE		(ISO_REG_BASE + 0x118)
#define ISO_GPIE1		(ISO_REG_BASE + 0x11C)
#define ISO_GPDP		(ISO_REG_BASE + 0x120)
#define ISO_GPDP1		(ISO_REG_BASE + 0x124)
#define ISO_GPDEB		(ISO_REG_BASE + 0x128)
#define ISO_ISR_GP0A		(ISO_REG_BASE + 0x130)
#define ISO_ISR_GP1A		(ISO_REG_BASE + 0x134)
#define ISO_ISR_GP0DA		(ISO_REG_BASE + 0x138)
#define ISO_ISR_GP1DA		(ISO_REG_BASE + 0x13c)

#endif /* #ifndef ISO_REG_H */
