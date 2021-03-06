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
#define VERIFY_DTE_KBOOT

/************************************************************************
 *  External variables
 ************************************************************************/
extern NOCS_Certificate *rom_cert;
extern NOCS_Params *rom_params;
extern NOCS_Aux_Code_Tail *rom_aux_code_tail;
extern int *rom_sys_boot_flash_type;

/************************************************************************
 *  Public variables
 ************************************************************************/
DTE_KBOOT_AREA_Tail g_dte_kboot_tail;
unsigned int g_dte_kboot_area_size;

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
// function pointer to ROM code
extern void (*rom_copy_memory)(void *dst, void *src, unsigned int size);
extern int (*rom_check_image_hash)(char *p_img, unsigned int img_size, char *p_hash);
extern int (*rom_verify_image_signature)(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256);
extern unsigned int (*rom_skip_pkcs_v1_5_padding)(char *ptr);
extern int (*rom_AES_decrypt_key_in_CW)(unsigned int algo_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry);

// flash related
extern int get_dte_kboot_spi(unsigned int dst_addr, unsigned int size);
extern int get_dte_kboot_nand(unsigned int dst_addr, unsigned int size);
extern int get_dte_kboot_spi_n(unsigned int dst_addr, unsigned int size);
extern int get_dte_kboot_emmc(unsigned int dst_addr, unsigned int size);

extern int check_image_hash(char *p_img, unsigned int img_size, char *p_img_hash, char *p_mcp_sha256);
extern int verify_image_signature(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256);
extern int scs_verify_dte_kboot(char *p_img);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
int decrypt_dte_kboot(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr)
{
	return AES_decrypt_key_in_CW(ALGO_ID_AES_CBC, src_addr, length, dst_addr, 120);
}

static int get_dte_kboot(const unsigned int flash_type, const int target_addr)
{
	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
			res = get_dte_kboot_spi(target_addr, g_dte_kboot_area_size);
			break;

		case SPI_NAND_FLASH_BOOT:
			res = get_dte_kboot_spi_n(target_addr, g_dte_kboot_area_size);
			break;

		case NAND_FLASH_BOOT:
			res = get_dte_kboot_nand(target_addr, g_dte_kboot_area_size);
			break;

		case EMMC_BOOT:
			res = get_dte_kboot_emmc(target_addr, g_dte_kboot_area_size);
			break;

		case UNKNOWN_BOOT:
		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

#if defined(VERIFY_DTE_KBOOT)
static int verify_dte_kboot(const unsigned int img_addr, const int secure_type)
{
	int res = 0;
	char *p_sig_copy;
	unsigned int tmp, _img_addr;
	unsigned int kboot_bin_size;

	_img_addr = KSEG1(img_addr);

	// make a copy of original header (right after kboot binary)
	// kboot bin size includes key rights
	kboot_bin_size = g_dte_kboot_area_size - sizeof(DTE_KBOOT_AREA_Tail) + 4;

	rom_copy_memory(&g_dte_kboot_tail, (char *)(_img_addr + kboot_bin_size - 4), sizeof(DTE_KBOOT_AREA_Tail));
	p_sig_copy = (char *)(g_dte_kboot_tail.Signature);

#if defined(DEBUG)
	hexdump("p_sig_copy", p_sig_copy, RSA_SIGNATURE_LEN);
#endif

	switch (secure_type) {
		case NONE_SECURE_BOOT:
			tmp = rom_skip_pkcs_v1_5_padding(p_sig_copy);
			if ( (res = check_image_hash((char *)_img_addr,  g_dte_kboot_area_size - RSA_SIGNATURE_LEN, p_sig_copy + tmp, (char *)CP_HASH_DDR)) ) {
				debug("rom_check_image_hash return %x\n", res);
				res = ERR_DTE_KBOOT_NOT_MATCH;
			}

			break;

		case RTK_SECURE_BOOT:
		case DCAS_SECURE_BOOT:
//			tmp = KSEG1(rom_params->Address_of_Boot_Code_Area);
			tmp = KSEG1(DEFAULT_KBOOT_ADDR);

			// decrypt DTE kboot
			if ((res = decrypt_dte_kboot((unsigned char *)_img_addr, kboot_bin_size, (unsigned char *)tmp)))
				break;

#if defined(DEBUG)
			hexdump("bootcode encrypted (first 1024bytes)", tmp, 1024);
#endif

#if defined(DEBUG)
			hexdump("bootcode decrypted (first 1024bytes)", _img_addr, 1024);
#endif

			// copy decrypted data
			//rom_copy_memory(&g_dte_kboot_tail, (char *)(tmp + kboot_bin_size - 4), 4);

			// concatenate decrypted DTE kboot with remaining header
			rom_copy_memory((char *)(tmp + kboot_bin_size), (char *)(_img_addr + kboot_bin_size), sizeof(DTE_KBOOT_AREA_Tail) - 4);

			res = verify_image_signature((char *)tmp,
				g_dte_kboot_area_size - RSA_SIZE,
				p_sig_copy,
				(char *)(rom_cert->External_Public_RSA_Key),
				(char *)(rom_cert->External_R2_Public_RSA_Key),
				(char *)CP_HASH_DDR);
			break;

		case NAGRA_SECURE_BOOT:
			res = scs_verify_dte_kboot((char *)_img_addr);
			break;

		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	if (res == ERR_NOT_MATCH)
		return ERR_DTE_KBOOT_NOT_MATCH;
	else
		return res;
}
#endif

int process_dte_kboot(const int flash_type, const int secure_type, unsigned int *exist_kboot)
{
	int res = 0;
#if defined(DEBUG)
	unsigned int tmp = 0;
#endif
	unsigned int dst_addr = KSEG1(DEFAULT_KBOOT_ADDR);

	if (secure_type != NONE_SECURE_BOOT)
		dst_addr = DEFAULT_ENCRYPT_ADDR;

	// calculate DTE kboot area size
	//tmp = rom_params->Total_Area_Size[rom_params->Total_Area_Size_Selection];
	//g_dte_kboot_area_size = tmp - sizeof(NOCS_Certificate) - rom_cert->Size_Of_SCS_Params_Area - rom_params->Size_of_Aux_Code_Area - SCS_UNCHECK_AREA;

	debug("NOCS Certificate area size: 0x%x\n", sizeof(NOCS_Certificate));
	debug("Param area size: 0x%x\n", rom_cert->Size_Of_SCS_Params_Area);
	debug("Aux code area size: 0x%x\n", rom_params->Size_of_Aux_Code_Area);
	debug("Uncheck area size: 0x%x\n", SCS_UNCHECK_AREA);
	debug("SCS total area size: 0x%x\n", tmp);
	debug("estimated DTE bootcode area size: 0x%x\n", g_dte_kboot_area_size);
	debug("boot specific param: 0x%x\n", rom_params->External_Boot_Specific_Params);
	debug("boot code address: 0x%x\n", dst_addr);

	// We patched the rom_params->Address_of_Aux_Code_Area as the size of kboot
	if (rom_params->Address_of_Aux_Code_Area != 0)
	{
		g_dte_kboot_area_size = rom_params->Address_of_Aux_Code_Area + sizeof(DTE_KBOOT_AREA_Tail);

		if ((res = get_dte_kboot(flash_type, dst_addr))) {
			return res;
		}
#if defined(VERIFY_DTE_KBOOT)
		if ((res = verify_dte_kboot(dst_addr, secure_type))) {
			debug("verify_dte_kboot error 0x%x\n", res);
			return res;
		}
#endif

		*exist_kboot = 1; // make sure kboot image is right
	}

	return res;
}
