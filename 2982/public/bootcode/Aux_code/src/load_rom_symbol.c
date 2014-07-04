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
#include "rom_symbol.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/

/************************************************************************
 *  Public variables
 ************************************************************************/
// data in ROM code
NOCS_Certificate *rom_cert;
NOCS_Params *rom_params;
NOCS_Aux_Code_Tail *rom_aux_code_tail;
unsigned int *rom_s_PageSize;
unsigned int *rom_s_BlockSize;
unsigned int *rom_s_PagePerBlock;
unsigned int *rom_sys_flash_current_pos;
int *rom_sys_boot_flash_type;
unsigned int *rom_alloc_count;
unsigned int *rom_alloc_current;

// function in ROM code
int (*rom_compare_memory)(void *s1, void *s2, unsigned int size);
void (*rom_copy_memory)(void *dst, void *src, unsigned int size);
void (*rom_sync)(void);
unsigned int (*rom_swap_endian)(unsigned int input);
int (*rom_get_secure_boot_type)(void);
int (*rom_get_boot_flash_type)(void);
int (*rom_check_image_hash)(char *p_img, unsigned int img_size, char *p_hash);
int (*rom_verify_image_signature)(char *p_img, unsigned int img_size, char *p_sig, char *p_rsa_key, char *p_rsa_key_r2, char *p_mcp_sha256);
unsigned int (*rom_skip_pkcs_v1_5_padding)(char *ptr);
int (*rom_append_padding)(char *p_buff, const unsigned int length);
int (*rom_SHA256_hash)(unsigned char *src_addr, int length, unsigned char *dst_addr, unsigned int iv[8]);
unsigned int (*rom_do_RSA)(const unsigned int signature_addr, const unsigned int rsa_key_addr, const unsigned int rsa_key_addr_r2, const unsigned int output_addr);
int (*rom_spi_n_read_image)(unsigned int dst_addr, unsigned int *page_addr, unsigned int length, unsigned int page_count, const unsigned int magic);
int (*rom_nf_read_image)(unsigned int dst_addr, unsigned int *page_addr, unsigned int length, unsigned int page_count, const unsigned char magic);
int (*rom_mmc_blk_read)(unsigned int blk_addr, unsigned int blk_cnt, unsigned char * data_buffer);
void (*rom_enable_PLL)(unsigned int addr, unsigned int delay_nop);
void (*rom_st_enable_clock)(unsigned int reg_reset, unsigned int mask_reset, unsigned int reg_clock, unsigned int mask_clock);
void (*rom_enable_clock)(unsigned int reg_reset, unsigned int mask_reset, unsigned int reg_clock, unsigned int mask_clock);
int (*rom_AES_decrypt_key_in_CW)(unsigned int algo_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry);
int (*rom_is_scs_enabled)(void);
int (*rom_scs_validate_controlling_data)(const NOCS_Controlling_Data *p_cd);
void (*rom_mask_register)(const unsigned int reg_addr, const unsigned int AND_filter, const unsigned int OR_filter);
void (*rom_mdelay)(const unsigned int ms);

#if defined(ENV_FPGA)
void (*rom_hexdump)(const char *str, const void *buf, unsigned int length);
#endif

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/

void load_rom_symbol(void)
{
	debug("%s\n", __FUNCTION__);

	rom_cert = (NOCS_Certificate *)ROM__B__g_NOCS_Certificate;
	rom_params = (NOCS_Params *)ROM__B__g_Params_Area;
	rom_aux_code_tail = (NOCS_Aux_Code_Tail *)ROM__B__g_Aux_Code_Tail;
	rom_s_PageSize = (unsigned int *)ROM__B__s_PageSize;
	rom_s_BlockSize = (unsigned int *)ROM__B__s_BlockSize;
	rom_s_PagePerBlock = (unsigned int *)ROM__B__s_PagePerBlock;
	rom_sys_boot_flash_type = (int *)ROM__B__sys_boot_flash_type;

#if defined(ROM__B__alloc_count)
	rom_alloc_count = (unsigned int *)ROM__B__alloc_count;
#else
	rom_alloc_count = (unsigned int *)ROM__b__alloc_count;
#endif
	rom_alloc_current = (unsigned int *)ROM__b__alloc_current;

	rom_compare_memory = (int (*)(void *, void *, unsigned int))ROM__T__compare_memory;
	rom_copy_memory = (void (*)(void *, void *, unsigned int))ROM__T__copy_memory;
	rom_sync = (void (*)(void))ROM__T__sync;
	rom_sys_flash_current_pos = (unsigned int *)ROM__B__sys_flash_current_pos;
	rom_swap_endian = (unsigned int (*)(unsigned int))ROM__T__swap_endian;
	rom_get_secure_boot_type = (int (*)(void))ROM__T__get_secure_boot_type;
	rom_get_boot_flash_type = (int (*)(void))ROM__T__get_boot_flash_type;
	rom_check_image_hash = (int (*)(char *, unsigned int, char *))ROM__T__check_image_hash;
	rom_verify_image_signature = (int (*)(char *, unsigned int, char *, char *, char *, char *))ROM__T__verify_image_signature;
	rom_skip_pkcs_v1_5_padding = (unsigned int (*)(char *))ROM__T__skip_pkcs_v1_5_padding;
	rom_append_padding = (int (*)(char *, const unsigned int))ROM__t__append_padding;
	rom_SHA256_hash = (int (*)(unsigned char *, int, unsigned char *, unsigned int *))ROM__T__SHA256_hash;
	rom_do_RSA = (unsigned int (*)(const unsigned int, const unsigned int, const unsigned int, const unsigned int))ROM__T__do_RSA;
	rom_enable_PLL = (void (*)(unsigned int, unsigned int))ROM__T__enable_PLL;
	rom_st_enable_clock = (void (*)(unsigned int, unsigned int, unsigned int, unsigned int))ROM__T__st_enable_clock;
	rom_enable_clock = (void (*)(unsigned int, unsigned int, unsigned int, unsigned int))ROM__T__enable_clock;
	rom_AES_decrypt_key_in_CW = (int (*)(unsigned int algo_id, unsigned char *src_addr, unsigned int length, unsigned char *dst_addr, unsigned int key_entry))ROM__T__AES_decrypt_key_in_CW;
	rom_is_scs_enabled = (int (*)(void))ROM__T__is_scs_enabled;
	rom_scs_validate_controlling_data = (int (*)(const NOCS_Controlling_Data *))ROM__T__scs_validate_controlling_data;
	rom_mask_register = (void (*)(unsigned int, unsigned int, unsigned int))ROM__T__mask_register;
    rom_mdelay = (void (*)(unsigned int))ROM__T__mdelay;

	debug("rom_sys_flash_current_pos: 0x%x\n", *rom_sys_flash_current_pos);
	debug("rom_sys_boot_flash_type: %d\n", *rom_sys_boot_flash_type);

/* check if SPI-NAND flash driver symbol exist (FPGA config may not contain such function) */
#if defined(ROM_SYMBOL_SPI_N)
	rom_spi_n_read_image = (int (*)(unsigned int, unsigned int *, unsigned int, unsigned int, const unsigned int))ROM__T__spi_n_read_image;
	//rom_sfc_read_page_to_cache = (int (*)(const unsigned int))ROM__T__sfc_read_page_to_cache;
	//rom_sfc_get_cache_tag_p = (int (*)(unsigned int))ROM__T__sfc_get_cache_tag_p;
#endif

/* check if NAND flash driver symbol exist (FPGA config may not contain such function) */
#if defined(ROM_SYMBOL_NAND)
	rom_nf_read_image = (int (*)(unsigned int, unsigned int *, unsigned int, unsigned int, const unsigned int))ROM__T__nf_read_image;
	//rom_nand_op_read_page = (int (*)(const unsigned int, char *, const unsigned int))ROM__T__nand_op_read_page;
	//rom_nand_op_get_sram = (int (*)(const int, const unsigned int))ROM__T__nand_op_get_sram;
#endif

//#if defined(ROM_SYMBOL_EMMC)
	rom_mmc_blk_read = (int (*)(unsigned int, unsigned int, unsigned char *))ROM__T__mmc_blk_read;
//#endif

#if defined(ENV_FPGA)
//	rom_hexdump = (void (*)(const char *, const void *, unsigned int))ROM__T__hexdump;
#endif

//	test_rom_symbol();
}
