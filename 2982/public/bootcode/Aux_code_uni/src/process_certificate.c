
/************************************************************************
 *
 *  process_certificate.c
 *
 *  Process NOCS Certificate for Sirius internal ROM
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
//#include "uart.h"
#include "error_type.h"
#include "util.h"
#include "mcp.h"
#include "NOCS.h"

#if defined(CONFIG_ENV_REALCHIP_SIM)
#define CONFIG_DEBUG_UART_PRINT
#endif

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
extern NOCS_Certificate g_NOCS_Certificate;

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern int get_nocs_certificate_spi(unsigned int dst_addr);
#if 0
extern int get_nocs_certificate_spi_n(unsigned int dst_addr);
#endif
extern int get_nocs_certificate_nand(unsigned int dst_addr);
extern int get_nocs_certificate_emmc(unsigned int dst_addr);

/************************************************************************
 *  Static function prototypes
 ************************************************************************/


/************************************************************************
 *  Function body
 ************************************************************************/

static int get_certificate(const unsigned int flash_type)
{
	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
			res = get_nocs_certificate_spi(PARA_START_IN_CP42K_SRAM_ADDR);
			break;
#if 0
		case SPI_NAND_FLASH_BOOT:
			res = get_nocs_certificate_spi_n(PARA_START_IN_CP42K_SRAM_ADDR);
			break;
#endif

		case NAND_FLASH_BOOT:
			res = get_nocs_certificate_nand(PARA_START_IN_CP42K_SRAM_ADDR);
			break;

		case EMMC_BOOT:
			res = get_nocs_certificate_emmc(PARA_START_IN_CP42K_SRAM_ADDR);
			break;

		case UNKNOWN_BOOT:
		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

static int verify_certificate(const unsigned int img_addr, const int secure_type)
{
	//just copy data, coz romcode did the job.
	unsigned int size_after_padding = sizeof(NOCS_Certificate) - offsetof(NOCS_Certificate, Controlling_Data);
	// make a copy of original signature
	copy_memory(&g_NOCS_Certificate, (char *)img_addr, sizeof(NOCS_Certificate) - size_after_padding);
	copy_memory(&g_NOCS_Certificate.Controlling_Data, (char *)img_addr + CERTIFICATE_SIZE - size_after_padding, size_after_padding);
	return 0;
}

static int parse_certificate(const unsigned int cert_tdb_addr, const int secure_type)
{
#if defined(DEBUG)
	printf("\nParam area size: 0x%x, Param area addr:0x%x\n", g_NOCS_Certificate.Size_Of_SCS_Params_Area, g_NOCS_Certificate.Address_Of_SCS_Param_Area);
#endif

	return 0;
}

int process_certificate(const int flash_type, const int secure_type)
{
	int res;

	/* get NOCS Certificate */
	if ((res = get_certificate(flash_type))) {
		return res;
	}

	/* verify NOCS Certificate */
	if ((res = verify_certificate(PARA_START_IN_CP42K_SRAM_ADDR, secure_type))) {
		return res;
	}

	/* parse NOCS Certificate */
	if ((res = parse_certificate(PARA_START_IN_CP42K_SRAM_ADDR, secure_type))) {
		return res;
	}

	return res;
}
