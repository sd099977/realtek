//############################################################################################################
//
// File Name: TV_NTSC_M.c
// Description: TV Encoder NTSC-M for CVBS initial setting
// Parameter:
// Programmer: Ardor Yen
// Date: 2010/02/06
//
//############################################################################################################
//extern unsigned int *RGB_flag;
#include "TVE_reg.h"
#include "qc_verify.h"
#include "TVE.h"
#include "crt_sys_reg.h"
void TVE_TV_NTSC_M(void)
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
#endif
    //0xb8018208
    rtd_outl(TVE_DAC_MUX_reg,
                     TVE_DAC_MUX_write_en6(0)|TVE_DAC_MUX_up_ctrl_prog(0)|
                     TVE_DAC_MUX_write_en5(1)|TVE_DAC_MUX_up_ctrl_int0(3)|
                     TVE_DAC_MUX_write_en4(1)|TVE_DAC_MUX_up_ctrl_int1(3)|
                     TVE_DAC_MUX_write_en3(1)|TVE_DAC_MUX_dacmode(0)| 
                     TVE_DAC_MUX_write_en2(0)|TVE_DAC_MUX_swap23(0)|
                     TVE_DAC_MUX_write_en1(0)|TVE_DAC_MUX_swap56(0));
    //0xb801820c
    rtd_outl(TVE_CMP_DLY_reg,
                     TVE_CMP_DLY_write_en3(1)|TVE_CMP_DLY_ygdelay(0)|
                     TVE_CMP_DLY_write_en2(1)|TVE_CMP_DLY_bdelay(0)|
                     TVE_CMP_DLY_write_en1(1)|TVE_CMP_DLY_rdelay(0));
    //0xb8018210 
    rtd_outl(TVE_DAC_MISC_reg,
                     TVE_DAC_MISC_write_en3(1)|TVE_DAC_MISC_neg_out(0)|
                     TVE_DAC_MISC_write_en2(0)|TVE_DAC_MISC_out_control(0)|
                     TVE_DAC_MISC_write_en1(0)|TVE_DAC_MISC_dac_value(0));
#if 0 //not use
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
#endif
    //==============================================================================
    //General control register
    //==============================================================================
    //0xb8018000
    rtd_outl(TVE_SYNCGEN_RST_reg,
                     TVE_SYNCGEN_RST_write_en5(1)|TVE_SYNCGEN_RST_hi_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en4(1)|TVE_SYNCGEN_RST_pi_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en3(1)|TVE_SYNCGEN_RST_i_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en2(1)|TVE_SYNCGEN_RST_p_sync_go(0)|
                     TVE_SYNCGEN_RST_write_en1(1)|TVE_SYNCGEN_RST_h_sync_go(0));

    //==========================================================================
    //Sarnoff IP
    //==========================================================================
    //Reset Sarnoff IP----------------------------------------------------------
    //0xb8018038
    rtd_outl(TVE_SRSTN_reg, TVE_SRSTN_srstn(1));
    //Y gain--------------------------------------------------------------------
    //0xb8018a00
    rtd_outl(TVE_IP_Y_GAIN_reg, TVE_IP_Y_GAIN_y_gain(0x200));
    //0xb8018880
    rtd_outl(TVE_IP_PHS_0_reg, TVE_IP_PHS_phi(0x1f));
    //0xb8018884
    rtd_outl(TVE_IP_PHS_1_reg, TVE_IP_PHS_phi(0x7c));
    //0xb8018888
    rtd_outl(TVE_IP_PHS_2_reg, TVE_IP_PHS_phi(0xf0));
    //0xb801888c
    rtd_outl(TVE_IP_PHS_3_reg, TVE_IP_PHS_phi(0x21));
    //SCH phase-----------------------------------------------------------------
    //0xb8018890
    rtd_outl(TVE_IP_SCTOH_0_reg, TVE_IP_SCTOH_sctoh(0x00));
    //0xb8018894
    rtd_outl(TVE_IP_SCTOH_1_reg, TVE_IP_SCTOH_sctoh(0x02));
    //0xb8018898
    rtd_outl(TVE_IP_SCTOH_2_reg, TVE_IP_SCTOH_sctoh(0x02));
    //0xb801889c
    rtd_outl(TVE_IP_SCTOH_3_reg, TVE_IP_SCTOH_sctoh(0x44));
    //0xb80188a0
    rtd_outl(TVE_IP_F_CTRL_reg,
                    TVE_IP_F_CTRL_u_invert(0)|
                    TVE_IP_F_CTRL_v_invert(0)|
                    TVE_IP_F_CTRL_t_offset_phase(1)|
                    TVE_IP_F_CTRL_t_reset_fsc(0));
    //black and blank level-----------------------------------------------------
    //0xb80188a8 
    rtd_outl(TVE_IP_BLCK_LVL_reg, TVE_IP_BLCK_LVL_black_lvl(0x8d));
    //0xb80188ac
    rtd_outl(TVE_IP_BLNK_LVL_reg, TVE_IP_BLNK_LVL_blank_lvl(0x78));
    //0xb80188b0
    rtd_outl(TVE_IP_CLAMP_LVL_reg, TVE_IP_CLAMP_LVL_clamp_lvl(0x10));
    //sync level----------------------------------------------------------------
    //0xb80188b4
    rtd_outl(TVE_IP_SYNC_LVL_reg, TVE_IP_SYNC_LVL_sync_lvl(0x7));
    //Y filter:select full BW---------------------------------------------------
    //0xb80188b8
    rtd_outl(TVE_IP_Y_CTRL_reg,
                    TVE_IP_Y_CTRL_y_interp(0)|
                    TVE_IP_Y_CTRL_y_colorbar_en(0)|
                    TVE_IP_Y_CTRL_t_ydel_adj(7)|
                    TVE_IP_Y_CTRL_t_sel_ylpf(0)|
                    TVE_IP_Y_CTRL_t_ygain_val(0));
    //0xb8018984
    rtd_outl(TVE_IP_TEST_PARAM_reg,
                    TVE_IP_TEST_PARAM_t_byp_yups(0)|
                    TVE_IP_TEST_PARAM_t_sel_ylp(1)|
                    TVE_IP_TEST_PARAM_t_ygain_off(0)|
                    TVE_IP_TEST_PARAM_y_tsin_cos(0)|
                    TVE_IP_TEST_PARAM_y_tsel_dac_tst(0)|
                    TVE_IP_TEST_PARAM_y_tdig_out(0));
    //Chroma LPF bypass---------------------------------------------------------
    //0xb801898c
    rtd_outl(TVE_IP_TEST_T_BYP_CUPS_reg,
                    TVE_IP_TEST_T_BYP_CUPS_t_byp_cups(0)|
                    TVE_IP_TEST_T_BYP_CUPS_t_byp_clpf(1)|
                    TVE_IP_TEST_T_BYP_CUPS_t_c_gain_off(0));
    //0xb80188bc
    rtd_outl(TVE_IP_O_CTRL_reg,
                    TVE_IP_O_CTRL_y_tsel_yuv(0)|
                    TVE_IP_O_CTRL_t_pd_cvdac(0)|
                    TVE_IP_O_CTRL_t_pd_ydac(0)|
                    TVE_IP_O_CTRL_t_pd_cdac(0));
    //burst amplitude-----------------------------------------------------------
    //0xb80188c8
    rtd_outl(TVE_IP_NBA_reg, TVE_IP_NBA_nba(0xc8));
    //0xb80188cc
    rtd_outl(TVE_IP_PBA_reg, TVE_IP_PBA_pba(0));
    //0xb80188d0
    rtd_outl(TVE_IP_C_CTRL_reg,
                    TVE_IP_C_CTRL_t_pal_clpf(0)|
                    TVE_IP_C_CTRL_t_sel_c_gain(0));
    //0xb80188e0
    rtd_outl(TVE_IP_S_CTRL_reg,
                    TVE_IP_S_CTRL_t_hsync_phs(0)|
                    TVE_IP_S_CTRL_t_vsync_phs(0)|
                    TVE_IP_S_CTRL_y_tsyncmode(1)|
                    TVE_IP_S_CTRL_y_tencd_mode(0));
    //0xb80188e4
    rtd_outl(TVE_IP_VSO0_reg,
                    TVE_IP_VSO0_clk_phs(0)|
                    TVE_IP_VSO0_t_fsync_enbl(1)|
                    TVE_IP_VSO0_t_fsync_phs(1)|
                    TVE_IP_VSO0_vso(1));
    //0xb80188e8
    rtd_outl(TVE_IP_VSO1_reg, TVE_IP_VSO1_vso(0x06));
    //0xb80188ec
    rtd_outl(TVE_IP_HSO0_reg, TVE_IP_HSO0_hso(0x06));
    //0xb80188f0
    rtd_outl(TVE_IP_HSO1_reg, TVE_IP_HSO1_hso(0xb3));
    //0xb80188f4
    rtd_outl(TVE_IP_HLC0_reg, TVE_IP_HLC0_hlc(0x03));
    //0xb80188f8
    rtd_outl(TVE_IP_HLC1_reg, TVE_IP_HLC1_hlc(0x59));
    //raising and falling time--------------------------------------------------
    //0xb80189c0
    rtd_outl(TVE_IP_SYNC_LVL2_reg, TVE_IP_SYNC_LVL2_sync_lvl_h(0x64));
    //0xb80189c4
    rtd_outl(TVE_IP_SYNC_LVL3_reg, TVE_IP_SYNC_LVL3_sync_lvl_m(0x2d));
    //0xb80189c8
    rtd_outl(TVE_IP_SYNC_LVL4_reg, TVE_IP_SYNC_LVL4_sync_lvl_l(0x07));
    //C unit Low pass filter gain-----------------------------------------------
    //0xb80189cc
    rtd_outl(TVE_IP_SYNCLPF_GAIN_reg, TVE_IP_SYNCLPF_GAIN_clpf_gain(0x14));

    //==========================================================================
    //Macrovision
    //==========================================================================
    //Macrovision Copy Protection for 525i Type 1
    //0xb8018920
    rtd_outl(TVE_IP_MVFCR_reg, TVE_IP_MVFCR_mvfcr(0x0)); //N0
    //0xb8018924
    rtd_outl(TVE_IP_MVCSL1_reg, TVE_IP_MVCSL1_mvcsl1(0x3a)); //N1*2
    //0xb8018928
    rtd_outl(TVE_IP_MVCLS1_reg, TVE_IP_MVCLS1_mvcls1(0x11)); //N2
    //0xb801892c
    rtd_outl(TVE_IP_MVCSL2_reg, TVE_IP_MVCSL2_mvcsl2(0x4b)); //N3*2+1
    //0xb8018930
    rtd_outl(TVE_IP_MVCLS2_reg, TVE_IP_MVCLS2_mvcls2(0x11)); //N4
    //0xb8018934
    rtd_outl(TVE_IP_MVCSSP_reg, TVE_IP_MVCSSP_mvcssp(0x1)| //N5
                                        TVE_IP_MVCSSP_mvcsnum(0x7)| //N6
                                        TVE_IP_MVCSSP_mvcsln(0x0)); //N7
    //0xb8018938
    rtd_outl(TVE_IP_MVPSD_reg, TVE_IP_MVPSD_mvpsd(0x1b)); //N8
    //0xb801893c
    rtd_outl(TVE_IP_MVPSL_reg, TVE_IP_MVPSL_mvpsl(0x1b)); //N9
    //0xb8018940
    rtd_outl(TVE_IP_MVPSS_reg, TVE_IP_MVPSS_mvpss(0x24)); //N10
    //0xb8018944
    rtd_outl(TVE_IP_MVPSLS0_reg, TVE_IP_MVPSLS0_mvpsls(0x7)); //N11(MSB)
    //0xb8018948
    rtd_outl(TVE_IP_MVPSLS1_reg, TVE_IP_MVPSLS1_mvpsls(0xf8)); //N11(LSB)
    //0xb801894c
    rtd_outl(TVE_IP_MVPSFS0_reg, TVE_IP_MVPSFS0_mvpsfs(0x0)); //N12(MSB)
    //0xb8018950
    rtd_outl(TVE_IP_MVPSFS1_reg, TVE_IP_MVPSFS1_mvpsfs(0x0)); //N12(LSB)
    //0xb8018954
    rtd_outl(TVE_IP_MVPSAGCA_reg, TVE_IP_MVPSAGCA_mvpsagca(0xf)); //N13
    //0xb8018958
    rtd_outl(TVE_IP_MVPSAGCB_reg, TVE_IP_MVPSAGCB_mvpsagcb(0xf)); //N14
    //0xb801895c
    rtd_outl(TVE_IP_MVEOFBPC_reg, TVE_IP_MVEOFBPC_mveofbpc(0x60)); //N15
    //0xb8018960
    rtd_outl(TVE_IP_MVPBZ1_reg, TVE_IP_MVPBZ1_mvpbz1(0xa)| //N17
                                        TVE_IP_MVPBZ1_mvpbz2(0x0)); //N18
    //0xb8018964
    rtd_outl(TVE_IP_MVPBZ3_reg, TVE_IP_MVPBZ3_mvpbz3(0x5)| //N19
                                        TVE_IP_MVPBZ3_mvpadvbsen(0x0)| //N16
                                        TVE_IP_MVPBZ3_mvpzninvrt(0x4)); //N20
    //0xb8018968
    rtd_outl(TVE_IP_MVPCSLIMD0_reg, TVE_IP_MVPCSLIMD0_mvpcslimd_lsb(0xff)); //N21(LSB)
    //0xb801896c
    rtd_outl(TVE_IP_MVPCSLIMD1_reg, TVE_IP_MVPCSLIMD1_mvpcslimd_msb(0x03)); //N21(MSB)
    if(*RGB_flag1==0) //RGB mode
        //0xb8018130
        rtd_outl(TVE_MV_CTRL_reg,
                         TVE_MV_CTRL_mv_rb_ebl(1)|
                         TVE_MV_CTRL_mv_g_ebl(1)|
                         TVE_MV_CTRL_mv_ebl(0)|
                         TVE_MV_CTRL_write_data(0)); //N22
    else //YUV mode
        //0xb8018130
        rtd_outl(TVE_MV_CTRL_reg,
                         TVE_MV_CTRL_mv_rb_ebl(1)|
                         TVE_MV_CTRL_mv_g_ebl(0)|
                         TVE_MV_CTRL_mv_ebl(0)|
                         TVE_MV_CTRL_write_data(0)); //N22
    //0xb8018990
    rtd_outl(TVE_IP_MV_CTRL_reg, TVE_IP_MV_CTRL_mvtms(0x10));

    //==========================================================================
    //H-Timing Setting
    //==========================================================================
    //sync timing---------------------------------------------------------------
    //0xb80189d0
    rtd_outl(TVE_IP_SYNC_STRT_reg, TVE_IP_SYNC_STRT_sync_strt(0x0c));
    //0xb80189d4
    rtd_outl(TVE_IP_SYNC_END_reg, TVE_IP_SYNC_END_sync_end(0x4b));
    //0xb80189d8
    rtd_outl(TVE_IP_SYNC_SREND_reg, TVE_IP_SYNC_SREND_sync_srend(0x7a));
    //0xb80189dc
    rtd_outl(TVE_IP_SYNC_EQEND_reg, TVE_IP_SYNC_EQEND_sync_eqend(0x2b));
    //active video area---------------------------------------------------------
    //0xb80189e0
    rtd_outl(TVE_IP_ACTV_STRT_reg, TVE_IP_ACTV_STRT_actv_strt(0x85));
    //0xb80189e4
    rtd_outl(TVE_IP_ACTV_END_reg, TVE_IP_ACTV_END_actv_end(0xaa));
    //burst position------------------------------------------------------------
    //0xb80189e8
    rtd_outl(TVE_IP_WBRST_STRT_reg, TVE_IP_WBRST_STRT_wbrst_strt(0x5a));
    //0xb80189ec
    rtd_outl(TVE_IP_NBRST_STRT_reg, TVE_IP_NBRST_STRT_nbrst_strt(0x62));
    //0xb80189f0
    rtd_outl(TVE_IP_NBRST_END_reg, TVE_IP_NBRST_END_nbrst_end(0x84));

    //==========================================================================
    //Sync generator register
    //==========================================================================
    //0xb8018004
    rtd_outl(TVE_SYNCGEN_I_reg,
                     TVE_SYNCGEN_I_write_en2(1)|TVE_SYNCGEN_I_v_thr(524)|
                     TVE_SYNCGEN_I_write_en1(1)|TVE_SYNCGEN_I_h_thr(857));
    //0xb80180b0
    rtd_outl(TVE_IP_VSYNCPOS_reg,
                     TVE_IP_VSYNCPOS_write_en2(1)|TVE_IP_VSYNCPOS_ip_vsync_pos1(524)|
                     TVE_IP_VSYNCPOS_write_en1(1)|TVE_IP_VSYNCPOS_ip_vsync_pos2(261));
    //0xb80180b4
    rtd_outl(TVE_IP_HSYNCPOS_reg, TVE_IP_HSYNCPOS_hthr(857));

    //==========================================================================
    //Active video position registers
    //==========================================================================
    //interlaced Hpos
    //0xb8018050
    rtd_outl(TVE_AV_I_HPOS_reg,
                     TVE_AV_I_HPOS_write_en2(1)|TVE_AV_I_HPOS_i_h_st(132)|
                     TVE_AV_I_HPOS_write_en1(1)|TVE_AV_I_HPOS_i_h_end(851));

    //0xb801804c
    rtd_outl(TVE_SLEW_I_HPOS_reg,
                     TVE_SLEW_I_HPOS_write_en2(1)|TVE_SLEW_I_HPOS_i_h_st(132)|
                     TVE_SLEW_I_HPOS_write_en1(1)|TVE_SLEW_I_HPOS_i_h_end(851));
		
    //0xb801805c
    rtd_outl(TVE_ITOP_VPOS_reg,
                     TVE_ITOP_VPOS_write_en2(1)|TVE_ITOP_VPOS_itop_v_st(21)|
                     TVE_ITOP_VPOS_write_en1(1)|TVE_ITOP_VPOS_itop_v_end(260));
    //0xb8018060
    rtd_outl(TVE_IBOT_VPOS_reg,
                     TVE_IBOT_VPOS_write_en2(1)|TVE_IBOT_VPOS_ibot_v_st(284)|
                     TVE_IBOT_VPOS_write_en1(1)|TVE_IBOT_VPOS_ibot_v_end(523));

    //==========================================================================
    //Slew rate and source control registers
    //==========================================================================
    //Active video slew rate
    //0xb8018048
    rtd_outl(TVE_AV_SLEW_reg,
                     TVE_AV_SLEW_write_en4(1)|TVE_AV_SLEW_i_en(1)|
                     TVE_AV_SLEW_write_en2(1)|TVE_AV_SLEW_i_slewrate(2));
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
    //0xb8018074
    rtd_outl(TVE_I_COLORBAR_HPOS_reg,
                     TVE_I_COLORBAR_HPOS_write_en2(1)|TVE_I_COLORBAR_HPOS_i_h_width(89)|
                     TVE_I_COLORBAR_HPOS_write_en1(1)|TVE_I_COLORBAR_HPOS_i_h_st_pos(130));
    return;
}
