/****************************************************************************************
* Program Name:
* Author:
* Date:
* Description:
* Copyright (C) 2013 Realtek Inc. All Right Reserved.
****************************************************************************************/

/************************************************************************
 *  Include files
 ************************************************************************/
//#include <stdio.h>
//#include <string.h>
#include "util.h"
#include "loader.h"
#include "UART.h"
#include "NOCS.h"
#include "reset_def_sirius.h"
#include "error_type.h"
//#include "autoconf_hw_setting.h"

/************************************************************************
 *  Definitions
 ************************************************************************/

/************************************************************************
 *  External variables
 ************************************************************************/
extern NOCS_Params *rom_params;

/************************************************************************
 *  Public variables
 ************************************************************************/

/************************************************************************
 *  Static variables
 ************************************************************************/

/************************************************************************
 *  External function prototype
 ************************************************************************/
extern int parse_hw_setting_c(unsigned int *ptr, const unsigned int limit, unsigned int *parsed_bytes, const char skip);
extern int get_hwsetting_spi(unsigned int dst_addr,  int size);
extern int get_hwsetting_spi_n(unsigned int dst_addr,  int size);
extern int get_hwsetting_nand(unsigned int dst_addr,  int size);
extern int get_hwsetting_emmc(unsigned int dst_addr,  int size);


/************************************************************************
 *  Public function prototype
 ************************************************************************/

/************************************************************************
 *  Static function prototype
 ************************************************************************/
//static int get_options(int argc, char **argv);
//static void show_help(void);

/************************************************************************
 *  Function body
 ************************************************************************/

#if defined(ENV_SIMULATION)
void init_hwsetting_simulation(void)
{
	REG32(0xb8000244)|= 0x00004400;
	REG32(0xb8000000) = 0x2f800003;
	REG32(0xb800000c) = 0x01bc0001;
	REG32(0xb80002c0) = 0x000000ff;
	REG32(0xb80002c4) = 0xffc13018;
	REG32(0xb80002c8) = 0x00000000;
	REG32(0xb80002cc) = 0x00000000;
	REG32(0xb80002d0) = 0x00000019;
	REG32(0xb80002d4) = 0x00000000;
	REG32(0xb80002d8) = 0x00000000;
	REG32(0xb80002dc) = 0x00000001;
	REG32(0xb80002c0) = 0x0003cfcf;
	REG32(0xb8008910) = 0x00000f7e;
	REG32(0xb8008910) = 0x00000ffe;
	REG32(0xb800890c) = 0x00000034;
	REG32(0xb8008004) = 0x00620000;
	REG32(0xb8008690) = 0x00000000;
	REG32(0xb8008694) = 0x20000000;
	REG32(0xb8008e00) = 0x00000040;
	REG32(0xb801e544) = 0x00000017;
	REG32(0xb801e548) = 0x00000017;
	REG32(0xb801e54c) = 0x00000017;
	REG32(0xb801e550) = 0x00000017;
	REG32(0xb801e554) = 0x0001000e;
	REG32(0xb801e558) = 0x00000fff;
	REG32(0xb801e6a0) = 0x10000000;
	REG32(0xb8008800) = 0x001cb811;
	REG32(0xb8008804) = 0x05100d0d;
	REG32(0xb8008808) = 0x02040508;
	REG32(0xb800880c) = 0x2001707a;
	REG32(0xb8008810) = 0x03030a02;
	REG32(0xb8008814) = 0x00200400;
	REG32(0xb8008818) = 0x00240080;
	REG32(0xb8008844) = 0x00000d71;
	REG32(0xb8008838) = 0x07fcc3cf;
	REG32(0xb8008838) = 0x03fcc3cf;
	REG32(0xb8008820) = 0x00003fff;
	REG32(0xb8008824) = 0x00fa4700;
	REG32(0xb8008824) = 0x007a4700;
	REG32(0xb8008848) = 0x00000018;
	REG32(0xb8008840) = 0x30000000;
	REG32(0xb8008840) = 0x0a000000;
	REG32(0xb8008840) = 0x0000c003;
	REG32(0xb8008840) = 0x03000000;
	REG32(0xb8008840) = 0x0c000000;
	REG32(0xb8008840) = 0x00200000;
	REG32(0xb8008850) = 0x00000000;
	REG32(0xb800884c) = 0x00000030;
	REG32(0xb8008944) = 0x00000229;
	REG32(0xb8008954) = 0x00000011;
	REG32(0xb8008904) = 0x00002880;
	// enable SCPU PLL
	REG32(0xb8000104) = 0x00000004;
	REG32(0xb8000104) = 0x00000005;
	REG32(0xb8000104) = 0x00000007;
	REG32(0xb8000104) = 0x00000003;

}
#endif

#if defined(ENV_FPGA)
void init_hwsetting_fpga(void)
{
	// DDR
	REG32(0xb8008800) = 0x000F7509; //

	REG32(0xb8008004) = 0x00420808; // for ddr3 mapping, 16bit

	REG32(0xb8008804) = 0x03050411;
	REG32(0xb8008808) = 0x04040306;
	REG32(0xb800880c) = 0x3f00504d;
	REG32(0xb8008810) = 0x03030a02;
	REG32(0xb8008814) = 0x00200400;
	REG32(0xb8008818) = 0x00240080;
	REG32(0xb8008844) = 0x00010711;
	REG32(0xb8008838) = 0x07000000;
	REG32(0xb8008838) = 0x03000600;
	REG32(0xb8008824) = 0x00fa4700;
	REG32(0xb8008824) = 0x007a4700;
	REG32(0xb8008848) = 0x00000000;
	REG32(0xb8008840) = 0x30000000;
	REG32(0xb8008840) = 0x0a000000;
	REG32(0xb8008840) = 0x0000c003;
	REG32(0xb8008840) = 0x03000000;
	REG32(0xb8008840) = 0x0c000000;
	REG32(0xb8008840) = 0x00200000;
	REG32(0xb8008850) = 0x00000000;
	REG32(0xb800894c) = 0x00000030;
}
#endif

void InitTimer(unsigned int dwInit)
{
#if 0 //def ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

	//Disable Interrupt
	REG32(0xb801b664) = 0;

	//Disable Timer
	REG32(0xb801b644) = 0;

	//Set The Initial Value
	REG32(0xb801b604) = dwInit;

	//Enable Timer Mode
	REG32(0xb801b644) = 0xC0000000;

	// Clear Interrupt Pending (must after enable)
	REG32(0xb801b008) = 1 << (7);
}

bool SystemTimeout()
{
#if 0 //def ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
#endif

	bool	bIoStatus = FALSE;
	UINT32 	bitmask = 1 << (7);

	if(REG32(0xb801b008) & bitmask)
	{
		bIoStatus = TRUE;
	}

	return bIoStatus;
}

void arom_mdelay(unsigned int dwMiniSecond)
{
#define TIMERINFO_MSEC      1000000/37

	InitTimer(dwMiniSecond*TIMERINFO_MSEC);
	//Wait for Interrupt Pending Status
	while(SystemTimeout() == FALSE);
}

void arom_mask_register(const unsigned int reg_addr, const unsigned int AND_filter, 
	const unsigned int OR_filter)
{
#if 0 //def ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
	prints("\n");
#endif

	REG32(reg_addr) = (REG32(reg_addr) & AND_filter) | OR_filter;
	arom_mdelay(20);

}

int init_hwsetting(void)
{
	int res = 0;
/*
#if defined(ENV_FPGA)
//	init_hwsetting_fpga();
//	return 0;
#elif defined(ENV_SIMULATION)
	init_hwsetting_simulation();
	return 0;
#endif
*/
	rtd_outl(0xb8062300,'H');
	arom_mdelay(100);
	rtd_outl(0xb8062300,'a');

	 //-------- HDMI bandgap power---------
    arom_mask_register(0xb800000c, 0xfffffffd, 0x00000002);// enable HDMI clock
    arom_mask_register(0xb800000c, 0xfffffffd, 0x00000000);// disable HDMI clock
    arom_mask_register(0xb8000008, 0xfffdffff, 0x00000000);// hold HDMI reset
    arom_mask_register(0xb8000008, 0xfffdffff, 0x00020000);// release HDMI reset
    arom_mdelay(0x1);
    arom_mask_register(0xb800000c, 0xfffffffd, 0x00000002);// enable HDMI clock
    arom_mask_register(0xb8007b40, 0xfdffffff, 0x02000000);       //HDMI bandgap power 1:on 0:off
    arom_mdelay(0x1);
    
	//-------- IFD MBIAS ----------
	arom_mask_register(0xb8000014, 0xfffeffff, 0x00010000);		 // enable IFADC clock
	arom_mask_register(0xb8000014, 0xfffeffff, 0x00000000);		 // disable IFADC clock
	arom_mask_register(0xb8000008, 0xffffffdf, 0x00000000);		 // hold IFADC reset
	arom_mask_register(0xb8000008, 0xffffffdf, 0x00000020);		 // release IFADC reset
	arom_mdelay(0x1);
	arom_mask_register(0xb8000014, 0xfffeffff, 0x00010000);		 // enable IFADC clock
	arom_mask_register(0xb8033110, 0xfffffeff, 0x00000100);		 // IFD MBIAS power on
	arom_mdelay(0x1);


	rtd_inl(0xb80002e0); //--> 0x00000000;
	//rtd_outl(0x180002DC,0x000000ff);//4.reg_dpi_pll_dum[0] go HIGH (PLL LDO reset)//4.LDO reset--400~750MHz,800~1100MHz
	//arom_mdelay(300);
	rtd_outl(0xb80002dc, 0x000000ff);		//4.reg_dpi_pll_dum[0] go HIGH (PLL LDO reset)//4.LDO reset--1400~1700MHz
 arom_mdelay(0x100);
	//rtd_outl(0xb80102e4, 0x00000000);//ckref_sel
	 //=========== PLL Phase interpolation (PI) setting ===================//
	
	//rtd_outl(0xb80002d4,0x03e00000) //854MHz
	//rtd_outl(0xb80002d4,0x03b00000) //800MHz
rtd_outl(0xb80002d4,0x03600000); //742MHz
	//rtd_outl(0xb80002d4,0x02600000)//540MHz
	//rtd_outl(0xb80002d4, 0x01f00000);//445.5MHz
	//rtd_outl(0xb80002d4, 0x01a00000);//3XX
	//rtd_outl(0xb80002d4, 0x01f00000);//445.5MHz
	//rtd_outl(0xb80002d4, 0x01f00000);//445.5MHz

	 //PI_phase
 rtd_outl(0xb80002c8, 0x38380535);       //DQS0,DQS1,cmd,ck
	 rtd_outl(0xb80002cc, 0x00000000);		 // xx,ck_1,,DQS3,DQS2
	 rtd_outl(0xb80002d0, 0x00000879);

	 //PI_RL_BIAS
	 //rtd_outl(0xb80002c4,0xff98ca9e);//clok;200-375MHz,VCO;400~750MHz
	 //rtd_outl(0xb80002c4,0xffcaca9f);//clock;400~550MHz,VCO;800~1100MHz
	 rtd_outl(0xb80002c4, 0xffdaca8e);		 //clock;700~850MHz,VCO;1400~1700MHz

	 //
	 //===================================PLL initial=================================================
	arom_mask_register(0xb8000000, 0xfe7fffff, 0x01800000); 	  //DCU&DC_phy reset
	 arom_mdelay(0x5);
	 arom_mask_register(0xb800000c, 0xfffbffff, 0x00040000); 	  //DCU&DC_phy_ck_en on
//rtd_outl(0xb800000c, 0xffffffff);       //DCU&DC_phy_ck_en on
rtd_outl(0xb80002c0, 0x00d000ff);       //c) enable reg_dpi_mck_clk_en
	 //rtd_outl(0xb80002C0,0x200001ff); //c) enable reg_dpi_mck_clk_oe 
	 //rtd_outl(0xb80002C0,0x200003ff); //c) enable reg_dpi_mck_clk_oe 
	 //rtd_outl(0xb80002C0,0x200007ff); //c) enable reg_dpi_mck_clk_oe 
	 //rtd_outl(0xb80002C0,0x20000fff); //c) enable reg_dpi_mck_clk_oe 
	 //rtd_outl(0xb80002C0,0x20001fff); //c) enable reg_dpi_mck_clk_oe 
	 //rtd_outl(0xb80002C0,0x20003fff); //c) enable reg_dpi_mck_clk_oe 
rtd_outl(0xb80002c0, 0x00d07fff);       //c) enable reg_dpi_mck_clk_oe
	

	// b80002c0 is right is ok
rtd_outl(0xb801E524,0x0000003c); //[5]:[2]-->  dqs_mux_sel_WRLVL_CTRL-->DPI_spec
	rtd_outl(0xb801E6A0,0x10000000); //[27]:[24]-->_dqs_mux_sel_BIST_2TO1-->DPI_spec
	//rtd_outl(0xb801E524,0x00000000);
//rtd_outl(0xb801E524,0x0000003c); //[5]:[2]-->  dqs_mux_sel_WRLVL_CTRL-->DPI_spec
	//rtd_inl(0xb801e524); 
	rtd_inl(0xb80002e0);
	arom_mdelay(0x100);
	//===================================PLL initial end ============================================
	
	//============================ DC PAD/ZQ/TX Delay Chain Setting ===================================================//
	//**************************zq********************************//
	//====0x1801_E5D0?
rtd_outl(0xb801e600,0x00000000);//ZQ pad PD[4]:0
rtd_outl(0xb801e51c,0x04010000);//R480 calibration enable
arom_mdelay(0x5);
rtd_inl(0xb801e688);//?wait [0]=1,[1]~[5]:calibartion status for R480 calibration done
arom_mdelay(0x5);
	
rtd_outl(0xb801e51c,0x0C00067f);//set zq result to [30:28]=0,zprog=[13:0]ocd&odt,[27]:1=cal done update-->OCD:34,ODT:60
arom_mdelay(0x5);
rtd_outl(0xb801e51c,0x0d00067f);//cal start--->OCD:34,ODT:60
arom_mdelay(0x5);
rtd_inl(0xb801e520);//wait[31]=1,wait calibration done
arom_mdelay(0x5);
rtd_outl(0xb801e51c,0x0C00067f);
rtd_outl(0xb801e51c,0x1C000aff);//set zq result to [30:28]=0,zprog=[13:0]ocd&odt,[27]:1=cal done update-->OCD:34,ODT:60
arom_mdelay(0x5);
rtd_outl(0xb801e51c,0x1d000aff);//cal start--->OCD:34,ODT:60
arom_mdelay(0x5);
rtd_inl(0xb801e520);//wait[31]=1,wait calibration done
arom_mdelay(0x5);
rtd_outl(0xb801e51c,0x1C000aff);
//=========record the step for ODT==================//

//=====ODT,OCD sel===================//
//PAD:DQS,DQ,ck,ck&cmd select for several odt&ocd
rtd_outl(0xb801e564,0x00000000);//DQ_ODTN_sel
rtd_outl(0xb801e5D4,0x00000000);//DQ_OCDN_sel
//rtd_outl(0xb801e5D8,0x00000000);//DQSP_ODT_sel//pupd3 on,unbalance DQS 
//rtd_outl(0xb801e5Dc,0x00000000);//DQSN_ODT_sel//pupd3 on,unbalance DQS
rtd_outl(0xb801e5D8,0x00110011);//DQSP_ODT_sel//pupd3 on,unbalance DQS 
rtd_outl(0xb801e5Dc,0x11001100);//DQSN_ODT_sel//pupd3 on,unbalance DQS
rtd_inl(0xb801e5d8);
rtd_inl(0xb801e5dc);
rtd_outl(0xb801e5F0,0x00000000);//DQS_OCD_sel
rtd_outl(0xb801e5F4,0x00000000);//ADR_OCD_sel
rtd_outl(0xb801e5F8,0x00000000);//CK_OCD_sel
rtd_outl(0xb801e6cc,0x00000000);//CS_1_OCDP,CS_1_OCDN,CS_OCDP,CS_OCDN

rtd_outl(0xb801e600,0x00000010);//ZQ pad PD[4]:1
	//==============add/cmd OE===============//
	//cmd&add
	rtd_outl(0xb801e510,0x3ef);//cmd&add_OE
	rtd_outl(0xb801e514,0x0);//PAD_IDDQ
	//==============OE end===================//
	
	//========Tx delay chain==========//
	//cmd&add
	rtd_outl(0xb801e500,0x44444444);//dly_a7-a0
	rtd_outl(0xb801e504,0x44444444);//dly_a15-a8
	rtd_outl(0xb801e508,0x00044400);//dly_ba2-ba0
	rtd_outl(0xb801e50c,0x44444444);//dly_csn_1,csn,odt,we_n,cas_n,ras_n,cke
	//Data delay chain
	rtd_outl(0xb801e530,0x44444444);//dly_DQ7_DQ0
	rtd_outl(0xb801e540,0x44444444);//dly_DQS3_DM3
	rtd_outl(0xb801e680,0x00004444);//dqs3-dqs0,OE_dly:dqs_OE???
	rtd_outl(0xb801E61C,0x00000003);//update tx dly

	//========Tx delay chain end==========//
	
	
	
	//============================ DC SYS Setting ===================================================//
	// DC 1 SYS Setting
	//w 0xb8008004, 0x006b0000		 // DC1 SYS Setting 2DDR, 1Gb x 2 (256MBytes), bank re-mapping enable
	//rtd_outl(0xb8008004, 0x026b0000); 	  // DC1 SYS Setting 2DDR, 2Gb x 2 (512MBytes), bank re-mapping enable
	//rtd_outl(0xb8008004, 0x086b0000); 	  // DC1 SYS Setting 2DDR, 4Gb x 2 (1GBytes), bank re-mapping enable
	//w 0xb8008004, 0x00620000		 // DC1 SYS Setting 1DDR, 1Gb x 1 (128MBytes), bank re-mapping enable
	//w 0xb8008004, 0x02620000		 // DC1 SYS Setting 1DDR, 2Gb x 1 (256MBytes), bank re-mapping enable
	rtd_outl(0xb8008004, 0x08620000);		// DC1 SYS Setting 1DDR, 4Gb x 1 (512MBytes), bank re-mapping enable
	 
	
	//====================================== DC1 Timing Setting Start =========================================//
	//1333 Setting
	// pupd1 --> TMCL_RD = CL or CL +0.5
	// pupd2 --> TMCL_RD = CL + 1 ~ 1.5
	// 4Gbits for DC1
rtd_outl(0xb800880c, 0x200170C7);  //TMCTRL3: tFAW: 32((32+2)*1.25=42.5)(40ns)/ tREF: 0x17((23+1)*128*1.25=3840)(3.9us/7.8us) / tmRFC:0xc7((122+11)*1.25=262.5)(300ns)
rtd_outl(0xb8008800, 0x001cc819);       //TMCTRL0: tRAS:0x1c((28+2)*1.25 = 37.5)(35ns) / #tCL:0xb(11nCK) / #tCWL:0x8(8nCK) / #tmCLRD:0x1a(26/2=13)(13nCK)
rtd_outl(0xb8008804, 0x060a0a22);       //TMCTRL1: tRRD:0x6(6+2=8)(7.5nCK) / tRP:0xa((10+2)*1.25=15)(13.125ns) / tRCD:0xa((10+2)*1.25=15)(13.125ns) / tRC:0x22((34+6)*1.25 = 50)(48.75ns)
rtd_outl(0xb8008808, 0x0206070a);       //TMCTRL2: TCCD:4(2+2=4)(4nCK) / tRTP:6(6*1.25=7.5)(7.5ns) / tWTR:7((7+1)*1.25=10)(7.5ns) / tWR:0xa((10+2)*1.25=15)(15ns)
rtd_outl(0xb8008810, 0x03030d02);       //TMCTRL4: tAOND:3((3+2)*1.25=6.25)(2ns) / tAOFD:3((3+2)*1.25=6.25)(2ns) / tMMOD(Mode register Set Command cycle time):13(13)max(12nCK, 15ns) / tMMRD(MRS cmd to ODT update delay):2(2+2=4)(4nCK)
	rtd_outl(0xb8008814, 0x00200400);		//TMCTRL5: tMRTW:1(2nCK) / tZQOPER:0x200(512)((256nCK) / tZQINIT:0x400(1024)(512nCK)
	rtd_outl(0xb8008818, 0x00240080);		//TMCTRL6: dqs_lat_sel:1 / dqs_alt:12.5 / tDLLK:0x240(576)(512nCK) / tZQCS:0x80(128)(64nCK)
rtd_outl(0xb8008844, 0x00060d71);       //MOD_REG0,  bit[15:0] for DDR3-1600MHz: #CL11/BC4&BL8/#WR12/AL0, 34/60
rtd_outl(0xb8008848, 0x00000018);       //MOD23_REG for DDR3:Rtt_WR: disable,  #CWL:8,  ASR disable,  dynamic ODT off.
rtd_outl(0xb801E558, 0x00007fff);       //ODT_CTRL_new
	 

	//1600 Setting
	// pupd1 --> TMCL_RD = CL or CL +0.5
	// pupd2 --> TMCL_RD = CL + 1 ~ 1.5
	// 4Gbits for DC1
	//rtd_outl(0xb800880c, 0x200170C7);  //TMCTRL3: tFAW: 32((32+2)*1.25=42.5)(40ns)/ tREF: 0x17((23+1)*128*1.25=3840)(3.9us/7.8us) / tmRFC:0xc7((122+11)*1.25=262.5)(300ns)
	//rtd_outl(0xb8008800, 0x001cc819); 	  //TMCTRL0: tRAS:0x1c((28+2)*1.25 = 37.5)(35ns) / #tCL:0xb(11nCK) / #tCWL:0x8(8nCK) / #tmCLRD:0x1a(26/2=13)(13nCK)
	//rtd_outl(0xb8008804, 0x060a0a22); 	  //TMCTRL1: tRRD:0x6(6+2=8)(7.5nCK) / tRP:0xa((10+2)*1.25=15)(13.125ns) / tRCD:0xa((10+2)*1.25=15)(13.125ns) / tRC:0x22((34+6)*1.25 = 50)(48.75ns)
	//rtd_outl(0xb8008808, 0x0206070a); 	  //TMCTRL2: TCCD:4(2+2=4)(4nCK) / tRTP:6(6*1.25=7.5)(7.5ns) / tWTR:7((7+1)*1.25=10)(7.5ns) / tWR:0xa((10+2)*1.25=15)(15ns)
	//rtd_outl(0xb8008810, 0x03030d02); 	  //TMCTRL4: tAOND:3((3+2)*1.25=6.25)(2ns) / tAOFD:3((3+2)*1.25=6.25)(2ns) / tMMOD(Mode register Set Command cycle time):13(13)max(12nCK, 15ns) / tMMRD(MRS cmd to ODT update delay):2(2+2=4)(4nCK)
	//rtd_outl(0xb8008814, 0x00200400); 	  //TMCTRL5: tMRTW:1(2nCK) / tZQOPER:0x200(512)((256nCK) / tZQINIT:0x400(1024)(512nCK)
	//rtd_outl(0xb8008818, 0x00240080); 	  //TMCTRL6: dqs_lat_sel:1 / dqs_alt:12.5 / tDLLK:0x240(576)(512nCK) / tZQCS:0x80(128)(64nCK)
	//rtd_outl(0xb8008844, 0x00060d71); 	  //MOD_REG0,  bit[15:0] for DDR3-1600MHz: #CL11/BC4&BL8/#WR12/AL0, 34/60
	//rtd_outl(0xb8008848, 0x00000018); 	  //MOD23_REG for DDR3:Rtt_WR: disable,  #CWL:8,  ASR disable,	dynamic ODT off.
	//rtd_outl(0xb801E558, 0x00007fff); 	  //ODT_CTRL_new
	 
	//====================================== DC1 Timing Setting End =========================================//
	rtd_outl(0xb8008f00, 0x00000002);		//enable 2T cmd
	rtd_outl(0xb800882c, 0x00000000);		//DC_MIS
	rtd_outl(0xb8008830, 0x00000000);		//DC_MISa pre_dis,0, lbk_en,disable
	rtd_outl(0xb8008834, 0x10000000);		//DC_MISb tmrc_sel,1: 0: tmrc,tmras+tmrp, 1: tmrc,tmrc (DRAM always let tRAS+tRP,tRC)
	//=======================================================================================================//
	//======================================================PUPU3&4 Setting==================================//
	//==================pupd3 mode==================//
	//rtd_outl(0xb801e618,0x007f2052);//pupd3 mode
	//for pupd3 ZQ calibration
	//ODT unbalance setting-->side effect :duty-----using two ODT setting for DQSP & DQSN ,need measuremet
 
	//read fifo setting:tm_dqs_en+2.5T=tm_rd_fifo  ,tm_dqs=tmcl_rd
	//CL+1T=tm_odt_en
rtd_outl(0xb801e544,0x0000c016);//tm_dqs_en,7.5T-- dqs0                      
rtd_outl(0xb801e548,0x0000c016);//tm_dqs_en,7.5T-- dqs1
rtd_outl(0xb801e54c,0x0000c016);//tm_dqs_en,7.5T-- dqs2   
rtd_outl(0xb801e550,0x0000c016);//tm_dqs_en,7.5T-- dqs3
rtd_outl(0xb801e554,0x0001040f);//tm_rd_fifo=11T //
	//rtd_outl(0xb801e558,0x00000fff);//tm_odt_en:2~13T //«e­±//
	 
	 
	 
	 
	
	//we must follow the Cas latency//
//rtd_outl(0xb801e5d8,0x0);//ODT
//rtd_outl(0xb801e5dc,0x0);//ODT
	//RDCew @$PAD_CTRL_PROG 		 = 0x1C000aff															
	//RDCew @$PAD_CTRL_PROG 		 = 0x1d000aff															
	 
	
	//fifo reset
	 
	
	//==================pupd3 mode==================//
rtd_outl(0xb801e618,0x007f2052);//rst_fifo_mode=1,fw_set_mode=2//pupd3
	//==================pupd4 mode==================//
	//rtd_outl(0xb801e618,0x007f2092);//pupd4 mode on
	//*rtd_outl(0xb801e5fc,0x00000fff);//[11]~[0]=>pupd4 current selection
	//
	//*read fifo setting:tm_dqs_en+4T=tm_rd_fifo
	//tm_dqs_en+1T=tm_odt_en
	 
	//we must follow the Read latency//
	 
	//fifo reset
	//rtd_outl(0xb801e618,.....);//fifo reset mode [2][3]?????
	//question [2][3] :rst_fifo_mode,[1][0]:fw_set_mode
	//fw_set_mode==>rtd_ooutl(0xb801e61c,0x000000000);//question
	//we should test for rst fifo and all reset 
	 
	 
	 
	//==================pupd4 mode==================//
	//==============================================//
	//======================================================PUPU3&4 Setting==================================//
	 
	 

	
	//==========read delay chain (rx phase)======//
	 
	rtd_outl(0xb801e58c,0x0a0a0a0a);//DQSP[3]~DQSP[0] dly
	rtd_outl(0xb801e590,0x0a0a0a0a);//DQSP[3]~DQSP[0] dly
	rtd_outl(0xb801e594,0x0a0a0a0a);//DQSP[3]~DQSP[0] dly
	rtd_outl(0xb801e598,0x0a0a0a0a);//DQSP[3]~DQSP[0] dly
	
	rtd_outl(0xb801e59c,0x0a0a0a0a);//DQSP[7]~DQSP[4] dly
	rtd_outl(0xb801e5a0,0x0a0a0a0a);//DQSP[7]~DQSP[4] dly
	rtd_outl(0xb801e5a4,0x0a0a0a0a);//DQSP[7]~DQSP[4] dly
	rtd_outl(0xb801e5a8,0x0a0a0a0a);//DQSP[7]~DQSP[4] dly
	
	rtd_outl(0xb801e5ac,0x0a0a0a0a);//DQSN[3]~DQSN[0] dly
	rtd_outl(0xb801e5b0,0x0a0a0a0a);//DQSN[3]~DQSN[0] dly
	rtd_outl(0xb801e5b4,0x0a0a0a0a);//DQSN[3]~DQSN[0] dly
	rtd_outl(0xb801e5b8,0x0a0a0a0a);//DQSN[3]~DQSN[0] dly
	
	rtd_outl(0xb801e5bc,0x0a0a0a0a);//DQSN[7]~DQSN[4] dly
	rtd_outl(0xb801e5c0,0x0a0a0a0a);//DQSN[7]~DQSN[4] dly
	rtd_outl(0xb801e5c4,0x0a0a0a0a);//DQSN[7]~DQSN[4] dly
	rtd_outl(0xb801e5c8,0x0a0a0a0a);//DQSN[7]~DQSN[4] dly
	 
	rtd_outl(0xb801e684,0x0a330a33);//?
	rtd_outl(0xb801e690,0x00000000);//?
	rtd_outl(0xb801e69c,0x00000000);//?
	rtd_outl(0xb801e61c,0x0000000c);//fw_Set_rd_dly=1,for update the Rx dly chain
 
	//Reg for update the Rx phase
	 
	//==========read delay chain (rx phase)end===//
	//========================fifo===============================//
	rtd_outl(0xb800884c,0x00000030);   //R/W/Q FIFO
	rtd_outl(0xb801e6dc,0x22116677);//?
	rtd_outl(0xb801e6e0,0x10101010);//?
	rtd_outl(0xb801e568,0x22116677);//cal_shift_ctrl
	rtd_outl(0xb801e56c,0x22222222);//cal_LS_sel
	rtd_outl(0xb801e570,0x22222222);//cal_LS_sel
	rtd_outl(0xb801e574,0x22222222);//cal_LS_sel
	rtd_outl(0xb801e578,0x22222222);//cal_LS_sel
	
	rtd_outl(0xb801e57c,0x22222222);//cal_RS_sel
	rtd_outl(0xb801e580,0x22222222);//cal_RS_sel
	rtd_outl(0xb801e584,0x22222222);//cal_RS_sel
	rtd_outl(0xb801e588,0x22222222);//cal_RS_sel

	//============================DDR_initial==================//
	//rtd_outl(0xb8008940, 0x00000001); 	  //
	rtd_outl(0xb8008840, 0x00000003);		//DRAM init
	arom_mdelay(0x1);
	rtd_outl(0xb8008840, 0x03000000);		//end 200us
	arom_mdelay(0x2);
	rtd_outl(0xb8008840, 0x0c000000);		//end 500us
	arom_mdelay(0x5); 
	//==========================DDR_initail_end==================//
	

	//-------- BUS/BUSH/ACPU clock source select to 27MHz ------------------------
	rtd_outl(0xb8060050,0x00000001);
	arom_mdelay(1);
	
	//-------- SPI clk -------------------------------------------------
	rtd_outl(0xb801a808,0xF); // fdiv, clk_sf = clk_sys / (fdiv+1)
	arom_mdelay(1);
rtd_outl(0xb801a814,0x1); // latch data at the rising edge
	rtd_outl(0xb801a80c,0x00202020);

	//-------- PLL ACPU -------------------------------------------------
	rtd_outl(0xb800010c,0x00000324); // PLLACPU power down, hold reset, output disable
	rtd_outl(0xb8000108,0x000A3600); // max 850, set 27*37/2 = 499.5MHz
	rtd_outl(0xb800010c,0x00000325); // PLLACPU power on
	rtd_outl(0xb800010c,0x00000327); // release PLLACPU reset

	//-------- PLL BUS -------------------------------------------------
	rtd_outl(0xb8000138,0x00000004); // PLLBUS power down, hold reset, output disable
	rtd_outl(0xb8000130,0x00351B52); // max 405, set 27*15 = 405MHz
	rtd_outl(0xb8000138,0x00000005); // PLLBUS power on
	rtd_outl(0xb8000138,0x00000007); // release PLL reset
	
	//-------- PLL BUSH -------------------------------------------------
	rtd_outl(0xb8000148,0x00000004);  // PLLBUSH power down, hold reset, output disable
	rtd_outl(0xb8000140,0x17BD1B52); // max 384, set 27*113/2/4 = 381.375MHz
	rtd_outl(0xb8000148,0x00000005);  // PLLBUSH power on
	rtd_outl(0xb8000148,0x00000007);  // release PLLBUSH reset
	
	arom_mdelay(1); // wait at least > 15us
	rtd_outl(0xb800010c,0x00000323); // PLLACPU output enable
	rtd_outl(0xb8000138,0x00000003); // PLLBUS output enable
	rtd_outl(0xb8000148,0x00000003); // PLLBUSH output enable
	
	//-------- BUS/BUSH/ACPU clock source select to PLLBUS/PLLBUSH/PLLACPU ------------------------
	rtd_outl(0xb8060050,0x00000000); 
	arom_mdelay(1); 

	//-------- PLL SCPU -------------------------------------------------
	rtd_outl(0xb8000100,0x00262400); // max 1000, set 27*100/3= 900MHz
	rtd_outl(0xb8000104,0x00000325); // PLLSCPU  power on
	rtd_outl(0xb8000104,0x00000327); // release SCPU PLL reset
	
	//-------- PLL VCPU -------------------------------------------------
	rtd_outl(0xb8000110,0x00350A00); // target 472, set 27*37/2=472.5MHz
	rtd_outl(0xb8000114,0x00000325); // PLLVCPU power on
	rtd_outl(0xb8000114,0x00000327); // release VCPU PLL reset
	//-------- PLL DISP -------------------------------------------------
	rtd_outl(0xb8000190,0x01901336);	// set 243MHz
	rtd_outl(0xb8000194,0x11020001);	// DPLL power on
	rtd_outl(0xb8000194,0x11020043);	// release DPLL reset

	
	//-------- PLL GPU1-------------------------------------------------
	rtd_outl(0xb80001e0,0x00098600); // max 450, set 351MHz
	rtd_outl(0xb80001e4,0x00000325); // PLLGPU1 power on
	rtd_outl(0xb80001e4,0x00000327); // release PLLGPU1 reset
	
	//-------- PLL GPU2-------------------------------------------------
	rtd_outl(0xb80001e8,0x00098600); // max 450, set 351MHz
	rtd_outl(0xb80001ec,0x00000325); // PLLGPU2 power on
	rtd_outl(0xb80001ec,0x00000327); // release PLLGPU2 reset

	//-------- PLL 27X -------------------------------------------------
	//rtd_outl(0xb8000240,0x0225000E); // max = 432, set 27*16 = 432MHz 
	//rtd_outl(0xb8000244,0x00105401); // 1.1V LDO power on & output 1.0V, LDO XTAL power on & output 1.76V
	//rtd_outl(0xb8000248,0x00000001); // release PLL_27X & VCO reset & power on
	//rtd_outl(0xb8000248,0x00000007); // release PLL_27X & VCO reset & power on
	//arom_mdelay(1); // at least > 5us
	
	
	//-------- PLL ETN -------------------------------------------------
	//rtd_outl(0xb8016d00,0x0230370a); // 25M
	//rtd_outl(0xb8016d04,0x00008035); // power on	
	//rtd_outl(0xb8016d04,0x00008037); // release reset
	
	arom_mdelay(1); // at least > 5us
	rtd_outl(0xb8000104,0x00000323); // PLLSCPU CKOUT enable
	rtd_outl(0xb8000114,0x00000323); // PLLVCPU CKOUT enable
	rtd_outl(0xb80001e4,0x00000323); // PLLGPU1 output enable
	rtd_outl(0xb80001ec,0x00000323); // PLLGPU2 output enable
	//rtd_outl(0xb8016d04,0x00008033); // PLLETN output enable

	//-------- Module Clock & Reset Enable ---------
	arom_mask_register(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3, I/M/D domain clock
	arom_mask_register(0xb8000014, 0x1effffe7, 0x00000000);// disable TVSB1~3, I/M/D domain clock
	arom_mask_register(0xb8000008, 0xffff8fe9, 0x00000000);// hold TVSB1~3, I/M/D domain reset
	arom_mask_register(0xb8000008, 0xffff8fe9, 0x00007016);// release TVSB1~3, I/M/D domain reset
	arom_mdelay(0x1);
	arom_mask_register(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3, I/M/D domain clock

	//-------- Disable write merger, Multi write, Bypass Read ----------- price
	//rtd_outl(0xb801a018, 0x00002888); // disable A/VCPU write merge, bypass read
	//rtd_outl(0xb8008f04, 0x00000000);// dsiable SCPU write merge, bypass read
	
	//-------- HDMI bandgap power---------
	//arom_mask_register(0xb8000008, 0xFFFDFFFF, 0x00020000); // release HDMI reset
	//arom_mask_register(0xb800000c, 0xFFFFFFFD, 0x00000002); // enable HDMI clock
	//arom_mask_register(0xb8007B40, 0xFDFFFFFF,0x02000000); //HDMI bandgap power 1:on 0:off
	//arom_mdelay(1);
    
    //---------- Arbitration Setting-------------
    //new pre-arbitration
    arom_mask_register(0xb8008004, 0xfeffffff, 0x01000000);

    //DCU1 Arbitration
    rtd_outl(0xb8008028, 0x8e610040);              // pre-arb merge, use nertd_outl(setting for KONKA USB playback issue, increase DC_PHY utility, trade-off realtime of priority, suggest by SYChang
    rtd_outl(0xb8008080, 0x00000000);              // TVSB2
    rtd_outl(0xb8008084, 0x00100020);              // TVSB1
    rtd_outl(0xb8008088, 0x00100020);              // SB1
    rtd_outl(0xb800808c, 0x00100040);              // SB2
    rtd_outl(0xb8008090, 0x00180040);              // SB3
    rtd_outl(0xb8008094, 0x00100020);              // VE
    rtd_outl(0xb8008098, 0x00100020);              // TVSB3
    rtd_outl(0xb800809c, 0x00180020);              // GPU1
    rtd_outl(0xb80080a0, 0x00000020);              // DTV Demod
    rtd_outl(0xb80080a4, 0x00100020);              // VE2
    rtd_outl(0xb80080a8, 0x00180020);              // GPU2
    rtd_outl(0xb80080b0, 0x07ff0007);

    //TVSB2_DCU1
    rtd_outl(0xb8038100, 0x00000007);
    rtd_outl(0xb8038108, 0x00000020);              // DIMW
    rtd_outl(0xb803810c, 0x00000020);              // DIMR
    rtd_outl(0xb8038110, 0x00000050);              // CAPM
    rtd_outl(0xb8038114, 0x00000050);              // DISPM
    rtd_outl(0xb8038118, 0x00000090);              // ODWR
    rtd_outl(0xb803811c, 0x00000088);              // ODRD
    rtd_outl(0xb8038120, 0x00000090);              // VO1_Y
    rtd_outl(0xb8038124, 0x00000090);              // VO1_C
    rtd_outl(0xb8038128, 0x00000044);              // OSD1
    rtd_outl(0xb803812c, 0x00000088);              // SUBT
    rtd_outl(0xb8038130, 0x00000090);              // IHDMI
    rtd_outl(0xb8038134, 0x00000090);              // VO2_Y
    rtd_outl(0xb8038138, 0x00000090);              // VO2_C
    rtd_outl(0xb803813c, 0x00000090);              // CAPS
    rtd_outl(0xb8038140, 0x00000090);              // DISPS
    rtd_outl(0xb8038144, 0x00000044);              // OSD2

return 0;
	return res;
}

/* This function is called before applying hwsetting */
int pre_hwsetting_c(void)
{
	debug("%s\n", __FUNCTION__);

	return 0;
}

/* This function is called after applying hwsetting */
int post_hwsetting_c(void)
{
	debug("%s\n", __FUNCTION__);

	return 0;
}

int get_hwsetting(const int flash_type, const unsigned int target_addr)
{
	int res = 0;

	switch (flash_type) {
		case SPI_FLASH_BOOT:
			res = get_hwsetting_spi(target_addr, SCS_UNCHECK_AREA);
			break;
#if 0
		case SPI_NAND_FLASH_BOOT:
			res = get_hwsetting_spi_n(target_addr, SCS_UNCHECK_AREA);
			break;
#endif
		case NAND_FLASH_BOOT:
			res = get_hwsetting_nand(target_addr, SCS_UNCHECK_AREA);
			break;
		case EMMC_BOOT:
			res = get_hwsetting_emmc(target_addr, SCS_UNCHECK_AREA);
			break;

		case UNKNOWN_BOOT:
		default:
			res = ERR_UNKNOWN_TYPE;
			break;
	}

	return res;
}

int init_hwsetting_c(const int flash_type)
{
	int res;
	unsigned int dst, count;
	
	//dst = CP42K_SRAM_ADDR + rom_params->Size_of_Aux_Code_Area;	
	dst = CP42K_SRAM_ADDR + CP42K_SRAM_SIZE - SCS_UNCHECK_AREA;	

	res = get_hwsetting(flash_type, dst);

	if(res == 0)
		debug("get hw setting DONE!\n");
	else {
		debug("get hw setting ERROR!\n");
		return ERR_HWSETTING_FAILED;
	}

	pre_hwsetting_c();

	//skip header
	res = parse_hw_setting_c((unsigned int *)(dst+4), 3072, &count, 0);

	post_hwsetting_c();

	if(res == 1)
		debug("parse hw setting DONE!\n");
	else {
		debug("parse hw setting ERROR!\n");
		return ERR_HWSETTING_NOT_FINISH;
	}	
	return 0;
}
