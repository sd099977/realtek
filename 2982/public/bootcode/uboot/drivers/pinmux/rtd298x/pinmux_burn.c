
/************************************************************************
 *
 *  pinmux_burn.c
 *
 *  pinmux driver for rtd298x 
 *
 * 
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include <config.h>
#include <asm/io.h>

#include "rbus/mis_reg.h"
#include "rbus/iso_reg.h"
#include "rbus/crt_sys_reg.h"
#include "rbus/rbusPinmuxReg.h"


/************************************************************************
 *  Definitions
 ************************************************************************/
#define GPIO_MUXCFG_0   PINMUX_GPIO_CFG_0_VADDR
#define GPIO_MUXCFG_1   PINMUX_GPIO_CFG_1_VADDR
#define GPIO_MUXCFG_2   PINMUX_GPIO_CFG_2_VADDR
#define GPIO_MUXCFG_3   PINMUX_GPIO_CFG_3_VADDR
#define GPIO_MUXCFG_4   PINMUX_GPIO_CFG_4_VADDR
#define GPIO_MUXCFG_5   PINMUX_GPIO_CFG_5_VADDR
#define GPIO_MUXCFG_6   PINMUX_GPIO_CFG_6_VADDR
#define GPIO_MUXCFG_7   PINMUX_GPIO_CFG_7_VADDR
#define GPIO_MUXCFG_8   PINMUX_GPIO_CFG_8_VADDR
#define GPIO_MUXCFG_9   PINMUX_GPIO_CFG_9_VADDR
#define GPIO_MUXCFG_10  PINMUX_GPIO_CFG_10_VADDR
#define GPIO_MUXCFG_11  PINMUX_GPIO_CFG_11_VADDR
#define GPIO_MUXCFG_12  PINMUX_GPIO_CFG_12_VADDR
#define GPIO_MUXCFG_13  PINMUX_GPIO_CFG_13_VADDR
#define GPIO_MUXCFG_14  PINMUX_GPIO_CFG_14_VADDR
#define GPIO_MUXCFG_15  PINMUX_GPIO_CFG_15_VADDR
#define GPIO_MUXCFG_16  PINMUX_GPIO_CFG_16_VADDR
#define GPIO_MUXCFG_17  PINMUX_GPIO_CFG_17_VADDR
#define GPIO_MUXCFG_18  PINMUX_GPIO_CFG_18_VADDR
#define GPIO_MUXCFG_19  PINMUX_GPIO_CFG_19_VADDR
#define GPIO_MUXCFG_20  PINMUX_GPIO_CFG_20_VADDR
#define GPIO_MUXCFG_21  PINMUX_GPIO_CFG_21_VADDR
#define GPIO_MUXCFG_22  PINMUX_GPIO_CFG_22_VADDR
#define GPIO_MUXCFG_23  PINMUX_GPIO_CFG_23_VADDR
#define GPIO_MUXCFG_24  PINMUX_GPIO_CFG_24_VADDR
#define GPIO_MUXCFG_25  PINMUX_GPIO_CFG_25_VADDR
#define GPIO_MUXCFG_26  PINMUX_GPIO_CFG_26_VADDR
#define GPIO_MUXCFG_27  PINMUX_GPIO_CFG_27_VADDR
#define GPIO_MUXCFG_28  PINMUX_GPIO_CFG_28_VADDR
#define GPIO_MUXCFG_29  PINMUX_GPIO_CFG_29_VADDR
#define GPIO_MUXCFG_30  PINMUX_GPIO_CFG_30_VADDR
#define GPIO_MUXCFG_31  PINMUX_GPIO_CFG_31_VADDR
#define GPIO_MUXCFG_32  PINMUX_GPIO_CFG_32_VADDR
#define GPIO_MUXCFG_33  PINMUX_GPIO_CFG_33_VADDR
#define GPIO_MUXCFG_34  PINMUX_GPIO_CFG_34_VADDR
#define GPIO_MUXCFG_35  PINMUX_GPIO_CFG_35_VADDR
#define GPIO_MUXCFG_36  PINMUX_GPIO_CFG_36_VADDR
#define GPIO_MUXCFG_37  PINMUX_GPIO_CFG_37_VADDR
#define GPIO_MUXCFG_38  PINMUX_GPIO_CFG_38_VADDR
#define GPIO_MUXCFG_39  PINMUX_GPIO_CFG_39_VADDR
#define GPIO_MUXCFG_40  PINMUX_GPIO_CFG_40_VADDR
#define GPIO_MUXCFG_41  PINMUX_GPIO_CFG_41_VADDR
#define GPIO_MUXCFG_42  PINMUX_GPIO_CFG_42_VADDR
#define GPIO_MUXCFG_43  PINMUX_GPIO_CFG_43_VADDR
#define GPIO_MUXCFG_44  PINMUX_GPIO_CFG_44_VADDR
#define GPIO_MUXCFG_45  PINMUX_GPIO_CFG_45_VADDR
#define GPIO_MUXCFG_46  PINMUX_GPIO_CFG_46_VADDR
#define GPIO_MUXCFG_47  PINMUX_GPIO_CFG_47_VADDR
#define GPIO_MUXCFG_48  PINMUX_GPIO_CFG_48_VADDR
#define GPIO_MUXCFG_49  PINMUX_GPIO_CFG_49_VADDR
#define GPIO_MUXCFG_50  PINMUX_GPIO_CFG_50_VADDR


#define ISO_GPDIR1  ISO_GPDIR_1_reg
#define ISO_GPDATO1 ISO_GPDATO_1_reg
#define ISO_GPDATI1 ISO_GPDATI_1_reg

#define BB_USB_CFG_1   PINMUX_BB_USB_CFG_1_VADDR
#define PIN_MUX_CTRL6  PINMUX_PIN_MUX_CTRL6_VADDR

#define SYS_GROUP1_CK_EN CRT_GROUP1_CK_EN_VADDR

#define ST_PINMUX_REG_BASE		0x18060200

#define GPIO_ST_MUXCFG_0		(ST_PINMUX_REG_BASE + 0x00)
#define GPIO_ST_MUXCFG_1		(ST_PINMUX_REG_BASE + 0x04)
#define GPIO_ST_MUXCFG_2		(ST_PINMUX_REG_BASE + 0x08)
#define GPIO_ST_MUXCFG_3		(ST_PINMUX_REG_BASE + 0x0c)
#define GPIO_ST_MUXCFG_4		(ST_PINMUX_REG_BASE + 0x10)
#define GPIO_ST_MUXCFG_5		(ST_PINMUX_REG_BASE + 0x14)
#define GPIO_ST_MUXCFG_6		(ST_PINMUX_REG_BASE + 0x18)
#define GPIO_ST_MUXCFG_7		(ST_PINMUX_REG_BASE + 0x1c)
#define GPIO_ST_MUXCFG_8		(ST_PINMUX_REG_BASE + 0x24)
#define GPIO_ST_MUXCFG_9		(ST_PINMUX_REG_BASE + 0x28)
#define GPIO_ST_MUXCFG_10		(ST_PINMUX_REG_BASE + 0x2c)
#define GPIO_ST_MUXCFG_11		(ST_PINMUX_REG_BASE + 0x30)
#define GPIO_ST_MUXCFG_12		(ST_PINMUX_REG_BASE + 0x34)
#define GPIO_ST_MUXCFG_13		(ST_PINMUX_REG_BASE + 0x38)
#define GPIO_ST_MUXCFG_14		(ST_PINMUX_REG_BASE + 0x3c)
#define GPIO_ST_MUXCFG_15		(ST_PINMUX_REG_BASE + 0x40)
#define GPIO_ST_MUXCFG_16		(ST_PINMUX_REG_BASE + 0x44)
#define GPIO_ST_MUXCFG_17		(ST_PINMUX_REG_BASE + 0x48)
#define GPIO_ST_MUXCFG_18		(ST_PINMUX_REG_BASE + 0x4c)

#define ST_PIN_MUX_CTRL0		(ST_PINMUX_REG_BASE + 0xa0)



// see "Main_Sirius_PinMux.doc"
#define PINMUX_REG_BASE		0x18000800

#define PIN_MUX_CTRL0 		(PINMUX_REG_BASE + 0xc0)
#define PIN_MUX_CTRL1 		(PINMUX_REG_BASE + 0xc4)
#define PIN_MUX_CTRL2 		(PINMUX_REG_BASE + 0xc8)


/*
#define PINMUX_PIN_MUX_CTRL0_VADDR                 (0xb80008fc)
#define PINMUX_PIN_MUX_CTRL1_VADDR                 (0xb8000900)
#define PINMUX_PIN_MUX_CTRL2_VADDR                 (0xb8000904)
*/


/* HW POL/SW POL/Boption */
#define NAND_TV176_LQFP		0
#define NAND_TV256_LQFP_CASE_2_3_5	1
#define NAND_TV_BGA		1
#define NAND_BOX176_LQFP_CASE_1_4_5_6_8	2

#define EMMC_TV176_LQFP		0
#define EMMC_TV256_LQFP_CASE_2_3_4_5	0
#define EMMC_TV_BGA		0
#define EMMC_TV256_LQFP_CASE_1	1
#define EMMC_BOX176_LQFP_CASE_2	2
#define EMMC_BOX176_LQFP_CASE_4_5	3
#define EMMC_BOX176_LQFP_CASE_7	4
#define EMMC_BOX176_LQFP_CASE_8	5
#define EMMC_TV_BGA_LGE		6
#define EMMC_TV_BGA_CHINA	7

//booting flash type
#define NAND_FLASH_BOOT		0
#define SPI_FLASH_BOOT		1
#define EMMC_BOOT		2
#define SPI_NAND_FLASH_BOOT	3
#define UNKNOWN_BOOT		(-1)

#define mask_register rtd_maskl
#define REG32(addr)		  (*(volatile unsigned int *)(addr))

/************************************************************************
 *  External function prototypes
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

static void set_nand_pin_mux(int type_select)
{
#if defined(_DEBUG)
	prints("\n%s", __FUNCTION__);
#endif

	unsigned int inverse;

	if (type_select == NAND_TV176_LQFP) {
		// set GPIO_35_ps to NF_CE0, 0x1800_0828[13:9 ] = 0x00 (NF)
		inverse = (0x1f << 9);
		mask_register(GPIO_MUXCFG_10, ~inverse, 0);
	}

	// set GPIO_39_ps to NF_CLE, 0x1800_0830[31:27] = 0x00 (NF)
	// set GPIO_40_ps to NF_WR , 0x1800_0830[22:18] = 0x00 (NF)
	inverse = (0x1f << 27) | (0x1f << 18);
	if (type_select == NAND_BOX176_LQFP_CASE_1_4_5_6_8) {
		// set GPIO_41_ps to NF_CE0, 0x1800_0830[13:9] = 0x00 (NF)
		inverse |= (0x1f << 9);
	}
	mask_register(GPIO_MUXCFG_12, ~inverse, 0);

	// set GPIO_42_ps to NF_ALE, 0x1800_0834[31:27] = 0x00 (NF)
	// set GPIO_44_ps to NF_D0 , 0x1800_0834[13:9 ] = 0x00 (NF)
	inverse = (0x1f << 27) | (0x1f << 9);
	mask_register(GPIO_MUXCFG_13, ~inverse, 0);

	// set GPIO_45_ps to NF_D1 , 0x1800_0838[31:27] = 0x00 (NF)
	// set GPIO_46_ps to NF_D2 , 0x1800_0838[22:18] = 0x00 (NF)
	// set GPIO_47_ps to NF_D3 , 0x1800_0838[13:9 ] = 0x00 (NF)
	inverse = (0x1f << 27) | (0x1f << 18) | (0x1f << 9);
	mask_register(GPIO_MUXCFG_14, ~inverse, 0);

	// set GPIO_48_ps to NF_D4 , 0x1800_083c[31:27] = 0x00 (NF)
	// set GPIO_49_ps to NF_D5 , 0x1800_083c[22:18] = 0x00 (NF)
	// set GPIO_50_ps to NF_D6 , 0x1800_083c[13:9 ] = 0x00 (NF)
	inverse = (0x1f << 27) | (0x1f << 18) | (0x1f << 9);
	mask_register(GPIO_MUXCFG_15, ~inverse, 0);

	// set GPIO_51_ps to NF_D7 , 0x1800_0840[31:27] = 0x00 (NF)
	inverse = (0x1f << 27);
	if ((type_select == NAND_TV176_LQFP) || (type_select == NAND_TV256_LQFP_CASE_2_3_5) || (type_select == NAND_TV_BGA)) {
		// set GPIO_52_ps to NF_RD , 0x1800_0840[22:18] = 0x00 (NF)
		inverse |= (0x1f << 18);
	}
	mask_register(GPIO_MUXCFG_16, ~inverse, 0);

	// set GPIO_56_ps to NF_RDY, 0x1800_0844[13:9 ] = 0x00 (NF)
	inverse = (0x1f << 9);
	if ((type_select == NAND_TV256_LQFP_CASE_2_3_5) || (type_select == NAND_TV_BGA)) {
		// set GPIO_55_ps to NF_CE0 , 0x1800_0844[22:18] = 0x00 (NF)
		inverse |= (0x1f << 18);
	}
	mask_register(GPIO_MUXCFG_17, ~inverse, 0);

	if (type_select == NAND_BOX176_LQFP_CASE_1_4_5_6_8) {
		// set GPIO_143_ps to NF_RD , 0x1800_0848[31:27] = 0x00 (NF)
		inverse = (0x1f << 27);
		mask_register(GPIO_MUXCFG_18, ~inverse, 0);
	}
}

static void set_spi_pin_mux(const unsigned int gpio_value)
{
#if defined(_DEBUG)
	prints("\n%s", __FUNCTION__);
#endif

	unsigned int reg_val;
	unsigned int tmp;

	// set GPIO_39_ps to SPI_SCLK , 0x1800_0830[31:27] = 0x01 (SPI) or 0x15 (SPI-NAND)
	// set GPIO_40_ps to SPI_DI   , 0x1800_0830[22:18] = 0x01 (SPI) or 0x15 (SPI-NAND)
	// set GPIO_41_ps to SPI_CS_N , 0x1800_0830[13:9 ] = 0x01 (SPI) or 0x15 (SPI-NAND)
	tmp = (gpio_value << 27) | (gpio_value << 18) | (gpio_value << 9);
	reg_val = (REG32(GPIO_MUXCFG_12) & 0x0783c1ff) | tmp;
	REG32(GPIO_MUXCFG_12) = reg_val; 

	// set GPIO_42_ps to SPI_DO   , 0x1800_0834[31:27] = 0x01 (SPI) or 0x15 (SPI-NAND)
	tmp = (gpio_value << 27);
	reg_val = (REG32(GPIO_MUXCFG_13) & 0x07ffffff) | tmp;
	REG32(GPIO_MUXCFG_13) = reg_val;
}

static void set_emmc_pin_mux(int type_select)
{
#if defined(_DEBUG)
	prints("\n%s", __FUNCTION__);
#endif

	unsigned int inverse;
	unsigned int assert_bits;
	unsigned int clk_workaround;

	//printf("\n%s type_select = %d\n", __FUNCTION__, type_select);


	// see Mantis 55208 for this workaround
	clk_workaround = REG32(SYS_GROUP1_CK_EN);
	REG32(SYS_GROUP1_CK_EN) |= (0x1 << 29);

	if (type_select == EMMC_TV_BGA_CHINA) {
		// set GPIO_184_ps to eMMC_D0 , 0x1800_0888[22:18] = 0x02 (eMMC)
		// set GPIO_185_ps to eMMC_D1 , 0x1800_0888[13:9 ] = 0x02 (eMMC)
		inverse = (0x1f << 18) | (0x1f << 9);
		assert_bits = (0x2 << 18) | (0x2 << 9);
		mask_register(GPIO_MUXCFG_34, ~inverse, assert_bits);

		// set GPIO_181_ps to eMMC_D2 , 0x1800_0884[22:18] = 0x02 (eMMC)
		// set GPIO_182_ps to eMMC_D7 , 0x1800_0884[13:9 ] = 0x02 (eMMC)
		mask_register(GPIO_MUXCFG_33, ~inverse, assert_bits);

		// set GPIO_153_ps to eMMC_D3 , 0x1800_08a0[22:18] = 0x02 (eMMC)
		// set GPIO_152_ps to eMMC_D4 , 0x1800_08a0[31:27] = 0x02 (eMMC)
		inverse = (0x1f << 27) | (0x1f << 18);
		assert_bits = (0x2 << 27) | (0x2 << 18);
		mask_register(GPIO_MUXCFG_40, ~inverse, assert_bits);

		// set GPIO_188_ps to eMMC_D5 , 0x1800_088c[13:9 ] = 0x02 (eMMC)
		inverse = (0x1f << 9);
		assert_bits = (0x2 << 9);
		mask_register(GPIO_MUXCFG_35, ~inverse, assert_bits);

		// set GPIO_169_ps to eMMC_D6 , 0x1800_0874[22:18] = 0x02 (eMMC)
		inverse = (0x1f << 18);
		assert_bits = (0x2 << 18);
		mask_register(GPIO_MUXCFG_29, ~inverse, assert_bits);
	}
	else {
		// set GPIO_44_ps to eMMC_D0 , 0x1800_0834[13:9 ] = 0x02 (eMMC)
		inverse = (0x1f << 9);
		assert_bits = (0x2 << 9);
		mask_register(GPIO_MUXCFG_13, ~inverse, assert_bits);

		// set GPIO_45_ps to eMMC_D1 , 0x1800_0838[31:27] = 0x02 (eMMC)
		// set GPIO_46_ps to eMMC_D2 , 0x1800_0838[22:18] = 0x02 (eMMC)
		// set GPIO_47_ps to eMMC_D3 , 0x1800_0838[13:9 ] = 0x02 (eMMC)
		inverse = (0x1f << 27) | (0x1f << 18) | (0x1f << 9);
		assert_bits = (0x2 << 27) | (0x2 << 18) | (0x2 << 9);
		mask_register(GPIO_MUXCFG_14, ~inverse, assert_bits);

		// set GPIO_48_ps to eMMC_D4 , 0x1800_083c[31:27] = 0x02 (eMMC)
		// set GPIO_49_ps to eMMC_D5 , 0x1800_083c[22:18] = 0x02 (eMMC)
		// set GPIO_50_ps to eMMC_D6 , 0x1800_083c[13:9 ] = 0x02 (eMMC)
		mask_register(GPIO_MUXCFG_15, ~inverse, assert_bits);

		// set GPIO_51_ps to eMMC_D7 , 0x1800_0840[31:27] = 0x02 (eMMC)
		inverse = (0x1f << 27);
		assert_bits = (0x2 << 27);
		mask_register(GPIO_MUXCFG_16, ~inverse, assert_bits);
	}

	if (type_select == EMMC_TV_BGA_CHINA) {
		// set GPIO_150_ps to eMMC_CMD, 0x1800_0958[22:18] = 0x02 (eMMC)
		inverse = (0x1f << 18);
		assert_bits = (0x2 << 18);
		mask_register(GPIO_MUXCFG_50, ~inverse, assert_bits);
	}
	else if (type_select == EMMC_BOX176_LQFP_CASE_8) {
		// set ST_GPIO_42_ps to eMMC_CMD, 0x1806_0228[13:9 ] = 0x01 (eMMC)
		inverse = (0x1f << 9);
		assert_bits = (0x1 << 9);
		mask_register(GPIO_ST_MUXCFG_9, ~inverse, assert_bits);
	}
	else {
		// set GPIO_56_ps to eMMC_CMD, 0x1800_0844[13:9 ] = 0x02 (eMMC)
		inverse = (0x1f << 9);
		assert_bits = (0x2 << 9);
		mask_register(GPIO_MUXCFG_17, ~inverse, assert_bits);
	}

	switch(type_select) {
		case EMMC_TV176_LQFP:	// same as EMMC_TV256_LQFP_CASE_2_3_4_5, EMMC_TV_BGA
			// set ST_GPIO_12_ps to eMMC_CLK, 0x1806_0248[31:27] = 0x01 (eMMC)
			inverse = (0x1f << 27);
			assert_bits = (0x1 << 27);
			mask_register(GPIO_ST_MUXCFG_17, ~inverse, assert_bits);

			// set BB_DIO_3_ps to eMMC_RST_N, 0x1800_08f8[31:27] = 0x1f (gpio)
			inverse = (0x1f << 27);
			assert_bits = (0x1f << 27);
			mask_register(BB_USB_CFG_1, ~inverse, assert_bits);
			break;

		case EMMC_TV256_LQFP_CASE_1:
			// set GPIO_52_ps to eMMC_CLK, 0x1800_0840[22:18] = 0x02 (eMMC)
			inverse = (0x1f << 18);
			assert_bits = (0x2 << 18);
			mask_register(GPIO_MUXCFG_16, ~inverse, assert_bits);

			// set GPIO_55_ps to eMMC_RST_N, 0x1800_0844[22:18] = 0x02 (gpio)
			mask_register(GPIO_MUXCFG_17, ~inverse, assert_bits);
			break;

		case EMMC_BOX176_LQFP_CASE_2:
			// set GPIO_143_ps to eMMC_CLK, 0x1800_0848[31:27] = 0x02 (eMMC)
			inverse = (0x1f << 27);
			assert_bits = (0x2 << 27);
			mask_register(GPIO_MUXCFG_18, ~inverse, assert_bits);

			// set GPIO_40_ps to eMMC_RST_N, 0x1800_0830[22:18] = 0x1f (gpio)
			inverse = (0x1f << 18);
			assert_bits = (0x1f << 18);
			mask_register(GPIO_MUXCFG_12, ~inverse, assert_bits);
			break;

		case EMMC_BOX176_LQFP_CASE_4_5:
			// set ST_GPIO_12_ps to eMMC_CLK, 0x1806_0248[31:27] = 0x01 (eMMC)
			inverse = (0x1f << 27);
			assert_bits = (0x1 << 27);
			mask_register(GPIO_ST_MUXCFG_17, ~inverse, assert_bits);

			// set GPIO_97_ps to eMMC_RST_N, 0x1800_0860[13:9 ] = 0x1f (gpio)
			inverse = (0x1f << 9);
			assert_bits = (0x1f << 9);
			mask_register(GPIO_MUXCFG_24, ~inverse, assert_bits);
			break;

		case EMMC_BOX176_LQFP_CASE_7:
			// set GPIO_39_ps to eMMC_CLK, 0x1800_0830[31:27] = 0x02 (eMMC)
			inverse = (0x1f << 27);
			assert_bits = (0x2 << 27);
			mask_register(GPIO_MUXCFG_12, ~inverse, assert_bits);

			// set GPIO_42_ps to eMMC_RST_N, 0x1800_0834[31:27] = 0x1f (gpio)
			assert_bits = (0x1f << 27);
			mask_register(GPIO_MUXCFG_13, ~inverse, assert_bits);
			break;

		case EMMC_BOX176_LQFP_CASE_8:
			// set ST_GPIO_43_ps to eMMC_CLK, 0x1806_0228[22:18] = 0x01 (eMMC)
			// set ST_GPIO_44_ps to eMMC_RST_N, 0x1806_0228[31:27] = 0x1f (gpio)
			inverse = (0x1f << 27) | (0x1f << 18);
			assert_bits = (0x1f << 27) | (0x1 << 18);
			mask_register(GPIO_ST_MUXCFG_9, ~inverse, assert_bits);
			break;

		case EMMC_TV_BGA_LGE:
			// set GPIO_85_ps to eMMC_CLK, 0x1800_0850[13:9 ] = 0x02 (eMMC)
			inverse = (0x1f << 9);
			assert_bits = (0x2 << 9);
			mask_register(GPIO_MUXCFG_20, ~inverse, assert_bits);

			// set BB_DIO_3_ps to eMMC_RST_N, 0x1800_08f8[31:27] = 0x1f (eMMC_RST)
			inverse = (0x1f << 27);
			assert_bits = (0x1f << 27);
			mask_register(BB_USB_CFG_1, ~inverse, assert_bits);
			break;

		case EMMC_TV_BGA_CHINA:
			// set GPIO_157_ps to eMMC_CLK, 0x1800_08a4[13:9 ] = 0x02 (eMMC)
			inverse = (0x1f << 9);
			assert_bits = (0x2 << 9);
			mask_register(GPIO_MUXCFG_41, ~inverse, assert_bits);

			// set GPIO_151_ps to eMMC_RST_N, 0x1800_089c[13:9 ] = 0x1f (eMMC)
			inverse = (0x1f << 9);
			assert_bits = (0x1f << 9);
			mask_register(GPIO_MUXCFG_39, ~inverse, assert_bits);
			break;

		default:	// should not happened 
			break;
	}

	// set input mux in 0x1800_0914
	switch(type_select) {
		case EMMC_TV176_LQFP:
		case EMMC_TV256_LQFP_CASE_1:
		case EMMC_TV_BGA_LGE:
		case EMMC_BOX176_LQFP_CASE_2:
		case EMMC_BOX176_LQFP_CASE_4_5:
		case EMMC_BOX176_LQFP_CASE_7:
			// [30:28] = 0x1
			// [27:26], [25:24], [23:22], [21:20], [19:18], [16:15], [14:13], [12:11] = 0x0
			assert_bits = 0x10000000;
			break;
		case EMMC_BOX176_LQFP_CASE_8:
			// [30:28] = 0x2
			// [27:26], [25:24], [23:22], [21:20], [19:18], [16:15], [14:13], [12:11] = 0x0
			assert_bits = 0x20000000;
			break;
		case EMMC_TV_BGA_CHINA:
			// [30:28] = 0x6
			// [27:26], [25:24], [23:22], [21:20], [19:18], [16:15], [14:13], [12:11] = 0x2
			assert_bits = 0x6aa95000;
			break;
		default:
			assert_bits = 0;
			break;
	}
	inverse = 0x7ffdf800;
	mask_register(PIN_MUX_CTRL6, ~inverse, assert_bits);

	REG32(SYS_GROUP1_CK_EN) = clk_workaround;
}

/*
 * TV176/others check from GPIO
 *	0: TV176_LQFP
 *	1: others package
 */
int get_tv176_others_check_value(void)
{
	int res = 0;
	unsigned int pin_mux;
	unsigned int gpio_dir;

	pin_mux = REG32(GPIO_MUXCFG_45);	// save pin mux
	gpio_dir = REG32(MIS_GP5DIR);		// save GPIO direction
	REG32(GPIO_MUXCFG_45) |= (0x1f << 27);	// set gpio_167_ps = 0x1f
	REG32(MIS_GP5DIR) &= ~(0x1 << 7);	// set GPIO 167 as input pin, [7] = 0
	res = (REG32(MIS_GP5DATI) >> 7) & 0x1;	// get from GPIO 167
	REG32(MIS_GP5DIR) = gpio_dir;		// restore GPIO direction
	REG32(GPIO_MUXCFG_45) = pin_mux;	// restore pin mux
	printf("\n%s res = %d\n", __FUNCTION__, res);	
	return res;
}

/*
 * get different NAND/eMMC type from GPIO
 */
int get_nand_emmc_type_select(const int flash_type)
{
#if defined(_DEBUG)
	prints("\n%s", __FUNCTION__);
#endif

	int res;
	unsigned int pin_mux;
	unsigned int gpio_dir;

	if (get_tv176_others_check_value() == 0) {
		if (flash_type == NAND_FLASH_BOOT)
			return NAND_TV176_LQFP;
		else
			return EMMC_TV176_LQFP;
	}

	/*
	 * from "Sirius ROM CODE.ppt"
	 *-----------------------------------------
	 * BOOT_TYPE_bit0 from PAD_GPIO_20 as bit0
	 * BOOT_TYPE_bit1 from PAD_GPIO_21 as bit1
	 * BOOT_TYPE_bit2 from PAD_GPIO_22 as bit2
	 *-----------------------------------------
	 * 000 -> EMMC: TV256_LQFP Case 2,3,4,5
	 *              TV_BGA
	 * 001 -> NAND: TV256_LQFP Case 2,3,5
	 *              TV_BGA
	 *        EMMC: TV256_LQFP Case 1
	 * 010 -> NAND: BOX176_LQFP Case 1,4,5,6,8
	 *        EMMC: BOX176_LQFP Case 2
	 * 011 -> EMMC: BOX176_LQFP Case 4,5
	 * 100 -> EMMC: BOX176_LQFP Case 7
	 * 101 -> EMMC: BOX176_LQFP Case 8
	 * 110 -> EMMC: TV_BGA_LGE
	 * 111 -> EMMC: TV_BGA_CHINA
	 */
	
	/* get boot_type (from GPIO) */
	pin_mux = REG32(GPIO_MUXCFG_7);	// save pin mux
	gpio_dir = REG32(MIS_GP0DIR);	// save GPIO direction
	REG32(GPIO_MUXCFG_7) = pin_mux | (0x1f << 27) | (0x1f << 18) | (0x1f << 9);	// set gpio_20_ps = 0x1f, gpio_21_ps = 0x1f, gpio_22_ps = 0x1f
	REG32(MIS_GP0DIR) &= ~(0x7 << 22);	// set GPIO 20/21/22 as input pin, [22:20] = 0
	res = (REG32(MIS_GP0DATI) >> 20) & 0x7;	// get boot_type type from GPIO [22:20]
	REG32(MIS_GP0DIR) = gpio_dir;	// restore GPIO direction
	REG32(GPIO_MUXCFG_7) = pin_mux;	// restore pin mux

	printf("\n%s res = %d\n", __FUNCTION__, res);
	return res;
}

int set_pin_mux_force(const int flash_type)
{
#if defined(_DEBUG)
	prints("\n%s", __FUNCTION__);
#endif

	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
		case SPI_NAND_FLASH_BOOT:
			set_spi_pin_mux(0x01);
			break;
			
		case NAND_FLASH_BOOT:
			set_nand_pin_mux(get_nand_emmc_type_select(flash_type));			
			break;
		
		case EMMC_BOOT:
			printf("\nEMMC boot\n");
#if defined(Config_Package_type_EMMC_TV176_LQFP)
			printf("\nEMMC_TV176_LQFP\n"); 			
			//set_emmc_pin_mux(EMMC_TV176_LQFP);
			REG32(0x18000914) = (REG32(0x18000914) & 0x000000ff) |0x10000000;	// EMMC_Source control reg(176/256 QFP)
			REG32(0x18060248) = (REG32(0x18060248) & 0x00ffffff) |0x08000000;	// EMMC_CLK st_gpio_12	
			REG32(0x18000844) = (REG32(0x18000844) & 0xffffc000) |0x00000400;	// EMMC_CMD gpio_56 
			REG32(0x18000834) = (REG32(0x18000834) & 0xffffc000) |0x00000400;	// EMMC_DAT0 gpio_44 
			REG32(0x18000838) = (REG32(0x18000838) & 0x00000000) |0x10080400;	// EMMC_DAT1/2/3 gpio_45/46/47 
			REG32(0x1800083c) = (REG32(0x1800083c) & 0x00000000) |0x10080400;	// EMMC_DAT4/5/6 gpio_48/49/50 
			REG32(0x18000840) = (REG32(0x18000840) & 0x007fffff) |0x10000000;	// EMMC_DAT7 gpio_51
			REG32(0x180008F8) = (REG32(0x180008F8) & 0xffc1ffff) |0x003e0000;	//EMMC_RST_N 0x1800_08F8[21:17]=0x1F	bb_dio3_ps	GPIO196
#elif defined(Config_Package_type_EMMC_TV_BGA_CA)
			printf("\nEMMC_TV_BGA_CA\n");			
			set_emmc_pin_mux(EMMC_TV_BGA_CHINA);
#else
			printf("\n[Warning] no package type defined\n");
			printf("\nchange to default EMMC_TV176_LQFP\n");			
			REG32(0x18000914) = (REG32(0x18000914) & 0x000000ff) |0x10000000;	// EMMC_Source control reg(176/256 QFP)
			REG32(0x18060248) = (REG32(0x18060248) & 0x00ffffff) |0x08000000;	// EMMC_CLK st_gpio_12	
			REG32(0x18000844) = (REG32(0x18000844) & 0xffffc000) |0x00000400;	// EMMC_CMD gpio_56 
			REG32(0x18000834) = (REG32(0x18000834) & 0xffffc000) |0x00000400;	// EMMC_DAT0 gpio_44 
			REG32(0x18000838) = (REG32(0x18000838) & 0x00000000) |0x10080400;	// EMMC_DAT1/2/3 gpio_45/46/47 
			REG32(0x1800083c) = (REG32(0x1800083c) & 0x00000000) |0x10080400;	// EMMC_DAT4/5/6 gpio_48/49/50 
			REG32(0x18000840) = (REG32(0x18000840) & 0x007fffff) |0x10000000;	// EMMC_DAT7 gpio_51
			REG32(0x180008F8) = (REG32(0x180008F8) & 0xffc1ffff) |0x003e0000;	//EMMC_RST_N 0x1800_08F8[21:17]=0x1F	bb_dio3_ps	GPIO196
#endif
			break;

		case UNKNOWN_BOOT:
		default:
			res = -1;
			break;
	}

	return res;
}

int set_pin_mux_auto(const int flash_type)
{
#if defined(_DEBUG)
	prints("\n%s", __FUNCTION__);
#endif

	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
		case SPI_NAND_FLASH_BOOT:
			set_spi_pin_mux(0x01);
			break;
		case NAND_FLASH_BOOT:
			set_nand_pin_mux(get_nand_emmc_type_select(flash_type));
			break;
		
		case EMMC_BOOT:
			set_emmc_pin_mux(get_nand_emmc_type_select(flash_type));
			break;

		case UNKNOWN_BOOT:
		default:
			res = -1;
			break;
	}

	return res;
}

int set_pin_mux_burn()
{
#if defined(_DEBUG)
	prints("\n%s", __FUNCTION__);
#endif

	int flash_type;

#if defined(CONFIG_SYS_RTK_EMMC_FLASH)
	flash_type = EMMC_BOOT;
	printf("\n%s() flash: eMMC\n", __FUNCTION__);
#elif defined(CONFIG_SYS_RTK_NAND_FLASH)
	flash_type = NAND_FLASH_BOOT;
	printf("\n%s() flash: NAND\n", __FUNCTION__);
#else
#error "error! flash type for pinmux burn not defined!"
#endif

	int res = 0;

#if 0
	unsigned int chip_id;
	chip_id = REG32(0x18060000);
	
	// check chip version
	switch (chip_id & 0xffff) {
		case 0x0001:
			printf("\npin mux auto\n");
			res = set_pin_mux_auto(flash_type);
			break;
		case 0x0000:
		default:
			printf("\npin mux force\n");
			res = set_pin_mux_force(flash_type);
			break;
	}
#else
	printf("\npin mux auto\n");
	res = set_pin_mux_auto(flash_type);
#endif
	return res;
}
