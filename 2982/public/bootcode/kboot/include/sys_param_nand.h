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
#define SYS_PARAM_FACTORY_START		0x3500000
#define SYS_PARAM_FACTORY_SIZE		0x800000		//8M

/* system_parameter_3 */
#define SYS_PARAM_BOOTCODE_START	0x0		// in fact, bootcode-area start from block_no:0x6
#define SYS_PARAM_BOOTCODE_SIZE		0x1400000		//20M

/*secure store parameter*/
#define SYS_PARAM_SECURE_STORE_START	0x1400000	
#define SYS_PARAM_SECURE_STORE_SIZE		0x2100000	//33M	

/* system_parameter_4 */
#define SYS_PARAM_FACTORY_RO_START	0x3D00000
#define SYS_PARAM_FACTORY_RO_SIZE	0x200000	// 2M
#define SYS_PARAM_FACTORY_RESERVED   0x400000	// 4M

/*fw_table addr*/
#define SYS_PARAM_FW_TABLE_START	0x4300000

#endif /* __SYS_PARAM__ */

