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
#include "flash_nand_profile.h"
#include "flash_nand_onfi.h"
#include "nand_operation.h"

/************************************************************************
 *  Definitions
 ************************************************************************/
#define SWITCH_NF_BUS(select)		(REG32(NF_DBUS_MUX) = select)

#define LITTLE_ENDIAN
/************************************************************************
 *  External variables
 ************************************************************************/
extern unsigned int s_PageSize;
extern unsigned int s_BlockSize;
extern unsigned int s_PagePerBlock;
extern unsigned int s_FlashID4Bytes;

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
extern int get_secure_boot_type(void);
extern int get_nand_boot_type(int *ecc_type, int *access_mode, int *page_size);
extern unsigned int calculate_image_checksum(unsigned int start_addr, unsigned int len);

/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/
static unsigned int nf_read_page_c(unsigned int page_no, unsigned int dest_addr);
static unsigned int nf_read_to_PP_first_c(unsigned int col_addr, unsigned int page_addr, unsigned int length);
static int nf_read_id(unsigned addr, unsigned int *id);
static void nf_get_info_from_id(const unsigned int id, unsigned int *page_size, unsigned int *block_size);
static int nf_get_info_from_onfi(unsigned int *page_size, unsigned int *page_per_block, unsigned int *block_size);

/************************************************************************
 *  Function body
 ************************************************************************/
#if 1
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
unsigned int nf_read_page_c(unsigned int page_no, unsigned int dest_addr)
{
#if defined(DEBUG)
	printf("\n%s (page_no=0x%x, dest_addr=0x%x)\n", __FUNCTION__, page_no, dest_addr);
#endif

	if (nand_op_read_page(page_no, (char *)dest_addr, s_PageSize) != 0)
		return ERR_NF_READ_ECC_FAIL;	// ECC not correctable
	else
		return 0;
}

/*
 * read_to_PP_first C version
 *
 * input:
 *	col_addr: column address
 *	page_addr: page no.
 *	length: read length
 * return:
 *	0 means read to PP ok, others mean ECC failed
 *
 */
static unsigned int nf_read_to_PP_first_c(unsigned int col_addr, unsigned int page_addr, unsigned int length)
{
	if (nand_op_read_to_PP_first(col_addr, page_addr, length) != 0)
		return ERR_NF_READ_ECC_FAIL;	// ECC not correctable
	else
		return 0;
}

/*
 * get flash profile data
 *
 * input argument:
 *	profile_page_no_limit: maximum search limit
 *	page_increment: page increment within loop
 * return:
 *	0 means success, others means failed
 *
 */
static int nf_get_flash_profile_c(unsigned int profile_page_no_limit, unsigned int page_increment)
{
	unsigned int page_no;
	unsigned int checksum1, checksum2;
	t_nand_profile *profile;
	unsigned int identifier[2];

	/* profile is not allowed in Nagra secure boot */
	if (get_secure_boot_type() == NAGRA_SECURE_BOOT)
		return -1;

#if defined(LITTLE_ENDIAN)
	identifier[0] = 0x4c414552; // 'REAL'
	identifier[1] = 0x2e4b4554; // 'TEK.'
#else
	identifier[0] = 0x5245414c; // 'REAL' (big-endian)
	identifier[1] = 0x54454b2e; // 'TEK.' (big-endian)
#endif

	s_PageSize = s_BlockSize = s_PagePerBlock = 0;

	for (page_no = 0; page_no < profile_page_no_limit; page_no += page_increment) {
		if (nf_read_to_PP_first_c(0, page_no, 512))
			continue;	// next one

#if defined(DEBUG)
		printf("c");
#endif

		// disable read_by_pp (so CPU can access PP)
		REG32(NF_PP_RDY) = 0;

		// enable address mapping
#if defined(LITTLE_ENDIAN)
		REG32(NF_SRAM_CTL) = 0x30;
#else
		REG32(NF_SRAM_CTL) = 0x10;
#endif

#if defined(DEBUG)
		printf("\nread page 0x%x to PP\n", page_no);
		hexdump("profile in PP", (char *)NF_SRAM_BASE, sizeof(t_nand_profile));
#endif

		// check profile identifier
		if ( (REG32(NF_SRAM_BASE) == identifier[0])
			&& (REG32(NF_SRAM_BASE + 4) == identifier[1]) ) {

#if defined(DEBUG)
			printf("d");
#endif

			profile = (t_nand_profile *)NF_SRAM_BASE;

			// calculate byte checksum
			checksum1 = calculate_image_checksum(NF_SRAM_BASE, 0x80);
			checksum2 = *(unsigned int *)(profile->checksum);

#if defined(DEBUG)
			printf("\ncalculate_image_checksum: 0x%08x", checksum1);
			printf("\nprofile->checksum: 0x%08x\n", checksum2);
#endif

			// verify
			if (checksum1 == checksum2) {
				// get NAND flash info
				s_FlashID4Bytes = *(unsigned int *)(profile->manufacturer_id);
				//s_PageSize = profile->data_per_page;
				//s_PagePerBlock = profile->page_per_block;
				s_PageSize = REG32(NF_SRAM_BASE+offsetof(t_nand_profile, data_per_page));
				s_PagePerBlock = REG32(NF_SRAM_BASE+offsetof(t_nand_profile, page_per_block));
				s_BlockSize = s_PagePerBlock * s_PageSize;

#if defined(DEBUG)
				printf("e");
				printf("\nprofile->manufacturer_id (first 4B): 0x%x", *(unsigned int *)(profile->manufacturer_id));
				printf("\nprofile->data_per_page: 0x%x", profile->data_per_page);
				printf("\nprofile->page_per_block: 0x%x", profile->page_per_block);
				printf("\nREG32(data_per_page): 0x%x", REG32(NF_SRAM_BASE+offsetof(t_nand_profile, data_per_page)));
				printf("\nREG32(page_per_block):0x%x\n", REG32(NF_SRAM_BASE+offsetof(t_nand_profile, page_per_block)));
				printf("\n");
#endif

				break;
			}
		}

		// disable address mapping
		REG32(NF_SRAM_CTL) = 0;
	}

	// disable address mapping (again to make sure it's really disabled)
	REG32(NF_SRAM_CTL) = 0;

	if ( (s_PageSize == 0) || (s_BlockSize == 0) || (s_PagePerBlock == 0) ) {
#if defined(DEBUG)
		printf("\nno profile\n");
#endif
		return -1;
	}
	else
		return 0;
}

#if 0 //removed by Andy Teng, MacArthur2 does not support 24bit ecc or 40bit ecc
static unsigned int nf_is_12bit_ecc(void)
{
	return nand_op_is12bit_ecc();
}

static unsigned int nf_is_24bit_ecc(void)
{
	return 0;
}
#endif

static unsigned int nf_get_spare(void)
{
#if defined(LITTLE_ENDIAN)
	return nand_op_get_sram(0x2, 0);
#else
	/* swap endian */
	/* the data in spare is ex. 23 00 00 00, but the magic number 23 is in LSB */
	return swap_endian(nand_op_get_sram(0x2, 0));
#endif
}

/*
 * issue RESET command to nand flash
 */
static int nf_reset(void)
{
	if (nand_op_reset() != 0)
		return ERR_NF_RESET_FAIL;	// time-out
	else
		return 0;
}

static int nf_identify(void)
{
	int res;

	/* read id */
	s_FlashID4Bytes = 0;
	if ((res = nf_read_id(0, &s_FlashID4Bytes)))
		return res;

	// first search flash profile
	if (nf_get_flash_profile_c(NAND_PROFILE_LIMIT, NAND_PROFILE_INCREMENT)) {
		// profile not exist, try to see if ONFI available
		res = nf_get_info_from_onfi(&s_PageSize, &s_PagePerBlock, &s_BlockSize);
		if (res) {
#if defined(DEBUG)
			printf("\nONFI not found: 0x%x\n", res);
#endif
			// ONFI unavailable, get info from flash id instead
			nf_get_info_from_id(s_FlashID4Bytes, &s_PageSize, &s_BlockSize);
			s_PagePerBlock = s_BlockSize / s_PageSize;
		}
	}

#if defined(DEBUG)
	printf("flash id: 0x%x", s_FlashID4Bytes);
	printf("\npage size: 0x%x", s_PageSize);
	printf("\nblock size: 0x%x", s_BlockSize);
	printf("\npage per block: 0x%x\n", s_PagePerBlock);
#endif

	if ( (s_PageSize == 0) || (s_BlockSize == 0) || (s_PagePerBlock == 0) )
		return ERR_NF_IDENTIFY_FAIL;
	else
		return 0;
}

static int nf_read_id(unsigned int addr, unsigned int *id)
{
	if (nand_op_read_id(addr, id) != 0)
		return ERR_NF_READ_ID_FAIL;
	else
		return 0;
}

static void nf_get_info_from_id(const unsigned int id, unsigned int *page_size, unsigned int *block_size)
{
	unsigned char c;
	unsigned int val;

	c = id >> 24;	// get 4th byte ID
#if 0
	if (nand_op_is_6bit_ecc()) {	// 6-bit ECC, use original rule like Mars
#endif
		val = c & 0x3;
		*page_size = 1024 << val;
		val = (c & 0x30) >> 4;
		*block_size = 0x10000 << val;
#if 0
	}
	else {	// 12-bit ECC
		val = c & 0x3;
		*page_size = 2048 << val;

		// rule for block size depend on different brand...
		if ((id & 0xff) == 0xad) {
			// for HYNIX flash:
			//
			// block size	I/O7	I/O5	I/O4
			// (KB)
			// -----------------------------------
			// 128		0	0	0
			// 256		0	0	1
			// 512		0	1	0
			// 768		0	1	1
			// 1024 	1	0	0
			// 2048 	1	0	1
			val = ((c & 0x80) >> 5) | ((c >> 4) & 0x3);
			if (val == 0)
				*block_size = 0x20000;		// 128KB
			else if (val == 5)
				*block_size = 0x200000; 	 // 2048KB
			else
				*block_size = 0x40000 * val;	// 256KB * factor
		}
		else {
			// for TOSHIBA, SAMSUNG flash:
			//
			// block size	I/O7	I/O5	I/O4
			// (KB)
			// -----------------------------------
			// 128		0	0	0
			// 256		0	0	1
			// 512		0	1	0
			// 1024 	0	1	1
			val = (c >> 4) & 0x3;
			*block_size = 0x20000 << val;	// 128KB * 2^factor
		}
	}
#endif
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
int nf_read_image(unsigned int dst_addr,
	unsigned int *page_addr,
	unsigned int length,
	unsigned int page_count,
	const unsigned char magic)
{
#if defined(DEBUG)
	printf("\n%s (dst_addr=0x%x, page_addr=0x%x, length=0x%x, magic=0x%x)\n", __FUNCTION__, dst_addr, *page_addr, length, magic);
#endif
	int res = 0;
	unsigned int count = 0;
	unsigned int retry = NAND_HW_SETTING_RETRY;
	unsigned int spare_tags;
	unsigned int current_page = *page_addr;

	if (length % s_PageSize) {
		// align length to page boundary
		length = (length / s_PageSize + 1) * s_PageSize;
	}

	while (count < length) {
		res = nf_read_page_c(current_page, dst_addr);
		if (res) {	// ECC error happened
#if defined(DEBUG)
			printf("\t==> ECC error\n");
			printf("0xb8010034: 0x%x\n", REG32(NF_BLANK_CHK));
#endif
jump_to_next_blk:
			if (--retry) {
				// jump to the same offset of next block
				current_page += s_PagePerBlock;
				continue;
			}
			else	// retry too many times, return failed
				return -1;
		}

		// check spare area to see if this correct page
		spare_tags = ((page_count & 0xffff) << 16) | magic;
#if defined(DEBUG)
			printf("spare_tags: 0x%x, nf_get_spare(): 0x%x\n", spare_tags, nf_get_spare());
#endif
		if (spare_tags != nf_get_spare()) {
			// maybe page counter is not correct, or magic number not match, or just an empty page (it's not the page we want anyway)
			goto jump_to_next_blk;
		}

		// read ok, go to next page
		current_page++;
		dst_addr += s_PageSize;
		count += s_PageSize;
		page_count++;	// remember to increment page counter in spare area
	}

	// update page_addr value
	*page_addr = current_page;
	return 0;
}

static unsigned short onfi_crc16(unsigned short crc, unsigned char const *p, unsigned int len)
{
	int i;
	while (len--) {
		crc ^= *p++ << 8;
		for (i = 0; i < 8; i++)
			crc = (crc << 1) ^ ((crc & 0x8000) ? 0x8005 : 0);
	}

	return crc;
}

static int nf_get_info_from_onfi(unsigned int *page_size, unsigned int *page_per_block, unsigned int *block_size)
{
	struct nand_onfi_params onfi_params[3];
	unsigned int tmp = 0;
	int i;
	unsigned short crc_val;
	unsigned char onfi_signature[4];

	memset(onfi_params, 0, sizeof(onfi_params));

	// read id to check ONFI
	if (nf_read_id(0x20, &tmp))
		return -1;

	if (tmp != 0x49464e4f)	// 'ONFI' in little-endian
		return -1;

	// read parameter page
	if (nand_op_read_onfi_params((unsigned int *)onfi_params, sizeof(onfi_params)))
		return -2;

	onfi_signature[0] = 0x4f;
	onfi_signature[1] = 0x4e;
	onfi_signature[2] = 0x46;
	onfi_signature[3] = 0x49;

	// at most 3 copies of parameter page
	for (i = 0; i < 3; i++) {
#if defined(DEBUG)
		hexdump("onfi_params", (char *)(&onfi_params[i]), sizeof(onfi_params[i]));
#endif
		// validate signature
		if ( compare_memory(onfi_params[i].sig, onfi_signature, sizeof(onfi_signature)) ) {
#if defined(DEBUG)
			printf("signature not match: ");
			for (tmp = 0; tmp < 4; tmp++) {
				printf("0x%x, ", onfi_params[i].sig[tmp]);
			}
			printf(" \n");
#endif
			continue;
		}

		// validate crc
		crc_val = onfi_crc16(ONFI_CRC_BASE, (unsigned char *)(&onfi_params[i]), 254);
#if defined(DEBUG)
		printf("crc in nofi_params: 0x%x, crc16: 0x%x\n", onfi_params[i].crc, crc_val);
#endif
		if (crc_val == onfi_params[i].crc) {
			// ONFI parameter found
			*page_size = onfi_params[i].byte_per_page;
			*page_per_block = onfi_params[i].pages_per_block;
			*block_size = (*page_size) * (*page_per_block);
			break;	// crc correct
		}
	}

	if (i == 3)
		return -3;	// crc all failed
	else
		return 0;
}

int init_nand(void)
{
#if defined(DEBUG)
	printf("\n%s", __FUNCTION__);
#endif
	int res = 0;
	int ecc_type, access_mode, page_size;

	/* get ECC type & access mode & page size*/
	if ((res = get_nand_boot_type(&ecc_type, &access_mode, &page_size)))
		return res;
	else {
		REG32(NF_ECC_SEL) = ecc_type;
		REG32(NF_RND_RW_EN) = access_mode;
	}

	nand_op_set_timing(0x2, 0x2, 0x2, 0x9);
	REG32(NF_SPR_DDR_CTL) &= ~0x20000000;	// disable spare to DDR

	/* reset flash */
	if ((res = nf_reset()))
		return res;

	/* identify flash */
	if ((res = nf_identify()))
		return res;

	/* set random access mode registers if enabled */
	if (nand_op_is_random_mode()) {

#if defined(DEBUG)
		printf("random access mode\n");
#endif

		REG32(NF_RND_CMD1) = 0x5;
		REG32(NF_RND_CMD2) = 0xe0;
		nand_op_set_random_col_addr(0, s_PageSize);
	}

	/* switch NF dbus to CP SRAM */
	REG32(NF_DBUS_MUX) = 0x1;

	return res;
}
#endif /* 0 */

static unsigned int align_page_count(unsigned int length)
{
	unsigned int page_cnt;
	unsigned int aligned_size;

	aligned_size = (length + s_PageSize - 1) & ~(s_PageSize - 1);
	page_cnt = aligned_size / s_PageSize;

#if defined(DEBUG)
	printf("org size = 0x%x, align to size = 0x%x, page_cnt = 0x%x\n", length, aligned_size, page_cnt);
#endif

	return page_cnt;
}

/*********************************************************************************************************/
int get_nocs_certificate_nand(unsigned int dst_addr)
{
	if (init_nand())
		return ERR_GET_NOCS_CERTIFICATE_FAILED;

	// start from block 6 (same with Magellan)
	g_sys_flash_current_pos = 6 * s_PagePerBlock;

	if ( nf_read_image(dst_addr, &g_sys_flash_current_pos, CERTIFICATE_SIZE, 0, HW_SETTING_MAGIC_NUM) )
		return ERR_GET_NOCS_CERTIFICATE_FAILED;

#if defined(DEBUG)
	hexdump("NOCS Certificate from NAND", (char *)dst_addr, CERTIFICATE_SIZE);
	printf("g_sys_flash_current_pos: 0x%x\n", g_sys_flash_current_pos);
#endif
	return 0;
}

int get_nocs_params_nand(unsigned int dst_addr)
{
	unsigned int size = g_NOCS_Certificate.Size_Of_SCS_Params_Area;

	// Params Area is in the next page of Certificate
	if ( nf_read_image(dst_addr, &g_sys_flash_current_pos, size, g_sys_flash_current_pos % s_PagePerBlock, HW_SETTING_MAGIC_NUM) )
		return ERR_GET_PARAM_AREA_FAILED;

#if defined(DEBUG)
	hexdump("Params Area from NAND", (char *)dst_addr, size);
	printf("g_sys_flash_current_pos: 0x%x\n", g_sys_flash_current_pos);
#endif

	return 0;
}

int get_nocs_aux_code_nand(unsigned int dst_addr)
{
	unsigned int size = g_Params_Area.Size_of_Aux_Code_Area;
	unsigned int page_cnt;

	page_cnt = align_page_count(size);

	g_sys_flash_current_pos += page_cnt;

#if defined(DEBUG)
	printf("read cnt: 0x%x\n", page_cnt);
	printf("g_sys_flash_current_pos: 0x%x\n", g_sys_flash_current_pos);
#endif

	return 0;
}

int get_hwsetting_nand(unsigned int dst_addr,  int size)
{
	unsigned int page_addr = g_sys_flash_current_pos;
	unsigned int tmp = s_PagePerBlock;
	unsigned int page_cnt;

	page_cnt = page_addr % tmp;

	debug("page_addr: 0x%x, page_count: 0x%x\n", page_addr, page_cnt);

	SWITCH_NF_BUS(NF_DBUS_CP_SRAM);
	if ( nf_read_image(dst_addr, &page_addr, size, page_cnt, HW_SETTING_MAGIC_NUM) )
		return ERR_HWSETTING_FAILED;

	return 0;
}

int get_dte_bootcode_nand(unsigned int dst_addr, unsigned int size)
{
	unsigned int page_addr = g_sys_flash_current_pos;
	unsigned int tmp = s_PagePerBlock;

	// align page_addr to the beginning of next block
	if (page_addr % tmp)
		page_addr = (page_addr / tmp + 1) * tmp;

	debug("page_addr: 0x%x\n", page_addr);

	SWITCH_NF_BUS(NF_DBUS_DDR);
	if ( nf_read_image(dst_addr, &page_addr, size, 0, BOOTCODE_MAGIC_NUM) )
		return ERR_GET_DTE_BOOTCODE_FAILED;

	aux_sys_flash_curent_pos = page_addr; // save the current pos

	return 0;
}

int get_dte_kboot_nand(unsigned int dst_addr, unsigned int size)
{
	unsigned int page_addr = aux_sys_flash_curent_pos;
	unsigned int tmp = s_PagePerBlock;

	// align page_addr to the beginning of next block
	if (page_addr % tmp)
		page_addr = (page_addr / tmp + 1) * tmp;

	debug("page_addr: 0x%x\n", page_addr);

	SWITCH_NF_BUS(NF_DBUS_DDR);
	if ( nf_read_image(dst_addr, &page_addr, size, 0, KBOOT_MAGIC_NUM) )
		return ERR_GET_DTE_KBOOT_FAILED;

	aux_sys_flash_curent_pos = page_addr; // save the current pos

	return 0;
}

