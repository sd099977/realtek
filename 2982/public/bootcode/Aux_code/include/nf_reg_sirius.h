/************************************************************************
 *
 *  nf_reg_sirius.h
 *
 *  Defines for Sirius NF registers
 *
 ************************************************************************/

#ifndef NF_REG_H
#define NF_REG_H

#define USE_KCPU_SECURITY_REGISTER	// use KCPU only register to access flash

/************************************************************************
 *  Definition
 ************************************************************************/
#define NF_REG_BASE	 0xb8010000

#ifdef USE_KCPU_SECURITY_REGISTER
#define	NF_PAGE_ADR0		NF_ND_SECU_PA0
#define	NF_PAGE_ADR1		NF_ND_SECU_PA1
#define	NF_PAGE_ADR2		NF_ND_SECU_PA2
#define	NF_PAGE_ADR3		NF_ND_SECU_PA3
#define	NF_ND_CTL		NF_ND_SECU_CTRL
#define NF_AUTO_TRIG		NF_SECU_AUTO_TRIG
#define	NF_DMA_ADR		NF_DMA_SECU_CTRL1
#define	NF_DMA_LEN		NF_DMA_SECU_CTRL2
#define	NF_DMA_CONF		NF_DMA_SECU_CTRL3
#else
#define	NF_PAGE_ADR0		(NF_REG_BASE + 0)
#define	NF_PAGE_ADR1		(NF_REG_BASE + 0x4)
#define	NF_PAGE_ADR2		(NF_REG_BASE + 0x8)	//ADDR[20:16] = [4:0]
#define	NF_PAGE_ADR3		(NF_REG_BASE + 0x2c)
#define	NF_ND_CTL		(NF_REG_BASE + 0x18)
#define NF_AUTO_TRIG		(NF_REG_BASE + 0x200)
#define	NF_DMA_ADR		(NF_REG_BASE + 0x304)
#define	NF_DMA_LEN		(NF_REG_BASE + 0x308)
#define	NF_DMA_CONF		(NF_REG_BASE + 0x30c)
#endif

#define	NF_COL_ADR0		(NF_REG_BASE + 0xc)
#define	NF_COL_ADR1		(NF_REG_BASE + 0x3c)

#define	NF_ADR_MODE		(NF_REG_BASE + 0x8)	//[7:5]
#define	NF_DATA			(NF_REG_BASE + 0x14)

#define	NF_DATA_TL0		(NF_REG_BASE + 0x100)
#define	NF_DATA_TL1		(NF_REG_BASE + 0x104)

#define	NF_CMD1			(NF_REG_BASE + 0x10)
#define	NF_CMD2			(NF_REG_BASE + 0x274)
#define	NF_CMD3			(NF_REG_BASE + 0x28)

#define NF_ECC_STATE		(NF_REG_BASE + 0x38)
#define NF_RSECC_NUM		(NF_REG_BASE + 0x204)
#define	NF_RND_CMD1		(NF_REG_BASE + 0x208)
#define	NF_RND_CMD2		(NF_REG_BASE + 0x20c)
#define	NF_RND_DATASTR_COL_H	(NF_REG_BASE + 0x210)
#define	NF_RND_SPR_STR_COL_H	(NF_REG_BASE + 0x214)
#define	NF_RND_SPR_STR_COL_L	(NF_REG_BASE + 0x218)
#define	NF_RND_RW_EN		(NF_REG_BASE + 0x21c)

#define	NF_ECC_STOP		(NF_REG_BASE + 0x264)
#define	NF_ECC_PAGE		(NF_REG_BASE + 0x268)
#define	NF_MULTI_CH_MODE	(NF_REG_BASE + 0x27c)

#define	NF_PAGE_CNT		(NF_REG_BASE + 0x26c)
#define	NF_PAGE_LEN		(NF_REG_BASE + 0x270)

#define NF_MAX_ECC_NUM		(NF_REG_BASE + 0x22c)
#define NF_CMP_MASK		(NF_REG_BASE + 0x230)

#define NF_T3			(NF_REG_BASE + 0x234)
#define NF_T2			(NF_REG_BASE + 0x238)
#define NF_T1			(NF_REG_BASE + 0x23c)

#define NF_PP_CTL1		(NF_REG_BASE + 0x12c)	//ADDR[7:0]
#define NF_PP_CTL0		(NF_REG_BASE + 0x110)	//ADDR[9:8] = [5:4]
#define NF_PP_RDY		(NF_REG_BASE + 0x228)

#define NF_LOW_PWR		(NF_REG_BASE + 0x13c)

#define NF_POLL_STATUS		(NF_REG_BASE + 0x30)

#define NF_SRAM_CTL		(NF_REG_BASE + 0x300)
#define NF_DMA1_CTL		(NF_REG_BASE + 0x10c)

#define	NF_SYS_LOW_PWR		(NF_REG_BASE + 0x310)

#define NF_DES_CMD		(NF_REG_BASE + 0x314)
#define NF_DES_MODE		(NF_REG_BASE + 0x318)
#define NF_DES_USER		(NF_REG_BASE + 0x31c)
#define	NF_DES_BASE		(NF_REG_BASE + 0x330)
#define	NF_DES_LIMIT		(NF_REG_BASE + 0x334)
#define	NF_DES_WP		(NF_REG_BASE + 0x338)
#define	NF_DES_RP		(NF_REG_BASE + 0x33c)
#define	NF_DES_CNT		(NF_REG_BASE + 0x340)
#define	NF_DBU			(NF_REG_BASE + 0x344)
#define	NF_SPR_DDR_CTL		(NF_REG_BASE + 0x348)

#define	NF_CHIP_EN		(NF_REG_BASE + 0x130)

#define	NF_USER_MASK		(NF_REG_BASE + 0x320)

#define	NF_ISR			(NF_REG_BASE + 0x324)
#define	NF_IER			(NF_REG_BASE + 0x328)

#define NF_DELAY_CNT		(NF_REG_BASE + 0x260)

#define NF_BLANK_CHK		(NF_REG_BASE + 0x34)
#define NF_ECC_SEL		(NF_REG_BASE + 0x128)
#define NF_CP_LEN		(NF_REG_BASE + 0x34c)
#define NF_DBUS_MUX		(NF_REG_BASE + 0x35c)
#define NF_SRAM_BASE		(NF_REG_BASE + 0x400) 

/* NF access (KCPU only) */
#define NF_ND_SECU_PA0		(NF_REG_BASE + 0x40)
#define NF_ND_SECU_PA1		(NF_REG_BASE + 0x44)
#define NF_ND_SECU_PA2		(NF_REG_BASE + 0x48)
#define NF_ND_SECU_PA3		(NF_REG_BASE + 0x4c)
#define NF_ND_SECU_CTRL		(NF_REG_BASE + 0x50)
#define NF_SECU_AUTO_TRIG	(NF_REG_BASE + 0x54)

/* NF protection range (KCPU only) */
#define NF_ND_SECU_START_PA0	(NF_REG_BASE + 0x58)
#define NF_ND_SECU_START_PA1	(NF_REG_BASE + 0x5c)
#define NF_ND_SECU_START_PA2	(NF_REG_BASE + 0x60)
#define NF_ND_SECU_END_PA0	(NF_REG_BASE + 0x64)
#define NF_ND_SECU_END_PA1	(NF_REG_BASE + 0x68)
#define NF_ND_SECU_END_PA2	(NF_REG_BASE + 0x6c)
#define NF_ND_SECU_MASK_EN	(NF_REG_BASE + 0x70)
#define NF_ND_SECU_BLOCK_MODE	(NF_REG_BASE + 0x74)
#define NF_PP_SRAM_FLUSH	(NF_REG_BASE + 0x7c)

/* DDR DMA security */
#define NF_DMA_SECU_CTRL1	(NF_REG_BASE + 0x360)
#define NF_DMA_SECU_CTRL2	(NF_REG_BASE + 0x364)
#define NF_DMA_SECU_CTRL3	(NF_REG_BASE + 0x368)

/* Multi-CPU request */
#define NF_SECU_REQ		(NF_REG_BASE + 0x36c)
#define NF_MULTI_CPU_ST		(NF_REG_BASE + 0x370)

#define NF_CP_NF		(NF_REG_BASE + 0x380)
#define NF_AUTO_PINSHARE_ST	(NF_REG_BASE + 0x384)


/* NAND flash ECC type */
#define NAND_ECC_TYPE_6BIT		0
#define NAND_ECC_TYPE_12BIT	1

#define NAND_CHIP_SELECT	0x1e		// NAND flash chip select = 0

/* NF dbus switch */
#define NF_DBUS_DDR		0
#define NF_DBUS_CP_SRAM		1

#endif /* #ifndef NF_REG_H */
