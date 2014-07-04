#ifndef _RTD_TYPES_H
#include <rtd_types_qc.h>
#endif

#include "ifd_driver.h"

extern bool g_scan_flag;
extern UINT8 g_scan_curr_audio_std;
extern UINT8 g_curr_audio_std;

ATV_TUNER_MODULE *pTuner;
IFD_MSG_LEVEL g_ifd_msg_level;

//=================================================================
/**
 * drv_ifd_pointer_check
 *
 *
 * @param { void }
 * @return { bool }
 */
bool drv_ifd_pointer_check(void)
{
	if(pTuner == NULL)
	{
		IFD_DEBUG_MSG(IFD_MSG_OTHERS,"pTuner is NULL\n");
		return _FALSE;
	}
	return _TRUE;
}
#if 1//carol

void drv_ifd_display_init(void)
{
               
}
//=================================================================
//IFD local driver
//=================================================================
//=================================================================
/**
 * drv_ifd_system_init
 *
 *
 * @param <void>
 * @return { void }
 */
void drv_ifd_system_init(void)
{
	//g_curr_std = 0xff;
	//g_curr_audio_std = 0xff;

	//g_scan_curr_std = 0xff;
	//g_scan_curr_audio_std = 0xff;

	//g_afc_ongoing=0;
	//g_afc_stage_count=0;
	//g_afc_curr_freq=0;
	//g_afc_center_freq=0;
	//g_afc_direction=0;
}
//=================================================================
/**
 * drv_ifd_get_cr_offset_100hz
 *
 *
 * @param <void>
 * @return <offset>
 */
INT32 drv_ifd_get_cr_offset_100hz(UINT8 afc)   //drvif
{
	UINT32 ifd_offset = 0, curr_freq=0, curr_freq_opti=0;
	INT32 shift_freq, rf_shift;
	INT32 divider_offset=0;
	UINT8 in_afc;
	UINT16 Ratio=0;
	UINT32 curTunerIFVal=0;

	//IFD_DEBUG_MSG(IFD_MSG_SCANCH, "drv_ifd_get_cr_offset_100hz()\n");
	
	if(drv_ifd_pointer_check() == _FALSE) return 0;

	pTuner->GetRatioInStepSize(pTuner, &Ratio);
	pTuner->GetIfFreqHz(pTuner, &curTunerIFVal);

	if(g_scan_flag==IFD_ENABLE)
	{
		pTuner->GetRfFreqHz(pTuner, &curr_freq);
	}
	else
	{
		pTuner->GetRfFreqHz(pTuner, &curr_freq);
	}
	//IFD_DEBUG_MSG(IFD_MSG_OTHERS, "curr_freq=%d\n", curr_freq);
	curr_freq_opti = ((UINT16)((curr_freq + (UINT32)curTunerIFVal) / (UINT32)Ratio))*Ratio-curTunerIFVal;
	//IFD_DEBUG_MSG(IFD_MSG_OTHERS, "curr_freq_opti=%d\n", curr_freq_opti);
	rf_shift = curr_freq_opti - curr_freq;
	//IFD_DEBUG_MSG(IFD_MSG_OTHERS, "rf_shift=%d\n", rf_shift);

	if(Ratio==0)
	{
		//IFD_DEBUG_MSG(IFD_MSG_OTHERS, "RatioInStepSize is 0.\n");
		return 0;
	}
	
	in_afc = afc;
	ifd_offset = drv_ifd_get_cr_freq_offset();
	ifd_offset = ifd_offset>>8;
	if(curTunerIFVal>270000)
	{
		if(ifd_offset > 2048) {
			shift_freq =  -(((4096-ifd_offset)*54000)>>16);  //kHz
			divider_offset = (shift_freq*10-((UINT16)Ratio/2)) /(UINT16)Ratio;
		} else {
			shift_freq = (ifd_offset*54000)>>16;  //kHz
			divider_offset = (shift_freq*10+((UINT16)Ratio/2)) /(UINT16)Ratio;
		}
	}
	else
	{
		if(ifd_offset > 2048) {
			shift_freq =  -(((4096-ifd_offset)*54000)>>16);  //kHz
			shift_freq = - shift_freq;
			divider_offset = (shift_freq*10+((UINT16)Ratio/2)) /(UINT16)Ratio;
		} else {
			shift_freq = (ifd_offset*54000)>>16;  //kHz
			shift_freq = - shift_freq;
			divider_offset = (shift_freq*10-((UINT16)Ratio/2)) /(UINT16)Ratio;
		}
	}
	divider_offset = divider_offset*Ratio;
	//IFD_DEBUG_MSG(IFD_MSG_OTHERS, "divider_offset*Ratio=%d\n", divider_offset);
	divider_offset = rf_shift+divider_offset;
	IFD_DEBUG_MSG(IFD_MSG_OTHERS, "comp=>divider_offset=%d\n", divider_offset);
	return divider_offset;

}
//=================================================================
/**
 * drv_ifd_cal_nco
 *
 *
 * @param {pif_freq}
 * @return {nco_value}
 */
UINT32 drv_ifd_cal_nco(UINT32 pif_freq)
{
	UINT32 nco_value;
	
	if(pif_freq > 270000) {
		pif_freq = 540000-pif_freq;
	}
	nco_value = ((UINT32)(pif_freq)/100);
	nco_value <<= 20;
	nco_value = nco_value/5400;
	
	return ((UINT32)(nco_value & 0x0fffff));

}

//=================================================================
/**
 * drv_ifd_clamp_reset
 *
 *
 * @param {void}
 * @return {void}
 */
void drv_ifd_clamp_reset(IFD_CLAMP_RESET_POLARITY polarity)
{
	if(polarity == IFD_CLAMP_RESET_POS)
	{
	       drv_ifd_set_clamping_thr_max(IFD_CLAMP_MID_THD_POS);
	       drv_ifd_set_clamping_thr_min(IFD_CLAMP_MID_THD_POS);
	       ScalerTimer_DelayXms(1);
		drv_ifd_clamp_offset_hold(IFD_CLAMP_OFFSET_HOLD);
		ScalerTimer_DelayXms(1);
		drv_ifd_clamp_offset_hold(IFD_CLAMP_OFFSET_NORMAL);
	       drv_ifd_set_clamping_thr_max(IFD_CLAMP_MAX_THD);
	       drv_ifd_set_clamping_thr_min(IFD_CLAMP_MIN_THD);
	}
	else
	{
	       drv_ifd_set_clamping_thr_max(IFD_CLAMP_MID_THD_NEG);
	       drv_ifd_set_clamping_thr_min(IFD_CLAMP_MID_THD_NEG);
	       ScalerTimer_DelayXms(1);
		drv_ifd_clamp_offset_hold(IFD_CLAMP_OFFSET_HOLD);
		ScalerTimer_DelayXms(1);
		drv_ifd_clamp_offset_hold(IFD_CLAMP_OFFSET_NORMAL);
	       drv_ifd_set_clamping_thr_max(IFD_CLAMP_MAX_THD);
	       drv_ifd_set_clamping_thr_min(IFD_CLAMP_MIN_THD);
	}

}

//=================================================================
/**
 * drv_ifd_agc_polarity
 *
 *
 * @param {polarity}
 * @return {void}
 */
void drv_ifd_agc_polarity(TUNER_AGCPOLARITY_SEL polarity)
{
	switch (polarity)
	{
		default :
		case TUNER_RF_POS_IF_POS :
			drv_ifd_agc_polar_inv(IFD_DISABLE);
		break;
		case TUNER_RF_POS_IF_NONE :
			drv_ifd_agc_polar_inv(IFD_DISABLE);
		break;
		case TUNER_RF_POS_IF_NEG : // set rf, if individually
			drv_ifd_agc_out_inv(IFD_DISABLE, IFD_ENABLE);
		break;
		case TUNER_RF_NONE_IF_POS :
			drv_ifd_agc_polar_inv(IFD_DISABLE);
		break;
		case TUNER_RF_NONE_IF_NONE :
			drv_ifd_agc_polar_inv(IFD_DISABLE);
		break;
		case TUNER_RF_NONE_IF_NEG : // polarity inverse
			drv_ifd_agc_polar_inv(IFD_ENABLE);
		break;
		case TUNER_RF_NEG_IF_POS : // set rf, if individually
			drv_ifd_agc_out_inv(IFD_ENABLE, IFD_DISABLE);
		break;
		case TUNER_RF_NEG_IF_NONE : // polarity inverse
			drv_ifd_agc_polar_inv(IFD_ENABLE);
		break;
		case TUNER_RF_NEG_IF_NEG : // polarity inverse
			drv_ifd_agc_polar_inv(IFD_ENABLE);
		break;
	}
}
//=================================================================
/**
 * drv_ifd_set_video_ntsc
 *
 *
 * @param {void}
 * @return {void}
 */
void drv_ifd_set_video_ntsc(void)
{
	UINT32 curTunerIFVal=0, test_if=0;


	if(g_scan_flag)
	{
		pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_NTSC, TUNER_ATV_AUDIO_MODE_MN);
		curTunerIFVal = GET_ATV_TUNER_PIF_MN();
		IFD_DEBUG_MSG(IFD_MSG_SCANCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);		
		pTuner->GetIfFreqHz(pTuner, &test_if);
		IFD_DEBUG_MSG(IFD_MSG_SCANCH, "test_if=%d\n", (UINT32)test_if);
		if(curTunerIFVal<270000) 
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		}
		else
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		}
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_MN());
		drv_ifd_set_cr_bpf_coef(IFD_ENABLE, GET_ATV_IFD_CRBPF_TABLE_MN());
		drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));
	}
	else
	{
		pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_NTSC, TUNER_ATV_AUDIO_MODE_MN);
	
		curTunerIFVal = GET_ATV_TUNER_PIF_MN();
		IFD_DEBUG_MSG(IFD_MSG_SETCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);

		if(curTunerIFVal<270000)
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		}
		else
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		}
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_MN());
		drv_ifd_set_cr_bpf_coef(IFD_ENABLE, GET_ATV_IFD_CRBPF_TABLE_MN());
		drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));
	}
	
	drv_ifd_input_filter_sel(GET_ATV_IFD_INPUTFLTNTSC_EN(), GET_ATV_IFD_INPUTFLTTABLENTSC());
	drv_ifd_outputlpf_vsync(IFD_OUTPUTLPF_VSYNC_START_NTSC, IFD_OUTPUTLPF_VSYNC_END_NTSC);
	drv_ifd_video_outputlpf_coef_update(IFD_ENABLE,GET_ATV_IFD_VIDEOLPFNTSC());
	drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL_NTSC);
	drv_ifd_set_shaping_filter(GET_ATV_IFD_SHAPEFILTER_BW());
	drv_ifd_set_pos_neg_mod(IFD_MODULATION_SEL_NEG);
	drv_ifd_cr_vsync(IFD_CR_VSYNC_START_NTSC, IFD_CR_VSYNC_END_NTSC); //cr vsync

	if(g_scan_flag)
	{
		drv_ifd_eq_en(0);
	}
	else
	{
		drv_ifd_set_eq_coef(GET_ATV_IFD_EQ_TABLE_NTSC());
		drv_ifd_eq_en(1);
	}
	

	drv_ifd_agc_loop1_pos_en(IFD_DISABLE);
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() );
	drv_ifd_agc_data_target(GET_ATV_IFD_AGCDATATARG());
	drv_ifd_mtd_set_thr(0x7, GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() >>1, (GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() >>1)-0x30);
	drv_ifd_agc_hsync_start1(IFD_VSmode1_Hstart_NTSC, IFD_VSmode1_Hend_NTSC);
	drv_ifd_agc_vsync_start1(IFD_VSmode1_Vstart_NTSC, IFD_VSmode1_Vend_NTSC); //irene ok// irene has to check why w/o vsync_start2/hsync_start2
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, 0x000000FE);  //agc enable
       drv_ifd_agc_loop1_fine_tune_en(IFD_DISABLE);
	if(g_curr_audio_std==0xff)
		drv_ifd_grp_delay_en (GET_ATV_IFD_GRPDELAYM_EN(),  GET_ATV_IFD_GRPDELAYTABLEM());//drv_ifd_group_delay_coe_table(GET_IFD_GRPDEALY_M());
}
void drv_ifd_set_video_ntsc_dk(void)
{
	UINT32 curTunerIFVal=0;


	if(g_scan_flag)
	{
		pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_SCAN, TUNER_ATV_AUDIO_MODE_DK);
		curTunerIFVal = GET_ATV_TUNER_PIF_SCAN();
		IFD_DEBUG_MSG(IFD_MSG_SCANCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);

		if(curTunerIFVal<270000) 
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		}
		else
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		}
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_SCAN());
		drv_ifd_set_cr_bpf_coef(IFD_ENABLE, GET_ATV_IFD_CRBPF_TABLE_SCAN());
		drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));
	}
	else
	{
		pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_NTSC, TUNER_ATV_AUDIO_MODE_DK);
		curTunerIFVal = GET_ATV_TUNER_PIF_DK();
		IFD_DEBUG_MSG(IFD_MSG_SETCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);

		if(curTunerIFVal<270000) 
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		}
		else
		{
			if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
			else
				drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		}
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_IDKL());
		drv_ifd_set_cr_bpf_coef(IFD_ENABLE, GET_ATV_IFD_CRBPF_TABLE_DK());
		drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));
	}
	drv_ifd_input_filter_sel(GET_ATV_IFD_INPUTFLTPALD_EN(), GET_ATV_IFD_INPUTFLTTABLEPALD());
	drv_ifd_outputlpf_vsync(IFD_OUTPUTLPF_VSYNC_START_NTSC, IFD_OUTPUTLPF_VSYNC_END_NTSC);
	drv_ifd_video_outputlpf_coef_update(IFD_ENABLE,GET_ATV_IFD_VIDEOLPFNTSC());
	drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL_NTSC/*(IFD_UPSAMPLE_LP_SEL)GET_IFD_VIDEOUPSAMPLE_LPF_NTSC()*/);
	drv_ifd_set_shaping_filter(GET_ATV_IFD_SHAPEFILTER_BW());
	drv_ifd_set_pos_neg_mod(IFD_MODULATION_SEL_NEG);
	drv_ifd_cr_vsync(IFD_CR_VSYNC_START_NTSC, IFD_CR_VSYNC_END_NTSC); //cr vsync

	if(g_scan_flag)
	{
		drv_ifd_eq_en(0);
	}
	else
	{
		drv_ifd_set_eq_coef(GET_ATV_IFD_EQ_TABLE_NTSC());
		drv_ifd_eq_en(1);
	}
	

	drv_ifd_agc_loop1_pos_en(IFD_DISABLE);
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() );
	drv_ifd_agc_data_target(GET_ATV_IFD_AGCDATATARG() );
	drv_ifd_mtd_set_thr(0x7, GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() >>1, (GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() >>1)-0x30);
	drv_ifd_agc_hsync_start1(IFD_VSmode1_Hstart_NTSC, IFD_VSmode1_Hend_NTSC);
	drv_ifd_agc_vsync_start1(IFD_VSmode1_Vstart_NTSC, IFD_VSmode1_Vend_NTSC); //irene ok// irene has to check why w/o vsync_start2/hsync_start2
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, 0x000000FE);  //agc enable
       drv_ifd_agc_loop1_fine_tune_en(IFD_DISABLE);
	if(g_curr_audio_std==0xff)
		drv_ifd_grp_delay_en (GET_ATV_IFD_GRPDELAYM_EN(),  GET_ATV_IFD_GRPDELAYTABLEM());//drv_ifd_group_delay_coe_table(GET_IFD_GRPDEALY_M());
}
//=================================================================
/**
 * drv_ifd_set_video_pal
 *
 *
 * @param <mode>
 * @return {void}
 */
void drv_ifd_set_video_pal(void)
{
	UINT32 curTunerIFVal=0;

	if(g_scan_flag)
	{	
		if (g_scan_curr_audio_std==TUNER_ATV_AUDIO_MODE_B)
		{
			pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_SCAN, TUNER_ATV_AUDIO_MODE_B);
			curTunerIFVal = GET_ATV_TUNER_PIF_B();
		}
		else
		{
			pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_SCAN, TUNER_ATV_AUDIO_MODE_UNKNOWN);
			curTunerIFVal = GET_ATV_TUNER_PIF_SCAN();
		}
		IFD_DEBUG_MSG(IFD_MSG_SCANCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);
		drv_ifd_set_cr_bpf_coef(IFD_ENABLE,  GET_ATV_IFD_CRBPF_TABLE_SCAN()/*stCrBpfArray[g_curIFMapIdx].CrBpf_Table*/);
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_SCAN());
	}
	else
	{
		pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_PAL, TUNER_ATV_AUDIO_MODE_DK);
		curTunerIFVal = GET_ATV_TUNER_PIF_DK();
		IFD_DEBUG_MSG(IFD_MSG_SETCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);
		drv_ifd_set_cr_bpf_coef(IFD_ENABLE,  GET_ATV_IFD_CRBPF_TABLE_DK()/*stCrBpfArray[g_curIFMapIdx].CrBpf_Table*/);
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_IDKL());
	}
	
	drv_ifd_outputlpf_vsync(IFD_OUTPUTLPF_VSYNC_START_PAL, IFD_OUTPUTLPF_VSYNC_END_PAL);
	drv_ifd_cr_vsync(IFD_CR_VSYNC_START_PAL, IFD_CR_VSYNC_END_PAL); //cr vsync
	drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));

	if(g_scan_flag)
	{
		drv_ifd_eq_en(0);
	}
	else
	{
		drv_ifd_set_eq_coef(GET_ATV_IFD_EQ_TABLE_PAL_DKL());
		drv_ifd_eq_en(1);
	}
	drv_ifd_set_shaping_filter(GET_ATV_IFD_SHAPEFILTER_BW());

	if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
	{
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
	}
	else
	{
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
	}
	drv_ifd_input_filter_sel(GET_ATV_IFD_INPUTFLTPALD_EN(), GET_ATV_IFD_INPUTFLTTABLEPALD());
	drv_ifd_set_pos_neg_mod(IFD_MODULATION_SEL_NEG);
	drv_ifd_video_outputlpf_coef_update(IFD_ENABLE,GET_ATV_IFD_VIDEOLPFPAL_BG());
	drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL_PAL/*(IFD_UPSAMPLE_LP_SEL)GET_IFD_VIDEOUPSAMPLE_LPF_PAL()*/);
	drv_ifd_agc_loop1_pos_en(IFD_DISABLE);
	drv_ifd_agc_hsync_start1(IFD_VSmode1_Hstart_PAL, IFD_VSmode1_Hend_PAL);
	drv_ifd_agc_vsync_start1(IFD_VSmode1_Vstart_PAL, IFD_VSmode1_Vend_PAL);
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETPAL());
	drv_ifd_agc_data_target(GET_ATV_IFD_AGCDATATARG());
	drv_ifd_mtd_set_thr(0x7, GET_ATV_IFD_AGCLOOP1_MAXTARGETPAL()>>1, (GET_ATV_IFD_AGCLOOP1_MAXTARGETPAL()>>1)-0x30);
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, 0x000000FE);
        drv_ifd_agc_loop1_fine_tune_en(IFD_DISABLE);
	if(g_curr_audio_std==0xff)
		drv_ifd_grp_delay_en (GET_ATV_IFD_GRPDELAYDKL_EN(),  GET_ATV_IFD_GRPDELAYTABLEDKL());//drv_ifd_group_delay_coe_table(GET_IFD_GRPDEALY_DKL());
}
//=================================================================
/**
 * drv_ifd_set_video_secaml
 *
 *
 * @param {void}
 * @return {void}
 */
void drv_ifd_set_video_secaml(void)
{
	UINT32 curTunerIFVal=0;

	pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_SECAM, TUNER_ATV_AUDIO_MODE_L);
	curTunerIFVal = GET_ATV_TUNER_PIF_L();
	IFD_DEBUG_MSG(IFD_MSG_SCANCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);
	IFD_DEBUG_MSG(IFD_MSG_SETCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);

	if(curTunerIFVal<270000) 
	{
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_IDKL());
	}
	else
	{
	}
	
	//#ifdef CONFIG_IFD_CRBPF_NEW
	drv_ifd_input_filter_sel(GET_ATV_IFD_INPUTFLTPALD_EN(), GET_ATV_IFD_INPUTFLTTABLEPALD());
	drv_ifd_outputlpf_vsync(IFD_OUTPUTLPF_VSYNC_START_SECAM, IFD_OUTPUTLPF_VSYNC_END_SECAM);
	drv_ifd_set_cr_bpf_coef(IFD_ENABLE,  GET_ATV_IFD_CRBPF_TABLE_L()/*stCrBpfArray[g_curIFMapIdx].CrBpf_Table*/);
	//#else
	//Set CR BPF according by PIF.
	//drv_ifd_initdata_by_tuner_if();
	//drv_ifd_set_cr_bpf_coef(IFD_ENABLE,  stCrBpfArray[g_curIFMapIdx].CrBpf_Table);
	//#endif
	//Set CR nco according by PIF.
	drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));
       drv_ifd_cr_vsync(IFD_CR_VSYNC_START_SECAM, IFD_CR_VSYNC_END_SECAM); //cr vsync
	drv_ifd_eq_en(0);

	drv_ifd_set_shaping_filter(GET_ATV_IFD_SHAPEFILTER_BW());

	if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG)
	{
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
	}
	else
	{
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
	}
	drv_ifd_set_pos_neg_mod(IFD_MODULATION_SEL_POS);
	//#ifdef CONFIG_OUTPUTLPF_COEF_MODIFY_USE
	drv_ifd_video_outputlpf_coef_update(IFD_ENABLE,GET_ATV_IFD_VIDEOLPFSECAM());
	//#else
	//drv_ifd_set_video_bw((IFD_VIDEO_BW_SEL)GET_IFD_VIDEOBPF_SECAM());//drv_ifd_set_video_audio_nf_bw(GET_IFD_VIDEOBPF_SECAM(), GET_IFD_AUDIOBPF_NF2SECAM(), GET_IFD_AUDIOBPF_NF1SECAM(), GET_IFD_VIDEOUPSAMPLE_LPF_SECAM());
	//#endif
	drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL_PAL/*(IFD_UPSAMPLE_LP_SEL)GET_IFD_VIDEOUPSAMPLE_LPF_SECAM()*/);
	drv_ifd_agc_loop1_pos_en(IFD_ENABLE);
	//drv_ifd_agc_loop2_pos_en(IFD_ENABLE); // irene have to check
	drv_ifd_agc_hsync_start1(IFD_VSmode1_Hstart_SECAM, IFD_VSmode1_Hend_SECAM);
	drv_ifd_agc_vsync_start1(IFD_VSmode1_Vstart_SECAM, IFD_VSmode1_Vend_SECAM);
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETSECAM());
	drv_ifd_agc_data_target(GET_ATV_IFD_AGCDATATARG());
	drv_ifd_mtd_set_thr(0x7, GET_ATV_IFD_AGCLOOP1_MAXTARGETSECAM()>>1, (GET_ATV_IFD_AGCLOOP1_MAXTARGETSECAM()>>1)-0x30);
	//drv_ifd_agc_loop2_target(GET_IFD_AGCLOOP2_MAXTARGET_SECAM());
	//drv_ifd_agc_hsync_start2(IFD_VSmode2_Hstart_SECAM, IFD_VSmode2_Hend_SECAM);
	//drv_ifd_agc_vsync_start2(IFD_VSmode2_Vstart_SECAM, IFD_VSmode2_Vend_SECAM);
       drv_ifd_agc_loop1_fine_tune_en(IFD_ENABLE);
       //drv_ifd_agc_loop2_fine_tune_en(IFD_ENABLE);
	if(g_curr_audio_std==0xff)
		drv_ifd_grp_delay_en (GET_ATV_IFD_GRPDELAYDKL_EN(),  GET_ATV_IFD_GRPDELAYTABLEDKL());//drv_ifd_group_delay_coe_table(GET_IFD_GRPDEALY_DKL());
}
//=================================================================
/**
 * drv_ifd_set_video_secamla
 *
 *
 * @param {void}
 * @return {void}
 */
void drv_ifd_set_video_secamla()
{
	UINT32 curTunerIFVal=0;

	pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_SECAMLA, TUNER_ATV_AUDIO_MODE_LA);

	curTunerIFVal =  GET_ATV_TUNER_PIF_LA();
	pTuner->GetIfFreqHz(pTuner, &curTunerIFVal);
	IFD_DEBUG_MSG(IFD_MSG_SCANCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);
	IFD_DEBUG_MSG(IFD_MSG_SETCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);

	if(curTunerIFVal<270000) 
	{
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_LA());
	}
	else
	{
	}
	drv_ifd_input_filter_sel(GET_ATV_IFD_INPUTFLTPALD_EN(), GET_ATV_IFD_INPUTFLTTABLEPALD());
	drv_ifd_outputlpf_vsync(IFD_OUTPUTLPF_VSYNC_START_SECAM, IFD_OUTPUTLPF_VSYNC_END_SECAM);
	drv_ifd_set_cr_bpf_coef(IFD_ENABLE, GET_ATV_IFD_CRBPF_TABLE_LA());
	drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));
	drv_ifd_cr_vsync(IFD_CR_VSYNC_START_SECAM, IFD_CR_VSYNC_END_SECAM); //cr vsync
	drv_ifd_eq_en(0);

	drv_ifd_set_shaping_filter(GET_ATV_IFD_SHAPEFILTER_BW());

	if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_POS)
	{
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
	}
	else
	{
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
	}
	drv_ifd_set_pos_neg_mod(IFD_MODULATION_SEL_POS);
	drv_ifd_video_outputlpf_coef_update(IFD_ENABLE,GET_ATV_IFD_VIDEOLPFSECAM());
	drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL_PAL);
	drv_ifd_agc_diff_targ(GET_ATV_IFD_AGCLOOP1_DIFFTARGET());
	drv_ifd_agc_loop1_pos_en(IFD_ENABLE);
	drv_ifd_agc_hsync_start1(IFD_VSmode1_Hstart_SECAM, IFD_VSmode1_Hend_SECAM);
	drv_ifd_agc_vsync_start1(IFD_VSmode1_Vstart_SECAM, IFD_VSmode1_Vend_SECAM);
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETSECAM());
	drv_ifd_agc_data_target(GET_ATV_IFD_AGCDATATARG());
	drv_ifd_mtd_set_thr(0x7, GET_ATV_IFD_AGCLOOP1_MAXTARGETSECAM()>>1, (GET_ATV_IFD_AGCLOOP1_MAXTARGETSECAM()>>1)-0x30);
       drv_ifd_agc_loop1_fine_tune_en(IFD_ENABLE);
	if(g_curr_audio_std==0xff)
		drv_ifd_grp_delay_en (GET_ATV_IFD_GRPDELAYDKL_EN(),  GET_ATV_IFD_GRPDELAYTABLEDKL());//drv_ifd_group_delay_coe_table(GET_IFD_GRPDEALY_DKL());


}
//=================================================================
/**
 * drv_ifd_set_video_fm_radio
 *
 *
 * @param {void}
 * @return {void}
 */
void drv_ifd_set_video_fm_radio(void)
{
	UINT32 curTunerIFVal=0;

	pTuner->SetStandardMode(pTuner, TUNER_ATV_VIDEO_MODE_NTSC, TUNER_ATV_AUDIO_MODE_FM_RADIO);

	curTunerIFVal = GET_ATV_TUNER_PIF_MN();
	IFD_DEBUG_MSG(IFD_MSG_SCANCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);
	IFD_DEBUG_MSG(IFD_MSG_SETCH, "curTunerIFVal=%d\n", (UINT32)curTunerIFVal);

	if(curTunerIFVal<270000) 
	{
		//drv_ifd_input_filter_sel(IFD_INPUT_FILTER_LPF);
		//carol: drv_ifd_input_filter_sel(stIFDUserData.InputFlt**_En,  &stIFDUserData.InputFltTable**[0]);
		//drv_ifd_adc_clk_sel(IFD_CLK_RATE_108M, IFD_INPUT_DN_FILTER_108M_LPF);
		drv_ifd_set_cr_inner_lpf_sel((IFD_CR_INNER_LPF)GET_ATV_IFD_CRINNERLPF_MN());
	}
	else 
	{
		//drv_ifd_input_filter_sel(IFD_INPUT_FILTER_HPF);
		//carol: drv_ifd_input_filter_sel(stIFDUserData.InputFlt**_En,  &stIFDUserData.InputFltTable**[0]);
		//drv_ifd_adc_clk_sel(IFD_CLK_RATE_108M, IFD_INPUT_DN_FILTER_108M_HPF);
	}

	drv_ifd_input_filter_sel(GET_ATV_IFD_INPUTFLTPALD_EN(), GET_ATV_IFD_INPUTFLTTABLEPALD());

	//#ifdef CONFIG_IFD_CRBPF_NEW
	drv_ifd_set_cr_bpf_coef(IFD_ENABLE, GET_ATV_IFD_CRBPF_TABLE_MN()/*stCrBpfArray[g_curIFMapIdx].CrBpf_Table*/);
	//#else
	//Set CR BPF according by PIF.
	//drv_ifd_initdata_by_tuner_if();
	//drv_ifd_set_cr_bpf_coef(IFD_ENABLE, stCrBpfArray[g_curIFMapIdx].CrBpf_Table);
	//#endif

	//Fix CR nco according by PIF.
	drv_ifd_set_cr_nco(IFD_DISABLE, drv_ifd_cal_nco(curTunerIFVal));

	drv_ifd_eq_en(0);
	drv_ifd_set_pos_neg_mod(IFD_MODULATION_SEL_NEG);
	//#ifdef CONFIG_OUTPUTLPF_COEF_MODIFY_USE
	drv_ifd_video_outputlpf_coef_update(IFD_ENABLE,GET_ATV_IFD_VIDEOLPFNTSC());
	//#else
	//drv_ifd_set_video_bw((IFD_VIDEO_BW_SEL)GET_IFD_VIDEOBPF_NTSC());//drv_ifd_set_video_audio_nf_bw(GET_IFD_VIDEOBPF_NTSC(), GET_IFD_AUDIOBPF_NF2NTSC(), GET_IFD_AUDIOBPF_NF1NTSC(), GET_IFD_VIDEOUPSAMPLE_LPF_NTSC());
	//#endif
	drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL_NTSC/*(IFD_UPSAMPLE_LP_SEL)GET_IFD_VIDEOUPSAMPLE_LPF_NTSC()*/);
	drv_ifd_set_shaping_filter(GET_ATV_IFD_SHAPEFILTER_BW());


	if(GET_ATV_TUNER_IFTYPE()==TUNER_IF_TYPE_NEG){
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
	}
	else{
		if(curTunerIFVal<270000)
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
		else
			drv_ifd_set_shaping_img(IFD_SHAPING_IMG_POS);
	}

	drv_ifd_agc_loop1_pos_en(IFD_DISABLE);
	//drv_ifd_agc_loop2_pos_en(IFD_DISABLE); // irene's code without this, irene has to check
	//drv_ifd_agc_vsync_start2(IFD_VSmode2_Vstart_NTSC, IFD_VSmode2_Vend_NTSC);
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() );
	drv_ifd_agc_data_target(GET_ATV_IFD_AGCLOOP1_MAXTARGETNTSC() );
	//drv_ifd_agc_loop2_target(GET_IFD_AGCLOOP2_MAXTARGET_NTSC());
	drv_ifd_agc_hsync_start1(IFD_VSmode1_Hstart_NTSC, IFD_VSmode1_Hend_NTSC);
	drv_ifd_agc_vsync_start1(IFD_VSmode1_Vstart_NTSC, IFD_VSmode1_Vend_NTSC); //irene ok// irene has to check why w/o vsync_start2/hsync_start2
	//drv_ifd_agc_hsync_start2(IFD_VSmode2_Hstart_NTSC, IFD_VSmode2_Hend_NTSC);
	//drv_ifd_agc_vsync_start2(IFD_VSmode2_Vstart_NTSC, IFD_VSmode2_Vend_NTSC);
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, 0x000000FE);  //agc enable
       drv_ifd_agc_loop1_fine_tune_en(IFD_DISABLE);
       //drv_ifd_agc_loop2_fine_tune_en(IFD_DISABLE);
	drv_ifd_grp_delay_en (GET_ATV_IFD_GRPDELAYM_EN(),  GET_ATV_IFD_GRPDELAYTABLEM());//drv_ifd_group_delay_coe_table(GET_IFD_GRPDEALY_M());


	

}


//=================================================================
/**
 * drv_ifd_agc_mode_set
 *
 *
 * @param <ifdAGCmode><pga_fix_value>
 * @return { void }
 */
void drv_ifd_agc_mode_set(IFD_MODE_AGC_PGA_CONFIG ifd_agc_mode, IFD_MODE_AGC_PGA_FIXGAIN_LEVEL pga_fix_value)
{
	switch (ifd_agc_mode)
	{
		case IFD_AGC_DOUBLE_NOIFAMP_PGA :
		case IFD_AGC_2STEP_NOIFAMP_PGA :
		case IFD_AGC_DOUBLE_IFAMP_FIXPGA:
		default:
			drv_ifd_adc_input_sel(IFD_ADC_INPUT_SEL_IFPGA);
		    	break;
		case IFD_AGC_DOUBLE_IFAMP_NOPGA :
		case IFD_AGC_2STEP_IFAMP_NOPGA :
			drv_ifd_adc_input_sel(IFD_ADC_INPUT_SEL_BYPASS);
		    	break;
	}
	switch (ifd_agc_mode)
	{
		case IFD_AGC_DOUBLE_NOIFAMP_PGA:
 		case IFD_AGC_DOUBLE_IFAMP_NOPGA:
		case IFD_AGC_DOUBLE_IFAMP_FIXPGA:
			drv_ifd_agc_mode_sel(IFD_AGC_MODE_2LOOP);
		    	break;
              case IFD_AGC_2STEP_IFAMP_NOPGA:
		case IFD_AGC_2STEP_NOIFAMP_PGA:
		default:
			drv_ifd_agc_mode_sel(IFD_AGC_MODE_2STEP);
			break;
	}
	if(ifd_agc_mode==IFD_AGC_DOUBLE_IFAMP_FIXPGA) 
	{
		if(pga_fix_value<=IFD_MODE_AGC_PGA_FIXGAIN_LEVEL_2P5DB)
		{
			switch(pga_fix_value)
			{
				case -1 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_FROM_DIGITAL); break;
				case -2 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_N1DB); break;	
				case -3 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_N2DB); break;
				case -4 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_N3DB); break;
				case -5 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_N4DB); break;
				case -6 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_N5DB); break;
				case -7 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_N6DB); break;
				case -8 : drv_ifd_adc_pga_gain_fix(IFD_ENABLE, IFD_ADC_PGAFIX_CTRL_N7DB); break;
			}
			drv_ifd_agc_pga_manual_en(IFD_ENABLE,0x00);
		}
		else
		{
			drv_ifd_adc_pga_gain_fix(IFD_DISABLE,IFD_ADC_PGAFIX_CTRL_FROM_DIGITAL);
			drv_ifd_agc_pga_manual_en(IFD_ENABLE, pga_fix_value);
		}
	}
	else
	{
		drv_ifd_adc_pga_gain_fix(IFD_DISABLE, IFD_ADC_PGAFIX_CTRL_FROM_DIGITAL);
		drv_ifd_agc_pga_manual_en(IFD_DISABLE,0x00);
	}
	return;
}

void drv_ifd_specific_function_enable(bool enable)
{
	//Cr State
	drv_ifd_cr_state_en(enable);
	//Cr phase inverse enable
	drv_ifd_cr_phase_inverse_en(enable);
	//Agc Hasten

}
//=================================================================
/**
 * drv_ifd_para_change_with_tunerband
 *
 *
 * @param {void}
 * @return {void}
 */
 
void drv_ifd_para_change_with_tunerband()
{
	UINT32 curr_freq;
	UINT8 BandNo;
	pTuner->GetRfFreqHz(pTuner, &curr_freq);
	pTuner->CheckBand(pTuner, curr_freq, &BandNo);

	if(drv_ifd_get_agc_mode_sel()==IFD_AGC_MODE_2STEP)
	{
		drv_ifd_agc_2step_pga_minimum(GET_ATV_IFD_AGC_PGA_MIN(BandNo));
	}
	else
	{
		drv_ifd_agc_vtop(GET_ATV_IFD_AGCVTOP(BandNo));
		drv_ifd_agc_krf(GET_ATV_IFD_AGC_KRF(BandNo));
	}
	drv_ifd_agc_rf_max(GET_ATV_IFD_AGC_RF_MAX(BandNo));
	drv_ifd_agc_rf_min(GET_ATV_IFD_AGC_RF_MIN(BandNo));
	rtd_outl(IFD_IF_AGC_MIN_VADDR, ((GET_ATV_IFD_AGC_IF_MAX()<<16) |GET_ATV_IFD_AGC_IF_MIN()));
}

//=================================================================
/**
 * drv_ifd_set_adc_init
 *
 *
 * @param {void}
 * @return {void}
 */
void drv_ifd_set_adc_init(void)
{
	UINT32 curTunerIFVal=0;

	if(drv_ifd_pointer_check()==_FALSE) return;

	curTunerIFVal = GET_ATV_TUNER_PIF_DK();

	/////////////////////////////////////////////////////////////////////
	//Analog
	/////////////////////////////////////////////////////////////////////
	drv_ifd_power_on(IFD_ENABLE);
	drv_ifd_analog_preset();
	drv_ifd_set_adcinput_swing((IFD_ADC_SHAGAIN)GET_ATV_IFD_ADCINPUT_SHAGAIN(), (IFD_ADC_FULLSCALE)GET_ATV_IFD_ADCINPUT_FULLSCALE());
	drv_ifd_adc_clk_sel((IFD_CLK_RATE)GET_ATV_IFD_ADCINPUT_CLOCK(), (IFD_INPUT_DN_FILTER)GET_ATV_IFD_ADCINPUT_DN_FILTER_SEL());
	/////////////////////////////////////////////////////////////////////
	//Input Filter
	/////////////////////////////////////////////////////////////////////
	drv_ifd_input_filter_sel(GET_ATV_IFD_INPUTFLTPALD_EN(), GET_ATV_IFD_INPUTFLTTABLEPALD());
	/////////////////////////////////////////////////////////////////////
	//CR
	/////////////////////////////////////////////////////////////////////
	//Cr Bpf Coef.
	drv_ifd_cr_inner_lpf_en(IFD_ENABLE);
	drv_ifd_set_cr_bpf_coef(IFD_ENABLE, GET_ATV_IFD_CRBPF_TABLE_DK());
	//Cr Lock
	drv_ifd_set_cr_lock_freq_thr(IFD_CR_LOCK_OFFSET_THD_300K);
	drv_ifd_set_cr_lock_with_freq(IFD_ENABLE);
	drv_ifd_set_cr_nco(IFD_ENABLE, drv_ifd_cal_nco(curTunerIFVal));
	rtd_maskl(IFD_CR_FREQ_SAT_VADDR, ~((UINT32)0x1FFFF), IFD_CR_OFFSET_SAT);
	drv_ifd_set_cr_weighting_settings(IFD_CR_WEIGHT_CR_LOCK_ENABLE, IFD_CR_WEIGHT_MAX_DECREASE_512CYCLE, IFD_CR_WEIGHT_MAX_SHIFT_RIGHT_1BIT);
	drv_ifd_set_cr_weighting_en(IFD_ENABLE);
	drv_ifd_cr_error_thd(GET_ATV_IFD_CRLOCK_ERR_THD());
	drv_ifd_cr_auto_reset_en(IFD_ENABLE);
	drv_ifd_cr_phase_inverse_en(IFD_DISABLE);
	drv_ifd_cr_phase_inverse_st4_en(IFD_DISABLE);
	drv_ifd_cr_phase_inverse_st2_en(IFD_ENABLE);
	drv_ifd_cr_phase_inverse_st0_en(IFD_DISABLE);

	//Cr State
	drv_ifd_cr_loop_filter_kp_st3(GET_ATV_IFD_CRST3PGAIN());
	drv_ifd_cr_loop_filter_ki_st3(GET_ATV_IFD_CRST3IGAIN());
	drv_ifd_cr_loop_filter_kp_st2(GET_ATV_IFD_CRST2PGAIN());
	drv_ifd_cr_loop_filter_ki_st2(GET_ATV_IFD_CRST2IGAIN());
	drv_ifd_cr_loop_filter_kp_st0(GET_ATV_IFD_CRST0PGAIN());
	drv_ifd_cr_loop_filter_ki_st0(GET_ATV_IFD_CRST0IGAIN());
	drv_ifd_cr_loop_filter_kp(GET_ATV_IFD_CRPGAIN());
	drv_ifd_cr_loop_filter_ki(GET_ATV_IFD_CRIGAIN());
	drv_ifd_cr_st3_dn_debounce(0x2);
	drv_ifd_cr_st2_dn_debounce(0x2);
	drv_ifd_cr_st2_up_debounce(0x2);
	drv_ifd_cr_st1_dn_debounce(0x2);
	drv_ifd_cr_st1_up_debounce(0x2);
	drv_ifd_cr_st0_up_debounce(0x2);
	drv_ifd_cr_st2_freq_var_up_thr(0x50);
	drv_ifd_cr_st2_freq_var_low_thr(0x10);
	drv_ifd_cr_st4_freq_var_thr(0x30);
	drv_ifd_cr_st3_freq_var_thr(0x30);
	drv_ifd_cr_st0_phase_var_thr(0x28);
	drv_ifd_cr_st2_phase_var_thr(0x30);	
	rtd_outl(IFD_CR_PHASE_ERROR_AVG_SET_VADDR, 0x01040040); //Enable to take the cr frequency error sample in vertival sync. Area
	rtd_outl(IFD_CR_FREQ_ERROR_AVG_SET_VADDR, 0x08040040);  //Enable to take the cr frequency error sample in vertival sync. Area
	
	//cr vsync
	drv_ifd_cr_vsync(IFD_CR_VSYNC_START_PAL, IFD_CR_VSYNC_END_PAL); 
	
	//need to confirm->cr phase error avg
	
	/////////////////////////////////////////////////////////////////////
	//Shaping filter
	/////////////////////////////////////////////////////////////////////
	drv_ifd_set_shaping_filter(GET_ATV_IFD_SHAPEFILTER_BW());
	drv_ifd_set_shaping_img(IFD_SHAPING_IMG_NEG);
	rtd_maskl(IFD_POWER_CAL_VADDR, ~(_BIT8), _BIT8); //Reset
	//need to confirm->power cal for shap
	
	/////////////////////////////////////////////////////////////////////
	//Data gain
	/////////////////////////////////////////////////////////////////////
	drv_ifd_set_videopath_output_gain((IFD_VIDEOPATH_OUTPUT_GAIN)GET_ATV_IFD_DATAGAINSEL()); //data_gain => 0
	//need to confirm->data gain mask thd
	//need to confirm->data gain mask enable

	/////////////////////////////////////////////////////////////////////
	//Clamping
	/////////////////////////////////////////////////////////////////////
	drv_ifd_set_clamping_scale(IFD_CLAMP_SCALE_1D4);
	drv_ifd_set_clamping_thr_max(IFD_CLAMP_MAX_THD);
	drv_ifd_set_clamping_thr_min(IFD_CLAMP_MIN_THD);
	rtd_outl(IFD_27M_VCLAMP_IN_MIN_SAT_VADDR, 0x00001e00);

	/////////////////////////////////////////////////////////////////////
	//Video output
	/////////////////////////////////////////////////////////////////////
	drv_ifd_outputlpf_vsync(IFD_OUTPUTLPF_VSYNC_START_PAL, IFD_OUTPUTLPF_VSYNC_END_PAL);
	drv_ifd_set_54to27_decimation_enable(IFD_ENABLE);
	drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL_PAL);

	/////////////////////////////////////////////////////////////////////
	//AGC
	/////////////////////////////////////////////////////////////////////
	drv_ifd_agc_mode_set(GET_ATV_IFD_AGCPGAMODE(), GET_ATV_IFD_AGCFIXPGAVALUE());
	if(GET_ATV_IFD_AGCPGAMODE()==IFD_AGC_DOUBLE_IFAMP_FIXPGA) drv_ifd_agc_pga_manual_en(IFD_ENABLE,GET_ATV_IFD_AGCFIXPGAVALUE());
	else drv_ifd_agc_pga_manual_en(IFD_DISABLE,0x00);

	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, 0x0000009E);
	rtd_maskl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_CNTL1_VADDR, ~((UINT32)0xFFF), IFD_UNLOCK_MAX_DEC_CNT);
	rtd_maskl(IFD_AGC_MAX_COUNT_FOR_FINE_LOCK_MODE_AGC_CNTL2_VADDR,  ~((UINT32)0xFFF), IFD_UNLOCK_MAX_DEC_CNT);
	drv_ifd_set_slow_charge_en_for_max(IFD_ENABLE);
	drv_ifd_set_slow_charge_en_for_peak(IFD_ENABLE);
	drv_ifd_agc_diff_targ(GET_ATV_IFD_AGCLOOP1_DIFFTARGET());
	rtd_outl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_LOCK2_VADDR, GET_ATV_IFD_AGCLOOP1_DNSAMPLE()<<4);
	drv_ifd_agc_targ_val(GET_ATV_IFD_AGCLOOP1_MAXTARGETPAL());

	rtd_outl(IFD_AGC_CNTL_SEL_VADDR, 0x0);
	drv_ifd_agc_polarity(GET_ATV_TUNER_AGCPOLARITY());
	rtd_outl(IFD_KI_VAL_VADDR, 0x0);
	drv_ifd_agc_loop1_kp_settings(GET_ATV_IFD_AGCLOOP1_KPGAIN());
	drv_ifd_agc_loop1_ki_settings(GET_ATV_IFD_AGCLOOP1_KIGAIN());
	drv_ifd_agc_loop1_pishift_settings(GET_ATV_IFD_AGCLOOP1_KPKISHIFT());
	rtd_outl(IFD_RF_AGC_LIMIT_VALUE_VADDR, ((GET_ATV_IFD_AGC_RF_MIN(0)<<16) |GET_ATV_IFD_AGC_RF_MAX(0)));
	rtd_outl(IFD_IF_AGC_MIN_VADDR, ((GET_ATV_IFD_AGC_IF_MAX()<<16) |GET_ATV_IFD_AGC_IF_MIN()));
	rtd_outl(IFD_AGC_LOCK_TH_VADDR, ((IFD_LOOP1_AGC_LOCK_OUT_THD<<8) | IFD_LOOP1_AGC_LOCK_IN_THD));
	drv_ifd_agc_hsync_start1(IFD_VSmode1_Hstart_PAL, IFD_VSmode1_Hend_PAL);
	drv_ifd_agc_vsync_start1(IFD_VSmode1_Vstart_PAL, IFD_VSmode1_Vend_PAL);

	rtd_outl(IFD_AGC_PEAK_DETECT_VADDR, (IFD_PEAK_DEC_CNT&0xfff));
	drv_ifd_agc_loop2_peak_cnt(IFD_PEAK2_DEC_CNT);
	drv_ifd_agc_loop1_peak_force(GET_ATV_IFD_AGCLOOP1_PEAKFORCE_EN());
	drv_ifd_agc_loop1_peak_en(IFD_ENABLE);
	drv_ifd_agc_loop2_peak_en(IFD_ENABLE);
	drv_ifd_agc_peak_target(GET_ATV_IFD_AGCLOOP1_PEAKTARGET());
	drv_ifd_agc_krf(IFD_AGC_KRF);
	rtd_outl(IFD_AGC_LINEBASE_CTL_VADDR, 0x00000070);
	rtd_outl(IFD_AGC_MAX2_CNT_1_VADDR, ((IFD_UNLOCK_MAX2_DEC_CNT<<12)|IFD_LOCK_MAX2_DEC_CNT));
	drv_ifd_loop2_agcin_kpki_settings(GET_ATV_IFD_AGCLOOP2_KPGAIN(), GET_ATV_IFD_AGCLOOP2_KIGAIN(), GET_ATV_IFD_AGCLOOP2_KPSHIFT(), GET_ATV_IFD_AGCLOOP2_KISHIFT());
	rtd_outl(IFD_AGC_MAX2_LIMIT_CNT_1_VADDR, 0x0000FFF0);

	drv_ifd_agc_loop2_dn_sample(GET_ATV_IFD_AGCLOOP2_DNSAMPLE());
	drv_ifd_agc_dgain_up_dn_boundary(IFD_AGC_2STEP_DGAIN_LOW_THD, IFD_AGC_2STEP_DGAIN_HIGH_THD);
	rtd_outl(IFD_AGC_DGAIN_TO_PGA_VADDR, 0x20401388);
	drv_ifd_agc_2step_pga_step(IFD_AGC_2STEP_PGA_STEP);
	drv_ifd_agc_vtop(GET_ATV_IFD_AGCVTOP(0));
	
	drv_ifd_agc_2step_pga_minimum(GET_ATV_IFD_AGC_PGA_MIN(0));
	drv_ifd_agc_loop1_finetune_dn_sample(GET_ATV_IFD_AGCLOOP1_FINEDNSAMPLE());
	drv_ifd_agc_loop2_finetune_dn_sample(GET_ATV_IFD_AGCLOOP2_FINEDNSAMPLE());
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, 0x000000FE);

	drv_ifd_agc_rfagc_padctrl(IFD_AGC_PADCTRL_OPENDRAIN);
	drv_ifd_agc_ifagc_padctrl(IFD_AGC_PADCTRL_TTL);
	drv_ifd_agc_sigma_delta_dnsel(GET_ATV_IFD_AGCSIGMADELTADNSEL());

	//Rf Agc Hasten
	rtd_outl(IFD_AGC_RF_HASTEN_VADDR, (GET_ATV_IFD_AGC_RFHASTEN_EN()<<28)|(GET_ATV_IFD_AGC_RFHASTEN_KI()<<24)|(GET_ATV_IFD_AGC_RFHASTEN_CNTL()<<12)|GET_ATV_IFD_AGC_RFHASTEN_THR());
	//Agc Sep Rf If
	rtd_outl(IFD_AGC_SEP_RF_IF_VADDR, (GET_ATV_IFD_AGC_SEPRFIF_EN()<<12)|(GET_ATV_IFD_AGC_SEPRFIF_IFKP()<<4)|GET_ATV_IFD_AGC_SEPRFIF_IFKI());
	//Adaptive Gain Target
	drv_ifd_agc_adaptivetarget_fine_interval(GET_ATV_IFD_AGCADAPT_FINEINTERVAL());
	drv_ifd_agc_adaptivetarget_interval(GET_ATV_IFD_AGCADAPT_INTERVAL());
	drv_ifd_agc_adaptivetarget_en(IFD_ENABLE);
	drv_ifd_agc_adaptivetarget_inc_thr(GET_ATV_IFD_AGCADAPT_INCTHR());
	drv_ifd_agc_adaptivetarget_min_difftarg(GET_ATV_IFD_AGCADAPT_MINDIFFTARGET());
	drv_ifd_agc_adaptivetarget_min_targ(GET_ATV_IFD_AGCADAPT_MINMAXTARGET());
	drv_ifd_agc_adaptivetarget_fine_targthr(GET_ATV_IFD_AGCADAPT_FINEINTERVAL());
	drv_ifd_agc_adaptivetarget_diff_coarsestep(GET_ATV_IFD_AGCADAPT_DIFFCOARSESTEP());
	//Debug Init
	//drvif_ifd_dma_data((IFD_DEBUG_MODE_CONFIG)0);

}
#else
 
#endif