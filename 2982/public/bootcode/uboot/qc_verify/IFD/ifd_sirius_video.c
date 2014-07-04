
/*=============================================================*/
/**
 * drv_ifd_set_input_flt_sel
 *
 *
 * @param <input_flt_en><table>
 * @return { void }
 */
void drv_ifd_input_filter_sel(bool enable, UINT16 * table)
{
	UINT8 i;
	input_flt_en_RBUS input_flt_en_rbus_data;

	UINT32 addr_base = FEin_INPUT_FLT_TAP_0_1_VADDR;

	for(i=0;i<(INPUT_FILTER_TABLE_SIZE>>1);i++)
	{
		rtd_outl(addr_base+i*4, table[2*i]<<16|table[2*i+1]);
	}

	input_flt_en_rbus_data.regValue = rtd_inl(FEin_INPUT_FLT_EN_VADDR);
	input_flt_en_rbus_data.input_flt_en=enable;
	rtd_outl(FEin_INPUT_FLT_EN_VADDR, input_flt_en_rbus_data.regValue);

	
}

/*=============================================================*/
void drv_ifd_set_videopath_output_gain(IFD_VIDEOPATH_OUTPUT_GAIN data_gain)
{
	shape_filter_selection_RBUS shape_filter_selection_rbus_data;

	shape_filter_selection_rbus_data.regValue = rtd_inl(IFD_SHAPE_FILTER_SELECTION_VADDR);
	shape_filter_selection_rbus_data.data_gain_sel= data_gain;
	rtd_outl(IFD_SHAPE_FILTER_SELECTION_VADDR, shape_filter_selection_rbus_data.regValue);
}
IFD_VIDEOPATH_OUTPUT_GAIN drv_ifd_set_videopath_output_gain_get_info(void)
{
	shape_filter_selection_RBUS shape_filter_selection_rbus_data;

	shape_filter_selection_rbus_data.regValue = rtd_inl(IFD_SHAPE_FILTER_SELECTION_VADDR);
	return (IFD_VIDEOPATH_OUTPUT_GAIN)shape_filter_selection_rbus_data.data_gain_sel;
}
/*=============================================================*/
/**
  * drv_ifd_set_shaping_filter
 *
 *
 * @param <shaping_bw_sel>
 * @return { void }
 */
void drv_ifd_set_shaping_filter(IFD_SHAPING_BW_SEL shaping_bw_sel)
{
	shape_filter_selection_RBUS shape_filter_selection_rbus_data;

	shape_filter_selection_rbus_data.regValue = rtd_inl(IFD_SHAPE_FILTER_SELECTION_VADDR);
	shape_filter_selection_rbus_data.shaping_bw_sel = shaping_bw_sel;
	rtd_outl(IFD_SHAPE_FILTER_SELECTION_VADDR, shape_filter_selection_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_shaping_filter_get_info
 *
 *
 * @param <void>
 * @return { shaping_bw_sel }
 */
UINT8 drv_ifd_set_shaping_filter_get_info()
{
	shape_filter_selection_RBUS shape_filter_selection_rbus_data;

	shape_filter_selection_rbus_data.regValue = rtd_inl(IFD_SHAPE_FILTER_SELECTION_VADDR);
	return shape_filter_selection_rbus_data.shaping_bw_sel;
}
/*=============================================================*/
/**
 * drv_ifd_set_shaping_img
 *
 *
 * @param <shaping_image_sel>
 * @return { void }
 */
void drv_ifd_set_shaping_img( IFD_SHAPING_IMG_SEL shaping_image_sel)
{
	shape_filter_selection_RBUS shape_filter_selection_rbus_data;
	shape_filter_selection_rbus_data.regValue = rtd_inl(IFD_SHAPE_FILTER_SELECTION_VADDR);
	shape_filter_selection_rbus_data.shaping_image_sel = shaping_image_sel;
	rtd_outl(IFD_SHAPE_FILTER_SELECTION_VADDR, shape_filter_selection_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_shaping_filter_img_get_info
 *
 *
 * @param <void>
 * @return <shaping_image_sel>
 */
bool drv_ifd_set_shaping_filter_img_get_info()
{
	shape_filter_selection_RBUS shape_filter_selection_rbus_data;

	shape_filter_selection_rbus_data.regValue = rtd_inl(IFD_SHAPE_FILTER_SELECTION_VADDR);
	return shape_filter_selection_rbus_data.shaping_image_sel;

}
/*=============================================================*/
/**
 * drv_ifd_soft_reset
 *
 *
 * @param <reset>
 * @return { void }
 */
void drv_ifd_soft_reset(bool reset)
{
	soft_reset_27_clk_phase_RBUS soft_reset_27_clk_phase_rbus_data;

	soft_reset_27_clk_phase_rbus_data.regValue = rtd_inl(IFD_SOFT_RESET_27_CLK_PHASE_VADDR);
	soft_reset_27_clk_phase_rbus_data.soft_reset = reset;
	rtd_outl(IFD_SOFT_RESET_27_CLK_PHASE_VADDR, soft_reset_27_clk_phase_rbus_data.regValue);
}
bool drv_ifd_soft_reset_get_info(void)
{
	soft_reset_27_clk_phase_RBUS soft_reset_27_clk_phase_rbus_data;

	soft_reset_27_clk_phase_rbus_data.regValue = rtd_inl(IFD_SOFT_RESET_27_CLK_PHASE_VADDR);
	return soft_reset_27_clk_phase_rbus_data.soft_reset;
}
/*=============================================================*/
/**
 * drv_ifd_set_54to27_decimation_enable
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_set_54to27_decimation_enable(bool enable)
{
	decimation_filter_enable_RBUS decimation_filter_enable_rbus_data;

	decimation_filter_enable_rbus_data.regValue = rtd_inl(IFD_DECIMATION_FILTER_ENABLE_VADDR);
	decimation_filter_enable_rbus_data.decimation_en = enable;
	rtd_outl(IFD_DECIMATION_FILTER_ENABLE_VADDR, decimation_filter_enable_rbus_data.regValue);
};
/*=============================================================*/
/**
 * drv_ifd_eq_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_eq_en(bool enable)
{
	eq_filter_sel_RBUS eq_filter_sel_rbus_data;

	eq_filter_sel_rbus_data.regValue = rtd_inl(IFD_108M_EQ_FILTER_SEL_VADDR);
	eq_filter_sel_rbus_data.eq_en= enable;
	rtd_outl(IFD_108M_EQ_FILTER_SEL_VADDR, eq_filter_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_eq_en_get_info
 *
 *
 * @param <void>
 * @return { enable }
 */
bool drv_ifd_eq_en_get_info(void)
{
	eq_filter_sel_RBUS eq_filter_sel_rbus_data;

	eq_filter_sel_rbus_data.regValue = rtd_inl(IFD_108M_EQ_FILTER_SEL_VADDR);
	return (eq_filter_sel_rbus_data.eq_en);
}
/*=============================================================*/
/**
 * drv_ifd_set_eq_coef
 *
 *
 * @param <table>
 * @return { void }
 */
void drv_ifd_set_eq_coef(UINT16 *table)
{
	eq_filter_sel_RBUS eq_filter_sel_rbus_data;

        UINT32 i;

        for(i=0;i<EQ_TABLE_SIZE;i++)
        {
                eq_filter_sel_rbus_data.regValue = 0;
                rtd_outl(IFD_108M_EQ_FILTER_SEL_VADDR, eq_filter_sel_rbus_data.regValue);
                eq_filter_sel_rbus_data.eq_coe_modify_en= 1;
                eq_filter_sel_rbus_data.eq_coe_tap= i;
                eq_filter_sel_rbus_data.eq_coe= table[i];
                rtd_outl(IFD_108M_EQ_FILTER_SEL_VADDR, eq_filter_sel_rbus_data.regValue);
        }

        eq_filter_sel_rbus_data.regValue = 0;
        rtd_outl(IFD_108M_EQ_FILTER_SEL_VADDR, eq_filter_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_eq_coef
 *
 *
 * @param <table>
 * @return { void }
 */
void drv_ifd_get_eq_coef(UINT16 *table)
{
	eq_filter_read_RBUS eq_filter_read_rbus_data;

	UINT32 i;

	eq_filter_read_rbus_data.regValue = 0;
	
	for(i=0;i<EQ_TABLE_SIZE;i++)
	{
		eq_filter_read_rbus_data.eq_coe_read_tap = i;   
		rtd_outl(IFD_108M_EQ_FILTER_READ_VADDR, eq_filter_read_rbus_data.regValue);
		eq_filter_read_rbus_data.regValue = rtd_inl(IFD_108M_EQ_FILTER_READ_VADDR);
		
		table[i] = eq_filter_read_rbus_data.eq_coe_read;
        }

        eq_filter_read_rbus_data.regValue = 0;
        rtd_outl(IFD_108M_EQ_FILTER_READ_VADDR, eq_filter_read_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_eq_out_rms
 *
 *
 * @param { void }
 * @return { void }
 */
UINT32 drv_ifd_get_eq_out_rms(void)
{
	eq_out_rms_RBUS eq_out_rms_rbus_data;

	eq_out_rms_rbus_data.regValue = rtd_inl(IFD_108M_EQ_OUT_RMS_VADDR);

	return eq_out_rms_rbus_data.eq_out_rms;
}
/*=============================================================*/
/**
 * drv_ifd_set_pos_neg_mod
 *
 *
 * @param <mod_sel>
 * @return { void }
 */
void drv_ifd_set_pos_neg_mod(IFD_MODULATION_SEL mod_sel)
{
	mod_sel_RBUS mod_sel_rbus_data;

	mod_sel_rbus_data.regValue = rtd_inl(IFD_27M_MOD_SEL_VADDR);
	mod_sel_rbus_data.mod_sel = mod_sel;
	rtd_outl(IFD_27M_MOD_SEL_VADDR, mod_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_video_bw
 *
 *
 * @param <video_bw_sel>
 * @return { void }
 */
void drv_ifd_set_video_bw(IFD_VIDEO_BW_SEL video_bw_sel)
{
	video_bw_sel_RBUS video_bw_sel_rbus_data;

	video_bw_sel_rbus_data.regValue = rtd_inl(IFD_108M_VIDEO_BW_SEL_VADDR);
	video_bw_sel_rbus_data.video_bw_sel= video_bw_sel;
	rtd_outl(IFD_108M_VIDEO_BW_SEL_VADDR, video_bw_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_video_bw_info
 *
 *
 * @param <void>
 * @return { video_bw_sel }
 */
UINT8 drv_ifd_get_video_bw_info(void)
{
	video_bw_sel_RBUS video_bw_sel_rbus_data;

	video_bw_sel_rbus_data.regValue = rtd_inl(IFD_108M_VIDEO_BW_SEL_VADDR);
	return (video_bw_sel_rbus_data.video_bw_sel);
}
/*=============================================================*/
/**
 * drv_ifd_set_video_upsample_lp_sel
 *
 *
 * @param <video_bw_sel>
 * @return { void }
 */
void drv_ifd_set_video_upsample_lp_sel(IFD_UPSAMPLE_LP_SEL sel)
{
	video_bw_sel_RBUS video_bw_sel_rbus_data;

	video_bw_sel_rbus_data.regValue = rtd_inl(IFD_108M_VIDEO_BW_SEL_VADDR);
	video_bw_sel_rbus_data.video_upsample_lp_sel= sel;
	rtd_outl(IFD_108M_VIDEO_BW_SEL_VADDR, video_bw_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_video_upsample_lp_sel_get_info
 *
 *
 * @param <void>
 * @return { video_bw_sel }
 */
IFD_UPSAMPLE_LP_SEL drv_ifd_set_video_upsample_lp_sel_get_info(void)
{
	video_bw_sel_RBUS video_bw_sel_rbus_data;

	video_bw_sel_rbus_data.regValue = rtd_inl(IFD_108M_VIDEO_BW_SEL_VADDR);
	return (IFD_UPSAMPLE_LP_SEL)(video_bw_sel_rbus_data.video_upsample_lp_sel);
}
/*=============================================================*/
/**
 * drv_ifd_grp_delay_en
 *
 *
 * @param <enable><table>
 * @return { void }
 */
void drv_ifd_grp_delay_en (bool enable,  UINT16 *table)
{
	grp_delay_en_RBUS grp_delay_en_rbus_data;
	UINT32 i;

	for(i=0;i<GP_BPF_TABLE_SIZE;i++)
	{
		grp_delay_en_rbus_data.regValue = 0;
		rtd_outl(IFD_108M_GRP_DELAY_EN_VADDR, grp_delay_en_rbus_data.regValue);
		grp_delay_en_rbus_data.grp_delay_coe_en= 1;
		grp_delay_en_rbus_data.grp_delay_select_tap= i+1;
		grp_delay_en_rbus_data.grp_delay_coe_modofy= table[i];
		rtd_outl(IFD_108M_GRP_DELAY_EN_VADDR, grp_delay_en_rbus_data.regValue);
	}
	grp_delay_en_rbus_data.regValue = 0;
       rtd_outl(IFD_108M_GRP_DELAY_EN_VADDR, grp_delay_en_rbus_data.regValue);
	grp_delay_en_rbus_data.grp_delay_en = enable;
	rtd_outl(IFD_108M_GRP_DELAY_EN_VADDR, grp_delay_en_rbus_data.regValue);
}
bool drv_ifd_grp_delay_en_get_info(void)
{
	grp_delay_en_RBUS grp_delay_en_rbus_data;

	grp_delay_en_rbus_data.regValue = rtd_inl(IFD_108M_GRP_DELAY_EN_VADDR);
	return grp_delay_en_rbus_data.grp_delay_en;
}
/*=============================================================*/
/**
 * drv_ifd_video_outputlpf_coef_update
 *
 *
 * @param <enable><table>
 * @return { void }
 */
void drv_ifd_video_outputlpf_coef_update (bool enable,  UINT16 *table)
{
	output_lpf_modify_en_RBUS output_lpf_modify_en_rbus_data;
	video_bw_sel_RBUS video_bw_sel_data;
	UINT32 i;

	video_bw_sel_data.regValue = rtd_inl(IFD_108M_VIDEO_BW_SEL_VADDR);
	
	if(enable==IFD_ENABLE)
	{	
		video_bw_sel_data.video_bw_sel=1;
		rtd_outl(IFD_108M_VIDEO_BW_SEL_VADDR, video_bw_sel_data.regValue);
		
		for(i=0;i<OUPUT_LPF_TABLE_SIZE;i++)
		{
			output_lpf_modify_en_rbus_data.regValue = 0;
			output_lpf_modify_en_rbus_data.output_lpf_vsync_coe_change = IFD_DISABLE;
			rtd_outl(IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR, output_lpf_modify_en_rbus_data.regValue);
			output_lpf_modify_en_rbus_data.output_lpf_coe_modify_en= 1;
			output_lpf_modify_en_rbus_data.output_lpf_coe_tap= i+1;
			output_lpf_modify_en_rbus_data.output_lpf_coe= table[i];
			rtd_outl(IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR, output_lpf_modify_en_rbus_data.regValue);
		}
		output_lpf_modify_en_rbus_data.regValue = 0;
       	rtd_outl(IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR, output_lpf_modify_en_rbus_data.regValue);
		output_lpf_modify_en_rbus_data.output_lpf_extern_set = IFD_ENABLE;
		rtd_outl(IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR, output_lpf_modify_en_rbus_data.regValue);
	}
	else
	{
		video_bw_sel_data.video_bw_sel=0;
		rtd_outl(IFD_108M_VIDEO_BW_SEL_VADDR, video_bw_sel_data.regValue);
		
		output_lpf_modify_en_rbus_data.regValue = 0;
		output_lpf_modify_en_rbus_data.output_lpf_vsync_coe_change = IFD_DISABLE;
		output_lpf_modify_en_rbus_data.output_lpf_extern_set = IFD_DISABLE;
       	rtd_outl(IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR, output_lpf_modify_en_rbus_data.regValue);
	}

}
void drv_ifd_video_outputlpf_en (bool enable)
{
	output_lpf_modify_en_RBUS output_lpf_modify_en_rbus_data;
	
	output_lpf_modify_en_rbus_data.regValue = 0;
	output_lpf_modify_en_rbus_data.output_lpf_vsync_coe_change = 1;
	output_lpf_modify_en_rbus_data.output_lpf_extern_set = enable;
	rtd_outl(IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR, output_lpf_modify_en_rbus_data.regValue);
}
bool drv_ifd_video_outputlpf_en_get_info(void)
{
	output_lpf_modify_en_RBUS output_lpf_modify_en_rbus_data;

	output_lpf_modify_en_rbus_data.regValue = rtd_inl(IFD_108M_OUTPUT_LPF_MODIFY_EN_VADDR);

	return output_lpf_modify_en_rbus_data.output_lpf_extern_set;
}
//=================================================================
//Clamp
//=================================================================
void drv_ifd_clamp_offset_hold (IFD_CLAMP_OFFSET clamp_offset_hold)
{
	clamping_scale_RBUS clamping_scale_rbus_data;

	clamping_scale_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_SCALE_VADDR);
	clamping_scale_rbus_data.clamp_offset_hold = clamp_offset_hold;
	rtd_outl(IFD_27M_CLAMPING_SCALE_VADDR,clamping_scale_rbus_data.regValue);
}
IFD_CLAMP_OFFSET drv_ifd_clamp_offset_hold_get_info(void)
{
	clamping_scale_RBUS clamping_scale_rbus_data;

	clamping_scale_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_SCALE_VADDR);
	return (IFD_CLAMP_OFFSET)clamping_scale_rbus_data.clamp_offset_hold;
}
void drv_ifd_clamp_offset_reset (bool clamping_reset)
{
	clamping_scale_RBUS clamping_scale_rbus_data;

	clamping_scale_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_SCALE_VADDR);
	clamping_scale_rbus_data.clamping_reset = clamping_reset;
	rtd_outl(IFD_27M_CLAMPING_SCALE_VADDR,clamping_scale_rbus_data.regValue);
}
bool drv_ifd_clamp_offset_reset_get_info(void)
{
	clamping_scale_RBUS clamping_scale_rbus_data;

	clamping_scale_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_SCALE_VADDR);
	return clamping_scale_rbus_data.clamping_reset;
}
/*=============================================================*/
/**
 * drv_ifd_set_clamping_scale
 *
 *
 * @param <clamping_scale>
 * @return { void }
 */
void drv_ifd_set_clamping_scale (IFD_CLAMP_SCALE clamping_scale)
{
	clamping_scale_RBUS clamping_scale_rbus_data;

	clamping_scale_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_SCALE_VADDR);
	clamping_scale_rbus_data.clamping_scale = clamping_scale;
	rtd_outl(IFD_27M_CLAMPING_SCALE_VADDR,clamping_scale_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_clamping_scale_get_info
 *
 *
 * @param <void>
 * @return { clamping_scale }
 */
IFD_CLAMP_SCALE drv_ifd_set_clamping_scale_get_info (void)
{
	clamping_scale_RBUS clamping_scale_rbus_data;

	clamping_scale_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_SCALE_VADDR);
	return (IFD_CLAMP_SCALE)(clamping_scale_rbus_data.clamping_scale);
}
/*=============================================================*/
/**
 * drv_ifd_set_clamping_thr_max
 *
 *
 * @param <clamping_thr_max>
 * @return <void>
 */
void drv_ifd_set_clamping_thr_max (UINT16 clamping_thr_max)
{
        clamping_thr_max_RBUS clamping_thr_max_rbus_data;

        clamping_thr_max_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_THR_MAX_VADDR);
        clamping_thr_max_rbus_data.clamping_thr_max= clamping_thr_max;
	rtd_outl(IFD_27M_CLAMPING_THR_MAX_VADDR,clamping_thr_max_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_clamping_thr_max_get_info
 *
 *
 * @param <void>
 * @return <clamping_thr_max>
 */
UINT16 drv_ifd_set_clamping_thr_max_get_info (void)
{
        clamping_thr_max_RBUS clamping_thr_max_rbus_data;

        clamping_thr_max_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_THR_MAX_VADDR);
        return (clamping_thr_max_rbus_data.clamping_thr_max);


}
/*=============================================================*/
/**
 * drv_ifd_set_clamping_thr_min
 *
 *
 * @param <clamping_thr_min>
 * @return <void>
 */
void drv_ifd_set_clamping_thr_min (UINT16 clamping_thr_min)
{
        clamping_thr_min_RBUS clamping_thr_min_rbus_data;

        clamping_thr_min_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_THR_MIN_VADDR);
        clamping_thr_min_rbus_data.clamping_thr_min= clamping_thr_min;
        rtd_outl(IFD_27M_CLAMPING_THR_MIN_VADDR,clamping_thr_min_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_clamping_thr_min_get_info
 *
 *
 * @param <void>
 * @return <clamping_thr_min>
 */
UINT16 drv_ifd_set_clamping_thr_min_get_info (void)
{
        clamping_thr_min_RBUS clamping_thr_min_rbus_data;

        clamping_thr_min_rbus_data.regValue = rtd_inl(IFD_27M_CLAMPING_THR_MIN_VADDR);
        return (clamping_thr_min_rbus_data.clamping_thr_min);


}
/*=============================================================*/
/**
 * drv_ifd_get_clamping_offset_status
 *
 *
 * @param <void>
 * @return <clamping_offset_status>
 */
UINT16 drv_ifd_get_clamping_offset_status (void)
{
	offset_RBUS offset_rbus_data;

	offset_rbus_data.regValue= rtd_inl(IFD_27M_OFFSET_VADDR);

	return offset_rbus_data.offset_status;
}
/*=============================================================*/
/**
 * drv_ifd_bypass_demod
 *
 *
 * @param <bypass>
 * @return { void }
 */
void drv_ifd_bypass_demod(bool bypass)
{
	ad_bypass_enable_RBUS ad_bypass_enable_rbus_data;

	ad_bypass_enable_rbus_data.regValue = rtd_inl(IFD_AD_BYPASS_ENABLE_VADDR);
	ad_bypass_enable_rbus_data.bypassad = bypass;
	rtd_outl(IFD_AD_BYPASS_ENABLE_VADDR, ad_bypass_enable_rbus_data.regValue);
}


/*=============================================================*/
/**
 * drv_ifd_adc_clk_sel
 *
 *
 * @param <clk_rate>
 * @return { void }
 */
void drv_ifd_adc_clk_sel(IFD_CLK_RATE clk_rate, IFD_INPUT_DN_FILTER input_dn_filter)
{
	input_filter_set_RBUS input_filter_set_data;

	input_filter_set_data.regValue = rtd_inl(FEin_INPUT_FILTER_SET_VADDR);
		
	switch(clk_rate)
	{
		case IFD_CLK_RATE_108M:
			input_filter_set_data.adc_clk_sel = 1;
			input_filter_set_data.input_dn_filter_sel= input_dn_filter;
			break;		
		case IFD_CLK_RATE_54M:
			input_filter_set_data.adc_clk_sel = 0;
			input_filter_set_data.input_dn_filter_sel= 0;
			break;		
		case IFD_CLK_RATE_135M:
			input_filter_set_data.adc_clk_sel = 2;
			input_filter_set_data.input_dn_filter_sel= (0x1<<1|input_dn_filter);
			break;
		case IFD_CLK_RATE_162M:
			input_filter_set_data.adc_clk_sel = 3;
			input_filter_set_data.input_dn_filter_sel= (0x1<<2|input_dn_filter);
			break;
		default:
			break;
	}
	
	rtd_outl(FEin_INPUT_FILTER_SET_VADDR, input_filter_set_data.regValue);
	
	drv_ifd_adc_clock(clk_rate);
	//drvif_module_vdc_FIFO_CLK_setting();
}

/*=============================================================*/
/**
 * drv_ifd_adc_clk_sel_get_info
 *
 *
 * @param <void>
 * @return { clk_rate }
 */
IFD_CLK_RATE drv_ifd_adc_clk_sel_get_info(void)
{
	input_filter_set_RBUS input_filter_set_data;
	IFD_CLK_RATE clk_rate;

	input_filter_set_data.regValue = rtd_inl(FEin_INPUT_FILTER_SET_VADDR);
	
	switch(input_filter_set_data.adc_clk_sel)
	{
		case 1:
			clk_rate = IFD_CLK_RATE_108M;
			break;		
		case 0:
			clk_rate = IFD_CLK_RATE_54M;
			break;		
		case 2:
			clk_rate = IFD_CLK_RATE_135M;
			break;
		case 3:
			clk_rate = IFD_CLK_RATE_162M;
			break;
		default:
			clk_rate = IFD_CLK_RATE_108M;
			break;
	}
	
	return clk_rate;
}
/*=============================================================*/
/**
 * drv_ifd_outputlpf_vsync
 *
 *
 * @param <input_filter_sel>
 * @return { void }
 */
void drv_ifd_outputlpf_vsync(UINT16 start, UINT16 end)
{
	output_lpf_vsync_start_RBUS output_lpf_vsync_start_rbus_data;

	output_lpf_vsync_start_rbus_data.regValue = rtd_inl(IFD_OUTPUT_LPF_VSYNC_START_VADDR);
	output_lpf_vsync_start_rbus_data.lpf_vsync_start = start;
	output_lpf_vsync_start_rbus_data.lpf_vsync_end = end;
	rtd_outl(IFD_OUTPUT_LPF_VSYNC_START_VADDR, output_lpf_vsync_start_rbus_data.regValue);
}
//=================================================================
//Modulation Type Detection
//=================================================================
void drv_ifd_mtd_reset(bool enable)
{
	mod_detect_update_cntl_RBUS mod_detect_update_cntl_rbus_data;

	mod_detect_update_cntl_rbus_data.regValue = rtd_inl(IFD_MOD_DETECT_UPDATE_CNTL_VADDR);
	mod_detect_update_cntl_rbus_data.mod_reset = enable;
	rtd_outl(IFD_MOD_DETECT_UPDATE_CNTL_VADDR, mod_detect_update_cntl_rbus_data.regValue);
}
bool drv_ifd_mtd_reset_get_info(void)
{
	mod_detect_update_cntl_RBUS mod_detect_update_cntl_rbus_data;

	mod_detect_update_cntl_rbus_data.regValue = rtd_inl(IFD_MOD_DETECT_UPDATE_CNTL_VADDR);
	
	return mod_detect_update_cntl_rbus_data.mod_reset;
}
void drv_ifd_mtd_set_thr(UINT8 mod_state_thr, UINT16 neg_mod_thr, UINT16 pos_mod_thr)
{
	mod_detect_thr_RBUS mod_detect_thr_rbus_data;

	mod_detect_thr_rbus_data.regValue = rtd_inl(IFD_MOD_DETECT_THR_VADDR);
	mod_detect_thr_rbus_data.mod_state_thr = mod_state_thr;
	mod_detect_thr_rbus_data.neg_mod_thr = neg_mod_thr;
	mod_detect_thr_rbus_data.pos_mod_thr = pos_mod_thr;
	rtd_outl(IFD_MOD_DETECT_THR_VADDR, mod_detect_thr_rbus_data.regValue);
}
IFD_MTD_STATUS drv_ifd_mtd_get_mod_state(void)
{
	mod_detect_state_RBUS mod_detect_state_rbus_data;

	mod_detect_state_rbus_data.regValue = rtd_inl(IFD_MOD_DETECT_STATE_VADDR);

	return (IFD_MTD_STATUS)mod_detect_state_rbus_data.mod_state;
}
void drv_ifd_mtd_auto_en(bool enable)
{
	mod_detect_auto_RBUS mod_detect_auto_rbus_data;

	mod_detect_auto_rbus_data.regValue = rtd_inl(IFD_MOD_DETECT_AUTO_VADDR);
	mod_detect_auto_rbus_data.mod_auto_en = enable;
	rtd_outl(IFD_MOD_DETECT_AUTO_VADDR, mod_detect_auto_rbus_data.regValue);
}
bool drv_ifd_mtd_auto_en_get_info(void)
{
	mod_detect_auto_RBUS mod_detect_auto_rbus_data;

	mod_detect_auto_rbus_data.regValue = rtd_inl(IFD_MOD_DETECT_AUTO_VADDR);
	return mod_detect_auto_rbus_data.mod_auto_en;
}

