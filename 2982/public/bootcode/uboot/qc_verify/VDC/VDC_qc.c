//#include <rtd298x_qc_verify.h>
//#include <rtd298x_qc_verify_bga459.h>
#include <qc_verify.h>
//#include <qc_verify_common.h>	// default include
#ifndef _RTD_TYPES_H
#include <rtd_types.h>
#endif
#include "vdc_qc.h"
#include "rbusAdcReg.h"	
#include "rbusVDIFDinReg.h"
#include "rbusVDPQReg.h"
#include "rbusVDTopReg.h"

// 2013.02/21 Mark define for debug //
#define vd_show_message
/////////////////////////////////

#define _3D_One_Frame_Use	0x01b11a
#define _SDRAM_3D_COM_USE	0x1b11b0
#undef vd_show_message
#define CONFIG_MAC_ESD_ENABLE 1

/////////////////////////////////Mark Test//////////////////
#define CONFIG_QC_TEST

#define CONFIG_VD_1
//#define ADC_Path9
//#define ADC_Path10
//#define ADC_Path11
#define ADC_Path12
//#define ADC_Path13
//#define ADC_Path14

#define CONFIG_VD_2
#define CONFIG_VD_3
#define CONFIG_VD_4
#define CONFIG_VD_5
#ifdef CONFIG_256_PKG
#define  CONFIG_VD_6
#endif
#define  CONFIG_VD_7
/////////////////////////////////Mark Test//////////////////
//jacky
#define sirius_qc 1
#define rework 1
#define Test_Y_Path 1
#define SetADCPath 1
#define open_debug_msg 0
#if open_debug_msg
#define dmsg printk
#else
#define dmsg
#endif

typedef enum cvbs_mode_s{
	NTSC_ = 0x0,
	PALI_
}cvbs_mode_t;

typedef enum crc_sel_s{
	QC_ = 0x0,
	MP_
}crc_sel_s_t;

typedef enum v0v1v2_sel_s{
	dc_v0 = 0x1,
	dc_v1 = 0x2,
	dc_v2 = 0x4,
	dc_v_all_enable = 0x7,
	dc_v_all_disble = 0x0
}v0v1v2_sel_t;

typedef enum updn_pos_sel_s{
	updn_pos_v0 = 0x1,
	updn_pos_v1 = 0x2,
	updn_pos_v2 = 0x4,
	updn_pos_v_all_enable = 0x7,
	updn_pos_v_all_disble = 0x0
} updn_pos_sel_t;

typedef enum updn_neg_sel_s{
	updn_neg_v0 = 0x1,
	updn_neg_v1 = 0x2,
	updn_neg_v2 = 0x4,
	updn_neg_v_all_enable = 0x7,
	updn_neg_v_all_disble = 0x0
} updn_neg_sel_t;

typedef enum Ypp_input_pin_s{
	VIN_4P = 0x1,
	VIN_7P = 0x2,
	VIN_8P = 0x3
};


// it used to measure the crc result in the loading script
// Then, make sure the color bar is right
unsigned int g_scart_ntsc_crc_qc = 0x20B27CA0;
unsigned int g_scart_pali_crc_qc = 0x96A0C785;
unsigned int g_scart_ntsc_crc_mp = 0x2140F8F7;
unsigned int g_scart_pali_crc_mp = 0x2140F8F7;

unsigned int g_sv_ntsc_crc_qc = 0x5D8A9DF0;
unsigned int g_sv_pali_crc_qc = 0xB7A96C8E;
unsigned int g_sv_ntsc_crc_mp = 0xBB731588;
unsigned int g_sv_pali_crc_mp = 0x3AE7E3C3;






#ifdef CONFIG_QC_TEST
#ifdef  CONFIG_VD_1
#define  Test_vdc_PathSelect
#endif

#ifdef  CONFIG_VD_2
#define  Test_vdc_Test_Memory
#endif

#ifdef  CONFIG_VD_3
#define  Test_vdc_Test_BIst
#endif

#ifdef  CONFIG_VD_4
#define  Test_vdc_Test_CRC

#endif

#ifdef 	CONFIG_VD_5
#define Test_vdc_Test_DRF_BIst
#endif

#ifdef 	CONFIG_VD_6
#define Test_vdc_Test_Scart_Fsw_Adc
#endif

#ifdef	CONFIG_VD_7
#define Test_vdc_Test_FIFO
#endif
#endif
#if 0
UINT32 cvbs_2d_pal1		=0x63977fa3;
UINT32  cvbs_2d_pal2	= 0x6bed0ec7;
UINT32 cvbs_3d_ntsc		=0x0cdc3534;
UINT32 cvbs_3d_pal		=0x38b61c79;

//	UINT32 cvbs_2d_ntsc_qc = 0x0205e2b1;	// original data
UINT32 cvbs_2d_ntsc_qc	= 0xc59b0c31;	// 2013.03/04 Mark test data
//	UINT32 cvbs_2d_pal_qc	= 0x797ebc45;	// original data
UINT32 cvbs_2d_pal_qc	= 0xf85f9f1e;	// 2013.03/04 Mark test data
//	UINT32 cvbs_2d_ntsc_mp = 0x3103dddb;	// original data
UINT32 cvbs_2d_ntsc_mp	= 0xf5a87a18;	// 2013.03/21 Mark test data
//	UINT32 cvbs_2d_pal_mp = 0x11100b4a;	// original data
UINT32 cvbs_2d_pal_mp	= 0xef7d6d8;		// 2013.03/21 Mark test data
//UINT32 Component_2d_ntsc	= 0x9653b19b;	// original data
UINT32 Component_2d_ntsc	= 0x5863dc7;	// 2013.03/04 Mark test data
//UINT32 Component_2d_pal	= 0x9653b19b;	// original data
UINT32 Component_2d_pal	= 0xdc91bb16;	// 2013.03/04 Mark test data
#else

UINT32 cvbs_2d_ntsc_qc	= 0xD64618EB;	//0xc59b0c31;	// 2013.03/04 Mark test data
UINT32 cvbs_2d_pal_qc	=0x3891CACB;      //0x77c80d08;	// 2013.03/04 Mark test data
UINT32 cvbs_2d_ntsc_mp	=  0x6DBA3F25;	//0xf5a87a18;	// 2013.03/21 Mark test data
UINT32 cvbs_2d_pal_mp	= 0x446CC6F7;	//0x0EF7D6D8;		// 2013.03/21 Mark test data


// no using
UINT32 cvbs_2d_pal1		=0x63977fa3;
UINT32  cvbs_2d_pal2	= 0x6bed0ec7;
UINT32 cvbs_3d_ntsc		=0x0cdc3534;
UINT32 cvbs_3d_pal		=0x38b61c79;
UINT32 Component_2d_ntsc	= 0x5863dc7;	// 2013.03/04 Mark test data
UINT32 Component_2d_pal	= 0xdc91bb16;	// 2013.03/04 Mark test data

#endif


int	MAC2_Version = 1;	
int	MAC2P_Version = 0;



UINT32 CRC_error_count;	

void module_vdc_Bring_Up_screen_scripts(void)
{
#if 1
rtd_outl(0xb8003620,0x00000108);		// set VDC 444 output					// FSW_CTRL2
rtd_outl(0xb8003418,0x00000091);		// if chroma unlock, chage cstate to chromalock_cstate		// CKILL_LB_SEL
rtd_outl(0xb8003764,0x0008017F);		// bit[9:8]=01, select Select the VCO freq = 540M			// MISC_CONTROL
#else
rtd_outl(0xb8019620,0x00000108);		// set VDC 444 output					// FSW_CTRL2
rtd_outl(0xb8019418,0x00000091);		// if chroma unlock, chage cstate to chromalock_cstate		// CKILL_LB_SEL
rtd_outl(0xb8019764,0x0008017F);		// bit[9:8]=01, select Select the VCO freq = 540M			// MISC_CONTROL
#endif
//#include "case13_CVBS_VIN9_fs_fhd/VDAC_VIN9P.tbl" 
//		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/vgip_ch1_vd.tbl"
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/m_ch1_frc_1080i10b444.tbl"
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/uzu_main_444_bypass480i.tbl"
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/DPLL_297MHz.tbl"
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/dtg_fhd_fs.tbl"
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/mtg_fhd.tbl"
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/ivs2dvs_480i_fhd.tbl"		
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/m_ch1_frc_to_fs.tbl"
		udelay(50);
#include "case13_CVBS_VIN9_fs_fhd/LVDS_FHD_1Seg_2Port.tbl"	
		udelay(50);




#if 0	// 2013.02/23 Mark: initialization part of CVBS_VIN_12P
///// VD power /////
		rtd_outl(0xb8020000,0x000000FF);		// ADC power on						// ADC_POWER
		rtd_outl(0xb802005C,0x00130003);		// VDADC power on						// VDADC_POW_CTL
///// CRT /////
		rtd_outl(0xb8000104,0xFB9F9DEF);		// reset VD clock						// SYS_SRST1
		rtd_outl(0xb8000104,0xFBFF9DEF);		// stop reset VD clock					// SYS_SRST1
		rtd_outl(0xb8000108,0xFFFFFFFF);		// Reset all system RS for UART			// SYS_SRST2
		rtd_outl(0xb8000114,0xFFFFFDFF);		// enable VD clock						// SYS_CLKEN1
		rtd_outl(0xb8000118,0x3FE4FFFF);		// enable ATV input control of VD			// SYS_CLKEN2
///// PLL27X /////
		rtd_outl(0xb8000204,0x00020001);		// [17] ATV in ck sel = 1: VD; [0] uart ck src = 1: 27MHz (XTAL)	// SYS_CLKSEL
		rtd_outl(0xb80004D0,0x02250012);	// SYS_PLL_27X1 (CRT.doc) [12] PLL27x_M_SEL = 0: programmable divider; [9:8] PLL27X_N = 00:1; [6:0] PLL27X_M = 0x12
		rtd_outl(0xb80004D4,0x00036631);	// SYS_PLL_27X2 (CRT.doc) [9:8] PLL27X_LDO_SEL = 10:1.76V; [5:4] PLL27X_PS_54M_DELAY = 11: use when VCO=540M; [0] PLL27X_PS_DUTY_SEL = 1: larger duty cycle
		rtd_outl(0xb80004D8,0x00000117);	// SYS_PLL_27X3 (CRT.doc) [17:8] PLL27X_ RESERVE = 1; [4] PLL27X_PS_EN = 1:enable; [2] PLL27X_VCORSTB; [1] PLL27X reset control = 1: normal; [0] PLL27X_POW = 1: power on
		rtd_outl(0xb80004DC,0x0000F501);	// SYS_PLL_27X4 (CRT.doc) [17:16] PLL27X_CK108M_DIV = 00: divide by 5 (use when VCO=540MHz); [15:14] PLL27X_YPPADC_CKO_SEL = 11:108M; [13] PLL27X_YPPADC_CKO_ENPLL27x = 1; [12] PLL27X_YPPADC_CK54M_EN = 1; [11:10] PLL27X_IFADC_CKO_SEL = 01:54M; [9] PLL27X_IFADC_DIV = 0: divide by 4 (use when VCO=648M or 540M or 432M to generate 162M, 135M and 108M); [0] CK_IFADC_MUX = 1:PLL27X
		#if sirius_qc //jacky
		rtd_outl(0xb8003764,0x0008017F);	// MISC_CONTROL (Video.doc) [9:8] Swallow_freq_sel = 1:540Mhz
		#else
		rtd_outl(0xb8019764,0x0008017F);	// MISC_CONTROL (Video.doc) [9:8] Swallow_freq_sel = 1:540Mhz
		#endif
		rtd_outl(0xb8018094,0x00000010);	// input_filter_set (IFD_input.doc) [5:4] adc_clk_sel = 1:108M
///// IFD /////	(setting decimation filter, from PacificPrime script, BW = 6.5MHz)
		rtd_outl(0xb80180D4,0x00000100);		// vd_fifo_clr = 1						// VD_INPUT_FIFO_STATUS1
		rtd_outl(0xb80180D4,0x00000000);		// vd_fifo_clr = 0						// VD_INPUT_FIFO_STATUS1
		rtd_outl(0xb8018000,0x00000030);		// tap1~4: 3,44,124,169 (0x03,0x2c,0x7c,0xa9)x16		// input_flt_tap_0_1
		rtd_outl(0xb8018004,0x02C007C0);		// tap1~4: 3,44,124,169 (0x030,0x2c0,0x7c0,0xa90)		// input_flt_tap_2_3
		rtd_outl(0xb8018008,0x0A901FDB);		// [12:0] = tap5						// input_flt_tap_4_5
		rtd_outl(0xb801800c,0x00120026);											// input_flt_tap_6_7
		rtd_outl(0xb8018010,0x00310022);											// input_flt_tap_8_9
		rtd_outl(0xb8018014,0x1FFA1FCF);											// input_flt_tap_10_11
		rtd_outl(0xb8018018,0x1FC21FE3);											// input_flt_tap_12_13
		rtd_outl(0xb801801C,0x0025005D);											// input_flt_tap_14_15
		rtd_outl(0xb8018020,0x005C0014);											// input_flt_tap_16_17
		rtd_outl(0xb8018024,0x1FA91F66);											// input_flt_tap_18_19
		rtd_outl(0xb8018028,0x1F890012);											// input_flt_tap_20_21
		rtd_outl(0xb801802C,0x00B400FA);											// input_flt_tap_22_23
		rtd_outl(0xb8018030,0x008F1F8C);											// input_flt_tap_24_25
		rtd_outl(0xb8018034,0x1E821E40);											// input_flt_tap_26_27
		rtd_outl(0xb8018038,0x1F6101E1);											// input_flt_tap_28_29
		rtd_outl(0xb801803C,0x050607A2);											// input_flt_tap_30_31
		rtd_outl(0xb8018040,0x08A50000);											// input_flt_tap_32_33
		rtd_outl(0xb80180A4,0x00000000);		// disable sv_yc_switch					// VD_IN_DELAY_SEL2
		rtd_outl(0xb80180AC,0x00000030);		// decimation filter [6:4] BW [0] 0: data from DF; 1: direct from ADC	// VD_INOUT_CTRL
		rtd_outl(0xb80008b0,0xCCCC000F);		// 0_08b0 make sure 10P, 11P, 13P, 14P are used as vd input (ADC_CFG PinMux.doc)
		rtd_outl(0xb80008b4,0xDD000003);		// 0_08b4 make sure SCART_FSW0, FSW1 are used as vd input (SCART_FSW_CFG PinMux.doc)
		udelay(50);

///// VD /////
		#if sirius_qc //jacky
		rtd_outl(0xb8003004,0x00000000);		// set AV							// VIDEO_CONTROL1
		rtd_outl(0xb8003080,0x00000000);		// decimation filter has been changed				// INOUT_CTRL
		rtd_outl(0xb800309C,0x00000047);		// set bgate_raw_sel enable					// VIDEO_CONTROL2
		rtd_outl(0xb8003608,0x000000C9);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_outl(0xb800360C,0x00000000);		// set Y							// CLAMP_UPDN_EN
		rtd_outl(0xb8003610,0x000000FF);		// enable AD1~AD4 clamp up/dn				// CLAMP_RGB_UPDN_EN
		rtd_outl(0xb8003620,0x00000108);		// set VDC 444 output					// FSW_CTRL2
		rtd_outl(0xb8003764,0x0008017F);		// bit[9:8]=01, select Select the VCO freq = 540M			// MISC_CONTROL
//		rtd_outl(0xb8003794,0x00000000);		// disable pattern generator					// PATTERN_CONTROL
		rtd_outl(0xb80037FC,0x00000000);		// Disable clamp test mode					// ADC_UPDN_CTRL
		#else
		rtd_outl(0xb8019004,0x00000000);		// set AV							// VIDEO_CONTROL1
		rtd_outl(0xb8019080,0x00000000);		// decimation filter has been changed				// INOUT_CTRL
		rtd_outl(0xb801909C,0x00000047);		// set bgate_raw_sel enable					// VIDEO_CONTROL2
		rtd_outl(0xb8019608,0x000000C9);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_outl(0xb801960C,0x00000000);		// set Y							// CLAMP_UPDN_EN
		rtd_outl(0xb8019610,0x000000FF);		// enable AD1~AD4 clamp up/dn				// CLAMP_RGB_UPDN_EN
		rtd_outl(0xb8019620,0x00000108);		// set VDC 444 output					// FSW_CTRL2
		rtd_outl(0xb8019764,0x0008017F);		// bit[9:8]=01, select Select the VCO freq = 540M			// MISC_CONTROL
//		20130516 Mark: keep the pattern gen for CRC fail debug
//		rtd_outl(0xb8019794,0x00000000);		// disable pattern generator					// PATTERN_CONTROL
		rtd_outl(0xb80197FC,0x00000000);		// Disable clamp test mode					// ADC_UPDN_CTRL
		#endif
#endif
}

void module_vdc_Print_Initial_Registers(void)
{
	printk("==== initial settings ====\n");
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000100,rtd_inl(0xb8000100));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000104,rtd_inl(0xb8000104));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000108,rtd_inl(0xb8000108));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb800010c,rtd_inl(0xb800010c));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000110,rtd_inl(0xb8000110));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000114,rtd_inl(0xb8000114));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000118,rtd_inl(0xb8000118));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb800011c,rtd_inl(0xb800011c));	//

	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000200,rtd_inl(0xb8000200));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000204,rtd_inl(0xb8000204));	//

	printk("rtd_outl(0x%x, 0x%08x);\n",0xB8000310,rtd_inl(0xB8000310));	//

	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000400,rtd_inl(0xb8000400));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000404,rtd_inl(0xb8000404));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb800040c,rtd_inl(0xb800040c));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000410,rtd_inl(0xb8000410));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000414,rtd_inl(0xb8000414));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000420,rtd_inl(0xb8000420));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000424,rtd_inl(0xb8000424));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000428,rtd_inl(0xb8000428));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000430,rtd_inl(0xb8000430));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000434,rtd_inl(0xb8000434));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000438,rtd_inl(0xb8000438));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000450,rtd_inl(0xb8000450));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000454,rtd_inl(0xb8000454));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000458,rtd_inl(0xb8000458));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb800045c,rtd_inl(0xb800045c));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000464,rtd_inl(0xb8000464));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000478,rtd_inl(0xb8000478));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb800047c,rtd_inl(0xb800047c));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000490,rtd_inl(0xb8000490));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000494,rtd_inl(0xb8000494));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000498,rtd_inl(0xb8000498));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb800049c,rtd_inl(0xb800049c));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004b4,rtd_inl(0xb80004b4));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004c0,rtd_inl(0xb80004c0));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004c4,rtd_inl(0xb80004c4));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004c8,rtd_inl(0xb80004c8));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004d0,rtd_inl(0xb80004d0));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004d4,rtd_inl(0xb80004d4));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004d8,rtd_inl(0xb80004d8));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004dc,rtd_inl(0xb80004dc));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb80004e4,rtd_inl(0xb80004e4));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000500,rtd_inl(0xb8000500));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000504,rtd_inl(0xb8000504));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000508,rtd_inl(0xb8000508));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb800050c,rtd_inl(0xb800050c));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000514,rtd_inl(0xb8000514));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000518,rtd_inl(0xb8000518));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000854,rtd_inl(0xb8000854));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8000910,rtd_inl(0xb8000910));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb801a808,rtd_inl(0xb801a808));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8060030,rtd_inl(0xb8060030));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8060040,rtd_inl(0xb8060040));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8060044,rtd_inl(0xb8060044));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8060050,rtd_inl(0xb8060050));	//

	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020000,rtd_inl(0xb8020000));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020004,rtd_inl(0xb8020004));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb802000c,rtd_inl(0xb802000c));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020010,rtd_inl(0xb8020010));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020014,rtd_inl(0xb8020014));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020020,rtd_inl(0xb8020020));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020024,rtd_inl(0xb8020024));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020028,rtd_inl(0xb8020028));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020030,rtd_inl(0xb8020030));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020034,rtd_inl(0xb8020034));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020038,rtd_inl(0xb8020038));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020050,rtd_inl(0xb8020050));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020054,rtd_inl(0xb8020054));	// 
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb8020058,rtd_inl(0xb8020058));	//
	printk("rtd_outl(0x%x, 0x%08x);\n",0xb802005c,rtd_inl(0xb802005c));	// 
}

void module_vdc_Print_Registers(unsigned char Y_path, unsigned char Y_Gnd_path, int delay_time)
{
	printk("==== VIN_P = %d ==== VIN_P = %d ====\n", Y_path, Y_Gnd_path);
	printk("==== VD settings ====\n");
	printk("%x = %08X\n", FEin_VD_IN_DELAY_SEL2_VADDR, rtd_inl(FEin_VD_IN_DELAY_SEL2_VADDR));	// 1_80a4
	printk("%x = %08X\n",0xb80180ac, rtd_inl(0xb80180ac));	// 1_80ac
	#if sirius_qc //jacky
	printk("%x = %08X\n",0xb8003004, rtd_inl(0xb8003004));	// 0_3004
	printk("%x = %08X\n",0xb8003008, rtd_inl(0xb8003008));	// 0_3008
	printk("%x = %08X\n",0xb8003080, rtd_inl(0xb8003080));	// 0_3080
	printk("%x = %08X\n",0xb800309c, rtd_inl(0xb800309c));	// 0_309c
	#else
	printk("%x = %08X\n",0xb8019004, rtd_inl(0xb8019004));	// 1_9004
	printk("%x = %08X\n",0xb8019008, rtd_inl(0xb8019008));	// 1_9008
	printk("%x = %08X\n",0xb8019080, rtd_inl(0xb8019080));	// 1_9080
	printk("%x = %08X\n",0xb801909c, rtd_inl(0xb801909c));	// 1_909c
	#endif
	printk("%x = %08X\n", VDC_AD_SW_CTRL0_VADDR, rtd_inl(VDC_AD_SW_CTRL0_VADDR));	// 1_9608
	printk("%x = %08X\n", VDC_CLAMP_UPDN_EN_VADDR, rtd_inl(VDC_CLAMP_UPDN_EN_VADDR));	// 1_960c
	printk("%x = %08X\n", VDC_CLAMP_RGB_UPDN_EN_VADDR, rtd_inl(VDC_CLAMP_RGB_UPDN_EN_VADDR));	// 1_9610
	#if sirius_qc //jacky
	printk("%x = %08X\n",0xb8003620, rtd_inl(0xb8003620));	// 1_9620
	printk("%x = %08X\n",0xb8003764, rtd_inl(0xb8003764));	// 1_9764
	printk("%x = %08X\n",0xb8003794, rtd_inl(0xb8003794));	// 1_9794
	printk("%x = %08X\n",0xb80037FC, rtd_inl(0xb80037FC));	// 1_97fc
	#else
	printk("%x = %08X\n",0xb8019620, rtd_inl(0xb8019620));	// 1_9620
	printk("%x = %08X\n",0xb8019764, rtd_inl(0xb8019764));	// 1_9764
	printk("%x = %08X\n",0xb8019794, rtd_inl(0xb8019794));	// 1_9794
	printk("%x = %08X\n",0xb80197FC, rtd_inl(0xb80197FC));	// 1_97fc
	#endif
	printk("==== ADC settings ====\n");
//	2013.02/27 Mark: debug for VIN0P~VIN8P
	printk("%x = %08X\n", ADC_ADC_POWER_VADDR, rtd_inl(ADC_ADC_POWER_VADDR));	// 2_0000
	printk("%x = %08X\n", ADC_ADC_IBIAS0123_VADDR, rtd_inl(ADC_ADC_IBIAS0123_VADDR));	// 2_0004
	printk("==== VIN0P~VIN8P ====\n");
	printk("%x = %08X\n", ADC_ADC_CTL_RGB12_VADDR, rtd_inl(ADC_ADC_CTL_RGB12_VADDR));	// 2_0008
	printk("%x = %08X\n", ADC_ADC_VBIAS_VADDR, rtd_inl(ADC_ADC_VBIAS_VADDR));	// 2_000c
	printk("%x = %08X\n", ADC_ADC_CLOCK_VADDR, rtd_inl(ADC_ADC_CLOCK_VADDR));	// 2_00010
	printk("%x = %08X\n", ADC_ADC_DCRESTORE_CTRL_VADDR, rtd_inl(ADC_ADC_DCRESTORE_CTRL_VADDR));	// 2_0018
	printk("%x = %08X\n", ADC_ADC_CLAMP_CTRL0_VADDR, rtd_inl(ADC_ADC_CLAMP_CTRL0_VADDR));	// 2_0001c
	printk("%x = %08X\n", ADC_ADC_CLAMP_CTRL1_VADDR, rtd_inl(ADC_ADC_CLAMP_CTRL1_VADDR));	// 2_0020
	printk("%x = %08X\n", ADC_ADC_CLAMP_CTRL2_VADDR, rtd_inl(ADC_ADC_CLAMP_CTRL2_VADDR));	// 2_0024
	printk("%x = %08X\n", ADC_ADC_CLAMP_CTRL3_VADDR, rtd_inl(ADC_ADC_CLAMP_CTRL3_VADDR));	// 2_0028
//	2013.02/27 Mark: debug for VIN9P~VIN14P	
	printk("==== VIN9P~VIN14P ====\n");
	printk("%x = %08X\n", ADC_VD_ADC_CLAMP_CTL_1_VADDR, rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR));	// 2_0048
	printk("%x = %08X\n", ADC_VD_ADC_CLAMP_CTL_2_VADDR, rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR));	// 2_004c
	printk("%x = %08X\n", ADC_VD_ADC_UPDN_CTL_VADDR, rtd_inl(ADC_VD_ADC_UPDN_CTL_VADDR));	// 2_0050
	printk("%x = %08X\n", ADC_VDADC_CORE_LPF_CTRL_VADDR, rtd_inl(ADC_VDADC_CORE_LPF_CTRL_VADDR));	// 2_0054
	printk("%x = %08X\n", ADC_VDADC_CK_CTL_VADDR, rtd_inl(ADC_VDADC_CK_CTL_VADDR));	// 2_0058
	printk("%x = %08X\n", ADC_VDADC_POW_CTL_VADDR, rtd_inl(ADC_VDADC_POW_CTL_VADDR));	// 2_005c
	printk("==== VIN_P = %d ==== VIN_P = %d ====\n", Y_path, Y_Gnd_path);
	udelay(delay_time);	// time for display
}

void module_vdc_Print_ADC_Value(int display_time)
{
	int i;
	for(i = 0; i < display_time; i++)
	{
		printk("[VDC][VD ADC value]	%x = %08X\n",0xb802008c,rtd_inl(0xb802008c));	// 2_008c
	}
#if 0
	printk("[VDC][CRT1]	%x = %08X\n",0xb80004d0,rtd_inl(0xb80004d0));	// 0_04d0
	printk("[VDC][CRT1]	%x = %08X\n",0xb80004d4,rtd_inl(0xb80004d4));	// 0_04d4
	printk("[VDC][CRT1]	%x = %08X\n",0xb80004d8,rtd_inl(0xb80004d8));	// 0_04d8
	printk("[VDC][CRT1]	%x = %08X\n",0xb80004dc,rtd_inl(0xb80004dc));	// 0_04dc
#endif
}

void drvif_module_vdc_ifd_input_path(void)
{
#if 1
	/////IFD_TOP////
	rtd_outl(0xb8033080,0x00100001);	// for PLL27X 2.5V LDO, MBias&Global power should enable
	rtd_outl(0xb80330ac,0x00000152);	// for PLL27X 2.5V LDO, IFD ADC_LDO power
	
	
	///// IFD ///// (setting decimation filter, from PacificPrime script, BW = 6.5MHz)
	rtd_outl(0xb80040D4,0x00000100);		// vd_fifo_clr = 1						// VD_INPUT_FIFO_STATUS1
	rtd_outl(0xb80040D4,0x00000000);		// vd_fifo_clr = 0						// VD_INPUT_FIFO_STATUS1
	
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
	
	
	rtd_outl(0xb80040A4,0x00000000);		// disable sv_yc_switch 				// VD_IN_DELAY_SEL2
	rtd_outl(0xb80040AC,0x00000030);		// decimation filter [6:4] BW [0] 0: data from DF; 1: direct from ADC	// VD_INOUT_CTRL
#endif

}

void drvif_module_vdc_path_and_clamp_setting(void)
{
#if 1
	//-------- VD setting------------------------------------------------
	// vd initial setting
	rtd_outl(0xb8003004,0x00000000);		// set AV							// VIDEO_CONTROL1
	rtd_outl(0xb8003080,0x00000000);		// decimation filter has been changed				// INOUT_CTRL
	rtd_outl(0xb800309C,0x00000047);		// set bgate_raw_sel enable 				// VIDEO_CONTROL2
	rtd_outl(0xb8003620,0x00000108);		// set VDC 444 output					// FSW_CTRL2
	rtd_outl(0xb8003764,0x0008007F);		// bit[9:8]=01, select Select the VCO freq = 432M			// MISC_CONTROL
	rtd_outl(0xb8003794,0x00000000);		// disable pattern generator					// PATTERN_CONTROL
	rtd_outl(0xb80037FC,0x00000000);		// Disable clamp test mode					// ADC_UPDN_CTRL
	rtd_outl(0xb8003608,0x000000C9);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
	rtd_outl(0xb800360C,0x00000000);		// set Y							// CLAMP_UPDN_EN
	rtd_outl(0xb8003610,0x000000FF);		// enable AD1~AD4 clamp up/dn				// CLAMP_RGB_UPDN_EN
#endif

}


//	#define CONFIG_DEBUG_DISPLAY
void drvif_module_vdc_Initial(void)
{

	drvif_module_vdc_ifd_input_path();

	drvif_module_vdc_path_and_clamp_setting();

	printk("VDC initialization done\n");
//	module_vdc_Print_Initial_Registers();
////1/25 end
}
/**
   drvif_module_vdc_SoftReset
   Reset video parameter

   @param <void>       { void }
   @return                  { void }

*/
void drvif_module_vdc_SoftReset(void)
{
	#if sirius_qc //jacky
	soft_reset3_RBUS soft_reset3_reg;
	soft_reset3_reg.regValue = rtd_inl(CRT_SOFT_RESET3_VADDR);
	soft_reset3_reg.rstn_vdec2 = 0;
	rtd_outl(CRT_SOFT_RESET3_VADDR, soft_reset3_reg.regValue);
	
	udelay(10000);

	soft_reset3_reg.regValue = rtd_inl(CRT_SOFT_RESET3_VADDR);
	soft_reset3_reg.rstn_vdec2 = 1;
	rtd_outl(CRT_SOFT_RESET3_VADDR, soft_reset3_reg.regValue);
	
	#else
	sys_srst1_RBUS sys_srst1_reg;
	sys_srst1_reg.regValue = rtd_inl(SYSTEM_SYS_SRST1_VADDR);
	sys_srst1_reg.rstn_vdec2 = 0;	// [21] RSTN_VDEC2: SW Reset bit of  Video Decode (active low)
	rtd_outl(SYSTEM_SYS_SRST1_VADDR, sys_srst1_reg.regValue);

      	udelay(10000);

	sys_srst1_reg.regValue = rtd_inl(SYSTEM_SYS_SRST1_VADDR);
	sys_srst1_reg.rstn_vdec2 = 1;	// [21] RSTN_VDEC2: SW Reset bit of  Video Decode (active low)
	rtd_outl(SYSTEM_SYS_SRST1_VADDR, sys_srst1_reg.regValue);
	#endif
}

void drvif_module_vdc_VDCReset(void)
{
	#if sirius_qc //jacky
	soft_reset3_RBUS soft_reset3_reg;
	soft_reset3_reg.regValue = rtd_inl(CRT_SOFT_RESET3_VADDR);
	soft_reset3_reg.rstn_vdec = 0;
	rtd_outl(CRT_SOFT_RESET3_VADDR, soft_reset3_reg.regValue);
	udelay(10000);
	soft_reset3_reg.regValue = rtd_inl(CRT_SOFT_RESET3_VADDR);
	soft_reset3_reg.rstn_vdec = 1;
	rtd_outl(CRT_SOFT_RESET3_VADDR, soft_reset3_reg.regValue);
	#else
	sys_srst1_RBUS sys_srst1_reg;		// 1_0104
	sys_srst1_reg.regValue = rtd_inl(SYSTEM_SYS_SRST1_VADDR);
	sys_srst1_reg.rstn_vdec = 0;	// [22] RSTN_VDEC: Reset bit of  Video Decode (active low)
	rtd_outl(SYSTEM_SYS_SRST1_VADDR, sys_srst1_reg.regValue);

      	udelay(100000);
		
	sys_srst1_reg.regValue = rtd_inl(SYSTEM_SYS_SRST1_VADDR);	// 1_0104
	sys_srst1_reg.rstn_vdec = 1;	// [22] RSTN_VDEC: Reset bit of  Video Decode (active low)
	rtd_outl(SYSTEM_SYS_SRST1_VADDR, sys_srst1_reg.regValue);
	#endif
}

void drvif_module_vdc_clock_enable(bool on_off)
{
	#if sirius_qc //jacky
	clock_enable1_RBUS clock_enable1_reg;

	if(on_off)
	{
		clock_enable1_reg.regValue = rtd_inl(CRT_CLOCK_ENABLE1_VADDR);
		clock_enable1_reg.clken_vdec = 1;
		rtd_outl(CRT_CLOCK_ENABLE1_VADDR, clock_enable1_reg.regValue);
	}
	else
	{
		clock_enable1_reg.regValue = rtd_inl(CRT_CLOCK_ENABLE1_VADDR);
		clock_enable1_reg.clken_vdec = 0;
		rtd_outl(CRT_CLOCK_ENABLE1_VADDR, clock_enable1_reg.regValue);
	}
	#else
	sys_clken1_RBUS sys_clken1_reg;	// 1_0114
	if(on_off)
	{
		sys_clken1_reg.regValue = rtd_inl(SYSTEM_SYS_CLKEN1_VADDR);
		sys_clken1_reg.clken_vdec = 1;
		rtd_outl(SYSTEM_SYS_CLKEN1_VADDR, sys_clken1_reg.regValue);
//		rtd_maskl(SYSTEM_SYS_CLKEN1_VADDR,~_BIT22, _BIT22);	// &(~bit22) |(bit22) => set bit22 = 1
	}
	else
	{
		sys_clken1_reg.regValue = rtd_inl(SYSTEM_SYS_CLKEN1_VADDR);
		sys_clken1_reg.clken_vdec = 0;
		rtd_outl(SYSTEM_SYS_CLKEN1_VADDR, sys_clken1_reg.regValue);	// 1_0114
//		rtd_maskl(SYSTEM_SYS_CLKEN1_VADDR,~_BIT22, _ZERO);	// &(~bit22) |(0x0) => set bit22 = 0
////1/27 end
	}
	#endif
}

UINT8 drvif_module_vdc_CheckHVisLocked(void)
{
	UINT8 Data[1];

	Data[0]=(UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR);	// 1_9008

	if (!(Data[0] & _BIT0))
	{
		if ((Data[0] & _HSLCK) && (Data[0] & _VLINF))
		{
//			printk("\n VDC Locked..................... \n");
			return 1;
		}
	}

//	printk("\n VDC unLock////////////  \n");
	return 0;
////1/27 end
}

bool module_vdc_CheckHVCisLocked(UINT8 Y_path)
{
	UINT32 i, j;
	UINT8  no_signal;
	UINT8  mode_check ;
	
  	for(i=0; i<20000; i++)
 	{
		/*for(j=0; j<500; j++)
 		{
  			udelay(2000);
		}*/
		udelay(50);
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		if (no_signal == 0xe)
		{
			printk("[QC][VD][Y VDBS test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
			break;
		}
	}

//	module_vdc_Print_Registers(VIDEO_INPUT11, VIDEO_GNDA1, 2000);	// 2013.03/28 Mark: debug
	
  	if (no_signal == 0x00)
	{
		printk("[QC][VD][AV] crystal does not work! the signal is %x\n", no_signal);
		return _FAIL;
	}
  	else if (no_signal == 0x01)
	{
		printk("[QC][VD][AV] no signal = %x, fail!\n", no_signal);
		return _FAIL;
	}	
	else if (no_signal == 0xe)
	{
		printk("[QC][VD][AV] VD test input VIN%dP is OK with no_signal = %x\n", Y_path, no_signal);
		return _SUCCESS;
	}
	else 
	{
		printk("[QC][VD][AV] VD test input VIN%dP is fail, the signal value==>%x \n", Y_path, no_signal);
		return _FAIL;
	}
	return _SUCCESS;
}

UINT8 module_vdc_SetADCPath(UINT8 path_signal, UINT8 path_gnd)
{
	unsigned short ucDcRestore_RGB;
	unsigned short ucDcRestore_VD;
	unsigned short ucYppClamp_RGB;
	unsigned short ucYppClamp_VD;
	unsigned short ucClampUpDn_RGB;
	unsigned short ucClampUpDn_VD;
	unsigned char ucTemp;

	adc_power_RBUS adc_power_reg;	// 2_0000
	adc_power_reg.regValue = rtd_inl(ADC_ADC_POWER_VADDR);
	adc_ibias0123_RBUS adc_ibias0123_reg;	// 2_0004
	adc_ibias0123_reg.regValue = rtd_inl(ADC_ADC_IBIAS0123_VADDR);
	adc_ctl_rgb12_RBUS adc_ctl_rgb12_reg;		// 2_0008
	adc_ctl_rgb12_reg.regValue = rtd_inl(ADC_ADC_CTL_RGB12_VADDR);
	adc_clock_RBUS adc_clock_reg;	// 2_0010
	adc_clock_reg.regValue = rtd_inl(ADC_ADC_CLOCK_VADDR);
	adc_ctl_reserved_RBUS adc_ctl_reserved_reg;	// 2_0014
	adc_ctl_reserved_reg.regValue = rtd_inl(ADC_ADC_CTL_RESERVED_VADDR);
	adc_dcrestore_ctrl_RBUS adc_dcrestore_ctrl_reg;	// 2_0018
	adc_dcrestore_ctrl_reg.regValue = rtd_inl(ADC_ADC_DCRESTORE_CTRL_VADDR);
	adc_clamp_ctrl0_RBUS adc_clamp_ctrl0_reg;	// 2_001c
	adc_clamp_ctrl0_reg.regValue = rtd_inl(ADC_ADC_CLAMP_CTRL0_VADDR);
	adc_clamp_ctrl1_RBUS adc_clamp_ctrl1_reg;	// 2_0020
	adc_clamp_ctrl1_reg.regValue = rtd_inl(ADC_ADC_CLAMP_CTRL1_VADDR);
	adc_clamp_ctrl2_RBUS adc_clamp_ctrl2_reg;	// 2_0024
	adc_clamp_ctrl2_reg.regValue = rtd_inl(ADC_ADC_CLAMP_CTRL2_VADDR);
	adc_clamp_ctrl3_RBUS adc_clamp_ctrl3_reg;	// 2_0028
	adc_clamp_ctrl3_reg.regValue = rtd_inl(ADC_ADC_CLAMP_CTRL3_VADDR);
	adc_gain0_RBUS adc_gain0_reg;	// 2_0030
	adc_gain0_reg.regValue = rtd_inl(ADC_ADC_GAIN0_VADDR);
	adc_gain1_RBUS adc_gain1_reg;	// 2_0034
	adc_gain1_reg.regValue = rtd_inl(ADC_ADC_GAIN1_VADDR);
	//USER: Vincent_Lee  DATE: 2012/5/10 TODO: Set the ADC offset value when CVBS source init.
	adc_offset0_RBUS adc_offset0_reg;	// 2_0038
	adc_offset0_reg.regValue = rtd_inl(ADC_ADC_OFFSET0_VADDR);
	adc_offset1_RBUS adc_offset1_reg;	// 2_003c
	adc_offset1_reg.regValue = rtd_inl(ADC_ADC_OFFSET1_VADDR);
	vd_adc_clamp_ctl_1_RBUS vd_adc_clamp_ctl_1_reg;	// 2_0048
	vd_adc_clamp_ctl_1_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR);
	vd_adc_clamp_ctl_2_RBUS vd_adc_clamp_ctl_2_reg;	// 2_004c
	vd_adc_clamp_ctl_2_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR);
	vd_adc_updn_ctl_RBUS vd_adc_updn_ctl_reg;	// 2_0050
	vd_adc_updn_ctl_reg.regValue = rtd_inl(ADC_VD_ADC_UPDN_CTL_VADDR);
 	vdadc_core_lpf_ctrl_RBUS vdadc_core_lpf_ctrl_reg;	// 2_0054
	vdadc_core_lpf_ctrl_reg.regValue = rtd_inl(ADC_VDADC_CORE_LPF_CTRL_VADDR);
	vdadc_ck_ctl_RBUS vdadc_ck_ctl_reg;	// 2_0058
	vdadc_ck_ctl_reg.regValue = rtd_inl(ADC_VDADC_CK_CTL_VADDR);
	vdadc_pow_ctl_RBUS vdadc_pow_ctl_reg;	// 2_005c
	vdadc_pow_ctl_reg.regValue = rtd_inl(ADC_VDADC_POW_CTL_VADDR);

	udelay(50);

	switch(path_signal)
	{
		case VIDEO_INPUT0:
			dmsg("case: VIDEO_INPUT0 = %d\n", path_signal);
		case VIDEO_INPUT1:
			dmsg("case: VIDEO_INPUT1 = %d\n", path_signal);
		case VIDEO_INPUT2:
			dmsg("case: VIDEO_INPUT2 = %d\n", path_signal);
			adc_ctl_rgb12_reg.adc_ctl_rgb1_1_0 = 0x0;	// 2_0008[1:0] B Channel Input+ = VIN0P
			adc_ctl_rgb12_reg.adc_ctl_rgb1_3_2 = 0x0;	// 2_0008[3:2] G Channel Input+ = VIN1P
			adc_ctl_rgb12_reg.adc_ctl_rgb1_5_4 = 0x0;	// 2_0008[5:4] R Channel Input+ = VIN2P
			dmsg("adc_ctl_rgb12_reg.adc_ctl_rgb1_1_0 = %X\n",adc_ctl_rgb12_reg.adc_ctl_rgb1_1_0);
			break;
		case VIDEO_INPUT4:
			dmsg("case: VIDEO_INPUT4 = %d\n", path_signal);
			adc_ctl_rgb12_reg.adc_ctl_rgb1_7 = 0x1;		// 2_0008[7] G Channel Input+ Select VIN4PP
		case VIDEO_INPUT3:
			dmsg("case: VIDEO_INPUT3 = %d\n", path_signal);
		case VIDEO_INPUT5:
			dmsg("case: VIDEO_INPUT5 = %d\n", path_signal);
			adc_ctl_rgb12_reg.adc_ctl_rgb1_1_0 = 0x1;	// 2_0008[1:0] B Channel Input+ = VIN3P
			adc_ctl_rgb12_reg.adc_ctl_rgb1_3_2 = 0x1;	// 2_0008[3:2] G Channel Input+ = VIN4P
			adc_ctl_rgb12_reg.adc_ctl_rgb1_5_4 = 0x1;	// 2_0008[5:4] R Channel Input+ = VIN5P
			break;
		case VIDEO_INPUT7:
			dmsg("case: VIDEO_INPUT7 = %d\n", path_signal);
			adc_ctl_rgb12_reg.adc_ctl_rgb1_8 = 0x1;		// 2_0008[8] G Channel Input+ Select VIN7PP
		case VIDEO_INPUT8:
			dmsg("case: VIDEO_INPUT8 = %d\n", path_signal);
			adc_ctl_rgb12_reg.adc_ctl_rgb1_9 = 0x1;		// 2_0008[9] R Channel Input+ Select VIN8PP
		case VIDEO_INPUT6:
			dmsg("case: VIDEO_INPUT6 = %d\n", path_signal);
			adc_ctl_rgb12_reg.adc_ctl_rgb1_1_0 = 0x2;	// 2_0008[1:0] B Channel Input+ = VIN6P
			adc_ctl_rgb12_reg.adc_ctl_rgb1_3_2 = 0x2;	// 2_0008[3:2] G Channel Input+ = VIN7P
			adc_ctl_rgb12_reg.adc_ctl_rgb1_5_4 = 0x2;	// 2_0008[5:4] R Channel Input+ = VIN8P
			break;
		case VIDEO_INPUT9:
		case VIDEO_INPUT10:
		case VIDEO_INPUT11:
		case VIDEO_INPUT12:
		case VIDEO_INPUT13:
		case VIDEO_INPUT14:
		default:
			dmsg("case: VIDEO_INPUT = %d\n", path_signal);
			adc_ctl_rgb12_reg.adc_ctl_rgb1_1_0 = 0x3;	// 2_0008[1:0] B Channel Input+ = X
			adc_ctl_rgb12_reg.adc_ctl_rgb1_3_2 = 0x3;	// 2_0008[3:2] G Channel Input+ = X
			adc_ctl_rgb12_reg.adc_ctl_rgb1_5_4 = 0x3;	// 2_0008[5:4] R Channel Input+ = X
			break;
	}
	
	ucDcRestore_RGB = adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl;		// 2_0018 [8:0] DC restore enable = R2,G2,B2,R1,G1,B1,R0,G0,B0
	ucDcRestore_VD = vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_15_13;	// 2_0048 [15:13] DC restore enable = V2,V1,V0
			
	ucYppClamp_RGB = adc_clamp_ctrl1_reg.adc_clamp_ctrl0;			// 2_0020 [8:0] Clamp Enable = R2,G2,B2,R1,G1,B1,R0,G0,B0
	ucYppClamp_VD = vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_7_5;	// 2_0048 [7:5] Clamp Enable = V2,V1,V0

	ucClampUpDn_RGB = adc_clamp_ctrl2_reg.adc_clamp_ctrl3;			// 2_0024 [8:0] VDC UP/DN Enable = R2,G2,B2,R1,G1,B1,R0,G0,B0
	ucClampUpDn_VD = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0;		// 2_0050 [2:0] VDC UP/DN Enable = V2,V1,V0
    dmsg("ucClampUpDn_VD = %0x\n", ucClampUpDn_VD);	// 2_0050[2:0]
    
	udelay(50);
	
	switch(path_signal)
	{
//////// B channel setting /////////////////////////////////////////////////////////////////////////////////
		case VIDEO_INPUT0:
//				printk("case: VIDEO_INPUT0 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000001));	// 2_0018[0] = 0, disable dc restore
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000001));		// 2_0020[0] = 0, disable YPP clamp
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000001);			// 2_0024[0] = 1, enable clamp up/dn
			goto _B_Ch_Set;
			
		case VIDEO_INPUT3:
//				printk("case: VIDEO_INPUT3 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000008));	// 2_0018[3] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000008));		// 2_0020[3] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000008);			// 2_0024[3] = 1
			goto _B_Ch_Set;
			
		case VIDEO_INPUT6:
//				printk("case: VIDEO_INPUT6 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000040));	// 2_0018[6] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000040));		// 2_0020[6] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000040);			// 2_0024[6] = 1
_B_Ch_Set:
//				RTD_Log(LOGGER_INFO, "[VDC][Set Blue channel] %x\n",path_signal);
//				B Ch Gnd Set Input-[19][18][17]
				adc_clamp_ctrl1_reg.adc_clamp_ctrl4_5 = 1;	// 2_0020[21] Blue[0]- Negative UP/DN NCLAMP_EN Enable
				adc_gain1_reg.adc_gain_blu = 0x300;			// 2_0034[10:0] Blue Channel Gain Adjust
//				B Channel Input- [17:16] : VIDEO_GN(0x00), VIDEO_Y0N(0x21), VIDEO_Y1N(0x22)

				dmsg("path_gnd = %x\n",path_gnd);
				if(path_gnd == VIDEO_GNDB)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_1_0 = 0x00;	// 2_0008[17:16] B Channel Input- Select = BN
				else if(path_gnd == VIDEO_GNDY0)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_1_0 = 0x01;	// 2_0008[17:16] B Channel Input- Select = Y0N
				else if(path_gnd == VIDEO_GNDY1)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_1_0 = 0x02;	// 2_0008[17:16] B Channel Input- Select = Y1N
				else
					adc_ctl_rgb12_reg.adc_ctl_rgb2_1_0 = 0x03;	// 2_0008[17:16] B Channel Input- Select = X
				dmsg("path_gnd & 0x03 = %x\n",path_gnd & 0x03);
				
				dmsg("case: VIDEO_BN = %d\n",adc_ctl_rgb12_reg.adc_ctl_rgb2_1_0);
				dmsg("case: VIDEO_GN = %d\n",adc_ctl_rgb12_reg.adc_ctl_rgb2_3_2);
				dmsg("case: VIDEO_RN = %d\n",adc_ctl_rgb12_reg.adc_ctl_rgb2_5_4);
				ucTemp = 0;
			break;
//////// G channel setting /////////////////////////////////////////////////////////////////////////////////
		case VIDEO_INPUT1:
//				printk("case: VIDEO_INPUT1 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000002));	// 2_0018[1] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000002));		// 2_0020[1] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000002);			// 2_0024[1] = 1
			goto _G_Ch_Set;
		case VIDEO_INPUT4:
//				printk("case: VIDEO_INPUT4 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000010));	// 2_0018[4] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000010));		// 2_0020[4] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000010);			// 2_0024[4] = 1
			goto _G_Ch_Set;
		case VIDEO_INPUT7:
//				printk("case: VIDEO_INPUT7 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000080));	// 2_0018[7] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000080));		// 2_0020[7] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000080);			// 2_0024[7] = 1
_G_Ch_Set:
//				RTD_Log(LOGGER_INFO, "[VDC][Set Green channel] %x\n",path_signal);
//				G Ch Gnd Set Input-[19][18][17]
				adc_clamp_ctrl1_reg.adc_clamp_ctrl4_6 = 1;	// 2_0020[22] Green[4]- Negative UP/DN NCLAMP_EN Enable
				adc_gain0_reg.adc_gain_grn = 0x300;			// 2_0030[26:16] Green Channel Gain Adjust
//				G Channel Input- [19:18] : VIDEO_GN(0x10), VIDEO_Y0N(0x21), VIDEO_Y1N(0x22)

				dmsg("path_gnd = %x\n",path_gnd);
				if(path_gnd == VIDEO_GNDR)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_3_2= 0x00;	// 2_0008[19:18] G Channel Input- Select = GN
				else if(path_gnd == VIDEO_GNDY0)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_3_2 = 0x01;	// 2_0008[19:18] G Channel Input- Select = Y0N
				else if(path_gnd == VIDEO_GNDY1)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_3_2 = 0x02;	// 2_0008[19:18] G Channel Input- Select = Y1N
				else
					adc_ctl_rgb12_reg.adc_ctl_rgb2_3_2 = 0x03;	// 2_0008[19:18] G Channel Input- Select = X
				dmsg("path_gnd & 0x03 = %x\n",path_gnd & 0x03);
			
				dmsg("case: VIDEO_BN = %d\n", adc_ctl_rgb12_reg.adc_ctl_rgb2_1_0);
				dmsg("case: VIDEO_GN = %d\n", adc_ctl_rgb12_reg.adc_ctl_rgb2_3_2);
				dmsg("case: VIDEO_RN = %d\n", adc_ctl_rgb12_reg.adc_ctl_rgb2_5_4);
				ucTemp = 1;
			break;
//////// R channel setting /////////////////////////////////////////////////////////////////////////////////
		case VIDEO_INPUT2:
				dmsg("case: VIDEO_INPUT2 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000004));	// 2_0018[2] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000004));		// 2_0020[2] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000004);			// 2_0024[2] = 1
			goto _R_Ch_Set;
		case VIDEO_INPUT5:
				dmsg("case: VIDEO_INPUT5 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000020));	// 2_0018[5] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000020));		// 2_0020[5] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000020);			// 2_0024[5] = 1
			goto _R_Ch_Set;
		case VIDEO_INPUT8:
				dmsg("case: VIDEO_INPUT8 = %d\n", path_signal);
				adc_dcrestore_ctrl_reg.adc_dcrestore_ctrl = (ucDcRestore_RGB & (~0x00000100));	// 2_0018[8] = 0
				adc_clamp_ctrl1_reg.adc_clamp_ctrl0 = (ucYppClamp_RGB & (~0x00000100));		// 2_0020[8] = 0
				adc_clamp_ctrl2_reg.adc_clamp_ctrl3 = (ucClampUpDn_RGB | 0x00000100);			// 2_0024[8] = 1
_R_Ch_Set:
//				RTD_Log(LOGGER_INFO, "[VDC][Set Red channel] %x\n",path_signal);
//				R Ch Gnd Set Input-[19][18][17]
				adc_clamp_ctrl1_reg.adc_clamp_ctrl4_7 = 1;	// 2_0020[23] Red[8]- Negative UP/DN NCLAMP_EN Enable
				adc_gain0_reg.adc_gain_red= 0x300;			// 2_0030[10:0] Red Channel Gain Adjust
//				R Channel Input- [21:20] : VIDEO_RN(0x20), VIDEO_Y0N(0x21), VIDEO_Y1NN(0x22); Y1NN => VIDEO_GNDA0(0x30), VIDEO_GNDA1(0x31)

				printk("path_gnd = %x\n",path_gnd);
				if(path_gnd == VIDEO_GNDR)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_5_4 = 0x00;	// 2_0008[21:20] R Channel Input- Select = GN
				else if(path_gnd == VIDEO_GNDY0)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_5_4 = 0x01;	// 2_0008[21:20] R Channel Input- Select = Y0N
				else if(path_gnd == VIDEO_GNDY1)
					adc_ctl_rgb12_reg.adc_ctl_rgb2_5_4 = 0x02;	// 2_0008[21:20] R Channel Input- Select = Y1N
				else
					adc_ctl_rgb12_reg.adc_ctl_rgb2_5_4 = 0x03;	// 2_0008[21:20] R Channel Input- Select = X
				dmsg("path_gnd & 0x03 = %x\n",path_gnd & 0x03);
				dmsg("case: VIDEO_BN = %d\n", adc_ctl_rgb12_reg.adc_ctl_rgb2_1_0);
				dmsg("case: VIDEO_GN = %d\n", adc_ctl_rgb12_reg.adc_ctl_rgb2_3_2);
				dmsg("case: VIDEO_RN = %d\n", adc_ctl_rgb12_reg.adc_ctl_rgb2_5_4);
				ucTemp = 2;
			break;
////2/18 end
//////// V Channel Input+ [28:26][7:6] : 9P~13P /////////////////////////////////////////////////////////////
//////// sirius V Channel Input: 9P,10P,12P,13P /////////////////////////////////////////////////////////////
		case VIDEO_INPUT9:	// set 2_0008[26] = 1 and [7:6] = 00
				dmsg("case: VIDEO_INPUT9 = %d\n", path_signal);
				vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_10 = 0x0;//0050 //[10] V Channel Passive Input+ Select  VIN9PP (0: VIN9P, 1: VIN8P)
				vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_10_9 = 0x0;//0048 //BIT [10:9]: V Channel Input+ Select 00: Select VIN9PP 01: Select VIN10P 10: Select VIN11PP
				ucTemp = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0;
				ucTemp |= _BIT0;
				vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0 = ucTemp;	// 2_0050[0] = 1, enable VD0 clamp up/dn
			goto _V_Ch_Gnd_Set;

		case VIDEO_INPUT10:	// set 2_0008[27] = 1 and [7:6] = 01
				dmsg("case: VIDEO_INPUT10 = %d\n", path_signal);
				vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_10_9 = 0x1;//BIT [10:9]: V Channel Input+ Select 00: Select VIN9PP 01: Select VIN10P 10: Select VIN11PP
				ucTemp = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0;
				ucTemp |= _BIT1;
				vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0 = ucTemp;	// 2_0050[0] = 1, enable VD0 clamp up/dn
				//dmsg("vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_11_9 = %x\n", vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_11_9);
			goto _V_Ch_Gnd_Set;

		default:
		case VIDEO_INPUT12:	
				vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_9_8 = 0x0;//[9:8]: V Channel Passive Input+ Select VIN11PP (00/01: VIN12P, 10/11: VIN13P)
				vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_10_9 = 0x2;//BIT [10:9]: V Channel Input+ Select 00: Select VIN9PP 01: Select VIN10P 10: Select VIN11PP
				ucTemp = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0;
				ucTemp |= _BIT2;
				vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0 = ucTemp;	// 2_0050[0] = 1, enable VD0 clamp up/dn			
				dmsg("vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_9_8 = %X // 2_004c[9:8] V Channel Passive Input+ Select VIN11PP = VIN12P\n",vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_9_8);
			goto _V_Ch_Set;

		case VIDEO_INPUT13:	
			vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_9_8 = 0x2;//[9:8]: V Channel Passive Input+ Select VIN11PP (00/01: VIN12P, 10/11: VIN13P)
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_10_9 = 0x2;//BIT [10:9]: V Channel Input+ Select 00: Select VIN9PP 01: Select VIN10P 10: Select VIN11PP
			vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0 = 0x4;	// 2_0050[0] = 1, enable VD0 clamp up/dn		
			goto _V_Ch_Set;

//				printk("test before V Ch Set %x = %08X\n", ADC_VDADC_CORE_LPF_CTRL_VADDR, vdadc_core_lpf_ctrl_reg.regValue);	// 2_0054

_V_Ch_Set:	// set 2_0008[28] V Channel Input+ Select = 1(VIN11PP); and 2_0008[7:6] V Channel 1st 2nd LPF Input+ Select, for YC Mix = 10(VIN11PP)
			//vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_9_8 = 0x02;	// 2_0048[25:24] V Channel 1st 2nd LPF Input+ Select, for YC Mix = VIN11PP
			#if 0 //jacky_adc
			ucTemp = vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_11_9;	// 2_0048[11:9] V Channel Input+ Select
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_11_9 = (ucTemp | _BIT2);	// 2_0048[11:9] V Channel Input+ Select = VIN11PP (turn on source follower)
			#endif
			//vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0 = (ucClampUpDn_VD | _BIT2);	// 2_0050[2] = 1, enable VD2 clamp up/dn
//			printk("vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_11_9 = %x\n", vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_11_9);
////2/21
_V_Ch_Gnd_Set:
			switch(path_gnd)
			{
				case VIDEO_GNDA0:	// 2_0020[28] VDC [9]- Negative UP/DN NCLAMP_EN Enable
//					vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14 = 0x00;	// 2_0048[31:30] V Channel Input- Select = 00: A0N; 01: A1N; 10: A2N; 11: X
					dmsg("case: VIDEO_GNDA0 = %X\n", path_gnd);
					//ucTemp = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8;	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2,V1,V0
					dmsg("ucTemp = %X // 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2,V1,V0\n",ucTemp);
					vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = (ucTemp | _BIT0);	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V0
					vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = 0x1;	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V0
					dmsg("vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = %X // 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V0\n",vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8);
					dmsg("vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = %d\n", vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8);
					break;
				case VIDEO_GNDA1:	// 2_0020[29] VDC [10]- Negative UP/DN NCLAMP_EN Enable
//					vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14 = 0x01;	// 2_0048[31:30] V Channel Input- Select = 00: A0N; 01: A1N; 10: A2N; 11: X
					ucTemp = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8;	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2,V1,V0
					//vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = (ucTemp | _BIT1);	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V1
					vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = 0x2;	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V1
					dmsg("vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = %d\n", vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8);
					break;
				case VIDEO_GNDA2:	// 2_0020[20] VDC [11]- Negative UP/DN NCLAMP_EN Enable
//					vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14 = 0x02;	// 2_0048[31:30] V Channel Input- Select = 00: A0N; 01: A1N; 10: A2N; 11: X
					ucTemp = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8;	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2,V1,V0
					//vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = (ucTemp | _BIT2);	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2
					vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = 0x4;	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2
					dmsg("vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = %d\n", vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8);
					break;
				default:	// All negative up/dn NCLAMP_EN Enable
//					vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14 = 0x03;	// 2_0048[31:30] V Channel Input- Select = 00: A0N; 01: A1N; 10: A2N; 11: X
					ucTemp = vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8;	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2,V1,V0
					vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8= (ucTemp | 0x07);	// 2_0050[10:8] Negative UP/DN NCLAMP_EN Enable = V2, V1, V0
					break;
			}
//			V Channel Input- 2_0008[23:22] : VIDEO_GNDA0(0x30), VIDEO_GNDA1(0x31), VIDEO_GNDA2(0x32)
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14 = (path_gnd & 0x03);	// 2_0048[31:30] V Channel Input- Select
//			dmsg("vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14 = %x", vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14);
			ucTemp = 3;
			break;
	}
//	udelay(2000);
	udelay(50);
	
	rtd_outl(ADC_ADC_POWER_VADDR,adc_power_reg.regValue);	// 2_0000
	rtd_outl(ADC_ADC_IBIAS0123_VADDR,adc_ibias0123_reg.regValue);	// 2_0004
	rtd_outl(ADC_ADC_CTL_RGB12_VADDR,adc_ctl_rgb12_reg.regValue);	// 2_0008
	rtd_outl(ADC_ADC_CLOCK_VADDR,adc_clock_reg.regValue);	// 2_0010
	rtd_outl(ADC_ADC_CTL_RESERVED_VADDR,adc_ctl_reserved_reg.regValue);	// 2_0014
	rtd_outl(ADC_ADC_DCRESTORE_CTRL_VADDR,adc_dcrestore_ctrl_reg.regValue);	// 2_0018
	rtd_outl(ADC_ADC_CLAMP_CTRL0_VADDR,adc_clamp_ctrl0_reg.regValue);	// 2_001c
	rtd_outl(ADC_ADC_CLAMP_CTRL1_VADDR,adc_clamp_ctrl1_reg.regValue);	// 2_0020
	rtd_outl(ADC_ADC_CLAMP_CTRL2_VADDR,adc_clamp_ctrl2_reg.regValue);	// 2_0024
	rtd_outl(ADC_ADC_CLAMP_CTRL3_VADDR,adc_clamp_ctrl3_reg.regValue);// 2_0028
	rtd_outl(ADC_ADC_GAIN0_VADDR,adc_gain0_reg.regValue);	// 2_0030
	rtd_outl(ADC_ADC_GAIN1_VADDR,adc_gain1_reg.regValue);	// 2_0034
	rtd_outl(ADC_ADC_OFFSET0_VADDR,adc_offset0_reg.regValue);	// 2_0038
	rtd_outl(ADC_ADC_OFFSET1_VADDR,adc_offset1_reg.regValue);	// 2_003c
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_1_VADDR, vd_adc_clamp_ctl_1_reg.regValue);	// 2_0048
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_2_VADDR, vd_adc_clamp_ctl_2_reg.regValue);	// 2_004c
	rtd_outl(ADC_VD_ADC_UPDN_CTL_VADDR,vd_adc_updn_ctl_reg.regValue);	// 2_0050
	rtd_outl(ADC_VDADC_CORE_LPF_CTRL_VADDR, vdadc_core_lpf_ctrl_reg.regValue);	// 2_0054
	rtd_outl(ADC_VDADC_CK_CTL_VADDR,vdadc_ck_ctl_reg.regValue);	// 2_0058
	rtd_outl(ADC_VDADC_POW_CTL_VADDR, vdadc_pow_ctl_reg.regValue);	// 2_005c
//	udelay(2000);
	udelay(50);
	return ucTemp;
}

void module_vdc_ClampType_set(unsigned char ClampTpye, unsigned char ClampADC)
{	// set 960c, 9610
	CLAMP_UPDN_EN_RBUS clamp_updn_en_reg;	// 960c
	clamp_updn_en_reg.regValue = rtd_inl(VDC_CLAMP_UPDN_EN_VADDR);
	CLAMP_RGB_UPDN_EN_RBUS clamp_rgb_updn_en_reg;	// 9610
	clamp_rgb_updn_en_reg.regValue = rtd_inl(VDC_CLAMP_RGB_UPDN_EN_VADDR);

//	printk("9608 = %x\n9610 = %x\n", rtd_inl(VDC_CLAMP_UPDN_EN_VADDR), rtd_inl(VDC_CLAMP_RGB_UPDN_EN_VADDR));
//	printk("[QC][Clamp Type set] Type = %d; ADC = %d\n", ClampTpye, ClampADC);

	switch(ClampADC)
	{
		case 0:	// B-ch
			clamp_updn_en_reg.clamp_ad1 = ClampTpye;	// 1_960c[7:6] clamp selection for AD1 part
			clamp_rgb_updn_en_reg.clamp_a_up_en = 1;	// 1_9610[7] enable cleamp up
			clamp_rgb_updn_en_reg.clamp_a_dn_en = 1;	// 1_9610[6] enable cleamp dn
#if 1
//			printk("case 0:	1_960c[7:6] clamp selection for AD1 part = %X\n",clamp_updn_en_reg.clamp_ad1);
#endif
			break;
		case 1:	// G-ch
			clamp_updn_en_reg.clamp_ad2 = ClampTpye;	// 1_960c[5:4] clamp selection for AD2 part
			clamp_rgb_updn_en_reg.clamp_b_up_en = 1;	// 1_9610[5] enable cleamp up
			clamp_rgb_updn_en_reg.clamp_b_dn_en = 1;	// 1_9610[4] enable cleamp dn
#if 1
//			printk("case 1:	1_960c[5:4] clamp selection for AD2 part = %X\n",clamp_updn_en_reg.clamp_ad2);
#endif
			break;
		case 2:	// R-ch
			clamp_updn_en_reg.clamp_ad3 = ClampTpye;	// 1_960c[3:2] clamp selection for AD3 part
			clamp_rgb_updn_en_reg.clamp_c_up_en = 1;	// 1_9610[3] enable cleamp up
			clamp_rgb_updn_en_reg.clamp_c_dn_en = 1;	// 1_9610[2] enable cleamp dn
#if 1
//			printk("case 2:	1_960c[3:2] clamp selection for AD3 part = %X\n",clamp_updn_en_reg.clamp_ad3);
#endif
			break;
		default:
		case 3:	// V-ch
			clamp_updn_en_reg.clamp_ad4 = ClampTpye;	// 1_960c[1:0] clamp selection for AD4 part
			clamp_rgb_updn_en_reg.clamp_d_up_en = 1;	// 1_9610[1] enable cleamp up
			clamp_rgb_updn_en_reg.clamp_d_dn_en = 1;	// 1_9610[0] enable cleamp dn
#if 1
//			printk("case 3:	1_960c[1:0] clamp selection for AD4 part = %X\n",clamp_updn_en_reg.clamp_ad4);
#endif
			break;
	}

	rtd_outl(VDC_CLAMP_UPDN_EN_VADDR,clamp_updn_en_reg.regValue);	// 1_960c
	rtd_outl(VDC_CLAMP_RGB_UPDN_EN_VADDR,clamp_rgb_updn_en_reg.regValue);	// 1_9610
}

void drvif_module_Set_VD_pll27x_54M_CLK(bool on_off)
{	// 0_0508[6] 
	#if sirius_qc //jacky
	sys_pll_27x4_RBUS sys_pll_27x4_reg;	// 0_04dc
	sys_pll_27x4_reg.regValue = rtd_inl(CRT_SYS_PLL_27X4_VADDR);
	sys_pll_27x4_reg.pll27x_yppadc_ck54m_en = on_off;	// 0_04dc[12] PLL27x YPPADC 54MHz clock enable
	rtd_outl(CRT_SYS_PLL_27X4_VADDR,sys_pll_27x4_reg.regValue);	// 0_04dc
	#else
	sys_pll_27x4_RBUS sys_pll_27x4_reg;	// 0_04dc
	sys_pll_27x4_reg.regValue = rtd_inl(SYSTEM_SYS_PLL_27X4_VADDR);
	sys_pll_27x4_reg.pll27x_yppadc_ck54m_en = on_off;	// 0_04dc[12] PLL27x YPPADC 54MHz clock enable
	rtd_outl(SYSTEM_SYS_PLL_27X4_VADDR,sys_pll_27x4_reg.regValue);	// 0_04dc
	#endif
}

/**
	 module_vdc_SetInput_Y
	if the input is the av ,the function is setting the y registers
	@param<SrcType> {uint8_t Y_path, uint8_t Y_Gnd_path}
	return { none }
	@ingroup dragon_video
*/
void module_vdc_SetInput_Y(unsigned char Y_path, unsigned char Y_Gnd_path)
{
	unsigned char ADCselect;

	printk( "[VDC][Set Input Y][Y_path] %d, [Y_Gnd_path] %d\n", Y_path, Y_Gnd_path);

	//make sure the sv disable
	vd_adc_clamp_ctl_2_RBUS vd_adc_clamp_ctl_2_reg;		// 2_004c
	vd_adc_clamp_ctl_2_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR);
	vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_5 = 0;	
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_2_VADDR,vd_adc_clamp_ctl_2_reg.regValue);
	
	ADCselect = (module_vdc_SetADCPath(Y_path, Y_Gnd_path) & 0x03);
#if 0
	printk("ADCselect = %X	//result of Set ADC Path\n",ADCselect);
#endif

#if 0//sirius_qc//jacky
	#if 1 
	VIDEO_CONTROL1_RBUS VIDEO_CONTROL1_reg;
	VIDEO_CONTROL1_reg.regValue = rtd_inl(VDC_VIDEO_CONTROL1_VADDR);
	VIDEO_CONTROL1_reg.regValue = 0x0;
	rtd_outl(VDC_VIDEO_CONTROL1_VADDR,VIDEO_CONTROL1_reg.regValue);		// set AV		// VIDEO_CONTROL1
	INOUT_CTRL_RBUS INOUT_CTRL_reg;
	INOUT_CTRL_reg.regValue = rtd_inl(VDC_INOUT_CTRL_VADDR);
	INOUT_CTRL_reg.regValue= 0x0;
	rtd_outl(VDC_INOUT_CTRL_VADDR,INOUT_CTRL_reg.regValue);		// decimation filter has been changed		// INOUT_CTRL
	VIDEO_CONTROL2_RBUS VIDEO_CONTROL2_reg;
	VIDEO_CONTROL2_reg.regValue = rtd_inl(VDC_VIDEO_CONTROL2_VADDR); //value:0x00000047
	VIDEO_CONTROL2_reg.bgate_raw_sel = 0x1; //always high
	VIDEO_CONTROL2_reg.mv_hagc_mode = 0x0;
	rtd_outl(VDC_VIDEO_CONTROL2_VADDR,VIDEO_CONTROL2_reg.regValue);	// set bgate_raw_sel enable 				// VIDEO_CONTROL2
	FSW_CTRL2_RBUS FSW_CTRL2_reg;
	FSW_CTRL2_reg.regValue = rtd_inl(VDC_FSW_CTRL2_VADDR);
	FSW_CTRL2_reg.out444_sel = 0x1; //0: 4:2:2 output 1:  4:4:4 output
	rtd_outl(VDC_FSW_CTRL2_VADDR,FSW_CTRL2_reg.regValue);		// Set 444 output
	MISC_CONTROL_RBUS MISC_CONTROL_reg;
	MISC_CONTROL_reg.regValue = rtd_inl(VDC_MISC_CONTROL_VADDR);
	MISC_CONTROL_reg.swallow_freq_sel = 0x1;
	rtd_outl(VDC_MISC_CONTROL_VADDR,MISC_CONTROL_reg.regValue);	// bit[9:8]=01, select Select the VCO freq = 540M	// MISC_CONTROL
	PATTERN_CONTROL_RBUS PATTERN_CONTROL_reg;
	PATTERN_CONTROL_reg.regValue = rtd_inl(VDC_PATTERN_CONTROL_VADDR);
	PATTERN_CONTROL_reg.regValue = 0x0;
	rtd_outl(VDC_PATTERN_CONTROL_VADDR,PATTERN_CONTROL_reg.regValue);		// disable pattern generator					// PATTERN_CONTROL
	ADC_UPDN_CTRL_RBUS ADC_UPDN_CTRL_reg;
	ADC_UPDN_CTRL_reg.regValue = rtd_inl(VDC_ADC_UPDN_CTRL_VADDR);
	ADC_UPDN_CTRL_reg.regValue = 0x0;
	rtd_outl(VDC_ADC_UPDN_CTRL_VADDR,ADC_UPDN_CTRL_reg.regValue);		// Disable clamp test mode					// ADC_UPDN_CTRL
	#else
	rtd_outl(0xb8003004,0x00000000);		// set AV									// VIDEO_CONTROL1
	rtd_outl(0xb8003080,0x00000000);		// decimation filter has been changed				// INOUT_CTRL
	rtd_outl(0xb800309c,0x00000047);		// set bgate_raw_sel enable					// VIDEO_CONTROL2
	rtd_outl(0xb8003620,0x00000108);		// Set 444 output
	rtd_outl(0xb8003764,0x0008017F);		// bit[9:8]=01, select Select the VCO freq = 540M	// MISC_CONTROL
	rtd_outl(0xb8003794,0x00000000);		// disable pattern generator					// PATTERN_CONTROL
	rtd_outl(0xb80037FC,0x00000000);		// Disable clamp test mode					// ADC_UPDN_CTRL
	#endif
#else// 2013.02/26 Mark: use script settings to save time
	rtd_outl(VDC_VIDEO_CONTROL1_VADDR,0x00000000);		// set AV									// VIDEO_CONTROL1
	rtd_outl(VDC_INOUT_CTRL_VADDR,0x00000000);		// decimation filter has been changed				// INOUT_CTRL
	rtd_outl(VDC_VIDEO_CONTROL2_VADDR,0x00000047);		// set bgate_raw_sel enable					// VIDEO_CONTROL2
	rtd_outl(VDC_FSW_CTRL2_VADDR,0x00000108);		// Set 444 output
	rtd_outl(VDC_MISC_CONTROL_VADDR,0x0008017F);		// bit[9:8]=01, select Select the VCO freq = 540M	// MISC_CONTROL
	rtd_outl(VDC_PATTERN_CONTROL_VADDR,0x00000000);		// disable pattern generator					// PATTERN_CONTROL
	rtd_outl(VDC_ADC_UPDN_CTRL_VADDR,0x00000000);		// Disable clamp test mode					// ADC_UPDN_CTRL
#endif

	AD_SW_CTRL0_RBUS ad_sw_ctrl0_reg;	// 1_9608
	ad_sw_ctrl0_reg.regValue = rtd_inl(VDC_AD_SW_CTRL0_VADDR);
	ad_sw_ctrl0_reg.sw_comp = ADCselect;	// set VD AD switch
#if 0
	printk("ad_sw_ctrl0_reg.sw_comp = %X	//1_9608[7:6]\n",ad_sw_ctrl0_reg.sw_comp);
#endif
	module_vdc_ClampType_set(AD_YorCVBS,ADCselect);	// 1_960c & 1_9610 set Y
	drvif_module_Set_VD_pll27x_54M_CLK(0);	// 0_04dc[12] PLL27x YPPADC 54MHz clock enable, used by SCART

#if sirius_qc
	rtd_outl(FEin_VD_IN_DELAY_SEL2_VADDR,0x0);	// 1_80a4
#else
	// there is a vd_ifd_input bug according to read bus in the sirius 
	VD_IN_DELAY_SEL2_RBUS vd_in_delay_sel2_reg;	// 1_80a4
	vd_in_delay_sel2_reg.regValue = rtd_inl(FEin_VD_IN_DELAY_SEL2_VADDR);
	vd_in_delay_sel2_reg.sv_sel = 0;			// 1_80a4[3:2] ADC selection for S-Video ADC sharing = AD1 (actually dont care)
	vd_in_delay_sel2_reg.sv_yc_switch =0;	// 1_80a4[1] Y/C data Switch for S-Video ADC sharing = disable
	vd_in_delay_sel2_reg.sv_in_one_adc =0;	// 1_80a4[0] Enable S-Video Y/C ADC sharing = disable
	rtd_outl(FEin_VD_IN_DELAY_SEL2_VADDR,vd_in_delay_sel2_reg.regValue);	// 1_80a4
#endif
	
	rtd_outl(VDC_AD_SW_CTRL0_VADDR,ad_sw_ctrl0_reg.regValue);	// 1_9608
}

/**
     module_vdc_SetInput_YC
    if the input is the  s-video ,the function is setting the y and c path registers
    @param<SrcType> { uint8_t Y_path, uint8_t Y_Gnd_path, uint8_t C_path, uint8_t C_Gnd_path }
    @return { none }
    @ingroup dragon_video
*/
void module_vdc_SetInput_YC(UINT8 Y_path, UINT8 Y_Gnd_path, UINT8 C_path, UINT8 C_Gnd_path, UINT8 SV_Type)
{
	unsigned char Y_ADCselect, C_ADCselect;

	printk( "[VDC][Set Input YC][Y_path] %d, [Y_Gnd_path] %d\n", Y_path, Y_Gnd_path);
	Y_ADCselect = module_vdc_SetADCPath(Y_path, Y_Gnd_path);
//	udelay(10000);
	udelay(50);

	printk( "[VDC][Set Input YC][C_path] %d, [C_Gnd_path] %d\n", C_path, C_Gnd_path);
	C_ADCselect = module_vdc_SetADCPath(C_path, C_Gnd_path);
//	udelay(10000);
	udelay(50);

///// SV Mutual Settings /////
#if sirius_qc
#else
	VD_IN_DELAY_SEL2_RBUS vd_in_delay_sel2_reg;		// 1_80a4
	vd_in_delay_sel2_reg.regValue = rtd_inl(FEin_VD_IN_DELAY_SEL2_VADDR);
	VD_INOUT_CTRL_RBUS vd_inout_ctrl_reg;				// 1_80ac
	vd_inout_ctrl_reg.regValue = rtd_inl(FEin_VD_INOUT_CTRL_VADDR);
#endif
	VIDEO_CONTROL1_RBUS video_control1_reg;			// 1_9004
	video_control1_reg.regValue = rtd_inl(VDC_VIDEO_CONTROL1_VADDR);
	OUTPUT_CONTROL_RBUS output_control_reg;			// 1_907c
	output_control_reg.regValue = rtd_inl(VDC_OUTPUT_CONTROL_VADDR);
	INOUT_CTRL_RBUS inout_ctrl_reg;						// 1_9080
	inout_ctrl_reg.regValue = rtd_inl(VDC_INOUT_CTRL_VADDR);
	VIDEO_CONTROL2_RBUS video_control2_reg;			// 1_909c
	video_control2_reg.regValue = rtd_inl(VDC_VIDEO_CONTROL2_VADDR);
	AUTO_POS_CTRL_RBUS auto_pos_ctrl_reg;				// 1_94c0
	auto_pos_ctrl_reg.regValue = rtd_inl(VDC_AUTO_POS_CTRL_VADDR);
	AD_SW_CTRL0_RBUS ad_sw_ctrl0_reg;					// 1_9608
	ad_sw_ctrl0_reg.regValue = rtd_inl(VDC_AD_SW_CTRL0_VADDR);
	CLAMP_UPDN_EN_RBUS clamp_updn_en_reg;			// 1_960c
	clamp_updn_en_reg.regValue = rtd_inl(VDC_CLAMP_UPDN_EN_VADDR);
	CLAMP_RGB_UPDN_EN_RBUS clamp_rgb_updn_en_reg;	// 1_9610
	clamp_rgb_updn_en_reg.regValue = rtd_inl(VDC_CLAMP_RGB_UPDN_EN_VADDR);
	FSW_CTRL2_RBUS fsw_ctrl2_reg;						// 1_9620
	fsw_ctrl2_reg.regValue = rtd_inl(VDC_FSW_CTRL2_VADDR);
#if sirius_qc
#else
	MISC_CONTROL_RBUS misc_control_reg;				// 1_9764
	misc_control_reg.regValue = rtd_inl(VDC_MISC_CONTROL_VADDR);
#endif
	PATTERN_CONTROL_RBUS pattern_control_reg;			// 1_9794
	pattern_control_reg.regValue = rtd_inl(VDC_PATTERN_CONTROL_VADDR);
	ADC_UPDN_CTRL_RBUS adc_updn_ctrl_reg;				// 1_97fc
	adc_updn_ctrl_reg.regValue = rtd_inl(VDC_ADC_UPDN_CTRL_VADDR);
	adc_power_RBUS adc_power_reg;						// 2_0000
	adc_power_reg.regValue = rtd_inl(ADC_ADC_POWER_VADDR);
	adc_ctl_rgb12_RBUS adc_ctl_rgb12_reg;					// 2_0008
	adc_ctl_rgb12_reg.regValue = rtd_inl(ADC_ADC_CTL_RGB12_VADDR);
	adc_clock_RBUS adc_clock_reg;						// 2_0010
	adc_clock_reg.regValue = rtd_inl(ADC_ADC_CLOCK_VADDR);
	adc_clamp_ctrl1_RBUS adc_clamp_ctrl1_reg;				// 2_0020
	adc_clamp_ctrl1_reg.regValue = rtd_inl(ADC_ADC_CLAMP_CTRL1_VADDR);
	vd_adc_clamp_ctl_1_RBUS vd_adc_clamp_ctl_1_reg;		// 2_0048
	vd_adc_clamp_ctl_1_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR);
	vd_adc_clamp_ctl_2_RBUS vd_adc_clamp_ctl_2_reg;		// 2_004c
	vd_adc_clamp_ctl_2_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR);
	vd_adc_updn_ctl_RBUS	vd_adc_updn_ctl_reg;			// 2_0050
	vd_adc_updn_ctl_reg.regValue = rtd_inl(ADC_VD_ADC_UPDN_CTL_VADDR);
	vdadc_core_lpf_ctrl_RBUS vdadc_core_lpf_ctrl_reg;		// 2_0054
	vdadc_core_lpf_ctrl_reg.regValue = rtd_inl(ADC_VDADC_CORE_LPF_CTRL_VADDR);
	vdadc_ck_ctl_RBUS vdadc_ck_ctl_reg;					// 2_0058
	vdadc_ck_ctl_reg.regValue = rtd_inl(ADC_VDADC_CK_CTL_VADDR);

	rtd_maskl(0xb8020048,0xffff1fff,0x00000000); //disable dc resotre

	adc_clamp_ctrl1_reg.adc_clamp_ctrl4_4_0 = 0x04;	// 2_0020[20:16] UP/DN CLAMP current=20uA*[3:0] [4]: Resistor R=6K/2K, Voltage=0.825V, for YC Mix(0: Open, 1: Short)
	//vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_7_3 = (_BIT2 | _BIT1);	// 2_0050[7:3] CLAMP current=20uA*[3:0][4]: Resistor R=6K/2K, Voltage=0.825V, for YC Mix (0: Open, 1: Short)
	
	if(SV_Type == VIDEO_SV_SWAP)	// Y/C swap
	{
		printk("[VDC][SV][Path Select] Using YC swap!!\n");	//Y_path only from VIN9P,VIN10P
//// Y/C swap 54MHz domain ////
		//drvif_module_Set_VD_pll27x_54M_CLK(1);	// 54M clock enable
//		yc swap power on
//		adc_power_reg.adc_power_11 = 1;	// 2_0000[11] VDC Channel ADC Input YC Swap for S-Video, for YC Swap
//		adc_power_reg.adc_power_10 = 1;	// 2_0000[10] VDC Channel 2nd 1st-LPF Power On, Always Select VIN11PP,  for YC Swap

//// enable Y/C swap ////
		#if sirius_qc
		rtd_outl(FEin_VD_IN_DELAY_SEL2_VADDR,0x0000000F);
		#else
		vd_in_delay_sel2_reg.sv_sel = 0x03;		// 1_80a4[3:2] ADC selection for S-Video ADC sharing = AD4
		vd_in_delay_sel2_reg.sv_yc_switch = 1;	// 1_80a4[1] Y/C data Switch for S-Video ADC sharing = enable
		vd_in_delay_sel2_reg.sv_in_one_adc = 1;	// 1_80a4[0] Enable S-Video Y/C ADC sharing = enable
		#endif
		vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_5 = 1;	// 2_004c[5] YC Swap for S-Video YC Swap (0: Disable YC Swap, 1: Enable YC Swap)

		#if 0 //jacky_adc
		//vdadc_core_lpf_ctrl_reg.vdadc_lpf_ctrl_6 = 1;	// 2_0054[6] LPF2 Power(for YC-swap) = 0: Power down , 1:Power on 
		#endif
//// set ClampType for Y/C swap ////
//		rtd_outl(0xb8019608,0x00000010);		// select sv path (often sets C9 or 1B, U40 sets 15)			// AD_SW_CTRL0
//		ad_sw_ctrl0_reg.regValue = 0x10;		// 1_9608 set VD AD switch for Y/C swap	// Mark done
		ad_sw_ctrl0_reg.sw_comp = 0x0;	// 1_9608[7:6] set VD Y AD switch = ad1 (swap, special case)
		ad_sw_ctrl0_reg.sw_pr_r = 0x1;	// 1_9608[5:4] set VD C AD switch = ad2 (swap, special case)
//		rtd_outl(0xb801960C,0x00000008);		// set sv (U40 sets 0x08)					// CLAMP_UPDN_EN
		clamp_updn_en_reg.clamp_ad3 = AD_CorRorPr;	// 1_960c[3:2] clamp selection for AD_3 part = 10: CorRorPr
		clamp_updn_en_reg.clamp_ad4 = AD_YorCVBS;	// 1_960c[1:0] clamp selection for AD_4 part = 00: YorCVBS
//		rtd_outl(0xb8019610,0x000000FF);			// enable clamp up/dn					// CLAMP_RGB_UPDN_EN
//		clamp_rgb_updn_en_reg.regValue = 0x0f;		// Mark done by ClampType
		clamp_rgb_updn_en_reg.clamp_c_up_en = 1;	// 1_9610[3] enable VD3 clamp up
		clamp_rgb_updn_en_reg.clamp_c_dn_en = 1;	// 1_9610[2] enable VD3 clamp dn
		clamp_rgb_updn_en_reg.clamp_d_up_en = 1;	// 1_9610[1] enable VD4 clamp up
		clamp_rgb_updn_en_reg.clamp_d_dn_en = 1;	// 1_9610[0] enable VD4 clamp dn
//		adc_ctl_rgb12_reg.adc_ctl_rgb2_15_13 = 0x00;	// 2_0008[31:29] V Channel UP/DN Swap for YC, for YC Mix = 000
		vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_12_10 = 0x05;	// 2_0048[28:26] BIT [ 12:10 ] : V Channel UP/DN Swap for YC, for YC Mix = VIN11PP~VIN9PP UP/DN Swap (0: UP[3]/DN[3], 1: UP[2]/DN[2])
#if sirius_qc
#else
		if(Y_path == VIDEO_INPUT10)	// QA board connector: Y_path is VIDEO_INPUT10; C_path is VIDEO_INPUT13
		{
//			set 2_0008[31:29] V Channel UP/DN Swap for YC, for YC Mix = 100;
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_12_10 = 0x05;	// 2_0048[28:26] BIT [ 12:10 ] : V Channel UP/DN Swap for YC, for YC Mix = VIN11PP~VIN9PP UP/DN Swap (0: UP[3]/DN[3], 1: UP[2]/DN[2]); VIN11PP updn come from AD3; VIN10P updn come from AD2
//			set 2_0008[7:6] V Channel 1st 2nd LPF Input+ Select, for YC Mix = 00: VIN9PP
//			adc_ctl_rgb12_reg.adc_ctl_rgb1_7_6 = 0x00;	// 2_0008[7:6] V Channel 1st 2nd LPF Input+ Select, for YC Mix = 00
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_9_8 = 0x01;	// 2_0048[25:24] V Channel 1st 2nd LPF Input+ Select, for YC Mix = VIN10P
//			printk("[QC][VDC][YC] Y through VIN10P, 0048[28:26] = %x, 0048[25:24] = %x\n", vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_12_10, vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_9_8);
		}
		else		// no other case on QA board
		{
//			seems can't use YC swap in case Y9P, C8P
//			set [31:29] = 100, [7:6] = 01
//[Mark]		adc_ctl_rgb12_reg.adc_ctl_rgb1_7_6 = 0x01;	// 2_0008 [7:6] = 01
		}
#endif
		rtd_outl(VDC_CLAMP_UPDN_EN_VADDR, clamp_updn_en_reg.regValue);				// 1_960c
		rtd_outl(VDC_CLAMP_RGB_UPDN_EN_VADDR, clamp_rgb_updn_en_reg.regValue);	// 1_9610
//		udelay(2000);
		udelay(50);
	}
	else		// Y/C not swap
	{

//		rtd_outl(0xb8019608,0x000000E0);		// [7:6] 11:ADC_V; [5:4] 10:ADC_R; select Y path		// AD_SW_CTRL0
//		rtd_outl(0xb801960C,0x00000008);		// [3:2] AD3 = 10:C/R/Pr; [1:0] AD4 = 00:Y/CVBS; set Y		// CLAMP_UPDN_EN
		///// VD ADC /////

//		rtd_outl(0xb8020004,0x00004002);		// U/D clamp current select: normal				// ADC_IBIAS0123
//		rtd_outl(0xb8020008,0x00200E20);		// R Channel Input+ Select GND; Input- Select Y1N		// ADC_CTL_RGB12
//		rtd_outl(0xb802000C,0x0103081C);		// default: VRT/VRB swing select: x1;  Gain select:0.8v 		// ADC_VBIAS

//		rtd_outl(0xb8020010,0x00000401);		// Selet clk => VDC	, PLL27X(RGB), 50% duty			// ADC_CLOCK
		adc_clock_reg.adc_clock_10 = 1;			// 2_0010[10] RGB/YPP Channel Clock Source = 0: APLL; 1: PLL27X

//		rtd_outl(0xb8020018,0x00190000);		// RGB/YPP 2nd LPF Bandwidth = 400M, disable all DC restore	// ADC_DCRESTORE_CTRL
//		rtd_outl(0xb802001C,0x00400000);		// disable R8N, G4N, B0N clamp				// ADC_CLAMP_CTRL0 
//		rtd_outl(0xb8020020,0x00840000);		// disable all Input+ clamp; en R8N, disable G4N, B0N up/dn	// ADC_CLAMP_CTRL1 
//		rtd_outl(0xb8020024,0x44200100);		// enable R2(VIN_8P) VDC up/dn				// ADC_CLAMP_CTRL2

		rtd_outl(0xb8020028,0x00000000);		// disable all N_clamp up/dn					// ADC_CLAMP_CTRL3 
		rtd_outl(0xb8020048,0x00670200);		// A0N, 2nd LPF input = VIN9P; VOFFSET 4b-DAC ~= 0.65V	// VD_ADC_CLAMP_CTL_1
		rtd_outl(0xb802004C,0x00000440);		// [10] VD analog ADC path = VIN9PP; [5] disable YC swap	// VD_ADC_CLAMP_CTL_2
		rtd_outl(0xb8020050,0x00000121);		// A0N UP/DN Nclamp, V0 UP/DN clamp			// VD_ADC_UPDN_CTL
		rtd_outl(0xb8020054,0x22880003);		// SHA Gain, VRT/VRB Gain, LPF Gain			// VDADC_CORE_LPF_CTRL (same setting as U40 test chip)
		rtd_outl(0xb8020058,0x00008940);		// en PLL27X_CK54M; select VDC Channel Clock Source		// VDADC_CK_CTL
//		udelay(4000);
		udelay(50);

		printk("[VDC][SV][Path Select] Not using YC swap!!\n");
//// Y/C seperate 108MHz domain ////
#if sirius_qc
#else
		drvif_module_Set_VD_pll27x_54M_CLK(0);	// 0_04dc[12] PLL27x YPPADC 54MHz clock enable, used by SCART
#endif
//		yc swap power off
//		adc_power_reg.adc_power_11 = 0;	// 2_0000[11] VDC Channel ADC Input YC Swap for S-Video, for YC Swap
//		adc_power_reg.adc_power_10 = 0;	// 2_0000[10] VDC Channel 2nd 1st-LPF Power On, Always Select VIN11PP,  for YC Swap

//// disable Y/C swap ////
//		rtd_outl(0xb80180A4,0x00000000);		// disable sv_yc_switch					// VD_IN_DELAY_SEL2
#if sirius_qc
		rtd_outl(FEin_VD_IN_DELAY_SEL2_VADDR,0x00000000);
#else
		vd_in_delay_sel2_reg.sv_sel = 0x00;		// 1_80a4[3:2] ADC selection for S-Video ADC sharing = AD1(default)
		vd_in_delay_sel2_reg.sv_yc_switch = 0;	// 1_80a4[1] Y/C data Switch for S-Video ADC sharing = disable
		vd_in_delay_sel2_reg.sv_in_one_adc = 0;	// 1_80a4[0] Enable S-Video Y/C ADC sharing = disable
#endif
		vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_5 = 0;	// 2_004c[5] YC Swap for S-Video YC Swap (0: Disable YC Swap, 1: Enable YC Swap)
		#if 0 //jacky_adc
		vdadc_core_lpf_ctrl_reg.vdadc_lpf_ctrl_6 = 0;	// 2_0054[6] LPF2 Power(for YC-swap) = 0: Power down , 1:Power on 
		#endif
//// set ClampType for Y/C seperate ////
		ad_sw_ctrl0_reg.sw_comp = Y_ADCselect;	// 1_9608[7:6] set VD Y AD switch
		ad_sw_ctrl0_reg.sw_pr_r = C_ADCselect;	// 1_9608[5:4] set VD C AD switch
		module_vdc_ClampType_set(AD_YorCVBS, Y_ADCselect);		// set Y
		module_vdc_ClampType_set(AD_CorRorPr, C_ADCselect);		// set C
// 		adc_dcrestore_ctrl_reg.adc_ctl_rgb_7_4 = 0x03;	// set RGB SH gain = 1.1 for SV only
	}
//	adc_dcrestore_ctrl_reg.adc_ctl_rgb_15_12 = 0x03;	// set V-ch SH gain = 1.1 for SV only
//	adc_dcrestore_ctrl_reg.adc_ctl_rgb_10_8 = 0x00;	// set LPF = 10M
//	clamp_rgb_updn_en_reg.regValue = 0xff;	// 1_9610 enable cleamp up/dn

#if 1	// 2013.03/07 Mark debug: choose which we need in fw SV path selection
//	rtd_outl(0xb80180AC,0x00000030);		// [6:4] decimation filter: ADC run @ 27MHz mode select = 0: data from DF; 1: direct from ADC(by pass)	// VD_INOUT_CTRL
#if sirius_qc
	rtd_outl(FEin_VD_INOUT_CTRL_VADDR,0x00000030);
#else
	vd_inout_ctrl_reg.adc27_mod = 0x03;	// 1_80ac[6:4] Front-end ADC decimation filter BW select = 011: 6.5MHz
	vd_inout_ctrl_reg.adc27_mod = 0;	// 1_80ac[0] ADC run @ 27MHz mode select = 0: data from DF; 1: direct from ADC(by pass)
#endif
///// VD /////
//	rtd_outl(0xb8019004,0x00000000);		// 1_9004[5] selects input video format = 1: S-Video (separated Y/C)	// VIDEO_CONTROL1
	video_control1_reg.yc_src = 1;			// 1_9004[5] selects input video format = 1: S-Video (separated Y/C)	// VIDEO_CONTROL1
//	rtd_outl(0xb8019080,0x00000000);		// decimation filter has been changed				// INOUT_CTRL
	inout_ctrl_reg.avout_hsync_end = 0x00;	// 1_9080[17:8] Avout_hsync low setting
	inout_ctrl_reg.fe_bypass_sel = 0;			// 1_9080[4] Front-end digital filter bypass delay select = 0: bypass without delay
	inout_ctrl_reg.sw_tu_cvbs = 0;			// 1_9080[3] Switch for Tuner CVBS and Clamping Data = 0: Data comes from ADC and clamping up/dn goes to ADC

//	rtd_outl(0xb801909c,0x00000047);		// set bgate_raw_sel enable					// VIDEO_CONTROL2
	video_control2_reg.dc_clamp_mode = 0x00;	// 1_909c[5:4] sets the mode for analog front end DC clamping = 11: off; 00: auto; use backporch when a signal exists; use synctip if no signal exists
	video_control2_reg.bgate_raw_sel = 1;	// 1_909c[2] Control vd_bgate_raw as clamping pulse for ADC = 0: default; 1: always high
	video_control2_reg.cagc_en= 1;			// 1_909c[1] enables the chroma AGC. If disabled, then the cagc value is used to drive directly the AGC gain.(Can be controlled manually only when Hagcreg_en is disabled.) = 1
	video_control2_reg.hagc_en= 1;			// 1_909c[0] enables the luma/composite AGC. If disabled, then the hagc value is used to drive directly the digital gain.(Can be controlled manually only when Hagcreg_en is disabled.) = 1

//	rtd_outl(0xb8019620,0x00000108);		// set VDC 444 output					// FSW_CTRL2
	fsw_ctrl2_reg.scart_en = 0;				// 1_9620[7] enable SCART function = 0
	fsw_ctrl2_reg.out444_sel = 1;			// 1_9620[3] 4:4:4 output select = 1: 4:4:4 output; 0: 4:2:2 output

// 2013.03/08 start
//	rtd_outl(0xb8019764,0x0008017F);		// bit[9:8]=01, select Select the VCO freq = 540M			// MISC_CONTROL
#if sirius_qc
	rtd_outl(VDC_MISC_CONTROL_VADDR,0x0008007F);		// bit[9:8]=00, select Select the VCO freq = 432M
#else
	misc_control_reg.swallow_freq_sel = 0x01;	// 1_9764[9:8] Select the VCO freq = 1:540Mhz
#endif
#if 0
	misc_control_reg.swallow_on_vsync = 0;	// 1_9764[7] limit the swallow circuit actions only during V-sync blanking region = 0
	misc_control_reg.ndivload_en = 1;	// 1_9764[6] phase swallow divider load control enable = 1
	misc_control_reg.ps_up_en = 1;	// 1_9764[5] phase swallow up control enable = 1
	misc_control_reg.ps_dn_en = 1;	// 1_9764[4] phase swallow down control enable = 1
	misc_control_reg.pll_div = 0x0f;	// 1_9764[3:0] set the divider parameter, range from 0 to 15 (2^0 to 2^15) = 0x0f
#endif
//	rtd_outl(0xb8019794,0x00000000);		// disable pattern generator					// PATTERN_CONTROL
#if 1
	pattern_control_reg.pattern_generator_enable = 0;	// 1_9794[0] enable the pattern generator
#endif
//	rtd_outl(0xb80197FC,0x00000000);		// Disable clamp test mode					// ADC_UPDN_CTRL
#if 1
	adc_updn_ctrl_reg.adc_updn_debug_en = 0;	// 1_97fc[2] Debug ADC clamp up/dn control enable = 0, in case someone turn it on
	adc_updn_ctrl_reg.adc_updn_debug_up = 0;	// 1_97fc[1] ADC clamp up enable = 0, in case someone turn it on
	adc_updn_ctrl_reg.adc_updn_debug_dn = 0;	// 1_97fc[0] ADC clamp down enable = 0, in case someone turn it on
#endif

///// U40 設定 /////
// VDADC VIN10P, VIN13P
//	rtd_outl(0xb8020010,0x00000401);		// clk from PLL27X
//	rtd_outl(0xb8020048,0x89770C01);		// BU setting
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_8 = 0;		// 2_0048[8] VDC Channel Single Ended or Diff, Input = 0: Single Ended; 1: Diff
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_1_0 = 0x00;	// 2_0048[1:0] input2/1/0(VIN11P-VIN0P) DC restore resister = 00:open; 01:500k; 10:1M; 11:5M
//	rtd_outl(0xb802004c,0x00000270);		// BU setting
//	rtd_outl(0xb8020050,0x00000436);		// BU setting
//	rtd_outl(0xb8020054,0x22900046);		// [5:4] 00: 4.5Kohms (darker); [2:0] 011:10.57M (default)
//	rtd_outl(0xb8020058,0x00008940);		// BU setting

// VDC input setting
//	rtd_outl(0xb80180A4,0x0000000F);		// enable sv_yc_switch, sharing through AD4 for yc swap		// VD_IN_DELAY_SEL2
//	rtd_outl(0xb8019608,0x00000010);		// select sv path (often sets C9 or 1B, U40 sets 15)			// AD_SW_CTRL0
//	rtd_outl(0xb801960C,0x00000008);		// set sv (U40 sets 0x08)					// CLAMP_UPDN_EN
//	rtd_outl(0xb8019610,0x000000FF);		// enable clamp up/dn					// CLAMP_RGB_UPDN_EN
//	rtd_outl(0xb8019004,0x00000020);		// set sv							// VIDEO_CONTROL1

//	rtd_outl(0xb801907c,0x00000087);		// set yc_delay						// OUTPUT_CONTROL
	output_control_reg.blue_mode = 0x02;	// 1_907c[5:4] controls the blue screen mode = 00: disable; 01: enabled; 10: auto; 11: reserved
	output_control_reg.yc_delay = 0x07;		// 1_907c[2:0] 2's complement number controls the output delay between luma and chroma, The range is [-5,7] = 0x07
//	rtd_outl(0xb801916C,0x00000000);		// H sync start; list here in case we need it			// HSYNC_PULSE_START
//	rtd_outl(0xb80194c0,0x00000000);		// new yc_delay for NTSC M					// AUTO_POS_CTRL
	auto_pos_ctrl_reg.new_cr1delay_en = 0;	// 1_94c0[30] New cr delay enable = 0
	auto_pos_ctrl_reg.new_cb1delay_en = 0;	// 1_94c0[29] New cb delay enable = 0
	auto_pos_ctrl_reg.new_y1delay_en = 0;	// 1_94c0[28] New y delay enable = 0
//	rtd_outl(0xb8019900,0x00000000);		// set 1/2/3D; list here in case we need it				// YC_SEP_CONTROL
//	udelay(2000);
	udelay(50);
#endif

#if sirius_qc
#else
	rtd_outl(FEin_VD_IN_DELAY_SEL2_VADDR, vd_in_delay_sel2_reg.regValue);		// 1_80a4
	rtd_outl(FEin_VD_INOUT_CTRL_VADDR, vd_inout_ctrl_reg.regValue);				// 1_80ac
#endif
	rtd_outl(VDC_VIDEO_CONTROL1_VADDR, video_control1_reg.regValue);			// 1_9004
	rtd_outl(VDC_OUTPUT_CONTROL_VADDR, output_control_reg.regValue);			// 1_907c
	rtd_outl(VDC_INOUT_CTRL_VADDR, inout_ctrl_reg.regValue);					// 1_9080
	rtd_outl(VDC_VIDEO_CONTROL2_VADDR, video_control2_reg.regValue);			// 1_909c
	rtd_outl(VDC_AUTO_POS_CTRL_VADDR, auto_pos_ctrl_reg.regValue);				// 1_94c0
	rtd_outl(VDC_AD_SW_CTRL0_VADDR, ad_sw_ctrl0_reg.regValue);				// 1_9608
	rtd_outl(VDC_FSW_CTRL2_VADDR, fsw_ctrl2_reg.regValue);						// 1_9620
#if sirius_qc
#else
	rtd_outl(VDC_MISC_CONTROL_VADDR, misc_control_reg.regValue);				// 1_9764
#endif
	rtd_outl(VDC_PATTERN_CONTROL_VADDR, pattern_control_reg.regValue);			// 1_9794
	rtd_outl(VDC_ADC_UPDN_CTRL_VADDR, adc_updn_ctrl_reg.regValue);			// 1_97fc
	rtd_outl(ADC_ADC_POWER_VADDR, adc_power_reg.regValue);					// 2_0000
	rtd_outl(ADC_ADC_CTL_RGB12_VADDR, adc_ctl_rgb12_reg.regValue);				// 2_0008
	rtd_outl(ADC_ADC_CLOCK_VADDR, adc_clock_reg.regValue);					// 2_0010
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_1_VADDR, vd_adc_clamp_ctl_1_reg.regValue);	// 2_0048
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_2_VADDR, vd_adc_clamp_ctl_2_reg.regValue);	// 2_004c
	rtd_outl(ADC_VD_ADC_UPDN_CTL_VADDR, vd_adc_updn_ctl_reg.regValue);		// 2_0050
	rtd_outl(ADC_VDADC_CORE_LPF_CTRL_VADDR, vdadc_core_lpf_ctrl_reg.regValue);	// 2_0054
	rtd_outl(ADC_VDADC_CK_CTL_VADDR, vdadc_ck_ctl_reg.regValue);				// 2_0058
//	udelay(4000);
	udelay(50);
//#include "case13_CVBS_VIN9_fs_fhd/SV_Y10P_C13P.tbl"
//#include "case13_CVBS_VIN9_fs_fhd/SV_Y9P_C8P.tbl"
}

bool module_vdc_Test_Mode(UINT8 AV_mode)
{
	UINT32 i, j;
	UINT8 mode_check ;
	
#if 0	// debug
	printk("[QC][VD][Mode Test] av_mode = %x	rtd_inl(0x%x) = 0x%08x\n", AV_mode, VDC_MODE_DETECTION_STATUS_VADDR, rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR));
#endif

#if 1
	for(i=0; i<30000; i++)
	{
		mode_check = ((UINT8)rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR) & 0x0f);
		udelay(200);
		if(mode_check == AV_mode)
		{
			printk("[QC][VD][Mode Test] Supposed input mode = %x, detected value => %x \n, test success!\n", AV_mode, mode_check);
			printk("[QC][VD][Mode Test] Success occurs at i = %d\n", i);
			break;
		}
	}

	for(i=0; i<5000; i++)	// make some delay to make sure it can distinguish NTSC and other mode, this is necessary delay
	{
		udelay(100);
	}
	
	mode_check = ((UINT8)rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR) & 0x0f);
	udelay(50);

#if 0	// 20130510 Mark: use this becuase the 443358 flag is not done well in Magellan Ver.A ====
	if((AV_mode == _PALI)&(mode_check == _NTSC50))
	{
		AV_mode = _PALI;
	}
	else if((AV_mode == _NTSC)&(mode_check == _NTSC443))
	{
		AV_mode = _NTSC;
	}
	else
	{}
	// ==========================================================
#endif
	
	if(mode_check != AV_mode)
	{
			printk("[QC][VD][Mode Test] Supposed input mode = %x, detected value => %x \n, test fail!\n", AV_mode, mode_check);
		return _FAIL;
	}
	else
	{
			printk("[QC][VD][Mode Test] Supposed input mode = %x, detected value => %x \n, test success!\n", AV_mode, mode_check);
	}
#endif
	return _SUCCESS;
}

bool module_vdc_Test_YC_Path(UINT8 Y_path, UINT8 Y_Gnd_path, UINT8 C_path, UINT8 C_Gnd_path, UINT8 SV_Type)
{
	UINT32 i, j;
	UINT8  no_signal;
	UINT8  mode_check;

	MANUAL_MODE_RBUS manual_mode_reg;	// 1_94a0
	manual_mode_reg.regValue = rtd_inl(VDC_MANUAL_MODE_VADDR);
	MODE_DETECTION_STATUS_RBUS mode_detection_status_reg;	// 1_94a4
	mode_detection_status_reg.regValue = rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR);
	AUTOMODE_443358PK_CTRL_RBUS automode_443358pk_ctrl_reg;	// 1_957c
	automode_443358pk_ctrl_reg.regValue = rtd_inl(VDC_AUTOMODE_443358PK_CTRL_VADDR);
	PATTERN_CONTROL_RBUS pattern_control_reg;	// 1_9794
	pattern_control_reg.regValue = rtd_inl(VDC_PATTERN_CONTROL_VADDR);

	manual_mode_reg.auto_mode_en = 1;	// 1_94a0[7] Auto mode detection enable register. When bit6 is 0, reference to this bit = 1: enable. Use auto mode; 0: disable. Use manual mode
	manual_mode_reg.state_machine_reset = 1;	// 1_94a0[3] Reset auto mode state machine = 1 : reset; 0 : normal
	manual_mode_reg.state_machine_reset = 0;	// 1_94a0[3] Reset auto mode state machine = 1 : reset; 0 : normal
	automode_443358pk_ctrl_reg.mode_443358pk_sel = 1;	// 1_957c[1:0] = 0, use new 443358 flag for debug
//	automode_443358pk_ctrl_reg.mode_443358pk_sel = 0;	// 1_957c[1:0] = 0, use old 443358 flag, new one is failed
	pattern_control_reg.pattern_generator_enable = 0;	// 1_9794[0] disable the pattern generator

	rtd_outl(VDC_AD_SW_CTRL0_VADDR, manual_mode_reg.regValue);	// 1_94a0
	rtd_outl(VDC_AD_SW_CTRL0_VADDR, mode_detection_status_reg.regValue);	// 1_94a4
	rtd_outl(VDC_AUTOMODE_443358PK_CTRL_VADDR, automode_443358pk_ctrl_reg.regValue);	// 1_957c
	rtd_outl(VDC_PATTERN_CONTROL_VADDR, pattern_control_reg.regValue);	// 1_9794
	udelay(3000);

	module_vdc_SetInput_YC(Y_path, Y_Gnd_path, C_path, C_Gnd_path, SV_Type);

	//fix the yc 2nd order mux setting
	vd_adc_clamp_ctl_1_RBUS vd_adc_clamp_ctl_1_reg;	// 2_0048
	vd_adc_clamp_ctl_1_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR);
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_10_9 = 0x1;//BIT [10:9]: V Channel Input+ Select 00: Select VIN9PP 01: Select VIN10P 10: Select VIN11PP
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_1_VADDR, vd_adc_clamp_ctl_1_reg.regValue);	// 2_0048
	rtd_maskl(0xb8020058,0xFFFFFF9F,0x00000060);//[6] = 1 108M: positive [5] = 1 54M: positive
	rtd_maskl(0xb8020058,0xFFFFFFFC,0x00000000);//[1:0] = 0 the default should be X1 multiple

	udelay(3000);
	/*
	for(i=0; i<20000; i++)
 	{
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(200);
		if (no_signal == 0xe)
		{
			printk("[QC][VD][YC test][path = %x / %x] %d = %x\n", Y_path, C_path, i, no_signal);
			break;
		}
	}
	*/
	printk("\n");
	printk("0x%x:\t%x\n",ADC_VD_ADC_CLAMP_CTL_1_VADDR,rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR));//0048
	printk("0x%x:\t%x\n",ADC_VD_ADC_CLAMP_CTL_2_VADDR,rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR));//004c
	printk("0x%x:\t%x\n",ADC_VD_ADC_UPDN_CTL_VADDR,rtd_inl(ADC_VD_ADC_UPDN_CTL_VADDR));//0050
	printk("0x%x:\t%x\n",ADC_VDADC_CORE_LPF_CTRL_VADDR,rtd_inl(ADC_VDADC_CORE_LPF_CTRL_VADDR));//0054
	printk("0x%x:\t%x\n",ADC_VDADC_CK_CTL_VADDR,rtd_inl(ADC_VDADC_CK_CTL_VADDR));//0058
	printk("0x%x:\t%x\n",ADC_VDADC_POW_CTL_VADDR,rtd_inl(ADC_VDADC_POW_CTL_VADDR));//005c


  	for(i=0; i<1000; i++)
 	{
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(50);
		if (no_signal == 0xe)
		{
			printk("[QC][VD][YC test][path = %d / %d] no_signal = %x @ %d \n", Y_path, C_path, no_signal, i);
			break;
		}
		else if(i == 99)
		{
			printk("[QC][VD][YC test][path = %d / %d] no_signal = %x @ %d \n", Y_path, C_path, no_signal, i);
		}
		else
		{}
	}

#if 0
  	for(i=0; i<30000; i++)
 	{
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(500);
		if (no_signal == 0xe)
		{
			printk("[QC][VD][YC test][path = %x / %x] no_signal = %x @ %d \n", Y_path, C_path, no_signal, i);
			break;
		}
		else if(i == 9999)
		{
			printk("[QC][VD][YC test][path = %x / %x] no_signal = %x @ %d \n", Y_path, C_path, no_signal, i);
		}
	}

  	for(i=0; i<10000; i++)
 	{
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(500);
		if (no_signal == 0xe)
		{
			printk("[QC][VD][YC test][path = %x / %x] no_signal = %x @ %d \n", Y_path, C_path, no_signal, i);
			break;
		}
		else if(i == 9999)
		{
			printk("[QC][VD][YC test][path = %x / %x] no_signal = %x @ %d \n", Y_path, C_path, no_signal, i);
		}
	}
#endif

  	if (no_signal == 0x00)
	{
		printk("[QC][VD][SV] crystal does not work! the signal is %x\n", no_signal);
		return _FAIL;
	}
  	else if (no_signal == 0x01)
	{
		printk("[QC][VD][SV] no signal = %x, fail!\n", no_signal);
		return _FAIL;
	}	
	else if (no_signal == 0xe)
	{
		printk("[QC][VD][SV] vd test input SV0 is OK with y path vin%dp.no_signal = %x\n", Y_path, no_signal);
		return _SUCCESS;
	}
	else 
	{
		printk("[QC][VD][AV] vd test input SV0 is fail, the signal value==>%x \n", Y_path, no_signal);
		return _FAIL;
	}
	return _SUCCESS;
}

bool module_vdc_Test_Y_Path(UINT8 Y_path, UINT8 Gnd_path)
{
	UINT32 i, j;
	UINT8  no_signal;
	UINT8  mode_check;
	#if 1
	module_vdc_SetInput_Y(Y_path,Gnd_path);
	#endif
#if 0
	///// VDBS LDO power setting
	rtd_outl(0xb8033004,0x00000111);		// [8] power control of VDBS buffer; [4] power control of line driver	// VDAC_POW	(VDACIFADC_AIF_TOP.doc)
//	rtd_outl(0xb8033004,0x00001011);		// [12] power control of  VDAC; [4] power control of line driver	// VDAC_POW	(VDACIFADC_AIF_TOP.doc)
	#if sirius_qc//jacky
	AVOUT_FIFO_STATUS_RBUS AVOUT_FIFO_STATUS_reg;
	AVOUT_FIFO_STATUS_reg.regValue = rtd_inl(VDC_AVOUT_FIFO_STATUS_VADDR);
	AVOUT_FIFO_STATUS_reg.regValue = 0x0;
	rtd_outl(VDC_AVOUT_FIFO_STATUS_VADDR,AVOUT_FIFO_STATUS_reg.regValue);		// [8:5] avout_mixer_sel = 0000: Clamped CVBS data without fe_fil and agc	// AVOUT_FIFO_STATUS
	#else
	rtd_outl(0xb8019084,0x00000000);		// [8:5] avout_mixer_sel = 0000: Clamped CVBS data without fe_fil and agc	// AVOUT_FIFO_STATUS
	#endif
	udelay(3000);

	///// VDADC & VD setting
	#if Test_Y_Path //jacky
	//ADC POWER ON SETTING
	adc_power_RBUS adc_power_reg;
	adc_power_reg.regValue = rtd_inl(ADC_ADC_POWER_VADDR);
	adc_power_reg.adc_power_0 = 0x1;//Blue Channel ADC Power On
	adc_power_reg.adc_power_1 = 0x1;//Green Channel ADC Power On
	adc_power_reg.adc_power_2 = 0x1;//Red Channel ADC Power On
	adc_power_reg.adc_power_3 = 0x1;//ADC Bandgap Power On
	adc_power_reg.adc_power_4 = 0x1;//SOG1 Power On
	adc_power_reg.adc_power_5 = 0x1;//SOG0 Power On
	adc_power_reg.adc_power_6 = 0x1;//ADC clock Power On
	adc_power_reg.adc_power_7 = 0x1;//Online Auto_SOY ADC Clock Power On
	rtd_outl(ADC_ADC_POWER_VADDR,adc_power_reg.regValue);				// 2_0000 ADC power on
	vdadc_pow_ctl_RBUS vdadc_pow_ctl_reg;
	vdadc_pow_ctl_reg.regValue = rtd_inl(ADC_VDADC_POW_CTL_VADDR);
	vdadc_pow_ctl_reg.vdadc_pow = 0x1;
	vdadc_pow_ctl_reg.ldo100ma_pow = 0x1;
	rtd_outl(ADC_VDADC_POW_CTL_VADDR,vdadc_pow_ctl_reg.regValue);			// 2_005c VDADC power on
	VD_IN_DELAY_SEL2_RBUS VD_IN_DELAY_SEL2_reg;
	VD_IN_DELAY_SEL2_reg.regValue = rtd_inl(FEin_VD_IN_DELAY_SEL2_VADDR);
	VD_IN_DELAY_SEL2_reg.regValue = 0x0;
	rtd_outl(FEin_VD_IN_DELAY_SEL2_VADDR,VD_IN_DELAY_SEL2_reg.regValue); // 1_9794 disable yc swap ???
	PATTERN_CONTROL_RBUS PATTERN_CONTROL_reg;
	PATTERN_CONTROL_reg.regValue = rtd_inl(VDC_PATTERN_CONTROL_VADDR);
	PATTERN_CONTROL_reg.regValue = 0x0;
	rtd_outl(VDC_PATTERN_CONTROL_VADDR,PATTERN_CONTROL_reg.regValue);		// disable pattern generator
	rtd_outl(ADC_ADC_CLOCK_VADDR, 0x00000401);				// Selet clk => VDC
	rtd_outl(ADC_ADC_CTL_RGB12_VADDR, 0x0015A02A);			// Selet VIN6P,VIN7P,VIN8P,VIN_Y0N;[12]Gain=0.5
	rtd_outl(ADC_ADC_DCRESTORE_CTRL_VADDR, 0x18180000);	//disable dc restore, select BPF=10M
	CLAMP_UPDN_EN_RBUS CLAMP_UPDN_EN_reg;
	CLAMP_UPDN_EN_reg.regValue = rtd_inl(VDC_CLAMP_UPDN_EN_VADDR);
	CLAMP_UPDN_EN_reg.regValue = 0x0;
	rtd_outl(VDC_CLAMP_UPDN_EN_VADDR, CLAMP_UPDN_EN_reg.regValue );			// set Y
	CLAMP_RGB_UPDN_EN_RBUS CLAMP_RGB_UPDN_EN_reg;
	CLAMP_RGB_UPDN_EN_reg.regValue = rtd_inl(VDC_CLAMP_RGB_UPDN_EN_VADDR);
	CLAMP_RGB_UPDN_EN_reg.clamp_d_dn_en = 0x1;
	CLAMP_RGB_UPDN_EN_reg.clamp_d_up_en = 0x1;
	CLAMP_RGB_UPDN_EN_reg.clamp_c_dn_en = 0x1;
	CLAMP_RGB_UPDN_EN_reg.clamp_c_up_en = 0x1;
	CLAMP_RGB_UPDN_EN_reg.clamp_b_dn_en = 0x1;
	CLAMP_RGB_UPDN_EN_reg.clamp_b_up_en = 0x1;
	CLAMP_RGB_UPDN_EN_reg.clamp_a_dn_en = 0x1;
	CLAMP_RGB_UPDN_EN_reg.clamp_a_up_en = 0x1;
	rtd_outl(VDC_CLAMP_RGB_UPDN_EN_VADDR,CLAMP_RGB_UPDN_EN_reg.regValue);		// 1_9610 enable clamp up/dn
	VIDEO_CONTROL1_RBUS VIDEO_CONTROL1_reg;
	VIDEO_CONTROL1_reg.regValue = rtd_inl(VDC_VIDEO_CONTROL1_VADDR);
	VIDEO_CONTROL1_reg.regValue = 0x0;
	rtd_outl(VDC_VIDEO_CONTROL1_VADDR, VIDEO_CONTROL1_reg.regValue);			// set AV
	#else
	rtd_outl(ADC_ADC_POWER_VADDR, 0x000000ff);				// 2_0000 ADC power on
	rtd_outl(ADC_VDADC_POW_CTL_VADDR, 0x00130003);			// 2_005c VDADC power on
	rtd_outl(FEin_VD_IN_DELAY_SEL2_VADDR, 0x00000000);		// 1_9794 disable yc swap
	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00000000);		// disable pattern generator
	rtd_outl(ADC_ADC_CLOCK_VADDR, 0x00000401);				// Selet clk => VDC
	rtd_outl(ADC_ADC_CTL_RGB12_VADDR, 0x0015A02A);			// Selet VIN6P,VIN7P,VIN8P,VIN_Y0N;[12]Gain=0.5
	rtd_outl(ADC_ADC_DCRESTORE_CTRL_VADDR, 0x18180000);	//disable dc restore, select BPF=10M
	rtd_outl(VDC_CLAMP_UPDN_EN_VADDR, 0x00000000);			// set Y
	rtd_outl(VDC_CLAMP_RGB_UPDN_EN_VADDR, 0x000000ff);		// 1_9610 enable clamp up/dn
	rtd_outl(VDC_VIDEO_CONTROL1_VADDR, 0x00000000);			// set AV
	#endif
	udelay(3000);
#endif

#if 0	// for debug
	module_vdc_Print_Registers(Y_path, Gnd_path, 1000);
#endif

printk("\n");
printk("0x%x:\t%x\n",ADC_VD_ADC_CLAMP_CTL_1_VADDR,rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR));//0048
printk("0x%x:\t%x\n",ADC_VD_ADC_CLAMP_CTL_2_VADDR,rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR));//004c
printk("0x%x:\t%x\n",ADC_VD_ADC_UPDN_CTL_VADDR,rtd_inl(ADC_VD_ADC_UPDN_CTL_VADDR));//0050
printk("0x%x:\t%x\n",ADC_VDADC_CORE_LPF_CTRL_VADDR,rtd_inl(ADC_VDADC_CORE_LPF_CTRL_VADDR));//0054
printk("0x%x:\t%x\n",ADC_VDADC_CK_CTL_VADDR,rtd_inl(ADC_VDADC_CK_CTL_VADDR));//0058
printk("0x%x:\t%x\n",ADC_VDADC_POW_CTL_VADDR,rtd_inl(ADC_VDADC_POW_CTL_VADDR));//005c


#if Test_Y_Path
	VIDEO_STATUS_REG1_RBUS VIDEO_STATUS_REG1_reg;
  	for(i=0; i<40000; i++)
 	{
 		VIDEO_STATUS_REG1_reg.regValue = rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR);
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(500);
		if ((VIDEO_STATUS_REG1_reg.hlock == 0x1)&&(VIDEO_STATUS_REG1_reg.vlock == 0x1)&&(VIDEO_STATUS_REG1_reg.chomalock==0x1))
		{
//			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
			break;
		}
		else if(i == 39999)
		{
			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
		}
		else
		{}
	}
#else
  	for(i=0; i<40000; i++)
 	{
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(500);
		if (no_signal == 0xe)
		{
//			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
			break;
		}
		else if(i == 39999)
		{
			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
		}
		else
		{}
	}
#endif

#if 0
  	for(i=0; i<10000; i++)
 	{
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(500);
		if (no_signal == 0xe)
		{
			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
			break;
		}
		else if(i == 9999)
		{
			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
		}
	}

  	for(i=0; i<10000; i++)
 	{
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
		udelay(500);
		if (no_signal == 0xe)
		{
			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
			break;
		}
		else if(i == 9999)
		{
			printk("[QC][VD][Y test][path = %x] no_signal = %x @ %d\n", Y_path, no_signal, i);
		}
	}
#endif

  	if (no_signal == 0x00)
	{
		printk("[QC][VD][AV] crystal does not work! the signal is %x\n", no_signal);
		return _FAIL;
	}
  	else if (no_signal == 0x01)
	{
		printk("[QC][VD][AV] no signal = %x, fail!\n", no_signal);
		return _FAIL;
	}	
	else if (no_signal == 0xe)
	{
		printk("[QC][VD][AV] VD test input VIN%dP is OK with no_signal = %x\n", Y_path, no_signal);
		return _SUCCESS;
	}
	else 
	{
		printk("[QC][VD][AV] VD test input VIN%dP is fail, the signal value==>%x \n", Y_path, no_signal);
		return _FAIL;
	}
	return _SUCCESS;
}

#ifdef Test_vdc_PathSelect
UINT8  module_vdc_PathSelect(void)
{
	UINT8 no_signal;
	UINT8 mode_check;
	UINT8 av_mode;
	UINT32 i;

	av_mode = _PALI;
//	av_mode = _NTSC;

#if 0	// debug
	printk("av_mode = %x	rtd_outl(0x%x, 0x%08x);\n", av_mode, VDC_MODE_DETECTION_STATUS_VADDR, rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR));
#endif
	
	printk("=== VDC Qc PathSelect start ===\n");

#ifdef CONFIG_256_PKG



	printk("[QC][VD][Path Select][SV] test mode = %d\n", av_mode);

//// SV connector Y10P / A2N / C12P / A2N input test ////
	#if 1 //jacky
	if(module_vdc_Test_YC_Path(VIDEO_INPUT10, VIDEO_GNDA1, VIDEO_INPUT13, VIDEO_GNDA2, VIDEO_SV_SWAP) != _SUCCESS)
		return _FAIL;
	#else
	if(module_vdc_Test_YC_Path(VIDEO_INPUT10, VIDEO_GNDA2, VIDEO_INPUT12, VIDEO_GNDA2, VIDEO_SV_SWAP) != _SUCCESS)
		return _FAIL;
	#endif
	udelay(1000);

//// SV connector Y10P / A2N / C12P / A2N mode test ////
#if 0
	if(module_vdc_Test_Mode(av_mode) != _SUCCESS)
	{
#if 1 	// debug
		#if sirius_qc //jacky
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80034a4, rtd_inl(0xb80034a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800356c, rtd_inl(0xb800356c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003570, rtd_inl(0xb8003570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003574, rtd_inl(0xb8003574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003578, rtd_inl(0xb8003578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800357c, rtd_inl(0xb800357c));
		#else
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80194a4, rtd_inl(0xb80194a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801956c, rtd_inl(0xb801956c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019570, rtd_inl(0xb8019570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019574, rtd_inl(0xb8019574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019578, rtd_inl(0xb8019578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801957c, rtd_inl(0xb801957c));
		#endif
#endif
		return _FAIL;
	}
#endif

	drvif_module_vdc_SoftReset();
	drvif_module_vdc_VDCReset();
	udelay(3000);

#if 0	// Make sure VD return to unlock
	for(i=0; i<20000; i++)
	{
		udelay(1000);
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
//		if ((no_signal != 0xe) & (no_signal != 0x6))
		if (no_signal != 0xe)
		{	printk("no_signal = %x @ %d\n", no_signal, i);
			break;
		}
	}
	printk("no_signal = %x \n", no_signal);
#endif
#endif

//// now reverse mode for AV input test ////
//	printk("[QC][VD][Mode test] now reverse the checking mode!\n");
	if(av_mode == _PALI)
	{
//		printk("[QC][VD][Path Select][AV] the mode is %x, now turn it to %x!\n", av_mode, _NTSC);
		av_mode = _NTSC;
	}
	else if(av_mode == _NTSC)
	{
//		printk("[QC][VD][Path Select][AV] the mode is %x, now turn it to %x!\n", av_mode, _PALI);
		av_mode = _PALI;
	}
	else
	{
//		printk("[QC][VD][Path Select][AV] the mode you want to check is neither NTSC nor PALI!\n");
	}
	mode_check = ((UINT8)rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR) & 0x0f);

	udelay(500);
	
//	printk("[QC][VD][Path Select][AV] the input mode is %x now\n", av_mode);

#if 0 	// debug
	#if sirius_qc //jacky
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80034a4, rtd_inl(0xb80034a4));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800356c, rtd_inl(0xb800356c));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003570, rtd_inl(0xb8003570));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003574, rtd_inl(0xb8003574));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003578, rtd_inl(0xb8003578));
	#else
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80194a4, rtd_inl(0xb80194a4));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801956c, rtd_inl(0xb801956c));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019570, rtd_inl(0xb8019570));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019574, rtd_inl(0xb8019574));
	printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019578, rtd_inl(0xb8019578));
	#endif
	printk("rtd_outl(0x%x, 0x%08x);\n", VDC_AUTOMODE_443358PK_CTRL_VADDR, rtd_inl(VDC_AUTOMODE_443358PK_CTRL_VADDR));
#endif

	udelay(500);
	
#if 0	// 2013.03/06 Mark: YPP QC code will test VIN0P ~ VIN5P 
//// AV 0P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT0,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV 1P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT1,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV 2P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT2,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV 3P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT3,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV 4P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT4,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV 5P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT5,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);
#endif
	
#if 0	// 2013.03/13 Mark: IFD QC code will test VIN6P ~ VIN8P 
//// AV 6P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT6, VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
//	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV 7P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT7, VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
//	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV 8P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT8, VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
//	drvif_module_vdc_SoftReset();
	udelay(2000);
#endif

#if 0	// 2013.03/14 Mark: SV part will test VIN10P, VIN13P 
//// AV 10P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT10,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);
	
//// AV 13P input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT13,VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(2000);
#endif

#if 0	// 2013.03/13 Mark: AVOUT (SCART_OUT_pin19) test will test VIN9P & VIN11P
//// AV connector 9P / A1N input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT9, VIDEO_GNDA1) != _SUCCESS)
		return _FAIL;
//	drvif_module_vdc_SoftReset();
	udelay(2000);

//// AV connector 11P / A0N input test ////
	if(module_vdc_Test_Y_Path(VIDEO_INPUT11, VIDEO_GNDA0) != _SUCCESS)
		return _FAIL;
//	drvif_module_vdc_SoftReset();
	udelay(2000);
#endif

//	module_vdc_Print_Registers(VIDEO_INPUT12, VIDEO_GNDA0, 100);	// debug

//// AV connector 9P / A0N input test ////
// CONFIG_BOX == 0 // 0 for BGA_TV , 1 for BGA_BOX
#if CONFIG_BGA == 0 // 0 for QFP , 1 for BGA //jacky sirius
	if(module_vdc_Test_Y_Path(VIDEO_INPUT12, VIDEO_GNDA0) != _SUCCESS)
	{
		#if sirius_qc //jacky
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80034a4, rtd_inl(0xb80034a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800356c, rtd_inl(0xb800356c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003570, rtd_inl(0xb8003570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003574, rtd_inl(0xb8003574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003578, rtd_inl(0xb8003578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800357c, rtd_inl(0xb800357c));
		#else
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80194a4, rtd_inl(0xb80194a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801956c, rtd_inl(0xb801956c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019570, rtd_inl(0xb8019570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019574, rtd_inl(0xb8019574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019578, rtd_inl(0xb8019578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801957c, rtd_inl(0xb801957c));
		#endif

//		module_vdc_Print_Registers(VIDEO_INPUT12, VIDEO_GNDA0, 100);	// debug
		return _FAIL;
	} 
	drvif_module_vdc_SoftReset();
	drvif_module_vdc_VDCReset();
	udelay(3000);
#else //jacky

	drvif_module_vdc_SoftReset();
	drvif_module_vdc_VDCReset();
	udelay(3000);

	if(module_vdc_Test_YC_Path(VIDEO_INPUT10, VIDEO_GNDA1, VIDEO_INPUT12, VIDEO_GNDA2, VIDEO_SV_SWAP) != _SUCCESS)
		return _FAIL;

	drvif_module_vdc_SoftReset();
	drvif_module_vdc_VDCReset();
	udelay(3000);


	if(module_vdc_Test_Y_Path(VIDEO_INPUT9, VIDEO_GNDA0) != _SUCCESS)
	{
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80034a4, rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800356c, rtd_inl(VDC_SEP_BURST_RO2_VADDR));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003570, rtd_inl(VDC_SEP_BURST_RO3_VADDR));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003574, rtd_inl(VDC_SEP_BURST_TH1_VADDR));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003578, rtd_inl(VDC_SEP_BURST_FLAG1_VADDR));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800357c, rtd_inl(VDC_AUTOMODE_443358PK_CTRL_VADDR));

//		module_vdc_Print_Registers(VIDEO_INPUT12, VIDEO_GNDA0, 100);	// debug
		return _FAIL;
	} 
	drvif_module_vdc_SoftReset();
	drvif_module_vdc_VDCReset();
	udelay(3000);

#endif //jacky 

#if 0	// Make sure VD return to unlock
	for(i=0; i<20000; i++)
	{
		udelay(1000);
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
//		if ((no_signal != 0xe) & (no_signal != 0x6))
		if (no_signal != 0xe)
		{	
			printk("no_signal = %x @ %d\n", no_signal, i);
			break;
		}
	}
	printk("no_signal = %x \n", no_signal);
#endif

//// AV connector 14P / A1N input test ////
#if 0
	if(module_vdc_Test_Y_Path(VIDEO_INPUT14, VIDEO_GNDA1) != _SUCCESS)
	{
		#if sirius_qc //jacky
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80034a4, rtd_inl(0xb80034a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800356c, rtd_inl(0xb800356c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003570, rtd_inl(0xb8003570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003574, rtd_inl(0xb8003574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003578, rtd_inl(0xb8003578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800357c, rtd_inl(0xb800357c));
		#else
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80194a4, rtd_inl(0xb80194a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801956c, rtd_inl(0xb801956c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019570, rtd_inl(0xb8019570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019574, rtd_inl(0xb8019574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019578, rtd_inl(0xb8019578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801957c, rtd_inl(0xb801957c));
		#endif
		return _FAIL;
	}
	udelay(3000);	// need some delay to make sure that the detected mode has changed
	
//// AV connector 14P / A1N mode test ////
	if(module_vdc_Test_Mode(av_mode) != _SUCCESS)
	{
		#if sirius_qc //jacky
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80034a4, rtd_inl(0xb80034a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800356c, rtd_inl(0xb800356c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003570, rtd_inl(0xb8003570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003574, rtd_inl(0xb8003574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8003578, rtd_inl(0xb8003578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb800357c, rtd_inl(0xb800357c));
		#else
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb80194a4, rtd_inl(0xb80194a4));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801956c, rtd_inl(0xb801956c));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019570, rtd_inl(0xb8019570));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019574, rtd_inl(0xb8019574));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb8019578, rtd_inl(0xb8019578));
		printk("rtd_outl(0x%x, 0x%08x);\n", 0xb801957c, rtd_inl(0xb801957c));
		#endif
		return _FAIL;
	}

	drvif_module_vdc_SoftReset();
	drvif_module_vdc_VDCReset();
	udelay(3000);


#if 1	// Make sure VD return to unlock
	for(i=0; i<20000; i++)
	{
		udelay(1000);
		no_signal = ((UINT8)rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR) & 0xf);
//		if ((no_signal != 0xe) & (no_signal != 0x6))
		if (no_signal != 0xe)
		{	printk("no_signal = %x @ %d\n", no_signal, i);
			break;
		}
	}
	printk("no_signal = %x \n", no_signal);
#endif
#endif
#ifdef CONFIG_256_PKG
//// AV input from connector VIN9P / A1N through VDBS to VIN13P / A2N, A-A bypass test ////

	rtd_outl(0xb8033004,0x00000111);		// [8] power control of VDBS buffer; [4] power control of line driver	// VDAC_POW	(VDACIFADC_AIF_TOP.doc)
//	rtd_outl(0xb8033004,0x00001011);		// [12] power control of  VDAC; [4] power control of line driver	// VDAC_POW	(VDACIFADC_AIF_TOP.doc)
	#if sirius_qc //jacky
	rtd_outl(0xb8003084,0x00000000);		// [8:5] avout_mixer_sel = 0000: Clamped CVBS data without fe_fil and agc	// AVOUT_FIFO_STATUS
	#else
	rtd_outl(0xb8019084,0x00000000);		// [8:5] avout_mixer_sel = 0000: Clamped CVBS data without fe_fil and agc	// AVOUT_FIFO_STATUS
	#endif
	for(i=0; i<10; i++)	// turn on the VDBS LDO need some time...
		udelay(3000);
	
#if 0	// 2013.03/14 Mark: A-A bypass test
	#include "case13_CVBS_VIN9_fs_fhd/VDBS_VIN9P_VIN11P.tbl";
	for(i=0; i<50; i++)
	{
		udelay(100);
	}
	printk("[QC][VD][AV] now test AA bypass from VIN%dP to VIN%dP\n", VIDEO_INPUT9, VIDEO_INPUT11);
	if(module_vdc_CheckHVCisLocked(VIDEO_INPUT11) != _SUCCESS)
		return _FAIL;

#endif

	// 2013.03/27 Mark: replace script for VDBS test
///// VD AA Bypass /////
	rtd_outl(0xb8033004,0x00000111);		// [8] power control of VDBS buffer; [4] power control of line driver	// VDAC_POW	(VDACIFADC_AIF_TOP.doc)
//	rtd_outl(0xb8033004,0x00001011);		// [12] power control of  VDAC; [4] power control of line driver	// VDAC_POW	(VDACIFADC_AIF_TOP.doc)
	#if sirius_qc //jacky
	rtd_outl(0xb8003084,0x00000000);		// [8:5] avout_mixer_sel = 0000: Clamped CVBS data without fe_fil and agc	// AVOUT_FIFO_STATUS
	#else
	rtd_outl(0xb8019084,0x00000000);		// [8:5] avout_mixer_sel = 0000: Clamped CVBS data without fe_fil and agc	// AVOUT_FIFO_STATUS
	#endif
	udelay(3000);
	
	module_vdc_SetInput_Y(VIDEO_INPUT9, VIDEO_GNDA0);
	for(i=0; i<10; i++)	// make sure the delay is enough
		udelay(3000);

	printk("[QC][VD][Path Select][VDBS] VIDEO_INPUT9 2 VIDEO_INPUT13\n");	
	if(module_vdc_Test_Y_Path(VIDEO_INPUT13, VIDEO_GNDA2) != _SUCCESS)
		return _FAIL;
	drvif_module_vdc_SoftReset();
	udelay(50);
#endif

	return  _SUCCESS;
}
#endif

#ifdef Test_vdc_Test_Memory
UINT8  module_vdc_Test_Memory(void)
{
	UINT32 i;
	UINT32 nRegAddr;
	UINT8  memory_test ;

	drvif_module_vdc_VDCReset();
	drvif_module_vdc_SoftReset();
       nRegAddr=0x0e80000;
#if sirius_qc //jacky
#define VDC_MEM0_ADDR_INI_VADDR                   (0xb8003870)
#define VDC_MEM1_ADDR_INI_VADDR                   (0xb8003874)
#define VDC_MEM2_ADDR_INI_VADDR                   (0xb8003878)
#define VDC_MEM3_ADDR_INI_VADDR                   (0xb800387c)
#define VDC_MEM0_ADDR_END_VADDR                   (0xb8003880)
#define VDC_MEM1_ADDR_END_VADDR                   (0xb8003884)
#define VDC_MEM2_ADDR_END_VADDR                   (0xb8003888)
#define VDC_MEM3_ADDR_END_VADDR                   (0xb800388c)
#else
#define VDC_MEM0_ADDR_INI_VADDR                   (0xb8019870)
#define VDC_MEM1_ADDR_INI_VADDR                   (0xb8019874)
#define VDC_MEM2_ADDR_INI_VADDR                   (0xb8019878)
#define VDC_MEM3_ADDR_INI_VADDR                   (0xb801987c)
#define VDC_MEM0_ADDR_END_VADDR                   (0xb8019880)
#define VDC_MEM1_ADDR_END_VADDR                   (0xb8019884)
#define VDC_MEM2_ADDR_END_VADDR                   (0xb8019888)
#define VDC_MEM3_ADDR_END_VADDR                   (0xb801988c)
#endif

	 // frame 0 start
	rtd_outl(VDC_MEM0_ADDR_INI_VADDR,(nRegAddr&0x1fffffff));
         // frame 0 end
         nRegAddr = nRegAddr + _3D_One_Frame_Use - 1;
	rtd_outl(VDC_MEM0_ADDR_END_VADDR,(nRegAddr&0x1fffffff));

         // frame 1 start
         nRegAddr = nRegAddr + 1;
	rtd_outl(VDC_MEM1_ADDR_INI_VADDR,(nRegAddr&0x1fffffff));
         // frame 1 end
         nRegAddr = nRegAddr + _3D_One_Frame_Use - 1;
	rtd_outl(VDC_MEM1_ADDR_END_VADDR,(nRegAddr&0x1fffffff));

         // frame 2 start
         nRegAddr = nRegAddr + 1;
	rtd_outl(VDC_MEM2_ADDR_INI_VADDR,(nRegAddr&0x1fffffff));
         // frame 2 end
         nRegAddr = nRegAddr + _3D_One_Frame_Use - 1;
 	rtd_outl(VDC_MEM2_ADDR_END_VADDR,(nRegAddr&0x1fffffff));

         // frame 3 start
         nRegAddr = nRegAddr + 1;
	rtd_outl(VDC_MEM3_ADDR_INI_VADDR,(nRegAddr&0x1fffffff));
          // frame 3 end
         nRegAddr = nRegAddr + _3D_One_Frame_Use - 1;
	rtd_outl(VDC_MEM3_ADDR_END_VADDR,(nRegAddr&0x1fffffff));
	rtd_outl(VDC_VD_SRAM_ON_OFF_VADDR,0x03);//CRC bypass memory enable
	rtd_outl(VDC_DMA_CTRL5_VADDR,0x02);//open memory and test

  	for( i=0;i<100;i++)
	{
	  	udelay(300);
		memory_test= (UINT8)rtd_inl(VDC_DMA_CTRL5_VADDR);
    		memory_test = 0x03 & memory_test;
		if(memory_test==0x03)
			break;
	}

	memory_test=(UINT8)rtd_inl(VDC_DMA_CTRL5_VADDR);
	if(memory_test!=0x03)
	{
		printk("vd test memory is fail  the memory test value==>%x \n", memory_test );
		rtd_outl(VDC_DMA_CTRL5_VADDR,0x04);//off memory
		return _FAIL;
	}
	else
	{
		printk("[TEST_MEMORY] memory test OK \n");
	}
	rtd_outl(VDC_DMA_CTRL5_VADDR,0x04); //off memory
	return  _SUCCESS;
}
#endif

#ifdef Test_vdc_Test_BIst
UINT8  module_vdc_Test_BIst(void)
{
//	printk("Now testing BIST\n");
//	UINT32 i;
	drvif_module_vdc_VDCReset();
	drvif_module_vdc_SoftReset();

	rtd_outl(VDC_BIST_MODE_VADDR,0x1f);	//0xb801_97a0 enable all bist modes
#if 1	// 2013.02/26 Mark debug BIST en
	BIST_MODE_RBUS bist_mode_reg;
	bist_mode_reg.regValue = rtd_inl(VDC_BIST_MODE_VADDR);
	printk("BIST_MODE %X = %X\n",VDC_BIST_MODE_VADDR,bist_mode_reg.regValue);
#endif

	//udelay(5000);
	udelay(10000);

	if((UINT8)rtd_inl(VDC_BIST_DONE_VADDR)!=0x1f)	//0xb801_97a4 check all bist modes done
	{
#if 1	// 2013.02/26 Mark debug BIST done
		BIST_DONE_RBUS bist_done_reg;
		bist_done_reg.regValue = rtd_inl(VDC_BIST_DONE_VADDR);
		printk("BIST_DONE %X = %X\n",VDC_BIST_DONE_VADDR,bist_done_reg.regValue);
#endif
		printk("	bist_done is not ready	(time out)");
		return _FAIL;
	}

	udelay(500);

	if((UINT8)rtd_inl(VDC_BIST_FAIL_VADDR))	//0xb801_97a8 check any of bist modes fail
	{
#if 0	// 2013.02/26 Mark debug BIST fail
		BIST_FAIL_RBUS bist_fail_reg;
		bist_fail_reg.regValue = rtd_inl(VDC_BIST_FAIL_VADDR);
		printk("BIST_FAIL %X = %X\n",VDC_BIST_FAIL_VADDR,bist_fail_reg.regValue);
#endif	
		printk("	bist fail~~~~~ ");
		return _FAIL;
	}

	printk("[TEST_BIST] Bist test OK \n");
	
	return  _SUCCESS;
}

#endif
UINT8  module_Debug_CRC_Registert(void)
{

	printk("module_Debug_CRC_Registert\n");
	printk("VDC_MISC_CONTROL_VADDR=%x \n", rtd_inl(VDC_MISC_CONTROL_VADDR));	// bit[9:8]=01, select Select the VCO freq = 540M
	printk("VDC_VD_SRAM_ON_OFF_VADDR =%x\n",rtd_inl(VDC_VD_SRAM_ON_OFF_VADDR));	// 1_985c[1:0] CRC bypass memory enable; VD SRAM = on
    	printk("VDC_YC_SEP_MODE_CTRL_VADDR=%x\n",rtd_inl(VDC_YC_SEP_MODE_CTRL_VADDR));	// 1_9b28 D memory Off, test 1D (YC_SEP_MODE_CTRL PQ.doc)
    	printk("VDC_YC_SEP_CONTROL_VADDR=%x \n" ,rtd_inl(VDC_YC_SEP_CONTROL_VADDR));	// 1_9900[2:0] 2D memory Off, test 1D; select modes for the composite signal's luma (Y) and chroma I separation before color demodulation = 011: basic luma notch filter mode (for very noisy and unstable pictures)  (不經過line buffer的結果)

 //	stop clock
    	printk("VDC_PATTERN_CONTROL_VADDR=%x\n", rtd_inl(VDC_PATTERN_CONTROL_VADDR));    //disable pattern gen.
    	printk("VDC_DMA_CTRL5_VADDR=%x \n", rtd_inl(VDC_DMA_CTRL5_VADDR));		  //frame buffer memory off.
    	printk("VDC_YC_SEP_MODE_CTRL_VADDR=%x \n", rtd_inl(VDC_YC_SEP_MODE_CTRL_VADDR));
    	printk("VDC_YC_SEP_CONTROL_VADDR=%x \n", rtd_inl(VDC_YC_SEP_CONTROL_VADDR));	  //notch-filter
	printk("VDC_AD_SW_CTRL0_VADDR=%x\n",rtd_inl(VDC_AD_SW_CTRL0_VADDR));
	printk("VDC_CLAMP_UPDN_EN_VADDR=%x\n",rtd_inl(VDC_CLAMP_UPDN_EN_VADDR));

/////PatternGenMode==CVBS

    	printk("VDC_VIDEO_CONTROL1_VADDR=%x\n", rtd_inl(VDC_VIDEO_CONTROL1_VADDR));   // Video Control, set input format: CVBS
    	printk("VDC_VIDEO_CONTROL1_VADDR=%x \n", rtd_inl(VDC_VD_BASIC_REGISTER_ENABLE_VADDR));   // Auto Mode: basic register enable (default)
    	printk("VDC_YC_SEP_CONTROL_VADDR%x\n", rtd_inl(VDC_YC_SEP_CONTROL_VADDR));   // YC sep adaptive mode: 2D (default)
    	printk("VDC_VSYNC_TIME_CONST_VADDR=%x\n", rtd_inl(VDC_VSYNC_TIME_CONST_VADDR));   // VSYNC_TIME_CONST: set field polarity
    	printk("VDC_CSTATE_CTRL_VADDR=%x\n", rtd_inl(VDC_CSTATE_CTRL_VADDR));   // disable Fast lock when phase error
}
UINT8 VDC_CVBS_PatternGen_Enable(UINT8 num)
{
    	UINT32 crc = 0x00000000;
	UINT32 i;
	rtd_outl(VDC_MISC_CONTROL_VADDR, 0x2017f);	// bit[9:8]=01, select Select the VCO freq = 540M
	rtd_outl(VDC_VD_SRAM_ON_OFF_VADDR,0x03);	// 1_985c[1:0] CRC bypass memory enable; VD SRAM = on
    	rtd_outl(VDC_YC_SEP_MODE_CTRL_VADDR, 0x00);	// 1_9b28 D memory Off, test 1D (YC_SEP_MODE_CTRL PQ.doc)
    	rtd_outl(VDC_YC_SEP_CONTROL_VADDR, 0x03);	// 1_9900[2:0] 2D memory Off, test 1D; select modes for the composite signal's luma (Y) and chroma I separation before color demodulation = 011: basic luma notch filter mode (for very noisy and unstable pictures)  (不經過line buffer的結果)
//	VDC Reset
	drvif_module_vdc_VDCReset();
	drvif_module_vdc_SoftReset();
 //	stop clock
	udelay(10000);
#if 1
    	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);    //disable pattern gen.
    	rtd_outl(VDC_DMA_CTRL5_VADDR, 0x04);		  //frame buffer memory off.
    	rtd_outl(VDC_YC_SEP_MODE_CTRL_VADDR, 0x00);
//    	rtd_outl(VDC_YC_SEP_CONTROL_VADDR, 0x03);	  //notch-filter
	rtd_outl(VDC_AD_SW_CTRL0_VADDR,0x00);
//	rtd_outl(VDC_CLAMP_UPDN_EN_VADDR,0x00);

    	for( i=0; i<500; i++)
    	{
        	udelay(100);
    	}
/////PatternGenMode==CVBS

//    	rtd_outl(VDC_VIDEO_CONTROL1_VADDR, 0x00000001);   // Video Control, set input format: CVBS
//    	rtd_outl(VDC_VD_BASIC_REGISTER_ENABLE_VADDR, 0x00000000);   // Auto Mode: basic register enable (default)
    	rtd_outl(VDC_YC_SEP_CONTROL_VADDR, 0x00000003);   // YC sep adaptive mode: 2D (default)
//	  	rtd_outl(VDC_VSYNC_TIME_CONST_VADDR, 0x0000008a);   // VSYNC_TIME_CONST: set field polarity
//    	rtd_outl(VDC_CSTATE_CTRL_VADDR, 0x000000a0);   // disable Fast lock when phase error
//		rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000080);

#endif

	if(num==3)
	{
		udelay(100);
		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x13);	  //enable PAL pattern gen.(MP)
	}
	else if(num==2)
	{
		udelay(100);
		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x11);	  //enable NTSC pattern gen.(MP)
	}
	else if(num==1)
    	{
            	udelay(100);
        	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x03);    //enable PAL pattern gen.(QC)
    	}
    	else
    	{
            	udelay(100);
        	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x01);    //enable NTSC pattern gen.(QC)
    	}

    	for( i=0; i<10; i++)
    	{
        	udelay(100);
    	}
    	drvif_module_vdc_clock_enable(0);		
      	udelay(100);
	drvif_module_vdc_SoftReset();

		
		
    	for( i=0;i<300;i++)
	{
		udelay(50);
    	}

    	drvif_module_vdc_clock_enable(1);

    	for( i=0;i<300;i++)
    	{
	    	udelay(1000);
    	}

#if 0
	printk("CVBS 9418:%x............. \n",rtd_inl(VDC_PATTERN_CONTROL_VADDR));
	printk("9008=%x \n",rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR));
    	printk("[crc ] %x \n",rtd_inl(VDC_CRC_RESULT3_VADDR));

#endif

	crc=rtd_inl(VDC_CRC_RESULT3_VADDR);

	if(num==3)
	{
	     	if(crc != cvbs_2d_pal_mp)
	    	{
	    		CRC_error_count=CRC_error_count+1;    	    	
        		printk(" the cvbs CRC,2d,pal MP is error, the value:%x,CRC_error_count=%d \n",crc,CRC_error_count);
        		//rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);
//        		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);
//			module_Debug_CRC_Registert();
			module_vdc_Bring_Up_screen_scripts();										
        		return _FAIL;
   		}
		else
		{
			CRC_error_count=0;
			printk("crc:pal MP test is OK, crc = %x\n", crc);
		}
	}
	else if(num==2)
	{
	    	if(crc != cvbs_2d_ntsc_mp)
    		{
	    		CRC_error_count=CRC_error_count+1;    
        		printk(" the cvbs CRC,2d,ntsc MP is error, the value:%x,CRC_error_count=%d \n",crc,CRC_error_count);
        		//rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);
//        		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);
//			module_Debug_CRC_Registert();
			module_vdc_Bring_Up_screen_scripts();				
        		return _FAIL;
	    	}
		else
		{
			CRC_error_count=0;		
			printk("crc:ntsc MP test is OK, crc = %x\n", crc);
		}
	}
	else if(num==1)
	{
	     	if(crc != cvbs_2d_pal_qc)
	    	{
	    		CRC_error_count=CRC_error_count+1;    	    	
        		printk(" the cvbs CRC,2d,pal QC is error, the value:%x,CRC_error_count=%d \n",crc,CRC_error_count);
        		//rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);
//        		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);
//			module_Debug_CRC_Registert();
			module_vdc_Bring_Up_screen_scripts();						
        		return _FAIL;
   		}
		else
		{
			CRC_error_count=0;		
			printk("crc:pal QC test is OK, crc = %x\n", crc);
		}
	}
	else
	{
	    	if(crc != cvbs_2d_ntsc_qc)
	    	{
	    		CRC_error_count=CRC_error_count+1;    	    	
        		printk(" the cvbs CRC,2d,ntsc QC is error, the value:%x,CRC_error_count=%d \n",crc,CRC_error_count);
        		//rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);
//        		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);
//			module_Debug_CRC_Registert();
			module_vdc_Bring_Up_screen_scripts();						
        		return _FAIL;
	    	}
		else
		{
			CRC_error_count=0;			
			printk("crc:ntsc QC test is OK, crc = %x\n", crc);
		}
	}

    	for( i=0;i<100;i++)
    	{
        	udelay(50);
    	}

    	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);    //disable pattern gen.
    	rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);

    	for( i=0;i<10;i++)
    	{
        	udelay(50);
    	}
	drvif_module_vdc_SoftReset();

#if 0
#if defined(CONFIG_FT)
	for( i=0;i<50;i++)
#else
    	for( i=0;i<100;i++)
#endif
    	{
        	udelay(50);
    	}

    	printk("9418:%x............. \n",rtd_inl(VDC_PATTERN_CONTROL_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT3_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT2_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT1_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT0_VADDR));
#endif
    return _SUCCESS;
}
UINT8 VDC_Component_PatternGen_Enable(UINT8 num)
{
    	UINT32 crc = 0x00000000;
    	UINT32 i;
 // stop clock

    	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);    //disable pattern gen.
    	rtd_outl(VDC_DMA_CTRL5_VADDR, 0x04);
    	rtd_outl(VDC_YC_SEP_MODE_CTRL_VADDR, 0x00);
    	rtd_outl(VDC_YC_SEP_CONTROL_VADDR, 0x03);
	rtd_outl(VDC_AD_SW_CTRL0_VADDR,0x40);
	rtd_outl(VDC_CLAMP_UPDN_EN_VADDR,0x00);

    	for( i=0;i<500;i++)
    	{
        	udelay(100);
    	}
/////PatternGenMode==YPbPr

    	rtd_outl(VDC_VIDEO_CONTROL1_VADDR, 0x00000041);   // Video Control, set input format: YPbPr
    	rtd_outl(VDC_VD_BASIC_REGISTER_ENABLE_VADDR, 0x00000000);   // Auto Mode: basic register enable (default)
    	rtd_outl(VDC_YC_SEP_CONTROL_VADDR, 0x00000003);   // YC sep adaptive mode: 2D (default)
    	rtd_outl(VDC_VSYNC_TIME_CONST_VADDR, 0x0000008a);   // VSYNC_TIME_CONST: set field polarity
    	rtd_outl(VDC_CSTATE_CTRL_VADDR, 0x000000a0);   // disable Fast lock when phase error

    	if(num==1)
    	{
       	rtd_outl(VDC_MANUAL_MODE_VADDR, 0x01);
            	udelay(500);
        	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x0F);    //enable PAL pattern gen.
    	}
    	else
    	{
        	rtd_outl(VDC_MANUAL_MODE_VADDR, 0x00);
		udelay(500);
        	 rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x0D);    //enable NTSC pattern gen.
    	}
	drvif_module_vdc_clock_enable(0);
    	for( i=0;i<100;i++)
    	{
        	udelay(100);
    	}

	drvif_module_vdc_SoftReset();

    	for( i=0;i<600;i++)
	{
		udelay(50);
    	}
    	drvif_module_vdc_clock_enable(1);

    	for( i=0;i<3000;i++)
    	{
	    	udelay(100);
    	}
#if 0
	printk("CVBS 9418:%x............. \n",rtd_inl(VDC_PATTERN_CONTROL_VADDR));
	printk("9008=%x \n",rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR));
    	printk("[crc 1_0] %x \n",rtd_inl(VDC_CRC_RESULT3_VADDR));
	printk("[crc 1_1] %x \n",rtd_inl(VDC_CRC_RESULT2_VADDR));
	printk("[crc 1_2] %x \n",rtd_inl(VDC_CRC_RESULT1_VADDR));
	printk("[crc 1_3] %x \n",rtd_inl(VDC_CRC_RESULT0_VADDR));
#endif
    	crc=rtd_inl(VDC_CRC_RESULT3_VADDR);

    	if(num==1)
    	{
         	if(crc != Component_2d_pal)
        	{
            		printk(" the cvbs CRC,2d,pal is error, the value:%x............. \n",crc);
            		rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);
            		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);
			module_Debug_CRC_Registert();					
            		return _FAIL;
       	}
		else
		{
			printk("crc: cvbs CRC,2d,pal is OK, crc = %x\n", crc);
		}
    	}
    	else
    	{
        	if(crc != Component_2d_ntsc)
        	{
            		printk(" the cvbs CRC,2d,ntsc is error, the value:%x............. \n",crc);
            		rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);
            		rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);
			module_Debug_CRC_Registert();					
            		return _FAIL;
        	}
		else
		{
			printk("crc: cvbs CRC,2d,ntsc is OK, crc = %x\n", crc);
		}
    	}

    	for( i=0;i<3000;i++)
    	{
        	udelay(50);
        	udelay(50);
    	}
    	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);    //disable pattern gen.
    	rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);
    	for( i=0;i<3000;i++)
    	{
        	udelay(50);
        	udelay(50);
    	}
	drvif_module_vdc_SoftReset();
    	for( i=0;i<3000;i++)
    	{
        	udelay(50);
        	udelay(50);
    	}

#if 0
    	printk("9418:%x............. \n",rtd_inl(VDC_PATTERN_CONTROL_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT3_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT2_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT1_VADDR));
    	printk("[reset] %x \n",rtd_inl(VDC_CRC_RESULT0_VADDR));
#endif
    return _SUCCESS;
}


#if 1
void vdc_change_adc_from_ypp_vinXp(unsigned char vinXp)
{
	vd_adc_clamp_ctl_1_RBUS vd_adc_clamp_ctl_1_reg; // 2_0048
	vd_adc_clamp_ctl_2_RBUS vd_adc_clamp_ctl_2_reg;//2_004c
	adc_ctl_rgb12_RBUS 	adc_ctl_rgb12_REG;//2_0008
	
	//clear the value
	rtd_outl(ADC_ADC_CTL_RGB12_VADDR, 0x0);
	
	adc_ctl_rgb12_REG.regValue = rtd_inl(ADC_ADC_CTL_RGB12_VADDR);
	vd_adc_clamp_ctl_1_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR);
	vd_adc_clamp_ctl_2_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR);

	adc_ctl_rgb12_REG.adc_ctl_rgb1_11_10 = vinXp;//[11:10] VD Channel Input+ Select VIN_VD_i = 0x1:VIN_4P 0x2:VIN_7P 0x3:VIN_8P	// ADC_CTL_RGB12
	vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_10 = 0x1; //vin8p
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_10_9 = 0x0; //vin9pp

	rtd_outl(ADC_VD_ADC_CLAMP_CTL_1_VADDR, vd_adc_clamp_ctl_1_reg.regValue);
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_2_VADDR, vd_adc_clamp_ctl_2_reg.regValue);
	rtd_outl(ADC_ADC_CTL_RGB12_VADDR, adc_ctl_rgb12_REG.regValue);

	//rtd_outl(0xb8020008,0x00000400);		// [11:10] VD Channel Input+ Select VIN_VD_i = 00:VIN_4P	// ADC_CTL_RGB12

}

void vdc_dc_restore_enable(unsigned char v0v1v2)
{
	vd_adc_clamp_ctl_1_RBUS vd_adc_clamp_ctl_1_reg; // 2_0048
	vd_adc_clamp_ctl_1_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR);

	switch(v0v1v2)
	{
		case dc_v0:
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_15_13 = 0x1;
			break;
		case dc_v1:
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_15_13 = 0x2;
			break;
		case dc_v2:
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_15_13 = 0x4;
			break;
		case dc_v_all_enable:
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_15_13 = 0x7;
			break;
		case dc_v_all_disble:
		default:
			vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_15_13 = 0x0;
			break;
	}

	rtd_outl(ADC_VD_ADC_CLAMP_CTL_1_VADDR,vd_adc_clamp_ctl_1_reg.regValue);
}

void vdc_clamp_updn_enable(unsigned int positive, unsigned int negative)
{
	vd_adc_updn_ctl_RBUS vd_adc_updn_ctl_reg;

	vd_adc_updn_ctl_reg.regValue = rtd_inl(ADC_VD_ADC_UPDN_CTL_VADDR);
	
	vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = negative;//disable  negative updn clamp
	vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0 = positive;//disable updn clamp

	rtd_outl(ADC_VD_ADC_UPDN_CTL_VADDR,vd_adc_updn_ctl_reg.regValue);
}

void vdc_dump_register(void)
{
	unsigned int i = 0;
	unsigned int adc_base_address = 0xb8020048;

	for(i = 0; i < 6; i++)
	{
		//adc_base_address+=(i*4);
		dmsg("address 0x%x, value: 0x%x\n", (adc_base_address+(i*4)), rtd_inl((adc_base_address+(i*4))));
	}
}

void vdc_open_vin7p_for_ifd_loopback_test(void)
{
		unsigned int i;
		
		module_vdc_crt_clock_setting();
	
		module_vdc_adc_power_on();
	
		drvif_module_vdc_VDCReset();	
	
		drvif_module_vdc_SoftReset();	

		module_vdc_switch_av_2_tv_and_disable_ifd_clamp();

		module_vdc_adc_setting();

		dmsg("1--------------------\n");
		vdc_dump_register();

		vdc_change_adc_from_ypp_vinXp(VIN_7P);

		dmsg("2--------------------\n");
		vdc_dump_register();
	
		drvif_module_vdc_Initial(); 

		vdc_clamp_updn_enable(updn_pos_v0, updn_neg_v0);

		vdc_dc_restore_enable(dc_v_all_disble);

		//disable sv seperation 
		vd_adc_clamp_ctl_2_RBUS vd_adc_clamp_ctl_2_reg; // 2_004c
		vd_adc_clamp_ctl_2_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR);
		vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_5 = 0x0;
		rtd_outl(ADC_VD_ADC_CLAMP_CTL_2_VADDR,vd_adc_clamp_ctl_2_reg.regValue);

		//reference from Y0N
		vd_adc_clamp_ctl_1_RBUS vd_adc_clamp_ctl_1_reg;
		vd_adc_clamp_ctl_1_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR);
		vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_15_14 = 0x0;
		rtd_outl(ADC_VD_ADC_CLAMP_CTL_1_VADDR,vd_adc_clamp_ctl_1_reg.regValue);		

		dmsg("3--------------------\n");
		vdc_dump_register();

		for( i=0;i<10000;i++)
    	{
       		udelay(100);
    	}
		dmsg("\naddress 0x%x, vdc status:0x%x\n",VDC_VIDEO_STATUS_REG1_VADDR,rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR));

		//while(1);
}

//close clock and rst vd. Then, open clock again
void vdc_clock_OnOff_and_rst(void)
{
	unsigned int i;
	
	udelay(10000);
	
	drvif_module_vdc_clock_enable(0);
    for( i=0;i<100;i++)
    {
       	udelay(100);
    }

	drvif_module_vdc_SoftReset();

    for( i=0;i<600;i++)
	{
		udelay(50);
    }

	drvif_module_vdc_clock_enable(1);

    for( i=0;i<3000;i++)
    {
	   	udelay(100);
    }

}

void vdc_scart_enable(unsigned int format, unsigned int crc_check_sel_t)
{
	PATTERN_CONTROL_RBUS PATTERN_CONTROL_REG;
	FSW_CTRL2_RBUS FSW_CTRL2_REG;
	AD_SW_CTRL0_RBUS AD_SW_CTRL0_REG;
	CB_SAT_ADJ_RBUS CB_SAT_ADJ_REG;

	rtd_outl(VDC_FSW_CTRL2_VADDR ,0x0);//3620 // data path scart enable

	PATTERN_CONTROL_REG.regValue= rtd_inl(VDC_PATTERN_CONTROL_VADDR);
	FSW_CTRL2_REG.regValue = rtd_inl(VDC_FSW_CTRL2_VADDR);
	AD_SW_CTRL0_REG.regValue = rtd_inl(VDC_AD_SW_CTRL0_VADDR);
	CB_SAT_ADJ_REG.regValue = rtd_inl(VDC_CB_SAT_ADJ_VADDR);

	// pattern_gen_scart_en
	PATTERN_CONTROL_REG.pattern_generator_enable = 0x1;
	PATTERN_CONTROL_REG.pattern_gen_scart_en = 0x1;

	PATTERN_CONTROL_REG.crc_chk_sel = crc_check_sel_t;
	PATTERN_CONTROL_REG.pattern_gen_cvbs_mode = format;

	PATTERN_CONTROL_REG.patgen_vline = 0x40;
	PATTERN_CONTROL_REG.patgen_vline_en = 0x0;
	PATTERN_CONTROL_REG.patgen_vline_vactive_end = 0x1D;
	PATTERN_CONTROL_REG.fifo_out_pattern_gen_en = 0x0;
	
	// data path scart enable
	FSW_CTRL2_REG.scart_en = 0x1;
	FSW_CTRL2_REG.cout_limit = 0x1;
	FSW_CTRL2_REG.fb_sw = 0x1;
	// It has to disable, because of only 422 output in the fpga 
	FSW_CTRL2_REG.out444_sel = 0x1;
	FSW_CTRL2_REG.outfifo_444_sel = 0x1;
	
	// scart adc select
	AD_SW_CTRL0_REG.sw_comp = 0x0;
	AD_SW_CTRL0_REG.sw_pr_r = 0x1;
	AD_SW_CTRL0_REG.sw_pb_b = 0x3;
	AD_SW_CTRL0_REG.sw_g = 0x2;

	//saturation
	CB_SAT_ADJ_REG.cb_saturation = 0x80;

	rtd_outl(VDC_PATTERN_CONTROL_VADDR , PATTERN_CONTROL_REG.regValue);//3794 // pattern_gen_scart_en
	rtd_outl(VDC_FSW_CTRL2_VADDR , FSW_CTRL2_REG.regValue);//3620 // data path scart enable
	rtd_outl(VDC_AD_SW_CTRL0_VADDR , AD_SW_CTRL0_REG.regValue);//3608 // scart adc select
	rtd_outl(VDC_CB_SAT_ADJ_VADDR , CB_SAT_ADJ_REG.regValue); //3634 saturation

	// open 1-2-1 filter
	FSW_CTRL2_REG.regValue = rtd_inl(VDC_FSW_CTRL2_VADDR);
	FSW_CTRL2_REG.fb_sw = 0x1;
	FSW_CTRL2_REG.fb_en = 0x0;
	rtd_outl(VDC_FSW_CTRL2_VADDR , FSW_CTRL2_REG.regValue);//3620 // data path scart enable


	dmsg("0x%x, 0x%x\n",VDC_PATTERN_CONTROL_VADDR,rtd_inl(VDC_PATTERN_CONTROL_VADDR));
	dmsg("0x%x, 0x%x\n",VDC_FSW_CTRL2_VADDR,rtd_inl(VDC_FSW_CTRL2_VADDR));
	dmsg("0x%x, 0x%x\n",VDC_AD_SW_CTRL0_VADDR,rtd_inl(VDC_AD_SW_CTRL0_VADDR));
	dmsg("0x%x, 0x%x\n",VDC_CB_SAT_ADJ_VADDR,rtd_inl(VDC_CB_SAT_ADJ_VADDR));
	//rtd_outl(VDC_PATTERN_CONTROL_VADDR , 0x01d04021);//3794 // pattern_gen_scart_en
	//rtd_outl(VDC_FSW_CTRL2_VADDR , 0x00000090);//3620 // data path scart enable
	//rtd_outl(VDC_AD_SW_CTRL0_VADDR , 0x0000001E);//3608 // scart adc select
	//rtd_outl(VDC_CB_SAT_ADJ_VADDR , 00000080); //3634 saturation
	//rtd_outl(VDC_FSW_CTRL2_VADDR , 0x00000092);//3620 // bit[0] =0 scart_rgb data  bit[0] = 1 cvbs_data

}

UINT8 VDC_SCART_PatternGen_Enable(UINT8 num)
{
	unsigned int scart_crc = 0x0;
	unsigned int i;

	//clear setting 
	rtd_outl(VDC_VIDEO_CONTROL1_VADDR,0x0); 
	
	switch(num){
		case 0:
				vdc_scart_enable(NTSC_,QC_);	
				break;
		case 1:
				vdc_scart_enable(PALI_,QC_);
				break;
		case 2:
				vdc_scart_enable(NTSC_,MP_);
				break;
		case 3:
				vdc_scart_enable(PALI_,MP_);
				break;
	}

	//close clock and rst vd. Then, open clock again
	vdc_clock_OnOff_and_rst();

	scart_crc = rtd_inl(VDC_CRC_RESULT3_VADDR);

	#if 0 //nothing to do, just to check the variance of crc
	for(i = 0; i< 100; i++)
	{
		scart_crc = rtd_inl(VDC_CRC_RESULT3_VADDR);
		printk("0x%x\n",scart_crc);
		udelay(100);
	}
	#endif

	switch(num){
		case 0:
			if(scart_crc != g_scart_ntsc_crc_qc)
			{
				printk("SCART NTSC QC CRC VALUE:0x%x\n",scart_crc);
				return _FAIL;
			}
			else
			{
				printk("scart_crc:NTSC QC test is OK, crc = %x\n", scart_crc);
			}
			break;
		case 1:
			if(scart_crc != g_scart_pali_crc_qc)
			{
				printk("SCART PALI QC CRC VALUE:0x%x, \n",scart_crc);
				return _FAIL;
			}
			else
			{
				printk("scart_crc:PALI QC test is OK, crc = %x\n", scart_crc);

			}
			break;
		case 2:
			if(scart_crc != g_scart_ntsc_crc_mp)
			{
				printk("SCART NTSC MP CRC VALUE:0x%x, \n",scart_crc);
				return _FAIL;
			}
			else
			{
				printk("scart_crc:NTSC MP test is OK, crc = %x\n", scart_crc);
			}
			break;
		case 3:
			if(scart_crc != g_scart_ntsc_crc_mp)
			{
				printk("SCART PALI MP CRC VALUE:0x%x, \n",scart_crc);
				return _FAIL;
			}
			else
			{
				printk("scart_crc:PALI MP test is OK, crc = %x\n", scart_crc);
			}
			break;
		default:
			printk("Please use 0 to 3! NOTHGINGH TO DO\n");
			break;
	}

	rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);    //disable pattern gen.
	
	return _SUCCESS;
		
}

void VDC_SV_enable(unsigned int format, unsigned int crc_check_sel_t)
{
	PATTERN_CONTROL_RBUS PATTERN_CONTROL_REG; //3794
	VIDEO_CONTROL1_RBUS VIDEO_CONTROL1_REG; //3004

	rtd_outl(VDC_VIDEO_CONTROL1_VADDR,0X0);
	rtd_outl(VDC_YC_SEP_MODE_CTRL_VADDR, 0x00);	// 1_9b28 D memory Off, test 1D (YC_SEP_MODE_CTRL PQ.doc)
    rtd_outl(VDC_YC_SEP_CONTROL_VADDR, 0x03);	// 1_9900[2:0] 2D memory Off, test 1D; select modes for the composite signal's luma (Y) and chroma I separation before color demodulation = 011: basic luma notch filter mode (for very noisy and unstable pictures)  (不經過line buffer的結果)
	rtd_outl(VDC_AD_SW_CTRL0_VADDR,0x0);
	
	PATTERN_CONTROL_REG.regValue = rtd_inl(VDC_PATTERN_CONTROL_VADDR);
	VIDEO_CONTROL1_REG.regValue = rtd_inl(VDC_VIDEO_CONTROL1_VADDR);

	//pattern generator enable
	PATTERN_CONTROL_REG.pattern_generator_enable = 0x1;
	PATTERN_CONTROL_REG.crc_chk_sel = crc_check_sel_t;
	PATTERN_CONTROL_REG.pattern_gen_cvbs_mode = format;

	//switch to the path of sv
	VIDEO_CONTROL1_REG.yc_src = 0x1;

	rtd_outl(VDC_PATTERN_CONTROL_VADDR,PATTERN_CONTROL_REG.regValue);
	rtd_outl(VDC_VIDEO_CONTROL1_VADDR,VIDEO_CONTROL1_REG.regValue);

	dmsg("0x%x, 0x%x\n",VDC_PATTERN_CONTROL_VADDR,rtd_inl(VDC_PATTERN_CONTROL_VADDR));
	dmsg("0x%x, 0x%x\n",VDC_VIDEO_CONTROL1_VADDR,rtd_inl(VDC_VIDEO_CONTROL1_VADDR));

//rtd_outl(VDC_PATTERN_CONTROL_VADDR , 0x00000001);//3794 // pattern_gen_en
//rtd_outl(VDC_VIDEO_CONTROL1_VADDR , 0x00000020);//3004 // data path sv enable

}

UINT8 VDC_SV_PatternGen_Enable(UINT8 num)
{
	unsigned int sv_crc = 0x0;
	unsigned int i;
	
	switch(num){
		case 0:
				VDC_SV_enable(NTSC_,QC_);	
				break;
		case 1:
				VDC_SV_enable(PALI_,QC_);
				break;
		case 2:
				VDC_SV_enable(NTSC_,MP_);
				break;
		case 3:
				VDC_SV_enable(PALI_,MP_);
				break;
	}

	//close clock and rst vd. Then, open clock again
	vdc_clock_OnOff_and_rst();

	sv_crc = rtd_inl(VDC_CRC_RESULT3_VADDR);

	switch(num){
		case 0:
			if(sv_crc != g_sv_ntsc_crc_qc)
			{
				CRC_error_count=CRC_error_count+1;
				printk("SV NTSC QC CRC VALUE:0x%x\n",sv_crc);
				return _FAIL;
			}
			else
			{
				CRC_error_count=0;
				printk("sv_crc:NTSC QC test is OK, crc = %x\n", sv_crc);
			}
			break;
		case 1:
			if(sv_crc != g_sv_pali_crc_qc)
			{
				CRC_error_count=CRC_error_count+1;
				printk("SV PALI QC CRC VALUE:0x%x, \n",sv_crc);
				return _FAIL;
			}
			else
			{
				CRC_error_count=0;
				printk("sv_crc:PALI QC test is OK, crc = %x\n", sv_crc);
			}
			break;
		case 2:
			if(sv_crc != g_sv_ntsc_crc_mp)
			{
				CRC_error_count=CRC_error_count+1;
				printk("SV NTSC MP CRC VALUE:0x%x, \n",sv_crc);
				return _FAIL;
			}
			else
			{
				CRC_error_count=0;
				printk("sv_crc:NTSC MP test is OK, crc = %x\n", sv_crc);
			}
			break;
		case 3:
			if(sv_crc != g_sv_pali_crc_mp)
			{
				CRC_error_count=CRC_error_count+1;
				printk("SV PALI MP CRC VALUE:0x%x, \n",sv_crc);
				return _FAIL;
			}
			else
			{
				CRC_error_count=0;
				printk("sv_crc:PALI MP test is OK, crc = %x\n", sv_crc);
			}
			break;
		default:
			printk("Please use 0 to 3! NOTHGINGH TO DO\n");
			break;
	}

    	for( i=0;i<100;i++)
    	{
        	udelay(50);
    	}

    rtd_outl(VDC_PATTERN_CONTROL_VADDR, 0x00);    //disable pattern gen.
    rtd_maskl(VDC_HSYNC_DTO_INC_VADDR,0x7fffffff,0x00000000);

    	for( i=0;i<10;i++)
    	{
        	udelay(50);
    	}
	drvif_module_vdc_SoftReset();



	return _SUCCESS;
}
#endif




//#define Component_PatternGen_NTSC
//#define Component_PatternGen_PAL

#define CVBS_PatternGen_2D_PAL_QC
#define CVBS_PatternGen_2D_NTSC_QC


#define CVBS_PatternGen_2D_PAL_MP
#define CVBS_PatternGen_2D_NTSC_MP

UINT8 module_vdc_Test_CRC(void)
{
	UINT8 CRC;
	rtd_outl(0xb8020048,0x00880100);	// 20130520 Mark: prevent the front end signal go through VDADC
	rtd_outl(0xb802004c,0x00000140);	// 20130520 Mark: prevent the front end signal go through VDADC

	
#ifdef CVBS_PatternGen_2D_NTSC_QC
	CRC = VDC_CVBS_PatternGen_Enable(0);  // NTSC, seven lines for QC
	if(CRC == _FAIL)
	{
	       while(CRC_error_count!=0)
	       	{
		   	CRC=VDC_CVBS_PatternGen_Enable(0);
			if (CRC_error_count>2)
				break;
	       	}
		if(CRC == _FAIL)
			{
		printk("the cvbs 2d ntsc QC crc is fail............. \n");
//		module_vdc_Bring_Up_screen_scripts();	// 20130516 Mark debug bring up screen for debug
		#if sirius_qc //jacky
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		#else
		rtd_outl(0xb8019608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8019794,~_BIT0,_BIT0);
		#endif
		return _FAIL;
			}
	}
#endif

#ifdef CVBS_PatternGen_2D_PAL_QC
//	#ifndef CONFIG_FT
	CRC = VDC_CVBS_PatternGen_Enable(1);  // PAL, seven lines for QC
	if(CRC == _FAIL)
    	{
 		while(CRC_error_count!=0)
	       	{
		   	CRC=VDC_CVBS_PatternGen_Enable(1);
			if (CRC_error_count>2)
				break;
	       	}

			if(CRC == _FAIL)
			{
            			printk("the cvbs 2d pal QC crc is fail............. \n");
//				module_vdc_Bring_Up_screen_scripts();	// 20130516 Mark debug bring up screen for debug
				#if sirius_qc //jacky
				rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
				rtd_maskl(0xb8003794,~_BIT0,_BIT0);			
				#else
				rtd_outl(0xb8019608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
				rtd_maskl(0xb8019794,~_BIT0,_BIT0);
				#endif

            			return _FAIL;
        		}          	
    	}
//	#endif
#endif

#ifdef CVBS_PatternGen_2D_NTSC_MP
	CRC= VDC_CVBS_PatternGen_Enable(2);  // NTSC, seven lines for QC
	if(CRC == _FAIL)
	{
	 	while(CRC_error_count!=0)
	       	{
		   	CRC=VDC_CVBS_PatternGen_Enable(2);
			if (CRC_error_count>2)
				break;
	       	}
		if(CRC == _FAIL)
			{
		printk("the cvbs 2d ntsc MP crc is fail............. \n");
//		module_vdc_Bring_Up_screen_scripts();	// 20130516 Mark debug bring up screen for debug
		#if sirius_qc //jacky
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);	
		#else
		rtd_outl(0xb8019608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8019794,~_BIT0,_BIT0);	
		#endif
		return _FAIL;
			}
	}
#endif

#ifdef CVBS_PatternGen_2D_PAL_MP
	CRC = VDC_CVBS_PatternGen_Enable(3);  // NTSC, seven lines for QC
	if(CRC==_FAIL)
	{
		 while(CRC_error_count!=0)
	       	{
		   	CRC=VDC_CVBS_PatternGen_Enable(3);
			if (CRC_error_count>2)
				break;
	       	}
		if(CRC == _FAIL)
			{		 
		printk("the cvbs 2d pal MP crc is fail............. \n");
//		module_vdc_Bring_Up_screen_scripts();	// 20130516 Mark debug bring up screen for debug
		#if sirius_qc //jacky
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		#else
		rtd_outl(0xb8019608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8019794,~_BIT0,_BIT0);
		#endif
		
		return _FAIL;
			}
	}
#endif

#ifdef Component_PatternGen_NTSC
    CRC = VDC_Component_PatternGen_Enable(0); // NTSC, six frames for MP
    if(CRC == _FAIL)
    {
        printk("the Component 2d ntsc crc is fail............. \n");
//	module_vdc_Bring_Up_screen_scripts();	// 20130516 Mark debug bring up screen for debug
	#if sirius_qc //jacky
	rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
	rtd_maskl(0xb8003794,~_BIT0,_BIT0);
	#else
	rtd_outl(0xb8019608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
	rtd_maskl(0xb8019794,~_BIT0,_BIT0);
	#endif
	
        return _FAIL;
    }
#endif
#ifdef Component_PatternGen_PAL
    CRC = VDC_Component_PatternGen_Enable(1); // PAL, six frames for MP
    if(CRC == _FAIL)
    {
        printk("the Component 2d palcrc is fail............. \n");
//	module_vdc_Bring_Up_screen_scripts();	// 20130516 Mark debug bring up screen for debug
		#if sirius_qc //jacky
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		#else
	rtd_outl(0xb8019608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
	rtd_maskl(0xb8019794,~_BIT0,_BIT0);
		#endif
	
        return _FAIL;
    }
#endif

#if 1
	dmsg("SV test crc...\n");

	CRC = VDC_SV_PatternGen_Enable(0);
	if( CRC == _FAIL)
	{
		while(CRC_error_count!=0)
		{
			CRC=VDC_SV_PatternGen_Enable(0);
			if (CRC_error_count>2)
				break;
		}
		if(CRC == _FAIL)
		{
			printk("the SV ntsc QC crc is fail............. \n");
			rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
			rtd_maskl(0xb8003794,~_BIT0,_BIT0);
			return _FAIL;
		}
	}

	CRC = VDC_SV_PatternGen_Enable(1);
	if( CRC == _FAIL)
	{
		printk("the SV PALI QC crc is fail............. \n");
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		return _FAIL;
	}

	CRC = VDC_SV_PatternGen_Enable(2);
	if( CRC == _FAIL)
	{
		printk("the SV ntsc MP crc is fail............. \n");
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		return _FAIL;
	}

	CRC = VDC_SV_PatternGen_Enable(3);
	if( CRC == _FAIL)
	{
		printk("the SV PALI MP crc is fail............. \n");
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		return _FAIL;
	}


	dmsg("start test scart crc...\n");
	CRC = VDC_SCART_PatternGen_Enable(0); // SCART TEST FOR NTSC QC
	if( CRC == _FAIL)
	{
		printk("the SCART ntsc QC crc is fail............. \n");
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		return _FAIL;
	}
	CRC = VDC_SCART_PatternGen_Enable(1); // SCART TEST FOR pal QC
	if( CRC == _FAIL)
	{
		printk("the SCART pal QC crc is fail............. \n");
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		return _FAIL;
	}
	CRC = VDC_SCART_PatternGen_Enable(2); // SCART TEST FOR NTSC mp
	if( CRC == _FAIL)
	{
		printk("the SCART ntsc mp crc is fail............. \n");
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		return _FAIL;
	}
	CRC = VDC_SCART_PatternGen_Enable(3); // SCART TEST FOR pal mp
	if( CRC == _FAIL)
	{
		printk("the SCART ntsc mp crc is fail............. \n");
		rtd_outl(0xb8003608,0x0000001c);		// select Y path (often sets C9 or 1B)				// AD_SW_CTRL0
		rtd_maskl(0xb8003794,~_BIT0,_BIT0);
		return _FAIL;
	}



#endif

/*
	CRC=VDC_CVBS_PatternGen_New_Crc1_Enable();
      if(CRC==_FAIL)
    {
        printk("the new crc1 is  fail............. \n");
        return _FAIL;
    }
     CRC=VDC_CVBS_PatternGen_New_Crc2_Enable();
      if(CRC==_FAIL)
    {
        printk("the new crc2 is  fail............. \n");
        return _FAIL;
    }
    */
	printk("[TEST_CRC] crc test OK \n");
    return _SUCCESS;
}

#ifdef Test_vdc_Test_DRF_BIst
UINT8  module_vdc_Test_DRF_BIst(void)
{

	UINT8  bist_done_drf_27;
	UINT8  bist_done_drf_dma_fifo;
	UINT8  bist_drf_start_pause;
	UINT8  bist_drf_fail_flag;
	UINT32 i;

	drvif_module_vdc_VDCReset();
	drvif_module_vdc_SoftReset();
///////////////////////////////  drf bist test  /////////////////////////
	rtd_outl(VDC_BIST_MODE_VADDR,0x00);	//0xb801_97a0 disable all bist modes
	udelay(100);

	rtd_outl(VDC_BIST_DRF_MODE_VADDR,0x1f);	//0xb801_97ac enable all drf_bist modes
	udelay(10000);
	
	if((UINT8)rtd_inl(VDC_BIST_DRF_PAUSE_VADDR)!=0x1f)	//wait drf bist pause
	{
		printk("drf bist pause1 is fail value==>%x \n", (UINT8)rtd_inl(VDC_BIST_DRF_PAUSE_VADDR));
		return _FAIL;
	}
	
	rtd_outl(VDC_BIST_DRF_RESUME_VADDR,0x1f);	//drf bist resume all on
	udelay(10);
	rtd_outl(VDC_BIST_DRF_RESUME_VADDR,0x00);	//drf bist resume all off	
	
	for(i=0;i<10;i++)
	{
		udelay(100);
	}

	if((UINT8)rtd_inl(VDC_BIST_DRF_PAUSE_VADDR)!=0x1f)	//wait drf bist pause
	{
		printk("drf bist pause2 is fail value==>%x \n", (UINT8)rtd_inl(VDC_BIST_DRF_PAUSE_VADDR));
		return _FAIL;
	}

	rtd_outl(VDC_BIST_DRF_RESUME_VADDR,0x1f);	//drf bist resume all on
	udelay(10);
	rtd_outl(VDC_BIST_DRF_RESUME_VADDR,0x00);	//drf bist resume all off

	for(i=0;i<10;i++)
	{
		udelay(100);
	}

	if((UINT8)rtd_inl(VDC_BIST_DRF_DONE_VADDR)!=0x1f)	//wait drf bist done
	{
		printk("drf bist done is fail value==>%x \n", (UINT8)rtd_inl(VDC_BIST_DRF_DONE_VADDR));
		return _FAIL;
	}

	for(i=0;i<10;i++)
	{
		udelay(100);
	}
	if((UINT8)rtd_inl(VDC_BIST_DRF_FAIL_VADDR))
	{
		printk("	drf bist fail~~~~~ ");
		return _FAIL;
	}

	printk("[TEST_DRF_BIST] DRF Bist test OK \n");

	return  _SUCCESS;
}

#endif


#ifdef Test_vdc_Test_Scart_Fsw_Adc
UINT8  module_vdc_Test_Scart_Fsw_Adc(void)
{
	UINT32 tmp;
	UINT32 i;
//	printk("[debug] TEST SCART FSW ADC\n");
	UINT32 fsw_value ;
	#if sirius_qc //jacky
	sys_pll_27x4_RBUS sys_pll_27x4_reg;	// 0_04dc
	sys_pll_27x4_reg.regValue = rtd_inl(CRT_SYS_PLL_27X4_VADDR);
	#else
	sys_pll_27x4_RBUS sys_pll_27x4_reg;	// 0_04dc
	sys_pll_27x4_reg.regValue = rtd_inl(SYSTEM_SYS_PLL_27X4_VADDR);
	#endif
	FSW_CTRL0_RBUS fsw_ctrl0_reg;	// 1_9610
	fsw_ctrl0_reg.regValue = rtd_inl(VDC_FSW_CTRL0_VADDR);
	FSW_CTRL2_RBUS fsw_ctrl2_reg;	// 1_9620
	fsw_ctrl2_reg.regValue = rtd_inl(VDC_FSW_CTRL2_VADDR);
	adc_power_RBUS adc_power_reg;	// 2_0000
	adc_power_reg.regValue = rtd_inl(ADC_ADC_POWER_VADDR);
	scart_ctrl1_RBUS scart_ctrl1_reg;	// 2_006c
	scart_ctrl1_reg.regValue = rtd_inl(ADC_SCART_CTRL1_VADDR);
	st_srst0_RBUS st_srst0_reg;		// 6_0030
	st_srst0_reg.regValue = rtd_inl(SYSTEM_ST_SRST0_VADDR);
	st_srst1_RBUS st_srst1_reg;		// 6_0034
	st_srst1_reg.regValue = rtd_inl(SYSTEM_ST_SRST1_VADDR);
	st_clken0_RBUS st_clken0_reg;		// 6_0040
	st_clken0_reg.regValue = rtd_inl(SYSTEM_ST_CLKEN0_VADDR);
	st_clken1_RBUS st_clken1_reg;		// 6_0044
	st_clken1_reg.regValue = rtd_inl(SYSTEM_ST_CLKEN1_VADDR);

#if 1
	#if sirius_qc //jacky
	sys_pll_27x4_reg.pll27x_yppadc_cko_en = 1;		// 0_04dc[13] PLL27x YPPADC output clock enable = 1
	sys_pll_27x4_reg.pll27x_yppadc_ck54m_en = 1;	// 0_04dc[12] PLL27x YPPADC 54MHz clock enable = 1
	#endif
	fsw_ctrl2_reg.scart_en = 1;			// 1_9620[7] enable SCART function
	adc_power_reg.adc_power_3 = 1;	// 2_0000[3] ADC Bandgap Power On 

	st_srst0_reg.rstn_i2c0_off = 1;		// 6_0030[6] Reset bit of I2C0_OFF (active low)
	st_srst0_reg.rstn_uart0_off = 1;		// 6_0030[5] Reset bit of UART0_OFF (active low)
	st_srst0_reg.rstn_iso_misc = 1;		// 6_0030[0] Reset bit of ISO_MISC (active low) (Only reset by power-on reset and external reset)
	st_srst1_reg.rstn_emcu_top = 1;		// 6_0034[10] Reset bit of EMCU Top (active low)
	st_srst1_reg.rstn_emcu_core = 1;	// 6_0034[9] Reset bit of EMCU Core (active low)
	st_srst1_reg.rstn_hdmi_det = 1;		// 6_0034[8] Reset bit of HDMI Clock Detection (active low)
	st_srst1_reg.rstn_cec = 1;			// 6_0034[7] Reset bit of CEC (active low)
	st_srst1_reg.rstn_syncp = 1;			// 6_0034[6] Reset bit of Standby Top SyncProcessor (active low)
	st_srst1_reg.rstn_irda = 1;			// 6_0034[2] Reset bit of IRDA (active low)
	st_srst1_reg.rstn_ddc = 1;			// 6_0034[1] Reset bit of DDC (active low)
	st_srst1_reg.rstn_lsadc = 1;			// 6_0034[0] Reset bit of LSADC (active low)

	st_clken0_reg.clken_i2c0_off = 1;		// 6_0040[6] Clock enable bit for I2C0_OFF
	st_clken0_reg.clken_uart0_off = 1;	// 6_0040[5] Clock enable bit for UART0_OFF
	st_clken0_reg.clken_irda_off= 1;		// 6_0040[4] Clock enable bit for IRDA _OFF
	st_clken0_reg.clken_iso_misc = 1;	// 6_0040[0] Clock enable bit for ISO_MISC
	st_clken1_reg.clken_emcu_core = 1;	// 6_0044[9] Clock enable bit for EMCU Core
	st_clken1_reg.clken_hdmi_det = 1;	// 6_0044[8] Clock enable bit for HDMI Clock Detection
	st_clken1_reg.clken_cec = 1;		// 6_0044[7] Clock enable bit for CEC
	st_clken1_reg.clken_syncp = 1;		// 6_0044[6] Clock enable bit for Standby Top SyncProcessor
	st_clken1_reg.clken_irda = 1;		// 6_0044[2] Clock enable bit for IRDA
	st_clken1_reg.clken_ddc = 1;		// 6_0044[1] Clock enable bit for DDC
	st_clken1_reg.clken_lsadc = 1;		// 6_0044[0] Clock enable bit for LSADC
#endif

	rtd_maskl(0xb8033080,~_BIT0,_BIT0);	// 3_3080[0] ADC2X global power on	= 1 (ADC2X_POW VDACIFADC_AIF_TOP.doc)
	rtd_maskl(0xb8033080,~_BIT12,_BIT12);	// 3_3080[12] ADC2X input cm power on = 1 (ADC2X_POW VDACIFADC_AIF_TOP.doc)
	rtd_maskl(0xb8033080,~_BIT8,_BIT8);	// 3_3080[8] ADC2X power on	= 1 (ADC2X_POW VDACIFADC_AIF_TOP.doc)
	rtd_maskl(ADC_SCART_CTRL1_VADDR,~_BIT0,_BIT0);	// 2_006c[0] SCART 3bit ADC Power on

	tmp = scart_ctrl1_reg.vdadc_sct_ctrl;	
	scart_ctrl1_reg.vdadc_sct_ctrl = tmp & (~_BIT3);	// 2_006c[3] SCART INPUT SELECT, 0:RGBSW0 
	tmp = scart_ctrl1_reg.vdadc_sct_ctrl;
	scart_ctrl1_reg.vdadc_sct_ctrl = tmp & (~_BIT2);	// 2_006c[2] SCART INPUT LPF ENABLE; 1: LPF  0:bypass
	fsw_ctrl0_reg.aa3_en = 1;	// 1_9610[7] 1-2-1 AA filter for 3 bit ADC input
	tmp = scart_ctrl1_reg.vdadc_sct_ctrl;
	scart_ctrl1_reg.vdadc_sct_ctrl = tmp & (~_BIT5);	// 2_006c[5:4] SCART SOURCE CURRENT SELECT = 01: 20u
	tmp = scart_ctrl1_reg.vdadc_sct_ctrl;
	scart_ctrl1_reg.vdadc_sct_ctrl = tmp & (~_BIT4) | (_BIT4);	// 2_006c[5:4] SCART SOURCE CURRENT SELECT = 01: 20u
	tmp = scart_ctrl1_reg.vdadc_sct_ctrl;
	scart_ctrl1_reg.vdadc_sct_ctrl = tmp & (~_BIT0) | (_BIT0);	// 2_006c[0] SCART ADC power on = 1
	#if sirius_qc //jacky
	rtd_outl(CRT_SYS_PLL_27X4_VADDR,sys_pll_27x4_reg.regValue);	// 0_04dc
	#else
	rtd_outl(SYSTEM_SYS_PLL_27X4_VADDR,sys_pll_27x4_reg.regValue);	// 0_04dc
	#endif
	rtd_outl(VDC_FSW_CTRL0_VADDR,fsw_ctrl0_reg.regValue);		// 1_9610
	rtd_outl(VDC_FSW_CTRL2_VADDR,fsw_ctrl2_reg.regValue);		// 1_9620
	rtd_outl(ADC_ADC_POWER_VADDR,adc_power_reg.regValue);	// 2_0000
	rtd_outl(ADC_SCART_CTRL1_VADDR,scart_ctrl1_reg.regValue);	// 2_006c
	rtd_outl(SYSTEM_ST_SRST0_VADDR,st_srst0_reg.regValue);		// 6_0030
	rtd_outl(SYSTEM_ST_SRST1_VADDR,st_srst1_reg.regValue);		// 6_0034
	rtd_outl(SYSTEM_ST_CLKEN0_VADDR,st_clken0_reg.regValue);	// 6_0040
	rtd_outl(SYSTEM_ST_CLKEN1_VADDR,st_clken1_reg.regValue);	// 6_0044
	rtd_outl(0xb8000910,0x00000003);	// 0_0910[7:0] Testpin_mux = 0x3: debug of top MUX for VD	// MAIN_TEST_PIN_CTRL Main_Magellan_PinMux.doc
	rtd_outl(0xb80008b4,0xDD000003);	// 0_08b4 make sure SCART_FSW0, FSW1 are used as vd input (SCART_FSW_CFG PinMux.doc)
	rtd_outl(0xb800084c,0xf0f0f0f0);	// 0_084c[7:4] GPIO_79_ps = F: MIS_GPIO_bit79<I/O>; E: test_en_bit5<O>	// GPIO_CFG_19 Main_Magellan_PinMux.doc
	rtd_outl(0xb800086c,0xf0f0f0f0);	// 0_086c[15:12] GPIO_142_ps = F: MIS_GPIO_bit142<I/O>	// GPIO_CFG_27 Main_Magellan_PinMux.doc
//	printk("[VDC][QC][SCART]SCART write back\n" );
	udelay(2000);

#if 1	// 2013.03/14 Mark: test FSW0 path to SCART 3-bit ADC
//==== analysis of FSW0 input High value ====	
//	printk("[VDC][QC][SCART][FSW] now turn on 3bit ADC input\n");

	scart_ctrl1_reg.regValue = rtd_inl(ADC_SCART_CTRL1_VADDR);
	tmp = scart_ctrl1_reg.vdadc_sct_ctrl;
	scart_ctrl1_reg.vdadc_sct_ctrl = (tmp | (~_BIT3));	// 2_006c[3] SCART INPUT SELECT (1: REGSW1  0:RGBSW0)
	rtd_outl(ADC_SCART_CTRL1_VADDR, scart_ctrl1_reg.regValue);	// 2_006c
	udelay(2000);


	rtd_outl(0xb800081c,rtd_inl(0xb800081c)|_BIT20|_BIT21|_BIT22|_BIT23);  //GPIO29 assign=GPIO
	rtd_outl(0xb801bc00,rtd_inl(0xb801bc00)|_BIT29);	// GPIO29 assign=output
	rtd_outl(0xb801bc18,rtd_inl(0xb801bc18)|_BIT29);	// GPIO29 output=High
//	rtd_outl(0xb801bc08,0x00008000);	// 0_bc08[15] GPIO[95:64] direction configuration [15] = 0:GPI; 1:GPO	// GP2DIR Magellan_DesignSpec_MISC.doc
//	rtd_outl(0xb801bc10,0x00000000);	// 0_bc10[14 GPIO[159:128] direction configuration [14] = 0:GPI; 1:GPO	// GP4DIR Magellan_DesignSpec_MISC.doc

//	rtd_outl(0xb801bc20,0x00008000);	// 0_bc20[15] GPIO[95:64] data output [15] = _BIT15: set GPIO_bit79 as High	// GP2DATO Magellan_DesignSpec_MISC.doc
//	rtd_outl(0xb801bc28,0x00004000);	// 0_bc20[14 GPIO[159:128] data output [14] = _BIT14: set GPIO_bit142 as High	// GP4DATO Magellan_DesignSpec_MISC.doc

	udelay(10000);					// this delay can't be too short, or the GPO won't be high
	

	for(i =0; i<100; i++)
	{
		fsw_value = (rtd_inl(VDC_FSW_INPUT_STATUS_VADDR) & 0xf);	// 1_9640[2:0] FSW 3bit ADC input value
		if(fsw_value == 0x7)
			break;

		udelay(500);
	}

	if(fsw_value != 0x07)
	{
		printk("[VDC][QC][SCART][FSW] the input is high, vdc FSW0 to SCART 3bit ADC is fail\n");
		printk("[VDC][QC][SCART][FSW] FSW0 to SCART 3bit ADC is fail, the adc value==>%x\n",fsw_value);
		return _FAIL;
	}
	else
	{
		printk("[VDC][QC][SCART][H] FSW0 to SCART 3bit ADC is OK with value: %d\n", fsw_value);
	}


//==== analysis of FSW0 input Low value ====	
	printk("[VDC][QC][SCART][FSW] now turn off 3bit ADC input\n");

	rtd_outl(0xb800081c,rtd_inl(0xb800081c)|_BIT20|_BIT21|_BIT22|_BIT23);  //GPIO29 assign=GPIO
	rtd_outl(0xb801bc00,rtd_inl(0xb801bc00)|_BIT29);	// GPIO29 assign=output
	rtd_outl(0xb801bc18,rtd_inl(0xb801bc18)&(~_BIT29));	// GPIO29 output=High
	udelay(10000);					// this delay can't be too short, or the GPO won't be low
	
	for(i =0; i<100; i++)
	{
		fsw_value = (rtd_inl(VDC_FSW_INPUT_STATUS_VADDR) & 0xf);	// 1_9640[2:0] FSW 3bit ADC input value
		if(fsw_value == 0x0)
			break;
		udelay(500);
	}

	if(fsw_value != 0x00)
	{
		printk("[VDC][QC][SCART][FSW] the input is low, vdc FSW0 to SCART 3bit ADC is fail\n");
		printk("[VDC][QC][SCART][FSW] FSW0 to SCART 3bit ADC is fail, the adc value==>%x\n",fsw_value);
		return _FAIL;
	}
	else
	{
		printk("[VDC][QC][SCART][L] FSW0 to SCART 3bit ADC is OK with value: %d\n", fsw_value);
	}

	printk("[Test_SCART_FSW_ADC] ADC FSW test OK\n");
#endif

	return  _SUCCESS;
}
#endif

#ifdef Test_vdc_Test_FIFO
UINT8 module_vdc_Test_FIFO(void)
{

	UINT32 fifo_value;
	UINT32 testi = 0;

	// start settings //
	#if 0
	sys_pll_27x2_RBUS sys_pll_27x2_reg;
	sys_pll_27x2_reg.regValue = rtd_inl(CRT_SYS_PLL_27X2_VADDR);
	sys_pll_27x2_reg.pll27x_ps_54m_delay = 0x2;
	rtd_outl(CRT_SYS_PLL_27X2_VADDR, sys_pll_27x2_reg.regValue);

	sys_pll_27x3_RBUS sys_pll_27x3_reg;
	sys_pll_27x3_reg.regValue = rtd_inl(CRT_SYS_PLL_27X3_VADDR);
	sys_pll_27x3_reg.pll27x_ps_div2 = 0x0;
	rtd_outl(CRT_SYS_PLL_27X3_VADDR, sys_pll_27x3_reg.regValue);
	#endif


	drvif_module_vdc_VDCReset();	// 2013.1/27 done
	drvif_module_vdc_SoftReset();	// 2013.1/27 done

	udelay(4000);//ps_updn_swap

	FIFO_CTRL_RBUS fifo_ctrl_reg;
	fifo_ctrl_reg.regValue = rtd_inl(VDC_FIFO_CTRL_VADDR);	// 1_9758
	//fifo_ctrl_reg.ps_updn_swap = 1;	// 1_9768[2] ps_updn_swap = 1:enable	// Mark debug 20130508
	rtd_outl(VDC_FIFO_CTRL_VADDR, fifo_ctrl_reg.regValue);

	udelay(4000);

	//rtd_outl(VDC_MISC_CONTROL_VADDR,0x0008017f);	// 1_9764 enable VDC phase swallow VCO = 540M
	rtd_outl(VDC_MISC_CONTROL_VADDR,0x0008007F);		// bit[9:8]=01, select Select the VCO freq = 432M			// MISC_CONTROL

	udelay(4000);

	// settings done //

	rtd_outl(VDC_FIFO_STATUS_VADDR,0x0000000f);	// 1_975c fifo

	udelay(4000);

	AVOUT_FIFO_STATUS_RBUS avout_fifo_status_reg;
	avout_fifo_status_reg.regValue = rtd_inl(VDC_AVOUT_FIFO_STATUS_VADDR);	// 1_9084
	avout_fifo_status_reg.output_fifo_full = 1;	// [26] default = 0, Write 1 to clear. Clear after read
	avout_fifo_status_reg.output_fifo_empty = 1;	// [25] default = 0, Write 1 to clear. Clear after read
	avout_fifo_status_reg.avout_fifo_status_full = 1;	// [1] default = 0, Write 1 to clear. Clear after read
	avout_fifo_status_reg.avout_fifo_status_empty = 1;	// [0] default = 0, Write 1 to clear. Clear after read
	rtd_outl(VDC_AVOUT_FIFO_STATUS_VADDR, avout_fifo_status_reg.regValue);

	udelay(4000);

	FIFO_DEPTH_MIN_STATUS_RBUS fifo_depth_min_status_reg;
	fifo_depth_min_status_reg.regValue = rtd_inl(VDC_FIFO_DEPTH_MIN_STATUS_VADDR);	// 1_9768
	fifo_depth_min_status_reg.fifo_depth_min_clr = 1;	
	rtd_outl(VDC_FIFO_DEPTH_MIN_STATUS_VADDR, fifo_depth_min_status_reg.regValue);

	udelay(4000);

	FIFO_DEPTH_MAX_STATUS_RBUS fifo_depth_max_status_reg;
	fifo_depth_max_status_reg.regValue = rtd_inl(VDC_FIFO_DEPTH_MAX_STATUS_VADDR);	// 1_976c
	fifo_depth_max_status_reg.fifo_depth_max_clr = 1;
	rtd_outl(VDC_FIFO_DEPTH_MAX_STATUS_VADDR, fifo_depth_max_status_reg.regValue);

	udelay(4000);

	printk("FIFO_STATUS debug 1st\n");
	printk("%x = %08X\n", CRT_SYS_PLL_27X1_VADDR, rtd_inl(CRT_SYS_PLL_27X1_VADDR));	// 0_04d0
	printk("%x = %08X\n", CRT_SYS_PLL_27X2_VADDR, rtd_inl(CRT_SYS_PLL_27X2_VADDR));	// 0_04d4
	printk("%x = %08X\n", CRT_SYS_PLL_27X3_VADDR, rtd_inl(CRT_SYS_PLL_27X3_VADDR));	// 0_04d8
	printk("%x = %08X\n", CRT_SYS_PLL_27X4_VADDR, rtd_inl(CRT_SYS_PLL_27X4_VADDR));	// 0_04dc
	printk("%x = %08X\n", VDC_AVOUT_FIFO_STATUS_VADDR, rtd_inl(VDC_AVOUT_FIFO_STATUS_VADDR));	// 1_9084
	printk("%x = %08X\n", VDC_FIFO_CTRL_VADDR, rtd_inl(VDC_FIFO_CTRL_VADDR));	// 1_9758
	printk("%x = %08X\n", VDC_FIFO_STATUS_VADDR, rtd_inl(VDC_FIFO_STATUS_VADDR));	// 1_975c
	printk("%x = %08X\n", VDC_MISC_CONTROL_VADDR, rtd_inl(VDC_MISC_CONTROL_VADDR));	// 1_9764
	printk("%x = %08X\n", VDC_FIFO_DEPTH_MIN_STATUS_VADDR, rtd_inl(VDC_FIFO_DEPTH_MIN_STATUS_VADDR));	// 1_9768
	printk("%x = %08X\n", VDC_FIFO_DEPTH_MAX_STATUS_VADDR, rtd_inl(VDC_FIFO_DEPTH_MAX_STATUS_VADDR));	// 1_976c

	// write clear register again before reading //

	rtd_outl(VDC_FIFO_STATUS_VADDR,0x0000000f);	// 1_975c fifo	
	udelay(4000);
	
	fifo_value = rtd_inl(VDC_FIFO_STATUS_VADDR);	// 1_975c fifo
	fifo_value = fifo_value & 0x03;
	if(fifo_value)
	{
		printk("FIFO_STATUS:975c fail==>%x\n",fifo_value);

		// 20130510 Mark: double check the FIFO status ============
		rtd_outl(VDC_FIFO_STATUS_VADDR,0x0000000f);	// 1_975c fifo
		udelay(4000);//1000

		fifo_depth_min_status_reg.regValue = rtd_inl(VDC_FIFO_DEPTH_MIN_STATUS_VADDR);	// 1_9768
		fifo_depth_min_status_reg.fifo_depth_min_clr = 1;	
		rtd_outl(VDC_FIFO_DEPTH_MIN_STATUS_VADDR, fifo_depth_min_status_reg.regValue);
		udelay(4000);
		printk("%x = %08X\n", VDC_FIFO_DEPTH_MIN_STATUS_VADDR, rtd_inl(VDC_FIFO_DEPTH_MIN_STATUS_VADDR));	// 1_9768

		fifo_depth_max_status_reg.regValue = rtd_inl(VDC_FIFO_DEPTH_MAX_STATUS_VADDR);	// 1_976c
		fifo_depth_max_status_reg.fifo_depth_max_clr = 1;
		rtd_outl(VDC_FIFO_DEPTH_MAX_STATUS_VADDR, fifo_depth_max_status_reg.regValue);
		udelay(4000);
		printk("%x = %08X\n", VDC_FIFO_DEPTH_MAX_STATUS_VADDR, rtd_inl(VDC_FIFO_DEPTH_MAX_STATUS_VADDR));	// 1_976c
		// ==========================================
		
		return _FAIL;
	}
	fifo_value = rtd_inl(VDC_FIFO_DEPTH_MIN_STATUS_VADDR);	// 1_9768 fifo min
	fifo_value = fifo_value & 0x100;	// 1_9768[8] FIFO_depth_min_clr = 1
	if(fifo_value)
	{
		printk("FIFO_DEPTH_MIN_STATUS:9768 fail==>%x\n",fifo_value);
		return _FAIL;
	}
	fifo_value = rtd_inl(VDC_FIFO_DEPTH_MAX_STATUS_VADDR);	// 1_976c fifo max
	fifo_value = fifo_value & 0x100;	// 1_976c[8] FIFO_depth_max_clr = 1
	if(fifo_value)
	{
		printk("FIFO_DEPTH_MAX_STATUS:976c fail==>%x\n",fifo_value);
		return _FAIL;
	}
	printk("[TEST_FIFO] FIFO test OK\n");
	return _SUCCESS;
}
#endif

BOOL QC_Verifier_VDC_CVBS_VIN9(void)
{
	UINT32 i,temp;
	drvif_module_vdc_Initial();	// 2013.02/21 Mark: move initialization behaviors to the Initial function

#if 0	// 2013.02/27 Mark debug Set SV Path for YC swap
	module_vdc_SetInput_YC(VIDEO_INPUT10, VIDEO_GNDA2, VIDEO_INPUT13, VIDEO_GNDA2, VIDEO_SV_SWAP);
	module_vdc_Print_Registers(VIDEO_INPUT10, VIDEO_GNDA2, 1000);
	udelay(800000000);
#endif

#if 0// 2013.02/27 Mark debug Set SV Path for not YC swap
	module_vdc_SetInput_YC(VIDEO_INPUT9, VIDEO_GNDA0, VIDEO_INPUT8, VIDEO_GNDY1, VIDEO_SV_NORMAL);
	module_vdc_Print_Registers(VIDEO_INPUT9, VIDEO_GNDA0, 1000);
#endif

#if 0	// 2013.02/25 Mark: debug load AV_13P script
#include "case13_CVBS_VIN9_fs_fhd/AV_13P.tbl"
	udelay(200000);
#endif

#if 0	// 2013.02/27 Mark: 0P ~ 14P switch debug

	for (i = 0; i < 1; i++)
	{
		int display_time = 2000000;
		int adc_display_time = 100;
#ifdef ADC_Path0
//#include "case13_CVBS_VIN9_fs_fhd/AV_0P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT0, VIDEO_GNDB);
		module_vdc_Print_Registers(VIDEO_INPUT0, VIDEO_GNDB,display_time);
#endif

#ifdef ADC_Path1
//#include "case13_CVBS_VIN9_fs_fhd/AV_1P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT1, VIDEO_GNDG);
		module_vdc_Print_Registers(VIDEO_INPUT1, VIDEO_GNDG,display_time);
#endif

#ifdef ADC_Path2
//#include "case13_CVBS_VIN9_fs_fhd/AV_2P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT2, VIDEO_GNDR);
		module_vdc_Print_Registers(VIDEO_INPUT2, VIDEO_GNDR,display_time);
#endif

#ifdef ADC_Path3
//#include "case13_CVBS_VIN9_fs_fhd/AV_3P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT3, VIDEO_GNDY0);
		module_vdc_Print_Registers(VIDEO_INPUT3, VIDEO_GNDY0,display_time);
#endif

#ifdef ADC_Path4
//#include "case13_CVBS_VIN9_fs_fhd/AV_4P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT4, VIDEO_GNDY0);
		module_vdc_Print_Registers(VIDEO_INPUT4, VIDEO_GNDY0,display_time);
#endif

#ifdef ADC_Path5
//#include "case13_CVBS_VIN9_fs_fhd/AV_5P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT5, VIDEO_GNDY0);
		module_vdc_Print_Registers(VIDEO_INPUT5, VIDEO_GNDY0,display_time);
#endif

#ifdef ADC_Path6
//#include "case13_CVBS_VIN9_fs_fhd/AV_6P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT6, VIDEO_GNDY1);
		module_vdc_Print_Registers(VIDEO_INPUT6, VIDEO_GNDY1,display_time);
#endif

#ifdef ADC_Path7
//#include "case13_CVBS_VIN9_fs_fhd/AV_7P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT7, VIDEO_GNDY1);
		module_vdc_Print_Registers(VIDEO_INPUT7, VIDEO_GNDY1,display_time);
#endif

#ifdef ADC_Path8
//		#include "case13_CVBS_VIN9_fs_fhd/AV_8P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT8, VIDEO_GNDY1);
		module_vdc_Print_Registers(VIDEO_INPUT8, VIDEO_GNDY1,display_time);
#endif

#ifdef ADC_Path9
//#include "case13_CVBS_VIN9_fs_fhd/AV_9P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT9, VIDEO_GNDA0);
		module_vdc_Print_Registers(VIDEO_INPUT9, VIDEO_GNDA0,display_time);
		module_vdc_Print_ADC_Value(adc_display_time);
#endif

#ifdef ADC_Path10
//#include "case13_CVBS_VIN9_fs_fhd/AV_10P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT10, VIDEO_GNDA0);
		module_vdc_Print_Registers(VIDEO_INPUT10, VIDEO_GNDA0,display_time);
		module_vdc_Print_ADC_Value(adc_display_time);
#endif

#ifdef ADC_Path11
//#include "case13_CVBS_VIN9_fs_fhd/AV_11P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT11, VIDEO_GNDA0);
		module_vdc_Print_Registers(VIDEO_INPUT11, VIDEO_GNDA0,display_time);
		module_vdc_Print_ADC_Value(adc_display_time);
#endif

#ifdef ADC_Path13
//#include "case13_CVBS_VIN9_fs_fhd/AV_13P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT13, VIDEO_GNDA0);
		module_vdc_Print_Registers(VIDEO_INPUT13, VIDEO_GNDA0,display_time);
		module_vdc_Print_ADC_Value(adc_display_time);

#endif

#ifdef ADC_Path14
//#include "case13_CVBS_VIN9_fs_fhd/AV_14P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT14, VIDEO_GNDA0);
		module_vdc_Print_Registers(VIDEO_INPUT14, VIDEO_GNDA0,display_time);
		module_vdc_Print_ADC_Value(adc_display_time);
#endif

#ifdef ADC_Path12
//#include "case13_CVBS_VIN9_fs_fhd/AV_12P.tbl"
		module_vdc_SetInput_Y(VIDEO_INPUT12, VIDEO_GNDA0);
//		module_vdc_Print_Registers(VIDEO_INPUT12, VIDEO_GNDA0,display_time);
//		module_vdc_Print_ADC_Value(adc_display_time);
#endif
	}
#endif
	
	for(i=0; i<100; i++)
	{
		temp=rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR);
		if(0x30E == temp)	
		{
			#if 1
			printk("Reg b8003008[8:0] = 0x%02x\n @ %d", rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR), i);
			#else
			printk("Reg b8019008[8:0] = 0x%02x\n @ %d", rtd_inl(VDC_VIDEO_STATUS_REG1_VADDR), i);	
			#endif
			return  _SUCCESS;
		}
//		udelay(200000);
		udelay(1000);
	}
	return _FAIL;
}

UINT8 module_vdc_tst_Open(void)
{
		printk("[VDC] module_vdc_tst_Open\n");

#if 1
#ifdef Test_vdc_PathSelect
#ifdef vd_show_message
	printk("Test_vdc_PathSelect\n");
#endif

#if 0	// debug
	printk("av_mode = %x	rtd_outl(0x%x, 0x%08x);\n", _PALI, VDC_MODE_DETECTION_STATUS_VADDR, rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR));
#endif

	if(module_vdc_PathSelect()!=_SUCCESS)
	{
#ifdef vd_show_message
		printk("VD_Test_Input_Signal is fail\n");
#endif

#if 1	// debug
		printk("av_mode = %x	rtd_outl(0x%x, 0x%08x);\n", _PALI, VDC_MODE_DETECTION_STATUS_VADDR, rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR));
#endif

		return _FAIL;
	}
#endif
#endif

//------------------------------------------------------

#if 1
#ifdef Test_vdc_Test_Scart_Fsw_Adc
#ifdef vd_show_message
	printk("Test_vdc_Test_Scart_Fsw_Adc\n");
#endif
 	if(module_vdc_Test_Scart_Fsw_Adc()!=_SUCCESS)
 	{
#ifdef vd_show_message
		printk("VD_Test_Scart_Fsw_Adc is fail\n");
#endif
		return _FAIL;
	}
	else
	{
#ifdef vd_show_message
		printk("VD_Test_Scart_Fsw_Adc  is  ok  \n");
#endif
	}
#endif
#endif

//------------------------------------------------------

#if 1
#ifdef Test_vdc_Test_Memory
#ifdef vd_show_message
	printk("Test_vdc_Test_Memory\n");
#endif
	if(module_vdc_Test_Memory()!=_SUCCESS)
	{
#ifdef vd_show_message
		printk("VD_Test_Memory is fail\n");
#endif
		return _FAIL;
	}
#endif
#endif

//------------------------------------------------------

#if 1 //jacky_tmp_ignore
#ifdef Test_vdc_Test_BIst
#ifdef vd_show_message
	printk("Test_vdc_Test_BIst\n");
#endif
	if(module_vdc_Test_BIst()!=_SUCCESS)
	{
#ifdef vd_show_message
		printk("VD_Test_BIst is fail\n");
#endif
		return _FAIL;
	}
 #endif
 #endif

//------------------------------------------------------

#if 1
#ifdef  Test_vdc_Test_CRC
#ifdef vd_show_message
	printk("Test_vdc_Test_CRC\n");
#endif
	if(module_vdc_Test_CRC()!=_SUCCESS)
	{
#ifdef vd_show_message
		printk("VD_Test_crc is fail\n");
#endif
		return _FAIL;
	}
#endif
 #endif
//------------------------------------------------------

#if 1
#ifdef Test_vdc_Test_DRF_BIst
#ifdef vd_show_message
	printk("Test_vdc_Test_DRF_BIst\n");
#endif
	if(module_vdc_Test_DRF_BIst()!=_SUCCESS)
	{
#ifdef vd_show_message
		printk("VD_Test_DRF_BIst is fail\n");
#endif
		return _FAIL;
	}
 #endif
//	add frequency offset
	rtd_outl(VDC_HSYNC_DTO_INC_VADDR,0xa0606560);
 #endif

//------------------------------------------------------

#if 1 
#ifdef Test_vdc_Test_FIFO
#ifdef vd_show_message
	printk("Test_vdc_Test_FIFO\n");
#endif
	if(module_vdc_Test_FIFO()!=_SUCCESS)
	{
		printk("VD_Test_FIFO is fail\n");
		return _FAIL;
	}
#endif
#endif
 
	return  _SUCCESS;
}


void module_vdc_crt_clock_setting(void)
{
	soft_reset2_RBUS soft_reset2_reg;
	soft_reset3_RBUS soft_reset3_reg;
	clock_enable1_RBUS clock_enable1_reg;
	group1_ck_en_RBUS group1_ck_en_reg;
	group1_ck_sel_RBUS group1_ck_sel_reg;
	sys_pll_27x1_RBUS sys_pll_27x1_reg;
	sys_pll_27x2_RBUS sys_pll_27x2_reg;
	sys_pll_27x3_RBUS sys_pll_27x3_reg;
	sys_pll_27x4_RBUS sys_pll_27x4_reg;

	soft_reset2_reg.regValue = rtd_inl(CRT_SOFT_RESET2_VADDR);
	soft_reset3_reg.regValue = rtd_inl(CRT_SOFT_RESET3_VADDR);
	clock_enable1_reg.regValue = rtd_inl(CRT_CLOCK_ENABLE1_VADDR);
	group1_ck_en_reg.regValue = rtd_inl(CRT_GROUP1_CK_EN_VADDR);
	group1_ck_sel_reg.regValue = rtd_inl(CRT_GROUP1_CK_SEL_VADDR);
	sys_pll_27x1_reg.regValue = rtd_inl(CRT_SYS_PLL_27X1_VADDR);
	sys_pll_27x2_reg.regValue = rtd_inl(CRT_SYS_PLL_27X2_VADDR);
	sys_pll_27x3_reg.regValue = rtd_inl(CRT_SYS_PLL_27X3_VADDR);
	sys_pll_27x4_reg.regValue = rtd_inl(CRT_SYS_PLL_27X4_VADDR);

	soft_reset2_reg.rstn_atvin = 0x1;//Reset bit [16] RSTN_ATVIN [17]RSTN_ATVIN2
	soft_reset2_reg.rstn_atvin2 = 0x1;//Reset bit [16] RSTN_ATVIN [17]RSTN_ATVIN2
	soft_reset3_reg.rstn_vdec = 0x1;//Reset bit [19] RSTN_VDEC Reset bit of  Video Decode (active low) [4] RSTN_APLL_ADC Reset bit of APLL_ADC [10] RSTN_VDEC2
	soft_reset3_reg.rstn_vdec2 = 0x1;//Reset bit [19] RSTN_VDEC Reset bit of  Video Decode (active low) [4] RSTN_APLL_ADC Reset bit of APLL_ADC [10] RSTN_VDEC2
	soft_reset3_reg.rstn_apll_adc = 0x1;//Reset bit [19] RSTN_VDEC Reset bit of  Video Decode (active low) [4] RSTN_APLL_ADC Reset bit of APLL_ADC [10] RSTN_VDEC2
	clock_enable1_reg.clken_vdec = 0x1;//[26] CLKEN_VDEC
	group1_ck_en_reg.clken_atvin_vd = 0x1;//Clock enable bit [27]Clock enable bit for ATV Input Control of Video Decoder [24] Clock enable bit for APLL_ADC
	group1_ck_en_reg.clken_apll_adc = 0x1;//Clock enable bit [27]Clock enable bit for ATV Input Control of Video Decoder [24] Clock enable bit for APLL_ADC
	group1_ck_sel_reg.atvin_clk_sel = 0x1;//ATVIN_CLK_SEL[17], 0x0: IFD, 0x1: VD
	//group1_ck_sel_reg.atvin_vd_clk_sel = 0;
	sys_pll_27x1_reg.pll27x_m = 0xE;//PLL27X_M[6:0] = 0x0E
	sys_pll_27x2_reg.pll27x_ps_54m_delay = 0x2;//	PLL27x phase swallow delay cycle select (to generate 54M),	00: use when VCO=324M 01: use when VCO=648M10: use when VCO=432M, 11: use when VCO=540M
	sys_pll_27x3_reg.pll27x_ps_div2 = 0x0;//	PLL27x phase swallow 648M mode, 0: normal mode, used when VCO=540,324,432M
	sys_pll_27x4_reg.pll_l2h_cml_pow = 0x1;//[25]PLL_L2H_CML_POW = 1[12] PLL27X_YPPADC_CK54M_EN = 0; for Y [13]pll27x_yppadc_cko_en = 1 [17:16] = 0x1 01: divide by 4 (use when VCO=432MHz)
	sys_pll_27x4_reg.pll27x_yppadc_cko_en = 0x1;//[25]PLL_L2H_CML_POW = 1[12] PLL27X_YPPADC_CK54M_EN = 0; for Y [13]pll27x_yppadc_cko_en = 1 [17:16] = 0x1 01: divide by 4 (use when VCO=432MHz)
	sys_pll_27x4_reg.pll27x_ck108m_div = 0x1;

	rtd_outl(CRT_SOFT_RESET2_VADDR, soft_reset2_reg.regValue);	// 0_0004
	rtd_outl(CRT_SOFT_RESET3_VADDR, soft_reset3_reg.regValue);	// 0_0008
	rtd_outl(CRT_CLOCK_ENABLE1_VADDR, clock_enable1_reg.regValue);	// 0_000c
	rtd_outl(CRT_GROUP1_CK_EN_VADDR, group1_ck_en_reg.regValue);	// 0_0014
	rtd_outl(CRT_GROUP1_CK_SEL_VADDR, group1_ck_sel_reg.regValue);	// 0_0018
	rtd_outl(CRT_SYS_PLL_27X1_VADDR, sys_pll_27x1_reg.regValue);	// 0_0240
	rtd_outl(CRT_SYS_PLL_27X2_VADDR, sys_pll_27x2_reg.regValue);    //0_0244
	rtd_outl(CRT_SYS_PLL_27X3_VADDR, sys_pll_27x3_reg.regValue);    //0_0244
	rtd_outl(CRT_SYS_PLL_27X4_VADDR, sys_pll_27x4_reg.regValue);	// 0_024c

	//power on pll 27x
	sys_pll_27x3_reg.regValue = rtd_inl(CRT_SYS_PLL_27X3_VADDR);
	sys_pll_27x3_reg.pll27x_pow = 0x1;
	sys_pll_27x3_reg.pll27x_rstb = 0x1;
	sys_pll_27x3_reg.pll27x_vcorstb = 0x1;
	sys_pll_27x3_reg.pll27x_ps_en = 0x1;
	//rtd_outl(CRT_SYS_PLL_27X3_VADDR, 0x00000000);      //Power off and rst PLL27x
	rtd_outl(CRT_SYS_PLL_27X3_VADDR, sys_pll_27x3_reg.regValue);//0_0248	   //Power on PLL27x
	
	dmsg("\n%s:\n",__FUNCTION__);
	dmsg("0_0004:0x%x\n",rtd_inl(CRT_SOFT_RESET2_VADDR));
	dmsg("0_0008:0x%x\n",rtd_inl(CRT_SOFT_RESET3_VADDR));
	dmsg("0_000c:0x%x\n",rtd_inl(CRT_CLOCK_ENABLE1_VADDR));
	dmsg("0_0014:0x%x\n",rtd_inl(CRT_GROUP1_CK_EN_VADDR));
	dmsg("0_0018:0x%x\n",rtd_inl(CRT_GROUP1_CK_SEL_VADDR));
	dmsg("0_0240:0x%x\n",rtd_inl(CRT_SYS_PLL_27X1_VADDR));
	dmsg("0_0248:0x%x\n",rtd_inl(CRT_SYS_PLL_27X3_VADDR));
	dmsg("0_024c:0x%x\n",rtd_inl(CRT_SYS_PLL_27X4_VADDR));

}

void module_vdc_adc_power_on(void)
{
	adc_power_RBUS adc_power_reg;
	vdadc_core_lpf_ctrl_RBUS vdadc_core_lpf_ctrl_reg;
	vdadc_pow_ctl_RBUS vdadc_pow_ctl_reg;
	
	adc_power_reg.regValue = rtd_inl(ADC_ADC_POWER_VADDR);
	vdadc_core_lpf_ctrl_reg.regValue = rtd_inl(ADC_VDADC_CORE_LPF_CTRL_VADDR);
	vdadc_pow_ctl_reg.regValue = rtd_inl(ADC_VDADC_POW_CTL_VADDR);

	////ADC_POWER[0]Blue Channel ADC Power On,ADC_POWER[1]Green Channel ADC Power On,ADC_POWER[2]Red Channel ADC Power On,ADC_POWER[3]ADC Bandgap Power On
	////ADC_POWER[4]SOG1 Power On,ADC_POWER[5]SOG0 Power On,ADC_POWER[6]ADC clock Power On,ADC_POWER[7]Online Auto_SOY ADC Clock Power On
	adc_power_reg.adc_power_0 = 0x1;
	adc_power_reg.adc_power_1 = 0x1;
	adc_power_reg.adc_power_2 = 0x1;
	adc_power_reg.adc_power_3 = 0x1;
	adc_power_reg.adc_power_4 = 0x1;
	adc_power_reg.adc_power_5 = 0x1;
	adc_power_reg.adc_power_6 = 0x1;
	adc_power_reg.adc_power_7 = 0x1;

	// externel [1]LDO100MA_POW [0]VDADC power on	3.3V				// VDADC_POW_CTL
	vdadc_pow_ctl_reg.vdadc_pow = 0x1;
	vdadc_pow_ctl_reg.ldo100ma_pow = 0x1; // the major power of vdadc

	// internel [22]ADC Power On [21]LDO Power On	 1.xV
	vdadc_core_lpf_ctrl_reg.vdadc_adc_ctrl_5 = 0x1;
	vdadc_core_lpf_ctrl_reg.vdadc_adc_ctrl_6 = 0x1;
	
	
	rtd_outl(ADC_ADC_POWER_VADDR,adc_power_reg.regValue);
	rtd_outl(ADC_VDADC_CORE_LPF_CTRL_VADDR,vdadc_core_lpf_ctrl_reg.regValue);
	rtd_outl(ADC_VDADC_POW_CTL_VADDR,vdadc_pow_ctl_reg.regValue);

	
	////ADC_POWER[0]Blue Channel ADC Power On,ADC_POWER[1]Green Channel ADC Power On,ADC_POWER[2]Red Channel ADC Power On,ADC_POWER[3]ADC Bandgap Power On
	////ADC_POWER[4]SOG1 Power On,ADC_POWER[5]SOG0 Power On,ADC_POWER[6]ADC clock Power On,ADC_POWER[7]Online Auto_SOY ADC Clock Power On
	//rtd_maskl(0xb8020000,0xFFFFFFFF,0x000000FF); 
	
	// externel [1]LDO100MA_POW [0]VDADC power on	3.3V				// VDADC_POW_CTL
	//rtd_maskl(0xb802005C,0xFFFFFFFF,0x00000003); 
	
	// internel [22]ADC Power On [21]LDO Power On	 1.xV
	//rtd_maskl(0xb8020054,0xFFFFFFFF,0x00600000); 

	dmsg("0x%x",rtd_inl(0xb802005C));


}

void module_vdc_adc_setting(void)
{
	#if CONFIG_BGA == 0 // 0 for QFP , 1 for BGA
	//-------- VD ADC PATH-------------------------------------------------
	//REG_VDADC_CLAMP_CTRL2[10] 	mux1----[2:0]:VDC UP/DN Enable,[10:8]:Negative UP/DN NCLAMP_EN Enable-|
	//SV0_Y 						----------------------------------------------------------------------| - REG_VDADC_CLAMP_CTRL1[10:9] mux3
	//REG_VDADC_CLAMP_CTRL2[9:8]	mux2----[2:0]:VDC UP/DN Enable,[10:8]:Negative UP/DN NCLAMP_EN Enable-|
	//comment:
	//004c REG_VDADC_CLAMP_CTRL2[10] : 0: 9+ 1: 8+
	//004c REG_VDADC_CLAMP_CTRL2[9:8]: 00/01: 12+, 10/11: 13+
	//0048 REG_VDADC_CLAMP_CTRL1[10:9]: 00: 9++(mux1), 01: 10+, 10:11++(mux2)
	//[sirius] vin9p: cvbs vin10p: sv
	//---------------------------------------------------------------------
	rtd_maskl(ADC_VD_ADC_CLAMP_CTL_2_VADDR,0xFFFFFCE3,0x00000100);//VD_ADC_CLAMP_CTL_2: [9:8] = 0x1,vin12p [4:2] = 0, nagtive clamp disable
	rtd_maskl(ADC_VD_ADC_CLAMP_CTL_1_VADDR,0xFFFF191F,0x00008400);//VD_ADC_CLAMP_CTL_1: [15:13] = 0x4,dc restore v2  [10:9] = 0x2,vin11pp [7:5] = 0,clamp disable
	rtd_maskl(ADC_VD_ADC_UPDN_CTL_VADDR,0xFFFFF8F8,0x00000000);//VD_ADC_UPDN_CTL: [10:8] = 0,nagtive updn clamp disable [2:0] = 0, updn clamp disable
	#else
		#if CONFIG_BOX == 0 // 0 for BGA_TV , 1 for BGA_BOX
	vd_adc_clamp_ctl_1_RBUS vd_adc_clamp_ctl_1_reg; // 2_0048
	vd_adc_clamp_ctl_1_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_1_VADDR);
	vd_adc_clamp_ctl_2_RBUS vd_adc_clamp_ctl_2_reg; // 2_004c
	vd_adc_clamp_ctl_2_reg.regValue = rtd_inl(ADC_VD_ADC_CLAMP_CTL_2_VADDR);
	vd_adc_updn_ctl_RBUS vd_adc_updn_ctl_reg;	// 2_0050
	vd_adc_updn_ctl_reg.regValue = rtd_inl(ADC_VD_ADC_UPDN_CTL_VADDR);

	//setting first order path
	vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_10= 0x0; //input from vin9p (cvbs)
	vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_9_8 = 0x0;// input from vin12p (qfp: cvbs input bga: sv: c input)
	
	//setting second order patch
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_10_9 = 0x0; //vin9pp

	//setting dc restore or clamp
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_15_13 = 0x1; // dc restore v1
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl1_7_5 = 0x0;//disable all positive offline clamp
	vd_adc_clamp_ctl_2_reg.vdadc_clamp_ctrl2_4_2 = 0x0;// disable offline negative clamp
	vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_10_8 = 0x0;//disable  negative updn clamp
	vd_adc_updn_ctl_reg.vdadc_updn_ctrl0_2_0 = 0x0;//disable updn clamp

	//set 4-bit dac code
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_7_4 = 0x9;
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_3_0 = 0x7;

	//yc swap nclamp
	vd_adc_clamp_ctl_1_reg.vdadc_clamp_ctrl0_12_10 = 0x5;

	rtd_outl(0xb802005c,0x20000003);
		
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_1_VADDR,vd_adc_clamp_ctl_1_reg.regValue);
	rtd_outl(ADC_VD_ADC_CLAMP_CTL_2_VADDR,vd_adc_clamp_ctl_2_reg.regValue);
	rtd_outl(ADC_VD_ADC_UPDN_CTL_VADDR,vd_adc_updn_ctl_reg.regValue);
		#endif
	#endif
}

void module_vdc_switch_av_2_tv_and_disable_ifd_clamp(void)
{
	INOUT_CTRL_RBUS inout_ctrl_rbus_reg;	// 1_9080
	inout_ctrl_rbus_reg.regValue = rtd_inl(VDC_INOUT_CTRL_VADDR);
	inout_ctrl_rbus_reg.sw_tu_cvbs = 0;	// Switch for Tuner CVBS and Clamping Data; 0: Data comes from ADC and clamping up/dn goes to ADC
	inout_ctrl_rbus_reg.clamp_if_up_en = 0;
	inout_ctrl_rbus_reg.clamp_if_dn_en = 0;
	rtd_outl(VDC_INOUT_CTRL_VADDR, inout_ctrl_rbus_reg.regValue);	// 1_9080
}

BOOL QC_Verifier_VDC_EQC(void){
	UINT8 ADCselect;
	UINT32 i;
	bool verifyResult = FALSE;

	dmsg("\n%s()\t1\n",__FUNCTION__);

	module_vdc_crt_clock_setting();

	module_vdc_adc_power_on();

	printk("[QC_Verifier_VDC  Chip_ID=%x]\n",MAC2P_Version&MAC2_Version);

#if 1
	drvif_module_vdc_VDCReset();	// 2013.1/27 done
	dmsg("\t2\n");
	drvif_module_vdc_SoftReset();	// 2013.1/27 done
	dmsg("\t3\n");
	module_vdc_switch_av_2_tv_and_disable_ifd_clamp();
	dmsg("\t4\n");
	module_vdc_adc_setting();
	dmsg("\t5\n");
#endif

	printk("[QC_Verifier_VDC_EQC]\n");

	drvif_module_vdc_Initial();	// 2013.1/27 done
	
	printk("[VDC Qc Initial is ok]\n");
#if 1	// debug
	printk("av_mode = %x	rtd_outl(0x%x, 0x%08x);\n", _PALI, VDC_MODE_DETECTION_STATUS_VADDR, rtd_inl(VDC_MODE_DETECTION_STATUS_VADDR));
#endif

#if 1// 2013.02/23 Mark test function
	if(module_vdc_tst_Open() == _SUCCESS)	// 2013.1/29
	{
		printk("[VDC QC in EQC Test is ok]\n");
		verifyResult=_SUCCESS;
	}
	else
		verifyResult= _FAIL;
#endif
	return verifyResult;
}


BOOL QC_Verifier_VDC_FT(void){ return _SUCCESS;}

BOOL QC_Verifier_VDC_ESD(void){ return _SUCCESS;}

BOOL QC_Verifier_VDC_OLTOST(void){ return _SUCCESS;}

int QC_Verifier_VDC(void){

	printk("jacky_test\n");

#if 0
	vdc_open_vin7p_for_ifd_loopback_test();
#endif

#if 0	// 2013.02/08 Clliferd QC test
if(QC_Verifier_VDC_CVBS_VIN9() == _SUCCESS)
	return _SUCCESS;
else
	return _FAIL;
#endif

#if 1	// 2013.02/22 Mark debug
if(QC_Verifier_VDC_EQC() == _SUCCESS)
	return _SUCCESS;
else
	return _FAIL;
#endif
}

