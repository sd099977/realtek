#include <qc_verify_common.h>


#define _SUCCESS				0
#define _FAIL   				1

#define YPP_480I  0
#define YPP_1080I 1
#define YPP_1080P 2

#ifndef BOOL
typedef int BOOL;    //define BOOL
#endif

#ifndef _BIT0
#define _BIT0 (0x1)
#define _BIT1 (0x2)
#define _BIT2 (0x4)
#define _BIT3 (0x8)
#define _BIT4 (0x10)
#define _BIT5 (0x20)
#define _BIT6 (0x40)
#define _BIT7 (0x80)
#define _BIT8 (0x100)
#define _BIT9 (0x200)

#define _BIT10 (0x400)
#define _BIT11 (0x800)
#define _BIT12 (0x1000)
#define _BIT13 (0x2000)
#define _BIT14 (0x4000)
#define _BIT15 (0x8000)
#define _BIT16 (0x10000)
#define _BIT17 (0x20000)
#define _BIT18 (0x40000)
#define _BIT19 (0x80000)

#define _BIT20 (0x100000)
#define _BIT21 (0x200000)
#define _BIT22 (0x400000)
#define _BIT23 (0x800000)
#define _BIT24 (0x1000000)
#define _BIT25 (0x2000000)
#define _BIT26 (0x4000000)
#define _BIT27 (0x8000000)
#define _BIT28 (0x10000000)
#define _BIT29 (0x20000000)

#define _BIT30 (0x40000000)
#define _BIT31 (0x80000000)
#endif

#define abs(a,b)	(a>b)?(a-b):(b-a)
///////////////    IPTG  Reg     ///////////////////
#define  REG_PTG_TOTALHV				0xb8022100
#define  REG_PTG_H_STA_WID				0xb8022104
#define  REG_PTG_V_STA_LEN				0xb8022108
#define  REG_PTG_TG						0xb802210c
#define  REG_PTG_TG_LINE				0xb8022110
#define  REG_PTG_HSTA_WID				0xb8022114
#define  REG_PTG_VSTA_LEN				0xb8022118
#define  REG_PTG_CTRL					0xb802211c
#define  REG_PTG_BARW					0xb8022120
#define  REG_PTG_C0Y					0xb8022124
#define  REG_PTG_C1Y					0xb8022128
#define  REG_PTG_C2Y					0xb802212c
#define  REG_PTG_C3Y					0xb8022130
#define  REG_PTG_C4Y					0xb8022134
#define  REG_PTG_C5Y					0xb8022138
#define  REG_PTG_C6Y					0xb802213c
#define  REG_PTG_C7Y					0xb8022140
#define  REG_PTG_MAX_COLOR_CTRL		0xb8022144

#define  REG_R_PTG_HSTA_WID			0xb8022148
#define  REG_R_PTG_VSTA_LEN		    	0xb802214c
#define  REG_R_PTG_CTRL					0xb8022150
#define  REG_R_PTG_BARW				0xb8022154
#define  REG_R_PTG_C0Y					0xb8022158
#define  REG_R_PTG_C1Y					0xb802215c
#define  REG_R_PTG_C2Y					0xb8022160
#define  REG_R_PTG_C3Y					0xb8022164
#define  REG_R_PTG_C4Y					0xb8022168
#define  REG_R_PTG_C5Y					0xb802216c
#define  REG_R_PTG_C6Y					0xb8022170
#define  REG_R_PTG_C7Y					0xb8022174
#define  REG_R_PTG_MAX_COLOR_CTRL		0xb8022178


///////////////    SP measur Reg     ///////////////////
#define  REG_SP_TOGGLE			0xb8021070
#define  REG_SP_MS3CTRL			0xb8021100
#define  REG_SP_MS3RST0			0xb8021104
#define  REG_SP_MS3RST1			0xb8021108
#define  REG_SP_MS3Stus			0xb802110c
#define  REG_SP_MS3ENATCTRL	0xb8021118
#define  REG_SP_MS3ENAT		0xb802111c
#define  REG_SP_MS1CTRL			0xb8021200
#define  REG_SP_MS1RST0			0xb8021204
#define  REG_SP_MS1RST1			0xb8021208
#define  REG_SP_MS1Stus			0xb802120c
#define  REG_SP_MS2CTRL			0xb8021214
#define  REG_SP_MS2RST0			0xb8021218
#define  REG_SP_MS2RST1			0xb802121c
#define  REG_SP_MS2Stus			0xb8021220


///////////////    ABL Reg     ///////////////////
#define REG_ABL_CTRL			0xb8020200
#define REG_ABL_WINDOW 		0xb8020204
#define  REG_ABL_STATUS 		0xb8020208
#define  REG_ABL_RSLT0 			0xb8020210
#define  REG_ABL_RSLT1 			0xb8020214
#define  REG_ABL_NOISE_VAL0 	0xb8020218
#define  REG_ABL_NOISE_VAL1 	0xb802021c
#define  REG_ABL_MGN_RG 		0xb8020220
#define  REG_ABL_MGN_B 			0xb8020224

///////////////    SF Reg     ///////////////////
#define  REG_AUTO_FIELD				0xb8022000
#define  REG_AUTO_H_BOUNDARY		0xb8022004
#define  REG_AUTO_V_BOUNDARY		0xb8022008
#define  REG_AUTO_RGB_MARGIN		0xb802200c
#define  REG_AUTO_ADJ				0xb8022010
#define  REG_AUTO_RESULT_V			0xb8022014
#define  REG_AUTO_RESULT_H			0xb8022018
#define  REG_AUTO_RESULT_PASHE_M	0xb802201c
#define  REG_AUTO_RESULT_PASHE_L	0xb8022020
#define  REG_AUTO_PASHE_CTRL0		0xb8022024


///////////////    ADC Reg     ///////////////////
#define  REG_ADC_OFFSET0 			0xb8020038
#define  REG_ADC_OFFSET1 			0xb802003c

///////////////    SOY Reg     ///////////////////
#define  REG_SOYCH0_A0 			0xb8020300
#define  REG_SOYCH0_A1 			0xb8020304
#define  REG_SOYCH0_A2 			0xb8020308
#define  REG_SOYCH0_A3 			0xb802030c
#define  REG_SOYCH0_A4 			0xb8020310


///////////////   APLL thermal Reg/////////////


#define Thremal_testing 0   //0:480I   1:1080I  2:1080P





/////////////////////////////////////////////////
///////                 For NIKE TX Test             ///////////
/////////////////////////////////////////////////

BOOL YPP_RX_CheckStable(UINT8 SourceType)
{

	UINT32 On_Vsync_total;
	UINT32 On_Vsync;
	UINT32 Off_Vsync_total;
	UINT32 Off_Vsync;
	int i;
	int imd_error=0;


	printk("YPP_RX_CheckStable source type=%x \n",SourceType);	
	switch(SourceType)
		{
		case YPP_480I:
		#include "ypp_adc_480i.tbl"
			udelay(200000);
		#include "apll_ypp480i.tbl"                        // APLL for YPbPr480i source
			udelay(200000);
		#include "sp_480i.tbl" 
			udelay(200000);
		#include "vgip_ch1_ipg_480i.tbl"
			// Enable Online measure
		break;
		case YPP_1080P:
		case YPP_1080I:
			break;
		default:
			break;
		}
		rtd_outl(0xb8021100, 0x00050600);	// Enable Offline measure			
		rtd_outl(0xb8021200, 0x00000600);	// Enable Online measure


	#if 1
////////////////Off line measure/////////////////

	for(i=0;i<3;i++){
	rtd_outl(0xb8021100, 0x00050600);	// Status read of Offline measure		
	udelay(5000);	
	rtd_outl(0xb8021100, 0x00051600);	// Status read of Offline measure

	Off_Vsync_total = rtd_inl(0xb8021104);
	printk("Offline Measure Result :0x%x \n", Off_Vsync_total);

	Off_Vsync = (Off_Vsync_total&0x7ffc0000)>>18;

	switch(SourceType)
		{
		case YPP_480I:
			if((Off_Vsync>=0x104)&&(Off_Vsync<=0x107))
				{		
				printk("Offline Measure Vsync Count total = %x \n",Off_Vsync);
				printk("Timing = 480i \n");
				imd_error |=0;
				}
			else if(i==2)
				{
				printk("Offline Measure Vsync Count total fail resoult=0x%x \n",Off_Vsync);
				imd_error |= 1;
				return 1;
				}
			break;
		case YPP_1080I:
		case YPP_1080P:
			break;
			default:
				break;
		}
	}

	udelay(200000);	
////////////////On line measure/////////////////
	for(i=0;i<3;i++){
	rtd_outl(0xb8021200, 0x00000600);	// Status read of Online measure			
	udelay(5000);	
	rtd_outl(0xb8021200, 0x00001600);	// Status read of Online measure	
	On_Vsync_total = rtd_inl(0xb8021204);
	printk("Online Measure Result :0x%x \n", On_Vsync_total);

	On_Vsync_total = (On_Vsync_total&0x7ffC0000)>>18;
	switch(SourceType)
		{
		case YPP_480I:
			if((Off_Vsync>=0x104)&&(Off_Vsync<=0x107))
				{		
				printk("Offline Measure Vsync Count total = %x \n",Off_Vsync);
				printk("Timing = 480i \n");
				imd_error |=0;
				}
			else if(i==2)
				{		
				printk("Offline Measure Vsync Count total fail resoult=0x%x \n",Off_Vsync);
				imd_error |= 1;
				return 1;
				}
			break;
		case YPP_1080I:
		case YPP_1080P:
			break;
			default:
				break;
		}
	}
	#endif
	
	if(imd_error==0)
	return 0;
else 
	return 1;
}


BOOL IMD_Tst(VOID)
{
	UINT32 abl_result;
	UINT32 sync_type=0;
	UINT32 rgb_data;
	UINT32 R_data;
	UINT32 G_data;
	UINT32 B_data;
	UINT32 ADC_data;
	UINT32 On_Vsync_total;
	UINT32 On_Vsync;
	UINT32 V_temp;
	UINT32 Off_Vsync_total;
	UINT32 Off_Vsync;
	int adc_tolerance=800;  //ADC is 12 bit, 10bit real , center is 0x7ff tolerence is 200*4
	int i;
	int imd_error=0;



// for ESD Pad test -- VGA data
 printk("IMD process 4 VGA path & data \n");
//LVDS_display_set();
// -------- before change apll , should disable abl and apll  
	rtd_outl(0xb8020200, 0x0);
	rtd_outl(0xb8020104, 0x1); //disable apll for re-write
	udelay(200000); 
	rtd_maskl(0xb8033110, 0xFFFFFEFF,0x00000100); // IFD MBIAS power on  PLL 27X power


#include "adc_VGA.tbl"
udelay(20000);
#include "sp_VGA.tbl" 
#include "apll_800600.tbl"                        // VGA 800*600
udelay(20000);

// ====================HS&VS pad check===========================	


rtd_outl(0xb8021070,0x3);
udelay(100000);
if((rtd_inl(0xb8021070)&0x3)==0x3)
{
	printk("HS VS pad is  OK \n");
	
	while((rtd_inl(0xb8021004)&0x80000000)!=0x80000000)
			{
			for (i=0; i<255; i++)	// for delay
				i = i;
			}
	sync_type = rtd_inl(0xb8021004)&0x00000070;
	sync_type = sync_type>>4;
	//ROSPrintf("sync type is :%d\n", sync_type);

	if (sync_type == 6)
	{
		printk("sync type is separate\n");
		//return 1;
	}
	else
	{
		printk("sync type is fail\n");
		return 1;
	}


}
else
{
printk("0xb8021070= 0x%x \n",rtd_inl(0xb8021070));
	printk("VS pad is fail \n");
return 1;
}
#if 0
// ====================RGB pad check===========================	
	udelay(1000000);
	for (i=100; i>0; i--)
	{   
		ADC_data = rtd_inl(0xb8020058);		//read  data
		G_data = (ADC_data&0x00000fff);
		R_data = ((ADC_data>>16)&0x00000fff);
		ADC_data = rtd_inl(0xb802005C);		//read  data
		B_data = ((ADC_data>>16)&0x00000fff);
	
		if ((abs(B_data,0x7ff) < adc_tolerance)&&(abs(G_data,0x7ff) < adc_tolerance)&&(abs(R_data,0x7ff) < adc_tolerance))
		{
			imd_error=0;
			break;
		}
		else			
  			imd_error=1;
	udelay(100);		
	}
	if(imd_error)
		{
		printk("RGB pad is fail!!!!!!! R=0x%x,G=0x%x,B=0x%x\n",R_data,G_data,B_data);
		return 1;
		}
	else
		printk("RGB pad is OK,R=0x%x,G=0x%x,B=0x%x\n",R_data,G_data,B_data);		

#endif


udelay(2000); 

 printk("IMD process 6  YPP\n");
 rtd_outl(0xb8020104, 0x00050609);	 //enable APLL LDO 1.1V power  
 udelay(20000); 

#include "ypp_adc_480i.tbl"
udelay(2500);
#include "apll_ypp480i.tbl"                        // APLL for YPbPr480i source
udelay(2100);
udelay(25000);
rtd_outl(0xb8020104, 0x00050608);	// enable APLL & dual clk

udelay(20000);	

#include "sp_480i.tbl" 
udelay(20000);	

// Enable Offline measure
rtd_outl(0xb8021100, 0x00050600);	// Enable Offline measure
udelay(20000);
//#include "vgip_ch1_ipg_480i.tbl"   //20130324

//#include "vgipch1_480i.tbl"                     // VGIP(ch1) for 480i setting
udelay(20000);	 

// Enable Online measure
rtd_outl(0xb8021200, 0x00000600);	// Enable Online measure



#if 1
udelay(20000);
//#include "vgip_ch1_ipg_480i.tbl"               // vgip ch1 for ipg 480i
//#include "rgb2yuvch1_dis.tbl"                   // rgb2yuv disable   

//#include "uzd_ch1_444_10b_bypass480i.tbl"      // UZD 444 10b bypass , UZD disable

udelay(15000);

rtd_outl(0xb8021200, 0x00001600);	// Status read of Online measure	
udelay(15000);
	On_Vsync_total = rtd_inl(0xb8021204);
	printk("Online Measure Result :0x%x \n", On_Vsync_total);


printk("0xb8020360= 0x%x \n",rtd_inl(0xb8020360));
printk("0xb8020360= 0x%x \n",rtd_inl(0xb8020360));
printk("0xb8020360= 0x%x \n",rtd_inl(0xb8020360));
printk("0xb8020360= 0x%x \n",rtd_inl(0xb8020360));

printk("0xb8021070= 0x%x \n",rtd_inl(0xb8021070));
printk("0xb8021070= 0x%x \n",rtd_inl(0xb8021070));

printk("0xb8021004= 0x%x \n",rtd_inl(0xb8021004));

#include "vgip_ch1_ypp_480i.tbl"               // vgip ch1 for ipg 480i    20130324
	//#include "rgb2yuvch1_dis.tbl"                   // rgb2yuv disable   

printk("Loading...7!\n");

#include "uzd_ch1_444_10b_bypass.tbl"
#include "m_ch1_frc_to_fs.tbl"

printk("Loading...10!\n");

#include "uzu_main_444_480i_to_fhd.tbl"
#include "dpll_297MHz.tbl"
#include "dtg_fhd_fs.tbl"
#include "mtg_fhd.tbl"

printk("Loading...13!\n");


#include "ypp_fs_480i.tbl"
#include "lvds_fhd_1Seg_2Port.tbl"


    	
//=========================================================
//udelay(200000);
//#include "di_bypass.tbl"                    // bypass de-interlace
//udelay(200000);
//#include "m_ch1_frc_1080i10b444.tbl"            // M-domain setting //mark
//#include "uzu_main_444_bypass480i.tbl"
//udelay(200000);
//#include "dpll_297MHz.tbl"
//#include "dtg_fhd_fs.tbl"
//udelay(200000);
//#include "mtg_fhd.tbl"
//udelay(200000);
//#include "ivs2dvs_480i_fhd.tbl"                // ivs2dvs delay for ipg480i to FHD
//#include "m_ch1_frc_to_fs.tbl"      //intinal mark 
//#include "LVDS_FHD_1Pixel_1Seg_2Port.tbl"	// SFG, PIF, TX_PHY
//udelay(200000);
//==============================================================
//#include "dpll_fhd_480i_dibypass.tbl"      // DPLL setting for fhd
//#include "dtg_fhd.tbl"                          // DTG for full hd setting
//#include "mtg_fhd.tbl"                        // MTG for 1920x1080 setting
//#include "uzu_main_444_bypass480i.tbl"         // UZU for 444 bypass , UZU enable
//#include "yuv2rgb_main_en.tbl"                  // yuv 2 rgb main enable
//#include "LVDS_Pin_Share.tbl" 
#else
#include "di_bypass.tbl"                        // DIinterlace bypass	// ok
#include "rgb2yuvch1_dis.tbl"                   // rgb2yuv disable   	// ok
#include "uzd_ch1_444_10bit_480i2sxga.tbl"      // UZD for sxga2sxga setting  // ok
#include "fs10b444.tbl"                         // 444/10 Bit for 480p 1x setting
#include "uzu_main_444_10it_480i2sxga_4PLVDS.tbl"      // UZU for 480i to sxga  // ok
#include "yuv2rgbmain_en.tbl"                   // yuv 2 rgb main enable
#include "dpll_480i_sxga_4PLVDS.tbl"    
#include "dtg_sxga_4PLVDS.tbl"                         // DTG for sxga setting	 // ok
#include "mtg_sxga_4PLVDS.tbl"                         // MTG for sxga setting  // ok
#include "ivs2dvs_480i_sxga_4PLVDS.tbl"                // ivs2dvs delay for 480i_sxga  // ok
#include "LVDS_Pin_Share_4PLVDS.tbl"                        // LVDS Control setting

#endif

#include "ABL_YPP.tbl"


	// ABL status read
	udelay(10000);
	abl_result = rtd_inl(0xb8020208);
	for (i=15000; i>0; i--)
	{   
		if (abl_result == 0x80000007)   // Sirius ABL as same as 55
		{ 
			printk("ABL adjust Pass \n");
			i = 0;
			imd_error = 0;
		} 
		else
		{
		abl_result = rtd_inl(0xb8020208);
		}
		udelay(1000);
	}
	
	if (abl_result != 0x80000007)	// Sirius ABL as same as 55
	{
		printk("ABL adjust Fail abl_result=0x%x \n",abl_result);
		imd_error = 1;
		return 1;
	}


// Measure read
udelay(15000);
////////////////Off line measure/////////////////

	for(i=0;i<3;i++){
	udelay(30000);	
	rtd_outl(0xb8021100, 0x01000600);	// Status read of Offline measure		
	udelay(30000);	
	rtd_outl(0xb8021100, 0x01001600);	// Status read of Offline measure

	Off_Vsync_total = rtd_inl(0xb8021104);
	printk("Offline Measure Result :0x%x \n", Off_Vsync_total);

	Off_Vsync = (Off_Vsync_total&0x7ffc0000)>>18;

	if (Off_Vsync == 0x105)
	{
		printk("Offline Measure Vsync Count total = 261 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
		break;
	}
	else if (Off_Vsync == 0x106)
	{
		printk("Offline Measure Vsync Count total = 262 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
				break;
	}
	else if (Off_Vsync == 0x104)
	{
		printk("Offline Measure Vsync Count total = 260 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
				break;
	}
	else if (Off_Vsync == 0x107)
	{
		printk("Offline Measure Vsync Count total = 263 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
				break;
	}
	else if(i==2)
		{	
			printk("Offline Measure Vsync Count total fail resoult=0x%x \n",Off_Vsync);
			imd_error |= 1;
			return 1;
				}


		}

udelay(25000);	
rtd_outl(0xb8022210, 0x90050001); //VGIP select ADC

////////////////On line measure/////////////////
	for(i=0;i<3;i++){
	udelay(40000);	
	rtd_outl(0xb8021200, 0x00000000);
	udelay(40000);
	rtd_outl(0xb8021200, 0x00000600);	// Status read of Online measure			
	udelay(50000);	
	rtd_outl(0xb8021200, 0x00001600);	// Status read of Online measure	
	udelay(15000);
	On_Vsync_total = rtd_inl(0xb8021204);
	printk("Online Measure Result :0x%x \n", On_Vsync_total);

	On_Vsync_total = (On_Vsync_total&0x7ffC0000)>>18;

	if (On_Vsync_total == 0x105)
	{
		printk("Online Measure Vsync Count total = 261 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
		break;
	}
	else	if (On_Vsync_total == 0x104)
	{
		printk("Online Measure Vsync Count total = 260 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
		break;		
	}
		else	if (On_Vsync_total == 0x106)
	{
		printk("Online Measure Vsync Count total = 262 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
		break;		
	}
		else	if (On_Vsync_total == 0x107)
	{
		printk("Online Measure Vsync Count total = 263 \n");
		printk("Timing = 480i \n");
		imd_error |=0;
		break;
	}
	else if(i==2)
		{
		
			printk("Online Measure Vsync Count total fail resoult=0x%x \n",On_Vsync_total);
			imd_error |= 1;
			return 1;
	}
		
		}


if(imd_error==0)
	return 0;
else 
	return 1;

}

void IPTG_480I()
{


//#include "ddr_init.tbl"

//--

/*-------------------------------------------------------------------------------Sirius Mark Script
#include "case8_ypbpr480i_fs_fhd/apll_ipg480i.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/ipg_480i_QC.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/sp_ipg.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/vgip_ch1_ipg_480i.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/m_ch1_frc_1080i10b444.tbl"	//????
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/uzu_main_444_bypass480i.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/DPLL_297MHz.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/dtg_fhd_fs.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/mtg_fhd.tbl"
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/ivs2dvs_480i_fhd.tbl"		// ivs2dvs delay for ipg1080p to FHD
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/m_ch1_frc_to_fs.tbl"		// mdomain change to fs mode
		udelay(50);
#include "case8_ypbpr480i_fs_fhd/LVDS_FHD_1Seg_2Port.tbl"	// SFG, PIF, TX_PHY
*/  //------------------------------------------------------------------------------------------Sirius Mark Script


//rtd_outl(0xb800DB40, 0x02800202);	//HDMI Bandgap Enable
rtd_outl(0xb802a700, 0x00000040);	//YUV2RGB conversion Disable

}

BOOL IP_ABL_Verify()
{

UINT16  Hsync_Delay=4;
UINT16  Hstart=0,Hact_start=0;
UINT16  Vstart=0,Vact_start=0;
UINT8    reg_conut=0,TestCase=8;

UINT16 R_code,G_code,B_code;	
UINT32 ABL_Hstart,temp,temp1,temp2,i,ii;
bool     Fl_pass=1;
printk("IP_ABL_Verify \n");

              Hstart=rtd_inl(REG_PTG_H_STA_WID)>>16;   // Horizontal active start = 16, active width = 842
              Hact_start=rtd_inl(REG_PTG_HSTA_WID)>>16;   // Pattern Gen display Hstart & Hactive =704 前端留16 piexels 用來判斷porch 
              Vstart=rtd_inl(REG_PTG_V_STA_LEN)>>16;   // Horizontal active start = 16, active width = 842
              Vact_start=rtd_inl(REG_PTG_VSTA_LEN)>>16;   // Pattern Gen display Hstart & Hactive =704 前端留16 piexels 用來判斷porch 

	// abl setup (abl.tbl)
	  	ABL_Hstart=Hact_start-Hsync_Delay-4; // init H window width=4
	  	  printk("ABL_Hstart=0x%x \n",ABL_Hstart);	
for (reg_conut=0;reg_conut<TestCase;reg_conut++)	  	
{
		rtd_outl(REG_PTG_TG, 0x40000003);   // Enable timing generator
		rtd_outl(REG_PTG_TOTALHV, 0x035a0106);   // Total pixel = 858*262
		rtd_outl(REG_PTG_H_STA_WID, 0x0010034a);   // Horizontal active start = 16, active width = 842
		rtd_outl(REG_PTG_V_STA_LEN, 0x00050101);   // Vertical active start = 5, active width = 257
		rtd_outl(REG_PTG_HSTA_WID, 0x009102c0);   // Pattern Gen display Hstart & Hactive =704 前端留16 piexels 用來判斷porch 
		rtd_outl(REG_PTG_VSTA_LEN, 0x001000f0);   // Pattern Gen display Vstart & Vactive
		rtd_outl(REG_PTG_CTRL, 0x00000003);   // PTG control, select pattern = Color Bar 
		rtd_outl(REG_PTG_BARW, 0x00000059);   // Color bar width  =59
		rtd_outl(REG_PTG_C0Y, 0x00ffffff);   // active region color 
		rtd_outl(REG_PTG_C2Y, 0x00010101);   // porch region color 101=5           10 bit color=5
		rtd_outl(REG_PTG_MAX_COLOR_CTRL, 0x00000fff);   // color set (copy from defualt value) 1 coloe
		rtd_outl(REG_PTG_TG, 0x4000003);   // Enable timing generator
		udelay(10000);
		rtd_outl(REG_ABL_WINDOW, (0x07818300|(ABL_Hstart/3)));  // 1/3 porch
		rtd_outl(REG_ABL_STATUS, 0x80000000);
		rtd_outl(REG_ABL_CTRL, 0x808a0100);
		rtd_outl(REG_ABL_MGN_RG, 0x00440044);	
		rtd_outl(REG_ABL_MGN_B, 0x00000044);	
		udelay(10000);
		
	switch(reg_conut)		
	{
		case 0://  min/avg  measure meathod 
				rtd_outl(REG_ABL_WINDOW, (0x07818300|(ABL_Hstart+2)));  // window cross porch & active
				udelay(100000);
				R_code=rtd_inl(REG_ABL_RSLT0)>>16;
				G_code=rtd_inl(REG_ABL_RSLT0)&(0x0000ffff);
				B_code=rtd_inl(REG_ABL_RSLT1)&(0x0000ffff);
		              if( (R_code==0x202)&&(G_code==0x202) &&(B_code==0x202) ) //measure  AVG
		              	{
							rtd_outl(REG_ABL_CTRL, rtd_inl(REG_ABL_CTRL)|_BIT25);	
							udelay(10000);
					  		R_code=rtd_inl(REG_ABL_RSLT0)>>16;
							G_code=rtd_inl(REG_ABL_RSLT0)&(0x0000ffff);
							B_code=rtd_inl(REG_ABL_RSLT1)&(0x0000ffff);
					              if( (R_code==0x5)&&(G_code==0x5) &&(B_code==0x5) )  //measure  min					
		            				printk("IP_ABL,avg/min  measure PASS!! \n");	
							else
								{
							printk("IP_ABL,avg measure fail 1 R=0x%x,G=0x%x,B=0x%x! \n",R_code,G_code,B_code);		
							Fl_pass=FALSE;
								}
		              	}
				else	  
					{
						printk("IP_ABL,min measure fail 2 R=0x%x,G=0x%x,B=0x%x! \n",R_code,G_code,B_code);	
						Fl_pass=FALSE;
					}
		break;		
		case 1://diff
				R_code=rtd_inl(REG_ABL_NOISE_VAL0)>>16; //diff
				G_code=rtd_inl(REG_ABL_NOISE_VAL0)&(0x0000ffff);//diff
				B_code=rtd_inl(REG_ABL_NOISE_VAL1)&(0x0000ffff);//diff

				if(((R_code+(rtd_inl(REG_ABL_RSLT0)>>16))==8)&&
				    ((G_code+(rtd_inl(REG_ABL_RSLT0)&0x0000ffff))==8)&&
				    ((B_code+(rtd_inl(REG_ABL_RSLT1)&0x0000ffff))==8))
          			printk("IP_ABL,diff  measure PASS!! \n");	
				else
					{
					printk("IP_ABL,diff R=0x%x,G=0x%x,B=0x%x! \n",R_code,G_code,B_code);
					Fl_pass=FALSE;
					}
				
				
		break;
		case 2://target
				rtd_outl(REG_ABL_CTRL, rtd_inl(REG_ABL_CTRL)&(0xfffff000&(0<<8)));
				udelay(20000);	
				R_code=rtd_inl(REG_ABL_RSLT0)>>16;
				G_code=rtd_inl(REG_ABL_RSLT0)&(0x0000ffff);
				B_code=rtd_inl(REG_ABL_RSLT1)&(0x0000ffff);

				for(i=0;i<16;i++)
					{
					rtd_outl(REG_ABL_CTRL, (rtd_inl(REG_ABL_CTRL)&(0xfffff000&(i<<8))));
					udelay(10000);	
				
					if(!(((rtd_inl(REG_ABL_NOISE_VAL0)>>16)==abs(R_code,4*i))&&
						((rtd_inl(REG_ABL_NOISE_VAL0)&0x0000ffff)==abs(G_code,4*i))&&
						((rtd_inl(REG_ABL_NOISE_VAL1)&(0x0000ffff))==abs(B_code,4*i))))
						{
         		 			printk("IP_ABL,target value i=%d fail!! \n",i);	
						Fl_pass=FALSE;
						break;
						}				         		 	
					}
					printk("IP_ABL,target value Pass!! \n");
				
		break;
		
		case 3://vga/ypp mode Pos_Neg pin select
				temp=rtd_inl(REG_ABL_STATUS)&0x00000007;
				if(temp==7)
					{

					rtd_outl(REG_ABL_CTRL, rtd_inl(REG_ABL_CTRL)|(_BIT24));
					udelay(10000);	
								temp=rtd_inl(REG_ABL_STATUS)&0x00000007;
								if(temp==2)
									printk("IP_ABL,YPP/VGA mode & Pos_Neg pin select Pass!! \n");
								else
									{
									printk("IP_ABL,YPP/VGA mode & Pos_Neg pin selectFail 1!! \n");	
									Fl_pass=FALSE;
									}
					}
				else
					{
					printk("IP_ABL,YPP/VGA mode Fail 2!! \n");	
					Fl_pass=FALSE;
					}				
		break;
		case 4://offline & frame	 ABL_EN	
				rtd_outl(REG_PTG_C0Y, 0x00101010);   // active region color 
				rtd_outl(REG_ABL_WINDOW, (0x07818300|(ABL_Hstart+1)));  // window cross porch & active
				    for(i=0;i<4;i++)
					{
					rtd_outl(REG_ADC_OFFSET0, 0x00000000);   //offset to default				
					rtd_outl(REG_ADC_OFFSET1, 0x00000000);   //offset to default	
					udelay(100000);	
					rtd_outl(REG_ABL_CTRL, (0x70000100|(i<<20))); //off line mode, frame=4
					udelay(10000);
					rtd_outl(REG_ABL_CTRL, (0xf0000100|(i<<20))); //off line mode, frame=4
					udelay(300000);	
					temp=(rtd_inl(REG_ADC_OFFSET0)&0x0000ffff)-0x000;
					if(!((temp)==((i+5)*(rtd_inl(REG_ABL_MGN_RG)&0x00003e0)>>5)))
						{
                                         	printk("IP_ABL,Offline&frame mode &ABL_EN Fail  i =%d!! \n",i);	
						printk("temp=%d !! \n",temp);	
						printk("resoult=%d !! \n",(rtd_inl(REG_ABL_NOISE_VAL0)&0x0000ffff));												
						Fl_pass=FALSE;
						break;
						}
					}
				if(Fl_pass!=FALSE)
					printk("IP_ABL,offline&framemode & ABL_EN  PASS !! \n");	
				break;	
									
			
		case 5://Online mode
					rtd_outl(REG_ADC_OFFSET0, 0x00000000);   //offset to default				
					rtd_outl(REG_ADC_OFFSET1, 0x00000000);   //offset to default	
					udelay(100000);	
					rtd_outl(REG_ABL_CTRL, 0xf0800100); //off line mode, frame=4
					udelay(2000000);	
					

					R_code=(rtd_inl(REG_ADC_OFFSET0)&0x0000ffff);	
					G_code=(rtd_inl(REG_ADC_OFFSET0)>>16)&0x0000ffff;	
					B_code=rtd_inl(REG_ADC_OFFSET1)&0x0000ffff;	
					if((R_code!=0x7ff)||(G_code!=0x7ff)||(B_code!=0x7ff))
						{
						printk("IP_ABL,Online mode Fail  !! \n");	
						printk("R_code=%d,G_code=%d,B_code=%d, !! \n",R_code,G_code,B_code);	
						Fl_pass=FALSE;						
						break;
						}
									
					printk("IP_ABL,online mode PASS !! \n");									
			break;
			
		case 6:// Hs leading/trailing
				rtd_outl(REG_ABL_WINDOW, (0x07818300|(ABL_Hstart)));  // window cross porch & active
				udelay(20000);
				R_code=rtd_inl(REG_ABL_RSLT0)>>16;
				G_code=rtd_inl(REG_ABL_RSLT0)&(0x0000ffff);
				B_code=rtd_inl(REG_ABL_RSLT1)&(0x0000ffff);
		              if( (R_code==5)
&&(G_code==5) &&(B_code==5) ) //leading edge
		              	{
							rtd_outl(REG_ABL_CTRL, rtd_inl(REG_ABL_CTRL)|(_BIT16));	
							udelay(20000);
					  		R_code=rtd_inl(REG_ABL_RSLT0)>>16;
							G_code=rtd_inl(REG_ABL_RSLT0)&(0x0000ffff);
							B_code=rtd_inl(REG_ABL_RSLT1)&(0x0000ffff);
							udelay(20000);
					              if( (R_code==0x3FF)
&&(G_code==0x3FF) &&(B_code==0x3FF) )  //Trailing edge
             		            				printk("IP_ABL, Hsync leading/trailing edge  PASS!! \n");	
							else	
								{
								printk("IP_ABL, Hsync leading/trailing edge  Fail!! R=%d,G=%d,B=%d \n",R_code,G_code,B_code);	
								Fl_pass=FALSE;
								}
		              	}
				  break;
		case 7: //H window
				rtd_outl(REG_PTG_CTRL, 0x00000004);   // H gradient
				rtd_outl(REG_PTG_C3Y, 0x28282800);   //  neg adj 24
				rtd_outl(REG_PTG_C4Y, 0x0F000000);   // every 8 pixel
				udelay(2000);
				temp=1023;
				for (i=0;i<3;i++)
					{
				rtd_outl(REG_ABL_WINDOW,( (0x07818000|(ABL_Hstart+4))|(i<<8)));  // 4 pixel in front of data
				udelay(20000);
				R_code=rtd_inl(REG_ABL_RSLT0)>>16;
				G_code=rtd_inl(REG_ABL_RSLT0)&(0x0000ffff);
				B_code=rtd_inl(REG_ABL_RSLT1)&(0x0000ffff);			
				temp=temp-12*i;
		              if( !((R_code==temp)&&(G_code==temp) &&(B_code==temp) ))
		              	{
					printk("IP_ABL, H window  Fail!! R=%d,G=%d,B=%d \n",R_code,G_code,B_code);
					Fl_pass=FALSE;
					  break;

		              	}
				}
					

				temp=0x3ff;
				for (i=0;i<3;i++)
					{
				rtd_outl(REG_ABL_WINDOW,( (0x07818300|((ABL_Hstart+7)/2))|(i<<30)));  // 4 pixel in front of data
				udelay(20000);
				if(i==0)
				temp2=1;
				else if(i==1)
				temp2=2;
				else if(i==2)
				temp2=4;
				else
				temp2=8;				
				
				temp1=(rtd_inl(REG_ABL_WINDOW)&0xff)*temp2;
				if((temp1+4)<(ABL_Hstart+4))
				temp=((rtd_inl(REG_PTG_C2Y)&0xff)<<2)|(rtd_inl(REG_PTG_C2Y)&0x3);// 10 it data lsb 2 bit repeat
				else
				temp=0x3ff-((temp1-(ABL_Hstart+4))/16)*24;
				
				R_code=rtd_inl(REG_ABL_RSLT0)>>16;
				G_code=rtd_inl(REG_ABL_RSLT0)&(0x0000ffff);
				B_code=rtd_inl(REG_ABL_RSLT1)&(0x0000ffff);			
		              if( !((R_code==temp)
&&(G_code==temp) &&(B_code==temp) ))
		              	{
					printk("IP_ABL, H window  pos_mul Fail!! R=%d,G=%d,B=%d,ABL_Hstart=%x,temp=%x,temp1=%x \n",R_code,G_code,B_code,ABL_Hstart,temp,temp1);
					Fl_pass=FALSE;
					  break;

		              	}
				}
				if(Fl_pass==TRUE)
				printk("IP_ABL, H window & pos_mul Pass \n");					
			break;

			
		case 8: //V window
				rtd_outl(REG_PTG_TG, 0x40000002);   // Disable timing generator
				rtd_outl(REG_PTG_VSTA_LEN, 0x001900f0);   // V datastart move to line 25
				rtd_outl(REG_PTG_TG, 0x40000003);   // Enable timing generator				
				udelay(20000);
				rtd_outl(REG_ABL_CTRL, 0x008a0100);
				rtd_outl(REG_ABL_WINDOW, (0x01818300|(ABL_Hstart+4)));  // at  the edge of H,V data, H width =4
																// Vstart=24, end=48 & measure=8 lines, interval=16 lines
				rtd_outl(REG_ABL_CTRL, 0x808a0100);															     
				udelay(20000);
				
				R_code=rtd_inl(REG_ABL_RSLT0)>>16;
				if (R_code==0x3ff)
					{
					rtd_outl(REG_ABL_WINDOW, (0x00f16300|(ABL_Hstart+4)));  // move V start=22 ,end=46
					udelay(20000);
					R_code=rtd_inl(REG_ABL_RSLT0)>>16;
					if((R_code==0x301)|(R_code==0x300)) //(1023*6*4+5*2*4)/8*4      average value
				       printk("IP_ABL, V start/end  Pass \n");		
					else						
						{
						printk("IP_ABL, V start/end  fail1 R_code=0x%x\n",R_code);	
						Fl_pass=FALSE;
						break;
						}
					}
				else
					{
						printk("IP_ABL, V start/end  fail2 R_code=0x%x \n",R_code);	
						Fl_pass=FALSE;						
						break;	
					}
				temp=8;
				for(i=1;i<4;i++) //avg line count
					{
					temp=temp*2;
					rtd_outl(REG_ABL_WINDOW,(((rtd_inl(REG_ABL_WINDOW)&0xfffff3ff)|(i<<10))&0x000fffff)|(((temp+22+16)/2)<<20));  // move V start=22 ,end=54
					rtd_outl(REG_ABL_CTRL,(rtd_inl(REG_ABL_CTRL)&~_BIT31));
					udelay(100);
					rtd_outl(REG_ABL_CTRL,(rtd_inl(REG_ABL_CTRL)|_BIT31));
					udelay(60000);
//					printk("IP_ABL, 0x%x \n", rtd_inl(REG_ABL_WINDOW));			
					R_code=rtd_inl(REG_ABL_RSLT0)>>16;	
					G_code=(40+(temp-2)*4*1023)/(temp*4);
					temp1=abs(R_code,G_code);
					if(temp1>3)
						{
						printk("IP_ABL, V avg line fail  i=%d, Result=0x%x,Target=0x%x \n",abs(R_code,G_code),R_code,G_code);	
						Fl_pass=FALSE;						
						break;
						}
					}
				break;
		case 9:  //test MGN  in VGA mode
				rtd_outl(REG_PTG_C0Y, 0x00101010);   // active region color 
				rtd_outl(REG_ABL_WINDOW, (0x07818300|(ABL_Hstart)));  // window cross porch & active
				rtd_outl(REG_ABL_MGN_RG, 0x10841084);  // MGN
				rtd_outl(REG_ABL_MGN_B, 0x00001084);  // MGN

				for(i=0;i<3;i++)  // for R G B 3 color
					{
					rtd_outl(REG_ABL_MGN_RG, 0x10841084);  // MGN
					rtd_outl(REG_ABL_MGN_B, 0x00001084);  // MGN
					rtd_outl(REG_ABL_CTRL, 0x80800100); 
					udelay(20000);	
					rtd_outl(REG_ADC_OFFSET0, 0x00000000);   //offset to default				
					rtd_outl(REG_ADC_OFFSET1, 0x00000000);   //offset to default	
					udelay(100000);	
					rtd_outl(REG_ABL_CTRL, 0x80800100|(1<<(30-i))); //off line mode, frame=4
					udelay(500000);
					
					if(i==0)
					temp=(rtd_inl(REG_ADC_OFFSET0)&0x0000ffff)-0x000;		
					else if(i==1)
					temp=((rtd_inl(REG_ADC_OFFSET0)&0xffff0000)>>16)-0x000;						
					else
					temp=(rtd_inl(REG_ADC_OFFSET1)&0x0000ffff)-0x000;					
					
					if(temp==0)	//EQ_MGN,adjust 1step=1
						{
						rtd_outl(REG_ABL_MGN_RG, 0x00840084);  // window cross porch & active
						rtd_outl(REG_ABL_MGN_B, 0x00000084);  // window cross porch & active					
						udelay(10000);	
						
						if(i==0)
						temp1=rtd_inl(REG_ADC_OFFSET0)&0x0000ffff;
						else if(i==1)
						temp1=(rtd_inl(REG_ADC_OFFSET0)&0xffff0000)>>16;						
						else
						temp1=rtd_inl(REG_ADC_OFFSET1)&0x0000ffff;					
						
				       if(temp1>0x400) // [10]=sign bit:neg value direction
						printk("IP_ABL, color(R=0,G=1,B=2)=%d EQ_MGN Pass temp1=0x%x! \n",i,temp1);					
						else
							{
							printk("IP_ABL, color(R=0,G=1,B=2)=%d EQ_ERROR_MGN fail1 result=0x%x! \n",i,temp1);
							Fl_pass=FALSE;							
							break;
							}
						}
					else
						{
						printk("IP_ABL,color(R=0,G=1,B=2)=%d EQ_ERROR_MGN fail2 result=0x%x! \n",i,temp1);	
						Fl_pass=FALSE;						
						break;
						}


					//Large_error_MGN,  adjust 1step=LG_error_MGN
					rtd_outl(REG_ABL_CTRL, 0x80800100); //off line mode, frame=4
					rtd_outl(REG_ADC_OFFSET0, 0x00000000);   //offset to default				
					rtd_outl(REG_ADC_OFFSET1, 0x00000000);   //offset to default	
					udelay(100000);	
					rtd_outl(REG_ABL_MGN_RG, 0x00440044);  // window cross porch & active
					rtd_outl(REG_ABL_MGN_B, 0x00000044);  // window cross porch & active	
					rtd_outl(REG_ABL_CTRL, 0x80800100|(1<<(30-i))); //off line mode, frame=4
					udelay(10000);	
					
					if(i==0)
					temp=rtd_inl(REG_ADC_OFFSET0)&0x0000ffff;
					else if(i==1)
					temp=(rtd_inl(REG_ADC_OFFSET0)&0xffff0000)>>16;						
					else
					temp=rtd_inl(REG_ADC_OFFSET1)&0x0000ffff;					
					
				       if(temp1>0x400) // [10]=sign bit:neg value direction
						printk("IP_ABL,color(R=0,G=1,B=2) =%d LG_MGN Pass result=0x%x,temp1=0x%x ! \n",i,temp,temp1);										
					else
						{
						printk("IP_ABL,colo(R=0,G=1,B=2) r=%d LG_MGN fail result=0x%x,temp1=0x%x   ! \n",i,temp,temp1);	
						Fl_pass=FALSE;						
						break;
						}
					}
		default:
			break;									
		}
	if (Fl_pass==FALSE)
		break;
	}
if (Fl_pass==FALSE)
	return 0;
else
	return 1;
}

BOOL IP_SF_Verify()
{
UINT8    test_count=0,test_case=6;

UINT32  temp,temp1,i;
bool     Fl_pass=1;

printk("IP_SF_Verify  \n");
//IPTG  Total pixel = 858*262, H start 145 ,width 704, V start 16 active 240


for(test_count=0;test_count<test_case;test_count++)
{
rtd_outl(0xb8022210, 0x90000001);	 //VGIP enable 
rtd_outl(REG_PTG_C0Y, 0x00ffffff);//R=0x1ff,G=0x3ff B=0x2ff
rtd_outl(REG_AUTO_H_BOUNDARY, 0x00500359);//set H  boudary , start 80 end 858
rtd_outl(REG_AUTO_V_BOUNDARY, 0x00020106);//set V  boudary , start 2 end 262
rtd_outl(REG_AUTO_RGB_MARGIN, 0x04040400);//Noise MGN 0
rtd_outl(REG_AUTO_ADJ, 0);//reset adj
rtd_outl(REG_AUTO_FIELD, 0);//reset field
rtd_outl(0xb8023500, 0x0);//Disable dither
rtd_outl(0xb8023504, 0x0);//diable Dither
	switch(test_count)
		{
			case 0:// test H V boundary & Result HV start/end
				rtd_outl(REG_AUTO_RGB_MARGIN, 0);			
				rtd_outl(REG_AUTO_ADJ, _BIT0);
				udelay(100000);	
				temp=abs(rtd_inl(REG_AUTO_V_BOUNDARY),rtd_inl(REG_AUTO_RESULT_V)); //interlace  1 line diff between even/odd
				if((rtd_inl(REG_AUTO_H_BOUNDARY)==rtd_inl(REG_AUTO_RESULT_H))&&
					(temp<=1))
					
					printk("IP_SF_Verify, HV boundary & Result Pass \n");
				else
					{
					printk("IP_SF_Verify, HV boundary & Result fail H boundary=0x%x,V_boundary=0x%x\n",rtd_inl(REG_AUTO_RESULT_H),rtd_inl(REG_AUTO_RESULT_V));
					Fl_pass=FALSE;	
					break;
					}
				rtd_outl(REG_AUTO_RGB_MARGIN, 0x04040400);//Noise MGN 0
				rtd_outl(REG_AUTO_ADJ, _BIT0);
				udelay(100000);	
				if(((rtd_inl(REG_PTG_HSTA_WID)>>16)==((rtd_inl(REG_AUTO_RESULT_H)>>16)+1))&&   //IPTG H active start
				    ((rtd_inl(REG_PTG_HSTA_WID)&0x0000ffff)==(rtd_inl(REG_AUTO_RESULT_H)&0x0000fff)-(rtd_inl(REG_AUTO_RESULT_H)>>16)+1)) //IPGT H width
					printk("IP_SF_Verify, RGB MGN PASS \n");
				else
					{
					printk("IP_SF_Verify, RGB MGN fail =0x%x\n",rtd_inl(REG_AUTO_RESULT_H) );
					Fl_pass=FALSE;						
					break;
					}	
	
				break;
			case 1: //Odd sel en
				rtd_outl(0xb8022210, 0x90000101);	 //VGIP enable  safe-mode->Odd off
				rtd_outl(REG_AUTO_FIELD, (_BIT7|_BIT6));	 //mesaure odd
				udelay(100000);	
				rtd_outl(REG_AUTO_ADJ, _BIT0);	 //Enable measue		
				udelay(100000);	
				if(rtd_inl(REG_AUTO_ADJ)==0)
					{
						printk("IP_SF_Verify, odd sel fail1 0x%x\n",rtd_inl(REG_AUTO_ADJ));							
						Fl_pass=FALSE;
						break;						
					}
				else
				rtd_outl(REG_AUTO_FIELD, _BIT7);	 //VGIP enable  safe-mode->Odd off
					udelay(10000);	
				rtd_outl(REG_AUTO_ADJ, _BIT0);	 //Enable measue		
				udelay(100000);	
				if(rtd_inl(REG_AUTO_ADJ)!=0)
					{
						printk("IP_SF_Verify, odd sel fail2 x\n",rtd_inl(REG_AUTO_ADJ));							
						Fl_pass=FALSE;
						break;						
					}
				printk("IP_SF_Verify, odd sel PASS \n");							

				// pulse_det_en & phase/balance mode
			       rtd_outl(REG_AUTO_H_BOUNDARY, 0x00900091);//set H  boudary , measure only two vertical line  color black->white
				rtd_outl(REG_AUTO_V_BOUNDARY, rtd_inl(REG_AUTO_RESULT_V));
				rtd_outl(REG_AUTO_ADJ,_BIT6| _BIT5|_BIT4|_BIT1);	 //difference&MAX&Acc&Phase		
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)|_BIT0);	 //Enable measue						
				udelay(100000);	
				temp=rtd_inl(REG_AUTO_RESULT_PASHE_L);  //V active* (1023-5)  sum of difference

				rtd_outl(REG_AUTO_ADJ,_BIT6|_BIT5|_BIT4|_BIT3|_BIT1);	    ////difference&MAX&Acc&Phase  + pulse_det_en result will be double
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)|_BIT0);	 //Enable measue						
				udelay(100000);	
				temp1=rtd_inl(REG_AUTO_RESULT_PASHE_L);				
				if (temp*2==temp1)
				printk("IP_SF_Verify, pulse_det_en PASS \n");												
				else
				{
				printk("IP_SF_Verify, pulse_det_en fail 0x%x\n", temp1);				
				Fl_pass=FALSE;
				}
				break;
				
			case 2://RGB_in_one_en & square_en
			        //Measure R
				rtd_outl(REG_AUTO_RGB_MARGIN, 0x00000000);//Noise MGN 0
				rtd_outl(REG_AUTO_ADJ, _BIT4);	 //differ & accu
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp=rtd_inl(REG_AUTO_RESULT_PASHE_L);
			        //Measure G
				rtd_outl(REG_AUTO_RGB_MARGIN, 0x00000100);//Noise MGN 0
				rtd_outl(REG_AUTO_ADJ, _BIT4);	 //differ & accu
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp=temp+rtd_inl(REG_AUTO_RESULT_PASHE_L);
			        //Measure B
				rtd_outl(REG_AUTO_RGB_MARGIN, 0x00000200);//Noise MGN 0
				rtd_outl(REG_AUTO_ADJ, _BIT4);	 //differ & accu
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp=temp+rtd_inl(REG_AUTO_RESULT_PASHE_L);


				rtd_outl(REG_AUTO_FIELD,_BIT4);	 //RGB together
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp1=rtd_inl(REG_AUTO_RESULT_PASHE_L);
				
				if(abs(temp,temp1)<0x0000100)
				printk("IP_SF_Verify, RGB_in_one_en  PASS,SumRGB=%x,in_one=%x \n",temp,temp1);
				else
					{
					printk("IP_SF_Verify, RGB_in_one_en  fail ,temp=0x%x,temp1=0x%x\n",temp,temp1);
					printk("fail ,b8022010=0x%x,b8022000=0x%x\n",rtd_inl(REG_AUTO_ADJ),rtd_inl(REG_AUTO_FIELD));
					//printk("fail ,temp=0x%x,temp1=0x%x\n",temp,temp1);
					Fl_pass=FALSE;
					break;
					}
				rtd_outl(REG_AUTO_FIELD,_BIT4|_BIT3);	 //RGB together/square_en
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp1=rtd_inl(REG_AUTO_RESULT_PASHE_L);
				rtd_outl(REG_AUTO_RGB_MARGIN, 0x04040400);//Noise MGN 0
				
				if(temp<temp1)					
					printk("IP_SF_Verify, square_en  PASS \n");
				else
					{
					
					printk("IP_SF_Verify, square_en  fail temp1=%x\n",temp1);
					Fl_pass=FALSE;
					break;
					}
				break;
			case 3: //sum of pixel  &  even/odd pixel

			       // sum of pixel
			       rtd_outl(REG_AUTO_H_BOUNDARY, 0x00900091);//set H  boudary , measure only two vertical line
   				rtd_outl(REG_AUTO_FIELD, _BIT2);	 //pixel number mode
 				rtd_outl(REG_AUTO_ADJ, _BIT6|_BIT4);	 //pixel number mode
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp=rtd_inl(REG_AUTO_RESULT_PASHE_L);
				temp1=abs(temp,(((rtd_inl(REG_AUTO_H_BOUNDARY)&0x0000ffff)-(rtd_inl(REG_AUTO_H_BOUNDARY)>>16)+1)* 
						  ((rtd_inl(REG_AUTO_V_BOUNDARY)&0x0000ffff)-(rtd_inl(REG_AUTO_V_BOUNDARY)>>16)+1)));
				if(temp1<=2)
					printk("IP_SF_Verify, sum_pixel_num  PASS \n");
				else
					{
					printk("IP_SF_Verify, sum_pixel_num fail \n");
					Fl_pass=FALSE;
					break;
					}			
				// even/odd pixel
				rtd_outl(REG_AUTO_RGB_MARGIN, 0x07040400);//Noise MGN 0
				udelay(10000);
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				if(((temp/2)+2)>rtd_inl(REG_AUTO_RESULT_PASHE_L))
					printk("IP_SF_Verify, even/odd pixel select  PASS \n");
				else
					{
					printk("IP_SF_Verify, even/odd pixel select  fail 0x%x\n",rtd_inl(REG_AUTO_RESULT_PASHE_L));
					Fl_pass=FALSE;
					}
				break;
				
			case 4: // compare mode / color select  & MAX/MIN
				rtd_outl(REG_PTG_C0Y, 0x00ff7fbf);//IPTG R=0x1ff,G=0x3ff B=0x2ff
				rtd_outl(REG_AUTO_H_BOUNDARY, 0x009300B0);				
				rtd_outl(REG_AUTO_ADJ, _BIT6|_BIT5);//compare mode & max color
				for(i=0;i<3;i++)
					{
					rtd_outl(REG_AUTO_RGB_MARGIN, 0x04040400|(i<<8));//IPTG R=0x1ff,G=0x3ff B=0x2ff
					udelay(10000);
					rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
					udelay(100000);	
					if((rtd_inl(REG_AUTO_RESULT_PASHE_L)>>8)!=(i+1))
						{
						printk("IP_SF_Verify, color select MAX fail i (R=0,B=1,G=2)=%d,0x%x\n",i,rtd_inl(REG_AUTO_RESULT_PASHE_L));						
						Fl_pass=FALSE;
						break;
						}
					}
						printk("IP_SF_Verify, color select & compare mode MAX  PASS\n");						

				// MIN		
				rtd_outl(REG_AUTO_ADJ, _BIT6);//compare mode & max color						

				rtd_outl(REG_AUTO_V_BOUNDARY, 0x00040104);//set V  boudary , start 2 end 262
				udelay(10000);					
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp=(~(rtd_inl(REG_AUTO_RESULT_PASHE_L)))&0x000003ff;
				if( temp==5)
						printk("IP_SF_Verify, color select & compare mode MIN  PASS\n");
				else
					{
						printk("IP_SF_Verify, color select & compare mode MIN  fail 0x%x \n",temp);
						Fl_pass=FALSE;
					}
				break;
			case 5:
				// diff_pixel_sel->value
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);
			       rtd_outl(REG_AUTO_H_BOUNDARY, 0x00910091);//set H  boudary , measure only one vertical line				
			       rtd_outl(REG_AUTO_V_BOUNDARY, rtd_inl(REG_AUTO_RESULT_V));//set H  boudary to active size ,and  measure only one vertical line							       
 				rtd_outl(REG_AUTO_ADJ, _BIT4);	 //select pixel value & acc mode
				udelay(10000);	
				rtd_outl(REG_AUTO_ADJ,rtd_inl(REG_AUTO_ADJ)| _BIT0);	 //Enable measue		
				udelay(100000);	
				temp=rtd_inl(REG_AUTO_RESULT_PASHE_L);
				temp1=(0x3ff*((rtd_inl(REG_AUTO_RESULT_V)&0x0000ffff)-(rtd_inl(REG_AUTO_RESULT_V)>>16)+1) );
				if(temp== temp1)
					printk("IP_SF_Verify, diff_pixel_sel  PASS \n");				
				else
				{
					printk("IP_SF_Verify, diff_pixel_sel  fail 0x%x target=0x%x \n",temp,temp1);				
					Fl_pass=FALSE;
					break;
				}				
				break;
			case 6://auto phase				
				break;
			default:			
				break;
		}
		if (Fl_pass==FALSE)
		break;
}
if (Fl_pass==FALSE)
	return 0;
else
	return 1;

}


BOOL IP_SP_Verify()
{
UINT8    test_count=0,test_case=7,i;
UINT32  temp;
bool     Fl_pass=1;

printk("IP_SP_Verify  \n");



//IPTG  Total pixel = 858*262, H start 145 ,width 704, V start 16 active 240
for(test_count=0;test_count<test_case;test_count++)
{
		rtd_outl(0xb8021000,0);// source select PTG ,decomp disable (de_hs=hs_raw,de_vs=vs_raw)
		rtd_outl(REG_PTG_TG,(rtd_inl(REG_PTG_TG)&0xfffffffd));   // Set progressive							
		switch(test_count)
			{
			case 0: //offline measure
				rtd_outl(0xb8021000,0);// source select PTG ,decomp disable (de_hs=hs_raw,de_vs=vs_raw)
				udelay(1000);	
				rtd_outl(REG_SP_MS3CTRL ,_BIT9|_BIT10);//auto mode , enable
				udelay(100000);		
				rtd_outl(REG_SP_MS3CTRL ,_BIT9|_BIT10|_BIT12);//pop up
				udelay(200000);	
				temp=rtd_inl(REG_SP_MS3CTRL);

				if(temp&0x00200000)
					printk("IP_SP_Offline_Verify, off_ms_now  PASS \n");				
				else{
					printk("IP_SP_Offline_Verify, off_ms_now  Fail,temp=0x%x \n",temp);					
					Fl_pass=FALSE;
					break;
					}

				udelay(200000);		
				temp=rtd_inl(REG_SP_MS3RST0);
				temp=abs(((temp&0x7ffc0000)>>18),(rtd_inl(REG_PTG_TOTALHV)&0x00000fff));
				if(temp<=1)
					printk("IP_SP_Offline_Verify, V period  PASS \n");						
				else{
					printk("IP_SP_Offline_Verify, V period  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					break;
					}

			
				temp=rtd_inl(REG_SP_MS3RST0);
				temp=abs(((temp&0x0000fff0)>>4),2*((rtd_inl(REG_PTG_TOTALHV)&0x0fff0000)>>16));	
				if(temp<=3)
					printk("IP_SP_Offline_Verify, H period  PASS \n");						
				else{
					printk("IP_SP_Offline_Verify, H period  fail , temp=0x%x,measure=0x%x,IPTG=0x%x\n",temp,rtd_inl(REG_SP_MS3RST0),rtd_inl(REG_PTG_TOTALHV));									
					Fl_pass=FALSE;
					break;
					}


				temp=rtd_inl(REG_SP_MS3RST1);
				temp=abs((temp&0x0000ffff),2*16*(((rtd_inl(REG_PTG_TG)&0x00000300)>>8)+1));	
				if(temp<=3)
					printk("IP_SP_Offline_Verify, H high period  PASS \n");						
				else{
					printk("IP_SP_Offline_Verify, H high period  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					break;
					}

				temp=rtd_inl(REG_SP_MS3RST1);
				temp=abs(((temp&0x0fff0000)>>16),4);	
				if(temp<=3)
					printk("IP_SP_Offline_Verify, V high period  PASS \n");						
				else{
					printk("IP_SP_Offline_Verify, V high period  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					break;					
					}		
				break;

			case 2: //Off line measure source
				rtd_outl(0xb8021000,0x400);// SP1 source select PTG ,decomp enable (de_hs!=hs_raw,de_vs!=vs_raw)				
//				rtd_outl(0xb8021000,0x400);// SP1 source select PTG ,decomp enable (de_hs!=hs_raw,de_vs!=vs_raw)				

				
				udelay(3000);				
				for(i=0;i<8;i++)
					{
					rtd_outl(REG_SP_MS3CTRL ,(i<<16)|_BIT9|_BIT10);//auto mode , enable
					udelay(30000);		
					rtd_outl(REG_SP_MS3CTRL ,(i<<16)|_BIT9|_BIT10|_BIT12);//pop up
					udelay(30000);
					temp=rtd_inl(REG_SP_MS3RST0);
					if((i!=2)&&(i!=3)&&(i!=6)&&(i!=7))//no sp2
						{
							temp=abs(((temp&0x7ffc0000)>>18),(rtd_inl(REG_PTG_TOTALHV)&0x00000fff));
							if(temp>1)
							{
								printk("IP_SP_Offline_Verify, source select fail , temp=0x%x\n",temp);									
								Fl_pass=FALSE;
								break;
							}				
						}
					}
				if(Fl_pass==TRUE)
								printk("IP_SP_Offline_Verify, source select Pass \n");														
				break;
				
			case 3: //online measure1
				rtd_outl(0xb8021000,0);// source select PTG ,decomp disable (de_hs=hs_raw,de_vs=vs_raw)
				udelay(1000);	
				rtd_outl(REG_SP_MS1CTRL ,_BIT9|_BIT10);//auto mode , enable
				udelay(100000);		
				rtd_outl(REG_SP_MS1CTRL ,_BIT9|_BIT10|_BIT12);//pop up
				udelay(2000);	
//				temp=rtd_inl(REG_SP_MS1CTRL);

//				if(temp&0x00200000)
//					printk("IP_SP_Online_Verify, off_ms_now  PASS \n");				
//				else{
//					printk("IP_SP_Online_Verify, off_ms_now  Fail,temp=0x%x \n",temp);					
//					Fl_pass=FALSE;
//					}

				udelay(2000);		
				temp=rtd_inl(REG_SP_MS1RST0);
				temp=abs(((temp&0x7ffc0000)>>18),(rtd_inl(REG_PTG_TOTALHV)&0x00000fff));
				if(temp<=1)
					printk("IP_SP_Online1_Verify, V period  PASS \n");						
				else{
					printk("IP_SP_Online1_Verify, V period  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					}

			
				temp=rtd_inl(REG_SP_MS1RST0);
				temp=abs(((temp&0x0000fff0)>>4),2*((rtd_inl(REG_PTG_TOTALHV)&0x0fff0000)>>16));	
				if(temp<=3)
					printk("IP_SP_Online1_Verify, H period  PASS \n");						
				else{
					printk("IP_SP_Online1_Verify, H period  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					}


				temp=rtd_inl(REG_SP_MS1RST1);
				temp=abs((temp&0x0000ffff),2*16*(((rtd_inl(REG_PTG_TG)&0x00000300)>>8)+1));	
				if(temp<=3)
					printk("IP_SP_Online1_Verify, H high period  PASS \n");						
				else{
					printk("IP_SP_Online1_Verify, H high period  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					}

				temp=rtd_inl(REG_SP_MS1RST1);
				temp=abs(((temp&0x0fff0000)>>16),4);	
				if(temp<=3)
					printk("IP_SP_Online1_Verify, V high period  PASS \n");						
				else{
					printk("IP_SP_Online1_Verify, V high period  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					}		
				break;

			case 4: //online measure1
				rtd_outl(0xb8021000,0);// source select PTG ,decomp disable (de_hs=hs_raw,de_vs=vs_raw)
				udelay(1000);	
				rtd_outl(REG_SP_MS1CTRL ,_BIT9|_BIT10|_BIT16);//auto mode , enable, APLL clock
				udelay(100000);		
				rtd_outl(REG_SP_MS1CTRL ,_BIT9|_BIT10|_BIT12|_BIT16);//pop up
				udelay(2000);	
				temp=rtd_inl(REG_SP_MS1RST0);
				temp=abs(((temp&0x0000fff0)>>4),((rtd_inl(REG_PTG_TOTALHV)&0x0fff0000)>>16));	
				if(temp<=3)
					printk("IP_SP_Online1_Verify, measure by APLL clock  PASS \n");						
				else{
					printk("IP_SP_Online1_Verify, measure by APLL clock  fail , temp=0x%x\n",temp);									
					Fl_pass=FALSE;
					}

				
				break;
#if 0   // MacArthur has no sub channel
			case 5: //online measure2
					rtd_outl(0xb8021000,0);// source select PTG ,decomp disable (de_hs=hs_raw,de_vs=vs_raw)
					rtd_outl(0xb8022244,0x90000001);				//Enable VGIP2 
					udelay(100000);	
					rtd_outl(REG_SP_MS2CTRL ,_BIT9|_BIT10);//auto mode , enable
					udelay(100000);		
					rtd_outl(REG_SP_MS2CTRL ,_BIT9|_BIT10|_BIT12);//pop up
					udelay(200000);	
	//				temp=rtd_inl(REG_SP_MS1CTRL);

	//				if(temp&0x00200000)
	//					printk("IP_SP_Online_Verify, off_ms_now  PASS \n");				
	//				else{
	//					printk("IP_SP_Online_Verify, off_ms_now  Fail,temp=0x%x \n",temp);					
	//					Fl_pass=FALSE;
	//					}

					udelay(200000);		
					temp=rtd_inl(REG_SP_MS2RST0);
					temp=abs(((temp&0x0fff0000)>>16),(rtd_inl(REG_PTG_TOTALHV)&0x00000fff));
					if(temp<=1)
						printk("IP_SP_Online2_Verify, V period  PASS \n");						
					else{
						printk("IP_SP_Online2_Verify, V period  fail , temp=0x%x\n",temp);									
						Fl_pass=FALSE;
						}

				
					temp=rtd_inl(REG_SP_MS2RST0);
					temp=abs(((temp&0x0000fff0)>>4),2*((rtd_inl(REG_PTG_TOTALHV)&0x0fff0000)>>16));	
					if(temp<=3)
						printk("IP_SP_Online2_Verify, H period  PASS \n");						
					else{
						printk("IP_SP_Online2_Verify, H period  fail , temp=0x%x\n",temp);									
						Fl_pass=FALSE;
						}


					temp=rtd_inl(REG_SP_MS2RST1);
					temp=abs((temp&0x0000ffff),2*16*(((rtd_inl(REG_PTG_TG)&0x00000300)>>8)+1));	
					if(temp<=3)
						printk("IP_SP_Online2_Verify, H high period  PASS \n");						
					else{
						printk("IP_SP_Online2_Verify, H high period  fail , temp=0x%x\n",temp);									
						Fl_pass=FALSE;
						}

					temp=rtd_inl(REG_SP_MS2RST1);
					temp=abs(((temp&0x0fff0000)>>16),4);	
					if(temp<=3)
						printk("IP_SP_Online2_Verify, V high period  PASS \n");						
					else{
						printk("IP_SP_Online2_Verify, V high period  fail , temp=0x%x\n",temp);									
						Fl_pass=FALSE;
						}		
					break;

				case 6: //online measure2
					rtd_outl(0xb8021000,0);// source select PTG ,decomp disable (de_hs=hs_raw,de_vs=vs_raw)
					udelay(1000);	
					rtd_outl(REG_SP_MS2CTRL ,_BIT9|_BIT10|_BIT16);//auto mode , enable, APLL clock
					udelay(100000);		
					rtd_outl(REG_SP_MS2CTRL ,_BIT9|_BIT10|_BIT12|_BIT16);//pop up
					udelay(200000);	
					temp=rtd_inl(REG_SP_MS2RST0);
					temp=abs(((temp&0x0000fff0)>>4),((rtd_inl(REG_PTG_TOTALHV)&0x0fff0000)>>16));	
					if(temp<=3)
						printk("IP_SP_Online2_Verify, measure by APLL clock  PASS \n");						
					else{
						printk("IP_SP_Online2_Verify, measure by APLL clock  fail , temp=0x%x\n",temp);									
						Fl_pass=FALSE;
						}					
					break;				
#endif				
			default:
				break;
			}
		if (Fl_pass==FALSE)
		break;
}
if (Fl_pass==FALSE)
	return 0;
else
	return 1;

}
//#if 1           //20130822
BOOL IP_3D_ONMS_Verify()
{
UINT8    test_count=0,test_case=15,i;
//IPTG  Total pixel = 858*262, H start 145 ,width 704, V start 16 active 240

	//UINT32	FL_case=0xFFFFFFFF;	
	bool	Fl_pass=1;
	UINT32	rgb2yuv=0;
	UINT32 cnt_n=0;
	
	UINT32	active_space_1=0,active_space_2=0,active_space_3=0;
	UINT32	Vtotalde=0,Vtotal=0,Vs_high_period=0,Hs_high_period=0;
	UINT32	Hact=0,htotal=0,Vblank_len=0,Vact_start=0;
	
	UINT32	onms_vact_space1_max_info=0;
	UINT32	onms_vact_space2_max_info=0;
	UINT32	onms_vact_space3_max_info=0;
	UINT32	onms_vact_space1_min_info=0;
	UINT32	onms_vact_space2_min_info=0;
	UINT32	onms_vact_space3_min_info=0;

	UINT32	Get_r_value=0,Get_g_value=0,Get_b_value=0;
	UINT32	L_blank_line_end=0,R_blank_line_start=0;

	printk(" === IP_3D_ONMS_Verify === \n");

//=================================//
//=== set hdmi 1080p to display ===//
//=================================//
#if 0
#include "apll_ipg1080p.tbl"				// apll setting
#include "sp_ipg.tbl"						// sync processor to select hs/vs from ipg
#include "vgip_ch1_ipg_1080p.tbl"			// vgip ch1 for ipg
#include "rgb2yuvch1_dis.tbl"                   // rgb2yuv disable
#include "uzd_ch1_444_10b_bypass1080p.tbl"	// UZD 444 10b bypass , UZD disable
#include "di_bypass_ch1.tbl"				// bypass de-interlace
#include "ivs2dvs_1080p_fhd.tbl"			// ivs2dvs delay
#include "m_ch1_frc_1080p10b444.tbl"		// M-domain setting
#include "dpll_fhd_1080p_dibypass.tbl"		// DPLL setting for fhd
#include "dtg_fhd.tbl"						// DTG for full hd setting
#include "mtg_fhd.tbl"						// MTG for 1920x1080 setting
#include "uzu_main_444_bypass1080p.tbl"		// UZU for 444 bypass, UZU enable
#include "yuv2rgb_main_en.tbl"				// yuv 2 rgb main enable
#include "LVDS_Pin_Share.tbl"				// LVDS Control setting
#else

//#include "case4_ipg1080p_3d_297Mhz/apll_ipg1080p.tbl"            //Sirius Mark Script ------------------------2014.01.06

//=================test IPTG 3D and 3d onms=================================================

//=== HDMI 3D PTG Setting ===//  HDMI Mac setting and clock 297Mhz



//rtd_outl(0xb8000910,0x00000006); //select hdmi debug output?
rtd_outl(0xb800da40,0x03000000); //enable bandgap
rtd_outl(0xb800d048,0x00000180); //deep color clock output = enable,Enable HDMI deep color mode = enable
rtd_outl(0xb800d098,0x00000008); //video enable
rtd_outl(0xb800d018,0x00000220); //auto output enable, output clk enable
rtd_outl(0xb800d400,0x07e0005b); //M = 31+2;N = 1+2,output clk div1
rtd_outl(0xb800d404,0x00070289); //power down
rtd_outl(0xb800d410,0x00000010); //input clk = X'tal, output clk = PLL, double buffer M,N,O code
rtd_outl(0xb800d414,0x00000000); //div oclk by 1
rtd_outl(0xb800d404,0x00070288); //power up
//delay(1ms);
rtd_outl(0xb800d404,0x00070a88); //cmp enable = 1 after power up
//delay(100us);
rtd_outl(0xb800d404,0x00071a88); //latch cal after power up
//============================================================================================

												  		//Sirius Mark Script ------------------------2014.01.06
//#include "case4_ipg1080p_3d_297Mhz/ipg_1080p.tbl"     //add adc setting select hdmi 297Mhz clock for IPTG 

//#include "case4_ipg1080p_3d_297Mhz/sp_ipg.tbl"         //Sirius Mark Script ------------------------2014.01.06
//#include "case4_ipg1080p_3d_297Mhz/vgip_ch1_ipg_1080p.tbl"//Sirius Mark Script ------------------------2014.01.06



#endif
	

	rgb2yuv=(rtd_inl(0xb800d0bc)>>18)&0x3;		//read color space mode
	if (rgb2yuv == 0x0)
		{
		rtd_maskl(0xb8023000,~(_BIT1|_BIT0),0x0);	//rgb2yuv disable
		rtd_maskl(0xb802a700,~_BIT0,0x0);			//yuv2rgb disable
		}
	else
		{
		rtd_maskl(0xb802a700,~_BIT0,_BIT0); 		//yuv2rgb enable
		}

	//rtd_maskl(0xb8023000,0x00000020);			//rgb2yuv disable
	//rtd_maskl(0xb802a700,0x00000002);			//yuv2rgb disable


								

//===========================//
//=== HDMI 3D PTG Setting ===//
//===========================//
	//#include "hdmi_3D_PTG_1080P.tbl"		// 3D PTG
//	rtd_outl(0xb800d580,0x0000000e); //HDMI Output Source = PTG , bypass fifo = diable

	//////HDMI MAC Setting//////
//	rtd_outl(0xb8000910,0x00000006); //select hdmi debug output
//	rtd_outl(0xb800da40,0x02000000); //enable bandgap
//	rtd_outl(0xb800d028,0x000001d0); //debug output select = dbg_out_29 , test pin[0]= dpclk_buf
//	rtd_outl(0xb800d048,0x00000180); //deep color clock output = enable,Enable HDMI deep color mode = enable
//	rtd_outl(0xb800d098,0x00000008); //video enable
//	rtd_outl(0xb800d018,0x00000220); //auto output enable, output clk enable
//	rtd_outl(0xb800d400,0x07e0005b); //M = 31+2;N = 1+2,output clk div1
//	rtd_outl(0xb800d404,0x00070289); //power down
//	rtd_outl(0xb800d410,0x00000010); //input clk = X'tal, output clk = PLL, double buffer M,N,O code
//	rtd_outl(0xb800d414,0x00000000); //div oclk by 1
//	rtd_outl(0xb800d404,0x00070288); //power up
	//delay(1ms);
//	rtd_outl(0xb800d404,0x00070a88); //cmp enable = 1 after power up
	//delay(100us);
//	rtd_outl(0xb800d404,0x00071a88); //latch cal after power up

#if 0
	//////HDMI 3D PTG Setting///////
	rtd_outl(0xb800d50c,0x00000006); //PTG disable
	rtd_outl(0xb800d500,0x08980465); //Input horizontal total pixel = 2200,when 3D mode, vertical total lines =1125*2
	//rtd_outl(0xb800d504,0x00c00780); //Hstart = 192 , Active Video Width = 1920
	//rtd_outl(0xb800d508,0x00290438); //Vstart = 41 , Active Video Length = 1080
	rtd_outl(0xb800d504,0x008c0780); //Hstart = 140 , Active Video Width = 1920
	rtd_outl(0xb800d508,0x00160438); //Vstart = 22 , Active Video Length = 1080

	rtd_outl(0xb800d514,0x008c0780); //pattern Hstart = 202 , pattern width = 1920
	rtd_outl(0xb800d518,0x00160438); //pattern Vstart = 21 , pattern length = 1080

	rtd_outl(0xb800d520,0x00000003); //L PTG mode = Veritical color bar
	rtd_outl(0xb800d524,0x000000f0); //L single bar width =
	//rtd_outl(0xb800d528,0x00d1f05a); //L Color0 = Red(0x0051f05a) //for DE 能出debug pin(Y bit8 =1)
	rtd_outl(0xb800d528,0x0051f05a); //L Color0 = Red
	rtd_outl(0xb800d52c,0x00296ef0); //L Color1 = Blue
	rtd_outl(0xb800d530,0x00913622); //L Color2 = Green
	rtd_outl(0xb800d548,0x00000fff); //L Max color count = 1

	rtd_outl(0xb800d550,0x00000003); //R PTG mode = Veritical color bar
	rtd_outl(0xb800d554,0x000000f0); //R single bar width =
	rtd_outl(0xb800d558,0x00296ef0); //R Color0 = Blue
	rtd_outl(0xb800d55c,0x0051f05a); //R Color1 = Red
	rtd_outl(0xb800d560,0x00913622); //R Color2 = Green
	rtd_outl(0xb800d578,0x00000fff); //R Max color count = 1

	rtd_outl(0xb800d50c,0x00000005); //fix L flag disable,mode = 3D mode , PTG enable
	rtd_outl(0xb800d580,0x0000000e); //HDMI Output Source = PTG , bypass fifo = diable
	//rtd_outl(0xb800d580,0x0000001d); //HDMI Output Source = PTG , bypass fifo = enable
#else
	rtd_outl(REG_PTG_TG,0x00000006); //PTG disable
	rtd_outl(REG_PTG_TOTALHV,0x08980465); //Input horizontal total pixel = 2200,when 3D mode, vertical total lines =1125*2 
	rtd_outl(REG_PTG_H_STA_WID,0x008c0780); //Hstart = 140 , Active Video Width = 1920
	rtd_outl(REG_PTG_V_STA_LEN,0x00160438); //Vstart = 22 , Active Video Length = 1080

	rtd_outl(REG_PTG_HSTA_WID,0x008c0780); //pattern Hstart = 202 , pattern width = 1920
	rtd_outl(REG_PTG_VSTA_LEN,0x00160438); //pattern Vstart = 21 , pattern length = 1080
	rtd_outl(REG_R_PTG_HSTA_WID,0x008c0780); //pattern Hstart = 202 , pattern width = 1920
	rtd_outl(REG_R_PTG_VSTA_LEN,0x00160438); //pattern Vstart = 21 , pattern length = 1080

	rtd_outl(REG_PTG_CTRL,0x00000003); //L PTG mode = Veritical color bar
	rtd_outl(REG_PTG_BARW,0x000000f0); //L single bar width =
	//rtd_outl(0xb800d528,0x00d1f05a); //L Color0 = Red(0x0051f05a) //for DE 能出debug pin(Y bit8 =1)
	rtd_outl(REG_PTG_C0Y,0x0051f05a); //L Color0 = Red
	rtd_outl(REG_PTG_C1Y,0x00296ef0); //L Color1 = Blue
	rtd_outl(REG_PTG_C2Y,0x00913622); //L Color2 = Green
	rtd_outl(REG_PTG_C7Y,0x10808000); //color bar =1
	rtd_outl(REG_PTG_MAX_COLOR_CTRL,0x00000fff); //L Max color count = 1
 
	rtd_outl(REG_R_PTG_CTRL,0x00000003); //R PTG mode = Veritical color bar
	rtd_outl(REG_R_PTG_BARW,0x000000f0); //R single bar width =
	rtd_outl(REG_R_PTG_C0Y,0x00296ef0); //R Color0 = Blue
	rtd_outl(REG_R_PTG_C1Y,0x0051f05a); //R Color1 = Red
	rtd_outl(REG_R_PTG_C2Y,0x00913622); //R Color2 = Green
	rtd_outl(REG_R_PTG_C7Y,0x10808000); //color bar =1
	rtd_outl(REG_R_PTG_MAX_COLOR_CTRL,0x00000fff); //R Max color count = 1

	rtd_outl(REG_PTG_TG,0x00000005); //fix L flag disable,mode = 3D mode , PTG enable
#endif



	udelay(100);										

for(test_count=0;test_count<test_case;test_count++)
{

	switch(test_count)
			{
			case 0:
//===============================//
//=== 3D ONMS START for 1080P ===//
//===============================//
					printk("(0)Check progressive mode\n");

					// step 0 : measure active space in progressive mode
					rtd_outl(0xb8021300,0x091100a0); 	// set progressive mode
					rtd_outl(0xb8021314,0x042E0433); 	// set active_video2 = 0x42e = 1070, active_video1 = 0x433 = 1075
					rtd_outl(0xb802131c,0x0370DC37); 	// set active_space 1,2,3 = 0x37 = 45 (std of 1080), 30(std of 720)
					udelay(1000);

					for(cnt_n=0;cnt_n<100;cnt_n++)
					{
						rtd_maskl(0xb8021300,~_BIT0,_BIT0);	// start measure
						udelay(100000);
						rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
						udelay(1000);
						rtd_inl(0xb8021300);				// read for ready
						udelay(1000);
						//printk(".");
						if((rtd_inl(0xb8021324)!=0)&((rtd_inl(0xb8021300)&0x1)==0))
							break;
					}
					
					active_space_1 = rtd_inl(0xb8021324);
					if(active_space_1 != 0x00330006)
					{
						printk("(0)progressive mode fail!! active_space_1 = 0x%x	\n",active_space_1);	
						Fl_pass=FALSE;
					}
					else
							printk("case 0==>PASS!!\n");
	
			break;

			case 1:
	
						// step 1 : check HV info.
						printk("1)Check HV info.\n");
						Vtotalde 		= (rtd_inl(0xb8021330)>>16)&0x0fff;
						Vtotal 			= (rtd_inl(0xb8021330)&0x3fff);
						Vs_high_period 	= (rtd_inl(0xb8021334)>>14)&0x0fff;
						Hs_high_period 	= (rtd_inl(0xb8021334)&0x3fff);
						Hact 			= (rtd_inl(0xb8021338)>>18)&0x3fff;
						htotal	 		= (rtd_inl(0xb8021338)>>2)&0x3fff;
						Vblank_len 		= (rtd_inl(0xb802133c)>>16)&0x00ff;
						Vact_start 		= (rtd_inl(0xb802133c)&0x0fff);

						if(Vtotalde != 0x89E)					//Vtotalde = 2206
						{
							printk("(1)Vtotalde fail,%x\n",Vtotalde);
							Fl_pass=FALSE;
							break;
						}
						else if (Vtotal !=0x8CB)				//Vtotal = 2251
						{
							printk("(1)Vtotal fail\n");
							Fl_pass=FALSE;
							break;							
						}
						else if (Vs_high_period !=0x4)			//Vs_high_period = 4
						{
							printk("(1)Vs_high_period fail\n");
							Fl_pass=FALSE;
							break;							
						}
						else if (Hs_high_period !=0x11)			//Hs_high_period = 17
						{
							printk("(1)Hs_high_period fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (Hact !=0x780)					//H_active = 1920
						{
							printk("(1)Hact fail,Hact = %x\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (htotal !=0x898)				//H_total = 2200
						{
							printk("(1)htotal fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (Vblank_len !=0x16)				//Vblank_len = 22
						{
							printk("(1)Vblank_len fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (Vact_start !=0x17)				//Vact_start = 23
						{
							printk("(1)Vact_start fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else
							printk("case 1==>PASS!!\n");
			break;
			case 2:


						printk("(2)Check interlace mode.\n");
						rtd_outl(0xb8021300,0x081100a0);	// set interlace mode
						rtd_outl(REG_PTG_TG,0x00000007);	// set hdmi PTG as interlaced mode.						
//						rtd_outl(0xb800d50c,0x00000007);	// set hdmi PTG as interlaced mode.
						rtd_outl(0xb8021314,0x042E0433);	// set active_video2 = 0x42e = 1070, active_video1 = 0x433 = 1075
						rtd_outl(0xb8021318,0x0433042E);	// set active_video4 = 0x433 = 1075, active_video3 = 0x42e = 1070
						udelay(1000);
						
						for(cnt_n=0;cnt_n<100;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0);	// start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if((rtd_inl(0xb8021328)!=0)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}
						active_space_1 = rtd_inl(0xb8021324);
						active_space_2 = rtd_inl(0xb8021328);
						active_space_3 = rtd_inl(0xb802132c);
						
						if((active_space_1!=0x00330006)|(active_space_2!=0x00330007)|(active_space_3!=0x00340007))
						{
							printk("(2)Interlace mode fail!! active_space_1 = 0x%x,active_space_2 = 0x%x,active_space_3 = 0x%x,	\n",active_space_1,active_space_2,active_space_3);	
							Fl_pass=FALSE;
							break;														
						}

						else
							printk("case 2==>PASS!!\n");
						
				break;
				case 3:
						printk("(3)Check Max/Min info.\n");
						onms_vact_space1_max_info = rtd_inl(0xb8021344);
						onms_vact_space2_max_info = rtd_inl(0xb8021348);
						onms_vact_space3_max_info = rtd_inl(0xb802134c);
						onms_vact_space1_min_info = rtd_inl(0xb8021350);
						onms_vact_space2_min_info = rtd_inl(0xb8021354);
						onms_vact_space3_min_info = rtd_inl(0xb8021358);

						if(onms_vact_space1_max_info != 0x0330182D)
						{
							printk("(3)onms_vact_space1_max_info fail %x\n",onms_vact_space1_max_info);
							Fl_pass=FALSE;
							break;														
						}
						else if (onms_vact_space2_max_info !=0x03301C2C)
						{
							printk("(3)onms_vact_space2_max_info fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (onms_vact_space3_max_info !=0x03401C2D)
						{
							printk("(3)onms_vact_space3_max_info fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (onms_vact_space1_min_info !=0x0330182D)
						{
							printk("(3)onms_vact_space1_min_info fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (onms_vact_space2_min_info !=0x03301C2C)
						{
							printk("(3)onms_vact_space2_min_info fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else if (onms_vact_space3_min_info !=0x03401C2D)
						{
							printk("(3)onms_vact_space3_min_info fail\n");
							Fl_pass=FALSE;
							break;														
						}
						else											
							printk("case 3==>PASS!!\n");

					break;

					case 4:

						printk("(4)Check pixel value\n");

						// check Pixel_get_en,Pixel_ok
						if(rtd_inl(0xb8021304) != 0x01000000)
						{
							printk("(4)Pixel_ok fail\n");
							Fl_pass=FALSE;
							break;
						}

						//get rgb value
						rtd_outl(REG_PTG_C0Y,0x00010101);	// set L region to black gray level = 1(of 8bit)						
//						rtd_outl(0xb800d528,0x00010101);	// set L region to black gray level = 1(of 8bit)
															//(ptg will repeat to 10 bit, 1 will be 101)
						rtd_outl(0xb8021314,0x042E0400);	// set measure area to L region
						udelay(100000);

						for(cnt_n=0;cnt_n<100;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0);	// start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if((rtd_inl(0xb8021328)==0x001B0000)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}
							
						Get_r_value = (rtd_inl(0xb8021304)>>12)&0xfff;	//r value of L region = 0x14 = b10100
						Get_g_value = rtd_inl(0xb8021304)&0xfff;		//g value of L region = 0x14 = b10100
						Get_b_value = rtd_inl(0xb8021308)&0xfff;		//b value of L region = 0x14 = b10100

						if((Get_r_value!=0x14)|(Get_g_value!=0x14)|(Get_b_value!=0x14)) //the same with ptg
						{
							printk("(4)Pixel get value fail%x %x %x\n",Get_r_value,Get_g_value,Get_b_value);
							Fl_pass=FALSE;
							break;
						}

						//set active value equal to the getting value
						rtd_outl(0xb802130c,0x00014014);
						rtd_outl(0xb8021310,0x00000014);

						for(cnt_n=0;cnt_n<100;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0);	// start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if((rtd_inl(0xb8021324)==0x00370000)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}
						//if the difference pixel number < th, HW will assume it's active space
						active_space_1 = rtd_inl(0xb8021324);
						if(active_space_1 != 0x00370000)
						{
							printk("(4)Pixel set active value fail\n");
							Fl_pass=FALSE;
							break;
						}
						
						rtd_outl(0xb8021300,0x0a1100a0);	// select active space 2 to get value
						for(cnt_n=0;cnt_n<100;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0);	// start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if((rtd_inl(0xb8021328)==0x001B0000)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}


						Get_r_value = (rtd_inl(0xb8021304)>>12)&0xfff;	//r value of R region = 0x6E8
						Get_g_value = rtd_inl(0xb8021304)&0xfff;		//g value of R region = 0x294
						Get_b_value = rtd_inl(0xb8021308)&0xfff;		//b value of R region = 0xF00

						if((Get_r_value!=0x6E8)|(Get_g_value!=0x294)|(Get_b_value!=0xF00)) //the same with ptg
						{
							printk("(4)Select active space 2 fail\n");
							Fl_pass=FALSE;
							break;
						}

						if(Fl_pass!=FALSE)
							printk("case 4==>PASS!!\n");
					break;
					
					case 5:
						// step 5 : check blank line
						printk("(5)Check blank line\n");
						rtd_outl(REG_PTG_TG,0x00000005);	// set progressive
						rtd_outl(REG_PTG_C0Y,0x00000000);	// set L region to black gray level = 0(of 8bit)						
//						rtd_outl(0xb800d50c,0x00000005);	// set progressive
//						rtd_outl(0xb800d528,0x00000000);	// set L region to black gray level = 0(of 8bit)
						rtd_outl(0xb8021314,0x042E0470);	// set region conver the blank line
						rtd_outl(0xb802130c,0x00000000);	// reset active r/g/b value to 0
						rtd_outl(0xb8021310,0x00000000);	// reset active r/g/b value to 0
						rtd_outl(0xb8021300,0x091100a0);
						
						for(cnt_n=0;cnt_n<100;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0);	// start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if(((rtd_inl(0xb8021320)&0xfff)==0x467)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}

						L_blank_line_end = (rtd_inl(0xb8021320)&0x7ff);	
						if(L_blank_line_end != 0x467)
						{
							printk("(5)L_blank_line_end fail \n");
							Fl_pass=FALSE;
							break;
						}
							
						rtd_outl(REG_PTG_C0Y,0x0051f05a);	// set L region to black gray level = 0(of 8bit)						
						rtd_outl(REG_R_PTG_C0Y,0x00000000);	// set L region to black gray level = 0(of 8bit)	
//						rtd_outl(0xb800d528,0x0051f05a);	// reset L region
//						rtd_outl(0xb800d558,0x00000000);	// set R region to black gray level = 0(of 8bit)
						rtd_outl(0xb8021314,0x042E0300);	// set region conver the blank line

						for(cnt_n=0;cnt_n<100;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0);	// start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if((rtd_inl(0xb8021328)==0x01020001)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}

						R_blank_line_start = ((rtd_inl(0xb8021320)>>16)&0x7df);
						if(R_blank_line_start != 0x102)
						{
							printk("(5)R_blank_line_start fail %x\n",rtd_inl(0xb8021320));
							Fl_pass=FALSE;
							break;
						}
						rtd_outl(0xb8021314,0x042E0433);	// reset region
						if(Fl_pass!=FALSE)
							printk("case 5==>PASS!!\n");
					break;
					case 6:
	// step 6 : check flag of status
						printk("(6)Check flag of status\n");
						
						//set continuous mode, flag will NOT be correct in one time mode
						rtd_maskl(0xb8021300,~_BIT1,_BIT1);
						udelay(10000);

						//set min > (end-start)
						//b802135c[2]=1,[1]=1,[0]=1
						rtd_outl(0xb8021340,0x04010040);
						udelay(100000);

						for(cnt_n=0;cnt_n<100;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if((rtd_inl(0xb802135c)==0x00070007)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}
						if((rtd_inl(0xb802135c)&0x7)!=0x7)
						{
							printk("(6)Vact_space_under_min fail %x\n",rtd_inl(0xb802135c));	
							Fl_pass=FALSE;
							break;
						}
						else
							printk("case 6==>PASS!!\n");

				break;						
				case 7:		
						printk("(7)Hsync inversion check\n");					
						rtd_outl(0xb8021360,_BIT0);
						udelay(1000);
						rtd_maskl(0xb8021360,~_BIT0,0x0);
						udelay(1000);
						rtd_outl(0xb8021360,_BIT1);
						udelay(1000);
						rtd_maskl(0xb8021360,~_BIT1,0x0);
						udelay(1000);
						rtd_outl(0xb8021360,_BIT2);
						udelay(1000);
						rtd_maskl(0xb8021360,~_BIT2,0x0);
						
						//reset
						rtd_outl(0xb8021340,0x0);
						for(cnt_n=0;cnt_n<10;cnt_n++)
						{
							rtd_outl(0xb802135c,0xfffff);//wclr_out
							rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							if(rtd_inl(0xb802135c)==0x00070000)
								break;
						}
						if(rtd_inl(0xb802135c)!=0x00070000)
						{
							printk("(7)Hsync inversion fail 1 %x\n",rtd_inl(0xb802135c));
							Fl_pass=FALSE;
							break;
						}
					
						//invert hsync
						//b802135c[16]=0,[8]=1,[6]=1,[3]=1
						rtd_maskl(0xb8021300,~_BIT3,_BIT3); 	//invert hsync
						for(cnt_n=0;cnt_n<10;cnt_n++)
						{
							rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							udelay(1000);
							//printk(".");
							if((rtd_inl(0xb802135c)==0x00060148)&((rtd_inl(0xb8021300)&0x1)==0))
								break;
						}
						if(rtd_inl(0xb802135c)!=0x00060148)
						{
							printk("(7)Hsync inversion fail 2  %x\n",rtd_inl(0xb802135c));
							Fl_pass=FALSE;
							break;
						}
						else
							printk("case 7==>PASS!!\n");
					break;
				case 8:	
						rtd_outl(0xb8021360,_BIT3);
						udelay(1000);
						rtd_maskl(0xb8021360,~_BIT3,0x0);
						udelay(1000);
						rtd_outl(0xb8021360,_BIT6);
						udelay(1000);
						rtd_maskl(0xb8021360,~_BIT6,0x0);
						udelay(1000);
						rtd_outl(0xb8021360,_BIT8);
						udelay(1000);
						rtd_maskl(0xb8021360,~_BIT8,0x0);
						//reset
						rtd_maskl(0xb8021300,~_BIT3,0x0); //invert hsync back to initial
						for(cnt_n=0;cnt_n<10;cnt_n++)
						{
							rtd_outl(0xb802135c,0xfffff);//wclr_out
							rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
							udelay(100000);
							rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
							udelay(1000);
							rtd_inl(0xb8021300);				// read for ready
							if(rtd_inl(0xb802135c)==0x00070000)
								break;
						}
						if(rtd_inl(0xb802135c)!=0x00070000)
							{
								printk("(8)Vsync inversion fail 1%x\n",rtd_inl(0xb802135c));
							Fl_pass=FALSE;
							break;
							}

							//invert vsync
							//b802135c[17]=0,[15]=1,[12]=1,[9]=1,[7]=1,[6]=1
							rtd_maskl(0xb8021300,~_BIT4,_BIT4); 	//invert hsync
							for(cnt_n=0;cnt_n<10;cnt_n++)
							{
								rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
								udelay(100000);
								rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
								udelay(1000);
								rtd_inl(0xb8021300);				// read for ready
								udelay(1000);
								//printk(".");
								if((rtd_inl(0xb802135c)==0x000592C0)&((rtd_inl(0xb8021300)&0x1)==0))
									break;
							}
							if(rtd_inl(0xb802135c)!=0x000592C0)
							{
								printk("(8)Vsync inversion fail 2%x\n",rtd_inl(0xb802135c));
							Fl_pass=FALSE;
							break;
							}
							else
							printk("case 8==>PASS!!\n");								

						break;

					case 9:
							rtd_outl(0xb8021360,_BIT6);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT6,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT7);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT7,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT9);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT9,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT12);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT12,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT15);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT15,0x0);
							//reset
							rtd_maskl(0xb8021300,~_BIT4,0x0); //invert hsync back to initial
							for(cnt_n=0;cnt_n<10;cnt_n++)
							{
								rtd_outl(0xb802135c,0xfffff);//wclr_out
								rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
								udelay(100000);
								rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
								udelay(1000);
								rtd_inl(0xb8021300);				// read for ready
								if(rtd_inl(0xb802135c)==0x00070000)
									break;
							}
							if(rtd_inl(0xb802135c)!=0x00070000)
							{
								printk("(9)Hact & Htotal detect fail 1%x\n",rtd_inl(0xb802135c));
								Fl_pass=FALSE;
								break;
							}							
					
							//change htotal & hact
							//b802135c[14]=1,[4]=1(change htatoal),[5]=1,[3]=1(change hact)
							rtd_outl(REG_PTG_TOTALHV,0x08b80465);	//change htotal
							rtd_outl(REG_PTG_H_STA_WID,0x008c0788);	//change hact							
//							rtd_outl(0xb800d500,0x08b80465);	//change htotal
//							rtd_outl(0xb800d504,0x008c0788);	//change hact
							for(cnt_n=0;cnt_n<10;cnt_n++)
							{
								rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
								udelay(100000);
								rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
								udelay(1000);
								rtd_inl(0xb8021300);				// read for ready
								udelay(1000);
								//printk(".");
								if((rtd_inl(0xb802135c)==0x00074038)&((rtd_inl(0xb8021300)&0x1)==0))
									break;
							}
							if(rtd_inl(0xb802135c)!=0x00074038)
							{
								printk("(9)Hact & Htotal detect fail 2%x\n",rtd_inl(0xb802135c));
								Fl_pass=FALSE;
								break;
							}
							else
							printk("case 9==>PASS!!\n");	
					break;
				case 10:
							rtd_outl(0xb8021360,_BIT3);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT3,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT4);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT4,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT5);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT5,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT14);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT14,0x0);
							//reset	
							rtd_outl(REG_PTG_TOTALHV,0x08980465);	//change htotal
							rtd_outl(REG_PTG_H_STA_WID,0x008c0780);	//change hact								
//							rtd_outl(0xb800d500,0x08980465);	//set htotal back
//							rtd_outl(0xb800d504,0x008c0780);	//set hact back
							for(cnt_n=0;cnt_n<10;cnt_n++)
							{
								rtd_outl(0xb802135c,0xfffff);//wclr_out
								rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
								udelay(100000);
								rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
								udelay(1000);
								rtd_inl(0xb8021300);				// read for ready
								if(rtd_inl(0xb802135c)==0x00070000)
									break;
							}
							if(rtd_inl(0xb802135c)!=0x00070000)
							{
								printk("(10)Vact & Vtotal detect fail 1%x\n",rtd_inl(0xb802135c));
								Fl_pass=FALSE;
								break;
							}							

							//change vtotal & vact
							//b802135c[15]=1,[7]=1,[6]=1(change vtatoal),[7]=1(change vact)
							rtd_outl(REG_PTG_TOTALHV,0x0898046d);	//change htotal
							rtd_outl(REG_PTG_V_STA_LEN,0x00160478);	//change hact								
//					rtd_outl(0xb800d500,0x0898046d);	//change vtotal
//					rtd_outl(0xb800d508,0x00160478);	//change vact
							for(cnt_n=0;cnt_n<10;cnt_n++)
							{
								rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
								udelay(100000);
								rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
								udelay(1000);
								rtd_inl(0xb8021300);				// read for ready
								udelay(1000);
								//printk(".");
								if((rtd_inl(0xb802135c)==0x000780C0)&((rtd_inl(0xb8021300)&0x1)==0))
									break;
							}
							if(rtd_inl(0xb802135c)!=0x000780C0)
							{
								printk("(10)Vact & Vtotal detect fail 1%x\n",rtd_inl(0xb802135c));
								Fl_pass=FALSE;
								break;
							}
							else
							printk("case 10==>PASS!!\n");	
					break;		
				case 11:
							rtd_outl(0xb8021360,_BIT6);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT6,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT7);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT7,0x0);
							udelay(1000);
							rtd_outl(0xb8021360,_BIT15);
							udelay(1000);
							rtd_maskl(0xb8021360,~_BIT15,0x0);
							//reset
							rtd_outl(REG_PTG_TOTALHV,0x08980465);	//change htotal
							rtd_outl(REG_PTG_V_STA_LEN,0x00160438);	//change hact								
//					rtd_outl(0xb800d500,0x08980465);	//set vtotal back
//					rtd_outl(0xb800d508,0x00160438);	//set vact back
//						rtd_outl(0xb8021300,(rtd_inl(0xb8021300)&~_BIT1));
							for(cnt_n=0;cnt_n<10;cnt_n++)
							{
								rtd_outl(0xb802135c,0xfffff);//wclr_out
								rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
								udelay(100000);
								rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
								udelay(1000);
								rtd_inl(0xb8021300);				// read for ready
								if(rtd_inl(0xb802135c)==0x00070000)
									break;
							}
								if(rtd_inl(0xb802135c)!=0x00070000)
								{
									printk("(11)vtotal time-out detect fail 1%x\n",rtd_inl(0xb802135c));
									Fl_pass=FALSE;
								break;
							}							
								//change vtotal to make vsync time-out
								//b802135c[13]=1,
							rtd_outl(REG_PTG_TOTALHV,0x08980c65);	//change htotal								
//						rtd_outl(0xb800d500,0x08980c65);	//change vtotal & htotal
								for(cnt_n=0;cnt_n<100;cnt_n++)
								{
									rtd_outl(0xb802135c,0xfffff);//wclr_out
									rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
									udelay(100000);
									rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
									udelay(1000);
									rtd_inl(0xb8021300);				// read for ready
									udelay(1000);
									//printk(".");
									if((rtd_inl(0xb802135c)==0x00070007)&((rtd_inl(0xb8021300)&0x1)==0))
										break;
								}
						udelay(100000);								
								if((rtd_inl(0xb802135c)&_BIT13)==0)
								{
									printk("(11)vtotal time-out detect fail 2%x\n",rtd_inl(0xb802135c));
									Fl_pass=FALSE;
								break;
							}
							else
							printk("case 11==>PASS!!\n");	
					break;		
				case 12:
								rtd_outl(0xb8021360,_BIT13);
								udelay(1000);
								rtd_maskl(0xb8021360,~_BIT13,0x0);
								//reset
								rtd_maskl(0xb8021300,~_BIT6,_BIT6); //set time-out to 76ms
								rtd_maskl(0xb8021300,~_BIT0,_BIT0); //start measure
								for(cnt_n=0;cnt_n<100;cnt_n++)
								{
									rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
									udelay(100000);
									rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
									udelay(1000);
									rtd_inl(0xb8021300);				// read for ready
									udelay(1000);
									//printk(".");
									if((rtd_inl(0xb802135c)==0x00070007)&((rtd_inl(0xb8021300)&0x1)==0))
										break;
								}
								if(rtd_inl(0xb802135c)!=0x00070000)
								{
									printk("(12)vtotal time-out threshold fail 1%x\n",rtd_inl(0xb802135c));
									Fl_pass=FALSE;
								break;
							}
							else
							printk("case 12==>PASS!!\n");	
					break;	
				case 13:
							rtd_outl(REG_PTG_TOTALHV,0x08980465);	//change htotal					
//						rtd_outl(0xb800d500,0x08980465);	//set htotal,vtotal back
								for(cnt_n=0;cnt_n<10;cnt_n++)
								{
									rtd_outl(0xb802135c,0xfffff);//wclr_out
									rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
									udelay(100000);
									rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
									udelay(1000);
									rtd_inl(0xb8021300);				// read for ready
									if(rtd_inl(0xb802135c)==0x00070000)
										break;
								}
								if(rtd_inl(0xb802135c)!=0x00070000)
									{
										printk("(13)htotal over-flow detect fail 1%x\n",rtd_inl(0xb802135c));
									Fl_pass=FALSE;
								break;
								}								
									//disable ptg to make hsync & vsync over-flow
									//b802135c[10]=1
							rtd_outl(REG_PTG_TG,0x0);	//change htotal														
//							rtd_outl(0xb800d50c,0x0);	//disable ptg
									for(cnt_n=0;cnt_n<10;cnt_n++)
									{
										rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
										udelay(100000);
										rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
										udelay(1000);
										rtd_inl(0xb8021300);				// read for ready
										udelay(1000);
										//printk(".");
										if((((rtd_inl(0xb802135c)&_BIT10)>>10)==1)&((rtd_inl(0xb8021300)&0x1)==0))
											break;
									}
									if(((rtd_inl(0xb802135c)&_BIT10)>>10)!=1)
									{
										printk("(13)htotal over-flow detect fail 2%x\n",rtd_inl(0xb802135c));
									Fl_pass=FALSE;
								break;
							}
							else
							printk("case 13==>PASS!!\n");	
							break;
						case 14:							
									rtd_outl(0xb8021360,_BIT10);
									udelay(1000);
									rtd_maskl(0xb8021360,~_BIT10,0x0);
									//reset
							rtd_outl(REG_PTG_TG,0x5);//change htotal										
//							rtd_outl(0xb800d50c,0x5);	//enable ptg
									for(cnt_n=0;cnt_n<10;cnt_n++)
									{
										rtd_outl(0xb802135c,0xfffff);//wclr_out
										rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
										udelay(100000);
										rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
										udelay(1000);
										rtd_inl(0xb8021300);				// read for ready
										if(rtd_inl(0xb802135c)==0x00070000)
											break;
									}
								if(rtd_inl(0xb802135c)!=0x00070000)
								{
									printk("(14)vtotal overflow detect fail 1%x\n",rtd_inl(0xb802135c));
									Fl_pass=FALSE;
								break;
							}
								//change vtotal to make vsync over-flow
								//b802135c[11]=1
							rtd_outl(REG_PTG_TG,0x7);//change htotal	
						rtd_outl(REG_PTG_TOTALHV,0x00981fff);	//change vtotal							
//						rtd_outl(0xb800d50c,0x7);			//set interlace mode, Vtotal will be double.
//						rtd_outl(0xb800d500,0x00981fff);	//change vtotal
								for(cnt_n=0;cnt_n<10;cnt_n++)
								{
									rtd_maskl(0xb8021300,~_BIT24,0x0);//set interlace mode.
									rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
									udelay(100000);
									rtd_maskl(0xb8021300,~_BIT2,_BIT2);	// pop-up measure result
									udelay(1000);
									rtd_inl(0xb8021300);				// read for ready
									udelay(1000);
									//printk(".");
									if((((rtd_inl(0xb802135c)&_BIT11)>>11)==1)&((rtd_inl(0xb8021300)&0x1)==0))
										break;
								}
								if(((rtd_inl(0xb802135c)&_BIT11)>>11)!=1)
								{
									printk("(14)vtotal overflow detect fail 2%x\n",rtd_inl(0xb802135c));
									Fl_pass=FALSE;
								break;
							}
							else
							printk("case 14==>PASS!!\n");	
							break;		
						case 15:
							      rtd_outl(0xb8021360,_BIT11);
								udelay(1000);
								rtd_maskl(0xb8021360,~_BIT11,0x0);
								//reset
							rtd_outl(REG_PTG_TG,0x08980465);//change htotal	
//						rtd_outl(0xb800d500,0x08980465);	//set htotal back
								for(cnt_n=0;cnt_n<10;cnt_n++)
								{
									rtd_outl(0xb802135c,0xfffff);//wclr_out
									rtd_maskl(0xb8021300,~_BIT0,_BIT0); // start measure
									udelay(100000);
									rtd_maskl(0xb8021300,~_BIT2,_BIT2); // pop-up measure result
									udelay(1000);
									rtd_inl(0xb8021300);				// read for ready
									if(rtd_inl(0xb802135c)==0x00070000)
										break;
								}
							break;
				default:
							break;

				}
			printk("(Fl_pass flag=%x\n",Fl_pass);
			if (Fl_pass==FALSE)
		break;
}

		
	if (Fl_pass==FALSE)
		return 0;
	else
		return 1;


}
//#endif      //20130821
BOOL IP_IPTG_Verify()
{
UINT8    test_count=0,test_case=16,i;
UINT16  Width,Length;
UINT32   temp;
bool     Fl_pass=1;

printk("IP_IPTG_Verify  \n");

		rtd_outl(0xb8020000 , 0x000001ff);  // global power on



//IPTG  Total pixel = 858*262, H start 145 ,width 704, V start 16 active 240

for(test_count=0;test_count<test_case;test_count++)
{
		rtd_outl(REG_PTG_TOTALHV, 0x035a0106);   // Total pixel = 858*262
		rtd_outl(REG_PTG_H_STA_WID, 0x0010034a);   // Horizontal active start = 16, active width = 842
		rtd_outl(REG_PTG_V_STA_LEN, 0x00050101);   // Vertical active start = 5, active width = 257


		rtd_outl(REG_PTG_HSTA_WID, 0x009102c0);   // Pattern Gen display Hstart=145 & Hactive =704 前端留16 piexels 用來判斷porch 
		rtd_outl(REG_PTG_VSTA_LEN, 0x001000f0);   // Pattern Gen display Vstart=16 & Vactive =240
		rtd_outl(REG_PTG_CTRL, 0x00000003);   // PTG control, select pattern = Color Bar 
		rtd_outl(REG_PTG_BARW, 0x00000059);   // Color bar width  =59
		rtd_outl(REG_PTG_C0Y, 0x00ffffff);   // active region color 
		rtd_outl(REG_PTG_C2Y, 0x00070707);   // porch region color 101=5           10 bit color=5
		rtd_outl(REG_PTG_MAX_COLOR_CTRL, 0x00000fff);   // color set (copy from defualt value) 1 color
		rtd_outl(REG_PTG_TG, 0x40000002);   // Enable timing generator, interlace,seperate
		udelay(20000);
		rtd_outl(REG_PTG_TG, 0x40000003);   // Enable timing generator, interlace,seperate
		
switch(test_count)
	{
	case 0:  //IPTG HV total use online measure 
		rtd_outl(0xb8021200, 0x00010600);		//online measure
		udelay(200000);			
		rtd_outl(0xb8021200, 0x00011600);		//online measure
		udelay(200000);	
		temp=rtd_inl(0xb8021204);		//online measure		
		Width=(temp&0x0000fff0)>>4;
		Length=(temp&0x7ffc0000)>>18;		
		temp=abs((Length+1),(rtd_inl(REG_PTG_TOTALHV)&0x00000fff));
			if(((Width+1)==((rtd_inl(REG_PTG_TOTALHV)&0x0fff0000)>>16))&& 
  			    (temp<=1))
				printk("IP_IPTG_Verify HVtotal Pass\n");						  			    
			else
			{
				printk("IP_IPTG_Verify fail Htotal=%d VTotal=%d temp=%d\n",Width,Length,temp);		
				Fl_pass=FALSE;	
				break;
			}	
	
		break;
	case 1: //IPTG HV start& width& len
		rtd_outl(0xb8022210, 0x90000001);	 //VGIP enable 
		rtd_outl(REG_AUTO_H_BOUNDARY, 0x0005035A);//set H  boudary , start 80 end 858
		rtd_outl(REG_AUTO_V_BOUNDARY, 0x00020106);//set V  boudary , start 2 end 262
		rtd_outl(REG_AUTO_RGB_MARGIN, 0x04040400);//Noise MGN 0
		rtd_outl(REG_AUTO_ADJ, 0);//reset adj
		rtd_outl(REG_AUTO_FIELD, 0);//reset field		
	
				rtd_outl(REG_AUTO_ADJ, _BIT0);
				udelay(100000);	
				Length=((rtd_inl(REG_AUTO_RESULT_V)&0x0fff0000)>>16);
				Width=((rtd_inl(REG_AUTO_RESULT_H)&0x0fff0000)>>16);

				if(((Length+1)==(rtd_inl(REG_PTG_V_STA_LEN)&0x0fff0000)>>16)&&
					((Width+1)==(rtd_inl(REG_PTG_H_STA_WID)&0x0fff000)>>16))
					printk("IP_IPTG_Verify HV start Pass\n");		
				else
					{
					printk("IP_IPTG_Verify Hstart=%d Vstart=%d\n",Width,Length);		
					Fl_pass=FALSE;	
					break;								
					}
				
				Length=(rtd_inl(REG_AUTO_RESULT_V)&0x00000fff)-Length+1;
				Width=(rtd_inl(REG_AUTO_RESULT_H)&0x00000fff)-Width+1;
				if((Length==(rtd_inl(REG_PTG_V_STA_LEN)&0x00000fff))&&
					(Width==(rtd_inl(REG_PTG_H_STA_WID)&0x00000fff)))
					printk("IP_IPTG_Verify HV WID&LEN Pass\n");		
				else
					{
					printk("IP_IPTG_Verify H_WID=%d V_LEN=%d\n",Width,Length);		
					Fl_pass=FALSE;	
					}
				break;				
	case 2://IPTG PTG HV start& width& len
				rtd_outl(REG_AUTO_RGB_MARGIN, 0x80808000);//Noise MGN 0
				rtd_outl(REG_AUTO_ADJ, _BIT0);
				udelay(100000);	

				Length=((rtd_inl(REG_AUTO_RESULT_V)&0x0fff0000)>>16);
				Width=((rtd_inl(REG_AUTO_RESULT_H)&0x0fff0000)>>16);

				if(((Length+1)==(rtd_inl(REG_PTG_VSTA_LEN)&0x0fff0000)>>16)&&
					((Width+1)==(rtd_inl(REG_PTG_HSTA_WID)&0x0fff000)>>16))
					printk("IP_IPTG_Verify PTG HV start Pass\n");		
				else
					{
					printk("IP_IPTG_Verify fail PTG Hstart=%d Vstart=%d\n",Width,Length);		
					Fl_pass=FALSE;	
					break;								
					}
				
				Length=(rtd_inl(REG_AUTO_RESULT_V)&0x00000fff)-Length+1;
				Width=(rtd_inl(REG_AUTO_RESULT_H)&0x00000fff)-Width+1;
				if((Length==(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff))&&
					(Width==(rtd_inl(REG_PTG_HSTA_WID)&0x00000fff)))
					printk("IP_IPTG_Verify PTG HV WID&LEN Pass\n");		
				else
					{
					printk("IP_IPTG_Verify PTG H_WID=%d V_LEN=%d\n",Width,Length);		
					Fl_pass=FALSE;	
					}								
				break;
	case 3: //IPTG H_HighPulseWid                   TEST: on line measure
				for (i=0;i<4;i++)
					{
						rtd_outl(REG_PTG_TG,(rtd_inl(REG_PTG_TG)&0xfffffcff)|(i<<8));   // Set H_HighPulseWid
						udelay(20000);							
						rtd_outl(0xb8021200, 0x00010600);		//online measure
						udelay(20000);			
						rtd_outl(0xb8021200, 0x00011600);		//Pop up
						udelay(200000);	
						Width=rtd_inl(0xb8021208)&0x00000fff;
						if(Width!=((i+1)*0x10))
							{
							printk("IP_IPTG_Verify H_HighPulseWid=%d result=%d\n",i,Width);									
							Fl_pass=FALSE;	
							break;
							}
						if(i==3)
							printk("IP_IPTG_Verify H_HighPulseWid  Pass\n");									
					}
				break;	
	case 4: //IPTG CS type              TEST: SP auto run result
				for (i=0;i<5;i++)
					{
						rtd_outl(REG_PTG_TG,(rtd_inl(REG_PTG_TG)&0x0fffffff)|(i<<28));   // Set CS
						udelay(20000);							
						rtd_outl(0xb8021008, 0x00000000);		//SP2 AUTO detect
						udelay(20000);			
						rtd_outl(0xb8021008, 0x00000400);		//SP2 AUTO detect						
						udelay(200000);									
						temp=(rtd_inl(0xb802100c)&0x00000070)>>4;  //get sync type
						switch(i)
							{
							case 0://IPTG cs= OR
							case 1://IPTG cs= XOR
								if(temp!=5)  //sp detect XOR/OR without EQ
									temp=FALSE;
								else
									temp=TRUE;
							break;
							case 2://IPTG cs= all 0
							case 3://IPTG cs= all 1 	
								if(temp!=0)  //sp detect No signal 
									temp=FALSE;
								else
									temp=TRUE;	
							break;
							case 4://IPTG cs= separete 	
								if(temp!=6)  //sp detect Separaet 
									temp=FALSE;
								else
									temp=TRUE;	
							break;

							default:
									temp=FALSE;	
								break;	

							}
						if(temp==FALSE)
							{
							printk("IP_IPTG_Verify CS=%d result=%d\n",i,(rtd_inl(0xb802100c)&0x00000070)>>4);									
							Fl_pass=FALSE;	
							break;
							}
//							printk("IP_IPTG_Verify CS=%d result=%d\n",i,(rtd_inl(0xb802100c)&0x00000070)>>4);	
						if(i==4)
							printk("IP_IPTG_Verify CS  Pass\n");									
					}
				break;		
		case 5:	//Enable                  TEST: Auto run result
					rtd_outl(REG_PTG_TG,(rtd_inl(REG_PTG_TG)&0x0fffffff));   // Set CS=OR,Enable

					rtd_outl(0xb8021008, 0x00000000);		//SP2 AUTO detect
					udelay(20000);			
					rtd_outl(0xb8021008, 0x00000400);		//SP2 AUTO detect						
					udelay(200000);									
					temp=(rtd_inl(0xb802100c)&0x00000070)>>4;  //get sync type
					if(temp==5)	//sp detect XOR/OR without EQ
						{
						rtd_outl(REG_PTG_TG,(rtd_inl(REG_PTG_TG)&0x0ffffffe));   // Set CS=OR,Disable
						rtd_outl(0xb8021008, 0x00000000);		//SP2 AUTO detect
						udelay(20000);			
						rtd_outl(0xb8021008, 0x00000400);		//SP2 AUTO detect						
						udelay(200000);									
						temp=(rtd_inl(0xb802100c)&0x00000070)>>4;  //get sync type						
						if(temp==0) //sp detect No signal
							{
							printk("IP_IPTG_Verify EN Pass\n");									
		
							}
						else
							{
							printk("IP_IPTG_Verify EN fail\n");									
							Fl_pass=FALSE;	
							break;
							}																									
						}
					else
						{
						printk("IP_IPTG_Verify EN fail\n");									
						Fl_pass=FALSE;	
						break;
							}		
					break;
		case 6:	//Interlace/progressive mode   TEST: VGIP FIELD TOG
					rtd_outl(0xb8022214,0x000000ff);// clear VGIP field tog flag
					udelay(200000);								
					temp=rtd_inl(0xb8022214);
					if(temp&0x00000040) //interlace
						{
						printk("IP_IPTG_Verify interlace\n");									
						rtd_outl(REG_PTG_TG,(rtd_inl(REG_PTG_TG)&0xfffffffd));   // Set progressive					
						udelay(200000);								
						rtd_outl(0xb8022214,0x000000ff);// clear VGIP field tog flag
						udelay(200000);								
							if(!(rtd_inl(0xb8022214)&0x00000040))
	//					printk("IP_IPTG_Verify progressive\n");																
							printk("IP_IPTG_Verify interlace/progressive Pass\n");			
							else
							{
								printk("1. IP_IPTG_Verify interlace/progressive fail flag=0x%x\n",rtd_inl(0xb8022214));		
								Fl_pass=FALSE;	
								break;
							}									
						}
					else
						{
						printk("2. IP_IPTG_Verify interlace/progressive fail flag=0x%x\n",rtd_inl(0xb8022214));		
						Fl_pass=FALSE;	
						break;
							}		
		break;

		case 7: //random   TEST:CRC
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)|0x00000100)&0xfffffff8); //enable random , disable PGT (All image is random)
			udelay(200000);											
			
			rtd_outl(0xb8025220,0x00000003); //Enable  uzd CRC
			udelay(200000);											
			temp= rtd_inl(0xb8025224); //CRC result

			if((temp==0x3847466F)||(temp==0x14ED1808))
		   		printk("IP_IPTG_Verify Random Background Pass\n");		
			else{
				printk("IP_IPTG_Verify Random Background Fail CRC=0x%x\n",temp);		
				Fl_pass=FALSE;	
				}

			udelay(1000000);			// hold pattern on screen for tester see								
 		break;

		case 8: // V color bar    TEST CRC
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000003); //V color bar
			rtd_outl(REG_PTG_C0Y,0x00ffffff); // color  bar 1 =white
			rtd_outl(REG_PTG_C1Y,0x0000ff00); // color  bar 2 =red
			rtd_outl(REG_PTG_C2Y,0x00ff0000); // color  bar 3 =green
			rtd_outl(REG_PTG_C3Y,0x0000ff00); // color  bar 4 =blue
			rtd_outl(REG_PTG_C4Y,0xffff0000); // color  bar 5 =yellow
			rtd_outl(REG_PTG_C5Y,0xff00ff00); // color  bar 6 =cyan
			rtd_outl(REG_PTG_C6Y,0x00ffff00); // color  bar 7 =maginta
			rtd_outl(REG_PTG_C7Y,0x00000000); // color  bar 8 =Black
			rtd_outl(REG_PTG_C7Y,(rtd_inl(REG_PTG_C7Y)|0x00000007)); //7 color bar
			
			udelay(20000);											
			rtd_outl(0xb8025220,0x00000003); //Enable  CRC
			udelay(20000);											
			temp= rtd_inl(0xb8025224);  //CRC result

			if((temp==0x8AC023E9)||(temp==0x79752773))
		   		printk("IP_IPTG_Verify V color bar & 8 colors Pass\n");		
			else{
				printk("IP_IPTG_Verify V color bar & 8 colors fail CRC=0x%x\n",temp);		
				Fl_pass=FALSE;	
				}

			udelay(1000000);			// hold pattern on screen for tester see								
			break;

		case 9: // H color bar    TEST CRC
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000002); //H color bar		
			rtd_outl(REG_PTG_BARW,((rtd_inl(REG_PTG_BARW)&0xfffffc00)|(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff)/8)); //7 color bar

			rtd_outl(REG_PTG_C0Y,0x00ffffff); // color  bar 1 =white
			rtd_outl(REG_PTG_C1Y,0x0000ff00); // color  bar 2 =red
			rtd_outl(REG_PTG_C2Y,0x00ff0000); // color  bar 3 =green
			rtd_outl(REG_PTG_C3Y,0x0000ff00); // color  bar 4 =blue
			rtd_outl(REG_PTG_C4Y,0xffff0000); // color  bar 5 =yellow
			rtd_outl(REG_PTG_C5Y,0xff00ff00); // color  bar 6 =cyan
			rtd_outl(REG_PTG_C6Y,0x00ffff00); // color  bar 7 =maginta
			rtd_outl(REG_PTG_C7Y,0x00000000); // color  bar 8 =Black
			rtd_outl(REG_PTG_C7Y,(rtd_inl(REG_PTG_C7Y)|0x00000007)); //7 color bar

			
			udelay(20000);											
			rtd_outl(0xb8025220,0x00000003); //Enable  CRC
			udelay(20000);											
			temp= rtd_inl(0xb8025224);  //CRC result

			if((temp==0x29169BD3)||(temp==0xF05A1C02))
		   		printk("IP_IPTG_Verify H color bar & BARW Pass\n");		
			else{
				printk("IP_IPTG_Verify H color bar & BARW fail CRC=0x%x\n",temp);		
				Fl_pass=FALSE;	
				}

			udelay(1000000);			// hold pattern on screen for tester see								
			break;
			
     
      
            case 10: // H gradient    TEST CRC
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000004); //H color bar
//			rtd_outl(REG_PTG_MAX_COLOR_CTRL,(rtd_inl(REG_PTG_MAX_COLOR_CTRL)|0x07000000)); //7 color bar
//			rtd_outl(REG_PTG_BARW,((rtd_inl(REG_PTG_BARW)&0xfffffc00)|(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff)/8)); //7 color bar

			rtd_outl(REG_PTG_C0Y,0x00000000); // black  background
			rtd_outl(REG_PTG_C3Y,0x04040400); // adjust
			rtd_outl(REG_PTG_C4Y,0x01000000); // step   
			
			udelay(20000);											
			rtd_outl(0xb8025220,0x00000003); //Enable  CRC
			udelay(20000);											
			temp= rtd_inl(0xb8025224);  //CRC result

			if((temp==0x894C4BBC)||(temp==0xFA59F937))
		   		printk("IP_IPTG_Verify H gradient & step & adjust Pass\n");		
			else{
				printk("IP_IPTG_Verify H gradient & step & adjust fail CRC=0x%x\n",temp);		
				Fl_pass=FALSE;	
				}

			udelay(1000000);			// hold pattern on screen for tester see								
			break;	
			
            case 11: // V gradient    TEST CRC
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000005); //V color bar
//			rtd_outl(REG_PTG_MAX_COLOR_CTRL,(rtd_inl(REG_PTG_MAX_COLOR_CTRL)|0x07000000)); //7 color bar
//			rtd_outl(REG_PTG_BARW,((rtd_inl(REG_PTG_BARW)&0xfffffc00)|(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff)/8)); //7 color bar

			rtd_outl(REG_PTG_C0Y,0x00000000); // black  background
			rtd_outl(REG_PTG_C3Y,0x05050500); // adjust
			rtd_outl(REG_PTG_C4Y,0x00000000); // step   
			
			udelay(20000);											
			rtd_outl(0xb8025220,0x00000003); //Enable  CRC
			udelay(20000);											
			temp= rtd_inl(0xb8025224);  //CRC result

			if((temp==0x042A3DE5)||(temp==0x558D4924))
		   		printk("IP_IPTG_Verify V gradient & step & adjust  Pass\n");		
			else{
				printk("IP_IPTG_Verify V gradient & step & adjust fail CRC=0x%x\n",temp);		
				Fl_pass=FALSE;	
				}

			udelay(1000000);			// hold pattern on screen for tester see								
			break;			

          case 12: // HV gradient    TEST CRC
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000006); //V color bar
//			rtd_outl(REG_PTG_MAX_COLOR_CTRL,(rtd_inl(REG_PTG_MAX_COLOR_CTRL)|0x07000000)); //7 color bar
//			rtd_outl(REG_PTG_BARW,((rtd_inl(REG_PTG_BARW)&0xfffffc00)|(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff)/8)); //7 color bar

			rtd_outl(REG_PTG_C0Y,0x00000000); // black  background
			rtd_outl(REG_PTG_C3Y,0x02020200); // adjust
			rtd_outl(REG_PTG_C4Y,0x00000000); // step   
			
			udelay(20000);											
			rtd_outl(0xb8025220,0x00000003); //Enable  CRC
			udelay(20000);											
			temp= rtd_inl(0xb8025224);  //CRC result

			if((temp==0x57A2C69F)||(temp==0x6EB9B006))
		   		printk("IP_IPTG_Verify HV gradient & step & adjust  Pass\n");		
			else{
				printk("IP_IPTG_Verify HV gradient & step & adjust fail CRC=0x%x\n",temp);		
				Fl_pass=FALSE;	
				}

			udelay(1000000);			// hold pattern on screen for tester see								
			break;	
          case 13: // Bitmap    TEST CRC
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000007); //V color bar
//			rtd_outl(REG_PTG_MAX_COLOR_CTRL,(rtd_inl(REG_PTG_MAX_COLOR_CTRL)|0x07000000)); //7 color bar
//			rtd_outl(REG_PTG_BARW,((rtd_inl(REG_PTG_BARW)&0xfffffc00)|(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff)/8)); //7 color bar

			rtd_outl(REG_PTG_C0Y,0x00000000); // black  background
			rtd_outl(REG_PTG_C1Y,0x00ffffff); // white  frontground			
			rtd_outl(REG_PTG_C4Y,0x00007700); // Bitmap 8x8   
			rtd_outl(REG_PTG_C5Y,0xFF0f0f00); // Bitmap 8x8   
			rtd_outl(REG_PTG_C6Y,0x0f0ff000); // Bitmap 8x8   
			rtd_outl(REG_PTG_C7Y,0xf0f0f000); // Bitmap 8x8   
			
			udelay(20000);											
			rtd_outl(0xb8025220,0x00000003); //Enable  CRC
			udelay(20000);											
			temp= rtd_inl(0xb8025224);  //CRC result

			if((temp==0xBAE4E8C3)||(temp==0x6CEB125E)||(temp==0x7CC0715E))
		   		printk("IP_IPTG_Verify Bitmap Pass\n");		
			else{
				printk("IP_IPTG_Verify Bitmap CRC=0x%x\n",temp);		
				Fl_pass=FALSE;	
				}

			udelay(1000000);			// hold pattern on screen for tester see								
			break;	

          case 14: // MV  H/Mp_adj mode    TEST: tester see
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000007); //Bitmap
//			rtd_outl(REG_PTG_MAX_COLOR_CTRL,(rtd_inl(REG_PTG_MAX_COLOR_CTRL)|0x07000000)); //7 color bar
//			rtd_outl(REG_PTG_BARW,((rtd_inl(REG_PTG_BARW)&0xfffffc00)|(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff)/8)); //7 color bar

			rtd_outl(REG_PTG_C0Y,0x00000000); // black  background
			rtd_outl(REG_PTG_C1Y,0x00ffffff); // white  frontground			
			rtd_outl(REG_PTG_C4Y,0x00007700); // Bitmap 8x8   
			rtd_outl(REG_PTG_C5Y,0xFF0f0f00); // Bitmap 8x8   
			rtd_outl(REG_PTG_C6Y,0x0f0ff000); // Bitmap 8x8   
			rtd_outl(REG_PTG_C7Y,0xf0f0f000); // Bitmap 8x8   

			rtd_outl(REG_PTG_MAX_COLOR_CTRL,0x04000f00); // Bitmap 8x8   
			rtd_outl(REG_PTG_MAX_COLOR_CTRL,0x04000f80); // Bitmap 8x8   
			
		   		printk("IP_IPTG_Verify Motion H direct  MP_ADJ \n");		

			udelay(10000000);			// hold pattern on screen for tester see
			break;				

          case 15: // MV  V/Mp_adj mode    TEST: tester see
			rtd_outl(REG_PTG_TG,rtd_inl(REG_PTG_TG)&0xfffffffd); //progressive 
			rtd_outl(REG_PTG_CTRL,(rtd_inl(REG_PTG_CTRL)&0xfffffff8)|0x0000007); //Bitmap
//			rtd_outl(REG_PTG_MAX_COLOR_CTRL,(rtd_inl(REG_PTG_MAX_COLOR_CTRL)|0x07000000)); //7 color bar
//			rtd_outl(REG_PTG_BARW,((rtd_inl(REG_PTG_BARW)&0xfffffc00)|(rtd_inl(REG_PTG_VSTA_LEN)&0x00000fff)/8)); //7 color bar

			rtd_outl(REG_PTG_C0Y,0x00000000); // black  background
			rtd_outl(REG_PTG_C1Y,0x00ffffff); // white  frontground			
			rtd_outl(REG_PTG_C4Y,0x00007700); // Bitmap 8x8   
			rtd_outl(REG_PTG_C5Y,0xFF0f0f00); // Bitmap 8x8   
			rtd_outl(REG_PTG_C6Y,0x0f0ff000); // Bitmap 8x8   
			rtd_outl(REG_PTG_C7Y,0xf0f0f000); // Bitmap 8x8   

			rtd_outl(REG_PTG_MAX_COLOR_CTRL,0x00040f00); // Bitmap 8x8   
			rtd_outl(REG_PTG_MAX_COLOR_CTRL,0x00040f80); // Bitmap 8x8   
			
		   		printk("IP_IPTG_Verify Motion V direct  MP_vs_num \n");		

			udelay(3000000);			// hold pattern on screen for tester see
			break;				

	default:
		break;
	}
	if (Fl_pass==FALSE)
		break;
}
if (Fl_pass==FALSE)
	return 0;
else
	return 1;

}




BOOL	APLL_Thermal_test()
{
	UINT8	w;
 	UINT8	num;
	UINT32 	y;
	UINT32	x = 0;
	UINT32	z = 0;
	UINT32	dummy_delay = 0;
	


rtd_outl(0xb80004dc,0x00003000); //open PLL27x clock        00003000

#if Thremal_testing==0

rtd_outl(0xb800db40, 0x02800202);       //HDMI bandgap power
rtd_outl(0xb800db44, 0x00030800);       //HDMI bandgap power  
rtd_outl(0xb802005c, 0x00130003);	    //LDO power on 

udelay(100000);

printk("480i\n");


udelay(100000);


rtd_outl(0xb802010c, 0x00700000);	//set longt path


//              Sirius Mark Script

/*
#include "ypp_adc_480i.tbl"
 udelay(200000);
#include "apll_ypp480i.tbl"                        // APLL for YPbPr480i source
 udelay(200000);
#include "sp_480i.tbl" 

#include "vgip_ch1_ypp_480i.tbl"               // vgip ch1 for ipg 480i    20130324
	
#include "m_ch1_frc_1080i10b444.tbl"	
#include "uzu_main_444_bypass480i.tbl"
 

 
#include "dpll_297MHz.tbl"
#include "dtg_fhd_fs.tbl"
 

 
#include "mtg_fhd.tbl"
#include "ivs2dvs_480i_fhd.tbl"		// ivs2dvs delay for ipg1080p to FHD
#include "m_ch1_frc_to_fs.tbl"		// mdomain change to fs mode
 
	 

#include "LVDS_FHD_1Seg_2Port.tbl"	// SFG, PIF, TX_PHY
 */

 
 // 			 Sirius Mark Script



 UINT8 BestPhase=0;
 UINT32 BestSOD=0;	 
 udelay(100000);
 printk("Long path\n");


 for (dummy_delay=2; dummy_delay<4; dummy_delay++)
	 {
        x = rtd_inl(0xb8020108)&0x0000ffff;	// set dummy_delay
		rtd_outl(0xb8020108, x | dummy_delay<<16);  

	   
        printk("Long path dummy_delay = %d\n",dummy_delay);     
        printk("0xb8020108= 0x%x \n",rtd_inl(0xb8020108));

		for (y=0; y<16; y++)
			{

				
			rtd_outl(0xb8020124, y);	// delay_cp_mode
			printk("delay_cp_mode = %d\n",y);
			printk("0xb8020108= 0x%x \n",rtd_inl(0xb8020108));

			//Smart Fit setting
			//rtd_outl(0xb8022000, 0x00000010);	
			rtd_outl(0xb8022000, 0x000000C0); // only measure odd
			rtd_outl(0xb8022004, 0x02000600);	
			rtd_outl(0xb8022008, 0x00500300);	
			rtd_outl(0xb802200c, 0x40404200);	
			rtd_outl(0xb8022010, 0x0000007a);
			rtd_outl(0xb8022024, 0x00000000);

			z = 0;
			for (num=0; num<128; num++)
				{
				x = rtd_inl(0xb802010c)&0xffffff80;	// set phase
				rtd_outl(0xb802010c, x | z); 
				
				//printk("phase = %x\n",z);
				z = z+1;
				
				for (w=0; w<255; w++)	// for delay
					w = w;
			
				rtd_outl(0xb8022010, 0x0000007b);
				while((rtd_inl(0xb8022010)&0x00000001)==1)
					{
					for (w=0; w<255; w++)
						w = w;	
					}
			
				x = rtd_inl(0xb8022020);
				//printk("sum = %x\n",x);
				printk("%d\n",x);	
				//printk("SF phase=%d,SOD=%d\n",z,x);
				if(y==15)  // long path    mode 3
					{
					if(x>BestSOD)
						{
						BestPhase=z-1;
						BestSOD=x;
						}
					}
				
				}
			}
     }


   
printk("Software Mode LONG PATH + mode 1 BestPhase=%d, BestSOD=%x \n",BestPhase,BestSOD);




/*
BestPhase=0;
BestSOD=0; 
// Smart Fit auto phase

rtd_outl(0xb8022024, 0x800000ff);
rtd_outl(0xb8022010, 0x00000053);
udelay(10000);	
for (w=0; w<255; w++)
				w = w;	

for(z=0;z<128;z++)
{
	while((rtd_inl(0xb8022024)&0x00000080)==0)		
		{
		//printk("0xb8022024=%x \n",rtd_inl(0xb8022024));
		}
//	printk("0xb8022024=%x \n",rtd_inl(0xb8022024));	
rtd_outl(0xb8022024,rtd_inl(0xb8022024)|0x00000080);
//udelay(10000);	
x = rtd_inl(0xb8022020);
	if(x>BestSOD)
			{
			BestPhase=z;
			BestSOD=x;
			} 
printk("HW Phase=%d SOD=%d \n",z,x);

}
printk("Hardware Mode LONG PATH + mode 1 BestPhase=%d, BestSOD=%x \n",BestPhase,BestSOD);
*/
#endif




#if Thremal_testing==1

rtd_outl(0xb800db40, 0x02800202);       //HDMI bandgap power
rtd_outl(0xb800db44, 0x00030800);       //HDMI bandgap power  
rtd_outl(0xb802005c, 0x00130003);	    //LDO power on 

udelay(100000);

printk("1080i\n");


//              Sirius Mark Script
/*

#include "APLL_ypp_adc_1080i.tbl"


udelay(100000);


rtd_outl(0xb802010c, 0x00700000);//set longt path

#include "APLL_apll_ypp1080i.tbl"

udelay(1000);


#include "APLL_sp_1080i.tbl"
printk("0xb8021004= 0x%x \n",rtd_inl(0xb8021004));

#include "APLL_vgip_ch1_ypp_1080i.tbl"
//#include "LVDS_FHD_1Pixel_1Seg_2Port.tbl"
udelay(1000);


#include "APLL_di_en_ch1_1080i_2d.tbl"
udelay(1000);

#include "APLL_m_ch1_frc_1080i10b444.tbl"
#include "APLL_uzu_main_444_bypass1080i.tbl"
udelay(1000);

//--
#include "APLL_DPLL_297MHz_1080i.tbl"
udelay(1000);

#include "APLL_dtg_fhd_fs_1080i.tbl"
udelay(1000);

#include "APLL_mtg_fhd_1080i.tbl"
#include "APLL_ivs2dvs_1080i_fhd.tbl"		// ivs2dvs delay for ipg1080p to FHD
//#include "m_ch1_frc_to_fs.tbl"			// mdomain change to fs mode
#include "APLL_LVDS_FHD_1Seg_2Port_1080i.tbl"

*/

//				Sirius Mark Script


UINT8 BestPhase=0;
UINT32 BestSOD=0;	

rtd_outl(0xb802010c, 0x00700000);	//set longt path
printk("Long path\n");


udelay(100000);


 for (dummy_delay=2; dummy_delay<4; dummy_delay++)
	 {
        x = rtd_inl(0xb8020108)&0x0000ffff;	// set dummy_delay
		rtd_outl(0xb8020108, x | dummy_delay<<16);  

	   
        printk("Long path dummy_delay = %d\n",dummy_delay);     
        printk("0xb8020108= 0x%x \n",rtd_inl(0xb8020108));

		for (y=0; y<16; y++)
			{

				
			rtd_outl(0xb8020124, y);	// delay_cp_mode
			printk("delay_cp_mode = %d\n",y);
			printk("0xb8020108= 0x%x \n",rtd_inl(0xb8020108));

			//Smart Fit setting
			//rtd_outl(0xb8022000, 0x00000010);	
			rtd_outl(0xb8022000, 0x000000C0); // only measure odd
			rtd_outl(0xb8022004, 0x02000600);	
			rtd_outl(0xb8022008, 0x00500300);	
			rtd_outl(0xb802200c, 0x40404200);	
			rtd_outl(0xb8022010, 0x0000007a);
			rtd_outl(0xb8022024, 0x00000000);

			z = 0;
			for (num=0; num<128; num++)
				{
				x = rtd_inl(0xb802010c)&0xffffff80;	// set phase
				rtd_outl(0xb802010c, x | z); 
				
				//printk("phase = %x\n",z);
				z = z+1;
				
				for (w=0; w<255; w++)	// for delay
					w = w;
			
				rtd_outl(0xb8022010, 0x0000007b);
				while((rtd_inl(0xb8022010)&0x00000001)==1)
					{
					for (w=0; w<255; w++)
						w = w;	
					}
			
				x = rtd_inl(0xb8022020);
				//printk("sum = %x\n",x);
				printk("%d\n",x);	
				//printk("SF phase=%d,SOD=%d\n",z,x);
				if(y==15)  // long path    mode 3
					{
					if(x>BestSOD)
						{
						BestPhase=z-1;
						BestSOD=x;
						}
					}
				
				}
			}
     }


   
printk("Software Mode LONG PATH + mode 1 BestPhase=%d, BestSOD=%x \n",BestPhase,BestSOD);




/*
BestPhase=0;
BestSOD=0; 
// Smart Fit auto phase

rtd_outl(0xb8022024, 0x800000ff);
rtd_outl(0xb8022010, 0x00000053);
udelay(10000);	
for (w=0; w<255; w++)
				w = w;	

for(z=0;z<128;z++)
{
	while((rtd_inl(0xb8022024)&0x00000080)==0)		
		{
		//printk("0xb8022024=%x \n",rtd_inl(0xb8022024));
		}
//	printk("0xb8022024=%x \n",rtd_inl(0xb8022024));	
rtd_outl(0xb8022024,rtd_inl(0xb8022024)|0x00000080);
//udelay(10000);	
x = rtd_inl(0xb8022020);
	if(x>BestSOD)
			{
			BestPhase=z;
			BestSOD=x;
			} 
printk("HW Phase=%d SOD=%d \n",z,x);

}
printk("Hardware Mode LONG PATH + mode 1 BestPhase=%d, BestSOD=%x \n",BestPhase,BestSOD);
*/
#endif




	

#if Thremal_testing==2

rtd_outl(0xb800db40, 0x02800202);       //HDMI bandgap power
rtd_outl(0xb800db44, 0x00030800);       //HDMI bandgap power  
rtd_outl(0xb802005c, 0x00130003);	    //LDO power on 

udelay(100000);

printk("1080P\n");
		// crt script

//				Sirius Mark Script

/*

#include "APLL_ypp_adc_1080p.tbl"

udelay(100000);

#include "APLL_apll_ypp1080p.tbl"
		
#include "APLL_sp_1080p.tbl"
#include "APLL_vgip_ch1_ipg_1080p.tbl"
#include "APLL_m_ch1_frc_1080p10b444.tbl"            // M-domain setting
#include "APLL_uzu_main_444_bypass1080p.tbl"         // UZU for 444 bypass , UZU disable
		
#include "APLL_DPLL_297MHz.tbl"
#include "APLL_dtg_fhd_fs.tbl"
#include "APLL_mtg_fhd.tbl"
#include "APLL_LVDS_FHD_1Seg_2Port.tbl"


*/
//				Sirius Mark Script


UINT8 BestPhase=0;
UINT32 BestSOD=0;	

rtd_outl(0xb802010c, 0x00400000);	//set Short path   Phase select:Look up table   Intinal phase:phase0
printk("Short path\n");

    
   for (dummy_delay=0; dummy_delay<4; dummy_delay++)
	   {
          x = rtd_inl(0xb8020108)&0x0000ffff;	// set dummy_delay
		  rtd_outl(0xb8020108, x | dummy_delay<<16);  

	   
          printk("Short path dummy_delay = %d\n",dummy_delay);     
          printk("0xb8020108= 0x%x \n",rtd_inl(0xb8020108));
	   
		for (y=0; y<16; y++)
			{
				
			rtd_outl(0xb8020124, y);	// delay_cp_mode
			printk("delay_cp_mode = %d\n",y);
            printk("0xb8020124= 0x%x \n",rtd_inl(0xb8020124));
			//Smart Fit setting
			//rtd_outl(0xb8022000, 0x00000010);	
			rtd_outl(0xb8022000, 0x000000C0);  // only measure odd
			rtd_outl(0xb8022004, 0x02000600);	
			rtd_outl(0xb8022008, 0x00500300);	
			rtd_outl(0xb802200c, 0x40404200);	
			rtd_outl(0xb8022010, 0x0000007a);
			rtd_outl(0xb8022024, 0x00000000);

			z = 0;
			for (num=0; num<128; num++)
				{
				x = rtd_inl(0xb802010c)&0xffffff80;	// set phase
				rtd_outl(0xb802010c, x | z); 
				
				//printk("phase = %x\n",z);
				//printk("0xb802010c= 0x%x \n",rtd_inl(0xb802010c));
				z = z+1;
			
				for (w=0; w<255; w++)	// for delay
					w = w;
			
				rtd_outl(0xb8022010, 0x0000007b);
				while((rtd_inl(0xb8022010)&0x00000001)==1)
					{
					for (w=0; w<255; w++)	// for delay
						w = w;	
					}
			
				x = rtd_inl(0xb8022020);
				//printk("sum = %x\n",x);
				//printk("\n");
				printk("%d\n",x);	
				}
			}
       }
rtd_outl(0xb802010c, 0x00600000);	//set longt path
printk("Long path\n");

 for (dummy_delay=0; dummy_delay<4; dummy_delay++)
	 {
        x = rtd_inl(0xb8020108)&0x0000ffff;	// set dummy_delay
		rtd_outl(0xb8020108, x | dummy_delay<<16);  

	   
        printk("Long path dummy_delay = %d\n",dummy_delay);     
        printk("0xb8020108= 0x%x \n",rtd_inl(0xb8020108));

		for (y=0; y<16; y++)
			{

				
			rtd_outl(0xb8020124, y);	// delay_cp_mode
			printk("delay_cp_mode = %d\n",y);
			printk("0xb8020124= 0x%x \n",rtd_inl(0xb8020124));

			//Smart Fit setting
			//rtd_outl(0xb8022000, 0x00000010);	
			rtd_outl(0xb8022000, 0x000000C0); // only measure odd
			rtd_outl(0xb8022004, 0x02000600);	
			rtd_outl(0xb8022008, 0x00500300);	
			rtd_outl(0xb802200c, 0x40404200);	
			rtd_outl(0xb8022010, 0x0000007a);
			rtd_outl(0xb8022024, 0x00000000);

			z = 0;
			for (num=0; num<128; num++)
				{
				x = rtd_inl(0xb802010c)&0xffffff80;	// set phase
				rtd_outl(0xb802010c, x | z); 
				
				//printk("phase = %x\n",z);
				z = z+1;
				
				for (w=0; w<255; w++)	// for delay
					w = w;
			
				rtd_outl(0xb8022010, 0x0000007b);
				while((rtd_inl(0xb8022010)&0x00000001)==1)
					{
					for (w=0; w<255; w++)
						w = w;	
					}
			
				x = rtd_inl(0xb8022020);
				//printk("sum = %x\n",x);
				printk("%d\n",x);	
				//printk("SF phase=%d,SOD=%d\n",z,x);
				if(y==15)  // long path    mode 3
					{
					if(x>BestSOD)
						{
						BestPhase=z-1;
						BestSOD=x;
						}
					}
				
				}
			}
     }
printk("Software Mode LONG PATH + mode 1 BestPhase=%d, BestSOD=%x \n",BestPhase,BestSOD);
/*
BestPhase=0;
BestSOD=0; 
// Smart Fit auto phase

rtd_outl(0xb8022024, 0x800000ff);
rtd_outl(0xb8022010, 0x00000053);
udelay(10000);	
for (w=0; w<255; w++)
				w = w;	

for(z=0;z<128;z++)
{
	while((rtd_inl(0xb8022024)&0x00000080)==0)		
		{
		//printk("0xb8022024=%x \n",rtd_inl(0xb8022024));
		}
//	printk("0xb8022024=%x \n",rtd_inl(0xb8022024));	
rtd_outl(0xb8022024,rtd_inl(0xb8022024)|0x00000080);
//udelay(10000);	
x = rtd_inl(0xb8022020);
	if(x>BestSOD)
			{
			BestPhase=z;
			BestSOD=x;
			} 
printk("HW Phase=%d SOD=%d \n",z,x);

}
printk("Hardware Mode LONG PATH + mode 1 BestPhase=%d, BestSOD=%x \n",BestPhase,BestSOD);
*/
#endif

return SUCCESS;

}











BOOL I_domain_IP_Verify()
{
bool success=TRUE;
printk("I_domain_IP_Verify, Load 480I IPTG \n");
IPTG_480I(); //RGB color space direct related to IPTG
success=success&IP_ABL_Verify();
if(success==TRUE)

success=success&IP_SF_Verify();
if(success==TRUE)
//success=success&IP_IPTG_Verify();
if(success==TRUE)
success=success&IP_SP_Verify();
if(success==TRUE)
success=success&IP_3D_ONMS_Verify();

return success;
}
int QC_Verifier_I_Domain(void)
{
	//example

    UINT32 	dwParameter1 = 0;
    UINT32	dwParameter2 = 0;
    UINT32 	dwParameter3 = 0;
    UINT32 	result = 0;	


	
printk("IMDVerifier\n");
//udelay(100000);
//rtd_outl(0xb8000114, 0x03000000);
//udelay(100000);
//rtd_outl(0xb8000104, 0x03000000);
//udelay(100000);
//rtd_outl(0xb8000104, 0xffffffff);
//udelay(100000);
//rtd_outl(0xb8000114, 0xffffffff);
	//-------- Module Clock & Reset Enable ---------
	rtd_maskl(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock
	rtd_maskl(0xb8000014, 0x1effffe7, 0x00000000);// disable TVSB1~3,APLL_ADC,I/M/D domain clock
	rtd_maskl(0xb8000008, 0xffff8fe9, 0x00000000);// hold TVSB1~3,APLL_ADC,I/M/D domain reset
	rtd_maskl(0xb8000008, 0xffff8fe9, 0x00007016);// release TVSB1~3,APLL_ADC,I/M/D domain reset
	udelay(100000);    
	rtd_maskl(0xb8000014, 0x1effffe7, 0xE1000018);// enable TVSB1~3,APLL_ADC,I/M/D domain clock

    
//rtd_outl(0xb800095c, 0x40000030); //add pic haf    
#if 1

//printk("IMD process 1 LVDS_display_set \n");

//printk("IMD process 2 enable LVDS power\n");
//       ew(0xb800091c,0xff684423);  // enable LVDS power 

printk("IMD process 3 IMD_Tst \n");
    result = result + IMD_Tst();
    //result = result + APLL_Thermal_test();  //test APLL   20130821
	
//	imd_error=result;                                            // 

//#include "m_ch1_frc_480i10b444.tbl"
//#include "LVDS_FHD_1Pixel_1Seg_4Port.tbl"	


//LVDS_display_set(); //   enable lvds gpo control
//rtd_outl(0xb8000884, 0xC1320020);
    if (result)
		return _FAIL;
    else
		return _SUCCESS;

#else
printk("IDomain IP test \n");

//printk("IMD process 2 enable LVDS power\n");
//       ew(0xb800091c,0xff684423);  // enable LVDS power 


I_domain_IP_Verify();
//	imd_error=result;                                            // 

//#include "m_ch1_frc_480i10b444.tbl"
//#include "LVDS_FHD_1Pixel_1Seg_4Port.tbl"	


//LVDS_display_set(); //   enable lvds gpo control
//rtd_outl(0xb8000884, 0xC1320020);
    if (result)
		return _FAIL;
    else
		return _SUCCESS;

//     result=  I_domain_IP_Verify();
//IPTG_480I();
    //APLL_Thermal_test();
     return SUCCESS;//result|APLL_Thermal_test();
#endif
	
	printk("\n");	

	return SUCCESS;	
}

