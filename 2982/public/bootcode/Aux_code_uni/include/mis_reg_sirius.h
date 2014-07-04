/************************************************************************
 *
 *  mis_reg_sirius.h
 *
 *  Defines for Sirius MISC registers
 *
 ************************************************************************/

#ifndef MIS_REG_H
#define MIS_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
//see "Sirius_MISC_Arch_Spec.doc"
#define MIS_REG_BASE		0xb801b000

#define MIS_UMSK_ISR		(MIS_REG_BASE + 0x8)
#define MIS_ISR			(MIS_REG_BASE + 0xc)

#define MIS_UMSK_ISR_GP0A	(MIS_REG_BASE + 0x40)
#define MIS_UMSK_ISR_GP1A	(MIS_REG_BASE + 0x44)
#define MIS_UMSK_ISR_GP2A	(MIS_REG_BASE + 0x48)
#define MIS_UMSK_ISR_GP3A	(MIS_REG_BASE + 0x4c)
#define MIS_UMSK_ISR_GP4A	(MIS_REG_BASE + 0x50)
#define MIS_UMSK_ISR_GP5A	(MIS_REG_BASE + 0x54)
#define MIS_UMSK_ISR_GP6A	(MIS_REG_BASE + 0x58)
#define MIS_UMSK_ISR_GP7A	(MIS_REG_BASE + 0x5c)

#define MIS_UMSK_ISR_GP0DA	(MIS_REG_BASE + 0x60)
#define MIS_UMSK_ISR_GP1DA	(MIS_REG_BASE + 0x64)
#define MIS_UMSK_ISR_GP2DA	(MIS_REG_BASE + 0x68)
#define MIS_UMSK_ISR_GP3DA	(MIS_REG_BASE + 0x6c)
#define MIS_UMSK_ISR_GP4DA	(MIS_REG_BASE + 0x70)
#define MIS_UMSK_ISR_GP5DA	(MIS_REG_BASE + 0x74)
#define MIS_UMSK_ISR_GP6DA	(MIS_REG_BASE + 0x78)
#define MIS_UMSK_ISR_GP7DA	(MIS_REG_BASE + 0x7c)

/* GPIO */
#define MIS_GP0DIR		(MIS_REG_BASE + 0x100)
#define MIS_GP1DIR		(MIS_REG_BASE + 0x104)
#define MIS_GP2DIR		(MIS_REG_BASE + 0x108)
#define MIS_GP3DIR		(MIS_REG_BASE + 0x10c)
#define MIS_GP4DIR		(MIS_REG_BASE + 0x110)
#define MIS_GP5DIR		(MIS_REG_BASE + 0x114)
#define MIS_GP6DIR		(MIS_REG_BASE + 0x118)
#define MIS_GP0DATO		(MIS_REG_BASE + 0x11c)
#define MIS_GP1DATO		(MIS_REG_BASE + 0x120)
#define MIS_GP2DATO		(MIS_REG_BASE + 0x124)
#define MIS_GP3DATO		(MIS_REG_BASE + 0x128)
#define MIS_GP4DATO		(MIS_REG_BASE + 0x12c)
#define MIS_GP5DATO		(MIS_REG_BASE + 0x130)
#define MIS_GP6DATO		(MIS_REG_BASE + 0x134)
#define MIS_GP0DATI		(MIS_REG_BASE + 0x138)
#define MIS_GP1DATI		(MIS_REG_BASE + 0x13c)
#define MIS_GP2DATI		(MIS_REG_BASE + 0x140)
#define MIS_GP3DATI		(MIS_REG_BASE + 0x144)
#define MIS_GP4DATI		(MIS_REG_BASE + 0x148)
#define MIS_GP5DATI		(MIS_REG_BASE + 0x14c)
#define MIS_GP6DATI		(MIS_REG_BASE + 0x150)
#define MIS_GP0IE		(MIS_REG_BASE + 0x154)
#define MIS_GP1IE		(MIS_REG_BASE + 0x158)
#define MIS_GP2IE		(MIS_REG_BASE + 0x15c)
#define MIS_GP3IE		(MIS_REG_BASE + 0x160)
#define MIS_GP4IE		(MIS_REG_BASE + 0x164)
#define MIS_GP5IE		(MIS_REG_BASE + 0x168)
#define MIS_GP6IE		(MIS_REG_BASE + 0x16c)

/* Timer */
#define MIS_TCWCR		(MIS_REG_BASE + 0x6f0)
#define MIS_TCWTR		(MIS_REG_BASE + 0x6f4)
#define MIS_TCWNMI		(MIS_REG_BASE + 0x6f8)
#define MIS_TCWOV		(MIS_REG_BASE + 0x6fc)



#endif /* #ifndef MIS_REG_H */
