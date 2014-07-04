/*
 * Configuration settings for the Realtek 298X Demo board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_298X_TV001_512M_X16_NAND_H
#define __CONFIG_RTK_298X_TV001_512M_X16_NAND_H

/*
 * Choose default console port
 */
#define UART_PORT 0

/*
 * Include the common settings of RTD298X platform.
 */
#include <configs/rtd298x_common.h>
#include <configs/rtd298x_common_nand.h>

/*
 * The followings were RTD298X demo board specific configuration settings.
 */

/* Board config name */
#define CONFIG_BOARD_298X_TV001_QFP176_V3_NAND

/* Package type */
#define CONFIG_QFP176
//#define CONFIG_BGA459
//#define CONFIG_BOX_BGA459


/* Flash type is SPI or NAND or eMMC*/
//#define CONFIG_SYS_RTK_SPI_FLASH
#define CONFIG_SYS_RTK_NAND_FLASH
//#define CONFIG_SYS_RTK_EMMC_FLASH

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
/*NAND*/
//nand setting
#define CONFIG_SYS_RTK_NAND_FLASH
#define CONFIG_MTD_NAND_RTK
#define CONFIG_MTD_NAND_IBT
#define CONFIG_SYS_MAX_NAND_DEVICE 1
#define CONFIG_SYS_NAND_BASE 0xb8010000
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_NAND
#define CONFIG_CMD_MTDPARTS	/* mtd parts support		*/

//default mtdids
#define MTDIDS_DEFAULT "nand0=rtk_nand"
//default mtd partition
#define MTDPARTS_DEFAULT		"mtdparts=rtk_nand:473088k,4352k(/),20480k(/usr/local/etc),26368k"

//default factory param
#define CONFIG_FACTORY_SIZE		0x800000	/* For NAND */
#define CONFIG_FACTORY_START	0x1400000	/* For NAND */

/* ENV */
#undef	CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_IS_IN_FACTORY
#define CONFIG_SYS_FACTORY_READ_ONLY

#ifndef CONFIG_PARTITIONS
#define CONFIG_PARTITIONS
#endif
#define CONFIG_DOS_PARTITION

/* USB Setting */
#define CONFIG_CMD_FAT
#define CONFIG_CMD_USB
#define CONFIG_USB_STORAGE
#define CONFIG_USB_EHCI
#define CONFIG_USB_RTK_EHCI
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2

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



///*  AMP (need modified board's PIN  */
//#define CONFIG_REALTEK_AMP_TAS5711
//#define CONFIG_CMD_MISC
////#define CONFIG_SOFT_I2C
//#define CONFIG_SYS_I2C_SPEED    100000

//#define CONFIG_CMD_KEY_BURNING

/* KBoot */
#define CONFIG_CMD_KBOOT
//#define CONFIG_KCPU_LOAD_RESCUE
#define CONFIG_KCPU_LOAD_K_FW

/* Watchdog */
//#define CONFIG_REALTEK_WATCHDOG

#endif /* __CONFIG_RTK_298X_TV001_512M_X16_NAND_H */
