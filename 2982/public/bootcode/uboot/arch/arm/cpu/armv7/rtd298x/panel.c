#include <common.h>
#if defined(CONFIG_RTD299X)
#include <asm/arch/panelConfigParameter.h>
#elif defined(CONFIG_RTD298X)
#include <asm/arch/panel_config_parameter.h>
#endif
#include <rbusPpOverlayReg.h>
#include <crt_sys_reg.h>
#include <rbusPinmuxReg.h>
#include <rbusPifReg.h>
#include <rbusSfgReg.h>
#include <rbusVby1Reg.h>
#include <platform_lib/board/pcb_mgr.h>
#include <platform_lib/board/pcb.h>
#include <asm/io.h>
#include <bootparam.h>
#include <asm/arch/factorylib.h>
#include <panel.h>
#include <asm/arch/rbus/rbusLD_InterfaceReg.h>
#include <asm/arch/ld_interface.h>
#include <rtk_g2c_lib.h>
#include <asm/arch/fw_info.h>
#include <panel_api.h>
#include <watchdog.h>
#include <system.h>

#ifdef CONFIG_PANEL_SHARP_60_MEMC
#include <tcon/frdlcdapi.h>
#include <rtk_i2c_lib.h>
#endif //#ifdef CONFIG_PANEL_SHARP_60_MEMC

extern uchar boot_ac_on;
extern int boot_power_on_mode;
extern BOOT_MODE boot_mode;

#define DISABLE_SOME_PRINTF
#ifdef DISABLE_SOME_PRINTF
	#define DEBUG_PRINT(fmt,args...)
#else
	#define DEBUG_PRINT(fmt,args...)	 printf(fmt,## args);
#endif


int rtk_dispi_bisr(void);

void panel_vby1_tx(void);
void panel_epi_tx(void);
void panel_lvds_tx(void);




#ifdef OPEN_CELL_PANEL
void Panel_Tcon_Init(void);
#endif
#ifdef CONFIG_PANEL_SHARP_60_MEMC
void panel_sharp_memc_init(unsigned char stage);
#endif //#ifdef CONFIG_PANEL_SHARP_60_MEMC

#ifdef CONFIG_PANEL_APPLY_TCON_SETTING
#define PANEL_TCON_SETTING_HEADER_MAGNO_BIN	"BIN"
#define PANEL_TCON_SETTING_HEADER_MAGNO_TXT	"TXT"
#define PANEL_TCON_SETTING_FILE_NAME	FACTORY_HEADER_FILE_NAME"TCON.bin"
#define PANEL_ODC_SETTING_FILE_NAME		FACTORY_HEADER_FILE_NAME"ODC.bin"

extern void panel_apply_tcon_setting(char *filename);
#endif

void panel_misc(void);

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

#if 0
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
#ifdef CONFIG_REALTEK_I2C
//	unsigned long long value=0;
	UINT8 msg[2];

	G2C_Init(0x3);

	msg[0] = PA168_I2C_CMD_LVDS_FMT;
	msg[1] = LVDS_FMT_10BIT_VESA; //
	G2C_Write_EX(3, PA168_I2C_SLAVE_ID, 0, 0, 2, msg);
#endif

	printf("[PA168] Send I2C command!\n");

	return;
}

static unsigned char m_TCON_I2C_MASTER = 4;

void Millet4_i2c_cmd(void)
{
	static unsigned char m_TCON_I2C_DEVICE_ADDR = 0x65;	//millet4 slave address

	UINT8 TCON_MILLET4_I2C_CMD_TABLE[2][1][9] =
	{
		{
			// 2k1k120
			{0x26, 0x38, 0x50, 0x6e, 0x00, 0x00, 0x10, 0x00, 0x01},
		},
		{
			// 4k2k30
			{0x26, 0x38, 0x50, 0x6e, 0x00, 0x00, 0x10, 0x00, 0x03},
		}
	};

	printf("Millet4_i2c_cmd\n");

	G2C_Init(m_TCON_I2C_MASTER);

	if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_2k1k){
		printf("mode 2k1k\n");
		G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 9, ((UINT8*) TCON_MILLET4_I2C_CMD_TABLE));
	}else if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_4k2k){
		printf("mode 4k2k\n");
		G2C_Write_EX(m_TCON_I2C_MASTER, m_TCON_I2C_DEVICE_ADDR, 0, 0, 9, ((UINT8*) TCON_MILLET4_I2C_CMD_TABLE+9));
	}


}


unsigned char panel_Tcon_PA168_Enable(void)
{

	if((default_panel_parameter.iCONFIG_PANEL_TYPE == 2) && (default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_PA168_AU_55))
		return 1;

	return 0;
}
#endif

unsigned char Get_PANEL_TYPE_IS_MILLET3_4K2K_SERIES(void)
{
	if((default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX >=  DYNAMIC_OUTPUT_PANEL_SERIES_BEGIN) &&
		   (default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX < DYNAMIC_OUTPUT_PANEL_SERIES_MAX))
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
	pll_disp1_RBUS pll_disp1_reg;
	pll_disp2_RBUS pll_disp2_reg;
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

	dclkss_reg.regValue = rtd_inl(CRT_SYS_DCLKSS_VADDR);
	offset = dclkss_reg.dclk_offset_11_0;
	dclkss_reg.dclk_offset_11_0 = 0;
	dclkss_reg.dclk_ss_en = 0;
	dclkss_reg.dclk_ss_load = 1;
	rtd_outl(CRT_SYS_DCLKSS_VADDR, dclkss_reg.regValue);

	rtd_maskl(CRT_PLL_DISP2_VADDR, ~(_BIT17) , _BIT17);

	mdelay(1);

	pll_disp2_reg.regValue =  rtd_inl(CRT_PLL_DISP2_VADDR);
	pll_disp1_reg.regValue = 0;
	pll_disp1_reg.dpll_m = M_Code - 2;
	pll_disp2_reg.dpll_o = div;
	pll_disp1_reg.dpll_n= N_Code - 2;
	pll_disp1_reg.dpll_ip= CPC;
	rtd_outl(CRT_PLL_DISP1_VADDR, pll_disp1_reg.regValue);
	rtd_outl(CRT_PLL_DISP2_VADDR, pll_disp2_reg.regValue);
	mdelay(1);

	dclkss_reg.dclk_offset_11_0 = offset;
	dclkss_reg.dclk_ss_en = 1;
	dclkss_reg.dclk_ss_load = 1;
	rtd_outl(CRT_SYS_DCLKSS_VADDR, dclkss_reg.regValue);

	pll_disp2_reg.regValue = rtd_inl(CRT_PLL_DISP2_VADDR);
	pll_disp2_reg.dpll_rstb = 1;
	pll_disp2_reg.dpll_fupdn = 1;
	pll_disp2_reg.dpll_stop = 1;
	pll_disp2_reg.dpll_vcorstb = 1;
	pll_disp2_reg.dpll_pow= 1;
	rtd_outl(CRT_PLL_DISP2_VADDR, pll_disp2_reg.regValue);

	//rtd_maskl(SYSTEM_SYS_DCLKSS_VADDR, 0xff, _BIT31 | _BIT2|_BIT0);
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

	reg.regValue = rtd_inl(CRT_SYS_DCLKSS_VADDR);
	reg.dclk_offset_11_0 = usDclkOffset;
	reg.dclk_ss_en = 1;
	reg.dclk_ss_load = 1;
	rtd_outl(CRT_SYS_DCLKSS_VADDR, reg.regValue);
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

printf("##### drvif_clock_set_dclk : %d ###########\n", ulFreq);
//#ifdef VBY_ONE
	//if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){

	if(ulFreq >= 200000000)
		ulFreq = ulFreq/2; //by2 via 0xb8028294[1:0]

	//}
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


void panel_sfg_config(struct _PANEL_CONFIG_PARAMETER *panel)
{
	  //---------- SFG ------------------------------------------------------------------
	sfg_zz_shift_dbg_ctrl_RBUS sfg_zz_shift_dbg_ctrl_reg;
	sfg_swap_ctrl0_RBUS sfg_swap_ctrl0_reg;
	sfg_swap_ctrl1_RBUS sfg_swap_ctrl1_reg;
//	sfg_swap_ctrl2_RBUS sfg_swap_ctrl2_reg;
	int i=0;

//	sfg_swap_ctrl2_reg.regValue = 0;

	sfg_zz_shift_dbg_ctrl_reg.regValue = rtd_inl(SFG_SFG_ZZ_SHIFT_DBG_CTRL_VADDR);
	sfg_zz_shift_dbg_ctrl_reg.dout_mode = panel->iCONFIG_DISPLAY_COLOR_BITS;
	sfg_zz_shift_dbg_ctrl_reg.dout_en  = 1;
	sfg_zz_shift_dbg_ctrl_reg.dvs_inv = (panel->iCONFIG_DISPLAY_VERTICAL_SYNC_NORMAL? 0:1);
	sfg_zz_shift_dbg_ctrl_reg.dhs_inv = (panel->iCONFIG_DISPLAY_VERTICAL_SYNC_NORMAL? 0:1);
	sfg_zz_shift_dbg_ctrl_reg.dden_inv = 0;
	sfg_zz_shift_dbg_ctrl_reg.daclk_inv = 1;
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
#if 0
	sfg_swap_ctrl0_reg.force_bg_dif_iport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_jport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_kport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_lport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_mport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_nport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_oport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_pport = 1;
#endif
	rtd_outl(SFG_SFG_SWAP_CTRL0_VADDR, sfg_swap_ctrl0_reg.regValue);
	sfg_swap_ctrl1_reg.regValue = rtd_inl(SFG_SFG_SWAP_CTRL1_VADDR);

	if(panel->iCONFIG_DISPLAY_PORT_CONFIG1){
		sfg_swap_ctrl1_reg.regValue = panel->iCONFIG_DISPLAY_PORT_CONFIG1;
//		sfg_swap_ctrl2_reg.regValue = panel->iCONFIG_DISPLAY_PORT_CONFIG2;
	}else{
		sfg_swap_ctrl1_reg.output_porta = panel->iCONFIG_DISPLAY_PORTAB_SWAP?1:0;
		sfg_swap_ctrl1_reg.output_portb = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;
	}
	rtd_outl(SFG_SFG_SWAP_CTRL1_VADDR, sfg_swap_ctrl1_reg.regValue);


	sfg_ctrl_0_RBUS    sfg_ctrl_0_reg;
	sfg_ctrl_9_RBUS    sfg_ctrl_9_reg;
	sfg_ctrl_8_RBUS    sfg_ctrl_8_reg;
	sfg_ctrl_7_RBUS    sfg_ctrl_7_reg;
	sfg_ctrl_6_RBUS    sfg_ctrl_6_reg;
	sfg_ctrl_5_RBUS	   sfg_ctrl_5_reg;
	sfg_ctrl_1_RBUS    sfg_ctrl_1_reg;
	sfg_ctrl_a_RBUS    sfg_ctrl_a_reg;	
	sfg_ctrl_b_RBUS	   sfg_ctrl_b_reg;
	sfg_ctrl_c_RBUS    sfg_ctrl_c_reg;

	unsigned int m_seg_width = 0;

	sfg_ctrl_0_reg.regValue = rtd_inl(SFG_SFG_CTRL_0_VADDR);

	//if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
	if(panel->iCONFIG_SFG_SEG_NUM != 0){

		m_seg_width = (panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS)/(panel->iCONFIG_SFG_SEG_NUM);

		if(panel->iCONFIG_SFG_SEG_NUM == 1){
			sfg_ctrl_1_reg.regValue = 0;
		}
		else{
			sfg_ctrl_1_reg.seg0_start = 0;
			sfg_ctrl_1_reg.seg1_start = m_seg_width;
		}
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

		if(panel->iCONFIG_SFG_PORT_NUM != 0)
			sfg_ctrl_0_reg.port_num = panel->iCONFIG_SFG_PORT_NUM-1;
		else{
			if(panel->iCONFIG_DISPLAY_PORT == 2){	// port 4
				sfg_ctrl_0_reg.port_num = 3;
			}else{ //port 1,2
				sfg_ctrl_0_reg.port_num = panel->iCONFIG_DISPLAY_PORT;
			}			
		}

	}
	else{	//traditional lvds panel setting
		if(panel->iCONFIG_DISPLAY_PORT == 2){	// port 4
			sfg_ctrl_0_reg.port_num = 3;
		}else{ //port 1,2
			sfg_ctrl_0_reg.port_num = panel->iCONFIG_DISPLAY_PORT;
		}
		sfg_ctrl_0_reg.seg_num = 0;
		rtd_outl(SFG_SFG_CTRL_1_VADDR, 0);
		rtd_outl(SFG_SFG_CTRL_2_VADDR, 0);
		rtd_outl(SFG_SFG_CTRL_3_VADDR, 0);
		rtd_outl(SFG_SFG_CTRL_4_VADDR, 0);
	}

	rtd_outl(SFG_SFG_CTRL_0_VADDR, sfg_ctrl_0_reg.regValue);
		
	sfg_ctrl_6_reg.regValue = 0;
	sfg_ctrl_6_reg.tg_auto_cfg = 1;
	rtd_outl(SFG_SFG_CTRL_6_VADDR, sfg_ctrl_6_reg.regValue);//Disable ByPass Mode

	sfg_ctrl_7_reg.regValue = rtd_inl(SFG_SFG_CTRL_7_VADDR);	
	sfg_ctrl_7_reg.hsync_width = panel->iCONFIG_DISP_HSYNC_WIDTH;//HS_Width = 16 dclk = 16*Pixel_Mode*n DH_Width (ゲ4计, nタ俱计)
	sfg_ctrl_7_reg.hsync_delay = panel->iCONFIG_DISP_HORIZONTAL_TOTAL -13;
	rtd_outl(SFG_SFG_CTRL_7_VADDR, sfg_ctrl_7_reg.regValue);

	
	sfg_ctrl_8_reg.regValue = rtd_inl(SFG_SFG_CTRL_8_VADDR);
	sfg_ctrl_8_reg.vsync_start = 0;
	sfg_ctrl_8_reg.vsync_end = panel->iCONFIG_DISP_VSYNC_LENGTH;
	rtd_outl(SFG_SFG_CTRL_8_VADDR, sfg_ctrl_8_reg.regValue);

	sfg_ctrl_9_reg.regValue = rtd_inl(SFG_SFG_CTRL_9_VADDR);
	sfg_ctrl_9_reg.sfg_dh_den_sta = panel->iCONFIG_DISP_DEN_STA_HPOS;
	sfg_ctrl_9_reg.req_start = panel->iCONFIG_DISP_DEN_STA_HPOS-6;
	rtd_outl(SFG_SFG_CTRL_9_VADDR, sfg_ctrl_9_reg.regValue);

	sfg_ctrl_5_reg.regValue = rtd_inl(SFG_SFG_CTRL_5_VADDR);
	sfg_ctrl_5_reg.hs_distance = 0;
	sfg_ctrl_5_reg.seg0_flip= 0;
	rtd_outl(SFG_SFG_CTRL_5_VADDR, sfg_ctrl_5_reg.regValue);

	sfg_ctrl_a_reg.regValue = rtd_inl(SFG_SFG_CTRL_A_VADDR);
	sfg_ctrl_a_reg.final_line_length = (panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS);
	sfg_ctrl_a_reg.hsync_threshold = 0;
	rtd_outl(SFG_SFG_CTRL_A_VADDR, sfg_ctrl_a_reg.regValue);

	sfg_ctrl_b_reg.regValue = 0;
	rtd_outl(SFG_SFG_CTRL_B_VADDR, sfg_ctrl_b_reg.regValue); 

	if(panel->iCONFIG_PANEL_TYPE == P_EPI_TYPE){
		sfg_ctrl_c_reg.hs_den_io_dist = sfg_ctrl_9_reg.req_start + 6;
		sfg_ctrl_c_reg.hs_io_dist = sfg_ctrl_7_reg.hsync_delay + 6;
	}else{
		sfg_ctrl_c_reg.regValue = 0;
	}
	rtd_outl(SFG_SFG_CTRL_C_VADDR, sfg_ctrl_c_reg.regValue);

	if(panel->iCONFIG_PANEL_TYPE == P_EPI_TYPE){
		rtd_outl(SFG_ZZ_CTRL_VADDR, 0x881144A0);		
		rtd_outl(SFG_SFG_DUMMY_VADDR, 0x00009999);
	}
	
	rtd_outl(SFG_SFG_MID_DUMMY_0_VADDR, 0);
	rtd_outl(SFG_SFG_MID_DUMMY_1_VADDR, 0);
	rtd_outl(SFG_SFG_MID_DUMMY_2_VADDR, 0);
	rtd_outl(SFG_SFG_MID_DUMMY_3_VADDR, 0);
	rtd_outl(SFG_SFG_DATA_AFTER_DEN_VADDR, 0);

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
	//lvds_ctrl3_RBUS  lvds_ctrl3;
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
	//-------- PLL DISP -------------------------------------------------
	printf("CRT reg1=%x,reg2=%x\n",rtd_inl(0xb8000008),rtd_inl(0xb8000014));
	//rtd_maskl(0xb8000c78, ~_BIT7, 0);
	//drvif_clock_set_dclk(panel->iCONFIG_DISPLAY_CLOCK_TYPICAL);  // defualt fps: 50Hz

	//disable double buffer register
	double_buffer_ctrl_reg.regValue = rtd_inl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR);
	double_buffer_ctrl_reg.dreg_dbuf_en = 0;
	rtd_outl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR, double_buffer_ctrl_reg.regValue);
	//DTG setting
	display_timing_ctrl1_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR);
	display_timing_ctrl1_reg.disp_frc_on_fsync = 0;
	display_timing_ctrl1_reg.disp_line_4x = panel->iFIX_LAST_LINE_4X_ENABLE;
	display_timing_ctrl1_reg.disp_fsync_en = 0;

	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K)
		display_timing_ctrl1_reg.disp_en = 0;	// enable dtg out wait for vby one phy and sfg ready for sync timing
	else
		display_timing_ctrl1_reg.disp_en = 1;

	display_timing_ctrl1_reg.wde_to_free_run = 0;
	display_timing_ctrl1_reg.dout_force_bg = 1;
	display_timing_ctrl1_reg.dhs_first_mask = 0;
	display_timing_ctrl1_reg.auto_switch_fll_to_fs = 0;
	display_timing_ctrl1_reg.disp_fix_last_line = 0;

	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, display_timing_ctrl1_reg.regValue);
	display_timing_ctrl2_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR);
	if((panel->iCONFIG_DISP_ACT_END_HPOS - panel->iCONFIG_DISP_ACT_STA_HPOS) >= 3840)
		display_timing_ctrl2_reg.shpnr_line_mode = 2;
	else
		display_timing_ctrl2_reg.shpnr_line_mode = 0;
		
//	display_timing_ctrl2_reg.sr_mode = panel->iCONFIG_SR_MODE; //SR bypass
//	display_timing_ctrl2_reg.sr_pixel_mode = panel->iCONFIG_SR_PIXEL_MODE; // 4pixel mode
//	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR, display_timing_ctrl2_reg.regValue);
//	display_timing_ctrl2_reg.output_porta = panel->iCONFIG_DISPLAY_PORTAB_SWAP?1:0;
//	display_timing_ctrl2_reg.output_portb = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;
//	display_timing_ctrl2_reg.output_portc = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;
//       display_timing_ctrl2_reg.dclk_mode_switch = panel->iCONFIG_DISPLAY_PORT;
	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR, display_timing_ctrl2_reg.regValue);


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

#if 1//defined(CONFIG_BOARD_298X_TV001_QFP176_V3_NAND)||defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV013_QFP176_EMMC) || defined (CONFIG_BOARD_298X_TV010_QFP176_V3_EMMC)//add by markchen for backlight PWM control 20140423
	display_background_color_reg.d_bg_b = 0;
#else
	display_background_color_reg.d_bg_b = 0xFF;//frank@0114 let DTG BG blue color to check panel setting
#endif
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
#if 0
      //---------- SFG ------------------------------------------------------------------
	sfg_zz_shift_dbg_ctrl_RBUS sfg_zz_shift_dbg_ctrl_reg;
	sfg_swap_ctrl0_RBUS sfg_swap_ctrl0_reg;
	sfg_swap_ctrl1_RBUS sfg_swap_ctrl1_reg;
//	sfg_swap_ctrl2_RBUS sfg_swap_ctrl2_reg;
	int i=0;

//	sfg_swap_ctrl2_reg.regValue = 0;

	sfg_zz_shift_dbg_ctrl_reg.regValue = rtd_inl(SFG_SFG_ZZ_SHIFT_DBG_CTRL_VADDR);
	sfg_zz_shift_dbg_ctrl_reg.dout_mode = panel->iCONFIG_DISPLAY_COLOR_BITS;
	sfg_zz_shift_dbg_ctrl_reg.dout_en  = 1;
	sfg_zz_shift_dbg_ctrl_reg.dvs_inv = panel->iCONFIG_DISPLAY_VERTICAL_SYNC_NORMAL;
	sfg_zz_shift_dbg_ctrl_reg.dhs_inv = panel->iCONFIG_DISPLAY_HORIZONTAL_SYNC_NORMAL;
	sfg_zz_shift_dbg_ctrl_reg.dden_inv = 0;
	sfg_zz_shift_dbg_ctrl_reg.daclk_inv = 1;
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
#if 0
	sfg_swap_ctrl0_reg.force_bg_dif_iport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_jport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_kport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_lport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_mport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_nport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_oport = 1;
	sfg_swap_ctrl0_reg.force_bg_dif_pport = 1;
#endif
	rtd_outl(SFG_SFG_SWAP_CTRL0_VADDR, sfg_swap_ctrl0_reg.regValue);
	sfg_swap_ctrl1_reg.regValue = rtd_inl(SFG_SFG_SWAP_CTRL1_VADDR);

	if(panel->iCONFIG_DISPLAY_PORT_CONFIG1){
		sfg_swap_ctrl1_reg.regValue = panel->iCONFIG_DISPLAY_PORT_CONFIG1;
//		sfg_swap_ctrl2_reg.regValue = panel->iCONFIG_DISPLAY_PORT_CONFIG2;
	}else{
		sfg_swap_ctrl1_reg.output_porta = panel->iCONFIG_DISPLAY_PORTAB_SWAP?1:0;
		sfg_swap_ctrl1_reg.output_portb = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;
	}
	rtd_outl(SFG_SFG_SWAP_CTRL1_VADDR, sfg_swap_ctrl1_reg.regValue);
//	rtd_outl(SFG_SFG_SWAP_CTRL2_VADDR, sfg_swap_ctrl2_reg.regValue);

	//sfg_swap_ctrl1_reg.output_portc = panel->iCONFIG_DISPLAY_PORTAB_SWAP?0:1;

//	rtd_outl(SFG_SFG_DUMMY_CTRL_0_VADDR, 0x00000000);	//SEG 0/1/2/3, Front/End, Odd/Even Line, no dummy pixel
//	rtd_outl(SFG_SFG_DUMMY_CTRL_1_VADDR, 0x00000000);	//SEG 4/5/6/7, Front/End, Odd/Even Line, no dummy pixel
//	rtd_outl(SFG_SFG_DUMMY_CTRL_2_VADDR, 0x00000000);	//SEG 8/9/10/11, Front/End, Odd/Even Line, no dummy pixel
//	rtd_outl(SFG_SFG_DUMMY_CTRL_3_VADDR, 0x00000000);	//SEG 12/13/14/15, Front/End, Odd/Even Line, no dummy pixel

	sfg_ctrl_0_RBUS    sfg_ctrl_0_reg;
	sfg_ctrl_a_RBUS	sfg_ctrl_a_reg;
	sfg_ctrl_9_RBUS    sfg_ctrl_9_reg;
	sfg_ctrl_8_RBUS    sfg_ctrl_8_reg;
	sfg_ctrl_7_RBUS    sfg_ctrl_7_reg;
	sfg_ctrl_6_RBUS    sfg_ctrl_6_reg;
	sfg_ctrl_0_reg.regValue = rtd_inl(SFG_SFG_CTRL_0_VADDR);

	sfg_ctrl_1_RBUS    sfg_ctrl_1_reg;
//	sfg_ctrl_2_RBUS    sfg_ctrl_2_reg;
//	sfg_ctrl_3_RBUS    sfg_ctrl_3_reg;
//	sfg_ctrl_4_RBUS    sfg_ctrl_4_reg;
//	sfg_seg_start_0_RBUS    sfg_seg_start_0_reg;
//	sfg_seg_start_1_RBUS    sfg_seg_start_1_reg;
//	sfg_seg_start_2_RBUS    sfg_seg_start_2_reg;
//	sfg_seg_start_3_RBUS    sfg_seg_start_3_reg;
	unsigned int m_seg_width = 0;

	//if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
	if(panel->iCONFIG_SFG_SEG_NUM != 0){

		m_seg_width = (panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS)/(panel->iCONFIG_SFG_SEG_NUM);

		if(panel->iCONFIG_SFG_SEG_NUM == 1){
			sfg_ctrl_1_reg.regValue = 0;
		}
		else{
			sfg_ctrl_1_reg.seg0_start = 0;
			sfg_ctrl_1_reg.seg1_start = m_seg_width;
		}
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

		if(panel->iCONFIG_SFG_PORT_NUM != 0)
			sfg_ctrl_0_reg.port_num = panel->iCONFIG_SFG_PORT_NUM-1;
		else{
			if(panel->iCONFIG_DISPLAY_PORT == 2){	// port 4
				sfg_ctrl_0_reg.port_num = 3;
			}else{ //port 1,2
				sfg_ctrl_0_reg.port_num = panel->iCONFIG_DISPLAY_PORT;
			}			
		}

	}
	else{
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
//		rtd_outl(SFG_SFG_SEG_START_0_VADDR, 0);
//		rtd_outl(SFG_SFG_SEG_START_1_VADDR, 0);
//		rtd_outl(SFG_SFG_SEG_START_2_VADDR, 0);
//		rtd_outl(SFG_SFG_SEG_START_3_VADDR, 0);
	}

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

	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		UINT8 pixelmode = 1; 
/*		// Sirius only support 1 pixel mode
		if(panel->iCONFIG_SR_PIXEL_MODE == 0)
			pixelmode = 1;
		else if(panel->iCONFIG_SR_PIXEL_MODE == 1)
			pixelmode = 2;
		else if(panel->iCONFIG_SR_PIXEL_MODE == 2)
			pixelmode = 4;
*/
		sfg_ctrl_7_reg.hsync_delay = ((panel->iCONFIG_DISP_ACT_END_HPOS-panel->iCONFIG_DISP_ACT_STA_HPOS)/pixelmode)+24; //pixel mode=>0:1 pixel, 1:2 pixel, 2:4 pixel
		//hsync_delay = 984 = data_length/Pixel_Mode +24
		sfg_ctrl_9_reg.sfg_dh_den_sta = (panel->iCONFIG_DISP_DEN_STA_HPOS/pixelmode);
		sfg_ctrl_9_reg.req_start = (panel->iCONFIG_DISP_DEN_STA_HPOS/pixelmode)-6;
		sfg_ctrl_6_reg.tg_auto_cfg = 1;
	}
	else{
		sfg_ctrl_7_reg.hsync_delay = panel->iCONFIG_DISP_HORIZONTAL_TOTAL -13;
		sfg_ctrl_9_reg.sfg_dh_den_sta = panel->iCONFIG_DISP_DEN_STA_HPOS;
		sfg_ctrl_9_reg.req_start = panel->iCONFIG_DISP_DEN_STA_HPOS-6;
		sfg_ctrl_6_reg.tg_auto_cfg = 1;
		sfg_ctrl_6_reg.regValue= 0;
	}

	rtd_outl(SFG_SFG_CTRL_A_VADDR, sfg_ctrl_a_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_9_VADDR, sfg_ctrl_9_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_8_VADDR, sfg_ctrl_8_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_7_VADDR, sfg_ctrl_7_reg.regValue);
	rtd_outl(SFG_SFG_CTRL_6_VADDR, sfg_ctrl_6_reg.regValue);//Disable ByPass Mode
#else
	panel_sfg_config(panel);
#endif



	drvif_clock_set_dclk(panel->iCONFIG_DISPLAY_CLOCK_TYPICAL);
	if(panel->iCONFIG_DISPLAY_CLOCK_TYPICAL > 200*1000000){
		dclk_sel_reg.dclk_sel = 0; //DCLK = DPLL_Clk
	}else{
		dclk_sel_reg.dclk_sel = 1; //DCLK = DPLL_Clk / 2
	}

	printf("dclk_sel = %x\n", dclk_sel_reg.dclk_sel);
	rtd_outl(PPOVERLAY_DCLK_SEL_VADDR, dclk_sel_reg.regValue);
	DEBUG_PRINT("panel_init  panel->iCONFIG_DISPLAY_PORT = %x\n",panel->iCONFIG_DISPLAY_PORT);

#if 0

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

		if(panel->iCONFIG_PANEL_TYPE != P_VBY1_4K2K){
			rtd_outl(PIF_LVDS_CTRL0_VADDR, 0);
			lvds_ctrl3.regValue = 0;
		       lvds_ctrl3.lvds_pn_swap = 0;
			lvds_ctrl3.lvds_map = panel->iCONFIG_DISPLAY_BITMAPPING_TABLE?1:0;
			lvds_ctrl3.lvds_aport_en = 1;
			lvds_ctrl3.lvds_bport_en = 1;
//			lvds_ctrl3.lvds_cport_en = 1;
//			lvds_ctrl3.lvds_dport_en = 1;
			rtd_outl(PIF_LVDS_CTRL3_VADDR, lvds_ctrl3.regValue);
		}
	}
	else
	{
		rtd_outl(PIF_LVDS_CTRL0_VADDR, 0);
		lvds_ctrl3.regValue = 0;
	       lvds_ctrl3.lvds_pn_swap = 0;
		lvds_ctrl3.lvds_map_inv = 1;//frank@0114 sync sirius register script
		lvds_ctrl3.lvds_map = panel->iCONFIG_DISPLAY_BITMAPPING_TABLE?1:0;
		lvds_ctrl3.lvds_aport_en = 1;
		lvds_ctrl3.lvds_bport_en = 1;
//		lvds_ctrl3.lvds_cport_en = 1;
//		lvds_ctrl3.lvds_dport_en = 1;
#ifdef CONFIG_BOARD_298X_TV013_QFP176_EMMC
		lvds_ctrl3.lvds_mirror = 1;
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
#else
	panel_interface_common();
#endif


	double_buffer_ctrl_reg.regValue = rtd_inl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR);
	double_buffer_ctrl_reg.dreg_dbuf_en = 1;
	rtd_outl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR, double_buffer_ctrl_reg.regValue);


	display_timing_ctrl1_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR);
	display_timing_ctrl1_reg.disp_frc_on_fsync = 0;
	display_timing_ctrl1_reg.disp_fsync_en = 0;

	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		display_timing_ctrl1_reg.dout_force_bg = 0;		
		display_timing_ctrl1_reg.disp_en = 1;					// enable dtg out for sync vby_one timing
	}
	else
		display_timing_ctrl1_reg.dout_force_bg = 1;

	rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, display_timing_ctrl1_reg.regValue);
#if 0
	if(panel->iCONFIG_PANEL_TYPE == P_VBY1_4K2K){

		printf("================== P_VBY1_4K2K condition ===================\n");
		//vby1_fhd_1pixel_1seg_4port();


		display_timing_ctrl1_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR);
		display_timing_ctrl1_reg.disp_en = 1;					// enable dtg out for sync vby_one timing
		rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, display_timing_ctrl1_reg.regValue);
	}

	else{
		//LVDS/mini-LVDS/EPI/VBy1 TXPHY //frank@0114 sync below LVDS setting from sirius hw sd script
		rtd_outl(0xb8000C00, 0x03001810);	// PI_A1 = Phase0, PI_A2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
		rtd_outl(0xb8000C04, 0x03001810);	// PI_B1 = Phase0, PI_B2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
		rtd_outl(0xb8000C08, 0x03040000);	// PI_AB = Phase0, CK7X = 1X Current, CK5X Duty Adjust Disable, PI_Clock = 300~600MHz,
		rtd_outl(0xb8000C0C, 0x04153700);	// Choose legacy charge-pump, DIV248 = 2, VCO = 74.25*7*DIV248 = 1.0395GHz,
							// Small Kvco, CK1X Not Inverse, PLL_VCO = 2V,
							// Icp = 12.5uA, Cp = 9.5pF, Rs = 12Kohm,
							// PI_A Disble, PI_B Disable ==> PI_AB Disble
		rtd_outl(0xb8000C10, 0x90040000);	// P0 A-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C14, 0x90040000);	// P0 B-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C18, 0x90040000);	// P0 C-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C1C, 0x91040000);	// P0 D-Pair LVDS, Use PI_A2, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C20, 0x90040000);	// P0 E-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C24, 0x90040000);	// P0 F-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C28, 0x90040000);	// P0 G-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C2C, 0x90040000);	// P0 H-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,

     	#if defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV013_QFP176_EMMC)||defined(CONFIG_BOARD_298X_TV010_QFP176_V3_EMMC)  //add by markchen for backlight PWM control 20140423
		rtd_outl(0xb8000010,0x1200001E);//PWM CLK EN
		rtd_outl(0xb8000010,0x1000001E);//PWM CLK EN
		rtd_outl(0xb8000004,0x10042973);//PWM RST
		rtd_outl(0xb8000004,0x100429f3);//PWM RST
		rtd_outl(0xb8000010,0x1200001E);//PWM CLK EN


		rtd_outl(0xb8000c78,0xffff0000); //LVDS pad power on

		rtd_part_outl(0xb80008B8,31,27,0xD);//pinshare

		rtd_outl(0xb8000C2C, 0x50040000);

		rtd_outl(0xb801b430,0x00320063);
		rtd_outl(0xb801b42c,0x800030A8);
		rtd_outl(0xb801b428,0x60000000);
		mdelay(((&default_panel_parameter)->iPANEL_TO_LVDS_ON_ms));
		#endif
		rtd_outl(0xb8000C30, 0x00000000);	// P0 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
							// P0 Double Driving disable,
		rtd_outl(0xb8000C34, 0x90040000);	// P1 A-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C38, 0x90040000);	// P1 B-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C3C, 0x90040000);	// P1 C-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C40, 0x91040000);	// P1 D-Pair LVDS, Use PI_B2, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C44, 0x90040000);	// P1 E-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C48, 0x90040000);	// P1 F-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C4C, 0x90040000);	// P1 G-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
		rtd_outl(0xb8000C50, 0x00000000);	// P1 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
							// P1 Double Driving disable,
		rtd_outl(0xb8000C54, 0x09ECD000);	// ISOURCE = IBHX, Select LVDS/mLVDS/EPI TXPHY,
							// LDO_CML Enable & 2V, LDO_DPLL/LVDSPLL Enable & 1.05V,
							// Swing = 4mA. VCM = 1.25V,
		rtd_outl(0xb8000C58, 0x00000000);	// P0 Pre-emphasis disable, internal resistor disable, TTL 2mA,
							// P0 Not Adjudt CK1X Delay, CML 1.2mA (PLL<1.2GHz),
		rtd_outl(0xb8000C5C, 0x00000000);	// P0 CMOS Mode, SR 1-buffer delay,
		rtd_outl(0xb8000C60, 0x00000000);	// P1 Pre-emphasis disable, internal resistor disable, TTL 2mA,
							// P1 Not Adjudt CK1X Delay, CML 1.2mA (PLL<1.2GHz),
		rtd_outl(0xb8000C64, 0x00000000);	// P1 CMOS Mode, SR 1-buffer delay,
		rtd_outl(0xb8000C78, 0xFFFF0000);	// Lane Power Enable for non-Vby1-Mode
	}
#endif

	if(panel->iCONFIG_PANEL_TYPE == P_DISP_TO_TVOX){
		display_timing_ctrl2_RBUS display_timing_ctrl2_reg;
		double_buffer_ctrl_RBUS double_buffer_ctrl_reg;

		double_buffer_ctrl_reg.regValue = rtd_inl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR);
		double_buffer_ctrl_reg.dreg_dbuf_en = 0;
		rtd_outl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR, double_buffer_ctrl_reg.regValue);

		display_timing_ctrl2_reg.regValue = rtd_inl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR);
		display_timing_ctrl2_reg.d2tve_src_sel = 0x3; //dither
		rtd_outl(PPOVERLAY_DISPLAY_TIMING_CTRL2_VADDR, display_timing_ctrl2_reg.regValue);

		double_buffer_ctrl_reg.regValue = rtd_inl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR);
		double_buffer_ctrl_reg.dreg_dbuf_en = 1;
		rtd_outl(PPOVERLAY_DOUBLE_BUFFER_CTRL_VADDR, double_buffer_ctrl_reg.regValue);

	}

#ifdef ENABLE_DISP_BISR //frank@0114 fix me
	rtk_dispi_bisr();
#endif

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

void panel_interface_common(void)
{	
	lvds_ctrl0_RBUS lvds_ctrl0_reg;	
	lvds_ctrl3_RBUS  lvds_ctrl3_reg;

	lvds_ctrl0_reg.regValue = rtd_inl(PIF_LVDS_CTRL0_VADDR);	
	lvds_ctrl3_reg.regValue = rtd_inl(PIF_LVDS_CTRL3_VADDR);

	printf("=== Panel Type : %d ===\n", default_panel_parameter.iCONFIG_PANEL_TYPE);
	
	if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
		lvds_ctrl0_reg.plt_lvds_mode_78 = 3; //vb1 mode;
		lvds_ctrl3_reg.regValue = 0; //LVDS Port Disable

		//LVDS Pin Share
		rtd_maskl(0xb80008BC,0x003FFFFF,0xAD400000);	// LVDS A-Port E Pair P/N PinShare to VBY1_HTPD/VBY1_LOCK
		rtd_maskl(0xb80008C4,0xFFFFF003,0x00000000);	// LVDS B-Port D Pair PinShare
		rtd_outl(0xb80008C8, 0x00000000);		// LVDS B-Port A/B/C Pair PinShare
		
		panel_vby1_tx();

		
		lane_status_RBUS lane_status_reg;
		
		lane_status_reg.regValue = 0;
		lane_status_reg.byte_mode = 4;
		lane_status_reg.section= default_panel_parameter.iCONFIG_SFG_SEG_NUM;
		if(default_panel_parameter.iCONFIG_SR_PIXEL_MODE == 0)
			lane_status_reg.pixel_mode = 1;
		else if(default_panel_parameter.iCONFIG_SR_PIXEL_MODE == 1)
			lane_status_reg.pixel_mode = 2;
		else if(default_panel_parameter.iCONFIG_SR_PIXEL_MODE == 2)
			lane_status_reg.pixel_mode = 4; 		
		lane_status_reg.lane_count = default_panel_parameter.iCONFIG_SFG_PORT_NUM;
		rtd_outl(VBY1_LANE_STATUS_VADDR, lane_status_reg.regValue);
		
		printf("Vby1 Lane Status: %x \n", lane_status_reg.regValue);
	}
	else if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_EPI_TYPE){		
		lvds_ctrl0_reg.plt_lvds_mode_78 = 2; //epi mode;		
		lvds_ctrl3_reg.regValue = 0; //LVDS Port Disable
		
		//LVDS Pin Share
		rtd_outl(0xb80008B8, 0x00000000);	// LVDS A-Port F/G/H Pair PinShare
		rtd_outl(0xb80008BC, 0x00000000);	// LVDS A-Port C/D/E Pair PinShare
		rtd_outl(0xb80008C0, 0x00000000);	// LVDS A-Port A/B, LVDS B-Port G Pair PinShare
		rtd_outl(0xb80008C4, 0x00000000);	// LVDS B-Port D/E/F Pair PinShare
		rtd_outl(0xb80008C8, 0x00000000);	// LVDS B-Port A/B/C Pair PinShare

		
		rtd_maskl(CRT_GROUP1_CK_SEL_VADDR,0xFC7FFFFF,0x00000000); // EPI_DIV_CLKSEL, bit25=0=from normal path, bit[24:23]=00=divide by 3,(6 lane mode), (CRT spec)

		panel_epi_tx();
	}	
	else if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_MINI_LVDS){	
		lvds_ctrl0_reg.plt_lvds_mode_78 = 1; //mini lvds mode;
	}
	else{		
		lvds_ctrl0_reg.plt_lvds_mode_78 = 0; //lvds mode;
		
	    lvds_ctrl3_reg.lvds_pn_swap = 0;		
		lvds_ctrl3_reg.lvds_map_inv = 1;//frank@0114 sync sirius register script
		lvds_ctrl3_reg.lvds_map = default_panel_parameter.iCONFIG_DISPLAY_BITMAPPING_TABLE?1:0;
		lvds_ctrl3_reg.lvds_aport_en = 1;
		lvds_ctrl3_reg.lvds_bport_en = 1;
#ifdef CONFIG_BOARD_298X_TV013_QFP176_EMMC
		lvds_ctrl3_reg.lvds_mirror = 1;
#endif
#if defined(LVDS_PN_SWAP)
	#if LVDS_PN_SWAP
		lvds_ctrl3_reg.lvds_pn_swap = 1;
		rtd_outl(PIF_LVDS_CTRL3_VADDR, lvds_ctrl3_reg.regValue);
	#endif
#endif		

		//LVDS Pin Share
/*		
		rtd_outl(0xb80008B8, 0x00000000);	// LVDS A-Port F/G/H Pair PinShare
		rtd_outl(0xb80008BC, 0x00000000);	// LVDS A-Port C/D/E Pair PinShare
		rtd_outl(0xb80008C0, 0x00000000);	// LVDS A-Port A/B, LVDS B-Port G Pair PinShare
		rtd_outl(0xb80008C4, 0x00000000);	// LVDS B-Port D/E/F Pair PinShare
		rtd_outl(0xb80008C8, 0x00000000);	// LVDS B-Port A/B/C Pair PinShare
*/
		//frank@0114 sync sirius hw setting	
		rtd_outl(0xb80008C4, 0x00000000);	// LVDS B-Port D/E/F Pair PinShare
		rtd_outl(0xb80008C8, 0x00000000);	// LVDS B-Port A/B/C Pair PinShare
		rtd_maskl(0xb80008B8, 0xfffff003, 0x0); // LVDS A-Port F Pair PinShare
		rtd_outl(0xb80008BC, 0x00000000);	// LVDS A-Port C/D/E Pair PinShare
		rtd_maskl(0xb80008C0, 0x00000ffc, 0x0); // LVDS A-Port A/B,

		panel_lvds_tx();
	}
	rtd_outl(PIF_LVDS_CTRL0_VADDR, lvds_ctrl0_reg.regValue);
	rtd_outl(PIF_LVDS_CTRL3_VADDR, lvds_ctrl3_reg.regValue);

}

void panel_lvds_tx()
{
	//LVDS/mini-LVDS/EPI/VBy1 TXPHY //frank@0114 sync below LVDS setting from sirius hw sd script
	rtd_outl(0xb8000C00, 0x03001810);	// PI_A1 = Phase0, PI_A2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C04, 0x03001810);	// PI_B1 = Phase0, PI_B2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C08, 0x03040000);	// PI_AB = Phase0, CK7X = 1X Current, CK5X Duty Adjust Disable, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C0C, 0x04153700);	// Choose legacy charge-pump, DIV248 = 2, VCO = 74.25*7*DIV248 = 1.0395GHz,
						// Small Kvco, CK1X Not Inverse, PLL_VCO = 2V,
						// Icp = 12.5uA, Cp = 9.5pF, Rs = 12Kohm,
						// PI_A Disble, PI_B Disable ==> PI_AB Disble
	rtd_outl(0xb8000C10, 0x90040000);	// P0 A-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C14, 0x90040000);	// P0 B-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C18, 0x90040000);	// P0 C-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C1C, 0x91040000);	// P0 D-Pair LVDS, Use PI_A2, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C20, 0x90040000);	// P0 E-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C24, 0x90040000);	// P0 F-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C28, 0x90040000);	// P0 G-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C2C, 0x90040000);	// P0 H-Pair LVDS, Use PI_A1, SR Disable, internal resistor 100ohm,

#if defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV013_QFP176_EMMC)||defined(CONFIG_BOARD_298X_TV010_QFP176_V3_EMMC) \ 
	||defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)  //add by markchen for backlight PWM control 20140423

	rtd_outl(0xb8000010,0x1200001E);//PWM CLK EN
	rtd_outl(0xb8000010,0x1000001E);//PWM CLK EN
	rtd_outl(0xb8000004,0x10042973);//PWM RST
	rtd_outl(0xb8000004,0x100429f3);//PWM RST
	rtd_outl(0xb8000010,0x1200001E);//PWM CLK EN


	rtd_outl(0xb8000c78,0xffff0000); //LVDS pad power on

	rtd_part_outl(0xb80008B8,31,27,0xD);//pinshare

	rtd_outl(0xb8000C2C, 0x50040000);

	rtd_outl(0xb801b430,0x00320063);
	rtd_outl(0xb801b42c,0x800030A8);
	rtd_outl(0xb801b428,0x60000000);
//	mdelay(((&default_panel_parameter)->iPANEL_TO_LVDS_ON_ms));
#endif
	rtd_outl(0xb8000C30, 0x00000000);	// P0 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P0 Double Driving disable,
	rtd_outl(0xb8000C34, 0x90040000);	// P1 A-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C38, 0x90040000);	// P1 B-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C3C, 0x90040000);	// P1 C-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C40, 0x91040000);	// P1 D-Pair LVDS, Use PI_B2, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C44, 0x90040000);	// P1 E-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C48, 0x90040000);	// P1 F-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C4C, 0x90040000);	// P1 G-Pair LVDS, Use PI_B1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C50, 0x00000000);	// P1 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P1 Double Driving disable,
	rtd_outl(0xb8000C54, 0x09ECD000);	// ISOURCE = IBHX, Select LVDS/mLVDS/EPI TXPHY,
						// LDO_CML Enable & 2V, LDO_DPLL/LVDSPLL Enable & 1.05V,
						// Swing = 4mA. VCM = 1.25V,
	rtd_outl(0xb8000C58, 0x00000000);	// P0 Pre-emphasis disable, internal resistor disable, TTL 2mA,
						// P0 Not Adjudt CK1X Delay, CML 1.2mA (PLL<1.2GHz),
	rtd_outl(0xb8000C5C, 0x00000000);	// P0 CMOS Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C60, 0x00000000);	// P1 Pre-emphasis disable, internal resistor disable, TTL 2mA,
						// P1 Not Adjudt CK1X Delay, CML 1.2mA (PLL<1.2GHz),
	rtd_outl(0xb8000C64, 0x00000000);	// P1 CMOS Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C78, 0xFFFF0000);	// Lane Power Enable for non-Vby1-Mode
/*
	//frank@0114 sync sirius hw setting	
	rtd_outl(0xb80008C4, 0x00000000);	// LVDS B-Port D/E/F Pair PinShare
	rtd_outl(0xb80008C8, 0x00000000);	// LVDS B-Port A/B/C Pair PinShare
	rtd_maskl(0xb80008B8, 0xfffff003, 0x0); // LVDS A-Port F Pair PinShare
	rtd_outl(0xb80008BC, 0x00000000);	// LVDS A-Port C/D/E Pair PinShare
	rtd_maskl(0xb80008C0, 0x00000ffc, 0x0); // LVDS A-Port A/B,
*/	
}

void panel_epi_tx()
{
	//epi mac v14
	// EPI MAC-layer configuration

	rtd_outl(0xB802D500,0x00000015); // CTR_Start=0x15,CTR_Start_dummy=0x0,P/N no swap. 

	rtd_outl(0xB802D504,0x00000000); // Lane0: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D508,0x00000000); // Lane1: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D50c,0x00000000); // Lane2: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D510,0x00000000); // Lane3: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D514,0x00000000); // Lane4: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D518,0x00000000); // Lane5: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D51c,0x00000000); // Lane6: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D520,0x00000000); // Lane7: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 

	// NEW
	rtd_outl(0xB802D524,0x0000db09); // Lane0: SOE for LGD L7 use, T2=222(bit[17:8]=219=0xDB), T1=13(bit[7:0]=9=0x9)  
	rtd_outl(0xB802D528,0x0000d907); // Lane1: SOE for LGD L6 use, T2=220(bit[17:8]=217=0xD9), T1=11(bit[7:0]=7=0x7) 
	rtd_outl(0xB802D52c,0x0000d705); // Lane2: SOE for LGD L5 use, T2=218(bit[17:8]=215=0xD7), T1= 9(bit[7:0]=5=0x5)
	rtd_outl(0xB802D530,0x0000d503); // Lane3: SOE for LGD L4 use, T2=216(bit[17:8]=213=0xD5), T1= 7(bit[7:0]=3=0x3)
	rtd_outl(0xB802D534,0x0000d402); // Lane4: SOE for LGD L3 use, T2=215(bit[17:8]=212=0xD4), T1= 6(bit[7:0]=2=0x2)
	rtd_outl(0xB802D538,0x0000d604); // Lane5: SOE for LGD L2 use, T2=217(bit[17:8]=214=0xD6), T1= 8(bit[7:0]=4=0x4)
	rtd_outl(0xB802D53c,0x0000d706); // Lane6: SOE for LGD L1 use, T2=219(bit[17:8]=215=0xD7), T1=10(bit[7:0]=6=0x6)
	rtd_outl(0xB802D540,0x0000da08); // Lane7: SOE for LGD L0 use, T2=221(bit[17:8]=218=0xDA), T1=12(bit[7:0]=8=0x8)

	rtd_outl(0xB802D544,0x00000410); // Lane0: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D548,0x00000410); // Lane1: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D54c,0x00000C10); // Lane2: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D550,0x00000C10); // Lane3: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D554,0x00000C10); // Lane4: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D558,0x00000C10); // Lane5: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D55c,0x00000410); // Lane6: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D560,0x00000410); // Lane7: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	
	rtd_outl(0xB802D564,0xFFFFFFE3); // CTR2:Select CTR2(c0 ~c5 ) source. From Tcon or Register(all "1"). (c0,POL from tcon3)
	rtd_outl(0xB802D568,0xFFF4FFFF); // CTR2:Select CTR2(c6 ~c11) source. From Tcon or Register(all "1"). (c9,GSP from tcon9)
	rtd_outl(0xB802D56c,0xFFFFFFFF); // CTR2:Select CTR2(c12~c17) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D570,0xFFFFFFFF); // CTR2:Select CTR2(c18~c23) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D574,0xFFFFFFFF); // CTR2:Select CTR2(c24~c29) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D578,0x00000000); // CTR3: reserved for future. bit30=0 to disable.
	rtd_outl(0xB802D57c,0x0000002A); // Data_Start=0x2A,Data_Start_dummy=0x0.
	rtd_outl(0xB802D580,0x08000000); // Bit31=0=No_data_in.(Bit30=1 to reset), Bit29=0=PRBS7_OFF, 8bit
	rtd_outl(0xB802D584,0xC0000000); // EPI mode setting, bit[1]=0=lock_source_from_hw.
	rtd_outl(0xB802D588,0x00000C40);   // Pin_map=00=table(1)=v14,8 lane, v13 SOE
#if 0
	//---------------------------------------------------------------------------------------------------------------------------------
	//PIF
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D000, 0x00000008);	// PIF EPI Mode, bit[3:2]=10=EPI mode. (Display_Panel_Interface spec)
	rtd_outl(0xb802D010, 0x00000000);	// LVDS Port Disable
///////////////////////////////
	//---------------------------------------------------------------------------------------------------------------------------------
	//LVDS Pin Share
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb80008B8, 0x00000000);	// LVDS A-Port F/G/H Pair PinShare
	rtd_outl(0xb80008BC, 0x00000000);	// LVDS A-Port C/D/E Pair PinShare
	rtd_outl(0xb80008C0, 0x00000000);	// LVDS A-Port A/B, LVDS B-Port G Pair PinShare
	rtd_outl(0xb80008C4, 0x00000000);	// LVDS B-Port D/E/F Pair PinShare
	rtd_outl(0xb80008C8, 0x00000000);	// LVDS B-Port A/B/C Pair PinShare
#endif
	//---------------------------------------------------------------------------------------------------------------------------------
	//LVDS/mini-LVDS/EPI/VBy1 TXPHY (EPI mode)
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000C00, 0x03001810);	// PI_A1 = Phase0, PI_A2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C04, 0x03001810);	// PI_B1 = Phase0, PI_B2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C08, 0x03040000);	// PI_AB = Phase0, CK7X = 1X Current, CK5X Duty Adjust Disable, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C0C, 0x00313730);	// Choose legacy charge-pump, DIV248 = 1, VCO = 74.25*7*DIV248 = 1.0395GHz,
						// Small Kvco, CK1X Not Inverse, PLL_VCO = 2V,
						// Icp = 12.5uA, Cp = 9.5pF, Rs = 12Kohm,
						// PI_A Disble, PI_B Disable ==> PI_AB Disble
	rtd_outl(0xb8000C10, 0x6C040000);	// P0 A-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C14, 0x6C040000);	// P0 B-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C18, 0x6C040000);	// P0 C-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C1C, 0x6C040000);	// P0 D-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C20, 0x6C040000);	// P0 E-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C24, 0x6C040000);	// P0 F-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C28, 0x6C040000);	// P0 G-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C2C, 0x6C040000);	// P0 H-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C30, 0x07f80000);	// P0 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P0 Double Driving enable,
	rtd_outl(0xb8000C34, 0x6C040000);	// P1 A-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C38, 0x6C040000);	// P1 B-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C3C, 0x6C040000);	// P1 C-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C40, 0x6C040000);	// P1 D-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C44, 0x6C040000);	// P1 E-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C48, 0x6C040000);	// P1 F-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C4C, 0x6C040000);	// P1 G-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C50, 0x07f00000);	// P1 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P1 Double Driving enable,
	rtd_outl(0xb8000C54, 0x08D0D000);	// ISOURCE = IBHX, Select LVDS/mLVDS/EPI TXPHY, 
						// LDO_CML Enable & 2V, LDO_DPLL/LVDSPLL Enable & 1.05V,
						// Swing = 3mA. VCM = 0.9V,
	rtd_outl(0xb8000C58, 0x1fe01fe0);	// P0 Pre-emphasis disable, internal resistor enable, TTL 2mA,
						// P0 Not Adjudt CK1X Delay, CML 2.4mA (PLL>1.2GHz),
	rtd_outl(0xb8000C5C, 0xFF000000);	// P0 CML Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C60, 0x1fc07f00);	// P1 Pre-emphasis disable, internal resistor enable, TTL 2mA,
						// P1 Not Adjudt CK1X Delay, CML 2.4mA (PLL>1.2GHz),
	rtd_outl(0xb8000C64, 0xFF000000);	// P1 CML Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C78, 0x80000000);	// Port Power Enable for non-Vby1-Mode (Lane power off)	

	//TCON
	rtd_part_outl(0xb80008C4,31,27,0x3);//Tcon16 (GCLK)
	rtd_part_outl(0xb8000C48,31,29,0x2);//Tcon16 pin share enable

	rtd_part_outl(0xb80008C4,6,2,0x3);//Tcon1 (GST)
	rtd_part_outl(0xb8000C40,28,26,0x2);//Tcon1 pin share enable

	rtd_part_outl(0xb80008C8,16,12,0x3);//Tcon5 (E/O)
	rtd_part_outl(0xb8000C38,28,26,0x2);//Tcon5 pin share enable

	rtd_part_outl(0xb80008C8,6,2,0x3);//Tcon7 (MCLK)
	rtd_part_outl(0xb8000C34,28,26,0x2);//Tcon7 pin share enable
	/////////////////////////////////////////////////////////////// which LVDS PAD would be set GPIO port ?

	rtd_part_outl(0xb80008c8,11,7,0x1F);// set reverse signal became to GPO
	rtd_part_outl(0xb8000c34,31,29,0x2);// this GPO was setted for Siruous use
	rtd_part_outl(0xb801b108,15,15,0x1);


	/////////// set Tcon3 initial value for test signal 

	rtd_outl(0xb802d704,0x00200000);//(modify)
	rtd_outl(0xb802dB0C,0x00000001);//(modify)

	///////////////////////// set Tcon5 and Tcon4 become E/O

	//rtd_outl(0xb802d7b4,0x00000180); //set Tcon5 enable and set frame cross mode (modify)
	//rtd_outl(0xb802d7b0,0x0016044e); //set Vstart Vend (modify)
	//rtd_outl(0xb802d7ac,0x00990819); // set Hstart Hend (modify)

	rtd_outl(0xb802d7b4,0x00000480); //set Tcon5 enable and set frame cross mode (modify)
	rtd_outl(0xb802d7b0,0x045B045B); //set Vstart Vend (modify)
	rtd_outl(0xb802d7ac,0x00990099); //set Hstart Hend (modify)
	rtd_outl(0xb802d7bc,0x0000007E);// set frame period=126 (modify)
	
	rtd_outl(0xb802d794,0x00000480); // set Tcon4 enable frame cross mode
	rtd_outl(0xb802d790,0x045B045B); // set Vstart Vend
	rtd_outl(0xb802d78C,0x01040104); // set Hstart Hend
	rtd_outl(0xb802d79C,0x0000007E);// set frame period=126
	
	rtd_outl(0xb802d7b4,0x00000483); // set Tcon5=Tcon5 Xor Tcon4
	rtd_outl(0xb802db0c,0x00000000);//Tcon IP disable
	rtd_outl(0xb802db0c,0x00000001);// Tcon IP enable
	/////////////////////////////
	
	////////////set Tcon0 Tcon1 become GST
	rtd_outl(0xb802d714,0x00000180);//set Tcon0 enable and across line1 mode 
	rtd_outl(0xb802d710,0x00080011);//set Tcon0 Vstart Vend
	rtd_outl(0xb802d70c,0x004D00A5);//set Tcon0 Hstart Hend
	
	rtd_outl(0xb802d734,0x00000183);//set Tcon1 enable and across line1 mode
	rtd_outl(0xb802d730,0x04530457);//set Tcon1 Vstart and Vend
	rtd_outl(0xb802d72c,0x08190819);//set Tcon1 Hstart Hend 
	/////////////////////////////////////////////////// 
	
	///////////// set Tcon7 MCLK
	
	rtd_outl(0xb802d7f4,0x00000080);//set Tcon7 enable
	rtd_outl(0xb802d7f0,0x00140450);//VStart and Vend  //	(0x00150452)
	rtd_outl(0xb802d7ec,0x045005B0);//HStart and Hend  // be careful 0x04d006a0
	//////////////////////////////
	
	//////////////////////////////////// set Tcon16,Tcon15,Tcon14 became to GCLK
	
	//rtd_outl(0xb802d8e0,0x00000280); // enable Tcon14 and set across line2 mode
	//rtd_outl(0xb802d8dc,0x00110450); // set Vstart Vend/////change 44F
	//rtd_outl(0xb802d8d8,0x089304C0); // set Hstart Hend//0x0380001C
	
	//rtd_outl(0xb802d900,0x00000180); //enable Tcon15 and set across line1 mode
	//rtd_outl(0xb802d8fc,0x00110014); // set Vstart Vend
	//rtd_outl(0xb802d8f8,0x057000E1); //set Hstart Hend
	//rtd_outl(0xb802d900,0x000001C0); // set Tcon15 invertion
	
	//rtd_outl(0xb802d900,0x000001C1);// Tcon15 AND Tcon14
	
	//rtd_outl(0xb802d920,0x00000182);// set Tcon16 enable and across line1 mode
	//rtd_outl(0xb802d91C,0x044F0457);//set Tcon16 Vstart Vend
	//rtd_outl(0xb802d918,0x08190819);// set Tcon16 Hstart Hend
	
	rtd_outl(0xb802d900,0x00000180);// set Tcon15 across line1 mode
	rtd_outl(0xb802d8FC,0x044D0457);// set Tcon15 Vstart Vend
	rtd_outl(0xb802d8F8,0x00990819);// set Tcon15 Hstart Hend
	
	rtd_outl(0xb802d920,0x00000082);// set Tcon16 normal mode
	rtd_outl(0xb802d91C,0x0012044D);// set Tcon16 Vstart Vend
	rtd_outl(0xb802d918,0x01000400);// set Tcon16 Hstart Hend
	
	//////////////////////////////////set Tcon9 became GPL
	rtd_outl(0xb802d834,0x00000180); //set Tcon9 become to across line1 mode 
	rtd_outl(0xb802d830,0x00140018); //set Vstart Vend
	rtd_outl(0xb802d82c,0x00010750); //set Hstart Hend
	//////////////////////////////////set Tcon2 became to POL
	rtd_outl(0xb802d754,0x00000380); //set Tcon2 become to frame across mode	// be careful
	rtd_outl(0xb802d750,0x0015010E); //set Vstart Vend
	rtd_outl(0xb802d74c,0x00990120); //set Hstart Hend
	rtd_outl(0xb802d758,0x00040002); //set number of line cross period
	
	rtd_outl(0xb802d76C,0x00070007);//set Tcon3 Hstart Hend
	rtd_outl(0xb802d770,0x00010001);//set Tcon3 Vstart Vend
	rtd_outl(0xb802d774,0x00000483);//set Tcon3 which across 
	rtd_outl(0xb802d77c,0x00000000);
	
//	rtd_outl(0xb802d170,0x00000155);
//	rtd_part_outl(0xb8028014,12,0,0x544);
//	rtd_part_outl(0xb802800c,28,16,0x897);
//	rtd_part_outl(0xb802800C,12,0,0x897);


	//panel config
	// 60hz
//	rtd_outl(0xb8028294, 0x00000001);	// DCLK = DPLL_Clock div 2 for FHD120hz (DTG spec) 
	rtd_outl(0xb8000C0C, 0x00313730);	// Choose legacy charge-pump, DIV248 = 1, VCO = 74.25*7*DIV248 = 1.0395GHz,
		
	rtd_maskl(0xb8000018,0xFC7FFFFF,0x00000000); // bit25=0=from normal path, bit[24:23]=00=divide by 3,(6 lane mode), (CRT spec)
	
	rtd_outl(0xB802D584,0xC0000006); // EPI mode setting, bit[1]=1=lock_source_from_reg, bit[2]=lock_value=1.
	
	rtd_outl(0xB802D524,0x00011506); // Lane0: SOE for LGD L7 use, T2=222(bit[17:8]=219=0xDB), T1=13(bit[7:0]=9=0x9)  
	rtd_outl(0xB802D528,0x00011506); // Lane1: SOE for LGD L6 use, T2=220(bit[17:8]=217=0xD9), T1=11(bit[7:0]=7=0x7) 
	rtd_outl(0xB802D52c,0x00011506); // Lane2: SOE for LGD L5 use, T2=218(bit[17:8]=215=0xD7), T1= 9(bit[7:0]=5=0x5)
	rtd_outl(0xB802D530,0x00011506); // Lane3: SOE for LGD L4 use, T2=216(bit[17:8]=213=0xD5), T1= 7(bit[7:0]=3=0x3)
	rtd_outl(0xB802D534,0x00011506); // Lane4: SOE for LGD L3 use, T2=215(bit[17:8]=212=0xD4), T1= 6(bit[7:0]=2=0x2)
	rtd_outl(0xB802D538,0x00011506); // Lane5: SOE for LGD L2 use, T2=217(bit[17:8]=214=0xD6), T1= 8(bit[7:0]=4=0x4)
	rtd_outl(0xB802D53c,0x00011506); // Lane6: SOE for LGD L1 use, T2=219(bit[17:8]=215=0xD7), T1=10(bit[7:0]=6=0x6)
	rtd_outl(0xB802D540,0x00011506); // Lane7: SOE for LGD L0 use, T2=221(bit[17:8]=218=0xDA), T1=12(bit[7:0]=8=0x8)
	
	rtd_outl(0xB802D544,0x00000090); // Lane0: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D548,0x00000090); // Lane1: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D54c,0x00000090); // Lane2: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D550,0x00000090); // Lane3: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D554,0x00000090); // Lane4: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D558,0x00000090); // Lane5: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D55c,0x00000090); // Lane6: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D560,0x00000090); // Lane7: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)

	// Lane Power Enable for non-Vby1-Mode
	rtd_outl(0xb8000C78, 0x9F800000);	// Lane Power Enable for non-Vby1-Mode


}

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

#if 0 //ben marked unused code
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
#endif

void vby1_fhd_dtg(void)
{
	printf("=== vby1_fhd_dtg ====");
	rtd_maskl(0xb8000190,0xF00F888F,0x02101450);	// DPLL M, N, Icp = 2.5uA, Rs = 6KOhms.
	rtd_maskl(0xb8000194,0xFFCFCFFE,0x00300001);	// DPLL DIV_A/1
	rtd_maskl(0xb8028294,0xFFFFFFFC,0x00000000);	// DPLL DIV_D/1
	rtd_maskl(0xb8000300,0xF000FFFA,0x07500001);	// DPLL OFFSET
	rtd_maskl(0xb8000300,0xF000FFFA,0x07500005);	// DPLL OFFSET Load in

	rtd_outl(0xb8028000, 0x01000000);	// Free Run Mode
	rtd_outl(0xb8028008, 0x0000000F);	// Hsync width
	rtd_outl(0xb802800C, 0x08970897);	// DH_total
	rtd_outl(0xb8028010, 0x00000005);	// DV_sync width
	rtd_outl(0xb8028014, 0x00000464);	// DV_total
	rtd_outl(0xb8028018, 0x008C080C);	// DH_den_sta, DH_den_end
	rtd_outl(0xb802801C, 0x0016044E);	// DV_den_sta, DV_den_end
	rtd_outl(0xb8028024, 0x000000FF);	// Display Background Color
	rtd_outl(0xb8028028, 0x00000002);	// Disable Buffer

	rtd_outl(0xb8028100, 0x00000001);	// Main Display enable
	rtd_outl(0xb8028108, 0x0CD40000);	// Main Border Color
	rtd_outl(0xb802810C, 0x00000000);	// Main Background Color
	rtd_outl(0xb8028110, 0x00000780);	// Main DEN_H_str,Main DEN_H_end
	rtd_outl(0xb8028114, 0x00000438);	// Main DEN_V_str,Main DEN_V_end
	rtd_outl(0xb8028118, 0x00000780);	// Main Background_H_str,Main Background_H_end
	rtd_outl(0xb802811C, 0x00000438);	// Main Background_V_str,Main Background_V_end
	rtd_outl(0xb8028120, 0x00000780);	// Main Active_H_str,Main Active_H_end
	rtd_outl(0xb8028124, 0x00000438);	// Main Active_V_str,Main Active_V_end

}

void panel_vby1_tx(void)
{
	printf("=== panel_vby1_tx_phy ===");
#if 0
	//---------------------------------------------------------------------------------------------------------------------------------
	//DCLK DIV
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8028294, 0x00000000);	// DCLK = DPLL_Clock div 1

	//---------------------------------------------------------------------------------------------------------------------------------
	//SFG, 1 Pixel Mode, DH_ST_END = 0x008C080C, DTG_HS_Width = 16, DTG_VS_Width = 6
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D100, 0x000008C0);	// 10-bit Mode, Dout Enable, delay chain inverse + 0ns
	rtd_outl(0xb802D104, 0x4000FFFF);	// PIF_Clock = Dclk/2, Force to background enable
	rtd_outl(0xb802D108, 0x01234567);	// Port A~H mapping
	rtd_outl(0xb802D12C, 0x00000000);	// NO sub-Pixel shift
	rtd_outl(0xb802D130, 0x00000000);	// SEG 0, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D134, 0x00000000);	// SEG 0, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D138, 0x00000000);	// SEG 1, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D13C, 0x00000000);	// SEG 1, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D140, 0x00000000);	// SEG 2, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D144, 0x00000000);	// SEG 2, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D148, 0x00000000);	// SEG 3, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D14C, 0x00000000);	// SEG 3, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D150, 0x00000000);	// SEG 4, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D154, 0x00000000);	// SEG 4, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D158, 0x00000000);	// SEG 5, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D15C, 0x00000000);	// SEG 5, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D160, 0x00000000);	// SEG 6, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D164, 0x00000000);	// SEG 6, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D168, 0x00000000);	// SEG 7, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D16C, 0x00000000);	// SEG 7, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D170, 0x00000003);	// Normal Data Mapping, 1-SEG, 4-Port, No H-Flip
	rtd_outl(0xb802D174, 0x00000000);	// start address of SEG 0/1 , residue of SEG 0/1
	rtd_outl(0xb802D178, 0x00000000);	// start address of SEG 2/3 , residue of SEG 2/3
	rtd_outl(0xb802D17C, 0x00000000);	// start address of SEG 4/5 , residue of SEG 4/5
	rtd_outl(0xb802D180, 0x00000000);	// start address of SEG 6/7 , residue of SEG 6/7
	rtd_outl(0xb802D188, 0x40000000);	// Disable ByPass Mode, Auto config mode enable
	rtd_outl(0xb802D18C, 0x000F088B);	// HS_Width = 16 dclk; hsync_delay = DH_Total  - 13 = 2187;
	rtd_outl(0xb802D190, 0x00050000);	// VS_ST = 0; VS_END = 6;
	rtd_outl(0xb802D194, 0x008C0086);	// sfg_dh_den_sta = DH_DEN_ST = 140;
						// req_st = hs_back_porch - 6 = 134;
	rtd_outl(0xb802D198, 0x00000000);	// Hs_distance for DRD Mode (no USE); Seg0 Not Flip;
	rtd_outl(0xb802D19C, 0x07800000);	// final_line_length = 1920, hsync_threshold = 0
	rtd_outl(0xb802D1A0, 0x00000000);	// Residue_pix_div_12_split_mode &
						// Final_addr_split_mode for Tri-gate Mode (no USE)
	rtd_outl(0xb802D1A4, 0x0008C891);	// hs_den_io_dist = req_st + 6 = 140; (for EPI)
						// hs_io_dist = hs_delay + 6 = 2187 + 6 = 2193; (for EPI)
	rtd_outl(0xb802D1B8, 0x00000000);	// Line 4N/4N+1/4N+2/4N+3 => G_0/G_last select original data,
						// data not inverse
	rtd_outl(0xb802D1EC, 0x00000000);	// SEG 0/1, middle, no dummy pixel
	rtd_outl(0xb802D1F0, 0x00000000);	// SEG 2/3, middle, no dummy pixel
	rtd_outl(0xb802D1F4, 0x00000000);	// SEG 4/5, middle, no dummy pixel
	rtd_outl(0xb802D1F8, 0x00000000);	// SEG 6/7, middle, no dummy pixel
	rtd_outl(0xb802D1FC, 0x00000000);	// Active_pixel_RGB & Last_ext_pixel for DRD
#endif

#if 0
	//---------------------------------------------------------------------------------------------------------------------------------
	//PIF
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D000, 0x0000000C);	// PIF VBy1 Mode
	rtd_outl(0xb802D010, 0x00004000);	// LVDS Port Disable, P2S LSB First

	//---------------------------------------------------------------------------------------------------------------------------------
	//LVDS Pin Share
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_maskl(0xb80008BC,0x003FFFFF,0xAD400000);	// LVDS A-Port E Pair P/N PinShare to VBY1_HTPD/VBY1_LOCK
	rtd_maskl(0xb80008C4,0xFFFFF003,0x00000000);	// LVDS B-Port D Pair PinShare
	rtd_outl(0xb80008C8, 0x00000000);		// LVDS B-Port A/B/C Pair PinShare
#endif

	//---------------------------------------------------------------------------------------------------------------------------------
	//LVDS/mini-LVDS/EPI/VBy1 TXPHY
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000C00, 0x03001810);	// PI_A1 = Phase0, PI_A2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C04, 0x03001810);	// PI_B1 = Phase0, PI_B2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C08, 0x03040000);	// PI_AB = Phase0, CK7X = 1X Current, CK5X Duty Adjust Disable, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C0C, 0x000C3330);	// Choose legacy charge-pump, DIV248 = 1,
						// PLL_Out = VCO = 297*4/4*5/DIV248 = 1.485GHz,
						// Small Kvco, CK1X Not Inverse, PLL_VCO = 2V,
						// Icp = 2.5uA, Cp = 9.5pF, Rs = 6Kohm,
						// PI_A Disble, PI_B Disable ==> PI_AB Disble
	rtd_outl(0xb8000C10, 0xFC040000);	// P0 A-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C14, 0xFC040000);	// P0 B-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C18, 0xFC040000);	// P0 C-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C1C, 0xFC040000);	// P0 D-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C20, 0xFC040000);	// P0 E-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C24, 0xFC040000);	// P0 F-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C28, 0xFC040000);	// P0 G-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C2C, 0xFC040000);	// P0 H-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C30, 0x00000000);	// P0 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P0 Double Driving disable,
	rtd_outl(0xb8000C34, 0xD8040000);	// P1 A-Pair Vby1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C38, 0xD8040000);	// P1 B-Pair Vby1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C3C, 0xD8040000);	// P1 C-Pair Vby1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C40, 0xD8040000);	// P1 D-Pair Vby1, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C44, 0xFC040000);	// P1 E-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C48, 0xFC040000);	// P1 F-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C4C, 0xFC040000);	// P1 G-Pair Hi-Z, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C50, 0x00000000);	// P1 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P1 Double Driving disable,
	rtd_outl(0xb8000C54, 0xC96CD000);	// ISOURCE = IBHN, Select VBy1 TXPHY,
						// LDO_CML Enable & 2V, LDO_DPLL/LVDSPLL Enable & 1.05V,
						// Swing = 3.5mA. VCM = 1.25V,
	rtd_outl(0xb8000C58, 0x00000000);	// P0 Pre-emphasis disable, internal resistor disable, TTL 2mA,
						// P0 Not Adjudt CK1X Delay, CML 1.2mA (PLL<1.2GHz),
	rtd_outl(0xb8000C5C, 0xFF000000);	// P0 CML Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C60, 0x00000000);	// P1 Pre-emphasis disable, internal resistor disable, TTL 2mA,
						// P1 Not Adjudt CK1X Delay, CML 1.2mA (PLL<1.2GHz),
	rtd_outl(0xb8000C64, 0xFE000000);	// P1 CML Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C78, 0x8000000F);	// Lane Power Enable for Vby1 Mode => P1 Port A/B/C/D Pair,


	//---------------------------------------------------------------------------------------------------------------------------------
	//VBy1 A-PHY
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000C7C, 0x00000000);	// P0 Port Pre-emphasis disable, internal resister disable,
	rtd_outl(0xb8000C80, 0x00403004);	// P0 A-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000C84, 0x00403004);	// P0 B-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000C88, 0x00403004);	// P0 C-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000C8C, 0x00403004);	// P0 D-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000C90, 0x00403004);	// P0 E-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000C94, 0x00403004);	// P0 F-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000C98, 0x00403004);	// P0 G-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000C9C, 0x00403004);	// P0 H-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000CA0, 0x000F000F);	// P1 Port Pre-emphasis enable, internal resister E/F/G Pair disable,
	rtd_outl(0xb8000CA4, 0x00F01004);	// P1 A-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000CA8, 0x00F01004);	// P1 B-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000CAC, 0x00F01004);	// P1 C-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000CB0, 0x00F01004);	// P1 D-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000CB4, 0x00F01004);	// P1 E-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000CB8, 0x00F01004);	// P1 F-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,
	rtd_outl(0xb8000CBC, 0x00F01004);	// P1 G-Pair driver 15.5mA, internal 50ohm, emphasis 2mA,

	//---------------------------------------------------------------------------------------------------------------------------------
	//VBy1 D-PHY
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000CC0, 0x00000013);	// PRBS Pattern disable,
	rtd_outl(0xb8000CC4, 0x00000000);	// PN Swap disable,
	rtd_outl(0xb8000CC8, 0x00FF0000);	// Lane enable,

	//---------------------------------------------------------------------------------------------------------------------------------
	//VBy1 Mac
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D600, 0x00010000);	// 30bpp RGB/YCbCr444,
	rtd_outl(0xb802D604, 0x01040104);	// 1-Pixel Mode, 4-Lane out, 1-section, 4-byte mode,
	rtd_outl(0xb802D608, 0x00000000);	// FSBP Ctrl Data,
	rtd_outl(0xb802D610, 0x01000000);	// VBy1 disable, PLL lclk not stable, transfer disable,
	rtd_outl(0xb802D628, 0x00040898);	// VBy1 FIFO Force reset in vertical blank,
	rtd_outl(0xb802D648, 0x00000000);	// VBy1 use external pin (LOCKN, HTPDN),
	rtd_outl(0xb802D64C, 0x00000000);	// VBy1 MSB/LSB Not Swap, Lane Not Swap,
	rtd_outl(0xb802D650, 0x00000000);	// Normal VBy1,
	rtd_outl(0xb802D610, 0xE1000000);	// VBy1 enable, PLL lclk stable, transfer enable,

	//---------------------------------------------------------------------------------------------------------------------------------
	//VBy1 TXPHY initial Flow (will ECO)
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_maskl(0xb8000C54,0xBFFFFFFF,0x00000000);	// TXPHY is LVDS/mLVDS/EPI Mode
	rtd_maskl(0xb8000C78,0x7FFFFFFF,0x00000000);	// TXPHY totally disable (expect LDO)
	rtd_maskl(0xb802D104,0x3FFFFFFF,0x00000000);	// PIF_Clock = Dclk/1
	rtd_maskl(0xb8000C0C,0xFC03FFFF,0x000C0000);	// TXPHY PLL DIV = 5
	rtd_outl(0xb8000198, 0x80000022);		// lane_clk = (dclk*5*M/N)/5 = (dclk*5*4byte/4lane)/5 = dclk
	rtd_maskl(0xb8000C78,0x7FFFFFFF,0x80000000);	// TXPHY totally enable
	udelay(1000000);
	rtd_maskl(0xb8000C54,0xBFFFFFFF,0x40000000);	// TXPHY is Vby1 Mode

	//---------------------------------------------------------------------------------------------------------------------------------
	//LOCKN, HPTDN Pin share
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_maskl(0xb80008BC,0x003FFFFF,0xAD400000);	// LVDS A-Port E Pair PinShare (P=VBY1_HTPD, N=VBY1_LOCK), src1
	rtd_maskl(0xb8000C20,0x003FFFFF,0x00000000);	// P0 E-Pair TTLI Mode
	rtd_maskl(0xb8000904,0xFFFF11FF,0x00002200);	// VBY1_HTPD & VBY1_LOCK use src1

}

void panel_dpg_enable(void) // uzu color bar
{
	UINT32 width;
	UINT32 height;
	
	rtd_outl(0xb8029000, 0x00000031);	// DPG Color Bar

	width = (default_panel_parameter.iCONFIG_DISP_ACT_END_HPOS - default_panel_parameter.iCONFIG_DISP_ACT_STA_HPOS);
	height = (default_panel_parameter.iCONFIG_DISP_ACT_END_VPOS - default_panel_parameter.iCONFIG_DISP_ACT_STA_VPOS);
		
	rtd_outl(0xb8029074, (width/8)-1);	// DPG Color Width
	rtd_outl(0xb8029028, (((width&0xffff)<<16)|(height&0xffff)));	// Input Size

	// clear dtg & mtg force bg
	rtd_clearbits(PPOVERLAY_DISPLAY_TIMING_CTRL1_VADDR, _BIT18);
	rtd_clearbits(PPOVERLAY_MAIN_DISPLAY_CONTROL_RSV_VADDR, _BIT1);

}


#if 0 //ben mark unused code
void lvds_2k1k_120_4ports_script(void)
{
//#if defined(LVDS_PANEL_MILLET3_2K1K_120)
	//dpll
	rtd_outl(0xb8000190, 0x0210142A);	// M = 35, N = 3
	rtd_outl(0xb8000194, 0x01720042);	// DIV = 1 , DPLL power on
	rtd_outl(0xb8000300, 0x07500001);	// OFFSET = 1872, DPLL_CLK = 297MHz
	rtd_outl(0xb8000300, 0x07500005);	// Load in
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
	//rtd_outl(0xb800DA40, 0x03000202);	// HDMI Power Enable
	printf("========= lvds_2k1k_120_4ports_script : LVDS/mini-LVDS TX PHY ==========\n");

//#endif
}
#endif

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

#if 0 //ben marked unused code
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
#endif

void LG_ART5_EPI_PANEL_Script()
{
	printf("LG_ART5_EPI_PANEL_Script\n");

	rtd_outl(0xb8000190, 0x02101216);		// DPLL M, N, RS=28K, Ip=2.5uA
	rtd_maskl(0xb8000194,0xFFCFCFFE,0x00300001);	// DPLL DIV_A/1
	rtd_maskl(0xb8028294,0xFFFFFFFC,0x00000000);	// DPLL DIV_D/1
	rtd_maskl(0xb8000300,0xF000FFFA,0x07500001);	// DPLL OFFSET
	rtd_maskl(0xb8000300,0xF000FFFA,0x07500005);	// DPLL OFFSET Load in

	rtd_outl(0xb8029000, 0x00000031);	// DPG Color Bar
	rtd_outl(0xb8029074, 0x000000EF);	// DPG Color Width
	rtd_outl(0xb8029028, 0x07800438);	// Input Size

	rtd_outl(0xb8028000, 0x01000000);	// Free Run Mode
	rtd_outl(0xb8028008, 0x0000000F);	// Hsync width
	rtd_outl(0xb802800C, 0x08970897);	// DH_total
	rtd_outl(0xb8028010, 0x00000005);	// DV_sync width
	rtd_outl(0xb8028014, 0x00000464);	// DV_total
	rtd_outl(0xb8028018, 0x008C080C);	// DH_den_sta, DH_den_end
	rtd_outl(0xb802801C, 0x0016044E);	// DV_den_sta, DV_den_end		
	rtd_outl(0xb8028024, 0x000000FF);	// Display Background Color
	rtd_outl(0xb8028028, 0x00000002);	// Disable Buffer

	rtd_outl(0xb8028100, 0x00000001);	// Main Display enable
	rtd_outl(0xb8028108, 0x0CD40000);	// Main Border Color
	rtd_outl(0xb802810C, 0x00000000);	// Main Background Color
	rtd_outl(0xb8028110, 0x00000780);	// Main DEN_H_str,Main DEN_H_end
	rtd_outl(0xb8028114, 0x00000438);	// Main DEN_V_str,Main DEN_V_end
	rtd_outl(0xb8028118, 0x00000780);	// Main Background_H_str,Main Background_H_end
	rtd_outl(0xb802811C, 0x00000438);	// Main Background_V_str,Main Background_V_end
	rtd_outl(0xb8028120, 0x00000780);	// Main Active_H_str,Main Active_H_end
	rtd_outl(0xb8028124, 0x00000438);	// Main Active_V_str,Main Active_V_end


	//epi mac v14
	// EPI MAC-layer configuration

	rtd_outl(0xB802D500,0x00000015); // CTR_Start=0x15,CTR_Start_dummy=0x0,P/N no swap. 

	rtd_outl(0xB802D504,0x00000000); // Lane0: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D508,0x00000000); // Lane1: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D50c,0x00000000); // Lane2: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D510,0x00000000); // Lane3: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D514,0x00000000); // Lane4: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D518,0x00000000); // Lane5: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D51c,0x00000000); // Lane6: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 
	rtd_outl(0xB802D520,0x00000000); // Lane7: SOE for FSM use, depends on PORCH num. (ex:2200-1920=280) 

	// NEW
	rtd_outl(0xB802D524,0x0000db09); // Lane0: SOE for LGD L7 use, T2=222(bit[17:8]=219=0xDB), T1=13(bit[7:0]=9=0x9)  
	rtd_outl(0xB802D528,0x0000d907); // Lane1: SOE for LGD L6 use, T2=220(bit[17:8]=217=0xD9), T1=11(bit[7:0]=7=0x7) 
	rtd_outl(0xB802D52c,0x0000d705); // Lane2: SOE for LGD L5 use, T2=218(bit[17:8]=215=0xD7), T1= 9(bit[7:0]=5=0x5)
	rtd_outl(0xB802D530,0x0000d503); // Lane3: SOE for LGD L4 use, T2=216(bit[17:8]=213=0xD5), T1= 7(bit[7:0]=3=0x3)
	rtd_outl(0xB802D534,0x0000d402); // Lane4: SOE for LGD L3 use, T2=215(bit[17:8]=212=0xD4), T1= 6(bit[7:0]=2=0x2)
	rtd_outl(0xB802D538,0x0000d604); // Lane5: SOE for LGD L2 use, T2=217(bit[17:8]=214=0xD6), T1= 8(bit[7:0]=4=0x4)
	rtd_outl(0xB802D53c,0x0000d706); // Lane6: SOE for LGD L1 use, T2=219(bit[17:8]=215=0xD7), T1=10(bit[7:0]=6=0x6)
	rtd_outl(0xB802D540,0x0000da08); // Lane7: SOE for LGD L0 use, T2=221(bit[17:8]=218=0xDA), T1=12(bit[7:0]=8=0x8)

	rtd_outl(0xB802D544,0x00000410); // Lane0: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D548,0x00000410); // Lane1: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D54c,0x00000C10); // Lane2: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D550,0x00000C10); // Lane3: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D554,0x00000C10); // Lane4: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D558,0x00000C10); // Lane5: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D55c,0x00000410); // Lane6: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D560,0x00000410); // Lane7: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	
	rtd_outl(0xB802D564,0xFFFFFFE3); // CTR2:Select CTR2(c0 ~c5 ) source. From Tcon or Register(all "1"). (c0,POL from tcon3)
	rtd_outl(0xB802D568,0xFFF4FFFF); // CTR2:Select CTR2(c6 ~c11) source. From Tcon or Register(all "1"). (c9,GSP from tcon9)
	rtd_outl(0xB802D56c,0xFFFFFFFF); // CTR2:Select CTR2(c12~c17) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D570,0xFFFFFFFF); // CTR2:Select CTR2(c18~c23) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D574,0xFFFFFFFF); // CTR2:Select CTR2(c24~c29) source. From Tcon or Register(all "1").
	rtd_outl(0xB802D578,0x00000000); // CTR3: reserved for future. bit30=0 to disable.
	rtd_outl(0xB802D57c,0x0000002A); // Data_Start=0x2A,Data_Start_dummy=0x0.
	rtd_outl(0xB802D580,0x08000000); // Bit31=0=No_data_in.(Bit30=1 to reset), Bit29=0=PRBS7_OFF, 8bit
	rtd_outl(0xB802D584,0xC0000000); // EPI mode setting, bit[1]=0=lock_source_from_hw.
	rtd_outl(0xB802D588,0x00000C40);   // Pin_map=00=table(1)=v14,8 lane, v13 SOE

	//Epi fhd 1seg 2port
////////////////////////////////
	//---------------------------------------------------------------------------------------------------------------------------------
	//DCLK DIV
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8028294, 0x00000001);	// DCLK = DPLL_Clock div 1 for FHD120hz/8lane (DTG spec) 
	//rtd_maskl(0xb8000018,0xFC7FFFFF,0x00800000); // bit25=0=from normal path, bit[24:23]=01=divide by 4,(8 lane mode), (CRT spec)
	rtd_maskl(0xb8000018,0xFC7FFFFF,0x00000000); // bit25=0=from normal path, bit[24:23]=01=divide by 4,(8 lane mode), (CRT spec)
	
	//---------------------------------------------------------------------------------------------------------------------------------
	//SFG, 1 Pixel Mode, DH_ST_END = 0x008C080C, DTG_HS_Width = 16, DTG_VS_Width = 6
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D100, 0x000008C0);	// 10-bit Mode, Dout Enable, delay chain inverse + 0ns
	rtd_outl(0xb802D104, 0x0000FFFF);	// PIF_Clock = Dclk/1, Force to background enable
	rtd_outl(0xb802D108, 0x01234567);	// Port A~H mapping
	rtd_outl(0xb802D12C, 0x88114400);	// line 4n/4n+2 not shift sub-Pixel, line_end add dummy sub-pixel = glast
						// line 4n+1/4n+3 shift 1 sub-Pixel, line_st add dummy sub-pixel = g0
	rtd_outl(0xb802D130, 0x00000000);	// SEG 0, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D134, 0x00000000);	// SEG 0, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D138, 0x00000000);	// SEG 1, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D13C, 0x00000000);	// SEG 1, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D140, 0x00000000);	// SEG 2, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D144, 0x00000000);	// SEG 2, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D148, 0x00000000);	// SEG 3, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D14C, 0x00000000);	// SEG 3, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D150, 0x00000000);	// SEG 4, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D154, 0x00000000);	// SEG 4, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D158, 0x00000000);	// SEG 5, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D15C, 0x00000000);	// SEG 5, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D160, 0x00000000);	// SEG 6, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D164, 0x00000000);	// SEG 6, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D168, 0x00000000);	// SEG 7, Front/End, 4n+0/4n+1 Line, no dummy pixel
	rtd_outl(0xb802D16C, 0x00000000);	// SEG 7, Front/End, 4n+2/4n+3 Line, no dummy pixel
	rtd_outl(0xb802D170, 0x00000055);	// Normal Data Mapping, 6-SEG, 6-Port, No H-Flip
	rtd_outl(0xb802D174, 0x00000140);	//start address of SEG 0/1 , residue of SEG 0/1 
	rtd_outl(0xb802D178, 0x028003C0);	//start address of SEG 2/3 , residue of SEG 2/3 
	rtd_outl(0xb802D17C, 0x05000640);	//start address of SEG 4/5 , residue of SEG 4/5 
	rtd_outl(0xb802D180, 0x00000000);	//start address of SEG 6/7 , residue of SEG 6/7
	rtd_outl(0xb802D188, 0x40000000);	// Disable ByPass Mode, Auto config mode enable
	rtd_outl(0xb802D18C, 0x000F088B);	// HS_Width = 16 dclk; hsync_delay = DH_Total  - 13 = 2187;
	rtd_outl(0xb802D190, 0x00050000);	// VS_ST = 0; VS_END = 6;
	rtd_outl(0xb802D194, 0x008C0086);	// sfg_dh_den_sta = DH_DEN_ST = 140;
						// req_st = hs_back_porch - 6 = 134;
	rtd_outl(0xb802D198, 0x00000000);	// Hs_distance for DRD Mode (no USE); Seg0 Not Flip;
	rtd_outl(0xb802D19C, 0x07800000);	// final_line_length = 1920, hsync_threshold = 0
	rtd_outl(0xb802D1A0, 0x00000000);	// Residue_pix_div_12_split_mode &
						// Final_addr_split_mode for Tri-gate Mode (no USE)
	rtd_outl(0xb802D1A4, 0x0008C891);	// hs_den_io_dist = req_st + 6 = 140; (for EPI)
						// hs_io_dist = hs_delay + 6 = 2187 + 6 = 2193; (for EPI)
	rtd_outl(0xb802D1B8, 0x00009999);	// Line start = B_1st, Line end = R_last, data not inverse,
	rtd_outl(0xb802D1EC, 0x00000000);	// SEG 0/1, middle, no dummy pixel
	rtd_outl(0xb802D1F0, 0x00000000);	// SEG 2/3, middle, no dummy pixel
	rtd_outl(0xb802D1F4, 0x00000000);	// SEG 4/5, middle, no dummy pixel
	rtd_outl(0xb802D1F8, 0x00000000);	// SEG 6/7, middle, no dummy pixel
	rtd_outl(0xb802D1FC, 0x00000000);	// Active_pixel_RGB & Last_ext_pixel for DRD
	
	//---------------------------------------------------------------------------------------------------------------------------------
	//PIF
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb802D000, 0x00000008);	// PIF EPI Mode, bit[3:2]=10=EPI mode. (Display_Panel_Interface spec)
	rtd_outl(0xb802D010, 0x00000000);	// LVDS Port Disable
///////////////////////////////
	//---------------------------------------------------------------------------------------------------------------------------------
	//LVDS Pin Share
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb80008B8, 0x00000000);	// LVDS A-Port F/G/H Pair PinShare
	rtd_outl(0xb80008BC, 0x00000000);	// LVDS A-Port C/D/E Pair PinShare
	rtd_outl(0xb80008C0, 0x00000000);	// LVDS A-Port A/B, LVDS B-Port G Pair PinShare
	rtd_outl(0xb80008C4, 0x00000000);	// LVDS B-Port D/E/F Pair PinShare
	rtd_outl(0xb80008C8, 0x00000000);	// LVDS B-Port A/B/C Pair PinShare

	//---------------------------------------------------------------------------------------------------------------------------------
	//LVDS/mini-LVDS/EPI/VBy1 TXPHY (EPI mode)
	//---------------------------------------------------------------------------------------------------------------------------------
	rtd_outl(0xb8000C00, 0x03001810);	// PI_A1 = Phase0, PI_A2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C04, 0x03001810);	// PI_B1 = Phase0, PI_B2 = Phase0, CK7X = 1X Current, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C08, 0x03040000);	// PI_AB = Phase0, CK7X = 1X Current, CK5X Duty Adjust Disable, PI_Clock = 300~600MHz,
	rtd_outl(0xb8000C0C, 0x00313730);	// Choose legacy charge-pump, DIV248 = 1, VCO = 74.25*7*DIV248 = 1.0395GHz,
						// Small Kvco, CK1X Not Inverse, PLL_VCO = 2V,
						// Icp = 12.5uA, Cp = 9.5pF, Rs = 12Kohm,
						// PI_A Disble, PI_B Disable ==> PI_AB Disble
	rtd_outl(0xb8000C10, 0x6C040000);	// P0 A-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C14, 0x6C040000);	// P0 B-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C18, 0x6C040000);	// P0 C-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C1C, 0x6C040000);	// P0 D-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C20, 0x6C040000);	// P0 E-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C24, 0x6C040000);	// P0 F-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C28, 0x6C040000);	// P0 G-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C2C, 0x6C040000);	// P0 H-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C30, 0x07f80000);	// P0 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P0 Double Driving enable,
	rtd_outl(0xb8000C34, 0x6C040000);	// P1 A-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C38, 0x6C040000);	// P1 B-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C3C, 0x6C040000);	// P1 C-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C40, 0x6C040000);	// P1 D-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C44, 0x6C040000);	// P1 E-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C48, 0x6C040000);	// P1 F-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C4C, 0x6C040000);	// P1 G-Pair EPI, SR Disable, internal resistor 100ohm,
	rtd_outl(0xb8000C50, 0x07f00000);	// P1 Not Adjudt CK7X Delay, CK7X Not Inverse, PI Not Lag 0.5UI,
						// P1 Double Driving enable,
	rtd_outl(0xb8000C54, 0x08D0D000);	// ISOURCE = IBHX, Select LVDS/mLVDS/EPI TXPHY, 
						// LDO_CML Enable & 2V, LDO_DPLL/LVDSPLL Enable & 1.05V,
						// Swing = 3mA. VCM = 0.9V,
	rtd_outl(0xb8000C58, 0x1fe01fe0);	// P0 Pre-emphasis disable, internal resistor enable, TTL 2mA,
						// P0 Not Adjudt CK1X Delay, CML 2.4mA (PLL>1.2GHz),
	rtd_outl(0xb8000C5C, 0xFF000000);	// P0 CML Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C60, 0x1fc07f00);	// P1 Pre-emphasis disable, internal resistor enable, TTL 2mA,
						// P1 Not Adjudt CK1X Delay, CML 2.4mA (PLL>1.2GHz),
	rtd_outl(0xb8000C64, 0xFF000000);	// P1 CML Mode, SR 1-buffer delay,
	rtd_outl(0xb8000C78, 0x80000000);	// Port Power Enable for non-Vby1-Mode (Lane power off)	

	//TCON
	rtd_part_outl(0xb80008C4,31,27,0x3);//Tcon16 (GCLK)
	rtd_part_outl(0xb8000C48,31,29,0x2);//Tcon16 pin share enable

	rtd_part_outl(0xb80008C4,6,2,0x3);//Tcon1 (GST)
	rtd_part_outl(0xb8000C40,28,26,0x2);//Tcon1 pin share enable

	rtd_part_outl(0xb80008C8,16,12,0x3);//Tcon5 (E/O)
	rtd_part_outl(0xb8000C38,28,26,0x2);//Tcon5 pin share enable

	rtd_part_outl(0xb80008C8,6,2,0x3);//Tcon7 (MCLK)
	rtd_part_outl(0xb8000C34,28,26,0x2);//Tcon7 pin share enable
	/////////////////////////////////////////////////////////////// which LVDS PAD would be set GPIO port ?

	rtd_part_outl(0xb80008c8,11,7,0x1F);// set reverse signal became to GPO
	rtd_part_outl(0xb8000c34,31,29,0x2);// this GPO was setted for Siruous use
	rtd_part_outl(0xb801b108,15,15,0x1);


	/////////// set Tcon3 initial value for test signal 

	rtd_outl(0xb802d704,0x00200000);//(modify)
	rtd_outl(0xb802dB0C,0x00000001);//(modify)

	///////////////////////// set Tcon5 and Tcon4 become E/O

	//rtd_outl(0xb802d7b4,0x00000180); //set Tcon5 enable and set frame cross mode (modify)
	//rtd_outl(0xb802d7b0,0x0016044e); //set Vstart Vend (modify)
	//rtd_outl(0xb802d7ac,0x00990819); // set Hstart Hend (modify)

	rtd_outl(0xb802d7b4,0x00000480); //set Tcon5 enable and set frame cross mode (modify)
	rtd_outl(0xb802d7b0,0x045B045B); //set Vstart Vend (modify)
	rtd_outl(0xb802d7ac,0x00990099); //set Hstart Hend (modify)
	rtd_outl(0xb802d7bc,0x0000007E);// set frame period=126 (modify)

	rtd_outl(0xb802d794,0x00000480); // set Tcon4 enable frame cross mode
	rtd_outl(0xb802d790,0x045B045B); // set Vstart Vend
	rtd_outl(0xb802d78C,0x01040104); // set Hstart Hend
	rtd_outl(0xb802d79C,0x0000007E);// set frame period=126

	rtd_outl(0xb802d7b4,0x00000483); // set Tcon5=Tcon5 Xor Tcon4
	rtd_outl(0xb802db0c,0x00000000);//Tcon IP disable
	rtd_outl(0xb802db0c,0x00000001);// Tcon IP enable
	/////////////////////////////

	////////////set Tcon0 Tcon1 become GST
	rtd_outl(0xb802d714,0x00000180);//set Tcon0 enable and across line1 mode 
	rtd_outl(0xb802d710,0x00080011);//set Tcon0 Vstart Vend
	rtd_outl(0xb802d70c,0x004D00A5);//set Tcon0 Hstart Hend

	rtd_outl(0xb802d734,0x00000183);//set Tcon1 enable and across line1 mode
	rtd_outl(0xb802d730,0x04530457);//set Tcon1 Vstart and Vend
	rtd_outl(0xb802d72c,0x08190819);//set Tcon1 Hstart Hend 
	/////////////////////////////////////////////////// 

	///////////// set Tcon7 MCLK

	rtd_outl(0xb802d7f4,0x00000080);//set Tcon7 enable
	rtd_outl(0xb802d7f0,0x00140450);//VStart and Vend  //	(0x00150452)
	rtd_outl(0xb802d7ec,0x045005B0);//HStart and Hend  // be careful 0x04d006a0
	//////////////////////////////

	//////////////////////////////////// set Tcon16,Tcon15,Tcon14 became to GCLK
	
	//rtd_outl(0xb802d8e0,0x00000280); // enable Tcon14 and set across line2 mode
	//rtd_outl(0xb802d8dc,0x00110450); // set Vstart Vend/////change 44F
	//rtd_outl(0xb802d8d8,0x089304C0); // set Hstart Hend//0x0380001C
	
	//rtd_outl(0xb802d900,0x00000180); //enable Tcon15 and set across line1 mode
	//rtd_outl(0xb802d8fc,0x00110014); // set Vstart Vend
	//rtd_outl(0xb802d8f8,0x057000E1); //set Hstart Hend
	//rtd_outl(0xb802d900,0x000001C0); // set Tcon15 invertion
	
	//rtd_outl(0xb802d900,0x000001C1);// Tcon15 AND Tcon14
	
	//rtd_outl(0xb802d920,0x00000182);// set Tcon16 enable and across line1 mode
	//rtd_outl(0xb802d91C,0x044F0457);//set Tcon16 Vstart Vend
	//rtd_outl(0xb802d918,0x08190819);// set Tcon16 Hstart Hend
	
	rtd_outl(0xb802d900,0x00000180);// set Tcon15 across line1 mode
	rtd_outl(0xb802d8FC,0x044D0457);// set Tcon15 Vstart Vend
	rtd_outl(0xb802d8F8,0x00990819);// set Tcon15 Hstart Hend
	
	rtd_outl(0xb802d920,0x00000082);// set Tcon16 normal mode
	rtd_outl(0xb802d91C,0x0012044D);// set Tcon16 Vstart Vend
	rtd_outl(0xb802d918,0x01000400);// set Tcon16 Hstart Hend
	
	//////////////////////////////////set Tcon9 became GPL
	rtd_outl(0xb802d834,0x00000180); //set Tcon9 become to across line1 mode 
	rtd_outl(0xb802d830,0x00140018); //set Vstart Vend
	rtd_outl(0xb802d82c,0x00010750); //set Hstart Hend
	//////////////////////////////////set Tcon2 became to POL
	rtd_outl(0xb802d754,0x00000380); //set Tcon2 become to frame across mode  // be careful
	rtd_outl(0xb802d750,0x0015010E); //set Vstart Vend
	rtd_outl(0xb802d74c,0x00990120); //set Hstart Hend
	rtd_outl(0xb802d758,0x00040002); //set number of line cross period

	rtd_outl(0xb802d76C,0x00070007);//set Tcon3 Hstart Hend
	rtd_outl(0xb802d770,0x00010001);//set Tcon3 Vstart Vend
	rtd_outl(0xb802d774,0x00000483);//set Tcon3 which across 
	rtd_outl(0xb802d77c,0x00000000);
	
	rtd_outl(0xb802d170,0x00000155);
		rtd_part_outl(0xb8028014,12,0,0x544);
	rtd_part_outl(0xb802800c,28,16,0x897);
	rtd_part_outl(0xb802800C,12,0,0x897);


	//panel config
	// 60hz
	rtd_outl(0xb8028294, 0x00000001);	// DCLK = DPLL_Clock div 2 for FHD120hz (DTG spec) 
	rtd_outl(0xb8000C0C, 0x00313730);	// Choose legacy charge-pump, DIV248 = 1, VCO = 74.25*7*DIV248 = 1.0395GHz,
		
	rtd_maskl(0xb8000018,0xFC7FFFFF,0x00000000); // bit25=0=from normal path, bit[24:23]=00=divide by 3,(6 lane mode), (CRT spec)
	
	rtd_outl(0xB802D584,0xC0000006); // EPI mode setting, bit[1]=1=lock_source_from_reg, bit[2]=lock_value=1.
	
	rtd_outl(0xB802D524,0x00011506); // Lane0: SOE for LGD L7 use, T2=222(bit[17:8]=219=0xDB), T1=13(bit[7:0]=9=0x9)  
	rtd_outl(0xB802D528,0x00011506); // Lane1: SOE for LGD L6 use, T2=220(bit[17:8]=217=0xD9), T1=11(bit[7:0]=7=0x7) 
	rtd_outl(0xB802D52c,0x00011506); // Lane2: SOE for LGD L5 use, T2=218(bit[17:8]=215=0xD7), T1= 9(bit[7:0]=5=0x5)
	rtd_outl(0xB802D530,0x00011506); // Lane3: SOE for LGD L4 use, T2=216(bit[17:8]=213=0xD5), T1= 7(bit[7:0]=3=0x3)
	rtd_outl(0xB802D534,0x00011506); // Lane4: SOE for LGD L3 use, T2=215(bit[17:8]=212=0xD4), T1= 6(bit[7:0]=2=0x2)
	rtd_outl(0xB802D538,0x00011506); // Lane5: SOE for LGD L2 use, T2=217(bit[17:8]=214=0xD6), T1= 8(bit[7:0]=4=0x4)
	rtd_outl(0xB802D53c,0x00011506); // Lane6: SOE for LGD L1 use, T2=219(bit[17:8]=215=0xD7), T1=10(bit[7:0]=6=0x6)
	rtd_outl(0xB802D540,0x00011506); // Lane7: SOE for LGD L0 use, T2=221(bit[17:8]=218=0xDA), T1=12(bit[7:0]=8=0x8)
	
	rtd_outl(0xB802D544,0x00000090); // Lane0: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D548,0x00000090); // Lane1: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D54c,0x00000090); // Lane2: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D550,0x00000090); // Lane3: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D554,0x00000090); // Lane4: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D558,0x00000090); // Lane5: CTR2:Register value for CTR2.(LTD2=1, GMAEN=1, others:0)
	rtd_outl(0xB802D55c,0x00000090); // Lane6: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)
	rtd_outl(0xB802D560,0x00000090); // Lane7: CTR2:Register value for CTR2.(LTD2=1, GMAEN=0, others:0)

	// Lane Power Enable for non-Vby1-Mode
	rtd_outl(0xb8000C78, 0x9F800000);	// Lane Power Enable for non-Vby1-Mode
	
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


void panel_reconfig_fhd_param()
{
	default_panel_parameter.iCONFIG_DISP_VERTICAL_TOTAL = 1125; 
	default_panel_parameter.iCONFIG_DISP_HORIZONTAL_TOTAL = 2200;
	default_panel_parameter.iCONFIG_DISP_DEN_STA_HPOS= 140; 
	default_panel_parameter.iCONFIG_DISP_DEN_END_HPOS = 2060; 
	default_panel_parameter.iCONFIG_DISP_DEN_STA_VPOS= 16; 
	default_panel_parameter.iCONFIG_DISP_DEN_END_VPOS = 1096; 
	default_panel_parameter.iCONFIG_DISP_ACT_STA_HPOS= 0; 
	default_panel_parameter.iCONFIG_DISP_ACT_END_HPOS= 1920; 
	default_panel_parameter.iCONFIG_DISP_ACT_STA_VPOS= 0; 
	default_panel_parameter.iCONFIG_DISP_ACT_END_VPOS= 1080; 
	default_panel_parameter.iCONFIG_DISP_HSYNC_LASTLINE= 2200; 
}


void panel_init_1st(void)
{
	if (boot_mode == BOOT_CONSOLE_MODE) {
		printf("skip panel_init_1st, mode=%d\n", boot_mode);
		return;
	}

	if (panel_init_1st_is_done)
		return;
	panel_init_1st_is_done = 1;

	printf("panel_init_1st\n");

	if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_M4_Default_2k1k)
	{
		printf("reconfig dtg as fhd\n");
		panel_reconfig_fhd_param();
	}

	//printf("iCONFIG_BACKLIGHT_PWM_FREQ=%d\n", (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_FREQ);
	//printf("iCONFIG_BACKLIGHT_PWM_DUTY=%d\n", (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_DUTY);
	//printf("iPANEL_TO_LVDS_ON_ms=%d\n", (&default_panel_parameter)->iPANEL_TO_LVDS_ON_ms);
	//printf("iLVDS_TO_LIGHT_ON_ms=%d\n", (&default_panel_parameter)->iLVDS_TO_LIGHT_ON_ms);
#if 0 //frank@0516 move to Post_CRT_arbitration //frank@0117 open D domain related clock and reset
	//-------- PLL DISP -------------------------------------------------
	rtd_outl(0xb8000190,0x02601336);	// max 540, set 360MHz
	rtd_outl(0xb8000194,0x11020001);	// DPLL power on
	rtd_outl(0xb8000194,0x11020043);	// release DPLL reset

	 //enable vodma pll
	 rtd_outl(0xb8000160,0x00222613);  // max 450, set 27*12 = 324MHz
	 rtd_outl(0xb8000164,0x00000005); // PLLVODMA power on
	 rtd_outl(0xb8000164,0x00000007); // release PLLVODMA reset
	 mdelay(1); //ScalerTimer_DelayXms(1); // at least > 5us
	 rtd_outl(0xb8000164,0x00000003); // PLLVODMA output enable




	//-------- Module Clock & Reset Enable ---------
	rtd_maskl(0xb8000014, 0x1effffc7, 0xE1000038);// enable TVSB1~3, I/M/D domain clock
	rtd_maskl(0xb8000014, 0x1effffc7, 0x00000000);// disable TVSB1~3, I/M/D domain clock
	rtd_maskl(0xb8000008, 0xffff8fe1, 0x00000000);// hold TVSB1~3, I/M/D domain reset
	rtd_maskl(0xb8000008, 0xffff8fe1, 0x0000701e);// release TVSB1~3, I/M/D domain reset
	mdelay(1);
	rtd_maskl(0xb8000014, 0x1effffe7, 0xE1000038);// enable TVSB1~3, I/M/D domain clock

	printf("0xb8000014=%x\n",rtd_inl(0xb8000014));
	printf("0xb8000008=%x\n",rtd_inl(0xb8000008));

	//new pre-arbitration
	rtd_maskl(0xb8008004, 0xfeffffff, 0x01000000);
	//DCU1 Arbitration
	rtd_outl(0xb8008028, 0x8e620080);		// pre-arb merge, use nertd_outl(setting for KONKA USB playback issue, increase DC_PHY utility, trade-off realtime of priority, suggest by SYChang
	rtd_outl(0xb8008080, 0x00000000);		// TVSB2
	rtd_outl(0xb8008084, 0x00100020);		// TVSB1
	rtd_outl(0xb8008088, 0x00100020);		// SB1
	rtd_outl(0xb800808c, 0x00100040);		// SB2
	rtd_outl(0xb8008090, 0x00180040);		// SB3
	rtd_outl(0xb8008094, 0x00100020);		// VE
	rtd_outl(0xb8008098, 0x00100020);		// TVSB3
	rtd_outl(0xb800809c, 0x00180020);		// GPU1
	rtd_outl(0xb80080a0, 0x00000020);		// DTV Demod
	rtd_outl(0xb80080a4, 0x00100020);		// VE2
	rtd_outl(0xb80080a8, 0x00180020);		// GPU2
	rtd_outl(0xb80080b0, 0x07ff0007);

	//TVSB2_DCU1
	rtd_outl(0xb8038100, 0x00000007);
	rtd_outl(0xb8038108, 0x00000080);		// DIMW
	rtd_outl(0xb803810c, 0x00000070);		// DIMR
	rtd_outl(0xb8038110, 0x00000080);		// CAPM
	rtd_outl(0xb8038114, 0x00000080);		// DISPM
	rtd_outl(0xb8038118, 0x00000080);		// ODWR
	rtd_outl(0xb803811c, 0x00000080);		// ODRD
	rtd_outl(0xb8038120, 0x00000080);		// VO1_Y
	rtd_outl(0xb8038124, 0x00000080);		// VO1_C
	rtd_outl(0xb8038128, 0x00000080);		// OSD1
	rtd_outl(0xb803812c, 0x00000080);		// SUBT
	rtd_outl(0xb8038130, 0x00000080);		// IHDMI
	rtd_outl(0xb8038134, 0x00000080);		// VO2_Y
	rtd_outl(0xb8038138, 0x00000080);		// VO2_C
	rtd_outl(0xb803813c, 0x00000080);		// CAPS
	rtd_outl(0xb8038140, 0x00000080);		// DISPS
	rtd_outl(0xb8038144, 0x00000080);		// OSD2

	//Close GPU CTI mode
	rtd_maskl(0xb800802c, 0xfffffffe, 0x00000001);
#endif


	if(Get_PANEL_TYPE_IS_IWATT_LOCAL_DIMMING()){
		printf("\n $$$$$$$$ This is Local Dimming Panel !!! \n");
#ifdef CONFIG_REALTEK_LOCAL_DIMMING_INTERFACE
		ld_Init();
#endif
	}

#if defined(CONFIG_BOARD_298X_TV003_QFP176_V2_NAND)
#else
	rtd_maskl(0xB80008BC, 0xffc00fff, 0x003ff000);
	rtd_maskl(0xB80008C4, 0xfffff003, 0x00000ffc);
	rtd_maskl(0xB801b108, 0xfffff9ff, 0x00000600);
	rtd_maskl(0xB801b108, 0xfffff9ff, 0x00000600);
	rtd_maskl(0xB801b104, 0x9fffffff, 0x60000000);
	rtd_outl(0xb8000c78,0xffff0000);
	IO_Set(PIN_LVDS_ON_OFF, 1);
#endif

#if (defined CONFIG_PANEL_CMI_V390HJ1_PEL_OPENCELL)
	IO_Set(PIN_PANEL_OE1_ON_OFF, 1);
	IO_Set(PIN_PANEL_OE2_ON_OFF, 1);
	IO_Set(PIN_PANEL_VFLK_ON_OFF, 1);
#endif

#ifdef CONFIG_PANEL_SHARP_60_MEMC
	panel_sharp_memc_init(0);
#else //#ifdef CONFIG_PANEL_SHARP_60_MEMC
#ifdef CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC
#else
	mdelay(((&default_panel_parameter)->iPANEL_TO_LVDS_ON_ms));
#endif
#endif //#ifdef CONFIG_PANEL_SHARP_60_MEMC

	// set Panel Display Timing Gen
	setPanelDataSetting(&default_panel_parameter);

#ifdef CONFIG_PANEL_SHARP_60_MEMC
	//panel_sharp_memc_init(1);
#endif //#ifdef CONFIG_PANEL_SHARP_60_MEMC

#if 0
	if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){

		panel_vby1_tx_phy();

	}
	else if(Get_PANEL_TYPE_IS_MILLET3_4K2K_SERIES()){
		printf("========= 4K2K Millet3 Series LVDS Panel ==========\n");
		lvds_2k1k_120_4ports_script();
		//frank@05232012 disable VBY1 power down
//		rtd_clearbits(0xb802d6d8, _BIT31);
//		rtd_clearbits(0xb802d6f8, _BIT31);
//		rtd_clearbits(0xb802d6d8, (_BIT30|_BIT1|_BIT0));
//		rtd_clearbits(0xb802d6f8, (_BIT30|_BIT1|_BIT0));
//		rtd_clearbits(0xb802d610, _BIT31);
 	}
	else if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_EPI_TYPE){
		printf("========= EPI TYPE Panel ==========\n");
		if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == P_EPI_LG_47_ART5){
			LG_ART5_EPI_PANEL_Script();
		}
		else{
			EPI_FHD_60HZ_Script();
		}
	}
	else{
#if 0 //frank@0114
 		//frank@05232012 disable LVDS TX PHY
		rtd_clearbits(0xb8000c50, (_BIT31|_BIT30|_BIT29));

		//frank@05232012 disable VBY1 power down
		rtd_clearbits(0xb802d6d8, _BIT31);
		rtd_clearbits(0xb802d6f8, _BIT31);
		rtd_clearbits(0xb802d6d8, (_BIT30|_BIT1|_BIT0));
		rtd_clearbits(0xb802d6f8, (_BIT30|_BIT1|_BIT0));
		rtd_clearbits(0xb802d610, _BIT31);
#endif
	}
	printf("======= PANEL_CUSTOM_INDEX: %x =======\n", default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX);


	#ifndef OPEN_CELL_PANEL

		if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){
			//LOCKN, HPTDN Pin share
			rtd_maskl(0xb80008BC,0x003FFFFF,0xAD400000);	// LVDS A-Port E Pair PinShare (P=VBY1_HTPD, N=VBY1_LOCK), src1
			rtd_maskl(0xb8000C20,0x003FFFFF,0x00000000);	// P0 E-Pair TTLI Mode
			rtd_maskl(0xb8000904,0xFFFF11FF,0x00002200);	// VBY1_HTPD & VBY1_LOCK use src1
		}else{
			//frank@0114 sync sirius hw setting
			rtd_maskl(0xb80008B8, 0xfffff003, 0x0);	// LVDS A-Port F Pair PinShare
			rtd_outl(0xb80008BC, 0x00000000);	// LVDS A-Port C/D/E Pair PinShare
			rtd_maskl(0xb80008C0, 0x00000ffc, 0x0);	// LVDS A-Port A/B,
		}

	#else
	Panel_Tcon_Init();
	#endif

	if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_EPI_TYPE){
		rtd_outl(0xb80008A0, 0xFFF33333);	// LVDS C Port Pin Share to Tcon
		rtd_outl(0xb80008A4, 0x33000000);	// LVDS C Port Pin Share to Tcon
		rtd_outl(0xb80008A8, 0x33FF0000);	// LVDS D Port Pin Share to Tcon
	}else if(default_panel_parameter.iCONFIG_PANEL_TYPE == P_VBY1_4K2K){

	}else{
		//frank@0114 sync sirius hw setting
		rtd_outl(0xb80008C4, 0x00000000);	// LVDS B-Port D/E/F Pair PinShare
		rtd_outl(0xb80008C8, 0x00000000);	// LVDS B-Port A/B/C Pair PinShare
	}
#endif
	panel_customized_setting();

#ifndef CONFIG_SYS_PANEL_DISABLE_PATTERN_GEN
	panel_dpg_enable();
#endif

	#if defined(LVDS_PN_SWAP)
	rtd_maskl(0xb802d000, 0xfffffbff, 0x00000000);  //LVDS PN Swap disable bit10=0
	printf("Do LVDS PN Swap\n");
	#endif //#if defined(LVDS_PN_SWAP)

	rtd_outl(0xb802810c, 0x0);
	//dump_register();

}

void pwm_pinshare_power_enable(void)
{
	//clken:1
	//rtd_part_outl(0xb800000c,0,0,1);//clken_misc[0]
	//rtd_part_outl(0xb800000c,6,6,1);//clk_en_iso_misc[6]
//		rtd_part_outl(0xb8000010,25,25,1);//clken_pwm[25]:1
//		rtd_part_outl(0xb8000014,12,12,1);//clken_padmux[12]
//		rtd_part_outl(0xb8000014,29,29,1);//clken_tvsb3[29]//mantis:55208
	rtd_maskl(0xb8000010, (~_BIT25), _BIT25);
	rtd_maskl(0xb8000014, (~_BIT12), _BIT12);
	rtd_maskl(0xb8000014, (~_BIT29), _BIT29);
	//rtd_part_outl(0xb8060040,3,3,1);//clken_iso_pwm[3]:1
	//rtd_part_outl(0xb8060040,2,2,1);//clken_iso_padmux[2]
	////rtd_part_outl(0xb8060040,1,1,1);//clken_iso_misc_off[1]
	//rtd_part_outl(0xb8060040,0,0,1);//clken_iso_misc[0]

	//clken:0
	//rtd_part_outl(0xb800000c,0,0,0);//clken_misc[0]
	//rtd_part_outl(0xb800000c,6,6,0);//clk_en_iso_misc[6]
//		rtd_part_outl(0xb8000010,25,25,0);//clken_pwm[25]:1
//		rtd_part_outl(0xb8000014,12,12,0);//clken_padmux[12]
//		rtd_part_outl(0xb8000014,29,29,0);//clken_tvsb3[29]//mantis:55208
	rtd_maskl(0xb8000010, (~_BIT25), 0);
	rtd_maskl(0xb8000014, (~_BIT12), 0);
	rtd_maskl(0xb8000014, (~_BIT29), 0);
	//rtd_part_outl(0xb8060040,3,3,0);//clken_iso_pwm[3]:1
	//rtd_part_outl(0xb8060040,2,2,0);//clken_iso_padmux[2]
	////rtd_part_outl(0xb8060040,1,1,0);//clken_iso_misc_off[1]
	//rtd_part_outl(0xb8060040,0,0,0);//clken_iso_misc[0]

	//RSTN:0
	//rtd_part_outl(0xb8000000,0,0,0); //rstn_misc[0]
//		rtd_part_outl(0xb8000008,14,14,0); //rstn_tvsb3[14]
	rtd_maskl(0xb8000008, (~_BIT14), 0);
	//mdelay(10);
	//rtd_part_outl(0xb8060030,3,3,0); //rstn_iso_pwm[3]
	////rtd_part_outl(0xb8060030,2,2,0);//rstn_iso_padmux[2]
	////rtd_part_outl(0xb8060030,1,1,0);//iso_misc_off[1]
	//rtd_part_outl(0xb8060030,0,0,0);//rstn_iso_misc[0]
	//!!halt!! rtd_part_outl(0xb8000004,13,13,0);//rstn_padmux[13]
	//!!halt!! rtd_part_outl(0xb8000004,7,7,0);//rstn_pwm[7]

	//RSTN:1
	//rtd_part_outl(0xb8000000,0,0,1); //rstn_misc[0]
//		rtd_part_outl(0xb8000008,14,14,1); //rstn_tvsb3[14]
	rtd_maskl(0xb8000008, (~_BIT14), _BIT14);
	//rtd_part_outl(0xb8060030,3,3,1); //rstn_iso_pwm[3]
	////rtd_part_outl(0xb8060030,2,2,1);//rstn_iso_padmux[2]
	////rtd_part_outl(0xb8060030,1,1,1);//iso_misc_off[1]
	//rtd_part_outl(0xb8060030,0,0,1);//rstn_iso_misc[0]
//		rtd_part_outl(0xb8000004,13,13,1);//rstn_padmux[13]
//		rtd_part_outl(0xb8000004,7,7,1);//rstn_pwm[7]
	rtd_maskl(0xb8000004, (~_BIT13), _BIT13);
	rtd_maskl(0xb8000004, (~_BIT7), _BIT7);

	//clken:1
	//rtd_part_outl(0xb800000c,0,0,1);//clken_misc[0]
	//rtd_part_outl(0xb800000c,6,6,1);//clk_en_iso_misc[6]
//		rtd_part_outl(0xb8000010,25,25,1);//clken_pwm[25]:1
//		rtd_part_outl(0xb8000014,12,12,1);//clken_padmux[12]
//		rtd_part_outl(0xb8000014,29,29,1);//clken_tvsb3[29]//mantis:55208
	rtd_maskl(0xb8000010, (~_BIT25), _BIT25);
	rtd_maskl(0xb8000014, (~_BIT12), _BIT12);
	rtd_maskl(0xb8000014, (~_BIT29), _BIT29);
	//rtd_part_outl(0xb8060040,3,3,1);//clken_iso_pwm[3]:1
	//rtd_part_outl(0xb8060040,2,2,1);//clken_iso_padmux[2]
	////rtd_part_outl(0xb8060040,1,1,1);//clken_iso_misc_off[1]
	//rtd_part_outl(0xb8060040,0,0,1);//clken_iso_misc[0]

	//pin share
	//!!!no need!!! rtd_part_outl(0xb80008b8,31,27,d);//pin share "0x0D"
//		rtd_part_outl(0xb8000c2c,31,29,2);//pin share "0x2"

	if((default_panel_parameter.iCONFIG_PANEL_TYPE != P_VBY1_4K2K)
		&&(default_panel_parameter.iCONFIG_PANEL_TYPE != P_EPI_TYPE))
	{
		rtd_maskl(0xb8000c2c, (~(_BIT31|_BIT30|_BIT29)), _BIT30);
		rtd_outl(0xb8000c78,0xffff0000);//pin share "0xffff0000"
	}
}

void panel_current_adjust(void)
{			//panel			 id		frequence
	int valuefre=0;
	int valuefre1=0;
	int valueduty=0;
	int valueduty1=0;

#ifdef PIN_PANEL_CURRENT_ADJ		
	printf("panel current value = 0x%x\n",(&default_panel_parameter)->iCONFIG_DISP_RESVER05);
	valueduty=((&default_panel_parameter)->iCONFIG_DISP_RESVER05)>>8;
	valueduty1=((&default_panel_parameter)->iCONFIG_DISP_RESVER05) & 0xFF;
	IO_PWM_SetFreq(PIN_PANEL_CURRENT_ADJ,15000);	//set Freq 15k
	IO_PWM_SetDuty(PIN_PANEL_CURRENT_ADJ, valueduty);
	IO_PWM_SetFreq(PIN_PANEL_CURRENT_ADJ1,15000);	//set freq 15K
	IO_PWM_SetDuty(PIN_PANEL_CURRENT_ADJ1,valueduty1); //pwm_set
#endif
}

void panel_init_2nd(void)
{
	if (boot_mode == BOOT_CONSOLE_MODE) {
		printf("skip panel_init_2nd, mode=%d\n", boot_mode);
		return;
	}

	if (panel_init_2nd_is_done || (boot_power_on_mode == POWER_OFF))
		return;
	panel_init_2nd_is_done = 1;

	printf("panel_init_2nd\n");
	// set up back light pwm freq/duty
	panel_current_adjust();
#if defined(CONFIG_BOARD_298X_TV003_QFP176_V2_NAND)	
    IO_PWM_SetFreq(PIN_DIMMER,(&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_FREQ);  //pwm_init
    IO_PWM_SetDuty(PIN_DIMMER, (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_DUTY); //pwm_set
#elif defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC)
	IO_PWM_SetFreq(PIN_BL_ADJ,(&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_FREQ);	//pwm_init
	if ( bootparam.backlight_value > 254 )
	{
		bootparam.backlight_value = 254;
	}
	else if ( bootparam.backlight_value < 10 )
	{
		bootparam.backlight_value = 10;
	}
	IO_PWM_SetDuty(PIN_BL_ADJ, bootparam.backlight_value); //pwm_set
#elif defined(CONFIG_BOARD_298X_TV015_QFP176_V3_EMMC_VER1)
	if(default_panel_parameter.iCONFIG_BACKLIGHT_PWM_DUTY > 254)
		default_panel_parameter.iCONFIG_BACKLIGHT_PWM_DUTY = 254;
	if(default_panel_parameter.iCONFIG_BACKLIGHT_PWM_DUTY < 2)
		default_panel_parameter.iCONFIG_BACKLIGHT_PWM_DUTY = 2;
	IO_PWM_SetFreq(PIN_BL_ADJ,(&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_FREQ);	//pwm_init
	IO_PWM_SetDuty(PIN_BL_ADJ, (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_DUTY); 	//pwm_set
#else
	IO_PWM_SetFreq(PIN_BL_ADJ,(&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_FREQ);	//pwm_init
	IO_PWM_SetDuty(PIN_BL_ADJ, (&default_panel_parameter)->iCONFIG_BACKLIGHT_PWM_DUTY); 	//pwm_set
#endif	
	pwm_pinshare_power_enable();

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
	//printf("\n%d\n",__LINE__);
#ifndef IS_BOX
	if (boot_power_on_mode != BACKLIGHT_OFF)
		IO_Set(PIN_BL_ON_OFF, 1);
#endif

	if(Get_PANEL_TYPE_IS_IWATT_LOCAL_DIMMING()){
#ifdef CONFIG_REALTEK_LOCAL_DIMMING_INTERFACE
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
#endif

       //printf("\n $$$$$$$$ Read 0xA0 = %x \n", ld_Read(0x280));// Read 0xA0 register value



	printf("\n $$$$$$$$ local diming setting complete ....... \n");
        }

#if defined(CONFIG_BOARD_298X_TV035_QFP176_V3_EMMC) || defined(CONFIG_BOARD_298X_TV035_BGA459_EMMC)
	//add by xiangping_chen start
   	//for LVDS Spread Spectrum FMDIV
    rtd_maskl(0xb8000318, 0xFFFF80FF,0x9<<8);
	//add by xiangping_chen end
#endif
        // IMPORTANT! must be called
        panel_misc();

}

void panel_misc(void)
{
#if defined(CONFIG_REALTEK_AMP_TAS5711) || defined(CONFIG_REALTEK_AMP_TAS5707)
    printf("ampinit at panel flow, %d\n",__LINE__);
    extern void AudioAmp_InitAudioOut2I2S_2nd(void);
    AudioAmp_InitAudioOut2I2S_2nd();
#endif

#if defined(CONFIG_REALTEK_EERPOM_TV010_A)
    if(boot_power_on_mode != POWER_OFF)
    {
        Eeprom_SetMacAddressToKernel_Read();
        Eeprom_SetMacAddressToKernel_Apply();
    }
#endif

#ifdef CONFIG_USB_CHECK_CUSTOMER_COMMAND
    if (boot_ac_on && (boot_mode == BOOT_NORMAL_MODE))
    {
        // usb start
        char cmd[128];
        int ret=0;
        memset(cmd, 0, sizeof(cmd));
        sprintf(cmd, "usb start");
        WATCHDOG_KICK();
        ret = run_command(cmd, 0);
        if(ret != 0)
        {
            /* Usb start error */
            WATCHDOG_KICK();
            printf("[INFO] %s:usb start failed. (No USB plug-in)\n", __FUNCTION__);
        }
        else {
            char* pUsbFirstFileName = NULL;
            pUsbFirstFileName = fat_ls_first("usb", "0:1");
            WATCHDOG_KICK();
            if (pUsbFirstFileName) {
                printf("pUsbFirstFileName = %s\n", pUsbFirstFileName);
                if (strncmp(pUsbFirstFileName, "skyworth_test_", strlen("skyworth_test_")) == 0) {  //speedup
                    if (strncmp(pUsbFirstFileName, "skyworth_test_enter_install", strlen("skyworth_test_enter_install")) == 0) {
                        printf("\033[1;31m Usb fast install is detected!! \033[m\n");
                        /* fill 0x2379aacc to enter rescure kernel */
                        rtd_outl(REG_AC_DC_ON_reg, 0x2379aacc);

                        // trigger WD
                        rtd_outl(MIS_TCWTR, _BIT0);
                        rtd_outl(MIS_TCWOV_reg, 0x0); //reboot immediately
                        rtd_clearbits(MIS_TCWCR_reg, 0xff);
                    }

                    if (strncmp(pUsbFirstFileName, "skyworth_test_panelid_", strlen("skyworth_test_panelid_")) == 0) {
                        printf("[DEBUG]%s:%d\n",__FUNCTION__,__LINE__);
                        char panelID_str[3] ={ 0x00, 0x00, 0x00};
                        int panelID;
                        int final_num = strlen("skyworth_test_panelid_");
                        panelID_str[0] = pUsbFirstFileName[final_num];
                        panelID_str[1] = pUsbFirstFileName[final_num+1];
                        panelID = (unsigned int) strtoul (panelID_str, (char **) 0, 10);
                        printf("\033[1;31m panelID_str = %s, panelID = %d\033[m\n", panelID_str, panelID);
                        printf("\033[1;31m panelID_str = %s, panelID = %d\033[m\n", panelID_str, panelID);
                        printf("\033[1;31m panelID_str = %s, panelID = %d\033[m\n", panelID_str, panelID);
                        printf("\033[1;31m panelID_str = %s, panelID = %d\033[m\n", panelID_str, panelID);
                        printf("\033[1;31m panelID_str = %s, panelID = %d\033[m\n", panelID_str, panelID);
                        //eep command
                        memset(cmd, 0, sizeof(cmd));
                        sprintf(cmd, "eep e 0x%02x\n", panelID);
                        printf("\033[1;31m cmd: %s \033[m\n", cmd);
                        WATCHDOG_KICK();
                        run_command(cmd, 0);
                    }
                }
            }
            else
                printf("pUsbFirstFileName = NULL\n");
        }
        // usb stop
        memset(cmd, 0, sizeof(cmd));
        sprintf(cmd, "usb stop");
        ret = run_command(cmd, 0);
        if (ret != 0)
        {
            /* Usb stop error */
            printf("[INFO] %s:usb stop failed.\n", __FUNCTION__);
        }
    }
#endif

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

#if 0
	// PA168 init via I2C command
	if(panel_Tcon_PA168_Enable()){
		mdelay(500);  // wait TCON ready //500ms
		PA168_i2c_cmd(); // PA168 init via I2C command
	}else if(Get_PANEL_TYPE_IS_MILLET3_4K2K_SERIES()){
		mdelay(500);  // wait TCON ready //500ms
		if(default_panel_parameter.iCONFIG_PANEL_CUSTOM_INDEX == VBY_ONE_PANEL_INX8903_4K2K_VBY1){
		}
		else{
			Millet4_i2c_cmd();
		}
	}
#endif
	panel_tcon_i2c_control();


	return;
}

#ifdef IS_BOX
//For BOX ONLY by Andy Teng 2014/02/19
void hdmi_tx_init(void)
{
	printf("%s\n", __FUNCTION__);

	//HDMI TX
	rtd_maskl(0xb8000000, 0xffffefff, 0x1000);	  //HDMI TX rstn
	rtd_maskl(0xb800000c, 0xfffffeff, 0x100); //HDMI TX clk en
	//HDMI RX
	rtd_maskl(0xb8000008, 0xfffdffff, 0x20000);   //HDMI RX rstn
	rtd_maskl(0xb800000c, 0xfffffffd, 0x2);   //HDMI RX clk en
	rtd_maskl(0xb8007B40, 0xFDFFFFFF,0x02000000); //HDMI bandgap power 1:on 0:off
	//HDMI AIO
	rtd_maskl(0xb8000000, 0xffff7fff, 0x8000);	  //AIO rstn
	rtd_maskl(0xb800000c, 0xfffffbff, 0x400); //AIO clk en
	//APLL ADC
	rtd_maskl(0xb8000008, 0xffffffef, 0x10);  //APLL ADC rstn
	rtd_maskl(0xb8000014, 0xfeffffff, 0x1000000); //APLL ADC clk en
	//TVE
	rtd_maskl(0xb8000000, 0xfff7ffff, 0x80000);   //TVE rstn
	rtd_maskl(0xb8000004, 0xfff7ffff, 0x80000);   //TVE clkgen reset
	rtd_maskl(0xb800000c, 0xffffbfff, 0x4000);	  //TVE clk en
	//Display2Tve
	rtd_maskl(0xb8000008, 0xfffffffd, 0x2);   // DISP rstn
	rtd_maskl(0xb8000014, 0xfffffff7, 0x8);   //DISP clk en
	rtd_maskl(0xb8000014, 0xffbfffff, 0x400000);  //Display2TVE clk en

	rtd_outl(0xb8020104,0x00050009);  // APLL_ADC LDO power, for PLL27X

	return;
}
#endif

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

#ifdef IS_BOX
	hdmi_tx_init();
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

#ifdef CONFIG_PANEL_SHARP_60_MEMC
int ms_wait(int ms)
{
	udelay(1000*ms);
	return 0;
}

void panel_sharp_memc_init(unsigned char stage)
{
	if(0 == stage)
	{
		udelay(40000);  // 40 ms
		IO_Set(PIN_PANEL_ENABLE, 0);
//		IO_Set(PIN_DET_POW, 1);
		udelay(40000);  // 40 ms
	}
	else if(1 == stage)
	{
		IO_Set(PIN_BL_ON_OFF, 1);  // Shared with Panel_I2C_Enable
		udelay(100000);  // 100 ms
		dFrdLcdControler_e dFrdLcdControler = FRDLCD_UNKNOWN;
		// Register TV003 I2C callback function
		//printf("Sharp:ifrdSetDriver\n");
		dResult_e dReseult = S_SPEC_ERROR;
		unsigned short Vcomdata;
		unsigned char version[50];

		ifrdSetDriver(I2C_Read_EX2,I2C_Write_EX2,ms_wait);

		// 4-1 Start sequence
		udelay(100000);  // 100 ms
		printf("SHARP 60 MEMC\n");
		// Set inch size of the factory mode.
		//printf("Sharp:eFrdLcdSetSize\n");
		dReseult = eFrdLcdSetSize(FRDLCD_PNL_60);
		//printf("eFrdLcdSetSize = %d\r\n",dReseult);
		//printf("Sharp:eFrdLcdGetLsiInfo\n");
		dFrdLcdControler = eFrdLcdGetLsiInfo();
		//printf("eFrdLcdGetLsiInfo = %d\r\n",dFrdLcdControler);

		dReseult = eFrdLcdChkEepLoadEnd();
		//printf("eFrdLcdChkEepLoadEnd = %d\r\n",dReseult);

		dReseult = eFrdLcdChkEepLoadEnd();
		//printf("eFrdLcdChkEepLoadEnd = %d\r\n",dReseult);

		dReseult = eFrdLcdGetRevInfo(version);
		//printf("eFrdLcdGetRevInfo = %d\r\n",dReseult);

		dReseult = eFrdLcdGetLibVer(version);
		//printf("eFrdLcdGetLibVer = %d\r\n",dReseult);
		//printf("eFrdLcdGetLibVer = %s\r\n",version);
/*
		dReseult = eFrdLcdGetDac(1,&Vcomdata);
		{
			if(Vcomdata > 127)
				Vcomdata = 0;
			dReseult = eFrdLcdSetDac(0,(unsigned char)Vcomdata);
		}
*/
		//printf("Sharp:eFrdSetMute\n");
		eFrdSetMute(1);
		//printf("Sharp:eFrdLcdInit\n");
		dReseult = eFrdLcdInit(1);
		//printf("eFrdLcdInit = %d\r\n",dReseult);

		// Set to FRD_INPUT_FREQ_60HZ
		//printf("Sharp:eFrdInit(1,FRD_INPUT_FREQ_60HZ)\n");
		dReseult = eFrdInit(1,FRD_INPUT_FREQ_50HZ);
		//printf("eFrdInit = %d\r\n ",dReseult);

		// Set to FRDLCD_TRN_OVR_NORMAL
		//printf("eFrdLcdSetTrnOvr(FRDLCD_TRN_OVR_NORMAL)\n");
		dReseult = eFrdLcdSetTrnOvr(FRDLCD_TRN_OVR_NORMAL);
		//printf("eFrdLcdSetTrnOvr = %d\r\n ",dReseult);

		// 4-3 Quick shoot
		// INV_POW must be high, but where is INV_POW??
		if(1) // To Do:  Obtain the setting from MENU->Picture->Advanced->Quick shoot
		{
			//printf("Quick shoot is ON\r\n");
			eFrdSetMode(1);
		}
		else
		{
			//printf("Quick shoot is OFF\r\n");
			eFrdSetMode(0);
		}

		// 4-4 Frequency control
		// INV_POW must be high, but where is INV_POW??
		//printf("Frequency control enable\r\n");
		eFrdSetMute(1);
		udelay(64000);  // 64 ms
		eFrdSetFreeRun(1);

		// Set to FRD_INPUT_FREQ_60HZ
		eFrdSetOutFreq(FRD_INPUT_FREQ_60HZ);
		eFrdLcdSetQsFreq(FRD_INPUT_FREQ_60HZ);
		udelay(50000);  // 50 ms
		eFrdSetFreeRun(0);
		udelay(50000);  // 50 ms
		eFrdSetMute(0);
		udelay(64000);  // 64 ms

		// 4-5 Temperature change
		// INV_POW must be high, but where is INV_POW??

		/*__________________________________________________
		|(*1) Temperature table	|			  |
		|	temperature	|	Temperature table |
		|	Temp<99		|		0	  |
		|	99<=Temp<8C	|		1	  |
		|	8C<=Temp<80	|		2 	  |
		|	80<=Temp<74	|		3	  |
		|	74<=Temp<69	|		4	  |
		|	69<=Temp<5E	|		5	  |
		|	5E<=Temp<4E	|		6	  |
		|	4E<=Temp	|		7	  |
		|_______________________|_________________________|
		*/
		//eFrdLcdSetLvl();

		// INV_POW must be low, but where is INV_POW??
		//printf("eFrdLcdSetQsEnable(1,1)\n");
		eFrdLcdSetQsEnable(1,1);
		//printf("eFrdSetMute(0)\n");
		eFrdSetMute(0);
		udelay(42000);  // 42 ms
		//printf("eFrdLcdSetOutput(1)\n");
		eFrdLcdSetOutput(1);
	}
}
#endif //#ifdef CONFIG_PANEL_SHARP_60_MEMC

