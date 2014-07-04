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
#include "nf_reg.h"
#include "reset_def.h"
#include "error_type.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define SWITCH_NF_BUS(select)		(REG32(NF_DBUS_MUX) = select)

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int *rom_s_PageSize;
extern unsigned int *rom_s_BlockSize;
extern unsigned int *rom_s_PagePerBlock;
extern unsigned int *rom_sys_flash_current_pos;
extern unsigned int aux_sys_flash_curent_pos;
/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/
static unsigned int s_flash_fw_pos;
/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int (*rom_nf_read_image)(unsigned int dst_addr, unsigned int *page_addr, unsigned int length, unsigned int page_count, const unsigned char magic);
//extern int (*rom_nand_op_read_page)(const unsigned int page_no, char *dest_addr, const unsigned int page_size);
//extern unsigned int (*rom_nand_op_get_sram)(const int mapping, const unsigned int offset);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/

/************************************************************************
 *  Function body
 ************************************************************************/
#if 0
static unsigned int nf_get_spare(void)
{
#if !defined(ROM_SYMBOL_NAND)
	printf("ROM code symbol have no %s functions!\n", "NAND");
	printf("hint: check rom_symbol.h is correct\n");
	return -1;
#endif
	return rom_nand_op_get_sram(0x2, 0);
}

/*
 * nf_read_page C version
 *
 * input argument:
 *	page_no: page address
 *	dest_addr: DDR address
 * involved variable:
 *	s_PageSize: page size
 * return:
 *	0 means success, others means failed
 */
static unsigned int nf_read_page_c(unsigned int page_no, unsigned int dest_addr)
{
#if !defined(ROM_SYMBOL_NAND)
	printf("ROM code symbol have no %s functions!\n", "NAND");
	printf("hint: check rom_symbol.h is correct\n");
	return -1;
#endif

#if defined(ENV_FPGA)
	printf("%s(page_no=0x%x, dest_addr=0x%x)\n", __FUNCTION__, page_no, dest_addr);
#endif

	if (rom_nand_op_read_page(page_no, (char *)dest_addr, *rom_s_PageSize) != 0)
		return -1;	//ERR_NF_READ_ECC_FAIL;	// ECC not correctable
	else
		return 0;
}

/*
 * read image from NAND to memory (find next backup if ECC error)
 *
 * input:
 *	[in] dst_addr: destination memory address
 *	[in/out] page_addr: source page address to find (not necessary aligned to block)
 *	[in] length: image length
 *	[in] page_count: start page counter (3rd, 4th byte) in spare area
 *	[in] magic: 1st byte in spare area
 *
 * return:
 *	0 means read success, others means error
 *
 * note:
 *	For those images who do not start from the 1st page of a block (such as Params area or Aux code area),
 *	since multiple images are in the same block,
 *	so page_count must be provided in order to locate the exact page within one block.
 *
 *	For normal image such as bootcode, it always starts from the 1st page of a block.
 *	(page_count=0)
 *
 *	If the image size is more than one block, page_count should work as well.
 *
 */
static int nf_read_image(unsigned int dst_addr,
	unsigned int *page_addr,
	unsigned int length,
	unsigned int page_count,
	const unsigned char magic)
{
#if !defined(ROM_SYMBOL_NAND)
	printf("ROM code symbol have no %s functions!\n", "NAND");
	printf("hint: check rom_symbol.h is correct\n");
	return -1;
#endif

#if defined(ENV_FPGA)
	printf("%s(dst_addr=%x, page_addr=%x, length=%x, magic=%x)\n", __FUNCTION__, dst_addr, *page_addr, length, magic);
#endif
	int res = 0;
	unsigned int count = 0;
	unsigned int retry = 0x100;	//NAND_HW_SETTING_RETRY;
	unsigned int spare_tags;
	unsigned int current_page = *page_addr;
	unsigned int page_size = *rom_s_PageSize;

	if (length % page_size) {
		// align length to page boundary
		length = (length / page_size + 1) * page_size;
	}

	while (count < length) {
		res = nf_read_page_c(current_page, dst_addr);
		if (res) {	// ECC error happened
#if defined(ENV_FPGA)
			printf("\t==> ECC error\n");
			printf("0xb8010034: 0x%x\n", REG32(NF_BLANK_CHK));
#endif
jump_to_next_blk:
			if (--retry) {
				// jump to the same offset of next block
				current_page += *rom_s_PagePerBlock;
				continue;
			}
			else	// retry too many times, return failed
				return -1;
		}

		// check spare area to see if this correct page
		spare_tags = ((page_count & 0xffff) << 16) | magic;
#if defined(ENV_FPGA)
		printf("spare_tags: 0x%x, nf_get_spare(): 0x%x\n", spare_tags, nf_get_spare());
#endif
		if (spare_tags != nf_get_spare()) {
			// maybe page counter is not correct, or magic number not match, or just an empty page (it's not the page we want anyway)
			goto jump_to_next_blk;
		}

		// read ok, go to next page
		current_page++;
		dst_addr += page_size;
		count += page_size;
		page_count++;	// remember to increment page counter in spare area
	}

	// update page_addr value
	*page_addr = current_page;
	return 0;
}
#endif /* 0 */

int get_dte_kboot_nand(unsigned int dst_addr, unsigned int size)
{
	unsigned int page_addr = aux_sys_flash_curent_pos;//*rom_sys_flash_current_pos;
	unsigned int tmp = *rom_s_PagePerBlock;

	// align page_addr to the beginning of next block
	if (page_addr % tmp)
		page_addr = (page_addr / tmp + 1) * tmp;

	debug("page_addr: 0x%x\n", page_addr);

	SWITCH_NF_BUS(NF_DBUS_DDR);
	if ( rom_nf_read_image(dst_addr, &page_addr, size, 0, KBOOT_MAGIC_NUM) )
		return ERR_GET_DTE_KBOOT_FAILED;

	aux_sys_flash_curent_pos = page_addr; // save the current pos

	return 0;
}

int get_dte_bootcode_nand(unsigned int dst_addr, unsigned int size)
{
	unsigned int page_addr = *rom_sys_flash_current_pos;
	unsigned int tmp = *rom_s_PagePerBlock;

	// align page_addr to the beginning of next block
	if (page_addr % tmp)
		page_addr = (page_addr / tmp + 1) * tmp;

	debug("page_addr: 0x%x\n", page_addr);

	SWITCH_NF_BUS(NF_DBUS_DDR);
	if ( rom_nf_read_image(dst_addr, &page_addr, size, 0, BOOTCODE_MAGIC_NUM) )
		return ERR_GET_DTE_BOOTCODE_FAILED;

	aux_sys_flash_curent_pos = page_addr; // save the current pos

	return 0;
}

int get_hwsetting_nand(unsigned int dst_addr,  int size)
{
	unsigned int page_addr = *rom_sys_flash_current_pos;
	unsigned int tmp = *rom_s_PagePerBlock;
	unsigned int page_count;

	//page_count = page_addr - (NAND_START_BLOCK * tmp);
	page_count = page_addr%tmp;

	debug("page_addr: 0x%x, page_count: 0x%x\n", page_addr, page_count);

	SWITCH_NF_BUS(NF_DBUS_CP_SRAM);
	if ( rom_nf_read_image(dst_addr, &page_addr, size, page_count, HW_SETTING_MAGIC_NUM) )
		return ERR_HWSETTING_FAILED;

	return 0;
}

int get_sec_fw_nocs_certificate(unsigned int flash_offset, unsigned int dst_addr)
{
	//@TODO: not verify yet
	// SEC FW NOCS Certificate starts from pre-defined flash offset
	s_flash_fw_pos = flash_offset / *rom_s_PageSize;
	SWITCH_NF_BUS(NF_DBUS_CP_SRAM);
	if ( rom_nf_read_image(dst_addr, &s_flash_fw_pos, sizeof(SEC_FW_NOCS_Certificate), 0, SEC_FW_MAGIC_NUM) )
		return ERR_GET_FW_NOCS_CERTIFICATE_FAILED;

	return 0;
}

int get_sec_fw(unsigned int dst_addr)
{
	//@TODO: get SEC FW area (right behind SEC FW NOCS Certificate)
	return 0;
}
