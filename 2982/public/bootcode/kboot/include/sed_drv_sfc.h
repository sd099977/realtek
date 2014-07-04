#ifndef __SED_DRV_SFC_H__
#define __SED_DRV_SFC_H__

/* NOR Flash start address (0xBDC00000 + 16MB) */
#define SPI_BASE_ADDR	0xBEC00000

#define SFC_REG_BASE	0xB801A800

#define SFC_OPCODE		(SFC_REG_BASE + 0x00)
#define SFC_CTL			(SFC_REG_BASE + 0x04)
#define SFC_SCK			(SFC_REG_BASE + 0x08)
#define SFC_CE			(SFC_REG_BASE + 0x0c)
#define SFC_WP			(SFC_REG_BASE + 0x10)
#define SFC_POS_LATCH	(SFC_REG_BASE + 0x14)
#define SFC_WAIT_WR		(SFC_REG_BASE + 0x18)
#define SFC_EN_WR		(SFC_REG_BASE + 0x1c)
#define SFC_FAST_RD		(SFC_REG_BASE + 0x20)
#define SFC_SCK_TAP		(SFC_REG_BASE + 0x24)
#define SFC_32MB_EN		(SFC_REG_BASE + 0x28)

/* OP Code */
#define CMD_OP_READ_ID		0x90
#define CMD_OP_JEDEC_ID		0x9F
#define CMD_OP_READ_STS		0x05
#define CMD_OP_READ			0x03
#define CMD_OP_FAST_READ	0x0B
#define CMD_OP_WRITE_EN		0x06
#define CMD_OP_BYTE_PROG	0x02
#define CMD_OP_4K_ERASE		0x20
#define CMD_OP_32K_ERASE	0x52
#define CMD_OP_64K_ERASE	0xD8

/* SFC CTL */
#define DATA_EN	0x10
#define ADDR_EN	0x08

int sed_sfc_init (void);
int sed_sfc_read (uint32 offset, uint8 *buf, uint32 len);
int sed_sfc_write (uint32 offset, uint8 *buf, uint32 len);
int sed_sfc_erase (uint32 offset, uint32 len);

#endif
