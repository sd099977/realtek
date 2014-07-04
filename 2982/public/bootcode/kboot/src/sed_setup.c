#include "sed_common.h"
#include "sed_drv_wdog.h"
#include "sed_drv_sfc.h"
#include "sed_drv_gpio.h"
#include <sysdefs.h>


extern int mmc_blk_write( unsigned int blk_addr, unsigned int blk_cnt, unsigned char * data_buffer );
extern int mmc_blk_read( unsigned int blk_addr, unsigned int blk_cnt, unsigned char * data_buffer );
extern uint8 visualize_print_disable;

//see "Sirius_CRT_Arch_Spec.doc"
#define SYS_REG_BASE			0xb8000000
#define SYS_PLL_KCPU			(SYS_REG_BASE + 0x108)
#define SYS_PLL_BUS1			(SYS_REG_BASE + 0x130)

uint8 kcpu_m = 0;
uint8 bus_m = 0;

extern void arom_mdelay(unsigned int dwMiniSecond);

//=====================Start init DDR============================
 void arom_mask_register(const unsigned int reg_addr, const unsigned int AND_filter,
	 const unsigned int OR_filter)
 {
	 REG32(reg_addr) = (REG32(reg_addr) & AND_filter) | OR_filter;
	 arom_mdelay(20);

 }

 void InitTimer(unsigned int dwInit)
{

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

	bool	bIoStatus = FALSE;
	UINT32 	bitmask = 1 << (7);

	if(REG32(0xb801b008) & bitmask)
	{
		bIoStatus = TRUE;
	}

	return bIoStatus;
}
#define TIMERINFO_MSEC      1000000/37

void arom_mdelay(unsigned int dwMiniSecond)
{
	InitTimer(dwMiniSecond*TIMERINFO_MSEC);
	//Wait for Interrupt Pending Status
	while(SystemTimeout() == FALSE);
}




void sed_ddr_init()
{

#ifdef ENABLE_DDR
	//-------- HDMI bandgap power---------
	arom_mask_register(0xb800000c, 0xfffffffd, 0x00000002);// enable HDMI clock
	arom_mask_register(0xb800000c, 0xfffffffd, 0x00000000);// disable HDMI clock
	arom_mask_register(0xb8000008, 0xfffdffff, 0x00000000);// hold HDMI reset
	arom_mask_register(0xb8000008, 0xfffdffff, 0x00020000);// release HDMI reset
	arom_mdelay(0x1);
	arom_mask_register(0xb800000c, 0xfffffffd, 0x00000002);// enable HDMI clock
	arom_mdelay(0x1);
	arom_mask_register(0xb8007b40, 0xfdffffff, 0x02000000);		 //HDMI bandgap power 1:on 0:off
	//arom_mask_register(0xb8000004,0xffffffef,0x00000100);//2.REGPLL_Rst
	//arom_mdelay(0x5);
	//arom_mask_register(0xb8000014, 0xffffffef, 0x00000000);	   //3.REGPLL_ck_en
	//-------- IFD MBIAS ----------
	arom_mask_register(0xb8000014, 0xfffeffff, 0x00010000);		 // enable IFADC clock
	arom_mask_register(0xb8000014, 0xfffeffff, 0x00000000);		 // disable IFADC clock
	arom_mask_register(0xb8000008, 0xffffffdf, 0x00000000);		 // hold IFADC reset
	arom_mask_register(0xb8000008, 0xffffffdf, 0x00000020);		 // release IFADC reset
	arom_mdelay(0x1);
	arom_mask_register(0xb8000014, 0xfffeffff, 0x00010000);		 // enable IFADC clock
	arom_mdelay(0x1);
	arom_mask_register(0xb8033110, 0xfffffeff, 0x00000100);		 // IFD MBIAS power on
	arom_mdelay(0x1);


	rtd_inl(0xb80002e0); //--> 0x00000000;
	//rtd_outl(0x180002DC,0x000000ff);//4.reg_dpi_pll_dum[0] go HIGH (PLL LDO reset)//4.LDO reset--400~750MHz,800~1100MHz
	//arom_mdelay(300);
	rtd_outl(0xb80002dc, 0x000000ff);		//4.reg_dpi_pll_dum[0] go HIGH (PLL LDO reset)//4.LDO reset--1400~1700MHz
	arom_mdelay(100);
	rtd_outl(0xb80102e4, 0x00000000);//ckref_sel
	 //=========== PLL Phase interpolation (PI) setting ===================//

	//rtd_outl(0xb80002d4,0x03e00000) //854MHz
	//rtd_outl(0xb80002d4,0x03b00000) //800MHz
	rtd_outl(0xb80002d4,0x02f00000); //661.5MHz
	//rtd_outl(0xb80002d4,0x02600000)//540MHz
	//rtd_outl(0xb80002d4, 0x01f00000);//445.5MHz
	//rtd_outl(0xb80002d4, 0x01a00000);//3XX
	//rtd_outl(0xb80002d4, 0x01f00000);//445.5MHz
	//rtd_outl(0xb80002d4, 0x01f00000);//445.5MHz

	 //PI_phase
	 rtd_outl(0xb80002c8, 0x00000000);		 //DQS0,DQS1,cmd,ck
	 rtd_outl(0xb80002cc, 0x00000000);		 // xx,ck_1,,DQS3,DQS2
	 rtd_outl(0xb80002d0, 0x00000879);

	 //PI_RL_BIAS
	 //rtd_outl(0xb80002c4,0xff98ca9e);//clok;200-375MHz,VCO;400~750MHz
	 //rtd_outl(0xb80002c4,0xffcaca9f);//clock;400~550MHz,VCO;800~1100MHz
	 rtd_outl(0xb80002c4, 0xffdaca8e);		 //clock;700~850MHz,VCO;1400~1700MHz

	 //
	 //===================================PLL initial=================================================
	arom_mask_register(0xb8000000, 0xfe7fffff, 0x01800000); 	  //DCU&DC_phy reset
	 arom_mdelay(0x1);
	 arom_mask_register(0xb800000c, 0xfffbffff, 0x00040000); 	  //DCU&DC_phy_ck_en on
	 //rtd_outl(0xb800000c, 0xffffffff);	   //DCU&DC_phy_ck_en on
	 rtd_outl(0xb80002c0, 0x020000ff);		 //c) enable reg_dpi_mck_clk_en
	 //rtd_outl(0xb80002C0,0x200001ff); //c) enable reg_dpi_mck_clk_oe
	 //rtd_outl(0xb80002C0,0x200003ff); //c) enable reg_dpi_mck_clk_oe
	 //rtd_outl(0xb80002C0,0x200007ff); //c) enable reg_dpi_mck_clk_oe
	 //rtd_outl(0xb80002C0,0x20000fff); //c) enable reg_dpi_mck_clk_oe
	 //rtd_outl(0xb80002C0,0x20001fff); //c) enable reg_dpi_mck_clk_oe
	 //rtd_outl(0xb80002C0,0x20003fff); //c) enable reg_dpi_mck_clk_oe
	 rtd_outl(0xb80002c0, 0x02007fff);		 //c) enable reg_dpi_mck_clk_oe


	// b80002c0 is right is ok
	rtd_outl(0xb801E6A0,0x10000000); //[27]:[24]-->_dqs_mux_sel_BIST_2TO1-->DPI_spec
	//rtd_outl(0xb801E524,0x00000000);
	rtd_outl(0xb801E524,0x0000003c); //[5]:[2]-->  dqs_mux_sel_WRLVL_CTRL-->DPI_spec
	//rtd_inl(0xb801e524);
	rtd_inl(0xb80002e0);
	arom_mdelay(0x10);
	//===================================PLL initial end ============================================

	//============================ DC PAD/ZQ/TX Delay Chain Setting ===================================================//
	//**************************zq********************************//
	//====0x1801_E5D0?
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
	rtd_outl(0xb800880c, 0x2001707a);		//TMCTRL3: tFAW:0x19((25+2)*1.5=40.5)(40ns)/ tREF: 0x13((19+1)*128*1.5=3840)(3.9us/7.8us) / tmRFC:0xA3((163+11)*1.5=261)(260ns)
	rtd_outl(0xb8008800, 0x00189714);		//TMCTRL0: tRAS:0x18((24+2)*1.5 = 39)(35ns) / #tCL:0x9(9nCK) / #tCWL:0x7(7nCK) / #tmCLRD:0x14(20/2=10)(10nCK)
	rtd_outl(0xb8008804, 0x05100d0d);		//TMCTRL1: tRRD:0x6(6+2=8)(7.5nCK) / tRP:0x7((7+2)*1.5=13.5)(13.125ns) / tRCD:0x7((7+2)*1.5=13.5)(13.125ns) / tRC:0x1B((27+6)*1.5 = 49.5)(48.75ns)
	rtd_outl(0xb8008808, 0x02040508);		//TMCTRL2: TCCD:2(2+2=4)(4nCK) / tRTP:6(6*1.5=7.5)(7.5ns) / tWTR:5((5+1)*1.5=9)(7.5ns) / tWR:0x9((9+2)*1.5=18)(15ns)
	rtd_outl(0xb8008810, 0x03030a02);		//TMCTRL4: tAOND:2((2+2)*1.5=6)(2ns) / tAOFD:2((2+2)*1.5=6)(2ns) / tMMOD(Mode register Set Command cycle time):13(13)max(12nCK, 15ns) / tMMRD(MRS cmd to ODT update delay):2(2+2=4)(4nCK)
	rtd_outl(0xb8008814, 0x00200400);		//TMCTRL5: tMRTW:1(2nCK) / tZQOPER:0x200(512)((256nCK) / tZQINIT:0x400(1024)(512nCK)
	rtd_outl(0xb8008818, 0x00240080);		//TMCTRL6: dqs_lat_sel:1 / dqs_alt:12.5 / tDLLK:0x240(576)(512nCK) / tZQCS:0x80(128)(64nCK)
	rtd_outl(0xb8008844, 0x00000d31);		//MOD_REG0,  bit[15:0] for DDR3-1600MHz: #CL11/BC4&BL8/#WR12/AL0, 34/60
	rtd_outl(0xb8008848, 0x00000010);		//MOD23_REG for DDR3:Rtt_WR: disable,  #CWL:8,	ASR disable,  dynamic ODT off.
	rtd_outl(0xb801E558, 0x00000fff);		//ODT_CTRL_new


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
	 rtd_outl(0xb8062300,'l');
	//read fifo setting:tm_dqs_en+2.5T=tm_rd_fifo  ,tm_dqs=tmcl_rd
	//CL+1T=tm_odt_en
	rtd_outl(0xb801e544,0x0000c010);//tm_dqs_en,7.5T-- dqs0
	rtd_outl(0xb801e548,0x0000c010);//tm_dqs_en,7.5T-- dqs1
	rtd_outl(0xb801e54c,0x0000c010);//tm_dqs_en,7.5T-- dqs2
	rtd_outl(0xb801e550,0x0000c010);//tm_dqs_en,7.5T-- dqs3
	rtd_outl(0xb801e554,0x0001040b);//tm_rd_fifo=11T //
	//rtd_outl(0xb801e558,0x00000fff);//tm_odt_en:2~13T //«e­±//





	//we must follow the Cas latency//
	rtd_outl(0xb801e5d8,0x0);//ODT
	rtd_outl(0xb801e5dc,0x0);//ODT
	//RDCew @$PAD_CTRL_PROG 		 = 0x1C000aff
	//RDCew @$PAD_CTRL_PROG 		 = 0x1d000aff


	//fifo reset


	//==================pupd3 mode==================//
	rtd_outl(0xb801e618,0x007f2012);//rst_fifo_mode=1,fw_set_mode=2//old mode
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
#endif

}
//======================Init DDR done=========================

void sed_cmd_chip_rst (uint8 *ibuf, uint8 *obuf)
{
	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	/* Do chipset reset here*/
	sed_wdog_reset();

	/* Should not reach here */
	return;
}


extern char __heap_start_addr;
#define END_OF_DMEM_ADDR	0xb807A800

void sed_cmd_chip_rst_post (void)
{
	uint32 *ptr = 0;

	//sed_printf("sed_cmd_chip_rst_post\n");
	#if 0
	ptr = (uint32 *)(uint32) &__heap_start_addr;
	sed_printf("dmem(%x %x):\n", ptr, __heap_start_addr);

	for (i=0; i<10; i++)
		sed_printf("dmem(%x %x):\n", (uint32) ptr, *(ptr++));

	sed_printf("dmem(%x %x):\n", END_OF_DMEM_ADDR, *(uint32 *) END_OF_DMEM_ADDR-4);
	#endif
	ptr = (uint32 *)(uint32) &__heap_start_addr;

	/* Clear volatile memory */
	while ( ((uint32) ptr)<END_OF_DMEM_ADDR ) {
		*(ptr++) = 0;
	}

	#if 0
	ptr = (uint32 *)(uint32) &__heap_start_addr;

	for (i=0; i<10; i++)
		sed_printf("dmem(%x %x):\n", (uint32) ptr, *(ptr++));

	sed_printf("fdmem(%x %x):\n", END_OF_DMEM_ADDR-4, *(uint32 *) (END_OF_DMEM_ADDR-4));
	#endif

	/* Set (CERT_Cmd_Max_Cycles [10]) check "C_CERT_EXCHANGE" */
}

// suggested clk paramters are 0x00 0x00 0x0D 0x0D
int sed_cmd_set_config (uint8 *ibuf, uint8 *obuf)
{
	uint16 clkParaLen = get_cmd_data_len(ibuf) - 1;
	uint8 saveSetting = ibuf[clkParaLen + 3];
	uint8 sts = C_SET_CONFIG_OK;
	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	kcpu_m = ibuf[CMD_DATA_IN_IDX+2];
	bus_m = ibuf[CMD_DATA_IN_IDX+3];
	ibuf[CMD_DATA_IN_IDX+4] = visualize_print_disable;

	/* Check parameter and apply new CLK setting */
	//sed_printf("CLK(%d):\n", clkParaLen);
	//sed_format_print(&(ibuf[CMD_DATA_IN_IDX]), clkParaLen);

	// kcpu_m range is from 1~13
	// bus_m range is from 0~13
	if ((kcpu_m > 13) || (bus_m > 13) || (kcpu_m <1)) {
		sts = C_SET_CONFIG_PARAM_ERROR;
		goto fail;
	}

	// kcpu clk
	bitwise_AND_OR(SYS_PLL_KCPU, 0xfff80fff, (kcpu_m<<12));

	// cert/cp clk
	bitwise_AND_OR(SYS_PLL_BUS1, 0xfe03ffff, (bus_m<<18));


	kcpu_m = (REG32(SYS_PLL_KCPU)>>12)&0x7f;
	bus_m =  (REG32(SYS_PLL_BUS1)>>18)&0x7f;

	if ((kcpu_m != ibuf[CMD_DATA_IN_IDX+2]) ||
		(bus_m != ibuf[CMD_DATA_IN_IDX+3])) {
		sts = C_SET_CONFIG_ERROR;
		goto fail;
	}

	if (saveSetting) {
		/* Save CLK setting to persistent memory */
		sed_sfc_erase(0x200000, 0x1000); //-> (check spi flash free block)
		sed_sfc_write(0x200000, &(ibuf[CMD_DATA_IN_IDX]), clkParaLen+1); //-> (check spi flash free block)
	}

fail:

	obuf[RSP_DATA_OUT_IDX] = 0;
	obuf[RSP_DATA_OUT_IDX+1] = 0;
	obuf[RSP_DATA_OUT_IDX+2] = kcpu_m;
	obuf[RSP_DATA_OUT_IDX+3] = bus_m;

#if 0
	/* Read CLK setting from register and fill in obuf */
	for (i = 0; i < clkParaLen; i++)
		obuf[RSP_DATA_OUT_IDX + i] = ibuf[CMD_DATA_IN_IDX + i];
#endif

	return sed_command_exit(obuf, C_SET_CONFIG, clkParaLen, sts);
}

#define SED_CLK_SETTING_NUM		0x4
int sed_cmd_get_config (uint8 *ibuf, uint8 *obuf)
{
	uint8 sts = C_GET_CONFIG_OK;

	sed_command_entry(obuf, IO_BUF_MAX_LEN);

	kcpu_m = (REG32(SYS_PLL_KCPU)>>12)&0x7f;
	bus_m =  (REG32(SYS_PLL_BUS1)>>18)&0x7f;

	obuf[RSP_DATA_OUT_IDX] = 0;
	obuf[RSP_DATA_OUT_IDX+1] = 0;
	obuf[RSP_DATA_OUT_IDX+2] = kcpu_m;
	obuf[RSP_DATA_OUT_IDX+3] = bus_m;

	return sed_command_exit(obuf, C_GET_CONFIG, SED_CLK_SETTING_NUM, sts);

}

void sed_init_config()
{
	uint8 temp[16]= {0,0,0,0,1};

	// read the config date back from spi flash
 	sed_sfc_read(0x200000, temp, 16);
	kcpu_m = temp[2];
	bus_m = temp[3];
	visualize_print_disable = temp[4];

	//sed_printf("%x ", kcpu_m);
	//sed_printf("%x ", bus_m);

	if ((kcpu_m > 13) || (bus_m > 13) || (kcpu_m <1)) {  // restore to default
		kcpu_m = 0xd; // 405Mhz
		bus_m = 0xd; // 405Mhz/2
		visualize_print_disable	 = 1;
	}

	// kcpu clk
	bitwise_AND_OR(SYS_PLL_KCPU, 0xfff80fff, (kcpu_m<<12));
  	// cert/cp clk
	bitwise_AND_OR(SYS_PLL_BUS1, 0xfe03ffff, (bus_m<<18));

}

void wait_loop(volatile unsigned int count)
{
	while (count--)
		;
}


void __attribute__ ((nomips16)) enable_clock(unsigned int reg_reset, unsigned int mask_reset,
	unsigned int reg_clock, unsigned int mask_clock)
{
#ifdef ROM_DEBUG
	prints("\n");
	prints(__FUNCTION__);
	prints("\n");
#endif

	/* set CLKEN = 0 */
	REG32(reg_clock) &= ~mask_clock;

	/* set RSTN = 0 */
	REG32(reg_reset) &= ~mask_reset;

	/* set CLKEN = 1 */
	REG32(reg_clock) |= mask_clock;

	/* wait a while */
	wait_loop(0x10);

	/* set CLKEN = 0 */
	REG32(reg_clock) &= ~mask_clock;

	/* set RSTN = 1 */
	REG32(reg_reset) |= mask_reset;

	/* wait a while */
	//wait_loop(0x10);

	/* set CLKEN = 1 */
	REG32(reg_clock) |= mask_clock;
}


#define SYS_SOFT_RESET3			(SYS_REG_BASE + 0x8)
#define SYS_GROUP1_CK_EN		(SYS_REG_BASE + 0x14)

void sed_cert_reset()
{
	// Nagra AKL/ND/DSC
	enable_clock(SYS_SOFT_RESET3, 0xE0000000, SYS_GROUP1_CK_EN, 0x00000600);

}

