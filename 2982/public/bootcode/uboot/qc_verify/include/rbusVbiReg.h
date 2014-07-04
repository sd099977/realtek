/**
* @file rbusVbiReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/30
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_VBI_REG_H_
#define _RBUS_VBI_REG_H_

#include "rbusTypes.h"




// VBI Register Address
#define VBI_VBISL0_VADDR                           (0xb8034800)
#define VBI_TT_VBI_CC_CTRL0_VADDR                  (0xb8034804)
#define VBI_TT_VBI_CC_CTRL1_VADDR                  (0xb8034808)
#define VBI_TT_VBI_CC_CTRL2_VADDR                  (0xb803480c)
#define VBI_VBI_CC_PATTERN_COMPARE_1_VADDR         (0xb8034810)
#define VBI_VBI_CC_PATTERN_COMPARE_2_VADDR         (0xb8034814)
#define VBI_VBI_VOUNT_SHIFT_VADDR                  (0xb8034820)
#define VBI_CGMS_C0_VADDR                          (0xb8034900)
#define VBI_CGMS_C1_VADDR                          (0xb8034904)
#define VBI_CGMS_C2_VADDR                          (0xb8034908)
#define VBI_CGMS_C3_VADDR                          (0xb803490c)
#define VBI_CGMS_C4_VADDR                          (0xb8034910)
#define VBI_CGMS_C5_VADDR                          (0xb8034914)
#define VBI_TT_VBI_TT_DATA00_VADDR                 (0xb8034918)
#define VBI_TT_VBI_TT_DATA01_VADDR                 (0xb803491c)
#define VBI_TT_VBI_TT_DATA02_VADDR                 (0xb8034920)
#define VBI_TT_VBI_TT_DATA03_VADDR                 (0xb8034924)
#define VBI_TT_VBI_TT_DATA04_VADDR                 (0xb8034928)
#define VBI_TT_VBI_TT_DATA05_VADDR                 (0xb803492c)
#define VBI_TT_VBI_TT_DATA06_VADDR                 (0xb8034930)
#define VBI_TT_VBI_TT_DATA07_VADDR                 (0xb8034934)
#define VBI_TT_VBI_TT_DATA08_VADDR                 (0xb8034938)
#define VBI_TT_VBI_TT_DATA09_VADDR                 (0xb803493c)
#define VBI_TT_VBI_TT_DATA10_VADDR                 (0xb8034940)
#define VBI_TT_VBI_CONTROL_REGISTER_VADDR          (0xb8034a00)
#define VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_5_8_VADDR  (0xb8034a04)
#define VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_9_12_VADDR  (0xb8034a08)
#define VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_13_16_VADDR  (0xb8034a0c)
#define VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_17_20_VADDR  (0xb8034a10)
#define VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_21_24_VADDR  (0xb8034a14)
#define VBI_TT_VBI_DATA_TYPE_CONFIG_REG_FOR_LINE_25_26_VADDR  (0xb8034a18)
#define VBI_TT_VBI_LOOP_FILTER_I_GAIN_REGISTER_VADDR  (0xb8034a1c)
#define VBI_TT_VBI_DTO_REGISTER1_VADDR             (0xb8034a20)
#define VBI_TT_VBI_DTO_REGISTER2_VADDR             (0xb8034a24)
#define VBI_TT_VBI_DTO_FRAME_START_VADDR           (0xb8034a28)
#define VBI_TT_VBI_CCWSS_DATA_VADDR                (0xb8034a2c)
#define VBI_TT_VBI_DATA_STATUS_VADDR               (0xb8034a30)
#define VBI_TT_VBI_START_VADDR                     (0xb8034a3c)
#define VBI_TT_VPS_DATA3_VADDR                     (0xb8034a40)
#define VBI_TT_VPS_DATA2_VADDR                     (0xb8034a44)
#define VBI_TT_VPS_DATA1_VADDR                     (0xb8034a48)
#define VBI_TT_VPS_DATA0_VADDR                     (0xb8034a4c)
#define VBI_TT_VBI_NOISY_CTRL1_VADDR               (0xb8034a60)
#define VBI_TT_VBI_NOISY_CTRL2_VADDR               (0xb8034a64)
#define VBI_TT_VBI_NOISY_CTRL3_VADDR               (0xb8034a68)
#define VBI_TT_VBI_CO_CH_CTRL_VADDR                (0xb8034a6c)
#define VBI_TT_VBI_CLAMPAGC_CTRL_VADDR             (0xb8034a70)
#define VBI_TT_VBI_NOISY_CTRL_VADDR                (0xb8034a74)
#define VBI_TT_VBI_PATTERN_SEL_VADDR               (0xb8034a78)
#define VBI_TT_VBI_PATTERN_SEL1_VADDR              (0xb8034a7c)
#define VBI_TT_VBI_PATTERN_SEL2_VADDR              (0xb8034a80)
#define VBI_TT_VBI_PATTERN_SEL3_VADDR              (0xb8034a84)
#define VBI_TT_VBI_NOISY_CTRL4_VADDR               (0xb8034a88)
#define VBI_TT_VBI_NOISY_CTRL5_VADDR               (0xb8034a8c)
#define VBI_TT_VBI_NOISY_CTRL6_VADDR               (0xb8034a90)
#define VBI_TT_VBI_STATUS1_VADDR                   (0xb8034a94)
#define VBI_TT_VBI_STATUS2_VADDR                   (0xb8034a98)
#define VBI_TT_VBI_STATUS3_VADDR                   (0xb8034a9c)
#define VBI_TT_VBI_STATUS4_VADDR                   (0xb8034aa0)
#define VBI_TT_VBI_DUMP_DATA1_VADDR                (0xb8034aa4)
#define VBI_TT_VBI_DUMP_DATA2_VADDR                (0xb8034aa8)
#define VBI_TT_VBI_ODD_PARIORITY_RECOVERY_VADDR    (0xb8034aac)
#define VBI_TT_VBI_ODD_PARIORITY_RECOVERY_1_VADDR  (0xb8034ab0)
#define VBI_TT_VBI_AGC_SLICE_LEVEL_VADDR           (0xb8034ab4)
#define VBI_TT_VBI_AGC_SLICE_LEVEL1_VADDR          (0xb8034ab8)
#define VBI_TT_VBI_AGC_SLICE_LEVEL2_VADDR          (0xb8034abc)
#define VBI_TT_VBI_WSS_VPS_VOTE_VADDR              (0xb8034ac0)
#define VBI_TT_VBI_WSS_VPS_VOTE2_VADDR             (0xb8034ac4)
#define VBI_TT_VBI_PAGE6_VADDR                     (0xb8034ac8)
#define VBI_VBI_DEBUG_MODE_VADDR                   (0xb8034bc0)
#define VBI_VBI_FPGA_TEST1_VADDR                   (0xb8034bc4)
#define VBI_VBI_FPGA_TEST2_VADDR                   (0xb8034bc8)
#define VBI_VBI_FPGA_TEST3_VADDR                   (0xb8034bcc)
#define VBI_VBI_FPGA_TEST4_VADDR                   (0xb8034bd0)
#define VBI_VBI_FPGA_TEST5_VADDR                   (0xb8034bd4)
#define VBI_VBI_FPGA_TEST6_VADDR                   (0xb8034bd8)
#define VBI_VBI_FPGA_TEST7_VADDR                   (0xb8034bdc)
#define VBI_VBI_FPGA_TEST8_VADDR                   (0xb8034be0)
#define VBI_VBI_DMA_FRAME_ADDR_VADDR               (0xb8034c00)
#define VBI_VBI_DMA_FRAME_ADDR_END_VADDR           (0xb8034c04)
#define VBI_VBI_DMA_FIFO_STAUS_VADDR               (0xb8034c08)
#define VBI_VBI_DMA_CTRL_VADDR                     (0xb8034c0c)
#define VBI_VBI_DMA_VACTIVE1_VADDR                 (0xb8034c10)
#define VBI_VBI_DMA_VACTIVE2_VADDR                 (0xb8034c14)
#define VBI_VBI_DUMP_INT_VADDR                     (0xb8034c18)
#define VBI_BIST_TEST1_VADDR                       (0xb8034c1c)
#define VBI_BIST_MODE_VADDR                        (0xb8034c20)
#define VBI_BIST_DONE_VADDR                        (0xb8034c24)
#define VBI_BIST_FAIL_VADDR                        (0xb8034c28)
#define VBI_BIST_DRF_MODE_VADDR                    (0xb8034c2c)
#define VBI_BIST_DRF_RESUME_VADDR                  (0xb8034c30)
#define VBI_BIST_DONE_DRF_VADDR                    (0xb8034c34)
#define VBI_BIST_DRF_PAUSE_VADDR                   (0xb8034c38)
#define VBI_BIST_FAIL_DRF_VADDR                    (0xb8034c3c)
#define VBI_BIST_DVSE_VADDR                        (0xb8034c40)
#define VBI_VBI_PPR_LVLD1_VADDR                    (0xb8034c50)
#define VBI_VBI_PPR_LVLD2_VADDR                    (0xb8034c54)
#define VBI_VBIPPR_CTRL_REG_VADDR                  (0xb8034c58)
#define VBI_VBIPPR_PKT_RX_CNT_REG_VADDR            (0xb8034c5c)
#define VBI_VBIPPR_PG_MODE_REG_VADDR               (0xb8034c60)
#define VBI_VBIPPR_PG_LINE_ACT_REG_VADDR           (0xb8034c64)
#define VBI_VBIPPR_PGDATA_B1B4_REG_VADDR           (0xb8034c68)
#define VBI_VBIPPR_PGDATA_B5B8_REG_VADDR           (0xb8034c6c)
#define VBI_VBIPPR_PGDATA_B9B12_REG_VADDR          (0xb8034c70)
#define VBI_VBIPPR_PGDATA_B13B16_REG_VADDR         (0xb8034c74)
#define VBI_VBIPPR_PGDATA_B17B20_REG_VADDR         (0xb8034c78)
#define VBI_VBIPPR_PGDATA_B21B24_REG_VADDR         (0xb8034c7c)
#define VBI_VBIPPR_PGDATA_B25B28_REG_VADDR         (0xb8034c80)
#define VBI_VBIPPR_PGDATA_B29B32_REG_VADDR         (0xb8034c84)
#define VBI_VBIPPR_PGDATA_B33B36_REG_VADDR         (0xb8034c88)
#define VBI_VBIPPR_PGDATA_B37B40_REG_VADDR         (0xb8034c8c)
#define VBI_VBIPPR_PGDATA_B41B44_REG_VADDR         (0xb8034c90)
#define VBI_VBIPPR_PGDATA_B45B47_REG_VADDR         (0xb8034c94)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======VBI register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbisl_out_mux_manual_en:1;
        RBus_UInt32  vbisl_out_auto_tt_vps_sel:1;
        RBus_UInt32  vbisl_out_mux_sel:2;
        RBus_UInt32  vbi_dma_stop:1;
        RBus_UInt32  vbi_dma_stop_en:1;
        RBus_UInt32  res1:18;
        RBus_UInt32  vbisl0_src_sel:1;
        RBus_UInt32  vbisl0_sys625i:1;
        RBus_UInt32  vbisl0_fieldi_inv:1;
        RBus_UInt32  vbisl2_lcnt_field_inv:1;
        RBus_UInt32  res2:4;
    };
}vbisl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_cc_caposc_frun_en:1;
        RBus_UInt32  tt_vbi_cc_vote_en:1;
        RBus_UInt32  tt_vbi_cc_vote_sel:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_vbi_cc_vote_num:4;
        RBus_UInt32  res2:4;
        RBus_UInt32  tt_vbi_cc_data_swing_gain:4;
        RBus_UInt32  tt_vbi_cc_blank_offset:16;
    };
}tt_vbi_cc_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  find_start:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  tt_vbi_cc_st_correlation_en:1;
        RBus_UInt32  tt_vbi_cc_st_correlation_thl:8;
        RBus_UInt32  res2:16;
    };
}tt_vbi_cc_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_cc_out_hcount_en:1;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_cc_out_hcount_start:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_cc_out_hcount_end:10;
    };
}tt_vbi_cc_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  cc_pattern_field:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  find_start_num:6;
    };
}vbi_cc_pattern_compare_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cc_compare_data:32;
    };
}vbi_cc_pattern_compare_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  vbi_vount_shift_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vbi_vount_shift_field_inv:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  vbi_vount_shift_num:11;
    };
}vbi_vount_shift_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  cgms_c0_debounce_sel:3;
        RBus_UInt32  res2:6;
        RBus_UInt32  cgms_c0_slicer_dcl:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  cgms_c0_lpf_sel:2;
        RBus_UInt32  cgms_c0_slicer_ms:2;
        RBus_UInt32  cgms_c0_adap_slvl_en:1;
        RBus_UInt32  cgms_c0_slicen:1;
    };
}cgms_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  cgms_c1_actline_t:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  cgms_c1_actline_b:10;
    };
}cgms_c1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  cgms_c2_dcdet_st:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  cgms_c2_dcdet_end:10;
    };
}cgms_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  cgms_auto_period_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  cgms_period_cnt:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  cgms_c3_lv_dc_th:10;
    };
}cgms_c3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vbisl16_cgms_int_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  cgms_c4_cgms_vld:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  cgms_c4_cgmsdata:20;
    };
}cgms_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cgms_c5_min_period:8;
        RBus_UInt32  cgms_c5_max_period:8;
        RBus_UInt32  cgms_c5_period:8;
    };
}cgms_c5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  tt_ttdata41:8;
        RBus_UInt32  tt_ttdata40:8;
    };
}tt_vbi_tt_data00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata39:8;
        RBus_UInt32  tt_ttdata38:8;
        RBus_UInt32  tt_ttdata37:8;
        RBus_UInt32  tt_ttdata36:8;
    };
}tt_vbi_tt_data01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata35:8;
        RBus_UInt32  tt_ttdata34:8;
        RBus_UInt32  tt_ttdata33:8;
        RBus_UInt32  tt_ttdata32:8;
    };
}tt_vbi_tt_data02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata31:8;
        RBus_UInt32  tt_ttdata30:8;
        RBus_UInt32  tt_ttdata29:8;
        RBus_UInt32  tt_ttdata28:8;
    };
}tt_vbi_tt_data03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata27:8;
        RBus_UInt32  tt_ttdata26:8;
        RBus_UInt32  tt_ttdata25:8;
        RBus_UInt32  tt_ttdata24:8;
    };
}tt_vbi_tt_data04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata23:8;
        RBus_UInt32  tt_ttdata22:8;
        RBus_UInt32  tt_ttdata21:8;
        RBus_UInt32  tt_ttdata20:8;
    };
}tt_vbi_tt_data05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata19:8;
        RBus_UInt32  tt_ttdata18:8;
        RBus_UInt32  tt_ttdata17:8;
        RBus_UInt32  tt_ttdata16:8;
    };
}tt_vbi_tt_data06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata15:8;
        RBus_UInt32  tt_ttdata14:8;
        RBus_UInt32  tt_ttdata13:8;
        RBus_UInt32  tt_ttdata12:8;
    };
}tt_vbi_tt_data07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata11:8;
        RBus_UInt32  tt_ttdata10:8;
        RBus_UInt32  tt_ttdata9:8;
        RBus_UInt32  tt_ttdata8:8;
    };
}tt_vbi_tt_data08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata7:8;
        RBus_UInt32  tt_ttdata6:8;
        RBus_UInt32  tt_ttdata5:8;
        RBus_UInt32  tt_ttdata4:8;
    };
}tt_vbi_tt_data09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata3:8;
        RBus_UInt32  tt_ttdata2:8;
        RBus_UInt32  tt_ttdata1:8;
        RBus_UInt32  tt_ttdata0:8;
    };
}tt_vbi_tt_data10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_data_hlvl_wss:8;
        RBus_UInt32  tt_vbi_data_hlvl:8;
        RBus_UInt32  tt_start_code:8;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_adap_slvl_en:2;
        RBus_UInt32  tt_vbi_muxout:1;
        RBus_UInt32  tt_vbi_hsyncout:1;
        RBus_UInt32  tt_vbi_long_st_sel:1;
        RBus_UInt32  tt_vbi_st_err_ignored:1;
        RBus_UInt32  tt_vbi_en:1;
    };
}tt_vbi_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil8e:4;
        RBus_UInt32  tt_vbil8o:4;
        RBus_UInt32  tt_vbil7e:4;
        RBus_UInt32  tt_vbil7o:4;
        RBus_UInt32  tt_vbil6e:4;
        RBus_UInt32  tt_vbil6o:4;
        RBus_UInt32  tt_vbil5e:4;
        RBus_UInt32  tt_vbil5o:4;
    };
}tt_vbi_data_type_config_reg_for_line_5_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil12e:4;
        RBus_UInt32  tt_vbil12o:4;
        RBus_UInt32  tt_vbil11e:4;
        RBus_UInt32  tt_vbil11o:4;
        RBus_UInt32  tt_vbil10e:4;
        RBus_UInt32  tt_vbil10o:4;
        RBus_UInt32  tt_vbil9e:4;
        RBus_UInt32  tt_vbil9o:4;
    };
}tt_vbi_data_type_config_reg_for_line_9_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil16e:4;
        RBus_UInt32  tt_vbil16o:4;
        RBus_UInt32  tt_vbil15e:4;
        RBus_UInt32  tt_vbil15o:4;
        RBus_UInt32  tt_vbil14e:4;
        RBus_UInt32  tt_vbil14o:4;
        RBus_UInt32  tt_vbil13e:4;
        RBus_UInt32  tt_vbil13o:4;
    };
}tt_vbi_data_type_config_reg_for_line_13_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil20e:4;
        RBus_UInt32  tt_vbil20o:4;
        RBus_UInt32  tt_vbil19e:4;
        RBus_UInt32  tt_vbil19o:4;
        RBus_UInt32  tt_vbil18e:4;
        RBus_UInt32  tt_vbil18o:4;
        RBus_UInt32  tt_vbil17e:4;
        RBus_UInt32  tt_vbil17o:4;
    };
}tt_vbi_data_type_config_reg_for_line_17_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil24e:4;
        RBus_UInt32  tt_vbil24o:4;
        RBus_UInt32  tt_vbil23e:4;
        RBus_UInt32  tt_vbil23o:4;
        RBus_UInt32  tt_vbil22e:4;
        RBus_UInt32  tt_vbil22o:4;
        RBus_UInt32  tt_vbil21e:4;
        RBus_UInt32  tt_vbil21o:4;
    };
}tt_vbi_data_type_config_reg_for_line_21_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  tt_vbivpsl16e:4;
        RBus_UInt32  tt_vbivps16o:4;
        RBus_UInt32  tt_vbil26e:4;
        RBus_UInt32  tt_vbil26o:4;
        RBus_UInt32  tt_vbil25e:4;
        RBus_UInt32  tt_vbil25o:4;
    };
}tt_vbi_data_type_config_reg_for_line_25_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  tt_vbi_slicer_level_iir:9;
        RBus_UInt32  tt_vbi_vps_lpfil_gain:4;
        RBus_UInt32  tt_vbi_wss625_lpfil_gain:4;
        RBus_UInt32  tt_vbi_cc_lpfil_gain:4;
        RBus_UInt32  tt_vbi_tele_lpfil_gain:4;
    };
}tt_vbi_loop_filter_i_gain_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_teletext_dto:16;
        RBus_UInt32  tt_vbi_caption_dto:16;
    };
}tt_vbi_dto_register1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_dto:16;
        RBus_UInt32  tt_vbi_wss625_dto:16;
    };
}tt_vbi_dto_register2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_caption_frame_start:8;
        RBus_UInt32  tt_teletext_frame_start:8;
        RBus_UInt32  tt_wss625_frame_start:8;
        RBus_UInt32  tt_vps_frame_start:8;
    };
}tt_vbi_dto_frame_start_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_wssdata1:8;
        RBus_UInt32  tt_wssdata0:8;
        RBus_UInt32  tt_ccdata1:8;
        RBus_UInt32  tt_ccdata0:8;
    };
}tt_vbi_ccwss_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_data_field_ind:1;
        RBus_UInt32  tt_wss_int_en:1;
        RBus_UInt32  tt_cc_int_en:1;
        RBus_UInt32  tt_vps_int_en:1;
        RBus_UInt32  tt_tt_int_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  tt_int_clean:1;
        RBus_UInt32  wss_int_clean:1;
        RBus_UInt32  cc_int_clean:1;
        RBus_UInt32  vps_int_clean:1;
        RBus_UInt32  tt_tt_rdy:1;
        RBus_UInt32  tt_wss_rdy:1;
        RBus_UInt32  tt_cc_rdy:1;
        RBus_UInt32  tt_vps_rdy:1;
        RBus_UInt32  tt_vbi_noise_th:8;
        RBus_UInt32  tt_wssdata2:8;
    };
}tt_vbi_data_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_caption_start:8;
        RBus_UInt32  tt_vbi_teletext_start:8;
        RBus_UInt32  tt_vbi_wss625_start:8;
        RBus_UInt32  tt_vbi_vps_start:8;
    };
}tt_vbi_start_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  tt_vbi_wss_slice_level:9;
        RBus_UInt32  tt_vpsdata3:8;
    };
}tt_vps_data3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vpsdata2:32;
    };
}tt_vps_data2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vpsdata1:32;
    };
}tt_vps_data1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vpsdata0:32;
    };
}tt_vps_data0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_data_hold_cyc:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_vbi_fe_lpf_sel:2;
        RBus_UInt32  filter_gain_sel:2;
        RBus_UInt32  filter_coe_en:1;
        RBus_UInt32  tt_vbi_st_correlation_en:1;
        RBus_UInt32  tt_vbi_st_correlation_thl:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  filter_select_tap:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  filter_coe_modify:11;
    };
}tt_vbi_noisy_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_out_hcount_en:1;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_out_hcount_start_tt:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_out_hcount_end_tt:10;
    };
}tt_vbi_noisy_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_odd_par_err_byte_replace_en:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  tt_vbi_odd_par_err_byte_substitute_data:8;
        RBus_UInt32  res2:7;
        RBus_UInt32  tt_vbi_odd_parity_chk_en:1;
        RBus_UInt32  res3:5;
        RBus_UInt32  tt_vbi_noise_filter_sw:3;
    };
}tt_vbi_noisy_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_coch_auto_compensate_en:2;
        RBus_UInt32  res1:18;
        RBus_UInt32  tt_coch_tran_thl:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  tt_coch_noise_filter_sel:1;
    };
}tt_vbi_co_ch_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_clamp_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  tt_vbi_clamp_dc_level_sub:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  tt_vbi_clamp_dc_level_add:9;
        RBus_UInt32  tt_vbi_clamp_dgain:8;
    };
}tt_vbi_clampagc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_slice_lv_fix_start:8;
        RBus_UInt32  res1:3;
        RBus_UInt32  tt_vbi_slice_lv_fix_start_en:1;
        RBus_UInt32  tt_vbi_data_region_lpfil_gain:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  tt_vbi_data_region_phase_inv_disable:1;
        RBus_UInt32  tt_vbi_phase_inv_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  tt_vbi_pd_en2_err_fix_en:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  tt_vbi_resample_filter_sel:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  res6:1;
        RBus_UInt32  tt_vbi_pd_loop_filter_round_sel:2;
    };
}tt_vbi_noisy_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_slice_lv_fix_start_wss:8;
        RBus_UInt32  res1:10;
        RBus_UInt32  tt_vbi_pattern_sel:6;
        RBus_UInt32  tt_vbi_vps_pattern_set1:8;
    };
}tt_vbi_pattern_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_pattern_set2:32;
    };
}tt_vbi_pattern_sel1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_pattern_set3:32;
    };
}tt_vbi_pattern_sel2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_pattern_set4:32;
    };
}tt_vbi_pattern_sel3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_out_hcount_en_vps:1;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_out_hcount_start_vps:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_out_hcount_end_vps:10;
    };
}tt_vbi_noisy_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_out_hcount_en_wss:1;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_out_hcount_start_wss:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_out_hcount_end_wss:10;
    };
}tt_vbi_noisy_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  tt_vbi_st_correlation_en_vps:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  tt_vbi_st_correlation_thl_vps:10;
        RBus_UInt32  res3:3;
        RBus_UInt32  tt_vbi_st_correlation_en_wss:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  tt_vbi_st_correlation_thl_wss:10;
    };
}tt_vbi_noisy_ctrl6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_slice_data_en:1;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_select_line:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_hcount_st:10;
    };
}tt_vbi_status1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_slice_data_1:32;
    };
}tt_vbi_status2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_slice_data_0:32;
    };
}tt_vbi_status3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  tt_vbi_line_detect:20;
    };
}tt_vbi_status4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vbi_dump_rowdata_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vbi_dump_ttdata_en:1;
        RBus_UInt32  vbi_dump_line_num:24;
    };
}tt_vbi_dump_data1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vbi_dump_overhead:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  vbi_dump_tt_det:1;
        RBus_UInt32  vbi_dump_field_sel:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  vbi_dump_byte_num:10;
        RBus_UInt32  res4:2;
        RBus_UInt32  vbi_dump_hcount_st:10;
    };
}tt_vbi_dump_data2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  tt_vbi_odd_par_err_bit_correct_en:1;
        RBus_UInt32  tt_vbi_odd_par_dc:3;
        RBus_UInt32  tt_vbi_odd_parity_chk_th:4;
    };
}tt_vbi_odd_pariority_recovery_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  tt_vbi_odd_par_line_en:26;
    };
}tt_vbi_odd_pariority_recovery_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_agc_en:1;
        RBus_UInt32  tt_data_error_filter_sel:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_agc_comp_w_data:1;
        RBus_UInt32  tt_agc_line_start:8;
        RBus_UInt32  tt_agc_diff_th:8;
        RBus_UInt32  tt_agc_line_circle:12;
    };
}tt_vbi_agc_slice_level_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_data_error_ignor:8;
        RBus_UInt32  tt_data_error_count_dn:12;
        RBus_UInt32  tt_data_error_count_up:12;
    };
}tt_vbi_agc_slice_level1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  tt_vbi_slicer_level_agc:9;
        RBus_UInt32  res2:12;
        RBus_UInt32  tt_data_error_diff_rat:4;
    };
}tt_vbi_agc_slice_level2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_start_code_ignor_num:4;
        RBus_UInt32  wss_data_sel:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  vps_vote_en:1;
        RBus_UInt32  wss_vote_en:1;
        RBus_UInt32  vps_vote_thl:8;
        RBus_UInt32  wss_vote_thl:8;
        RBus_UInt32  vps_start_code_ignor_num:4;
        RBus_UInt32  wss_start_code_ignor_num:4;
    };
}tt_vbi_wss_vps_vote_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wss_vbi_clamp_en:1;
        RBus_UInt32  wss_vbi_clamp_filter:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  wss_vbi_clamp_dc_level_sub:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  wss_vbi_clamp_dc_level_add:9;
        RBus_UInt32  wss_vbi_clamp_dgain:8;
    };
}tt_vbi_wss_vps_vote2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  page6_en:1;
        RBus_UInt32  res1:11;
        RBus_UInt32  page6_lpfil_gain:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  page6_notrig_disable1:1;
        RBus_UInt32  page6_notrig_disable2:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  page6_sel_priority:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  page6_en_count:6;
    };
}tt_vbi_page6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_debug_mode_en:1;
        RBus_UInt32  res1:18;
        RBus_UInt32  vbi_data_err:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  pat_gen_en:1;
        RBus_UInt32  vbi_debug_mode:8;
    };
}vbi_debug_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test1:32;
    };
}vbi_fpga_test1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test2:32;
    };
}vbi_fpga_test2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test3:32;
    };
}vbi_fpga_test3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test4:32;
    };
}vbi_fpga_test4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test5:32;
    };
}vbi_fpga_test5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test6:32;
    };
}vbi_fpga_test6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test7:32;
    };
}vbi_fpga_test7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test8:32;
    };
}vbi_fpga_test8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vbi_dma_frame_addr:29;
    };
}vbi_dma_frame_addr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vbi_dma_frame_addr_end:29;
    };
}vbi_dma_frame_addr_end_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  vbi_dma_ctrl_ofifo_thr:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  vbi_dma_ctrl_ceiladr:6;
        RBus_UInt32  res3:5;
        RBus_UInt32  vbi_dma_ctrl_bstlen:3;
    };
}vbi_dma_fifo_staus_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  vbi_dma_ctrl_ofifo_err_flag:1;
        RBus_UInt32  vbi_dma_mem_off:1;
        RBus_UInt32  vbi_dma_test_mode:1;
        RBus_UInt32  res2:1;
    };
}vbi_dma_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  vbi_dma_vactive_st1:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  vbi_dma_vactive_end1:10;
    };
}vbi_dma_vactive1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  vbi_dma_vactive_st2:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  vbi_dma_vactive_end2:10;
    };
}vbi_dma_vactive2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  vbi_dump_overflow:1;
        RBus_UInt32  vbi_dump_irq_en:1;
        RBus_UInt32  vbi_dump_irq:1;
    };
}vbi_dump_int_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  sram_on_off:1;
    };
}bist_test1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_mode:1;
    };
}bist_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_done:1;
    };
}bist_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_fail:1;
    };
}bist_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_mode_drf:1;
    };
}bist_drf_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_drf_test_resume:1;
    };
}bist_drf_resume_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_done_drf:1;
    };
}bist_done_drf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_drf_start_pause:1;
    };
}bist_drf_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_fail_drf:1;
    };
}bist_fail_drf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  bist_ls:1;
        RBus_UInt32  bist_rmeb:1;
        RBus_UInt32  bist_rmb:4;
        RBus_UInt32  res2:3;
        RBus_UInt32  bist_rmea:1;
        RBus_UInt32  bist_rma:4;
    };
}bist_dvse_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  vbippr_lvld_tendl:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  vbippr_lvld_tstl:11;
    };
}vbi_ppr_lvld1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  vbippr_lvld_bendl:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  vbippr_lvld_bstl:11;
    };
}vbi_ppr_lvld2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  vbippr_data_acqu_en:1;
    };
}vbippr_ctrl_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pkt_rx_rst:1;
        RBus_UInt32  res1:15;
        RBus_UInt32  vbippr_pkt_rx_cnt:16;
    };
}vbippr_pkt_rx_cnt_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_sync_fifo_rd_count:16;
        RBus_UInt32  res1:7;
        RBus_UInt32  vbi_sync_fifo_rx_count_rst:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  vbippr_pg_mode:3;
        RBus_UInt32  res3:2;
        RBus_UInt32  vbippr_pgdebug_en:1;
        RBus_UInt32  vbippr_pg_en:1;
    };
}vbippr_pg_mode_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  vbippr_pg_line_act:1;
    };
}vbippr_pg_line_act_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata1:8;
        RBus_UInt32  vbippr_pgdata2:8;
        RBus_UInt32  vbippr_pgdata3:8;
        RBus_UInt32  vbippr_pgdata4:8;
    };
}vbippr_pgdata_b1b4_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata5:8;
        RBus_UInt32  vbippr_pgdata6:8;
        RBus_UInt32  vbippr_pgdata7:8;
        RBus_UInt32  vbippr_pgdata8:8;
    };
}vbippr_pgdata_b5b8_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata9:8;
        RBus_UInt32  vbippr_pgdata10:8;
        RBus_UInt32  vbippr_pgdata11:8;
        RBus_UInt32  vbippr_pgdata12:8;
    };
}vbippr_pgdata_b9b12_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata13:8;
        RBus_UInt32  vbippr_pgdata14:8;
        RBus_UInt32  vbippr_pgdata15:8;
        RBus_UInt32  vbippr_pgdata16:8;
    };
}vbippr_pgdata_b13b16_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata17:8;
        RBus_UInt32  vbippr_pgdata18:8;
        RBus_UInt32  vbippr_pgdata19:8;
        RBus_UInt32  vbippr_pgdata20:8;
    };
}vbippr_pgdata_b17b20_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata21:8;
        RBus_UInt32  vbippr_pgdata22:8;
        RBus_UInt32  vbippr_pgdata23:8;
        RBus_UInt32  vbippr_pgdata24:8;
    };
}vbippr_pgdata_b21b24_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata25:8;
        RBus_UInt32  vbippr_pgdata26:8;
        RBus_UInt32  vbippr_pgdata27:8;
        RBus_UInt32  vbippr_pgdata28:8;
    };
}vbippr_pgdata_b25b28_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata29:8;
        RBus_UInt32  vbippr_pgdata30:8;
        RBus_UInt32  vbippr_pgdata31:8;
        RBus_UInt32  vbippr_pgdata32:8;
    };
}vbippr_pgdata_b29b32_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata33:8;
        RBus_UInt32  vbippr_pgdata34:8;
        RBus_UInt32  vbippr_pgdata35:8;
        RBus_UInt32  vbippr_pgdata36:8;
    };
}vbippr_pgdata_b33b36_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata37:8;
        RBus_UInt32  vbippr_pgdata38:8;
        RBus_UInt32  vbippr_pgdata39:8;
        RBus_UInt32  vbippr_pgdata40:8;
    };
}vbippr_pgdata_b37b40_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata41:8;
        RBus_UInt32  vbippr_pgdata42:8;
        RBus_UInt32  vbippr_pgdata43:8;
        RBus_UInt32  vbippr_pgdata44:8;
    };
}vbippr_pgdata_b41b44_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata45:8;
        RBus_UInt32  vbippr_pgdata46:8;
        RBus_UInt32  vbippr_pgdata47:8;
        RBus_UInt32  res1:8;
    };
}vbippr_pgdata_b45b47_reg_RBUS;





#else //apply LITTLE_ENDIAN


//======VBI register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:4;
        RBus_UInt32  vbisl2_lcnt_field_inv:1;
        RBus_UInt32  vbisl0_fieldi_inv:1;
        RBus_UInt32  vbisl0_sys625i:1;
        RBus_UInt32  vbisl0_src_sel:1;
        RBus_UInt32  res1:18;
        RBus_UInt32  vbi_dma_stop_en:1;
        RBus_UInt32  vbi_dma_stop:1;
        RBus_UInt32  vbisl_out_mux_sel:2;
        RBus_UInt32  vbisl_out_auto_tt_vps_sel:1;
        RBus_UInt32  vbisl_out_mux_manual_en:1;
    };
}vbisl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_cc_blank_offset:16;
        RBus_UInt32  tt_vbi_cc_data_swing_gain:4;
        RBus_UInt32  res2:4;
        RBus_UInt32  tt_vbi_cc_vote_num:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_vbi_cc_vote_sel:1;
        RBus_UInt32  tt_vbi_cc_vote_en:1;
        RBus_UInt32  tt_vbi_cc_caposc_frun_en:1;
    };
}tt_vbi_cc_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:16;
        RBus_UInt32  tt_vbi_cc_st_correlation_thl:8;
        RBus_UInt32  tt_vbi_cc_st_correlation_en:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  find_start:1;
    };
}tt_vbi_cc_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_cc_out_hcount_end:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_cc_out_hcount_start:10;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_cc_out_hcount_en:1;
    };
}tt_vbi_cc_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  find_start_num:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  cc_pattern_field:1;
        RBus_UInt32  res1:23;
    };
}vbi_cc_pattern_compare_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cc_compare_data:32;
    };
}vbi_cc_pattern_compare_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_vount_shift_num:11;
        RBus_UInt32  res3:1;
        RBus_UInt32  vbi_vount_shift_field_inv:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vbi_vount_shift_en:1;
        RBus_UInt32  res1:15;
    };
}vbi_vount_shift_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cgms_c0_slicen:1;
        RBus_UInt32  cgms_c0_adap_slvl_en:1;
        RBus_UInt32  cgms_c0_slicer_ms:2;
        RBus_UInt32  cgms_c0_lpf_sel:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  cgms_c0_slicer_dcl:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  cgms_c0_debounce_sel:3;
        RBus_UInt32  res1:5;
    };
}cgms_c0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cgms_c1_actline_b:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  cgms_c1_actline_t:10;
        RBus_UInt32  res1:6;
    };
}cgms_c1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cgms_c2_dcdet_end:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  cgms_c2_dcdet_st:10;
        RBus_UInt32  res1:6;
    };
}cgms_c2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cgms_c3_lv_dc_th:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  cgms_period_cnt:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  cgms_auto_period_en:1;
        RBus_UInt32  res1:7;
    };
}cgms_c3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cgms_c4_cgmsdata:20;
        RBus_UInt32  res3:4;
        RBus_UInt32  cgms_c4_cgms_vld:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vbisl16_cgms_int_en:1;
        RBus_UInt32  res1:3;
    };
}cgms_c4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cgms_c5_period:8;
        RBus_UInt32  cgms_c5_max_period:8;
        RBus_UInt32  cgms_c5_min_period:8;
        RBus_UInt32  res1:8;
    };
}cgms_c5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata40:8;
        RBus_UInt32  tt_ttdata41:8;
        RBus_UInt32  res1:16;
    };
}tt_vbi_tt_data00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata36:8;
        RBus_UInt32  tt_ttdata37:8;
        RBus_UInt32  tt_ttdata38:8;
        RBus_UInt32  tt_ttdata39:8;
    };
}tt_vbi_tt_data01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata32:8;
        RBus_UInt32  tt_ttdata33:8;
        RBus_UInt32  tt_ttdata34:8;
        RBus_UInt32  tt_ttdata35:8;
    };
}tt_vbi_tt_data02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata28:8;
        RBus_UInt32  tt_ttdata29:8;
        RBus_UInt32  tt_ttdata30:8;
        RBus_UInt32  tt_ttdata31:8;
    };
}tt_vbi_tt_data03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata24:8;
        RBus_UInt32  tt_ttdata25:8;
        RBus_UInt32  tt_ttdata26:8;
        RBus_UInt32  tt_ttdata27:8;
    };
}tt_vbi_tt_data04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata20:8;
        RBus_UInt32  tt_ttdata21:8;
        RBus_UInt32  tt_ttdata22:8;
        RBus_UInt32  tt_ttdata23:8;
    };
}tt_vbi_tt_data05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata16:8;
        RBus_UInt32  tt_ttdata17:8;
        RBus_UInt32  tt_ttdata18:8;
        RBus_UInt32  tt_ttdata19:8;
    };
}tt_vbi_tt_data06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata12:8;
        RBus_UInt32  tt_ttdata13:8;
        RBus_UInt32  tt_ttdata14:8;
        RBus_UInt32  tt_ttdata15:8;
    };
}tt_vbi_tt_data07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata8:8;
        RBus_UInt32  tt_ttdata9:8;
        RBus_UInt32  tt_ttdata10:8;
        RBus_UInt32  tt_ttdata11:8;
    };
}tt_vbi_tt_data08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata4:8;
        RBus_UInt32  tt_ttdata5:8;
        RBus_UInt32  tt_ttdata6:8;
        RBus_UInt32  tt_ttdata7:8;
    };
}tt_vbi_tt_data09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ttdata0:8;
        RBus_UInt32  tt_ttdata1:8;
        RBus_UInt32  tt_ttdata2:8;
        RBus_UInt32  tt_ttdata3:8;
    };
}tt_vbi_tt_data10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_en:1;
        RBus_UInt32  tt_vbi_st_err_ignored:1;
        RBus_UInt32  tt_vbi_long_st_sel:1;
        RBus_UInt32  tt_vbi_hsyncout:1;
        RBus_UInt32  tt_vbi_muxout:1;
        RBus_UInt32  tt_adap_slvl_en:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_start_code:8;
        RBus_UInt32  tt_vbi_data_hlvl:8;
        RBus_UInt32  tt_vbi_data_hlvl_wss:8;
    };
}tt_vbi_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil5o:4;
        RBus_UInt32  tt_vbil5e:4;
        RBus_UInt32  tt_vbil6o:4;
        RBus_UInt32  tt_vbil6e:4;
        RBus_UInt32  tt_vbil7o:4;
        RBus_UInt32  tt_vbil7e:4;
        RBus_UInt32  tt_vbil8o:4;
        RBus_UInt32  tt_vbil8e:4;
    };
}tt_vbi_data_type_config_reg_for_line_5_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil9o:4;
        RBus_UInt32  tt_vbil9e:4;
        RBus_UInt32  tt_vbil10o:4;
        RBus_UInt32  tt_vbil10e:4;
        RBus_UInt32  tt_vbil11o:4;
        RBus_UInt32  tt_vbil11e:4;
        RBus_UInt32  tt_vbil12o:4;
        RBus_UInt32  tt_vbil12e:4;
    };
}tt_vbi_data_type_config_reg_for_line_9_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil13o:4;
        RBus_UInt32  tt_vbil13e:4;
        RBus_UInt32  tt_vbil14o:4;
        RBus_UInt32  tt_vbil14e:4;
        RBus_UInt32  tt_vbil15o:4;
        RBus_UInt32  tt_vbil15e:4;
        RBus_UInt32  tt_vbil16o:4;
        RBus_UInt32  tt_vbil16e:4;
    };
}tt_vbi_data_type_config_reg_for_line_13_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil17o:4;
        RBus_UInt32  tt_vbil17e:4;
        RBus_UInt32  tt_vbil18o:4;
        RBus_UInt32  tt_vbil18e:4;
        RBus_UInt32  tt_vbil19o:4;
        RBus_UInt32  tt_vbil19e:4;
        RBus_UInt32  tt_vbil20o:4;
        RBus_UInt32  tt_vbil20e:4;
    };
}tt_vbi_data_type_config_reg_for_line_17_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil21o:4;
        RBus_UInt32  tt_vbil21e:4;
        RBus_UInt32  tt_vbil22o:4;
        RBus_UInt32  tt_vbil22e:4;
        RBus_UInt32  tt_vbil23o:4;
        RBus_UInt32  tt_vbil23e:4;
        RBus_UInt32  tt_vbil24o:4;
        RBus_UInt32  tt_vbil24e:4;
    };
}tt_vbi_data_type_config_reg_for_line_21_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbil25o:4;
        RBus_UInt32  tt_vbil25e:4;
        RBus_UInt32  tt_vbil26o:4;
        RBus_UInt32  tt_vbil26e:4;
        RBus_UInt32  tt_vbivps16o:4;
        RBus_UInt32  tt_vbivpsl16e:4;
        RBus_UInt32  res1:8;
    };
}tt_vbi_data_type_config_reg_for_line_25_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_tele_lpfil_gain:4;
        RBus_UInt32  tt_vbi_cc_lpfil_gain:4;
        RBus_UInt32  tt_vbi_wss625_lpfil_gain:4;
        RBus_UInt32  tt_vbi_vps_lpfil_gain:4;
        RBus_UInt32  tt_vbi_slicer_level_iir:9;
        RBus_UInt32  res1:7;
    };
}tt_vbi_loop_filter_i_gain_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_caption_dto:16;
        RBus_UInt32  tt_vbi_teletext_dto:16;
    };
}tt_vbi_dto_register1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_wss625_dto:16;
        RBus_UInt32  tt_vbi_vps_dto:16;
    };
}tt_vbi_dto_register2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vps_frame_start:8;
        RBus_UInt32  tt_wss625_frame_start:8;
        RBus_UInt32  tt_teletext_frame_start:8;
        RBus_UInt32  tt_caption_frame_start:8;
    };
}tt_vbi_dto_frame_start_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_ccdata0:8;
        RBus_UInt32  tt_ccdata1:8;
        RBus_UInt32  tt_wssdata0:8;
        RBus_UInt32  tt_wssdata1:8;
    };
}tt_vbi_ccwss_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_wssdata2:8;
        RBus_UInt32  tt_vbi_noise_th:8;
        RBus_UInt32  tt_vps_rdy:1;
        RBus_UInt32  tt_cc_rdy:1;
        RBus_UInt32  tt_wss_rdy:1;
        RBus_UInt32  tt_tt_rdy:1;
        RBus_UInt32  vps_int_clean:1;
        RBus_UInt32  cc_int_clean:1;
        RBus_UInt32  wss_int_clean:1;
        RBus_UInt32  tt_int_clean:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  tt_tt_int_en:1;
        RBus_UInt32  tt_vps_int_en:1;
        RBus_UInt32  tt_cc_int_en:1;
        RBus_UInt32  tt_wss_int_en:1;
        RBus_UInt32  tt_data_field_ind:1;
    };
}tt_vbi_data_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_start:8;
        RBus_UInt32  tt_vbi_wss625_start:8;
        RBus_UInt32  tt_vbi_teletext_start:8;
        RBus_UInt32  tt_vbi_caption_start:8;
    };
}tt_vbi_start_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vpsdata3:8;
        RBus_UInt32  tt_vbi_wss_slice_level:9;
        RBus_UInt32  res1:15;
    };
}tt_vps_data3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vpsdata2:32;
    };
}tt_vps_data2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vpsdata1:32;
    };
}tt_vps_data1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vpsdata0:32;
    };
}tt_vps_data0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  filter_coe_modify:11;
        RBus_UInt32  res3:1;
        RBus_UInt32  filter_select_tap:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  tt_vbi_st_correlation_thl:8;
        RBus_UInt32  tt_vbi_st_correlation_en:1;
        RBus_UInt32  filter_coe_en:1;
        RBus_UInt32  filter_gain_sel:2;
        RBus_UInt32  tt_vbi_fe_lpf_sel:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_vbi_data_hold_cyc:1;
    };
}tt_vbi_noisy_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_out_hcount_end_tt:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_out_hcount_start_tt:10;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_out_hcount_en:1;
    };
}tt_vbi_noisy_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_noise_filter_sw:3;
        RBus_UInt32  res3:5;
        RBus_UInt32  tt_vbi_odd_parity_chk_en:1;
        RBus_UInt32  res2:7;
        RBus_UInt32  tt_vbi_odd_par_err_byte_substitute_data:8;
        RBus_UInt32  res1:7;
        RBus_UInt32  tt_vbi_odd_par_err_byte_replace_en:1;
    };
}tt_vbi_noisy_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_coch_noise_filter_sel:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  tt_coch_tran_thl:8;
        RBus_UInt32  res1:18;
        RBus_UInt32  tt_coch_auto_compensate_en:2;
    };
}tt_vbi_co_ch_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_clamp_dgain:8;
        RBus_UInt32  tt_vbi_clamp_dc_level_add:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  tt_vbi_clamp_dc_level_sub:9;
        RBus_UInt32  res1:2;
        RBus_UInt32  tt_vbi_clamp_en:1;
    };
}tt_vbi_clampagc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_pd_loop_filter_round_sel:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  tt_vbi_resample_filter_sel:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  tt_vbi_pd_en2_err_fix_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  tt_vbi_phase_inv_en:1;
        RBus_UInt32  tt_vbi_data_region_phase_inv_disable:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  tt_vbi_data_region_lpfil_gain:4;
        RBus_UInt32  tt_vbi_slice_lv_fix_start_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  tt_vbi_slice_lv_fix_start:8;
    };
}tt_vbi_noisy_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_pattern_set1:8;
        RBus_UInt32  tt_vbi_pattern_sel:6;
        RBus_UInt32  res1:10;
        RBus_UInt32  tt_vbi_slice_lv_fix_start_wss:8;
    };
}tt_vbi_pattern_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_pattern_set2:32;
    };
}tt_vbi_pattern_sel1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_pattern_set3:32;
    };
}tt_vbi_pattern_sel2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_vps_pattern_set4:32;
    };
}tt_vbi_pattern_sel3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_out_hcount_end_vps:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_out_hcount_start_vps:10;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_out_hcount_en_vps:1;
    };
}tt_vbi_noisy_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_out_hcount_end_wss:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_out_hcount_start_wss:10;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_out_hcount_en_wss:1;
    };
}tt_vbi_noisy_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_st_correlation_thl_wss:10;
        RBus_UInt32  res4:2;
        RBus_UInt32  tt_vbi_st_correlation_en_wss:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  tt_vbi_st_correlation_thl_vps:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  tt_vbi_st_correlation_en_vps:1;
        RBus_UInt32  res1:3;
    };
}tt_vbi_noisy_ctrl6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_hcount_st:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  tt_vbi_select_line:10;
        RBus_UInt32  res1:5;
        RBus_UInt32  tt_vbi_slice_data_en:1;
    };
}tt_vbi_status1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_slice_data_1:32;
    };
}tt_vbi_status2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_slice_data_0:32;
    };
}tt_vbi_status3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_line_detect:20;
        RBus_UInt32  res1:12;
    };
}tt_vbi_status4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dump_line_num:24;
        RBus_UInt32  vbi_dump_ttdata_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vbi_dump_rowdata_en:1;
        RBus_UInt32  res1:3;
    };
}tt_vbi_dump_data1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dump_hcount_st:10;
        RBus_UInt32  res4:2;
        RBus_UInt32  vbi_dump_byte_num:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  vbi_dump_field_sel:1;
        RBus_UInt32  vbi_dump_tt_det:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  vbi_dump_overhead:1;
        RBus_UInt32  res1:3;
    };
}tt_vbi_dump_data2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_odd_parity_chk_th:4;
        RBus_UInt32  tt_vbi_odd_par_dc:3;
        RBus_UInt32  tt_vbi_odd_par_err_bit_correct_en:1;
        RBus_UInt32  res1:24;
    };
}tt_vbi_odd_pariority_recovery_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_vbi_odd_par_line_en:26;
        RBus_UInt32  res1:6;
    };
}tt_vbi_odd_pariority_recovery_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_agc_line_circle:12;
        RBus_UInt32  tt_agc_diff_th:8;
        RBus_UInt32  tt_agc_line_start:8;
        RBus_UInt32  tt_agc_comp_w_data:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  tt_data_error_filter_sel:1;
        RBus_UInt32  tt_agc_en:1;
    };
}tt_vbi_agc_slice_level_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_data_error_count_up:12;
        RBus_UInt32  tt_data_error_count_dn:12;
        RBus_UInt32  tt_data_error_ignor:8;
    };
}tt_vbi_agc_slice_level1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tt_data_error_diff_rat:4;
        RBus_UInt32  res2:12;
        RBus_UInt32  tt_vbi_slicer_level_agc:9;
        RBus_UInt32  res1:7;
    };
}tt_vbi_agc_slice_level2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wss_start_code_ignor_num:4;
        RBus_UInt32  vps_start_code_ignor_num:4;
        RBus_UInt32  wss_vote_thl:8;
        RBus_UInt32  vps_vote_thl:8;
        RBus_UInt32  wss_vote_en:1;
        RBus_UInt32  vps_vote_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  wss_data_sel:1;
        RBus_UInt32  tt_start_code_ignor_num:4;
    };
}tt_vbi_wss_vps_vote_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wss_vbi_clamp_dgain:8;
        RBus_UInt32  wss_vbi_clamp_dc_level_add:9;
        RBus_UInt32  res2:3;
        RBus_UInt32  wss_vbi_clamp_dc_level_sub:9;
        RBus_UInt32  res1:1;
        RBus_UInt32  wss_vbi_clamp_filter:1;
        RBus_UInt32  wss_vbi_clamp_en:1;
    };
}tt_vbi_wss_vps_vote2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  page6_en_count:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  page6_sel_priority:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  page6_notrig_disable2:1;
        RBus_UInt32  page6_notrig_disable1:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  page6_lpfil_gain:4;
        RBus_UInt32  res1:11;
        RBus_UInt32  page6_en:1;
    };
}tt_vbi_page6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_debug_mode:8;
        RBus_UInt32  pat_gen_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vbi_data_err:1;
        RBus_UInt32  res1:18;
        RBus_UInt32  vbi_debug_mode_en:1;
    };
}vbi_debug_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test1:32;
    };
}vbi_fpga_test1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test2:32;
    };
}vbi_fpga_test2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test3:32;
    };
}vbi_fpga_test3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test4:32;
    };
}vbi_fpga_test4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test5:32;
    };
}vbi_fpga_test5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test6:32;
    };
}vbi_fpga_test6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test7:32;
    };
}vbi_fpga_test7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_fpga_test8:32;
    };
}vbi_fpga_test8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dma_frame_addr:29;
        RBus_UInt32  res1:3;
    };
}vbi_dma_frame_addr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dma_frame_addr_end:29;
        RBus_UInt32  res1:3;
    };
}vbi_dma_frame_addr_end_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dma_ctrl_bstlen:3;
        RBus_UInt32  res3:5;
        RBus_UInt32  vbi_dma_ctrl_ceiladr:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  vbi_dma_ctrl_ofifo_thr:6;
        RBus_UInt32  res1:10;
    };
}vbi_dma_fifo_staus_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:1;
        RBus_UInt32  vbi_dma_test_mode:1;
        RBus_UInt32  vbi_dma_mem_off:1;
        RBus_UInt32  vbi_dma_ctrl_ofifo_err_flag:1;
        RBus_UInt32  res1:28;
    };
}vbi_dma_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dma_vactive_end1:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  vbi_dma_vactive_st1:10;
        RBus_UInt32  res1:6;
    };
}vbi_dma_vactive1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dma_vactive_end2:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  vbi_dma_vactive_st2:10;
        RBus_UInt32  res1:6;
    };
}vbi_dma_vactive2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_dump_irq:1;
        RBus_UInt32  vbi_dump_irq_en:1;
        RBus_UInt32  vbi_dump_overflow:1;
        RBus_UInt32  res1:29;
    };
}vbi_dump_int_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sram_on_off:1;
        RBus_UInt32  res1:31;
    };
}bist_test1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mode:1;
        RBus_UInt32  res1:31;
    };
}bist_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_done:1;
        RBus_UInt32  res1:31;
    };
}bist_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail:1;
        RBus_UInt32  res1:31;
    };
}bist_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mode_drf:1;
        RBus_UInt32  res1:31;
    };
}bist_drf_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_test_resume:1;
        RBus_UInt32  res1:31;
    };
}bist_drf_resume_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_done_drf:1;
        RBus_UInt32  res1:31;
    };
}bist_done_drf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_start_pause:1;
        RBus_UInt32  res1:31;
    };
}bist_drf_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail_drf:1;
        RBus_UInt32  res1:31;
    };
}bist_fail_drf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_rma:4;
        RBus_UInt32  bist_rmea:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  bist_rmb:4;
        RBus_UInt32  bist_rmeb:1;
        RBus_UInt32  bist_ls:1;
        RBus_UInt32  res1:18;
    };
}bist_dvse_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_lvld_tstl:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  vbippr_lvld_tendl:11;
        RBus_UInt32  res1:5;
    };
}vbi_ppr_lvld1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_lvld_bstl:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  vbippr_lvld_bendl:11;
        RBus_UInt32  res1:5;
    };
}vbi_ppr_lvld2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_data_acqu_en:1;
        RBus_UInt32  res1:31;
    };
}vbippr_ctrl_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pkt_rx_cnt:16;
        RBus_UInt32  res1:15;
        RBus_UInt32  vbippr_pkt_rx_rst:1;
    };
}vbippr_pkt_rx_cnt_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pg_en:1;
        RBus_UInt32  vbippr_pgdebug_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  vbippr_pg_mode:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  vbi_sync_fifo_rx_count_rst:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  vbi_sync_fifo_rd_count:16;
    };
}vbippr_pg_mode_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pg_line_act:1;
        RBus_UInt32  res1:31;
    };
}vbippr_pg_line_act_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata4:8;
        RBus_UInt32  vbippr_pgdata3:8;
        RBus_UInt32  vbippr_pgdata2:8;
        RBus_UInt32  vbippr_pgdata1:8;
    };
}vbippr_pgdata_b1b4_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata8:8;
        RBus_UInt32  vbippr_pgdata7:8;
        RBus_UInt32  vbippr_pgdata6:8;
        RBus_UInt32  vbippr_pgdata5:8;
    };
}vbippr_pgdata_b5b8_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata12:8;
        RBus_UInt32  vbippr_pgdata11:8;
        RBus_UInt32  vbippr_pgdata10:8;
        RBus_UInt32  vbippr_pgdata9:8;
    };
}vbippr_pgdata_b9b12_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata16:8;
        RBus_UInt32  vbippr_pgdata15:8;
        RBus_UInt32  vbippr_pgdata14:8;
        RBus_UInt32  vbippr_pgdata13:8;
    };
}vbippr_pgdata_b13b16_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata20:8;
        RBus_UInt32  vbippr_pgdata19:8;
        RBus_UInt32  vbippr_pgdata18:8;
        RBus_UInt32  vbippr_pgdata17:8;
    };
}vbippr_pgdata_b17b20_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata24:8;
        RBus_UInt32  vbippr_pgdata23:8;
        RBus_UInt32  vbippr_pgdata22:8;
        RBus_UInt32  vbippr_pgdata21:8;
    };
}vbippr_pgdata_b21b24_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata28:8;
        RBus_UInt32  vbippr_pgdata27:8;
        RBus_UInt32  vbippr_pgdata26:8;
        RBus_UInt32  vbippr_pgdata25:8;
    };
}vbippr_pgdata_b25b28_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata32:8;
        RBus_UInt32  vbippr_pgdata31:8;
        RBus_UInt32  vbippr_pgdata30:8;
        RBus_UInt32  vbippr_pgdata29:8;
    };
}vbippr_pgdata_b29b32_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata36:8;
        RBus_UInt32  vbippr_pgdata35:8;
        RBus_UInt32  vbippr_pgdata34:8;
        RBus_UInt32  vbippr_pgdata33:8;
    };
}vbippr_pgdata_b33b36_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata40:8;
        RBus_UInt32  vbippr_pgdata39:8;
        RBus_UInt32  vbippr_pgdata38:8;
        RBus_UInt32  vbippr_pgdata37:8;
    };
}vbippr_pgdata_b37b40_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbippr_pgdata44:8;
        RBus_UInt32  vbippr_pgdata43:8;
        RBus_UInt32  vbippr_pgdata42:8;
        RBus_UInt32  vbippr_pgdata41:8;
    };
}vbippr_pgdata_b41b44_reg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  vbippr_pgdata47:8;
        RBus_UInt32  vbippr_pgdata46:8;
        RBus_UInt32  vbippr_pgdata45:8;
    };
}vbippr_pgdata_b45b47_reg_RBUS;


#endif







#endif //_RBUS_VBI_REG_H_

