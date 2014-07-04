//############################################################################################################
//
// File Name: TV_525i.c
// Description: TV Encoder 525i for YPbPr initial setting
// Parameter:
// Programmer: Ardor Yen
// Date: 2010/02/06
//
//############################################################################################################
#include "TVE_reg.h"
#include "qc_verify.h"
#include "TVE.h"
#include "crt_sys_reg.h"


void TVE_TV_525i(UINT32 RGB_mode, UINT32 video_format)
{
#if 0
    //0xb8000020
    rtd_outl(SYS_DISP_PLL_DIV_reg,
                     SYS_DISP_PLL_DIV_write_en2(1)|SYS_DISP_PLL_DIV_dac2_div(0)|	//216MHz for CVBS
                     SYS_DISP_PLL_DIV_write_en1(1)|SYS_DISP_PLL_DIV_dac1_div(0));	//216MHz for component DACs.
    //0xb8000024
    rtd_outl(SYS_DISP_PLL_DIV2_reg,
                     SYS_DISP_PLL_DIV2_write_en3(1)|SYS_DISP_PLL_DIV2_tve_div(1));	//27MHz to TVE
#else

	// Setting for turn on TVPLL and set frequency = 148.5MHz
	rtd_outl(0xb80001cc,0x00053622);	// SYS_TVPLL_CTRL1_reg
	rtd_outl(0xb80001d0,0x00000922);	// SYS_TVPLL_CTRL2_reg
	rtd_outl(0xb80001d4,0x00560000);	// SYS_TVPLL_CTRL3_reg
	rtd_outl(0xb80001c4,0x00409012);	// SYS_TMDS_SCR2_reg
	rtd_outl(0xb80001c8,0x04810b77);	// SYS_TMDS_SCR3_reg


	// Setting PLLDDS output frequency = 432MHz
	rtd_outl(0xb8000170,0x0727d244);	// SYS_PLL_DISP_SD1_reg
	rtd_outl(0xb8000174,0x00554000);	// SYS_PLL_DISP_SD2_reg

	rtd_outl(0xb8000024, 0x00018000);
	// Setting mux to select clocks frequency for dac1_clk = 148.5,clk_tve_p = 148.5 and from TVPLL. The dac2_clk = 27,clk_tve_i = 27 and from PLLDDS.
	rtd_outl(0xb8000028,0x00000028);	// SYS_DISP_PLL_DIV3_reg



#endif
    //==============================================================================
    //DAC control
    //==============================================================================
#if 0
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

#else
	//dac part
		rtd_outl(0xb8033000, 0x00001452);
		rtd_outl(0xb8033004, 0x00120000);
		rtd_outl(0xb8033008, 0x000010F0);
		rtd_outl(0xb803300C, 0x00000611);
		rtd_outl(0xb8033024, 0x00000007);			//<2:0> Source From ADC2X_DOUT 
		rtd_outl(0xb803301c, 0x66671110);
		rtd_outl(0xb8033014, 0x00007000);


#endif
	//0xb801836c
    rtd_outl(TVE_DAC_SEL_reg,
		     TVE_DAC_SEL_write_en1(1)|TVE_DAC_SEL_dac0_sel(0));//YPbPr & CVBS output
    //0xb8018208
    rtd_outl(TVE_DAC_MUX_reg,
                     TVE_DAC_MUX_write_en6(0)|TVE_DAC_MUX_up_ctrl_prog(0)|
                     TVE_DAC_MUX_write_en5(1)|TVE_DAC_MUX_up_ctrl_int0(2)|
                     TVE_DAC_MUX_write_en4(1)|TVE_DAC_MUX_up_ctrl_int1(2)|
                     TVE_DAC_MUX_write_en3(1)|TVE_DAC_MUX_dacmode(0)| //if RTD1175/1075
                     //TVE_DAC_MUX_write_en3(1)|TVE_DAC_MUX_dacmode(3)| //if RTD1055
                     TVE_DAC_MUX_write_en2(0)|TVE_DAC_MUX_swap23(0)|
                     TVE_DAC_MUX_write_en1(0)|TVE_DAC_MUX_swap56(0));
    //0xb801820c
    rtd_outl(TVE_CMP_DLY_reg,
                     TVE_CMP_DLY_write_en3(1)|TVE_CMP_DLY_ygdelay(0)|
                     TVE_CMP_DLY_write_en2(1)|TVE_CMP_DLY_bdelay(1)|
                     TVE_CMP_DLY_write_en1(1)|TVE_CMP_DLY_rdelay(1));
    //0xb8018210 
    rtd_outl(TVE_DAC_MISC_reg,
                     TVE_DAC_MISC_write_en3(1)|TVE_DAC_MISC_neg_out(0)|
                     TVE_DAC_MISC_write_en2(0)|TVE_DAC_MISC_out_control(0)|
                     TVE_DAC_MISC_write_en1(0)|TVE_DAC_MISC_dac_value(0));
		#if 1
		//FIR coeficients, high frequency enhancement
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
                     TVE_SYNCGEN_P_write_en2(1)|TVE_SYNCGEN_P_v_thr(524)|
                     TVE_SYNCGEN_P_write_en1(1)|TVE_SYNCGEN_P_h_thr(857));
    //0xb801800c
    rtd_outl(TVE_SYNCGEN_HDMI_reg,
                     TVE_SYNCGEN_HDMI_write_en3(1)|TVE_SYNCGEN_HDMI_i_p_sel(1)|
                     TVE_SYNCGEN_HDMI_write_en2(1)|TVE_SYNCGEN_HDMI_v_thr(524)|
                     TVE_SYNCGEN_HDMI_write_en1(1)|TVE_SYNCGEN_HDMI_h_thr(857));

    //==========================================================================
    //Active video position registers
    //==========================================================================
    //progressive Hpos
    //0xb8018054
    rtd_outl(TVE_AV_P_HPOS1_reg,
                     TVE_AV_P_HPOS1_write_en3(1)|TVE_AV_P_HPOS1_p_av_cord(1)|
                     TVE_AV_P_HPOS1_write_en2(1)|TVE_AV_P_HPOS1_p_h_st(136)|
                     TVE_AV_P_HPOS1_write_en1(1)|TVE_AV_P_HPOS1_p_h_end(856));
    //0xb8018064
    rtd_outl(TVE_P_VPOS1_reg,
                     TVE_P_VPOS1_write_en2(1)|TVE_P_VPOS1_p_v_st(42)|
                     TVE_P_VPOS1_write_en1(1)|TVE_P_VPOS1_p_v_end(521));
    //HDMI Hpos
    //0xb8018058
    rtd_outl(TVE_AV_H_HPOS1_reg,
                     TVE_AV_H_HPOS1_write_en3(1)|TVE_AV_H_HPOS1_h_av_cord(0)|
                     TVE_AV_H_HPOS1_write_en2(1)|TVE_AV_H_HPOS1_h_h_st(132)|
                     TVE_AV_H_HPOS1_write_en1(1)|TVE_AV_H_HPOS1_h_h_end(851));
    //0xb801806C
    rtd_outl(TVE_H_VPOS1_reg,
                     TVE_H_VPOS1_write_en2(1)|TVE_H_VPOS1_h_v_st(21)|
                     TVE_H_VPOS1_write_en1(1)|TVE_H_VPOS1_h_v_end(260));
    //0xb8018070
    rtd_outl(TVE_H_VPOS2_reg,
                     TVE_H_VPOS2_write_en2(1)|TVE_H_VPOS2_h_v_st(284)|
                     TVE_H_VPOS2_write_en1(1)|TVE_H_VPOS2_h_v_end(523));

    //==========================================================================
    //Slew rate and source control registers
    //==========================================================================
    //Active video slew rate
    //0xb8018048
    rtd_outl(TVE_AV_SLEW_reg,
                     TVE_AV_SLEW_write_en3(1)|TVE_AV_SLEW_p_en(1)|
                     TVE_AV_SLEW_write_en1(1)|TVE_AV_SLEW_p_slewrate(2));
    //0xb8018040
    rtd_outl(TVE_AV_CTRL_reg,
                     TVE_AV_CTRL_h_colorbar_ebl(0)|
                     TVE_AV_CTRL_h_black_ebl(0)|
                     TVE_AV_CTRL_i_colorbar_ebl(1)|
                     TVE_AV_CTRL_p_colorbar_ebl(1)|
                     TVE_AV_CTRL_i_black_ebl(0)|
                     TVE_AV_CTRL_p_black_ebl(0)|
                     TVE_AV_CTRL_write_data(1));
    //0xb8018040
    rtd_outl(TVE_AV_CTRL_reg,
                     TVE_AV_CTRL_h_colorbar_ebl(0)|
                     TVE_AV_CTRL_h_black_ebl(0)|
                     TVE_AV_CTRL_i_colorbar_ebl(0)|
                     TVE_AV_CTRL_p_colorbar_ebl(0)|
                     TVE_AV_CTRL_i_black_ebl(1)|
                     TVE_AV_CTRL_p_black_ebl(1)|
                     TVE_AV_CTRL_write_data(0));

    //==========================================================================
    //Progressive/HD registers
    //==========================================================================
    //0xb8018040
    rtd_outl(TVE_CAV_422_reg, TVE_CAV_422_fir422_sel(1));

    //==========================================================================
    //Video format setting
    //==========================================================================
    //0xb80180f4
    rtd_outl(TVE_COMP_G_CLMPLVL_reg,
                     TVE_COMP_G_CLMPLVL_write_en2(1)|TVE_COMP_G_CLMPLVL_g_up(4095)|
                     TVE_COMP_G_CLMPLVL_write_en1(1)|TVE_COMP_G_CLMPLVL_g_dn(0));
    //0xb80180f8
    rtd_outl(TVE_COMP_RB_CLMPLVL_reg,
                     TVE_COMP_RB_CLMPLVL_write_en2(1)|TVE_COMP_RB_CLMPLVL_rb_up(4095)|
                     TVE_COMP_RB_CLMPLVL_write_en1(1)|TVE_COMP_RB_CLMPLVL_rb_dn(0));
    if(*mv_flag1==0)
    {
        //Macrovision on with RGB mod-------------------------------------------
        if(RGB_mode==0)
        {
            //0xb8018010
            rtd_outl(TVE_COMP_CTRL_reg,
                             TVE_COMP_CTRL_comp_ebl(0)|
                             TVE_COMP_CTRL_sdtv_ebl(0)|
                             TVE_COMP_CTRL_vs_polar(0)|
                             TVE_COMP_CTRL_hs_polar(0)|
                             TVE_COMP_CTRL_vga_hvsync(0)|
                             TVE_COMP_CTRL_comp_sel(0)|
                             TVE_COMP_CTRL_sync_rb_ebl(0)|
                             TVE_COMP_CTRL_sync_g_ebl(0)|
                             TVE_COMP_CTRL_rgb_mod(1)|
                             TVE_COMP_CTRL_vbi_rb_ebl(0)|
                             TVE_COMP_CTRL_vbi_g_ebl(0)|
                             TVE_COMP_CTRL_hdsync(0)|
                             TVE_COMP_CTRL_syncmod_sel(0)|
                             TVE_COMP_CTRL_write_data(1));
            switch(video_format)
            {
                case 1:
                    //0xb80180e8
                    rtd_outl(TVE_COMP_BP_LVL_reg,
                                     TVE_COMP_BP_LVL_write_en2(0)|TVE_COMP_BP_LVL_y_sync_l(0)|
                                     TVE_COMP_BP_LVL_write_en1(1)|TVE_COMP_BP_LVL_bp_lvl(0xc80));
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x3f0));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x7d4)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x112));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x795d)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x860));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x763f)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x86e));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x22c6)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x1387));
    //0xb8018110
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x0ff)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x0ff));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x0ff));
                    break;
                case 2:
                    //0xb80180e8
                    rtd_outl(TVE_COMP_BP_LVL_reg,
                                     TVE_COMP_BP_LVL_write_en2(0)|TVE_COMP_BP_LVL_y_sync_l(0)|
                                     TVE_COMP_BP_LVL_write_en1(1)|TVE_COMP_BP_LVL_bp_lvl(0xc80));
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3c0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x3c0));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x800)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x0));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x7938)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x89d));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x7609)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x89d));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x2389)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x13f5));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7fec)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x7fec));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x7fec));
                    break;
                default:
                    break;
            }
        }
        //Macrovision on with YUV mode------------------------------------------
        else
        {
            //0xb8018010
            rtd_outl(TVE_COMP_CTRL_reg,
                             TVE_COMP_CTRL_comp_ebl(0)|
                             TVE_COMP_CTRL_sdtv_ebl(0)|
                             TVE_COMP_CTRL_vs_polar(0)|
                             TVE_COMP_CTRL_hs_polar(0)|
                             TVE_COMP_CTRL_vga_hvsync(0)|
                             TVE_COMP_CTRL_comp_sel(0)|
                             TVE_COMP_CTRL_sync_rb_ebl(0)|
                             TVE_COMP_CTRL_sync_g_ebl(0)|
                             TVE_COMP_CTRL_rgb_mod(1)|
                             TVE_COMP_CTRL_vbi_rb_ebl(0)|
                             TVE_COMP_CTRL_vbi_g_ebl(0)|
                             TVE_COMP_CTRL_hdsync(0)|
                             TVE_COMP_CTRL_syncmod_sel(0)|
                             TVE_COMP_CTRL_write_data(0));

            switch(video_format)
            {
                case 1: //SMPTE
                    //0xb8018100
                    rtd_outl(TVE_VBI_COEFF_reg,
                                     TVE_VBI_COEFF_write_en2(1)|TVE_VBI_COEFF_gain(0x07f4)|
                                     TVE_VBI_COEFF_write_en1(1)|TVE_VBI_COEFF_offset(0x0e0));
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x804));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x845)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x5f));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x86e));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x137c)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0xdf4));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7d70)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2014));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(1)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x200e));
                    break;
                case 2: //Beatcam
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3c0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x805));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x7f2)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x7ff0));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x7f2));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x19fd)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x12a2));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7ff0)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2019));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x2012));
                    break;
                case 3: //MII
                    //0xb8018100
                    rtd_outl(TVE_VBI_COEFF_reg,
                                     TVE_VBI_COEFF_write_en2(1)|TVE_VBI_COEFF_gain(0x07f4)|
                                     TVE_VBI_COEFF_write_en1(1)|TVE_VBI_COEFF_offset(0x0e0));
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x804));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x845)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x5f));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x7cc));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x120b)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0xcee));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x110)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2012));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(1)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x200c));
                    break;
                case 4: //SDTV
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x804));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x800)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x7f00));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x890));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x137c)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0xdf4));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7e30)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2014));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x200e));
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        //Macrovision off with RGB mode-----------------------------------------
        if(RGB_mode==0)
        {
            //0xb8018010
            rtd_outl(TVE_COMP_CTRL_reg,
                             TVE_COMP_CTRL_comp_ebl(0)|
                             TVE_COMP_CTRL_sdtv_ebl(0)|
                             TVE_COMP_CTRL_vs_polar(0)|
                             TVE_COMP_CTRL_hs_polar(0)|
                             TVE_COMP_CTRL_vga_hvsync(0)|
                             TVE_COMP_CTRL_comp_sel(0)|
                             TVE_COMP_CTRL_sync_rb_ebl(0)|
                             TVE_COMP_CTRL_sync_g_ebl(0)|
                             TVE_COMP_CTRL_rgb_mod(1)|
                             TVE_COMP_CTRL_vbi_rb_ebl(0)|
                             TVE_COMP_CTRL_vbi_g_ebl(0)|
                             TVE_COMP_CTRL_hdsync(0)|
                             TVE_COMP_CTRL_syncmod_sel(0)|
                             TVE_COMP_CTRL_write_data(1));
            switch(video_format)
            {
                case 1:
                    //0xb80180e8
                    rtd_outl(TVE_COMP_BP_LVL_reg,
                                     TVE_COMP_BP_LVL_write_en2(0)|TVE_COMP_BP_LVL_y_sync_l(0)|
                                     TVE_COMP_BP_LVL_write_en1(0)|TVE_COMP_BP_LVL_bp_lvl(0xc80));
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x3f0));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x7d4)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x112));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x795d)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x86e));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x7640)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x86e));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x22c7)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x1388));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7d4f)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x7d4f));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x7d4f));
                    break;
                case 2:
                    //0xb80180e8
                    rtd_outl(TVE_COMP_BP_LVL_reg,
                                     TVE_COMP_BP_LVL_write_en2(0)|TVE_COMP_BP_LVL_y_sync_l(0)|
                                     TVE_COMP_BP_LVL_write_en1(0)|TVE_COMP_BP_LVL_bp_lvl(0xc80));
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3c0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x3c0));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x800)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x0));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x7947)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x8a2));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x75fb)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x89e));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x2315)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x13c9));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7c0e)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x7c27));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x7c27));
                    break;
                default:
                    break;
            }
        }
        //Macrovision off with YUV mode
        else
        {
            //0xb8018010
            rtd_outl(TVE_COMP_CTRL_reg,
                             TVE_COMP_CTRL_comp_ebl(0)|
                             TVE_COMP_CTRL_sdtv_ebl(0)|
                             TVE_COMP_CTRL_vs_polar(0)|
                             TVE_COMP_CTRL_hs_polar(0)|
                             TVE_COMP_CTRL_vga_hvsync(0)|
                             TVE_COMP_CTRL_comp_sel(0)|
                             TVE_COMP_CTRL_sync_rb_ebl(0)|
                             TVE_COMP_CTRL_sync_g_ebl(0)|
                             TVE_COMP_CTRL_rgb_mod(1)|
                             TVE_COMP_CTRL_vbi_rb_ebl(0)|
                             TVE_COMP_CTRL_vbi_g_ebl(0)|
                             TVE_COMP_CTRL_hdsync(0)|
                             TVE_COMP_CTRL_syncmod_sel(0)|
                             TVE_COMP_CTRL_write_data(0));
            switch(video_format)
            {
                case 1: //SMPTE

                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x804));
/*                    //0xb8018100
                    rtd_outl(TVE_VBI_COEFF_reg,
                                     TVE_VBI_COEFF_write_en2(1)|TVE_VBI_COEFF_gain(0x07f4)|
                                     TVE_VBI_COEFF_write_en1(1)|TVE_VBI_COEFF_offset(0x0ff));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x845)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x5f));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x86e));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x0));
		    //0xb8018110
		    rtd_outl(TVE_AV_COEFF3_reg,
				     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x13F0)|
				     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0xe00));//multi-burst OK
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7d50)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2014));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(1)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x200e));//This case works!!
*/
                    //0xb8018100
                    rtd_outl(TVE_VBI_COEFF_reg,
                                     TVE_VBI_COEFF_write_en2(1)|TVE_VBI_COEFF_gain(0x0875)|
                                     TVE_VBI_COEFF_write_en1(1)|TVE_VBI_COEFF_offset(0x0));

 
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x87f)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x0));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x870));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(20));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x1300)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0xcf0));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x0)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x1300));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(1)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x1200));
                    break;
                case 2: //Beatcam
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3c0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x805));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x7f2)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x7ff0));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x7f2));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x0));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x19fd)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x12a2));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7ff0)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2019));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x2012));
                    break;
                case 3: //MII
                    //0xb8018100
                    rtd_outl(TVE_VBI_COEFF_reg,
                                     TVE_VBI_COEFF_write_en2(1)|TVE_VBI_COEFF_gain(0x07f4)|
                                     TVE_VBI_COEFF_write_en1(1)|TVE_VBI_COEFF_offset(0x0ff));
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x804));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x845)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x5f));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x7cc));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x0));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x120b)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0xcee));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x160)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2012));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(1)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x200c));
                    break;
                case 4: //SDTV
                    //0xb80180f0
                    rtd_outl(TVE_COMP_PBPR_BLNKLVL_reg,
                                     TVE_COMP_PBPR_BLNKLVL_write_en2(1)|TVE_COMP_PBPR_BLNKLVL_y_blank_lvl(0x3f0)|
                                     TVE_COMP_PBPR_BLNKLVL_write_en1(1)|TVE_COMP_PBPR_BLNKLVL_pbpr_blank_lvl(0x804));
                    //0xb8018104
                    rtd_outl(TVE_BLNK_COEFF_reg,
                                     TVE_BLNK_COEFF_write_en2(1)|TVE_BLNK_COEFF_gain(0x800)|
                                     TVE_BLNK_COEFF_write_en1(1)|TVE_BLNK_COEFF_offset(0x7f00));
                    //0xb8018108
                    rtd_outl(TVE_AV_COEFF1_reg,
                                     TVE_AV_COEFF1_write_en2(1)|TVE_AV_COEFF1_c2(0x0)|
                                     TVE_AV_COEFF1_write_en1(1)|TVE_AV_COEFF1_c1(0x890));
                    //0xb801810c
                    rtd_outl(TVE_AV_COEFF2_reg,
                                     TVE_AV_COEFF2_write_en2(1)|TVE_AV_COEFF2_c3(0x0)|
                                     TVE_AV_COEFF2_write_en1(1)|TVE_AV_COEFF2_c4(0x0));
                    //0xb8018110
                    rtd_outl(TVE_AV_COEFF3_reg,
                                     TVE_AV_COEFF3_write_en2(1)|TVE_AV_COEFF3_c5(0x137c)|
                                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0xdf4));
                    //0xb8018114
                    rtd_outl(TVE_AV_COEFF4_reg,
                                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0x7b50)|
                                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0x2014));
                    //0xb8018118
                    rtd_outl(TVE_AV_COEFF5_reg,
                                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0x200e));
                    break;
                default:
                    break;
            }
        }
    }
    //==========================================================================
    //Component registers
    //==========================================================================
    //0xb80180e0
    rtd_outl(TVE_COMP_SYNCLVL_reg,
                     TVE_COMP_SYNCLVL_write_en3(1)|TVE_COMP_SYNCLVL_slewrate(2)|
                     TVE_COMP_SYNCLVL_write_en2(1)|TVE_COMP_SYNCLVL_y_negsynclvl(0x40)|
                     TVE_COMP_SYNCLVL_write_en1(1)|TVE_COMP_SYNCLVL_y_possynclvl(0));
    //0xb80180e4
    rtd_outl(TVE_COMP_SYNC_SLEWLVL_reg,
                     TVE_COMP_SYNC_SLEWLVL_write_en2(1)|TVE_COMP_SYNC_SLEWLVL_y_sync_h(0x2b6)|
                     TVE_COMP_SYNC_SLEWLVL_write_en1(1)|TVE_COMP_SYNC_SLEWLVL_y_sync_m(0xd0));
    //0xb80180ec
    rtd_outl(TVE_COMP_PBPR_SYNCLVL_reg,
                     TVE_COMP_PBPR_SYNCLVL_write_en2(1)|TVE_COMP_PBPR_SYNCLVL_pbpr_negsynclvl(0x3f0)|
                     TVE_COMP_PBPR_SYNCLVL_write_en1(1)|TVE_COMP_PBPR_SYNCLVL_pbpr_possynclvl(0x40));

    //==============================================================================
    //General control register
    //==============================================================================
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
    // 0xb8018010
    rtd_outl(TVE_COMP_CTRL_reg,
                     TVE_COMP_CTRL_comp_ebl(1)|
                     TVE_COMP_CTRL_sdtv_ebl(1)|
                     TVE_COMP_CTRL_vs_polar(0)|
                     TVE_COMP_CTRL_hs_polar(0)|
                     TVE_COMP_CTRL_vga_hvsync(0)|
                     TVE_COMP_CTRL_comp_sel(1)|
                     TVE_COMP_CTRL_sync_rb_ebl(0)|
                     TVE_COMP_CTRL_sync_g_ebl(1)|
                     TVE_COMP_CTRL_rgb_mod(0)|
                     TVE_COMP_CTRL_vbi_rb_ebl(0)|
                     TVE_COMP_CTRL_vbi_g_ebl(1)|
                     TVE_COMP_CTRL_hdsync(0)|
                     TVE_COMP_CTRL_syncmod_sel(0)|
                     TVE_COMP_CTRL_write_data(1));
    // 0xb8018130
    rtd_outl(TVE_MV_CTRL_reg,
                     TVE_MV_CTRL_mv_rb_ebl(0)|
                     TVE_MV_CTRL_mv_g_ebl(1)|
                     TVE_MV_CTRL_mv_ebl(0)|
                     TVE_MV_CTRL_write_data(1));
    return;
}
