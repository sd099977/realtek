/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 2012 by Chuck Chen <ycchen@realtek.com>
 *
 * Time initialization.
 */

#include <common.h>
#include <asm/utils.h>
#include <asm/arch/system.h>
#include <asm/arch/rbus/iso_reg.h>

//#define wfi()	__asm__ __volatile__ ("wfi" : : : "memory")

#define SB2_INV_INT_EN_VADDR			0xb801a004
#define DC_EC_CTRL_VADDR				0xb80082d0
#define DC_EC_ADDCMD_HI_VADDR			0xb80082d4
#define DC_EC_ADDCMD_LO_VADDR			0xb80082d8
#define DC_RD_TAG_CHECK_VADDR			0xb80082dc
#define DC_EXP_LANE_CTRL_VADDR		0xb8008f04

void hold_hw_semaphore(void)
{
//	printf("## Hold HW semaphore\n");

	rtd_outl(0xb801a000, 0x1);
}

void enable_ccdinr_memshare(void)
{
	unsigned int _iTemp;

//	printf("*** REG(0xb8024010)=0x%08x\n", rtd_inl(0xb8024010));
//	printf("*** REG(0xb802404c)=0x%08x\n", rtd_inl(0xb802404c));
//	printf("*** REG(0xb8024000)=0x%08x\n", rtd_inl(0xb8024000));

	_iTemp = rtd_inl(0xb8024010);
	_iTemp |= 1UL<<19;
	rtd_outl(0xb8024010, _iTemp);	// force_2D = 1

	_iTemp = rtd_inl(0xb802404c);
	_iTemp &= ~(1UL<<10);
	rtd_outl(0xB802404C, _iTemp);	// force_2D_timing = 0

	_iTemp = rtd_inl(0xb8024000);
	_iTemp &= ~(1UL<<28);
	rtd_outl(0xb8024000, _iTemp);	// ip_enable = 0

	_iTemp = rtd_inl(0xb8024010);
	_iTemp |= 1UL<<29;
	rtd_outl(0xb8024010, _iTemp);	// Ccdinr_memshare_en = 1

//	printf("*** Enable DI memshare\n");
//	printf("*** REG(0xb8024010)=0x%08x\n", rtd_inl(0xb8024010));
//	printf("*** REG(0xb802404c)=0x%08x\n", rtd_inl(0xb802404c));
//	printf("*** REG(0xb8024000)=0x%08x\n", rtd_inl(0xb8024000));
}

void disable_ccdinr_memshare(void)
{
	unsigned int _iTemp;

//	printf("*** REG(0xb8024010)=0x%08x\n", rtd_inl(0xb8024010));
//	printf("*** REG(0xb802404c)=0x%08x\n", rtd_inl(0xb802404c));
//	printf("*** REG(0xb8024000)=0x%08x\n", rtd_inl(0xb8024000));

	_iTemp = rtd_inl(0xb8024010);
	_iTemp &= ~(1UL<<19);
	rtd_outl(0xb8024010, _iTemp);	// force_2D = 0

	_iTemp = rtd_inl(0xb802404c);
	_iTemp &= ~(1UL<<10);
	rtd_outl(0xB802404C, _iTemp);	// force_2D_timing = 0

	_iTemp = rtd_inl(0xb8024000);
	_iTemp &= ~(1UL<<28);
	rtd_outl(0xb8024000, _iTemp);	// ip_enable = 0

	_iTemp = rtd_inl(0xb8024010);
	_iTemp &= ~(1UL<<29);
	rtd_outl(0xb8024010, _iTemp);	// Ccdinr_memshare_en = 0

//	printf("*** Disable DI memshare\n");
//	printf("*** REG(0xb8024010)=0x%08x\n", rtd_inl(0xb8024010));
//	printf("*** REG(0xb802404c)=0x%08x\n", rtd_inl(0xb802404c));
//	printf("*** REG(0xb8024000)=0x%08x\n", rtd_inl(0xb8024000));
}

void do_ddr_calibration(void)
{
#ifdef ENABLE_DDR_CALIBRATION
	unsigned int regValue = 0;
	unsigned char v1done = 0;
	unsigned char v2done = 0;
	unsigned int count_down = 10000;

	// enable int_vs
	rtd_outl(SB2_CPU_INT_EN_reg, _BIT7 | _BIT0);

	// notice vcpu1 to enter calibration.
	rtd_outl(REG_DDR_CAL_FLAG_reg, _BIT0); // set Reg(A).bit0=1 to notify v_ddr_cal.S to execute ddr calibration

	// wait int_vs
	while(count_down > 0){
		regValue = rtd_inl(SB2_CPU_INT_reg);
		if ((regValue & _BIT7) == _BIT7)
		{
			// clear int_vs
			rtd_outl(SB2_CPU_INT_reg, _BIT7);
			break;
		}
		count_down--;
	}

	if (count_down == 0) {
		printf("[BUG!!!] scpu exit wait int_vs loop because of count_down = 0.\n");
	}

	printf("*");

	// check vcpu1 has been finished calibration.
	regValue = rtd_inl(REG_DDR_CAL_FLAG_reg);
	if (regValue & _BIT1 != _BIT1) {
		printf("[BUG!!!][BUG!!!] scpu get int_vs but calibration was still running.\n");
	}
	else {
		printf("*");
	}

	// prevent that v1/v2 were still in sram region
	mdelay(1);

	// disable DI memshare
	disable_ccdinr_memshare();

	// disable int_vs
	rtd_outl(SB2_CPU_INT_EN_reg, _BIT7);
#endif
}

/*
 * clock enable api
 */
void enable_clock(uint reg_reset, uint mask_reset, uint reg_clock, uint mask_clock)
{
	// clk = 0
	rtd_outl(reg_clock, rtd_inl(reg_clock) & (~mask_clock));

	// rst = 0
	rtd_outl(reg_reset, rtd_inl(reg_reset) & (~mask_reset));

	// wait
	udelay(10);

	// rst = 1
	rtd_outl(reg_reset, rtd_inl(reg_reset) | mask_reset);

	// wait
	udelay(10);

	// clk = 1
	rtd_outl(reg_clock, rtd_inl(reg_clock) | mask_clock);
}

/*
 * Enable essential clock domains, modules and
 * do some additional special settings needed
 */
int clock_init(void)
{
	//enable DCSYS error command detection
	rtd_outl(DC_EC_ADDCMD_HI_VADDR, 0x0);
	rtd_outl(DC_EC_ADDCMD_LO_VADDR, 0x0);
	rtd_outl(DC_EC_CTRL_VADDR, _BIT3 | _BIT2 | _BIT1 | _BIT0);
	rtd_outl(DC_RD_TAG_CHECK_VADDR, _BIT1 | _BIT0);

	// disable write merge
	//rtd_outl(DC_EXP_LANE_CTRL_VADDR, 0x1);

	// enable rbus timeout
	//rtd_outl(SB2_INV_INT_EN_VADDR, _BIT5 | _BIT4 | _BIT0);

	return 0;
}
