/*
 * SAMSUNG EXYNOS5 USB HOST XHCI Controller
 *
 * Copyright (C) 2012 Samsung Electronics Co.Ltd
 *	Vivek Gautam <gautam.vivek@samsung.com>
 *	Vikas Sajjan <vikas.sajjan@samsung.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301 USA
 */

/*
 * This file is a conglomeration for DWC3-init sequence and further
 * exynos5 specific PHY-init sequence.
 */

#include <common.h>
#include <malloc.h>
#include <usb.h>
#include <watchdog.h>
#include <asm-generic/errno.h>
#include <linux/compat.h>

#include "xhci.h"
#include <usb/usb_reg.h>

#define USB_PHY_DELAY	5
static int get_usb2_phy(int port1, int phy_reg) {
	int phy_value;
	int addr;

	if(port1 > 4 && port1 < 1) {
		printf("#@# %s(%d) error port1 %d\n", __func__, __LINE__, port1);
		return -1;
	}

	if (phy_reg < 0xe0 || phy_reg > 0xf7) {
		printf("#@# %s(%d) error phy_reg 0x%x\n", __func__, __LINE__, phy_reg);
		return -1;
	}

	addr = 0xb8058280 + (port1 - 1) * 4;

	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = 0x02000000 | (phy_reg & 0x0f) << 8;
	//mdelay(USB_PHY_DELAY);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = 0x02000000 | (phy_reg & 0xd0) << 4;
	//mdelay(USB_PHY_DELAY);
	phy_value = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) & 0xff;
	//printf("#@# %s(%d) port %d phy_reg 0x%.2x = 0x%x\n", __func__, __LINE__, port1, phy_reg, phy_value);

	return (phy_value & 0xff);
}

static int set_usb2_phy(int port1, int phy_reg, int phy_value) {
	int value;
	int addr;

	if(port1 > 4 && port1 < 1) {
		printf("#@# %s(%d) error port1 %d\n", __func__, __LINE__, port1);
		return -1;
	}

	if (phy_reg < 0xe0 || phy_reg > 0xf7) {
		printf("#@# %s(%d) error phy_reg 0x%x\n", __func__, __LINE__, phy_reg);
		return -1;
	}

	addr = 0xb8058280 + (port1 - 1) * 4;

	do {
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(VSTATUS0_OUT_reg) = (phy_value & 0xff) << 24 | (phy_value & 0xff) << 16 | (phy_value & 0xff) << 8 | (phy_value & 0xff);
		//mdelay(USB_PHY_DELAY);
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = 0x02000000 | (phy_reg & 0x0f) << 8;
		//mdelay(USB_PHY_DELAY);
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = 0x02000000 | (phy_reg & 0xf0) << 4;
		//mdelay(USB_PHY_DELAY);
		value = get_usb2_phy(port1, phy_reg);
		//printf("#@# %s(%d) port %d phy_reg 0x%.2x set 0x%x get 0x%x\n", __func__, __LINE__, port1, phy_reg, phy_value & 0xff, value);
	} while (0); // just write once
	//} while (value != phy_value); // write till the data is correct

	return value;
}

void check_mdio_ready(void)
{
	int value;
	do {
		//mdelay(USB_PHY_DELAY);
		value = ((*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)) >> MDIO_CTR_mdio_busy_shift ) & 0x1;
	} while(value == 1);
}

void usb3_phy_setting(void)
{
	printf("#@# %s(%d) +++ 20130826\n", __func__, __LINE__);

	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x4AB8000D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xC0CE010D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xE048020D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x2770030D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x5978040D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x6164050D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x3168060D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x3220070D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x35B3080D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x923C090D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x92400A0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x8B150B0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x4CEA0C0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x148A0D0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x98C90E0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x80000F0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x000C100D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x4C00110D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xFC00120D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0C81130D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xDE01140D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0000150D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0000160D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0000170D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0000180D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xE102190D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x12631A0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xC7FD1B0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xCB801C0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xA03F1D0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xC2801E0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xB7F0200D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0407210D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0016220D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x0CA1230D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x93A6240D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x2B92250D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x646D260D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x80E8270D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xE060280D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x30802A0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x20382B0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x74AE2C0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0xE54C2D0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x700E2E0D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x7978040D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x923C090D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x903C090D;
	check_mdio_ready();
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(MDIO_CTR_reg)=0x923C090D;
	check_mdio_ready();

	printf("#@# %s(%d) --- \n", __func__, __LINE__);
}

void usb2_phy_setting(void)
{
	printf("#@# %s(%d) +++ 20130823-1\n", __func__, __LINE__);

	/////////////////////////////////////////////
	// set PLL 480 Mhz for port3
	set_usb2_phy(3, 0xf7, 0x0f);
	set_usb2_phy(3, 0xe4, 0xc3);
	set_usb2_phy(3, 0xe7, 0xe3);

	/////////////////////////////////////////////
	// for port 1
	#if 1 /* no auto_k */
	set_usb2_phy(1, 0xe0, 0x44);
	set_usb2_phy(1, 0xe1, 0xe8);
	set_usb2_phy(1, 0xe2, 0x99);
	set_usb2_phy(1, 0xe3, 0xa1);
	set_usb2_phy(1, 0xe5, 0x95);
	set_usb2_phy(1, 0xe6, 0xb8);
	set_usb2_phy(1, 0xf0, 0xfc);
	set_usb2_phy(1, 0xf1, 0x8c);
	set_usb2_phy(1, 0xf2, 0x00);
	set_usb2_phy(1, 0xf3, 0x11);
	set_usb2_phy(1, 0xf4, 0x9b);
	set_usb2_phy(1, 0xf6, 0x01);
	#else
#if defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC) || defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC_V2)
	set_usb2_phy(1, 0xe2, 0x9b);
#endif /* CONFIG_BOARD_TV005_L4300_RTD2993_EMMC */
	set_usb2_phy(1, 0xe5, 0x91);
	set_usb2_phy(1, 0xe1, 0x4a);
	mdelay(USB_PHY_DELAY);
	set_usb2_phy(1, 0xe1, 0xea);
	#endif

	/////////////////////////////////////////////
	// for port 2
	#if 1 /* no auto_k */
	set_usb2_phy(2, 0xe0, 0x44);
	set_usb2_phy(2, 0xe1, 0xe8);
	set_usb2_phy(2, 0xe2, 0x99);
	set_usb2_phy(2, 0xe3, 0xa1);
	set_usb2_phy(2, 0xe5, 0x95);
	set_usb2_phy(2, 0xe6, 0xb8);
	set_usb2_phy(2, 0xf0, 0xfc);
	set_usb2_phy(2, 0xf1, 0x8c);
	set_usb2_phy(2, 0xf2, 0x00);
	set_usb2_phy(2, 0xf3, 0x11);
	set_usb2_phy(2, 0xf4, 0x9b);
	set_usb2_phy(2, 0xf6, 0x01);
	#else
#if defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC) || defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC_V2)
	set_usb2_phy(2, 0xe2, 0x9b);
#endif /* CONFIG_BOARD_TV005_L4300_RTD2993_EMMC */
	set_usb2_phy(2, 0xe5, 0x91);
	set_usb2_phy(2, 0xe1, 0x4a);
	mdelay(USB_PHY_DELAY);
	set_usb2_phy(2, 0xe1, 0xea);
	#endif

	/////////////////////////////////////////////
	// for port 3
	#if 1 /* no auto_k */
	set_usb2_phy(3, 0xe0, 0x44);
	set_usb2_phy(3, 0xe1, 0xe8);
	set_usb2_phy(3, 0xe2, 0x99);
	set_usb2_phy(3, 0xe3, 0xa1);
	set_usb2_phy(3, 0xe5, 0x95);
	set_usb2_phy(3, 0xe6, 0xb8);
	set_usb2_phy(3, 0xf0, 0xfc);
	set_usb2_phy(3, 0xf1, 0x8c);
	set_usb2_phy(3, 0xf2, 0x00);
	set_usb2_phy(3, 0xf3, 0x11);
	set_usb2_phy(3, 0xf4, 0x9b);
	set_usb2_phy(3, 0xf6, 0x01);
	#else
#if defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC) || defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC_V2)
	set_usb2_phy(3, 0xe2, 0x9b);
#endif /* CONFIG_BOARD_TV005_L4300_RTD2993_EMMC */
	set_usb2_phy(3, 0xe5, 0x91);
	set_usb2_phy(3, 0xe1, 0x4a);
	mdelay(USB_PHY_DELAY);
	set_usb2_phy(3, 0xe1, 0xea);
	#endif

	/////////////////////////////////////////////
	// for port 4
	#if 1 /* no auto_k */
	set_usb2_phy(4, 0xe0, 0x44);
	set_usb2_phy(4, 0xe1, 0xe8);
	set_usb2_phy(4, 0xe2, 0x99);
	set_usb2_phy(4, 0xe3, 0xa1);
	set_usb2_phy(4, 0xe5, 0x95);
	set_usb2_phy(4, 0xe6, 0xb8);
	set_usb2_phy(4, 0xf0, 0xfc);
	set_usb2_phy(4, 0xf1, 0x8c);
	set_usb2_phy(4, 0xf2, 0x00);
	set_usb2_phy(4, 0xf3, 0x11);
	set_usb2_phy(4, 0xf4, 0x9b);
	set_usb2_phy(4, 0xf6, 0x01);
	#else
#if defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC) || defined(CONFIG_BOARD_TV005_L4300_RTD2993_EMMC_V2)
	set_usb2_phy(4, 0xe2, 0x9b);
#endif /* CONFIG_BOARD_TV005_L4300_RTD2993_EMMC */
	set_usb2_phy(4, 0xe5, 0x91);
	set_usb2_phy(4, 0xe1, 0x4a);
	mdelay(USB_PHY_DELAY);
	set_usb2_phy(4, 0xe1, 0xea);
	#endif

	printf("#@# %s(%d) --- \n", __func__, __LINE__);
}

static void usb3_mac_setting(void)
{
	unsigned int tmp;

	printf("#@# %s(%d) +++ 20130916\n", __func__, __LINE__);

#if 0 /* setting for RTD299X fpga board */
	//printf("#@# %s(%d) usb code version\n", __func__, __LINE__);
	//printf("#@# %s(%d) GET_MAPPED_RBUS_ADDR(WRAP_CTR_reg) = 0x%.8x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(WRAP_CTR_reg));

	//printf("#@# %s(%d) set usb2 port count = 1, bit[7:4]\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg);
	tmp &= ~(0xf << HMAC_CTR0_host_num_u2_port_shift);
	tmp |= (0x1 << HMAC_CTR0_host_num_u2_port_shift);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg));
#endif /* setting for RTD299X fpga board */

#if 0
	//printf("#@# %s(%d) set xhci version to 0.96, bit[31]\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg);
	tmp &= ~(0x1 << 31);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(HMAC_CTR0_reg));
#endif

#if 1
	//printf("#@# %s(%d) disable multi request, bit[1]\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013000) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013000));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013000);
	tmp |= (0x1 << 1);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013000) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013000) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013000));
#endif

	//printf("#@# %s(%d) set utmi clock to 30mhz, bit[3]\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058200) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058200));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058200);
	tmp |= (0x1 << 3);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058200) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058200) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058200));

	//printf("#@# %s(%d) set utmi clock to 30mhz, bit[3]\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058204) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058204));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058204);
	tmp |= (0x1 << 3);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058204) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058204) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058204));

	//printf("#@# %s(%d) set utmi clock to 30mhz, bit[3]\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058208) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058208));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058208);
	tmp |= (0x1 << 3);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058208) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058208) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058208));

	//printf("#@# %s(%d) set utmi clock to 30mhz, bit[3]\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805820c) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805820c));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805820c);
	tmp |= (0x1 << 3);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805820c) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805820c) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805820c));

#if 1
	// GTXTHRCFG
	//printf("#@# %s(%d) GTXTHRCFG\n", __func__, __LINE__);
	//printf("#@# %s(%d) GET_MAPPED_RBUS_ADDR(0xb8058108) = 0x%.8x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058108));
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058108) = 0x01010000; // disable GTXTHRCFG
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058108) = 0x21010000;
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058108) = 0x22020000;
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058108) = 0x24040000;
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058108) = 0x30100000;
	//printf("#@# %s(%d) GET_MAPPED_RBUS_ADDR(0xb8058108) = 0x%.8x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8058108));

	// GRXTHRCFG
	//printf("#@# %s(%d) GRXTHRCFG\n", __func__, __LINE__);
	//printf("#@# %s(%d) GET_MAPPED_RBUS_ADDR(0xb805810c) = 0x%.8x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805810c));
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805810c) = 0x01080000; // disable GRXTHRCFG
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805810c) = 0x21080000;
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805810c) = 0x22100000;
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805810c) = 0x24200000;
	//*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805810c) = 0x30800000;
	//printf("#@# %s(%d) GET_MAPPED_RBUS_ADDR(0xb805810c) = 0x%.8x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb805810c));
#endif

	// disable ahb timing function
	//printf("#@# %s(%d) disable ahb timing function\n", __func__, __LINE__);
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013088) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013088));
	tmp = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013088);
	tmp |= (0x1 << 0);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013088) = tmp;
	//printf("#@# %s(%d) *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013088) = 0x%x\n", __func__, __LINE__, *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013088));

	printf("#@# %s(%d) --- \n", __func__, __LINE__);
}

int xhci_hcd_init(int index, struct xhci_hccr **hccr, struct xhci_hcor **hcor)
{
	// FIXME
	// 1. set xhci usbphy
	// 2. register mapping
	// 3. irq ?

#define RTD299X_XHCI_BASE	0xb8050000

	*hccr = (struct xhci_hccr *)RTD299X_XHCI_BASE;
	*hcor = (struct xhci_hcor *)((uint32_t) *hccr
				+ HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	usb3_phy_setting();
	usb2_phy_setting();
	usb3_mac_setting();

	debug("xhci: init hccr %x and hcor %x hc_length %d\n",
		(uint32_t)*hccr, (uint32_t)*hcor,
		(uint32_t)HC_LENGTH(xhci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

void xhci_hcd_stop(int index)
{
	return;
}
