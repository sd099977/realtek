#ifndef __NOCS_BSD_ENV_H__
#define __NOCS_BSD_ENV_H__

#include <linux/types.h>
#include <common.h>
#include <stdarg.h>
#include <malloc.h>
#include <stdio_dev.h>
#include <exports.h>
#include <config.h>
#include <command.h>
#include <malloc.h>
#include <asm/errno.h>
#include <asm/io.h>

/*bit definition for  rtk_show_data() */
#define TYPE32                  BIT0
#define TCLOSE                  BIT1 //show data closely

#endif  //? #define __NOCS_BSD_ENV_H__