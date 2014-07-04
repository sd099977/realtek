/******************************************************************************
 * $Id: nand_base_rtk.c 317223 2010-06-01 07:38:49Z alexchang2131 $
 * drivers/mtd/nand/nand_base_rtk.c
 * Overview: Realtek MTD NAND Driver
 * Copyright (c) 2008 Realtek Semiconductor Corp. All Rights Reserved.
 * Modification History:
 *    #000 2008-06-10 Ken-Yu   create file
 *    #001 2008-09-10 Ken-Yu   add BBT and BB management
 *    #002 2008-09-28 Ken-Yu   change r/w from single to multiple pages
 *    #003 2008-10-09 Ken-Yu   support single nand with multiple dies
 *    #004 2008-10-23 Ken-Yu   support multiple nands
 *
 *******************************************************************************/
#include <common.h>
#include <linux/types.h>
#include <linux/mtd/mtd.h>
#include <asm/io.h>
#include <linux/bitops.h>
// Ken-Yu
#include <mtd/mtd-abi.h>
#include <linux/mtd/rtk_nand.h>
#include <asm/arch/rbus/nand_reg.h>
#include <linux/bitops.h>
#include "rtk_nand_list.h"
#include <asm/arch/sys_param_nand.h>

#ifdef CONFIG_NAND_MULTI_READ_FOR_CARDREADER
	#define NAND_POWEROFF_CARDREADER_WITH_MULTI_READ	(1)//add for fixing card reader share pin bug. alexchang 0831-2010
#else
	#define NAND_POWEROFF_CARDREADER_WITH_MULTI_READ	(0)//add for fixing card reader share pin bug. alexchang 0831-2010
#endif

#ifdef CONFIG_NAND_READ_SKIP_UPDATE_BBT
	#define NAND_READ_SKIP_UPDATE_BBT		(1)//add for fixing card reader share pin bug. alexchang 0901-2010
#else
	#define NAND_READ_SKIP_UPDATE_BBT		(0)//add for fixing card reader share pin bug. alexchang 0901-2010
#endif
//#ifdef CONFIG_NAND_BBT_NEW_MECHANISM
//	#define NAND_BBT_NEW_MECHANISM		(1)//add for fixing card reader share pin bug. alexchang 1026-2010
//	static struct semaphore nf_BBT_sem;
//#else
//	#define NAND_BBT_NEW_MECHANISM		(0)//add for fixing card reader share pin bug. alexchang 1026-2010
//#endif

static unsigned char g_isSysSecure = 0;
extern unsigned char g_isRandomize;
#define Nand_Block_Isbad_Slow_Version 0
#define MTD_SEM_RETRY_COUNT	(0x40)
#define NOTALIGNED(mtd, x) (x & (mtd->oobblock-1)) != 0
#define NAND_CP_RW_DISABLE (0xFFFFFFFF)

#define check_end(mtd, addr, len)					\
do {									\
	if (mtd->size == 0) 						\
		return -ENODEV;						\
	else								\
	if ((addr + len) > mtd->size) {					\
		printk (				\
			"%s: attempt access past end of device\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while(0)

#define check_page_align(mtd, addr)					\
do {									\
	if (addr & (mtd->oobblock - 1)) {				\
		printk (				\
			"%s: attempt access non-page-aligned data\n",	\
			__FUNCTION__);					\
		printk (				\
			"%s: mtd->oobblock = 0x%x\n",			\
			__FUNCTION__,mtd->oobblock);			\
		return -EINVAL;						\
	}								\
} while (0)

#define check_block_align(mtd, addr)					\
do {									\
	if (addr & (mtd->erasesize - 1)) {				\
		printk (				\
			"%s: attempt access non-block-aligned data\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while (0)

#define check_len_align(mtd,len)					\
do {									\
	if (len & (512 - 1)) {          	 			\
		printk (				\
               	      "%s: attempt access non-512bytes-aligned mem\n",	\
			__FUNCTION__);					\
		return -EINVAL;						\
	}								\
} while (0)

#ifdef CONFIG_MTD_NAND_IBT
#define BAD_BLOCK  0x0
#define GOOD_BLOCK 0x1
#define BLANK_BLOCK 0x2

#define BOTH_OK 0x0
#define B1_ERR 0x1
#define B2_ERR 0x2
#define BOTH_ERR	B1_ERR|B2_ERR
#endif
extern char *rtkNF_parse_token(const char *parsed_string, const char *token);
extern unsigned int rtkNF_getBootcodeSize(void);
extern unsigned int rtkNF_getFactParaSize(void);

extern int is_magellan_cpu(void);



int TEST_READ_WRITE(struct mtd_info *mtd, int page);

unsigned int g_mtd_BootcodeSize = 0;

#ifdef CONFIG_MTD_NAND_IBT
unsigned int IBT_LEN=0;
unsigned int g_ss_tarsize=0;
unsigned int g_ro_start=0;
#endif


#if NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
/*
	parse_token can parse a string and extract the value of designated token.
		parsed_string: The string to be parsed.
		token: the name of the token
		return value: If return value is NULL, it means that the token is not found.
			If return value is "non zero", it means that the token is found, and return value will be a string that contains the value of that token.
			If the token doesn't have a value, return value will be a string that contains empty string ("\0").
			If return value is "non zero", "BE SURE" TO free it after you donot need it.

		Exp:
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A0");
				=> value=NULL
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A1");
				=> value points to a string of "\0"
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A2");
				=> value points to a string of "222"
			char *value=parse_token("A1 A2=222 A3=\"333 333\"", "A3");
				=> value points to a string of "333 333"
*/
static char *NF_parse_token(const char *parsed_string, const char *token)
{
	const char *ptr = parsed_string;
	const char *start, *end, *value_start, *value_end;
	char *ret_str;

	while(1) {
		value_start = value_end = 0;
		for(;*ptr == ' ' || *ptr == '\t'; ptr++)	;
		if(*ptr == '\0')	break;
		start = ptr;
		for(;*ptr != ' ' && *ptr != '\t' && *ptr != '=' && *ptr != '\0'; ptr++) ;
		end = ptr;
		if(*ptr == '=') {
			ptr++;
			if(*ptr == '"') {
				ptr++;
				value_start = ptr;
				for(; *ptr != '"' && *ptr != '\0'; ptr++)	;
				if(*ptr != '"' || (*(ptr+1) != '\0' && *(ptr+1) != ' ' && *(ptr+1) != '\t')) {
					printk("system_parameters error! Check your parameters.");
					break;
				}
			} else {
				value_start = ptr;
				for(;*ptr != ' ' && *ptr != '\t' && *ptr != '\0' && *ptr != '"'; ptr++) ;
				if(*ptr == '"') {
					printk("system_parameters error! Check your parameters.");
					break;
				}
			}
			value_end = ptr;
		}

		if(!strncmp(token, start, end-start)) {
			if(value_start) {
				ret_str = kmalloc(value_end-value_start+1, GFP_KERNEL);
				strncpy(ret_str, value_start, value_end-value_start);
				ret_str[value_end-value_start] = '\0';
				return ret_str;
			} else {
				ret_str = kmalloc(1, GFP_KERNEL);
				strcpy(ret_str, "");
				return ret_str;
			}
		}
	}

	return (char*)NULL;
}
#endif

#if NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
u32 NF_rtk_power_gpio=0;
u32 NF_rtk_power_bits=0;
void NF_rtkcr_card_power(u8 status)
{
    void __iomem *mmio = (void __iomem *) NF_rtk_power_gpio;
    if(status==0){ //power on
        printk("Card Power on\n");
        writel(readl(mmio) & ~(1<<NF_rtk_power_bits),mmio);
    }else{          //power off
        printk("Card Power off\n");
        writel(readl(mmio) | (1<<NF_rtk_power_bits),mmio);
    }
}
void NF_rtkcr_chk_param(u32 *pparam, u32 len, u8 *ptr)
{
    unsigned int value,i;
    for(i=0;i<len;i++){
        value = ptr[i] - '0';
        if((value >= 0) && (value <=9))
        {
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
        value = ptr[i] - 'a';
        if((value >= 0) && (value <=5))
        {
            value+=10;
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
        value = ptr[i] - 'A';
        if((value >= 0) && (value <=5))
        {
            value+=10;
            *pparam+=value<<(4*(len-1-i));
            continue;
        }
    }
}
int NF_rtkcr_get_gpio(void)
{
    unsigned char *cr_param;
    void __iomem *mmio;
//    cr_param=(char *)NF_parse_token(platform_info.system_parameters,"cr_pw");
    if(cr_param){
        NF_rtkcr_chk_param(&NF_rtk_power_gpio,4,cr_param);
        NF_rtkcr_chk_param(&NF_rtk_power_bits,2,cr_param+5);

        mmio = (void __iomem *) (NF_rtk_power_gpio+0xb8010000);
        writel(readl(mmio) | (1<<NF_rtk_power_bits),mmio); //enable GPIO output

        if((NF_rtk_power_gpio & 0xf00) ==0x100){
            NF_rtk_power_gpio+=0xb8010010;
        }else if((NF_rtk_power_gpio & 0xf00) ==0xd00){
            NF_rtk_power_gpio+=0xb8010004;
        }else{
            printk(KERN_ERR "wrong GPIO of card's power.\n");
            return -1;
        }
        printk("power_gpio = 0x%x\n",NF_rtk_power_gpio);
        printk("power_bits = %d\n",NF_rtk_power_bits);
        return 0;
    }
    printk(KERN_ERR "Can't find GPIO of card's power.\n");
    return -1;

}

#endif


/* NAND low-level MTD interface functions */
static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf);
static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *buf,
			u_char *oob_buf, struct nand_oobinfo *oobsel);
static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf);
static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char * buf,
			const u_char *oob_buf, struct nand_oobinfo *oobsel);
static int nand_erase (struct mtd_info *mtd, struct erase_info *instr);
static int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt);
static void nand_sync (struct mtd_info *mtd);
static int nand_suspend (struct mtd_info *mtd);
static void nand_resume (struct mtd_info *mtd);
static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops);
static int nand_read_oob_ext (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen, u_char *oob_buf);

static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops);

/* YAFFS2 */

static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs);
static int nand_block_markbad (struct mtd_info *mtd, loff_t ofs);
static int rtk_secure_store_init(struct mtd_info *mtd, u16 chipnr);

/////////////////////////////////////////
static int rtk_update_bbt (struct mtd_info *mtd, __u8 *data_buf, __u8 *oob_buf, BB_t *bbt);
static int TEST_ERASE_ALL(struct mtd_info *mtd, int page, int bc);



/* Global Variables */
int RBA=0;
static int oob_size, ppb, isLastPage;
static int page_size = 0;
//CMYu:, 20090415
//extern platform_info_t platform_info;
char *mp_erase_nand;
int mp_erase_flag = 0;
//CMYu:, 20090512
char *mp_time_para;
int mp_time_para_value = 0;
char *nf_clock;
int nf_clock_value = 0;
//CMYu:, 20090720
char *mcp;
//CMYu:, 20091030
int read_has_check_bbt = 0;
unsigned int read_block = 0XFFFFFFFF;
unsigned int read_remap_block = 0XFFFFFFFF;
int write_has_check_bbt = 0;
unsigned int write_block = 0XFFFFFFFF;
unsigned int write_remap_block = 0XFFFFFFFF;

//===========================================================================
static void NF_CKSEL(char *PartNum, unsigned int value)
{
	REG_WRITE_U32( 0xb800000c,REG_READ_U32(0xb800000c)& (~0x00800000));
	REG_WRITE_U32( 0xb8000034,value);
	REG_WRITE_U32(0xb800000c,REG_READ_U32(0xb800000c)| (0x00800000));
	printk("[%s] %s is set to nf clock: 0x%x\n", __FUNCTION__, PartNum, value);
}
//------------------------------------------------------------------------------------------------
#if 0
static inline int generic_ffs(int x)
{
	int r = 1;
	if (!x)
		return 0;
	if (!(x & 0xffff)) {
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff)) {
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf)) {
		x >>= 4;
		r += 4;
	}
	if (!(x & 3)) {
		x >>= 2;
		r += 2;
	}
	if (!(x & 1)) {
		x >>= 1;
		r += 1;
	}
	return r;
}
#endif
//------------------------------------------------------------------------------------------------
static int  check_BBT(struct mtd_info *mtd, unsigned int blk)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	printk("[%s]..\n", __FUNCTION__);
	int i;
	//int BBs=0;

	for ( i=0; i<RBA; i++)
	{
		if ( this->bbt[i].bad_block == blk )
		{
			printk("blk 0x%x exist\n",blk);
			return -1;
		}
	}

	return 0;
}

//------------------------------------------------------------------------------------------------

static void dump_BBT(struct mtd_info *mtd)
{

	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int i;
	int BBs=0;
	printk("[%s] Nand BBT Content\n", __FUNCTION__);
	for ( i=0; i<RBA; i++){
		if ( i==0 && this->bbt[i].BB_die == BB_DIE_INIT && this->bbt[i].bad_block == BB_INIT ){
			printk("Congratulation!! No BBs in this Nand.\n");
			break;
		}
		if ( this->bbt[i].bad_block != BB_INIT ){
			printk("[%d] (%d, %u, %d, %u)\n", i, this->bbt[i].BB_die, this->bbt[i].bad_block,
				this->bbt[i].RB_die, this->bbt[i].remap_block);
			BBs++;
		}
	}
	this->BBs = BBs;
}
#if 0//NAND_BBT_NEW_MECHANISM
int rtk_GetRemapBlk(struct mtd_info *mtd, int chipnr_remap, int block )
{
	struct nand_chip *this = mtd->priv;
	int i=0;
	int retBlk = -1;
	for ( i=0; i<RBA; i++){
	if ( this->bbt[i].bad_block != BB_INIT ){
		if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
			retBlk = this->bbt[i].remap_block;
			if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
				this->active_chip = chipnr_remap = this->bbt[i].RB_die;
				this->select_chip(mtd, chipnr_remap);
			}
		}
	}else
		break;
	}
	return retBlk;
}
//-------------------------------------------------------------------------------------------------
int rtk_BadBlkRemapping(struct mtd_info *mtd, int chipnr, int chipnr_remap, int badblock, int* err_chipnr_remap  )
{
	struct nand_chip *this = mtd->priv;
	int i=0;
	int retBlk = -1;
	while (down_interruptible (&nf_BBT_sem)) {
		printk("%s : Retry\n",__FUNCTION__);
		//return -ERESTARTSYS;
	}
	for( i=0; i<RBA; i++){
		if(this->bbt[i].bad_block==badblock)
		{
			up(&nf_BBT_sem);
			return -1;
		}
	}
	for( i=0; i<RBA; i++){
		if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
			if ( chipnr != chipnr_remap)
				this->bbt[i].BB_die = chipnr_remap;
			else
				this->bbt[i].BB_die = chipnr;
			this->bbt[i].bad_block = badblock;
			if(err_chipnr_remap)
				*err_chipnr_remap = this->bbt[i].RB_die;
			retBlk = this->bbt[i].remap_block;
			break;
		}
	}
	up(&nf_BBT_sem);
	if ( retBlk == -1 ){
		printk("[%s] RBA do not have free remap block\n", __FUNCTION__);
		return -1;
	}
	dump_BBT(mtd);
	return retBlk;
}
#endif


static void reverse_to_Yaffs2Tags(__u8 *r_oobbuf)
{
	int k;
	int cpBits=0;
	if(page_size==2048)
		cpBits=16;
	else
		cpBits=32;
	for ( k=0; k<cpBits; k++ ){
//	for ( k=0; k<oob_size; k++ ){
		r_oobbuf[k]  = r_oobbuf[1+k];
	}
}


 static int rtk_block_isbad(struct mtd_info *mtd, u16 chipnr, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block, page_offset;
	unsigned char block_status_p1;

	//unsigned char buf[oob_size] __attribute__((__aligned__(4)));

	this->active_chip=chipnr=0;
	page = ((int) ofs) >> this->page_shift;
	page_offset = page & (ppb-1);
	block = page/ppb;
	memset(this->g_oobbuf, 0xff, oob_size);
	
	if ( isLastPage ){
		page = block*ppb + (ppb-1);
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->g_oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p1 = this->g_oobbuf[0];

	}else{
		if ( this->read_oob (mtd, chipnr, page, oob_size, this->g_oobbuf) ){
			printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
			return 1;
		}
		block_status_p1 = this->g_oobbuf[0];

	}

	if(block <= (SYS_PARAM_FW_TABLE_START/mtd->erasesize)){
		if (( block_status_p1 != BLOCK_CLEAN)&&(block_status_p1 != BLOCK_HWSETTING)&&(block_status_p1 != BLOCK_KEY_SIG)&&  \
		(block_status_p1 != BLOCK_OTHER_DATA)&&(block_status_p1 != BLOCK_BBT)&& (block_status_p1 != BLOCK_FACTORY_SETTING) && \
		(block_status_p1 != BLOCK_BOOTCODE)&& (block_status_p1 != BLOCK_DATA)&&(block_status_p1 != BLOCK_ENVPARAM_MAGICNO)&& \
		(block_status_p1 != BLOCK_IBT)&& (block_status_p1 != BLOCK_EMCU) && (block_status_p1 != BLOCK_KBOOT)){
		
			printf("Bootcode/Secure-store/Factory area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  1;		//error block tag, bad block
		}
		
	}else{
		if(block_status_p1 != 0xff){
			printf("block tag error!!! block_status_p1 = [%x], block_no = [0x%x]\n",block_status_p1,block);
			return  1;		//error block tag, bad block
		}
	}

	return 0;
}


static int nand_block_isbad (struct mtd_info *mtd, loff_t ofs)
{
	int rc = 0;
	//unsigned int chipnr=0;

	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block, page_offset;
	unsigned int chipnr=0;
	unsigned char block_status_p1;
	unsigned int temp;

	//unsigned char buf[oob_size] __attribute__((__aligned__(4)));

	/* Check for invalid offset */
	if (ofs > mtd->size)
		return -EINVAL;

	page = ((int) ofs) >> this->page_shift;
	page_offset = page & (ppb-1);
	block = page/ppb;
	memset(this->g_oobbuf, 0xff, oob_size);
	
	if ( this->read_oob (mtd, chipnr, page, oob_size, this->g_oobbuf) ){
		printf("read oob error!!!\n");
		return 1;		//read error, bad block
	}
	block_status_p1 = this->g_oobbuf[0];

	if(block <= (SYS_PARAM_FW_TABLE_START/mtd->erasesize)){
		if (( block_status_p1 != BLOCK_CLEAN)&&(block_status_p1 != BLOCK_HWSETTING)&&(block_status_p1 != BLOCK_KEY_SIG)&&  \
		(block_status_p1 != BLOCK_OTHER_DATA)&&(block_status_p1 != BLOCK_BBT)&& (block_status_p1 != BLOCK_FACTORY_SETTING) && \
		(block_status_p1 != BLOCK_BOOTCODE)&& (block_status_p1 != BLOCK_DATA)&&(block_status_p1 != BLOCK_ENVPARAM_MAGICNO)&& \
		(block_status_p1 != BLOCK_IBT) && (block_status_p1 != BLOCK_EMCU)&& (block_status_p1 != BLOCK_KBOOT)){
			return  1;		//error block tag, bad block
		}
		
	}else{
		if(block_status_p1 != 0xff){
			//printf("[%s][%d]block tag error!!! block_status_p1 = [%x]",__FUNCTION__,__LINE__,block_status_p1);
			return  1;		//error block tag, bad block
		}
	}

	return rc;
}


static int nand_block_markbad (struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block, page_offset;
	int i;
	int rc = 0;
	unsigned char buf[oob_size] __attribute__((__aligned__(4)));
	int chipnr, chipnr_remap;

	page = ((int) ofs) >> this->page_shift;
	this->active_chip = chipnr = chipnr_remap = (int)(ofs >> this->chip_shift);
	page_offset = page & (ppb-1);
	block = page/ppb;

	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);

#ifdef CONFIG_MTD_NAND_IBT
	//search ibt
	if(this->use_ibt){
		if(((this->ibt[block].src_block ==	SRC_INIT)&&(this->ibt[block].dst_block ==  DST_INIT)) ||(this->ibt[block].dst_block== block)){
			#ifdef _DEBUG_IBT
			printk(" [%s][block no = 0x%x]ibt  ...\n",__FUNCTION__,block);
			#endif
		}else if(this->ibt[block].dst_block != block){
			block = this->ibt[block].dst_block;
			#ifdef _DEBUG_IBT
			printk(" [%s][block no = 0x%x]ibt search...\n", __FUNCTION__,block);
			#endif
		}
	}
#endif

	for ( i=0; i<RBA; i++){
		if ( this->bbt[i].bad_block != BB_INIT ){
			if ( chipnr == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
				block = this->bbt[i].remap_block;
				if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
					this->active_chip = chipnr_remap = this->bbt[i].RB_die;
					this->select_chip(mtd, chipnr_remap);
				}
			}
		}else
			break;
	}
	page = block*ppb + page_offset;

	buf[0]=0x00;
	rc = this->write_oob (mtd, this->active_chip, page, oob_size, buf);
	if (rc) {
			//DEBUG (MTD_DEBUG_LEVEL0, "%s: write_oob failed\n", __FUNCTION__);
			return -1;
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------

static int nf_scan_block_tag(struct mtd_info *mtd, unsigned int from, unsigned int depth, unsigned int page_count,unsigned char block_tag)
{
	struct nand_chip *this = mtd->priv;
	int res,stop_block;
	int i=0;
	int chipnr=0;
	int page;
	int ret_value = 0;
	unsigned int spare_tags;

	spare_tags = ((page_count & 0xffff) << 16) | block_tag;
	stop_block = from + depth;
	this->active_chip=chipnr=0;
	this->select_chip(mtd, chipnr);
	
	for(i = from; i < stop_block; i++ ){
		page = i*this->ppb;
		//reset buf
		memset(this->g_oobbuf, 0xff, this->oob_size);
		res = this->read_oob(mtd, chipnr, page, this->oob_size, this->g_oobbuf);
		if(res < 0){
			//read fail, jump next block
			continue;

		}else{
			//check spare value
			if(spare_tags == ((unsigned int *)this->g_oobbuf)[0]){
				ret_value = i;
				break;
			}
		}
	}

	//return
	if(spare_tags == ((unsigned int *)this->g_oobbuf)[0]){
		return ret_value;
	}else{
		//return fail
		return 0;
	}

}

//sync from romcode
static int nand_rescue_image_read(struct mtd_info *mtd, unsigned char* dst_buf, unsigned int from, unsigned int length, unsigned int page_count, const unsigned char magic)
{
	struct nand_chip *this = mtd->priv;
	int res = 0;
	unsigned int count = 0;
	unsigned int retry = 0x20;
	unsigned int spare_tags;
	unsigned int current_page;
	int chipnr=0;
	int data_len = 0;

	if ((from + length) > mtd->size) {
		printf("nf_rescue_image_read: Attempt read beyond end of device\n");
		return -1;
	}

	if (NOTALIGNED (mtd, from)) {
		printf("nf_rescue_image_read: Attempt to read not page aligned data\n");
		return -1;
	}

	this->active_chip=chipnr=0;
	this->select_chip(mtd, chipnr);

	current_page = from/page_size;
	
	if (length % page_size) {
		// align length to page boundary
		length = (length / page_size + 1) * page_size;
	}

	while (count < length) {
		memset(this->g_oobbuf, 0xff, oob_size);
		res = this->read_ecc_page (mtd, this->active_chip, current_page, &dst_buf[data_len], this->g_oobbuf);
		if (res) {	// ECC error happened
jump_to_next_blk:
			if (--retry) {
				// jump to the same offset of next block
				current_page += ppb;
				continue;
			}
			else	// retry too many times, return failed
				return -1;
		}

		// check spare area to see if this correct page
		spare_tags = ((page_count & 0xffff) << 16) | magic;
		if (spare_tags != ((unsigned int *)this->g_oobbuf)[0]) {
			// maybe page counter is not correct, or magic number not match, or just an empty page (it's not the page we want anyway)
			goto jump_to_next_blk;
		}

		// read ok, go to next page
		current_page++;
		data_len += page_size;
		count += page_size;
		page_count++;	// remember to increment page counter in spare area
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------

static int nand_read_oob_ext (struct mtd_info *mtd, loff_t from, size_t len, size_t *retlen,
			u_char *oob_buf)
{
	struct nand_chip *this = mtd->priv;
	unsigned int page, realpage;
	int oob_len = 0, thislen;
	int rc=0;
	int old_page, page_offset, block;
	int chipnr, chipnr_remap;
	int i;

	if ((from + len) > mtd->size) {
		printk ("nand_read_oob: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}


	if (NOTALIGNED (mtd, from)) {
		printk (KERN_NOTICE "nand_read_oob: Attempt to read not page aligned data\n");
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	block = page/ppb;
	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);


	if ( retlen )
		*retlen = 0;
	thislen = oob_size;

	while (oob_len < len) {
		if (thislen > (len - oob_len))
			thislen = (len - oob_len);

		#ifdef CONFIG_MTD_NAND_IBT
		//search ibt
		if(this->use_ibt){
			if(((this->ibt[block].src_block ==	SRC_INIT)&&(this->ibt[block].dst_block ==  DST_INIT)) ||(this->ibt[block].dst_block== block)){
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt  ...\n",__FUNCTION__,block);
				#endif
			}else if(this->ibt[block].dst_block != block){
				block = this->ibt[block].dst_block;
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt search...\n", __FUNCTION__,block);
				#endif
			}
		}
		#endif

		for ( i=0; i<RBA; i++){
			if ( this->bbt[i].bad_block != BB_INIT ){
				if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
					block = this->bbt[i].remap_block;
					if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
						this->active_chip = chipnr_remap = this->bbt[i].RB_die;
						this->select_chip(mtd, chipnr_remap);
					}
				}
			}else
				break;
		}

		page = block*ppb + page_offset;

		rc = this->read_oob (mtd, this->active_chip, page, thislen, &oob_buf[oob_len]);
		if (rc < 0) {
			if (rc == -1){
				printk ("%s: read_oob: Un-correctable HW ECC\n", __FUNCTION__);
				if(check_BBT(mtd,page/ppb)==0)
				{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							this->bbt[i].BB_die = chipnr_remap;
						else
							this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page/ppb;
						break;
					}
				}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, this->g_databuf, this->g_oobbuf, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
					}
				}

				this->g_oobbuf[0] = 0x00;
				if ( isLastPage ){
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->g_oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->g_oobbuf);
				}else{
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->g_oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->g_oobbuf);
				}
				printk("rtk_read_oob: Un-correctable HW ECC Error at page=%d\n", page);
			}else{
				printk ("%s: rtk_read_oob: semphore failed\n", __FUNCTION__);
				return -1;
			}
		}

		oob_len += thislen;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( oob_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page/ppb;
	}

	if ( retlen ){
		if ( oob_len == len )
			*retlen = oob_len;
		else{
			printk("[%s] error: oob_len %d != len %d\n", __FUNCTION__, oob_len, len);
			return -1;
		}
	}

	return 0;
}


static int nand_read (struct mtd_info *mtd, loff_t from, size_t len, size_t * retlen, u_char * buf)
{
	int rc=0;
	unsigned int retryCnt = MTD_SEM_RETRY_COUNT;
	unsigned int rd_len;
	unsigned int tmp_len;
	
	if(g_isSysSecure||g_isRandomize)
  {
        if(g_isRandomize)
			mtd->isCPdisable_R = 0;
		if(g_isSysSecure)
		{
			if(*retlen == NAND_CP_RW_DISABLE)
				mtd->isCPdisable_R = 1;
			else
				mtd->isCPdisable_R = 0;
		}
//		if(g_isRandomize)
//		{
//			//mtd->isScramble= 1;
//			mtd->isCPdisable_R = 0;
//		}
	}
	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);

	//printf("[%s] mtd->oobblock =%u\n", __FUNCTION__, mtd->oobblock);
	
	tmp_len = rd_len = len;
	// align read length to page boundary
	if (rd_len & (mtd->oobblock - 1))
	{
		rd_len = (rd_len / mtd->oobblock + 1) * mtd->oobblock;
	}

	len = rd_len;
	rc = nand_read_ecc (mtd, from, len, retlen, buf, NULL, NULL);

	if(*retlen == len)
		*retlen=tmp_len;
		
	if(g_isSysSecure||g_isRandomize)
        {
		//printk("[%s] done \n",__FUNCTION__);
		//mtd->isScramble= 0;

	}

	return rc;
}

static int nand_read_oob (struct mtd_info *mtd, loff_t from, struct mtd_oob_ops *ops)
{
	int rc = 0;
	unsigned int retryCnt = MTD_SEM_RETRY_COUNT;
	if(g_isSysSecure||g_isRandomize)
	{
        if(g_isRandomize)
        {
			//mtd->isScramble = 1;
			mtd->isCPdisable_R = 0;
        }
		else
			mtd->isCPdisable_R = 1;//Add by alexchang for disable yaffs cp read. 0614-2011

	}
	//printk("[%s] mtd->oobblock =%u\n", __FUNCTION__, mtd->oobblock);
	mtd->oobinfo.useecc = ops->mode;
	//printk("[%s]scramble 0x%x\n",__FUNCTION__,mtd->isScramble);
	if(ops->len==ops->ooblen)// read oob
		 rc = nand_read_oob_ext(mtd, from, ops->len, &ops->retlen,ops->oobbuf);
	else
	{

		 rc = nand_read_ecc(mtd, from, ops->len, &ops->retlen,ops->datbuf, ops->oobbuf, NULL);
	}

	if(g_isSysSecure||g_isRandomize)
        {
//		printk("[%s] done \n",__FUNCTION__);
		//mtd->isScramble= 0;


	}

	return rc;
}
static int nand_read_ecc (struct mtd_info *mtd, loff_t from, size_t len,
			size_t *retlen, u_char *buf, u_char *oob_buf, struct nand_oobinfo *oobsel)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned long long  page, realpage,page_ppb;
	int data_len, oob_len;
	int rc;
	unsigned int old_page, page_offset, block;
	int chipnr, chipnr_remap;
	int i;
	int tmp_isCPdisable_R = mtd->isCPdisable_R;

	if ((from + len) > mtd->size) {
		printf ("nand_read_ecc: Attempt read beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}

	if (NOTALIGNED (mtd, from) || NOTALIGNED(mtd, len)) {
		printf (KERN_NOTICE "nand_read_ecc: Attempt to read not page aligned data\n");
		return -EINVAL;
	}

	realpage = (int)(from >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(from >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	
	page_offset = page & (ppb-1);
	//block = page/ppb;
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;
	
	//printk("\t\tReady to READ blk:%u, page:%u, len:%u, page_size:%d, oob_size:%d\n",page/ppb,page%ppb,len,page_size,oob_size);

	this->active_chip=chipnr=chipnr_remap=0;
	//CMYu, 20091030
	if ( this->numchips == 1 && block != read_block ){
		read_block = block;
		read_remap_block = 0xFFFFFFFF;
		read_has_check_bbt = 0;
	}
	if(oobsel)
	{
		if (oobsel->useecc==MTD_ECC_RTK_HW )
		{
			mtd->ecctype = MTD_ECC_RTK_HW;
		}
		else
			mtd->ecctype = MTD_ECC_NONE;
	}
	else
		mtd->ecctype = mtd->oobinfo.useecc;

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = oob_len = 0;

	while (data_len < len) {
		//CMYu, 20091030
		#if 0
		if ( this->numchips == 1){
			if ( (page>=block*ppb) && (page<(block+1)*ppb) && read_has_check_bbt==1 )
				goto SKIP_BBT_CHECK;
		}
		#endif

		#ifdef CONFIG_MTD_NAND_IBT
		//search ibt
		if(this->use_ibt){
			if(((this->ibt[block].src_block ==	SRC_INIT)&&(this->ibt[block].dst_block ==  DST_INIT)) ||(this->ibt[block].dst_block== block)){
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt  ...\n",__FUNCTION__,block);
				#endif
			}else if(this->ibt[block].dst_block != block){
				block = this->ibt[block].dst_block;
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt search...\n", __FUNCTION__,block);
				#endif
			}
		}
		#endif

		read_remap_block = 0xFFFFFFFF;
		for ( i=0; i<RBA; i++){
			if ( this->bbt[i].bad_block != BB_INIT ){
				if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
					read_remap_block = block = this->bbt[i].remap_block;
					if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
						this->active_chip = chipnr_remap = this->bbt[i].RB_die;
						this->select_chip(mtd, chipnr_remap);
					}
				}
			}else
				break;
		}

		read_has_check_bbt = 1;

SKIP_BBT_CHECK:
		if ( this->numchips == 1 && read_has_check_bbt==1 ){
			if ( read_remap_block == 0xFFFFFFFF )
				page = block*ppb + page_offset;
			else
				page = read_remap_block*ppb + page_offset;
		}else
			page = block*ppb + page_offset;
		
		mtd->isCPdisable_R =tmp_isCPdisable_R;
		//printf("block no = 0x%x, page_no = %llu\n",block,page);

		rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], &oob_buf[oob_len]);
		if (rc < 0) {
			#if	NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
			printk("[%s]Try again..\n",__FUNCTION__);
			NF_rtkcr_card_power(1);//power off card reader.
			rc = this->read_ecc_page (mtd, this->active_chip, page, &buf[data_len], &oob_buf[oob_len]);
			if(rc<0)
			{
			#if NAND_READ_SKIP_UPDATE_BBT
				return -1;
			#endif
			}
			#endif
			if (rc == -1){
				printk ("%s: read_ecc_page: Un-correctable HW ECC\n", __FUNCTION__);

				#ifdef CONFIG_MTD_NAND_IBT
				if(this->use_ibt)
					page_ppb = block;
				#endif

				//update BBT
				if(check_BBT(mtd,page_ppb)==0)
				{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							this->bbt[i].BB_die = chipnr_remap;
						else
							this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page_ppb;
						break;
					}
				}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, this->g_databuf, this->g_oobbuf, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
					}
				}

				this->g_oobbuf[0] = 0x00;
				block = page_ppb;
				if ( isLastPage){
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->g_oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->g_oobbuf);
				}else{
					this->erase_block (mtd, this->active_chip, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->g_oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->g_oobbuf);
				}
				printk("rtk_read_ecc_page: Un-correctable HW ECC Error at page=%llu\n", page);
			}else{
				printk ("%s: read_ecc_page:  semphore failed\n", __FUNCTION__);
				return -1;
			}
		}
		//else
			//printk("\t\tConfirm to READ blk:%u, page:%u Succeed!!\n",page/ppb,page%ppb);
		data_len += page_size;

		if(oob_buf)//add by alexchang 0524-2010
		oob_len += oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page/ppb;
	}

	if ( retlen ){
		if ( data_len == len )
			*retlen = data_len;
		else{
			printk("[%s] error: data_len %d != len %d\n", __FUNCTION__, data_len, len);
			return -1;
		}
	}
	//printk("[%s]OK\n",__FUNCTION__);

	return 0;
}


static int nand_write (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen, const u_char *buf)
{
	int rc = 0;
	unsigned int retryCnt = MTD_SEM_RETRY_COUNT;
	if(g_isSysSecure||g_isRandomize)
        {

		if(g_isRandomize)
		{
			//mtd->isScramble = 1;
			mtd->isCPdisable_W = 0;
		}
		else
			mtd->isCPdisable_W = 1;//Add by alexchang for disable yaffs cp read. 0614-2011
		//printk("[%s]Set mtd->isCPdisable_W --> 0 ",__FUNCTION__);
		//printk("[%s]Scrabmle flag 0x%x\n",__FUNCTION__,mtd->isScramble);
	}
	else
		mtd->isCPdisable_W = 1;
	rc = (nand_write_ecc (mtd, to, len, retlen, buf, NULL, NULL));

	if(g_isSysSecure||g_isRandomize)
        {
		//printk("[%s] done\n",__FUNCTION__);
		//mtd->isScramble= 0;
	}
	return rc;
}

static int nand_write_oob (struct mtd_info *mtd, loff_t to, struct mtd_oob_ops *ops)//for 2.6.34 YAFFS-->mtd
{
	int rc = 0;
	unsigned int retryCnt = MTD_SEM_RETRY_COUNT;
	if(g_isSysSecure||g_isRandomize)
        {

		if(g_isRandomize)
		{
			//mtd->isScramble = 1;
			mtd->isCPdisable_W = 0;
		}
		else
			mtd->isCPdisable_W = 1;//Add by alexchang for disable yaffs cp read. 0614-2011
		//printk("[%s]Set mtd->isCPdisable_W --> 1 ",__FUNCTION__);
		//printk("[%s]Scrabmle flag 0x%x\n",__FUNCTION__,mtd->isScramble);
	}
	rc =  nand_write_ecc (mtd, to, ops->len, &ops->retlen,ops->datbuf, ops->oobbuf, NULL);
	if(g_isSysSecure||g_isRandomize)
        {
		//	mtd->isScramble= 0;
		//printk("[%s] done\n",__FUNCTION__);

	}
	return rc;
}

static int nand_write_ecc (struct mtd_info *mtd, loff_t to, size_t len, size_t *retlen,
			const u_char * buf, const u_char *oob_buf, struct nand_oobinfo *oobsel)
{
	struct nand_chip *this = mtd->priv;
	unsigned long long page, realpage,page_ppb;
	int data_len, oob_len;
	int rc;
	unsigned int i, old_page, page_offset, block;
	int chipnr, chipnr_remap, err_chipnr = 0, err_chipnr_remap = 1;
	int backup_offset;
	int block_remap=0x12345678;
	int tmp_isCPdisable_W = mtd->isCPdisable_W;
	
	if ((to + len) > mtd->size) {
		printk ("nand_write_ecc: Attempt write beyond end of device\n");
		*retlen = 0;
		return -EINVAL;
	}
	
	if (NOTALIGNED (mtd, to) || NOTALIGNED(mtd, len)) {
		printf ("nand_write_ecc: Attempt to write not page aligned data\n");
		return -EINVAL;
	}
	
	realpage = (unsigned long long)(to >> this->page_shift);
	this->active_chip = chipnr = chipnr_remap = (int)(to >> this->chip_shift);
	old_page = page = realpage & this->pagemask;
	page_offset = page & (ppb-1);
	//block = page/ppb;
	page_ppb = page;
	do_div(page_ppb,ppb);
	block = (unsigned int)page_ppb;
	//CMYu, 20091030

	this->active_chip=chipnr=chipnr_remap=0;
	if ( this->numchips == 1 && block != write_block ){
		write_block = block;
		write_remap_block = 0xFFFFFFFF;
		write_has_check_bbt = 0;
	}

	this->select_chip(mtd, chipnr);

	if ( retlen )
		*retlen = 0;

	data_len = oob_len = 0;

	while ( data_len < len) {

		//CMYu, 20091030
		#if 0
		if ( this->numchips == 1){
			if ( (page>=block*ppb) && (page<(block+1)*ppb) && write_has_check_bbt==1 )
			{
				//printk("goto skip_bbt_check: write_has_check_bbt %d\n",write_has_check_bbt);
				goto SKIP_BBT_CHECK;
			}
		}
		#endif
		#ifdef CONFIG_MTD_NAND_IBT
		//search ibt
		if(this->use_ibt){
			if(((this->ibt[block].src_block ==	SRC_INIT)&&(this->ibt[block].dst_block ==  DST_INIT)) ||(this->ibt[block].dst_block== block)){
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt  ...\n",__FUNCTION__,block);
				#endif
			}else if(this->ibt[block].dst_block != block){
				block = this->ibt[block].dst_block;
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt search...\n", __FUNCTION__,block);
				#endif
			}
		}
		#endif

		write_remap_block = 0xFFFFFFFF;
		for ( i=0; i<RBA; i++){
			if ( this->bbt[i].bad_block != BB_INIT ){
				if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
					write_remap_block = block = this->bbt[i].remap_block;
					if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
						this->active_chip = chipnr_remap = this->bbt[i].RB_die;
						this->select_chip(mtd, chipnr_remap);
					}
				}
			}else
				break;
		}

		write_has_check_bbt = 1;

SKIP_BBT_CHECK:
		if ( this->numchips == 1 && write_has_check_bbt==1 ){
			if ( write_remap_block == 0xFFFFFFFF )
				page = block*ppb + page_offset;
			else
				page = write_remap_block*ppb + page_offset;
		}else
			page = block*ppb + page_offset;
		//printk("Confirm to write blk:%u, page:%u\n",page/ppb,page%ppb);
		mtd->isCPdisable_W= tmp_isCPdisable_W;
		if(oob_buf)
			rc = this->write_ecc_page (mtd, this->active_chip, page, &buf[data_len], &oob_buf[oob_len], 0);
		else
			rc = this->write_ecc_page (mtd, this->active_chip, page, &buf[data_len], NULL, 0);

		if (rc < 0) {
			if ( rc == -1){
				//printk ("%s: write_ecc_page:  write blk:%u, page:%u failed\n", __FUNCTION__,page/ppb,page%ppb);

			#ifdef CONFIG_MTD_NAND_IBT
			if(this->use_ibt)
				page_ppb = block;
			#endif
			
			if(check_BBT(mtd,page_ppb)==0)
			{

				/* update BBT */
				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT){
						if ( chipnr != chipnr_remap)	//remap block is bad
							err_chipnr = chipnr_remap;
						else
							err_chipnr = chipnr;
						this->bbt[i].BB_die = err_chipnr;
						this->bbt[i].bad_block = page_ppb;
						err_chipnr_remap = this->bbt[i].RB_die;
						block_remap = this->bbt[i].remap_block;
						break;
					}
				}

				if ( block_remap == 0x12345678 ){
					printk("[%s] RBA do not have free remap block\n", __FUNCTION__);
					return -1;
				}
			}

				dump_BBT(mtd);

				if ( rtk_update_bbt (mtd, this->g_databuf, this->g_oobbuf, this->bbt) ){
					printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
					return -1;
				}

				backup_offset = page&(ppb-1);
				this->select_chip(mtd, err_chipnr_remap);
				this->erase_block (mtd, err_chipnr_remap, block_remap*ppb);
#if 0
				printk("[%s] Start to Backup old_page from %d to %d\n", __FUNCTION__, block*ppb, block*ppb+backup_offset-1);

				for ( i=0; i<backup_offset; i++){
					if ( err_chipnr != err_chipnr_remap ){
						this->active_chip = err_chipnr;
						this->select_chip(mtd, err_chipnr);
					}
					this->read_ecc_page(mtd, this->active_chip, (page/ppb)*ppb+i, this->g_databuf, this->g_oobbuf);
					if ( this->g_oobbuf )
						reverse_to_Yaffs2Tags(this->g_oobbuf);
					if ( err_chipnr != err_chipnr_remap ){
						this->active_chip = err_chipnr_remap;
						this->select_chip(mtd, err_chipnr_remap);
					}
					this->write_ecc_page(mtd, this->active_chip, block_remap*ppb+i, this->g_databuf, this->g_oobbuf, 0);
				}
				this->write_ecc_page (mtd, this->active_chip, block_remap*ppb+backup_offset, &buf[data_len], &oob_buf[oob_len], 0);
				printk("[%s] write failure page = %d to %d\n", __FUNCTION__, page, block_remap*ppb+backup_offset);
#endif
				if ( err_chipnr != err_chipnr_remap ){
					this->active_chip = err_chipnr;
					this->select_chip(mtd, err_chipnr);
				}

				this->g_oobbuf[0] = 0x00;
				block = page_ppb;
				if ( isLastPage ){
					this->erase_block (mtd, err_chipnr, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-1, oob_size, this->g_oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+ppb-2, oob_size, this->g_oobbuf);
				}else{
					this->erase_block (mtd, err_chipnr, block*ppb);
					this->write_oob(mtd, this->active_chip, block*ppb, oob_size, this->g_oobbuf);
					this->write_oob(mtd, this->active_chip, block*ppb+1, oob_size, this->g_oobbuf);
				}
			}else{
				printk ("%s: write_ecc_page:  rc=%d\n", __FUNCTION__, rc);
				return -1;
			}
		}
		//else
			//printk("Confirm to write blk:%u, page:%u Succeed!!\n",page/ppb,page%ppb);
		data_len += page_size;
		oob_len += oob_size;

		old_page++;
		page_offset = old_page & (ppb-1);
		if ( data_len<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}
		block = old_page/ppb;
	}

	if ( retlen ){

		if ( data_len == len )
			*retlen = data_len;
		else{
			printk("[%s] error: data_len %d != len %d\n", __FUNCTION__, data_len, len);
			return -1;
		}
	}
	return 0;
}


static int nand_erase (struct mtd_info *mtd, struct erase_info *instr)
{

	return nand_erase_nand (mtd, instr, 0);
}


static int nand_erase_nand (struct mtd_info *mtd, struct erase_info *instr, int allowbbt)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	u_int32_t addr = instr->addr;
	u_int32_t len = instr->len;
	int page, chipnr;
	int old_page, block;
	int elen = 0;
	int rc = 0;
	int realpage, chipnr_remap, block_remap=0x12345678;

	check_end (mtd, addr, len);
	check_block_align (mtd, addr);

	 instr->fail_addr = 0xffffffff;

	realpage = ((int) addr) >> this->page_shift;
	this->active_chip = chipnr = chipnr_remap = ((int) addr) >> this->chip_shift;
	old_page = page = realpage & this->pagemask;
	block = page/ppb;

	this->active_chip=chipnr=chipnr_remap=0;
	this->select_chip(mtd, chipnr);

	instr->state = MTD_ERASING;
	while (elen < len) {
		//printk("Ready to Erase blk %u\n",page/ppb);

		#ifdef CONFIG_MTD_NAND_IBT
		//search ibt
		if(this->use_ibt){
			if(((this->ibt[block].src_block ==  SRC_INIT)&&(this->ibt[block].dst_block ==  DST_INIT)) ||(this->ibt[block].dst_block== block)){
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt  ...\n",__FUNCTION__,block);
				#endif
			}else if(this->ibt[block].dst_block != block){
				block = this->ibt[block].dst_block;
				#ifdef _DEBUG_IBT
				printk(" [%s][block no = 0x%x]ibt search...\n", __FUNCTION__,block);
				#endif
			}
		}
		#endif

		int i;
		for ( i=0; i<RBA; i++){
			if ( this->bbt[i].bad_block != BB_INIT ){
				if ( this->active_chip == this->bbt[i].BB_die && block == this->bbt[i].bad_block ){
					block = this->bbt[i].remap_block;
					if ( this->bbt[i].BB_die != this->bbt[i].RB_die ){
						this->active_chip = chipnr_remap = this->bbt[i].RB_die;
						this->select_chip(mtd, chipnr_remap);
					}
				}
			}else
				break;
		}

		page = block*ppb;
		//printk("confirm to Erase blk %u\n",page/ppb);
		rc = this->erase_block (mtd, this->active_chip, page);

		if (rc) {
			printk ("%s: block erase failed at page address=0x%08x\n", __FUNCTION__, addr);
			instr->fail_addr = (page << this->page_shift);
			if(check_BBT(mtd,page/ppb)==0)
			{

				for( i=0; i<RBA; i++){
					if ( this->bbt[i].bad_block == BB_INIT && this->bbt[i].remap_block != RB_INIT)
						{
							if ( chipnr != chipnr_remap)
								this->bbt[i].BB_die = chipnr_remap;
							else
								this->bbt[i].BB_die = chipnr;
						this->bbt[i].bad_block = page/ppb;
						block_remap = this->bbt[i].remap_block;
						break;
					}
				}

				if ( block_remap == 0x12345678 ){
					printk("[%s] RBA do not have free remap block[%d]\n", __FUNCTION__,RBA);
					return -1;
				}
			}

			dump_BBT(mtd);

			if ( rtk_update_bbt (mtd, this->g_databuf, this->g_oobbuf, this->bbt) ){
				printk("[%s] rtk_update_bbt() fails\n", __FUNCTION__);
				return -1;
			}

			this->g_oobbuf[0] = 0x00;
			if ( isLastPage ){
				this->write_oob(mtd, chipnr, page+ppb-1, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, page+ppb-2, oob_size, this->g_oobbuf);
			}else{
				this->write_oob(mtd, chipnr, page, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, page+1, oob_size, this->g_oobbuf);
			}

			rc = this->erase_block(mtd, chipnr_remap, block_remap*ppb);
		}
		//else
			//printk("confirm to Erase blk %u  succeed!!\n",page/ppb);

		if ( chipnr != chipnr_remap )
			this->select_chip(mtd, chipnr);

		elen += mtd->erasesize;

		old_page += ppb;

		if ( elen<len && !(old_page & this->pagemask)) {
			old_page &= this->pagemask;
			chipnr++;
			this->active_chip = chipnr;
			this->select_chip(mtd, chipnr);
		}

		block = old_page/ppb;
	}
	instr->state = MTD_ERASE_DONE;

	return rc;
}


static void nand_sync (struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	this->state = RTK_FL_READY;
}


static int nand_suspend (struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	this->suspend(mtd);
	return 0;
}


static void nand_resume (struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	this->resume(mtd);
}


static void nand_select_chip(struct mtd_info *mtd, int chip)
{
	switch(chip) {
		case -1:
			REG_WRITE_U32(REG_PD,0xff);
			break;
		case 0:
		case 1:
		case 2:
		case 3:
			REG_WRITE_U32(REG_PD, ~(1 << chip));
			break;
		default:
			REG_WRITE_U32(REG_PD, ~(1 << 0));
	}
}


static int scan_last_die_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page = 0;
	__u32 addr;
	int block_num = this->block_num;
	int block_size = 1 << this->phys_erase_shift;
	int table_index=0;
	int remap_block[RBA];
	int remap_count = 0;
	int i, j;
	int numchips = this->numchips;
	int chip_size = this->chipsize;
	int rc = 0;
	__u8 *block_status = NULL;

	start_page = 0x00000000;			//bootcode: bb search from block 0
	this->active_chip = numchips-1;
	this->select_chip(mtd, numchips-1);

	block_status = kmalloc( block_num, GFP_KERNEL );
	if ( !block_status ){
		printk("%s: Error, no enough memory for block_status\n",__FUNCTION__);
		rc = -ENOMEM;
		goto EXIT;
	}
	memset ( (__u32 *)block_status, 0, block_num );
	for( addr=start_page; addr<chip_size; addr+=block_size ){
		if ( rtk_block_isbad(mtd, numchips-1, addr) ){
			int bb = addr >> this->phys_erase_shift;
			block_status[bb] = 0xff;
		}
	}

	for ( i=0; i<RBA; i++){
		if ( block_status[(block_num-1)-i] == 0x00){
			remap_block[remap_count] = (block_num-1)-i;
			remap_count++;
		}
	}

	if (remap_count<RBA+1){
		for (j=remap_count+1; j<RBA+1; j++)
			remap_block[j-1] = RB_INIT;
	}

	for ( i=0; i<(block_num-RBA); i++){
		if (block_status[i] == 0xff){
			this->bbt[table_index].bad_block = i;
			this->bbt[table_index].BB_die = numchips-1;
			this->bbt[table_index].remap_block = remap_block[table_index];
			this->bbt[table_index].RB_die = numchips-1;
			table_index++;
		}
	}

	for( i=table_index; table_index<RBA; table_index++){
		this->bbt[table_index].bad_block = BB_INIT;
		this->bbt[table_index].BB_die = BB_DIE_INIT;
		this->bbt[table_index].remap_block = remap_block[table_index];
		this->bbt[table_index].RB_die = numchips-1;
	}

	kfree(block_status);

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);

EXIT:
	if (rc){
		if (block_status)
			kfree(block_status);
	}

	return 0;
}


static int scan_other_die_BB(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page;
	__u32 addr;
	int block_size = 1 << this->phys_erase_shift;
	int j, k;
	int numchips = this->numchips;
	int chip_size = this->chipsize;

	for( k=0; k<numchips-1; k++ ){
		this->active_chip = k;
		this->select_chip(mtd, k);
		
		start_page = 0x00000000;		//bootcode: bb search from block 0
		
		for( addr=start_page; addr<chip_size; addr+=block_size ){
			if ( rtk_block_isbad(mtd, k, addr) ){
				for( j=0; j<RBA; j++){
					if ( this->bbt[j].bad_block == BB_INIT && this->bbt[j].remap_block != RB_INIT){
						this->bbt[j].bad_block = addr >> this->phys_erase_shift;
						this->bbt[j].BB_die = k;
						this->bbt[j].RB_die = numchips-1;
						break;
					}
				}
			}
		}
	}

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);

	return 0;
}

static int rtk_create_bbt(struct mtd_info *mtd, int page)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;

	int rc = 0;
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter=0;
	if(page==ppb)
		printk("[%s] nand driver creates B1 !!\n", __FUNCTION__);
	else if(page==(ppb<<1))
		printk("[%s] nand driver creates B2 !!\n", __FUNCTION__);

	if ( scan_last_die_BB(mtd) ){
		printk("[%s] scan_last_die_BB() error !!\n", __FUNCTION__);
		return -1;
	}

	if ( this->numchips >1 ){
		if ( scan_other_die_BB(mtd) ){
			printk("[%s] scan_last_die() error !!\n", __FUNCTION__);
			return -1;
		}
	}

	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	printf("[%s][%d]mem_page_num =%d\n",__FUNCTION__,__LINE__,mem_page_num);
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_BBT, 0xff, mem_page_num*page_size);

	this->select_chip(mtd, 0);

	if ( this->erase_block(mtd, 0, page) ){
		printk("[%s]erase block %d failure !!\n", __FUNCTION__, page/ppb);
		rc =  -1;
		goto EXIT;
	}

	this->g_oobbuf[0] = BBT_TAG;

	memcpy( temp_BBT, this->bbt, sizeof(BB_t)*RBA );
	//dump_BBT(mtd);		//test
	while( mem_page_num>0 ){
		if ( this->write_ecc_page(mtd, 0, page+page_counter, temp_BBT+page_counter*page_size,
			this->g_oobbuf, 1) ){
				printk("[%s] write BBT B%d page %d failure!!\n", __FUNCTION__,
					page ==0?0:1, page+page_counter);
				rc =  -1;
				goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}

EXIT:
	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}

static int rtk_update_bbt (struct mtd_info *mtd, __u8 *data_buf, __u8 *oob_buf, BB_t *bbt)
{
	int rc = 0;
	struct nand_chip *this = mtd->priv;
	unsigned char active_chip = this->active_chip;
	u8 *temp_BBT = 0;

	oob_buf[0] = BBT_TAG;

	this->select_chip(mtd, 0);

	if ( sizeof(BB_t)*RBA <= page_size){
		memcpy( data_buf, bbt, sizeof(BB_t)*RBA );
	}else{
		temp_BBT = kmalloc( 2*page_size, GFP_KERNEL );
		if ( !(temp_BBT) ){
			printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
			return -ENOMEM;
		}
		memset(temp_BBT, 0xff, 2*page_size);
		memcpy(temp_BBT, bbt, sizeof(BB_t)*RBA );
		memcpy(data_buf, temp_BBT, page_size);
	}

	if ( this->erase_block(mtd, 0, ppb) ){
		printk("[%s]error: erase block 1 failure\n", __FUNCTION__);
	}

	if ( this->write_ecc_page(mtd, 0, ppb, data_buf, oob_buf, 1) ){
		printk("[%s]update BBT B1 page 0 failure\n", __FUNCTION__);
	}else{
		if ( sizeof(BB_t)*RBA > page_size){
			memset(data_buf, 0xff, page_size);
			memcpy( data_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, ppb+1, data_buf, oob_buf, 1) ){
				printk("[%s]update BBT B1 page 1 failure\n", __FUNCTION__);
			}
			memcpy(data_buf, temp_BBT, page_size);//add by alexchang 0906-2010
		}
	}
	//-----------------------------------------------------------------------
	if ( this->erase_block(mtd, 0, ppb<<1) ){
		printk("[%s]error: erase block 1 failure\n", __FUNCTION__);
		return -1;
	}

	if ( this->write_ecc_page(mtd, 0, ppb<<1, data_buf, oob_buf, 1) ){
		printk("[%s]update BBT B2 failure\n", __FUNCTION__);
		return -1;
	}else{
		if ( sizeof(BB_t)*RBA > page_size){
			memset(data_buf, 0xff, page_size);
			memcpy( data_buf, temp_BBT+page_size, sizeof(BB_t)*RBA - page_size );
			if ( this->write_ecc_page(mtd, 0, 2*ppb+1, data_buf, oob_buf, 1) ){
				printk("[%s]error: erase block 2 failure\n", __FUNCTION__);
				return -1;
			}
		}
	}

	this->select_chip(mtd, active_chip);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}

#ifdef CONFIG_MTD_NAND_IBT
static int rtk_init_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	__u32 start_page = 0;
	__u32 addr;
	int block_num = this->block_num;
	int block_size = 1 << this->phys_erase_shift;
	int table_index=0;
	int remap_block[RBA];
	int remap_count = 0;
	int i, j;
	int numchips = this->numchips;
	int chip_size = this->chipsize;
	int rc = 0;
	__u8 *block_status = NULL;

	start_page = chip_size - block_size*RBA;
	this->active_chip = numchips-1;
	this->select_chip(mtd, numchips-1);

	block_status = kmalloc( block_num, GFP_KERNEL );
	if ( !block_status ){
		printk("%s: Error, no enough memory for block_status\n",__FUNCTION__);
		rc = -ENOMEM;
		goto EXIT;
	}
	memset ( (__u32 *)block_status, 0, block_num );
	//just scan remap area
	for( addr=start_page; addr<chip_size; addr+=block_size ){
		if ( rtk_block_isbad(mtd, numchips-1, addr) ){
			int bb = addr >> this->phys_erase_shift;
			block_status[bb] = 0xff;
		}
	}

	for ( i=0; i<RBA; i++){
		if ( block_status[(block_num-1)-i] == 0x00){
			remap_block[remap_count] = (block_num-1)-i;
			remap_count++;
		}
	}

	if (remap_count<RBA+1){
		for (j=remap_count+1; j<RBA+1; j++)
			remap_block[j-1] = RB_INIT;
	}

	for( i=table_index; table_index<RBA; table_index++){
		this->bbt[table_index].bad_block = BB_INIT;
		this->bbt[table_index].BB_die = BB_DIE_INIT;
		this->bbt[table_index].remap_block = remap_block[table_index];
		this->bbt[table_index].RB_die = numchips-1;
	}

	kfree(block_status);

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);

EXIT:
	if (rc){
		if (block_status)
			kfree(block_status);
	}

	return 0;
}

static int rtk_create_init_bbt(struct mtd_info *mtd, int page)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;

	int rc = 0;
	u8 *temp_BBT = 0;
	u8 mem_page_num, page_counter=0;
	unsigned int i=0; 
	
	if(page==ppb)
		printk("[%s] nand driver init BBT !!\n", __FUNCTION__);
	else if(page==(ppb<<1))
		printk("[%s] nand driver init BBT BAK !!\n", __FUNCTION__);

	if ( rtk_init_bbt(mtd) ){
		printk("[%s] scan_last_die_BB() error !!\n", __FUNCTION__);
		return -1;
	}
	
	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	printf("[%s][%d]mem_page_num =%d\n",__FUNCTION__,__LINE__,mem_page_num);
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_BBT, 0xff, mem_page_num*page_size);

	this->select_chip(mtd, 0);

	if ( this->erase_block(mtd, 0, page) ){
		printk("[%s]erase block %d failure !!\n", __FUNCTION__, page/ppb);
		rc =  -1;
		goto EXIT;
	}

	this->g_oobbuf[0] = BBT_TAG;

	memcpy( temp_BBT, this->bbt, sizeof(BB_t)*RBA );
	//dump_BBT(mtd);		//test
	while( mem_page_num>0 ){
		if ( this->write_ecc_page(mtd, 0, page+page_counter, temp_BBT+page_counter*page_size,
			this->g_oobbuf, 1) ){
				printk("[%s] write BBT B%d page %d failure!!\n", __FUNCTION__,
					page ==0?0:1, page+page_counter);
				rc =  -1;
				goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}

EXIT:
	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}

#endif

#ifdef CONFIG_MTD_NAND_IBT
 static int rtk_block_isbad_ibt(struct mtd_info *mtd, u16 chipnr, loff_t ofs)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int page, block, page_offset;
	unsigned char block_status_p1;
	int ret;
	//unsigned char buf[oob_size] __attribute__((__aligned__(4)));

	this->active_chip=chipnr=0;
	page = ((int) ofs) >> this->page_shift;
	page_offset = page & (ppb-1);
	block = page/ppb;

	memset(this->g_oobbuf, 0xff, oob_size);
	ret = this->read_oob_ibt(mtd, chipnr, page, oob_size, this->g_oobbuf);

	if(DATA_ALL_ONE == ret)
		return BLANK_BLOCK;

	if(ret == -1)
	{
		printk ("%s: read_oob page=%d failed\n", __FUNCTION__, page);
		return BAD_BLOCK;
	}

	block_status_p1 = this->g_oobbuf[0];

	if(block == 0x0){
		if (( block_status_p1 != BLOCK_CLEAN)&&(block_status_p1 != BLOCK_OTHER_DATA)){
			printf("Profile area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  BAD_BLOCK;		//error block tag, bad block
		}
	}else if((block == BBT_BLOCK_ADDR)||(block == BBT_BAK_BLOCK_ADDR) ){
		if (( block_status_p1 != BLOCK_CLEAN)&&(block_status_p1 != BLOCK_BBT)){
			printf("BBT area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  BAD_BLOCK;		//error block tag, bad block
		}

	}else if((block == IBT_BLOCK_ADDR)||(block == IBT_BAK_BLOCK_ADDR)){

		if (( block_status_p1 != BLOCK_CLEAN)&&(block_status_p1 != BLOCK_IBT)){
			printf("IBT area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  BAD_BLOCK;		//error block tag, bad block
		}

	}else if(block < SYS_PARAM_BOOTCODE_SIZE/mtd->erasesize){

		if (( block_status_p1 != BLOCK_CLEAN)&&(block_status_p1 != BLOCK_HWSETTING)&&(block_status_p1 != BLOCK_KEY_SIG)&&  \
		(block_status_p1 != BLOCK_OTHER_DATA)&&(block_status_p1 != BLOCK_BOOTCODE)&& (block_status_p1 != BLOCK_KBOOT)&& \
		(block_status_p1 != BLOCK_DATA)&&(block_status_p1 != BLOCK_ENVPARAM_MAGICNO)&&(block_status_p1 != BLOCK_EMCU)){
		
			printf("Bootcode Area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  BAD_BLOCK;		//error block tag, bad block
		}
	}else if((block >= SYS_PARAM_BOOTCODE_SIZE /mtd->erasesize ) && (block < (SYS_PARAM_SECURE_STORE_START+SYS_PARAM_SECURE_STORE_SIZE)/mtd->erasesize)){

		if(block_status_p1 != BLOCK_CLEAN){
			printf("Secure-store Area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  BAD_BLOCK;		//error block tag, bad block
		}

	}else if((block >= (SYS_PARAM_SECURE_STORE_START+SYS_PARAM_SECURE_STORE_SIZE)/mtd->erasesize) && (block < SYS_PARAM_FW_TABLE_START/mtd->erasesize)){

		if((block_status_p1 != BLOCK_CLEAN)&&(block_status_p1 != BLOCK_FACTORY_SETTING)){
			printf("Factory/Factory-ro Area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  BAD_BLOCK;		//error block tag, bad block
		}

	}else{
		if(block_status_p1 != BLOCK_CLEAN){
			printf("Linux Area: block tag error!!! block_status_p1 = [0x%x], block_no = [0x%x]\n",block_status_p1,block);
			return  BAD_BLOCK;		//error block tag, bad block
		}
	}

	return GOOD_BLOCK;
}

static void rtk_secure_store_info_init(secure_store_info* ss_info)
{
	ss_info->secure_store_saddr = SYS_PARAM_SECURE_STORE_START;
	ss_info->secure_store_len = SYS_PARAM_SECURE_STORE_SIZE;
	ss_info->secure_store_block_size= DEFAULT_SECURE_STORE_BLOCK_SIZE;

	ss_info->secure_store_rw_saddr = ss_info->secure_store_saddr;
	ss_info->secure_store_rw_len = ss_info->secure_store_len - ss_info->secure_store_block_size;

	ss_info->secure_store_ro_saddr = ss_info->secure_store_rw_saddr + ss_info->secure_store_rw_len;
	ss_info->secure_store_ro_len = ss_info->secure_store_block_size;

	printf("secure_store_saddr = 0x%x\n",ss_info->secure_store_saddr);
	printf("secure_store_len = 0x%x\n",ss_info->secure_store_len);
	printf("secure_store_block_size = 0x%x\n",ss_info->secure_store_block_size);
	printf("secure_store_rw_saddr = 0x%x\n",ss_info->secure_store_rw_saddr);
	printf("secure_store_rw_len = 0x%x\n",ss_info->secure_store_rw_len);
	printf("secure_store_ro_saddr = 0x%x\n",ss_info->secure_store_ro_saddr);
	printf("secure_store_ro_len = 0x%x\n",ss_info->secure_store_ro_len);

	return;
}

unsigned int Sstore_tar_crc(char* tar_path , unsigned int len) 
{
	unsigned int ret_crc32 = 0;
	
	// check checksum;
	if (nand_crc32(tar_path, len, &ret_crc32) != 0) {
		printf("crc32 calculation failed!\n");
	} 

	printf("tail header crc  = %u\n", ret_crc32);
	return ret_crc32;

}


unsigned int Sstore_tar_checksum(char *header ) {

	unsigned char *data = (unsigned char *) header;
	unsigned int sum;
	int i;
        // check checksum;
        sum=0;
        for (i=0;i<148;i++) sum+=data[i];

        for (i=156;i<512;i++) sum+=data[i];

        for (i=0; i<8; i++) sum += 32;

	 printf("check_sum = %06o\n", sum);
	 return sum;
}

void Sstore_tar_fill_checksum(char *cheader ) {
	ss_posix_header* header = (ss_posix_header*) cheader;	
	sprintf(header->chksum, "%06o", Sstore_tar_checksum(cheader));

	header->chksum[6] = 0;
	header->chksum[7] = 0x20;
	printf("fill header checksun  = %s\n", header->chksum);
}

static int rtk_secure_store_write_back(struct mtd_info *mtd, u16 chipnr, unsigned int rw_start,unsigned int limit_len, unsigned int seq_no, unsigned int ro_spage, unsigned int ro_epage)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int i=0;
	unsigned int rw_sblock = rw_start/mtd->erasesize;
	unsigned int rw_eblock = rw_sblock + limit_len/mtd->erasesize;
	int rc=0;
	unsigned int read_len=0;
	unsigned int write_len=0;
	unsigned int data_len=0;
	unsigned int ro_current_page = 0;
	unsigned int ro_current_block = 0;
	unsigned int rw_current_page = 0;
	unsigned int rw_current_block = 0;
	unsigned char tar_size= 0;
	unsigned char *p_buf_tarsize = NULL;
	ss_posix_header_bk *p_tail =NULL;
	ss_posix_header *p_header =NULL;

	p_buf_tarsize = (unsigned char *)malloc(g_ss_tarsize);
	if(p_buf_tarsize == NULL){
		printf("[%s][%d]Malloc buffer failed!\n", __FUNCTION__,__LINE__);
		return -1;
	}else{
		memset(p_buf_tarsize, 0xff, g_ss_tarsize);
	}

	//erase 
	for(i=rw_sblock; i<rw_eblock; i++){
		rc = this->erase_block(mtd, chipnr, i*ppb);
		if ( rc<0 ){
			this->g_oobbuf[0] = 0x00;
			if ( isLastPage ){
				this->write_oob(mtd, chipnr, i*ppb+ppb-1, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, i*ppb+ppb-2, oob_size, this->g_oobbuf);
			}else{
				this->write_oob(mtd, chipnr, i*ppb, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, i*ppb+1, oob_size, this->g_oobbuf);
			}
		}
	}

	//printf("rw_start = 0x%x\n",rw_start);
	//printf("limit_len = 0x%x\n",limit_len);
	//printf("ro_spage = 0x%x\n",ro_spage);
	//printf("ro_epage = 0x%x\n",ro_epage);
	//init value
	ro_current_page = ro_spage;
	ro_current_block = ro_current_page/ppb;
	
	data_len = (ro_epage-ro_spage)*mtd->oobblock;
	read_len = 0;
	//printf("ro_current_page = 0x%x\n",ro_current_page);
	//printf("ro_current_block = 0x%x\n",ro_current_block);
	//printf("rw_current_page = 0x%x\n",rw_current_page);
	//printf("rw_current_block = 0x%x\n",rw_current_block);
	//printf("read_len = 0x%x\n",read_len);

	while(read_len < data_len){
		//read data from ro_area
		rc = rtk_block_isbad_ibt(mtd, chipnr, ro_current_block*mtd->erasesize);
		if(rc == BAD_BLOCK){
			//read_len -= mtd->erasesize;
			if(ro_current_block == ro_spage/ppb){
				printf("[%s][%d]Get secure store RO-area header failed!\n", __FUNCTION__,__LINE__);
				free(p_buf_tarsize);
				return -1;
			}else{
				ro_current_page += ppb;
				ro_current_block =ro_current_page/ppb;
				continue;
			}
		}

		//printf("ro_current_page = 0x%x\n",ro_current_page);
		rc = this->read_ecc_page(mtd, chipnr, ro_current_page, &p_buf_tarsize[read_len], NULL);
		if(rc == -1){
			//update block tag
			this->g_oobbuf[0] = 0x00;
			if ( isLastPage ){
				this->write_oob(mtd, chipnr, ro_current_block*ppb+ppb-1, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, ro_current_block*ppb+ppb-2, oob_size, this->g_oobbuf);
			}else{
				this->write_oob(mtd, chipnr, ro_current_block*ppb, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, ro_current_block*ppb+1, oob_size, this->g_oobbuf);
			}
			printf("[Warning][%d] Update secure_store data to secure_store rw area failed!\n",__LINE__);
			free(p_buf_tarsize);
			return -1;
		}

		read_len += mtd->oobblock;
		ro_current_page++;
		ro_current_block = rw_current_page/ppb;
	}

	//process ss header & tail
	p_tail = (ss_posix_header_bk *)malloc(sizeof(ss_posix_header_bk));
	if(p_tail == NULL){
		printf("[%s][%d]Malloc buffer failed!\n", __FUNCTION__,__LINE__);
		free(p_buf_tarsize);
		return -1;
	}else{
		memset(p_tail, 0xff, sizeof(ss_posix_header_bk));
	}
	
	p_header = (ss_posix_header *)malloc(sizeof(ss_posix_header));
	if(p_header == NULL){
		printf("[%s][%d]Malloc buffer failed!\n", __FUNCTION__,__LINE__);
		free(p_buf_tarsize);
		free(p_tail);
		return -1;
	}else{
		//memset(p_header, 0xff, sizeof(ss_posix_header));
		memcpy(p_header, p_buf_tarsize, sizeof(ss_posix_header));
		memcpy(p_tail, &p_buf_tarsize[p_header->rtk_tarsize], sizeof(ss_posix_header_bk));
		p_header->rtk_seqnum = seq_no;
		Sstore_tar_fill_checksum((char *)p_header);
		p_tail->rtk_filecrc32 = Sstore_tar_crc((char *)p_buf_tarsize, p_header->rtk_tarsize);
		memcpy(p_tail, p_header, 500);
	}
	//write back header & tail
	memcpy(p_buf_tarsize , p_header, sizeof(ss_posix_header));
	memcpy(&p_buf_tarsize[p_header->rtk_tarsize], p_tail,sizeof(ss_posix_header_bk));

	free(p_header);
	free(p_tail);
	
	//write back
	rw_current_page = rw_start/mtd->oobblock;
	rw_current_block =rw_current_page/ppb;
	
	while(write_len < data_len){
		rc = rtk_block_isbad_ibt(mtd, chipnr, rw_current_block*mtd->erasesize);
		if(rc == BAD_BLOCK){
			rw_current_page += ppb;
			rw_current_block =rw_current_page/ppb;
			if(rw_current_block >= rw_eblock){
				printf("[Warning][%d] Update secure_store data to secure_store rw area failed!\n",__LINE__);
				return -1;
			}
		}

		//printf("rw_current_page = 0x%x\n",rw_current_page);
		memset(this->g_oobbuf, 0xff , mtd->oobsize);
		rc = this->write_ecc_page(mtd, chipnr, rw_current_page, &p_buf_tarsize[write_len], this->g_oobbuf, 0);
		if(rc == -1){
			//update block tag
			this->g_oobbuf[0] = 0x00;
			if ( isLastPage ){
				this->write_oob(mtd, chipnr, rw_current_block*ppb+ppb-1, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, rw_current_block*ppb+ppb-2, oob_size, this->g_oobbuf);
			}else{
				this->write_oob(mtd, chipnr, rw_current_block*ppb, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, rw_current_block*ppb+1, oob_size, this->g_oobbuf);
			}
			//update read_len
			write_len -= (rw_current_page%ppb)*mtd->oobblock;
			//update rw info 
			rw_current_page = rw_current_page - rw_current_page%ppb +ppb;		//next block
			rw_current_block =rw_current_page/ppb;

			if(rw_current_block >= rw_eblock){
				printf("[Warning][%d] Update secure_store data to secure_store rw area failed!\n",__LINE__);
				return -1;
			}
			continue;
		}else{
			rw_current_page++;
			rw_current_block = rw_current_page/ppb;

			write_len += mtd->oobblock;
		}
	}
	free(p_buf_tarsize);
	return 0;
}

static int rtk_secure_store_ro_data_check(struct mtd_info *mtd, u16 chipnr, secure_store_info *ss_info)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned int ss_ro_bstart = ss_info->secure_store_ro_saddr/mtd->erasesize;
	unsigned int ss_ro_bnum = ss_info->secure_store_ro_len/mtd->erasesize;
	unsigned int i=0;
	int res=0;
	ss_posix_header *p_header =NULL;
	
	p_header = (ss_posix_header *)malloc(mtd->oobblock);
	if(p_header == NULL){
		printf("[%s][%d]Malloc buffer failed!\n", __FUNCTION__,__LINE__);
		return -1;
	}else{
		memset(p_header, 0xff, mtd->oobblock);
	}

	//read secure store header
	for(i=ss_ro_bstart; i<(ss_ro_bstart+ss_ro_bnum); i++){
		res = rtk_block_isbad_ibt(mtd, chipnr, i*mtd->erasesize);
		if(res == GOOD_BLOCK){
			//read secure store header
			res = this->read_ecc_page(mtd, chipnr, i*ppb, p_header, NULL);
			if(res  == -1){
				//update block tag
				this->g_oobbuf[0] = 0x00;
				if ( isLastPage ){
					this->write_oob(mtd, chipnr, i*ppb+ppb-1, oob_size, this->g_oobbuf);
					this->write_oob(mtd, chipnr, i*ppb+ppb-2, oob_size, this->g_oobbuf);
				}else{
					this->write_oob(mtd, chipnr, i*ppb, oob_size, this->g_oobbuf);
					this->write_oob(mtd, chipnr, i*ppb+1, oob_size, this->g_oobbuf);
				}
				printf("[Warning][%d] Check secure_store data failed!\n",__LINE__);
				return -1;
			}else{
				//read success
				g_ro_start = i*mtd->erasesize;
				break;
			}
		}
	}

	//secure store header check
	if(p_header->rtk_tarsize > (ss_info->secure_store_block_size-DEFAULT_SECURE_STORE_BLOCK_RES_LEN)){
		printf("[Warning][%d] Check secure_store header failed!\n",__LINE__);
		return -1;
	}
	if(p_header->rtk_tarsize < (sizeof(ss_posix_header))*2){
		printf("[Warning][%d] Check secure_store header failed!\n",__LINE__);
		return -1;
	}
	if(strcmp(p_header->rtk_signature,"RTK")){
		printf("[Warning][%d] Check secure_store header failed!\n",__LINE__);
		return -1;
	}
	if(p_header->rtk_seqnum != 0){
		printf("[Warning][%d] Check secure_store header failed!\n",__LINE__);
		return -1;
	}

	//page align
	g_ss_tarsize = (((p_header->rtk_tarsize + sizeof(ss_posix_header_bk)) + mtd->oobblock -1)/mtd->oobblock)*mtd->oobblock;

	return 0;
	
}

static int rtk_secure_store_init(struct mtd_info *mtd, u16 chipnr)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	secure_store_info ss_info;
	unsigned int ss_rw_block_num;
	unsigned int ss_ro_data_epage;
	unsigned int ss_ro_data_eblock;
	unsigned int ss_ro_data_spage;
	int i=0;
	unsigned int rw_start;
	int rc;

	rtk_secure_store_info_init(&ss_info);
	ss_rw_block_num = ss_info.secure_store_rw_len/ss_info.secure_store_block_size;
	//sanity check
	if(ss_info.secure_store_rw_len%ss_info.secure_store_block_size){
		printf("[Warning]Secure store RW-area size or Secure store block size error !\n");
		return -1;
	}
	
	//printf("ss_rw_block_num = 0x%x\n",ss_rw_block_num);
	rc = rtk_secure_store_ro_data_check(mtd, chipnr, &ss_info);
	if(rc == -1){
		printf("[Warning][%d] Check secure_store data failed!\n",__LINE__);
		return -1;
	}

	if((g_ro_start == 0) ||(g_ss_tarsize == 0)||(g_ro_start < ss_info.secure_store_ro_saddr)){
		printf("[Warning][%d] Get param failed!\n",__LINE__);
		return -1;
	}
	
	ss_ro_data_spage = g_ro_start/mtd->oobblock;
	ss_ro_data_epage = ss_ro_data_spage+ g_ss_tarsize/mtd->oobblock;
	
	printf("ss_ro_data_spage = 0x%x ss_ro_data_epage = 0x%x \n",ss_ro_data_spage, ss_ro_data_epage);
	
	for(i = 0; i<ss_rw_block_num; i++){
		rw_start = ss_info.secure_store_rw_saddr + i*ss_info.secure_store_block_size;
		rc = rtk_secure_store_write_back(mtd,chipnr,rw_start, ss_info.secure_store_block_size, i, ss_ro_data_spage,ss_ro_data_epage);
		if(rc == 0){
			printf("Init secure store block 0x%x Success!!!\n",i);
		}else{
			printf("Init secure store block 0x%x Failed!!!\n",i);
		}
	}
	
	return 0;
}

static int rtk_create_ibt_pre(struct mtd_info *mtd, unsigned int start_addr, unsigned int end_addr, unsigned int scan_end_addr)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int block_size = 1 << this->phys_erase_shift;
	int numchips = this->numchips;
	
	unsigned int i=0, j=0;
	int ret=0;
	unsigned int current_dst_block = start_addr;
	unsigned int temp_current_block;
	
	printf("IBT start addr : %d   IBT end addr: %d  IBT scan end addr : %d\n", start_addr,end_addr,scan_end_addr);
	
	for (i = start_addr; i < end_addr; i++)
   	{
   		int ret_val;
		unsigned int addr=i*block_size;
		
		ret_val = rtk_block_isbad_ibt(mtd, numchips-1, addr);
		switch (ret_val) {
			case GOOD_BLOCK:
			case BLANK_BLOCK:
				this->ibt[i].src_block = i;
				
				if(current_dst_block == i){
					this->ibt[i].dst_block = current_dst_block;
					current_dst_block ++;
				}
				else{
					for(j = current_dst_block; j< scan_end_addr; j++)
					{
						__u32 ofs;
						int ret;
						ofs = j*block_size;
						ret = rtk_block_isbad_ibt(mtd, numchips-1, ofs);
						if(ret == BAD_BLOCK)
							continue;
						else{
							current_dst_block = j;
							break;
							}
					}
					this->ibt[i].dst_block = current_dst_block;
					current_dst_block ++;
				}
				break;
					
      			case BAD_BLOCK:
         			//updata ibt
         			this->ibt[i].src_block = i;
				if(current_dst_block == i){
					temp_current_block = current_dst_block+1;
				}else{
					temp_current_block =current_dst_block;
				}
				for(j = temp_current_block ; j< scan_end_addr; j++)
				{
					__u32 ofs;
					int ret;
					ofs = j*block_size;
					ret = rtk_block_isbad_ibt(mtd, numchips-1, ofs);
					if(ret == BAD_BLOCK){
						continue;
					}else{
						current_dst_block = j;
						break;
					}
				}
				this->ibt[i].dst_block = current_dst_block;
				current_dst_block ++;
				
        			 break;
		
      			default:
         			//impossible;
         			return -1;
   		}
	}

	return ret;
}

static int scan_last_die_ibt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int block_num = this->block_num;
	int block_size = 1 << this->phys_erase_shift;
	int i, j;
	int numchips = this->numchips;
	int rc = 0;
	unsigned int ibt_start, ibt_end, ibt_scan_end;

	IBT_LEN = block_num;
	this->active_chip = numchips-1;
	this->select_chip(mtd, numchips-1);

	//init ibt
	for (i = 0 ; i < IBT_LEN; i++)
   	{
   		this->ibt[i].src_die = SRC_DIE_INIT;
		this->ibt[i].src_block = SRC_INIT;
      		this->ibt[i].dst_die = DST_DIE_INIT;
      		this->ibt[i].dst_block = DST_INIT;
   	}

	//create ibt for bootcode-area
	printf("Starting create bootcode area IBT\n");
	ibt_start = IBT_SCAN_START_BLOCK;
	ibt_end = SYS_PARAM_BOOTCODE_SIZE/block_size -this->I_BOOTCODE_RBA;	//bootcode-area not include factory-ro
	ibt_scan_end = SYS_PARAM_BOOTCODE_SIZE/block_size;
	rtk_create_ibt_pre(mtd, ibt_start, ibt_end, ibt_scan_end);

	//create ibt for kernel-area
	printf("Starting create kernel area IBT\n");
	ibt_start = SYS_PARAM_FACTORY_START/block_size;	//kernel-area include factory-ro / factory /kernel
	ibt_end =block_num -RBA -this->I_KERNEL_RBA;	//reserved remap area
	ibt_scan_end = block_num -RBA;
	rtk_create_ibt_pre(mtd, ibt_start, ibt_end, ibt_scan_end);
	
	return 0;

}

static int rtk_create_ibt(struct mtd_info *mtd, int page)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;

	unsigned int ibt_page_no,ibt_bak_page_no;
	
	int rc = 0;
	u8 *temp_IBT = 0;
	u8 mem_page_num, page_counter=0;
	
	ibt_page_no = IBT_BLOCK_ADDR*ppb;
	ibt_bak_page_no = IBT_BAK_BLOCK_ADDR*ppb;
	
	if(page==ibt_page_no)
		printk("[%s] nand driver creates IBT !!\n", __FUNCTION__);
	else if(page==ibt_bak_page_no)
		printk("[%s] nand driver creates IBT_BAK !!\n", __FUNCTION__);

//-----------------------------------------------
	if ( scan_last_die_ibt(mtd) ){
		printk("[%s] scan_last_die_BB() error !!\n", __FUNCTION__);
		return -1;
	}
#if 0
	if ( this->numchips >1 ){
		if ( scan_other_die_BB(mtd) ){
			printk("[%s] scan_last_die() error !!\n", __FUNCTION__);
			return -1;
		}
	}
#endif
//--------------------------------------------------

	mem_page_num = (sizeof(IB_t)*IBT_LEN + page_size-1 )/page_size;
	printf("[%s][%d]mem_page_num =%d\n",__FUNCTION__,__LINE__,mem_page_num);
	
	temp_IBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_IBT ){
		printk("%s: Error, no enough memory for temp_IBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_IBT, 0xff, mem_page_num*page_size);

	this->select_chip(mtd, 0);

	if ( this->erase_block(mtd, 0, page) ){
		printk("[%s]erase block %d failure !!\n", __FUNCTION__, page/ppb);
		rc =  -1;
		goto EXIT;
	}

	this->g_oobbuf[0] = IBT_TAG;

	memcpy( temp_IBT, this->ibt, sizeof(IB_t)*IBT_LEN );
	//dump_BBT(mtd);		//test
	while( mem_page_num>0 ){
		if ( this->write_ecc_page(mtd, 0, page+page_counter, temp_IBT+page_counter*page_size,
			this->g_oobbuf, 1) ){
				printk("[%s] write IBT B%d page %d failure!!\n", __FUNCTION__,
					page ==0?0:1, page+page_counter);
				rc =  -1;
				goto EXIT;
		}
		page_counter++;
		mem_page_num--;
	}

EXIT:
	if (temp_IBT)
		kfree(temp_IBT);

	return rc;


}

static int rtk_nand_scan_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	__u8 isbbt_b1, isbbt_b2;
	u8 *temp_BBT=0;
	u8 mem_page_num, page_counter=0;
	unsigned int ibt_page_no,ibt_bak_page_no;

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);
	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	
	memset( temp_BBT, 0xff, mem_page_num*page_size);
	rc = this->read_ecc_page(mtd, 0, ppb, this->g_databuf, this->g_oobbuf);

	isbbt_b1 = this->g_oobbuf[0];
	if ( !rc ){
		if ( isbbt_b1 == BBT_TAG ){
			printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
			memcpy( temp_BBT, this->g_databuf, page_size );
			page_counter++;
			mem_page_num--;

			while( mem_page_num>0 ){
				if ( this->read_ecc_page(mtd, 0, ppb+page_counter, this->g_databuf, this->g_oobbuf) ){
					printk("[%s] load bbt B1 error!!\n", __FUNCTION__);
					kfree(temp_BBT);
					return -1;
				}
				memcpy( temp_BBT+page_counter*page_size, this->g_databuf, page_size );
				page_counter++;
				mem_page_num--;
			}
			memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );

			if(this->use_ibt)
				goto ibt_exist_bbt_exist;
			else
				goto ibt_fail_bbt_exist;
			
		}
		else{
			printk("[%s] read BBT B1 tags fails, try to load BBT B2\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, 0, ppb<<1, this->g_databuf, this->g_oobbuf);
			isbbt_b2 = this->g_oobbuf[0];
			if ( !rc ){
				if ( isbbt_b2 == BBT_TAG ){
					printk("[%s] have created bbt B2, just loads it !!\n", __FUNCTION__);
					memcpy( temp_BBT, this->g_databuf, page_size );
					page_counter++;
					mem_page_num--;

					while( mem_page_num>0 ){
						if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->g_databuf, this->g_oobbuf) ){
							printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
							kfree(temp_BBT);
							return -1;
						}
						memcpy( temp_BBT+page_counter*page_size, this->g_databuf, page_size );
						page_counter++;
						mem_page_num--;
					}
					memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );

					if(this->use_ibt)
						goto ibt_exist_bbt_exist;
					else
						goto ibt_fail_bbt_exist;
					
				}else{
					printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B1 and B2\n", __FUNCTION__);
					
					if(this->use_ibt){
						this->bbt_err_status = BOTH_OK;
						goto ibt_exist_bbt_fail;
					}else{
						this->bbt_err_status = BOTH_OK;
						goto ibt_fail_bbt_fail;

						}
				}
			}else{
				printk("[%s] read BBT B2 with HW ECC fails, nand driver will creat BBT B1\n", __FUNCTION__);
				
				if(this->use_ibt){
					this->bbt_err_status = B2_ERR;
					goto ibt_exist_bbt_fail;
				}else{
					this->bbt_err_status = B2_ERR;
					goto ibt_fail_bbt_fail;
				}
			}
		}
	}else{
		printk("[%s] read BBT B1 with HW ECC error, try to load BBT B2\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, 0, ppb<<1, this->g_databuf, this->g_oobbuf);
		isbbt_b2 = this->g_oobbuf[0];
		if ( !rc ){
			if ( isbbt_b2 == BBT_TAG ){
				printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
				memcpy( temp_BBT, this->g_databuf, page_size );
				page_counter++;
				mem_page_num--;

				while( mem_page_num>0 ){
					if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->g_databuf, this->g_oobbuf) ){
						printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
						kfree(temp_BBT);
						return -1;
					}
					memcpy( temp_BBT+page_counter*page_size, this->g_databuf, page_size );
					page_counter++;
					mem_page_num--;
				}
				memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );

				if(this->use_ibt)
					goto ibt_exist_bbt_exist;
				else
					goto ibt_fail_bbt_exist;
			}else{
				printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B2\n", __FUNCTION__);
				
				if(this->use_ibt){
					this->bbt_err_status = B1_ERR;
					goto ibt_exist_bbt_fail;
				}else{
					this->bbt_err_status = B1_ERR;
					goto ibt_fail_bbt_fail;
				}
			}
		}else{
			printk("[%s] read BBT B1 and B2 with HW ECC fails\n", __FUNCTION__);
			this->bbt_err_status = BOTH_ERR;
			kfree(temp_BBT);
			return -1;
		}
	}

	dump_BBT(mtd);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;

ibt_exist_bbt_exist:
	printf("[OK] IBT exist , BBT exist ......\n");
	dump_BBT(mtd);
	
	if (temp_BBT)
		kfree(temp_BBT);
	return 0;

ibt_exist_bbt_fail:

	printf("[ERROR]IBT exist , BBT no-exist .....\n");
	return -1;

ibt_fail_bbt_exist:
	printf("[WARNING] IBT no-exist , BBT exist .....\n");
	dump_BBT(mtd);
	
	if (temp_BBT)
		kfree(temp_BBT);
	return 0;

ibt_fail_bbt_fail:
	printf("[OK] IBT no-exist , BBT no-exist!!!First RUN.....\n");
	ibt_page_no = IBT_BLOCK_ADDR*ppb;
	ibt_bak_page_no = IBT_BAK_BLOCK_ADDR*ppb;
	
	if(this->ibt_err_status == B1_ERR){
		rtk_create_ibt(mtd, ibt_bak_page_no);
	}else if(this->ibt_err_status == B2_ERR){
		rtk_create_ibt(mtd, ibt_page_no);
	}else if(this->ibt_err_status == BOTH_OK){
		rtk_create_ibt(mtd, ibt_page_no);
		rtk_create_ibt(mtd, ibt_bak_page_no);
	}

	this->use_ibt = 1;		//redefine use_ibt

	if(this->bbt_err_status == B1_ERR){
		rtk_create_init_bbt(mtd, ppb<<1);
	}else if(this->bbt_err_status == B2_ERR){
		rtk_create_init_bbt(mtd, ppb);
	}else if(this->bbt_err_status == BOTH_OK){
		rtk_create_init_bbt(mtd, ppb);
		rtk_create_init_bbt(mtd, ppb<<1);
	}

	dump_BBT(mtd);
	
	if (temp_BBT)
		kfree(temp_BBT);

	//init secure store
	rtk_secure_store_init(mtd, 0);
	
	return 0;
}


//ibt bbt init
static int rtk_nand_scan_ibt_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	unsigned int ibt_page_no,ibt_bak_page_no;
	__u8 isibt, isibt_bak;
	u8 *temp_IBT=0;
	u8 mem_page_num, page_counter=0;
	
	ibt_page_no = IBT_BLOCK_ADDR*ppb;
	ibt_bak_page_no = IBT_BAK_BLOCK_ADDR*ppb;

	RTK_FLUSH_CACHE((unsigned long) this->ibt, sizeof(IB_t)*IBT_LEN);
	
	mem_page_num = (sizeof(IB_t)*IBT_LEN + page_size-1 )/page_size;
	temp_IBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_IBT ){
		printf("%s: Error, no enough memory for temp_IBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset( temp_IBT, 0xff, mem_page_num*page_size);

	rc = this->read_ecc_page(mtd, 0, ibt_page_no, this->g_databuf, this->g_oobbuf);
	
	isibt = this->g_oobbuf[0];
	printk("[%s][%d]this->g_oobbuf[0] = %x\n",__FUNCTION__,__LINE__, this->g_oobbuf[0]);
	
	if ( !rc ){
		if ( isibt == IBT_TAG ){
			printf("[%s] IBT exist!!!load it...\r\n",__FUNCTION__);
			memcpy( temp_IBT, this->g_databuf, page_size );
			page_counter++;
			mem_page_num--;

			while( mem_page_num>0 ){
				if ( this->read_ecc_page(mtd, 0, ibt_page_no+page_counter, this->g_databuf, this->g_oobbuf) ){
					printk("[%s] load ibt error!!\n", __FUNCTION__);
					kfree(temp_IBT);
					return -1;
				}
				memcpy( temp_IBT+page_counter*page_size, this->g_databuf, page_size );
				page_counter++;
				mem_page_num--;
			}
			memcpy( this->ibt, temp_IBT, sizeof(IB_t)*IBT_LEN);

			goto ibt_exist;
			
		}else{
			printf("[%s] read IBT tags fails, try to load IBT_BAK...\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, 0, ibt_bak_page_no, this->g_databuf, this->g_oobbuf);
			isibt_bak = this->g_oobbuf[0];
			if(!rc){
				if ( isibt_bak == IBT_TAG ){
					printf("[%s] IBT BAK exist!!!loads it...\r\n",__FUNCTION__);
					memcpy( temp_IBT, this->g_databuf, page_size );
					page_counter++;
					mem_page_num--;

					while( mem_page_num>0 ){
						if ( this->read_ecc_page(mtd, 0, ibt_bak_page_no+page_counter, this->g_databuf, this->g_oobbuf) ){
							printk("[%s] load ibt bak error!!\n", __FUNCTION__);
							kfree(temp_IBT);
							return -1;
						}
						memcpy( temp_IBT+page_counter*page_size, this->g_databuf, page_size );
						page_counter++;
						mem_page_num--;
					}
					memcpy( this->bbt, temp_IBT, sizeof(IB_t)*IBT_LEN );
					
					goto ibt_exist;
					
				}else{
					//build ibt & bbt and bak*********
					printk("[%s] read IBT BAK tags fails...\n", __FUNCTION__);
					this->ibt_err_status = BOTH_OK;
					goto ibt_fail;
				}

			}else{
				printk("[%s] read IBT BAK with HW ECC fails...\n", __FUNCTION__);	
				//build ibt & bbt***********
				this->ibt_err_status = B2_ERR;
				goto ibt_fail;
			}
				
		}
		
	}else{
		printf("[%s] read IBT with HW ECC error, try to load IBT BAK\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, 0, ibt_bak_page_no, this->g_databuf, this->g_oobbuf);
		isibt_bak = this->g_oobbuf[0];
		
		if ( !rc ){
			if ( isibt_bak == IBT_TAG ){
				printf("[%s] IBT BAK exist!!!loads it...\r\n",__FUNCTION__);
				memcpy( temp_IBT, this->g_databuf, page_size );
				page_counter++;
				mem_page_num--;

				while( mem_page_num>0 ){
					if ( this->read_ecc_page(mtd, 0, ibt_bak_page_no+page_counter, this->g_databuf, this->g_oobbuf) ){
						printk("[%s] load ibt BAK error!!\n", __FUNCTION__);
						kfree(temp_IBT);
						return -1;
					}
					memcpy( temp_IBT+page_counter*page_size, this->g_databuf, page_size );
					page_counter++;
					mem_page_num--;
				}
				memcpy( this->bbt, temp_IBT, sizeof(IB_t)*IBT_LEN );

				//scan & load bbt
				goto ibt_exist;
				
			}else{
				printf("[%s] read IBT BAK tags fails...\n", __FUNCTION__);
				this->ibt_err_status = B1_ERR ;
				goto ibt_fail;
				
			}
		}else{
			printk("[%s] read IBT and IBT BAK with HW ECC fails...\n", __FUNCTION__);
			//goto ibt_fail;
			this->ibt_err_status = BOTH_ERR;
			kfree(temp_IBT);
			return -1;
		}

	}

	if (temp_IBT)
		kfree(temp_IBT);
	return rc;
	
ibt_exist:
	this->use_ibt = 1;
	if (temp_IBT)
		kfree(temp_IBT);
			
	//scan & load bbt
	rc = this->scan_bbt (mtd);
	return rc;

ibt_fail:
	this->use_ibt = 0;

	if (temp_IBT)
		kfree(temp_IBT);
			
	//scan & load bbt
	rc = this->scan_bbt (mtd);
	return rc;
	
}


#else
static int rtk_nand_scan_bbt(struct mtd_info *mtd)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	int rc = 0;
	__u8 isbbt_b1, isbbt_b2;
	u8 *temp_BBT=0;
	u8 mem_page_num, page_counter=0;

	RTK_FLUSH_CACHE((unsigned long) this->bbt, sizeof(BB_t)*RBA);
	mem_page_num = (sizeof(BB_t)*RBA + page_size-1 )/page_size;
	temp_BBT = kmalloc( mem_page_num*page_size, GFP_KERNEL );
	if ( !temp_BBT ){
		printk("%s: Error, no enough memory for temp_BBT\n",__FUNCTION__);
		return -ENOMEM;
	}
	
	memset( temp_BBT, 0xff, mem_page_num*page_size);
	rc = this->read_ecc_page(mtd, 0, ppb, this->g_databuf, this->g_oobbuf);

	isbbt_b1 = this->g_oobbuf[0];
	if ( !rc ){
		if ( isbbt_b1 == BBT_TAG ){
			printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
			memcpy( temp_BBT, this->g_databuf, page_size );
			page_counter++;
			mem_page_num--;

			while( mem_page_num>0 ){
				if ( this->read_ecc_page(mtd, 0, ppb+page_counter, this->g_databuf, this->g_oobbuf) ){
					printk("[%s] load bbt B1 error!!\n", __FUNCTION__);
					kfree(temp_BBT);
					return -1;
				}
				memcpy( temp_BBT+page_counter*page_size, this->g_databuf, page_size );
				page_counter++;
				mem_page_num--;
			}
			memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
		}
		else{
			printk("[%s] read BBT B1 tags fails, try to load BBT B2\n", __FUNCTION__);
			rc = this->read_ecc_page(mtd, 0, ppb<<1, this->g_databuf, this->g_oobbuf);
			isbbt_b2 = this->g_oobbuf[0];
			if ( !rc ){
				if ( isbbt_b2 == BBT_TAG ){
					printk("[%s] have created bbt B2, just loads it !!\n", __FUNCTION__);
					memcpy( temp_BBT, this->g_databuf, page_size );
					page_counter++;
					mem_page_num--;

					while( mem_page_num>0 ){
						if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->g_databuf, this->g_oobbuf) ){
							printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
							kfree(temp_BBT);
							return -1;
						}
						memcpy( temp_BBT+page_counter*page_size, this->g_databuf, page_size );
						page_counter++;
						mem_page_num--;
					}
					memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
				}else{
					printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B1 and B2\n", __FUNCTION__);
					rtk_create_bbt(mtd, ppb);
					rtk_create_bbt(mtd, ppb<<1);
				}
			}else{
				printk("[%s] read BBT B2 with HW ECC fails, nand driver will creat BBT B1\n", __FUNCTION__);
				rtk_create_bbt(mtd, ppb);
			}
		}
	}else{
		printk("[%s] read BBT B1 with HW ECC error, try to load BBT B2\n", __FUNCTION__);
		rc = this->read_ecc_page(mtd, 0, ppb<<1, this->g_databuf, this->g_oobbuf);
		isbbt_b2 = this->g_oobbuf[0];
		if ( !rc ){
			if ( isbbt_b2 == BBT_TAG ){
				printk("[%s] have created bbt B1, just loads it !!\n", __FUNCTION__);
				memcpy( temp_BBT, this->g_databuf, page_size );
				page_counter++;
				mem_page_num--;

				while( mem_page_num>0 ){
					if ( this->read_ecc_page(mtd, 0, 2*ppb+page_counter, this->g_databuf, this->g_oobbuf) ){
						printk("[%s] load bbt B2 error!!\n", __FUNCTION__);
						kfree(temp_BBT);
						return -1;
					}
					memcpy( temp_BBT+page_counter*page_size, this->g_databuf, page_size );
					page_counter++;
					mem_page_num--;
				}
				memcpy( this->bbt, temp_BBT, sizeof(BB_t)*RBA );
			}else{
				printk("[%s] read BBT B2 tags fails, nand driver will creat BBT B2\n", __FUNCTION__);
				rtk_create_bbt(mtd, ppb<<1);
			}
		}else{
			printk("[%s] read BBT B1 and B2 with HW ECC fails\n", __FUNCTION__);
			kfree(temp_BBT);
			return -1;
		}
	}

	dump_BBT(mtd);

	if (temp_BBT)
		kfree(temp_BBT);

	return rc;
}
#endif

int rtk_nand_scan(struct mtd_info *mtd, int maxchips)
{
	struct nand_chip *this = (struct nand_chip *)mtd->priv;
	unsigned char id[6];
	unsigned int device_size=0;
	unsigned int i;
	unsigned int nand_type_id ;
	int rtk_lookup_table_flag=0;
	unsigned char maker_code;
	unsigned char device_code;
	unsigned char B5th;
	unsigned char B6th;
	unsigned int block_size;
	unsigned int num_chips = 1;
	uint64_t chip_size=0;
	unsigned int num_chips_probe = 1;
	uint64_t result = 0;
	uint64_t div_res = 0;
	unsigned int flag_size, mempage_order;

	if ( !this->select_chip )
		this->select_chip = nand_select_chip;
	if ( !this->scan_bbt )
		this->scan_bbt = rtk_nand_scan_bbt;
	
	this->active_chip = 0;
	this->select_chip(mtd, 0);
	
#if 0
	if(platform_info.secure_boot)
		g_isSysSecure = 1;
#endif

#if 0
	printk("nand_base_rtk version:0824-2011\n");
        if(is_macarthur_cpu())
        {
                if((REG_READ_U32(0xb8060008)&0x01)!=1)
                {
                        printk("[%s]Doesn't support NAND boot for macathur\n",__FUNCTION__);
                        return -1;
                }
        }
#endif
	mtd->name = "rtk_nand";
	printf("[Sirius] %s\n", mtd->name);

#if 0
#if		NAND_POWEROFF_CARDREADER_WITH_MULTI_READ
	NF_rtkcr_get_gpio();
	printk("(V)NAND_POWEROFF_CARDREADER_WITH_MULTI_READ\n");
#else
	printk("(X)NAND_POWEROFF_CARDREADER_WITH_MULTI_READ\n");
#endif

#if NAND_READ_SKIP_UPDATE_BBT
		printk("(V)NAND_READ_SKIP_UPDATE_BBT\n");
#else
		printk("(X)NAND_READ_SKIP_UPDATE_BBT\n");
#endif
#endif

	while (1) {
		this->read_id(mtd, id);

		this->maker_code = maker_code = id[0];
		this->device_code = device_code = id[1];
		nand_type_id = maker_code<<24 | device_code<<16 | id[2]<<8 | id[3];
		B5th = id[4];
		B6th = id[5];

		printf("[Sirius]READ ID:0x%x 0x%x 0x%x 0x%x 0x%x 0x%x\n",id[0],id[1],id[2],id[3],id[4],id[5]);

        	i=1;


		if (i > 1){
			num_chips_probe = i;
			printk(KERN_INFO "NAND Flash Controller detects %d dies\n", num_chips_probe);
		}

		for (i = 0; nand_device[i].name; i++){

		#if 0
			//for read id debug
			if(nand_device[i].id==0xADDA9095)
			{
				printk("nand_device[%d].id:0x%x, nand_type_id:0x%x\n",i,nand_device[i].id,nand_type_id);
				printk("nand_device[%d].CycleID5th:0x%x, B5th:0x%x\n",i,nand_device[i].CycleID5th,B5th);
				printk("nand_device[%d].CycleID6th:0x%x, B6th:0x%x\n",i,nand_device[i].CycleID6th,B6th);
			}
		#endif


			if ( nand_device[i].id==nand_type_id &&
				((nand_device[i].CycleID5th==0xff)?1:(nand_device[i].CycleID5th==B5th))&&
				((nand_device[i].CycleID6th==0xff)?1:(nand_device[i].CycleID6th==B6th))){
				REG_WRITE_U32( REG_TIME_PARA1,nand_device[i].T1);
				REG_WRITE_U32( REG_TIME_PARA2,nand_device[i].T2);
				REG_WRITE_U32( REG_TIME_PARA3,nand_device[i].T3);
				if ( nand_type_id != HY27UT084G2M ){
					REG_WRITE_U32( REG_MULTI_CHNL_MODE,0x20);
				}
				if (nand_device[i].size == num_chips_probe * nand_device[i].chipsize){
					if ( num_chips_probe == nand_device[i].num_chips ){
						printk("One %s chip has %d die(s) on board\n",
							nand_device[i].name, nand_device[i].num_chips);
						mtd->PartNum = nand_device[i].name;
						device_size = nand_device[i].size;
						chip_size = nand_device[i].chipsize;
						page_size = nand_device[i].PageSize;
						block_size = nand_device[i].BlockSize;
						oob_size = nand_device[i].OobSize;
						num_chips = nand_device[i].num_chips;
						isLastPage = nand_device[i].isLastPage;
						rtk_lookup_table_flag = 1;
						REG_WRITE_U32( REG_TIME_PARA1,nand_device[i].T1);
						REG_WRITE_U32( REG_TIME_PARA2,nand_device[i].T2);
						REG_WRITE_U32( REG_TIME_PARA3,nand_device[i].T3);
						printf("nand part=%s, id=%x, device_size=%lu, chip_size=%lu, num_chips=%d, page_size=%d, isLastPage=%d, eccBits=%d\n",
							nand_device[i].name, nand_device[i].id, (unsigned long)nand_device[i].size, (unsigned long)nand_device[i].chipsize,
							nand_device[i].num_chips, nand_device[i].PageSize,nand_device[i].isLastPage, nand_device[i].eccSelect);
						break;
					}
				}else{
					if ( !strcmp(nand_device[i].name, "HY27UF084G2M" ) )
						continue;
					else{
						printk("We have %d the same %s chips on board\n",
							num_chips_probe/nand_device[i].num_chips, nand_device[i].name);
						mtd->PartNum = nand_device[i].name;
						device_size = nand_device[i].size;
						chip_size = nand_device[i].chipsize;
						page_size = nand_device[i].PageSize;
						block_size = nand_device[i].BlockSize;
						oob_size = nand_device[i].OobSize;
						num_chips = nand_device[i].num_chips;
						isLastPage = nand_device[i].isLastPage;
						rtk_lookup_table_flag = 1;
						printk("nand part=%s, id=%x, device_size=%lu, chip_size=%lu, num_chips=%d, isLastPage=%d, eccBits=%d\n",
							nand_device[i].name, nand_device[i].id, (unsigned long)nand_device[i].size, (unsigned long)nand_device[i].chipsize,
							nand_device[i].num_chips, nand_device[i].isLastPage, nand_device[i].eccSelect);
						break;
					}
				}
			}
		}

		if ( !rtk_lookup_table_flag ){
			printf("Warning: Lookup Table do not have this nand flash !!\n");
			printf ("%s: Manufacture ID=0x%02x, Chip ID=0x%02x, "
					"3thID=0x%02x, 4thID=0x%02x, 5thID=0x%02x, 6thID=0x%02x\n",
					mtd->name, id[0], id[1], id[2], id[3], id[4], id[5]);
			return -1;
		}

		this->page_shift = generic_ffs(page_size)-1;
		this->phys_erase_shift = generic_ffs(block_size)-1;

		this->oob_shift = generic_ffs(oob_size)-1;
		ppb = this->ppb = block_size >> this->page_shift;

		if (chip_size){
			this->block_num = chip_size >> this->phys_erase_shift;
			this->page_num = chip_size >> this->page_shift;
			this->chipsize = chip_size;
			this->device_size = device_size;
			this->chip_shift =  generic_ffs(this->chipsize )-1;
		}

		this->pagemask = (this->chipsize >> this->page_shift) - 1;

		mtd->oobsize = this->oob_size = oob_size;

		mtd->writesize = mtd->oobblock = page_size;//add by alexchang 0923-2010
		mtd->erasesize = block_size;



		this->ecc_select = nand_device[i].eccSelect;//add by alexchang 0617-2011.
		this->eccmode = MTD_ECC_RTK_HW;
		mtd->eccsize = 512;
		break;

	}

	this->select_chip(mtd, 0);

	if ( num_chips != num_chips_probe )
		this->numchips = num_chips_probe;
	else
		this->numchips = num_chips;
	div_res = mtd->size = this->numchips * this->chipsize;

	do_div(div_res,block_size);
	result = div_res;
	result*=this->RBA_PERCENT;
	do_div(result,100);
	RBA = this->RBA = result;

//	RBA = this->RBA = (mtd->size/block_size) * this->RBA_PERCENT/100;
	if(mtd->u32RBApercentage)
		mtd->u32RBApercentage = this->RBA_PERCENT;
	printk("[%s]mtd->u32RBApercentage %d%, RBA = %d\n",__FUNCTION__,mtd->u32RBApercentage, RBA);

#ifdef CONFIG_MTD_NAND_IBT
	//init I_KERNEL_RBA
	result = div_res;
	result*=this->I_KERNEL_RBA_PERCENT;
	do_div(result,100);
	this->I_KERNEL_RBA = result;
	printf("[%s]I_KERNEL_RBA_PERCENT %d%, I_KERNEL_RBA = %d\n",\
		__FUNCTION__,this->I_KERNEL_RBA_PERCENT, this->I_KERNEL_RBA);
	
	//init I_KERNEL_RBA
	div_res = SYS_PARAM_BOOTCODE_SIZE;
	do_div(div_res,block_size);
	result = div_res;
	result*=this->I_BOOTCODE_RBA_PERCENT;
	do_div(result,100);
	this->I_BOOTCODE_RBA = result;
	printf("[%s]I_BOOTCODE_RBA_PERCENT %d%, I_BOOTCODE_RBA = %d\n",\
		__FUNCTION__,this->I_BOOTCODE_RBA_PERCENT, this->I_BOOTCODE_RBA);
#endif	
	this->bbt = kmalloc( sizeof(BB_t)*RBA, GFP_KERNEL );
	if ( !this->bbt ){
		printk("%s: Error, no enough memory for BBT\n",__FUNCTION__);
		return -1;
	}
	memset(this->bbt, 0,  sizeof(BB_t)*RBA);
	
#ifdef CONFIG_MTD_NAND_IBT
	//ibt
	IBT_LEN = this->block_num;
	this->ibt = kmalloc( sizeof(IB_t)*IBT_LEN, GFP_KERNEL );
	if ( !this->ibt ){
		printk("%s: Error, no enough memory for IBT\n",__FUNCTION__);
		return -1;
	}
	memset(this->ibt, 0,  sizeof(IB_t)*IBT_LEN);
#endif

	this->g_databuf = kmalloc( page_size, GFP_KERNEL );
	if ( !this->g_databuf ){
		printk("%s: Error, no enough memory for g_databuf\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset(this->g_databuf, 0xff, page_size);

	this->g_oobbuf = kmalloc( oob_size, GFP_KERNEL );
	if ( !this->g_oobbuf ){
		printk("%s: Error, no enough memory for g_oobbuf\n",__FUNCTION__);
		return -ENOMEM;
	}
	memset(this->g_oobbuf, 0xff, oob_size);

	flag_size =  (this->numchips * this->page_num) >> 3;
	//mempage_order = get_order(flag_size);
#if 0
//	if(mempage_order<13)
	{
		this->erase_page_flag = (void *)__get_free_pages(GFP_KERNEL, mempage_order);
		if ( !this->erase_page_flag ){
			printk("%s: Error, no enough memory for erase_page_flag\n",__FUNCTION__);
			return -ENOMEM;
		}
		memset ( (__u32 *)this->erase_page_flag, 0, flag_size);
	}
#endif
	mtd->type				= MTD_NANDFLASH;
	mtd->flags			= MTD_CAP_NANDFLASH;
	mtd->ecctype		= MTD_ECC_NONE;
	mtd->erase			= nand_erase;
	mtd->point			= NULL;
	mtd->unpoint		= NULL;
	mtd->read				= nand_read;
	mtd->write			= nand_write;
	mtd->read_ecc		= nand_read_ecc;
	mtd->write_ecc		= nand_write_ecc;
	mtd->read_oob		= nand_read_oob;
	mtd->write_oob	= 	nand_write_oob;
	//mtd->_readv			= NULL;
	//mtd->writev			= NULL;
	//mtd->_readv_ecc	= NULL;
	//mtd->_writev_ecc	= NULL;
	mtd->sync			= nand_sync;
	mtd->lock				= NULL;
	mtd->unlock			= NULL;
	//mtd->suspend		= nand_suspend;
	//mtd->resume		= nand_resume;
	//mtd->owner			= THIS_MODULE;

	mtd->block_isbad			= nand_block_isbad;
	mtd->block_markbad	= nand_block_markbad;

	/* Ken: 20090210 */
	mtd->reload_bbt = rtk_nand_scan_bbt;
	mtd->scan_block_tag = nf_scan_block_tag;
	mtd->rescue_image_read = nand_rescue_image_read;
	//------------------------------------------------------------
	printf("-------------------------infomation--------------------------\n");
	printf("this->page_shift: %lu\n", (unsigned long)this->page_shift);
	printf("this->oob_shift: 0x%x\n", this->oob_shift);
	printf("this->pagemask: %lu\n", (unsigned long)this->pagemask);
	printf("this->chipsize: %lu\n",(unsigned long)this->chipsize);

#if 0
	/* =========================== for MP usage =======================*/
	mp_time_para = (char *) NF_parse_token(platform_info.system_parameters, "mp_time_para");
	if ( mp_time_para && strlen(mp_time_para) )
		mp_time_para_value = simple_strtoul(mp_time_para, &mp_time_para, 10);

	if ( mp_time_para_value ){
		/* reset the optimal speed */
		REG_WRITE_U32( REG_TIME_PARA1,mp_time_para_value);
		REG_WRITE_U32( REG_TIME_PARA2,mp_time_para_value);
		REG_WRITE_U32( REG_TIME_PARA3,mp_time_para_value);
	}

	/* get nf_clock from /sys/realtek_boards/system_parameters */
	nf_clock = (char *) NF_parse_token(platform_info.system_parameters, "nf_clock");
	if ( nf_clock && strlen(nf_clock) )
		nf_clock_value = simple_strtoul(nf_clock, &nf_clock, 10);

	if ( nf_clock_value )
		NF_CKSEL(mtd->PartNum, nf_clock_value);

	/* get mp_erase_nand from /sys/realtek_boards/system_parameters */
	mp_erase_nand = (char *) NF_parse_token(platform_info.system_parameters, "mp_erase_nand");
	//printk("mp_erase_nand=%s\n", mp_erase_nand);
	if ( mp_erase_nand && strlen(mp_erase_nand) )
		mp_erase_flag = simple_strtoul(mp_erase_nand, &mp_erase_nand, 10);
	//printk("mp_erase_flag=%d\n", mp_erase_flag);

	if ( mp_erase_flag ){
		int start_pos = 0;
		int start_page = (start_pos/mtd->erasesize)*ppb;

		unsigned long long block_num = mtd->size - start_pos;

		do_div(block_num,mtd->erasesize);
		//int block_num = (mtd->size - start_pos)/mtd->erasesize;
		//printk("start_page=%d, block_num=%d\n", start_page, block_num);
		printk("Starting erasure all contents of nand for MP.\n");
		TEST_ERASE_ALL(mtd, start_page, block_num);
		this->select_chip(mtd, 0);
		return 0;
	}

	/* CMYu, 20090720, get mcp from /sys/realtek_boards/system_parameters */
	mcp = (char *) NF_parse_token(platform_info.system_parameters, "mcp");
	//printk("mcp=%s\n", mcp);
	if (mcp){
		if ( strstr(mcp, "ecb") )
			this->mcp = MCP_AES_ECB;
		else if ( strstr(mcp, "cbc") )
			this->mcp = MCP_AES_CBC;
		else if ( strstr(mcp, "ctr") )
			this->mcp = MCP_AES_CTR;
		else
			this->mcp = MCP_NONE;
	}
#endif
	//for MCP test
	//this->mcp = MCP_AES_ECB;
	//printk("[%s] this->mcp=%d\n", __FUNCTION__, this->mcp);

	/* =========== WE Over spec: Underclocking lists: ========== */
	switch(nand_type_id){
		case HY27UT084G2M:	//WE: 40 ns
			//NF_CKSEL(mtd->PartNum, 0x04);	//43.2 MHz
			break;
		case HY27UF081G2A:	//WE: 15 ns
		case HY27UF082G2A:
		case K9G4G08U0A:
		case K9G8G08U0M:
		case TC58NVG0S3C:
		case TC58NVG1S3C:
		case HY27UT084G2A:
			NF_CKSEL(mtd->PartNum, 0x03);	//54 MHz
			break;
		default:
			;
	}

	//TEST_ERASE_ALL(mtd, 0, 1);
	//TEST_READ_WRITE(mtd, 0);
	//TEST_ERASE_ALL(mtd, 8192, 2048);
#ifdef CONFIG_MTD_NAND_IBT
	return rtk_nand_scan_ibt_bbt(mtd);
#else
	return this->scan_bbt (mtd);
#endif
}


static int TEST_ERASE_ALL(struct mtd_info *mtd, int page, int bc)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	int i;
	int chip_block_num = this->block_num;
	int start_block = page/ppb;
	int block_in_die;
	int rc = 0;
	int chipnr =0, block;

	if ( page & (ppb-1) ){
		page = (page/ppb)*ppb;
	}

	for ( i=0; i<bc; i++){
		block_in_die = start_block + i;
		chipnr = block_in_die/chip_block_num;

		this->active_chip=chipnr=0;
		block = block_in_die%chip_block_num;
		this->select_chip(mtd, block_in_die/chip_block_num);
		rc = this->erase_block(mtd, chipnr, block*ppb);
		if ( rc<0 ){
			this->g_oobbuf[0] = 0x00;
			if ( isLastPage ){
				this->write_oob(mtd, chipnr, block*ppb+ppb-1, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, block*ppb+ppb-2, oob_size, this->g_oobbuf);
			}else{
				this->write_oob(mtd, chipnr, block*ppb, oob_size, this->g_oobbuf);
				this->write_oob(mtd, chipnr, block*ppb+1, oob_size, this->g_oobbuf);
			}
		}
	}

	return 0;
}

int TEST_READ_WRITE(struct mtd_info *mtd, int page)
{
	struct nand_chip *this = (struct nand_chip *) mtd->priv;
	unsigned int chipnr=0;
	unsigned int i=0;

	memset(this->g_databuf, 0x00 , mtd->oobblock);
	this->g_databuf[0] = 0x11;
	this->g_databuf[1] = 0x22;
	this->g_databuf[2] = 0x33;
	this->g_databuf[3] = 0x44;
	this->g_databuf[4] = 0x55;
	this->g_databuf[5] = 0x11;
	this->g_databuf[6] = 0x22;
	this->g_databuf[7] = 0x33;
	this->g_databuf[8] = 0x44;
	this->g_databuf[9] = 0x55;
	this->g_databuf[10] = 0x11;
	this->g_databuf[11] = 0x22;
	this->g_databuf[12] = 0x33;
	this->g_databuf[13] = 0x44;
	this->g_databuf[14] = 0x55;
	
	memset(this->g_oobbuf, 0xff , 64);
	this->g_oobbuf[0] = 0xff;
	this->g_oobbuf[1] = 0x55;
	this->g_oobbuf[2] = 0x11;
	this->g_oobbuf[3] = 0x22;
	this->g_oobbuf[4] = 0x33;

	this->write_ecc_page(mtd, chipnr, page, this->g_databuf, this->g_oobbuf, 0);

	//redifine g_databuf value
	memset(this->g_databuf, 0xff , mtd->oobblock);
	memset(this->g_oobbuf, 0x00 , 64);
	this->read_ecc_page(mtd, chipnr, page, this->g_databuf, this->g_oobbuf);
	printk("\n-------------------------------------------------------read write test starting-------------------------------\n");
	for(i = 0; i< 2048; i++){
		if((i%16)==0)
			printk("\n");
		
		printk("0x%x\t", this->g_databuf[i]);
	}

	printk("\n\noob data:\n");
	for(i = 0; i < 64; i++){
		if((i%16)==0)
			printk("\n");
		
		printk("0x%x\t", this->g_oobbuf[i]);

	}
	printk("\n-------------------------------------------------------read write test ending--------------------------------\n");

	return 0;

}


