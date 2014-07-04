/*
 * Configuration settings for the Realtek 298X Demo board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_298X_QC_VERIFY_BGA459_H
#define __CONFIG_RTK_298X_QC_VERIFY_BGA459_H


/*
 * Include the common settings of RTD298X platform.
 */
#include <configs/rtd298x_common.h>

/*
 * The followings were RTD298X demo board specific configuration settings.
 */

/* Board config name */
#define CONFIG_BOARD_298X_TV001_BGA459_EMMC

/* Package type */
//#define CONFIG_QFP176
#define CONFIG_BGA459
//#define CONFIG_BOX_BGA459


/* Flash type is SPI or NAND or eMMC*/
//#define CONFIG_SYS_RTK_SPI_FLASH
//#define CONFIG_SYS_RTK_NAND_FLASH
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


#define CONFIG_REALTEK_I2C

#define CONFIG_QC_VERIFY

/* U-boot command */
#define CONFIG_CMD_QC

/* QC code running type */
#define CONFIG_EQC 1
#define CONFIG_FT  0
#define CONFIG_RMA 0  //for RMA IC analysis
#define CONFIG_QC_VERIFY_ATO 0
#define CONFIG_QC_ONCE_ALL  1
#define CONFIG_BGA 1
#define CONFIG_USB_PORT 3   //2 or 3 port

#if CONFIG_BGA
#define CONFIG_BOX 0
#endif

/* Define each ip */
#if CONFIG_EQC
#define CONFIG_QC_SCPU   0
#define CONFIG_QC_GPU   0
#define CONFIG_QC_VE   0
#define CONFIG_QC_AUDIO 0
#define CONFIG_QC_GETN   0
#define CONFIG_QC_HDMI_TX  0
#define CONFIG_QC_HDMI_RX  0
#define CONFIG_QC_CEC   0
#define CONFIG_QC_I_DOMAIN   0
#define CONFIG_QC_IFD   0
#define CONFIG_QC_MD_DOMAIN  0
#define CONFIG_QC_PERIPHERAL 0
#define CONFIG_QC_SPI   0
#define CONFIG_QC_USB   0
#define CONFIG_QC_VIP   0
#define CONFIG_QC_VDC   0
#define CONFIG_QC_VBI   0
#define CONFIG_QC_NAND  0
#define CONFIG_QC_I3DDMA     0
#define CONFIG_QC_TVE_TV     0
#define CONFIG_QC_TVE_BOX    0
#define CONFIG_QC_EMMC  0
#define CONFIG_QC_BISR  0
#define CONFIG_QC_BIST  0
#define CONFIG_QC_SPI_NAND   0
#define CONFIG_QC_MHL   0
#define CONFIG_QC_EPI   0
#define CONFIG_QC_DDR   0
#define CONFIG_QC_DTV_Demod  0
#define CONFIG_QC_STANDBY    0
#define CONFIG_QC_YPPADC   0

#if CONFIG_BGA
#define CONFIG_QC_CARDREADER 0
#endif

#if CONFIG_QC_USB
//for USB
#define CONFIG_BOOT_USB_EHCI 1
#define CONFIG_BOOT_USB_EHCI1 1
#define CONFIG_BOOT_USB_STORAGE 1
#define CONFIG_USB_PATCH 1

//for FS

#define CONFIG_BOOT_FS 1
#define CONFIG_BOOT_FS_FAT 1
#define CONFIG_SUPPORT_VFAT 1

#ifndef CONFIG_DOS_PARTITION
#define CONFIG_DOS_PARTITION 1
#endif
#endif //CONFIG_QC_USB

#else //FT
#define CONFIG_QC_SPI   1
#define CONFIG_QC_EMMC  0
#define CONFIG_QC_GETN   0
#define CONFIG_QC_MD_DOMAIN  1
#endif //CONFIG_EQC

#endif /* __CONFIG_RTK_298X_QC_VERIFY_BGA459_H */
