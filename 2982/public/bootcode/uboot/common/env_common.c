/*
 * (C) Copyright 2000-2010
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * (C) Copyright 2001 Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Andreas Heppel <aheppel@sysgo.de>
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

#include <common.h>
#include <command.h>
#include <environment.h>
#include <linux/stddef.h>
#include <search.h>
#include <errno.h>
#include <malloc.h>
#include <asm/arch/system.h>
#include <asm/arch/extern_param.h>
#include <asm/arch/fw_info.h>
#include <asm/arch/factorylib.h>
#include <asm/arch/factorylib_ro.h>
#include <asm/arch/bootparam.h>
#if defined(CONFIG_REALTEK_EERPOM_TV010_A)
#include "../drivers/eeprom/EEP_TV010_A/eeprom.h"
#endif

#ifndef CONFIG_SYS_RTK_NAND_FLASH
#include <asm/arch/sys_param_emmc.h>
#else
#include <linux/mtd/nand.h>		//surport nand flash driver
#include <nand.h>
#include <asm/arch/sys_param_nand.h>
#endif

DECLARE_GLOBAL_DATA_PTR;

#define PANEL_BIN_FILENAME_IN_FACTORY	FACTORY_HEADER_FILE_NAME"bin_panel/panel.bin"

extern uint boot_part;
extern int boot_power_on_mode;

/************************************************************************
 * Default settings to be used when no valid environment is found
 */
#define XMK_STR(x)	#x
#define MK_STR(x)	XMK_STR(x)

const uchar default_environment[] = {
#if (1)	// Chuck for DS-5
#ifdef	CONFIG_BOOTARGS
	"bootargs="	CONFIG_BOOTARGS			"\0"
#endif
#ifdef	CONFIG_BOOTCOMMAND
	"bootcmd="	CONFIG_BOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_RAMBOOTCOMMAND
	"ramboot="	CONFIG_RAMBOOTCOMMAND		"\0"
#endif
#ifdef	CONFIG_NFSBOOTCOMMAND
	"nfsboot="	CONFIG_NFSBOOTCOMMAND		"\0"
#endif
#if defined(CONFIG_BOOTDELAY) && (CONFIG_BOOTDELAY >= 0)
	"bootdelay="	MK_STR(CONFIG_BOOTDELAY)	"\0"
#endif
#if defined(CONFIG_BAUDRATE) && (CONFIG_BAUDRATE >= 0)
	"baudrate="	MK_STR(CONFIG_BAUDRATE)		"\0"
#endif
#ifdef	CONFIG_LOADS_ECHO
	"loads_echo="	MK_STR(CONFIG_LOADS_ECHO)	"\0"
#endif
#ifdef	CONFIG_ETHADDR
	"ethaddr="	MK_STR(CONFIG_ETHADDR)		"\0"
#endif
#ifdef	CONFIG_ETH1ADDR
	"eth1addr="	MK_STR(CONFIG_ETH1ADDR)		"\0"
#endif
#ifdef	CONFIG_ETH2ADDR
	"eth2addr="	MK_STR(CONFIG_ETH2ADDR)		"\0"
#endif
#ifdef	CONFIG_ETH3ADDR
	"eth3addr="	MK_STR(CONFIG_ETH3ADDR)		"\0"
#endif
#ifdef	CONFIG_ETH4ADDR
	"eth4addr="	MK_STR(CONFIG_ETH4ADDR)		"\0"
#endif
#ifdef	CONFIG_ETH5ADDR
	"eth5addr="	MK_STR(CONFIG_ETH5ADDR)		"\0"
#endif
#ifdef	CONFIG_IPADDR
	"ipaddr="	MK_STR(CONFIG_IPADDR)		"\0"
#endif
#ifdef	CONFIG_SERVERIP
	"serverip="	MK_STR(CONFIG_SERVERIP)		"\0"
#endif
#ifdef	CONFIG_SYS_AUTOLOAD
	"autoload="	CONFIG_SYS_AUTOLOAD		"\0"
#endif
#ifdef	CONFIG_PREBOOT
	"preboot="	CONFIG_PREBOOT			"\0"
#endif
#ifdef	CONFIG_ROOTPATH
	"rootpath="	CONFIG_ROOTPATH			"\0"
#endif
#ifdef	CONFIG_GATEWAYIP
	"gatewayip="	MK_STR(CONFIG_GATEWAYIP)	"\0"
#endif
#ifdef	CONFIG_NETMASK
	"netmask="	MK_STR(CONFIG_NETMASK)		"\0"
#endif
#ifdef	CONFIG_HOSTNAME
	"hostname="	MK_STR(CONFIG_HOSTNAME)		"\0"
#endif
#ifdef	CONFIG_BOOTFILE
	"bootfile="	CONFIG_BOOTFILE			"\0"
#endif
#ifdef	CONFIG_LOADADDR
	"loadaddr="	MK_STR(CONFIG_LOADADDR)		"\0"
#endif
#ifdef	CONFIG_CLOCKS_IN_MHZ
	"clocks_in_mhz=1\0"
#endif
#if defined(CONFIG_PCI_BOOTDELAY) && (CONFIG_PCI_BOOTDELAY > 0)
	"pcidelay="	MK_STR(CONFIG_PCI_BOOTDELAY)	"\0"
#endif
#ifdef	CONFIG_ENV_VARS_UBOOT_CONFIG
	"arch="		CONFIG_SYS_ARCH			"\0"
	"cpu="		CONFIG_SYS_CPU			"\0"
	"board="	CONFIG_SYS_BOARD		"\0"
#ifdef CONFIG_SYS_VENDOR
	"vendor="	CONFIG_SYS_VENDOR		"\0"
#endif
#ifdef CONFIG_SYS_SOC
	"soc="		CONFIG_SYS_SOC			"\0"
#endif
#endif
#ifdef CONFIG_SILENT_KERNEL
	"silent=1\0"
#endif
#ifdef CONFIG_CHECK_IMG_VERSION
        "fwver=0.0.0\0"
#endif
#ifdef	CONFIG_EXTRA_ENV_SETTINGS
	CONFIG_EXTRA_ENV_SETTINGS
#endif
#endif	//Chuck for DS-5
	"\0"
};

struct hsearch_data env_htab;

static uchar __env_get_char_spec(int index)
{
	return *((uchar *)(gd->env_addr + index));
}
uchar env_get_char_spec(int)
	__attribute__((weak, alias("__env_get_char_spec")));

static uchar env_get_char_init(int index)
{
	/* if crc was bad, use the default environment */
	if (gd->env_valid)
		return env_get_char_spec(index);
	else
		return default_environment[index];
}

uchar env_get_char_memory(int index)
{
	return *env_get_addr(index);
}

uchar env_get_char(int index)
{
	/* if relocated to RAM */
	if (gd->flags & GD_FLG_RELOC)
		return env_get_char_memory(index);
	else
		return env_get_char_init(index);
}

const uchar *env_get_addr(int index)
{
	if (gd->env_valid)
		return (uchar *)(gd->env_addr + index);
	else
		return &default_environment[index];
}

void set_default_env(const char *s)
{
	if (sizeof(default_environment) > ENV_SIZE) {
		puts("*** Error - default environment variables is too large\n\n");
		return;
	}

	if (s) {
		if (*s == '!') {
			printf("*** Warning - %s, "
				"using default environment variables\n\n",
				s + 1);
		} else {
			puts(s);
		}
	} else {
		puts("[ENV] Using default environment variables\n\n");
	}

	if (himport_r(&env_htab, (char *)default_environment,
			sizeof(default_environment), '\0', 0) == 0)
		error("Environment import failed: errno = %d\n", errno);

	gd->flags |= GD_FLG_ENV_READY;
}

/*
 * Check if CRC is valid and (if yes) import the environment.
 * Note that "buf" may or may not be aligned.
 */
int env_import(const char *buf, int check)
{
	env_t *ep = (env_t *)buf;

	if (check) {
		uint32_t crc;

		memcpy(&crc, &ep->crc, sizeof(crc));

		if (crc32(0, ep->data, ENV_SIZE) != crc) {
			//set_default_env("!bad CRC");
			set_default_env(NULL); // ck modify that prevent serious error messages
			return 0;
		}
	}

	if (himport_r(&env_htab, (char *)ep->data, ENV_SIZE, '\0', 0)) {
		gd->flags |= GD_FLG_ENV_READY;
		return 1;
	}

	error("Cannot import environment: errno = %d\n", errno);

	set_default_env("!import failed");

	return 0;
}

/* Porting from Darwin Env*/

#if 0 /* Boot Revision Define Comments that sync from kernel */
/* The format of "bootrev" is like "0001.0203.4567". The second two bytes of it stands for board id, and the upper half byte of board id stands for CPU id */
typedef enum {
	realtek_299x_qa_board				= 0x000700,
	realtek_299x_demo_ab_board			= 0x000701,
	realtek_299x_demo_c_4ddr_1g_board	= 0x000702,
	realtek_299x_demo_c_4ddr_2g_board	= 0x000703,
	realtek_299x_demo_d_4ddr_2g_board	= 0x000704,
	C10_2995_v1_board					= 0x100700,
	C05_2993_l4300_board				= 0x050700,
} _board_id_t;

/* The format of "bootrev" is like "0001.0203.4567". The first two byte of it stands for company id */
typedef enum {
	company_realtek	= 0x00,
	company_alpha	= 0x01,
	company_C02		= 0x02,
	company_C03		= 0x03,
	company_C04		= 0x04,
	company_C05		= 0x05,
	company_C06		= 0x06,
	company_C07		= 0x07,
	company_C08		= 0x08,
	company_C09		= 0x09,
	/* skip 0x0a ~ 0x0f */
	company_C10		= 0x10,
	company_C11 	= 0x11,
	company_C12 	= 0x12,
	company_C13 	= 0x13,
	company_C14 	= 0x14,
	company_C15 	= 0x15,
	company_C16 	= 0x16,
	company_C17 	= 0x17,
	company_C18 	= 0x18,
	company_C19 	= 0x19,
	/* skip 0x1a ~ 0x1f */
	company_C20 	= 0x20,
} _company_id_t;

/* Defines of CPU ID */
typedef enum {
	realtek_299x_cpu	= 0x07,
} _cpu_id_t;
#endif

#define BOOT_REV_STRING		CONFIG_COMPANY_ID"."CONFIG_BOARD_ID"."CONFIG_VERSION

static char sys_chiprev_str[64];

#define BOOT_PARAMS_SIZE		1536	// sync with linux/arch/arm/kernel/atags.c
#define ENV_VAR_ADDRESS			(LINUX_KERNEL_ADDR + 0x100 + BOOT_PARAMS_SIZE)
#define ENV_VAR_INFO_ADDRESS	(ENV_VAR_ADDRESS + sizeof(t_env_var) * (SYS_USER_ENVIRONMENT_MAX_INDEX + 2))

//static t_env_var       	env_vars[SYS_USER_ENVIRONMENT_MAX_INDEX + 2];
//static t_env_var_info  	env_var_info[SYS_USER_ENVIRONMENT_MAX_INDEX + 1];
static t_env_var       	*env_vars = (t_env_var *)ENV_VAR_ADDRESS;
static t_env_var_info  	*env_var_info = (t_env_var_info *)ENV_VAR_INFO_ADDRESS;

unsigned char env_setup_env_panel(uchar *panel_filename);
extern unsigned int env_setup_env_pcb(void);

/*
 * Get export env pointer
 */
t_env_var *env_get_export_all(void)
{
	return env_vars;
}

/*
 * export env
 */
int env_export(void)
{
	char *buf = NULL;
	size_t len = 0;
	int buf_i = 0, data_j =0;
	int index = 0;
	unsigned char bParseName = 1; /* when parsing name, we should find the first '=' */

	env_vars = (t_env_var *)ENV_VAR_ADDRESS;
	env_var_info = (t_env_var_info *)ENV_VAR_INFO_ADDRESS;

	memset(env_vars, 0, sizeof(t_env_var) * (SYS_USER_ENVIRONMENT_MAX_INDEX + 2));
	memset(env_var_info, 0, sizeof(t_env_var_info) * (SYS_USER_ENVIRONMENT_MAX_INDEX + 1));

	len = hexport_r(&env_htab, '\0', &buf, 0, 0, NULL);
	if (len < 0) {
		error("%s: Cannot export environment: errno = %d\n", __func__, errno);
		return -1;
	}

	/* Parse export string */
	/* Ex. name1=value1\0name2=value2\0name3=value3\0name4= ... \0\0 */
	for (buf_i = 0;buf_i < len && buf[buf_i] != '\0';)
	{
		data_j = 0;
		bParseName = 1;

		/* Match an env item */
		while (buf[buf_i] != '\0') {

			if (bParseName && buf[buf_i] == '=') {
				/* Separate name and value */
				env_var_info[index].data[data_j] = '\0';
				env_vars[index].name	= &(env_var_info[index].data[0]);
				env_vars[index].val	= &(env_var_info[index].data[data_j + 1]); /* skip '=' */

				bParseName = 0; /* change to 0 that means start to parse value */
			}
			else {
				/* Save data */
				env_var_info[index].data[data_j] = buf[buf_i];
			}

			data_j++;
			buf_i++;
		}

		/* data terminate */
		env_var_info[index].data[data_j] = '\0';

		index++;
		buf_i++;
	}

	/* env terminate */
	env_vars[index].name = NULL;
	env_vars[index].val = NULL;

	free(buf);

#if 0 // dump result
	index = 0;

	printf("dump env_export() result\n");

	while ((env_vars[index].name != NULL) && (env_vars[index].val != NULL))
	{
		printf("[%d] %s %s\n", index, env_vars[index].name, env_vars[index].val);

		index++;
	}
#endif

	return len;
}

void env_relocate(void)
{
#ifdef CONFIG_SYS_RTK_NAND_FLASH
	int dev = nand_curr_device;
	nand_info_t *nand =&nand_info[dev]; 	//nand_info[0];
	//struct nand_chip *this = (struct nand_chip *) nand->priv;
#endif
	char		*raw = NULL;
	int			i = 0;
	char		*msg;
#if defined(CONFIG_REALTEK_EERPOM_TV010_A)
#elif defined(CONFIG_SYS_FACTORY_READ_ONLY)
	char		*mac_ptr;
	int			mac_len;
	int			rc = 0;
#endif

	msg = (char *)malloc(128);

#if defined(CONFIG_NEEDS_MANUAL_RELOC)
	env_reloc();
#endif
	if (gd->env_valid == 0) {
#if defined(CONFIG_ENV_IS_NOWHERE)	/* Environment not changable */
		set_default_env(NULL);
#else
		bootstage_error(BOOTSTAGE_ID_NET_CHECKSUM);
		set_default_env("!bad CRC");
#endif
	} else {
		env_relocate_spec();
	}


/*
 *********************************************************
 * Realtek Patch:
 *    Assign platform related environment variables.
 *********************************************************
 */

	/* Bootcode revision */
	memset(sys_chiprev_str, 0x0, 64);
	if (strlen(BOOT_REV_STRING) < 64)
		strcpy(sys_chiprev_str, BOOT_REV_STRING);
	else
		strncpy(sys_chiprev_str, BOOT_REV_STRING, 63);

	for (i = 0; i < 63; i++)
	{
		if( (sys_chiprev_str[i] == 0x58) || (sys_chiprev_str[i] == 0x78)) //rev_str[i] == 'X' || 'x'
		{
			/* FIXME */
			sys_chiprev_str[i] = 0x32;
			break;
		}
	}

	if (setenv("bootrev", sys_chiprev_str))
		;

#if defined(CONFIG_REALTEK_EERPOM_TV010_A)
	if(boot_power_on_mode != POWER_OFF)
	{
		Eeprom_SetMacAddressToKernel_Read();
		Eeprom_SetMacAddressToKernel_Apply();
	}
#elif defined(CONFIG_SYS_FACTORY_READ_ONLY)
	if(boot_power_on_mode != POWER_OFF) {
		/* Mac Address from factory read-only */
		rc = factory_ro_read(FACTORY_RO_MAC_BIN, &mac_ptr, &mac_len);
		if (!rc) {
			memset(msg, 0, 20); // real length is 17
#if 0 //old mac format
			sprintf(msg, "%02x:%02x:%02x:%02x:%02x:%02x",
				mac_ptr[0],
				mac_ptr[1],
				mac_ptr[2],
				mac_ptr[3],
				mac_ptr[4],
				mac_ptr[5]
			);
#else
			mac_ptr[17] = '\0';
			strcpy(msg, mac_ptr);
#endif
			printf("Mac Address use %s in factory_ro\n", msg);
			if (setenv("ethaddr", msg))
				;
		}
		else {
			printf("Mac Address use %s\n", getenv("ethaddr"));
		}
	}
#endif

	/* Prompt */
	if (setenv("prompt", NULL)) // clear prompt
		;

	if (strlen(bootparam.install_file_name) > 0)
		sprintf( msg, "param_addr=%x tv_system=%s imgfile_pattern=%s",
			((uint)(ext_para_ptr->env_param_saddr)) & 0x1fffffff,
			SYS_PARAM_TV_SYSTEM,
			bootparam.install_file_name
		);
	else
		sprintf( msg, "param_addr=%x tv_system=%s",
         ((uint)(ext_para_ptr->env_param_saddr)) & 0x1fffffff,
         SYS_PARAM_TV_SYSTEM
      );

	/* system_parameters_1 pass parameter start address to kernel */
	raw = msg; /* Always overwrite parameters with default settings. */

	if (setenv("system_parameters_1", raw))
		;

	/* This is for telling the installer what target flash type and flash info */
	if (1) {//(boot_flash_type == BOOT_EMMC) {
		sprintf( msg, "boot_flash=%s factory_start=%x factory_size=%x",
			SYS_PARAM_BOOT_FLASH,
			SYS_PARAM_FACTORY_START,
			SYS_PARAM_FACTORY_SIZE
		);

		if (setenv("system_parameters_2", raw))
			;

#ifndef CONFIG_SYS_RTK_NAND_FLASH
				sprintf(raw, "bootcode_start=%x bootcode_size=%x rescue_start=%x rescue_size=%x",
					SYS_PARAM_BOOTCODE_START,
					SYS_PARAM_BOOTCODE_SIZE,
					(uint)(ext_para_ptr->rescue_img_addr) * EMMC_BLOCK_SIZE,
					ext_para_ptr->rescue_img_size
				);
#else
#ifdef CONFIG_SAFE_UPGRADE
				sprintf(raw, "bootcode_start=%x bootcode_size=%x ss_start=%x ss_size=%x reserved_size=%x ssu=1",
					SYS_PARAM_BOOTCODE_START,
					SYS_PARAM_BOOTCODE_SIZE,
					SYS_PARAM_SECURE_STORE_START,
					SYS_PARAM_SECURE_STORE_SIZE,
					SYS_PARAM_FACTORY_RESERVED
				);

#else
				sprintf(raw, "bootcode_start=%x bootcode_size=%x ss_start=%x ss_size=%x reserved_size=%x",
					SYS_PARAM_BOOTCODE_START,
					SYS_PARAM_BOOTCODE_SIZE,
					SYS_PARAM_SECURE_STORE_START,
					SYS_PARAM_SECURE_STORE_SIZE,
					SYS_PARAM_FACTORY_RESERVED
				);
#endif
#endif

		if (setenv("system_parameters_3", raw))
			;
	}

	/* system_parameters_4 pass bootpart parameter to kernel */
	sprintf( msg, "boot_part=%d factory_ro_start=%x factory_ro_size=%x",
			boot_part,
			SYS_PARAM_FACTORY_RO_START,
			SYS_PARAM_FACTORY_RO_SIZE
	);

	if (setenv("system_parameters_4", raw))
		;

#ifdef CONFIG_SYS_PANEL_PARAMETER
	/* panel parameters setting */
  #ifdef PANEL_CONFIG_FROM_FACTORY_PANEL_BIN
	env_setup_env_panel((uchar *)PANEL_BIN_FILENAME_IN_FACTORY); // assign panel.bin value
  #else
	env_setup_env_panel((uchar *)NULL); // assign default value
  #endif
#endif

#ifdef CONFIG_SYS_PCB_MANAGER
	/* PCB Manager */
	env_setup_env_pcb();
#endif

	free(msg);
}

#ifdef CONFIG_AUTO_COMPLETE
int env_complete(char *var, int maxv, char *cmdv[], int bufsz, char *buf)
{
	ENTRY *match;
	int found, idx;

	idx = 0;
	found = 0;
	cmdv[0] = NULL;

	while ((idx = hmatch_r(var, idx, &match, &env_htab))) {
		int vallen = strlen(match->key) + 1;

		if (found >= maxv - 2 || bufsz < vallen)
			break;

		cmdv[found++] = buf;
		memcpy(buf, match->key, vallen);
		buf += vallen;
		bufsz -= vallen;
	}

	qsort(cmdv, found, sizeof(cmdv[0]), strcmp_compar);

	if (idx)
		cmdv[found++] = "...";

	cmdv[found] = NULL;
	return found;
}
#endif
