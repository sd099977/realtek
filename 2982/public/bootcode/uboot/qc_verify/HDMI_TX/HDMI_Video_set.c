//#######################################################################################################
//
//  File Name:      HDMI_Video_set.C
//  Description:    HDMI Video initial setting
//
//#######################################################################################################
//extern UINT8 xvYCC;//, Timing_Gen, En_3D, Format_3D;
#include "qc_verify.h"
#include "hdmi.h"
#include "hdmi_reg.h"
#include "VO_reg.h"
#include "TV.h"
#include "TVE_reg.h"
//#include <../hdmi_tx/crt_sys_reg.h>
#include "crt_sys_reg.h"
#include <qc_verify_common.h>
#include <rtd_types_qc.h>
#include "hdmi_tx_table.h"
#include "mhl_tx_table.h"

//#include "TVE.h"

void TVE_TV_1080p60(void)
{
#if 0
    //0xb8000020
    rtd_outl(SYS_DISP_PLL_DIV_reg,
                     SYS_DISP_PLL_DIV_write_en2(1)|SYS_DISP_PLL_DIV_dac2_div(0)|    //216MHz for CVBS
                     SYS_DISP_PLL_DIV_write_en1(1)|SYS_DISP_PLL_DIV_dac1_div(4));   //148.5MHz for component DACs.
    //0xb8000024
    rtd_outl(SYS_DISP_PLL_DIV2_reg,
                     SYS_DISP_PLL_DIV2_write_en3(1)|SYS_DISP_PLL_DIV2_tve_div(4));  //148.5MHz to TVE
#else

    rtd_outl(0xb80001cc,0x00053622);    // SYS_TVPLL_CTRL1_reg
    rtd_outl(0xb80001d0,0x00000922);    // SYS_TVPLL_CTRL2_reg
    rtd_outl(0xb80001d4,0x00560000);    // SYS_TVPLL_CTRL3_reg
    rtd_outl(0xb80001c4,0x00409012);    // SYS_TMDS_SCR2_reg
    rtd_outl(0xb80001c8,0x04810b77);    // SYS_TMDS_SCR3_reg


    // Setting PLLDDS output frequency = 432MHz
    rtd_outl(0xb8000170,0x0727d244);    // SYS_PLL_DISP_SD1_reg
    rtd_outl(0xb8000174,0x00554000);    // SYS_PLL_DISP_SD2_reg


    // Setting mux to select clocks frequency for dac1_clk = 148.5,clk_tve_p = 148.5 and from TVPLL. The dac2_clk = 27,clk_tve_i = 27 and from PLLDDS.
    rtd_outl(0xb8000028,0x00000028);    // SYS_DISP_PLL_DIV3_reg


#endif
    //==========================================================================
    //DAC control
    //==========================================================================
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
    //0xb8018208
    rtd_outl(TVE_DAC_MUX_reg,
                     TVE_DAC_MUX_write_en6(0)|TVE_DAC_MUX_up_ctrl_prog(0)|
                     TVE_DAC_MUX_write_en5(1)|TVE_DAC_MUX_up_ctrl_int0(0)|
                     TVE_DAC_MUX_write_en4(1)|TVE_DAC_MUX_up_ctrl_int1(0)|
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
                     TVE_DAC_MISC_write_en3(1)|TVE_DAC_MISC_neg_out(0)|
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
#else
    //dac part
        rtd_outl(0xb8033000, 0x00001452);
        rtd_outl(0xb8033004, 0x00120000);
        rtd_outl(0xb8033008, 0x000110F0);
        rtd_outl(0xb803300C, 0x00000611);
        rtd_outl(0xb8033024, 0x00000007);           //<2:0> Source From ADC2X_DOUT
        rtd_outl(0xb803301c, 0x66671110);


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
                     TVE_SYNCGEN_P_write_en3(1)|TVE_SYNCGEN_P_i_p_sel(0)|
                     TVE_SYNCGEN_P_write_en2(1)|TVE_SYNCGEN_P_v_thr(1124)|
                     TVE_SYNCGEN_P_write_en1(1)|TVE_SYNCGEN_P_h_thr(2199));
    //0xb801800c
    rtd_outl(TVE_SYNCGEN_HDMI_reg,
                     TVE_SYNCGEN_HDMI_write_en3(1)|TVE_SYNCGEN_HDMI_i_p_sel(0)|
                     TVE_SYNCGEN_HDMI_write_en2(1)|TVE_SYNCGEN_HDMI_v_thr(1124)|
                     TVE_SYNCGEN_HDMI_write_en1(1)|TVE_SYNCGEN_HDMI_h_thr(2199));

    //==========================================================================
    //Active video position registers
    //==========================================================================
    //progressive Hpos
    //0xb8018054
    rtd_outl(TVE_AV_P_HPOS1_reg,
                     TVE_AV_P_HPOS1_write_en3(1)|TVE_AV_P_HPOS1_p_av_cord(1)|
                     TVE_AV_P_HPOS1_write_en2(1)|TVE_AV_P_HPOS1_p_h_st(273)|
                     TVE_AV_P_HPOS1_write_en1(1)|TVE_AV_P_HPOS1_p_h_end(2193));
    //0xb8018064
    rtd_outl(TVE_P_VPOS1_reg,
                     TVE_P_VPOS1_write_en2(1)|TVE_P_VPOS1_p_v_st(41)|
                     TVE_P_VPOS1_write_en1(1)|TVE_P_VPOS1_p_v_end(1120));
    //HDMI Hpos
    //0xb8018058
    rtd_outl(TVE_AV_H_HPOS1_reg,
                     TVE_AV_H_HPOS1_write_en3(1)|TVE_AV_H_HPOS1_h_av_cord(1)|
                     TVE_AV_H_HPOS1_write_en2(1)|TVE_AV_H_HPOS1_h_h_st(273)|
                     TVE_AV_H_HPOS1_write_en1(1)|TVE_AV_H_HPOS1_h_h_end(2193));
    //0xb801806c
    rtd_outl(TVE_H_VPOS1_reg,
                     TVE_H_VPOS1_write_en2(1)|TVE_H_VPOS1_h_v_st(41)|
                     TVE_H_VPOS1_write_en1(1)|TVE_H_VPOS1_h_v_end(1120));

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
                     TVE_P_COLORBAR_HPOS_write_en2(1)|TVE_P_COLORBAR_HPOS_p_h_width(239)|
                     TVE_P_COLORBAR_HPOS_write_en1(1)|TVE_P_COLORBAR_HPOS_p_h_st_pos(271));
    //0xb801807c
    rtd_outl(TVE_H_COLORBAR_HPOS_reg,
                     TVE_H_COLORBAR_HPOS_write_en2(1)|TVE_H_COLORBAR_HPOS_p_h_width(239)|
                     TVE_H_COLORBAR_HPOS_write_en1(1)|TVE_H_COLORBAR_HPOS_p_h_st_pos(271));

    //==========================================================================
    //Progressive/HD registers
    //==========================================================================
    //0xb8018044
    rtd_outl(TVE_CAV_422_reg, TVE_CAV_422_fir422_sel(1));
    //0xb8018080
    rtd_outl(TVE_COMP_VSYNC_HPOS_reg,
                     TVE_COMP_VSYNC_HPOS_write_en3(1)|TVE_COMP_VSYNC_HPOS_negsyncst(44)|
                     TVE_COMP_VSYNC_HPOS_write_en2(1)|TVE_COMP_VSYNC_HPOS_possyncst(86)|
                     TVE_COMP_VSYNC_HPOS_write_en1(1)|TVE_COMP_VSYNC_HPOS_syncend(130));
    //0xb8018088
    rtd_outl(TVE_COMP_SER_HPOS_reg,
                     TVE_COMP_SER_HPOS_write_en2(1)|TVE_COMP_SER_HPOS_ser_hstart(217)|
                     TVE_COMP_SER_HPOS_write_en1(1)|TVE_COMP_SER_HPOS_ser_hend(2197));
    //0xb801808c
    rtd_outl(TVE_COMP_SER_VPOS_reg,
                     TVE_COMP_SER_VPOS_write_en2(1)|TVE_COMP_SER_VPOS_ser_vstart(0)|
                     TVE_COMP_SER_VPOS_write_en1(1)|TVE_COMP_SER_VPOS_ser_vend(4));

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
                     TVE_AV_COEFF3_write_en1(1)|TVE_AV_COEFF3_c6(0x1440));
    //0xb8018114
    rtd_outl(TVE_AV_COEFF4_reg,
                     TVE_AV_COEFF4_write_en2(1)|TVE_AV_COEFF4_k1(0xd50)|
                     TVE_AV_COEFF4_write_en1(1)|TVE_AV_COEFF4_k2(0xbd0));
    //0xb8018118
    rtd_outl(TVE_AV_COEFF5_reg,
                     TVE_AV_COEFF5_write_en1(1)|TVE_AV_COEFF5_vbi_gain_ebl(0)|
                     TVE_AV_COEFF5_write_en2(1)|TVE_AV_COEFF5_k3(0xbc8));

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

void SET_PLL_HDMI(UINT32 format_idx, UINT8 deep_color, UINT8 deep_depth)
{
    pll_div_param_st *tmp;
    pll_analog_param_st *tmp1;
    UINT32 reg_val, mask;

    switch (format_idx) {
        case HDMI_TX_720_1440_480I_60HZ:
        case HDMI_TX_720_480P_60HZ:
        case HDMI_TX_720_1440_576I_50HZ:
        case HDMI_TX_720_576P_50HZ:
            rtd_outl(0xb8000024, 0x00006000); //sel_plihdmi_clk, 0xb8000024[13] = 1
            rtd_maskl(0xb8000028, 0xfffff3ff, 0x00000800); //reg_tve_hdmi_div_sel, 0xb8000028[11:10] = 2
            break;
        default:
            rtd_outl(0xb8000024, 0x00004000); //sel_plihdmi_clk, 0xb8000024[13] = 0
            rtd_maskl(0xb8000028, 0xfffff3ff, 0x00000000); //reg_tve_hdmi_div_sel, 0xb8000028[11:10] = 0
            break;
    }

    if (deep_color)
    {
        switch (deep_depth) {
            case 5:
                tmp = &pll_div_deep_color_10bit_table[0] + format_idx;
                tmp1 = &pll_analog_deep_color_10bit_table[0] + format_idx;
                break;
            case 6:
                tmp = &pll_div_deep_color_12bit_table[0] + format_idx;
                tmp1 = &pll_analog_deep_color_12bit_table[0] + format_idx;
                break;
            default:
                tmp = &pll_div_deep_color_8bit_table[0] + format_idx;
                tmp1 = &pll_analog_deep_color_8bit_table[0] + format_idx;
                break;
        }
    }
    else
    {
        tmp = &pll_div_deep_color_8bit_table[0] + format_idx;
        tmp1 = &pll_analog_deep_color_8bit_table[0] + format_idx;
    }

    mask = 0x7 + (0x1 << 3) + (0x7 << 4) + (1 << 7) + (0x1 << 8) + (0x3f << 14) + (0x1 << 20);
    reg_val = (tmp->disp.tv_ldiv << 14) + (tmp->disp.tv_pre_div << 20) +
              (tmp->disp.pix_div3 << 8) + (tmp->disp.pix_div5 << 7) +
              (tmp->disp.pix_div16 << 4) + (tmp->disp.tmds_div5 << 3) +
              (tmp->disp.tmds_div16 << 0);
    rtd_maskl(0xb80001cc, ~mask, reg_val);

    mask = (0x1 << 28) + (0x3 << 26) + (0x3 << 24) + (0x7 << 3) + (0x7 << 0);
    reg_val = (tmp1->disp.tv_kvco << 28) + (tmp1->disp.tv_cp << 26) +
              (tmp1->disp.tv_cs << 24) + (tmp1->hdmi.tx_pll_icp << 3) +
              (tmp1->hdmi.tx_pll_rs << 0);
    rtd_maskl(0xb80001c0, ~mask, reg_val);

    mask = (0x7 << 8) + (0x7 << 5);
    reg_val = (tmp1->disp.tv_icp << 8) + (tmp1->disp.tv_rs << 5);
    rtd_maskl(0xb80001d0, ~mask, reg_val);

    mask = (0x7 << 10);
    reg_val = (tmp1->disp.tv_pstep << 10);
    rtd_maskl(0xb80001cc, ~mask, reg_val);

    mask = (0x3 << 1) + (0x1 << 23) + (0x3 << 26) + (0x3 << 24);
    reg_val = (tmp1->others.pll_vco_scal << 1) + (tmp1->hdmi.tx_pll_kvco << 23) +
              (tmp1->hdmi.tx_pll_cp << 26) + (tmp1->hdmi.tx_pll_cs << 24);
    rtd_maskl(0xb80001c4, ~mask, reg_val);

    mask = (0x3 << 12);
    reg_val = 0x0 << 12;
    rtd_maskl(0xb8000028, ~mask, reg_val); // hdmi_tmds_div = 0 (/1)
}

void SET_PLL_MHL(UINT32 format_idx, bool pp_mode_en)
{
    pll_div_param_st *tmp;
    pll_analog_param_st *tmp1;
    UINT32 reg_val, mask;

    switch (format_idx) {
        case HDMI_TX_720_1440_480I_60HZ:
        case HDMI_TX_720_480P_60HZ:
        case HDMI_TX_720_1440_576I_50HZ:
        case HDMI_TX_720_576P_50HZ:
            rtd_outl(0xb8000024, 0x00006000); //sel_plihdmi_clk, 0xb8000024[13] = 1
            rtd_maskl(0xb8000028, 0xfffff3ff, 0x00000800); //reg_tve_hdmi_div_sel, 0xb8000028[11:10] = 2
            break;
        default:
            rtd_outl(0xb8000024, 0x00004000); //sel_plihdmi_clk, 0xb8000024[13] = 0
            rtd_maskl(0xb8000028, 0xfffff3ff, 0x00000000); //reg_tve_hdmi_div_sel, 0xb8000028[11:10] = 0
            break;
    }

    if (pp_mode_en)
    {
        printf("- pp mode\n");
        tmp = &pll_div_pp_mode_table[0] + format_idx;
        mask = (0x3 << 12);
        reg_val = 0x1 << 12;
        rtd_maskl(0xb8000028, ~mask, reg_val); // hdmi_tmds_div = 1 (/2)

        mask = (0x1 << 15) + (0x3 << 13);
        reg_val = (0x1 << 15) + (0x2 << 13);
        rtd_maskl(0xb80001c8, ~mask, reg_val); // mhl_div = 1 (/4, pp mode use)
    }
    else
    {
        printf("- 24bit mode\n");
        tmp = &pll_div_8bit_table[0] + format_idx;
        mask = (0x3 << 12);
        reg_val = 0x2 << 12;
        rtd_maskl(0xb8000028, ~mask, reg_val); // hdmi_tmds_div = 2 (/3)

        mask = (0x1 << 15) + (0x3 << 13);
        reg_val = (0x0 << 15) + (0x0 << 13);
        rtd_maskl(0xb80001c8, ~mask, reg_val); // mhl_div = 0 (/3, 24 bit use)
    }

    tmp1 = &pll_analog_mhl_table[0] + format_idx;

    mask = 0x7 + (0x1 << 3) + (0x7 << 4) + (0x1 << 7) + (0x1 << 8) + (0x3f << 14) + (0x1 << 20);
    reg_val = (tmp->disp.tv_ldiv << 14) + (tmp->disp.tv_pre_div << 20) +
              (tmp->disp.pix_div3 << 8) + (tmp->disp.pix_div5 << 7) +
              (tmp->disp.pix_div16 << 4) + (tmp->disp.tmds_div5 << 3) +
              (tmp->disp.tmds_div16 << 0);
    rtd_maskl(0xb80001cc, ~mask, reg_val);

    mask = (0x1 << 28) + (0x3 << 26) + (0x3 << 24) + (0x7 << 3) + (0x7 << 0);
    reg_val = (tmp1->disp.tv_kvco << 28) + (tmp1->disp.tv_cp << 26) +
              (tmp1->disp.tv_cs << 24) + (tmp1->hdmi.tx_pll_icp << 3) +
              (tmp1->hdmi.tx_pll_rs << 0);
    rtd_maskl(0xb80001c0, ~mask, reg_val);

    mask = (0x7 << 8) + (0x7 << 5);
    reg_val = (tmp1->disp.tv_icp << 8) + (tmp1->disp.tv_rs << 5);
    rtd_maskl(0xb80001d0, ~mask, reg_val);

    mask = (0x7 << 10);
    reg_val = (tmp1->disp.tv_pstep << 10);
    rtd_maskl(0xb80001cc, ~mask, reg_val);

    mask = (0x3 << 1) + (0x1 << 23) + (0x3 << 26) + (0x3 << 24);
    reg_val = (tmp1->others.pll_vco_scal << 1) + (tmp1->hdmi.tx_pll_kvco << 23) +
              (tmp1->hdmi.tx_pll_cp << 26) + (tmp1->hdmi.tx_pll_cs << 24);
    rtd_maskl(0xb80001c4, ~mask, reg_val);
}

void PLLDDSA(UINT8 M_Code,UINT8 N_Code,UINT8 K_Code)
{
	UINT16 VCO_freq=0,X_clk=27;

	rtd_maskl(SYS_PLL_DISP_SD4_reg,~(_BIT2|_BIT1|_BIT0),(_BIT2|_BIT0));	//PLL_POW=1, Power on,output disable
	rtd_maskl(SYS_PLL_DISP_SD4_reg,~_BIT1,_BIT1);						//PLL_RSTB=1, Release reset,K=1

	VCO_freq = X_clk*M_Code/N_Code;

	rtd_maskl(SYS_PLL_DISP_SD1_reg,0xff801fff,	(_BIT21|_BIT20|_BIT17|_BIT16|_BIT15));	//Icp=10uA,RS=20.3k,CS=61.6pF,CP=1.3pF

	N_Code = N_Code - 1;
	M_Code = M_Code - 2;
	K_Code = K_Code - 1;
	rtd_maskl(SYS_PLL_DISP_SD1_reg,0x007fffff,((((UINT32) N_Code)<<30)|(((UINT32) M_Code)<<23)));
	//must be
	BusyWaiting(10000);       	        											//Delay for Stable Value
	rtd_maskl(SYS_PLL_DISP_SD4_reg,~(_BIT5|_BIT4|_BIT2|_BIT1|_BIT0),((K_Code<<4)|_BIT1|_BIT0));	//PLL_OEB=0, Output enable
	BusyWaiting(10000);       	        											//Delay for Stable Value

}

void PLLHDMI(UINT8 M_Code,UINT8 N_Code,UINT8 Q_Code)
{
	rtd_maskl(SYS_PLL_OTHER_reg,~(_BIT8|_BIT7),(_BIT8|_BIT7));			//PLLHDMI_SEL= CKIN_HDMI
	rtd_maskl(SYS_PLL_HDMI2_reg,~(_BIT2|_BIT1|_BIT0),(_BIT2|_BIT0));	//PLL_POW=1, Power on,output disable
	rtd_maskl(SYS_PLL_HDMI2_reg,~_BIT1,_BIT1);						//PLL_RSTB=1, Release reset,K=1

	rtd_maskl(SYS_PLL_HDMI_reg,0xfffff007,	(_BIT11|_BIT10|_BIT9|_BIT8|_BIT6|_BIT5|_BIT4));	//Icp=12.5uA,RS=24k,CS=36pF,CP=1.5pF

	M_Code = M_Code - 2;
	Q_Code = Q_Code - 2;

	if (N_Code > 1){
		N_Code = N_Code - 2;
		rtd_maskl(SYS_PLL_HDMI_reg,0x00000fff,((((UINT32) Q_Code)<<12)|(((UINT32) N_Code)<<24)|(((UINT32) M_Code)<<16)));
	}else{
		rtd_maskl(SYS_PLL_HDMI_reg,0x00000fff,((((UINT32) Q_Code)<<12)|(((UINT32) M_Code)<<16)|_BIT23));//disable N
	}
	//must be
	BusyWaiting(10000);           	        											//Delay for Stable Value
	rtd_maskl(SYS_PLL_HDMI2_reg,~(_BIT2|_BIT1|_BIT0),(_BIT1|_BIT0));	//PLL_OEB=0, Output enable
	BusyWaiting(10000);           	        											//Delay for Stable Value

}

static unsigned int check_video_format_idx(unsigned int idx)
{
    unsigned int ret = 0;
#if OUTPUT_SRC_SELECT_HDMI
    if (idx != 0xdead)
    {
        ret = idx;
    }
    else
    {
        ret = HDMI_TX_1920_1080P_60HZ;
        printf("- %d idx doesn't support, so change to 1080P@60 idx\n", idx);
    }
#else
    if ((idx != 0xdead) && (idx != HDMI_TX_3840_2160P_30HZ))
    {
        ret = idx;
    }
    else
    {
        ret = HDMI_TX_1920_1080P_60HZ;
        printf("- %d idx doesn't support, so change to 1080P@60 idx\n", idx);
    }
#endif
    return ret;
}

static unsigned int get_format_idx(UINT8 format_num)
{
    UINT8 i;
    unsigned int ret = 0, idx = 0;
    switch (format_num) {
        //720(1440)x480i@60Hz
        case 1: //TV NTSC
            idx = HDMI_TX_720_1440_480I_60HZ;
            break;
        //720x480P@60Hz
        case 2: //TV 525p
        case 17:
            idx = HDMI_TX_720_480P_60HZ;
            break;
        //720(1440)x576i@50Hz
        case 3: //TV PAL
            idx = HDMI_TX_720_1440_576I_50HZ;
            break;
        //720x576p@50Hz
        case 4: //TV 626p
            idx = HDMI_TX_720_576P_50HZ;
            break;
        //1280x720P@60Hz
        case 5: //TV 720p60Hz
            idx = HDMI_TX_1280_720P_60HZ;
            break;
        //1920x1080i@50Hz
        case 6: //TV 1080i50Hz
            idx = HDMI_TX_1920_1080I_50HZ;
            break;
        //1920x1080i@60Hz
        case 7: //TV 1080i60Hz
            idx = HDMI_TX_1920_1080I_60HZ;
            break;
        //1920x1080p@24Hz
        case 18: //TV 1080p24Hz
            idx = HDMI_TX_1920_1080P_24HZ;
            break;
        //1280x720p@50Hz
        case 20: //TV 720p50Hz
            idx = HDMI_TX_1280_720P_50HZ;
            break;
        //1920x1080p@50Hz
        case 21: //TV 1080p50Hz
            idx = HDMI_TX_1920_1080P_50HZ;
            break;
        case 22:
            idx = HDMI_TX_1920_1080P_60HZ;
            break;
        case 32:
            idx = HDMI_TX_3840_2160P_30HZ;
            break;
        case 33:
            idx = HDMI_TX_800_600P_72HZ;
            break;
        case 34:
            idx = HDMI_TX_1600_1200P_85HZ;
            break;
        default:
            idx = 0xdead;
            break;
    }

    ret = check_video_format_idx(idx);
    printf("- video format num = %d translates to index = %d\n", format_num, ret);
    return ret;
}

static set_hdmi_timing_gen_for_2d_video_timing(UINT8 format_idx)
{
    //adam setting
    /*
    rtd_outl(0xb800d234, 0x0117077f);  // horizontal blank = 280-1, horizontal data active = 1920-1
    rtd_outl(0xb800d238, 0x002b0057);  // horizontal sync width = 44 -1, horizontal front porch = 88-1
    rtd_outl(0xb800d23c, 0x00000093);  // horizontal back proch = 148-1
    rtd_outl(0xb800d240, 0x04370437);  // vertical single field size (only active video) = 1080 -1, vertical total data active (with active space) = 1080-1
    rtd_outl(0xb800d24c, 0x000a002c);  // vertical sync width = 10, vertical blank = 45-1
    rtd_outl(0xb800d250, 0x00230008);  // vertical back proch = 36-1, vertical front porch = 8
    */
    hdmi_tx_timing_gen_st *tmp;
    tmp = &cea_timing_table[0] + format_idx;
    //0xb800d234
    rtd_outl(HDMI_H_PARA1_reg,
                     HDMI_H_PARA1_hblank(tmp->h.blank-1)|
                     HDMI_H_PARA1_hactive(tmp->h.active-1));
    //0xb800d238
    rtd_outl(HDMI_H_PARA2_reg,
                     HDMI_H_PARA2_hsync(tmp->h.sync-1)|
                     HDMI_H_PARA2_hfront(tmp->h.front-1));
    //0xb800d23c
    rtd_outl(HDMI_H_PARA3_reg,
                     HDMI_H_PARA3_hback(tmp->h.back-1));

    //0xb800d240
    rtd_outl(HDMI_V_PARA1_reg,
                     HDMI_V_PARA1_Vact_video(tmp->v.active-1)|
                     HDMI_V_PARA1_vactive(tmp->v.active-1));
    //0xb800d244
    rtd_outl(HDMI_V_PARA2_reg,
                     HDMI_V_PARA2_Vact_space1(0)|
                     HDMI_V_PARA2_Vact_space(tmp->v.space-1));

    //0xb800d248
    rtd_outl(HDMI_V_PARA3_reg,
                     HDMI_V_PARA3_Vblank3(0)|
                     HDMI_V_PARA3_Vact_space2(0));

    //0xb800d24c
    rtd_outl(HDMI_V_PARA4_reg,
                     (HDMI_V_PARA4_vsync((tmp->v.sync-1)<<1))|
                     HDMI_V_PARA4_vblank(tmp->v.blank-1));
    //0xb800d250
    rtd_outl(HDMI_V_PARA5_reg,
                     HDMI_V_PARA5_vback(tmp->v.back-1)|
                     (HDMI_V_PARA5_vfront((tmp->v.front-1)<<1)));

    //0xb800d254
    rtd_outl(HDMI_V_PARA6_reg,
                     HDMI_V_PARA6_Vsync1((0<<1))|
                     HDMI_V_PARA6_Vblank1(0));
    //0xb800d258
    rtd_outl(HDMI_V_PARA7_reg,
                     HDMI_V_PARA7_Vback1(0)|
                     HDMI_V_PARA7_Vfront1((0<<1)));
    //0xb800d25c
    rtd_outl(HDMI_V_PARA8_reg,
                     HDMI_V_PARA8_Vsync2((0<<1))|
                     HDMI_V_PARA8_Vblank2(0));
    //0xb800d260
    rtd_outl(HDMI_V_PARA9_reg,
                     HDMI_V_PARA9_Vback2(0)|
                     HDMI_V_PARA9_Vfront2((0<<1)));
    //0xb800d264
    rtd_outl(HDMI_V_PARA12_reg,
                     (HDMI_V_PARA12_vsynci(((tmp->vi.synci-1)<<1) + 1))|
                     HDMI_V_PARA12_vblanki(tmp->vi.blanki-1));
    //0xb800d268
    rtd_outl(HDMI_V_PARA13_reg,
                     HDMI_V_PARA13_vbacki(tmp->vi.backi-1)|
                     (HDMI_V_PARA13_vfronti(((tmp->vi.fronti-1)<<1) + 1)));
    //0xb800d26c
    rtd_outl(HDMI_V_PARA10_reg,
                     HDMI_V_PARA10_G(0x00beef));
    //0xb800d270
    rtd_outl(HDMI_V_PARA11_reg,
                     HDMI_V_PARA11_B(0x00beef)|
                     HDMI_V_PARA11_R(0x00beef));

}

static void set_hdmi_timing_gen_for_3d_video_timing(UINT8 video_format, UINT8 format_3d)
{
        switch(video_format)
        {
            //720(1440)x480i@60Hz===============================================
            case 1: //TV NTSC-M
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(275)|
                                 HDMI_H_PARA1_hactive(1439));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(123)|
                                 HDMI_H_PARA2_hfront(37));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(113));

                switch(format_3d)
                {
                    case 0:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(239)|
                                         HDMI_V_PARA1_vactive(1027));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(22)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(21));
                        break;
                    case 1:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(239)|
                                         HDMI_V_PARA1_vactive(239));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1(3<<1)|
                                         HDMI_V_PARA6_Vblank1(21));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(14)|
                                         HDMI_V_PARA7_Vfront1(4<<1));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2(3<<1)|
                                         HDMI_V_PARA8_Vblank2(21));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(14)|
                                         HDMI_V_PARA9_Vfront2(4<<1));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(22)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        break;
                    case 2:
                        //Line alternative no support!!
                        break;
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(239)|
                                         HDMI_V_PARA1_vactive(239));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((0<<1))|
                                         HDMI_V_PARA6_Vblank1(0));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(0)|
                                         HDMI_V_PARA7_Vfront1((0<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2((0<<1))|
                                         HDMI_V_PARA8_Vblank2(0));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(0)|
                                         HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 4:
                        //L + depth no support!!
                        break;
                    case 5:
                        //L + depth + graphics + graphics-depth no support!!
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(239)|
                                         HDMI_V_PARA1_vactive(239));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((0<<1))|
                                         HDMI_V_PARA6_Vblank1(0));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(0)|
                                         HDMI_V_PARA7_Vfront1((0<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2((0<<1))|
                                         HDMI_V_PARA8_Vblank2(0));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(0)|
                                         HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((3<<1))|
                                 HDMI_V_PARA4_vblank(21));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(14)|
                                 HDMI_V_PARA5_vfront((4<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 //HDMI_V_PARA12_vsynci(((2<<1)+1))|
                                 HDMI_V_PARA12_vsynci(((3<<1)+1))|
                                 HDMI_V_PARA12_vblanki(22));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(16)|
                                 HDMI_V_PARA13_vfronti(((4<<1)+1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //720x480P@60Hz=====================================================
            case 2: //TV 525p(700/300)
            case 17: //TV 525p(714/286)
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(137)|
                                 HDMI_H_PARA1_hactive(719));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(61)|
                                 HDMI_H_PARA2_hfront(15));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(59));

                switch(format_3d)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(1004));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(479));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(2054));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(479)|
                                         HDMI_V_PARA1_vactive(479));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d248
                rtd_outl(HDMI_V_PARA3_reg,
                                 HDMI_V_PARA3_Vblank3(0)|
                                 HDMI_V_PARA3_Vact_space2(0));
                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((6<<1))|
                                 HDMI_V_PARA4_vblank(44));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(29)|
                                 HDMI_V_PARA5_vfront((9<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci((0<<1))|
                                 HDMI_V_PARA12_vblanki(0));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(0)|
                                 HDMI_V_PARA13_vfronti((0<<1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //720(1440)x576i@50Hz===============================================
            case 3: //TV PAL
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(287)|
                                 HDMI_H_PARA1_hactive(1439));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(125)|
                                 HDMI_H_PARA2_hfront(23));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(137));

                switch(format_3d)
                {
                    case 0:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(287)|
                                         HDMI_V_PARA1_vactive(1225));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(24)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(23));
                        break;
                    case 1:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(287)|
                                         HDMI_V_PARA1_vactive(287));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1(3<<1)|
                                         HDMI_V_PARA6_Vblank1(23));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(18)|
                                         HDMI_V_PARA7_Vfront1(2<<1));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2(3<<1)|
                                         HDMI_V_PARA8_Vblank2(23));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(18)|
                                         HDMI_V_PARA9_Vfront2(2<<1));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(24)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        break;
                    case 2:
                        //Line alternative no support!!
                        break;
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(287)|
                                         HDMI_V_PARA1_vactive(287));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        break;
                    case 4:
                        //L + depth no support!!
                        break;
                    case 5:
                        //L + depth + graphics + graphics-depth no support!!
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(287)|
                                         HDMI_V_PARA1_vactive(287));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((3<<1))|
                                 HDMI_V_PARA4_vblank(23));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(18)|
                                 HDMI_V_PARA5_vfront((2<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci(((3<<1)+1))|
                                 HDMI_V_PARA12_vblanki(24));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(19) |
                                 HDMI_V_PARA13_vfronti(((2<<1)+1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //720x576p@50Hz=====================================================
            case 4: //TV 626p
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(143)|
                                 HDMI_H_PARA1_hactive(719));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(63)|
                                 HDMI_H_PARA2_hfront(11));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(67));

                switch(format_3d)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(575)|
                                         HDMI_V_PARA1_vactive(1200));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(48));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(575)|
                                         HDMI_V_PARA1_vactive(575));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(575)|
                                         HDMI_V_PARA1_vactive(2450));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(48));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(575)|
                                         HDMI_V_PARA1_vactive(575));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d248
                rtd_outl(HDMI_V_PARA3_reg,
                                 HDMI_V_PARA3_Vblank3(0)|
                                 HDMI_V_PARA3_Vact_space2(0));
                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(48));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(38)|
                                 HDMI_V_PARA5_vfront((5<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci((0<<1))|
                                 HDMI_V_PARA12_vblanki(0));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(0)|
                                 HDMI_V_PARA13_vfronti((0<<1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //1280x720P@60Hz====================================================
            case 5: //TV 720p60Hz
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(369)|
                                 HDMI_H_PARA1_hactive(1279));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(39)|
                                 HDMI_H_PARA2_hfront(109));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(219));

                switch(format_3d)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(1469));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(29));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(719));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(2969));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(29));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(719));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d248
                rtd_outl(HDMI_V_PARA3_reg,
                                 HDMI_V_PARA3_Vblank3(0)|
                                 HDMI_V_PARA3_Vact_space2(0));
                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(29));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(19)|
                                 HDMI_V_PARA5_vfront((5<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci((0<<1))|
                                 HDMI_V_PARA12_vblanki(0));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(0)|
                                 HDMI_V_PARA13_vfronti((0<<1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //1920x1080i@50Hz===================================================
            case 6: //TV 1080i50Hz
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(719)|
                                 HDMI_H_PARA1_hactive(1919));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(43)|
                                 HDMI_H_PARA2_hfront(527));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(147));

                switch(format_3d)
                {
                    case 0:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(539)|
                                         HDMI_V_PARA1_vactive(2227));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(22)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(21));
                        break;
                    case 1:
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(22)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((4<<1))|
                                         HDMI_V_PARA6_Vblank1(21));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(14) |
                                         HDMI_V_PARA7_Vfront1((1<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2(((4<<1)+1))|
                                         HDMI_V_PARA8_Vblank2(21));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(15)|
                                         HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 2:
                        //Line alternative no support!!
                        break;
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(539)|
                                         HDMI_V_PARA1_vactive(539));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((0<<1))|
                                         HDMI_V_PARA6_Vblank1(0));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(0)|
                                         HDMI_V_PARA7_Vfront1((0<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2((0<<1))|
                                         HDMI_V_PARA8_Vblank2(0));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 4:
                        //L + depth no support!!
                        break;
                    case 5:
                        //L + depth + graphics + graphics-depth no support!!
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(539)|
                                         HDMI_V_PARA1_vactive(539));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((0<<1))|
                                         HDMI_V_PARA6_Vblank1(0));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(0)|
                                         HDMI_V_PARA7_Vfront1((0<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2((0<<1))|
                                         HDMI_V_PARA8_Vblank2(0));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(0)|
                                         HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(21));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(14)|
                                 HDMI_V_PARA5_vfront((2<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci(((5<<1)+1))|
                                 HDMI_V_PARA12_vblanki(22));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(15)|
                                 HDMI_V_PARA13_vfronti(((2<<1)+1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d268
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //1920x1080i@60Hz===================================================
            case 7: //TV 1080i60Hz
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(279)|
                                 HDMI_H_PARA1_hactive(1919));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(43)|
                                 HDMI_H_PARA2_hfront(87));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(147));

                switch(format_3d)
                {
                    case 0:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(539)|
                                         HDMI_V_PARA1_vactive(2227));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(22)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(21));
                        break;
                    case 1:
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((4<<1))|
                                         HDMI_V_PARA6_Vblank1(21));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(14)|
                                         HDMI_V_PARA7_Vfront1((1<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2(((4<<1)+1))|
                                         HDMI_V_PARA8_Vblank2(21));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(15)|
                                         HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 2:
                        //Line alternative no support!!
                        break;
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(539)|
                                         HDMI_V_PARA1_vactive(539));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((0<<1))|
                                         HDMI_V_PARA6_Vblank1(0));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(0)|
                                         HDMI_V_PARA7_Vfront1((0<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2((0<<1))|
                                         HDMI_V_PARA8_Vblank2(0));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(0)|
                                         HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 4:
                        //L + depth no support!!
                        break;
                    case 5:
                        //L + depth + graphics + graphics-depth no support!!
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(539)|
                                         HDMI_V_PARA1_vactive(539));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        //0xb800d248
                        rtd_outl(HDMI_V_PARA3_reg,
                                         HDMI_V_PARA3_Vblank3(0)|
                                         HDMI_V_PARA3_Vact_space2(0));
                        //0xb800d254
                        rtd_outl(HDMI_V_PARA6_reg,
                                         HDMI_V_PARA6_Vsync1((0<<1))|
                                         HDMI_V_PARA6_Vblank1(0));
                        //0xb800d258
                        rtd_outl(HDMI_V_PARA7_reg,
                                         HDMI_V_PARA7_Vback1(0)|
                                         HDMI_V_PARA7_Vfront1((0<<1)));
                        //0xb800d25c
                        rtd_outl(HDMI_V_PARA8_reg,
                                         HDMI_V_PARA8_Vsync2((0<<1))|
                                         HDMI_V_PARA8_Vblank2(0));
                        //0xb800d260
                        rtd_outl(HDMI_V_PARA9_reg,
                                         HDMI_V_PARA9_Vback2(0)|
                                         HDMI_V_PARA9_Vfront2((0<<1)));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(21));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(14)|
                                 HDMI_V_PARA5_vfront((2<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci(((5<<1)+1))|
                                 HDMI_V_PARA12_vblanki(22));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(15)|
                                 HDMI_V_PARA13_vfronti(((2<<1)+1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d268
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //1920x1080p@24Hz===================================================
            case 18: //TV 1080p24Hz
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(829)|
                                 HDMI_H_PARA1_hactive(1919));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(43)|
                                 HDMI_H_PARA2_hfront(637));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(147));

                switch(format_3d)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(2204));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(1079));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(4454));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(1079));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d248
                rtd_outl(HDMI_V_PARA3_reg,
                                 HDMI_V_PARA3_Vblank3(0)|
                                 HDMI_V_PARA3_Vact_space2(0));
                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(44));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(35)|
                                 HDMI_V_PARA5_vfront((4<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci((0<<1))|
                                 HDMI_V_PARA12_vblanki(0));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(0)|
                                 HDMI_V_PARA13_vfronti((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d268
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //1280x720p@50Hz====================================================
            case 20: //TV 720p50Hz
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(699)|
                                 HDMI_H_PARA1_hactive(1279));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(39)|
                                 HDMI_H_PARA2_hfront(439));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(219));

                switch(format_3d)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(1469));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(29));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(719));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(2969));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(29));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(719)|
                                         HDMI_V_PARA1_vactive(719));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d248
                rtd_outl(HDMI_V_PARA3_reg,
                                 HDMI_V_PARA3_Vblank3(0)|
                                 HDMI_V_PARA3_Vact_space2(0));
                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(29));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(19)|
                                 HDMI_V_PARA5_vfront((5<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci((0<<1))|
                                 HDMI_V_PARA12_vblanki(0));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(0)|
                                 HDMI_V_PARA13_vfronti((0<<1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //1920x1080p@50Hz====================================================
            case 21: //TV 1080p50Hz
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(719)|
                                 HDMI_H_PARA1_hactive(1919));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(43)|
                                 HDMI_H_PARA2_hfront(527));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(147));

                switch(format_3d)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(2204));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(1079));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(4454));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(1079));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d248
                rtd_outl(HDMI_V_PARA3_reg,
                                 HDMI_V_PARA3_Vblank3(0)|
                                 HDMI_V_PARA3_Vact_space2(0));
                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(44));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(35)|
                                 HDMI_V_PARA5_vfront((4<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci((0<<1))|
                                 HDMI_V_PARA12_vblanki(0));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(0)|
                                 HDMI_V_PARA13_vfronti((0<<1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;
            //1920x1080p@60Hz====================================================
            case 22: //TV 1080p60Hz
                //0xb800d234
                rtd_outl(HDMI_H_PARA1_reg,
                                 HDMI_H_PARA1_hblank(279)|
                                 HDMI_H_PARA1_hactive(1919));
                //0xb800d238
                rtd_outl(HDMI_H_PARA2_reg,
                                 HDMI_H_PARA2_hsync(43)|
                                 HDMI_H_PARA2_hfront(87));
                //0xb800d23c
                rtd_outl(HDMI_H_PARA3_reg,
                                 HDMI_H_PARA3_hback(147));

                switch(format_3d)
                {
                    case 0:
                    case 4:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(2204));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 1:
                        //Field alternative no support!!
                        break;
                    case 2:
                    case 3:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(1079));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 5:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(4454));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(44));
                        break;
                    case 6:
                    case 8:
                        //0xb800d240
                        rtd_outl(HDMI_V_PARA1_reg,
                                         HDMI_V_PARA1_Vact_video(1079)|
                                         HDMI_V_PARA1_vactive(1079));
                        //0xb800d244
                        rtd_outl(HDMI_V_PARA2_reg,
                                         HDMI_V_PARA2_Vact_space1(0)|
                                         HDMI_V_PARA2_Vact_space(0));
                        break;
                    case 7:
                        break;
                    default:
                        break;
                }

                //0xb800d248
                rtd_outl(HDMI_V_PARA3_reg,
                                 HDMI_V_PARA3_Vblank3(0)|
                                 HDMI_V_PARA3_Vact_space2(0));
                //0xb800d24c
                rtd_outl(HDMI_V_PARA4_reg,
                                 HDMI_V_PARA4_vsync((5<<1))|
                                 HDMI_V_PARA4_vblank(44));
                //0xb800d250
                rtd_outl(HDMI_V_PARA5_reg,
                                 HDMI_V_PARA5_vback(35)|
                                 HDMI_V_PARA5_vfront((4<<1)));
                //0xb800d254
                rtd_outl(HDMI_V_PARA6_reg,
                                 HDMI_V_PARA6_Vsync1((0<<1))|
                                 HDMI_V_PARA6_Vblank1(0));
                //0xb800d258
                rtd_outl(HDMI_V_PARA7_reg,
                                 HDMI_V_PARA7_Vback1(0)|
                                 HDMI_V_PARA7_Vfront1((0<<1)));
                //0xb800d25c
                rtd_outl(HDMI_V_PARA8_reg,
                                 HDMI_V_PARA8_Vsync2((0<<1))|
                                 HDMI_V_PARA8_Vblank2(0));
                //0xb800d260
                rtd_outl(HDMI_V_PARA9_reg,
                                 HDMI_V_PARA9_Vback2(0)|
                                 HDMI_V_PARA9_Vfront2((0<<1)));
                //0xb800d264
                rtd_outl(HDMI_V_PARA12_reg,
                                 HDMI_V_PARA12_vsynci((0<<1))|
                                 HDMI_V_PARA12_vblanki(0));
                //0xb800d268
                rtd_outl(HDMI_V_PARA13_reg,
                                 HDMI_V_PARA13_vbacki(0)|
                                 HDMI_V_PARA13_vfronti((0<<1)));
                //0xb800d26c
                rtd_outl(HDMI_V_PARA10_reg,
                                 HDMI_V_PARA10_G(0x00beef));
                //0xb800d270
                rtd_outl(HDMI_V_PARA11_reg,
                                 HDMI_V_PARA11_B(0x00beef)|
                                 HDMI_V_PARA11_R(0x00beef));
                break;

            default:
                break;
        }

}

static void set_tve_timing_gen_for_2d_video_timing(UINT8 format_idx, UINT8 deep_color, UINT8 deep_depth)
{
    hdmi_tx_tve_timing_gen_st *tmp;

    if ((deep_color == 0) || ((deep_color == 1) && (deep_depth == 4)))
    {
        tmp = &tve_timg_8bit_dpc_table[0] + format_idx;
    }
    else if ((deep_color == 1) && (deep_depth == 5))
    {
        tmp = &tve_timg_10bit_dpc_table[0] + format_idx;
    }
    else if ((deep_color == 1) && (deep_depth == 6))
    {
        tmp = &tve_timg_12bit_dpc_table[0] + format_idx;
    }

    rtd_outl(TVE_HDMI_ST_reg,
                     TVE_HDMI_ST_write_en4(1)|TVE_HDMI_ST_sync_en(1)|
                     TVE_HDMI_ST_write_en3(1)|TVE_HDMI_ST_ch_sel(tmp->interlace)| //0:progressive, 1:interlace
                     TVE_HDMI_ST_write_en2(1)|TVE_HDMI_ST_vpos(tmp->v.vpos)|
                     TVE_HDMI_ST_write_en1(1)|TVE_HDMI_ST_hpos(tmp->h.hpos));
    //0xb80180bc
    rtd_outl(TVE_HDMI_DISP_HS_reg,
                     TVE_HDMI_DISP_HS_write_en2(1)|TVE_HDMI_DISP_HS_hs_start(tmp->h.hs_st)|
                     TVE_HDMI_DISP_HS_write_en1(1)|TVE_HDMI_DISP_HS_hs_end(tmp->h.hs_end));
    //0xb80180c0
    rtd_outl(TVE_HDMI_DISP_VSST1_reg,
                     TVE_HDMI_DISP_VSST1_write_en2(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1v(tmp->v.st_pos1v)|
                     TVE_HDMI_DISP_VSST1_write_en1(1)|TVE_HDMI_DISP_VSST1_vs_st_pos1h(tmp->v.st_pos1h));
    //0xb80180c4
    rtd_outl(TVE_HDMI_DISP_VSED1_reg,
                     TVE_HDMI_DISP_VSED1_write_en2(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1v(tmp->v.end_pos1v)|
                     TVE_HDMI_DISP_VSED1_write_en1(1)|TVE_HDMI_DISP_VSED1_vs_end_pos1h(tmp->v.end_pos1h));
    //0xb80180c8
    rtd_outl(TVE_HDMI_DISP_VSST2_reg,
                     TVE_HDMI_DISP_VSST2_write_en2(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2v(tmp->v.st_pos2v)|
                     TVE_HDMI_DISP_VSST2_write_en1(1)|TVE_HDMI_DISP_VSST2_vs_st_pos2h(tmp->v.st_pos2h));
    //0xb80180cc
    rtd_outl(TVE_HDMI_DISP_VSED2_reg,
                     TVE_HDMI_DISP_VSED2_write_en2(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2v(tmp->v.end_pos2v)|
                     TVE_HDMI_DISP_VSED2_write_en1(1)|TVE_HDMI_DISP_VSED2_vs_end_pos2h(tmp->v.end_pos2h));
    //0xb80180d0
    rtd_outl(TVE_HDMI_PXLACT_reg,
                     TVE_HDMI_PXLACT_write_en2(1)|TVE_HDMI_PXLACT_hpos_end(tmp->h.hpos_st)|
                     TVE_HDMI_PXLACT_write_en1(1)|TVE_HDMI_PXLACT_hpos_st(tmp->h.hpos_end));
    //0xb800d030
    rtd_outl(HDMI_SYNC_DLY_reg,
                     HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(tmp->disp.dly_nor_v)|
                     HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(tmp->disp.dly_nor_h)|
                     HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(tmp->disp.dly_disp_v)|
                     HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(tmp->disp.dly_disp_h));
    //0xb800d154
    rtd_outl(HDMI_DPC_reg,
                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(tmp->dpc.vfch_num)|
                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(tmp->dpc.fp_swen)|
                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(tmp->dpc.fp)|
                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(tmp->dpc.swen)|
                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(tmp->dpc.default_ph)|
                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(deep_depth)|
                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(deep_color));
}

static void set_deep_color_and_disp_delay_timing(UINT8 format_idx, UINT8 deep_color, UINT8 deep_depth)
{
    hdmi_tx_timing_dpc_disp_st *tmp;

    if ((deep_color == 0) || ((deep_color == 1) && (deep_depth == 4)))
    {
        tmp = &dpc_8bit_disp_table[0] + format_idx;
    }
    else if ((deep_color == 1) && (deep_depth == 5))
    {
        tmp = &dpc_10bit_disp_table[0] + format_idx;
    }
    else if ((deep_color == 1) && (deep_depth == 6))
    {
        tmp = &dpc_12bit_disp_table[0] + format_idx;
    }

    rtd_outl(HDMI_SYNC_DLY_reg,
                     HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(tmp->disp.dly_nor_v)|
                     HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(tmp->disp.dly_nor_h)|
                     HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(tmp->disp.dly_disp_v)|
                     HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(tmp->disp.dly_disp_h));
    //0xb800d154
    rtd_outl(HDMI_DPC_reg,
                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(tmp->dpc.vfch_num)|
                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(tmp->dpc.fp_swen)|
                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(tmp->dpc.fp)|
                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(tmp->dpc.swen)|
                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(tmp->dpc.default_ph)|
                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(deep_depth)|
                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(deep_color));
}

void SET_HDMI_Video(UINT8 Video_Format, UINT8 Pixel_Colocr_Format, UINT8 DVI_or_HDMI, UINT8 Deep_Color, UINT8 Deep_Depth,
                    UINT8 xv_YCC, UINT8 Timing_Gen, UINT8 En_3D, UINT8 Format_3D, bool pp_mode_en)
{
    UINT8 Video_Code, IP, SHD;
    unsigned int format_idx;
    UINT8 ext_video, ext_format;
    bool pp_en;

    format_idx = get_format_idx(Video_Format);
    if ((format_idx == HDMI_TX_800_600P_72HZ) ||
        (format_idx == HDMI_TX_1600_1200P_85HZ))
    {
        DVI_or_HDMI = 0;
    }
  
#if !OUTPUT_SRC_SELECT_HDMI

    rtd_outl(HDMI_MHLCTRL_reg,
                     HDMI_MHLCTRL_write_en1(1)|HDMI_MHLCTRL_mhl_enable(0)| //MHL disable
                     HDMI_MHLCTRL_write_en2(0)|
                     HDMI_MHLCTRL_write_en3(0)|
                     HDMI_MHLCTRL_write_en4(0)|
                     HDMI_MHLCTRL_write_en5(0)|
                     HDMI_MHLCTRL_write_en6(0));

    if ((format_idx == HDMI_TX_1920_1080P_60HZ) ||
        (format_idx == HDMI_TX_1920_1080P_50HZ))
    {
        pp_en = TRUE;
    }
    else
    {
        pp_en = pp_mode_en;
    }

#endif

    //0xb800d034
    rtd_outl(HDMI_CR_reg,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(0)| //TMDS Encoder disable
                     HDMI_CR_write_en2(0)|HDMI_CR_enablehdcp(0)|
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(0)); //HDMI disable
    //0xb800d0bc
    rtd_outl(HDMI_ICR_reg,
                     HDMI_ICR_write_en3(1)|HDMI_ICR_enaudio(0)| //0:disable HDMI audio data path
                     HDMI_ICR_write_en2(1)|HDMI_ICR_envitd(0)|
                     HDMI_ICR_write_en1(0)|HDMI_ICR_vitd(0));

    Video_Code = cea_timing_table[format_idx].video_code;
    //=====================================================================================================
    // HDMI Timing gen
    //=====================================================================================================
    if (Timing_Gen)
    {
        printf("- hdmi tx timing gen\n");
        if (En_3D)
        {
            // FIXME:4k2k
            set_hdmi_timing_gen_for_3d_video_timing(Video_Format, Format_3D);
        }
        else
        {
            set_hdmi_timing_gen_for_2d_video_timing(format_idx);
        }

	    // printf("HDMI test start........07\n");
        //Deep Color 24bit========================================================================================
        /*adam setting
        rtd_outl(0xb800d030, 0x00000924);  // hsync/vsync delay all 0
        rtd_outl(0xb800d154, 0x5280f100);  // video format change wait 1 vsync, do not use setting first deep color phase by SW, setting first deep color phase by SW, use default deep phase by SW, default phase, do not deep color mode
        */
        //FIXME : set_deep_color_and_disp_delay_timing(format_idx, Deep_Color, Deep_Depth);
        if (Deep_Color==0 || (Deep_Color==1 && Deep_Depth==4))
        {
	        // printf("HDMI test start........08\n");
        	//rtd_outl(HDMI_DUMMY_0_reg, HDMI_DUMMY_dummy(0xA0000000)); //fix 576i
            //0xb800d030
            rtd_outl(HDMI_SYNC_DLY_reg,
                             HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                             HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                             HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                             HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
            //0xb800d154
            rtd_outl(HDMI_DPC_reg,
                             HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                             HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                             HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                             HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                             HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                             HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                             HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
        }
        //Deep Color 30bit========================================================================================
        //FIXME 4k2k@30
        if (Deep_Color==1 && Deep_Depth==5)
        {
            switch (Video_Format)
            {
                case 2: //TV 525p
                    //0xb800d030
                    rtd_outl(HDMI_SYNC_DLY_reg,
                                     HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                     HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                     HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                     HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                    //0xb800d154
                    rtd_outl(HDMI_DPC_reg,
                    			//20120806 kist
                                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(3)|
                                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(1)|
                                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(2)|
                                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(0)|
                                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
                    			/*
                                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(3)|
                                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(1)|
                                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(3)|
                                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(0)|
                                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));*/
                    break;
                //720(1440)x576i@50Hz(Deep Color 30bit)-----------------------------
                case 3: //TV PAL
                    //0xb800d030
                    rtd_outl(HDMI_SYNC_DLY_reg,
                                     HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                     HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                     HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                     HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                    //0xb800d154
                    rtd_outl(HDMI_DPC_reg,
                                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(3)|
                                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(1)|
                                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(0)|
                                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
                    break;
                //1280x720P@60Hz(Deep Color 30bit)----------------------------------
                case 5: //TV 720p60Hz
                    //0xb800d030
                    rtd_outl(HDMI_SYNC_DLY_reg,
                                     HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                     HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                     HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                     HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
			        //0xb800d154
                    rtd_outl(HDMI_DPC_reg,
                                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(3)|
                                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(1)|
                                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(2)|
                                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(0)|
                                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
                    break;
                //1920x1080p@24Hz(Deep Color 30bit)---------------------------------
                case 18: //TV 1080p24Hz
                    //0xb800d030
                    rtd_outl(HDMI_SYNC_DLY_reg,
                                     HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                     HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                     HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                     HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                    //0xb800d154
                    rtd_outl(HDMI_DPC_reg,
                                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(3)|
                                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(1)|
                                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(0)|
                                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
                    break;
                default:
                    //0xb800d030
                    rtd_outl(HDMI_SYNC_DLY_reg,
                                     HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                                     HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                                     HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                                     HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
                    //0xb800d154
                    rtd_outl(HDMI_DPC_reg,
                                     HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                                     HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                                     HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                                     HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                                     HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                                     HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                                     HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));
                    break;
            }
        }
        //Deep Color 36bit========================================================================================
        if (Deep_Color==1 && Deep_Depth==6)
        {
            //	rtd_outl(HDMI_DUMMY_0_reg, HDMI_DUMMY_dummy(0xa0000000)); //fix 576i 30-bit hsync error
            //0xb800d030
            rtd_outl(HDMI_SYNC_DLY_reg,
                             HDMI_SYNC_DLY_write_en4(1)|HDMI_SYNC_DLY_nor_v(0)|
                             HDMI_SYNC_DLY_write_en3(1)|HDMI_SYNC_DLY_nor_h(0)|
                             HDMI_SYNC_DLY_write_en2(1)|HDMI_SYNC_DLY_disp_v(0)|
                             HDMI_SYNC_DLY_write_en1(1)|HDMI_SYNC_DLY_disp_h(0));
            //0xb800d154
            rtd_outl(HDMI_DPC_reg,
                             HDMI_DPC_write_en9(1)|HDMI_DPC_dp_vfch_num(1)|
                             HDMI_DPC_write_en8(1)|HDMI_DPC_fp_swen(0)|
                             HDMI_DPC_write_en7(1)|HDMI_DPC_fp(0)|
                             HDMI_DPC_write_en4(1)|HDMI_DPC_dp_swen(1)|
                             HDMI_DPC_write_en3(1)|HDMI_DPC_default_phase(1)|
                             HDMI_DPC_write_en2(1)|HDMI_DPC_color_depth(Deep_Depth)|
                             HDMI_DPC_write_en1(1)|HDMI_DPC_dpc_enable(Deep_Color));

        }
    }
    else
    {
        //FIXME : 4k2k@30
        printf("- hdmi tve timing gen\n");
        set_tve_timing_gen_for_2d_video_timing(format_idx, Deep_Color, Deep_Depth);
    }

    if(Video_Code==6 || Video_Code==21 || Video_Code==20 || Video_Code==5){
        IP = 1;
    }else{
        IP = 0;
    }
    switch(Video_Format) {
        //720(1440)x480i@60Hz
        case 1: //TV NTSC
        //720x480P@60Hz
        case 2: //TV 525p
        //720(1440)x576i@50Hz
        case 3: //TV PAL
        //720x576p@50Hz
        case 4: //TV 626p
            SHD = 1;
            break;
        //1280x720P@60Hz
        case 5: //TV 720p60Hz
        //1920x1080i@50Hz
        case 6: //TV 1080i50Hz
        //1920x1080i@60Hz
        case 7: //TV 1080i60Hz
        //1920x1080p@24Hz
        case 18: //TV 1080p24Hz
        //1280x720p@50Hz
        case 20: //TV 720p50Hz
        //1920x1080p@50Hz
        case 31: //TV 1080p50Hz
        //1920x1080p@60Hz
        case 16: //TV 1080p60Hz
        case 32: //TV 4k2k@30Hz
        case 0:
            SHD = 0;
            break;
    }

    //=====================================================================================================
    // HDMI Control
    //=====================================================================================================
    //adam setting
    //rtd_outl(0xb800d020, 0x00002004);  // image end signal (don't care in FPGA), progressive HD mode, HDMI timing genator enable

    if(Video_Code==6 || Video_Code==21) //480i and 576i
    {
       // printf("HDMI test start........21\n");
        rtd_outl(HDMI_CHNL_SEL_reg,
                             HDMI_CHNL_SEL_video_sd(SHD)|
                             HDMI_CHNL_SEL_Interlaced_vfmt(IP)|
                             HDMI_CHNL_SEL_3D_video_format(Format_3D)|
                             HDMI_CHNL_SEL_En_3D(En_3D)|
                             HDMI_CHNL_SEL_timing_gen_en(Timing_Gen)|//20121214 kist
                             HDMI_CHNL_SEL_chl_sel(1)); //0:P channel 1:I channel
    }
    else
    {
        //0xb800d020
        rtd_outl(HDMI_CHNL_SEL_reg,
                             HDMI_CHNL_SEL_video_sd(SHD)|
                             HDMI_CHNL_SEL_Interlaced_vfmt(IP)|
                             HDMI_CHNL_SEL_3D_video_format(Format_3D)|
                             HDMI_CHNL_SEL_En_3D(En_3D)|
                             HDMI_CHNL_SEL_timing_gen_en(Timing_Gen)|
                             HDMI_CHNL_SEL_chl_sel(0)); //0:P channel 1:I channel
    }
    if(DVI_or_HDMI==0) //DVI mode
        Pixel_Colocr_Format = 0;

    if(Pixel_Colocr_Format==0) //RGB mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        rtd_outl(HDMI_CS_TRANS0_reg, HDMI_CS_TRANS0_c1(0x04a80));
        rtd_outl(HDMI_CS_TRANS1_reg, HDMI_CS_TRANS1_c2(0x1e700));
        rtd_outl(HDMI_CS_TRANS2_reg, HDMI_CS_TRANS2_c3(0x1cc40));
        rtd_outl(HDMI_CS_TRANS3_reg, HDMI_CS_TRANS3_c4(0x04a80));
        rtd_outl(HDMI_CS_TRANS4_reg, HDMI_CS_TRANS4_c5(0x08140));
        rtd_outl(HDMI_CS_TRANS5_reg, HDMI_CS_TRANS5_c6(0x00000));
        rtd_outl(HDMI_CS_TRANS6_reg, HDMI_CS_TRANS6_c7(0x04a80));
        rtd_outl(HDMI_CS_TRANS7_reg, HDMI_CS_TRANS7_c8(0x00000));
        rtd_outl(HDMI_CS_TRANS8_reg, HDMI_CS_TRANS8_c9(0x06680));
        rtd_outl(HDMI_CS_TRANS9_reg, HDMI_CS_TRANS9_k1(0x021b0));
        rtd_outl(HDMI_CS_TRANS10_reg, HDMI_CS_TRANS10_k2(0x0ba70));
        rtd_outl(HDMI_CS_TRANS11_reg, HDMI_CS_TRANS11_k3(0x0c840));
    }
    else //YCbCr mode
    {
        //-- Color Transform (YCbCr 4:4:4 -> RGB 4:4:4)
        rtd_outl(HDMI_CS_TRANS0_reg, HDMI_CS_TRANS0_c1(0x04000));
        rtd_outl(HDMI_CS_TRANS1_reg, HDMI_CS_TRANS1_c2(0x00000));
        rtd_outl(HDMI_CS_TRANS2_reg, HDMI_CS_TRANS2_c3(0x00000));
        rtd_outl(HDMI_CS_TRANS3_reg, HDMI_CS_TRANS3_c4(0x00000));
        rtd_outl(HDMI_CS_TRANS4_reg, HDMI_CS_TRANS4_c5(0x04000));
        rtd_outl(HDMI_CS_TRANS5_reg, HDMI_CS_TRANS5_c6(0x00000));
        rtd_outl(HDMI_CS_TRANS6_reg, HDMI_CS_TRANS6_c7(0x00000));
        rtd_outl(HDMI_CS_TRANS7_reg, HDMI_CS_TRANS7_c8(0x00000));
        rtd_outl(HDMI_CS_TRANS8_reg, HDMI_CS_TRANS8_c9(0x04000));
        rtd_outl(HDMI_CS_TRANS9_reg, HDMI_CS_TRANS9_k1(0x0));
        rtd_outl(HDMI_CS_TRANS10_reg, HDMI_CS_TRANS10_k2(0x0));
        rtd_outl(HDMI_CS_TRANS11_reg, HDMI_CS_TRANS11_k3(0x0));
    }

    //adam setting
    //rtd_outl(0xb800d0b8, 0x0005506b);  // YCbcr444, not repeat pixel, HDMI mode
	// 0430 kist
	rtd_outl(HDMI_SCHCR_reg,
                         HDMI_SCHCR_write_en12(1)|
                         HDMI_SCHCR_color_transform_en(1));
	    //printf("HDMI test start........23\n");
    if((Video_Code==6 || Video_Code==21) && Pixel_Colocr_Format==3) //(480i or 576i) and YCbCr422
    {
        //0xb800d0b8
        rtd_outl(HDMI_SCHCR_reg,
                         HDMI_SCHCR_write_en10(1)|
                         HDMI_SCHCR_422_pixel_repeat(1));
    }
    else
    {
        //0xb800d0b8
        rtd_outl(HDMI_SCHCR_reg,
                         HDMI_SCHCR_write_en10(1)|
                         HDMI_SCHCR_422_pixel_repeat(0));
    }
	 //   printf("HDMI test start........24\n");
    //========================================================================================================
    // TMDS Serializer
    //========================================================================================================
#if OUTPUT_SRC_SELECT_HDMI
        SET_PLL_HDMI(format_idx, Deep_Color, Deep_Depth);
#else
        SET_PLL_MHL(format_idx, pp_en);
#endif
	//    printf("HDMI test start........26\n");
    /* adam setting
    rtd_outl(0xb800d078, 0x00000008);  // enable GCP trnsmission
    rtd_outl(0xb800d078, 0x00000009);  // enable GCP trnsmission (writen enable)
    rtd_outl(0xb800d0a0, 0x21084210);  // setting periodic island packet cycle length
    rtd_outl(0xb800d0b4, 0x00000c66);  // max packet length = 18-1 in vertical blanking, max packet length = 6-1 in horizontal blanking
    */
    //0xb800d078
    rtd_outl(HDMI_GCPCR_reg,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(0));
    //0xb800d078
    rtd_outl(HDMI_GCPCR_reg,
                     HDMI_GCPCR_enablegcp(1)|
                     HDMI_GCPCR_gcp_clearavmute(0)|
                     HDMI_GCPCR_gcp_setavmute(0)|
                     HDMI_GCPCR_write_data(1));
    //0xb800d0a0
    rtd_outl(HDMI_RPCR_reg,
                     HDMI_RPCR_write_en6(1)|HDMI_RPCR_prp5period(0)|
                     HDMI_RPCR_write_en5(1)|HDMI_RPCR_prp4period(0)|
                     HDMI_RPCR_write_en4(1)|HDMI_RPCR_prp3period(0)|
                     HDMI_RPCR_write_en3(1)|HDMI_RPCR_prp2period(0)|
                     HDMI_RPCR_write_en2(0)|HDMI_RPCR_prp1period(0)|
                     HDMI_RPCR_write_en1(1)|HDMI_RPCR_prp0period(0));
    //0xb800d0a4
    rtd_outl(HDMI_RPEN_reg,
                     HDMI_RPEN_enprpkt5(1)|
                     HDMI_RPEN_enprpkt4(1)|
                     HDMI_RPEN_enprpkt3(1)|
                     HDMI_RPEN_enprpkt2(1)| //Metadata package clear
                     HDMI_RPEN_enprpkt1(0)| //Audio InfoFrame package clear by HDMI_audio_set
                     HDMI_RPEN_enprpkt0(1)| //AVI InfoFrame package clear
                     HDMI_RPEN_write_data(0));
	    //printf("HDMI test start........27\n");
    //========================================================================================================
    //adam not setting
    rtd_outl(HDMI_DIPCCR_reg,
             HDMI_DIPCCR_write_en2(1)|HDMI_DIPCCR_vbidipcnt(packet_num_table[format_idx].v_max - 1)|
             HDMI_DIPCCR_write_en1(1)|HDMI_DIPCCR_hbidipcnt(packet_num_table[format_idx].h_max - 1));
    //=====================================================================================================
    // Scheduler
    //=====================================================================================================
#if 1
    //adam not setting
    if(DVI_or_HDMI==0) //DVI mode
    {
        switch(Video_Code)
        {
            case 2: //480p
            case 6: //480i
            case 17: //576p
            case 21: //576i
                //0xb800d0b8
                rtd_outl(HDMI_SCHCR_reg,
                                 HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                                 HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                                 HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(1)|
                                 HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(1)|
                                 HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                                 HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                                 HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(0)| //RGB444
                                 HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                                 HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(0)); //0:DVI mode 1:HDMI mode
                break;
            case 4: //720p60
            case 5: //1080i60
            case 19: //720p50
            case 20: //1080i50
            case 32: //1080p24
            case 31: //1080p50
            case 16: //1080p60
            case 95: //4k2k@30
            case 0:
                //0xb800d0b8
                rtd_outl(HDMI_SCHCR_reg,
                                 HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                                 HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                                 HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(0)|
                                 HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(0)|
                                 HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                                 HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                                 HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(0)| //RGB444
                                 HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                                 HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(0)); //0:DVI mode 1:HDMI mode
                break;
            default:
                break;
        }
    }
    else //HDMI mode
    {
        switch(Video_Code)
        {
        	//20120807 kist
            case 6: //480i
            case 21: //576i
                //0xb800d0b8
                rtd_outl(HDMI_SCHCR_reg,
                                 HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                                 HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                                 HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(1)|
                                 HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(1)|
                                 HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                                 HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                                 HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(Pixel_Colocr_Format)|
                                 HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|//20121220 kist
                                 HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(1)); //0:DVI mode 1:HDMI mode
                break;
            case 2: //480p
            case 17: //576p
                //0xb800d0b8
                rtd_outl(HDMI_SCHCR_reg,
                                 HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                                 HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                                 HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(1)|
                                 HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(1)|
                                 HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                                 HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                                 HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(Pixel_Colocr_Format)|
                                 HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                                 HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(1)); //0:DVI mode 1:HDMI mode
                break;
            case 4: //720p60
            case 5: //1080i60
            case 19: //720p50
            case 20: //1080i50
            case 32: //1080p24
            case 31: //1080p50
            case 16: //1080p60
            case 95: //4k2k@30
                //0xb800d0b8
                rtd_outl(HDMI_SCHCR_reg,
                                 HDMI_SCHCR_write_en9(0)|HDMI_SCHCR_vsyncpolin(0)|
                                 HDMI_SCHCR_write_en8(0)|HDMI_SCHCR_hsyncpolin(0)|
                                 HDMI_SCHCR_write_en7(1)|HDMI_SCHCR_vsyncpolinv(0)|
                                 HDMI_SCHCR_write_en6(1)|HDMI_SCHCR_hsyncpolinv(0)|
                                 HDMI_SCHCR_write_en5(1)|HDMI_SCHCR_pixelencycbcr422(0)|
                                 HDMI_SCHCR_write_en4(1)|HDMI_SCHCR_hdmi_videoxs(0)|
                                 HDMI_SCHCR_write_en3(1)|HDMI_SCHCR_pixelencfmt(Pixel_Colocr_Format)|
                                 HDMI_SCHCR_write_en2(1)|HDMI_SCHCR_pixelrepeat(0)|
                                 HDMI_SCHCR_write_en1(1)|HDMI_SCHCR_hdmi_modesel(1)); //0:DVI mode 1:HDMI mode
                break;
            default:
                break;
        }
    }
#endif

    rtd_outl(HDMI_HDCP_KOWR_reg, HDMI_HDCP_KOWR_hdcprekeykeepoutwin(0x29));

    rtd_outl(HDMI_INTEN_reg,
                     HDMI_INTEN_enriupdint(1)|
                     HDMI_INTEN_enpjupdint(1)|
                     HDMI_INTEN_write_data(0));

    HDMI_gen_avi_infoframe(Video_Code, Pixel_Colocr_Format, xv_YCC);
	 //   printf("HDMI test start........33\n");
    if (En_3D || (format_idx == HDMI_TX_3840_2160P_30HZ))
    {
        if (format_idx == HDMI_TX_3840_2160P_30HZ)
        {
            ext_video = HDMI_TX_EXTENDED_RESOLUTION_4K2K_FORMAT;
            ext_format = HDMI_TX_2160P30_VIC;
        }
        else if (En_3D)
        {
            ext_video = HDMI_TX_EXTENDED_RESOLUTION_3D_FORMAT;
            ext_format = Format_3D << VSIF_3D_FORMAT_BIT;
        }
        HDMI_gen_vendor_Specific_infoframe(ext_video, ext_format);
    }
    if(En_3D) HDMI_gen_vendor_Specific_infoframe(Format_3D);

    if(xv_YCC) HDMI_gen_metadata();

#if !OUTPUT_SRC_SELECT_HDMI // MHL mode

    rtd_outl(HDMI_AS_PHY_reg,
                        HDMI_AS_PHY_pvs_end(0x3fff)|
                        HDMI_AS_PHY_pvs_rst_en(0x1)|
                        HDMI_AS_PHY_rand_rst(0x1)|
                        HDMI_AS_PHY_pvs_start(0x150));
    rtd_outl(HDMI_AS_PHY_reg,
                        HDMI_AS_PHY_pvs_end(0x3fff)|
                        HDMI_AS_PHY_pvs_rst_en(0x0)|
                        HDMI_AS_PHY_rand_rst(0x0)|
                        HDMI_AS_PHY_pvs_start(0x150));
#endif

    rtd_outl(HDMI_CR_reg,
                     HDMI_CR_write_en3(1)|HDMI_CR_tmds_encen(1)| //TMDS Encoder enable
                     HDMI_CR_write_en2(1)|HDMI_CR_enablehdcp(1)| //Fixed a critical case of 480p with HDCP
                     HDMI_CR_write_en1(1)|HDMI_CR_enablehdmi(1)); //HDMI enable

#if !OUTPUT_SRC_SELECT_HDMI // MHL mode

    rtd_outl(HDMI_MHLCTRL_reg,
                     HDMI_MHLCTRL_write_en1(0)|
                     HDMI_MHLCTRL_write_en2(1)|HDMI_MHLCTRL_mhl_pp_mode((UINT32) pp_en)|
                     HDMI_MHLCTRL_write_en3(0)|
                     HDMI_MHLCTRL_write_en4(0)|
                     HDMI_MHLCTRL_write_en5(0)|
                     HDMI_MHLCTRL_write_en6(0));

    rtd_outl(HDMI_MHLCTRL_reg,
                     HDMI_MHLCTRL_write_en1(1)|HDMI_MHLCTRL_mhl_enable(1)|
                     HDMI_MHLCTRL_write_en2(0)|
                     HDMI_MHLCTRL_write_en3(0)|
                     HDMI_MHLCTRL_write_en4(0)|
                     HDMI_MHLCTRL_write_en5(0)|
                     HDMI_MHLCTRL_write_en6(0));

#endif

#if OUTPUT_SRC_SELECT_HDMI
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x3c0000);    //Lane0~3 enable
#else
    rtd_maskl(0xb80001c4, 0xffc3ffff, 0x080000);    //Lane1 enable
#endif

    return;
}
