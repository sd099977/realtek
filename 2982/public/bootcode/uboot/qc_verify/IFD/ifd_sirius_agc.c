
/*=============================================================*/
/**
 * drv_ifd_agc_dgain_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_dgain_en(bool enable)
{
	agc_enable_sel_RBUS agc_enable_sel_rbus_data;

	agc_enable_sel_rbus_data.regValue = rtd_inl(IFD_AGC_ENABLE_SEL_VADDR);
	agc_enable_sel_rbus_data.dgain_en = enable;
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, agc_enable_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_dgain_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_agc_rf_en(bool enable)
{
	agc_enable_sel_RBUS agc_enable_sel_rbus_data;

	agc_enable_sel_rbus_data.regValue = rtd_inl(IFD_AGC_ENABLE_SEL_VADDR);
	agc_enable_sel_rbus_data.agc_rf_en= enable;
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, agc_enable_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_fine_tune_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_loop1_fine_tune_en(bool enable)
{
	agc_enable_sel_RBUS agc_enable_sel_rbus_data;

	agc_enable_sel_rbus_data.regValue = rtd_inl(IFD_AGC_ENABLE_SEL_VADDR);
	agc_enable_sel_rbus_data.agc_fine_tune_en= enable;
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, agc_enable_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_fine_tune_en_get_info
 *
 *
 * @param <void>
 * @return { enable }
 */
bool drv_ifd_agc_loop1_fine_tune_en_get_info()
{
	agc_enable_sel_RBUS agc_enable_sel_rbus_data;

	agc_enable_sel_rbus_data.regValue = rtd_inl(IFD_AGC_ENABLE_SEL_VADDR);
       return agc_enable_sel_rbus_data.agc_fine_tune_en;
}
/*=============================================================*/
/**
 * drv_ifd_agc_bpf_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_bpf_en(bool enable)
{
	agc_enable_sel_RBUS agc_enable_sel_rbus_data;

	agc_enable_sel_rbus_data.regValue = rtd_inl(IFD_AGC_ENABLE_SEL_VADDR);
	agc_enable_sel_rbus_data.agc_bpf_en= enable;
	rtd_outl(IFD_AGC_ENABLE_SEL_VADDR, agc_enable_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_bpf_en_get_info
 *
 *
 * @param <void>
 * @return { enable }
 */
bool drv_ifd_agc_bpf_en_get_info(void)
{
	agc_enable_sel_RBUS agc_enable_sel_rbus_data;

	agc_enable_sel_rbus_data.regValue = rtd_inl(IFD_AGC_ENABLE_SEL_VADDR);
	return (agc_enable_sel_rbus_data.agc_bpf_en);
}
/*=============================================================*/
/**
 * drv_ifd_set_slow_charge_en_for_max
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_set_slow_charge_en_for_max(bool enable)
{
	agc_max_count_for_coarse_mode_agc_cntl1_RBUS agc_max_count_for_coarse_mode_agc_cntl1_rbus_data;

	agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_CNTL1_VADDR);
	agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.agc_slow_charge_max_en = enable;
	
	rtd_outl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_CNTL1_VADDR, agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_slow_charge_en_for_max
 *
 *
 * @param <void>
 * @return { enable }
 */
bool drv_ifd_get_slow_charge_en_for_max(void)
{
	agc_max_count_for_coarse_mode_agc_cntl1_RBUS agc_max_count_for_coarse_mode_agc_cntl1_rbus_data;

	agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_CNTL1_VADDR);

	return agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.agc_slow_charge_max_en;
}
/*=============================================================*/
/**
 * drv_ifd_set_slow_charge_en_for_peak
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_set_slow_charge_en_for_peak(bool enable)
{
	agc_max_count_for_coarse_mode_agc_cntl1_RBUS agc_max_count_for_coarse_mode_agc_cntl1_rbus_data;

	agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_CNTL1_VADDR);
	agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.agc_slow_charge_peak_en = enable;
	
	rtd_outl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_CNTL1_VADDR, agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_slow_charge_en_for_max
 *
 *
 * @param <void>
 * @return { enable }
 */
bool drv_ifd_get_slow_charge_en_for_peak(void)
{
	agc_max_count_for_coarse_mode_agc_cntl1_RBUS agc_max_count_for_coarse_mode_agc_cntl1_rbus_data;

	agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_CNTL1_VADDR);

	return agc_max_count_for_coarse_mode_agc_cntl1_rbus_data.agc_slow_charge_peak_en;
}
/*=============================================================*/
/**
 * drv_ifd_agc_diff_targ
 *
 *
 * @param <agc_diff_targ>
 * @return { void }
 */
void drv_ifd_agc_diff_targ(UINT16 agc_diff_targ)
{
	agc_avg_target_RBUS agc_avg_target_rbus_data;

	agc_avg_target_rbus_data.regValue = rtd_inl(IFD_AGC_AVG_TARGET_VADDR);
	agc_avg_target_rbus_data.agc_diff_targ = agc_diff_targ;
	rtd_outl(IFD_AGC_AVG_TARGET_VADDR, agc_avg_target_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_diff_target_get_info
 *
 *
 * @param <void>
 * @return { agc_diff_targ }
 */
UINT16  drv_ifd_agc_diff_target_get_info(void)
{
	agc_avg_target_RBUS agc_avg_target_rbus_data;

	agc_avg_target_rbus_data.regValue = rtd_inl(IFD_AGC_AVG_TARGET_VADDR);
	return (agc_avg_target_rbus_data.agc_diff_targ);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_pos_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_loop1_pos_en (bool enable)
{
	agc_max_count_for_coarse_mode_agc_lock2_RBUS agc_max_count_for_coarse_mode_agc_lock2_rbus_data;

	agc_max_count_for_coarse_mode_agc_lock2_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_LOCK2_VADDR);
	agc_max_count_for_coarse_mode_agc_lock2_rbus_data.agc_pos_en = enable;
	rtd_outl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_LOCK2_VADDR, agc_max_count_for_coarse_mode_agc_lock2_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_pos_en_get_info
 *
 *
 * @param <void>
 * @return { enable }
 */
bool drv_ifd_agc_pos_en_get_info (void)
{
        agc_max_count_for_coarse_mode_agc_lock2_RBUS agc_max_count_for_coarse_mode_agc_lock2_rbus_data;

        agc_max_count_for_coarse_mode_agc_lock2_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_LOCK2_VADDR);
        return agc_max_count_for_coarse_mode_agc_lock2_rbus_data.agc_pos_en;

}
/*=============================================================*/
/**
 * drv_ifd_agc_data_target
 *
 *
 * @param <agc_data_targ>
 * @return { void }
 */
void drv_ifd_agc_data_target(UINT16 agc_data_targ)
{
	agc_targ_val_RBUS agc_targ_val_rbus_data;

	agc_targ_val_rbus_data.regValue = rtd_inl(IFD_AGC_TARG_VAL_VADDR);
	agc_targ_val_rbus_data.agc_data_targ = agc_data_targ;
	rtd_outl(IFD_AGC_TARG_VAL_VADDR, agc_targ_val_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_targ_val_get_info
 *
 *
 * @param <void>
 * @return { agc_data_targ }
 */
UINT16 drv_ifd_agc_data_target_get_info(void)
{
	agc_targ_val_RBUS agc_targ_val_rbus_data;

	agc_targ_val_rbus_data.regValue = rtd_inl(IFD_AGC_TARG_VAL_VADDR);
	return (agc_targ_val_rbus_data.agc_data_targ);
}
/*=============================================================*/
/**
 * drv_ifd_agc_targ_val
 *
 *
 * @param <agc_targ_val>
 * @return { void }
 */
void drv_ifd_agc_targ_val(UINT16 agc_targ_val)
{
	agc_targ_val_RBUS agc_targ_val_rbus_data;

	agc_targ_val_rbus_data.regValue = rtd_inl(IFD_AGC_TARG_VAL_VADDR);
	agc_targ_val_rbus_data.agc_targ_val = agc_targ_val;
	rtd_outl(IFD_AGC_TARG_VAL_VADDR, agc_targ_val_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_targ_val_get_info
 *
 *
 * @param <void>
 * @return { agc_targ_val }
 */
UINT16 drv_ifd_agc_targ_val_get_info(void)
{
	agc_targ_val_RBUS agc_targ_val_rbus_data;

	agc_targ_val_rbus_data.regValue = rtd_inl(IFD_AGC_TARG_VAL_VADDR);
	return (agc_targ_val_rbus_data.agc_targ_val);
}
/*=============================================================*/
/**
 * drv_ifd_agc_out_inv
 *
 *
 * @param <agc_out_inv_rf><agc_out_inv_if>
 * @return { void }
 */
void drv_ifd_agc_out_inv(bool agc_out_inv_rf, bool agc_out_inv_if)
{
	agc_cntl_sel_RBUS agc_cntl_sel_rbus_data;

	agc_cntl_sel_rbus_data.regValue = rtd_inl(IFD_AGC_CNTL_SEL_VADDR);
	agc_cntl_sel_rbus_data.agc_out_inv_rf = agc_out_inv_rf;
	agc_cntl_sel_rbus_data.agc_out_inv_if = agc_out_inv_if;
	rtd_outl(IFD_AGC_CNTL_SEL_VADDR, agc_cntl_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_polar_inv
 *
 *
 * @param <agc_out_inv_rf><agc_out_inv_if>
 * @return { void }
 */
void drv_ifd_agc_polar_inv(bool agc_inv)
{
	agc_cntl_sel_RBUS agc_cntl_sel_rbus_data;

	agc_cntl_sel_rbus_data.regValue = rtd_inl(IFD_AGC_CNTL_SEL_VADDR);
	agc_cntl_sel_rbus_data.agc_polar = agc_inv;
	rtd_outl(IFD_AGC_CNTL_SEL_VADDR, agc_cntl_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_if_manual_en
 *
 *
 * @param <agc_if_manu_en>
 * @return { void }
 */
void drv_ifd_agc_if_manual_en(bool agc_if_manu_en)
{
	agc_cntl_sel_RBUS agc_cntl_sel_rbus_data;

	agc_cntl_sel_rbus_data.regValue = rtd_inl(IFD_AGC_CNTL_SEL_VADDR);
	agc_cntl_sel_rbus_data.agc_if_manu_en = agc_if_manu_en;
	rtd_outl(IFD_AGC_CNTL_SEL_VADDR, agc_cntl_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_if_manual_en_get_info
 *
 *
 * @param <void>
 * @return { agc_if_manu_en }
 */
UINT16 drv_ifd_agc_if_manual_en_get_info(void)
{
	agc_cntl_sel_RBUS agc_cntl_sel_rbus_data;

	agc_cntl_sel_rbus_data.regValue = rtd_inl(IFD_AGC_CNTL_SEL_VADDR);
	return (agc_cntl_sel_rbus_data.agc_if_manu_en);
}
/*=============================================================*/
/**
 * drv_ifd_agc_if_manual_gain
 *
 *
 * @param <agc_if_manu_value>
 * @return { void }
 */
void drv_ifd_agc_if_manual_gain(UINT16 agc_if_manu_value)
{

	agc_if_manu_value_RBUS agc_if_manu_value_rbus_data;
	agc_if_manu_value_rbus_data.regValue = rtd_inl(IFD_AGC_IF_MANU_VALUE_VADDR);
	agc_if_manu_value_rbus_data.agc_if_manu_value = agc_if_manu_value;
	rtd_outl(IFD_AGC_IF_MANU_VALUE_VADDR, agc_if_manu_value_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_if_manual_gain_get_info
 *
 *
 * @param <void>
 * @return { agc_if_manu_value }
 */
UINT16 drv_ifd_agc_if_manual_gain_get_info(void)
{
	agc_if_manu_value_RBUS agc_if_manu_value_rbus_data;

	agc_if_manu_value_rbus_data.regValue = rtd_inl(IFD_AGC_IF_MANU_VALUE_VADDR);
	return (agc_if_manu_value_rbus_data.agc_if_manu_value);
}
/*=============================================================*/
/**
 * drv_ifd_agc_rf_manual_en
 *
 *
 * @param <agc_rf_manu_en>
 * @return { void }
 */
void drv_ifd_agc_rf_manual_en(bool agc_rf_manu_en)
{
	agc_cntl_sel_RBUS agc_cntl_sel_rbus_data;

	agc_cntl_sel_rbus_data.regValue = rtd_inl(IFD_AGC_CNTL_SEL_VADDR);
	agc_cntl_sel_rbus_data.agc_rf_manu_en = agc_rf_manu_en;
	rtd_outl(IFD_AGC_CNTL_SEL_VADDR, agc_cntl_sel_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_rf_manual_en_get_info
 *
 *
 * @param <void>
 * @return { agc_rf_manu_en }
 */
bool drv_ifd_agc_rf_manual_en_get_info(void)
{
	agc_cntl_sel_RBUS agc_cntl_sel_rbus_data;

	agc_cntl_sel_rbus_data.regValue = rtd_inl(IFD_AGC_CNTL_SEL_VADDR);
	return (agc_cntl_sel_rbus_data.agc_rf_manu_en);
}
/*=============================================================*/
/**
 * drv_ifd_agc_manual_rf_gain
 *
 *
 * @param <agc_rf_manu_value>
 * @return { void }
 */
void drv_ifd_agc_manual_rf_gain(UINT16 agc_rf_manu_value)
{
	agc_rf_manu_value_RBUS agc_rf_manu_value_rbus_data;

	agc_rf_manu_value_rbus_data.regValue = rtd_inl(IFD_AGC_RF_MANU_VALUE_VADDR);
	agc_rf_manu_value_rbus_data.agc_rf_manu_value = agc_rf_manu_value;
	rtd_outl(IFD_AGC_RF_MANU_VALUE_VADDR, agc_rf_manu_value_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_manual_rf_gain
 *
 *
 * @param <void>
 * @return { agc_rf_manu_value }
 */
UINT16 drv_ifd_agc_manual_rf_gain_get_info(void)
{
	agc_rf_manu_value_RBUS agc_rf_manu_value_rbus_data;

	agc_rf_manu_value_rbus_data.regValue = rtd_inl(IFD_AGC_RF_MANU_VALUE_VADDR);
	return (agc_rf_manu_value_rbus_data.agc_rf_manu_value);
}
/*=============================================================*/
/**
 * drv_ifd_agc_manual_en
 *
 *
 * @param <agc_rf_manu_en><agc_rf_manu_value>
 * @return { void }
 */
void drv_ifd_agc_manual_en(bool agc_manual_en, UINT16 agc_manual_value)
{
	agc_cntl_sel_RBUS agc_cntl_sel_rbus_data;
	agc_manu_value_RBUS agc_manu_value_rbus_data;

	agc_cntl_sel_rbus_data.regValue = rtd_inl(IFD_AGC_CNTL_SEL_VADDR);
	agc_cntl_sel_rbus_data.agc_rf_manu_en = agc_manual_en;
	rtd_outl(IFD_AGC_CNTL_SEL_VADDR, agc_cntl_sel_rbus_data.regValue);

	agc_manu_value_rbus_data.regValue = rtd_inl(IFD_AGC_IF_MANU_VALUE_VADDR);
	agc_manu_value_rbus_data.agc_manu_value = agc_manual_value;
	rtd_outl(IFD_AGC_IF_MANU_VALUE_VADDR, agc_manu_value_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_kp_settings
 *
 *
 * @param <agc_kp>
 * @return { void }
 */
void drv_ifd_agc_loop1_kp_settings(UINT8 agc_kp)
{
	ki_val_RBUS ki_val_rbus_data;

	ki_val_rbus_data.regValue = rtd_inl(IFD_KI_VAL_VADDR);
	ki_val_rbus_data.agc_kp = agc_kp;
	rtd_outl(IFD_KI_VAL_VADDR, ki_val_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_ki_settings
 *
 *
 * @param <agc_ki>
 * @return { void }
 */
void drv_ifd_agc_loop1_ki_settings(UINT8 agc_ki)
{
	ki_val_RBUS ki_val_rbus_data;

	ki_val_rbus_data.regValue = rtd_inl(IFD_KI_VAL_VADDR);
	ki_val_rbus_data.agc_ki = agc_ki;
	rtd_outl(IFD_KI_VAL_VADDR, ki_val_rbus_data.regValue);
}

/*=============================================================*/
/**
 * drv_ifd_agc_loop1_pishift_settings
 *
 *
 * @param <agc_kpd_add_method_shift>
 * @return { void }
 */
void drv_ifd_agc_loop1_pishift_settings( UINT8 agc_kpd_add_method_shift)
{

//**************irene reminder**************
// agc_kpd_add_method_shift is signed value need modify
	ki_val_RBUS ki_val_rbus_data;

	ki_val_rbus_data.regValue = rtd_inl(IFD_KI_VAL_VADDR);
	ki_val_rbus_data.agc_kpd_add_method_shift = agc_kpd_add_method_shift;
	rtd_outl(IFD_KI_VAL_VADDR, ki_val_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_loop1_kp_settings
 *
 *
 * @param <void>
 * @return <agc_kp>
 */
UINT8 drv_ifd_get_agc_loop1_kp_settings()
{
	ki_val_RBUS ki_val_rbus_data;
	ki_val_rbus_data.regValue = rtd_inl(IFD_KI_VAL_VADDR);

	return ki_val_rbus_data.agc_kp;
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_loop1_ki_settings
 *
 *
 * @param <void>
 * @return <agc_ki >
 */
UINT8 drv_ifd_get_agc_loop1_ki_settings()
{
	ki_val_RBUS ki_val_rbus_data;
	ki_val_rbus_data.regValue = rtd_inl(IFD_KI_VAL_VADDR);

	return ki_val_rbus_data.agc_ki;
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_loop1_pishift_settings
 *
 *
 * @param <void>
 * @return <agc_kpd_add_method_shift >
 */
UINT8 drv_ifd_get_agc_loop1_pishift_settings()
{
	ki_val_RBUS ki_val_rbus_data;
	ki_val_rbus_data.regValue = rtd_inl(IFD_KI_VAL_VADDR);

	return ki_val_rbus_data.agc_kpd_add_method_shift;
}
/*=============================================================*/
/**
 * drv_ifd_agc_rf_max
 *
 *
 * @param <rf_max>
 * @return <void >
 */
void drv_ifd_agc_rf_max(UINT16 rf_max)
{
	rf_agc_limit_value_RBUS rf_agc_limit_value_rbus_data;
	rf_agc_limit_value_rbus_data.regValue = rtd_inl(IFD_RF_AGC_LIMIT_VALUE_VADDR);
	rf_agc_limit_value_rbus_data.agc_rf_max = rf_max;
	rtd_outl(IFD_RF_AGC_LIMIT_VALUE_VADDR, rf_agc_limit_value_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_rf_max_get_info
 *
 *
 * @param <void>
 * @return <rf_max >
 */
UINT16 drv_ifd_agc_rf_max_get_info()
{

	rf_agc_limit_value_RBUS rf_agc_limit_value_rbus_data;
	rf_agc_limit_value_rbus_data.regValue = rtd_inl(IFD_RF_AGC_LIMIT_VALUE_VADDR);
       return rf_agc_limit_value_rbus_data.agc_rf_max;

}
/*=============================================================*/
/**
 * drv_ifd_agc_rf_min
 *
 *
 * @param <rf_min>
 * @return <void >
 */
void drv_ifd_agc_rf_min(UINT16 rf_min)
{

	rf_agc_limit_value_RBUS rf_agc_limit_value_rbus_data;
	rf_agc_limit_value_rbus_data.regValue = rtd_inl(IFD_RF_AGC_LIMIT_VALUE_VADDR);
	rf_agc_limit_value_rbus_data.agc_rf_min = rf_min;
	rtd_outl(IFD_RF_AGC_LIMIT_VALUE_VADDR, rf_agc_limit_value_rbus_data.regValue);

}
/*=============================================================*/
/**
 * drv_ifd_agc_rf_min_get_info
 *
 *
 * @param <void>
 * @return <rf_min >
 */
UINT16 drv_ifd_agc_rf_min_get_info()
{

	rf_agc_limit_value_RBUS rf_agc_limit_value_rbus_data;
	rf_agc_limit_value_rbus_data.regValue = rtd_inl(IFD_RF_AGC_LIMIT_VALUE_VADDR);
       return rf_agc_limit_value_rbus_data.agc_rf_min;

}
void drv_ifd_agc_lock_thr(UINT8 thr)
{
	agc_lock_th_RBUS agc_lock_th_rbus_data;

	agc_lock_th_rbus_data.regValue = rtd_inl(IFD_AGC_LOCK_TH_VADDR);
	agc_lock_th_rbus_data.agc_lock_th = thr;
	rtd_outl(IFD_AGC_LOCK_TH_VADDR, agc_lock_th_rbus_data.regValue);
}
UINT8 drv_ifd_agc_lock_thr_get_info(void)
{
	agc_lock_th_RBUS agc_lock_th_rbus_data;

	agc_lock_th_rbus_data.regValue = rtd_inl(IFD_AGC_LOCK_TH_VADDR);

	return agc_lock_th_rbus_data.agc_lock_th;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop1_lock
 *
 *
 * @param <void>
 * @return <lock_status>
 */
bool drv_ifd_agc_get_loop1_lock()
{
	agc_lock_status_RBUS agc_lock_status_rbus_data;

	agc_lock_status_rbus_data.regValue = rtd_inl(IFD_AGC_LOCK_STATUS_VADDR);

	return agc_lock_status_rbus_data.agc_lock;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop1_fine_lock
 *
 *
 * @param <void>
 * @return <fine_lock_status>
 */
bool drv_ifd_agc_get_loop1_fine_lock()
{
	agc_lock_status_RBUS agc_lock_status_rbus_data;

	agc_lock_status_rbus_data.regValue = rtd_inl(IFD_AGC_LOCK_STATUS_VADDR);

	return agc_lock_status_rbus_data.agc_fine;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop1_peak_status
 *
 *
 * @param <void>
 * @return <peak_status>
 */
bool drv_ifd_agc_get_loop1_peak_status()
{
	agc_peak_detect_RBUS agc_peak_detect_rbus_data;

	agc_peak_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_DETECT_VADDR);

	return agc_peak_detect_rbus_data.agc_peak_status;
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_peak_en
 *
 *
 * @param <agc_peak_en>
 * @return { void }
 */
void drv_ifd_agc_loop1_peak_en(bool agc_peak_en)
{
	agc_peak_detect_RBUS agc_peak_detect_rbus_data;

	agc_peak_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_DETECT_VADDR);
	agc_peak_detect_rbus_data.agc_peak_en= agc_peak_en;
	rtd_outl(IFD_AGC_PEAK_DETECT_VADDR, agc_peak_detect_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_loop1_peak_en
 *
 *
 * @param <void>
 * @return <agc_peak_en>
 */
bool drv_ifd_get_agc_loop1_peak_en()
{
	agc_peak_detect_RBUS agc_peak_detect_rbus_data;

	agc_peak_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_DETECT_VADDR);

	return agc_peak_detect_rbus_data.agc_peak_en;
}
void drv_ifd_agc_loop1_peak_force(bool agc_peak_force)
{
	agc_peak_detect_RBUS agc_peak_detect_rbus_data;

	agc_peak_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_DETECT_VADDR);
	agc_peak_detect_rbus_data.agc_peak_force = agc_peak_force;
	rtd_outl(IFD_AGC_PEAK_DETECT_VADDR, agc_peak_detect_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_peak_target
 *
 *
 * @param <agc_peak_value>
 * @return { void }
 */
void drv_ifd_agc_peak_target(UINT16 agc_peak_value)
{
	agc_peak_value_RBUS agc_peak_value_rbus_data;

	agc_peak_value_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_VALUE_VADDR);
	agc_peak_value_rbus_data.agc_peak_value = agc_peak_value;
	rtd_outl(IFD_AGC_PEAK_VALUE_VADDR, agc_peak_value_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_peak_target_get_info
 *
 *
 * @param <void>
 * @return { agc_peak_value }
 */
UINT16  drv_ifd_agc_peak_target_get_info(void)
{
	agc_peak_value_RBUS agc_peak_value_rbus_data;

	agc_peak_value_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_VALUE_VADDR);
	return (agc_peak_value_rbus_data.agc_peak_value);
}

/*=============================================================*/
/**
 * drv_ifd_agc_get_loop1_err0
 *
 *
 * @param <void>
 * @return <agc_err>
 */
UINT16 drv_ifd_agc_get_loop1_err0()
{
	agc_err0_status_RBUS agc_err0_status_rbus_data;

	agc_err0_status_rbus_data.regValue = rtd_inl(IFD_AGC_ERR0_STATUS_VADDR);

	return agc_err0_status_rbus_data.agc_err;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop1_peak_error
 *
 *
 * @param <void>
 * @return <peak_error1>
 */
UINT16 drv_ifd_agc_get_loop1_peak_error()
{
	agc_err0_status_RBUS agc_err0_status_rbus_data;

	agc_err0_status_rbus_data.regValue = rtd_inl(IFD_AGC_ERR0_STATUS_VADDR);

	return agc_err0_status_rbus_data.agc_peak_error;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_if_output
 *
 *
 * @param <void>
 * @return <agc_if_mode>
 */
UINT16 drv_ifd_agc_get_if_output()
{
	agc_if_status_RBUS agc_if_status_rbus_data;

	agc_if_status_rbus_data.regValue = rtd_inl(IFD_AGC_IF_STATUS_VADDR);

	return agc_if_status_rbus_data.agc_if_mode;
}
/*=============================================================*/
/**
 * drv_ifd_agc_acc3_get_info
 *
 *
 * @param <void>
 * @return <agc_acc3>
 */
UINT16 drv_ifd_agc_acc3_get_info()
{
	agc_acc3_status_RBUS agc_acc3_status_rbus_data;

	agc_acc3_status_rbus_data.regValue = rtd_inl(IFD_AGC_ACC3_STATUS_VADDR);

	return agc_acc3_status_rbus_data.agc_acc3;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_rf_output
 *
 *
 * @param <void>
 * @return <agc_rf_mode>
 */
UINT16 drv_ifd_agc_get_rf_output()
{
	agc_rf_status_RBUS agc_rf_status_rbus_data;

	agc_rf_status_rbus_data.regValue = rtd_inl(IFD_AGC_RF_STATUS_VADDR);

	return agc_rf_status_rbus_data.agc_rf_mode;
}
/*=============================================================*/
/**
 * drv_ifd_agc_pga_manual_en
 *
 *
 * @param <agc_pga_fix_en><agc_pga_fix>
 * @return { void }
 */
void drv_ifd_agc_pga_manual_en(bool agc_pga_fix_en, UINT16 agc_pga_fix)
{
	agc_pga_1_RBUS agc_pga_1_rbus_data;

	agc_pga_1_rbus_data.regValue = rtd_inl(IFD_AGC_PGA_1_VADDR);
	agc_pga_1_rbus_data.agc_pga_fix_en = agc_pga_fix_en;
	agc_pga_1_rbus_data.agc_pga_fix = agc_pga_fix;
	rtd_outl(IFD_AGC_PGA_1_VADDR, agc_pga_1_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_pga_manual_en_get_info
 *
 *
 * @param { void }
 * @return { agc_pga_fix_en }
 */
bool drv_ifd_agc_pga_manual_en_get_info()
{
	agc_pga_1_RBUS agc_pga_1_rbus_data;

	agc_pga_1_rbus_data.regValue = rtd_inl(IFD_AGC_PGA_1_VADDR);
	return agc_pga_1_rbus_data.agc_pga_fix_en;
}
/*=============================================================*/
/**
 * drv_ifd_agc_pga_manual_index_get_info
 *
 *
 * @param { void }
 * @return { index_output }
 */
 UINT8 drv_ifd_agc_pga_manual_index_get_info()
{
	agc_pga_1_RBUS agc_pga_1_rbus_data;
	UINT16 index_output =0;
	UINT16 err_temp=0;

	agc_pga_1_rbus_data.regValue = rtd_inl(IFD_AGC_PGA_1_VADDR);
	err_temp =  agc_pga_1_rbus_data.agc_pga_fix;
	index_output = (err_temp & 0x000f)+(((err_temp & 0x1c00)>>10)+((err_temp & 0x0380)>>7)+((err_temp & 0x0070)>>4))*12;;
	if(index_output > (PGA_TABLE_SIZE-1))
		index_output = (PGA_TABLE_SIZE-1);
	return ((UINT8)index_output);
}
/*=============================================================*/
/**
 * drv_ifd_agc_sep_rf_if_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_sep_rf_if_en(bool enable)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);
	agc_sep_rf_if_rbus_data.agc_sep_rf_if_en= enable;
	rtd_outl(IFD_AGC_SEP_RF_IF_VADDR, agc_sep_rf_if_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_agc_if_kp
 *
 *
 * @param <agc_if_kp>
 * @return { void }
 */
void drv_ifd_set_agc_if_kp(UINT8 if_kp)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);
	agc_sep_rf_if_rbus_data.agc_if_kp= if_kp;
	rtd_outl(IFD_AGC_SEP_RF_IF_VADDR, agc_sep_rf_if_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_set_agc_if_ki
 *
 *
 * @param <agc_if_ki>
 * @return { void }
 */
void drv_ifd_set_agc_if_ki(UINT8 if_ki)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);
	agc_sep_rf_if_rbus_data.agc_if_ki= if_ki;
	rtd_outl(IFD_AGC_SEP_RF_IF_VADDR, agc_sep_rf_if_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_sep_rf_if_en_info
 *
 *
 * @param <void>
 * @return <enable>
 */
bool drv_ifd_get_agc_sep_rf_if_en_info()
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);
	return agc_sep_rf_if_rbus_data.agc_sep_rf_if_en;
}

/*=============================================================*/
/**
 * drv_ifd_agc_vtop
 *
 *
 * @param <agc_vtop>
 * @return { void }
 */
void drv_ifd_agc_vtop(UINT32 agc_vtop)
{
	vtop_value_RBUS vtop_value_rbus_data;

	vtop_value_rbus_data.regValue = rtd_inl(IFD_VTOP_VALUE_VADDR);
	vtop_value_rbus_data.agc_vtop = agc_vtop;
	rtd_outl(IFD_VTOP_VALUE_VADDR, vtop_value_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_vtop
 *
 *
 * @param <void>
 * @return <agc_vtop>
 */
UINT32 drv_ifd_get_agc_vtop()
{
	vtop_value_RBUS vtop_value_rbus_data;

	vtop_value_rbus_data.regValue = rtd_inl(IFD_VTOP_VALUE_VADDR);
	return vtop_value_rbus_data.agc_vtop;
}

/*=============================================================*/
/**
 * drv_ifd_agc_krf
 *
 *
 * @param <agc_krf>
 * @return { void }
 */
void drv_ifd_agc_krf(UINT32 agc_krf)
{
	krf_value_RBUS krf_value_rbus_data;

	krf_value_rbus_data.regValue = rtd_inl(IFD_KRF_VALUE_VADDR);
	krf_value_rbus_data.agc_krf = agc_krf;
	rtd_outl(IFD_KRF_VALUE_VADDR, krf_value_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_krf
 *
 *
 * @param <void>
 * @return <agc_krf>
 */
UINT32 drv_ifd_get_agc_krf()
{
	krf_value_RBUS krf_value_rbus_data;

	krf_value_rbus_data.regValue = rtd_inl(IFD_KRF_VALUE_VADDR);

	return krf_value_rbus_data.agc_krf;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_pga_code
 *
 *
 * @param <void>
 * @return <pga_set_read>
 */
UINT16 drv_ifd_agc_get_pga_code()
{
	read_pga_RBUS read_pga_rbus_data;

	read_pga_rbus_data.regValue = rtd_inl(IFD_READ_PGA_VADDR);

	return read_pga_rbus_data.pga_set_read;
}
/*=============================================================*/
/**
 * drv_ifd_agc_pga_index_get_info
 *
 *
 * @param { void }
 * @return { index_output }
 */
UINT8 drv_ifd_agc_pga_index_get_info()
{
	read_pga_RBUS read_pga_rbus_data;
	UINT16 index_output =0;
	UINT16 err_temp=0;

	read_pga_rbus_data.regValue = rtd_inl(IFD_READ_PGA_VADDR);

	err_temp =  read_pga_rbus_data.pga_set_read;
	index_output = (err_temp & 0x000f)+(((err_temp & 0x1c00)>>10)+((err_temp & 0x0380)>>7)+((err_temp & 0x0070)>>4))*12;;
	if(index_output > (PGA_TABLE_SIZE-1))
		index_output = (PGA_TABLE_SIZE-1);
	return ((UINT8)index_output);
	
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_hold
 *
 *
 * @param <agc_loop2_hold>
 * @return { void }
 */
void drv_ifd_agc_loop2_hold(bool agc_loop2_hold)
{
	agc_linebase_ctl_RBUS agc_linebase_ctl_rbus_data;

	agc_linebase_ctl_rbus_data.regValue= rtd_inl(IFD_AGC_LINEBASE_CTL_VADDR);
	agc_linebase_ctl_rbus_data.agc_loop2_hold = agc_loop2_hold;
	rtd_outl(IFD_AGC_LINEBASE_CTL_VADDR, agc_linebase_ctl_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_hold_get_info
 *
 *
 * @param <void>
 * @return { agc_loop2_hold }
 */
bool drv_ifd_agc_loop2_hold_get_info()
{
	agc_linebase_ctl_RBUS agc_linebase_ctl_rbus_data;

	agc_linebase_ctl_rbus_data.regValue= rtd_inl(IFD_AGC_LINEBASE_CTL_VADDR);
        return agc_linebase_ctl_rbus_data.agc_loop2_hold;
}
/*=============================================================*/
/**
 * drv_ifd_loop2_agcin_kpki_settings
 *
 *
 * @param <agc_in_kp><agc_in_ki><agc_in_kp_shift><agc_in_ki_shift>
 * @return { void }
 */
void drv_ifd_loop2_agcin_kpki_settings(UINT8 agc_in_kp, UINT8 agc_in_ki, UINT8 agc_in_kp_shift, UINT8 agc_in_ki_shift)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	agc_in_kp_ki_rbus_data.agc_in_kp = agc_in_kp;
	agc_in_kp_ki_rbus_data.agc_in_ki = agc_in_ki;
	agc_in_kp_ki_rbus_data.agc_in_kp_shift = agc_in_kp_shift;
	agc_in_kp_ki_rbus_data.agc_in_ki_shift = agc_in_ki_shift;
	rtd_outl(IFD_AGC_IN_KP_KI_VADDR, agc_in_kp_ki_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_kp_settings
 *
 *
 * @param <agc_in_kp>
 * @return { void }
 */
void drv_ifd_agc_loop2_kp_settings(UINT8 agc_in_kp)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	agc_in_kp_ki_rbus_data.agc_in_kp = agc_in_kp;
	rtd_outl(IFD_AGC_IN_KP_KI_VADDR, agc_in_kp_ki_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_kp_settings_get_info
 *
 *
 * @param <void>
 * @return { agc_in_kp }
 */
UINT8 drv_ifd_agc_loop2_kp_settings_get_info(void)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	return (agc_in_kp_ki_rbus_data.agc_in_kp);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_ki_settings
 *
 *
 * @param <agc_in_ki>
 * @return { void }
 */
void drv_ifd_agc_loop2_ki_settings(UINT8 agc_in_ki)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	agc_in_kp_ki_rbus_data.agc_in_ki = agc_in_ki;
	rtd_outl(IFD_AGC_IN_KP_KI_VADDR, agc_in_kp_ki_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_ki_settings_get_info
 *
 *
 * @param <void>
 * @return { agc_in_ki }
 */
UINT8 drv_ifd_agc_loop2_ki_settings_get_info(void)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	return (agc_in_kp_ki_rbus_data.agc_in_ki);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_kishift_settings
 *
 *
 * @param <agc_in_ki_shift>
 * @return { void }
 */
void drv_ifd_agc_loop2_kishift_settings(UINT8 agc_in_ki_shift)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	agc_in_kp_ki_rbus_data.agc_in_ki_shift = agc_in_ki_shift;
	rtd_outl(IFD_AGC_IN_KP_KI_VADDR, agc_in_kp_ki_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_kishift_settings_get_info
 *
 *
 * @param <void>
 * @return { agc_in_ki_shift }
 */
UINT8 drv_ifd_agc_loop2_kishift_settings_get_info(void)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	return (agc_in_kp_ki_rbus_data.agc_in_ki_shift);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_kpshift_settings
 *
 *
 * @param <agc_in_kp_shift>
 * @return { void }
 */
void drv_ifd_agc_loop2_kpshift_settings(UINT8 agc_in_kp_shift)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	agc_in_kp_ki_rbus_data.agc_in_kp_shift = agc_in_kp_shift;
	rtd_outl(IFD_AGC_IN_KP_KI_VADDR, agc_in_kp_ki_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_kpshift_settings_get_info
 *
 *
 * @param <void>
 * @return { agc_in_kp_shift }
 */
UINT8 drv_ifd_agc_loop2_kpshift_settings_get_info(void)
{
	agc_in_kp_ki_RBUS agc_in_kp_ki_rbus_data;

	agc_in_kp_ki_rbus_data.regValue = rtd_inl(IFD_AGC_IN_KP_KI_VADDR);
	return (agc_in_kp_ki_rbus_data.agc_in_kp_shift);
}
/*=============================================================*/
/**
 * drv_ifd_agc_dgain_boundary
 *
 *
 * @param <agc_in_max><agc_in_min>
 * @return { void }
 */
void drv_ifd_agc_dgain_boundary(UINT16 agc_in_max, UINT16 agc_in_min)
{
	agc_in_max_min_RBUS agc_in_max_min_rbus_data;

	agc_in_max_min_rbus_data.regValue = rtd_inl(IFD_AGC_IN_MAX_MIN_VADDR);
	agc_in_max_min_rbus_data.agc_in_max = agc_in_max;
	agc_in_max_min_rbus_data.agc_in_min = agc_in_min;
	rtd_outl(IFD_AGC_IN_MAX_MIN_VADDR, agc_in_max_min_rbus_data.regValue);

}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop2_max_out
 *
 *
 * @param {void}
 * @return  <max>
 */
UINT16 drv_ifd_agc_get_loop2_max_out()
{
	read_loop2_max_RBUS agc_max2_in_out_rbus_data;

	agc_max2_in_out_rbus_data.regValue = rtd_inl(IFD_READ_LOOP2_MAX_VADDR);

	return agc_max2_in_out_rbus_data.agc_max2_out;
}

/*=============================================================*/
/**
 * drv_ifd_agc_get_loop2_err
 *
 *
 * @param {void}
 * @return  <loop2_err>
 */
UINT16 drv_ifd_agc_get_loop2_err()
{
	agc_looop2_err_RBUS agc_looop2_err_rbus_data;

	agc_looop2_err_rbus_data.regValue= rtd_inl(IFD_AGC_LOOOP2_ERR_VADDR);

	return agc_looop2_err_rbus_data.loop2_err;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop1_dgain_output
 *
 *
 * @param {void}
 * @return  <agc_inner1>
 */
UINT16 drv_ifd_agc_get_loop1_dgain_output()
{
	agc_inner_status_RBUS agc_inner_status_rbus_data;

	agc_inner_status_rbus_data.regValue= rtd_inl(IFD_AGC_INNER_STATUS_VADDR);

	return agc_inner_status_rbus_data.agc_inner1;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop2_dgain_output
 *
 *
 * @param {void}
 * @return  <agc_inner2>
 */
UINT16 drv_ifd_agc_get_loop2_dgain_output()
{
	agc_inner_status_RBUS agc_inner_status_rbus_data;

	agc_inner_status_rbus_data.regValue= rtd_inl(IFD_AGC_INNER_STATUS_VADDR);

	return agc_inner_status_rbus_data.agc_inner2;
}
/*=============================================================*/
/**
 * drv_ifd_agc_adaptive_peak2_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_adaptive_peak2_en(bool enable)
{
	agc_peak2_detect_RBUS agc_peak2_detect_rbus_data;

	agc_peak2_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK2_DETECT_VADDR);
	agc_peak2_detect_rbus_data.agc_adaptive_peak2_en= enable;
	rtd_outl(IFD_AGC_PEAK2_DETECT_VADDR, agc_peak2_detect_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop2_peak_status
 *
 *
 * @param {void}
 * @return  <agc_peak2_status>
 */
bool drv_ifd_agc_get_loop2_peak_status()
{
	agc_peak2_detect_RBUS agc_peak2_detect_rbus_data;

	agc_peak2_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK2_DETECT_VADDR);

	return agc_peak2_detect_rbus_data.agc_peak2_status;
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_peak_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_loop2_peak_en(bool enable)
{
	agc_peak2_detect_RBUS agc_peak2_detect_rbus_data;

	agc_peak2_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK2_DETECT_VADDR);
	agc_peak2_detect_rbus_data.agc_peak2_en= enable;
	rtd_outl(IFD_AGC_PEAK2_DETECT_VADDR, agc_peak2_detect_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_peak_cnt
 *
 *
 * @param <agc_peak2_cnt>
 * @return { void }
 */
void drv_ifd_agc_loop2_peak_cnt(UINT16 agc_peak2_cnt)
{
	agc_peak2_detect_RBUS agc_peak2_detect_rbus_data;

	agc_peak2_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK2_DETECT_VADDR);
	agc_peak2_detect_rbus_data.agc_peak2_cnt = agc_peak2_cnt;
	rtd_outl(IFD_AGC_PEAK2_DETECT_VADDR, agc_peak2_detect_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_loop2_peak_en
 *
 *
 * @param <void>
 * @return <agc_peak2_en>
 */
bool drv_ifd_get_agc_loop2_peak_en()
{
	agc_peak2_detect_RBUS agc_peak2_detect_rbus_data;

	agc_peak2_detect_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK2_DETECT_VADDR);

	return agc_peak2_detect_rbus_data.agc_peak2_en;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop2_peak_error
 *
 *
 * @param {void}
 * @return  <error>
 */
UINT16 drv_ifd_agc_get_loop2_peak_error()
{

	agc_peak2_status_RBUS agc_peak2_status_rbus_data;

	agc_peak2_status_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK2_STATUS_VADDR);

	return agc_peak2_status_rbus_data.agc_peak2_error;
}
/*=============================================================*/
/**
 * drv_ifd_agc_get_loop2_peak_max
 *
 *
 * @param {void}
 * @return  <max>
 */
UINT16 drv_ifd_agc_get_loop2_peak_max()
{

	agc_peak2_status_RBUS agc_peak2_status_rbus_data;

	agc_peak2_status_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK2_STATUS_VADDR);

	return agc_peak2_status_rbus_data.agc_peak2_max;
}
/*=============================================================*/
/**
 * drv_ifd_agc_2step_en
 *
 *
 * @param <enable>
 * @return { void }
 */
void drv_ifd_agc_2step_en(bool enable)
{
	agc_2step_en_RBUS agc_2step_en_rbus_data;

	agc_2step_en_rbus_data.regValue = rtd_inl(IFD_AGC_2STEP_EN_VADDR);
	 agc_2step_en_rbus_data.agc_2step_en = enable;
	 rtd_outl(IFD_AGC_2STEP_EN_VADDR,agc_2step_en_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_get_agc_2step_en
 *
 *
 * @param <void>
 * @return <enable>
 */
bool drv_ifd_get_agc_2step_en()
{
	agc_2step_en_RBUS agc_2step_en_rbus_data;

	agc_2step_en_rbus_data.regValue = rtd_inl(IFD_AGC_2STEP_EN_VADDR);

	return agc_2step_en_rbus_data.agc_2step_en;
}
/*=============================================================*/
/**
 * drv_ifd_agc_dgain_up_dn_step
 *
 *
 * @param <agc_dgain_up_step><agc_dgain_down_step>
 * @return { void }
 */
void drv_ifd_agc_dgain_up_dn_step(UINT16 agc_dgain_up_step, UINT16 agc_dgain_down_step)
{
	agc_dgain_step_RBUS agc_dgain_step_rbus_data;

	agc_dgain_step_rbus_data.regValue = rtd_inl(IFD_AGC_DGAIN_STEP_VADDR);
	agc_dgain_step_rbus_data.agc_dgain_up_step = agc_dgain_up_step;
	agc_dgain_step_rbus_data.agc_dgain_down_step = agc_dgain_down_step;
	rtd_outl(IFD_AGC_DGAIN_STEP_VADDR, agc_dgain_step_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_dgain_up_dn_boundary
 *
 *
 * @param <agc_dgain_low_thr><agc_dgain_up_thr>
 * @return { void }
 */
void drv_ifd_agc_dgain_up_dn_boundary(UINT16 agc_dgain_low_thr, UINT16 agc_dgain_up_thr)
{
	agc_dgain_thr_RBUS agc_dgain_thr_rbus_data;

	agc_dgain_thr_rbus_data.regValue = rtd_inl(IFD_AGC_DGAIN_THR_VADDR);
	agc_dgain_thr_rbus_data.agc_dgain_up_thr = agc_dgain_up_thr;
	agc_dgain_thr_rbus_data.agc_dgain_low_thr = agc_dgain_low_thr;
	rtd_outl(IFD_AGC_DGAIN_THR_VADDR, agc_dgain_thr_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_2step_pga_step
 *
 *
 * @param <agc_step_num_pga>
 * @return { void }
 */
void drv_ifd_agc_2step_pga_step(UINT8 agc_step_num_pga)
{
	agc_dgain_to_pga_RBUS agc_dgain_to_pga_rbus_data;

	agc_dgain_to_pga_rbus_data.regValue = rtd_inl(IFD_AGC_DGAIN_TO_PGA_VADDR);
	agc_dgain_to_pga_rbus_data.agc_step_num_pga = agc_step_num_pga;
	rtd_outl(IFD_AGC_DGAIN_TO_PGA_VADDR, agc_dgain_to_pga_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_2step_pga_minimum
 *
 *
 * @param <agc_dgain_min_pga>
 * @return { void }
 */
void drv_ifd_agc_2step_pga_minimum(UINT32 agc_dgain_min_pga)
{
	agc_dgain_to_pga_RBUS agc_dgain_to_pga_rbus_data;

	agc_dgain_to_pga_rbus_data.regValue = rtd_inl(IFD_AGC_DGAIN_TO_PGA_VADDR);
	agc_dgain_to_pga_rbus_data.agc_dgain_min_pga = agc_dgain_min_pga;
	rtd_outl(IFD_AGC_DGAIN_TO_PGA_VADDR, agc_dgain_to_pga_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_2step_pga_minimum_get_info
 *
 *
 * @param <void>
 * @return < agc_dgain_min_pga >
 */
UINT32 drv_ifd_agc_2step_pga_minimum_get_info()
{
	agc_dgain_to_pga_RBUS agc_dgain_to_pga_rbus_data;

	agc_dgain_to_pga_rbus_data.regValue = rtd_inl(IFD_AGC_DGAIN_TO_PGA_VADDR);
       return agc_dgain_to_pga_rbus_data.agc_dgain_min_pga;

}
/*=============================================================*/
/**
 * drv_ifd_agc_mode_sel
 *
 *
 * @param <agc_mode>
 * @return { void }
 */
void drv_ifd_agc_mode_sel(IFD_AGC_MODE agc_mode)
{

	switch(agc_mode)
	{
		//case IFD_AGC_MODE_ORIGINAL:
			//drv_ifd_agc_original_mode(IFD_ENABLE);
		//	drv_ifd_agc_2step_en(IFD_DISABLE);
		//	break;
		case IFD_AGC_MODE_2LOOP:
			//drv_ifd_agc_original_mode(IFD_DISABLE);
			drv_ifd_agc_2step_en(IFD_DISABLE);
			break;
		case IFD_AGC_MODE_2STEP:
			//drv_ifd_agc_original_mode(IFD_DISABLE);
			drv_ifd_agc_2step_en(IFD_ENABLE);
			break;
		default:
			break;
	}

}
/*=============================================================*/
/**
 * drv_ifd_get_agc_mode_sel
 *
 *
 * @param <void>
 * @return <agc_mode>
 */
IFD_AGC_MODE drv_ifd_get_agc_mode_sel()
{
	if(drv_ifd_get_agc_2step_en())
		return IFD_AGC_MODE_2STEP;
	else
		return IFD_AGC_MODE_2LOOP;

}
/*=============================================================*/
/**
 * drv_ifd_agc_vsync_start1
 *
 *
 * @param <start><end>
 * @return { void }
 */
void drv_ifd_agc_vsync_start1(UINT16 start, UINT16 end)
{
	agc_vsync_start1_RBUS agc_vsync_start1_rbus_data;

	agc_vsync_start1_rbus_data.regValue = rtd_inl(IFD_AGC_VSYNC_START1_VADDR);
	agc_vsync_start1_rbus_data.agc_vsync_start= start;
	agc_vsync_start1_rbus_data.agc_vsync_end = end;
	rtd_outl(IFD_AGC_VSYNC_START1_VADDR, agc_vsync_start1_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_hsync_start1
 *
 *
 * @param <start><end>
 * @return { void }
 */
void drv_ifd_agc_hsync_start1(UINT16 start, UINT16 end)
{
	agc_hsync_start_RBUS agc_hsync_start_rbus_data;

	agc_hsync_start_rbus_data.regValue = rtd_inl(IFD_AGC_HSYNC_START_VADDR);
	agc_hsync_start_rbus_data.agc_hsync_start = start;
	agc_hsync_start_rbus_data.agc_hsync_end = end;
	rtd_outl(IFD_AGC_HSYNC_START_VADDR, agc_hsync_start_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_finetune_dn_sample
 *
 *
 * @param <dn_sample>
 * @return { void }
 */
 // irene note very strange for sync gate enable
void drv_ifd_agc_loop1_finetune_dn_sample(UINT16 dn_sample)
{
	agc_fine_tune_down_sample_RBUS agc_fine_tune_down_sample_rbus_data;

	agc_fine_tune_down_sample_rbus_data.regValue = rtd_inl(IFD_AGC_FINE_TUNE_DOWN_SAMPLE_VADDR);
	if(dn_sample == 0) {
		agc_fine_tune_down_sample_rbus_data.fine_tune_down_sample_en = IFD_DISABLE;
		agc_fine_tune_down_sample_rbus_data.fine_tune_down_sample = 0;
	} else {
		agc_fine_tune_down_sample_rbus_data.fine_tune_down_sample_en = IFD_ENABLE;
		agc_fine_tune_down_sample_rbus_data.fine_tune_down_sample = dn_sample;
	}
	rtd_outl(IFD_AGC_FINE_TUNE_DOWN_SAMPLE_VADDR, agc_fine_tune_down_sample_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_finetune_dn_sample_get_info
 *
 *
 * @param <void>
 * @return { dn_sample }
 */
UINT16 drv_ifd_agc_loop1_finetune_dn_sample_get_info(void)
{
	agc_fine_tune_down_sample_RBUS agc_fine_tune_down_sample_rbus_data;

	agc_fine_tune_down_sample_rbus_data.regValue = rtd_inl(IFD_AGC_FINE_TUNE_DOWN_SAMPLE_VADDR);
	return (agc_fine_tune_down_sample_rbus_data.fine_tune_down_sample);
}

/*=============================================================*/
/**
 * drv_ifd_agc_loop2_finetune_dn_sample
 *
 *
 * @param <dn_sample>
 * @return { void }
 */
// irene note very strange for sync gate enable
void drv_ifd_agc_loop2_finetune_dn_sample(UINT16 dn_sample)
{
	agc_fine_tune_down_sample_RBUS agc_fine_tune_down_sample_rbus_data;

	agc_fine_tune_down_sample_rbus_data.regValue = rtd_inl(IFD_AGC_FINE_TUNE_DOWN_SAMPLE_VADDR);
	if(dn_sample == 0) {
		agc_fine_tune_down_sample_rbus_data.fine_tune2_down_sample_en = IFD_DISABLE;
		agc_fine_tune_down_sample_rbus_data.fine_tune2_down_sample = 0;
	} else {
		agc_fine_tune_down_sample_rbus_data.fine_tune2_down_sample_en = IFD_ENABLE;
		agc_fine_tune_down_sample_rbus_data.fine_tune2_down_sample = dn_sample;
	}
	rtd_outl(IFD_AGC_FINE_TUNE_DOWN_SAMPLE_VADDR, agc_fine_tune_down_sample_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_finetune_dn_sample_get_info
 *
 *
 * @param <void>
 * @return { dn_sample }
 */
 UINT16 drv_ifd_agc_loop2_finetune_dn_sample_get_info(void)
{
	agc_fine_tune_down_sample_RBUS agc_fine_tune_down_sample_rbus_data;

	agc_fine_tune_down_sample_rbus_data.regValue = rtd_inl(IFD_AGC_FINE_TUNE_DOWN_SAMPLE_VADDR);
	return (agc_fine_tune_down_sample_rbus_data.fine_tune2_down_sample);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_dn_sample
 *
 *
 * @param <dnsample>
 * @return { void }
 */
void drv_ifd_agc_loop1_dn_sample (UINT16 dnsample)
{
	agc_max_count_for_coarse_mode_agc_lock2_RBUS agc_max_count_for_coarse_mode_agc_lock2_rbus_data;

	agc_max_count_for_coarse_mode_agc_lock2_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_LOCK2_VADDR);
	agc_max_count_for_coarse_mode_agc_lock2_rbus_data.agc_loop1_downsample_sel = dnsample;
	rtd_outl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_LOCK2_VADDR, agc_max_count_for_coarse_mode_agc_lock2_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop1_dn_sample_get_info
 *
 *
 * @param <void>
 * @return { dnsample }
 */
UINT16 drv_ifd_agc_loop1_dn_sample_get_info(void)
{
	agc_max_count_for_coarse_mode_agc_lock2_RBUS agc_max_count_for_coarse_mode_agc_lock2_rbus_data;

	agc_max_count_for_coarse_mode_agc_lock2_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_COUNT_FOR_COARSE_MODE_AGC_LOCK2_VADDR);
	return (agc_max_count_for_coarse_mode_agc_lock2_rbus_data.agc_loop1_downsample_sel);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_dn_sample
 *
 *
 * @param <dnsample>
 * @return { void }
 */
void drv_ifd_agc_loop2_dn_sample(UINT16 dnsample)
{
	agc_loop2_cntl_RBUS agc_loop2_cntl_rbus_data;

	agc_loop2_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_LOOP2_CNTL_VADDR);
	agc_loop2_cntl_rbus_data.agc_loop2_downsample_sel = dnsample;
	rtd_outl(IFD_AGC_LOOP2_CNTL_VADDR, agc_loop2_cntl_rbus_data.regValue);
}
/*=============================================================*/
/**
 * drv_ifd_agc_loop2_dn_sample_get_info
 *
 *
 * @param <void>
 * @return { dnsample }
 */
UINT16 drv_ifd_agc_loop2_dn_sample_get_info(void)
{
	agc_loop2_cntl_RBUS agc_loop2_cntl_rbus_data;

	agc_loop2_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_LOOP2_CNTL_VADDR);
	return (agc_loop2_cntl_rbus_data.agc_loop2_downsample_sel);
}

/*=============================================================*/
/**
 * drv_ifd_rf_full_get_info
 *
 *
 * @param <void>
 * @return { dnsample }
 */
bool drv_ifd_rf_full_get_info(void)
{
	agc_2step_status_RBUS agc_2step_status_rbus_data;

	agc_2step_status_rbus_data.regValue = rtd_inl(IFD_AGC_2STEP_STATUS_VADDR);
	return (agc_2step_status_rbus_data.rf_full);
}
//=================================================================
//AGC Rf Hasten
//=================================================================
void drv_ifd_agc_set_rf_hasten_en(bool enable)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);
	agc_rf_hasten_rbus_data.agc_rf_hasten_en = enable;
	rtd_outl(IFD_AGC_RF_HASTEN_VADDR, agc_rf_hasten_rbus_data.regValue);
}
bool drv_ifd_agc_get_rf_hasten_en(void)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);

	return agc_rf_hasten_rbus_data.agc_rf_hasten_en;
}
void drv_ifd_agc_set_rf_hasten_ki(UINT8 ki)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);
	agc_rf_hasten_rbus_data.agc_ki_rf_hasten = ki;
	rtd_outl(IFD_AGC_RF_HASTEN_VADDR, agc_rf_hasten_rbus_data.regValue);
}
UINT8 drv_ifd_agc_get_rf_hasten_ki(void)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);

	return agc_rf_hasten_rbus_data.agc_ki_rf_hasten;
}
void drv_ifd_agc_set_rf_hasten_max_cntl(UINT16 max_cntl)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);
	agc_rf_hasten_rbus_data.agc_max_cntl_rf_hasten= max_cntl;
	rtd_outl(IFD_AGC_RF_HASTEN_VADDR, agc_rf_hasten_rbus_data.regValue);
}
UINT16 drv_ifd_agc_get_rf_hasten_max_cntl(void)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);

	return agc_rf_hasten_rbus_data.agc_max_cntl_rf_hasten;
}
void drv_ifd_agc_set_rf_hasten_thr(UINT16 thr)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);
	agc_rf_hasten_rbus_data.agc_rf_hasten_thr= thr;
	rtd_outl(IFD_AGC_RF_HASTEN_VADDR, agc_rf_hasten_rbus_data.regValue);
}
UINT16 drv_ifd_agc_get_rf_hasten_thr(void)
{
	agc_rf_hasten_RBUS agc_rf_hasten_rbus_data;

	agc_rf_hasten_rbus_data.regValue = rtd_inl(IFD_AGC_RF_HASTEN_VADDR);

	return agc_rf_hasten_rbus_data.agc_rf_hasten_thr;
}
//=================================================================
//AGC Sep Rf If
//=================================================================
void drv_ifd_agc_set_sep_rf_if_en(bool enable)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);
	agc_sep_rf_if_rbus_data.agc_sep_rf_if_en = enable;
	rtd_outl(IFD_AGC_SEP_RF_IF_VADDR, agc_sep_rf_if_rbus_data.regValue);
}
bool drv_ifd_agc_get_sep_rf_if_en(void)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);

	return agc_sep_rf_if_rbus_data.agc_sep_rf_if_en;
}
void drv_ifd_agc_set_sep_rf_if_ki(UINT8 ki)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);
	agc_sep_rf_if_rbus_data.agc_if_ki= ki;
	rtd_outl(IFD_AGC_SEP_RF_IF_VADDR, agc_sep_rf_if_rbus_data.regValue);
}
UINT8 drv_ifd_agc_get_sep_rf_if_ki(void)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);

	return agc_sep_rf_if_rbus_data.agc_if_ki;
}
void drv_ifd_agc_set_sep_rf_if_kpi(UINT8 kp)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);
	agc_sep_rf_if_rbus_data.agc_if_kp= kp;
	rtd_outl(IFD_AGC_SEP_RF_IF_VADDR, agc_sep_rf_if_rbus_data.regValue);
}
UINT8 drv_ifd_agc_get_sep_rf_if_kp(void)
{
	agc_sep_rf_if_RBUS agc_sep_rf_if_rbus_data;

	agc_sep_rf_if_rbus_data.regValue = rtd_inl(IFD_AGC_SEP_RF_IF_VADDR);

	return agc_sep_rf_if_rbus_data.agc_if_kp;
}
//=================================================================
//AGC Gain Average Control
//=================================================================
void drv_ifd_agc_average_control(UINT16 interval, bool sel, UINT8 length)
{
	agc_gain_avg_ctrl_RBUS agc_gain_avg_ctrl_rbus_data;

	agc_gain_avg_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_GAIN_AVG_CTRL_VADDR);
	agc_gain_avg_ctrl_rbus_data.agc_gain_avg_interval = interval;
	agc_gain_avg_ctrl_rbus_data.agc_gain_avg_sel = sel;
	agc_gain_avg_ctrl_rbus_data.agc_gain_avg_length = length;
	rtd_outl(IFD_AGC_GAIN_AVG_CTRL_VADDR, agc_gain_avg_ctrl_rbus_data.regValue);
}
void drv_ifd_agc_average_get_status(UINT16 *var, UINT16 *mean)
{
	agc_gain_status_RBUS agc_gain_status_rbus_data;

	agc_gain_status_rbus_data.regValue = rtd_inl(IFD_AGC_GAIN_STATUS_VADDR);
	*var = agc_gain_status_rbus_data.agc_gain_var;
	*mean = agc_gain_status_rbus_data.agc_gain_mean;
}
//=================================================================
//AGC Adaptive Target Control
//=================================================================
void drv_ifd_agc_adaptivetarget_fine_interval(UINT16 setting)
{
	agc_adapt_targ_cntl_RBUS agc_adapt_targ_cntl_rbus_data;

	agc_adapt_targ_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_CNTL_VADDR);
	agc_adapt_targ_cntl_rbus_data.agc_fine_adapt_interval = setting;
	rtd_outl(IFD_AGC_ADAPT_TARG_CNTL_VADDR, agc_adapt_targ_cntl_rbus_data.regValue);
}
UINT16 drv_ifd_agc_adaptivetarget_fine_interval_get_info(void)
{
	agc_adapt_targ_cntl_RBUS agc_adapt_targ_cntl_rbus_data;

	agc_adapt_targ_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_CNTL_VADDR);
	return agc_adapt_targ_cntl_rbus_data.agc_fine_adapt_interval;
}

void drv_ifd_agc_adaptivetarget_interval(UINT16 setting)
{
	agc_adapt_targ_cntl_RBUS agc_adapt_targ_cntl_rbus_data;

	agc_adapt_targ_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_CNTL_VADDR);
	agc_adapt_targ_cntl_rbus_data.agc_adapt_interval = setting;
	rtd_outl(IFD_AGC_ADAPT_TARG_CNTL_VADDR, agc_adapt_targ_cntl_rbus_data.regValue);
}
UINT16 drv_ifd_agc_adaptivetarget_interval_get_info(void)
{
	agc_adapt_targ_cntl_RBUS agc_adapt_targ_cntl_rbus_data;

	agc_adapt_targ_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_CNTL_VADDR);
	return agc_adapt_targ_cntl_rbus_data.agc_adapt_interval;
}

void drv_ifd_agc_adaptivetarget_en(bool enable)
{
	agc_adapt_targ_cntl_RBUS agc_adapt_targ_cntl_rbus_data;

	agc_adapt_targ_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_CNTL_VADDR);
	agc_adapt_targ_cntl_rbus_data.agc_adapt_targ_en= enable;
	rtd_outl(IFD_AGC_ADAPT_TARG_CNTL_VADDR, agc_adapt_targ_cntl_rbus_data.regValue);
}
bool drv_ifd_agc_adaptivetarget_en_get_info(void)
{
	agc_adapt_targ_cntl_RBUS agc_adapt_targ_cntl_rbus_data;

	agc_adapt_targ_cntl_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_CNTL_VADDR);
	return agc_adapt_targ_cntl_rbus_data.agc_adapt_targ_en;
}
void drv_ifd_agc_adaptivetarget_inc_thr(UINT16 setting)
{
	agc_adapt_targ_inc_thr_RBUS agc_adapt_targ_inc_thr_rbus_data;

	agc_adapt_targ_inc_thr_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_INC_THR_VADDR);
	agc_adapt_targ_inc_thr_rbus_data.agc_targ_inc_thr = setting;
	rtd_outl(IFD_AGC_ADAPT_TARG_INC_THR_VADDR, agc_adapt_targ_inc_thr_rbus_data.regValue);
}
UINT16 drv_ifd_agc_adaptivetarget_inc_thr_get_info(void)
{
	agc_adapt_targ_inc_thr_RBUS agc_adapt_targ_inc_thr_rbus_data;

	agc_adapt_targ_inc_thr_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_INC_THR_VADDR);
	return agc_adapt_targ_inc_thr_rbus_data.agc_targ_inc_thr;
}
void drv_ifd_agc_adaptivetarget_min_difftarg(UINT16 setting)
{
	agc_adapt_targ_min_val_RBUS agc_adapt_targ_min_val_rbus_data;

	agc_adapt_targ_min_val_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_MIN_VAL_VADDR);
	agc_adapt_targ_min_val_rbus_data.agc_min_diff_targ = setting;
	rtd_outl(IFD_AGC_ADAPT_TARG_MIN_VAL_VADDR, agc_adapt_targ_min_val_rbus_data.regValue);
}
UINT16 drv_ifd_agc_adaptivetarget_min_difftarg_get_info(void)
{
	agc_adapt_targ_min_val_RBUS agc_adapt_targ_min_val_rbus_data;

	agc_adapt_targ_min_val_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_MIN_VAL_VADDR);
	return agc_adapt_targ_min_val_rbus_data.agc_min_diff_targ;
}
void drv_ifd_agc_adaptivetarget_min_targ(UINT16 setting)
{
	agc_adapt_targ_min_val_RBUS agc_adapt_targ_min_val_rbus_data;

	agc_adapt_targ_min_val_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_MIN_VAL_VADDR);
	agc_adapt_targ_min_val_rbus_data.agc_min_targ = setting;
	rtd_outl(IFD_AGC_ADAPT_TARG_MIN_VAL_VADDR, agc_adapt_targ_min_val_rbus_data.regValue);
}
UINT16 drv_ifd_agc_adaptivetarget_min_targ_get_info(void)
{
	agc_adapt_targ_min_val_RBUS agc_adapt_targ_min_val_rbus_data;

	agc_adapt_targ_min_val_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_MIN_VAL_VADDR);
	return agc_adapt_targ_min_val_rbus_data.agc_min_targ;
}
void drv_ifd_agc_adaptivetarget_fine_targthr(UINT16 setting)
{
	agc_adapt_targ_fine_mode_RBUS agc_adapt_targ_fine_mode_rbus_data;

	agc_adapt_targ_fine_mode_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_FINE_MODE_VADDR);
	agc_adapt_targ_fine_mode_rbus_data.agc_fine_targ_thr= setting;
	rtd_outl(IFD_AGC_ADAPT_TARG_FINE_MODE_VADDR, agc_adapt_targ_fine_mode_rbus_data.regValue);
}
UINT16 drv_ifd_agc_adaptivetarget_fine_targthr_get_info(void)
{
	agc_adapt_targ_fine_mode_RBUS agc_adapt_targ_fine_mode_rbus_data;

	agc_adapt_targ_fine_mode_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_FINE_MODE_VADDR);
	return agc_adapt_targ_fine_mode_rbus_data.agc_fine_targ_thr;
}
void drv_ifd_agc_adaptivetarget_diff_coarsestep(UINT16 setting)
{
	agc_adapt_targ_fine_mode_RBUS agc_adapt_targ_fine_mode_rbus_data;

	agc_adapt_targ_fine_mode_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_FINE_MODE_VADDR);
	agc_adapt_targ_fine_mode_rbus_data.agc_diff_coarse_step= setting;
	rtd_outl(IFD_AGC_ADAPT_TARG_FINE_MODE_VADDR, agc_adapt_targ_fine_mode_rbus_data.regValue);
}
UINT16 drv_ifd_agc_adaptivetarget_diff_coarsestep_get_info(void)
{
	agc_adapt_targ_fine_mode_RBUS agc_adapt_targ_fine_mode_rbus_data;

	agc_adapt_targ_fine_mode_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_FINE_MODE_VADDR);
	return agc_adapt_targ_fine_mode_rbus_data.agc_diff_coarse_step;
}

UINT16 drv_ifd_agc_adaptivetarget_get_difftarget_status(void)
{
	agc_adapt_targ_status_RBUS agc_adapt_targ_status_rbus_data;

	agc_adapt_targ_status_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_STATUS_VADDR);

	return (UINT16)agc_adapt_targ_status_rbus_data.adaptive_diff_targ_ro;
}
UINT16 drv_ifd_agc_adaptivetarget_get_target_status(void)
{
	agc_adapt_targ_status_RBUS agc_adapt_targ_status_rbus_data;

	agc_adapt_targ_status_rbus_data.regValue = rtd_inl(IFD_AGC_ADAPT_TARG_STATUS_VADDR);

	return (UINT16)agc_adapt_targ_status_rbus_data.adaptive_targ_val_ro;
}
//=================================================================
//AGC Impulsive Gate
//=================================================================
void drv_ifd_agc_impulsive_gate_end(UINT16 setting)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	impulsive_gate_set_rbus_data.impn_gate_end = setting;
	rtd_outl(IFD_IMPULSIVE_GATE_SET_VADDR, impulsive_gate_set_rbus_data.regValue);
}
UINT16 drv_ifd_agc_impulsive_gate_end_get_info(void)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	return impulsive_gate_set_rbus_data.impn_gate_end;
}
void drv_ifd_agc_impulsive_det_thr(UINT16 setting)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	impulsive_gate_set_rbus_data.impn_det_thr = setting;
	rtd_outl(IFD_IMPULSIVE_GATE_SET_VADDR, impulsive_gate_set_rbus_data.regValue);
}
UINT16 drv_ifd_agc_impulsive_det_thr_get_info(void)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	return impulsive_gate_set_rbus_data.impn_det_thr;
}
void drv_ifd_agc_impulsive_det_input_sel(IFD_AGC_IMPULSIVE_DET_INPUT setting)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	impulsive_gate_set_rbus_data.impn_det_input_sel = setting;
	rtd_outl(IFD_IMPULSIVE_GATE_SET_VADDR, impulsive_gate_set_rbus_data.regValue);
}
IFD_AGC_IMPULSIVE_DET_INPUT drv_ifd_agc_impulsive_det_input_sel_get_info(void)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	return (IFD_AGC_IMPULSIVE_DET_INPUT)impulsive_gate_set_rbus_data.impn_det_input_sel;
}
void drv_ifd_agc_impulsive_mask_en(bool setting)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	impulsive_gate_set_rbus_data.agc_impn_mask_en= setting;
	rtd_outl(IFD_IMPULSIVE_GATE_SET_VADDR, impulsive_gate_set_rbus_data.regValue);
}
bool drv_ifd_agc_impulsive_mask_en_get_info(void)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	return impulsive_gate_set_rbus_data.agc_impn_mask_en;
}
void drv_ifd_agc_impulsive_det_en(bool setting)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	impulsive_gate_set_rbus_data.impn_det_en= setting;
	rtd_outl(IFD_IMPULSIVE_GATE_SET_VADDR, impulsive_gate_set_rbus_data.regValue);
}
bool drv_ifd_agc_impulsive_det_en_get_info(void)
{
	impulsive_gate_set_RBUS impulsive_gate_set_rbus_data;

	impulsive_gate_set_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SET_VADDR);
	return impulsive_gate_set_rbus_data.impn_det_en;
}
void drv_ifd_agc_impulsive_det_stop(UINT8 setting)
{
	impulsive_gate_setII_RBUS impulsive_gate_setII_rbus_data;

	impulsive_gate_setII_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SETII_VADDR);
	impulsive_gate_setII_rbus_data.impn_det_stop = setting;
	rtd_outl(IFD_IMPULSIVE_GATE_SETII_VADDR, impulsive_gate_setII_rbus_data.regValue);
}
UINT8 drv_ifd_agc_impulsive_det_stop_get_info(void)
{
	impulsive_gate_setII_RBUS impulsive_gate_setII_rbus_data;

	impulsive_gate_setII_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SETII_VADDR);
	return impulsive_gate_setII_rbus_data.impn_det_stop;
}
void drv_ifd_agc_impulsive_gate_delay(UINT16 setting)
{
	impulsive_gate_setII_RBUS impulsive_gate_setII_rbus_data;

	impulsive_gate_setII_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SETII_VADDR);
	impulsive_gate_setII_rbus_data.impn_gate_delay= setting;
	rtd_outl(IFD_IMPULSIVE_GATE_SETII_VADDR, impulsive_gate_setII_rbus_data.regValue);
}
UINT16 drv_ifd_agc_impulsive_gate_delay_get_info(void)
{
	impulsive_gate_setII_RBUS impulsive_gate_setII_rbus_data;

	impulsive_gate_setII_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SETII_VADDR);
	return impulsive_gate_setII_rbus_data.impn_gate_delay;
}
UINT16 drv_ifd_agc_impulsive_detected_get_info(void)
{
	impulsive_gate_setII_RBUS impulsive_gate_setII_rbus_data;

	impulsive_gate_setII_rbus_data.regValue = rtd_inl(IFD_IMPULSIVE_GATE_SETII_VADDR);
	return impulsive_gate_setII_rbus_data.impn_detect;
}
//=================================================================
//AGC Hum Ctrl
//=================================================================
UINT16 drv_ifd_agc_synclevel_var_get_info(void)
{
	agc_sync_level_status_RBUS agc_sync_level_status_rbus_data;

	agc_sync_level_status_rbus_data.regValue = rtd_inl(IFD_AGC_SYNC_LEVEL_STATUS_VADDR);
	return agc_sync_level_status_rbus_data.agc_sync_level_var;
}
UINT16 drv_ifd_agc_synclevel_mean_get_info(void)
{
	agc_sync_level_status_RBUS agc_sync_level_status_rbus_data;

	agc_sync_level_status_rbus_data.regValue = rtd_inl(IFD_AGC_SYNC_LEVEL_STATUS_VADDR);
	return agc_sync_level_status_rbus_data.agc_sync_level_mean;
}
UINT16 drv_ifd_agc_max_var_get_info(void)
{
	agc_max_var_status_RBUS agc_max_var_status_rbus_data;

	agc_max_var_status_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_VAR_STATUS_VADDR);
	return agc_max_var_status_rbus_data.agc_max_var;
}
UINT16 drv_ifd_agc_max_mean_get_info(void)
{
	agc_max_var_status_RBUS agc_max_var_status_rbus_data;

	agc_max_var_status_rbus_data.regValue = rtd_inl(IFD_AGC_MAX_VAR_STATUS_VADDR);
	return agc_max_var_status_rbus_data.agc_max_mean;
}
bool drv_ifd_agc_hum_detected_get_info(void)
{
	agc_hum_ctrl_RBUS agc_hum_ctrl_rbus_data;

	agc_hum_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_CTRL_VADDR);
	return agc_hum_ctrl_rbus_data.hum_detect;
}
void drv_ifd_agc_hum_debounce(UINT8 setting)
{
	agc_hum_ctrl_RBUS agc_hum_ctrl_rbus_data;

	agc_hum_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_CTRL_VADDR);
	agc_hum_ctrl_rbus_data.agc_hum_debounce = setting;
	rtd_outl(IFD_AGC_HUM_CTRL_VADDR, agc_hum_ctrl_rbus_data.regValue);
}
UINT8 drv_ifd_agc_hum_debounce_get_info(void)
{
	agc_hum_ctrl_RBUS agc_hum_ctrl_rbus_data;

	agc_hum_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_CTRL_VADDR);
	return agc_hum_ctrl_rbus_data.agc_hum_debounce;
}
void drv_ifd_agc_hum_update_sel(IFD_AGC_HUM_UPDATE_SEL setting)
{
	agc_hum_ctrl_RBUS agc_hum_ctrl_rbus_data;

	agc_hum_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_CTRL_VADDR);
	agc_hum_ctrl_rbus_data.agc_hum_update_sel= setting;
	rtd_outl(IFD_AGC_HUM_CTRL_VADDR, agc_hum_ctrl_rbus_data.regValue);
}
IFD_AGC_HUM_UPDATE_SEL drv_ifd_agc_hum_update_sel_get_info(void)
{
	agc_hum_ctrl_RBUS agc_hum_ctrl_rbus_data;

	agc_hum_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_CTRL_VADDR);
	return (IFD_AGC_HUM_UPDATE_SEL)agc_hum_ctrl_rbus_data.agc_hum_update_sel;
}
void drv_ifd_agc_hum_en(bool setting)
{
	agc_hum_ctrl_RBUS agc_hum_ctrl_rbus_data;

	agc_hum_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_CTRL_VADDR);
	agc_hum_ctrl_rbus_data.agc_hum_en= setting;
	rtd_outl(IFD_AGC_HUM_CTRL_VADDR, agc_hum_ctrl_rbus_data.regValue);
}
bool drv_ifd_agc_hum_en_get_info(void)
{
	agc_hum_ctrl_RBUS agc_hum_ctrl_rbus_data;

	agc_hum_ctrl_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_CTRL_VADDR);
	return agc_hum_ctrl_rbus_data.agc_hum_en;
}
void drv_ifd_agc_hum_max_thr_out(UINT16 setting)
{
	agc_hum_max_thr_RBUS agc_hum_max_thr_rbus_data;

	agc_hum_max_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_MAX_THR_VADDR);
	agc_hum_max_thr_rbus_data.agc_hum_max_thr_out = setting;
	rtd_outl(IFD_AGC_HUM_MAX_THR_VADDR, agc_hum_max_thr_rbus_data.regValue);
}
UINT16 drv_ifd_agc_hum_max_thr_out_get_info(void)
{
	agc_hum_max_thr_RBUS agc_hum_max_thr_rbus_data;

	agc_hum_max_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_MAX_THR_VADDR);
	return agc_hum_max_thr_rbus_data.agc_hum_max_thr_out;
}
void drv_ifd_agc_hum_max_thr_in(UINT16 setting)
{
	agc_hum_max_thr_RBUS agc_hum_max_thr_rbus_data;

	agc_hum_max_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_MAX_THR_VADDR);
	agc_hum_max_thr_rbus_data.agc_hum_max_thr_in = setting;
	rtd_outl(IFD_AGC_HUM_MAX_THR_VADDR, agc_hum_max_thr_rbus_data.regValue);
}
UINT16 drv_ifd_agc_hum_max_thr_in_get_info(void)
{
	agc_hum_max_thr_RBUS agc_hum_max_thr_rbus_data;

	agc_hum_max_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_MAX_THR_VADDR);
	return agc_hum_max_thr_rbus_data.agc_hum_max_thr_in;
}
void drv_ifd_agc_hum_synclevel_thr_out(UINT16 setting)
{
	agc_hum_sync_level_thr_RBUS agc_hum_sync_level_thr_rbus_data;

	agc_hum_sync_level_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_SYNC_LEVEL_THR_VADDR);
	agc_hum_sync_level_thr_rbus_data.agc_hum_sync_thr_out= setting;
	rtd_outl(IFD_AGC_HUM_SYNC_LEVEL_THR_VADDR, agc_hum_sync_level_thr_rbus_data.regValue);
}
UINT16 drv_ifd_agc_hum_synclevel_thr_out_get_info(void)
{
	agc_hum_sync_level_thr_RBUS agc_hum_sync_level_thr_rbus_data;

	agc_hum_sync_level_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_SYNC_LEVEL_THR_VADDR);
	return agc_hum_sync_level_thr_rbus_data.agc_hum_sync_thr_out;
}
void drv_ifd_agc_hum_synclevel_thr_in(UINT16 setting)
{
	agc_hum_sync_level_thr_RBUS agc_hum_sync_level_thr_rbus_data;

	agc_hum_sync_level_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_SYNC_LEVEL_THR_VADDR);
	agc_hum_sync_level_thr_rbus_data.agc_hum_sync_thr_in= setting;
	rtd_outl(IFD_AGC_HUM_SYNC_LEVEL_THR_VADDR, agc_hum_sync_level_thr_rbus_data.regValue);
}
UINT16 drv_ifd_agc_hum_synclevel_thr_in_get_info(void)
{
	agc_hum_sync_level_thr_RBUS agc_hum_sync_level_thr_rbus_data;

	agc_hum_sync_level_thr_rbus_data.regValue = rtd_inl(IFD_AGC_HUM_SYNC_LEVEL_THR_VADDR);
	return agc_hum_sync_level_thr_rbus_data.agc_hum_sync_thr_in;
}
//=================================================================
//AGC Sigma Delta
//=================================================================
void drv_ifd_agc_rfagc_padctrl(IFD_AGC_PADCTRL setting)
{
	sigma_delta_cntl_RBUS sigma_delta_cntl_rbus_data;

	sigma_delta_cntl_rbus_data.regValue = rtd_inl(IFD_SIGMA_DELTA_CNTL_VADDR);
	sigma_delta_cntl_rbus_data.agc_rf_pad_control = setting;
	rtd_outl(IFD_SIGMA_DELTA_CNTL_VADDR, sigma_delta_cntl_rbus_data.regValue);
}
IFD_AGC_PADCTRL drv_ifd_agc_rfagc_padctrl_get_info(void)
{
	sigma_delta_cntl_RBUS sigma_delta_cntl_rbus_data;

	sigma_delta_cntl_rbus_data.regValue = rtd_inl(IFD_SIGMA_DELTA_CNTL_VADDR);
	return (IFD_AGC_PADCTRL)sigma_delta_cntl_rbus_data.agc_rf_pad_control;
}
void drv_ifd_agc_ifagc_padctrl(IFD_AGC_PADCTRL setting)
{
	sigma_delta_cntl_RBUS sigma_delta_cntl_rbus_data;

	sigma_delta_cntl_rbus_data.regValue = rtd_inl(IFD_SIGMA_DELTA_CNTL_VADDR);
	sigma_delta_cntl_rbus_data.agc_if_pad_control = setting;
	rtd_outl(IFD_SIGMA_DELTA_CNTL_VADDR, sigma_delta_cntl_rbus_data.regValue);
}
IFD_AGC_PADCTRL drv_ifd_agc_ifagc_padctrl_get_info(void)
{
	sigma_delta_cntl_RBUS sigma_delta_cntl_rbus_data;

	sigma_delta_cntl_rbus_data.regValue = rtd_inl(IFD_SIGMA_DELTA_CNTL_VADDR);
	return (IFD_AGC_PADCTRL)sigma_delta_cntl_rbus_data.agc_if_pad_control;
}
void drv_ifd_agc_sigma_delta_dnsel(UINT8 setting)
{
	sigma_delta_cntl_RBUS sigma_delta_cntl_rbus_data;

	sigma_delta_cntl_rbus_data.regValue = rtd_inl(IFD_SIGMA_DELTA_CNTL_VADDR);
	sigma_delta_cntl_rbus_data.agc_sigma_delta_dnsel = setting;
	rtd_outl(IFD_SIGMA_DELTA_CNTL_VADDR, sigma_delta_cntl_rbus_data.regValue);
}
UINT8 drv_ifd_agc_sigma_delta_dnsel_get_info(void)
{
	sigma_delta_cntl_RBUS sigma_delta_cntl_rbus_data;

	sigma_delta_cntl_rbus_data.regValue = rtd_inl(IFD_SIGMA_DELTA_CNTL_VADDR);
	return sigma_delta_cntl_rbus_data.agc_sigma_delta_dnsel;
}
//=================================================================
//Auto PGA MIN
//=================================================================
void drv_ifd_agc_auto_pga_min_en(bool enable)
{
	agc_peak_lsadc_RBUS agc_peak_lsadc_rbus_data;

	agc_peak_lsadc_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_LSADC_VADDR);
	agc_peak_lsadc_rbus_data.agc_auto_min_pga_en = enable;

	rtd_outl(IFD_AGC_PEAK_LSADC_VADDR, agc_peak_lsadc_rbus_data.agc_auto_min_pga_en);
}
UINT8 drv_ifd_agc_lsadc_out_peak_value_get_info(void)
{
	agc_peak_lsadc_RBUS agc_peak_lsadc_rbus_data;

	agc_peak_lsadc_rbus_data.regValue = rtd_inl(IFD_AGC_PEAK_LSADC_VADDR);
	
	return agc_peak_lsadc_rbus_data.agc_peak_lsadc;
}
//=================================================================
//RSSI output
//=================================================================
UINT8 drv_ifd_agc_lsadc_out_get_info(void)
{
	lsadc_out_RBUS lsadc_out_rbus_data;

	lsadc_out_rbus_data.regValue = rtd_inl(IFD_LSADC_OUT_VADDR);

	return lsadc_out_rbus_data.ls_adc_out;
}
//=================================================================
//Input Power Detect
//=================================================================
void drv_ifd_agc_inputpower_mode(bool setting)
{
	input_power_ctrl_RBUS input_power_ctrl_rbus_data;

	input_power_ctrl_rbus_data.regValue = rtd_inl(IFD_INPUT_POWER_CTRL_VADDR);
	input_power_ctrl_rbus_data.input_power_mode = setting;
	
	rtd_outl(IFD_INPUT_POWER_CTRL_VADDR, input_power_ctrl_rbus_data.regValue);
}
void drv_ifd_agc_inputpower_modulation_sel(bool setting)
{
	input_power_ctrl_RBUS input_power_ctrl_rbus_data;

	input_power_ctrl_rbus_data.regValue = rtd_inl(IFD_INPUT_POWER_CTRL_VADDR);
	input_power_ctrl_rbus_data.input_power_mod_sel= setting;
	
	rtd_outl(IFD_INPUT_POWER_CTRL_VADDR, input_power_ctrl_rbus_data.regValue);
}
void drv_ifd_agc_inputpower_cal_reset(bool setting)
{
	input_power_ctrl_RBUS input_power_ctrl_rbus_data;

	input_power_ctrl_rbus_data.regValue = rtd_inl(IFD_INPUT_POWER_CTRL_VADDR);
	input_power_ctrl_rbus_data.input_power_cal_reset= setting;
	
	rtd_outl(IFD_INPUT_POWER_CTRL_VADDR, input_power_ctrl_rbus_data.regValue);
}
void drv_ifd_agc_inputpower_pc_sel(bool setting)
{
	input_power_ctrl_RBUS input_power_ctrl_rbus_data;

	input_power_ctrl_rbus_data.regValue = rtd_inl(IFD_INPUT_POWER_CTRL_VADDR);
	input_power_ctrl_rbus_data.input_power_pc_sel= setting;
	
	rtd_outl(IFD_INPUT_POWER_CTRL_VADDR, input_power_ctrl_rbus_data.regValue);
}
void drv_ifd_agc_inputpower_sequentialmode_detect_freq(UINT32 *freq)
{
	UINT32 nco[10], i;
	UINT32 addr_base=IFD_NCO_IF_VADDR;

	for(i=0;i<10;i++)
	{
			nco[i] = ((UINT32)(freq[i])/100);
			nco[i] <<= 16;
			nco[i] = nco[i]/54000;
	}
	for(i=0;i<5;i++)
	{
		rtd_outl(addr_base+(i*4), (nco[2*i+1] <<16)|nco[2*i]);
	}
}
void drv_ifd_agc_inputpower_scanmode_detect_freq(UINT32 *freq)
{
	UINT32 nco[10], i;
	UINT32 addr_base=IFD_NCO_SCAN_RANGE1_VADDR;

	for(i=0;i<4;i++)
	{
			nco[i] = ((UINT32)(freq[i])/100);
			nco[i] <<= 16;
			nco[i] = nco[i]/54000;
	}
	for(i=0;i<2;i++)
	{
		rtd_outl(addr_base+(i*4), (nco[2*i+1] <<16)|nco[2*i]);
	}
}
void drv_ifd_agc_inputpower_scanmode_offset(UINT8 setting)
{
	input_power_ctrl_RBUS input_power_ctrl_rbus_data;

	input_power_ctrl_rbus_data.regValue = rtd_inl(IFD_INPUT_POWER_CTRL_VADDR);
	input_power_ctrl_rbus_data.input_power_scan_mode_offset = setting;
	
	rtd_outl(IFD_INPUT_POWER_CTRL_VADDR, input_power_ctrl_rbus_data.regValue);
}
bool drv_ifd_agc_inputpower_detect_result(UINT32 *result)
{
	UINT32 read_data, i;
	UINT32 addr_base=IFD_INPUT_POWER_OUTPUT_IF_VADDR;
	input_power_ctrl_RBUS input_power_ctrl_rbus_data;
	input_power_done_RBUS input_power_done_rbus_data;

	input_power_ctrl_rbus_data.regValue = rtd_inl(IFD_INPUT_POWER_CTRL_VADDR);
	input_power_ctrl_rbus_data.input_power_cal_reset= 1;
	rtd_outl(IFD_INPUT_POWER_CTRL_VADDR, input_power_ctrl_rbus_data.regValue);
	input_power_ctrl_rbus_data.input_power_cal_reset= 0;
	rtd_outl(IFD_INPUT_POWER_CTRL_VADDR, input_power_ctrl_rbus_data.regValue);

	i=255;
	do{
		input_power_done_rbus_data.regValue = rtd_inl(IFD_INPUT_POWER_DONE_VADDR);
		if(input_power_done_rbus_data.input_power_detect_done) break;
		i--;
	}while(i);

	if(i){
		for(i=0;i<5;i++)
		{
			read_data = rtd_inl(addr_base+i*4);
			result[2*i] = read_data>>16;
			result[2*i+1] = read_data&0xffff;
		}
		return 1;
	}
	else
	{
		for(i=0;i<10;i++)
		{
			result[i] = 0;
		}
		return 0;
	}
}
//=================================================================
//RF recoder
//=================================================================
void drv_ifd_agc_rf_record_en(bool enable)
{
	agc_rf_record_enable_RBUS agc_rf_record_enable_rbus_data;

	agc_rf_record_enable_rbus_data.regValue = rtd_inl(IFD_AGC_RF_RECORD_ENABLE_VADDR);
	agc_rf_record_enable_rbus_data.agc_rf_record_en = enable;
	rtd_outl(IFD_AGC_RF_RECORD_ENABLE_VADDR, agc_rf_record_enable_rbus_data.regValue);
}
bool drv_ifd_agc_rf_record_en_get_info(void)
{
	agc_rf_record_enable_RBUS agc_rf_record_enable_rbus_data;

	agc_rf_record_enable_rbus_data.regValue = rtd_inl(IFD_AGC_RF_RECORD_ENABLE_VADDR);
	return agc_rf_record_enable_rbus_data.agc_rf_record_en;
}
void drv_ifd_agc_rf_record_len(UINT8 len)
{
	agc_rf_record_enable_RBUS agc_rf_record_enable_rbus_data;

	agc_rf_record_enable_rbus_data.regValue = rtd_inl(IFD_AGC_RF_RECORD_ENABLE_VADDR);
	agc_rf_record_enable_rbus_data.agc_rf_record_len = len;
	rtd_outl(IFD_AGC_RF_RECORD_ENABLE_VADDR, agc_rf_record_enable_rbus_data.regValue);
}
void drv_ifd_agc_rf_record_get_info(UINT16 *table)
{
	UINT32 addr_base = IFD_AGC_RF_RECORD_0_1_VADDR;
	UINT32 i, data;

	for(i=0;i<100;i++)
	{
		data = rtd_inl(addr_base+4*i);
		table[2*i]=(data>>12)&0x7ff;
		table[2*i+1]=data&0x7ff;
	}
}
