/**
* @file rbusSD_DITHERReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/2/24
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_SD_DITHER_REG_H_
#define _RBUS_SD_DITHER_REG_H_

#include "rbusTypes.h"




// SD_DITHER Register Address

#define SD_DITHER_SD_DITHER_CTRL1_VADDR           (0xb8023600)
#define SD_DITHER_SD_DITHER_TEMPORAL_OFFSET_TAB_1_VADDR  (0xb8023604)
#define SD_DITHER_SD_DITHER_TEMPORAL_OFFSET_TAB_2_VADDR  (0xb8023608)
#define SD_DITHER_DI_HSD_CTRL0_VADDR              (0xb802360c)
#define SD_DITHER_DI_HSD_SCALE_HOR_FACTOR_VADDR   (0xb8023610)
#define SD_DITHER_DI_HSD_INITIAL_VALUE_VADDR      (0xb8023614)
#define SD_DITHER_DI_HSD_HOR_DELTA1_VADDR         (0xb8023618)
#define SD_DITHER_DI_HSD_HOR_SEGMENT_VADDR        (0xb802361c)
#define SD_DITHER_DI_HSD_CRC_CTRL_VADDR           (0xb8023620)
#define SD_DITHER_DI_HSD_CRC_RESULT_LEFT_VADDR    (0xb8023624)
#define SD_DITHER_DI_HSD_CRC_RESULT_VADDR         (0xb8023628)
#define SD_DITHER_DI_HSD_L_DES_CRC_VADDR          (0xb802362c)
#define SD_DITHER_DI_HSD_R_DES_CRC_VADDR          (0xb8023630)
#define SD_DITHER_DI_HSD_CRC_ERR_CNT_VADDR        (0xb8023634)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C0_VADDR   (0xb8023638)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C2_VADDR   (0xb802363c)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C4_VADDR   (0xb8023640)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C6_VADDR   (0xb8023644)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C8_VADDR   (0xb8023648)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C10_VADDR  (0xb802364c)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C12_VADDR  (0xb8023650)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C14_VADDR  (0xb8023654)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C16_VADDR  (0xb8023658)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C18_VADDR  (0xb802365c)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C20_VADDR  (0xb8023660)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C22_VADDR  (0xb8023664)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C24_VADDR  (0xb8023668)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C26_VADDR  (0xb802366c)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C28_VADDR  (0xb8023670)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB1_C30_VADDR  (0xb8023674)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C0_VADDR   (0xb8023678)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C2_VADDR   (0xb802367c)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C4_VADDR   (0xb8023680)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C6_VADDR   (0xb8023684)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C8_VADDR   (0xb8023688)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C10_VADDR  (0xb802368c)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C12_VADDR  (0xb8023690)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C14_VADDR  (0xb8023694)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C16_VADDR  (0xb8023698)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C18_VADDR  (0xb802369c)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C20_VADDR  (0xb80236a0)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C22_VADDR  (0xb80236a4)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C24_VADDR  (0xb80236a8)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C26_VADDR  (0xb80236ac)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C28_VADDR  (0xb80236b0)
#define SD_DITHER_DI_UZD_FIR_COEF_TAB2_C30_VADDR  (0xb80236b4)
#define SD_DITHER_DI_UZD_DB_CTRL_VADDR            (0xb80236b8)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======SD_DITHER register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  uv_disable:1;
        RBus_UInt32  frame_count_by_3d_l_flag_inv:1;
        RBus_UInt32  frame_count_by_3d_flag_en:1;
        RBus_UInt32  dummy18023600_11_10:2;
        RBus_UInt32  ch1_field_odd_temporal_offset_select:1;
        RBus_UInt32  ch1_field_even_temporal_offset_select:1;
        RBus_UInt32  ch1_temporal_offset_separate_mode:1;
        RBus_UInt32  ch1_dithering_table_select:2;
        RBus_UInt32  ch1_temporal_enable:1;
        RBus_UInt32  ch1_value_sign:1;
        RBus_UInt32  ch1_dithering_mode:1;
        RBus_UInt32  ch1_v_modulation:1;
        RBus_UInt32  ch1_h_modulation:1;
    };
}sd_dither_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  temp_offset_15:2;
        RBus_UInt32  temp_offset_14:2;
        RBus_UInt32  temp_offset_13:2;
        RBus_UInt32  temp_offset_12:2;
        RBus_UInt32  temp_offset_11:2;
        RBus_UInt32  temp_offset_10:2;
        RBus_UInt32  temp_offset_9:2;
        RBus_UInt32  temp_offset_8:2;
        RBus_UInt32  temp_offset_7:2;
        RBus_UInt32  temp_offset_6:2;
        RBus_UInt32  temp_offset_5:2;
        RBus_UInt32  temp_offset_4:2;
        RBus_UInt32  temp_offset_3:2;
        RBus_UInt32  temp_offset_2:2;
        RBus_UInt32  temp_offset_1:2;
        RBus_UInt32  temp_offset_0:2;
    };
}sd_dither_temporal_offset_tab_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  temp_offset_15:2;
        RBus_UInt32  temp_offset_14:2;
        RBus_UInt32  temp_offset_13:2;
        RBus_UInt32  temp_offset_12:2;
        RBus_UInt32  temp_offset_11:2;
        RBus_UInt32  temp_offset_10:2;
        RBus_UInt32  temp_offset_9:2;
        RBus_UInt32  temp_offset_8:2;
        RBus_UInt32  temp_offset_7:2;
        RBus_UInt32  temp_offset_6:2;
        RBus_UInt32  temp_offset_5:2;
        RBus_UInt32  temp_offset_4:2;
        RBus_UInt32  temp_offset_3:2;
        RBus_UInt32  temp_offset_2:2;
        RBus_UInt32  temp_offset_1:2;
        RBus_UInt32  temp_offset_0:2;
    };
}sd_dither_temporal_offset_tab_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  h_3d_sel_en:1;
        RBus_UInt32  h_y_table_sel:1;
        RBus_UInt32  h_c_table_sel:1;
        RBus_UInt32  h_zoom_en:1;
    };
}di_hsd_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  hor_fac:25;
    };
}di_hsd_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  hor_ini_l:8;
        RBus_UInt32  hor_ini:8;
    };
}di_hsd_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  nl_d1:14;
    };
}di_hsd_hor_delta1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  nl_seg1:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  nl_seg2:12;
    };
}di_hsd_hor_segment_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  crc_3d_en:1;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  ch1_hsd_crc_conti:1;
        RBus_UInt32  ch1_hsd_crc_start:1;
    };
}di_hsd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_l_result:32;
    };
}di_hsd_crc_result_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_r_result:32;
    };
}di_hsd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}di_hsd_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}di_hsd_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_crc_err_cnt:16;
        RBus_UInt32  l_crc_err_cnt:16;
    };
}di_hsd_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c0:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c1:12;
    };
}di_uzd_fir_coef_tab1_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c3:12;
    };
}di_uzd_fir_coef_tab1_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c5:12;
    };
}di_uzd_fir_coef_tab1_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c7:12;
    };
}di_uzd_fir_coef_tab1_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c8:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c9:12;
    };
}di_uzd_fir_coef_tab1_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c10:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c11:12;
    };
}di_uzd_fir_coef_tab1_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c13:12;
    };
}di_uzd_fir_coef_tab1_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c14:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c15:12;
    };
}di_uzd_fir_coef_tab1_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c16:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c17:12;
    };
}di_uzd_fir_coef_tab1_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c18:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c19:12;
    };
}di_uzd_fir_coef_tab1_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c20:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c21:12;
    };
}di_uzd_fir_coef_tab1_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c22:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c23:12;
    };
}di_uzd_fir_coef_tab1_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c24:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c25:12;
    };
}di_uzd_fir_coef_tab1_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c26:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c27:12;
    };
}di_uzd_fir_coef_tab1_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c28:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c29:12;
    };
}di_uzd_fir_coef_tab1_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c30:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c31:12;
    };
}di_uzd_fir_coef_tab1_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c0:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c1:12;
    };
}di_uzd_fir_coef_tab2_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c3:12;
    };
}di_uzd_fir_coef_tab2_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c5:12;
    };
}di_uzd_fir_coef_tab2_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c7:12;
    };
}di_uzd_fir_coef_tab2_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c8:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c9:12;
    };
}di_uzd_fir_coef_tab2_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c10:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c11:12;
    };
}di_uzd_fir_coef_tab2_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c13:12;
    };
}di_uzd_fir_coef_tab2_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c14:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c15:12;
    };
}di_uzd_fir_coef_tab2_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c16:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c17:12;
    };
}di_uzd_fir_coef_tab2_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c18:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c19:12;
    };
}di_uzd_fir_coef_tab2_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c20:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c21:12;
    };
}di_uzd_fir_coef_tab2_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c22:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c23:12;
    };
}di_uzd_fir_coef_tab2_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c24:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c25:12;
    };
}di_uzd_fir_coef_tab2_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c26:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c27:12;
    };
}di_uzd_fir_coef_tab2_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c28:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c29:12;
    };
}di_uzd_fir_coef_tab2_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c30:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c31:12;
    };
}di_uzd_fir_coef_tab2_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  h_db_apply:1;
        RBus_UInt32  h_db_rd_sel:1;
        RBus_UInt32  h_db_en:1;
        RBus_UInt32  res2:4;
    };
}di_uzd_db_ctrl_RBUS;





#else //apply LITTLE_ENDIAN


//======SD_DITHER register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_h_modulation:1;
        RBus_UInt32  ch1_v_modulation:1;
        RBus_UInt32  ch1_dithering_mode:1;
        RBus_UInt32  ch1_value_sign:1;
        RBus_UInt32  ch1_temporal_enable:1;
        RBus_UInt32  ch1_dithering_table_select:2;
        RBus_UInt32  ch1_temporal_offset_separate_mode:1;
        RBus_UInt32  ch1_field_even_temporal_offset_select:1;
        RBus_UInt32  ch1_field_odd_temporal_offset_select:1;
        RBus_UInt32  dummy18023600_11_10:2;
        RBus_UInt32  frame_count_by_3d_flag_en:1;
        RBus_UInt32  frame_count_by_3d_l_flag_inv:1;
        RBus_UInt32  uv_disable:1;
        RBus_UInt32  res1:17;
    };
}sd_dither_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  temp_offset_0:2;
        RBus_UInt32  temp_offset_1:2;
        RBus_UInt32  temp_offset_2:2;
        RBus_UInt32  temp_offset_3:2;
        RBus_UInt32  temp_offset_4:2;
        RBus_UInt32  temp_offset_5:2;
        RBus_UInt32  temp_offset_6:2;
        RBus_UInt32  temp_offset_7:2;
        RBus_UInt32  temp_offset_8:2;
        RBus_UInt32  temp_offset_9:2;
        RBus_UInt32  temp_offset_10:2;
        RBus_UInt32  temp_offset_11:2;
        RBus_UInt32  temp_offset_12:2;
        RBus_UInt32  temp_offset_13:2;
        RBus_UInt32  temp_offset_14:2;
        RBus_UInt32  temp_offset_15:2;
    };
}sd_dither_temporal_offset_tab_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  temp_offset_0:2;
        RBus_UInt32  temp_offset_1:2;
        RBus_UInt32  temp_offset_2:2;
        RBus_UInt32  temp_offset_3:2;
        RBus_UInt32  temp_offset_4:2;
        RBus_UInt32  temp_offset_5:2;
        RBus_UInt32  temp_offset_6:2;
        RBus_UInt32  temp_offset_7:2;
        RBus_UInt32  temp_offset_8:2;
        RBus_UInt32  temp_offset_9:2;
        RBus_UInt32  temp_offset_10:2;
        RBus_UInt32  temp_offset_11:2;
        RBus_UInt32  temp_offset_12:2;
        RBus_UInt32  temp_offset_13:2;
        RBus_UInt32  temp_offset_14:2;
        RBus_UInt32  temp_offset_15:2;
    };
}sd_dither_temporal_offset_tab_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_zoom_en:1;
        RBus_UInt32  h_c_table_sel:1;
        RBus_UInt32  h_y_table_sel:1;
        RBus_UInt32  h_3d_sel_en:1;
        RBus_UInt32  res1:28;
    };
}di_hsd_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_fac:25;
        RBus_UInt32  res1:7;
    };
}di_hsd_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  hor_ini_l:8;
        RBus_UInt32  res1:16;
    };
}di_hsd_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  nl_d1:14;
        RBus_UInt32  res1:18;
    };
}di_hsd_hor_delta1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  nl_seg2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  nl_seg1:12;
        RBus_UInt32  res1:4;
    };
}di_hsd_hor_segment_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_start:1;
        RBus_UInt32  ch1_hsd_crc_conti:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  crc_3d_en:1;
        RBus_UInt32  res1:27;
    };
}di_hsd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_l_result:32;
    };
}di_hsd_crc_result_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_r_result:32;
    };
}di_hsd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}di_hsd_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}di_hsd_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_crc_err_cnt:16;
        RBus_UInt32  r_crc_err_cnt:16;
    };
}di_hsd_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c1:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c0:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c3:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c2:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c5:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c4:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c7:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c6:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c9:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c8:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c11:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c10:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c13:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c12:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c15:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c14:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c17:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c16:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c19:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c18:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c21:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c20:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c23:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c22:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c25:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c24:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c27:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c26:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c29:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c28:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c31:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c30:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab1_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c1:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c0:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c3:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c2:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c5:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c4:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c7:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c6:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c9:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c8:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c11:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c10:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c13:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c12:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c15:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c14:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c17:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c16:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c19:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c18:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c21:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c20:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c23:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c22:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c25:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c24:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c27:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c26:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c29:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c28:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c31:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c30:12;
        RBus_UInt32  res1:4;
    };
}di_uzd_fir_coef_tab2_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:4;
        RBus_UInt32  h_db_en:1;
        RBus_UInt32  h_db_rd_sel:1;
        RBus_UInt32  h_db_apply:1;
        RBus_UInt32  res1:25;
    };
}di_uzd_db_ctrl_RBUS;


#endif







#endif //_RBUS_SD_DITHER_REG_H_

