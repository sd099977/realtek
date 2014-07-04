#include "sed_drv_common.h"
#include "sed_drv_sfc.h"
#include "sed_drv_pinmux.h"
#include <stdio.h> //can be removed

typedef struct
{
    unsigned int id;
    unsigned int attr;
    unsigned char sec_256k_en;
    unsigned char sec_64k_en;
    unsigned char sec_32k_en;
    unsigned char sec_4k_en;
    unsigned char page_program;
    const char *string;
    unsigned int size;
} t_device_type;

/* flash attribute */
#define FLASH_SINGLE_READ  0x01
#define FLASH_DUAL_READ	   0x02
#define FLASH_QUAD_READ	   0x04
#define FLASH_4BYTE_MODE   0x80

/* hcy modified as forwarding type */
#define SST_8Mbit                  0xbf800000
#define SST_4Mbit                  0xbf258d00
#define SST_16Mbit                 0xbf254100
#define PMC_4Mbit                  0x7f9d7e00
#define PMC_PMLQ032C_32Mbit        0x7f9d4600
#define ATMEL_AT25DF641A_64Mbit    0x1f480000
#define ATMEL_AT25DF641A2_64Mbit   0x1f860001
#define ATMEL_AT25DF641A3_64Mbit   0x1f480100
#define ATMEL_AT25DF321A_32Mbit    0x1f470100
#define MX_4Mbit                   0xc2201300
#define MX_25L1605_16Mbit          0xc2201500
#define MX_25L32_32Mbit	           0xc2201600
#define MX_25L6405D_64Mbit         0xc2201700
#define MX_25L12805D_128Mbit       0xc2201800
#define MX_25L25635E_256Mbit       0xc2201900
#define MX_25L6455E_64Mbit         0xc2261700
#define MX_25L12855E_128Mbit       0xc2261800
#define SPANSION_16Mbit            0x01021400
#define SPANSION_32Mbit            0x01021500
#define SPANSION_64Mbit            0x01021600
#define SPANSION_128Mbit           0x01201800
#define SPANSION_128Mbit_64s       0x03010000
#define SPANSION_128Mbit_256s      0x03000000
//#define S25FL064K_4s                          0xef4017
#define S25FL129P_64s              0x4d010000		// uniform  64KB sector
#define S25FL129P_256s             0x4d000000		// uniform 256KB sector
#define STM_64Mbit                 0x20201700
#define STM_128Mbit                0x20201800
#define STM_N25Q_128Mbit           0x20ba1800
#define STM_N25Q_64Mbit            0x20ba1700
#define STM_N25Q_32Mbit            0x20ba1600
#define EON_EN25B64_64Mbit         0x1c201700
#define EON_EN25F16_16Mbit         0x1c311500
#define EON_EN25Q32_32Mbit         0x1c301600
#define EON_EN25Q64_64Mbit         0x1c301700
#define EON_EN25Q128_128Mbit       0x1c301800
#define EON_EN25QH64_64Mbit        0x1c701700
#define EON_EN25Q256_256Mbit       0x1c701900
#define EON_EN25QF256_256Mbit      0x1c711900

#define WINBOND_W325Q128BV_128Mbit 0xef401800
#define WINBOND_W25Q32_32Mbit      0xef401600
#define WINBOND_W32Q64_64Mbit      0xef401700
#define WINBOND_W32Q256_256Mbit    0xef401900
#define GD25Q64_64Mbit             0xc8401700
#define GD25Q32_32Mbit             0xc8401600
#define ESTM_F25L64QA_64Mbit       0x8C411700
#define ESTM_F25L32QA_32Mbit       0x8C411600
#define ESTM_F25L32_32Mbit         0x8C401600
#define ESTM_F25L32PA_32Mbit       0x8C201600

static const t_device_type device[] =
{
//	{SST_4Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 0, "SST 4Mbit", 0x080000},
//	{SST_8Mbit, (FLASH_SINGLE_READ), 0, 0, 1, 1, 0, "SST 8Mbit", 0x100000},
//	{SST_16Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 0, "SST 16Mbit", 0x200000},
//	{PMC_4Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 1, 0, "PMC 4Mbit", 0x080000},
//	{PMC_PMLQ032C_32Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 1, 0, "PMC 32Mbit", 0x400000},
//	{ATMEL_AT25DF641A_64Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 1, 1, "ATMEL 64Mbit", 0x800000},
//	{ATMEL_AT25DF321A_32Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 1, 1, "ATMEL 32Mbit", 0x400000},
//	{MX_4Mbit,  (FLASH_SINGLE_READ), 0, 1, 0, 0, 0, "MX 4Mbit", 0x080000},
//	{MX_25L1605_16Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 0, 0, "MX 16Mbit", 0x200000},
//	{MX_25L32_32Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 1, 1, "MX 32Mbit", 0x400000},
	{MX_25L6405D_64Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 1, 1, "MX 64Mbit", 0x800000},
#if 0
	{MX_25L12805D_128Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 1, 1, "MX 128Mbit", 0x1000000},
	{MX_25L25635E_256Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ|FLASH_4BYTE_MODE), 0, 1, 0, 1, 1, "MX 256Mbit", 0x2000000}, /* now we use 16Mbytes(128Mbits) */
	{MX_25L6455E_64Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 1, 1, 1, "MX 64Mbit", 0x800000},
	{MX_25L12855E_128Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 1, 1, 1, "MX 128Mbit", 0x1000000},
	{SPANSION_16Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 0, 1, "SPANSION 16Mbit", 0x200000},
	{SPANSION_32Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 0, 0, "SPANSION 32Mbit", 0x400000},
	{SPANSION_64Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 0, 0, "SPANSION_64Mbit", 0x800000},
	{SPANSION_128Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 0, 0, "SPANSION_128Mbit", 0x1000000},
	{SPANSION_128Mbit_64s, (FLASH_SINGLE_READ), 0, 1, 0, 0, 1, "SPANSION_128Mbit_s64", 0x1000000},
	{S25FL129P_64s, (FLASH_SINGLE_READ), 0, 1, 0, 0, 1, "SPANSION_128Mbit_s64", 0x1000000},
	{STM_64Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 0, 1, "STMicron_128Mbit", 0x800000},
	{STM_128Mbit, (FLASH_SINGLE_READ), 1, 1, 0, 0, 1, "STMicron_128Mbit", 0x1000000},
	{STM_N25Q_128Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 0, 1, "STMicron_N25Q_128Mbit", 0x1000000},
	{EON_EN25B64_64Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 0, 1, "EON_EN25B64_64Mbit", 0x800000},
	{EON_EN25F16_16Mbit, (FLASH_SINGLE_READ), 0, 1, 0, 1, 1, "EON_EN25F16_16Mbit", 0x200000},
	{EON_EN25Q128_128Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 1, 1, "EON_EN25Q128_128Mbit", 0x1000000},
	{EON_EN25Q32_32Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 1, 1, "EON_EN25Q32_32Mbit", 0x400000},
	{EON_EN25Q64_64Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 1, 1, "EON_EN25Q64_64Mbit", 0x800000},
	{EON_EN25QH64_64Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 0, 1, 1, "EON_EN25QH64_64Mbit", 0x800000},
	{EON_EN25Q256_256Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ|FLASH_4BYTE_MODE), 0, 1, 0, 1, 1, "EON_EN25Q256_256Mbit", 0x2000000},
	{EON_EN25QF256_256Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ|FLASH_4BYTE_MODE), 0, 1, 0, 1, 1, "EON_EN25QF256_256Mbit", 0x2000000},
	{WINBOND_W25Q32_32Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 1, 1, 1, "WINBOND_W25Q32_32Mbit", 0x400000},
	{WINBOND_W32Q64_64Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 1, 1, 1, "WINBOND_W32Q64_64Mbit", 0x800000},
	{WINBOND_W325Q128BV_128Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ), 0, 1, 1, 1, 1, "WINBOND_W325Q128BV_128Mbit", 0x1000000},
	{WINBOND_W32Q256_256Mbit, (FLASH_SINGLE_READ|FLASH_DUAL_READ|FLASH_4BYTE_MODE), 0, 1, 1, 1, 1, "WINBOND_W32Q256_256Mbit", 0x2000000},
	{GD25Q64_64Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 1, "GD25Q64_64Mbit", 0x800000},
	{GD25Q32_32Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 1, "GD25Q32_32Mbit", 0x400000},
	{ESTM_F25L32QA_32Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 1, "ESTM_F25L32QA_32Mbit", 0x400000},
	{ESTM_F25L64QA_64Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 1, "ESTM_F25L64QA_64Mbit", 0x800000},
	{ESTM_F25L32_32Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 1, "ESMT_F25L32_32Mbit", 0x400000},
	{ESTM_F25L32PA_32Mbit, (FLASH_SINGLE_READ), 0, 1, 1, 1, 1, "ESTM_F25L32PA_32Mbit", 0x400000},
#endif
};

#define DEV_SIZE	(sizeof(device)/sizeof(t_device_type))

static t_device_type devicetype;

#define SPI_SAFE_OFFSET		0x100000
int sed_sfc_init (void)
{
#if defined (SIRIUS) || defined (FPGA)
	uint32 value;
	uint32 dst = SPI_BASE_ADDR + SPI_SAFE_OFFSET;

	/* Clock div */
	//REG32(SFC_SCK) = 0x1f;
	sed_pinmux_spi();
	/* Read device ID */
	sync();
	REG32(SFC_OPCODE) = CMD_OP_JEDEC_ID;
	sync();
	REG32(SFC_CTL) = DATA_EN;
	value = REG32(dst) & 0xFFFFFF00;

//	printf("Device ID: 0x%08X\n", value); //can be removed

	devicetype = device[0];

#if 0
	for (i = 0; i < DEV_SIZE; i++) {
		if (device[i].id == value) {
			devicetype = device[i];
			break;
		}
	}
#endif

	/* Read */
#if 1 /* For code size */
//	sync();
	REG32(SFC_OPCODE) = CMD_OP_READ;
//	sync();
	REG32(SFC_CTL) = DATA_EN|ADDR_EN;
#else
	if (devicetype.id == SST_8Mbit) {
		sync();
		REG32(SFC_OPCODE) = CMD_OP_READ;
		sync();
		REG32(SFC_CTL) = DATA_EN|ADDR_EN; //no need |0x1;
	} else {
		sync();
		REG32(SFC_OPCODE) = CMD_OP_FAST_READ;
		sync();
		REG32(SFC_CTL) = DATA_EN|ADDR_EN|0x1;
	}
#endif
//	if (i == DEV_SIZE) {
//		printf("sfc initial fail...\n"); //can be removed
//		return -1;
//	}
#if 0
	if (devicetype.id == EON_EN25QF256_256Mbit) {
		sync();
		REG32(SFC_OPCODE) = 0x0000001b;
		sync();
		REG32(SFC_CTL) = DATA_EN|ADDR_EN|0x1;
		REG32(SFC_32MB_EN) = 0x01;
	}
#endif

#else
	devicetype.string = "UNKNOWN"; //make compiler happy
#endif
	return 0;
}

int sed_sfc_read (uint32 offset, uint8 *buf, uint32 len)
{
#if defined (SIRIUS) || defined (FPGA)
	uint32 i;

	if (!buf || !len)
		return -1;

	for (i = 0; i < len; i++)
		buf[i] = REG8(SPI_BASE_ADDR + offset + i);
#endif
	return 0;
}

int sed_sfc_write (uint32 offset, uint8 *buf, uint32 len)
{
#if defined (SIRIUS) || defined (FPGA)
	uint32 value;
	uint32 src = (uint32) buf;
	uint32 dst = SPI_BASE_ADDR + offset;

	if (!buf || !len)
		return -1;

	/* Set HW write protect ?! */

	while (len--) {
		/* Write enable */
		sync();
		REG32(SFC_OPCODE) = CMD_OP_WRITE_EN;
		sync();
		REG32(SFC_CTL) = 0x00;
		value = REG8(dst);

		/* Byte program */
		sync();
		REG32(SFC_OPCODE) = CMD_OP_BYTE_PROG;
		sync();
		REG32(SFC_CTL) = DATA_EN|ADDR_EN;
		REG8(dst) = REG8(src);

		/* Read status register */
		do {
			sync();
			REG32(SFC_OPCODE) = CMD_OP_READ_STS;
			sync();
			REG32(SFC_CTL) = DATA_EN;
		} while ((value = REG8(dst)) & 0x1);

		/* Read */
#if 1 /* For code size */
		sync();
		REG32(SFC_OPCODE) = CMD_OP_READ;
		sync();
		REG32(SFC_CTL) = DATA_EN|ADDR_EN; //no need |0x1;
#else
		if (devicetype.id == SST_8Mbit) {
			sync();
			REG32(SFC_OPCODE) = CMD_OP_READ;
			sync();
			REG32(SFC_CTL) = DATA_EN|ADDR_EN; //no need |0x1;
		} else {
			sync();
			REG32(SFC_OPCODE) = CMD_OP_FAST_READ;
			sync();
			REG32(SFC_CTL) = DATA_EN|ADDR_EN|0x1;
		}
#endif

		if (REG8(dst) != REG8(src)) {
			//printf("sfc write fail...\n"); //can be removed
			return -1;
		}

		src++;
		dst++;
	}
#endif
	return 0;
}

int sed_sfc_erase (uint32 offset, uint32 len)
{
#if defined (SIRIUS) || defined (FPGA)
	uint32 size=0, value;
	uint32 dst = SPI_BASE_ADDR + offset;

	/* Set HW write protect ?! */

	while (len) {
		/* Write enable */
		sync();
		REG32(SFC_OPCODE) = CMD_OP_WRITE_EN;
		sync();
		REG32(SFC_CTL) = 0x00;
		value = REG8(dst);

		/* Erase sector */
		sync();
		if (len >= 0x40000) {
			if (devicetype.sec_256k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x40000;
			} else if (devicetype.sec_64k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x10000;
			} else if (devicetype.sec_32k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_32K_ERASE;
				size = 0x8000;
			} else if (devicetype.sec_4k_en == 1) {
				if (devicetype.id == PMC_4Mbit)
					REG32(SFC_OPCODE) = 0x000000d7;
				else
					REG32(SFC_OPCODE) = CMD_OP_4K_ERASE;
				size = 0x1000;
			}
		} else if ((0x40000 > len) && (len >= 0x10000)) {
			if (devicetype.sec_64k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x10000;
			} else if (devicetype.sec_32k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_32K_ERASE;
				size = 0x8000;
			} else if (devicetype.sec_4k_en == 1) {
				if (devicetype.id == PMC_4Mbit)
					REG32(SFC_OPCODE) = 0x000000d7;
				else
					REG32(SFC_OPCODE) = CMD_OP_4K_ERASE;
				size = 0x1000;
			} else if (devicetype.sec_256k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x40000;
			}
		} else if ((0x10000 > len) && (len >= 0x8000)) {
			if (devicetype.sec_32k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_32K_ERASE;
				size = 0x8000;
			} else if (devicetype.sec_4k_en == 1) {
				if (devicetype.id == PMC_4Mbit)
					REG32(SFC_OPCODE) = 0x000000d7;
				else
					REG32(SFC_OPCODE) = CMD_OP_4K_ERASE;
				size = 0x1000;
			} else if (devicetype.sec_64k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x10000;
			} else if (devicetype.sec_256k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x40000;
			}
		} else if (0x8000 > len) {
			if (devicetype.sec_4k_en == 1) {
				if (devicetype.id == PMC_4Mbit)
					REG32(SFC_OPCODE) = 0x000000d7;
				else
					REG32(SFC_OPCODE) = CMD_OP_4K_ERASE;
				size = 0x1000;
			} else if (devicetype.sec_32k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_32K_ERASE;
				size = 0x8000;
			} else if (devicetype.sec_64k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x10000;
			} else if (devicetype.sec_256k_en == 1) {
				REG32(SFC_OPCODE) = CMD_OP_64K_ERASE;
				size = 0x40000;
			}
		}
		sync();
		REG32(SFC_CTL) = ADDR_EN;
		value = REG8(dst);

		/* Read status register */
		do {
			sync();
			REG32(SFC_OPCODE) = CMD_OP_READ_STS;
			sync();
			REG32(SFC_CTL) = DATA_EN;
		} while ((value = REG8(dst)) & 0x1);

		/* Read */
#if 1 /* For code size */
		sync();
		REG32(SFC_OPCODE) = CMD_OP_READ;
		sync();
		REG32(SFC_CTL) = DATA_EN|ADDR_EN; //no need |0x1;
#else
		if (devicetype.id == SST_8Mbit) {
			sync();
			REG32(SFC_OPCODE) = CMD_OP_READ;
			sync();
			REG32(SFC_CTL) = DATA_EN|ADDR_EN; //no need |0x1;
		} else {
			sync();
			REG32(SFC_OPCODE) = CMD_OP_FAST_READ;
			sync();
			REG32(SFC_CTL) = DATA_EN|ADDR_EN|0x1;
		}
#endif
#if 0
		if (REG8(dst) != 0xFF) {
			printf("sfc erase fail...\n"); //can be removed
			return -1;
		}
#endif
		dst += size;
		size = (len > size)? size: len;
		len -= size;
	}
#endif
	return 0;
}

