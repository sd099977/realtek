/************************************************************************
 *
 *  mis_reg.h
 *
 *  Defines for RTD299X MISC registers
 *
 ************************************************************************/

#ifndef MIS_REG_H
#define MIS_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
#if defined(CONFIG_RTD299X)
#include <asm/arch/rbus/misc_reg.h>
#elif defined(CONFIG_RTD298X)
#include <asm/arch/rbus/mis_reg.h>
#include <asm/arch/rbus/rbusPinmuxReg.h>
#endif

#if 0 // use rbus/mis_reg.h
//see "RTD299X_DesignSpec_MISC.doc-page35"
#define MIS_REG_BASE		0xb801b000

/* GPIO */
#if defined(CONFIG_RTD299X)
#define MIS_GP0DIR		(MIS_REG_BASE + 0xc00)
#define MIS_GP1DIR		(MIS_REG_BASE + 0xc04)
#define MIS_GP2DIR		(MIS_REG_BASE + 0xc08)
#define MIS_GP3DIR		(MIS_REG_BASE + 0xc0c)
#define MIS_GP4DIR		(MIS_REG_BASE + 0xc10)
#define MIS_GP5DIR		(MIS_REG_BASE + 0xc14)
#define MIS_GP0DATO		(MIS_REG_BASE + 0xc18)
#define MIS_GP1DATO		(MIS_REG_BASE + 0xc1c)
#define MIS_GP2DATO		(MIS_REG_BASE + 0xc20)
#define MIS_GP3DATO		(MIS_REG_BASE + 0xc24)
#define MIS_GP4DATO		(MIS_REG_BASE + 0xc28)
#define MIS_GP5DATO		(MIS_REG_BASE + 0xc2c)
#define MIS_GP0DATI		(MIS_REG_BASE + 0xc30)
#define MIS_GP1DATI		(MIS_REG_BASE + 0xc34)
#define MIS_GP2DATI		(MIS_REG_BASE + 0xc38)
#define MIS_GP3DATI		(MIS_REG_BASE + 0xc3c)
#define MIS_GP4DATI		(MIS_REG_BASE + 0xc40)

#define MIS_GP0IE		(MIS_REG_BASE + 0xc48)
#define MIS_GP1IE		(MIS_REG_BASE + 0xc4c)
#define MIS_GP2IE		(MIS_REG_BASE + 0xc50)
#define MIS_GP3IE		(MIS_REG_BASE + 0xc54)
#define MIS_GP4IE		(MIS_REG_BASE + 0xc58)
#define MIS_GP5IE		(MIS_REG_BASE + 0xc5c)

#define MIS_TCWCR		(MIS_REG_BASE + 0xb00)
#define MIS_TCWTR		(MIS_REG_BASE + 0xb04)
#define MIS_TCWNMI		(MIS_REG_BASE + 0xb08)
#define MIS_TCWOV		(MIS_REG_BASE + 0xb0c)

#elif defined(CONFIG_RTD298X)

#define MIS_GP0DIR		(MIS_REG_BASE + 0x100)
#define MIS_GP1DIR		(MIS_REG_BASE + 0x104)
#define MIS_GP2DIR		(MIS_REG_BASE + 0x108)
#define MIS_GP3DIR		(MIS_REG_BASE + 0x10c)
#define MIS_GP4DIR		(MIS_REG_BASE + 0x110)
#define MIS_GP5DIR		(MIS_REG_BASE + 0x114)
#define MIS_GP0DATO		(MIS_REG_BASE + 0x118)
#define MIS_GP1DATO		(MIS_REG_BASE + 0x11c)
#define MIS_GP2DATO		(MIS_REG_BASE + 0x120)
#define MIS_GP3DATO		(MIS_REG_BASE + 0x124)
#define MIS_GP4DATO		(MIS_REG_BASE + 0x128)
#define MIS_GP5DATO		(MIS_REG_BASE + 0x12c)
#define MIS_GP0DATI		(MIS_REG_BASE + 0x130)
#define MIS_GP1DATI		(MIS_REG_BASE + 0x134)
#define MIS_GP2DATI		(MIS_REG_BASE + 0x138)
#define MIS_GP3DATI		(MIS_REG_BASE + 0x13c)
#define MIS_GP4DATI		(MIS_REG_BASE + 0x140)

#define MIS_GP0IE		(MIS_REG_BASE + 0x148)
#define MIS_GP1IE		(MIS_REG_BASE + 0x14c)
#define MIS_GP2IE		(MIS_REG_BASE + 0x150)
#define MIS_GP3IE		(MIS_REG_BASE + 0x154)
#define MIS_GP4IE		(MIS_REG_BASE + 0x158)
#define MIS_GP5IE		(MIS_REG_BASE + 0x15c)

#define MIS_TCWCR		(MIS_REG_BASE + 0x6f0)
#define MIS_TCWTR		(MIS_REG_BASE + 0x6f4)
#define MIS_TCWNMI		(MIS_REG_BASE + 0x6f8)
#define MIS_TCWOV		(MIS_REG_BASE + 0x6fc)
#endif
#endif

#if 1 // need ref 298x newest rbus/rbusPinmuxReg.h
// see "PMM_RTD299X_PinMux.doc"
#define ST_PINMUX_REG_BASE		0xb8060200
#define GPIO_ST_MUXCFG_0		(ST_PINMUX_REG_BASE + 0x00)

#define GPIO_ST_MUXCFG_8		(ST_PINMUX_REG_BASE + 0x24)
#define GPIO_ST_MUXCFG_9		(ST_PINMUX_REG_BASE + 0x28)
#define ST_PIN_MUX_CTRL0		(ST_PINMUX_REG_BASE + 0xa0)



// see "Main_RTD299X_PinMux.doc"
#define PINMUX_REG_BASE		0xb8000800

#define GPIO_MUXCFG_0		(PINMUX_REG_BASE + 0x00)
#define GPIO_MUXCFG_1		(PINMUX_REG_BASE + 0x04)
#define GPIO_MUXCFG_2		(PINMUX_REG_BASE + 0x08)
#define GPIO_MUXCFG_3		(PINMUX_REG_BASE + 0x0c)
#define GPIO_MUXCFG_4		(PINMUX_REG_BASE + 0x10)
#define GPIO_MUXCFG_5		(PINMUX_REG_BASE + 0x14)
#define GPIO_MUXCFG_6		(PINMUX_REG_BASE + 0x18)
#define GPIO_MUXCFG_22		(PINMUX_REG_BASE + 0x58)
#define GPIO_MUXCFG_23		(PINMUX_REG_BASE + 0x5c)
#define GPIO_MUXCFG_24		(PINMUX_REG_BASE + 0x60)
#define PIN_MUX_CTRL1 		(PINMUX_REG_BASE + 0x100)
#define PIN_MUX_CTRL2 		(PINMUX_REG_BASE + 0x104)
#endif


#endif /* #ifndef MIS_REG_H */
