//############################################################################################################
//
// File Name: TV_1080i60.c
// Description: TV Encoder 1080i/60Hz initial setting
// Programmer: Ardor Yen
// Date: 2010/02/06
//
//############################################################################################################
#include "TVE_reg.h"
#include "qc_verify.h"
#include "TVE.h"
#include "crt_sys_reg.h"
void TVE_TV_1080i60(void)
{

    //0xb8000020
    rtd_outl(SYS_DISP_PLL_DIV_reg,
                     SYS_DISP_PLL_DIV_write_en2(1)|SYS_DISP_PLL_DIV_dac2_div(0)|	//216MHz for CVBS
                     SYS_DISP_PLL_DIV_write_en1(1)|SYS_DISP_PLL_DIV_dac1_div(4));	//148.5MHz for component DACs.
    //0xb8000024
    rtd_outl(SYS_DISP_PLL_DIV2_reg,
                     SYS_DISP_PLL_DIV2_write_en3(1)|SYS_DISP_PLL_DIV2_tve_div(2));	//74.25MHz to TVE

    //==========================================================================
    //DAC control
    //==========================================================================
    //0xb8018200
    rtd_outl(TVE_VIDEO_DAC_CTRL_0_reg,
                     TVE_VIDEO_DAC_CTRL_vdac_apow(1)|
                     TVE_VIDEO_DAC_CTRL_vdac_bpow(1)|
                     TVE_VIDEO_DAC_CTRL_vdac_cpow(1)|
                     TVE_VIDEO_DAC_CTRL_powldv_l(1)|
                     TVE_VIDEO_DAC_CTRL_stanby_l(0)|
                     TVE_VIDEO_DAC_CTRL_biasa_regl(5)|
                     TVE_VIDEO_DAC_CTRL_biasb_regl(5)|
                     TVE_VIDEO_DAC_CTRL_biasc_regl(5));
    //0xb8018204
    rtd_outl(TVE_VIDEO_DAC_CTRL_1_reg,
                     TVE_VIDEO_DAC_CTRL_vdac_apow(1)|
                     TVE_VIDEO_DAC_CTRL_vdac_bpow(1)|
                     TVE_VIDEO_DAC_CTRL_vdac_cpow(1)|
                     TVE_VIDEO_DAC_CTRL_powldv_l(1)|
                     TVE_VIDEO_DAC_CTRL_stanby_l(0)|
                     TVE_VIDEO_DAC_CTRL_biasa_regl(5)|
                     TVE_VIDEO_DAC_CTRL_biasb_regl(5)|
                     TVE_VIDEO_DAC_CTRL_biasc_regl(5));
    //0xb8018208
    rtd_outl(TVE_DAC_MUX_reg,
                     TVE_DAC_MUX_write_en6(0)|TVE_DAC_MUX_up_ctrl_prog(0)|
                     TVE_DAC_MUX_write_en5(1)|TVE_DAC_MUX_up_ctrl_int0(1)|
                     TVE_DAC_MUX_write_en4(1)|TVE_DAC_MUX_up_ctrl_int1(1)|
                     TVE_DAC_MUX_write_en3(1)|TVE_DAC_MUX_dacmode(0)| //if RTD1175/1075
                     //TVE_DAC_MUX_write_en3(1)|TVE_DAC_MUX_dacmode(3)| //if RTD1055
                     TVE_DAC_MUX_write_en2(0)|TVE_DAC_MUX_swap23(0)|
                     TVE_DAC_MUX_write_en1(0)|TVE_DAC_MUX_swap56(0));
    //0xb801820c
    rtd_outl(TVE_CMP_DLY_reg,
                     TVE_CMP_DLY_write_en3(1)|TVE_CMP_DLY_ygdelay(1)|
                     TVE_CMP_DLY_write_en2(1)|TVE_CMP_DLY_bdelay(0)|
                     TVE_CMP_DLY_write_en1(1)|TVE_CMP_DLY_rdelay(0));
    //0xb8018210
    rtd_outl(TVE_DAC_MISC_reg,
                     TVE_DAC_MISC_write_en3(1)|TVE_DAC_MISC_neg_out(0x02)|
                     TVE_DAC_MISC_write_en2(0)|TVE_DAC_MISC_out_control(0)|
                     TVE_DAC_MISC_write_en1(0)|TVE_DAC_MISC_dac_value(0));
    //0xb8018218
    rtd_outl(TVE_VIDEO_DAC_CTRL2_0_reg,
                     TVE_VIDEO_DAC_CTRL2_abiq_regl(5)|
                     TVE_VIDEO_DAC_CTRL2_ldvbias_regl(4)|
                     TVE_VIDEO_DAC_CTRL2_vcmref_regl(2)|
                     TVE_VIDEO_DAC_CTRL2_vdac_cf_regl(7)|
                     TVE_VIDEO_DAC_CTRL2_vdac_rf_regl(2));
    //0xb801821c
    rtd_outl(TVE_VIDEO_DAC_CTRL2_1_reg,
                     TVE_VIDEO_DAC_CTRL2_abiq_regl(5)|
                     TVE_VIDEO_DAC_CTRL2_ldvbias_regl(4)|
                     TVE_VIDEO_DAC_CTRL2_vcmref_regl(2)|
                     TVE_VIDEO_DAC_CTRL2_vdac_cf_regl(7)|
                     TVE_VIDEO_DAC_CTRL2_vdac_rf_regl(2));
		#if 0
			//FIR coeficients, high frequency enhancement
			//0xb801837c
//		 	rtd_outl(TVE_DAC1_FIR_1_reg, 0x00001000);
		 	//0xb8018380
//		 	rtd_outl(TVE_DAC1_FIR_2_reg, 0x00000000);
			//0xb801837c
		 	rtd_outl(TVE_DAC1_FIR_1_reg, 0x3f0b146d);
		 	//0xb8018380
		 	rtd_outl(TVE_DAC1_FIR_2_reg, 0x001b3e99);
		 	//0xb8018388
		 	rtd_outl(TVE_DAC2_FIR_1_reg, 0x3f0b146d);
		 	//0xb801838c
		 	rtd_outl(TVE_DAC2_FIR_2_reg, 0x001b3e99);
		 	//0xb8018390
		 	rtd_outl(TVE_DAC3_FIR_1_reg, 0x3f0b146d);
		 	//0xb8018394
		 	rtd_outl(TVE_DAC3_FIR_2_reg, 0x001b3e99);
		 	//0xb8018398
		 	rtd_outl(TVE_DAC4_FIR_1_reg, 0x3f0b146d);
		 	//0xb801839c
		 	rtd_outl(TVE_DAC4_FIR_2_reg, 0x001b3e99);
		#endif
    //==========================================================================
    //Macrovision
    //==========================================================================
    //0xb8018920
    rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x0));

    //==========================================================================
    //Sync generator register
    //==========================================================================
    //0xb8018000
    rtd_outl(TVE_SYNCGEN_RST_reg,
                     TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));
    //0xb8018008
    rtd_outl(TVE_SYNCGEN_P_reg,
                     TVE_SYNCGEN_P_write_en3(1)|TVE_SYNCGEN_P_i_p_sel(1)|
                     TVE_SYNCGEN_P_write_en2(1)|TVE_SYNCGEN_P_v_thr(1124)|
                     TVE_SYNCGEN_P_write_en1(1)|TVE_SYNCGEN_P_h_thr(1099));
    //0xb801800c
    rtd_outl(TVE_SYNCGEN_HDMI_reg,
                     TVE_SYNCGEN_HDMI_write_en3(1)|TVE_SYNCGEN_HDMI_i_p_sel(1)|
                     TVE_SYNCGEN_HDMI_write_en2(1)|TVE_SYNCGEN_HDMI_v_thr(1124)|
                     TVE_SYNCGEN_HDMI_write_en1(1)|TVE_SYNCGEN_HDMI_h_thr(1099));

    //==========================================================================
    //Active video position registers
    //==========================================================================
    //progressive Hpos
    //0xb8018054
    rtd_outl(TVE_AV_P_HPOS1_reg,
                     TVE_AV_P_HPOS1_write_en3(1)|TVE_AV_P_HPOS1_p_av_cord(0)|
                     TVE_AV_P_HPOS1_write_en2(1)|TVE_AV_P_HPOS1_p_h_st(127)|
                     TVE_AV_P_HPOS1_write_en1(1)|TVE_AV_P_HPOS1_p_h_end(1087));
    //0xb8018064
    rtd_outl(TVE_P_VPOS1_reg,
                     TVE_P_VPOS1_write_en2(1)|TVE_P_VPOS1_p_v_st(20)|
                     TVE_P_VPOS1_write_en1(1)|TVE_P_VPOS1_p_v_end(559));
    //0xb8018068
    rtd_outl(TVE_P_VPOS2_reg,
                     TVE_P_VPOS2_write_en2(1)|TVE_P_VPOS2_p_v_st(583)|
                     TVE_P_VPOS2_write_en1(1)|TVE_P_VPOS2_p_v_end(1122));
    //HDMI Hpos
    //0xb8018058
    rtd_outl(TVE_AV_H_HPOS1_reg,
                     TVE_AV_H_HPOS1_write_en3(1)|TVE_AV_H_HPOS1_h_av_cord(0)|
                     TVE_AV_H_HPOS1_write_en2(1)|TVE_AV_H_HPOS1_h_h_st(127)|
                     TVE_AV_H_HPOS1_write_en1(1)|TVE_AV_H_HPOS1_h_h_end(1087));
    //0xb801806c
    rtd_outl(TVE_H_VPOS1_reg,
                     TVE_H_VPOS1_write_en2(1)|TVE_H_VPOS1_h_v_st(20)|
                     TVE_H_VPOS1_write_en1(1)|TVE_H_VPOS1_h_v_end(559));
    //0xb8018070
    rtd_outl(TVE_H_VPOS2_reg,
                     TVE_H_VPOS2_write_en2(1)|TVE_H_VPOS2_h_v_st(583)|
                     TVE_H_VPOS2_write_en1(1)|TVE_H_VPOS2_h_v_end(1122));

    //==========================================================================
    //Slew rate and source control registers
    //==========================================================================
    //Active video slew rate
    //0xb8018048
    rtd_outl(TVE_AV_SLEW_reg,
                     TVE_AV_SLEW_write_en3(1)|TVE_AV_SLEW_p_en(1)|
                     TVE_AV_SLEW_write_en1(1)|TVE_AV_SLEW_p_slewrate(2));
    //TVE colorbar
    //0xb8018040
    rtd_outl(TVE_AV_CTRL_reg,
                     TVE_AV_CTRL_h_colorbar_ebl(1)|
                     TVE_AV_CTRL_h_black_ebl(0)|
                     TVE_AV_CTRL_i_colorbar_ebl(1)|
                     TVE_AV_CTRL_p_colorbar_ebl(1)|
                     TVE_AV_CTRL_i_black_ebl(0)|
                     TVE_AV_CTRL_p_black_ebl(0)|
                     TVE_AV_CTRL_write_data(1));
    //0xb8018040
    rtd_outl(TVE_AV_CTRL_reg,
                     TVE_AV_CTRL_h_colorbar_ebl(0)|
                     TVE_AV_CTRL_h_black_ebl(1)|
                     TVE_AV_CTRL_i_colorbar_ebl(0)|
                     TVE_AV_CTRL_p_colorbar_ebl(0)|
                     TVE_AV_CTRL_i_black_ebl(1)|
                     TVE_AV_CTRL_p_black_ebl(1)|
                     TVE_AV_CTRL_write_data(0));
    //0xb8018078
    rtd_outl(TVE_P_COLORBAR_HPOS_reg,
                     TVE_P_COLORBAR_HPOS_write_en2(1)|TVE_P_COLORBAR_HPOS_p_h_width(119)|
                     TVE_P_COLORBAR_HPOS_write_en1(1)|TVE_P_COLORBAR_HPOS_p_h_st_pos(127));
    //0xb801807c
    rtd_outl(TVE_H_COLORBAR_HPOS_reg,
                     TVE_H_COLORBAR_HPOS_write_en2(1)|TVE_H_COLORBAR_HPOS_p_h_width(119)|
                     TVE_H_COLORBAR_HPOS_write_en1(1)|TVE_H_COLORBAR_HPOS_p_h_st_pos(127));

    //==========================================================================
    //Progressive/HD registers
    //==========================================================================
    //0xb8018044
    rtd_outl(TVE_CAV_422_reg, TVE_CAV_422_fir422_sel(1));
    //0xb8018080
    rtd_outl(TVE_COMP_VSYNC_HPOS_reg,
                     TVE_COMP_VSYNC_HPOS_write_en3(1)|TVE_COMP_VSYNC_HPOS_negsyncst(24)|
                     TVE_COMP_VSYNC_HPOS_write_en2(1)|TVE_COMP_VSYNC_HPOS_possyncst(68)|
                     TVE_COMP_VSYNC_HPOS_write_en1(1)|TVE_COMP_VSYNC_HPOS_syncend(112));
    //0xb8018088
    rtd_outl(TVE_COMP_SER_HPOS_reg,
                     TVE_COMP_SER_HPOS_write_en2(1)|TVE_COMP_SER_HPOS_ser_hstart(195)|
                     TVE_COMP_SER_HPOS_write_en1(1)|TVE_COMP_SER_HPOS_ser_hend(1074));
    //0xb801808c
    rtd_outl(TVE_COMP_SER_VPOS_reg,
                     TVE_COMP_SER_VPOS_write_en2(1)|TVE_COMP_SER_VPOS_ser_vstart(0)|
                     TVE_COMP_SER_VPOS_write_en1(1)|TVE_COMP_SER_VPOS_ser_vend(9));
    //0xb8018090
    rtd_outl(TVE_COMP_DSYNC_VPOS_reg,
                     TVE_COMP_DSYNC_VPOS_write_en4(1)|TVE_COMP_DSYNC_VPOS_dsync_b_vstart(0)|
                     TVE_COMP_DSYNC_VPOS_write_en3(1)|TVE_COMP_DSYNC_VPOS_dsync_b_vend(10)|
                     TVE_COMP_DSYNC_VPOS_write_en2(1)|TVE_COMP_DSYNC_VPOS_dsync_t_vstart(0)|
                     TVE_COMP_DSYNC_VPOS_write_en1(1)|TVE_COMP_DSYNC_VPOS_dsync_t_vend(11));

    //==========================================================================
    //Video format setting
    //==========================================================================
    //0xb80180f0
    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x800));
    //0xb8018104
    rtd_outl(TVE_BLNK_COEFF_reg,
                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0)|
                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0));
    //0xb8018108
    rtd_outl(TVE_AV_COEFF1_reg,
                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x0)|
                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x1404));
    //0xb801810c
    rtd_outl(TVE_AV_COEFF2_reg,
                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x0)|
                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x0));
    //0xb8018110
    rtd_outl(TVE_AV_COEFF3_reg,
                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x1440)|
                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x1420));
    //0xb8018114
    rtd_outl(TVE_AV_COEFF4_reg,
                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0xd50)|
                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0xbd0));
    //0xb8018118
    rtd_outl(TVE_AV_COEFF5_reg,
                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0xbe8));

    //==========================================================================
    //Component registers
    //==========================================================================
    //0xb80180e0
    rtd_outl(TVE_COMP_SYNCLVL_reg,
                     TVE_COMP_SYNCLVL_write_en3(1)|TVE_COMP_SYNCLVL_slewrate(2)|
                     TVE_COMP_SYNCLVL_write_en2(1)|TVE_COMP_SYNCLVL_y_negsynclvl(0x30)|
                     TVE_COMP_SYNCLVL_write_en1(1)|TVE_COMP_SYNCLVL_y_possynclvl(0x7b0));
    //0xb80180e4
    rtd_outl(TVE_COMP_SYNC_SLEWLVL_reg,
                     TVE_COMP_SYNC_SLEWLVL_write_en2(1)|TVE_COMP_SYNC_SLEWLVL_y_sync_h(0x2b6)|
                     TVE_COMP_SYNC_SLEWLVL_write_en1(1)|TVE_COMP_SYNC_SLEWLVL_y_sync_m(0xd0));
    //0xb80180ec
    rtd_outl(TVE_COMP_PBPR_SYNCLVL_reg,
                     TVE_COMP_PBPR_SYNCLVL_write_en2(1)|TVE_COMP_PBPR_SYNCLVL_pbpr_negsynclvl(0x450)|
                     TVE_COMP_PBPR_SYNCLVL_write_en1(1)|TVE_COMP_PBPR_SYNCLVL_pbpr_possynclvl(0xbb0));

    //==========================================================================
    //General control register
    //==========================================================================
    //0xb8018010
    rtd_outl(TVE_COMP_CTRL_reg,
                     TVE_COMP_CTRL_comp_ebl(1)|
                     TVE_COMP_CTRL_sdtv_ebl(1)|
                     TVE_COMP_CTRL_vs_polar(1)|
                     TVE_COMP_CTRL_hs_polar(1)|
                     TVE_COMP_CTRL_vga_hvsync(1)|
                     TVE_COMP_CTRL_comp_sel(1)|
                     TVE_COMP_CTRL_sync_rb_ebl(1)|
                     TVE_COMP_CTRL_sync_g_ebl(1)|
                     TVE_COMP_CTRL_rgb_mod(1)|
                     TVE_COMP_CTRL_vbi_rb_ebl(1)|
                     TVE_COMP_CTRL_vbi_g_ebl(1)|
                     TVE_COMP_CTRL_hdsync(1)|
                     TVE_COMP_CTRL_syncmod_sel(1)|
                     TVE_COMP_CTRL_write_data(0));
    //0xb8018130
    rtd_outl(TVE_MV_CTRL_reg,
                     TVE_MV_CTRL_mv_rb_ebl(1)|
                     TVE_MV_CTRL_mv_g_ebl(1)|
                     TVE_MV_CTRL_mv_ebl(0)|
                     TVE_MV_CTRL_write_data(0));
    //0xb8018010
    rtd_outl(TVE_COMP_CTRL_reg,
                     TVE_COMP_CTRL_comp_ebl(1)|
                     TVE_COMP_CTRL_sdtv_ebl(0)|
                     TVE_COMP_CTRL_vs_polar(0)|
                     TVE_COMP_CTRL_hs_polar(0)|
                     TVE_COMP_CTRL_vga_hvsync(0)|
                     TVE_COMP_CTRL_comp_sel(0)|
                     TVE_COMP_CTRL_sync_rb_ebl(0)|
                     TVE_COMP_CTRL_sync_g_ebl(1)|
                     TVE_COMP_CTRL_rgb_mod(0)|
                     TVE_COMP_CTRL_vbi_rb_ebl(0)|
                     TVE_COMP_CTRL_vbi_g_ebl(1)|
                     TVE_COMP_CTRL_hdsync(1)|
                     TVE_COMP_CTRL_syncmod_sel(0)|
                     TVE_COMP_CTRL_write_data(1));
    return;
}
