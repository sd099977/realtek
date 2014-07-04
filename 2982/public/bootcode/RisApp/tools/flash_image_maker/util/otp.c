
/************************************************************************
 *
 *  otp.c
 *
 *  OTP routine for MacArthur2 internal ROM
 *
 * 
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/

#include <sysdefs.h>
//#include "typedef.h"
//#include "reset_def.h"
#include "otp_reg_rtd298x.h"
//#include "iso_reg.h"
#include "mis_reg_rtd298x.h"
#include "pin_share_reg_rtd298x.h"
//#include "nf_reg.h"
//#include "sys_reg.h"
//#include "error_type.h"
#include "util.h"


/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  Public function prototypes
 ************************************************************************/

/************************************************************************
 *  Static function prototypes
 ************************************************************************/
static int decode_2state_otp(unsigned int value, int check_virgin_state);
static int use_pin_select_boot_option(void);

/************************************************************************
 *  Function body
 ************************************************************************/
static int decode_2state_otp(unsigned int value, int check_virgin_state)
{
	switch (value) {
		case 0x0:	// virgin state
			if (check_virgin_state) {
				if (OTP_VIRGIN_STATE_ILLEGAL)	// virgin state is most secure state
					return TWO_STATE_MOST_SECURE;
				else	// virgin state is least secure state
					return TWO_STATE_LEAST_SECURE;
			}
			else // virgin state is least secure state
				return TWO_STATE_LEAST_SECURE;
		case 0x1:
			return TWO_STATE_LEAST_SECURE;
		case 0x3:
		default:
			return TWO_STATE_MOST_SECURE;
	}
}


static int use_pin_select_boot_option(void)
{
	if (decode_2state_otp(OTP_BOOT_OPT_SEL_EN, 1) == TWO_STATE_LEAST_SECURE)
		return 1;
	else
		return 0;
/*
	switch (OTP_BOOT_OPT_SEL_EN) {
		case 0: // virgin state
			if (OTP_VIRGIN_STATE_ILLEGAL)
				return 0;	// virgin state is most secure state
			else
				return 1;	// virgin state is least secure state
		case 0x1:
			return 1;
		case 0x3:
			return 0;
		default:
			return 0;
	}
*/
}



int get_boot_flash_type(void)
{
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
	prints("\n");
	prints(__FUNCTION__);
#endif

#if defined(FPGA) || defined(CONFIG_ENV_FPGA)

#if defined(FPGA_FORCE_BOOT_OPTION_SPI)
	return SPI_FLASH_BOOT;
#elif defined(FPGA_FORCE_BOOT_OPTION_NAND)
	return NAND_FLASH_BOOT;
#elif defined(FPGA_FORCE_BOOT_OPTION_EMMC)
	return EMMC_BOOT;
#elif defined(FPGA_FORCE_BOOT_OPTION_SPI_NAND)
	return SPI_NAND_FLASH_BOOT;
#else
	return UNKNOWN_BOOT;
#endif /* end of #if defined(FPGA_FORCE_BOOT_OPTION_SPI) */

#else /* else of #if defined(FPGA) || defined(CONFIG_ENV_FPGA) */

	unsigned int res;

	if (use_pin_select_boot_option()) {
		/* get boot flash type from GPIO */
		unsigned int reg_val, tmp;
		unsigned int pin_mux1, pin_mux2;
		unsigned int gpio_dir;

		// from "Sirius ROM Code.ppt"
		pin_mux1 = REG32(GPIO_MUXCFG_12);	// save pin mux
		pin_mux2 = REG32(GPIO_MUXCFG_14);	// save pin mux
		gpio_dir = REG32(MIS_GP1DIR);	// save GPIO direction
		REG32(GPIO_MUXCFG_12) = pin_mux1 | (0x1f << 27);	// set gpio_39_ps = 0x1f
		REG32(GPIO_MUXCFG_14) = pin_mux2 | (0x1f << 27) | (0x1 << 25);	// set gpio_45_ps = 0x1f, gpio_45_pd = 1
		REG32(MIS_GP1DIR) &= ~((0x1 << 13) | (0x1 << 7));	// set GPIO 39/45 as input pin, [7] = [13] = 0
		udelay(500);
		//PAD_GPIO_45 (Flash type) bit0
		//PAD_GPIO_39 (Flash type) bit1 -> (00):NAND (01):SPI (10):SPI-NAND (11):eMMC
		reg_val = REG32(MIS_GP1DATI);
		tmp = ((reg_val >> (39-32-1)) & 0x2) | ((reg_val >> (45-32)) & 0x1);

		REG32(MIS_GP1DIR) = gpio_dir;	// restore GPIO direction
		REG32(GPIO_MUXCFG_14) = pin_mux2;	// restore pin mux
		REG32(GPIO_MUXCFG_12) = pin_mux1;	// restore pin mux

		switch (tmp) {
			case 0:
				res = NAND_FLASH_BOOT;
				break;
			case 0x1:
				res = SPI_FLASH_BOOT;
				break;
			case 0x2:
				res = SPI_NAND_FLASH_BOOT;
				break;
			case 0x3:
				res = EMMC_BOOT;
				break;
			default:	// should be impossible
				res = NAND_FLASH_BOOT;
				break;
		}
	}
	else {
		/* get boot flash type from OTP */
		switch (OTP_BOOT_TYPE_SEL) {
			case 0: // virgin state
				if (OTP_VIRGIN_STATE_ILLEGAL)
					res = EMMC_BOOT;	// virgin state is most secure state
				else
					res = SPI_FLASH_BOOT;	// virgin state is least secure state
				break;
			case 0x1:
				res = SPI_FLASH_BOOT;
				break;
			case 0x3:
				res = NAND_FLASH_BOOT;
				break;
			case 0x9:
				res = SPI_NAND_FLASH_BOOT;
				break;
			case 0x5:
			default:
				res = EMMC_BOOT;
				break;
		}
	}
	
#if defined(ENV_SIMULATION) || defined(CONFIG_DEBUG_SIMULATION_PRINT)
	sim_debug_print(0xecfa0000 | res);
#endif
	return res;

#endif /* end of #if defined(FPGA) || defined(CONFIG_ENV_FPGA) */
}

unsigned char get_secure_boot_type(void)
{
	return NONE_SECURE_BOOT;
}

#if 0
int get_boot_flash_type(void)
{
#ifdef ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

	unsigned int state, boottype;
	unsigned int reg_val, tmp;
	
	//MAC2 ROM CODE Boption_NAND SPI  pin mux register.ppt
	//PAD_GPIO_45 (Flash type) bit0
	//PAD_GPIO_39 (Flash type) bit1 -> (00):NAND (01):SPI (10):x (11):SPI-NAND 
	
	/* get boot_type (from GPIO) */

	//FLASH_TYPE_bit0
	tmp = REG32(GPIO_MUXCFG_11);
	state = REG32(MIS_GP1DIR);
	REG32(GPIO_MUXCFG_11) |= 0x00f00000; // set mux to GPIO_45, GPIO_MUXCFG_11[23:20] = 0xf
	REG32(MIS_GP1DIR) &= (~(1<<(45-32)));	// set GPIO_45 as input pin, MIS_GP1DIR[13] = 0
	reg_val = REG32(MIS_GP1DATI);
	/* get boottype type from GPIO_45 */
	boottype = (reg_val >> (45-32)) & 0x1;
	REG32(MIS_GP1DIR) = state; // restore GPIO direction
	REG32(GPIO_MUXCFG_11) = tmp; // restore pin mux

	//FLASH_TYPE_bit1
	tmp = REG32(GPIO_MUXCFG_9);
	state = REG32(MIS_GP1DIR);
	REG32(GPIO_MUXCFG_9) |= 0x000000f0; // set mux to GPIO_39, GPIO_MUXCFG_11[7:4] = 0xf
	REG32(MIS_GP1DIR) &= (~(1<<(39-32)));	// set GPIO_39 as input pin, MIS_GP1DIR[7] = 0
	reg_val = REG32(MIS_GP1DATI);
	/* get boottype type from GPIO_39 */
	boottype |= ((reg_val >> (39-32-1)) & 0x2);
	REG32(MIS_GP1DIR) = state; // restore GPIO direction
	REG32(GPIO_MUXCFG_9) = tmp; // restore pin mux


	switch(boottype) {
		case 0:
#ifdef ENV_SIMULATION
			sim_debug_print(0xecfa0000);
#endif
			return FLASH_TYPE_NAND;

		case 1:
#ifdef ENV_SIMULATION
			sim_debug_print(0xecfa1111);
#endif	
			return FLASH_TYPE_SPI;

		case 3:
#ifdef ENV_SIMULATION
			sim_debug_print(0xecfa3333);
#endif	
			return FLASH_TYPE_SPI_NAND;

		case 2:
		default:
		/* impossible!!! */
#ifdef ENV_SIMULATION
			sim_debug_print(0xecfadead);
#endif
			return FLASH_TYPE_SPI;
	}

}

int get_nand_boot_type(int *ecc_type, int *access_mode, int *page_size)
{

#ifdef FPGA
	//add by angus, wait fpga team provide setting
	//reg_val = REG32(ISO_GPDATI);
	//*ecc_type = (reg_val >> 18) & 0x1;	// ISO_GPIO[18] as ECC type
	//*access_mode = (reg_val >> 19) & 0x1;	// ISO_GPIO[19] as access mode
	*ecc_type = 0;
	*access_mode = 0;

	return 0;
#else
	unsigned int state;
	unsigned int reg_val, tmp;
	
	//see MAC2 ROM CODE Boption_NAND SPI  pin mux register.ppt

	//PAD_GPIO_44 (NAND ecc) -> High(1):6bit Low(0):12bit
	/* get ecc_type (from GPIO) */
	tmp = REG32(GPIO_MUXCFG_11);
	state = REG32(MIS_GP1DIR);
	REG32(GPIO_MUXCFG_11) |= 0xf0000000;	// set mux to GPIO_44, GPIO_MUXCFG_11[31:28] = 0xf
	REG32(MIS_GP1DIR) &= (~(1<<(44-32))); 	// set GPIO_44 as input pin, MIS_GP1DIR[12] = 0
	reg_val = REG32(MIS_GP1DATI);
	/* get ECC type from GPIO_44 */
	*ecc_type = ((reg_val >> (44-32)) & 0x1) ? NAND_ECC_TYPE_6BIT : NAND_ECC_TYPE_12BIT;
	REG32(MIS_GP1DIR) = state; // restore GPIO direction
	REG32(GPIO_MUXCFG_11) = tmp;	// restore pin mux

	//PAD_GPIO_48 (NAND access mode) -> High:enable Low:disable
	/* get access mode (from GPIO) */
	tmp = REG32(GPIO_MUXCFG_12);
	state = REG32(MIS_GP1DIR);
	REG32(GPIO_MUXCFG_12) |= 0xf0000000;	// set mux to GPIO_48, GPIO_MUXCFG_12[31:28] = 0xf
	REG32(MIS_GP1DIR) &= (~(1<<(48-32))); 	// set GPIO_48 as input pin, MIS_GP1DIR[16] = 0
	reg_val = REG32(MIS_GP1DATI);
	/* get access mode from GPIO_48 */
	*access_mode = (reg_val >> (48-32)) & 0x1;
	REG32(MIS_GP1DIR) = state; // restore GPIO direction
	REG32(GPIO_MUXCFG_12) = tmp;	// restore pin mux

	//PAD_GPIO_47 PAD_GPIO_46 (NAND page size)
	/* get page size (from GPIO) */
	tmp = REG32(GPIO_MUXCFG_11);
	state = REG32(MIS_GP1DIR);
	REG32(GPIO_MUXCFG_11) |= 0x0000f0f0;	// set mux to GPIO_46, GPIO_MUXCFG_11[15:12] = 0xf
														// set mux to GPIO_47, GPIO_MUXCFG_11[7:4] = 0xf
	REG32(MIS_GP1DIR) &= (~(1<<(48-32))); 	// set GPIO_48 as input pin, MIS_GP1DIR[16] = 0
	reg_val = REG32(MIS_GP1DATI);
	/* get page size from GPIO_47:46 */
	*page_size = (reg_val >> (46-32)) & 0x3;
	REG32(MIS_GP1DIR) = state; // restore GPIO direction
	REG32(GPIO_MUXCFG_11) = tmp;	// restore pin mux
	
	return 0;

#endif
#ifdef ENV_SIMULATION
		sim_debug_print(0xecceccff);
#endif

}

unsigned char get_secure_boot_type(void)
{
	int res;

#ifdef FPGA

#ifdef FPGA_SECURE_BOOT
	return FPGA_SECURE_BOOT;
#else
	return NONE_SECURE_BOOT;
#endif

#else

#if 0
	/* check back door function enabled, efuse [3780] */
	if (((REG32(OTP_EFUSE_BACKDOOR) >> 4) & 0x1) == 0x0)
	{
		/* check back door function enabled, efuse [3783:3781] */
		if (((REG32(OTP_EFUSE_BACKDOOR) >> 5) & 0x7) == 0x7)
		{
#ifdef ENV_SIMULATION
			sim_debug_print(0xdeface00);
#endif

			return NONE_SECURE_BOOT;
		}
	}

	//check efuse [3787:3786]
	/* check DCAS secure boot */
	res = (REG32(OTP_EFUSE_SECUREBOOT) >> 10) & 0x3;
	if (res == 3) {
#ifdef ENV_SIMULATION
		sim_debug_print(0xdeface03);
#endif

		return DCAS_SECURE_BOOT;
	}
	else if (res == 2) {
#ifdef ENV_SIMULATION
		sim_debug_print(0xdeface02);
#endif

		return RTK_SECURE_BOOT; // or RTK secure boot
	}


#ifdef ENV_SIMULATION
		sim_debug_print(0xdeface00);
#endif

	return NONE_SECURE_BOOT;
#else

	// check Bonding option for eFUSE Enable
	// Efuse control bit usage setting
	// 0:  Efuse control bit disable
	// 1:  Efuse control bit use
	if(((REG32(SYS_SC_POL) >> BOPTION_8_BIT_NO) & 0x1) == 0)
	{
		return NONE_SECURE_BOOT;	
	}

	/* check backdoor mode enabled, efuse [3848] */
	/* 0:on 1:off */
	if (((REG32(OTP_EFUSE_NONSECURITY_BACKDOOR_MODE) >> 8) & 0x1) == 0x0)
	{
		/* check backdoor function enabled, efuse [3879:3876] */
		if (((REG32(OTP_EFUSE_NONSECURITY_BACKDOOR_ON) >> 4) & 0xf) == 0xf)
		{
#ifdef ENV_SIMULATION
			sim_debug_print(0xdeface00);
#endif
			return NONE_SECURE_BOOT;
		}
	}

	//check efuse [3846:3845]
	// 0: non secure
	// 1: non secure
	// 2: rtk secure
	// 3: dcas secure	
	res = (REG32(OTP_EFUSE_SECUREBOOT) >> 5) & 0x3;

	switch(res) {
		case 3:
#ifdef ENV_SIMULATION
			sim_debug_print(0xdeface03);
#endif
			return DCAS_SECURE_BOOT;

		case 2:
#ifdef ENV_SIMULATION
			sim_debug_print(0xdeface02);
#endif	
			return RTK_SECURE_BOOT; // or RTK secure boot

		default:
		case 1:
		case 0:
#ifdef ENV_SIMULATION
			sim_debug_print(0xdeface00);
#endif
			return NONE_SECURE_BOOT;

	}
	/* impossible!!! */
	return NONE_SECURE_BOOT;

#endif

#endif	/* #ifdef FPGA */
}

void set_spi_pin_mux(void)
{
#ifndef FPGA
	int reg_val;
	
	// set GPIO_122_ps[15:12] to "	0: SPI_CS_N,<O>"
	// set GPIO_123_ps[7:4] to "	0: SPI_SCLK,<O>"
	reg_val = REG32(GPIO_MUXCFG_23) & 0xffff0f0f;
	REG32(GPIO_MUXCFG_23) = reg_val;	
	
	// set GPIO_125_ps[23:20] to "	0: SPI_DI,<I/O>"
	// set GPIO_126_ps[15:12] to "	0: SPI_DO,<I/O>"
	reg_val = REG32(GPIO_MUXCFG_24) & 0xff0f0fff;
	REG32(GPIO_MUXCFG_24) = reg_val;
#endif
}

void set_nand_pin_mux(void)
{
#ifndef FPGA
	unsigned int reg_val;

	// set GPIO_39_ps[7:4] to "	0: nf_tmx_cle,<O>"
	reg_val = (REG32(GPIO_MUXCFG_9) & 0xffffff0f);
	REG32(GPIO_MUXCFG_9) = reg_val; 

	// set GPIO_40_ps[31:28] to " 0: nf_tmx_wr_n,<O>"
	// set GPIO_41_ps[23:20] to " F: MIS_GPIO_bit41,<I/O>"
	// set GPIO_42_ps[15:12] to " 0: nf_tmx_ale,<O>"
	reg_val = (REG32(GPIO_MUXCFG_10) & 0x0f0f0fff) | 0x00f00000;
	REG32(GPIO_MUXCFG_10) = reg_val;

	// set GPIO_44_ps[31:28] to " 0: nf_tmx_bit0,<I/O>"
	// set GPIO_45_ps[23:20] to " 0: nf_tmx_bit1,<I/O>"
	// set GPIO_46_ps[15:12] to " 0: nf_tmx_bit2,<I/O>"
	// set GPIO_47_ps[07:04] to " 0: nf_tmx_bit3,<I/O>"
	reg_val = (REG32(GPIO_MUXCFG_11) & 0x0f0f0f0f);
	REG32(GPIO_MUXCFG_11) = reg_val;

	// set GPIO_48_ps[31:28] to " 0: nf_tmx_bit4,<I/O>"
	// set GPIO_49_ps[23:20] to " 0: nf_tmx_bit5,<I/O>"
	// set GPIO_50_ps[15:12] to " 0: nf_tmx_bit6,<I/O>"
	// set GPIO_51_ps[07:04] to " 0: nf_tmx_bit7,<I/O>"
	reg_val = (REG32(GPIO_MUXCFG_12) & 0x0f0f0f0f);
	REG32(GPIO_MUXCFG_12) = reg_val;

	// set GPIO_52_ps[31:28] to " 0: nf_tmx_rd_n,<O>"
	reg_val = (REG32(GPIO_MUXCFG_13) & 0x0fffffff);
	REG32(GPIO_MUXCFG_13) = reg_val;

	// set GPIO_56_ps[31:28] to " 0: tmx_nf_rdy,<I>"
	reg_val = (REG32(GPIO_MUXCFG_14) & 0x0fffffff);
	REG32(GPIO_MUXCFG_14) = reg_val;

	//select by PAD_BOPTION0 H:LQFP176 L:LQFP256
	if((REG32(SYS_SC_POL) >> BOPTION_0_BIT_NO) & 0x1) {
		// PAD_GPIO_35	NF_CE0 (LQFP176)
		// set GPIO_35_ps[7:4] to " 0: nf_tmx_ce_n_bit0,<O>"
		reg_val = (REG32(GPIO_MUXCFG_8) & 0xffffff0f);
		REG32(GPIO_MUXCFG_8) = reg_val;
	} 
	else {
		// PAD_GPIO_55	NF_CE0 (LQFP256)
		// set GPIO_55_ps[7:4] to " 0: nf_tmx_ce_n_bit0,<O>"
		reg_val = (REG32(GPIO_MUXCFG_13) & 0xffffff0f);
		REG32(GPIO_MUXCFG_13) = reg_val;
	}
#endif
}
#endif
