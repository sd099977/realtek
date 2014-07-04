/*
 * (C) Copyright 2008-2011 Freescale Semiconductor, Inc.
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

/* #define DEBUG */

#include <common.h>

#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <malloc.h>
#include <mmc.h>
#include <search.h>
#include <errno.h>
#include <fw_info.h>
#include <asm/arch/system.h>

char *env_name_spec = "MMC";

#ifdef ENV_IS_EMBEDDED
env_t *env_ptr = &environment;
#else /* ! ENV_IS_EMBEDDED */
env_t *env_ptr;
#endif /* ENV_IS_EMBEDDED */

DECLARE_GLOBAL_DATA_PTR;

#if !defined(CONFIG_ENV_OFFSET)
#define CONFIG_ENV_OFFSET 0x01800000
#endif

static int __mmc_get_env_addr(struct mmc *mmc, u32 *env_addr)
{
	*env_addr = CONFIG_ENV_OFFSET;
	return 0;
}
int mmc_get_env_addr(struct mmc *mmc, u32 *env_addr)
	__attribute__((weak, alias("__mmc_get_env_addr")));

int env_init(void)
{
	/* use default */
	gd->env_addr	= (ulong)&default_environment[0];
	gd->env_valid	= 1;

	return 0;
}

static int init_mmc_for_env(struct mmc *mmc)
{
	if (!mmc) {
		puts("No MMC card found\n");
		return -1;
	}

	if (mmc_init(mmc)) {
		puts("MMC init failed\n");
		return -1;
	}

	return 0;
}

#ifdef CONFIG_CMD_SAVEENV
static inline int write_env(struct mmc *mmc, unsigned long size,
			    unsigned long offset, const void *buffer)
{
	uint blk_start, blk_cnt, n;

#if 0 // hack by CK
	blk_start	= ALIGN(offset, mmc->write_bl_len) / mmc->write_bl_len;
	blk_cnt		= ALIGN(size, mmc->write_bl_len) / mmc->write_bl_len;

	n = mmc->block_dev.block_write(CONFIG_SYS_MMC_ENV_DEV, blk_start,
					blk_cnt, (u_char *)buffer);
#else
	blk_start	= ALIGN(offset , EMMC_BLOCK_SIZE) / EMMC_BLOCK_SIZE;
	blk_cnt		= ALIGN(size , EMMC_BLOCK_SIZE) / EMMC_BLOCK_SIZE;

	printf("%s: offset=0x%x size=0x%x\n", __FUNCTION__, offset, size);
	printf("%s: blk_start=0x%x blk_cnt=0x%x buffer=0x%x\n", __FUNCTION__, blk_start, blk_cnt, buffer);

	n = rtk_eMMC_write(blk_start, size, buffer);

	printf("%s: n=%d\n", __FUNCTION__, n);
#endif

	return (n == blk_cnt) ? 0 : -1;
}

int saveenv(void)
{
	ssize_t	len;
	char	*res;

#if 0 // hack by CK
	ALLOC_CACHE_ALIGN_BUFFER(env_t, env_new, 1);
	struct mmc *mmc = find_mmc_device(CONFIG_SYS_MMC_ENV_DEV);
	u32	offset;
	if (init_mmc_for_env(mmc) || mmc_get_env_addr(mmc, &offset))
		return 1;
#else
	env_t *env_new = NULL;
	struct mmc *mmc = NULL;	/* without use the registed mmc*/
	u32	offset;

	env_new = (env_t *)rtk_mem_info->temp_buffer_for_flash_data_addr;
	mmc_get_env_addr(mmc, &offset);
#endif

	res = (char *)&env_new->data;
	len = hexport_r(&env_htab, '\0', &res, ENV_SIZE, 0, NULL);
	if (len < 0) {
		error("Cannot export environment: errno = %d\n", errno);
		return 1;
	}

	env_new->crc = crc32(0, &env_new->data[0], ENV_SIZE);

#if 0 // hack by CK
	printf("Writing to MMC(%d)... ", CONFIG_SYS_MMC_ENV_DEV);
#else
	printf("Writing to MMC... \n");
#endif

	if (write_env(mmc, CONFIG_ENV_SIZE, offset, (u_char *)env_new)) {
		puts("failed\n");
		return 1;
	}

	puts("done\n");
	return 0;
}
#endif /* CONFIG_CMD_SAVEENV */

static inline int read_env(struct mmc *mmc, unsigned long size,
			   unsigned long offset, const void *buffer)
{
	uint blk_start, blk_cnt, n;

#if 0 // hack by CK
	blk_start	= ALIGN(offset, mmc->read_bl_len) / mmc->read_bl_len;
	blk_cnt		= ALIGN(size, mmc->read_bl_len) / mmc->read_bl_len;

	n = mmc->block_dev.block_read(CONFIG_SYS_MMC_ENV_DEV, blk_start,
					blk_cnt, (uchar *)buffer);
#else
	blk_start	= ALIGN(offset , EMMC_BLOCK_SIZE) / EMMC_BLOCK_SIZE;
	blk_cnt		= ALIGN(size , EMMC_BLOCK_SIZE) / EMMC_BLOCK_SIZE;

	n = rtk_eMMC_read(blk_start, size, buffer);

	if (n != blk_cnt) {
		printf("[ERR] %s: offset=0x%x size=0x%x\n", __FUNCTION__, offset, size);
		printf("[ERR] %s: blk_start=0x%x blk_cnt=0x%x buffer=0x%x\n", __FUNCTION__, blk_start, blk_cnt, buffer);
		printf("[ERR] %s: n=%d\n", __FUNCTION__, n);
	}
#endif

	return (n == blk_cnt) ? 0 : -1;
}

void env_relocate_spec(void)
{
#if !defined(ENV_IS_EMBEDDED)
#if 0 // hack by CK
	ALLOC_CACHE_ALIGN_BUFFER(char, buf, CONFIG_ENV_SIZE);
	struct mmc *mmc = find_mmc_device(CONFIG_SYS_MMC_ENV_DEV);
	u32 offset;

	if (init_mmc_for_env(mmc) || mmc_get_env_addr(mmc, &offset))
		return set_default_env(NULL);
#else
	char *buf = NULL;
	struct mmc *mmc = NULL;	/* without use the registed mmc*/
	u32 offset;

	buf = (char *)rtk_mem_info->temp_buffer_for_flash_data_addr;
	mmc_get_env_addr(mmc, &offset);

//	printf("Reading env from MMC... \n");
#endif

	if (read_env(mmc, CONFIG_ENV_SIZE, offset, buf))
		return set_default_env(NULL);

	env_import(buf, 1);

#endif
}
