/**
* @file rbusColor_dccReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/11/25
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_COLOR_DCC_REG_H_
#define _RBUS_COLOR_DCC_REG_H_

#include "rbusTypes.h"



//  COLOR_DCC Register Address



#define  COLOR_DCC_D_DCC_CTRL_VADDR 		(0xb802e400)
#define  COLOR_DCC_DCC_CTRL_COLOR_VADDR 		(0xb802e404)
#define  COLOR_DCC_DCC_CTRL_COLOR_MAIN_0_VADDR 		(0xb802e550)
#define  COLOR_DCC_DCC_CTRL_COLOR_MAIN_1_VADDR 		(0xb802e554)
#define  COLOR_DCC_DCC_CTRL_COLOR_SUB_0_VADDR 		(0xb802e558)
#define  COLOR_DCC_DCC_CTRL_COLOR_SUB_1_VADDR 		(0xb802e55c)
#define  COLOR_DCC_DCC_CTRL_LUMA_VADDR 		(0xb802e408)
#define  COLOR_DCC_DM_INTERP_DATA_00_VADDR 		(0xb802e410)
#define  COLOR_DCC_DM_INTERP_DATA_04_VADDR 		(0xb802e414)
#define  COLOR_DCC_DM_INTERP_DATA_08_VADDR 		(0xb802e418)
#define  COLOR_DCC_DM_INTERP_DATA_0C_VADDR 		(0xb802e41c)
#define  COLOR_DCC_DM_INTERP_DATA_10_VADDR 		(0xb802e420)
#define  COLOR_DCC_DM_INTERP_DATA_14_VADDR 		(0xb802e424)
#define  COLOR_DCC_DM_INTERP_DATA_18_VADDR 		(0xb802e428)
#define  COLOR_DCC_DM_INTERP_DATA_1C_VADDR 		(0xb802e42c)
#define  COLOR_DCC_DM_INTERP_DATA_40_VADDR 		(0xb802e450)
#define  COLOR_DCC_DM_INTERP_DATA_44_VADDR 		(0xb802e454)
#define  COLOR_DCC_DM_INTERP_DATA_48_VADDR 		(0xb802e458)
#define  COLOR_DCC_DM_INTERP_DATA_4C_VADDR 		(0xb802e45c)
#define  COLOR_DCC_DM_INTERP_DATA_50_VADDR 		(0xb802e460)
#define  COLOR_DCC_DM_INTERP_DATA_54_VADDR 		(0xb802e464)
#define  COLOR_DCC_DM_INTERP_DATA_58_VADDR 		(0xb802e468)
#define  COLOR_DCC_DM_INTERP_DATA_5C_VADDR 		(0xb802e46c)
#define  COLOR_DCC_DM_INTERP_DATA_20_VADDR 		(0xb802e430)
#define  COLOR_DCC_DM_INTERP_DATA_24_VADDR 		(0xb802e434)
#define  COLOR_DCC_DM_INTERP_DATA_28_VADDR 		(0xb802e438)
#define  COLOR_DCC_DM_INTERP_DATA_2C_VADDR 		(0xb802e43c)
#define  COLOR_DCC_DM_INTERP_DATA_30_VADDR 		(0xb802e440)
#define  COLOR_DCC_DM_INTERP_DATA_34_VADDR 		(0xb802e444)
#define  COLOR_DCC_DM_INTERP_DATA_38_VADDR 		(0xb802e448)
#define  COLOR_DCC_DM_INTERP_DATA_3C_VADDR 		(0xb802e44c)
#define  COLOR_DCC_DM_INTERP_DATA_60_VADDR 		(0xb802e470)
#define  COLOR_DCC_DM_INTERP_DATA_64_VADDR 		(0xb802e474)
#define  COLOR_DCC_DM_INTERP_DATA_68_VADDR 		(0xb802e478)
#define  COLOR_DCC_DM_INTERP_DATA_6C_VADDR 		(0xb802e47c)
#define  COLOR_DCC_DM_INTERP_DATA_70_VADDR 		(0xb802e480)
#define  COLOR_DCC_DM_INTERP_DATA_74_VADDR 		(0xb802e484)
#define  COLOR_DCC_DM_INTERP_DATA_78_VADDR 		(0xb802e488)
#define  COLOR_DCC_DM_INTERP_DATA_7C_VADDR 		(0xb802e48c)
#define  COLOR_DCC_DM_NC_BLEND_DATA_80_VADDR 		(0xb802e490)
#define  COLOR_DCC_DM_NC_ZERO_GAIN_VADDR 		(0xb802e494)
#define  COLOR_DCC_D_DCC_DB_CTRL_VADDR 		(0xb802e498)
#define  COLOR_DCC_D_DCC_SKIN_TONE_EN_VADDR 		(0xb802e560)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_CENTER_0_VADDR 		(0xb802e564)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_RANGE_0_VADDR 		(0xb802e568)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_CENTER_1_VADDR 		(0xb802e56c)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_RANGE_1_VADDR 		(0xb802e570)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_CENTER_2_VADDR 		(0xb802e574)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_RANGE_2_VADDR 		(0xb802e578)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_CENTER_3_VADDR 		(0xb802e57c)
#define  COLOR_DCC_D_DCC_SKIN_TONE_YUV_RANGE_3_VADDR 		(0xb802e580)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT0_0_VADDR 		(0xb802e584)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT0_1_VADDR 		(0xb802e588)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT1_0_VADDR 		(0xb802e58c)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT1_1_VADDR 		(0xb802e590)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT2_0_VADDR 		(0xb802e594)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT2_1_VADDR 		(0xb802e598)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT3_0_VADDR 		(0xb802e59c)
#define  COLOR_DCC_D_DCC_SKIN_TONE_SEGMENT3_1_VADDR 		(0xb802e5a0)
#define  COLOR_DCC_DS_INTERP_DATA_00_VADDR 		(0xb802e4b0)
#define  COLOR_DCC_DS_INTERP_DATA_04_VADDR 		(0xb802e4b4)
#define  COLOR_DCC_DS_INTERP_DATA_08_VADDR 		(0xb802e4b8)
#define  COLOR_DCC_DS_INTERP_DATA_0C_VADDR 		(0xb802e4bc)
#define  COLOR_DCC_DS_INTERP_DATA_10_VADDR 		(0xb802e4c0)
#define  COLOR_DCC_DS_INTERP_DATA_14_VADDR 		(0xb802e4c4)
#define  COLOR_DCC_DS_INTERP_DATA_18_VADDR 		(0xb802e4c8)
#define  COLOR_DCC_DS_INTERP_DATA_1C_VADDR 		(0xb802e4cc)
#define  COLOR_DCC_DS_INTERP_DATA_40_VADDR 		(0xb802e4f0)
#define  COLOR_DCC_DS_INTERP_DATA_44_VADDR 		(0xb802e4f4)
#define  COLOR_DCC_DS_INTERP_DATA_48_VADDR 		(0xb802e4f8)
#define  COLOR_DCC_DS_INTERP_DATA_4C_VADDR 		(0xb802e4fc)
#define  COLOR_DCC_DS_INTERP_DATA_50_VADDR 		(0xb802e500)
#define  COLOR_DCC_DS_INTERP_DATA_54_VADDR 		(0xb802e504)
#define  COLOR_DCC_DS_INTERP_DATA_58_VADDR 		(0xb802e508)
#define  COLOR_DCC_DS_INTERP_DATA_5C_VADDR 		(0xb802e50c)
#define  COLOR_DCC_DS_INTERP_DATA_20_VADDR 		(0xb802e4d0)
#define  COLOR_DCC_DS_INTERP_DATA_24_VADDR 		(0xb802e4d4)
#define  COLOR_DCC_DS_INTERP_DATA_28_VADDR 		(0xb802e4d8)
#define  COLOR_DCC_DS_INTERP_DATA_2C_VADDR 		(0xb802e4dc)
#define  COLOR_DCC_DS_INTERP_DATA_30_VADDR 		(0xb802e4e0)
#define  COLOR_DCC_DS_INTERP_DATA_34_VADDR 		(0xb802e4e4)
#define  COLOR_DCC_DS_INTERP_DATA_38_VADDR 		(0xb802e4e8)
#define  COLOR_DCC_DS_INTERP_DATA_3C_VADDR 		(0xb802e4ec)
#define  COLOR_DCC_DS_INTERP_DATA_60_VADDR 		(0xb802e510)
#define  COLOR_DCC_DS_INTERP_DATA_64_VADDR 		(0xb802e514)
#define  COLOR_DCC_DS_INTERP_DATA_68_VADDR 		(0xb802e518)
#define  COLOR_DCC_DS_INTERP_DATA_6C_VADDR 		(0xb802e51c)
#define  COLOR_DCC_DS_INTERP_DATA_70_VADDR 		(0xb802e520)
#define  COLOR_DCC_DS_INTERP_DATA_74_VADDR 		(0xb802e524)
#define  COLOR_DCC_DS_INTERP_DATA_78_VADDR 		(0xb802e528)
#define  COLOR_DCC_DS_INTERP_DATA_7C_VADDR 		(0xb802e52c)
#define  COLOR_DCC_DS_NC_BLEND_DATA_80_VADDR 		(0xb802e530)
#define  COLOR_DCC_DS_NC_ZERO_GAIN_VADDR 		(0xb802e534)
#define  COLOR_DCC_D_DCC_DUMMY_0_VADDR 		(0xb802e53c)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======COLOR_DCC register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  dcc_overlay:1;
        RBus_UInt32  dcc_sub_tab_sel:2;
        RBus_UInt32  dcc_main_tab_sel:2;
        RBus_UInt32  res2:11;
        RBus_UInt32  sub_table_sel:1;
        RBus_UInt32  main_table_sel:1;
        RBus_UInt32  res3:5;
        RBus_UInt32  sub_dcc_mode:2;
        RBus_UInt32  main_dcc_mode:2;
        RBus_UInt32  res4:2;
    };
}d_dcc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_main_seg8:5;
        RBus_UInt32  res1:1;
        RBus_UInt32  chroma_gain_limit_main:10;
        RBus_UInt32  chroma_gain_sub_seg8:5;
        RBus_UInt32  res2:1;
        RBus_UInt32  chroma_gain_limit_sub:10;
    };
}dcc_ctrl_color_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_main_intp_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  chroma_gain_main_seg3:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_main_seg2:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_main_seg1:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  chroma_gain_main_seg0:5;
    };
}dcc_ctrl_color_main_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  chroma_gain_main_seg7:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_main_seg6:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_main_seg5:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  chroma_gain_main_seg4:5;
    };
}dcc_ctrl_color_main_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_sub_intp_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  chroma_gain_sub_seg3:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_sub_seg2:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_sub_seg1:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  chroma_gain_sub_seg0:5;
    };
}dcc_ctrl_color_sub_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  chroma_gain_sub_seg7:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_sub_seg6:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_sub_seg5:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  chroma_gain_sub_seg4:5;
    };
}dcc_ctrl_color_sub_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  luma_offset_main:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  luma_offset_sub:8;
    };
}dcc_ctrl_luma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_0_hb:2;
        RBus_UInt32  m_base_0_0_lb:8;
        RBus_UInt32  m_g0_0_0:8;
        RBus_UInt32  m_g1_0_0:8;
    };
}dm_interp_data_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_1_hb:2;
        RBus_UInt32  m_base_0_1_lb:8;
        RBus_UInt32  m_g0_0_1:8;
        RBus_UInt32  m_g1_0_1:8;
    };
}dm_interp_data_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_2_hb:2;
        RBus_UInt32  m_base_0_2_lb:8;
        RBus_UInt32  m_g0_0_2:8;
        RBus_UInt32  m_g1_0_2:8;
    };
}dm_interp_data_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_3_hb:2;
        RBus_UInt32  m_base_0_3_lb:8;
        RBus_UInt32  m_g0_0_3:8;
        RBus_UInt32  m_g1_0_3:8;
    };
}dm_interp_data_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_4_hb:2;
        RBus_UInt32  m_base_0_4_lb:8;
        RBus_UInt32  m_g0_0_4:8;
        RBus_UInt32  m_g1_0_4:8;
    };
}dm_interp_data_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_5_hb:2;
        RBus_UInt32  m_base_0_5_lb:8;
        RBus_UInt32  m_g0_0_5:8;
        RBus_UInt32  m_g1_0_5:8;
    };
}dm_interp_data_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_6_hb:2;
        RBus_UInt32  m_base_0_6_lb:8;
        RBus_UInt32  m_g0_0_6:8;
        RBus_UInt32  m_g1_0_6:8;
    };
}dm_interp_data_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_7_hb:2;
        RBus_UInt32  m_base_0_7_lb:8;
        RBus_UInt32  m_g0_0_7:8;
        RBus_UInt32  m_g1_0_7:8;
    };
}dm_interp_data_1c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_8_hb:2;
        RBus_UInt32  m_base_0_8_lb:8;
        RBus_UInt32  m_g0_0_8:8;
        RBus_UInt32  m_g1_0_8:8;
    };
}dm_interp_data_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_9_hb:2;
        RBus_UInt32  m_base_0_9_lb:8;
        RBus_UInt32  m_g0_0_9:8;
        RBus_UInt32  m_g1_0_9:8;
    };
}dm_interp_data_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_a_hb:2;
        RBus_UInt32  m_base_0_a_lb:8;
        RBus_UInt32  m_g0_0_a:8;
        RBus_UInt32  m_g1_0_a:8;
    };
}dm_interp_data_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_b_hb:2;
        RBus_UInt32  m_base_0_b_lb:8;
        RBus_UInt32  m_g0_0_b:8;
        RBus_UInt32  m_g1_0_b:8;
    };
}dm_interp_data_4c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_c_hb:2;
        RBus_UInt32  m_base_0_c_lb:8;
        RBus_UInt32  m_g0_0_c:8;
        RBus_UInt32  m_g1_0_c:8;
    };
}dm_interp_data_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_d_hb:2;
        RBus_UInt32  m_base_0_d_lb:8;
        RBus_UInt32  m_g0_0_d:8;
        RBus_UInt32  m_g1_0_d:8;
    };
}dm_interp_data_54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_e_hb:2;
        RBus_UInt32  m_base_0_e_lb:8;
        RBus_UInt32  m_g0_0_e:8;
        RBus_UInt32  m_g1_0_e:8;
    };
}dm_interp_data_58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_0_f_hb:2;
        RBus_UInt32  m_base_0_f_lb:8;
        RBus_UInt32  m_g0_0_f:8;
        RBus_UInt32  m_g1_0_f:8;
    };
}dm_interp_data_5c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_0_hb:2;
        RBus_UInt32  m_base_1_0_lb:8;
        RBus_UInt32  m_g0_1_0:8;
        RBus_UInt32  m_g1_1_0:8;
    };
}dm_interp_data_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_1_hb:2;
        RBus_UInt32  m_base_1_1_lb:8;
        RBus_UInt32  m_g0_1_1:8;
        RBus_UInt32  m_g1_1_1:8;
    };
}dm_interp_data_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_2_hb:2;
        RBus_UInt32  m_base_1_2_lb:8;
        RBus_UInt32  m_g0_1_2:8;
        RBus_UInt32  m_g1_1_2:8;
    };
}dm_interp_data_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_3_hb:2;
        RBus_UInt32  m_base_1_3_lb:8;
        RBus_UInt32  m_g0_1_3:8;
        RBus_UInt32  m_g1_1_3:8;
    };
}dm_interp_data_2c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_4_hb:2;
        RBus_UInt32  m_base_1_4_lb:8;
        RBus_UInt32  m_g0_1_4:8;
        RBus_UInt32  m_g1_1_4:8;
    };
}dm_interp_data_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_5_hb:2;
        RBus_UInt32  m_base_1_5_lb:8;
        RBus_UInt32  m_g0_1_5:8;
        RBus_UInt32  m_g1_1_5:8;
    };
}dm_interp_data_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_6_hb:2;
        RBus_UInt32  m_base_1_6_lb:8;
        RBus_UInt32  m_g0_1_6:8;
        RBus_UInt32  m_g1_1_6:8;
    };
}dm_interp_data_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_7_hb:2;
        RBus_UInt32  m_base_1_7_lb:8;
        RBus_UInt32  m_g0_1_7:8;
        RBus_UInt32  m_g1_1_7:8;
    };
}dm_interp_data_3c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_8_hb:2;
        RBus_UInt32  m_base_1_8_lb:8;
        RBus_UInt32  m_g0_1_8:8;
        RBus_UInt32  m_g1_1_8:8;
    };
}dm_interp_data_60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_9_hb:2;
        RBus_UInt32  m_base_1_9_lb:8;
        RBus_UInt32  m_g0_1_9:8;
        RBus_UInt32  m_g1_1_9:8;
    };
}dm_interp_data_64_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_a_hb:2;
        RBus_UInt32  m_base_1_a_lb:8;
        RBus_UInt32  m_g0_1_a:8;
        RBus_UInt32  m_g1_1_a:8;
    };
}dm_interp_data_68_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_b_hb:2;
        RBus_UInt32  m_base_1_b_lb:8;
        RBus_UInt32  m_g0_1_b:8;
        RBus_UInt32  m_g1_1_b:8;
    };
}dm_interp_data_6c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_c_hb:2;
        RBus_UInt32  m_base_1_c_lb:8;
        RBus_UInt32  m_g0_1_c:8;
        RBus_UInt32  m_g1_1_c:8;
    };
}dm_interp_data_70_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_d_hb:2;
        RBus_UInt32  m_base_1_d_lb:8;
        RBus_UInt32  m_g0_1_d:8;
        RBus_UInt32  m_g1_1_d:8;
    };
}dm_interp_data_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_e_hb:2;
        RBus_UInt32  m_base_1_e_lb:8;
        RBus_UInt32  m_g0_1_e:8;
        RBus_UInt32  m_g1_1_e:8;
    };
}dm_interp_data_78_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  m_base_1_f_hb:2;
        RBus_UInt32  m_base_1_f_lb:8;
        RBus_UInt32  m_g0_1_f:8;
        RBus_UInt32  m_g1_1_f:8;
    };
}dm_interp_data_7c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_alpha_h_1:8;
        RBus_UInt32  m_alpha_l_1:8;
        RBus_UInt32  m_alpha_h_0:8;
        RBus_UInt32  m_alpha_l_0:8;
    };
}dm_nc_blend_data_80_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  m_zero_gain:22;
    };
}dm_nc_zero_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  db_en:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_apply:1;
    };
}d_dcc_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  y_blending_debug_mode_en:1;
        RBus_UInt32  y_blending_debug_mode_sel:1;
        RBus_UInt32  res2:7;
        RBus_UInt32  y_blending_mode:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  y_blending_reg0_en:1;
        RBus_UInt32  y_blending_reg1_en:1;
        RBus_UInt32  y_blending_reg2_en:1;
        RBus_UInt32  y_blending_reg3_en:1;
        RBus_UInt32  y_blending_en:1;
    };
}d_dcc_skin_tone_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_0_y_center:10;
        RBus_UInt32  y_blending_0_u_center:10;
        RBus_UInt32  y_blending_0_v_center:10;
    };
}d_dcc_skin_tone_yuv_center_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  y_blending_0_y_range:4;
        RBus_UInt32  y_blending_0_u_range:4;
        RBus_UInt32  y_blending_0_v_range:4;
    };
}d_dcc_skin_tone_yuv_range_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_1_y_center:10;
        RBus_UInt32  y_blending_1_u_center:10;
        RBus_UInt32  y_blending_1_v_center:10;
    };
}d_dcc_skin_tone_yuv_center_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  y_blending_1_y_range:4;
        RBus_UInt32  y_blending_1_u_range:4;
        RBus_UInt32  y_blending_1_v_range:4;
    };
}d_dcc_skin_tone_yuv_range_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_2_y_center:10;
        RBus_UInt32  y_blending_2_u_center:10;
        RBus_UInt32  y_blending_2_v_center:10;
    };
}d_dcc_skin_tone_yuv_center_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  y_blending_2_y_range:4;
        RBus_UInt32  y_blending_2_u_range:4;
        RBus_UInt32  y_blending_2_v_range:4;
    };
}d_dcc_skin_tone_yuv_range_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_3_y_center:10;
        RBus_UInt32  y_blending_3_u_center:10;
        RBus_UInt32  y_blending_3_v_center:10;
    };
}d_dcc_skin_tone_yuv_center_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  y_blending_3_y_range:4;
        RBus_UInt32  y_blending_3_u_range:4;
        RBus_UInt32  y_blending_3_v_range:4;
    };
}d_dcc_skin_tone_yuv_range_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_0_ratio_0:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_0_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_0_ratio_2:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_0_ratio_3:6;
    };
}d_dcc_skin_tone_segment0_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_0_ratio_4:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_0_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_0_ratio_6:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_0_ratio_7:6;
    };
}d_dcc_skin_tone_segment0_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_1_ratio_0:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_1_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_1_ratio_2:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_1_ratio_3:6;
    };
}d_dcc_skin_tone_segment1_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_1_ratio_4:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_1_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_1_ratio_6:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_1_ratio_7:6;
    };
}d_dcc_skin_tone_segment1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_2_ratio_0:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_2_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_2_ratio_2:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_2_ratio_3:6;
    };
}d_dcc_skin_tone_segment2_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_2_ratio_4:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_2_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_2_ratio_6:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_2_ratio_7:6;
    };
}d_dcc_skin_tone_segment2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_3_ratio_0:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_3_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_3_ratio_2:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_3_ratio_3:6;
    };
}d_dcc_skin_tone_segment3_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_3_ratio_4:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_3_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_3_ratio_6:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  y_blending_3_ratio_7:6;
    };
}d_dcc_skin_tone_segment3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_0_hb:2;
        RBus_UInt32  s_base_0_0_lb:8;
        RBus_UInt32  s_g0_0_0:8;
        RBus_UInt32  s_g1_0_0:8;
    };
}ds_interp_data_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_1_hb:2;
        RBus_UInt32  s_base_0_1_lb:8;
        RBus_UInt32  s_g0_0_1:8;
        RBus_UInt32  s_g1_0_1:8;
    };
}ds_interp_data_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_2_hb:2;
        RBus_UInt32  s_base_0_2_lb:8;
        RBus_UInt32  s_g0_0_2:8;
        RBus_UInt32  s_g1_0_2:8;
    };
}ds_interp_data_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_3_hb:2;
        RBus_UInt32  s_base_0_3_lb:8;
        RBus_UInt32  s_g0_0_3:8;
        RBus_UInt32  s_g1_0_3:8;
    };
}ds_interp_data_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_4_hb:2;
        RBus_UInt32  s_base_0_4_lb:8;
        RBus_UInt32  s_g0_0_4:8;
        RBus_UInt32  s_g1_0_4:8;
    };
}ds_interp_data_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_5_hb:2;
        RBus_UInt32  s_base_0_5_lb:8;
        RBus_UInt32  s_g0_0_5:8;
        RBus_UInt32  s_g1_0_5:8;
    };
}ds_interp_data_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_6_hb:2;
        RBus_UInt32  s_base_0_6_lb:8;
        RBus_UInt32  s_g0_0_6:8;
        RBus_UInt32  s_g1_0_6:8;
    };
}ds_interp_data_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_7_hb:2;
        RBus_UInt32  s_base_0_7_lb:8;
        RBus_UInt32  s_g0_0_7:8;
        RBus_UInt32  s_g1_0_7:8;
    };
}ds_interp_data_1c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_8_hb:2;
        RBus_UInt32  s_base_0_8_lb:8;
        RBus_UInt32  s_g0_0_8:8;
        RBus_UInt32  s_g1_0_8:8;
    };
}ds_interp_data_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_9_hb:2;
        RBus_UInt32  s_base_0_9_lb:8;
        RBus_UInt32  s_g0_0_9:8;
        RBus_UInt32  s_g1_0_9:8;
    };
}ds_interp_data_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_a_hb:2;
        RBus_UInt32  s_base_0_a_lb:8;
        RBus_UInt32  s_g0_0_a:8;
        RBus_UInt32  s_g1_0_a:8;
    };
}ds_interp_data_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_b_hb:2;
        RBus_UInt32  s_base_0_b_lb:8;
        RBus_UInt32  s_g0_0_b:8;
        RBus_UInt32  s_g1_0_b:8;
    };
}ds_interp_data_4c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_c_hb:2;
        RBus_UInt32  s_base_0_c_lb:8;
        RBus_UInt32  s_g0_0_c:8;
        RBus_UInt32  s_g1_0_c:8;
    };
}ds_interp_data_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_d_hb:2;
        RBus_UInt32  s_base_0_d_lb:8;
        RBus_UInt32  s_g0_0_d:8;
        RBus_UInt32  s_g1_0_d:8;
    };
}ds_interp_data_54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_e_hb:2;
        RBus_UInt32  s_base_0_e_lb:8;
        RBus_UInt32  s_g0_0_e:8;
        RBus_UInt32  s_g1_0_e:8;
    };
}ds_interp_data_58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_0_f_hb:2;
        RBus_UInt32  s_base_0_f_lb:8;
        RBus_UInt32  s_g0_0_f:8;
        RBus_UInt32  s_g1_0_f:8;
    };
}ds_interp_data_5c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_0_hb:2;
        RBus_UInt32  s_base_1_0_lb:8;
        RBus_UInt32  s_g0_1_0:8;
        RBus_UInt32  s_g1_1_0:8;
    };
}ds_interp_data_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_1_hb:2;
        RBus_UInt32  s_base_1_1_lb:8;
        RBus_UInt32  s_g0_1_1:8;
        RBus_UInt32  s_g1_1_1:8;
    };
}ds_interp_data_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_2_hb:2;
        RBus_UInt32  s_base_1_2_lb:8;
        RBus_UInt32  s_g0_1_2:8;
        RBus_UInt32  s_g1_1_2:8;
    };
}ds_interp_data_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_3_hb:2;
        RBus_UInt32  s_base_1_3_lb:8;
        RBus_UInt32  s_g0_1_3:8;
        RBus_UInt32  s_g1_1_3:8;
    };
}ds_interp_data_2c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_4_hb:2;
        RBus_UInt32  s_base_1_4_lb:8;
        RBus_UInt32  s_g0_1_4:8;
        RBus_UInt32  s_g1_1_4:8;
    };
}ds_interp_data_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_5_hb:2;
        RBus_UInt32  s_base_1_5_lb:8;
        RBus_UInt32  s_g0_1_5:8;
        RBus_UInt32  s_g1_1_5:8;
    };
}ds_interp_data_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_6_hb:2;
        RBus_UInt32  s_base_1_6_lb:8;
        RBus_UInt32  s_g0_1_6:8;
        RBus_UInt32  s_g1_1_6:8;
    };
}ds_interp_data_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_7_hb:2;
        RBus_UInt32  s_base_1_7_lb:8;
        RBus_UInt32  s_g0_1_7:8;
        RBus_UInt32  s_g1_1_7:8;
    };
}ds_interp_data_3c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_8_hb:2;
        RBus_UInt32  s_base_1_8_lb:8;
        RBus_UInt32  s_g0_1_8:8;
        RBus_UInt32  s_g1_1_8:8;
    };
}ds_interp_data_60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_9_hb:2;
        RBus_UInt32  s_base_1_9_lb:8;
        RBus_UInt32  s_g0_1_9:8;
        RBus_UInt32  s_g1_1_9:8;
    };
}ds_interp_data_64_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_a_hb:2;
        RBus_UInt32  s_base_1_a_lb:8;
        RBus_UInt32  s_g0_1_a:8;
        RBus_UInt32  s_g1_1_a:8;
    };
}ds_interp_data_68_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_b_hb:2;
        RBus_UInt32  s_base_1_b_lb:8;
        RBus_UInt32  s_g0_1_b:8;
        RBus_UInt32  s_g1_1_b:8;
    };
}ds_interp_data_6c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_c_hb:2;
        RBus_UInt32  s_base_1_c_lb:8;
        RBus_UInt32  s_g0_1_c:8;
        RBus_UInt32  s_g1_1_c:8;
    };
}ds_interp_data_70_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_d_hb:2;
        RBus_UInt32  s_base_1_d_lb:8;
        RBus_UInt32  s_g0_1_d:8;
        RBus_UInt32  s_g1_1_d:8;
    };
}ds_interp_data_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_e_hb:2;
        RBus_UInt32  s_base_1_e_lb:8;
        RBus_UInt32  s_g0_1_e:8;
        RBus_UInt32  s_g1_1_e:8;
    };
}ds_interp_data_78_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  s_base_1_f_hb:2;
        RBus_UInt32  s_base_1_f_lb:8;
        RBus_UInt32  s_g0_1_f:8;
        RBus_UInt32  s_g1_1_f:8;
    };
}ds_interp_data_7c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_alpha_h_1:8;
        RBus_UInt32  s_alpha_l_1:8;
        RBus_UInt32  s_alpha_h_0:8;
        RBus_UInt32  s_alpha_l_0:8;
    };
}ds_nc_blend_data_80_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  s_zero_gain:22;
    };
}ds_nc_zero_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802e53c_31_0:32;
    };
}d_dcc_dummy_0_RBUS;

#else //apply LITTLE_ENDIAN

//======COLOR_DCC register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  main_dcc_mode:2;
        RBus_UInt32  sub_dcc_mode:2;
        RBus_UInt32  res2:5;
        RBus_UInt32  main_table_sel:1;
        RBus_UInt32  sub_table_sel:1;
        RBus_UInt32  res3:11;
        RBus_UInt32  dcc_main_tab_sel:2;
        RBus_UInt32  dcc_sub_tab_sel:2;
        RBus_UInt32  dcc_overlay:1;
        RBus_UInt32  res4:3;
    };
}d_dcc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_limit_sub:10;
        RBus_UInt32  res1:1;
        RBus_UInt32  chroma_gain_sub_seg8:5;
        RBus_UInt32  chroma_gain_limit_main:10;
        RBus_UInt32  res2:1;
        RBus_UInt32  chroma_gain_main_seg8:5;
    };
}dcc_ctrl_color_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_main_seg0:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  chroma_gain_main_seg1:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_main_seg2:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_main_seg3:5;
        RBus_UInt32  res4:2;
        RBus_UInt32  chroma_gain_main_intp_en:1;
    };
}dcc_ctrl_color_main_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_main_seg4:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  chroma_gain_main_seg5:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_main_seg6:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_main_seg7:5;
        RBus_UInt32  res4:3;
    };
}dcc_ctrl_color_main_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_sub_seg0:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  chroma_gain_sub_seg1:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_sub_seg2:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_sub_seg3:5;
        RBus_UInt32  res4:2;
        RBus_UInt32  chroma_gain_sub_intp_en:1;
    };
}dcc_ctrl_color_sub_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_gain_sub_seg4:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  chroma_gain_sub_seg5:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_gain_sub_seg6:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  chroma_gain_sub_seg7:5;
        RBus_UInt32  res4:3;
    };
}dcc_ctrl_color_sub_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  luma_offset_sub:8;
        RBus_UInt32  res1:8;
        RBus_UInt32  luma_offset_main:8;
        RBus_UInt32  res2:8;
    };
}dcc_ctrl_luma_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_0:8;
        RBus_UInt32  m_g0_0_0:8;
        RBus_UInt32  m_base_0_0_lb:8;
        RBus_UInt32  m_base_0_0_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_1:8;
        RBus_UInt32  m_g0_0_1:8;
        RBus_UInt32  m_base_0_1_lb:8;
        RBus_UInt32  m_base_0_1_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_2:8;
        RBus_UInt32  m_g0_0_2:8;
        RBus_UInt32  m_base_0_2_lb:8;
        RBus_UInt32  m_base_0_2_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_3:8;
        RBus_UInt32  m_g0_0_3:8;
        RBus_UInt32  m_base_0_3_lb:8;
        RBus_UInt32  m_base_0_3_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_4:8;
        RBus_UInt32  m_g0_0_4:8;
        RBus_UInt32  m_base_0_4_lb:8;
        RBus_UInt32  m_base_0_4_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_5:8;
        RBus_UInt32  m_g0_0_5:8;
        RBus_UInt32  m_base_0_5_lb:8;
        RBus_UInt32  m_base_0_5_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_6:8;
        RBus_UInt32  m_g0_0_6:8;
        RBus_UInt32  m_base_0_6_lb:8;
        RBus_UInt32  m_base_0_6_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_7:8;
        RBus_UInt32  m_g0_0_7:8;
        RBus_UInt32  m_base_0_7_lb:8;
        RBus_UInt32  m_base_0_7_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_1c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_8:8;
        RBus_UInt32  m_g0_0_8:8;
        RBus_UInt32  m_base_0_8_lb:8;
        RBus_UInt32  m_base_0_8_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_9:8;
        RBus_UInt32  m_g0_0_9:8;
        RBus_UInt32  m_base_0_9_lb:8;
        RBus_UInt32  m_base_0_9_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_a:8;
        RBus_UInt32  m_g0_0_a:8;
        RBus_UInt32  m_base_0_a_lb:8;
        RBus_UInt32  m_base_0_a_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_b:8;
        RBus_UInt32  m_g0_0_b:8;
        RBus_UInt32  m_base_0_b_lb:8;
        RBus_UInt32  m_base_0_b_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_4c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_c:8;
        RBus_UInt32  m_g0_0_c:8;
        RBus_UInt32  m_base_0_c_lb:8;
        RBus_UInt32  m_base_0_c_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_d:8;
        RBus_UInt32  m_g0_0_d:8;
        RBus_UInt32  m_base_0_d_lb:8;
        RBus_UInt32  m_base_0_d_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_e:8;
        RBus_UInt32  m_g0_0_e:8;
        RBus_UInt32  m_base_0_e_lb:8;
        RBus_UInt32  m_base_0_e_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_0_f:8;
        RBus_UInt32  m_g0_0_f:8;
        RBus_UInt32  m_base_0_f_lb:8;
        RBus_UInt32  m_base_0_f_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_5c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_0:8;
        RBus_UInt32  m_g0_1_0:8;
        RBus_UInt32  m_base_1_0_lb:8;
        RBus_UInt32  m_base_1_0_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_1:8;
        RBus_UInt32  m_g0_1_1:8;
        RBus_UInt32  m_base_1_1_lb:8;
        RBus_UInt32  m_base_1_1_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_2:8;
        RBus_UInt32  m_g0_1_2:8;
        RBus_UInt32  m_base_1_2_lb:8;
        RBus_UInt32  m_base_1_2_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_3:8;
        RBus_UInt32  m_g0_1_3:8;
        RBus_UInt32  m_base_1_3_lb:8;
        RBus_UInt32  m_base_1_3_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_2c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_4:8;
        RBus_UInt32  m_g0_1_4:8;
        RBus_UInt32  m_base_1_4_lb:8;
        RBus_UInt32  m_base_1_4_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_5:8;
        RBus_UInt32  m_g0_1_5:8;
        RBus_UInt32  m_base_1_5_lb:8;
        RBus_UInt32  m_base_1_5_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_6:8;
        RBus_UInt32  m_g0_1_6:8;
        RBus_UInt32  m_base_1_6_lb:8;
        RBus_UInt32  m_base_1_6_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_7:8;
        RBus_UInt32  m_g0_1_7:8;
        RBus_UInt32  m_base_1_7_lb:8;
        RBus_UInt32  m_base_1_7_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_3c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_8:8;
        RBus_UInt32  m_g0_1_8:8;
        RBus_UInt32  m_base_1_8_lb:8;
        RBus_UInt32  m_base_1_8_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_9:8;
        RBus_UInt32  m_g0_1_9:8;
        RBus_UInt32  m_base_1_9_lb:8;
        RBus_UInt32  m_base_1_9_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_64_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_a:8;
        RBus_UInt32  m_g0_1_a:8;
        RBus_UInt32  m_base_1_a_lb:8;
        RBus_UInt32  m_base_1_a_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_68_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_b:8;
        RBus_UInt32  m_g0_1_b:8;
        RBus_UInt32  m_base_1_b_lb:8;
        RBus_UInt32  m_base_1_b_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_6c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_c:8;
        RBus_UInt32  m_g0_1_c:8;
        RBus_UInt32  m_base_1_c_lb:8;
        RBus_UInt32  m_base_1_c_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_70_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_d:8;
        RBus_UInt32  m_g0_1_d:8;
        RBus_UInt32  m_base_1_d_lb:8;
        RBus_UInt32  m_base_1_d_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_e:8;
        RBus_UInt32  m_g0_1_e:8;
        RBus_UInt32  m_base_1_e_lb:8;
        RBus_UInt32  m_base_1_e_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_78_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_g1_1_f:8;
        RBus_UInt32  m_g0_1_f:8;
        RBus_UInt32  m_base_1_f_lb:8;
        RBus_UInt32  m_base_1_f_hb:2;
        RBus_UInt32  res1:6;
    };
}dm_interp_data_7c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_alpha_l_0:8;
        RBus_UInt32  m_alpha_h_0:8;
        RBus_UInt32  m_alpha_l_1:8;
        RBus_UInt32  m_alpha_h_1:8;
    };
}dm_nc_blend_data_80_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_zero_gain:22;
        RBus_UInt32  res1:10;
    };
}dm_nc_zero_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  db_apply:1;
        RBus_UInt32  db_read_level:1;
        RBus_UInt32  db_en:1;
        RBus_UInt32  res1:29;
    };
}d_dcc_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_en:1;
        RBus_UInt32  y_blending_reg3_en:1;
        RBus_UInt32  y_blending_reg2_en:1;
        RBus_UInt32  y_blending_reg1_en:1;
        RBus_UInt32  y_blending_reg0_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  y_blending_mode:1;
        RBus_UInt32  res2:7;
        RBus_UInt32  y_blending_debug_mode_sel:1;
        RBus_UInt32  y_blending_debug_mode_en:1;
        RBus_UInt32  res3:14;
    };
}d_dcc_skin_tone_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_0_v_center:10;
        RBus_UInt32  y_blending_0_u_center:10;
        RBus_UInt32  y_blending_0_y_center:10;
        RBus_UInt32  res1:2;
    };
}d_dcc_skin_tone_yuv_center_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_0_v_range:4;
        RBus_UInt32  y_blending_0_u_range:4;
        RBus_UInt32  y_blending_0_y_range:4;
        RBus_UInt32  res1:20;
    };
}d_dcc_skin_tone_yuv_range_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_1_v_center:10;
        RBus_UInt32  y_blending_1_u_center:10;
        RBus_UInt32  y_blending_1_y_center:10;
        RBus_UInt32  res1:2;
    };
}d_dcc_skin_tone_yuv_center_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_1_v_range:4;
        RBus_UInt32  y_blending_1_u_range:4;
        RBus_UInt32  y_blending_1_y_range:4;
        RBus_UInt32  res1:20;
    };
}d_dcc_skin_tone_yuv_range_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_2_v_center:10;
        RBus_UInt32  y_blending_2_u_center:10;
        RBus_UInt32  y_blending_2_y_center:10;
        RBus_UInt32  res1:2;
    };
}d_dcc_skin_tone_yuv_center_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_2_v_range:4;
        RBus_UInt32  y_blending_2_u_range:4;
        RBus_UInt32  y_blending_2_y_range:4;
        RBus_UInt32  res1:20;
    };
}d_dcc_skin_tone_yuv_range_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_3_v_center:10;
        RBus_UInt32  y_blending_3_u_center:10;
        RBus_UInt32  y_blending_3_y_center:10;
        RBus_UInt32  res1:2;
    };
}d_dcc_skin_tone_yuv_center_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_3_v_range:4;
        RBus_UInt32  y_blending_3_u_range:4;
        RBus_UInt32  y_blending_3_y_range:4;
        RBus_UInt32  res1:20;
    };
}d_dcc_skin_tone_yuv_range_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_0_ratio_3:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_0_ratio_2:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_0_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_0_ratio_0:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment0_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_0_ratio_7:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_0_ratio_6:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_0_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_0_ratio_4:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment0_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_1_ratio_3:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_1_ratio_2:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_1_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_1_ratio_0:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment1_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_1_ratio_7:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_1_ratio_6:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_1_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_1_ratio_4:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_2_ratio_3:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_2_ratio_2:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_2_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_2_ratio_0:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment2_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_2_ratio_7:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_2_ratio_6:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_2_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_2_ratio_4:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_3_ratio_3:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_3_ratio_2:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_3_ratio_1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_3_ratio_0:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment3_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_blending_3_ratio_7:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  y_blending_3_ratio_6:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  y_blending_3_ratio_5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y_blending_3_ratio_4:6;
        RBus_UInt32  res4:2;
    };
}d_dcc_skin_tone_segment3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_0:8;
        RBus_UInt32  s_g0_0_0:8;
        RBus_UInt32  s_base_0_0_lb:8;
        RBus_UInt32  s_base_0_0_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_1:8;
        RBus_UInt32  s_g0_0_1:8;
        RBus_UInt32  s_base_0_1_lb:8;
        RBus_UInt32  s_base_0_1_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_2:8;
        RBus_UInt32  s_g0_0_2:8;
        RBus_UInt32  s_base_0_2_lb:8;
        RBus_UInt32  s_base_0_2_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_3:8;
        RBus_UInt32  s_g0_0_3:8;
        RBus_UInt32  s_base_0_3_lb:8;
        RBus_UInt32  s_base_0_3_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_4:8;
        RBus_UInt32  s_g0_0_4:8;
        RBus_UInt32  s_base_0_4_lb:8;
        RBus_UInt32  s_base_0_4_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_5:8;
        RBus_UInt32  s_g0_0_5:8;
        RBus_UInt32  s_base_0_5_lb:8;
        RBus_UInt32  s_base_0_5_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_6:8;
        RBus_UInt32  s_g0_0_6:8;
        RBus_UInt32  s_base_0_6_lb:8;
        RBus_UInt32  s_base_0_6_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_7:8;
        RBus_UInt32  s_g0_0_7:8;
        RBus_UInt32  s_base_0_7_lb:8;
        RBus_UInt32  s_base_0_7_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_1c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_8:8;
        RBus_UInt32  s_g0_0_8:8;
        RBus_UInt32  s_base_0_8_lb:8;
        RBus_UInt32  s_base_0_8_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_9:8;
        RBus_UInt32  s_g0_0_9:8;
        RBus_UInt32  s_base_0_9_lb:8;
        RBus_UInt32  s_base_0_9_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_a:8;
        RBus_UInt32  s_g0_0_a:8;
        RBus_UInt32  s_base_0_a_lb:8;
        RBus_UInt32  s_base_0_a_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_b:8;
        RBus_UInt32  s_g0_0_b:8;
        RBus_UInt32  s_base_0_b_lb:8;
        RBus_UInt32  s_base_0_b_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_4c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_c:8;
        RBus_UInt32  s_g0_0_c:8;
        RBus_UInt32  s_base_0_c_lb:8;
        RBus_UInt32  s_base_0_c_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_d:8;
        RBus_UInt32  s_g0_0_d:8;
        RBus_UInt32  s_base_0_d_lb:8;
        RBus_UInt32  s_base_0_d_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_54_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_e:8;
        RBus_UInt32  s_g0_0_e:8;
        RBus_UInt32  s_base_0_e_lb:8;
        RBus_UInt32  s_base_0_e_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_58_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_0_f:8;
        RBus_UInt32  s_g0_0_f:8;
        RBus_UInt32  s_base_0_f_lb:8;
        RBus_UInt32  s_base_0_f_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_5c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_0:8;
        RBus_UInt32  s_g0_1_0:8;
        RBus_UInt32  s_base_1_0_lb:8;
        RBus_UInt32  s_base_1_0_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_1:8;
        RBus_UInt32  s_g0_1_1:8;
        RBus_UInt32  s_base_1_1_lb:8;
        RBus_UInt32  s_base_1_1_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_2:8;
        RBus_UInt32  s_g0_1_2:8;
        RBus_UInt32  s_base_1_2_lb:8;
        RBus_UInt32  s_base_1_2_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_3:8;
        RBus_UInt32  s_g0_1_3:8;
        RBus_UInt32  s_base_1_3_lb:8;
        RBus_UInt32  s_base_1_3_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_2c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_4:8;
        RBus_UInt32  s_g0_1_4:8;
        RBus_UInt32  s_base_1_4_lb:8;
        RBus_UInt32  s_base_1_4_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_5:8;
        RBus_UInt32  s_g0_1_5:8;
        RBus_UInt32  s_base_1_5_lb:8;
        RBus_UInt32  s_base_1_5_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_6:8;
        RBus_UInt32  s_g0_1_6:8;
        RBus_UInt32  s_base_1_6_lb:8;
        RBus_UInt32  s_base_1_6_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_7:8;
        RBus_UInt32  s_g0_1_7:8;
        RBus_UInt32  s_base_1_7_lb:8;
        RBus_UInt32  s_base_1_7_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_3c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_8:8;
        RBus_UInt32  s_g0_1_8:8;
        RBus_UInt32  s_base_1_8_lb:8;
        RBus_UInt32  s_base_1_8_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_9:8;
        RBus_UInt32  s_g0_1_9:8;
        RBus_UInt32  s_base_1_9_lb:8;
        RBus_UInt32  s_base_1_9_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_64_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_a:8;
        RBus_UInt32  s_g0_1_a:8;
        RBus_UInt32  s_base_1_a_lb:8;
        RBus_UInt32  s_base_1_a_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_68_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_b:8;
        RBus_UInt32  s_g0_1_b:8;
        RBus_UInt32  s_base_1_b_lb:8;
        RBus_UInt32  s_base_1_b_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_6c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_c:8;
        RBus_UInt32  s_g0_1_c:8;
        RBus_UInt32  s_base_1_c_lb:8;
        RBus_UInt32  s_base_1_c_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_70_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_d:8;
        RBus_UInt32  s_g0_1_d:8;
        RBus_UInt32  s_base_1_d_lb:8;
        RBus_UInt32  s_base_1_d_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_e:8;
        RBus_UInt32  s_g0_1_e:8;
        RBus_UInt32  s_base_1_e_lb:8;
        RBus_UInt32  s_base_1_e_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_78_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_g1_1_f:8;
        RBus_UInt32  s_g0_1_f:8;
        RBus_UInt32  s_base_1_f_lb:8;
        RBus_UInt32  s_base_1_f_hb:2;
        RBus_UInt32  res1:6;
    };
}ds_interp_data_7c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_alpha_l_0:8;
        RBus_UInt32  s_alpha_h_0:8;
        RBus_UInt32  s_alpha_l_1:8;
        RBus_UInt32  s_alpha_h_1:8;
    };
}ds_nc_blend_data_80_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_zero_gain:22;
        RBus_UInt32  res1:10;
    };
}ds_nc_zero_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802e53c_31_0:32;
    };
}d_dcc_dummy_0_RBUS;




#endif 


#endif 
