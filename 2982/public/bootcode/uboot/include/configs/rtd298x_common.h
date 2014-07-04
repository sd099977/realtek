/*
 * Realtek RTD298X common configuration settings
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_RTD298X_COMMON_H
#define __CONFIG_RTK_RTD298X_COMMON_H

/* PRJ*.inc config */
#include "../../src/include/project_config.h"

/*NOCS BSD support */
//#define CONFIG_NOCS_BSD	1
#ifdef CONFIG_NOCS_BSD
//#define CONFIG_MAKE_BSD_RPC
#endif

/*
 * Realtek feature support
 */
#define CONFIG_BSP_REALTEK	1

/*
 * Realtek IC type
 */
#define CONFIG_RTD298X		1

/*
 * High Level Configuration Options
 */
#define CONFIG_ARMV7		1	/* This is an ARM V7 CPU core */
#define CONFIG_ARM_CA7_MPCORE	1	/* This is an ARM Cortex-A7 MPCore */

/* Get CPU defs */
//#include <asm/arch/cpu.h>
//#include <asm/arch/omap.h>

/* Display CPU and Board Info */
#define CONFIG_DISPLAY_CPUINFO		1
#define CONFIG_DISPLAY_BOARDINFO	1

#define CONFIG_SKIP_LOWLEVEL_INIT	1

#undef CONFIG_USE_IRQ				/* no support for IRQs */

#define CONFIG_CMDLINE_TAG		1	/* enable passing of ATAGs */
#define CONFIG_SETUP_MEMORY_TAGS	1
//#define CONFIG_INITRD_TAG		1
#define CONFIG_REVISION_TAG		1

/*
 * Size of malloc() pool
 * Total Size Environment - 128k
 * Malloc - add 256k
 */
#define CONFIG_ENV_SIZE			(128 << 10)
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (256 << 10))
#define CONFIG_SYS_NON_CACHE_LEN	(1 << 20)
/* Vector Base */
#define CONFIG_SYS_CA9_VECTOR_BASE	SRAM_ROM_VECT_BASE

/*
 * Hardware drivers
 */
#define CONFIG_USE_RTK_RTC			1
//#define CONFIG_REALTEK_WATCHDOG	1

/*
 *Nand support
 */
//#define CONFIG_CMD_NAND
//#define CONFIG_SYS_MAX_NAND_DEVICE 1
//#define CONFIG_SYS_NAND_BASE	0x00000000

/*
 * serial port - NS16550 compatible
 */
#define UART0_BASE				0x18062300
#define UART1_BASE				0x1801bc00

#if (UART_PORT == 0)
#define V_NS16550_CLK			27000000
#define CONFIG_SYS_NS16550_COM1	UART0_BASE
#elif (UART_PORT == 1)
#define V_NS16550_CLK			432000000
#define CONFIG_SYS_NS16550_COM1	UART1_BASE
#else
#error "UART_PORT defined error."
#endif

#ifdef IS_298X_FPGA
#ifdef V_NS16550_CLK
#undef V_NS16550_CLK
#endif
#define V_NS16550_CLK			25000000	//FPGA

#ifdef IS_ALSO_MAC3_FPGA
#ifdef UART1_BASE
#undef UART1_BASE
#endif
#define UART1_BASE				0x1801b100	//mac3 FPGA
#endif

#ifdef CONFIG_SYS_NS16550_COM1
#undef CONFIG_SYS_NS16550_COM1
#endif
#define CONFIG_SYS_NS16550_COM1	UART1_BASE	//FPGA
#endif /* End of #ifdef IS_298X_FPGA */


#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_REG_SIZE	(-4)
#define CONFIG_SYS_NS16550_CLK		V_NS16550_CLK

#define CONFIG_BAUDRATE			115200
#define CONFIG_SYS_BAUDRATE_TABLE	{4800, 9600, 19200, 38400, 57600, 115200}

#define CONFIG_SYS_CONSOLE_IS_IN_ENV	1
#define CONFIG_CONS_INDEX		1

/*
 * Environment setup
 */

#define CONFIG_BOOTDELAY	0

#define CONFIG_ENV_OVERWRITE

#if (UART_PORT == 0)
#define CONFIG_BOOTARGS \
	"androidboot.console=ttyS0 console=ttyS0,115200"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x03000000\0" \
	"console=ttyS0,115200\0"
#elif (UART_PORT == 1)
#define CONFIG_BOOTARGS \
	"androidboot.console=ttyS1 console=ttyS1,115200"

#define CONFIG_EXTRA_ENV_SETTINGS \
	"loadaddr=0x03000000\0" \
	"console=ttyS1,115200\0"
#else
#error "UART_PORT defined error."
#endif

#define CONFIG_BOOTCOMMAND \
	"bootr"



/* Flash */
#define CONFIG_SYS_NO_FLASH	1

/* commands to include */
#include <config_cmd_default.h>


//#define CONFIG_CMDLINE_EDITING
//#define CONFIG_AUTO_COMPLETE

/*
 * Miscellaneous configurable options
 */

/* CPU count setting, max count 4 (0 for auto detect) */
#define CONFIG_SYS_NR_CPUS	0

#define CONFIG_SYS_LONGHELP	/* undef to save memory */
#define CONFIG_SYS_HUSH_PARSER	/* use "hush" command parser */
#define CONFIG_SYS_CBSIZE		640
/* Print Buffer Size */
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16
/* Boot Argument Buffer Size */
#define CONFIG_SYS_BARGSIZE		(CONFIG_SYS_CBSIZE)

/*
 * memtest setup
 */
#define CONFIG_SYS_MEMTEST_START	0x00000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + (32 << 20))

/* Default load address */
#define CONFIG_SYS_LOAD_ADDR		0x03000000

/* Use General purpose timer 2 */
#define CONFIG_SYS_TIMER		2
#define CONFIG_SYS_HZ			1000

/*
 * Stack sizes
 *
 * The stack sizes are set up in start.S using the settings below
 */
//stack size is setup in linker script 1MB
#ifdef CONFIG_USE_IRQ
#define CONFIG_STACKSIZE_IRQ	(4 << 10)	/* IRQ stack */
#define CONFIG_STACKSIZE_FIQ	(4 << 10)	/* FIQ stack */
#endif

/*
 * SDRAM Memory Map
 * Even though we use two CS all the memory
 * is mapped to one contiguous block
 */
#define CONFIG_NR_DRAM_BANKS		2
#define CONFIG_SYS_SDRAM_BASE		0x00000000
#define CONFIG_SYS_RAM_DCU1_SIZE	0x20000000	// auto detection from hw settings

#define CONFIG_NO_RELOCATION
//if the relocation is enabled, the address is used to be the stack at very beginning.
#define CONFIG_SYS_INIT_SP_ADDR     0x00100000

#define CONFIG_SYS_L2CACHE_OFF
#ifdef CONFIG_NOCS_BSD //turn off CACHE for BAD TEST only
#define CONFIG_SYS_ICACHE_OFF
#define CONFIG_SYS_DCACHE_OFF 
#else
#if 0 // 1:cache disable   0:enable
#define CONFIG_SYS_ICACHE_OFF
#define CONFIG_SYS_DCACHE_OFF
#else
#define CONFIG_NONCACHE_ALLOCATION
#define CONFIG_CMD_CACHE
#endif
#endif

#ifndef CONFIG_SYS_L2CACHE_OFF
#define CONFIG_SYS_L2_PL310		1
#define CONFIG_SYS_PL310_BASE	0x48242000
#endif
#define CONFIG_SYS_CACHELINE_SIZE	32

/*
 * 64 bytes before this address should be set aside for u-boot.img's
 * header. That is 80E7FFC0--0x80E80000 should not be used for any
 * other needs.
 * ==> 0x00020000 for bootcode1
 * ==> 0x01400000 for bootcode2
 * ==> 0x00020000 for bootcode3
 */
#define CONFIG_JUMP_ADDRESS_FOR_BCLDR_2	0x01400000
#define CONFIG_JUMP_ADDRESS_FOR_BCLDR_3	0x00020000

/*
 * make AUTORUM=BCLDR2
 * make AUTORUM=BCLDR3
 */
#ifdef CONFIG_AUTO_RUN_BOOTLOADER2
	#define CONFIG_AUTO_RUN_BOOTLOADER	2
	#define CONFIG_LOAD_AUDIO2_IMAGE
#endif

#ifdef CONFIG_AUTO_RUN_BOOTLOADER3
	#define CONFIG_AUTO_RUN_BOOTLOADER	3
#endif

/*
 * rm include/autoconf.mk ---- prevent use old CONFIG_SYS_TEXT_BASE
 * make CONFIG_SYS_TEXT_BASE
 */
#ifndef CONFIG_SYS_TEXT_BASE
	#define CONFIG_SYS_TEXT_BASE		0x00020000
#endif

#define CONFIG_BOOT_PARAM_BASE			(0x00100000 + 0x100)
#define CONFIG_HEAP_RELOCATION

/* ENV related config options */
#define CONFIG_ENV_IS_NOWHERE

#define CONFIG_SYS_PROMPT       "Realtek> "

/* Library support */
#define CONFIG_LZMA
#define CONFIG_LZO

#ifdef CONFIG_CMD_NET
/* Eth Net */
#define CONFIG_CMD_PING
#define CONFIG_CMD_TFTPPUT
#define CONFIG_RTL8139CPLUS
#define CONFIG_TFTP_BLOCKSIZE		400

/* Network setting */

#define CONFIG_ETHADDR				00:10:20:30:40:50
#define CONFIG_IPADDR				192.168.100.1
#define CONFIG_GATEWAYIP			192.168.100.254
#define CONFIG_SERVERIP				192.168.100.2
#define CONFIG_NETMASK				255.255.255.0
#endif

/* Dss info*/
#define CONFIG_CMD_DSSINFO

/* NAND */
//#define CONFIG_MTD_NAND_RTK

/* BISR */
#define ENABLE_SCPU_BISR
#define ENABLE_VCPU_BISR
#define ENABLE_ACPU_BISR
#define ENABLE_DISP_BISR
//#define ENABLE_MCU_BISR
//#define ENABLE_GPU_BISR
//#define ENABLE_DEMOD_BISR

/* DDR Calibration */
//#define ENABLE_DDR_CALIBRATION

/* USB Setting */
#ifdef CONFIG_PARTITIONS
#define CONFIG_CMD_FAT
#endif
/*
 * get_vfatname_block     => assign to 0x0130_0000
 * get_dentfromdir_block  => assign to 0x0131_0000
 * do_fat_read_block      => assign to 0x0132_0000
 */
//#define CONFIG_FAT_USE_EXTMEM_FOR_LARGE_ARRAY

//#define CONFIG_PARTITIONS
//#define CONFIG_DOS_PARTITION
//#define CONFIG_CMD_USB
//#define CONFIG_USB_STORAGE
//#define CONFIG_USB_EHCI
//#define CONFIG_USB_RTK_EHCI
//#define CONFIG_USB_MAX_CONTROLLER_COUNT 2
//#define CONFIG_SYS_USB_EHCI_MAX_ROOT_PORTS 2
//#define CONFIG_USB_RTKBT

/* PCB Manager */
#define CONFIG_SYS_PCB_MANAGER

/* Factory */
#define CONFIG_SYS_FACTORY
//#define CONFIG_SYS_FACTORY_PROTECT_ALL  /* Add rtk_checksum to confirm data */
#define PANEL_CONFIG_FROM_FACTORY_PANEL_BIN

/* Factory Read-only : depend on customer */
//#define CONFIG_SYS_FACTORY_READ_ONLY

/* Decide Bootcode Enable Panel Parameter */
#define CONFIG_SYS_PANEL_SUPPORT 1

/* Panel Parameter */
#if CONFIG_SYS_PANEL_SUPPORT
#define CONFIG_SYS_PANEL_PARAMETER
/* default turn on*/
#define CONFIG_SYS_PANEL_DISABLE_PATTERN_GEN
#define CONFIG_CMD_PANEL
#else
#undef CONFIG_SYS_PANEL_SUPPORT
#undef CONFIG_SYS_PANEL_PARAMETER
#undef CONFIG_CMD_PANEL
#endif


/* TCON settting from factory */
//#define CONFIG_PANEL_APPLY_TCON_SETTING

/* Pin Mux */
#define CONFIG_SYS_PIN_MUX

/* GPIO */
#define CONFIG_REALTEK_GPIO

/* I2C */
#define CONFIG_I2C_MULTI_BUS
#define CONFIG_REALTEK_I2C

/* PWM */
#define CONFIG_REALTEK_PWM

/* LSADC */
#define CONFIG_REALTEK_LSADC

/* MISC Wakeup */
#define CONFIG_MISC_MGR_WAKEUP

/* Local Dimming Interface */
//#define CONFIG_REALTEK_LOCAL_DIMMING_INTERFACE

/* Logo Display */
//#define CONFIG_SYS_LOGO_DISP
#ifdef CONFIG_SYS_LOGO_DISP
//#define CONFIG_SYS_LOGO_DISP_NTSC
//#define CONFIG_SYS_LOGO_DISP_PAL
//#define CONFIG_SYS_LOGO_DISP_1080P50
//#define CONFIG_SYS_LOGO_DISP_1080P60
#endif

/* Bootcode Feature: Rescue linux read from USB */
//#define CONFIG_RESCUE_FROM_USB
//#define CONFIG_RESCUE_FROM_USB_FILENAME				"vmlinux.rescue.rtd299x.bin"

/* Bootcode Feature: Boot images read from USB */
//#define CONFIG_BOOT_FROM_USB
//#define CONFIG_BOOT_FROM_USB_KERNEL_FILENAME		"vmlinux.bin"
//#define CONFIG_BOOT_FROM_USB_AUDIO_FW_FILENAME		"bluecore.audio"
//#define CONFIG_BOOT_FROM_USB_VIDEO_FW_1_FILENAME	"video_firmware.bin"
//#define CONFIG_BOOT_FROM_USB_VIDEO_FW_2_FILENAME	"video2_firmware.bin"
//#define CONFIG_BOOT_FROM_USB_LZMA_EXTNAME			"lzma"

#if 0
/* Bootcode Feature: Detect install.img from USB when AC on */
#define CONFIG_USB_UPDATE_WHEN_AC_ON

/* Bootcode Feature: Detect dvrboot.exe.bin from USB when AC on */
#define CONFIG_USB_UPDATE_UBOOT_WHEN_AC_ON

/* Bootcode Feature: Read rescue linux from install.img or flash */
//#define CONFIG_USB_UPDATE_READ_RESCUE_FROM_FLASH
#endif

#if 1
/* Bootcode Feature: Clear env from factory after updated bootcode */
//#define CONFIG_CLEAR_ENV_AFTER_UPDATE_BOOTCODE
#endif

#if 1
/* Bootcode Feature: Display the time information to evaluate */
//#define CONFIG_DISPLAY_TIME_EVALUATION
#endif

#if 0
/* Bootcode Feature: Customize function callback register */
#define CONFIG_CUSTOMIZE_FUNC_REGISTER
#endif

#if 0
/* Bootcode Feature: Disable print log in uboot stage */
#define CONFIG_SILENT_CONSOLE
#endif

#if 0
/* Bootcode Feature: Disable print log in kernel stage */
#define CONFIG_SILENT_KERNEL
#endif

#if 0
/* build uboot run flash_writer directly */
#define CONFIG_RUN_FLASH_WRITER
#endif

// Config panel name and compile options
#if (0) // CMI V500 VBY1 panel setting
  /* VBY1 panel setting */
  #define CONFIG_PANEL_NAME "asm/arch/panel/CMI_V500_4K2K_VBY1.h"
  #define VBY_ONE 1
  #define VBY_ONE_PANEL_CMI_V500_4K2K_VBY1
#elif (0) // China Start 4k2k VBY1 panel
  #define CONFIG_PANEL_NAME "asm/arch/panel/China_Star_4K2K_VBY1.h"
  #define VBY_ONE 1
  #define VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1
#elif (0) //PixelWorks PA-168 4k2k MEMC TCON control
  //PixelWorks PA-168 4k2k MEMC TCON control
  //#define ENABLE_PA168_BOOTUP_IN_2CH_MODE  	// rtd299x boot up LVDS output in 2ch mode
  #ifdef ENABLE_PA168_BOOTUP_IN_2CH_MODE
  #define CONFIG_PANEL_NAME "asm/arch/panel/au_t550QVF01_demo_v3.h"
  #else
  #define CONFIG_PANEL_NAME "asm/arch/panel/au_t550QVF01_PA168.h"
  #endif
#elif (0) // Samsung LSC400HM03
  #define CONFIG_PANEL_NAME "asm/arch/panel/tsb_samsung_lsc400hm03.h"
  #define LVDS_PANEL_TSB_SAMSUNG_LSC400HM03
#elif (0) // 4k2k30Hz_4port LVDS + millet3
  #define CONFIG_PANEL_NAME "asm/arch/panel/CMI_Millet3_v500_4k2k.h"
  //#define LVDS_PANEL_MILLET3_4K2K_30
  #define LVDS_PANEL_MILLET3_2K1K_120
#else // default 60Hz panel
  /* LVDS panel setting */
  #define CONFIG_PANEL_NAME "asm/arch/panel/default_panel.h"
#endif


/*config Android OTA/Recovery mode feature*/
/*this feature should be used with the specific android recovery image(as the role of normal rescue)*/
#define CONFIG_ANDROID_RECOVERY 1

//298x bootcode FILE Name
#define BOOTCODE_RESCUE         "dvrboot.rescue.exe.bin"
#define FULL_IMG                "install.img"
#define USB_AUTO_SCRIPT         "rtk_autoupdate.lst"
#define MAX_USB_SCRIPT_LINE	64
#define MAX_USB_SCRIPT_LINE_LEN	128


#endif /* __CONFIG_RTK_RTD298X_COMMON_H */

