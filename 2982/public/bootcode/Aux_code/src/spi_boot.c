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
extern unsigned int *rom_sys_flash_current_pos;
extern unsigned int aux_sys_flash_curent_pos;

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern void (*rom_copy_memory)(void *dst, void *src, unsigned int size);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
int get_dte_kboot_spi(unsigned int dst_addr, unsigned int size)
{
	unsigned int src_addr = aux_sys_flash_curent_pos;

	dst_addr = KSEG1(dst_addr);

	debug("%s(dst_addr: 0x%x, size: 0x%x)\n", __FUNCTION__, dst_addr, size);
	debug("src_addr: 0x%x\n", src_addr);

	rom_copy_memory((char *)dst_addr, (char *)src_addr, size);

	aux_sys_flash_curent_pos = src_addr + size;	// save the current pos

	return 0;
}

int get_dte_bootcode_spi(unsigned int dst_addr, unsigned int size)
{
	unsigned int src_addr = *rom_sys_flash_current_pos + SCS_UNCHECK_AREA;

	dst_addr = KSEG1(dst_addr);

	debug("%s(dst_addr: 0x%x, size: 0x%x)\n", __FUNCTION__, dst_addr, size);
	debug("src_addr: 0x%x\n", src_addr);

	rom_copy_memory((char *)dst_addr, (char *)src_addr, size);

	aux_sys_flash_curent_pos = src_addr + size;	// save the current pos

	return 0;
}

int get_hwsetting_spi(unsigned int dst_addr,  int size)
{
	unsigned int src_addr = *rom_sys_flash_current_pos;

	dst_addr = KSEG1(dst_addr);

	debug("%s(dst_addr: 0x%x, size: 0x%x)\n", __FUNCTION__, dst_addr, size);
	debug("src_addr: 0x%x\n", src_addr);

	rom_copy_memory((char *)dst_addr, (char *)src_addr, size);
	return 0;
}
