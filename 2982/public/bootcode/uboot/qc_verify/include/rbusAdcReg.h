/**
* @file rbusAdcReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/30
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_ADC_REG_H_
#define _RBUS_ADC_REG_H_

#include "rbusTypes.h"




// ADC Register Address

#define ADC_ADC_POWER_VADDR                        (0xb8020000)
#define ADC_ADC_IBIAS0123_VADDR                    (0xb8020004)
#define ADC_ADC_CTL_RGB12_VADDR                    (0xb8020008)
#define ADC_ADC_VBIAS_VADDR                        (0xb802000c)
#define ADC_ADC_CLOCK_VADDR                        (0xb8020010)
#define ADC_ADC_CTL_RESERVED_VADDR                 (0xb8020014)
#define ADC_ADC_DCRESTORE_CTRL_VADDR               (0xb8020018)
#define ADC_ADC_CLAMP_CTRL0_VADDR                  (0xb802001c)
#define ADC_ADC_CLAMP_CTRL1_VADDR                  (0xb8020020)
#define ADC_ADC_CLAMP_CTRL2_VADDR                  (0xb8020024)
#define ADC_ADC_CLAMP_CTRL3_VADDR                  (0xb8020028)
#define ADC_ADC_IBIAS4_VADDR                       (0xb802002c)
#define ADC_ADC_GAIN0_VADDR                        (0xb8020030)
#define ADC_ADC_GAIN1_VADDR                        (0xb8020034)
#define ADC_ADC_OFFSET0_VADDR                      (0xb8020038)
#define ADC_ADC_OFFSET1_VADDR                      (0xb802003c)
#define ADC_ADC_CTL_1_VADDR                        (0xb8020040)
#define ADC_ADC_CTL_2_VADDR                        (0xb8020044)
#define ADC_VD_ADC_CLAMP_CTL_1_VADDR               (0xb8020048)
#define ADC_VD_ADC_CLAMP_CTL_2_VADDR               (0xb802004c)
#define ADC_VD_ADC_UPDN_CTL_VADDR                  (0xb8020050)
#define ADC_VDADC_CORE_LPF_CTRL_VADDR              (0xb8020054)
#define ADC_VDADC_CK_CTL_VADDR                     (0xb8020058)
#define ADC_VDADC_POW_CTL_VADDR                    (0xb802005c)
#define ADC_VD_SCT_VADDR                           (0xb8020060)
#define ADC_AHS_SMT_CTRL_VADDR                     (0xb8020064)
#define ADC_ADC_TEST_VADDR                         (0xb8020068)
#define ADC_SCART_CTRL1_VADDR                      (0xb802006c)
#define ADC_ADC_CLKGEN_RGB_CAPTURE_VADDR           (0xb8020080)
#define ADC_ADC_APLL_ADC_TESTOUT_MUX_VADDR         (0xb8020084)
#define ADC_ADC_RGB_DATA_VADDR                     (0xb8020088)
#define ADC_ADC_RGB_DATA2_VADDR                    (0xb802008c)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======ADC register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18020000_31_16:16;
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_power_9:1;
        RBus_UInt32  adc_power_8:1;
        RBus_UInt32  adc_power_7:1;
        RBus_UInt32  adc_power_6:1;
        RBus_UInt32  adc_power_5:1;
        RBus_UInt32  adc_power_4:1;
        RBus_UInt32  adc_power_3:1;
        RBus_UInt32  adc_power_2:1;
        RBus_UInt32  adc_power_1:1;
        RBus_UInt32  adc_power_0:1;
    };
}adc_power_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  adc_ibias1_7:1;
        RBus_UInt32  adc_ibias1_6:1;
        RBus_UInt32  adc_ibias1_5_1:5;
        RBus_UInt32  adc_ibias1_0:1;
        RBus_UInt32  adc_ibias0:8;
    };
}adc_ibias0123_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  adc_ctl_rgb2_11_10:2;
        RBus_UInt32  adc_ctl_rgb2_9:1;
        RBus_UInt32  adc_ctl_rgb2_8:1;
        RBus_UInt32  adc_ctl_rgb2_7:1;
        RBus_UInt32  adc_ctl_rgb2_6:1;
        RBus_UInt32  adc_ctl_rgb2_5_4:2;
        RBus_UInt32  adc_ctl_rgb2_3_2:2;
        RBus_UInt32  adc_ctl_rgb2_1_0:2;
        RBus_UInt32  res2:4;
        RBus_UInt32  adc_ctl_rgb1_11_10:2;
        RBus_UInt32  adc_ctl_rgb1_9:1;
        RBus_UInt32  adc_ctl_rgb1_8:1;
        RBus_UInt32  adc_ctl_rgb1_7:1;
        RBus_UInt32  adc_ctl_rgb1_6:1;
        RBus_UInt32  adc_ctl_rgb1_5_4:2;
        RBus_UInt32  adc_ctl_rgb1_3_2:2;
        RBus_UInt32  adc_ctl_rgb1_1_0:2;
    };
}adc_ctl_rgb12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_vbias3_7:1;
        RBus_UInt32  adc_vbias3_6:1;
        RBus_UInt32  adc_vbias3_5:1;
        RBus_UInt32  adc_vbias3_4:1;
        RBus_UInt32  adc_vbias3_3:1;
        RBus_UInt32  adc_vbias3_2:1;
        RBus_UInt32  adc_vbias3_1_0:2;
        RBus_UInt32  adc_vbias2_7:1;
        RBus_UInt32  adc_vbias2_6:1;
        RBus_UInt32  adc_vbias2_5:1;
        RBus_UInt32  adc_vbias2_4:1;
        RBus_UInt32  adc_vbias2_3:1;
        RBus_UInt32  adc_vbias2_2_0:3;
        RBus_UInt32  adc_vbias1_7_3:5;
        RBus_UInt32  adc_vbias1_2_0:3;
        RBus_UInt32  adc_vbias0_7_4:4;
        RBus_UInt32  adc_vbias0_3_2:2;
        RBus_UInt32  adc_vbias0_1:1;
        RBus_UInt32  adc_vbias0_0:1;
    };
}adc_vbias_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  adc_2x_sample_7:1;
        RBus_UInt32  adc_2x_sample_6:1;
        RBus_UInt32  adc_2x_sample_5:1;
        RBus_UInt32  adc_2x_sample_4_3:2;
        RBus_UInt32  adc_2x_sample_2:1;
        RBus_UInt32  adc_2x_sample_1:1;
        RBus_UInt32  adc_2x_sample_0:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  adc_clock_11:1;
        RBus_UInt32  adc_clock_10:1;
        RBus_UInt32  adc_clock_9_8:2;
        RBus_UInt32  adc_clock_7:1;
        RBus_UInt32  adc_clock_6:1;
        RBus_UInt32  adc_clock_5_4:2;
        RBus_UInt32  adc_clock_3:1;
        RBus_UInt32  adc_clock_2:1;
        RBus_UInt32  adc_clock_1_0:2;
    };
}adc_clock_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}adc_ctl_reserved_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  adc_ctl_rgb_7:1;
        RBus_UInt32  adc_ctl_rgb_6:1;
        RBus_UInt32  adc_ctl_rgb_5:1;
        RBus_UInt32  adc_ctl_rgb_4:1;
        RBus_UInt32  adc_ctl_rgb_3_0:4;
        RBus_UInt32  res2:7;
        RBus_UInt32  adc_dcrestore_ctrl:9;
    };
}adc_dcrestore_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  adc_clamp_ctrl2_11:1;
        RBus_UInt32  adc_clamp_ctrl2_10:1;
        RBus_UInt32  adc_clamp_ctrl2_9_8:2;
        RBus_UInt32  adc_clamp_ctrl2_7_6:2;
        RBus_UInt32  adc_clamp_ctrl2_5:1;
        RBus_UInt32  adc_clamp_ctrl2_4:1;
        RBus_UInt32  adc_clamp_ctrl2_3:1;
        RBus_UInt32  adc_clamp_ctrl2_2:1;
        RBus_UInt32  adc_clamp_ctrl2_1:1;
        RBus_UInt32  adc_clamp_ctrl2_0:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  res3:3;
        RBus_UInt32  adc_clamp_ctrl1_8:1;
        RBus_UInt32  adc_clamp_ctrl1_7_6:2;
        RBus_UInt32  adc_clamp_ctrl1_5:1;
        RBus_UInt32  adc_clamp_ctrl1_4_3:2;
        RBus_UInt32  adc_clamp_ctrl1_2:1;
        RBus_UInt32  adc_clamp_ctrl1_1_0:2;
    };
}adc_clamp_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  adc_clamp_ctrl4_7:1;
        RBus_UInt32  adc_clamp_ctrl4_6:1;
        RBus_UInt32  adc_clamp_ctrl4_5:1;
        RBus_UInt32  adc_clamp_ctrl4_4_0:5;
        RBus_UInt32  res2:7;
        RBus_UInt32  adc_clamp_ctrl0:9;
    };
}adc_clamp_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_sog_cmp_7_4:4;
        RBus_UInt32  adc_sog_cmp_3_0:4;
        RBus_UInt32  adc_sog_cmp1_7:1;
        RBus_UInt32  adc_sog_cmp1_6:1;
        RBus_UInt32  adc_sog_cmp1_5_0:6;
        RBus_UInt32  res1:7;
        RBus_UInt32  adc_clamp_ctrl3:9;
    };
}adc_clamp_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  adc_clamp_ctrl6_7:1;
        RBus_UInt32  adc_clamp_ctrl6_6:1;
        RBus_UInt32  adc_clamp_ctrl6_5:1;
        RBus_UInt32  adc_clamp_ctrl6_4:1;
        RBus_UInt32  adc_clamp_ctrl6_3:1;
        RBus_UInt32  adc_clamp_ctrl6_2:1;
        RBus_UInt32  adc_clamp_ctrl6_1:1;
        RBus_UInt32  adc_clamp_ctrl6_0:1;
        RBus_UInt32  adc_clamp_ctrl5_15:1;
        RBus_UInt32  adc_clamp_ctrl5_14_13:2;
        RBus_UInt32  adc_clamp_ctrl5_12:1;
        RBus_UInt32  adc_clamp_ctrl5_11_7:5;
        RBus_UInt32  adc_clamp_ctrl5_6:1;
        RBus_UInt32  adc_clamp_ctrl5_5:1;
        RBus_UInt32  adc_clamp_ctrl5_4:1;
        RBus_UInt32  adc_clamp_ctrl5_3:1;
        RBus_UInt32  adc_clamp_ctrl5_2_1:2;
        RBus_UInt32  adc_clamp_ctrl5_0:1;
    };
}adc_clamp_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}adc_ibias4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  adc_gain_grn:9;
        RBus_UInt32  dummy18020030_15_9:7;
        RBus_UInt32  adc_gain_red:9;
    };
}adc_gain0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  res2:10;
        RBus_UInt32  res3:7;
        RBus_UInt32  adc_gain_blu:9;
    };
}adc_gain1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_off_grn:10;
        RBus_UInt32  dummy18020038_15_10:6;
        RBus_UInt32  adc_off_red:10;
    };
}adc_offset0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  res2:10;
        RBus_UInt32  res3:6;
        RBus_UInt32  adc_off_blu:10;
    };
}adc_offset1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  adc_ctl_red_10_9:2;
        RBus_UInt32  adc_ctl_red_8_6:3;
        RBus_UInt32  adc_ctl_red_5_3:3;
        RBus_UInt32  adc_ctl_red_2_0:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  adc_ctl_grn_10_9:2;
        RBus_UInt32  adc_ctl_grn_8_6:3;
        RBus_UInt32  adc_ctl_grn_5_3:3;
        RBus_UInt32  adc_ctl_grn_2_0:3;
    };
}adc_ctl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  adc_ctl_blu_10_9:2;
        RBus_UInt32  adc_ctl_blu_8_6:3;
        RBus_UInt32  adc_ctl_blu_5_3:3;
        RBus_UInt32  adc_ctl_blu_2_0:3;
    };
}adc_ctl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_clamp_ctrl0_15_14:2;
        RBus_UInt32  vdadc_clamp_ctrl0_13:1;
        RBus_UInt32  vdadc_clamp_ctrl0_12_10:3;
        RBus_UInt32  vdadc_clamp_ctrl0_9_8:2;
        RBus_UInt32  vdadc_clamp_ctrl0_7_4:4;
        RBus_UInt32  vdadc_clamp_ctrl0_3_0:4;
        RBus_UInt32  vdadc_clamp_ctrl1_15_13:3;
        RBus_UInt32  vdadc_clamp_ctrl1_12:1;
        RBus_UInt32  vdadc_clamp_ctrl1_11:1;
        RBus_UInt32  vdadc_clamp_ctrl1_10_9:2;
        RBus_UInt32  vdadc_clamp_ctrl1_8:1;
        RBus_UInt32  vdadc_clamp_ctrl1_7_5:3;
        RBus_UInt32  vdadc_clamp_ctrl1_4:1;
        RBus_UInt32  vdadc_clamp_ctrl1_3_2:2;
        RBus_UInt32  vdadc_clamp_ctrl1_1_0:2;
    };
}vd_adc_clamp_ctl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  vdadc_clamp_ctrl2_15:1;
        RBus_UInt32  vdadc_clamp_ctrl2_14_12:3;
        RBus_UInt32  vdadc_clamp_ctrl2_11:1;
        RBus_UInt32  vdadc_clamp_ctrl2_10:1;
        RBus_UInt32  vdadc_clamp_ctrl2_9_8:2;
        RBus_UInt32  vdadc_clamp_ctrl2_7:1;
        RBus_UInt32  vdadc_clamp_ctrl2_6:1;
        RBus_UInt32  vdadc_clamp_ctrl2_5:1;
        RBus_UInt32  vdadc_clamp_ctrl2_4_2:3;
        RBus_UInt32  vdadc_clamp_ctrl2_1_0:2;
    };
}vd_adc_clamp_ctl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  vdadc_updn_ctrl0_15_14:2;
        RBus_UInt32  vdadc_updn_ctrl0_13_11:3;
        RBus_UInt32  vdadc_updn_ctrl0_10_8:3;
        RBus_UInt32  vdadc_updn_ctrl0_7_3:5;
        RBus_UInt32  vdadc_updn_ctrl0_2_0:3;
    };
}vd_adc_updn_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  vdadc_adc_ctrl_10:1;
        RBus_UInt32  vdadc_adc_ctrl_9_7:3;
        RBus_UInt32  vdadc_adc_ctrl_6:1;
        RBus_UInt32  vdadc_adc_ctrl_5:1;
        RBus_UInt32  vdadc_adc_ctrl_4_3:2;
        RBus_UInt32  vdadc_adc_ctrl_2:1;
        RBus_UInt32  vdadc_adc_ctrl_1:1;
        RBus_UInt32  vdadc_adc_ctrl_0:1;
        RBus_UInt32  res2:8;
        RBus_UInt32  vdadc_lpf_ctrl_7_2:6;
        RBus_UInt32  vdadc_lpf_ctrl_1_0:2;
    };
}vdadc_core_lpf_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  vdadc_ckin_sel_7:1;
        RBus_UInt32  vdadc_ckin_sel_6:1;
        RBus_UInt32  vdadc_ckin_sel_5:1;
        RBus_UInt32  vdadc_ckin_sel_4_2:3;
        RBus_UInt32  vdadc_ckin_sel_1_0:2;
        RBus_UInt32  vdadc_ckout_sel_7:1;
        RBus_UInt32  vdadc_ckout_sel_6:1;
        RBus_UInt32  vdadc_ckout_sel_5:1;
        RBus_UInt32  vdadc_ckout_sel_4:1;
        RBus_UInt32  vdadc_ckout_sel_3_2:2;
        RBus_UInt32  vdadc_ckout_sel_1_0:2;
    };
}vdadc_ck_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_reserve:16;
        RBus_UInt32  res1:12;
        RBus_UInt32  vdadc_in_flag_clr:1;
        RBus_UInt32  vdadc_in_flag:1;
        RBus_UInt32  ldo100ma_pow:1;
        RBus_UInt32  vdadc_pow:1;
    };
}vdadc_pow_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}vd_sct_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  vsync_e2:1;
        RBus_UInt32  vsync_pd:1;
        RBus_UInt32  vsync_pu:1;
        RBus_UInt32  vsync_sr:1;
        RBus_UInt32  hsync0_pwdn:1;
        RBus_UInt32  hsync0_pd_latch:1;
        RBus_UInt32  hsync0_3ven:1;
        RBus_UInt32  hsync0_pol:1;
        RBus_UInt32  hsync0_mode:1;
        RBus_UInt32  hsync0_vos:1;
        RBus_UInt32  hsync0_vtp_1_0:2;
        RBus_UInt32  hsync0_vtn_1_0:2;
    };
}ahs_smt_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  adc_test_7:1;
        RBus_UInt32  adc_test_6_4:3;
        RBus_UInt32  adc_test_3_2:2;
        RBus_UInt32  adc_test_1_0:2;
    };
}adc_test_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vdadc_sct_ctrl:8;
    };
}scart_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hs_hsfb_err_judge_sel:1;
        RBus_UInt32  flag_hs_catch_err_r:1;
        RBus_UInt32  hs_err_judge_en:1;
        RBus_UInt32  hs_catch_edge:1;
        RBus_UInt32  flag_hs_catch_err_ie:1;
        RBus_UInt32  vbick_div_phsel:1;
        RBus_UInt32  vbick_div_inv:1;
        RBus_UInt32  adck_div_inv:1;
        RBus_UInt32  adck_div_phsel:2;
        RBus_UInt32  adck_div_sel:1;
        RBus_UInt32  adck_div_en:1;
        RBus_UInt32  ablagc_cpsel:1;
        RBus_UInt32  vbi_swap:3;
        RBus_UInt32  rgb_from_hsptg:1;
        RBus_UInt32  adc_swap:3;
        RBus_UInt32  vbi_clk_inv:1;
        RBus_UInt32  adc_clkx2_inv:1;
        RBus_UInt32  adc_clk_inv:1;
        RBus_UInt32  soy0_clk_inv:1;
        RBus_UInt32  adc_clk_inv_en:1;
        RBus_UInt32  vbi_clk_en:1;
        RBus_UInt32  adc_clkx2_en:1;
        RBus_UInt32  soy0_clk_en:1;
        RBus_UInt32  st_latch_en:1;
        RBus_UInt32  vbi_clkx2_sel:1;
        RBus_UInt32  adck_test:1;
        RBus_UInt32  soy_test_en:1;
    };
}adc_clkgen_rgb_capture_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  dac_data_select:1;
        RBus_UInt32  adc_data_select:2;
        RBus_UInt32  dummy18020084_27_9:19;
        RBus_UInt32  adck_hdmi_clk_sel:1;
        RBus_UInt32  dummy18020084_7_5:3;
        RBus_UInt32  apll_adc_tstout_mux:3;
        RBus_UInt32  adc_tstout_mux:2;
    };
}adc_apll_adc_testout_mux_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  iadc_rout:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  iadc_gout:12;
    };
}adc_rgb_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  iadc_bout:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  iadc_vout:10;
    };
}adc_rgb_data2_RBUS;





#else //apply LITTLE_ENDIAN


//======ADC register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_power_0:1;
        RBus_UInt32  adc_power_1:1;
        RBus_UInt32  adc_power_2:1;
        RBus_UInt32  adc_power_3:1;
        RBus_UInt32  adc_power_4:1;
        RBus_UInt32  adc_power_5:1;
        RBus_UInt32  adc_power_6:1;
        RBus_UInt32  adc_power_7:1;
        RBus_UInt32  adc_power_8:1;
        RBus_UInt32  adc_power_9:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  dummy18020000_31_16:16;
    };
}adc_power_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_ibias0:8;
        RBus_UInt32  adc_ibias1_0:1;
        RBus_UInt32  adc_ibias1_5_1:5;
        RBus_UInt32  adc_ibias1_6:1;
        RBus_UInt32  adc_ibias1_7:1;
        RBus_UInt32  res2:8;
        RBus_UInt32  res1:8;
    };
}adc_ibias0123_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_ctl_rgb1_1_0:2;
        RBus_UInt32  adc_ctl_rgb1_3_2:2;
        RBus_UInt32  adc_ctl_rgb1_5_4:2;
        RBus_UInt32  adc_ctl_rgb1_6:1;
        RBus_UInt32  adc_ctl_rgb1_7:1;
        RBus_UInt32  adc_ctl_rgb1_8:1;
        RBus_UInt32  adc_ctl_rgb1_9:1;
        RBus_UInt32  adc_ctl_rgb1_11_10:2;
        RBus_UInt32  res2:4;
        RBus_UInt32  adc_ctl_rgb2_1_0:2;
        RBus_UInt32  adc_ctl_rgb2_3_2:2;
        RBus_UInt32  adc_ctl_rgb2_5_4:2;
        RBus_UInt32  adc_ctl_rgb2_6:1;
        RBus_UInt32  adc_ctl_rgb2_7:1;
        RBus_UInt32  adc_ctl_rgb2_8:1;
        RBus_UInt32  adc_ctl_rgb2_9:1;
        RBus_UInt32  adc_ctl_rgb2_11_10:2;
        RBus_UInt32  res1:4;
    };
}adc_ctl_rgb12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_vbias0_0:1;
        RBus_UInt32  adc_vbias0_1:1;
        RBus_UInt32  adc_vbias0_3_2:2;
        RBus_UInt32  adc_vbias0_7_4:4;
        RBus_UInt32  adc_vbias1_2_0:3;
        RBus_UInt32  adc_vbias1_7_3:5;
        RBus_UInt32  adc_vbias2_2_0:3;
        RBus_UInt32  adc_vbias2_3:1;
        RBus_UInt32  adc_vbias2_4:1;
        RBus_UInt32  adc_vbias2_5:1;
        RBus_UInt32  adc_vbias2_6:1;
        RBus_UInt32  adc_vbias2_7:1;
        RBus_UInt32  adc_vbias3_1_0:2;
        RBus_UInt32  adc_vbias3_2:1;
        RBus_UInt32  adc_vbias3_3:1;
        RBus_UInt32  adc_vbias3_4:1;
        RBus_UInt32  adc_vbias3_5:1;
        RBus_UInt32  adc_vbias3_6:1;
        RBus_UInt32  adc_vbias3_7:1;
    };
}adc_vbias_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_clock_1_0:2;
        RBus_UInt32  adc_clock_2:1;
        RBus_UInt32  adc_clock_3:1;
        RBus_UInt32  adc_clock_5_4:2;
        RBus_UInt32  adc_clock_6:1;
        RBus_UInt32  adc_clock_7:1;
        RBus_UInt32  adc_clock_9_8:2;
        RBus_UInt32  adc_clock_10:1;
        RBus_UInt32  adc_clock_11:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  adc_2x_sample_0:1;
        RBus_UInt32  adc_2x_sample_1:1;
        RBus_UInt32  adc_2x_sample_2:1;
        RBus_UInt32  adc_2x_sample_4_3:2;
        RBus_UInt32  adc_2x_sample_5:1;
        RBus_UInt32  adc_2x_sample_6:1;
        RBus_UInt32  adc_2x_sample_7:1;
        RBus_UInt32  res1:8;
    };
}adc_clock_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}adc_ctl_reserved_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_dcrestore_ctrl:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  adc_ctl_rgb_3_0:4;
        RBus_UInt32  adc_ctl_rgb_4:1;
        RBus_UInt32  adc_ctl_rgb_5:1;
        RBus_UInt32  adc_ctl_rgb_6:1;
        RBus_UInt32  adc_ctl_rgb_7:1;
        RBus_UInt32  res1:8;
    };
}adc_dcrestore_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_clamp_ctrl1_1_0:2;
        RBus_UInt32  adc_clamp_ctrl1_2:1;
        RBus_UInt32  adc_clamp_ctrl1_4_3:2;
        RBus_UInt32  adc_clamp_ctrl1_5:1;
        RBus_UInt32  adc_clamp_ctrl1_7_6:2;
        RBus_UInt32  adc_clamp_ctrl1_8:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  res2:4;
        RBus_UInt32  adc_clamp_ctrl2_0:1;
        RBus_UInt32  adc_clamp_ctrl2_1:1;
        RBus_UInt32  adc_clamp_ctrl2_2:1;
        RBus_UInt32  adc_clamp_ctrl2_3:1;
        RBus_UInt32  adc_clamp_ctrl2_4:1;
        RBus_UInt32  adc_clamp_ctrl2_5:1;
        RBus_UInt32  adc_clamp_ctrl2_7_6:2;
        RBus_UInt32  adc_clamp_ctrl2_9_8:2;
        RBus_UInt32  adc_clamp_ctrl2_10:1;
        RBus_UInt32  adc_clamp_ctrl2_11:1;
        RBus_UInt32  res1:4;
    };
}adc_clamp_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_clamp_ctrl0:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  adc_clamp_ctrl4_4_0:5;
        RBus_UInt32  adc_clamp_ctrl4_5:1;
        RBus_UInt32  adc_clamp_ctrl4_6:1;
        RBus_UInt32  adc_clamp_ctrl4_7:1;
        RBus_UInt32  res1:8;
    };
}adc_clamp_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_clamp_ctrl3:9;
        RBus_UInt32  res1:7;
        RBus_UInt32  adc_sog_cmp1_5_0:6;
        RBus_UInt32  adc_sog_cmp1_6:1;
        RBus_UInt32  adc_sog_cmp1_7:1;
        RBus_UInt32  adc_sog_cmp_3_0:4;
        RBus_UInt32  adc_sog_cmp_7_4:4;
    };
}adc_clamp_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_clamp_ctrl5_0:1;
        RBus_UInt32  adc_clamp_ctrl5_2_1:2;
        RBus_UInt32  adc_clamp_ctrl5_3:1;
        RBus_UInt32  adc_clamp_ctrl5_4:1;
        RBus_UInt32  adc_clamp_ctrl5_5:1;
        RBus_UInt32  adc_clamp_ctrl5_6:1;
        RBus_UInt32  adc_clamp_ctrl5_11_7:5;
        RBus_UInt32  adc_clamp_ctrl5_12:1;
        RBus_UInt32  adc_clamp_ctrl5_14_13:2;
        RBus_UInt32  adc_clamp_ctrl5_15:1;
        RBus_UInt32  adc_clamp_ctrl6_0:1;
        RBus_UInt32  adc_clamp_ctrl6_1:1;
        RBus_UInt32  adc_clamp_ctrl6_2:1;
        RBus_UInt32  adc_clamp_ctrl6_3:1;
        RBus_UInt32  adc_clamp_ctrl6_4:1;
        RBus_UInt32  adc_clamp_ctrl6_5:1;
        RBus_UInt32  adc_clamp_ctrl6_6:1;
        RBus_UInt32  adc_clamp_ctrl6_7:1;
        RBus_UInt32  res1:8;
    };
}adc_clamp_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}adc_ibias4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_gain_red:9;
        RBus_UInt32  dummy18020030_15_9:7;
        RBus_UInt32  adc_gain_grn:9;
        RBus_UInt32  res1:7;
    };
}adc_gain0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_gain_blu:9;
        RBus_UInt32  res3:7;
        RBus_UInt32  res2:10;
        RBus_UInt32  res1:6;
    };
}adc_gain1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_off_red:10;
        RBus_UInt32  dummy18020038_15_10:6;
        RBus_UInt32  adc_off_grn:10;
        RBus_UInt32  res1:6;
    };
}adc_offset0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_off_blu:10;
        RBus_UInt32  res3:6;
        RBus_UInt32  res2:10;
        RBus_UInt32  res1:6;
    };
}adc_offset1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_ctl_grn_2_0:3;
        RBus_UInt32  adc_ctl_grn_5_3:3;
        RBus_UInt32  adc_ctl_grn_8_6:3;
        RBus_UInt32  adc_ctl_grn_10_9:2;
        RBus_UInt32  res2:5;
        RBus_UInt32  adc_ctl_red_2_0:3;
        RBus_UInt32  adc_ctl_red_5_3:3;
        RBus_UInt32  adc_ctl_red_8_6:3;
        RBus_UInt32  adc_ctl_red_10_9:2;
        RBus_UInt32  res1:5;
    };
}adc_ctl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_ctl_blu_2_0:3;
        RBus_UInt32  adc_ctl_blu_5_3:3;
        RBus_UInt32  adc_ctl_blu_8_6:3;
        RBus_UInt32  adc_ctl_blu_10_9:2;
        RBus_UInt32  res1:21;
    };
}adc_ctl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_clamp_ctrl1_1_0:2;
        RBus_UInt32  vdadc_clamp_ctrl1_3_2:2;
        RBus_UInt32  vdadc_clamp_ctrl1_4:1;
        RBus_UInt32  vdadc_clamp_ctrl1_7_5:3;
        RBus_UInt32  vdadc_clamp_ctrl1_8:1;
        RBus_UInt32  vdadc_clamp_ctrl1_10_9:2;
        RBus_UInt32  vdadc_clamp_ctrl1_11:1;
        RBus_UInt32  vdadc_clamp_ctrl1_12:1;
        RBus_UInt32  vdadc_clamp_ctrl1_15_13:3;
        RBus_UInt32  vdadc_clamp_ctrl0_3_0:4;
        RBus_UInt32  vdadc_clamp_ctrl0_7_4:4;
        RBus_UInt32  vdadc_clamp_ctrl0_9_8:2;
        RBus_UInt32  vdadc_clamp_ctrl0_12_10:3;
        RBus_UInt32  vdadc_clamp_ctrl0_13:1;
        RBus_UInt32  vdadc_clamp_ctrl0_15_14:2;
    };
}vd_adc_clamp_ctl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_clamp_ctrl2_1_0:2;
        RBus_UInt32  vdadc_clamp_ctrl2_4_2:3;
        RBus_UInt32  vdadc_clamp_ctrl2_5:1;
        RBus_UInt32  vdadc_clamp_ctrl2_6:1;
        RBus_UInt32  vdadc_clamp_ctrl2_7:1;
        RBus_UInt32  vdadc_clamp_ctrl2_9_8:2;
        RBus_UInt32  vdadc_clamp_ctrl2_10:1;
        RBus_UInt32  vdadc_clamp_ctrl2_11:1;
        RBus_UInt32  vdadc_clamp_ctrl2_14_12:3;
        RBus_UInt32  vdadc_clamp_ctrl2_15:1;
        RBus_UInt32  res1:16;
    };
}vd_adc_clamp_ctl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_updn_ctrl0_2_0:3;
        RBus_UInt32  vdadc_updn_ctrl0_7_3:5;
        RBus_UInt32  vdadc_updn_ctrl0_10_8:3;
        RBus_UInt32  vdadc_updn_ctrl0_13_11:3;
        RBus_UInt32  vdadc_updn_ctrl0_15_14:2;
        RBus_UInt32  res1:16;
    };
}vd_adc_updn_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_lpf_ctrl_1_0:2;
        RBus_UInt32  vdadc_lpf_ctrl_7_2:6;
        RBus_UInt32  res2:8;
        RBus_UInt32  vdadc_adc_ctrl_0:1;
        RBus_UInt32  vdadc_adc_ctrl_1:1;
        RBus_UInt32  vdadc_adc_ctrl_2:1;
        RBus_UInt32  vdadc_adc_ctrl_4_3:2;
        RBus_UInt32  vdadc_adc_ctrl_5:1;
        RBus_UInt32  vdadc_adc_ctrl_6:1;
        RBus_UInt32  vdadc_adc_ctrl_9_7:3;
        RBus_UInt32  vdadc_adc_ctrl_10:1;
        RBus_UInt32  res1:5;
    };
}vdadc_core_lpf_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_ckout_sel_1_0:2;
        RBus_UInt32  vdadc_ckout_sel_3_2:2;
        RBus_UInt32  vdadc_ckout_sel_4:1;
        RBus_UInt32  vdadc_ckout_sel_5:1;
        RBus_UInt32  vdadc_ckout_sel_6:1;
        RBus_UInt32  vdadc_ckout_sel_7:1;
        RBus_UInt32  vdadc_ckin_sel_1_0:2;
        RBus_UInt32  vdadc_ckin_sel_4_2:3;
        RBus_UInt32  vdadc_ckin_sel_5:1;
        RBus_UInt32  vdadc_ckin_sel_6:1;
        RBus_UInt32  vdadc_ckin_sel_7:1;
        RBus_UInt32  res1:16;
    };
}vdadc_ck_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_pow:1;
        RBus_UInt32  ldo100ma_pow:1;
        RBus_UInt32  vdadc_in_flag:1;
        RBus_UInt32  vdadc_in_flag_clr:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  vdadc_reserve:16;
    };
}vdadc_pow_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}vd_sct_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync0_vtn_1_0:2;
        RBus_UInt32  hsync0_vtp_1_0:2;
        RBus_UInt32  hsync0_vos:1;
        RBus_UInt32  hsync0_mode:1;
        RBus_UInt32  hsync0_pol:1;
        RBus_UInt32  hsync0_3ven:1;
        RBus_UInt32  hsync0_pd_latch:1;
        RBus_UInt32  hsync0_pwdn:1;
        RBus_UInt32  vsync_sr:1;
        RBus_UInt32  vsync_pu:1;
        RBus_UInt32  vsync_pd:1;
        RBus_UInt32  vsync_e2:1;
        RBus_UInt32  res1:18;
    };
}ahs_smt_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_test_1_0:2;
        RBus_UInt32  adc_test_3_2:2;
        RBus_UInt32  adc_test_6_4:3;
        RBus_UInt32  adc_test_7:1;
        RBus_UInt32  res1:24;
    };
}adc_test_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdadc_sct_ctrl:8;
        RBus_UInt32  res1:24;
    };
}scart_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  soy_test_en:1;
        RBus_UInt32  adck_test:1;
        RBus_UInt32  vbi_clkx2_sel:1;
        RBus_UInt32  st_latch_en:1;
        RBus_UInt32  soy0_clk_en:1;
        RBus_UInt32  adc_clkx2_en:1;
        RBus_UInt32  vbi_clk_en:1;
        RBus_UInt32  adc_clk_inv_en:1;
        RBus_UInt32  soy0_clk_inv:1;
        RBus_UInt32  adc_clk_inv:1;
        RBus_UInt32  adc_clkx2_inv:1;
        RBus_UInt32  vbi_clk_inv:1;
        RBus_UInt32  adc_swap:3;
        RBus_UInt32  rgb_from_hsptg:1;
        RBus_UInt32  vbi_swap:3;
        RBus_UInt32  ablagc_cpsel:1;
        RBus_UInt32  adck_div_en:1;
        RBus_UInt32  adck_div_sel:1;
        RBus_UInt32  adck_div_phsel:2;
        RBus_UInt32  adck_div_inv:1;
        RBus_UInt32  vbick_div_inv:1;
        RBus_UInt32  vbick_div_phsel:1;
        RBus_UInt32  flag_hs_catch_err_ie:1;
        RBus_UInt32  hs_catch_edge:1;
        RBus_UInt32  hs_err_judge_en:1;
        RBus_UInt32  flag_hs_catch_err_r:1;
        RBus_UInt32  hs_hsfb_err_judge_sel:1;
    };
}adc_clkgen_rgb_capture_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_tstout_mux:2;
        RBus_UInt32  apll_adc_tstout_mux:3;
        RBus_UInt32  dummy18020084_7_5:3;
        RBus_UInt32  adck_hdmi_clk_sel:1;
        RBus_UInt32  dummy18020084_27_9:19;
        RBus_UInt32  adc_data_select:2;
        RBus_UInt32  dac_data_select:1;
        RBus_UInt32  res1:1;
    };
}adc_apll_adc_testout_mux_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  iadc_gout:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  iadc_rout:12;
        RBus_UInt32  res1:4;
    };
}adc_rgb_data_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  iadc_vout:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  iadc_bout:12;
        RBus_UInt32  res1:4;
    };
}adc_rgb_data2_RBUS;


#endif







#endif //_RBUS_ADC_REG_H_

