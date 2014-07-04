#include <qc_verify_common.h>
#include <VBI_qc.h>
#include <VBI_verify.h>
#include <rbusVbiReg.h>
#include <rbusVDTopReg.h>

//=====================================================
#define ypbpr_CC_VALUE 0x8080
#define VBI_TTX_DMA_WIDTH			(64) // 64 bytes
#define MEM_OFFSET					(0xA0000000) //0xa0000000
#define ALIGN_DMA	__attribute__	((aligned(8))) //是不足8位的補齊， 所有的都以8的倍數的地址 定址
#define VBI_TTX_DMA_LENGTH_ALIGN	(24) // 24 lines, because we need 256 alignment (24*64=6*4*64=6*256) //48,when dump field select => 0
#define VBI_TTX_DMA_LENGTH		(21) // 21 lines, 6~26  //42,when dump field select => 0, 不同的值在dump field select =1 時,打印的value 會不一樣
//=====================================================
static UINT8 ALIGN_DMA vbi_ttx_dma_org[VBI_TTX_DMA_LENGTH_ALIGN+4][VBI_TTX_DMA_WIDTH]; // 64 bytes * 24 lines (+4 lines to prevent DMA writing through end address)
static UINT8 (*vbi_ttx_dma)[][VBI_TTX_DMA_WIDTH] = NULL;

void Display_Init(void)
{
	printk("set display start ...\n");
	#include "ipg_480i.tbl"
	vbi_delay(100);
	#include "sp_ipg_480i.tbl"
	vbi_delay(100);
	#include "vgip_ch1_ipg_480i.tbl"
	vbi_delay(100);
	#include "m_ch1_frc_to_fs.tbl"
	vbi_delay(100);
	#include "uzu_main_444_480i_to_fhd.tbl"
	vbi_delay(100);
	#include "dpll_297MHz.tbl"
	vbi_delay(100);
	#include "dtg_fhd_fs.tbl"
	vbi_delay(100);
	#include "mtg_fhd.tbl"
	vbi_delay(100);
	#include "ipg_fs_480i.tbl"
	vbi_delay(100);
	#include "lvds_fhd_1Seg_2Port.tbl"
	printk("set display OK !!\n");
}


void AV_Init(void)
{
	rtd_maskl(0xb8022210, ~(_BIT30|_BIT29|_BIT28), _BIT29);
	//////DAC, Sirius-DesignSpec-TVSB1_Analog for av_out setting
	rtd_maskl(0xb8033004,0xFFFFFFFF, 0x00120000);//[20] REG_VDAC_POWMBIAS
	rtd_maskl(0xb803300C,0xFFFFFFFF, 0x00000010);//[4] IDACO_TV 0: power down, 1: power on
	rtd_maskl(0xb8033024,0xFFFFFFF8, 0x00000000);//[2:0]0:Source From VDADC

	////-------- VD ADC ----------------------------------------------------
	////ADC POWER ON
	////ADC_POWER[0]Blue Channel ADC Power On,ADC_POWER[1]Green Channel ADC Power On,ADC_POWER[2]Red Channel ADC Power On,ADC_POWER[3]ADC Bandgap Power On
	////ADC_POWER[4]SOG1 Power On,ADC_POWER[5]SOG0 Power On,ADC_POWER[6]ADC clock Power On,ADC_POWER[7]Online Auto_SOY ADC Clock Power On
	rtd_maskl(0xb8020000,0xFFFFFFFF,0x000000FF); 

	// externel [1]LDO100MA_POW [0]VDADC power on	3.3V				// VDADC_POW_CTL
	rtd_maskl(0xb802005C,0xFFFFFFFF,0x00000003); 

	// internel [22]ADC Power On [21]LDO Power On    1.xV
	rtd_maskl(0xb8020054,0xFFFFFFFF,0x00600000); 

	//-------- VD ADC PATH-------------------------------------------------
	//REG_VDADC_CLAMP_CTRL2[10]		mux1----[2:0]:VDC UP/DN Enable,[10:8]:Negative UP/DN NCLAMP_EN Enable-|
	//SV0_Y                         ----------------------------------------------------------------------|	- REG_VDADC_CLAMP_CTRL1[10:9] mux3
	//REG_VDADC_CLAMP_CTRL2[9:8]	mux2----[2:0]:VDC UP/DN Enable,[10:8]:Negative UP/DN NCLAMP_EN Enable-|
	//comment:
	//004c REG_VDADC_CLAMP_CTRL2[10] : 0: 9+ 1: 8+
	//004c REG_VDADC_CLAMP_CTRL2[9:8]: 00/01: 12+, 10/11: 13+
	//0048 REG_VDADC_CLAMP_CTRL1[10:9]: 00: 9++(mux1), 01: 10+, 10:11++(mux2)
	//[sirius] vin9p: cvbs vin10p: sv
	//---------------------------------------------------------------------
	rtd_maskl(0xb802004c,0xFFFFFCE3,0x00000100);//VD_ADC_CLAMP_CTL_2: [9:8] = 0x1,vin12p [4:2] = 0, nagtive clamp disable
	rtd_maskl(0xb8020048,0xFFFF191F,0x00008400);//VD_ADC_CLAMP_CTL_1: [15:13] = 0x4,dc restore v2  [10:9] = 0x2,vin11pp [7:5] = 0,clamp disable
	rtd_maskl(0xb8020050,0xFFFFF8F8,0x00000000);//VD_ADC_UPDN_CTL: [10:8] = 0,nagtive updn clamp disable [2:0] = 0, updn clamp disable

	/////IFD_TOP////
	rtd_outl(0xb8033080,0x00100001);    // for PLL27X 2.5V LDO, MBias&Global power should enable
	rtd_outl(0xb80330ac,0x00000152);    // for PLL27X 2.5V LDO, IFD ADC_LDO power


	///// IFD /////	(setting decimation filter, from PacificPrime script, BW = 6.5MHz)
	rtd_outl(0xb80040D4,0x00000100);		// vd_fifo_clr = 1						// VD_INPUT_FIFO_STATUS1
	rtd_outl(0xb80040D4,0x00000000);		// vd_fifo_clr = 0						// VD_INPUT_FIFO_STATUS1
	vbi_delay(10);

	rtd_outl(0xb8004000,0x00000030);		// tap1~4: 3,44,124,169 (0x03,0x2c,0x7c,0xa9)x16		// input_flt_tap_0_1
	rtd_outl(0xb8004004,0x02C007C0);		// tap1~4: 3,44,124,169 (0x030,0x2c0,0x7c0,0xa90)		// input_flt_tap_2_3
	rtd_outl(0xb8004008,0x0A901FDB);		// [12:0] = tap5						// input_flt_tap_4_5
	rtd_outl(0xb800400c,0x00120026);									// input_flt_tap_6_7
	rtd_outl(0xb8004010,0x00310022);									// input_flt_tap_8_9
	rtd_outl(0xb8004014,0x1FFA1FCF);									// input_flt_tap_10_11
	rtd_outl(0xb8004018,0x1FC21FE3);									// input_flt_tap_12_13
	rtd_outl(0xb800401C,0x0025005D);									// input_flt_tap_14_15
	rtd_outl(0xb8004020,0x005C0014);									// input_flt_tap_16_17
	rtd_outl(0xb8004024,0x1FA91F66);									// input_flt_tap_18_19
	rtd_outl(0xb8004028,0x1F890012);									// input_flt_tap_20_21
	rtd_outl(0xb800402C,0x00B400FA);									// input_flt_tap_22_23
	rtd_outl(0xb8004030,0x008F1F8C);									// input_flt_tap_24_25
	rtd_outl(0xb8004034,0x1E821E40);									// input_flt_tap_26_27
	rtd_outl(0xb8004038,0x1F6101E1);									// input_flt_tap_28_29
	rtd_outl(0xb800403C,0x050607A2);									// input_flt_tap_30_31
	rtd_outl(0xb8004040,0x08A50000);									// input_flt_tap_32_33
	vbi_delay(10);

	rtd_outl(0xb80040A4,0x00000000);		// disable sv_yc_switch					// VD_IN_DELAY_SEL2
	rtd_outl(0xb80040AC,0x00000030);		// decimation filter [6:4] BW [0] 0: data from DF; 1: direct from ADC	// VD_INOUT_CTRL
	vbi_delay(10);

	//-------- VD setting------------------------------------------------
	// vd initial setting
	rtd_outl(0xb8003004,0x00000000);		// set AV							// VIDEO_CONTROL1
	rtd_outl(0xb8003080,0x00000000);		// decimation filter has been changed				// INOUT_CTRL
	rtd_outl(0xb800309C,0x00000047);		// set bgate_raw_sel enable					// VIDEO_CONTROL2
	rtd_outl(0xb8003620,0x00000108);		// set VDC 444 output					// FSW_CTRL2
	rtd_outl(0xb8003764,0x0008007F);		// bit[9:8]=01, select Select the VCO freq = 432M			// MISC_CONTROL
	rtd_outl(0xb8003794,0x00000000);		// disable pattern generator					// PATTERN_CONTROL
	rtd_outl(0xb80037FC,0x00000000);		// Disable clamp test mode					// ADC_UPDN_CTRL
	rtd_outl(0xb8003608,0x000000C9);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
	rtd_outl(0xb800360C,0x00000000);		// set Y							// CLAMP_UPDN_EN
	rtd_outl(0xb8003610,0x000000FF);		// enable AD1~AD4 clamp up/dn				// CLAMP_RGB_UPDN_EN

	////vdadc swith dc restore to clamp
	rtd_maskl(0xb8020050,0xFFFFF8F8,0x00000104); // [2:0] = 0x4enable clamp updn V2[10:8] = 0x1 negtive enable clamp updn a0n
	vbi_delay(10);

	//sirius vd adc setting
	rtd_maskl(0xb8020048,0xFF0F1FFF,0x00C00000);//[23:20] = 0xC 1.3v we need 1.28v [15:13] disable dc restore
	rtd_maskl(0xb8020054,0xFFFFFC7F,0x00000280);//adc_ctrl[9:7] = 0x5, 1.05v vref(vtb gain) = 1.05v
	rtd_maskl(0xb802005c,0x0000FFFF,0x20000000);//adc_ctrl[29] = 1 sha = 0.6
	rtd_maskl(0xb8020058,0xFFFFFFFC,0x00000000);//[1:0] = 0 the default should be X1 multiple

	//swith panel source to vd
	rtd_maskl(0xb8022210,0x8FFFFFFF,0xa0000000); //[30:28] = 0x2 
	vbi_delay(10000);
	printk("[AV] VD lock status: %x \n", rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR));
}

void IFD_Init(void)
{
	//先執行IFD 的qc code 
	printk("[TV] VD lock status: %x \n", rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR));
}

#ifdef YPP_Input
void YPbPr_Init(void)
{
#ifdef YPPin_480i
	#include "ypp_adc_480i.tbl"
	#include "apll_ypp480i.tbl"
	#include "sp_ypp_480i.tbl"
	#include "vgip_ch1_ypp_480i.tbl"
	#include "bypass_di_uzd_ch1_444_10b.tbl"
	#include "m_ch1_frc_to_fs.tbl"
	#include "uzu_main_444_480i_to_fhd.tbl"
	#include "dpll_297MHz.tbl"
	#include "dtg_fhd_fs.tbl"
	#include "mtg_fhd.tbl"
	#include "ypp_fs_480i.tbl"
	#include "lvds_fhd_1Seg_2Port.tbl"
	printk("[Slicer] YPbPr_Init 480i done !!\n");
#endif
#ifdef YPPin_1080i
	#include "apll_ypp1080i.tbl"
	#include "ypp_adc_1080i.tbl"
	#include "sp_ypp_1080i.tbl"
	#include "vgip_ch1_ypp_1080i.tbl"
	#include "di_1080i_uzd_ch1_422_8b.tbl"
	#include "m_ch1_frc_1080p8b422.tbl"
	#include "uzu_main_444_1080i_to_fhd.tbl"
	#include "dpll_297MHz.tbl"
	#include "dtg_fhd_frc.tbl"
	#include "mtg_fhd.tbl"
	#include "lvds_fhd_1Seg_2Port.tbl"
	printk("[Slicer] YPbPr_Init 1080i done !!\n");
#endif
}
#endif

#ifdef CC_verify_test
void  CC_Init(void)
{
//----------------       CC  setting  start ------------------------------
	rtd_outl(VBI_TT_VBI_NOISY_CTRL1_VADDR, 0x20500000);  // bit 29  set that data from vd put through 16 tape low pass filter
	rtd_outl(VBI_TT_VBI_NOISY_CTRL4_VADDR, 0x0f043110);  //  resample data don't do "rounding" 

	if ( rtd_inl(VDC_VSYNC_TIME_CONST_VADDR) & _BIT7 )	// field_polarity
		rtd_outl(VBI_VBISL0_VADDR, 0x00000020);
	else
		rtd_outl(VBI_VBISL0_VADDR, 0x00000000);
	 
	rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x006c2713);    
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_9_12_VADDR, 0x00000000);  //line 9,10,11,12           
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_13_16_VADDR, 0x00000000);                              
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_17_20_VADDR, 0x00000000);  //line 17,18,19,20	          
	rtd_outl(VBI_TT_VBI_DTO_REGISTER1_VADDR, 0x0f911ad0);
	//rtd_outl(VBI_TT_VBI_DTO_REGISTER1_VADDR, 0x0f911b00);//fw setting	
	//rtd_outl(VBI_TT_VBI_NOISY_CTRL3_VADDR, 0x005a0100);//錯1bit 不發flag
	rtd_outl(VBI_TT_VBI_NOISY_CTRL3_VADDR, 0x005a0000);
	rtd_outl(VBI_TT_VBI_CO_CH_CTRL_VADDR, 0x00000000);

	rtd_outl(VDC_VBI_CO_CH_CTRL0_VADDR, 0x0000000f);// co-channel detected frame
	rtd_outl(VDC_VBI_CO_CH_CTRL1_VADDR, 0x0000000a);// co-channel detection back-porch different threshold

	printk("[1]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[2]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[3]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[4]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[5]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));

	if (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7)
	{
		printk("#########CC Cochannel \n" );
		//------------------------------ for   co_channel  -------------------------
		rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x006c2733); //adaptive slicer level
		rtd_outl(VBI_TT_VBI_DATA_STATUS_VADDR, 0x00003c00); //remember enable cc interrupt
		rtd_outl(VBI_TT_VBI_CO_CH_CTRL_VADDR, 0x400000a0); //force compensation on
		rtd_outl(VBI_TT_VBI_CC_CTRL0_VADDR, 0x87041000); //CC vote decision diable
		rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_21_24_VADDR, 0x00000011); //line 21,22,23,24->line 21 on
		//rtd_outl(0xb80194d4, 0x00000076);//VD co-channel on bit7->0
		//rtd_outl(0xb80194d8, 0x00000081);//VD co-channel on bit7->1,就不用shift 1條 line
		//rtd_outl(0xb80193c4, 0x00000083);//VD co-channel on bit7->1
		//rtd_outl(0xb801948c, 0x00000000);//VD co-channel on bit2->0
		//rtd_outl(0xb80190b0, 0x0000000d);//VD co-channel on bit7,6->0

//		rtd_maskl(0xb80195e4,~_BIT7, _BIT7);//VD co-channel 1-2-1 filter eable, bit7->1
//		rtd_maskl(0xb8019378,~_BIT7, _BIT7);//VD co-channel 1-2-1 filter eable, bit7->1
//		rtd_maskl(0xb8019374,~(_BIT9|_BIT8), _BIT8);//VD new vdetect  eable bit8->1,,就不用shift 1條 line    (regardless of  cochannel????)

		if(rtd_inl(VDC_NEW_VDETECT_CTRL_VADDR)&_BIT7)	// new_vdetect_en =1
		{
			rtd_maskl(VDC_VCR_OPTION_VADDR,~_BIT7, 0);//VD co-channel 1-2-1 filter eable, bit7->0
			rtd_maskl(VDC_NEW_VDETECT_LOOP_TH2_VADDR,~_BIT7, 0);//VD co-channel 1-2-1 filter eable, bit7->0
			rtd_maskl(VDC_NEW_VDETECT_CTRL_VADDR,~(_BIT9|_BIT8), _BIT8);//VD new vdetect  eable bit8->1,,就不用shift 1條 line    (regardless of  cochannel????)
			printk("#########Is new v detect \n" );
		}
		else
		{	// old v detect
			rtd_maskl(VDC_VCR_OPTION_VADDR,~_BIT7, _BIT7);//VD co-channel 1-2-1 filter eable, bit7->1
			rtd_maskl(VDC_NEW_VDETECT_LOOP_TH2_VADDR,~_BIT7, _BIT7);//VD co-channel 1-2-1 filter eable, bit7->1
			rtd_maskl(VDC_NEW_VDETECT_CTRL_VADDR,~(_BIT9|_BIT8), 0);//VD new vdetect  eable bit8->0,,就不用shift 1條 line    (regardless of  cochannel????)
			printk("#########Is old v detect \n" );
		}
		rtd_maskl(VDC_HDETECT_GATE_CTRL_VADDR,~_BIT2, 0);//VD co-channel on ,hdetect lpf disable bit2->0
		rtd_maskl(VDC_H_LOOP_MAXSTATE_VADDR,~(_BIT7|_BIT6|_BIT5), _BIT5);//VD bit7,bit6->0,hlock disable in vsync   bit5->1,hstate_fixed on==> the key of co-channel becomes better than pacific/AT
		//------------------------------ for   co_channel  -------------------------
	}
	else
	{
		printk("#########CC Normal \n" );
		//------------------------------ for   noise/ eye  -------------------------
		rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x006c2713);  //fixed slicer level
		rtd_outl(VBI_TT_VBI_DATA_STATUS_VADDR, 0x00004600);  //remember enable cc interrupt
		rtd_outl(VBI_TT_VBI_CO_CH_CTRL_VADDR, 0x000000a0);  //force compensation off
		rtd_outl(VBI_TT_VBI_CC_CTRL0_VADDR, 0xc7041000);  //CC vote decision enable
		rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_21_24_VADDR, 0x00000011);  //line 21,22,23,24->line 21 on

		rtd_maskl(VDC_VCR_OPTION_VADDR,~_BIT7, 0);//VD co-channel off 1-2-1 filter(1) disable, bit7->0
		rtd_maskl(VDC_NEW_VDETECT_LOOP_TH2_VADDR,~_BIT7, 0);//VD co-channel off 1-2-1 filter(2) disable, bit7->0
		rtd_maskl(VDC_NEW_VDETECT_CTRL_VADDR,~(_BIT9|_BIT8), _BIT8);//VD new vdetect  eable bit8->1(regardless of  cochannel)
		rtd_maskl(VDC_HDETECT_GATE_CTRL_VADDR,~_BIT2, _BIT2);//VD co-channel off  hdetect lpf enable ,bit2->1
		rtd_maskl(VDC_H_LOOP_MAXSTATE_VADDR,~(_BIT7|_BIT6|_BIT5), (_BIT7|_BIT6));//VD co-channel off  bit7,bit6->1,hlock enable in vsync bit5->0,hstate_fixed disable
		//------------------------------ for   noise/ eye    -------------------------
	}
	//特調
	//rtd_outl(0xb8020004, 0x5b455555);//[26:24]=011
	//rtd_outl(0xb8020020, 0x30104038); //[16:12] = 00100

//----------------       CC  setting  end ------------------------------	
	printk("[Slicer] CC_Init done !!\n");
}

UINT8 CC_verify(void)
{
	UINT32 i=0, j=0;
	tt_vbi_loop_filter_i_gain_register_RBUS tt_vbi_loop_filter_i_gain_register;	// 3_4a1c

	vbi_delay(100);
	printk("TT_VBI_Control_Register[3_4a00]: %x, TT_VBI_LOOP_FILTER_I_GAIN_REGISTER[3_4a1c]: %x\n",rtd_inl(VBI_TT_VBI_CONTROL_REGISTER_VADDR),rtd_inl(VBI_TT_VBI_LOOP_FILTER_I_GAIN_REGISTER_VADDR));
	printk("TT_VBI_CO_CH_CTRL[3_4a6c]: %x\n",rtd_inl(VBI_TT_VBI_CO_CH_CTRL_VADDR));
	printk("#########CC START \n" );

	UINT8 ucCoCh = (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7);
	printk("=== coch flag = %x\n",ucCoCh );

	while(i<100)
	{
		i++;
		vbi_delay(100);
		if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT17)==_BIT17)
		{ // CC ready
//			printk("#########CC READY  = %d\n",i );
			break;	// jj test
		}
		rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR,~_BIT17,_BIT17);//clr CC ready bit
		if(ucCoCh != (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7))
		{
			ucCoCh = (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7);
			printk("=== coch flag changed !!!! = %x\n",ucCoCh );
		}
	}

	i = 0;
	while(i<100000)
	{
		i++;
		vbi_delay(10);
		if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT17)==_BIT17) // CC ready
		{
			rtd_maskl(VBI_TT_VBI_PATTERN_SEL_VADDR, ~_BIT13, _BIT13);//cc pattern compare
			if (rtd_inl(VBI_TT_VBI_CC_CTRL1_VADDR)&_BIT31)//find start
			{
				printk("#########FIND CC COMPARE START \n" );
				for (j=0;j<350000;j++)
				{
					if(ucCoCh != (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7))
					{
						ucCoCh = (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7);
						printk("=== coch flag changed !!!! = %x\n",ucCoCh );
					}

					if((j & 0x000003ff) == 0x00000000)
					{
						tt_vbi_loop_filter_i_gain_register.regValue = rtd_inl(VBI_TT_VBI_LOOP_FILTER_I_GAIN_REGISTER_VADDR);
						printk("noisy_status = %x, slicer_level = %x \n",rtd_inl(VDC_NOISE_STATUS_VADDR),tt_vbi_loop_filter_i_gain_register.tt_vbi_slicer_level_iir);
					}
					vbi_delay(10);
					if (rtd_inl(VBI_VBI_DEBUG_MODE_VADDR)&_BIT12)
						break;
				}
				if (j<35000)
					printk("\n#########CC COMPARE FAIL, i = %d \n",j );
				else
					printk("\n#########CC COMPARE OK ! \n");

				rtd_maskl(VBI_TT_VBI_PATTERN_SEL_VADDR, ~_BIT13, 0);//cc pattern compare stop
				rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT17, _BIT17);
				rtd_maskl(VBI_VBI_DEBUG_MODE_VADDR,~_BIT12, _BIT12);//clear error flag
				break;
			}
			else
			{
				if((i & 0x00000fff) == 0x00000000)
					printk("FIND CC COMPARE START... \n" );
			}
		}
	}

	printk("@@@@@@@@@CC END \n" );
	return _FAIL;
}
#endif


#ifdef TT_WSS_VPS_test
void TT_WSS_VPS_Init(void)
{
//==================== For  vd  Slicer_1   TT  setting  start =============================================
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_5_8_VADDR, 0x66660000); // line 7,8
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_9_12_VADDR, 0x66666666); // line 9,10,11,12
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_13_16_VADDR, 0x66666666); // line 13,14,15,16
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_17_20_VADDR, 0x66666666); // line 17,18,19,20 
	//rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_21_24_VADDR, 0x66666666); // line 21,22,23,24  
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_21_24_VADDR, 0x00006666); // line 21,22,23,24  for pattern 2 co channel
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_25_26_VADDR, 0);
	rtd_maskl(VBI_VBI_FPGA_TEST1_VADDR,~_BIT6, _BIT6); // 1:toggle dump interrupt when having slicer data,for pacific' C

	if ( rtd_inl(VDC_VSYNC_TIME_CONST_VADDR) & _BIT7 )	// field_polarity
	rtd_outl(VBI_VBISL0_VADDR, 0x00000060);
	else
	rtd_outl(VBI_VBISL0_VADDR, 0x00000040);

	rtd_outl(VBI_TT_VBI_NOISY_CTRL1_VADDR, 0x21500000);	// bit 29  set that data from vd put through 16 tape low pass filter
														// start code correction is 80(50h)
	//rtd_outl(VBI_TT_VBI_CO_CH_CTRL_VADDR, 0x00000000); 
	//rtd_outl(VBI_TT_VBI_NOISY_CTRL4_VADDR, 0x0f043110);  //   bit 20 = 0 : disable fix slicer level, replace by adaptive slicer level
	rtd_outl(VBI_TT_VBI_NOISY_CTRL2_VADDR, 0x80800099);//20120705 kist modify,0x87->0x80,0xa5->0x99

	//rtd_outl(VBI_TT_VBI_STATUS1_VADDR, 0x800e01bb); //  setting  check tt-line

	rtd_outl(VDC_VBI_CO_CH_CTRL0_VADDR, 0x0000000f);// co-channel detected frame
	rtd_outl(VDC_VBI_CO_CH_CTRL1_VADDR, 0x0000000a);// co-channel detection back-porch different threshold

	printk("[1]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[2]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[3]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[4]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));
	vbi_delay(1000);
	printk("[5]0xb8003234: %x, 0xb8003238: %x\n",rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR),rtd_inl(VDC_VBI_CO_CH_CTRL1_VADDR));

	if (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7)
	{
		printk("#########TT Cochannel \n" );	
		//------------------------------ for   co_channel  -------------------------
		rtd_outl(VBI_TT_VBI_NOISY_CTRL1_VADDR, 0x213a0000); //correlation = 0x50->0x3a
		rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x5b5b2733);//adaptive slicer level
		rtd_outl(VBI_TT_VBI_DATA_STATUS_VADDR, 0x00003c00);//0x3c for co-channel,remember enable tt/wss/vps  interrupt
		rtd_outl(VBI_TT_VBI_CO_CH_CTRL_VADDR, 0x400000a0);//force compensation on
		//rtd_outl(0xb80194d4, 0x00000076);//VD co-channel on bit7->0, New Vsyn feature not act
		//rtd_outl(0xb80194d8, 0x00000081);//VD co-channel on bit7->1,就不用shift 1條 line
		//rtd_outl(0xb80193c4, 0x00000083);//VD co-channel on bit7->1
		//rtd_outl(0xb801948c, 0x00000000);//VD co-channel on bit2->0
		//rtd_outl(0xb80190b0, 0x0000000d);//VD co-channel on bit7,6->0
		rtd_maskl(VDC_VCR_OPTION_VADDR,~_BIT7, _BIT7);//VD co-channel 1-2-1 filter eable, bit7->1
		rtd_maskl(VDC_NEW_VDETECT_LOOP_TH2_VADDR,~_BIT7, _BIT7);//VD co-channel 1-2-1 filter eable, bit7->1,就不用shift 1條 line
		rtd_maskl(VDC_NEW_VDETECT_CTRL_VADDR,~(_BIT9|_BIT8), _BIT8);//VD new vdetect  eable bit8->1    (regardless of  cochannel????),,new_vdetect_max_limit_value_en disable
		rtd_maskl(VDC_HDETECT_GATE_CTRL_VADDR,~_BIT2, 0);//VD co-channel on ,hdetect lpf disable bit2->0
		rtd_maskl(VDC_H_LOOP_MAXSTATE_VADDR,~(_BIT7|_BIT6|_BIT5), _BIT5);//VD bit7,bit6->0,hlock disable in vsync   bit5->1,hstate_fixed on==> the key of co-channel becomes better than pacific/AT
		//rtd_maskl(0xb8019094,~(_BIT5|_BIT4), 0);//kill gate disable
	//------------------------------ for   co_channel  -------------------------
	}
	else
	{
		printk("#########TT Normal\n");
	 	//------------------------------ for   normal/noise/eye  -------------------------
		rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x5b5b2713);  //fixed slicer level
		rtd_outl(VBI_TT_VBI_DATA_STATUS_VADDR, 0x00004600);  //remember enable tt/wss/vps  interrupt(bit30->wss ,bit28 ->vps, bit27 ->tt)
		rtd_outl(VBI_TT_VBI_CO_CH_CTRL_VADDR, 0x000000a0);  //force compensation off
		//rtd_outl(0xb80194d4, 0x000000f6);//VD co-channel off bit7->1
		//rtd_outl(0xb80194d8, 0x00000001);//VD co-channel off bit7->0
		//rtd_outl(0xb80193c4, 0x00000003);//VD co-channel off bit7->0
		//rtd_outl(0xb801948c, 0x00000004);//VD co-channel off bit2->1
		//rtd_outl(0xb80190b0, 0x000000cd);//VD co-channel off bit7,6->1
		rtd_maskl(VDC_VCR_OPTION_VADDR,~_BIT7, 0);//VD co-channel off 1-2-1 filter(1) disable, bit7->0
		rtd_maskl(VDC_NEW_VDETECT_LOOP_TH2_VADDR,~_BIT7, 0);//VD co-channel off 1-2-1 filter(2) disable, bit7->0
		rtd_maskl(VDC_NEW_VDETECT_CTRL_VADDR,~(_BIT9|_BIT8), _BIT8);//VD new vdetect  eable bit8->1(regardless of  cochannel),,new_vdetect_max_limit_value_en disable
		rtd_maskl(VDC_HDETECT_GATE_CTRL_VADDR,~_BIT2, _BIT2);//VD co-channel off  hdetect lpf enable ,bit2->1
		rtd_maskl(VDC_H_LOOP_MAXSTATE_VADDR,~(_BIT7|_BIT6|_BIT5), (_BIT7|_BIT6));//VD co-channel off  bit7,bit6->1,hlock enable in vsync bit5->0,hstate_fixed disable
		//rtd_maskl(0xb8019094,~(_BIT5|_BIT4),(_BIT5|_BIT4));//kill gate enable
	//------------------------------ for   normal/noise/ eye -------------------------
	}
	rtd_outl(VBI_TT_VBI_CLAMPAGC_CTRL_VADDR,0x83c03c0c);//d gain = 0xc
	rtd_outl(VBI_TT_VBI_LOOP_FILTER_I_GAIN_REGISTER_VADDR,0x00004444);//loop filter gain kp = 0x4
	rtd_outl(VBI_TT_VBI_NOISY_CTRL4_VADDR, 0x0f023110);  //kp of TT in data area
	rtd_outl(VBI_TT_VBI_DTO_FRAME_START_VADDR ,  0xbe6fb4a8);//0x78->0x6f
	rtd_outl(VBI_TT_VBI_DTO_REGISTER2_VADDR ,  0x15991599);
	rtd_outl(VBI_TT_VBI_NOISY_CTRL6_VADDR ,  0x00000000);

#ifdef AGC_slicer_level
	rtd_outl(VBI_TT_VBI_CONTROL_REGISTER_VADDR, 0x4b4b2753);  //agc slicer level
	rtd_outl(VBI_TT_VBI_AGC_SLICE_LEVEL_VADDR,0x980050ff);
	rtd_outl(VBI_TT_VBI_AGC_SLICE_LEVEL1_VADDR,0x0a000000);
	rtd_outl(VBI_TT_VBI_AGC_SLICE_LEVEL2_VADDR,0x00000004);
#endif

#ifdef Pattern6_setting//dto setting for patttern 6
	rtd_outl(VBI_TT_VBI_DTO_REGISTER1_VADDR, 0x0f8c1ad0);//0f91->0f8f	
	rtd_outl(VBI_TT_VBI_NOISY_CTRL4_VADDR, 0x0f013110);  //kp of TT in data area for pattern 6
	rtd_maskl(VBI_TT_VBI_PAGE6_VADDR,0xffffffc0,0x6);//for pattern 6
#endif

#ifdef Odd_parity_recovery
	rtd_outl(VBI_TT_VBI_ODD_PARIORITY_RECOVERY_VADDR, 0x0000008a); //enable correct one bit error
	rtd_outl(VBI_TT_VBI_NOISY_CTRL3_VADDR, 0x805a0000);//replace error data by corrected  data 
	rtd_outl(VBI_TT_VBI_ODD_PARIORITY_RECOVERY_1_VADDR, 0x3fffffff); //odd parity recovery row 0 ~row25
#endif

//==================== For  Slicer_1   TT setting  end =============================================
	

// -------------------------   For   Slicer_1   VPS  WSS  setting  START ------------------------------------------   
#ifdef VPS_test
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_13_16_VADDR,  0x33666666);//line 13,14,15,16	//vd line 16 for vps
	rtd_outl(VBI_TT_VBI_NOISY_CTRL5_VADDR,  0x008200a0);//vps start code detect region
#endif

#ifdef WSS_test
	rtd_outl(VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_21_24_VADDR,  0x00cc6666);//line 24,23,22,21   //vd line 23 for wss
	//rtd_outl(VBI_TT_VBI_WSS_VPS_VOTE_VADDR,0x110f2d11);//WSS vote enable
#ifdef WSS_from_CC_path
	rtd_outl(VBI_TT_VBI_WSS_VPS_VOTE_VADDR,0x190f2d11);//WSS vote enable,wss from VD without burst(CC path)
	rtd_outl(VBI_TT_VBI_WSS_VPS_VOTE2_VADDR,0x84F03E70);//wss setting for CC path
#endif
#endif
//==================== For  Slicer_1   VPS/WSS setting  end =============================================

	//特調
	//rtd_outl(0xb8020004, 0x5b455555);//[26:24]=011
	//rtd_outl(0xb8020020, 0x30104038); //[16:12] = 00100

	// Read  0xb8030a30(1803_0b30)     bit16  vps_VPS_rdy 
	// Read  0xb8030a40 (bit 7:0) ~ 0xb8030a4c (bit 31:0)  VPS  data
	// Read  b8030a30(1803_0b30)     bit18  tt_WSS_rdy 
	// Read  0xb8030a2C  (Bit 31:16)  WSS  data

	//  for  TT  pattern  data_error  trigger
	//rtd_outl(VBI_TT_VBI_PATTERN_SEL_VADDR,0x0F000100);  // for  tt1033  pattern 1
	rtd_outl(VBI_TT_VBI_PATTERN_SEL_VADDR,0x0F000200);  // for  tt1033  pattern 2
	//rtd_outl(VBI_TT_VBI_PATTERN_SEL_VADDR,0x0F000400);  // for  tt1033  pattern 4
	//rtd_outl(VBI_TT_VBI_PATTERN_SEL_VADDR,0x0F001000);  // for  tt1033  pattern 6

	printk("[Slicer] TT_WSS_VPS_Init done !!\n");
}

UINT8 TT_WSS_VPS_verify(void)
{
	UINT32 i = 0, j = 0, k = 0, m = 0, wss_value = 1, wss_init_value = 0;
	UINT8 tt_detect = _SUCCESS;
	UINT8  tt_dma_data[12] = {0x9b,0x8c,0x5e,0x49,0xc7,0xd0,0x38,0x02,0x15,0x2f,0x64,0x73};
#ifdef VPS_test
	UINT32 vps_byte3;
	UINT32 vps_byte2;
	UINT32 vps_byte1;
	UINT32 vps_byte0;
	UINT32 vps_value[4];
	UINT32 vps_data[9] = {0};
	UINT32 vps;
#endif
#ifdef WSS_test	
	UINT8  wss_byte0 = 0, wss_byte1 = 0;
#endif
	UINT8  vbi_ttx[VBI_TTX_DMA_LENGTH][VBI_TTX_DMA_WIDTH]={0};
	UINT8 valid_data = FALSE;

	vbi_delay(1000);
	vbi_delay(1000);
	vbi_delay(1000);
	printk("TT_VBI_Control_Register[3_4a00]: %x, TT_VBI_LOOP_FILTER_I_GAIN_REGISTER[3_4a1c]: %x\n",rtd_inl(VBI_TT_VBI_CONTROL_REGISTER_VADDR),rtd_inl(VBI_TT_VBI_LOOP_FILTER_I_GAIN_REGISTER_VADDR));
	printk("TT_VBI_CO_CH_CTRL[3_4a6c]: %x\n",rtd_inl(VBI_TT_VBI_CO_CH_CTRL_VADDR));
	printk("#########TT  START \n" );

	rtd_maskl(VBI_VBI_DEBUG_MODE_VADDR, ~_BIT12, _BIT12);
	UINT8 ucCoCh = (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7);
	printk("=== coch flag = %x\n",ucCoCh );

#ifdef TT_test

	while(i<100)
	{
		i++;
		vbi_delay(100);
		if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT19)==_BIT19) // tt ready
		{ // TT ready
			printk("#########TT READY  = %d\n",i );
			break;	// jj test
		}
		rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT19, _BIT19);	//clr TT ready bit
		if(ucCoCh != (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7))
		{
			ucCoCh = (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7);
			printk("=== coch flag changed !!!! = %x\n",ucCoCh );
		}
	}

	i = 0;
	////////////////for pacific' 216 pin,remember to change to "Normal ram boot " of the menuconfig 
	///////////////////////////////////////////////////////////////////////////////////
	while(i<68000)
	{
		i++;
		vbi_delay(100);
		if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT19)==_BIT19) // tt ready
		{
			//printk("#########TT  READY \n" );
			if ((rtd_inl(VBI_VBI_DEBUG_MODE_VADDR)&_BIT12)==_BIT12) //tt_data_err bit
			{
				printk("     TT Data Error ,i=%d\n",i);
				rtd_maskl(VBI_VBI_DEBUG_MODE_VADDR, ~_BIT12, _BIT12);
				if (j>5)
				{
					tt_detect = _FAIL;
					break;
				}
				j++;
			}
			rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT19, _BIT19);
		}
		if(ucCoCh != (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7))
		{
			ucCoCh = (rtd_inl(VDC_VBI_CO_CH_CTRL0_VADDR)&_BIT7);
			printk("=== coch flag changed !!!! = %x\n",ucCoCh );
		}
		if((i & 0x0000007f) == 0x00000000)
		{
			printk(".");
		}
	}
	if(tt_detect)
		printk("\n\n######### TT verify FAIL ~~\n");
	else
		printk("\n\n######### TT verify PASS !!\n");
	printk("noisy_status = %x\n\n",rtd_inl(VDC_NOISE_STATUS_VADDR));
	printk("@@@@@@@@@ TT  END \n" );
#endif

#ifdef TT_DMA_test
	i = 0;
	m = 0;
	tt_detect = _SUCCESS;
	vbi_delay(10000);

	printk("#########TT  DMA  START \n" );
	//for TT1033 pattern 2 , line 7~ line 18 (12 line)
	//for TT1033 pattern 2 , line 7~ line 18 (12 line)
	//for TT1033 pattern 2 , line 7~ line 18 (12 line)	

	rtd_maskl(VBI_VBI_DUMP_INT_VADDR, ~_BIT0, _BIT0);	// enable VBI sends a field data to DMA  interrupt

//	while(i<15000)
	while(i<30000)
	{
		i++;
		udelay(1000);
		if((rtd_inl(VBI_VBI_DUMP_INT_VADDR)&_BIT0)==_BIT0) // vbi_dump_irq = 1
		{		
		       //printk("#########TT  DMA  IRQ  \n" );
						// DMA FIFO overflow
			if ( rtd_inl(VBI_VBI_DMA_CTRL_VADDR) & (_BIT3) )
			{
				printk( "VBI TTX DMA FIFO Overflow\n");
				rtd_maskl(VBI_VBI_DMA_CTRL_VADDR,~_BIT3,_BIT3);// clear out FIFO Overflow
			}

			if (vbi_ttx_dma != NULL ) 
			{

				for ( j=0 ; j<VBI_TTX_DMA_LENGTH ; ++j)
				{ 
					for (k=0; k<48;k++)
						vbi_ttx[j][k]= (*vbi_ttx_dma)[j][k];
					
					if (	(vbi_ttx[j][0]==0x00) &&//symtomy randomly add
						(vbi_ttx[j][1]==0x00) &&//symtomy randomly add
						(vbi_ttx[j][2]==0xFF) &&//symtomy randomly add
						(vbi_ttx[j][3]==0xFF) &&//symtomy randomly add
						((vbi_ttx[j][4]==0x22) || (vbi_ttx[j][4]==0x23)) &&//even or odd
						(vbi_ttx[j][5]==0x2A)) //TT
					{
						valid_data = FALSE;
						printk(" line = %d ", (j+6));

						if ((vbi_ttx[j][6]==0xc7)||(vbi_ttx[j][6]==0x02))//Magazine Number
						{
							for (k=0;k<12;k++)
							{
								if (vbi_ttx[j][7] == tt_dma_data[k])
								{//Packet Number
									valid_data = TRUE;
									break;
								}
							}
						}

						if ((valid_data == TRUE)&&(j<12))//line data compare, except line 18
						{
							for (k=8;k<48;k++)
							{
								//printk("%z ",(*vbi_ttx_dma)[j][k]);
								if ((vbi_ttx[j][k]== 0x7f)||(vbi_ttx[j][k] == 0xfe))
								{
									valid_data = TRUE;
								}
								else
								{
									valid_data = FALSE;
									break;
								}
							}
						}
						
						if (valid_data == TRUE)
						{
							if (j<12)//line data compare, except line 18
								printk("  TT DMA OK  \n");
							else
								printk(" \n");
						}
						else
						{
							tt_detect = _FAIL;
							printk(" ####################TT DMA FAIL ################## \n");
							break;
						}
					}
				}
			}
			rtd_maskl(VBI_VBI_DUMP_INT_VADDR, ~_BIT0, _BIT0);
		}
	}

	if(tt_detect)
		printk("\n\n######### TT DMA test FAIL !!\n\n");
	else
		printk("\n\n######### TT DMA test PASS !!\n\n");
	printk("@@@@@@@@@TT DMA  END \n" );
#endif

#ifdef WSS_test	
	printk("#########WSS START \n" );
	i = 0;
	m = 0;
	j=0;
	while(i<1800000)
	{
		i++;
		udelay(1000);
		if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT18)==_BIT18) // Bit18 = 1
		{
			//if ((m == 0)&&((rtd_inl(0xb8003240)&_BIT12)==_BIT12)&&((rtd_inl(0xb8003290)&_BIT12)==_BIT12))
			   	//printk(" WSS  M&AV CPU IRQ OK!!!\n");

		       //printk("#########WSS READY \n" );
			wss_byte1 = (rtd_inl(VBI_TT_VBI_CCWSS_DATA_VADDR)&0x00ff0000)>>16;
			wss_byte0 = (rtd_inl(VBI_TT_VBI_CCWSS_DATA_VADDR)&0xff000000)>>24;
			if (m == 0)
			{
				wss_init_value = (wss_byte1<<8)|wss_byte0 ;
				printk(" WSS Init Data ===> %x\n", wss_init_value);
			}
			else
			{
				wss_value = (wss_byte1<<8)|wss_byte0 ;
				if (wss_value != wss_init_value)
				{
					j++;
					printk("i=%d WSS Data ===> %x\n",i, wss_value );
					if (j>5)
						break;
				}
			}
			rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT18, _BIT18);
			m++;
		}
	}
	printk("@@@@@@@@@WSS END \n" );
#endif

#ifdef VPS_test
	printk("#########VPS START \n" );
	i = 0;
	m = 0;
	j =0;
	while(i<1800000)
	{
		i++;
		udelay(1000);
		if((rtd_inl(VBI_TT_VBI_DATA_STATUS_VADDR)&_BIT16)==_BIT16) // Bit16 = 1
		{
			//if ((m == 0)&&((rtd_inl(0xb8003240)&_BIT12)==_BIT12)&&((rtd_inl(0xb8003290)&_BIT12)==_BIT12))
			   	//printk(" VPS  M&AV CPU IRQ OK!!!\n");
			
		       //printk("#########VPS READY\n" );
			vps_byte3 = rtd_inl(VBI_TT_VPS_DATA3_VADDR);
			vps_byte2 = rtd_inl(VBI_TT_VPS_DATA2_VADDR);
			vps_byte1 = rtd_inl(VBI_TT_VPS_DATA1_VADDR);
			vps_byte0 = rtd_inl(VBI_TT_VPS_DATA0_VADDR);

			if (m == 0)
			{
				vps_value[3] = vps_byte3;
				vps_value[2] = vps_byte2;
				vps_value[1] = vps_byte1;
				vps_value[0] = vps_byte0;
				printk(" vps_init_value[3]  ===> %x \n", vps_value[3] );
				printk(" vps_init_value[2]  ===> %x \n", vps_value[2] );
				printk(" vps_init_value[1]  ===> %x \n", vps_value[1] );
				printk(" vps_init_value[0]  ===> %x \n", vps_value[0] );
				
				vps_data[2] = (vps_byte2&_BIT26) >>26;
				vps_data[3] = (vps_byte2&_BIT27) >>27;
				vps_data[4] = (vps_byte2&_BIT28) >>28;
				vps_data[5] = (vps_byte2&_BIT29) >>29;
				vps_data[6] = (vps_byte2&_BIT30) >>30;
				vps = (vps_data[2] << 4)+(vps_data[3] << 3)+(vps_data[4] << 2)+(vps_data[5] << 1)+vps_data[6] ;
				printk(" day      ===> %d \n", vps );

				vps_data[7] = (vps_byte2&_BIT31) >>31;
				vps_data[0] = (vps_byte2&_BIT16) >>16;
				vps_data[1] = (vps_byte2&_BIT17) >>17;
				vps_data[2] = (vps_byte2&_BIT18) >>18;
				vps =(vps_data[7] << 3)+(vps_data[0] << 2)+(vps_data[1] << 1)+vps_data[2] ;
				printk(" month  ===> %d \n", vps );

				vps_data[3] = (vps_byte2&_BIT19) >>19;
				vps_data[4] = (vps_byte2&_BIT20) >>20;
				vps_data[5] = (vps_byte2&_BIT21) >>21;
				vps_data[6] = (vps_byte2&_BIT22) >>22;
				vps_data[7] = (vps_byte2&_BIT23) >>23;
				vps = (vps_data[3] << 4)+(vps_data[4] << 3)+(vps_data[5] << 2)+(vps_data[6] << 1)+vps_data[7] ;
				printk(" hour     ===> %d \n", vps );

				vps_data[0] = (vps_byte2&_BIT8) >>8;
				vps_data[1] = (vps_byte2&_BIT9) >>9;
				vps_data[2] = (vps_byte2&_BIT10) >>10;
				vps_data[3] = (vps_byte2&_BIT11) >>11;
				vps_data[4] = (vps_byte2&_BIT12) >>12;
				vps_data[5] = (vps_byte2&_BIT13) >>13;
				vps = (vps_data[0] << 5)+(vps_data[1] << 4)+(vps_data[2] << 3)+(vps_data[3] << 2)+(vps_data[4] << 1)+vps_data[5] ;
				printk(" min      ===> %d \n", vps );

				vps_data[0] = (vps_byte0&_BIT12) >>12;
				vps_data[1] = (vps_byte0&_BIT13) >>13;
				vps_data[2] = (vps_byte0&_BIT14) >>14;
				vps_data[3] = (vps_byte0&_BIT15) >>15;
				vps_data[4] = (vps_byte2&_BIT14) >>14;
				vps_data[5] = (vps_byte2&_BIT15) >>15;
				vps_data[6] = (vps_byte2&_BIT0) ;
				vps_data[7] = (vps_byte2&_BIT1) >>1;
				vps =(vps_data[0] << 7)+(vps_data[1] << 6)+(vps_data[2] << 5)+(vps_data[3] << 4)+(vps_data[4] << 3)+(vps_data[5] << 2)+(vps_data[6] << 1)+vps_data[7] ;
				printk(" country ===> %d \n", vps );

				vps_data[0] = (vps_byte2&_BIT24) >>24;
				vps_data[1] = (vps_byte2&_BIT25) >>25;
				vps_data[2] = (vps_byte2&_BIT2) >>2;
				vps_data[3] = (vps_byte2&_BIT3) >>3;
				vps_data[4] = (vps_byte2&_BIT4) >>4;
				vps_data[5] = (vps_byte2&_BIT5) >>5;
				vps_data[6] = (vps_byte2&_BIT6) >>6;
				vps_data[7] = (vps_byte2&_BIT7) >>7;
				vps =(vps_data[0] << 7)+(vps_data[1] << 6)+(vps_data[2] << 5)+(vps_data[3] << 4)+(vps_data[4] << 3)+(vps_data[5] << 2)+(vps_data[6] << 1)+vps_data[7] ;
				printk(" net       ===> %d \n", vps );	

				vps_data[0] = (vps_byte3&_BIT0);
				vps_data[1] = (vps_byte3&_BIT1) >>1;
				vps_data[2] = (vps_byte3&_BIT2) >>2;
				vps_data[3] = (vps_byte3&_BIT3) >>3;
				vps_data[4] = (vps_byte3&_BIT4) >>4;
				vps_data[5] = (vps_byte3&_BIT5) >>5;
				vps_data[6] = (vps_byte3&_BIT6) >>6;
				vps_data[7] = (vps_byte3&_BIT7) >>7;
				vps =(vps_data[0] << 7)+(vps_data[1] << 6)+(vps_data[2] << 5)+(vps_data[3] << 4)+(vps_data[4] << 3)+(vps_data[5] << 2)+(vps_data[6] << 1)+vps_data[7] ;
				printk(" PTY      ===> %d \n", vps );
			}
			else
			{
				if( (vps_value[3] != vps_byte3)||(vps_value[2] != vps_byte2)||(vps_value[1] != vps_byte1)||(vps_value[0] != vps_byte0))
				{
					j++;
					printk(" vps_value[3]  ===> %x \n", vps_byte3 );
					printk(" vps_value[2]  ===> %x \n", vps_byte2 );
					printk(" vps_value[1]  ===> %x \n", vps_byte1 );
					printk(" vps_value[0]  ===> %x \n", vps_byte0 );
					if (j>5)
						break;
				}
			}
			m++;
			rtd_maskl(VBI_TT_VBI_DATA_STATUS_VADDR, ~_BIT16, _BIT16);
		}
	}
	printk("@@@@@@@@@VPS END \n" );
#endif
	return _FAIL;
}

#ifdef TT_DMA_test
void DMA_Init(void)
{
	vbi_ttx_dma  = (UINT8 (*)[][VBI_TTX_DMA_WIDTH])((UINT32)vbi_ttx_dma_org|MEM_OFFSET);

	rtd_outl(VBI_TT_VBI_DUMP_DATA1_VADDR, 0x11ffffff);
	//rtd_outl(VBI_TT_VBI_DUMP_DATA1_VADDR, 0x01ffffff);//when VBI_TTX_DMA_WIDTH=48
	// Vbi_dump_line_num  Bit0 --> dump dma-v-counter line 6
	// Vbi_dump_line_num  Bit1 --> dump dma-v-counter line 7
	// Vbi_dump_line_num  Bit23 --> dump dma-v-counter line 29
	// Bit24  Vbi_dump_ttdata_en
	// BIT28 Vbi_dump_rowdata_en
	// need enough byte number that dump can dump, so bit24&bit28 both enable

	//rtd_outl(VBI_TT_VBI_DUMP_DATA2_VADDR, 0x01002023);	// dump field select => 1  dump 1 field (dump per field)
	rtd_outl(VBI_TT_VBI_DUMP_DATA2_VADDR, 0x0100204d);	// dump field select => 1  dump 1 field (dump per field)
	//rtd_outl(VBI_TT_VBI_DUMP_DATA2_VADDR, 0x0000204d);	// dump field select => 0  dump 2  field (dump per 2  field),VBI_TTX_DMA_LENGTH_ALIGN&VBI_TTX_DMA_LENGTH need to change	
	rtd_outl(VBI_VBI_DMA_FRAME_ADDR_VADDR, ((UINT32)(&(*vbi_ttx_dma)[0][0]))>>3);	// start addr
	rtd_outl(VBI_VBI_DMA_FRAME_ADDR_END_VADDR, ((UINT32)(&(*vbi_ttx_dma)[VBI_TTX_DMA_LENGTH_ALIGN][0]))>>3); // end addr, 64*24 bytes
	rtd_outl(VBI_VBI_DMA_VACTIVE1_VADDR, 0x0006001A);	// line 6~26 for field 1
	rtd_outl(VBI_VBI_DMA_VACTIVE2_VADDR, 0x013F0153);	// line 6~26 for field 2 (+313)
	rtd_outl(VBI_VBI_DMA_FIFO_STAUS_VADDR, 0x00203f05);	// DMA FIFO for LV,LV2,Pacific,Darwin
	//rtd_outl(VBI_VBI_DMA_FIFO_STAUS_VADDR, 0x00101f05);	// DMA FIFO for Atlantic
	rtd_outl(VBI_VBI_DUMP_INT_VADDR, 0x00000002);		// DMA IRQ Enable
	rtd_outl(VBI_VBI_DMA_CTRL_VADDR, 0x00000000);		// enable DMA
	printk("[Slicer] DMA_Init done !!\n");
}
#endif

#endif

#ifdef CGMS_test
void CGMS_Init(void)
{
	//printk("#########CGMS_Init \n" );
////	rtd_outl(0xB8000204, 0x00020021); // vbi clk from YPP (bit5 = 1)
	rtd_outl(0xB8020080, 0x00000274); // bit[2]=1: vbi_clk use adc_clk2x (VBI_clk = 27MHz)

#ifdef AV_Input
	rtd_outl(0xb8000018,0x00020001);	// bit 5, VBI source, 0: Video Decoder,1: YPBPR
	rtd_outl(VBI_VBISL0_VADDR, 0x90000000);  // bit7=0  from  VD

	printk("[Slicer] AV CGMS_Init \n");
	rtd_outl(VBI_VBI_VOUNT_SHIFT_VADDR, 0x0);
	rtd_outl(VBI_CGMS_C0_VADDR, 0x07006413);  // for interlace
	rtd_outl(VBI_CGMS_C1_VADDR, 0x000E0115);  // active line  14
	//rtd_outl(VBI_CGMS_C2_VADDR, 0x00300130); // 480i do not

	rtd_outl(VBI_CGMS_C5_VADDR, 0x0038403c);  // for  480i

	rtd_outl(VBI_CGMS_C3_VADDR, 0x0100001e);  // bit 24  auto  period
	rtd_outl(VBI_CGMS_C4_VADDR, 0x10000000);  //remember enable cgms interrupt(bit28 ->cgms)
#endif

#ifdef YPP_Input
	rtd_outl(0xb8000018,0x00020021);	// bit 5, VBI source, 0: Video Decoder,1: YPBPR
	printk("[Slicer][0] YPP set:%x \n",rtd_inl(VBI_VBISL0_VADDR));
	rtd_outl(VBI_VBISL0_VADDR, 0x90000080);	// bit7=1  from  Ypp
											// bit[5] Pacific  need inverse V/H Line counter
											// bit[4] Pacific  need inverse field
	printk("[Slicer][1] YPP set:%x \n",rtd_inl(VBI_VBISL0_VADDR));


#ifdef YPPin_480i
	printk("[Slicer] CGMS_Init 480i \n");
	rtd_outl(VBI_VBI_VOUNT_SHIFT_VADDR, 0x0);
	rtd_outl(VBI_CGMS_C0_VADDR, 0x07006413);  // for interlace
	rtd_outl(VBI_CGMS_C1_VADDR, 0x000E0115);  // active line  14
	//rtd_outl(VBI_CGMS_C2_VADDR, 0x00300130); // 480i do not

	rtd_outl(VBI_CGMS_C5_VADDR, 0x0038403c);  // for  480i

	rtd_outl(VBI_CGMS_C3_VADDR, 0x0100001e);  // bit 24  auto  period
	rtd_outl(VBI_CGMS_C4_VADDR, 0x10000000);  //remember enable cgms interrupt(bit28 ->cgms)
#endif 

#ifdef YPPin_480p
	printk("[Slicer] CGMS_Init 480p \n");
	rtd_outl(VBI_VBI_VOUNT_SHIFT_VADDR, 0x0);
	rtd_outl(VBI_CGMS_C0_VADDR, 0x07006417);  // for progressive
	rtd_outl(VBI_CGMS_C1_VADDR, 0x001E001E);  // active line  30
	rtd_outl(VBI_CGMS_C2_VADDR, 0x00300130);   // 480p must be

	rtd_outl(VBI_CGMS_C5_VADDR, 0x0010241a);  // for  480p

	rtd_outl(VBI_CGMS_C3_VADDR, 0x0100001e);  // bit 24  auto  period
	rtd_outl(VBI_CGMS_C4_VADDR, 0x10000000);  //remember enable cgms interrupt(bit28 ->cgms)
#endif

#ifdef YPPin_720p
	printk("[Slicer] CGMS_Init 720p \n");
	rtd_outl(VBI_VBI_VOUNT_SHIFT_VADDR, 0x0);
	rtd_outl(VBI_CGMS_C0_VADDR, 0x07006417);  // for progressive
	rtd_outl(VBI_CGMS_C1_VADDR, 0x00130013);  // active line  19
	//rtd_outl(VBI_CGMS_C2_VADDR, 0x00300130);   // 720p do not

	rtd_outl(VBI_CGMS_C5_VADDR, 0x0030443A);  // for  720p

	rtd_outl(VBI_CGMS_C3_VADDR, 0x0100001e);  // bit 24  auto  period
	rtd_outl(VBI_CGMS_C4_VADDR, 0x10000000);  //remember enable cgms interrupt(bit28 ->cgms)
#endif

#ifdef YPPin_1080i
	printk("[Slicer] CGMS_Init 1080i \n");
	rtd_outl(VBI_VBI_VOUNT_SHIFT_VADDR, 0x0);
	rtd_outl(VBI_CGMS_C0_VADDR, 0x07006413);  // for interlace
	rtd_outl(VBI_CGMS_C1_VADDR, 0x00100243);  // active line  16
	//rtd_outl(VBI_CGMS_C2_VADDR, 0x00300130);   // 1080i do not

	rtd_outl(VBI_CGMS_C5_VADDR, 0x0043574D); // for  1080i

	rtd_outl(VBI_CGMS_C3_VADDR, 0x0100001e);  // bit 24  auto  period
	rtd_outl(VBI_CGMS_C4_VADDR, 0x10000000);  //remember enable cgms interrupt(bit28 ->cgms)
#endif
#endif

	printk("[Slicer] CGMS_Init done !!\n");
}

UINT8 CGMS_verify(void)
{
	UINT32 i,j;
	UINT32 cgms_detect;
	cgms_detect = _FAIL;
	
	printk("#########CGMS START \n" );
	i = 0;
	j = 0;
	while(i<2400000)//2400000
	{
		i++;
		udelay(10);
		if((rtd_inl(VBI_CGMS_C4_VADDR)&_BIT24)==_BIT24) // cgms valid
		{
			if ((j == 0)&&((rtd_inl(0xb8003240)&_BIT12)==_BIT12)&&((rtd_inl(0xb8003290)&_BIT12)==_BIT12))
			   	printk("CGMS M&AV CPU IRQ OK!!!\n");
		    
			j++;   	
			rtd_maskl(VBI_CGMS_C4_VADDR, ~_BIT24, _BIT24);
			cgms_detect = rtd_inl(VBI_CGMS_C4_VADDR)&0x000fffff;
			printk("%x\n", cgms_detect );
		}
	}
	printk("@@@@@@@@@CGMS END \n" );
	return _FAIL;
}
#endif

