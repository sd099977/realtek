#ifndef __FACTORY_LIB_H__
#define __FACTORY_LIB_H__

#ifndef CONFIG_SYS_RTK_NAND_FLASH

#include <asm/arch/sys_param_emmc.h>

#ifndef SYS_PARAM_FACTORY_START
#define CONFIG_FACTORY_START	0x1800000	/* For eMMC */
#else
#define CONFIG_FACTORY_START	SYS_PARAM_FACTORY_START
#endif

#ifndef SYS_PARAM_FACTORY_SIZE
#define CONFIG_FACTORY_SIZE		0x800000	/* For eMMC */
#else
#define CONFIG_FACTORY_SIZE		SYS_PARAM_FACTORY_SIZE
#endif

#else
#include <asm/arch/sys_param_nand.h>

#ifndef SYS_PARAM_FACTORY_START
#define CONFIG_FACTORY_START	0x3500000	/* For NAND */
#else
#define CONFIG_FACTORY_START	SYS_PARAM_FACTORY_START
#endif

#ifndef SYS_PARAM_FACTORY_SIZE
#define CONFIG_FACTORY_SIZE		0x800000	/* For NAND */
#else
#define CONFIG_FACTORY_SIZE		SYS_PARAM_FACTORY_SIZE
#endif

#endif	/*CONFIG_SYS_RTK_NAND_FLASH*/


#define FACTORY_HEADER_FILE_NAME		"tmp/factory/"

int factory_dump_info(void);
int factory_reset(void);
int factory_delete(char *path);
int factory_read_by_index(int index, char *buffer, int *length, char *name);
int factory_read(char *path, char**buffer, int *length);
int factory_write(char *path, char *buffer, int length);
int factory_save(void);
int factory_init(void);

#endif /* __FACTORY_LIB_H__ */

