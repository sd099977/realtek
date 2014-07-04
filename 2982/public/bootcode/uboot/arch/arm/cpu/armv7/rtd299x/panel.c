#include <panelConfigParameter.h>
#include <rbusPpOverlayReg.h>
#include <rbusSYSTEMReg.h>
#include <rbusPinmuxReg.h>
#include <rbusPifReg.h>
#include <rbusSfgReg.h>
#include <rbusVby1Reg.h>
#include <platform_lib/board/pcb_mgr.h>
#include <platform_lib/board/pcb.h>
#include <asm/io.h>
#include <bootparam.h>
#include <asm/arch/factorylib.h>
#include "panel.h"
#include <asm/arch/rbus/rbusLD_InterfaceReg.h>
#include <asm/arch/ld_interface.h>
#include <rtk_g2c_lib.h>

extern int boot_power_on_mode;

#define DISABLE_SOME_PRINTF
#ifdef DISABLE_SOME_PRINTF
	#define DEBUG_PRINT(fmt,args...)
#else
	#define DEBUG_PRINT(fmt,args...)	 printf(fmt,## args);
#endif


//UINT8 LVDS_4_PORTS_INDEX;


#ifdef OPEN_CELL_PANEL
void Panel_Tcon_Init(void);
#endif

#ifdef CONFIG_PANEL_APPLY_TCON_SETTING
#define PANEL_TCON_SETTING_HEADER_MAGNO_BIN	"BIN"
#define PANEL_TCON_SETTING_HEADER_MAGNO_TXT	"TXT"
#define PANEL_TCON_SETTING_FILE_NAME	FACTORY_HEADER_FILE_NAME"TCON.bin"
#define PANEL_ODC_SETTING_FILE_NAME		FACTORY_HEADER_FILE_NAME"ODC.bin"

extern void panel_apply_tcon_setting(char *filename);
#endif

extern struct _PANEL_CONFIG_PARAMETER  default_panel_parameter;
//extern INT32 boot_backlight_value;

#define CONFIG_CPU_XTAL_FREQ 27000000

//UINT32 panel_wait_us_first = 0;
//unsigned char panel_wait_is_wrap = 0;
static unsigned char  panel_init_1st_is_done = 0;
static unsigned char  panel_init_2nd_is_done = 0;
#if 0
UINT32 LVDS_4_PORT_MAPPING_TABLE[24] ={
	0x0123,	0x0132,	0x0213,	0x0231,
	0x0312,	0x0321,	0x1023,	0x1032,
	0x1203,	0x1230,	0x1320,	0x1302,
	0x2013,	0x2031,	0x2103,	0x2130,
	0x2301,	0x2310,	0x3012,	0x3021,
	0x3102,	0x3120,	0x3210,	0x3201
};
#endif


// PixelWorks PA168 MEMC control
#define PA168_I2C_SLAVE_ID			(0x22 >> 1)	// 1 bit R-shift for Darwin I2C bug?
#define PA168_I2C_CMD_LVDS_FMT	(0x18)
// PixelWorks PA168 4k2k TCON control
typedef enum _PA168_LVDS_INPUT_FMT{
	LVDS_FMT_8BIT_JEIDA	= 0,
	LVDS_FMT_8BIT_VESA	= 1,
	LVDS_FMT_10BIT_JEIDA	= 2,
	LVDS_FMT_10BIT_VESA	= 3,
	LVDS_FMT_10BIT_MIX	= 4
}PA168_LVDS_INPUT_FMT;

void PA168_i2c_cmd()
{
//	unsigned long long value=0;
	UINT8 msg[2];

	G2C_Init(0x3);

	msg[0] = PA168_I2C_CMD_LVDS_FMT;
	msg[1] = LVDS_FMT_10BIT_VESA; //
	G2C_Write_EX(3, PA168_I2C_SLAVE_ID, 0, 0, 2, msg);

	printf("[PA168] Send I2C command!\n");

	return;
}


unsigned char panel_Tcon_PA168_Enable(void)
{

	if((default_panel_parameter.iCONFIG_PANEL_TYPE == 2) && (default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_PA168_AU_55))
		return 1;

	return 0;
}


unsigned char Get_PANEL_TYPE_IS_MILLET3_4K2K_SERIES(void)
{
	if((default_panel_parameter.iCONFIG_PANEL_TYPE == P_LVDS_4K_2K) &&
		( (default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX >=  P_M3_CMI_55) &&
		   (default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX < P_MILLET_SERIES_PANEL_MAX)))
		   return 1;
	else
		return 0;
}

unsigned char Get_PANEL_TYPE_IS_IWATT_LOCAL_DIMMING(void)
{
	if((default_panel_parameter.iCONFIG_PANEL_TYPE == P_LVDS_2K1K) &&
		((default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_IWATT7018_LG_42_SFK1)||
		(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_IWATT7018_LG_47_SFK1)))
		   return 1;
	else
		return 0;
}



/**
 * drvif_clock_set_pll
 * Set PLL register.
 *
 * @param <M_Code> { M code}
 * @param <N_Code> { N code}
 * @param <CPC> { charge pump current}
 * @return { none }
 *
 */
void drvif_clock_set_pll(UINT8 M_Code, UINT8 N_Code, UINT8 div, UINT8 CPC)
{
	sys_pll_disp1_RBUS pll_disp1_reg;
	sys_pll_disp2_RBUS pll_disp2_reg;
	sys_dclkss_RBUS dclkss_reg;
	unsigned int offset;
	//Modify by tyan
	if(div == 1)
		div = 0;
	else	if(div == 2)
		div = 1;
	else if(div == 4)
		div = 2;
	else if(div == 8)
		div = 3;

	dclkss_reg.regValue = rtd_inl(SYSTEM_SYS_DCLKSS_VADDR);
	offset = dclkss_reg.dclk_offset_11_0;
	dclkss_reg.dclk_offset_11_0 = 0;
	dclkss_reg.dclk_ss_en = 0;
	dclkss_reg.dclk_ss_load = 1;
	rtd_outl(SYSTEM_SYS_DCLKSS_VADDR, dclkss_reg.regValue);

	rtd_maskl(SYSTEM_SYS_PLL_DISP2_VADDR, ~(_BIT17) , _BIT17); //<-- need or not ???

	mdelay(1);


	pll_disp2_reg.regValue =  rtd_inl(SYSTEM_SYS_PLL_DISP2_VADDR);
	pll_disp1_reg.regValue = 0;
	pll_disp1_reg.dpll_m = M_Code - 2;
	pll_disp2_reg.dpll_o = div;
	pll_disp1_reg.dpll_n= N_Code - 2;
	pll_disp1_reg.dpll_ip= CPC;
	rtd_outl(SYSTEM_SYS_PLL_DISP1_VADDR, pll_disp1_reg.regValue);
	rtd_outl(SYSTEM_SYS_PLL_DISP2_VADDR, pll_disp2_reg.regValue);
	mdelay(1);

	dclkss_reg.dclk_offset_11_0 = offset;
	dclkss_reg.dclk_ss_en = 1;
	dclkss_reg.dclk_ss_load = 1;
	rtd_outl(SYSTEM_SYS_DCLKSS_VADDR, dclkss_reg.regValue);

	pll_disp2_reg.regValue = rtd_inl(SYSTEM_SYS_PLL_DISP2_VADDR);
	pll_disp2_reg.dpll_rstb = 1;
	pll_disp2_reg.dpll_fupdn = 1;
	pll_disp2_reg.dpll_stop = 1;
	pll_disp2_reg.dpll_pwdn = 0;
	rtd_outl(SYSTEM_SYS_PLL_DISP2_VADDR, pll_disp2_reg.regValue);

	rtd_maskl(SYSTEM_SYS_DCLKSS_VADDR, 0xff, _BIT31 | _BIT2|_BIT0);
}

unsigned char drvif_clock_cal_cpc(unsigned int M_Code,unsigned int N_Code) // CPC : charge pump current
{
	unsigned int ucTemp1;
	unsigned int  ucTemp2 = 0;
	//sys_pll_disp2_RBUS pll_disp1_reg;

	//Modify by tyan start 20070701  but not test yet
	if( N_Code <= 5){
		//LPF_Mode = 0, suppose  iM / Ich = 1.673
		ucTemp1 = ((unsigned int) M_Code  *10000/ 1673);
	/*	pll_disp1_reg.regValue = IoReg_Read32(SYSTEM_SYS_PLL_DISP2_VADDR);
		pll_disp1_reg.dplllpfmode = 0;
		IoReg_Write32(SYSTEM_SYS_PLL_DISP2_VADDR, pll_disp1_reg.regValue);*/
	}
	else{
		//16>=N_Code>5
		//LPF_Mode = 1, suppose iM / Ich =17.6
		ucTemp1 = ( (unsigned int)M_Code *10000 / 17600);
		/*pll_disp1_reg.regValue = IoReg_Read32(SYSTEM_SYS_PLL_DISP2_VADDR);
		pll_disp1_reg.dplllpfmode = 1;
		IoReg_Write32(SYSTEM_SYS_PLL_DISP2_VADDR, pll_disp1_reg.regValue);*/
	}

	//ROSPrintf("\n Ich *10= %x",ucTemp1);

	//DPLL_CRNT[4:0] = DPLLSI[4:0]
	//I=(2.5uA+2.5uA*bit[0]+5uA*bit[1]+10uA*bit[2]+20uA*bit[3]+30uA*bit[4]) ,
	//Ip=I*[(bit[5]+1) / 2]Keep Icp/DPM constant

	ucTemp1=ucTemp1-25;

	if (ucTemp1 > 300) {
		ucTemp1 -= 300;
		ucTemp2 += 16;
	}

	if (ucTemp1 > 200) {
		ucTemp1 -= 200;
		ucTemp2 += 8;
	}

	if (ucTemp1 > 100) {
		ucTemp1 -= 100;
		ucTemp2 |= 4;
	}

	if (ucTemp1 > 50) {
		ucTemp1 -= 50;
		ucTemp2 += 2;
	}

	if (ucTemp1 > 25) {
		ucTemp1 -= 25;
		ucTemp2 += 1;
	}

	ucTemp2 += 32;

	return ucTemp2;
}


void drvif_clock_offset(unsigned short usDclkOffset)
{
	sys_dclkss_RBUS reg;

	reg.regValue = rtd_inl(SYSTEM_SYS_DCLKSS_VADDR);
	reg.dclk_offset_11_0 = usDclkOffset;
	reg.dclk_ss_en = 1;
	reg.dclk_ss_load = 1;
	rtd_outl(SYSTEM_SYS_DCLKSS_VADDR, reg.regValue);
}





/*============================================================================*/
/**
 * drvif_clock_set_dclk
 * This function is used to set display clock.
 *
 * @param	<niHFreq>		{ IHFreq }
 * @param	<niVActLen>		{ input length (IVActLen for normal case; IVTotal for FRC ATV and JPEG RPTG) }
 * @param	<default_freq>	{ default frequency (Its priority is highest. Set 0 to calculate dclk.) }
 * @return					{ 0) FRC, 1) framesync }
 */
unsigned char drvif_clock_set_dclk(unsigned int ulFreq)
{
	unsigned char  cpc,cnt=0,div=1, ret=0;
	unsigned short nMCode,nNCode;
	unsigned int nDPLL,temp=0;
	unsigned int nStep;
//	unsigned int ulFreq;
//	sys_pll_wd_out_RBUS pll_wdout_reg;

//	sys_pll_disp1_RBUS pll_disp0_reg;
//	sys_pll_disp2_RBUS pll_disp2_reg;



	//ulFreq>200MHz===>ulFreq * 16  too big(>32bit)
	//24.567MHz*(nMCode/nNCode)<=500 MHz
	//24.567MHz*(nMCode/nNCode)>=100 MHz
	//nMCode/nNCode<=20.3
	//nMCode/nNCode>=4
	//div>=25MHz*15/(ulFreq*8)
	//div<=125MHz*15/(ulFreq*8)
	//225MHz>=ulFreq>=28MHz
	//250MHz===>   1.04>=div>=0.208
	//28MHz===>   8.37>=div>=1.67

//#ifdef VBY_ONE
	if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		if(ulFreq >= 200000000)
			ulFreq = ulFreq/2; //by2 via 0xb8028294[1:0]
	}
//#endif

	if((ulFreq<=234000000) && (ulFreq>=46800000))
		div=1;
	else if((ulFreq<=117000000) && (ulFreq>=23400000))
		div=2;
	else if((ulFreq<=58000000) && (ulFreq>=11700000))
		div=4;
	else if((ulFreq<=29200000) && (ulFreq>=5850000))
 		div=8;

	//nMCode/nNCode<=20;setting  nMCode=temp*nNCode
	//nMCode/nNCode>=4;setting  nMCode=temp*nNCode
	//temp=ulFreq/24.567MHz*div*2*16/15 <=20
	//temp=ulFreq/24.567MHz*div*2*16/15 >=4

	temp=(ulFreq)*div*2*4/15/(CONFIG_CPU_XTAL_FREQ/256);

	temp=temp*4;

	if(temp>=(20*256))
		temp=20*256;
	if(temp<=(4*256))
		temp=4*256;

	for(cnt=3;cnt<=15;cnt++){
		nNCode=cnt;
		nMCode=nNCode*2*temp/256;
		nMCode = ((nMCode >> 1) + (nMCode & 0x01));
		if ((nMCode<=255)&&(nMCode>=3))
			break;
	}

	cpc = drvif_clock_cal_cpc(nMCode,nNCode);

	drvif_clock_set_pll(nMCode, nNCode, div, cpc);

	// Dclk frequency in Hz
	//CONFIG_SCALER_XTAL_FREQ * nMCode too big(>32bit)

	nDPLL = ((CONFIG_CPU_XTAL_FREQ/128 * nMCode) / (div * nNCode*2))*128;

	// Offset resolution (DPLL / 2^15) in Hz
	nStep = nDPLL >> 15;

	// Target frequency of Dclk in Hz
	if(ulFreq >= (nDPLL*15/16)){
		//temp = (ulFreq-(nDPLL*15/16) ) / nStep;
		temp = (ulFreq-((nDPLL/16)*15) ) / nStep;
		temp = 0x800-temp;
	}
	else{
		temp = ((nDPLL*15/16)-ulFreq ) / nStep;
		temp = 0x800+temp;
	}

	//Enable DDS spread spectrum output function
	drvif_clock_offset(temp);

	printf("Panel: ulFreq:%d, nDPLL:%d, Mcode:%d, Ncode:%d, offset:%x\n", ulFreq, nDPLL, nMCode, nNCode, temp);

	return ret;
}



/**
*
* @}
*/

//#undef	rtd_inl
//#define  rtd_inl(x) __rtd_inl(x)
void setPanelDataSetting(struct _PANEL_CONFIG_PARAMETER *panel)
{
//	unsigned int data ;
	unsigned int DHTotal;
	lvds_ctrl3_RBUS  lvds_ctrl3;
	display_timing_ctrl1_RBUS display_timing_ctrl1_reg;
	display_timing_ctrl2_RBUS display_timing_ctrl2_reg;
	dh_width_RBUS dh_width_reg;
	dh_total_last_line_length_RBUS dh_total_last_line_length_reg;
	dv_length_RBUS dv_length_reg;
	dv_total_RBUS dv_total_reg;
	dh_den_start_end_RBUS dh_den_start_end_reg;
	fs_iv_dv_fine_tuning_RBUS fs_iv_dv_fine_tuning_reg;
	display_background_color_RBUS display_background_color_reg;
	main_display_control_rsv_RBUS main_display_control_rsv_reg;
	main_den_h_start_end_RBUS main_den_h_start_end_reg;
	main_border_highlight_border_color_RBUS main_border_highlight_border_color_reg;
	main_den_v_start_end_RBUS main_den_v_start_end_reg;
	main_background_h_start_end_RBUS main_background_h_start_end_reg;
	main_active_h_start_end_RBUS main_active_h_start_end_reg;
	main_background_v_start_end_RBUS main_background_v_start_end_reg;
	main_active_v_start_end_RBUS main_active_v_start_end_reg;
	double_buffer_ctrl_RBUS double_buffer_ctrl_reg;
//	lvds_ctrl4_RBUS lvds_ctrl4_reg;
	dv_den_start_end_RBUS dv_den_start_end_reg;
//	lvds_misc_ctrl_0_RBUS 	lvds_misc_ctrl_0_reg;
	dclk_sel_RBUS dclk_sel_reg;

	//drvif_clock_set_dclk(panel->iCONFIG_DISPLAY_CLOCK_TYPICAL);  // defualt fps: 50Hz

	//disable double buffer register
	double_buffer_ctrl_reg.regValue = rtd_inl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR);
	double_buffer_ctrl_reg.dreg_dbuf_en_n = 1;
	rtd_outl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR, double_buffer_ctrl_reg.regValue);

	//DTG setting
	display_timing_ctrl1_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR);
	display_timing_ctrl1_reg.disp_frc_on_fsync = 0;
	display_timing_ctrl1_reg.disp_line_4x = panel->iFIX_LAST_LINE_4X_ENABLE;
	display_timing_ctrl1_reg.disp_fsync_en = 0;
//#ifdef VBY_ONE
	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K)
		display_timing_ctrl1_reg.disp_en = 0;	// enable dtg out wait for vby one phy and sfg ready for sync timing
	else		//#else
		display_timing_ctrl1_reg.disp_en = 1;
//#endif
	display_timing_ctrl1_reg.wde_to_free_run = 0;
	display_timing_ctrl1_reg.dout_force_bg = 1;
	display_timing_ctrl1_reg.dhs_first_mask = 0;
	display_timing_ctrl1_reg.auto_switch_fll_to_fs = 0;
	display_timing_ctrl1_reg.disp_fix_last_line = 0;

	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, display_timing_ctrl1_reg.regValue);

	display_timing_ctrl2_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR);
	display_timing_ctrl2_reg.sr_mode = panel->iCONFIG_SR_MODE; //SR bypass
	display_timing_ctrl2_reg.sr_pixel_mode = panel->iCONFIG_SR_PIXEL_MODE; // 4pixel mode
	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR, display_timing_ctrl2_reg.regValue);
//	display_timing_ctrl2_reg.output_porta = panel->iCONFIG_DISPLAY_PORTAB_SWAP?1:0;
//	display_timing_ctrl2_reg.output_portb = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;
//	display_timing_ctrl2_reg.output_portc = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;
//       display_timing_ctrl2_reg.dclk_mode_switch = panel->iCONFIG_DISPLAY_PORT;
//	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR, display_timing_ctrl2_reg.regValue);


	dh_width_reg.dh_width = panel->iCONFIG_DISP_HSYNC_WIDTH;
	rtd_outl(PPOVERLAY_DH_WIDTH_VADDR, dh_width_reg.regValue);

	// cklai@101223 make sure the DHTotal lastline value is odd.
	DHTotal = panel->iCONFIG_DISP_HSYNC_LASTLINE;
	if (DHTotal & _BIT0) // if odd
		DHTotal += 1; // set even

	dh_total_last_line_length_reg.regValue = 0;
	dh_total_last_line_length_reg.dh_total = panel->iCONFIG_DISP_HORIZONTAL_TOTAL - 1;
	dh_total_last_line_length_reg.dh_total_last_line = DHTotal - 1;
	rtd_outl(PPOVERLAY_DH_TOTAL_LAST_LINE_LENGTH_VADDR, dh_total_last_line_length_reg.regValue);


	dv_length_reg.regValue = 0;
	dv_length_reg.dv_length = panel->iCONFIG_DISP_VSYNC_LENGTH;

	rtd_outl(PPOVERLAY_DV_LENGTH_VADDR, dv_length_reg.regValue);


	dv_total_reg.regValue = 0;
	dv_total_reg.dv_total = panel->iCONFIG_DISP_VERTICAL_TOTAL - 1;
	rtd_outl(PPOVERLAY_DV_TOTAL_VADDR, dv_total_reg.regValue);


	dh_den_start_end_reg.regValue = 0;
	dh_den_start_end_reg.dh_den_sta = panel->iCONFIG_DISP_DEN_STA_HPOS;
	dh_den_start_end_reg.dh_den_end = panel->iCONFIG_DISP_DEN_END_HPOS;
	rtd_outl(PPOVERLAY_DH_DEN_START_END_VADDR, dh_den_start_end_reg.regValue);

	dv_den_start_end_reg.regValue = 0;
	dv_den_start_end_reg.dv_den_sta = panel->iCONFIG_DISP_DEN_STA_VPOS;
	dv_den_start_end_reg.dv_den_end = panel->iCONFIG_DISP_DEN_END_VPOS;
	//xuchenghao modify, "+1" do not change here, change in panel Parameter
	rtd_outl(PPOVERLAY_DV_DEN_START_END_VADDR, dv_den_start_end_reg.regValue);

	fs_iv_dv_fine_tuning_reg.regValue = 0;
//	fs_iv_dv_fine_tuning_reg.double_vs_error_flag = 0;
//	fs_iv_dv_fine_tuning_reg.db_vs_irq_en = 0;
	fs_iv_dv_fine_tuning_reg.db_vs_m2bg = 0;
//	fs_iv_dv_fine_tuning_reg.db_vs_s2bg = 0;

	rtd_outl(PPOVERLAY_FS_IV_DV_FINE_TUNING_VADDR, fs_iv_dv_fine_tuning_reg.regValue);


	display_background_color_reg.regValue = 0;
	display_background_color_reg.d_bg_r = 0;
	display_background_color_reg.d_bg_g = 0;
	display_background_color_reg.d_bg_b = 0;
	rtd_outl(PPOVERLAY_DISPLAY_BACKGROUND_COLOR_VADDR, display_background_color_reg.regValue);

	//MTG setting
	//USER:LewisLee DATE:2012/05/31
	//to prevent disable display data enable interrupt
	//let D domain ISR work error
	main_display_control_rsv_reg.regValue = rtd_inl(PPOVERLAY_MAIN_DISPLAY_CONTROL_RSV_VADDR);
	main_display_control_rsv_reg.main_wd_to_background = 0;
//	main_display_control_rsv_reg.dummy18028100_7_4 = 0;
//	main_display_control_rsv_reg.mv_den_sta_event_ie = 0;
//	main_display_control_rsv_reg.mv_den_end_event_ie = 0;
	main_display_control_rsv_reg.m_hbd_en = 0;
	main_display_control_rsv_reg.m_bd_trans = 0;
	main_display_control_rsv_reg.m_force_bg = 0;
	main_display_control_rsv_reg.m_disp_en = 1;
	rtd_outl(PPOVERLAY_MAIN_DISPLAY_CONTROL_RSV_VADDR, main_display_control_rsv_reg.regValue);

	//rtd_outl(PPOVERLAY_MAIN_DISPLAY_CONTROL_VADDR, 0x0000f000);//<-- I feel strange

	main_border_highlight_border_color_reg.regValue = 0;
	main_border_highlight_border_color_reg.m_bd_b = 0;
	main_border_highlight_border_color_reg.m_bd_g = 0;
	main_border_highlight_border_color_reg.m_bd_r = 0;
	main_border_highlight_border_color_reg.m_hbd_b = 0;
	main_border_highlight_border_color_reg.m_hbd_g =0;
	main_border_highlight_border_color_reg.m_hbd_r = 0;
	rtd_outl(PPOVERLAY_MAIN_BORDER_HIGHLIGHT_BORDER_COLOR_VADDR, main_border_highlight_border_color_reg.regValue);

	//Display window H Enable setting // 0x437
	main_den_h_start_end_reg.regValue = 0;
	main_den_h_start_end_reg.mh_den_sta = panel->iCONFIG_DISP_ACT_STA_HPOS;
	main_den_h_start_end_reg.mh_den_end = panel->iCONFIG_DISP_ACT_END_HPOS;
	rtd_outl(PPOVERLAY_MAIN_DEN_H_START_END_VADDR, main_den_h_start_end_reg.regValue);

	//Display window V Enable setting // 0x43a
	main_den_v_start_end_reg.regValue = 0;
	main_den_v_start_end_reg.mv_den_sta = panel->iCONFIG_DISP_ACT_STA_VPOS;
	main_den_v_start_end_reg.mv_den_end = panel->iCONFIG_DISP_ACT_END_VPOS;
	rtd_outl(PPOVERLAY_MAIN_DEN_V_START_END_VADDR, main_den_v_start_end_reg.regValue);

	//Background window H setting // 0x43d
	main_background_h_start_end_reg.regValue = 0;
	main_background_h_start_end_reg.mh_bg_sta = panel->iCONFIG_DISP_ACT_STA_HPOS;
	main_background_h_start_end_reg.mh_bg_end = panel->iCONFIG_DISP_ACT_END_HPOS;
	rtd_outl(PPOVERLAY_MAIN_BACKGROUND_H_START_END_VADDR, main_background_h_start_end_reg.regValue);

	//Background window V setting // 0x440
	main_background_v_start_end_reg.regValue = 0;
	main_background_v_start_end_reg.mv_bg_sta = panel->iCONFIG_DISP_ACT_STA_VPOS;
	main_background_v_start_end_reg.mv_bg_end = panel->iCONFIG_DISP_ACT_END_VPOS;

	rtd_outl(PPOVERLAY_MAIN_BACKGROUND_V_START_END_VADDR, main_background_v_start_end_reg.regValue);

	//Active window H setting // 0x443
	main_active_h_start_end_reg.regValue = 0;
	main_active_h_start_end_reg.mh_act_sta = panel->iCONFIG_DISP_ACT_STA_HPOS;
	main_active_h_start_end_reg.mh_act_end = panel->iCONFIG_DISP_ACT_END_HPOS;
	rtd_outl(PPOVERLAY_MAIN_ACTIVE_H_START_END_VADDR, main_active_h_start_end_reg.regValue);

	//Active window V setting // 0x446
	main_active_v_start_end_reg.regValue = 0;
	main_active_v_start_end_reg.mv_act_sta = panel->iCONFIG_DISP_ACT_STA_VPOS;
	main_active_v_start_end_reg.mv_act_end = panel->iCONFIG_DISP_ACT_END_VPOS;
	rtd_outl(PPOVERLAY_MAIN_ACTIVE_V_START_END_VADDR, main_active_v_start_end_reg.regValue);


//	double_buffer_ctrl_reg.regValue = rtd_inl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR);
//	double_buffer_ctrl_reg.dreg_dbuf_en_n = 1;
//	double_buffer_ctrl_reg.dreg_dbuf_set = 1;
//	rtd_outl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR, double_buffer_ctrl_reg.regValue);

      //---------- SFG ------------------------------------------------------------------
	sfg_zz_shift_dbg_ctrl_RBUS sfg_zz_shift_dbg_ctrl_reg;
	sfg_swap_ctrl0_RBUS sfg_swap_ctrl0_reg;
	sfg_swap_ctrl1_RBUS sfg_swap_ctrl1_reg;
//#ifdef VBY_ONE
	sfg_swap_ctrl2_RBUS sfg_swap_ctrl2_reg;
	int i=0;
//#endif

	sfg_swap_ctrl2_reg.regValue = 0;

	sfg_zz_shift_dbg_ctrl_reg.regValue = rtd_inl(SFG_SFG_ZZ_SHIFT_DBG_CTRL_VADDR);
	sfg_zz_shift_dbg_ctrl_reg.dout_mode = panel->iCONFIG_DISPLAY_COLOR_BITS;
	sfg_zz_shift_dbg_ctrl_reg.dout_en  = 1;
	sfg_zz_shift_dbg_ctrl_reg.dvs_inv = 0;
	sfg_zz_shift_dbg_ctrl_reg.dhs_inv = 0;
	sfg_zz_shift_dbg_ctrl_reg.dden_inv = 0;
	#if defined(CONFIG_BOARD_TV035_RTD2992_4DDR_1G_EMMC)
	sfg_zz_shift_dbg_ctrl_reg.daclk_inv = 0;
	#else
	sfg_zz_shift_dbg_ctrl_reg.daclk_inv = 1;
	#endif
	sfg_zz_shift_dbg_ctrl_reg.daclk_en = 1;
	sfg_zz_shift_dbg_ctrl_reg.dout_rb_swap = panel->iCONFIG_DISPLAY_RED_BLUE_SWAP;
	sfg_zz_shift_dbg_ctrl_reg.dout_bit_swap =  panel->iCONFIG_DISPLAY_MSB_LSB_SWAP;
	sfg_zz_shift_dbg_ctrl_reg.dout_data_inv = panel->iCONFIG_DISPLAY_OUTPUT_INVERSE;
	sfg_zz_shift_dbg_ctrl_reg.dclk_dly_sel = panel->iCONFIG_DISP_DCLK_DELAY;
	rtd_outl(SFG_SFG_ZZ_SHIFT_DBG_CTRL_VADDR, sfg_zz_shift_dbg_ctrl_reg.regValue);

	sfg_swap_ctrl0_reg.regValue = rtd_inl(SFG_SFG_SWAP_CTRL0_VADDR);
	sfg_swap_ctrl0_reg.dclk_mode_switch = panel->iCONFIG_DISPLAY_PORT;
	//Force to background enable
	sfg_swap_ctrl0_reg.force_bg_dif_aport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_bport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_cport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_dport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_eport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_fport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_gport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_hport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_iport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_jport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_kport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_lport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_mport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_nport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_oport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_pport = 1;
	rtd_outl(SFG_SFG_SWAP_CTRL0_VADDR, sfg_swap_ctrl0_reg.regValue);

	sfg_swap_ctrl1_reg.regValue = rtd_inl(SFG_SFG_SWAP_CTRL1_VADDR);

//#ifdef VBY_ONE

//	sfg_swap_ctrl1_reg.regValue = default_panel_parameter.iCONFIG_DISPLAY_PORT_CONFIG1;
//	sfg_swap_ctrl2_reg.regValue= default_panel_parameter.iCONFIG_DISPLAY_PORT_CONFIG2;

//	rtd_outl(SFG_SFG_SWAP_CTRL1_VADDR, sfg_swap_ctrl1_reg.regValue);
//	rtd_outl(SFG_SFG_SWAP_CTRL2_VADDR, sfg_swap_ctrl2_reg.regValue);
//#else
	if(panel->iCONFIG_DISPLAY_PORT_CONFIG1){
		sfg_swap_ctrl1_reg.regValue = panel->iCONFIG_DISPLAY_PORT_CONFIG1;
		sfg_swap_ctrl2_reg.regValue = panel->iCONFIG_DISPLAY_PORT_CONFIG2;
	}else{
		sfg_swap_ctrl1_reg.output_porta = panel->iCONFIG_DISPLAY_PORTAB_SWAP?1:0;
		sfg_swap_ctrl1_reg.output_portb = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;

#if defined(CONFIG_BOARD_TV013_RTD2992_EMMC)   //
		sfg_swap_ctrl1_reg.output_portc = panel->iCONFIG_DISPLAY_PORTAB_SWAP?1:0;
		sfg_swap_ctrl1_reg.output_portd = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;
#endif
	}
	rtd_outl(SFG_SFG_SWAP_CTRL1_VADDR, sfg_swap_ctrl1_reg.regValue);
	rtd_outl(SFG_SFG_SWAP_CTRL2_VADDR, sfg_swap_ctrl2_reg.regValue);
//#endif
	//sfg_swap_ctrl1_reg.output_portc = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;

	rtd_outl(SFG_SFG_DUMMY_CTRL_0_VADDR, 0x00000000);	//SEG 0/1/2/3, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(SFG_SFG_DUMMY_CTRL_1_VADDR, 0x00000000);	//SEG 4/5/6/7, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(SFG_SFG_DUMMY_CTRL_2_VADDR, 0x00000000);	//SEG 8/9/10/11, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(SFG_SFG_DUMMY_CTRL_3_VADDR, 0x00000000);	//SEG 12/13/14/15, Front/End, Odd/Even Line, no dummy pixel

	sfg_ctrl_0_RBUS    sfg_ctrl_0_reg;
	sfg_ctrl_a_RBUS	sfg_ctrl_a_reg;
	sfg_ctrl_9_RBUS    sfg_ctrl_9_reg;
	sfg_ctrl_8_RBUS    sfg_ctrl_8_reg;
	sfg_ctrl_7_RBUS    sfg_ctrl_7_reg;
	sfg_ctrl_6_RBUS    sfg_ctrl_6_reg;
	sfg_ctrl_0_reg.regValue = rtd_inl(SFG_SFG_CTRL_0_VADDR);

//#ifdef VBY_ONE
	sfg_ctrl_1_RBUS    sfg_ctrl_1_reg;
//	sfg_ctrl_2_RBUS    sfg_ctrl_2_reg;
//	sfg_ctrl_3_RBUS    sfg_ctrl_3_reg;
//	sfg_ctrl_4_RBUS    sfg_ctrl_4_reg;
//	sfg_seg_start_0_RBUS    sfg_seg_start_0_reg;
//	sfg_seg_start_1_RBUS    sfg_seg_start_1_reg;
//	sfg_seg_start_2_RBUS    sfg_seg_start_2_reg;
//	sfg_seg_start_3_RBUS    sfg_seg_start_3_reg;
	unsigned int m_seg_width = 0;

	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){

		m_seg_width = (panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS)/(panel->iCONFIG_SFG_SEG_NUM);

		sfg_ctrl_1_reg.seg0_start = 0;
		sfg_ctrl_1_reg.seg1_start = m_seg_width;
		rtd_outl(SFG_SFG_CTRL_1_VADDR, sfg_ctrl_1_reg.regValue);

		for(i=1; i<(panel->iCONFIG_SFG_SEG_NUM)/2; i++){

			sfg_ctrl_1_reg.seg0_start = sfg_ctrl_1_reg.seg1_start + m_seg_width;
			sfg_ctrl_1_reg.seg1_start = sfg_ctrl_1_reg.seg0_start + m_seg_width;

			rtd_outl(SFG_SFG_CTRL_1_VADDR+4*i, sfg_ctrl_1_reg.regValue);
		}

		for(i=(panel->iCONFIG_SFG_SEG_NUM)/2 ; i<8; i++){
			rtd_outl(SFG_SFG_CTRL_1_VADDR+4*i, 0);
		}

		sfg_ctrl_0_reg.seg_num = panel->iCONFIG_SFG_SEG_NUM-1;
		sfg_ctrl_0_reg.port_num = panel->iCONFIG_SFG_PORT_NUM-1;

	}
	else{ //#else
		if(panel->iCONFIG_DISPLAY_PORT == 2){   // port 4
			sfg_ctrl_0_reg.port_num = 3;
		}else{ //port 1,2
			sfg_ctrl_0_reg.port_num = panel->iCONFIG_DISPLAY_PORT;
		}
		sfg_ctrl_0_reg.seg_num = 0;
		rtd_outl(SFG_SFG_CTRL_1_VADDR, 0);
		rtd_outl(SFG_SFG_CTRL_2_VADDR, 0);
		rtd_outl(SFG_SFG_CTRL_3_VADDR, 0);
		rtd_outl(SFG_SFG_CTRL_4_VADDR, 0);
		rtd_outl(SFG_SFG_SEG_START_0_VADDR, 0);
		rtd_outl(SFG_SFG_SEG_START_1_VADDR, 0);
		rtd_outl(SFG_SFG_SEG_START_2_VADDR, 0);
		rtd_outl(SFG_SFG_SEG_START_3_VADDR, 0);
	}
	//#endif
	rtd_outl(SFG_SFG_CTRL_0_VADDR, sfg_ctrl_0_reg.regValue);
	sfg_ctrl_a_reg.regValue = rtd_inl(SFG_SFG_CTRL_A_VADDR);
	sfg_ctrl_9_reg.regValue = rtd_inl(SFG_SFG_CTRL_9_VADDR);
	sfg_ctrl_8_reg.regValue = rtd_inl(SFG_SFG_CTRL_8_VADDR);
	sfg_ctrl_7_reg.regValue = rtd_inl(SFG_SFG_CTRL_7_VADDR);
	sfg_ctrl_6_reg.regValue = rtd_inl(SFG_SFG_CTRL_6_VADDR);
	sfg_ctrl_a_reg.final_line_length = (panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS);
	sfg_ctrl_a_reg.hsync_threshold = 0;
	sfg_ctrl_8_reg.vsync_start = 0;
	sfg_ctrl_8_reg.vsync_end = panel->iCONFIG_DISP_VSYNC_LENGTH;
	sfg_ctrl_7_reg.hsync_width = panel->iCONFIG_DISP_HSYNC_WIDTH+1;//HS_Width = 16 dclk = 16*Pixel_Mode*n DH_Width (ゲ4计, nタ俱计)
//#ifdef VBY_ONE

	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		sfg_ctrl_7_reg.hsync_delay = ((panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS)/(panel->iCONFIG_SR_PIXEL_MODE*2))+24; //pixel mode=>0:1 pixel, 1:2 pixel, 2:4 pixel
		//hsync_delay = 984 = data_length/Pixel_Mode +24
		sfg_ctrl_9_reg.sfg_dh_den_sta = (panel->iCONFIG_DISP_DEN_STA_HPOS/(panel->iCONFIG_SR_PIXEL_MODE*2));
		sfg_ctrl_9_reg.req_start = (panel->iCONFIG_DISP_DEN_STA_HPOS/(panel->iCONFIG_SR_PIXEL_MODE*2))-6;
		sfg_ctrl_6_reg.tg_auto_cfg = 1;
	}
	else{ //#else
		sfg_ctrl_7_reg.hsync_delay = (panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS) +24;
		sfg_ctrl_9_reg.sfg_dh_den_sta = panel->iCONFIG_DISP_DEN_STA_HPOS;
		sfg_ctrl_9_reg.req_start = panel->iCONFIG_DISP_DEN_STA_HPOS-6;
		sfg_ctrl_6_reg.regValue= 0;
	}
//#endif
	rtd_outl(SFG_SFG_CTRL_A_VADDR, sfg_ctrl_a_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_9_VADDR, sfg_ctrl_9_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_8_VADDR, sfg_ctrl_8_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_7_VADDR, sfg_ctrl_7_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_6_VADDR, sfg_ctrl_6_reg.regValue);//Disable ByPass Mode

	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		UINT32 disp_clk;
		disp_clk = ((panel->iCONFIG_DISP_HORIZONTAL_TOTAL)*(panel->iCONFIG_DISP_VERTICAL_TOTAL)*30);
		printf("##### ben debug : %d ###########\n", disp_clk);
		drvif_clock_set_dclk(disp_clk);

	}else{
		drvif_clock_set_dclk(panel->iCONFIG_DISPLAY_CLOCK_TYPICAL);  // defualt fps: 50Hz
	}

	DEBUG_PRINT("panel_init  panel->iCONFIG_DISPLAY_PORT = %x\n",panel->iCONFIG_DISPLAY_PORT);
	//DEBUG_PRINT("panel_init  LVDS_4_PORTS_INDEX = %x\n",LVDS_4_PORTS_INDEX);
	//DEBUG_PRINT("panel_init  LVDS_4_PORTS_MAPPING_TABLE[LVDS_4_PORTS_INDEX] = %x\n",LVDS_4_PORT_MAPPING_TABLE[LVDS_4_PORTS_INDEX]);



	// Panel Interface setting
	if(panel->iCONFIG_DISPLAY_PORT == 2) // 4 port output
	{
#if 0
//		rtd_outl(PANEL_INTERFACE_TYPE3_CTRL1_VADDR, 0x00300000);
//		rtd_outl(PANEL_INTERFACE_LVDS_CTRL4_VADDR, 0x0036004F);
		//display_timing_ctrl2_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR);


		sfg_swap_ctrl1_reg.output_porta = (LVDS_4_PORT_MAPPING_TABLE[LVDS_4_PORTS_INDEX]>>12)&0x0f;
		sfg_swap_ctrl1_reg.output_portb = (LVDS_4_PORT_MAPPING_TABLE[LVDS_4_PORTS_INDEX]>>8)&0x0f;;
//		display_timing_ctrl2_reg.output_portc = (LVDS_4_PORT_MAPPING_TABLE[LVDS_4_PORTS_INDEX]>>4)&0x0f;;
//		display_timing_ctrl2_reg.output_portd = LVDS_4_PORT_MAPPING_TABLE[LVDS_4_PORTS_INDEX]&0x0f;;
		//display_timing_ctrl2_reg.dclk_mode_switch = panel->iCONFIG_DISPLAY_PORT;
		rtd_outl(SFG_SFG_SWAP_CTRL1_VADDR, sfg_swap_ctrl1_reg.regValue);
#endif
//#ifndef VBY_ONE
		if(panel->iCONFIG_PANEL_TYPE != P_VBY1_4K2K){
			rtd_outl(PIF_LVDS_CTRL0_VADDR, 0);
			lvds_ctrl3.regValue = 0;
		       lvds_ctrl3.lvds_pn_swap = 0;
			lvds_ctrl3.lvds_map = panel->iCONFIG_DISPLAY_BITMAPPING_TABLE?1:0;
			lvds_ctrl3.lvds_aport_en = 1;
			lvds_ctrl3.lvds_bport_en = 1;
			lvds_ctrl3.lvds_cport_en = 1;
			lvds_ctrl3.lvds_dport_en = 1;
			rtd_outl(PIF_LVDS_CTRL3_VADDR, lvds_ctrl3.regValue);
		}
//#endif
	}
	else
	{
		rtd_outl(PIF_LVDS_CTRL0_VADDR, 0);
		lvds_ctrl3.regValue = 0;
	       lvds_ctrl3.lvds_pn_swap = 0;
		lvds_ctrl3.lvds_map = panel->iCONFIG_DISPLAY_BITMAPPING_TABLE?1:0;
		lvds_ctrl3.lvds_aport_en = 1;
		lvds_ctrl3.lvds_bport_en = 1;
		#if defined(CONFIG_BOARD_TV035_RTD2992_4DDR_1G_EMMC)//modify by chenxiangping
		lvds_ctrl3.lvds_cport_en = 0;
		lvds_ctrl3.lvds_dport_en = 0;
		#else
		lvds_ctrl3.lvds_cport_en = 1;
		lvds_ctrl3.lvds_dport_en = 1;
		#endif

		// [PA-168] PA-168 2CH mode use port c/d only
		if(panel_Tcon_PA168_Enable() && (default_panel_parameter.iCONFIG_DISPLAY_PORT == 1)){
			lvds_ctrl3.lvds_aport_en = 0;
			lvds_ctrl3.lvds_bport_en = 0;
			printf("[PA168] Boot in 2ch\n");
		}

		rtd_outl(PIF_LVDS_CTRL3_VADDR, lvds_ctrl3.regValue);


		#if defined(LVDS_PN_SWAP)
			#if LVDS_PN_SWAP
				lvds_ctrl3.lvds_pn_swap = 1;
				rtd_outl(PIF_LVDS_CTRL3_VADDR, lvds_ctrl3.regValue);
			#endif
		#endif
	}
	//DCLK divide process
	dclk_sel_reg.regValue = rtd_inl(PPOVERLAY_DCLK_SEL_VADDR);

//#ifdef VBY_ONE
	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		dclk_sel_reg.dclk_sel = 0; //DCLK = DPLL_Clk
	}
//#else
	else{
		if(panel->iCONFIG_DISPLAY_PORT == 2) // 4 port output
		{
			dclk_sel_reg.dclk_sel = 0; //DCLK = DPLL_Clk
		}else if(panel->iCONFIG_DISPLAY_PORT < 2){
			dclk_sel_reg.dclk_sel = 1; //DCLK = DPLL_Clk / 2
		}
	}
//#endif

	rtd_outl(PPOVERLAY_DCLK_SEL_VADDR, dclk_sel_reg.regValue);

	double_buffer_ctrl_reg.regValue = rtd_inl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR);
	double_buffer_ctrl_reg.dreg_dbuf_en_n = 0;
	rtd_outl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR, double_buffer_ctrl_reg.regValue);



	display_timing_ctrl1_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR);
	display_timing_ctrl1_reg.disp_frc_on_fsync = 0;
	display_timing_ctrl1_reg.disp_fsync_en = 0;
//#ifdef VBY_ONE
#ifndef	CONFIG_BOARD_TV030_RTD2995_4DDR_2G_EMMC
	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K)
		display_timing_ctrl1_reg.dout_force_bg = 0;
	else //#else
		display_timing_ctrl1_reg.dout_force_bg = 1;
#else
	display_timing_ctrl1_reg.dout_force_bg = 1;
#endif
//#endif

//	display_timing_ctrl1_reg.dout_en = 1;
	//free run, force to background
	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, display_timing_ctrl1_reg.regValue);

//#ifdef VBY_ONE
	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){

		printf("================== P_VBY1_4K2K condition ===================\n");

		//other
		rtd_outl(0xb800da40, 0x03000202);	//HDMI bandgap

		rtd_outl(0xb8000864, 0x7070f0f0);	//HPDN and LOCKN pin share
		rtd_outl(0xb80008c8, 0x00330000);	//HPDN and LOCKN sel

		rtd_outl(SYSTEM_SYS_PLL_VBY11_VADDR, 0x0090010b);	//LS PLL M=22,N=2
		rtd_outl(SYSTEM_SYS_PLL_VBY12_VADDR, 0x01524043);	//LS PLL power off
		rtd_outl(SYSTEM_SYS_PLL_VBY12_VADDR, 0x01524042);	//LS PLL power on


		//VBy1 MAC
		rtd_outl(VBY1_VIDEO_FORMAT_VADDR, 0x00010000);	//data format select 30bpp

		//#if defined(VBY_ONE_PANEL_CMI_V500_4K2K_VBY1)
		if(panel->iCONFIG_PANEL_CUSTOM_INDEX == VBY_ONE_PANEL_CMI_V500_4K2K_VBY1){
			printf("================== VBY_ONE_PANEL_CMI_V500_4K2K_VBY1 ===================\n");
			rtd_outl(VBY1_LANE_STATUS_VADDR, 0x04100404);	//4pixel mode,16lane,4section,4Byte
		}
		else if(panel->iCONFIG_PANEL_CUSTOM_INDEX == VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1){  //#elif defined(VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1)
			printf("================== VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1 ===================\n");
			rtd_outl(VBY1_LANE_STATUS_VADDR, 0x02080204);	//2pixel mode,8lane,2section,4Byte
		}
		else if(panel->iCONFIG_PANEL_CUSTOM_INDEX == VBY_ONE_PANEL_CMI_60_4K2K_VBY1){  //#elif defined(VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1)
			printf("================== VBY_ONE_PANEL_CMI_60_4K2K_VBY1 ===================\n");
			rtd_outl(VBY1_LANE_STATUS_VADDR, 0x02080104);	//2pixel mode,8lane,2section,4Byte
		}


		//#endif

		rtd_outl(VBY1_PLL_TRACKING_VADDR, 0x00000001);	//FIFO boundary
		rtd_outl(VBY1_VBY1_OUT_CTRL_VADDR, 0x00000001);	//lane swap
		rtd_outl(VBY1_TRANSMIT_CONTROL_VADDR, 0xfa000000);	//VBy1 enable

		//VBy1 PHY 0
		rtd_outl(VBY1_PHY0_TXBIST_00_VADDR, 0x00000011);	//digital PHY set
		rtd_outl(VBY1_PHY0_TXBIST_02_VADDR, 0x00ff0000);	//lane enable

		rtd_outl(VBY1_PHY0_APHY_00_VADDR, 0x00000000);	//Pre-emphasis
		rtd_outl(VBY1_PHY0_APHY_01_VADDR, 0x77777777);	//Driving
		rtd_outl(VBY1_PHY0_APHY_02_VADDR, 0x50000000);	//Z0 calibration
		rtd_outl(VBY1_PHY0_APHY_04_VADDR, 0x54000080);	//PLL set , pre-div is 1 , Mdiv is 10
		rtd_outl(VBY1_PHY0_APHY_03_VADDR, 0xc000069f);	//PLL enable , RS=4K
	//	ScalerTimer_DelayXms(1);
		rtd_outl(VBY1_PHY0_APHY_03_VADDR, 0xc00ff69f);	//VBy1 port power on


		//VBy1 PHY 1
		rtd_outl(VBY1_PHY1_TXBIST_00_VADDR, 0x00000011);	//digital PHY set
		rtd_outl(VBY1_PHY1_TXBIST_02_VADDR, 0x00ff0000);	//lane enable

		rtd_outl(VBY1_PHY1_APHY_00_VADDR, 0x00000000);	//Pre-emphasis
		rtd_outl(VBY1_PHY1_APHY_01_VADDR, 0x77777777);	//Driving
		rtd_outl(VBY1_PHY1_APHY_02_VADDR, 0x50000000);	//Z0 calibration
		rtd_outl(VBY1_PHY1_APHY_04_VADDR, 0x54000080);	//PLL set , pre-div is 1 , Mdiv is 10

		rtd_outl(VBY1_PHY1_APHY_03_VADDR, 0xc000069f);	//PLL enable , RS=4K
	//	ScalerTimer_DelayXms(1);
		rtd_outl(VBY1_PHY1_APHY_03_VADDR, 0xc00ff69f);	//VBy1 port power on

		rtd_outl(VBY1_PHY0_APHY_02_VADDR, 0xd0000000);	//Z0 calibration
		rtd_outl(VBY1_PHY1_APHY_02_VADDR, 0xd0000000);	//Z0 calibration

		//rtd_outl(0xb802D644, 0xc0000001);	//VBy1 CDR training pattern

		display_timing_ctrl1_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR);
		display_timing_ctrl1_reg.disp_en = 1;					// enable dtg out for sync vby_one timing
		rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, display_timing_ctrl1_reg.regValue);
	}

	else{//#else
	//LVDS/mini-LVDS TX PHY setting
		rtd_outl(0xb8000C00, 0xEC8DAED9);	//Current_source_0 power on, PLL_0 power ON, LDO_0 pow signal power on
							//EPI_CM_0 => Select LVDS Mode
							//VCOM_SELL_0 = 3'b100
							//IBHN_0 = 40uA, IBHX_0 = 40uA, IBTX_0 = 80uA, CML_Pre_Driver_0 = 60uA
							//PLL_CP_0 = 3pF, PLL_CS_0 = 63pF, PLL_IP_0 = 10uA
							//EPI_VSELL_0 = 2.08V
							//VCOM_0 = 40u*24/8*10.04k = 1.2048V
		rtd_outl(0xb8000C04, 0x119FE7E1);	//PLL_RS_0 = 6Kohm, PLL_PI_IP_0 = 180uA, PI_Phase_0 = ??????, PI_0 Disable
		rtd_outl(0xb8000C08, 0x00080580);	//PLL_M_0 = 7, PLL_N_0 = 1, PLL_DIV_0 = 1
							//SWAPL_0 = 0 (7bit LVDS MSB First)
							//PLL_PI_RL_0 = 2.6kohm, PLL_LDO_0 = 1.76V
							//PLL_BW_0 = 10u/(2*pi)*6k*63/(63+3)*3G/7 = 3.9MHz
		rtd_outl(0xb8000C0C, 0x0FFF0FFF);	//Data/Clock_Selection_0 (LVDS Mode, All Pair PI Bypass)
		rtd_outl(0xb8000C10, 0x00000000);	//Pre-emphasis_enable_0 = 0, LAG_0 Disable
		rtd_outl(0xb8000C14, 0x00000000);	//segmented_transition_enable_0 = 0; EPI_Mode_0 disable
		rtd_outl(0xb8000C18, 0x00000FFF);	//Parallel_Resistor_0 Disable (double driving disable), TX_differential_0 enable
		rtd_outl(0xb8000C1C, 0x00AAAAAA);	//Parallel_Resistor_0 = 100ohm
		rtd_outl(0xb8000C20, 0x00000000);	//segmented_transition_timing_0 = (2'b00 => T0=slow, T1=slow)
		rtd_outl(0xb8000C2C, 0x00000000);	//Pre-emphasis_0 = X4 (the weakest)
		rtd_outl(0xb8000C30, 0x00000000);	//Pre-emphasis_0 = X4 (the weakest)
		rtd_outl(0xb8000C34, 0x0000000F);	//NMOS segmented_transition_current_0 = (the stongest)
		rtd_outl(0xb8000C38, 0xFFFFFFFF);	//NMOS segmented_transition_current_0 = (the stongest)
		rtd_outl(0xb8000C3C, 0x0000000F);	//PMOS segmented_transition_current_0 = (the stongest)
		rtd_outl(0xb8000C40, 0xFFFFFFFF);	//PMOS segmented_transition_current_0 = (the stongest)
		rtd_outl(0xb8000C44, 0x0E739CE7);	//SL_0 = 5'b11100 (3*13=x39)
		rtd_outl(0xb8000C48, 0x39CE739C);	//SL_0 = 5'b11100 (2*13=x39)
							//Iout_0 = 40u*8/4*39=3.12mA
		rtd_outl(0xb8000C50, 0xEC8DAED9);	//Current_source_1 power on, PLL_1 power ON, LDO_1 pow signal power on
							//EPI_CM_1 => Select LVDS Mode
							//VCOM_SELL_1 = 3'b100
							//IBHN_1 = 40uA, IBHX_1 = 40uA, IBTX_1 = 80uA, CML_Pre_Driver_1 = 60uA
							//PLL_CP_1 = 3pF, PLL_CS_1 = 63pF, PLL_IP_1 = 10uA
							//EPI_VSELL_1 = 2.08V
							//VCOM_1 = 40u*24/8*10.04k = 1.2048V
		rtd_outl(0xb8000C54, 0x219FE7E1);	//PLL_RS_1 = 6Kohm, PLL_PI_IP_1 = 180uA, PI_Phase_1 = ??????, PI_1 Disable
		rtd_outl(0xb8000C58, 0x00080580);	//PLL_M_1 = 7, PLL_N_1 = 1, PLL_DIV_1 = 1
							//SWAPL_1 = 0 (7bit LVDS MSB First)
							//PLL_PI_RL_1 = 2.6kohm, PLL_LDO_1 = 1.76V
							//PLL_BW_1 = 10u/(2*pi)*6k*63/(63+3)*3G/7 = 3.9MHz
		rtd_outl(0xb8000C5C, 0x0FFF0FFF);	//Data/Clock_Selection_1 (LVDS Mode, All Pair PI Bypass)
		rtd_outl(0xb8000C60, 0x00000000);	//Pre-emphasis_enable_1 = 0, LAG_1 Disable
		rtd_outl(0xb8000C64, 0x00000000);	//segmented_transition_enable_1 = 0; EPI_Mode_1 disable
		rtd_outl(0xb8000C68, 0x00000FFF);	//Parallel_Resistor_1 Disable (double driving disable), TX_differential_1 enable
		rtd_outl(0xb8000C6C, 0x00AAAAAA);	//Parallel_Resistor_1 = 100ohm
		rtd_outl(0xb8000C70, 0x00000000);	//segmented_transition_timing_1 = 2'b00 => (T0=slow, T1=slow)
		rtd_outl(0xb8000C7C, 0x00000000);	//Pre-emphasis_1 = X4 (the weakest)
		rtd_outl(0xb8000C80, 0x00000000);	//Pre-emphasis_1 = X4 (the weakest)
		rtd_outl(0xb8000C84, 0x0000000F);	//NMOS segmented_transition_current_1 = (the stongest)
		rtd_outl(0xb8000C88, 0xFFFFFFFF);	//NMOS segmented_transition_current_1 = (the stongest)
		rtd_outl(0xb8000C8C, 0x0000000F);	//PMOS segmented_transition_current_1 = (the stongest)
		rtd_outl(0xb8000C90, 0xFFFFFFFF);	//PMOS segmented_transition_current_1 = (the stongest)
		rtd_outl(0xb8000C94, 0x0E739CE7);	//SL_1 = 5'b01110 (3*13=x39)
		rtd_outl(0xb8000C98, 0x39CE739C);	//SL_1 = 5'b01110 (3*13=x39)
						//Iout_1 = 40u*8/4*39=3.12mA
		rtd_outl(0xb800DA40, 0x03000202);   // HDMI bandgap power on
	}

#ifdef ENABLE_DISP_BISR
	//frank@06252013 add below code to do the dispI/dispD BistR
	unsigned char DispIBISRFlag = 0, DispDBISRFlag = 0;

//rtd_outl(0xb800da40,0x03000202);
//rtd_outl(0xb800d10c,0x00000000);
//rtd_outl(0xb800d404,0x00170682);
//rtd_outl(0xb800d410,0x00000003);
//rtd_outl(0xb800d20c,0x00000288);
//rtd_outl(0xb800d380,0x47c20054);
rtd_outl(0xb8005210,0x80000000);
rtd_outl(0xb8005510,0x80000000);
mdelay(1);
rtd_outl(0xb8020000,0x000000ef);
rtd_outl(0xb8022284,0x0000000e);
//rtd_outl(0xb8024004,0x00000001);
rtd_outl(0xb8022210,0x40000001);
rtd_outl(0xb8022244,0x40000001);
//rtd_outl(0xb8028028,0x00000004);
//rtd_outl(0xb8028294,0x00000000);
//rtd_outl(0xb802cf58,0x00000001);
//rtd_outl(0xb8006004,0x0080a0a0);
//rtd_outl(0xb8031104,0x00000003);
//rtd_outl(0xb8031114,0x00000003);
//rtd_outl(0xb802f200,0x00000003);
//rtd_outl(0xb802f300,0x00000003);
//rtd_outl(0xb802f020,0x00000003);

	rtd_outl(0xb8000f00,0x0000001f);
	rtd_outl(0xb8000f04,0x0000001f);
	mdelay(1);

	if((rtd_inl(0xb8000f20)&0x1F) == 0x1f)
		DispIBISRFlag = 1;

	if((rtd_inl(0xb8000f24)&0x1F) == 0x1f)
		DispDBISRFlag = 1;

	rtd_outl(0xb8000f10, 0x1F);
	rtd_outl(0xb8000f14, 0x1F);

	printf("DispI : Finish BISR testing %s\n", (DispIBISRFlag ? "done" : "fail" ) );
	printf("DispD : Finish BISR testing %s\n", (DispDBISRFlag ? "done" : "fail" ) );
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

#if 0 // ck mark debug msg
void dump_register(void)
{
	printf("0xb8000490 : (%x) \n", rtd_inl(0xb8000490));
	printf("0xb8000494 : (%x) \n", rtd_inl(0xb8000494));
	printf("0xb8000640 : (%x) \n", rtd_inl(0xb8000640));

	printf("============ dtg 4k2k ============\n");
	printf("0xb8028000 : (%x) \n", rtd_inl(0xb8028000));
	printf("0xb8028004 : (%x) \n", rtd_inl(0xb8028004));
	printf("0xb8028008 : (%x) \n", rtd_inl(0xb8028008));
	printf("0xb802800C : (%x) \n", rtd_inl(0xb802800C));
	printf("0xb8028010 : (%x) \n", rtd_inl(0xb8028010));
	printf("0xb8028014 : (%x) \n", rtd_inl(0xb8028014));
	printf("0xb8028018 : (%x) \n", rtd_inl(0xb8028018));
	printf("0xb802801C : (%x) \n", rtd_inl(0xb802801C));
	printf("0xb8028028 : (%x) \n", rtd_inl(0xb8028028));
	printf("0xb8028294 : (%x) \n", rtd_inl(0xb8028294));

	printf("============ mtg 4k2k ============\n");
	printf("0xb8028100 : (%x) \n", rtd_inl(0xb8028100));
	printf("0xb8028108 : (%x) \n", rtd_inl(0xb8028108));
	printf("0xb802810C : (%x) \n", rtd_inl(0xb802810C));
	printf("0xb8028110 : (%x) \n", rtd_inl(0xb8028110));
	printf("0xb8028114 : (%x) \n", rtd_inl(0xb8028114));
	printf("0xb8028118 : (%x) \n", rtd_inl(0xb8028118));
	printf("0xb802811C : (%x) \n", rtd_inl(0xb802811C));
	printf("0xb8028120 : (%x) \n", rtd_inl(0xb8028120));
	printf("0xb8028124 : (%x) \n", rtd_inl(0xb8028124));

	printf("============ uzu ============\n");
	printf("0xb8029000 : (%x) \n", rtd_inl(0xb8029000));
	printf("0xb8029004 : (%x) \n", rtd_inl(0xb8029004));
	printf("0xb8029008 : (%x) \n", rtd_inl(0xb8029008));
	printf("0xb802900C : (%x) \n", rtd_inl(0xb802900C));
	printf("0xb8029024 : (%x) \n", rtd_inl(0xb8029024));
	printf("0xb8029010 : (%x) \n", rtd_inl(0xb8029010));
	printf("0xb8029014 : (%x) \n", rtd_inl(0xb8029014));
	printf("0xb8029018 : (%x) \n", rtd_inl(0xb8029018));
	printf("0xb802901C : (%x) \n", rtd_inl(0xb802901C));
	printf("0xb8029020 : (%x) \n", rtd_inl(0xb8029020));
	printf("0xb8029028 : (%x) \n", rtd_inl(0xb8029028));

	printf("============ vby1 ============\n");
	printf("0xb802D100 : (%x) \n", rtd_inl(0xb802D100));
	printf("0xb802D104 : (%x) \n", rtd_inl(0xb802D104));
	printf("0xb802D108 : (%x) \n", rtd_inl(0xb802D108));
	printf("0xb802D10C : (%x) \n", rtd_inl(0xb802D10C));
	printf("0xb802D130 : (%x) \n", rtd_inl(0xb802D130));
	printf("0xb802D134 : (%x) \n", rtd_inl(0xb802D134));
	printf("0xb802D138 : (%x) \n", rtd_inl(0xb802D138));
	printf("0xb802D13C : (%x) \n", rtd_inl(0xb802D13C));
	printf("0xb802D140 : (%x) \n", rtd_inl(0xb802D140));
	printf("0xb802D144 : (%x) \n", rtd_inl(0xb802D144));
	printf("0xb802D148 : (%x) \n", rtd_inl(0xb802D148));
	printf("0xb802D14C : (%x) \n", rtd_inl(0xb802D14C));
	printf("0xb802D150 : (%x) \n", rtd_inl(0xb802D150));
	printf("0xb802D154 : (%x) \n", rtd_inl(0xb802D154));
	printf("0xb802D158 : (%x) \n", rtd_inl(0xb802D158));
	printf("0xb802D15C : (%x) \n", rtd_inl(0xb802D15C));
	printf("0xb802D160 : (%x) \n", rtd_inl(0xb802D160));
	printf("0xb802D164 : (%x) \n", rtd_inl(0xb802D164));
	printf("0xb802D168 : (%x) \n", rtd_inl(0xb802D168));
	printf("0xb802D16C : (%x) \n", rtd_inl(0xb802D16C));
	printf("0xb802D170 : (%x) \n", rtd_inl(0xb802D170));
	printf("0xb802D174 : (%x) \n", rtd_inl(0xb802D174));

	printf("============ vby1 CMI============\n");

	printf("0xb800da40 : (%x) \n", rtd_inl(0xb800da40));
	printf("0xb8000864 : (%x) \n", rtd_inl(0xb8000864));
	printf("0xb80008c8 : (%x) \n", rtd_inl(0xb80008c8));

	printf("0xb8000498 : (%x) \n", rtd_inl(0xb8000498));
	printf("0xb800049c : (%x) \n", rtd_inl(0xb800049c));

	printf("0xb802D600 : (%x) \n", rtd_inl(0xb802D600));
	printf("0xb802D604 : (%x) \n", rtd_inl(0xb802D604));
	printf("0xb802D60c : (%x) \n", rtd_inl(0xb802D60c));
	printf("0xb802D610 : (%x) \n", rtd_inl(0xb802D610));

	printf("0xb802D6c0 : (%x) \n", rtd_inl(0xb802D6c0));
	printf("0xb802D6c8 : (%x) \n", rtd_inl(0xb802D6c8));
	printf("0xb802D6cc : (%x) \n", rtd_inl(0xb802D6cc));
	printf("0xb802D6d0 : (%x) \n", rtd_inl(0xb802D6d0));
	printf("0xb802D6d4 : (%x) \n", rtd_inl(0xb802D6d4));
	printf("0xb802D6dc : (%x) \n", rtd_inl(0xb802D6dc));
	printf("0xb802D6d8 : (%x) \n", rtd_inl(0xb802D6d8));
	printf("0xb802D6e0 : (%x) \n", rtd_inl(0xb802D6e0));
	printf("0xb802D6e8 : (%x) \n", rtd_inl(0xb802D6e8));
	printf("0xb802D6ec : (%x) \n", rtd_inl(0xb802D6ec));
	printf("0xb802D6f0 : (%x) \n", rtd_inl(0xb802D6f0));
	printf("0xb802D6f4 : (%x) \n", rtd_inl(0xb802D6f4));
	printf("0xb802D6fc : (%x) \n", rtd_inl(0xb802D6fc));
	printf("0xb802D6f8 : (%x) \n", rtd_inl(0xb802D6f8));
	printf("0xb802D648 : (%x) \n", rtd_inl(0xb802D648));

	printf("0xb8060230 : (%x) \n", rtd_inl(0xb8060230));
	printf("0xb8061100 : (%x) \n", rtd_inl(0xb8061100));
	printf("0xb8061108 : (%x) \n", rtd_inl(0xb8061108));
}
#endif

#if 0 // cklai@mark unused code
void vby1_4k2k_test_script(void)
{
	UINT16 cnt=0xfff;

	cnt = 0xfff; /* prevent compile warning */

#ifdef VBY_ONE_PANEL_CMI_V500_4K2K_VBY1
	rtd_outl(0xb8000490, 0x01f0142a);	// 297M Hz
	rtd_outl(0xb8000494, 0x01520042);	// DPLL div=1 , DPLL power on
	rtd_outl(0xb8000640, 0x00000005);	// DPLL div=1 , DPLL power on

	rtd_outl(0xb8028000, 0x11000000);	// free run mode
	rtd_outl(0xb8028004, 0x21f00201);	// Hx2/Vx2 , 4-pixel mode
	rtd_outl(0xb8028008, 0x0000000F);	// Hsync width

	rtd_outl(0xb802800C, 0x112F112F);	// DHtotal=4400
	rtd_outl(0xb8028010, 0x00000005);	// Vsync widths
	rtd_outl(0xb8028014, 0x000008C9);	// DVtotal=2250
	rtd_outl(0xb8028018, 0x01181018);	// DH_den_sta,DH_den_end
	rtd_outl(0xb802801C, 0x002d089d);	// DV_den_sta,DV_den_end

	rtd_outl(0xb8028028, 0x00000004);	// Double Buffer Control
	rtd_outl(0xb8028294, 0x00000000);	// dclk = dpll / 1 = 297MHz

	rtd_outl(0xb8028100, 0x00008C01);	// Main Display enable
	rtd_outl(0xb8028108, 0x0CD40000);	// Main Border Color
	rtd_outl(0xb802810C, 0x00000000);	// Main Background Color
	rtd_outl(0xb8028110, 0x00000F00);	// Main DEN_H_str,Main DEN_H_end
	rtd_outl(0xb8028114, 0x00000870);	// Main DEN_V_str,Main DEN_V_end
	rtd_outl(0xb8028118, 0x00000F00);	// Main Background_H_str,Main Background_H_end
	rtd_outl(0xb802811C, 0x00000870);	// Main Background_V_str,Main Background_V_end
	rtd_outl(0xb8028120, 0x00000F00);	// Main Active_H_str,Main Active_H_end
	rtd_outl(0xb8028124, 0x00000870);	// Main Active_V_str,Main Active_V_end

	//------------------------------------------------------------------------------------------------------------
	//SFG, 4 Pixel Mode, DTG_DH_ST_END = 0x01181018, DTG_HS_Width = 64, DTG_VS_Width = 8
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D100, 0x00000840);	//10-bit Mode, Dout Enable
	rtd_outl(0xb802D104, 0x8000FFFF);	//PIF_Clock = Dclk/4, Force to background enable
	rtd_outl(0xb802D108, 0x01234567);	//Port A~H mapping
	rtd_outl(0xb802D10C, 0x89ABCDEF);	//Port I~P mapping
	rtd_outl(0xb802D130, 0x00000000);	//SEG 0/1/2/3, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D134, 0x00000000);	//SEG 4/5/6/7, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D138, 0x00000000);	//SEG 8/9/10/11, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D13C, 0x00000000);	//SEG 12/13/14/15, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D140, 0x0000003F);	//4-SEG, 16-Port, No H-Flip
	rtd_outl(0xb802D144, 0x000003C0);	//SEG 0/1 Start
	rtd_outl(0xb802D148, 0x07800B40);	//SEG 2/3 Start
	rtd_outl(0xb802D14C, 0x00000000);	//SEG 4/5 Start
	rtd_outl(0xb802D150, 0x00000000);	//SEG 6/7 Start
	rtd_outl(0xb802D154, 0x00000000);	//SEG 8/9 Start
	rtd_outl(0xb802D158, 0x00000000);	//SEG 10/11 Start
	rtd_outl(0xb802D15C, 0x00000000);	//SEG 12/13 Start
	rtd_outl(0xb802D160, 0x00000000);	//SEG 14/15 Start
	rtd_outl(0xb802D164, 0x00000000);	//Disable ByPass Mode
	rtd_outl(0xb802D168, 0x004003D8);	//HS_Width = 64 dclk (ゲ4计, nタ俱计)
						//hsync_delay = 984 = data_length/Pixel_Mode +24
	rtd_outl(0xb802D16C, 0x00070000);	//VSYNC_ST = 0, V_SYNC = DV_Width
	rtd_outl(0xb802D170, 0x00460040);	//sfg_dh_den_sta = DH_ST / pixel_mode = 280/4, req_start = DH_ST / pixel_mode - 6 = 280/4 - 6 = 64
	rtd_outl(0xb802D174, 0x78000000);	//final_line_length = 3840, hsync_threshold = 0

	//other
	rtd_outl(0xb800da40, 0x03000202);	//HDMI bandgap

	rtd_outl(0xb8000864, 0x7070f0f0);	//HPDN and LOCKN pin share
	//rtd_outl(0xb80008a8, 0xff770000);	//HPDN and LOCKN pin share
	rtd_outl(0xb80008c8, 0x00330000);	//HPDN and LOCKN sel
	//rtd_outl(0xb80008c8, 0x00110000);	//HPDN and LOCKN sel

	//LS PLL
	rtd_outl(0xb8000498, 0x0140042a);	//LS PLL M=22,N=2
	rtd_outl(0xb800049c, 0x01520043);	//LS PLL power off
	rtd_outl(0xb800049c, 0x01520042);	//LS PLL power on

	//VBy1 MAC
	rtd_outl(0xb802D600, 0x00010000);	//data format select 30bpp
	rtd_outl(0xb802D604, 0x04100404);	//4pixel mode,16lane,4section,4Byte
	rtd_outl(0xb802D60c, 0x00000001);	//FIFO boundary
	rtd_outl(0xb802D610, 0xfa000000);	//VBy1 enable

	//VBy1 PHY 0
	rtd_outl(0xb802D6c0, 0x00000011);	//digital PHY set
	rtd_outl(0xb802D6c8, 0x00ff0000);	//lane enable

	rtd_outl(0xb802D6cc, 0x00000000);	//Pre-emphasis
	rtd_outl(0xb802D6d0, 0x77777777);	//Driving
	rtd_outl(0xb802D6d4, 0xd0000000);	//Z0 calibration
	rtd_outl(0xb802D6dc, 0x54000001);	//PLL set , pre-div is 1 , Mdiv is 10
	rtd_outl(0xb802D6d8, 0xc000068f);	//PLL enable , RS=4K

	cnt = 0xfff;
	while(cnt-- != 0);

	rtd_outl(0xb802D6d8, 0xc00ff68f);	//VBy1 port power on

	//VBy1 PHY 1
	rtd_outl(0xb802D6e0, 0x00000011);	//digital PHY set
	rtd_outl(0xb802D6e8, 0x00ff0000);	//lane enable

	rtd_outl(0xb802D6ec, 0x00000000);	//Pre-emphasis
	rtd_outl(0xb802D6f0, 0x77777777);	//Driving
	rtd_outl(0xb802D6f4, 0xd0000000);	//Z0 calibration
	rtd_outl(0xb802D6fc, 0x54000001);	//PLL set , pre-div is 1 , Mdiv is 10
	//rtd_outl(0xb802D6f8, 0xc00006cf);	//PLL enable
	rtd_outl(0xb802D6f8, 0xc000068f);	//PLL enable , RS=4K

	cnt = 0xfff;
	while(cnt-- != 0);

	rtd_outl(0xb802D6f8, 0xc00ff68f);	//VBy1 port power on

	rtd_outl(0xb802D648, 0x00000001);	//lane swap

#elif defined(VBY_ONE_PANEL_CHINA_STAR_4K2K_VBY1)

	rtd_outl(0xb8000490, 0x01f0142a);	// 297M Hz
	rtd_outl(0xb8000494, 0x01520042);	// DPLL div=1 , DPLL power on

	rtd_outl(0xb8028000, 0x11000000);	// free run mode
	rtd_outl(0xb8028004, 0x10f00201);	// Hx2/Vx2 , 2-pixel mode
	rtd_outl(0xb8028008, 0x0000000F);	// Hsync width

	rtd_outl(0xb802800C, 0x112F112F);	// DHtotal=4400
	rtd_outl(0xb8028010, 0x00000005);	// Vsync widths
	rtd_outl(0xb8028014, 0x000008C9);	// DVtotal=2250
	rtd_outl(0xb8028018, 0x01181018);	// DH_den_sta,DH_den_end
	rtd_outl(0xb802801C, 0x002d089d);	// DV_den_sta,DV_den_end

	rtd_outl(0xb8028028, 0x00000004);	// Double Buffer Control
	rtd_outl(0xb8028294, 0x00000000);	// dclk = dpll / 1 = 297MHz

	rtd_outl(0xb8028100, 0x00008C01);	// Main Display enable
	rtd_outl(0xb8028108, 0x0CD40000);	// Main Border Color
	rtd_outl(0xb802810C, 0x00000000);	// Main Background Color
	rtd_outl(0xb8028110, 0x00000F00);	// Main DEN_H_str,Main DEN_H_end
	rtd_outl(0xb8028114, 0x00000870);	// Main DEN_V_str,Main DEN_V_end
	rtd_outl(0xb8028118, 0x00000F00);	// Main Background_H_str,Main Background_H_end
	rtd_outl(0xb802811C, 0x00000870);	// Main Background_V_str,Main Background_V_end
	rtd_outl(0xb8028120, 0x00000F00);	// Main Active_H_str,Main Active_H_end
	rtd_outl(0xb8028124, 0x00000870);	// Main Active_V_str,Main Active_V_end

	rtd_outl(0xb802D100, 0x00000840);	//10-bit Mode, Dout Enable
	rtd_outl(0xb802D104, 0x4000FFFF);	//PIF_Clock = Dclk/2, Force to background enable
	rtd_outl(0xb802D108, 0x01234567);	//Port A~H mapping
	rtd_outl(0xb802D10C, 0x89ABCDEF);	//Port I~P mapping
	rtd_outl(0xb802D130, 0x00000000);	//SEG 0/1/2/3, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D134, 0x00000000);	//SEG 4/5/6/7, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D138, 0x00000000);	//SEG 8/9/10/11, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D13C, 0x00000000);	//SEG 12/13/14/15, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D140, 0x00000017);	//2-SEG, 8-Port, No H-Flip
	rtd_outl(0xb802D144, 0x00000780);	//SEG 0/1 Start
	rtd_outl(0xb802D148, 0x00000000);	//SEG 2/3 Start
	rtd_outl(0xb802D14C, 0x00000000);	//SEG 4/5 Start
	rtd_outl(0xb802D150, 0x00000000);	//SEG 6/7 Start
	rtd_outl(0xb802D154, 0x00000000);	//SEG 8/9 Start
	rtd_outl(0xb802D158, 0x00000000);	//SEG 10/11 Start
	rtd_outl(0xb802D15C, 0x00000000);	//SEG 12/13 Start
	rtd_outl(0xb802D160, 0x00000000);	//SEG 14/15 Start
	rtd_outl(0xb802D164, 0x00000000);	//Disable ByPass Mode
	rtd_outl(0xb802D168, 0x00400798);	//HS_Width = 64 dclk (ゲ4计, nタ俱计)
						//hsync_delay = 1944 = data_length/Pixel_Mode +24
	rtd_outl(0xb802D16C, 0x00070000);	//VSYNC_ST = 0, V_SYNC = DV_Width
	rtd_outl(0xb802D170, 0x00860080);	//sfg_dh_den_sta = DH_ST / pixel_mode = 280/4, req_start = DH_ST / pixel_mode - 6 = 280/4 - 6 = 274
	rtd_outl(0xb802D174, 0x78000000);	//final_line_length = 3840, hsync_threshold = 0

	//VBy1 PHY 0
	rtd_outl(0xb802D6c0, 0x00000011);	//digital PHY set
	rtd_outl(0xb802D6c8, 0x00ff0000);	//lane enable

	rtd_outl(0xb802D6cc, 0x00000000);	//Pre-emphasis
	rtd_outl(0xb802D6d0, 0x77777777);	//Driving
	rtd_outl(0xb802D6d4, 0xd0000000);	//Z0 calibration
	rtd_outl(0xb802D6dc, 0x54000001);	//PLL set , pre-div is 1 , Mdiv is 10
	//rtd_outl(0xb802D6d8, 0xc00006cf);	//PLL enable
	rtd_outl(0xb802D6d8, 0xc000068f);	//PLL enable , RS=4K
	cnt = 0xfff;
	while(cnt-- != 0);
	rtd_outl(0xb802D6d8, 0xc00ff68f);	//VBy1 port power on

	//VBy1 PHY 1
	rtd_outl(0xb802D6e0, 0x00000011);	//digital PHY set
	rtd_outl(0xb802D6e8, 0x00ff0000);	//lane enable

	rtd_outl(0xb802D6ec, 0x00000000);	//Pre-emphasis
	rtd_outl(0xb802D6f0, 0x77777777);	//Driving
	rtd_outl(0xb802D6f4, 0xd0000000);	//Z0 calibration
	rtd_outl(0xb802D6fc, 0x54000001);	//PLL set , pre-div is 1 , Mdiv is 10
	//rtd_outl(0xb802D6f8, 0xc00006cf);	//PLL enable
	rtd_outl(0xb802D6f8, 0xc000068f);	//PLL enable , RS=4K
	cnt = 0xfff;
	while(cnt-- != 0);
	rtd_outl(0xb802D6f8, 0xc00ff68f);	//VBy1 port power on


#endif
}
#endif

void uzu_main_444_bypass_4k2k(void)
{
#ifndef CONFIG_SYS_PANEL_DISABLE_PATTERN_GEN
	rtd_outl(0xb8029000, 0x00EF0031);//color bar
#endif
	//rtd_outl(0xb8029004, 0x02000282);	//444,bypass scale UP for v
	rtd_outl(0xb8029004, 0x00000080);	// UZU disable
	//HOR/VER_factor0x1802_9008 & 0x1802_900c
	//そΑ (In_size / Out_size ) * 2^20
	//絛瞅0 ° 2^20-1
	rtd_outl(0xb8029008, 0x00060000);//HOR_FAC 1x
	//rtd_outl(0xb802900C, 0x00087000);//VER_FAC 1x
	rtd_outl(0xb802900C, 0x00071c71);//VER_FAC 1x
	rtd_outl(0xb8029024, 0x0000ffff);//HOR/VER_INI
	//rtd_outl(0xb8027328, 0x00000004);//combine fifo enable
	//rtd_outl(0xb8027330, 0x00000001);//double buffer

	//Delta1/20x1802_9010 & 0x1802_9014
	//SEGMENT1/20x1802_9018 & 0x1802_901c
	//SEGMENT30x1802_9020
	//弧out_width = 2(segment1+segment2)+segment3
	//For linear scaling case, delta1 & delta2 & segment1 &segment2 常砞Θ0
	rtd_outl(0xb8029010, 0x00000000);//12:0==>HOR_DELTA1
	rtd_outl(0xb8029014, 0x00000000);//12:0==>HOR_DELTA2
	rtd_outl(0xb8029018, 0x00000000);//10:0==>SEGMENT1
	rtd_outl(0xb802901C, 0x00000000);//10:0==>SEGMENT2
	rtd_outl(0xb8029020, 0x00000500);//10:0==>SEGMENT3

	//DM_UZU(_Input_Size)  	0x1802_9028
	rtd_outl(0xb8029028, 0x07800438);//Input Size (1920x1080)
}

void lvds_2k1k_120_4ports_script(void)
{
//#if defined(LVDS_PANEL_MILLET3_2K1K_120)
	//dpll
	rtd_outl(0xb8000490, 0x0210142A);	// M = 35, N = 3
	rtd_outl(0xb8000494, 0x01720042);	// DIV = 1 , DPLL power on
	rtd_outl(0xb8000640, 0x07500001);	// OFFSET = 1872, DPLL_CLK = 297MHz
	rtd_outl(0xb8000640, 0x07500005);	// Load in
	//dtg
	rtd_outl(0xb8028000, 0x11040000);	// free run mode, force to bg
	rtd_outl(0xb8028004, 0xC0000000);	// SR Bypass
	rtd_outl(0xb8028008, 0x0000000F);	// Hsync width
	rtd_outl(0xb802800C, 0x08970897);	// DHtotal=2200
	rtd_outl(0xb8028010, 0x00000003);	// Vsync width
	rtd_outl(0xb8028014, 0x00000464);	// DVtotal=1125
	rtd_outl(0xb8028018, 0x008c080c);	// DH_den_sta,DH_den_end
	rtd_outl(0xb802801C, 0x0016044E);	// DV_den_sta,DV_den_end
	rtd_outl(0xb8028028, 0x00000004);	// Double Buffer Control
	rtd_outl(0xb8028294, 0x00000000);	// dclk = dpll / 1 = 297MHz
	//mtg
	rtd_outl(0xb8028100, 0x00000001);	// Main Display enable
	rtd_outl(0xb8028108, 0x0CD40000);	// Main Border Color
	rtd_outl(0xb802810C, 0x00000000);	// Main Background Color
	rtd_outl(0xb8028110, 0x00000780);	// Main DEN_H_str,Main DEN_H_end
	rtd_outl(0xb8028114, 0x00000438);	// Main DEN_V_str,Main DEN_V_end
	rtd_outl(0xb8028118, 0x00000780);	// Main Background_H_str,Main Background_H_end
	rtd_outl(0xb802811C, 0x00000438);	// Main Background_V_str,Main Background_V_end
	rtd_outl(0xb8028120, 0x00000780);	// Main Active_H_str,Main Active_H_end
	rtd_outl(0xb8028124, 0x00000438);	// Main Active_V_str,Main Active_V_end
	//color bar
#ifndef CONFIG_SYS_PANEL_DISABLE_PATTERN_GEN
	rtd_outl(0xb8029000, 0x00EF0031);		// D-domain Pattern Gen Setting
#endif
	rtd_outl(0xb8029028, 0x07800438);		//Input Size (1920x1080)

	//lvds
	//------------------------------------------------------------------------------------------------------------
	//DCLK DIV
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8028294, 0x00000000);	//DCLK = DPLL_Clk / 1

	//------------------------------------------------------------------------------------------------------------
	//SFG, 1 Pixel Mode, DH_ST_END = 0x008C080C, DTG_HS_Width = 16, DTG_VS_Width = 4
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D100, 0x000008c0);	//10-bit Mode, Dout Enable
	rtd_outl(0xb802D104, 0x8000FFFF);	//PIF_Clock = Dclk/4, Force to background enable
//	rtd_outl(0xb802D108, 0x23010000);	//Port A~H mapping
//	rtd_outl(0xb802D10C, 0x00000000);	//Port I~P mapping
	rtd_outl(0xb802D130, 0x00000000);	//SEG 0/1/2/3, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D134, 0x00000000);	//SEG 4/5/6/7, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D138, 0x00000000);	//SEG 8/9/10/11, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D13C, 0x00000000);	//SEG 12/13/14/15, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D140, 0x00000003);	//1-SEG, 4-Port, No H-Flip
	rtd_outl(0xb802D144, 0x00000000);	//SEG 0/1 Start
	rtd_outl(0xb802D148, 0x00000000);	//SEG 2/3 Start
	rtd_outl(0xb802D14C, 0x00000000);	//SEG 4/5 Start
	rtd_outl(0xb802D150, 0x00000000);	//SEG 6/7 Start
	rtd_outl(0xb802D154, 0x00000000);	//SEG 8/9 Start
	rtd_outl(0xb802D158, 0x00000000);	//SEG 10/11 Start
	rtd_outl(0xb802D15C, 0x00000000);	//SEG 12/13 Start
	rtd_outl(0xb802D160, 0x00000000);	//SEG 14/15 Start
	rtd_outl(0xb802D164, 0x00000000);	//Disable ByPass Mode
	rtd_outl(0xb802D168, 0x000F0798);	//HS_Width = 16 dclk = 16*Pixel_Mode*n DH_Width (ゲ4计, nタ俱计)
						//hsync_delay = 1944 = data_length/Pixel_Mode +24
	rtd_outl(0xb802D16C, 0x00030000);	//VSYNC_ST = 0, V_SYNC = DV_Width
	rtd_outl(0xb802D170, 0x008C0086);	//sfg_dh_den_sta = DH_ST = 140
						//req_start = DH_ST - 6 = 140 - 6 = 134
	rtd_outl(0xb802D174, 0x3C000000);	//final_line_length = 1920, hsync_threshold = 0

	//------------------------------------------------------------------------------------------------------------
	//PIF
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D000, 0x00000000);	//Select LVDS(Mini-LVDS) clock & data
	rtd_outl(0xb802D010, 0x000002F0);	//PN not Swap, LVDS not Mirror, LVDS Mapping Table1, LVDS Port Enable

	//------------------------------------------------------------------------------------------------------------
	//LVDS Pin Share
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000890, 0x00000000);	//A-Port LVDS pin share
	rtd_outl(0xb8000894, 0x00000000);	//A-Port LVDS pin share
	rtd_outl(0xb8000898, 0x00000000);	//B-Port LVDS pin share
	rtd_outl(0xb80008A0, 0x00000000);	//C-Port LVDS pin share
	rtd_outl(0xb80008A4, 0x00000000);	//C-Port LVDS pin share
	rtd_outl(0xb80008A8, 0x00000000);	//D-Port LVDS pin share

	//------------------------------------------------------------------------------------------------------------
	//LVDS/mini-LVDS TX PHY
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000C00, 0xEC8DAED9);	//Current_source_0 power on, PLL_0 power ON, LDO_0 pow signal power on
						//EPI_CM_0 => Select LVDS Mode
						//VCOM_SELL_0 = 3'b100
						//IBHN_0 = 40uA, IBHX_0 = 40uA, IBTX_0 = 80uA, CML_Pre_Driver_0 = 60uA
						//PLL_CP_0 = 3pF, PLL_CS_0 = 63pF, PLL_IP_0 = 10uA
						//EPI_VSELL_0 = 2.08V
						//VCOM_0 = 40u*24/8*10.04k = 1.2048V
	rtd_outl(0xb8000C04, 0x119FE7E1);	//PLL_RS_0 = 6Kohm, PLL_PI_IP_0 = 180uA, PI_Phase_0 = ??????, PI_0 Disable
	rtd_outl(0xb8000C08, 0x00080580);	//PLL_M_0 = 7, PLL_N_0 = 1, PLL_DIV_0 = 1
						//SWAPL_0 = 0 (7bit LVDS MSB First)
						//PLL_PI_RL_0 = 2.6kohm, PLL_LDO_0 = 1.76V
						//PLL_BW_0 = 10u/(2*pi)*6k*63/(63+3)*3G/7 = 3.9MHz
	rtd_outl(0xb8000C0C, 0x0FFF0FFF);	//Data/Clock_Selection_0 (LVDS Mode, All Pair PI Bypass)
	rtd_outl(0xb8000C10, 0x00000000);	//Pre-emphasis_enable_0 = 0, LAG_0 Disable
	rtd_outl(0xb8000C14, 0x00000000);	//segmented_transition_enable_0 = 0; EPI_Mode_0 disable
	rtd_outl(0xb8000C18, 0x00000FFF);	//Parallel_Resistor_0 Disable (double driving disable), TX_differential_0 enable
	rtd_outl(0xb8000C1C, 0x00AAAAAA);	//Parallel_Resistor_0 = 100ohm
	rtd_outl(0xb8000C20, 0x00000000);	//segmented_transition_timing_0 = (2'b00 => T0=slow, T1=slow)
	rtd_outl(0xb8000C2C, 0x00000000);	//Pre-emphasis_0 = X4 (the weakest)
	rtd_outl(0xb8000C30, 0x00000000);	//Pre-emphasis_0 = X4 (the weakest)
	rtd_outl(0xb8000C34, 0x0000000F);	//NMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C38, 0xFFFFFFFF);	//NMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C3C, 0x0000000F);	//PMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C40, 0xFFFFFFFF);	//PMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C44, 0x0E739CE7);	//SL_0 = 5'b11100 (3*13=x39)
	rtd_outl(0xb8000C48, 0x39CE739C);	//SL_0 = 5'b11100 (2*13=x39)
						//Iout_0 = 40u*8/4*39=3.12mA
	rtd_outl(0xb8000C50, 0xEC8DAED9);	//Current_source_1 power on, PLL_1 power ON, LDO_1 pow signal power on
						//EPI_CM_1 => Select LVDS Mode
						//VCOM_SELL_1 = 3'b100
						//IBHN_1 = 40uA, IBHX_1 = 40uA, IBTX_1 = 80uA, CML_Pre_Driver_1 = 60uA
						//PLL_CP_1 = 3pF, PLL_CS_1 = 63pF, PLL_IP_1 = 10uA
						//EPI_VSELL_1 = 2.08V
						//VCOM_1 = 40u*24/8*10.04k = 1.2048V
	rtd_outl(0xb8000C54, 0x219FE7E1);	//PLL_RS_1 = 6Kohm, PLL_PI_IP_1 = 180uA, PI_Phase_1 = ??????, PI_1 Disable
	rtd_outl(0xb8000C58, 0x00080580);	//PLL_M_1 = 7, PLL_N_1 = 1, PLL_DIV_1 = 1
						//SWAPL_1 = 0 (7bit LVDS MSB First)
						//PLL_PI_RL_1 = 2.6kohm, PLL_LDO_1 = 1.76V
						//PLL_BW_1 = 10u/(2*pi)*6k*63/(63+3)*3G/7 = 3.9MHz
	rtd_outl(0xb8000C5C, 0x0FFF0FFF);	//Data/Clock_Selection_1 (LVDS Mode, All Pair PI Bypass)
	rtd_outl(0xb8000C60, 0x00000000);	//Pre-emphasis_enable_1 = 0, LAG_1 Disable
	rtd_outl(0xb8000C64, 0x00000000);	//segmented_transition_enable_1 = 0; EPI_Mode_1 disable
	rtd_outl(0xb8000C68, 0x00000FFF);	//Parallel_Resistor_1 Disable (double driving disable), TX_differential_1 enable
	rtd_outl(0xb8000C6C, 0x00AAAAAA);	//Parallel_Resistor_1 = 100ohm
	rtd_outl(0xb8000C70, 0x00000000);	//segmented_transition_timing_1 = 2'b00 => (T0=slow, T1=slow)
	rtd_outl(0xb8000C7C, 0x00000000);	//Pre-emphasis_1 = X4 (the weakest)
	rtd_outl(0xb8000C80, 0x00000000);	//Pre-emphasis_1 = X4 (the weakest)
	rtd_outl(0xb8000C84, 0x0000000F);	//NMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C88, 0xFFFFFFFF);	//NMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C8C, 0x0000000F);	//PMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C90, 0xFFFFFFFF);	//PMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C94, 0x0E739CE7);	//SL_1 = 5'b01110 (3*13=x39)
	rtd_outl(0xb8000C98, 0x39CE739C);	//SL_1 = 5'b01110 (3*13=x39)
						//Iout_1 = 40u*8/4*39=3.12mA
	rtd_outl(0xb800DA40, 0x03000202);	// HDMI Power Enable

//#endif
}

#if 0 // cklai@mark unused code
void lvds_4k2k_30_4ports_script(void)
{
//#if defined(LVDS_PANEL_MILLET3_4K2K_30)
	//set dpll
	rtd_outl(0xb8000490, 0x0210142A);	// M = 35, N = 3
	rtd_outl(0xb8000494, 0x01720042);	// DIV = 1 , DPLL power on
	rtd_outl(0xb8000640, 0x07500001);	// OFFSET = 1872, DPLL_CLK = 297MHz
	rtd_outl(0xb8000640, 0x07500005);	// Load in
	//dtg 4k2k
	rtd_outl(0xb8028000, 0x11000000);	// free run mode
	rtd_outl(0xb8028004, 0xC5000000);	// SR Bypass
	rtd_outl(0xb8028008, 0x0000000F);	// Hsync width
	rtd_outl(0xb802800C, 0x112F112F);	// DHtotal=4400
	rtd_outl(0xb8028010, 0x00000005);	// Vsync widths
	rtd_outl(0xb8028014, 0x000008C9);	// DVtotal=2250
	rtd_outl(0xb8028018, 0x01181018);	// DH_den_sta,DH_den_end
	rtd_outl(0xb802801C, 0x002d089d);	// DV_den_sta,DV_den_end
	rtd_outl(0xb8028028, 0x00000004);	// Double Buffer Control
	rtd_outl(0xb8028294, 0x00000000);	// dclk = dpll / 1 = 297MHz
	//mtg 4k2k
	rtd_outl(0xb8028100, 0x00008C01);	// Main Display enable
	rtd_outl(0xb8028108, 0x0CD40000);	// Main Border Color
	rtd_outl(0xb802810C, 0x00000000);	// Main Background Color
	rtd_outl(0xb8028110, 0x00000F00);	// Main DEN_H_str,Main DEN_H_end
	rtd_outl(0xb8028114, 0x00000870);	// Main DEN_V_str,Main DEN_V_end
	rtd_outl(0xb8028118, 0x00000F00);	// Main Background_H_str,Main Background_H_end
	rtd_outl(0xb802811C, 0x00000870);	// Main Background_V_str,Main Background_V_end
	rtd_outl(0xb8028120, 0x00000F00);	// Main Active_H_str,Main Active_H_end
	rtd_outl(0xb8028124, 0x00000870);	// Main Active_V_str,Main Active_V_end
	//color bar
	rtd_outl(0xb8029000, 0x01DF0031);		// D-domain Pattern Gen Setting
	rtd_outl(0xb8029028, 0x0F000870);		//Input Size
	// lvds 4k2k 4port 1pixel 1seg
	//------------------------------------------------------------------------------------------------------------
	//SFG, 1 Pixel Mode, DTG_DH_ST_END = 0x01181018, DTG_HS_Width = 64, DTG_VS_Width = 8
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D100, 0x00000840);	//10-bit Mode, Dout Enable
	rtd_outl(0xb802D104, 0x8000FFFF);	//PIF_Clock = Dclk/4, Force to background enable
//	rtd_outl(0xb802D108, 0x23010000);	//Port A~H mapping
//	rtd_outl(0xb802D10C, 0x89ABCDEF);	//Port I~P mapping
	rtd_outl(0xb802D130, 0x00000000);	//SEG 0/1/2/3, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D134, 0x00000000);	//SEG 4/5/6/7, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D138, 0x00000000);	//SEG 8/9/10/11, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D13C, 0x00000000);	//SEG 12/13/14/15, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D140, 0x00000003);	//1-SEG, 4-Port, No H-Flip
	rtd_outl(0xb802D144, 0x00000000);	//SEG 0/1 Start
	rtd_outl(0xb802D148, 0x00000000);	//SEG 2/3 Start
	rtd_outl(0xb802D14C, 0x00000000);	//SEG 4/5 Start
	rtd_outl(0xb802D150, 0x00000000);	//SEG 6/7 Start
	rtd_outl(0xb802D154, 0x00000000);	//SEG 8/9 Start
	rtd_outl(0xb802D158, 0x00000000);	//SEG 10/11 Start
	rtd_outl(0xb802D15C, 0x00000000);	//SEG 12/13 Start
	rtd_outl(0xb802D160, 0x00000000);	//SEG 14/15 Start
	rtd_outl(0xb802D164, 0x00000000);	//Disable ByPass Mode
	rtd_outl(0xb802D168, 0x00400F18);	//HS_Width = 64 dclk (ゲ4计, nタ俱计)
										//hsync_delay = 984 = data_length/Pixel_Mode +24
	rtd_outl(0xb802D16C, 0x00070000);	//VSYNC_ST = 0, V_SYNC = DV_Width
	rtd_outl(0xb802D170, 0x01180112);	//sfg_dh_den_sta = DH_ST / pixel_mode = 280/4, req_start = DH_ST / pixel_mode - 6 = 280 - 6 = 274
	rtd_outl(0xb802D174, 0x78000000);	//final_line_length = 3840, hsync_threshold = 0

	//------------------------------------------------------------------------------------------------------------
	//PIF
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D000, 0x00000000);	//Select LVDS(Mini-LVDS) clock & data
	rtd_outl(0xb802D010, 0x000002F0);	//PN not Swap, LVDS not Mirror, LVDS Mapping Table1, LVDS Port Enable

	//------------------------------------------------------------------------------------------------------------
	//LVDS Pin Share
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000890, 0x00000000);	//A-Port LVDS pin share
	rtd_outl(0xb8000894, 0x00000000);	//A-Port LVDS pin share
	rtd_outl(0xb8000898, 0x00000000);	//B-Port LVDS pin share
	rtd_outl(0xb80008A0, 0x00000000);	//C-Port LVDS pin share
	rtd_outl(0xb80008A4, 0x00000000);	//C-Port LVDS pin share
	rtd_outl(0xb80008A8, 0x00000000);	//D-Port LVDS pin share

	//------------------------------------------------------------------------------------------------------------
	//LVDS/mini-LVDS TX PHY
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000C00, 0xEC8DAED9);	//Current_source_0 power on, PLL_0 power ON, LDO_0 pow signal power on
						//EPI_CM_0 => Select LVDS Mode
						//VCOM_SELL_0 = 3'b100
						//IBHN_0 = 40uA, IBHX_0 = 40uA, IBTX_0 = 80uA, CML_Pre_Driver_0 = 60uA
						//PLL_CP_0 = 3pF, PLL_CS_0 = 63pF, PLL_IP_0 = 10uA
						//EPI_VSELL_0 = 2.08V
						//VCOM_0 = 40u*24/8*10.04k = 1.2048V
	rtd_outl(0xb8000C04, 0x119FE7E1);	//PLL_RS_0 = 6Kohm, PLL_PI_IP_0 = 180uA, PI_Phase_0 = ??????, PI_0 Disable
	rtd_outl(0xb8000C08, 0x00080580);	//PLL_M_0 = 7, PLL_N_0 = 1, PLL_DIV_0 = 1
						//SWAPL_0 = 0 (7bit LVDS MSB First)
						//PLL_PI_RL_0 = 2.6kohm, PLL_LDO_0 = 1.76V
						//PLL_BW_0 = 10u/(2*pi)*6k*63/(63+3)*3G/7 = 3.9MHz
	rtd_outl(0xb8000C0C, 0x0FFF0FFF);	//Data/Clock_Selection_0 (LVDS Mode, All Pair PI Bypass)
	rtd_outl(0xb8000C10, 0x00000000);	//Pre-emphasis_enable_0 = 0, LAG_0 Disable
	rtd_outl(0xb8000C14, 0x00000000);	//segmented_transition_enable_0 = 0; EPI_Mode_0 disable
	rtd_outl(0xb8000C18, 0x00000FFF);	//Parallel_Resistor_0 Disable (double driving disable), TX_differential_0 enable
	rtd_outl(0xb8000C1C, 0x00AAAAAA);	//Parallel_Resistor_0 = 100ohm
	rtd_outl(0xb8000C20, 0x00000000);	//segmented_transition_timing_0 = (2'b00 => T0=slow, T1=slow)
	rtd_outl(0xb8000C2C, 0x00000000);	//Pre-emphasis_0 = X4 (the weakest)
	rtd_outl(0xb8000C30, 0x00000000);	//Pre-emphasis_0 = X4 (the weakest)
	rtd_outl(0xb8000C34, 0x0000000F);	//NMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C38, 0xFFFFFFFF);	//NMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C3C, 0x0000000F);	//PMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C40, 0xFFFFFFFF);	//PMOS segmented_transition_current_0 = (the stongest)
	rtd_outl(0xb8000C44, 0x0E739CE7);	//SL_0 = 5'b11100 (3*13=x39)
	rtd_outl(0xb8000C48, 0x39CE739C);	//SL_0 = 5'b11100 (2*13=x39)
						//Iout_0 = 40u*8/4*39=3.12mA
	rtd_outl(0xb8000C50, 0xEC8DAED9);	//Current_source_1 power on, PLL_1 power ON, LDO_1 pow signal power on
						//EPI_CM_1 => Select LVDS Mode
						//VCOM_SELL_1 = 3'b100
						//IBHN_1 = 40uA, IBHX_1 = 40uA, IBTX_1 = 80uA, CML_Pre_Driver_1 = 60uA
						//PLL_CP_1 = 3pF, PLL_CS_1 = 63pF, PLL_IP_1 = 10uA
						//EPI_VSELL_1 = 2.08V
						//VCOM_1 = 40u*24/8*10.04k = 1.2048V
	rtd_outl(0xb8000C54, 0x219FE7E1);	//PLL_RS_1 = 6Kohm, PLL_PI_IP_1 = 180uA, PI_Phase_1 = ??????, PI_1 Disable
	rtd_outl(0xb8000C58, 0x00080580);	//PLL_M_1 = 7, PLL_N_1 = 1, PLL_DIV_1 = 1
						//SWAPL_1 = 0 (7bit LVDS MSB First)
						//PLL_PI_RL_1 = 2.6kohm, PLL_LDO_1 = 1.76V
						//PLL_BW_1 = 10u/(2*pi)*6k*63/(63+3)*3G/7 = 3.9MHz
	rtd_outl(0xb8000C5C, 0x0FFF0FFF);	//Data/Clock_Selection_1 (LVDS Mode, All Pair PI Bypass)
	rtd_outl(0xb8000C60, 0x00000000);	//Pre-emphasis_enable_1 = 0, LAG_1 Disable
	rtd_outl(0xb8000C64, 0x00000000);	//segmented_transition_enable_1 = 0; EPI_Mode_1 disable
	rtd_outl(0xb8000C68, 0x00000FFF);	//Parallel_Resistor_1 Disable (double driving disable), TX_differential_1 enable
	rtd_outl(0xb8000C6C, 0x00AAAAAA);	//Parallel_Resistor_1 = 100ohm
	rtd_outl(0xb8000C70, 0x00000000);	//segmented_transition_timing_1 = 2'b00 => (T0=slow, T1=slow)
	rtd_outl(0xb8000C7C, 0x00000000);	//Pre-emphasis_1 = X4 (the weakest)
	rtd_outl(0xb8000C80, 0x00000000);	//Pre-emphasis_1 = X4 (the weakest)
	rtd_outl(0xb8000C84, 0x0000000F);	//NMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C88, 0xFFFFFFFF);	//NMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C8C, 0x0000000F);	//PMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C90, 0xFFFFFFFF);	//PMOS segmented_transition_current_1 = (the stongest)
	rtd_outl(0xb8000C94, 0x0E739CE7);	//SL_1 = 5'b01110 (3*13=x39)
	rtd_outl(0xb8000C98, 0x39CE739C);	//SL_1 = 5'b01110 (3*13=x39)
						//Iout_1 = 40u*8/4*39=3.12mA
	rtd_outl(0xb800DA40, 0x03000202);	// HDMI Power Enable
	//rtd_outl(0xb8020000, 0x000001FF);	// HDMI Power Enable


//#endif
}
#endif

void EPI_FHD_60HZ_Script(void)
{
	// Case for LGD demo
	// TM120,FHD,60HZ,32" Panel
	//

	// Bypass 12V panel power to EPI connector
	rtd_outl(0xb8061100, 0x00000010);		// bit4=1
	rtd_outl(0xb8061108, 0x00000010);		// bit4=1

	//set dpll
	rtd_outl(0xb8000490, 0x0210412A);	// M = 35, N = 6 for 148.5Mhz, IB=2u
	rtd_outl(0xb8000494, 0x01720042);	// DIV = 1 , DPLL power on
	rtd_outl(0xb8000640, 0x07500001);	// OFFSET = 1872, DPLL_CLK = 297MHz
	rtd_outl(0xb8000640, 0x07500005);	// Load in

	//set dtg
	rtd_outl(0xb8028000, 0x11000000);	// free run mode
	rtd_outl(0xb8028004, 0xC0000000);	// SR Bypass
	rtd_outl(0xb8028008, 0x0000000F);	// Hsync width
	rtd_outl(0xb802800C, 0x08970897);	// DHtotal=2200
	rtd_outl(0xb8028010, 0x00000003);	// Vsync width
	rtd_outl(0xb8028014, 0x00000464);	// DVtotal=1125
	rtd_outl(0xb8028018, 0x008c080c);	// DH_den_sta,DH_den_end
	rtd_outl(0xb802801C, 0x0016044E);	// DV_den_sta,DV_den_end
	rtd_outl(0xb8028028, 0x00000004);	// Double Buffer Control
	rtd_outl(0xb8028294, 0x00000000);	// dclk = dpll / 1 = 297MHz

	//set mtg
	rtd_outl(0xb8028100, 0x00000001);	// Main Display enable
	rtd_outl(0xb8028108, 0x0CD40000);	// Main Border Color
	rtd_outl(0xb802810C, 0x00000000);	// Main Background Color
	rtd_outl(0xb8028110, 0x00000780);	// Main DEN_H_str,Main DEN_H_end
	rtd_outl(0xb8028114, 0x00000438);	// Main DEN_V_str,Main DEN_V_end
	rtd_outl(0xb8028118, 0x00000780);	// Main Background_H_str,Main Background_H_end
	rtd_outl(0xb802811C, 0x00000438);	// Main Background_V_str,Main Background_V_end
	rtd_outl(0xb8028120, 0x00000780);	// Main Active_H_str,Main Active_H_end
	rtd_outl(0xb8028124, 0x00000438);	// Main Active_V_str,Main Active_V_end

	//D pattern gen
	rtd_outl(0xb8029000, 0x00EF0031);		// D-domain Pattern Gen Setting
	rtd_outl(0xb8029028, 0x07800438);		//Input Size (1920x1080)


	// EPI/LVDS pin share.
	// Select EPI mode
	rtd_outl(0xB802D000,0x00000001); // Select EPI mode.
	rtd_outl(0xb802D010,0x00000000); // Disable LVDS port

	rtd_outl(0xb8000890,0x00000000); //A-Port LVDS pin share
	rtd_outl(0xb8000894,0x00000000); //A-Port LVDS pin share
	rtd_outl(0xb8000898,0x00000000); //B-Port LVDS pin share
	rtd_outl(0xb80008A0,0x00000000); //C-Port LVDS pin share
	rtd_outl(0xb80008A4,0x00000000); //C-Port LVDS pin share
	rtd_outl(0xb80008A8,0x00000000); //D-Port LVDS pin share

	//------------------------------------------------------------------------------------------------------------
	//SFG, 1 Pixel Mode, DH_ST_END = 0x008C080C, DTG_HS_Width = 16, DTG_VS_Width = 4
	//------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D100,0x00101860); //8-bit Mode, Dout Enable, 2nd line shift 1 sub-pixel, Post R/B Swap
	rtd_outl(0xb802D104,0x0000FFFF); //Force to background enable
	rtd_outl(0xb802D108,0x54321000); //Port A~H mapping 6port. (*)
	rtd_outl(0xb802D10C,0x89abcdef); //Port I~P mapping
	rtd_outl(0xb802D130,0x00000000); //SEG 0/1/2/3, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D134,0x00000000); //SEG 4/5/6/7, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D138,0x00000000); //SEG 8/9/10/11, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D13C,0x00000000); //SEG 12/13/14/15, Front/End, Odd/Even Line, no dummy pixel
	rtd_outl(0xb802D140,0x00001055); //6-SEG, 6-Port, No H-Flip (*), bit12=1=Req_from_epi.
	rtd_outl(0xb802D144,0x00000140); //SEG 0/1 Start (*)
	rtd_outl(0xb802D148,0x028003C0); //SEG 2/3 Start (*)
	rtd_outl(0xb802D14C,0x05000640); //SEG 4/5 Start (*)
	rtd_outl(0xb802D150,0x00000000); //SEG 6/7 Start
	rtd_outl(0xb802D154,0x00000000); //SEG 8/9 Start
	rtd_outl(0xb802D158,0x00000000); //SEG 10/11 Start
	rtd_outl(0xb802D15C,0x00000000); //SEG 12/13 Start
	rtd_outl(0xb802D160,0x00000000); //SEG 14/15 Start
	rtd_outl(0xb802D164,0x40000000); //Disable ByPass Mode, bit30=1=auto_config_sfg_timing_gen
	rtd_outl(0xb802D168,0x000F0798); //HS_Width = 16 dclk = 16*Pixel_Mode*n DH_Width (multiple for 4, n is constant)
	                                 //hsync_delay = 1944 = data_length/Pixel_Mode +24
	rtd_outl(0xb802D16C,0x00030000); //VSYNC_ST = 0, V_SYNC = DV_Width
	rtd_outl(0xb802D170,0x008C0086); //sfg_dh_den_sta = DH_ST = 140
	                                 //req_start = DH_ST - 6 = 140 - 6 = 134
	rtd_outl(0xb802D174,0x3C000000); //final_line_length = 1920, hsync_threshold = 0

	//#include "epi_mac.tbl"
	// EPI MAC-layer configuration

	rtd_outl(0xB802D500,0x00000015); // CTR_Start=0x15,CTR_Start_dummy=0x0,P/N no swap.
	rtd_outl(0xB802D504,0x00000020); // SOE for FSM use, depends on PORCH num. (ex:2200-1920=280)
	                                 // soe_sta_num = Phase1_preamble_length
	                                 //     Value="set"+4
	                                 //     Set Phase1_len = Porch-Phase2_len =280/6-4=36 => Set 32.
	                                 // soe_width_num = Phase2_preamble_length
	                                 //     Value="set"+0
	                                 //     Set "0" = Phase2_len = 4+0=4  => Set 0
	rtd_outl(0xB802D508,0x00011506); // SOE for LGD use.
	                                 // V13:soe_sta_pkt=soe_end(8b)="Last data to falling"
	                                 //     RTK wr style => value="set"+0
	                                 //     LGD rd style => Value="set"+4, Timing min.=10 => v13 needs 10, So we set "6"
	                                 // V13:soe_width_pkt=soe_Start(10b)="First data to rising"
	                                 //     RTK wr style => value="set"+0
	                                 //     LGD rd style => vlaue="set"+3, Timing min.=3 => v13 needs 280, So we set "277"
	rtd_outl(0xB802D50C,0x00000090); // CTR2:Register value for CTR2.(LTD2,LBR=1, others:0)
	rtd_outl(0xB802D510,0xFFFFFFF1); // CTR2:Select CTR2(c0 ~c5 ) source. From Tcon or Register(all "1"). (c0 from tcon17)
	rtd_outl(0xB802D514,0xFFF9FFFF); // CTR2:Select CTR2(c6 ~c11) source. From Tcon or Register(all "1"). (c9 from tcon19)
	rtd_outl(0xB802D518,0xFFFFFFFF); // CTR2:Select CTR2(c12~c17) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D51C,0xFFFFFFFF); // CTR2:Select CTR2(c18~c23) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D520,0xFFFFFFFF); // CTR2:Select CTR2(c24~c29) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D524,0x00000000); // CTR3: reserved for future. bit30=0 to disable.
	rtd_outl(0xB802D528,0x0000002A); // Data_Start=0x2A,Data_Start_dummy=0x0.
	rtd_outl(0xB802D52C,0x08000000); // Bit31=0=No_data_in.(Bit30=1 to reset), Bit29=0=PRBS7_OFF, 8bit

	rtd_outl(0xB802D530,0xC0000000); // EPI mode setting, bit[1]=1=lock_source_from_hw.

	//#include "epi_phy.tbl"
	// EPI mode configuration
	// FHD 60hz input, 6lane, 8bit mode
	// Data_rate=148.5M*14/3=693Mbps

	//===== DCLK DIV =====
	rtd_outl(0xb8028294,0x00000000); // bit[1:0]=00(DCLK=DPLL_Clk/1),(00:/1, 01:/2, 10:/4)

	//===== PHY layer, Phy0 for port A,B =====
	rtd_outl(0xB8000C00,0xEECDFED8); // bit25=1=EPI_mode, bit[23:21]=110=0.9V.
	rtd_outl(0xB8000C04,0x119FE7E1); //
	rtd_outl(0xB8000C08,0x00380C80); // bit[21:20]=2'b11=EPI_LSB, bit[14:8]=M_code=12(Value=12+2=14).
	rtd_outl(0xB8000C0C,0x0FFF0FFF); // Select=1 for data, P2S not reset
	rtd_outl(0xB8000C10,0x00000000); // pre-emphasis=disable, p2s phase don't select.
	rtd_outl(0xB8000C14,0x00000FFF); // TXEPIENL=slew_control_bypass, 1:bypass(EPI), 0:not bypass
	rtd_outl(0xB8000C18,0x0FFF0FFF); // Differential mode=enable, Int.Z=ON
	rtd_outl(0xB8000C1C,0x00AAAAAA); // Z=10=100ohm (00:140ohm,01:120ohm,10:100ohm,11:80ohm)
	rtd_outl(0xB8000C20,0x00000000); // Tx SR selection 0:SR_on, 1:SR_off
	rtd_outl(0xB8000C24,0x00000000); // TTLI mode=not select
	rtd_outl(0xB8000C28,0x00000000); // TTLO mode=not select
	rtd_outl(0xB8000C2C,0x00000000); // Pre-emphasis swing selection=not select
	rtd_outl(0xB8000C30,0x00000000); // Pre-emphasis swing selection=not select
	rtd_outl(0xB8000C34,0x0000000F); // NMOS switch selection=not select (Sharp=on)
	rtd_outl(0xB8000C38,0xFFFFFFFF); // NMOS switch selection=not select (Sharp=on)
	rtd_outl(0xB8000C3C,0x0000000F); // PMOS switch selection=not select (Sharp=on)
	rtd_outl(0xB8000C40,0xFFFFFFFF); // PMOS switch selection=not select (Sharp=on)
	rtd_outl(0xB8000C44,0x0E739CE7); // Swing select=default=11100
	rtd_outl(0xB8000C48,0x39CE739C); // Swing select=default=11100

	//================================= Mux Setting ===================================
	rtd_outl(0xb800DA40,0x03000202); // HDMI Power Enable (PHY power supply)

	//#include "tcon_noSSCG.tbl"
	//Tcon Setting
	rtd_outl(0xb802D208, 0x00000000);	// Disable across frame and across line 3 Function
	rtd_outl(0xb802D464, 0x00000001);	// Enable Timing Controller Function

	// GST, TCON10 + TCON11, LVDS_C_DN, 14
	rtd_outl(0xb802D2D8, 0x08140824);	// TCON10 H_ST_END
	rtd_outl(0xb802D2DC, 0x04520454);	// TCON10 V_ST_END
	rtd_outl(0xb802D2E0, 0x00400080);	// TCON10 Ctrl, Normal Mode, noSSCG
	rtd_outl(0xb802D420, 0x00001680);	// TCON10 noSSCG ST_END
	rtd_outl(0xb802D2F0, 0x00940094);	// TCON11 H_ST_END
	rtd_outl(0xb802D2F4, 0x00100013);	// TCON11 V_ST_END
	rtd_outl(0xb802D2F8, 0x00420180);	// TCON11 Ctrl
	rtd_outl(0xb802D424, 0x000017C0);	// TCON11 noSSCG ST_END

	// MCLK, TCON9, LVDS_C_DP, 13
	rtd_outl(0xb802D2C0, 0x009400A4);	// TCON9 H_ST_END
	rtd_outl(0xb802D2C4, 0x00140452);	// TCON9 V_ST_END
	rtd_outl(0xb802D2C8, 0x00400080);	// TCON9 Ctrl, Normal Mode, noSSCG
	rtd_outl(0xb802D41C, 0x04E00640);	// TCON9 noSSCG ST_END

	// GCLK, TCON4 + TCON5 + TCON6 + TCON7, LVDS_C_EN, 12
	rtd_outl(0xb802D25C, 0x00940094);	// TCON4 H_ST_END
	rtd_outl(0xb802D260, 0x0011021F);	// TCON4 V_ST_END
	rtd_outl(0xb802D264, 0x00400380);	// TCON4 Ctrl, Across_Line_1
	rtd_outl(0xb802D268, 0x00020001);	// TCON4 Across_Line_3, RP = 2, HP = 1
	rtd_outl(0xb802D408, 0x098C10F8);	// TCON4 noSSCG ST_END
	rtd_outl(0xb802D270, 0x00940094);	// TCON5 H_ST_END
	rtd_outl(0xb802D274, 0x0010021F);	// TCON5 V_ST_END
	rtd_outl(0xb802D278, 0x00420380);	// TCON5 Ctrl, Across_Line_1, TCON5_noSSCG or TCON4_noSSCG
	rtd_outl(0xb802D27C, 0x00020001);	// TCON5 Across_Line_3, RP = 2, HP = 1
	rtd_outl(0xb802D40C, 0x098C10F8);	// TCON5 noSSCG ST_END
	rtd_outl(0xb802D284, 0x00940094);	// TCON6 H_ST_END
	rtd_outl(0xb802D288, 0x00100013);	// TCON6 V_ST_END
	rtd_outl(0xb802D28C, 0x00610180);	// TCON6 Ctrl, Across_Line_1 Mode, TCON inverse, TCON6_noSSCG and TCON5_noSSCG
	rtd_outl(0xb802D410, 0x000017C0);	// TCON6 noSSCG ST_END
	rtd_outl(0xb802D298, 0x08140824);	// TCON7 H_ST_END
	rtd_outl(0xb802D29C, 0x044E0454);	// TCON7 V_ST_END (V_END - 1)
	rtd_outl(0xb802D2A0, 0x00420080);	// TCON7 Ctrl, Normal Mode, TCON7_noSSCG or TCON6_noSSCG
	rtd_outl(0xb802D414, 0x00001680);	// TCON7 noSSCG ST_END

	// EO, TCON12 + TCON13, LVDS_C_CP, 15
	rtd_outl(0xb802D304, 0x08140814);	// TCON12 H_ST_END
	rtd_outl(0xb802D308, 0x04560456);	// TCON12 V_ST_END
	rtd_outl(0xb802D30C, 0x00000480);	// TCON12 Ctrl
	rtd_outl(0xb802D314, 0x0000007D);	// TCON12 Across Frame Period
	rtd_outl(0xb802D31C, 0x08740874);	// TCON13 H_ST_END
	rtd_outl(0xb802D320, 0x04560456);	// TCON13 V_ST_END
	rtd_outl(0xb802D324, 0x00000483);	// TCON13 Ctrl
	rtd_outl(0xb802D32C, 0x0000007D);	// TCON13 Across Frame Period

	// POL, TCON16 + TCON17, for EPI, 17
	rtd_outl(0xb802D358, 0x00020002);	// TCON16 H_ST_END
	rtd_outl(0xb802D35C, 0x00000000);	// TCON16 V_ST_END
	rtd_outl(0xb802D360, 0x00000480);	// TCON16 Ctrl
	rtd_outl(0xb802D368, 0x00000000);	// TCON16 Across Frame Period
	rtd_outl(0xb802D36C, 0x00020002);	// TCON17 H_ST_END
	rtd_outl(0xb802D370, 0x00000119);	// TCON17 V_ST_END
	rtd_outl(0xb802D374, 0x00000383);	// TCON17 Ctrl
	rtd_outl(0xb802D378, 0x00040003);	// TCON17 Across Line 3 HP/RP

	// GSP, TCON19, for EPI, LVDS_D_FN, 30
	rtd_outl(0xb802D394, 0x03C003C0);	// TCON19 H_ST_END
	rtd_outl(0xb802D398, 0x00150017);	// TCON19 V_ST_END
	rtd_outl(0xb802D39C, 0x00000180);	// TCON19 Ctrl

	// TEST, TCON15, for LVDS_C_CN, 16
	rtd_outl(0xb802D344, 0x00940814);
	rtd_outl(0xb802D348, 0x0016044E);
	rtd_outl(0xb802D34C, 0x00000180);

	rtd_outl(0xb802D208, 0x00000002);	// Enable across frame and across line 3 Function
	rtd_outl(0xb80004E4, 0x00000008);	// audio clock enable

#if 0 // mark test code
	// Test pin
	rtd_outl(0xb8000800, 0x60F0F0F0);   // bit[31:28]=0x6=EPI_lock_input to GPIO0
	rtd_outl(0xb80008C8, 0x00000000);   // Select EPI_lock from src_0(GPIO0)
	rtd_outl(0xb8000830, 0xE0E0E0E0);
	rtd_outl(0xb8000834, 0xE0E0E0E0);		// GPIO_53=DCLK
	rtd_outl(0xb8000838, 0xE0E0E0E0);
	rtd_outl(0xb800083C, 0xE0E0E0E0);		// GPIO[63:60]
	rtd_outl(0xb8000840, 0xE0E0E0E0);
	rtd_outl(0xb8000844, 0xE0E0E0E0);
	rtd_outl(0xb8000848, 0xE0E0E0E0);
	rtd_outl(0xb800084C, 0xE0E0E0E0);
	rtd_outl(0xb8000850, 0xE0E0E0E0);		// GPIO_83=EPI_DATA[0]
	rtd_outl(0xb8000854, 0xE0E0E0E0);
	rtd_outl(0xb8000910, 0x00000028);		// Test_Pin_Main = EPI out
#endif

	// must put here...??
	rtd_outl(0xb8022294, 0x0000001F);		// TTL out

	// Pin_mux setting

	// Tcon output
	rtd_outl(0xb80008A0, 0xFFF33333);	// LVDS C Port Pin Share to Tcon
	rtd_outl(0xb80008A4, 0x33000000);	// LVDS C Port Pin Share to Tcon
	rtd_outl(0xb80008A8, 0x33FF0000);	// LVDS D Port Pin Share to Tcon
	rtd_outl(0xb8000C68, 0x00000000);	// Disable differential mode
	rtd_outl(0xb8000C78, 0x00FFFFFF);	// TXPHY TTLI Enable

	// GPO setting
	rtd_outl(0xb801BC0C, 0x000000E0);	// GPIO_101=VCOMDYN=GPO=1, GPIO_102=WP=GPO=1, GPIO_103=REVERSE=GPO=1
	rtd_outl(0xb801BC24, 0x000000E0);	// GPIO_101=VCOMDYN=GPO=1, GPIO_102=WP=GPO=1, GPIO_103=REVERSE=GPO=1
}

#if 0 // cklai@mark unused code
void
panel_sys_set_wait_us(
    UINT32 us )	/* Interval in microseconds			*/
{
    UINT32 last;
    panel_wait_us_first = rtd_inl(0xb801b638);
    last  = panel_wait_us_first + 27*us;

    DEBUG_PRINT("set wait us=%d, current=%d\n", us, panel_wait_us_first);

    if (last >= panel_wait_us_first)
		panel_wait_is_wrap = 0;
    else
		panel_wait_is_wrap = 1;

}
#endif

void panel_init_1st(void)
{

	if (panel_init_1st_is_done)
		return;
	panel_init_1st_is_done = 1;

	printf("panel_init_1st\n");

	//printf("iCONFIG_BACKLIGHT_PWM_FREQ=%d\n", (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_FREQ);
	//printf("iCONFIG_BACKLIGHT_PWM_DUTY=%d\n", (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_DUTY);
	//printf("iPANEL_TO_LVDS_ON_ms=%d\n", (&default_panel_parameter)->iPANEL_TO_LVDS_ON_ms);
	//printf("iLVDS_TO_LIGHT_ON_ms=%d\n", (&default_panel_parameter)->iLVDS_TO_LIGHT_ON_ms);

	if(Get_PANEL_TYPE_IS_IWATT_LOCAL_DIMMING()){
		printf("\n $$$$$$$$ This is Local Dimming Panel !!! \n");
		ld_Init();
#if defined(CONFIG_BOARD_TV035_RTD2992_4DDR_1G_EMMC)   //for local diming setting

		// Set TCON12 is V-sync * 2
		//rtd_outl(0xb800080c,0x40404030);	// Pin share set tcon12
		rtd_outl(0xb802d304,0x00010001);	// HST = 1; HEND = 1
		rtd_outl(0xb802d308,0x00000002);	// VST = 0; VEND = 2;
		rtd_outl(0xb802d30c,0x00000380);	// access line mode3
		rtd_outl(0xb802d310,0x02320020);	// set high pulse width & period
		rtd_outl(0xb802d464,0x00000001);	// tcon global enable

		IO_Set(PIN_LOCAL_DIMMING_EN,1);		// power on local dimming enable
		mdelay(100);
#endif
	}



	IO_Set(PIN_LVDS_ON_OFF, 1);
#if (defined CONFIG_PANEL_CMI_V390HJ1_PEL_OPENCELL)
	IO_Set(PIN_PANEL_OE1_ON_OFF, 1);
	IO_Set(PIN_PANEL_OE2_ON_OFF, 1);
	IO_Set(PIN_PANEL_VFLK_ON_OFF, 1);
#endif
#if defined(CONFIG_BOARD_TV035_RTD2992_4DDR_1G_EMMC)//20130629 TV035 markchen add for power sequence
	IO_Set(PIN_GREEN_LED, 1);
	rtd_outl(0xb8061414, 0x0);//hongzhi add for (ir) auto power

	// PAD_NAME: A_FP 68
	rtd_maskl(0xB8000890, 0x0FFFFFFF, (RTD299X_BGA_PIN_AL21) << 28);
	// PAD_NAME: A_FN 69
	rtd_maskl(0xB8000890, 0xF0FFFFFF, (RTD299X_BGA_PIN_AK22) << 24);
	if (RTD299X_BGA_PIN_AK22 == 0xD) { rtd_maskl(0xb80008c8, ~((0x7)<<12), ((0x1&0x7)<<12)); }; // D: ld_spi0_p2_sck_src1,<I/O>
	if (RTD299X_BGA_PIN_AK22 == 0x4) { rtd_maskl(0xb80008c8, ~((0x7)<<8), ((0x1&0x7)<<8)); }; // 4: ld_spi1_p2_sck_src1,<I/O>
	// PAD_NAME: A_EP 70
	rtd_maskl(0xB8000890, 0xFF0FFFFF, (RTD299X_BGA_PIN_AL22) << 20);
	if (RTD299X_BGA_PIN_AL22 == 0xD) { rtd_maskl(0xb80008c4, ~((0x7)<<16), ((0x1&0x7)<<16)); }; // D: ld_spi0_p3_sdo_SRC1,<I/O>
	if (RTD299X_BGA_PIN_AL22 == 0x4) { rtd_maskl(0xb80008c4, ~((0x7)<<24), ((0x1&0x7)<<24)); }; // 4: ld_spi1_p3_sdo_SRC1,<I/O>
	// PAD_NAME: A_EN 71
	rtd_maskl(0xB8000890, 0xFFF0FFFF, (RTD299X_BGA_PIN_AM22) << 16);
	if (RTD299X_BGA_PIN_AM22 == 0xD) { rtd_maskl(0xb80008c4, ~((0x7)<<12), ((0x1&0x7)<<12)); }; // D: ld_spi0_p4_sdi_SRC1,<I>
	if (RTD299X_BGA_PIN_AM22 == 0x4) { rtd_maskl(0xb80008c4, ~((0x7)<<20), ((0x1&0x7)<<20)); }; // 4: ld_spi1_p4_sdi_SRC1,<I>
	// PAD_NAME: A_DP 72
	rtd_maskl(0xB8000890, 0xFFFF0FFF, (RTD299X_BGA_PIN_AK23) << 12);
	// PAD_NAME: A_DN 73
	rtd_maskl(0xB8000890, 0xFFFFF0FF, (RTD299X_BGA_PIN_AM23) << 8);
	// PAD_NAME: A_CP 74
	rtd_maskl(0xB8000890, 0xFFFFFF0F, (RTD299X_BGA_PIN_AL23) << 4);
	// PAD_NAME: A_CN 75
	rtd_maskl(0xB8000890, 0xFFFFFFF0, (RTD299X_BGA_PIN_AK24) << 0);
	// PAD_NAME: A_BP 76
	rtd_maskl(0xB8000894, 0x0FFFFFFF, (RTD299X_BGA_PIN_AL24) << 28);
	// PAD_NAME: A_BN 77
	rtd_maskl(0xB8000894, 0xF0FFFFFF, (RTD299X_BGA_PIN_AK25) << 24);
	// PAD_NAME: A_AP 78
	rtd_maskl(0xB8000894, 0xFF0FFFFF, (RTD299X_BGA_PIN_AL25) << 20);
	// PAD_NAME: A_AN 79
	rtd_maskl(0xB8000894, 0xFFF0FFFF, (RTD299X_BGA_PIN_AM25) << 16);
	// PAD_NAME: B_FP 80
	rtd_maskl(0xB8000898, 0x0FFFFFFF, (RTD299X_BGA_PIN_AK26) << 28);
	// PAD_NAME: B_FN 81
	rtd_maskl(0xB8000898, 0xF0FFFFFF, (RTD299X_BGA_PIN_AM26) << 24);
	// PAD_NAME: B_EP 82
	rtd_maskl(0xB8000898, 0xFF0FFFFF, (RTD299X_BGA_PIN_AL26) << 20);
	// PAD_NAME: B_EN 83
	rtd_maskl(0xB8000898, 0xFFF0FFFF, (RTD299X_BGA_PIN_AK27) << 16);
	// PAD_NAME: C_FP 84
	rtd_maskl(0xB80008A0, 0x0FFFFFFF, (RTD299X_BGA_PIN_AL30) << 28);
	// PAD_NAME: C_FN 85
	rtd_maskl(0xB80008A0, 0xF0FFFFFF, (RTD299X_BGA_PIN_AM31) << 24);
	if (RTD299X_BGA_PIN_AM31 == 0xD) { rtd_maskl(0xb80008c8, ~((0x7)<<12), ((0x2&0x7)<<12)); }; // D: ld_spi0_p2_sck_src2,<I/O>
	if (RTD299X_BGA_PIN_AM31 == 0x4) { rtd_maskl(0xb80008c8, ~((0x7)<<8), ((0x2&0x7)<<8)); }; // 4: ld_spi1_p2_sck_src2,<I/O>
	// PAD_NAME: C_EP 86
	rtd_maskl(0xB80008A0, 0xFF0FFFFF, (RTD299X_BGA_PIN_AL31) << 20);
	if (RTD299X_BGA_PIN_AL31 == 0xD) { rtd_maskl(0xb80008c4, ~((0x7)<<16), ((0x2&0x7)<<16)); }; // D: ld_spi0_p3_sdo_SRC2,<I/O>
	if (RTD299X_BGA_PIN_AL31 == 0x4) { rtd_maskl(0xb80008c4, ~((0x7)<<24), ((0x2&0x7)<<24)); }; // 4: ld_spi1_p3_sdo_SRC2,<I/O>
	// PAD_NAME: C_EN 87
	rtd_maskl(0xB80008A0, 0xFFF0FFFF, (RTD299X_BGA_PIN_AM32) << 16);
	if (RTD299X_BGA_PIN_AM32 == 0xD) { rtd_maskl(0xb80008c4, ~((0x7)<<12), ((0x2&0x7)<<12)); }; // D: ld_spi0_p4_sdi_SRC2,<I>
	if (RTD299X_BGA_PIN_AM32 == 0x4) { rtd_maskl(0xb80008c4, ~((0x7)<<20), ((0x2&0x7)<<20)); }; // 4: ld_spi1_p4_sdi_SRC2,<I>
	// PAD_NAME: C_DP 88
	rtd_maskl(0xB80008A0, 0xFFFF0FFF, (RTD299X_BGA_PIN_AK30) << 12);
	if (RTD299X_BGA_PIN_AK30 == 0x7) { rtd_maskl(0xb80008c8, ~((0x3)<<20), ((0x0&0x3)<<20)); }; // 7: VBY1_HTPD_src0,<I>
	// PAD_NAME: C_DN 89
	rtd_maskl(0xB80008A0, 0xFFFFF0FF, (RTD299X_BGA_PIN_AL32) << 8);
	if (RTD299X_BGA_PIN_AL32 == 0x7) { rtd_maskl(0xb80008c8, ~((0x3)<<16), ((0x0&0x3)<<16)); }; // 7: VBY1_LOCK_src0,<I>
	// PAD_NAME: C_CP 90
	rtd_maskl(0xB80008A0, 0xFFFFFF0F, (RTD299X_BGA_PIN_AK31) << 4);
	// PAD_NAME: C_CN 91
	rtd_maskl(0xB80008A0, 0xFFFFFFF0, (RTD299X_BGA_PIN_AK32) << 0);
	// PAD_NAME: C_BP 92
	rtd_maskl(0xB80008A4, 0x0FFFFFFF, (RTD299X_BGA_PIN_AJ31) << 28);
	// PAD_NAME: C_BN 93
	rtd_maskl(0xB80008A4, 0xF0FFFFFF, (RTD299X_BGA_PIN_AJ32) << 24);
	// PAD_NAME: C_AP 94
	rtd_maskl(0xB80008A4, 0xFF0FFFFF, (RTD299X_BGA_PIN_AJ30) << 20);
	// PAD_NAME: C_AN 95
	rtd_maskl(0xB80008A4, 0xFFF0FFFF, (RTD299X_BGA_PIN_AH32) << 16);
	// PAD_NAME: D_FP 96
	rtd_maskl(0xB80008A8, 0x0FFFFFFF, (RTD299X_BGA_PIN_AH31) << 28);
	// PAD_NAME: D_FN 97
	rtd_maskl(0xB80008A8, 0xF0FFFFFF, (RTD299X_BGA_PIN_AH30) << 24);
	// PAD_NAME: D_EP 98
	rtd_maskl(0xB80008A8, 0xFF0FFFFF, (RTD299X_BGA_PIN_AG31) << 20);
	if (RTD299X_BGA_PIN_AG31 == 0x7) { rtd_maskl(0xb80008c8, ~((0x3)<<20), ((0x1&0x3)<<20)); }; // 7: VBY1_HTPD_src1,<I>
	// PAD_NAME: D_EN 99
	rtd_maskl(0xB80008A8, 0xFFF0FFFF, (RTD299X_BGA_PIN_AG30) << 16);
	if (RTD299X_BGA_PIN_AG30 == 0x7) { rtd_maskl(0xb80008c8, ~((0x3)<<16), ((0x1&0x3)<<16)); }; // 7: VBY1_LOCK_src1,<I>
  //added by chenxiangping start

  //set DDR Ttable and Step in
  rtd_maskl(0xb8000518, 0xFFFFF000, 0x1C0);
  rtd_maskl(0xb8000518, 0xF000FFFF, 0x30D<<16);
  //set DDR Ttable and Step in
  rtd_maskl(0xb8000538, 0xFFFFF000, 0x1C0);
  rtd_maskl(0xb8000538, 0xF000FFFF, 0x30D<<16);

  //Set DDR  Enable
  rtd_maskl(0xb8000514, 0xFFFFFFF8, 0x5);
  rtd_maskl(0xb8000534, 0xFFFFFFF8, 0x5);

  //set LVDS  Percenage
  rtd_maskl(0xb8000640, 0xFFFFFF0F, 0x3<<4);
  rtd_maskl(0xb8000640, 0xFFFFFFFD, 0x1<<2);



  //added by chenxiangping end
#endif
//	printf("%d\n",__LINE__);
	mdelay(((&default_panel_parameter)->iPANEL_TO_LVDS_ON_ms));
//	printf("%d\n",__LINE__);

	// set Panel Display Timing Gen
	setPanelDataSetting(&default_panel_parameter);


//#if defined(VBY_ONE)
	if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){

		uzu_main_444_bypass_4k2k();
		rtd_maskl(0xb8060230, ~(0xf<<4), 0xf<<4);
		rtd_maskl(0xb8061100, ~(0x1<<4), 0x1<<4);
		rtd_maskl(0xb8061108, ~(0x1<<4), 0x1<<4);

	#ifndef	CONFIG_BOARD_TV030_RTD2995_4DDR_2G_EMMC  //do not set backlight GPIO at this marked by lichun zhao
		rtd_maskl(0xb8060230, ~(0xf<<20), 0xf<<20);
		rtd_maskl(0xb8061100, ~(0x1<<6), 0x1<<6);
		rtd_maskl(0xb8061108, ~(0x1<<6), 0x1<<0);
    #endif

#if 1
		// dclk issue , fix me later
		rtd_outl(0xb8000490, 0x01f0142a);	// 297M Hz
		rtd_outl(0xb8000494, 0x01520042);	// DPLL div=1 , DPLL power on
		rtd_outl(0xb8000640, 0x00000005);	// DPLL div=1 , DPLL power on
#endif

	//	vby1_4k2k_test_script();
	}
	else if(Get_PANEL_TYPE_IS_MILLET3_4K2K_SERIES()){
		printf("========= 4K2K Millet3 Series LVDS Panel ==========\n");
		lvds_2k1k_120_4ports_script();
		//frank@05232012 disable VBY1 power down
		rtd_clearbits(0xb802d6d8, _BIT31);
		rtd_clearbits(0xb802d6f8, _BIT31);
		rtd_clearbits(0xb802d6d8, (_BIT30|_BIT1|_BIT0));
		rtd_clearbits(0xb802d6f8, (_BIT30|_BIT1|_BIT0));
		rtd_clearbits(0xb802d610, _BIT31);
 	}else if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_EPI_TYPE){
		printf("========= EPI TYPE Panel ==========\n");
		EPI_FHD_60HZ_Script();
	}
	else{
 		//frank@05232012 disable LVDS TX PHY
#if defined(CONFIG_BOARD_TV013_RTD2992_EMMC)   //for local diming setting
		rtd_setbits(0xb8000c50, (_BIT31|_BIT30|_BIT29));
		//rtd_outl(0xb802D010, 0x000006F0);	//PN not Swap, LVDS not Mirror, LVDS Mapping Table1, LVDS Port Enable
		rtd_outl(0xb802D010, 0x000004F0);	//PN not Swap, LVDS not Mirror, LVDS Mapping Table1, LVDS Port Enable
#else
		rtd_clearbits(0xb8000c50, (_BIT31|_BIT30|_BIT29));
#endif
		//frank@05232012 disable VBY1 power down
		rtd_clearbits(0xb802d6d8, _BIT31);
		rtd_clearbits(0xb802d6f8, _BIT31);
		rtd_clearbits(0xb802d6d8, (_BIT30|_BIT1|_BIT0));
		rtd_clearbits(0xb802d6f8, (_BIT30|_BIT1|_BIT0));
		rtd_clearbits(0xb802d610, _BIT31);
	}

#if 1
  #ifndef OPEN_CELL_PANEL
	rtd_outl(0xb8000890, 0x00000000);   //A-Port LVDS pin share
	rtd_outl(0xb8000894, 0x00000000);   //A-Port LVDS pin share
  #else
	Panel_Tcon_Init();
  #endif

	if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_EPI_TYPE){
		rtd_outl(0xb80008A0, 0xFFF33333);	// LVDS C Port Pin Share to Tcon
		rtd_outl(0xb80008A4, 0x33000000);	// LVDS C Port Pin Share to Tcon
		rtd_outl(0xb80008A8, 0x33FF0000);	// LVDS D Port Pin Share to Tcon
	}else{
		rtd_outl(0xb8000898, 0x00000000);   //B-Port LVDS pin share
		rtd_outl(0xb80008A0, 0x00000000);	//C-Port LVDS pin share
		rtd_outl(0xb80008A4, 0x00000000);	//C-Port LVDS pin share
		rtd_outl(0xb80008A8, 0x00000000);	//D-Port LVDS pin share
	}

	#if defined(LVDS_PN_SWAP)
	rtd_maskl(0xb802d000, 0xfffffbff, 0x00000000);  //LVDS PN Swap disable bit10=0
	printf("Do LVDS PN Swap\n");
	#endif //#if defined(LVDS_PN_SWAP)
#endif

#if 0 // cklai mark. use PIN_LVDS_ON_OFF that depends on board
//set demo board panel/backlight enable
	rtd_maskl(0xB8060230, 0xff0fffff, 0x00f00000);
	rtd_maskl(0xB8060228, 0xff0fffff, 0x00f00000);
	rtd_maskl(0xb8061100, 0xffdfffbf, 0x00200040);
	rtd_maskl(0xb8061108, 0xffdfffbf, 0x00200000);
	printf("0xB8060230: 0x%08x\n", rtd_inl(0xB8060230));
	printf("0xB8060228: 0x%08x\n", rtd_inl(0xB8060228));
	printf("0xb8061100: 0x%08x\n", rtd_inl(0xb8061100));
	printf("0xb8061108: 0x%08x\n", rtd_inl(0xb8061108));
#endif
#ifdef	CONFIG_BOARD_TV030_RTD2995_4DDR_2G_EMMC  // set spreed on
	rtd_maskl(0xB8000514, ~ (_BIT2|_BIT0), ( _BIT2|_BIT0));
	rtd_maskl(0xB8000534,~ ( _BIT2|_BIT0),  (_BIT2|_BIT0));
#endif
rtd_outl(0xb802810c, 0x0);


#if 0 // ck mark debug msg
	//dump_register();
#endif




}

void panel_init_2nd(void)
{

	if (panel_init_2nd_is_done || (boot_power_on_mode == POWER_OFF))
		return;
	panel_init_2nd_is_done = 1;

	printf("panel_init_2nd\n");
	// set up back light pwm freq/duty
	IO_PWM_SetFreq(PIN_BL_ADJ,(&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_FREQ);	//pwm_init
	IO_PWM_SetDuty(PIN_BL_ADJ, (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_DUTY); //pwm_set
#if 0
	printf("panel_init_2nd,%d iLVDS_TO_LIGHT_ON_ms=%d \n",__LINE__, (&default_panel_parameter)->iLVDS_TO_LIGHT_ON_ms);
	printf("panel_init_2nd,%d iPANEL_TO_LVDS_ON_ms=%d \n",__LINE__, (&default_panel_parameter)->iPANEL_TO_LVDS_ON_ms);
	printf("panel_init_2nd,%d iLIGHT_TO_LDVS_OFF_ms=%d \n",__LINE__, (&default_panel_parameter)->iLIGHT_TO_LDVS_OFF_ms);
	printf("panel_init_2nd,%d iLVDS_TO_PANEL_OFF_ms=%d \n",__LINE__, (&default_panel_parameter)->iLVDS_TO_PANEL_OFF_ms);
#endif

#if 0 //defined(CONFIG_REALTEK_AMP_TAS5711)
	printf("%d\n",__LINE__);
	extern void AudioAmp_InitAudioOut2I2S_2nd(void);
	AudioAmp_InitAudioOut2I2S_2nd();
	(&default_panel_parameter)->iLVDS_TO_LIGHT_ON_ms -= 150;
#endif

//	printf("%d\n",__LINE__);
	mdelay((&default_panel_parameter)->iLVDS_TO_LIGHT_ON_ms);
//	printf("\n%d\n",__LINE__);
	IO_Set(PIN_BL_ON_OFF, 1);


	if(Get_PANEL_TYPE_IS_IWATT_LOCAL_DIMMING()){
	unsigned int  data0[5] = {0x00001280,0x000d5cd,0x00001b1b,0x000025b5,0x00004039}; // Write A0~A3 regiser value, 0x2500(A0) = (0xA0*4)+0x1000(Write mode)
	unsigned int  data1[22] = {	// Write 0x50~0x64 register value
							0x00001140,0x00000000,0x00000010,0x00000000,0x00000000,0x0000008f,
						    	0x00000677,0x00000677,0x0000047f,0x0000047f,0x00000287,0x00000287,
							0x0000008f,0x0000008f,0x00000677,0x00000677,0x0000047f,0x0000047f,
							0x00000287,0x00000287,0x0000008f,0x0000008f
						   };
	unsigned int  data2[18] = {	// Write 0x00~0x10 register value
							0x00001000,0x00000007,0x00000fff,0x00000fff,0x00000fff,0x00000fff,
						    	0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff,
							0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff
						   };
	unsigned int  data3[2] = {	0x00001280,0x000055cd  };// Write 0xA0 register value
	unsigned int  data4[2] = {	0x00001144,0x00000330  };// Write 0x51 register value
	unsigned int  data5[2] = {	0x00001284,0x00001717  };// Write 0xA1 register value
	unsigned int  data6[2] = {	0x00001148,0x000001ea  };// Write 0x52 register value
	unsigned int  data7[2] = {	0x00001148,0x000000ea  };// Write 0x52 register value
	unsigned int  data8[2] = {	0x00001000,0x00000007  };// Write 0x00 register value
	unsigned int  data9[17] = {	// Write 0x01~0x10 register value
							0x00001004,0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff,
							0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff,
							0x00000fff,0x00000fff,0x00000fff,0x00000fff,0x00000fff
							};

 	ld_Write(data0, 5 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data1, 22 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data2, 18 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data3, 2 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data4, 2 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data5, 2 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data6, 2 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data7, 2 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data8, 2 , LD_WRITE_MODE_NOT_FOLLOW_VSYNC);
	ld_Write(data9, 17 , LD_WRITE_MODE_FOLLOW_VSYNC);	// For Backlight Scan

       //printf("\n $$$$$$$$ Read 0xA0 = %x \n", ld_Read(0x280));// Read 0xA0 register value



	printf("\n $$$$$$$$ local diming setting complete ....... \n");
}





}

#if 0 // cklai@mark unused code
#define rtd_setbits(offset, Mask) rtd_outl(offset, (rtd_inl(offset) | Mask))
#define rtd_clearbits(offset, Mask) rtd_outl(offset, ((rtd_inl(offset) & ~(Mask))))
void scaler_wait_for_event(unsigned int addr, unsigned int event)
{
	unsigned int timeoutcnt = 0x032500;

	rtd_setbits(addr, event);
	rtd_clearbits(addr, event);


	do {
		if(rtd_inl(addr) & event) {
			return;
		}
	} while(timeoutcnt-- != 0);

	return;

}

void disable_force_bg(void)
{
	printf("disable_force_bg\n");
	display_timing_ctrl1_RBUS display_timing_ctrl1_reg;
	scaler_wait_for_event(PPOVERLAY_DTG_PENDING_STATUS_VADDR, _BIT0);//wait data anable end
	display_timing_ctrl1_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR);
	display_timing_ctrl1_reg.dout_force_bg = 0;
	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, display_timing_ctrl1_reg.regValue);
}
#endif

void panel_i2c_init(void)
{

	// PA168 init via I2C command
	if(panel_Tcon_PA168_Enable()){
		mdelay(500);  // wait TCON ready //500ms
		PA168_i2c_cmd(); // PA168 init via I2C command
	}

	return;
}

int panel_init(void)
{
//	printf("panel initialize....\n");
	panel_init_1st();
	// panel init via I2C
	panel_i2c_init();
//	printf("[DEBUG]%s:%d\n",__FUNCTION__,__LINE__);

#ifdef CONFIG_PANEL_APPLY_TCON_SETTING
	panel_apply_tcon_setting(PANEL_TCON_SETTING_FILE_NAME);
	panel_apply_tcon_setting(PANEL_ODC_SETTING_FILE_NAME);
#endif

#ifndef CONFIG_PANEL_INIT_2ND_AFTER_LOGO
	panel_init_2nd();
#endif

	return 0;
}

//USER: Vincent_Lee  DATE: 2012/4/28  TODO: Add TCON for open cell panel
#ifdef OPEN_CELL_PANEL
void Panel_Tcon_Init(void)
{
//#if (defined(CONFIG_PANEL_BENQ_22_3D_PR) || defined(CONFIG_PANEL_AUO_T420HW09_OPENCELL))
#ifdef CONFIG_PANEL_AUO_T420HW09_OPENCELL //Auo42

    IO_Set(PIN_PANEL_AVDD_17V6, 1);
	// mini-LVDS
	rtd_outl(0xb802D200, 0x00000071);	// 2-port/3-pair , 8-bit
	rtd_outl(0xb8000960, 0x23000030);
	rtd_outl(0xb8000964, 0x05060340);
	rtd_outl(0xb8000974, 0x00000051);
	rtd_outl(0xb802D000, 0x00000100);	// LVDS port disable
	rtd_outl(0xb802c718, 0x87800000);	// bypass SFG
	rtd_outl(0xb8028000, 0x13530C03);       // ---lhh---20120719
	rtd_outl(0xb8000954, 0x07402404);       // enable pre-emphasis , increase data swing


	//-----------------------------------------------------------

	// TCON Pin share

	rtd_outl(0xb8000890,0x003333F3);
	rtd_outl(0xb8000894,0x33000000);


	rtd_outl(0xb802D030,0x00000000);	// TCON global disable


	// YCLK; Pin96; TCON8; --> ok
	rtd_outl(0xb802D0D4,0x07D00830);	// HST = 2032; HEND = 2128;
	rtd_outl(0xb802D0D8,0x00000480);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D0DC,0x00000080);	// Normal Mode;

	// YDIOD/YDIO2/STV1; Pin97; TCON9; --> ok
	rtd_outl(0xb802D0E8,0x042E0311);	// HST = 1070; HEND = 785;
	rtd_outl(0xb802D0EC,0x00140016);	// VST = 20; VEND = 22;
	rtd_outl(0xb802D0F0,0x00000180);	// Across Line1 Mode;

	// YDIOU/YDIO1/STV; Pin98; TCON10; --> ok
	rtd_outl(0xb802D100,0x040502E8);	// HST = 1029; HEND = 744;
	rtd_outl(0xb802D104,0x00120014);	// VST = 18; VEND = 20;
	rtd_outl(0xb802D108,0x00000180);	// Across Line1 Mode;

	// YOE; Pin99; TCON11; --> ok
	rtd_outl(0xb802D118,0x01600600);	// HST = 352; HEND = 1536;
	rtd_outl(0xb802D11C,0x0013044C);	// VST = 19; VEND = 1020;
	rtd_outl(0xb802D120,0x00000080);	// Normal Mode;

	// RES; Pin100; TCON12; --> mini-LVDS data
	rtd_outl(0xb802D12C,0x008C080C);	// HST = 140; HEND = 2060;
	rtd_outl(0xb802D130,0x0012044A);	// VST = 18; VEND = 1098;
	rtd_outl(0xb802D134,0x00000080);	// Normal Mode;

	// STB2; Pin101; TCON13; --> ok
	rtd_outl(0xb802D144,0x08250897);	// HST = 2038; HEND = 2199;
	//rtd_outl(0xb802D148,0x00120011);	// VST = 18; VEND = 17;
	rtd_outl(0xb802D148,0x00000480);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D14C,0x00000080);	// Across Line2 Mode;

	// POL; Pin102; TCON14; --> ok
	rtd_outl(0xb802D158,0x07C007C0);	// HST = 1984; HEND = 1984;
	rtd_outl(0xb802D15C,0x00120480);	// VST = 18; VEND = 566;
	//rtd_outl(0xb802D15C,0x00000480);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D160,0x00013080);	// Across Line3 Mode;
	rtd_outl(0xb802D164,0x00020001);

	udelay(20 * 1000);

	// STB1; Pin103; TCON15; --> ok
	rtd_outl(0xb802D16C,0x06c80387);	// HST = 2038; HEND = 2199;
	//rtd_outl(b802D170,0x00120011);	// VST = 18; VEND = 17;
	//rtd_outl(0xb802D170,0x00000480);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D170,0x00000512);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D174,0x00000080);	// Normal Mode;

	// Reset Plus; TCON0; --> ok
	rtd_outl(0xb802D034,0x0088008A);	// HST = 130; HEND = 135;
	rtd_outl(0xb802D038,0x00000480);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D03c,0x00000080);	// Normal Mode;
	rtd_outl(0xb802D204,0x00000080);	// mini-LVDS Reset signal merge TCON0

	//--lhh-->>
	rtd_outl(0xb802c700, 0x00000049);
	rtd_outl(0xb802c718, 0x07800000);
	rtd_outl(0xb802c720, 0x0008078C);
	rtd_outl(0xb802c728, 0x08140000);

	rtd_outl(0xb8028004, 0x00002002);
	rtd_outl(0xb802d208, 0x000000F8);

	rtd_outl(0xb800095c, 0x00000307);
	rtd_outl(0xb8000960, 0x23000307);

	//<<--lhh--



	rtd_outl(0xb802D030,0x00000003);	// TCON enable

#elif (defined CONFIG_PANEL_CMI_V390HJ1_PEL_OPENCELL)  //cmi39

 if ((rtd_inl(0xb8060008) & 0x01) == 0) { // SPI boot



    IO_Set(PIN_PANEL_AVDD_17V6, 1);


	rtd_outl(0xb802d02c, 0xFFFFFFFF);

	// mini-LVDS
	rtd_outl(0xb802D200, 0x00000061);	// 2-port/3-pair , 8-bit
	rtd_outl(0xb8000960, 0x23000030);
	rtd_outl(0xb8000964, 0x05060340);
	rtd_outl(0xb8000974, 0x00000051);
	rtd_outl(0xb802D000, 0x00000100);	// LVDS port disable
	rtd_outl(0xb802c718, 0x07850000);	//---lhh---20120719
	//rtd_outl(0xb802c718, 0x87800000);	// bypass SFG
	//rtd_outl(0xb8028000, 0x13530404); // modify delay chain
	rtd_outl(0xb8028000, 0x13570C03); // ---lhh---20120719
	rtd_outl(0xb8000954, 0x07402404); // enable pre-emphasis , increase data swing

	//-----------------------------------------------------------

	// TCON Pin share



	rtd_outl(0xb802D030,0x00000000);	// TCON global disable
	rtd_outl(0xb802d030,0x00000003);	// TCON enable

	rtd_maskl(0xb8000890, 0xfffffff0, 0x00000003);	 //LVDS pin share


		//CKV; pin_101	;TCON_13
	rtd_outl(0xb802D144,0x046a0800);	// HST = 1130 ; HEND = 2048;
	rtd_outl(0xb802D148,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D14C,0x000000C0);	// Normal Mode + inverter;

	udelay(35 * 1000);

    rtd_maskl(0xb8000890, 0xffff0fff, 0x00003000);	 //LVDS pin share
	//TP1; pin_98	  ;TCON_10
	rtd_outl(0xb802D100,0x083a003a);	// HST = 2106 ; HEND = 58;
	rtd_outl(0xb802D104,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D108,0x00000080);	// Normal Mode;


	//OE1; pin_97	  ;TCON_9
	rtd_outl(0xb802D0E8,0x05b0080c);	// HST = 1456 ; HEND = 2060;
	rtd_outl(0xb802D0EC,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D0F0,0x00000080);	// Normal Mode;

	//OE2; pin_102	;TCON_14
	rtd_outl(0xb802D158,0x05b0080c);	// HST = 1456 ; HEND = 2060;
	rtd_outl(0xb802D15C,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D160,0x00000080);	// Normal Mode;

	// VFLK; Pin103; TCON15;
	rtd_outl(0xb802D16C,0x05F0035C);	// HST = 2038; HEND = 2199;
	rtd_outl(0xb802D170,0x00000600);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D174,0x00000280);	// Across Line2 Mode;

    udelay(15 * 1000);

	rtd_outl(0xb8000890,0x00333333);
	rtd_outl(0xb8000894,0x33000000);



	//STV; pin_99   ;TCON_11
	rtd_outl(0xb802D118,0x046a046a);	// HST = 1130 ; HEND = 1130;
	rtd_outl(0xb802D11C,0x00100012);	// VST = 16 ; VEND = 18;
	rtd_outl(0xb802D120,0x00000180);	// Across Line1 Mode;

	//POL; pin_100	;TCON_12
	rtd_outl(0xb802D12C,0x01000100);	// HST = 256 ; HEND = 256;
	rtd_outl(0xb802D130,0x04500450);	// VST = 1104; VEND = 1104;
	rtd_outl(0xb802D134,0x00000480);	// Across Frame Mode;
	rtd_outl(0xb802D138,0x00000000);	//
	rtd_outl(0xb802D13C,0x00000000);	//


	//udelay(20 * 1000);


	// Reset Plus; TCON0;
	//rtd_outl(b802D034,0088008A);	// HST = 130; HEND = 135;
	//rtd_outl(b802D038,00000480);	// VST = 0; VEND = 1152;
	//rtd_outl(b802D03c,00000080);	// Normal Mode;
	//rtd_outl(b802D204,00000080);	// mini-LVDS Reset signal merge TCON0


	// SFG
	rtd_outl(0xb802c700, 0x00000009);	// H-Flip disable, Panel interface output is 2-port
	//rtd_outl(0xb802c718, 0x07800000);	// line_length = 1920
	//rtd_outl(0xb802c718, 0x07830000);	// line_length = 1923
	rtd_outl(0xb802c720, 0x0008078C);	// SFG output hsync width = 9 ; SFG output hsync delay time = 1932 pixel
	//rtd_outl(0xb802c724, 0x00010000);	// SFG delayed VS for mini-LVDS reset pulse
	rtd_outl(0xb802c728, 0x08140000);	// SFG output 1st req position = 2068

	rtd_outl(0xb8028004, 0x00002002);
	rtd_outl(0xb802d208, 0x800000F8); // reset pules in total region ; reset pules width = F8;

	rtd_outl(0xb800095c, 0x00000307); // PLL clock pair phase selection
	rtd_outl(0xb8000960, 0x23000307); // PLL0 clock pair phase selection

	rtd_outl(0xb802d000, 0x00E20000); // odd line shift 3 sub-pixel ; even line shift 1 sub-pixel;
	rtd_outl(0xb802d200, 0x00000071); // mini LVDS R/L port swap




	// ========================================================
	// Panel is 1920x1080
	// D_Htotal = 2199 = 0x897, D_Vtotal = 1124 = 0x464
	// H_start = 140 = 0x8C, H_end = 2060 = 0x80C
	// V_start = 16 = 0x10, V_end = 1096 = 0x448
	// ========================================================#endif
   }

  else
  	 { // NAND boot

    IO_Set(PIN_PANEL_AVDD_17V6, 1);


	rtd_outl(0xb802d02c, 0xFFFFFFFF);

	// mini-LVDS
	rtd_outl(0xb802D200, 0x00000061);	// 2-port/3-pair , 8-bit
	rtd_outl(0xb8000960, 0x23000030);
	rtd_outl(0xb8000964, 0x05040342);
	rtd_outl(0xb8000974, 0x00000051);
	rtd_outl(0xb802D000, 0x00000100);	// LVDS port disable
	rtd_outl(0xb802c718, 0x07850000);	//---lhh---20120719
	//rtd_outl(0xb802c718, 0x87800000);	// bypass SFG
	//rtd_outl(0xb8028000, 0x13530404); // modify delay chain
	rtd_outl(0xb8028000, 0x13570C03); 		// ---lhh---20120719
	rtd_outl(0xb8000954, 0x07402404); // enable pre-emphasis , increase data swing

	//-----------------------------------------------------------

	// TCON Pin share



	rtd_outl(0xb802D030,0x00000000);	// TCON global disable
	rtd_outl(0xb802d030,0x00000003);	// TCON enable

	rtd_maskl(0xb8000890, 0xfffffff0, 0x00000003);	 //LVDS pin share


		//CKV; pin_101	;TCON_13
	rtd_outl(0xb802D144,0x046a0800);	// HST = 1130 ; HEND = 2048;
	rtd_outl(0xb802D148,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D14C,0x000000C0);	// Normal Mode + inverter;

	udelay(30 * 1000);

    rtd_maskl(0xb8000890, 0xffff0fff, 0x00003000);	 //LVDS pin share
	//TP1; pin_98	  ;TCON_10
	rtd_outl(0xb802D100,0x083a003a);	// HST = 2106 ; HEND = 58;
	rtd_outl(0xb802D104,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D108,0x00000080);	// Normal Mode;

    udelay(20 * 1000);

	rtd_outl(0xb8000890,0x00333333);
	rtd_outl(0xb8000894,0x33000000);



	//OE1; pin_97	  ;TCON_9
	rtd_outl(0xb802D0E8,0x05b0080c);	// HST = 1456 ; HEND = 2060;
	rtd_outl(0xb802D0EC,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D0F0,0x00000080);	// Normal Mode;



	//STV; pin_99   ;TCON_11
	rtd_outl(0xb802D118,0x046a046a);	// HST = 1130 ; HEND = 1130;
	rtd_outl(0xb802D11C,0x00100012);	// VST = 16 ; VEND = 18;
	rtd_outl(0xb802D120,0x00000180);	// Across Line1 Mode;

	//POL; pin_100	;TCON_12
	rtd_outl(0xb802D12C,0x01000100);	// HST = 256 ; HEND = 256;
	rtd_outl(0xb802D130,0x04500450);	// VST = 1104; VEND = 1104;
	rtd_outl(0xb802D134,0x00000480);	// Across Frame Mode;
	rtd_outl(0xb802D138,0x00000000);	//
	rtd_outl(0xb802D13C,0x00000000);	//


	//OE2; pin_102	;TCON_14
	rtd_outl(0xb802D158,0x05b0080c);	// HST = 1456 ; HEND = 2060;
	rtd_outl(0xb802D15C,0x00000600);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D160,0x00000080);	// Normal Mode;

	//udelay(20 * 1000);

	// VFLK; Pin103; TCON15;
	rtd_outl(0xb802D16C,0x05F0035C);	// HST = 2038; HEND = 2199;
	rtd_outl(0xb802D170,0x00000600);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D174,0x00000280);	// Across Line2 Mode;

	// Reset Plus; TCON0;
	//rtd_outl(b802D034,0088008A);	// HST = 130; HEND = 135;
	//rtd_outl(b802D038,00000480);	// VST = 0; VEND = 1152;
	//rtd_outl(b802D03c,00000080);	// Normal Mode;
	//rtd_outl(b802D204,00000080);	// mini-LVDS Reset signal merge TCON0


	// SFG
	rtd_outl(0xb802c700, 0x00000009);	// H-Flip disable, Panel interface output is 2-port
	//rtd_outl(0xb802c718, 0x07800000);	// line_length = 1920
	//rtd_outl(0xb802c718, 0x07830000);	// line_length = 1923
	rtd_outl(0xb802c720, 0x0008078C);	// SFG output hsync width = 9 ; SFG output hsync delay time = 1932 pixel
	//rtd_outl(0xb802c724, 0x00010000);	// SFG delayed VS for mini-LVDS reset pulse
	rtd_outl(0xb802c728, 0x08140000);	// SFG output 1st req position = 2068

	rtd_outl(0xb8028004, 0x00002002);
	rtd_outl(0xb802d208, 0x800000F8); // reset pules in total region ; reset pules width = F8;

	rtd_outl(0xb800095c, 0x00000307); // PLL clock pair phase selection
	rtd_outl(0xb8000960, 0x23000307); // PLL0 clock pair phase selection

	rtd_outl(0xb802d000, 0x00E20000); // odd line shift 3 sub-pixel ; even line shift 1 sub-pixel;
	rtd_outl(0xb802d200, 0x00000071); // mini LVDS R/L port swap




	// ========================================================
	// Panel is 1920x1080
	// D_Htotal = 2199 = 0x897, D_Vtotal = 1124 = 0x464
	// H_start = 140 = 0x8C, H_end = 2060 = 0x80C
	// V_start = 16 = 0x10, V_end = 1096 = 0x448
	// ========================================================#endif
   }
#else

	IO_Set(PIN_PANEL_AVDD_17V6, 1);


	rtd_outl(0xb802d02c, 0xFFFFFFFF);

	// mini-LVDS
	rtd_outl(0xb802D200, 0x00000061);	// 2-port/3-pair , 8-bit
	rtd_outl(0xb8000960, 0x23000030);
	rtd_outl(0xb8000964, 0x05020343);
	rtd_outl(0xb8000974, 0x00000051);
	rtd_outl(0xb802D000, 0x00000100);	// LVDS port disable
	rtd_outl(0xb802c718, 0x07800000);	// NOT bypass SFG
	//rtd_outl(0xb802c718, 0x87800000);	// bypass SFG
	//rtd_outl(0xb8028000, 0x13530404); // modify delay chain
	rtd_outl(0xb8028000, 0x13570404); // keep force background
	rtd_outl(0xb8000954, 0x07402404); // enable pre-emphasis , increase data swing

	//-----------------------------------------------------------

	// TCON Pin share

	rtd_outl(0xb8000890,0x00333333);
	rtd_outl(0xb8000894,0x33000000);

	rtd_outl(0xb802D030,0x00000000);	// TCON global disable

	//OE1; pin_97	  ;TCON_9
	rtd_outl(0xb802D0E8,0x05b0080c);	// HST = 1456 ; HEND = 2060;
	rtd_outl(0xb802D0EC,0x00000546);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D0F0,0x00000080);	// Normal Mode;

	//TP1; pin_98	  ;TCON_10
	rtd_outl(0xb802D100,0x083a003a);	// HST = 2106 ; HEND = 58;
	rtd_outl(0xb802D104,0x00000546);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D108,0x00000080);	// Normal Mode;

	//STV; pin_99   ;TCON_11
	rtd_outl(0xb802D118,0x046a046a);	// HST = 1130 ; HEND = 1130;
	rtd_outl(0xb802D11C,0x00100012);	// VST = 16 ; VEND = 18;
	rtd_outl(0xb802D120,0x00000180);	// Across Line1 Mode;

	//POL; pin_100	;TCON_12
	rtd_outl(0xb802D12C,0x01000100);	// HST = 256 ; HEND = 256;
	rtd_outl(0xb802D130,0x04500450);	// VST = 1104; VEND = 1104;
	rtd_outl(0xb802D134,0x00000480);	// Across Frame Mode;
	rtd_outl(0xb802D138,0x00000000);	//
	rtd_outl(0xb802D13C,0x00000000);	//

	//CKV; pin_101	;TCON_13
	rtd_outl(0xb802D144,0x046a0800);	// HST = 1130 ; HEND = 2048;
	rtd_outl(0xb802D148,0x00000546);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D14C,0x000000C0);	// Normal Mode + inverter;

	//OE2; pin_102	;TCON_14
	rtd_outl(0xb802D158,0x05b0080c);	// HST = 1456 ; HEND = 2060;
	rtd_outl(0xb802D15C,0x00000546);	// VST = 0 ; VEND = 1350;
	rtd_outl(0xb802D160,0x00000080);	// Normal Mode;

	udelay(20 * 1000);

	// VFLK; Pin103; TCON15;
	rtd_outl(0xb802D16C,0x05F00200);	// HST = 2038; HEND = 2199;
	rtd_outl(0xb802D170,0x00000480);	// VST = 0; VEND = 1152;
	rtd_outl(0xb802D174,0x00000280);	// Across Line2 Mode;

	// Reset Plus; TCON0;
	//rtd_outl(b802D034,0088008A);	// HST = 130; HEND = 135;
	//rtd_outl(b802D038,00000480);	// VST = 0; VEND = 1152;
	//rtd_outl(b802D03c,00000080);	// Normal Mode;
	//rtd_outl(b802D204,00000080);	// mini-LVDS Reset signal merge TCON0


	// SFG
	rtd_outl(0xb802c700, 0x00000009);	// H-Flip disable, Panel interface output is 2-port
	//rtd_outl(0xb802c718, 0x07800000);	// line_length = 1920
	//rtd_outl(0xb802c718, 0x07830000);	// line_length = 1923
	rtd_outl(0xb802c720, 0x0008078C);	// SFG output hsync width = 9 ; SFG output hsync delay time = 1932 pixel
	//rtd_outl(0xb802c724, 0x00010000);	// SFG delayed VS for mini-LVDS reset pulse
	rtd_outl(0xb802c728, 0x08140000);	// SFG output 1st req position = 2068

	rtd_outl(0xb8028004, 0x00002002);
	rtd_outl(0xb802d208, 0x800000F8); // reset pules in total region ; reset pules width = F8;

	rtd_outl(0xb800095c, 0x00000307); // PLL clock pair phase selection
	rtd_outl(0xb8000960, 0x23000307); // PLL0 clock pair phase selection

	rtd_outl(0xb802d000, 0x00E20000); // odd line shift 3 sub-pixel ; even line shift 1 sub-pixel;
	rtd_outl(0xb802d200, 0x00000071); // mini LVDS R/L port swap


	rtd_outl(0xb802d030,0x00000003);	// TCON enable

	// ========================================================
	// Panel is 1920x1080
	// D_Htotal = 2199 = 0x897, D_Vtotal = 1124 = 0x464
	// H_start = 140 = 0x8C, H_end = 2060 = 0x80C
	// V_start = 16 = 0x10, V_end = 1096 = 0x448
	// ========================================================#endif
#endif
}
#endif

#ifdef CONFIG_PANEL_APPLY_TCON_SETTING

typedef struct{
	char magic_no[4]; // "TXT", "BIN"
	int rsv1;
	int len; // instruction count
	int rsv3;
} tcon_setting_header_t;

typedef struct{
	char cmd[4]; // 'w', 'n'
} tcon_setting_entry_t;

typedef struct{
	tcon_setting_entry_t entry;
	uint reg_addr;
	uint value;
} tcon_setting_entry_write_t;

typedef struct{
	tcon_setting_entry_t entry;
	uint delay_us;
} tcon_setting_entry_delay_t;

void panel_apply_tcon_setting(char *filename)
{
	char *dst_addr;
	int dst_length;
	tcon_setting_header_t *header_p;
	tcon_setting_entry_t *entry_p;
	tcon_setting_entry_write_t *write_p;
	tcon_setting_entry_delay_t *delay_p;
	char *curr_p = NULL;
	uint i = 0;

	display_evaluate_time("panel_apply_tcon_setting-0");

	// read setting from factory
	if (factory_read(filename, &dst_addr, &dst_length)) {
		printf("------------can't find %s\n", filename);
	}
	else {
		printf("------------%s found\n", filename);

		curr_p = (char *)dst_addr;
		header_p = (tcon_setting_header_t *)dst_addr;

		// check setting format from header
		if (strncmp(header_p->magic_no, PANEL_TCON_SETTING_HEADER_MAGNO_BIN, 4) == 0)
		{
			printf("TCON setting type %s: parsing %d settings ...\n", header_p->magic_no, header_p->len);

			curr_p += sizeof(tcon_setting_header_t);

			// parse each entry and execute
			for (i = 0;i < header_p->len;i++)
			{
				entry_p = (tcon_setting_entry_t *)curr_p;

				if (entry_p->cmd[0] == 'w') // this entry is write cmd
				{
					write_p = (tcon_setting_entry_write_t *)curr_p;

					printf("%s 0x%08x 0x%08x\n", entry_p->cmd, write_p->reg_addr, write_p->value);

					rtd_outl(write_p->reg_addr, write_p->value);

					curr_p += sizeof(tcon_setting_entry_write_t);
				}
				else if (entry_p->cmd[0] == 'n') // this entry is delay cmd
				{
					delay_p = (tcon_setting_entry_delay_t *)curr_p;

					printf("%s 0x%08x\n", entry_p->cmd, delay_p->delay_us);

					udelay(delay_p->delay_us);

					curr_p += sizeof(tcon_setting_entry_delay_t);
				}
			}
		}
		else if (strncmp(header_p->magic_no, PANEL_TCON_SETTING_HEADER_MAGNO_TXT, 4) == 0)
		{
			printf("TCON setting type %s: still not support\n", header_p->magic_no);
		}
		else
		{
			printf("TCON setting type %s: unknown type\n", header_p->magic_no);
		}
	}

	display_evaluate_time("panel_apply_tcon_setting-1");
}
#endif

