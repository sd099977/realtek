/* Copyright (C) 2011
 * Corscience GmbH & Co. KG - Simon Schwarz <schwarz@corscience.de>
 *  - Added prep subcommand support
 *  - Reorganized source - modeled after powerpc version
 *
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * Copyright (C) 2001  Erik Mouw (J.A.K.Mouw@its.tudelft.nl)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307	 USA
 *
 */

#include <common.h>
#include <command.h>
#include <image.h>
#include <u-boot/zlib.h>
#include <asm/byteorder.h>
#include <fdt.h>
#include <libfdt.h>
#include <fdt_support.h>
#include <asm/bootm.h>
#include <exports.h>
#include <environment.h>
#include <wakeup.h>
#include <asm/arch/system.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/bootparam.h>
#include <platform_lib/board/pcb_mgr.h>
#include <platform_lib/board/pcb.h>
DECLARE_GLOBAL_DATA_PTR;

#if defined(CONFIG_SETUP_MEMORY_TAGS) || \
	defined(CONFIG_CMDLINE_TAG) || \
	defined(CONFIG_INITRD_TAG) || \
	defined(CONFIG_SERIAL_TAG) || \
	defined(CONFIG_REVISION_TAG)
static struct tag *params;
#endif

extern uint *KcpuFW_entry_ptr;
extern uint *boot_av_info_ptr;
extern int boot_power_on_mode;
extern uint b_fw_desc_table_vaild;

extern int rtk_plat_read_fw_desc_table_from_eMMC(void);
extern int rtk_plat_read_fw_desc_table_from_NAND(void);

#ifdef CONFIG_LMB
static ulong get_sp(void)
{
	ulong ret;

	asm("mov %0, sp" : "=r"(ret) : );
	return ret;
}

void arch_lmb_reserve(struct lmb *lmb)
{
	ulong sp;

	/*
	 * Booting a (Linux) kernel image
	 *
	 * Allocate space for command line and board info - the
	 * address should be as high as possible within the reach of
	 * the kernel (see CONFIG_SYS_BOOTMAPSZ settings), but in unused
	 * memory, which means far enough below the current stack
	 * pointer.
	 */
	sp = get_sp();
	debug("## Current stack ends at 0x%08lx ", sp);

	/* adjust sp by 1K to be safe */
	sp -= 1024;
	lmb_reserve(lmb, sp,
		    gd->bd->bi_dram[0].start + gd->bd->bi_dram[0].size - sp);
}
#endif

#ifdef CONFIG_OF_LIBFDT
static int fixup_memory_node(void *blob)
{
	bd_t	*bd = gd->bd;
	int bank;
	u64 start[CONFIG_NR_DRAM_BANKS];
	u64 size[CONFIG_NR_DRAM_BANKS];

	for (bank = 0; bank < CONFIG_NR_DRAM_BANKS; bank++) {
		start[bank] = bd->bi_dram[bank].start;
		size[bank] = bd->bi_dram[bank].size;
	}

	return fdt_fixup_memory_banks(blob, start, size, CONFIG_NR_DRAM_BANKS);
}
#endif

static void announce_and_cleanup(void)
{
	display_evaluate_time("bootcode end");
	printf("Starting kernel ... \n");
	bootstage_mark_name(BOOTSTAGE_ID_BOOTM_HANDOFF, "start_kernel");
#ifdef CONFIG_BOOTSTAGE_REPORT
	bootstage_report();
#endif

#ifdef CONFIG_USB_DEVICE
	udc_disconnect();
#endif
	cleanup_before_linux();
}

#if defined(CONFIG_SETUP_MEMORY_TAGS) || \
	defined(CONFIG_CMDLINE_TAG) || \
	defined(CONFIG_INITRD_TAG) || \
	defined(CONFIG_SERIAL_TAG) || \
	defined(CONFIG_REVISION_TAG)
static void setup_start_tag (bd_t *bd)
{
	params = (struct tag *)bd->bi_boot_params;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}
#endif

#ifdef CONFIG_SETUP_MEMORY_TAGS
static void setup_memory_tags(bd_t *bd)
{
	int i;

	for (i = 0; i < CONFIG_NR_DRAM_BANKS; i++) {
		params->hdr.tag = ATAG_MEM;
		params->hdr.size = tag_size (tag_mem32);

		params->u.mem.start = bd->bi_dram[i].start;
		params->u.mem.size = bd->bi_dram[i].size;

		params = tag_next (params);
	}
}
#endif

#ifdef CONFIG_CMDLINE_TAG
static void setup_commandline_tag(bd_t *bd, char *commandline)
{
	char *p;

	if (!commandline)
		return;

	/* eat leading white space */
	for (p = commandline; *p == ' '; p++);

	/* skip non-existent command lines so the kernel will still
	 * use its default command line.
	 */
	if (*p == '\0')
		return;

	params->hdr.tag = ATAG_CMDLINE;
	params->hdr.size =
		(sizeof (struct tag_header) + strlen (p) + 1 + 4) >> 2;

	strcpy (params->u.cmdline.cmdline, p);

	params = tag_next (params);
}
#endif

#ifdef CONFIG_INITRD_TAG
static void setup_initrd_tag(bd_t *bd, ulong initrd_start, ulong initrd_end)
{
	/* an ATAG_INITRD node tells the kernel where the compressed
	 * ramdisk can be found. ATAG_RDIMG is a better name, actually.
	 */
	params->hdr.tag = ATAG_INITRD2;
	params->hdr.size = tag_size (tag_initrd);

	params->u.initrd.start = initrd_start;
	params->u.initrd.size = initrd_end - initrd_start;

	params = tag_next (params);
}
#endif

#ifdef CONFIG_SERIAL_TAG
void setup_serial_tag(struct tag **tmp)
{
	struct tag *params = *tmp;
	struct tag_serialnr serialnr;
	void get_board_serial(struct tag_serialnr *serialnr);

	get_board_serial(&serialnr);
	params->hdr.tag = ATAG_SERIAL;
	params->hdr.size = tag_size (tag_serialnr);
	params->u.serialnr.low = serialnr.low;
	params->u.serialnr.high= serialnr.high;
	params = tag_next (params);
	*tmp = params;
}
#endif

#ifdef CONFIG_REVISION_TAG
void setup_revision_tag(struct tag **in_params)
{
	u32 rev = 0;
	u32 get_board_rev(void);

	rev = get_board_rev();
	params->hdr.tag = ATAG_REVISION;
	params->hdr.size = tag_size (tag_revision);
	params->u.revision.rev = rev;
	params = tag_next (params);
}
#endif

#if defined(CONFIG_SETUP_MEMORY_TAGS) || \
	defined(CONFIG_CMDLINE_TAG) || \
	defined(CONFIG_INITRD_TAG) || \
	defined(CONFIG_SERIAL_TAG) || \
	defined(CONFIG_REVISION_TAG)
static void setup_end_tag(bd_t *bd)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}
#endif

#ifdef CONFIG_OF_LIBFDT
static int create_fdt(bootm_headers_t *images)
{
	ulong of_size = images->ft_len;
	char **of_flat_tree = &images->ft_addr;
	ulong *initrd_start = &images->initrd_start;
	ulong *initrd_end = &images->initrd_end;
	struct lmb *lmb = &images->lmb;
	ulong rd_len;
	int ret;

	debug("using: FDT\n");

	boot_fdt_add_mem_rsv_regions(lmb, *of_flat_tree);

	rd_len = images->rd_end - images->rd_start;
	ret = boot_ramdisk_high(lmb, images->rd_start, rd_len,
			initrd_start, initrd_end);
	if (ret)
		return ret;

	ret = boot_relocate_fdt(lmb, of_flat_tree, &of_size);
	if (ret)
		return ret;

	fdt_chosen(*of_flat_tree, 1);
	fixup_memory_node(*of_flat_tree);
	fdt_fixup_ethernet(*of_flat_tree);
	fdt_initrd(*of_flat_tree, *initrd_start, *initrd_end, 1);

	return 0;
}
#endif

/**********************************************************
 * Append the pointer information of env_vars to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_envp(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	int len = 0;

	if (env_export() < 0) {
		printf("[ERR] %s: Cannot export environment\n", __func__);
	}
	else {
		len = strlen(commandline) + 16;

		tmp_cmdline = (char *)malloc(len);
		if (!tmp_cmdline) {
			printf("[ERR] %s: Malloc failed\n", __func__);
		}
		else {
			memset(tmp_cmdline, 0, len);

			sprintf(tmp_cmdline, "%s envp=%lx", commandline, (ulong)env_get_export_all());

			setenv("bootargs", tmp_cmdline);

			free(tmp_cmdline);
		}
	}

	return 0;
}

/**********************************************************
 * Append the flash type information to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_flashtype(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	int len = 0;

	len = strlen(commandline) + 16;

	tmp_cmdline = (char *)malloc(len);
	if (!tmp_cmdline) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);

		sprintf(tmp_cmdline, "%s flashtype=%s", commandline, pcb_get_boot_flash_type_string());

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
	}

	return 0;
}

/**********************************************************
 * Append the reclaim memory information to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_reclaim(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	int len = 0;
	boot_av_info_t *boot_av = NULL;
	uint pov_size = 0;
	uint reclaim_size = 0;

	/* consider the video stream buffer size */
	boot_av = (boot_av_info_t *) MIPS_BOOT_AV_INFO_ADDR;
	pov_size = SWAPEND32(boot_av->dwVideoStreamLength);

	if (pov_size % 0x100000 != 0) { // align MB
		pov_size += 0x100000;
	}

	/* dynamic compute the reclaim size */
	reclaim_size = (POWER_ON_MUSIC_BUFFER_SIZE +
					POWER_ON_VIDEO_BUFFER_SIZE +
					POWER_ON_MUSIC_STREAM_SIZE +
					pov_size) >> 20;

	len = strlen(commandline) + 64;

	tmp_cmdline = (char *)malloc(len);
	if (!tmp_cmdline) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);

		sprintf(tmp_cmdline, "%s reclaim=%dM@%dM last_image=%dM@%dM", commandline,
			reclaim_size,
			KERNEL_RESERVE_FOR_POM_POV_ADDR >> 20,
			POWER_ON_VIDEO_LAST_IMAGE_SIZE >> 20,
			POWER_ON_VIDEO_LAST_IMAGE_ADDR >> 20
		);

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
	}

	return 0;
}

/**********************************************************
 * Append the quiet or earlyprintk parameter to control kernel print.
 **********************************************************/
static int rtk_plat_boot_prep_kernel_print(char *string)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	int len = 0;

	if (strstr(commandline, string) != NULL) { // check the specific string is existed or not
		return 0;
	}

	len = strlen(commandline) + strlen(string) + 4;

	tmp_cmdline = (char *)malloc(len);
	if (!tmp_cmdline) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);

		sprintf(tmp_cmdline, "%s %s", commandline, string);

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
	}

	return 0;
}

#ifndef CONFIG_SYS_RTK_NAND_FLASH
/**********************************************************
 * Append the mmcparts parameter to pass mmc partition info.
 **********************************************************/
static int rtk_plat_boot_prep_mmcparts(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	fw_desc_table_v1_t *fw_desc_table_v1 = NULL;
	part_desc_entry_v1_t *part_entry = NULL;
	int fw_desc_table_base = rtk_mem_info->fw_desc_table_base_addr;
	unsigned char empty_mount[sizeof(part_entry->mount_point)];
	char tmp_str_buf[64];
	int len = 0;
	int i = 0;
	int part_count = 0;
	unsigned int size = 0;
	int ret = RTK_PLAT_ERR_OK;

	// check if already copied fw desc table from flash to ram
	if (!b_fw_desc_table_vaild) {
		ret = rtk_plat_read_fw_desc_table_from_eMMC();
		if (ret != RTK_PLAT_ERR_OK)
		{
			printf("Read failed: ignore %s\n", __FUNCTION__);
			return 0;
		}
	}

	len = strlen(commandline) + 256;

	tmp_cmdline = (char *)malloc(len);
	if (!tmp_cmdline) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);
		memset(empty_mount, 0, sizeof(empty_mount));

		sprintf(tmp_cmdline, "%s mmcparts=rtkemmc:", commandline);

		/* get partition table from fw_desc_table */
		fw_desc_table_v1 = (fw_desc_table_v1_t *)fw_desc_table_base;
		part_count = fw_desc_table_v1->part_list_len / sizeof(part_desc_entry_v1_t);
		part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));

		/* append each partition info to command line */
		for (i = 0; i < part_count; i++)
		{
			memset(tmp_str_buf, 0, sizeof(tmp_str_buf));
			size = part_entry[i].length / 0x400; // kbytes

			if (memcmp(empty_mount, part_entry[i].mount_point, sizeof(empty_mount)) != 0) {
				sprintf((char *)tmp_str_buf, "%uk(%s)", size, part_entry[i].mount_point);
			}
			else {
				sprintf((char *)tmp_str_buf, "%uk", size);
			}

			strcat(tmp_cmdline, (char *)tmp_str_buf);

			if (i != (part_count - 1)) {
	       		strncat(tmp_cmdline, ",", 1);
	       	}
		}

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
	}

	return 0;
}
#else	//CONFIG_SYS_RTK_NAND_FLASH

/**********************************************************
 * Append the mtdparts information to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_mtdparts(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	fw_desc_table_v1_t *fw_desc_table_v1 = NULL;
	part_desc_entry_v1_t *part_entry = NULL;
	int fw_desc_table_base = rtk_mem_info->fw_desc_table_base_addr;
	unsigned char empty_mount[sizeof(part_entry->mount_point)];
	char tmp_str_buf[64];
	fw_type_code_t  root_type;	
	int len = 0;
	int i = 0;
	int part_count = 0;
	unsigned int size = 0;
	int ret = RTK_PLAT_ERR_OK;

	// check if already copied fw desc table from flash to ram
	if (!b_fw_desc_table_vaild) {
		ret = rtk_plat_read_fw_desc_table_from_NAND();
		if (ret != RTK_PLAT_ERR_OK)
		{
			printf("Read failed: ignore %s\n", __FUNCTION__);
			return 0;
		}
	}

	len = strlen(commandline) + 256;

	tmp_cmdline = (char *)malloc(len);
	if (!tmp_cmdline) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);
		memset(empty_mount, 0, sizeof(empty_mount));

		sprintf(tmp_cmdline, "%s mtdparts=rtk_nand:", commandline);

		/* get partition table from fw_desc_table */
		fw_desc_table_v1 = (fw_desc_table_v1_t *)fw_desc_table_base;
		part_count = fw_desc_table_v1->part_list_len / sizeof(part_desc_entry_v1_t);
		part_entry = (part_desc_entry_v1_t *)(fw_desc_table_base + sizeof(fw_desc_table_v1_t));

		/* append each partition info to command line */
		for (i = 0; i < part_count; i++)
		{
			memset(tmp_str_buf, 0, sizeof(tmp_str_buf));
			size = part_entry[i].length / 0x400; // kbytes

			if (memcmp(empty_mount, part_entry[i].mount_point, sizeof(empty_mount)) != 0) {
				sprintf((char *)tmp_str_buf, "%uk(%s)", size, part_entry[i].mount_point);
			}
			else {
				sprintf((char *)tmp_str_buf, "%uk", size);
			}
			if ((part_entry[i].type == PART_TYPE_FS) &&
	       		(strlen((char *)part_entry[i].mount_point) == 1) &&	// rootfs is "/"
	       		(strcmp("/", (char *)part_entry[i].mount_point) == 0)) {
	       		if (part_entry[i].fw_type == FW_TYPE_RESERVED) {
	       			root_type = FW_TYPE_YAFFS2;
					printf("claire check @ %dth - FW_TYPE_YAFFS2\n\n",i);
	       		} else {
	       			root_type = part_entry[i].fw_type;
					printf("claire check @ %dth - type:%d\n\n", i, part_entry[i].fw_type);		
	       		}
			}
			strcat(tmp_cmdline, (char *)tmp_str_buf);

			if (i != (part_count - 1)) {
	       		strncat(tmp_cmdline, ",", 1);
	       	}
		}

		memset(tmp_str_buf, 0, sizeof(tmp_str_buf));
		sprintf(tmp_str_buf, " rootfstype=%s root=31:01", (root_type == FW_TYPE_SQUASH ? "squashfs" : "yaffs2"));
		strncat(tmp_cmdline, tmp_str_buf, strlen(tmp_str_buf));

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
	}

	return 0;
}
#endif

/**********************************************************
 * Append standby information to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_for_standby(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	char *tmp_cmdline_emcu = NULL;
	int len = 0;
	extern uchar boot_ac_on;
	len = strlen(commandline) + 24;

	tmp_cmdline = (char *)malloc(len);
	tmp_cmdline_emcu = (char *)malloc(24);

	if ((!tmp_cmdline) || (!tmp_cmdline_emcu)) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);
		memset(tmp_cmdline_emcu, 0, 24);

		if (boot_power_on_mode == POWER_OFF)
		{
			strcpy(tmp_cmdline_emcu, "POWERDOWN");
		}

		if (boot_ac_on)
		{
			//move to boot_prep_linux()
			//strcat(tmp_cmdline_emcu, " ac_on");
#ifdef CONFIG_MISC_MGR_WAKEUP
			rtkpm_clr_share_mem();
#endif
		}

#if defined(CONFIG_MISC_MGR_CUSTOM_TV010) && defined(CONFIG_MISC_MGR_WAKEUP)
		if(boot_power_on_mode == POWER_OFF)
		{
			unsigned int  keyarray[14] = {  0x0cf3f1f1,  //pwr
                                                        0xb6db6fff,
                                                                0x12edf1f1,
                                                                0x13ecf1f1,
                                                                0xfff1f1,  //zero
                                                                0x2fdf1f1,
                                                                0x3fcf1f1,
                                                                0x4fbf1f1,
                                                                0x5faf1f1,
                                                                0x6f9f1f1,
                                                                0x7f8f1f1,
                                                                0x8f7f1f1,
                                                                0x9f6f1f1,
                                                                0x1fef1f1       };      //nine
                        unsigned long long value1=0,value2=0;
                        unsigned long long pinarray[1] = {0x00};

                        if (pcb_mgr_get_enum_info_byname("POWER_EN", &value1) == 0)
                        {
                        	pinarray[0] = value1;//0x100010c04;//value1;
			}

			unsigned long long keypad[5]={0x00,0x00,0x00,0x00,0x00};
			unsigned long long value=0,value0=0,value3=0,value4=0,value5=0;
                        if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_UP", &value) == 0){
                        	keypad[0] = value;
                        }
                        if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_DOWN", &value0) == 0){
                                keypad[1] = value0;
                        }
                        if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_GUIDE", &value3) == 0){
                                keypad[2] = value3;
                        }
                        if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_SELECT", &value4) == 0){
                                keypad[3] = value4;
                        }
                        if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_MENU", &value5) == 0){
                                keypad[4] = value5;
                        }
                        rtkpm_clr_share_mem();
                        powerMgr_setup_power_en(1,&pinarray[0]);
                        powerMgr_setup_irda( 5,14,&keyarray[0]);
                        powerMgr_setup_keypad_multi(5,&keypad[0]);

                      }

#elif  defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC)
		if(boot_power_on_mode == POWER_OFF)
		{
			unsigned int  keyarray[5] = { 0xa05ffb04 ,0x0bf4e7e7 ,0x20b ,0x18e7e7e7 ,0x2379ff00};	//Power/Source/CH+/CH-
			unsigned long long value1=0,value2=0;
			unsigned long long pinarray[2] = { 0x00 ,0x00 };
		
			if (pcb_mgr_get_enum_info_byname("PIN_POWER_EN", &value1) == 0)
			{
				pinarray[0] = value1;//value1;
			}
			if (pcb_mgr_get_enum_info_byname("PIN_POWER_SOC_EN", &value2) == 0)
			{
				pinarray[1] = value2;
			}

			unsigned long long keypad[2]={0x00,0x00};
			unsigned long long value=0,value0=0;
			if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_PWR", &value) == 0){					
				keypad[0] = value;
			}
			if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_DOWN", &value0) == 0){
				keypad[1] = value0;
			}
				
			//rtd_maskl(0xb8061520,0xFFFFFFFE,0x1);//lsadc module  enable

			if ( bootparam.konka_sleepled_mode == 1 )
			{
				keyarray[4] = 0x2379ff01;   // set breathe logo LED
				rtd_maskl(0xb8060040,0xFFFFFFF7,0x1<<3);
				rtd_maskl(0xb8060030,0xFFFFFFF7,0x1<<3);
				rtd_maskl(0xb8060218,0xFFC1FFFF,0xC<<17);
				rtd_outl(0xb8061288,0x800030A8);
				rtd_outl(0xb8061284,0x60000000);
				rtd_outl(0xb806128c,0x00320063);				
			}
			else
				IO_Set(PIN_RED_LED, 0);
			
			rtkpm_clr_share_mem();
			powerMgr_setup_power_en(2,&pinarray[0]);
			powerMgr_setup_irda(10,5,&keyarray[0]);
			powerMgr_setup_keypad_multi(2,&keypad[0]);
				
		}
#elif defined(CONFIG_BOARD_298X_TV013_QFP176_EMMC)
		if(boot_power_on_mode == POWER_OFF)
		{
			unsigned int  keyarray[4] = { 0x0bf4e7e7, 0x19e6e7e7 ,0x18e7e7e7 ,0x20b};	//Power/Source/CH+/CH-
			unsigned long long value1=0,value2=0;
			unsigned long long pinarray[2] = { 0x00 ,0x00 };
			if (pcb_mgr_get_enum_info_byname("POWER_EN", &value1) == 0)
			{
				pinarray[0] = 0x100010c04;//value1;
			}
			if (pcb_mgr_get_enum_info_byname("PIN_POWER_SOC_EN", &value2) == 0){
				pinarray[1] = value2;
			}

			unsigned long long keypad[2]={0x00,0x00};
			unsigned long long value=0,value0=0;
			if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_PWR", &value) == 0){
				keypad[0] = value;
			}
			if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_DOWN", &value0) == 0){
				keypad[1] = value0;
			}
			if(bootparam.bootup_policy == 5)
				set_bootparam_policy(0);
			rtkpm_clr_share_mem();
			powerMgr_setup_power_en(2,&pinarray[0]);
			powerMgr_setup_irda(0,4,&keyarray[0]);
			powerMgr_setup_keypad_multi(2,&keypad[0]);
		}

#elif (defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1))
		if(boot_power_on_mode == POWER_OFF)
		{
			unsigned int  keyarray[4] = { 0xfe01bd00, 0xf708bd00 ,0xe718bd00 ,0xe31cbd00};	//Power/Source/CH+/CH- (AOC IrDA)
			unsigned long long value1=0,value2=0;
			unsigned long long pinarray[2] = { 0x00 ,0x00 };
			if (pcb_mgr_get_enum_info_byname("PIN_POWER_EN", &value1) == 0)
			{
				pinarray[0] = value1;//value1;
			}
		//	unsigned long long keypad[2]={0x00,0x00};
		//	unsigned long long value=0,value0=0;
		//	if (pcb_mgr_get_enum_info_byname("PIN_KEYPAD_PWR", &value) == 0){
		//		keypad[0] = value;
		//	}
			
		//	if(bootparam.bootup_policy == 5)
		//		set_bootparam_policy(0);
			rtkpm_clr_share_mem();
			powerMgr_setup_power_en(1,&pinarray[0]);
			powerMgr_setup_irda(1,4,&keyarray[0]);
		//	powerMgr_setup_keypad_multi(1,&keypad[0]);
		}
#elif defined(CONFIG_BOARD_298X_TV003_QFP176_V2_NAND)
		if(boot_power_on_mode == POWER_OFF)
		{
		    unsigned long long pinarray[2] = { 0x00 ,0x00 };
		    unsigned long long value=0;

		    IO_Set(PIN_LED_W, 0);		    
		    
		    rtkpm_clr_share_mem();
		    if ( pcb_mgr_get_enum_info_byname( "PIN_KEYPAD_PWR", &value ) == 0 )
		    {
		        powerMgr_setup_keypad_multi( 1, &value );
            }
            
            if ( pcb_mgr_get_enum_info_byname( "PIN_POWER_EN", &value ) == 0 )
            {
                pinarray[0] = value;
            }
            if ( pcb_mgr_get_enum_info_byname( "PIN_POWER_SOC_EN", &value ) == 0 )
            {
                pinarray[1] = value;
            }
			powerMgr_setup_power_en(2,&pinarray[0]);        		    
		}	
#elif defined(CONFIG_BOARD_298X_TV032_ATSC_QFP176_NAND)
		if(boot_power_on_mode == POWER_OFF)
		{
		    unsigned long long pinarray[2] = { 0x00 ,0x00 };
		    unsigned long long value=0;
			unsigned int  keyarray[9] = { 0xe11e7f00,0xb9467d02 ,0xf50aff80,0xa05ffb04, 0xff00855e,0xad52df20, 0x7d82fb41, 0xf708fb04,0xf50a4040};

		    IO_Set(PIN_LED_W, 0);		    
		    
		    rtkpm_clr_share_mem();
		    if ( pcb_mgr_get_enum_info_byname( "PIN_KEYPAD_PWR", &value ) == 0 )
		    {
		        powerMgr_setup_keypad_multi( 1, &value );
            }
            
            if ( pcb_mgr_get_enum_info_byname( "PIN_POWER_EN", &value ) == 0 )
            {
                pinarray[0] = value;
            }
          
			powerMgr_setup_power_en(1,&pinarray[0]); 
			powerMgr_setup_irda(1,9,&keyarray[0]);
		}	
#endif

		sprintf(tmp_cmdline, "%s %s", commandline, tmp_cmdline_emcu);

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
		free(tmp_cmdline_emcu);
	}

	return 0;
}

/**********************************************************
 * Append the cpu_nr information to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_cpus(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	int len = 0;
	int cpu_nr;
	unsigned int hw_cpu_nr;

	hw_cpu_nr = ((rtd_inl(0xb8017194) & (_BIT16 | _BIT17)) >> 16);

	if ((CONFIG_SYS_NR_CPUS == 0) || (hw_cpu_nr != 0)) { /* 0 means auto detect */
		cpu_nr = 4 - hw_cpu_nr;
	}
	else {
		cpu_nr = CONFIG_SYS_NR_CPUS;
		//set to max count, if setting is larger than 4.
		if (cpu_nr > 4) cpu_nr = 4;
		//set to min count, if setting is smaller than 0.
		if (cpu_nr < 0) cpu_nr = 1;
	}

	len = strlen(commandline) + 32;

	tmp_cmdline = (char *)malloc(len);
	if (!tmp_cmdline) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);

		if (cpu_nr == 1)	// nosmp option equal to maxcpus=0
			sprintf(tmp_cmdline, "%s nr_cpus=%d maxcpus=0", commandline, cpu_nr);
		else
			sprintf(tmp_cmdline, "%s nr_cpus=%d maxcpus=%d", commandline, cpu_nr, cpu_nr);

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
	}

   return 0;
}

/**********************************************************
 * Append the kcpu memory entry and size information to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_kcpu(void)
{
   char *commandline = getenv("bootargs");
   char *tmp_cmdline = NULL;
   int len = 0;
	unsigned int kentry = (*KcpuFW_entry_ptr & 0x1fffffff)- 0x1000;
	unsigned int ksize = 0x1dc00000 - kentry;

   len = strlen(commandline) + 64;

   tmp_cmdline = (char *)malloc(len);
   if (!tmp_cmdline) {
      printf("[ERR] %s: Malloc failed\n", __func__);
   }
   else {
      memset(tmp_cmdline, 0, len);

      sprintf(tmp_cmdline, "%s kentry=%dM@0x%x", commandline, ksize >> 20, kentry);
		setenv("bootargs", tmp_cmdline);

      free(tmp_cmdline);
	}

	return 0;
}

#ifdef CONFIG_IP_TO_KERNEL 
/**********************************************************
 * Append the network information to bootargs.
 **********************************************************/
static int rtk_plat_boot_prep_network(void)
{
	char *commandline = getenv("bootargs");
	char *tmp_cmdline = NULL;
	int len = 0;

	len = strlen(commandline) + 64;

	tmp_cmdline = (char *)malloc(len);
	if (!tmp_cmdline) {
		printf("[ERR] %s: Malloc failed\n", __func__);
	}
	else {
		memset(tmp_cmdline, 0, len);

		sprintf(tmp_cmdline, "%s ip=%s::%s:%s", commandline, getenv("ipaddr"), getenv("gatewayip"), getenv("netmask"));

		setenv("bootargs", tmp_cmdline);

		free(tmp_cmdline);
	}

	return 0;
}
#endif	//CONFIG_IP_TO_KERNEL

/* Subcommand: PREP */
static void boot_prep_linux(bootm_headers_t *images)
{
#ifdef CONFIG_CMDLINE_TAG
	char *commandline = NULL;
	extern uchar boot_ac_on;

	rtk_plat_boot_prep_envp();
	rtk_plat_boot_prep_flashtype();
	rtk_plat_boot_prep_cpus();
	
#ifndef CONFIG_SYS_RTK_NAND_FLASH
	rtk_plat_boot_prep_mmcparts();
#else
	rtk_plat_boot_prep_mtdparts();
#endif

#ifdef CONFIG_IP_TO_KERNEL
	rtk_plat_boot_prep_network();
#endif

	if (*KcpuFW_entry_ptr != 0)
		rtk_plat_boot_prep_kcpu();

	// boot animation existed
	if (*boot_av_info_ptr != 0)
	{
		rtk_plat_boot_prep_reclaim();
	}

	// en/disable kernel print message
	if (boot_mode != BOOT_RESCUE_MODE && getenv("silent") != NULL)
	{
		rtk_plat_boot_prep_kernel_print("quiet");
	}
	else
	{
		rtk_plat_boot_prep_kernel_print("earlyprintk");
	}

	if (boot_ac_on)
		rtk_plat_boot_prep_kernel_print("ac_on");

	if (boot_mode != BOOT_RESCUE_MODE) // Add for fixing Rescue Kernel stop at 8051 standby
	{
		if (boot_power_on_mode == POWER_OFF)
			rtk_plat_boot_prep_for_standby();
	}

	commandline = getenv("bootargs");
	printf("Kernel command line: %s\n", commandline);
#endif

#ifdef CONFIG_OF_LIBFDT
	if (images->ft_len) {
		debug("using: FDT\n");
		if (create_fdt(images)) {
			printf("FDT creation failed! hanging...");
			hang();
		}
	} else
#endif
	{
#if defined(CONFIG_SETUP_MEMORY_TAGS) || \
	defined(CONFIG_CMDLINE_TAG) || \
	defined(CONFIG_INITRD_TAG) || \
	defined(CONFIG_SERIAL_TAG) || \
	defined(CONFIG_REVISION_TAG)
		debug("using: ATAGS\n");
		setup_start_tag(gd->bd);
#ifdef CONFIG_SERIAL_TAG
		setup_serial_tag(&params);
#endif
#ifdef CONFIG_CMDLINE_TAG
		setup_commandline_tag(gd->bd, commandline);
#endif
#ifdef CONFIG_REVISION_TAG
		setup_revision_tag(&params);
#endif
#ifdef CONFIG_SETUP_MEMORY_TAGS
		setup_memory_tags(gd->bd);
#endif
#ifdef CONFIG_INITRD_TAG
		if (images->rd_start && images->rd_end)
			setup_initrd_tag(gd->bd, images->rd_start,
			images->rd_end);
#endif
		setup_end_tag(gd->bd);
#else /* all tags */
		printf("FDT and ATAGS support not compiled in - hanging\n");
		hang();
#endif /* all tags */
	}
}

//#define DEBUG_DUMP_ENV_RESULT
#ifdef DEBUG_DUMP_ENV_RESULT
int *_prom_envp;
#define GET_ENV(index) ((char *)(int)_prom_envp[(index)])
#endif

/* Subcommand: GO */
static void boot_jump_linux(bootm_headers_t *images)
{
	unsigned long machid = gd->bd->bi_arch_number;
	char *s;
	void (*kernel_entry)(int zero, int arch, uint params);
	unsigned long r2;

	kernel_entry = (void (*)(int, int, uint))images->ep;

	s = getenv("machid");
	if (s) {
		strict_strtoul(s, 16, &machid);
		printf("Using machid 0x%lx from environment\n", machid);
	}

	debug("## Transferring control to Linux (at address %08lx)" \
		"...\n", (ulong) kernel_entry);
	bootstage_mark(BOOTSTAGE_ID_RUN_OS);

	announce_and_cleanup();
#ifdef CONFIG_OF_LIBFDT
	if (images->ft_len)
		r2 = (unsigned long)images->ft_addr;
	else
#endif
		r2 = gd->bd->bi_boot_params;

	debug("bootargs=%s\n", getenv("bootargs"));
	debug("%s 0x%08x(0x%x,0x%lx,0x%lx)\n", __func__, (unsigned int)kernel_entry, 0, machid, r2);

	kernel_entry(0, machid, r2);
}

/* Main Entry point for arm bootm implementation
 *
 * Modeled after the powerpc implementation
 * DIFFERENCE: Instead of calling prep and go at the end
 * they are called if subcommand is equal 0.
 */
int do_bootm_linux(int flag, int argc, char *argv[], bootm_headers_t *images)
{
	/* No need for those on ARM */
	if (flag & BOOTM_STATE_OS_BD_T || flag & BOOTM_STATE_OS_CMDLINE)
		return -1;

	if (flag & BOOTM_STATE_OS_PREP) {
		boot_prep_linux(images);
		return 0;
	}

	if (flag & BOOTM_STATE_OS_GO) {
		boot_jump_linux(images);
		return 0;
	}

	boot_prep_linux(images);
	boot_jump_linux(images);
	return 0;
}

#ifdef CONFIG_CMD_BOOTZ

struct zimage_header {
	uint32_t	code[9];
	uint32_t	zi_magic;
	uint32_t	zi_start;
	uint32_t	zi_end;
};

#define	LINUX_ARM_ZIMAGE_MAGIC	0x016f2818

int bootz_setup(void *image, void **start, void **end)
{
	struct zimage_header *zi = (struct zimage_header *)image;

	if (zi->zi_magic != LINUX_ARM_ZIMAGE_MAGIC) {
		puts("Bad Linux ARM zImage magic!\n");
		return 1;
	}

	*start = (void *)zi->zi_start;
	*end = (void *)zi->zi_end;

	debug("Kernel image @ 0x%08x [ 0x%08x - 0x%08x ]\n",
		(uint32_t)image, (uint32_t)*start, (uint32_t)*end);

	return 0;
}
#endif	/* CONFIG_CMD_BOOTZ */
