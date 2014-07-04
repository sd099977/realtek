/**
* @file rbusPifReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/27
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_PIF_REG_H_
#define _RBUS_PIF_REG_H_

#include "rbusTypes.h"




// PIF Register Address

#define PIF_LVDS_CTRL0_VADDR                       (0xb802d000)
#define PIF_LVDS_DUMMY_0_VADDR                     (0xb802d004)
#define PIF_LVDS_CTRL1_VADDR                       (0xb802d008)
#define PIF_LVDS_CTRL2_VADDR                       (0xb802d00c)
#define PIF_LVDS_CTRL3_VADDR                       (0xb802d010)
#define PIF_MLVDS_CTRL0_VADDR                      (0xb802d01c)
#define PIF_MLVDS_RESET_PUL_CTRL_VADDR             (0xb802d020)
#define PIF_MLVDS_CTRL1_VADDR                      (0xb802d024)
#define PIF_MLVDS_CTRL2_VADDR                      (0xb802d028)
#define PIF_MLVDS_CTRL3_VADDR                      (0xb802d02c)
#define PIF_MLVDS_MULTI_RESET_PULSE_CTRL_VADDR     (0xb802d030)
#define PIF_MLVDS_MULTI_RESET_PULSE_0_VADDR        (0xb802d034)
#define PIF_MLVDS_MULTI_RESET_PULSE_1_VADDR        (0xb802d038)
#define PIF_MLVDS_MULTI_RESET_PULSE_2_VADDR        (0xb802d03c)
#define PIF_MLVDS_MULTI_RESET_PULSE_3_VADDR        (0xb802d040)
#define PIF_MLVDS_MULTI_RESET_PULSE_4_VADDR        (0xb802d044)
#define PIF_MLVDS_MULTI_RESET_PULSE_5_VADDR        (0xb802d048)
#define PIF_MLVDS_MULTI_RESET_PULSE_6_VADDR        (0xb802d04c)
#define PIF_MLVDS_MULTI_RESET_PULSE_7_VADDR        (0xb802d050)
#define PIF_MLVDS_MULTI_RESET_PULSE_8_VADDR        (0xb802d054)
#define PIF_MLVDS_MULTI_RESET_PULSE_9_VADDR        (0xb802d058)
#define PIF_MLVDS_MULTI_RESET_PULSE_10_VADDR       (0xb802d05c)
#define PIF_MLVDS_MULTI_RESET_PULSE_11_VADDR       (0xb802d060)
#define PIF_PAT_DET_WINDOW_H_INI_STA_WIDTH_VADDR   (0xb802d070)
#define PIF_PAT_DET_WINDOW_V_INI_STA_HEIGHT_VADDR  (0xb802d074)
#define PIF_PATTERN_DETECT_CTRL_VADDR              (0xb802d078)
#define PIF_PAT_DET_SUM1_VADDR                     (0xb802d080)
#define PIF_PAT_DET_SUM2_VADDR                     (0xb802d084)
#define PIF_PAT_DET_SUM3_VADDR                     (0xb802d088)
#define PIF_PAT_DET_SUM4_VADDR                     (0xb802d08c)
#define PIF_PAT_DET_SUM5_VADDR                     (0xb802d090)
#define PIF_PAT_DET_SUM6_VADDR                     (0xb802d094)
#define PIF_PAT_DET_SUM7_VADDR                     (0xb802d098)
#define PIF_PAT_DET_SUM8_VADDR                     (0xb802d09c)
#define PIF_PAT_DET_SUM9_VADDR                     (0xb802d0a0)
#define PIF_PAT_DET_SUM10_VADDR                    (0xb802d0a4)
#define PIF_PAT_DET_SUM11_VADDR                    (0xb802d0a8)
#define PIF_PAT_DET_SUM12_VADDR                    (0xb802d0ac)
#define PIF_PAT_DET_SUM13_VADDR                    (0xb802d0b0)
#define PIF_PAT_DET_SUM14_VADDR                    (0xb802d0b4)
#define PIF_PAT_DET_SUM15_VADDR                    (0xb802d0b8)
#define PIF_PAT_DET_SUM16_VADDR                    (0xb802d0bc)
#define PIF_PAT_DET_TH1_VADDR                      (0xb802d0c0)
#define PIF_PAT_DET_TH2_VADDR                      (0xb802d0c4)
#define PIF_PAT_DET_TH3_VADDR                      (0xb802d0c8)
#define PIF_PAT_DET_TH4_VADDR                      (0xb802d0cc)
#define PIF_PAT_DET_TH5_VADDR                      (0xb802d0d0)
#define PIF_PAT_DET_TH6_VADDR                      (0xb802d0d4)
#define PIF_PAT_DET_TH7_VADDR                      (0xb802d0d8)
#define PIF_PAT_DET_TH8_VADDR                      (0xb802d0dc)
#define PIF_PAT_DET_TH9_VADDR                      (0xb802d0e0)
#define PIF_PAT_DET_TH10_VADDR                     (0xb802d0e4)
#define PIF_PAT_DET_TH11_VADDR                     (0xb802d0e8)
#define PIF_PAT_DET_TH12_VADDR                     (0xb802d0ec)
#define PIF_PAT_DET_TH13_VADDR                     (0xb802d0f0)
#define PIF_PAT_DET_TH14_VADDR                     (0xb802d0f4)
#define PIF_PAT_DET_TH15_VADDR                     (0xb802d0f8)
#define PIF_PAT_DET_TH16_VADDR                     (0xb802d0fc)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======PIF register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  pif_debug_sel:3;
        RBus_UInt32  plt_lvds_mode_78:2;
        RBus_UInt32  res2:2;
    };
}lvds_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_dummy_0:32;
    };
}lvds_dummy_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_arsv1_sel:3;
        RBus_UInt32  lvds_arsv0_sel:3;
        RBus_UInt32  lvds_aden_sel:3;
        RBus_UInt32  lvds_avs_sel:3;
        RBus_UInt32  lvds_ahs_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  lvds_brsv1_sel:3;
        RBus_UInt32  lvds_brsv0_sel:3;
        RBus_UInt32  lvds_bden_sel:3;
        RBus_UInt32  lvds_bvs_sel:3;
        RBus_UInt32  lvds_bhs_sel:3;
        RBus_UInt32  res2:1;
    };
}lvds_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lvds_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  lvds_map_inv:1;
        RBus_UInt32  lvds_map:2;
        RBus_UInt32  lvds_pn_swap:1;
        RBus_UInt32  lvds_mirror:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ttl_en:1;
        RBus_UInt32  lvds_aport_en:1;
        RBus_UInt32  lvds_bport_en:1;
        RBus_UInt32  res3:6;
    };
}lvds_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_dummy_0:20;
        RBus_UInt32  mlvds_map_type_sel:4;
        RBus_UInt32  mlvds_en:1;
        RBus_UInt32  mlvds_map_inv:1;
        RBus_UInt32  mlvds_8p_special_swap:1;
        RBus_UInt32  mlvds_rl_swap:1;
        RBus_UInt32  mlvds_pn_swap:1;
        RBus_UInt32  mlvds_mirror:1;
        RBus_UInt32  mlvds_mode:2;
    };
}mlvds_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_rst_dummy:20;
        RBus_UInt32  mlvds_reset_pul_sel:12;
    };
}mlvds_reset_pul_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tcon_sel:8;
        RBus_UInt32  tcon_delay_sel_7:2;
        RBus_UInt32  tcon_delay_sel_6:2;
        RBus_UInt32  tcon_delay_sel_5:2;
        RBus_UInt32  tcon_delay_sel_4:2;
        RBus_UInt32  tcon_delay_sel_3:2;
        RBus_UInt32  tcon_delay_sel_2:2;
        RBus_UInt32  tcon_delay_sel_1:2;
        RBus_UInt32  tcon_delay_sel_0:2;
        RBus_UInt32  mlvds_rst_tcon_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  mlvds_rst_high:5;
    };
}mlvds_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_rst_low_region:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  mlvds_2ck_inv:1;
        RBus_UInt32  mlvds_1ck_inv:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  fw_merge_tcon_en:1;
        RBus_UInt32  p3_tcon_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  p3_tcon_sel:5;
        RBus_UInt32  p2_tcon_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  p2_tcon_sel:5;
        RBus_UInt32  p1_tcon_en:1;
        RBus_UInt32  res5:2;
        RBus_UInt32  p1_tcon_sel:5;
    };
}mlvds_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_rst_low:32;
    };
}mlvds_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_multi_reset_pulse_en:1;
        RBus_UInt32  res1:31;
    };
}mlvds_multi_reset_pulse_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_0:1;
        RBus_UInt32  mlvds_mrst_dummy_0:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_0:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_0:8;
        RBus_UInt32  mlvds_mrst_shift_0:4;
        RBus_UInt32  mlvds_mrst_low_0:12;
    };
}mlvds_multi_reset_pulse_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_1:1;
        RBus_UInt32  mlvds_mrst_dummy_1:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_1:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_1:8;
        RBus_UInt32  mlvds_mrst_shift_1:4;
        RBus_UInt32  mlvds_mrst_low_1:12;
    };
}mlvds_multi_reset_pulse_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_2:1;
        RBus_UInt32  mlvds_mrst_dummy_2:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_2:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_2:8;
        RBus_UInt32  mlvds_mrst_shift_2:4;
        RBus_UInt32  mlvds_mrst_low_2:12;
    };
}mlvds_multi_reset_pulse_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_3:1;
        RBus_UInt32  mlvds_mrst_dummy_3:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_3:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_3:8;
        RBus_UInt32  mlvds_mrst_shift_3:4;
        RBus_UInt32  mlvds_mrst_low_3:12;
    };
}mlvds_multi_reset_pulse_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_4:1;
        RBus_UInt32  mlvds_mrst_dummy_4:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_4:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_4:8;
        RBus_UInt32  mlvds_mrst_shift_4:4;
        RBus_UInt32  mlvds_mrst_low_4:12;
    };
}mlvds_multi_reset_pulse_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_5:1;
        RBus_UInt32  mlvds_mrst_dummy_5:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_5:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_5:8;
        RBus_UInt32  mlvds_mrst_shift_5:4;
        RBus_UInt32  mlvds_mrst_low_5:12;
    };
}mlvds_multi_reset_pulse_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_6:1;
        RBus_UInt32  mlvds_mrst_dummy_6:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_6:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_6:8;
        RBus_UInt32  mlvds_mrst_shift_6:4;
        RBus_UInt32  mlvds_mrst_low_6:12;
    };
}mlvds_multi_reset_pulse_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_7:1;
        RBus_UInt32  mlvds_mrst_dummy_7:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_7:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_7:8;
        RBus_UInt32  mlvds_mrst_shift_7:4;
        RBus_UInt32  mlvds_mrst_low_7:12;
    };
}mlvds_multi_reset_pulse_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_8:1;
        RBus_UInt32  mlvds_mrst_dummy_8:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_8:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_8:8;
        RBus_UInt32  mlvds_mrst_shift_8:4;
        RBus_UInt32  mlvds_mrst_low_8:12;
    };
}mlvds_multi_reset_pulse_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_9:1;
        RBus_UInt32  mlvds_mrst_dummy_9:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_9:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_9:8;
        RBus_UInt32  mlvds_mrst_shift_9:4;
        RBus_UInt32  mlvds_mrst_low_9:12;
    };
}mlvds_multi_reset_pulse_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_10:1;
        RBus_UInt32  mlvds_mrst_dummy_10:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_10:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_10:8;
        RBus_UInt32  mlvds_mrst_shift_10:4;
        RBus_UInt32  mlvds_mrst_low_10:12;
    };
}mlvds_multi_reset_pulse_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_tcon_merge_en_11:1;
        RBus_UInt32  mlvds_mrst_dummy_11:2;
        RBus_UInt32  mlvds_mrst_tcon_sel_11:5;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_11:8;
        RBus_UInt32  mlvds_mrst_shift_11:4;
        RBus_UInt32  mlvds_mrst_low_11:12;
    };
}mlvds_multi_reset_pulse_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  pat_det_h_ini_sta:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  pat_det_width:13;
    };
}pat_det_window_h_ini_sta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  pat_det_v_ini_sta:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  pat_det_height:12;
    };
}pat_det_window_v_ini_sta_height_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  spc_pt_1:1;
        RBus_UInt32  spc_pt_2:1;
        RBus_UInt32  spc_pt_3:1;
        RBus_UInt32  spc_pt_4:1;
        RBus_UInt32  spc_pt_5:1;
        RBus_UInt32  spc_pt_6:1;
        RBus_UInt32  spc_pt_7:1;
        RBus_UInt32  spc_pt_8:1;
        RBus_UInt32  spc_pt_9:1;
        RBus_UInt32  spc_pt_10:1;
        RBus_UInt32  spc_pt_11:1;
        RBus_UInt32  spc_pt_12:1;
        RBus_UInt32  spc_pt_13:1;
        RBus_UInt32  spc_pt_14:1;
        RBus_UInt32  spc_pt_15:1;
        RBus_UInt32  spc_pt_16:1;
        RBus_UInt32  res2:6;
        RBus_UInt32  pat_det_en:1;
        RBus_UInt32  pat_det_auto:1;
    };
}pattern_detect_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_1:32;
    };
}pat_det_sum1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_2:32;
    };
}pat_det_sum2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_3:32;
    };
}pat_det_sum3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_4:32;
    };
}pat_det_sum4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_5:32;
    };
}pat_det_sum5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_6:32;
    };
}pat_det_sum6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_7:32;
    };
}pat_det_sum7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_8:32;
    };
}pat_det_sum8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_9:32;
    };
}pat_det_sum9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_10:32;
    };
}pat_det_sum10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_11:32;
    };
}pat_det_sum11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_12:32;
    };
}pat_det_sum12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_13:32;
    };
}pat_det_sum13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_14:32;
    };
}pat_det_sum14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_15:32;
    };
}pat_det_sum15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_16:32;
    };
}pat_det_sum16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th1:32;
    };
}pat_det_th1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th2:32;
    };
}pat_det_th2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th3:32;
    };
}pat_det_th3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th4:32;
    };
}pat_det_th4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th5:32;
    };
}pat_det_th5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th6:32;
    };
}pat_det_th6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th7:32;
    };
}pat_det_th7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th8:32;
    };
}pat_det_th8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th9:32;
    };
}pat_det_th9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th10:32;
    };
}pat_det_th10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th11:32;
    };
}pat_det_th11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th12:32;
    };
}pat_det_th12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th13:32;
    };
}pat_det_th13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th14:32;
    };
}pat_det_th14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th15:32;
    };
}pat_det_th15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th16:32;
    };
}pat_det_th16_RBUS;





#else //apply LITTLE_ENDIAN


//======PIF register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_lvds_mode_78:2;
        RBus_UInt32  pif_debug_sel:3;
        RBus_UInt32  res1:25;
    };
}lvds_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_dummy_0:32;
    };
}lvds_dummy_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:1;
        RBus_UInt32  lvds_bhs_sel:3;
        RBus_UInt32  lvds_bvs_sel:3;
        RBus_UInt32  lvds_bden_sel:3;
        RBus_UInt32  lvds_brsv0_sel:3;
        RBus_UInt32  lvds_brsv1_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  lvds_ahs_sel:3;
        RBus_UInt32  lvds_avs_sel:3;
        RBus_UInt32  lvds_aden_sel:3;
        RBus_UInt32  lvds_arsv0_sel:3;
        RBus_UInt32  lvds_arsv1_sel:3;
    };
}lvds_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lvds_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res3:6;
        RBus_UInt32  lvds_bport_en:1;
        RBus_UInt32  lvds_aport_en:1;
        RBus_UInt32  ttl_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  lvds_mirror:1;
        RBus_UInt32  lvds_pn_swap:1;
        RBus_UInt32  lvds_map:2;
        RBus_UInt32  lvds_map_inv:1;
        RBus_UInt32  res1:17;
    };
}lvds_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mode:2;
        RBus_UInt32  mlvds_mirror:1;
        RBus_UInt32  mlvds_pn_swap:1;
        RBus_UInt32  mlvds_rl_swap:1;
        RBus_UInt32  mlvds_8p_special_swap:1;
        RBus_UInt32  mlvds_map_inv:1;
        RBus_UInt32  mlvds_en:1;
        RBus_UInt32  mlvds_map_type_sel:4;
        RBus_UInt32  mlvds_dummy_0:20;
    };
}mlvds_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_reset_pul_sel:12;
        RBus_UInt32  mlvds_rst_dummy:20;
    };
}mlvds_reset_pul_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_rst_high:5;
        RBus_UInt32  res1:2;
        RBus_UInt32  mlvds_rst_tcon_en:1;
        RBus_UInt32  tcon_delay_sel_0:2;
        RBus_UInt32  tcon_delay_sel_1:2;
        RBus_UInt32  tcon_delay_sel_2:2;
        RBus_UInt32  tcon_delay_sel_3:2;
        RBus_UInt32  tcon_delay_sel_4:2;
        RBus_UInt32  tcon_delay_sel_5:2;
        RBus_UInt32  tcon_delay_sel_6:2;
        RBus_UInt32  tcon_delay_sel_7:2;
        RBus_UInt32  tcon_sel:8;
    };
}mlvds_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  p1_tcon_sel:5;
        RBus_UInt32  res5:2;
        RBus_UInt32  p1_tcon_en:1;
        RBus_UInt32  p2_tcon_sel:5;
        RBus_UInt32  res4:2;
        RBus_UInt32  p2_tcon_en:1;
        RBus_UInt32  p3_tcon_sel:5;
        RBus_UInt32  res3:2;
        RBus_UInt32  p3_tcon_en:1;
        RBus_UInt32  fw_merge_tcon_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  mlvds_1ck_inv:1;
        RBus_UInt32  mlvds_2ck_inv:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  mlvds_rst_low_region:1;
    };
}mlvds_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_rst_low:32;
    };
}mlvds_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  mlvds_multi_reset_pulse_en:1;
    };
}mlvds_multi_reset_pulse_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_0:12;
        RBus_UInt32  mlvds_mrst_shift_0:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_0:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_0:5;
        RBus_UInt32  mlvds_mrst_dummy_0:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_0:1;
    };
}mlvds_multi_reset_pulse_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_1:12;
        RBus_UInt32  mlvds_mrst_shift_1:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_1:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_1:5;
        RBus_UInt32  mlvds_mrst_dummy_1:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_1:1;
    };
}mlvds_multi_reset_pulse_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_2:12;
        RBus_UInt32  mlvds_mrst_shift_2:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_2:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_2:5;
        RBus_UInt32  mlvds_mrst_dummy_2:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_2:1;
    };
}mlvds_multi_reset_pulse_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_3:12;
        RBus_UInt32  mlvds_mrst_shift_3:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_3:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_3:5;
        RBus_UInt32  mlvds_mrst_dummy_3:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_3:1;
    };
}mlvds_multi_reset_pulse_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_4:12;
        RBus_UInt32  mlvds_mrst_shift_4:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_4:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_4:5;
        RBus_UInt32  mlvds_mrst_dummy_4:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_4:1;
    };
}mlvds_multi_reset_pulse_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_5:12;
        RBus_UInt32  mlvds_mrst_shift_5:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_5:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_5:5;
        RBus_UInt32  mlvds_mrst_dummy_5:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_5:1;
    };
}mlvds_multi_reset_pulse_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_6:12;
        RBus_UInt32  mlvds_mrst_shift_6:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_6:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_6:5;
        RBus_UInt32  mlvds_mrst_dummy_6:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_6:1;
    };
}mlvds_multi_reset_pulse_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_7:12;
        RBus_UInt32  mlvds_mrst_shift_7:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_7:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_7:5;
        RBus_UInt32  mlvds_mrst_dummy_7:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_7:1;
    };
}mlvds_multi_reset_pulse_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_8:12;
        RBus_UInt32  mlvds_mrst_shift_8:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_8:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_8:5;
        RBus_UInt32  mlvds_mrst_dummy_8:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_8:1;
    };
}mlvds_multi_reset_pulse_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_9:12;
        RBus_UInt32  mlvds_mrst_shift_9:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_9:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_9:5;
        RBus_UInt32  mlvds_mrst_dummy_9:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_9:1;
    };
}mlvds_multi_reset_pulse_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_10:12;
        RBus_UInt32  mlvds_mrst_shift_10:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_10:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_10:5;
        RBus_UInt32  mlvds_mrst_dummy_10:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_10:1;
    };
}mlvds_multi_reset_pulse_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mlvds_mrst_low_11:12;
        RBus_UInt32  mlvds_mrst_shift_11:4;
        RBus_UInt32  mlvds_mrst_tcon_delay_en_11:8;
        RBus_UInt32  mlvds_mrst_tcon_sel_11:5;
        RBus_UInt32  mlvds_mrst_dummy_11:2;
        RBus_UInt32  mlvds_mrst_tcon_merge_en_11:1;
    };
}mlvds_multi_reset_pulse_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_det_width:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  pat_det_h_ini_sta:13;
        RBus_UInt32  res1:3;
    };
}pat_det_window_h_ini_sta_width_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_det_height:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  pat_det_v_ini_sta:12;
        RBus_UInt32  res1:4;
    };
}pat_det_window_v_ini_sta_height_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_det_auto:1;
        RBus_UInt32  pat_det_en:1;
        RBus_UInt32  res2:6;
        RBus_UInt32  spc_pt_16:1;
        RBus_UInt32  spc_pt_15:1;
        RBus_UInt32  spc_pt_14:1;
        RBus_UInt32  spc_pt_13:1;
        RBus_UInt32  spc_pt_12:1;
        RBus_UInt32  spc_pt_11:1;
        RBus_UInt32  spc_pt_10:1;
        RBus_UInt32  spc_pt_9:1;
        RBus_UInt32  spc_pt_8:1;
        RBus_UInt32  spc_pt_7:1;
        RBus_UInt32  spc_pt_6:1;
        RBus_UInt32  spc_pt_5:1;
        RBus_UInt32  spc_pt_4:1;
        RBus_UInt32  spc_pt_3:1;
        RBus_UInt32  spc_pt_2:1;
        RBus_UInt32  spc_pt_1:1;
        RBus_UInt32  res1:8;
    };
}pattern_detect_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_1:32;
    };
}pat_det_sum1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_2:32;
    };
}pat_det_sum2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_3:32;
    };
}pat_det_sum3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_4:32;
    };
}pat_det_sum4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_5:32;
    };
}pat_det_sum5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_6:32;
    };
}pat_det_sum6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_7:32;
    };
}pat_det_sum7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_8:32;
    };
}pat_det_sum8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_9:32;
    };
}pat_det_sum9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_10:32;
    };
}pat_det_sum10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_11:32;
    };
}pat_det_sum11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_12:32;
    };
}pat_det_sum12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_13:32;
    };
}pat_det_sum13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_14:32;
    };
}pat_det_sum14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_15:32;
    };
}pat_det_sum15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sum_line_16:32;
    };
}pat_det_sum16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th1:32;
    };
}pat_det_th1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th2:32;
    };
}pat_det_th2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th3:32;
    };
}pat_det_th3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th4:32;
    };
}pat_det_th4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th5:32;
    };
}pat_det_th5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th6:32;
    };
}pat_det_th6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th7:32;
    };
}pat_det_th7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th8:32;
    };
}pat_det_th8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th9:32;
    };
}pat_det_th9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th10:32;
    };
}pat_det_th10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th11:32;
    };
}pat_det_th11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th12:32;
    };
}pat_det_th12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th13:32;
    };
}pat_det_th13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th14:32;
    };
}pat_det_th14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th15:32;
    };
}pat_det_th15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pat_th16:32;
    };
}pat_det_th16_RBUS;


#endif







#endif //_RBUS_PIF_REG_H_

