
/************************************************************************
 *
 *  pinmux_mac2.c
 *
 *  pinmux driver for mac2 
 *
 * 
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include "util.h"
#include "mcp.h"
#include "error_type.h"

#include "otp_reg_rtd298x.h"
#include "mis_reg_rtd298x.h"
#include "sys_reg_rtd298x.h"
#include "iso_reg_rtd298x.h"
#include "pin_share_reg_rtd298x.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
//#define ROM_DEBUG

//this is used for realchip simulation
#ifdef FPGA
#undef FPGA
#endif

//this is used for realchip simulation
#ifdef CONFIG_ENV_FPGA
#undef CONFIG_ENV_FPGA
#endif
/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern void enable_uart_tx(void);

/************************************************************************
 *  Function body
 ************************************************************************/

static void set_nand_pin_mux(int type_select)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
#endif

#if !defined(FPGA) && !defined(CONFIG_ENV_FPGA)
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
#endif /* end of !defined(FPGA) && !defined(CONFIG_ENV_FPGA) */
}

static void set_spi_pin_mux(const unsigned int gpio_value)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
#endif

#if !defined(FPGA) && !defined(CONFIG_ENV_FPGA)
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

#endif /* end of !defined(FPGA) && !defined(CONFIG_ENV_FPGA) */
}

static void set_emmc_pin_mux(int type_select)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
#endif

#if !defined(FPGA) && !defined(CONFIG_ENV_FPGA)
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
#endif /* end of !defined(FPGA) && !defined(CONFIG_ENV_FPGA) */
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
	//printf("\n%s res = %d\n", __FUNCTION__, res);	
	return res;
}

/*
 * get different NAND/eMMC type from GPIO
 */
int get_nand_emmc_type_select(const int flash_type)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
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
	int res;

#ifdef ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif
	res = 0;

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
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

int set_pin_mux_auto(const int flash_type)
{
	int res;

#ifdef ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif
	res = 0;

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
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

int set_pin_mux(const int flash_type)
{
	int res = 0;

#ifdef ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

#if !defined(FPGA) && !defined(CONFIG_ENV_FPGA)
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
#endif

	return res;
}

void set_uart_rx_pin_mux(void)
{
	//(see Main_Sirius_PinMux.doc, PMM_Sirius_PinMux.doc)
#if !defined(FPGA) && !defined(CONFIG_ENV_FPGA)
	//unsigned int reg_val;
	unsigned int inverse;

	/* set UART0_rxdi_in_sel pin mux */
	/* UART0_rxdi_sel [18:16] -> "0: uart0_rxdi_src0 (vddc_scl_ps)" */
	inverse = (0x7 << 16);
	//reg_val = REG32(ST_PIN_MUX_CTRL0) & ~inverse;
	//REG32(ST_PIN_MUX_CTRL0) = reg_val;
	mask_register(ST_PIN_MUX_CTRL0, ~inverse, 0);

	/* set Vddc_scl_ps pin mux */
	/* Vddc_scl_ps [13:9 ] -> "9: uart0_rxdi_src0,<I>" */
	inverse = (0x1f << 9);
	//reg_val = REG32(GPIO_ST_MUXCFG_0) & ~inverse;
	//REG32(GPIO_ST_MUXCFG_0) = reg_val | (0x9 << 9);
	mask_register(GPIO_ST_MUXCFG_0, ~inverse, (0x9 << 9));

	/* set uart1_rxdi_in_sel pin mux */
	/* uart1_rxdi_sel [22:20] -> "0: uart1_rxdi_src0(gpio_53_ps)" */
	inverse = (0x7 << 20);
	//reg_val = REG32(PIN_MUX_CTRL0) & ~inverse;
	//REG32(PIN_MUX_CTRL0) = reg_val;
	mask_register(PIN_MUX_CTRL0, ~inverse, 0);

	/* set gpio_53_ps  pin mux */
	/* gpio_53_ps  [13:9 ] -> "2: uart1_rxdi_src0,<I>" */
	inverse = (0x1f << 9);
	//reg_val = REG32(GPIO_MUXCFG_16) & ~inverse;
	//REG32(GPIO_MUXCFG_16) = reg_val | (0x2 << 9);
	mask_register(GPIO_MUXCFG_16, ~inverse, (0x2 << 9));

#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	//enable_uart_tx();	// for debug use
#endif

#endif /* end of if !defined(FPGA) && !defined(#ifndef CONFIG_ENV_FPGA) */
}

/*
 * This function switch UART TX to GPI,
 * main purpose is to detect UART TX toggled by VGA DDC in check_recovery() function
 *
 */
void set_recovery_uart(void)
{
#if !defined(FPGA) && !defined(CONFIG_ENV_FPGA)

	//unsigned int reg_val;
	unsigned inverse;

	/* set vddc_sda_ps pin mux */
	/* 	vddc_sda_ps [31:27] -> "F: ISO_MIS_GPIO_bit14,<I/O>" */
	inverse = (0x1f << 27);
	//reg_val = REG32(GPIO_ST_MUXCFG_1) & 0x07ffffff;
	//REG32(GPIO_ST_MUXCFG_1) = reg_val | (0xf << 27);
	mask_register(GPIO_ST_MUXCFG_1, ~inverse, (0xf << 27));

	/* set gpio_54_ps pin mux */
	/* gpio_54_ps	[31:27] -> "F: ISO_MIS_GPIO_bit54,<I/O>" */
	//reg_val = REG32(GPIO_MUXCFG_17) & 0x07ffffff;
	//REG32(GPIO_MUXCFG_17) = reg_val | (0xf << 27);
	mask_register(GPIO_MUXCFG_17, ~inverse, (0xf << 27));

	/* clear GPIO ASSERT & DEASSERT Pending BIT (write 1 to clear) */
	//UART0 -> ISO_MIS_GPIO_bit14 -> INT14_A[15]
	//UART1 -> MIS_GPIO_bit54 -> INT15_A[24]
	REG32(ISO_ISR_GP0A) = (1 << 15);
	REG32(ISO_ISR_GP0DA) = (1 << 15);
	REG32(MIS_UMSK_ISR_GP1A) = (1 << 24);
	REG32(MIS_UMSK_ISR_GP1DA) = (1 << 24);
	
#endif /* end of #if !defined(FPGA) && !defined(CONFIG_ENV_FPGA) */

	REG32(U0IIR_FCR) = 0x1;
	REG32(U0IIR_FCR) = 0x7;	//set reciver tigger level to 0
#if !defined(FPGA) && !defined(CONFIG_ENV_FPGA)
	REG32(U1IIR_FCR) = 0x1;
	REG32(U1IIR_FCR) = 0x7; //set reciver tigger level to 0
#endif
}
