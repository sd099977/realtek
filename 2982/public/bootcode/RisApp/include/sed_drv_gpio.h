#ifndef __SED_DRV_GPIO_H__
#define __SED_DRV_GPIO_H__

#include "sed_drv_common.h"

#define GPIO_REG_BASE	0xB801B100

#define GPIO0_DIR	(GPIO_REG_BASE + 0x0)
#define GPIO1_DIR   (GPIO_REG_BASE + 0x4)
#define GPIO2_DIR   (GPIO_REG_BASE + 0x8)
#define GPIO3_DIR   (GPIO_REG_BASE + 0xC)
#define GPIO4_DIR   (GPIO_REG_BASE + 0x10)
#define GPIO5_DIR   (GPIO_REG_BASE + 0x14)
#define GPIO0_DATO	(GPIO_REG_BASE + 0x18)
#define GPIO1_DATO  (GPIO_REG_BASE + 0x1C)
#define GPIO2_DATO  (GPIO_REG_BASE + 0x20)
#define GPIO3_DATO  (GPIO_REG_BASE + 0x24)
#define GPIO4_DATO  (GPIO_REG_BASE + 0x28)
#define GPIO5_DATO  (GPIO_REG_BASE + 0x2C)
#define GPIO0_DATI	(GPIO_REG_BASE + 0x30)
#define GPIO1_DATI  (GPIO_REG_BASE + 0x34)
#define GPIO2_DATI  (GPIO_REG_BASE + 0x38)
#define GPIO3_DATI  (GPIO_REG_BASE + 0x3C)
#define GPIO4_DATI  (GPIO_REG_BASE + 0x40)
#define GPIO5_DATI  (GPIO_REG_BASE + 0x44)
#define GPIO0_IE	(GPIO_REG_BASE + 0x48)
#define GPIO1_IE    (GPIO_REG_BASE + 0x4C)
#define GPIO2_IE    (GPIO_REG_BASE + 0x50)
#define GPIO3_IE    (GPIO_REG_BASE + 0x54)
#define GPIO4_IE    (GPIO_REG_BASE + 0x58)
#define GPIO5_IE    (GPIO_REG_BASE + 0x5C)
#define GPIO0_DP  	(GPIO_REG_BASE + 0x60)
#define GPIO1_DP    (GPIO_REG_BASE + 0x64)
#define GPIO2_DP    (GPIO_REG_BASE + 0x68)
#define GPIO3_DP    (GPIO_REG_BASE + 0x6C)
#define GPIO4_DP    (GPIO_REG_BASE + 0x70)
#define GPIO5_DP    (GPIO_REG_BASE + 0x74)

#define MIS_GPIO_BASE		(0xb8061100)
#define MIS_GPDIR	(MIS_GPIO_BASE + 0x0)
#define MIS_GPDATO	(MIS_GPIO_BASE + 0x8)




void sed_gpio_init (void);
void GPIO_reset (void);
void GPIO_toggle (void);
void GPIO_pulse (void);

#endif
