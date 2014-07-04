/**
* @file rbusMhlReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/5/24
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_MHL_REG_H_
#define _RBUS_MHL_REG_H_

#include <rtd_types_qc.h>

#define CBUS_BASE_ADDR                     0xB8062C00

// MHL Register Address

#define CBUS_VADDR                         (CBUS_BASE_ADDR + 0x00)
#define CBUS_DIS0_VADDR                    (CBUS_BASE_ADDR + 0x04)
#define CBUS_DIS1_VADDR                    (CBUS_BASE_ADDR + 0x08)
#define CBUS_DIS2_VADDR                    (CBUS_BASE_ADDR + 0x0c)
#define CBUS_DIS3_VADDR                    (CBUS_BASE_ADDR + 0x10)
#define CBUS_DIS4_VADDR                    (CBUS_BASE_ADDR + 0x14)
#define CBUS_DIS5_VADDR                    (CBUS_BASE_ADDR + 0x18)
#define CBUS_PHY0_VADDR                    (CBUS_BASE_ADDR + 0x1c)
#define CBUS_PHY1_VADDR                    (CBUS_BASE_ADDR + 0x20)
#define MSC_REG_00_VADDR                   (CBUS_BASE_ADDR + 0x24)
#define MSC_REG_01_VADDR                   (CBUS_BASE_ADDR + 0x28)
#define MSC_REG_02_VADDR                   (CBUS_BASE_ADDR + 0x2c)
#define MSC_REG_03_VADDR                   (CBUS_BASE_ADDR + 0x30)
#define MSC_REG_04_VADDR                   (CBUS_BASE_ADDR + 0x34)
#define MSC_REG_05_VADDR                   (CBUS_BASE_ADDR + 0x38)
#define MSC_REG_06_VADDR                   (CBUS_BASE_ADDR + 0x3c)
#define MSC_REG_07_VADDR                   (CBUS_BASE_ADDR + 0x40)
#define MSC_REG_08_VADDR                   (CBUS_BASE_ADDR + 0x44)
#define MSC_REG_09_VADDR                   (CBUS_BASE_ADDR + 0x48)
#define MSC_REG_0A_VADDR                   (CBUS_BASE_ADDR + 0x4c)
#define MSC_REG_0B_VADDR                   (CBUS_BASE_ADDR + 0x50)
#define MSC_REG_0C_VADDR                   (CBUS_BASE_ADDR + 0x54)
#define MSC_REG_0D_VADDR                   (CBUS_BASE_ADDR + 0x58)
#define MSC_REG_0E_VADDR                   (CBUS_BASE_ADDR + 0x5c)
#define MSC_REG_0F_VADDR                   (CBUS_BASE_ADDR + 0x60)
#define MSC_REG_20_VADDR                   (CBUS_BASE_ADDR + 0x64)
#define MSC_REG_21_VADDR                   (CBUS_BASE_ADDR + 0x68)
#define MSC_REG_22_VADDR                   (CBUS_BASE_ADDR + 0x6c)
#define MSC_REG_23_VADDR                   (CBUS_BASE_ADDR + 0x70)
#define MSC_REG_24_VADDR                   (CBUS_BASE_ADDR + 0x74)
#define MSC_REG_25_VADDR                   (CBUS_BASE_ADDR + 0x78)
#define MSC_REG_26_VADDR                   (CBUS_BASE_ADDR + 0x7c)
#define MSC_REG_27_VADDR                   (CBUS_BASE_ADDR + 0x80)
#define MSC_REG_30_VADDR                   (CBUS_BASE_ADDR + 0x84)
#define MSC_REG_31_VADDR                   (CBUS_BASE_ADDR + 0x88)
#define MSC_REG_32_VADDR                   (CBUS_BASE_ADDR + 0x8c)
#define MSC_REG_33_VADDR                   (CBUS_BASE_ADDR + 0x90)
#define MSC_REG_34_VADDR                   (CBUS_BASE_ADDR + 0x94)
#define MSC_REG_35_VADDR                   (CBUS_BASE_ADDR + 0x98)
#define MSC_REG_36_VADDR                   (CBUS_BASE_ADDR + 0x9c)
#define MSC_REG_37_VADDR                   (CBUS_BASE_ADDR + 0xa0)
#define MSC_REG_40_VADDR                   (CBUS_BASE_ADDR + 0xa4)
#define MSC_REG_41_VADDR                   (CBUS_BASE_ADDR + 0xa8)
#define MSC_REG_42_VADDR                   (CBUS_BASE_ADDR + 0xac)
#define MSC_REG_43_VADDR                   (CBUS_BASE_ADDR + 0xb0)
#define MSC_REG_44_VADDR                   (CBUS_BASE_ADDR + 0xb4)
#define MSC_REG_45_VADDR                   (CBUS_BASE_ADDR + 0xb8)
#define MSC_REG_46_VADDR                   (CBUS_BASE_ADDR + 0xbc)
#define MSC_REG_47_VADDR                   (CBUS_BASE_ADDR + 0xc0)
#define MSC_REG_48_VADDR                   (CBUS_BASE_ADDR + 0xc4)
#define MSC_REG_49_VADDR                   (CBUS_BASE_ADDR + 0xc8)
#define MSC_REG_4A_VADDR                   (CBUS_BASE_ADDR + 0xcc)
#define MSC_REG_4B_VADDR                   (CBUS_BASE_ADDR + 0xd0)
#define MSC_REG_4C_VADDR                   (CBUS_BASE_ADDR + 0xd4)
#define MSC_REG_4D_VADDR                   (CBUS_BASE_ADDR + 0xd8)
#define MSC_REG_4E_VADDR                   (CBUS_BASE_ADDR + 0xdc)
#define MSC_REG_4F_VADDR                   (CBUS_BASE_ADDR + 0xe0)
#define MSC_REG_50_VADDR                   (CBUS_BASE_ADDR + 0xe4)
#define MSC_REG_51_VADDR                   (CBUS_BASE_ADDR + 0xe8)
#define MSC_REG_52_VADDR                   (CBUS_BASE_ADDR + 0xec)
#define MSC_REG_53_VADDR                   (CBUS_BASE_ADDR + 0xf0)
#define MSC_REG_54_VADDR                   (CBUS_BASE_ADDR + 0xf4)
#define MSC_REG_55_VADDR                   (CBUS_BASE_ADDR + 0xf8)
#define MSC_REG_56_VADDR                   (CBUS_BASE_ADDR + 0xfc)
#define MSC_REG_57_VADDR                   (CBUS_BASE_ADDR + 0x100)
#define MSC_REG_58_VADDR                   (CBUS_BASE_ADDR + 0x104)
#define MSC_REG_59_VADDR                   (CBUS_BASE_ADDR + 0x108)
#define MSC_REG_5A_VADDR                   (CBUS_BASE_ADDR + 0x10c)
#define MSC_REG_5B_VADDR                   (CBUS_BASE_ADDR + 0x110)
#define MSC_REG_5C_VADDR                   (CBUS_BASE_ADDR + 0x114)
#define MSC_REG_5D_VADDR                   (CBUS_BASE_ADDR + 0x118)
#define MSC_REG_5E_VADDR                   (CBUS_BASE_ADDR + 0x11c)
#define MSC_REG_5F_VADDR                   (CBUS_BASE_ADDR + 0x120)
#define CBUS_LINK_00_VADDR                 (CBUS_BASE_ADDR + 0x124)
#define CBUS_LINK_01_VADDR                 (CBUS_BASE_ADDR + 0x128)
#define CBUS_LINK_02_VADDR                 (CBUS_BASE_ADDR + 0x12c)
#define CBUS_LINK_03_VADDR                 (CBUS_BASE_ADDR + 0x130)
#define CBUS_LINK_04_VADDR                 (CBUS_BASE_ADDR + 0x134)
#define CBUS_LINK_05_VADDR                 (CBUS_BASE_ADDR + 0x138)
#define CBUS_LINK_06_VADDR                 (CBUS_BASE_ADDR + 0x13c)
#define CBUS_LINK_07_VADDR                 (CBUS_BASE_ADDR + 0x140)
#define CBUS_LINK_08_VADDR                 (CBUS_BASE_ADDR + 0x144)
#define CBUS_LINK_09_VADDR                 (CBUS_BASE_ADDR + 0x148)
#define CBUS_LINK_0A_VADDR                 (CBUS_BASE_ADDR + 0x14c)
#define CBUS_LINK_0B_VADDR                 (CBUS_BASE_ADDR + 0x150)
#define CBUS_LINK_0C_VADDR                 (CBUS_BASE_ADDR + 0x154)
#define CBUS_LINK_0D_VADDR                 (CBUS_BASE_ADDR + 0x158)
#define CBUS_LINK_0E_VADDR                 (CBUS_BASE_ADDR + 0x15c)
#define CBUS_LINK_0F_VADDR                 (CBUS_BASE_ADDR + 0x160)
#define CBUS_LINK_10_VADDR                 (CBUS_BASE_ADDR + 0x164)
#define CBUS_LINK_11_VADDR                 (CBUS_BASE_ADDR + 0x168)
#define CBUS_LINK_12_VADDR                 (CBUS_BASE_ADDR + 0x16c)
#define CBUS_LINK_13_VADDR                 (CBUS_BASE_ADDR + 0x170)
#define CBUS_LINK_14_VADDR                 (CBUS_BASE_ADDR + 0x174)
#define CBUS_LINK_15_VADDR                 (CBUS_BASE_ADDR + 0x178)
#define CBUS_FLAG_0_VADDR                  (CBUS_BASE_ADDR + 0x17c)
#define CBUS_MSC_00_VADDR                  (CBUS_BASE_ADDR + 0x180)
#define CBUS_MSC_01_VADDR                  (CBUS_BASE_ADDR + 0x184)
#define CBUS_MSC_02_VADDR                  (CBUS_BASE_ADDR + 0x188)
#define CBUS_MSC_03_VADDR                  (CBUS_BASE_ADDR + 0x18c)
#define CBUS_MSC_04_VADDR                  (CBUS_BASE_ADDR + 0x190)
#define CBUS_MSC_05_VADDR                  (CBUS_BASE_ADDR + 0x194)
#define CBUS_MSC_06_VADDR                  (CBUS_BASE_ADDR + 0x198)
#define CBUS_MSC_07_VADDR                  (CBUS_BASE_ADDR + 0x19c)
#define CBUS_MSC_08_VADDR                  (CBUS_BASE_ADDR + 0x1a0)
#define CBUS_MSC_09_VADDR                  (CBUS_BASE_ADDR + 0x1a4)
#define CBUS_MSC_0A_VADDR                  (CBUS_BASE_ADDR + 0x1a8)
#define CBUS_MSC_0B_VADDR                  (CBUS_BASE_ADDR + 0x1ac)
#define CBUS_MSC_0C_VADDR                  (CBUS_BASE_ADDR + 0x1b0)
#define CBUS_MSC_0D_VADDR                  (CBUS_BASE_ADDR + 0x1b4)
#define CBUS_MSC_0E_VADDR                  (CBUS_BASE_ADDR + 0x1b8)
#define CBUS_MSC_0F_VADDR                  (CBUS_BASE_ADDR + 0x1bc)
#define CBUS_MSC_10_VADDR                  (CBUS_BASE_ADDR + 0x1c0)
#define CBUS_MSC_11_VADDR                  (CBUS_BASE_ADDR + 0x1c4)
#define CBUS_MSC_12_VADDR                  (CBUS_BASE_ADDR + 0x1c8)
#define CBUS_MSC_13_VADDR                  (CBUS_BASE_ADDR + 0x1cc)
#define CBUS_MSC_14_VADDR                  (CBUS_BASE_ADDR + 0x1d0)
#define CBUS_MSC_15_VADDR                  (CBUS_BASE_ADDR + 0x1d4)
#define CBUS_MSC_16_VADDR                  (CBUS_BASE_ADDR + 0x1d8)
#define CBUS_MSC_17_VADDR                  (CBUS_BASE_ADDR + 0x1dc)
#define CBUS_MSC_18_VADDR                  (CBUS_BASE_ADDR + 0x1e0)
#define CBUS_MSC_19_VADDR                  (CBUS_BASE_ADDR + 0x1e4)
#define CBUS_MSC_1A_VADDR                  (CBUS_BASE_ADDR + 0x1e8)
#define CBUS_MSC_1B_VADDR                  (CBUS_BASE_ADDR + 0x1ec)
#define CBUS_MSC_1C_VADDR                  (CBUS_BASE_ADDR + 0x1f0)
#define CBUS_MSC_1D_VADDR                  (CBUS_BASE_ADDR + 0x1f4)
#define CBUS_MSC_1E_VADDR                  (CBUS_BASE_ADDR + 0x1f8)
#define CBUS_MSC_1F_VADDR                  (CBUS_BASE_ADDR + 0x1fc)
#define CBUS_MSC_20_VADDR                  (CBUS_BASE_ADDR + 0x200)
#define CBUS_MSC_21_VADDR                  (CBUS_BASE_ADDR + 0x204)
#define CBUS_MSC_22_VADDR                  (CBUS_BASE_ADDR + 0x208)
#define CBUS_MSC_23_VADDR                  (CBUS_BASE_ADDR + 0x20c)
#define CBUS_MSC_24_VADDR                  (CBUS_BASE_ADDR + 0x210)
#define FW0_REQ_00_VADDR                   (CBUS_BASE_ADDR + 0x214)
#define FW0_REQ_01_VADDR                   (CBUS_BASE_ADDR + 0x218)
#define FW0_REQ_02_VADDR                   (CBUS_BASE_ADDR + 0x21c)
#define FW0_REQ_03_VADDR                   (CBUS_BASE_ADDR + 0x220)
#define FW0_REQ_04_VADDR                   (CBUS_BASE_ADDR + 0x224)
#define FW0_REQ_05_VADDR                   (CBUS_BASE_ADDR + 0x228)
#define FW0_REQ_06_VADDR                   (CBUS_BASE_ADDR + 0x22c)
#define FW0_REQ_07_VADDR                   (CBUS_BASE_ADDR + 0x230)
#define FW0_REQ_08_VADDR                   (CBUS_BASE_ADDR + 0x234)
#define FW0_REQ_09_VADDR                   (CBUS_BASE_ADDR + 0x238)
#define CBUS_DDC_00_VADDR                  (CBUS_BASE_ADDR + 0x23c)
#define CBUS_DDC_01_VADDR                  (CBUS_BASE_ADDR + 0x240)
#define CBUS_DDC_02_VADDR                  (CBUS_BASE_ADDR + 0x244)
#define CBUS_DDC_03_VADDR                  (CBUS_BASE_ADDR + 0x248)
#define CBUS_DDC_04_VADDR                  (CBUS_BASE_ADDR + 0x24c)
#define CBUS_DDC_05_VADDR                  (CBUS_BASE_ADDR + 0x250)
#define CBUS_DDC_06_VADDR                  (CBUS_BASE_ADDR + 0x254)
#define CBUS_WDOG_VADDR                    (CBUS_BASE_ADDR + 0x258)
#define CBUS_INT_EN_VADDR                  (CBUS_BASE_ADDR + 0x25c)
#define CBUS_INT_INDEX_VADDR               (CBUS_BASE_ADDR + 0x260)
#define CBUS_TEST_VADDR                    (CBUS_BASE_ADDR + 0x264)
#define CBUS_DUMMY0_VADDR                  (CBUS_BASE_ADDR + 0x268)


//#define LITTLE_ENDIAN

#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======MHL register structure define==========
typedef union
{
    UINT32 regValue;
    struct{
        UINT32  enable:1;
        UINT32  irq_en_8051:1;
        UINT32  irq_en_scpu:1;
        UINT32  cbus_multi_sync:1;
        UINT32  rvd:16;
        UINT32  mhl_clk_ns:12;
    };
}cbus_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:3;
        UINT32  bypass_discov:1;
        UINT32  tsrc_float:8;
        UINT32  rxsense_fw_mode:1;
        UINT32  rxsense_fw_value:1;
        UINT32  tsrc_stable:10;
        UINT32  trxsense_deglitch:8;
    };
}cbus_dis0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  both_path_en:1;
        UINT32  trxsense_chk:9;
        UINT32  tsrc_wake_width1:5;
        UINT32  tsrc_wake_width2:7;
        UINT32  tsrc_wake_to_discov:10;
    };
}cbus_dis1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:5;
        UINT32  tsrc_pulse_width:7;
        UINT32  tsrc_conn:8;
        UINT32  rvd2:2;
        UINT32  tsrc_arbitrate:10;
    };
}cbus_dis2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tsink_float:8;
        UINT32  rvd1:2;
        UINT32  discovery_check_sink_start:5;
        UINT32  drive_wake_pulse_low_en:1;
        UINT32  rvd2:3;
        UINT32  max_discovery_pulse_count:5;
        UINT32  rvd3:3;
        UINT32  irq_en_src6_7:1;
        UINT32  irq_en_src3_4:1;
        UINT32  irq_en_tmds_off:1;
        UINT32  irq_en_tmds_out:1;
        UINT32  discov_standby:1;
    };
}cbus_dis3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:1;
        UINT32  src0:1;
        UINT32  src1:1;
        UINT32  src2:1;
        UINT32  src3_00:1;
        UINT32  src3_01:1;
        UINT32  src3_02:1;
        UINT32  src3_03:1;
        UINT32  src3_04:1;
        UINT32  src3_05:1;
        UINT32  src3_06:1;
        UINT32  src3_07:1;
        UINT32  src3_08:1;
        UINT32  src3_09:1;
        UINT32  src3_10:1;
        UINT32  src3_11:1;
        UINT32  src4:1;
        UINT32  src5:1;
        UINT32  src6:1;
        UINT32  src7:1;
        UINT32  rvd2:7;
        UINT32  irq_src6_7:1;
        UINT32  irq_src3_4:1;
        UINT32  irq_tmds_off:1;
        UINT32  irq_tmds_out:1;
        UINT32  rvd3:1;
    };
}cbus_dis4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dmy:32;
    };
}cbus_dis5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dmy:12;
        UINT32  reg_mhl_r10k_test:1;
        UINT32  reg_r1k_replace:1;
        UINT32  reg_mhl_bmos_en:1;
        UINT32  reg_mhl_hpd_det:1;
        UINT32  reg_mhl_r1k_det:1;
        UINT32  reg_r1k_vth_sel:1;
        UINT32  reg_mhl_tst_en:1;
        UINT32  reg_mhl_vsel:3;
        UINT32  reg_mhl_r10k:3;
        UINT32  reg_en_bias:1;
        UINT32  hdmi_hpd_en:1;
        UINT32  reg_cbus_strc:3;
        UINT32  tst_sel_h:2;
    };
}cbus_phy0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  hdmi_hpd_out:1;
        UINT32  reg_mhl_r10k_en:2;
        UINT32  rego_mhl_hpd_det:1;
        UINT32  rego_mhl_r1k_det:1;
    };
}cbus_phy1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  dev_state:8;
    };
}msc_reg_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  mhl_ver:8;
    };
}msc_reg_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  dev_cat:1;
        UINT32  plim:2;
        UINT32  pow:1;
        UINT32  dev_type:4;
    };
}msc_reg_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  adop_id_h:8;
    };
}msc_reg_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  adop_id_l:8;
    };
}msc_reg_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  vid_link_mode:2;
        UINT32  supp_vga:1;
        UINT32  supp_islands:1;
        UINT32  supp_ppixel:1;
        UINT32  supp_yuv422:1;
        UINT32  supp_yuv444:1;
        UINT32  supp_rgb444:1;
    };
}msc_reg_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  aud_link_mode:6;
        UINT32  aud_8ch:1;
        UINT32  aud_2ch:1;
    };
}msc_reg_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  supp_vt:1;
        UINT32  video_type:3;
        UINT32  vt_game:1;
        UINT32  vt_cinema:1;
        UINT32  vt_photo:1;
        UINT32  vt_graphics:1;
    };
}msc_reg_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  ld_gui:1;
        UINT32  ld_speaker:1;
        UINT32  ld_record:1;
        UINT32  ld_tuner:1;
        UINT32  ld_media:1;
        UINT32  ld_audio:1;
        UINT32  ld_video:1;
        UINT32  ld_display:1;
    };
}msc_reg_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  bandwid:8;
    };
}msc_reg_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  feature_flag:3;
        UINT32  ucp_recv_supp:1;
        UINT32  ucp_send_supp:1;
        UINT32  sp_supp:1;
        UINT32  rap_supp:1;
        UINT32  rcp_supp:1;
    };
}msc_reg_0a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  device_id_h:8;
    };
}msc_reg_0b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  device_id_l:8;
    };
}msc_reg_0c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scr_size:8;
    };
}msc_reg_0d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  stat_size:4;
        UINT32  int_size:4;
    };
}msc_reg_0e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  cap_0f:8;
    };
}msc_reg_0f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  rchg_int:3;
        UINT32  _3d_req:1;
        UINT32  grt_wrt:1;
        UINT32  req_wrt:1;
        UINT32  dscr_chg:1;
        UINT32  dcap_chg:1;
    };
}msc_reg_20_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  dchg_int_7:1;
        UINT32  dchg_int_6:1;
        UINT32  dchg_int_5:1;
        UINT32  dchg_int_4:1;
        UINT32  dchg_int_3:1;
        UINT32  dchg_int_2:1;
        UINT32  edid_chg:1;
        UINT32  dchg_int_0:1;
    };
}msc_reg_21_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  chg22_7:1;
        UINT32  chg22_6:1;
        UINT32  chg22_5:1;
        UINT32  chg22_4:1;
        UINT32  chg22_3:1;
        UINT32  chg22_2:1;
        UINT32  chg22_1:1;
        UINT32  chg22_0:1;
    };
}msc_reg_22_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  chg23_7:1;
        UINT32  chg23_6:1;
        UINT32  chg23_5:1;
        UINT32  chg23_4:1;
        UINT32  chg23_3:1;
        UINT32  chg23_2:1;
        UINT32  chg23_1:1;
        UINT32  chg23_0:1;
    };
}msc_reg_23_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  chg24_7:1;
        UINT32  chg24_6:1;
        UINT32  chg24_5:1;
        UINT32  chg24_4:1;
        UINT32  chg24_3:1;
        UINT32  chg24_2:1;
        UINT32  chg24_1:1;
        UINT32  chg24_0:1;
    };
}msc_reg_24_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  chg25_7:1;
        UINT32  chg25_6:1;
        UINT32  chg25_5:1;
        UINT32  chg25_4:1;
        UINT32  chg25_3:1;
        UINT32  chg25_2:1;
        UINT32  chg25_1:1;
        UINT32  chg25_0:1;
    };
}msc_reg_25_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  chg26_7:1;
        UINT32  chg26_6:1;
        UINT32  chg26_5:1;
        UINT32  chg26_4:1;
        UINT32  chg26_3:1;
        UINT32  chg26_2:1;
        UINT32  chg26_1:1;
        UINT32  chg26_0:1;
    };
}msc_reg_26_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  chg27_7:1;
        UINT32  chg27_6:1;
        UINT32  chg27_5:1;
        UINT32  chg27_4:1;
        UINT32  chg27_3:1;
        UINT32  chg27_2:1;
        UINT32  chg27_1:1;
        UINT32  chg27_0:1;
    };
}msc_reg_27_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  connected_rdy:7;
        UINT32  dcap_rdy:1;
    };
}msc_reg_30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:24;
        UINT32  link_mode:3;
        UINT32  rvd2:1;
        UINT32  path_en:1;
        UINT32  rvd3:3;
    };
}msc_reg_31_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  stat_32:8;
    };
}msc_reg_32_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  stat_33:8;
    };
}msc_reg_33_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  stat_34:8;
    };
}msc_reg_34_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  stat_35:8;
    };
}msc_reg_35_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  stat_36:8;
    };
}msc_reg_36_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  stat_37:8;
    };
}msc_reg_37_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_40:8;
    };
}msc_reg_40_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_41:8;
    };
}msc_reg_41_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_42:8;
    };
}msc_reg_42_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_43:8;
    };
}msc_reg_43_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_44:8;
    };
}msc_reg_44_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_45:8;
    };
}msc_reg_45_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_46:8;
    };
}msc_reg_46_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_47:8;
    };
}msc_reg_47_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_48:8;
    };
}msc_reg_48_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_49:8;
    };
}msc_reg_49_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_4a:8;
    };
}msc_reg_4a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_4b:8;
    };
}msc_reg_4b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_4c:8;
    };
}msc_reg_4c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_4d:8;
    };
}msc_reg_4d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_4e:8;
    };
}msc_reg_4e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_4f:8;
    };
}msc_reg_4f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_50:8;
    };
}msc_reg_50_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_51:8;
    };
}msc_reg_51_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_52:8;
    };
}msc_reg_52_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_53:8;
    };
}msc_reg_53_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_54:8;
    };
}msc_reg_54_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_55:8;
    };
}msc_reg_55_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_56:8;
    };
}msc_reg_56_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_57:8;
    };
}msc_reg_57_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_58:8;
    };
}msc_reg_58_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_59:8;
    };
}msc_reg_59_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_5a:8;
    };
}msc_reg_5a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_5b:8;
    };
}msc_reg_5b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_5c:8;
    };
}msc_reg_5c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_5d:8;
    };
}msc_reg_5d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_5e:8;
    };
}msc_reg_5e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scratch_5f:8;
    };
}msc_reg_5f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:14;
        UINT32  sync0_hb:9;
        UINT32  sync0_lb:9;
    };
}cbus_link_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  sync1_hb:8;
        UINT32  sync1_lb:8;
    };
}cbus_link_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  sync_bit_time:8;
    };
}cbus_link_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:23;
        UINT32  abs_thres_en:1;
        UINT32  abs_threshold:8;
    };
}cbus_link_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_link_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  irq_en_parity_fail:1;
        UINT32  ctrl_16_resv:1;
        UINT32  parity_fail_limit:5;
    };
}cbus_link_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  ack_fall:7;
    };
}cbus_link_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  ack_0:7;
    };
}cbus_link_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:24;
        UINT32  irq_parity_fail:1;
        UINT32  rvd2:7;
    };
}cbus_link_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  tx_bit_time:8;
    };
}cbus_link_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_link_0a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  tx_ack_fal:7;
    };
}cbus_link_0b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  tx_ack_low_hb:7;
    };
}cbus_link_0c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  tx_ack_low_lb:7;
    };
}cbus_link_0d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:19;
        UINT32  retry_lv:7;
        UINT32  irq_en_retry_ddc:1;
        UINT32  irq_en_retry_msc:1;
        UINT32  dmy:4;
    };
}cbus_link_0e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:21;
        UINT32  drv_str:5;
        UINT32  drv_hi_cbus:6;
    };
}cbus_link_0f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  wait:4;
    };
}cbus_link_10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  req_opp:8;
    };
}cbus_link_11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  req_cont:8;
    };
}cbus_link_12_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  req_hold:4;
        UINT32  resp_hold:4;
    };
}cbus_link_13_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rx_fifo_clr:1;
        UINT32  rvd1:10;
        UINT32  packet_max:5;
        UINT32  rvd2:2;
        UINT32  glob_time:8;
        UINT32  rvd3:5;
        UINT32  irq_en_link_err:1;
    };
}cbus_link_14_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:25;
        UINT32  burst_timeout:1;
        UINT32  rvd2:2;
        UINT32  irq_retry_ddc:1;
        UINT32  irq_retry_msc:1;
        UINT32  chk_err:1;
        UINT32  irq_link_err:1;
    };
}cbus_link_15_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:16;
        UINT32  fwdef_cmd_rev:8;
        UINT32  rvd2:7;
        UINT32  avoid_conf:1;
    };
}cbus_flag_0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msc_idle_resp_abort:1;
        UINT32  rvd:25;
        UINT32  mcumsc_en:1;
        UINT32  dmy:5;
    };
}cbus_msc_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  na_msc_cmd:8;
    };
}cbus_msc_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:11;
        UINT32  na_rx_len:5;
        UINT32  rvd2:6;
        UINT32  rx_fifo_full:1;
        UINT32  rx_fifo_empty:1;
        UINT32  na_msc_offset:8;
    };
}cbus_msc_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  rx_fifo_data:8;
    };
}cbus_msc_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:3;
        UINT32  irq_ucp:1;
        UINT32  irq_ucpk:1;
        UINT32  irq_ucpe:1;
        UINT32  irq_dcap_rdy_chg:1;
        UINT32  rvd2:1;
        UINT32  irq_path_en_chg:1;
        UINT32  rvd3:1;
        UINT32  irq_msge:1;
        UINT32  irq_rcp:1;
        UINT32  irq_rcpk:1;
        UINT32  irq_rcpe:1;
        UINT32  irq_rap:1;
        UINT32  irq_rapk:1;
        UINT32  irq_msg_sub:1;
        UINT32  irq_wr_stat:1;
        UINT32  irq_rd_devcap:1;
        UINT32  irq_get_stat:1;
        UINT32  irq_get_id:1;
        UINT32  irq_get_msg:1;
        UINT32  irq_sc1_err:1;
        UINT32  irq_ddc_err:1;
        UINT32  irq_msc_err:1;
        UINT32  irq_wr_burst:1;
        UINT32  irq_sc3_err:1;
        UINT32  irq_fwdef_cmd:1;
        UINT32  irq_allmsc_cmd:1;
        UINT32  irq_abort_res:1;
        UINT32  irq_abort_req:1;
        UINT32  irq_ddc_abort:1;
    };
}cbus_msc_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:3;
        UINT32  irq_en_ucp:1;
        UINT32  irq_en_ucpk:1;
        UINT32  irq_en_ucpe:1;
        UINT32  irq_en_dcap_rdy_chg:1;
        UINT32  rvd2:1;
        UINT32  irq_en_path_en_chg:1;
        UINT32  rvd3:1;
        UINT32  irq_en_msge:1;
        UINT32  irq_en_rcp:1;
        UINT32  irq_en_rcpk:1;
        UINT32  irq_en_rcpe:1;
        UINT32  irq_en_rap:1;
        UINT32  irq_en_rapk:1;
        UINT32  irq_en_msg_sub:1;
        UINT32  irq_en_wr_stat:1;
        UINT32  irq_en_rd_devcap:1;
        UINT32  irq_en_get_stat:1;
        UINT32  irq_en_get_id:1;
        UINT32  irq_en_get_msg:1;
        UINT32  irq_en_sc1_err:1;
        UINT32  irq_en_ddc_err:1;
        UINT32  irq_en_msc_err:1;
        UINT32  irq_en_wr_burst:1;
        UINT32  irq_en_sc3_err:1;
        UINT32  irq_en_fwdef_cmd:1;
        UINT32  irq_en_allmsc_cmd:1;
        UINT32  irq_en_abort_res:1;
        UINT32  irq_en_abort_req:1;
        UINT32  irq_en_ddc_abort:1;
    };
}cbus_msc_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_rchg_bit7:1;
        UINT32  irq_rchg_bit6:1;
        UINT32  irq_rchg_bit5:1;
        UINT32  irq_3d_req:1;
        UINT32  irq_grt_wrt:1;
        UINT32  irq_req_wrt:1;
        UINT32  irq_dscr_chg:1;
        UINT32  irq_dcap_chg:1;
        UINT32  irq_dchg_bit7:1;
        UINT32  irq_dchg_bit6:1;
        UINT32  irq_dchg_bit5:1;
        UINT32  irq_dchg_bit4:1;
        UINT32  irq_dchg_bit3:1;
        UINT32  irq_dchg_bit2:1;
        UINT32  irq_edid_chg:1;
        UINT32  irq_dchg_bit0:1;
        UINT32  irq_chg22_bit7:1;
        UINT32  irq_chg22_bit6:1;
        UINT32  irq_chg22_bit5:1;
        UINT32  irq_chg22_bit4:1;
        UINT32  irq_chg22_bit3:1;
        UINT32  irq_chg22_bit2:1;
        UINT32  irq_chg22_bit1:1;
        UINT32  irq_chg22_bit0:1;
        UINT32  irq_chg23_bit7:1;
        UINT32  irq_chg23_bit6:1;
        UINT32  irq_chg23_bit5:1;
        UINT32  irq_chg23_bit4:1;
        UINT32  irq_chg23_bit3:1;
        UINT32  irq_chg23_bit2:1;
        UINT32  irq_chg23_bit1:1;
        UINT32  irq_chg23_bit0:1;
    };
}cbus_msc_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_en_rchg_bit7:1;
        UINT32  irq_en_rchg_bit6:1;
        UINT32  irq_en_rchg_bit5:1;
        UINT32  irq_en_3d_req:1;
        UINT32  irq_en_grt_wrt:1;
        UINT32  irq_en_req_wrt:1;
        UINT32  irq_en_dscr_chg:1;
        UINT32  irq_en_dcap_chg:1;
        UINT32  irq_en_dchg_bit7:1;
        UINT32  irq_en_dchg_bit6:1;
        UINT32  irq_en_dchg_bit5:1;
        UINT32  irq_en_dchg_bit4:1;
        UINT32  irq_en_dchg_bit3:1;
        UINT32  irq_en_dchg_bit2:1;
        UINT32  irq_en_edid_chg:1;
        UINT32  irq_en_dchg_bit0:1;
        UINT32  irq_en_chg22_bit7:1;
        UINT32  irq_en_chg22_bit6:1;
        UINT32  irq_en_chg22_bit5:1;
        UINT32  irq_en_chg22_bit4:1;
        UINT32  irq_en_chg22_bit3:1;
        UINT32  irq_en_chg22_bit2:1;
        UINT32  irq_en_chg22_bit1:1;
        UINT32  irq_en_chg22_bit0:1;
        UINT32  irq_en_chg23_bit7:1;
        UINT32  irq_en_chg23_bit6:1;
        UINT32  irq_en_chg23_bit5:1;
        UINT32  irq_en_chg23_bit4:1;
        UINT32  irq_en_chg23_bit3:1;
        UINT32  irq_en_chg23_bit2:1;
        UINT32  irq_en_chg23_bit1:1;
        UINT32  irq_en_chg23_bit0:1;
    };
}cbus_msc_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_chg24_bit7:1;
        UINT32  irq_chg24_bit6:1;
        UINT32  irq_chg24_bit5:1;
        UINT32  irq_chg24_bit4:1;
        UINT32  irq_chg24_bit3:1;
        UINT32  irq_chg24_bit2:1;
        UINT32  irq_chg24_bit1:1;
        UINT32  irq_chg24_bit0:1;
        UINT32  irq_chg25_bit7:1;
        UINT32  irq_chg25_bit6:1;
        UINT32  irq_chg25_bit5:1;
        UINT32  irq_chg25_bit4:1;
        UINT32  irq_chg25_bit3:1;
        UINT32  irq_chg25_bit2:1;
        UINT32  irq_chg25_bit1:1;
        UINT32  irq_chg25_bit0:1;
        UINT32  irq_chg26_bit7:1;
        UINT32  irq_chg26_bit6:1;
        UINT32  irq_chg26_bit5:1;
        UINT32  irq_chg26_bit4:1;
        UINT32  irq_chg26_bit3:1;
        UINT32  irq_chg26_bit2:1;
        UINT32  irq_chg26_bit1:1;
        UINT32  irq_chg26_bit0:1;
        UINT32  irq_chg27_bit7:1;
        UINT32  irq_chg27_bit6:1;
        UINT32  irq_chg27_bit5:1;
        UINT32  irq_chg27_bit4:1;
        UINT32  irq_chg27_bit3:1;
        UINT32  irq_chg27_bit2:1;
        UINT32  irq_chg27_bit1:1;
        UINT32  irq_chg27_bit0:1;
    };
}cbus_msc_0a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_en_chg24_bit7:1;
        UINT32  irq_en_chg24_bit6:1;
        UINT32  irq_en_chg24_bit5:1;
        UINT32  irq_en_chg24_bit4:1;
        UINT32  irq_en_chg24_bit3:1;
        UINT32  irq_en_chg24_bit2:1;
        UINT32  irq_en_chg24_bit1:1;
        UINT32  irq_en_chg24_bit0:1;
        UINT32  irq_en_chg25_bit7:1;
        UINT32  irq_en_chg25_bit6:1;
        UINT32  irq_en_chg25_bit5:1;
        UINT32  irq_en_chg25_bit4:1;
        UINT32  irq_en_chg25_bit3:1;
        UINT32  irq_en_chg25_bit2:1;
        UINT32  irq_en_chg25_bit1:1;
        UINT32  irq_en_chg25_bit0:1;
        UINT32  irq_en_chg26_bit7:1;
        UINT32  irq_en_chg26_bit6:1;
        UINT32  irq_en_chg26_bit5:1;
        UINT32  irq_en_chg26_bit4:1;
        UINT32  irq_en_chg26_bit3:1;
        UINT32  irq_en_chg26_bit2:1;
        UINT32  irq_en_chg26_bit1:1;
        UINT32  irq_en_chg26_bit0:1;
        UINT32  irq_en_chg27_bit7:1;
        UINT32  irq_en_chg27_bit6:1;
        UINT32  irq_en_chg27_bit5:1;
        UINT32  irq_en_chg27_bit4:1;
        UINT32  irq_en_chg27_bit3:1;
        UINT32  irq_en_chg27_bit2:1;
        UINT32  irq_en_chg27_bit1:1;
        UINT32  irq_en_chg27_bit0:1;
    };
}cbus_msc_0b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  msc_err_code:8;
    };
}cbus_msc_0c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:22;
        UINT32  rcp_reply_abort:1;
        UINT32  rcp_reply_nack:1;
        UINT32  vendor_id:8;
    };
}cbus_msc_0d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  msg_cmd:8;
    };
}cbus_msc_0e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  msg_dat:8;
    };
}cbus_msc_0f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  msge_rcv:8;
    };
}cbus_msc_10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  rcp_rcv:8;
    };
}cbus_msc_11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  rcpk_rcv:8;
    };
}cbus_msc_12_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  rcpe_rcv:8;
    };
}cbus_msc_13_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  rap_rcv:8;
    };
}cbus_msc_14_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  rapk_rcv:8;
    };
}cbus_msc_15_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:26;
        UINT32  wb_id_chk:1;
        UINT32  rvd2:5;
    };
}cbus_msc_16_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  adop_idh_rcv:8;
        UINT32  adop_idl_rcv:8;
    };
}cbus_msc_17_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_18_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_19_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:20;
        UINT32  msc_fsm:6;
        UINT32  ddc_fsm:6;
    };
}cbus_msc_1a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  cap_offset:8;
    };
}cbus_msc_1b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  int_offset:8;
    };
}cbus_msc_1c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  sta_offset:8;
    };
}cbus_msc_1d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  scr_offset:8;
    };
}cbus_msc_1e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:30;
        UINT32  ddc_err_force:1;
        UINT32  msc_err_force:1;
    };
}cbus_msc_1f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  ddc_err_fw:8;
    };
}cbus_msc_20_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  msc_err_fw:8;
    };
}cbus_msc_21_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  ucp_rcv:8;
    };
}cbus_msc_22_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  ucpk_rcv:8;
    };
}cbus_msc_23_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  ucpe_rcv:8;
    };
}cbus_msc_24_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:22;
        UINT32  fw0_msg_processing:1;
        UINT32  fw0_req:1;
        UINT32  rvd2:1;
        UINT32  fw0_fifo_full:1;
        UINT32  fw0_fifo_empty:1;
        UINT32  rvd3:5;
    };
}fw0_req_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:19;
        UINT32  check_fw0_msg_processing:1;
        UINT32  rvd2:1;
        UINT32  fw0_tx_case:3;
        UINT32  fw0_cmd1:8;
    };
}fw0_req_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  fw0_cmd2:8;
    };
}fw0_req_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:8;
        UINT32  fw0_data1:8;
        UINT32  fw0_data2:8;
        UINT32  fw0_offset:8;
    };
}fw0_req_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  fw0_data:8;
    };
}fw0_req_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_fifo_clr:1;
        UINT32  rvd1:19;
        UINT32  fw0_fifo_len:4;
        UINT32  rvd2:2;
        UINT32  irq_en_fw0_rcv_err:1;
        UINT32  irq_en_fw0_fin:1;
        UINT32  irq_en_fw0_cmd:1;
        UINT32  irq_en_fw0_data:1;
        UINT32  rvd3:2;
    };
}fw0_req_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  fw0_cmd_rcv:8;
    };
}fw0_req_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  fw0_data_rcv:8;
    };
}fw0_req_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  fw0_rdata:8;
    };
}fw0_req_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:23;
        UINT32  irq_fw0_fin:1;
        UINT32  irq_fw0_cmd:1;
        UINT32  irq_fw0_data:1;
        UINT32  irq_fw0_rcv_err:1;
        UINT32  rvd2:5;
    };
}fw0_req_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_req:1;
        UINT32  rvd:22;
        UINT32  irq_ddc_data:1;
        UINT32  ddc_err_code:8;
    };
}cbus_ddc_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_idle_resp_abort:1;
        UINT32  rvd1:7;
        UINT32  ddc_addr_w:8;
        UINT32  ddc_addr_r:8;
        UINT32  rvd2:8;
    };
}cbus_ddc_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:21;
        UINT32  ddc_req_type:2;
        UINT32  mcuddc_need_resp:1;
        UINT32  mcuddc_en:1;
        UINT32  rvd2:4;
        UINT32  irq_en_ddc_data:1;
        UINT32  ddc_req_ctrl:1;
        UINT32  rvd3:1;
    };
}cbus_ddc_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  ddc_cmd_fw:8;
    };
}cbus_ddc_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:23;
        UINT32  ddc_rcv_data:9;
    };
}cbus_ddc_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:24;
        UINT32  ddc_data_fw:8;
    };
}cbus_ddc_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:8;
        UINT32  ddc_offset:8;
        UINT32  ddc_seg_val:8;
        UINT32  ddc_addr_0x60:8;
    };
}cbus_ddc_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  cbus_busy:1;
        UINT32  link_busy:1;
        UINT32  translation_busy:1;
        UINT32  ddc_busy:1;
        UINT32  msc_busy:1;
    };
}cbus_wdog_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_int_en_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:25;
        UINT32  irq_discovery:1;
        UINT32  irq_link:1;
        UINT32  irq_ddc:1;
        UINT32  irq_msc_ch:1;
        UINT32  irq_msc_int:1;
        UINT32  irq_msc_stat:1;
        UINT32  rvd2:1;
    };
}cbus_int_index_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:22;
        UINT32  fw_control_r10k:1;
        UINT32  fw_r10k_en:2;
        UINT32  cbus_test_md:1;
        UINT32  fw_out:1;
        UINT32  dbg_sel:3;
        UINT32  rvd2:2;
    };
}cbus_test_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dmy:32;
    };
}cbus_dummy0_RBUS;





#else //apply LITTLE_ENDIAN


//======MHL register structure define==========
typedef union
{
    UINT32 regValue;
    struct{
        UINT32  mhl_clk_ns:12;
        UINT32  rvd:16;
        UINT32  cbus_multi_sync:1;
        UINT32  irq_en_scpu:1;
        UINT32  irq_en_8051:1;
        UINT32  enable:1;
    };
}cbus_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  trxsense_deglitch:8;
        UINT32  tsrc_stable:10;
        UINT32  rxsense_fw_value:1;
        UINT32  rxsense_fw_mode:1;
        UINT32  tsrc_float:8;
        UINT32  bypass_discov:1;
        UINT32  rvd:3;
    };
}cbus_dis0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tsrc_wake_to_discov:10;
        UINT32  tsrc_wake_width2:7;
        UINT32  tsrc_wake_width1:5;
        UINT32  trxsense_chk:9;
        UINT32  both_path_en:1;
    };
}cbus_dis1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tsrc_arbitrate:10;
        UINT32  rvd1:2;
        UINT32  tsrc_conn:8;
        UINT32  tsrc_pulse_width:7;
        UINT32  rvd2:5;
    };
}cbus_dis2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  discov_standby:1;
        UINT32  irq_en_tmds_out:1;
        UINT32  irq_en_tmds_off:1;
        UINT32  irq_en_src3_4:1;
        UINT32  irq_en_src6_7:1;
        UINT32  rvd1:3;
        UINT32  max_discovery_pulse_count:5;
        UINT32  rvd2:3;
        UINT32  drive_wake_pulse_low_en:1;
        UINT32  discovery_check_sink_start:5;
        UINT32  rvd3:2;
        UINT32  tsink_float:8;
    };
}cbus_dis3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:1;
        UINT32  irq_tmds_out:1;
        UINT32  irq_tmds_off:1;
        UINT32  irq_src3_4:1;
        UINT32  irq_src6_7:1;
        UINT32  rvd2:7;
        UINT32  src7:1;
        UINT32  src6:1;
        UINT32  src5:1;
        UINT32  src4:1;
        UINT32  src3_11:1;
        UINT32  src3_10:1;
        UINT32  src3_09:1;
        UINT32  src3_08:1;
        UINT32  src3_07:1;
        UINT32  src3_06:1;
        UINT32  src3_05:1;
        UINT32  src3_04:1;
        UINT32  src3_03:1;
        UINT32  src3_02:1;
        UINT32  src3_01:1;
        UINT32  src3_00:1;
        UINT32  src2:1;
        UINT32  src1:1;
        UINT32  src0:1;
        UINT32  rvd3:1;
    };
}cbus_dis4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dmy:32;
    };
}cbus_dis5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tst_sel_h:2;
        UINT32  reg_cbus_strc:3;
        UINT32  hdmi_hpd_en:1;
        UINT32  reg_en_bias:1;
        UINT32  reg_mhl_r10k:3;
        UINT32  reg_mhl_vsel:3;
        UINT32  reg_mhl_tst_en:1;
        UINT32  reg_r1k_vth_sel:1;
        UINT32  reg_mhl_r1k_det:1;
        UINT32  reg_mhl_hpd_det:1;
        UINT32  reg_mhl_bmos_en:1;
        UINT32  reg_r1k_replace:1;
        UINT32  reg_mhl_r10k_test:1;
        UINT32  dmy:12;
    };
}cbus_phy0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rego_mhl_r1k_det:1;
        UINT32  rego_mhl_hpd_det:1;
        UINT32  reg_mhl_r10k_en:2;
        UINT32  hdmi_hpd_out:1;
        UINT32  rvd:27;
    };
}cbus_phy1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dev_state:8;
        UINT32  rvd:24;
    };
}msc_reg_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  mhl_ver:8;
        UINT32  rvd:24;
    };
}msc_reg_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dev_type:4;
        UINT32  pow:1;
        UINT32  plim:2;
        UINT32  dev_cat:1;
        UINT32  rvd:24;
    };
}msc_reg_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  adop_id_h:8;
        UINT32  rvd:24;
    };
}msc_reg_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  adop_id_l:8;
        UINT32  rvd:24;
    };
}msc_reg_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  supp_rgb444:1;
        UINT32  supp_yuv444:1;
        UINT32  supp_yuv422:1;
        UINT32  supp_ppixel:1;
        UINT32  supp_islands:1;
        UINT32  supp_vga:1;
        UINT32  vid_link_mode:2;
        UINT32  rvd:24;
    };
}msc_reg_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  aud_2ch:1;
        UINT32  aud_8ch:1;
        UINT32  aud_link_mode:6;
        UINT32  rvd:24;
    };
}msc_reg_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  vt_graphics:1;
        UINT32  vt_photo:1;
        UINT32  vt_cinema:1;
        UINT32  vt_game:1;
        UINT32  video_type:3;
        UINT32  supp_vt:1;
        UINT32  rvd:24;
    };
}msc_reg_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ld_display:1;
        UINT32  ld_video:1;
        UINT32  ld_audio:1;
        UINT32  ld_media:1;
        UINT32  ld_tuner:1;
        UINT32  ld_record:1;
        UINT32  ld_speaker:1;
        UINT32  ld_gui:1;
        UINT32  rvd:24;
    };
}msc_reg_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  bandwid:8;
        UINT32  rvd:24;
    };
}msc_reg_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rcp_supp:1;
        UINT32  rap_supp:1;
        UINT32  sp_supp:1;
        UINT32  ucp_send_supp:1;
        UINT32  ucp_recv_supp:1;
        UINT32  feature_flag:3;
        UINT32  rvd:24;
    };
}msc_reg_0a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  device_id_h:8;
        UINT32  rvd:24;
    };
}msc_reg_0b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  device_id_l:8;
        UINT32  rvd:24;
    };
}msc_reg_0c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scr_size:8;
        UINT32  rvd:24;
    };
}msc_reg_0d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  int_size:4;
        UINT32  stat_size:4;
        UINT32  rvd:24;
    };
}msc_reg_0e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  cap_0f:8;
        UINT32  rvd:24;
    };
}msc_reg_0f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dcap_chg:1;
        UINT32  dscr_chg:1;
        UINT32  req_wrt:1;
        UINT32  grt_wrt:1;
        UINT32  _3d_req:1;
        UINT32  rchg_int:3;
        UINT32  rvd:24;
    };
}msc_reg_20_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dchg_int_0:1;
        UINT32  edid_chg:1;
        UINT32  dchg_int_2:1;
        UINT32  dchg_int_3:1;
        UINT32  dchg_int_4:1;
        UINT32  dchg_int_5:1;
        UINT32  dchg_int_6:1;
        UINT32  dchg_int_7:1;
        UINT32  rvd:24;
    };
}msc_reg_21_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  chg22_0:1;
        UINT32  chg22_1:1;
        UINT32  chg22_2:1;
        UINT32  chg22_3:1;
        UINT32  chg22_4:1;
        UINT32  chg22_5:1;
        UINT32  chg22_6:1;
        UINT32  chg22_7:1;
        UINT32  rvd:24;
    };
}msc_reg_22_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  chg23_0:1;
        UINT32  chg23_1:1;
        UINT32  chg23_2:1;
        UINT32  chg23_3:1;
        UINT32  chg23_4:1;
        UINT32  chg23_5:1;
        UINT32  chg23_6:1;
        UINT32  chg23_7:1;
        UINT32  rvd:24;
    };
}msc_reg_23_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  chg24_0:1;
        UINT32  chg24_1:1;
        UINT32  chg24_2:1;
        UINT32  chg24_3:1;
        UINT32  chg24_4:1;
        UINT32  chg24_5:1;
        UINT32  chg24_6:1;
        UINT32  chg24_7:1;
        UINT32  rvd:24;
    };
}msc_reg_24_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  chg25_0:1;
        UINT32  chg25_1:1;
        UINT32  chg25_2:1;
        UINT32  chg25_3:1;
        UINT32  chg25_4:1;
        UINT32  chg25_5:1;
        UINT32  chg25_6:1;
        UINT32  chg25_7:1;
        UINT32  rvd:24;
    };
}msc_reg_25_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  chg26_0:1;
        UINT32  chg26_1:1;
        UINT32  chg26_2:1;
        UINT32  chg26_3:1;
        UINT32  chg26_4:1;
        UINT32  chg26_5:1;
        UINT32  chg26_6:1;
        UINT32  chg26_7:1;
        UINT32  rvd:24;
    };
}msc_reg_26_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  chg27_0:1;
        UINT32  chg27_1:1;
        UINT32  chg27_2:1;
        UINT32  chg27_3:1;
        UINT32  chg27_4:1;
        UINT32  chg27_5:1;
        UINT32  chg27_6:1;
        UINT32  chg27_7:1;
        UINT32  rvd:24;
    };
}msc_reg_27_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dcap_rdy:1;
        UINT32  connected_rdy:7;
        UINT32  rvd:24;
    };
}msc_reg_30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:3;
        UINT32  path_en:1;
        UINT32  rvd2:1;
        UINT32  link_mode:3;
        UINT32  rvd3:24;
    };
}msc_reg_31_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  stat_32:8;
        UINT32  rvd:24;
    };
}msc_reg_32_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  stat_33:8;
        UINT32  rvd:24;
    };
}msc_reg_33_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  stat_34:8;
        UINT32  rvd:24;
    };
}msc_reg_34_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  stat_35:8;
        UINT32  rvd:24;
    };
}msc_reg_35_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  stat_36:8;
        UINT32  rvd:24;
    };
}msc_reg_36_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  stat_37:8;
        UINT32  rvd:24;
    };
}msc_reg_37_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_40:8;
        UINT32  rvd:24;
    };
}msc_reg_40_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_41:8;
        UINT32  rvd:24;
    };
}msc_reg_41_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_42:8;
        UINT32  rvd:24;
    };
}msc_reg_42_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_43:8;
        UINT32  rvd:24;
    };
}msc_reg_43_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_44:8;
        UINT32  rvd:24;
    };
}msc_reg_44_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_45:8;
        UINT32  rvd:24;
    };
}msc_reg_45_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_46:8;
        UINT32  rvd:24;
    };
}msc_reg_46_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_47:8;
        UINT32  rvd:24;
    };
}msc_reg_47_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_48:8;
        UINT32  rvd:24;
    };
}msc_reg_48_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_49:8;
        UINT32  rvd:24;
    };
}msc_reg_49_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_4a:8;
        UINT32  rvd:24;
    };
}msc_reg_4a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_4b:8;
        UINT32  rvd:24;
    };
}msc_reg_4b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_4c:8;
        UINT32  rvd:24;
    };
}msc_reg_4c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_4d:8;
        UINT32  rvd:24;
    };
}msc_reg_4d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_4e:8;
        UINT32  rvd:24;
    };
}msc_reg_4e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_4f:8;
        UINT32  rvd:24;
    };
}msc_reg_4f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_50:8;
        UINT32  rvd:24;
    };
}msc_reg_50_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_51:8;
        UINT32  rvd:24;
    };
}msc_reg_51_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_52:8;
        UINT32  rvd:24;
    };
}msc_reg_52_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_53:8;
        UINT32  rvd:24;
    };
}msc_reg_53_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_54:8;
        UINT32  rvd:24;
    };
}msc_reg_54_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_55:8;
        UINT32  rvd:24;
    };
}msc_reg_55_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_56:8;
        UINT32  rvd:24;
    };
}msc_reg_56_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_57:8;
        UINT32  rvd:24;
    };
}msc_reg_57_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_58:8;
        UINT32  rvd:24;
    };
}msc_reg_58_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_59:8;
        UINT32  rvd:24;
    };
}msc_reg_59_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_5a:8;
        UINT32  rvd:24;
    };
}msc_reg_5a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_5b:8;
        UINT32  rvd:24;
    };
}msc_reg_5b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_5c:8;
        UINT32  rvd:24;
    };
}msc_reg_5c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_5d:8;
        UINT32  rvd:24;
    };
}msc_reg_5d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_5e:8;
        UINT32  rvd:24;
    };
}msc_reg_5e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scratch_5f:8;
        UINT32  rvd:24;
    };
}msc_reg_5f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sync0_lb:9;
        UINT32  sync0_hb:9;
        UINT32  rvd:14;
    };
}cbus_link_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sync1_lb:8;
        UINT32  sync1_hb:8;
        UINT32  rvd:16;
    };
}cbus_link_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sync_bit_time:8;
        UINT32  rvd:24;
    };
}cbus_link_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  abs_threshold:8;
        UINT32  abs_thres_en:1;
        UINT32  rvd:23;
    };
}cbus_link_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_link_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  parity_fail_limit:5;
        UINT32  ctrl_16_resv:1;
        UINT32  irq_en_parity_fail:1;
        UINT32  rvd:25;
    };
}cbus_link_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ack_fall:7;
        UINT32  rvd:25;
    };
}cbus_link_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ack_0:7;
        UINT32  rvd:25;
    };
}cbus_link_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:7;
        UINT32  irq_parity_fail:1;
        UINT32  rvd2:24;
    };
}cbus_link_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tx_bit_time:8;
        UINT32  rvd:24;
    };
}cbus_link_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_link_0a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tx_ack_fal:7;
        UINT32  rvd:25;
    };
}cbus_link_0b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tx_ack_low_hb:7;
        UINT32  rvd:25;
    };
}cbus_link_0c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tx_ack_low_lb:7;
        UINT32  rvd:25;
    };
}cbus_link_0d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dmy:4;
        UINT32  irq_en_retry_msc:1;
        UINT32  irq_en_retry_ddc:1;
        UINT32  retry_lv:7;
        UINT32  rvd:19;
    };
}cbus_link_0e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  drv_hi_cbus:6;
        UINT32  drv_str:5;
        UINT32  rvd:21;
    };
}cbus_link_0f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  wait:4;
        UINT32  rvd:28;
    };
}cbus_link_10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  req_opp:8;
        UINT32  rvd:24;
    };
}cbus_link_11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  req_cont:8;
        UINT32  rvd:24;
    };
}cbus_link_12_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  resp_hold:4;
        UINT32  req_hold:4;
        UINT32  rvd:24;
    };
}cbus_link_13_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_en_link_err:1;
        UINT32  rvd1:5;
        UINT32  glob_time:8;
        UINT32  rvd2:2;
        UINT32  packet_max:5;
        UINT32  rvd3:10;
        UINT32  rx_fifo_clr:1;
    };
}cbus_link_14_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_link_err:1;
        UINT32  chk_err:1;
        UINT32  irq_retry_msc:1;
        UINT32  irq_retry_ddc:1;
        UINT32  rvd1:2;
        UINT32  burst_timeout:1;
        UINT32  rvd2:25;
    };
}cbus_link_15_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  avoid_conf:1;
        UINT32  rvd1:7;
        UINT32  fwdef_cmd_rev:8;
        UINT32  rvd2:16;
    };
}cbus_flag_0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dmy:5;
        UINT32  mcumsc_en:1;
        UINT32  rvd:25;
        UINT32  msc_idle_resp_abort:1;
    };
}cbus_msc_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  na_msc_cmd:8;
        UINT32  rvd:24;
    };
}cbus_msc_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  na_msc_offset:8;
        UINT32  rx_fifo_empty:1;
        UINT32  rx_fifo_full:1;
        UINT32  rvd1:6;
        UINT32  na_rx_len:5;
        UINT32  rvd2:11;
    };
}cbus_msc_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rx_fifo_data:8;
        UINT32  rvd:24;
    };
}cbus_msc_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_ddc_abort:1;
        UINT32  irq_abort_req:1;
        UINT32  irq_abort_res:1;
        UINT32  irq_allmsc_cmd:1;
        UINT32  irq_fwdef_cmd:1;
        UINT32  irq_sc3_err:1;
        UINT32  irq_wr_burst:1;
        UINT32  irq_msc_err:1;
        UINT32  irq_ddc_err:1;
        UINT32  irq_sc1_err:1;
        UINT32  irq_get_msg:1;
        UINT32  irq_get_id:1;
        UINT32  irq_get_stat:1;
        UINT32  irq_rd_devcap:1;
        UINT32  irq_wr_stat:1;
        UINT32  irq_msg_sub:1;
        UINT32  irq_rapk:1;
        UINT32  irq_rap:1;
        UINT32  irq_rcpe:1;
        UINT32  irq_rcpk:1;
        UINT32  irq_rcp:1;
        UINT32  irq_msge:1;
        UINT32  rvd3:1;
        UINT32  irq_path_en_chg:1;
        UINT32  rvd2:1;
        UINT32  irq_dcap_rdy_chg:1;
        UINT32  irq_ucpe:1;
        UINT32  irq_ucpk:1;
        UINT32  irq_ucp:1;
        UINT32  rvd1:3;
    };
}cbus_msc_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_en_ddc_abort:1;
        UINT32  irq_en_abort_req:1;
        UINT32  irq_en_abort_res:1;
        UINT32  irq_en_allmsc_cmd:1;
        UINT32  irq_en_fwdef_cmd:1;
        UINT32  irq_en_sc3_err:1;
        UINT32  irq_en_wr_burst:1;
        UINT32  irq_en_msc_err:1;
        UINT32  irq_en_ddc_err:1;
        UINT32  irq_en_sc1_err:1;
        UINT32  irq_en_get_msg:1;
        UINT32  irq_en_get_id:1;
        UINT32  irq_en_get_stat:1;
        UINT32  irq_en_rd_devcap:1;
        UINT32  irq_en_wr_stat:1;
        UINT32  irq_en_msg_sub:1;
        UINT32  irq_en_rapk:1;
        UINT32  irq_en_rap:1;
        UINT32  irq_en_rcpe:1;
        UINT32  irq_en_rcpk:1;
        UINT32  irq_en_rcp:1;
        UINT32  irq_en_msge:1;
        UINT32  rvd1:1;
        UINT32  irq_en_path_en_chg:1;
        UINT32  rvd2:1;
        UINT32  irq_en_dcap_rdy_chg:1;
        UINT32  irq_en_ucpe:1;
        UINT32  irq_en_ucpk:1;
        UINT32  irq_en_ucp:1;
        UINT32  rvd3:3;
    };
}cbus_msc_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_chg23_bit0:1;
        UINT32  irq_chg23_bit1:1;
        UINT32  irq_chg23_bit2:1;
        UINT32  irq_chg23_bit3:1;
        UINT32  irq_chg23_bit4:1;
        UINT32  irq_chg23_bit5:1;
        UINT32  irq_chg23_bit6:1;
        UINT32  irq_chg23_bit7:1;
        UINT32  irq_chg22_bit0:1;
        UINT32  irq_chg22_bit1:1;
        UINT32  irq_chg22_bit2:1;
        UINT32  irq_chg22_bit3:1;
        UINT32  irq_chg22_bit4:1;
        UINT32  irq_chg22_bit5:1;
        UINT32  irq_chg22_bit6:1;
        UINT32  irq_chg22_bit7:1;
        UINT32  irq_dchg_bit0:1;
        UINT32  irq_edid_chg:1;
        UINT32  irq_dchg_bit2:1;
        UINT32  irq_dchg_bit3:1;
        UINT32  irq_dchg_bit4:1;
        UINT32  irq_dchg_bit5:1;
        UINT32  irq_dchg_bit6:1;
        UINT32  irq_dchg_bit7:1;
        UINT32  irq_dcap_chg:1;
        UINT32  irq_dscr_chg:1;
        UINT32  irq_req_wrt:1;
        UINT32  irq_grt_wrt:1;
        UINT32  irq_3d_req:1;
        UINT32  irq_rchg_bit5:1;
        UINT32  irq_rchg_bit6:1;
        UINT32  irq_rchg_bit7:1;
    };
}cbus_msc_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_en_chg23_bit0:1;
        UINT32  irq_en_chg23_bit1:1;
        UINT32  irq_en_chg23_bit2:1;
        UINT32  irq_en_chg23_bit3:1;
        UINT32  irq_en_chg23_bit4:1;
        UINT32  irq_en_chg23_bit5:1;
        UINT32  irq_en_chg23_bit6:1;
        UINT32  irq_en_chg23_bit7:1;
        UINT32  irq_en_chg22_bit0:1;
        UINT32  irq_en_chg22_bit1:1;
        UINT32  irq_en_chg22_bit2:1;
        UINT32  irq_en_chg22_bit3:1;
        UINT32  irq_en_chg22_bit4:1;
        UINT32  irq_en_chg22_bit5:1;
        UINT32  irq_en_chg22_bit6:1;
        UINT32  irq_en_chg22_bit7:1;
        UINT32  irq_en_dchg_bit0:1;
        UINT32  irq_en_edid_chg:1;
        UINT32  irq_en_dchg_bit2:1;
        UINT32  irq_en_dchg_bit3:1;
        UINT32  irq_en_dchg_bit4:1;
        UINT32  irq_en_dchg_bit5:1;
        UINT32  irq_en_dchg_bit6:1;
        UINT32  irq_en_dchg_bit7:1;
        UINT32  irq_en_dcap_chg:1;
        UINT32  irq_en_dscr_chg:1;
        UINT32  irq_en_req_wrt:1;
        UINT32  irq_en_grt_wrt:1;
        UINT32  irq_en_3d_req:1;
        UINT32  irq_en_rchg_bit5:1;
        UINT32  irq_en_rchg_bit6:1;
        UINT32  irq_en_rchg_bit7:1;
    };
}cbus_msc_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_chg27_bit0:1;
        UINT32  irq_chg27_bit1:1;
        UINT32  irq_chg27_bit2:1;
        UINT32  irq_chg27_bit3:1;
        UINT32  irq_chg27_bit4:1;
        UINT32  irq_chg27_bit5:1;
        UINT32  irq_chg27_bit6:1;
        UINT32  irq_chg27_bit7:1;
        UINT32  irq_chg26_bit0:1;
        UINT32  irq_chg26_bit1:1;
        UINT32  irq_chg26_bit2:1;
        UINT32  irq_chg26_bit3:1;
        UINT32  irq_chg26_bit4:1;
        UINT32  irq_chg26_bit5:1;
        UINT32  irq_chg26_bit6:1;
        UINT32  irq_chg26_bit7:1;
        UINT32  irq_chg25_bit0:1;
        UINT32  irq_chg25_bit1:1;
        UINT32  irq_chg25_bit2:1;
        UINT32  irq_chg25_bit3:1;
        UINT32  irq_chg25_bit4:1;
        UINT32  irq_chg25_bit5:1;
        UINT32  irq_chg25_bit6:1;
        UINT32  irq_chg25_bit7:1;
        UINT32  irq_chg24_bit0:1;
        UINT32  irq_chg24_bit1:1;
        UINT32  irq_chg24_bit2:1;
        UINT32  irq_chg24_bit3:1;
        UINT32  irq_chg24_bit4:1;
        UINT32  irq_chg24_bit5:1;
        UINT32  irq_chg24_bit6:1;
        UINT32  irq_chg24_bit7:1;
    };
}cbus_msc_0a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  irq_en_chg27_bit0:1;
        UINT32  irq_en_chg27_bit1:1;
        UINT32  irq_en_chg27_bit2:1;
        UINT32  irq_en_chg27_bit3:1;
        UINT32  irq_en_chg27_bit4:1;
        UINT32  irq_en_chg27_bit5:1;
        UINT32  irq_en_chg27_bit6:1;
        UINT32  irq_en_chg27_bit7:1;
        UINT32  irq_en_chg26_bit0:1;
        UINT32  irq_en_chg26_bit1:1;
        UINT32  irq_en_chg26_bit2:1;
        UINT32  irq_en_chg26_bit3:1;
        UINT32  irq_en_chg26_bit4:1;
        UINT32  irq_en_chg26_bit5:1;
        UINT32  irq_en_chg26_bit6:1;
        UINT32  irq_en_chg26_bit7:1;
        UINT32  irq_en_chg25_bit0:1;
        UINT32  irq_en_chg25_bit1:1;
        UINT32  irq_en_chg25_bit2:1;
        UINT32  irq_en_chg25_bit3:1;
        UINT32  irq_en_chg25_bit4:1;
        UINT32  irq_en_chg25_bit5:1;
        UINT32  irq_en_chg25_bit6:1;
        UINT32  irq_en_chg25_bit7:1;
        UINT32  irq_en_chg24_bit0:1;
        UINT32  irq_en_chg24_bit1:1;
        UINT32  irq_en_chg24_bit2:1;
        UINT32  irq_en_chg24_bit3:1;
        UINT32  irq_en_chg24_bit4:1;
        UINT32  irq_en_chg24_bit5:1;
        UINT32  irq_en_chg24_bit6:1;
        UINT32  irq_en_chg24_bit7:1;
    };
}cbus_msc_0b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msc_err_code:8;
        UINT32  rvd:24;
    };
}cbus_msc_0c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  vendor_id:8;
        UINT32  rcp_reply_nack:1;
        UINT32  rcp_reply_abort:1;
        UINT32  rvd:22;
    };
}cbus_msc_0d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msg_cmd:8;
        UINT32  rvd:24;
    };
}cbus_msc_0e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msg_dat:8;
        UINT32  rvd:24;
    };
}cbus_msc_0f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msge_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rcp_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rcpk_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_12_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rcpe_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_13_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rap_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_14_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rapk_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_15_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:5;
        UINT32  wb_id_chk:1;
        UINT32  rvd2:26;
    };
}cbus_msc_16_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  adop_idl_rcv:8;
        UINT32  adop_idh_rcv:8;
        UINT32  rvd:16;
    };
}cbus_msc_17_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_18_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_msc_19_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_fsm:6;
        UINT32  msc_fsm:6;
        UINT32  rvd:20;
    };
}cbus_msc_1a_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  cap_offset:8;
        UINT32  rvd:24;
    };
}cbus_msc_1b_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  int_offset:8;
        UINT32  rvd:24;
    };
}cbus_msc_1c_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sta_offset:8;
        UINT32  rvd:24;
    };
}cbus_msc_1d_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scr_offset:8;
        UINT32  rvd:24;
    };
}cbus_msc_1e_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msc_err_force:1;
        UINT32  ddc_err_force:1;
        UINT32  rvd:30;
    };
}cbus_msc_1f_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_err_fw:8;
        UINT32  rvd:24;
    };
}cbus_msc_20_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msc_err_fw:8;
        UINT32  rvd:24;
    };
}cbus_msc_21_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ucp_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_22_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ucpk_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_23_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ucpe_rcv:8;
        UINT32  rvd:24;
    };
}cbus_msc_24_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:5;
        UINT32  fw0_fifo_empty:1;
        UINT32  fw0_fifo_full:1;
        UINT32  rvd2:1;
        UINT32  fw0_req:1;
        UINT32  fw0_msg_processing:1;
        UINT32  rvd3:22;
    };
}fw0_req_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_cmd1:8;
        UINT32  fw0_tx_case:3;
        UINT32  rvd1:1;
        UINT32  check_fw0_msg_processing:1;
        UINT32  rvd2:19;
    };
}fw0_req_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_cmd2:8;
        UINT32  rvd:24;
    };
}fw0_req_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_offset:8;
        UINT32  fw0_data2:8;
        UINT32  fw0_data1:8;
        UINT32  rvd:8;
    };
}fw0_req_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_data:8;
        UINT32  rvd:24;
    };
}fw0_req_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:2;
        UINT32  irq_en_fw0_data:1;
        UINT32  irq_en_fw0_cmd:1;
        UINT32  irq_en_fw0_fin:1;
        UINT32  irq_en_fw0_rcv_err:1;
        UINT32  rvd2:2;
        UINT32  fw0_fifo_len:4;
        UINT32  rvd3:19;
        UINT32  fw0_fifo_clr:1;
    };
}fw0_req_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_cmd_rcv:8;
        UINT32  rvd:24;
    };
}fw0_req_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_data_rcv:8;
        UINT32  rvd:24;
    };
}fw0_req_07_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  fw0_rdata:8;
        UINT32  rvd:24;
    };
}fw0_req_08_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:5;
        UINT32  irq_fw0_rcv_err:1;
        UINT32  irq_fw0_data:1;
        UINT32  irq_fw0_cmd:1;
        UINT32  irq_fw0_fin:1;
        UINT32  rvd2:23;
    };
}fw0_req_09_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_err_code:8;
        UINT32  irq_ddc_data:1;
        UINT32  rvd:22;
        UINT32  ddc_req:1;
    };
}cbus_ddc_00_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:8;
        UINT32  ddc_addr_r:8;
        UINT32  ddc_addr_w:8;
        UINT32  rvd2:7;
        UINT32  ddc_idle_resp_abort:1;
    };
}cbus_ddc_01_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:1;
        UINT32  ddc_req_ctrl:1;
        UINT32  irq_en_ddc_data:1;
        UINT32  rvd2:4;
        UINT32  mcuddc_en:1;
        UINT32  mcuddc_need_resp:1;
        UINT32  ddc_req_type:2;
        UINT32  rvd3:21;
    };
}cbus_ddc_02_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_cmd_fw:8;
        UINT32  rvd:24;
    };
}cbus_ddc_03_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_rcv_data:9;
        UINT32  rvd:23;
    };
}cbus_ddc_04_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_data_fw:8;
        UINT32  rvd:24;
    };
}cbus_ddc_05_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ddc_addr_0x60:8;
        UINT32  ddc_seg_val:8;
        UINT32  ddc_offset:8;
        UINT32  rvd:8;
    };
}cbus_ddc_06_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  msc_busy:1;
        UINT32  ddc_busy:1;
        UINT32  translation_busy:1;
        UINT32  link_busy:1;
        UINT32  cbus_busy:1;
        UINT32  rvd:27;
    };
}cbus_wdog_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:32;
    };
}cbus_int_en_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:1;
        UINT32  irq_msc_stat:1;
        UINT32  irq_msc_int:1;
        UINT32  irq_msc_ch:1;
        UINT32  irq_ddc:1;
        UINT32  irq_link:1;
        UINT32  irq_discovery:1;
        UINT32  rvd2:25;
    };
}cbus_int_index_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:2;
        UINT32  dbg_sel:3;
        UINT32  fw_out:1;
        UINT32  cbus_test_md:1;
        UINT32  fw_r10k_en:2;
        UINT32  fw_control_r10k:1;
        UINT32  rvd2:22;
    };
}cbus_test_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dmy:32;
    };
}cbus_dummy0_RBUS;


#endif







#endif //_RBUS_MHL_REG_H_

