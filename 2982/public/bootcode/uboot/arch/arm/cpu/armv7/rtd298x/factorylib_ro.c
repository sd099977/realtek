#include <common.h>
#include <exports.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/system.h>
#include <fw_info.h>
#include <tar.h>

#ifdef CONFIG_SYS_RTK_NAND_FLASH
#include <linux/mtd/nand.h>		//surport nand flash
#include <nand.h>
#endif


#define ENABLE_FACTORY_RO_CONSOLE_MODE
//#define ENABLE_FACTORY_RO_DEBUG

#define FAC_RO_PRINTF(fmt, args...)		printf(fmt, ##args)

#ifdef	ENABLE_FACTORY_RO_DEBUG
#define FAC_RO_DEBUG(fmt, args...)		printf(fmt, ##args)
#else
#define FAC_RO_DEBUG(fmt, args...)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CONFIG_SYS_FACTORY_READ_ONLY
static int factory_ro_dirty = 0;
static uchar *factory_ro_buffer = NULL;
static uchar *factory_ro_buffer2 = NULL;
static int factory_ro_tarsize = 0;
static int factory_ro_seq_num = 0;

extern BOOT_FLASH_T boot_flash_type;
extern unsigned int tar_read_print_info;
extern unsigned char tar_read_print_prefix[32];
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef CONFIG_SYS_FACTORY_READ_ONLY
static int factory_ro_check_sanity_from_SPI(uchar *buffer, int length)
{
	int ret = 0;

#ifndef CONFIG_SYS_RTK_SPI_FLASH
	FAC_RO_DEBUG("[FAC_RO][WARN] CONFIG_SYS_RTK_SPI_FLASH is undefined\n");
#endif

	return ret;
}

static int factory_ro_check_sanity_from_NAND(uchar *buffer, int length)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
		int dev = nand_curr_device;
		nand_info_t *nand =&nand_info[dev];		//nand_info[0];
		struct nand_chip *this = (struct nand_chip *) nand->priv;
		unsigned int from,retlen,temp_page_num,temp_data_len;

		//uint factory_ro_header_bytes = 512;
		uint blk_start, blk_cnt = 0;
		int n = 0;
		int ret = 0;
		posix_header *p_start = NULL;
		posix_header *p_end = NULL;
		char factory_ro_header[] = FACTORY_RO_HEADER_FILE_NAME;
		uint data_ok = 0;
		unsigned int seqnum, tarsize;
		void *buf_contain_a_header;

		if (buffer == NULL) {
			FAC_RO_PRINTF("[FAC_RO][ERR] factory_ro buffer is NULL\n");
			return -1;
		}

		/* reset factory read-only data in ddr */
		memset(buffer, 0, length);

		p_start = (posix_header *)malloc(nand->oobblock);
		if (p_start == NULL) {
			FAC_RO_PRINTF("[FAC][ERR] p_start malloc(%d) failed\n", nand->oobblock);
			return -1;
		}

		memset(p_start, 0, nand->oobblock);

		buf_contain_a_header = (posix_header *)malloc(nand->oobblock * 2);
		if (buf_contain_a_header == NULL) {
			FAC_RO_PRINTF("[FAC][ERR] buf_contain_a_header malloc(%d) failed\n", nand->oobblock * 2);
			free(p_start);
			return -1;
		}

		memset(buf_contain_a_header, 0, nand->oobblock * 2);

		from = CONFIG_FACTORY_RO_START;
		nand->read(nand, from, nand->oobblock, &retlen, (unsigned char *)p_start);
		if (retlen != nand->oobblock)
		{
			/* Read error */
			FAC_RO_PRINTF("[FAC_RO][ERR] Get factory header from nand failed\n");
			ret = -1;
		}else
		{
			/* Read success */
			FAC_RO_DEBUG("[FAC_RO] Get factory header [%d] from nand\n", i);
		}


#ifdef ENABLE_FACTORY_RO_DEBUG
		FAC_RO_DEBUG("[FAC_RO] ******** CHECK FACTORY RO HEADER ********\n");

		if (!ret) {
			FAC_RO_DEBUG("[FAC_RO] -- PASS: read emmc\n");
		}
		else {
			FAC_RO_DEBUG("[FAC_RO] -- FAIL: read emmc\n");
		}

		if (!strcmp(p_start, factory_ro_header)) {
			FAC_RO_DEBUG("[FAC_RO] -- PASS: factory_ro header\n");
		}
		else {
			FAC_RO_DEBUG("[FAC_RO] -- FAIL: factory_ro header\n");
		}

		if (tar_check_header(p_start) == 0) {
			FAC_RO_DEBUG("[FAC_RO] -- PASS: tar header\n");
		}
		else {
			FAC_RO_DEBUG("[FAC_RO] -- FAIL: tar header\n");
		}

		if (p_start->rtk_tarsize >= 256) {
			FAC_RO_DEBUG("[FAC_RO] -- PASS: tar size >= 256\n");
		}
		else {
			FAC_RO_DEBUG("[FAC_RO] -- FAIL: tar size < 256\n");
		}

		if (!strcmp(p_start->rtk_signature, "RTK")) {
			FAC_RO_DEBUG("[FAC_RO] -- PASS: rtk signature\n");
		}
		else {
			FAC_RO_DEBUG("[FAC_RO] -- FAIL: rtk signature\n");
		}

		if (p_start->rtk_tarsize < (CONFIG_FACTORY_RO_SIZE - sizeof(posix_header))) {
			FAC_RO_DEBUG("[FAC_RO] -- PASS: tar size 0x%08x\n", p_start->rtk_tarsize);
		}
		else {
			FAC_RO_DEBUG("[FAC_RO] -- FAIL: tar size 0x%08x > 0x%08x\n", p_start->rtk_tarsize, CONFIG_FACTORY_RO_SIZE - sizeof(posix_header));
		}

		FAC_RO_DEBUG("[FAC_RO] ******** CHECK FACTORY RO HEADER ALL PASS\n");
		FAC_RO_DEBUG("[FAC_RO] Need to check the end header\n");
#endif

		if (!ret && !strcmp((const char *)p_start, factory_ro_header) && (tar_check_header((char *)p_start) == 0) && (p_start->rtk_tarsize >= 256)
				&& !strcmp(p_start->rtk_signature, "RTK") && (p_start->rtk_tarsize < (CONFIG_FACTORY_RO_SIZE - sizeof(posix_header)))) {

			seqnum = p_start->rtk_seqnum;
			tarsize = p_start->rtk_tarsize;

			temp_page_num = p_start->rtk_tarsize /nand->oobblock;
			//temp_page_num1 = p_start->rtk_tarsize % nand->oobblock;

			from = CONFIG_FACTORY_RO_START + temp_page_num*nand->oobblock ;

			nand->read(nand, from, nand->oobblock*2, &retlen,(unsigned char *)buf_contain_a_header);
			if (retlen != nand->oobblock)
			{
				/* Read error */
				FAC_RO_PRINTF("[FAC_RO][ERR] Get factory end header from nand failed\n");
				ret = -1;
			}else
			{
				/* Read success */
				FAC_RO_DEBUG("[FAC_RO] Get factory end header from nand\n");
			}

			p_end = (posix_header*)(((unsigned int) buf_contain_a_header) + (p_start->rtk_tarsize % nand->oobblock));


#if 0 //def ENABLE_FACTORY_RO_DEBUG
			FAC_RO_DEBUG("[FAC_RO] **dump p_start at %x\n", p_start);
			tar_dump_posix_header(p_start);

			FAC_RO_DEBUG("[FAC_RO] **dump p_end at %x\n", p_end);
			tar_dump_posix_header(p_end);
#endif

			if (!memcmp(p_end, p_start, sizeof(posix_header))) {
				data_ok = 1;
				FAC_RO_DEBUG("[FAC_RO] data_ok = %d\n", data_ok);
			}
		}

		free(p_start);
		free(buf_contain_a_header);

		FAC_RO_DEBUG("[FAC_RO] result: data_ok = 0x%x\n", data_ok);

		if (data_ok == 0)
		{
			p_start = (posix_header *)buffer;
			tar_build_header((char *)p_start, FACTORY_RO_HEADER_FILE_NAME, 0, '5');
			p_start->rtk_signature[0] = 'R';
			p_start->rtk_signature[1] = 'T';
			p_start->rtk_signature[2] = 'K';
			p_start->rtk_signature[3] = 0;
			p_start->rtk_tarsize = sizeof(posix_header);
			p_start->rtk_seqnum = factory_ro_seq_num;
			tar_fill_checksum((char *)p_start);
			tar_check_header((char *)p_start);
			FAC_RO_DEBUG("[FAC_RO] seq:0x%x\n", factory_ro_seq_num);
			FAC_RO_PRINTF("[FAC_RO] No factory_ro data in NAND\n");
			return sizeof(posix_header);
		}

		from = CONFIG_FACTORY_RO_START;
		temp_data_len = ((tarsize + nand->oobblock-1) /nand->oobblock) * nand->oobblock;
		nand->read(nand, from,temp_data_len, &retlen,(unsigned char *)buffer);

		factory_ro_seq_num = seqnum;

		FAC_RO_PRINTF("Factory_RO: seq:0x%x, size:0x%x (to 0x%x)\n",
			factory_ro_seq_num, tarsize, (unsigned int)buffer);

		return tarsize;

#else /* !CONFIG_SYS_RTK_NAND_FLASH */

		FAC_RO_DEBUG("[FAC_RO][WARN] CONFIG_SYS_RTK_EMMC_FLASH is undefined\n");
		return 0;

#endif
}

static int factory_ro_check_sanity_from_eMMC(uchar *buffer, int length)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH

	uint factory_ro_header_bytes = 512;
	uint blk_start, blk_cnt = 0;
	int n = 0;
	int ret = 0;
	posix_header *p_start = NULL;
	posix_header *p_end = NULL;
	char factory_ro_header[] = FACTORY_RO_HEADER_FILE_NAME;
	uint data_ok = 0;
	unsigned int seqnum, tarsize;
	void *buf_contain_a_header;

 	if (buffer == NULL) {
		FAC_RO_PRINTF("[FAC_RO][ERR] factory_ro buffer is NULL\n");
		return -1;
 	}

	/* reset factory read-only data in ddr */
	memset(buffer, 0, length);

	p_start = (posix_header *)malloc(factory_ro_header_bytes);
	if (p_start == NULL) {
		FAC_RO_PRINTF("[FAC][ERR] p_start malloc(%d) failed\n", factory_ro_header_bytes);
		return -1;
	}

	memset(p_start, 0, factory_ro_header_bytes);

	buf_contain_a_header = (posix_header *)malloc(factory_ro_header_bytes * 2);
	if (buf_contain_a_header == NULL) {
		FAC_RO_PRINTF("[FAC][ERR] buf_contain_a_header malloc(%d) failed\n", factory_ro_header_bytes * 2);
		free(p_start);
		return -1;
	}

	memset(buf_contain_a_header, 0, factory_ro_header_bytes * 2);

	/* Read factory ro header */
	blk_start = CONFIG_FACTORY_RO_START / EMMC_BLOCK_SIZE;
	blk_cnt = factory_ro_header_bytes / EMMC_BLOCK_SIZE;
	n = rtk_eMMC_read(blk_start, factory_ro_header_bytes, (unsigned int *)p_start);
	if (n != blk_cnt)
	{
		/* Read error */
		FAC_RO_PRINTF("[FAC_RO][ERR] Get factory_ro header from eMMC failed\n");
		ret = -1;
	}
	else
	{
		/* Read success */
		FAC_RO_DEBUG("[FAC_RO] Get factory_ro header from eMMC\n");
	}

#ifdef ENABLE_FACTORY_RO_DEBUG
	FAC_RO_DEBUG("[FAC_RO] ******** CHECK FACTORY RO HEADER ********\n");

	if (!ret) {
		FAC_RO_DEBUG("[FAC_RO] -- PASS: read emmc\n");
	}
	else {
		FAC_RO_DEBUG("[FAC_RO] -- FAIL: read emmc\n");
	}

	if (!strcmp(p_start, factory_ro_header)) {
		FAC_RO_DEBUG("[FAC_RO] -- PASS: factory_ro header\n");
	}
	else {
		FAC_RO_DEBUG("[FAC_RO] -- FAIL: factory_ro header\n");
	}

	if (tar_check_header(p_start) == 0) {
		FAC_RO_DEBUG("[FAC_RO] -- PASS: tar header\n");
	}
	else {
		FAC_RO_DEBUG("[FAC_RO] -- FAIL: tar header\n");
	}

	if (p_start->rtk_tarsize >= 256) {
		FAC_RO_DEBUG("[FAC_RO] -- PASS: tar size >= 256\n");
	}
	else {
		FAC_RO_DEBUG("[FAC_RO] -- FAIL: tar size < 256\n");
	}

	if (!strcmp(p_start->rtk_signature, "RTK")) {
		FAC_RO_DEBUG("[FAC_RO] -- PASS: rtk signature\n");
	}
	else {
		FAC_RO_DEBUG("[FAC_RO] -- FAIL: rtk signature\n");
	}

	if (p_start->rtk_tarsize < (CONFIG_FACTORY_RO_SIZE - sizeof(posix_header))) {
		FAC_RO_DEBUG("[FAC_RO] -- PASS: tar size 0x%08x\n", p_start->rtk_tarsize);
	}
	else {
		FAC_RO_DEBUG("[FAC_RO] -- FAIL: tar size 0x%08x > 0x%08x\n", p_start->rtk_tarsize, CONFIG_FACTORY_RO_SIZE - sizeof(posix_header));
	}

	FAC_RO_DEBUG("[FAC_RO] ******** CHECK FACTORY RO HEADER ALL PASS\n");
	FAC_RO_DEBUG("[FAC_RO] Need to check the end header\n");
#endif

	if (!ret && !strcmp((const char *)p_start, factory_ro_header) && (tar_check_header((char *)p_start) == 0) && (p_start->rtk_tarsize >= 256)
			&& !strcmp(p_start->rtk_signature, "RTK") && (p_start->rtk_tarsize < (CONFIG_FACTORY_RO_SIZE - sizeof(posix_header)))) {

		seqnum = p_start->rtk_seqnum;
		tarsize = p_start->rtk_tarsize;

		blk_start = (CONFIG_FACTORY_RO_START + p_start->rtk_tarsize) / EMMC_BLOCK_SIZE;
		n = rtk_eMMC_read(blk_start, EMMC_BLOCK_SIZE * 2, (unsigned int *)buf_contain_a_header);

		p_end = (posix_header*)(((unsigned int) buf_contain_a_header) + (p_start->rtk_tarsize % EMMC_BLOCK_SIZE));

#if 0 //def ENABLE_FACTORY_RO_DEBUG
		FAC_RO_DEBUG("[FAC_RO] **dump p_start at %x\n", p_start);
		tar_dump_posix_header(p_start);

		FAC_RO_DEBUG("[FAC_RO] **dump p_end at %x\n", p_end);
		tar_dump_posix_header(p_end);
#endif

		if (!memcmp(p_end, p_start, sizeof(posix_header))) {
			data_ok = 1;
			FAC_RO_DEBUG("[FAC_RO] data_ok = %d\n", data_ok);
		}
	}

	free(p_start);
	free(buf_contain_a_header);

	FAC_RO_DEBUG("[FAC_RO] result: data_ok = 0x%x\n", data_ok);

	if (data_ok == 0)
	{
		p_start = (posix_header *)buffer;
		tar_build_header((char *)p_start, FACTORY_RO_HEADER_FILE_NAME, 0, '5');
		p_start->rtk_signature[0] = 'R';
		p_start->rtk_signature[1] = 'T';
		p_start->rtk_signature[2] = 'K';
		p_start->rtk_signature[3] = 0;
		p_start->rtk_tarsize = sizeof(posix_header);
		p_start->rtk_seqnum = factory_ro_seq_num;
		tar_fill_checksum((char *)p_start);
		tar_check_header((char *)p_start);
		FAC_RO_DEBUG("[FAC_RO] seq:0x%x\n", factory_ro_seq_num);
		FAC_RO_PRINTF("[FAC_RO] No factory_ro data in eMMC\n");
		return sizeof(posix_header);
	}

	blk_start = (CONFIG_FACTORY_RO_START) / EMMC_BLOCK_SIZE;
	n = rtk_eMMC_read(blk_start, tarsize, (unsigned int *)buffer);

	factory_ro_seq_num = seqnum;

	FAC_RO_PRINTF("Factory_RO: seq:0x%x, blk:0x%x, size:0x%x (to 0x%x)\n",
		factory_ro_seq_num, blk_start, tarsize, (unsigned int)buffer);

	return tarsize;

#else /* !CONFIG_SYS_RTK_EMMC_FLASH */

	FAC_RO_DEBUG("[FAC_RO][WARN] CONFIG_SYS_RTK_EMMC_FLASH is undefined\n");
	return 0;

#endif
}

static int factory_ro_get_from_SPI(uchar *buffer)
{
	int ret = 0;

	ret = factory_ro_check_sanity_from_SPI(buffer, CONFIG_FACTORY_RO_SIZE);

	return ret;
}

static int factory_ro_get_from_NAND(uchar *buffer)
{
	int ret = 0;

	ret = factory_ro_check_sanity_from_NAND(buffer, CONFIG_FACTORY_RO_SIZE);

	return ret;
}

static int factory_ro_get_from_eMMC(uchar *buffer)
{
	int ret = 0;

	ret = factory_ro_check_sanity_from_eMMC(buffer, CONFIG_FACTORY_RO_SIZE);

	return ret;
}

static int factory_ro_save_to_SPI(uchar* buffer, int len)
{
	return 0;
}

static int factory_ro_save_to_NAND(uchar* buffer, int len)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int to;
	u_char *oob_buf;		//oob size
	unsigned int retlen;
	struct erase_info *instr;
	int erase_ret=0;

	posix_header *pp_start;
	unsigned int next_seqnum;
	uint blk_start, blk_cnt, n;
	uint total_len;

	if (buffer == NULL) {
		return -1;
	}

	oob_buf = malloc(nand->oobsize);
	if(oob_buf == NULL){
		printf("[FAC_RO][ERR] factory_ro_save_to_NAND: allocate oob_buf failed!!!\n");
		return -1;
	}

	next_seqnum = factory_ro_seq_num + 1;

	/* fill the first header as RTK header */
	pp_start = (posix_header *)buffer;
	pp_start->rtk_signature[0] = 'R';
	pp_start->rtk_signature[1] = 'T';
	pp_start->rtk_signature[2] = 'K';
	pp_start->rtk_signature[3] = 0;
	pp_start->rtk_tarsize = (unsigned int)len;
	pp_start->rtk_seqnum = next_seqnum;
	tar_fill_checksum((char *)pp_start);

	/* copy this RTK header to the end of tar file for data check */
	memcpy((void *)(((unsigned int) pp_start) + pp_start->rtk_tarsize), pp_start, sizeof(posix_header));

	/* the last block will be reserved to save serial no , and magic no */
	/* can't exceed 2M size - (1 block size)  */
	if (len > (CONFIG_FACTORY_RO_SIZE - nand->erasesize) ) {
		FAC_RO_DEBUG("[FAC_RO][ERR] factory_ro_save_to_NAND: too big\n");
		return 1;
	}

	total_len =  ((len + sizeof(posix_header) + nand->oobblock-1) / nand->oobblock) * nand->oobblock;
	oob_buf[0] = 0x82;

	to = CONFIG_FACTORY_RO_START;

	instr = (struct erase_info *)malloc(sizeof(struct erase_info));
	if(instr == NULL){
		printf("[FAC_RO][ERR] factory_save_to_NAND: allocate erase_info failed!!!\n");
		return -1;
	}
	memset(instr, 0x00, sizeof(struct erase_info));
	instr->mtd = nand;
	instr->addr = to;
	instr->len = total_len;
	erase_ret = nand->erase(nand, instr);
	if (erase_ret != 0) {
		printf("\n[FAC][ERR] factory_save_to_NAND: MTD Erase failure: %d\n",erase_ret);
		return 1;
	}else{
		free(instr);
	}

	nand->write_ecc(nand, to, total_len, &retlen, (u_char *)buffer, (u_char *)oob_buf, NULL);

	if(retlen == total_len){
		/* Write success */
		FAC_RO_PRINTF("[FAC_RO] Save to nand  OK\n");
	}else{
		/* Write error */
		FAC_RO_PRINTF("[FAC_RO][ERR] Save to nand FAILED\n");
		return 1;
	}

	/* remove the RTK header at the end of tar file to prevent side effect */
		memset((void *)(((unsigned int) pp_start) + pp_start->rtk_tarsize), 0, sizeof(posix_header));

		factory_ro_seq_num = next_seqnum;

#endif

		return 0;

}

static int factory_ro_save_to_eMMC(uchar* buffer, int len)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH

	posix_header *pp_start;
	unsigned int next_seqnum;
	uint blk_start, blk_cnt, n;
	uint total_len;

 	if (buffer == NULL) {
		return -1;
 	}

	next_seqnum = factory_ro_seq_num + 1;

	/* fill the first header as RTK header */
	pp_start = (posix_header *)buffer;
	pp_start->rtk_signature[0] = 'R';
	pp_start->rtk_signature[1] = 'T';
	pp_start->rtk_signature[2] = 'K';
	pp_start->rtk_signature[3] = 0;
	pp_start->rtk_tarsize = (unsigned int)len;
	pp_start->rtk_seqnum = next_seqnum;
	tar_fill_checksum((char *)pp_start);

	/* copy this RTK header to the end of tar file for data check */
	memcpy((void *)(((unsigned int) pp_start) + pp_start->rtk_tarsize), pp_start, sizeof(posix_header));

	/* the last block will be reserved to save serial no , and magic no */
	/* can't exceed 2M size - (1 block size)  */
	if (len > (CONFIG_FACTORY_RO_SIZE - EMMC_BLOCK_SIZE) ) {
		FAC_RO_DEBUG("[FAC_RO][ERR] factory_ro_save_to_eMMC: too big\n");
		return 1;
	}

	total_len = len + sizeof(posix_header);

	blk_start = CONFIG_FACTORY_RO_START / EMMC_BLOCK_SIZE;
	blk_cnt = ALIGN(total_len , EMMC_BLOCK_SIZE) / EMMC_BLOCK_SIZE;
	n = rtk_eMMC_write(blk_start, total_len, (uint *)buffer);
	if (n != blk_cnt)
	{
		/* Write error */
		FAC_RO_PRINTF("[FAC_RO][ERR] Save to eMMC FAILED\n");
		return 1;
	}
	else
	{
		/* Write success */
		FAC_RO_PRINTF("[FAC_RO] Save to eMMC (blk#:0x%x, buf:0x%08x, len:0x%x, seq#:0x%x)\n",
			blk_start, (uint)buffer, total_len, next_seqnum);
	}

	/* remove the RTK header at the end of tar file to prevent side effect */
	memset((void *)(((unsigned int) pp_start) + pp_start->rtk_tarsize), 0, sizeof(posix_header));

	factory_ro_seq_num = next_seqnum;

#endif

	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int factory_ro_dump_info(void)
{

	FAC_RO_PRINTF("****** dump factory read-only info ******\n");
	FAC_RO_PRINTF("boot_flash_type       = ");
	switch(boot_flash_type){
		case BOOT_NOR_SERIAL:
			FAC_RO_PRINTF("NOR\n");
			break;

		case BOOT_NAND:
			FAC_RO_PRINTF("NAND\n");
			break;

		case BOOT_EMMC:
			FAC_RO_PRINTF("MMC\n");
			break;

		default:
			FAC_RO_PRINTF("UNKNOWN\n");
			break;
	}

	FAC_RO_PRINTF("factory_ro_buffer     = 0x%08x\n", (uint)factory_ro_buffer);
	FAC_RO_PRINTF("factory_ro_buffer2    = 0x%08x\n", (uint)factory_ro_buffer2);
	FAC_RO_PRINTF("factory_ro_tarsize    = 0x%08x\n", factory_ro_tarsize);
	FAC_RO_PRINTF("factory_ro_seq_num    = 0x%08x\n", factory_ro_seq_num);

	return 0;
}

int factory_ro_dump_list(void)
{
	char *dst_addr;
	uint dst_length;

	tar_read_print_info = 1;

	memset(tar_read_print_prefix, 0, sizeof(tar_read_print_prefix));

	strcpy((char *)tar_read_print_prefix, FACTORY_RO_HEADER_FILE_NAME);

	tar_read("DUMMY_NAME_FOR_DUMP", (char *)rtk_mem_info->factory_ro_data_addr, CONFIG_FACTORY_RO_SIZE, &dst_addr, &dst_length);

	tar_read_print_info = 0;

	return 0;
}

int factory_ro_reset(void)
{
	posix_header *p_start = NULL;

 	if (factory_ro_buffer == NULL) {
		FAC_RO_PRINTF("[FAC_RO] factory_ro_reset: factory_ro_buffer is NULL\n");
		return -1;
 	}

	/* reset sequence number */
	factory_ro_seq_num = 0;

	/* reset tar size */
	factory_ro_tarsize = sizeof(posix_header);

	memset(factory_ro_buffer, 0, CONFIG_FACTORY_RO_SIZE);

	/* build RTK header */
	p_start = (posix_header *)factory_ro_buffer;
	tar_build_header((char *)p_start, FACTORY_RO_HEADER_FILE_NAME, 0, '5');
	p_start->rtk_signature[0] = 'R';
	p_start->rtk_signature[1] = 'T';
	p_start->rtk_signature[2] = 'K';
	p_start->rtk_signature[3] = 0;
	p_start->rtk_tarsize = sizeof(posix_header);
	p_start->rtk_seqnum = 0;
	tar_fill_checksum((char *)p_start);
	tar_check_header((char *)p_start);

	// save to factory ro data
	factory_ro_dirty = 1;

	factory_ro_save();

	return 0;
}

int factory_ro_delete(char *path)
{
 	if (factory_ro_buffer == NULL) {
		FAC_RO_PRINTF("[FAC_RO] factory_ro_delete: factory_ro_buffer is NULL\n");
		return -1;
 	}

	memset(factory_ro_buffer2, 0, CONFIG_FACTORY_RO_SIZE);
	factory_ro_tarsize = tar_add_or_delete((char *)factory_ro_buffer, path, 0, 0, (char *)factory_ro_buffer2, CONFIG_FACTORY_RO_SIZE, 0);
	factory_ro_dirty = 1;

	return 0;
}

#if 0 // cklai@mark unused code
int factory_ro_read_by_index(int index, char *buffer, int *length, char *name)
{
 	if (factory_ro_buffer == NULL) {
		FAC_RO_PRINTF("[FAC_RO] factory_ro_read_by_index: factory_ro_buffer is NULL\n");
		return -1;
 	}

	return tar_read_by_index(index, (char *)factory_ro_buffer, buffer, length, name);
}
#endif

/*
 * Return Value:
 *    0: success
 *    1: tar read failed
 *   -1: factory ro buffer error
 */
int factory_ro_read(char *path, char**buffer, int *length)
{
 	if (factory_ro_buffer == NULL) {
		FAC_RO_PRINTF("[FAC_RO] factory_ro_read: factory_ro_buffer is NULL\n");
		return -1;
 	}

	return tar_read(path, (char *)factory_ro_buffer, CONFIG_FACTORY_RO_SIZE, buffer, (uint *)length) == 0;
}

int factory_ro_write(char *path, char *buffer, int length)
{
	int length_512 = ((length + 511)/512) * 512;

 	if (factory_ro_buffer == NULL) {
		FAC_RO_PRINTF("[FAC_RO] factory_ro_write: factory_ro_buffer is NULL\n");
		return -1;
 	}

	if (length_512 + factory_ro_tarsize + 512 > CONFIG_FACTORY_RO_SIZE) {
		FAC_RO_PRINTF("[FAC_RO] factory_ro_write: too big\n");
		return -1;
	}

	memset(factory_ro_buffer2, 0 , CONFIG_FACTORY_RO_SIZE);

	if ((factory_ro_tarsize = tar_add_or_delete((char *)factory_ro_buffer, path, buffer, length, (char *)factory_ro_buffer2, CONFIG_FACTORY_RO_SIZE, 1)) == 0)  {
		FAC_RO_PRINTF("[FAC_RO] factory_ro_write: tar_add_or_delete fail\n");
		return -1;
	}
	FAC_RO_DEBUG("factory_ro_tarsize = 0x%x\n", factory_ro_tarsize);

	factory_ro_dirty = 1;

	return 0;
}

int factory_ro_save(void)
{
	int ret = 0;

	FAC_RO_PRINTF("[FAC_RO] factory_ro_save: ");

 	if (factory_ro_buffer == NULL) {
		FAC_RO_PRINTF("FAILED (factory_ro_buffer is NULL)\n");
		return -1;
 	}

	if (factory_ro_dirty && factory_ro_tarsize > 0) {

		switch(boot_flash_type){
			case BOOT_NOR_SERIAL:
				FAC_RO_PRINTF("NOR\n");
				ret = factory_ro_save_to_SPI(factory_ro_buffer, factory_ro_tarsize);
				break;

			case BOOT_NAND:
				FAC_RO_PRINTF("NAND\n");
				get_flash_shared_semaphore();
				ret = factory_ro_save_to_NAND(factory_ro_buffer, factory_ro_tarsize);
				release_flash_shared_semaphore();
				break;

			case BOOT_EMMC:
				FAC_RO_PRINTF("MMC\n");
				ret = factory_ro_save_to_eMMC(factory_ro_buffer, factory_ro_tarsize);
				break;

			default:
				FAC_RO_PRINTF("UNKNOWN\n");
				ret = -1;
				break;
		}
	}
	else {
		FAC_RO_PRINTF("no change\n");
		FAC_RO_DEBUG("[FAC_RO] factory_ro_dirty is %d\n", factory_ro_dirty);
	}

	factory_ro_dirty = 0;

	return ret;
}

int factory_ro_init(void)
{
	int ret = 0;

	factory_ro_buffer = (uchar *)rtk_mem_info->factory_ro_data_addr;
	factory_ro_buffer2 = (uchar *)rtk_mem_info->factory_ro_data_addr + CONFIG_FACTORY_RO_SIZE;

	switch(boot_flash_type){
		case BOOT_NOR_SERIAL:
			FAC_RO_PRINTF("NOR\n");
			factory_ro_tarsize = factory_ro_get_from_SPI(factory_ro_buffer);
			break;

		case BOOT_NAND:
			FAC_RO_PRINTF("NAND\n");
			get_flash_shared_semaphore();
			factory_ro_tarsize = factory_ro_get_from_NAND(factory_ro_buffer);
			release_flash_shared_semaphore();
			break;

		case BOOT_EMMC:
			FAC_RO_PRINTF("MMC\n");
			FAC_RO_DEBUG("[FAC_RO] factory_ro_buffer  = 0x%x\n", factory_ro_buffer);
			FAC_RO_DEBUG("[FAC_RO] factory_ro_buffer2 = 0x%x\n", factory_ro_buffer2);
			factory_ro_tarsize = factory_ro_get_from_eMMC(factory_ro_buffer);
			FAC_RO_DEBUG("[FAC_RO] factory_ro_tarsize = 0x%x\n", factory_ro_tarsize);
			break;

		default:
			FAC_RO_PRINTF("UNKNOWN\n");
			ret = -1;
			break;
	}

	return ret;
}

#ifdef ENABLE_FACTORY_RO_CONSOLE_MODE
int do_factory_ro(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char *buffer;
	unsigned long dst_buffer;//for rtice tool factory_ro read
	int length;
	int rc;
	char buf [12];

	if (argc < 2) {
		return CMD_RET_USAGE;
	}
	else {
		if (strcmp(argv[1], "save") == 0) {
			factory_ro_save();
		}
		else if (strcmp(argv[1], "reset") == 0) {
			factory_ro_reset();
		}
		else if (strcmp(argv[1], "info") == 0) {
			factory_ro_dump_info();
		}
		else if (strcmp(argv[1], "list") == 0) {
			factory_ro_dump_list();
		}
		else if (strcmp(argv[1], "delete") == 0) {
			factory_ro_delete(argv[2]);
		}
		else if (strcmp(argv[1], "read") == 0) {
			rc = factory_ro_read(argv[2], &buffer, &length);

			if (rc)
				FAC_RO_PRINTF("%s: file not found\n", argv[2]);
			else
			{
				sprintf(buf, "%x", length);
				setenv("filesize", buf);
				FAC_RO_PRINTF("%s: %d bytes at 0x%08x\n", argv[2], length, (uint)buffer);

				if (argc == 4) {
					dst_buffer = simple_strtoul(argv[3], NULL, 16);
					memcpy((void *)dst_buffer, (void *)buffer, length);
					FAC_RO_PRINTF("src[0x%08x] dst[0x%08x]\n", (uint)buffer, (uint)dst_buffer);
				}
			}
		}
		else if (strcmp(argv[1], "write") == 0) {

			buffer = (char *)simple_strtoul(argv[3], NULL, 16);
			length = (int)simple_strtoul(argv[4], NULL, 16);

			factory_ro_write(argv[2], buffer, length);
		}
		else {
			return CMD_RET_USAGE;
		}
	}

	return 0;
}


U_BOOT_CMD(
	facro,	5,	1,	do_factory_ro,
	"FACTORY read-only sub system",
	"read path\n"
	"facro write path addr length\n"
	"facro delete path\n"
	"facro save\n"
	"facro reset\n"
	"facro info\n"
	"facro list"
);
#endif
#endif

