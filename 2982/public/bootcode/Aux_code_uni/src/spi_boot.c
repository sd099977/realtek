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

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int g_sys_flash_current_pos;
extern unsigned int aux_sys_flash_curent_pos;

extern NOCS_Certificate g_NOCS_Certificate;
extern NOCS_Params g_Params_Area;
/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern void copy_memory(void *dst, void *src, unsigned int size);
extern int get_secure_boot_type(void);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
int get_nocs_certificate_spi(unsigned int dst_addr)
{
	int boot_type = get_secure_boot_type();

	if (boot_type == NONE_SECURE_BOOT)
		g_sys_flash_current_pos = SPI_BASE_ADDR + 0x8000; 	// flash physical address 0x8000
	else {
		g_sys_flash_current_pos = SPI_BASE_ADDR + 0x1004C00;	// flash physical address 0 (shift 16MB in order to avoid ROM code region)
	}
	copy_memory((char *)dst_addr, (char *)g_sys_flash_current_pos, CERTIFICATE_SIZE);

	g_sys_flash_current_pos += CERTIFICATE_SIZE;

	if (get_ic_version() == VER_A)
		g_sys_flash_current_pos -= (CERTIFICATE_SIZE - 0x21c);

	return 0;
}

int get_nocs_params_spi(unsigned int dst_addr)
{
	unsigned int size = g_NOCS_Certificate.Size_Of_SCS_Params_Area;

	copy_memory((char *)dst_addr, (char *)g_sys_flash_current_pos, size);
	g_sys_flash_current_pos += size;
	return 0;
}

int get_nocs_aux_code_spi(unsigned int dst_addr)
{
	unsigned int size = g_Params_Area.Size_of_Aux_Code_Area;

	g_sys_flash_current_pos += size;
	return 0;
}

int get_hwsetting_spi(unsigned int dst_addr,  int size)
{
	unsigned int src_addr = g_sys_flash_current_pos;

	dst_addr = KSEG1(dst_addr);

	debug("%s(dst_addr: 0x%x, size: 0x%x)\n", __FUNCTION__, dst_addr, size);
	debug("src_addr: 0x%x\n", src_addr);

	copy_memory((char *)dst_addr, (char *)src_addr, size);
	return 0;
}

int get_dte_bootcode_spi(unsigned int dst_addr, unsigned int size)
{
	unsigned int src_addr = g_sys_flash_current_pos + SCS_UNCHECK_AREA;

	dst_addr = KSEG1(dst_addr);

	debug("%s(dst_addr: 0x%x, size: 0x%x)\n", __FUNCTION__, dst_addr, size);
	debug("src_addr: 0x%x\n", src_addr);

	copy_memory((char *)dst_addr, (char *)src_addr, size);

	aux_sys_flash_curent_pos = src_addr + size;	// save the current pos

	return 0;
}

int get_dte_kboot_spi(unsigned int dst_addr, unsigned int size)
{
	unsigned int src_addr = aux_sys_flash_curent_pos;

	dst_addr = KSEG1(dst_addr);

	debug("%s(dst_addr: 0x%x, size: 0x%x)\n", __FUNCTION__, dst_addr, size);
	debug("src_addr: 0x%x\n", src_addr);

	copy_memory((char *)dst_addr, (char *)src_addr, size);

	aux_sys_flash_curent_pos = src_addr + size;	// save the current pos

	return 0;
}

