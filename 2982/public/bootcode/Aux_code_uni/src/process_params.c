
/************************************************************************
 *
 *  process_params.c
 *
 *  Process NOCS Params for Sirius internal ROM
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
#include "otp_reg.h"
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
extern NOCS_Params g_Params_Area;

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/
extern NOCS_Certificate g_NOCS_Certificate;
extern unsigned char mcp_tmp_buffer[64];

/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern int get_nocs_params_spi(unsigned int dst_addr);
#if 0
extern int get_nocs_params_spi_n(unsigned int dst_addr);
#endif
extern int get_nocs_params_nand(unsigned int dst_addr);
extern int get_nocs_params_emmc(unsigned int dst_addr);

/************************************************************************
 *  Static function prototypes
 ************************************************************************/


/************************************************************************
 *  Function body
 ************************************************************************/
static int get_params(const unsigned int flash_type)
{
	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
			res = get_nocs_params_spi(PARA_START_IN_CP42K_SRAM_ADDR);
			break;
#if 0
		case SPI_NAND_FLASH_BOOT:
			res = get_nocs_params_spi_n(PARA_START_IN_CP42K_SRAM_ADDR);
			break;
#endif

		case NAND_FLASH_BOOT:
			res = get_nocs_params_nand(PARA_START_IN_CP42K_SRAM_ADDR);
			break;

		case EMMC_BOOT:
			res = get_nocs_params_emmc(PARA_START_IN_CP42K_SRAM_ADDR);
			break;

		case UNKNOWN_BOOT:
		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

static int verify_params(const unsigned int img_addr, const int secure_type)
{
	//just copy data, coz romcode did the job.

	// 64*4 for unsigned int Signature[64]
	// 4*4 for unsigned int Flash_Protection_Key[4];
	unsigned int tail_data_size = sizeof(NOCS_Params) - offsetof(NOCS_Params, Controlling_Data);
	// make a copy of original signature
	copy_memory(&g_Params_Area, (char *)img_addr, sizeof(NOCS_Params) - tail_data_size);
	copy_memory(&g_Params_Area.Controlling_Data, (char *)img_addr + g_NOCS_Certificate.Size_Of_SCS_Params_Area - tail_data_size, tail_data_size);

	return 0;
}

static int parse_params(const unsigned int params_tdb_addr, const int secure_type)
{
#if defined(DEBUG)
	int i = 0;

	printf("\nSTR default region min size: 0x%x", g_Params_Area.STR_Default_Region_Min_Size);
	printf("\nAux code address: 0x%x", g_Params_Area.Address_of_Aux_Code_Area);
	printf(", Aux code size: 0x%x", g_Params_Area.Size_of_Aux_Code_Area);
	printf("\nDTE bootcode address: 0x%x", g_Params_Area.Address_of_Boot_Code_Area);
	printf("\ntotal area size: ");
	for (i = 0; i < 4; i++) {
		printf("0x%x, ",g_Params_Area.Total_Area_Size[i]);
	}
	printf("\ntotal area size selection: 0x%x", g_Params_Area.Total_Area_Size_Selection);
	printf(" => 0x%x", g_Params_Area.Total_Area_Size[g_Params_Area.Total_Area_Size_Selection]);
	printf("\n");
#endif

	if (g_Params_Area.Total_Area_Size_Selection > 4)
		return ERR_INVALID_PARAM;

	return 0;
}

int process_params(const int flash_type, const int secure_type)
{
	int res;

	/* get NOCS Params Area */
	if ((res = get_params(flash_type))) {
		return res;
	}

	/* verify NOCS Params Area */
	if ((res = verify_params(PARA_START_IN_CP42K_SRAM_ADDR, secure_type))) {
		return res;
	}

	/* parse NOCS Params Area */
	if ((res = parse_params(PARA_START_IN_CP42K_SRAM_ADDR, secure_type))) {
		return res;
	}

	return res;
}
