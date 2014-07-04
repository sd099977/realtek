/**
* @file rbusPinmuxReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2014/5/9
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_PINMUX_REG_H_
#define _RBUS_PINMUX_REG_H_

//#include "rbusTypes.h"
#include <asm/arch/rbus/rbusTypes.h>



// PINMUX Register Address

#define PINMUX_GPIO_CFG_0_VADDR                    (0xb8000800)
#define PINMUX_GPIO_CFG_1_VADDR                    (0xb8000804)
#define PINMUX_GPIO_CFG_2_VADDR                    (0xb8000808)
#define PINMUX_GPIO_CFG_3_VADDR                    (0xb800080c)
#define PINMUX_GPIO_CFG_4_VADDR                    (0xb8000810)
#define PINMUX_GPIO_CFG_5_VADDR                    (0xb8000814)
#define PINMUX_GPIO_CFG_6_VADDR                    (0xb8000818)
#define PINMUX_GPIO_CFG_7_VADDR                    (0xb800081c)
#define PINMUX_GPIO_CFG_8_VADDR                    (0xb8000820)
#define PINMUX_GPIO_CFG_9_VADDR                    (0xb8000824)
#define PINMUX_GPIO_CFG_10_VADDR                   (0xb8000828)
#define PINMUX_GPIO_CFG_11_VADDR                   (0xb800082c)
#define PINMUX_GPIO_CFG_12_VADDR                   (0xb8000830)
#define PINMUX_GPIO_CFG_13_VADDR                   (0xb8000834)
#define PINMUX_GPIO_CFG_14_VADDR                   (0xb8000838)
#define PINMUX_GPIO_CFG_15_VADDR                   (0xb800083c)
#define PINMUX_GPIO_CFG_16_VADDR                   (0xb8000840)
#define PINMUX_GPIO_CFG_17_VADDR                   (0xb8000844)
#define PINMUX_GPIO_CFG_18_VADDR                   (0xb8000848)
#define PINMUX_GPIO_CFG_46_VADDR                   (0xb8000948)
#define PINMUX_GPIO_CFG_47_VADDR                   (0xb800094c)
#define PINMUX_GPIO_CFG_48_VADDR                   (0xb8000950)
#define PINMUX_GPIO_CFG_49_VADDR                   (0xb8000954)
#define PINMUX_GPIO_CFG_19_VADDR                   (0xb800084c)
#define PINMUX_GPIO_CFG_20_VADDR                   (0xb8000850)
#define PINMUX_GPIO_CFG_21_VADDR                   (0xb8000854)
#define PINMUX_GPIO_CFG_22_VADDR                   (0xb8000858)
#define PINMUX_GPIO_CFG_23_VADDR                   (0xb800085c)
#define PINMUX_GPIO_CFG_24_VADDR                   (0xb8000860)
#define PINMUX_GPIO_CFG_25_VADDR                   (0xb8000864)
#define PINMUX_GPIO_CFG_26_VADDR                   (0xb8000868)
#define PINMUX_GPIO_CFG_27_VADDR                   (0xb800086c)
#define PINMUX_GPIO_CFG_28_VADDR                   (0xb8000870)
#define PINMUX_GPIO_CFG_29_VADDR                   (0xb8000874)
#define PINMUX_GPIO_CFG_30_VADDR                   (0xb8000878)
#define PINMUX_GPIO_CFG_31_VADDR                   (0xb800087c)
#define PINMUX_GPIO_CFG_32_VADDR                   (0xb8000880)
#define PINMUX_GPIO_CFG_33_VADDR                   (0xb8000884)
#define PINMUX_GPIO_CFG_34_VADDR                   (0xb8000888)
#define PINMUX_GPIO_CFG_35_VADDR                   (0xb800088c)
#define PINMUX_GPIO_CFG_50_VADDR                   (0xb8000958)
#define PINMUX_GPIO_CFG_40_VADDR                   (0xb80008a0)
#define PINMUX_GPIO_CFG_41_VADDR                   (0xb80008a4)
#define PINMUX_GPIO_CFG_42_VADDR                   (0xb80008a8)
#define PINMUX_GPIO_CFG_43_VADDR                   (0xb80008ac)
#define PINMUX_GPIO_CFG_51_VADDR                   (0xb800095c)
#define PINMUX_GPIO_CFG_36_VADDR                   (0xb8000890)
#define PINMUX_GPIO_CFG_37_VADDR                   (0xb8000894)
#define PINMUX_GPIO_CFG_38_VADDR                   (0xb8000898)
#define PINMUX_GPIO_CFG_39_VADDR                   (0xb800089c)
#define PINMUX_GPIO_CFG_44_VADDR                   (0xb80008b0)
#define PINMUX_GPIO_CFG_45_VADDR                   (0xb80008b4)
#define PINMUX_LVDS_CFG_0_VADDR                    (0xb80008b8)
#define PINMUX_LVDS_CFG_1_VADDR                    (0xb80008bc)
#define PINMUX_LVDS_CFG_2_VADDR                    (0xb80008c0)
#define PINMUX_LVDS_CFG_3_VADDR                    (0xb80008c4)
#define PINMUX_LVDS_CFG_4_VADDR                    (0xb80008c8)
#define PINMUX_HV_CFG_VADDR                        (0xb80008d8)
#define PINMUX_YPP_ADC_CFG_1_VADDR                 (0xb80008dc)
#define PINMUX_YPP_ADC_CFG_2_VADDR                 (0xb80008e0)
#define PINMUX_ADC_CFG_1_VADDR                     (0xb80008e4)
#define PINMUX_ADC_CFG_2_VADDR                     (0xb80008e8)
#define PINMUX_SCART_FSW_CFG_VD_DAC_CFG_VADDR      (0xb80008ec)
#define PINMUX_BB_CFG_1_VADDR                      (0xb80008f0)
#define PINMUX_BB_CFG_2_VADDR                      (0xb80008f4)
#define PINMUX_BB_USB_CFG_1_VADDR                  (0xb80008f8)
#define PINMUX_PIN_MUX_CTRL0_VADDR                 (0xb80008fc)
#define PINMUX_PIN_MUX_CTRL1_VADDR                 (0xb8000900)
#define PINMUX_PIN_MUX_CTRL2_VADDR                 (0xb8000904)
#define PINMUX_PIN_MUX_CTRL3_VADDR                 (0xb8000908)
#define PINMUX_PIN_MUX_CTRL4_VADDR                 (0xb800090c)
#define PINMUX_PIN_MUX_CTRL5_VADDR                 (0xb8000910)
#define PINMUX_PIN_MUX_CTRL6_VADDR                 (0xb8000914)
#define PINMUX_PIN_MUX_CTRL7_VADDR                 (0xb8000918)
#define PINMUX_PIN_MUX_CTRL8_VADDR                 (0xb800091c)
#define PINMUX_PIN_MUX_CTRL9_VADDR                 (0xb8000920)
#define PINMUX_PIN_MUX_CTR20_VADDR                 (0xb8000924)
#define PINMUX_PIN_MUX_CTR21_VADDR                 (0xb8000928)
#define PINMUX_SCHMIDT_TRIGGER_0_VADDR             (0xb800092c)
#define PINMUX_SCHMIDT_TRIGGER_1_VADDR             (0xb8000930)
#define PINMUX_SCHMIDT_TRIGGER_2_VADDR             (0xb8000934)
#define PINMUX_SCHMIDT_TRIGGER_3_VADDR             (0xb8000938)
#define PINMUX_SCHMIDT_TRIGGER_4_VADDR             (0xb800093c)
#define PINMUX_SCHMIDT_TRIGGER_5_VADDR             (0xb8000940)
#define PINMUX_MAIN_TEST_PIN_CTRL_VADDR            (0xb8000944)
#define PINMUX_LVDSEPI_PHY_78_CTRL_0_VADDR         (0xb8000c00)
#define PINMUX_LVDSEPI_PHY_78_CTRL_1_VADDR         (0xb8000c04)
#define PINMUX_LVDSEPI_PHY_78_CTRL_2_VADDR         (0xb8000c08)
#define PINMUX_LVDSEPI_PHY_78_CTRL_3_VADDR         (0xb8000c0c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_4_VADDR         (0xb8000c10)
#define PINMUX_LVDSEPI_PHY_78_CTRL_5_VADDR         (0xb8000c14)
#define PINMUX_LVDSEPI_PHY_78_CTRL_6_VADDR         (0xb8000c18)
#define PINMUX_LVDSEPI_PHY_78_CTRL_7_VADDR         (0xb8000c1c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_8_VADDR         (0xb8000c20)
#define PINMUX_LVDSEPI_PHY_78_CTRL_9_VADDR         (0xb8000c24)
#define PINMUX_LVDSEPI_PHY_78_CTRL_10_VADDR        (0xb8000c28)
#define PINMUX_LVDSEPI_PHY_78_CTRL_11_VADDR        (0xb8000c2c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_12_VADDR        (0xb8000c30)
#define PINMUX_LVDSEPI_PHY_78_CTRL_13_VADDR        (0xb8000c34)
#define PINMUX_LVDSEPI_PHY_78_CTRL_14_VADDR        (0xb8000c38)
#define PINMUX_LVDSEPI_PHY_78_CTRL_15_VADDR        (0xb8000c3c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_16_VADDR        (0xb8000c40)
#define PINMUX_LVDSEPI_PHY_78_CTRL_17_VADDR        (0xb8000c44)
#define PINMUX_LVDSEPI_PHY_78_CTRL_18_VADDR        (0xb8000c48)
#define PINMUX_LVDSEPI_PHY_78_CTRL_19_VADDR        (0xb8000c4c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_20_VADDR        (0xb8000c50)
#define PINMUX_LVDSEPI_PHY_78_CTRL_21_VADDR        (0xb8000c54)
#define PINMUX_LVDSEPI_PHY_78_CTRL_22_VADDR        (0xb8000c58)
#define PINMUX_LVDSEPI_PHY_78_CTRL_23_VADDR        (0xb8000c5c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_24_VADDR        (0xb8000c60)
#define PINMUX_LVDSEPI_PHY_78_CTRL_25_VADDR        (0xb8000c64)
#define PINMUX_LVDSEPI_PHY_78_CTRL_26_VADDR        (0xb8000c68)
#define PINMUX_LVDSEPI_PHY_78_CTRL_27_VADDR        (0xb8000c6c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_28_VADDR        (0xb8000c70)
#define PINMUX_LVDSEPI_PHY_78_CTRL_29_VADDR        (0xb8000c74)
#define PINMUX_LVDSEPI_PHY_78_CTRL_30_VADDR        (0xb8000c78)
#define PINMUX_LVDSEPI_PHY_78_CTRL_31_VADDR        (0xb8000c7c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_32_VADDR        (0xb8000c80)
#define PINMUX_LVDSEPI_PHY_78_CTRL_33_VADDR        (0xb8000c84)
#define PINMUX_LVDSEPI_PHY_78_CTRL_34_VADDR        (0xb8000c88)
#define PINMUX_LVDSEPI_PHY_78_CTRL_35_VADDR        (0xb8000c8c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_36_VADDR        (0xb8000c90)
#define PINMUX_LVDSEPI_PHY_78_CTRL_37_VADDR        (0xb8000c94)
#define PINMUX_LVDSEPI_PHY_78_CTRL_38_VADDR        (0xb8000c98)
#define PINMUX_LVDSEPI_PHY_78_CTRL_39_VADDR        (0xb8000c9c)
#define PINMUX_LVDSEPI_PHY_78_CTRL_40_VADDR        (0xb8000ca0)
#define PINMUX_LVDSEPI_PHY_78_CTRL_41_VADDR        (0xb8000ca4)
#define PINMUX_LVDSEPI_PHY_78_CTRL_42_VADDR        (0xb8000ca8)
#define PINMUX_LVDSEPI_PHY_78_CTRL_43_VADDR        (0xb8000cac)
#define PINMUX_LVDSEPI_PHY_78_CTRL_44_VADDR        (0xb8000cb0)
#define PINMUX_LVDSEPI_PHY_78_CTRL_45_VADDR        (0xb8000cb4)
#define PINMUX_LVDSEPI_PHY_78_CTRL_46_VADDR        (0xb8000cb8)
#define PINMUX_LVDSEPI_PHY_78_CTRL_47_VADDR        (0xb8000cbc)
#define PINMUX_VBY1_D_PHY0_TXBIST_00_VADDR         (0xb8000cc0)
#define PINMUX_VBY1_D_PHY0_TXBIST_01_VADDR         (0xb8000cc4)
#define PINMUX_VBY1_D_PHY0_TXBIST_02_VADDR         (0xb8000cc8)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======PINMUX register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rf_if_ps:5;
        RBus_UInt32  rf_if_pu:1;
        RBus_UInt32  rf_if_pd:1;
        RBus_UInt32  rf_if_ds:1;
        RBus_UInt32  rf_if_sr:1;
        RBus_UInt32  tuner_scl_ps:5;
        RBus_UInt32  tuner_scl_pu:1;
        RBus_UInt32  tuner_scl_pd:1;
        RBus_UInt32  tuner_scl_ds:1;
        RBus_UInt32  tuner_scl_sr:1;
        RBus_UInt32  res1:14;
    };
}gpio_cfg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tuner_sda_ps:5;
        RBus_UInt32  tuner_sda_pu:1;
        RBus_UInt32  tuner_sda_pd:1;
        RBus_UInt32  tuner_sda_ds:1;
        RBus_UInt32  tuner_sda_sr:1;
        RBus_UInt32  res1:23;
    };
}gpio_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_5_ps:5;
        RBus_UInt32  gpio_5_pu:1;
        RBus_UInt32  gpio_5_pd:1;
        RBus_UInt32  gpio_5_ds:1;
        RBus_UInt32  gpio_5_sr:1;
        RBus_UInt32  gpio_6_ps:5;
        RBus_UInt32  gpio_6_pu:1;
        RBus_UInt32  gpio_6_pd:1;
        RBus_UInt32  gpio_6_ds:1;
        RBus_UInt32  gpio_6_sr:1;
        RBus_UInt32  gpio_7_ps:5;
        RBus_UInt32  gpio_7_pu:1;
        RBus_UInt32  gpio_7_pd:1;
        RBus_UInt32  gpio_7_ds:1;
        RBus_UInt32  gpio_7_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_8_ps:5;
        RBus_UInt32  gpio_8_pu:1;
        RBus_UInt32  gpio_8_pd:1;
        RBus_UInt32  gpio_8_ds:1;
        RBus_UInt32  gpio_8_sr:1;
        RBus_UInt32  gpio_9_ps:5;
        RBus_UInt32  gpio_9_pu:1;
        RBus_UInt32  gpio_9_pd:1;
        RBus_UInt32  gpio_9_ds:1;
        RBus_UInt32  gpio_9_sr:1;
        RBus_UInt32  gpio_10_ps:5;
        RBus_UInt32  gpio_10_pu:1;
        RBus_UInt32  gpio_10_pd:1;
        RBus_UInt32  gpio_10_ds:1;
        RBus_UInt32  gpio_10_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_11_ps:5;
        RBus_UInt32  gpio_11_pu:1;
        RBus_UInt32  gpio_11_pd:1;
        RBus_UInt32  gpio_11_ds:1;
        RBus_UInt32  gpio_11_sr:1;
        RBus_UInt32  gpio_12_ps:5;
        RBus_UInt32  gpio_12_pu:1;
        RBus_UInt32  gpio_12_pd:1;
        RBus_UInt32  gpio_12_ds:1;
        RBus_UInt32  gpio_12_sr:1;
        RBus_UInt32  gpio_13_ps:5;
        RBus_UInt32  gpio_13_pu:1;
        RBus_UInt32  gpio_13_pd:1;
        RBus_UInt32  gpio_13_ds:1;
        RBus_UInt32  gpio_13_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_14_ps:5;
        RBus_UInt32  gpio_14_pu:1;
        RBus_UInt32  gpio_14_pd:1;
        RBus_UInt32  gpio_14_ds:1;
        RBus_UInt32  gpio_14_sr:1;
        RBus_UInt32  gpio_15_ps:5;
        RBus_UInt32  gpio_15_pu:1;
        RBus_UInt32  gpio_15_pd:1;
        RBus_UInt32  gpio_15_ds:1;
        RBus_UInt32  gpio_15_sr:1;
        RBus_UInt32  gpio_16_ps:5;
        RBus_UInt32  gpio_16_pu:1;
        RBus_UInt32  gpio_16_pd:1;
        RBus_UInt32  gpio_16_ds:1;
        RBus_UInt32  gpio_16_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_17_ps:5;
        RBus_UInt32  gpio_17_pu:1;
        RBus_UInt32  gpio_17_pd:1;
        RBus_UInt32  gpio_17_ds:1;
        RBus_UInt32  gpio_17_sr:1;
        RBus_UInt32  gpio_18_ps:5;
        RBus_UInt32  gpio_18_pu:1;
        RBus_UInt32  gpio_18_pd:1;
        RBus_UInt32  gpio_18_ds:1;
        RBus_UInt32  gpio_18_sr:1;
        RBus_UInt32  gpio_19_ps:5;
        RBus_UInt32  gpio_19_pu:1;
        RBus_UInt32  gpio_19_pd:1;
        RBus_UInt32  gpio_19_ds:1;
        RBus_UInt32  gpio_19_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_20_ps:5;
        RBus_UInt32  gpio_20_pu:1;
        RBus_UInt32  gpio_20_pd:1;
        RBus_UInt32  gpio_20_ds:1;
        RBus_UInt32  gpio_20_sr:1;
        RBus_UInt32  gpio_21_ps:5;
        RBus_UInt32  gpio_21_pu:1;
        RBus_UInt32  gpio_21_pd:1;
        RBus_UInt32  gpio_21_ds:1;
        RBus_UInt32  gpio_21_sr:1;
        RBus_UInt32  gpio_22_ps:5;
        RBus_UInt32  gpio_22_pu:1;
        RBus_UInt32  gpio_22_pd:1;
        RBus_UInt32  gpio_22_ds:1;
        RBus_UInt32  res1:6;
    };
}gpio_cfg_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_23_ps:5;
        RBus_UInt32  gpio_23_pu:1;
        RBus_UInt32  gpio_23_pd:1;
        RBus_UInt32  gpio_23_ds:1;
        RBus_UInt32  gpio_23_sr:1;
        RBus_UInt32  gpio_25_ps:5;
        RBus_UInt32  gpio_25_pu:1;
        RBus_UInt32  gpio_25_pd:1;
        RBus_UInt32  gpio_25_ds:1;
        RBus_UInt32  gpio_25_sr:1;
        RBus_UInt32  gpio_26_ps:5;
        RBus_UInt32  gpio_26_pu:1;
        RBus_UInt32  gpio_26_pd:1;
        RBus_UInt32  gpio_26_ds:1;
        RBus_UInt32  gpio_26_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_27_ps:5;
        RBus_UInt32  gpio_27_pu:1;
        RBus_UInt32  gpio_27_pd:1;
        RBus_UInt32  gpio_27_ds:1;
        RBus_UInt32  gpio_27_sr:1;
        RBus_UInt32  gpio_28_ps:5;
        RBus_UInt32  gpio_28_pu:1;
        RBus_UInt32  gpio_28_pd:1;
        RBus_UInt32  gpio_28_ds:1;
        RBus_UInt32  gpio_28_sr:1;
        RBus_UInt32  gpio_30_ps:5;
        RBus_UInt32  gpio_30_pu:1;
        RBus_UInt32  gpio_30_pd:1;
        RBus_UInt32  gpio_30_ds:1;
        RBus_UInt32  gpio_30_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_31_ps:5;
        RBus_UInt32  gpio_31_pu:1;
        RBus_UInt32  gpio_31_pd:1;
        RBus_UInt32  gpio_31_ds:1;
        RBus_UInt32  gpio_31_sr:1;
        RBus_UInt32  gpio_34_ps:5;
        RBus_UInt32  gpio_34_pu:1;
        RBus_UInt32  gpio_34_pd:1;
        RBus_UInt32  gpio_34_ds:1;
        RBus_UInt32  gpio_34_sr:1;
        RBus_UInt32  gpio_35_ps:5;
        RBus_UInt32  gpio_35_pu:1;
        RBus_UInt32  gpio_35_pd:1;
        RBus_UInt32  gpio_35_ds:1;
        RBus_UInt32  gpio_35_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_36_ps:5;
        RBus_UInt32  gpio_36_pu:1;
        RBus_UInt32  gpio_36_pd:1;
        RBus_UInt32  gpio_36_ds:1;
        RBus_UInt32  gpio_36_sr:1;
        RBus_UInt32  gpio_37_ps:5;
        RBus_UInt32  gpio_37_pu:1;
        RBus_UInt32  gpio_37_pd:1;
        RBus_UInt32  gpio_37_ds:1;
        RBus_UInt32  gpio_37_sr:1;
        RBus_UInt32  gpio_38_ps:5;
        RBus_UInt32  gpio_38_pu:1;
        RBus_UInt32  gpio_38_pd:1;
        RBus_UInt32  gpio_38_ds:1;
        RBus_UInt32  gpio_38_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_39_ps:5;
        RBus_UInt32  gpio_39_pu:1;
        RBus_UInt32  gpio_39_pd:1;
        RBus_UInt32  gpio_39_ds:1;
        RBus_UInt32  gpio_39_sr:1;
        RBus_UInt32  gpio_40_ps:5;
        RBus_UInt32  gpio_40_pu:1;
        RBus_UInt32  gpio_40_pd:1;
        RBus_UInt32  gpio_40_ds:1;
        RBus_UInt32  gpio_40_sr:1;
        RBus_UInt32  gpio_41_ps:5;
        RBus_UInt32  gpio_41_pu:1;
        RBus_UInt32  gpio_41_pd:1;
        RBus_UInt32  gpio_41_ds:1;
        RBus_UInt32  gpio_41_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_42_ps:5;
        RBus_UInt32  gpio_42_pu:1;
        RBus_UInt32  gpio_42_pd:1;
        RBus_UInt32  gpio_42_ds:1;
        RBus_UInt32  gpio_42_sr:1;
        RBus_UInt32  gpio_43_ps:5;
        RBus_UInt32  gpio_43_pu:1;
        RBus_UInt32  gpio_43_pd:1;
        RBus_UInt32  gpio_43_ds:1;
        RBus_UInt32  gpio_43_sr:1;
        RBus_UInt32  gpio_44_ps:5;
        RBus_UInt32  gpio_44_pu:1;
        RBus_UInt32  gpio_44_pd:1;
        RBus_UInt32  gpio_44_ds:1;
        RBus_UInt32  gpio_44_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_45_ps:5;
        RBus_UInt32  gpio_45_pu:1;
        RBus_UInt32  gpio_45_pd:1;
        RBus_UInt32  gpio_45_ds:1;
        RBus_UInt32  gpio_45_sr:1;
        RBus_UInt32  gpio_46_ps:5;
        RBus_UInt32  gpio_46_pu:1;
        RBus_UInt32  gpio_46_pd:1;
        RBus_UInt32  gpio_46_ds:1;
        RBus_UInt32  gpio_46_sr:1;
        RBus_UInt32  gpio_47_ps:5;
        RBus_UInt32  gpio_47_pu:1;
        RBus_UInt32  gpio_47_pd:1;
        RBus_UInt32  gpio_47_ds:1;
        RBus_UInt32  gpio_47_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_48_ps:5;
        RBus_UInt32  gpio_48_pu:1;
        RBus_UInt32  gpio_48_pd:1;
        RBus_UInt32  gpio_48_ds:1;
        RBus_UInt32  gpio_48_sr:1;
        RBus_UInt32  gpio_49_ps:5;
        RBus_UInt32  gpio_49_pu:1;
        RBus_UInt32  gpio_49_pd:1;
        RBus_UInt32  gpio_49_ds:1;
        RBus_UInt32  gpio_49_sr:1;
        RBus_UInt32  gpio_50_ps:5;
        RBus_UInt32  gpio_50_pu:1;
        RBus_UInt32  gpio_50_pd:1;
        RBus_UInt32  gpio_50_ds:1;
        RBus_UInt32  gpio_50_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_51_ps:5;
        RBus_UInt32  gpio_51_pu:1;
        RBus_UInt32  gpio_51_pd:1;
        RBus_UInt32  gpio_51_ds:1;
        RBus_UInt32  gpio_51_sr:1;
        RBus_UInt32  gpio_52_ps:5;
        RBus_UInt32  gpio_52_pu:1;
        RBus_UInt32  gpio_52_pd:1;
        RBus_UInt32  gpio_52_ds:1;
        RBus_UInt32  gpio_52_sr:1;
        RBus_UInt32  gpio_53_ps:5;
        RBus_UInt32  gpio_53_pu:1;
        RBus_UInt32  gpio_53_pd:1;
        RBus_UInt32  gpio_53_ds:1;
        RBus_UInt32  gpio_53_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_54_ps:5;
        RBus_UInt32  gpio_54_pu:1;
        RBus_UInt32  gpio_54_pd:1;
        RBus_UInt32  gpio_54_ds:1;
        RBus_UInt32  gpio_54_sr:1;
        RBus_UInt32  gpio_55_ps:5;
        RBus_UInt32  gpio_55_pu:1;
        RBus_UInt32  gpio_55_pd:1;
        RBus_UInt32  gpio_55_ds:1;
        RBus_UInt32  gpio_55_sr:1;
        RBus_UInt32  gpio_56_ps:5;
        RBus_UInt32  gpio_56_pu:1;
        RBus_UInt32  gpio_56_pd:1;
        RBus_UInt32  gpio_56_ds:1;
        RBus_UInt32  gpio_56_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_143_ps:5;
        RBus_UInt32  gpio_143_pu:1;
        RBus_UInt32  gpio_143_pd:1;
        RBus_UInt32  gpio_143_ds:1;
        RBus_UInt32  gpio_143_sr:1;
        RBus_UInt32  res1:23;
    };
}gpio_cfg_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_197_ps:5;
        RBus_UInt32  gpio_197_pu:1;
        RBus_UInt32  gpio_197_pd:1;
        RBus_UInt32  gpio_197_ds:1;
        RBus_UInt32  gpio_197_sr:1;
        RBus_UInt32  gpio_198_ps:5;
        RBus_UInt32  gpio_198_pu:1;
        RBus_UInt32  gpio_198_pd:1;
        RBus_UInt32  gpio_198_ds:1;
        RBus_UInt32  gpio_198_sr:1;
        RBus_UInt32  gpio_199_ps:5;
        RBus_UInt32  gpio_199_pu:1;
        RBus_UInt32  gpio_199_pd:1;
        RBus_UInt32  gpio_199_ds:1;
        RBus_UInt32  gpio_199_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_200_ps:5;
        RBus_UInt32  gpio_200_pu:1;
        RBus_UInt32  gpio_200_pd:1;
        RBus_UInt32  gpio_200_ds:1;
        RBus_UInt32  gpio_200_sr:1;
        RBus_UInt32  gpio_201_ps:5;
        RBus_UInt32  gpio_201_pu:1;
        RBus_UInt32  gpio_201_pd:1;
        RBus_UInt32  gpio_201_ds:1;
        RBus_UInt32  gpio_201_sr:1;
        RBus_UInt32  gpio_202_ps:5;
        RBus_UInt32  gpio_202_pu:1;
        RBus_UInt32  gpio_202_pd:1;
        RBus_UInt32  gpio_202_ds:1;
        RBus_UInt32  gpio_202_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_203_ps:5;
        RBus_UInt32  gpio_203_pu:1;
        RBus_UInt32  gpio_203_pd:1;
        RBus_UInt32  gpio_203_ds:1;
        RBus_UInt32  gpio_203_sr:1;
        RBus_UInt32  gpio_204_ps:5;
        RBus_UInt32  gpio_204_pu:1;
        RBus_UInt32  gpio_204_pd:1;
        RBus_UInt32  gpio_204_ds:1;
        RBus_UInt32  gpio_204_sr:1;
        RBus_UInt32  gpio_205_ps:5;
        RBus_UInt32  gpio_205_pu:1;
        RBus_UInt32  gpio_205_pd:1;
        RBus_UInt32  gpio_205_ds:1;
        RBus_UInt32  gpio_205_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_206_ps:5;
        RBus_UInt32  gpio_206_pu:1;
        RBus_UInt32  gpio_206_pd:1;
        RBus_UInt32  gpio_206_ds:1;
        RBus_UInt32  gpio_206_sr:1;
        RBus_UInt32  res1:23;
    };
}gpio_cfg_49_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_29_ps:5;
        RBus_UInt32  gpio_29_pu:1;
        RBus_UInt32  gpio_29_pd:1;
        RBus_UInt32  gpio_29_ds:1;
        RBus_UInt32  gpio_29_sr:1;
        RBus_UInt32  gpio_32_ps:5;
        RBus_UInt32  gpio_32_pu:1;
        RBus_UInt32  gpio_32_pd:1;
        RBus_UInt32  gpio_32_ds:1;
        RBus_UInt32  gpio_32_sr:1;
        RBus_UInt32  gpio_33_ps:5;
        RBus_UInt32  gpio_33_pu:1;
        RBus_UInt32  gpio_33_pd:1;
        RBus_UInt32  gpio_33_ds:1;
        RBus_UInt32  gpio_33_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_24_ps:5;
        RBus_UInt32  gpio_24_pu:1;
        RBus_UInt32  gpio_24_pd:1;
        RBus_UInt32  gpio_24_ds:1;
        RBus_UInt32  gpio_24_sr:1;
        RBus_UInt32  gpio_142_ps:5;
        RBus_UInt32  gpio_142_pu:1;
        RBus_UInt32  gpio_142_pd:1;
        RBus_UInt32  gpio_142_ds:1;
        RBus_UInt32  gpio_142_sr:1;
        RBus_UInt32  gpio_85_ps:5;
        RBus_UInt32  gpio_85_pu:1;
        RBus_UInt32  gpio_85_pd:1;
        RBus_UInt32  gpio_85_ds:1;
        RBus_UInt32  gpio_85_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_86_ps:5;
        RBus_UInt32  gpio_86_pu:1;
        RBus_UInt32  gpio_86_pd:1;
        RBus_UInt32  gpio_86_ds:1;
        RBus_UInt32  gpio_86_sr:1;
        RBus_UInt32  gpio_87_ps:5;
        RBus_UInt32  gpio_87_pu:1;
        RBus_UInt32  gpio_87_pd:1;
        RBus_UInt32  gpio_87_ds:1;
        RBus_UInt32  gpio_87_sr:1;
        RBus_UInt32  gpio_88_ps:5;
        RBus_UInt32  gpio_88_pu:1;
        RBus_UInt32  gpio_88_pd:1;
        RBus_UInt32  gpio_88_ds:1;
        RBus_UInt32  gpio_88_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_89_ps:5;
        RBus_UInt32  gpio_89_pu:1;
        RBus_UInt32  gpio_89_pd:1;
        RBus_UInt32  gpio_89_ds:1;
        RBus_UInt32  gpio_89_sr:1;
        RBus_UInt32  gpio_90_ps:5;
        RBus_UInt32  gpio_90_pu:1;
        RBus_UInt32  gpio_90_pd:1;
        RBus_UInt32  gpio_90_ds:1;
        RBus_UInt32  gpio_90_sr:1;
        RBus_UInt32  gpio_91_ps:5;
        RBus_UInt32  gpio_91_pu:1;
        RBus_UInt32  gpio_91_pd:1;
        RBus_UInt32  gpio_91_ds:1;
        RBus_UInt32  gpio_91_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_92_ps:5;
        RBus_UInt32  gpio_92_pu:1;
        RBus_UInt32  gpio_92_pd:1;
        RBus_UInt32  gpio_92_ds:1;
        RBus_UInt32  gpio_92_sr:1;
        RBus_UInt32  gpio_93_ps:5;
        RBus_UInt32  gpio_93_pu:1;
        RBus_UInt32  gpio_93_pd:1;
        RBus_UInt32  gpio_93_ds:1;
        RBus_UInt32  gpio_93_sr:1;
        RBus_UInt32  gpio_94_ps:5;
        RBus_UInt32  gpio_94_pu:1;
        RBus_UInt32  gpio_94_pd:1;
        RBus_UInt32  gpio_94_ds:1;
        RBus_UInt32  gpio_94_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_95_ps:5;
        RBus_UInt32  gpio_95_pu:1;
        RBus_UInt32  gpio_95_pd:1;
        RBus_UInt32  gpio_95_ds:1;
        RBus_UInt32  gpio_95_sr:1;
        RBus_UInt32  gpio_96_ps:5;
        RBus_UInt32  gpio_96_pu:1;
        RBus_UInt32  gpio_96_pd:1;
        RBus_UInt32  gpio_96_ds:1;
        RBus_UInt32  gpio_96_sr:1;
        RBus_UInt32  gpio_97_ps:5;
        RBus_UInt32  gpio_97_pu:1;
        RBus_UInt32  gpio_97_pd:1;
        RBus_UInt32  gpio_97_ds:1;
        RBus_UInt32  gpio_97_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_98_ps:5;
        RBus_UInt32  gpio_98_pu:1;
        RBus_UInt32  gpio_98_pd:1;
        RBus_UInt32  gpio_98_ds:1;
        RBus_UInt32  gpio_98_sr:1;
        RBus_UInt32  gpio_99_ps:5;
        RBus_UInt32  gpio_99_pu:1;
        RBus_UInt32  gpio_99_pd:1;
        RBus_UInt32  gpio_99_ds:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  gpio_100_ps:5;
        RBus_UInt32  gpio_100_pu:1;
        RBus_UInt32  gpio_100_pd:1;
        RBus_UInt32  gpio_100_ds:1;
        RBus_UInt32  gpio_100_sr:1;
        RBus_UInt32  res2:5;
    };
}gpio_cfg_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_101_ps:5;
        RBus_UInt32  gpio_101_pu:1;
        RBus_UInt32  gpio_101_pd:1;
        RBus_UInt32  gpio_101_ds:1;
        RBus_UInt32  gpio_101_sr:1;
        RBus_UInt32  gpio_102_ps:5;
        RBus_UInt32  gpio_102_pu:1;
        RBus_UInt32  gpio_102_pd:1;
        RBus_UInt32  gpio_102_ds:1;
        RBus_UInt32  gpio_102_sr:1;
        RBus_UInt32  gpio_103_ps:5;
        RBus_UInt32  gpio_103_pu:1;
        RBus_UInt32  gpio_103_pd:1;
        RBus_UInt32  gpio_103_ds:1;
        RBus_UInt32  gpio_103_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_104_ps:5;
        RBus_UInt32  gpio_104_pu:1;
        RBus_UInt32  gpio_104_pd:1;
        RBus_UInt32  gpio_104_ds:1;
        RBus_UInt32  gpio_104_sr:1;
        RBus_UInt32  gpio_105_ps:5;
        RBus_UInt32  gpio_105_pu:1;
        RBus_UInt32  gpio_105_pd:1;
        RBus_UInt32  gpio_105_ds:1;
        RBus_UInt32  gpio_105_sr:1;
        RBus_UInt32  gpio_106_ps:5;
        RBus_UInt32  gpio_106_pu:1;
        RBus_UInt32  gpio_106_pd:1;
        RBus_UInt32  gpio_106_ds:1;
        RBus_UInt32  gpio_106_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_107_ps:5;
        RBus_UInt32  gpio_107_pu:1;
        RBus_UInt32  gpio_107_pd:1;
        RBus_UInt32  gpio_107_ds:1;
        RBus_UInt32  gpio_107_sr:1;
        RBus_UInt32  gpio_108_ps:5;
        RBus_UInt32  gpio_108_pu:1;
        RBus_UInt32  gpio_108_pd:1;
        RBus_UInt32  gpio_108_ds:1;
        RBus_UInt32  gpio_108_sr:1;
        RBus_UInt32  res1:14;
    };
}gpio_cfg_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  gpio_169_ps:5;
        RBus_UInt32  gpio_169_pu:1;
        RBus_UInt32  gpio_169_pd:1;
        RBus_UInt32  gpio_169_ds:1;
        RBus_UInt32  gpio_169_sr:1;
        RBus_UInt32  gpio_170_ps:5;
        RBus_UInt32  gpio_170_pu:1;
        RBus_UInt32  gpio_170_pd:1;
        RBus_UInt32  gpio_170_ds:1;
        RBus_UInt32  gpio_170_sr:1;
        RBus_UInt32  res2:5;
    };
}gpio_cfg_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_171_ps:5;
        RBus_UInt32  gpio_171_pu:1;
        RBus_UInt32  gpio_171_pd:1;
        RBus_UInt32  gpio_171_ds:1;
        RBus_UInt32  gpio_171_sr:1;
        RBus_UInt32  gpio_172_ps:5;
        RBus_UInt32  gpio_172_pu:1;
        RBus_UInt32  gpio_172_pd:1;
        RBus_UInt32  gpio_172_ds:1;
        RBus_UInt32  gpio_172_sr:1;
        RBus_UInt32  gpio_173_ps:5;
        RBus_UInt32  gpio_173_pu:1;
        RBus_UInt32  gpio_173_pd:1;
        RBus_UInt32  gpio_173_ds:1;
        RBus_UInt32  gpio_173_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_174_ps:5;
        RBus_UInt32  gpio_174_pu:1;
        RBus_UInt32  gpio_174_pd:1;
        RBus_UInt32  gpio_174_ds:1;
        RBus_UInt32  gpio_174_sr:1;
        RBus_UInt32  gpio_175_ps:5;
        RBus_UInt32  gpio_175_pu:1;
        RBus_UInt32  gpio_175_pd:1;
        RBus_UInt32  gpio_175_ds:1;
        RBus_UInt32  gpio_175_sr:1;
        RBus_UInt32  gpio_176_ps:5;
        RBus_UInt32  gpio_176_pu:1;
        RBus_UInt32  gpio_176_pd:1;
        RBus_UInt32  gpio_176_ds:1;
        RBus_UInt32  gpio_176_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_177_ps:5;
        RBus_UInt32  gpio_177_pu:1;
        RBus_UInt32  gpio_177_pd:1;
        RBus_UInt32  gpio_177_ds:1;
        RBus_UInt32  gpio_177_sr:1;
        RBus_UInt32  gpio_178_ps:5;
        RBus_UInt32  gpio_178_pu:1;
        RBus_UInt32  gpio_178_pd:1;
        RBus_UInt32  gpio_178_ds:1;
        RBus_UInt32  gpio_178_sr:1;
        RBus_UInt32  gpio_179_ps:5;
        RBus_UInt32  gpio_179_pu:1;
        RBus_UInt32  gpio_179_pd:1;
        RBus_UInt32  gpio_179_ds:1;
        RBus_UInt32  gpio_179_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_180_ps:5;
        RBus_UInt32  gpio_180_pu:1;
        RBus_UInt32  gpio_180_pd:1;
        RBus_UInt32  gpio_180_ds:1;
        RBus_UInt32  gpio_180_sr:1;
        RBus_UInt32  gpio_181_ps:5;
        RBus_UInt32  gpio_181_pu:1;
        RBus_UInt32  gpio_181_pd:1;
        RBus_UInt32  gpio_181_ds:1;
        RBus_UInt32  gpio_181_sr:1;
        RBus_UInt32  gpio_182_ps:5;
        RBus_UInt32  gpio_182_pu:1;
        RBus_UInt32  gpio_182_pd:1;
        RBus_UInt32  gpio_182_ds:1;
        RBus_UInt32  gpio_182_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_183_ps:5;
        RBus_UInt32  gpio_183_pu:1;
        RBus_UInt32  gpio_183_pd:1;
        RBus_UInt32  gpio_183_ds:1;
        RBus_UInt32  gpio_183_sr:1;
        RBus_UInt32  gpio_184_ps:5;
        RBus_UInt32  gpio_184_pu:1;
        RBus_UInt32  gpio_184_pd:1;
        RBus_UInt32  gpio_184_ds:1;
        RBus_UInt32  gpio_184_sr:1;
        RBus_UInt32  gpio_185_ps:5;
        RBus_UInt32  gpio_185_pu:1;
        RBus_UInt32  gpio_185_pd:1;
        RBus_UInt32  gpio_185_ds:1;
        RBus_UInt32  gpio_185_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_186_ps:5;
        RBus_UInt32  gpio_186_pu:1;
        RBus_UInt32  gpio_186_pd:1;
        RBus_UInt32  gpio_186_ds:1;
        RBus_UInt32  gpio_186_sr:1;
        RBus_UInt32  gpio_187_ps:5;
        RBus_UInt32  gpio_187_pu:1;
        RBus_UInt32  gpio_187_pd:1;
        RBus_UInt32  gpio_187_ds:1;
        RBus_UInt32  gpio_187_sr:1;
        RBus_UInt32  gpio_188_ps:5;
        RBus_UInt32  gpio_188_pu:1;
        RBus_UInt32  gpio_188_pd:1;
        RBus_UInt32  gpio_188_ds:1;
        RBus_UInt32  gpio_188_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  gpio_150_ps:5;
        RBus_UInt32  gpio_150_pu:1;
        RBus_UInt32  gpio_150_pd:1;
        RBus_UInt32  gpio_150_ds:1;
        RBus_UInt32  gpio_150_sr:1;
        RBus_UInt32  gpio_151_ps:5;
        RBus_UInt32  gpio_151_pu:1;
        RBus_UInt32  gpio_151_pd:1;
        RBus_UInt32  gpio_151_ds:1;
        RBus_UInt32  gpio_151_sr:1;
        RBus_UInt32  res2:5;
    };
}gpio_cfg_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_152_ps:5;
        RBus_UInt32  gpio_152_pu:1;
        RBus_UInt32  gpio_152_pd:1;
        RBus_UInt32  gpio_152_ds:1;
        RBus_UInt32  gpio_152_sr:1;
        RBus_UInt32  gpio_153_ps:5;
        RBus_UInt32  gpio_153_pu:1;
        RBus_UInt32  gpio_153_pd:1;
        RBus_UInt32  gpio_153_ds:1;
        RBus_UInt32  gpio_153_sr:1;
        RBus_UInt32  gpio_154_ps:5;
        RBus_UInt32  gpio_154_pu:1;
        RBus_UInt32  gpio_154_pd:1;
        RBus_UInt32  gpio_154_ds:1;
        RBus_UInt32  gpio_154_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_155_ps:5;
        RBus_UInt32  gpio_155_pu:1;
        RBus_UInt32  gpio_155_pd:1;
        RBus_UInt32  gpio_155_ds:1;
        RBus_UInt32  gpio_155_sr:1;
        RBus_UInt32  gpio_156_ps:5;
        RBus_UInt32  gpio_156_pu:1;
        RBus_UInt32  gpio_156_pd:1;
        RBus_UInt32  gpio_156_ds:1;
        RBus_UInt32  gpio_156_sr:1;
        RBus_UInt32  gpio_157_ps:5;
        RBus_UInt32  gpio_157_pu:1;
        RBus_UInt32  gpio_157_pd:1;
        RBus_UInt32  gpio_157_ds:1;
        RBus_UInt32  gpio_157_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_158_ps:5;
        RBus_UInt32  gpio_158_pu:1;
        RBus_UInt32  gpio_158_pd:1;
        RBus_UInt32  gpio_158_ds:1;
        RBus_UInt32  gpio_158_sr:1;
        RBus_UInt32  gpio_159_ps:5;
        RBus_UInt32  gpio_159_pu:1;
        RBus_UInt32  gpio_159_pd:1;
        RBus_UInt32  gpio_159_ds:1;
        RBus_UInt32  gpio_159_sr:1;
        RBus_UInt32  gpio_160_ps:5;
        RBus_UInt32  gpio_160_pu:1;
        RBus_UInt32  gpio_160_pd:1;
        RBus_UInt32  gpio_160_ds:1;
        RBus_UInt32  gpio_160_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_161_ps:5;
        RBus_UInt32  gpio_161_pu:1;
        RBus_UInt32  gpio_161_pd:1;
        RBus_UInt32  gpio_161_ds:1;
        RBus_UInt32  gpio_161_sr:1;
        RBus_UInt32  gpio_162_ps:5;
        RBus_UInt32  gpio_162_pu:1;
        RBus_UInt32  gpio_162_pd:1;
        RBus_UInt32  gpio_162_ds:1;
        RBus_UInt32  gpio_162_sr:1;
        RBus_UInt32  gpio_163_ps:5;
        RBus_UInt32  gpio_163_pu:1;
        RBus_UInt32  gpio_163_pd:1;
        RBus_UInt32  gpio_163_ds:1;
        RBus_UInt32  gpio_163_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_164_ps:5;
        RBus_UInt32  gpio_164_pu:1;
        RBus_UInt32  gpio_164_pd:1;
        RBus_UInt32  gpio_164_ds:1;
        RBus_UInt32  gpio_164_sr:1;
        RBus_UInt32  gpio_165_ps:5;
        RBus_UInt32  gpio_165_pu:1;
        RBus_UInt32  gpio_165_pd:1;
        RBus_UInt32  gpio_165_ds:1;
        RBus_UInt32  gpio_165_sr:1;
        RBus_UInt32  res1:14;
    };
}gpio_cfg_51_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_189_ps:5;
        RBus_UInt32  gpio_189_pu:1;
        RBus_UInt32  gpio_189_pd:1;
        RBus_UInt32  gpio_189_ds:1;
        RBus_UInt32  gpio_189_sr:1;
        RBus_UInt32  gpio_190_ps:5;
        RBus_UInt32  gpio_190_pu:1;
        RBus_UInt32  gpio_190_pd:1;
        RBus_UInt32  gpio_190_ds:1;
        RBus_UInt32  gpio_190_sr:1;
        RBus_UInt32  gpio_191_ps:5;
        RBus_UInt32  gpio_191_pu:1;
        RBus_UInt32  gpio_191_pd:1;
        RBus_UInt32  gpio_191_ds:1;
        RBus_UInt32  gpio_191_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_3_ps:5;
        RBus_UInt32  gpio_3_pu:1;
        RBus_UInt32  gpio_3_pd:1;
        RBus_UInt32  gpio_3_ds:1;
        RBus_UInt32  gpio_3_sr:1;
        RBus_UInt32  gpio_4_ps:5;
        RBus_UInt32  gpio_4_pu:1;
        RBus_UInt32  gpio_4_pd:1;
        RBus_UInt32  gpio_4_ds:1;
        RBus_UInt32  gpio_4_sr:1;
        RBus_UInt32  gpio_145_ps:5;
        RBus_UInt32  gpio_145_pu:1;
        RBus_UInt32  gpio_145_pd:1;
        RBus_UInt32  gpio_145_ds:1;
        RBus_UInt32  gpio_145_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_146_ps:5;
        RBus_UInt32  gpio_146_pu:1;
        RBus_UInt32  gpio_146_pd:1;
        RBus_UInt32  gpio_146_ds:1;
        RBus_UInt32  gpio_146_sr:1;
        RBus_UInt32  gpio_147_ps:5;
        RBus_UInt32  gpio_147_pu:1;
        RBus_UInt32  gpio_147_pd:1;
        RBus_UInt32  gpio_147_ds:1;
        RBus_UInt32  gpio_147_sr:1;
        RBus_UInt32  gpio_148_ps:5;
        RBus_UInt32  gpio_148_pu:1;
        RBus_UInt32  gpio_148_pd:1;
        RBus_UInt32  gpio_148_ds:1;
        RBus_UInt32  gpio_148_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_149_ps:5;
        RBus_UInt32  gpio_149_pu:1;
        RBus_UInt32  gpio_149_pd:1;
        RBus_UInt32  gpio_149_ds:1;
        RBus_UInt32  gpio_149_sr:1;
        RBus_UInt32  res1:23;
    };
}gpio_cfg_39_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  gpio_166_ps:5;
        RBus_UInt32  gpio_166_pu:1;
        RBus_UInt32  gpio_166_pd:1;
        RBus_UInt32  gpio_166_ds:1;
        RBus_UInt32  gpio_166_sr:1;
        RBus_UInt32  res2:5;
    };
}gpio_cfg_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_167_ps:5;
        RBus_UInt32  gpio_167_pu:1;
        RBus_UInt32  gpio_167_pd:1;
        RBus_UInt32  gpio_167_ds:1;
        RBus_UInt32  gpio_167_sr:1;
        RBus_UInt32  gpio_168_ps:5;
        RBus_UInt32  gpio_168_pu:1;
        RBus_UInt32  gpio_168_pd:1;
        RBus_UInt32  gpio_168_ds:1;
        RBus_UInt32  gpio_168_sr:1;
        RBus_UInt32  gpio_144_ps:5;
        RBus_UInt32  gpio_144_pu:1;
        RBus_UInt32  gpio_144_pd:1;
        RBus_UInt32  gpio_144_ds:1;
        RBus_UInt32  gpio_144_sr:1;
        RBus_UInt32  res1:5;
    };
}gpio_cfg_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_a_hp_ps:5;
        RBus_UInt32  lvds_a_hn_ps:5;
        RBus_UInt32  lvds_a_gp_ps:5;
        RBus_UInt32  lvds_a_gn_ps:5;
        RBus_UInt32  lvds_a_fp_ps:5;
        RBus_UInt32  lvds_a_fn_ps:5;
        RBus_UInt32  res1:2;
    };
}lvds_cfg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_a_ep_ps:5;
        RBus_UInt32  lvds_a_en_ps:5;
        RBus_UInt32  lvds_a_dp_ps:5;
        RBus_UInt32  lvds_a_dn_ps:5;
        RBus_UInt32  lvds_a_cp_ps:5;
        RBus_UInt32  lvds_a_cn_ps:5;
        RBus_UInt32  res1:2;
    };
}lvds_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_a_bp_ps:5;
        RBus_UInt32  lvds_a_bn_ps:5;
        RBus_UInt32  lvds_a_ap_ps:5;
        RBus_UInt32  lvds_a_an_ps:5;
        RBus_UInt32  lvds_b_gp_ps:5;
        RBus_UInt32  lvds_b_gn_ps:5;
        RBus_UInt32  res1:2;
    };
}lvds_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_b_fp_ps:5;
        RBus_UInt32  lvds_b_fn_ps:5;
        RBus_UInt32  lvds_b_ep_ps:5;
        RBus_UInt32  lvds_b_en_ps:5;
        RBus_UInt32  lvds_b_dp_ps:5;
        RBus_UInt32  lvds_b_dn_ps:5;
        RBus_UInt32  res1:2;
    };
}lvds_cfg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lvds_b_cp_ps:5;
        RBus_UInt32  lvds_b_cn_ps:5;
        RBus_UInt32  lvds_b_bp_ps:5;
        RBus_UInt32  lvds_b_bn_ps:5;
        RBus_UInt32  lvds_b_ap_ps:5;
        RBus_UInt32  lvds_b_an_ps:5;
        RBus_UInt32  res1:2;
    };
}lvds_cfg_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_ps:5;
        RBus_UInt32  hsync_ps:5;
        RBus_UInt32  res1:20;
        RBus_UInt32  vsync_gpi_en:1;
        RBus_UInt32  hsync_gpi_en:1;
    };
}hv_cfg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_0p_ps:5;
        RBus_UInt32  vin_bn_ps:5;
        RBus_UInt32  vin_1p_ps:5;
        RBus_UInt32  vin_2p_ps:5;
        RBus_UInt32  res1:8;
        RBus_UInt32  vin_0p_gpi_en:1;
        RBus_UInt32  vin_bn_gpi_en:1;
        RBus_UInt32  vin_1p_gpi_en:1;
        RBus_UInt32  vin_2p_gpi_en:1;
    };
}ypp_adc_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_6p_ps:5;
        RBus_UInt32  vin_y1n_ps:5;
        RBus_UInt32  vin_7p_ps:5;
        RBus_UInt32  vin_8p_ps:5;
        RBus_UInt32  res1:8;
        RBus_UInt32  vin_6p_gpi_en:1;
        RBus_UInt32  vin_y1n_gpi_en:1;
        RBus_UInt32  vin_7p_gpi_en:1;
        RBus_UInt32  vin_8p_gpi_en:1;
    };
}ypp_adc_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_9p_ps:5;
        RBus_UInt32  vin_12p_ps:5;
        RBus_UInt32  vin_a0n_ps:5;
        RBus_UInt32  vin_a2n_ps:5;
        RBus_UInt32  vin_10p_ps:5;
        RBus_UInt32  res1:2;
        RBus_UInt32  vin_9p_gpi_en:1;
        RBus_UInt32  vin_12p_gpi_en:1;
        RBus_UInt32  vin_a0n_gpi_en:1;
        RBus_UInt32  vin_a2n_gpi_en:1;
        RBus_UInt32  vin_10p_gpi_en:1;
    };
}adc_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_13p_ps:5;
        RBus_UInt32  res1:26;
        RBus_UInt32  vin_13p_gpi_en:1;
    };
}adc_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scart_fsw_0_ps:5;
        RBus_UInt32  vdbs_out_ps:5;
        RBus_UInt32  vdac_out_ps:5;
        RBus_UInt32  res1:14;
        RBus_UInt32  scart_fsw_0_gpi_en:1;
        RBus_UInt32  vdbs_out_gpi_en:1;
        RBus_UInt32  vdac_out_gpi_en:1;
    };
}scart_fsw_cfg_vd_dac_cfg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bb_ai2l_ps:5;
        RBus_UInt32  bb_ai2r_ps:5;
        RBus_UInt32  bb_ai3l_ps:5;
        RBus_UInt32  bb_ai3r_ps:5;
        RBus_UInt32  bb_ai4l_ps:5;
        RBus_UInt32  res1:2;
        RBus_UInt32  bb_ai2l_gpi_en:1;
        RBus_UInt32  bb_ai2r_gpi_en:1;
        RBus_UInt32  bb_ai3l_gpi_en:1;
        RBus_UInt32  bb_ai3r_gpi_en:1;
        RBus_UInt32  bb_ai4l_gpi_en:1;
    };
}bb_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bb_ai4r_ps:5;
        RBus_UInt32  bb_aiol_ps:5;
        RBus_UInt32  bb_aior_ps:5;
        RBus_UInt32  bb_hpol_ps:5;
        RBus_UInt32  bb_hpor_ps:5;
        RBus_UInt32  res1:2;
        RBus_UInt32  bb_ai4r_gpi_en:1;
        RBus_UInt32  bb_aiol_gpi_en:1;
        RBus_UInt32  bb_aior_gpi_en:1;
        RBus_UInt32  bb_hpol_gpi_en:1;
        RBus_UInt32  bb_hpor_gpi_en:1;
    };
}bb_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bb_dio1_ps:5;
        RBus_UInt32  bb_dio2_ps:5;
        RBus_UInt32  bb_dio3_ps:5;
        RBus_UInt32  usb3_hsdm_pshsdp_2_apad:5;
        RBus_UInt32  usb3_hsdp_pshsdm_2_apad:5;
        RBus_UInt32  res1:2;
        RBus_UInt32  bb_dio1_ps_gpi_en:1;
        RBus_UInt32  bb_dio2_ps_gpi_en:1;
        RBus_UInt32  bb_dio3_ps_gpi_en:1;
        RBus_UInt32  usb3_hsdm_gpi_en:1;
        RBus_UInt32  usb3_hsdp_gpi_en:1;
    };
}bb_usb_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_40_ie_v18:1;
        RBus_UInt32  gpio_52_ie_v18:1;
        RBus_UInt32  gpio_86_ie_v18:1;
        RBus_UInt32  uart2_rxdi_sel:3;
        RBus_UInt32  uart2_cts_n_sel:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  uart1_rxdi_sel:3;
        RBus_UInt32  uart1_cts_n_sel:2;
        RBus_UInt32  tp2_mux_selection:2;
        RBus_UInt32  tp1_mux_selection:2;
        RBus_UInt32  tp0_mux_selection:2;
        RBus_UInt32  i2c2_in_sel:4;
        RBus_UInt32  res2:1;
        RBus_UInt32  i2c1_in_sel:3;
        RBus_UInt32  res3:4;
    };
}pin_mux_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ld_spi1_p2_sck_in_sel:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  ld_spi1_p3_sdo_in_sel:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  ld_spi1_p4_sdi_sel:4;
        RBus_UInt32  res3:1;
        RBus_UInt32  ld_spi0_p2_sck_in_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  ld_spi0_p3_sdo_in_sel:3;
        RBus_UInt32  ld_spi0_p4_sdi_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  anttx_in_sel:2;
        RBus_UInt32  antrx_in_sel:2;
        RBus_UInt32  antoe_in_sel:2;
    };
}pin_mux_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  spdif_in_sel:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  epi_lock_sel:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  usb_pwr_flag0_in_sel:2;
        RBus_UInt32  usb_pwr_flag1_in_sel:2;
        RBus_UInt32  usb_pwr_flag2_in_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  vby1_htpd_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  vby1_lock_sel:3;
        RBus_UInt32  res5:8;
        RBus_UInt32  phif_enable:1;
    };
}pin_mux_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  uni_pwm_7_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  uni_pwm_6_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  uni_pwm_5_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  uni_pwm_4_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  uni_pwm_3_sel:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  uni_pwm_2_sel:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  uni_pwm_1_sel:3;
        RBus_UInt32  res8:1;
        RBus_UInt32  uni_pwm_0_sel:3;
    };
}pin_mux_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  sc0_cd_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  sc0_d0_in_sel:3;
        RBus_UInt32  res3:10;
        RBus_UInt32  sc1_cd_sel:4;
        RBus_UInt32  res4:1;
        RBus_UInt32  sc1_d0_in_sel:4;
        RBus_UInt32  res5:5;
    };
}pin_mux_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  cr_sd_cmd_in_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  cr_sd_wp_sel:4;
        RBus_UInt32  res3:1;
        RBus_UInt32  cr_sd_cd_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  cr_sd_d0_in_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  cr_sd_d1_in_sel:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  cr_sd_d2_in_sel:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  cr_sd_d3_in_sel:3;
        RBus_UInt32  res8:3;
    };
}pin_mux_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  emmc_cmd_in_sel:3;
        RBus_UInt32  emmc_d0_in_sel:2;
        RBus_UInt32  emmc_d1_in_sel:2;
        RBus_UInt32  emmc_d2_in_sel:2;
        RBus_UInt32  emmc_d3_in_sel:2;
        RBus_UInt32  emmc_d4_in_sel:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  emmc_d5_in_sel:2;
        RBus_UInt32  emmc_d6_in_sel:2;
        RBus_UInt32  emmc_d7_in_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  hddc0_sda_in_sel:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  hddc0_scl_sel:2;
        RBus_UInt32  res5:5;
    };
}pin_mux_ctrl6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  tp1_clk_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  tp1_sync_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  tp1_val_sel:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  tp1_d0_sel:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  mii_mdio_in_sel:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  mii_rxer_sel:3;
        RBus_UInt32  mii_crs_sel:2;
        RBus_UInt32  res7:1;
        RBus_UInt32  mii_rxdv_sel:3;
        RBus_UInt32  res8:1;
        RBus_UInt32  mii_rxd0_sel:2;
        RBus_UInt32  res9:1;
        RBus_UInt32  mii_rxd1_sel:2;
        RBus_UInt32  res10:1;
        RBus_UInt32  mii_rxd2_sel:3;
        RBus_UInt32  res11:1;
    };
}pin_mux_ctrl7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  mii_rxd3_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  mii_rxc_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  mii_txc_sel:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  mii_col_sel:3;
        RBus_UInt32  res5:18;
    };
}pin_mux_ctrl8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  tp2_clk_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  tp2_sync_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  tp2_val_sel:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  tp2_d0_sel:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  tp2_err_sel:1;
        RBus_UInt32  res6:3;
        RBus_UInt32  gspi_sclk_in_sel:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  gspi_di_in_sel:3;
        RBus_UInt32  res8:1;
        RBus_UInt32  gspi_cs_in_sel:3;
        RBus_UInt32  res9:1;
        RBus_UInt32  gspi_do_in_sel:3;
        RBus_UInt32  res10:4;
    };
}pin_mux_ctrl9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  tp0_d0_sel:2;
        RBus_UInt32  tp0_d1_sel:2;
        RBus_UInt32  tp0_d2_sel:2;
        RBus_UInt32  tp0_d3_sel:2;
        RBus_UInt32  tp0_d4_sel:2;
        RBus_UInt32  tp0_d5_sel:2;
        RBus_UInt32  tp0_d6_sel:2;
        RBus_UInt32  tp0_d7_sel:2;
        RBus_UInt32  tp0_clk_sel:2;
        RBus_UInt32  tp0_val_sel:2;
        RBus_UInt32  tp0_sync_sel:2;
        RBus_UInt32  res2:9;
    };
}pin_mux_ctr20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcmcia_d0_in_sel:2;
        RBus_UInt32  pcmcia_d1_in_sel:2;
        RBus_UInt32  pcmcia_d2_in_sel:2;
        RBus_UInt32  pcmcia_d3_in_sel:2;
        RBus_UInt32  pcmcia_d4_in_sel:2;
        RBus_UInt32  pcmcia_d5_in_sel:2;
        RBus_UInt32  pcmcia_d6_in_sel:2;
        RBus_UInt32  pcmcia_d7_in_sel:2;
        RBus_UInt32  pcmcia_inpack0_n_sel:2;
        RBus_UInt32  pcmcia_cd0_n_sel:2;
        RBus_UInt32  pcmcia_ireq0_n_sel:2;
        RBus_UInt32  pcmcia_wait0_n_sel:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  pcmcia_inpack1_n_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  pcmcia_ireq1_n_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  pcmcia_wait1_n_sel:1;
        RBus_UInt32  pcmcia_cd1_n_sel:2;
    };
}pin_mux_ctr21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  rf_if_smt:1;
        RBus_UInt32  tuner_scl_smt:1;
        RBus_UInt32  tuner_sda_smt:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  gpio_5_smt:1;
        RBus_UInt32  gpio_6_smt:1;
        RBus_UInt32  gpio_7_smt:1;
        RBus_UInt32  gpio_8_smt:1;
        RBus_UInt32  gpio_9_smt:1;
        RBus_UInt32  gpio_10_smt:1;
        RBus_UInt32  gpio_11_smt:1;
        RBus_UInt32  gpio_12_smt:1;
        RBus_UInt32  gpio_13_smt:1;
        RBus_UInt32  gpio_14_smt:1;
        RBus_UInt32  gpio_15_smt:1;
        RBus_UInt32  gpio_16_smt:1;
        RBus_UInt32  gpio_17_smt:1;
        RBus_UInt32  gpio_18_smt:1;
        RBus_UInt32  gpio_19_smt:1;
        RBus_UInt32  gpio_20_smt:1;
        RBus_UInt32  gpio_22_smt:1;
        RBus_UInt32  gpio_21_smt:1;
        RBus_UInt32  gpio_23_smt:1;
        RBus_UInt32  res3:6;
    };
}schmidt_trigger_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_25_smt:1;
        RBus_UInt32  gpio_26_smt:1;
        RBus_UInt32  gpio_27_smt:1;
        RBus_UInt32  gpio_28_smt:1;
        RBus_UInt32  gpio_39_smt:1;
        RBus_UInt32  gpio_40_smt:1;
        RBus_UInt32  gpio_41_smt:1;
        RBus_UInt32  gpio_42_smt:1;
        RBus_UInt32  gpio_35_smt:1;
        RBus_UInt32  gpio_30_smt:1;
        RBus_UInt32  gpio_31_smt:1;
        RBus_UInt32  gpio_34_smt:1;
        RBus_UInt32  gpio_36_smt:1;
        RBus_UInt32  gpio_37_smt:1;
        RBus_UInt32  gpio_38_smt:1;
        RBus_UInt32  gpio_43_smt:1;
        RBus_UInt32  gpio_44_smt:1;
        RBus_UInt32  gpio_45_smt:1;
        RBus_UInt32  gpio_46_smt:1;
        RBus_UInt32  gpio_47_smt:1;
        RBus_UInt32  gpio_48_smt:1;
        RBus_UInt32  gpio_49_smt:1;
        RBus_UInt32  gpio_50_smt:1;
        RBus_UInt32  gpio_51_smt:1;
        RBus_UInt32  gpio_52_smt:1;
        RBus_UInt32  gpio_143_smt:1;
        RBus_UInt32  gpio_55_smt:1;
        RBus_UInt32  gpio_56_smt:1;
        RBus_UInt32  gpio_53_smt:1;
        RBus_UInt32  gpio_54_smt:1;
        RBus_UInt32  res1:2;
    };
}schmidt_trigger_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_29_smt:1;
        RBus_UInt32  gpio_32_smt:1;
        RBus_UInt32  gpio_33_smt:1;
        RBus_UInt32  gpio_24_smt:1;
        RBus_UInt32  gpio_142_smt:1;
        RBus_UInt32  res1:27;
    };
}schmidt_trigger_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_85_smt:1;
        RBus_UInt32  gpio_86_smt:1;
        RBus_UInt32  gpio_87_smt:1;
        RBus_UInt32  gpio_88_smt:1;
        RBus_UInt32  gpio_89_smt:1;
        RBus_UInt32  gpio_90_smt:1;
        RBus_UInt32  gpio_91_smt:1;
        RBus_UInt32  gpio_92_smt:1;
        RBus_UInt32  gpio_93_smt:1;
        RBus_UInt32  gpio_94_smt:1;
        RBus_UInt32  gpio_95_smt:1;
        RBus_UInt32  gpio_96_smt:1;
        RBus_UInt32  gpio_97_smt:1;
        RBus_UInt32  gpio_98_smt:1;
        RBus_UInt32  gpio_99_smt:1;
        RBus_UInt32  gpio_100_smt:1;
        RBus_UInt32  gpio_101_smt:1;
        RBus_UInt32  gpio_102_smt:1;
        RBus_UInt32  gpio_103_smt:1;
        RBus_UInt32  gpio_104_smt:1;
        RBus_UInt32  gpio_105_smt:1;
        RBus_UInt32  gpio_106_smt:1;
        RBus_UInt32  gpio_107_smt:1;
        RBus_UInt32  gpio_108_smt:1;
        RBus_UInt32  res1:8;
    };
}schmidt_trigger_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_169_smt:1;
        RBus_UInt32  gpio_170_smt:1;
        RBus_UInt32  gpio_171_smt:1;
        RBus_UInt32  gpio_172_smt:1;
        RBus_UInt32  gpio_173_smt:1;
        RBus_UInt32  gpio_174_smt:1;
        RBus_UInt32  gpio_175_smt:1;
        RBus_UInt32  gpio_176_smt:1;
        RBus_UInt32  gpio_177_smt:1;
        RBus_UInt32  gpio_178_smt:1;
        RBus_UInt32  gpio_179_smt:1;
        RBus_UInt32  gpio_180_smt:1;
        RBus_UInt32  gpio_181_smt:1;
        RBus_UInt32  gpio_182_smt:1;
        RBus_UInt32  gpio_183_smt:1;
        RBus_UInt32  gpio_184_smt:1;
        RBus_UInt32  gpio_185_smt:1;
        RBus_UInt32  gpio_186_smt:1;
        RBus_UInt32  gpio_187_smt:1;
        RBus_UInt32  gpio_188_smt:1;
        RBus_UInt32  gpio_197_smt:1;
        RBus_UInt32  gpio_198_smt:1;
        RBus_UInt32  gpio_199_smt:1;
        RBus_UInt32  gpio_200_smt:1;
        RBus_UInt32  gpio_201_smt:1;
        RBus_UInt32  gpio_202_smt:1;
        RBus_UInt32  gpio_203_smt:1;
        RBus_UInt32  gpio_204_smt:1;
        RBus_UInt32  gpio_205_smt:1;
        RBus_UInt32  gpio_206_smt:1;
        RBus_UInt32  res1:2;
    };
}schmidt_trigger_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gpio_189_smt:1;
        RBus_UInt32  gpio_190_smt:1;
        RBus_UInt32  gpio_191_smt:1;
        RBus_UInt32  gpio_3_smt:1;
        RBus_UInt32  gpio_4_smt:1;
        RBus_UInt32  gpio_145_smt:1;
        RBus_UInt32  gpio_146_smt:1;
        RBus_UInt32  gpio_147_smt:1;
        RBus_UInt32  gpio_148_smt:1;
        RBus_UInt32  gpio_149_smt:1;
        RBus_UInt32  gpio_150_smt:1;
        RBus_UInt32  gpio_151_smt:1;
        RBus_UInt32  gpio_152_smt:1;
        RBus_UInt32  gpio_153_smt:1;
        RBus_UInt32  gpio_154_smt:1;
        RBus_UInt32  gpio_155_smt:1;
        RBus_UInt32  gpio_156_smt:1;
        RBus_UInt32  gpio_157_smt:1;
        RBus_UInt32  gpio_158_smt:1;
        RBus_UInt32  gpio_159_smt:1;
        RBus_UInt32  gpio_160_smt:1;
        RBus_UInt32  gpio_161_smt:1;
        RBus_UInt32  gpio_162_smt:1;
        RBus_UInt32  gpio_163_smt:1;
        RBus_UInt32  gpio_164_smt:1;
        RBus_UInt32  gpio_165_smt:1;
        RBus_UInt32  gpio_166_smt:1;
        RBus_UInt32  gpio_167_smt:1;
        RBus_UInt32  gpio_168_smt:1;
        RBus_UInt32  gpio_144_smt:1;
        RBus_UInt32  res1:2;
    };
}schmidt_trigger_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  main_ext_clk_en:8;
        RBus_UInt32  testpin_mux:8;
    };
}main_test_pin_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_a1_pi_phsel_78:12;
        RBus_UInt32  plt_a1_sel_2xi_78:1;
        RBus_UInt32  plt_a2_pi_phsel_78:12;
        RBus_UInt32  plt_a2_sel_2xi_78:1;
        RBus_UInt32  plt_a_pi_freq_78:2;
        RBus_UInt32  res1:3;
        RBus_UInt32  plt_sel_v25:1;
    };
}lvdsepi_phy_78_ctrl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_b1_pi_phsel_78:12;
        RBus_UInt32  plt_b1_sel_2xi_78:1;
        RBus_UInt32  plt_b2_pi_phsel_78:12;
        RBus_UInt32  plt_b2_sel_2xi_78:1;
        RBus_UInt32  plt_b_pi_freq_78:2;
        RBus_UInt32  res1:4;
    };
}lvdsepi_phy_78_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_ab_pi_phsel_78:12;
        RBus_UInt32  plt_ab_freq_78:2;
        RBus_UInt32  plt_ab_sel_2xi_78:1;
        RBus_UInt32  plt_ck5xp_duty_78:2;
        RBus_UInt32  plt_ck5xn_duty_78:2;
        RBus_UInt32  res1:13;
    };
}lvdsepi_phy_78_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_cmu_big_kvco_78:1;
        RBus_UInt32  plt_cmu_ckpixel_inv_78:1;
        RBus_UInt32  plt_cmu_ck_ref_inv_78:1;
        RBus_UInt32  plt_cmu_cp_new_78:1;
        RBus_UInt32  plt_cmu_div248_78:2;
        RBus_UInt32  plt_cmu_loop_divn_78:8;
        RBus_UInt32  plt_cmu_sel_cp_i_78:5;
        RBus_UInt32  plt_cmu_sel_sc_78:1;
        RBus_UInt32  plt_cmu_sel_sr_78:3;
        RBus_UInt32  plt_cmu_sel_vldo_78:2;
        RBus_UInt32  plt_en_test_78:1;
        RBus_UInt32  plt_cmu_a_pi_bypass:1;
        RBus_UInt32  plt_cmu_b_pi_bypass:1;
        RBus_UInt32  res1:4;
    };
}lvdsepi_phy_78_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txlap_mode_78:3;
        RBus_UInt32  plt_p0_txlan_mode_78:3;
        RBus_UInt32  plt_p0_txla_ckphs_78:2;
        RBus_UInt32  plt_p0_txla_sel_emp_78:3;
        RBus_UInt32  plt_p0_txla_sr_78:2;
        RBus_UInt32  plt_p0_txla_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txlbp_mode_78:3;
        RBus_UInt32  plt_p0_txlbn_mode_78:3;
        RBus_UInt32  plt_p0_txlb_ckphs_78:2;
        RBus_UInt32  plt_p0_txlb_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlb_sr_78:2;
        RBus_UInt32  plt_p0_txlb_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txlcp_mode_78:3;
        RBus_UInt32  plt_p0_txlcn_mode_78:3;
        RBus_UInt32  plt_p0_txlc_ckphs_78:2;
        RBus_UInt32  plt_p0_txlc_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlc_sr_78:2;
        RBus_UInt32  plt_p0_txlc_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txldp_mode_78:3;
        RBus_UInt32  plt_p0_txldn_mode_78:3;
        RBus_UInt32  plt_p0_txld_ckphs_78:2;
        RBus_UInt32  plt_p0_txld_sel_emp_78:3;
        RBus_UInt32  plt_p0_txld_sr_78:2;
        RBus_UInt32  plt_p0_txld_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txlep_mode_78:3;
        RBus_UInt32  plt_p0_txlen_mode_78:3;
        RBus_UInt32  plt_p0_txle_ckphs_78:2;
        RBus_UInt32  plt_p0_txle_sel_emp_78:3;
        RBus_UInt32  plt_p0_txle_sr_78:2;
        RBus_UInt32  plt_p0_txle_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txlfp_mode_78:3;
        RBus_UInt32  plt_p0_txlfn_mode_78:3;
        RBus_UInt32  plt_p0_txlf_ckphs_78:2;
        RBus_UInt32  plt_p0_txlf_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlf_sr_78:2;
        RBus_UInt32  plt_p0_txlf_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txlgp_mode_78:3;
        RBus_UInt32  plt_p0_txlgn_mode_78:3;
        RBus_UInt32  plt_p0_txlg_ckphs_78:2;
        RBus_UInt32  plt_p0_txlg_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlg_sr_78:2;
        RBus_UInt32  plt_p0_txlg_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txlhp_mode_78:3;
        RBus_UInt32  plt_p0_txlhn_mode_78:3;
        RBus_UInt32  plt_p0_txlh_ckphs_78:2;
        RBus_UInt32  plt_p0_txlh_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlh_sr_78:2;
        RBus_UInt32  plt_p0_txlh_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txl_ck7x_delay_78:2;
        RBus_UInt32  plt_p0_txl_ck7x_inv_78:1;
        RBus_UInt32  plt_p0_txl_ck7x_lag_78:1;
        RBus_UInt32  plt_p0_txl_cm_mode_78:1;
        RBus_UInt32  plt_p0_txl_ib2x_78:8;
        RBus_UInt32  res1:19;
    };
}lvdsepi_phy_78_ctrl_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txlap_mode_78:3;
        RBus_UInt32  plt_p1_txlan_mode_78:3;
        RBus_UInt32  plt_p1_txla_ckphs_78:2;
        RBus_UInt32  plt_p1_txla_sel_emp_78:3;
        RBus_UInt32  plt_p1_txla_sr_78:2;
        RBus_UInt32  plt_p1_txla_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txlbp_mode_78:3;
        RBus_UInt32  plt_p1_txlbn_mode_78:3;
        RBus_UInt32  plt_p1_txlb_ckphs_78:2;
        RBus_UInt32  plt_p1_txlb_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlb_sr_78:2;
        RBus_UInt32  plt_p1_txlb_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txlcp_mode_78:3;
        RBus_UInt32  plt_p1_txlcn_mode_78:3;
        RBus_UInt32  plt_p1_txlc_ckphs_78:2;
        RBus_UInt32  plt_p1_txlc_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlc_sr_78:2;
        RBus_UInt32  plt_p1_txlc_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txldp_mode_78:3;
        RBus_UInt32  plt_p1_txldn_mode_78:3;
        RBus_UInt32  plt_p1_txld_ckphs_78:2;
        RBus_UInt32  plt_p1_txld_sel_emp_78:3;
        RBus_UInt32  plt_p1_txld_sr_78:2;
        RBus_UInt32  plt_p1_txld_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txlep_mode_78:3;
        RBus_UInt32  plt_p1_txlen_mode_78:3;
        RBus_UInt32  plt_p1_txle_ckphs_78:2;
        RBus_UInt32  plt_p1_txle_sel_emp_78:3;
        RBus_UInt32  plt_p1_txle_sr_78:2;
        RBus_UInt32  plt_p1_txle_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txlfp_mode_78:3;
        RBus_UInt32  plt_p1_txlfn_mode_78:3;
        RBus_UInt32  plt_p1_txlf_ckphs_78:2;
        RBus_UInt32  plt_p1_txlf_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlf_sr_78:2;
        RBus_UInt32  plt_p1_txlf_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txlgp_mode_78:3;
        RBus_UInt32  plt_p1_txlgn_mode_78:3;
        RBus_UInt32  plt_p1_txlg_ckphs_78:2;
        RBus_UInt32  plt_p1_txlg_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlg_sr_78:2;
        RBus_UInt32  plt_p1_txlg_term_78:2;
        RBus_UInt32  res1:17;
    };
}lvdsepi_phy_78_ctrl_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txl_ck7x_delay_78:2;
        RBus_UInt32  plt_p1_txl_ck7x_inv_78:1;
        RBus_UInt32  plt_p1_txl_ck7x_lag_78:1;
        RBus_UInt32  plt_p1_txl_cm_mode_78:1;
        RBus_UInt32  plt_p1_txl_ib2x_78:7;
        RBus_UInt32  res1:20;
    };
}lvdsepi_phy_78_ctrl_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_sel_isource_78:1;
        RBus_UInt32  plt_sel_mode_78:1;
        RBus_UInt32  plt_sel_test_78:2;
        RBus_UInt32  plt_sel_txl_vldo_78:2;
        RBus_UInt32  plt_sel_tx_i_78:4;
        RBus_UInt32  plt_sel_vcm_78:5;
        RBus_UInt32  vcckoff_33v_78:1;
        RBus_UInt32  plt_en_lv_ldo_78:1;
        RBus_UInt32  plt_en_txl_ldo_78:1;
        RBus_UInt32  plt_sel_lv_vldo_78:2;
        RBus_UInt32  res1:12;
    };
}lvdsepi_phy_78_ctrl_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_ttl_str_78:1;
        RBus_UInt32  plt_p0_txl_ck1x_delay_78:2;
        RBus_UInt32  plt_p0_txl_cml_str_78:8;
        RBus_UInt32  plt_p0_txl_en_emp_78:8;
        RBus_UInt32  plt_p0_txl_en_term_78:8;
        RBus_UInt32  res1:5;
    };
}lvdsepi_phy_78_ctrl_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txl_pre_drv_78:8;
        RBus_UInt32  plt_p0_txl_sr_td_78:8;
        RBus_UInt32  res1:16;
    };
}lvdsepi_phy_78_ctrl_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_ttl_str_78:1;
        RBus_UInt32  plt_p1_txl_ck1x_delay_78:2;
        RBus_UInt32  plt_p1_txl_cml_str_78:7;
        RBus_UInt32  plt_p1_txl_en_emp_78:7;
        RBus_UInt32  plt_p1_txl_en_term_78:7;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txl_pre_drv_78:7;
        RBus_UInt32  plt_p1_txl_sr_td_78:7;
        RBus_UInt32  res1:18;
    };
}lvdsepi_phy_78_ctrl_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_dummy_78_63_32:32;
    };
}lvdsepi_phy_78_ctrl_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_dummy_78_31_0:32;
    };
}lvdsepi_phy_78_ctrl_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_dummy_78_55_32:24;
    };
}lvdsepi_phy_78_ctrl_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_dummy_78_31_0:32;
    };
}lvdsepi_phy_78_ctrl_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pow_plt_78:1;
        RBus_UInt32  pow_plt_p0_txl_78:8;
        RBus_UInt32  pow_plt_p1_txl_78:7;
        RBus_UInt32  pow_plt_p0_txv_78:8;
        RBus_UInt32  res1:1;
        RBus_UInt32  pow_plt_p1_txv_78:7;
    };
}lvdsepi_phy_78_ctrl_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txv_en_emp:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  plt_p0_txv_en_term:8;
    };
}lvdsepi_phy_78_ctrl_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txva_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txva_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txva_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txva_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txva_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txva_vgate:3;
    };
}lvdsepi_phy_78_ctrl_32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txvb_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvb_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvb_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvb_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvb_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvb_vgate:3;
    };
}lvdsepi_phy_78_ctrl_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txvc_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvc_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvc_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvc_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvc_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvc_vgate:3;
    };
}lvdsepi_phy_78_ctrl_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txvd_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvd_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvd_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvd_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvd_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvd_vgate:3;
    };
}lvdsepi_phy_78_ctrl_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txve_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txve_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txve_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txve_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txve_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txve_vgate:3;
    };
}lvdsepi_phy_78_ctrl_36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txvf_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvf_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvf_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvf_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvf_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvf_vgate:3;
    };
}lvdsepi_phy_78_ctrl_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txvg_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvg_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvg_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvg_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvg_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvg_vgate:3;
    };
}lvdsepi_phy_78_ctrl_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p0_txvh_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvh_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvh_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvh_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvh_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvh_vgate:3;
    };
}lvdsepi_phy_78_ctrl_39_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  plt_p1_txv_en_emp:7;
        RBus_UInt32  res2:9;
        RBus_UInt32  plt_p1_txv_en_term:7;
    };
}lvdsepi_phy_78_ctrl_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txva_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txva_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txva_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txva_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txva_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txva_vgate:3;
    };
}lvdsepi_phy_78_ctrl_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txvb_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvb_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvb_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvb_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvb_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvb_vgate:3;
    };
}lvdsepi_phy_78_ctrl_42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txvc_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvc_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvc_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvc_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvc_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvc_vgate:3;
    };
}lvdsepi_phy_78_ctrl_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txvd_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvd_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvd_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvd_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvd_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvd_vgate:3;
    };
}lvdsepi_phy_78_ctrl_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txve_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txve_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txve_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txve_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txve_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txve_vgate:3;
    };
}lvdsepi_phy_78_ctrl_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txvf_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvf_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvf_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvf_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvf_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvf_vgate:3;
    };
}lvdsepi_phy_78_ctrl_46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txvg_amp:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvg_driver:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvg_emp:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvg_slew:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvg_term:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvg_vgate:3;
    };
}lvdsepi_phy_78_ctrl_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_repeat:1;
        RBus_UInt32  bist_tp_sel:1;
        RBus_UInt32  delay_sel0:3;
        RBus_UInt32  delay_sel1:3;
        RBus_UInt32  delay_sel2:3;
        RBus_UInt32  delay_sel3:3;
        RBus_UInt32  res1:12;
        RBus_UInt32  tp_type_sel:1;
        RBus_UInt32  scramble_default:1;
        RBus_UInt32  txbist_mode:2;
        RBus_UInt32  prbs_sel:1;
        RBus_UInt32  x1x2_sel:1;
    };
}vby1_d_phy0_txbist_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reserved_txbist_01:4;
        RBus_UInt32  enhance_mode:1;
        RBus_UInt32  prbs_reverse:1;
        RBus_UInt32  scramble_dis:1;
        RBus_UInt32  pn_swap:1;
        RBus_UInt32  bist_seed:8;
        RBus_UInt32  packet_length:8;
        RBus_UInt32  packet_number:8;
    };
}vby1_d_phy0_txbist_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reserved_txbist_02:8;
        RBus_UInt32  lane_enable:8;
        RBus_UInt32  debug_sel:8;
        RBus_UInt32  err_period:8;
    };
}vby1_d_phy0_txbist_02_RBUS;





#else //apply LITTLE_ENDIAN


//======PINMUX register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  tuner_scl_sr:1;
        RBus_UInt32  tuner_scl_ds:1;
        RBus_UInt32  tuner_scl_pd:1;
        RBus_UInt32  tuner_scl_pu:1;
        RBus_UInt32  tuner_scl_ps:5;
        RBus_UInt32  rf_if_sr:1;
        RBus_UInt32  rf_if_ds:1;
        RBus_UInt32  rf_if_pd:1;
        RBus_UInt32  rf_if_pu:1;
        RBus_UInt32  rf_if_ps:5;
    };
}gpio_cfg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  tuner_sda_sr:1;
        RBus_UInt32  tuner_sda_ds:1;
        RBus_UInt32  tuner_sda_pd:1;
        RBus_UInt32  tuner_sda_pu:1;
        RBus_UInt32  tuner_sda_ps:5;
    };
}gpio_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_7_sr:1;
        RBus_UInt32  gpio_7_ds:1;
        RBus_UInt32  gpio_7_pd:1;
        RBus_UInt32  gpio_7_pu:1;
        RBus_UInt32  gpio_7_ps:5;
        RBus_UInt32  gpio_6_sr:1;
        RBus_UInt32  gpio_6_ds:1;
        RBus_UInt32  gpio_6_pd:1;
        RBus_UInt32  gpio_6_pu:1;
        RBus_UInt32  gpio_6_ps:5;
        RBus_UInt32  gpio_5_sr:1;
        RBus_UInt32  gpio_5_ds:1;
        RBus_UInt32  gpio_5_pd:1;
        RBus_UInt32  gpio_5_pu:1;
        RBus_UInt32  gpio_5_ps:5;
    };
}gpio_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_10_sr:1;
        RBus_UInt32  gpio_10_ds:1;
        RBus_UInt32  gpio_10_pd:1;
        RBus_UInt32  gpio_10_pu:1;
        RBus_UInt32  gpio_10_ps:5;
        RBus_UInt32  gpio_9_sr:1;
        RBus_UInt32  gpio_9_ds:1;
        RBus_UInt32  gpio_9_pd:1;
        RBus_UInt32  gpio_9_pu:1;
        RBus_UInt32  gpio_9_ps:5;
        RBus_UInt32  gpio_8_sr:1;
        RBus_UInt32  gpio_8_ds:1;
        RBus_UInt32  gpio_8_pd:1;
        RBus_UInt32  gpio_8_pu:1;
        RBus_UInt32  gpio_8_ps:5;
    };
}gpio_cfg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_13_sr:1;
        RBus_UInt32  gpio_13_ds:1;
        RBus_UInt32  gpio_13_pd:1;
        RBus_UInt32  gpio_13_pu:1;
        RBus_UInt32  gpio_13_ps:5;
        RBus_UInt32  gpio_12_sr:1;
        RBus_UInt32  gpio_12_ds:1;
        RBus_UInt32  gpio_12_pd:1;
        RBus_UInt32  gpio_12_pu:1;
        RBus_UInt32  gpio_12_ps:5;
        RBus_UInt32  gpio_11_sr:1;
        RBus_UInt32  gpio_11_ds:1;
        RBus_UInt32  gpio_11_pd:1;
        RBus_UInt32  gpio_11_pu:1;
        RBus_UInt32  gpio_11_ps:5;
    };
}gpio_cfg_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_16_sr:1;
        RBus_UInt32  gpio_16_ds:1;
        RBus_UInt32  gpio_16_pd:1;
        RBus_UInt32  gpio_16_pu:1;
        RBus_UInt32  gpio_16_ps:5;
        RBus_UInt32  gpio_15_sr:1;
        RBus_UInt32  gpio_15_ds:1;
        RBus_UInt32  gpio_15_pd:1;
        RBus_UInt32  gpio_15_pu:1;
        RBus_UInt32  gpio_15_ps:5;
        RBus_UInt32  gpio_14_sr:1;
        RBus_UInt32  gpio_14_ds:1;
        RBus_UInt32  gpio_14_pd:1;
        RBus_UInt32  gpio_14_pu:1;
        RBus_UInt32  gpio_14_ps:5;
    };
}gpio_cfg_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_19_sr:1;
        RBus_UInt32  gpio_19_ds:1;
        RBus_UInt32  gpio_19_pd:1;
        RBus_UInt32  gpio_19_pu:1;
        RBus_UInt32  gpio_19_ps:5;
        RBus_UInt32  gpio_18_sr:1;
        RBus_UInt32  gpio_18_ds:1;
        RBus_UInt32  gpio_18_pd:1;
        RBus_UInt32  gpio_18_pu:1;
        RBus_UInt32  gpio_18_ps:5;
        RBus_UInt32  gpio_17_sr:1;
        RBus_UInt32  gpio_17_ds:1;
        RBus_UInt32  gpio_17_pd:1;
        RBus_UInt32  gpio_17_pu:1;
        RBus_UInt32  gpio_17_ps:5;
    };
}gpio_cfg_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  gpio_22_ds:1;
        RBus_UInt32  gpio_22_pd:1;
        RBus_UInt32  gpio_22_pu:1;
        RBus_UInt32  gpio_22_ps:5;
        RBus_UInt32  gpio_21_sr:1;
        RBus_UInt32  gpio_21_ds:1;
        RBus_UInt32  gpio_21_pd:1;
        RBus_UInt32  gpio_21_pu:1;
        RBus_UInt32  gpio_21_ps:5;
        RBus_UInt32  gpio_20_sr:1;
        RBus_UInt32  gpio_20_ds:1;
        RBus_UInt32  gpio_20_pd:1;
        RBus_UInt32  gpio_20_pu:1;
        RBus_UInt32  gpio_20_ps:5;
    };
}gpio_cfg_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_26_sr:1;
        RBus_UInt32  gpio_26_ds:1;
        RBus_UInt32  gpio_26_pd:1;
        RBus_UInt32  gpio_26_pu:1;
        RBus_UInt32  gpio_26_ps:5;
        RBus_UInt32  gpio_25_sr:1;
        RBus_UInt32  gpio_25_ds:1;
        RBus_UInt32  gpio_25_pd:1;
        RBus_UInt32  gpio_25_pu:1;
        RBus_UInt32  gpio_25_ps:5;
        RBus_UInt32  gpio_23_sr:1;
        RBus_UInt32  gpio_23_ds:1;
        RBus_UInt32  gpio_23_pd:1;
        RBus_UInt32  gpio_23_pu:1;
        RBus_UInt32  gpio_23_ps:5;
    };
}gpio_cfg_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_30_sr:1;
        RBus_UInt32  gpio_30_ds:1;
        RBus_UInt32  gpio_30_pd:1;
        RBus_UInt32  gpio_30_pu:1;
        RBus_UInt32  gpio_30_ps:5;
        RBus_UInt32  gpio_28_sr:1;
        RBus_UInt32  gpio_28_ds:1;
        RBus_UInt32  gpio_28_pd:1;
        RBus_UInt32  gpio_28_pu:1;
        RBus_UInt32  gpio_28_ps:5;
        RBus_UInt32  gpio_27_sr:1;
        RBus_UInt32  gpio_27_ds:1;
        RBus_UInt32  gpio_27_pd:1;
        RBus_UInt32  gpio_27_pu:1;
        RBus_UInt32  gpio_27_ps:5;
    };
}gpio_cfg_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_35_sr:1;
        RBus_UInt32  gpio_35_ds:1;
        RBus_UInt32  gpio_35_pd:1;
        RBus_UInt32  gpio_35_pu:1;
        RBus_UInt32  gpio_35_ps:5;
        RBus_UInt32  gpio_34_sr:1;
        RBus_UInt32  gpio_34_ds:1;
        RBus_UInt32  gpio_34_pd:1;
        RBus_UInt32  gpio_34_pu:1;
        RBus_UInt32  gpio_34_ps:5;
        RBus_UInt32  gpio_31_sr:1;
        RBus_UInt32  gpio_31_ds:1;
        RBus_UInt32  gpio_31_pd:1;
        RBus_UInt32  gpio_31_pu:1;
        RBus_UInt32  gpio_31_ps:5;
    };
}gpio_cfg_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_38_sr:1;
        RBus_UInt32  gpio_38_ds:1;
        RBus_UInt32  gpio_38_pd:1;
        RBus_UInt32  gpio_38_pu:1;
        RBus_UInt32  gpio_38_ps:5;
        RBus_UInt32  gpio_37_sr:1;
        RBus_UInt32  gpio_37_ds:1;
        RBus_UInt32  gpio_37_pd:1;
        RBus_UInt32  gpio_37_pu:1;
        RBus_UInt32  gpio_37_ps:5;
        RBus_UInt32  gpio_36_sr:1;
        RBus_UInt32  gpio_36_ds:1;
        RBus_UInt32  gpio_36_pd:1;
        RBus_UInt32  gpio_36_pu:1;
        RBus_UInt32  gpio_36_ps:5;
    };
}gpio_cfg_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_41_sr:1;
        RBus_UInt32  gpio_41_ds:1;
        RBus_UInt32  gpio_41_pd:1;
        RBus_UInt32  gpio_41_pu:1;
        RBus_UInt32  gpio_41_ps:5;
        RBus_UInt32  gpio_40_sr:1;
        RBus_UInt32  gpio_40_ds:1;
        RBus_UInt32  gpio_40_pd:1;
        RBus_UInt32  gpio_40_pu:1;
        RBus_UInt32  gpio_40_ps:5;
        RBus_UInt32  gpio_39_sr:1;
        RBus_UInt32  gpio_39_ds:1;
        RBus_UInt32  gpio_39_pd:1;
        RBus_UInt32  gpio_39_pu:1;
        RBus_UInt32  gpio_39_ps:5;
    };
}gpio_cfg_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_44_sr:1;
        RBus_UInt32  gpio_44_ds:1;
        RBus_UInt32  gpio_44_pd:1;
        RBus_UInt32  gpio_44_pu:1;
        RBus_UInt32  gpio_44_ps:5;
        RBus_UInt32  gpio_43_sr:1;
        RBus_UInt32  gpio_43_ds:1;
        RBus_UInt32  gpio_43_pd:1;
        RBus_UInt32  gpio_43_pu:1;
        RBus_UInt32  gpio_43_ps:5;
        RBus_UInt32  gpio_42_sr:1;
        RBus_UInt32  gpio_42_ds:1;
        RBus_UInt32  gpio_42_pd:1;
        RBus_UInt32  gpio_42_pu:1;
        RBus_UInt32  gpio_42_ps:5;
    };
}gpio_cfg_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_47_sr:1;
        RBus_UInt32  gpio_47_ds:1;
        RBus_UInt32  gpio_47_pd:1;
        RBus_UInt32  gpio_47_pu:1;
        RBus_UInt32  gpio_47_ps:5;
        RBus_UInt32  gpio_46_sr:1;
        RBus_UInt32  gpio_46_ds:1;
        RBus_UInt32  gpio_46_pd:1;
        RBus_UInt32  gpio_46_pu:1;
        RBus_UInt32  gpio_46_ps:5;
        RBus_UInt32  gpio_45_sr:1;
        RBus_UInt32  gpio_45_ds:1;
        RBus_UInt32  gpio_45_pd:1;
        RBus_UInt32  gpio_45_pu:1;
        RBus_UInt32  gpio_45_ps:5;
    };
}gpio_cfg_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_50_sr:1;
        RBus_UInt32  gpio_50_ds:1;
        RBus_UInt32  gpio_50_pd:1;
        RBus_UInt32  gpio_50_pu:1;
        RBus_UInt32  gpio_50_ps:5;
        RBus_UInt32  gpio_49_sr:1;
        RBus_UInt32  gpio_49_ds:1;
        RBus_UInt32  gpio_49_pd:1;
        RBus_UInt32  gpio_49_pu:1;
        RBus_UInt32  gpio_49_ps:5;
        RBus_UInt32  gpio_48_sr:1;
        RBus_UInt32  gpio_48_ds:1;
        RBus_UInt32  gpio_48_pd:1;
        RBus_UInt32  gpio_48_pu:1;
        RBus_UInt32  gpio_48_ps:5;
    };
}gpio_cfg_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_53_sr:1;
        RBus_UInt32  gpio_53_ds:1;
        RBus_UInt32  gpio_53_pd:1;
        RBus_UInt32  gpio_53_pu:1;
        RBus_UInt32  gpio_53_ps:5;
        RBus_UInt32  gpio_52_sr:1;
        RBus_UInt32  gpio_52_ds:1;
        RBus_UInt32  gpio_52_pd:1;
        RBus_UInt32  gpio_52_pu:1;
        RBus_UInt32  gpio_52_ps:5;
        RBus_UInt32  gpio_51_sr:1;
        RBus_UInt32  gpio_51_ds:1;
        RBus_UInt32  gpio_51_pd:1;
        RBus_UInt32  gpio_51_pu:1;
        RBus_UInt32  gpio_51_ps:5;
    };
}gpio_cfg_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_56_sr:1;
        RBus_UInt32  gpio_56_ds:1;
        RBus_UInt32  gpio_56_pd:1;
        RBus_UInt32  gpio_56_pu:1;
        RBus_UInt32  gpio_56_ps:5;
        RBus_UInt32  gpio_55_sr:1;
        RBus_UInt32  gpio_55_ds:1;
        RBus_UInt32  gpio_55_pd:1;
        RBus_UInt32  gpio_55_pu:1;
        RBus_UInt32  gpio_55_ps:5;
        RBus_UInt32  gpio_54_sr:1;
        RBus_UInt32  gpio_54_ds:1;
        RBus_UInt32  gpio_54_pd:1;
        RBus_UInt32  gpio_54_pu:1;
        RBus_UInt32  gpio_54_ps:5;
    };
}gpio_cfg_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  gpio_143_sr:1;
        RBus_UInt32  gpio_143_ds:1;
        RBus_UInt32  gpio_143_pd:1;
        RBus_UInt32  gpio_143_pu:1;
        RBus_UInt32  gpio_143_ps:5;
    };
}gpio_cfg_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_199_sr:1;
        RBus_UInt32  gpio_199_ds:1;
        RBus_UInt32  gpio_199_pd:1;
        RBus_UInt32  gpio_199_pu:1;
        RBus_UInt32  gpio_199_ps:5;
        RBus_UInt32  gpio_198_sr:1;
        RBus_UInt32  gpio_198_ds:1;
        RBus_UInt32  gpio_198_pd:1;
        RBus_UInt32  gpio_198_pu:1;
        RBus_UInt32  gpio_198_ps:5;
        RBus_UInt32  gpio_197_sr:1;
        RBus_UInt32  gpio_197_ds:1;
        RBus_UInt32  gpio_197_pd:1;
        RBus_UInt32  gpio_197_pu:1;
        RBus_UInt32  gpio_197_ps:5;
    };
}gpio_cfg_46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_202_sr:1;
        RBus_UInt32  gpio_202_ds:1;
        RBus_UInt32  gpio_202_pd:1;
        RBus_UInt32  gpio_202_pu:1;
        RBus_UInt32  gpio_202_ps:5;
        RBus_UInt32  gpio_201_sr:1;
        RBus_UInt32  gpio_201_ds:1;
        RBus_UInt32  gpio_201_pd:1;
        RBus_UInt32  gpio_201_pu:1;
        RBus_UInt32  gpio_201_ps:5;
        RBus_UInt32  gpio_200_sr:1;
        RBus_UInt32  gpio_200_ds:1;
        RBus_UInt32  gpio_200_pd:1;
        RBus_UInt32  gpio_200_pu:1;
        RBus_UInt32  gpio_200_ps:5;
    };
}gpio_cfg_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_205_sr:1;
        RBus_UInt32  gpio_205_ds:1;
        RBus_UInt32  gpio_205_pd:1;
        RBus_UInt32  gpio_205_pu:1;
        RBus_UInt32  gpio_205_ps:5;
        RBus_UInt32  gpio_204_sr:1;
        RBus_UInt32  gpio_204_ds:1;
        RBus_UInt32  gpio_204_pd:1;
        RBus_UInt32  gpio_204_pu:1;
        RBus_UInt32  gpio_204_ps:5;
        RBus_UInt32  gpio_203_sr:1;
        RBus_UInt32  gpio_203_ds:1;
        RBus_UInt32  gpio_203_pd:1;
        RBus_UInt32  gpio_203_pu:1;
        RBus_UInt32  gpio_203_ps:5;
    };
}gpio_cfg_48_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  gpio_206_sr:1;
        RBus_UInt32  gpio_206_ds:1;
        RBus_UInt32  gpio_206_pd:1;
        RBus_UInt32  gpio_206_pu:1;
        RBus_UInt32  gpio_206_ps:5;
    };
}gpio_cfg_49_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_33_sr:1;
        RBus_UInt32  gpio_33_ds:1;
        RBus_UInt32  gpio_33_pd:1;
        RBus_UInt32  gpio_33_pu:1;
        RBus_UInt32  gpio_33_ps:5;
        RBus_UInt32  gpio_32_sr:1;
        RBus_UInt32  gpio_32_ds:1;
        RBus_UInt32  gpio_32_pd:1;
        RBus_UInt32  gpio_32_pu:1;
        RBus_UInt32  gpio_32_ps:5;
        RBus_UInt32  gpio_29_sr:1;
        RBus_UInt32  gpio_29_ds:1;
        RBus_UInt32  gpio_29_pd:1;
        RBus_UInt32  gpio_29_pu:1;
        RBus_UInt32  gpio_29_ps:5;
    };
}gpio_cfg_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_85_sr:1;
        RBus_UInt32  gpio_85_ds:1;
        RBus_UInt32  gpio_85_pd:1;
        RBus_UInt32  gpio_85_pu:1;
        RBus_UInt32  gpio_85_ps:5;
        RBus_UInt32  gpio_142_sr:1;
        RBus_UInt32  gpio_142_ds:1;
        RBus_UInt32  gpio_142_pd:1;
        RBus_UInt32  gpio_142_pu:1;
        RBus_UInt32  gpio_142_ps:5;
        RBus_UInt32  gpio_24_sr:1;
        RBus_UInt32  gpio_24_ds:1;
        RBus_UInt32  gpio_24_pd:1;
        RBus_UInt32  gpio_24_pu:1;
        RBus_UInt32  gpio_24_ps:5;
    };
}gpio_cfg_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_88_sr:1;
        RBus_UInt32  gpio_88_ds:1;
        RBus_UInt32  gpio_88_pd:1;
        RBus_UInt32  gpio_88_pu:1;
        RBus_UInt32  gpio_88_ps:5;
        RBus_UInt32  gpio_87_sr:1;
        RBus_UInt32  gpio_87_ds:1;
        RBus_UInt32  gpio_87_pd:1;
        RBus_UInt32  gpio_87_pu:1;
        RBus_UInt32  gpio_87_ps:5;
        RBus_UInt32  gpio_86_sr:1;
        RBus_UInt32  gpio_86_ds:1;
        RBus_UInt32  gpio_86_pd:1;
        RBus_UInt32  gpio_86_pu:1;
        RBus_UInt32  gpio_86_ps:5;
    };
}gpio_cfg_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_91_sr:1;
        RBus_UInt32  gpio_91_ds:1;
        RBus_UInt32  gpio_91_pd:1;
        RBus_UInt32  gpio_91_pu:1;
        RBus_UInt32  gpio_91_ps:5;
        RBus_UInt32  gpio_90_sr:1;
        RBus_UInt32  gpio_90_ds:1;
        RBus_UInt32  gpio_90_pd:1;
        RBus_UInt32  gpio_90_pu:1;
        RBus_UInt32  gpio_90_ps:5;
        RBus_UInt32  gpio_89_sr:1;
        RBus_UInt32  gpio_89_ds:1;
        RBus_UInt32  gpio_89_pd:1;
        RBus_UInt32  gpio_89_pu:1;
        RBus_UInt32  gpio_89_ps:5;
    };
}gpio_cfg_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_94_sr:1;
        RBus_UInt32  gpio_94_ds:1;
        RBus_UInt32  gpio_94_pd:1;
        RBus_UInt32  gpio_94_pu:1;
        RBus_UInt32  gpio_94_ps:5;
        RBus_UInt32  gpio_93_sr:1;
        RBus_UInt32  gpio_93_ds:1;
        RBus_UInt32  gpio_93_pd:1;
        RBus_UInt32  gpio_93_pu:1;
        RBus_UInt32  gpio_93_ps:5;
        RBus_UInt32  gpio_92_sr:1;
        RBus_UInt32  gpio_92_ds:1;
        RBus_UInt32  gpio_92_pd:1;
        RBus_UInt32  gpio_92_pu:1;
        RBus_UInt32  gpio_92_ps:5;
    };
}gpio_cfg_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_97_sr:1;
        RBus_UInt32  gpio_97_ds:1;
        RBus_UInt32  gpio_97_pd:1;
        RBus_UInt32  gpio_97_pu:1;
        RBus_UInt32  gpio_97_ps:5;
        RBus_UInt32  gpio_96_sr:1;
        RBus_UInt32  gpio_96_ds:1;
        RBus_UInt32  gpio_96_pd:1;
        RBus_UInt32  gpio_96_pu:1;
        RBus_UInt32  gpio_96_ps:5;
        RBus_UInt32  gpio_95_sr:1;
        RBus_UInt32  gpio_95_ds:1;
        RBus_UInt32  gpio_95_pd:1;
        RBus_UInt32  gpio_95_pu:1;
        RBus_UInt32  gpio_95_ps:5;
    };
}gpio_cfg_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:5;
        RBus_UInt32  gpio_100_sr:1;
        RBus_UInt32  gpio_100_ds:1;
        RBus_UInt32  gpio_100_pd:1;
        RBus_UInt32  gpio_100_pu:1;
        RBus_UInt32  gpio_100_ps:5;
        RBus_UInt32  res1:1;
        RBus_UInt32  gpio_99_ds:1;
        RBus_UInt32  gpio_99_pd:1;
        RBus_UInt32  gpio_99_pu:1;
        RBus_UInt32  gpio_99_ps:5;
        RBus_UInt32  gpio_98_sr:1;
        RBus_UInt32  gpio_98_ds:1;
        RBus_UInt32  gpio_98_pd:1;
        RBus_UInt32  gpio_98_pu:1;
        RBus_UInt32  gpio_98_ps:5;
    };
}gpio_cfg_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_103_sr:1;
        RBus_UInt32  gpio_103_ds:1;
        RBus_UInt32  gpio_103_pd:1;
        RBus_UInt32  gpio_103_pu:1;
        RBus_UInt32  gpio_103_ps:5;
        RBus_UInt32  gpio_102_sr:1;
        RBus_UInt32  gpio_102_ds:1;
        RBus_UInt32  gpio_102_pd:1;
        RBus_UInt32  gpio_102_pu:1;
        RBus_UInt32  gpio_102_ps:5;
        RBus_UInt32  gpio_101_sr:1;
        RBus_UInt32  gpio_101_ds:1;
        RBus_UInt32  gpio_101_pd:1;
        RBus_UInt32  gpio_101_pu:1;
        RBus_UInt32  gpio_101_ps:5;
    };
}gpio_cfg_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_106_sr:1;
        RBus_UInt32  gpio_106_ds:1;
        RBus_UInt32  gpio_106_pd:1;
        RBus_UInt32  gpio_106_pu:1;
        RBus_UInt32  gpio_106_ps:5;
        RBus_UInt32  gpio_105_sr:1;
        RBus_UInt32  gpio_105_ds:1;
        RBus_UInt32  gpio_105_pd:1;
        RBus_UInt32  gpio_105_pu:1;
        RBus_UInt32  gpio_105_ps:5;
        RBus_UInt32  gpio_104_sr:1;
        RBus_UInt32  gpio_104_ds:1;
        RBus_UInt32  gpio_104_pd:1;
        RBus_UInt32  gpio_104_pu:1;
        RBus_UInt32  gpio_104_ps:5;
    };
}gpio_cfg_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  gpio_108_sr:1;
        RBus_UInt32  gpio_108_ds:1;
        RBus_UInt32  gpio_108_pd:1;
        RBus_UInt32  gpio_108_pu:1;
        RBus_UInt32  gpio_108_ps:5;
        RBus_UInt32  gpio_107_sr:1;
        RBus_UInt32  gpio_107_ds:1;
        RBus_UInt32  gpio_107_pd:1;
        RBus_UInt32  gpio_107_pu:1;
        RBus_UInt32  gpio_107_ps:5;
    };
}gpio_cfg_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:5;
        RBus_UInt32  gpio_170_sr:1;
        RBus_UInt32  gpio_170_ds:1;
        RBus_UInt32  gpio_170_pd:1;
        RBus_UInt32  gpio_170_pu:1;
        RBus_UInt32  gpio_170_ps:5;
        RBus_UInt32  gpio_169_sr:1;
        RBus_UInt32  gpio_169_ds:1;
        RBus_UInt32  gpio_169_pd:1;
        RBus_UInt32  gpio_169_pu:1;
        RBus_UInt32  gpio_169_ps:5;
        RBus_UInt32  res1:9;
    };
}gpio_cfg_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_173_sr:1;
        RBus_UInt32  gpio_173_ds:1;
        RBus_UInt32  gpio_173_pd:1;
        RBus_UInt32  gpio_173_pu:1;
        RBus_UInt32  gpio_173_ps:5;
        RBus_UInt32  gpio_172_sr:1;
        RBus_UInt32  gpio_172_ds:1;
        RBus_UInt32  gpio_172_pd:1;
        RBus_UInt32  gpio_172_pu:1;
        RBus_UInt32  gpio_172_ps:5;
        RBus_UInt32  gpio_171_sr:1;
        RBus_UInt32  gpio_171_ds:1;
        RBus_UInt32  gpio_171_pd:1;
        RBus_UInt32  gpio_171_pu:1;
        RBus_UInt32  gpio_171_ps:5;
    };
}gpio_cfg_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_176_sr:1;
        RBus_UInt32  gpio_176_ds:1;
        RBus_UInt32  gpio_176_pd:1;
        RBus_UInt32  gpio_176_pu:1;
        RBus_UInt32  gpio_176_ps:5;
        RBus_UInt32  gpio_175_sr:1;
        RBus_UInt32  gpio_175_ds:1;
        RBus_UInt32  gpio_175_pd:1;
        RBus_UInt32  gpio_175_pu:1;
        RBus_UInt32  gpio_175_ps:5;
        RBus_UInt32  gpio_174_sr:1;
        RBus_UInt32  gpio_174_ds:1;
        RBus_UInt32  gpio_174_pd:1;
        RBus_UInt32  gpio_174_pu:1;
        RBus_UInt32  gpio_174_ps:5;
    };
}gpio_cfg_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_179_sr:1;
        RBus_UInt32  gpio_179_ds:1;
        RBus_UInt32  gpio_179_pd:1;
        RBus_UInt32  gpio_179_pu:1;
        RBus_UInt32  gpio_179_ps:5;
        RBus_UInt32  gpio_178_sr:1;
        RBus_UInt32  gpio_178_ds:1;
        RBus_UInt32  gpio_178_pd:1;
        RBus_UInt32  gpio_178_pu:1;
        RBus_UInt32  gpio_178_ps:5;
        RBus_UInt32  gpio_177_sr:1;
        RBus_UInt32  gpio_177_ds:1;
        RBus_UInt32  gpio_177_pd:1;
        RBus_UInt32  gpio_177_pu:1;
        RBus_UInt32  gpio_177_ps:5;
    };
}gpio_cfg_32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_182_sr:1;
        RBus_UInt32  gpio_182_ds:1;
        RBus_UInt32  gpio_182_pd:1;
        RBus_UInt32  gpio_182_pu:1;
        RBus_UInt32  gpio_182_ps:5;
        RBus_UInt32  gpio_181_sr:1;
        RBus_UInt32  gpio_181_ds:1;
        RBus_UInt32  gpio_181_pd:1;
        RBus_UInt32  gpio_181_pu:1;
        RBus_UInt32  gpio_181_ps:5;
        RBus_UInt32  gpio_180_sr:1;
        RBus_UInt32  gpio_180_ds:1;
        RBus_UInt32  gpio_180_pd:1;
        RBus_UInt32  gpio_180_pu:1;
        RBus_UInt32  gpio_180_ps:5;
    };
}gpio_cfg_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_185_sr:1;
        RBus_UInt32  gpio_185_ds:1;
        RBus_UInt32  gpio_185_pd:1;
        RBus_UInt32  gpio_185_pu:1;
        RBus_UInt32  gpio_185_ps:5;
        RBus_UInt32  gpio_184_sr:1;
        RBus_UInt32  gpio_184_ds:1;
        RBus_UInt32  gpio_184_pd:1;
        RBus_UInt32  gpio_184_pu:1;
        RBus_UInt32  gpio_184_ps:5;
        RBus_UInt32  gpio_183_sr:1;
        RBus_UInt32  gpio_183_ds:1;
        RBus_UInt32  gpio_183_pd:1;
        RBus_UInt32  gpio_183_pu:1;
        RBus_UInt32  gpio_183_ps:5;
    };
}gpio_cfg_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_188_sr:1;
        RBus_UInt32  gpio_188_ds:1;
        RBus_UInt32  gpio_188_pd:1;
        RBus_UInt32  gpio_188_pu:1;
        RBus_UInt32  gpio_188_ps:5;
        RBus_UInt32  gpio_187_sr:1;
        RBus_UInt32  gpio_187_ds:1;
        RBus_UInt32  gpio_187_pd:1;
        RBus_UInt32  gpio_187_pu:1;
        RBus_UInt32  gpio_187_ps:5;
        RBus_UInt32  gpio_186_sr:1;
        RBus_UInt32  gpio_186_ds:1;
        RBus_UInt32  gpio_186_pd:1;
        RBus_UInt32  gpio_186_pu:1;
        RBus_UInt32  gpio_186_ps:5;
    };
}gpio_cfg_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:5;
        RBus_UInt32  gpio_151_sr:1;
        RBus_UInt32  gpio_151_ds:1;
        RBus_UInt32  gpio_151_pd:1;
        RBus_UInt32  gpio_151_pu:1;
        RBus_UInt32  gpio_151_ps:5;
        RBus_UInt32  gpio_150_sr:1;
        RBus_UInt32  gpio_150_ds:1;
        RBus_UInt32  gpio_150_pd:1;
        RBus_UInt32  gpio_150_pu:1;
        RBus_UInt32  gpio_150_ps:5;
        RBus_UInt32  res1:9;
    };
}gpio_cfg_50_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_154_sr:1;
        RBus_UInt32  gpio_154_ds:1;
        RBus_UInt32  gpio_154_pd:1;
        RBus_UInt32  gpio_154_pu:1;
        RBus_UInt32  gpio_154_ps:5;
        RBus_UInt32  gpio_153_sr:1;
        RBus_UInt32  gpio_153_ds:1;
        RBus_UInt32  gpio_153_pd:1;
        RBus_UInt32  gpio_153_pu:1;
        RBus_UInt32  gpio_153_ps:5;
        RBus_UInt32  gpio_152_sr:1;
        RBus_UInt32  gpio_152_ds:1;
        RBus_UInt32  gpio_152_pd:1;
        RBus_UInt32  gpio_152_pu:1;
        RBus_UInt32  gpio_152_ps:5;
    };
}gpio_cfg_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_157_sr:1;
        RBus_UInt32  gpio_157_ds:1;
        RBus_UInt32  gpio_157_pd:1;
        RBus_UInt32  gpio_157_pu:1;
        RBus_UInt32  gpio_157_ps:5;
        RBus_UInt32  gpio_156_sr:1;
        RBus_UInt32  gpio_156_ds:1;
        RBus_UInt32  gpio_156_pd:1;
        RBus_UInt32  gpio_156_pu:1;
        RBus_UInt32  gpio_156_ps:5;
        RBus_UInt32  gpio_155_sr:1;
        RBus_UInt32  gpio_155_ds:1;
        RBus_UInt32  gpio_155_pd:1;
        RBus_UInt32  gpio_155_pu:1;
        RBus_UInt32  gpio_155_ps:5;
    };
}gpio_cfg_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_160_sr:1;
        RBus_UInt32  gpio_160_ds:1;
        RBus_UInt32  gpio_160_pd:1;
        RBus_UInt32  gpio_160_pu:1;
        RBus_UInt32  gpio_160_ps:5;
        RBus_UInt32  gpio_159_sr:1;
        RBus_UInt32  gpio_159_ds:1;
        RBus_UInt32  gpio_159_pd:1;
        RBus_UInt32  gpio_159_pu:1;
        RBus_UInt32  gpio_159_ps:5;
        RBus_UInt32  gpio_158_sr:1;
        RBus_UInt32  gpio_158_ds:1;
        RBus_UInt32  gpio_158_pd:1;
        RBus_UInt32  gpio_158_pu:1;
        RBus_UInt32  gpio_158_ps:5;
    };
}gpio_cfg_42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_163_sr:1;
        RBus_UInt32  gpio_163_ds:1;
        RBus_UInt32  gpio_163_pd:1;
        RBus_UInt32  gpio_163_pu:1;
        RBus_UInt32  gpio_163_ps:5;
        RBus_UInt32  gpio_162_sr:1;
        RBus_UInt32  gpio_162_ds:1;
        RBus_UInt32  gpio_162_pd:1;
        RBus_UInt32  gpio_162_pu:1;
        RBus_UInt32  gpio_162_ps:5;
        RBus_UInt32  gpio_161_sr:1;
        RBus_UInt32  gpio_161_ds:1;
        RBus_UInt32  gpio_161_pd:1;
        RBus_UInt32  gpio_161_pu:1;
        RBus_UInt32  gpio_161_ps:5;
    };
}gpio_cfg_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  gpio_165_sr:1;
        RBus_UInt32  gpio_165_ds:1;
        RBus_UInt32  gpio_165_pd:1;
        RBus_UInt32  gpio_165_pu:1;
        RBus_UInt32  gpio_165_ps:5;
        RBus_UInt32  gpio_164_sr:1;
        RBus_UInt32  gpio_164_ds:1;
        RBus_UInt32  gpio_164_pd:1;
        RBus_UInt32  gpio_164_pu:1;
        RBus_UInt32  gpio_164_ps:5;
    };
}gpio_cfg_51_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_191_sr:1;
        RBus_UInt32  gpio_191_ds:1;
        RBus_UInt32  gpio_191_pd:1;
        RBus_UInt32  gpio_191_pu:1;
        RBus_UInt32  gpio_191_ps:5;
        RBus_UInt32  gpio_190_sr:1;
        RBus_UInt32  gpio_190_ds:1;
        RBus_UInt32  gpio_190_pd:1;
        RBus_UInt32  gpio_190_pu:1;
        RBus_UInt32  gpio_190_ps:5;
        RBus_UInt32  gpio_189_sr:1;
        RBus_UInt32  gpio_189_ds:1;
        RBus_UInt32  gpio_189_pd:1;
        RBus_UInt32  gpio_189_pu:1;
        RBus_UInt32  gpio_189_ps:5;
    };
}gpio_cfg_36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_145_sr:1;
        RBus_UInt32  gpio_145_ds:1;
        RBus_UInt32  gpio_145_pd:1;
        RBus_UInt32  gpio_145_pu:1;
        RBus_UInt32  gpio_145_ps:5;
        RBus_UInt32  gpio_4_sr:1;
        RBus_UInt32  gpio_4_ds:1;
        RBus_UInt32  gpio_4_pd:1;
        RBus_UInt32  gpio_4_pu:1;
        RBus_UInt32  gpio_4_ps:5;
        RBus_UInt32  gpio_3_sr:1;
        RBus_UInt32  gpio_3_ds:1;
        RBus_UInt32  gpio_3_pd:1;
        RBus_UInt32  gpio_3_pu:1;
        RBus_UInt32  gpio_3_ps:5;
    };
}gpio_cfg_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_148_sr:1;
        RBus_UInt32  gpio_148_ds:1;
        RBus_UInt32  gpio_148_pd:1;
        RBus_UInt32  gpio_148_pu:1;
        RBus_UInt32  gpio_148_ps:5;
        RBus_UInt32  gpio_147_sr:1;
        RBus_UInt32  gpio_147_ds:1;
        RBus_UInt32  gpio_147_pd:1;
        RBus_UInt32  gpio_147_pu:1;
        RBus_UInt32  gpio_147_ps:5;
        RBus_UInt32  gpio_146_sr:1;
        RBus_UInt32  gpio_146_ds:1;
        RBus_UInt32  gpio_146_pd:1;
        RBus_UInt32  gpio_146_pu:1;
        RBus_UInt32  gpio_146_ps:5;
    };
}gpio_cfg_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  gpio_149_sr:1;
        RBus_UInt32  gpio_149_ds:1;
        RBus_UInt32  gpio_149_pd:1;
        RBus_UInt32  gpio_149_pu:1;
        RBus_UInt32  gpio_149_ps:5;
    };
}gpio_cfg_39_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:5;
        RBus_UInt32  gpio_166_sr:1;
        RBus_UInt32  gpio_166_ds:1;
        RBus_UInt32  gpio_166_pd:1;
        RBus_UInt32  gpio_166_pu:1;
        RBus_UInt32  gpio_166_ps:5;
        RBus_UInt32  res1:18;
    };
}gpio_cfg_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  gpio_144_sr:1;
        RBus_UInt32  gpio_144_ds:1;
        RBus_UInt32  gpio_144_pd:1;
        RBus_UInt32  gpio_144_pu:1;
        RBus_UInt32  gpio_144_ps:5;
        RBus_UInt32  gpio_168_sr:1;
        RBus_UInt32  gpio_168_ds:1;
        RBus_UInt32  gpio_168_pd:1;
        RBus_UInt32  gpio_168_pu:1;
        RBus_UInt32  gpio_168_ps:5;
        RBus_UInt32  gpio_167_sr:1;
        RBus_UInt32  gpio_167_ds:1;
        RBus_UInt32  gpio_167_pd:1;
        RBus_UInt32  gpio_167_pu:1;
        RBus_UInt32  gpio_167_ps:5;
    };
}gpio_cfg_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  lvds_a_fn_ps:5;
        RBus_UInt32  lvds_a_fp_ps:5;
        RBus_UInt32  lvds_a_gn_ps:5;
        RBus_UInt32  lvds_a_gp_ps:5;
        RBus_UInt32  lvds_a_hn_ps:5;
        RBus_UInt32  lvds_a_hp_ps:5;
    };
}lvds_cfg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  lvds_a_cn_ps:5;
        RBus_UInt32  lvds_a_cp_ps:5;
        RBus_UInt32  lvds_a_dn_ps:5;
        RBus_UInt32  lvds_a_dp_ps:5;
        RBus_UInt32  lvds_a_en_ps:5;
        RBus_UInt32  lvds_a_ep_ps:5;
    };
}lvds_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  lvds_b_gn_ps:5;
        RBus_UInt32  lvds_b_gp_ps:5;
        RBus_UInt32  lvds_a_an_ps:5;
        RBus_UInt32  lvds_a_ap_ps:5;
        RBus_UInt32  lvds_a_bn_ps:5;
        RBus_UInt32  lvds_a_bp_ps:5;
    };
}lvds_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  lvds_b_dn_ps:5;
        RBus_UInt32  lvds_b_dp_ps:5;
        RBus_UInt32  lvds_b_en_ps:5;
        RBus_UInt32  lvds_b_ep_ps:5;
        RBus_UInt32  lvds_b_fn_ps:5;
        RBus_UInt32  lvds_b_fp_ps:5;
    };
}lvds_cfg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  lvds_b_an_ps:5;
        RBus_UInt32  lvds_b_ap_ps:5;
        RBus_UInt32  lvds_b_bn_ps:5;
        RBus_UInt32  lvds_b_bp_ps:5;
        RBus_UInt32  lvds_b_cn_ps:5;
        RBus_UInt32  lvds_b_cp_ps:5;
    };
}lvds_cfg_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_gpi_en:1;
        RBus_UInt32  vsync_gpi_en:1;
        RBus_UInt32  res1:20;
        RBus_UInt32  hsync_ps:5;
        RBus_UInt32  vsync_ps:5;
    };
}hv_cfg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_2p_gpi_en:1;
        RBus_UInt32  vin_1p_gpi_en:1;
        RBus_UInt32  vin_bn_gpi_en:1;
        RBus_UInt32  vin_0p_gpi_en:1;
        RBus_UInt32  res1:8;
        RBus_UInt32  vin_2p_ps:5;
        RBus_UInt32  vin_1p_ps:5;
        RBus_UInt32  vin_bn_ps:5;
        RBus_UInt32  vin_0p_ps:5;
    };
}ypp_adc_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_8p_gpi_en:1;
        RBus_UInt32  vin_7p_gpi_en:1;
        RBus_UInt32  vin_y1n_gpi_en:1;
        RBus_UInt32  vin_6p_gpi_en:1;
        RBus_UInt32  res1:8;
        RBus_UInt32  vin_8p_ps:5;
        RBus_UInt32  vin_7p_ps:5;
        RBus_UInt32  vin_y1n_ps:5;
        RBus_UInt32  vin_6p_ps:5;
    };
}ypp_adc_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_10p_gpi_en:1;
        RBus_UInt32  vin_a2n_gpi_en:1;
        RBus_UInt32  vin_a0n_gpi_en:1;
        RBus_UInt32  vin_12p_gpi_en:1;
        RBus_UInt32  vin_9p_gpi_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  vin_10p_ps:5;
        RBus_UInt32  vin_a2n_ps:5;
        RBus_UInt32  vin_a0n_ps:5;
        RBus_UInt32  vin_12p_ps:5;
        RBus_UInt32  vin_9p_ps:5;
    };
}adc_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vin_13p_gpi_en:1;
        RBus_UInt32  res1:26;
        RBus_UInt32  vin_13p_ps:5;
    };
}adc_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdac_out_gpi_en:1;
        RBus_UInt32  vdbs_out_gpi_en:1;
        RBus_UInt32  scart_fsw_0_gpi_en:1;
        RBus_UInt32  res1:14;
        RBus_UInt32  vdac_out_ps:5;
        RBus_UInt32  vdbs_out_ps:5;
        RBus_UInt32  scart_fsw_0_ps:5;
    };
}scart_fsw_cfg_vd_dac_cfg_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bb_ai4l_gpi_en:1;
        RBus_UInt32  bb_ai3r_gpi_en:1;
        RBus_UInt32  bb_ai3l_gpi_en:1;
        RBus_UInt32  bb_ai2r_gpi_en:1;
        RBus_UInt32  bb_ai2l_gpi_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  bb_ai4l_ps:5;
        RBus_UInt32  bb_ai3r_ps:5;
        RBus_UInt32  bb_ai3l_ps:5;
        RBus_UInt32  bb_ai2r_ps:5;
        RBus_UInt32  bb_ai2l_ps:5;
    };
}bb_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bb_hpor_gpi_en:1;
        RBus_UInt32  bb_hpol_gpi_en:1;
        RBus_UInt32  bb_aior_gpi_en:1;
        RBus_UInt32  bb_aiol_gpi_en:1;
        RBus_UInt32  bb_ai4r_gpi_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  bb_hpor_ps:5;
        RBus_UInt32  bb_hpol_ps:5;
        RBus_UInt32  bb_aior_ps:5;
        RBus_UInt32  bb_aiol_ps:5;
        RBus_UInt32  bb_ai4r_ps:5;
    };
}bb_cfg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  usb3_hsdp_gpi_en:1;
        RBus_UInt32  usb3_hsdm_gpi_en:1;
        RBus_UInt32  bb_dio3_ps_gpi_en:1;
        RBus_UInt32  bb_dio2_ps_gpi_en:1;
        RBus_UInt32  bb_dio1_ps_gpi_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  usb3_hsdp_pshsdm_2_apad:5;
        RBus_UInt32  usb3_hsdm_pshsdp_2_apad:5;
        RBus_UInt32  bb_dio3_ps:5;
        RBus_UInt32  bb_dio2_ps:5;
        RBus_UInt32  bb_dio1_ps:5;
    };
}bb_usb_cfg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res3:4;
        RBus_UInt32  i2c1_in_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  i2c2_in_sel:4;
        RBus_UInt32  tp0_mux_selection:2;
        RBus_UInt32  tp1_mux_selection:2;
        RBus_UInt32  tp2_mux_selection:2;
        RBus_UInt32  uart1_cts_n_sel:2;
        RBus_UInt32  uart1_rxdi_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  uart2_cts_n_sel:2;
        RBus_UInt32  uart2_rxdi_sel:3;
        RBus_UInt32  gpio_86_ie_v18:1;
        RBus_UInt32  gpio_52_ie_v18:1;
        RBus_UInt32  gpio_40_ie_v18:1;
    };
}pin_mux_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  antoe_in_sel:2;
        RBus_UInt32  antrx_in_sel:2;
        RBus_UInt32  anttx_in_sel:2;
        RBus_UInt32  res5:1;
        RBus_UInt32  ld_spi0_p4_sdi_sel:3;
        RBus_UInt32  ld_spi0_p3_sdo_in_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  ld_spi0_p2_sck_in_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  ld_spi1_p4_sdi_sel:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  ld_spi1_p3_sdo_in_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  ld_spi1_p2_sck_in_sel:4;
    };
}pin_mux_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  phif_enable:1;
        RBus_UInt32  res5:8;
        RBus_UInt32  vby1_lock_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  vby1_htpd_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  usb_pwr_flag2_in_sel:2;
        RBus_UInt32  usb_pwr_flag1_in_sel:2;
        RBus_UInt32  usb_pwr_flag0_in_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  epi_lock_sel:3;
        RBus_UInt32  res1:3;
        RBus_UInt32  spdif_in_sel:1;
    };
}pin_mux_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  uni_pwm_0_sel:3;
        RBus_UInt32  res8:1;
        RBus_UInt32  uni_pwm_1_sel:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  uni_pwm_2_sel:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  uni_pwm_3_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  uni_pwm_4_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  uni_pwm_5_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  uni_pwm_6_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  uni_pwm_7_sel:3;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res5:5;
        RBus_UInt32  sc1_d0_in_sel:4;
        RBus_UInt32  res4:1;
        RBus_UInt32  sc1_cd_sel:4;
        RBus_UInt32  res3:10;
        RBus_UInt32  sc0_d0_in_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  sc0_cd_sel:3;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res8:3;
        RBus_UInt32  cr_sd_d3_in_sel:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  cr_sd_d2_in_sel:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  cr_sd_d1_in_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  cr_sd_d0_in_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  cr_sd_cd_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  cr_sd_wp_sel:4;
        RBus_UInt32  res2:1;
        RBus_UInt32  cr_sd_cmd_in_sel:3;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res5:5;
        RBus_UInt32  hddc0_scl_sel:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  hddc0_sda_in_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  emmc_d7_in_sel:2;
        RBus_UInt32  emmc_d6_in_sel:2;
        RBus_UInt32  emmc_d5_in_sel:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  emmc_d4_in_sel:2;
        RBus_UInt32  emmc_d3_in_sel:2;
        RBus_UInt32  emmc_d2_in_sel:2;
        RBus_UInt32  emmc_d1_in_sel:2;
        RBus_UInt32  emmc_d0_in_sel:2;
        RBus_UInt32  emmc_cmd_in_sel:3;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctrl6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res11:1;
        RBus_UInt32  mii_rxd2_sel:3;
        RBus_UInt32  res10:1;
        RBus_UInt32  mii_rxd1_sel:2;
        RBus_UInt32  res9:1;
        RBus_UInt32  mii_rxd0_sel:2;
        RBus_UInt32  res8:1;
        RBus_UInt32  mii_rxdv_sel:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  mii_crs_sel:2;
        RBus_UInt32  mii_rxer_sel:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  mii_mdio_in_sel:2;
        RBus_UInt32  res5:1;
        RBus_UInt32  tp1_d0_sel:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  tp1_val_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  tp1_sync_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  tp1_clk_sel:1;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctrl7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res5:18;
        RBus_UInt32  mii_col_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  mii_txc_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  mii_rxc_sel:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  mii_rxd3_sel:3;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctrl8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res10:4;
        RBus_UInt32  gspi_do_in_sel:3;
        RBus_UInt32  res9:1;
        RBus_UInt32  gspi_cs_in_sel:3;
        RBus_UInt32  res8:1;
        RBus_UInt32  gspi_di_in_sel:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  gspi_sclk_in_sel:3;
        RBus_UInt32  res6:3;
        RBus_UInt32  tp2_err_sel:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  tp2_d0_sel:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  tp2_val_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  tp2_sync_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  tp2_clk_sel:1;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctrl9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:9;
        RBus_UInt32  tp0_sync_sel:2;
        RBus_UInt32  tp0_val_sel:2;
        RBus_UInt32  tp0_clk_sel:2;
        RBus_UInt32  tp0_d7_sel:2;
        RBus_UInt32  tp0_d6_sel:2;
        RBus_UInt32  tp0_d5_sel:2;
        RBus_UInt32  tp0_d4_sel:2;
        RBus_UInt32  tp0_d3_sel:2;
        RBus_UInt32  tp0_d2_sel:2;
        RBus_UInt32  tp0_d1_sel:2;
        RBus_UInt32  tp0_d0_sel:2;
        RBus_UInt32  res1:1;
    };
}pin_mux_ctr20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcmcia_cd1_n_sel:2;
        RBus_UInt32  pcmcia_wait1_n_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  pcmcia_ireq1_n_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  pcmcia_inpack1_n_sel:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  pcmcia_wait0_n_sel:2;
        RBus_UInt32  pcmcia_ireq0_n_sel:2;
        RBus_UInt32  pcmcia_cd0_n_sel:2;
        RBus_UInt32  pcmcia_inpack0_n_sel:2;
        RBus_UInt32  pcmcia_d7_in_sel:2;
        RBus_UInt32  pcmcia_d6_in_sel:2;
        RBus_UInt32  pcmcia_d5_in_sel:2;
        RBus_UInt32  pcmcia_d4_in_sel:2;
        RBus_UInt32  pcmcia_d3_in_sel:2;
        RBus_UInt32  pcmcia_d2_in_sel:2;
        RBus_UInt32  pcmcia_d1_in_sel:2;
        RBus_UInt32  pcmcia_d0_in_sel:2;
    };
}pin_mux_ctr21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res3:6;
        RBus_UInt32  gpio_23_smt:1;
        RBus_UInt32  gpio_21_smt:1;
        RBus_UInt32  gpio_22_smt:1;
        RBus_UInt32  gpio_20_smt:1;
        RBus_UInt32  gpio_19_smt:1;
        RBus_UInt32  gpio_18_smt:1;
        RBus_UInt32  gpio_17_smt:1;
        RBus_UInt32  gpio_16_smt:1;
        RBus_UInt32  gpio_15_smt:1;
        RBus_UInt32  gpio_14_smt:1;
        RBus_UInt32  gpio_13_smt:1;
        RBus_UInt32  gpio_12_smt:1;
        RBus_UInt32  gpio_11_smt:1;
        RBus_UInt32  gpio_10_smt:1;
        RBus_UInt32  gpio_9_smt:1;
        RBus_UInt32  gpio_8_smt:1;
        RBus_UInt32  gpio_7_smt:1;
        RBus_UInt32  gpio_6_smt:1;
        RBus_UInt32  gpio_5_smt:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  tuner_sda_smt:1;
        RBus_UInt32  tuner_scl_smt:1;
        RBus_UInt32  rf_if_smt:1;
        RBus_UInt32  res1:2;
    };
}schmidt_trigger_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  gpio_54_smt:1;
        RBus_UInt32  gpio_53_smt:1;
        RBus_UInt32  gpio_56_smt:1;
        RBus_UInt32  gpio_55_smt:1;
        RBus_UInt32  gpio_143_smt:1;
        RBus_UInt32  gpio_52_smt:1;
        RBus_UInt32  gpio_51_smt:1;
        RBus_UInt32  gpio_50_smt:1;
        RBus_UInt32  gpio_49_smt:1;
        RBus_UInt32  gpio_48_smt:1;
        RBus_UInt32  gpio_47_smt:1;
        RBus_UInt32  gpio_46_smt:1;
        RBus_UInt32  gpio_45_smt:1;
        RBus_UInt32  gpio_44_smt:1;
        RBus_UInt32  gpio_43_smt:1;
        RBus_UInt32  gpio_38_smt:1;
        RBus_UInt32  gpio_37_smt:1;
        RBus_UInt32  gpio_36_smt:1;
        RBus_UInt32  gpio_34_smt:1;
        RBus_UInt32  gpio_31_smt:1;
        RBus_UInt32  gpio_30_smt:1;
        RBus_UInt32  gpio_35_smt:1;
        RBus_UInt32  gpio_42_smt:1;
        RBus_UInt32  gpio_41_smt:1;
        RBus_UInt32  gpio_40_smt:1;
        RBus_UInt32  gpio_39_smt:1;
        RBus_UInt32  gpio_28_smt:1;
        RBus_UInt32  gpio_27_smt:1;
        RBus_UInt32  gpio_26_smt:1;
        RBus_UInt32  gpio_25_smt:1;
    };
}schmidt_trigger_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  gpio_142_smt:1;
        RBus_UInt32  gpio_24_smt:1;
        RBus_UInt32  gpio_33_smt:1;
        RBus_UInt32  gpio_32_smt:1;
        RBus_UInt32  gpio_29_smt:1;
    };
}schmidt_trigger_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  gpio_108_smt:1;
        RBus_UInt32  gpio_107_smt:1;
        RBus_UInt32  gpio_106_smt:1;
        RBus_UInt32  gpio_105_smt:1;
        RBus_UInt32  gpio_104_smt:1;
        RBus_UInt32  gpio_103_smt:1;
        RBus_UInt32  gpio_102_smt:1;
        RBus_UInt32  gpio_101_smt:1;
        RBus_UInt32  gpio_100_smt:1;
        RBus_UInt32  gpio_99_smt:1;
        RBus_UInt32  gpio_98_smt:1;
        RBus_UInt32  gpio_97_smt:1;
        RBus_UInt32  gpio_96_smt:1;
        RBus_UInt32  gpio_95_smt:1;
        RBus_UInt32  gpio_94_smt:1;
        RBus_UInt32  gpio_93_smt:1;
        RBus_UInt32  gpio_92_smt:1;
        RBus_UInt32  gpio_91_smt:1;
        RBus_UInt32  gpio_90_smt:1;
        RBus_UInt32  gpio_89_smt:1;
        RBus_UInt32  gpio_88_smt:1;
        RBus_UInt32  gpio_87_smt:1;
        RBus_UInt32  gpio_86_smt:1;
        RBus_UInt32  gpio_85_smt:1;
    };
}schmidt_trigger_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  gpio_206_smt:1;
        RBus_UInt32  gpio_205_smt:1;
        RBus_UInt32  gpio_204_smt:1;
        RBus_UInt32  gpio_203_smt:1;
        RBus_UInt32  gpio_202_smt:1;
        RBus_UInt32  gpio_201_smt:1;
        RBus_UInt32  gpio_200_smt:1;
        RBus_UInt32  gpio_199_smt:1;
        RBus_UInt32  gpio_198_smt:1;
        RBus_UInt32  gpio_197_smt:1;
        RBus_UInt32  gpio_188_smt:1;
        RBus_UInt32  gpio_187_smt:1;
        RBus_UInt32  gpio_186_smt:1;
        RBus_UInt32  gpio_185_smt:1;
        RBus_UInt32  gpio_184_smt:1;
        RBus_UInt32  gpio_183_smt:1;
        RBus_UInt32  gpio_182_smt:1;
        RBus_UInt32  gpio_181_smt:1;
        RBus_UInt32  gpio_180_smt:1;
        RBus_UInt32  gpio_179_smt:1;
        RBus_UInt32  gpio_178_smt:1;
        RBus_UInt32  gpio_177_smt:1;
        RBus_UInt32  gpio_176_smt:1;
        RBus_UInt32  gpio_175_smt:1;
        RBus_UInt32  gpio_174_smt:1;
        RBus_UInt32  gpio_173_smt:1;
        RBus_UInt32  gpio_172_smt:1;
        RBus_UInt32  gpio_171_smt:1;
        RBus_UInt32  gpio_170_smt:1;
        RBus_UInt32  gpio_169_smt:1;
    };
}schmidt_trigger_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  gpio_144_smt:1;
        RBus_UInt32  gpio_168_smt:1;
        RBus_UInt32  gpio_167_smt:1;
        RBus_UInt32  gpio_166_smt:1;
        RBus_UInt32  gpio_165_smt:1;
        RBus_UInt32  gpio_164_smt:1;
        RBus_UInt32  gpio_163_smt:1;
        RBus_UInt32  gpio_162_smt:1;
        RBus_UInt32  gpio_161_smt:1;
        RBus_UInt32  gpio_160_smt:1;
        RBus_UInt32  gpio_159_smt:1;
        RBus_UInt32  gpio_158_smt:1;
        RBus_UInt32  gpio_157_smt:1;
        RBus_UInt32  gpio_156_smt:1;
        RBus_UInt32  gpio_155_smt:1;
        RBus_UInt32  gpio_154_smt:1;
        RBus_UInt32  gpio_153_smt:1;
        RBus_UInt32  gpio_152_smt:1;
        RBus_UInt32  gpio_151_smt:1;
        RBus_UInt32  gpio_150_smt:1;
        RBus_UInt32  gpio_149_smt:1;
        RBus_UInt32  gpio_148_smt:1;
        RBus_UInt32  gpio_147_smt:1;
        RBus_UInt32  gpio_146_smt:1;
        RBus_UInt32  gpio_145_smt:1;
        RBus_UInt32  gpio_4_smt:1;
        RBus_UInt32  gpio_3_smt:1;
        RBus_UInt32  gpio_191_smt:1;
        RBus_UInt32  gpio_190_smt:1;
        RBus_UInt32  gpio_189_smt:1;
    };
}schmidt_trigger_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  testpin_mux:8;
        RBus_UInt32  main_ext_clk_en:8;
        RBus_UInt32  res1:16;
    };
}main_test_pin_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_sel_v25:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  plt_a_pi_freq_78:2;
        RBus_UInt32  plt_a2_sel_2xi_78:1;
        RBus_UInt32  plt_a2_pi_phsel_78:12;
        RBus_UInt32  plt_a1_sel_2xi_78:1;
        RBus_UInt32  plt_a1_pi_phsel_78:12;
    };
}lvdsepi_phy_78_ctrl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  plt_b_pi_freq_78:2;
        RBus_UInt32  plt_b2_sel_2xi_78:1;
        RBus_UInt32  plt_b2_pi_phsel_78:12;
        RBus_UInt32  plt_b1_sel_2xi_78:1;
        RBus_UInt32  plt_b1_pi_phsel_78:12;
    };
}lvdsepi_phy_78_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  plt_ck5xn_duty_78:2;
        RBus_UInt32  plt_ck5xp_duty_78:2;
        RBus_UInt32  plt_ab_sel_2xi_78:1;
        RBus_UInt32  plt_ab_freq_78:2;
        RBus_UInt32  plt_ab_pi_phsel_78:12;
    };
}lvdsepi_phy_78_ctrl_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  plt_cmu_b_pi_bypass:1;
        RBus_UInt32  plt_cmu_a_pi_bypass:1;
        RBus_UInt32  plt_en_test_78:1;
        RBus_UInt32  plt_cmu_sel_vldo_78:2;
        RBus_UInt32  plt_cmu_sel_sr_78:3;
        RBus_UInt32  plt_cmu_sel_sc_78:1;
        RBus_UInt32  plt_cmu_sel_cp_i_78:5;
        RBus_UInt32  plt_cmu_loop_divn_78:8;
        RBus_UInt32  plt_cmu_div248_78:2;
        RBus_UInt32  plt_cmu_cp_new_78:1;
        RBus_UInt32  plt_cmu_ck_ref_inv_78:1;
        RBus_UInt32  plt_cmu_ckpixel_inv_78:1;
        RBus_UInt32  plt_cmu_big_kvco_78:1;
    };
}lvdsepi_phy_78_ctrl_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txla_term_78:2;
        RBus_UInt32  plt_p0_txla_sr_78:2;
        RBus_UInt32  plt_p0_txla_sel_emp_78:3;
        RBus_UInt32  plt_p0_txla_ckphs_78:2;
        RBus_UInt32  plt_p0_txlan_mode_78:3;
        RBus_UInt32  plt_p0_txlap_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txlb_term_78:2;
        RBus_UInt32  plt_p0_txlb_sr_78:2;
        RBus_UInt32  plt_p0_txlb_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlb_ckphs_78:2;
        RBus_UInt32  plt_p0_txlbn_mode_78:3;
        RBus_UInt32  plt_p0_txlbp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txlc_term_78:2;
        RBus_UInt32  plt_p0_txlc_sr_78:2;
        RBus_UInt32  plt_p0_txlc_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlc_ckphs_78:2;
        RBus_UInt32  plt_p0_txlcn_mode_78:3;
        RBus_UInt32  plt_p0_txlcp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txld_term_78:2;
        RBus_UInt32  plt_p0_txld_sr_78:2;
        RBus_UInt32  plt_p0_txld_sel_emp_78:3;
        RBus_UInt32  plt_p0_txld_ckphs_78:2;
        RBus_UInt32  plt_p0_txldn_mode_78:3;
        RBus_UInt32  plt_p0_txldp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txle_term_78:2;
        RBus_UInt32  plt_p0_txle_sr_78:2;
        RBus_UInt32  plt_p0_txle_sel_emp_78:3;
        RBus_UInt32  plt_p0_txle_ckphs_78:2;
        RBus_UInt32  plt_p0_txlen_mode_78:3;
        RBus_UInt32  plt_p0_txlep_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txlf_term_78:2;
        RBus_UInt32  plt_p0_txlf_sr_78:2;
        RBus_UInt32  plt_p0_txlf_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlf_ckphs_78:2;
        RBus_UInt32  plt_p0_txlfn_mode_78:3;
        RBus_UInt32  plt_p0_txlfp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txlg_term_78:2;
        RBus_UInt32  plt_p0_txlg_sr_78:2;
        RBus_UInt32  plt_p0_txlg_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlg_ckphs_78:2;
        RBus_UInt32  plt_p0_txlgn_mode_78:3;
        RBus_UInt32  plt_p0_txlgp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p0_txlh_term_78:2;
        RBus_UInt32  plt_p0_txlh_sr_78:2;
        RBus_UInt32  plt_p0_txlh_sel_emp_78:3;
        RBus_UInt32  plt_p0_txlh_ckphs_78:2;
        RBus_UInt32  plt_p0_txlhn_mode_78:3;
        RBus_UInt32  plt_p0_txlhp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  plt_p0_txl_ib2x_78:8;
        RBus_UInt32  plt_p0_txl_cm_mode_78:1;
        RBus_UInt32  plt_p0_txl_ck7x_lag_78:1;
        RBus_UInt32  plt_p0_txl_ck7x_inv_78:1;
        RBus_UInt32  plt_p0_txl_ck7x_delay_78:2;
    };
}lvdsepi_phy_78_ctrl_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p1_txla_term_78:2;
        RBus_UInt32  plt_p1_txla_sr_78:2;
        RBus_UInt32  plt_p1_txla_sel_emp_78:3;
        RBus_UInt32  plt_p1_txla_ckphs_78:2;
        RBus_UInt32  plt_p1_txlan_mode_78:3;
        RBus_UInt32  plt_p1_txlap_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p1_txlb_term_78:2;
        RBus_UInt32  plt_p1_txlb_sr_78:2;
        RBus_UInt32  plt_p1_txlb_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlb_ckphs_78:2;
        RBus_UInt32  plt_p1_txlbn_mode_78:3;
        RBus_UInt32  plt_p1_txlbp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p1_txlc_term_78:2;
        RBus_UInt32  plt_p1_txlc_sr_78:2;
        RBus_UInt32  plt_p1_txlc_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlc_ckphs_78:2;
        RBus_UInt32  plt_p1_txlcn_mode_78:3;
        RBus_UInt32  plt_p1_txlcp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p1_txld_term_78:2;
        RBus_UInt32  plt_p1_txld_sr_78:2;
        RBus_UInt32  plt_p1_txld_sel_emp_78:3;
        RBus_UInt32  plt_p1_txld_ckphs_78:2;
        RBus_UInt32  plt_p1_txldn_mode_78:3;
        RBus_UInt32  plt_p1_txldp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p1_txle_term_78:2;
        RBus_UInt32  plt_p1_txle_sr_78:2;
        RBus_UInt32  plt_p1_txle_sel_emp_78:3;
        RBus_UInt32  plt_p1_txle_ckphs_78:2;
        RBus_UInt32  plt_p1_txlen_mode_78:3;
        RBus_UInt32  plt_p1_txlep_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p1_txlf_term_78:2;
        RBus_UInt32  plt_p1_txlf_sr_78:2;
        RBus_UInt32  plt_p1_txlf_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlf_ckphs_78:2;
        RBus_UInt32  plt_p1_txlfn_mode_78:3;
        RBus_UInt32  plt_p1_txlfp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  plt_p1_txlg_term_78:2;
        RBus_UInt32  plt_p1_txlg_sr_78:2;
        RBus_UInt32  plt_p1_txlg_sel_emp_78:3;
        RBus_UInt32  plt_p1_txlg_ckphs_78:2;
        RBus_UInt32  plt_p1_txlgn_mode_78:3;
        RBus_UInt32  plt_p1_txlgp_mode_78:3;
    };
}lvdsepi_phy_78_ctrl_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  plt_p1_txl_ib2x_78:7;
        RBus_UInt32  plt_p1_txl_cm_mode_78:1;
        RBus_UInt32  plt_p1_txl_ck7x_lag_78:1;
        RBus_UInt32  plt_p1_txl_ck7x_inv_78:1;
        RBus_UInt32  plt_p1_txl_ck7x_delay_78:2;
    };
}lvdsepi_phy_78_ctrl_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  plt_sel_lv_vldo_78:2;
        RBus_UInt32  plt_en_txl_ldo_78:1;
        RBus_UInt32  plt_en_lv_ldo_78:1;
        RBus_UInt32  vcckoff_33v_78:1;
        RBus_UInt32  plt_sel_vcm_78:5;
        RBus_UInt32  plt_sel_tx_i_78:4;
        RBus_UInt32  plt_sel_txl_vldo_78:2;
        RBus_UInt32  plt_sel_test_78:2;
        RBus_UInt32  plt_sel_mode_78:1;
        RBus_UInt32  plt_sel_isource_78:1;
    };
}lvdsepi_phy_78_ctrl_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  plt_p0_txl_en_term_78:8;
        RBus_UInt32  plt_p0_txl_en_emp_78:8;
        RBus_UInt32  plt_p0_txl_cml_str_78:8;
        RBus_UInt32  plt_p0_txl_ck1x_delay_78:2;
        RBus_UInt32  plt_p0_ttl_str_78:1;
    };
}lvdsepi_phy_78_ctrl_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  plt_p0_txl_sr_td_78:8;
        RBus_UInt32  plt_p0_txl_pre_drv_78:8;
    };
}lvdsepi_phy_78_ctrl_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  plt_p1_txl_en_term_78:7;
        RBus_UInt32  plt_p1_txl_en_emp_78:7;
        RBus_UInt32  plt_p1_txl_cml_str_78:7;
        RBus_UInt32  plt_p1_txl_ck1x_delay_78:2;
        RBus_UInt32  plt_p1_ttl_str_78:1;
    };
}lvdsepi_phy_78_ctrl_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  plt_p1_txl_sr_td_78:7;
        RBus_UInt32  plt_p1_txl_pre_drv_78:7;
    };
}lvdsepi_phy_78_ctrl_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_dummy_78_63_32:32;
    };
}lvdsepi_phy_78_ctrl_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_dummy_78_31_0:32;
    };
}lvdsepi_phy_78_ctrl_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_dummy_78_55_32:24;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_dummy_78_31_0:32;
    };
}lvdsepi_phy_78_ctrl_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pow_plt_p1_txv_78:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  pow_plt_p0_txv_78:8;
        RBus_UInt32  pow_plt_p1_txl_78:7;
        RBus_UInt32  pow_plt_p0_txl_78:8;
        RBus_UInt32  pow_plt_78:1;
    };
}lvdsepi_phy_78_ctrl_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txv_en_term:8;
        RBus_UInt32  res2:8;
        RBus_UInt32  plt_p0_txv_en_emp:8;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txva_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txva_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txva_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txva_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txva_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txva_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_32_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txvb_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvb_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvb_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvb_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvb_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvb_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_33_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txvc_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvc_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvc_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvc_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvc_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvc_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txvd_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvd_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvd_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvd_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvd_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvd_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_35_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txve_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txve_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txve_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txve_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txve_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txve_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_36_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txvf_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvf_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvf_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvf_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvf_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvf_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_37_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txvg_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvg_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvg_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvg_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvg_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvg_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_38_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p0_txvh_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p0_txvh_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p0_txvh_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p0_txvh_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p0_txvh_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p0_txvh_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_39_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txv_en_term:7;
        RBus_UInt32  res2:9;
        RBus_UInt32  plt_p1_txv_en_emp:7;
        RBus_UInt32  res1:9;
    };
}lvdsepi_phy_78_ctrl_40_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txva_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txva_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txva_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txva_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txva_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txva_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_41_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txvb_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvb_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvb_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvb_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvb_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvb_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_42_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txvc_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvc_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvc_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvc_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvc_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvc_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_43_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txvd_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvd_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvd_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvd_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvd_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvd_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_44_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txve_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txve_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txve_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txve_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txve_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txve_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txvf_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvf_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvf_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvf_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvf_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvf_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_46_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_p1_txvg_vgate:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  plt_p1_txvg_term:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  plt_p1_txvg_slew:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  plt_p1_txvg_emp:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plt_p1_txvg_driver:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  plt_p1_txvg_amp:4;
        RBus_UInt32  res1:8;
    };
}lvdsepi_phy_78_ctrl_47_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  x1x2_sel:1;
        RBus_UInt32  prbs_sel:1;
        RBus_UInt32  txbist_mode:2;
        RBus_UInt32  scramble_default:1;
        RBus_UInt32  tp_type_sel:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  delay_sel3:3;
        RBus_UInt32  delay_sel2:3;
        RBus_UInt32  delay_sel1:3;
        RBus_UInt32  delay_sel0:3;
        RBus_UInt32  bist_tp_sel:1;
        RBus_UInt32  bist_repeat:1;
    };
}vby1_d_phy0_txbist_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  packet_number:8;
        RBus_UInt32  packet_length:8;
        RBus_UInt32  bist_seed:8;
        RBus_UInt32  pn_swap:1;
        RBus_UInt32  scramble_dis:1;
        RBus_UInt32  prbs_reverse:1;
        RBus_UInt32  enhance_mode:1;
        RBus_UInt32  reserved_txbist_01:4;
    };
}vby1_d_phy0_txbist_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  err_period:8;
        RBus_UInt32  debug_sel:8;
        RBus_UInt32  lane_enable:8;
        RBus_UInt32  reserved_txbist_02:8;
    };
}vby1_d_phy0_txbist_02_RBUS;


#endif







#endif //_RBUS_PINMUX_REG_H_

