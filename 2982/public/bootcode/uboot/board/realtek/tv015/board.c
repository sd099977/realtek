/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * Time initialization.
 */
#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/system.h>

DECLARE_GLOBAL_DATA_PTR;

const struct rtd298x_sysinfo sysinfo = {
#if defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
	"Board: TV015 1st ver. Board(TPV XM)\n"	
#else
	"Board: TV015 1st ver. Board(TPV TPE)\n"
#endif
};

/**
 * @brief checkboard
 *
 * @return 0
 */
int checkboard(void)
{
	printf(sysinfo.board_string);
    return 0;
}

/**
 * @brief board_init
 *
 * @return 0
 */
int board_init(void)
{
	gd->bd->bi_arch_number = MACH_TYPE_RTK_RTD298X;
	gd->bd->bi_boot_params = CONFIG_BOOT_PARAM_BASE; /* boot param addr */

	return 0;
}

/**
 * @brief dram_init_banksize
 *
 * @return 0
 */
void dram_init_banksize(void)
{
	unsigned int ddr_size = 0;

	// Bank 1
	ddr_size = get_ddr_size(0);

	//printf("DDR SIZE=0x%x\n", ddr_size);

	if (ddr_size > CONFIG_SYS_RAM_DCU1_SIZE) {
		gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
		gd->bd->bi_dram[0].size = CONFIG_SYS_RAM_DCU1_SIZE;		
		gd->bd->bi_dram[1].start = gd->bd->bi_dram[0].start + gd->bd->bi_dram[0].size;
		gd->bd->bi_dram[1].size = ddr_size - gd->bd->bi_dram[0].size;
	}
	else
	{
		gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
		gd->bd->bi_dram[0].size = ddr_size;
		gd->bd->bi_dram[1].start = 0;
		gd->bd->bi_dram[1].size = 0;
	}
	
	//printf("DRAM[0] base=0x%x, size=0x%x\n", gd->bd->bi_dram[0].start, gd->bd->bi_dram[0].size);
	//printf("DRAM[1] base=0x%x, size=0x%x\n", gd->bd->bi_dram[1].start, gd->bd->bi_dram[1].size);
}

int board_eth_init(bd_t *bis)
{
	return 0;
}

/**
 * @brief misc_init_r - Configure Panda board specific configurations
 * such as power configurations, ethernet initialization as phase2 of
 * boot sequence
 *
 * @return 0
 */
int misc_init_r(void)
{
	return 0;
}

/*
 * get_board_rev() - get board revision
 */
u32 get_board_rev(void)
{
	uint revision = 0;

	revision = (uint)simple_strtoul(CONFIG_VERSION, NULL, 16);

	return revision;
}
