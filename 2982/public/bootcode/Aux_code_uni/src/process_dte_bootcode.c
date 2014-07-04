/****************************************************************************************
* Program Name:
* Author:
* Date:
* Description:
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
#include "util.h"
#include "loader.h"
#include "UART.h"
#include "NOCS.h"
#include "reset_def.h"
#include "error_type.h"
#include "mcp.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define VERIFY_DTE_BOOTCODE

/************************************************************************
 *  External variables
 ************************************************************************/
extern NOCS_Certificate g_NOCS_Certificate;
extern NOCS_Params g_Params_Area;
//extern NOCS_Aux_Code_Tail g_Aux_Code_Tail;
extern DTE_BOOTCODE_AREA_Tail g_dte_bootcode_tail;
extern unsigned int g_dte_bootcode_area_size;

/************************************************************************
 *  Public variables
 ************************************************************************/


/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
// flash related
extern int get_dte_bootcode_spi(unsigned int dst_addr, unsigned int size);
extern int get_dte_bootcode_nand(unsigned int dst_addr, unsigned int size);
extern int get_dte_bootcode_spi_n(unsigned int dst_addr, unsigned int size);
extern int get_dte_bootcode_emmc(unsigned int dst_addr, unsigned int size);

extern int check_image_hash(char *p_img, unsigned int img_size, char *p_img_hash, char *p_mcp_sha256);
extern int verify_image_signature(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256);
extern int scs_verify_dte_bootcode(char *p_img);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
int decrypt_dte_bootcode(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr)
{
	return AES_decrypt_key_in_CW(ALGO_ID_AES_CBC, src_addr, length, dst_addr, 120);
}

static int get_dte_bootcode(const unsigned int flash_type, const int target_addr)
{
	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
			res = get_dte_bootcode_spi(target_addr, g_dte_bootcode_area_size);
			break;

		case SPI_NAND_FLASH_BOOT:
			res = get_dte_bootcode_spi_n(target_addr, g_dte_bootcode_area_size);
			break;

		case NAND_FLASH_BOOT:
			res = get_dte_bootcode_nand(target_addr, g_dte_bootcode_area_size);
			break;

		case EMMC_BOOT:
			res = get_dte_bootcode_emmc(target_addr, g_dte_bootcode_area_size);
			break;

		case UNKNOWN_BOOT:
		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

#if defined(VERIFY_DTE_BOOTCODE)
static int verify_dte_bootcode(const unsigned int img_addr, const int secure_type)
{
	int res = 0;
	char *p_sig_copy;
	unsigned int tmp, _img_addr;
	unsigned int bootcode_bin_size;

	_img_addr = KSEG1(img_addr);

	// make a copy of original header (right after bootcode binary)
	// bootcode bin size includes key rights
	bootcode_bin_size = g_dte_bootcode_area_size - sizeof(DTE_BOOTCODE_AREA_Tail) + 4;

	copy_memory(&g_dte_bootcode_tail, (char *)(_img_addr + bootcode_bin_size - 4), sizeof(DTE_BOOTCODE_AREA_Tail));
	p_sig_copy = (char *)(g_dte_bootcode_tail.Signature);

#if defined(DEBUG)
	hexdump("p_sig_copy", p_sig_copy, RSA_SIGNATURE_LEN);
#endif

	switch (secure_type) {
		case NONE_SECURE_BOOT:
			tmp = skip_pkcs_v1_5_padding(p_sig_copy);
			if ( (res = check_image_hash((char *)_img_addr,  g_dte_bootcode_area_size - RSA_SIGNATURE_LEN, p_sig_copy + tmp, (char *)CP_HASH_DDR)) ) {
				debug("check_image_hash return %x\n", res);
				res = ERR_DTE_BOOTCODE_NOT_MATCH;
			}

			break;

		case RTK_SECURE_BOOT:
		case DCAS_SECURE_BOOT:
			tmp = KSEG1(g_Params_Area.Address_of_Boot_Code_Area);

			// decrypt DTE bootcode
			if ((res = decrypt_dte_bootcode((unsigned char *)_img_addr, bootcode_bin_size, (unsigned char *)tmp)))
				break;

#if defined(DEBUG)
			hexdump("bootcode encrypted (first 1024bytes)", tmp, 1024);
#endif

#if defined(DEBUG)
			hexdump("bootcode decrypted (first 1024bytes)", _img_addr, 1024);
#endif

			// copy decrypted data
			//rom_copy_memory(&g_dte_bootcode_tail, (char *)(tmp + bootcode_bin_size - 4), 4);

			// concatenate decrypted DTE bootcode with remaining header
			copy_memory((char *)(tmp + bootcode_bin_size), (char *)(_img_addr + bootcode_bin_size), sizeof(DTE_BOOTCODE_AREA_Tail) - 4);

			res = verify_image_signature((char *)tmp,
				g_dte_bootcode_area_size - RSA_SIZE,
				p_sig_copy,
				(char *)(g_NOCS_Certificate.External_Public_RSA_Key),
				(char *)(g_NOCS_Certificate.External_R2_Public_RSA_Key),
				(char *)CP_HASH_DDR);
			break;

#if 0
		case NAGRA_SECURE_BOOT:
			res = scs_verify_dte_bootcode((char *)_img_addr);
			break;
#endif
		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	if (res == ERR_NOT_MATCH)
		return ERR_DTE_BOOTCODE_NOT_MATCH;
	else
		return res;
}
#endif

int process_dte_bootcode(const int flash_type, const int secure_type)
{
	int res = 0;
#if defined(DEBUG)
	unsigned int tmp = 0;
#endif
	unsigned int dst_addr = KSEG1(g_Params_Area.Address_of_Boot_Code_Area);

	if (secure_type != NONE_SECURE_BOOT)
		dst_addr = DEFAULT_ENCRYPT_ADDR;

	// calculate DTE bootcode area size
	//tmp = rom_params->Total_Area_Size[rom_params->Total_Area_Size_Selection];
	//g_dte_bootcode_area_size = tmp - sizeof(NOCS_Certificate) - rom_cert->Size_Of_SCS_Params_Area - rom_params->Size_of_Aux_Code_Area - SCS_UNCHECK_AREA;

	debug("NOCS Certificate area size: 0x%x\n", sizeof(NOCS_Certificate));
	debug("Param area size: 0x%x\n", g_NOCS_Certificate.Size_Of_SCS_Params_Area);
	debug("Aux code area size: 0x%x\n", g_Params_Area.Size_of_Aux_Code_Area);
	debug("Uncheck area size: 0x%x\n", SCS_UNCHECK_AREA);
	debug("SCS total area size: 0x%x\n", tmp);
	debug("estimated DTE bootcode area size: 0x%x\n", g_dte_bootcode_area_size);
	debug("boot specific param: 0x%x\n", g_Params_Area.External_Boot_Specific_Params);
	debug("boot code address: 0x%x\n", dst_addr);


	g_dte_bootcode_area_size = g_Params_Area.External_Boot_Specific_Params + sizeof(DTE_BOOTCODE_AREA_Tail);

	if ((res = get_dte_bootcode(flash_type, dst_addr))) {
		return res;
	}
#if defined(VERIFY_DTE_BOOTCODE)
	if ((res = verify_dte_bootcode(dst_addr, secure_type))) {
		debug("verify_dte_bootcode error 0x%x\n", res);
		return res;
	}
#endif

	return res;
}
