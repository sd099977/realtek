/*
 *  On-line: Bootcode need to generate environment variable "system_parameters",
 *           and pass them to kernel for installer.
 *
 * Off-line: When generating bootloader.tar in compile time,
 *           we need to pass the system_parameters for image_file_creator.
 */

#ifndef __SYS_PARAM_NAND__
#define __SYS_PARAM_NAND__

/*
 ************************************************
 * Attention:
 *   Because this file will be included by image_file_creator,
 *     please don't add code that depends on bootcode definition.
 *
 * Ex.
 *     (X) include "some_define.h"
 *     (X) #define SYS_PARAM_SOME_DEFINE CONFIG_SOME_DEFINE
 *     (X) #ifdef CONFIG_SOME_DEFINE
 ************************************************
 */

/* system_parameter_1 */
//#define SYS_PARAM_PARAM_ADDR		0x40000	// extern_param->env_param_saddr
#define SYS_PARAM_TV_SYSTEM			"NULL"

/* system_parameter_2 */
#define SYS_PARAM_BOOT_FLASH		"nand"
#define SYS_PARAM_FACTORY_START		0x1400000
#define SYS_PARAM_FACTORY_SIZE		0x800000		//8192KB

/* system_parameter_3 */
#define SYS_PARAM_BOOTCODE_START	0x0		// block_no:0x6
#define SYS_PARAM_BOOTCODE_SIZE		0x1400000		//20M

//#define SYS_PARAM_RESCUE_START	0x100000	// extern_param->rescue_img_addr
//#define SYS_PARAM_RESCUE_SIZE		0x3c0b20	// extern_param->rescue_img_size

/* system_parameter_4 */
//#define SYS_PARAM_BOOT_PART		0x0		// layout.txt in factory
#define SYS_PARAM_FACTORY_RO_START	0x1000000
#define SYS_PARAM_FACTORY_RO_SIZE	0x10000			//64KB

#endif /* __SYS_PARAM__ */

