#include <qc_verify_common.h>
#include <rbusHDMIReg.h>
#include <rbusDFEReg.h>
#include <rbusMHLCbus.h>
#include <MHL_cbus.h>
#include <rbusMiscDDCReg.h>

//b8007b08
//bit31 Show Pannel
//bit26 Clock Hysterisis
//bit25 Packet Pixel mode
//bit24 CBUS Enable
//bit18 HDMI Port2
//bit17 HDMI Port1
//bit16 HDMI Port0
//bit11 checking crc to quit if any error
//bit10 MHL Port 2
//bit09 MHL Port 1
//bit08 MHL Port 0
//bit07 HDMI printf
//bit06 Auto EQ

//Set 1 detect from PG packet!
//Set 0 Force No support DVI mode
//#define DVImode 0
UINT8 _bMhl_clk_mode;

typedef struct {
	unsigned int Info;   //[0] : cbus transmit ready or not 
	                          //[1] : reconnect  or not 
	                          //[2] : 1 sec rotine command  ,write ready command per 1 sec 
	                          //[3] : MHL or not
	UINT16 MHL_TIMER1;  // For release  SET_MHL_READY_TO_TRANSMIT
	UINT16 MHL_TIMER2;  // For  RECONNECT_1K
	UINT16 MHL_TIMER3;  // For CONNECT_DCAP_RDY command  1 sec send 1 times
	UINT8   MHL_CBUS_CMD_ST;
	UINT8   bBuf[16];
} MHL_PARAM_T;
MHL_PARAM_T MHL_CTRL;

typedef enum
{
    _MHL_WRITE_BURST_WITH_REQ,
    _MHL_WRITE_BURST_WITHOUT_REQ,
}EnumMHLWriteBurstMode;
enum {
	CBUS_INIT,
	CBUS_WAKE,
	CBUS_DISCOVERY,
	CBUS_CLRHPD,
	CBUS_SETHPD,
	CBUS_PATHEN,
//	CBUS_DCAP,
	CBUS_READY	
};

UINT8 MHLMscSendCommand( UINT8 enumMSCCommand, UINT8 enumMSCOffset, UINT8 enumMSCValue);


/***************************************************************************************/
//Function :   void CBUS_InitialPHYSettings(void)
//Description:  Calibration for 1K/100K and LDO Level Adjust
//                 
//return: S
/**************************************************************************************/
void CBUS_InitialPHYSettings(void)
{
	//HDMI_printk("[CBUS] CBUS_InitialPHYSettings\n");	
	//rtd_maskl(ST_SRST1_reg, ~(RSTN_CBUS_TX|RSTN_CBUS), (RSTN_CBUS_TX|RSTN_CBUS));  				// enable before using b8062bxx & b8062c1c
	//rtd_maskl(ST_CLKEN1_reg,~(CLKEN_CBUS_TX_IP|CLKEN_CBUS_TX|CLKEN_CBUS),(CLKEN_CBUS_TX_IP|CLKEN_CBUS_TX|CLKEN_CBUS));  // enable before using b8062bxx & b8062c1c
	rtd_maskl(CBUS_PHY0_reg, ~CBUS_PHY0_EN_BIAS, CBUS_PHY0_EN_BIAS); 								// enable signal for CBUS_TX_RX (Sirius added)
	
	// Disable CBUS LDO and Input Comparator
	rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_en_ldo_cbus_mask|CBUS_PHY_1_en_cmp_cbus_mask),0);	
	// Disable Output Driver
	rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_en_driver_cbus_mask),0);

	// Auto Calibration for 1K and Manual Calibration for 100K For monitor
	// TV set 1 k 100k auto , see if it is ok or not ????
	//set resistance manual mode
	rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_auto_k_100k_mask|CBUS_PHY_1_auto_k_1k_mask|CBUS_PHY_1_en_res_cal_cbus_mask), (CBUS_PHY_1_auto_k_100k_mask|CBUS_PHY_1_auto_k_1k_mask));
	rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_auto_k_100k_mask|CBUS_PHY_1_auto_k_1k_mask|CBUS_PHY_1_en_res_cal_cbus_mask), (CBUS_PHY_1_auto_k_100k_mask|CBUS_PHY_1_auto_k_1k_mask|CBUS_PHY_1_en_res_cal_cbus_mask));
	// Adjust CBUS Input Comparator VIH = 0.95V and VIL = 0.65V
	rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_sel_cbus0_input_high_mask|CBUS_PHY_1_sel_cbus0_input_low_mask), (CBUS_PHY_1_sel_cbus0_input_high(1)|CBUS_PHY_1_sel_cbus0_input_low(1)));
	// Set CBUS Max Driving Strength    43n   cloud modify 2013 change 43=>32
	rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_sel_cbus_0_driving_mask), (CBUS_PHY_1_sel_cbus_0_driving(6)));
	// for cts test 2na to rxsence

	rtd_maskl(HDMIPHY_REG_CK_9_12_reg,~MHL_Z100K,MHL_Z100K);	 //disable    100k res //Sirius

}

/***************************************************************************************/
//Function :   void MHLInitialMACSettings(void)
//Description:  Cbus setting
//                 
//return: S
/**************************************************************************************/
void MHLInitialMACSettings(void)
{
    // Write clear wake pulse & discovery pulse 
     rtd_maskl(CBUS_STANDBY_00_reg, ~(CBUS_STANDBY_00_wake_pulse_det_mask|CBUS_STANDBY_00_dis_pulse_det_mask),(CBUS_STANDBY_00_wake_pulse_det_mask|CBUS_STANDBY_00_dis_pulse_det_mask));
    
    // Set MHL 1MHz Clk Divider  27M clock 
     rtd_maskl(CBUS_STANDBY_01_reg, ~(CBUS_STANDBY_01_clk_1m_div_mask), CBUS_STANDBY_01_clk_1m_div(13));
    
    //cloud fix for HTC issue
     rtd_maskl(CBUS_STANDBY_01_reg, ~(CBUS_STANDBY_01_clk_1k_div_mask), CBUS_STANDBY_01_clk_1k_div(648));  //519* 1.25
    //initial wake up pulse width
    //2013 0621 for HTC wake up timing  16.25msec ~33.75msec     // HTC ONE and butterfly
     rtd_maskl(CBUS_STANDBY_04_reg,~(CBUS_STANDBY_04_wake_offset_mask|CBUS_STANDBY_04_cbus_disconn_mask|CBUS_STANDBY_04_wake_cnt_mask|_BIT8|_BIT9|_BIT10),(CBUS_STANDBY_04_wake_offset(7)|_BIT8|_BIT9|_BIT10|_BIT11|_BIT12|_BIT13));//20msec +-7msec
       
    //Set Cbus discuss  Low Time to 150us
     rtd_maskl(CBUS_STANDBY_02_reg, ~(CBUS_STANDBY_02_disconn_mask), CBUS_STANDBY_02_disconn(1)); //cloud test for 4.3.20
	  
    // Set Discovery Upper/Lower Bound  60 micro second ~ 140 micro sec
     rtd_maskl(CBUS_STANDBY_05_reg, ~(CBUS_STANDBY_05_dis_upper_mask|CBUS_STANDBY_05_dis_lower_mask), (CBUS_STANDBY_05_dis_upper(5)|CBUS_STANDBY_05_dis_lower(5)));
}

void CDF_Cability_Setting(void)
{
	rtd_maskl(MSC_REG_01_reg, ~MSC_REG_01_mhl_ver_mask, (CDF_CR_MHL_VER_MAJOR<<4)|CDF_CR_MHL_VER_MINOR);  //MHL 2.0
	rtd_maskl(MSC_REG_02_reg, ~(MSC_REG_02_plim_mask|MSC_REG_02_pow_mask|MSC_REG_02_dev_type_mask), MSC_REG_02_plim(CDF_CR_POW_PLIM)|MSC_REG_02_pow(CDF_CR_POW)|MSC_REG_02_dev_type(CDF_CR_DEV_TYPE));  //MHL 2.0
	//adopter_H
	rtd_outl (MSC_REG_03_reg,CDF_CR_ADOPTER_ID_H);
	// adopter_L
	rtd_outl (MSC_REG_04_reg,CDF_CR_ADOPTER_ID_L);


	rtd_maskl(MSC_REG_05_reg, ~(MSC_REG_05_vid_link_md_mask|MSC_REG_05_supp_vga_mask|MSC_REG_05_supp_islands_mask|MSC_REG_05_supp_ppixel_mask|MSC_REG_05_supp_yuv422_mask|MSC_REG_05_supp_yuv444_mask|MSC_REG_05_supp_rgb444_mask),(MSC_REG_05_supp_vga(CDF_CR_SUPP_VGA))|MSC_REG_05_supp_islands(CDF_CR_SUPP_ISLANDS)|MSC_REG_05_supp_ppixel(CDF_CR_SUPP_PPIXEL)|MSC_REG_05_supp_yuv422(CDF_CR_SUPP_YCBCR422)|MSC_REG_05_supp_yuv444(CDF_CR_SUPP_YCBCR444)|MSC_REG_05_supp_rgb444(CDF_CR_SUPP_YCBCR444));// not support PP mode 

	rtd_maskl(MSC_REG_06_reg, ~(MSC_REG_06_aud_8ch_mask|MSC_REG_06_aud_2ch_mask),MSC_REG_06_aud_8ch(CDF_CR_AUD_8CH)|MSC_REG_06_aud_2ch(CDF_CR_AUD_2CH));// not support PP mode 

	rtd_maskl(MSC_REG_07_reg, ~(MSC_REG_07_video_type_mask|MSC_REG_07_vt_game_mask|MSC_REG_07_vt_cinema_mask|MSC_REG_07_vt_photo_mask|MSC_REG_07_vt_graphics_mask),MSC_REG_07_vt_game(CDF_CR_VT_GAME)|MSC_REG_07_vt_cinema(CDF_CR_VT_CINEMA)|MSC_REG_07_vt_photo(CDF_CR_VT_PHOTO)|MSC_REG_07_vt_graphics(CDF_CR_VT_GRAPHICS));

	rtd_maskl(MSC_REG_08_reg, ~(MSC_REG_08_ld_gui_mask|MSC_REG_08_ld_speaker_mask|MSC_REG_08_ld_record_mask|MSC_REG_08_ld_tuner_mask|MSC_REG_08_ld_media_mask|MSC_REG_08_ld_audio_mask|MSC_REG_08_ld_video_mask|MSC_REG_08_ld_display_mask),MSC_REG_08_ld_gui(CDF_CR_LD_GUI)|MSC_REG_08_ld_speaker(CDF_CR_LD_SPEAKER)|MSC_REG_08_ld_record(CDF_CR_LD_RECORD)|MSC_REG_08_ld_tuner(CDF_CR_LD_TUNER)|MSC_REG_08_ld_media(CDF_CR_LD_MEDIA)|MSC_REG_08_ld_audio(CDF_CR_LD_AUDIO)|MSC_REG_08_ld_video(CDF_CR_LD_VIDEO)|MSC_REG_08_ld_display(CDF_CR_LD_DISPLAY));//

	rtd_maskl(MSC_REG_09_reg, ~MSC_REG_09_bandwid_mask,MSC_REG_09_bandwid(CDF_CR_BANDWIDTH));// not support PP mode  
	// RCP  RAP support   UCP RECV support 
	rtd_maskl(MSC_REG_0A_reg, ~(MSC_REG_0A_ucp_recv_supp_mask|MSC_REG_0A_ucp_send_supp_mask|MSC_REG_0A_sp_supp_mask|MSC_REG_0A_rap_supp_mask|MSC_REG_0A_rcp_supp_mask),MSC_REG_0A_ucp_recv_supp(CDF_CR_UCP_RECV_SUPPORT)|MSC_REG_0A_ucp_send_supp(CDF_CR_UCP_SEND_SUPPORT)|MSC_REG_0A_sp_supp(CDF_CR_SP_SUPPORT)|MSC_REG_0A_rap_supp(CDF_CR_RAP_SUPPORT)|MSC_REG_0A_rcp_supp(CDF_CR_RCP_SUPPORT));// not support RAP   RCP  UCP send

	rtd_maskl(MSC_REG_0B_reg, ~MSC_REG_0B_device_id_h_mask,CDF_CR_DEVICE_ID_H);// not support PP mode

	rtd_maskl(MSC_REG_0C_reg, ~MSC_REG_0C_device_id_l_mask,CDF_CR_DEVICE_ID_L);// not support PP mode  

	rtd_maskl(MSC_REG_0D_reg, ~MSC_REG_0D_scr_size_mask,MSC_REG_0D_scr_size(CDF_CR_SCRATCHPAD_SIZE));// not support PP mode

	rtd_maskl(MSC_REG_0E_reg, ~(MSC_REG_0E_stat_size_mask|MSC_REG_0E_int_size_mask),MSC_REG_0E_stat_size(CDF_CR_INT_SIZE)|MSC_REG_0E_int_size(CDF_CR_STAT_SIZE));// not support PP mode  

}

/***************************************************************************************/
//Function :  MHLTmdsInitial(void)
//Description: MHL Tmds Setting 
// 
//return: SEND MSG RCP key To follower
/**************************************************************************************/
void MHLTmdsInitial(void)
{
	//pn no swap
	rtd_maskl(MHL_DAL_STATUS_reg, ~(MHL_DAL_STATUS_pn_swap_mask),0);

	//MHL
	rtd_maskl(MHL_DAL_STATUS_reg,~MHL_DAL_STATUS_mhl_ver_1_2_mask,MHL_DAL_STATUS_mhl_ver_1_2(1));
	CDF_Cability_Setting();
}

/***************************************************************************************/
//Function :  MHL_LinkerSetting(UINT8 bkeycode)
//Description: MHL_MSG_UCPE  
//                  UTF-8 Character Protocol (UCP)
//return: SEND MSG RCP key To follower
/**************************************************************************************/
void CBUS_LinkerSetting(float fSystemClk)
{
	float  One_clk_period ,fTemp1,fTemp2 ;
	UINT8 bTemp1,bTemp2;

	// Upper Bound of SYNC Pulse Low Time Period  & Lower Bound 
	//ScalerSetByte(P28_AF_CBUS0_CTRL_0F, 0xEA);
	//upper bound of sync pulse 
	One_clk_period = 1000/(fSystemClk/2) ; //unit  n -sec
	fTemp1 = 1.6*T_BIT_CBUS_MAX/One_clk_period;
	bTemp1 = (UINT8)fTemp1 ;  //0xc2 if clock is 202Mhz
	fTemp2 = 1.4*T_BIT_CBUS_MIN/One_clk_period;
	bTemp2 = (UINT8)fTemp2 ;  //0x71 if clock is 202Mhz
	//HDMI_PRINTF("[CBUS_LOG]CBUS_LinkerSetting Sync pulse low Time Upper bound  = %x (0xc2)Lower bound = %x (0x71) \n",bTemp1 ,bTemp2);
	rtd_maskl(CBUS_LINK_00_reg, ~(CBUS_LINK_00_sync0_hb_mask|CBUS_LINK_00_sync0_lb_mask), (CBUS_LINK_00_sync0_hb(bTemp1)|CBUS_LINK_00_sync0_lb(bTemp2)));

	// Upper Bound of SYNC Pulse High Time Period & Lower Bound of SYNC Pulse High Time Period
	//ScalerSetByte(P28_B1_CBUS0_CTRL_11, 0x58);
	fTemp1 = 0.6*T_BIT_CBUS_MAX/One_clk_period;
	bTemp1 = (UINT8)fTemp1 ;  //0x48 if clock is 202Mhz
	fTemp2 = 0.4*T_BIT_CBUS_MIN/One_clk_period;
	bTemp2 = (UINT8)fTemp2 ;  //0x21 if clock is 202Mhz
	//HDMI_PRINTF("[CBUS_LOG]CBUS_LinkerSetting Sync pulse High Time Upper bound  = %x (0x48) Lower bound = %x (0x21) \n",bTemp1 ,bTemp2);
	rtd_maskl(CBUS_LINK_01_reg, ~(CBUS_LINK_01_sync1_hb_mask|CBUS_LINK_01_sync1_lb_mask), (CBUS_LINK_01_sync1_hb(bTemp1)|CBUS_LINK_01_sync1_lb(bTemp2)));

	// Absolute Threshold Time
	//ScalerSetByte(P28_B4_CBUS0_CTRL_14, 0x5D);// not set bit 8 enable 
	fTemp1 = 0.76*T_BIT_CBUS_AVE/One_clk_period; ;
	bTemp1 = (UINT8)fTemp1 ;  //0x48 if clock is 202Mhz
	//HDMI_PRINTF("[CBUS_LOG] Absolute Threshold Time = %x (0x4d) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_03_reg, ~(CBUS_LINK_03_abs_threshold_mask), (CBUS_LINK_03_abs_threshold(bTemp1)));

	// Parity Bit Time
	//ScalerSetByte(P28_B5_CBUS0_CTRL_15, 0x79);
	fTemp1 = T_BIT_CBUS_AVE/One_clk_period; ;
	bTemp1 = (UINT8)fTemp1 ;  //0x65 if clock is 202Mhz    
	//HDMI_PRINTF("[CBUS_LOG] Parity Bit Time = %x (0x65) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_04_reg, ~(CBUS_LINK_04_parity_time_mask), (CBUS_LINK_04_parity_time(bTemp1)));

	// Parity Error Limit
	//ScalerSetBit(P28_B6_CBUS0_CTRL_16, ~(_BIT7 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);

	rtd_maskl(CBUS_LINK_05_reg, ~(CBUS_LINK_05_parity_limit_mask|CBUS_LINK_05_parity_fail_mask), (CBUS_LINK_05_parity_limit(0x0f)|CBUS_LINK_05_parity_fail_mask));	

	// Ack Bit Initial Falling Edge
	//ScalerSetBit(P28_B7_CBUS0_CTRL_17, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x0F);
	//fTemp1 =0.75* 128/One_clk_period;//cloud test
	fTemp1 = 128/One_clk_period;//cloud test
	bTemp1 = (UINT8)fTemp1 ;  // if clock is 202Mhz       ????????????
	//HDMI_PRINTF("[CBUS_LOG] Ack Bit Initial Falling Edge = %x (0x0d) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_06_reg, ~(CBUS_LINK_06_ack_fall_mask), (CBUS_LINK_06_ack_fall(bTemp1)));	

	// Ack Bit Drive Low Time
	//ScalerSetBit(P28_B8_CBUS0_CTRL_18, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x3C);
	// 400nsec ~600nsec 
	// fTemp1 = 0.96*T_CBUS_ACK_0/One_clk_period; 
	fTemp1 = T_CBUS_ACK_0/One_clk_period; 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz       
	//HDMI_PRINTF("[CBUS_LOG] Ack Bit Drive Low Time = %x (0x32) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_07_reg, ~(CBUS_LINK_07_ack_0_mask), (CBUS_LINK_07_ack_0(bTemp1)));	

	// Requester Bit Time
	//ScalerSetByte(P28_BA_CBUS0_CTRL_1A, 0x80);
	// fTemp1 = 1.04*T_TX_bit_time/One_clk_period; 
	fTemp1 = T_TX_bit_time/One_clk_period; 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz       
	//HDMI_PRINTF("[CBUS_LOG] Ack Bit Drive Low Time = %x (0x65) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_08_reg, ~(CBUS_LINK_08_tx_bit_time_mask), (CBUS_LINK_08_tx_bit_time(bTemp1)));	

	// Check Received Ack Bit's Falling Edge
	//ScalerSetBit(P28_BC_CBUS0_CTRL_1C, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x7F);
	// fTemp1 = T_TX_bit_time*0.7/One_clk_period; 
	fTemp1 = T_TX_bit_time*0.88/One_clk_period; 
	bTemp1 = (UINT8)fTemp1 ;
	//cloud change for cts test
	//bTemp1 = 0x59;
	//HDMI_PRINTF("[CBUS_LOG] Check Received Ack Bit's Falling Edge = %x (0x46) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_0A_reg, ~(CBUS_LINK_0A_tx_ack_fal_mask), (CBUS_LINK_0A_tx_ack_fal(bTemp1)));	

	// Check Received Ack Bit's Driving Low Period Upper Bound
	//ScalerSetBit(P28_BD_CBUS0_CTRL_1D, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x4F);
	fTemp1 = T_CBUS_ACK_0_max*1.21/One_clk_period; 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz     
	//bTemp1 = 0x45;
	//bTemp1 = 0x49;//2013 0815 for cbus cts 4.3.
	//HDMI_PRINTF("[CBUS_LOG] Check Received Ack Bit's Driving Low Period Upper Bound = %x (0x3E) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_0B_reg, ~(CBUS_LINK_0B_tx_ack_low_hb_mask), (CBUS_LINK_0B_tx_ack_low_hb(bTemp1)));

	// Check Received Ack Bit's Driving Low Period Lower Bound
	//ScalerSetBit(P28_BE_CBUS0_CTRL_1E, ~(_BIT6 | _BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x25);
	fTemp1 = T_CBUS_ACK_0_min*0.8/One_clk_period; 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz   
	//cloud change for cts test
	//bTemp1 = 0x20;
	//HDMI_PRINTF("[CBUS_LOG] Check Received Ack Bit's Driving Low Period lower Bound = %x (0x27) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_0C_reg, ~(CBUS_LINK_0C_tx_ack_low_lb_mask), (CBUS_LINK_0C_tx_ack_low_lb(bTemp1)));

	// Actively Driving High Time for CBUS
	//ScalerSetBit(P28_C0_CBUS0_CTRL_20, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1 | _BIT0), 0x19);
	fTemp1 = T_drive_H_AVE/One_clk_period; 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz       
	//HDMI_PRINTF("[CBUS_LOG] Actively Driving High Time for CBUS = %x (0x19) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_0E_reg, ~(CBUS_LINK_0E_drv_hi_cbus_mask), (CBUS_LINK_0E_drv_hi_cbus(bTemp1)));

	// CBUS Requester Transmit Opportunity after Arbitration
	//ScalerSetByte(P28_C2_CBUS0_CTRL_22, 0x79);
	fTemp1 = T_TX_bit_time/One_clk_period; 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz       
	//HDMI_PRINTF("[CBUS_LOG] CBUS Requester Transmit Opportunity after Arbitration = %x (0x65) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_10_reg, ~(CBUS_LINK_10_req_opp_flt_mask), (CBUS_LINK_10_req_opp_flt(bTemp1)));

	// CBUS Requester Continue After Ack
	//ScalerSetByte(P28_C3_CBUS0_CTRL_23, 0x3C);
	fTemp1 = T_TX_bit_time*0.5/(One_clk_period); 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz       
	//HDMI_PRINTF("[CBUS_LOG] CBUS Requester Continue After Ack = %x (0x32) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_11_reg, ~(CBUS_LINK_11_req_cont_mask), (CBUS_LINK_11_req_cont(bTemp1)));

	// Link Layer Timeout
	//ScalerSetBit(P28_C5_CBUS0_CTRL_25, ~(_BIT5 | _BIT4 | _BIT3 | _BIT2 | _BIT1), (_BIT4 | _BIT3 | _BIT2));
	fTemp1 = ((T_link_timeout/One_clk_period)-15)/16; 
	bTemp1 = (UINT8)fTemp1 ;  //0x32  if clock is 202Mhz       
	//HDMI_PRINTF("[CBUS_LOG] CBUS Requester Continue After Ack = %x (0x0c) \n",bTemp1 );
	rtd_maskl(CBUS_LINK_13_reg, ~(CBUS_LINK_13_link_time_mask), (CBUS_LINK_13_link_time(bTemp1)));
}

void Cbus_Power(char enable)
{
#define DETECT_MHL2_IN 1
	if(enable)
	{
		// Enable CBUS Phy, LDO and Input Comparator  Enable Output Driver
		rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_en_cbus_mask|CBUS_PHY_1_en_cmp_cbus_mask|CBUS_PHY_1_en_driver_cbus_mask|CBUS_PHY_1_en_ldo_cbus_mask|CBUS_PHY_1_psm_cbus_mask|CBUS_PHY_1_sel_cbusb_gpio_mask),(CBUS_PHY_1_en_cbus_mask|CBUS_PHY_1_en_cmp_cbus_mask|CBUS_PHY_1_en_driver_cbus_mask|CBUS_PHY_1_en_ldo_cbus_mask) );
	}
	else
	{
		if(MHLMscSendCommand( MHL_MSC_CMD_CODE_CLR_HPD, MHL_MSC_CMD_CODE_NULL, MHL_MSC_CMD_CODE_NULL) == _MHL_OK)
		{
			//HDMI_PRINTF("[CBUS] _MHL_CLR_HPD!!!!!  \n" );  
		}
		else
		{
			HDMI_PRINTF("[CBUS]  _MHL_CLR_HPD FAIL!!!!!  \n" ); 
		}
		//FIX HUAWEI NOT SET CBUS pulse issue
		//set input 
		if(DETECT_MHL2_IN)   hdmiport_mask(CBUS_PHY_0_reg,~(CBUS_PHY_0_cbus_e_mask),(0));  //set input 
		hdmiport_mask(CBUS_PHY_1_reg,~(CBUS_PHY_1_sel_cbusb_gpio_mask),(CBUS_PHY_1_sel_cbusb_gpio_mask)); //disable cbus ,SET GPIO function
		// Disable CBUS Phy, LDO, Input Comparator & Disable Output Driver
		rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_en_cbus_mask|CBUS_PHY_1_en_cmp_cbus_mask|CBUS_PHY_1_en_driver_cbus_mask|CBUS_PHY_1_en_ldo_cbus_mask),0 );
		rtd_maskl(CBUS_STANDBY_08_reg, ~(CBUS_STANDBY_08_goto_sink1_mask),(CBUS_STANDBY_08_goto_sink1_mask) );
	}
}

//--------------------------------------------------
// Description  : Power Process for CBUS Phy
// Input Value  : bEn --> _ON/_OFF
// Output Value : None
//--------------------------------------------------
void CBUSSwitch( UINT8 benable)
{
	if(benable == TRUE)    // MHL plug in 
	{
		rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_en_cbus_mask|CBUS_PHY_1_en_cmp_cbus_mask|CBUS_PHY_1_en_driver_cbus_mask|CBUS_PHY_1_en_ldo_cbus_mask|CBUS_PHY_1_psm_cbus_mask|CBUS_PHY_1_sel_cbusb_gpio_mask),(CBUS_PHY_1_en_cbus_mask|CBUS_PHY_1_en_cmp_cbus_mask|CBUS_PHY_1_en_driver_cbus_mask|CBUS_PHY_1_en_ldo_cbus_mask) );
		rtd_maskl(HDMIPHY_REG_CK_9_12_reg,~MHL_Z100K, MHL_Z100K); //disable 100k //Sirius
		// SET GPIO AS CBUS 
		rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_sel_cbusb_gpio_mask),0);
		// Enable Discovery IRQ
		rtd_maskl(CBUS_STANDBY_00_reg, ~(CBUS_STANDBY_00_dis_irq_en_mask|CBUS_STANDBY_00_wake_irq_en_mask),0);
		// MHL Attached
		rtd_maskl(CBUS_STANDBY_08_reg, ~(CBUS_STANDBY_08_cable_det_mask),CBUS_STANDBY_08_cable_det_mask);
		rtd_maskl(HDMI_VCR_reg, ~(HDMI_VCR_cbus_ddc_chsel_mask),HDMI_VCR_cbus_ddc_chsel_mask);//cbus ddc select
//		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300pow_mask|REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask|REG_MHL_CTRL_reg_z100k_enb_mask), (REG_MHL_CTRL_reg_z300pow((1<<ch))));	//MHL mode
//		rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,   //Z0
//			~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask), 
//			(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(0x00)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(0x00)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(0x00)));
	}
	else                            // MHL plug out
	{
		// set GPIO be HPD
		rtd_maskl(CBUS_PHY_1_reg, ~(CBUS_PHY_1_sel_cbusb_gpio_mask),CBUS_PHY_1_sel_cbusb_gpio_mask);

		// Discovery Function Power Down and System Clk Gated
		// Disable Discovery IRQ
		rtd_maskl(CBUS_STANDBY_00_reg, ~(CBUS_STANDBY_00_dis_irq_en_mask|CBUS_STANDBY_00_wake_irq_en_mask),0);

		// MHL Unattached
		rtd_maskl(CBUS_STANDBY_08_reg, ~(CBUS_STANDBY_08_cable_det_mask),0);
		rtd_maskl(HDMI_VCR_reg, ~(HDMI_VCR_cbus_ddc_chsel_mask),0);  //cbus ddc select  
//		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300pow_mask|REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask|REG_MHL_CTRL_reg_z100k_enb_mask), 
//			(REG_MHL_CTRL_reg_z300pow_mask|REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask|REG_MHL_CTRL_reg_z100k_enb_mask));	//MHL mode
//		rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,   //Z0
//			~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask), 
//			(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(0x07)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(0x07)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(0x07)));
	}    
}



//--------------------------------------------------
// Description  : Send MSC HPD Operation
// Input Value  : ucInputPort --> D0 or D1
//                enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Different Fail Situations
//--------------------------------------------------

UINT8 MHLMscFIFOSendCommand( UINT8 enumMSCCommand, UINT8 enumMSCOffset, UINT8 enumMSCValue, UINT8 ucDataLength, UINT8 *pucData)
{
	UINT8 ucTimeOut = 100;
	UINT8 ucSendType = 0;
	UINT8 ucWaitType = 0;
	UINT8 ucI = 0;
	//  HDMI_PRINTF("[CBUS_LOG] cloud MHLMscFIFOSendCommand = %x ,  offset = %x ,  enumMSCValue = %x \n" ,enumMSCCommand,enumMSCOffset,enumMSCValue); 
	switch(enumMSCCommand)
	{
	case MHL_MSC_CMD_CODE_SET_INT:   //MHL_MSC_CMD_CODE_WRT_STAT 
	case MHL_MSC_CMD_CODE_MSC_MSG:
		ucSendType = MHL_TX_CASE_COM_OFF_DAT;
		ucWaitType = MHL_TX_WAIT_CASE_CMD_ONLY;
		break;

	case MHL_MSC_CMD_CODE_SET_HPD:
		ucSendType = MHL_TX_CASE_COMMAND;
		ucWaitType = MHL_TX_WAIT_CASE_CMD_ONLY;
		break;

	case MHL_MSC_CMD_CODE_GET_STATE:
	case MHL_MSC_CMD_CODE_GET_VENDOR_ID:
	case MHL_MSC_CMD_CODE_GET_MSC_ERR:
		ucSendType = MHL_TX_CASE_COMMAND;
		ucWaitType = MHL_TX_WAIT_CASE_DATA_ONLY;
		break;

	case MHL_MSC_CMD_CODE_ABORT:
		ucSendType = MHL_TX_CASE_COMMAND;
		ucWaitType = MHL_TX_WAIT_CASE_CMD_NO_WAIT;
		break;

	case MHL_MSC_CMD_CODE_WRT_BURST:
		ucSendType = MHL_TX_CASE_COM_OFF_DAT_COM;
		ucWaitType = MHL_TX_WAIT_CASE_CMD_ONLY;
		break;

	default:
		break;
	}


	// Check If Source Has Sent An ABORT Packet
	if(CBUS_MSC_06_get_abort_req_irq(rtd_inl(CBUS_MSC_06_reg)) == TRUE)		
	{
		//clear Abort flag 
		rtd_maskl(CBUS_MSC_06_reg,~(CBUS_MSC_06_abort_req_irq_mask),CBUS_MSC_06_abort_req_irq_mask);
		return _MHL_ABORT_FAIL;
	}

	FW0Requester_set_tx_case(ucSendType);
	rtd_maskl(FW0_REQ_00_reg,~(FW0_REQ_00_fw0_fifo_clr_mask),FW0_REQ_00_fw0_fifo_clr_mask);
	// Set MSC Command
	FW0Requester_set_cmd1(enumMSCCommand);
	// Set MSC Offset
	FW0Requester_set_offset(enumMSCOffset);
	if(enumMSCCommand == MHL_MSC_CMD_CODE_WRT_BURST)
	{
		HDMI_PRINTF("[CBUS] MHLMscFIFOSendCommand -> MHL_MSC_CMD_CODE_WRT_BURST \n");   
		// Set MSC Last Command
		FW0Requester_set_cmd2(MHL_MSC_CMD_CODE_EOF);
		// Set MSC Data
		for(ucI = 0; ucI < ucDataLength; ucI++)
		{
			FW0Requester_set_data(pucData[ucI]);
		}
	}
	else
	{
		// Set MSC Value
		FW0Requester_set_data(enumMSCValue);
	}

	// MSC Packet and Wait Type
	FW0Requester_set_head(MHL_HEADER_MSC_CMD);
	FW0Requester_set_wait_case(ucWaitType);
	// Send Request
	FW0Requester_set_req_en(1);

	// Check if Process is finished
	while(--ucTimeOut != 0)
	{
		//  HDMI_PRINTF("[CBUS_LOG]HW REQ finish  = %d  , Error flag = %d  \n",FW0Requester_get_finish_flag() ,FW0Requester_get_error_flag());
		if(CBUS_MSC_06_get_abort_req_irq(rtd_inl(CBUS_MSC_06_reg)) == TRUE)  //abort occur		
		{
			//clear Abort flag 
			rtd_maskl(CBUS_MSC_06_reg,~(CBUS_MSC_06_abort_req_irq_mask),CBUS_MSC_06_abort_req_irq_mask);
			HDMI_PRINTF("[CBUS] SEND CMD return Abort \n");
			return _MHL_ABORT_FAIL;
		}
		else if((FW0Requester_get_finish_flag() == TRUE) && (FW0Requester_get_error_flag() == 0x00))
		{   
			// Transmit success
			// Clear Flag

			FW0Requester_set_finish_flag(1);

			if(ucWaitType == MHL_TX_WAIT_CASE_CMD_NO_WAIT)
			{
				//   HDMI_PRINTF("[CBUS_LOG]Transmit finish !!_MHL_SUCCESS!!!!!!\n");
				return _MHL_SUCCESS;
			}
			else
			{
				// Check ACK Packet
				// HDMI_PRINTF("[CBUS_LOG]Transmit finish !!!!!!\n");
				if(FW0Requester_get_cmd()== MHL_MSC_CMD_CODE_ACK)
				{
					//    HDMI_PRINTF("[CBUS_LOG]SEND CMD return _MHL_SUCCESS \n");
					return _MHL_SUCCESS;
				}
				else
				{
					HDMI_PRINTF("[CBUS] SEND CMD return _MHL_FAIL \n");
					return _MHL_FAIL;
				}
			}
		}
		else if((FW0Requester_get_error_flag() == TRUE)  && (FW0Requester_get_error_code() == _MHL_ERR_CODE_PRO_ER))
		{
			// Clear Flags
			FW0Requester_set_finish_flag(1);
			FW0Requester_set_error_flag(1);
			FW0Requester_CLR_error_code() ;
			HDMI_PRINTF("[CBUS] SEND CMD return _MHL_ABORT_REPLY \n");
			return _MHL_ABORT_REPLY;
		}

		udelay(10000);
		//  ScalerTimerDelayXms(1);
	}

	// Clear Flags
	FW0Requester_set_finish_flag(1);
	FW0Requester_set_error_flag(1);
	FW0Requester_CLR_error_code() ;
	HDMI_PRINTF("[CBUS] not finish ucTimeOut = %d !! _MHL_FAIL !!!!!! \n",ucTimeOut);  
	return _MHL_FAIL;
}
//--------------------------------------------------
// Description  : Send MSC HPD Operation
// Input Value  : ucInputPort --> D0 or D1
//                enumMSCType --> MSC Command
//                enumMSCOffset --> MSC Device Register
//                enumMSCValue --> MSC Device Register Field
// Output Value : Success or Fail
//--------------------------------------------------
UINT8 MHLMscSendCommand( UINT8 enumMSCCommand, UINT8 enumMSCOffset, UINT8 enumMSCValue)
{
    UINT8 ucResultPacket = 0;
    
    ucResultPacket = MHLMscFIFOSendCommand( enumMSCCommand, enumMSCOffset, enumMSCValue, 0, _NULL_POINTER);
 
    return ucResultPacket;

}

//--------------------------------------------------
// Description  : Send Write Burst Operation
// Input Value  : ucInputPort --> D0 or D1
//                ucDataLength --> Data Length
//                pucData --> Data
//                ucMode --> Write Burst Mode
// Output Value : Success or Different Fail Situations
//--------------------------------------------------

UINT8 MHLMscSendWriteBurst(UINT8  ucOffset, UINT8 ucDataLength, UINT8 *pucData, EnumMHLWriteBurstMode enumMode)
{
    UINT8 ucResultPacket = 0 , bTimecnt =100;

    if(enumMode == _MHL_WRITE_BURST_WITH_REQ)
    {

	// Clear Grant To Write Flag
	rtd_maskl(MSC_REG_20_reg,~MSC_REG_20_grt_wrt_mask,MSC_REG_20_grt_wrt_mask);
	// Send Request to Write
	MHLMscSendCommand( MHL_MSC_CMD_CODE_SET_INT, _MHL_REG_RCHANGE_INT, REQ_WRT);

	//  this area is different with monitor
	// Disable Access Port Auto Increase
	//    ScalerSetBit(P28_AB_CBUS0_CTRL_0B, ~_BIT0, 0x00);
	// Polling Grant to Write
	//    ScalerSetByte(P28_AC_CBUS0_CTRL_0C, _MSC_RCHANGE_INT);
	//    ScalerTimerPollingFlagProc(100, P28_AD_CBUS0_CTRL_0D, _MSC_GRT_WRT, _TRUE);
	// Enable Access Port Auto Increase
	//    ScalerSetBit(P28_AB_CBUS0_CTRL_0B, ~_BIT0, _BIT0);        

	do
	{
		mdelay(10);
		bTimecnt --;
//		if(MSC_REG_20_get_grt_wrt(rtd_inl(MSC_REG_20_reg)))   break ;
	}
	while ((!MSC_REG_20_get_grt_wrt(rtd_inl(MSC_REG_20_reg)))&&(bTimecnt) );

	if(bTimecnt ==0)    HDMI_PRINTF("[CBUS] MHLMscSendWriteBurst  wait Timeout!!! \n" );

    }

//    if(GET_MHL_READY_TO_TRANSMIT() == TRUE)
    {
        ucResultPacket = MHLMscFIFOSendCommand(MHL_MSC_CMD_CODE_WRT_BURST, ucOffset, 0x00, ucDataLength, pucData);

        switch(ucResultPacket)
        {
            case _MHL_SUCCESS: // Source reply ACK Packet

                // Send Device Scratchpad Change
                MHLMscSendCommand( MHL_MSC_CMD_CODE_SET_INT, _MHL_REG_RCHANGE_INT, DSCR_CHG);
                
                return _MHL_OK;
                
                break;

            case _MHL_ABORT_FAIL: // Source reply ABORT Packet

//                SET_MHL_READY_TO_TRANSMIT(0);

//                SET_MHL_TIMER1_SEC(250); // 250 * 10 msec  =2.5 sec
                

                
                return _MHL_NG;

                break;

            case _MHL_ABORT_REPLY: // Source Reply Data Packet Instead of Control Packet

                MHLMscFIFOSendCommand( MHL_MSC_CMD_CODE_ABORT, MHL_MSC_CMD_CODE_NULL, MHL_MSC_CMD_CODE_NULL, 0, _NULL_POINTER);

                return _MHL_NG;
                
                break;

            default: // Source Reply No Packet(Timeout) or NACK

                return _MHL_NG;
                
                break;
        }
    }
//    else
//    {                
//        return _MHL_NG;
//    }
}


bool  MHLMscCheckDeviceINT(void)
{
    if(CBUS_MSC_06_get_wr_stat_irq(rtd_inl(CBUS_MSC_06_reg)) == TRUE )	
    {
        HDMI_PRINTF("[CBUS] Receive Write stat cmd=%x offset=%x  data=%x  len=%x\n" ,rtd_inl(CBUS_MSC_01_reg),rtd_inl(CBUS_MSC_02_reg),rtd_inl(CBUS_MSC_04_reg),CBUS_MSC_03_get_na_rx_len(rtd_inl(CBUS_MSC_03_reg)));  

        // Check Request To Write
	if(MSC_REG_20_get_req_wrt(rtd_inl(MSC_REG_20_reg)) == TRUE)
	{
		//HDMI_PRINTF("[CBUS_LOG]READ TX REQUEST WRT  !!! \n" );  
		if(MHLMscSendCommand( MHL_MSC_CMD_CODE_SET_INT, _MHL_REG_RCHANGE_INT, GRT_WRT) == _MHL_OK)
		{
			//write clr flag 
			rtd_maskl(MSC_REG_20_reg,~MSC_REG_20_req_wrt_mask,MSC_REG_20_req_wrt_mask);
		}
	}

        // Check 3D Request and Reply No Support For All Timings
	  if(MSC_REG_20_get_cbus_3d_req(rtd_inl(MSC_REG_20_reg)) == TRUE)
        {
            // 3D_VIC Header
            MHL_CTRL.bBuf[0] = _MHL_3D_VIC_HB;   //ADOPTER ID HIGH
            MHL_CTRL.bBuf[1] = _MHL_3D_VIC_LB;   //ADOPTER ID LOW

            // Total Entries -> 0
            MHL_CTRL.bBuf[3] = 0x00;

            // Checksum -> pData[0] ^ pData[1] ^ pData[3]
            MHL_CTRL.bBuf[2] = 0x10;

            // 3D_DTD Header
            MHL_CTRL.bBuf[4] = _MHL_3D_DTD_HB;
            MHL_CTRL.bBuf[5] = _MHL_3D_DTD_LB;

            // Total Entries -> 0
            MHL_CTRL.bBuf[7] = 0x00;

            // Checksum -> pData[0] ^ pData[1] ^ pData[3]
            MHL_CTRL.bBuf[6] = 0x11;

            if((MHLMscSendWriteBurst( _MHL_REG_SCRATCH_START, 4, MHL_CTRL.bBuf, _MHL_WRITE_BURST_WITH_REQ) == _MHL_OK) &&
               (MHLMscSendWriteBurst(_MHL_REG_SCRATCH_START, 4, &MHL_CTRL.bBuf[4], _MHL_WRITE_BURST_WITH_REQ)) == _MHL_OK)
            {
                //ScalerSetDataPortByte(P28_AC_CBUS0_CTRL_0C, _MSC_RCHANGE_INT, _BIT4);
		   rtd_maskl(MSC_REG_20_reg,~MSC_REG_20_cbus_3d_req_shift,MSC_REG_20_cbus_3d_req_shift);
            }
        }

        // Clear Flag WRT_STAT
        //rtd_maskl(CBUS_MSC_06_reg,~CBUS_MSC_06_wr_stat_irq_mask,CBUS_MSC_06_wr_stat_irq_mask);
	  rtd_outl(CBUS_MSC_06_reg,CBUS_MSC_06_wr_stat_irq_mask);

		return TRUE;
    }
	return FALSE;

}

/**************************************************************************************************************************

****************************************************************************************************************************/

void MHLSwitch( UINT8 bchannel, UINT8 benable)
{
	if(benable == TRUE)    // MHL plug in   MHL mode
	{
#if 0
		if(hdmi_in(HDMI_AFCR_reg)&MHL_CTS_TEST_ON)
		{
		_bMhl_clk_mode =  (hdmi_in(HDMI_AFCR_reg)&MHL_CTS_TEST_PP_MODE)>>30;
		HDMI_PRINTF("[MHL_LOG]CTS mode set  _bMhl_clk_mode =%x   !!!!!!! \n",_bMhl_clk_mode);	
		}
		else
		{
		//  MHLMscSendCommand( MHL_MSC_CMD_CODE_READ_DEVCAP, _VID_LINK_MODE, NULL);
		if(!_bMhl_FW_PP_24_LOCK)     MHL_SET_PP_24BIT_SWITCH();

		}
#endif

		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask|REG_MHL_CTRL_reg_z100k_enb_mask),(0));	//MHL mode
		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_mhlpow_mask),REG_MHL_CTRL_reg_mhlpow(1));	//MHL mode
		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_mhl_hdmisel_mask),0);	//MHL mode

		if(_bMhl_clk_mode)  // packedpixel mode 
		{
			rtd_maskl(MHL_DEMUX_CTRL_reg, ~(MHL_DEMUX_CTRL_mhl_en_mask|MHL_DEMUX_CTRL_mhl_pp_en_mask),MHL_DEMUX_CTRL_mhl_en_mask|MHL_DEMUX_CTRL_mhl_pp_en_mask);
			rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~(MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_mask|MHL_HDMI_MAC_CTRL_pp_mode_output_mask|MHL_HDMI_MAC_CTRL_packet_mhl_en_mask),(MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_mask|MHL_HDMI_MAC_CTRL_pp_mode_output_mask|MHL_HDMI_MAC_CTRL_packet_mhl_en_mask));
			rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~(MHL_HDMI_MAC_CTRL_xor_pixel_sel_mask),MHL_HDMI_MAC_CTRL_xor_pixel_sel(3));

			rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~CK_MOD_SEL_mask, HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_mod_sel(2));
			//HDMI_PRINTF("[MHL] MHL ppmode\n");
		}
		else                         //24bit mode mode 
		{
			rtd_maskl(MHL_DEMUX_CTRL_reg, ~(MHL_DEMUX_CTRL_mhl_en_mask|MHL_DEMUX_CTRL_mhl_pp_en_mask),MHL_DEMUX_CTRL_mhl_en_mask);
			rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~(MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_mask|MHL_HDMI_MAC_CTRL_pp_mode_output_mask|MHL_HDMI_MAC_CTRL_packet_mhl_en_mask),0);
			rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~(MHL_HDMI_MAC_CTRL_xor_pixel_sel_mask),MHL_HDMI_MAC_CTRL_xor_pixel_sel(0));

			rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~CK_MOD_SEL_mask, HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg_mod_sel(1));
			//HDMI_PRINTF("[MHL] MHL 24bit mode\n");
		}
	}
	else                            // MHL plug out  HDMI MODE 
	{
		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask|REG_MHL_CTRL_reg_z100k_enb_mask),(REG_MHL_CTRL_reg_z100k_enb_mask|REG_MHL_CTRL_reg_z300_sel_2_mask|REG_MHL_CTRL_reg_z300_sel_1_mask|REG_MHL_CTRL_reg_z300_sel_0_mask));	//HDMI mode
		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_mhlpow_mask),REG_MHL_CTRL_reg_mhlpow(0));	//HDMI mode
		rtd_maskl(REG_MHL_CTRL_reg,~(REG_MHL_CTRL_reg_mhl_hdmisel_mask),REG_MHL_CTRL_reg_mhl_hdmisel_mask);	//HDMI mode

		rtd_maskl(MHL_DEMUX_CTRL_reg, ~(MHL_DEMUX_CTRL_mhl_en_mask|MHL_DEMUX_CTRL_mhl_pp_en_mask),0);  
		// disable 100k pull to vdd 
		//HW lock channel 2
		rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_mask,0); // MHL pp mode clear
		rtd_maskl( HDMIPHY_REG_CK_9_12_reg, ~MHL_Z100K, MHL_Z100K); // turn off cbus 100k
		//clear MHL pp mode HDCP setting      
		rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~(MHL_HDMI_MAC_CTRL_ch_dec_pp_mode_en_mask|MHL_HDMI_MAC_CTRL_pp_mode_output_mask|MHL_HDMI_MAC_CTRL_packet_mhl_en_mask),0);
		rtd_maskl(MHL_HDMI_MAC_CTRL_reg,~(MHL_HDMI_MAC_CTRL_xor_pixel_sel_mask),MHL_HDMI_MAC_CTRL_xor_pixel_sel(0));

		rtd_maskl(HDMIPHY_REG_DIG_PHY_CTRL_NEW_1_reg,~CK_MOD_SEL_mask,0);
	}

}

/**************************************************************************************************************************

****************************************************************************************************************************/

void QC_CBUS(UINT8 channel)
{
	UINT32 timer1 = 0, discovery_time_pt=0, msc_time_pt=0, break_time_pt=0;
	UINT16 cbus_st = CBUS_INIT;

#if QA_BOARD	//HDMI_MHL_Sel ST_GPIO
	rtd_maskl(0xb8061100, ~_BIT12, _BIT12); 
	rtd_maskl(0xb8061108, ~_BIT12, 0); 
#else
	rtd_maskl(0xb8061100, ~_BIT9, _BIT9); 
	rtd_maskl(0xb8061108, ~_BIT9, 0); 
#endif


	CBUSSwitch(1);

	rtd_maskl(CBUS_STANDBY_04_reg,~(CBUS_STANDBY_04_disconn_irq_en_mask|CBUS_STANDBY_04_cbus_disconn_mask),(CBUS_STANDBY_04_cbus_disconn_mask)); // qc only
	HDMI_PRINTF("[CBUS] Please connecting MHL source, waiting.....%s\n", CTS_TEST?"(CTS Mode)":"");
	break_time_pt = timer1;

	while(1)
	{
		if((rtd_inl(CBUS_STANDBY_04_reg)&(CBUS_STANDBY_04_cbus_disconn_mask)) == ( CBUS_STANDBY_04_cbus_disconn_mask))
		{
			rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,   //Z0
						~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask), 
						(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(0x00)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(0x00)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(0x00)));
			rtd_maskl(HDMIPHY_REG_CK_9_12_reg,~MHL_Z100K, MHL_Z100K);	 //disable   100k res //Sirius

        		//rtd_maskl(CBUS_STANDBY_02_reg,~(CBUS_STANDBY_02_dis_deb_lv_mask),0);

        		rtd_maskl(CBUS_STANDBY_04_reg,~(CBUS_STANDBY_04_disconn_irq_en_mask|CBUS_STANDBY_04_cbus_disconn_mask),(CBUS_STANDBY_04_cbus_disconn_mask));
			rtd_maskl(CBUS_STANDBY_08_reg, ~(CBUS_STANDBY_08_goto_sink1_mask),(CBUS_STANDBY_08_goto_sink1_mask) );
			rtd_maskl(CBUS_STANDBY_00_reg,~(CBUS_STANDBY_00_dis_pulse_det_mask|CBUS_STANDBY_00_wake_pulse_det_mask),(CBUS_STANDBY_00_dis_pulse_det_mask|CBUS_STANDBY_00_wake_pulse_det_mask));
			cbus_st = CBUS_INIT;
			break_time_pt = timer1;
			HDMI_PRINTF("[CBUS] disconnected!\n");
		}
		
		//wait wake up pulse 
		if ( cbus_st==CBUS_INIT )
		{
			if((rtd_inl(CBUS_STANDBY_00_reg)&(CBUS_STANDBY_00_wake_pulse_det_mask)) == (  CBUS_STANDBY_00_wake_pulse_det_mask) ) // wake up  occurs
	    		{
	        		rtd_outl(CBUS_STANDBY_00_reg, CBUS_STANDBY_00_wake_pulse_det_mask); //Sirius
	        		cbus_st = CBUS_WAKE;
				break_time_pt = timer1;
	        		HDMI_PRINTF("[CBUS] wake up pulse!\n");
	    		}
		}
		
		//wait discovery pulse 
		if ( cbus_st==CBUS_WAKE )
		{
			if((rtd_inl(CBUS_STANDBY_00_reg)&(CBUS_STANDBY_00_dis_pulse_det_mask)) == (CBUS_STANDBY_00_dis_pulse_det_mask ))   // discovery occurs
	    		{
	    			rtd_maskl(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg,   //Z0
						~(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow_mask|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow_mask), 
						(HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_b_z0pow(0x07)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_g_z0pow(0x07)|HDMIPHY_REG_BANDGAP_Z0_CTRL_2_reg_r_z0pow(0x07)));
				rtd_maskl(HDMIPHY_REG_CK_9_12_reg,~MHL_Z100K, 0);	 //enable   100k res //Sirius

	        		rtd_maskl(CBUS_STANDBY_00_reg,~(CBUS_STANDBY_00_dis_pulse_det_mask|CBUS_STANDBY_00_wake_pulse_det_mask),(CBUS_STANDBY_00_dis_pulse_det_mask|CBUS_STANDBY_00_wake_pulse_det_mask));

	        		rtd_maskl(CBUS_STANDBY_02_reg,~(CBUS_STANDBY_02_dis_deb_lv_mask),0);
	        		// Enable Stuck Low IRQ and Clear Flag
	        		rtd_maskl(CBUS_STANDBY_04_reg,~(CBUS_STANDBY_04_disconn_irq_en_mask|CBUS_STANDBY_04_cbus_disconn_mask),(CBUS_STANDBY_04_disconn_irq_en_mask|CBUS_STANDBY_04_cbus_disconn_mask));

				cbus_st = CBUS_DISCOVERY;
		  		HDMI_PRINTF("[CBUS] discovery done!\n");
				udelay(10000);
				break_time_pt = timer1;
				discovery_time_pt  = timer1;
	    		}
		}
		
		//SEND HPD command 
		if ( cbus_st==CBUS_DISCOVERY && (abs(timer1-discovery_time_pt)>300) )
		{
			if(MHLMscSendCommand( MHL_MSC_CMD_CODE_SET_HPD, MHL_MSC_CMD_CODE_NULL, MHL_MSC_CMD_CODE_NULL) == _MHL_OK)
	    		{
	    			cbus_st = CBUS_SETHPD;
				break_time_pt = timer1;
				HDMI_PRINTF("[CBUS] sent set_hpd\n");
	    		}
		    	else
	    		{
				HDMI_PRINTF("[CBUS] MHL_SET_HPD FAIL!!!!!  \n" );
	    		}
			udelay(10000);
			discovery_time_pt  = timer1;
		}
		
		//SEND path enable command 
		if ( cbus_st==CBUS_SETHPD )
		{
			if(MHLMscSendCommand( MHL_MSC_CMD_CODE_WRT_STAT, _MHL_REG_LINK_MODE, LINK_MODE_PATH_EN) == _MHL_OK)
			{
				cbus_st = CBUS_PATHEN;
				break_time_pt = timer1;
				HDMI_PRINTF("[CBUS] sent path_en, MHL is connected successfully\n");
			}
			else
			{
				HDMI_PRINTF("[CBUS]  PATH_EN FAIL!!!!!  \n" ); 
			}
			udelay(10000);
	    	}

		//
	      if ( cbus_st==CBUS_PATHEN )
	      	{
	     	 	if(MHLMscSendCommand(MHL_MSC_CMD_CODE_WRT_STAT, _MHL_REG_CONNECTED_RDY, CONNECT_DCAP_RDY) == _MHL_OK)
	            	{
	            		rtd_maskl(HDMIPHY_REG_CK_9_12_reg,~MHL_Z100K, MHL_Z100K); //disable 100k
				cbus_st = CBUS_READY;
				break_time_pt = timer1;
	     			HDMI_PRINTF("[CBUS] sent dcap, ver=%x\n", rtd_inl(MSC_REG_01_reg));
	            	}
			else
			{
		      		HDMI_PRINTF("[CBUS] MHL DEV CAP RDY FAIL!!!!!  \n" ); 
			}
			udelay(10000);
	      	}
		
		if ( cbus_st == CBUS_READY || cbus_st==CBUS_PATHEN )
		{
			if ( abs(timer1-msc_time_pt)>100 )
			{
				if ( MHLMscCheckDeviceINT() ) {
					break_time_pt = timer1;
				}
				msc_time_pt = timer1;
			}
		}

#if CTS_TEST==1
		// ----- 4.3.17.2 ------------------------
		if ( SEND_CLR_HPD() && cbus_st == CBUS_READY )
		{
			//CLEAR_CLR_HPD();
			if(MHLMscSendCommand( MHL_MSC_CMD_CODE_CLR_HPD, MHL_MSC_CMD_CODE_NULL, MHL_MSC_CMD_CODE_NULL) == _MHL_OK)
			{
				cbus_st = CBUS_CLRHPD;
				break_time_pt = timer1;
				HDMI_PRINTF("[CBUS] sent clr_hpd\n");
//				rtd_maskl(0xb8061100, ~_BIT10, 0);
				udelay(10000);
			}
		}
//		if ( SEND_SET_HPD() && cbus_st == CBUS_CLRHPD )
//		{
//			//CLEAR_SET_HPD();
//			if(MHLMscSendCommand( MHL_MSC_CMD_CODE_SET_HPD, MHL_MSC_CMD_CODE_NULL, MHL_MSC_CMD_CODE_NULL) == _MHL_OK)
//			{
//				cbus_st = CBUS_SETHPD;
//				HDMI_PRINTF("[CBUS] sent set_hpd from clr_hpd\n");
//				udelay(10000);
//			}
//		}
		// ----- 4.3.17.2 ------------------------

#else
		if ( abs(timer1-break_time_pt) > LOOP_TIMEOUT )
		{
			break; //quit if no command in timeout
		}
#endif

		udelay(1000); //loop takes at least 1ms
		timer1++;
		
	}
	//
	//mdelay(9000);
	if(MSC_REG_31_get_clk_mode(rtd_inl(MSC_REG_31_reg)) == PPmode)  
		_bMhl_clk_mode = 1;		
 	else                                                                                     
  		_bMhl_clk_mode = 0;
	
}


bool QC_Mhl_Main(UINT8 channel)
{
    bool crc_result=FALSE;
    UINT32 b;

    drvif_Hdmi_Init();

    if ( get_Koffset_result()!=0 )
    {
        printk("[HDMI] WARNING: Koffset result fail\n");
#if CheckKoffSetError
        return FALSE;
#endif
    }

    drvif_Hdmi_InitSrc(channel);

    if ( CBUS_EN )
    {
        QC_CBUS(channel);
    }
    else
    {
        _bMhl_clk_mode = (ForcePacketPixelMode)?1:0;
        Cbus_Power(1);
    }
    MHLSwitch(channel, 1);

#if KEEP_WAITING_DATA
    HDMI_PRINTF("[MHL] Waiting for data in...(press 'x' to quit)\n");
    do {
        b = HdmiMeasureVedioClock();
        if ( GETCHAR_x ) {
            break;
        }
    }while (b<100);
#else
    b = HdmiMeasureVedioClock();
#endif

    if ( b>100 ) {
        SetupMHLTMDSPhy(b, 0);
        mdelay(10);
        Hdmi_DetectMode(b);
    //        HDMI_PRINTF("[MHL] TMDS clock = %dMHz\n", (b*27)>>8);
    }

#if Audio_Output_Setting	
    Hdmi_AudioModeDetect();
#endif

#ifdef MHL_DisplayPanel
    if (_BIT31&(~ rtd_inl(HDMIPHY_REG_CK_9_12_reg)))
    {
        rtd_maskl(SOFT_RESET3_reg,~(RSTN_TVSB2|RSTN_DISPIM|RSTN_DISP),(RSTN_TVSB2|RSTN_DISPIM|RSTN_DISP));		//CRT
        rtd_maskl(CLOCK_ENABLE1_reg,~CLKEN_DCU,CLKEN_DCU);		//CRT
        rtd_maskl(SOFT_RESET3_reg,~(CLKEN_TVSB2|CLKEN_DISPIM|CLKEN_DISP),(CLKEN_TVSB2|CLKEN_DISPIM|CLKEN_DISP));		//CRT
#if HDMI_DisplayPanel==HDMI_1080p
		#include "1080p/case18_hdmi1080p_frc_fhd.tbl" 
#elif HDMI_DisplayPanel==HDMI_1080i
		#include "1080i/case2_hdmipg1080i_frc_fhd.tbl" 
#endif
    }
#endif

    crc_result = QC_CRCCheck();
    printk("[MHL] Port%d TMDS clock = %03dMHz, CRC checked: %s\n", channel, (b*27+128)>>8, crc_result?"PASS":"FAIL!");
    HDMI_PRINTF("[MHL] ==================================================\n\n");

    return crc_result;
}

bool IsMHLPortEnable(UINT8 pt)
{
	if ( pt==0 ) {
		return (MPort0!=0);
	}
	else if ( pt==1 ) {
		return (MPort1!=0);
	}
	else {
		return (MPort2!=0);
	}
}

int QC_Verifier_MHL(void)
{
    int Result = SUCCESS;
    bool test_flag = TRUE;
    UINT16  i=0,j=0;

    printk("Sirius MHL Rx QC Test\n");
    adc_init(0, 1);

    for ( i=0; i<HDMI_QCloop; i++ )
    {
        printk("[MHL] LOOP=#%d\n", i+1);
        for ( j=0; j<3; j++ )
        {
            if ( IsMHLPortEnable(j) )
            {
                test_flag &= QC_Mhl_Main(j);
            }
        }
#if LOOP_ERROR_BREAK
        if ( !test_flag )
        {
            break;
        }
#endif
    }

    if ( !test_flag )
    {
        Result = FAILED;
    }

    return Result;
}


UINT8 MHL_IsPPMode(void)
{
	return _bMhl_clk_mode;
}

