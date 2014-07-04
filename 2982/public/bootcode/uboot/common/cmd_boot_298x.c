/*
 * (C) Copyright 2000-2003
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/*
 * Misc boot support
 */
#include <common.h>
#include <command.h>
#include <net.h>
#include <asm/arch/rbus/crt_sys_reg.h>
#include <asm/arch/panel_config_parameter.h>
#include <asm/arch/system.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/extern_param.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/flash_writer_u/mcp.h>
#include <asm/arch/bootparam.h>
#ifndef CONFIG_SYS_RTK_NAND_FLASH
#include <asm/arch/sys_param_emmc.h>
#else
#include <asm/arch/sys_param_nand.h>
#include <linux/mtd/nand.h>		//surport nand flash driver
#include <nand.h>
#endif

#include <watchdog.h>
#include <fat.h>

#ifdef CONFIG_LZMA
#include <lzma/LzmaTypes.h>
#include <lzma/LzmaDec.h>
#include <lzma/LzmaTools.h>
#endif /* CONFIG_LZMA */
#include "linux/lzo.h"
#include <platform_lib/board/pcb.h>

#if defined(CONFIG_SYS_PANEL_SUPPORT)
	#include "panel.h"
	extern struct _PANEL_CONFIG_PARAMETER  default_panel_parameter;
	#define vFlipEnable (default_panel_parameter.iVFLIP)
#else
	static UINT8 vFlipEnable = 0;
#endif


DECLARE_GLOBAL_DATA_PTR;

#define cmd_boot_rtd_outl(addr, val)	rtd_outl(addr, val)
#define cmd_boot_rtd_inl(addr)			rtd_inl(addr)

typedef enum{
	BOOT_FROM_USB_DISABLE,
	BOOT_FROM_USB_UNCOMPRESSED,
	BOOT_FROM_USB_COMPRESSED
}BOOT_FROM_USB_T;

typedef enum{
	BOOT_FROM_FLASH_NORMAL_MODE,
	BOOT_FROM_FLASH_MANUAL_MODE
}BOOT_FROM_FLASH_T;

uint *KcpuFW_entry_ptr        = 0;
uint *uart_reg_base_ptr			= (uint *)MIPS_UART_REG_BASE_ADDR;			/* notify uart reg to A/V CPU */
uint *boot_av_info_ptr			= (uint *)MIPS_BOOT_AV_INFO_PTR_ADDR;		/* copy form darwin *boot_av_info_ptr */
uint *AudioFlag_ptr				= (uint *)MIPS_AUDIO_FLAG_PTR_ADDR;			/* for ACPU RPC */
uint *VideoFlag_ptr_V1			= (uint *)MIPS_VIDEO_FLAG_PTR_V1_ADDR;		/* for VCPU RPC */
uint *VideoFlag_ptr_V2       	= (uint *)MIPS_VIDEO_FLAG_PTR_V2_ADDR;    /* not used */
uint *KcpuFlag_ptr       		= (uint *)MIPS_KCPU_FLAG_PTR_ADDR;    /* for KCPU RPC*/
uint *AudioFW_entry_ptr			= (uint *)MIPS_AUDIO_FW_ENTRY_PTR_ADDR;		/* copy from darwin *streamfile_ptrA */
uint *VideoFW_entry_ptr_V1		= (uint *)MIPS_VIDEO_FW_ENTRY_PTR_V1_ADDR;	/* copy from darwin *streamfile_ptrV */
uint *VideoFW_entry_ptr_V2      = (uint *)MIPS_VIDEO_FW_ENTRY_PTR_V2_ADDR;   /* not used */
uint *shared_printk_buffer_ptr	= (uint *)MIPS_SHARED_PRINTK_BUFFER_ADDR;	/* copy form darwin *shared_printk_buf */
uint *audio_output_info_ptr		= (uint *)MIPS_AUDIO_OUTPUT_INFO_ADDR;		/* copy form Mac *audio_output_info */
rtk_mem_info_t *rtk_mem_info	= (rtk_mem_info_t *)UBOOT_MEM_INFO_ADDR;	/* rtd299x option */

/* for test only */
unsigned int default_aes_key[4] = { 0x2dc2df39, 0x420321d0, 0xcef1fe23, 0x74029d95 };

//uint blk_state_len;			// length of bootcode block state array
//uint nand_bootcode_area_size = 0x1400000;	// NAND bootcode area size
#ifndef CONFIG_SYS_RTK_NAND_FLASH
uint eMMC_bootcode_area_size = SYS_PARAM_BOOTCODE_SIZE;		// eMMC bootcode area size
uint eMMC_fw_desc_table_start = 0;				// start address of valid fw desc table in emmc
#else
uint NAND_fw_desc_table_saddr = SYS_PARAM_FW_TABLE_START;		// start address of fw table in nand-layout
uint NAND_fw_desc_table_start=0;		// start address of valid fw desc table in nand
#endif

uchar boot_logo_enable = 1;
uchar boot_music_enable = 1;
int boot_power_on_mode = POWER_ON;
uint custom_audio1_length = 0;
uint custom_video1_length = 0;
uint custom_audio2_length = 0;
uint custom_video2_length = 0;
#if defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC)||defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
uint  custom_image_length = 11;
#endif

int prev_power_on_status = POWER_ON;
uint boot_part = 0; // from layout.txt
uint boot_tag = TAG_COMPLETE; // from layout.txt


uint b_fw_desc_table_vaild = 0;
uint sys_logo_start = UBOOT_LOGO_START_ADDR;
uchar sys_logo_enabled = 0;
uchar sys_logo_is_HDMI = 0;
uchar tv_test_enabled = 0;
fw_desc_entry_v1_t *kernel_entry = NULL;
BOOT_FROM_FLASH_T boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
BOOT_FROM_USB_T boot_from_usb = BOOT_FROM_USB_DISABLE;
UINT32 g_u32StdAnimation =0 ;
UINT32 g_isSTR = 0;
#if defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC)//20140506  xq_xiao
int konka_boot_vol;
int konka_sleepled_mode;
int konka_uart_enable;
#endif

extern uchar boot_ac_on;
extern unsigned int mcp_dscpt_addr;
extern const unsigned int Kh_key_default[4];

#if defined(CONFIG_STD_ENABLE)
#define IS_ENABLE_STD		(1)
#else
#define IS_ENABLE_STD		(0)
#endif

#if IS_ENABLE_STD
uint bytes_per_page = 512;
uint pages_per_block = 1;
#else
uint bytes_per_page = 0;
uint pages_per_block = 0;
#endif

UINT32 g_goAddr = 0;
UINT32 (*GoFuncPtr)(void);

#if IS_ENABLE_STD
#define IS_ERASE_ID_BLK	(1)

#define EMMC_FACTORY_SIZE			0x800000	// factory area size (right behind bootcode blocks)
#define BOOTCODE_CONTINUE	(0xF2)
#define BOOTCODE_STD_WORK	(0xF3)
#define UNZIP_BUFFER_SIZE	0x400000
#define USE_LZMA			(0)
#define STD_ID_STRING		"@RTK_STD"

UINT32 g_u32STDsize=0;
UINT32 g_u32STDoffset=0x4000000;
UINT32 g_audio_buffer_addr = 0;
UINT32 g_audio_buffer_size = 0;
UINT32 g_video_buffer_addr = 0;
UINT32 g_video_buffer_size = 0;
UINT32 g_last_image_addr = 0;
UINT32 g_last_image_size =0 ;

UINT8 headerBuf[8192];

UINT32 g_imgLen = 0;
UINT32 g_ZipBuf = 0;
UINT32 g_ZipBlkSize = 0;

UINT32 g_STDbsBufferSize = 0;


typedef struct{
        u8      sig[8];
        u16     version;
        u16     data_format;
        u32     start_addr;
        u32     comp_total_size;
        u32     comp_blk_size;
        u32     comp_buffer_addr;
        u32     bs_buffer_addr;
        u32     bs_buffer_size;
        u32     audio_buffer_addr;
        u32     audio_buffer_size;
        u32     video_buffer_addr;
        u32     video_buffer_size;
        u32     last_image_addr;
        u32     last_image_size;
} st_swsusp_header;

UINT32 std_BSsize = 0;
UINT32 g_STDbsBufferAddr = 0;

UINT32 g_u32Stdflag = 0;
UINT8 *ptrHeadBuf;
UINT32 g_u32DataFormat = 0;
//	   data_format = 0: raw data
//	   data_format = 1: LZO compressed data
//	   data_format = 2: ZLIB compressed data
//	   data_format = 3: LZMA compressed data
#endif

extern void delete_env(void);
extern void enable_clock(uint reg_reset, uint mask_reset, uint reg_clock, uint mask_clock);
extern void do_vcpu_bisr(void);
extern int rtk_plat_boot_go(bootm_headers_t *images);
extern int rtk_plat_run_rescue_from_flash(void);
extern int rtk_plat_run_rescue_from_USB(const char *rescue_file_name);
extern int decrypt_image(char *src, char *dst, uint length, uint *key);
extern void rtk_hexdump( const char * str, unsigned char * pcBuf, unsigned int length );
extern int boot_prep_linux_kcpu(void);

#if IS_ENABLE_STD
int moveToRam(unsigned int* blockNO, unsigned int len, UINT32 Buffer, unsigned int signature)
{
	//printf("[%s][blk:0x%x, addr:0x%x, len:0x%x]\n",__FUNCTION__,*blockNO,Buffer,len);
	//flash_STDread.block_no = blockNO;
    //flash_STDread.signature = signature;
    //flash_STDread.length = len;
    //flash_STDread.buffer = (UINT8*)Buffer;
	//return IO_read(SYS_MAJOR_FLASH, 0, &flash_STDread);
	unsigned int rescue_blk_addr=*blockNO;
	//printf("rescue_blk_addr 0x%x\n",rescue_blk_addr);
	rtk_eMMC_read(rescue_blk_addr, len, (unsigned int *)Buffer);
	return 0;
}


int unzipToRam(UINT32 srcBuffer, UINT32 desBuffer, UINT32 inlen, UINT32* outlen)
{
	int ret = 0;
	*outlen = UNZIP_BUFFER_SIZE;
	if(g_u32DataFormat == 0x0)//raw format
	{
		ret = inlen;
	}
	else if(g_u32DataFormat == 0x03)//LZMA support
	{
		//RTK_LZMA_Init();
		printf("[%s]outlen 0x%x\n",*outlen);
		//ret = RTK_LZMA_Decompress((UINT8*)srcBuffer,inlen,(UINT8*)desBuffer,outlen);
		printf("[%s]ret %d\n",__FUNCTION__,ret);
	}
	else if(g_u32DataFormat == 0x01)//LZO support
	{
		ret = lzo1x_decompress_safe((UINT8*)srcBuffer,inlen,(UINT8*)desBuffer,outlen);
	}

		return ret;
		//return lzo1x_decompress_safe((UINT8*)srcBuffer,inlen,(UINT8*)desBuffer,outlen);
}


int processImg_STDAnimation(UINT8* Buffer)
{
	UINT32 lenCnt = 0;
	UINT32 blkNO = 0;
	UINT32 memAddr = 0;
	UINT32 imgLen = 0;
	UINT32 retZipLen = 0xff;
	int i=0;
	unsigned int tmp =0;
	unsigned int modTmp =0;
	unsigned int u32Pad = 256*1024;
	unsigned int compressSize = 0;
	unsigned int unzipSize = 0;
	unsigned int mul = u32Pad/(bytes_per_page * pages_per_block);
	blkNO = (g_u32STDoffset+128*1024)/(bytes_per_page * pages_per_block);
	printf("%s...\n",__FUNCTION__);
	printf("g_imgLen is 0x%x\n",g_imgLen);
	//printf("Move and unzip to ram...Start\n");

display_evaluate_time("Move and unzip to ram...Start");
//int EJTestCnt = 0;
	while(lenCnt<g_imgLen)
	{
		//if(EJTestCnt>=2) break;
		memcpy(&memAddr,&Buffer[128+8*i],4);
		memcpy(&imgLen,&Buffer[132+8*i],4);
		//printf("i value: %d, lenCnt 0x%x\n",i,lenCnt);
		//printf("memAddr 0x%x, imageLen:0x%x\n",memAddr,imgLen);
		//printf("[Move]blk 0x%x --> mem 0x%x\n",blkNO,g_ZipBuf);
	if(!g_u32DataFormat)//Don't support compress....
	{

		if(moveToRam(&blkNO,imgLen,memAddr, 0) !=0)
		{
			printf("[%s]Nand read fail....\n",__FUNCTION__);
			return -1;
		}

		//unzipToRam(g_ZipBuf,memAddr,imgLen,&retZipLen);
		//printf("[Unzip]mem 0x%x --> mem 0x%x, Len 0x%x\n",g_ZipBuf,memAddr,retZipLen);
		printf(".");

	}
	else
	{
		compressSize+=imgLen;
		if(moveToRam(&blkNO,imgLen,g_ZipBuf, 0) !=0)
		{
			printf("[%s]Nand read fail....\n",__FUNCTION__);
			return -1;
		}
		//printf("$\n");
		unzipToRam(g_ZipBuf,memAddr,imgLen,&retZipLen);
		//printf("[Unzip]mem 0x%x --> mem 0x%x, Len 0x%x\n",g_ZipBuf,memAddr,retZipLen);
		unzipSize+=retZipLen;
		printf(".");
		if(retZipLen > g_ZipBlkSize)
		{
			printf("Unzip overfollow!!!!!!!!!!!!!\n");
	//printf("blk 0x%x, size 0x%x, unziplen 0x%x\n",blkNO,imgLen,retZipLen);
	//printf("retZiplen 0x%x\n\n\n",retZipLen);
			break;
		}
		//printf("blk 0x%x, size 0x%x, unziplen 0x%x\n",blkNO,imgLen,retZipLen);

	}
		tmp = imgLen/u32Pad;
		modTmp =  imgLen%u32Pad;
		if(modTmp)
			blkNO+=((tmp+1)*mul);
		else
			blkNO+=(tmp*mul);
		lenCnt+=imgLen;
		i++;

		//EJTestCnt++;
	}
	//printf("Move and unzip to ram...End\n");
	display_evaluate_time("Move and unzip to ram...End");
	printf("Process zip size 0x%x, unzip size 0x%x\n",compressSize,unzipSize);

	//sys_dcache_flush_all();
	//sys_icache_invalidate_all();

}

unsigned int  processImg_V3(UINT8* Buffer)
{
	UINT32 lenCnt = 0;
	UINT32 blkNO = 0;
	UINT32 memAddr = 0;
	UINT32 imgLen = 0;
	UINT32 retZipLen = 0xff;
	int i=0;
	unsigned int tmp =0;
	unsigned int modTmp =0;
	unsigned int u32Pad = 256*1024;
	unsigned int mul = u32Pad/(bytes_per_page * pages_per_block);
	blkNO = (g_u32STDoffset+128*1024)/(bytes_per_page * pages_per_block);
	printf("STD_V3 supported...\n");
    g_u32StdAnimation = 1;

	#if 1
//	sys_dcache_flush_all();
//	sys_icache_invalidate_all();
	return BOOTCODE_STD_WORK;
	#else

	while(lenCnt<g_imgLen)
	{
		memcpy(&memAddr,&Buffer[132+16*i],4);
		memcpy(&imgLen,&Buffer[136+16*i],4);
		if(moveToRam(&blkNO,imgLen,g_ZipBuf, 0) !=OK)
		{
			printf("[%s]Nand read fail....\n",__FUNCTION__);
			return BOOTCODE_CONTINUE;
		}
		unzipToRam(g_ZipBuf,memAddr,imgLen,&retZipLen);
	//printf("retZiplen 0x%x\n\n\n",retZipLen);
	//break;
		tmp = imgLen/u32Pad;
		modTmp =  imgLen%u32Pad;
		if(modTmp)
			blkNO+=((tmp+1)*mul);
		else
			blkNO+=(tmp*mul);
		lenCnt+=imgLen;
		i++;
	}
	#endif
	//sys_dcache_flush_all();
	//sys_icache_invalidate_all();
	//return BOOTCODE_STD_WORK;
}
void imdpatterngenerator_ipg1080p_fs_fhd_dibypass(void)
{
	#include "scripts/dpll_297MHz.tbl"                    // DPLL setting for fhd

	#include "scripts/dtg_fhd_frc.tbl"                      // DTG for full hd setting

	#include "scripts/mtg_fhd.tbl"                           // MTG for 1920x1080 setting

	rtd_outl(0xb8029000, 0x00EF0031);			   // D-domain Pattern Gen Setting

	rtd_outl(0xb8029028, 0x07800438);			   //Input Size (1920x1080)

	#include "scripts/LVDS_FHD_1Pixel_1Seg_2Port.tbl"        // SFG, PIF, TX_PHY


}

void STDinitProc(void)
{

	printf("[%s]init panel module...\n",__FUNCTION__);
	//init panel_1st
	//initmodulesEx1();
	//init panel_2nd
	//initmodulesEx2();


	//Enable clock and init procedure.....
	//post_hwsetting();
printf("Set IMD domain pattern...\n");
    printf("Skip imdpatterngenerator_ipg1080p_fs_fhd_dibypass()\n");
    //imdpatterngenerator_ipg1080p_fs_fhd_dibypass();

#ifndef Board_LAN_NULL
				//printf("Reset Ethernet Mac.\n");
				//reset ethernet mac
    	//REG8(0xb801603b) = 0x01;//For saturn
//    	REG32(0xb8016038) = 0x01;//For darwin & Macarthur
#endif

//For 299X
	//cmd_boot_rtd_outl(0xb8016234, 0x0);
	//cmd_boot_rtd_outl(0xb801603c, 0xffff);
	//cmd_boot_rtd_outl(0xb8016038, 0x1);


	//disable UART0/UART1 interrupt before go linux
	//if ((REG32(KSEG1(MIS_U0LCR)) & 0x80) == 0)
	//	REG32(KSEG1(MIS_U0IER_DLH)) = 0;
	//if ((REG32(KSEG1(MIS_U1LCR)) & 0x80) == 0)
	//	REG32(KSEG1(MIS_U1IER_DLH)) = 0;


//	imdpatterngenerator_ipg1080p_fs_fhd_dibypass();
}

/************************************************************************
 *
 *                          mainSTD
 *  Description :
 *  -------------
 *  Implement STD(Suspend To Disk) functionl
 *
 *  Return values :
 *  ---------------
 *  None, function never returns
 *
 ************************************************************************/
unsigned int mainSTD(void)
{
	UINT32 blkNO;
	UINT32 goAddr;
	UINT32 imgLen;
	//UINT32 ddrAddr=1024*1024-4096;
	UINT32 skipBlk=0;
	UINT32 skipSize = 1024*1024;
	char ch =0;
	int k=0;
	if(g_u32STDsize<=0||g_u32STDoffset<=0)
	   return BOOTCODE_CONTINUE;
	printf("Start STD function...\n");
	//printf("g_u32STDsize 0x%x\n",g_u32STDsize);
	//printf("g_u32STDoffset 0x%x\n",g_u32STDoffset);
	//Write parameter to system_parameters_3

	//if (BOOT_FLASH_TYPE == BOOT_NAND)
	{

			return processImg_V3(ptrHeadBuf);
	}
	//else
	//	return BOOTCODE_CONTINUE;
}


int checkHeader(UINT8* Buffer)
{
	st_swsusp_header header_buf;

	//Check identifier
	memcpy(&header_buf,Buffer,sizeof(st_swsusp_header));
	if(memcmp(header_buf.sig,STD_ID_STRING,8)!=0)
	{
		printf("STD identifier NOT match\n");
		return BOOTCODE_CONTINUE;
	}

	g_u32StdAnimation 	= 1;
	g_u32Stdflag 		= header_buf.version;
	g_u32DataFormat 	= header_buf.data_format;
	g_goAddr 			= header_buf.start_addr;
	g_imgLen 			= header_buf.comp_total_size;
	g_ZipBlkSize 		= header_buf.comp_blk_size;
	g_ZipBuf 			= header_buf.comp_buffer_addr;
	g_STDbsBufferAddr	= header_buf.bs_buffer_addr;
	g_STDbsBufferSize 	= header_buf.bs_buffer_size;
	g_audio_buffer_addr	= header_buf.audio_buffer_addr;
	g_audio_buffer_size	= header_buf.audio_buffer_size;
	g_video_buffer_addr = header_buf.video_buffer_addr;
	g_video_buffer_size = header_buf.video_buffer_size;
	g_last_image_addr 	= header_buf.last_image_addr;
	g_last_image_size 	= header_buf.last_image_size;

	if(g_u32DataFormat==0x03)
		printf("Use lzma\n");
    else if(g_u32DataFormat==0x01)
		printf("Use LZO\n");
	else if(g_u32DataFormat==0x0)
		printf("Use raw data\n");
	else
		printf("Unknown data format\n");

	#if ALFIE_TEST
		printf("Only For alfie test!\n");
		g_u32StdAnimation = 0;
	#endif
		printf("g_u32StdAnimation 0x%x\n",g_u32StdAnimation);
		printf("g_u32Stdflag 0x%x\n",g_u32Stdflag);
		printf("g_u32DataFormat 0x%x\n",g_u32DataFormat);
		printf("Go address 0x%x\n",g_goAddr);
		printf("imgLen 0x%x\n",g_imgLen);
		printf("g_ZipBlkSize 0x%x\n",g_ZipBlkSize);
		printf("ZipBuf 0x%x\n",g_ZipBuf);
		printf("g_STDbsBufferAddr 0x%x\n",g_STDbsBufferAddr);
		printf("g_STDbsBufferSize 0x%x\n",g_STDbsBufferSize);

	if(g_imgLen<=0)
	{
		printf("[WARNING]image length <=0 [%u]\n",g_imgLen);
		return BOOTCODE_CONTINUE;
	}
	printf("STD go 0x%x\n",g_goAddr);
	printf("%s:\n",__FUNCTION__);
	printf("g_audio_buffer_addr 0x%x\n",g_audio_buffer_addr);
	printf("g_audio_buffer_size 0x%x\n",g_audio_buffer_size);
	printf("g_video_buffer_addr 0x%x\n",g_video_buffer_addr);
	printf("g_video_buffer_size 0x%x\n",g_video_buffer_size);
	printf("g_last_image_addr 0x%x\n",g_last_image_addr);
	printf("g_last_image_size 0x%x\n",g_last_image_size);
	return 0;
}


#endif

static void release_hw_semaphore(void)
{
//	printf("## Release HW semaphore\n");

	cmd_boot_rtd_outl(0xb801a000, 0x0);
}

#ifdef CONFIG_CMD_GO
static unsigned long do_go_kernel_image(void)
{
	bootm_headers_t	images;

	memset(&images, 0, sizeof(bootm_headers_t));

	if (getenv("kernel_entry") != NULL) {
		images.ep = (unsigned long)simple_strtol(getenv("kernel_entry"), NULL, 16);
	}
	else {
		images.ep = (unsigned long)LINUX_KERNEL_ENTRY;
	}

	printf("Start Linux at 0x%lx ...\n", images.ep);

	rtk_plat_boot_go(&images);

	return 0;
}

static unsigned long do_go_kcpu_fw(unsigned int address)
{
	printf("Start KCPU Firmware ...\n");

	if (boot_prep_linux_kcpu() !=0)
		return 0;

	flush_dcache_all();

#ifdef CONFIG_KCPU_LOAD_K_FW
	run_command("kboot go_k", 0);
#else
	if (address != 0xffffffff)
		rtd_outl(CRT_WDOG_DATA10_VADDR, address);
	else if (*KcpuFW_entry_ptr != 0)
		rtd_outl(CRT_WDOG_DATA10_VADDR, *KcpuFW_entry_ptr);
	else
		rtd_outl(CRT_WDOG_DATA10_VADDR, MIPS_KCPU_FW_ENTRY_ADDR | MIPS_KSEG0BASE);

	//release hw semaphore
	rtd_outl(0xb801a630, 0x0);
#endif

	return 0;
}

static int unmute_amp(void)
{
#if 0
	unsigned long long value = 0;

	if (pcb_mgr_get_enum_info_byname("PIN_AMP_MUTE", &value) < 0) {
		printf("no PIN_AMP_MUTE\n");
		return -1;
	} else {
		printf("%s %d mute src\n", __FUNCTION__, __LINE__);
		rtd_outl(0xb8033004, 0x00120000);
		rtd_outl(0xb8006b28, 0x00007ff8);
		printf("%s %d unmute amp\n", __FUNCTION__, __LINE__);
		mdelay(350);
		IO_Set(value, 0);// 0: unmute  1: mute
	}
#else
	//set bb_aiol_GPI_EN bb_aior_GPI_EN as GPIO mode
	//mute AMP in pcb
	printf("bypass unmute\n");
#endif

	return 0;
}

static unsigned long do_go_audio_fw(void)
{
	uint mask_reset;
	uint mask_clock;

	printf("Start Audio Firmware ...\n");

	*AudioFW_entry_ptr = SWAPEND32(MIPS_AUDIO_FW_ENTRY_ADDR | MIPS_KSEG1BASE);

	flush_dcache_all();

#ifdef ENABLE_ACPU_BISR
   mdelay(10);
   printf("%s %d hold_hw_semaphore\n", __FUNCTION__, __LINE__);
   hold_hw_semaphore();
#endif
   // rst = 0
   rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);   // aio, ae
   rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT0);   // acpu
   rtd_clearbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);  //dac1, dac2
   // clk = 1
   rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22);
   rtd_setbits(CRT_GROUP1_CK_EN_VADDR, _BIT19 | _BIT18 | _BIT17 | _BIT15 | _BIT14 | _BIT13);
   rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6);

   // clk = 0
   rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22); // aio, ae
   rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6); // ade, acpu
   // rst = 0
   rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);   // aio, ae
   rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT0);   // acpu
   rtd_clearbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);  //dac1, dac2
   udelay(10);
   // rst = 1
   rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);
   rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT0);
   rtd_setbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);
   udelay(10);
   // clk = 1
   rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22);
   rtd_setbits(CRT_GROUP1_CK_EN_VADDR, _BIT19 | _BIT18 | _BIT17 | _BIT15 | _BIT14 | _BIT13);
   rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6);

	unmute_amp();

#ifdef ENABLE_ACPU_BISR
   do_acpu_bisr();
#endif

	/* Release HW Semaphore */
	release_hw_semaphore();

	return 0;
}

static unsigned long do_go_video_fw(int vcpu_no)
{
	int ret = 0;
	uint mask_reset, mask_reset1;
	uint mask_clock, mask_clock1;

	switch (vcpu_no) {
		case 0:
		case 1:
			printf("Start Video Firmware ...\n");
			*VideoFW_entry_ptr_V1 = SWAPEND32(MIPS_VIDEO_FW_1_ENTRY_ADDR | MIPS_KSEG1BASE);
			break;

		default:
			printf("## Unknown option %d\n", vcpu_no);
			ret = 1;
			break;
	}

	if (ret == 0)
	{
		flush_dcache_all();

#ifdef ENABLE_VCPU_BISR
		mdelay(10);
		printf("%s %d hold_hw_semaphore\n", __FUNCTION__, __LINE__);
		hold_hw_semaphore();
#endif
		// rst = 0
		rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
		rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);

		// clk = 1
		rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
		rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);
		// clk = 0
		rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); // ve, se
		rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7); // vcpu, vde, me
		// rst = 0
		rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
		rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
		udelay(10);
		// rst = 1
		rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
		rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
		udelay(10);
		// clk = 1
		rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
		rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);

#ifdef ENABLE_VCPU_BISR
		do_vcpu_bisr();
#endif

		/* Release HW Semaphore */
		release_hw_semaphore();
	}

	return ret;
}

static unsigned long do_go_all_fw(void)
{
	int ret = 0;
	uint mask_reset;
	uint mask_clock;

	printf("Start Audio Firmware ...\n");
	printf("Start Video Firmware ...\n");

	*AudioFW_entry_ptr = SWAPEND32(MIPS_AUDIO_FW_ENTRY_ADDR | MIPS_KSEG1BASE);
	*VideoFW_entry_ptr_V1 = SWAPEND32(MIPS_VIDEO_FW_1_ENTRY_ADDR | MIPS_KSEG1BASE);

	if (*KcpuFW_entry_ptr != 0) {
		printf("Start KCPU Firmware ...\n");
   	if (boot_prep_linux_kcpu() !=0) {
			printf("boot_prep_linux_kcpu failed\n");
      	return 0;
		}
	}

	flush_dcache_all();

#ifdef ENABLE_ACPU_BISR
	mdelay(10);
	printf("%s %d hold_hw_semaphore\n", __FUNCTION__, __LINE__);
	hold_hw_semaphore();
#endif

	/* Enable ACPU */
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);	 // aio, ae
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT0);   // acpu
	rtd_clearbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);  //dac1, dac2
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22);
	rtd_setbits(CRT_GROUP1_CK_EN_VADDR, _BIT19 | _BIT18 | _BIT17 | _BIT15 | _BIT14 | _BIT13);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6);

	// clk = 0
	rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22); // aio, ae
	rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6); // ade, acpu
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);   // aio, ae
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT0);   // acpu
	rtd_clearbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);  //dac1, dac2
	udelay(10);
	// rst = 1
	rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);
	rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT0);
	rtd_setbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);
	udelay(10);
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22);
	rtd_setbits(CRT_GROUP1_CK_EN_VADDR, _BIT19 | _BIT18 | _BIT17 | _BIT15 | _BIT14 | _BIT13);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6);

	unmute_amp();

#ifdef ENABLE_ACPU_BISR
	do_acpu_bisr();
#endif

	/* Enable VCPU1 */
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);

	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);
	// clk = 0
	rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); // ve, se
	rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7); // vcpu, vde, me
	// rst = 0
	rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
	udelay(10);
	// rst = 1
	rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
	rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
	udelay(10);
	// clk = 1
	rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
	rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);

#ifdef ENABLE_VCPU_BISR
	do_vcpu_bisr();
#endif

	/* Release HW Semaphore */
	release_hw_semaphore();

	if (*KcpuFW_entry_ptr != 0) {
#ifdef CONFIG_KCPU_LOAD_K_FW
		run_command("kboot go_k", 0);
#else
		rtd_outl(CRT_WDOG_DATA10_VADDR, *KcpuFW_entry_ptr);

		//release hw semaphore
		rtd_outl(0xb801a630, 0x0);
#endif
   }

	/* Enter kernel entry */
	do_go_kernel_image();

	return ret;
}

/* Allow ports to override the default behavior */
__attribute__((weak))
unsigned long do_go_exec (ulong (*entry)(int, char * const []), int argc, char * const argv[])
{
	return entry (argc, argv);
}

int do_go (cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	ulong	addr=0xffffffff, rc;
	int     rcode = 0;
	int     i;

	if (argc < 2)
		return CMD_RET_USAGE;

	if (argv[1][0] == 'a')
	{
		if (argv[1][1] == '\0')	// audio fw
		{
			return do_go_audio_fw();
		}
		else if (argv[1][1] == 'l' && argv[1][2] == 'l')	// all fw
		{
			return do_go_all_fw();
		}
		else
		{
			printf("Unknown command '%s'\n", argv[1]);
			return CMD_RET_USAGE;
		}
	}
	else if (argv[1][0] == 'v')
	{
		if (argv[1][1] == '\0')	// v1, v2 fw
		{
			return do_go_video_fw(0);
		}
		else if (argv[1][1] == '1')	// v1 fw
		{
			return do_go_video_fw(1);
		}
		else if (argv[1][1] == '2')	// v2 fw
		{
			return do_go_video_fw(2);
		}
		else
		{
			printf("Unknown command '%s'\n", argv[1]);
			return CMD_RET_USAGE;
		}
	}
	else if (argv[1][0] == 'k')
	{
		return do_go_kernel_image();	// kernel image
	}
	else if (argv[1][0] == 'c')
	{
		if (argc == 3)
			addr = simple_strtoul(argv[2], NULL, 16);

		return do_go_kcpu_fw(addr);
	}
	else if (argv[1][0] == 'r')
	{
#ifdef CONFIG_KCPU_LOAD_RESCUE
		int ret = 0;

		ret = run_command("kboot rescue", 0);
		if (ret != 0) { // failed
			return 0;
		}

		ret = run_command("kboot wait", 0);
		if (ret != 0) { // failed
			return 0;
		}

		ret = run_command("kboot go_r", 0);
		if (ret != 0) { // failed
			return 0;
		}

		printf("[FATAL] k enter rescue, s should enter busy loop.\n");

		return 0;
#endif

		if (argv[1][1] == '\0') // rescue from flash
		{
			if (rtk_plat_run_rescue_from_flash() == RTK_PLAT_ERR_OK)
			{
				boot_mode = BOOT_RESCUE_MODE;

				return do_go_kernel_image();
			}
			else
			{
				return 0;
			}
		}
#ifdef CONFIG_RESCUE_FROM_USB
		else if (argv[1][1] == 'u') // rescue from usb
		{
			char file_name_buf[32];
			char *rescue_file_name = NULL;

			rescue_file_name = getenv("rescue_file_name");

			if (rescue_file_name == NULL) {
				strcpy(file_name_buf, CONFIG_RESCUE_FROM_USB_FILENAME);
				rescue_file_name = file_name_buf;
			}

			if (rtk_plat_run_rescue_from_USB(rescue_file_name) == RTK_PLAT_ERR_OK)
			{
				return do_go_kernel_image();
			}
			else
			{
				return 0;
			}
		}
#endif
		else
		{
			return 0;
		}
	}

	addr = simple_strtoul(argv[1], NULL, 16);

	printf ("Starting application at 0x%08lX ...\n", addr);

	for( i = 0; i < argc; i++ ) {
		if( strncmp( argv[i], "nocache", 7 ) == 0 ) {
			printf ("Run application w/o any cache\n");
			cleanup_before_dvrbootexe();
			break;
		}
	}

	/*
	 * pass address parameter as argv[0] (aka command name),
	 * and all remaining args
	 */
	rc = do_go_exec ((void *)addr, argc - 1, argv + 1);
	if (rc != 0) rcode = 1;

#ifdef CONFIG_CLEAR_ENV_AFTER_UPDATE_BOOTCODE
	if (rcode == 0 && addr == DVRBOOT_EXE_BIN_ENTRY_ADDR)
	{
		printf ("MMC rescan ...\n");
		run_command_list("mmc rescan", -1, 0); // rescan mmc device to prevent mmc read error

		printf ("Clear env in factory after updating bootcode ...\n");
		delete_env();
	}
#endif


	printf ("Application terminated, rc = 0x%lX\n", rc);
	return rcode;
}

/* -------------------------------------------------------------------- */

U_BOOT_CMD(
	go, CONFIG_SYS_MAXARGS, 1,	do_go,
	"start application at address 'addr' or start running fw",
	"[addr/a/v/v1/v2/k] [arg ...]\n"
	"\taddr  - start application at address 'addr'\n"
	"\ta     - start audio firmware\n"
	"\tv     - start video firmware 1\n"
	"\tc     - start kcpu firmware \n"
	"\tk     - start kernel\n"
	"\tr     - start rescue linux\n"
#ifdef CONFIG_RESCUE_FROM_USB
	"\tru    - start rescue linux from usb\n"
#endif
	"\tall   - start all firmware\n"
	"\t[arg] - passing 'arg' as arguments\n"
);

#endif

U_BOOT_CMD(
	reset, 1, 0,	do_reset,
	"Perform RESET of the CPU",
	""
);

/*
 * input
 * interface : "usb"
 * char *dev_part : "0:1"
 *
 * return : first file in root directory or NULL
 */
char *fat_ls_first (char *interface, char *dev_part)
{
//	char *filename = "/";
	int dev=0;
	int part=1;
	char *ep;
	block_dev_desc_t *dev_desc=NULL;

	dev = (int)simple_strtoul(dev_part, &ep, 16);
	dev_desc = get_dev(interface,dev);
	if (dev_desc == NULL) {
		puts("\n** Invalid boot device **\n");
		return NULL;
	}
	if (*ep) {
		if (*ep != ':') {
			puts("\n** Invalid boot device, use `dev[:part]' **\n");
			return NULL;
		}
		part = (int)simple_strtoul(++ep, NULL, 16);
	}
	if (fat_register_device(dev_desc,part)!=0) {
		printf("\n** Unable to use %s %d:%d for fatls **\n",
			interface, dev, part);
		return NULL;
	}

	return file_fat_ls_first();
}

#if defined(CONFIG_USB_UPDATE_SCRIPT)

extern long usb_read_fat_file_size;
int install_to_go_flag = 0;

static inline char* skip_char(char* str, char c)
{
	do
	{
		if(*str==0) return NULL;
		if(*str==c) return str+1;
		str++;
	} while(1);
	return NULL;
}
bool have_bootcode = false, have_image = false;

static int check_image_flag()
{
        return have_image;
}

static int check_dvrboot_flag()
{
        int i, j, endmark;
        char *script = (char *)(DVRBOOT_EXE_BIN_ENTRY_ADDR);
	char *flagchar;
        char newline[MAX_USB_SCRIPT_LINE][MAX_USB_SCRIPT_LINE_LEN] = {0};

	if ( usb_read_fat_file_size > MAX_USB_SCRIPT_LINE*MAX_USB_SCRIPT_LINE_LEN*8 )
	{
		printf("[WARN] %s:read %s failed. (file size too large > %d)\n", __FUNCTION__, USB_AUTO_SCRIPT, MAX_USB_SCRIPT_LINE*MAX_USB_SCRIPT_LINE_LEN);
		return 0;
	}
        printf("**** usb_read_fat_file_size = %d\n", usb_read_fat_file_size);
        int tempSLen = strlen(BOOTCODE_RESCUE);
        int tempSLen2 = strlen(FULL_IMG);

        for (i=0, j=0, endmark=0; i < usb_read_fat_file_size ; i++)
	{
                if ( *(script+i) == 0x0D )
                {
			if ( (i-endmark+1) > MAX_USB_SCRIPT_LINE_LEN )
			{
				printf("[WARN] %s:read %s.lst failed. (line length too large > %d)\n",__FUNCTION__, USB_AUTO_SCRIPT, MAX_USB_SCRIPT_LINE_LEN);
				return 0;
			}
                	*(script+i) = '\0';
                	*(script+i+1) = '\0';
			memcpy(newline[j], (char *)(script+endmark), i-endmark+1);
        		//printf("i=%d,j=%d:%02x:%s\n", i, j, *(script+i+2), newline[j]);
                        endmark=i+2;
                        j++;
                }
        }

	for (i=0; (i < (j-1)); i++)
	{
		if((newline[i][0] == ';') || (newline[i][0] == '#')) continue;
		printf("newline: %s\n", newline[i]);

		if(0 == strncmp( BOOTCODE_RESCUE , newline[i], tempSLen))
                {
                        printf( "%s=%s\n", BOOTCODE_RESCUE, flagchar=skip_char(newline[i]+tempSLen, '='));
                        if (flagchar[0] == 'N')
				have_bootcode = true;
			//else
                                //return 0;
                        continue;
        	}
                if(0 == strncmp( FULL_IMG , newline[i], tempSLen2))
                {
                        printf( "%s=%s\n", FULL_IMG, flagchar=skip_char(newline[i]+tempSLen2, '='));
                        if (flagchar[0] == 'N')
				have_image = true;
			//else
                                //return 0;
                        continue;
        	}
	}
	return have_bootcode;
}

int check_usb_autoscript_update(const char *script_file_name, uchar bBootcode, uchar bUsb_need_init)
{
	uint target_addr = 0;
	uint data_bytes = 0;
	int ret = 0;
	char cmd[128] = {0};

	printf("[UAC_DBG] autoscript parms: bBootcode=%d, bUsb_need_init=%d, install_to_go_flag=%d\n", bBootcode, bUsb_need_init, install_to_go_flag);
        if (bUsb_need_init)
	{
		// usb start_ac
		memset( cmd, 0, sizeof(cmd) );
		sprintf( cmd, "usb start_ac" );
		ret = run_command( cmd, 0 );
		if (ret != 0)
		{
			/* usb start_ac error */
			printf("[INFO] %s:usb start_ac failed. (No USB plug-in)\n", __FUNCTION__);
			return 0;
		}
	}
#ifdef CONFIG_USB_UPDATE_UBOOT_WHEN_AC_ON
      	if (install_to_go_flag == 0)
	{
		// read dvrboot.exe.bin from usb
		printf("read %s to entering usb update bootcode ...\n", script_file_name);
		target_addr = DVRBOOT_EXE_BIN_ENTRY_ADDR;
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "fatload usb 0:1 %x %s %x", target_addr, script_file_name, data_bytes);
		ret = run_command(cmd, 0);
	}
#else
	// read dvrboot.exe.bin from usb
	printf("read %s to entering usb update bootcode ...\n", script_file_name);
	target_addr = DVRBOOT_EXE_BIN_ENTRY_ADDR;
	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "fatload usb 0:1 %x %s %x", target_addr, script_file_name, data_bytes);
	ret = run_command(cmd, 0);
#endif
        if (bBootcode)
	{
		if (ret != 0)
		{
			/* Read error */
			install_to_go_flag = 2;
			printf("[WARN] %s:read %s failed. (No such file, skip bootcode update flow)\n", __FUNCTION__, script_file_name);
			return 0;
		}
		else
		{
			/* Read success */
			install_to_go_flag = 1;
			if(check_dvrboot_flag())
                        	return 1;  // dvrboot.exe.bin=N in autoscript.lst
			else
				return 0;  // dvrboot.exe.bin=N Not in autoscript.lst or marked by #
		}
        }
        else
        {
#ifdef CONFIG_USB_UPDATE_UBOOT_WHEN_AC_ON
		if (install_to_go_flag == 1 && check_image_flag() )
		{
			/* Read success */
			return 1;
		}
		else
		{
			/* Read error */
			printf("[WARN] %s:read %s failed. (No such file, skip install flow)\n", __FUNCTION__, script_file_name);
			return 0;
		}
#else
		if (ret != 0)
		{
			/* Read error */
			printf("[WARN] %s:read %s failed. (No such file, skip install flow)\n", __FUNCTION__, script_file_name);
			return 0;
		}
		else
		{
                        if( check_image_flag() == 1 )
			        return 1;  //autoscript.lst exits
			else
			{
                                printf("[WARN] %s:read %s failed. (No such file, skip install flow)\n", __FUNCTION__, script_file_name);
                                return 0;
			}
		}
#endif
        }
}
#endif

#ifdef CONFIG_USB_UPDATE_WHEN_AC_ON
#define RESCUE_FILENAME_IN_INSTALL_IMG	"0.vmlinux.rescue.bin"
#define RESCUE_FILENAME_IN_INSTALL_IMG2	"0.vmlinux.rescue.aes"

#ifdef CONFIG_CHECK_IMG_VERSION
#include <environment.h>
extern unsigned long strtoul(	const char *str, char **endptr, int base);
#define FORCE_UPDATE true //Flag to set force update when no version can be referenced.
#define IMG_VERSION_FILE "FW_VERSION"

bool check_if_image_update_by_version( bool forceUpdate )
{
        bool ret = forceUpdate; //if you want update without ant version check
                                //please pass true in this function.
        char *tmp_tok = NULL;
        int tmp_tok_index = 0;
        unsigned int img_version[3] = {0};
        unsigned int fw_version[3] = {0};
        
        //check if env have version number----------
        ENTRY e, *ep;
        const char *name = "fwver";
	e.key = name;
	e.data = NULL;
        
        hsearch_r(e, FIND, &ep, &env_htab);
	if (ep == NULL)
	{
                printf("[WARN] %s:read env variable - fwver failed. (No such env) skip check version number\n", __FUNCTION__);
                return ret;
	}
        
        //got the fw version        
	printf("software_version=%s\n", ep->data);
        tmp_tok = strtok( ep->data, "." );
        while(tmp_tok!=NULL)
        {
                fw_version[tmp_tok_index] = strtoul(tmp_tok, NULL, 10);
                tmp_tok_index += 1;
                tmp_tok = strtok( NULL, "."  );
        }
        //-----------------------------------
        
        //check if image have version file------------
        char *dst_addr = NULL;
	unsigned int dst_length = 0;
        char image_version[20] = {0};
        char cmd[128] = {0};
        // read install.img from usb 
	printf("read %s 0x%x bytes to entering usb update ...\n", "install.img", 0x00C00000);
	sprintf(cmd, "fatload usb 0:1 %x %s %x", 0x0f800000, "install.img", 0x00C00000);
	ret = run_command(cmd, 0);
        
        if( tar_read( IMG_VERSION_FILE, rtk_mem_info->temp_buffer_for_flash_data_addr, 0x00C00000/*maybe too large*/, &dst_addr, &dst_length) > 0 )
        {
                //Read file content
                strncpy( image_version, dst_addr, dst_length );
                printf("install image_version is =%s\n", image_version);
                tmp_tok_index = 0;
                tmp_tok = strtok( image_version, "." );
                while(tmp_tok!=NULL)
                {
                        img_version[tmp_tok_index] = strtoul(tmp_tok, NULL, 10);
                        tmp_tok_index += 1;
                        tmp_tok = strtok( NULL, "."  );
                }
                                        
        }else
        {
                printf("[WARN] %s:read image version number failed. (No version info in install.img) skip check version number\n", __FUNCTION__);
                return ret;
        }
        //-----------------------------------
        
        //compare version if image is newer than fw, just update it.
        if( img_version[0] == fw_version[0] )
        {
                if( img_version[1] == fw_version[1] )
                {
                        if( img_version[2] < fw_version[2] )
                                ret = false; //no-need update
                        else
                                ret = true; //need update
                }
                else if( img_version[1] < fw_version[1] )
                {
                        ret = false; //no-need update
                }
                else
                        ret = true; //need update
        }
        else if( img_version[0] > fw_version[0] )
                ret = true; //need update
        else
                ret = false; //no-need update

        if( ret == true )
        {
                sprintf(cmd, "env set %s %d.%d.%d;env save", name, img_version[0], img_version[1], img_version[2]);
	        if( 0 != run_command(cmd, 0) )
	        {
                        printf("[WARN] %s:set new version failed. skip check version number\n", __FUNCTION__);
                        ret = false; //is it a good way?
	        }
        }

        return ret;

}
#endif

int check_usb_update(const char *install_file_name, uchar bBootcode, uchar bUsb_need_init)
{
	uint target_addr = 0;
	uint data_bytes = 0;
	int ret = 0;
	char cmd[128];
#ifndef CONFIG_USB_UPDATE_READ_RESCUE_FROM_FLASH
	char *dst_addr = NULL;
	uint dst_length = 0;
#endif
	unsigned int rescue_bytes;
	unsigned int secure_mode;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int rescue_truncated_size;

	// for encrypted rescue linux
	mcp_dscpt_addr = 0;
	secure_mode = rtk_get_secure_boot_type();

	if (bUsb_need_init)
	{
		// usb start_ac
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "usb start_ac");
		ret = run_command(cmd, 0);
		if (ret != 0)
		{
			/* usb start_ac error */
			printf("[INFO] %s:usb start_ac failed. (No USB plug-in)\n", __FUNCTION__);
			return 0;
		}
	}

	if (bBootcode)
	{
		// read dvrboot.exe.bin from usb
		printf("read %s to entering usb update bootcode ...\n", install_file_name);
		target_addr = DVRBOOT_EXE_BIN_ENTRY_ADDR;
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "fatload usb 0:1 %x %s %x", target_addr, install_file_name, data_bytes);
		ret = run_command(cmd, 0);
		if (ret != 0)
		{
			/* Read error */
			printf("[WARN] %s:read %s failed. (No such file)\n", __FUNCTION__, install_file_name);
			return 0;
		}
		else
		{
			/* Read success */
			return 1;
		}
	}
	else
	{
#ifdef CONFIG_CHECK_IMG_VERSION                
                if( !check_if_image_update_by_version(FORCE_UPDATE) ) //Alway set update when no version info can be referenced.
                {
                        printf("[WARN] %s:check %s version be older than firmware install now. Skip AC-on auto update\n", __FUNCTION__, install_file_name);
                        return 0;   
                }
#endif                
		target_addr = rtk_mem_info->temp_buffer_for_flash_data_addr;

#ifdef CONFIG_USB_UPDATE_READ_RESCUE_FROM_FLASH
		data_bytes = 0x200; // try reading 512 bytes to check file existed or not
#else
		data_bytes = 0x00C00000; // try reading 12M to cover the resuce linux
#endif

		// read install.img from usb
		printf("read %s 0x%x bytes to entering usb update ...\n", install_file_name, data_bytes);
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "fatload usb 0:1 %x %s %x", target_addr, install_file_name, data_bytes);
		ret = run_command(cmd, 0);
		if (ret != 0)
		{
			/* Read error */
			printf("[WARN] %s:Read %s 0x%x bytes from USB failed. (0x%x)\n", __FUNCTION__, install_file_name, data_bytes, ret);
			return 0;
		}
		else
		{
			//return 1;/* Read success */
			//printf("Read %s from USB success.\n", install_file_name);
		}

#ifdef CONFIG_USB_UPDATE_READ_RESCUE_FROM_FLASH
		printf("copy rescue linux from emmc\n");
#else
		printf("copy rescue linux from usb\n");

		// find rescue linux
		if( secure_mode == 0 ) {
			ret = tar_read(RESCUE_FILENAME_IN_INSTALL_IMG, target_addr, data_bytes, &dst_addr, &dst_length);
		}
		else {
			ret = tar_read(RESCUE_FILENAME_IN_INSTALL_IMG2, target_addr, data_bytes, &dst_addr, &dst_length);
		}
		if ( ret > 0 )
		{
			/* copy to kernel entry address */
			target_addr = LINUX_KERNEL_ENTRY;

			rescue_bytes = dst_length;
			switch( secure_mode ) {
				case 0:											// normal mode
					rescue_truncated_size = SHA256_SIZE;
					break;
				case 1:											// NDS
					printf("[ERR] %s: not support NDS secure mode\n", __FUNCTION__);
					rescue_truncated_size = RSA_SIGNATURE_LENGTH;
					return 0;
				case 2:											// RTK
					rescue_truncated_size = RSA_SIGNATURE_LENGTH;
					break;
				case 3: 	// DCAS
					printf("[ERR] %s: not support DCAS secure mode\n", __FUNCTION__);
					rescue_truncated_size = RSA_SIGNATURE_LENGTH;
					return 0;
				default:
					printf("[ERR] %s: unknown secure mode\n", __FUNCTION__);
					return 0;
			}

			// debug print
			//printf("*** %s %d : file size   = 0x%08x(%d)\n", __FILE__, __LINE__, dst_length, dst_length );
			//printf("*** %s %d : dst_addr    = 0x%08x\n", __FILE__, __LINE__, (unsigned int)dst_addr );
			//printf("*** %s %d : target_addr = 0x%08x\n", __FILE__, __LINE__, target_addr );
			//printf("*** %s %d : bootcode_truncated_size = 0x%08x\n", __FILE__, __LINE__, bootcode_truncated_size );
			rtk_hexdump("the first 32-byte rescue data", dst_addr, 32 );
			//rtk_hexdump("the last 512-byte rescue data", dst_addr+dst_length-512, 512 );

			// decode image
			if( secure_mode == 2 ) { // RTK
				printf("to decrypt...\n");
				if (decrypt_image((char *)dst_addr,
					(char *)target_addr,
					dst_length-rescue_truncated_size,
					Kh_key_ptr))
				{
					printf("decrypt image error!\n");
					return 0;
				}
				// debug print
				rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)target_addr, 32 );

				printf("decrypt rescue successful\n");

			}
			// caculate hash of rescue
			if( secure_mode == 0 ) {
#if 0
				ret = Verify_SHA256_hash( (unsigned char *)dst_addr,
				                          dst_length - rescue_truncated_size,
				                          (unsigned char *)(dst_addr + dst_length - rescue_truncated_size), 0 );
#else
				ret = 0; // image_file_ceator not append any data to it, so skip hash verification
#endif
			}
			else {
#if (0)
				reverse_signature( (unsigned char *)(dst_addr+dst_length-rescue_truncated_size) );

				ret = Verify_SHA256_hash( (unsigned char *)target_addr,
				                          dst_length - rescue_truncated_size,
				                          (unsigned char *)(dst_addr + dst_length - rescue_truncated_size),
				                          1 );
#endif
				printf("skip SHA256 check...\n");
				ret = 0;
			}
			if( ret < 0 ) {
				printf("[ERR] %s: hash value not match\n", __FUNCTION__ );
				return 0;
			}

			if( secure_mode == 0 ) {
				printf("copy %s from 0x%08x to 0x%x %d bytes\n", RESCUE_FILENAME_IN_INSTALL_IMG, dst_addr, target_addr, dst_length);
				memcpy((char *)target_addr, dst_addr, dst_length);
			}
		}
		else
		{
			/* tar read failed or not found */
			printf("[ERR] %s:File %s not found\n", __FUNCTION__, secure_mode ? RESCUE_FILENAME_IN_INSTALL_IMG2 : RESCUE_FILENAME_IN_INSTALL_IMG);
			return 0;
		}
#endif
	}

	return 1;
}
#endif

uint get_checksum(uchar *p, uint len) {
	uint checksum = 0;
	uint i;

	for(i = 0; i < len; i++) {
		checksum += *(p+i);

		if (i % 0x200000 == 0)
		{
			EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here
		}
	}
	return checksum;
}

#if defined(CONFIG_SYS_RTK_EMMC_FLASH) || defined(CONFIG_SYS_RTK_NAND_FLASH)
static int check_image(void)
{
	return 0;
}
#endif

#if 0 // move to arch/arm/include/asm/arch-rtd299x/fw_infoh
typedef struct{
	uchar bIsEncrypted;			/* must fill this value before we call get layout */
	uchar bIsCompressed;		/* must fill this value before we call get layout */

	uint flash_to_ram_addr;		/* will get this result at least */
	uint encrpyted_addr;		/* option result */
	uint decrypted_addr;		/* option result */
	uint compressed_addr;		/* option result */
	uint decompressed_addr;		/* option result */
	uint image_target_addr;		/* must fill this value before we call get layout */
} MEM_LAYOUT_WHEN_READ_IMAGE_T;
#endif

uint get_mem_layout_when_read_image(MEM_LAYOUT_WHEN_READ_IMAGE_T *mem_layout)
{
	if (mem_layout->image_target_addr == 0)
	{
		printf("[ERROR] mem_layout->image_target_addr = 0x%08x\n", mem_layout->image_target_addr);

		return 1;
	}

	if (mem_layout->bIsEncrypted)
	{
		mem_layout->flash_to_ram_addr = mem_layout->encrpyted_addr = rtk_mem_info->encrypted_fw_image_addr;

		if (mem_layout->bIsCompressed)
		{
			mem_layout->decrypted_addr = mem_layout->compressed_addr = COMPRESSED_FW_IMAGE_ADDR;
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
			mem_layout->flash_to_ram_addr = mem_layout->compressed_addr = COMPRESSED_FW_IMAGE_ADDR;
			mem_layout->decompressed_addr = mem_layout->image_target_addr;
		}
		else
		{
			mem_layout->flash_to_ram_addr = mem_layout->image_target_addr;
		}
	}

	return 0;
}

int decrypt_image_fpk(char *src, char *dst, uint length)
{
	int i;
	uint sblock_len;
	uchar *sblock_dst, *sblock_src;

	printf("decrypt(fpk) from 0x%08x to 0x%08x, len:0x%08x\n", (uint)src, (uint)dst, length);

	// get short block size
	sblock_len = length & 0xf;

	if (AES_CBC_decrypt_key_in_CW((uchar *)src, length - sblock_len, (uchar *)dst, 120)) {
		printf("%s %d, fail\n", __FUNCTION__, __LINE__);
		return -1;
	}

	// handle short block (<16B)
	if (sblock_len) {
		// take the last 16B of AES CBC result as input, do AES ECB encrypt
		sblock_src = (uchar *)src + (length - sblock_len);
		sblock_dst = (uchar *)dst + (length - sblock_len);
		//printf("sblock_src: 0x%p, sblock_dst: 0x%p\n", sblock_src, sblock_dst);
		if (AES_ECB_encrypt_key_in_CW((UINT8 *)(sblock_src - 16), 16, sblock_dst, 120)) {
			printf("%s %d, fail\n", __FUNCTION__, __LINE__);
			return -1;
		}

		// XOR with short block data to generate final result
		for (i = 0; i < sblock_len; i++)
			sblock_dst[i] ^= sblock_src[i];
	}

	return 0;
}

int decrypt_image(char *src, char *dst, uint length, uint *key)
{
	int i;
	uint sblock_len;
	uchar *sblock_dst, *sblock_src;

	printf("decrypt from 0x%08x to 0x%08x, len:0x%08x\n", (uint)src, (uint)dst, length);

	// get short block size
	sblock_len = length & 0xf;

	if (AES_CBC_decrypt((uchar *)src, length - sblock_len, (uchar *)dst, key)) {
		printf("%s %d, fail\n", __FUNCTION__, __LINE__);
		return -1;
	}

	// handle short block (<16B)
	if (sblock_len) {
		// take the last 16B of AES CBC result as input, do AES ECB encrypt
		sblock_src = (uchar *)src + (length - sblock_len);
		sblock_dst = (uchar *)dst + (length - sblock_len);
		//printf("sblock_src: 0x%p, sblock_dst: 0x%p\n", sblock_src, sblock_dst);
		if (AES_ECB_encrypt((UINT8 *)(sblock_src - 16), 16, sblock_dst, key)) {
			printf("%s %d, fail\n", __FUNCTION__, __LINE__);
			return -1;
		}

		// XOR with short block data to generate final result
		for (i = 0; i < sblock_len; i++)
			sblock_dst[i] ^= sblock_src[i];
	}

	return 0;
}

//#define DUBUG_FW_DESC_TABLE
#ifdef DUBUG_FW_DESC_TABLE
void dump_fw_desc_table_v1(fw_desc_table_v1_t *fw_desc_table_v1)
{
	if (fw_desc_table_v1 != NULL) {
		printf("## Fw Desc Table ##############################\n");
		printf("## fw_desc_table_v1                = 0x%08x\n", fw_desc_table_v1);
		printf("## fw_desc_table_v1->signature     = %s\n", fw_desc_table_v1->signature);
		printf("## fw_desc_table_v1->checksum      = 0x%08x\n", fw_desc_table_v1->checksum);
		printf("## fw_desc_table_v1->version       = 0x%08x\n", fw_desc_table_v1->version);
		printf("## fw_desc_table_v1->paddings      = 0x%08x\n", fw_desc_table_v1->paddings);
		printf("## fw_desc_table_v1->part_list_len = 0x%08x\n", fw_desc_table_v1->part_list_len);
		printf("## fw_desc_table_v1->fw_list_len   = 0x%08x\n", fw_desc_table_v1->fw_list_len);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_desc_table_v1 is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_part_desc_entry_v1(part_desc_entry_v1_t *part_entry)
{
	if (part_entry != NULL) {
		printf("## Part Desc Entry ############################\n");
		printf("## part_entry                      = 0x%08x\n", part_entry);
		printf("## part_entry->type                = 0x%08x\n", part_entry->type);
		printf("## part_entry->ro                  = 0x%08x\n", part_entry->ro);
		printf("## part_entry->length              = 0x%08x\n", part_entry->length);
		printf("## part_entry->fw_count            = 0x%08x\n", part_entry->fw_count);
		printf("## part_entry->fw_type             = 0x%08x\n", part_entry->fw_type);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d part_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}

void dump_fw_desc_entry_v1(fw_desc_entry_v1_t *fw_entry)
{
	if (fw_entry != NULL) {
		printf("## Fw Desc Entry ##############################\n");
		printf("## fw_entry                        = 0x%08x\n", fw_entry);
		printf("## fw_entry->type                  = 0x%08x\n", fw_entry->type);
		printf("## fw_entry->lzma                  = 0x%08x\n", fw_entry->lzma);
		printf("## fw_entry->ro                    = 0x%08x\n", fw_entry->ro);
		printf("## fw_entry->version               = 0x%08x\n", fw_entry->version);
		printf("## fw_entry->target_addr           = 0x%08x\n", fw_entry->target_addr);
		printf("## fw_entry->offset                = 0x%08x\n", fw_entry->offset);
		printf("## fw_entry->length                = 0x%08x\n", fw_entry->length);
		printf("## fw_entry->paddings              = 0x%08x\n", fw_entry->paddings);
		printf("## fw_entry->checksum              = 0x%08x\n", fw_entry->checksum);
		printf("###############################################\n\n");
	}
	else {
		printf("[ERR] %s:%d fw_entry is NULL.\n", __FUNCTION__, __LINE__);
	}
}
#endif

//#define DUBUG_BOOT_AV_INFO
#ifdef DUBUG_BOOT_AV_INFO
void dump_boot_av_info(boot_av_info_t *boot_av)
{
	if (boot_av != NULL) {
		printf("\n");
		printf("## Boot AV Info (0x%08x) ##################\n", boot_av);
		printf("## boot_av->dwMagicNumber          = 0x%08x\n", boot_av->dwMagicNumber);
		printf("## boot_av->dwVideoStreamAddress   = 0x%08x\n", boot_av->dwVideoStreamAddress);
		printf("## boot_av->dwVideoStreamLength    = 0x%08x\n", boot_av->dwVideoStreamLength);
		printf("## boot_av->dwAudioStreamAddress   = 0x%08x\n", boot_av->dwAudioStreamAddress);
		printf("## boot_av->dwAudioStreamLength    = 0x%08x\n", boot_av->dwAudioStreamLength);
		printf("## boot_av->bVideoDone             = 0x%08x\n", boot_av->bVideoDone);
		printf("## boot_av->bAudioDone             = 0x%08x\n", boot_av->bAudioDone);
		printf("## boot_av->bHDMImode              = 0x%08x\n", boot_av->bHDMImode);
		printf("## boot_av->dwAudioStreamVolume    = 0x%08x\n", boot_av->dwAudioStreamVolume);
		printf("## boot_av->dwAudioStreamRepeat    = 0x%08x\n", boot_av->dwAudioStreamRepeat);
		printf("## boot_av->bPowerOnImage          = 0x%08x\n", boot_av->bPowerOnImage);
		printf("## boot_av->bRotate                = 0x%08x\n", boot_av->bRotate);
		printf("## boot_av->dwVideoStreamType      = 0x%08x\n", boot_av->dwVideoStreamType);
		printf("## boot_av->audio_buffer_addr      = 0x%08x\n", boot_av->audio_buffer_addr);
		printf("## boot_av->audio_buffer_size      = 0x%08x\n", boot_av->audio_buffer_size);
		printf("## boot_av->video_buffer_addr      = 0x%08x\n", boot_av->video_buffer_addr);
		printf("## boot_av->video_buffer_size      = 0x%08x\n", boot_av->video_buffer_size);
		printf("## boot_av->last_image_addr        = 0x%08x\n", boot_av->last_image_addr);
		printf("## boot_av->last_image_size        = 0x%08x\n", boot_av->last_image_size);
		printf("###############################################\n\n");
	}
}
#endif

static void reset_shared_memory(void)
{
	boot_av_info_t *boot_av;

//	*uart_reg_base_ptr = 0;
	*boot_av_info_ptr = 0;
	*AudioFlag_ptr = 0;
	*VideoFlag_ptr_V1 = 0;
	*AudioFW_entry_ptr = 0;
	*VideoFW_entry_ptr_V1 = 0;
	memset(shared_printk_buffer_ptr, 0, MIPS_SHARED_PRINTK_BUFFER_SIZE);

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));
}

//#define RESCUE_LINUX_IN_USB_IS_COMPRESSED

#ifdef CONFIG_RESCUE_FROM_USB
/*
 * run rescue from flash (USB)
 */
int rtk_plat_run_rescue_from_USB(const char *rescue_file_name)
{
	uint target_addr = 0;
	int ret = 0;
	char cmd[128];
#ifdef RESCUE_LINUX_IN_USB_IS_COMPRESSED
	uint rescue_bytes = 0;
	uint uncompressedSize = 0;
#endif

	printf("Run rescue from USB\n");

/*
	if (ext_para_ptr->rescue_img_size == 0)
	{
		printf("[ERR] %s:Rescue image size error!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	if (ext_para_ptr->rescue_img_part0_saddr == 0)
	{
		printf("[ERR] %s:Rescue first part address error!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	if (ext_para_ptr->rescue_img_part0_len == 0)
	{
		printf("[ERR] %s:Rescue first part length error!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}
*/

	/*
	 * From Angus:
	 *     Flash Writer doesn't use rescue_img_part1_saddr,
	 *     so we won't check the part1 saddr and length here.
	 */

	/* Read rescue linux */
//	rescue_blk_no = ext_para_ptr->rescue_img_part0_saddr;
//	rescue_bytes = ext_para_ptr->rescue_img_size;
#ifdef RESCUE_LINUX_IN_USB_IS_COMPRESSED
	target_addr = rtk_mem_info->encrypted_fw_image_addr;
#else
	target_addr = LINUX_KERNEL_ENTRY;
#endif

	printf("\n");
	printf("########################################################\n");
	printf("## Enter Rescue Linux:\n");
	printf("##    rescue_file_name = %s\n", rescue_file_name);
	printf("##    target_addr      = 0x%x\n", target_addr);
	printf("########################################################\n");
	printf("\n");

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "usb start_ac");

	ret = run_command(cmd, 0);
	if (ret != 0)
	{
		/* usb start_ac error */
		printf("[ERR] %s:usb start_ac failed. (%s)\n", __FUNCTION__, cmd);
	}

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "fatload usb 0:1 %x %s", target_addr, rescue_file_name);

	ret = run_command(cmd, 0);
	if (ret != 0)
	{
		/* Read error */
		printf("[ERR] %s:Read rescue from USB failed. (%s, 0x%x, 0x%x)\n", __FUNCTION__, rescue_file_name, target_addr, ret);
		ret = RTK_PLAT_ERR_READ_RESCUE_IMG;
	}
	else
	{
		/* Read success */
		printf("[Done] copy rescue0: from USB:%s to 0x%x (0x%x)\n", rescue_file_name, target_addr, ret);
		ret = RTK_PLAT_ERR_OK;
	}

#ifdef RESCUE_LINUX_IN_USB_IS_COMPRESSED
	/* do unlzma */
	printf("## Decompress rescue linux using LZMA ...\n");
	if (lzmaBuffToBuffDecompress((uchar*)LINUX_KERNEL_ENTRY, &uncompressedSize, (uchar*)target_addr, rescue_bytes) != 0)
	{
		/* Decompress error */
		printf("[ERR] %s:Decompress using LZMA error!! (0x%x, 0x%x)\n", __FUNCTION__, target_addr, rescue_bytes);

		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}
	else
	{
		/* Decompress success */
		printf("[Done] uncompressedSize = 0x%x\n", uncompressedSize);
	}
#endif

	return ret;
}
#endif

/*
 * run rescue from flash (eMMC)
 */
int rtk_get_secure_boot_type(void)
{
#if 0
	switch(ext_para_ptr->secure_mode) {
		case 0:
			return NONE_SECURE_BOOT;

		case 1:
			return NDS_SECURE_BOOT;

		case 2:
			return RTK_SECURE_BOOT;

		case 3:
			return DCAS_SECURE_BOOT;

		default:
			return NONE_SECURE_BOOT;
	}
	return NONE_SECURE_BOOT;
#else
#if defined(CONFIG_SYS_RTK_SECURE_BOOT)
	return RTK_SECURE_BOOT;
#else
	return NONE_SECURE_BOOT;
#endif
#endif
}



int rtk_plat_run_rescue_from_eMMC(void)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	#define RESCUE_LINUX_IN_EMMC_IS_COMPRESSED 1 // temp use this define
	unsigned int secure_mode;
	unsigned int rescue_blk_addr = 0;
	int ret = 0;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int rescue_truncated_size;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	rescue_linux_info_t rescue_linux_hdr;
	unsigned int rescue_linux_hdr_size;
	uint imageSize = 0;
	uint decompressedSize = 0;

	// for encrypted rescue linux
	secure_mode = rtk_get_secure_boot_type();

	switch( secure_mode ) {
		case NONE_SECURE_BOOT:					// normal mode
			rescue_truncated_size = SHA256_SIZE;
			break;
		case RTK_SECURE_BOOT:					// RTK
			rescue_truncated_size = RSA_SIGNATURE_LENGTH;
			//force some setting
			Kh_key_ptr = default_aes_key;
			break;
#if 0 //:TODO: Fix it for other secure boot
		case NDS_SECURE_BOOT:					// NDS
			printf("[ERR] %s: not support NDS secure mode\n", __FUNCTION__);
			rescue_truncated_size = RSA_SIGNATURE_LENGTH;
			return RTK_PLAT_ERR_READ_RESCUE_IMG;


		case DCAS_SECURE_BOOT:					// DCAS
			printf("[ERR] %s: not support DCAS secure mode\n", __FUNCTION__);
			rescue_truncated_size = RSA_SIGNATURE_LENGTH;
			return RTK_PLAT_ERR_READ_RESCUE_IMG;
#endif
		default:
			printf("[ERR] %s: unknown secure mode\n", __FUNCTION__);
			return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	/* get memory layout before copy kernel image */
	mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
	mem_layout.bIsCompressed = RESCUE_LINUX_IN_EMMC_IS_COMPRESSED;
	mem_layout.image_target_addr = LINUX_KERNEL_ENTRY;

	get_mem_layout_when_read_image(&mem_layout);

	rescue_blk_addr = EMMC_RESCUE_LINUX_BLOCK_NO;
	rescue_linux_hdr_size = sizeof(rescue_linux_info_t);

	if( !(ret = rtk_eMMC_read(rescue_blk_addr, rescue_linux_hdr_size, (unsigned int *)mem_layout.flash_to_ram_addr)) ) {
		printf("[ERR] %s:Read rescue header failed\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}
	else {
		printf("get header done\n");
	}

	/* if secure mode, do decrypt header first */
	if( secure_mode == RTK_SECURE_BOOT ) {

		printf("decrypt header size %d...\n", (rescue_linux_hdr_size+(0x10-1)&~(0x10-1)));

		if (decrypt_image((char *)mem_layout.flash_to_ram_addr,
					(char *)mem_layout.decrypted_addr,
					(rescue_linux_hdr_size+(0x10-1)&~(0x10-1)),
					Kh_key_ptr))
		{
			printf("decrypt header error!\n");
			return RTK_PLAT_ERR_READ_RESCUE_IMG;
		}
		memcpy(&rescue_linux_hdr, (void *)mem_layout.decrypted_addr, rescue_linux_hdr_size);
		rescue_linux_hdr.dwImageSize += RSA_2048_KEY_LENGTH;

	}
	else
	{
		memcpy(&rescue_linux_hdr, (void *)mem_layout.flash_to_ram_addr, rescue_linux_hdr_size);
	}

	if (rescue_linux_hdr.dwMagicNumber == RESCUE_LINUX_HEADER_MAGICNO) {
		rescue_blk_addr = EMMC_RESCUE_LINUX_BLOCK_NO;
		imageSize = rescue_linux_hdr.dwImageSize;

		//compressed data start from the end of the header
		mem_layout.compressed_addr += rescue_linux_hdr_size;
	}
	else {
		printf("[WARN] rescue linux header error, fall back to ext_para mode\n");
		rescue_blk_addr = ext_para_ptr->rescue_img_addr;
		imageSize = ext_para_ptr->rescue_img_size;
	}

	if( imageSize == 0 ) {
		printf("[ERR] %s:Rescue image size error!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	printf("#############################\n");
	printf("# Enter Rescue Linux:\n");
	printf("#   secure_mode = %d\n",     secure_mode);
	printf("#   compressed  = %d\n",     mem_layout.bIsCompressed);
	printf("#   block_no    = 0x%08x\n", rescue_blk_addr);
	printf("#   size_bytes  = 0x%08x\n", imageSize);
	printf("#   target_addr = 0x%08x\n", mem_layout.image_target_addr);
	printf("#############################\n");

	if( !(ret = rtk_eMMC_read(rescue_blk_addr, imageSize, (unsigned int *)mem_layout.flash_to_ram_addr)) ) {
		printf("[ERR] %s:Read rescue failed\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}
	else {
		printf("read done\n");
	}

	/* if secure mode, do AES CBC decrypt */
	if( secure_mode == RTK_SECURE_BOOT ) {

		printf("to decrypt...\n");

		if (decrypt_image((char *)mem_layout.encrpyted_addr,
					(char *)mem_layout.decrypted_addr,
					imageSize-rescue_truncated_size,
					Kh_key_ptr))
		{
			printf("decrypt image error!\n");
			return RTK_PLAT_ERR_READ_RESCUE_IMG;
		}

		rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32 );

		printf("decrypt rescue successful\n");

#if 0
		reverse_signature( (unsigned char *)(mem_layout.encrpyted_addr + imageSize - rescue_truncated_size) );

		ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
								  imageSize - rescue_truncated_size,
								  (unsigned char *)(mem_layout.encrpyted_addr + imageSize - rescue_truncated_size), 1 );
		if( ret < 0 )
			rtk_hexdump("the first 32-byte rescue data", (unsigned char *)mem_layout.decrypted_addr, 32 );
#endif
		printf("skip SHA256 check...\n");
		imageSize = imageSize-rescue_truncated_size;
	}
	else
	{
		ret = Verify_SHA256_hash( (unsigned char *)mem_layout.flash_to_ram_addr,
		                          imageSize - rescue_truncated_size,
		                          (unsigned char *)(mem_layout.flash_to_ram_addr + imageSize - rescue_truncated_size), 0 );
		if( ret < 0 )
			rtk_hexdump("the first 32-byte rescue data", (unsigned char *)mem_layout.flash_to_ram_addr, 32 );

	}

	if( ret < 0 ) {
		printf("[ERR] %s: hash value not match\n", __FUNCTION__ );
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	/* if lzma rescue, decompress rescue image to target_addr */
	if (mem_layout.bIsCompressed)
	{
		if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
		{
			printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

			return RTK_PLAT_ERR_READ_KERNEL_IMG;
		}
	}
#endif

	return RTK_PLAT_ERR_OK;
}

int rtk_plat_run_rescue_from_NAND(void)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
#define RESCUE_LINUX_IN_NAND_IS_COMPRESSED 1 // temp use this define
#define RESCUE_LINUX_SCAN_DEPTH  0x20
#define RESCUE_LINUX_BLOCK_TAG  0x80
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from;
	unsigned int retlen;

	unsigned int secure_mode;
	unsigned int rescue_blk_addr = 0;
	int ret = 0;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int rescue_truncated_size;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	rescue_linux_info_t rescue_linux_hdr;
	unsigned int rescue_linux_hdr_size;
	uint imageSize = 0;
	uint decompressedSize = 0;

	// for encrypted rescue linux
	secure_mode = rtk_get_secure_boot_type();

	switch( secure_mode ) {
		case NONE_SECURE_BOOT:					// normal mode
			rescue_truncated_size = SHA256_SIZE;
			break;
      case RTK_SECURE_BOOT:               // RTK
         rescue_truncated_size = RSA_SIGNATURE_LENGTH;
         //force some setting
         Kh_key_ptr = default_aes_key;
         break;
#if 0 //:TODO: Fix it for secure boot
		case NDS_SECURE_BOOT:					// NDS
			printf("[ERR] %s: not support NDS secure mode\n", __FUNCTION__);
			rescue_truncated_size = RSA_SIGNATURE_LENGTH;
			return RTK_PLAT_ERR_READ_RESCUE_IMG;

		case DCAS_SECURE_BOOT:					// DCAS
			printf("[ERR] %s: not support DCAS secure mode\n", __FUNCTION__);
			rescue_truncated_size = RSA_SIGNATURE_LENGTH;
			return RTK_PLAT_ERR_READ_RESCUE_IMG;
#endif
		default:
			printf("[ERR] %s: unknown secure mode\n", __FUNCTION__);
			return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	/* get memory layout before copy kernel image */
	mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
	mem_layout.bIsCompressed = RESCUE_LINUX_IN_NAND_IS_COMPRESSED;
	mem_layout.image_target_addr = LINUX_KERNEL_ENTRY;

	get_mem_layout_when_read_image(&mem_layout);

	//rescue_blk_addr = NAND_RESCURE_LOGO_BLK_ADDR;
	rescue_blk_addr = nand->scan_block_tag(nand, NAND_RESCURE_LOGO_BLK_ADDR, RESCUE_LINUX_SCAN_DEPTH, 0,RESCUE_LINUX_BLOCK_TAG);
	if(rescue_blk_addr == 0){
		printf("[ERR] %s: Scan block-tag failed!!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}else{
		printf("[OK] %s:Scan block-tag ok!!\n", __FUNCTION__);
	}
	rescue_linux_hdr_size = sizeof(rescue_linux_info_t);

	from = rescue_blk_addr* (nand->erasesize);	//must define NAND_fw_desc_table_start
	ret = nand->rescue_image_read(nand, (unsigned char *)mem_layout.flash_to_ram_addr, from, rescue_linux_hdr_size, 0, RESCUE_LINUX_BLOCK_TAG);
	if(ret == 0){
		/* Read success */
		printf("[OK] %s:Read rescue header ok!!\n", __FUNCTION__);
	}else{
		/* Read error */
		printf("[ERR] %s:Read rescue header error!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

   /* if secure mode, do decrypt header first */
   if( secure_mode == RTK_SECURE_BOOT ) {

      printf("decrypt header size %d...\n", (rescue_linux_hdr_size+(0x10-1)&~(0x10-1)));

      if (decrypt_image_fpk((char *)mem_layout.flash_to_ram_addr,
               (char *)mem_layout.decrypted_addr,
               (rescue_linux_hdr_size+(0x10-1)&~(0x10-1))
               ))
      {
         printf("decrypt header error!\n");
         return RTK_PLAT_ERR_READ_RESCUE_IMG;
      }
      memcpy(&rescue_linux_hdr, (void *)mem_layout.decrypted_addr, rescue_linux_hdr_size);
      rescue_linux_hdr.dwImageSize += RSA_2048_KEY_LENGTH;

   }
   else
   {
      memcpy(&rescue_linux_hdr, (void *)mem_layout.flash_to_ram_addr, rescue_linux_hdr_size);
   }

	if (rescue_linux_hdr.dwMagicNumber == RESCUE_LINUX_HEADER_MAGICNO) {
		//rescue_blk_addr = NAND_RESCURE_LOGO_BLK_ADDR;
		imageSize = rescue_linux_hdr.dwImageSize;

		//compressed data start from the end of the header
		mem_layout.compressed_addr += rescue_linux_hdr_size;
	}
	else {
		printf("[WARN] rescue linux header error, fall back to ext_para mode\n");
		rescue_blk_addr = ext_para_ptr->rescue_img_addr;
		imageSize = ext_para_ptr->rescue_img_size;
	}

	if( imageSize == 0 ) {
		printf("[ERR] %s:Rescue image size error!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	printf("#############################\n");
	printf("# Enter Rescue Linux:\n");
	printf("#   secure_mode = %d\n",     secure_mode);
	printf("#   compressed  = %d\n",     mem_layout.bIsCompressed);
	printf("#   block_no    = 0x%08x\n", rescue_blk_addr);
	printf("#   size_bytes  = 0x%08x\n", imageSize);
	printf("#   target_addr = 0x%08x\n", mem_layout.image_target_addr);
	printf("#############################\n");

	from = rescue_blk_addr* (nand->erasesize);	//must define NAND_fw_desc_table_start
	/* copy rescue linux from flash */
	ret = nand->rescue_image_read(nand, (unsigned char *)mem_layout.flash_to_ram_addr, from, imageSize, 0, RESCUE_LINUX_BLOCK_TAG);
	if(ret == 0){
		/* Read success */
		printf("[OK] %s:Read rescue linux ok!!\n", __FUNCTION__);
	}else{
		/* Read error */
		printf("[ERR] %s:Read rescue linux error!!\n", __FUNCTION__);
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	/* if secure mode, do AES CBC decrypt */
	if( secure_mode == RTK_SECURE_BOOT ) {

		printf("to decrypt...\n");

		if (decrypt_image_fpk((char *)mem_layout.encrpyted_addr,
					(char *)mem_layout.decrypted_addr,
					imageSize-rescue_truncated_size
					))
		{
			printf("decrypt image error!\n");
			return RTK_PLAT_ERR_READ_RESCUE_IMG;
		}

		rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32 );

		printf("decrypt rescue successful\n");

#if (0)
		reverse_signature( (unsigned char *)(mem_layout.encrpyted_addr + imageSize - rescue_truncated_size) );

		ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
								  imageSize - rescue_truncated_size,
								  (unsigned char *)(mem_layout.encrpyted_addr + imageSize - rescue_truncated_size), 1 );
		if( ret < 0 )
			rtk_hexdump("the first 32-byte rescue data", (unsigned char *)mem_layout.decrypted_addr, 32 );
#endif
		printf("skip SHA256 check...\n");
		imageSize = imageSize-rescue_truncated_size;
	}
	else
	{
		ret = Verify_SHA256_hash( (unsigned char *)mem_layout.flash_to_ram_addr,
								  imageSize - rescue_truncated_size,
								  (unsigned char *)(mem_layout.flash_to_ram_addr + imageSize - rescue_truncated_size), 0 );

		if( ret < 0 )
			rtk_hexdump("the first 32-byte rescue data", (unsigned char *)mem_layout.flash_to_ram_addr, 32 );

	}

	if( ret < 0 ) {
		printf("[ERR] %s: hash value not match\n", __FUNCTION__ );
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}

	/* if lzma rescue, decompress rescue image to target_addr */
	if (mem_layout.bIsCompressed)
	{
		if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
		{
			printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

			return RTK_PLAT_ERR_READ_KERNEL_IMG;
		}
	}
#endif

	return RTK_PLAT_ERR_OK;
}

/*
 * run rescue from flash (SPI/NAND/eMMC)
 */
int rtk_plat_run_rescue_from_flash(void)
{
#ifndef Board_WATCHDOG_NULL
//	WATCHDOG_disable();
#endif

//:TODO: Remove it in the future
#if 1
	if (ext_para_ptr == NULL)
	{
		printf("[ERR] ext_para_ptr is NULL.\n");
		return RTK_PLAT_ERR_READ_RESCUE_IMG;
	}
#endif

	if (boot_flash_type == BOOT_EMMC)
	{
		/* For eMMC */
		return rtk_plat_run_rescue_from_eMMC();
	}

	if (boot_flash_type == BOOT_NAND)
	{
		/* For NAND */
		return rtk_plat_run_rescue_from_NAND();
	}

	return RTK_PLAT_ERR_OK;
}

/*
 * Use firmware description table to read images from usb.
 */
int rtk_plat_read_fw_image_from_USB(uint bCompressed)
{
#ifdef CONFIG_BOOT_FROM_USB
	uint target_addr = 0;
	char fw_fname[32];
	char cmd[128];
	int ret = 0;
	boot_av_info_t *boot_av;
	uint uncompressedSize = 0;
	uint compressedSize = 0;
	uint uncompressed_target_addr = 0;

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

//////////////////////////////////////////////////////////////////////////

	memset(fw_fname, 0, sizeof(fw_fname));
	if (bCompressed)
	{
		sprintf(fw_fname, "%s.%s", CONFIG_BOOT_FROM_USB_AUDIO_FW_FILENAME, CONFIG_BOOT_FROM_USB_LZMA_EXTNAME);
		target_addr = rtk_mem_info->temp_buffer_for_flash_data_addr;
	}
	else
	{
		strcpy(fw_fname, CONFIG_BOOT_FROM_USB_AUDIO_FW_FILENAME);
		target_addr = MIPS_AUDIO_FW_ENTRY_ADDR;
	}

	printf("########################################################\n");
	if (bCompressed)
		printf("## Audio LZMA FW from USB\n");
	else
		printf("## Audio FW from USB\n");
	printf("##    file_name   = %s\n", fw_fname);
	printf("##    target_addr = 0x%x\n", target_addr);

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "fatload usb 0:1 %x %s", target_addr, fw_fname);

	ret = run_command(cmd, 0);
	if (ret != 0)
	{
		/* Read error */
		printf("[ERR] %s:Read from USB failed. (%s, 0x%x, 0x%x)\n", __FUNCTION__, fw_fname, target_addr, ret);
	}
	else
	{
		/* Read success */
		if (bCompressed)
		{
			printf("## Decompress audio fw using LZMA ...\n");

			uncompressed_target_addr = MIPS_AUDIO_FW_ENTRY_ADDR;
			compressedSize = getenv_ulong("filesize", 16, 0);

			if (compressedSize == 0) {
				printf("[ERR] %s:Get the wrong compressed filesize.\n", __FUNCTION__);
			}
			else {
				printf("##    compressedSize   = 0x%x\n", compressedSize);
				printf("##    target_addr      = 0x%x\n", uncompressed_target_addr);
			}

			if (lzmaBuffToBuffDecompress((uchar*)uncompressed_target_addr, &uncompressedSize, (uchar*)target_addr, compressedSize) != 0)
			{
				/* Decompress error */
				printf("[ERR] %s:Decompress using LZMA error!! (0x%x, 0x%x)\n", __FUNCTION__, target_addr, compressedSize);

				return RTK_PLAT_ERR_READ_FW_IMG;
			}
			else
			{
				/* Decompress success */
				printf("##    uncompressedSize = 0x%x\n", uncompressedSize);
			}

			target_addr = uncompressed_target_addr;
		}

		*AudioFW_entry_ptr = CPU_TO_BE32(target_addr);

		printf("########################################################\n");
		printf("[OK]\n");

	}

//////////////////////////////////////////////////////////////////////////

	memset(fw_fname, 0, sizeof(fw_fname));
	if (bCompressed)
	{
		sprintf(fw_fname, "%s.%s", CONFIG_BOOT_FROM_USB_VIDEO_FW_1_FILENAME, CONFIG_BOOT_FROM_USB_LZMA_EXTNAME);
		target_addr = rtk_mem_info->temp_buffer_for_flash_data_addr;
	}
	else
	{
		strcpy(fw_fname, CONFIG_BOOT_FROM_USB_VIDEO_FW_1_FILENAME);
		target_addr = MIPS_VIDEO_FW_1_ENTRY_ADDR;
	}

	printf("########################################################\n");
	if (bCompressed)
		printf("## Video LZMA FW 1 from USB\n");
	else
		printf("## Video FW 1 from USB\n");
	printf("##    file_name   = %s\n", fw_fname);
	printf("##    target_addr = 0x%x\n", target_addr);

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "fatload usb 0:1 %x %s", target_addr, fw_fname);

	ret = run_command(cmd, 0);
	if (ret != 0)
	{
		/* Read error */
		printf("[ERR] %s:Read from USB failed. (%s, 0x%x, 0x%x)\n", __FUNCTION__, fw_fname, target_addr, ret);
	}
	else
	{
		/* Read success */
		if (bCompressed)
		{
			printf("## Decompress video fw 1 using LZMA ...\n");

			uncompressed_target_addr = MIPS_VIDEO_FW_1_ENTRY_ADDR;
			compressedSize = getenv_ulong("filesize", 16, 0);
			if (compressedSize == 0) {
				printf("[ERR] %s:Get the wrong compressed filesize.\n", __FUNCTION__);
			}
			else {
				printf("##	  compressedSize   = 0x%x\n", compressedSize);
				printf("##	  target_addr	   = 0x%x\n", uncompressed_target_addr);
			}

			if (lzmaBuffToBuffDecompress((uchar*)uncompressed_target_addr, &uncompressedSize, (uchar*)target_addr, compressedSize) != 0)
			{
				/* Decompress error */
				printf("[ERR] %s:Decompress using LZMA error!! (0x%x, 0x%x)\n", __FUNCTION__, target_addr, compressedSize);

				return RTK_PLAT_ERR_READ_FW_IMG;
			}
			else
			{
				/* Decompress success */
				printf("##	  uncompressedSize = 0x%x\n", uncompressedSize);
			}

			target_addr = uncompressed_target_addr;
		}

		*VideoFW_entry_ptr_V1 = CPU_TO_BE32(target_addr);

		printf("########################################################\n");
		printf("[OK]\n");

	}

//////////////////////////////////////////////////////////////////////////

	memset(fw_fname, 0, sizeof(fw_fname));
	if (bCompressed)
	{
		sprintf(fw_fname, "%s.%s", CONFIG_BOOT_FROM_USB_VIDEO_FW_2_FILENAME, CONFIG_BOOT_FROM_USB_LZMA_EXTNAME);
		target_addr = rtk_mem_info->temp_buffer_for_flash_data_addr;
	}
	else
	{
		strcpy(fw_fname, CONFIG_BOOT_FROM_USB_VIDEO_FW_2_FILENAME);
		target_addr = MIPS_VIDEO_FW_2_ENTRY_ADDR;
	}

	printf("########################################################\n");
	if (bCompressed)
		printf("## Video LZMA FW 2 from USB\n");
	else
		printf("## Video FW 2 from USB\n");
	printf("##    file_name   = %s\n", fw_fname);
	printf("##    target_addr = 0x%x\n", target_addr);

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "fatload usb 0:1 %x %s", target_addr, fw_fname);

	ret = run_command(cmd, 0);
	if (ret != 0)
	{
		/* Read error */
		printf("[ERR] %s:Read from USB failed. (%s, 0x%x, 0x%x)\n", __FUNCTION__, fw_fname, target_addr, ret);
	}
	else
	{
		/* Read success */
		if (bCompressed)
		{
			printf("## Decompress video fw 2 using LZMA ...\n");

			uncompressed_target_addr = MIPS_VIDEO_FW_2_ENTRY_ADDR;
			compressedSize = getenv_ulong("filesize", 16, 0);
			if (compressedSize == 0) {
				printf("[ERR] %s:Get the wrong compressed filesize.\n", __FUNCTION__);
			}
			else {
				printf("##	  compressedSize   = 0x%x\n", compressedSize);
				printf("##	  target_addr	   = 0x%x\n", uncompressed_target_addr);
			}

			if (lzmaBuffToBuffDecompress((uchar*)uncompressed_target_addr, &uncompressedSize, (uchar*)target_addr, compressedSize) != 0)
			{
				/* Decompress error */
				printf("[ERR] %s:Decompress using LZMA error!! (0x%x, 0x%x)\n", __FUNCTION__, target_addr, compressedSize);

				return RTK_PLAT_ERR_READ_FW_IMG;
			}
			else
			{
				/* Decompress success */
				printf("##	  uncompressedSize = 0x%x\n", uncompressedSize);
			}

			target_addr = uncompressed_target_addr;
		}

		printf("########################################################\n");
		printf("[OK]\n");

	}

//////////////////////////////////////////////////////////////////////////

#endif

	return RTK_PLAT_ERR_OK;
}


#if IS_ENABLE_STD
/*
 * Use firmware description table to read images from eMMC flash.
 */
int rtk_plat_read_fw_image_from_eMMC_STD(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version,UINT8* Buffer)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
//	char *src;
	fw_desc_entry_v1_t *this_entry;
	fw_desc_entry_v11_t *v11_entry;
	fw_desc_entry_v21_t *v21_entry;
	int i;
	int videoFileNum=0, audioFileNum=0;
//	uint size;
	uint unit_len;
	char buf[64];
	uint fw_checksum = 0;
#if 0 // mark secure boot
	char str_phash[256];
#if defined(Config_Secure_RSA_TRUE)
	char *checksum, *signature;
#endif
	char sha1_hash[SHA1_SIZE];
	char *hash_str;
#endif
	unsigned int secure_mode;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	int ret;
	boot_av_info_t *boot_av;
//	uint source_addr;
//	uint target_addr;
	uint block_no;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint decompressedSize = 0;
	int selV1_V2=0x0;

	mcp_dscpt_addr = 0;

	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH + sizeof(struct image_extra_info);

	/* find fw_entry structure according to version */
	switch (version)
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
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

#if 0 // mark secure boot
#if defined(Config_Secure_RSA_TRUE)
	checksum = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign));
	signature = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign)+1);

	// set RSA key to env variable
	if (env_split_and_save("RSA_KEY_MODULUS", Config_Secure_RSA_MODULUS, 96) != OK)
		return NULL;
#endif
#endif

	if (secure_mode == RTK_SECURE_BOOT)
	{
		// set AES img key to env variable
		setenv( "AES_IMG_KEY", SECURE_KH_KEY_STR);
	}

	//	memset(str_phash, 0, 256);

	if(!g_isSTR)
	{
		/* clear boot_av_info memory */
		boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
		memset(boot_av, 0, sizeof(boot_av_info_t));

		//setup default value
		boot_av->audio_buffer_addr	= SWAPEND32(POWER_ON_MUSIC_BUFFER_ADDR | MIPS_KSEG0BASE);
		boot_av->audio_buffer_size	= SWAPEND32(POWER_ON_MUSIC_BUFFER_SIZE);
		boot_av->video_buffer_addr	= SWAPEND32(POWER_ON_VIDEO_BUFFER_ADDR | MIPS_KSEG0BASE);
		boot_av->video_buffer_size	= SWAPEND32(POWER_ON_VIDEO_BUFFER_SIZE);
		boot_av->last_image_addr	= SWAPEND32(POWER_ON_VIDEO_LAST_IMAGE_ADDR | MIPS_KSEG0BASE);
		boot_av->last_image_size	= SWAPEND32(POWER_ON_VIDEO_LAST_IMAGE_SIZE);
	}

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(1); // insert execute customer callback at here

		this_entry = (fw_desc_entry_v1_t *)(fw_entry + unit_len * i);

		if (this_entry->target_addr)
		{
			switch(this_entry->type)
			{
				case FW_TYPE_AUDIO:
					if (boot_power_on_mode == POWER_OFF)
						continue;

					*AudioFW_entry_ptr = CPU_TO_BE32(this_entry->target_addr);
					printf("Audio FW:\n");
					break;

				case FW_TYPE_VIDEO:
					if (boot_power_on_mode == POWER_OFF)
                  continue;

					*VideoFW_entry_ptr_V1 = CPU_TO_BE32(this_entry->target_addr);
					printf("Video FW 1:\n");
					selV1_V2|=0x01;
					break;

				case FW_TYPE_KCPU:
					if (boot_power_on_mode == POWER_OFF)
                  continue;

					printf("KCPU FW:\n");
					*KcpuFW_entry_ptr = this_entry->target_addr;
					break;

				case FW_TYPE_ECPU:
					continue;	// Aux code copy ECPU image to DDR

				default:
					continue;
			}

			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
				this_entry->target_addr, this_entry->length, this_entry->target_addr + this_entry->length);

			printf("\t FW Image fr 0x%08x %s\n", eMMC_fw_desc_table_start + this_entry->offset, this_entry->lzma ? "(lzma)" : "(non-lzma)");

			WATCHDOG_KICK();

			if (this_entry->type != FW_TYPE_KERNEL)
			{
				/* secure mode and lzma will only apply to fw image */
				if (this_entry->type == FW_TYPE_AUDIO ||
					this_entry->type == FW_TYPE_VIDEO ||
					this_entry->type == FW_TYPE_VIDEO_2 ||
					this_entry->type == FW_TYPE_ECPU ||
					this_entry->type == FW_TYPE_KCPU)
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = this_entry->lzma;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}

				get_mem_layout_when_read_image(&mem_layout);

				/* read image from flash */
				mem_layout.flash_to_ram_addr -= (this_entry->offset % EMMC_BLOCK_SIZE);

				imageSize = this_entry->length;

				block_no = (eMMC_fw_desc_table_start + this_entry->offset) / EMMC_BLOCK_SIZE ;

				if (!rtk_eMMC_read(block_no, imageSize, (uint *)mem_layout.flash_to_ram_addr))
				{
					printf("[ERR] Read fw error (type:%d)!\n", this_entry->type);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}

				/* Check checksum */
				fw_checksum = get_checksum((uchar *)mem_layout.flash_to_ram_addr, imageSize);

				if (this_entry->checksum != fw_checksum)
				{
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n", this_entry->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
				}

				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
						rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
						//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(rtk_mem_info->encrypted_fw_image_addr+this_entry->length-512), 512);

						// decrypt image
						printf("to decrypt...\n");
						if (decrypt_image_fpk((char *)mem_layout.encrpyted_addr,
							(char *)mem_layout.decrypted_addr,
							imageSize-img_truncated_size
							))
						{
							printf("decrypt image(%d) error!\n", this_entry->type);
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);
#if (0)
						reverse_signature( (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size) );

						ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
												  imageSize - img_truncated_size,
												  (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size),
												  1 );
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}
#endif
						printf("skip SHA256 check...\n");
						imageSize = imageSize - img_truncated_size;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
			}
		}

		if (version == FW_DESC_TABLE_V1_T_VERSION_11)
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
		else if (version == FW_DESC_TABLE_V1_T_VERSION_21)
		{
			v21_entry = (fw_desc_entry_v21_t *)this_entry;

#if defined(Config_Secure_RSA_TRUE)
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
				//printf("[DEBUG_MSG] part_num:%x, act_size:%x, recovered hash:%s\n", v21_entry->part_num, v21_entry->act_size, checksum);
			}
#endif	/* defined(Config_Secure_RSA_TRUE) */
		}
	}

	/* Flush caches */
	flush_dcache_all();

	if (check_image()) {
		// invalid image
		return RTK_PLAT_ERR_READ_FW_IMG;
	}

	do_go_audio_fw();
	do_go_video_fw(selV1_V2);

	if(g_isSTR)
	{
		//jump to STR address!!
		GoFuncPtr=(UINT32*)g_goAddr;
		rtd_outl(REG_STR_JUMP_ADDR_reg,0);
		g_isSTR=0;
		cleanup_before_linux();
		printf("STR go address 0x%x\n",g_goAddr);
		(*GoFuncPtr)();
	}


		if(processImg_STDAnimation(Buffer)==-1)
			{
						printf("STD data fail..\n");
						return NULL;
			}
		else
		{
			/** jump to linux kernel **/

			EXECUTE_CUSTOMIZE_FUNC(1); // insert execute customer callback at here

			//Reset ethernet
			cmd_boot_rtd_outl(0xb8016234, 0x0);
			cmd_boot_rtd_outl(0xb801603c, 0xffff);
			cmd_boot_rtd_outl(0xb8016038, 0x1);

			//Disable UART0/UART1
		#define ISO_MISC_OFF_INT_EN_reg 			 0xB8062108
		#define SCPU_INT_EN_reg     				 0xB801B080
        #define BIT(x) (1<<(x))
		   rtd_outl(ISO_MISC_OFF_INT_EN_reg,BIT(2));
		   rtd_outl(SCPU_INT_EN_reg,BIT(3));
		   rtd_outl(SCPU_INT_EN_reg,BIT(4));
		   rtd_outl(SCPU_INT_EN_reg,BIT(5));



			printf("0xb8016234 : 0x%x\n",cmd_boot_rtd_inl(0xb8016234));
			printf("0xb801603c : 0x%x\n",cmd_boot_rtd_inl(0xb801603c));
			printf("0xb8016038 : 0x%x\n",cmd_boot_rtd_inl(0xb8016038));



			//#ifdef CONFIG_USB_DEVICE
			//udc_disconnect();
			//#endif
			cleanup_before_linux();
			printf("Ready to go STD kernel address[0x%x]!!!\n",g_goAddr);
			if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE)
    		{
				(*GoFuncPtr)();
			}
			else
				return RTK_PLAT_ERR_OK;
			return NULL;
		}
#endif	//CONFIG_SYS_RTK_EMMC_FLASH

	return RTK_PLAT_ERR_OK;
}
#endif	//IS_ENABLE_STD

/*
 * Use firmware description table to read images from eMMC flash.
 */
int rtk_plat_read_fw_image_from_eMMC(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
//	char *src;
	fw_desc_entry_v1_t *this_entry;
	fw_desc_entry_v11_t *v11_entry;
#if defined(Config_Secure_RSA_TRUE)
	fw_desc_entry_v21_t *v21_entry;
#endif
	int i;
	int videoFileNum=0, audioFileNum=0;
//	uint size;
	uint unit_len;
	char buf[64];
	uint fw_checksum = 0;
#if 0 // mark secure boot
	char str_phash[256];
#if defined(Config_Secure_RSA_TRUE)
	char *checksum, *signature;
#endif
	char sha1_hash[SHA1_SIZE];
	char *hash_str;
#endif
	unsigned int secure_mode;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	int ret;
	boot_av_info_t *boot_av;
//	uint source_addr;
//	uint target_addr;
	uint block_no;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint decompressedSize = 0;
	uint bootfile_length = 0;

	mcp_dscpt_addr = 0;


	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH + sizeof(struct image_extra_info);

	/* find fw_entry structure according to version */
	switch (version)
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
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

#if 0 // mark secure boot
#if defined(Config_Secure_RSA_TRUE)
	checksum = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign));
	signature = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign)+1);

	// set RSA key to env variable
	if (env_split_and_save("RSA_KEY_MODULUS", Config_Secure_RSA_MODULUS, 96) != OK)
		return NULL;
#endif
#endif

	if (secure_mode == RTK_SECURE_BOOT)
	{
		// set AES img key to env variable
		setenv( "AES_IMG_KEY", SECURE_KH_KEY_STR);
	}

	//	memset(str_phash, 0, 256);

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	//setup default value
	boot_av->audio_buffer_addr	= SWAPEND32(POWER_ON_MUSIC_BUFFER_ADDR | MIPS_KSEG0BASE);
	boot_av->audio_buffer_size	= SWAPEND32(POWER_ON_MUSIC_BUFFER_SIZE);
	boot_av->video_buffer_addr	= SWAPEND32(POWER_ON_VIDEO_BUFFER_ADDR | MIPS_KSEG0BASE);
	boot_av->video_buffer_size	= SWAPEND32(POWER_ON_VIDEO_BUFFER_SIZE);
	boot_av->last_image_addr	= SWAPEND32(POWER_ON_VIDEO_LAST_IMAGE_ADDR | MIPS_KSEG0BASE);
	boot_av->last_image_size	= SWAPEND32(POWER_ON_VIDEO_LAST_IMAGE_SIZE);

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_desc_entry_v1_t *)(fw_entry + unit_len * i);

		if (this_entry->target_addr)
		{
			switch(this_entry->type)
			{
				case FW_TYPE_BOOTCODE:
					printf("Boot Code:\n");
					break;

				case FW_TYPE_KERNEL:
					kernel_entry = this_entry;
					printf("Linux Kernel:\n");
					break;

				case FW_TYPE_AUDIO:
					if (boot_power_on_mode == POWER_ON)
					{
						*AudioFW_entry_ptr = CPU_TO_BE32(this_entry->target_addr);
					}
					else
					{
						*AudioFW_entry_ptr = 0;
					}
					printf("Audio FW:\n");
					break;

				case FW_TYPE_VIDEO:
					if (boot_power_on_mode == POWER_ON)
					{
						*VideoFW_entry_ptr_V1 = CPU_TO_BE32(this_entry->target_addr);
					}
					else
					{
						*VideoFW_entry_ptr_V1 = 0;
					}
					printf("Video FW 1:\n");
					break;

				case FW_TYPE_KCPU:
					printf("KCPU FW:\n");
					*KcpuFW_entry_ptr = this_entry->target_addr;
					break;

				case FW_TYPE_ECPU:
					continue;	// Aux code copy ECPU image to DDR

				case FW_TYPE_JFFS2:
					printf("JFFS2 Image:\n");
					break;

				case FW_TYPE_SQUASH:
					printf("Squash Image:\n");
					break;

				case FW_TYPE_EXT3:
					printf("EXT3 Image:\n");
					break;

				case FW_TYPE_ODD:
					printf("ODD Image:\n");
					break;

				case FW_TYPE_YAFFS2:
					printf("YAFFS2 Image:\n");
					break;

				case FW_TYPE_AUDIO_FILE:
					this_entry->target_addr = (POWER_ON_MUSIC_STREAM_ADDR | MIPS_KSEG0BASE);
					audioFileNum++;

					printf("Audio data %d:\n", audioFileNum);

					switch(audioFileNum)
					{
						case 1:
							if ((boot_music_enable != 1) )
								continue;
							break;

						case 2:
							if ((boot_music_enable != 2) )
								continue;
							break;

						case 3:
							if ((boot_music_enable != 3) )
								continue;
							break;

						default:
							continue;
					}

					/* if enable boot music, need to assign boot_av structure */
					if (boot_music_enable && (boot_power_on_mode == POWER_ON))
					{
						if (boot_music_enable==2 && custom_audio1_length != 0)
						{
							bootfile_length = custom_audio1_length;
						}
						else if (boot_music_enable==3 && custom_audio2_length != 0)
						{
							bootfile_length = custom_audio2_length;
						}
						else
						{
							bootfile_length = this_entry->length;
						}

						/* check bootfile size that prevent memory overlap */
						if (bootfile_length > POWER_ON_MUSIC_STREAM_SIZE)
						{
							printf("[Warn] Audio data length is %x > %x, skip this entry\n",
								bootfile_length,
								POWER_ON_MUSIC_STREAM_SIZE);

							continue;
						}
						else
						{
							/* pass */
							boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
							boot_av->dwAudioStreamAddress = SWAPEND32(this_entry->target_addr);
							boot_av->dwAudioStreamLength = SWAPEND32(bootfile_length);
#ifdef CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC//20140506  xq_xiao
							if ( bootparam.konka_boot_vol != 0 )
								boot_av->dwAudioStreamVolume = (bootparam.konka_boot_vol-60);
							else
								boot_av->dwAudioStreamVolume = (-17);
#else
							boot_av->dwAudioStreamVolume = (-17);
#endif

							this_entry->length = bootfile_length;
						}

					}

					break;

				case FW_TYPE_VIDEO_FILE:
					this_entry->target_addr = (POWER_ON_VIDEO_STREAM_ADDR | MIPS_KSEG0BASE);
					videoFileNum++;

					printf("Video data %d:\n", videoFileNum);

					switch(videoFileNum)
					{
						case 1:
							if ((boot_logo_enable != 1) )
								continue;
							break;

						case 2:
							if ((boot_logo_enable != 2) )
								continue;
							break;

						case 3:
							if ((boot_logo_enable != 3) )
								continue;
							break;

						default:
							continue;
					}

					/* if enable boot video/jpeg, need to assign boot_av structure */
					if (boot_logo_enable && (boot_power_on_mode == POWER_ON))
					{
						if (boot_logo_enable == 2 && custom_video1_length != 0)
						{
							bootfile_length = custom_video1_length;
						}
						else if (boot_logo_enable == 3 && custom_video2_length != 0)
						{
							bootfile_length = custom_video2_length;
						}
						else
						{
							bootfile_length = this_entry->length;
						}

						/* check bootfile size that prevent memory overlap */
						if (bootfile_length > POWER_ON_VIDEO_STREAM_SIZE)
						{
							printf("[Warn] Video data length is %x > %x, skip this entry\n",
								bootfile_length,
								POWER_ON_VIDEO_STREAM_SIZE);

							continue;
						}
						else
						{
							/* pass */
							boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
							boot_av->dwVideoStreamAddress = SWAPEND32(this_entry->target_addr);
							boot_av->dwVideoStreamLength = SWAPEND32(bootfile_length);
							boot_av->bPowerOnImage = 0;

							if(vFlipEnable)
								boot_av->bRotate = 1;
							else
								boot_av->bRotate = 0;

							this_entry->length = bootfile_length;
						}

					}
					break;

				case FW_TYPE_IMAGE_FILE:
					this_entry->target_addr = (POWER_ON_VIDEO_STREAM_ADDR | MIPS_KSEG0BASE);
					videoFileNum++;

					printf("Video[image] data %d:\n", videoFileNum);

					switch(videoFileNum)
					{
						case 1:
							if ((boot_logo_enable != 1) )
								continue;
							break;

						case 2:
							if ((boot_logo_enable != 2) )
								continue;
							break;

						case 3:
							if ((boot_logo_enable != 3) )
								continue;
							break;

						default:
							continue;
					}

					/* if enable boot video/jpeg, need to assign boot_av structure */
					if (boot_logo_enable && (boot_power_on_mode == POWER_ON))
					{
						if (boot_logo_enable == 2 && custom_video1_length != 0)
						{
							bootfile_length = custom_video1_length;
						}
						else if (boot_logo_enable == 3 && custom_video2_length != 0)
						{
							bootfile_length = custom_video2_length;
						}
						else
						{
							bootfile_length = this_entry->length;
						}

						/* check bootfile size that prevent memory overlap */
						if (bootfile_length > POWER_ON_VIDEO_STREAM_SIZE)
						{
							printf("[Warn] Video[image] data length is %x > %x, skip this entry\n",
								bootfile_length,
								POWER_ON_VIDEO_STREAM_SIZE);

							continue;
						}
						else
						{
							/* pass */
							boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
							boot_av->dwVideoStreamAddress = SWAPEND32(this_entry->target_addr);
							boot_av->dwVideoStreamLength = SWAPEND32(bootfile_length);
							boot_av->bPowerOnImage = 1;

							if(vFlipEnable)
								boot_av->bRotate = 1;
							else
								boot_av->bRotate = 0;

							this_entry->length = bootfile_length;
						}

					}
					break;

				default:
					printf("Unknown FW (%d):\n", this_entry->type);
					break;
			}

			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
				this_entry->target_addr, this_entry->length, this_entry->target_addr + this_entry->length);

			printf("\t FW Image fr 0x%08x %s\n", eMMC_fw_desc_table_start + this_entry->offset, this_entry->lzma ? "(lzma)" : "(non-lzma)");

			if (this_entry->length == 0)
			{
				printf("\t FW Image size is zero, skip this entry\n");
				continue;
			}

			WATCHDOG_KICK();

			// if enter standby, load kernel and ecpu.bin only
			if ((boot_power_on_mode == POWER_OFF) && this_entry->type != FW_TYPE_ECPU && this_entry->type != FW_TYPE_KERNEL)
			{
				printf("\t Enter standby, skip this entry\n");
				continue;
			}

			if (this_entry->type != FW_TYPE_KERNEL)
			{
				/* secure mode and lzma will only apply to fw image */
				if (this_entry->type == FW_TYPE_AUDIO ||
					this_entry->type == FW_TYPE_VIDEO ||
					this_entry->type == FW_TYPE_VIDEO_2 ||
					this_entry->type == FW_TYPE_ECPU ||
					this_entry->type == FW_TYPE_KCPU)
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = this_entry->lzma;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}

				get_mem_layout_when_read_image(&mem_layout);

				/* read image from flash */
				mem_layout.flash_to_ram_addr -= (this_entry->offset % EMMC_BLOCK_SIZE);

				imageSize = this_entry->length;

				block_no = (eMMC_fw_desc_table_start + this_entry->offset) / EMMC_BLOCK_SIZE ;

				if (!rtk_eMMC_read(block_no, imageSize, (uint *)mem_layout.flash_to_ram_addr))
				{
					printf("[ERR] Read fw from emmc error (block_no:%d)\n", block_no);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}

				/* Check checksum */
				fw_checksum = get_checksum((uchar *)mem_layout.flash_to_ram_addr, imageSize);

				if (this_entry->checksum != fw_checksum)
				{
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n", this_entry->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
				}

				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
						rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
						//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(rtk_mem_info->encrypted_fw_image_addr+this_entry->length-512), 512);

						// decrypt image
						printf("to decrypt...\n");
						if (decrypt_image_fpk((char *)mem_layout.encrpyted_addr,
							(char *)mem_layout.decrypted_addr,
							imageSize-img_truncated_size
							))
						{
							printf("decrypt image(%d) error!\n", this_entry->type);
							return RTK_PLAT_ERR_READ_FW_IMG;
						}

						rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

#if (0)
						reverse_signature( (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size) );

						ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
												  imageSize - img_truncated_size,
												  (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size),
												  1 );
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}
#endif
						printf("skip SHA256 check...\n");
						imageSize = imageSize - img_truncated_size;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
			}

		}

		if (version == FW_DESC_TABLE_V1_T_VERSION_11)
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
		else if (version == FW_DESC_TABLE_V1_T_VERSION_21)
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
				//printf("[DEBUG_MSG] part_num:%x, act_size:%x, recovered hash:%s\n", v21_entry->part_num, v21_entry->act_size, checksum);
			}
#endif	/* defined(Config_Secure_RSA_TRUE) */
		}
	}

#if 0 // logo
#ifndef Logo_Source_NULL
	/* Set logo */
	LOGO_DISP_init();
#endif
#endif

	if (check_image()) {
		// invalid image
#if 0
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled)
		return run_rescue_from_usb(RESCUE_LINUX_FILE_NAME);
#elif defined(Rescue_Source_FLASH)
#if defined(Logo_Source_FLASH)
#if defined(Logo6_Source_FLASH)
		LOGO_DISP_change(5);
#endif
#endif
		return run_rescue_from_flash();
#else
		return NULL;
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
#else
		return RTK_PLAT_ERR_READ_FW_IMG;
#endif
	}

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		*boot_av_info_ptr = SWAPEND32((uint) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

#if 0 // factory
	//if DC on, need check if save factory bootPowerOn or not. if save, spend 100ms.
	factory_info_set_BootPowerOn();
	display_evaluate_time("factory_info_set_BootPowerOn");
#endif

#if 0 // delay
/* 1. Wait 15ms to avoid the distortion of messages from A/V cpu.
 * 2. Discard SCPU_CLK90K_HI(0x1801b544) for simplicity.
 * 3. Show the value in seconds.
 */
	{
		unsigned int counter;

		sys_wait_ms(15);
		counter = REG32(MIS_SCPU_CLK90K_LO);
		counter /= 90; /* in milliseconds */
		printf("SCPU_CLK90K=%d.%03d sec.\n", counter/1000, counter%1000);
	}
#endif

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_EMMC_FLASH */

	return RTK_PLAT_ERR_OK;
}

/*
 * Use firmware description table to read images from NAND flash.
 */
int rtk_plat_read_fw_image_from_NAND(
		uint fw_desc_table_base, part_desc_entry_v1_t* part_entry, int part_count,
		void* fw_entry, int fw_count,
		uchar version)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from;
	unsigned int retlen;

//	char *src;
	fw_desc_entry_v1_t *this_entry;
	fw_desc_entry_v11_t *v11_entry;
#if defined(Config_Secure_RSA_TRUE)
	fw_desc_entry_v21_t *v21_entry;
#endif
	int i;
	int videoFileNum=0, audioFileNum=0;
//	uint size;
	uint unit_len;
	char buf[64];
	uint fw_checksum = 0;
#if 0 // mark secure boot
	char str_phash[256];
#if defined(Config_Secure_RSA_TRUE)
	char *checksum, *signature;
#endif
	char sha1_hash[SHA1_SIZE];
	char *hash_str;
#endif
	unsigned int secure_mode;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;
	unsigned int img_truncated_size; // install_a will append 256-byte signature data to it
	int ret;
	boot_av_info_t *boot_av;
//	uint source_addr;
//	uint target_addr;
	uint block_no;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	uint imageSize = 0;
	uint decompressedSize = 0;
	uint bootfile_length = 0;

	mcp_dscpt_addr = 0;

	secure_mode = rtk_get_secure_boot_type();
	img_truncated_size = RSA_SIGNATURE_LENGTH + sizeof(struct image_extra_info);

	/* find fw_entry structure according to version */
	switch (version)
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
			return RTK_PLAT_ERR_READ_FW_IMG;
	}

#if 0 // mark secure boot
#if defined(Config_Secure_RSA_TRUE)
	checksum = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign));
	signature = (char *)alloc_freemem(sizeof(v21_entry->RSA_sign)+1);

	// set RSA key to env variable
	if (env_split_and_save("RSA_KEY_MODULUS", Config_Secure_RSA_MODULUS, 96) != OK)
		return NULL;
#endif
#endif

	if (secure_mode == RTK_SECURE_BOOT)
	{
		// set AES img key to env variable
		setenv( "AES_IMG_KEY", SECURE_KH_KEY_STR);
	}

	//	memset(str_phash, 0, 256);

	/* clear boot_av_info memory */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	memset(boot_av, 0, sizeof(boot_av_info_t));

	//setup default value
	boot_av->audio_buffer_addr	= SWAPEND32(POWER_ON_MUSIC_BUFFER_ADDR | MIPS_KSEG0BASE);
	boot_av->audio_buffer_size	= SWAPEND32(POWER_ON_MUSIC_BUFFER_SIZE);
	boot_av->video_buffer_addr	= SWAPEND32(POWER_ON_VIDEO_BUFFER_ADDR | MIPS_KSEG0BASE);
	boot_av->video_buffer_size	= SWAPEND32(POWER_ON_VIDEO_BUFFER_SIZE);
	boot_av->last_image_addr	= SWAPEND32(POWER_ON_VIDEO_LAST_IMAGE_ADDR | MIPS_KSEG0BASE);
	boot_av->last_image_size	= SWAPEND32(POWER_ON_VIDEO_LAST_IMAGE_SIZE);

	/* parse each fw_entry */
	for (i = 0; i < fw_count; i++)
	{
		EXECUTE_CUSTOMIZE_FUNC(0); // insert execute customer callback at here

		this_entry = (fw_desc_entry_v1_t *)(fw_entry + unit_len * i);

		if (this_entry->target_addr)
		{
			switch(this_entry->type)
			{
				case FW_TYPE_BOOTCODE:
					printf("Boot Code:\n");
					break;

				case FW_TYPE_KERNEL:
					kernel_entry = this_entry;
					printf("Linux Kernel:\n");
					break;

				case FW_TYPE_AUDIO:
					if (boot_power_on_mode == POWER_ON || boot_power_on_mode == BACKLIGHT_OFF )
					{
						*AudioFW_entry_ptr = CPU_TO_BE32(this_entry->target_addr);
					}
					else
					{
						*AudioFW_entry_ptr = 0;
					}
					printf("Audio FW:\n");
					break;

				case FW_TYPE_VIDEO:
					if (boot_power_on_mode == POWER_ON || boot_power_on_mode == BACKLIGHT_OFF )
					{
						*VideoFW_entry_ptr_V1 = CPU_TO_BE32(this_entry->target_addr);
					}
					else
					{
						*VideoFW_entry_ptr_V1 = 0;
					}
					printf("Video FW 1:\n");
					break;

				case FW_TYPE_KCPU:
					printf("KCPU FW:\n");
					*KcpuFW_entry_ptr = this_entry->target_addr;
#ifdef CONFIG_KCPU_LOAD_K_FW
					printf("(skip)\n");
					continue;
#else
					break;
#endif

				case FW_TYPE_ECPU:
					continue;	// Aux code copy ECPU image to DDR

				case FW_TYPE_JFFS2:
					printf("JFFS2 Image:\n");
					break;

				case FW_TYPE_SQUASH:
					printf("Squash Image:\n");
					break;

				case FW_TYPE_EXT3:
					printf("EXT3 Image:\n");
					break;

				case FW_TYPE_ODD:
					printf("ODD Image:\n");
					break;

				case FW_TYPE_YAFFS2:
					printf("YAFFS2 Image:\n");
					break;

				case FW_TYPE_AUDIO_FILE:
					this_entry->target_addr = (POWER_ON_MUSIC_STREAM_ADDR | MIPS_KSEG0BASE);
					audioFileNum++;

					printf("Audio data %d:\n", audioFileNum);

					switch(audioFileNum)
					{
						case 1:
							if ((boot_music_enable != 1) )
								continue;
							break;

						case 2:
							if ((boot_music_enable != 2) )
								continue;
							break;

						case 3:
							if ((boot_music_enable != 3) )
								continue;
							break;

						default:
							continue;
					}

					/* if enable boot music, need to assign boot_av structure */
					if (boot_music_enable && (boot_power_on_mode == POWER_ON || boot_power_on_mode == BACKLIGHT_OFF ))
					{
						if (boot_music_enable==2 && custom_audio1_length != 0)
						{
							bootfile_length = custom_audio1_length;
						}
						else if (boot_music_enable==3 && custom_audio2_length != 0)
						{
							bootfile_length = custom_audio2_length;
						}
						else
						{
							bootfile_length = this_entry->length;
						}

						/* check bootfile size that prevent memory overlap */
						if (bootfile_length > POWER_ON_MUSIC_STREAM_SIZE)
						{
							printf("[Warn] Audio data length is %x > %x, skip this entry\n",
								bootfile_length,
								POWER_ON_MUSIC_STREAM_SIZE);

							continue;
						}
						else
						{
							/* pass */
							boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
							boot_av->dwAudioStreamAddress = SWAPEND32(this_entry->target_addr);
							boot_av->dwAudioStreamLength = SWAPEND32(bootfile_length);
#ifdef CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC//20140506  xq_xiao
							if ( bootparam.konka_boot_vol != 0 )
								boot_av->dwAudioStreamVolume = (bootparam.konka_boot_vol-60);
							else
								boot_av->dwAudioStreamVolume = (-17);
#else
							boot_av->dwAudioStreamVolume = (-17);
#endif

							this_entry->length = bootfile_length;
						}

					}

					break;

				case FW_TYPE_VIDEO_FILE:
					this_entry->target_addr = (POWER_ON_VIDEO_STREAM_ADDR | MIPS_KSEG0BASE);
					videoFileNum++;

					printf("Video data %d:\n", videoFileNum);

					switch(videoFileNum)
					{
						case 1:
							if ((boot_logo_enable != 1) )
								continue;
							break;

						case 2:
							if ((boot_logo_enable != 2) )
								continue;
							break;

						case 3:
							if ((boot_logo_enable != 3) )
								continue;
							break;

						default:
							continue;
					}

					/* if enable boot video/jpeg, need to assign boot_av structure */
					if (boot_logo_enable && (boot_power_on_mode == POWER_ON || boot_power_on_mode == BACKLIGHT_OFF ))
					{
						if (boot_logo_enable == 2 && custom_video1_length != 0)
						{
							bootfile_length = custom_video1_length;
						}
						else if (boot_logo_enable == 3 && custom_video2_length != 0)
						{
							bootfile_length = custom_video2_length;
						}
						else
						{
							bootfile_length = this_entry->length;
						}

						/* check bootfile size that prevent memory overlap */
						if (bootfile_length > POWER_ON_VIDEO_STREAM_SIZE)
						{
							printf("[Warn] Video data length is %x > %x, skip this entry\n",
								bootfile_length,
								POWER_ON_VIDEO_STREAM_SIZE);

							continue;
						}
						else
						{
							/* pass */
							boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
							boot_av->dwVideoStreamAddress = SWAPEND32(this_entry->target_addr);
							boot_av->dwVideoStreamLength = SWAPEND32(bootfile_length);
							boot_av->bPowerOnImage = 0;

							if(vFlipEnable)
								boot_av->bRotate = 1;
							else
								boot_av->bRotate = 0;

							this_entry->length = bootfile_length;
						}

					}
					break;

				case FW_TYPE_IMAGE_FILE:
					this_entry->target_addr = (POWER_ON_VIDEO_STREAM_ADDR | MIPS_KSEG0BASE);
					videoFileNum++;

					printf("Video[image] data %d:\n", videoFileNum);

					switch(videoFileNum)
					{
						case 1:
							if ((boot_logo_enable != 1) )
								continue;
							break;

						case 2:
							if ((boot_logo_enable != 2) )
								continue;
							break;

						case 3:
							if ((boot_logo_enable != 3) )
								continue;
							break;

						default:
							continue;
					}

					/* if enable boot video/jpeg, need to assign boot_av structure */
					if (boot_logo_enable && (boot_power_on_mode == POWER_ON || boot_power_on_mode == BACKLIGHT_OFF ))
					{
						if (boot_logo_enable == 2 && custom_video1_length != 0)
						{
							bootfile_length = custom_video1_length;
						}
						else if (boot_logo_enable == 3 && custom_video2_length != 0)
						{
							bootfile_length = custom_video2_length;
						}
						else
						{
							bootfile_length = this_entry->length;
						}

						/* check bootfile size that prevent memory overlap */
						if (bootfile_length > POWER_ON_VIDEO_STREAM_SIZE)
						{
							printf("[Warn] Video[image] data length is %x > %x, skip this entry\n",
								bootfile_length,
								POWER_ON_VIDEO_STREAM_SIZE);

							continue;
						}
						else
						{
							/* pass */
							boot_av->dwMagicNumber = SWAPEND32(BOOT_AV_INFO_MAGICNO);
							boot_av->dwVideoStreamAddress = SWAPEND32(this_entry->target_addr);
							boot_av->dwVideoStreamLength = SWAPEND32(bootfile_length);
							boot_av->bPowerOnImage = 1;

							if(vFlipEnable)
								boot_av->bRotate = 1;
							else
								boot_av->bRotate = 0;

							this_entry->length = bootfile_length;
						}

					}
					break;

				default:
					printf("Unknown FW (%d):\n", this_entry->type);
					break;
			}

			printf("\t FW Image to 0x%08x, size=0x%08x (0x%08x)\n",
				this_entry->target_addr, this_entry->length, this_entry->target_addr + this_entry->length);

			printf("\t FW Image fr 0x%08x %s\n", NAND_fw_desc_table_start + this_entry->offset, this_entry->lzma ? "(lzma)" : "(non-lzma)");

			if (this_entry->length == 0)
			{
				printf("\t FW Image size is zero, skip this entry\n");
				continue;
			}

			WATCHDOG_KICK();

			// if enter standby, load kernel and ecpu.bin only
			if ((boot_power_on_mode == POWER_OFF) && this_entry->type != FW_TYPE_ECPU && this_entry->type != FW_TYPE_KERNEL)
			{
				printf("\t Enter standby, skip this entry\n");
				continue;
			}

			if (this_entry->type != FW_TYPE_KERNEL)
			{
				/* secure mode and lzma will only apply to fw image */
				if (this_entry->type == FW_TYPE_AUDIO ||
					this_entry->type == FW_TYPE_VIDEO ||
					this_entry->type == FW_TYPE_VIDEO_2 ||
					this_entry->type == FW_TYPE_ECPU ||
					this_entry->type == FW_TYPE_KCPU)
				{
					/* get memory layout before copy fw image */
					mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
					mem_layout.bIsCompressed = this_entry->lzma;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}
				else
				{
					/* get memory layout before copy other image */
					mem_layout.bIsEncrypted = 0;
					mem_layout.bIsCompressed = 0;
					mem_layout.image_target_addr = this_entry->target_addr & (~MIPS_KSEG_MSK);
				}

				get_mem_layout_when_read_image(&mem_layout);

				/* read image from flash */
#if 0
				mem_layout.flash_to_ram_addr -= (this_entry->offset % EMMC_BLOCK_SIZE);

				imageSize = this_entry->length;

				block_no = (eMMC_fw_desc_table_start + this_entry->offset) / EMMC_BLOCK_SIZE ;

				if (!rtk_eMMC_read(block_no, imageSize, (uint *)mem_layout.flash_to_ram_addr))
				{
					printf("[ERR] Read fw from emmc error (block_no:%d)\n", block_no);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}
#else
				from = NAND_fw_desc_table_start + this_entry->offset;
				imageSize = this_entry->length;
				mem_layout.flash_to_ram_addr -= (this_entry->offset % nand->erasesize);
				get_flash_shared_semaphore();
				nand->read(nand, from, imageSize, &retlen, (uint *)mem_layout.flash_to_ram_addr);
				release_flash_shared_semaphore();
				if (retlen != imageSize)
				{
					/* Read error */
					printf("[ERR] %s:Read fw error!!\n", __FUNCTION__);

					return RTK_PLAT_ERR_READ_FW_IMG;
				}else
				{
					/* Read success */
					printf("[OK] %s:Read fw ok!!\n", __FUNCTION__);
				}

#endif
				/* Check checksum */
				fw_checksum = get_checksum((uchar *)mem_layout.flash_to_ram_addr, imageSize);

				if (this_entry->checksum != fw_checksum)
				{
					printf("\t FW Image checksum FAILED\n");
					printf("\t FW Image entry  checksum=0x%08x\n", this_entry->checksum);
					printf("\t FW Image result checksum=0x%08x\n", fw_checksum);
				}

				/* if secure mode, do AES CBC decrypt */
				if (mem_layout.bIsEncrypted)
				{
					if (secure_mode == RTK_SECURE_BOOT)
					{
						rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
						//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(rtk_mem_info->encrypted_fw_image_addr+this_entry->length-512), 512);

						// decrypt image
						printf("to decrypt...\n");
						if (decrypt_image_fpk((char *)mem_layout.encrpyted_addr,
							(char *)mem_layout.decrypted_addr,
							imageSize-img_truncated_size
							))
						{
							printf("decrypt image(%d) error!\n", this_entry->type);
							return RTK_PLAT_ERR_READ_FW_IMG;
						}


#if (0)
						reverse_signature( (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size) );

						ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
												  imageSize - img_truncated_size,
												  (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size),
												  1 );
						if( ret < 0 ) {
							printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
							return RTK_PLAT_ERR_READ_FW_IMG;
						}
#endif
						printf("skip SHA256 check...\n");
						imageSize = imageSize - img_truncated_size;
					}
				}

				/* if lzma type, decompress image */
				if (mem_layout.bIsCompressed)
				{
					if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
					{
						printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

						return RTK_PLAT_ERR_READ_FW_IMG;
					}
				}
			}

		}

		if (version == FW_DESC_TABLE_V1_T_VERSION_11)
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
		else if (version == FW_DESC_TABLE_V1_T_VERSION_21)
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
				//printf("[DEBUG_MSG] part_num:%x, act_size:%x, recovered hash:%s\n", v21_entry->part_num, v21_entry->act_size, checksum);
			}
#endif	/* defined(Config_Secure_RSA_TRUE) */
		}
	}

#if 0 // logo
#ifndef Logo_Source_NULL
	/* Set logo */
	LOGO_DISP_init();
#endif
#endif

	if (check_image()) {
		// invalid image
#if 0
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled)
		return run_rescue_from_usb(RESCUE_LINUX_FILE_NAME);
#elif defined(Rescue_Source_FLASH)
#if defined(Logo_Source_FLASH)
#if defined(Logo6_Source_FLASH)
		LOGO_DISP_change(5);
#endif
#endif
		return run_rescue_from_flash();
#else
		return NULL;
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
#else
		return RTK_PLAT_ERR_READ_FW_IMG;
#endif
	}

	/* set boot_av_info_ptr */
	if (boot_av->dwMagicNumber == SWAPEND32(BOOT_AV_INFO_MAGICNO))
	{
		boot_av->bHDMImode = sys_logo_is_HDMI;

		// enable audio sound
		if (boot_av->dwAudioStreamLength != 0)
		{
			;
		}

		*boot_av_info_ptr = SWAPEND32((uint) boot_av);

		#ifdef DUBUG_BOOT_AV_INFO
		dump_boot_av_info(boot_av);
		#endif
	}

#if 0 // factory
	//if DC on, need check if save factory bootPowerOn or not. if save, spend 100ms.
	factory_info_set_BootPowerOn();
	display_evaluate_time("factory_info_set_BootPowerOn");
#endif

#if 0 // delay
/* 1. Wait 15ms to avoid the distortion of messages from A/V cpu.
 * 2. Discard SCPU_CLK90K_HI(0x1801b544) for simplicity.
 * 3. Show the value in seconds.
 */
	{
		unsigned int counter;

		sys_wait_ms(15);
		counter = REG32(MIS_SCPU_CLK90K_LO);
		counter /= 90; /* in milliseconds */
		printf("SCPU_CLK90K=%d.%03d sec.\n", counter/1000, counter%1000);
	}
#endif

	/* Flush caches */
	flush_dcache_all();

#endif /* CONFIG_SYS_RTK_EMMC_FLASH */

	return RTK_PLAT_ERR_OK;
}

/*
 * Use firmware description table to read images from SPI flash.
 */
int rtk_plat_read_fw_image_from_SPI(void)
{
	/* TODO */
	printf("[TODO] boot from SPI is not ready!\n");

	return RTK_PLAT_ERR_PARSE_FW_DESC;
}

/*
 * Read firmware description table from eMMC
 */
int rtk_plat_read_fw_desc_table_from_eMMC(void)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	fw_desc_table_v1_t fw_desc_table_v1;
	uint fw_desc_table_base;
	uint fw_desc_table_blk;	// block no of firmware description table
	uint checksum;

	eMMC_fw_desc_table_start = eMMC_bootcode_area_size + CONFIG_FACTORY_SIZE;
	fw_desc_table_base = rtk_mem_info->fw_desc_table_base_addr;

	/* Use which fw desc table depends on boot_part */
	if (boot_part == 1)
	{
		eMMC_fw_desc_table_start += 0x8000000; // ping-pong fw desc table is at 0x0a00_0000
	}

	/* Firmware Description Table is right behind bootcode blocks */
	fw_desc_table_blk = eMMC_fw_desc_table_start / EMMC_BLOCK_SIZE;

	/* copy Firmware Description Table Header from flash */
	if (!rtk_eMMC_read(fw_desc_table_blk, sizeof(fw_desc_table_v1_t), (uint *)fw_desc_table_base))
	{
		printf("[ERR] %s:Read fw_desc_table_v1_t error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, sizeof(fw_desc_table_v1_t), fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		memcpy(&fw_desc_table_v1, (void*)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}

	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1.signature)) != 0)
	{
		printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1.signature);
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);

#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(&fw_desc_table_v1);
#endif

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	if (!rtk_eMMC_read(fw_desc_table_blk, fw_desc_table_v1.paddings, (uint *)fw_desc_table_base))
	{
		printf("[ERR] %s:Read all fw tables error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, fw_desc_table_v1.paddings, fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* Check checksum */
	checksum = get_checksum((uchar*)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1.part_list_len +
			fw_desc_table_v1.fw_list_len);

	if (fw_desc_table_v1.checksum != checksum)
	{
		printf("[ERR] %s:Checksum not match(0x%x != 0x%x)\n", __FUNCTION__,
			fw_desc_table_v1.checksum, checksum);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	b_fw_desc_table_vaild = 1; /* set 1: fw desc table in ram is valid */
#endif
	return RTK_PLAT_ERR_OK;

}

/*
 * Read firmware description table from NAND
 */
int rtk_plat_read_fw_desc_table_from_NAND(void)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from, to;
	unsigned int retlen;

	fw_desc_table_v1_t fw_desc_table_v1;
	uint fw_desc_table_base;
	//uint fw_desc_table_blk;	// block no of firmware description table
	uint checksum;
	char ssu_retry = 0;

#ifdef CONFIG_SAFE_UPGRADE
	printf("SSU on.\n");
return_ssu_boot_flow:
#else
	printf("SSU off.\n");
#endif

	if (ssu_retry == 0) {
		NAND_fw_desc_table_start = NAND_fw_desc_table_saddr;
	      printf("read main fwtab @ 0x%p\n", NAND_fw_desc_table_start);
	} else {
		NAND_fw_desc_table_start = NAND_fw_desc_table_saddr+nand->erasesize ;
	      printf("read backup fwtab @ 0x%p\n", NAND_fw_desc_table_start);
	}

	fw_desc_table_base = rtk_mem_info->fw_desc_table_base_addr;

	/* Use which fw desc table depends on boot_part */
#if 0
	if (boot_part == 1)
	{
		eMMC_fw_desc_table_start += 0x8000000; // ping-pong fw desc table is at 0x0a00_0000
	}

	/* Firmware Description Table is right behind bootcode blocks */
	fw_desc_table_blk = eMMC_fw_desc_table_start / EMMC_BLOCK_SIZE;

	/* copy Firmware Description Table Header from flash */
	if (!rtk_eMMC_read(fw_desc_table_blk, sizeof(fw_desc_table_v1_t), (uint *)fw_desc_table_base))
	{
		printf("[ERR] %s:Read fw_desc_table_v1_t error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, sizeof(fw_desc_table_v1_t), fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		memcpy(&fw_desc_table_v1, (void*)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}
#else
	from = NAND_fw_desc_table_start; 	//must define NAND_fw_desc_table_start
	/* copy Firmware Description Table Header from flash */
	get_flash_shared_semaphore();
	nand->read(nand, from, sizeof(fw_desc_table_v1_t), &retlen, (uint *)fw_desc_table_base);
	release_flash_shared_semaphore();
	if (retlen != sizeof(fw_desc_table_v1_t))
	{
		/* Read error */
		printf("[ERR] %s:Read fw_desc_table_v1_t error!!\n", __FUNCTION__);
#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}else
	{
		/* Read success */
		printf("[OK] %s:Read fw_desc_table_v1_t  ok!!\n", __FUNCTION__);
		memcpy(&fw_desc_table_v1, (void*)fw_desc_table_base, sizeof(fw_desc_table_v1_t));
	}
#endif
	/* Check signature first! */
	if (strncmp((const char *)fw_desc_table_v1.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table_v1.signature)) != 0)
	{
		printf("[ERR] %s:Signature(%s) error!\n", __FUNCTION__, fw_desc_table_v1.signature);
#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);

#ifdef DUBUG_FW_DESC_TABLE
	dump_fw_desc_table_v1(&fw_desc_table_v1);
#endif

	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
#if 0
	if (!rtk_eMMC_read(fw_desc_table_blk, fw_desc_table_v1.paddings, (uint *)fw_desc_table_base))
	{
		printf("[ERR] %s:Read all fw tables error! (0x%x, 0x%x, 0x%x)\n",
			__FUNCTION__, fw_desc_table_blk, fw_desc_table_v1.paddings, fw_desc_table_base);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
#else
	/* copy Firmware Description/Partition/Fw_entry Tables from flash */
	 from = NAND_fw_desc_table_start;
	get_flash_shared_semaphore();
	nand->read(nand, from, fw_desc_table_v1.paddings, &retlen, (uint *)fw_desc_table_base);
	release_flash_shared_semaphore();
	if (retlen != fw_desc_table_v1.paddings)
	{
		/* Read error */
		printf("[ERR] %s:Read all fw tables error!!\n", __FUNCTION__);
#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}else
	{
		/* Read success */
		printf("[OK] %s:Read all fw tables ok!!\n", __FUNCTION__);
	}
#endif
	/* Check checksum */
	checksum = get_checksum((uchar*)fw_desc_table_base +
			offsetof(fw_desc_table_v1_t, version),
			sizeof(fw_desc_table_v1_t) -
			offsetof(fw_desc_table_v1_t, version) +
			fw_desc_table_v1.part_list_len +
			fw_desc_table_v1.fw_list_len);

	if (fw_desc_table_v1.checksum != checksum)
	{
		printf("[ERR] %s:Checksum not match(0x%x != 0x%x)\n", __FUNCTION__,
			fw_desc_table_v1.checksum, checksum);
#ifdef CONFIG_SAFE_UPGRADE
		if (ssu_retry == 0)
			goto ssu_read_backup_fwtab;
#endif

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	b_fw_desc_table_vaild = 1; /* set 1: fw desc table in ram is valid */

#ifdef CONFIG_SAFE_UPGRADE
	if (ssu_retry == 1) {
		// write backupfwdesc to main fwdesc
		struct erase_info *instr;
		u_char* p_data;
		uint n;
		instr = (struct erase_info *)malloc(sizeof(struct erase_info));
		if(instr == NULL){

			printf("[ERR] %s: allocate erase_info failed!!!\n", __FUNCTION__);
			return RTK_PLAT_ERR_PARSE_FW_DESC;

		}
		memset(instr, 0x00, sizeof(struct erase_info));
		instr->mtd = nand;
		instr->addr = NAND_fw_desc_table_saddr;
		instr->len = nand->erasesize ;
		get_flash_shared_semaphore();
		int erase_ret = nand->erase(nand, instr);
		release_flash_shared_semaphore();

		if (erase_ret != 0) {
			printf("\n[ERR] %s: MTD Erase failure: %d\n",__FUNCTION__,erase_ret);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}else{
			free(instr);
		}
		to = NAND_fw_desc_table_saddr;
		uint data_len = fw_desc_table_v1.paddings;

		uint page_align_size =  nand->oobblock*( ( data_len + nand->oobblock -1) / nand->oobblock);

		p_data = (u_char*)malloc( page_align_size);
		if (p_data == NULL) {
			printf("[ERR] %s: allocate fwdesc merged buffer failed!!!\n", __FUNCTION__);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}
		memset(p_data, 0xff, page_align_size);
		//memcpy(p_data, &fw_desc_table_v1, sizeof(fw_desc_table_v1_t));
		memcpy(p_data, (void*)fw_desc_table_base , fw_desc_table_v1.paddings);
		get_flash_shared_semaphore();
		n = nand->write(nand, to, page_align_size, &retlen, (u_char *)p_data);
		release_flash_shared_semaphore();
		if(retlen == data_len){
			/* Write success */
			//printf("\n[%s][%d]retlen = %d, total_len=%d ", __FUNCTION__,__LINE__,retlen,total_len);
			printf("\n Save to main fwdesc OK\n");

		}else{
			/* Write error */
			//printf("\n[%s][%d]retlen = %llu, total_len=%d ", __FUNCTION__,__LINE__,retlen,total_len);
			printf("\n [ERR] Save to main fwdesc FAILED, retlen = %llu, total_len=%d \n", retlen, data_len);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
		}

	}
ssu_read_backup_fwtab:
	if (ssu_retry == 0 && b_fw_desc_table_vaild == 0) {
		ssu_retry = 1;
		goto return_ssu_boot_flow;
	}

#endif
#endif
	return RTK_PLAT_ERR_OK;

}

/*
 * Parse firmware description table and read all data from usb to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_USB(void)
{
	int ret = RTK_PLAT_ERR_OK;

#ifdef CONFIG_BOOT_FROM_USB
	if (boot_from_usb == BOOT_FROM_USB_UNCOMPRESSED) {
		ret = rtk_plat_read_fw_image_from_USB(0);
	}
	else if (boot_from_usb == BOOT_FROM_USB_COMPRESSED) {
		ret = rtk_plat_read_fw_image_from_USB(1);
	}
	else {
		printf("[WARN] boot_from_usb is %d\n", boot_from_usb);
		ret = RTK_PLAT_ERR_BOOT;
	}
#else
	printf("[WARN] CONFIG_BOOT_FROM_USB is not defined\n");
	ret = RTK_PLAT_ERR_BOOT;
#endif

	return ret;
}

#if IS_ENABLE_STD
#define IoReg_Write32(x, y)	rtd_outl((x), (y))

#define LSADC_PAD0_VADDR		(0xb8061500)
#define LSADC_CTRL_VADDR		(0xb8061520)
#define PERI_ANALOG_CTRL_VADDR	(0xb8061528)

#define PERI_ANALOG_ENABLE		(0x00010101)
#define LSADC_CTRL_SETTING_DISABLE	(0x16100000)
#define LSADC_CTRL_SETTING_ENABLE	(0x16100001)
#define LSADC_PAD_SETTING		(0x80000000)			//voltage-mode and enable

/* re-init to recovery keypad's register values after suspense */
void re_lsadcInit
(void)
{
	int	i,
		tmp;

	// LSADC Control register
	IoReg_Write32(PERI_ANALOG_CTRL_VADDR, PERI_ANALOG_ENABLE);		//enable analog
	IoReg_Write32(LSADC_CTRL_VADDR, LSADC_CTRL_SETTING_DISABLE);	//disable digital

	for(i=0; i<8; i++) {
		tmp=LSADC_PAD_SETTING | (i<<12);							//pad0_sw
		IoReg_Write32(LSADC_PAD0_VADDR+i*4, tmp);
	}
	IoReg_Write32(LSADC_CTRL_VADDR, LSADC_CTRL_SETTING_ENABLE);		//enable digital

	//power consumption
	//IoReg_Mask32(0xb8060208, 0xFFFFFF00,0x000000CC);				//PINMUX_PMM_CFG_2_VADDR
	//IoReg_Mask32(0xb8060210, 0x0FFFFFFF,0x000000CC);

	return;
}
#endif

/*
 * Parse firmware description table and read all data from eMMC to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_eMMC(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	fw_desc_table_v1_t fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry;
	fw_desc_entry_v1_t *fw_entry, *fw_entry_v1;
	fw_desc_entry_v11_t *fw_entry_v11;
	fw_desc_entry_v21_t *fw_entry_v21;
	uint part_count = 0;
	uint fw_total_len;
	uint fw_total_paddings;
	uint fw_entry_num = 0;
	uint fw_desc_table_base;
	int i;


   //Identify if enter STR or not
    if(rtd_inl(REG_CRT_SUSPEND_reg) == KERNEL_RSV_MEM_MAGICNO)
    {
			if(rtd_inl(REG_STR_JUMP_ADDR_reg)!=0)
			{
				g_goAddr = rtd_inl(REG_STR_JUMP_ADDR_reg);
				g_isSTR = 1;
				printf("Ready to enter STR mode.\n");
			}
			else
				g_isSTR = 0;
    }
	else
	 	g_isSTR = 0;



	/* Read fw desc table from eMMC */
	ret = rtk_plat_read_fw_desc_table_from_eMMC();

	if (ret != RTK_PLAT_ERR_OK) {
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* must after rtk_plat_read_fw_desc_table_from_eMMC() */
	fw_desc_table_base = rtk_mem_info->fw_desc_table_base_addr;
	memcpy(&fw_desc_table_v1, (void*)fw_desc_table_base, sizeof(fw_desc_table_v1_t));

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);

	/* Check partition existence */
	if (fw_desc_table_v1.part_list_len == 0)
	{
		printf("[ERR] %s:No partition found!\n", __FUNCTION__);
		//return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		part_count = fw_desc_table_v1.part_list_len / sizeof(part_desc_entry_v1_t);
	}

	fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);

	printf("\t FW Table to 0x%08x, size=0x%08x (0x%08x)\n",
				fw_desc_table_base,
				fw_desc_table_v1.paddings,
				fw_desc_table_base + fw_desc_table_v1.paddings);

	printf("\t FW Table fr 0x%08x, fw count: %d\n",
				eMMC_fw_desc_table_start,
				fw_entry_num);

	part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1.part_list_len);

	for (i = 0; i < part_count; i++)
	{
		part_entry[i].length = BE32_TO_CPU(part_entry[i].length);

#ifdef DUBUG_FW_DESC_TABLE
		dump_part_desc_entry_v1(&(part_entry[i]));
#endif
	}

	/* Check partition type */
	/*  It so weired that we use part_entry for checking fw count? So we mark it
	if (part_entry[0].type != PART_TYPE_FW)
	{
		printf("[ERR] %s:No firmware partition found!\n", __FUNCTION__);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	*/
	fw_total_len = 0;
	fw_total_paddings = 0;

	/* Parse firmware entries and compute fw_total_len */
	switch (fw_desc_table_v1.version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);

			for (i = 0; i < fw_entry_num; i++)
			{
				fw_entry[i].version = BE32_TO_CPU(fw_entry[i].version);
				fw_entry[i].target_addr = BE32_TO_CPU(fw_entry[i].target_addr);
				fw_entry[i].offset = BE32_TO_CPU(fw_entry[i].offset) - eMMC_fw_desc_table_start;	/* offset from fw_desc_table_base */
				fw_entry[i].length = BE32_TO_CPU(fw_entry[i].length);
				fw_entry[i].paddings = BE32_TO_CPU(fw_entry[i].paddings);
				fw_entry[i].checksum = BE32_TO_CPU(fw_entry[i].checksum);

//				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x)\n",
//					i, fw_entry[i].offset, fw_entry[i].length, fw_entry[i].paddings);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry[i].length;
				fw_total_paddings += fw_entry[i].paddings;
			}


			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			fw_entry_v11 = (fw_desc_entry_v11_t*)fw_entry;
                              fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v11_t);
			for(i = 0; i < fw_entry_num; i++) {
				fw_entry_v1 = &fw_entry_v11[i].v1;
				fw_entry_v1->version = BE32_TO_CPU(fw_entry_v1->version);
				fw_entry_v1->target_addr = BE32_TO_CPU(fw_entry_v1->target_addr);
				fw_entry_v1->offset = BE32_TO_CPU(fw_entry_v1->offset) - eMMC_fw_desc_table_start;	/* offset from fw_desc_table_base */
				fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
				fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
				fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);

				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings, fw_entry_v11[i].act_size, fw_entry_v11[i].part_num);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry_v1->length;
				fw_total_paddings += fw_entry_v1->paddings;
			}


			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			fw_entry_v21 = (fw_desc_entry_v21_t*)fw_entry;
                              fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v21_t);
			for(i = 0; i < fw_entry_num; i++) {
				fw_entry_v1 = &fw_entry_v21[i].v1;
				fw_entry_v1->version = BE32_TO_CPU(fw_entry_v1->version);
				fw_entry_v1->target_addr = BE32_TO_CPU(fw_entry_v1->target_addr);
				fw_entry_v1->offset = BE32_TO_CPU(fw_entry_v1->offset) - eMMC_fw_desc_table_start;	/* offset from fw_desc_table_base */
				fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
				fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
				fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);

				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings, fw_entry_v21[i].act_size, fw_entry_v21[i].part_num);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry_v1->length;
				fw_total_paddings += fw_entry_v1->paddings;
			}


			break;

		default:
			printf("[ERR] %s:unknown version:%d\n", __FUNCTION__, fw_desc_table_v1.version);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

// STD is not well-tested in 298x
#if 0	//IS_ENABLE_STD

	unsigned int blkNO ;
	unsigned int idBlkNo;
	int memshift=0;
	char		*raw = NULL;
	char tmp[32],msg[128];
	printf("part_entry[0].len 0x%x\n",BE32_TO_CPU(part_entry[0].length));
	printf("fw_desc_table_v1.paddings 0x%x\n",fw_desc_table_v1.paddings);
	printf("fw_total_paddings 0x%x\n",fw_total_paddings);
	printf("eMMC_bootcode_area_size0x%x\n",eMMC_bootcode_area_size);
	printf("EMMC_FACTORY_SIZE 0x%x\n",EMMC_FACTORY_SIZE);
	g_u32STDsize = BE32_TO_CPU(part_entry[0].length)-fw_desc_table_v1.paddings-fw_total_paddings-eMMC_bootcode_area_size-EMMC_FACTORY_SIZE;
	g_u32STDoffset = eMMC_bootcode_area_size+EMMC_FACTORY_SIZE+fw_desc_table_v1.paddings+fw_total_paddings;

	printf("g_u32STDsize 0x%x, g_u32STDoffset 0x%x\n",g_u32STDsize,g_u32STDoffset);

	/* system_parameters_3 pass parameter start address to kernel */
	if (!(raw = getenv("system_parameters_3")))
		raw = "";	   /* Create new */
	sprintf( msg, "%s STD_size=%x STD_offset=%x",
				raw,
				g_u32STDsize,
				g_u32STDoffset
				);

	if (setenv("system_parameters_3", msg))
		;
	//sprintf (tmp, "0x%x", g_u32STDoffset);
	//setenv( "STD_OFFSET", tmp);
	//sprintf (tmp, "0x%x", g_u32STDsize);
	//setenv( "STD_SIZE", tmp);
//return NULL;
#if 0
	//Identify STD flag
	g_u32STDsize = BE32_TO_CPU(part_entry[0].length)-fw_desc_table_v1.paddings-fw_total_paddings-nand_bootcode_area_size-NAND_FACTORY_SIZE;
	g_u32STDoffset = nand_bootcode_area_size+NAND_FACTORY_SIZE+fw_desc_table_v1.paddings+fw_total_paddings;

	/* system_parameters_3 pass parameter start address to kernel */
	if( !env_get( "system_parameters_3", &raw, NULL, 0 ))
		raw = "";	 /* Create new */
		sprintf( msg, "%s STD_size=%x STD_offset=%x",
			raw,
			g_u32STDsize,
			g_u32STDoffset
			);
	ret = env_set( "system_parameters_3", msg, ENV_ATTR_RW, NULL, NULL );
	 if(ret!=OK)
	 {
		printf("Set_env system_parameters_3 Error  %d\n",ret);
		//return BOOTCODE_CONTINUE;
	 }

	blkNO = g_u32STDoffset/(bytes_per_page * pages_per_block);
	idBlkNo = blkNO;
	//t_FLASH_ctrl_descriptor flash_ctrl;
	printf("STD ID block NO: 0x%x\n",idBlkNo);

	if(g_u32STDsize<=0)
	{
		printf("Warning!!! STD size is not enough!!!(size = 0x%x)\n",g_u32STDsize);
		printf("Enter normal boot!!\n");
		goto normalboot;
	}
#else
g_u32STDsize = 0x80000000;
g_u32STDoffset =0x4000000;
blkNO = g_u32STDoffset/(bytes_per_page * pages_per_block);
printf("blkNO 0x%x, 0x%x, 0x%x, 0x%x\n",blkNO,g_u32STDoffset,bytes_per_page , pages_per_block);
#endif
	memshift = 8-(UINT32)&headerBuf%8;
	ptrHeadBuf = &headerBuf[memshift];
	moveToRam(&blkNO,4096,ptrHeadBuf,0);
	if(checkHeader(ptrHeadBuf)!=0)
	{
	#if 1
			goto normalboot;
	#else
		if(IO_read(SYS_MAJOR_FLASH, 0, &flash_read) != OK) {
			printf("%s:%d read fw_desc_table_v1 fail!!\n", __FUNCTION__, __LINE__);
		goto go_rescue;
		}
	#endif

	}

	printf("STD image size : 0x%x\n",g_imgLen);
	printf("STD space size : 0x%x\n",g_u32STDsize);
	if(g_imgLen>g_u32STDsize)
	{
		printf("[Warning]STD image is out of space.\n");
		goto normalboot;
	}



	if(mainSTD()==BOOTCODE_STD_WORK)
		{
			STDinitProc();
			GoFuncPtr=(UINT32*)g_goAddr;
#if 0
		printf("Don't erase ID block!!\n");
#else

#if IS_ENABLE_STD
			/* Re-init Keypad */
			re_lsadcInit();
#endif

			if(g_u32Stdflag<=3)
			{
				#if IS_ERASE_ID_BLK
				//Erase STD_ID block
				char idBuffer[4];
				unsigned int blk_start = g_u32STDoffset/(bytes_per_page * pages_per_block);
				memset(&idBuffer,'\0',4);
				printf("Erase ID block(blk_start 0x%x)\n",blk_start);
				rtk_eMMC_write(blk_start, 4, idBuffer);
				#endif
			}
#endif
#ifndef Board_WATCHDOG_NULL
			//printf("[STD INFO]Disable watchdog ... \n");
			//WATCHDOG_disable();
#endif

#if 0//ALFIE_TEST
		g_u32StdAnimation = 0;
#endif
			if(!g_u32StdAnimation)
			{
				processImg_STDAnimation(ptrHeadBuf);



				printf("Reset ethernet/disable interrupt/flush cache...\n");
				//Reset ethernet
				cmd_boot_rtd_outl(0xb8016234, 0x0);
				cmd_boot_rtd_outl(0xb801603c, 0xffff);
				cmd_boot_rtd_outl(0xb8016038, 0x1);

				//Disable UART0/UART1
				#define ISO_MISC_OFF_INT_EN_reg 			 0xB8062108
				#define SCPU_INT_EN_reg     				 0xB801B080
				#define BIT(x) (1<<(x))
				rtd_outl(ISO_MISC_OFF_INT_EN_reg,BIT(2));
				rtd_outl(SCPU_INT_EN_reg,BIT(3));
				rtd_outl(SCPU_INT_EN_reg,BIT(4));
				rtd_outl(SCPU_INT_EN_reg,BIT(5));

				//printf("0xb8016234 : 0x%x\n",cmd_boot_rtd_inl(0xb8016234));
				//printf("0xb801603c : 0x%x\n",cmd_boot_rtd_inl(0xb801603c));
				//printf("0xb8016038 : 0x%x\n",cmd_boot_rtd_inl(0xb8016038));

				//#ifdef CONFIG_USB_DEVICE
				//udc_disconnect();
				//#endif
				cleanup_before_linux();
				printf("[AT]Ready to go STD kernel address!!!\n");
				(*GoFuncPtr)();
				return NULL;
			}
		}
	else
	{
		if(g_u32Stdflag<=3)
			{

				//Erase STD_ID block
				char idBuffer[4];
				unsigned int blk_start = g_u32STDoffset/(bytes_per_page * pages_per_block);
				memset(&idBuffer,'\0',4);
				printf("Erase ID block(blk_start 0x%x)\n",blk_start);
				rtk_eMMC_write(blk_start, 4, idBuffer);

			}

		//printf("STD fail..watchdog reset...\n");
	//execute_line("reset",TRUE);

	//REG32(0Xb801bb04)=1;		// clear watchdog
	//REG32(0Xb801bb0c)=0x800000; // set overflow count
	//REG32(0Xb801bb00)=0;		// enable watchdog

	}

normalboot:

#endif	//IS_ENABLE_STD

	if(g_u32StdAnimation||g_isSTR)
	{
		#if IS_ENABLE_STD
		printf("STD/STR fw follow...\n");
		ret = rtk_plat_read_fw_image_from_eMMC_STD(
			fw_desc_table_base, part_entry, part_count,
			fw_entry, fw_entry_num,
			fw_desc_table_v1.version,ptrHeadBuf);
		#endif
	}
	else
	{
		printf("Normal boot fw follow...\n");
	ret = rtk_plat_read_fw_image_from_eMMC(
			fw_desc_table_base, part_entry, part_count,
			fw_entry, fw_entry_num,
			fw_desc_table_v1.version);
	}
#endif

	return ret;
}

/*
 * Parse firmware description table and read all data from NAND to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_NAND(void)
{
	int ret = RTK_PLAT_ERR_OK;
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from;
	unsigned int retlen;

	fw_desc_table_v1_t fw_desc_table_v1;
	part_desc_entry_v1_t *part_entry;
	fw_desc_entry_v1_t *fw_entry, *fw_entry_v1;
	fw_desc_entry_v11_t *fw_entry_v11;
	fw_desc_entry_v21_t *fw_entry_v21;
	uint part_count = 0;
	uint fw_total_len;
	uint fw_total_paddings;
	uint fw_entry_num = 0;
	uint fw_desc_table_base;
	int i;


    //Identify if enter STR or not
    if(rtd_inl(REG_CRT_SUSPEND_reg) == KERNEL_RSV_MEM_MAGICNO)
    {
		#if 1
			if(rtd_inl(REG_STR_JUMP_ADDR_reg)!=0)
			{
				g_goAddr = rtd_inl(REG_STR_JUMP_ADDR_reg);
				g_isSTR = 1;
			}
			else
				g_isSTR = 0;

		#else
		printf("Ready to enter STR mode.\n");
		if(rtd_inl(REG_STR_JUMP_ADDR_reg)!=0)
		{
			g_goAddr = rtd_inl(REG_STR_JUMP_ADDR_reg);
			GoFuncPtr=(UINT32*)g_goAddr;
			printf("STR go address 0x%x\n",g_goAddr);
			(*GoFuncPtr)();
		}
		else
		{
			g_isSTR = 0;
			printf("STR jump address is null, exit STR mode!\n");
		}
		#endif
    }
	else
	 	g_isSTR = 0;



	/* Read fw desc table from NAND */
	ret = rtk_plat_read_fw_desc_table_from_NAND();

	if (ret != RTK_PLAT_ERR_OK) {
		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}

	/* must after rtk_plat_read_fw_desc_table_from_NAND() */
	fw_desc_table_base = rtk_mem_info->fw_desc_table_base_addr;
	memcpy(&fw_desc_table_v1, (void*)fw_desc_table_base, sizeof(fw_desc_table_v1_t));

	fw_desc_table_v1.checksum = BE32_TO_CPU(fw_desc_table_v1.checksum);
	fw_desc_table_v1.paddings = BE32_TO_CPU(fw_desc_table_v1.paddings);
	fw_desc_table_v1.part_list_len = BE32_TO_CPU(fw_desc_table_v1.part_list_len);
	fw_desc_table_v1.fw_list_len = BE32_TO_CPU(fw_desc_table_v1.fw_list_len);

	/* Check partition existence */
	if (fw_desc_table_v1.part_list_len == 0)
	{
		printf("[ERR] %s:No partition found!\n", __FUNCTION__);
		//return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	else
	{
		part_count = fw_desc_table_v1.part_list_len / sizeof(part_desc_entry_v1_t);
	}

	fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);

	printf("\t FW Table to 0x%08x, size=0x%08x (0x%08x)\n",
				fw_desc_table_base,
				fw_desc_table_v1.paddings,
				fw_desc_table_base + fw_desc_table_v1.paddings);

	printf("\t FW Table fr 0x%08x, fw count: %d\n",
				NAND_fw_desc_table_start,
				fw_entry_num);

	part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));
	fw_entry = (fw_desc_entry_v1_t *)(fw_desc_table_base +
			sizeof(fw_desc_table_v1_t) +
			fw_desc_table_v1.part_list_len);

	for (i = 0; i < part_count; i++)
	{
		part_entry[i].length = BE32_TO_CPU(part_entry[i].length);

#ifdef DUBUG_FW_DESC_TABLE
		dump_part_desc_entry_v1(&(part_entry[i]));
#endif
	}

	/* Check partition type */
	/*  It so weired that we use part_entry for checking fw count? So we mark it
	if (part_entry[0].type != PART_TYPE_FW)
	{
		printf("[ERR] %s:No firmware partition found!\n", __FUNCTION__);

		return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
	*/
	fw_total_len = 0;
	fw_total_paddings = 0;

	/* Parse firmware entries and compute fw_total_len */
	switch (fw_desc_table_v1.version)
	{
		case FW_DESC_TABLE_V1_T_VERSION_1:
			fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v1_t);

			for (i = 0; i < fw_entry_num; i++)
			{
				fw_entry[i].version = BE32_TO_CPU(fw_entry[i].version);
				fw_entry[i].target_addr = BE32_TO_CPU(fw_entry[i].target_addr);
				fw_entry[i].offset = BE32_TO_CPU(fw_entry[i].offset) - NAND_fw_desc_table_start;	/* offset from fw_desc_table_base */
				fw_entry[i].length = BE32_TO_CPU(fw_entry[i].length);
				fw_entry[i].paddings = BE32_TO_CPU(fw_entry[i].paddings);
				fw_entry[i].checksum = BE32_TO_CPU(fw_entry[i].checksum);

//				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x)\n",
//					i, fw_entry[i].offset, fw_entry[i].length, fw_entry[i].paddings);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry[i].length;
				fw_total_paddings += fw_entry[i].paddings;
			}


			break;

		case FW_DESC_TABLE_V1_T_VERSION_11:
			fw_entry_v11 = (fw_desc_entry_v11_t*)fw_entry;
                              fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v11_t);
			for(i = 0; i < fw_entry_num; i++) {
				fw_entry_v1 = &fw_entry_v11[i].v1;
				fw_entry_v1->version = BE32_TO_CPU(fw_entry_v1->version);
				fw_entry_v1->target_addr = BE32_TO_CPU(fw_entry_v1->target_addr);
				fw_entry_v1->offset = BE32_TO_CPU(fw_entry_v1->offset) - NAND_fw_desc_table_start;	/* offset from fw_desc_table_base */
				fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
				fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
				fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);

				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings, fw_entry_v11[i].act_size, fw_entry_v11[i].part_num);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry_v1->length;
				fw_total_paddings += fw_entry_v1->paddings;
			}


			break;

		case FW_DESC_TABLE_V1_T_VERSION_21:
			fw_entry_v21 = (fw_desc_entry_v21_t*)fw_entry;
                              fw_entry_num = fw_desc_table_v1.fw_list_len / sizeof(fw_desc_entry_v21_t);
			for(i = 0; i < fw_entry_num; i++) {
				fw_entry_v1 = &fw_entry_v21[i].v1;
				fw_entry_v1->version = BE32_TO_CPU(fw_entry_v1->version);
				fw_entry_v1->target_addr = BE32_TO_CPU(fw_entry_v1->target_addr);
				fw_entry_v1->offset = BE32_TO_CPU(fw_entry_v1->offset) - NAND_fw_desc_table_start;	/* offset from fw_desc_table_base */
				fw_entry_v1->length = BE32_TO_CPU(fw_entry_v1->length);
				fw_entry_v1->paddings = BE32_TO_CPU(fw_entry_v1->paddings);
				fw_entry_v1->checksum = BE32_TO_CPU(fw_entry_v1->checksum);

				printf("[OK] fw_entry[%d] offset = 0x%x length = 0x%x (paddings = 0x%x) act_size = %d part_num = %d\n",
					i, fw_entry_v1->offset, fw_entry_v1->length, fw_entry_v1->paddings, fw_entry_v21[i].act_size, fw_entry_v21[i].part_num);

#ifdef DUBUG_FW_DESC_TABLE
				dump_fw_desc_entry_v1(&(fw_entry[i]));
#endif

				fw_total_len += fw_entry_v1->length;
				fw_total_paddings += fw_entry_v1->paddings;
			}


			break;

		default:
			printf("[ERR] %s:unknown version:%d\n", __FUNCTION__, fw_desc_table_v1.version);
			return RTK_PLAT_ERR_PARSE_FW_DESC;
	}
#if 0
#if IS_ENABLE_STD

	unsigned int blkNO ;
	unsigned int idBlkNo;
	int memshift=0;
	char		*raw = NULL;
	char tmp[32],msg[128];
	printf("part_entry[0].len 0x%x\n",BE32_TO_CPU(part_entry[0].length));
	printf("fw_desc_table_v1.paddings 0x%x\n",fw_desc_table_v1.paddings);
	printf("fw_total_paddings 0x%x\n",fw_total_paddings);
	printf("eMMC_bootcode_area_size0x%x\n",eMMC_bootcode_area_size);
	printf("EMMC_FACTORY_SIZE 0x%x\n",EMMC_FACTORY_SIZE);
	g_u32STDsize = BE32_TO_CPU(part_entry[0].length)-fw_desc_table_v1.paddings-fw_total_paddings-eMMC_bootcode_area_size-EMMC_FACTORY_SIZE;
	g_u32STDoffset = eMMC_bootcode_area_size+EMMC_FACTORY_SIZE+fw_desc_table_v1.paddings+fw_total_paddings;

	printf("g_u32STDsize 0x%x, g_u32STDoffset 0x%x\n",g_u32STDsize,g_u32STDoffset);

	/* system_parameters_3 pass parameter start address to kernel */
	if (!(raw = getenv("system_parameters_3")))
		raw = "";	   /* Create new */
	sprintf( msg, "%s STD_size=%x STD_offset=%x",
				raw,
				g_u32STDsize,
				g_u32STDoffset
				);

	if (setenv("system_parameters_3", msg))
		;
	//sprintf (tmp, "0x%x", g_u32STDoffset);
	//setenv( "STD_OFFSET", tmp);
	//sprintf (tmp, "0x%x", g_u32STDsize);
	//setenv( "STD_SIZE", tmp);
//return NULL;
#if 0
	//Identify STD flag
	g_u32STDsize = BE32_TO_CPU(part_entry[0].length)-fw_desc_table_v1.paddings-fw_total_paddings-nand_bootcode_area_size-NAND_FACTORY_SIZE;
	g_u32STDoffset = nand_bootcode_area_size+NAND_FACTORY_SIZE+fw_desc_table_v1.paddings+fw_total_paddings;

	/* system_parameters_3 pass parameter start address to kernel */
	if( !env_get( "system_parameters_3", &raw, NULL, 0 ))
		raw = "";	 /* Create new */
		sprintf( msg, "%s STD_size=%x STD_offset=%x",
			raw,
			g_u32STDsize,
			g_u32STDoffset
			);
	ret = env_set( "system_parameters_3", msg, ENV_ATTR_RW, NULL, NULL );
	 if(ret!=OK)
	 {
		printf("Set_env system_parameters_3 Error  %d\n",ret);
		//return BOOTCODE_CONTINUE;
	 }

	blkNO = g_u32STDoffset/(bytes_per_page * pages_per_block);
	idBlkNo = blkNO;
	//t_FLASH_ctrl_descriptor flash_ctrl;
	printf("STD ID block NO: 0x%x\n",idBlkNo);

	if(g_u32STDsize<=0)
	{
		printf("Warning!!! STD size is not enough!!!(size = 0x%x)\n",g_u32STDsize);
		printf("Enter normal boot!!\n");
		goto normalboot;
	}
#else
g_u32STDsize = 0x80000000;
g_u32STDoffset =0x4000000;
blkNO = g_u32STDoffset/(bytes_per_page * pages_per_block);
printf("blkNO 0x%x, 0x%x, 0x%x, 0x%x\n",blkNO,g_u32STDoffset,bytes_per_page , pages_per_block);
#endif
	memshift = 8-(UINT32)&headerBuf%8;
	ptrHeadBuf = &headerBuf[memshift];
	moveToRam(&blkNO,4096,ptrHeadBuf,0);
	if(checkHeader(ptrHeadBuf)!=0)
	{
	#if 1
			goto normalboot;
	#else
		if(IO_read(SYS_MAJOR_FLASH, 0, &flash_read) != OK) {
			printf("%s:%d read fw_desc_table_v1 fail!!\n", __FUNCTION__, __LINE__);
		goto go_rescue;
		}
	#endif

	}

	printf("STD image size : 0x%x\n",g_imgLen);
	printf("STD space size : 0x%x\n",g_u32STDsize);
	if(g_imgLen>g_u32STDsize)
	{
		printf("[Warning]STD image is out of space.\n");
		goto normalboot;
	}



	if(mainSTD()==BOOTCODE_STD_WORK)
		{
			STDinitProc();
			GoFuncPtr=(UINT32*)g_goAddr;
#if 0
		printf("Don't erase ID block!!\n");
#else

#if IS_ENABLE_STD
			/* Re-init Keypad */
			re_lsadcInit();
#endif

			if(g_u32Stdflag<=3)
			{
				#if IS_ERASE_ID_BLK
				//Erase STD_ID block
				char idBuffer[4];
				unsigned int blk_start = g_u32STDoffset/(bytes_per_page * pages_per_block);
				memset(&idBuffer,'\0',4);
				printf("Erase ID block(blk_start 0x%x)\n",blk_start);
				rtk_eMMC_write(blk_start, 4, idBuffer);
				#endif
			}
#endif
#ifndef Board_WATCHDOG_NULL
			//printf("[STD INFO]Disable watchdog ... \n");
			//WATCHDOG_disable();
#endif

#if 0//ALFIE_TEST
		g_u32StdAnimation = 0;
#endif
			if(!g_u32StdAnimation)
			{
				processImg_STDAnimation(ptrHeadBuf);



				printf("Reset ethernet/disable interrupt/flush cache...\n");
				//Reset ethernet
				cmd_boot_rtd_outl(0xb8016234, 0x0);
				cmd_boot_rtd_outl(0xb801603c, 0xffff);
				cmd_boot_rtd_outl(0xb8016038, 0x1);

				//Disable UART0/UART1
				#define ISO_MISC_OFF_INT_EN_reg 			 0xB8062108
				#define SCPU_INT_EN_reg     				 0xB801B080
				#define BIT(x) (1<<(x))
				rtd_outl(ISO_MISC_OFF_INT_EN_reg,BIT(2));
				rtd_outl(SCPU_INT_EN_reg,BIT(3));
				rtd_outl(SCPU_INT_EN_reg,BIT(4));
				rtd_outl(SCPU_INT_EN_reg,BIT(5));

				//printf("0xb8016234 : 0x%x\n",cmd_boot_rtd_inl(0xb8016234));
				//printf("0xb801603c : 0x%x\n",cmd_boot_rtd_inl(0xb801603c));
				//printf("0xb8016038 : 0x%x\n",cmd_boot_rtd_inl(0xb8016038));

				//#ifdef CONFIG_USB_DEVICE
				//udc_disconnect();
				//#endif
				cleanup_before_linux();
				printf("[AT]Ready to go STD kernel address!!!\n");
				(*GoFuncPtr)();
				return NULL;
			}
		}
	else
	{
		if(g_u32Stdflag<=3)
			{

				//Erase STD_ID block
				char idBuffer[4];
				unsigned int blk_start = g_u32STDoffset/(bytes_per_page * pages_per_block);
				memset(&idBuffer,'\0',4);
				printf("Erase ID block(blk_start 0x%x)\n",blk_start);
				rtk_eMMC_write(blk_start, 4, idBuffer);

			}

		//printf("STD fail..watchdog reset...\n");
	//execute_line("reset",TRUE);

	//REG32(0Xb801bb04)=1;		// clear watchdog
	//REG32(0Xb801bb0c)=0x800000; // set overflow count
	//REG32(0Xb801bb00)=0;		// enable watchdog

	}

normalboot:

#endif

	if(g_u32StdAnimation||g_isSTR)
	{
		#if IS_ENABLE_STD
		printf("STD/STR fw follow...\n");
		ret = rtk_plat_read_fw_image_from_eMMC_STD(
			fw_desc_table_base, part_entry, part_count,
			fw_entry, fw_entry_num,
			fw_desc_table_v1.version,ptrHeadBuf);
		#endif
	}
	else
	{
		printf("Normal boot fw follow...\n");
	ret = rtk_plat_read_fw_image_from_eMMC(
			fw_desc_table_base, part_entry, part_count,
			fw_entry, fw_entry_num,
			fw_desc_table_v1.version);
	}
#endif
	ret = rtk_plat_read_fw_image_from_NAND(
			fw_desc_table_base, part_entry, part_count,
			fw_entry, fw_entry_num,
			fw_desc_table_v1.version);
#endif

	return ret;
}

/*
 * Parse firmware description table and read all data from SPI flash to ram except kernel image.
 */
int rtk_plat_prepare_fw_image_from_SPI(void)
{
	int ret = RTK_PLAT_ERR_OK;

#if 0 // for nor
	/* Get flash size. */
	if((rcode = SYSCON_read(SYSCON_BOARD_MONITORFLASH_SIZE_ID,
				&flash_size, sizeof(flash_size))) != OK) {
		printf("get flash size fail!!\n");
		return NULL;
	}

	flash_end_addr = 0xbec00000 + flash_size ;

	/* SCIT signature address */
	scit_signature_addr = (void*)0xbec00000 + 0x100000 + 0x10000 - 0x100;


	memcpy(&fw_desc_table, (void*)(flash_end_addr - sizeof(fw_desc_table)), sizeof(fw_desc_table));
	fw_desc_table.checksum = BE32_TO_CPU(fw_desc_table.checksum);
	memcpy(fw_desc_entry, (void*)(flash_end_addr - sizeof(fw_desc_table) -sizeof(fw_desc_entry)),
					sizeof(fw_desc_entry));

	checksum = get_checksum((uchar*)&fw_desc_table +
			offsetof(fw_desc_table_t, version),
			sizeof(fw_desc_table_t) - offsetof(fw_desc_table_t, version));
	checksum += get_checksum((uchar*)fw_desc_entry, sizeof(fw_desc_entry));

	memcpy(signature_str_buf, fw_desc_table.signature, sizeof(fw_desc_table.signature));

	/* Check checksum and signature. */
	if(fw_desc_table.checksum != checksum ||
			strncmp(fw_desc_table.signature,
			FIRMWARE_DESCRIPTION_TABLE_SIGNATURE,
			sizeof(fw_desc_table.signature)) != 0) {
		printf("Checksum(0x%x) or signature(%s) error! Entering rescue linux...\n",
			fw_desc_table.checksum, signature_str_buf);
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled)
		return run_rescue_from_usb(RESCUE_LINUX_FILE_NAME);
#elif defined(Rescue_Source_FLASH)
#if defined(Logo_Source_FLASH)
#if defined(Logo6_Source_FLASH)
		LOGO_DISP_change(5);
#endif
#endif
		return run_rescue_from_flash();
#else
		return NULL;
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
	}


	if(strncmp((char*)scit_signature_addr, VERONA_SCIT_SIGNATURE_STRING,
			strlen(VERONA_SCIT_SIGNATURE_STRING)) != 0) {
		printf("Can not find signature string, \"%s\"! Entering rescue linux...\n",
			VERONA_SCIT_SIGNATURE_STRING);
#if defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled)
		return run_rescue_from_usb(rescue_file);
#elif defined(Rescue_Source_FLASH)
#if defined(Logo_Source_FLASH)
#if defined(Logo6_Source_FLASH)
		LOGO_DISP_change(5);
#endif
#endif
		return run_rescue_from_flash();
#else
		return NULL;
#endif /* defined(Rescue_Source_USB) && defined(Board_USB_Driver_Enabled) */
	}

	fw_desc_table.length = BE32_TO_CPU(fw_desc_table.length);

	for(i = 0; i < (int)ARRAY_COUNT(fw_desc_entry); i++) {
		fw_desc_entry[i].version =
			BE32_TO_CPU(fw_desc_entry[i].version);
		fw_desc_entry[i].target_addr =
			BE32_TO_CPU(fw_desc_entry[i].target_addr);
		fw_desc_entry[i].offset = BE32_TO_CPU(fw_desc_entry[i].offset);
		fw_desc_entry[i].length = BE32_TO_CPU(fw_desc_entry[i].length);
		fw_desc_entry[i].paddings = BE32_TO_CPU(fw_desc_entry[i].paddings);
		fw_desc_entry[i].checksum = BE32_TO_CPU(fw_desc_entry[i].checksum);
	}

	return run_kernel_from_flash(0x9ec00000, flash_size,
			fw_desc_entry, ARRAY_COUNT(fw_desc_entry));
#endif

//	ret = rtk_plat_read_fw_image_from_SPI();

	return ret;
}

/*
 * Read kernel image from usb to ram.
 */
int rtk_plat_read_kernel_image_from_USB(bootm_headers_t *images, uint bCompressed)
{
	int ret = RTK_PLAT_ERR_READ_KERNEL_IMG;

#ifdef CONFIG_BOOT_FROM_USB
	uint target_addr = 0;
	char fw_fname[32];
	char cmd[128];
	uint uncompressedSize = 0;
	uint compressedSize = 0;
	uint uncompressed_target_addr = 0;

	memset(fw_fname, 0, sizeof(fw_fname));
	if (bCompressed)
	{
		sprintf(fw_fname, "%s.%s", CONFIG_BOOT_FROM_USB_KERNEL_FILENAME, CONFIG_BOOT_FROM_USB_LZMA_EXTNAME);
		target_addr = rtk_mem_info->encrypted_fw_image_addr;
	}
	else
	{
		strcpy(fw_fname, CONFIG_BOOT_FROM_USB_KERNEL_FILENAME);
		target_addr = LINUX_KERNEL_ENTRY;
	}

	printf("########################################################\n");
	if (bCompressed)
		printf("## Kernel LZMA Image from USB\n");
	else
		printf("## Kernel Image from USB\n");
	printf("##    file_name   = %s\n", fw_fname);
	printf("##    target_addr = 0x%x\n", target_addr);

	memset(cmd, 0, sizeof(cmd));
	sprintf(cmd, "fatload usb 0:1 %x %s", target_addr, fw_fname);

	ret = run_command(cmd, 0);
	if (ret != 0)
	{
		/* Read error */
		printf("[ERR] %s:Read kernel image from USB failed. (%s, 0x%x, 0x%x)\n", __FUNCTION__, fw_fname, target_addr, ret);
		ret = RTK_PLAT_ERR_READ_KERNEL_IMG;
	}
	else
	{
		/* Read success */
		if (bCompressed)
		{
			printf("## Decompress kernel image using LZMA ...\n");

			uncompressed_target_addr = LINUX_KERNEL_ENTRY;
			compressedSize = getenv_ulong("filesize", 16, 0);

			if (compressedSize == 0) {
				printf("[ERR] %s:Get the wrong compressed filesize.\n", __FUNCTION__);
			}
			else {
				printf("##	  compressedSize   = 0x%x\n", compressedSize);
				printf("##	  target_addr	   = 0x%x\n", uncompressed_target_addr);
			}

			if (lzmaBuffToBuffDecompress((uchar*)uncompressed_target_addr, &uncompressedSize, (uchar*)target_addr, compressedSize) != 0)
			{
				/* Decompress error */
				printf("[ERR] %s:Decompress using LZMA error!! (0x%x, 0x%x)\n", __FUNCTION__, target_addr, compressedSize);

				return RTK_PLAT_ERR_READ_KERNEL_IMG;
			}
			else
			{
				/* Decompress success */
				printf("##	  uncompressedSize = 0x%x\n", uncompressedSize);
			}

			target_addr = uncompressed_target_addr;
		}

		printf("########################################################\n");
		printf("[OK]\n");

		ret = RTK_PLAT_ERR_OK;
	}

	/* update bootm_headers_t to be compitable with U-boot */
	memset(images, 0, sizeof(bootm_headers_t));
	images->ep = target_addr;

#endif

	return ret;
}

/*
 * Read kernel image from eMMC flash to ram.
 */
int rtk_plat_read_kernel_image_from_eMMC(bootm_headers_t *images)
{
#ifdef CONFIG_SYS_RTK_EMMC_FLASH
	int ret = 0;
	unsigned int img_truncated_size = 0; // install_a will append 256-byte signature data to it
	uint decompressedSize = 0;
	uint imageSize = 0;
	uint block_no = 0;
	uint fw_checksum = 0;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	unsigned int secure_mode = 0;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;

	img_truncated_size = RSA_SIGNATURE_LENGTH + sizeof(struct image_extra_info);

	if (kernel_entry == NULL)
	{
		printf("[ERR] %s:kernel_entry is NULL!!\n", __FUNCTION__);

		return RTK_PLAT_ERR_READ_KERNEL_IMG;
	}
	else
	{

#ifdef DUBUG_FW_DESC_TABLE
		printf("[DBG] kernel_entry->offset = 0x%08x \n", kernel_entry->offset);
		printf("[DBG] kernel_entry->length = 0x%08x \n", kernel_entry->length);
		printf("[DBG] kernel_entry->target_addr = 0x%08x \n", kernel_entry->target_addr);
		printf("[DBG] kernel_entry->lzma = 0x%08x \n", kernel_entry->lzma);
#endif

		secure_mode = rtk_get_secure_boot_type();

		/* get memory layout before copy kernel image */
		mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
		mem_layout.bIsCompressed = kernel_entry->lzma;
		mem_layout.image_target_addr = kernel_entry->target_addr & (~MIPS_KSEG_MSK);

		get_mem_layout_when_read_image(&mem_layout);

		/* read kernel image from flash */
		mem_layout.flash_to_ram_addr -= (kernel_entry->offset % EMMC_BLOCK_SIZE);

		imageSize = kernel_entry->length;

		block_no = (eMMC_fw_desc_table_start + kernel_entry->offset) / EMMC_BLOCK_SIZE;

#ifdef DUBUG_FW_DESC_TABLE
		printf("[DBG] kernel block_no=0x%08x, source_addr=0x%08x\n", block_no, mem_layout.flash_to_ram_addr);
#endif

		if (!rtk_eMMC_read(block_no, imageSize, (uint *)mem_layout.flash_to_ram_addr))
		{
			printf("[ERR] %s:Read kernel image error!!\n", __FUNCTION__);

			return RTK_PLAT_ERR_READ_KERNEL_IMG;
		}

		/* Check checksum */
		fw_checksum = get_checksum((uchar *)mem_layout.flash_to_ram_addr, imageSize);

		if (kernel_entry->checksum != fw_checksum)
		{
			printf("\t Kernel checksum FAILED\n");
			printf("\t Kernel entry  checksum=0x%08x\n", kernel_entry->checksum);
			printf("\t Kernel result checksum=0x%08x\n", fw_checksum);
		}

		/* if secure mode, do AES CBC decrypt */
		if (secure_mode == RTK_SECURE_BOOT)
		{
			rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
			//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(rtk_mem_info->encrypted_fw_image_addr+kernel_entry->length-512), 512);

			// decrypt image
			printf("to decrypt...\n");
			mem_layout.decompressed_addr &= (~MIPS_KSEG_MSK);
			if (decrypt_image_fpk((char *)mem_layout.encrpyted_addr,
				(char *)mem_layout.decrypted_addr,
				imageSize-img_truncated_size
				))
			{
				printf("decrypt image(%d) error!\n", kernel_entry->type);
				return RTK_PLAT_ERR_READ_KERNEL_IMG;
			}

			rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

#if (0)
			reverse_signature( (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size) );

			ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
			                          imageSize - img_truncated_size,
			                          (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size),
			                          1 );
			if( ret < 0 ) {
				printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
				return RTK_PLAT_ERR_READ_KERNEL_IMG;
			}
#endif
			printf("skip SHA256 check...\n");
			imageSize = imageSize - img_truncated_size;
		}

		/* if lzma kernel, decompress kernel image to target_addr */
		if (kernel_entry->lzma)
		{
			if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
			{
				printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

				return RTK_PLAT_ERR_READ_KERNEL_IMG;
			}
		}

		/* update bootm_headers_t to be compitable with U-boot */
		memset(images, 0, sizeof(bootm_headers_t));
		images->ep = (ulong)mem_layout.image_target_addr;

	}
#endif

	return RTK_PLAT_ERR_OK;
}

/*
 * Read kernel image from NAND flash to ram.
 */
int rtk_plat_read_kernel_image_from_NAND(bootm_headers_t *images)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
	struct nand_chip *this = (struct nand_chip *) nand->priv;
	unsigned long int from;
	unsigned int retlen;

	int ret = 0;
	unsigned int img_truncated_size = 0; // install_a will append 256-byte signature data to it
	uint decompressedSize = 0;
	uint imageSize = 0;
	//uint block_no = 0;
	uint fw_checksum = 0;
	MEM_LAYOUT_WHEN_READ_IMAGE_T mem_layout;
	unsigned int secure_mode = 0;
	unsigned int * Kh_key_ptr = DEFAULT_KEY_PTR;

	img_truncated_size = RSA_SIGNATURE_LENGTH + sizeof(struct image_extra_info);

	if (kernel_entry == NULL)
	{
		printf("[ERR] %s:kernel_entry is NULL!!\n", __FUNCTION__);

		return RTK_PLAT_ERR_READ_KERNEL_IMG;
	}
	else
	{

#ifdef DUBUG_FW_DESC_TABLE
		printf("[DBG] kernel_entry->offset = 0x%08x \n", kernel_entry->offset);
		printf("[DBG] kernel_entry->length = 0x%08x \n", kernel_entry->length);
		printf("[DBG] kernel_entry->target_addr = 0x%08x \n", kernel_entry->target_addr);
		printf("[DBG] kernel_entry->lzma = 0x%08x \n", kernel_entry->lzma);
#endif

		secure_mode = rtk_get_secure_boot_type();

		/* get memory layout before copy kernel image */
		mem_layout.bIsEncrypted = (secure_mode != NONE_SECURE_BOOT);
		mem_layout.bIsCompressed = kernel_entry->lzma;
		mem_layout.image_target_addr = kernel_entry->target_addr & (~MIPS_KSEG_MSK);

		get_mem_layout_when_read_image(&mem_layout);

		/* read kernel image from flash */
#if 0
		mem_layout.flash_to_ram_addr -= (kernel_entry->offset % EMMC_BLOCK_SIZE);

		imageSize = kernel_entry->length;

		block_no = (eMMC_fw_desc_table_start + kernel_entry->offset) / EMMC_BLOCK_SIZE;

#ifdef DUBUG_FW_DESC_TABLE
		printf("[DBG] kernel block_no=0x%08x, source_addr=0x%08x\n", block_no, mem_layout.flash_to_ram_addr);
#endif

		if (!rtk_eMMC_read(block_no, imageSize, (uint *)mem_layout.flash_to_ram_addr))
		{
			printf("[ERR] %s:Read kernel image error!!\n", __FUNCTION__);

			return RTK_PLAT_ERR_READ_KERNEL_IMG;
		}
#else

		mem_layout.flash_to_ram_addr -= (kernel_entry->offset % nand->erasesize);

		imageSize = kernel_entry->length;

		from = NAND_fw_desc_table_start + kernel_entry->offset;		//must define NAND_fw_desc_table_start

#ifdef DUBUG_FW_DESC_TABLE
//		printf("[DBG] kernel block_no=0x%08x, source_addr=0x%08x\n", block_no, mem_layout.flash_to_ram_addr);
#endif
		nand->read(nand, from, imageSize, &retlen, (uint *)mem_layout.flash_to_ram_addr);
		if (retlen != imageSize)
		{
			/* Read error */
			printf("[ERR] %s:Read kernel image error!!\n", __FUNCTION__);

			return RTK_PLAT_ERR_READ_KERNEL_IMG;
		}else
		{
			/* Read success */
			printf("[OK] %s:Read kernel image ok!!\n", __FUNCTION__);
		}
#endif
		/* Check checksum */
		fw_checksum = get_checksum((uchar *)mem_layout.flash_to_ram_addr, imageSize);

		if (kernel_entry->checksum != fw_checksum)
		{
			printf("\t Kernel checksum FAILED\n");
			printf("\t Kernel entry  checksum=0x%08x\n", kernel_entry->checksum);
			printf("\t Kernel result checksum=0x%08x\n", fw_checksum);
		}

		/* if secure mode, do AES CBC decrypt */
		if (secure_mode == RTK_SECURE_BOOT)
		{
			rtk_hexdump("the first 32-byte encrypted data", (unsigned char *)mem_layout.encrpyted_addr, 32);
			//rtk_hexdump("the last 512-byte encrypted data", (unsigned char *)(rtk_mem_info->encrypted_fw_image_addr+kernel_entry->length-512), 512);

			// decrypt image
			printf("to decrypt...\n");
			mem_layout.decompressed_addr &= (~MIPS_KSEG_MSK);
			if (decrypt_image_fpk((char *)mem_layout.encrpyted_addr,
				(char *)mem_layout.decrypted_addr,
				imageSize-img_truncated_size
				))
			{
				printf("decrypt image(%d) error!\n", kernel_entry->type);
				return RTK_PLAT_ERR_READ_KERNEL_IMG;
			}

			rtk_hexdump("the first 32-byte decrypted data", (unsigned char *)mem_layout.decrypted_addr, 32);

#if (0)
			reverse_signature( (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size) );

			ret = Verify_SHA256_hash( (unsigned char *)mem_layout.decrypted_addr,
			                          imageSize - img_truncated_size,
			                          (unsigned char *)(mem_layout.encrpyted_addr + imageSize - img_truncated_size),
			                          1 );
			if( ret < 0 ) {
				printf("[ERR] %s: verify hash fail(%d)\n", __FUNCTION__, ret );
				return RTK_PLAT_ERR_READ_KERNEL_IMG;
			}
#endif
			//printf("skip SHA256 check...\n");
			imageSize = imageSize - img_truncated_size;
		}

		/* if lzma kernel, decompress kernel image to target_addr */
		if (kernel_entry->lzma)
		{
			if (lzmaBuffToBuffDecompress((uchar*)mem_layout.decompressed_addr, &decompressedSize, (uchar*)mem_layout.compressed_addr, imageSize) != 0)
			{
				printf("[ERR] %s:Decompress using LZMA error!!\n", __FUNCTION__);

				return RTK_PLAT_ERR_READ_KERNEL_IMG;
			}
		}

		/* update bootm_headers_t to be compitable with U-boot */
		memset(images, 0, sizeof(bootm_headers_t));
		images->ep = (ulong)mem_layout.image_target_addr;

	}
#endif

	return RTK_PLAT_ERR_OK;
}

/*
 * Read kernel image from SPI flash to ram.
 */
int rtk_plat_read_kernel_image_from_SPI(bootm_headers_t *images)
{
	int ret = RTK_PLAT_ERR_READ_KERNEL_IMG;

	/* TODO */

	return ret;
}

//#define DEBUG_SKIP_BOOT_ALL
//#define DEBUG_SKIP_BOOT_LINUX
//#define DEBUG_SKIP_BOOT_AV

int rtk_plat_boot_setup(bootm_headers_t *images)
{
	int ret = RTK_PLAT_ERR_OK;
	char cmd[16];

	printf("Start Boot Setup ... ");

	/* reset some shared memory */
	reset_shared_memory();

#ifdef DEBUG_SKIP_BOOT_ALL // Skip by CK
	printf("(CK skip)\n");
	return RTK_PLAT_ERR_PARSE_FW_DESC;
#else
	printf("\n");
#endif

	if (boot_from_usb != BOOT_FROM_USB_DISABLE) // workaround path that read fw img from usb
	{
		memset(cmd, 0, sizeof(cmd));
		sprintf(cmd, "usb start_ac");

		ret = run_command(cmd, 0);

		if (ret != 0)
		{
			/* usb start_ac error */
			printf("[ERR] %s:failed (%s)\n", __FUNCTION__, cmd);
		}
		else
		{
			ret = rtk_plat_prepare_fw_image_from_USB();
		}
	}
	else
	{
		/* parse fw_desc_table, and read all data from flash to ram except kernel image */
		if (boot_flash_type == BOOT_EMMC)
		{
			/* For eMMC */
			ret = rtk_plat_prepare_fw_image_from_eMMC();
		}
		else if (boot_flash_type == BOOT_NAND)
		{
			/* For NAND */
#ifdef CONFIG_KCPU_LOAD_K_FW
			ret = run_command("kboot normal", 0);
#endif
			ret = rtk_plat_prepare_fw_image_from_NAND();
		}
		else
		{
			/* For SPI */
			ret = rtk_plat_prepare_fw_image_from_SPI();
		}
	}

#ifndef DEBUG_SKIP_BOOT_AV // mark for boot linux kernel only
	if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE)
	{
		if (ret == RTK_PLAT_ERR_OK)
		{
#ifndef CONFIG_KCPU_LOAD_K_FW
			if (*KcpuFW_entry_ptr != 0) {
				printf("Start KCPU Firmware ...\n");
				if (boot_prep_linux_kcpu() !=0) {
					printf("boot_prep_linux_kcpu failed\n");
					return 0;
				}
			}
#endif

			/* Flush caches */
			flush_dcache_all();

			if (*AudioFW_entry_ptr != 0)
			{
		#ifdef ENABLE_ACPU_BISR
				mdelay(10);
				printf("%s %d hold_hw_semaphore\n", __FUNCTION__, __LINE__);
				hold_hw_semaphore();
		#endif

				// clk = 0
				rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22); // aio, ae
				rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6); // ade, acpu
				// rst = 0
				rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);   // aio, ae
				rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT0);   // acpu
				rtd_clearbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);  //dac1, dac2
				udelay(10);
				// rst = 1
				rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT15 | _BIT28);
				rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT0);
				rtd_setbits(CRT_SOFT_RESET3_VADDR, _BIT6 | _BIT8);
				udelay(10);
				// clk = 1
				rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT10 | _BIT22);
				rtd_setbits(CRT_GROUP1_CK_EN_VADDR, _BIT19 | _BIT18 | _BIT17 | _BIT15 | _BIT14 | _BIT13);
				rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT4 | _BIT6);

				unmute_amp();

		#ifdef ENABLE_ACPU_BISR
				do_acpu_bisr();
		#endif

				//printf("aa 0x%x, 0x%x, 0x%x, 0x%x\n", rtd_inl(0x00000094), rtd_inl(0x00000098), rtd_inl(0x0000009c), rtd_inl(0x000000a0));

				/* Release HW Semaphore before enable ACPU clock, prevent VCPU2 blocking */
				printf("Release HW semaphore\n");
				release_hw_semaphore();

				mdelay(50);
			}

#if( CONFIG_SYS_TEXT_BASE != 0x00020000 )
			/* a_entry fw was loaded by bootloader function  */
			/* delay 50 ms to read debug message more easily */
			mdelay(50);
#endif
			if (*VideoFW_entry_ptr_V1 != 0)
			{
#ifdef ENABLE_VCPU_BISR
				mdelay(10);
				printf("%s %d hold_hw_semaphore\n", __FUNCTION__, __LINE__);
				hold_hw_semaphore();
#endif

				printf("Enable VCPU1\n");
				/* Enable VCPU clock */
				// clk = 1
				rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
				rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);
				// clk = 0
				rtd_clearbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17); // ve, se
				rtd_clearbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7); // vcpu, vde, me
				// rst = 0
				rtd_clearbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
				rtd_clearbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
				udelay(10);
				// rst = 1
				rtd_setbits(CRT_SOFT_RESET1_VADDR, _BIT16 | _BIT17 | _BIT18 | _BIT22);
				rtd_setbits(CRT_SOFT_RESET2_VADDR, _BIT1 | _BIT3);
				udelay(10);
				// clk = 1
				rtd_setbits(CRT_CLOCK_ENABLE1_VADDR, _BIT8 | _BIT12 | _BIT13 | _BIT17);
				rtd_setbits(CRT_CLOCK_ENABLE2_VADDR, _BIT5 | _BIT7);

#ifdef ENABLE_VCPU_BISR
				do_vcpu_bisr();
#endif

				//printf("aa 0x%x, 0x%x, 0x%x, 0x%x\n", rtd_inl(0x00000094), rtd_inl(0x00000098), rtd_inl(0x0000009c), rtd_inl(0x000000a0));
				printf("Release HW semaphore again\n");
				release_hw_semaphore();
			}

			if (*KcpuFW_entry_ptr != 0) {
#ifdef CONFIG_KCPU_LOAD_K_FW
				run_command("kboot wait", 0);
				run_command("kboot go_k", 0);
#else
				printf("Enable KCPU\n");
				rtd_outl(CRT_WDOG_DATA10_VADDR, *KcpuFW_entry_ptr);

				//release hw semaphore
				rtd_outl(0xb801a630, 0x0);
#endif
			}
		}
	}
	else
	{
		printf("[Skip A] boot manual mode\n");
		printf("[Skip V] boot manual mode\n");
	}
#endif

	if (ret == RTK_PLAT_ERR_OK)
	{
		if (boot_from_usb != BOOT_FROM_USB_DISABLE) // workaround path that read fw img from usb
		{
			ret = rtk_plat_read_kernel_image_from_USB(images, (boot_from_usb == BOOT_FROM_USB_COMPRESSED) ? 1 : 0);

			memset(cmd, 0, sizeof(cmd));
			sprintf(cmd, "usb stop");

			if (run_command(cmd, 0))
			{
				/* Usb stop error */
				printf("[ERR] %s:failed (%s)\n", __FUNCTION__, cmd);
			}
		}
		else
		{
			/* read kernel image from flash to ddr, that is used to speed up the appearance of booting logo */
			if (boot_flash_type == BOOT_EMMC)
			{
				/* For eMMC */
				ret = rtk_plat_read_kernel_image_from_eMMC(images);
			}
			else if (boot_flash_type == BOOT_NAND)
			{
				/* For NAND */
				ret = rtk_plat_read_kernel_image_from_NAND(images);
			}
			else
			{
				/* For SPI */
				ret = rtk_plat_read_kernel_image_from_SPI(images);
			}
		}
	}

	return ret;
}

int rtk_plat_boot_go(bootm_headers_t *images)
{
	do_bootm_linux(0, 0, NULL, images);

	/* Reached here means jump to kernel entry flow failed */

	return RTK_PLAT_ERR_BOOT;
}

/*
 ************************************************************************
 *
 * This is the final part before booting Linux in realtek platform:
 * we need to move audio/video firmware and stream files
 * from flash to ram. We will also decompress or decrypt image files,
 * if necessary, which depends on the information from flash writer.
 *
 ************************************************************************
 */
int  rtk_plat_boot_handler(void)
{
	bootm_headers_t	images;
	int ret = RTK_PLAT_ERR_OK;

#if 0 // patch for FPGA
//	printf("## [FIXME] rtk_plat_boot_handler()--patch for FPGA\n");
	images.ep = LINUX_KERNEL_ENTRY;
#else
	/* copy audio/video firmware and stream files from flash to ram */
	ret = rtk_plat_boot_setup(&images);

#ifdef CONFIG_PANEL_INIT_2ND_AFTER_LOGO
	panel_init_2nd();
#endif
#ifdef CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC//20140429 markchen add unmute for power on music
	if(boot_power_on_mode == POWER_ON)
	{
		//if(IO_Get(PIN_HP_OUT_JD))
		IO_Set(PIN_AMP_MUTE, 0);
		//IO_Set(PIN_GREEN_LED, 0);
		if ( bootparam.konka_sleepled_mode == 1 )
			IO_Set(PIN_RED_LED, 0);
		else
			IO_Set(PIN_RED_LED, 1);
	}
#elif defined(CONFIG_BOARD_298X_TV013_QFP176_EMMC)
	if(boot_power_on_mode == POWER_ON && bootparam.boot_music_enable == 1)
		IO_Set(PIN_AMP_MUTE, 0);
#elif defined(CONFIG_BOARD_298X_TV003_QFP176_V2_NAND)
    if (boot_power_on_mode == POWER_ON)
    	IO_Set(PIN_LED_W, 1);
#endif

#endif

#if defined(CONFIG_BOOTUP_BY_PREV_POWER_STATUS) || defined(ENABLE_BOOTUP_POLICY)
	//bcoz set_bootparam_power_state waste 250ms. put here for speed up BootLogo
	if (boot_ac_on && (prev_power_on_status == POWER_OFF) && (boot_power_on_mode == POWER_ON)) {
		WATCHDOG_KICK();
		set_bootparam_power_state(POWER_ON);
		WATCHDOG_KICK();
	}
#endif

#if defined (CONFIG_BOARD_298X_TV010_QFP176_V3_EMMC)
	if(boot_power_on_mode == POWER_ON) {
		IO_Set(PIN_LED_ON_OFF, 1);
       }
#endif
#if defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
	if(boot_power_on_mode == POWER_ON) {
		IO_Set(PIN_RLED_ON_OFF, 0);
		IO_Set(PIN_GLED_ON_OFF, 1);
	}
	else{
		IO_Set(PIN_RLED_ON_OFF, 1);
		IO_Set(PIN_GLED_ON_OFF, 0);
	}
#endif

	if (ret == RTK_PLAT_ERR_OK)
	{
#ifndef DEBUG_SKIP_BOOT_LINUX
		if (boot_from_flash == BOOT_FROM_FLASH_NORMAL_MODE)
		{
			/* go Linux */
#ifdef CONFIG_REALTEK_WATCHDOG
			WATCHDOG_KICK();
#else
			WATCHDOG_DISABLE();
#endif

			EXECUTE_CUSTOMIZE_FUNC(1); // insert execute customer callback at here

			ret = rtk_plat_boot_go(&images);
		}
		else
		{
			printf("[Skip K] boot manual mode (execute \"go all\")\n");
		}
#endif
	}

	return ret;
}

int rtk_plat_do_bootr(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
//	int ret = RTK_PLAT_ERR_OK;

	/* reset boot flags */
	boot_from_flash = BOOT_FROM_FLASH_NORMAL_MODE;
	boot_from_usb = BOOT_FROM_USB_DISABLE;

	/* parse option */
	if (argc == 1)
	{
		boot_from_usb = BOOT_FROM_USB_DISABLE;
	}
	else if (argc == 2 && argv[1][0] == 'u')
	{
		if (argv[1][1] == 'z')
		{
			boot_from_usb = BOOT_FROM_USB_COMPRESSED;
		}
		else if (argv[1][1] == '\0')
		{
			boot_from_usb = BOOT_FROM_USB_UNCOMPRESSED;
		}
		else
		{
			return CMD_RET_USAGE;
		}
	}
	else if (argc == 2 && argv[1][0] == 'm')
	{
		boot_from_flash = BOOT_FROM_FLASH_MANUAL_MODE;
	}
	else
	{
		return CMD_RET_USAGE;
	}

	WATCHDOG_KICK();

	rtk_plat_boot_handler();

	return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
	bootr, 2, 0,	rtk_plat_do_bootr,
	"boot realtek platform",
	"[u/uz]\n"
	"\tu   - boot from usb\n"
	"\tuz  - boot from usb (use lzma image)\n"
	"\tm   - read fw from flash but boot manually (go all)\n"
);

