
/************************************************************************
 *
 *  otp_sirius.c
 *
 *  OTP routine for Sirius internal ROM
 *
 * 
 * Copyright (c) 2013 Realtek Semiconductor Corp. All rights reserved.
 *
 ************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
//#include "typedef.h"
#include "sysdefs.h"
#include "reset_def.h"
#include "otp_reg.h"
#include "iso_reg.h"
#include "mis_reg.h"
#include "pin_share_reg.h"
#include "nf_reg.h"
#include "sys_reg.h"
#include "error_type.h"
//#include "utility.h"
//#include "timer.h"

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
 *  External variables
 ************************************************************************/

/************************************************************************
 *  External function prototypes
************************************************************************/
#if defined(ROM_DEBUG) || defined(CONFIG_DEBUG_UART_PRINT)
extern void prints(const char *ch);
#endif

/************************************************************************
 *  Public function prototypes
 ************************************************************************/

/************************************************************************
 *  Static function prototypes
 ************************************************************************/

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
}

int get_boot_flash_type(void)
{
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
			case 0:	// virgin state
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
}

int get_nand_boot_type(int *ecc_type, int *access_mode, int *page_size)
{
	unsigned int reg_val;
	unsigned int pin_mux1, pin_mux2, pin_mux3;
	unsigned int gpio_dir;

	//"Sirius ROM Code.ppt"
	pin_mux1 = REG32(GPIO_MUXCFG_13);	// save pin mux
	pin_mux2 = REG32(GPIO_MUXCFG_14);	// save pin mux
	pin_mux3 = REG32(GPIO_MUXCFG_15);	// save pin mux
	gpio_dir = REG32(MIS_GP1DIR);	// save GPIO direction

	REG32(GPIO_MUXCFG_13) = pin_mux1 | (0x1f << 9);	// set mux to GPIO 44, [13:9 ] = 0x1f
	REG32(GPIO_MUXCFG_14) = pin_mux2 | (0x1f << 18) | (0x1f << 9);	// set mux to GPIO 46/47, [22:18] = [13:9] = 0x1f
	REG32(GPIO_MUXCFG_15) = pin_mux3 | (0x1f << 27);	// set mux to GPIO 48, [31:27] = 0x1f
	REG32(MIS_GP1DIR) &= ~((0x1 << (44-32)) | (0x7 << (46-32)));	// set GPIO 44, [48:46] as input pin, [12] = [16:14] = 0
	reg_val = REG32(MIS_GP1DATI);

	//PAD_GPIO_44 (NAND ecc) -> High(1):12bit Low(0):6bit
	*ecc_type = ((reg_val >> (44-32)) & 0x1) ? NAND_ECC_TYPE_12BIT : NAND_ECC_TYPE_6BIT;

	//PAD_GPIO_48 (NAND access mode) -> High(1):enable Low(0):disable
	*access_mode = (reg_val >> (48-32)) & 0x1;

	//PAD_GPIO_47 PAD_GPIO_46 (NAND page size)
	// LL(00):2k LH(01):4K HL(10):8K HH(11):x
	*page_size = (reg_val >> (46-32)) & 0x3;

	REG32(MIS_GP1DIR) = gpio_dir;	// restore GPIO direction
	REG32(GPIO_MUXCFG_15) = pin_mux3;	// restore pin mux
	REG32(GPIO_MUXCFG_14) = pin_mux2;	// restore pin mux
	REG32(GPIO_MUXCFG_13) = pin_mux1;	// restore pin mux

	if (use_pin_select_boot_option() == 0) {
		/* get NAND ECC type from OTP */
/*
		if (decode_2state_otp(OTP_NAND_ECC_SIZE, 1) == TWO_STATE_LEAST_SECURE)
			*ecc_type = NAND_ECC_TYPE_6BIT;
		else
			*ecc_type = NAND_ECC_TYPE_12BIT;
*/

		switch (OTP_NAND_ECC_SIZE) {
			case 0:	// virgin state
				if (OTP_VIRGIN_STATE_ILLEGAL)
					*ecc_type =  NAND_ECC_TYPE_12BIT;	// virgin state is most secure state
				else
					*ecc_type =  NAND_ECC_TYPE_6BIT;	// virgin state is least secure state
				break;
			case 0x1:
				*ecc_type =  NAND_ECC_TYPE_6BIT;
				break;
			case 0x3:
			default:
				*ecc_type =  NAND_ECC_TYPE_12BIT;
				break;
		}

	}

#if defined(ENV_SIMULATION) || defined(CONFIG_DEBUG_SIMULATION_PRINT)
	// debug in simulation
	sim_debug_print(0xaccacc00 | *access_mode);
	sim_debug_print(0xbccbcc00 | *page_size);
	sim_debug_print(0xeccecc00 | *ecc_type);
#endif

	return 0;
}

static int is_secure_boot_enabled(void)
{
	if (decode_2state_otp(OTP_SECURE_BOOT_EN, 1) == TWO_STATE_LEAST_SECURE)
		return 0;
	else
		return 1;
}

int get_secure_boot_type(void)
{
	int res;

	if (is_secure_boot_enabled() == 0) {
		res = NONE_SECURE_BOOT;
		goto epilog_get_secure_boot_type;
	}

	switch (OTP_SECURE_BOOT_TYPE) {
		case 0:	// virgin state
			if (OTP_VIRGIN_STATE_ILLEGAL)
				res = NAGRA_SECURE_BOOT;	// virgin state is most secure state
			else
				res = NONE_SECURE_BOOT;	// virgin state is least secure state
			break;
		case 0x1:
			res = NAGRA_SECURE_BOOT;
			break;
		case 0x5:
			if (REG32(OTP_STATUS) & 0x100)	// check backdoor open
				res = NONE_SECURE_BOOT;
			else
				res = RTK_SECURE_BOOT;
			break;
		case 0x9:
			res = DCAS_SECURE_BOOT;
			break;
		default:
			res = NAGRA_SECURE_BOOT;
			break;
	}

epilog_get_secure_boot_type:
#if defined(ENV_SIMULATION) || defined(CONFIG_DEBUG_SIMULATION_PRINT)
			sim_debug_print(0xdeface00 | res);
#endif
	return res;
}

int is_mem_obfus_enabled(void)
{
	if (decode_2state_otp(OTP_MEM_OBF_EN, 1) == TWO_STATE_LEAST_SECURE)
		return 0;
	else
		return 1;
}

int is_bootcode_encrypted(void)
{
	return OTP_BOOTCODE_ENCRYPT_AES_EN;
}

int is_scs_flash_protection_activation(void)
{
	if (decode_2state_otp(OTP_SCS_FLASH_PROTECTION_ACTIVATION, 1) == TWO_STATE_MOST_SECURE)
		return 1;
	else
		return 0;
}
