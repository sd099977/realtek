
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

static const char* get_flash_type_name(unsigned int flash_type)
{
	switch(flash_type){
		case NAND_FLASH_BOOT:
			return "NAND";
		case SPI_FLASH_BOOT:
			return "SPI";
		case SPI_NAND_FLASH_BOOT:
			return "SPI_NAND";
		case EMMC_BOOT:
			return "EMMC";
		default:	// should be impossible
			return "NAND";
	}
}

unsigned char get_secure_boot_type(void)
{
	return NONE_SECURE_BOOT;
}

int get_burn_boot_flash_type(void)
{
	unsigned int boot_type;

	mdelay(500);
	boot_type = get_boot_flash_type();	

	printf("auto flash type: %s\n", get_flash_type_name(boot_type));

	switch (boot_type) {
		case NAND_FLASH_BOOT:
			return FLASH_TYPE_NAND;
			break;
		case SPI_FLASH_BOOT:
			return FLASH_TYPE_SPI;
			break;
		case SPI_NAND_FLASH_BOOT:
			return FLASH_TYPE_SPI_NAND;
			break;
		case EMMC_BOOT:
			return FLASH_TYPE_EMMC;
			break;
		default:	// should be impossible
			return FLASH_TYPE_NAND;
			break;
	}

	return -1;
}
