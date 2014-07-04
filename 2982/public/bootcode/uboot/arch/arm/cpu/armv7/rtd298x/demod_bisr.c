/*****************************************************************************
* Direct Test Name:      acpu_case
*
* Author:         R3366
* Date:           Tue Apr 10 16:13:58 CST 2012
* Description:
*
*       Note:
*
*       Copyright (C) 2004 Realtek Inc. All Right Reserved.
*
    1) Set Pin Mux
    2) Set I2C1 send command to Demod
    3) Demod 0xe40e write 0x1
    4) Demod 0xc017 write 0x1 , shotern drf bist time
    5) Demod 0xc018 write 0x1, shotern drf bist time
    6) Demod 0xc001 write 0x1, Release reg soft rst
    7) Demod 0xc016 write 0x1, Release reg bisr rst
    8) Demod 0xc016 write 0x1, Release reg bisr rst
    9) Wait for Demod 0xc83e bit4 = 1, // 0xc83e {3'b0, dmbt_bisr_done_all, ldpc_bisr_done, outer_bisr_done[1:0], inrx_bisr_done}
    10) Check Demod 0xc833 = 0x0, // 0xc833 {1'b0, ldpc_bisr_fail,outer_bisr_fail[1:0],inrx_bisr_fail[3:0]}
    11) Demod 0xc01a write 0x7, Hold BISR Remap
*****************************************************************************/

#include <common.h>
#include <asm/armv7.h>
#include <asm/sizes.h>
#include <config.h>
#include <asm/errno.h>
#include <asm/io.h>
#include <asm/arch/rbus/crt_sys_reg.h>
#include <asm/arch/rbus/mis_reg.h>

//void diag_pass();
//void diag_fail();

// Word Access - timeout after 10ms
#define WAIT_FUNC(addr,mask,value) \
        iMaxCount = 100; \
        while (iMaxCount--) { \
        	if ((rtd_inl(addr) & mask) == value) { \
        		break; \
			} \
			udelay(100); \
		} \

#define IFADC_ADC2X_POW_reg 0xb8033080


/* main needs to be the first program */
/* argc and argv are not allowed */

int rtk_demod_bisr( void )
{
#ifdef ENABLE_DEMOD_BISR
	int reg_data, tmp_data;
	unsigned int iMaxCount;
	unsigned int iMaxCount2;

	printf("DEMOD: BISR testing ....\n");

	//pll setting
//	rtd_outl(0xb80004f8, 0xf);
	rtd_outl(IFADC_ADC2X_POW_reg, 0x01111111); // IFADC: ADC2X_POW

	rtd_maskl(SYS_SOFT_RESET2_reg, ~(_BIT12), _BIT12); // SYS_SOFT_RESET2, bit12:RSTN_DTV_DEMOD=1
	rtd_maskl(SYS_GROUP1_CK_EN_reg, ~(_BIT11), _BIT11); // SYS_GROUP1_CK_EN, bit11:CLKEN_DTV_DEMOD=1
	rtd_maskl(SYS_TP_DEMOD_CTRL_reg, ~(_BIT4), 0); // SYS_TP_DEMOD_CTRL, bit4:demod_i2c_saddr=0

	printf("DEMOD: Finish BISR testing (OK)\n");
#endif
  	return 0;
}

