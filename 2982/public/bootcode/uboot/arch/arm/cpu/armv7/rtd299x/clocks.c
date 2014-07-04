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
	unsigned int iBISROldReg = 0;
	unsigned int iBISRFlag = 0;
	unsigned int iMaxCount = 100;

#ifdef ENABLE_VCPU_BISR
	mdelay(10);
	printf("%s %d hold_hw_semaphore\n", __FUNCTION__, __LINE__);
	hold_hw_semaphore();
#endif

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

#ifdef ENABLE_VCPU_BISR
#if 0
	mdelay(10);
	//printf("\n");
	//printf("-------------------------------------------- mask flasg\n");
	//printf("r mask_reset  : 0x%08x\n", mask_reset );
	//printf("r mask_clock  : 0x%08x\n", mask_clock );
	//printf("-------------------------------------------- current status\n");
	//printf("r Reg(0x%08x) : 0x%08x  // reg_reset\n", reg_reset, rtd_inl(reg_reset) );
	//printf("r Reg(0x%08x) : 0x%08x  // reg_clock\n", reg_clock, rtd_inl(reg_clock) );
	//printf("r Reg(0xb8000f08) : 0x%08x\n", rtd_inl(0xb8000f08) );
	//printf("r Reg(0xb8000f18) : 0x%08x\n", rtd_inl(0xb8000f18) );
	//printf("r Reg(0xb8000f28) : 0x%08x\n", rtd_inl(0xb8000f28) );

	if( ( mask_clock & (_BIT3 | _BIT4 | _BIT5) ) == (_BIT3 | _BIT4 | _BIT5) ) {
		//printf("VCPU1: BISR testing ....\n");
		iBISRFlag |= 0x02;
	}
	if( ( mask_clock & (_BIT7 | _BIT8 | _BIT9) ) == (_BIT7 | _BIT8 | _BIT9) ) {
		//printf("VCPU2: BISR testing ....\n");
		iBISRFlag |= 0x01;
	}

	if( iBISRFlag ) {
		iBISROldReg = rtd_inl(0xb8000f08);
		//printf("r Reg(0xb8000f08) : 0x%08x\n", rtd_inl(0xb8000f08) );
		//printf("r Reg(0xb8000f28) : 0x%08x\n", rtd_inl(0xb8000f28) );
		//printf("w Reg(0xb8000f08) = 0x%08x\n", (iBISROldReg|iBISRFlag) );
		rtd_outl( 0xb8000f08, (iBISROldReg|iBISRFlag) );
		mdelay(10);
		//printf("r Reg(0xb8000f08) : 0x%08x\n", rtd_inl(0xb8000f08) );
		//rtd_outl( 0xb8000f08, (iBISROldReg) );
		//udelay(100);
		//rtd_outl( 0xb8000f08, (iBISROldReg|iBISRFlag) );
		//udelay(100);
		while( (rtd_inl(0xb8000f28)&iBISRFlag) != iBISRFlag ) {
			//printf("r Reg(0xb8000f28) : 0x%08x\n", rtd_inl(0xb8000f28) );
			iMaxCount--;
			mdelay(100);
			if( iMaxCount == 0 ) {
				break;
			}

		}
		//printf("r Reg(0xb8000f28) : 0x%08x\n", rtd_inl(0xb8000f28) );
		iBISROldReg = rtd_inl(0xb8000f18);
		rtd_outl(0xb8000f18, (iBISRFlag|iBISROldReg));
		printf("\n\nVCPUx : Finish BISR testing %s\n\n", (iMaxCount ? "done" : "fail" ) );
	}
	mdelay(10);
#endif
#if 1
	mdelay(10);
	if( ( mask_clock & (_BIT3 | _BIT4 | _BIT5) ) == (_BIT3 | _BIT4 | _BIT5) ) {
		printf("\nVCPU1: BISR testing ....\n");
		iBISRFlag = 0x02;
		iBISROldReg = rtd_inl(0xb8000f08);
		rtd_outl( 0xb8000f08, (iBISROldReg|iBISRFlag) );
		udelay(100);
		while( (rtd_inl(0xb8000f28)&iBISRFlag) != iBISRFlag ) {
			iMaxCount--;
			udelay(100);
			if( iMaxCount == 0 ) {
				break;
			}

		}
		iBISROldReg = rtd_inl(0xb8000f18);
		rtd_outl(0xb8000f18, (iBISRFlag|iBISROldReg));
		printf("VCPU1: Finish BISR testing %s\n\n", (iMaxCount ? "done" : "fail" ) );
	}

	iMaxCount = 100;
	if( ( mask_clock & (_BIT7 | _BIT8 | _BIT9) ) == (_BIT7 | _BIT8 | _BIT9) ) {
		printf("\nVCPU2: BISR testing ....\n");
		iBISRFlag = 0x01;
		iBISROldReg = rtd_inl(0xb8000f08);
		rtd_outl( 0xb8000f08, (iBISROldReg|iBISRFlag) );
		udelay(100);
		while( (rtd_inl(0xb8000f28)&iBISRFlag) != iBISRFlag ) {
			iMaxCount--;
			udelay(100);
			if( iMaxCount == 0 ) {
				break;
			}

		}
		iBISROldReg = rtd_inl(0xb8000f18);
		rtd_outl(0xb8000f18, (iBISRFlag|iBISROldReg));
		printf("VCPU2: Finish BISR testing %s\n\n", (iMaxCount ? "done" : "fail" ) );
	}
	mdelay(10);
#endif
#endif
}

static int rtc_init(void)
{
	uint rtcstop_regValue;

	rtcstop_regValue = rtd_inl(RTCSTOP_reg);

	// check RTC status
	if (RTCSTOP_get_RTCSTOP(rtcstop_regValue) == 0x0) // status: running
	{
		;	// RTC: Already running ... do nothing ...
	}
	else // status: stopped
	{
		// initialize RTC
		rtd_outl(RTCACR_reg, RTCACR_BC(0x0) | RTCACR_CLKSEL(0x0)); // clk select

		// reset time info
		rtd_outl(RTCSEC_reg, RTCSEC_RTCSEC(0x0)); // sec
		rtd_outl(RTCMIN_reg, RTCMIN_RTCMIN(0x0)); // min
		rtd_outl(RTCHR_reg, RTCHR_RTCHR(0x0)); // hour
		rtd_outl(RTCDATE1_reg, RTCDATE1_RTCDATE1(0x0)); // date LSB
		rtd_outl(RTCDATE2_reg, RTCDATE2_RTCDATE2(0x0)); // date MSB

		// enable RTC
		rtd_outl(RTCEN_reg, RTCEN_RTCEN(0x5A));

		// check RTC status
		rtcstop_regValue = rtd_inl(RTCSTOP_reg);
		if (RTCSTOP_get_RTCSTOP(rtcstop_regValue) == 0x0)
		{
			;	// RTC: Running
		}
		else
		{
			;	// RTC: Stop
		}
	}

	return 0;
}

/*
 * Enable essential clock domains, modules and
 * do some additional special settings needed
 */
int clock_init(void)
{
#if 1 // patch for SB2 write merge disable
	rtd_outl(0xb801a018, 0x000c2cc0);
#endif

# if 1 // add by cfyeh +++
	//rtd_outl(0xb8000100,0xffffffff);
	rtd_outl(0xb8000104,0xffffffff);
	rtd_outl(0xb8000108,0xffffffff);
	rtd_outl(0xb800010c,0xffffffff);

	//rtd_outl(0xb8000110,0xffffffff);
	rtd_outl(0xb8000114,0xffffffff);
	// default disable uart1/2/3
	rtd_outl(0xb8000118,0xfffffe3f);
	//rtd_outl(0xb800011c,0xffffffff);

	rtd_outl(0xb8060040,0xffffffff);
	rtd_outl(0xb80004a4,0x53);

	//HDMI band gap
	//bit25
	rtd_outl(0xb800da40,0x03000000);

	//UTMI reset
	rtd_outl(0xb8013008,0xf);
	rtd_outl(0xb8013008,0x0);

	//USB3_ANA_PHY
	rtd_outl(0xb80130c4,0xe);
	//USB2_POW_gate
	rtd_outl(0xb80130c8,0xf);

	//2. set the USB2PHYCFG[6]=0=Suspend USB2.0 HS/FS/LS PHY (SusPHY)
	rtd_outl(0xb8058200,0x00001408);
	rtd_outl(0xb8058204,0x00001408);
	rtd_outl(0xb8058208,0x00001408);
	rtd_outl(0xb805820c,0x00001408);
#endif // add by cfyeh ---

#if 1 // default disable demod clock
	rtd_maskl(0xb8000118, ~(_BIT11), 0);
//	rtd_maskl(0xb8000214, ~(_BIT3), 0); // Internal address is 0x24 (default)
//	rtd_maskl(0xb8000214, ~(_BIT3), _BIT3); // if conflict with external i2c address (0x24), set internal as 0x26
#endif

	// watchdog reset cannot reset thess following registers, so we do the clear here
	rtd_outl(ISO_ISR_reg, 0xffffffff);
	rtd_outl(UMSK_ISR_GP_ASSERT_reg, 0xffffffff);
	rtd_outl(UMSK_ISR_GP_ASSERT_1, 0xffffffff);
	rtd_outl(UMSK_ISR_GP_DEASSERT, 0xffffffff);
	rtd_outl(UMSK_ISR_GP_DEASSERT_1, 0xffffffff);
	rtd_outl(ISO_SCPU_INT_EN_reg, ~_BIT0);

	// enable RTC
	rtc_init();

	return 0;
}
