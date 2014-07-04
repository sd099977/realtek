
/*=============================================================*/
/**
 * drv_ifd_set_audio_bp_up_lp
 *
 *
 * @param <audio_bp_sel><audio_upsample_lp_sel>
 * @return { void }
 */
void drv_ifd_set_audio_bp_up_lp (IFD_AUDIO_BP_SEL audio_bp_sel, IFD_AUDIO_UPSAMPLE_LP_SEL audio_upsample_lp_sel, bool bpf_input_div2_sel)
{
	audio_bp_sel_RBUS audio_bp_sel_rbus_data;

	audio_bp_sel_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_BP_SEL_VADDR);
	audio_bp_sel_rbus_data.output_bpf_input_div2 = bpf_input_div2_sel;
	audio_bp_sel_rbus_data.audio_bp_sel = audio_bp_sel & 0xFF;
	audio_bp_sel_rbus_data.audio_upsample_lp_sel = audio_upsample_lp_sel;

	rtd_outl(IFD_49M_AUDIO_BP_SEL_VADDR, audio_bp_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_audio_bp
 *
 *
 * @param <audio_bp_sel>
 * @return { void }
 */
void drv_ifd_set_audio_bp (IFD_AUDIO_BP_SEL audio_bp_sel)
{
	audio_bp_sel_RBUS audio_bp_sel_rbus_data;

	audio_bp_sel_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_BP_SEL_VADDR);
	audio_bp_sel_rbus_data.audio_bp_sel = audio_bp_sel & 0xFF;

	rtd_outl(IFD_49M_AUDIO_BP_SEL_VADDR, audio_bp_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_audio_bp_info
 *
 *
 * @param <void>
 * @return { audio_bp_sel }
 */
UINT8 drv_ifd_get_audio_bp_info (void)
{
	audio_bp_sel_RBUS audio_bp_sel_rbus_data;

	audio_bp_sel_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_BP_SEL_VADDR);
	return (audio_bp_sel_rbus_data.audio_bp_sel);
}
/*=============================================================*/
/**
 * drv_ifd_audio_gain_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_audio_gain_en(bool enable)
{
	audio_gain_manu_RBUS audio_gain_manu_rbus_data;
	audio_gain_status_RBUS audio_gain_status_rbus_data;

	audio_gain_manu_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_GAIN_MANU_VADDR);
	audio_gain_status_rbus_data.regValue= rtd_inl(IFD_49M_AUDIO_GAIN_STATUS_VADDR);
	if(enable)
	{
		audio_gain_manu_rbus_data.aagc_en = enable;
		audio_gain_manu_rbus_data.audio_gain_manual=0;
	}
	else
	{
		audio_gain_manu_rbus_data.aagc_en = enable;
		audio_gain_manu_rbus_data.audio_gain_manual=audio_gain_status_rbus_data.audio_gain_status;
	}
	rtd_outl(IFD_49M_AUDIO_GAIN_MANU_VADDR, audio_gain_manu_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_audio_gain_en_get_info
 *
 *
 * @param <void>
 * @return { enable }
 */
bool drv_ifd_audio_gain_en_get_info(void)
{
	audio_gain_manu_RBUS audio_gain_manu_rbus_data;

	audio_gain_manu_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_GAIN_MANU_VADDR);
	return (audio_gain_manu_rbus_data.aagc_en);
}

void drv_ifd_audio_gain_manual(UINT16 gain)
{
	audio_gain_manu_RBUS audio_gain_manu_rbus_data;

	audio_gain_manu_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_GAIN_MANU_VADDR);
	audio_gain_manu_rbus_data.audio_gain_manual=gain;
	rtd_outl(IFD_49M_AUDIO_GAIN_MANU_VADDR, audio_gain_manu_rbus_data.regValue);
}
UINT16 drv_ifd_audio_gain_manual_get_info(void)
{
	audio_gain_manu_RBUS audio_gain_manu_rbus_data;

	audio_gain_manu_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_GAIN_MANU_VADDR);
	return (audio_gain_manu_rbus_data.audio_gain_manual);
}
/*=============================================================*/
/**
 * drv_ifd_audio_gain_status
 *
 *
 * @param <void>
 * @return <UINT16>
 */
UINT16 drv_ifd_audio_gain_status(void)
{
	audio_gain_status_RBUS audio_gain_status_rbus_data;

	audio_gain_status_rbus_data.regValue = rtd_inl(IFD_49M_AUDIO_GAIN_STATUS_VADDR);
	
	return audio_gain_status_rbus_data.audio_gain_status;
}

