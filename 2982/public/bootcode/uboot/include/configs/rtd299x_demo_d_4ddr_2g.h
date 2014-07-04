/*
 * Configuration settings for the Realtek RTD299X Demo board VerD.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD299X_DEMO_VER_D_H
#define __CONFIG_RTK_RTD299X_DEMO_VER_D_H

/*
 * Include the common settings of RTD299X platform.
 */
#include <configs/rtd299x_common.h>

/*
 * The followings were RTD299X demo board specific configuration settings.
 */

/* Customer ID */
#define CONFIG_CUSTOMER_ID "tv001"

/* Board config name */
#define CONFIG_BOARD_DEMO_VER_C_RTD299X_EMMC /* use the same pin share with verC */

/* Flash writer setting:
 *   The corresponding setting will be located at
 *   uboot/examples/flash_writer_u/$(CONFIG_FLASH_WRITER_SETTING).inc
 */
#define CONFIG_FLASH_WRITER_SETTING		"6227_force_emmc_demo_d_4ddr_2g"

/* Flash type is SPI or NAND or eMMC*/
//#define CONFIG_SYS_RTK_SPI_FLASH
//#define CONFIG_SYS_RTK_NAND_FLASH
#define CONFIG_SYS_RTK_EMMC_FLASH

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

/* Boot Revision */
#define CONFIG_COMPANY_ID 		"0000"
#define CONFIG_BOARD_ID         "0704"
#define CONFIG_VERSION          "0000"


///*  AMP (need modified board's PIN  */
//#define CONFIG_REALTEK_AMP_TAS5711
//#define CONFIG_CMD_MISC
////#define CONFIG_SOFT_I2C
//#define CONFIG_SYS_I2C_SPEED    100000

//#define CONFIG_CMD_KEY_BURNING

#endif /* __CONFIG_RTK_RTD299X_DEMO_VER_D_H */

