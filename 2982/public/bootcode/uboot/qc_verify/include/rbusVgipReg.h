/**
* @file rbusVgipReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/27
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_VGIP_REG_H_
#define _RBUS_VGIP_REG_H_

#include "rbusTypes.h"




// VGIP Register Address

#define VGIP_SMOOTH_TOG_CTRL_VADDR                 (0xb8022200)
#define VGIP_SMOOTH_TOG_STATUS_VADDR               (0xb8022204)
#define VGIP_V8_CTRL_VADDR                         (0xb8022208)
#define VGIP_VGIP_GLOBAL_CTRL_VADDR                (0xb802220c)
#define VGIP_VGIP_CHN1_CTRL_VADDR                  (0xb8022210)
#define VGIP_VGIP_CHN1_STATUS_VADDR                (0xb8022214)
#define VGIP_VGIP_CHN1_ACT_HSTA_WIDTH_VADDR        (0xb8022218)
#define VGIP_VGIP_CHN1_ACT_VSTA_LENGTH_VADDR       (0xb802221c)
#define VGIP_VGIP_CHN1_DELAY_VADDR                 (0xb8022220)
#define VGIP_VGIP_CHN1_MISC_VADDR                  (0xb8022224)
#define VGIP_VGIP_CHN1_PTN_H_VI_VADDR              (0xb8022228)
#define VGIP_VGIP_CHN1_PTN0_VADDR                  (0xb802222c)
#define VGIP_VGIP_CHN1_PTN1_VADDR                  (0xb8022230)
#define VGIP_VGIP_CHN1_LC_VADDR                    (0xb8022234)
#define VGIP_ICH1_VGIP_CRC_CTRL_VADDR              (0xb8022238)
#define VGIP_ICH1_VGIP_CRC_RESULT_VADDR            (0xb802223c)
#define VGIP_VGIP_CHN1_WDE_VADDR                   (0xb8022240)
#define VGIP_PR_L_R_ONLY_CTRL_VADDR                (0xb8022250)
#define VGIP_ADC_RAW_DATA_DMA_VADDR                (0xb8022278)
#define VGIP_FRAMEPACKING_CTRL1_VADDR              (0xb802227c)
#define VGIP_FRAMEPACKING_CTRL2_VADDR              (0xb8022280)
#define VGIP_DATA_PATH_SELECT_VADDR                (0xb8022284)
#define VGIP_VGIP_VBISLI_VADDR                     (0xb8022288)
#define VGIP_INT_CTL_VADDR                         (0xb802228c)
#define VGIP_CTS_FIFO_CTL_VADDR                    (0xb8022290)
#define VGIP_DISPI_TEST_SEL_VADDR                  (0xb8022294)
#define VGIP_VGIP_CHN1_3D_RIGHT_ACT_HSTA_WIDTH_VADDR  (0xb8022298)
#define VGIP_VGIP_CHN1_3D_RIGHT_ACT_VSTA_LENGTH_VADDR  (0xb802229c)
#define VGIP_FRAMEPACKING_INTERLACE_CTRL1_VADDR    (0xb80222a8)
#define VGIP_FRAMEPACKING_INTERLACE_CTRL2_VADDR    (0xb80222ac)
#define VGIP_FRAMEPACKING_INTERLACE_CTRL3_VADDR    (0xb80222b0)
#define VGIP_FRAMEPACKING_INTERLACE_CTRL4_VADDR    (0xb80222b4)
#define VGIP_L_R_ACTIVE_ENABLE_CTRL1_VADDR         (0xb80222b8)
#define VGIP_L_R_ACTIVE_ENABLE_CTRL2_VADDR         (0xb80222bc)

#define VGIP_CHN2_VCLK_CTRL_VADDR                  (0xb8022400)
#define VGIP_CHN2_V8_1_CTRL_VADDR                  (0xb8022404)
#define VGIP_CHN2_V8_2_CTRL_VADDR                  (0xb8022408)
#define VGIP_VGIP_CHN2_GLOBAL_CTRL_VADDR           (0xb802240c)
#define VGIP_VGIP_CHN2_CTRL_VADDR                  (0xb8022410)
#define VGIP_VGIP_CHN2_STATUS_VADDR                (0xb8022414)
#define VGIP_VGIP_CHN2_ACT_HSTA_WIDTH_VADDR        (0xb8022418)
#define VGIP_VGIP_CHN2_ACT_VSTA_LENGTH_VADDR       (0xb802241c)
#define VGIP_VGIP_CHN2_DELAY_VADDR                 (0xb8022420)
#define VGIP_VGIP_CHN2_MISC_VADDR                  (0xb8022424)
#define VGIP_VGIP_CHN2_PTN_H_VI_VADDR              (0xb8022428)
#define VGIP_VGIP_CHN2_PTN0_VADDR                  (0xb802242c)
#define VGIP_VGIP_CHN2_PTN1_VADDR                  (0xb8022430)
#define VGIP_VGIP_CHN2_LC_VADDR                    (0xb8022434)
#define VGIP_ICH2_VGIP_CRC_CTRL_VADDR              (0xb8022438)
#define VGIP_ICH2_VGIP_CRC_RESULT_VADDR            (0xb802243c)
#define VGIP_VGIP_CHN2_WDE_VADDR                   (0xb8022440)
#define VGIP_CHN2_PR_L_R_ONLY_CTRL_VADDR           (0xb8022450)
#define VGIP_CHN2_ADC_RAW_DATA_DMA_VADDR           (0xb8022478)
#define VGIP_CHN2_FRAMEPACKING_CTRL1_VADDR         (0xb802247c)
#define VGIP_CHN2_FRAMEPACKING_CTRL2_VADDR         (0xb8022480)
#define VGIP_CHN2_CTS_FIFO_CTL_VADDR               (0xb8022490)
#define VGIP_CHN2_DISPI_TEST_SEL_VADDR             (0xb8022494)
#define VGIP_VGIP_CHN2_3D_RIGHT_ACT_HSTA_WIDTH_VADDR  (0xb8022498)
#define VGIP_VGIP_CHN2_3D_RIGHT_ACT_VSTA_LENGTH_VADDR  (0xb802249c)
#define VGIP_CHN2_FRAMEPACKING_INTERLACE_CTRL1_VADDR  (0xb80224a8)
#define VGIP_CHN2_FRAMEPACKING_INTERLACE_CTRL2_VADDR  (0xb80224ac)
#define VGIP_CHN2_FRAMEPACKING_INTERLACE_CTRL3_VADDR  (0xb80224b0)
#define VGIP_CHN2_FRAMEPACKING_INTERLACE_CTRL4_VADDR  (0xb80224b4)
#define VGIP_CHN2_L_R_ACTIVE_ENABLE_CTRL1_VADDR    (0xb80224b8)
#define VGIP_CHN2_L_R_ACTIVE_ENABLE_CTRL2_VADDR    (0xb80224bc)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======VGIP register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  sub_imd_smooth_toggle_clk_time2switch_en:1;
        RBus_UInt32  sub_imd_smooth_toggle_style:2;
        RBus_UInt32  sub_imd_smooth_toggle_apply:1;
        RBus_UInt32  main_imd_smooth_toggle_clk_time2switch_en:1;
        RBus_UInt32  main_imd_smooth_toggle_style:2;
        RBus_UInt32  main_imd_smooth_toggle_apply:1;
    };
}smooth_tog_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vo2_reg_is_db:1;
        RBus_UInt32  sub_vgip_reg_is_db:1;
        RBus_UInt32  sub_uzd_reg_is_db:1;
        RBus_UInt32  vo1_reg_is_db:1;
        RBus_UInt32  main_vgip_reg_is_db:1;
        RBus_UInt32  di_reg_is_db:1;
        RBus_UInt32  i_edge_smooth_reg_is_db:1;
        RBus_UInt32  main_uzd_reg_is_db:1;
    };
}smooth_tog_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  v8_dummy:8;
        RBus_UInt32  dummy18022208_7_2:6;
        RBus_UInt32  smfit_vs_delay_sel:1;
        RBus_UInt32  ch1_select_duplicate_lsb:1;
    };
}v8_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_l_flag_delay_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  auto_l_flag_delay_num:13;
        RBus_UInt32  l_flag_delay_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  l_flag_delay_num:13;
    };
}vgip_global_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_ivrun:1;
        RBus_UInt32  ch1_in_sel:3;
        RBus_UInt32  ch1_random_en:1;
        RBus_UInt32  ch1_fdrop_en:1;
        RBus_UInt32  ch1_vact_end_ie:1;
        RBus_UInt32  ch1_vact_start_ie:1;
        RBus_UInt32  ch1_field_hs_inv:1;
        RBus_UInt32  ch1_odd_vd_inv:1;
        RBus_UInt32  ch1_odd_vd_en:1;
        RBus_UInt32  ch1_3dleft_inv:1;
        RBus_UInt32  ch1_3dleft_sync_edge:1;
        RBus_UInt32  ch1_odd_inv:1;
        RBus_UInt32  ch1_odd_sync_edge:1;
        RBus_UInt32  ch1_odd_det_en:1;
        RBus_UInt32  ch1_hpact_is_hact:1;
        RBus_UInt32  ch1_fcap_str_odd:1;
        RBus_UInt32  ch1_mask_den_inv:1;
        RBus_UInt32  ch1_mask_den_1l:1;
        RBus_UInt32  ch1_3d_mode_en:1;
        RBus_UInt32  ch1_safe_odd_inv:1;
        RBus_UInt32  ch1_force_tog:1;
        RBus_UInt32  ch1_safe_mode:1;
        RBus_UInt32  ch1_3d_right_act_en:1;
        RBus_UInt32  ch1_hs_syncedge:1;
        RBus_UInt32  ch1_vs_syncedge:1;
        RBus_UInt32  ch1_vs_by_hs_en_n:1;
        RBus_UInt32  ch1_vs_inv:1;
        RBus_UInt32  ch1_hs_inv:1;
        RBus_UInt32  ch1_digital_mode:1;
        RBus_UInt32  ch1_in_clk_en:1;
    };
}vgip_chn1_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  ch1_vs_end:1;
        RBus_UInt32  ch1_vs_start:1;
        RBus_UInt32  ch1_vact_end:1;
        RBus_UInt32  ch1_vact_start:1;
        RBus_UInt32  dummy18022214_23_18:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  ch1_vlc_status:1;
        RBus_UInt32  ch1_rl_err:1;
        RBus_UInt32  ch1_vs_err:1;
        RBus_UInt32  ch1_hs_err:1;
        RBus_UInt32  ch1_field_err:1;
        RBus_UInt32  ch1_rl_tog:1;
        RBus_UInt32  ch1_l_flag_pol:1;
        RBus_UInt32  ch1_vs_tog:1;
        RBus_UInt32  ch1_hs_tog:1;
        RBus_UInt32  ch1_field_pol:1;
        RBus_UInt32  ch1_field_tog:1;
        RBus_UInt32  ch1_field_vs_lsb:2;
        RBus_UInt32  ch1_more_1line_field:1;
        RBus_UInt32  ch1_bounce_status_2:1;
        RBus_UInt32  ch1_bounce_status_1:1;
        RBus_UInt32  ch1_bounce_status_0:1;
    };
}vgip_chn1_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_db_rdy:1;
        RBus_UInt32  ch1_db_en:1;
        RBus_UInt32  ch1_ih_act_sta:14;
        RBus_UInt32  ch1_db_read_sel:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch1_ih_act_wid:14;
    };
}vgip_chn1_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch1_iv_act_sta:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch1_iv_act_len:13;
    };
}vgip_chn1_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch1_ihs_dly:14;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch1_ivs_dly:13;
    };
}vgip_chn1_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_de_mask_en:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  ch1_hporch_num_sel:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  l_flag_force_tog:1;
        RBus_UInt32  ch1_hporch_num:13;
        RBus_UInt32  ch1_auto_ihs_dly:2;
        RBus_UInt32  ch1_auto_ivs_dly:2;
        RBus_UInt32  ch1_hdly_one:1;
        RBus_UInt32  ch1_v1_v2_swap:1;
        RBus_UInt32  ch1_v2_v3_swap:1;
        RBus_UInt32  ch1_v1_v3_swap:1;
    };
}vgip_chn1_misc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_captst_en:1;
        RBus_UInt32  ch1_captst_mode:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch1_vcaptst_num:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch1_hcaptst_num:14;
    };
}vgip_chn1_ptn_h_vi_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  ch1_captst_r_data:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch1_captst_g_data:12;
    };
}vgip_chn1_ptn0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch1_hporch_num_sel:14;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch1_captst_b_data:12;
    };
}vgip_chn1_ptn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_vlcen:1;
        RBus_UInt32  ch1_vlc_mode:1;
        RBus_UInt32  ch1_vlc_ie:1;
        RBus_UInt32  den_crc_sel:1;
        RBus_UInt32  res1:4;
        RBus_UInt32  ch1_line_cnt:12;
        RBus_UInt32  ch1_vln:12;
    };
}vgip_chn1_lc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  ch1_crc_region:1;
        RBus_UInt32  ch1_crc_ctrl_in:1;
        RBus_UInt32  ch1_crc_field_edge_sel:1;
        RBus_UInt32  ch1_crc_field:1;
        RBus_UInt32  ch1_crc_conti:1;
        RBus_UInt32  ch1_crc_start:1;
    };
}ich1_vgip_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_crc_result:32;
    };
}ich1_vgip_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_wd_to_main:1;
        RBus_UInt32  ch1_wd_to_sub:1;
        RBus_UInt32  dummy18022240_29_19:11;
        RBus_UInt32  ch1_vs_err_wde:1;
        RBus_UInt32  ch1_hs_err_wde:1;
        RBus_UInt32  ch1_field_err_wde:1;
        RBus_UInt32  ch1_rl_err_wde:1;
        RBus_UInt32  dummy18022240_14_4:11;
        RBus_UInt32  ch1_rl_err_ie:1;
        RBus_UInt32  ch1_vs_err_ie:1;
        RBus_UInt32  ch1_hs_err_ie:1;
        RBus_UInt32  ch1_field_err_ie:1;
    };
}vgip_chn1_wde_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  ch1_pr_l_r_only_mask_hs:1;
        RBus_UInt32  ch1_pr_l_r_only_rm_den:1;
        RBus_UInt32  ch1_pr_l_r_only_en:1;
    };
}pr_l_r_only_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_test_dma_count:28;
        RBus_UInt32  res1:1;
        RBus_UInt32  force_den:1;
        RBus_UInt32  force_vsync:1;
        RBus_UInt32  adc_test_dma_mode:1;
    };
}adc_raw_data_dma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vs_width:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  frame_packing_en:1;
        RBus_UInt32  vs_position:13;
    };
}framepacking_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  den_mask_start:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  den_mask_end:13;
    };
}framepacking_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  uzd1_in_sel:2;
        RBus_UInt32  uzd2_in_sel:2;
        RBus_UInt32  dummy18022284_7:1;
        RBus_UInt32  fsync_ch_sel:1;
        RBus_UInt32  adc_ch_sel:2;
        RBus_UInt32  xcdi_clk_en:1;
        RBus_UInt32  dummy18022284_2_1:2;
        RBus_UInt32  xcdi_in_sel:1;
    };
}data_path_select_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  vbisli_in_sel:2;
        RBus_UInt32  vbisli_ivs_dly:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  vbisli_ihs_dly:14;
    };
}vgip_vbisli_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  onms3_int_ie:1;
        RBus_UInt32  offms_int_ie:1;
        RBus_UInt32  onms2_int_ie:1;
        RBus_UInt32  onms1_int_ie:1;
        RBus_UInt32  hist_ch1_int_ie:1;
        RBus_UInt32  hist_ch2_int_ie:1;
        RBus_UInt32  vgip_int_ie:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  dispi_int_ie:1;
    };
}int_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  dummy_ctsfifo_sdnr:1;
        RBus_UInt32  force_ctsfifo_rstn_sdnr:1;
        RBus_UInt32  en_ctsfifo_vsrst_sdnr:1;
        RBus_UInt32  en_ctsfifo_bypass_sdnr:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  dummy_ctsfifo_vgip:1;
        RBus_UInt32  force_ctsfifo_rstn_vgip:1;
        RBus_UInt32  en_ctsfifo_vsrst_vgip:1;
        RBus_UInt32  en_ctsfifo_bypass_vgip:1;
    };
}cts_fifo_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  disp_testpinsel:6;
    };
}dispi_test_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch1_3d_right_ih_act_sta:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch1_3d_right_ih_act_wid:14;
    };
}vgip_chn1_3d_right_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch1_3d_right_iv_act_sta:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch1_3d_right_iv_act_len:13;
    };
}vgip_chn1_3d_right_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vs_width_r_odd:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  frame_packing_field_en:1;
        RBus_UInt32  vs_position_r_odd:13;
    };
}framepacking_interlace_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  den_mask_start_r_odd:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  den_mask_end_r_odd:13;
    };
}framepacking_interlace_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vs_width_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  vs_position_r_even:13;
    };
}framepacking_interlace_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  den_mask_start_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  den_mask_end_r_even:13;
    };
}framepacking_interlace_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  end_l:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  sta_l:14;
    };
}l_r_active_enable_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_r_act_en:1;
        RBus_UInt32  h_v_mode:1;
        RBus_UInt32  end_r:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  sta_r:14;
    };
}l_r_active_enable_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ch2_v8_dummy:8;
    };
}ch2_vclk_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dummy18022404_7_0:8;
    };
}ch2_V8_1_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  ch2_select_duplicate_lsb:1;
    };
}ch2_V8_2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_auto_l_flag_delay_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_auto_l_flag_delay_num:13;
        RBus_UInt32  ch2_l_flag_delay_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_l_flag_delay_num:13;
    };
}vgip_chn2_global_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_ivrun:1;
        RBus_UInt32  ch2_in_sel:3;
        RBus_UInt32  ch2_random_en:1;
        RBus_UInt32  ch2_fdrop_en:1;
        RBus_UInt32  ch2_vact_end_ie:1;
        RBus_UInt32  ch2_vact_start_ie:1;
        RBus_UInt32  ch2_field_hs_inv:1;
        RBus_UInt32  ch2_odd_vd_inv:1;
        RBus_UInt32  ch2_odd_vd_en:1;
        RBus_UInt32  ch2_3dleft_inv:1;
        RBus_UInt32  ch2_3dleft_sync_edge:1;
        RBus_UInt32  ch2_odd_inv:1;
        RBus_UInt32  ch2_odd_sync_edge:1;
        RBus_UInt32  ch2_odd_det_en:1;
        RBus_UInt32  ch2_hpact_is_hact:1;
        RBus_UInt32  ch2_fcap_str_odd:1;
        RBus_UInt32  ch2_mask_den_inv:1;
        RBus_UInt32  ch2_mask_den_1l:1;
        RBus_UInt32  ch2_3d_mode_en:1;
        RBus_UInt32  ch2_safe_odd_inv:1;
        RBus_UInt32  ch2_force_tog:1;
        RBus_UInt32  ch2_safe_mode:1;
        RBus_UInt32  ch2_3d_right_act_en:1;
        RBus_UInt32  ch2_hs_syncedge:1;
        RBus_UInt32  ch2_vs_syncedge:1;
        RBus_UInt32  ch2_vs_by_hs_en_n:1;
        RBus_UInt32  ch2_vs_inv:1;
        RBus_UInt32  ch2_hs_inv:1;
        RBus_UInt32  ch2_digital_mode:1;
        RBus_UInt32  ch2_in_clk_en:1;
    };
}vgip_chn2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  ch2_vs_end:1;
        RBus_UInt32  ch2_vs_start:1;
        RBus_UInt32  ch2_vact_end:1;
        RBus_UInt32  ch2_vact_start:1;
        RBus_UInt32  dummy18022414_23_18:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  ch2_vlc_status:1;
        RBus_UInt32  ch2_rl_err:1;
        RBus_UInt32  ch2_vs_err:1;
        RBus_UInt32  ch2_hs_err:1;
        RBus_UInt32  ch2_field_err:1;
        RBus_UInt32  ch2_rl_tog:1;
        RBus_UInt32  ch2_l_flag_pol:1;
        RBus_UInt32  ch2_vs_tog:1;
        RBus_UInt32  ch2_hs_tog:1;
        RBus_UInt32  ch2_field_pol:1;
        RBus_UInt32  ch2_field_tog:1;
        RBus_UInt32  ch2_field_vs_lsb:2;
        RBus_UInt32  ch2_more_1line_field:1;
        RBus_UInt32  ch2_bounce_status_2:1;
        RBus_UInt32  ch2_bounce_status_1:1;
        RBus_UInt32  ch2_bounce_status_0:1;
    };
}vgip_chn2_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_db_rdy:1;
        RBus_UInt32  ch2_db_en:1;
        RBus_UInt32  ch2_ih_act_sta:14;
        RBus_UInt32  ch2_db_read_sel:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch2_ih_act_wid:14;
    };
}vgip_chn2_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_iv_act_sta:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_iv_act_len:13;
    };
}vgip_chn2_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_ihs_dly:14;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_ivs_dly:13;
    };
}vgip_chn2_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_de_mask_en:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  ch2_hporch_num_sel:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_l_flag_force_tog:1;
        RBus_UInt32  ch2_hporch_num:13;
        RBus_UInt32  ch2_auto_ihs_dly:2;
        RBus_UInt32  ch2_auto_ivs_dly:2;
        RBus_UInt32  ch2_hdly_one:1;
        RBus_UInt32  ch2_v1_v2_swap:1;
        RBus_UInt32  ch2_v2_v3_swap:1;
        RBus_UInt32  ch2_v1_v3_swap:1;
    };
}vgip_chn2_misc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_captst_en:1;
        RBus_UInt32  ch2_captst_mode:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch2_vcaptst_num:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_hcaptst_num:14;
    };
}vgip_chn2_ptn_h_vi_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  ch2_captst_r_data:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch2_captst_g_data:12;
    };
}vgip_chn2_ptn0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_hporch_num_sel:14;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch2_captst_b_data:12;
    };
}vgip_chn2_ptn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_vlcen:1;
        RBus_UInt32  ch2_vlc_mode:1;
        RBus_UInt32  ch2_vlc_ie:1;
        RBus_UInt32  ch2_den_crc_sel:1;
        RBus_UInt32  res1:4;
        RBus_UInt32  ch2_line_cnt:12;
        RBus_UInt32  ch2_vln:12;
    };
}vgip_chn2_lc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  ch2_crc_region:1;
        RBus_UInt32  ch2_crc_ctrl_in:1;
        RBus_UInt32  ch2_crc_field_edge_sel:1;
        RBus_UInt32  ch2_crc_field:1;
        RBus_UInt32  ch2_crc_conti:1;
        RBus_UInt32  ch2_crc_start:1;
    };
}ich2_vgip_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_crc_result:32;
    };
}ich2_vgip_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_wd_to_main:1;
        RBus_UInt32  ch2_wd_to_sub:1;
        RBus_UInt32  dummy18022440_29_19:11;
        RBus_UInt32  ch2_vs_err_wde:1;
        RBus_UInt32  ch2_hs_err_wde:1;
        RBus_UInt32  ch2_field_err_wde:1;
        RBus_UInt32  ch2_rl_err_wde:1;
        RBus_UInt32  dummy18022440_14_4:11;
        RBus_UInt32  ch2_rl_err_ie:1;
        RBus_UInt32  ch2_vs_err_ie:1;
        RBus_UInt32  ch2_hs_err_ie:1;
        RBus_UInt32  ch2_field_err_ie:1;
    };
}vgip_chn2_wde_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  ch2_pr_l_r_only_mask_hs:1;
        RBus_UInt32  ch2_pr_l_r_only_rm_den:1;
        RBus_UInt32  ch2_pr_l_r_only_en:1;
    };
}ch2_pr_l_r_only_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_adc_test_dma_count:28;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch2_force_den:1;
        RBus_UInt32  ch2_force_vsync:1;
        RBus_UInt32  ch2_adc_test_dma_mode:1;
    };
}ch2_adc_raw_data_dma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_vs_width:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_frame_packing_en:1;
        RBus_UInt32  ch2_vs_position:13;
    };
}ch2_framepacking_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_den_mask_start:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_den_mask_end:13;
    };
}ch2_framepacking_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  ch2_dummy_ctsfifo_sdnr:1;
        RBus_UInt32  ch2_force_ctsfifo_rstn_sdnr:1;
        RBus_UInt32  ch2_en_ctsfifo_vsrst_sdnr:1;
        RBus_UInt32  ch2_en_ctsfifo_bypass_sdnr:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch2_dummy_ctsfifo_vgip:1;
        RBus_UInt32  ch2_force_ctsfifo_rstn_vgip:1;
        RBus_UInt32  ch2_en_ctsfifo_vsrst_vgip:1;
        RBus_UInt32  ch2_en_ctsfifo_bypass_vgip:1;
    };
}ch2_cts_fifo_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ch2_dispi_test_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_3d_right_ih_act_sta:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_3d_right_ih_act_wid:14;
    };
}vgip_chn2_3d_right_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_3d_right_iv_act_sta:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_3d_right_iv_act_len:13;
    };
}vgip_chn2_3d_right_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_vs_width_r_odd:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_frame_packing_field_en:1;
        RBus_UInt32  ch2_vs_position_r_odd:13;
    };
}ch2_framepacking_interlace_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_den_mask_start_r_odd:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_den_mask_end_r_odd:13;
    };
}ch2_framepacking_interlace_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_vs_width_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_vs_position_r_even:13;
    };
}ch2_framepacking_interlace_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ch2_den_mask_start_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_den_mask_end_r_even:13;
    };
}ch2_framepacking_interlace_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_end_l:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_sta_l:14;
    };
}ch2_l_r_active_enable_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_l_r_act_en:1;
        RBus_UInt32  ch2_h_v_mode:1;
        RBus_UInt32  ch2_end_r:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_sta_r:14;
    };
}ch2_l_r_active_enable_ctrl2_RBUS;





#else //apply LITTLE_ENDIAN


//======VGIP register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  main_imd_smooth_toggle_apply:1;
        RBus_UInt32  main_imd_smooth_toggle_style:2;
        RBus_UInt32  main_imd_smooth_toggle_clk_time2switch_en:1;
        RBus_UInt32  sub_imd_smooth_toggle_apply:1;
        RBus_UInt32  sub_imd_smooth_toggle_style:2;
        RBus_UInt32  sub_imd_smooth_toggle_clk_time2switch_en:1;
        RBus_UInt32  res1:24;
    };
}smooth_tog_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  main_uzd_reg_is_db:1;
        RBus_UInt32  i_edge_smooth_reg_is_db:1;
        RBus_UInt32  di_reg_is_db:1;
        RBus_UInt32  main_vgip_reg_is_db:1;
        RBus_UInt32  vo1_reg_is_db:1;
        RBus_UInt32  sub_uzd_reg_is_db:1;
        RBus_UInt32  sub_vgip_reg_is_db:1;
        RBus_UInt32  vo2_reg_is_db:1;
        RBus_UInt32  res1:24;
    };
}smooth_tog_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_select_duplicate_lsb:1;
        RBus_UInt32  smfit_vs_delay_sel:1;
        RBus_UInt32  dummy18022208_7_2:6;
        RBus_UInt32  v8_dummy:8;
        RBus_UInt32  res1:16;
    };
}v8_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_flag_delay_num:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  l_flag_delay_en:1;
        RBus_UInt32  auto_l_flag_delay_num:13;
        RBus_UInt32  res1:2;
        RBus_UInt32  auto_l_flag_delay_en:1;
    };
}vgip_global_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_in_clk_en:1;
        RBus_UInt32  ch1_digital_mode:1;
        RBus_UInt32  ch1_hs_inv:1;
        RBus_UInt32  ch1_vs_inv:1;
        RBus_UInt32  ch1_vs_by_hs_en_n:1;
        RBus_UInt32  ch1_vs_syncedge:1;
        RBus_UInt32  ch1_hs_syncedge:1;
        RBus_UInt32  ch1_3d_right_act_en:1;
        RBus_UInt32  ch1_safe_mode:1;
        RBus_UInt32  ch1_force_tog:1;
        RBus_UInt32  ch1_safe_odd_inv:1;
        RBus_UInt32  ch1_3d_mode_en:1;
        RBus_UInt32  ch1_mask_den_1l:1;
        RBus_UInt32  ch1_mask_den_inv:1;
        RBus_UInt32  ch1_fcap_str_odd:1;
        RBus_UInt32  ch1_hpact_is_hact:1;
        RBus_UInt32  ch1_odd_det_en:1;
        RBus_UInt32  ch1_odd_sync_edge:1;
        RBus_UInt32  ch1_odd_inv:1;
        RBus_UInt32  ch1_3dleft_sync_edge:1;
        RBus_UInt32  ch1_3dleft_inv:1;
        RBus_UInt32  ch1_odd_vd_en:1;
        RBus_UInt32  ch1_odd_vd_inv:1;
        RBus_UInt32  ch1_field_hs_inv:1;
        RBus_UInt32  ch1_vact_start_ie:1;
        RBus_UInt32  ch1_vact_end_ie:1;
        RBus_UInt32  ch1_fdrop_en:1;
        RBus_UInt32  ch1_random_en:1;
        RBus_UInt32  ch1_in_sel:3;
        RBus_UInt32  ch1_ivrun:1;
    };
}vgip_chn1_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_bounce_status_0:1;
        RBus_UInt32  ch1_bounce_status_1:1;
        RBus_UInt32  ch1_bounce_status_2:1;
        RBus_UInt32  ch1_more_1line_field:1;
        RBus_UInt32  ch1_field_vs_lsb:2;
        RBus_UInt32  ch1_field_tog:1;
        RBus_UInt32  ch1_field_pol:1;
        RBus_UInt32  ch1_hs_tog:1;
        RBus_UInt32  ch1_vs_tog:1;
        RBus_UInt32  ch1_l_flag_pol:1;
        RBus_UInt32  ch1_rl_tog:1;
        RBus_UInt32  ch1_field_err:1;
        RBus_UInt32  ch1_hs_err:1;
        RBus_UInt32  ch1_vs_err:1;
        RBus_UInt32  ch1_rl_err:1;
        RBus_UInt32  ch1_vlc_status:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dummy18022214_23_18:6;
        RBus_UInt32  ch1_vact_start:1;
        RBus_UInt32  ch1_vact_end:1;
        RBus_UInt32  ch1_vs_start:1;
        RBus_UInt32  ch1_vs_end:1;
        RBus_UInt32  res1:4;
    };
}vgip_chn1_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_ih_act_wid:14;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch1_db_read_sel:1;
        RBus_UInt32  ch1_ih_act_sta:14;
        RBus_UInt32  ch1_db_en:1;
        RBus_UInt32  ch1_db_rdy:1;
    };
}vgip_chn1_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_iv_act_len:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch1_iv_act_sta:13;
        RBus_UInt32  res1:3;
    };
}vgip_chn1_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_ivs_dly:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch1_ihs_dly:14;
        RBus_UInt32  res1:2;
    };
}vgip_chn1_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_v1_v3_swap:1;
        RBus_UInt32  ch1_v2_v3_swap:1;
        RBus_UInt32  ch1_v1_v2_swap:1;
        RBus_UInt32  ch1_hdly_one:1;
        RBus_UInt32  ch1_auto_ivs_dly:2;
        RBus_UInt32  ch1_auto_ihs_dly:2;
        RBus_UInt32  ch1_hporch_num:13;
        RBus_UInt32  l_flag_force_tog:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch1_hporch_num_sel:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  ch1_de_mask_en:1;
    };
}vgip_chn1_misc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hcaptst_num:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch1_vcaptst_num:13;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch1_captst_mode:1;
        RBus_UInt32  ch1_captst_en:1;
    };
}vgip_chn1_ptn_h_vi_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_captst_g_data:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch1_captst_r_data:12;
        RBus_UInt32  res1:4;
    };
}vgip_chn1_ptn0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_captst_b_data:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch1_hporch_num_sel:14;
        RBus_UInt32  res1:2;
    };
}vgip_chn1_ptn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_vln:12;
        RBus_UInt32  ch1_line_cnt:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  den_crc_sel:1;
        RBus_UInt32  ch1_vlc_ie:1;
        RBus_UInt32  ch1_vlc_mode:1;
        RBus_UInt32  ch1_vlcen:1;
    };
}vgip_chn1_lc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_crc_start:1;
        RBus_UInt32  ch1_crc_conti:1;
        RBus_UInt32  ch1_crc_field:1;
        RBus_UInt32  ch1_crc_field_edge_sel:1;
        RBus_UInt32  ch1_crc_ctrl_in:1;
        RBus_UInt32  ch1_crc_region:1;
        RBus_UInt32  res1:26;
    };
}ich1_vgip_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_crc_result:32;
    };
}ich1_vgip_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_field_err_ie:1;
        RBus_UInt32  ch1_hs_err_ie:1;
        RBus_UInt32  ch1_vs_err_ie:1;
        RBus_UInt32  ch1_rl_err_ie:1;
        RBus_UInt32  dummy18022240_14_4:11;
        RBus_UInt32  ch1_rl_err_wde:1;
        RBus_UInt32  ch1_field_err_wde:1;
        RBus_UInt32  ch1_hs_err_wde:1;
        RBus_UInt32  ch1_vs_err_wde:1;
        RBus_UInt32  dummy18022240_29_19:11;
        RBus_UInt32  ch1_wd_to_sub:1;
        RBus_UInt32  ch1_wd_to_main:1;
    };
}vgip_chn1_wde_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_pr_l_r_only_en:1;
        RBus_UInt32  ch1_pr_l_r_only_rm_den:1;
        RBus_UInt32  ch1_pr_l_r_only_mask_hs:1;
        RBus_UInt32  res1:29;
    };
}pr_l_r_only_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_test_dma_mode:1;
        RBus_UInt32  force_vsync:1;
        RBus_UInt32  force_den:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  adc_test_dma_count:28;
    };
}adc_raw_data_dma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vs_position:13;
        RBus_UInt32  frame_packing_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  vs_width:13;
        RBus_UInt32  res1:3;
    };
}framepacking_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  den_mask_end:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  den_mask_start:13;
        RBus_UInt32  res1:3;
    };
}framepacking_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  xcdi_in_sel:1;
        RBus_UInt32  dummy18022284_2_1:2;
        RBus_UInt32  xcdi_clk_en:1;
        RBus_UInt32  adc_ch_sel:2;
        RBus_UInt32  fsync_ch_sel:1;
        RBus_UInt32  dummy18022284_7:1;
        RBus_UInt32  uzd2_in_sel:2;
        RBus_UInt32  uzd1_in_sel:2;
        RBus_UInt32  res1:20;
    };
}data_path_select_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbisli_ihs_dly:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  vbisli_ivs_dly:13;
        RBus_UInt32  vbisli_in_sel:2;
        RBus_UInt32  res1:1;
    };
}vgip_vbisli_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dispi_int_ie:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  vgip_int_ie:1;
        RBus_UInt32  hist_ch2_int_ie:1;
        RBus_UInt32  hist_ch1_int_ie:1;
        RBus_UInt32  onms1_int_ie:1;
        RBus_UInt32  onms2_int_ie:1;
        RBus_UInt32  offms_int_ie:1;
        RBus_UInt32  onms3_int_ie:1;
        RBus_UInt32  res1:22;
    };
}int_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  en_ctsfifo_bypass_vgip:1;
        RBus_UInt32  en_ctsfifo_vsrst_vgip:1;
        RBus_UInt32  force_ctsfifo_rstn_vgip:1;
        RBus_UInt32  dummy_ctsfifo_vgip:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  en_ctsfifo_bypass_sdnr:1;
        RBus_UInt32  en_ctsfifo_vsrst_sdnr:1;
        RBus_UInt32  force_ctsfifo_rstn_sdnr:1;
        RBus_UInt32  dummy_ctsfifo_sdnr:1;
        RBus_UInt32  res1:20;
    };
}cts_fifo_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  disp_testpinsel:6;
        RBus_UInt32  res1:26;
    };
}dispi_test_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_3d_right_ih_act_wid:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch1_3d_right_ih_act_sta:14;
        RBus_UInt32  res1:2;
    };
}vgip_chn1_3d_right_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_3d_right_iv_act_len:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch1_3d_right_iv_act_sta:13;
        RBus_UInt32  res1:3;
    };
}vgip_chn1_3d_right_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vs_position_r_odd:13;
        RBus_UInt32  frame_packing_field_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  vs_width_r_odd:13;
        RBus_UInt32  res1:3;
    };
}framepacking_interlace_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  den_mask_end_r_odd:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  den_mask_start_r_odd:13;
        RBus_UInt32  res1:3;
    };
}framepacking_interlace_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vs_position_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  vs_width_r_even:13;
        RBus_UInt32  res1:3;
    };
}framepacking_interlace_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  den_mask_end_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  den_mask_start_r_even:13;
        RBus_UInt32  res1:3;
    };
}framepacking_interlace_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sta_l:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  end_l:14;
        RBus_UInt32  res1:2;
    };
}l_r_active_enable_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sta_r:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  end_r:14;
        RBus_UInt32  h_v_mode:1;
        RBus_UInt32  l_r_act_en:1;
    };
}l_r_active_enable_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_v8_dummy:8;
        RBus_UInt32  res1:24;
    };
}ch2_vclk_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18022404_7_0:8;
        RBus_UInt32  res1:24;
    };
}ch2_V8_1_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_select_duplicate_lsb:1;
        RBus_UInt32  res1:31;
    };
}ch2_V8_2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_l_flag_delay_num:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_l_flag_delay_en:1;
        RBus_UInt32  ch2_auto_l_flag_delay_num:13;
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_auto_l_flag_delay_en:1;
    };
}vgip_chn2_global_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_in_clk_en:1;
        RBus_UInt32  ch2_digital_mode:1;
        RBus_UInt32  ch2_hs_inv:1;
        RBus_UInt32  ch2_vs_inv:1;
        RBus_UInt32  ch2_vs_by_hs_en_n:1;
        RBus_UInt32  ch2_vs_syncedge:1;
        RBus_UInt32  ch2_hs_syncedge:1;
        RBus_UInt32  ch2_3d_right_act_en:1;
        RBus_UInt32  ch2_safe_mode:1;
        RBus_UInt32  ch2_force_tog:1;
        RBus_UInt32  ch2_safe_odd_inv:1;
        RBus_UInt32  ch2_3d_mode_en:1;
        RBus_UInt32  ch2_mask_den_1l:1;
        RBus_UInt32  ch2_mask_den_inv:1;
        RBus_UInt32  ch2_fcap_str_odd:1;
        RBus_UInt32  ch2_hpact_is_hact:1;
        RBus_UInt32  ch2_odd_det_en:1;
        RBus_UInt32  ch2_odd_sync_edge:1;
        RBus_UInt32  ch2_odd_inv:1;
        RBus_UInt32  ch2_3dleft_sync_edge:1;
        RBus_UInt32  ch2_3dleft_inv:1;
        RBus_UInt32  ch2_odd_vd_en:1;
        RBus_UInt32  ch2_odd_vd_inv:1;
        RBus_UInt32  ch2_field_hs_inv:1;
        RBus_UInt32  ch2_vact_start_ie:1;
        RBus_UInt32  ch2_vact_end_ie:1;
        RBus_UInt32  ch2_fdrop_en:1;
        RBus_UInt32  ch2_random_en:1;
        RBus_UInt32  ch2_in_sel:3;
        RBus_UInt32  ch2_ivrun:1;
    };
}vgip_chn2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_bounce_status_0:1;
        RBus_UInt32  ch2_bounce_status_1:1;
        RBus_UInt32  ch2_bounce_status_2:1;
        RBus_UInt32  ch2_more_1line_field:1;
        RBus_UInt32  ch2_field_vs_lsb:2;
        RBus_UInt32  ch2_field_tog:1;
        RBus_UInt32  ch2_field_pol:1;
        RBus_UInt32  ch2_hs_tog:1;
        RBus_UInt32  ch2_vs_tog:1;
        RBus_UInt32  ch2_l_flag_pol:1;
        RBus_UInt32  ch2_rl_tog:1;
        RBus_UInt32  ch2_field_err:1;
        RBus_UInt32  ch2_hs_err:1;
        RBus_UInt32  ch2_vs_err:1;
        RBus_UInt32  ch2_rl_err:1;
        RBus_UInt32  ch2_vlc_status:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dummy18022414_23_18:6;
        RBus_UInt32  ch2_vact_start:1;
        RBus_UInt32  ch2_vact_end:1;
        RBus_UInt32  ch2_vs_start:1;
        RBus_UInt32  ch2_vs_end:1;
        RBus_UInt32  res1:4;
    };
}vgip_chn2_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_ih_act_wid:14;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch2_db_read_sel:1;
        RBus_UInt32  ch2_ih_act_sta:14;
        RBus_UInt32  ch2_db_en:1;
        RBus_UInt32  ch2_db_rdy:1;
    };
}vgip_chn2_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_iv_act_len:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_iv_act_sta:13;
        RBus_UInt32  res1:3;
    };
}vgip_chn2_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_ivs_dly:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_ihs_dly:14;
        RBus_UInt32  res1:2;
    };
}vgip_chn2_delay_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_v1_v3_swap:1;
        RBus_UInt32  ch2_v2_v3_swap:1;
        RBus_UInt32  ch2_v1_v2_swap:1;
        RBus_UInt32  ch2_hdly_one:1;
        RBus_UInt32  ch2_auto_ivs_dly:2;
        RBus_UInt32  ch2_auto_ihs_dly:2;
        RBus_UInt32  ch2_hporch_num:13;
        RBus_UInt32  ch2_l_flag_force_tog:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_hporch_num_sel:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  ch2_de_mask_en:1;
    };
}vgip_chn2_misc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_hcaptst_num:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_vcaptst_num:13;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch2_captst_mode:1;
        RBus_UInt32  ch2_captst_en:1;
    };
}vgip_chn2_ptn_h_vi_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_captst_g_data:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch2_captst_r_data:12;
        RBus_UInt32  res1:4;
    };
}vgip_chn2_ptn0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_captst_b_data:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch2_hporch_num_sel:14;
        RBus_UInt32  res1:2;
    };
}vgip_chn2_ptn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_vln:12;
        RBus_UInt32  ch2_line_cnt:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  ch2_den_crc_sel:1;
        RBus_UInt32  ch2_vlc_ie:1;
        RBus_UInt32  ch2_vlc_mode:1;
        RBus_UInt32  ch2_vlcen:1;
    };
}vgip_chn2_lc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_crc_start:1;
        RBus_UInt32  ch2_crc_conti:1;
        RBus_UInt32  ch2_crc_field:1;
        RBus_UInt32  ch2_crc_field_edge_sel:1;
        RBus_UInt32  ch2_crc_ctrl_in:1;
        RBus_UInt32  ch2_crc_region:1;
        RBus_UInt32  res1:26;
    };
}ich2_vgip_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_crc_result:32;
    };
}ich2_vgip_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_field_err_ie:1;
        RBus_UInt32  ch2_hs_err_ie:1;
        RBus_UInt32  ch2_vs_err_ie:1;
        RBus_UInt32  ch2_rl_err_ie:1;
        RBus_UInt32  dummy18022440_14_4:11;
        RBus_UInt32  ch2_rl_err_wde:1;
        RBus_UInt32  ch2_field_err_wde:1;
        RBus_UInt32  ch2_hs_err_wde:1;
        RBus_UInt32  ch2_vs_err_wde:1;
        RBus_UInt32  dummy18022440_29_19:11;
        RBus_UInt32  ch2_wd_to_sub:1;
        RBus_UInt32  ch2_wd_to_main:1;
    };
}vgip_chn2_wde_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_pr_l_r_only_en:1;
        RBus_UInt32  ch2_pr_l_r_only_rm_den:1;
        RBus_UInt32  ch2_pr_l_r_only_mask_hs:1;
        RBus_UInt32  res1:29;
    };
}ch2_pr_l_r_only_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_adc_test_dma_mode:1;
        RBus_UInt32  ch2_force_vsync:1;
        RBus_UInt32  ch2_force_den:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch2_adc_test_dma_count:28;
    };
}ch2_adc_raw_data_dma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_vs_position:13;
        RBus_UInt32  ch2_frame_packing_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_vs_width:13;
        RBus_UInt32  res1:3;
    };
}ch2_framepacking_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_den_mask_end:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_den_mask_start:13;
        RBus_UInt32  res1:3;
    };
}ch2_framepacking_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_en_ctsfifo_bypass_vgip:1;
        RBus_UInt32  ch2_en_ctsfifo_vsrst_vgip:1;
        RBus_UInt32  ch2_force_ctsfifo_rstn_vgip:1;
        RBus_UInt32  ch2_dummy_ctsfifo_vgip:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  ch2_en_ctsfifo_bypass_sdnr:1;
        RBus_UInt32  ch2_en_ctsfifo_vsrst_sdnr:1;
        RBus_UInt32  ch2_force_ctsfifo_rstn_sdnr:1;
        RBus_UInt32  ch2_dummy_ctsfifo_sdnr:1;
        RBus_UInt32  res1:20;
    };
}ch2_cts_fifo_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ch2_dispi_test_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_3d_right_ih_act_wid:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_3d_right_ih_act_sta:14;
        RBus_UInt32  res1:2;
    };
}vgip_chn2_3d_right_act_hsta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_3d_right_iv_act_len:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_3d_right_iv_act_sta:13;
        RBus_UInt32  res1:3;
    };
}vgip_chn2_3d_right_act_vsta_length_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_vs_position_r_odd:13;
        RBus_UInt32  ch2_frame_packing_field_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_vs_width_r_odd:13;
        RBus_UInt32  res1:3;
    };
}ch2_framepacking_interlace_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_den_mask_end_r_odd:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_den_mask_start_r_odd:13;
        RBus_UInt32  res1:3;
    };
}ch2_framepacking_interlace_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_vs_position_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_vs_width_r_even:13;
        RBus_UInt32  res1:3;
    };
}ch2_framepacking_interlace_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_den_mask_end_r_even:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ch2_den_mask_start_r_even:13;
        RBus_UInt32  res1:3;
    };
}ch2_framepacking_interlace_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_sta_l:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ch2_end_l:14;
        RBus_UInt32  res1:2;
    };
}ch2_l_r_active_enable_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_sta_r:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  ch2_end_r:14;
        RBus_UInt32  ch2_h_v_mode:1;
        RBus_UInt32  ch2_l_r_act_en:1;
    };
}ch2_l_r_active_enable_ctrl2_RBUS;


#endif







#endif //_RBUS_VGIP_REG_H_

