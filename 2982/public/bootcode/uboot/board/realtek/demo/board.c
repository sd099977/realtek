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

const struct rtd299x_sysinfo sysinfo = {
    "Board: Realtek Demo Board\n"
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
	gd->bd->bi_arch_number = MACH_TYPE_RTK_RTD299X;
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
	#define CONFIG_SYS_SDRAM_DCU2_BASE_FIX 0x40000000
	unsigned int ddr_size = 0;

#ifdef IS_298X_FPGA
	// Bank 1
	gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
	gd->bd->bi_dram[0].size = CONFIG_SYS_RAM_DCU1_SIZE;

#if (CONFIG_NR_DRAM_BANKS > 1)
	// Bank 2
	gd->bd->bi_dram[1].start = CONFIG_SYS_SDRAM_DCU2_BASE;
	gd->bd->bi_dram[1].size = CONFIG_SYS_RAM_DCU2_SIZE;
#endif

#else

	if (GET_IC_VERSION() == VERSION_A)
	{
		// Bank 1
		gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
		gd->bd->bi_dram[0].size = CONFIG_SYS_RAM_DCU1_SIZE;

#if (CONFIG_NR_DRAM_BANKS > 1)
		// Bank 2
		gd->bd->bi_dram[1].start = CONFIG_SYS_SDRAM_DCU2_BASE;
		gd->bd->bi_dram[1].size = CONFIG_SYS_RAM_DCU2_SIZE;
#endif

#if (CONFIG_NR_DRAM_BANKS > 2)
		// Bank 3
	#if defined(CONFIG_SYS_SDRAM_DCU_OPT_BASE) && defined(CONFIG_SYS_RAM_DCU_OPT_SIZE)
			gd->bd->bi_dram[2].start = CONFIG_SYS_SDRAM_DCU_OPT_BASE;
			gd->bd->bi_dram[2].size = CONFIG_SYS_RAM_DCU_OPT_SIZE;
	#endif
#endif

#if (CONFIG_NR_DRAM_BANKS > 3)
		// Bank 4
	#if defined(CONFIG_SYS_SDRAM_DCU_OPT_2_BASE) && defined(CONFIG_SYS_RAM_DCU_OPT_2_SIZE)
			gd->bd->bi_dram[3].start = CONFIG_SYS_SDRAM_DCU_OPT_2_BASE;
			gd->bd->bi_dram[3].size = CONFIG_SYS_RAM_DCU_OPT_2_SIZE;
	#endif
#endif
	}
	else
	{
		// Bank 1
		ddr_size = get_ddr_size(0);
		if (ddr_size >= 0x20000000) // 512M
			ddr_size = 0x20000000;

		gd->bd->bi_dram[0].start = CONFIG_SYS_SDRAM_BASE;
		gd->bd->bi_dram[0].size = ddr_size;

#if (CONFIG_NR_DRAM_BANKS > 1)
		// Bank 2
		ddr_size = get_ddr_size(1);
		gd->bd->bi_dram[1].start = CONFIG_SYS_SDRAM_DCU2_BASE_FIX;
		gd->bd->bi_dram[1].size = ddr_size;
#endif
	}
#endif
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
