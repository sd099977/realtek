/*
 * USB HOST EHCI Controller
 */

#include <common.h>
#include <malloc.h>
#include <usb.h>
#include <watchdog.h>
#include <asm-generic/errno.h>
#include <linux/compat.h>

#include "ehci.h"
#include <usb/usb_reg.h>

#define USB_PHY_DELAY	5
#define CONFIG_USB_RTK_HCD_SECOND
#define CONFIG_MACH_RTK_298x
static int get_usb2_phy_mac0(int port1, int phy_reg) {
	int phy_value;
	int addr;
	unsigned int tmp;

	if(port1 > 2 && port1 < 1) {
		printf("#@# %s(%d) error port1 %d\n", __func__, __LINE__, port1);
		return -1;
	}

	if (phy_reg < 0xe0 || phy_reg > 0xf7) {
		printf("#@# %s(%d) error phy_reg 0x%x\n", __func__, __LINE__, phy_reg);
		return -1;
	}

	addr = 0xb80130a4;

	tmp = 0x00020000 | (phy_reg & 0x0f) << 8 | ((port1 == 1)? (0x2000) : (0x4000));
	//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
	mdelay(USB_PHY_DELAY);
	tmp = 0x00020000 | (phy_reg & 0xd0) << 4 | ((port1 == 1)? (0x2000) : (0x4000));
	//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
	mdelay(USB_PHY_DELAY);

	phy_value = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) & 0xff;
	//printf("#@# %s(%d) port %d phy_reg 0x%.2x = 0x%x\n", __func__, __LINE__, port1, phy_reg, phy_value);

	return (phy_value & 0xff);
}

static int get_usb2_phy_mac1(int port1, int phy_reg) {
	int phy_value;
	int addr;
	unsigned int tmp;

	if(port1 > 1 && port1 < 1) {
		printf("#@# %s(%d) error port1 %d\n", __func__, __LINE__, port1);
		return -1;
	}

	if (phy_reg < 0xe0 || phy_reg > 0xf7) {
		printf("#@# %s(%d) error phy_reg 0x%x\n", __func__, __LINE__, phy_reg);
		return -1;
	}

	addr = 0xb80120a4;

	tmp = 0x00020000 | (phy_reg & 0x0f) << 8 | ((port1 == 1)? (0x2000) : (0x4000));
	//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
	mdelay(USB_PHY_DELAY);
	tmp = 0x00020000 | (phy_reg & 0xd0) << 4 | ((port1 == 1)? (0x2000) : (0x4000));
	//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
	mdelay(USB_PHY_DELAY);

	phy_value = *(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) & 0xff;
	//printf("#@# %s(%d) port %d phy_reg 0x%.2x = 0x%x\n", __func__, __LINE__, port1, phy_reg, phy_value);

	return (phy_value & 0xff);
}

static int set_usb2_phy_mac0(int port1, int phy_reg, int phy_value) {
	int value;
	int addr;
	unsigned int tmp;

	if(port1 > 2 && port1 < 1) {
		printf("#@# %s(%d) error port1 %d\n", __func__, __LINE__, port1);
		return -1;
	}

	if (phy_reg < 0xe0 || phy_reg > 0xf7) {
		printf("#@# %s(%d) error phy_reg 0x%x\n", __func__, __LINE__, phy_reg);
		return -1;
	}

	addr = 0xb80130a4;

	do {
		if (port1 == 1) {
			*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013804) = (phy_value & 0xff);
		} else {
			*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8013824) = (phy_value & 0xff);
		}
		mdelay(USB_PHY_DELAY);

		tmp = 0x00020000 | (phy_reg & 0x0f) << 8 | ((port1 == 1)? (0x2000) : (0x4000));
		//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
		mdelay(USB_PHY_DELAY);
		tmp = 0x00020000 | (phy_reg & 0xf0) << 4 | ((port1 == 1)? (0x2000) : (0x4000));
		//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
		mdelay(USB_PHY_DELAY);

		value = get_usb2_phy_mac0(port1, phy_reg);
		//printf("#@# %s(%d) port %d phy_reg 0x%.2x set 0x%x get 0x%x\n", __func__, __LINE__, port1, phy_reg, phy_value & 0xff, value);
	} while (0); // just write once
	//} while (value != phy_value); // write till the data is correct

	return value;
}

static int set_usb2_phy_mac1(int port1, int phy_reg, int phy_value) {
	int value;
	int addr;
	unsigned int tmp;

	if(port1 > 1 && port1 < 1) {
		printf("#@# %s(%d) error port1 %d\n", __func__, __LINE__, port1);
		return -1;
	}

	if (phy_reg < 0xe0 || phy_reg > 0xf7) {
		printf("#@# %s(%d) error phy_reg 0x%x\n", __func__, __LINE__, phy_reg);
		return -1;
	}

	addr = 0xb80120a4;

	do {
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8012804) = (phy_value & 0xff);
		mdelay(USB_PHY_DELAY);

		tmp = 0x00020000 | (phy_reg & 0x0f) << 8 | ((port1 == 1)? (0x2000) : (0x4000));
		//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
		mdelay(USB_PHY_DELAY);
		tmp = 0x00020000 | (phy_reg & 0xf0) << 4 | ((port1 == 1)? (0x2000) : (0x4000));
		//printf("#@# %s(%d) tmp 0x%x\n", __func__, __LINE__, tmp);
		*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(addr) = tmp;
		mdelay(USB_PHY_DELAY);

		value = get_usb2_phy_mac1(port1, phy_reg);
		//printf("#@# %s(%d) port %d phy_reg 0x%.2x set 0x%x get 0x%x\n", __func__, __LINE__, port1, phy_reg, phy_value & 0xff, value);
	} while (0); // just write once
	//} while (value != phy_value); // write till the data is correct

	return value;
}

void usb2_phy_setting(void)
{
	printk("#@# %s(%d) +++ for usbphy setting 20140609\n", __func__, __LINE__);

#if defined(CONFIG_MACH_RTK_298x)
	//USBPHY_Register_Setting(1);

	rtd_outl(0xb801380c,0x00000001); //Mac0 p0 UTMI reset
	rtd_outl(0xb801380c,0x00000000); //Mac0 p0 UTMI reset

	rtd_outl(0xb801382c,0x00000001); //Mac0 p1 UTMI reset
	rtd_outl(0xb801382c,0x00000000); //Mac0 p1 UTMI reset

#ifdef CONFIG_USB_RTK_HCD_SECOND
	rtd_outl(0xb801280c,0x00000001); //Mac1 p0 UTMI reset
	rtd_outl(0xb801280c,0x00000000); //Mac1 p0 1UTMI reset
#endif /* USB_RTK_HCD_SECOND */

	/////////////////////0xE0 manual Z0//////////////////////
	//Mac0 Write Port 0 manual mode
	set_usb2_phy_mac0(1, 0xe0, 0x60);
	set_usb2_phy_mac0(1, 0xe0, 0xa1);

	//Mac0 Write Port 1 manual mode
	set_usb2_phy_mac0(2, 0xe0, 0x60);
	set_usb2_phy_mac0(2, 0xe0, 0xa1);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0 manual mode
	set_usb2_phy_mac1(1, 0xe0, 0x60);
	set_usb2_phy_mac1(1, 0xe0, 0xa1);
#endif /* USB_RTK_HCD_SECOND */

	////////////////E1//////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe1, 0x2e);

	//Mac0 Write port1 E1
	set_usb2_phy_mac0(2, 0xe1, 0x2e);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write port0 E1
	set_usb2_phy_mac1(1, 0xe1, 0x2e);
#endif /* USB_RTK_HCD_SECOND */

	///////////////E2 EOP width& Bit /////////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe2, 0x9a);

	//Mac0 Write Port 1 E2
	set_usb2_phy_mac0(2, 0xe2, 0x9a);


#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe2, 0x9a);
#endif /* USB_RTK_HCD_SECOND */

	///////////////  E3 /////////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe3, 0x8b);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xe3, 0x8b);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe3, 0x8b);
#endif /* USB_RTK_HCD_SECOND */

	///////////////////E4 Output Swing////////////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe4, 0x8c);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xe4, 0x8c);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe4, 0x8c);
#endif /* USB_RTK_HCD_SECOND */

	///////////////////E7////////////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe7, 0x81);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xe7, 0x81);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe7, 0x81);
#endif /* USB_RTK_HCD_SECOND */

	/////////////////////MAC0 P0 RX 0xE0/Page1//////////////////////
	//Mac0 Write Port 0/page1
	set_usb2_phy_mac0(1, 0xf4, 0xbb);
	set_usb2_phy_mac0(1, 0xe0, 0x21);
	set_usb2_phy_mac0(1, 0xe0, 0x25);
	set_usb2_phy_mac0(1, 0xf4, 0x9b);

	//Mac0 Write Port1/page1
	set_usb2_phy_mac0(2, 0xf4, 0xbb);
	set_usb2_phy_mac0(2, 0xe0, 0x21);
	set_usb2_phy_mac0(2, 0xe0, 0x25);
	set_usb2_phy_mac0(2, 0xf4, 0x9b);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0 /page1
	set_usb2_phy_mac1(1, 0xf4, 0xbb);
	set_usb2_phy_mac1(1, 0xe0, 0x21);
	set_usb2_phy_mac1(1, 0xe0, 0x25);
	set_usb2_phy_mac1(1, 0xf4, 0x9b);
#endif /* USB_RTK_HCD_SECOND */

	///////////////////E4 Output Swing////////////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe4, 0xdc);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xe4, 0xdc);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe4, 0xdc);
#endif /* USB_RTK_HCD_SECOND */

	///////////////////E7////////////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe7, 0x71);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xe7, 0x71);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe7, 0x71);
#endif /* USB_RTK_HCD_SECOND */

	///////////////   E5  ////////////////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe5, 0x1d);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xe5, 0x1d);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe5, 0x1d);
#endif /* USB_RTK_HCD_SECOND */

	///////   E6  ////////////////
	//Mac0 Write Port 0
	set_usb2_phy_mac0(1, 0xe6, 0xc9);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xe6, 0xc9);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xe6, 0xc9);
#endif /* USB_RTK_HCD_SECOND */

	//////////////////// Slew rate 0xE1/Page1//////////////////////
	//Mac0 Write Port 0/page1
	set_usb2_phy_mac0(1, 0xf4, 0xbb);
	set_usb2_phy_mac0(1, 0xe1, 0xaf);
	set_usb2_phy_mac0(1, 0xf4, 0x9b);

	//Mac0 Write Port 1/page1
	set_usb2_phy_mac0(2, 0xf4, 0xbb);
	set_usb2_phy_mac0(2, 0xe1, 0xaf);
	set_usb2_phy_mac0(2, 0xf4, 0x9b);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0/page1
	set_usb2_phy_mac1(1, 0xf4, 0xbb);
	set_usb2_phy_mac1(1, 0xe1, 0xaf);
	set_usb2_phy_mac1(1, 0xf4, 0x9b);
#endif /* USB_RTK_HCD_SECOND */

	///////   F2  ////////////////
	//Mac0 Write Port 0 F2
	set_usb2_phy_mac0(1, 0xf2, 0x00);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xf2, 0x00);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xf2, 0x00);
#endif /* USB_RTK_HCD_SECOND */

	///////   F6  ////////////////
	//Mac0 Write Port 0 F2
	set_usb2_phy_mac0(1, 0xf6, 0x00);

	//Mac0 Write Port 1
	set_usb2_phy_mac0(2, 0xf6, 0x00);

#ifdef CONFIG_USB_RTK_HCD_SECOND
	//Mac1 Write Port 0
	set_usb2_phy_mac1(1, 0xf6, 0x00);
#endif /* USB_RTK_HCD_SECOND */
#endif /* defined(CONFIG_MACH_RTK_298x) */

	printf("#@# %s(%d) --- \n", __func__, __LINE__);
}

void usb2_clk_setting(void)
{
#ifdef CONFIG_MACH_RTK_298x
	// enable clock and reset of usb
	// release phy reset
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8000000) |= (0x7 << 8);
	mdelay(10);
	// mac clock enable
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb800000c) |= (0x14 << 0);
	mdelay(10);
	// mac clock disable
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb800000c) &= ~(0x14 << 0);
	mdelay(10);
	// release mac reset
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8000000) |= (0x7 << 4);
	mdelay(10);
	// mac clock enable
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb800000c) |= (0x14 << 0);
	mdelay(10);
	// disable interrupt to scpu
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb801a640) |= (0x1 << 5);
#endif /* CONFIG_MACH_RTK_298x */
}

int ehci_hcd_init(int index, struct ehci_hccr **hccr, struct ehci_hcor **hcor)
{
#define RTD298X_EHCI_BASE	0xb8013000
#define RTD298X_EHCI1_BASE	0xb8012000

	// just for mac0
	if (index == 0) {
		usb2_clk_setting();
		usb2_phy_setting();

		printf("#@# %s(%d) ehci mac0\n", __func__, __LINE__);
		*hccr = (struct ehci_hccr *)RTD298X_EHCI_BASE;
		*hcor = (struct ehci_hcor *)((uint32_t) *hccr
					+ HC_LENGTH(ehci_readl((unsigned int)&(*hccr)->cr_capbase)));
	} else {
		printf("#@# %s(%d) ehci mac1\n", __func__, __LINE__);
		*hccr = (struct ehci_hccr *)RTD298X_EHCI1_BASE;
		*hcor = (struct ehci_hcor *)((uint32_t) *hccr
					+ HC_LENGTH(ehci_readl((unsigned int)&(*hccr)->cr_capbase)));
	}

	debug("ehci: init hccr %x and hcor %x hc_length %d\n",
		(uint32_t)*hccr, (uint32_t)*hcor,
		(uint32_t)HC_LENGTH(ehci_readl(&(*hccr)->cr_capbase)));

	return 0;
}

int ehci_hcd_stop(int index)
{
#ifdef CONFIG_MACH_RTK_298x
	// enable clock and reset of usb
	// not release phy reset
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8000000) &= ~(0x7 << 8);
	mdelay(10);
	// mac clock disable
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb800000c) &= ~(0x14 << 0);
	mdelay(10);
	// not release mac reset
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb8000000) &= ~(0x7 << 4);
	mdelay(10);
	// disable interrupt to scpu
	*(unsigned int volatile *)GET_MAPPED_RBUS_ADDR(0xb801a640) &= ~(0x1 << 5);
#endif /* CONFIG_MACH_RTK_298x */

	return 0;
}
