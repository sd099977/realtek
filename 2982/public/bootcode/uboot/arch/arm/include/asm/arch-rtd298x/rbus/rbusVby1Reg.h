/**
* @file rbusVby1Reg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013-5-30
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_VBY1_REG_H_
#define _RBUS_VBY1_REG_H_

#include "rbus/rbusTypes.h"




// VBY1 Register Address

#define VBY1_VIDEO_FORMAT_VADDR                    (0xb802d600)
#define VBY1_LANE_STATUS_VADDR                     (0xb802d604)
#define VBY1_CTL_VADDR                             (0xb802d608)
#define VBY1_PLL_TRACKING_VADDR                    (0xb802d60c)
#define VBY1_TRANSMIT_CONTROL_VADDR                (0xb802d610)
#define VBY1_TRANSMIT_STATUS_VADDR                 (0xb802d614)
#define VBY1_THREE_FLAG_VADDR                      (0xb802d618)
#define VBY1_INTERRUPT_VADDR                       (0xb802d61c)
#define VBY1_CRC_CONTROL_VADDR                     (0xb802d620)
#define VBY1_CRC_RESULT_VADDR                      (0xb802d624)
#define VBY1_CTS_FIFO_VADDR                        (0xb802d628)
#define VBY1_VBY1_BIST_VADDR                       (0xb802d62c)
#define VBY1_VBY1_BIST0_0_VADDR                    (0xb802d630)
#define VBY1_VBY1_BIST0_1_VADDR                    (0xb802d634)
#define VBY1_VBY1_BIST0_2_VADDR                    (0xb802d638)
#define VBY1_VBY1_BIST0_3_VADDR                    (0xb802d63c)
#define VBY1_VBY1_BIST4_VADDR                      (0xb802d640)
#define VBY1_VBY1_DEBUG_VADDR                      (0xb802d644)
#define VBY1_VBY1_FW_CTRL_VADDR                    (0xb802d648)
#define VBY1_VBY1_OUT_CTRL_VADDR                   (0xb802d64c)
#define VBY1_VBY1_BIT_SHIFT_CTRL_VADDR             (0xb802d650)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======VBY1 register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  color_format:4;
        RBus_UInt32  res2:6;
        RBus_UInt32  win:10;
    };
}video_format_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  pixel_mode:3;
        RBus_UInt32  res2:3;
        RBus_UInt32  lane_count:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  section:5;
        RBus_UInt32  res4:5;
        RBus_UInt32  byte_mode:3;
    };
}lane_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  ctl:24;
    };
}ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  over_boundary:1;
        RBus_UInt32  under_boundary:1;
        RBus_UInt32  res1:25;
        RBus_UInt32  reg_boundary:5;
    };
}pll_tracking_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_en:1;
        RBus_UInt32  pll_stable:1;
        RBus_UInt32  transfer_en:1;
        RBus_UInt32  video_trans_mode:1;
        RBus_UInt32  debounce_cnt:4;
        RBus_UInt32  dummy1802d610_23_22:2;
        RBus_UInt32  reg_delay:22;
    };
}transmit_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802d614_31_8:24;
        RBus_UInt32  reset_sel:1;
        RBus_UInt32  num_check_fail:1;
        RBus_UInt32  aln_finish:1;
        RBus_UInt32  initial_finish:1;
        RBus_UInt32  cdr_out_en:1;
        RBus_UInt32  video_en:1;
        RBus_UInt32  aln_en:1;
        RBus_UInt32  initial_en:1;
    };
}transmit_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  three_mode:2;
        RBus_UInt32  three_en:1;
    };
}three_flag_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802d61c_31_8:24;
        RBus_UInt32  int_async_over_boundary_en:1;
        RBus_UInt32  int_async_under_boundary_en:1;
        RBus_UInt32  int_cts_full_en:1;
        RBus_UInt32  int_cts_empty_en:1;
        RBus_UInt32  int_async_over_boundary:1;
        RBus_UInt32  int_async_under_boundary:1;
        RBus_UInt32  int_cts_full:1;
        RBus_UInt32  int_cts_empty:1;
    };
}interrupt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  reg_crc_start:1;
        RBus_UInt32  reg_crc_conti:1;
    };
}crc_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_result:32;
    };
}crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  rd_addr_initial:4;
        RBus_UInt32  full_boundary:4;
        RBus_UInt32  empty_boundary:4;
        RBus_UInt32  dummy1802d628_6_5:2;
        RBus_UInt32  force_rstn_delay_en:1;
        RBus_UInt32  force_rstn:1;
        RBus_UInt32  en_bypass:1;
        RBus_UInt32  full_mask_error:1;
        RBus_UInt32  empty_mask_error:1;
    };
}cts_fifo_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  vby1_drf_pause:1;
        RBus_UInt32  vby1_drf_done:1;
        RBus_UInt32  vby1_bist_done:1;
        RBus_UInt32  vby1_drf_resume:1;
        RBus_UInt32  vby1_drf_mode:1;
        RBus_UInt32  vby1_bist_mode:1;
    };
}vby1_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_0:1;
    };
}vby1_bist0_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  drf_bist_fail_3:1;
        RBus_UInt32  drf_bist_fail_2:1;
        RBus_UInt32  drf_bist_fail_1:1;
        RBus_UInt32  drf_bist_fail_0:1;
    };
}vby1_bist0_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_0:4;
    };
}vby1_bist0_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802d63c_31_4:28;
        RBus_UInt32  ls_3:1;
        RBus_UInt32  ls_2:1;
        RBus_UInt32  ls_1:1;
        RBus_UInt32  ls_0:1;
    };
}vby1_bist0_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802d640_31_0:32;
    };
}vby1_bist4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  debug_mode:5;
    };
}vby1_debug_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_htpdn_ctrl:1;
        RBus_UInt32  fw_lockn_ctrl:1;
        RBus_UInt32  res1:28;
        RBus_UInt32  fw_htpdn:1;
        RBus_UInt32  fw_lockn:1;
    };
}vby1_fw_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  lsb_msb_swap:1;
        RBus_UInt32  lane_swap:1;
    };
}vby1_out_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bit_shift_enable:1;
        RBus_UInt32  res1:19;
        RBus_UInt32  output_bit:4;
        RBus_UInt32  res2:6;
        RBus_UInt32  shift_bit:2;
    };
}vby1_bit_shift_ctrl_RBUS;

#else //apply LITTLE_ENDIAN


//======VBY1 register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  win:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  color_format:4;
        RBus_UInt32  res2:12;
    };
}video_format_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  byte_mode:3;
        RBus_UInt32  res1:5;
        RBus_UInt32  section:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  lane_count:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  pixel_mode:3;
        RBus_UInt32  res4:5;
    };
}lane_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ctl:24;
        RBus_UInt32  res1:8;
    };
}ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_boundary:5;
        RBus_UInt32  res1:25;
        RBus_UInt32  under_boundary:1;
        RBus_UInt32  over_boundary:1;
    };
}pll_tracking_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_delay:22;
        RBus_UInt32  dummy1802d610_23_22:2;
        RBus_UInt32  debounce_cnt:4;
        RBus_UInt32  video_trans_mode:1;
        RBus_UInt32  transfer_en:1;
        RBus_UInt32  pll_stable:1;
        RBus_UInt32  reg_en:1;
    };
}transmit_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  initial_en:1;
        RBus_UInt32  aln_en:1;
        RBus_UInt32  video_en:1;
        RBus_UInt32  cdr_out_en:1;
        RBus_UInt32  initial_finish:1;
        RBus_UInt32  aln_finish:1;
        RBus_UInt32  num_check_fail:1;
        RBus_UInt32  reset_sel:1;
        RBus_UInt32  dummy1802d614_31:24;
    };
}transmit_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  three_en:1;
        RBus_UInt32  three_mode:2;
        RBus_UInt32  res1:29;
    };
}three_flag_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  int_cts_empty:1;
        RBus_UInt32  int_cts_full:1;
        RBus_UInt32  int_async_under_boundary:1;
        RBus_UInt32  int_async_over_boundary:1;
        RBus_UInt32  int_cts_empty_en:1;
        RBus_UInt32  int_cts_full_en:1;
        RBus_UInt32  int_async_under_boundary_en:1;
        RBus_UInt32  int_async_over_boundary_en:1;
        RBus_UInt32  dummy1802d61c_31:24;
    };
}interrupt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_crc_conti:1;
        RBus_UInt32  reg_crc_start:1;
        RBus_UInt32  res1:30;
    };
}crc_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_result:32;
    };
}crc_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  empty_mask_error:1;
        RBus_UInt32  full_mask_error:1;
        RBus_UInt32  en_bypass:1;
        RBus_UInt32  force_rstn:1;
        RBus_UInt32  force_rstn_delay_en:1;
        RBus_UInt32  dummy1802d628_6:2;
        RBus_UInt32  empty_boundary:4;
        RBus_UInt32  full_boundary:4;
        RBus_UInt32  rd_addr_initial:4;
        RBus_UInt32  res1:13;
    };
}cts_fifo_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vby1_bist_mode:1;
        RBus_UInt32  vby1_drf_mode:1;
        RBus_UInt32  vby1_drf_resume:1;
        RBus_UInt32  vby1_bist_done:1;
        RBus_UInt32  vby1_drf_done:1;
        RBus_UInt32  vby1_drf_pause:1;
        RBus_UInt32  res1:26;
    };
}vby1_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  res1:28;
    };
}vby1_bist0_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  drf_bist_fail_0:1;
        RBus_UInt32  drf_bist_fail_1:1;
        RBus_UInt32  drf_bist_fail_2:1;
        RBus_UInt32  drf_bist_fail_3:1;
        RBus_UInt32  res1:28;
    };
}vby1_bist0_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  res1:12;
    };
}vby1_bist0_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ls_0:1;
        RBus_UInt32  ls_1:1;
        RBus_UInt32  ls_2:1;
        RBus_UInt32  ls_3:1;
        RBus_UInt32  dummy1802d63c_31:28;
    };
}vby1_bist0_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802d640_31_0:32;
    };
}vby1_bist4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  debug_mode:5;
        RBus_UInt32  res1:27;
    };
}vby1_debug_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_lockn:1;
        RBus_UInt32  fw_htpdn:1;
        RBus_UInt32  res1:28;
        RBus_UInt32  fw_lockn_ctrl:1;
        RBus_UInt32  fw_htpdn_ctrl:1;
    };
}vby1_fw_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lane_swap:1;
        RBus_UInt32  lsb_msb_swap:1;
        RBus_UInt32  res1:30;
    };
}vby1_out_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  shift_bit:2;
        RBus_UInt32  res1:6;
        RBus_UInt32  output_bit:4;
        RBus_UInt32  res2:19;
        RBus_UInt32  bit_shift_enable:1;
    };
}vby1_bit_shift_ctrl_RBUS;




#endif







#endif //_RBUS_VBY1_REG_H_

