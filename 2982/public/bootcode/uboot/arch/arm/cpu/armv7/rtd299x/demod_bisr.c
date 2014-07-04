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
#include <asm/arch/rbus/crt_reg.h>
#include <asm/arch/rbus/misc_reg.h>

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
	int reg_data, tmp_data;
	unsigned int iMaxCount;
	unsigned int iMaxCount2;

	printf("DEMOD: BISR testing ....\n");

	//pll setting
//	rtd_outl(0xb80004f8, 0xf);
	rtd_outl(IFADC_ADC2X_POW_reg, 0x01111111); // IFADC: ADC2X_POW

	/* ========== Pin MUX ========== */
	rtd_maskl(SYS_SRST2_reg, ~(_BIT11), _BIT11); // SYS_SRST2, bit11:RSTN_DTV_DEMOD=1
	rtd_maskl(SYS_CLKEN2_reg, ~(_BIT11), _BIT11); // SYS_CLKEN2, bit11:CLKEN_DTV_DEMOD=1
	rtd_maskl(SYS_CLKDIV_reg, ~(_BIT3), 0); // SYS_CLKDIV_reg, bit3:DEMOD_I2C_SADDR_SEL=0

	/* ========== Configuration MISC I2C0 ========== */
	rtd_outl(IC1_ENABLE_reg,      0x00000000); // Diable MISC I2C0
	rtd_outl(IC1_INTR_MASK_reg,   0x00000000); // MASK all the interrupts
	rtd_outl(IC1_TAR_reg,         0x00000012); // Target address, & Set 7 bit address mode
	rtd_outl(IC1_CON_reg,         0x00000025); // 7 bit address mode, slave_en, full speed mode, restart_en
	rtd_outl(IC1_SAR_reg,         0x00000055); // Slave address
	rtd_outl(IC1_HS_MADDR_reg,    0x00000002); // HS Master Mode Code Address
	rtd_outl(IC1_SS_SCL_HCNT_reg, 0x00000060); // Standard Speed I2C Clock SCL High Count
	rtd_outl(IC1_SS_SCL_LCNT_reg, 0x000000B0); // Standard Speed I2C Clock SCL Low Count
	rtd_outl(IC1_FS_SCL_HCNT_reg, 0x0000001A); // Full Speed I2C Clock SCL High Count
	rtd_outl(IC1_FS_SCL_LCNT_reg, 0x00000030); // Full Speed I2C Clock SCL Low Count
//	rtd_outl(IC1_HS_SCL_HCNT_reg, 0x00000020); // High Speed I2C Clock SCL High Count
//	rtd_outl(IC1_HS_SCL_LCNT_reg, 0x00000026); // High Speed I2C Clock SCL Low Count
	rtd_outl(IC1_TX_TL_reg,       0x00000000); // TX FIFO threshold level
	rtd_outl(IC1_RX_TL_reg,       0x00000002); // RX FIFO threshold level
	rtd_outl(IC1_ENABLE_reg,      0x00000001); // Enable MISC I2C0

	//rtd_inl(IC1_COMP_PARAM_1_reg); // I2C0 Component Parameter Register 1

	/* ========== MISC I2C0 : Write Addr:0xe40e, Data:0x01 ========== */
	rtd_outl(IC1_DATA_CMD_reg, 0x000000e4); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x0000000e); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	/* ========== MISC I2C0 : Write Addr:0xc017, Data:0x01 ========== */
	//notice!! shotern drf bist time
	rtd_outl(IC1_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000017); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	/* ========== MISC I2C0 : Write Addr:0xc018, Data:0x01 ========== */
	//notice!! shotern drf bist time
	rtd_outl(IC1_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000018); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000200); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	/* ========== MISC I2C0 : Write Addr:0xc001, Data:0x01 ========== */
	//Release reg soft rst
	rtd_outl(IC1_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000001); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	/* ========== MISC I2C0 : Write Addr:0xc016, Data:0x01 ========== */
	//Release reg bisr rst
	rtd_outl(IC1_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000016); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	/* ========== MISC I2C0 : Write Addr:0xc016, Data:0x01 ========== */
	//Release reg bisr rst
	rtd_outl(IC1_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000016); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000201); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	/* ========== MISC I2C0 : Read Addr:0xc83e (Check BISR Done) ========== */
	// 0xc83e {3'b0, dmbt_bisr_done_all, ldpc_bisr_done, outer_bisr_done[1:0], inrx_bisr_done}
	iMaxCount2 = 100; // timeout - 100 x (10ms+10ms+0.1ms) = about 2 seconds
	while (iMaxCount2--) {
		rtd_outl(IC1_DATA_CMD_reg, 0x000000c8); // DATA_CMD
		rtd_outl(IC1_DATA_CMD_reg, 0x0000023e); // DATA_CMD & Send Stop

		WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
		rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

		rtd_outl(IC1_DATA_CMD_reg, 0x00000300); // DATA_CMD (Set to Read & Send Stop)

		WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
		rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

		reg_data = rtd_inl(IC1_DATA_CMD_reg); // Read DATA_CMD Value
		tmp_data = reg_data;
		if ((tmp_data & 0x10) == 0x10) { // check dmbt_bisr_done_all
			break;
		}
		udelay(100);
	}

	/* ========== MISC I2C0 : Read Addr:0xc833 (Check ) ========== */
	// 0xc833 {1'b0, ldpc_bisr_fail,outer_bisr_fail[1:0],inrx_bisr_fail[3:0]}
	rtd_outl(IC1_DATA_CMD_reg, 0x000000c8); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000233); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	rtd_outl(IC1_DATA_CMD_reg, 0x00000300); // DATA_CMD (Set to Read & Send Stop)

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	reg_data = rtd_inl(IC1_DATA_CMD_reg); // Read DATA_CMD Value
	tmp_data = reg_data;
	if ((tmp_data & 0xff) != 0x0) {
		printf("DEMOD: Finish BISR testing (FAIL)\n");
		return 0;
	}

	// ===========================================================================
	// HOLD BISR

	/* ========== MISC I2C0 : Write Addr:0xc01a, Data:0x07 ========== */
	// Set bit2~bit0
	rtd_outl(IC1_DATA_CMD_reg, 0x000000c0); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x0000001a); // DATA_CMD
	rtd_outl(IC1_DATA_CMD_reg, 0x00000207); // DATA_CMD & Send Stop

	WAIT_FUNC(IC1_RAW_INTR_STAT_reg,0x00000200,0x00000200); // Wait MISC I2C0 transfer done, Check STOP_DET=1
	rtd_inl(IC1_CLR_STOP_DET_reg); // Clear STOP_DET

	printf("DEMOD: Finish BISR testing (OK)\n");

  	return 0;
}

