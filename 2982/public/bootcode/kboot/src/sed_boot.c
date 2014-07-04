#include "sysdefs.h"
#include "string.h"
#include "sed_common.h"
#include "sed_boot.h"
#include "lzma_tools.h"
#include "mcp.h"
//surport nand flash driver
#include <sys_param_nand.h>
#include <sed_nand.h>


long *kcpu_argv = (long *)(KCPU_CMDLINE_ADDR | MIPS_KSEG0BASE);
char *kcpu_cmdline = (char *)((KCPU_CMDLINE_ADDR | MIPS_KSEG0BASE) + sizeof(long)*2);
uint kcpu_entry_addr = 0;

uint NAND_fw_desc_table_saddr = SYS_PARAM_FW_TABLE_START;		// start address of fw table in nand-layout
uint NAND_fw_desc_table_start = 0;		// start address of valid fw desc table in nand

BOOT_FLASH_T boot_flash_type = BOOT_FLASH_TYPE;
uint b_fw_desc_table_vaild = 0;

/* AES raw key for test only */
unsigned int default_aes_key[4] = { 0x2dc2df39, 0x420321d0, 0xcef1fe23, 0x74029d95 };

/* RSA raw key for test only */
const unsigned char __attribute__((aligned(4))) rsa_key_2048_little[256] = {
    0xAF, 0xE4, 0x39, 0xEC, 0xDD, 0xE5, 0x16, 0x00, 0x72, 0xBB, 0x65, 0x84, 0xDD, 0xA5, 0x4F, 0xBD,
    0xDF, 0xE3, 0x2E, 0xE3, 0x17, 0x5C, 0xDB, 0x00, 0xAC, 0x52, 0xFE, 0xD2, 0xC3, 0x71, 0x2A, 0xEC,
    0x2B, 0x45, 0x77, 0x1D, 0x48, 0x7F, 0x4C, 0x30, 0xC7, 0x34, 0x2C, 0x7C, 0x8F, 0x95, 0xE5, 0x01,
    0xD8, 0x73, 0x94, 0x1F, 0x62, 0xE6, 0x10, 0x27, 0x98, 0x7A, 0xF8, 0xAC, 0x5A, 0x92, 0x9B, 0x9F,
    0x6E, 0xB6, 0x19, 0x17, 0x71, 0x19, 0x3D, 0x0C, 0x03, 0x63, 0xF4, 0x18, 0xA4, 0xC6, 0xBF, 0xFC,
    0x40, 0x94, 0xFF, 0x12, 0x3F, 0x88, 0xC0, 0x8E, 0x82, 0xC3, 0x81, 0x54, 0xFA, 0x11, 0xBA, 0x3D,
    0x74, 0x2B, 0xF6, 0x9E, 0x46, 0x1D, 0xEF, 0xFF, 0xD8, 0x05, 0x43, 0x89, 0x76, 0x84, 0xED, 0x76,
    0xF3, 0x60, 0x90, 0xAD, 0xFA, 0xCC, 0xC2, 0x38, 0x88, 0xFF, 0xC0, 0x62, 0x0A, 0xEC, 0x79, 0x15,
    0x48, 0x00, 0x5E, 0x67, 0xA4, 0xE9, 0x6B, 0x48, 0xD9, 0x44, 0xDE, 0x0C, 0xE8, 0x0E, 0xCF, 0x56,
    0x1B, 0xC9, 0x18, 0x26, 0x11, 0xE3, 0x24, 0x8A, 0x9C, 0x50, 0x2F, 0x64, 0x99, 0x8A, 0xD8, 0x48,
    0x25, 0xD4, 0x9D, 0x62, 0xBE, 0x95, 0xAF, 0xA8, 0x0E, 0x5A, 0x30, 0x9D, 0x64, 0xE2, 0xEE, 0x6E,
    0x66, 0xF0, 0xD2, 0x25, 0x39, 0x38, 0x14, 0xDB, 0xD4, 0x03, 0x6D, 0xA8, 0x0F, 0xCB, 0x80, 0xFA,
    0x63, 0x22, 0xF7, 0xDE, 0xBF, 0x4D, 0x94, 0x83, 0x81, 0x3A, 0xC5, 0x2E, 0xD3, 0x93, 0xC5, 0xA8,
    0x9C, 0xB0, 0x74, 0x93, 0xC8, 0x65, 0xFD, 0x11, 0x65, 0x71, 0x5E, 0x2A, 0xB7, 0xB0, 0x48, 0xF1,
    0x02, 0x43, 0x05, 0x41, 0xA8, 0xA9, 0x64, 0x7A, 0xEC, 0xB7, 0x81, 0xAB, 0x89, 0x5F, 0xD3, 0xDA,
    0xC3, 0xB8, 0xB8, 0x0D, 0xA1, 0xDB, 0x74, 0x3F, 0xEB, 0x83, 0x3F, 0xAF, 0x38, 0x54, 0x97, 0xB9,
};

extern void get_flash_shared_semaphore(void);
extern void release_flash_shared_semaphore(void);

uint get_mem_layout_when_read_image(MEM_LAYOUT_WHEN_READ_IMAGE_T *mem_layout)
{
	if (mem_layout->image_target_addr == 0)
	{
		sed_printf("[ERROR] mem_layout->image_target_addr = 0x%08x\n", mem_layout->image_target_addr);

		return 1;
	}

	if (mem_layout->bIsEncrypted)
	{
		mem_layout->flash_to_ram_addr = mem_layout->encrpyted_addr = (ENCRYPTED_FW_IMAGE_ADDR | MIPS_KSEG0BASE);

		if (mem_layout->bIsCompressed)
		{
			mem_layout->decrypted_addr = mem_layout->compressed_addr = (COMPRESSED_FW_IMAGE_ADDR | MIPS_KSEG0BASE);
			mem_layout->decompressed_addr = mem_layout->image_target_addr;
		}
		else
		{
			mem_layout->decrypted_addr = mem_layout->image_target_addr;
		}
	}
	else
	{
		if (mem_layout->bIsCompressed)
		{
			mem_layout->flash_to_ram_addr = mem_layout->compressed_addr = (COMPRESSED_FW_IMAGE_ADDR | MIPS_KSEG0BASE);
			mem_layout->decompressed_addr = mem_layout->image_target_addr;
		}
		else
		{
			mem_layout->flash_to_ram_addr = mem_layout->image_target_addr;
		}
	}

	return 0;
}

uint get_checksum(unchar *p, uint len)
{
	uint checksum = 0;
	uint i;

	for(i = 0; i < len; i++) {
		checksum += *(p+i);
	}
	return checksum;
}

int get_secure_boot_type(void)
{

#if defined(CONFIG_SYS_RTK_SECURE_BOOT)
	return RTK_SECURE_BOOT;
#else
	return NONE_SECURE_BOOT;
#endif
}

int decrypt_image(unsigned char *src_addr, unsigned char *dst_addr, unsigned int length, unsigned int *key)
{
	int i;
	uint sblock_len;
	unchar *sblock_dst, *sblock_src;
	int ret = 0;

	// get short block size
	sblock_len = length & 0xf;

#if 1
	sed_printf("AES_CBC_decrypt:\n");
	sed_printf("    src_addr: 0x%x\n", src_addr);
	sed_printf("    dst_addr: 0x%x\n", dst_addr);
	sed_printf("     length : 0x%x\n", length);
#endif

	ret = AES_CBC_decrypt(src_addr, length - sblock_len, dst_addr, key);

	if (ret) {
		sed_printf("%s %d fail\n", __FUNCTION__, __LINE__);
		return -1;
	}

	// handle short block (< 16B)
	if (sblock_len) {
		// take the last 16B of raw image as input to XOR with short block data to generate final result
		sblock_src = (unchar *)dst_addr + (length - sblock_len) - 16;
		sblock_dst = (unchar *)dst_addr + (length - sblock_len);

#if 1
		sed_printf("AES_CBC_decrypt:(short block)\n");
		sed_printf("    sblock_src: 0x%x\n", sblock_src);
		sed_printf("    sblock_dst: 0x%x\n", sblock_dst);
		sed_printf("    sblock_len: 0x%x\n", sblock_len);
#endif

		for (i = 0; i < sblock_len; i++)
			sblock_dst[i] ^= sblock_src[i];
	}

	return 0;
}

int Verify_SHA256_hash( unsigned char * src_addr, unsigned int length, unsigned char * ref_sha256, unsigned int do_recovery )
{
	char *p_rsa_key = (char *)NULL;
	char *p_hash_result = (char *)NULL;

	p_rsa_key = (char *)rsa_key_2048_little;
	p_hash_result = (char *)mcp_hash_result;

	if (do_recovery)
	{
		return verify_image_signature((char *)src_addr,
				length,
				(char *)ref_sha256,
				p_rsa_key,
				p_hash_result);
	}
	else
	{
		return check_image_hash((char *)src_addr,
				length,
				(char *)ref_sha256,
				p_hash_result);
	}
}

int kboot_read_rescue_from_eMMC(void)
{
	return 0;
}

int kboot_read_rescue_from_NAND(void)
{
#define RESCUE_LINUX_IN_NAND_IS_COMPRESSED 0 // temp use this define
#define RESCUE_LINUX_SCAN_DEPTH  0xf
#define RESCUE_LINUX_BLOCK_TAG  0x80

	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
//	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from;
//	unsigned int retlen;

	unsigned int secure_mode;
	unsigned int rescue_blk_addr = 0;
	int ret = 0;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int rescue_truncated_size;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	rescue_linux_info_t rescue_linux_hdr;
	unsigned int rescue_linux_hdr_size;
	uint imageSize = 0;
	SizeT decompressedSize = 0;

	// for encrypted rescue linux
	secure_mode = get_secure_boot_type();

	switch( secure_mode ) {
		case NONE_SECURE_BOOT:					// normal mode
			rescue_truncated_size = SHA256_SIZE;
			break;
		case RTK_SECURE_BOOT:			  // RTK
			rescue_truncated_size = RSA_SIGNATURE_LENGTH;
			//force some setting
			Kh_key_ptr = default_aes_key;
			break;
		default:
			sed_printf("[ERR] %s: unknown secure mode\n", __FUNCTION__);
			return 1;
	}

	/* get memory layout before copy kernel image */
	mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
	mem_layout.bIsCompressed = RESCUE_LINUX_IN_NAND_IS_COMPRESSED;
	mem_layout.image_target_addr = (K_RESCUE_LINUX_ENTRY | MIPS_KSEG0BASE);

	if (mem_layout.bIsCompressed == 0)
	{
		// real data start from the end of the header
		mem_layout.image_target_addr -= sizeof(rescue_linux_info_t);
	}

	get_mem_layout_when_read_image(&mem_layout);

	get_flash_shared_semaphore();
	rescue_blk_addr = nand->scan_block_tag(nand, NAND_RESCURE_LOGO_BLK_ADDR, RESCUE_LINUX_SCAN_DEPTH, 0,RESCUE_LINUX_BLOCK_TAG);
	release_flash_shared_semaphore();
	if(rescue_blk_addr == 0){
		sed_printf("[ERR] %s: Scan block-tag failed!!!\n", __FUNCTION__);
		return 1;
	}else{
		sed_printf("[OK] %s:Scan block-tag ok!!\n", __FUNCTION__);
	}
	rescue_linux_hdr_size = sizeof(rescue_linux_info_t);

	from = rescue_blk_addr* (nand->erasesize);	//must define NAND_fw_desc_table_start
	get_flash_shared_semaphore();
	ret = nand->rescue_image_read(nand, (unsigned char *)mem_layout.flash_to_ram_addr, from, rescue_linux_hdr_size, 0, RESCUE_LINUX_BLOCK_TAG);
	release_flash_shared_semaphore();
	if(ret == 0){
		/* Read success */
		sed_printf("[OK] %s:Read rescue header ok!!\n", __FUNCTION__);
	}else{
		/* Read error */
		sed_printf("[ERR] %s:Read rescue header error!!\n", __FUNCTION__);
		return 1;
	}

   /* if secure mode, do decrypt header first */
   if( secure_mode == RTK_SECURE_BOOT ) {

	  sed_printf("decrypt header size %d...\n", ((rescue_linux_hdr_size+(0x10-1))&~(0x10-1)));

	  if (decrypt_image((unchar *)mem_layout.flash_to_ram_addr,
			(unchar *)mem_layout.decrypted_addr,
			((rescue_linux_hdr_size+(0x10-1))&~(0x10-1)),
			Kh_key_ptr))
	  {
		 sed_printf("decrypt header error!\n");
		 return 1;
	  }
	  memcpy(&rescue_linux_hdr, (void *)mem_layout.decrypted_addr, rescue_linux_hdr_size);
	  rescue_linux_hdr.dwImageSize += RSA_2048_KEY_LENGTH;

   }
   else
   {
	  memcpy(&rescue_linux_hdr, (void *)mem_layout.flash_to_ram_addr, rescue_linux_hdr_size);
   }

	if (rescue_linux_hdr.dwMagicNumber == RESCUE_LINUX_HEADER_MAGICNO) {
		imageSize = rescue_linux_hdr.dwImageSize;

		//compressed data start from the end of the header
		mem_layout.compressed_addr += rescue_linux_hdr_size;
	}
	else {
		sed_printf("[WARN] rescue linux header error.\n");
		return 1;
	}

	if( imageSize == 0 ) {
		sed_printf("[ERR] %s:Rescue image size error!!\n", __FUNCTION__);
		return 1;
	}

	sed_printf("#############################\n");
	sed_printf("# Enter Rescue Linux:\n");
	sed_printf("#  secure_mode = %d\n", secure_mode);
	sed_printf("#  compressed  = %d\n", mem_layout.bIsCompressed);
	sed_printf("#  block_no    = 0x%08x\n", rescue_blk_addr);
	sed_printf("#  size_bytes  = 0x%08x\n", imageSize);
	sed_printf("#  target_addr = 0x%08x\n", mem_layout.image_target_addr);
	sed_printf("#############################\n");

	from = rescue_blk_addr* (nand->erasesize);	//must define NAND_fw_desc_table_start
	/* copy rescue linux from flash */
	get_flash_shared_semaphore();
	ret = nand->rescue_image_read(nand, (unsigned char *)mem_layout.flash_to_ram_addr, from, imageSize, 0, RESCUE_LINUX_BLOCK_TAG);
	release_flash_shared_semaphore();
	if(ret == 0){
		/* Read success */
		sed_printf("[OK] %s:Read rescue linux ok!!\n", __FUNCTION__);
	}
	else{
		/* Read error */
		sed_printf("[ERR] %s:Read rescue linux error!!\n", __FUNCTION__);
		return 1;
	}

	/* if secure mode, do AES CBC decrypt */
	if( secure_mode == RTK_SECURE_BOOT ) {

		sed_printf("to decrypt ...\n");

		if (decrypt_image((unchar *)mem_layout.encrpyted_addr,
			(unchar *)mem_layout.decrypted_addr,
			imageSize,
			Kh_key_ptr))
		{
			sed_printf("decrypt image error!\n");
			return 1;
		}

		sed_printf("decrypt rescue successful.\n");

		reverse_signature( (unsigned char *)(mem_layout.decrypted_addr + imageSize - rescue_truncated_size) );

		ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
								  imageSize - rescue_truncated_size - SHA256_SIZE,
								  (unsigned char *)(mem_layout.decrypted_addr + imageSize - rescue_truncated_size), 1 );

		if( ret )
			rtk_hexdump("the first 32-byte decrypted rescue data", (unsigned char *)mem_layout.decrypted_addr, 32 );

	}
	else
	{
		ret = Verify_SHA256_hash( (unsigned char *)mem_layout.flash_to_ram_addr,
								  imageSize - rescue_truncated_size,
								  (unsigned char *)(mem_layout.flash_to_ram_addr + imageSize - rescue_truncated_size), 0 );

		if( ret )
			rtk_hexdump("the first 32-byte rescue data", (unsigned char *)mem_layout.flash_to_ram_addr, 32 );

	}

	if( ret ) {
		sed_printf("[ERR] %s: hash value not match\n", __FUNCTION__ );
		return 1;
	}


	/* if lzma rescue, decompress rescue image to target_addr */
	if (mem_layout.bIsCompressed)
	{
		sed_printf("to decompress ...\n");

		if (lzmaBuffToBuffDecompress((unchar*)mem_layout.decompressed_addr, &decompressedSize, (unchar*)mem_layout.compressed_addr, imageSize) != 0)
		{
			sed_printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);
			return 1;
		}

		sed_printf("decompress successful.\n");
	}

	sed_printf("%s() done.\n", __FUNCTION__);

	return 0;
}


int kboot_read_rescue_from_SPI(void)
{
	return 0;
}

int kboot_read_fw_table_from_eMMC(void)
{
	return 0;
}

int kboot_read_fw_table_from_NAND(fw_desc_table_v1_t *fw_desc_table_v1)
{
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
//	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from;
	unsigned int retlen;
	char ssu_retry = 0;

	uint fw_desc_table_base;
	uint checksum;

#ifdef CONFIG_SAFE_UPGRADE
	sed_printf("SSU on.\n");
return_ssu_boot_flow:
#else
	sed_printf("SSU off.\n");
#endif

	if (ssu_retry == 0) {
		NAND_fw_desc_table_start = NAND_fw_desc_table_saddr;
		sed_printf("read main fwtab @ 0x%p\n", NAND_fw_desc_table_start);
	}
	else {
		NAND_fw_desc_table_start = NAND_fw_desc_table_saddr+nand->erasesize ;
		sed_printf("read backup fwtab @ 0x%p\n", NAND_fw_desc_table_start);
	}

	fw_desc_table_base = (KCPU_FIRMWARE_TABLE_ADDR | MIPS_KSEG0BASE);

	from = NAND_fw_desc_table_start;

	/* copy Firmware Description Table Header from flash */
	get_flash_shared_semaphore();
	nand->read(nand, from, sizeof(fw_desc_table_v1_t), (size_t *)&retlen, (u_char *)fw_desc_table_base);
	release_flash_shared_semaphore();
	if (retlen != sizeof(fw_desc_table_v1_t))
	{
		/* Read error */
		sed_printf("[ERR] %s:Read fw_desc_table_v1_t error!!\n", __FUNCTION__);

#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif

		return 1;
	}
	else
	{
		/* Read success */
		sed_printf("[OK] %s:Read fw_desc_table_v1_t  ok!!\n", __FUNCTION__);
		memcpy(fw_desc_table_v1, (void*)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}

	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1->signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1->signature)) != 0)
	{
		sed_printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1->signature);
#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif
		return 1;
	}

#if 0
	fw_desc_table_v1->checksum = BE32_TO_CPU(fw_desc_table_v1->checksum);
	fw_desc_table_v1->paddings = BE32_TO_CPU(fw_desc_table_v1->paddings);
	fw_desc_table_v1->part_list_len = BE32_TO_CPU(fw_desc_table_v1->part_list_len);
	fw_desc_table_v1->fw_list_len = BE32_TO_CPU(fw_desc_table_v1->fw_list_len);
#endif

#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(fw_desc_table_v1);
#endif

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	from = NAND_fw_desc_table_start;
	get_flash_shared_semaphore();
	nand->read(nand, from, fw_desc_table_v1->paddings, (size_t *)&retlen, (u_char *)fw_desc_table_base);
	release_flash_shared_semaphore();
	if (retlen != fw_desc_table_v1->paddings)
	{
		/* Read error */
		sed_printf("[ERR] %s:Read all fw tables error!!\n", __FUNCTION__);

#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif

		return 1;
	}
	else
	{
		/* Read success */
		sed_printf("[OK] %s:Read all fw tables ok!!\n", __FUNCTION__);
	}

	/* Check checksum */
	checksum = get_checksum((unchar*)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1->part_list_len +
			fw_desc_table_v1->fw_list_len);

	if (fw_desc_table_v1->checksum != checksum)
	{
		sed_printf("[ERR] %s:Checksum not match(0x%x != 0x%x)\n", __FUNCTION__,
			fw_desc_table_v1->checksum, checksum);

#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif

		return 1;
	}

	b_fw_desc_table_vaild = 1; /* set 1: fw desc table in ram is valid */

#ifdef CONFIG_SAFE_UPGRADE
	if (ssu_retry == 1) {
		// write backupfwdesc to main fwdesc
		struct erase_info *instr;
		u_char* p_data;
		uint n;
		unsigned long int to;
		instr = (struct erase_info *)malloc(sizeof(struct erase_info));
		if(instr == NULL){

			sed_printf("[ERR] %s: allocate erase_info failed!!!\n", __FUNCTION__);
			return RTK_PLAT_ERR_PARSE_FW_DESC;

		}
		memset(instr, 0x00, sizeof(struct erase_info));
		instr->mtd = nand;
		instr->addr = NAND_fw_desc_table_saddr;
		instr->len = nand->erasesize ;
		int erase_ret = nand->erase(nand, instr);

		if (erase_ret != 0) {
			sed_printf("\n[ERR] %s: MTD Erase failure: %d\n",__FUNCTION__,erase_ret);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}
		else{
			free(instr);
		}
		to = NAND_fw_desc_table_saddr;
		uint data_len = fw_desc_table_v1->paddings;

		uint page_align_size =	nand->oobblock*( ( data_len + nand->oobblock -1) / nand->oobblock);

		p_data = (u_char*)malloc( page_align_size);
		if (p_data == NULL) {
			sed_printf("[ERR] %s: allocate fwdesc merged buffer failed!!!\n", __FUNCTION__);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}
		memset(p_data, 0xff, page_align_size);
		//memcpy(p_data, fw_desc_table_v1, sizeof(fw_desc_table_v1_t));
		memcpy(p_data, (void*)fw_desc_table_base , fw_desc_table_v1->paddings);
		n = nand->write(nand, to, page_align_size, &retlen, (u_char *)p_data);
		if(retlen == data_len){
			/* Write success */
			//sed_printf("\n[%s][%d]retlen = %d, total_len=%d ", __FUNCTION__,__LINE__,retlen,total_len);
			sed_printf("\n Save to main fwdesc OK\n");

		}
		else{
			/* Write error */
			//sed_printf("\n[%s][%d]retlen = %llu, total_len=%d ", __FUNCTION__,__LINE__,retlen,total_len);
			sed_printf("\n [ERR] Save to main fwdesc FAILED, retlen = %llu, total_len=%d \n", retlen, data_len);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}

	}

ssu_read_backup_fwtab:
	if (ssu_retry == 0 && b_fw_desc_table_vaild == 0) {
		ssu_retry = 1;
		goto return_ssu_boot_flow;
	}

#endif
	return 0;

}


int kboot_read_fw_table_from_SPI(void)
{
	return 0;
}

int kboot_read_kernel_from_eMMC(void)
{
	return 0;
}

int kboot_read_kernel_from_NAND(fw_desc_table_v1_t *fw_desc_table_v1)
{
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
//	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from;
	unsigned int retlen;

	int ret = 0;
	uint fw_desc_table_base;
	fw_desc_entry_v1_t *this_entry;
	void *fw_entry;
	fw_desc_entry_v11_t *v11_entry;
#if defined(Config_Secure_RSA_TRUE)
	fw_desc_entry_v21_t *v21_entry;
#endif
	int i;
	uint unit_len;
	char buf[64];
	uint fw_checksum = 0;
	unsigned int secure_mode;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	SizeT decompressedSize = 0;
	uint fw_count;

	secure_mode = get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH;

	/* find fw_entry structure according to version */
	switch (fw_desc_table_v1->version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			unit_len = sizeof(fw_desc_entry_v1_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			unit_len = sizeof(fw_desc_entry_v11_t);
			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			unit_len = sizeof(fw_desc_entry_v21_t);
			break;

		default:
			return 1;
	}

	fw_desc_table_base = (KCPU_FIRMWARE_TABLE_ADDR | MIPS_KSEG0BASE);
	fw_count = fw_desc_table_v1->fw_list_len / unit_len;
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
				sizeof(fw_desc_table_v1_t) +
				fw_desc_table_v1->part_list_len);

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		this_entry = (fw_desc_entry_v1_t *)(fw_entry + unit_len * i);

		if (this_entry->target_addr)
		{
			switch(this_entry->type)
			{
				case FW_TYPE_KCPU:
					sed_printf("KCPU FW:\n");
					kcpu_entry_addr = (this_entry->target_addr | MIPS_KSEG0BASE);
					break;

				default:
					continue;
			}

			sed_printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
				this_entry->target_addr, this_entry->length, this_entry->target_addr + this_entry->length);

			sed_printf("\t FW Image fr 0x%08x %s\n", NAND_fw_desc_table_start + this_entry->offset, this_entry->lzma ? "(lzma)" : "(non-lzma)");

			if (this_entry->length == 0)
			{
				sed_printf("\t FW Image size is zero, skip this entry\n");
				continue;
			}

			/* get memory layout before copy fw image */
			mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
			mem_layout.bIsCompressed = this_entry->lzma;
			mem_layout.image_target_addr = this_entry->target_addr | MIPS_KSEG0BASE;

			get_mem_layout_when_read_image(&mem_layout);

			/* read image from flash */
			from = this_entry->offset;
			imageSize = this_entry->length;
			mem_layout.flash_to_ram_addr -= (this_entry->offset % nand->erasesize);
			get_flash_shared_semaphore();
			nand->read(nand, from, imageSize, (size_t *)&retlen, (u_char *)mem_layout.flash_to_ram_addr);
			release_flash_shared_semaphore();
			if (retlen != imageSize)
			{
				/* Read error */
				sed_printf("[ERR] %s:Read fw error!!\n", __FUNCTION__);

				return 1;
			}
			else
			{
				/* Read success */
				sed_printf("[OK] %s:Read fw ok!!\n", __FUNCTION__);
			}

			/* Check checksum */
			fw_checksum = get_checksum((unchar *)mem_layout.flash_to_ram_addr, imageSize);

			if (this_entry->checksum != fw_checksum)
			{
				sed_printf("\t FW Image checksum FAILED\n");
				sed_printf("\t FW Image entry  checksum=0x%08x\n", this_entry->checksum);
				sed_printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
			}

			/* if secure mode, do AES CBC decrypt */
			if (mem_layout.bIsEncrypted)
			{
				if (secure_mode == RTK_SECURE_BOOT)
				{
					rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);

					// decrypt image
					sed_printf("to decrypt...\n");
					if (decrypt_image((unchar *)mem_layout.encrpyted_addr,
						(unchar *)mem_layout.decrypted_addr,
						imageSize,
						Kh_key_ptr))
					{
						sed_printf("decrypt image(%d) error!\n", this_entry->type);
						return 1;
					}

					rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

					reverse_signature( (unsigned char *)(mem_layout.decrypted_addr + imageSize - img_truncated_size) );

					ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
											  imageSize - img_truncated_size - SHA256_SIZE,
											  (unsigned char *)(mem_layout.decrypted_addr + imageSize - img_truncated_size),
											  1 );
					if( ret ) {
						sed_printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
						return 1;
					}

					imageSize = imageSize - img_truncated_size - SHA256_SIZE;
				}
			}

			/* if lzma type, decompress image */
			if (mem_layout.bIsCompressed)
			{
				if (lzmaBuffToBuffDecompress((unchar*)mem_layout.decompressed_addr, &decompressedSize, (unchar*)mem_layout.compressed_addr, imageSize) != 0)
				{
					sed_printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

					return 1;
				}
			}

		}

		if (fw_desc_table_v1->version == FW_DESC_TABLE_V1_T_VERSION_11)
		{
			v11_entry = (fw_desc_entry_v11_t*) (fw_entry + unit_len * i);

			if (v11_entry->act_size != 0)
			{
				// string format: "part_num:act_size:hash,"
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "%d:%d:", v11_entry->part_num, v11_entry->act_size);
//				strncat(str_phash, buf, strlen(buf));
				memset(buf, 0, sizeof(buf));
				memcpy(buf, v11_entry->hash, sizeof(v11_entry->hash));
				buf[sizeof(v11_entry->hash)] = ',';
//				strncat(str_phash, buf, strlen(buf));
			}
		}
		else if (fw_desc_table_v1->version == FW_DESC_TABLE_V1_T_VERSION_21)
		{
#if defined(Config_Secure_RSA_TRUE)
			v21_entry = (fw_desc_entry_v21_t *)this_entry;

			// exclude partition 0 (contain bootcode/kernel/audio/video image)
			if ( (v21_entry->part_num != PART_TYPE_RESERVED) &&
				(v21_entry->act_size != 0) ){
				// recover hash value from signature
				memset(checksum, 0, sizeof(v21_entry->RSA_sign));
				memset(signature, 0, sizeof(v21_entry->RSA_sign)+1);
				memcpy(signature, v21_entry->RSA_sign, sizeof(v21_entry->RSA_sign));

				rsa_verify(signature, Config_Secure_RSA_MODULUS, checksum);

				// string format: "part_num:act_size:hash,"
				memset(buf, 0, sizeof(buf));
				sprintf(buf, "%d:%d:%s,", v21_entry->part_num, v21_entry->act_size, checksum);
//				strncat(str_phash, buf, strlen(buf));
				//sed_printf("[DEBUG_MSG] part_num:%x, act_size:%x, recovered hash:%s\n", v21_entry->part_num, v21_entry->act_size, checksum);
			}
#endif	/* defined(Config_Secure_RSA_TRUE) */
		}
	}

	return 0;
}


int kboot_read_kernel_from_SPI(void)
{
	return 0;
}

int kboot_setup_rescue(void)
{
	int ret = 0;

	/* read rescue image */
	if (boot_flash_type == BOOT_EMMC)
		ret = kboot_read_rescue_from_eMMC();
	else if (boot_flash_type == BOOT_NAND)
		ret = kboot_read_rescue_from_NAND();
	else
		ret = kboot_read_rescue_from_SPI();

	return ret;
}

int kboot_setup_kernel(void)
{
	int ret = 0;
	fw_desc_table_v1_t fw_desc_table_v1;

	sed_printf("kboot read fw table ...\n");

	/* read fw table */
	if (boot_flash_type == BOOT_EMMC)
		ret = kboot_read_fw_table_from_eMMC();
	else if (boot_flash_type == BOOT_NAND)
		ret = kboot_read_fw_table_from_NAND(&fw_desc_table_v1);
	else
		ret = kboot_read_fw_table_from_SPI();

	if (ret) {
		sed_printf("kboot read fw table error.\n");
		return ret;
	}

	sed_printf("kboot read kernel ...\n");

	/* read kernel image */
	if (boot_flash_type == BOOT_EMMC)
		ret = kboot_read_kernel_from_eMMC();
	else if (boot_flash_type == BOOT_NAND)
		ret = kboot_read_kernel_from_NAND(&fw_desc_table_v1);
	else
		ret = kboot_read_kernel_from_SPI();

	if (ret) {
		sed_printf("kboot read kernel error.\n");
	}

	if (kcpu_entry_addr == 0) {
		sed_printf("kernel not found.\n");
	}

	return ret;
}

int kboot_go_linux(void)
{
	char tmp_cmd[64];
	unsigned int memsize = 0;

	memset((void *)kcpu_argv, 0x0, KCPU_CMDLINE_SIZE);
	kcpu_argv[1] = (long)kcpu_cmdline;

	memsize = 0x20000000;

	sprintf(tmp_cmd, "memsize=0x%x ", memsize);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	sprintf(tmp_cmd, "boot_flash=%s ", SYS_PARAM_BOOT_FLASH);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	sprintf(tmp_cmd, "factory=0x%x@0x%x ", SYS_PARAM_FACTORY_SIZE, SYS_PARAM_FACTORY_START);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	sprintf(tmp_cmd, "factory_ro=0x%x@0x%x ", SYS_PARAM_FACTORY_RO_SIZE, SYS_PARAM_FACTORY_RO_START);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	sprintf(tmp_cmd, "bootcode=0x%x@0x%x ", SYS_PARAM_BOOTCODE_SIZE, SYS_PARAM_BOOTCODE_START);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	sprintf(tmp_cmd, "ss_start=0x%x ss_size=%x ", SYS_PARAM_SECURE_STORE_START, SYS_PARAM_SECURE_STORE_SIZE);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

	sprintf(tmp_cmd, "reserved_size=%x ", SYS_PARAM_FACTORY_RESERVED);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));

#ifdef CONFIG_SAFE_UPGRADE
	sprintf(tmp_cmd, "ssu=1 ");
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));
#endif

#ifdef PIN_FLASH_WP_STRING
	sprintf(tmp_cmd, "flash_wp=%s ", PIN_FLASH_WP_STRING);
	strncat(kcpu_cmdline, tmp_cmd, strlen(tmp_cmd));
#endif

	if (strlen(kcpu_cmdline) >= KCPU_CMDLINE_SIZE) {
		sed_printf("KCPU's command line parameters is TOO MUCH!\n");
		return 1;
	}

	sed_printf("kcpu_cmdline is %s ...\n", kcpu_cmdline);

	return 0;
}

