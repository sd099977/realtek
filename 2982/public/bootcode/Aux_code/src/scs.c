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

/************************************************************************
 *  External variables
 ************************************************************************/
extern DTE_KBOOT_AREA_Tail g_dte_kboot_tail;
extern unsigned int g_dte_kboot_area_size;
extern DTE_BOOTCODE_AREA_Tail g_dte_bootcode_tail;
extern unsigned int g_dte_bootcode_area_size;
extern NOCS_Certificate *rom_cert;
extern NOCS_Params *rom_params;

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int decrypt_dte_kboot(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr);
extern int decrypt_dte_bootcode(unsigned char *src_addr, unsigned int length, unsigned char *dst_addr);
extern int verify_image_signature(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256);

// function pointer to ROM code
extern void (*rom_copy_memory)(void *dst, void *src, unsigned int size);
extern int (*rom_verify_image_signature)(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256);
extern int (*rom_is_scs_enabled)(void);
extern int (*rom_scs_validate_controlling_data)(const NOCS_Controlling_Data *p_cd);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

int scs_verify_dte_kboot(char *p_img)
{
#if defined(ENV_FPGA) || defined(DEBUG)
	printf("%s(0x%x)\n", __FUNCTION__, (unsigned int)p_img);
#endif
	int res = 0;
	unsigned int kboot_addr;
	unsigned int kboot_bin_size;
	DTE_KBOOT_AREA_Tail *p_dte_kboot_tail = &g_dte_kboot_tail;

	if (p_img == NULL)
		return ERR_INVALID_PARAM;

	kboot_bin_size = g_dte_kboot_area_size - sizeof(DTE_KBOOT_AREA_Tail) + 4;
	kboot_addr = KSEG1(DEFAULT_KBOOT_ADDR);

	// decrypt DTE kboot
	if ((res = decrypt_dte_kboot((unsigned char *)p_img, kboot_bin_size, (unsigned char *)kboot_addr)))
		return res;

#if defined(DEBUG)
	hexdump("kboot encrypted (first 1024bytes)", p_img, 1024);
#endif

#if defined(DEBUG)
	hexdump("kboot decrypted (first 1024bytes)", kboot_addr, 1024);
#endif

	// copy decrypted data
	rom_copy_memory(&g_dte_kboot_tail, (char *)(kboot_addr + kboot_bin_size - 4), 4);

	// concatenate decrypted DTE kboot with remaining header
	rom_copy_memory((char *)(kboot_addr + kboot_bin_size), (p_img + kboot_bin_size), sizeof(DTE_KBOOT_AREA_Tail) - 4);

	if (rom_is_scs_enabled()) {
		// verify signature
		res = verify_image_signature((char *)kboot_addr,
			g_dte_kboot_area_size - RSA_SIZE,
			(char *)(p_dte_kboot_tail->Signature),
			(char *)(rom_cert->External_Public_RSA_Key),
			(char *)(rom_cert->External_R2_Public_RSA_Key),
			(char *)CP_HASH_DDR);

#if defined(DEBUG)
			hexdump("g_dte_kboot_tail", p_dte_kboot_tail, sizeof(DTE_KBOOT_AREA_Tail));
#endif

		// verify Controlling Data
		res = rom_scs_validate_controlling_data(&(p_dte_kboot_tail->Controlling_Data));
		if (res)
			return res;

		// verify KeyRights
		if (p_dte_kboot_tail->Key_Rights != 0x1)
			res = ERR_SCS_INVALID_KEY_RIGHTS;
	}

	return res;
}

int scs_verify_dte_bootcode(char *p_img)
{
#if defined(ENV_FPGA) || defined(DEBUG)
	printf("%s(0x%x)\n", __FUNCTION__, (unsigned int)p_img);
#endif
	int res = 0;
	unsigned int bootcode_addr;
	unsigned int bootcode_bin_size;
	DTE_BOOTCODE_AREA_Tail *p_dte_bootcode_tail = &g_dte_bootcode_tail;

	if (p_img == NULL)
		return ERR_INVALID_PARAM;

	bootcode_bin_size = g_dte_bootcode_area_size - sizeof(DTE_BOOTCODE_AREA_Tail) + 4;
	bootcode_addr = KSEG1(rom_params->Address_of_Boot_Code_Area);

	// decrypt DTE bootcode
	if ((res = decrypt_dte_bootcode((unsigned char *)p_img, bootcode_bin_size, (unsigned char *)bootcode_addr)))
		return res;

#if defined(DEBUG)
	hexdump("bootcode encrypted (first 1024bytes)", p_img, 1024);
#endif

#if defined(DEBUG)
	hexdump("bootcode decrypted (first 1024bytes)", bootcode_addr, 1024);
#endif

	// copy decrypted data
	rom_copy_memory(&g_dte_bootcode_tail, (char *)(bootcode_addr + bootcode_bin_size - 4), 4);

	// concatenate decrypted DTE bootcode with remaining header
	rom_copy_memory((char *)(bootcode_addr + bootcode_bin_size), (p_img + bootcode_bin_size), sizeof(DTE_BOOTCODE_AREA_Tail) - 4);

	if (rom_is_scs_enabled()) {
		// verify signature
		res = verify_image_signature((char *)bootcode_addr,
			g_dte_bootcode_area_size - RSA_SIZE,
			(char *)(p_dte_bootcode_tail->Signature),
			(char *)(rom_cert->External_Public_RSA_Key),
			(char *)(rom_cert->External_R2_Public_RSA_Key),
			(char *)CP_HASH_DDR);

#if defined(DEBUG)
			hexdump("g_dte_bootcode_tail", p_dte_bootcode_tail, sizeof(DTE_BOOTCODE_AREA_Tail));
#endif

		// verify Controlling Data
		res = rom_scs_validate_controlling_data(&(p_dte_bootcode_tail->Controlling_Data));
		if (res)
			return res;

		// verify KeyRights
		if (p_dte_bootcode_tail->Key_Rights != 0x1)
			res = ERR_SCS_INVALID_KEY_RIGHTS;
	}

	return res;
}
