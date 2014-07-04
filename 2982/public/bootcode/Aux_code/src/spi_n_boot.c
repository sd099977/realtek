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
#include "sfc_reg.h"
#include "NOCS.h"
#include "reset_def.h"
#include "error_type.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define SPI_NAND_BASE_ADDR	0xbec00000	/* SPI-NAND flash address (0xbfc00000 may be in ROM region) */

/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int *rom_s_PageSize;
extern unsigned int *rom_s_BlockSize;
extern unsigned int *rom_s_PagePerBlock;
extern unsigned int *rom_sys_flash_current_pos;

extern int (*rom_spi_n_read_image)(unsigned int dst_addr, unsigned int *page_addr, unsigned int length, unsigned int page_count, const unsigned int magic);
//extern void (*rom_sync)(void);
//extern unsigned int (*rom_swap_endian)(unsigned int input);
//extern int (*rom_sfc_read_page_to_cache)(const unsigned int page_no);
//extern int (*rom_sfc_get_cache_tag_p)(unsigned int page_no);

/************************************************************************
 *  Public variables
 ************************************************************************/

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
#if 0
/*
 * copy flash data from cache buffer to destination
 *
 * input:
 *	[in] dst_addr: destination memory address
 *	[in/out] page_addr: page address (decide even/odd block number for Micron flash)
 *	[in] length: image length
 *
 * return:
 *	number of bytes have been copied (multiple of 4B)
 *
 * note:
 *	input length may exceed page size, however this function only copies at most one page size on each call
 *	(because there are only at most one page size data bytes in the cache buffer)
 */
static unsigned int sfc_copy_from_cache(unsigned int dst_addr, unsigned int page_addr, unsigned int length)
{
#if !defined(ROM_SYMBOL_SPI_N)
	printf("ROM code symbol have no %s functions!\n", "SPI-NAND");
	printf("hint: check rom_symbol.h is correct\n");
	return -1;
#endif

#if defined(ENV_FPGA)
	printf("%s(dst_addr=0x%x, page_addr=0x%x, length=0x%x)\n", __FUNCTION__, dst_addr, page_addr, length);
#endif
	unsigned int i, src;
	unsigned int *p_dst = (unsigned int *)dst_addr;
	unsigned int count = (length > *rom_s_PageSize ? *rom_s_PageSize : length);	// at most copy 1 page

	REG32(SFC_OPCODE) = 0x00000003;

#ifdef _SPI_NAND_CTRL
	REG32(SFC_CTL) = 0x00000019; /* dataen = 1, adren = 1, dmycnt = 1 */
#else
	REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
#endif
	rom_sync();

	for (i = 0 ; i < count / 4; i++) {
#ifdef _SPI_NAND_CTRL
		set_spi_n_address(SPI_ADDR_CNT_2, i*4);
		src = SPI_NAND_BASE_ADDR;
#else
		src = SPI_NAND_BASE_ADDR + (i*4 << 8);
#endif

		p_dst[i] = rom_swap_endian(REG32(src));
	}
	// return how many bytes have been copied
	return (i * 4);
}

/*
 * read image from SPI-NAND to memory (find next backup if ECC error)
 *
 * input:
 *	[in] dst_addr: destination memory address
 *	[in/out] page_addr: source page address to find (not necessary aligned to block)
 *	[in] length: image length
 *	[in] page_count: start page counter (3rd, 4th byte) in ECC protected spare area
 *	[in] magic: 1st byte in ECC protected spare area
 *
 * return:
 *	0 means read success, others means error
 *
 * note:
 *	First 4 bytes in spare area are not protected by ECC (see spec).
 *
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
int spi_n_read_image(unsigned int dst_addr,
	unsigned int *page_addr,
	unsigned int length,
	unsigned int page_count,
	const unsigned int magic)
{
#if !defined(ROM_SYMBOL_SPI_N)
	printf("ROM code symbol have no %s functions!\n", "SPI-NAND");
	printf("hint: check rom_symbol.h is correct\n");
	return -1;
#endif

#if defined(ENV_FPGA)
	printf("%s(dst_addr=%x, page_addr=%x, length=%x, magic=%x)\n", __FUNCTION__, dst_addr, *page_addr, length, magic);
#endif
	int res = 0;
	unsigned int count = 0;
	unsigned int retry = 0x100;	//NAND_HW_SETTING_RETRY;
	unsigned int spare_tags = 0;
	unsigned int current_page = *page_addr;
	unsigned int temp = 0;

	while (count < length) {
		res = rom_sfc_read_page_to_cache(current_page);
		if (res) {	// ECC error happened
#if defined(ENV_FPGA)
			printf("\t==> ECC error\n");
#endif
jump_to_next_blk:
			if (--retry) {
				// jump to the same offset of next block
				current_page += *rom_spi_n_page_per_block;
				continue;
			}
			else	// retry too many times, return failed
				return -1;
		}

		// check spare area to see if this correct page
		temp = ((page_count & 0xffff) << 16) | (magic & 0xffff);
		spare_tags = (unsigned int)rom_sfc_get_cache_tag_p(current_page);
		if (spare_tags != temp) {
#if defined(ENV_FPGA)
			printf("supposed_tags: 0x%x, spare_tags: 0x%x\n", temp, spare_tags);
			temp = sfc_copy_from_cache(dst_addr, current_page, length - count);
			hexdump("read from cache", (char *)dst_addr, 0x100);
#endif
			// maybe page counter is not correct, or magic number not match, or just an empty page (it's not the page we want anyway)
			goto jump_to_next_blk;
		}

		// read image from cache to destination
		temp = sfc_copy_from_cache(dst_addr, current_page, (length - count));

		// go to next page
		current_page++;
		dst_addr += temp;
		count += temp;
		page_count++;	// remember to increment page counter in spare area
	}

	// update page_addr value
	*page_addr = current_page;
	return 0;
}
#endif /* 0 */

int get_dte_kboot_spi_n(unsigned int dst_addr, unsigned int size)
{
	unsigned int page_addr = *rom_sys_flash_current_pos; // FIXME
	unsigned int tmp = *rom_s_PagePerBlock;

	// align page_addr to the beginning of next block
	if (page_addr % tmp)
		page_addr = (page_addr / tmp + 1) * tmp;

	if ( rom_spi_n_read_image(dst_addr, &page_addr, size, 0, KBOOT_MAGIC_NUM) )
		return ERR_GET_DTE_KBOOT_FAILED;

	return 0;
}

int get_dte_bootcode_spi_n(unsigned int dst_addr, unsigned int size)
{
	unsigned int page_addr = *rom_sys_flash_current_pos;
	unsigned int tmp = *rom_s_PagePerBlock;

	// align page_addr to the beginning of next block
	if (page_addr % tmp)
		page_addr = (page_addr / tmp + 1) * tmp;

	if ( rom_spi_n_read_image(dst_addr, &page_addr, size, 0, BOOTCODE_MAGIC_NUM) )
		return ERR_GET_DTE_BOOTCODE_FAILED;

	return 0;
}
