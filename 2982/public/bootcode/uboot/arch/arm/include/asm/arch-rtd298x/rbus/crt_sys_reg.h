/**
* @file rbusCRTReg.h
* RBus CRTc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/30
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _RBUS_CRT_REG_H_
#define _RBUS_CRT_REG_H_

#include "rbusTypes.h"




// CRT Register Address

#define CRT_SC_VERID_VADDR                         (0xb8060000)
#define CRT_SC_LV_RST_VADDR                        (0xb8060004)
#define CRT_SC_POL_VADDR                           (0xb8060008)
#define CRT_ST_CTRL0_VADDR                         (0xb8060010)
#define CRT_ST_SRST0_VADDR                         (0xb8060030)
#define CRT_ST_SRST1_VADDR                         (0xb8060034)
#define CRT_ST_CLKEN0_VADDR                        (0xb8060040)
#define CRT_ST_CLKEN1_VADDR                        (0xb8060044)
#define CRT_ST_MHL_CBUS_VADDR                  (0xb8060048)
#define CRT_ST_BUSCLK_VADDR                        (0xb8060050)
#define CRT_ST_EMCUCLK_VADDR                       (0xb8060054)
#define CRT_ST_CLKMUX_VADDR                        (0xb8060058)
#define CRT_ST_ALU_0_VADDR                         (0xb806005c)
#define CRT_ALU_IE_VADDR                           (0xb8060060)
#define CRT_ALU_IP_VADDR                           (0xb8060064)
#define CRT_ALU_PASS_VADDR                         (0xb8060068)
#define CRT_STB_IRQ_ALL_VADDR                      (0xb806006c)
#define CRT_ST_RING_OSC_0_VADDR                    (0xb80600e4)
#define CRT_ST_RING_OSC_1_VADDR                    (0xb80600e8)
#define CRT_ST_DBG_1_VADDR                         (0xb80600f0)
#define CRT_WDOG_DATA1_VADDR                       (0xb8060100)
#define CRT_WDOG_DATA2_VADDR                       (0xb8060104)
#define CRT_WDOG_DATA3_VADDR                       (0xb8060108)
#define CRT_WDOG_DATA4_VADDR                       (0xb806010c)
#define CRT_WDOG_DATA5_VADDR                       (0xb8060110)
#define CRT_WDOG_DATA6_VADDR                       (0xb8060114)
#define CRT_WDOG_DATA7_VADDR                       (0xb8060118)
#define CRT_WDOG_DATA8_VADDR                       (0xb806011c)
#define CRT_WDOG_DATA9_VADDR                       (0xb8060120)
#define CRT_WDOG_DATA10_VADDR                      (0xb8060124)
#define CRT_WDOG_DATA11_VADDR                      (0xb8060128)
#define CRT_WDOG_DATA12_VADDR                      (0xb806012c)
#define CRT_SOFT_RESET1_VADDR                  (0xb8000000)
#define CRT_SOFT_RESET2_VADDR                  (0xb8000004)
#define CRT_SOFT_RESET3_VADDR                  (0xb8000008)
#define CRT_CLOCK_ENABLE1_VADDR                (0xb800000c)
#define CRT_CLOCK_ENABLE2_VADDR                (0xb8000010)
#define CRT_GROUP1_CK_EN_VADDR                 (0xb8000014)
#define CRT_GROUP1_CK_SEL_VADDR                (0xb8000018)
#define CRT_TVE_CK_SEL_VADDR                   (0xb800001c)
#define CRT_DISP_PLL_DIV_VADDR                 (0xb8000020)
#define CRT_DISP_PLL_DIV2_VADDR                (0xb8000024)
#define CRT_DISP_PLL_DIV3_VADDR                (0xb8000028)
#define CRT_AUDIO_CLK_CTL_VADDR                (0xb800002c)
#define CRT_PLL_DIV_VADDR                      (0xb8000030)
#define CRT_NF_CKSEL_VADDR                     (0xb8000038)
#define CRT_NDS_SC_CKSEL_VADDR                 (0xb800003c)
#define CRT_CR_CKSEL_VADDR                     (0xb8000040)
#define CRT_CLKDIV_VADDR                       (0xb8000044)
#define CRT_ARM_WD_VADDR                       (0xb8000048)
#define CRT_POWER_CTRL0_VADDR                  (0xb800004c)
#define CRT_PLL_WDOUT_VADDR                    (0xb8000050)
#define CRT_TM_CTRL0_VADDR                     (0xb8000054)
#define CRT_TM_CTRL1_VADDR                     (0xb8000058)
#define CRT_TM_CTRL2_VADDR                     (0xb800005c)
#define CRT_DSS00_DSS_GPU0_VADDR               (0xb8000060)
#define CRT_DSS01_DSS_GPU0_VADDR               (0xb8000064)
#define CRT_DSS02_DSS_GPU0_VADDR               (0xb8000068)
#define CRT_DSS03_DSS_GPU1_VADDR               (0xb800006c)
#define CRT_DSS04_DSS_GPU1_VADDR               (0xb8000070)
#define CRT_DSS05_DSS_GPU1_VADDR               (0xb8000074)
#define CRT_DSS06_DSS_GPU2_VADDR               (0xb8000078)
#define CRT_DSS07_DSS_GPU2_VADDR               (0xb800007c)
#define CRT_DSS08_DSS_GPU2_VADDR               (0xb8000080)
#define CRT_DSS09_DSS_GPU3_VADDR               (0xb8000084)
#define CRT_DSS10_DSS_GPU3_VADDR               (0xb8000088)
#define CRT_DSS11_DSS_GPU3_VADDR               (0xb800008c)
#define CRT_DSS12_DSS_TOP0_VADDR               (0xb8000090)
#define CRT_DSS13_DSS_TOP0_VADDR               (0xb8000094)
#define CRT_DSS14_DSS_TOP0_VADDR               (0xb8000098)
#define CRT_DSS15_DSS_TVSB10_VADDR             (0xb800009c)
#define CRT_DSS16_DSS_TVSB10_VADDR             (0xb80000a0)
#define CRT_DSS17_DSS_TVSB10_VADDR             (0xb80000a4)
#define CRT_DSS18_DSS_TVSB11_VADDR             (0xb80000a8)
#define CRT_DSS19_DSS_TVSB11_VADDR             (0xb80000ac)
#define CRT_DSS20_DSS_TVSB11_VADDR             (0xb80000b0)
#define CRT_DSS21_DSS_TVSB30_VADDR             (0xb80000b4)
#define CRT_DSS22_DSS_TVSB30_VADDR             (0xb80000b8)
#define CRT_DSS23_DSS_TVSB30_VADDR             (0xb80000bc)
#define CRT_CSM00_CSM_DDR_VADDR                (0xb80007e8)
#define CRT_CSM01_CSM_DDR_VADDR                (0xb80007ec)
#define CRT_CSM02_CSM_DDR_VADDR                (0xb80007f0)
#define CRT_CSM03_CSM_DDR_VADDR                (0xb80007f4)
#define CRT_CSM04_CSM_DDR_VADDR                (0xb80007f8)
#define CRT_CSM05_CSM_DDR_VADDR                (0xb80007fc)
#define CRT_CHIP_SRAM_CTRL_VADDR               (0xb80000c0)
#define CRT_CHIP_MISC_CTRL_VADDR               (0xb80000c4)
#define CRT_CHIP_INFO2_VADDR                   (0xb80000c8)
#define CRT_APS_CTL_VADDR                      (0xb80000cc)
#define CRT_PWDN_CTRL_VADDR                    (0xb80000d0)
#define CRT_PWDN_CTRL2_VADDR                   (0xb80000d4)
#define CRT_PWDN_CTRL3_VADDR                   (0xb80000d8)
#define CRT_PWDN_CTRL4_VADDR                   (0xb80000dc)
#define CRT_AT_SPEED_VADDR                     (0xb80000e0)
#define CRT_ANA_CTRL_VADDR                     (0xb80000e4)
#define CRT_TP_DEMOD_CTRL_VADDR                (0xb80000e8)
#define CRT_CONTROL0_VADDR                     (0xb80000ec)
#define CRT_SECURITY_ST_VADDR                  (0xb80000f0)
#define CRT_DMY2_VADDR                         (0xb80000f4)
#define CRT_BUS_PLL_SSC_VADDR                  (0xb80000f8)
#define CRT_DCSB_PLL_SSC_VADDR                 (0xb80000fc)
#define CRT_PLL_SCPU1_VADDR                    (0xb8000100)
#define CRT_PLL_SCPU2_VADDR                    (0xb8000104)
#define CRT_PLL_ACPU1_VADDR                    (0xb8000108)
#define CRT_PLL_ACPU2_VADDR                    (0xb800010c)
#define CRT_PLL_VCPU1_VADDR                    (0xb8000110)
#define CRT_PLL_VCPU2_VADDR                    (0xb8000114)
#define CRT_PLL_BUS1_VADDR                     (0xb8000130)
#define CRT_PLL_BUS2_VADDR                     (0xb8000134)
#define CRT_PLL_BUS3_VADDR                     (0xb8000138)
#define CRT_PLL_DCSB1_VADDR                    (0xb8000140)
#define CRT_PLL_DCSB2_VADDR                    (0xb8000144)
#define CRT_PLL_DCSB3_VADDR                    (0xb8000148)
#define CRT_PLL_VODMA1_VADDR                   (0xb8000160)
#define CRT_PLL_VODMA2_VADDR                   (0xb8000164)
#define CRT_PLLBUS_TST_VADDR                   (0xb8000168)
#define CRT_PLL_DISP_SD1_VADDR                 (0xb8000170)
#define CRT_PLL_DISP_SD2_VADDR                 (0xb8000174)
#define CRT_PLL_DISP_SD3_VADDR                 (0xb8000178)
#define CRT_PLL_DISP_SD4_VADDR                 (0xb800017c)
#define CRT_PLL_DISP_SD5_VADDR                 (0xb8000180)
#define CRT_PLL_DISP_SD6_VADDR                 (0xb8000184)
#define CRT_PLL_DISP_SD7_VADDR                 (0xb8000188)
#define CRT_PLL_DISP1_VADDR                    (0xb8000190)
#define CRT_PLL_DISP2_VADDR                    (0xb8000194)
#define CRT_PLL_VBY1_MAC1_VADDR                (0xb8000198)
#define CRT_TMDS_SCR1_VADDR                    (0xb80001c0)
#define CRT_TMDS_SCR2_VADDR                    (0xb80001c4)
#define CRT_TMDS_SCR3_VADDR                    (0xb80001c8)
#define CRT_TVPLL_CTRL1_VADDR                  (0xb80001cc)
#define CRT_TVPLL_CTRL2_VADDR                  (0xb80001d0)
#define CRT_TVPLL_CTRL3_VADDR                  (0xb80001d4)
#define CRT_TVPLL_CTRL4_VADDR                  (0xb80001d8)
#define CRT_TVPLL_CTRL5_VADDR                  (0xb80001dc)
#define CRT_TVPLL_CTRL6_VADDR                  (0xb80001f0)
#define CRT_PLL_GPU1_VADDR                     (0xb80001e0)
#define CRT_PLL_GPU2_VADDR                     (0xb80001e4)
#define CRT_PLL_GPU3_VADDR                     (0xb80001e8)
#define CRT_PLL_GPU4_VADDR                     (0xb80001ec)
#define CRT_TRNG1_VADDR                        (0xb80001fc)
#define CRT_CRT_DEBUG_VADDR                    (0xb8000400)
#define CRT_DUMMY_VADDR                        (0xb8000450)
#define CRT_CRT_BIST_EN1_VADDR                 (0xb8000500)
#define CRT_CRT_BIST_EN2_VADDR                 (0xb8000504)
#define CRT_CRT_BIST_EN3_VADDR                 (0xb8000508)
#define CRT_CRT_DRF_BIST_EN1_VADDR             (0xb8000520)
#define CRT_CRT_DRF_BIST_EN2_VADDR             (0xb8000524)
#define CRT_CRT_DRF_BIST_EN3_VADDR             (0xb8000528)
#define CRT_CRT_DRF_TEST_RESUME1_VADDR         (0xb8000540)
#define CRT_CRT_DRF_TEST_RESUME2_VADDR         (0xb8000544)
#define CRT_CRT_DRF_TEST_RESUME3_VADDR         (0xb8000548)
#define CRT_CRT_DRF_START_PAUSE1_VADDR         (0xb8000560)
#define CRT_CRT_DRF_START_PAUSE3_VADDR         (0xb8000568)
#define CRT_CRT_BISR_EN1_VADDR                 (0xb8000580)
#define CRT_CRT_BISR_RSTN1_VADDR               (0xb8000588)
#define CRT_CRT_BISR_PWR_RSTN1_VADDR           (0xb8000590)
#define CRT_CRT_BISR_HOLD_REMAP1_VADDR         (0xb8000598)
#define CRT_CRT_BISR_HOLD_REMAP2_VADDR         (0xb800059c)
#define CRT_CRT_BISR_2ND_RUN_EN1_VADDR         (0xb80005a0)
#define CRT_CRT_DRF_BISR_EN1_VADDR             (0xb80005a8)
#define CRT_CRT_DRF_BISR_TEST_RESUME1_VADDR    (0xb80005b0)
#define CRT_CRT_SLEEP_ACK1_VADDR               (0xb80005b4)
#define CRT_CRT_SLEEP_REQ1_VADDR               (0xb80005b8)
#define CRT_CRT_LIGHT_SLEEP1_VADDR             (0xb80005c0)
#define CRT_CRT_BISR_RSTN2_VADDR               (0xb80005d0)
#define CRT_BIST_ST1_VADDR                     (0xb8000600)
#define CRT_BIST_ST2_VADDR                     (0xb8000610)
#define CRT_BIST_ST3_VADDR                     (0xb8000614)
#define CRT_DRF_ST1_VADDR                      (0xb8000620)
#define CRT_DRF_ST2_VADDR                      (0xb8000624)
#define CRT_CRT_BISR_DONE1_VADDR               (0xb8000700)
#define CRT_CRT_BISR_ST1_VADDR                 (0xb8000710)
#define CRT_CRT_BISR_REPAIRED1_VADDR           (0xb8000720)
#define CRT_CRT_BISR_OUT1_VADDR                (0xb8000730)
#define CRT_CRT_BISR_OUT2_VADDR                (0xb8000734)
#define CRT_CRT_DRF_BISR_ST1_VADDR             (0xb8000750)
#define CRT_SYS_PLL_512FS1_VADDR               (0xb8000200)
#define CRT_SYS_PLL_512FS2_VADDR               (0xb8000204)
#define CRT_SYS_PLL_DIF1_VADDR                 (0xb8000220)
#define CRT_SYS_PLL_DIF2_VADDR                 (0xb8000224)
#define CRT_SYS_PLL_DIF3_VADDR                 (0xb8000228)
#define CRT_SYS_PLL_27X1_VADDR                 (0xb8000240)
#define CRT_SYS_PLL_27X2_VADDR                 (0xb8000244)
#define CRT_SYS_PLL_27X3_VADDR                 (0xb8000248)
#define CRT_SYS_PLL_27X4_VADDR                 (0xb800024c)
#define CRT_SYS_PLL_AUD1_VADDR                 (0xb8000260)
#define CRT_SYS_PLL_AUD3_VADDR                 (0xb8000264)
#define CRT_SYS_PLL_PSAUD1_VADDR               (0xb8000280)
#define CRT_SYS_PLL_PSAUD2_VADDR               (0xb8000284)
#define CRT_SYS_PLL_DDR1_VADDR                 (0xb80002c0)
#define CRT_SYS_PLL_DDR2_VADDR                 (0xb80002c4)
#define CRT_SYS_PLL_DDR3_VADDR                 (0xb80002c8)
#define CRT_SYS_PLL_DDR4_VADDR                 (0xb80002cc)
#define CRT_SYS_PLL_DDR_SSC1_VADDR             (0xb80002d0)
#define CRT_SYS_PLL_DDR_SSC2_VADDR             (0xb80002d4)
#define CRT_SYS_PLL_DDR_SSC3_VADDR             (0xb80002d8)
#define CRT_SYS_PLL_DDR5_VADDR                 (0xb80002dc)
#define CRT_SYS_PLL_DDR5_1_VADDR               (0xb80002e0)
#define CRT_SYS_PLL_DUMMY_IN_VADDR             (0xb80002e4)
#define CRT_SYS_PLL_DUMMY_OUT_VADDR            (0xb80002e8)
#define CRT_SYS_DCLKSS_VADDR                   (0xb8000300)
#define CRT_DPLL_IN_FSYNC_TRACKING_CTRL_VADDR  (0xb8000304)
#define CRT_DPLL_IN_FSYNC_TRACKING_CTRL2_VADDR (0xb8000308)
#define CRT_DPLL_IN_FSYNC_TRACKING_DEBUG_VADDR (0xb800030c)
#define CRT_DCLK_FRC2FSYNC_SPEEDUP_VADDR       (0xb8000310)
#define CRT_DPLL_STATUS_RO_VADDR               (0xb8000314)
#define CRT_DCLKSS_FREQ_VADDR                  (0xb8000318)
#define CRT_DCLKSS_PROFILE0_VADDR              (0xb800031c)
#define CRT_DCLKSS_PROFILE1_VADDR              (0xb8000320)
#define CRT_DCLKSS_PROFILE2_VADDR              (0xb8000324)
#define CRT_DCLKSS_PROFILE3_VADDR              (0xb8000328)
#define CRT_DCLKSS_PROFILE4_VADDR              (0xb800032c)
#define CRT_DCLKSS_PROFILE5_VADDR              (0xb8000330)
#define CRT_DCLKSS_PROFILE6_VADDR              (0xb8000334)
#define CRT_DCLKSS_PROFILE7_VADDR              (0xb8000338)
#define CRT_DCLKSS_PROFILE8_VADDR              (0xb800033c)
#define CRT_DCLKSS_PROFILE9_VADDR              (0xb8000340)
#define CRT_DCLKSS_PROFILE10_VADDR             (0xb8000344)
#define CRT_DCLKSS_PROFILE11_VADDR             (0xb8000348)
#define CRT_DCLKSS_PROFILE12_VADDR             (0xb800034c)
#define CRT_DCLKSS_PROFILE13_VADDR             (0xb8000350)
#define CRT_DCLKSS_PROFILE14_VADDR             (0xb8000354)
#define CRT_DCLKSS_PROFILE15_VADDR             (0xb8000358)
#define CRT_DPLL_DOUBLE_BUFFER_CTRL_VADDR      (0xb800035c)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======CRT register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vercode:32;
    };
}sc_verid_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  por_reser:12;
        RBus_UInt32  div_emb:2;
        RBus_UInt32  cap_emb:2;
        RBus_UInt32  en_emb:1;
        RBus_UInt32  main_pow_on:1;
        RBus_UInt32  main_por_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  por_v33set_l:2;
        RBus_UInt32  por_v10set_l:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  bufm_sel:3;
        RBus_UInt32  ldov10_sel:3;
        RBus_UInt32  stbldo_pow:1;
    };
}sc_lv_rst_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pad_boption9:1;
        RBus_UInt32  pad_boption7:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  at_speed_pll_done:1;
        RBus_UInt32  porl_at_speed_scan:1;
        RBus_UInt32  porl_pll_en:1;
        RBus_UInt32  porl_dis_por:1;
        RBus_UInt32  porl_host_s_en_n:1;
        RBus_UInt32  porl_test_mode:6;
        RBus_UInt32  porl_ejtag_en_n:1;
        RBus_UInt32  porl_test_en_n:1;
        RBus_UInt32  porl_boot_opt:2;
        RBus_UInt32  porl_ejtag_mode:1;
        RBus_UInt32  porl_ejtag_loc:1;
        RBus_UInt32  porl_hif_loc:1;
    };
}sc_pol_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  efuse_isln_en:1;
        RBus_UInt32  ddr_isln_en:1;
        RBus_UInt32  rstn_getn:1;
        RBus_UInt32  rstn_mt:1;
        RBus_UInt32  mt_isln_en:1;
    };
}st_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  rstn_i2c0_off:1;
        RBus_UInt32  rstn_uart0_off:1;
        RBus_UInt32  rstn_irda_off:1;
        RBus_UInt32  rstn_pwm:1;
        RBus_UInt32  rstn_pad_mux:1;
        RBus_UInt32  rstn_iso_misc_off:1;
        RBus_UInt32  rstn_iso_misc:1;
    };
}st_srst0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  rstn_vfd:1;
        RBus_UInt32  rstn_ddc3:1;
        RBus_UInt32  rstn_ddc2:1;
        RBus_UInt32  rstn_ddc1:1;
        RBus_UInt32  rstn_osc:1;
        RBus_UInt32  rstn_rtc:1;
        RBus_UInt32  rstn_emcu_top:1;
        RBus_UInt32  rstn_emcu_core:1;
        RBus_UInt32  rstn_hdmi_det:1;
        RBus_UInt32  rstn_cec:1;
        RBus_UInt32  rstn_syncp:1;
        RBus_UInt32  rstn_cbus_tx:1;
        RBus_UInt32  rstn_cbus:1;
        RBus_UInt32  rstn_alu:1;
        RBus_UInt32  rstn_irda:1;
        RBus_UInt32  rstn_ddc:1;
        RBus_UInt32  rstn_lsadc:1;
    };
}st_srst1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  clken_i2c0_off:1;
        RBus_UInt32  clken_uart0_off:1;
        RBus_UInt32  clken_irda_off:1;
        RBus_UInt32  clken_pwm:1;
        RBus_UInt32  clken_pad_mux:1;
        RBus_UInt32  clken_iso_misc_off:1;
        RBus_UInt32  clken_iso_misc:1;
    };
}st_clken0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  clken_cbus_tx_ip:1;
        RBus_UInt32  clken_vfd:1;
        RBus_UInt32  clken_ddc3:1;
        RBus_UInt32  clken_ddc2:1;
        RBus_UInt32  clken_ddc1:1;
        RBus_UInt32  clken_osc:1;
        RBus_UInt32  clken_rtc:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  clken_emcu_core:1;
        RBus_UInt32  clken_hdmi_det:1;
        RBus_UInt32  clken_cec:1;
        RBus_UInt32  clken_syncp:1;
        RBus_UInt32  clken_cbus_tx:1;
        RBus_UInt32  clken_cbus:1;
        RBus_UInt32  clken_alu:1;
        RBus_UInt32  clken_irda:1;
        RBus_UInt32  clken_ddc:1;
        RBus_UInt32  clken_lsadc:1;
    };
}st_clken1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  mhl_clkdiv:3;
        RBus_UInt32  mhl_clkdiv_en:1;
    };
}st_mhl_cbus_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  bus_div_en:1;
        RBus_UInt32  bus_div_apply:1;
        RBus_UInt32  bus_div_busy:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  bus_div_sel:3;
        RBus_UInt32  res3:11;
        RBus_UInt32  bus_clksel:1;
    };
}st_busclk_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  emcu_div_en:1;
        RBus_UInt32  emcu_div_apply:1;
        RBus_UInt32  emcu_div_busy:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  emcu_div_sel:3;
        RBus_UInt32  res3:11;
        RBus_UInt32  res4:1;
    };
}st_emcuclk_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  osc_clksel:1;
        RBus_UInt32  uart_clksel:1;
    };
}st_clkmux_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  st2_isln_en:1;
        RBus_UInt32  res1:23;
        RBus_UInt32  st2_wakeup_tim:4;
        RBus_UInt32  st2_de_iso_ps_tim:4;
    };
}st_alu_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  stie_cbus_tx:1;
        RBus_UInt32  stie_self_wakeup:1;
        RBus_UInt32  stie_rtc:1;
        RBus_UInt32  stie_cec:1;
        RBus_UInt32  stie_cbus:1;
        RBus_UInt32  stie_iso_misc:1;
    };
}alu_ie_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  stip_cbus_tx:1;
        RBus_UInt32  stip_self_wakeup:1;
        RBus_UInt32  stip_rtc:1;
        RBus_UInt32  stip_cec:1;
        RBus_UInt32  stip_cbus:1;
        RBus_UInt32  stip_iso_misc:1;
    };
}alu_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  stpass_cbus_tx:1;
        RBus_UInt32  stpass_self_wakeup:1;
        RBus_UInt32  stpass_rtc:1;
        RBus_UInt32  stpass_cec:1;
        RBus_UInt32  stpass_cbus:1;
        RBus_UInt32  stpass_iso_misc:1;
    };
}alu_pass_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  cbus_tx_kcpu_ie:1;
        RBus_UInt32  rtc_kcpu_ie:1;
        RBus_UInt32  cec_kcpu_ie:1;
        RBus_UInt32  cbus_kcpu_ie:1;
        RBus_UInt32  hdmi_clk_det_kcpu_ie:1;
        RBus_UInt32  syncp_kcpu_ie:1;
        RBus_UInt32  iso_misc_off_kcpu_ie:1;
        RBus_UInt32  iso_misc_kcpu_ie:1;
        RBus_UInt32  cbus_tx_scpu_ie:1;
        RBus_UInt32  rtc_acpu_ie:1;
        RBus_UInt32  rtc_scpu_ie:1;
        RBus_UInt32  cec_scpu_ie:1;
        RBus_UInt32  cbus_scpu_ie:1;
        RBus_UInt32  hdmi_clk_det_scpu_ie:1;
        RBus_UInt32  syncp_scpu_ie:1;
        RBus_UInt32  iso_misc_off_scpu_ie:1;
        RBus_UInt32  iso_misc_scpu_ie:1;
    };
}stb_irq_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  s_emb:7;
        RBus_UInt32  osc_sw_s:7;
        RBus_UInt32  res2:2;
        RBus_UInt32  osc_status:2;
        RBus_UInt32  osc_cnt_diff:8;
        RBus_UInt32  osc_rstb_emb:1;
        RBus_UInt32  osc_tracking_mode:2;
        RBus_UInt32  osc_tracking_en:1;
    };
}st_ring_osc_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  osc_detection:10;
        RBus_UInt32  dummy180600e8_7_2:6;
        RBus_UInt32  ddr_iso_rst1_en:1;
        RBus_UInt32  osc_detection_en:1;
    };
}st_ring_osc_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  alu_test_mode_en:1;
        RBus_UInt32  alu_dbg_sel:7;
        RBus_UInt32  crt_dbg_sel:4;
        RBus_UInt32  res2:14;
        RBus_UInt32  dbg_div_sel:2;
    };
}st_dbg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data1:32;
    };
}wdog_data1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data2:32;
    };
}wdog_data2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data3:32;
    };
}wdog_data3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data4:32;
    };
}wdog_data4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data5:32;
    };
}wdog_data5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data6:32;
    };
}wdog_data6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data7:32;
    };
}wdog_data7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data8:32;
    };
}wdog_data8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data9:32;
    };
}wdog_data9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data10:32;
    };
}wdog_data10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data11:32;
    };
}wdog_data11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data12:32;
    };
}wdog_data12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rvd:1;
        RBus_UInt32  rstn_demod:1;
        RBus_UInt32  rstn_nf:1;
        RBus_UInt32  rstn_ae:1;
        RBus_UInt32  rstn_tp:1;
        RBus_UInt32  rstn_md:1;
        RBus_UInt32  rstn_cp:1;
        RBus_UInt32  rstn_dc_phy:1;
        RBus_UInt32  rstn_dcu:1;
        RBus_UInt32  rstn_se:1;
        RBus_UInt32  rstn_gpu:1;
        RBus_UInt32  rstn_vo:1;
        RBus_UInt32  rstn_tve:1;
        RBus_UInt32  rstn_ve:1;
        RBus_UInt32  rstn_ve_p2:1;
        RBus_UInt32  rstn_me1:1;
        RBus_UInt32  rstn_aio:1;
        RBus_UInt32  rstn_etn_phy:1;
        RBus_UInt32  rstn_etn:1;
        RBus_UInt32  rstn_hdmi:1;
        RBus_UInt32  rstn_ddc:1;
        RBus_UInt32  rstn_usb_phy2:1;
        RBus_UInt32  rstn_usb_phy1:1;
        RBus_UInt32  rstn_usb_phy0:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  rstn_usb_mac0:1;
        RBus_UInt32  rstn_usb_mac1:1;
        RBus_UInt32  rstn_usb_arb:1;
        RBus_UInt32  rstn_gspi:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  rstn_rng:1;
        RBus_UInt32  rstn_misc:1;
    };
}soft_reset1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rstn_ur2:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  rstn_ur1:1;
        RBus_UInt32  rstn_i2c_0:1;
        RBus_UInt32  rstn_i2c_1:1;
        RBus_UInt32  rstn_i2c_2:1;
        RBus_UInt32  rstn_pcmcia:1;
        RBus_UInt32  rstn_sc:1;
        RBus_UInt32  rstn_ir:1;
        RBus_UInt32  rstn_cec:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  rstn_tve_clkgen:1;
        RBus_UInt32  rstn_tm:1;
        RBus_UInt32  rstn_atvin2:1;
        RBus_UInt32  rstn_atvin:1;
        RBus_UInt32  rstn_bistreg:1;
        RBus_UInt32  rstn_usb_mac:1;
        RBus_UInt32  rstn_padmux:1;
        RBus_UInt32  rstn_dtv_demod:1;
        RBus_UInt32  rstn_emmc:1;
        RBus_UInt32  rstn_cr:1;
        RBus_UInt32  rstn_pcr_cnt:1;
        RBus_UInt32  rstn_scpu_wrap:1;
        RBus_UInt32  rstn_pwm:1;
        RBus_UInt32  rstn_gpio:1;
        RBus_UInt32  rstn_pllreg:1;
        RBus_UInt32  rstn_scpu:1;
        RBus_UInt32  rstn_vde:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  rstn_vcpu:1;
        RBus_UInt32  rstn_acpu:1;
    };
}soft_reset2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rstn_akl:1;
        RBus_UInt32  rstn_nd:1;
        RBus_UInt32  rstn_dsc:1;
        RBus_UInt32  rstn_sce:1;
        RBus_UInt32  rstn_kt:1;
        RBus_UInt32  rstn_scpu_dbg:1;
        RBus_UInt32  rstn_scpu_l2:1;
        RBus_UInt32  res1:4;
        RBus_UInt32  rstn_tvsb1_tve:1;
        RBus_UInt32  rstn_vdec:1;
        RBus_UInt32  rstn_kcpu:1;
        RBus_UInt32  rstn_hdmirx:1;
        RBus_UInt32  rstn_tv_tve:1;
        RBus_UInt32  rstn_osdcomp:1;
        RBus_UInt32  rstn_tvsb3:1;
        RBus_UInt32  rstn_tvsb1:1;
        RBus_UInt32  rstn_tvsb2:1;
        RBus_UInt32  rstn_if_demod:1;
        RBus_UInt32  rstn_vdec2:1;
        RBus_UInt32  rstn_vbis0:1;
        RBus_UInt32  rstn_audio2_dac:1;
        RBus_UInt32  rstn_audio_adc:1;
        RBus_UInt32  rstn_audio_dac:1;
        RBus_UInt32  rstn_ifadc:1;
        RBus_UInt32  rstn_apll_adc:1;
        RBus_UInt32  rstn_vodma:1;
        RBus_UInt32  rstn_dispim:1;
        RBus_UInt32  rstn_disp:1;
        RBus_UInt32  rstn_sb2:1;
    };
}soft_reset3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  clken_tvsb1_tve:1;
        RBus_UInt32  clk_en_demod:1;
        RBus_UInt32  clken_vdec:1;
        RBus_UInt32  clk_en_cr:1;
        RBus_UInt32  clk_en_emmc:1;
        RBus_UInt32  clk_en_nf:1;
        RBus_UInt32  clk_en_ae:1;
        RBus_UInt32  clk_en_tp:1;
        RBus_UInt32  clk_en_md:1;
        RBus_UInt32  clk_en_cp:1;
        RBus_UInt32  clk_en_dcu:1;
        RBus_UInt32  clk_en_se:1;
        RBus_UInt32  clken_tv_tve:1;
        RBus_UInt32  clken_tve_clkgen:1;
        RBus_UInt32  clk_en_tve:1;
        RBus_UInt32  clk_en_ve:1;
        RBus_UInt32  clk_en_ve_p2:1;
        RBus_UInt32  clk_en_tve_sys:1;
        RBus_UInt32  clk_en_aio:1;
        RBus_UInt32  clk_en_etn:1;
        RBus_UInt32  clk_en_hdmi:1;
        RBus_UInt32  reg_clken_3d_gde:1;
        RBus_UInt32  clk_en_iso_misc:1;
        RBus_UInt32  clk_en_pcr:1;
        RBus_UInt32  clk_en_usb0:1;
        RBus_UInt32  clk_en_gspi:1;
        RBus_UInt32  clk_en_usb1:1;
        RBus_UInt32  clk_en_hdmirx:1;
        RBus_UInt32  clk_en_misc:1;
    };
}clock_enable1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clk_en_ur2:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  clk_en_ur1:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  clk_en_pwm:1;
        RBus_UInt32  clk_en_misc_i2c_2:1;
        RBus_UInt32  res3:6;
        RBus_UInt32  clk_en_iso_mis:1;
        RBus_UInt32  clk_en_misc_i2c_0:1;
        RBus_UInt32  clk_en_misc_i2c_1:1;
        RBus_UInt32  clk_en_misc_pcmcia:1;
        RBus_UInt32  clk_en_misc_sc:1;
        RBus_UInt32  clk_en_misc_ir:1;
        RBus_UInt32  clk_en_misc_cec:1;
        RBus_UInt32  clk_en_misc_rtc:1;
        RBus_UInt32  clk_en_misc_vfd:1;
        RBus_UInt32  clk_en_me1:1;
        RBus_UInt32  clk_en_vde:1;
        RBus_UInt32  clk_en_ade:1;
        RBus_UInt32  clk_en_vcpu:1;
        RBus_UInt32  clk_en_acpu:1;
        RBus_UInt32  clk_en_scpu_wrap:1;
        RBus_UInt32  clk_en_scpu:1;
        RBus_UInt32  reg_clken_scpu_cssys:1;
        RBus_UInt32  res4:1;
    };
}clock_enable2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clken_tvsb1:1;
        RBus_UInt32  clken_tvsb2:1;
        RBus_UInt32  clken_tvsb3:1;
        RBus_UInt32  clken_tm:1;
        RBus_UInt32  clken_atvin_vd:1;
        RBus_UInt32  clken_atvin_ifd:1;
        RBus_UInt32  clken_osdcomp:1;
        RBus_UInt32  clken_apll_adc:1;
        RBus_UInt32  clken_if_demod:1;
        RBus_UInt32  clken_disp2tve:1;
        RBus_UInt32  clken_bistreg:1;
        RBus_UInt32  clken_vbis0:1;
        RBus_UInt32  clken_audio_daad_128fs:1;
        RBus_UInt32  clken_audio_daad_256fs:1;
        RBus_UInt32  clken_audio_pre512fs:1;
        RBus_UInt32  clken_ifadc:1;
        RBus_UInt32  clken_audio2_512fs:1;
        RBus_UInt32  clken_audio2_daad_256fs:1;
        RBus_UInt32  clken_audio2_daad_128fs:1;
        RBus_UInt32  clken_padmux:1;
        RBus_UInt32  clken_dtv_demod:1;
        RBus_UInt32  clk_en_akl:1;
        RBus_UInt32  clk_en_dsc:1;
        RBus_UInt32  clk_en_sce:1;
        RBus_UInt32  clk_en_kt:1;
        RBus_UInt32  clken_ddc:1;
        RBus_UInt32  clken_vodma:1;
        RBus_UInt32  clken_dispim:1;
        RBus_UInt32  clken_disp:1;
        RBus_UInt32  clken_pllreg:1;
        RBus_UInt32  clk_en_kcpu:1;
        RBus_UInt32  clk_en_sb2:1;
    };
}group1_ck_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  ve_rif_use_p2clk:1;
        RBus_UInt32  epi_dbg_clksel:1;
        RBus_UInt32  epi_div_clksel:2;
        RBus_UInt32  res2:5;
        RBus_UInt32  atvin_clk_sel:1;
        RBus_UInt32  atvin_vd_clk_sel:1;
        RBus_UInt32  atvin_vdadc_tve_clk_sel:1;
        RBus_UInt32  res3:6;
        RBus_UInt32  vdec_x27_clksel:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  vbis0_yppsel:1;
        RBus_UInt32  inv_vbis0_clk:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  sclk_sel:1;
    };
}group1_ck_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  clk_tve_p_vo_clk_sel2:1;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  clk_tve_p_vo_clk_sel:1;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  hdmi_phy_ckinv:1;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  dac2_ckinv:1;
        RBus_UInt32  dac1_ckinv:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  tveck_mix_sel:1;
    };
}tve_ck_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  dac2_div:5;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  dac1_div:5;
    };
}disp_pll_div_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  write_en11:1;
        RBus_UInt32  hdmi_deep_clk_sel:1;
        RBus_UInt32  write_en10:1;
        RBus_UInt32  tve_i_div:2;
        RBus_UInt32  write_en9:1;
        RBus_UInt32  hdmi_tmds_div:2;
        RBus_UInt32  write_en8:1;
        RBus_UInt32  sel_plldisp_clk2:1;
        RBus_UInt32  write_en7:1;
        RBus_UInt32  sel_pllhdmi_clk:1;
        RBus_UInt32  write_en6:1;
        RBus_UInt32  hdmi_pxl_repeat:1;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  hdmi_phy_clk_sel:1;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  hdmi_div:3;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  tve_div:4;
    };
}disp_pll_div2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  reg_hdmi_tmds_div:2;
        RBus_UInt32  reg_tve_hdmi_div_sel:2;
        RBus_UInt32  reg_dac1_clk_sel:2;
        RBus_UInt32  reg_tve_pclk_sel:2;
        RBus_UInt32  reg_dac2_clk_sel:2;
        RBus_UInt32  reg_tve_iclk_sel:2;
        RBus_UInt32  reg_dac1_phy_clk_inv:1;
        RBus_UInt32  reg_dac2_phy_clk_inv:1;
    };
}disp_pll_div3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  audio_use_sysclk:1;
    };
}audio_clk_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  scpu_freq_sel:2;
        RBus_UInt32  vcpu_freq_sel:2;
        RBus_UInt32  acpu_freq_sel:2;
        RBus_UInt32  ddr_freq_sel:2;
        RBus_UInt32  bus_freq_sel:1;
    };
}pll_div_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  nf_div:3;
    };
}nf_cksel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  nds_sc_div:3;
    };
}nds_sc_cksel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_en3:1;
        RBus_UInt32  cremmc_clk_sel:1;
        RBus_UInt32  res1:22;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  emmc_div:3;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  cr_div:3;
    };
}cr_cksel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  dtv_demod_multi_req_disable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  aud_dtv_freq_sel:3;
    };
}clkdiv_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  scpu_wd_en:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  scpu_wd_cnt:12;
    };
}arm_wd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  atv_iso_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  atv_str_status:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  atv_str_pow:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  dtv_iso_en:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  dtv_str_status:1;
        RBus_UInt32  res6:1;
        RBus_UInt32  dtv_str_pow:1;
    };
}power_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  pll27x_wdout:1;
        RBus_UInt32  reg_pllvodma_wdout:1;
        RBus_UInt32  pllgpu_wdout:1;
        RBus_UInt32  pllgpu_wdout_2:1;
        RBus_UInt32  pllaud_status:1;
        RBus_UInt32  pll512fs_wdout:1;
        RBus_UInt32  reg_pllbush_wdout:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  plldif_wdout:1;
        RBus_UInt32  pllbus2_wdout:1;
        RBus_UInt32  plletn_wdout:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllbus_wdout:1;
        RBus_UInt32  plldisp_wdout:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  plldds_wdout:1;
        RBus_UInt32  reg_pllvcpu_wdout:1;
        RBus_UInt32  reg_pllacpu_wdout:1;
        RBus_UInt32  reg_pllscpu_wdout:1;
    };
}pll_wdout_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  tm_enable:1;
        RBus_UInt32  tm_data_valid:1;
        RBus_UInt32  tm_data_sampled:1;
        RBus_UInt32  tm_reverse_cmp_out:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  tm_data_out:7;
        RBus_UInt32  tm_pwron_dly:16;
    };
}tm_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tm_compare_dly:16;
        RBus_UInt32  tm_sample_dly:16;
    };
}tm_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  reg_tm_sbg:3;
        RBus_UInt32  reg_tm_sos:3;
        RBus_UInt32  reg_tm_sinl:2;
        RBus_UInt32  reg_tm_pow:1;
        RBus_UInt32  res2:1;
    };
}tm_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35d5_speed_en:1;
        RBus_UInt32  dss_c35d5_data_in:20;
        RBus_UInt32  dss_c35d5_wire_sel:1;
        RBus_UInt32  dss_c35d5_ro_sel:3;
        RBus_UInt32  dss_c35d5_dss_rst_n:1;
    };
}dss00_dss_gpu0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35d5_wsort_go:1;
        RBus_UInt32  dss_c35d5_count_out:20;
        RBus_UInt32  dss_c35d5_ready:1;
    };
}dss01_dss_gpu0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35d5_dbgo:16;
    };
}dss02_dss_gpu0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_dss_rst_n:1;
    };
}dss03_dss_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_ready:1;
    };
}dss04_dss_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35_dbgo:16;
    };
}dss05_dss_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35d5_speed_en:1;
        RBus_UInt32  dss_c35d5_data_in:20;
        RBus_UInt32  dss_c35d5_wire_sel:1;
        RBus_UInt32  dss_c35d5_ro_sel:3;
        RBus_UInt32  dss_c35d5_dss_rst_n:1;
    };
}dss06_dss_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35d5_wsort_go:1;
        RBus_UInt32  dss_c35d5_count_out:20;
        RBus_UInt32  dss_c35d5_ready:1;
    };
}dss07_dss_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35d5_dbgo:16;
    };
}dss08_dss_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_dss_rst_n:1;
    };
}dss09_dss_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_ready:1;
    };
}dss10_dss_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35_dbgo:16;
    };
}dss11_dss_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_dss_rst_n:1;
    };
}dss12_dss_top0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_ready:1;
    };
}dss13_dss_top0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35_dbgo:16;
    };
}dss14_dss_top0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_dss_rst_n:1;
    };
}dss15_dss_tvsb10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_ready:1;
    };
}dss16_dss_tvsb10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35_dbgo:16;
    };
}dss17_dss_tvsb10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35d5_speed_en:1;
        RBus_UInt32  dss_c35d5_data_in:20;
        RBus_UInt32  dss_c35d5_wire_sel:1;
        RBus_UInt32  dss_c35d5_ro_sel:3;
        RBus_UInt32  dss_c35d5_dss_rst_n:1;
    };
}dss18_dss_tvsb11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35d5_wsort_go:1;
        RBus_UInt32  dss_c35d5_count_out:20;
        RBus_UInt32  dss_c35d5_ready:1;
    };
}dss19_dss_tvsb11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35d5_dbgo:16;
    };
}dss20_dss_tvsb11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_dss_rst_n:1;
    };
}dss21_dss_tvsb30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_ready:1;
    };
}dss22_dss_tvsb30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dss_c35_dbgo:16;
    };
}dss23_dss_tvsb30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  csm0_data_sel:2;
        RBus_UInt32  csm0_addr:4;
        RBus_UInt32  csm0_read_en:1;
        RBus_UInt32  csm0_hold:1;
        RBus_UInt32  csm0_acc_mode:1;
        RBus_UInt32  csm0_in_sel:2;
        RBus_UInt32  csm0_csm_en:1;
        RBus_UInt32  csm0_rstn:1;
    };
}csm00_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  csm0_ready:1;
    };
}csm01_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm0_data:32;
    };
}csm02_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  csm1_data_sel:2;
        RBus_UInt32  csm1_addr:4;
        RBus_UInt32  csm1_read_en:1;
        RBus_UInt32  csm1_hold:1;
        RBus_UInt32  csm1_acc_mode:1;
        RBus_UInt32  csm1_in_sel:2;
        RBus_UInt32  csm1_csm_en:1;
        RBus_UInt32  csm1_rstn:1;
    };
}csm03_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  csm1_ready:1;
    };
}csm04_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm1_data:32;
    };
}csm05_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  rme_rom:1;
        RBus_UInt32  rm_rom:4;
        RBus_UInt32  rme_800:1;
        RBus_UInt32  rm_800:4;
        RBus_UInt32  rme_600:1;
        RBus_UInt32  rm_600:4;
        RBus_UInt32  rme_400:1;
        RBus_UInt32  rm_400:4;
        RBus_UInt32  rme_300:1;
        RBus_UInt32  rm_300:4;
        RBus_UInt32  rme_200:1;
        RBus_UInt32  rm_200:4;
    };
}chip_sram_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  resume_cycle_sel:1;
    };
}chip_misc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  clk_na_fail:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  testmode:1;
        RBus_UInt32  nf_sel:1;
        RBus_UInt32  sf_sel:1;
    };
}chip_info2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  dds_rstn:1;
    };
}aps_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  kcpu_boot_info:32;
    };
}pwdn_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  acpu_boot_info:32;
    };
}pwdn_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  kcpu_boot_info_valid:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  kcpu_sw_rst:1;
    };
}pwdn_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  acpu_boot_info_valid:1;
    };
}pwdn_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  dac_test:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  scpu_config_done:1;
    };
}at_speed_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  etn_phy_gpio_en:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  etn_phy_125m_en:1;
    };
}ana_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  demod_i2c_saddr:1;
        RBus_UInt32  demod_i2c_sel:1;
        RBus_UInt32  tp2_dm_sel:1;
        RBus_UInt32  tp1_dm_sel:1;
        RBus_UInt32  tp0_dm_sel:1;
    };
}tp_demod_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  sf_en:1;
    };
}control0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  akl_busy:1;
    };
}security_st_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reserved1:32;
    };
}dmy2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bus_ssc_sse:1;
        RBus_UInt32  bus_ssc_ckinv:1;
        RBus_UInt32  bus_ssc_sss:6;
        RBus_UInt32  res1:1;
        RBus_UInt32  bus_ssc_ssn:7;
        RBus_UInt32  bus_ssc_ssfpv:8;
        RBus_UInt32  res2:6;
        RBus_UInt32  bus_ssc_stms:2;
    };
}bus_pll_ssc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dcsb_ssc_sse:1;
        RBus_UInt32  dcsb_ssc_ckinv:1;
        RBus_UInt32  dcsb_ssc_sss:6;
        RBus_UInt32  res1:1;
        RBus_UInt32  dcsb_ssc_ssn:7;
        RBus_UInt32  dcsb_ssc_ssfpv:8;
        RBus_UInt32  res2:6;
        RBus_UInt32  dcsb_ssc_stms:2;
    };
}dcsb_pll_ssc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  reg_pllscpu_n:2;
        RBus_UInt32  reg_pllscpu_m:8;
        RBus_UInt32  reg_pllscpu_ip:3;
        RBus_UInt32  reg_pllscpu_o:2;
        RBus_UInt32  reg_pllscpu_wdrst:1;
        RBus_UInt32  reg_pllscpu_wdset:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllscpu_tst:1;
    };
}pll_scpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  reg_pllscpu_rs:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllscpu_cs:2;
        RBus_UInt32  reg_pllscpu_cp:1;
        RBus_UInt32  reg_pllscpu_oeb:1;
        RBus_UInt32  pllscpu_rstb:1;
        RBus_UInt32  reg_pllscpu_pow:1;
    };
}pll_scpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  reg_pllacpu_n:2;
        RBus_UInt32  reg_pllacpu_m:7;
        RBus_UInt32  reg_pllacpu_ip:3;
        RBus_UInt32  reg_pllacpu_o:2;
        RBus_UInt32  reg_pllacpu_wdrst:1;
        RBus_UInt32  reg_pllacpu_wdset:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllacpu_tst:1;
    };
}pll_acpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  reg_pllacpu_rs:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllacpu_cs:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllacpu_oeb:1;
        RBus_UInt32  pllacpu_rstb:1;
        RBus_UInt32  reg_pllacpu_pow:1;
    };
}pll_acpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  reg_pllvcpu_ip:3;
        RBus_UInt32  reg_pllvcpu_n:2;
        RBus_UInt32  reg_pllvcpu_m:7;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllvcpu_o:2;
        RBus_UInt32  reg_pllvcpu_wdrst:1;
        RBus_UInt32  reg_pllvcpu_wdset:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  reg_pllvcpu_tst:1;
    };
}pll_vcpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  reg_pllvcpu_rs:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllvcpu_cs:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllvcpu_oeb:1;
        RBus_UInt32  pllvcpu_rstb:1;
        RBus_UInt32  reg_pllvcpu_pow:1;
    };
}pll_vcpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_pllbus_o:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pllbus_n:2;
        RBus_UInt32  reg_pllbus_m:7;
        RBus_UInt32  reg_pllbus_ip:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllbus_rs:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_pllbus_cs:2;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_pllbus_cp:2;
        RBus_UInt32  reg_pllbus_r3:3;
        RBus_UInt32  reg_pllbus_c3:2;
    };
}pll_bus1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  reg_pllbus_pi_rl:2;
        RBus_UInt32  reg_pllbus_pi_rs:2;
        RBus_UInt32  reg_pllbus_pi_bias:2;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  reg_pllbus_wdmode:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  reg_pllbus_fupdn:1;
        RBus_UInt32  reg_pllbus_psen:1;
        RBus_UInt32  reg_pllbus_vcorb:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  reg_pllbus_tst:1;
        RBus_UInt32  reg_pllbus_pstst:1;
    };
}pll_bus2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  reg_pllbus_oeb:1;
        RBus_UInt32  reg_pllbus_rstb:1;
        RBus_UInt32  reg_pllbus_pow:1;
    };
}pll_bus3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_pllbus_o_h:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pllbus_n_h:2;
        RBus_UInt32  reg_pllbus_m_h:7;
        RBus_UInt32  reg_pllbus_ip_h:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllbus_rs_h:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_pllbus_cs_h:2;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_pllbus_cp_h:2;
        RBus_UInt32  reg_pllbus_r3_h:3;
        RBus_UInt32  reg_pllbus_c3_h:2;
    };
}pll_dcsb1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  reg_pllbus_pi_rl_h:2;
        RBus_UInt32  reg_pllbus_pi_rs_h:2;
        RBus_UInt32  reg_pllbus_pi_bias_h:2;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  reg_pllbus_wdmode_h:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  reg_pllbus_fupdn_h:1;
        RBus_UInt32  reg_pllbus_psen_h:1;
        RBus_UInt32  reg_pllbus_vcorb_h:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  reg_pllbus_tst_h:1;
        RBus_UInt32  reg_pllbus_pstst_h:1;
    };
}pll_dcsb2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  reg_pllbus_oeb_h:1;
        RBus_UInt32  reg_pllbus_rstb_h:1;
        RBus_UInt32  reg_pllbus_pow_h:1;
    };
}pll_dcsb3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  reg_pllvodma_n:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pllvodma_m:7;
        RBus_UInt32  reg_pllvodma_ip:3;
        RBus_UInt32  reg_pllvodma_o:2;
        RBus_UInt32  reg_pllvodma_wdset:1;
        RBus_UInt32  reg_pllvodma_wdrst:1;
        RBus_UInt32  reg_pllvodma_cs:2;
        RBus_UInt32  reg_pllvodma_rs:3;
    };
}pll_vodma1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  reg_pllvodma_tst:1;
        RBus_UInt32  reg_pllvodma_oeb:1;
        RBus_UInt32  reg_pllvodma_rstb:1;
        RBus_UInt32  reg_pllvodma_pow:1;
    };
}pll_vodma2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  reg_pllcpu_reg:2;
        RBus_UInt32  reg_pllbus_reser:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllbus_reg:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_plltst_div:2;
        RBus_UInt32  res4:3;
        RBus_UInt32  reg_plltst_sel:5;
    };
}pllbus_tst_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_plldds_n:2;
        RBus_UInt32  reg_plldds_m:7;
        RBus_UInt32  reg_plldds_ip:3;
        RBus_UInt32  reg_plldds_rs:3;
        RBus_UInt32  reg_plldds_cs:2;
        RBus_UInt32  reg_plldds_cp:2;
        RBus_UInt32  reg_plldds_r3:3;
        RBus_UInt32  reg_plldds_c3:2;
        RBus_UInt32  reg_plldds_pi_rl:2;
        RBus_UInt32  reg_plldds_pi_rs:2;
        RBus_UInt32  reg_plldds_pi_bias:2;
        RBus_UInt32  reg_plldds_wdmode:2;
    };
}pll_disp_sd1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_plldds_o:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  psaud_1a_phase_sel:1;
        RBus_UInt32  psaud_2a_phase_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  pcr_a_smooth_en:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  pcr_a_phase_sel:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  pcr_a_ctl_en:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_plldds_fupdn:1;
        RBus_UInt32  res6:1;
        RBus_UInt32  reg_plldds_ddsen:1;
        RBus_UInt32  res7:1;
        RBus_UInt32  reg_plldds_vcorb:1;
        RBus_UInt32  res8:1;
        RBus_UInt32  reg_plldds_tst:1;
        RBus_UInt32  reg_plldds_pstst:1;
        RBus_UInt32  res9:1;
        RBus_UInt32  res10:10;
    };
}pll_disp_sd2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_psaud1_fupdn:1;
        RBus_UInt32  reg_psaud1_div:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_psaud1_tst:1;
        RBus_UInt32  reg_psaud1_psen:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_psaud2_fupdn:1;
        RBus_UInt32  reg_psaud2_div:1;
        RBus_UInt32  reg_psaud2_tst:1;
        RBus_UInt32  reg_psaud2_psen:1;
        RBus_UInt32  res5:16;
        RBus_UInt32  reg_psaud1_oeb:1;
        RBus_UInt32  reg_psaud1_rstb:1;
        RBus_UInt32  reg_psaud2_oeb:1;
        RBus_UInt32  reg_psaud2_rstb:1;
    };
}pll_disp_sd3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  reg_plldds_o:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_plldds_oeb:1;
        RBus_UInt32  reg_plldds_rstb:1;
        RBus_UInt32  reg_plldds_pow:1;
    };
}pll_disp_sd4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plldds_pcr_acc:16;
        RBus_UInt32  plldds_pcr_overflow:16;
    };
}pll_disp_sd5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  n_pcr_a_n_nxt:16;
        RBus_UInt32  pcr_a_n_nxt:16;
    };
}pll_disp_sd6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  pcr_a_n_nxt_add:8;
        RBus_UInt32  pcr_a_n_nxt_add_period:16;
    };
}pll_disp_sd7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dpll_m:8;
        RBus_UInt32  res2:5;
        RBus_UInt32  dpll_n:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  dpll_ip:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  dpll_rs:3;
        RBus_UInt32  dpll_cp:2;
        RBus_UInt32  dpll_cs:2;
    };
}pll_disp1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  dpll_ldosel:2;
        RBus_UInt32  res2:3;
        RBus_UInt32  dpll_reser:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  dpll_fupdn:1;
        RBus_UInt32  dpll_stop:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  dpll_reserve:1;
        RBus_UInt32  dpll_bpphs:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  dpll_bpn:1;
        RBus_UInt32  dpll_o:2;
        RBus_UInt32  res6:5;
        RBus_UInt32  dpll_rstb:1;
        RBus_UInt32  dpll_wdrst:1;
        RBus_UInt32  dpll_wdset:1;
        RBus_UInt32  dpll_clksel:1;
        RBus_UInt32  dpll_freeze:1;
        RBus_UInt32  dpll_vcorstb:1;
        RBus_UInt32  dpll_pow:1;
    };
}pll_disp2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  plt_cmu_macpll_divm:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  plt_cmu_macpll_divn:3;
    };
}pll_vby1_mac1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_tv_wdmode:2;
        RBus_UInt32  reg_tvkvco:1;
        RBus_UInt32  reg_tv_cp:2;
        RBus_UInt32  reg_tv_cs:2;
        RBus_UInt32  reg_tx_ck5xp_duty:2;
        RBus_UInt32  reg_tx_ck5xn_duty:2;
        RBus_UInt32  reg_tx_amp:4;
        RBus_UInt32  reg_tx_ibias:2;
        RBus_UInt32  reg_tx_emph:3;
        RBus_UInt32  reg_tx_en_emph:1;
        RBus_UInt32  reg_tx_force_vc:1;
        RBus_UInt32  reg_tx_set_vc:2;
        RBus_UInt32  reg_tx_pll_edge:1;
        RBus_UInt32  reg_tx_pll_icp:3;
        RBus_UInt32  reg_tx_pll_rs:3;
    };
}tmds_scr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_tx_pdrv_isel:2;
        RBus_UInt32  reg_tx_pll_cp:2;
        RBus_UInt32  reg_tx_pll_cs:2;
        RBus_UInt32  reg_tx_pll_kvco:1;
        RBus_UInt32  reg_tx_pll_pu:1;
        RBus_UInt32  reg_tx_pu:4;
        RBus_UInt32  reg_tx_driver:2;
        RBus_UInt32  reg_tx_slew:2;
        RBus_UInt32  reg_tx_tst_en:1;
        RBus_UInt32  reg_tx_vgate:3;
        RBus_UInt32  reg_pll_tst_en:1;
        RBus_UInt32  reg_tst_sel:2;
        RBus_UInt32  reg_tx_bypass_pll:1;
        RBus_UInt32  reg_tx_rt_en:1;
        RBus_UInt32  reg_tx_rt_sel:2;
        RBus_UInt32  reg_pll_vco_scale:2;
        RBus_UInt32  reg_bypass_din:1;
    };
}tmds_scr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_tx_pll_wdmode:2;
        RBus_UInt32  reg_tx_v1p05_sel:2;
        RBus_UInt32  reg_ldo_cco_pu:1;
        RBus_UInt32  reg_ldo_cco_vsel:2;
        RBus_UInt32  reg_ldo_pll_pu:1;
        RBus_UInt32  reg_ldo_pll_vsel:3;
        RBus_UInt32  reg_en_mhl:1;
        RBus_UInt32  reg_force_rxsense:1;
        RBus_UInt32  reg_rxsense:2;
        RBus_UInt32  reg_mhl_div:1;
        RBus_UInt32  reg_mhl_vcm:2;
        RBus_UInt32  reg_diff_rt_en:1;
        RBus_UInt32  reg_cec_enb:1;
        RBus_UInt32  reg_cec_rsel:3;
        RBus_UInt32  reg_cec_rpu_en:1;
        RBus_UInt32  reg_hpd_en:1;
        RBus_UInt32  reg_cable_det_en:1;
        RBus_UInt32  reg_ldo_tmds_pu:1;
        RBus_UInt32  reg_ldo_tmds_vsel:3;
        RBus_UInt32  reg_ldo_tmds_capsel:1;
    };
}tmds_scr3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  reg_tv_pre_div:1;
        RBus_UInt32  reg_tv_ldiv:6;
        RBus_UInt32  reg_tv_pstep_en:1;
        RBus_UInt32  reg_tv_pstep:3;
        RBus_UInt32  reg_hdmi_ck_en:1;
        RBus_UInt32  reg_pixel_div3:1;
        RBus_UInt32  reg_pixel_div5:1;
        RBus_UInt32  reg_pixel_div16:3;
        RBus_UInt32  reg_tmds_div5:1;
        RBus_UInt32  reg_tmds_div16:3;
    };
}tvpll_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_sel_ref_clk27:1;
        RBus_UInt32  reg_reserve:16;
        RBus_UInt32  reg_tv_pll_pu:1;
        RBus_UInt32  reg_tv_icp:3;
        RBus_UInt32  reg_tv_rs:3;
        RBus_UInt32  reg_tv_bypass_pll:1;
        RBus_UInt32  reg_tv_force_vc:1;
        RBus_UInt32  reg_tv_set_vc:2;
        RBus_UInt32  reg_tv_tst_en:1;
    };
}tvpll_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  reg_pcr_smooth_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pcr_phase_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pcr_ctl_en:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_plldds_fupdn:1;
        RBus_UInt32  reg_plldds_ddsen:1;
        RBus_UInt32  res5:4;
        RBus_UInt32  reg_shuffle_en:1;
        RBus_UInt32  reg_tvpll_fupdn:1;
        RBus_UInt32  reg_tvpll_reserve:1;
        RBus_UInt32  reg_tvpll_stop:1;
        RBus_UInt32  res6:9;
    };
}tvpll_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_plldds_pcr_acc:16;
        RBus_UInt32  reg_plldds_pcr_overflow:16;
    };
}tvpll_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  reg_pcr_a_n_nxt_add:8;
        RBus_UInt32  reg_pcr_a_n_nxt_add_period:16;
    };
}tvpll_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_n_pcr_a_n_nxt:16;
        RBus_UInt32  reg_pcr_a_n_nxt:16;
    };
}tvpll_ctrl6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  reg_pllgpu_n:2;
        RBus_UInt32  reg_pllgpu_m:7;
        RBus_UInt32  reg_pllgpu_ip:3;
        RBus_UInt32  reg_pllgpu_k:2;
        RBus_UInt32  reg_pllgpu_wdmode:2;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllgpu_tst:1;
    };
}pll_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  reg_pllgpu_rs:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllgpu_cs:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllgpu_oeb:1;
        RBus_UInt32  reg_pllgpu_rstb:1;
        RBus_UInt32  reg_pllgpu_pow:1;
    };
}pll_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  reg_pllgpu_n_2:2;
        RBus_UInt32  reg_pllgpu_m_2:7;
        RBus_UInt32  reg_pllgpu_ip_2:3;
        RBus_UInt32  reg_pllgpu_k_2:2;
        RBus_UInt32  reg_pllgpu_wdmode_2:2;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllgpu_tst_2:1;
    };
}pll_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  reg_pllgpu_rs_2:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllgpu_cs_2:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllgpu_oeb_2:1;
        RBus_UInt32  reg_pllgpu_rstb_2:1;
        RBus_UInt32  reg_pllgpu_pow_2:1;
    };
}pll_gpu4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_trng_res:2;
        RBus_UInt32  reg_trng_gain:2;
        RBus_UInt32  reg_trng_fs:2;
        RBus_UInt32  reg_trng_div:2;
        RBus_UInt32  reg_trng_d:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_trng_tst:1;
        RBus_UInt32  reg_trng_pow:1;
    };
}trng1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crt_dbg1_div_sel:2;
        RBus_UInt32  crt_dbg0_div_sel:2;
        RBus_UInt32  res1:15;
        RBus_UInt32  crt_dbg_en:1;
        RBus_UInt32  crt_dbg_sel0:6;
        RBus_UInt32  crt_dbg_sel1:6;
    };
}crt_debug_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy_reg:31;
        RBus_UInt32  ejtag_hif_det:1;
    };
}dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sb2_rom_bist_en:1;
        RBus_UInt32  res1:17;
        RBus_UInt32  sce_bist_mode:1;
        RBus_UInt32  tp_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hdmi0_bist_en:1;
        RBus_UInt32  hdmi1_bist_en:1;
        RBus_UInt32  vde_bist_en:1;
        RBus_UInt32  dc3_bist_en:1;
        RBus_UInt32  dc2_bist_en:1;
        RBus_UInt32  ae_rom_bist_en:1;
        RBus_UInt32  ae_bist_en:1;
        RBus_UInt32  cr_nf1_bist_en:1;
        RBus_UInt32  cp_bist_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_bist_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  ve17_bist_en:1;
        RBus_UInt32  ve16_bist_en:1;
        RBus_UInt32  ve15_bist_en:1;
        RBus_UInt32  ve14_bist_en:1;
        RBus_UInt32  ve13_bist_en:1;
        RBus_UInt32  ve12_bist_en:1;
        RBus_UInt32  ve11_bist_en:1;
        RBus_UInt32  ve10_bist_en:1;
        RBus_UInt32  ve9_bist_en:1;
        RBus_UInt32  ve8_bist_en:1;
        RBus_UInt32  ve7_bist_en:1;
        RBus_UInt32  ve6_bist_en:1;
        RBus_UInt32  ve5_bist_en:1;
        RBus_UInt32  ve4_bist_en:1;
        RBus_UInt32  ve3_bist_en:1;
        RBus_UInt32  ve2_bist_en:1;
        RBus_UInt32  ve1_bist_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_bist_en2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  etn2_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  md_bist_en:1;
        RBus_UInt32  usb2_bist_en:1;
        RBus_UInt32  usb1_bist_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  kcpu1_bist_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  vcpu_bist_en:1;
        RBus_UInt32  acpu_bist_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_bist_en3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  sce_drf_bist_mode:1;
        RBus_UInt32  tp_drf_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hdmi0_drf_bist_en:1;
        RBus_UInt32  hdmi1_drf_bist_en:1;
        RBus_UInt32  vde_drf_bist_en:1;
        RBus_UInt32  dc3_drf_bist_en:1;
        RBus_UInt32  dc2_drf_bist_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  cr_nf1_drf_bist_en:1;
        RBus_UInt32  cp_drf_bist_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_bist_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  ve17_drf_bist_en:1;
        RBus_UInt32  ve16_drf_bist_en:1;
        RBus_UInt32  ve15_drf_bist_en:1;
        RBus_UInt32  ve14_drf_bist_en:1;
        RBus_UInt32  ve13_drf_bist_en:1;
        RBus_UInt32  ve12_drf_bist_en:1;
        RBus_UInt32  ve11_drf_bist_en:1;
        RBus_UInt32  ve10_drf_bist_en:1;
        RBus_UInt32  ve9_drf_bist_en:1;
        RBus_UInt32  ve8_drf_bist_en:1;
        RBus_UInt32  ve7_drf_bist_en:1;
        RBus_UInt32  ve6_drf_bist_en:1;
        RBus_UInt32  ve5_drf_bist_en:1;
        RBus_UInt32  ve4_drf_bist_en:1;
        RBus_UInt32  ve3_drf_bist_en:1;
        RBus_UInt32  ve2_drf_bist_en:1;
        RBus_UInt32  ve1_drf_bist_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_bist_en2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  ae_drf_bist_en:1;
        RBus_UInt32  etn2_drf_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  md_drf_bist_en:1;
        RBus_UInt32  usb2_drf_bist_en:1;
        RBus_UInt32  usb1_drf_bist_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  kcpu1_drf_bist_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  vcpu_drf_bist_en:1;
        RBus_UInt32  acpu_drf_bist_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_bist_en3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  sce_drf_test_resume:1;
        RBus_UInt32  tp_drf_test_resume:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hdmi0_drf_test_resume:1;
        RBus_UInt32  hdmi1_drf_test_resume:1;
        RBus_UInt32  vde_drf_test_resume:1;
        RBus_UInt32  dc3_drf_test_resume:1;
        RBus_UInt32  dc2_drf_test_resume:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  cr_nf1_drf_test_resume:1;
        RBus_UInt32  cp_drf_test_resume:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_test_resume1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  ve17_drf_test_resume:1;
        RBus_UInt32  ve16_drf_test_resume:1;
        RBus_UInt32  ve15_drf_test_resume:1;
        RBus_UInt32  ve14_drf_test_resume:1;
        RBus_UInt32  ve13_drf_test_resume:1;
        RBus_UInt32  ve12_drf_test_resume:1;
        RBus_UInt32  ve11_drf_test_resume:1;
        RBus_UInt32  ve10_drf_test_resume:1;
        RBus_UInt32  ve9_drf_test_resume:1;
        RBus_UInt32  ve8_drf_test_resume:1;
        RBus_UInt32  ve7_drf_test_resume:1;
        RBus_UInt32  ve6_drf_test_resume:1;
        RBus_UInt32  ve5_drf_test_resume:1;
        RBus_UInt32  ve4_drf_test_resume:1;
        RBus_UInt32  ve3_drf_test_resume:1;
        RBus_UInt32  ve2_drf_test_resume:1;
        RBus_UInt32  ve1_drf_test_resume:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_test_resume2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  ae_drf_test_resume:1;
        RBus_UInt32  etn2_drf_test_resume:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  md_drf_test_resume:1;
        RBus_UInt32  usb2_drf_test_resume:1;
        RBus_UInt32  usb1_drf_test_resume:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  kcpu1_drf_test_resume:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  vcpu_drf_test_resume:1;
        RBus_UInt32  acpu_drf_test_resume:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_test_resume3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  vde_drf_start_pause:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_start_pause1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  etn2_drf_start_pause:1;
        RBus_UInt32  vcpu_drf_start_pause:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_start_pause3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  kcpu_bisr_en:1;
        RBus_UInt32  vcpu_bisr_en:1;
        RBus_UInt32  acpu_bisr_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_bisr_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  cp42k_bisr_rstn:1;
        RBus_UInt32  kcpu_bisr_rstn:1;
        RBus_UInt32  vcpu_bisr_rstn:1;
        RBus_UInt32  acpu_bisr_rstn:1;
        RBus_UInt32  write_data:1;
    };
}crt_bisr_rstn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  cp42k_bisr_pwr_rstn:1;
        RBus_UInt32  kcpu_bisr_pwr_rstn:1;
        RBus_UInt32  vcpu_bisr_pwr_rstn:1;
        RBus_UInt32  acpu_bisr_pwr_rstn:1;
        RBus_UInt32  write_data:1;
    };
}crt_bisr_pwr_rstn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  cp42k_bisr_hold_remap:1;
        RBus_UInt32  kcpu_bisr_hold_remap:1;
        RBus_UInt32  vcpu_bisr_hold_remap:1;
        RBus_UInt32  acpu_bisr_hold_remap:1;
        RBus_UInt32  write_data:1;
    };
}crt_bisr_hold_remap1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  spnr_bisr_remap:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  iuzd_bisr_remap:1;
        RBus_UInt32  ich1_bisr_sdnr_remap:1;
    };
}crt_bisr_hold_remap2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  cp42k_bisr_second_run_en:1;
        RBus_UInt32  kcpu_bisr_second_run_en:1;
        RBus_UInt32  vcpu_bisr_second_run_en:1;
        RBus_UInt32  acpu_bisr_second_run_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_bisr_2nd_run_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  cp42k_drf_bisr_en:1;
        RBus_UInt32  kcpu_drf_bisr_en:1;
        RBus_UInt32  vcpu_drf_bisr_en:1;
        RBus_UInt32  acpu_drf_bisr_en:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_bisr_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  cp42k_drf_bisr_test_resume:1;
        RBus_UInt32  kcpu_drf_bisr_test_resume:1;
        RBus_UInt32  vcpu_drf_bisr_test_resume:1;
        RBus_UInt32  acpu_drf_bisr_test_resume:1;
        RBus_UInt32  write_data:1;
    };
}crt_drf_bisr_test_resume1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  vcpu_sleepsys_r:1;
        RBus_UInt32  acpu_sleepsys_r:1;
        RBus_UInt32  res2:1;
    };
}crt_sleep_ack1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  vcpu_sleepreq_r:1;
        RBus_UInt32  acpu_sleepreq_r:1;
        RBus_UInt32  write_data:1;
    };
}crt_sleep_req1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  nf_light_sleep:1;
        RBus_UInt32  md_light_sleep:1;
        RBus_UInt32  etn_light_sleep:1;
        RBus_UInt32  cp_light_sleep:1;
        RBus_UInt32  hdmitx_light_sleep:1;
        RBus_UInt32  dc_sb_light_sleep:1;
        RBus_UInt32  sb2_light_sleep:1;
        RBus_UInt32  ve_light_sleep:1;
        RBus_UInt32  sb2_rom_light_sleep:1;
        RBus_UInt32  kcpu_light_sleep:1;
        RBus_UInt32  vcpu_light_sleep:1;
        RBus_UInt32  acpu_light_sleep:1;
        RBus_UInt32  write_data:1;
    };
}crt_light_sleep1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  spnr_bisr_rstn:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  iuzd_bisr_rstn:1;
        RBus_UInt32  ich1_bisr_sdnr_rstn:1;
    };
}crt_bisr_rstn2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  mbist_ve_st:1;
        RBus_UInt32  mbist_tp_st:1;
        RBus_UInt32  mbist_md_st:1;
        RBus_UInt32  mbist_hdmi_st:1;
        RBus_UInt32  mbist_acpu_st:1;
    };
}bist_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  vcpu_bist_fail:1;
        RBus_UInt32  res2:9;
        RBus_UInt32  vde_bist_fail0:1;
        RBus_UInt32  sce_bist_fail:1;
        RBus_UInt32  kcpu_bist_fail:1;
        RBus_UInt32  etn_bist2_fail:1;
        RBus_UInt32  nf1_bist_fail:1;
        RBus_UInt32  me_bist_fail1:1;
        RBus_UInt32  me_bist_fail0:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  dc3_bist_fail:1;
        RBus_UInt32  dc2_bist_fail:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  cp_bist_fail:1;
        RBus_UInt32  ae_bist_fail:1;
    };
}bist_st2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  ve_bist17_fail:1;
        RBus_UInt32  ve_bist16_fail:1;
        RBus_UInt32  ve_bist15_fail:1;
        RBus_UInt32  ve_bist14_fail:1;
        RBus_UInt32  ve_bist13_fail:1;
        RBus_UInt32  ve_bist12_fail:1;
        RBus_UInt32  ve_bist11_fail:1;
        RBus_UInt32  ve_bist10_fail:1;
        RBus_UInt32  ve_bist9_fail:1;
        RBus_UInt32  ve_bist8_fail:1;
        RBus_UInt32  ve_bist7_fail:1;
        RBus_UInt32  ve_bist6_fail:1;
        RBus_UInt32  ve_bist5_fail:1;
        RBus_UInt32  ve_bist4_fail:1;
        RBus_UInt32  ve_bist3_fail:1;
        RBus_UInt32  ve_bist2_fail:1;
        RBus_UInt32  ve_bist1_fail:1;
    };
}bist_st3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  vcpu_drf_bist_fail:1;
        RBus_UInt32  vde_drf_bist_fail:1;
        RBus_UInt32  res2:10;
        RBus_UInt32  etn_drf_bist2_fail:1;
        RBus_UInt32  sce_drf_bist_fail:1;
        RBus_UInt32  nf1_drf_bist_fail:1;
        RBus_UInt32  me_drf_bist_fail1:1;
        RBus_UInt32  me_drf_bist_fail0:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  dc3_drf_bist_fail:1;
        RBus_UInt32  dc2_drf_bist_fail:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  cp_drf_bist_fail:1;
        RBus_UInt32  ae_drf_bist_fail:1;
    };
}drf_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  ve_drf_bist17_fail:1;
        RBus_UInt32  ve_drf_bist16_fail:1;
        RBus_UInt32  ve_drf_bist15_fail:1;
        RBus_UInt32  ve_drf_bist14_fail:1;
        RBus_UInt32  ve_drf_bist13_fail:1;
        RBus_UInt32  ve_drf_bist12_fail:1;
        RBus_UInt32  ve_drf_bist11_fail:1;
        RBus_UInt32  ve_drf_bist10_fail:1;
        RBus_UInt32  ve_drf_bist9_fail:1;
        RBus_UInt32  ve_drf_bist8_fail:1;
        RBus_UInt32  ve_drf_bist7_fail:1;
        RBus_UInt32  ve_drf_bist6_fail:1;
        RBus_UInt32  ve_drf_bist5_fail:1;
        RBus_UInt32  ve_drf_bist4_fail:1;
        RBus_UInt32  ve_drf_bist3_fail:1;
        RBus_UInt32  ve_drf_bist2_fail:1;
        RBus_UInt32  ve_drf_bist1_fail:1;
    };
}drf_st2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  spnr_bisr_done:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  i3ddma_uzd_bisr_done:1;
        RBus_UInt32  ich1_bisr_sdnr_done:1;
        RBus_UInt32  res3:20;
        RBus_UInt32  cp42k_bisr_done:1;
        RBus_UInt32  kcpu_bisr_done:1;
        RBus_UInt32  vcpu_bisr_done:1;
        RBus_UInt32  res4:1;
    };
}crt_bisr_done1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vcpu_bisr_fail:1;
        RBus_UInt32  res2:24;
        RBus_UInt32  cp42k_bisr_fail:1;
        RBus_UInt32  kcpu_bisr_st:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  acpu_bisr_st:1;
    };
}crt_bisr_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  cp42k_bisr_repaired:1;
        RBus_UInt32  kcpu_bisr_repaired:1;
        RBus_UInt32  vcpu_bisr_repaired:1;
        RBus_UInt32  acpu_bisr_repaired:1;
    };
}crt_bisr_repaired1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  vcpu_bisr_out:28;
    };
}crt_bisr_out1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  cp42k_bisr_out:7;
    };
}crt_bisr_out2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  vcpu_drf_bisr_fail:1;
        RBus_UInt32  res2:24;
        RBus_UInt32  cp42k_drf_bisr_fail:1;
        RBus_UInt32  cp42k_drf_bisr_done:1;
        RBus_UInt32  res3:2;
    };
}crt_drf_bisr_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  pll512fs_n:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  pll512fs_m:7;
        RBus_UInt32  pll512fs_bpn:1;
        RBus_UInt32  pll512fs_bps:1;
        RBus_UInt32  pll512fs_cs:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  pll512fs_ip:3;
        RBus_UInt32  pll512fs_s:3;
        RBus_UInt32  pll512fs_q:3;
        RBus_UInt32  pll512fs_rs:3;
        RBus_UInt32  pll512fs_tst:1;
        RBus_UInt32  pll512fs_wdrst:1;
        RBus_UInt32  pll512fs_wdset:1;
    };
}sys_pll_512fs1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  pll512fs_oeb:1;
        RBus_UInt32  pll512fs_rstb:1;
        RBus_UInt32  pll512fs_pow:1;
    };
}sys_pll_512fs2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  plldif_n:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  plldif_m:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  plldif_ip:3;
        RBus_UInt32  plldif_lf_rs:2;
        RBus_UInt32  plldif_lf_cp:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  res5:11;
    };
}sys_pll_dif1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  res2:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  plldif_wdmode:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  plldif_divdig_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  plldif_divadc_sel:3;
    };
}sys_pll_dif2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  plldif_vco_rstb:1;
        RBus_UInt32  plldif_rstb:1;
        RBus_UInt32  plldif_pow:1;
    };
}sys_pll_dif3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  pll27x_wdmode:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  pll27x_lf_cp:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  pll27x_lf_rs:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  pll27x_ip:3;
        RBus_UInt32  res5:6;
        RBus_UInt32  pll27x_n:2;
        RBus_UInt32  res6:1;
        RBus_UInt32  pll27x_m:7;
    };
}sys_pll_27x1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  pll_ldo_xtal_sel:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  pll_xixo_load:1;
        RBus_UInt32  pll_xixo_drive_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  pll_pow_ldo11v:1;
        RBus_UInt32  pll_ldo11v_sel:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  pll_pow_ldo:1;
        RBus_UInt32  pll_ldo_sel:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  pll27x_ps_54m_delay:2;
        RBus_UInt32  res6:2;
        RBus_UInt32  pll27x_ps_psel_pulse_w:1;
        RBus_UInt32  pll27x_ps_duty_sel:1;
    };
}sys_pll_27x2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  pll_reserve:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  pll27x_ps_en:1;
        RBus_UInt32  pll27x_ps_div2:1;
        RBus_UInt32  pll27x_vcorstb:1;
        RBus_UInt32  pll27x_rstb:1;
        RBus_UInt32  pll27x_pow:1;
    };
}sys_pll_27x3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  pll27x_ifadc_duty:2;
        RBus_UInt32  pll_yppadc_cko_54m_polar:1;
        RBus_UInt32  pll_yppadc_cko_polar:1;
        RBus_UInt32  pll_ifadc_cko_polar:1;
        RBus_UInt32  pll_l2h_cml_pow:1;
        RBus_UInt32  pll27x_d16_en:1;
        RBus_UInt32  pll27x_pll_tst:3;
        RBus_UInt32  pll27x_en_tst:1;
        RBus_UInt32  pll_rssi_cko_en:1;
        RBus_UInt32  pll27x_ck108m_en:1;
        RBus_UInt32  pll27x_ck108m_div:2;
        RBus_UInt32  pll27x_yppadc_cko_sel:2;
        RBus_UInt32  pll27x_yppadc_cko_en:1;
        RBus_UInt32  pll27x_yppadc_ck54m_en:1;
        RBus_UInt32  pll27x_ifadc_cko_sel:2;
        RBus_UInt32  pll27x_ifadc_div:1;
        RBus_UInt32  pll27x_ifadc_cko_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  pllaud_ckin_mux:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  pll27x_dvb_s2_demod_324m_div:1;
        RBus_UInt32  pll27x_dvb_s2_demod_324m_en:1;
        RBus_UInt32  pll_ck_ifadc_mux:1;
    };
}sys_pll_27x4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  pllaud_ip:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  pllaud_rs:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  pllaud_cp:2;
        RBus_UInt32  res4:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  res6:1;
        RBus_UInt32  pllaud_wdrst:1;
        RBus_UInt32  pllaud_wdset:1;
        RBus_UInt32  pllaud_tst:1;
    };
}sys_pll_aud1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  pllaud_rstb:1;
        RBus_UInt32  pllaud_oeb1:1;
        RBus_UInt32  pllaud_oeb2:1;
        RBus_UInt32  pllaud_pwdn:1;
    };
}sys_pll_aud3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  psaud_psen:1;
        RBus_UInt32  psaud_en:1;
        RBus_UInt32  psaud_tst:1;
        RBus_UInt32  psaud_ctrl:1;
    };
}sys_pll_psaud1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  psaud_div:4;
    };
}sys_pll_psaud2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_pll_dbug_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_dpi_oesync_op_sel:10;
        RBus_UInt32  reg_dpi_pdiv:2;
        RBus_UInt32  reg_dpi_clk_oe:10;
        RBus_UInt32  reg_dpi_mck_clk_en:8;
    };
}sys_pll_ddr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_en_post_pi:10;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_dpi_post_pi_rs:1;
        RBus_UInt32  reg_dpi_pll_sel_cpmode:1;
        RBus_UInt32  reg_dpi_cco_band:2;
        RBus_UInt32  reg_dpi_cco_kvco:1;
        RBus_UInt32  reg_dpi_icp:4;
        RBus_UInt32  reg_dpi_post_pi_bias:2;
        RBus_UInt32  reg_dpi_post_pi_rl:2;
        RBus_UInt32  reg_dpi_pll_ldo_vsel:2;
        RBus_UInt32  reg_dpi_lpf_sr:3;
        RBus_UInt32  reg_dpi_lpf_cp:1;
        RBus_UInt32  reg_dpi_loop_pi_isel:2;
    };
}sys_pll_ddr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_dpi_post_pi_sel3:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_dpi_post_pi_sel2:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_dpi_post_pi_sel1:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_dpi_post_pi_sel0:6;
    };
}sys_pll_ddr3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_dpi_post_pi_sel7:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_dpi_post_pi_sel6:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_dpi_post_pi_sel5:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_dpi_post_pi_sel4:6;
    };
}sys_pll_ddr4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_post_pi_sel7:5;
        RBus_UInt32  reg_dpi_post_pi_sel9:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_dpi_post_pi_sel8:6;
        RBus_UInt32  reg_v11_ldo_vsel:2;
        RBus_UInt32  reg_dpi_f390k:2;
        RBus_UInt32  reg_dpi_wd_enable:1;
        RBus_UInt32  reg_dpi_time2_rst_width:2;
        RBus_UInt32  reg_dpi_time_rdy_ckout:2;
        RBus_UInt32  reg_dpi_time0_ck:3;
    };
}sys_pll_ddr_ssc1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_dpi_sel_mode:1;
        RBus_UInt32  reg_dpi_n_code:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_dpi_f_code:13;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_dpi_en_ssc:1;
        RBus_UInt32  reg_dpi_bypass_pi:1;
        RBus_UInt32  reg_dpi_en_center_in:1;
    };
}sys_pll_ddr_ssc2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_weighting_sel:3;
        RBus_UInt32  reg_dpi_order:1;
        RBus_UInt32  reg_dpi_tbase:12;
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_dpi_step_in:13;
    };
}sys_pll_ddr_ssc3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  reg_dpi_loop_pi_isel_2:1;
        RBus_UInt32  reg_dpi_pll_dum:8;
    };
}sys_pll_ddr5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  pll_stable:1;
    };
}sys_pll_ddr5_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dpi_dummy_in_dll:32;
    };
}sys_pll_dummy_in_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dpi_dummy_out_dll:32;
    };
}sys_pll_dummy_out_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_field_flag_mode_en:1;
        RBus_UInt32  dclk_filed_flag_slt:3;
        RBus_UInt32  dclk_offset_11_0:12;
        RBus_UInt32  dclk_new_en:1;
        RBus_UInt32  dclk_ss_test:1;
        RBus_UInt32  dclk_freq_syn_slt:6;
        RBus_UInt32  dclk_ss_rag:4;
        RBus_UInt32  dummy18000300_3:1;
        RBus_UInt32  dclk_ss_load:1;
        RBus_UInt32  dummy18000300_1:1;
        RBus_UInt32  dclk_ss_en:1;
    };
}sys_dclkss_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sscg_mcode_slow_modify_valid:1;
        RBus_UInt32  sscg_mcode_slow_modify_stable:1;
        RBus_UInt32  sscg_mcode_slow_modify_pixel:12;
        RBus_UInt32  sscg_offset_slow_modify_valid:1;
        RBus_UInt32  sscg_offset_slow_modify_stable:1;
        RBus_UInt32  sscg_offset_slow_modify_pixel:12;
        RBus_UInt32  in_frame_tracking_offset_inverse:1;
        RBus_UInt32  in_frame_tracking_ypbpr_en:1;
        RBus_UInt32  in_frame_tracking_vd_dec_en:1;
        RBus_UInt32  in_frame_tracking_general_en:1;
    };
}dpll_in_fsync_tracking_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  in_frame_tracking_neg_th:12;
        RBus_UInt32  in_frame_tracking_pos_th:12;
        RBus_UInt32  in_frame_tracking_mul:8;
    };
}dpll_in_fsync_tracking_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sscg_offset_over_flag:1;
        RBus_UInt32  sscg_profile_over_underflow_flag:1;
        RBus_UInt32  sscg_profile_protection:1;
        RBus_UInt32  sscg_offset_over_th_max:13;
        RBus_UInt32  dpll_mcode_protection:1;
        RBus_UInt32  dpll_mcode_protection_ready_width:2;
        RBus_UInt32  sscg_offset_over_th_value:13;
    };
}dpll_in_fsync_tracking_debug_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  frc2fsync_speedup_m_code:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  frc2fsync_speedup_offset:11;
    };
}dclk_frc2fsync_speedup_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  final_m_code:10;
        RBus_UInt32  res2:3;
        RBus_UInt32  final_profile:13;
    };
}dpll_status_ro_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  final_profile_force_64n_en:2;
        RBus_UInt32  dclk_ss_async_protection:1;
        RBus_UInt32  res1:14;
        RBus_UInt32  dclk_ss_fmdiv:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  dclk_ss_protection_cnt_max:7;
    };
}dclkss_freq_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1800031c_31_30:2;
        RBus_UInt32  dclk_ss_shuffle_en:1;
        RBus_UInt32  dclk_profile_remap_en:1;
        RBus_UInt32  dclk_profile_remap_1:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_0:12;
    };
}dclkss_profile0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_3:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_2:12;
    };
}dclkss_profile1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_5:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_4:12;
    };
}dclkss_profile2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_7:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_6:12;
    };
}dclkss_profile3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_9:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_8:12;
    };
}dclkss_profile4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_11:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_10:12;
    };
}dclkss_profile5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_13:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_12:12;
    };
}dclkss_profile6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_15:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_14:12;
    };
}dclkss_profile7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_17:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_16:12;
    };
}dclkss_profile8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_19:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_18:12;
    };
}dclkss_profile9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_21:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_20:12;
    };
}dclkss_profile10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_23:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_22:12;
    };
}dclkss_profile11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_25:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_24:12;
    };
}dclkss_profile12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_27:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_26:12;
    };
}dclkss_profile13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_29:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_28:12;
    };
}dclkss_profile14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  dclk_profile_remap_31:13;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_30:12;
    };
}dclkss_profile15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  double_buf_en:1;
        RBus_UInt32  double_buf_read_sel:1;
        RBus_UInt32  double_buf_apply:1;
    };
}dpll_double_buffer_ctrl_RBUS;





#else //apply LITTLE_ENDIAN


//======CRT register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vercode:32;
    };
}sc_verid_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stbldo_pow:1;
        RBus_UInt32  ldov10_sel:3;
        RBus_UInt32  bufm_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  por_v10set_l:2;
        RBus_UInt32  por_v33set_l:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  main_por_en:1;
        RBus_UInt32  main_pow_on:1;
        RBus_UInt32  en_emb:1;
        RBus_UInt32  cap_emb:2;
        RBus_UInt32  div_emb:2;
        RBus_UInt32  por_reser:12;
    };
}sc_lv_rst_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  porl_hif_loc:1;
        RBus_UInt32  porl_ejtag_loc:1;
        RBus_UInt32  porl_ejtag_mode:1;
        RBus_UInt32  porl_boot_opt:2;
        RBus_UInt32  porl_test_en_n:1;
        RBus_UInt32  porl_ejtag_en_n:1;
        RBus_UInt32  porl_test_mode:6;
        RBus_UInt32  porl_host_s_en_n:1;
        RBus_UInt32  porl_dis_por:1;
        RBus_UInt32  porl_pll_en:1;
        RBus_UInt32  porl_at_speed_scan:1;
        RBus_UInt32  at_speed_pll_done:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  pad_boption7:1;
        RBus_UInt32  pad_boption9:1;
    };
}sc_pol_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mt_isln_en:1;
        RBus_UInt32  rstn_mt:1;
        RBus_UInt32  rstn_getn:1;
        RBus_UInt32  ddr_isln_en:1;
        RBus_UInt32  efuse_isln_en:1;
        RBus_UInt32  res1:27;
    };
}st_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rstn_iso_misc:1;
        RBus_UInt32  rstn_iso_misc_off:1;
        RBus_UInt32  rstn_pad_mux:1;
        RBus_UInt32  rstn_pwm:1;
        RBus_UInt32  rstn_irda_off:1;
        RBus_UInt32  rstn_uart0_off:1;
        RBus_UInt32  rstn_i2c0_off:1;
        RBus_UInt32  res1:25;
    };
}st_srst0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rstn_lsadc:1;
        RBus_UInt32  rstn_ddc:1;
        RBus_UInt32  rstn_irda:1;
        RBus_UInt32  rstn_alu:1;
        RBus_UInt32  rstn_cbus:1;
        RBus_UInt32  rstn_cbus_tx:1;
        RBus_UInt32  rstn_syncp:1;
        RBus_UInt32  rstn_cec:1;
        RBus_UInt32  rstn_hdmi_det:1;
        RBus_UInt32  rstn_emcu_core:1;
        RBus_UInt32  rstn_emcu_top:1;
        RBus_UInt32  rstn_rtc:1;
        RBus_UInt32  rstn_osc:1;
        RBus_UInt32  rstn_ddc1:1;
        RBus_UInt32  rstn_ddc2:1;
        RBus_UInt32  rstn_ddc3:1;
        RBus_UInt32  rstn_vfd:1;
        RBus_UInt32  res1:15;
    };
}st_srst1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clken_iso_misc:1;
        RBus_UInt32  clken_iso_misc_off:1;
        RBus_UInt32  clken_pad_mux:1;
        RBus_UInt32  clken_pwm:1;
        RBus_UInt32  clken_irda_off:1;
        RBus_UInt32  clken_uart0_off:1;
        RBus_UInt32  clken_i2c0_off:1;
        RBus_UInt32  res1:25;
    };
}st_clken0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clken_lsadc:1;
        RBus_UInt32  clken_ddc:1;
        RBus_UInt32  clken_irda:1;
        RBus_UInt32  clken_alu:1;
        RBus_UInt32  clken_cbus:1;
        RBus_UInt32  clken_cbus_tx:1;
        RBus_UInt32  clken_syncp:1;
        RBus_UInt32  clken_cec:1;
        RBus_UInt32  clken_hdmi_det:1;
        RBus_UInt32  clken_emcu_core:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  clken_rtc:1;
        RBus_UInt32  clken_osc:1;
        RBus_UInt32  clken_ddc1:1;
        RBus_UInt32  clken_ddc2:1;
        RBus_UInt32  clken_ddc3:1;
        RBus_UInt32  clken_vfd:1;
        RBus_UInt32  clken_cbus_tx_ip:1;
        RBus_UInt32  res1:14;
    };
}st_clken1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mhl_clkdiv_en:1;
        RBus_UInt32  mhl_clkdiv:3;
        RBus_UInt32  res1:28;
    };
}st_mhl_cbus_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bus_clksel:1;
        RBus_UInt32  res3:11;
        RBus_UInt32  bus_div_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  bus_div_busy:1;
        RBus_UInt32  bus_div_apply:1;
        RBus_UInt32  bus_div_en:1;
        RBus_UInt32  res1:13;
    };
}st_busclk_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res4:1;
        RBus_UInt32  res3:11;
        RBus_UInt32  emcu_div_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  emcu_div_busy:1;
        RBus_UInt32  emcu_div_apply:1;
        RBus_UInt32  emcu_div_en:1;
        RBus_UInt32  res1:13;
    };
}st_emcuclk_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  uart_clksel:1;
        RBus_UInt32  osc_clksel:1;
        RBus_UInt32  res1:30;
    };
}st_clkmux_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  st2_de_iso_ps_tim:4;
        RBus_UInt32  st2_wakeup_tim:4;
        RBus_UInt32  res1:23;
        RBus_UInt32  st2_isln_en:1;
    };
}st_alu_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stie_iso_misc:1;
        RBus_UInt32  stie_cbus:1;
        RBus_UInt32  stie_cec:1;
        RBus_UInt32  stie_rtc:1;
        RBus_UInt32  stie_self_wakeup:1;
        RBus_UInt32  stie_cbus_tx:1;
        RBus_UInt32  res1:26;
    };
}alu_ie_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stip_iso_misc:1;
        RBus_UInt32  stip_cbus:1;
        RBus_UInt32  stip_cec:1;
        RBus_UInt32  stip_rtc:1;
        RBus_UInt32  stip_self_wakeup:1;
        RBus_UInt32  stip_cbus_tx:1;
        RBus_UInt32  res1:26;
    };
}alu_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  stpass_iso_misc:1;
        RBus_UInt32  stpass_cbus:1;
        RBus_UInt32  stpass_cec:1;
        RBus_UInt32  stpass_rtc:1;
        RBus_UInt32  stpass_self_wakeup:1;
        RBus_UInt32  stpass_cbus_tx:1;
        RBus_UInt32  res1:26;
    };
}alu_pass_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  iso_misc_scpu_ie:1;
        RBus_UInt32  iso_misc_off_scpu_ie:1;
        RBus_UInt32  syncp_scpu_ie:1;
        RBus_UInt32  hdmi_clk_det_scpu_ie:1;
        RBus_UInt32  cbus_scpu_ie:1;
        RBus_UInt32  cec_scpu_ie:1;
        RBus_UInt32  rtc_scpu_ie:1;
        RBus_UInt32  rtc_acpu_ie:1;
        RBus_UInt32  cbus_tx_scpu_ie:1;
        RBus_UInt32  iso_misc_kcpu_ie:1;
        RBus_UInt32  iso_misc_off_kcpu_ie:1;
        RBus_UInt32  syncp_kcpu_ie:1;
        RBus_UInt32  hdmi_clk_det_kcpu_ie:1;
        RBus_UInt32  cbus_kcpu_ie:1;
        RBus_UInt32  cec_kcpu_ie:1;
        RBus_UInt32  rtc_kcpu_ie:1;
        RBus_UInt32  cbus_tx_kcpu_ie:1;
        RBus_UInt32  res1:15;
    };
}stb_irq_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  osc_tracking_en:1;
        RBus_UInt32  osc_tracking_mode:2;
        RBus_UInt32  osc_rstb_emb:1;
        RBus_UInt32  osc_cnt_diff:8;
        RBus_UInt32  osc_status:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  osc_sw_s:7;
        RBus_UInt32  s_emb:7;
        RBus_UInt32  res1:2;
    };
}st_ring_osc_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  osc_detection_en:1;
        RBus_UInt32  ddr_iso_rst1_en:1;
        RBus_UInt32  dummy180600e8_7_2:6;
        RBus_UInt32  osc_detection:10;
        RBus_UInt32  res1:14;
    };
}st_ring_osc_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dbg_div_sel:2;
        RBus_UInt32  res2:14;
        RBus_UInt32  crt_dbg_sel:4;
        RBus_UInt32  alu_dbg_sel:7;
        RBus_UInt32  alu_test_mode_en:1;
        RBus_UInt32  res1:4;
    };
}st_dbg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data1:32;
    };
}wdog_data1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data2:32;
    };
}wdog_data2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data3:32;
    };
}wdog_data3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data4:32;
    };
}wdog_data4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data5:32;
    };
}wdog_data5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data6:32;
    };
}wdog_data6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data7:32;
    };
}wdog_data7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data8:32;
    };
}wdog_data8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data9:32;
    };
}wdog_data9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data10:32;
    };
}wdog_data10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data11:32;
    };
}wdog_data11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wdog_data12:32;
    };
}wdog_data12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rstn_misc:1;
        RBus_UInt32  rstn_rng:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  rstn_gspi:1;
        RBus_UInt32  rstn_usb_arb:1;
        RBus_UInt32  rstn_usb_mac1:1;
        RBus_UInt32  rstn_usb_mac0:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  rstn_usb_phy0:1;
        RBus_UInt32  rstn_usb_phy1:1;
        RBus_UInt32  rstn_usb_phy2:1;
        RBus_UInt32  rstn_ddc:1;
        RBus_UInt32  rstn_hdmi:1;
        RBus_UInt32  rstn_etn:1;
        RBus_UInt32  rstn_etn_phy:1;
        RBus_UInt32  rstn_aio:1;
        RBus_UInt32  rstn_me1:1;
        RBus_UInt32  rstn_ve_p2:1;
        RBus_UInt32  rstn_ve:1;
        RBus_UInt32  rstn_tve:1;
        RBus_UInt32  rstn_vo:1;
        RBus_UInt32  rstn_gpu:1;
        RBus_UInt32  rstn_se:1;
        RBus_UInt32  rstn_dcu:1;
        RBus_UInt32  rstn_dc_phy:1;
        RBus_UInt32  rstn_cp:1;
        RBus_UInt32  rstn_md:1;
        RBus_UInt32  rstn_tp:1;
        RBus_UInt32  rstn_ae:1;
        RBus_UInt32  rstn_nf:1;
        RBus_UInt32  rstn_demod:1;
        RBus_UInt32  res1:1;
    };
}soft_reset1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rstn_acpu:1;
        RBus_UInt32  rstn_vcpu:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  rstn_vde:1;
        RBus_UInt32  rstn_scpu:1;
        RBus_UInt32  rstn_pllreg:1;
        RBus_UInt32  rstn_gpio:1;
        RBus_UInt32  rstn_pwm:1;
        RBus_UInt32  rstn_scpu_wrap:1;
        RBus_UInt32  rstn_pcr_cnt:1;
        RBus_UInt32  rstn_cr:1;
        RBus_UInt32  rstn_emmc:1;
        RBus_UInt32  rstn_dtv_demod:1;
        RBus_UInt32  rstn_padmux:1;
        RBus_UInt32  rstn_usb_mac:1;
        RBus_UInt32  rstn_bistreg:1;
        RBus_UInt32  rstn_atvin:1;
        RBus_UInt32  rstn_atvin2:1;
        RBus_UInt32  rstn_tm:1;
        RBus_UInt32  rstn_tve_clkgen:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  rstn_cec:1;
        RBus_UInt32  rstn_ir:1;
        RBus_UInt32  rstn_sc:1;
        RBus_UInt32  rstn_pcmcia:1;
        RBus_UInt32  rstn_i2c_2:1;
        RBus_UInt32  rstn_i2c_1:1;
        RBus_UInt32  rstn_i2c_0:1;
        RBus_UInt32  rstn_ur1:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  rstn_ur2:1;
    };
}soft_reset2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rstn_sb2:1;
        RBus_UInt32  rstn_disp:1;
        RBus_UInt32  rstn_dispim:1;
        RBus_UInt32  rstn_vodma:1;
        RBus_UInt32  rstn_apll_adc:1;
        RBus_UInt32  rstn_ifadc:1;
        RBus_UInt32  rstn_audio_dac:1;
        RBus_UInt32  rstn_audio_adc:1;
        RBus_UInt32  rstn_audio2_dac:1;
        RBus_UInt32  rstn_vbis0:1;
        RBus_UInt32  rstn_vdec2:1;
        RBus_UInt32  rstn_if_demod:1;
        RBus_UInt32  rstn_tvsb2:1;
        RBus_UInt32  rstn_tvsb1:1;
        RBus_UInt32  rstn_tvsb3:1;
        RBus_UInt32  rstn_osdcomp:1;
        RBus_UInt32  rstn_tv_tve:1;
        RBus_UInt32  rstn_hdmirx:1;
        RBus_UInt32  rstn_kcpu:1;
        RBus_UInt32  rstn_vdec:1;
        RBus_UInt32  rstn_tvsb1_tve:1;
        RBus_UInt32  res1:4;
        RBus_UInt32  rstn_scpu_l2:1;
        RBus_UInt32  rstn_scpu_dbg:1;
        RBus_UInt32  rstn_kt:1;
        RBus_UInt32  rstn_sce:1;
        RBus_UInt32  rstn_dsc:1;
        RBus_UInt32  rstn_nd:1;
        RBus_UInt32  rstn_akl:1;
    };
}soft_reset3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clk_en_misc:1;
        RBus_UInt32  clk_en_hdmirx:1;
        RBus_UInt32  clk_en_usb1:1;
        RBus_UInt32  clk_en_gspi:1;
        RBus_UInt32  clk_en_usb0:1;
        RBus_UInt32  clk_en_pcr:1;
        RBus_UInt32  clk_en_iso_misc:1;
        RBus_UInt32  reg_clken_3d_gde:1;
        RBus_UInt32  clk_en_hdmi:1;
        RBus_UInt32  clk_en_etn:1;
        RBus_UInt32  clk_en_aio:1;
        RBus_UInt32  clk_en_tve_sys:1;
        RBus_UInt32  clk_en_ve_p2:1;
        RBus_UInt32  clk_en_ve:1;
        RBus_UInt32  clk_en_tve:1;
        RBus_UInt32  clken_tve_clkgen:1;
        RBus_UInt32  clken_tv_tve:1;
        RBus_UInt32  clk_en_se:1;
        RBus_UInt32  clk_en_dcu:1;
        RBus_UInt32  clk_en_cp:1;
        RBus_UInt32  clk_en_md:1;
        RBus_UInt32  clk_en_tp:1;
        RBus_UInt32  clk_en_ae:1;
        RBus_UInt32  clk_en_nf:1;
        RBus_UInt32  clk_en_emmc:1;
        RBus_UInt32  clk_en_cr:1;
        RBus_UInt32  clken_vdec:1;
        RBus_UInt32  clk_en_demod:1;
        RBus_UInt32  clken_tvsb1_tve:1;
        RBus_UInt32  res1:3;
    };
}clock_enable1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_clken_scpu_cssys:1;
        RBus_UInt32  clk_en_scpu:1;
        RBus_UInt32  clk_en_scpu_wrap:1;
        RBus_UInt32  clk_en_acpu:1;
        RBus_UInt32  clk_en_vcpu:1;
        RBus_UInt32  clk_en_ade:1;
        RBus_UInt32  clk_en_vde:1;
        RBus_UInt32  clk_en_me1:1;
        RBus_UInt32  clk_en_misc_vfd:1;
        RBus_UInt32  clk_en_misc_rtc:1;
        RBus_UInt32  clk_en_misc_cec:1;
        RBus_UInt32  clk_en_misc_ir:1;
        RBus_UInt32  clk_en_misc_sc:1;
        RBus_UInt32  clk_en_misc_pcmcia:1;
        RBus_UInt32  clk_en_misc_i2c_1:1;
        RBus_UInt32  clk_en_misc_i2c_0:1;
        RBus_UInt32  clk_en_iso_mis:1;
        RBus_UInt32  res3:6;
        RBus_UInt32  clk_en_misc_i2c_2:1;
        RBus_UInt32  clk_en_pwm:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  clk_en_ur1:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  clk_en_ur2:1;
    };
}clock_enable2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clk_en_sb2:1;
        RBus_UInt32  clk_en_kcpu:1;
        RBus_UInt32  clken_pllreg:1;
        RBus_UInt32  clken_disp:1;
        RBus_UInt32  clken_dispim:1;
        RBus_UInt32  clken_vodma:1;
        RBus_UInt32  clken_ddc:1;
        RBus_UInt32  clk_en_kt:1;
        RBus_UInt32  clk_en_sce:1;
        RBus_UInt32  clk_en_dsc:1;
        RBus_UInt32  clk_en_akl:1;
        RBus_UInt32  clken_dtv_demod:1;
        RBus_UInt32  clken_padmux:1;
        RBus_UInt32  clken_audio2_daad_128fs:1;
        RBus_UInt32  clken_audio2_daad_256fs:1;
        RBus_UInt32  clken_audio2_512fs:1;
        RBus_UInt32  clken_ifadc:1;
        RBus_UInt32  clken_audio_pre512fs:1;
        RBus_UInt32  clken_audio_daad_256fs:1;
        RBus_UInt32  clken_audio_daad_128fs:1;
        RBus_UInt32  clken_vbis0:1;
        RBus_UInt32  clken_bistreg:1;
        RBus_UInt32  clken_disp2tve:1;
        RBus_UInt32  clken_if_demod:1;
        RBus_UInt32  clken_apll_adc:1;
        RBus_UInt32  clken_osdcomp:1;
        RBus_UInt32  clken_atvin_ifd:1;
        RBus_UInt32  clken_atvin_vd:1;
        RBus_UInt32  clken_tm:1;
        RBus_UInt32  clken_tvsb3:1;
        RBus_UInt32  clken_tvsb2:1;
        RBus_UInt32  clken_tvsb1:1;
    };
}group1_ck_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sclk_sel:1;
        RBus_UInt32  res5:3;
        RBus_UInt32  inv_vbis0_clk:1;
        RBus_UInt32  vbis0_yppsel:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  vdec_x27_clksel:1;
        RBus_UInt32  res3:6;
        RBus_UInt32  atvin_vdadc_tve_clk_sel:1;
        RBus_UInt32  atvin_vd_clk_sel:1;
        RBus_UInt32  atvin_clk_sel:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  epi_div_clksel:2;
        RBus_UInt32  epi_dbg_clksel:1;
        RBus_UInt32  ve_rif_use_p2clk:1;
        RBus_UInt32  res1:5;
    };
}group1_ck_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tveck_mix_sel:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  dac1_ckinv:1;
        RBus_UInt32  dac2_ckinv:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  hdmi_phy_ckinv:1;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  clk_tve_p_vo_clk_sel:1;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  clk_tve_p_vo_clk_sel2:1;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  res1:19;
    };
}tve_ck_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dac1_div:5;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  dac2_div:5;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  res1:20;
    };
}disp_pll_div_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tve_div:4;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  hdmi_div:3;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  hdmi_phy_clk_sel:1;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  hdmi_pxl_repeat:1;
        RBus_UInt32  write_en6:1;
        RBus_UInt32  sel_pllhdmi_clk:1;
        RBus_UInt32  write_en7:1;
        RBus_UInt32  sel_plldisp_clk2:1;
        RBus_UInt32  write_en8:1;
        RBus_UInt32  hdmi_tmds_div:2;
        RBus_UInt32  write_en9:1;
        RBus_UInt32  tve_i_div:2;
        RBus_UInt32  write_en10:1;
        RBus_UInt32  hdmi_deep_clk_sel:1;
        RBus_UInt32  write_en11:1;
        RBus_UInt32  res1:7;
    };
}disp_pll_div2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dac2_phy_clk_inv:1;
        RBus_UInt32  reg_dac1_phy_clk_inv:1;
        RBus_UInt32  reg_tve_iclk_sel:2;
        RBus_UInt32  reg_dac2_clk_sel:2;
        RBus_UInt32  reg_tve_pclk_sel:2;
        RBus_UInt32  reg_dac1_clk_sel:2;
        RBus_UInt32  reg_tve_hdmi_div_sel:2;
        RBus_UInt32  reg_hdmi_tmds_div:2;
        RBus_UInt32  res1:18;
    };
}disp_pll_div3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_use_sysclk:1;
        RBus_UInt32  res1:31;
    };
}audio_clk_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bus_freq_sel:1;
        RBus_UInt32  ddr_freq_sel:2;
        RBus_UInt32  acpu_freq_sel:2;
        RBus_UInt32  vcpu_freq_sel:2;
        RBus_UInt32  scpu_freq_sel:2;
        RBus_UInt32  res1:23;
    };
}pll_div_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  nf_div:3;
        RBus_UInt32  res1:29;
    };
}nf_cksel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  nds_sc_div:3;
        RBus_UInt32  res1:29;
    };
}nds_sc_cksel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cr_div:3;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  emmc_div:3;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  res1:22;
        RBus_UInt32  cremmc_clk_sel:1;
        RBus_UInt32  write_en3:1;
    };
}cr_cksel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aud_dtv_freq_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  dtv_demod_multi_req_disable:1;
        RBus_UInt32  res1:27;
    };
}clkdiv_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scpu_wd_cnt:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  scpu_wd_en:1;
        RBus_UInt32  res1:15;
    };
}arm_wd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dtv_str_pow:1;
        RBus_UInt32  res6:1;
        RBus_UInt32  dtv_str_status:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  dtv_iso_en:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  atv_str_pow:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  atv_str_status:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  atv_iso_en:1;
        RBus_UInt32  res1:19;
    };
}power_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllscpu_wdout:1;
        RBus_UInt32  reg_pllacpu_wdout:1;
        RBus_UInt32  reg_pllvcpu_wdout:1;
        RBus_UInt32  plldds_wdout:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  plldisp_wdout:1;
        RBus_UInt32  reg_pllbus_wdout:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  plletn_wdout:1;
        RBus_UInt32  pllbus2_wdout:1;
        RBus_UInt32  plldif_wdout:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pllbush_wdout:1;
        RBus_UInt32  pll512fs_wdout:1;
        RBus_UInt32  pllaud_status:1;
        RBus_UInt32  pllgpu_wdout_2:1;
        RBus_UInt32  pllgpu_wdout:1;
        RBus_UInt32  reg_pllvodma_wdout:1;
        RBus_UInt32  pll27x_wdout:1;
        RBus_UInt32  res1:13;
    };
}pll_wdout_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tm_pwron_dly:16;
        RBus_UInt32  tm_data_out:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  tm_reverse_cmp_out:1;
        RBus_UInt32  tm_data_sampled:1;
        RBus_UInt32  tm_data_valid:1;
        RBus_UInt32  tm_enable:1;
        RBus_UInt32  res1:4;
    };
}tm_ctrl0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tm_sample_dly:16;
        RBus_UInt32  tm_compare_dly:16;
    };
}tm_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_tm_pow:1;
        RBus_UInt32  reg_tm_sinl:2;
        RBus_UInt32  reg_tm_sos:3;
        RBus_UInt32  reg_tm_sbg:3;
        RBus_UInt32  res1:22;
    };
}tm_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_dss_rst_n:1;
        RBus_UInt32  dss_c35d5_ro_sel:3;
        RBus_UInt32  dss_c35d5_wire_sel:1;
        RBus_UInt32  dss_c35d5_data_in:20;
        RBus_UInt32  dss_c35d5_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss00_dss_gpu0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_ready:1;
        RBus_UInt32  dss_c35d5_count_out:20;
        RBus_UInt32  dss_c35d5_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss01_dss_gpu0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss02_dss_gpu0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dss_rst_n:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss03_dss_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_ready:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss04_dss_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss05_dss_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_dss_rst_n:1;
        RBus_UInt32  dss_c35d5_ro_sel:3;
        RBus_UInt32  dss_c35d5_wire_sel:1;
        RBus_UInt32  dss_c35d5_data_in:20;
        RBus_UInt32  dss_c35d5_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss06_dss_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_ready:1;
        RBus_UInt32  dss_c35d5_count_out:20;
        RBus_UInt32  dss_c35d5_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss07_dss_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss08_dss_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dss_rst_n:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss09_dss_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_ready:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss10_dss_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss11_dss_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dss_rst_n:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss12_dss_top0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_ready:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss13_dss_top0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss14_dss_top0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dss_rst_n:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss15_dss_tvsb10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_ready:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss16_dss_tvsb10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss17_dss_tvsb10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_dss_rst_n:1;
        RBus_UInt32  dss_c35d5_ro_sel:3;
        RBus_UInt32  dss_c35d5_wire_sel:1;
        RBus_UInt32  dss_c35d5_data_in:20;
        RBus_UInt32  dss_c35d5_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss18_dss_tvsb11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_ready:1;
        RBus_UInt32  dss_c35d5_count_out:20;
        RBus_UInt32  dss_c35d5_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss19_dss_tvsb11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35d5_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss20_dss_tvsb11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dss_rst_n:1;
        RBus_UInt32  dss_c35_ro_sel:3;
        RBus_UInt32  dss_c35_wire_sel:1;
        RBus_UInt32  dss_c35_data_in:20;
        RBus_UInt32  dss_c35_speed_en:1;
        RBus_UInt32  res1:6;
    };
}dss21_dss_tvsb30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_ready:1;
        RBus_UInt32  dss_c35_count_out:20;
        RBus_UInt32  dss_c35_wsort_go:1;
        RBus_UInt32  res1:10;
    };
}dss22_dss_tvsb30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dss_c35_dbgo:16;
        RBus_UInt32  res1:16;
    };
}dss23_dss_tvsb30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm0_rstn:1;
        RBus_UInt32  csm0_csm_en:1;
        RBus_UInt32  csm0_in_sel:2;
        RBus_UInt32  csm0_acc_mode:1;
        RBus_UInt32  csm0_hold:1;
        RBus_UInt32  csm0_read_en:1;
        RBus_UInt32  csm0_addr:4;
        RBus_UInt32  csm0_data_sel:2;
        RBus_UInt32  res1:19;
    };
}csm00_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm0_ready:1;
        RBus_UInt32  res1:31;
    };
}csm01_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm0_data:32;
    };
}csm02_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm1_rstn:1;
        RBus_UInt32  csm1_csm_en:1;
        RBus_UInt32  csm1_in_sel:2;
        RBus_UInt32  csm1_acc_mode:1;
        RBus_UInt32  csm1_hold:1;
        RBus_UInt32  csm1_read_en:1;
        RBus_UInt32  csm1_addr:4;
        RBus_UInt32  csm1_data_sel:2;
        RBus_UInt32  res1:19;
    };
}csm03_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm1_ready:1;
        RBus_UInt32  res1:31;
    };
}csm04_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  csm1_data:32;
    };
}csm05_csm_ddr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_200:4;
        RBus_UInt32  rme_200:1;
        RBus_UInt32  rm_300:4;
        RBus_UInt32  rme_300:1;
        RBus_UInt32  rm_400:4;
        RBus_UInt32  rme_400:1;
        RBus_UInt32  rm_600:4;
        RBus_UInt32  rme_600:1;
        RBus_UInt32  rm_800:4;
        RBus_UInt32  rme_800:1;
        RBus_UInt32  rm_rom:4;
        RBus_UInt32  rme_rom:1;
        RBus_UInt32  res1:2;
    };
}chip_sram_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  resume_cycle_sel:1;
        RBus_UInt32  res1:31;
    };
}chip_misc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sf_sel:1;
        RBus_UInt32  nf_sel:1;
        RBus_UInt32  testmode:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  clk_na_fail:1;
        RBus_UInt32  res1:23;
    };
}chip_info2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dds_rstn:1;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  res1:30;
    };
}aps_ctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  kcpu_boot_info:32;
    };
}pwdn_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  acpu_boot_info:32;
    };
}pwdn_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  kcpu_sw_rst:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  kcpu_boot_info_valid:1;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  res1:28;
    };
}pwdn_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  acpu_boot_info_valid:1;
        RBus_UInt32  res1:31;
    };
}pwdn_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  scpu_config_done:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  dac_test:1;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  res1:28;
    };
}at_speed_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  etn_phy_125m_en:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  etn_phy_gpio_en:1;
        RBus_UInt32  write_en2:1;
        RBus_UInt32  res1:28;
    };
}ana_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tp0_dm_sel:1;
        RBus_UInt32  tp1_dm_sel:1;
        RBus_UInt32  tp2_dm_sel:1;
        RBus_UInt32  demod_i2c_sel:1;
        RBus_UInt32  demod_i2c_saddr:1;
        RBus_UInt32  res1:27;
    };
}tp_demod_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sf_en:1;
        RBus_UInt32  res1:31;
    };
}control0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  akl_busy:1;
        RBus_UInt32  res1:31;
    };
}security_st_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reserved1:32;
    };
}dmy2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bus_ssc_stms:2;
        RBus_UInt32  res2:6;
        RBus_UInt32  bus_ssc_ssfpv:8;
        RBus_UInt32  bus_ssc_ssn:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  bus_ssc_sss:6;
        RBus_UInt32  bus_ssc_ckinv:1;
        RBus_UInt32  bus_ssc_sse:1;
    };
}bus_pll_ssc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dcsb_ssc_stms:2;
        RBus_UInt32  res2:6;
        RBus_UInt32  dcsb_ssc_ssfpv:8;
        RBus_UInt32  dcsb_ssc_ssn:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  dcsb_ssc_sss:6;
        RBus_UInt32  dcsb_ssc_ckinv:1;
        RBus_UInt32  dcsb_ssc_sse:1;
    };
}dcsb_pll_ssc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllscpu_tst:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllscpu_wdset:1;
        RBus_UInt32  reg_pllscpu_wdrst:1;
        RBus_UInt32  reg_pllscpu_o:2;
        RBus_UInt32  reg_pllscpu_ip:3;
        RBus_UInt32  reg_pllscpu_m:8;
        RBus_UInt32  reg_pllscpu_n:2;
        RBus_UInt32  res1:10;
    };
}pll_scpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllscpu_pow:1;
        RBus_UInt32  pllscpu_rstb:1;
        RBus_UInt32  reg_pllscpu_oeb:1;
        RBus_UInt32  reg_pllscpu_cp:1;
        RBus_UInt32  reg_pllscpu_cs:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllscpu_rs:3;
        RBus_UInt32  res1:21;
    };
}pll_scpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllacpu_tst:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllacpu_wdset:1;
        RBus_UInt32  reg_pllacpu_wdrst:1;
        RBus_UInt32  reg_pllacpu_o:2;
        RBus_UInt32  reg_pllacpu_ip:3;
        RBus_UInt32  reg_pllacpu_m:7;
        RBus_UInt32  reg_pllacpu_n:2;
        RBus_UInt32  res1:11;
    };
}pll_acpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllacpu_pow:1;
        RBus_UInt32  pllacpu_rstb:1;
        RBus_UInt32  reg_pllacpu_oeb:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllacpu_cs:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllacpu_rs:3;
        RBus_UInt32  res1:21;
    };
}pll_acpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllvcpu_tst:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  reg_pllvcpu_wdset:1;
        RBus_UInt32  reg_pllvcpu_wdrst:1;
        RBus_UInt32  reg_pllvcpu_o:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllvcpu_m:7;
        RBus_UInt32  reg_pllvcpu_n:2;
        RBus_UInt32  reg_pllvcpu_ip:3;
        RBus_UInt32  res1:9;
    };
}pll_vcpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllvcpu_pow:1;
        RBus_UInt32  pllvcpu_rstb:1;
        RBus_UInt32  reg_pllvcpu_oeb:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllvcpu_cs:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllvcpu_rs:3;
        RBus_UInt32  res1:21;
    };
}pll_vcpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllbus_c3:2;
        RBus_UInt32  reg_pllbus_r3:3;
        RBus_UInt32  reg_pllbus_cp:2;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_pllbus_cs:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_pllbus_rs:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllbus_ip:3;
        RBus_UInt32  reg_pllbus_m:7;
        RBus_UInt32  reg_pllbus_n:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pllbus_o:2;
        RBus_UInt32  res1:2;
    };
}pll_bus1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllbus_pstst:1;
        RBus_UInt32  reg_pllbus_tst:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  reg_pllbus_vcorb:1;
        RBus_UInt32  reg_pllbus_psen:1;
        RBus_UInt32  reg_pllbus_fupdn:1;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllbus_wdmode:2;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  reg_pllbus_pi_bias:2;
        RBus_UInt32  reg_pllbus_pi_rs:2;
        RBus_UInt32  reg_pllbus_pi_rl:2;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  res1:13;
    };
}pll_bus2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllbus_pow:1;
        RBus_UInt32  reg_pllbus_rstb:1;
        RBus_UInt32  reg_pllbus_oeb:1;
        RBus_UInt32  res1:29;
    };
}pll_bus3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllbus_c3_h:2;
        RBus_UInt32  reg_pllbus_r3_h:3;
        RBus_UInt32  reg_pllbus_cp_h:2;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_pllbus_cs_h:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_pllbus_rs_h:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllbus_ip_h:3;
        RBus_UInt32  reg_pllbus_m_h:7;
        RBus_UInt32  reg_pllbus_n_h:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pllbus_o_h:2;
        RBus_UInt32  res1:2;
    };
}pll_dcsb1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllbus_pstst_h:1;
        RBus_UInt32  reg_pllbus_tst_h:1;
        RBus_UInt32  write_en1:1;
        RBus_UInt32  reg_pllbus_vcorb_h:1;
        RBus_UInt32  reg_pllbus_psen_h:1;
        RBus_UInt32  reg_pllbus_fupdn_h:1;
        RBus_UInt32  write_en3:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllbus_wdmode_h:2;
        RBus_UInt32  write_en4:1;
        RBus_UInt32  reg_pllbus_pi_bias_h:2;
        RBus_UInt32  reg_pllbus_pi_rs_h:2;
        RBus_UInt32  reg_pllbus_pi_rl_h:2;
        RBus_UInt32  write_en5:1;
        RBus_UInt32  res1:13;
    };
}pll_dcsb2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllbus_pow_h:1;
        RBus_UInt32  reg_pllbus_rstb_h:1;
        RBus_UInt32  reg_pllbus_oeb_h:1;
        RBus_UInt32  res1:29;
    };
}pll_dcsb3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllvodma_rs:3;
        RBus_UInt32  reg_pllvodma_cs:2;
        RBus_UInt32  reg_pllvodma_wdrst:1;
        RBus_UInt32  reg_pllvodma_wdset:1;
        RBus_UInt32  reg_pllvodma_o:2;
        RBus_UInt32  reg_pllvodma_ip:3;
        RBus_UInt32  reg_pllvodma_m:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pllvodma_n:2;
        RBus_UInt32  res1:10;
    };
}pll_vodma1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllvodma_pow:1;
        RBus_UInt32  reg_pllvodma_rstb:1;
        RBus_UInt32  reg_pllvodma_oeb:1;
        RBus_UInt32  reg_pllvodma_tst:1;
        RBus_UInt32  res1:28;
    };
}pll_vodma2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_plltst_sel:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  reg_plltst_div:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_pllbus_reg:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllbus_reser:4;
        RBus_UInt32  reg_pllcpu_reg:2;
        RBus_UInt32  res1:10;
    };
}pllbus_tst_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_plldds_wdmode:2;
        RBus_UInt32  reg_plldds_pi_bias:2;
        RBus_UInt32  reg_plldds_pi_rs:2;
        RBus_UInt32  reg_plldds_pi_rl:2;
        RBus_UInt32  reg_plldds_c3:2;
        RBus_UInt32  reg_plldds_r3:3;
        RBus_UInt32  reg_plldds_cp:2;
        RBus_UInt32  reg_plldds_cs:2;
        RBus_UInt32  reg_plldds_rs:3;
        RBus_UInt32  reg_plldds_ip:3;
        RBus_UInt32  reg_plldds_m:7;
        RBus_UInt32  reg_plldds_n:2;
    };
}pll_disp_sd1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res10:10;
        RBus_UInt32  res9:1;
        RBus_UInt32  reg_plldds_pstst:1;
        RBus_UInt32  reg_plldds_tst:1;
        RBus_UInt32  res8:1;
        RBus_UInt32  reg_plldds_vcorb:1;
        RBus_UInt32  res7:1;
        RBus_UInt32  reg_plldds_ddsen:1;
        RBus_UInt32  res6:1;
        RBus_UInt32  reg_plldds_fupdn:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  pcr_a_ctl_en:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  pcr_a_phase_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  pcr_a_smooth_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  psaud_2a_phase_sel:1;
        RBus_UInt32  psaud_1a_phase_sel:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_plldds_o:2;
    };
}pll_disp_sd2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_psaud2_rstb:1;
        RBus_UInt32  reg_psaud2_oeb:1;
        RBus_UInt32  reg_psaud1_rstb:1;
        RBus_UInt32  reg_psaud1_oeb:1;
        RBus_UInt32  res5:16;
        RBus_UInt32  reg_psaud2_psen:1;
        RBus_UInt32  reg_psaud2_tst:1;
        RBus_UInt32  reg_psaud2_div:1;
        RBus_UInt32  reg_psaud2_fupdn:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_psaud1_psen:1;
        RBus_UInt32  reg_psaud1_tst:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_psaud1_div:1;
        RBus_UInt32  reg_psaud1_fupdn:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  res1:1;
    };
}pll_disp_sd3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_plldds_pow:1;
        RBus_UInt32  reg_plldds_rstb:1;
        RBus_UInt32  reg_plldds_oeb:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_plldds_o:2;
        RBus_UInt32  res1:26;
    };
}pll_disp_sd4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plldds_pcr_overflow:16;
        RBus_UInt32  plldds_pcr_acc:16;
    };
}pll_disp_sd5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcr_a_n_nxt:16;
        RBus_UInt32  n_pcr_a_n_nxt:16;
    };
}pll_disp_sd6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcr_a_n_nxt_add_period:16;
        RBus_UInt32  pcr_a_n_nxt_add:8;
        RBus_UInt32  res1:8;
    };
}pll_disp_sd7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dpll_cs:2;
        RBus_UInt32  dpll_cp:2;
        RBus_UInt32  dpll_rs:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  dpll_ip:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  dpll_n:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  dpll_m:8;
        RBus_UInt32  res1:4;
    };
}pll_disp1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dpll_pow:1;
        RBus_UInt32  dpll_vcorstb:1;
        RBus_UInt32  dpll_freeze:1;
        RBus_UInt32  dpll_clksel:1;
        RBus_UInt32  dpll_wdset:1;
        RBus_UInt32  dpll_wdrst:1;
        RBus_UInt32  dpll_rstb:1;
        RBus_UInt32  res6:5;
        RBus_UInt32  dpll_o:2;
        RBus_UInt32  dpll_bpn:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  dpll_bpphs:1;
        RBus_UInt32  dpll_reserve:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  dpll_stop:1;
        RBus_UInt32  dpll_fupdn:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  dpll_reser:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  dpll_ldosel:2;
        RBus_UInt32  res1:2;
    };
}pll_disp2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plt_cmu_macpll_divn:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  plt_cmu_macpll_divm:3;
        RBus_UInt32  res1:25;
    };
}pll_vby1_mac1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_tx_pll_rs:3;
        RBus_UInt32  reg_tx_pll_icp:3;
        RBus_UInt32  reg_tx_pll_edge:1;
        RBus_UInt32  reg_tx_set_vc:2;
        RBus_UInt32  reg_tx_force_vc:1;
        RBus_UInt32  reg_tx_en_emph:1;
        RBus_UInt32  reg_tx_emph:3;
        RBus_UInt32  reg_tx_ibias:2;
        RBus_UInt32  reg_tx_amp:4;
        RBus_UInt32  reg_tx_ck5xn_duty:2;
        RBus_UInt32  reg_tx_ck5xp_duty:2;
        RBus_UInt32  reg_tv_cs:2;
        RBus_UInt32  reg_tv_cp:2;
        RBus_UInt32  reg_tvkvco:1;
        RBus_UInt32  reg_tv_wdmode:2;
        RBus_UInt32  res1:1;
    };
}tmds_scr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bypass_din:1;
        RBus_UInt32  reg_pll_vco_scale:2;
        RBus_UInt32  reg_tx_rt_sel:2;
        RBus_UInt32  reg_tx_rt_en:1;
        RBus_UInt32  reg_tx_bypass_pll:1;
        RBus_UInt32  reg_tst_sel:2;
        RBus_UInt32  reg_pll_tst_en:1;
        RBus_UInt32  reg_tx_vgate:3;
        RBus_UInt32  reg_tx_tst_en:1;
        RBus_UInt32  reg_tx_slew:2;
        RBus_UInt32  reg_tx_driver:2;
        RBus_UInt32  reg_tx_pu:4;
        RBus_UInt32  reg_tx_pll_pu:1;
        RBus_UInt32  reg_tx_pll_kvco:1;
        RBus_UInt32  reg_tx_pll_cs:2;
        RBus_UInt32  reg_tx_pll_cp:2;
        RBus_UInt32  reg_tx_pdrv_isel:2;
        RBus_UInt32  res1:2;
    };
}tmds_scr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_ldo_tmds_capsel:1;
        RBus_UInt32  reg_ldo_tmds_vsel:3;
        RBus_UInt32  reg_ldo_tmds_pu:1;
        RBus_UInt32  reg_cable_det_en:1;
        RBus_UInt32  reg_hpd_en:1;
        RBus_UInt32  reg_cec_rpu_en:1;
        RBus_UInt32  reg_cec_rsel:3;
        RBus_UInt32  reg_cec_enb:1;
        RBus_UInt32  reg_diff_rt_en:1;
        RBus_UInt32  reg_mhl_vcm:2;
        RBus_UInt32  reg_mhl_div:1;
        RBus_UInt32  reg_rxsense:2;
        RBus_UInt32  reg_force_rxsense:1;
        RBus_UInt32  reg_en_mhl:1;
        RBus_UInt32  reg_ldo_pll_vsel:3;
        RBus_UInt32  reg_ldo_pll_pu:1;
        RBus_UInt32  reg_ldo_cco_vsel:2;
        RBus_UInt32  reg_ldo_cco_pu:1;
        RBus_UInt32  reg_tx_v1p05_sel:2;
        RBus_UInt32  reg_tx_pll_wdmode:2;
        RBus_UInt32  res1:1;
    };
}tmds_scr3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_tmds_div16:3;
        RBus_UInt32  reg_tmds_div5:1;
        RBus_UInt32  reg_pixel_div16:3;
        RBus_UInt32  reg_pixel_div5:1;
        RBus_UInt32  reg_pixel_div3:1;
        RBus_UInt32  reg_hdmi_ck_en:1;
        RBus_UInt32  reg_tv_pstep:3;
        RBus_UInt32  reg_tv_pstep_en:1;
        RBus_UInt32  reg_tv_ldiv:6;
        RBus_UInt32  reg_tv_pre_div:1;
        RBus_UInt32  res1:11;
    };
}tvpll_ctrl1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_tv_tst_en:1;
        RBus_UInt32  reg_tv_set_vc:2;
        RBus_UInt32  reg_tv_force_vc:1;
        RBus_UInt32  reg_tv_bypass_pll:1;
        RBus_UInt32  reg_tv_rs:3;
        RBus_UInt32  reg_tv_icp:3;
        RBus_UInt32  reg_tv_pll_pu:1;
        RBus_UInt32  reg_reserve:16;
        RBus_UInt32  reg_sel_ref_clk27:1;
        RBus_UInt32  res1:3;
    };
}tvpll_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res6:9;
        RBus_UInt32  reg_tvpll_stop:1;
        RBus_UInt32  reg_tvpll_reserve:1;
        RBus_UInt32  reg_tvpll_fupdn:1;
        RBus_UInt32  reg_shuffle_en:1;
        RBus_UInt32  res5:4;
        RBus_UInt32  reg_plldds_ddsen:1;
        RBus_UInt32  reg_plldds_fupdn:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_pcr_ctl_en:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pcr_phase_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_pcr_smooth_en:1;
        RBus_UInt32  res1:7;
    };
}tvpll_ctrl3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_plldds_pcr_overflow:16;
        RBus_UInt32  reg_plldds_pcr_acc:16;
    };
}tvpll_ctrl4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pcr_a_n_nxt_add_period:16;
        RBus_UInt32  reg_pcr_a_n_nxt_add:8;
        RBus_UInt32  res1:8;
    };
}tvpll_ctrl5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pcr_a_n_nxt:16;
        RBus_UInt32  reg_n_pcr_a_n_nxt:16;
    };
}tvpll_ctrl6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllgpu_tst:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllgpu_wdmode:2;
        RBus_UInt32  reg_pllgpu_k:2;
        RBus_UInt32  reg_pllgpu_ip:3;
        RBus_UInt32  reg_pllgpu_m:7;
        RBus_UInt32  reg_pllgpu_n:2;
        RBus_UInt32  res1:11;
    };
}pll_gpu1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllgpu_pow:1;
        RBus_UInt32  reg_pllgpu_rstb:1;
        RBus_UInt32  reg_pllgpu_oeb:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllgpu_cs:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllgpu_rs:3;
        RBus_UInt32  res1:21;
    };
}pll_gpu2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllgpu_tst_2:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  reg_pllgpu_wdmode_2:2;
        RBus_UInt32  reg_pllgpu_k_2:2;
        RBus_UInt32  reg_pllgpu_ip_2:3;
        RBus_UInt32  reg_pllgpu_m_2:7;
        RBus_UInt32  reg_pllgpu_n_2:2;
        RBus_UInt32  res1:11;
    };
}pll_gpu3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_pllgpu_pow_2:1;
        RBus_UInt32  reg_pllgpu_rstb_2:1;
        RBus_UInt32  reg_pllgpu_oeb_2:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_pllgpu_cs_2:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_pllgpu_rs_2:3;
        RBus_UInt32  res1:21;
    };
}pll_gpu4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_trng_pow:1;
        RBus_UInt32  reg_trng_tst:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_trng_d:4;
        RBus_UInt32  reg_trng_div:2;
        RBus_UInt32  reg_trng_fs:2;
        RBus_UInt32  reg_trng_gain:2;
        RBus_UInt32  reg_trng_res:2;
        RBus_UInt32  res1:16;
    };
}trng1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crt_dbg_sel1:6;
        RBus_UInt32  crt_dbg_sel0:6;
        RBus_UInt32  crt_dbg_en:1;
        RBus_UInt32  res1:15;
        RBus_UInt32  crt_dbg0_div_sel:2;
        RBus_UInt32  crt_dbg1_div_sel:2;
    };
}crt_debug_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ejtag_hif_det:1;
        RBus_UInt32  dummy_reg:31;
    };
}dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  cp_bist_en:1;
        RBus_UInt32  cr_nf1_bist_en:1;
        RBus_UInt32  ae_bist_en:1;
        RBus_UInt32  ae_rom_bist_en:1;
        RBus_UInt32  dc2_bist_en:1;
        RBus_UInt32  dc3_bist_en:1;
        RBus_UInt32  vde_bist_en:1;
        RBus_UInt32  hdmi1_bist_en:1;
        RBus_UInt32  hdmi0_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  tp_bist_en:1;
        RBus_UInt32  sce_bist_mode:1;
        RBus_UInt32  res1:17;
        RBus_UInt32  sb2_rom_bist_en:1;
    };
}crt_bist_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  ve1_bist_en:1;
        RBus_UInt32  ve2_bist_en:1;
        RBus_UInt32  ve3_bist_en:1;
        RBus_UInt32  ve4_bist_en:1;
        RBus_UInt32  ve5_bist_en:1;
        RBus_UInt32  ve6_bist_en:1;
        RBus_UInt32  ve7_bist_en:1;
        RBus_UInt32  ve8_bist_en:1;
        RBus_UInt32  ve9_bist_en:1;
        RBus_UInt32  ve10_bist_en:1;
        RBus_UInt32  ve11_bist_en:1;
        RBus_UInt32  ve12_bist_en:1;
        RBus_UInt32  ve13_bist_en:1;
        RBus_UInt32  ve14_bist_en:1;
        RBus_UInt32  ve15_bist_en:1;
        RBus_UInt32  ve16_bist_en:1;
        RBus_UInt32  ve17_bist_en:1;
        RBus_UInt32  res1:14;
    };
}crt_bist_en2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_bist_en:1;
        RBus_UInt32  vcpu_bist_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  kcpu1_bist_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  usb1_bist_en:1;
        RBus_UInt32  usb2_bist_en:1;
        RBus_UInt32  md_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  etn2_bist_en:1;
        RBus_UInt32  res1:18;
    };
}crt_bist_en3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  cp_drf_bist_en:1;
        RBus_UInt32  cr_nf1_drf_bist_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  dc2_drf_bist_en:1;
        RBus_UInt32  dc3_drf_bist_en:1;
        RBus_UInt32  vde_drf_bist_en:1;
        RBus_UInt32  hdmi1_drf_bist_en:1;
        RBus_UInt32  hdmi0_drf_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  tp_drf_bist_en:1;
        RBus_UInt32  sce_drf_bist_mode:1;
        RBus_UInt32  res1:18;
    };
}crt_drf_bist_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  ve1_drf_bist_en:1;
        RBus_UInt32  ve2_drf_bist_en:1;
        RBus_UInt32  ve3_drf_bist_en:1;
        RBus_UInt32  ve4_drf_bist_en:1;
        RBus_UInt32  ve5_drf_bist_en:1;
        RBus_UInt32  ve6_drf_bist_en:1;
        RBus_UInt32  ve7_drf_bist_en:1;
        RBus_UInt32  ve8_drf_bist_en:1;
        RBus_UInt32  ve9_drf_bist_en:1;
        RBus_UInt32  ve10_drf_bist_en:1;
        RBus_UInt32  ve11_drf_bist_en:1;
        RBus_UInt32  ve12_drf_bist_en:1;
        RBus_UInt32  ve13_drf_bist_en:1;
        RBus_UInt32  ve14_drf_bist_en:1;
        RBus_UInt32  ve15_drf_bist_en:1;
        RBus_UInt32  ve16_drf_bist_en:1;
        RBus_UInt32  ve17_drf_bist_en:1;
        RBus_UInt32  res1:14;
    };
}crt_drf_bist_en2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_drf_bist_en:1;
        RBus_UInt32  vcpu_drf_bist_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  kcpu1_drf_bist_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  usb1_drf_bist_en:1;
        RBus_UInt32  usb2_drf_bist_en:1;
        RBus_UInt32  md_drf_bist_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  etn2_drf_bist_en:1;
        RBus_UInt32  ae_drf_bist_en:1;
        RBus_UInt32  res1:17;
    };
}crt_drf_bist_en3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  cp_drf_test_resume:1;
        RBus_UInt32  cr_nf1_drf_test_resume:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  dc2_drf_test_resume:1;
        RBus_UInt32  dc3_drf_test_resume:1;
        RBus_UInt32  vde_drf_test_resume:1;
        RBus_UInt32  hdmi1_drf_test_resume:1;
        RBus_UInt32  hdmi0_drf_test_resume:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  tp_drf_test_resume:1;
        RBus_UInt32  sce_drf_test_resume:1;
        RBus_UInt32  res1:18;
    };
}crt_drf_test_resume1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  ve1_drf_test_resume:1;
        RBus_UInt32  ve2_drf_test_resume:1;
        RBus_UInt32  ve3_drf_test_resume:1;
        RBus_UInt32  ve4_drf_test_resume:1;
        RBus_UInt32  ve5_drf_test_resume:1;
        RBus_UInt32  ve6_drf_test_resume:1;
        RBus_UInt32  ve7_drf_test_resume:1;
        RBus_UInt32  ve8_drf_test_resume:1;
        RBus_UInt32  ve9_drf_test_resume:1;
        RBus_UInt32  ve10_drf_test_resume:1;
        RBus_UInt32  ve11_drf_test_resume:1;
        RBus_UInt32  ve12_drf_test_resume:1;
        RBus_UInt32  ve13_drf_test_resume:1;
        RBus_UInt32  ve14_drf_test_resume:1;
        RBus_UInt32  ve15_drf_test_resume:1;
        RBus_UInt32  ve16_drf_test_resume:1;
        RBus_UInt32  ve17_drf_test_resume:1;
        RBus_UInt32  res1:14;
    };
}crt_drf_test_resume2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_drf_test_resume:1;
        RBus_UInt32  vcpu_drf_test_resume:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  kcpu1_drf_test_resume:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  usb1_drf_test_resume:1;
        RBus_UInt32  usb2_drf_test_resume:1;
        RBus_UInt32  md_drf_test_resume:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  etn2_drf_test_resume:1;
        RBus_UInt32  ae_drf_test_resume:1;
        RBus_UInt32  res1:17;
    };
}crt_drf_test_resume3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  vde_drf_start_pause:1;
        RBus_UInt32  res1:30;
    };
}crt_drf_start_pause1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  vcpu_drf_start_pause:1;
        RBus_UInt32  etn2_drf_start_pause:1;
        RBus_UInt32  res1:29;
    };
}crt_drf_start_pause3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_bisr_en:1;
        RBus_UInt32  vcpu_bisr_en:1;
        RBus_UInt32  kcpu_bisr_en:1;
        RBus_UInt32  res1:28;
    };
}crt_bisr_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_bisr_rstn:1;
        RBus_UInt32  vcpu_bisr_rstn:1;
        RBus_UInt32  kcpu_bisr_rstn:1;
        RBus_UInt32  cp42k_bisr_rstn:1;
        RBus_UInt32  res1:27;
    };
}crt_bisr_rstn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_bisr_pwr_rstn:1;
        RBus_UInt32  vcpu_bisr_pwr_rstn:1;
        RBus_UInt32  kcpu_bisr_pwr_rstn:1;
        RBus_UInt32  cp42k_bisr_pwr_rstn:1;
        RBus_UInt32  res1:27;
    };
}crt_bisr_pwr_rstn1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_bisr_hold_remap:1;
        RBus_UInt32  vcpu_bisr_hold_remap:1;
        RBus_UInt32  kcpu_bisr_hold_remap:1;
        RBus_UInt32  cp42k_bisr_hold_remap:1;
        RBus_UInt32  res1:27;
    };
}crt_bisr_hold_remap1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ich1_bisr_sdnr_remap:1;
        RBus_UInt32  iuzd_bisr_remap:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  spnr_bisr_remap:1;
        RBus_UInt32  res1:28;
    };
}crt_bisr_hold_remap2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_bisr_second_run_en:1;
        RBus_UInt32  vcpu_bisr_second_run_en:1;
        RBus_UInt32  kcpu_bisr_second_run_en:1;
        RBus_UInt32  cp42k_bisr_second_run_en:1;
        RBus_UInt32  res1:27;
    };
}crt_bisr_2nd_run_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_drf_bisr_en:1;
        RBus_UInt32  vcpu_drf_bisr_en:1;
        RBus_UInt32  kcpu_drf_bisr_en:1;
        RBus_UInt32  cp42k_drf_bisr_en:1;
        RBus_UInt32  res1:27;
    };
}crt_drf_bisr_en1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_drf_bisr_test_resume:1;
        RBus_UInt32  vcpu_drf_bisr_test_resume:1;
        RBus_UInt32  kcpu_drf_bisr_test_resume:1;
        RBus_UInt32  cp42k_drf_bisr_test_resume:1;
        RBus_UInt32  res1:27;
    };
}crt_drf_bisr_test_resume1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:1;
        RBus_UInt32  acpu_sleepsys_r:1;
        RBus_UInt32  vcpu_sleepsys_r:1;
        RBus_UInt32  res1:29;
    };
}crt_sleep_ack1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_sleepreq_r:1;
        RBus_UInt32  vcpu_sleepreq_r:1;
        RBus_UInt32  res1:29;
    };
}crt_sleep_req1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  write_data:1;
        RBus_UInt32  acpu_light_sleep:1;
        RBus_UInt32  vcpu_light_sleep:1;
        RBus_UInt32  kcpu_light_sleep:1;
        RBus_UInt32  sb2_rom_light_sleep:1;
        RBus_UInt32  ve_light_sleep:1;
        RBus_UInt32  sb2_light_sleep:1;
        RBus_UInt32  dc_sb_light_sleep:1;
        RBus_UInt32  hdmitx_light_sleep:1;
        RBus_UInt32  cp_light_sleep:1;
        RBus_UInt32  etn_light_sleep:1;
        RBus_UInt32  md_light_sleep:1;
        RBus_UInt32  nf_light_sleep:1;
        RBus_UInt32  res1:19;
    };
}crt_light_sleep1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ich1_bisr_sdnr_rstn:1;
        RBus_UInt32  iuzd_bisr_rstn:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  spnr_bisr_rstn:1;
        RBus_UInt32  res1:28;
    };
}crt_bisr_rstn2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mbist_acpu_st:1;
        RBus_UInt32  mbist_hdmi_st:1;
        RBus_UInt32  mbist_md_st:1;
        RBus_UInt32  mbist_tp_st:1;
        RBus_UInt32  mbist_ve_st:1;
        RBus_UInt32  res1:27;
    };
}bist_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ae_bist_fail:1;
        RBus_UInt32  cp_bist_fail:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  dc2_bist_fail:1;
        RBus_UInt32  dc3_bist_fail:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  me_bist_fail0:1;
        RBus_UInt32  me_bist_fail1:1;
        RBus_UInt32  nf1_bist_fail:1;
        RBus_UInt32  etn_bist2_fail:1;
        RBus_UInt32  kcpu_bist_fail:1;
        RBus_UInt32  sce_bist_fail:1;
        RBus_UInt32  vde_bist_fail0:1;
        RBus_UInt32  res2:9;
        RBus_UInt32  vcpu_bist_fail:1;
        RBus_UInt32  res1:7;
    };
}bist_st2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ve_bist1_fail:1;
        RBus_UInt32  ve_bist2_fail:1;
        RBus_UInt32  ve_bist3_fail:1;
        RBus_UInt32  ve_bist4_fail:1;
        RBus_UInt32  ve_bist5_fail:1;
        RBus_UInt32  ve_bist6_fail:1;
        RBus_UInt32  ve_bist7_fail:1;
        RBus_UInt32  ve_bist8_fail:1;
        RBus_UInt32  ve_bist9_fail:1;
        RBus_UInt32  ve_bist10_fail:1;
        RBus_UInt32  ve_bist11_fail:1;
        RBus_UInt32  ve_bist12_fail:1;
        RBus_UInt32  ve_bist13_fail:1;
        RBus_UInt32  ve_bist14_fail:1;
        RBus_UInt32  ve_bist15_fail:1;
        RBus_UInt32  ve_bist16_fail:1;
        RBus_UInt32  ve_bist17_fail:1;
        RBus_UInt32  res1:15;
    };
}bist_st3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ae_drf_bist_fail:1;
        RBus_UInt32  cp_drf_bist_fail:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  dc2_drf_bist_fail:1;
        RBus_UInt32  dc3_drf_bist_fail:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  me_drf_bist_fail0:1;
        RBus_UInt32  me_drf_bist_fail1:1;
        RBus_UInt32  nf1_drf_bist_fail:1;
        RBus_UInt32  sce_drf_bist_fail:1;
        RBus_UInt32  etn_drf_bist2_fail:1;
        RBus_UInt32  res2:10;
        RBus_UInt32  vde_drf_bist_fail:1;
        RBus_UInt32  vcpu_drf_bist_fail:1;
        RBus_UInt32  res1:7;
    };
}drf_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ve_drf_bist1_fail:1;
        RBus_UInt32  ve_drf_bist2_fail:1;
        RBus_UInt32  ve_drf_bist3_fail:1;
        RBus_UInt32  ve_drf_bist4_fail:1;
        RBus_UInt32  ve_drf_bist5_fail:1;
        RBus_UInt32  ve_drf_bist6_fail:1;
        RBus_UInt32  ve_drf_bist7_fail:1;
        RBus_UInt32  ve_drf_bist8_fail:1;
        RBus_UInt32  ve_drf_bist9_fail:1;
        RBus_UInt32  ve_drf_bist10_fail:1;
        RBus_UInt32  ve_drf_bist11_fail:1;
        RBus_UInt32  ve_drf_bist12_fail:1;
        RBus_UInt32  ve_drf_bist13_fail:1;
        RBus_UInt32  ve_drf_bist14_fail:1;
        RBus_UInt32  ve_drf_bist15_fail:1;
        RBus_UInt32  ve_drf_bist16_fail:1;
        RBus_UInt32  ve_drf_bist17_fail:1;
        RBus_UInt32  res1:15;
    };
}drf_st2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res4:1;
        RBus_UInt32  vcpu_bisr_done:1;
        RBus_UInt32  kcpu_bisr_done:1;
        RBus_UInt32  cp42k_bisr_done:1;
        RBus_UInt32  res3:20;
        RBus_UInt32  ich1_bisr_sdnr_done:1;
        RBus_UInt32  i3ddma_uzd_bisr_done:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  spnr_bisr_done:1;
        RBus_UInt32  res1:4;
    };
}crt_bisr_done1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  acpu_bisr_st:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  kcpu_bisr_st:1;
        RBus_UInt32  cp42k_bisr_fail:1;
        RBus_UInt32  res2:24;
        RBus_UInt32  vcpu_bisr_fail:1;
        RBus_UInt32  res1:3;
    };
}crt_bisr_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  acpu_bisr_repaired:1;
        RBus_UInt32  vcpu_bisr_repaired:1;
        RBus_UInt32  kcpu_bisr_repaired:1;
        RBus_UInt32  cp42k_bisr_repaired:1;
        RBus_UInt32  res1:28;
    };
}crt_bisr_repaired1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vcpu_bisr_out:28;
        RBus_UInt32  res1:4;
    };
}crt_bisr_out1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cp42k_bisr_out:7;
        RBus_UInt32  res1:25;
    };
}crt_bisr_out2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res3:2;
        RBus_UInt32  cp42k_drf_bisr_done:1;
        RBus_UInt32  cp42k_drf_bisr_fail:1;
        RBus_UInt32  res2:24;
        RBus_UInt32  vcpu_drf_bisr_fail:1;
        RBus_UInt32  res1:3;
    };
}crt_drf_bisr_st1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll512fs_wdset:1;
        RBus_UInt32  pll512fs_wdrst:1;
        RBus_UInt32  pll512fs_tst:1;
        RBus_UInt32  pll512fs_rs:3;
        RBus_UInt32  pll512fs_q:3;
        RBus_UInt32  pll512fs_s:3;
        RBus_UInt32  pll512fs_ip:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  pll512fs_cs:2;
        RBus_UInt32  pll512fs_bps:1;
        RBus_UInt32  pll512fs_bpn:1;
        RBus_UInt32  pll512fs_m:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  pll512fs_n:3;
        RBus_UInt32  res1:1;
    };
}sys_pll_512fs1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll512fs_pow:1;
        RBus_UInt32  pll512fs_rstb:1;
        RBus_UInt32  pll512fs_oeb:1;
        RBus_UInt32  res1:29;
    };
}sys_pll_512fs2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res5:11;
        RBus_UInt32  res4:1;
        RBus_UInt32  plldif_lf_cp:2;
        RBus_UInt32  plldif_lf_rs:2;
        RBus_UInt32  plldif_ip:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  plldif_m:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  plldif_n:2;
        RBus_UInt32  res1:2;
    };
}sys_pll_dif1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plldif_divadc_sel:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  plldif_divdig_sel:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  plldif_wdmode:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  res1:19;
    };
}sys_pll_dif2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  plldif_pow:1;
        RBus_UInt32  plldif_rstb:1;
        RBus_UInt32  plldif_vco_rstb:1;
        RBus_UInt32  res1:29;
    };
}sys_pll_dif3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll27x_m:7;
        RBus_UInt32  res6:1;
        RBus_UInt32  pll27x_n:2;
        RBus_UInt32  res5:6;
        RBus_UInt32  pll27x_ip:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  pll27x_lf_rs:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  pll27x_lf_cp:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  pll27x_wdmode:2;
        RBus_UInt32  res1:2;
    };
}sys_pll_27x1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll27x_ps_duty_sel:1;
        RBus_UInt32  pll27x_ps_psel_pulse_w:1;
        RBus_UInt32  res6:2;
        RBus_UInt32  pll27x_ps_54m_delay:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  pll_ldo_sel:2;
        RBus_UInt32  pll_pow_ldo:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  pll_ldo11v_sel:2;
        RBus_UInt32  pll_pow_ldo11v:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  pll_xixo_drive_sel:2;
        RBus_UInt32  pll_xixo_load:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  pll_ldo_xtal_sel:2;
        RBus_UInt32  res1:10;
    };
}sys_pll_27x2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll27x_pow:1;
        RBus_UInt32  pll27x_rstb:1;
        RBus_UInt32  pll27x_vcorstb:1;
        RBus_UInt32  pll27x_ps_div2:1;
        RBus_UInt32  pll27x_ps_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  pll_reserve:8;
        RBus_UInt32  res1:16;
    };
}sys_pll_27x3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll_ck_ifadc_mux:1;
        RBus_UInt32  pll27x_dvb_s2_demod_324m_en:1;
        RBus_UInt32  pll27x_dvb_s2_demod_324m_div:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  pllaud_ckin_mux:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  pll27x_ifadc_cko_en:1;
        RBus_UInt32  pll27x_ifadc_div:1;
        RBus_UInt32  pll27x_ifadc_cko_sel:2;
        RBus_UInt32  pll27x_yppadc_ck54m_en:1;
        RBus_UInt32  pll27x_yppadc_cko_en:1;
        RBus_UInt32  pll27x_yppadc_cko_sel:2;
        RBus_UInt32  pll27x_ck108m_div:2;
        RBus_UInt32  pll27x_ck108m_en:1;
        RBus_UInt32  pll_rssi_cko_en:1;
        RBus_UInt32  pll27x_en_tst:1;
        RBus_UInt32  pll27x_pll_tst:3;
        RBus_UInt32  pll27x_d16_en:1;
        RBus_UInt32  pll_l2h_cml_pow:1;
        RBus_UInt32  pll_ifadc_cko_polar:1;
        RBus_UInt32  pll_yppadc_cko_polar:1;
        RBus_UInt32  pll_yppadc_cko_54m_polar:1;
        RBus_UInt32  pll27x_ifadc_duty:2;
        RBus_UInt32  res1:1;
    };
}sys_pll_27x4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pllaud_tst:1;
        RBus_UInt32  pllaud_wdset:1;
        RBus_UInt32  pllaud_wdrst:1;
        RBus_UInt32  res6:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  pllaud_cp:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  pllaud_rs:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  pllaud_ip:3;
        RBus_UInt32  res1:14;
    };
}sys_pll_aud1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pllaud_pwdn:1;
        RBus_UInt32  pllaud_oeb2:1;
        RBus_UInt32  pllaud_oeb1:1;
        RBus_UInt32  pllaud_rstb:1;
        RBus_UInt32  res1:28;
    };
}sys_pll_aud3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  psaud_ctrl:1;
        RBus_UInt32  psaud_tst:1;
        RBus_UInt32  psaud_en:1;
        RBus_UInt32  psaud_psen:1;
        RBus_UInt32  res1:28;
    };
}sys_pll_psaud1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  psaud_div:4;
        RBus_UInt32  res1:28;
    };
}sys_pll_psaud2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_mck_clk_en:8;
        RBus_UInt32  reg_dpi_clk_oe:10;
        RBus_UInt32  reg_dpi_pdiv:2;
        RBus_UInt32  reg_dpi_oesync_op_sel:10;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_dpi_pll_dbug_en:1;
    };
}sys_pll_ddr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_loop_pi_isel:2;
        RBus_UInt32  reg_dpi_lpf_cp:1;
        RBus_UInt32  reg_dpi_lpf_sr:3;
        RBus_UInt32  reg_dpi_pll_ldo_vsel:2;
        RBus_UInt32  reg_dpi_post_pi_rl:2;
        RBus_UInt32  reg_dpi_post_pi_bias:2;
        RBus_UInt32  reg_dpi_icp:4;
        RBus_UInt32  reg_dpi_cco_kvco:1;
        RBus_UInt32  reg_dpi_cco_band:2;
        RBus_UInt32  reg_dpi_pll_sel_cpmode:1;
        RBus_UInt32  reg_dpi_post_pi_rs:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_dpi_en_post_pi:10;
    };
}sys_pll_ddr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_post_pi_sel0:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_dpi_post_pi_sel1:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_dpi_post_pi_sel2:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_dpi_post_pi_sel3:6;
        RBus_UInt32  res1:2;
    };
}sys_pll_ddr3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_post_pi_sel4:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_dpi_post_pi_sel5:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  reg_dpi_post_pi_sel6:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_dpi_post_pi_sel7:6;
        RBus_UInt32  res1:2;
    };
}sys_pll_ddr4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_time0_ck:3;
        RBus_UInt32  reg_dpi_time_rdy_ckout:2;
        RBus_UInt32  reg_dpi_time2_rst_width:2;
        RBus_UInt32  reg_dpi_wd_enable:1;
        RBus_UInt32  reg_dpi_f390k:2;
        RBus_UInt32  reg_v11_ldo_vsel:2;
        RBus_UInt32  reg_dpi_post_pi_sel8:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_dpi_post_pi_sel9:6;
        RBus_UInt32  reg_post_pi_sel7:5;
        RBus_UInt32  res1:1;
    };
}sys_pll_ddr_ssc1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_en_center_in:1;
        RBus_UInt32  reg_dpi_bypass_pi:1;
        RBus_UInt32  reg_dpi_en_ssc:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_dpi_f_code:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_dpi_n_code:8;
        RBus_UInt32  reg_dpi_sel_mode:1;
        RBus_UInt32  res1:3;
    };
}sys_pll_ddr_ssc2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_step_in:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_dpi_tbase:12;
        RBus_UInt32  reg_dpi_order:1;
        RBus_UInt32  reg_dpi_weighting_sel:3;
    };
}sys_pll_ddr_ssc3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_dpi_pll_dum:8;
        RBus_UInt32  reg_dpi_loop_pi_isel_2:1;
        RBus_UInt32  res1:23;
    };
}sys_pll_ddr5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll_stable:1;
        RBus_UInt32  res1:31;
    };
}sys_pll_ddr5_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dpi_dummy_in_dll:32;
    };
}sys_pll_dummy_in_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dpi_dummy_out_dll:32;
    };
}sys_pll_dummy_out_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_ss_en:1;
        RBus_UInt32  dummy18000300_1:1;
        RBus_UInt32  dclk_ss_load:1;
        RBus_UInt32  dummy18000300_3:1;
        RBus_UInt32  dclk_ss_rag:4;
        RBus_UInt32  dclk_freq_syn_slt:6;
        RBus_UInt32  dclk_ss_test:1;
        RBus_UInt32  dclk_new_en:1;
        RBus_UInt32  dclk_offset_11_0:12;
        RBus_UInt32  dclk_filed_flag_slt:3;
        RBus_UInt32  dclk_field_flag_mode_en:1;
    };
}sys_dclkss_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  in_frame_tracking_general_en:1;
        RBus_UInt32  in_frame_tracking_vd_dec_en:1;
        RBus_UInt32  in_frame_tracking_ypbpr_en:1;
        RBus_UInt32  in_frame_tracking_offset_inverse:1;
        RBus_UInt32  sscg_offset_slow_modify_pixel:12;
        RBus_UInt32  sscg_offset_slow_modify_stable:1;
        RBus_UInt32  sscg_offset_slow_modify_valid:1;
        RBus_UInt32  sscg_mcode_slow_modify_pixel:12;
        RBus_UInt32  sscg_mcode_slow_modify_stable:1;
        RBus_UInt32  sscg_mcode_slow_modify_valid:1;
    };
}dpll_in_fsync_tracking_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  in_frame_tracking_mul:8;
        RBus_UInt32  in_frame_tracking_pos_th:12;
        RBus_UInt32  in_frame_tracking_neg_th:12;
    };
}dpll_in_fsync_tracking_ctrl2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sscg_offset_over_th_value:13;
        RBus_UInt32  dpll_mcode_protection_ready_width:2;
        RBus_UInt32  dpll_mcode_protection:1;
        RBus_UInt32  sscg_offset_over_th_max:13;
        RBus_UInt32  sscg_profile_protection:1;
        RBus_UInt32  sscg_profile_over_underflow_flag:1;
        RBus_UInt32  sscg_offset_over_flag:1;
    };
}dpll_in_fsync_tracking_debug_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  frc2fsync_speedup_offset:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  frc2fsync_speedup_m_code:3;
        RBus_UInt32  res1:13;
    };
}dclk_frc2fsync_speedup_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  final_profile:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  final_m_code:10;
        RBus_UInt32  res1:6;
    };
}dpll_status_ro_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_ss_protection_cnt_max:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  dclk_ss_fmdiv:7;
        RBus_UInt32  res1:14;
        RBus_UInt32  dclk_ss_async_protection:1;
        RBus_UInt32  final_profile_force_64n_en:2;
    };
}dclkss_freq_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_0:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  dclk_profile_remap_1:12;
        RBus_UInt32  dclk_profile_remap_en:1;
        RBus_UInt32  dclk_ss_shuffle_en:1;
        RBus_UInt32  dummy1800031c_31_30:2;
    };
}dclkss_profile0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_2:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_3:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_4:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_5:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_6:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_7:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_8:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_9:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_10:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_11:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_13:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_14:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_15:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_16:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_17:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_18:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_19:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile9_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_20:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_21:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_22:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_23:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_24:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_25:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_26:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_27:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_28:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_29:12;
        RBus_UInt32  res1:4;
    };
}dclkss_profile14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dclk_profile_remap_30:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  dclk_profile_remap_31:13;
        RBus_UInt32  res1:3;
    };
}dclkss_profile15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  double_buf_apply:1;
        RBus_UInt32  double_buf_read_sel:1;
        RBus_UInt32  double_buf_en:1;
        RBus_UInt32  res1:29;
    };
}dpll_double_buffer_ctrl_RBUS;

#endif




// the following part is not parsed from tool
#define SYS_PLL_SCPU1_reg                                             0xb8000100
#define SYS_PLL_SCPU1_pllscpu_n_shift                                 (20)
#define SYS_PLL_SCPU1_pllscpu_m_shift                                 (12)
#define SYS_PLL_SCPU1_pllscpu_o_shift                                 (7)
#define SYS_PLL_SCPU1_pllscpu_n_mask                                  (0x00300000)
#define SYS_PLL_SCPU1_pllscpu_m_mask                                  (0x000FF000)
#define SYS_PLL_SCPU1_pllscpu_o_mask                                  (0x00000180)
#define SYS_PLL_SCPU2_reg                                             0xb8000104
#define SYS_PLL_SCPU2_pllscpu_oeb_mask                                (0x00000004)
#define SYS_PLL_GPU1_reg                                              0xb80001E0
#define SYS_PLL_GPU1_pllgpu_n_shift                                   (19)
#define SYS_PLL_GPU1_pllgpu_m_shift                                   (12)
#define SYS_PLL_GPU1_pllgpu_o_shift                                   (7)
#define SYS_PLL_GPU1_pllgpu_n_mask                                    (0x00180000)
#define SYS_PLL_GPU1_pllgpu_m_mask                                    (0x0007F000)
#define SYS_PLL_GPU1_pllgpu_o_mask                                    (0x00000180)
#define SYS_PLL_GPU2_reg                                              0xb80001E4
#define SYS_PLL_GPU2_pllgpu_oeb_mask                                  (0x00000004)
#define SYS_PLL_2_GPU1_reg                                            0xb80001E8
#define SYS_PLL_2_GPU1_pllgpu_n_2_shift                               (19)
#define SYS_PLL_2_GPU1_pllgpu_m_2_shift                               (12)
#define SYS_PLL_2_GPU1_pllgpu_ip_2_shift                              (9)
#define SYS_PLL_2_GPU1_pllgpu_o_2_shift                               (7)
#define SYS_PLL_2_GPU1_pllgpu_n_2_mask                                (0x00180000)
#define SYS_PLL_2_GPU1_pllgpu_m_2_mask                                (0x0007F000)
#define SYS_PLL_2_GPU1_pllgpu_o_2_mask                                (0x00000180)
#define SYS_PLL_2_GPU2_reg                                            0xb80001EC
#define SYS_PLL_2_GPU2_pllgpu_oeb_2_mask                              (0x00000004)
#define SYS_PLL_BUS1_reg                                              0xb8000130
#define SYS_PLL_BUS1_REG_PLLBUS_O_shift                               (28)
#define SYS_PLL_BUS1_REG_PLLBUS_N_shift                               (25)
#define SYS_PLL_BUS1_REG_PLLBUS_M_shift                               (18)
#define SYS_PLL_BUS1_REG_PLLBUS_O_mask                                (0x30000000)
#define SYS_PLL_BUS1_REG_PLLBUS_N_mask                                (0x06000000)
#define SYS_PLL_BUS1_REG_PLLBUS_M_mask                                (0x01FC0000)
#define SYS_PLL_BUS3_reg                                              0xb8000138
#define SYS_PLL_BUS3_REG_PLLBUS_OEB_mask                              (0x00000004)
#define SYS_PLL_DCSB1_reg                                             0xb8000140
#define SYS_PLL_DCSB1_REG_PLLBUS_O_H_shift                            (28)
#define SYS_PLL_DCSB1_REG_PLLBUS_N_H_shift                            (25)
#define SYS_PLL_DCSB1_REG_PLLBUS_M_H_shift                            (18)
#define SYS_PLL_DCSB1_REG_PLLBUS_O_H_mask                             (0x30000000)
#define SYS_PLL_DCSB1_REG_PLLBUS_N_H_mask                             (0x06000000)
#define SYS_PLL_DCSB1_REG_PLLBUS_M_H_mask                             (0x01FC0000)
#define SYS_PLL_DCSB3_reg                                             0xb8000148
#define SYS_PLL_DCSB3_REG_PLLBUS_OEB_H_mask                           (0x00000004)
#define SYS_PLL_ACPU1_reg                                             0xb8000108
#define SYS_PLL_ACPU1_pllacpu_n_shift                                 (19)
#define SYS_PLL_ACPU1_pllacpu_m_shift                                 (12)
#define SYS_PLL_ACPU1_pllacpu_ip_shift                                (9)
#define SYS_PLL_ACPU1_pllacpu_o_shift                                 (7)
#define SYS_PLL_ACPU1_pllacpu_n_mask                                  (0x00180000)
#define SYS_PLL_ACPU1_pllacpu_m_mask                                  (0x0007F000)
#define SYS_PLL_ACPU1_pllacpu_ip_mask                                 (0x00000E00)
#define SYS_PLL_ACPU1_pllacpu_o_mask                                  (0x00000180)
#define SYS_PLL_ACPU2_reg                                             0xb800010c
#define SYS_PLL_ACPU2_pllacpu_oeb_mask                                (0x00000004)
#define SYS_PLL_VCPU1_reg                                             0xb8000110
#define SYS_PLL_VCPU1_pllvcpu_n_shift                                 (18)
#define SYS_PLL_VCPU1_pllvcpu_m_shift                                 (11)
#define SYS_PLL_VCPU1_pllvcpu_o_shift                                 (7)
#define SYS_PLL_VCPU1_pllvcpu_n_mask                                  (0x000c0000)
#define SYS_PLL_VCPU1_pllvcpu_m_mask                                  (0x0003F800)
#define SYS_PLL_VCPU1_pllvcpu_o_mask                                  (0x00000180)
#define SYS_PLL_VCPU2_reg                                             0xb8000114
#define SYS_PLL_VCPU2_pllvcpu_oeb_mask                                (0x00000004)
#define SYS_PLL_DDR_SSC2_reg														 0xb80002d4
#define SYS_PLL_DDR_SSC2_reg_dpi_n_code_shift								 (20)
#define SYS_PLL_DDR_SSC2_reg_dpi_n_code_mask									 (0x0ff00000)
#endif //_RBUS_CRT_REG_H_


