/*
 * Configuration settings for the Realtek 298X Demo board.
 *
 * Won't include this file.
 * Just type "make <board_name>_config" and will be included in source tree.
 */

#ifndef __CONFIG_RTK_298X_TV010_1G_1X16_H
#define __CONFIG_RTK_298X_TV010_1G_1X16_H


#include <configs/rtd298x_tv001_bga459_ddr_1g_1x16.h>

/* Watchdog */
#define CONFIG_REALTEK_WATCHDOG

/*8051 tv010 customize*/
#define CONFIG_MISC_MGR_CUSTOM_TV010

#endif /* __CONFIG_RTK_298X_TV010_1G_1X16_H */
