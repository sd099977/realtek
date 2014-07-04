/************************************************************************
 *
 *  sys_reg_sirius.h
 *
 *  Defines for Sirius CRT registers
 *
 ************************************************************************/

#ifndef SYS_REG_H
#define SYS_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
//see "Sirius_DesignSpec_StandbyTop.doc"
#define ST_REG_BASE              0xb8060000 
									   
#define ST_VERID            (ST_REG_BASE + 0)
#define ST_LV_RST           (ST_REG_BASE + 0x4)
#define ST_POL              (ST_REG_BASE + 0x8)
#define ST_CTRL0            (ST_REG_BASE + 0x10)

#define ST_RESET0           (ST_REG_BASE + 0x30)
#define ST_RESET1           (ST_REG_BASE + 0x34)
#define ST_CLOCK_ENABLE0    (ST_REG_BASE + 0x40)
#define ST_CLOCK_ENABLE1    (ST_REG_BASE + 0x44)
#define ST_MHL_CBUS         (ST_REG_BASE + 0x48)
#define ST_BUSCLK           (ST_REG_BASE + 0x50)
#define ST_EMCUCLK          (ST_REG_BASE + 0x54)
#define ST_CLKMUX           (ST_REG_BASE + 0x58)

/* register not affected by watchdog reset */
#define ST_WDOG_DATA1		(ST_REG_BASE + 0x100)
#define ST_WDOG_DATA2		(ST_REG_BASE + 0x104)
#define ST_WDOG_DATA3		(ST_REG_BASE + 0x108)
#define ST_WDOG_DATA4		(ST_REG_BASE + 0x10c)
#define ST_WDOG_DATA5		(ST_REG_BASE + 0x110)
#define ST_WDOG_DATA6		(ST_REG_BASE + 0x114)
#define ST_WDOG_DATA7		(ST_REG_BASE + 0x118)
#define ST_WDOG_DATA8		(ST_REG_BASE + 0x11c)
#define ST_WDOG_DATA9		(ST_REG_BASE + 0x120)

// bit[1]: set by HIF, indicate KCPU is unable to run, ACPU has to init CRT/UART registers for recovery mode
// bit[0]: set by KCPU, indicate ACPU which UART is active for recovery mode (0 means UART0, 1 means UART1)
#if defined(FPGA) || defined(CONFIG_ENV_FPGA)
#define ST_WDOG_DATA10		(0xb801bc1c)		// FPGA does not include ISO registers, use MISC UART scratch register instead
#else
#define ST_WDOG_DATA10		(ST_REG_BASE + 0x124)
#endif

// bit[0]: set by 8051, force KCPU to skip recovery mode detection
#define ST_WDOG_DATA11		(ST_REG_BASE + 0x128)

// contains ACPU jump address (see reset_def_sirius.h)
#define ST_WDOG_DATA12		(ST_REG_BASE + 0x12c)

//see "Sirius_CRT_Arch_Spec.doc"
#define SYS_REG_BASE			0xb8000000 
                                   
/* CRT */                                   
#define SYS_SOFT_RESET1			(SYS_REG_BASE + 0x0)
#define SYS_SOFT_RESET2			(SYS_REG_BASE + 0x4)
#define SYS_SOFT_RESET3			(SYS_REG_BASE + 0x8)
#define SYS_CLOCK_ENABLE1		(SYS_REG_BASE + 0xc)
#define SYS_CLOCK_ENABLE2		(SYS_REG_BASE + 0x10)
#define SYS_GROUP1_CK_EN		(SYS_REG_BASE + 0x14)
#define SYS_GROUP1_CK_SEL		(SYS_REG_BASE + 0x18)
#define SYS_AUDIO_CLK_CTL		(SYS_REG_BASE + 0x2c)

#define SYS_CONTROL0			(SYS_REG_BASE + 0xec)

#define SYS_PLL_SCPU1			(SYS_REG_BASE + 0x100)
#define SYS_PLL_SCPU2			(SYS_REG_BASE + 0x104)
#define SYS_PLL_ACPU1			(SYS_REG_BASE + 0x108)
#define SYS_PLL_ACPU2			(SYS_REG_BASE + 0x10c)
#define SYS_PLL_VCPU1			(SYS_REG_BASE + 0x110)
#define SYS_PLL_VCPU2			(SYS_REG_BASE + 0x114)
#define SYS_PLL_BUS1			(SYS_REG_BASE + 0x130)
#define SYS_PLL_BUS2			(SYS_REG_BASE + 0x134)
#define SYS_PLL_BUS3			(SYS_REG_BASE + 0x138)
#define SYS_PLL_DCSB1			(SYS_REG_BASE + 0x140)
#define SYS_PLL_DCSB2			(SYS_REG_BASE + 0x144)
#define SYS_PLL_DCSB3			(SYS_REG_BASE + 0x148)

#define SYS_PLL_DISP_SD1		(SYS_REG_BASE + 0x170)
#define SYS_PLL_DISP_SD2		(SYS_REG_BASE + 0x174)
#define SYS_PLL_DISP_SD3		(SYS_REG_BASE + 0x178)
#define SYS_PLL_DISP_SD4		(SYS_REG_BASE + 0x17c)
#define SYS_PLL_DISP_SD5		(SYS_REG_BASE + 0x180)
#define SYS_PLL_DISP_SD6		(SYS_REG_BASE + 0x184)
#define SYS_PLL_DISP_SD7		(SYS_REG_BASE + 0x188)

/* BISR control registers */
#define SYS_CRT_BISR_EN1		(SYS_REG_BASE + 0x580)
#define SYS_CRT_BISR_RSTN1		(SYS_REG_BASE + 0x588)
#define SYS_CRT_BISR_PWR_RSTN1		(SYS_REG_BASE + 0x590)
#define SYS_CRT_BISR_HOLD_REMAP1	(SYS_REG_BASE + 0x598)
#define SYS_CRT_BISR_HOLD_REMAP2	(SYS_REG_BASE + 0x59c)
#define SYS_CRT_BISR_2ND_RUN_EN1	(SYS_REG_BASE + 0x5a0)
#define SYS_CRT_DRF_BISR_EN1		(SYS_REG_BASE + 0x5a8)
#define SYS_CRT_DRF_BISR_TEST_RESUME1	(SYS_REG_BASE + 0x5b0)

#define SYS_CRT_BISR_DONE1		(SYS_REG_BASE + 0x700)
#define SYS_CRT_BISR_ST			(SYS_REG_BASE + 0x710)
#define SYS_CRT_BISR_REPAIRED1		(SYS_REG_BASE + 0x720)



//see "Sirius-DesignSpec-PLLETN.doc"
#define SYS_PLL_ETN2 			(SYS_REG_BASE + 0x16d04)

#endif /* #ifndef SYS_REG_H */
