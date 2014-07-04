/*
 * Copyright 2007 Freescale Semiconductor, Inc.
 *
 * This file is licensed under the terms of the GNU General Public
 * License Version 2. This file is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef _CONFIG_CMD_DEFAULT_H
#define _CONFIG_CMD_DEFAULT_H

/*
 * Alphabetical list of all commands that are configured by default.
 * This is essentially all commands minus those that are considered
 * "non-standard" for some reason (memory hogs, requires special
 * hardware, not fully tested, etc.).
 */

#define CONFIG_CMD_BDI		/* bdinfo			*/
#ifndef CONFIG_SYS_NO_FLASH
#define CONFIG_CMD_FLASH	/* flinfo, erase, protect	*/
#endif
#define CONFIG_CMD_GO		/* go			*/
#define CONFIG_CMD_LOADB	/* loadb, loady	*/
#define CONFIG_CMD_MEMORY	/* md mm nm mw cp cmp crc base loop mtest */
#define CONFIG_CMD_NET		/* bootp, tftpboot, rarpboot	*/
#define CONFIG_CMD_SAVEENV	/* saveenv			*/

#endif	/* _CONFIG_CMD_DEFAULT_H */
