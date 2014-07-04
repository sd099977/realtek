#include <project_config.h>
#include <stdio.h>
#include <sysdefs.h>
#include "flashdev_sn.h"
#include "flashdev_sn_reg.h"
#include "md_reg.h"
#include <util.h>


#define PAGE_TMP_ADDR		(0xa0200000 - UBOOT_DDR_OFFSET)
#define PAGE_TMP_ADDR2		(0xa0230000 - UBOOT_DDR_OFFSET)
#define PAGE_TMP_ADDR3		(0xa0240000 - UBOOT_DDR_OFFSET)
#define PAGE_TMP_ADDR4		(0xa0250000 - UBOOT_DDR_OFFSET)

#define SPARE_DMA_ADDR		(0xa0210000 - UBOOT_DDR_OFFSET)
#define BLK_STATE_BASE		(0xa0220000 - UBOOT_DDR_OFFSET)


#define _SPI_NAND_CTRL
#define _USE_MD
#define FEATURE_CHECK
//#define PRINT_LOG
#define ROM_DEBUG
#define LITTLE_ENDIAN
//#define SPI_NAND_PROFILE

#define SFC_DELAY 50
#define STATUS_TIMEOUT 100
#define MD_MAX_WRITE_SIZE 256

#define BLOCK_IND_ADDRESS 0x800
#define TAG_ADDRESS 0x804
#define PAGE_2K_SIZE 0x800

extern UINT8 verify_after_write;

/* if using big endian system, it requires to swap spare's endian */
//#define SPARE_SWAP_ENDIAN

static UINT32 pages_per_block;
static UINT32 blocks_per_flash;

//-----------------------------------------//
static UINT32  fileflash_phys_start ;
static UINT32  fileflash_phys_end ;
static UINT8 *blk_state;			// bootcode block state array
static UINT32 blk_state_len;			// length of bootcode block state array
static UINT32 current_env_start;		// (latest) env param page address
static UINT8 env_version_no;			// (latest) env param version on

static BB_t *bbt;
static UINT32 BBT_LENGTH;
static UINT32 spi_nand_bootcode_area_size;		// NAND bootcode area size
static const spi_n_device_type *ptr_device;

//-----------------------------------------//

// bad block related
static int bbt_exist(void *dev);
static int init_bbt(spi_n_device_type *device);
static int get_remap_block(UINT32 *start_blk);
static int build_bbt(void *dev);
static int load_bbt(void *dev);
static void write_bbt(void *dev);

static UINT32 initial_bad_block_offset(spi_n_device_type *device);

static int set_block_state(UINT32 block_no, UINT8 state);
static int get_block_state(UINT32 block_no, UINT8 *state);


// NAND profile related
static int nand_profile_exist(const void *dev);
static int build_nand_profile(const void *dev, t_nand_profile *profile);
static int write_nand_profile(const void *dev, t_nand_profile *profile);
static unsigned int accumulate_byte_value(const void *buf, unsigned int length);



static void set_spi_n_address(unsigned int addr_cnt, unsigned int addr);
static void clr_spi_n_address();
static void sn_set_feature(unsigned char address, unsigned char data);
static void sn_get_feature(unsigned char address, unsigned char *data);

static int sn_wait_ready();
static void sn_read_id(unsigned int *id);
static int sfc_reset();
static int sn_check_ecc(UINT8 c0_status);

static void sn_read_byte(const UINT32 ca_address, UINT8 *spi_1byte_data);
static void sn_read_word(const UINT32 ca_address, UINT32 *spi_4byte_data);
void sn_write_byte(const UINT32 ca_address, const UINT8 spi_1byte_data);
void sn_write_word(const UINT32 ca_address, const UINT32 spi_4byte_data);
static int sn_write_enable();
static int sn_write_disable();
static void sn_md_read_cache2mem(void *dst, void *src, UINT32 len);
static void sn_md_write_mem2cache(void *dst, void *src, UINT32 len);
static int sn_read_cache_b(const UINT32 block, const UINT32 page, UINT8 *data, const UINT32 length);
static int sn_write_cache_b(const UINT32 block, const UINT32 page, UINT8 *data, const UINT32 length);
static int sn_program_execute(const UINT32 block, const UINT32 page);
static int sfc_read_page_to_cache_b(spi_n_device_type *device, const unsigned int block_addr, const unsigned int page_addr);
static int sfc_read_page_to_cache(spi_n_device_type *device, const unsigned int page_no);
static int sfc_read_phys_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf);
static int sfc_read_phys_page_b(spi_n_device_type *device, UINT32 block_addr, UINT32 page_addr, UINT8 *buf);
static int sfc_read_page_nomap(spi_n_device_type *device, UINT32 page_no, UINT8 *buf);
static int sfc_read_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf);
static int sfc_get_spare(spi_n_device_type *device, UINT32 blk_no, UINT32 *spare, UINT32 offset);
static int sfc_write_phys_page_b(spi_n_device_type *device, UINT32 block_addr, UINT32 page_addr, UINT8 *buf);
static int sfc_write_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf);
static int sfc_write_cache_to_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf);
static int sfc_set_spare(spi_n_device_type *device, UINT32 blk_no, UINT32 spare, UINT32 offset);
static int sfc_erase_phys_block(spi_n_device_type *device, UINT32 block_addr);
static int sfc_erase_phys_block(spi_n_device_type *device, UINT32 block_addr);
static int sfc_erase_block_nomap(spi_n_device_type *device, UINT32 block_addr);
static int sfc_erase_block(spi_n_device_type *device, UINT32 block_addr);
static int sfc_find_blks(spi_n_device_type *device, UINT32 start_block, UINT32 search_depth, UINT32 offset);

static int sfc_read(spi_n_device_type *device, UINT32 start_page, UINT8 *buf, UINT32 size);
static int sfc_write(spi_n_device_type *device, UINT32 start_page, UINT8 *buf, UINT32 size);

//-----------------------------------------//
#ifdef DUMP_SPI_NAND_FLASH
static spi_n_device_type *devicetype;

void SFC_dump_spi_nand_flash(spi_n_device_type *device, UINT32 dst_addr, UINT32 src_page, UINT32 page_len)
{
	//devicetype = device;

	UINT32 i;
	UINT32 block_addr, page_addr;
	UINT32 pageperblock = device->BlockSize/device->PageSize;

	for (i = 0; i< page_len;i++) {

		block_addr = src_page / pageperblock;
		page_addr = src_page % pageperblock;

		if (sfc_read_page_to_cache_b(device, block_addr, page_addr) < 0) {
			/* ecc error & cannot be corrected */
			printf("ecc error & cannot be corrected\n");
			return;
		}

		sn_read_cache_b(block_addr, page_addr, (UINT8 *)dst_addr, device->PageSize+64);
		src_page++;
		dst_addr=dst_addr+device->PageSize+64;

	}
	return;
}

#endif
//-----------------------------------------//
static void set_spi_n_address(unsigned int addr_cnt, unsigned int addr)
{
	REG32(SPI_NAND_0) = (((addr_cnt) & 0x3) << 26) | (0x3 << 24) | (addr & 0xffffff);
	return;
}

static void clr_spi_n_address()
{
	REG32(SPI_NAND_0) = 0;
	return;
}

static void sn_set_feature(unsigned char address, unsigned char data)
{
	unsigned int spi_address;

	// TODO: change to ECO controller

	REG32(SFC_OPCODE) = 0x0000001f;

#ifdef _SPI_NAND_CTRL
	REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
	set_spi_n_address(SPI_ADDR_CNT_1, address);
	spi_address = SPI_BASE_ADDR;
	udelay(SFC_DELAY);
	REG8(spi_address) = data;
#else
	REG32(SFC_CTL) = 0x00000008; /* dataen = 0, adren = 1, dmycnt = 0 */
	spi_address = SPI_BASE_ADDR + (address << 16) + (data << 8);
	udelay(SFC_DELAY);
	REG8(spi_address) = 0x0;
#endif

#ifdef _SPI_NAND_CTRL
	clr_spi_n_address();
#endif

	return;
}

static void sn_get_feature(unsigned char address, unsigned char *data)
{
	unsigned int spi_address;

	// TODO: change to ECO controller

	REG32(SFC_OPCODE) = 0x0000000f;
	REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */

#ifdef _SPI_NAND_CTRL
	set_spi_n_address(SPI_ADDR_CNT_1, address);
	spi_address = SPI_BASE_ADDR;
#else
	spi_address = SPI_BASE_ADDR + (address << 16);
#endif
	udelay(SFC_DELAY);
	*data = REG8(spi_address);

#ifdef _SPI_NAND_CTRL
	clr_spi_n_address();
#endif

	return;
}


static int sn_wait_ready()
{
   UINT32 retry;
   UINT8 spi_1byte_data;

   retry = 0;
   do {
      udelay(SFC_DELAY);
      sn_get_feature(0xc0, &spi_1byte_data);
   } while ((spi_1byte_data & 0x1)&&(++retry < STATUS_TIMEOUT));

   if (retry == STATUS_TIMEOUT) {
      printf("\nsn_wait_ready fail: timeout, status %x\n", spi_1byte_data);
      return -1;
   }
   return 0;
}

static int sn_unlock_flash()
{
   UINT8 spi_1byte_data;

   sn_set_feature(0xa0, 0x00);

   if (sn_wait_ready())
   	return -1;

#ifdef FEATURE_CHECK
   sn_get_feature(0xa0, &spi_1byte_data);
   if (spi_1byte_data&0x38) {
   		printf("\nsn_unlock_flash(): set feature: status 0x%x fail.\n", spi_1byte_data);
      return -1;
   }
#endif
	return 0;
}

static void sn_read_id(unsigned int *id)
{
	unsigned int spi_address;

	// TODO: change to ECO controller

	REG32(SFC_OPCODE) = 0x0000009f;
	REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */

#ifdef _SPI_NAND_CTRL
	set_spi_n_address(SPI_ADDR_CNT_1, 0x00);
	spi_address = SPI_BASE_ADDR;
#else
	spi_address = SPI_BASE_ADDR + (0x00 << 16);
#endif
	udelay(SFC_DELAY);
	*id = REG32(spi_address);


#ifdef _SPI_NAND_CTRL
	clr_spi_n_address();
#endif


#if 0
	prints("\nFlash id:[");
	print_hex(*id);
	prints("]");
#endif
}

static int sfc_reset()
{
	REG32(SFC_OPCODE) = 0x000000ff;
	REG32(SFC_CTL) = 0x00000000; /* dataen = 0 adren = 0, dmycnt = 0 */

	udelay(SFC_DELAY);
	REG8(SPI_BASE_ADDR) = 0x00;

   if (sn_wait_ready()) {
      return -1;
   }

	return 0;
}

static int sn_check_ecc(UINT8 c0_status)
{
   switch ((c0_status & 0x30) >> 4) {
      case 0x3:
         //bit error & corrected (for GD)
         break;
      case 0x2:
         //bit error & NOT corrected
         return -1;
         break;
      case 0x1:
         //bit error & corrected
         break;
      case 0x0:
         //no bit error
         break;
      default:
         //impossible;
         return -1;
   }
   return 0;
}

static void sn_read_byte(const UINT32 ca_address, UINT8 *spi_1byte_data)
{
	UINT32   spi_address;

	REG32(SFC_OPCODE) = 0x00000003;

#ifdef _SPI_NAND_CTRL
	REG32(SFC_CTL) = 0x00000019; /* dataen = 1, adren = 1, dmycnt = 1 */
	set_spi_n_address(SPI_ADDR_CNT_2, ca_address);
	spi_address = SPI_BASE_ADDR;
	udelay(SFC_DELAY);
	*spi_1byte_data = REG8(spi_address);
	clr_spi_n_address();
#else
   REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
   spi_address = SPI_BASE_ADDR + ((ca_address&0x1fff) << 8);
	udelay(SFC_DELAY);
   *spi_1byte_data = REG8(spi_address);
#endif

}

static void sn_read_word(const UINT32 ca_address, UINT32 *spi_4byte_data)
{
   UINT32   spi_address;

   REG32(SFC_OPCODE) = 0x00000003;

#ifdef _SPI_NAND_CTRL
   REG32(SFC_CTL) = 0x00000019; /* dataen = 1, adren = 1, dmycnt = 0 */
	set_spi_n_address(SPI_ADDR_CNT_2, ca_address);
	spi_address = SPI_BASE_ADDR;
	udelay(SFC_DELAY);
   *spi_4byte_data = REG32(spi_address);
	clr_spi_n_address();
#else
   REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
   spi_address = SPI_BASE_ADDR + (ca_address << 8);
	udelay(SFC_DELAY);
   *spi_4byte_data = REG32(spi_address);
#endif

#ifdef LITTLE_ENDIAN
   *spi_4byte_data = SWAPEND32(*spi_4byte_data);
#endif
}

void sn_write_byte(const UINT32 ca_address, const UINT8 spi_1byte_data)
{
	UINT32   spi_address;

	REG32(SFC_OPCODE) = 0x00000084;

#ifdef _SPI_NAND_CTRL
   REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
	set_spi_n_address(SPI_ADDR_CNT_2, ca_address);
	udelay(SFC_DELAY);
   REG8(SPI_BASE_ADDR) = spi_1byte_data;
	clr_spi_n_address();
#else
	REG32(SFC_CTL) = 0x00000008; /* dataen = 0, adren = 1, dmycnt = 0 */
#ifdef LITTLE_ENDIAN
	spi_address = SPI_BASE_ADDR + ((ca_address&0x1fff) << 8) + (spi_1byte_data&0xfc) + ((spi_1byte_data&0x3)^0x3);
#else
	spi_address = SPI_BASE_ADDR + ((ca_address&0x1fff) << 8) + spi_1byte_data;
#endif
	udelay(SFC_DELAY);
	REG8(spi_address) = 0x0;
#endif

	return;
}

void sn_write_word(const UINT32 ca_address, const UINT32 spi_4byte_data)
{
	UINT32   spi_data;

	REG32(SFC_OPCODE) = 0x00000084;

#ifdef LITTLE_ENDIAN
	spi_data = SWAPEND32(spi_4byte_data);
#else
	spi_data = spi_4byte_data;
#endif

#ifdef _SPI_NAND_CTRL
	REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
	set_spi_n_address(SPI_ADDR_CNT_2, ca_address);
	udelay(SFC_DELAY);
	REG32(SPI_BASE_ADDR) = spi_data;
	clr_spi_n_address();
#else
	REG32(SFC_CTL) = 0x00000010; /* dataen = 1, adren = 0, dmycnt = 0 */
	REG32(SPI_BASE_ADDR) = ((ca_address & 0x1fff) << 16) + ((spi_data >> 16) & 0xffff);
	udelay(SFC_DELAY);
	REG32(SPI_BASE_ADDR) = (((ca_address + 2) & 0x1fff) << 16) + (spi_data & 0xffff);
#endif

	return;
}

static int sn_write_enable()
{
	UINT8 	spi_1byte_data;
	UINT32   retry;

	do {
		REG32(SFC_OPCODE) = 0x00000006;
		REG32(SFC_CTL) = 0x00000000; /* dataen = 0, adren = 0, dmycnt = 0 */
		udelay(SFC_DELAY);
		REG8(SPI_BASE_ADDR) = 0x0;;

		sn_get_feature(0xc0, &spi_1byte_data);
	} while (((spi_1byte_data & 0x2) == 0x0) && (++retry < STATUS_TIMEOUT));

	if (retry == STATUS_TIMEOUT) {
		printf("\nsn_write_enable(): timeout set feature: status 0x%x fail.\n", spi_1byte_data);
		return -1;
	}

	return 0;
}

static int sn_write_disable()
{
	UINT8 	spi_1byte_data;
	UINT32   retry;

	do {
		REG32(SFC_OPCODE) = 0x00000004;
		REG32(SFC_CTL) = 0x00000000; /* dataen = 0, adren = 0, dmycnt = 0 */
		udelay(SFC_DELAY);
		REG8(SPI_BASE_ADDR) = 0x0;

		sn_get_feature(0xc0, &spi_1byte_data);
	} while ((spi_1byte_data & 0x2) && (++retry < STATUS_TIMEOUT));

	if (retry == STATUS_TIMEOUT) {
		prints("\nsn_write_enable(): timeout set feature: status 0x");
		print_hex(spi_1byte_data);
		prints(" fail.");
		return -1;
	}

	return 0;
}

static void sn_md_read_cache2mem(void *dst, void *src, UINT32 len)
{
	// flush cache before DMA
	sys_dcache_flush_all();

	REG32(SFC_OPCODE) = 0x00000003;

#ifdef _SPI_NAND_CTRL
	REG32(SFC_CTL) = 0x00000019; /* dataen = 1, adren = 1, dmycnt = 1 */
	set_spi_n_address(SPI_ADDR_CNT_2, 0); // address don't care, use MD address
#else
	REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
#endif
	udelay(SFC_DELAY);

	REG32(MD_FDMA_DDR_SADDR) = (UINT32)PHYS(dst);
	REG32(MD_FDMA_FL_SADDR) = (UINT32)(src - SPI_BASE_ADDR);
	REG32(MD_FDMA_CTRL2) = 0x2c000000 | (len & 0x1ffffff); /*don't swap (bit28:0)*/

	sync();
	REG32(MD_FDMA_CTRL1) = 3;  // go
	while ((REG32(MD_FDMA_CTRL1) & 0x1) != 0);

#ifdef _SPI_NAND_CTRL
	clr_spi_n_address();
#endif

   return;
}

static void sn_md_write_mem2cache(void *dst, void *src, UINT32 len)
{
	sn_write_enable();

	REG32(SFC_OPCODE) = 0x00000084;

#ifdef _SPI_NAND_CTRL
	REG32(SFC_CTL) = 0x00000018; /* dataen = 1, adren = 1, dmycnt = 0 */
	set_spi_n_address(SPI_ADDR_CNT_2, 0); // address don't care, use MD address
	udelay(SFC_DELAY);

	sys_dcache_flush_all();

	REG32(MD_FDMA_DDR_SADDR) = (UINT32)PHYS(src);
	REG32(MD_FDMA_FL_SADDR) = (UINT32)dst;
	REG32(MD_FDMA_CTRL2) = 0x2e000000 | ((len) & 0x1ffffff); /*don't swap (bit28:0)*/

	sync();
	REG32(MD_FDMA_CTRL1) = 3;	// go
	while ((REG32(MD_FDMA_CTRL1) & 0x1) != 0);

	clr_spi_n_address();
#else
   UINT8 *wbuf;
	wbuf = (UINT8 *)PAGE_TMP_ADDR3;

	REG32(SFC_CTL) = 0x00000010; /* dataen = 1, adren = 0, dmycnt = 0 */
	udelay(SFC_DELAY);

	// for spi-nand
	// cmd + add + add + data
	wbuf[0] = ((UINT32)dst >> 8) & 0xff;
	wbuf[1] = (UINT32)dst & 0xff;
	copy_memory(&wbuf[2], src, len);

	// flush cache before DMA
	sys_dcache_flush_all();

	REG32(MD_FDMA_DDR_SADDR) = (UINT32)PHYS(wbuf);
	REG32(MD_FDMA_FL_SADDR) = (UINT32)(SPI_BASE_ADDR - SPI_BASE_ADDR);
	REG32(MD_FDMA_CTRL2) = 0x2e000000 | ((len) & 0x1ffffff); /*don't swap (bit28:0)*/

	sync();
	REG32(MD_FDMA_CTRL1) = 3;	// go
	while ((REG32(MD_FDMA_CTRL1) & 0x1) != 0);

	sn_write_byte((UINT32)dst + len - 2, *((UINT8 *)src + len - 2));
	sn_write_byte((UINT32)dst + len - 1, *((UINT8 *)src + len - 1));
#endif

   return;
}

static int sn_read_cache_b(const UINT32 block, const UINT32 page, UINT8 *data, const UINT32 length)
{
   UINT32 dst, src;

   dst = (UINT32)data;
#ifdef _USE_MD
#ifdef _SPI_NAND_CTRL
	src = SPI_BASE_ADDR + ((block & 0x1) << 12); 	//choose plane for micron
#else
	src = SPI_BASE_ADDR + ((block & 0x1) << (12 + 8)); 	//choose plane for micron
#endif
   sn_md_read_cache2mem((void *)dst, (void *)src, length);
#else
   src = ((block & 0x1) << 12);    //choose plane for micron
	UINT32 i;
	for (i = 0; i < length/4; i++) {
		sn_read_word(src+i*4, (UINT32 *)(dst+i*4));
	}
#endif

   return 0;
}

static int sn_write_cache_b(const UINT32 block, const UINT32 page, UINT8 *data, const UINT32 length)
{
   UINT32 dst, src, i;

   dst = (block & 0x1) << 12;    //choose plane for micron
   src = (UINT32)data;

#ifdef _USE_MD
#ifdef _SPI_NAND_CTRL
	sn_md_write_mem2cache((void *)dst, (void *)src, length);
#else
   for (i = 0; i < length/MD_MAX_WRITE_SIZE; i++) {
      sn_md_write_mem2cache((void *)dst, (void *)src, MD_MAX_WRITE_SIZE);
      dst = dst + MD_MAX_WRITE_SIZE;
      src = src + MD_MAX_WRITE_SIZE;
   }
#endif
#else
	UINT32 *ptr = (UINT32 *)data;
	for (i = 0; i < length/4; i++) {
		dst = ((block & 0x1) << 12) + i*4;
		sn_write_word(dst, ptr[i]);
	}
#endif

   return 0;
}

static int sn_program_execute(const UINT32 block, const UINT32 page)
{
	UINT32 spi_address;
	UINT8 spi_1byte_data;

	sn_write_enable();

	REG32(SFC_OPCODE) = 0x00000010;
	REG32(SFC_CTL) = 0x00000008; /* dataen = 0, adren = 1, dmycnt = 0 */

#ifdef _SPI_NAND_CTRL
	spi_address = ((block & 0x3ff) << 6) + (page & 0x3f);
	set_spi_n_address(SPI_ADDR_CNT_3, spi_address);
	udelay(SFC_DELAY);
	REG8(SPI_BASE_ADDR) = 0x0;
	clr_spi_n_address();
#else
   spi_address = SPI_BASE_ADDR + ((block & 0x3ff) << 6) + (page & 0x3f);    //choose plane for micron
#ifdef LITTLE_ENDIAN
   spi_address = spi_address^0x3;
#endif
	udelay(SFC_DELAY);
	REG8(spi_address) = 0x0;
#endif

	if (sn_wait_ready()) {
		return -1;
	}

	prints("\nsn_program_execute(): block addr 0x");
	print_val(block, 4);
	prints(" page addr 0x");
	print_val(page, 4);

	sn_get_feature(0xc0, &spi_1byte_data);

	if (spi_1byte_data&0x08) {
		prints("\nsn_program_execute(): set feature: status 0x");
		print_hex(spi_1byte_data);
		prints(" fail.");
		return -1;
	}

	return 0;
}

static int sfc_read_page_to_cache_b(spi_n_device_type *device, const unsigned int block_addr, const unsigned int page_addr)
{
	unsigned int spi_address, spare;
	unsigned char data;

	REG32(SFC_OPCODE) = 0x00000013;
	REG32(SFC_CTL) = 0x00000008; /* dataen = 0, adren = 1, dmycnt = 1 */

#ifdef _SPI_NAND_CTRL
	set_spi_n_address(SPI_ADDR_CNT_3, ((block_addr & 0x3ff) << 6) | (page_addr & 0x3f));
	spi_address = SPI_BASE_ADDR;
#else
	spi_address = SPI_BASE_ADDR + ((block_addr & 0x3ff) << 6) + (page_addr & 0x3f);
#ifdef LITTLE_ENDIAN
	spi_address = spi_address^0x3;
#endif
#endif
	udelay(SFC_DELAY);
	REG8(spi_address) = 0x0;

#ifdef _SPI_NAND_CTRL
	clr_spi_n_address();
#endif

   if (sn_wait_ready()) {
      return -1;
   }

	sn_get_feature(0xc0, &data);

	if (sn_check_ecc(data) < 0) {
#ifdef ROM_DEBUG
		printf("\nECC error on block 0x%x, page 0x%x: sn_get_feature=%x\n", block_addr, page_addr, data);
		//prints("\necc error! on block ");
		//print_hex(block_addr);
		//prints(", page ");
		//print_hex(page_addr);
#endif
		return -1;
	}

	//check block indicator
	if (page_addr == 0) {
		sfc_get_spare(device, block_addr, &spare, 0);
		if ((spare & 0xff) != BLOCK_CLEAN) {
#ifdef ROM_DEBUG
			printf("\nbad block spare =%x on block %x, page %x\n", spare, block_addr, page_addr);
			//print_hex(spare);
			//prints(" on block ");
			//print_hex(block_addr);
			//prints(", page ");
			//print_hex(page_addr);
#endif
			return -1;
		}
	}
	return 0;
}

static int sfc_read_page_to_cache(spi_n_device_type *device, const unsigned int page_no)
{
	UINT32 block_addr, page_addr;
	UINT32 pageperblock = device->BlockSize/device->PageSize;

	block_addr = page_no / pageperblock;
	page_addr = page_no % pageperblock;

	return sfc_read_page_to_cache_b(device, block_addr, page_addr);
}

static int sfc_read_phys_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf)
{
	UINT32 block_addr, page_addr;
	UINT32 pageperblock = device->BlockSize/device->PageSize;

	if (sfc_read_page_to_cache(device, page_no) < 0) {
		/* ecc error & cannot be corrected */
		return -1;
	}

	block_addr = page_no / pageperblock;
	page_addr = page_no % pageperblock;

	sn_read_cache_b(block_addr, page_addr, buf, device->PageSize);

#if 0
	print_uart("\nsfc_read_phys_page page_no=");
	print_val(page_no, 8);
	print_uart(" buf=");
	print_val(buf, 8);
	print_uart("\n");
#endif

	return 0;
}

static int sfc_read_phys_page_b(spi_n_device_type *device, UINT32 block_addr, UINT32 page_addr, UINT8 *buf)
{
	if (sfc_read_page_to_cache_b(device, block_addr, page_addr) < 0) {
		/* ecc error & cannot be corrected */
		return -1;
	}

	sn_read_cache_b(block_addr, page_addr, buf, device->PageSize);

#if 0
	print_uart("\nsfc_read_phys_page_b block_addr=");
	print_val(block_addr, 4);
	print_uart(" page_addr=");
	print_val(page_addr, 4);
	print_uart(" buf=");
	print_val(buf, 8);
	print_uart("\n");
#endif

	return 0;
}

static int sfc_read_page_nomap(spi_n_device_type *device, UINT32 page_no, UINT8 *buf)
{
	return sfc_read_phys_page(device, page_no, buf);
}

static int sfc_read_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf)
{
	return sfc_read_phys_page(device, page_no, buf);
}

static int sfc_get_spare(spi_n_device_type *device, UINT32 blk_no, UINT32 *spare, UINT32 offset)
{
	UINT32 ca_address = ((blk_no & 0x1) << 12) + device->PageSize + offset;

	//sn_read_byte(PAGE_2K_SIZE + offset, spare);
	sn_read_word(ca_address, spare);
#ifdef SPARE_SWAP_ENDIAN
	*spare = swap_endian(*spare);
#endif

#if 0
#ifdef ROM_DEBUG
	prints("\n");
	print_hex(device->PageSize + offset);
	prints(" {");
	print_hex(*spare);
	prints("}");
#endif
#endif
	return 0;
}

static int sfc_write_phys_page_b(spi_n_device_type *device, UINT32 block_addr, UINT32 page_addr, UINT8 *buf)
{
	UINT32 res;

	sn_write_cache_b(block_addr, page_addr, buf, device->PageSize);

	res = sn_program_execute(block_addr, page_addr);

#if 1
	UINT32 spare, tmp;
	UINT8 data;

	if (verify_after_write) {
   	sn_get_feature(0xa0, &data);

		//get spare first
		sfc_get_spare(device, block_addr, &spare, 4);

		//read page
		set_memory((UINT8 *)PAGE_TMP_ADDR4, 0xff, device->PageSize);
		sfc_read_phys_page_b(device, block_addr, page_addr, (UINT8 *)PAGE_TMP_ADDR4);

		//get spare
		sfc_get_spare(device, block_addr, &tmp, 4);

		//verify data and spare
		res = compare_memory(buf, (UINT8 *)PAGE_TMP_ADDR4, device->PageSize);
		if ((res != 0) || (spare != tmp)) {
			printf("\nverify page fail! block_addr=%x page_addr=%x buf=%x feature(0xa0)=%x\n", block_addr, page_addr, PAGE_TMP_ADDR4, data);

			if (spare != tmp) {
				printf("\nwrite spare=%x read=%x\n", spare, tmp);
			}

			if (res) {
				hexdump("write buffer", buf, device->PageSize);
				hexdump("read buffer", (char *)PAGE_TMP_ADDR4, device->PageSize);
			}

		}
	}
#endif

#if 0
	print_uart("nsfc_write_phys_page page_no=");
	print_val(page_no, 8);
	print_uart(" ");
	print_val(buf, 8);
	print_uart("\n");
#endif

	if (res == 0) {
		/* show '.' in console */
		prints(".");
		return 0;
	}
	/* show '!' in console */
	prints("!(");
	print_val(block_addr, 4);
	prints(" ");
	print_val(page_addr, 4);
	prints(") ");

	return -1;
}

static int sfc_write_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf)
{
	UINT32 block_addr, page_addr;
	UINT32 pageperblock = device->BlockSize/device->PageSize;

	block_addr = page_no / pageperblock;
	page_addr = page_no % pageperblock;

	return sfc_write_phys_page_b(device, block_addr, page_addr, buf);
}

static int sfc_write_cache_to_page(spi_n_device_type *device, UINT32 page_no, UINT8 *buf)
{
	UINT32 block_addr, page_addr;
	UINT32 pageperblock = device->BlockSize/device->PageSize;

	block_addr = page_no / pageperblock;
	page_addr = page_no % pageperblock;

	return sn_write_cache_b(block_addr, page_addr, buf, device->PageSize);
}

static int sfc_set_spare(spi_n_device_type *device, UINT32 blk_no, UINT32 spare, UINT32 offset)
{
	UINT32 ca_address = ((blk_no & 0x1) << 12) + device->PageSize + offset;

#ifdef SPARE_SWAP_ENDIAN
	spare = swap_endian(spare);
#endif
	sn_write_word(ca_address, spare);

#ifdef SPARE_SWAP_ENDIAN
		spare = swap_endian(spare);
#endif
	if (((spare & 0xff) == BLOCK_BAD) && (offset == 4)) {
		sn_write_byte(device->PageSize, BLOCK_BAD);
	}
	else {
		sn_write_byte(device->PageSize, BLOCK_CLEAN);
	}
	return 0;
}

static int sfc_erase_phys_block(spi_n_device_type *device, UINT32 block_addr)
{
	UINT32	spi_address;
	UINT8 	spi_1byte_data;

	sn_write_enable();

	spi_address = SPI_BASE_ADDR + ((block_addr & 0x3ff) << 6);
#ifdef LITTLE_ENDIAN
	spi_address = spi_address^0x3;
#endif

	REG32(SFC_OPCODE) = 0x000000d8;
	REG32(SFC_CTL) = 0x00000008; /* dataen = 0, adren = 1, dmycnt = 0 */
	udelay(SFC_DELAY);
	REG8(spi_address) = 0x0;

	if (sn_wait_ready()) {
		return -1;
	}

	sn_get_feature(0xc0, &spi_1byte_data);

	if (spi_1byte_data&0x40) {
		//printf("erase fail: status %x\n", spi_1byte_data);
		/* show 'X' in console */
		prints("X(");
		print_val(block_addr,3);
		prints(")");
		return -1;
	}

	/* show '/' in console */
	//printf("/(%x)", block_addr);
	prints("/(");
	print_val(block_addr,3);
	prints(")");
	return 0;
}

static int sfc_erase_block_nomap(spi_n_device_type *device, UINT32 block_addr)
{
	return sfc_erase_phys_block(device, block_addr);
}

static int sfc_erase_block(spi_n_device_type *device, UINT32 block_addr)
{
	return sfc_erase_phys_block(device, block_addr);
}

static int sfc_find_blks(spi_n_device_type *device, UINT32 start_block, UINT32 search_depth, UINT32 offset)
{
	UINT32 blk, limit, page_no;
	UINT32 spare;
	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	INT8 res;

	// validate arguments
	if ((device == NULL) || (start_block >= blockperflash) || (offset >= pageperblock))
		return (-1);

	// determine search limit
	if (search_depth == 0)
		limit = spi_nand_bootcode_area_size / device->BlockSize;	// only bootcode blocks
	else if (search_depth >= blockperflash)
		limit = blockperflash;	// search to end of flash
	else
	{
		limit = start_block + search_depth;

		// cannot search beyond flash (max is last block of flash)
		if (limit >= blockperflash)
			limit = blockperflash;
	}

	for (blk = start_block, page_no = (blk * pageperblock + offset);
		blk < limit ;
		blk++, page_no += pageperblock)
	{
		res = sfc_read_page_to_cache_b(device, blk, 0);

		switch (res)
		{
			//case DATA_ALL_ONE:
			//	set_block_state(blk, BLOCK_CLEAN);
			//	continue;

			case 0:		// read to table success
				sfc_get_spare(device, blk, &spare, 4);
				spare &= 0xff;
				break;

			default:	// read to table has error
				set_block_state(blk, BLOCK_BAD);
				continue;	// next block
		}

		// NOTE: BLOCK_UNDETERMINE is a fake state,
		// all blocks in the flash "SHALL NOT" have this state or it will cause some problem!!
		if (spare == BLOCK_UNDETERMINE)
			continue;	// should not happen

		/*
		// check if block is beyond the range of block state table
		res = get_block_state(blk, &state);
		if (res)
			continue;
		*/

		// update with new magic no. in spare area
		set_block_state(blk, (UINT8)(spare & 0xff));
	}

//	{
//		UINT8 state;
//		for (blk = 0; blk < blk_state_len; blk++)
//		{

//			get_block_state(blk, &state);
//			printf("blk=0x%x, state=0x%x \n", blk, state);
//		}
//	}

	return 0;
}

/************************************************************************
 *
 *                          do_erase_n
 *  Description :
 *  -------------
 *  implement the flash erase
 *  (make sure there's enough blocks for do_write_n function)
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
#define USE_GENERAL_METHOD	(1)
int do_erase_sn(void *dev,               //flash device
               unsigned int* dest,     //start of block NO.
               unsigned int   rem_size) //request data length
{
	UINT32 signature;
	spi_n_device_type *device = (spi_n_device_type *)dev;

	UINT32 req_block_no, total_blocks, first_block;
	UINT32 current_block_no = *dest;
	int res;
	UINT8 state;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	//UINT32 blockperflash = device->size/device->BlockSize;

	// calculate required number of blocks
	req_block_no = rem_size / device->BlockSize;
	if (rem_size % device->BlockSize)
		req_block_no++;

	total_blocks = req_block_no;
	first_block = *dest;

	while (req_block_no != 0)
	{
		// return failed if reach bootcode blocks boundary
		if (current_block_no > (blk_state_len - 1))
			return -1;

		res = get_block_state(current_block_no, &state);
		if (res)
		{
			// block state table has no record (out of range?)
			// try to read first page in block then check data
			// in spare area those load to PP
			res = sfc_read_page_to_cache_b(device, current_block_no, 0);

			// read page failed (restart to find contiguous clean blocks)
			if (res == -1)
			{
				current_block_no++;
				#if !USE_GENERAL_METHOD
					req_block_no = total_blocks;
					first_block = current_block_no;	// re-init start block no
				#endif
				continue;
			}

			sfc_get_spare(device, current_block_no, &signature, 4);
			state = signature & 0xff;
		}

		// block is good
		if (state == BLOCK_CLEAN)
		{
			current_block_no++;
			req_block_no--;
			continue;
		}

		// bad block (restart to find contiguous clean blocks)
		if((state == BLOCK_BAD) || (state == BLOCK_ENVPARAM_MAGICNO))
		{
			sfc_erase_block(device, current_block_no);
			sfc_set_spare(device, current_block_no, BLOCK_BAD, 4);
			sfc_write_page(device, current_block_no * pageperblock, (UINT8 *)PAGE_TMP_ADDR);
			set_block_state(current_block_no, BLOCK_BAD);
			current_block_no++;
			#if !USE_GENERAL_METHOD
				req_block_no = total_blocks;
				first_block = current_block_no;	// re-init start block no
			#endif
			continue;
		}
		else
		{
			// if erase current_block_no fail, mark this block as fail
			if (sfc_erase_block(device, current_block_no) < 0)
			{
				// write 'BAD_BLOCK' signature to spare cell
				// (restart to find contiguous clean blocks)
				sfc_set_spare(device, current_block_no, BLOCK_BAD, 4);
				sfc_write_page(device, current_block_no * pageperblock, (UINT8 *)PAGE_TMP_ADDR);
				set_block_state(current_block_no, BLOCK_BAD);
				current_block_no++;
				#if !USE_GENERAL_METHOD
					req_block_no = total_blocks;
					first_block = current_block_no;	// re-init start block no
				#endif
				continue;
			}
			else
			{
				// block is good after erase
				set_block_state(current_block_no, BLOCK_CLEAN);
				current_block_no++;
				req_block_no--;
			}// end of erase block success
		}
	}// end of while (req_block_no != 0)

	// return start block available to write
	return first_block;

}





/**********************************************************************
** built by hcy for bad block handle
**
***********************************************************************/

static int nf_BB_handle(spi_n_device_type *device, UINT32 current_block_no)
{
	UINT32 page_no;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	//UINT32 blockperflash = device->size/device->BlockSize;

	page_no = current_block_no * pageperblock;

	/* mark the block as BB */
	set_memory((void *)PAGE_TMP_ADDR, 0xff, device->PageSize);
	sfc_set_spare(device, current_block_no, BLOCK_BAD, 4);
	sfc_write_page(device, page_no, (UINT8 *)PAGE_TMP_ADDR);

	return 0;


}
/************************************************************************
 *
 *                          do_erase_map
 *  Description :
 *  -------------
 *  implement the flash erase with remapping feature
 *  (make sure there's enough blocks for do_write_map function)
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_erase_map_sn(void *dev,               //flash device
               unsigned int* dest,     //start of block NO.
               unsigned int   rem_size) //request data length
{
	spi_n_device_type *device = (spi_n_device_type *)dev;

	UINT32 req_block_no, total_blocks, first_block;
	UINT32 current_block_no = *dest;

	// calculate required number of blocks
	req_block_no = rem_size / device->BlockSize;
	if (rem_size % device->BlockSize)
		req_block_no++;

	total_blocks = req_block_no;
	first_block = *dest;

	while (req_block_no != 0)
	{
		// return failed if reach  blocks boundary
		if (current_block_no > (blk_state_len - 1))
			return -1;


		// if erase current_block_no fail, mark this block as fail
		if (sfc_erase_block(device, current_block_no) < 0)
		{
			prints("\ndo_erase_map_sn :sfc_erase_block err , BB handle\n");
			// write 'BAD_BLOCK' signature to spare cell
			nf_BB_handle(device, current_block_no);

			continue;
		}
		else
		{
			current_block_no++;
			req_block_no--;
		}// end of erase block success


	}// end of while (req_block_no != 0)

	// return start block available to write
	return first_block;

}

/************************************************************************
 *
 *                          do_write
 *  Description :
 *  -------------
 *  implement the flash write
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_write_sn(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int signature,
               const unsigned int page_offset)
{
	spi_n_device_type *device = (spi_n_device_type *)dev;
	int data_len = rem_size;
	UINT32 current_page;
	UINT8 * data_ptr = array_ptr;
	int ith;
	UINT32 page_counter = 0;	// ith page of the data
	UINT32 spare;
	UINT32 temp;
	UINT32 fail_counter = 0;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	//UINT32 blockperflash = device->size/device->BlockSize;

	if (page_offset > pageperblock) {
		prints("\n[do_write_sn] invalid page offset: ");
		print_hex(page_offset, 4);
		return -1;
	}

	//hexdump("signature=0x%x \n", signature);//cy test


	/* all need do map  */
	//	return do_write_map(dev, array_ptr, dest, rem_size,signature);

	if (page_offset == 0) {
		//erase blocks we need to save data
		ith = do_erase_sn(dev, dest, rem_size);

		if (ith == -1)
			return -1;	// no more blocks available
	}
	else
		ith = *dest;	// skip erase blocks

	current_page = ((UINT32)ith) * pageperblock + page_offset;

	// write data to nand flash pages
	while (data_len > 0)
	{
		UINT32 current_block_no = current_page / pageperblock;

		// set signature to pp buffer and wait for writing to spare cell
		// (in the spare area first 2B is signature , following 2B are page_counter)
		spare = (signature & 0x0000ffff) | ((page_counter & 0xffff) << 16);
		sfc_set_spare(device, current_block_no, spare, 4);

		if (sfc_write_page( device, current_page, data_ptr) < 0)
		{
			// erase whole block to write signature to spare cell
			sfc_erase_block(device, current_block_no);

			//write 'BAD_BLOCK' signature to spare cell
			sfc_set_spare(device, current_block_no, BLOCK_BAD, 4);
			set_block_state(current_block_no, BLOCK_BAD);

			// perform writing
			set_memory((UINT8 *)PAGE_TMP_ADDR, 0xff, device->PageSize);
			sfc_write_page(device, current_block_no * pageperblock, (UINT8 *)PAGE_TMP_ADDR);

			if (page_offset != 0)
				return -1;	// just return failed (no retry)

			#if 0
				// redo all operation from start
				ith = do_erase_n(dev, dest, rem_size);
				if (ith == -1)
					return -1;	// no more blocks available

				data_len = rem_size;
				current_page = ((UINT32)ith) * pages_per_block;
				data_ptr = array_ptr;
				page_counter = 0;
			#else
				current_block_no++;//Try to write in next block.
				//nf_erase_block(device, current_block_no);
				data_len += ((current_page%pageperblock)*device->PageSize);
				ith = do_erase_sn(dev, &current_block_no, data_len);
				if (ith == -1)
					return -1;	// no more blocks available

				current_block_no = ith;
				data_ptr -= ((current_page%pageperblock)*device->PageSize);
				page_counter -= (current_page % pageperblock);
				current_page = current_block_no*pageperblock;
			#endif
			continue;
		}
		else
		{
			UINT32 current_block_no = current_page / pageperblock;

			if (verify_after_write) {
				int cmp;
				print_uart("\nverify after write\n");

				// clear buffer
				set_memory((UINT8 *)PAGE_TMP_ADDR, 0xff, device->PageSize);
				temp = 0;

				// also clear cache (prevent write data still remain in cache)
				sn_write_cache_b(current_page / pages_per_block, current_page % pages_per_block, (UINT8 *)PAGE_TMP_ADDR, device->PageSize);

				// read page again
				sfc_read_page(device, current_page, (UINT8 *)PAGE_TMP_ADDR);
				sfc_get_spare(device, current_block_no, &temp, 4);

				// verify data is the same
				cmp = compare_memory(data_ptr, (UINT8 *)PAGE_TMP_ADDR, device->PageSize);
				if ((temp != spare) || (cmp != 0)) {
#if 1
					if (cmp != 0)
						hexdump("read back from flash", (UINT8 *)PAGE_TMP_ADDR, device->PageSize);
					if (temp != spare)
						printf("spare: 0x%x (supposed: 0x%x)\n", temp, spare);
#endif
					if (page_offset != 0)
						return -1;	// just return failed (no retry)

					if (fail_counter > 3) {
						print_uart("verify failed\n");
						print_val((UINT32)data_ptr,4);
						print_uart("\n");
						print_val(PAGE_TMP_ADDR,4);
						return -1;
					}

					fail_counter++;
					print_uart("f");
					// redo all operation from start
					ith = do_erase_sn(dev, dest, rem_size);
					if (ith == -1)
						return -1;      // no more blocks available

					data_len = rem_size;
					current_page = ((UINT32)ith) * pageperblock;
					data_ptr = array_ptr;
					page_counter = 0;
					continue;
				}
			}

			set_block_state(current_page / pageperblock, signature);
			data_ptr += device->PageSize;
			data_len -= device->PageSize;
			// increment current_page if not finished
			if (data_len > 0)
				current_page ++;
		}

		page_counter++;
	}
/*
	// adjust first block available for env
	end_blk = current_page / pages_per_block;
	if (end_blk >= fileflash_phys_start )
		fileflash_phys_start = end_blk + 1;
*/
	*dest = ith;
	return current_page;
}
/************************************************************************
 *
 *                          do_write_map
 *  Description :
 *  -------------
 *  implement the flash write with remapping feature
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_write_map_sn(void *dev,
               unsigned char* array_ptr,
               unsigned int* dest,
               unsigned int   rem_size,
               unsigned int signature)
{
	spi_n_device_type *device = (spi_n_device_type *)dev;
	int data_len = rem_size;
	UINT32 current_page;
	UINT8 * data_ptr = array_ptr;
	int ith;
	UINT32 page_counter = 0;	// ith page of the data
	UINT32 spare;
	UINT32 temp;
	UINT32 fail_counter = 0;
	int     i=0;
	UINT32 current_block_no;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	//erase blocks we need to save data
	ith = do_erase_map_sn(dev, dest, rem_size);

	if (ith == -1)
		return -1;	// no more blocks available

	current_page = ((UINT32)ith) * pageperblock;
	current_block_no = current_page / pageperblock;
	printf("current_page=0x%x current_block_no=0x%x \n", current_page, current_block_no);
	// write data to nand flash pages
	while (data_len > 0)
	{

		// set signature to pp buffer and wait for writing to spare cell
		// (in the spare area first 2B is signature , following 2B are page_counter)
		spare = (signature & 0x0000ffff) | ((page_counter & 0xffff) << 16);
		sfc_set_spare(device, (current_page / pageperblock), spare, 4);
		i++;

		if ( sfc_write_page( device, current_page, data_ptr) < 0 /*|| i==2*/)
		{

			printf("test BB handle current_page=0x%x current_block_no=0x%x \n", current_page, current_block_no);
			// erase whole block to write signature to spare cell
			sfc_erase_block(device, current_block_no);

			// write 'BAD_BLOCK' signature to spare cell
			nf_BB_handle(device, current_block_no);

			// redo all operation from start
			ith = do_erase_map(dev, dest, rem_size);
			if (ith == -1)
				return -1;	// no more blocks available

			data_len = rem_size;
			current_page = ((UINT32)ith) * pageperblock;
			data_ptr = array_ptr;
			page_counter = 0;

			continue;
		}
		else
		{
			if (verify_after_write) {
				// perform writing
				set_memory((UINT8 *)PAGE_TMP_ADDR, 0xff, device->PageSize);

				// read page again
				sfc_read_page(device, current_page, (UINT8 *)PAGE_TMP_ADDR);
				sfc_get_spare(device, current_page / pages_per_block, &temp, 4);

				// verify data is the same
				if ((temp != spare) || compare_memory(data_ptr, (UINT8 *)PAGE_TMP_ADDR, device->PageSize)) {
					if (fail_counter > 3) {
						print_uart("verify failed\n");
						print_val((UINT32)data_ptr,4);
						print_uart("\n");
						print_val(PAGE_TMP_ADDR,4);
						return -1;
					}
					/* leave to deciding if need BB_handle



					*/
					fail_counter++;
					print_uart("f");

					// redo all operation from start
					ith = do_erase_map(dev, dest, rem_size);
					if (ith == -1)
						return -1;      // no more blocks available

					data_len = rem_size;
					current_page = ((UINT32)ith) * pageperblock;
					data_ptr = array_ptr;
					page_counter = 0;

					continue;
				}
                        }

			set_block_state(current_page / pageperblock, signature);
			data_ptr += device->PageSize;
			data_len -= device->PageSize;
			// increment current_page if not finished
			if (data_len > 0)
				current_page ++;
		}

		page_counter++;
	}

	*dest = ith;
	return current_page;
}
/************************************************************************
 *
 *                          do_identify_n
 *  Description :
 *  -------------
 *  implement the identyfy flash type
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_identify_sn(void **dev)
{
	UINT32 chipid = 0;
	UINT32 idx;

#ifdef FPGA
	REG32(0xb801a808) = 3;	// FPGA: 25/(3+1)=6.5 MHz

	// turn on KCPU in-order mode
	//sync();
	//REG32(0xb801a018) = 0x80000;
	//sync();
	//REG32(0xb801a018) = 0xc0000;
	//sync();
#endif

	sfc_reset();

	blocks_per_flash  = 0;

	// reset chip id
	chipid = 0;

	/***************************************
	 * get maker ID and device ID from flash
	 ***************************************/

	//get maker id and device id from DDR
	sn_read_id(&chipid);
	printf("\nFlash id [0x%x]\n", chipid);
	//print_uart("\nFlash id [0x");
	//print_val(chipid,8);
	//print_uart("]\n");

	/***************************************
	 * compare maker id and device ID with
	 * IDs in nand flash table
	 ***************************************/
	for (idx = 0; idx < DEV_SIZE_SPI_N; idx++)
	{
		/* find the match flash brand */

		if (chipid != spi_n_device[idx].id)
			continue;

		*dev = (void *)&spi_n_device[idx];
		ptr_device = &spi_n_device[idx];

		// calculate block number per flash and page size per block
		pages_per_block  = spi_n_device[idx].BlockSize / spi_n_device[idx].PageSize;
		blocks_per_flash = spi_n_device[idx].size / spi_n_device[idx].BlockSize;
		break;
	}

   if (idx == DEV_SIZE_SPI_N) { // not found
		prints("\ncannot find any match ID!!!");
		*dev = 0;
		return -1;
	}

	// set bootcode area size according to different block size
	if (((spi_n_device_type *)(*dev))->BlockSize <= 0x40000)		// < 256KB
		spi_nand_bootcode_area_size = NAND_BOOTCODE_AREA_12MB;
	else if (((spi_n_device_type *)(*dev))->BlockSize <= 0x100000)	// 512KB/1MB
		spi_nand_bootcode_area_size = NAND_BOOTCODE_AREA_30MB;
	else if (((spi_n_device_type *)(*dev))->BlockSize == 0x200000)	// 2MB
		spi_nand_bootcode_area_size = NAND_BOOTCODE_AREA_50MB;
	else	// undefined block size??
		return -1;

	printf("SPI-NAND flash info:\n\tFlash ID: 0x%x\n", (((spi_n_device_type *)(*dev))->id));
	printf("\tPart Num: %s\n", (((spi_n_device_type *)(*dev))->string));
	printf("\tPage size:  0x%08x\n", (((spi_n_device_type *)(*dev))->PageSize));
	printf("\tBlock size: 0x%08x\n", (((spi_n_device_type *)(*dev))->BlockSize));
	printf("\tFlash size: 0x%08x\n", (((spi_n_device_type *)(*dev))->size));

	if (sn_unlock_flash())
		return -1;

	test_oob((spi_n_device_type *)(*dev));
	return 0;
}

/************************************************************************
 *
 *                          do_init_n
 *  Description :
 *  -------------
 *  implement the following NAND flash init job:
 *	1. setup block state table for bootcode area
 *	2. erase old bootcode blocks
 *	3. determine block range for env param
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_init_sn(void *dev)
{
	spi_n_device_type *device = (spi_n_device_type *)dev;
	UINT32 i, temp, temp2, idx, spare;
	INT32 res;
	UINT8 state;
	//UINT32 len;
	//t_nand_profile *profile;
	if (device == NULL)
		return (-1);

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	// init block state table
	//blk_state_len = nand_bootcode_area_size / device->BlockSize;	// only bootcode blocks
	blk_state_len = blockperflash;
	//for (i = 0; i < blk_state_len; i++)
	for (i = 0; i < blockperflash; i++)
		REG8(BLK_STATE_BASE + i) = BLOCK_UNDETERMINE;
	blk_state = (UINT8 *)BLK_STATE_BASE;


	/* fill all blocks state table */
	// search with non-exist magic no (this guarantees we can visit to the end of the bootcode blocks)
	res = sfc_find_blks(device, 0, blk_state_len, 0);
	//sfc_get_spare(device, &spare, 4);
	spare = 0;

	if((spare & 0xff) == 0x23) {
		/* erase blocks */ //cy test I will modified
		for (i = 0; i < blk_state_len; i++)
		{

			if (sfc_erase_block_nomap(device, i)) {
				prints("\nsfc_erase_block_nomap err , BB handle");
				set_block_state(i, BLOCK_BAD);
			}
			else
			{
				// check read ok after erase
				res = sfc_read_page_nomap(device, i * pageperblock, (UINT8 *)PAGE_TMP_ADDR);
				if (res == 0)
					set_block_state(i,  BLOCK_CLEAN);
				else {
					set_block_state(i, BLOCK_BAD);
				}
			}
		}
		//check_build_bbt(device);
	}
	else {
		/* after we create the block state table , we check if bbt exists or not */
		//check_build_bbt(device);

		/* erase old bootcode related blocks */ //cy test I will modified
		for (i = 0; i < /*blk_state_len*/ spi_nand_bootcode_area_size / device->BlockSize; i++)
		{
			get_block_state(i, &state);
			switch (state)
			{
				// block is ready to write
				case BLOCK_CLEAN:
				// reserve env block & user data only
				case BLOCK_ENVPARAM_MAGICNO:
				// reserve user programed data
				case BLOCK_OTHER_DATA:
				// skip bad block table (they are in block 0 & 1, should not happen here)
				case BLOCK_BBT:
				// dont erase factory setting data
				case BLOCK_FACTORY_SETTING:
					break;

				// erase old bootcode

				case BLOCK_HWSETTING:


				case BLOCK_BOOTCODE:
				case BLOCK_DATA:
				// erase again to make sure it's really a bad block
				case BLOCK_BAD:
				// erase unknown type of block
				default:
					if (sfc_erase_block(device, i)) {
						prints("\nsfc_erase_block err , BB handle");
						// write 'BAD_BLOCK' signature to spare cell
						nf_BB_handle(device, i);

						set_block_state(i, BLOCK_BAD);
					}
					else
					{
						// check read ok after erase
						// res = sfc_read_page(device, i * pageperblock, (UINT8 *)PAGE_TMP_ADDR);

						res = sfc_read_page_to_cache_b(device, i, 0);
						if (res == 0)
							set_block_state(i,  BLOCK_CLEAN);
						else {

							prints("\nsfc_read_page err , BB handle");
							// write 'BAD_BLOCK' signature to spare cell
							nf_BB_handle(device, i);


							set_block_state(i, BLOCK_BAD);
						}

					}
			}
		}
	}

	// reset current env start page address
	env_version_no = 0;
	current_env_start = temp = temp2 = fileflash_phys_end = fileflash_phys_start = -1;
	for (idx = 3, i = 0; idx < spi_nand_bootcode_area_size / device->BlockSize; idx++)
	{
		if (get_block_state(idx, &state))
			continue;	// block out of range

		// find first env block
		if ((fileflash_phys_start == -1)
			&& (state == BLOCK_ENVPARAM_MAGICNO))
		{
		    fileflash_phys_start = idx;
		}

		// find last env block
		if (state == BLOCK_ENVPARAM_MAGICNO)
		{
		    fileflash_phys_end = idx;
		}

		// find first unused block
		if ((temp == -1) && (state == BLOCK_CLEAN))
		{
		    temp = idx;
		}

		// find last unused block
		if (blk_state[idx] == BLOCK_CLEAN)
		{
		    temp2 = idx;
		}
	}

	// locate first block available for env
	if (temp < fileflash_phys_start)
		fileflash_phys_start = temp;

	// extend block available for env (maximum is last block of bootcode area)
	if (fileflash_phys_end == -1)
	{
		if (temp2 != -1)
			fileflash_phys_end = temp2;
		else
			print_uart("no space for env\n");
	}
	else
	{
		if ((temp2 != -1) && (fileflash_phys_end < temp2))
			fileflash_phys_end = temp2;
	}

	return 0;
}
/************************************************************************
 *
 *                          write_bbt
 *  Description :
 *  -------------
 *  write BBT
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void write_bbt(void *dev)
{
	UINT32 idx, len, bbt_size;
	int res;
	spi_n_device_type *device = (spi_n_device_type *)dev;
	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	// prepare memory space for bad block table (aligned to page boundary)
	bbt_size = sizeof(BB_t) * BBT_LENGTH;
	len = bbt_size / device->PageSize;
	if (bbt_size & (device->PageSize - 1))
		len++;

	if (len >= pageperblock)
	{
		print_uart("bbt exceed one block\n");
		return;
	}

	len *= device->PageSize;
	set_memory((UINT8 *)PAGE_TMP_ADDR, 0xff, len);
	copy_memory((UINT8 *)PAGE_TMP_ADDR, bbt, bbt_size);

	// write bad block table into block 0 & 1
	for (idx = 1; idx < 3; idx++)
	{
		sfc_set_spare(device, idx, BLOCK_BBT, 4);
		res = sfc_erase_block(device, idx);
		if (res == 0)
		{
		 	if (sfc_write(device, idx * pageperblock, (UINT8 *)PAGE_TMP_ADDR, len))
				print_uart("write bbt failed\n");
			else
				set_block_state(idx, BLOCK_BBT);
		}
		else
		{
			print_uart("erase bbt failed\n");
			set_block_state(idx, BLOCK_BAD);
		}
	}
}
/************************************************************************
 *
 *                          check_build_bbt
 *  Description :
 *  -------------
 *  check & build BBT
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void check_build_bbt_sn(void *dev)
{
	//INT32 res;
	//UINT32 idx;
	//UINT32 ini_bb_offset;
	spi_n_device_type *device = (spi_n_device_type *)dev;
	//UINT32 spare;
	//UINT8 status;
	if (device == NULL)
		return (-1);

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	if (bbt_exist(dev) == 0 )
	{
		print_uart("build bbt...");

		// reserve 5% blocks
		BBT_LENGTH = blockperflash * RBA_PERCENTAGE / 100;
#if 0
		// scan untill end of flash
		//nf_find_blk(device, nand_bootcode_area_size / device->BlockSize, 0xffffffff, initial_bad_block_offset(device));
		ini_bb_offset = initial_bad_block_offset(device);
		for (res = 0, idx = nand_bootcode_area_size / device->BlockSize; idx < blocks_per_flash; idx++)
		{


			// read initial block status
			// (1st byte in the physical spare area, not controller's spare area)
			// e.g. 2KB page -> 1st spare byte at column address 2048
			//      4KB page -> 1st spare byte at column address 4096
			res = nf_read_single_byte(device, device->PageSize, (idx * pages_per_block + ini_bb_offset), &status);

			if (status != BLOCK_CLEAN)
				status = (nf_erase_block(device, idx) == 0 ? BLOCK_CLEAN : BLOCK_BAD);

			// save block state
			set_block_state(idx, status);
		}

#endif
		if (init_bbt(dev))
		{
			print_uart("init_bbt failed\n");
			return;
		}

		build_bbt(dev);

		write_bbt(dev);

		print_uart("build bbt...finished");
	}
	else {
		print_uart("load bbt...");
		load_bbt(dev);
	}

}
/************************************************************************
 *
 *                          do_exit_n
 *  Description :
 *  -------------
 *  implement the exit flash writing operation
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
void do_exit_sn(void *dev)
{
#ifdef SPI_NAND_PROFILE
	spi_n_device_type *device = (spi_n_device_type *)dev;
	t_nand_profile *profile;
	int res;

	//if (nand_profile_exist(device) == 0) {
		prints("build profile...");
		profile = (t_nand_profile *)simple_malloc(sizeof(t_nand_profile));
		if (profile == NULL)
			return;

		set_memory(profile, 0, sizeof(t_nand_profile));
		build_nand_profile(device, profile);
		hexdump("[do_exit_sn]", profile, sizeof(t_nand_profile));
		res = write_nand_profile(device, profile);
		if (res == -1)
			return;
		else
			prints("done\n");
	//}
#endif
	test_oob(dev);
}

/************************************************************************
 *
 *                          FLASH_NAND_search_latest_env
 *  Description :
 *  -------------
 *  Search latest env param data
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'device',   IN,    variable of type, spi_n_device_type.
 *  'start',    IN,    start block no
 *  'end',   	IN,    end block no
 *  'latest',  	INOUT, latest env param start page address
 *
 *
 *  Return values :
 *  ---------------
 *
 * 'OK' = 0x00:                         System FLASH OK
 *
 ************************************************************************/
static int nf_search_latest_env(spi_n_device_type *device, UINT32 start, UINT32 end, UINT32 *latest)
{
	UINT32 page_start, page_end, increment;
	UINT32 i, spare;
	UINT8 res, version, lowest, highest;
	UINT8 wrap_version;	// version no (wrap case)
	UINT32 wrap_latest;	// latest env address (wrap case)
	UINT32 pageperblock;
	UINT32 blockperflash;

	if (device == NULL)
		return (-1);

	pageperblock = device->BlockSize/device->PageSize;
	blockperflash = device->size/device->BlockSize;

	// env param size is 64KB
	increment = NAND_ENV_SIZE / device->PageSize;

	// start == -1 means search from the first block (skip block 0 because it's used by YAFFS)
	page_start = (start == -1 ? 1 : start) * pageperblock;

	// end == -1 means search to the end of the bootcode blocks
	page_end = (end == -1 ? blk_state_len : end) * pageperblock;

	// search to the last page of the block
	page_end += pageperblock;

	version = highest = wrap_latest = wrap_version = 0;
	lowest = 255;
	for (i = page_start; i < page_end; i += increment)
	{
		res = sfc_read_page(device, i, (UINT8 *)PAGE_TMP_ADDR);

		// skip empty page
		if (res == DATA_ALL_ONE)
			continue;

		sfc_get_spare(device, i / pageperblock, &spare, 4);

		// check 1st byte of spare area identifies env param
		if ((spare & 0xff) != BLOCK_ENVPARAM_MAGICNO)
			continue;

		// get 2nd byte of the spare area
		res = (spare >> 8) & 0xff;
		if (res >= version)
		{
			version = res;
			*latest = i;
		}

		// update lowest & highest version no
		if (res < lowest)
			lowest = res;
		if (res > highest)
			highest = res;

		// update possible wraped latest no
		// (number of env in flash is expected to be smaller than 128)
		/*
			why 128?
			if BlockSize=256K, env=64K
			=> one block contains at most 4 versions
			=> thus we support at most 128/4=32 blocks for storing env

			=> if BlockSize=128K, we can support up to 64 blocks !!
		*/
		if ((res >= wrap_version) && (res < 128))
		{
			wrap_version = res;
			wrap_latest = i;
		}
	}

	// check wrap condition (when version 0 and 255 both exists)
	if ((lowest == 0) && (highest == 255))
	{
		// version no 255 is not latest, use warped ones instead
		version = wrap_version;
		*latest = wrap_latest;
	}

	// update env param version no
	env_version_no = version;

	return 0;
}


/************************************************************************
 *
 *                          nf_search_next_env
 *  Description :
 *  -------------
 *  Search next writable address for env param data
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'device',	IN,	variable of type, spi_n_device_type.
 *  'page_no',  INOUT,	page address of next writable address
 *
 *
 *  Return values :
 *  ---------------
 *
 *  '-1': device is NULL or cannot found writable address
 *
 ************************************************************************/
static int nf_search_next_env(spi_n_device_type *device, UINT32 *page_no)
{
	INT8 res;
	UINT32 current_env_end, page_cnt;
	UINT32 current_blk, next_blk;
	UINT8 state;
	UINT32 pageperblock;
	UINT32 blockperflash;

	if ((device == NULL) || (page_no == NULL))
		return (-1);

	pageperblock = device->BlockSize/device->PageSize;
	blockperflash = device->size/device->BlockSize;

	// check if latest env exist
	if (current_env_start == -1)
	{
		// no env found in flash
		//return (-1);

		// no current env, start from fileflash_phys_start
		for (next_blk = fileflash_phys_start; next_blk <= fileflash_phys_end; next_blk++)
		{
			if (get_block_state(next_blk, &state))
				continue;

			switch (state)
			{
				case BLOCK_CLEAN:
					*page_no =  next_blk * pageperblock;
					return (0);

				case BLOCK_ENVPARAM_MAGICNO:
					res = sfc_erase_block(device, next_blk);
					if (res == 0)
					{
						*page_no = next_blk * pageperblock;
						return (0);
					}
					else	// erase failed, mark as bad block
						set_block_state(next_blk, BLOCK_BAD);
					break;

				default:
					break;
			}
		}

		// cannot find any available block
		return (-1);
	}

	/* find next writable 64KB area */
	page_cnt = NAND_ENV_SIZE / device->PageSize;
	current_env_end = current_env_start + page_cnt - 1;
	current_blk = current_env_end / pageperblock;
	//printf("current_env_end:%x, current_blk:%x\n", current_env_end, current_blk);

	// check if current env block has space
	if ( current_blk == ((current_env_end + page_cnt) / pageperblock) )
	{
		// current env & next env in the same block
		*page_no = current_env_start + page_cnt;
		return (0);
	}
	else
	{
		// current env & next env not in the same block
		next_blk = (current_blk >= fileflash_phys_end ? fileflash_phys_start : current_blk + 1);
		while (next_blk != current_blk)
		{
			// try to find next available block
			res = get_block_state(next_blk, &state);
			if (res == 0)
			{
				switch (blk_state[next_blk])
				{
					// skip bad block
					case BLOCK_BAD:
					// skip bootcode related block
					case BLOCK_HWSETTING:
					case BLOCK_BOOTCODE:
					case BLOCK_DATA:
						break;

					case BLOCK_CLEAN:
						*page_no = next_blk * pageperblock;
						return (0);

					case BLOCK_ENVPARAM_MAGICNO:
					//case BLOCK_OTHER_DATA:
						res = sfc_erase_block(device, next_blk);
						if (res == 0)
						{
							*page_no = next_blk * pageperblock;
							return (0);
						}
						else	// erase failed, mark as bad block
							set_block_state(next_blk, BLOCK_BAD);
						break;

					default:
						break;
				}
			}
			// end of bootcode blocks, wrap to fileflsh start
			if (next_blk >= fileflash_phys_end)
				next_blk = fileflash_phys_start;
			else
				next_blk++;
		}
		return (-1);
	}

}


/************************************************************************
 *
 *                          sfc_read
 *  Description :
 *  -------------
 *  read SPI-NAND flash
 *
 *  Parameters :
 *  ------------
 *  'device',       	IN,    variable of type, spi_n_device_type.
 *  'start_page',  	IN,    start page address to read
 *  'buf', 	        IN,    pointer for buffer of data to read
 *  'size',       	IN,    number of bytes to read
 *
 *  Return values :
 *  ---------------
 *  '-1': device is NULL or read beyond flash or read failed
 *
 ************************************************************************/
static int sfc_read(spi_n_device_type *device, UINT32 start_page, UINT8 *buf, UINT32 size)
{
	UINT32 stop_page;
	INT32 res;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	// validate arguments (size should be aligned to page size boundary)
	if ( (device == NULL) || (buf == NULL)
		|| (start_page > pageperblock * blockperflash)
		|| (size & (device->PageSize - 1))
		|| (size == 0) )
		return (-1);

	// do not allow read past end of flash
	stop_page = start_page + size / device->PageSize;
	if (stop_page > pageperblock * blockperflash)
		return (-1);

	while (start_page < stop_page)
	{
		res = sfc_read_page(device, start_page, buf);
		switch (res)
		{
			//case DATA_ALL_ONE:	// page is clean
			case 0:
				break;

			default:
				return (-1);
                                break;
		}

		buf += device->PageSize;
		start_page++;
	}
	return 0;
}


/************************************************************************
 *
 *                          sfc_write
 *  Description :
 *  -------------
 *  write data into SPI-NAND flash
 *
 *  Parameters :
 *  ------------
 *  'device',       	IN,    variable of type, spi_n_device_type.
 *  'start_page',  	IN,    start page address to write
 *  'buf', 	        IN,    pointer for buffer of data to be written
 *  'size',       	IN,    number of bytes to write
 *
 *  Return values :
 *  ---------------
 *  '-1': device is NULL or write beyond flash or write failed
 *
 ************************************************************************/
static int sfc_write(spi_n_device_type *device, UINT32 start_page, UINT8 *buf, UINT32 size)
{
	UINT32 stop_page;
	INT32 res;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	// validate arguments (size should be aligned to page size boundary)
	if ( (device == NULL) || (buf == NULL)
		|| (start_page > pageperblock * blockperflash)
		|| (size & (device->PageSize - 1))
		|| (size == 0) )
		return (-1);

	// do not allow write past end of flash
	stop_page = start_page + size / device->PageSize;
	if (stop_page > pageperblock * blockperflash)
		return (-1);

	while (start_page < stop_page)
	{
		res = sfc_write_page(device, start_page, buf);
		if (res)
			return (-1);
		buf += device->PageSize;
		start_page++;
	}
	return (0);
}
/************************************************************************
 *
 *                          set_block_state
 *  Description :
 *  -------------
 *  get block state
 *
 *  Parameters :
 *  ------------
 *  'block_no',	IN,	block no.
 *  'state',	IN,	specified block state
 *
 *  Return values :
 *  ---------------
 *  '-1': block_no is out of range
 *
 ************************************************************************/
static int set_block_state(UINT32 block_no, UINT8 state)
{
/*
	if (block_no >= blk_state_len)
		return (-1);

	blk_state[block_no] = state;
	return (0);
*/
	blk_state[block_no] = state;
	return (block_no < blk_state_len ? 0 : -1);
}


/************************************************************************
 *
 *                          get_block_state
 *  Description :
 *  -------------
 *  get block state
 *
 *  Parameters :
 *  ------------
 *  'block_no',	IN,	block no.
 *  'state',	INOUT,	specified block state
 *
 *  Return values :
 *  ---------------
 *  '-1': block_no is out of range
 *
 ************************************************************************/
static int get_block_state(UINT32 block_no, UINT8 *state)
{
/*
	if (block_no >= blk_state_len)
		return (-1);

	*state = blk_state[block_no];
	return 0;
*/
	*state = blk_state[block_no];
	return (block_no < blk_state_len ? 0 : -1);
}


/************************************************************************
 *
 *                          get_env_n
 *  Description :
 *  -------------
 *  get env param from flash to DRAM
 *
 *  Parameters :
 *  ------------
 *  'device',	IN,	variable of type, spi_n_device_type.
 *  'buf',	IN,	env data pointer
 *
 *  Return values :
 *  ---------------
 *  '-1': means device or buf is NULL, or no env found, or copy env to DRAM failed
 *
 ************************************************************************/
int get_env_sn(void *dev, UINT8 *buf)
{
	INT32 res;
	spi_n_device_type *device = (spi_n_device_type *)dev;

	if ((device == NULL) || (buf == NULL))
		return (-1);

        // search latest env data from fileflash_phys_start
       	nf_search_latest_env(device, fileflash_phys_start, fileflash_phys_end, &current_env_start);
	if (current_env_start == -1)
        	return (-1);	// no env found

        // copy latest env data to DDR
        res = sfc_read(device, current_env_start, buf, NAND_ENV_SIZE);
       	return (res);
}


/************************************************************************
 *
 *                          save_env_n
 *  Description :
 *  -------------
 *  save env param from DRAM to flash
 *
 *  Parameters :
 *  ------------
 *  'device',	IN,	variable of type, spi_n_device_type.
 *  'buf',	IN,	env data pointer
 *
 *  Return values :
 *  ---------------
 *  '-1': means device or buf is NULL, or no env found, or find next writable page address failed
 *
 ************************************************************************/
int save_env_sn(void *dev, UINT8 *buf)
{
	spi_n_device_type *device = (spi_n_device_type *)dev;
	UINT32 start_page, spare;
	UINT8 block_state;
	int rc;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	if ((device == NULL) || (buf == NULL))
		return (-1);

	// skip save env param if latest one is not overwritten by bootcode blocks
	block_state = BLOCK_UNDETERMINE;
	if (current_env_start == -1) {
		prints("\ncurrent_env_start == -1");
	}

	rc = get_block_state(current_env_start / pageperblock, &block_state);
	if (rc != 0)
		return rc;

	if (block_state == BLOCK_ENVPARAM_MAGICNO)
		return 0;
	else
		current_env_start = -1;		// current env page does not exist

	// find next writable page address
	rc = nf_search_next_env(dev, &start_page);
	if (rc != 0)
		return rc;

	// if this is the first time to write env param, start with version 0
	spare = (env_version_no == 0 ? 0 : env_version_no + 1);
	spare = (spare << 8) | BLOCK_ENVPARAM_MAGICNO;
	sfc_set_spare(device, (start_page / pages_per_block), spare, 4);
	rc = sfc_write(device, start_page, buf, NAND_ENV_SIZE);
//	printf("start_page:%x, env_version_no: %x\n", start_page, (current_env_start == -1 ? 0 : env_version_no + 1));
	if (rc == 0)
	{
		// write env param success
		current_env_start = start_page;	// update env param page address
		env_version_no++;		// increment env param version no

		// update block state array
		if (set_block_state(start_page / pageperblock, BLOCK_ENVPARAM_MAGICNO))
			return (-1);
	}

	return rc;

}

static int bbt_exist(void *dev)
{
	INT32 res;
	UINT8 state = 0;
	spi_n_device_type *device = (spi_n_device_type *)dev;

	// first check block 1
	get_block_state(1, &state);
	switch (state)
	{
		case BLOCK_CLEAN:	// block 1 is empty
			return (0);

		case BLOCK_BBT:		// block 2 has bad block table
			return (1);

		case BLOCK_BAD:
		default:
			res = sfc_erase_block(device, 1);
			if (res == 0)
				return (0);
			else
				print_uart("block 1 failed\n");
			break;
	}

	// block 1 failed, check block 2 instead
	get_block_state(2, &state);
	switch (state)
	{
		case BLOCK_CLEAN:	// block 2 is empty
			return (0);

		case BLOCK_BBT:		// block 2 has bad block table
			return (1);

		case BLOCK_BAD:
		default:
			res = sfc_erase_block(device, 2);
			if (res == 0)
				return (0);
			else
				print_uart("block 2 failed\n");
			break;
	}

	return (-1);
}

static int init_bbt(spi_n_device_type *device)
{
	UINT32 i, remap_idx;
	UINT32 bbt_limit;
	UINT8 cs;
	UINT32 phys_offset;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	// specify bad block table space
	bbt = (BB_t *)(BLK_STATE_BASE + blockperflash);

	// reset bad block table with initial value
	for (i = 0 ; i < BBT_LENGTH; i++)
	{
		bbt[i].BB_die = BB_DIE_INIT;
		bbt[i].bad_block = BB_INIT;
		bbt[i].RB_die = RB_DIE_INIT;
		bbt[i].remap_block = RB_INIT;
	}

	// fill the remap block field
	remap_idx = blockperflash - 1;
	bbt_limit = remap_idx - BBT_LENGTH;
	for (i = 0; i < BBT_LENGTH; i++)
	{
		if (get_remap_block(&remap_idx)) {
			printf("get_remap_block err \n");
			return (-1);		// cannot find remap block anymore
		}

		// remapping block no. is limited to the last "BBT_LENGTH" blocks of flash
		if (remap_idx < bbt_limit)
			break;

		// calculate physical block offset and chip select
		phys_offset = remap_idx;
#if 0
		if (map_phys_block(device, &cs, &phys_offset)) {
			printf("map_phys_block \n");
			return (-1);
		}
#endif
		bbt[i].RB_die = cs;
		bbt[i].remap_block = phys_offset;
		remap_idx--;
	}

	return 0;
}

static int get_remap_block(UINT32 *start_blk)
{
	UINT8 state;
	UINT32 ith;

	if (start_blk == NULL)
		return (-1);

	// cannot remap beyond flash
	if (*start_blk >= blocks_per_flash) {

		return (-1);
	}

	// search backward , >=2 bbt blocks , I think
	for (ith = *start_blk; ith >= 2 ; ith--)
	{
		get_block_state(ith, &state);

		// found replaceable block
		if (state == BLOCK_CLEAN)
		{
			*start_blk = ith;
			return (0);
		}
	}

	return (-1);
}

static int build_bbt(void *dev)
{
	//int res;
	UINT32 i, bbt_i;
	UINT32 phys_offset;
	UINT8 state, cs;
	spi_n_device_type *device = (spi_n_device_type *)dev;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	// check for bad block
	for (i = spi_nand_bootcode_area_size / device->BlockSize, bbt_i = 0;
		(i < blockperflash) && (bbt_i < BBT_LENGTH); // stop when bad block table is full
		i++)
	{
		get_block_state(i, &state);
		if (state == BLOCK_BAD)
		{
			// check remapping block is valid
			if (bbt[bbt_i].remap_block == RB_INIT)
				break;			// reach the end of valid table entry

			// calculate physical block offset and chip select
			phys_offset = i;
#if 0
			if (map_phys_block(device, &cs, &phys_offset))
				return (-1);
#endif
			// register into bad block table
			bbt[bbt_i].BB_die = cs;
			bbt[bbt_i].bad_block = phys_offset;
			bbt_i++;
		}
	}

	return (0);
}

static int load_bbt(void *dev)
{
	UINT8 state;
	spi_n_device_type *device = (spi_n_device_type *)dev;
	UINT32 i, bbt_size;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	for (i = 1; i < 3; i++)
	{
		get_block_state(i, &state);
		if (state == BLOCK_BBT)
			break;
	}

	// bad block table not found (something wrong with building bad block table)
	// or cannot get bad block table (cause read ECC failed)
	if (i == 3)
	{
		BBT_LENGTH = 0;
		bbt = NULL;
		return (-1);
	}
	// specify bad block table space
	bbt = (BB_t *)(BLK_STATE_BASE + blockperflash);

	BBT_LENGTH = blockperflash * RBA_PERCENTAGE / 100;
	bbt_size = sizeof(BB_t) * BBT_LENGTH;

	// read bad block table to DRAM
	if (sfc_read( device, i * pageperblock, (UINT8 *)bbt, ((bbt_size / device->PageSize) + 1) * device->PageSize ))
	{
		return (-1);
	}


	for (i = 0 ; i<BBT_LENGTH; i++)
	{

		printf("BB_die=0x%x ", bbt[i].BB_die);
		printf("bad_block=0x%x ", bbt[i].bad_block);
		printf("RB_die=0x%x ", bbt[i].RB_die);
		printf("remap_block=0x%x \n", bbt[i].remap_block);

	}
	return (0);



}
static UINT32 initial_bad_block_offset(spi_n_device_type *device)
{
	UINT32 pageperblock = device->BlockSize/device->PageSize;
	//UINT32 blockperflash = device->size/device->BlockSize;

	// initial bad block mark is in first page of the block
	if (device->initial_bb_pos == INITIAL_BB_POS_FIRST)
		return 0;
	// initial bad block mark is in last page of the block
	else if (device->initial_bb_pos == INITIAL_BB_POS_LAST)
		return (pageperblock - 1);
	// should not happen
	else
		return -1;
}
/************************************************************************
 *
 *                          remapped_bbt
 *  Description :
 *  -------------
 *  remap bad block
 *
 *
 *  Parameters :
 *  ------------
 *
 *  'chip_sel',  	INOUT,    chip select value
 *  'block_no',		INOUT,    bad/remap block no.
 *
 *
 *  Return values :
 *  ---------------
 *
 *
 *
 ************************************************************************/
static void remapped_bbt(UINT8 *chip_sel, UINT32 *block_no)
{
	UINT32 i;
	UINT8 cs;
	UINT32 blk;

	// no remapping info (remain original chip_select & block_no)
	if (bbt == NULL) {
		printf("bbt null !\n");
		return;
	}

	cs = *chip_sel;
	blk = *block_no;
	for (i = 0; i < BBT_LENGTH; i++)
	{
#if 0
		printf("cs=0x%x, blk=0x%x \n", cs, blk);
		printf("i=0x%x, BB_die=0x%x ", i, bbt[i].BB_die);
		printf("bad_block=0x%x ", bbt[i].bad_block);
		printf("RB_die=0x%x ", bbt[i].RB_die);
		printf("remap_block=0x%x \n", bbt[i].remap_block);
#endif
		// check if bad block entry is valid
		if (bbt[i].BB_die == BB_DIE_INIT) {

			break;
		}

		// update remapping block if found (may have recursive mapping)
		if ((bbt[i].BB_die == cs) && (bbt[i].bad_block == blk))
		{
			cs = bbt[i].RB_die;
			blk = bbt[i].remap_block;
			printf(" 0x%x remap to (%x, 0x%x)\n",bbt[i].bad_block,   cs, blk);
			continue;
		}
	}
	// return final remapping result
	*chip_sel = cs;
	*block_no = blk;

	return;
}

/************************************************************************
 *
 *                          do_read_n
 *  Description :
 *  -------------
 *  implement the flash read
 *
 *  Parameters :
 *  ------------
 *
 *  Return values :
 *  ---------------
 *
 ************************************************************************/
int do_read_sn(void *dev,
               unsigned int*  start_blk,	// start of block NO.
               unsigned char* dest,		// dest memory address
               unsigned int   rem_size,		// request data length
               unsigned int   signature)
{
	spi_n_device_type *device = (spi_n_device_type *)dev;
	UINT32 i, page_len, tmp;
	UINT8 state;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	// search block state table
	if ((signature) && (*start_blk < blk_state_len))
	{
		for (i = *start_blk; i < blk_state_len; i++)
		{
			tmp = 0;
			get_block_state(i, &state);
			if (state == BLOCK_BAD) {
				INT8 res;

				res = sfc_read_page_to_cache_b(device, i, 0);
				if (!res)
				{
					sfc_get_spare(device, i, &tmp, 4);
					state = tmp && 0xff;
					//printf("new block state=0x%x \n",state);
				}
			}
			if (state == signature)
			{
				*start_blk = i;
				break;
			}
		}

		if (i == blk_state_len)
			return -1;		// not found
	}

	// align data length to page boundary
	page_len = rem_size / device->PageSize;
	if (rem_size % device->PageSize)
		page_len++;

	return sfc_read(device, (*start_blk * pageperblock), dest,
					(page_len * device->PageSize));
}

static int nand_profile_exist(const void *dev)
{
	UINT8 state = 0;
	int res;
	unsigned int checksum;
	t_nand_profile *profile;
	spi_n_device_type *device = (spi_n_device_type *)dev;

	// first check block state
	get_block_state(0, &state);
	if (state != BLOCK_OTHER_DATA) {
		printf("[%x] profile not exist\n", state);
		return 0;
	}

	// then try to read profile
	res = sfc_read_page(device, 0, (UINT8 *)PAGE_TMP_ADDR);
	if (res == -1) {
		printf("read profile error\n");
		return 0;
	}

	// check profile identifier
	profile = (t_nand_profile *)PAGE_TMP_ADDR;
	res = compare_memory(profile->identifier, NAND_PROFILE_IDENTIFIER,
		strlen(NAND_PROFILE_IDENTIFIER));
	if (res) {
		char *ptr;

		printf("wrong profile identifier:\n\t");
		for (res = 0; res < sizeof(profile->identifier); res++)
			printf("%2x ", profile->identifier[res]);
		printf("\n\t");
		ptr = NAND_PROFILE_IDENTIFIER;
		for (res = 0; res < strlen(NAND_PROFILE_IDENTIFIER); res++)
			printf("%2x ", ptr[res]);
		return 0;
	}

	checksum = accumulate_byte_value(profile, 128);
	if (checksum != *((unsigned int *)profile->checksum)) {
		printf("profile checksum not match (%x <> %x)\n",
			checksum, *((unsigned int *)profile->checksum));
		return 0;
	}

	return 1;
}

static int build_nand_profile(const void *dev, t_nand_profile *profile)
{
	unsigned int tmp, checksum;
	spi_n_device_type *device = (spi_n_device_type *)dev;

	UINT32 pageperblock = device->BlockSize/device->PageSize;
	UINT32 blockperflash = device->size/device->BlockSize;

	if ((dev == NULL) || (profile == NULL)) {
		return -1;
	}

	// build NAND profile
	copy_memory(profile->identifier, NAND_PROFILE_IDENTIFIER, sizeof(NAND_PROFILE_IDENTIFIER));
	profile->revision = 0x2;

	for (tmp = 0; tmp < 4; tmp++)
		profile->manufacturer_id[tmp] = (device->id >> (tmp * 8)) & 0xff;
#if 0
	if (device->read_id_len > 4) {
		profile->manufacturer_id[tmp] = device->id5;
		tmp++;

		if (device->read_id_len > 5)
			profile->manufacturer_id[tmp] = device->id6;
	}
#endif

	if (strlen(device->string) < (sizeof(profile->flash_name) - 1))
		tmp = strlen(device->string);
	else
		tmp = sizeof(profile->flash_name) - 1;
	copy_memory(profile->flash_name, (char *)(device->string), tmp);

	profile->number_of_bbt = 2;
	profile->bbt_start_block = 0x1;
	profile->bbt_end_block = 0x2;
	profile->number_of_rsv_block = blockperflash * RBA_PERCENTAGE / 100;
	profile->rsv_start_block = blockperflash - profile->number_of_rsv_block;
	profile->rsv_end_block = blockperflash - 1;
	profile->data_per_page = device->PageSize;

#if 0
	switch (device->ecc_bit) {
		case ECC_6BIT:
			tmp = 16 * (device->PageSize / 512);
			break;
		case ECC_12BIT:
			tmp = 26 * (device->PageSize / 512);
			break;
		case ECC_24BIT:
			tmp = 46 * (device->PageSize / 1024);
			break;
		default:	// unknown type
			return -1;
	}
#endif
	profile->oob_per_page = tmp;
	profile->page_per_block = pageperblock;
	profile->block_per_die = blockperflash;
	//profile->ecc_bit = device->ecc_bit;
	//profile->param_t1 = device->t1;
	//profile->param_t2 = device->t2;
	//profile->param_t3 = device->t3;
	//profile->address_mode = device->addr_mode_rw;

	checksum = accumulate_byte_value(profile, 128);
	//modify by angus, magellan doesn't endian invert
	//for (tmp = 0; tmp < 4; tmp++)
		//profile->checksum[tmp] = (checksum >> (tmp * 8)) & 0xff;
	*(unsigned int *)profile->checksum = checksum;

	return 0;
}

static int write_nand_profile(const void *dev, t_nand_profile *profile)
{
	UINT8 state = 0;
	spi_n_device_type *device = (spi_n_device_type *)dev;

	if ((dev == NULL) || (profile == NULL) )
		return -1;

	if (sizeof(t_nand_profile) > device->PageSize) {
		prints("\nNAND profile exceed one page");
		return -2;
	}

	copy_memory((UINT8 *)PAGE_TMP_ADDR, profile, sizeof(t_nand_profile));
	set_memory((UINT8 *) (PAGE_TMP_ADDR + sizeof(t_nand_profile)), 0xff, device->PageSize - sizeof(t_nand_profile));

#if 0
	get_block_state(0, &state);
	if (state != BLOCK_CLEAN) {
		// erase block 0
		if (sfc_erase_block(device, 0)) {
			prints("\nerase block 0 error");
			return -3;
		}
	}
#else
	//force erase
	//sfc_read_page(device, 0, (UINT8 *)PAGE_TMP_ADDR2);
	//hexdump("before erase, read check", (UINT8 *)PAGE_TMP_ADDR2, sizeof(t_nand_profile));
	if (sfc_erase_block(device, 0)) {
		prints("\nerase block 0 error");
		return -3;
	}
	//sfc_read_page(device, 0, (UINT8 *)PAGE_TMP_ADDR2);
	//hexdump("after erase, read check", (UINT8 *)PAGE_TMP_ADDR2, sizeof(t_nand_profile));
#endif

	//sn_read_cache_b(0, 0, (UINT8 *)PAGE_TMP_ADDR2, 2112);
	//hexdump("before write, read cache", (UINT8 *)PAGE_TMP_ADDR2, 2112);

	// write profile into page 0
	sfc_set_spare(device, 0, BLOCK_OTHER_DATA, 4);

	if (sfc_write(device, 0, (UINT8 *)PAGE_TMP_ADDR, device->PageSize)) {
		print_uart("\nwrite NAND profile failed");
		set_block_state(0, BLOCK_BAD);
		return -4;
	}
	else {
		set_block_state(0, BLOCK_OTHER_DATA);
		//hexdump("after write", (UINT8 *)PAGE_TMP_ADDR, sizeof(t_nand_profile));
		//sfc_read_page(device, 0, (UINT8 *)PAGE_TMP_ADDR2);
		//hexdump("read check", (UINT8 *)PAGE_TMP_ADDR2, sizeof(t_nand_profile));
	}
	//sn_read_cache_b(0, 0, (UINT8 *)PAGE_TMP_ADDR2, 2112);
	//hexdump("after write, read cache", (UINT8 *)PAGE_TMP_ADDR2, 2112);

	return 0;
}

static unsigned int accumulate_byte_value(const void *buf, unsigned int length)
{
	unsigned int i, res;
	unsigned char *ptr = (unsigned char *)buf;

	if ((buf == NULL) || (length == 0))
		return 0;

	for (i = res = 0; i < length; i++)
		res += ptr[i];

	return res;
}

void test_oob(void *dev)
{
#ifdef FPGA
	int res;
	unsigned int blk, spare;

	printf("%s()\n",__FUNCTION__);

	for(blk = 0; blk <=30; blk++){
	res = sfc_read_page_to_cache_b(dev, blk, 0);

	//printf("%s()[%d]: block %d, res %d\n",__FUNCTION__, __LINE__, blk, res);
	if(res==0){
		sfc_get_spare(dev, blk, &spare, 4);
		spare &= 0xff;
		printf("block = %d-----block_state = 0x%x\n", blk, spare);
	}
		else {
			printf("read block = %d error\n", blk);

	}
	}
#endif
}
