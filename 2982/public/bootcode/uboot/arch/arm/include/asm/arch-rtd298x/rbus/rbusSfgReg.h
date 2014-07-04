/**
* @file rbusSfgReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/27
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_SFG_REG_H_
#define _RBUS_SFG_REG_H_

#include "rbusTypes.h"




// SFG Register Address

#define SFG_SFG_ZZ_SHIFT_DBG_CTRL_VADDR            (0xb802d100)
#define SFG_SFG_SWAP_CTRL0_VADDR                   (0xb802d104)
#define SFG_SFG_SWAP_CTRL1_VADDR                   (0xb802d108)
#define SFG_SFG_CRC_CTRL_VADDR                     (0xb802d110)
#define SFG_SFG_CRC_RESULT_VADDR                   (0xb802d114)
#define SFG_SFG_CRC_R_RESULT_VADDR                 (0xb802d118)
#define SFG_SFG_L_DES_CRC_VADDR                    (0xb802d11c)
#define SFG_SFG_R_DES_CRC_VADDR                    (0xb802d120)
#define SFG_SFG_CRC_ERR_CNT_VADDR                  (0xb802d124)
#define SFG_SFG_FORCE_BG_AT_DIF_VADDR              (0xb802d128)
#define SFG_ZZ_CTRL_VADDR                          (0xb802d12c)
#define SFG_SFG_DUMMY_CTRL_0A_VADDR                (0xb802d130)
#define SFG_SFG_DUMMY_CTRL_0B_VADDR                (0xb802d134)
#define SFG_SFG_DUMMY_CTRL_1A_VADDR                (0xb802d138)
#define SFG_SFG_DUMMY_CTRL_1B_VADDR                (0xb802d13c)
#define SFG_SFG_DUMMY_CTRL_2A_VADDR                (0xb802d140)
#define SFG_SFG_DUMMY_CTRL_2B_VADDR                (0xb802d144)
#define SFG_SFG_DUMMY_CTRL_3A_VADDR                (0xb802d148)
#define SFG_SFG_DUMMY_CTRL_3B_VADDR                (0xb802d14c)
#define SFG_SFG_DUMMY_CTRL_4A_VADDR                (0xb802d150)
#define SFG_SFG_DUMMY_CTRL_4B_VADDR                (0xb802d154)
#define SFG_SFG_DUMMY_CTRL_5A_VADDR                (0xb802d158)
#define SFG_SFG_DUMMY_CTRL_5B_VADDR                (0xb802d15c)
#define SFG_SFG_DUMMY_CTRL_6A_VADDR                (0xb802d160)
#define SFG_SFG_DUMMY_CTRL_6B_VADDR                (0xb802d164)
#define SFG_SFG_DUMMY_CTRL_7A_VADDR                (0xb802d168)
#define SFG_SFG_DUMMY_CTRL_7B_VADDR                (0xb802d16c)
#define SFG_SFG_CTRL_0_VADDR                       (0xb802d170)
#define SFG_SFG_CTRL_1_VADDR                       (0xb802d174)
#define SFG_SFG_CTRL_2_VADDR                       (0xb802d178)
#define SFG_SFG_CTRL_3_VADDR                       (0xb802d17c)
#define SFG_SFG_CTRL_4_VADDR                       (0xb802d180)
#define SFG_SFG_CTRL_6_VADDR                       (0xb802d188)
#define SFG_SFG_CTRL_7_VADDR                       (0xb802d18c)
#define SFG_SFG_CTRL_8_VADDR                       (0xb802d190)
#define SFG_SFG_CTRL_9_VADDR                       (0xb802d194)
#define SFG_SFG_CTRL_5_VADDR                       (0xb802d198)
#define SFG_SFG_CTRL_A_VADDR                       (0xb802d19c)
#define SFG_SFG_CTRL_B_VADDR                       (0xb802d1a0)
#define SFG_SFG_CTRL_C_VADDR                       (0xb802d1a4)
#define SFG_SFG_TG_AUTO_1_VADDR                    (0xb802d1a8)
#define SFG_SFG_TG_AUTO_2_VADDR                    (0xb802d1ac)
#define SFG_SFG_TG_AUTO_3_VADDR                    (0xb802d1b0)
#define SFG_SFG_TG_AUTO_4_VADDR                    (0xb802d1b4)
#define SFG_SFG_DUMMY_VADDR                        (0xb802d1b8)
#define SFG_SFG_BIST_MODE_VADDR                    (0xb802d1bc)
#define SFG_SFG_BIST_DONE_VADDR                    (0xb802d1c0)
#define SFG_SFG_BIST_FAIL_GROUP_VADDR              (0xb802d1c4)
#define SFG_SFG_BIST_FAIL_VADDR                    (0xb802d1c8)
#define SFG_SFG_DRF_MODE_VADDR                     (0xb802d1d0)
#define SFG_SFG_DRF_RESUME_VADDR                   (0xb802d1d4)
#define SFG_SFG_DRF_DONE_VADDR                     (0xb802d1d8)
#define SFG_SFG_DRF_PAUSE_VADDR                    (0xb802d1dc)
#define SFG_SFG_DRF_FAIL_GROUP_VADDR               (0xb802d1e0)
#define SFG_SFG_DRF_FAI_VADDR                      (0xb802d1e4)
#define SFG_SFG_BIST_OTHER_VADDR                   (0xb802d1e8)
#define SFG_SFG_MID_DUMMY_0_VADDR                  (0xb802d1ec)
#define SFG_SFG_MID_DUMMY_1_VADDR                  (0xb802d1f0)
#define SFG_SFG_MID_DUMMY_2_VADDR                  (0xb802d1f4)
#define SFG_SFG_MID_DUMMY_3_VADDR                  (0xb802d1f8)
#define SFG_SFG_DATA_AFTER_DEN_VADDR               (0xb802d1fc)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======SFG register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  dout_pre_rb_swap:1;
        RBus_UInt32  dispd_debug_mode:3;
        RBus_UInt32  dout_mode:2;
        RBus_UInt32  dout_en:1;
        RBus_UInt32  dvs_inv:1;
        RBus_UInt32  dhs_inv:1;
        RBus_UInt32  dden_inv:1;
        RBus_UInt32  daclk_inv:1;
        RBus_UInt32  daclk_en:1;
        RBus_UInt32  dout_rb_swap:1;
        RBus_UInt32  dout_bit_swap:1;
        RBus_UInt32  dout_data_inv:1;
        RBus_UInt32  dclk_dly_sel:3;
    };
}sfg_zz_shift_dbg_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_mode_switch:2;
        RBus_UInt32  res1:14;
        RBus_UInt32  force_bg_dif_aport:1;
        RBus_UInt32  force_bg_dif_bport:1;
        RBus_UInt32  force_bg_dif_cport:1;
        RBus_UInt32  force_bg_dif_dport:1;
        RBus_UInt32  force_bg_dif_eport:1;
        RBus_UInt32  force_bg_dif_fport:1;
        RBus_UInt32  force_bg_dif_gport:1;
        RBus_UInt32  force_bg_dif_hport:1;
        RBus_UInt32  res2:8;
    };
}sfg_swap_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  output_porta:4;
        RBus_UInt32  output_portb:4;
        RBus_UInt32  output_portc:4;
        RBus_UInt32  output_portd:4;
        RBus_UInt32  output_porte:4;
        RBus_UInt32  output_portf:4;
        RBus_UInt32  output_portg:4;
        RBus_UInt32  output_porth:4;
    };
}sfg_swap_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  sfg_crc_mode:1;
        RBus_UInt32  sfg_crc_l_auto_cmp_en:1;
        RBus_UInt32  sfg_crc_r_auto_cmp_en:1;
        RBus_UInt32  sfg_crc_conti:1;
        RBus_UInt32  sfg_crc_start:1;
    };
}sfg_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_crc_result_0:32;
    };
}sfg_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_crc_result_1:32;
    };
}sfg_crc_r_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_l_des_crc:32;
    };
}sfg_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_r_des_crc:32;
    };
}sfg_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_l_crc_err_cnt:16;
        RBus_UInt32  sfg_r_crc_err_cnt:16;
    };
}sfg_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  en_force_bg_dif:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  bg_dif_red:10;
        RBus_UInt32  bg_dif_grn:10;
        RBus_UInt32  bg_dif_blu:10;
    };
}sfg_force_bg_at_dif_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  zz_shift_last_sel_0:2;
        RBus_UInt32  zz_shift_last_sel_1:2;
        RBus_UInt32  zz_shift_last_sel_2:2;
        RBus_UInt32  zz_shift_last_sel_3:2;
        RBus_UInt32  zz_shift_1st_sel_0:2;
        RBus_UInt32  zz_shift_1st_sel_1:2;
        RBus_UInt32  zz_shift_1st_sel_2:2;
        RBus_UInt32  zz_shift_1st_sel_3:2;
        RBus_UInt32  zz_shift_sp_0:2;
        RBus_UInt32  zz_shift_sp_1:2;
        RBus_UInt32  zz_shift_sp_2:2;
        RBus_UInt32  zz_shift_sp_3:2;
        RBus_UInt32  zz_shift_mode_0:1;
        RBus_UInt32  zz_shift_mode_1:1;
        RBus_UInt32  zz_shift_mode_2:1;
        RBus_UInt32  zz_shift_mode_3:1;
        RBus_UInt32  res1:4;
    };
}zz_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_0_front_dummy_num_0:8;
        RBus_UInt32  seg_0_back_dummy_num_0:8;
        RBus_UInt32  seg_0_front_dummy_num_1:8;
        RBus_UInt32  seg_0_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_0_front_dummy_num_2:8;
        RBus_UInt32  seg_0_back_dummy_num_2:8;
        RBus_UInt32  seg_0_front_dummy_num_3:8;
        RBus_UInt32  seg_0_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_1_front_dummy_num_0:8;
        RBus_UInt32  seg_1_back_dummy_num_0:8;
        RBus_UInt32  seg_1_front_dummy_num_1:8;
        RBus_UInt32  seg_1_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_1a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_1_front_dummy_num_2:8;
        RBus_UInt32  seg_1_back_dummy_num_2:8;
        RBus_UInt32  seg_1_front_dummy_num_3:8;
        RBus_UInt32  seg_1_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_1b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_2_front_dummy_num_0:8;
        RBus_UInt32  seg_2_back_dummy_num_0:8;
        RBus_UInt32  seg_2_front_dummy_num_1:8;
        RBus_UInt32  seg_2_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_2a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_2_front_dummy_num_2:8;
        RBus_UInt32  seg_2_back_dummy_num_2:8;
        RBus_UInt32  seg_2_front_dummy_num_3:8;
        RBus_UInt32  seg_2_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_2b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_3_front_dummy_num_0:8;
        RBus_UInt32  seg_3_back_dummy_num_0:8;
        RBus_UInt32  seg_3_front_dummy_num_1:8;
        RBus_UInt32  seg_3_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_3a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_3_front_dummy_num_2:8;
        RBus_UInt32  seg_3_back_dummy_num_2:8;
        RBus_UInt32  seg_3_front_dummy_num_3:8;
        RBus_UInt32  seg_3_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_3b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_4_front_dummy_num_0:8;
        RBus_UInt32  seg_4_back_dummy_num_0:8;
        RBus_UInt32  seg_4_front_dummy_num_1:8;
        RBus_UInt32  seg_4_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_4a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_4_front_dummy_num_2:8;
        RBus_UInt32  seg_4_back_dummy_num_2:8;
        RBus_UInt32  seg_4_front_dummy_num_3:8;
        RBus_UInt32  seg_4_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_4b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_5_front_dummy_num_0:8;
        RBus_UInt32  seg_5_back_dummy_num_0:8;
        RBus_UInt32  seg_5_front_dummy_num_1:8;
        RBus_UInt32  seg_5_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_5a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_5_front_dummy_num_2:8;
        RBus_UInt32  seg_5_back_dummy_num_2:8;
        RBus_UInt32  seg_5_front_dummy_num_3:8;
        RBus_UInt32  seg_5_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_5b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_6_front_dummy_num_0:8;
        RBus_UInt32  seg_6_back_dummy_num_0:8;
        RBus_UInt32  seg_6_front_dummy_num_1:8;
        RBus_UInt32  seg_6_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_6a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_6_front_dummy_num_2:8;
        RBus_UInt32  seg_6_back_dummy_num_2:8;
        RBus_UInt32  seg_6_front_dummy_num_3:8;
        RBus_UInt32  seg_6_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_6b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_7_front_dummy_num_0:8;
        RBus_UInt32  seg_7_back_dummy_num_0:8;
        RBus_UInt32  seg_7_front_dummy_num_1:8;
        RBus_UInt32  seg_7_back_dummy_num_1:8;
    };
}sfg_dummy_ctrl_7a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_7_front_dummy_num_2:8;
        RBus_UInt32  seg_7_back_dummy_num_2:8;
        RBus_UInt32  seg_7_front_dummy_num_3:8;
        RBus_UInt32  seg_7_back_dummy_num_3:8;
    };
}sfg_dummy_ctrl_7b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy_0:2;
        RBus_UInt32  data_mode:2;
        RBus_UInt32  dummy_1:2;
        RBus_UInt32  mask_one_eye_black_en:1;
        RBus_UInt32  mask_one_eye_black_left:1;
        RBus_UInt32  dummy_pixel_shift_en:1;
        RBus_UInt32  res1:14;
        RBus_UInt32  h_flip_en:1;
        RBus_UInt32  seg_num:4;
        RBus_UInt32  port_num:4;
    };
}sfg_ctrl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg0_start_res:4;
        RBus_UInt32  seg0_start:12;
        RBus_UInt32  seg1_start_res:4;
        RBus_UInt32  seg1_start:12;
    };
}sfg_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg2_start_res:4;
        RBus_UInt32  seg2_start:12;
        RBus_UInt32  seg3_start_res:4;
        RBus_UInt32  seg3_start:12;
    };
}sfg_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg4_start_res:4;
        RBus_UInt32  seg4_start:12;
        RBus_UInt32  seg5_start_res:4;
        RBus_UInt32  seg5_start:12;
    };
}sfg_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg6_start_res:4;
        RBus_UInt32  seg6_start:12;
        RBus_UInt32  seg7_start_res:4;
        RBus_UInt32  seg7_start:12;
    };
}sfg_ctrl_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bypass_mode:1;
        RBus_UInt32  tg_auto_cfg:1;
        RBus_UInt32  pif_2d2g_hs_sel:1;
        RBus_UInt32  s2p_en:1;
        RBus_UInt32  subpixel0_0:4;
        RBus_UInt32  subpixel1_0:4;
        RBus_UInt32  subpixel2_0:4;
        RBus_UInt32  subpixel0_1:4;
        RBus_UInt32  subpixel1_1:4;
        RBus_UInt32  subpixel2_1:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  debug_sel:3;
    };
}sfg_ctrl_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  hsync_width:8;
        RBus_UInt32  hsync_delay:16;
    };
}sfg_ctrl_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  vsync_end:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  vsync_start:8;
    };
}sfg_ctrl_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_dh_den_sta:16;
        RBus_UInt32  req_start:16;
    };
}sfg_ctrl_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hs_distance:16;
        RBus_UInt32  res1:15;
        RBus_UInt32  seg0_flip:1;
    };
}sfg_ctrl_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  final_line_length:13;
        RBus_UInt32  hsync_threshold:16;
    };
}sfg_ctrl_a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  residue_pix_div_12_split_mode:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  final_addr_split_mode:10;
    };
}sfg_ctrl_b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  hs_den_io_dist:12;
        RBus_UInt32  hs_io_dist:12;
    };
}sfg_ctrl_c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_delay_auto:16;
        RBus_UInt32  req_start_auto:16;
    };
}sfg_tg_auto_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  pif_2d2g_hs_sel_auto:1;
        RBus_UInt32  vsync_start_auto:8;
        RBus_UInt32  vsync_end_auto:8;
        RBus_UInt32  hsync_width_auto:8;
    };
}sfg_tg_auto_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  dummy_read:1;
        RBus_UInt32  hs_den_io_dist_auto:12;
        RBus_UInt32  hs_io_dist_auto:12;
    };
}sfg_tg_auto_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_dh_den_sta_auto:16;
        RBus_UInt32  res1:16;
    };
}sfg_tg_auto_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy_2:15;
        RBus_UInt32  in_data_inv:1;
        RBus_UInt32  line0_g0_sel:2;
        RBus_UInt32  line0_glast_sel:2;
        RBus_UInt32  line1_g0_sel:2;
        RBus_UInt32  line1_glast_sel:2;
        RBus_UInt32  line2_g0_sel:2;
        RBus_UInt32  line2_glast_sel:2;
        RBus_UInt32  line3_g0_sel:2;
        RBus_UInt32  line3_glast_sel:2;
    };
}sfg_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_bist_mode:1;
        RBus_UInt32  sfg_0_bist_mode:1;
    };
}sfg_bist_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_bist_done:1;
        RBus_UInt32  sfg_0_bist_done:1;
    };
}sfg_bist_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_bist_fail_group:1;
        RBus_UInt32  sfg_0_bist_fail_group:1;
    };
}sfg_bist_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  sfg_1_bist_fail_1:1;
        RBus_UInt32  sfg_1_bist_fail_0:1;
        RBus_UInt32  sfg_0_bist_fail_1:1;
        RBus_UInt32  sfg_0_bist_fail_0:1;
    };
}sfg_bist_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_drf_mode:1;
        RBus_UInt32  sfg_0_drf_mode:1;
    };
}sfg_drf_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_drf_resume:1;
        RBus_UInt32  sfg_0_drf_resume:1;
    };
}sfg_drf_resume_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_drf_done:1;
        RBus_UInt32  sfg_0_drf_done:1;
    };
}sfg_drf_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_drf_pause:1;
        RBus_UInt32  sfg_0_drf_pause:1;
    };
}sfg_drf_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  sfg_1_drf_fail_group:1;
        RBus_UInt32  sfg_0_drf_fail_group:1;
    };
}sfg_drf_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  sfg_1_drf_fail_1:1;
        RBus_UInt32  sfg_1_drf_fail_0:1;
        RBus_UInt32  sfg_0_drf_fail_1:1;
        RBus_UInt32  sfg_0_drf_fail_0:1;
    };
}sfg_drf_fai_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_bist_rst_n:1;
        RBus_UInt32  sfg_1_bist_rst_n:1;
        RBus_UInt32  res1:24;
        RBus_UInt32  sfg_bist_ls:1;
        RBus_UInt32  sfg_bist_rm:4;
        RBus_UInt32  sfg_bist_rme:1;
    };
}sfg_bist_other_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg0_mid_dummy_place:12;
        RBus_UInt32  seg0_mid_dummy_num:4;
        RBus_UInt32  seg1_mid_dummy_place:12;
        RBus_UInt32  seg1_mid_dummy_num:4;
    };
}sfg_mid_dummy_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg2_mid_dummy_place:12;
        RBus_UInt32  seg2_mid_dummy_num:4;
        RBus_UInt32  seg3_mid_dummy_place:12;
        RBus_UInt32  seg3_mid_dummy_num:4;
    };
}sfg_mid_dummy_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg4_mid_dummy_place:12;
        RBus_UInt32  seg4_mid_dummy_num:4;
        RBus_UInt32  seg5_mid_dummy_place:12;
        RBus_UInt32  seg5_mid_dummy_num:4;
    };
}sfg_mid_dummy_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg6_mid_dummy_place:12;
        RBus_UInt32  seg6_mid_dummy_num:4;
        RBus_UInt32  seg7_mid_dummy_place:12;
        RBus_UInt32  seg7_mid_dummy_num:4;
    };
}sfg_mid_dummy_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  active_pixel_rgb:13;
        RBus_UInt32  res2:2;
        RBus_UInt32  last_ext_pixel:6;
    };
}sfg_data_after_den_RBUS;





#else //apply LITTLE_ENDIAN


//======SFG register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_dly_sel:3;
        RBus_UInt32  dout_data_inv:1;
        RBus_UInt32  dout_bit_swap:1;
        RBus_UInt32  dout_rb_swap:1;
        RBus_UInt32  daclk_en:1;
        RBus_UInt32  daclk_inv:1;
        RBus_UInt32  dden_inv:1;
        RBus_UInt32  dhs_inv:1;
        RBus_UInt32  dvs_inv:1;
        RBus_UInt32  dout_en:1;
        RBus_UInt32  dout_mode:2;
        RBus_UInt32  dispd_debug_mode:3;
        RBus_UInt32  dout_pre_rb_swap:1;
        RBus_UInt32  res1:14;
    };
}sfg_zz_shift_dbg_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:8;
        RBus_UInt32  force_bg_dif_hport:1;
        RBus_UInt32  force_bg_dif_gport:1;
        RBus_UInt32  force_bg_dif_fport:1;
        RBus_UInt32  force_bg_dif_eport:1;
        RBus_UInt32  force_bg_dif_dport:1;
        RBus_UInt32  force_bg_dif_cport:1;
        RBus_UInt32  force_bg_dif_bport:1;
        RBus_UInt32  force_bg_dif_aport:1;
        RBus_UInt32  res1:14;
        RBus_UInt32  dclk_mode_switch:2;
    };
}sfg_swap_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  output_porth:4;
        RBus_UInt32  output_portg:4;
        RBus_UInt32  output_portf:4;
        RBus_UInt32  output_porte:4;
        RBus_UInt32  output_portd:4;
        RBus_UInt32  output_portc:4;
        RBus_UInt32  output_portb:4;
        RBus_UInt32  output_porta:4;
    };
}sfg_swap_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_crc_start:1;
        RBus_UInt32  sfg_crc_conti:1;
        RBus_UInt32  sfg_crc_r_auto_cmp_en:1;
        RBus_UInt32  sfg_crc_l_auto_cmp_en:1;
        RBus_UInt32  sfg_crc_mode:1;
        RBus_UInt32  res1:27;
    };
}sfg_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_crc_result_0:32;
    };
}sfg_crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_crc_result_1:32;
    };
}sfg_crc_r_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_l_des_crc:32;
    };
}sfg_l_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_r_des_crc:32;
    };
}sfg_r_des_crc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_r_crc_err_cnt:16;
        RBus_UInt32  sfg_l_crc_err_cnt:16;
    };
}sfg_crc_err_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bg_dif_blu:10;
        RBus_UInt32  bg_dif_grn:10;
        RBus_UInt32  bg_dif_red:10;
        RBus_UInt32  res1:1;
        RBus_UInt32  en_force_bg_dif:1;
    };
}sfg_force_bg_at_dif_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  zz_shift_mode_3:1;
        RBus_UInt32  zz_shift_mode_2:1;
        RBus_UInt32  zz_shift_mode_1:1;
        RBus_UInt32  zz_shift_mode_0:1;
        RBus_UInt32  zz_shift_sp_3:2;
        RBus_UInt32  zz_shift_sp_2:2;
        RBus_UInt32  zz_shift_sp_1:2;
        RBus_UInt32  zz_shift_sp_0:2;
        RBus_UInt32  zz_shift_1st_sel_3:2;
        RBus_UInt32  zz_shift_1st_sel_2:2;
        RBus_UInt32  zz_shift_1st_sel_1:2;
        RBus_UInt32  zz_shift_1st_sel_0:2;
        RBus_UInt32  zz_shift_last_sel_3:2;
        RBus_UInt32  zz_shift_last_sel_2:2;
        RBus_UInt32  zz_shift_last_sel_1:2;
        RBus_UInt32  zz_shift_last_sel_0:2;
    };
}zz_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_0_back_dummy_num_1:8;
        RBus_UInt32  seg_0_front_dummy_num_1:8;
        RBus_UInt32  seg_0_back_dummy_num_0:8;
        RBus_UInt32  seg_0_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_0_back_dummy_num_3:8;
        RBus_UInt32  seg_0_front_dummy_num_3:8;
        RBus_UInt32  seg_0_back_dummy_num_2:8;
        RBus_UInt32  seg_0_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_1_back_dummy_num_1:8;
        RBus_UInt32  seg_1_front_dummy_num_1:8;
        RBus_UInt32  seg_1_back_dummy_num_0:8;
        RBus_UInt32  seg_1_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_1a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_1_back_dummy_num_3:8;
        RBus_UInt32  seg_1_front_dummy_num_3:8;
        RBus_UInt32  seg_1_back_dummy_num_2:8;
        RBus_UInt32  seg_1_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_1b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_2_back_dummy_num_1:8;
        RBus_UInt32  seg_2_front_dummy_num_1:8;
        RBus_UInt32  seg_2_back_dummy_num_0:8;
        RBus_UInt32  seg_2_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_2a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_2_back_dummy_num_3:8;
        RBus_UInt32  seg_2_front_dummy_num_3:8;
        RBus_UInt32  seg_2_back_dummy_num_2:8;
        RBus_UInt32  seg_2_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_2b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_3_back_dummy_num_1:8;
        RBus_UInt32  seg_3_front_dummy_num_1:8;
        RBus_UInt32  seg_3_back_dummy_num_0:8;
        RBus_UInt32  seg_3_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_3a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_3_back_dummy_num_3:8;
        RBus_UInt32  seg_3_front_dummy_num_3:8;
        RBus_UInt32  seg_3_back_dummy_num_2:8;
        RBus_UInt32  seg_3_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_3b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_4_back_dummy_num_1:8;
        RBus_UInt32  seg_4_front_dummy_num_1:8;
        RBus_UInt32  seg_4_back_dummy_num_0:8;
        RBus_UInt32  seg_4_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_4a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_4_back_dummy_num_3:8;
        RBus_UInt32  seg_4_front_dummy_num_3:8;
        RBus_UInt32  seg_4_back_dummy_num_2:8;
        RBus_UInt32  seg_4_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_4b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_5_back_dummy_num_1:8;
        RBus_UInt32  seg_5_front_dummy_num_1:8;
        RBus_UInt32  seg_5_back_dummy_num_0:8;
        RBus_UInt32  seg_5_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_5a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_5_back_dummy_num_3:8;
        RBus_UInt32  seg_5_front_dummy_num_3:8;
        RBus_UInt32  seg_5_back_dummy_num_2:8;
        RBus_UInt32  seg_5_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_5b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_6_back_dummy_num_1:8;
        RBus_UInt32  seg_6_front_dummy_num_1:8;
        RBus_UInt32  seg_6_back_dummy_num_0:8;
        RBus_UInt32  seg_6_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_6a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_6_back_dummy_num_3:8;
        RBus_UInt32  seg_6_front_dummy_num_3:8;
        RBus_UInt32  seg_6_back_dummy_num_2:8;
        RBus_UInt32  seg_6_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_6b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_7_back_dummy_num_1:8;
        RBus_UInt32  seg_7_front_dummy_num_1:8;
        RBus_UInt32  seg_7_back_dummy_num_0:8;
        RBus_UInt32  seg_7_front_dummy_num_0:8;
    };
}sfg_dummy_ctrl_7a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg_7_back_dummy_num_3:8;
        RBus_UInt32  seg_7_front_dummy_num_3:8;
        RBus_UInt32  seg_7_back_dummy_num_2:8;
        RBus_UInt32  seg_7_front_dummy_num_2:8;
    };
}sfg_dummy_ctrl_7b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  port_num:4;
        RBus_UInt32  seg_num:4;
        RBus_UInt32  h_flip_en:1;
        RBus_UInt32  res1:14;
        RBus_UInt32  dummy_pixel_shift_en:1;
        RBus_UInt32  mask_one_eye_black_left:1;
        RBus_UInt32  mask_one_eye_black_en:1;
        RBus_UInt32  dummy_1:2;
        RBus_UInt32  data_mode:2;
        RBus_UInt32  dummy_0:2;
    };
}sfg_ctrl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg1_start:12;
        RBus_UInt32  seg1_start_res:4;
        RBus_UInt32  seg0_start:12;
        RBus_UInt32  seg0_start_res:4;
    };
}sfg_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg3_start:12;
        RBus_UInt32  seg3_start_res:4;
        RBus_UInt32  seg2_start:12;
        RBus_UInt32  seg2_start_res:4;
    };
}sfg_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg5_start:12;
        RBus_UInt32  seg5_start_res:4;
        RBus_UInt32  seg4_start:12;
        RBus_UInt32  seg4_start_res:4;
    };
}sfg_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg7_start:12;
        RBus_UInt32  seg7_start_res:4;
        RBus_UInt32  seg6_start:12;
        RBus_UInt32  seg6_start_res:4;
    };
}sfg_ctrl_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  debug_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  subpixel2_1:4;
        RBus_UInt32  subpixel1_1:4;
        RBus_UInt32  subpixel0_1:4;
        RBus_UInt32  subpixel2_0:4;
        RBus_UInt32  subpixel1_0:4;
        RBus_UInt32  subpixel0_0:4;
        RBus_UInt32  s2p_en:1;
        RBus_UInt32  pif_2d2g_hs_sel:1;
        RBus_UInt32  tg_auto_cfg:1;
        RBus_UInt32  bypass_mode:1;
    };
}sfg_ctrl_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_delay:16;
        RBus_UInt32  hsync_width:8;
        RBus_UInt32  res1:8;
    };
}sfg_ctrl_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_start:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  vsync_end:8;
        RBus_UInt32  res1:8;
    };
}sfg_ctrl_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  req_start:16;
        RBus_UInt32  sfg_dh_den_sta:16;
    };
}sfg_ctrl_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg0_flip:1;
        RBus_UInt32  res1:15;
        RBus_UInt32  hs_distance:16;
    };
}sfg_ctrl_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_threshold:16;
        RBus_UInt32  final_line_length:13;
        RBus_UInt32  res1:3;
    };
}sfg_ctrl_a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  final_addr_split_mode:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  residue_pix_div_12_split_mode:4;
        RBus_UInt32  res1:16;
    };
}sfg_ctrl_b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hs_io_dist:12;
        RBus_UInt32  hs_den_io_dist:12;
        RBus_UInt32  res1:8;
    };
}sfg_ctrl_c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  req_start_auto:16;
        RBus_UInt32  hsync_delay_auto:16;
    };
}sfg_tg_auto_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_width_auto:8;
        RBus_UInt32  vsync_end_auto:8;
        RBus_UInt32  vsync_start_auto:8;
        RBus_UInt32  pif_2d2g_hs_sel_auto:1;
        RBus_UInt32  res1:7;
    };
}sfg_tg_auto_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hs_io_dist_auto:12;
        RBus_UInt32  hs_den_io_dist_auto:12;
        RBus_UInt32  dummy_read:1;
        RBus_UInt32  res1:7;
    };
}sfg_tg_auto_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  sfg_dh_den_sta_auto:16;
    };
}sfg_tg_auto_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  line3_glast_sel:2;
        RBus_UInt32  line3_g0_sel:2;
        RBus_UInt32  line2_glast_sel:2;
        RBus_UInt32  line2_g0_sel:2;
        RBus_UInt32  line1_glast_sel:2;
        RBus_UInt32  line1_g0_sel:2;
        RBus_UInt32  line0_glast_sel:2;
        RBus_UInt32  line0_g0_sel:2;
        RBus_UInt32  in_data_inv:1;
        RBus_UInt32  dummy_2:15;
    };
}sfg_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_bist_mode:1;
        RBus_UInt32  sfg_1_bist_mode:1;
        RBus_UInt32  res1:30;
    };
}sfg_bist_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_bist_done:1;
        RBus_UInt32  sfg_1_bist_done:1;
        RBus_UInt32  res1:30;
    };
}sfg_bist_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_bist_fail_group:1;
        RBus_UInt32  sfg_1_bist_fail_group:1;
        RBus_UInt32  res1:30;
    };
}sfg_bist_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_bist_fail_0:1;
        RBus_UInt32  sfg_0_bist_fail_1:1;
        RBus_UInt32  sfg_1_bist_fail_0:1;
        RBus_UInt32  sfg_1_bist_fail_1:1;
        RBus_UInt32  res1:28;
    };
}sfg_bist_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_drf_mode:1;
        RBus_UInt32  sfg_1_drf_mode:1;
        RBus_UInt32  res1:30;
    };
}sfg_drf_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_drf_resume:1;
        RBus_UInt32  sfg_1_drf_resume:1;
        RBus_UInt32  res1:30;
    };
}sfg_drf_resume_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_drf_done:1;
        RBus_UInt32  sfg_1_drf_done:1;
        RBus_UInt32  res1:30;
    };
}sfg_drf_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_drf_pause:1;
        RBus_UInt32  sfg_1_drf_pause:1;
        RBus_UInt32  res1:30;
    };
}sfg_drf_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_drf_fail_group:1;
        RBus_UInt32  sfg_1_drf_fail_group:1;
        RBus_UInt32  res1:30;
    };
}sfg_drf_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_0_drf_fail_0:1;
        RBus_UInt32  sfg_0_drf_fail_1:1;
        RBus_UInt32  sfg_1_drf_fail_0:1;
        RBus_UInt32  sfg_1_drf_fail_1:1;
        RBus_UInt32  res1:28;
    };
}sfg_drf_fai_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sfg_bist_rme:1;
        RBus_UInt32  sfg_bist_rm:4;
        RBus_UInt32  sfg_bist_ls:1;
        RBus_UInt32  res1:24;
        RBus_UInt32  sfg_1_bist_rst_n:1;
        RBus_UInt32  sfg_0_bist_rst_n:1;
    };
}sfg_bist_other_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg1_mid_dummy_num:4;
        RBus_UInt32  seg1_mid_dummy_place:12;
        RBus_UInt32  seg0_mid_dummy_num:4;
        RBus_UInt32  seg0_mid_dummy_place:12;
    };
}sfg_mid_dummy_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg3_mid_dummy_num:4;
        RBus_UInt32  seg3_mid_dummy_place:12;
        RBus_UInt32  seg2_mid_dummy_num:4;
        RBus_UInt32  seg2_mid_dummy_place:12;
    };
}sfg_mid_dummy_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg5_mid_dummy_num:4;
        RBus_UInt32  seg5_mid_dummy_place:12;
        RBus_UInt32  seg4_mid_dummy_num:4;
        RBus_UInt32  seg4_mid_dummy_place:12;
    };
}sfg_mid_dummy_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  seg7_mid_dummy_num:4;
        RBus_UInt32  seg7_mid_dummy_place:12;
        RBus_UInt32  seg6_mid_dummy_num:4;
        RBus_UInt32  seg6_mid_dummy_place:12;
    };
}sfg_mid_dummy_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  last_ext_pixel:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  active_pixel_rgb:13;
        RBus_UInt32  res1:11;
    };
}sfg_data_after_den_RBUS;


#endif







#endif //_RBUS_SFG_REG_H_

