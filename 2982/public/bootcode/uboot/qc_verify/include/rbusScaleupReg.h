/**
* @file rbusScaleupReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/12/31
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_SCALEUP_REG_H_
#define _RBUS_SCALEUP_REG_H_

#include "rbusTypes.h"



//  SCALEUP Register Address



#define  SCALEUP_D_UZU_GLOBLE_CTRL_VADDR 		(0xb8029000)
#define  SCALEUP_DM_UZU_CTRL_VADDR 		(0xb8029004)
#define  SCALEUP_DM_UZU_SCALE_HOR_FACTOR_VADDR 		(0xb8029008)
#define  SCALEUP_DM_UZU_SCALE_VER_FACTOR_VADDR 		(0xb802900c)
#define  SCALEUP_DM_UZU_HOR_DELTA1_VADDR 		(0xb8029010)
#define  SCALEUP_DM_UZU_HOR_DELTA2_VADDR 		(0xb8029014)
#define  SCALEUP_DM_UZU_HOR_SEGMENT1_VADDR 		(0xb8029018)
#define  SCALEUP_DM_UZU_HOR_SEGMENT2_VADDR 		(0xb802901c)
#define  SCALEUP_DM_UZU_HOR_SEGMENT3_VADDR 		(0xb8029020)
#define  SCALEUP_DM_UZU_INITIAL_VALUE_VADDR 		(0xb8029024)
#define  SCALEUP_DM_UZU_INPUT_SIZE_VADDR 		(0xb8029028)
#define  SCALEUP_DM_UZU_8TAP_DERING_VADDR 		(0xb802902c)
#define  SCALEUP_DM_UZU_PEAKING_CORING_VADDR 		(0xb8029038)
#define  SCALEUP_DM_UZU_PEAKING_GAIN_VADDR 		(0xb802903c)
#define  SCALEUP_DM_MEM_CRC_CTRL_VADDR 		(0xb8029040)
#define  SCALEUP_DM_MEM_CRC_RESULT_VADDR 		(0xb8029044)
#define  SCALEUP_MEM_CRC_CTR2_VADDR 		(0xb8029048)
#define  SCALEUP_MEM_CRC_R_RESULT_VADDR 		(0xb802904c)
#define  SCALEUP_MEM_L_DES_CRC_VADDR 		(0xb8029050)
#define  SCALEUP_MEM_R_DES_CRC_VADDR 		(0xb8029054)
#define  SCALEUP_MEM_CRC_ERR_CNT_VADDR 		(0xb8029058)
#define  SCALEUP_D_UZU_CRC_CTRL_VADDR 		(0xb802905c)
#define  SCALEUP_D_UZU_CRC_RESULT_VADDR 		(0xb8029060)
#define  SCALEUP_D_UZU_PATGEN_COLOR0_VADDR 		(0xb8029064)
#define  SCALEUP_D_UZU_PATGEN_COLOR1_VADDR 		(0xb8029068)
#define  SCALEUP_D_UZU_PATGEN_COLOR2_VADDR 		(0xb802906c)
#define  SCALEUP_D_UZU_PATGEN_COLOR3_VADDR 		(0xb8029070)
#define  SCALEUP_D_UZU_PATGEN_FRAME_TOGGLE_VADDR 		(0xb8029074)
#define  SCALEUP_D_UZU_PATGEN_FRAME_TOGGLE1_VADDR 		(0xb8029078)
#define  SCALEUP_D_UZU_PATGEN_FRAME_TOGGLE2_VADDR 		(0xb802907c)
#define  SCALEUP_D_UZU_PATGEN_FRAME_TOGGLE3_VADDR 		(0xb8029080)
#define  SCALEUP_ACCESSDATA_CTRL_UZU_VADDR 		(0xb8029090)
#define  SCALEUP_ACCESSDATA_POSCTRL_UZU_VADDR 		(0xb8029094)
#define  SCALEUP_READDATA_DATA_Y1_UZU_VADDR 		(0xb8029098)
#define  SCALEUP_READDATA_DATA_Y2_UZU_VADDR 		(0xb802909c)
#define  SCALEUP_READDATA_DATA_C1_UZU_VADDR 		(0xb80290a0)
#define  SCALEUP_READDATA_DATA_C2_UZU_VADDR 		(0xb80290a4)
#define  SCALEUP_READDATA_DATA_C3_UZU_VADDR 		(0xb80290a8)
#define  SCALEUP_READDATA_DATA_C4_UZU_VADDR 		(0xb80290ac)
#define  SCALEUP_WRITEDATA_DATA_UZU_VADDR 		(0xb80290b0)
#define  SCALEUP_DM_UZU_MAIN_H_PARTIAL_DROP_VADDR 		(0xb80290b4)
#define  SCALEUP_DM_UZU_MAIN_V_PARTIAL_DROP_VADDR 		(0xb80290b8)
#define  SCALEUP_DM_UZU_PARTIAL_DROP_CTRL_VADDR 		(0xb80290bc)
#define  SCALEUP_DM_UZU_MAIN_ADAPT8TAP_VADDR 		(0xb80290c0)
#define  SCALEUP_DM_USM_UN_SHARP_MASK_FILTER_VADDR 		(0xb80290c4)
#define  SCALEUP_DM_USM_UPPER_LOWER_BOUND_SHIFT_VADDR 		(0xb80290c8)
#define  SCALEUP_DM_USM_BLENDING_REGION_THD_VADDR 		(0xb80290cc)
#define  SCALEUP_DM_USM_HLPF_COEF_VADDR 		(0xb80290d0)
#define  SCALEUP_DM_USM_EDGE_DETECT1_VADDR 		(0xb80290d4)
#define  SCALEUP_DM_USM_EDGE_DETECT2_VADDR 		(0xb80290d8)
#define  SCALEUP_DM_USM_EDGE_DETECT3_VADDR 		(0xb80290dc)
#define  SCALEUP_DM_UZU_V6CTRL_VADDR 		(0xb80290e0)
#define  SCALEUP_DM_UZU_ADAPTV6CTRL_VADDR 		(0xb80290e4)
#define  SCALEUP_DM_UZU_INITIAL_VALUE_LEFT_VADDR 		(0xb80290e8)
#define  SCALEUP_DM_UZU_DB_CTRL_VADDR 		(0xb80290f0)
#define  SCALEUP_DM_UZU_WCLR_VADDR 		(0xb80290f4)
#define  SCALEUP_LEFT_3D_PTG_CTRL3_VADDR 		(0xb8029100)
#define  SCALEUP_LEFT_3D_PTG_CTRL4_VADDR 		(0xb8029104)
#define  SCALEUP_LEFT_3D_PTG_CTRL5_VADDR 		(0xb8029108)
#define  SCALEUP_RIGHT_3D_PTG_CTRL1_VADDR 		(0xb802910c)
#define  SCALEUP_RIGHT_3D_PTG_CTRL2_VADDR 		(0xb8029110)
#define  SCALEUP_RIGHT_3D_PTG_CTRL3_VADDR 		(0xb8029114)
#define  SCALEUP_PTG_3D_CTR1_VADDR 		(0xb8029118)
#define  SCALEUP_COEF_TABLE_RW_CTL_VADDR 		(0xb8029130)
#define  SCALEUP_COEF_TABLE_CTL_VADDR 		(0xb8029134)
#define  SCALEUP_COEF_TABLE_CTL_0_VADDR 		(0xb8029138)
#define  SCALEUP_COEF_TABLE_CTL_1_VADDR 		(0xb802913c)
#define  SCALEUP_COEF_TABLE_CTL_2_VADDR 		(0xb8029140)
#define  SCALEUP_COEF_TABLE_CTL_3_VADDR 		(0xb8029144)
#define  SCALEUP_DM_UZU_BIST_0_VADDR 		(0xb8029180)
#define  SCALEUP_DM_UZU_BIST_2_VADDR 		(0xb8029184)
#define  SCALEUP_DM_UZU_BIST_3_VADDR 		(0xb8029188)
#define  SCALEUP_DM_UZU_BIST_4_VADDR 		(0xb802918c)
#define  SCALEUP_DM_UZU_COEF_BIST_VADDR 		(0xb8029190)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C0_VADDR 		(0xb8029200)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C2_VADDR 		(0xb8029204)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C4_VADDR 		(0xb8029208)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C6_VADDR 		(0xb802920c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C8_VADDR 		(0xb8029210)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C10_VADDR 		(0xb8029214)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C12_VADDR 		(0xb8029218)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C14_VADDR 		(0xb802921c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C16_VADDR 		(0xb8029220)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C18_VADDR 		(0xb8029224)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C20_VADDR 		(0xb8029228)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C22_VADDR 		(0xb802922c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C24_VADDR 		(0xb8029230)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C26_VADDR 		(0xb8029234)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C28_VADDR 		(0xb8029238)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C30_VADDR 		(0xb802923c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C32_VADDR 		(0xb8029240)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C34_VADDR 		(0xb8029244)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C36_VADDR 		(0xb8029248)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C38_VADDR 		(0xb802924c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C40_VADDR 		(0xb8029250)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C42_VADDR 		(0xb8029254)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C44_VADDR 		(0xb8029258)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C46_VADDR 		(0xb802925c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C48_VADDR 		(0xb8029260)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C50_VADDR 		(0xb8029264)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C52_VADDR 		(0xb8029268)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C54_VADDR 		(0xb802926c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C56_VADDR 		(0xb8029270)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C58_VADDR 		(0xb8029274)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C60_VADDR 		(0xb8029278)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB1_C62_VADDR 		(0xb802927c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C0_VADDR 		(0xb8029280)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C2_VADDR 		(0xb8029284)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C4_VADDR 		(0xb8029288)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C6_VADDR 		(0xb802928c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C8_VADDR 		(0xb8029290)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C10_VADDR 		(0xb8029294)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C12_VADDR 		(0xb8029298)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C14_VADDR 		(0xb802929c)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C16_VADDR 		(0xb80292a0)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C18_VADDR 		(0xb80292a4)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C20_VADDR 		(0xb80292a8)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C22_VADDR 		(0xb80292ac)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C24_VADDR 		(0xb80292b0)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C26_VADDR 		(0xb80292b4)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C28_VADDR 		(0xb80292b8)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C30_VADDR 		(0xb80292bc)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C32_VADDR 		(0xb80292c0)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C34_VADDR 		(0xb80292c4)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C36_VADDR 		(0xb80292c8)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C38_VADDR 		(0xb80292cc)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C40_VADDR 		(0xb80292d0)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C42_VADDR 		(0xb80292d4)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C44_VADDR 		(0xb80292d8)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C46_VADDR 		(0xb80292dc)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C48_VADDR 		(0xb80292e0)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C50_VADDR 		(0xb80292e4)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C52_VADDR 		(0xb80292e8)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C54_VADDR 		(0xb80292ec)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C56_VADDR 		(0xb80292f0)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C58_VADDR 		(0xb80292f4)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C60_VADDR 		(0xb80292f8)
#define  SCALEUP_DM_UZU_FIR_COEF_TAB2_C62_VADDR 		(0xb80292fc)
#define  SCALEUP_DS_UZU_CTRL_VADDR 		(0xb8029300)
#define  SCALEUP_DS_UZU_SCALE_HOR_FACTOR_VADDR 		(0xb8029304)
#define  SCALEUP_DS_UZU_SCALE_VER_FACTOR_VADDR 		(0xb8029308)
#define  SCALEUP_DS_UZU_INITIAL_VALUE_VADDR 		(0xb802930c)
#define  SCALEUP_DS_UZU_INPUT_SIZE_VADDR 		(0xb8029310)
#define  SCALEUP_DS_MEM_CRC_CTRL_VADDR 		(0xb8029314)
#define  SCALEUP_DS_MEM_CRC_RESULT_VADDR 		(0xb8029318)
#define  SCALEUP_DS_UZU_SUB_H_PARTIAL_DROP_VADDR 		(0xb802931c)
#define  SCALEUP_DS_UZU_SUB_V_PARTIAL_DROP_VADDR 		(0xb8029320)
#define  SCALEUP_DS_UZU_DB_CTRL_VADDR 		(0xb8029324)
#define  SCALEUP_DS_MEM_CRC_CTR2_VADDR 		(0xb8029328)
#define  SCALEUP_DS_MEM_L_DES_CRC_VADDR 		(0xb802932c)
#define  SCALEUP_DS_MEM_CRC_ERR_CNT_VADDR 		(0xb8029330)
#define  SCALEUP_DS_UZU_WCLR_VADDR 		(0xb8029334)
#define  SCALEUP_DS_UZU_FIR_COEF_VER_C0_C3_VADDR 		(0xb8029340)
#define  SCALEUP_DS_UZU_FIR_COEF_VER_C4_C7_VADDR 		(0xb8029344)
#define  SCALEUP_DS_UZU_FIR_COEF_VER_C8_C11_VADDR 		(0xb8029348)
#define  SCALEUP_DS_UZU_FIR_COEF_VER_C12_C15_VADDR 		(0xb802934c)
#define  SCALEUP_DS_UZU_FIR_COEF_HOR_C0_VADDR 		(0xb8029350)
#define  SCALEUP_DS_UZU_FIR_COEF_HOR_C4_VADDR 		(0xb8029354)
#define  SCALEUP_DS_UZU_FIR_COEF_HOR_C8_VADDR 		(0xb8029358)
#define  SCALEUP_DS_UZU_FIR_COEF_HOR_C12_VADDR 		(0xb802935c)
#define  SCALEUP_DS_UZU_BIST_0_VADDR 		(0xb8029360)
#define  SCALEUP_DS_UZU_BIST_1_VADDR 		(0xb8029364)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======SCALEUP register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18029000_31_14:18;
        RBus_UInt32  lr_black_en:1;
        RBus_UInt32  lr_black_sel:1;
        RBus_UInt32  in_black_en:1;
        RBus_UInt32  in_even_black:1;
        RBus_UInt32  out_black_en:1;
        RBus_UInt32  out_even_black:1;
        RBus_UInt32  patgen_sync:1;
        RBus_UInt32  patgen_mode:3;
        RBus_UInt32  patgen_lflag_en:1;
        RBus_UInt32  patgen_field:1;
        RBus_UInt32  patgen_sel:2;
    };
}d_uzu_globle_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_mode_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  ver_pr_mode:2;
        RBus_UInt32  wd_main_buf_udf_en:1;
        RBus_UInt32  irq_main_buf_udf_en:1;
        RBus_UInt32  bypassfornr:1;
        RBus_UInt32  v_y_consttab_sel:2;
        RBus_UInt32  v_c_consttab_sel:2;
        RBus_UInt32  h_y_consttab_sel:2;
        RBus_UInt32  h_c_consttab_sel:2;
        RBus_UInt32  hor8_table_sel:2;
        RBus_UInt32  d_3d_sel_en:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  in_fmt_conv:1;
        RBus_UInt32  conv_type:1;
        RBus_UInt32  v_y_table_sel:1;
        RBus_UInt32  v_c_table_sel:1;
        RBus_UInt32  h_y_table_sel:1;
        RBus_UInt32  h_c_table_sel:1;
        RBus_UInt32  in_fmt_dup:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  h_zoom_en:1;
    };
}dm_uzu_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  hor_factor:20;
    };
}dm_uzu_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  ver_factor:20;
    };
}dm_uzu_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  hor_delta1:13;
    };
}dm_uzu_hor_delta1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  hor_delta2:13;
    };
}dm_uzu_hor_delta2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  hor_segment1:11;
    };
}dm_uzu_hor_segment1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  hor_segment2:11;
    };
}dm_uzu_hor_segment2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  hor_segment3:12;
    };
}dm_uzu_hor_segment3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  hflip_en:1;
        RBus_UInt32  res2:12;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  ver_ini:8;
    };
}dm_uzu_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  hor_input_size:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  ver_input_size:12;
    };
}dm_uzu_input_size_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  level_flatness_coeff:1;
        RBus_UInt32  h4h8_blend_en:1;
        RBus_UInt32  dering_dbg_mode:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  h4h8_blend_range:2;
        RBus_UInt32  h4h8_blend_lowbound:8;
        RBus_UInt32  lpf_blend_mask_sel:1;
        RBus_UInt32  lpf_blend_en:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  lpf_blend_range:2;
        RBus_UInt32  lpf_blend_lowbound:8;
    };
}dm_uzu_8tap_dering_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  pk_mask_c0:5;
        RBus_UInt32  pk_mask_c1:4;
        RBus_UInt32  pk_mask_c2:4;
        RBus_UInt32  pk_en:1;
        RBus_UInt32  pk_coring:8;
        RBus_UInt32  pk_x1:8;
    };
}dm_uzu_peaking_coring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  pk_mask_c3:4;
        RBus_UInt32  pk_shiftbit:2;
        RBus_UInt32  pk_offset:8;
        RBus_UInt32  pk_lmtp:4;
        RBus_UInt32  pk_lmtn:4;
        RBus_UInt32  pk_g1:4;
        RBus_UInt32  pk_g2:4;
    };
}dm_uzu_peaking_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  vcti_type3_thd:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  vcti_gain:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  vcti_select:2;
        RBus_UInt32  vcti_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  conti:1;
        RBus_UInt32  start:1;
    };
}dm_mem_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mem_crc:32;
    };
}dm_mem_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  crc_3d_en:1;
    };
}mem_crc_ctr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_r_result:32;
    };
}mem_crc_r_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}mem_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}mem_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_crc_err_cnt:16;
        RBus_UInt32  l_crc_err_cnt:16;
    };
}mem_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  ch_sel:1;
        RBus_UInt32  conti:1;
        RBus_UInt32  start:1;
    };
}d_uzu_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  uzu_crc:32;
    };
}d_uzu_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  patgen_c0_y:8;
        RBus_UInt32  patgen_c0_cr:8;
        RBus_UInt32  patgen_c0_cb:8;
    };
}d_uzu_patgen_color0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  patgen_c1_y:8;
        RBus_UInt32  patgen_c1_cr:8;
        RBus_UInt32  patgen_c1_cb:8;
    };
}d_uzu_patgen_color1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  patgen_c2_y:8;
        RBus_UInt32  patgen_c2_cr:8;
        RBus_UInt32  patgen_c2_cb:8;
    };
}d_uzu_patgen_color2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  patgen_c3_y:8;
        RBus_UInt32  patgen_c3_cr:8;
        RBus_UInt32  patgen_c3_cb:8;
    };
}d_uzu_patgen_color3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_tog_num:5;
        RBus_UInt32  patgen_tog_sel:2;
        RBus_UInt32  patgen_lflag:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  patgen_width:22;
    };
}d_uzu_patgen_frame_toggle_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  patgen_lflag_1:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  patgen_width_1:22;
    };
}d_uzu_patgen_frame_toggle1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  patgen_lflag_2:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  patgen_width_2:22;
    };
}d_uzu_patgen_frame_toggle2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  patgen_lflag_3:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  patgen_width_3:22;
    };
}d_uzu_patgen_frame_toggle3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  ch_sel:1;
        RBus_UInt32  write_en:1;
        RBus_UInt32  read_en:1;
    };
}accessdata_ctrl_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  starty:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  startx:12;
    };
}accessdata_posctrl_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  y01:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  y00:10;
    };
}readdata_data_y1_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  y11:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  y10:10;
    };
}readdata_data_y2_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v00:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u00:10;
    };
}readdata_data_c1_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v01:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u01:10;
    };
}readdata_data_c2_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v10:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u10:10;
    };
}readdata_data_c3_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v11:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u11:10;
    };
}readdata_data_c4_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vcti_lpf_lbound2:10;
        RBus_UInt32  vcti_lpf_hbound2:10;
        RBus_UInt32  v:4;
        RBus_UInt32  u:4;
        RBus_UInt32  y:4;
    };
}writedata_data_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vcti_lpf_lbound1:10;
        RBus_UInt32  hor_m_front_drop:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  hor_m_back_drop:10;
    };
}dm_uzu_main_h_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vcti_lpf_hbound1:10;
        RBus_UInt32  vcti_low_pass_filter_en:1;
        RBus_UInt32  res1:5;
        RBus_UInt32  ver_m_front_drop:8;
        RBus_UInt32  ver_m_back_drop:8;
    };
}dm_uzu_main_v_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  hor_m_front_drop_odd:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  hor_m_back_drop_odd:10;
        RBus_UInt32  res3:1;
        RBus_UInt32  pixel_drop_mode:1;
        RBus_UInt32  res4:2;
    };
}dm_uzu_partial_drop_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adapt8_upbnd:8;
        RBus_UInt32  adapt8_sec3:8;
        RBus_UInt32  adapt8_sec2:8;
        RBus_UInt32  adapt8_sec1:8;
    };
}dm_uzu_main_adapt8tap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  db_mode:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  gain_flex_en:1;
        RBus_UInt32  ed_detect_en:1;
        RBus_UInt32  usm_en:1;
        RBus_UInt32  var_thd:8;
        RBus_UInt32  low_thd:8;
        RBus_UInt32  amount:8;
    };
}dm_usm_un_sharp_mask_filter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  min_shift:8;
        RBus_UInt32  max_shift:8;
    };
}dm_usm_upper_lower_bound_shift_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  diff_thd4:8;
        RBus_UInt32  diff_thd3:8;
        RBus_UInt32  diff_thd2:8;
        RBus_UInt32  diff_thd1:8;
    };
}dm_usm_blending_region_thd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  usm_hlpf_c3:6;
        RBus_UInt32  usm_hlpf_c2:4;
        RBus_UInt32  usm_hlpf_c1:4;
        RBus_UInt32  usm_hlpf_c0:4;
    };
}dm_usm_hlpf_coef_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_dif_thd3:8;
        RBus_UInt32  max_dif_thd2:8;
        RBus_UInt32  max_dif_thd1:8;
        RBus_UInt32  ed_dif_thd1:8;
    };
}dm_usm_edge_detect1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  amount_step3:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  amount_step2:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  amount_step1:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  amount_step0:6;
    };
}dm_usm_edge_detect2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  edge_detect_mode:1;
        RBus_UInt32  flat_ed_en:1;
        RBus_UInt32  flat_cnt_thd:4;
        RBus_UInt32  ed_dif_thd3:8;
        RBus_UInt32  ed_dif_thd2:8;
    };
}dm_usm_edge_detect3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy180290e0_31_4:28;
        RBus_UInt32  v6tap_table_sel:2;
        RBus_UInt32  v6tap_adapt_en:1;
        RBus_UInt32  v6tap_en:1;
    };
}dm_uzu_v6ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adaptv6_upbnd:8;
        RBus_UInt32  adaptv6_sec3:8;
        RBus_UInt32  adaptv6_sec2:8;
        RBus_UInt32  adaptv6_sec1:8;
    };
}dm_uzu_adaptv6ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  hor_ini_l:8;
        RBus_UInt32  ver_ini_l:8;
    };
}dm_uzu_initial_value_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  db_en:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_apply:1;
    };
}dm_uzu_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  buff_unf:1;
    };
}dm_uzu_wclr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  left_ydi:8;
        RBus_UInt32  left_udi:8;
        RBus_UInt32  left_vdi:8;
    };
}left_3d_ptg_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  left_h_saddr:8;
        RBus_UInt32  left_v_saddr:8;
        RBus_UInt32  left_h_limit:8;
        RBus_UInt32  left_v_limit:8;
    };
}left_3d_ptg_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  left_hsize:8;
        RBus_UInt32  left_vsize:8;
        RBus_UInt32  see_sadr_only_l:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  left_hstep:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  left_vstep:6;
    };
}left_3d_ptg_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  right_ydi:8;
        RBus_UInt32  right_udi:8;
        RBus_UInt32  right_vdi:8;
    };
}right_3d_ptg_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  right_h_saddr:8;
        RBus_UInt32  right_v_saddr:8;
        RBus_UInt32  right_h_limit:8;
        RBus_UInt32  right_v_limit:8;
    };
}right_3d_ptg_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  right_hsize:8;
        RBus_UInt32  right_vsize:8;
        RBus_UInt32  see_sadr_only_r:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  right_hstep:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  right_vstep:6;
    };
}right_3d_ptg_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  ptg_bg_ydi:8;
        RBus_UInt32  ptg_bg_udi:8;
        RBus_UInt32  ptg_bg_vdi:8;
    };
}ptg_3d_ctr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  coef_rw_sel:2;
    };
}coef_table_rw_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  coef_addr:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  coef_write:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  coef_tab_sel:1;
    };
}coef_table_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  coef0:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  coef1:12;
    };
}coef_table_ctl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  coef2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  coef3:12;
    };
}coef_table_ctl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  coef4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  coef5:12;
    };
}coef_table_ctl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  coef6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  coef7:12;
    };
}coef_table_ctl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  drf_bist_fail_11:1;
        RBus_UInt32  drf_bist_fail_10:1;
        RBus_UInt32  drf_bist_fail_9:1;
        RBus_UInt32  drf_bist_fail_8:1;
        RBus_UInt32  drf_bist_fail_7:1;
        RBus_UInt32  drf_bist_fail_6:1;
        RBus_UInt32  drf_bist_fail_5:1;
        RBus_UInt32  drf_bist_fail_4:1;
        RBus_UInt32  drf_bist_fail_3:1;
        RBus_UInt32  drf_bist_fail_2:1;
        RBus_UInt32  drf_bist_fail_1:1;
        RBus_UInt32  drf_bist_fail_0:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  bist_fail_11:1;
        RBus_UInt32  bist_fail_10:1;
        RBus_UInt32  bist_fail_9:1;
        RBus_UInt32  bist_fail_8:1;
        RBus_UInt32  bist_fail_7:1;
        RBus_UInt32  bist_fail_6:1;
        RBus_UInt32  bist_fail_5:1;
        RBus_UInt32  bist_fail_4:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_0:1;
    };
}dm_uzu_bist_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  ls_0:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  rme_11:1;
        RBus_UInt32  rme_10:1;
        RBus_UInt32  rme_9:1;
        RBus_UInt32  rme_8:1;
        RBus_UInt32  rme_7:1;
        RBus_UInt32  rme_6:1;
        RBus_UInt32  rme_5:1;
        RBus_UInt32  rme_4:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_0:1;
    };
}dm_uzu_bist_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_7:4;
        RBus_UInt32  rm_6:4;
        RBus_UInt32  rm_5:4;
        RBus_UInt32  rm_4:4;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_0:4;
    };
}dm_uzu_bist_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  rm_11:4;
        RBus_UInt32  rm_10:4;
        RBus_UInt32  rm_9:4;
        RBus_UInt32  rm_8:4;
    };
}dm_uzu_bist_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drf_bist_fail_0:1;
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  res1:24;
        RBus_UInt32  ls_0:1;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rm_0:4;
    };
}dm_uzu_coef_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c0:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c1:12;
    };
}dm_uzu_fir_coef_tab1_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c3:12;
    };
}dm_uzu_fir_coef_tab1_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c5:12;
    };
}dm_uzu_fir_coef_tab1_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c7:12;
    };
}dm_uzu_fir_coef_tab1_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c8:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c9:12;
    };
}dm_uzu_fir_coef_tab1_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c10:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c11:12;
    };
}dm_uzu_fir_coef_tab1_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c13:12;
    };
}dm_uzu_fir_coef_tab1_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c14:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c15:12;
    };
}dm_uzu_fir_coef_tab1_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c16:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c17:12;
    };
}dm_uzu_fir_coef_tab1_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c18:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c19:12;
    };
}dm_uzu_fir_coef_tab1_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c20:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c21:12;
    };
}dm_uzu_fir_coef_tab1_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c22:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c23:12;
    };
}dm_uzu_fir_coef_tab1_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c24:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c25:12;
    };
}dm_uzu_fir_coef_tab1_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c26:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c27:12;
    };
}dm_uzu_fir_coef_tab1_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c28:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c29:12;
    };
}dm_uzu_fir_coef_tab1_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c30:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c31:12;
    };
}dm_uzu_fir_coef_tab1_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c32:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c33:12;
    };
}dm_uzu_fir_coef_tab1_c32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c34:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c35:12;
    };
}dm_uzu_fir_coef_tab1_c34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c36:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c37:12;
    };
}dm_uzu_fir_coef_tab1_c36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c38:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c39:12;
    };
}dm_uzu_fir_coef_tab1_c38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c40:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c41:12;
    };
}dm_uzu_fir_coef_tab1_c40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c42:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c43:12;
    };
}dm_uzu_fir_coef_tab1_c42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c44:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c45:12;
    };
}dm_uzu_fir_coef_tab1_c44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c46:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c47:12;
    };
}dm_uzu_fir_coef_tab1_c46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c48:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c49:12;
    };
}dm_uzu_fir_coef_tab1_c48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c50:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c51:12;
    };
}dm_uzu_fir_coef_tab1_c50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c52:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c53:12;
    };
}dm_uzu_fir_coef_tab1_c52_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c54:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c55:12;
    };
}dm_uzu_fir_coef_tab1_c54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c56:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c57:12;
    };
}dm_uzu_fir_coef_tab1_c56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c58:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c59:12;
    };
}dm_uzu_fir_coef_tab1_c58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c60:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c61:12;
    };
}dm_uzu_fir_coef_tab1_c60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c62:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c63:12;
    };
}dm_uzu_fir_coef_tab1_c62_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c0:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c1:12;
    };
}dm_uzu_fir_coef_tab2_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c3:12;
    };
}dm_uzu_fir_coef_tab2_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c5:12;
    };
}dm_uzu_fir_coef_tab2_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c7:12;
    };
}dm_uzu_fir_coef_tab2_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c8:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c9:12;
    };
}dm_uzu_fir_coef_tab2_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c10:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c11:12;
    };
}dm_uzu_fir_coef_tab2_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c13:12;
    };
}dm_uzu_fir_coef_tab2_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c14:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c15:12;
    };
}dm_uzu_fir_coef_tab2_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c16:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c17:12;
    };
}dm_uzu_fir_coef_tab2_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c18:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c19:12;
    };
}dm_uzu_fir_coef_tab2_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c20:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c21:12;
    };
}dm_uzu_fir_coef_tab2_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c22:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c23:12;
    };
}dm_uzu_fir_coef_tab2_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c24:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c25:12;
    };
}dm_uzu_fir_coef_tab2_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c26:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c27:12;
    };
}dm_uzu_fir_coef_tab2_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c28:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c29:12;
    };
}dm_uzu_fir_coef_tab2_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c30:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c31:12;
    };
}dm_uzu_fir_coef_tab2_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c32:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c33:12;
    };
}dm_uzu_fir_coef_tab2_c32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c34:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c35:12;
    };
}dm_uzu_fir_coef_tab2_c34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c36:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c37:12;
    };
}dm_uzu_fir_coef_tab2_c36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c38:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c39:12;
    };
}dm_uzu_fir_coef_tab2_c38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c40:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c41:12;
    };
}dm_uzu_fir_coef_tab2_c40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c42:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c43:12;
    };
}dm_uzu_fir_coef_tab2_c42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c44:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c45:12;
    };
}dm_uzu_fir_coef_tab2_c44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c46:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c47:12;
    };
}dm_uzu_fir_coef_tab2_c46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c48:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c49:12;
    };
}dm_uzu_fir_coef_tab2_c48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c50:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c51:12;
    };
}dm_uzu_fir_coef_tab2_c50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c52:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c53:12;
    };
}dm_uzu_fir_coef_tab2_c52_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c54:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c55:12;
    };
}dm_uzu_fir_coef_tab2_c54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c56:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c57:12;
    };
}dm_uzu_fir_coef_tab2_c56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c58:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c59:12;
    };
}dm_uzu_fir_coef_tab2_c58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c60:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c61:12;
    };
}dm_uzu_fir_coef_tab2_c60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c62:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c63:12;
    };
}dm_uzu_fir_coef_tab2_c62_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  wd_sub_buf_udf_en:1;
        RBus_UInt32  irq_sub_buf_udf_en:1;
        RBus_UInt32  res2:16;
        RBus_UInt32  in_fmt_dup:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  in_fmt_conv:1;
        RBus_UInt32  conv_type:1;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  h_zoom_en:1;
    };
}ds_uzu_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  hor_factor:20;
    };
}ds_uzu_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  ver_factor:20;
    };
}ds_uzu_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  hflip_en:1;
        RBus_UInt32  res2:12;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  ver_ini:8;
    };
}ds_uzu_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  hor_input_size:13;
        RBus_UInt32  res2:4;
        RBus_UInt32  ver_input_size:12;
    };
}ds_uzu_input_size_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  conti:1;
        RBus_UInt32  start:1;
    };
}ds_mem_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mem_crc:32;
    };
}ds_mem_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  hor_s_front_drop:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  hor_s_back_drop:11;
    };
}ds_uzu_sub_h_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  ver_s_front_drop:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  ver_s_back_drop:9;
    };
}ds_uzu_sub_v_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  db_en:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_apply:1;
    };
}ds_uzu_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  auto_cmp_en:1;
    };
}ds_mem_crc_ctr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  des_crc:32;
    };
}ds_mem_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  crc_err_cnt:16;
    };
}ds_mem_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  buff_unf:1;
    };
}ds_uzu_wclr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c0:8;
        RBus_UInt32  ver_c1:8;
        RBus_UInt32  ver_c2:8;
        RBus_UInt32  ver_c3:8;
    };
}ds_uzu_fir_coef_ver_c0_c3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c4:8;
        RBus_UInt32  ver_c5:8;
        RBus_UInt32  ver_c6:8;
        RBus_UInt32  ver_c7:8;
    };
}ds_uzu_fir_coef_ver_c4_c7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c8:8;
        RBus_UInt32  ver_c9:8;
        RBus_UInt32  ver_c10:8;
        RBus_UInt32  ver_c11:8;
    };
}ds_uzu_fir_coef_ver_c8_c11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c12:8;
        RBus_UInt32  ver_c13:8;
        RBus_UInt32  ver_c14:8;
        RBus_UInt32  ver_c15:8;
    };
}ds_uzu_fir_coef_ver_c12_c15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c0:8;
        RBus_UInt32  hor_c1:8;
        RBus_UInt32  hor_c2:8;
        RBus_UInt32  hor_c3:8;
    };
}ds_uzu_fir_coef_hor_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c4:8;
        RBus_UInt32  hor_c5:8;
        RBus_UInt32  hor_c6:8;
        RBus_UInt32  hor_c7:8;
    };
}ds_uzu_fir_coef_hor_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c8:8;
        RBus_UInt32  hor_c9:8;
        RBus_UInt32  hor_c10:8;
        RBus_UInt32  hor_c11:8;
    };
}ds_uzu_fir_coef_hor_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c12:8;
        RBus_UInt32  hor_c13:8;
        RBus_UInt32  hor_c14:8;
        RBus_UInt32  hor_c15:8;
    };
}ds_uzu_fir_coef_hor_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_uzu_bist_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_0:4;
        RBus_UInt32  ls_3:1;
        RBus_UInt32  ls_2:1;
        RBus_UInt32  ls_1:1;
        RBus_UInt32  ls_0:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  drf_bist_fail_3:1;
        RBus_UInt32  drf_bist_fail_2:1;
        RBus_UInt32  drf_bist_fail_1:1;
        RBus_UInt32  drf_bist_fail_0:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_0:1;
    };
}ds_uzu_bist_1_RBUS;

#else //apply LITTLE_ENDIAN

//======SCALEUP register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_sel:2;
        RBus_UInt32  patgen_field:1;
        RBus_UInt32  patgen_lflag_en:1;
        RBus_UInt32  patgen_mode:3;
        RBus_UInt32  patgen_sync:1;
        RBus_UInt32  out_even_black:1;
        RBus_UInt32  out_black_en:1;
        RBus_UInt32  in_even_black:1;
        RBus_UInt32  in_black_en:1;
        RBus_UInt32  lr_black_sel:1;
        RBus_UInt32  lr_black_en:1;
        RBus_UInt32  dummy18029000_31_14:18;
    };
}d_uzu_globle_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_zoom_en:1;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  in_fmt_dup:1;
        RBus_UInt32  h_c_table_sel:1;
        RBus_UInt32  h_y_table_sel:1;
        RBus_UInt32  v_c_table_sel:1;
        RBus_UInt32  v_y_table_sel:1;
        RBus_UInt32  conv_type:1;
        RBus_UInt32  in_fmt_conv:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  d_3d_sel_en:1;
        RBus_UInt32  hor8_table_sel:2;
        RBus_UInt32  h_c_consttab_sel:2;
        RBus_UInt32  h_y_consttab_sel:2;
        RBus_UInt32  v_c_consttab_sel:2;
        RBus_UInt32  v_y_consttab_sel:2;
        RBus_UInt32  bypassfornr:1;
        RBus_UInt32  irq_main_buf_udf_en:1;
        RBus_UInt32  wd_main_buf_udf_en:1;
        RBus_UInt32  ver_pr_mode:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  hor_mode_sel:3;
    };
}dm_uzu_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_factor:20;
        RBus_UInt32  res1:12;
    };
}dm_uzu_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_factor:20;
        RBus_UInt32  res1:12;
    };
}dm_uzu_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_delta1:13;
        RBus_UInt32  res1:19;
    };
}dm_uzu_hor_delta1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_delta2:13;
        RBus_UInt32  res1:19;
    };
}dm_uzu_hor_delta2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_segment1:11;
        RBus_UInt32  res1:21;
    };
}dm_uzu_hor_segment1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_segment2:11;
        RBus_UInt32  res1:21;
    };
}dm_uzu_hor_segment2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_segment3:12;
        RBus_UInt32  res1:20;
    };
}dm_uzu_hor_segment3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_ini:8;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  res1:12;
        RBus_UInt32  hflip_en:1;
        RBus_UInt32  res2:3;
    };
}dm_uzu_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_input_size:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  hor_input_size:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_input_size_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lpf_blend_lowbound:8;
        RBus_UInt32  lpf_blend_range:2;
        RBus_UInt32  res1:4;
        RBus_UInt32  lpf_blend_en:1;
        RBus_UInt32  lpf_blend_mask_sel:1;
        RBus_UInt32  h4h8_blend_lowbound:8;
        RBus_UInt32  h4h8_blend_range:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  dering_dbg_mode:2;
        RBus_UInt32  h4h8_blend_en:1;
        RBus_UInt32  level_flatness_coeff:1;
    };
}dm_uzu_8tap_dering_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pk_x1:8;
        RBus_UInt32  pk_coring:8;
        RBus_UInt32  pk_en:1;
        RBus_UInt32  pk_mask_c2:4;
        RBus_UInt32  pk_mask_c1:4;
        RBus_UInt32  pk_mask_c0:5;
        RBus_UInt32  res1:2;
    };
}dm_uzu_peaking_coring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pk_g2:4;
        RBus_UInt32  pk_g1:4;
        RBus_UInt32  pk_lmtn:4;
        RBus_UInt32  pk_lmtp:4;
        RBus_UInt32  pk_offset:8;
        RBus_UInt32  pk_shiftbit:2;
        RBus_UInt32  pk_mask_c3:4;
        RBus_UInt32  res1:2;
    };
}dm_uzu_peaking_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  start:1;
        RBus_UInt32  conti:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  vcti_en:1;
        RBus_UInt32  vcti_select:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  vcti_gain:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  vcti_type3_thd:6;
        RBus_UInt32  res4:10;
    };
}dm_mem_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mem_crc:32;
    };
}dm_mem_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_3d_en:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  res1:29;
    };
}mem_crc_ctr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_r_result:32;
    };
}mem_crc_r_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}mem_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}mem_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_crc_err_cnt:16;
        RBus_UInt32  r_crc_err_cnt:16;
    };
}mem_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  start:1;
        RBus_UInt32  conti:1;
        RBus_UInt32  ch_sel:1;
        RBus_UInt32  res1:29;
    };
}d_uzu_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  uzu_crc:32;
    };
}d_uzu_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_c0_cb:8;
        RBus_UInt32  patgen_c0_cr:8;
        RBus_UInt32  patgen_c0_y:8;
        RBus_UInt32  res1:8;
    };
}d_uzu_patgen_color0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_c1_cb:8;
        RBus_UInt32  patgen_c1_cr:8;
        RBus_UInt32  patgen_c1_y:8;
        RBus_UInt32  res1:8;
    };
}d_uzu_patgen_color1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_c2_cb:8;
        RBus_UInt32  patgen_c2_cr:8;
        RBus_UInt32  patgen_c2_y:8;
        RBus_UInt32  res1:8;
    };
}d_uzu_patgen_color2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_c3_cb:8;
        RBus_UInt32  patgen_c3_cr:8;
        RBus_UInt32  patgen_c3_y:8;
        RBus_UInt32  res1:8;
    };
}d_uzu_patgen_color3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_width:22;
        RBus_UInt32  res1:2;
        RBus_UInt32  patgen_lflag:1;
        RBus_UInt32  patgen_tog_sel:2;
        RBus_UInt32  patgen_tog_num:5;
    };
}d_uzu_patgen_frame_toggle_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_width_1:22;
        RBus_UInt32  res1:2;
        RBus_UInt32  patgen_lflag_1:1;
        RBus_UInt32  res2:7;
    };
}d_uzu_patgen_frame_toggle1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_width_2:22;
        RBus_UInt32  res1:2;
        RBus_UInt32  patgen_lflag_2:1;
        RBus_UInt32  res2:7;
    };
}d_uzu_patgen_frame_toggle2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_width_3:22;
        RBus_UInt32  res1:2;
        RBus_UInt32  patgen_lflag_3:1;
        RBus_UInt32  res2:7;
    };
}d_uzu_patgen_frame_toggle3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  read_en:1;
        RBus_UInt32  write_en:1;
        RBus_UInt32  ch_sel:1;
        RBus_UInt32  res1:29;
    };
}accessdata_ctrl_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  startx:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  starty:12;
        RBus_UInt32  res2:4;
    };
}accessdata_posctrl_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y00:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  y01:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_y1_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y10:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  y11:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_y2_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u00:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v00:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c1_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u01:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v01:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c2_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u10:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v10:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c3_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u11:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v11:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c4_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y:4;
        RBus_UInt32  u:4;
        RBus_UInt32  v:4;
        RBus_UInt32  vcti_lpf_hbound2:10;
        RBus_UInt32  vcti_lpf_lbound2:10;
    };
}writedata_data_uzu_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_m_back_drop:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  hor_m_front_drop:10;
        RBus_UInt32  vcti_lpf_lbound1:10;
    };
}dm_uzu_main_h_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_m_back_drop:8;
        RBus_UInt32  ver_m_front_drop:8;
        RBus_UInt32  res1:5;
        RBus_UInt32  vcti_low_pass_filter_en:1;
        RBus_UInt32  vcti_lpf_hbound1:10;
    };
}dm_uzu_main_v_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  pixel_drop_mode:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  hor_m_back_drop_odd:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  hor_m_front_drop_odd:10;
        RBus_UInt32  res4:6;
    };
}dm_uzu_partial_drop_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adapt8_sec1:8;
        RBus_UInt32  adapt8_sec2:8;
        RBus_UInt32  adapt8_sec3:8;
        RBus_UInt32  adapt8_upbnd:8;
    };
}dm_uzu_main_adapt8tap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  amount:8;
        RBus_UInt32  low_thd:8;
        RBus_UInt32  var_thd:8;
        RBus_UInt32  usm_en:1;
        RBus_UInt32  ed_detect_en:1;
        RBus_UInt32  gain_flex_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  db_mode:4;
    };
}dm_usm_un_sharp_mask_filter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_shift:8;
        RBus_UInt32  min_shift:8;
        RBus_UInt32  res1:16;
    };
}dm_usm_upper_lower_bound_shift_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  diff_thd1:8;
        RBus_UInt32  diff_thd2:8;
        RBus_UInt32  diff_thd3:8;
        RBus_UInt32  diff_thd4:8;
    };
}dm_usm_blending_region_thd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  usm_hlpf_c0:4;
        RBus_UInt32  usm_hlpf_c1:4;
        RBus_UInt32  usm_hlpf_c2:4;
        RBus_UInt32  usm_hlpf_c3:6;
        RBus_UInt32  res1:14;
    };
}dm_usm_hlpf_coef_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ed_dif_thd1:8;
        RBus_UInt32  max_dif_thd1:8;
        RBus_UInt32  max_dif_thd2:8;
        RBus_UInt32  max_dif_thd3:8;
    };
}dm_usm_edge_detect1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  amount_step0:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  amount_step1:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  amount_step2:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  amount_step3:6;
        RBus_UInt32  res4:2;
    };
}dm_usm_edge_detect2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ed_dif_thd2:8;
        RBus_UInt32  ed_dif_thd3:8;
        RBus_UInt32  flat_cnt_thd:4;
        RBus_UInt32  flat_ed_en:1;
        RBus_UInt32  edge_detect_mode:1;
        RBus_UInt32  res1:10;
    };
}dm_usm_edge_detect3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v6tap_en:1;
        RBus_UInt32  v6tap_adapt_en:1;
        RBus_UInt32  v6tap_table_sel:2;
        RBus_UInt32  dummy180290e0_31:28;
    };
}dm_uzu_v6ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adaptv6_sec1:8;
        RBus_UInt32  adaptv6_sec2:8;
        RBus_UInt32  adaptv6_sec3:8;
        RBus_UInt32  adaptv6_upbnd:8;
    };
}dm_uzu_adaptv6ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_ini_l:8;
        RBus_UInt32  hor_ini_l:8;
        RBus_UInt32  res1:16;
    };
}dm_uzu_initial_value_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  db_apply:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_en:1;
        RBus_UInt32  res1:29;
    };
}dm_uzu_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  buff_unf:1;
        RBus_UInt32  res1:31;
    };
}dm_uzu_wclr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  left_vdi:8;
        RBus_UInt32  left_udi:8;
        RBus_UInt32  left_ydi:8;
        RBus_UInt32  res1:8;
    };
}left_3d_ptg_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  left_v_limit:8;
        RBus_UInt32  left_h_limit:8;
        RBus_UInt32  left_v_saddr:8;
        RBus_UInt32  left_h_saddr:8;
    };
}left_3d_ptg_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  left_vstep:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  left_hstep:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  see_sadr_only_l:1;
        RBus_UInt32  left_vsize:8;
        RBus_UInt32  left_hsize:8;
    };
}left_3d_ptg_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  right_vdi:8;
        RBus_UInt32  right_udi:8;
        RBus_UInt32  right_ydi:8;
        RBus_UInt32  res1:8;
    };
}right_3d_ptg_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  right_v_limit:8;
        RBus_UInt32  right_h_limit:8;
        RBus_UInt32  right_v_saddr:8;
        RBus_UInt32  right_h_saddr:8;
    };
}right_3d_ptg_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  right_vstep:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  right_hstep:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  see_sadr_only_r:1;
        RBus_UInt32  right_vsize:8;
        RBus_UInt32  right_hsize:8;
    };
}right_3d_ptg_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ptg_bg_vdi:8;
        RBus_UInt32  ptg_bg_udi:8;
        RBus_UInt32  ptg_bg_ydi:8;
        RBus_UInt32  res1:8;
    };
}ptg_3d_ctr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_rw_sel:2;
        RBus_UInt32  res1:30;
    };
}coef_table_rw_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef_tab_sel:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  coef_write:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  coef_addr:5;
        RBus_UInt32  res3:19;
    };
}coef_table_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef1:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  coef0:12;
        RBus_UInt32  res2:4;
    };
}coef_table_ctl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef3:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  coef2:12;
        RBus_UInt32  res2:4;
    };
}coef_table_ctl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef5:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  coef4:12;
        RBus_UInt32  res2:4;
    };
}coef_table_ctl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coef7:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  coef6:12;
        RBus_UInt32  res2:4;
    };
}coef_table_ctl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  bist_fail_4:1;
        RBus_UInt32  bist_fail_5:1;
        RBus_UInt32  bist_fail_6:1;
        RBus_UInt32  bist_fail_7:1;
        RBus_UInt32  bist_fail_8:1;
        RBus_UInt32  bist_fail_9:1;
        RBus_UInt32  bist_fail_10:1;
        RBus_UInt32  bist_fail_11:1;
        RBus_UInt32  res1:4;
        RBus_UInt32  drf_bist_fail_0:1;
        RBus_UInt32  drf_bist_fail_1:1;
        RBus_UInt32  drf_bist_fail_2:1;
        RBus_UInt32  drf_bist_fail_3:1;
        RBus_UInt32  drf_bist_fail_4:1;
        RBus_UInt32  drf_bist_fail_5:1;
        RBus_UInt32  drf_bist_fail_6:1;
        RBus_UInt32  drf_bist_fail_7:1;
        RBus_UInt32  drf_bist_fail_8:1;
        RBus_UInt32  drf_bist_fail_9:1;
        RBus_UInt32  drf_bist_fail_10:1;
        RBus_UInt32  drf_bist_fail_11:1;
        RBus_UInt32  res2:4;
    };
}dm_uzu_bist_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_4:1;
        RBus_UInt32  rme_5:1;
        RBus_UInt32  rme_6:1;
        RBus_UInt32  rme_7:1;
        RBus_UInt32  rme_8:1;
        RBus_UInt32  rme_9:1;
        RBus_UInt32  rme_10:1;
        RBus_UInt32  rme_11:1;
        RBus_UInt32  res1:4;
        RBus_UInt32  ls_0:1;
        RBus_UInt32  res2:15;
    };
}dm_uzu_bist_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_4:4;
        RBus_UInt32  rm_5:4;
        RBus_UInt32  rm_6:4;
        RBus_UInt32  rm_7:4;
    };
}dm_uzu_bist_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_8:4;
        RBus_UInt32  rm_9:4;
        RBus_UInt32  rm_10:4;
        RBus_UInt32  rm_11:4;
        RBus_UInt32  res1:16;
    };
}dm_uzu_bist_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  ls_0:1;
        RBus_UInt32  res1:24;
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  drf_bist_fail_0:1;
    };
}dm_uzu_coef_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c1:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c0:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c3:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c2:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c5:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c4:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c7:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c6:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c9:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c8:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c11:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c10:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c13:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c12:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c15:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c14:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c17:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c16:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c19:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c18:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c21:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c20:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c23:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c22:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c25:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c24:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c27:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c26:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c29:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c28:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c31:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c30:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c33:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c32:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c35:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c34:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c37:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c36:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c39:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c38:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c41:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c40:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c43:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c42:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c45:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c44:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c47:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c46:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c49:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c48:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c51:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c50:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c53:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c52:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c52_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c55:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c54:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c57:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c56:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c59:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c58:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c61:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c60:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c63:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c62:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab1_c62_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c1:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c0:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c3:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c2:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c5:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c4:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c7:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c6:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c9:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c8:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c11:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c10:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c13:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c12:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c15:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c14:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c17:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c16:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c19:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c18:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c21:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c20:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c23:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c22:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c25:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c24:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c27:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c26:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c29:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c28:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c31:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c30:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c33:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c32:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c35:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c34:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c37:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c36:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c39:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c38:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c41:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c40:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c43:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c42:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c45:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c44:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c47:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c46:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c49:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c48:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c51:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c50:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c53:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c52:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c52_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c55:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c54:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c57:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c56:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c59:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c58:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c61:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c60:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c63:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c62:12;
        RBus_UInt32  res2:4;
    };
}dm_uzu_fir_coef_tab2_c62_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_zoom_en:1;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  conv_type:1;
        RBus_UInt32  in_fmt_conv:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  in_fmt_dup:1;
        RBus_UInt32  res1:16;
        RBus_UInt32  irq_sub_buf_udf_en:1;
        RBus_UInt32  wd_sub_buf_udf_en:1;
        RBus_UInt32  res2:7;
    };
}ds_uzu_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_factor:20;
        RBus_UInt32  res1:12;
    };
}ds_uzu_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_factor:20;
        RBus_UInt32  res1:12;
    };
}ds_uzu_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_ini:8;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  res1:12;
        RBus_UInt32  hflip_en:1;
        RBus_UInt32  res2:3;
    };
}ds_uzu_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_input_size:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  hor_input_size:13;
        RBus_UInt32  res2:3;
    };
}ds_uzu_input_size_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  start:1;
        RBus_UInt32  conti:1;
        RBus_UInt32  res1:30;
    };
}ds_mem_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mem_crc:32;
    };
}ds_mem_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_s_back_drop:11;
        RBus_UInt32  res1:1;
        RBus_UInt32  hor_s_front_drop:11;
        RBus_UInt32  res2:9;
    };
}ds_uzu_sub_h_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_s_back_drop:9;
        RBus_UInt32  res1:7;
        RBus_UInt32  ver_s_front_drop:9;
        RBus_UInt32  res2:7;
    };
}ds_uzu_sub_v_partial_drop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  db_apply:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_en:1;
        RBus_UInt32  res1:29;
    };
}ds_uzu_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_cmp_en:1;
        RBus_UInt32  res1:31;
    };
}ds_mem_crc_ctr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  des_crc:32;
    };
}ds_mem_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_err_cnt:16;
        RBus_UInt32  res1:16;
    };
}ds_mem_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  buff_unf:1;
        RBus_UInt32  res1:31;
    };
}ds_uzu_wclr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c3:8;
        RBus_UInt32  ver_c2:8;
        RBus_UInt32  ver_c1:8;
        RBus_UInt32  ver_c0:8;
    };
}ds_uzu_fir_coef_ver_c0_c3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c7:8;
        RBus_UInt32  ver_c6:8;
        RBus_UInt32  ver_c5:8;
        RBus_UInt32  ver_c4:8;
    };
}ds_uzu_fir_coef_ver_c4_c7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c11:8;
        RBus_UInt32  ver_c10:8;
        RBus_UInt32  ver_c9:8;
        RBus_UInt32  ver_c8:8;
    };
}ds_uzu_fir_coef_ver_c8_c11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_c15:8;
        RBus_UInt32  ver_c14:8;
        RBus_UInt32  ver_c13:8;
        RBus_UInt32  ver_c12:8;
    };
}ds_uzu_fir_coef_ver_c12_c15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c3:8;
        RBus_UInt32  hor_c2:8;
        RBus_UInt32  hor_c1:8;
        RBus_UInt32  hor_c0:8;
    };
}ds_uzu_fir_coef_hor_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c7:8;
        RBus_UInt32  hor_c6:8;
        RBus_UInt32  hor_c5:8;
        RBus_UInt32  hor_c4:8;
    };
}ds_uzu_fir_coef_hor_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c11:8;
        RBus_UInt32  hor_c10:8;
        RBus_UInt32  hor_c9:8;
        RBus_UInt32  hor_c8:8;
    };
}ds_uzu_fir_coef_hor_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_c15:8;
        RBus_UInt32  hor_c14:8;
        RBus_UInt32  hor_c13:8;
        RBus_UInt32  hor_c12:8;
    };
}ds_uzu_fir_coef_hor_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_uzu_bist_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  drf_bist_fail_0:1;
        RBus_UInt32  drf_bist_fail_1:1;
        RBus_UInt32  drf_bist_fail_2:1;
        RBus_UInt32  drf_bist_fail_3:1;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  ls_0:1;
        RBus_UInt32  ls_1:1;
        RBus_UInt32  ls_2:1;
        RBus_UInt32  ls_3:1;
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_3:4;
    };
}ds_uzu_bist_1_RBUS;




#endif 


#endif 
