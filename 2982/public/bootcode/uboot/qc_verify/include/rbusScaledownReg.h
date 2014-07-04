/**
* @file rbusScaledownReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/12/31
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_SCALEDOWN_REG_H_
#define _RBUS_SCALEDOWN_REG_H_

#include "rbusTypes.h"



//  SCALEDOWN Register Address



#define  SCALEDOWN_ICH1_IBUFF_STATUS_CTRL_VADDR 		(0xb8025200)
#define  SCALEDOWN_ICH1_UZD_CTRL0_VADDR 		(0xb8025204)
#define  SCALEDOWN_ICH1_UZD_CTRL1_VADDR 		(0xb8025208)
#define  SCALEDOWN_ICH1_UZD_SCALE_HOR_FACTOR_VADDR 		(0xb802520c)
#define  SCALEDOWN_ICH1_UZD_SCALE_VER_FACTOR_VADDR 		(0xb8025210)
#define  SCALEDOWN_ICH1_UZD_INITIAL_VALUE_VADDR 		(0xb8025214)
#define  SCALEDOWN_ICH1_UZD_HOR_DELTA1_VADDR 		(0xb8025218)
#define  SCALEDOWN_ICH1_UZD_HOR_SEGMENT_VADDR 		(0xb802521c)
#define  SCALEDOWN_ICH1_UZD_CRC_CTRL_VADDR 		(0xb8025220)
#define  SCALEDOWN_ICH1_UZD_CRC_RESULT_VADDR 		(0xb8025224)
#define  SCALEDOWN_ICH1_UZD_CRC_RESULT_RIGHT_VADDR 		(0xb8025228)
#define  SCALEDOWN_ICH1_UZD_L_DES_CRC_VADDR 		(0xb802522c)
#define  SCALEDOWN_ICH1_UZD_R_DES_CRC_VADDR 		(0xb8025230)
#define  SCALEDOWN_ICH1_UZD_CRC_ERR_CNT_VADDR 		(0xb8025234)
#define  SCALEDOWN_ICH1_IBUFF_CTRL_I_BUFF_CTRL_VADDR 		(0xb8025240)
#define  SCALEDOWN_ICH1_UZD_CHANNEL_SWAP_VADDR 		(0xb8025244)
#define  SCALEDOWN_ICH1_UZD_DB_CTRL_VADDR 		(0xb8025248)
#define  SCALEDOWN_ICH1_IBUFF_STATUS_VADDR 		(0xb802524c)
#define  SCALEDOWN_ICH1_HSD_CRC_CTRL_VADDR 		(0xb8025250)
#define  SCALEDOWN_ICH1_HSD_CRC_RESULT_LEFT_VADDR 		(0xb8025254)
#define  SCALEDOWN_ICH1_HSD_CRC_RESULT_VADDR 		(0xb8025258)
#define  SCALEDOWN_ICH1_HSD_L_DES_CRC_VADDR 		(0xb802525c)
#define  SCALEDOWN_ICH1_HSD_R_DES_CRC_VADDR 		(0xb8025260)
#define  SCALEDOWN_ICH1_HSD_CRC_ERR_CNT_VADDR 		(0xb8025264)
#define  SCALEDOWN_MEASURE_IVST_RESULT_MAIN_PATH_VADDR 		(0xb8025270)
#define  SCALEDOWN_MEASURE_ACTIVE_LINE_PIXELS_RESULT_MAIN_PATH_VADDR 		(0xb8025274)
#define  SCALEDOWN_MEASURE_CTRL_VADDR 		(0xb8025278)
#define  SCALEDOWN_ACCESSDATA_CTRL_UZD_VADDR 		(0xb8025280)
#define  SCALEDOWN_ACCESSDATA_POSCTRL_UZD_VADDR 		(0xb8025284)
#define  SCALEDOWN_READDATA_DATA_Y1_UZD_VADDR 		(0xb8025288)
#define  SCALEDOWN_READDATA_DATA_Y2_UZD_VADDR 		(0xb802528c)
#define  SCALEDOWN_READDATA_DATA_C1_UZD_VADDR 		(0xb8025290)
#define  SCALEDOWN_READDATA_DATA_C2_UZD_VADDR 		(0xb8025294)
#define  SCALEDOWN_READDATA_DATA_C3_UZD_VADDR 		(0xb8025298)
#define  SCALEDOWN_READDATA_DATA_C4_UZD_VADDR 		(0xb802529c)
#define  SCALEDOWN_WRITEDATA_DATA_UZD_VADDR 		(0xb80252a0)
#define  SCALEDOWN_ICH1_SDNR_BIST_FSBUF_FAIL_VADDR 		(0xb80252b0)
#define  SCALEDOWN_ICH1_SDNR_DRF_FSBUF_FAIL_VADDR 		(0xb80252b4)
#define  SCALEDOWN_ICH1_SDNR_BISR_LINEBUF_FAIL_VADDR 		(0xb80252b8)
#define  SCALEDOWN_ICH1_SDNR_DRF_LINEBUF_FAIL_VADDR 		(0xb80252bc)
#define  SCALEDOWN_ICH1_SDNR_LINEBUF_DVS_VADDR 		(0xb80252c0)
#define  SCALEDOWN_ICH1_SDNR_FSBUF_DVS01_VADDR 		(0xb80252c4)
#define  SCALEDOWN_ICH1_SDNR_FSBUF_DVS23_VADDR 		(0xb80252c8)
#define  SCALEDOWN_ICH1_SDNR_444TO422_CTRL_VADDR 		(0xb80252f0)
#define  SCALEDOWN_ICH1_HSD_3D_BOUNDARY_VADDR 		(0xb80252f4)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C0_VADDR 		(0xb8025300)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C2_VADDR 		(0xb8025304)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C4_VADDR 		(0xb8025308)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C6_VADDR 		(0xb802530c)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C8_VADDR 		(0xb8025310)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C10_VADDR 		(0xb8025314)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C12_VADDR 		(0xb8025318)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C14_VADDR 		(0xb802531c)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C16_VADDR 		(0xb8025320)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C18_VADDR 		(0xb8025324)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C20_VADDR 		(0xb8025328)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C22_VADDR 		(0xb802532c)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C24_VADDR 		(0xb8025330)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C26_VADDR 		(0xb8025334)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C28_VADDR 		(0xb8025338)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB1_C30_VADDR 		(0xb802533c)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C0_VADDR 		(0xb8025340)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C2_VADDR 		(0xb8025344)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C4_VADDR 		(0xb8025348)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C6_VADDR 		(0xb802534c)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C8_VADDR 		(0xb8025350)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C10_VADDR 		(0xb8025354)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C12_VADDR 		(0xb8025358)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C14_VADDR 		(0xb802535c)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C16_VADDR 		(0xb8025360)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C18_VADDR 		(0xb8025364)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C20_VADDR 		(0xb8025368)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C22_VADDR 		(0xb802536c)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C24_VADDR 		(0xb8025370)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C26_VADDR 		(0xb8025374)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C28_VADDR 		(0xb8025378)
#define  SCALEDOWN_ICH1_UZD_FIR_COEF_TAB2_C30_VADDR 		(0xb802537c)
#define  SCALEDOWN_ICH2_UZD_CTRL0_VADDR 		(0xb8025400)
#define  SCALEDOWN_ICH2_UZD_CTRL1_VADDR 		(0xb8025404)
#define  SCALEDOWN_ICH2_UZD_SCALE_HOR_FACTOR_VADDR 		(0xb8025408)
#define  SCALEDOWN_ICH2_UZD_SCALE_VER_FACTOR_VADDR 		(0xb802540c)
#define  SCALEDOWN_ICH2_UZD_INITIAL_VALUE_VADDR 		(0xb8025410)
#define  SCALEDOWN_ICH2_UZD_H_OUTPUT_SIZE_VADDR 		(0xb8025414)
#define  SCALEDOWN_ICH2_UZD_CRC_CTRL_VADDR 		(0xb8025418)
#define  SCALEDOWN_ICH2_UZD_CRC_RESULT_VADDR 		(0xb802541c)
#define  SCALEDOWN_ICH2_IBUFF_STATUS_CTRL_VADDR 		(0xb8025420)
#define  SCALEDOWN_ICH2_IBUFF_CTRL_I_BUFF_CTRL_VADDR 		(0xb8025424)
#define  SCALEDOWN_ICH2_UZD_CHANNEL_SWAP_VADDR 		(0xb8025428)
#define  SCALEDOWN_ICH2_UZD_DB_CTRL_VADDR 		(0xb8025430)
#define  SCALEDOWN_ICH2_IBUFF_STATUS_VADDR 		(0xb8025434)
#define  SCALEDOWN_ICH2_HSD_CRC_CTRL_VADDR 		(0xb8025440)
#define  SCALEDOWN_ICH2_HSD_CRC_RESULT_VADDR 		(0xb8025444)
#define  SCALEDOWN_MEASURE_CTRL_IVST_RESULT_SUB_PATH_VADDR 		(0xb8025448)
#define  SCALEDOWN_MEASURE_IVST_RESULT_SUB_PATH_VADDR 		(0xb802544c)
#define  SCALEDOWN_MEASURE_ACTIVE_LINE_PIXELS_RESULT_SUB_PATH_VADDR 		(0xb8025450)
#define  SCALEDOWN_ICH2_SDNR_BISR_LINEBUF_FAIL_VADDR 		(0xb80254b0)
#define  SCALEDOWN_ICH2_SDNR_DRF_LINEBUF_FAIL_VADDR 		(0xb80254b4)
#define  SCALEDOWN_ICH2_SDNR_LINEBUF_DVS_VADDR 		(0xb80254b8)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======SCALEDOWN register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  wd_fsync_ovf_en:1;
        RBus_UInt32  wd_fsync_udf_en:1;
        RBus_UInt32  wd_ibuff_ovf_en:1;
        RBus_UInt32  wd_ibuff_to_main:1;
        RBus_UInt32  wd_ibuff_to_sub:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  irq_fsync_ovf_en:1;
        RBus_UInt32  irq_fsync_udf_en:1;
        RBus_UInt32  irq_ibuff_ovf_en:1;
        RBus_UInt32  res3:8;
    };
}ich1_ibuff_status_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  dummy18025204_26:1;
        RBus_UInt32  sel_3d_en:1;
        RBus_UInt32  truncationctrl:1;
        RBus_UInt32  argb_dummy_data:8;
        RBus_UInt32  dummy18025204_15_14:2;
        RBus_UInt32  argb_swap:1;
        RBus_UInt32  rgb_to_argb_en:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  out_bit:1;
        RBus_UInt32  sort_fmt:1;
        RBus_UInt32  v_y_table_sel:1;
        RBus_UInt32  v_c_table_sel:1;
        RBus_UInt32  h_y_table_sel:1;
        RBus_UInt32  h_c_table_sel:1;
        RBus_UInt32  buffer_mode:2;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  h_zoom_en:1;
    };
}ich1_uzd_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  lp121_en:1;
        RBus_UInt32  res2:9;
        RBus_UInt32  vsd_3d_boundary:13;
        RBus_UInt32  res3:1;
        RBus_UInt32  vsd_3d_mode:2;
    };
}ich1_uzd_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  hor_fac:25;
    };
}ich1_uzd_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  ver_ini_int_l:1;
        RBus_UInt32  ver_ini_int:1;
        RBus_UInt32  ver_fac:25;
    };
}ich1_uzd_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_ini_l:8;
        RBus_UInt32  ver_ini_l:8;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  ver_ini:8;
    };
}ich1_uzd_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  nl_d1:14;
    };
}ich1_uzd_hor_delta1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  nl_seg1:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  nl_seg2:12;
    };
}ich1_uzd_hor_segment_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  crc_3d_en:1;
        RBus_UInt32  conti:1;
        RBus_UInt32  start:1;
    };
}ich1_uzd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_l_result:32;
    };
}ich1_uzd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_r_result:32;
    };
}ich1_uzd_crc_result_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}ich1_uzd_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}ich1_uzd_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_crc_err_cnt:16;
        RBus_UInt32  l_crc_err_cnt:16;
    };
}ich1_uzd_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ibuf_v_size:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ibuf_h_size:13;
    };
}ich1_ibuff_ctrl_i_buff_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  rgb565_en:1;
        RBus_UInt32  rgb_ch_swap:3;
    };
}ich1_uzd_channel_swap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  mdom_comp_rd_sel:1;
        RBus_UInt32  mdom_comp_db_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  h_db_apply:1;
        RBus_UInt32  h_db_rd_sel:1;
        RBus_UInt32  h_db_en:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  v_db_apply:1;
        RBus_UInt32  v_db_rd_sel:1;
        RBus_UInt32  v_db_en:1;
    };
}ich1_uzd_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  q_sbs_lr_ovf:1;
        RBus_UInt32  q_sbs_lr_udf:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ibuff_ovf:1;
        RBus_UInt32  fsync_ovf:1;
        RBus_UInt32  fsync_udf:1;
    };
}ich1_ibuff_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  ch1_hsd_crc_conti:1;
        RBus_UInt32  ch1_hsd_crc_start:1;
    };
}ich1_hsd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_l_result:32;
    };
}ich1_hsd_crc_result_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_r_result:32;
    };
}ich1_hsd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}ich1_hsd_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}ich1_hsd_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_crc_err_cnt:16;
        RBus_UInt32  l_crc_err_cnt:16;
    };
}ich1_hsd_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  m_ivst_value_odd:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  m_ivst_value_even:12;
    };
}measure_ivst_result_main_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  m_vactive_line_value:12;
        RBus_UInt32  res2:3;
        RBus_UInt32  m_hactive_hpixel_value:13;
    };
}measure_active_line_pixels_result_main_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_ivst_en:1;
        RBus_UInt32  m_ihs_mode:1;
        RBus_UInt32  res1:29;
        RBus_UInt32  m_active_line_pixel_en:1;
    };
}measure_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  write_en:1;
        RBus_UInt32  read_en:1;
    };
}accessdata_ctrl_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  starty:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  startx:13;
    };
}accessdata_posctrl_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  y01:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  y00:10;
    };
}readdata_data_y1_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  y11:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  y10:10;
    };
}readdata_data_y2_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v00:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u00:10;
    };
}readdata_data_c1_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v01:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u01:10;
    };
}readdata_data_c2_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v10:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u10:10;
    };
}readdata_data_c3_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  v11:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  u11:10;
    };
}readdata_data_c4_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  v:4;
        RBus_UInt32  u:4;
        RBus_UInt32  y:4;
    };
}writedata_data_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  sdnr_bist_fsbuf_fail_3:1;
        RBus_UInt32  sdnr_bist_fsbuf_fail_2:1;
        RBus_UInt32  sdnr_bist_fsbuf_fail_1:1;
        RBus_UInt32  sdnr_bist_fsbuf_fail_0:1;
    };
}ich1_sdnr_bist_fsbuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  sdnr_drf_fsbuf_fail_3:1;
        RBus_UInt32  sdnr_drf_fsbuf_fail_2:1;
        RBus_UInt32  sdnr_drf_fsbuf_fail_1:1;
        RBus_UInt32  sdnr_drf_fsbuf_fail_0:1;
    };
}ich1_sdnr_drf_fsbuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bisr_linebuf_fail_0:1;
    };
}ich1_sdnr_bisr_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  sdnr_drf_linebuf_fail_0:1;
    };
}ich1_sdnr_drf_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  sdnr_linebuf_ls_en:1;
        RBus_UInt32  sdnr_linebuf_dvse:1;
        RBus_UInt32  sdnr_linebuf_dvs:4;
    };
}ich1_sdnr_linebuf_dvs_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  sdnr_fsbuf_ls_en1:1;
        RBus_UInt32  sdnr_fsbuf_dvse1:1;
        RBus_UInt32  sdnr_fsbuf_dvs1:4;
        RBus_UInt32  res2:10;
        RBus_UInt32  sdnr_fsbuf_ls_en0:1;
        RBus_UInt32  sdnr_fsbuf_dvse0:1;
        RBus_UInt32  sdnr_fsbuf_dvs0:4;
    };
}ich1_sdnr_fsbuf_dvs01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  sdnr_fsbuf_ls_en3:1;
        RBus_UInt32  sdnr_fsbuf_dvse3:1;
        RBus_UInt32  sdnr_fsbuf_dvs3:4;
        RBus_UInt32  res2:10;
        RBus_UInt32  sdnr_fsbuf_ls_en2:1;
        RBus_UInt32  sdnr_fsbuf_dvse2:1;
        RBus_UInt32  sdnr_fsbuf_dvs2:4;
    };
}ich1_sdnr_fsbuf_dvs23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  cr_dly_cb:1;
        RBus_UInt32  drop:1;
        RBus_UInt32  dummy180252f0_0:1;
    };
}ich1_sdnr_444to422_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  hsd_3d_boundary:13;
    };
}ich1_hsd_3d_boundary_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c0:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c1:12;
    };
}ich1_uzd_fir_coef_tab1_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c3:12;
    };
}ich1_uzd_fir_coef_tab1_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c5:12;
    };
}ich1_uzd_fir_coef_tab1_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c7:12;
    };
}ich1_uzd_fir_coef_tab1_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c8:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c9:12;
    };
}ich1_uzd_fir_coef_tab1_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c10:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c11:12;
    };
}ich1_uzd_fir_coef_tab1_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c13:12;
    };
}ich1_uzd_fir_coef_tab1_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c14:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c15:12;
    };
}ich1_uzd_fir_coef_tab1_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c16:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c17:12;
    };
}ich1_uzd_fir_coef_tab1_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c18:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c19:12;
    };
}ich1_uzd_fir_coef_tab1_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c20:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c21:12;
    };
}ich1_uzd_fir_coef_tab1_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c22:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c23:12;
    };
}ich1_uzd_fir_coef_tab1_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c24:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c25:12;
    };
}ich1_uzd_fir_coef_tab1_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c26:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c27:12;
    };
}ich1_uzd_fir_coef_tab1_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c28:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c29:12;
    };
}ich1_uzd_fir_coef_tab1_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c30:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab1_c31:12;
    };
}ich1_uzd_fir_coef_tab1_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c0:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c1:12;
    };
}ich1_uzd_fir_coef_tab2_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c3:12;
    };
}ich1_uzd_fir_coef_tab2_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c5:12;
    };
}ich1_uzd_fir_coef_tab2_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c7:12;
    };
}ich1_uzd_fir_coef_tab2_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c8:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c9:12;
    };
}ich1_uzd_fir_coef_tab2_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c10:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c11:12;
    };
}ich1_uzd_fir_coef_tab2_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c13:12;
    };
}ich1_uzd_fir_coef_tab2_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c14:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c15:12;
    };
}ich1_uzd_fir_coef_tab2_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c16:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c17:12;
    };
}ich1_uzd_fir_coef_tab2_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c18:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c19:12;
    };
}ich1_uzd_fir_coef_tab2_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c20:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c21:12;
    };
}ich1_uzd_fir_coef_tab2_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c22:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c23:12;
    };
}ich1_uzd_fir_coef_tab2_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c24:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c25:12;
    };
}ich1_uzd_fir_coef_tab2_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c26:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c27:12;
    };
}ich1_uzd_fir_coef_tab2_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c28:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c29:12;
    };
}ich1_uzd_fir_coef_tab2_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c30:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  tab2_c31:12;
    };
}ich1_uzd_fir_coef_tab2_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  dummy18025400_23_20:4;
        RBus_UInt32  argb_dummy_data:8;
        RBus_UInt32  dummy18025400_11_10:2;
        RBus_UInt32  argb_swap:1;
        RBus_UInt32  rgb_to_argb_en:1;
        RBus_UInt32  dummy18025400_7:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  output_fmt:1;
        RBus_UInt32  buffer_mode:2;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  h_zoom_en:1;
    };
}ich2_uzd_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  lp121_en:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  h_y_filter:2;
        RBus_UInt32  h_c_filter:2;
    };
}ich2_uzd_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  hor_fac:25;
    };
}ich2_uzd_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  ver_fac:25;
    };
}ich2_uzd_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  ver_ini:8;
    };
}ich2_uzd_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  h_output_size:12;
    };
}ich2_uzd_h_output_size_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  conti:1;
        RBus_UInt32  start:1;
    };
}ich2_uzd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  uzd_crc:32;
    };
}ich2_uzd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  wd_fsync_ovf_en:1;
        RBus_UInt32  wd_fsync_udf_en:1;
        RBus_UInt32  wd_ibuff_ovf_en:1;
        RBus_UInt32  wd_ibuff_to_main:1;
        RBus_UInt32  wd_ibuff_to_sub:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  irq_fsync_ovf_en:1;
        RBus_UInt32  irq_fsync_udf_en:1;
        RBus_UInt32  irq_ibuff_ovf_en:1;
        RBus_UInt32  res3:8;
    };
}ich2_ibuff_status_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ibuf_v_size:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  ibuf_h_size:13;
    };
}ich2_ibuff_ctrl_i_buff_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  rgb565_en:1;
        RBus_UInt32  rgb_ch_swap:3;
    };
}ich2_uzd_channel_swap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  h_db_apply:1;
        RBus_UInt32  h_db_rd_sel:1;
        RBus_UInt32  h_db_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  v_db_apply:1;
        RBus_UInt32  v_db_rd_sel:1;
        RBus_UInt32  v_db_en:1;
    };
}ich2_uzd_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  q_sbs_lr_ovf:1;
        RBus_UInt32  q_sbs_lr_udf:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ibuff_ovf:1;
        RBus_UInt32  fsync_ovf:1;
        RBus_UInt32  fsync_udf:1;
    };
}ich2_ibuff_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  ch2_hsd_crc_conti:1;
        RBus_UInt32  ch2_hsd_crc_start:1;
    };
}ich2_hsd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_hsd_crc_result:32;
    };
}ich2_hsd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_ivst_en:1;
        RBus_UInt32  s_ihs_mode:1;
        RBus_UInt32  res1:29;
        RBus_UInt32  s_active_line_pixel_en:1;
    };
}measure_ctrl_ivst_result_sub_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  s_ivst_value_odd:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  s_ivst_value_even:12;
    };
}measure_ivst_result_sub_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  s_vactive_line_value:12;
        RBus_UInt32  res2:3;
        RBus_UInt32  s_hactive_hpixel_value:13;
    };
}measure_active_line_pixels_result_sub_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bisr_linebuf_fail_0:1;
    };
}ich2_sdnr_bisr_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  sdnr_drf_linebuf_fail_0:1;
    };
}ich2_sdnr_drf_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  sdnr_linebuf_ls_en:1;
        RBus_UInt32  sdnr_linebuf_dvse:1;
        RBus_UInt32  sdnr_linebuf_dvs:4;
    };
}ich2_sdnr_linebuf_dvs_RBUS;

#else //apply LITTLE_ENDIAN

//======SCALEDOWN register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  irq_ibuff_ovf_en:1;
        RBus_UInt32  irq_fsync_udf_en:1;
        RBus_UInt32  irq_fsync_ovf_en:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  wd_ibuff_to_sub:1;
        RBus_UInt32  wd_ibuff_to_main:1;
        RBus_UInt32  wd_ibuff_ovf_en:1;
        RBus_UInt32  wd_fsync_udf_en:1;
        RBus_UInt32  wd_fsync_ovf_en:1;
        RBus_UInt32  res3:11;
    };
}ich1_ibuff_status_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_zoom_en:1;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  buffer_mode:2;
        RBus_UInt32  h_c_table_sel:1;
        RBus_UInt32  h_y_table_sel:1;
        RBus_UInt32  v_c_table_sel:1;
        RBus_UInt32  v_y_table_sel:1;
        RBus_UInt32  sort_fmt:1;
        RBus_UInt32  out_bit:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  rgb_to_argb_en:1;
        RBus_UInt32  argb_swap:1;
        RBus_UInt32  dummy18025204_15:2;
        RBus_UInt32  argb_dummy_data:8;
        RBus_UInt32  truncationctrl:1;
        RBus_UInt32  sel_3d_en:1;
        RBus_UInt32  dummy18025204_26:1;
        RBus_UInt32  res1:5;
    };
}ich1_uzd_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsd_3d_mode:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  vsd_3d_boundary:13;
        RBus_UInt32  res2:9;
        RBus_UInt32  lp121_en:1;
        RBus_UInt32  res3:6;
    };
}ich1_uzd_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_fac:25;
        RBus_UInt32  res1:7;
    };
}ich1_uzd_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_fac:25;
        RBus_UInt32  ver_ini_int:1;
        RBus_UInt32  ver_ini_int_l:1;
        RBus_UInt32  res1:5;
    };
}ich1_uzd_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_ini:8;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  ver_ini_l:8;
        RBus_UInt32  hor_ini_l:8;
    };
}ich1_uzd_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  nl_d1:14;
        RBus_UInt32  res1:18;
    };
}ich1_uzd_hor_delta1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  nl_seg2:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  nl_seg1:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_hor_segment_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  start:1;
        RBus_UInt32  conti:1;
        RBus_UInt32  crc_3d_en:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  res1:27;
    };
}ich1_uzd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_l_result:32;
    };
}ich1_uzd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_r_result:32;
    };
}ich1_uzd_crc_result_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}ich1_uzd_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}ich1_uzd_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_crc_err_cnt:16;
        RBus_UInt32  r_crc_err_cnt:16;
    };
}ich1_uzd_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ibuf_h_size:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  ibuf_v_size:13;
        RBus_UInt32  res2:3;
    };
}ich1_ibuff_ctrl_i_buff_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rgb_ch_swap:3;
        RBus_UInt32  rgb565_en:1;
        RBus_UInt32  res1:28;
    };
}ich1_uzd_channel_swap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_db_en:1;
        RBus_UInt32  v_db_rd_sel:1;
        RBus_UInt32  v_db_apply:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  h_db_en:1;
        RBus_UInt32  h_db_rd_sel:1;
        RBus_UInt32  h_db_apply:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  mdom_comp_db_en:1;
        RBus_UInt32  mdom_comp_rd_sel:1;
        RBus_UInt32  res3:22;
    };
}ich1_uzd_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fsync_udf:1;
        RBus_UInt32  fsync_ovf:1;
        RBus_UInt32  ibuff_ovf:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  q_sbs_lr_udf:1;
        RBus_UInt32  q_sbs_lr_ovf:1;
        RBus_UInt32  res2:26;
    };
}ich1_ibuff_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_start:1;
        RBus_UInt32  ch1_hsd_crc_conti:1;
        RBus_UInt32  l_auto_cmp_en:1;
        RBus_UInt32  r_auto_cmp_en:1;
        RBus_UInt32  res1:28;
    };
}ich1_hsd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_l_result:32;
    };
}ich1_hsd_crc_result_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch1_hsd_crc_r_result:32;
    };
}ich1_hsd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_des_crc:32;
    };
}ich1_hsd_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_des_crc:32;
    };
}ich1_hsd_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_crc_err_cnt:16;
        RBus_UInt32  r_crc_err_cnt:16;
    };
}ich1_hsd_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_ivst_value_even:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  m_ivst_value_odd:12;
        RBus_UInt32  res2:4;
    };
}measure_ivst_result_main_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_hactive_hpixel_value:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  m_vactive_line_value:12;
        RBus_UInt32  res2:4;
    };
}measure_active_line_pixels_result_main_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  m_active_line_pixel_en:1;
        RBus_UInt32  res1:29;
        RBus_UInt32  m_ihs_mode:1;
        RBus_UInt32  m_ivst_en:1;
    };
}measure_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  read_en:1;
        RBus_UInt32  write_en:1;
        RBus_UInt32  res1:30;
    };
}accessdata_ctrl_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  startx:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  starty:13;
        RBus_UInt32  res2:3;
    };
}accessdata_posctrl_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y00:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  y01:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_y1_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y10:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  y11:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_y2_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u00:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v00:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c1_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u01:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v01:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c2_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u10:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v10:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c3_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  u11:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v11:10;
        RBus_UInt32  res2:6;
    };
}readdata_data_c4_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y:4;
        RBus_UInt32  u:4;
        RBus_UInt32  v:4;
        RBus_UInt32  res1:20;
    };
}writedata_data_uzd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_bist_fsbuf_fail_0:1;
        RBus_UInt32  sdnr_bist_fsbuf_fail_1:1;
        RBus_UInt32  sdnr_bist_fsbuf_fail_2:1;
        RBus_UInt32  sdnr_bist_fsbuf_fail_3:1;
        RBus_UInt32  res1:28;
    };
}ich1_sdnr_bist_fsbuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_drf_fsbuf_fail_0:1;
        RBus_UInt32  sdnr_drf_fsbuf_fail_1:1;
        RBus_UInt32  sdnr_drf_fsbuf_fail_2:1;
        RBus_UInt32  sdnr_drf_fsbuf_fail_3:1;
        RBus_UInt32  res1:28;
    };
}ich1_sdnr_drf_fsbuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bisr_linebuf_fail_0:1;
        RBus_UInt32  res1:31;
    };
}ich1_sdnr_bisr_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_drf_linebuf_fail_0:1;
        RBus_UInt32  res1:31;
    };
}ich1_sdnr_drf_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_linebuf_dvs:4;
        RBus_UInt32  sdnr_linebuf_dvse:1;
        RBus_UInt32  sdnr_linebuf_ls_en:1;
        RBus_UInt32  res1:26;
    };
}ich1_sdnr_linebuf_dvs_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_fsbuf_dvs0:4;
        RBus_UInt32  sdnr_fsbuf_dvse0:1;
        RBus_UInt32  sdnr_fsbuf_ls_en0:1;
        RBus_UInt32  res1:10;
        RBus_UInt32  sdnr_fsbuf_dvs1:4;
        RBus_UInt32  sdnr_fsbuf_dvse1:1;
        RBus_UInt32  sdnr_fsbuf_ls_en1:1;
        RBus_UInt32  res2:10;
    };
}ich1_sdnr_fsbuf_dvs01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_fsbuf_dvs2:4;
        RBus_UInt32  sdnr_fsbuf_dvse2:1;
        RBus_UInt32  sdnr_fsbuf_ls_en2:1;
        RBus_UInt32  res1:10;
        RBus_UInt32  sdnr_fsbuf_dvs3:4;
        RBus_UInt32  sdnr_fsbuf_dvse3:1;
        RBus_UInt32  sdnr_fsbuf_ls_en3:1;
        RBus_UInt32  res2:10;
    };
}ich1_sdnr_fsbuf_dvs23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy180252f0_0:1;
        RBus_UInt32  drop:1;
        RBus_UInt32  cr_dly_cb:1;
        RBus_UInt32  res1:29;
    };
}ich1_sdnr_444to422_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsd_3d_boundary:13;
        RBus_UInt32  res1:19;
    };
}ich1_hsd_3d_boundary_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c1:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c0:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c3:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c2:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c5:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c4:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c7:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c6:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c9:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c8:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c11:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c10:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c13:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c12:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c15:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c14:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c17:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c16:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c19:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c18:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c21:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c20:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c23:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c22:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c25:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c24:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c27:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c26:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c29:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c28:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab1_c31:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab1_c30:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab1_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c1:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c0:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c3:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c2:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c5:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c4:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c7:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c6:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c9:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c8:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c11:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c10:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c13:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c12:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c15:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c14:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c17:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c16:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c19:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c18:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c21:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c20:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c23:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c22:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c25:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c24:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c27:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c26:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c29:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c28:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tab2_c31:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  tab2_c30:12;
        RBus_UInt32  res2:4;
    };
}ich1_uzd_fir_coef_tab2_c30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_zoom_en:1;
        RBus_UInt32  v_zoom_en:1;
        RBus_UInt32  buffer_mode:2;
        RBus_UInt32  output_fmt:1;
        RBus_UInt32  odd_inv:1;
        RBus_UInt32  video_comp_en:1;
        RBus_UInt32  dummy18025400_7:1;
        RBus_UInt32  rgb_to_argb_en:1;
        RBus_UInt32  argb_swap:1;
        RBus_UInt32  dummy18025400_11:2;
        RBus_UInt32  argb_dummy_data:8;
        RBus_UInt32  dummy18025400_23:4;
        RBus_UInt32  res1:8;
    };
}ich2_uzd_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_c_filter:2;
        RBus_UInt32  h_y_filter:2;
        RBus_UInt32  res1:4;
        RBus_UInt32  lp121_en:1;
        RBus_UInt32  res2:23;
    };
}ich2_uzd_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hor_fac:25;
        RBus_UInt32  res1:7;
    };
}ich2_uzd_scale_hor_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_fac:25;
        RBus_UInt32  res1:7;
    };
}ich2_uzd_scale_ver_factor_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ver_ini:8;
        RBus_UInt32  hor_ini:8;
        RBus_UInt32  res1:16;
    };
}ich2_uzd_initial_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_output_size:12;
        RBus_UInt32  res1:20;
    };
}ich2_uzd_h_output_size_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  start:1;
        RBus_UInt32  conti:1;
        RBus_UInt32  res1:30;
    };
}ich2_uzd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  uzd_crc:32;
    };
}ich2_uzd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  irq_ibuff_ovf_en:1;
        RBus_UInt32  irq_fsync_udf_en:1;
        RBus_UInt32  irq_fsync_ovf_en:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  wd_ibuff_to_sub:1;
        RBus_UInt32  wd_ibuff_to_main:1;
        RBus_UInt32  wd_ibuff_ovf_en:1;
        RBus_UInt32  wd_fsync_udf_en:1;
        RBus_UInt32  wd_fsync_ovf_en:1;
        RBus_UInt32  res3:11;
    };
}ich2_ibuff_status_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ibuf_h_size:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  ibuf_v_size:13;
        RBus_UInt32  res2:3;
    };
}ich2_ibuff_ctrl_i_buff_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rgb_ch_swap:3;
        RBus_UInt32  rgb565_en:1;
        RBus_UInt32  res1:28;
    };
}ich2_uzd_channel_swap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_db_en:1;
        RBus_UInt32  v_db_rd_sel:1;
        RBus_UInt32  v_db_apply:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  h_db_en:1;
        RBus_UInt32  h_db_rd_sel:1;
        RBus_UInt32  h_db_apply:1;
        RBus_UInt32  res2:25;
    };
}ich2_uzd_db_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fsync_udf:1;
        RBus_UInt32  fsync_ovf:1;
        RBus_UInt32  ibuff_ovf:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  q_sbs_lr_udf:1;
        RBus_UInt32  q_sbs_lr_ovf:1;
        RBus_UInt32  res2:26;
    };
}ich2_ibuff_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_hsd_crc_start:1;
        RBus_UInt32  ch2_hsd_crc_conti:1;
        RBus_UInt32  res1:30;
    };
}ich2_hsd_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch2_hsd_crc_result:32;
    };
}ich2_hsd_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_active_line_pixel_en:1;
        RBus_UInt32  res1:29;
        RBus_UInt32  s_ihs_mode:1;
        RBus_UInt32  s_ivst_en:1;
    };
}measure_ctrl_ivst_result_sub_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_ivst_value_even:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  s_ivst_value_odd:12;
        RBus_UInt32  res2:4;
    };
}measure_ivst_result_sub_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  s_hactive_hpixel_value:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  s_vactive_line_value:12;
        RBus_UInt32  res2:4;
    };
}measure_active_line_pixels_result_sub_path_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bisr_linebuf_fail_0:1;
        RBus_UInt32  res1:31;
    };
}ich2_sdnr_bisr_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_drf_linebuf_fail_0:1;
        RBus_UInt32  res1:31;
    };
}ich2_sdnr_drf_linebuf_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sdnr_linebuf_dvs:4;
        RBus_UInt32  sdnr_linebuf_dvse:1;
        RBus_UInt32  sdnr_linebuf_ls_en:1;
        RBus_UInt32  res1:26;
    };
}ich2_sdnr_linebuf_dvs_RBUS;




#endif 


#endif 
