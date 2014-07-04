/**
* @file rbusColor_sharpReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/12/31
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_COLOR_SHARP_REG_H_
#define _RBUS_COLOR_SHARP_REG_H_

#include "rbusTypes.h"



//  COLOR_SHARP Register Address



#define  COLOR_SHARP_DM_NR_SHP_CTRL_VADDR 		(0xb802a500)
#define  COLOR_SHARP_DM_MKIII_SHP_CTRL_VADDR 		(0xb802a504)
#define  COLOR_SHARP_DM_PEAKING_FILTER_0_VADDR 		(0xb802a528)
#define  COLOR_SHARP_DM_PEAKING_FILTER_1_VADDR 		(0xb802a5c4)
#define  COLOR_SHARP_DM_PEAKING_GAIN_VADDR 		(0xb802a52c)
#define  COLOR_SHARP_DM_PEAKING_BOUND_VADDR 		(0xb802a530)
#define  COLOR_SHARP_DM_PEAKING_EMF_VADDR 		(0xb802a534)
#define  COLOR_SHARP_DM_ECS_CTRL_VADDR 		(0xb802a538)
#define  COLOR_SHARP_DM_ECS_THL_VADDR 		(0xb802a53c)
#define  COLOR_SHARP_DM_CHROMA_LOWPASS_VADDR 		(0xb802a540)
#define  COLOR_SHARP_DM_AUTO_SHP_DATA_VADDR 		(0xb802a544)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_00_VADDR 		(0xb802a548)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_01_VADDR 		(0xb802a54c)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_02_VADDR 		(0xb802a550)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_03_VADDR 		(0xb802a554)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_04_VADDR 		(0xb802a558)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_05_VADDR 		(0xb802a55c)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_06_VADDR 		(0xb802a560)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_07_VADDR 		(0xb802a564)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_08_VADDR 		(0xb802a568)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_09_VADDR 		(0xb802a56c)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_10_VADDR 		(0xb802a570)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_11_VADDR 		(0xb802a574)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_12_VADDR 		(0xb802a578)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_13_VADDR 		(0xb802a57c)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_14_VADDR 		(0xb802a580)
#define  COLOR_SHARP_DM_AUTO_SHP_FIR_COUNT_15_VADDR 		(0xb802a584)
#define  COLOR_SHARP_DM_CDS_CM1_U_BOUND_0_VADDR 		(0xb802a588)
#define  COLOR_SHARP_DM_CDS_CM1_V_BOUND_0_VADDR 		(0xb802a58c)
#define  COLOR_SHARP_DM_CDS_CM5_U_BOUND_0_VADDR 		(0xb802a590)
#define  COLOR_SHARP_DM_CDS_CM5_V_BOUND_0_VADDR 		(0xb802a594)
#define  COLOR_SHARP_DM_CDS_PEAKING_GAIN_CM1_VADDR 		(0xb802a598)
#define  COLOR_SHARP_DM_CDS_PEAKING_BOUND_CM1_VADDR 		(0xb802a59c)
#define  COLOR_SHARP_DM_CDS_PEAKING_GAIN_CM5_VADDR 		(0xb802a5a0)
#define  COLOR_SHARP_DM_CDS_PEAKING_BOUND_CM5_VADDR 		(0xb802a5a4)
#define  COLOR_SHARP_DM_CDS_CM1_U_BOUND_1_VADDR 		(0xb802a5a8)
#define  COLOR_SHARP_DM_CDS_CM1_V_BOUND_1_VADDR 		(0xb802a5ac)
#define  COLOR_SHARP_DM_CDS_CM5_U_BOUND_1_VADDR 		(0xb802a5b0)
#define  COLOR_SHARP_DM_CDS_CM5_V_BOUND_1_VADDR 		(0xb802a5b4)
#define  COLOR_SHARP_DM_PEAKING_EMF_OFFSET_VADDR 		(0xb802a5c8)
#define  COLOR_SHARP_DM_SKIPIR_CTRL1_VADDR 		(0xb802a5d0)
#define  COLOR_SHARP_DM_SKIPIR_CTRL2_VADDR 		(0xb802a5d4)
#define  COLOR_SHARP_DM_SKIPIR_CTRL3_VADDR 		(0xb802a5d8)
#define  COLOR_SHARP_DM_EMFMK2_CTRL_VADDR 		(0xb802a5dc)
#define  COLOR_SHARP_DM_DNOISE_CTRL1_VADDR 		(0xb802a5e0)
#define  COLOR_SHARP_DM_DNOISE_CTRL2_VADDR 		(0xb802a5e4)
#define  COLOR_SHARP_DM_EMF_EXT_VADDR 		(0xb802a5e8)
#define  COLOR_SHARP_DS_NR_SHP_CTRL_VADDR 		(0xb802a600)
#define  COLOR_SHARP_DS_RIPV_DATA_VADDR 		(0xb802a604)
#define  COLOR_SHARP_DS_PEAKING_FILTER_0_VADDR 		(0xb802a628)
#define  COLOR_SHARP_DS_PEAKING_FILTER_1_VADDR 		(0xb802a6c4)
#define  COLOR_SHARP_DS_PEAKING_GAIN_VADDR 		(0xb802a62c)
#define  COLOR_SHARP_DS_PEAKING_BOUND_VADDR 		(0xb802a630)
#define  COLOR_SHARP_DS_PEAKING_EMF_VADDR 		(0xb802a634)
#define  COLOR_SHARP_DS_ECS_CTRL_VADDR 		(0xb802a638)
#define  COLOR_SHARP_DS_ECS_THL_VADDR 		(0xb802a63c)
#define  COLOR_SHARP_DS_CHROMA_LOWPASS_VADDR 		(0xb802a640)
#define  COLOR_SHARP_DM_SEGPK_CTRL1_VADDR 		(0xb802a650)
#define  COLOR_SHARP_DM_SEGPK_CTRL2_VADDR 		(0xb802a654)
#define  COLOR_SHARP_DM_SEGPK_CTRL3_VADDR 		(0xb802a658)
#define  COLOR_SHARP_DM_SEGPK_RING_VADDR 		(0xb802a65c)
#define  COLOR_SHARP_DM_SEGPK_LPF_VADDR 		(0xb802a660)
#define  COLOR_SHARP_DM_SEGPK_EDGPK1_VADDR 		(0xb802a664)
#define  COLOR_SHARP_DM_SEGPK_EDGPK2_VADDR 		(0xb802a668)
#define  COLOR_SHARP_DM_SEGPK_EDGPK3_VADDR 		(0xb802a66c)
#define  COLOR_SHARP_DM_SEGPK_EDGPK4_VADDR 		(0xb802a670)
#define  COLOR_SHARP_DM_SEGPK_VPK1_VADDR 		(0xb802a674)
#define  COLOR_SHARP_DM_SEGPK_VPK2_VADDR 		(0xb802a678)
#define  COLOR_SHARP_DM_SEGPK_VPK3_VADDR 		(0xb802a67c)
#define  COLOR_SHARP_DM_SEGPK_VPK4_VADDR 		(0xb802a680)
#define  COLOR_SHARP_DM_SEGPK_VWSUM_VADDR 		(0xb802a684)
#define  COLOR_SHARP_DM_SEGPK_DBG_VADDR 		(0xb802a688)
#define  COLOR_SHARP_DM_SEGPK_EDGE_CORING_0_VADDR 		(0xb802a6ac)
#define  COLOR_SHARP_DM_SEGPK_EDGE_CORING_1_VADDR 		(0xb802a6b0)
#define  COLOR_SHARP_DM_2D_SHP_EDGE_2_VADDR 		(0xb802a6b4)
#define  COLOR_SHARP_DM_2D_SHP_EDGE_3_VADDR 		(0xb802a6b8)
#define  COLOR_SHARP_DM_2D_SHP_TEX_2_VADDR 		(0xb802a6bc)
#define  COLOR_SHARP_DM_2D_SHP_TEX_3_VADDR 		(0xb802a6c0)
#define  COLOR_SHARP_DS_PEAKING_EMF_OFFSET_VADDR 		(0xb802a6c8)
#define  COLOR_SHARP_SHP_CRC_CTRL_VADDR 		(0xb802a6f0)
#define  COLOR_SHARP_SHP_CRC_RESULT_VADDR 		(0xb802a6f4)
#define  COLOR_SHARP_PEAK2D_BIST_VADDR 		(0xb802a6f8)
#define  COLOR_SHARP_DM_SOURS_LPF_0_VADDR 		(0xb802ae00)
#define  COLOR_SHARP_DM_SOURS_LPF_1_VADDR 		(0xb802ae04)
#define  COLOR_SHARP_DM_2D_SHP_EDGE_0_VADDR 		(0xb802ae08)
#define  COLOR_SHARP_DM_2D_SHP_EDGE_1_VADDR 		(0xb802ae0c)
#define  COLOR_SHARP_DM_2D_SHP_TEX_0_VADDR 		(0xb802ae10)
#define  COLOR_SHARP_DM_2D_SHP_TEX_1_VADDR 		(0xb802ae14)
#define  COLOR_SHARP_DM_MAXMIN_SHP_GAIN_0_VADDR 		(0xb802ae18)
#define  COLOR_SHARP_DM_MAXMIN_SHP_GAIN_1_VADDR 		(0xb802ae1c)
#define  COLOR_SHARP_DM_MAXMIN_SHP_GAIN_2_VADDR 		(0xb802ae20)
#define  COLOR_SHARP_DM_MAXMIN_SHP_GAIN_3_VADDR 		(0xb802ae24)
#define  COLOR_SHARP_DM_MAXMIN_SHP_STEP_0_VADDR 		(0xb802ae28)
#define  COLOR_SHARP_DM_MAXMIN_SHP_STEP_1_VADDR 		(0xb802ae2c)
#define  COLOR_SHARP_DM_MAXMIN_SHP_STEP_2_VADDR 		(0xb802ae30)
#define  COLOR_SHARP_DM_MAXMIN_SHP_STEP_3_VADDR 		(0xb802ae34)
#define  COLOR_SHARP_DM_MAXMIN_LPF_WEIT_0_VADDR 		(0xb802ae38)
#define  COLOR_SHARP_DM_MAXMIN_LPF_WEIT_1_VADDR 		(0xb802ae3c)
#define  COLOR_SHARP_DM_MAXMIN_LPF_WEIT_2_VADDR 		(0xb802ae40)
#define  COLOR_SHARP_DM_MAXMIN_LPF_WEIT_3_VADDR 		(0xb802ae44)
#define  COLOR_SHARP_DM_MAXMIN_LPF_STEP_0_VADDR 		(0xb802ae48)
#define  COLOR_SHARP_DM_MAXMIN_LPF_STEP_1_VADDR 		(0xb802ae4c)
#define  COLOR_SHARP_DM_MAXMIN_LPF_STEP_2_VADDR 		(0xb802ae50)
#define  COLOR_SHARP_DM_MAXMIN_LPF_STEP_3_VADDR 		(0xb802ae54)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_GAIN_0_VADDR 		(0xb802ae58)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_GAIN_1_VADDR 		(0xb802ae5c)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_GAIN_2_VADDR 		(0xb802ae60)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_GAIN_3_VADDR 		(0xb802ae64)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_STEP_0_VADDR 		(0xb802ae68)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_STEP_1_VADDR 		(0xb802ae6c)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_STEP_2_VADDR 		(0xb802ae70)
#define  COLOR_SHARP_DM_MAXMIN_GAIN_BY_Y_STEP_3_VADDR 		(0xb802ae74)
#define  COLOR_SHARP_SHP_DLTI_CTRL_1_VADDR 		(0xb802a68c)
#define  COLOR_SHARP_SHP_DLTI_CTRL_2_VADDR 		(0xb802a690)
#define  COLOR_SHARP_SHP_DLTI_CTRL_3_VADDR 		(0xb802a694)
#define  COLOR_SHARP_SHP_DLTI_GAIN_OFFSET_1_VADDR 		(0xb802a698)
#define  COLOR_SHARP_SHP_DLTI_GAIN_OFFSET_2_VADDR 		(0xb802a69c)
#define  COLOR_SHARP_SHP_DLTI_GAIN_OFFSET_3_VADDR 		(0xb802a6a0)
#define  COLOR_SHARP_SHP_DLTI_GAIN_OFFSET_4_VADDR 		(0xb802a6a4)
#define  COLOR_SHARP_SHP_DLTI_GAIN_OFFSET_5_VADDR 		(0xb802a6a8)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======COLOR_SHARP register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  mkiii_en:1;
        RBus_UInt32  db_read:1;
        RBus_UInt32  db_en:1;
        RBus_UInt32  db_load:1;
        RBus_UInt32  clp_enable:1;
        RBus_UInt32  res2:7;
        RBus_UInt32  emf_enable:1;
        RBus_UInt32  peaking_enable:1;
    };
}dm_nr_shp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  mkiii_tex_filter_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  mkiii_edge_filter_sel:2;
        RBus_UInt32  res3:3;
        RBus_UInt32  mmsum_2d_src_sel:1;
        RBus_UInt32  mmsum_array_mode:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  seg_gain_debug_step:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  seg_gain_debug_mode:2;
        RBus_UInt32  res6:3;
        RBus_UInt32  gain_by_y_en:1;
        RBus_UInt32  lpf_weigh_en:1;
        RBus_UInt32  max_min_gain_en:1;
        RBus_UInt32  sharp_mkiii_debug_en:1;
    };
}dm_mkiii_shp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  sh_b0:2;
        RBus_UInt32  sh_b1:2;
        RBus_UInt32  res2:3;
        RBus_UInt32  c0:9;
        RBus_UInt32  res3:3;
        RBus_UInt32  c1:9;
    };
}dm_peaking_filter_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c2:8;
        RBus_UInt32  res1:1;
        RBus_UInt32  c3:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  c4:7;
        RBus_UInt32  res3:2;
        RBus_UInt32  c5:6;
    };
}dm_peaking_filter_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  tex_d2_shift_bit:2;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_neg:8;
    };
}dm_peaking_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  lv:8;
    };
}dm_peaking_bound_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  seg0_offset:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg2_gain_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  seg1_gain_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  seg0_gain_sel:3;
        RBus_UInt32  emf_range_force_v_5tap:1;
        RBus_UInt32  emf_range_force_h_11tap:1;
        RBus_UInt32  emf_range:2;
        RBus_UInt32  emf_shift:3;
        RBus_UInt32  res5:1;
    };
}dm_peaking_emf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}dm_ecs_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}dm_ecs_thl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  blur_fac:5;
    };
}dm_chroma_lowpass_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  enable:1;
        RBus_UInt32  shift_bit:4;
        RBus_UInt32  bin0_offset:8;
        RBus_UInt32  y_lb:8;
        RBus_UInt32  y_ub:8;
    };
}dm_auto_shp_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut0:22;
    };
}dm_auto_shp_fir_count_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut1:22;
    };
}dm_auto_shp_fir_count_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut2:22;
    };
}dm_auto_shp_fir_count_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut3:22;
    };
}dm_auto_shp_fir_count_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut4:22;
    };
}dm_auto_shp_fir_count_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut5:22;
    };
}dm_auto_shp_fir_count_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut6:22;
    };
}dm_auto_shp_fir_count_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut7:22;
    };
}dm_auto_shp_fir_count_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut8:22;
    };
}dm_auto_shp_fir_count_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut9:22;
    };
}dm_auto_shp_fir_count_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut10:22;
    };
}dm_auto_shp_fir_count_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut11:22;
    };
}dm_auto_shp_fir_count_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut12:22;
    };
}dm_auto_shp_fir_count_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut13:22;
    };
}dm_auto_shp_fir_count_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut14:22;
    };
}dm_auto_shp_fir_count_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  lut15:22;
    };
}dm_auto_shp_fir_count_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  cds_cm5_enable:1;
        RBus_UInt32  cds_cm1_enable:1;
        RBus_UInt32  cds_enable:1;
        RBus_UInt32  cds_debug:2;
        RBus_UInt32  res2:4;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  u_lb:10;
    };
}dm_cds_cm1_u_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  cds_conti_area:4;
        RBus_UInt32  cds_conti_enable:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  v_lb:10;
    };
}dm_cds_cm1_v_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  u_lb:10;
    };
}dm_cds_cm5_u_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  v_lb:10;
    };
}dm_cds_cm5_v_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_neg:8;
    };
}dm_cds_peaking_gain_cm1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  lv:8;
    };
}dm_cds_peaking_bound_cm1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_neg:8;
    };
}dm_cds_peaking_gain_cm5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  lv:8;
    };
}dm_cds_peaking_bound_cm5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  u_lb:10;
    };
}dm_cds_cm1_u_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  v_lb:10;
    };
}dm_cds_cm1_v_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  u_lb:10;
    };
}dm_cds_cm5_u_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  v_lb:10;
    };
}dm_cds_cm5_v_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wtsum_level:3;
        RBus_UInt32  wtsum_enable:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  wtsum_tap:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg2_offset:11;
        RBus_UInt32  res3:1;
        RBus_UInt32  seg1_offset:11;
    };
}dm_peaking_emf_offset_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  oceansft:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  isletsft:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  isletlvsft:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  isletgainsft:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  revlvsft:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  revgainsft:3;
        RBus_UInt32  res7:2;
        RBus_UInt32  islet_mode_sel:1;
        RBus_UInt32  revlv_en:1;
        RBus_UInt32  revgain_en:1;
        RBus_UInt32  isletlv_en:1;
        RBus_UInt32  isletgain_en:1;
        RBus_UInt32  skipir_en:1;
    };
}dm_skipir_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  isletmode1_th:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  debug_sharp_d2sft:3;
        RBus_UInt32  sharp_graymode:1;
        RBus_UInt32  debug_sharp:1;
        RBus_UInt32  debug_revlv:1;
        RBus_UInt32  debug_isletlv:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  islet_enlargeaov:3;
        RBus_UInt32  isletrange:4;
    };
}dm_skipir_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  isletlv_upbnd:8;
        RBus_UInt32  isletgain_upbnd:8;
        RBus_UInt32  revlv_upbnd:8;
        RBus_UInt32  revgain_upbnd:8;
    };
}dm_skipir_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  declinebit:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  blendstepbit:3;
        RBus_UInt32  res3:2;
        RBus_UInt32  lowbnd:10;
        RBus_UInt32  res4:3;
        RBus_UInt32  aov_range:1;
        RBus_UInt32  res5:2;
        RBus_UInt32  emf_mk2_debug:1;
        RBus_UInt32  emf_mode_sel:1;
    };
}dm_emfmk2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802a5e0_31_11:21;
        RBus_UInt32  dnoise_gainsft:3;
        RBus_UInt32  dummy1802a5e0_7:1;
        RBus_UInt32  dnoise_lvsft:3;
        RBus_UInt32  dnoise_aovrange:1;
        RBus_UInt32  dnoise_mode:1;
        RBus_UInt32  dnoise_gain_en:1;
        RBus_UInt32  dnoise_lv_en:1;
    };
}dm_dnoise_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dnoise_gain_upbnd:8;
        RBus_UInt32  dnoise_lv_upbnd:8;
        RBus_UInt32  dnoise_noise_gain_th:8;
        RBus_UInt32  dnoise_noise_lv_th:8;
    };
}dm_dnoise_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  emf_fixextent:8;
    };
}dm_emf_ext_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  clp_enable:1;
        RBus_UInt32  res2:7;
        RBus_UInt32  emf_enable:1;
        RBus_UInt32  peaking_enable:1;
    };
}ds_nr_shp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_ripv_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  sh_b0:2;
        RBus_UInt32  sh_b1:2;
        RBus_UInt32  res2:3;
        RBus_UInt32  c0:9;
        RBus_UInt32  res3:3;
        RBus_UInt32  c1:9;
    };
}ds_peaking_filter_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c2:8;
        RBus_UInt32  res1:1;
        RBus_UInt32  c3:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  c4:7;
        RBus_UInt32  res3:2;
        RBus_UInt32  c5:6;
    };
}ds_peaking_filter_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_neg:8;
    };
}ds_peaking_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  lv:8;
    };
}ds_peaking_bound_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  seg0_offset:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg2_gain_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  seg1_gain_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  seg0_gain_sel:3;
        RBus_UInt32  res5:4;
        RBus_UInt32  emf_shift:3;
        RBus_UInt32  res6:1;
    };
}ds_peaking_emf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_ecs_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_ecs_thl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  blur_fac:5;
    };
}ds_chroma_lowpass_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  edg_tex_blending_lpf_filter_en:1;
        RBus_UInt32  edg_tex_blending_lpf_filter:2;
        RBus_UInt32  enhance_mode:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  edgextrange:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  sobel_stepbit:3;
        RBus_UInt32  sobel_upbnd:8;
        RBus_UInt32  sobelmode:1;
        RBus_UInt32  edgmode:2;
        RBus_UInt32  texpk_en:1;
        RBus_UInt32  edgpk_en:1;
        RBus_UInt32  edgext_en:1;
        RBus_UInt32  segpk_mode:2;
    };
}dm_segpk_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  pkdlti_difsign:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  pkdlti_comsign:3;
        RBus_UInt32  res3:2;
        RBus_UInt32  zigsftbit_reg:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  zdiff_stepbit:3;
        RBus_UInt32  zdiff_upbnd:8;
    };
}dm_segpk_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  tex_en:1;
        RBus_UInt32  actsftbit_reg:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  tex_stepbit:3;
        RBus_UInt32  tex_upbnd:8;
    };
}dm_segpk_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  ringtune:4;
        RBus_UInt32  res2:5;
        RBus_UInt32  ringgain_reg:3;
        RBus_UInt32  res3:2;
        RBus_UInt32  ringrange_reg:2;
        RBus_UInt32  res4:3;
        RBus_UInt32  dering_en:1;
    };
}dm_segpk_ring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  lpf_filter:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  lpf_mode:3;
    };
}dm_segpk_lpf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  sh_b0:2;
        RBus_UInt32  sh_b1:2;
        RBus_UInt32  res2:3;
        RBus_UInt32  c0:9;
        RBus_UInt32  res3:3;
        RBus_UInt32  c1:9;
    };
}dm_segpk_edgpk1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c2:8;
        RBus_UInt32  res1:1;
        RBus_UInt32  c3:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  c4:7;
        RBus_UInt32  res3:2;
        RBus_UInt32  c5:6;
    };
}dm_segpk_edgpk2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  edg_d2_shift_bit:2;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_neg:8;
    };
}dm_segpk_edgpk3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  lv:8;
    };
}dm_segpk_edgpk4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpk_c2:8;
        RBus_UInt32  res1:3;
        RBus_UInt32  vpk_c1:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  vpk_c0:9;
    };
}dm_segpk_vpk1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  vpk_lv:8;
        RBus_UInt32  vpk_gain_neg:8;
        RBus_UInt32  vpk_gain_pos:8;
    };
}dm_segpk_vpk2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  vpk_hv_pos:8;
        RBus_UInt32  vpk_hv_neg:8;
    };
}dm_segpk_vpk3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  vext_reg:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  v_dering_en:1;
        RBus_UInt32  v_tex_en:1;
        RBus_UInt32  vemf_en:1;
        RBus_UInt32  vpk_en:1;
    };
}dm_segpk_vpk4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  v_wtsum_tap:1;
        RBus_UInt32  v_wtsum_level:3;
        RBus_UInt32  v_wtsum_enable:1;
    };
}dm_segpk_vwsum_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  debugmode:4;
    };
}dm_segpk_dbg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  bigedge_ratio:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  smalledge_ratio:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  deltaedge_ratio:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  smalledge_ulevel:5;
    };
}dm_segpk_edge_coring_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  edge_coring_en:1;
        RBus_UInt32  edge_gain_en:1;
        RBus_UInt32  edge_coring_debug:2;
        RBus_UInt32  res1:3;
        RBus_UInt32  deltaedge_ulevel:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  edge_coring_clip:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  edge_gain_bound:5;
        RBus_UInt32  edge_ser_range:4;
    };
}dm_segpk_edge_coring_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c7:8;
        RBus_UInt32  coef_c8:8;
        RBus_UInt32  coef_c9:8;
        RBus_UInt32  coef_c10:8;
    };
}dm_2d_shp_edge_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c11:8;
        RBus_UInt32  coef_c12:8;
        RBus_UInt32  coef_c13:8;
        RBus_UInt32  coef_c14:8;
    };
}dm_2d_shp_edge_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c7:8;
        RBus_UInt32  coef_c8:8;
        RBus_UInt32  coef_c9:8;
        RBus_UInt32  coef_c10:8;
    };
}dm_2d_shp_tex_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c11:8;
        RBus_UInt32  coef_c12:8;
        RBus_UInt32  coef_c13:8;
        RBus_UInt32  coef_c14:8;
    };
}dm_2d_shp_tex_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  seg2_offset:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg1_offset:11;
    };
}ds_peaking_emf_offset_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  crc_channel:1;
        RBus_UInt32  crc_conti:1;
        RBus_UInt32  crc_start:1;
    };
}shp_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  shp_crc_result:32;
    };
}shp_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  ls:1;
        RBus_UInt32  dvse:1;
        RBus_UInt32  dvs:4;
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  drf_fail_0:1;
        RBus_UInt32  drf_fail_1:1;
        RBus_UInt32  drf_fail_2:1;
        RBus_UInt32  drf_fail_3:1;
        RBus_UInt32  res2:5;
    };
}peak2d_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  coef_c0:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  coef_c1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  coef_c2:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  coef_c3:6;
    };
}dm_sours_lpf_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  coef_c4:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  coef_c5:6;
    };
}dm_sours_lpf_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  coef_c0:9;
        RBus_UInt32  coef_c1:8;
        RBus_UInt32  coef_c2:8;
    };
}dm_2d_shp_edge_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c3:8;
        RBus_UInt32  coef_c4:8;
        RBus_UInt32  coef_c5:8;
        RBus_UInt32  coef_c6:8;
    };
}dm_2d_shp_edge_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  coef_c0:9;
        RBus_UInt32  coef_c1:8;
        RBus_UInt32  coef_c2:8;
    };
}dm_2d_shp_tex_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c3:8;
        RBus_UInt32  coef_c4:8;
        RBus_UInt32  coef_c5:8;
        RBus_UInt32  coef_c6:8;
    };
}dm_2d_shp_tex_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s0:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s1:11;
    };
}dm_maxmin_shp_gain_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s3:11;
    };
}dm_maxmin_shp_gain_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s5:11;
    };
}dm_maxmin_shp_gain_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:16;
    };
}dm_maxmin_shp_gain_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  s1:11;
    };
}dm_maxmin_shp_step_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s3:11;
    };
}dm_maxmin_shp_step_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s5:11;
    };
}dm_maxmin_shp_step_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:16;
    };
}dm_maxmin_shp_step_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s0:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s1:11;
    };
}dm_maxmin_lpf_weit_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s3:11;
    };
}dm_maxmin_lpf_weit_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s5:11;
    };
}dm_maxmin_lpf_weit_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:16;
    };
}dm_maxmin_lpf_weit_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  s1:11;
    };
}dm_maxmin_lpf_step_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s3:11;
    };
}dm_maxmin_lpf_step_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s5:11;
    };
}dm_maxmin_lpf_step_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:16;
    };
}dm_maxmin_lpf_step_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s0:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s1:11;
    };
}dm_maxmin_gain_by_y_gain_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s3:11;
    };
}dm_maxmin_gain_by_y_gain_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s5:11;
    };
}dm_maxmin_gain_by_y_gain_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:16;
    };
}dm_maxmin_gain_by_y_gain_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  s1:11;
    };
}dm_maxmin_gain_by_y_step_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s3:11;
    };
}dm_maxmin_gain_by_y_step_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  s5:11;
    };
}dm_maxmin_gain_by_y_step_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:16;
    };
}dm_maxmin_gain_by_y_step_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  data_sel:1;
        RBus_UInt32  can_shift:2;
        RBus_UInt32  maxlen:3;
        RBus_UInt32  pnth:10;
        RBus_UInt32  dcp_th:8;
        RBus_UInt32  res1:1;
        RBus_UInt32  d1_cp_shift:2;
        RBus_UInt32  ffd2_en:1;
        RBus_UInt32  tn_blend_mode:1;
        RBus_UInt32  tn_blend_en:1;
        RBus_UInt32  ovc_en:1;
        RBus_UInt32  dlti_en:1;
    };
}shp_dlti_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dlti_debug:3;
        RBus_UInt32  res1:12;
        RBus_UInt32  ffd1_ratio:7;
        RBus_UInt32  ffd1_th:10;
    };
}shp_dlti_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  ffd2_ratio:7;
        RBus_UInt32  ffd2_range2r:10;
        RBus_UInt32  ffd2_range2l:10;
    };
}shp_dlti_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  tngain2:5;
        RBus_UInt32  tnoff2:4;
        RBus_UInt32  tngain1:5;
        RBus_UInt32  tnoff1:4;
        RBus_UInt32  tngain0:5;
        RBus_UInt32  tnoff0:4;
    };
}shp_dlti_gain_offset_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  tngain5:5;
        RBus_UInt32  tnoff5:4;
        RBus_UInt32  tngain4:5;
        RBus_UInt32  tnoff4:4;
        RBus_UInt32  tngain3:5;
        RBus_UInt32  tnoff3:4;
    };
}shp_dlti_gain_offset_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  tngain8:5;
        RBus_UInt32  tnoff8:4;
        RBus_UInt32  tngain7:5;
        RBus_UInt32  tnoff7:4;
        RBus_UInt32  tngain6:5;
        RBus_UInt32  tnoff6:4;
    };
}shp_dlti_gain_offset_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  tngain11:5;
        RBus_UInt32  tnoff11:4;
        RBus_UInt32  tngain10:5;
        RBus_UInt32  tnoff10:4;
        RBus_UInt32  tngain9:5;
        RBus_UInt32  tnoff9:4;
    };
}shp_dlti_gain_offset_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  tngain14:5;
        RBus_UInt32  tnoff14:4;
        RBus_UInt32  tngain13:5;
        RBus_UInt32  tnoff13:4;
        RBus_UInt32  tngain12:5;
        RBus_UInt32  tnoff12:4;
    };
}shp_dlti_gain_offset_5_RBUS;

#else //apply LITTLE_ENDIAN

//======COLOR_SHARP register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  peaking_enable:1;
        RBus_UInt32  emf_enable:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  clp_enable:1;
        RBus_UInt32  db_load:1;
        RBus_UInt32  db_en:1;
        RBus_UInt32  db_read:1;
        RBus_UInt32  mkiii_en:1;
        RBus_UInt32  res2:18;
    };
}dm_nr_shp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sharp_mkiii_debug_en:1;
        RBus_UInt32  max_min_gain_en:1;
        RBus_UInt32  lpf_weigh_en:1;
        RBus_UInt32  gain_by_y_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  seg_gain_debug_mode:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg_gain_debug_step:3;
        RBus_UInt32  res3:2;
        RBus_UInt32  mmsum_array_mode:1;
        RBus_UInt32  mmsum_2d_src_sel:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  mkiii_edge_filter_sel:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  mkiii_tex_filter_sel:2;
        RBus_UInt32  res6:6;
    };
}dm_mkiii_shp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c1:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  c0:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  sh_b1:2;
        RBus_UInt32  sh_b0:2;
        RBus_UInt32  res3:4;
    };
}dm_peaking_filter_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c5:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  c4:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  c3:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  c2:8;
    };
}dm_peaking_filter_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_neg:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  tex_d2_shift_bit:2;
        RBus_UInt32  res1:6;
    };
}dm_peaking_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lv:8;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  res1:4;
    };
}dm_peaking_bound_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  emf_shift:3;
        RBus_UInt32  emf_range:2;
        RBus_UInt32  emf_range_force_h_11tap:1;
        RBus_UInt32  emf_range_force_v_5tap:1;
        RBus_UInt32  seg0_gain_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg1_gain_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  seg2_gain_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  seg0_offset:11;
        RBus_UInt32  res5:1;
    };
}dm_peaking_emf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}dm_ecs_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}dm_ecs_thl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blur_fac:5;
        RBus_UInt32  res1:27;
    };
}dm_chroma_lowpass_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_ub:8;
        RBus_UInt32  y_lb:8;
        RBus_UInt32  bin0_offset:8;
        RBus_UInt32  shift_bit:4;
        RBus_UInt32  enable:1;
        RBus_UInt32  res1:3;
    };
}dm_auto_shp_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut0:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut1:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut2:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut3:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut4:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut5:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut6:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut7:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut8:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut9:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut10:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut11:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut12:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut13:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut14:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut15:22;
        RBus_UInt32  res1:10;
    };
}dm_auto_shp_fir_count_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res2:4;
        RBus_UInt32  cds_debug:2;
        RBus_UInt32  cds_enable:1;
        RBus_UInt32  cds_cm1_enable:1;
        RBus_UInt32  cds_cm5_enable:1;
        RBus_UInt32  res3:1;
    };
}dm_cds_cm1_u_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  cds_conti_enable:1;
        RBus_UInt32  cds_conti_area:4;
        RBus_UInt32  res3:3;
    };
}dm_cds_cm1_v_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res2:10;
    };
}dm_cds_cm5_u_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res2:10;
    };
}dm_cds_cm5_v_bound_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_neg:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  res1:8;
    };
}dm_cds_peaking_gain_cm1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lv:8;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  res1:4;
    };
}dm_cds_peaking_bound_cm1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_neg:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  res1:8;
    };
}dm_cds_peaking_gain_cm5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lv:8;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  res1:4;
    };
}dm_cds_peaking_bound_cm5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res2:10;
    };
}dm_cds_cm1_u_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res2:10;
    };
}dm_cds_cm1_v_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  u_ub:10;
        RBus_UInt32  res2:10;
    };
}dm_cds_cm5_u_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_lb:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  v_ub:10;
        RBus_UInt32  res2:10;
    };
}dm_cds_cm5_v_bound_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg1_offset:11;
        RBus_UInt32  res1:1;
        RBus_UInt32  seg2_offset:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  wtsum_tap:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  wtsum_enable:1;
        RBus_UInt32  wtsum_level:3;
    };
}dm_peaking_emf_offset_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  skipir_en:1;
        RBus_UInt32  isletgain_en:1;
        RBus_UInt32  isletlv_en:1;
        RBus_UInt32  revgain_en:1;
        RBus_UInt32  revlv_en:1;
        RBus_UInt32  islet_mode_sel:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  revgainsft:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  revlvsft:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  isletgainsft:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  isletlvsft:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  isletsft:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  oceansft:3;
        RBus_UInt32  res7:1;
    };
}dm_skipir_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  isletrange:4;
        RBus_UInt32  islet_enlargeaov:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  debug_isletlv:1;
        RBus_UInt32  debug_revlv:1;
        RBus_UInt32  debug_sharp:1;
        RBus_UInt32  sharp_graymode:1;
        RBus_UInt32  debug_sharp_d2sft:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  isletmode1_th:8;
        RBus_UInt32  res3:8;
    };
}dm_skipir_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  revgain_upbnd:8;
        RBus_UInt32  revlv_upbnd:8;
        RBus_UInt32  isletgain_upbnd:8;
        RBus_UInt32  isletlv_upbnd:8;
    };
}dm_skipir_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  emf_mode_sel:1;
        RBus_UInt32  emf_mk2_debug:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  aov_range:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  lowbnd:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  blendstepbit:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  declinebit:2;
        RBus_UInt32  res5:6;
    };
}dm_emfmk2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dnoise_lv_en:1;
        RBus_UInt32  dnoise_gain_en:1;
        RBus_UInt32  dnoise_mode:1;
        RBus_UInt32  dnoise_aovrange:1;
        RBus_UInt32  dnoise_lvsft:3;
        RBus_UInt32  dummy1802a5e0_7:1;
        RBus_UInt32  dnoise_gainsft:3;
        RBus_UInt32  dummy1802a5e0_31:21;
    };
}dm_dnoise_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dnoise_noise_lv_th:8;
        RBus_UInt32  dnoise_noise_gain_th:8;
        RBus_UInt32  dnoise_lv_upbnd:8;
        RBus_UInt32  dnoise_gain_upbnd:8;
    };
}dm_dnoise_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  emf_fixextent:8;
        RBus_UInt32  res1:24;
    };
}dm_emf_ext_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  peaking_enable:1;
        RBus_UInt32  emf_enable:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  clp_enable:1;
        RBus_UInt32  res2:22;
    };
}ds_nr_shp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_ripv_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c1:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  c0:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  sh_b1:2;
        RBus_UInt32  sh_b0:2;
        RBus_UInt32  res3:4;
    };
}ds_peaking_filter_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c5:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  c4:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  c3:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  c2:8;
    };
}ds_peaking_filter_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_neg:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  res1:8;
    };
}ds_peaking_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lv:8;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  res1:4;
    };
}ds_peaking_bound_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  emf_shift:3;
        RBus_UInt32  res2:4;
        RBus_UInt32  seg0_gain_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  seg1_gain_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  seg2_gain_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  seg0_offset:11;
        RBus_UInt32  res6:1;
    };
}ds_peaking_emf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_ecs_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_ecs_thl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blur_fac:5;
        RBus_UInt32  res1:27;
    };
}ds_chroma_lowpass_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  segpk_mode:2;
        RBus_UInt32  edgext_en:1;
        RBus_UInt32  edgpk_en:1;
        RBus_UInt32  texpk_en:1;
        RBus_UInt32  edgmode:2;
        RBus_UInt32  sobelmode:1;
        RBus_UInt32  sobel_upbnd:8;
        RBus_UInt32  sobel_stepbit:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  edgextrange:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  enhance_mode:2;
        RBus_UInt32  edg_tex_blending_lpf_filter:2;
        RBus_UInt32  edg_tex_blending_lpf_filter_en:1;
        RBus_UInt32  res3:3;
    };
}dm_segpk_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  zdiff_upbnd:8;
        RBus_UInt32  zdiff_stepbit:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  zigsftbit_reg:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  pkdlti_comsign:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  pkdlti_difsign:3;
        RBus_UInt32  res4:9;
    };
}dm_segpk_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tex_upbnd:8;
        RBus_UInt32  tex_stepbit:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  actsftbit_reg:2;
        RBus_UInt32  tex_en:1;
        RBus_UInt32  res2:17;
    };
}dm_segpk_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dering_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  ringrange_reg:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  ringgain_reg:3;
        RBus_UInt32  res3:5;
        RBus_UInt32  ringtune:4;
        RBus_UInt32  res4:12;
    };
}dm_segpk_ring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lpf_mode:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  lpf_filter:3;
        RBus_UInt32  res2:25;
    };
}dm_segpk_lpf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c1:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  c0:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  sh_b1:2;
        RBus_UInt32  sh_b0:2;
        RBus_UInt32  res3:4;
    };
}dm_segpk_edgpk1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c5:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  c4:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  c3:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  c2:8;
    };
}dm_segpk_edgpk2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_neg:8;
        RBus_UInt32  gain_pos:8;
        RBus_UInt32  gain_blr:8;
        RBus_UInt32  edg_d2_shift_bit:2;
        RBus_UInt32  res1:6;
    };
}dm_segpk_edgpk3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lv:8;
        RBus_UInt32  hv_neg:10;
        RBus_UInt32  hv_pos:10;
        RBus_UInt32  res1:4;
    };
}dm_segpk_edgpk4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpk_c0:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  vpk_c1:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  vpk_c2:8;
    };
}dm_segpk_vpk1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpk_gain_pos:8;
        RBus_UInt32  vpk_gain_neg:8;
        RBus_UInt32  vpk_lv:8;
        RBus_UInt32  res1:8;
    };
}dm_segpk_vpk2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpk_hv_neg:8;
        RBus_UInt32  vpk_hv_pos:8;
        RBus_UInt32  res1:16;
    };
}dm_segpk_vpk3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpk_en:1;
        RBus_UInt32  vemf_en:1;
        RBus_UInt32  v_tex_en:1;
        RBus_UInt32  v_dering_en:1;
        RBus_UInt32  res1:4;
        RBus_UInt32  vext_reg:8;
        RBus_UInt32  res2:16;
    };
}dm_segpk_vpk4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_wtsum_enable:1;
        RBus_UInt32  v_wtsum_level:3;
        RBus_UInt32  v_wtsum_tap:1;
        RBus_UInt32  res1:27;
    };
}dm_segpk_vwsum_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  debugmode:4;
        RBus_UInt32  res1:28;
    };
}dm_segpk_dbg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  smalledge_ulevel:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  deltaedge_ratio:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  smalledge_ratio:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  bigedge_ratio:5;
        RBus_UInt32  res4:3;
    };
}dm_segpk_edge_coring_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  edge_ser_range:4;
        RBus_UInt32  edge_gain_bound:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  edge_coring_clip:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  deltaedge_ulevel:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  edge_coring_debug:2;
        RBus_UInt32  edge_gain_en:1;
        RBus_UInt32  edge_coring_en:1;
    };
}dm_segpk_edge_coring_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c10:8;
        RBus_UInt32  coef_c9:8;
        RBus_UInt32  coef_c8:8;
        RBus_UInt32  coef_c7:8;
    };
}dm_2d_shp_edge_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c14:8;
        RBus_UInt32  coef_c13:8;
        RBus_UInt32  coef_c12:8;
        RBus_UInt32  coef_c11:8;
    };
}dm_2d_shp_edge_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c10:8;
        RBus_UInt32  coef_c9:8;
        RBus_UInt32  coef_c8:8;
        RBus_UInt32  coef_c7:8;
    };
}dm_2d_shp_tex_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c14:8;
        RBus_UInt32  coef_c13:8;
        RBus_UInt32  coef_c12:8;
        RBus_UInt32  coef_c11:8;
    };
}dm_2d_shp_tex_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg1_offset:11;
        RBus_UInt32  res1:1;
        RBus_UInt32  seg2_offset:11;
        RBus_UInt32  res2:9;
    };
}ds_peaking_emf_offset_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_start:1;
        RBus_UInt32  crc_conti:1;
        RBus_UInt32  crc_channel:1;
        RBus_UInt32  res1:29;
    };
}shp_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  shp_crc_result:32;
    };
}shp_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  drf_fail_3:1;
        RBus_UInt32  drf_fail_2:1;
        RBus_UInt32  drf_fail_1:1;
        RBus_UInt32  drf_fail_0:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  dvs:4;
        RBus_UInt32  dvse:1;
        RBus_UInt32  ls:1;
        RBus_UInt32  res2:13;
    };
}peak2d_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c3:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  coef_c2:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  coef_c1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  coef_c0:6;
        RBus_UInt32  res4:2;
    };
}dm_sours_lpf_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c5:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  coef_c4:6;
        RBus_UInt32  res2:18;
    };
}dm_sours_lpf_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c2:8;
        RBus_UInt32  coef_c1:8;
        RBus_UInt32  coef_c0:9;
        RBus_UInt32  res1:7;
    };
}dm_2d_shp_edge_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c6:8;
        RBus_UInt32  coef_c5:8;
        RBus_UInt32  coef_c4:8;
        RBus_UInt32  coef_c3:8;
    };
}dm_2d_shp_edge_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c2:8;
        RBus_UInt32  coef_c1:8;
        RBus_UInt32  coef_c0:9;
        RBus_UInt32  res1:7;
    };
}dm_2d_shp_tex_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_c6:8;
        RBus_UInt32  coef_c5:8;
        RBus_UInt32  coef_c4:8;
        RBus_UInt32  coef_c3:8;
    };
}dm_2d_shp_tex_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s1:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s0:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_shp_gain_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s3:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_shp_gain_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s5:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_shp_gain_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_shp_gain_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s1:11;
        RBus_UInt32  res1:21;
    };
}dm_maxmin_shp_step_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s3:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_shp_step_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s5:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_shp_step_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_shp_step_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s1:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s0:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_lpf_weit_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s3:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_lpf_weit_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s5:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_lpf_weit_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_lpf_weit_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s1:11;
        RBus_UInt32  res1:21;
    };
}dm_maxmin_lpf_step_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s3:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_lpf_step_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s5:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_lpf_step_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_lpf_step_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s1:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s0:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_gain_by_y_gain_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s3:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_gain_by_y_gain_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s5:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_gain_by_y_gain_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_gain_by_y_gain_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s1:11;
        RBus_UInt32  res1:21;
    };
}dm_maxmin_gain_by_y_step_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s3:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s2:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_gain_by_y_step_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s5:11;
        RBus_UInt32  res1:5;
        RBus_UInt32  s4:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_gain_by_y_step_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  s6:11;
        RBus_UInt32  res2:5;
    };
}dm_maxmin_gain_by_y_step_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dlti_en:1;
        RBus_UInt32  ovc_en:1;
        RBus_UInt32  tn_blend_en:1;
        RBus_UInt32  tn_blend_mode:1;
        RBus_UInt32  ffd2_en:1;
        RBus_UInt32  d1_cp_shift:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  dcp_th:8;
        RBus_UInt32  pnth:10;
        RBus_UInt32  maxlen:3;
        RBus_UInt32  can_shift:2;
        RBus_UInt32  data_sel:1;
    };
}shp_dlti_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ffd1_th:10;
        RBus_UInt32  ffd1_ratio:7;
        RBus_UInt32  res1:12;
        RBus_UInt32  dlti_debug:3;
    };
}shp_dlti_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ffd2_range2l:10;
        RBus_UInt32  ffd2_range2r:10;
        RBus_UInt32  ffd2_ratio:7;
        RBus_UInt32  res1:5;
    };
}shp_dlti_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tnoff0:4;
        RBus_UInt32  tngain0:5;
        RBus_UInt32  tnoff1:4;
        RBus_UInt32  tngain1:5;
        RBus_UInt32  tnoff2:4;
        RBus_UInt32  tngain2:5;
        RBus_UInt32  res1:5;
    };
}shp_dlti_gain_offset_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tnoff3:4;
        RBus_UInt32  tngain3:5;
        RBus_UInt32  tnoff4:4;
        RBus_UInt32  tngain4:5;
        RBus_UInt32  tnoff5:4;
        RBus_UInt32  tngain5:5;
        RBus_UInt32  res1:5;
    };
}shp_dlti_gain_offset_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tnoff6:4;
        RBus_UInt32  tngain6:5;
        RBus_UInt32  tnoff7:4;
        RBus_UInt32  tngain7:5;
        RBus_UInt32  tnoff8:4;
        RBus_UInt32  tngain8:5;
        RBus_UInt32  res1:5;
    };
}shp_dlti_gain_offset_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tnoff9:4;
        RBus_UInt32  tngain9:5;
        RBus_UInt32  tnoff10:4;
        RBus_UInt32  tngain10:5;
        RBus_UInt32  tnoff11:4;
        RBus_UInt32  tngain11:5;
        RBus_UInt32  res1:5;
    };
}shp_dlti_gain_offset_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tnoff12:4;
        RBus_UInt32  tngain12:5;
        RBus_UInt32  tnoff13:4;
        RBus_UInt32  tngain13:5;
        RBus_UInt32  tnoff14:4;
        RBus_UInt32  tngain14:5;
        RBus_UInt32  res1:5;
    };
}shp_dlti_gain_offset_5_RBUS;




#endif 


#endif 
