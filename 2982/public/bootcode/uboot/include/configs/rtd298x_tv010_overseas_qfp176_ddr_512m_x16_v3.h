/*
 * Configuration settings for the Realtek 298X Demo board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_298X_TV001_512M_X16_H
#define __CONFIG_RTK_298X_TV001_512M_X16_H

/*
 * Choose default console port
 */
#define UART_PORT 0

/*
 * Include the common settings of RTD298X platform.
 */
#include <configs/rtd298x_common.h>

/*
 * The followings were RTD298X demo board specific configuration settings.
 */

/* Board config name */
#define CONFIG_BOARD_298X_TV010_OVERSEAS_QFP176_V3_EMMC

/* Package type */
#define CONFIG_QFP176
//#define CONFIG_BGA459
//#define CONFIG_BOX_BGA459


/* Flash type is SPI or NAND or eMMC*/
//#define CONFIG_SYS_RTK_SPI_FLASH
//#define CONFIG_SYS_RTK_NAND_FLASH
#define CONFIG_SYS_RTK_EMMC_FLASH

/* MMC */
//#define CONFIG_MMC
//#ifndef CONFIG_PARTITIONS
//#define CONFIG_PARTITIONS
//#endif
//#define CONFIG_DOS_PARTITION
//#define CONFIG_GENERIC_MMC
//#define CONFIG_RTK_MMC
//#define CONFIG_CMD_MMC

#if defined(CONFIG_SYS_RTK_EMMC_FLASH)

/* MMC */
#define CONFIG_MMC
#ifndef CONFIG_PARTITIONS
#define CONFIG_PARTITIONS
#endif
#define CONFIG_DOS_PARTITION
#define CONFIG_GENERIC_MMC
#define CONFIG_RTK_MMC
#define CONFIG_CMD_MMC

/* USB Setting */
#define CONFIG_CMD_FAT
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI
#define CONFIG_USB_RTK_EHCI
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2

/* ENV */
#undef	CONFIG_ENV_IS_NOWHERE
#ifdef CONFIG_SYS_FACTORY
#define CONFIG_ENV_IS_IN_FACTORY
#else
#define CONFIG_ENV_IS_IN_MMC	/* if enable CONFIG_SYS_FACTORY, env will be saved in factory data */
#endif

#define CONFIG_SYS_FACTORY_READ_ONLY

#elif defined(CONFIG_SYS_RTK_NAND_FLASH)
//#define CONFIG_FACTORY_SIZE		0x400000	/* For NAND */

#else
//#define CONFIG_FACTORY_SIZE		0x20000		/* For SPI */
#endif

/* CPU count setting, max count 4 (0 for auto detect) */
#undef CONFIG_SYS_NR_CPUS
#define CONFIG_SYS_NR_CPUS	0

/* Boot Revision */
#define CONFIG_COMPANY_ID 		Param_companyID
#define CONFIG_BOARD_ID         Param_boardID
#define CONFIG_VERSION          Param_version

#define ENABLE_BOOTUP_POLICY

///*  AMP (need modified board's PIN  */
//#define CONFIG_REALTEK_AMP_TAS5711
//#define CONFIG_CMD_MISC
////#define CONFIG_SOFT_I2C
//#define CONFIG_SYS_I2C_SPEED    100000

//#define CONFIG_CMD_KEY_BURNING

/* Watchdog */
#define CONFIG_REALTEK_WATCHDOG

/* Bootcode Feature: Detect install.img from USB when AC on and have Auto Script */
#undef CONFIG_USB_UPDATE_SCRIPT
#define CONFIG_USB_UPDATE_SCRIPT

/* Bootcode Feature: Detect install.img from USB when AC on */
#undef CONFIG_USB_UPDATE_WHEN_AC_ON
#define CONFIG_USB_UPDATE_WHEN_AC_ON

/* Bootcode Feature: Detect dvrboot.exe.bin from USB when AC on */
#undef CONFIG_USB_UPDATE_UBOOT_WHEN_AC_ON
#define CONFIG_USB_UPDATE_UBOOT_WHEN_AC_ON

/* Bootcode Feature: Read rescue linux from install.img or flash */
#undef CONFIG_USB_UPDATE_READ_RESCUE_FROM_FLASH
//#define CONFIG_USB_UPDATE_READ_RESCUE_FROM_FLASH

#endif /* __CONFIG_RTK_298X_TV001_512M_X16_H */
