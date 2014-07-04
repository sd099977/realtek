
/************************************************************************
 *
 *  process_aux_code.c
 *
 *  Process NOCS Auxiliary Code for Sirius internal ROM
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
extern NOCS_Certificate g_NOCS_Certificate;
extern NOCS_Params g_Params_Area;
//extern NOCS_Aux_Code_Tail g_Aux_Code_Tail;

/************************************************************************
 *  External function prototypes
 ************************************************************************/
extern int get_nocs_aux_code_spi(unsigned int dst_addr);
#if 0
extern int get_nocs_aux_code_spi_n(unsigned int dst_addr);
#endif
extern int get_nocs_aux_code_nand(unsigned int dst_addr);
extern int get_nocs_aux_code_emmc(unsigned int dst_addr);

extern int verify_image_signature(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key,char *p_rsa_key_r2);
extern int check_image_hash(char *p_img, unsigned int img_size, char *p_hash);
extern unsigned int skip_pkcs_v1_5_padding(char *ptr);
extern int scs_verify_aux_code(char *p_img);

/************************************************************************
 *  Static function prototypes
 ************************************************************************/


/************************************************************************
 *  Function body
 ************************************************************************/
static int get_aux_code(const unsigned int flash_type, const int target_addr)
{
	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
			res = get_nocs_aux_code_spi(target_addr);
			break;
#if 0
		case SPI_NAND_FLASH_BOOT:
			res = get_nocs_aux_code_spi_n(target_addr);
			break;
#endif

		case NAND_FLASH_BOOT:
			res = get_nocs_aux_code_nand(target_addr);
			break;

		case EMMC_BOOT:
			res = get_nocs_aux_code_emmc(target_addr);
			break;

		case UNKNOWN_BOOT:
		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

static int verify_aux_code(const unsigned int img_addr, const int secure_type)
{
	//do nothing, coz romcode did the job.
	return 0;
}

static int parse_aux_code(const unsigned int params_tdb_addr, const int secure_type)
{
#if defined(DEBUG)
	unsigned int temp;

	printf("\nAux code actual size: 0x%x",  g_Params_Area.Size_of_Aux_Code_Area - sizeof(NOCS_Aux_Code_Tail));


	printf("\nSummary:\n");
	printf("----------");
	printf("\nCertificate area size: 0x%x", sizeof(NOCS_Certificate));
	printf("\nParam area size: 0x%x", g_NOCS_Certificate.Size_Of_SCS_Params_Area);
	printf("\nAux code area size: 0x%x", g_Params_Area.Size_of_Aux_Code_Area);
	printf("\nUncheck area size: 0x%x", SCS_UNCHECK_AREA);
	printf("\ncaculated DTE bootcode area size: ");
	temp = g_Params_Area.Total_Area_Size[g_Params_Area.Total_Area_Size_Selection];
	printf("0x%x, ", temp);
	temp = temp - sizeof(NOCS_Certificate) - g_NOCS_Certificate.Size_Of_SCS_Params_Area - g_Params_Area.Size_of_Aux_Code_Area - SCS_UNCHECK_AREA;
	printf("0x%x ", temp);
	printf("\n");
#endif

	return 0;
}

int process_aux_code(const int flash_type, const int secure_type)
{
	int res = 0;
	unsigned int img_addr = CP42K_SRAM_ADDR;

	/* get NOCS Aux Code */
	if ((res = get_aux_code(flash_type, img_addr))) {
		return res;
	}

	/* verify NOCS Aux Code */
	if ((res = verify_aux_code(img_addr, secure_type))) {
		return res;
	}

	/* parse NOCS Aux Code */
	if ((res = parse_aux_code(CP42K_SRAM_ADDR, secure_type))) {
		return res;
	}

	return res;
}
