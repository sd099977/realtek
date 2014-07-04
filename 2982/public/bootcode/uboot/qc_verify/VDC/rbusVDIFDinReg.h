/**
* @file rbusVDIFDinReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/23
* @version 802
* @ingroup model_rbus
*
*/

#ifndef _RBUS_DEFAULT_REG_H_
#define _RBUS_DEFAULT_REG_H_






// DEFAULT Register Address

#define FEin_INPUT_FLT_TAP_0_1_VADDR                  (0xb8004000)
#define FEin_INPUT_FLT_TAP_2_3_VADDR                  (0xb8004004)
#define FEin_INPUT_FLT_TAP_4_5_VADDR                  (0xb8004008)
#define FEin_INPUT_FLT_TAP_6_7_VADDR                  (0xb800400c)
#define FEin_INPUT_FLT_TAP_8_9_VADDR                  (0xb8004010)
#define FEin_INPUT_FLT_TAP_10_11_VADDR                (0xb8004014)
#define FEin_INPUT_FLT_TAP_12_13_VADDR                (0xb8004018)
#define FEin_INPUT_FLT_TAP_14_15_VADDR                (0xb800401c)
#define FEin_INPUT_FLT_TAP_16_17_VADDR                (0xb8004020)
#define FEin_INPUT_FLT_TAP_18_19_VADDR                (0xb8004024)
#define FEin_INPUT_FLT_TAP_20_21_VADDR                (0xb8004028)
#define FEin_INPUT_FLT_TAP_22_23_VADDR                (0xb800402c)
#define FEin_INPUT_FLT_TAP_24_25_VADDR                (0xb8004030)
#define FEin_INPUT_FLT_TAP_26_27_VADDR                (0xb8004034)
#define FEin_INPUT_FLT_TAP_28_29_VADDR                (0xb8004038)
#define FEin_INPUT_FLT_TAP_30_31_VADDR                (0xb800403c)
#define FEin_INPUT_FLT_TAP_32_33_VADDR                (0xb8004040)
#define FEin_INPUT_FLT_TAP_34_35_VADDR                (0xb8004044)
#define FEin_INPUT_FLT_TAP_36_37_VADDR                (0xb8004048)
#define FEin_INPUT_FLT_TAP_38_39_VADDR                (0xb800404c)
#define FEin_INPUT_FLT_TAP_40_41_VADDR                (0xb8004050)
#define FEin_INPUT_FLT_TAP_42_43_VADDR                (0xb8004054)
#define FEin_INPUT_FLT_TAP_44_45_VADDR                (0xb8004058)
#define FEin_INPUT_FLT_TAP_46_47_VADDR                (0xb800405c)
#define FEin_INPUT_FLT_TAP_48_49_VADDR                (0xb8004060)
#define FEin_INPUT_FLT_TAP_50_51_VADDR                (0xb8004064)
#define FEin_INPUT_FLT_TAP_52_53_VADDR                (0xb8004068)
#define FEin_INPUT_FLT_TAP_54_55_VADDR                (0xb800406c)
#define FEin_INPUT_FLT_TAP_56_57_VADDR                (0xb8004070)
#define FEin_INPUT_FLT_TAP_58_59_VADDR                (0xb8004074)
#define FEin_INPUT_FLT_TAP_60_61_VADDR                (0xb8004078)
#define FEin_INPUT_FLT_TAP_62_63_VADDR                (0xb800407c)
#define FEin_INPUT_FLT_TAP_64_65_VADDR                (0xb8004080)
#define FEin_INPUT_FLT_TAP_66_67_VADDR                (0xb8004084)
#define FEin_INPUT_FLT_TAP_68_69_VADDR                (0xb8004088)
#define FEin_INPUT_FLT_TAP_70_71_VADDR                (0xb800408c)
#define FEin_INPUT_FLT_EN_VADDR                       (0xb8004090)
#define FEin_INPUT_FILTER_SET_VADDR                   (0xb8004094)
#define FEin_IFD_ADC_CLK_POLAR_VADDR                  (0xb8004098)
#define FEin_IFD_CP_TEST_ENABLE_VADDR                 (0xb800409c)
#define FEin_VD_IN_DELAY_SEL1_VADDR                   (0xb80040a0)
#define FEin_VD_IN_DELAY_SEL2_VADDR                   (0xb80040a4)
#define FEin_VD_ADC_LSB_CTRL_VADDR                    (0xb80040a8)
#define FEin_VD_INOUT_CTRL_VADDR                      (0xb80040ac)
#define FEin_CRC_EN_VADDR                             (0xb80040b0)
#define FEin_CRC_108MHZ_RESULT1_VADDR                 (0xb80040b4)
#define FEin_CRC_108MHZ_RESULT2_VADDR                 (0xb80040b8)
#define FEin_INPUT_DEBUG_VADDR                        (0xb80040bc)
#define FEin_IF_PATTERNGEN_VADDR                      (0xb80040c0)
#define FEin_IFD_INPUT_FIFO_STATUS_VADDR              (0xb80040d0)
#define FEin_VD_INPUT_FIFO_STATUS1_VADDR              (0xb80040d4)
#define FEin_VD_INPUT_FIFO_STATUS2_VADDR              (0xb80040d8)
#define FEin_IFD_INPUT_FIFO_STATUS3_VADDR             (0xb80040dc)
#define FEin_IFD_FIFO_CRC_VADDR                       (0xb80040e0)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======DEFAULT register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap0:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap1:13;
    };
}input_flt_tap_0_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap2:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap3:13;
    };
}input_flt_tap_2_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap4:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap5:13;
    };
}input_flt_tap_4_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap6:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap7:13;
    };
}input_flt_tap_6_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap8:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap9:13;
    };
}input_flt_tap_8_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap10:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap11:13;
    };
}input_flt_tap_10_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap12:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap13:13;
    };
}input_flt_tap_12_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap14:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap15:13;
    };
}input_flt_tap_14_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap16:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap17:13;
    };
}input_flt_tap_16_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap18:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap19:13;
    };
}input_flt_tap_18_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap20:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap21:13;
    };
}input_flt_tap_20_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap22:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap23:13;
    };
}input_flt_tap_22_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap24:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap25:13;
    };
}input_flt_tap_24_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap26:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap27:13;
    };
}input_flt_tap_26_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap28:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap29:13;
    };
}input_flt_tap_28_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap30:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap31:13;
    };
}input_flt_tap_30_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap32:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap33:13;
    };
}input_flt_tap_32_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap34:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap35:13;
    };
}input_flt_tap_34_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap36:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap37:13;
    };
}input_flt_tap_36_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap38:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap39:13;
    };
}input_flt_tap_38_39_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap40:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap41:13;
    };
}input_flt_tap_40_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap42:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap43:13;
    };
}input_flt_tap_42_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap44:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap45:13;
    };
}input_flt_tap_44_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap46:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap47:13;
    };
}input_flt_tap_46_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap48:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap49:13;
    };
}input_flt_tap_48_49_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap50:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap51:13;
    };
}input_flt_tap_50_51_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap52:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap53:13;
    };
}input_flt_tap_52_53_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap54:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap55:13;
    };
}input_flt_tap_54_55_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap56:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap57:13;
    };
}input_flt_tap_56_57_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap58:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap59:13;
    };
}input_flt_tap_58_59_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap60:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap61:13;
    };
}input_flt_tap_60_61_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap62:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap63:13;
    };
}input_flt_tap_62_63_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap64:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap65:13;
    };
}input_flt_tap_64_65_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap66:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap67:13;
    };
}input_flt_tap_66_67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap68:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap69:13;
    };
}input_flt_tap_68_69_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  input_flt_tap70:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap71:13;
    };
}input_flt_tap_70_71_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  input_flt_en:1;
    };
}input_flt_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  adc_fifo_in_sel:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  adc_clk_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  input_dn_filter_sel:3;
    };
}input_filter_set_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  ls_adcclk_polar:1;
        RBus_UInt32  clk54_polar:1;
    };
}IFD_ADC_CLK_POLAR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  cp_test_enable:1;
    };
}IFD_cp_test_enable_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ad4_input_delay:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  ad3_input_delay:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  ad2_input_delay:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  ad1_input_delay:5;
    };
}VD_IN_DELAY_SEL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cvbs_tve_mux:1;
        RBus_UInt32  res1:18;
        RBus_UInt32  ad5_input_delay:5;
        RBus_UInt32  res2:4;
        RBus_UInt32  sv_sel:2;
        RBus_UInt32  sv_yc_switch:1;
        RBus_UInt32  sv_in_one_adc:1;
    };
}VD_IN_DELAY_SEL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  scart_input_delay_108:4;
        RBus_UInt32  yppb_input_delay_108:4;
        RBus_UInt32  yppg_input_delay_108:4;
        RBus_UInt32  yppr_input_delay_108:4;
        RBus_UInt32  vdadc_input_delay_108:4;
        RBus_UInt32  adc3_lsb_force0_num:2;
        RBus_UInt32  adc2_lsb_force0_num:2;
        RBus_UInt32  adc1_lsb_force0_num:2;
        RBus_UInt32  adc0_lsb_force0_num:2;
    };
}VD_ADC_LSB_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  fe_fil_sel:3;
        RBus_UInt32  res2:3;
        RBus_UInt32  adc27_mod:1;
    };
}VD_INOUT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  crc_108mhz_en:1;
    };
}CRC_EN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_108mhz_result_1:32;
    };
}CRC_108MHZ_RESULT1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_108mhz_result_2:32;
    };
}CRC_108MHZ_RESULT2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  input_debug_sel:2;
    };
}INPUT_DEBUG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  if_patterngen_nco:16;
        RBus_UInt32  res2:2;
        RBus_UInt32  if_patterngen_mod_sel:1;
        RBus_UInt32  if_patterngen_en:1;
    };
}IF_PATTERNGEN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  input_fifo_pg_full_clr:1;
        RBus_UInt32  input_fifo_pg_empty_clr:1;
        RBus_UInt32  input_fifo_pg_clr:1;
        RBus_UInt32  input_fifo_pg_full:1;
        RBus_UInt32  input_fifo_pg_empty:1;
        RBus_UInt32  res2:11;
        RBus_UInt32  input_fifo_full_clr:1;
        RBus_UInt32  input_fifo_empty_clr:1;
        RBus_UInt32  input_fifo_clr:1;
        RBus_UInt32  input_fifo_full:1;
        RBus_UInt32  input_fifo_empty:1;
    };
}IFD_INPUT_FIFO_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ad_debug_full:1;
        RBus_UInt32  ad_debug_empty:1;
        RBus_UInt32  ad5_fifo_full:1;
        RBus_UInt32  ad5_fifo_empty:1;
        RBus_UInt32  adc_sync_fifo_clr:1;
        RBus_UInt32  vdadc_sync_fifo_full:1;
        RBus_UInt32  vdadc_sync_fifo_empty:1;
        RBus_UInt32  ypp_blu_sync_fifo_full:1;
        RBus_UInt32  ypp_blu_sync_fifo_empty:1;
        RBus_UInt32  ypp_grn_sync_fifo_full:1;
        RBus_UInt32  ypp_grn_sync_fifo_empty:1;
        RBus_UInt32  ypp_red_sync_fifo_full:1;
        RBus_UInt32  ypp_red_sync_fifo_empty:1;
        RBus_UInt32  scart_sync_fifo_full:1;
        RBus_UInt32  scart_sync_fifo_empty:1;
        RBus_UInt32  ycref_sync_fifo_full:1;
        RBus_UInt32  ycref_sync_fifo_empty:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vd_fifo_clr:1;
        RBus_UInt32  ad1_fifo_full:1;
        RBus_UInt32  ad1_fifo_empty:1;
        RBus_UInt32  ad2_fifo_full:1;
        RBus_UInt32  ad2_fifo_empty:1;
        RBus_UInt32  ad3_fifo_full:1;
        RBus_UInt32  ad3_fifo_empty:1;
        RBus_UInt32  ad4_fifo_full:1;
        RBus_UInt32  ad4_fifo_empty:1;
    };
}VD_INPUT_FIFO_STATUS1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  ad_debug_full_clr:1;
        RBus_UInt32  ad_debug_empty_clr:1;
        RBus_UInt32  ad5_fifo_full_clr:1;
        RBus_UInt32  ad5_fifo_empty_clr:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  vdadc_sync_fifo_full_clr:1;
        RBus_UInt32  vdadc_sync_fifo_empty_clr:1;
        RBus_UInt32  ypp_blu_sync_fifo_full_clr:1;
        RBus_UInt32  ypp_blu_sync_fifo_empty_clr:1;
        RBus_UInt32  ypp_grn_sync_fifo_full_clr:1;
        RBus_UInt32  ypp_grn_sync_fifo_empty_clr:1;
        RBus_UInt32  ypp_red_sync_fifo_full_clr:1;
        RBus_UInt32  ypp_red_sync_fifo_empty_clr:1;
        RBus_UInt32  scart_sync_fifo_full_clr:1;
        RBus_UInt32  scart_sync_fifo_empty_clr:1;
        RBus_UInt32  ycref_sync_fifo_full_clr:1;
        RBus_UInt32  ycref_sync_fifo_empty_clr:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  ad1_fifo_full_clr:1;
        RBus_UInt32  ad1_fifo_empty_clr:1;
        RBus_UInt32  ad2_fifo_full_clr:1;
        RBus_UInt32  ad2_fifo_empty_clr:1;
        RBus_UInt32  ad3_fifo_full_clr:1;
        RBus_UInt32  ad3_fifo_empty_clr:1;
        RBus_UInt32  ad4_fifo_full_clr:1;
        RBus_UInt32  ad4_fifo_empty_clr:1;
    };
}VD_INPUT_FIFO_STATUS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  fifo_recover_depth:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  fifo_recover_thr:3;
        RBus_UInt32  res3:3;
        RBus_UInt32  fifo_recover_en:1;
    };
}IFD_INPUT_FIFO_STATUS3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  fifo_crc_en:1;
    };
}IFD_FIFO_CRC_RBUS;





#else //apply LITTLE_ENDIAN


//======DEFAULT register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap1:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap0:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_0_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap3:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap2:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_2_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap5:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap4:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_4_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap7:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap6:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_6_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap9:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap8:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_8_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap11:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap10:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_10_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap13:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap12:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_12_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap15:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap14:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_14_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap17:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap16:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_16_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap19:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap18:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_18_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap21:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap20:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_20_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap23:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap22:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_22_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap25:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap24:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_24_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap27:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap26:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_26_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap29:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap28:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_28_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap31:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap30:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_30_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap33:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap32:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_32_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap35:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap34:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_34_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap37:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap36:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_36_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap39:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap38:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_38_39_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap41:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap40:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_40_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap43:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap42:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_42_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap45:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap44:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_44_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap47:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap46:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_46_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap49:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap48:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_48_49_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap51:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap50:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_50_51_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap53:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap52:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_52_53_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap55:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap54:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_54_55_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap57:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap56:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_56_57_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap59:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap58:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_58_59_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap61:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap60:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_60_61_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap63:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap62:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_62_63_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap65:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap64:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_64_65_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap67:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap66:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_66_67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap69:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap68:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_68_69_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_tap71:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  input_flt_tap70:13;
        RBus_UInt32  res1:3;
    };
}input_flt_tap_70_71_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_flt_en:1;
        RBus_UInt32  res1:31;
    };
}input_flt_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_dn_filter_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  adc_clk_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  adc_fifo_in_sel:1;
        RBus_UInt32  res1:23;
    };
}input_filter_set_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clk54_polar:1;
        RBus_UInt32  ls_adcclk_polar:1;
        RBus_UInt32  res1:30;
    };
}IFD_ADC_CLK_POLAR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cp_test_enable:1;
        RBus_UInt32  res1:31;
    };
}IFD_cp_test_enable_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad1_input_delay:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  ad2_input_delay:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  ad3_input_delay:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  ad4_input_delay:5;
        RBus_UInt32  res1:3;
    };
}VD_IN_DELAY_SEL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sv_in_one_adc:1;
        RBus_UInt32  sv_yc_switch:1;
        RBus_UInt32  sv_sel:2;
        RBus_UInt32  res2:4;
        RBus_UInt32  ad5_input_delay:5;
        RBus_UInt32  res1:18;
        RBus_UInt32  cvbs_tve_mux:1;
    };
}VD_IN_DELAY_SEL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc0_lsb_force0_num:2;
        RBus_UInt32  adc1_lsb_force0_num:2;
        RBus_UInt32  adc2_lsb_force0_num:2;
        RBus_UInt32  adc3_lsb_force0_num:2;
        RBus_UInt32  vdadc_input_delay_108:4;
        RBus_UInt32  yppr_input_delay_108:4;
        RBus_UInt32  yppg_input_delay_108:4;
        RBus_UInt32  yppb_input_delay_108:4;
        RBus_UInt32  scart_input_delay_108:4;
        RBus_UInt32  res1:4;
    };
}VD_ADC_LSB_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc27_mod:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  fe_fil_sel:3;
        RBus_UInt32  res1:25;
    };
}VD_INOUT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_108mhz_en:1;
        RBus_UInt32  res1:31;
    };
}CRC_EN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_108mhz_result_1:32;
    };
}CRC_108MHZ_RESULT1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_108mhz_result_2:32;
    };
}CRC_108MHZ_RESULT2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_debug_sel:2;
        RBus_UInt32  res1:30;
    };
}INPUT_DEBUG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  if_patterngen_en:1;
        RBus_UInt32  if_patterngen_mod_sel:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  if_patterngen_nco:16;
        RBus_UInt32  res1:12;
    };
}IF_PATTERNGEN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  input_fifo_empty:1;
        RBus_UInt32  input_fifo_full:1;
        RBus_UInt32  input_fifo_clr:1;
        RBus_UInt32  input_fifo_empty_clr:1;
        RBus_UInt32  input_fifo_full_clr:1;
        RBus_UInt32  res2:11;
        RBus_UInt32  input_fifo_pg_empty:1;
        RBus_UInt32  input_fifo_pg_full:1;
        RBus_UInt32  input_fifo_pg_clr:1;
        RBus_UInt32  input_fifo_pg_empty_clr:1;
        RBus_UInt32  input_fifo_pg_full_clr:1;
        RBus_UInt32  res1:11;
    };
}IFD_INPUT_FIFO_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad4_fifo_empty:1;
        RBus_UInt32  ad4_fifo_full:1;
        RBus_UInt32  ad3_fifo_empty:1;
        RBus_UInt32  ad3_fifo_full:1;
        RBus_UInt32  ad2_fifo_empty:1;
        RBus_UInt32  ad2_fifo_full:1;
        RBus_UInt32  ad1_fifo_empty:1;
        RBus_UInt32  ad1_fifo_full:1;
        RBus_UInt32  vd_fifo_clr:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  ycref_sync_fifo_empty:1;
        RBus_UInt32  ycref_sync_fifo_full:1;
        RBus_UInt32  scart_sync_fifo_empty:1;
        RBus_UInt32  scart_sync_fifo_full:1;
        RBus_UInt32  ypp_red_sync_fifo_empty:1;
        RBus_UInt32  ypp_red_sync_fifo_full:1;
        RBus_UInt32  ypp_grn_sync_fifo_empty:1;
        RBus_UInt32  ypp_grn_sync_fifo_full:1;
        RBus_UInt32  ypp_blu_sync_fifo_empty:1;
        RBus_UInt32  ypp_blu_sync_fifo_full:1;
        RBus_UInt32  vdadc_sync_fifo_empty:1;
        RBus_UInt32  vdadc_sync_fifo_full:1;
        RBus_UInt32  adc_sync_fifo_clr:1;
        RBus_UInt32  ad5_fifo_empty:1;
        RBus_UInt32  ad5_fifo_full:1;
        RBus_UInt32  ad_debug_empty:1;
        RBus_UInt32  ad_debug_full:1;
        RBus_UInt32  res1:3;
    };
}VD_INPUT_FIFO_STATUS1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad4_fifo_empty_clr:1;
        RBus_UInt32  ad4_fifo_full_clr:1;
        RBus_UInt32  ad3_fifo_empty_clr:1;
        RBus_UInt32  ad3_fifo_full_clr:1;
        RBus_UInt32  ad2_fifo_empty_clr:1;
        RBus_UInt32  ad2_fifo_full_clr:1;
        RBus_UInt32  ad1_fifo_empty_clr:1;
        RBus_UInt32  ad1_fifo_full_clr:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  ycref_sync_fifo_empty_clr:1;
        RBus_UInt32  ycref_sync_fifo_full_clr:1;
        RBus_UInt32  scart_sync_fifo_empty_clr:1;
        RBus_UInt32  scart_sync_fifo_full_clr:1;
        RBus_UInt32  ypp_red_sync_fifo_empty_clr:1;
        RBus_UInt32  ypp_red_sync_fifo_full_clr:1;
        RBus_UInt32  ypp_grn_sync_fifo_empty_clr:1;
        RBus_UInt32  ypp_grn_sync_fifo_full_clr:1;
        RBus_UInt32  ypp_blu_sync_fifo_empty_clr:1;
        RBus_UInt32  ypp_blu_sync_fifo_full_clr:1;
        RBus_UInt32  vdadc_sync_fifo_empty_clr:1;
        RBus_UInt32  vdadc_sync_fifo_full_clr:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ad5_fifo_empty_clr:1;
        RBus_UInt32  ad5_fifo_full_clr:1;
        RBus_UInt32  ad_debug_empty_clr:1;
        RBus_UInt32  ad_debug_full_clr:1;
        RBus_UInt32  res1:3;
    };
}VD_INPUT_FIFO_STATUS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_recover_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  fifo_recover_thr:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  fifo_recover_depth:2;
        RBus_UInt32  res1:22;
    };
}IFD_INPUT_FIFO_STATUS3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_crc_en:1;
        RBus_UInt32  res1:31;
    };
}IFD_FIFO_CRC_RBUS;


#endif







#endif //_RBUS_FEin_REG_H_

