/************************************************************************
 *
 *  sfc_reg.h
 *
 *  Defines for Sirius SFC registers
 *
 ************************************************************************/

#ifndef SFC_REG_H
#define SFC_REG_H

/************************************************************************
 *  Definition
 ************************************************************************/
#define SFC_REG_BASE		0xb801a800

#define MD_PP_DATA_SIZE_SHIFT	8	/* 256 bytes */
#define MD_PP_DATA_SIZE		(1 << MD_PP_DATA_SIZE_SHIFT)

#define SFC_OPCODE		(SFC_REG_BASE + 0x00)
#define SFC_CTL			(SFC_REG_BASE + 0x04)
#define SFC_SCK			(SFC_REG_BASE + 0x08)
#define SFC_CE			(SFC_REG_BASE + 0x0c)
#define SFC_WP			(SFC_REG_BASE + 0x10)
#define SFC_POS_LATCH		(SFC_REG_BASE + 0x14)
#define SFC_WAIT_WR		(SFC_REG_BASE + 0x18)
#define SFC_EN_WR		(SFC_REG_BASE + 0x1c)
#define SFC_FAST_RD		(SFC_REG_BASE + 0x20)
#define SFC_SCK_TAP		(SFC_REG_BASE + 0x24)
#define SF_32MB_EN	     	(SFC_REG_BASE + 0x28)

#define SPI_NAND_0		(SFC_REG_BASE + 0x2c)

#define SPI_ADDR_CNT_1		0	
#define SPI_ADDR_CNT_2		1
#define SPI_ADDR_CNT_3		2

// System Bridge II
#define SB2_WRAPPER_CTRL	((volatile unsigned int *)0xb801a018)

// Move Data Engine
//#define MD_FDMA_DDR_SADDR	((volatile unsigned int *)0xb800b088)
//#define MD_FDMA_FL_SADDR	((volatile unsigned int *)0xb800b08c)
//#define MD_FDMA_CTRL2		((volatile unsigned int *)0xb800b090)
//#define MD_FDMA_CTRL1		((volatile unsigned int *)0xb800b094)


#endif /* #ifndef SFC_REG_H */
