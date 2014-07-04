/**
* @file rbusDefaultReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2014/2/12
* @version 1.1
* @ingroup model_rbus
*
*/

#ifndef _HDMI_CRT_REG_H_
#define _HDMI_CRT_REG_H_

#include <rtd_types_qc.h>




// DEFAULT Register Address

#define SYS_CRT_SOFT_RESET1_VADDR                  (0xb8000000)
#define SYS_CRT_SOFT_RESET2_VADDR                  (0xb8000004)
#define SYS_CRT_SOFT_RESET3_VADDR                  (0xb8000008)
#define SYS_CRT_CLOCK_ENABLE1_VADDR                (0xb800000c)
#define SYS_CRT_CLOCK_ENABLE2_VADDR                (0xb8000010)
#define SYS_CRT_GROUP1_CK_EN_VADDR                 (0xb8000014)
#define SYS_CRT_GROUP1_CK_SEL_VADDR                (0xb8000018)
#define SYS_CRT_TVE_CK_SEL_VADDR                   (0xb800001c)
#define SYS_CRT_DISP_PLL_DIV_VADDR                 (0xb8000020)
#define SYS_CRT_DISP_PLL_DIV2_VADDR                (0xb8000024)
#define SYS_CRT_DISP_PLL_DIV3_VADDR                (0xb8000028)
#define SYS_CRT_AUDIO_CLK_CTL_VADDR                (0xb800002c)
#define SYS_CRT_PLL_DIV_VADDR                      (0xb8000030)
#define SYS_CRT_NF_CKSEL_VADDR                     (0xb8000038)
#define SYS_CRT_NDS_SC_CKSEL_VADDR                 (0xb800003c)
#define SYS_CRT_CR_CKSEL_VADDR                     (0xb8000040)
#define SYS_CRT_CLKDIV_VADDR                       (0xb8000044)
#define SYS_CRT_ARM_WD_VADDR                       (0xb8000048)
#define SYS_CRT_POWER_CTRL0_VADDR                  (0xb800004c)
#define SYS_CRT_PLL_WDOUT_VADDR                    (0xb8000050)
#define SYS_CRT_TM_CTRL0_VADDR                     (0xb8000054)
#define SYS_CRT_TM_CTRL1_VADDR                     (0xb8000058)
#define SYS_CRT_TM_CTRL2_VADDR                     (0xb800005c)
#define SYS_CRT_DSS00_DSS_GPU0_VADDR               (0xb8000060)
#define SYS_CRT_DSS01_DSS_GPU0_VADDR               (0xb8000064)
#define SYS_CRT_DSS02_DSS_GPU0_VADDR               (0xb8000068)
#define SYS_CRT_DSS03_DSS_GPU1_VADDR               (0xb800006c)
#define SYS_CRT_DSS04_DSS_GPU1_VADDR               (0xb8000070)
#define SYS_CRT_DSS05_DSS_GPU1_VADDR               (0xb8000074)
#define SYS_CRT_DSS06_DSS_GPU2_VADDR               (0xb8000078)
#define SYS_CRT_DSS07_DSS_GPU2_VADDR               (0xb800007c)
#define SYS_CRT_DSS08_DSS_GPU2_VADDR               (0xb8000080)
#define SYS_CRT_DSS09_DSS_GPU3_VADDR               (0xb8000084)
#define SYS_CRT_DSS10_DSS_GPU3_VADDR               (0xb8000088)
#define SYS_CRT_DSS11_DSS_GPU3_VADDR               (0xb800008c)
#define SYS_CRT_DSS12_DSS_TOP0_VADDR               (0xb8000090)
#define SYS_CRT_DSS13_DSS_TOP0_VADDR               (0xb8000094)
#define SYS_CRT_DSS14_DSS_TOP0_VADDR               (0xb8000098)
#define SYS_CRT_DSS15_DSS_TVSB10_VADDR             (0xb800009c)
#define SYS_CRT_DSS16_DSS_TVSB10_VADDR             (0xb80000a0)
#define SYS_CRT_DSS17_DSS_TVSB10_VADDR             (0xb80000a4)
#define SYS_CRT_DSS18_DSS_TVSB11_VADDR             (0xb80000a8)
#define SYS_CRT_DSS19_DSS_TVSB11_VADDR             (0xb80000ac)
#define SYS_CRT_DSS20_DSS_TVSB11_VADDR             (0xb80000b0)
#define SYS_CRT_DSS21_DSS_TVSB30_VADDR             (0xb80000b4)
#define SYS_CRT_DSS22_DSS_TVSB30_VADDR             (0xb80000b8)
#define SYS_CRT_DSS23_DSS_TVSB30_VADDR             (0xb80000bc)
#define SYS_CRT_CSM00_CSM_DDR_VADDR                (0xb80007e8)
#define SYS_CRT_CSM01_CSM_DDR_VADDR                (0xb80007ec)
#define SYS_CRT_CSM02_CSM_DDR_VADDR                (0xb80007f0)
#define SYS_CRT_CSM03_CSM_DDR_VADDR                (0xb80007f4)
#define SYS_CRT_CSM04_CSM_DDR_VADDR                (0xb80007f8)
#define SYS_CRT_CSM05_CSM_DDR_VADDR                (0xb80007fc)
#define SYS_CRT_CHIP_SRAM_CTRL_VADDR               (0xb80000c0)
#define SYS_CRT_CHIP_MISC_CTRL_VADDR               (0xb80000c4)
#define SYS_CRT_CHIP_INFO2_VADDR                   (0xb80000c8)
#define SYS_CRT_APS_CTL_VADDR                      (0xb80000cc)
#define SYS_CRT_PWDN_CTRL_VADDR                    (0xb80000d0)
#define SYS_CRT_PWDN_CTRL2_VADDR                   (0xb80000d4)
#define SYS_CRT_PWDN_CTRL3_VADDR                   (0xb80000d8)
#define SYS_CRT_PWDN_CTRL4_VADDR                   (0xb80000dc)
#define SYS_CRT_AT_SPEED_VADDR                     (0xb80000e0)
#define SYS_CRT_ANA_CTRL_VADDR                     (0xb80000e4)
#define SYS_CRT_TP_DEMOD_CTRL_VADDR                (0xb80000e8)
#define SYS_CRT_CONTROL0_VADDR                     (0xb80000ec)
#define SYS_CRT_SECURITY_ST_VADDR                  (0xb80000f0)
#define SYS_CRT_DMY2_VADDR                         (0xb80000f4)
#define SYS_CRT_BUS_PLL_SSC_VADDR                  (0xb80000f8)
#define SYS_CRT_BUSH_PLL_SSC_VADDR                 (0xb80000fc)
#define SYS_CRT_PLL_SCPU1_VADDR                    (0xb8000100)
#define SYS_CRT_PLL_SCPU2_VADDR                    (0xb8000104)
#define SYS_CRT_PLL_ACPU1_VADDR                    (0xb8000108)
#define SYS_CRT_PLL_ACPU2_VADDR                    (0xb800010c)
#define SYS_CRT_PLL_VCPU1_VADDR                    (0xb8000110)
#define SYS_CRT_PLL_VCPU2_VADDR                    (0xb8000114)
#define SYS_CRT_PLL_BUS1_VADDR                     (0xb8000130)
#define SYS_CRT_PLL_BUS2_VADDR                     (0xb8000134)
#define SYS_CRT_PLL_BUS3_VADDR                     (0xb8000138)
#define SYS_CRT_PLL_BUSH1_VADDR                    (0xb8000140)
#define SYS_CRT_PLL_BUSH2_VADDR                    (0xb8000144)
#define SYS_CRT_PLL_BUSH3_VADDR                    (0xb8000148)
#define SYS_CRT_PLL_VODMA1_VADDR                   (0xb8000160)
#define SYS_CRT_PLL_VODMA2_VADDR                   (0xb8000164)
#define SYS_CRT_PLLBUS_TST_VADDR                   (0xb8000168)
#define SYS_CRT_PLL_DISP_SD1_VADDR                 (0xb8000170)
#define SYS_CRT_PLL_DISP_SD2_VADDR                 (0xb8000174)
#define SYS_CRT_PLL_DISP_SD3_VADDR                 (0xb8000178)
#define SYS_CRT_PLL_DISP_SD4_VADDR                 (0xb800017c)
#define SYS_CRT_PLL_DISP_SD5_VADDR                 (0xb8000180)
#define SYS_CRT_PLL_DISP_SD6_VADDR                 (0xb8000184)
#define SYS_CRT_PLL_DISP_SD7_VADDR                 (0xb8000188)
#define SYS_CRT_PLL_DISP1_VADDR                    (0xb8000190)
#define SYS_CRT_PLL_DISP2_VADDR                    (0xb8000194)
#define SYS_CRT_PLL_VBY1_MAC1_VADDR                (0xb8000198)
    #define SYS_CRT_TMDS_SCR1_VADDR                    (0xb80001c0)
    #define SYS_CRT_TMDS_SCR2_VADDR                    (0xb80001c4)
    #define SYS_CRT_TMDS_SCR3_VADDR                    (0xb80001c8)
    #define SYS_CRT_TVPLL_CTRL1_VADDR                  (0xb80001cc)
    #define SYS_CRT_TVPLL_CTRL2_VADDR                  (0xb80001d0)
    #define SYS_CRT_TVPLL_CTRL3_VADDR                  (0xb80001d4)
#define SYS_CRT_TVPLL_CTRL4_VADDR                  (0xb80001d8)
#define SYS_CRT_TVPLL_CTRL5_VADDR                  (0xb80001dc)
#define SYS_CRT_TVPLL_CTRL5_VADDR                  (0xb80001f0)
#define SYS_CRT_PLL_GPU1_VADDR                     (0xb80001e0)
#define SYS_CRT_PLL_GPU2_VADDR                     (0xb80001e4)
#define SYS_CRT_PLL_GPU3_VADDR                     (0xb80001e8)
#define SYS_CRT_PLL_GPU4_VADDR                     (0xb80001ec)
#define SYS_CRT_TRNG1_VADDR                        (0xb80001fc)
#define SYS_CRT_CRT_DEBUG_VADDR                    (0xb8000400)
#define SYS_CRT_DUMMY_VADDR                        (0xb8000450)
#define SYS_CRT_CRT_BIST_EN1_VADDR                 (0xb8000500)
#define SYS_CRT_CRT_BIST_EN2_VADDR                 (0xb8000504)
#define SYS_CRT_CRT_BIST_EN3_VADDR                 (0xb8000508)
#define SYS_CRT_CRT_DRF_BIST_EN1_VADDR             (0xb8000520)
#define SYS_CRT_CRT_DRF_BIST_EN2_VADDR             (0xb8000524)
#define SYS_CRT_CRT_DRF_BIST_EN3_VADDR             (0xb8000528)
#define SYS_CRT_CRT_DRF_TEST_RESUME1_VADDR         (0xb8000540)
#define SYS_CRT_CRT_DRF_TEST_RESUME2_VADDR         (0xb8000544)
#define SYS_CRT_CRT_DRF_TEST_RESUME3_VADDR         (0xb8000548)
#define SYS_CRT_CRT_DRF_START_PAUSE1_VADDR         (0xb8000560)
#define SYS_CRT_CRT_DRF_START_PAUSE3_VADDR         (0xb8000568)
#define SYS_CRT_CRT_BISR_EN1_VADDR                 (0xb8000580)
#define SYS_CRT_CRT_BISR_RSTN1_VADDR               (0xb8000588)
#define SYS_CRT_CRT_BISR_PWR_RSTN1_VADDR           (0xb8000590)
#define SYS_CRT_CRT_BISR_HOLD_REMAP1_VADDR         (0xb8000598)
#define SYS_CRT_CRT_BISR_HOLD_REMAP2_VADDR         (0xb800059c)
#define SYS_CRT_CRT_BISR_2ND_RUN_EN1_VADDR         (0xb80005a0)
#define SYS_CRT_CRT_DRF_BISR_EN1_VADDR             (0xb80005a8)
#define SYS_CRT_CRT_DRF_BISR_TEST_RESUME1_VADDR    (0xb80005b0)
#define SYS_CRT_CRT_SLEEP_ACK1_VADDR               (0xb80005b4)
#define SYS_CRT_CRT_SLEEP_REQ1_VADDR               (0xb80005b8)
#define SYS_CRT_CRT_LIGHT_SLEEP1_VADDR             (0xb80005c0)
#define SYS_CRT_CRT_BISR_RSTN2_VADDR               (0xb80005d0)
#define SYS_CRT_BIST_ST1_VADDR                     (0xb8000600)
#define SYS_CRT_BIST_ST2_VADDR                     (0xb8000610)
#define SYS_CRT_BIST_ST3_VADDR                     (0xb8000614)
#define SYS_CRT_DRF_ST1_VADDR                      (0xb8000620)
#define SYS_CRT_DRF_ST2_VADDR                      (0xb8000624)
#define SYS_CRT_CRT_BISR_DONE1_VADDR               (0xb8000700)
#define SYS_CRT_CRT_BISR_ST1_VADDR                 (0xb8000710)
#define SYS_CRT_CRT_BISR_REPAIRED1_VADDR           (0xb8000720)
#define SYS_CRT_CRT_BISR_OUT1_VADDR                (0xb8000730)
#define SYS_CRT_CRT_BISR_OUT2_VADDR                (0xb8000734)
#define SYS_CRT_CRT_DRF_BISR_ST1_VADDR             (0xb8000750)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======DEFAULT register structure define==========
typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  rstn_demod:1;
        UINT32  rstn_nf:1;
        UINT32  rstn_ae:1;
        UINT32  rstn_tp:1;
        UINT32  rstn_md:1;
        UINT32  rstn_cp:1;
        UINT32  rstn_dc_phy:1;
        UINT32  rstn_dcu:1;
        UINT32  rstn_se:1;
        UINT32  rstn_gpu:1;
        UINT32  rstn_vo:1;
        UINT32  rstn_tve:1;
        UINT32  rstn_ve:1;
        UINT32  rstn_ve_p2:1;
        UINT32  rstn_me1:1;
        UINT32  rstn_aio:1;
        UINT32  rstn_etn_phy:1;
        UINT32  rstn_etn:1;
        UINT32  rstn_hdmi:1;
        UINT32  rstn_ddc:1;
        UINT32  rstn_usb_phy2:1;
        UINT32  rstn_usb_phy1:1;
        UINT32  rstn_usb_phy0:1;
        UINT32  rvd:1;
        UINT32  rstn_usb_mac0:1;
        UINT32  rstn_usb_mac1:1;
        UINT32  rstn_usb_arb:1;
        UINT32  rstn_gspi:1;
        UINT32  rvd:1;
        UINT32  rstn_rng:1;
        UINT32  rstn_misc:1;
    };
}soft_reset1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rstn_ur2:1;
        UINT32  rvd:2;
        UINT32  rstn_ur1:1;
        UINT32  rstn_i2c_0:1;
        UINT32  rstn_i2c_1:1;
        UINT32  rstn_i2c_2:1;
        UINT32  rstn_pcmcia:1;
        UINT32  rstn_sc:1;
        UINT32  rstn_ir:1;
        UINT32  rstn_cec:1;
        UINT32  rvd:1;
        UINT32  rstn_tve_clkgen:1;
        UINT32  rstn_tm:1;
        UINT32  rstn_atvin2:1;
        UINT32  rstn_atvin:1;
        UINT32  rstn_bistreg:1;
        UINT32  rstn_usb_mac:1;
        UINT32  rstn_padmux:1;
        UINT32  rstn_dtv_demod:1;
        UINT32  rstn_emmc:1;
        UINT32  rstn_cr:1;
        UINT32  rstn_pcr_cnt:1;
        UINT32  rstn_scpu_wrap:1;
        UINT32  rstn_pwm:1;
        UINT32  rstn_gpio:1;
        UINT32  rstn_pllreg:1;
        UINT32  rstn_scpu:1;
        UINT32  rstn_vde:1;
        UINT32  rvd:1;
        UINT32  rstn_vcpu:1;
        UINT32  rstn_acpu:1;
    };
}soft_reset2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rstn_akl:1;
        UINT32  rstn_nd:1;
        UINT32  rstn_dsc:1;
        UINT32  rstn_sce:1;
        UINT32  rstn_kt:1;
        UINT32  rstn_scpu_dbg:1;
        UINT32  rstn_scpu_l2:1;
        UINT32  rvd:4;
        UINT32  rstn_tvsb1_tve:1;
        UINT32  rstn_vdec:1;
        UINT32  rstn_kcpu:1;
        UINT32  rstn_hdmirx:1;
        UINT32  rstn_tv_tve:1;
        UINT32  rstn_osdcomp:1;
        UINT32  rstn_tvsb3:1;
        UINT32  rstn_tvsb1:1;
        UINT32  rstn_tvsb2:1;
        UINT32  rstn_if_demod:1;
        UINT32  rstn_vdec2:1;
        UINT32  rstn_vbis0:1;
        UINT32  rstn_audio2_dac:1;
        UINT32  rstn_audio_adc:1;
        UINT32  rstn_audio_dac:1;
        UINT32  rstn_ifadc:1;
        UINT32  rstn_apll_adc:1;
        UINT32  rstn_vodma:1;
        UINT32  rstn_dispim:1;
        UINT32  rstn_disp:1;
        UINT32  rstn_sb2:1;
    };
}soft_reset3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:3;
        UINT32  clken_tvsb1_tve:1;
        UINT32  clk_en_demod:1;
        UINT32  clken_vdec:1;
        UINT32  clk_en_cr:1;
        UINT32  clk_en_emmc:1;
        UINT32  clk_en_nf:1;
        UINT32  clk_en_ae:1;
        UINT32  clk_en_tp:1;
        UINT32  clk_en_md:1;
        UINT32  clk_en_cp:1;
        UINT32  clk_en_dcu:1;
        UINT32  clk_en_se:1;
        UINT32  clken_tv_tve:1;
        UINT32  clken_tve_clkgen:1;
        UINT32  clk_en_tve:1;
        UINT32  clk_en_ve:1;
        UINT32  clk_en_ve_p2:1;
        UINT32  clk_en_tve_sys:1;
        UINT32  clk_en_aio:1;
        UINT32  clk_en_etn:1;
        UINT32  clk_en_hdmi:1;
        UINT32  reg_clken_3d_gde:1;
        UINT32  rvd:1;
        UINT32  clk_en_pcr:1;
        UINT32  clk_en_usb0:1;
        UINT32  clk_en_gspi:1;
        UINT32  clk_en_usb1:1;
        UINT32  clk_en_hdmirx:1;
        UINT32  clk_en_misc:1;
    };
}clock_enable1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  clk_en_ur2:1;
        UINT32  rvd:2;
        UINT32  clk_en_ur1:1;
        UINT32  rvd:2;
        UINT32  clk_en_pwm:1;
        UINT32  clk_en_misc_i2c_2:1;
        UINT32  rvd:6;
        UINT32  rvd:1;
        UINT32  rvd:1;
        UINT32  clk_en_misc_i2c_1:1;
        UINT32  clk_en_misc_pcmcia:1;
        UINT32  clk_en_misc_sc:1;
        UINT32  clk_en_misc_ir:1;
        UINT32  rvd:1;
        UINT32  rvd:1;
        UINT32  rvd:1;
        UINT32  clk_en_me1:1;
        UINT32  clk_en_vde:1;
        UINT32  clk_en_ade:1;
        UINT32  clk_en_vcpu:1;
        UINT32  clk_en_acpu:1;
        UINT32  clk_en_scpu_wrap:1;
        UINT32  clk_en_scpu:1;
        UINT32  reg_clken_scpu_cssys:1;
        UINT32  rvd:1;
    };
}clock_enable2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  clken_tvsb1:1;
        UINT32  clken_tvsb2:1;
        UINT32  clken_tvsb3:1;
        UINT32  clken_tm:1;
        UINT32  clken_atvin_vd:1;
        UINT32  clken_atvin_ifd:1;
        UINT32  clken_osdcomp:1;
        UINT32  clken_apll_adc:1;
        UINT32  clken_if_demod:1;
        UINT32  clken_disp2tve:1;
        UINT32  clken_bistreg:1;
        UINT32  clken_vbis0:1;
        UINT32  clken_audio_daad_128fs:1;
        UINT32  clken_audio_daad_256fs:1;
        UINT32  clken_audio_pre512fs:1;
        UINT32  clken_ifadc:1;
        UINT32  clken_audio2_512fs:1;
        UINT32  clken_audio2_daad_256fs:1;
        UINT32  clken_audio2_daad_128fs:1;
        UINT32  clken_padmux:1;
        UINT32  clken_dtv_demod:1;
        UINT32  clk_en_akl:1;
        UINT32  clk_en_dsc:1;
        UINT32  clk_en_sce:1;
        UINT32  clk_en_kt:1;
        UINT32  clken_ddc:1;
        UINT32  clken_vodma:1;
        UINT32  clken_dispim:1;
        UINT32  clken_disp:1;
        UINT32  clken_pllreg:1;
        UINT32  clk_en_kcpu:1;
        UINT32  clk_en_sb2:1;
    };
}group1_ck_en_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:5;
        UINT32  ve_rif_use_p2clk:1;
        UINT32  epi_dbg_clksel:1;
        UINT32  epi_div_clksel:2;
        UINT32  rvd:5;
        UINT32  atvin_clk_sel:1;
        UINT32  atvin_vd_clk_sel:1;
        UINT32  atvin_vdadc_tve_clk_sel:1;
        UINT32  rvd:6;
        UINT32  vdec_x27_clksel:1;
        UINT32  rvd:2;
        UINT32  vbis0_yppsel:1;
        UINT32  inv_vbis0_clk:1;
        UINT32  rvd:3;
        UINT32  sclk_sel:1;
    };
}group1_ck_sel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:19;
        UINT32  write_en5:1;
        UINT32  clk_tve_p_vo_clk_sel2:1;
        UINT32  write_en4:1;
        UINT32  clk_tve_p_vo_clk_sel:1;
        UINT32  write_en3:1;
        UINT32  hdmi_phy_ckinv:1;
        UINT32  write_en2:1;
        UINT32  rvd:2;
        UINT32  dac2_ckinv:1;
        UINT32  dac1_ckinv:1;
        UINT32  write_en1:1;
        UINT32  tveck_mix_sel:1;
    };
}tve_ck_sel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:20;
        UINT32  write_en2:1;
        UINT32  dac2_div:5;
        UINT32  write_en1:1;
        UINT32  dac1_div:5;
    };
}disp_pll_div_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:7;
        UINT32  write_en11:1;
        UINT32  hdmi_deep_clk_sel:1;
        UINT32  write_en10:1;
        UINT32  tve_i_div:2;
        UINT32  write_en9:1;
        UINT32  hdmi_tmds_div:2;
        UINT32  write_en8:1;
        UINT32  sel_plldisp_clk2:1;
        UINT32  write_en7:1;
        UINT32  sel_pllhdmi_clk:1;
        UINT32  write_en6:1;
        UINT32  hdmi_pxl_repeat:1;
        UINT32  write_en5:1;
        UINT32  hdmi_phy_clk_sel:1;
        UINT32  write_en4:1;
        UINT32  hdmi_div:3;
        UINT32  write_en3:1;
        UINT32  tve_div:4;
    };
}disp_pll_div2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:18;
        UINT32  reg_hdmi_tmds_div:2;
        UINT32  reg_tve_hdmi_div_sel:2;
        UINT32  reg_dac1_clk_sel:2;
        UINT32  reg_tve_pclk_sel:2;
        UINT32  reg_dac2_clk_sel:2;
        UINT32  reg_tve_iclk_sel:2;
        UINT32  reg_dac1_phy_clk_inv:1;
        UINT32  reg_dac2_phy_clk_inv:1;
    };
}disp_pll_div3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:31;
        UINT32  audio_use_sysclk:1;
    };
}audio_clk_ctl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:23;
        UINT32  scpu_freq_sel:2;
        UINT32  vcpu_freq_sel:2;
        UINT32  acpu_freq_sel:2;
        UINT32  ddr_freq_sel:2;
        UINT32  bus_freq_sel:1;
    };
}pll_div_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:29;
        UINT32  nf_div:3;
    };
}nf_cksel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:29;
        UINT32  nds_sc_div:3;
    };
}nds_sc_cksel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_en3:1;
        UINT32  cremmc_clk_sel:1;
        UINT32  rvd:22;
        UINT32  write_en2:1;
        UINT32  emmc_div:3;
        UINT32  write_en1:1;
        UINT32  cr_div:3;
    };
}cr_cksel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  dtv_demod_multi_req_disable:1;
        UINT32  rvd:1;
        UINT32  aud_dtv_freq_sel:3;
    };
}clkdiv_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:15;
        UINT32  scpu_wd_en:1;
        UINT32  rvd:4;
        UINT32  scpu_wd_cnt:12;
    };
}arm_wd_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:19;
        UINT32  atv_iso_en:1;
        UINT32  rvd:1;
        UINT32  atv_str_status:1;
        UINT32  rvd:1;
        UINT32  atv_str_pow:1;
        UINT32  rvd:3;
        UINT32  dtv_iso_en:1;
        UINT32  rvd:1;
        UINT32  dtv_str_status:1;
        UINT32  rvd:1;
        UINT32  dtv_str_pow:1;
    };
}power_ctrl0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:13;
        UINT32  pll27x_wdout:1;
        UINT32  reg_pllvodma_wdout:1;
        UINT32  pllgpu_wdout:1;
        UINT32  pllgpu_wdout_2:1;
        UINT32  pllaud_status:1;
        UINT32  pll512fs_wdout:1;
        UINT32  reg_pllbush_wdout:1;
        UINT32  rvd:1;
        UINT32  plldif_wdout:1;
        UINT32  pllbus2_wdout:1;
        UINT32  plletn_wdout:1;
        UINT32  rvd:1;
        UINT32  reg_pllbus_wdout:1;
        UINT32  plldisp_wdout:1;
        UINT32  rvd:1;
        UINT32  plldds_wdout:1;
        UINT32  reg_pllvcpu_wdout:1;
        UINT32  reg_pllacpu_wdout:1;
        UINT32  reg_pllscpu_wdout:1;
    };
}pll_wdout_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:4;
        UINT32  tm_enable:1;
        UINT32  tm_data_valid:1;
        UINT32  tm_data_sampled:1;
        UINT32  tm_reverse_cmp_out:1;
        UINT32  rvd:1;
        UINT32  tm_data_out:7;
        UINT32  tm_pwron_dly:16;
    };
}tm_ctrl0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tm_compare_dly:16;
        UINT32  tm_sample_dly:16;
    };
}tm_ctrl1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:22;
        UINT32  reg_tm_sbg:3;
        UINT32  reg_tm_sos:3;
        UINT32  reg_tm_sinl:2;
        UINT32  reg_tm_pow:1;
        UINT32  rvd:1;
    };
}tm_ctrl2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35d5_speed_en:1;
        UINT32  dss_c35d5_data_in:20;
        UINT32  dss_c35d5_wire_sel:1;
        UINT32  dss_c35d5_ro_sel:3;
        UINT32  dss_c35d5_dss_rst_n:1;
    };
}dss00_dss_gpu0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35d5_wsort_go:1;
        UINT32  dss_c35d5_count_out:20;
        UINT32  dss_c35d5_ready:1;
    };
}dss01_dss_gpu0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35d5_dbgo:16;
    };
}dss02_dss_gpu0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35_speed_en:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_dss_rst_n:1;
    };
}dss03_dss_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35_wsort_go:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_ready:1;
    };
}dss04_dss_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35_dbgo:16;
    };
}dss05_dss_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35d5_speed_en:1;
        UINT32  dss_c35d5_data_in:20;
        UINT32  dss_c35d5_wire_sel:1;
        UINT32  dss_c35d5_ro_sel:3;
        UINT32  dss_c35d5_dss_rst_n:1;
    };
}dss06_dss_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35d5_wsort_go:1;
        UINT32  dss_c35d5_count_out:20;
        UINT32  dss_c35d5_ready:1;
    };
}dss07_dss_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35d5_dbgo:16;
    };
}dss08_dss_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35_speed_en:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_dss_rst_n:1;
    };
}dss09_dss_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35_wsort_go:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_ready:1;
    };
}dss10_dss_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35_dbgo:16;
    };
}dss11_dss_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35_speed_en:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_dss_rst_n:1;
    };
}dss12_dss_top0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35_wsort_go:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_ready:1;
    };
}dss13_dss_top0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35_dbgo:16;
    };
}dss14_dss_top0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35_speed_en:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_dss_rst_n:1;
    };
}dss15_dss_tvsb10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35_wsort_go:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_ready:1;
    };
}dss16_dss_tvsb10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35_dbgo:16;
    };
}dss17_dss_tvsb10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35d5_speed_en:1;
        UINT32  dss_c35d5_data_in:20;
        UINT32  dss_c35d5_wire_sel:1;
        UINT32  dss_c35d5_ro_sel:3;
        UINT32  dss_c35d5_dss_rst_n:1;
    };
}dss18_dss_tvsb11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35d5_wsort_go:1;
        UINT32  dss_c35d5_count_out:20;
        UINT32  dss_c35d5_ready:1;
    };
}dss19_dss_tvsb11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35d5_dbgo:16;
    };
}dss20_dss_tvsb11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:6;
        UINT32  dss_c35_speed_en:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_dss_rst_n:1;
    };
}dss21_dss_tvsb30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  dss_c35_wsort_go:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_ready:1;
    };
}dss22_dss_tvsb30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  dss_c35_dbgo:16;
    };
}dss23_dss_tvsb30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:19;
        UINT32  csm0_data_sel:2;
        UINT32  csm0_addr:4;
        UINT32  csm0_read_en:1;
        UINT32  csm0_hold:1;
        UINT32  csm0_acc_mode:1;
        UINT32  csm0_in_sel:2;
        UINT32  csm0_csm_en:1;
        UINT32  csm0_rstn:1;
    };
}csm00_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:31;
        UINT32  csm0_ready:1;
    };
}csm01_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm0_data:32;
    };
}csm02_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:19;
        UINT32  csm1_data_sel:2;
        UINT32  csm1_addr:4;
        UINT32  csm1_read_en:1;
        UINT32  csm1_hold:1;
        UINT32  csm1_acc_mode:1;
        UINT32  csm1_in_sel:2;
        UINT32  csm1_csm_en:1;
        UINT32  csm1_rstn:1;
    };
}csm03_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:31;
        UINT32  csm1_ready:1;
    };
}csm04_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm1_data:32;
    };
}csm05_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:2;
        UINT32  rme_rom:1;
        UINT32  rm_rom:4;
        UINT32  rme_800:1;
        UINT32  rm_800:4;
        UINT32  rme_600:1;
        UINT32  rm_600:4;
        UINT32  rme_400:1;
        UINT32  rm_400:4;
        UINT32  rme_300:1;
        UINT32  rm_300:4;
        UINT32  rme_200:1;
        UINT32  rm_200:4;
    };
}chip_sram_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:31;
        UINT32  resume_cycle_sel:1;
    };
}chip_misc_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:23;
        UINT32  clk_na_fail:1;
        UINT32  rvd:5;
        UINT32  testmode:1;
        UINT32  nf_sel:1;
        UINT32  sf_sel:1;
    };
}chip_info2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:30;
        UINT32  write_en2:1;
        UINT32  dds_rstn:1;
    };
}aps_ctl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  kcpu_boot_info:32;
    };
}pwdn_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  acpu_boot_info:32;
    };
}pwdn_ctrl2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  write_en2:1;
        UINT32  kcpu_boot_info_valid:1;
        UINT32  write_en1:1;
        UINT32  kcpu_sw_rst:1;
    };
}pwdn_ctrl3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:31;
        UINT32  acpu_boot_info_valid:1;
    };
}pwdn_ctrl4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  write_en2:1;
        UINT32  dac_test:1;
        UINT32  write_en1:1;
        UINT32  scpu_config_done:1;
    };
}at_speed_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  write_en2:1;
        UINT32  etn_phy_gpio_en:1;
        UINT32  write_en1:1;
        UINT32  etn_phy_125m_en:1;
    };
}ana_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  demod_i2c_saddr:1;
        UINT32  demod_i2c_sel:1;
        UINT32  tp2_dm_sel:1;
        UINT32  tp1_dm_sel:1;
        UINT32  tp0_dm_sel:1;
    };
}tp_demod_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:31;
        UINT32  sf_en:1;
    };
}control0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:31;
        UINT32  akl_busy:1;
    };
}security_st_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:32;
    };
}dmy2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  bus_ssc_sse:1;
        UINT32  bus_ssc_ckinv:1;
        UINT32  bus_ssc_sss:6;
        UINT32  rvd:1;
        UINT32  bus_ssc_ssn:7;
        UINT32  bus_ssc_ssfpv:8;
        UINT32  rvd:6;
        UINT32  bus_ssc_stms:2;
    };
}bus_pll_ssc_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  bush_ssc_sse:1;
        UINT32  bush_ssc_ckinv:1;
        UINT32  bush_ssc_sss:6;
        UINT32  rvd:1;
        UINT32  bush_ssc_ssn:7;
        UINT32  bush_ssc_ssfpv:8;
        UINT32  rvd:6;
        UINT32  bush_ssc_stms:2;
    };
}bush_pll_ssc_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  reg_pllscpu_n:2;
        UINT32  reg_pllscpu_m:8;
        UINT32  reg_pllscpu_ip:3;
        UINT32  reg_pllscpu_o:2;
        UINT32  reg_pllscpu_wdrst:1;
        UINT32  reg_pllscpu_wdset:1;
        UINT32  rvd:4;
        UINT32  reg_pllscpu_tst:1;
    };
}pll_scpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:21;
        UINT32  reg_pllscpu_rs:3;
        UINT32  rvd:2;
        UINT32  reg_pllscpu_cs:2;
        UINT32  reg_pllscpu_cp:1;
        UINT32  reg_pllscpu_oeb:1;
        UINT32  pllscpu_rstb:1;
        UINT32  reg_pllscpu_pow:1;
    };
}pll_scpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:11;
        UINT32  reg_pllacpu_n:2;
        UINT32  reg_pllacpu_m:7;
        UINT32  reg_pllacpu_ip:3;
        UINT32  reg_pllacpu_o:2;
        UINT32  reg_pllacpu_wdrst:1;
        UINT32  reg_pllacpu_wdset:1;
        UINT32  rvd:4;
        UINT32  reg_pllacpu_tst:1;
    };
}pll_acpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:21;
        UINT32  reg_pllacpu_rs:3;
        UINT32  rvd:2;
        UINT32  reg_pllacpu_cs:2;
        UINT32  rvd:1;
        UINT32  reg_pllacpu_oeb:1;
        UINT32  pllacpu_rstb:1;
        UINT32  reg_pllacpu_pow:1;
    };
}pll_acpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:9;
        UINT32  reg_pllvcpu_ip:3;
        UINT32  reg_pllvcpu_n:2;
        UINT32  reg_pllvcpu_m:7;
        UINT32  rvd:2;
        UINT32  reg_pllvcpu_o:2;
        UINT32  reg_pllvcpu_wdrst:1;
        UINT32  reg_pllvcpu_wdset:1;
        UINT32  rvd:4;
        UINT32  reg_pllvcpu_tst:1;
    };
}pll_vcpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:21;
        UINT32  reg_pllvcpu_rs:3;
        UINT32  rvd:2;
        UINT32  reg_pllvcpu_cs:2;
        UINT32  rvd:1;
        UINT32  reg_pllvcpu_oeb:1;
        UINT32  pllvcpu_rstb:1;
        UINT32  reg_pllvcpu_pow:1;
    };
}pll_vcpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:2;
        UINT32  reg_pllbus_o:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_n:2;
        UINT32  reg_pllbus_m:7;
        UINT32  reg_pllbus_ip:3;
        UINT32  rvd:1;
        UINT32  reg_pllbus_rs:3;
        UINT32  rvd:1;
        UINT32  reg_pllbus_cs:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_cp:2;
        UINT32  reg_pllbus_r3:3;
        UINT32  reg_pllbus_c3:2;
    };
}pll_bus1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:13;
        UINT32  write_en5:1;
        UINT32  reg_pllbus_pi_rl:2;
        UINT32  reg_pllbus_pi_rs:2;
        UINT32  reg_pllbus_pi_bias:2;
        UINT32  write_en4:1;
        UINT32  reg_pllbus_wdmode:2;
        UINT32  rvd:2;
        UINT32  write_en3:1;
        UINT32  reg_pllbus_fupdn:1;
        UINT32  reg_pllbus_psen:1;
        UINT32  reg_pllbus_vcorb:1;
        UINT32  write_en1:1;
        UINT32  reg_pllbus_tst:1;
        UINT32  reg_pllbus_pstst:1;
    };
}pll_bus2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:29;
        UINT32  reg_pllbus_oeb:1;
        UINT32  reg_pllbus_rstb:1;
        UINT32  reg_pllbus_pow:1;
    };
}pll_bus3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:2;
        UINT32  reg_pllbus_o_h:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_n_h:2;
        UINT32  reg_pllbus_m_h:7;
        UINT32  reg_pllbus_ip_h:3;
        UINT32  rvd:1;
        UINT32  reg_pllbus_rs_h:3;
        UINT32  rvd:1;
        UINT32  reg_pllbus_cs_h:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_cp_h:2;
        UINT32  reg_pllbus_r3_h:3;
        UINT32  reg_pllbus_c3_h:2;
    };
}pll_bush1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:13;
        UINT32  write_en5:1;
        UINT32  reg_pllbus_pi_rl_h:2;
        UINT32  reg_pllbus_pi_rs_h:2;
        UINT32  reg_pllbus_pi_bias_h:2;
        UINT32  write_en4:1;
        UINT32  reg_pllbus_wdmode_h:2;
        UINT32  rvd:2;
        UINT32  write_en3:1;
        UINT32  reg_pllbus_fupdn_h:1;
        UINT32  reg_pllbus_psen_h:1;
        UINT32  reg_pllbus_vcorb_h:1;
        UINT32  write_en1:1;
        UINT32  reg_pllbus_tst_h:1;
        UINT32  reg_pllbus_pstst_h:1;
    };
}pll_bush2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:29;
        UINT32  reg_pllbus_oeb_h:1;
        UINT32  reg_pllbus_rstb_h:1;
        UINT32  reg_pllbus_pow_h:1;
    };
}pll_bush3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  reg_pllvodma_n:2;
        UINT32  rvd:1;
        UINT32  reg_pllvodma_m:7;
        UINT32  reg_pllvodma_ip:3;
        UINT32  reg_pllvodma_o:2;
        UINT32  reg_pllvodma_wdset:1;
        UINT32  reg_pllvodma_wdrst:1;
        UINT32  reg_pllvodma_cs:2;
        UINT32  reg_pllvodma_rs:3;
    };
}pll_vodma1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  reg_pllvodma_tst:1;
        UINT32  reg_pllvodma_oeb:1;
        UINT32  reg_pllvodma_rstb:1;
        UINT32  reg_pllvodma_pow:1;
    };
}pll_vodma2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  reg_pllcpu_reg:2;
        UINT32  reg_pllbus_reser:4;
        UINT32  rvd:2;
        UINT32  reg_pllbus_reg:2;
        UINT32  rvd:2;
        UINT32  reg_plltst_div:2;
        UINT32  rvd:3;
        UINT32  reg_plltst_sel:5;
    };
}pllbus_tst_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_plldds_n:2;
        UINT32  reg_plldds_m:7;
        UINT32  reg_plldds_ip:3;
        UINT32  reg_plldds_rs:3;
        UINT32  reg_plldds_cs:2;
        UINT32  reg_plldds_cp:2;
        UINT32  reg_plldds_r3:3;
        UINT32  reg_plldds_c3:2;
        UINT32  reg_plldds_pi_rl:2;
        UINT32  reg_plldds_pi_rs:2;
        UINT32  reg_plldds_pi_bias:2;
        UINT32  reg_plldds_wdmode:2;
    };
}pll_disp_sd1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:2;
        UINT32  rvd:2;
        UINT32  psaud_1a_phase_sel:1;
        UINT32  psaud_2a_phase_sel:1;
        UINT32  rvd:1;
        UINT32  pcr_a_smooth_en:1;
        UINT32  rvd:1;
        UINT32  pcr_a_phase_sel:1;
        UINT32  rvd:1;
        UINT32  pcr_a_ctl_en:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_fupdn:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_ddsen:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_vcorb:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_tst:1;
        UINT32  reg_plldds_pstst:1;
        UINT32  rvd:1;
        UINT32  rvd:10;
    };
}pll_disp_sd2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  rvd:1;
        UINT32  reg_psaud1_fupdn:1;
        UINT32  reg_psaud1_div:1;
        UINT32  rvd:1;
        UINT32  reg_psaud1_tst:1;
        UINT32  reg_psaud1_psen:1;
        UINT32  rvd:1;
        UINT32  reg_psaud2_fupdn:1;
        UINT32  reg_psaud2_div:1;
        UINT32  reg_psaud2_tst:1;
        UINT32  reg_psaud2_psen:1;
        UINT32  rvd:16;
        UINT32  reg_psaud1_oeb:1;
        UINT32  reg_psaud1_rstb:1;
        UINT32  reg_psaud2_oeb:1;
        UINT32  reg_psaud2_rstb:1;
    };
}pll_disp_sd3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:26;
        UINT32  reg_plldds_o:2;
        UINT32  rvd:1;
        UINT32  reg_plldds_oeb:1;
        UINT32  reg_plldds_rstb:1;
        UINT32  reg_plldds_pow:1;
    };
}pll_disp_sd4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  plldds_pcr_acc:16;
        UINT32  plldds_pcr_overflow:16;
    };
}pll_disp_sd5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  n_pcr_a_n_nxt:16;
        UINT32  pcr_a_n_nxt:16;
    };
}pll_disp_sd6_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:8;
        UINT32  pcr_a_n_nxt_add:8;
        UINT32  pcr_a_n_nxt_add_period:16;
    };
}pll_disp_sd7_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:4;
        UINT32  dpll_m:8;
        UINT32  rvd:5;
        UINT32  dpll_n:3;
        UINT32  rvd:1;
        UINT32  dpll_ip:3;
        UINT32  rvd:1;
        UINT32  dpll_rs:3;
        UINT32  dpll_cp:2;
        UINT32  dpll_cs:2;
    };
}pll_disp1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:2;
        UINT32  dpll_ldosel:2;
        UINT32  rvd:3;
        UINT32  dpll_reser:1;
        UINT32  rvd:2;
        UINT32  dpll_fupdn:1;
        UINT32  dpll_stop:1;
        UINT32  rvd:2;
        UINT32  dpll_reserve:1;
        UINT32  dpll_bpphs:1;
        UINT32  rvd:1;
        UINT32  dpll_bpn:1;
        UINT32  dpll_o:2;
        UINT32  rvd:5;
        UINT32  dpll_rstb:1;
        UINT32  dpll_wdrst:1;
        UINT32  dpll_wdset:1;
        UINT32  dpll_clksel:1;
        UINT32  dpll_freeze:1;
        UINT32  dpll_vcorstb:1;
        UINT32  dpll_pow:1;
    };
}pll_disp2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  plt_cmu_macpll_divm:3;
        UINT32  rvd:1;
        UINT32  plt_cmu_macpll_divn:3;
    };
}pll_vby1_mac1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  reg_tv_wdmode:2;
        UINT32  reg_tvkvco:1;
        UINT32  reg_tv_cp:2;
        UINT32  reg_tv_cs:2;
        UINT32  reg_tx_ck5xp_duty:2;
        UINT32  reg_tx_ck5xn_duty:2;
        UINT32  reg_tx_amp:4;
        UINT32  reg_tx_ibias:2;
        UINT32  reg_tx_emph:3;
        UINT32  reg_tx_en_emph:1;
        UINT32  reg_tx_force_vc:1;
        UINT32  reg_tx_set_vc:2;
        UINT32  reg_tx_pll_edge:1;
        UINT32  reg_tx_pll_icp:3;
        UINT32  reg_tx_pll_rs:3;
    };
}tmds_scr1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:2;
        UINT32  reg_tx_pdrv_isel:2;
        UINT32  reg_tx_pll_cp:2;
        UINT32  reg_tx_pll_cs:2;
        UINT32  reg_tx_pll_kvco:1;
        UINT32  reg_tx_pll_pu:1;
        UINT32  reg_tx_pu:4;
        UINT32  reg_tx_driver:2;
        UINT32  reg_tx_slew:2;
        UINT32  reg_tx_tst_en:1;
        UINT32  reg_tx_vgate:3;
        UINT32  reg_pll_tst_en:1;
        UINT32  reg_tst_sel:2;
        UINT32  reg_tx_bypass_pll:1;
        UINT32  reg_tx_rt_en:1;
        UINT32  reg_tx_rt_sel:2;
        UINT32  reg_pll_vco_scale:2;
        UINT32  reg_bypass_din:1;
    };
}tmds_scr2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  reg_tx_pll_wdmode:2;
        UINT32  reg_tx_v1p05_sel:2;
        UINT32  reg_ldo_cco_pu:1;
        UINT32  reg_ldo_cco_vsel:2;
        UINT32  reg_ldo_pll_pu:1;
        UINT32  reg_ldo_pll_vsel:3;
        UINT32  reg_en_mhl:1;
        UINT32  reg_force_rxsense:1;
        UINT32  reg_rxsense:2;
        UINT32  reg_mhl_div:1;
        UINT32  reg_mhl_vcm:2;
        UINT32  reg_diff_rt_en:1;
        UINT32  reg_cec_enb:1;
        UINT32  reg_cec_rsel:3;
        UINT32  reg_cec_rpu_en:1;
        UINT32  reg_hpd_en:1;
        UINT32  reg_cable_det_en:1;
        UINT32  reg_ldo_tmds_pu:1;
        UINT32  reg_ldo_tmds_vsel:3;
        UINT32  reg_ldo_tmds_capsel:1;
    };
}tmds_scr3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:11;
        UINT32  reg_tv_pre_div:1;
        UINT32  reg_tv_ldiv:6;
        UINT32  reg_tv_pstep_en:1;
        UINT32  reg_tv_pstep:3;
        UINT32  reg_hdmi_ck_en:1;
        UINT32  reg_pixel_div3:1;
        UINT32  reg_pixel_div5:1;
        UINT32  reg_pixel_div16:3;
        UINT32  reg_tmds_div5:1;
        UINT32  reg_tmds_div16:3;
    };
}tvpll_ctrl1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:3;
        UINT32  reg_sel_ref_clk27:1;
        UINT32  reg_reserve:16;
        UINT32  reg_tv_pll_pu:1;
        UINT32  reg_tv_icp:3;
        UINT32  reg_tv_rs:3;
        UINT32  reg_tv_bypass_pll:1;
        UINT32  reg_tv_force_vc:1;
        UINT32  reg_tv_set_vc:2;
        UINT32  reg_tv_tst_en:1;
    };
}tvpll_ctrl2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:7;
        UINT32  reg_pcr_smooth_en:1;
        UINT32  rvd:1;
        UINT32  reg_pcr_phase_sel:1;
        UINT32  rvd:1;
        UINT32  reg_pcr_ctl_en:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_fupdn:1;
        UINT32  reg_plldds_ddsen:1;
        UINT32  rvd:4;
        UINT32  reg_shuffle_en:1;
        UINT32  reg_tvpll_fupdn:1;
        UINT32  reg_tvpll_reserve:1;
        UINT32  reg_tvpll_stop:1;
        UINT32  rvd:9;
    };
}tvpll_ctrl3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_plldds_pcr_acc:16;
        UINT32  reg_plldds_pcr_overflow:16;
    };
}tvpll_ctrl4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:8;
        UINT32  reg_pcr_a_n_nxt_add:8;
        UINT32  reg_pcr_a_n_nxt_add_period:16;
    };
}tvpll_ctrl5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_n_pcr_a_n_nxt:16;
        UINT32  reg_pcr_a_n_nxt:16;
    };
}tvpll_ctrl5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:11;
        UINT32  reg_pllgpu_n:2;
        UINT32  reg_pllgpu_m:7;
        UINT32  reg_pllgpu_ip:3;
        UINT32  reg_pllgpu_k:2;
        UINT32  reg_pllgpu_wdmode:2;
        UINT32  rvd:4;
        UINT32  reg_pllgpu_tst:1;
    };
}pll_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:21;
        UINT32  reg_pllgpu_rs:3;
        UINT32  rvd:2;
        UINT32  reg_pllgpu_cs:2;
        UINT32  rvd:1;
        UINT32  reg_pllgpu_oeb:1;
        UINT32  reg_pllgpu_rstb:1;
        UINT32  reg_pllgpu_pow:1;
    };
}pll_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:11;
        UINT32  reg_pllgpu_n_2:2;
        UINT32  reg_pllgpu_m_2:7;
        UINT32  reg_pllgpu_ip_2:3;
        UINT32  reg_pllgpu_k_2:2;
        UINT32  reg_pllgpu_wdmode_2:2;
        UINT32  rvd:4;
        UINT32  reg_pllgpu_tst_2:1;
    };
}pll_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:21;
        UINT32  reg_pllgpu_rs_2:3;
        UINT32  rvd:2;
        UINT32  reg_pllgpu_cs_2:2;
        UINT32  rvd:1;
        UINT32  reg_pllgpu_oeb_2:1;
        UINT32  reg_pllgpu_rstb_2:1;
        UINT32  reg_pllgpu_pow_2:1;
    };
}pll_gpu4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:16;
        UINT32  reg_trng_res:2;
        UINT32  reg_trng_gain:2;
        UINT32  reg_trng_fs:2;
        UINT32  reg_trng_div:2;
        UINT32  reg_trng_d:4;
        UINT32  rvd:2;
        UINT32  reg_trng_tst:1;
        UINT32  reg_trng_pow:1;
    };
}trng1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  crt_dbg1_div_sel:2;
        UINT32  crt_dbg0_div_sel:2;
        UINT32  rvd:15;
        UINT32  crt_dbg_en:1;
        UINT32  crt_dbg_sel0:6;
        UINT32  crt_dbg_sel1:6;
    };
}crt_debug_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dummy_reg:31;
        UINT32  ejtag_hif_det:1;
    };
}dummy_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sb2_rom_bist_en:1;
        UINT32  rvd:17;
        UINT32  sce_bist_mode:1;
        UINT32  tp_bist_en:1;
        UINT32  rvd:2;
        UINT32  hdmi0_bist_en:1;
        UINT32  hdmi1_bist_en:1;
        UINT32  vde_bist_en:1;
        UINT32  dc3_bist_en:1;
        UINT32  dc2_bist_en:1;
        UINT32  ae_rom_bist_en:1;
        UINT32  ae_bist_en:1;
        UINT32  cr_nf1_bist_en:1;
        UINT32  cp_bist_en:1;
        UINT32  write_data:1;
    };
}crt_bist_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:14;
        UINT32  ve17_bist_en:1;
        UINT32  ve16_bist_en:1;
        UINT32  ve15_bist_en:1;
        UINT32  ve14_bist_en:1;
        UINT32  ve13_bist_en:1;
        UINT32  ve12_bist_en:1;
        UINT32  ve11_bist_en:1;
        UINT32  ve10_bist_en:1;
        UINT32  ve9_bist_en:1;
        UINT32  ve8_bist_en:1;
        UINT32  ve7_bist_en:1;
        UINT32  ve6_bist_en:1;
        UINT32  ve5_bist_en:1;
        UINT32  ve4_bist_en:1;
        UINT32  ve3_bist_en:1;
        UINT32  ve2_bist_en:1;
        UINT32  ve1_bist_en:1;
        UINT32  write_data:1;
    };
}crt_bist_en2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:18;
        UINT32  etn2_bist_en:1;
        UINT32  rvd:2;
        UINT32  md_bist_en:1;
        UINT32  usb2_bist_en:1;
        UINT32  usb1_bist_en:1;
        UINT32  rvd:2;
        UINT32  kcpu1_bist_en:1;
        UINT32  rvd:2;
        UINT32  vcpu_bist_en:1;
        UINT32  acpu_bist_en:1;
        UINT32  write_data:1;
    };
}crt_bist_en3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:18;
        UINT32  sce_drf_bist_mode:1;
        UINT32  tp_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  hdmi0_drf_bist_en:1;
        UINT32  hdmi1_drf_bist_en:1;
        UINT32  vde_drf_bist_en:1;
        UINT32  dc3_drf_bist_en:1;
        UINT32  dc2_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  cr_nf1_drf_bist_en:1;
        UINT32  cp_drf_bist_en:1;
        UINT32  write_data:1;
    };
}crt_drf_bist_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:14;
        UINT32  ve17_drf_bist_en:1;
        UINT32  ve16_drf_bist_en:1;
        UINT32  ve15_drf_bist_en:1;
        UINT32  ve14_drf_bist_en:1;
        UINT32  ve13_drf_bist_en:1;
        UINT32  ve12_drf_bist_en:1;
        UINT32  ve11_drf_bist_en:1;
        UINT32  ve10_drf_bist_en:1;
        UINT32  ve9_drf_bist_en:1;
        UINT32  ve8_drf_bist_en:1;
        UINT32  ve7_drf_bist_en:1;
        UINT32  ve6_drf_bist_en:1;
        UINT32  ve5_drf_bist_en:1;
        UINT32  ve4_drf_bist_en:1;
        UINT32  ve3_drf_bist_en:1;
        UINT32  ve2_drf_bist_en:1;
        UINT32  ve1_drf_bist_en:1;
        UINT32  write_data:1;
    };
}crt_drf_bist_en2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:17;
        UINT32  ae_drf_bist_en:1;
        UINT32  etn2_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  md_drf_bist_en:1;
        UINT32  usb2_drf_bist_en:1;
        UINT32  usb1_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  kcpu1_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  vcpu_drf_bist_en:1;
        UINT32  acpu_drf_bist_en:1;
        UINT32  write_data:1;
    };
}crt_drf_bist_en3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:18;
        UINT32  sce_drf_test_resume:1;
        UINT32  tp_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  hdmi0_drf_test_resume:1;
        UINT32  hdmi1_drf_test_resume:1;
        UINT32  vde_drf_test_resume:1;
        UINT32  dc3_drf_test_resume:1;
        UINT32  dc2_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  cr_nf1_drf_test_resume:1;
        UINT32  cp_drf_test_resume:1;
        UINT32  write_data:1;
    };
}crt_drf_test_resume1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:14;
        UINT32  ve17_drf_test_resume:1;
        UINT32  ve16_drf_test_resume:1;
        UINT32  ve15_drf_test_resume:1;
        UINT32  ve14_drf_test_resume:1;
        UINT32  ve13_drf_test_resume:1;
        UINT32  ve12_drf_test_resume:1;
        UINT32  ve11_drf_test_resume:1;
        UINT32  ve10_drf_test_resume:1;
        UINT32  ve9_drf_test_resume:1;
        UINT32  ve8_drf_test_resume:1;
        UINT32  ve7_drf_test_resume:1;
        UINT32  ve6_drf_test_resume:1;
        UINT32  ve5_drf_test_resume:1;
        UINT32  ve4_drf_test_resume:1;
        UINT32  ve3_drf_test_resume:1;
        UINT32  ve2_drf_test_resume:1;
        UINT32  ve1_drf_test_resume:1;
        UINT32  write_data:1;
    };
}crt_drf_test_resume2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:17;
        UINT32  ae_drf_test_resume:1;
        UINT32  etn2_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  md_drf_test_resume:1;
        UINT32  usb2_drf_test_resume:1;
        UINT32  usb1_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  kcpu1_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  vcpu_drf_test_resume:1;
        UINT32  acpu_drf_test_resume:1;
        UINT32  write_data:1;
    };
}crt_drf_test_resume3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:30;
        UINT32  vde_drf_start_pause:1;
        UINT32  write_data:1;
    };
}crt_drf_start_pause1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:29;
        UINT32  etn2_drf_start_pause:1;
        UINT32  vcpu_drf_start_pause:1;
        UINT32  write_data:1;
    };
}crt_drf_start_pause3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  kcpu_bisr_en:1;
        UINT32  vcpu_bisr_en:1;
        UINT32  acpu_bisr_en:1;
        UINT32  write_data:1;
    };
}crt_bisr_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  cp42k_bisr_rstn:1;
        UINT32  kcpu_bisr_rstn:1;
        UINT32  vcpu_bisr_rstn:1;
        UINT32  acpu_bisr_rstn:1;
        UINT32  write_data:1;
    };
}crt_bisr_rstn1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  cp42k_bisr_pwr_rstn:1;
        UINT32  kcpu_bisr_pwr_rstn:1;
        UINT32  vcpu_bisr_pwr_rstn:1;
        UINT32  acpu_bisr_pwr_rstn:1;
        UINT32  write_data:1;
    };
}crt_bisr_pwr_rstn1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  cp42k_bisr_hold_remap:1;
        UINT32  kcpu_bisr_hold_remap:1;
        UINT32  vcpu_bisr_hold_remap:1;
        UINT32  acpu_bisr_hold_remap:1;
        UINT32  write_data:1;
    };
}crt_bisr_hold_remap1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  spnr_bisr_remap:1;
        UINT32  rvd:1;
        UINT32  iuzd_bisr_remap:1;
        UINT32  ich1_bisr_sdnr_remap:1;
    };
}crt_bisr_hold_remap2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  cp42k_bisr_second_run_en:1;
        UINT32  kcpu_bisr_second_run_en:1;
        UINT32  vcpu_bisr_second_run_en:1;
        UINT32  acpu_bisr_second_run_en:1;
        UINT32  write_data:1;
    };
}crt_bisr_2nd_run_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  cp42k_drf_bisr_en:1;
        UINT32  kcpu_drf_bisr_en:1;
        UINT32  vcpu_drf_bisr_en:1;
        UINT32  acpu_drf_bisr_en:1;
        UINT32  write_data:1;
    };
}crt_drf_bisr_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  cp42k_drf_bisr_test_resume:1;
        UINT32  kcpu_drf_bisr_test_resume:1;
        UINT32  vcpu_drf_bisr_test_resume:1;
        UINT32  acpu_drf_bisr_test_resume:1;
        UINT32  write_data:1;
    };
}crt_drf_bisr_test_resume1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:29;
        UINT32  vcpu_sleepsys_r:1;
        UINT32  acpu_sleepsys_r:1;
        UINT32  rvd:1;
    };
}crt_sleep_ack1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:29;
        UINT32  vcpu_sleepreq_r:1;
        UINT32  acpu_sleepreq_r:1;
        UINT32  write_data:1;
    };
}crt_sleep_req1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:19;
        UINT32  nf_light_sleep:1;
        UINT32  md_light_sleep:1;
        UINT32  etn_light_sleep:1;
        UINT32  cp_light_sleep:1;
        UINT32  hdmitx_light_sleep:1;
        UINT32  dc_sb_light_sleep:1;
        UINT32  sb2_light_sleep:1;
        UINT32  ve_light_sleep:1;
        UINT32  sb2_rom_light_sleep:1;
        UINT32  kcpu_light_sleep:1;
        UINT32  vcpu_light_sleep:1;
        UINT32  acpu_light_sleep:1;
        UINT32  write_data:1;
    };
}crt_light_sleep1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  spnr_bisr_rstn:1;
        UINT32  rvd:1;
        UINT32  iuzd_bisr_rstn:1;
        UINT32  ich1_bisr_sdnr_rstn:1;
    };
}crt_bisr_rstn2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:27;
        UINT32  mbist_ve_st:1;
        UINT32  mbist_tp_st:1;
        UINT32  mbist_md_st:1;
        UINT32  mbist_hdmi_st:1;
        UINT32  mbist_acpu_st:1;
    };
}bist_st1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:7;
        UINT32  vcpu_bist_fail:1;
        UINT32  rvd:9;
        UINT32  vde_bist_fail0:1;
        UINT32  sce_bist_fail:1;
        UINT32  kcpu_bist_fail:1;
        UINT32  etn_bist2_fail:1;
        UINT32  nf1_bist_fail:1;
        UINT32  me_bist_fail1:1;
        UINT32  me_bist_fail0:1;
        UINT32  rvd:2;
        UINT32  dc3_bist_fail:1;
        UINT32  dc2_bist_fail:1;
        UINT32  rvd:2;
        UINT32  cp_bist_fail:1;
        UINT32  ae_bist_fail:1;
    };
}bist_st2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:15;
        UINT32  ve_bist17_fail:1;
        UINT32  ve_bist16_fail:1;
        UINT32  ve_bist15_fail:1;
        UINT32  ve_bist14_fail:1;
        UINT32  ve_bist13_fail:1;
        UINT32  ve_bist12_fail:1;
        UINT32  ve_bist11_fail:1;
        UINT32  ve_bist10_fail:1;
        UINT32  ve_bist9_fail:1;
        UINT32  ve_bist8_fail:1;
        UINT32  ve_bist7_fail:1;
        UINT32  ve_bist6_fail:1;
        UINT32  ve_bist5_fail:1;
        UINT32  ve_bist4_fail:1;
        UINT32  ve_bist3_fail:1;
        UINT32  ve_bist2_fail:1;
        UINT32  ve_bist1_fail:1;
    };
}bist_st3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:7;
        UINT32  vcpu_drf_bist_fail:1;
        UINT32  vde_drf_bist_fail:1;
        UINT32  rvd:10;
        UINT32  etn_drf_bist2_fail:1;
        UINT32  sce_drf_bist_fail:1;
        UINT32  nf1_drf_bist_fail:1;
        UINT32  me_drf_bist_fail1:1;
        UINT32  me_drf_bist_fail0:1;
        UINT32  rvd:2;
        UINT32  dc3_drf_bist_fail:1;
        UINT32  dc2_drf_bist_fail:1;
        UINT32  rvd:2;
        UINT32  cp_drf_bist_fail:1;
        UINT32  ae_drf_bist_fail:1;
    };
}drf_st1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:15;
        UINT32  ve_drf_bist17_fail:1;
        UINT32  ve_drf_bist16_fail:1;
        UINT32  ve_drf_bist15_fail:1;
        UINT32  ve_drf_bist14_fail:1;
        UINT32  ve_drf_bist13_fail:1;
        UINT32  ve_drf_bist12_fail:1;
        UINT32  ve_drf_bist11_fail:1;
        UINT32  ve_drf_bist10_fail:1;
        UINT32  ve_drf_bist9_fail:1;
        UINT32  ve_drf_bist8_fail:1;
        UINT32  ve_drf_bist7_fail:1;
        UINT32  ve_drf_bist6_fail:1;
        UINT32  ve_drf_bist5_fail:1;
        UINT32  ve_drf_bist4_fail:1;
        UINT32  ve_drf_bist3_fail:1;
        UINT32  ve_drf_bist2_fail:1;
        UINT32  ve_drf_bist1_fail:1;
    };
}drf_st2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:4;
        UINT32  spnr_bisr_done:1;
        UINT32  rvd:1;
        UINT32  i3ddma_uzd_bisr_done:1;
        UINT32  ich1_bisr_sdnr_done:1;
        UINT32  rvd:20;
        UINT32  cp42k_bisr_done:1;
        UINT32  kcpu_bisr_done:1;
        UINT32  vcpu_bisr_done:1;
        UINT32  rvd:1;
    };
}crt_bisr_done1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:3;
        UINT32  vcpu_bisr_fail:1;
        UINT32  rvd:24;
        UINT32  cp42k_bisr_fail:1;
        UINT32  kcpu_bisr_st:1;
        UINT32  rvd:1;
        UINT32  acpu_bisr_st:1;
    };
}crt_bisr_st1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:28;
        UINT32  cp42k_bisr_repaired:1;
        UINT32  kcpu_bisr_repaired:1;
        UINT32  vcpu_bisr_repaired:1;
        UINT32  acpu_bisr_repaired:1;
    };
}crt_bisr_repaired1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:4;
        UINT32  vcpu_bisr_out:28;
    };
}crt_bisr_out1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:25;
        UINT32  cp42k_bisr_out:7;
    };
}crt_bisr_out2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:3;
        UINT32  vcpu_drf_bisr_fail:1;
        UINT32  rvd:24;
        UINT32  cp42k_drf_bisr_fail:1;
        UINT32  cp42k_drf_bisr_done:1;
        UINT32  rvd:2;
    };
}crt_drf_bisr_st1_RBUS;





#else //apply LITTLE_ENDIAN


//======DEFAULT register structure define==========
typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rstn_misc:1;
        UINT32  rstn_rng:1;
        UINT32  rvd:1;
        UINT32  rstn_gspi:1;
        UINT32  rstn_usb_arb:1;
        UINT32  rstn_usb_mac1:1;
        UINT32  rstn_usb_mac0:1;
        UINT32  rvd:1;
        UINT32  rstn_usb_phy0:1;
        UINT32  rstn_usb_phy1:1;
        UINT32  rstn_usb_phy2:1;
        UINT32  rstn_ddc:1;
        UINT32  rstn_hdmi:1;
        UINT32  rstn_etn:1;
        UINT32  rstn_etn_phy:1;
        UINT32  rstn_aio:1;
        UINT32  rstn_me1:1;
        UINT32  rstn_ve_p2:1;
        UINT32  rstn_ve:1;
        UINT32  rstn_tve:1;
        UINT32  rstn_vo:1;
        UINT32  rstn_gpu:1;
        UINT32  rstn_se:1;
        UINT32  rstn_dcu:1;
        UINT32  rstn_dc_phy:1;
        UINT32  rstn_cp:1;
        UINT32  rstn_md:1;
        UINT32  rstn_tp:1;
        UINT32  rstn_ae:1;
        UINT32  rstn_nf:1;
        UINT32  rstn_demod:1;
        UINT32  rvd:1;
    };
}soft_reset1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rstn_acpu:1;
        UINT32  rstn_vcpu:1;
        UINT32  rvd:1;
        UINT32  rstn_vde:1;
        UINT32  rstn_scpu:1;
        UINT32  rstn_pllreg:1;
        UINT32  rstn_gpio:1;
        UINT32  rstn_pwm:1;
        UINT32  rstn_scpu_wrap:1;
        UINT32  rstn_pcr_cnt:1;
        UINT32  rstn_cr:1;
        UINT32  rstn_emmc:1;
        UINT32  rstn_dtv_demod:1;
        UINT32  rstn_padmux:1;
        UINT32  rstn_usb_mac:1;
        UINT32  rstn_bistreg:1;
        UINT32  rstn_atvin:1;
        UINT32  rstn_atvin2:1;
        UINT32  rstn_tm:1;
        UINT32  rstn_tve_clkgen:1;
        UINT32  rvd:1;
        UINT32  rstn_cec:1;
        UINT32  rstn_ir:1;
        UINT32  rstn_sc:1;
        UINT32  rstn_pcmcia:1;
        UINT32  rstn_i2c_2:1;
        UINT32  rstn_i2c_1:1;
        UINT32  rstn_i2c_0:1;
        UINT32  rstn_ur1:1;
        UINT32  rvd:2;
        UINT32  rstn_ur2:1;
    };
}soft_reset2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rstn_sb2:1;
        UINT32  rstn_disp:1;
        UINT32  rstn_dispim:1;
        UINT32  rstn_vodma:1;
        UINT32  rstn_apll_adc:1;
        UINT32  rstn_ifadc:1;
        UINT32  rstn_audio_dac:1;
        UINT32  rstn_audio_adc:1;
        UINT32  rstn_audio2_dac:1;
        UINT32  rstn_vbis0:1;
        UINT32  rstn_vdec2:1;
        UINT32  rstn_if_demod:1;
        UINT32  rstn_tvsb2:1;
        UINT32  rstn_tvsb1:1;
        UINT32  rstn_tvsb3:1;
        UINT32  rstn_osdcomp:1;
        UINT32  rstn_tv_tve:1;
        UINT32  rstn_hdmirx:1;
        UINT32  rstn_kcpu:1;
        UINT32  rstn_vdec:1;
        UINT32  rstn_tvsb1_tve:1;
        UINT32  rvd:4;
        UINT32  rstn_scpu_l2:1;
        UINT32  rstn_scpu_dbg:1;
        UINT32  rstn_kt:1;
        UINT32  rstn_sce:1;
        UINT32  rstn_dsc:1;
        UINT32  rstn_nd:1;
        UINT32  rstn_akl:1;
    };
}soft_reset3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  clk_en_misc:1;
        UINT32  clk_en_hdmirx:1;
        UINT32  clk_en_usb1:1;
        UINT32  clk_en_gspi:1;
        UINT32  clk_en_usb0:1;
        UINT32  clk_en_pcr:1;
        UINT32  rvd:1;
        UINT32  reg_clken_3d_gde:1;
        UINT32  clk_en_hdmi:1;
        UINT32  clk_en_etn:1;
        UINT32  clk_en_aio:1;
        UINT32  clk_en_tve_sys:1;
        UINT32  clk_en_ve_p2:1;
        UINT32  clk_en_ve:1;
        UINT32  clk_en_tve:1;
        UINT32  clken_tve_clkgen:1;
        UINT32  clken_tv_tve:1;
        UINT32  clk_en_se:1;
        UINT32  clk_en_dcu:1;
        UINT32  clk_en_cp:1;
        UINT32  clk_en_md:1;
        UINT32  clk_en_tp:1;
        UINT32  clk_en_ae:1;
        UINT32  clk_en_nf:1;
        UINT32  clk_en_emmc:1;
        UINT32  clk_en_cr:1;
        UINT32  clken_vdec:1;
        UINT32  clk_en_demod:1;
        UINT32  clken_tvsb1_tve:1;
        UINT32  rvd:3;
    };
}clock_enable1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  reg_clken_scpu_cssys:1;
        UINT32  clk_en_scpu:1;
        UINT32  clk_en_scpu_wrap:1;
        UINT32  clk_en_acpu:1;
        UINT32  clk_en_vcpu:1;
        UINT32  clk_en_ade:1;
        UINT32  clk_en_vde:1;
        UINT32  clk_en_me1:1;
        UINT32  rvd:1;
        UINT32  rvd:1;
        UINT32  rvd:1;
        UINT32  clk_en_misc_ir:1;
        UINT32  clk_en_misc_sc:1;
        UINT32  clk_en_misc_pcmcia:1;
        UINT32  clk_en_misc_i2c_1:1;
        UINT32  rvd:1;
        UINT32  rvd:1;
        UINT32  rvd:6;
        UINT32  clk_en_misc_i2c_2:1;
        UINT32  clk_en_pwm:1;
        UINT32  rvd:2;
        UINT32  clk_en_ur1:1;
        UINT32  rvd:2;
        UINT32  clk_en_ur2:1;
    };
}clock_enable2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  clk_en_sb2:1;
        UINT32  clk_en_kcpu:1;
        UINT32  clken_pllreg:1;
        UINT32  clken_disp:1;
        UINT32  clken_dispim:1;
        UINT32  clken_vodma:1;
        UINT32  clken_ddc:1;
        UINT32  clk_en_kt:1;
        UINT32  clk_en_sce:1;
        UINT32  clk_en_dsc:1;
        UINT32  clk_en_akl:1;
        UINT32  clken_dtv_demod:1;
        UINT32  clken_padmux:1;
        UINT32  clken_audio2_daad_128fs:1;
        UINT32  clken_audio2_daad_256fs:1;
        UINT32  clken_audio2_512fs:1;
        UINT32  clken_ifadc:1;
        UINT32  clken_audio_pre512fs:1;
        UINT32  clken_audio_daad_256fs:1;
        UINT32  clken_audio_daad_128fs:1;
        UINT32  clken_vbis0:1;
        UINT32  clken_bistreg:1;
        UINT32  clken_disp2tve:1;
        UINT32  clken_if_demod:1;
        UINT32  clken_apll_adc:1;
        UINT32  clken_osdcomp:1;
        UINT32  clken_atvin_ifd:1;
        UINT32  clken_atvin_vd:1;
        UINT32  clken_tm:1;
        UINT32  clken_tvsb3:1;
        UINT32  clken_tvsb2:1;
        UINT32  clken_tvsb1:1;
    };
}group1_ck_en_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sclk_sel:1;
        UINT32  rvd:3;
        UINT32  inv_vbis0_clk:1;
        UINT32  vbis0_yppsel:1;
        UINT32  rvd:2;
        UINT32  vdec_x27_clksel:1;
        UINT32  rvd:6;
        UINT32  atvin_vdadc_tve_clk_sel:1;
        UINT32  atvin_vd_clk_sel:1;
        UINT32  atvin_clk_sel:1;
        UINT32  rvd:5;
        UINT32  epi_div_clksel:2;
        UINT32  epi_dbg_clksel:1;
        UINT32  ve_rif_use_p2clk:1;
        UINT32  rvd:5;
    };
}group1_ck_sel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tveck_mix_sel:1;
        UINT32  write_en1:1;
        UINT32  dac1_ckinv:1;
        UINT32  dac2_ckinv:1;
        UINT32  rvd:2;
        UINT32  write_en2:1;
        UINT32  hdmi_phy_ckinv:1;
        UINT32  write_en3:1;
        UINT32  clk_tve_p_vo_clk_sel:1;
        UINT32  write_en4:1;
        UINT32  clk_tve_p_vo_clk_sel2:1;
        UINT32  write_en5:1;
        UINT32  rvd:19;
    };
}tve_ck_sel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dac1_div:5;
        UINT32  write_en1:1;
        UINT32  dac2_div:5;
        UINT32  write_en2:1;
        UINT32  rvd:20;
    };
}disp_pll_div_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tve_div:4;
        UINT32  write_en3:1;
        UINT32  hdmi_div:3;
        UINT32  write_en4:1;
        UINT32  hdmi_phy_clk_sel:1;
        UINT32  write_en5:1;
        UINT32  hdmi_pxl_repeat:1;
        UINT32  write_en6:1;
        UINT32  sel_pllhdmi_clk:1;
        UINT32  write_en7:1;
        UINT32  sel_plldisp_clk2:1;
        UINT32  write_en8:1;
        UINT32  hdmi_tmds_div:2;
        UINT32  write_en9:1;
        UINT32  tve_i_div:2;
        UINT32  write_en10:1;
        UINT32  hdmi_deep_clk_sel:1;
        UINT32  write_en11:1;
        UINT32  rvd:7;
    };
}disp_pll_div2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_dac2_phy_clk_inv:1;
        UINT32  reg_dac1_phy_clk_inv:1;
        UINT32  reg_tve_iclk_sel:2;
        UINT32  reg_dac2_clk_sel:2;
        UINT32  reg_tve_pclk_sel:2;
        UINT32  reg_dac1_clk_sel:2;
        UINT32  reg_tve_hdmi_div_sel:2;
        UINT32  reg_hdmi_tmds_div:2;
        UINT32  rvd:18;
    };
}disp_pll_div3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  audio_use_sysclk:1;
        UINT32  rvd:31;
    };
}audio_clk_ctl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  bus_freq_sel:1;
        UINT32  ddr_freq_sel:2;
        UINT32  acpu_freq_sel:2;
        UINT32  vcpu_freq_sel:2;
        UINT32  scpu_freq_sel:2;
        UINT32  rvd:23;
    };
}pll_div_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  nf_div:3;
        UINT32  rvd:29;
    };
}nf_cksel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  nds_sc_div:3;
        UINT32  rvd:29;
    };
}nds_sc_cksel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  cr_div:3;
        UINT32  write_en1:1;
        UINT32  emmc_div:3;
        UINT32  write_en2:1;
        UINT32  rvd:22;
        UINT32  cremmc_clk_sel:1;
        UINT32  write_en3:1;
    };
}cr_cksel_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  aud_dtv_freq_sel:3;
        UINT32  rvd:1;
        UINT32  dtv_demod_multi_req_disable:1;
        UINT32  rvd:27;
    };
}clkdiv_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scpu_wd_cnt:12;
        UINT32  rvd:4;
        UINT32  scpu_wd_en:1;
        UINT32  rvd:15;
    };
}arm_wd_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dtv_str_pow:1;
        UINT32  rvd:1;
        UINT32  dtv_str_status:1;
        UINT32  rvd:1;
        UINT32  dtv_iso_en:1;
        UINT32  rvd:3;
        UINT32  atv_str_pow:1;
        UINT32  rvd:1;
        UINT32  atv_str_status:1;
        UINT32  rvd:1;
        UINT32  atv_iso_en:1;
        UINT32  rvd:19;
    };
}power_ctrl0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllscpu_wdout:1;
        UINT32  reg_pllacpu_wdout:1;
        UINT32  reg_pllvcpu_wdout:1;
        UINT32  plldds_wdout:1;
        UINT32  rvd:1;
        UINT32  plldisp_wdout:1;
        UINT32  reg_pllbus_wdout:1;
        UINT32  rvd:1;
        UINT32  plletn_wdout:1;
        UINT32  pllbus2_wdout:1;
        UINT32  plldif_wdout:1;
        UINT32  rvd:1;
        UINT32  reg_pllbush_wdout:1;
        UINT32  pll512fs_wdout:1;
        UINT32  pllaud_status:1;
        UINT32  pllgpu_wdout_2:1;
        UINT32  pllgpu_wdout:1;
        UINT32  reg_pllvodma_wdout:1;
        UINT32  pll27x_wdout:1;
        UINT32  rvd:13;
    };
}pll_wdout_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tm_pwron_dly:16;
        UINT32  tm_data_out:7;
        UINT32  rvd:1;
        UINT32  tm_reverse_cmp_out:1;
        UINT32  tm_data_sampled:1;
        UINT32  tm_data_valid:1;
        UINT32  tm_enable:1;
        UINT32  rvd:4;
    };
}tm_ctrl0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tm_sample_dly:16;
        UINT32  tm_compare_dly:16;
    };
}tm_ctrl1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  reg_tm_pow:1;
        UINT32  reg_tm_sinl:2;
        UINT32  reg_tm_sos:3;
        UINT32  reg_tm_sbg:3;
        UINT32  rvd:22;
    };
}tm_ctrl2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_dss_rst_n:1;
        UINT32  dss_c35d5_ro_sel:3;
        UINT32  dss_c35d5_wire_sel:1;
        UINT32  dss_c35d5_data_in:20;
        UINT32  dss_c35d5_speed_en:1;
        UINT32  rvd:6;
    };
}dss00_dss_gpu0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_ready:1;
        UINT32  dss_c35d5_count_out:20;
        UINT32  dss_c35d5_wsort_go:1;
        UINT32  rvd:10;
    };
}dss01_dss_gpu0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_dbgo:16;
        UINT32  rvd:16;
    };
}dss02_dss_gpu0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dss_rst_n:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_speed_en:1;
        UINT32  rvd:6;
    };
}dss03_dss_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_ready:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_wsort_go:1;
        UINT32  rvd:10;
    };
}dss04_dss_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dbgo:16;
        UINT32  rvd:16;
    };
}dss05_dss_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_dss_rst_n:1;
        UINT32  dss_c35d5_ro_sel:3;
        UINT32  dss_c35d5_wire_sel:1;
        UINT32  dss_c35d5_data_in:20;
        UINT32  dss_c35d5_speed_en:1;
        UINT32  rvd:6;
    };
}dss06_dss_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_ready:1;
        UINT32  dss_c35d5_count_out:20;
        UINT32  dss_c35d5_wsort_go:1;
        UINT32  rvd:10;
    };
}dss07_dss_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_dbgo:16;
        UINT32  rvd:16;
    };
}dss08_dss_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dss_rst_n:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_speed_en:1;
        UINT32  rvd:6;
    };
}dss09_dss_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_ready:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_wsort_go:1;
        UINT32  rvd:10;
    };
}dss10_dss_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dbgo:16;
        UINT32  rvd:16;
    };
}dss11_dss_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dss_rst_n:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_speed_en:1;
        UINT32  rvd:6;
    };
}dss12_dss_top0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_ready:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_wsort_go:1;
        UINT32  rvd:10;
    };
}dss13_dss_top0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dbgo:16;
        UINT32  rvd:16;
    };
}dss14_dss_top0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dss_rst_n:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_speed_en:1;
        UINT32  rvd:6;
    };
}dss15_dss_tvsb10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_ready:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_wsort_go:1;
        UINT32  rvd:10;
    };
}dss16_dss_tvsb10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dbgo:16;
        UINT32  rvd:16;
    };
}dss17_dss_tvsb10_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_dss_rst_n:1;
        UINT32  dss_c35d5_ro_sel:3;
        UINT32  dss_c35d5_wire_sel:1;
        UINT32  dss_c35d5_data_in:20;
        UINT32  dss_c35d5_speed_en:1;
        UINT32  rvd:6;
    };
}dss18_dss_tvsb11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_ready:1;
        UINT32  dss_c35d5_count_out:20;
        UINT32  dss_c35d5_wsort_go:1;
        UINT32  rvd:10;
    };
}dss19_dss_tvsb11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35d5_dbgo:16;
        UINT32  rvd:16;
    };
}dss20_dss_tvsb11_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dss_rst_n:1;
        UINT32  dss_c35_ro_sel:3;
        UINT32  dss_c35_wire_sel:1;
        UINT32  dss_c35_data_in:20;
        UINT32  dss_c35_speed_en:1;
        UINT32  rvd:6;
    };
}dss21_dss_tvsb30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_ready:1;
        UINT32  dss_c35_count_out:20;
        UINT32  dss_c35_wsort_go:1;
        UINT32  rvd:10;
    };
}dss22_dss_tvsb30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dss_c35_dbgo:16;
        UINT32  rvd:16;
    };
}dss23_dss_tvsb30_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm0_rstn:1;
        UINT32  csm0_csm_en:1;
        UINT32  csm0_in_sel:2;
        UINT32  csm0_acc_mode:1;
        UINT32  csm0_hold:1;
        UINT32  csm0_read_en:1;
        UINT32  csm0_addr:4;
        UINT32  csm0_data_sel:2;
        UINT32  rvd:19;
    };
}csm00_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm0_ready:1;
        UINT32  rvd:31;
    };
}csm01_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm0_data:32;
    };
}csm02_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm1_rstn:1;
        UINT32  csm1_csm_en:1;
        UINT32  csm1_in_sel:2;
        UINT32  csm1_acc_mode:1;
        UINT32  csm1_hold:1;
        UINT32  csm1_read_en:1;
        UINT32  csm1_addr:4;
        UINT32  csm1_data_sel:2;
        UINT32  rvd:19;
    };
}csm03_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm1_ready:1;
        UINT32  rvd:31;
    };
}csm04_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  csm1_data:32;
    };
}csm05_csm_ddr_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rm_200:4;
        UINT32  rme_200:1;
        UINT32  rm_300:4;
        UINT32  rme_300:1;
        UINT32  rm_400:4;
        UINT32  rme_400:1;
        UINT32  rm_600:4;
        UINT32  rme_600:1;
        UINT32  rm_800:4;
        UINT32  rme_800:1;
        UINT32  rm_rom:4;
        UINT32  rme_rom:1;
        UINT32  rvd:2;
    };
}chip_sram_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  resume_cycle_sel:1;
        UINT32  rvd:31;
    };
}chip_misc_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sf_sel:1;
        UINT32  nf_sel:1;
        UINT32  testmode:1;
        UINT32  rvd:5;
        UINT32  clk_na_fail:1;
        UINT32  rvd:23;
    };
}chip_info2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dds_rstn:1;
        UINT32  write_en2:1;
        UINT32  rvd:30;
    };
}aps_ctl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  kcpu_boot_info:32;
    };
}pwdn_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  acpu_boot_info:32;
    };
}pwdn_ctrl2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  kcpu_sw_rst:1;
        UINT32  write_en1:1;
        UINT32  kcpu_boot_info_valid:1;
        UINT32  write_en2:1;
        UINT32  rvd:28;
    };
}pwdn_ctrl3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  acpu_boot_info_valid:1;
        UINT32  rvd:31;
    };
}pwdn_ctrl4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  scpu_config_done:1;
        UINT32  write_en1:1;
        UINT32  dac_test:1;
        UINT32  write_en2:1;
        UINT32  rvd:28;
    };
}at_speed_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  etn_phy_125m_en:1;
        UINT32  write_en1:1;
        UINT32  etn_phy_gpio_en:1;
        UINT32  write_en2:1;
        UINT32  rvd:28;
    };
}ana_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  tp0_dm_sel:1;
        UINT32  tp1_dm_sel:1;
        UINT32  tp2_dm_sel:1;
        UINT32  demod_i2c_sel:1;
        UINT32  demod_i2c_saddr:1;
        UINT32  rvd:27;
    };
}tp_demod_ctrl_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  sf_en:1;
        UINT32  rvd:31;
    };
}control0_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  akl_busy:1;
        UINT32  rvd:31;
    };
}security_st_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd1:32;
    };
}dmy2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  bus_ssc_stms:2;
        UINT32  rvd:6;
        UINT32  bus_ssc_ssfpv:8;
        UINT32  bus_ssc_ssn:7;
        UINT32  rvd:1;
        UINT32  bus_ssc_sss:6;
        UINT32  bus_ssc_ckinv:1;
        UINT32  bus_ssc_sse:1;
    };
}bus_pll_ssc_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  bush_ssc_stms:2;
        UINT32  rvd:6;
        UINT32  bush_ssc_ssfpv:8;
        UINT32  bush_ssc_ssn:7;
        UINT32  rvd:1;
        UINT32  bush_ssc_sss:6;
        UINT32  bush_ssc_ckinv:1;
        UINT32  bush_ssc_sse:1;
    };
}bush_pll_ssc_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllscpu_tst:1;
        UINT32  rvd:4;
        UINT32  reg_pllscpu_wdset:1;
        UINT32  reg_pllscpu_wdrst:1;
        UINT32  reg_pllscpu_o:2;
        UINT32  reg_pllscpu_ip:3;
        UINT32  reg_pllscpu_m:8;
        UINT32  reg_pllscpu_n:2;
        UINT32  rvd:10;
    };
}pll_scpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllscpu_pow:1;
        UINT32  pllscpu_rstb:1;
        UINT32  reg_pllscpu_oeb:1;
        UINT32  reg_pllscpu_cp:1;
        UINT32  reg_pllscpu_cs:2;
        UINT32  rvd:2;
        UINT32  reg_pllscpu_rs:3;
        UINT32  rvd:21;
    };
}pll_scpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllacpu_tst:1;
        UINT32  rvd:4;
        UINT32  reg_pllacpu_wdset:1;
        UINT32  reg_pllacpu_wdrst:1;
        UINT32  reg_pllacpu_o:2;
        UINT32  reg_pllacpu_ip:3;
        UINT32  reg_pllacpu_m:7;
        UINT32  reg_pllacpu_n:2;
        UINT32  rvd:11;
    };
}pll_acpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllacpu_pow:1;
        UINT32  pllacpu_rstb:1;
        UINT32  reg_pllacpu_oeb:1;
        UINT32  rvd:1;
        UINT32  reg_pllacpu_cs:2;
        UINT32  rvd:2;
        UINT32  reg_pllacpu_rs:3;
        UINT32  rvd:21;
    };
}pll_acpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllvcpu_tst:1;
        UINT32  rvd:4;
        UINT32  reg_pllvcpu_wdset:1;
        UINT32  reg_pllvcpu_wdrst:1;
        UINT32  reg_pllvcpu_o:2;
        UINT32  rvd:2;
        UINT32  reg_pllvcpu_m:7;
        UINT32  reg_pllvcpu_n:2;
        UINT32  reg_pllvcpu_ip:3;
        UINT32  rvd:9;
    };
}pll_vcpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllvcpu_pow:1;
        UINT32  pllvcpu_rstb:1;
        UINT32  reg_pllvcpu_oeb:1;
        UINT32  rvd:1;
        UINT32  reg_pllvcpu_cs:2;
        UINT32  rvd:2;
        UINT32  reg_pllvcpu_rs:3;
        UINT32  rvd:21;
    };
}pll_vcpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllbus_c3:2;
        UINT32  reg_pllbus_r3:3;
        UINT32  reg_pllbus_cp:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_cs:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_rs:3;
        UINT32  rvd:1;
        UINT32  reg_pllbus_ip:3;
        UINT32  reg_pllbus_m:7;
        UINT32  reg_pllbus_n:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_o:2;
        UINT32  rvd:2;
    };
}pll_bus1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllbus_pstst:1;
        UINT32  reg_pllbus_tst:1;
        UINT32  write_en1:1;
        UINT32  reg_pllbus_vcorb:1;
        UINT32  reg_pllbus_psen:1;
        UINT32  reg_pllbus_fupdn:1;
        UINT32  write_en3:1;
        UINT32  rvd:2;
        UINT32  reg_pllbus_wdmode:2;
        UINT32  write_en4:1;
        UINT32  reg_pllbus_pi_bias:2;
        UINT32  reg_pllbus_pi_rs:2;
        UINT32  reg_pllbus_pi_rl:2;
        UINT32  write_en5:1;
        UINT32  rvd:13;
    };
}pll_bus2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllbus_pow:1;
        UINT32  reg_pllbus_rstb:1;
        UINT32  reg_pllbus_oeb:1;
        UINT32  rvd:29;
    };
}pll_bus3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllbus_c3_h:2;
        UINT32  reg_pllbus_r3_h:3;
        UINT32  reg_pllbus_cp_h:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_cs_h:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_rs_h:3;
        UINT32  rvd:1;
        UINT32  reg_pllbus_ip_h:3;
        UINT32  reg_pllbus_m_h:7;
        UINT32  reg_pllbus_n_h:2;
        UINT32  rvd:1;
        UINT32  reg_pllbus_o_h:2;
        UINT32  rvd:2;
    };
}pll_bush1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllbus_pstst_h:1;
        UINT32  reg_pllbus_tst_h:1;
        UINT32  write_en1:1;
        UINT32  reg_pllbus_vcorb_h:1;
        UINT32  reg_pllbus_psen_h:1;
        UINT32  reg_pllbus_fupdn_h:1;
        UINT32  write_en3:1;
        UINT32  rvd:2;
        UINT32  reg_pllbus_wdmode_h:2;
        UINT32  write_en4:1;
        UINT32  reg_pllbus_pi_bias_h:2;
        UINT32  reg_pllbus_pi_rs_h:2;
        UINT32  reg_pllbus_pi_rl_h:2;
        UINT32  write_en5:1;
        UINT32  rvd:13;
    };
}pll_bush2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllbus_pow_h:1;
        UINT32  reg_pllbus_rstb_h:1;
        UINT32  reg_pllbus_oeb_h:1;
        UINT32  rvd:29;
    };
}pll_bush3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllvodma_rs:3;
        UINT32  reg_pllvodma_cs:2;
        UINT32  reg_pllvodma_wdrst:1;
        UINT32  reg_pllvodma_wdset:1;
        UINT32  reg_pllvodma_o:2;
        UINT32  reg_pllvodma_ip:3;
        UINT32  reg_pllvodma_m:7;
        UINT32  rvd:1;
        UINT32  reg_pllvodma_n:2;
        UINT32  rvd:10;
    };
}pll_vodma1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllvodma_pow:1;
        UINT32  reg_pllvodma_rstb:1;
        UINT32  reg_pllvodma_oeb:1;
        UINT32  reg_pllvodma_tst:1;
        UINT32  rvd:28;
    };
}pll_vodma2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_plltst_sel:5;
        UINT32  rvd:3;
        UINT32  reg_plltst_div:2;
        UINT32  rvd:2;
        UINT32  reg_pllbus_reg:2;
        UINT32  rvd:2;
        UINT32  reg_pllbus_reser:4;
        UINT32  reg_pllcpu_reg:2;
        UINT32  rvd:10;
    };
}pllbus_tst_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_plldds_wdmode:2;
        UINT32  reg_plldds_pi_bias:2;
        UINT32  reg_plldds_pi_rs:2;
        UINT32  reg_plldds_pi_rl:2;
        UINT32  reg_plldds_c3:2;
        UINT32  reg_plldds_r3:3;
        UINT32  reg_plldds_cp:2;
        UINT32  reg_plldds_cs:2;
        UINT32  reg_plldds_rs:3;
        UINT32  reg_plldds_ip:3;
        UINT32  reg_plldds_m:7;
        UINT32  reg_plldds_n:2;
    };
}pll_disp_sd1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:10;
        UINT32  rvd:1;
        UINT32  reg_plldds_pstst:1;
        UINT32  reg_plldds_tst:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_vcorb:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_ddsen:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_fupdn:1;
        UINT32  rvd:1;
        UINT32  pcr_a_ctl_en:1;
        UINT32  rvd:1;
        UINT32  pcr_a_phase_sel:1;
        UINT32  rvd:1;
        UINT32  pcr_a_smooth_en:1;
        UINT32  rvd:1;
        UINT32  psaud_2a_phase_sel:1;
        UINT32  psaud_1a_phase_sel:1;
        UINT32  rvd:2;
        UINT32  rvd:2;
    };
}pll_disp_sd2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_psaud2_rstb:1;
        UINT32  reg_psaud2_oeb:1;
        UINT32  reg_psaud1_rstb:1;
        UINT32  reg_psaud1_oeb:1;
        UINT32  rvd:16;
        UINT32  reg_psaud2_psen:1;
        UINT32  reg_psaud2_tst:1;
        UINT32  reg_psaud2_div:1;
        UINT32  reg_psaud2_fupdn:1;
        UINT32  rvd:1;
        UINT32  reg_psaud1_psen:1;
        UINT32  reg_psaud1_tst:1;
        UINT32  rvd:1;
        UINT32  reg_psaud1_div:1;
        UINT32  reg_psaud1_fupdn:1;
        UINT32  rvd:1;
        UINT32  rvd:1;
    };
}pll_disp_sd3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_plldds_pow:1;
        UINT32  reg_plldds_rstb:1;
        UINT32  reg_plldds_oeb:1;
        UINT32  rvd:1;
        UINT32  reg_plldds_o:2;
        UINT32  rvd:26;
    };
}pll_disp_sd4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  plldds_pcr_overflow:16;
        UINT32  plldds_pcr_acc:16;
    };
}pll_disp_sd5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  pcr_a_n_nxt:16;
        UINT32  n_pcr_a_n_nxt:16;
    };
}pll_disp_sd6_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  pcr_a_n_nxt_add_period:16;
        UINT32  pcr_a_n_nxt_add:8;
        UINT32  rvd:8;
    };
}pll_disp_sd7_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dpll_cs:2;
        UINT32  dpll_cp:2;
        UINT32  dpll_rs:3;
        UINT32  rvd:1;
        UINT32  dpll_ip:3;
        UINT32  rvd:1;
        UINT32  dpll_n:3;
        UINT32  rvd:5;
        UINT32  dpll_m:8;
        UINT32  rvd:4;
    };
}pll_disp1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  dpll_pow:1;
        UINT32  dpll_vcorstb:1;
        UINT32  dpll_freeze:1;
        UINT32  dpll_clksel:1;
        UINT32  dpll_wdset:1;
        UINT32  dpll_wdrst:1;
        UINT32  dpll_rstb:1;
        UINT32  rvd:5;
        UINT32  dpll_o:2;
        UINT32  dpll_bpn:1;
        UINT32  rvd:1;
        UINT32  dpll_bpphs:1;
        UINT32  dpll_reserve:1;
        UINT32  rvd:2;
        UINT32  dpll_stop:1;
        UINT32  dpll_fupdn:1;
        UINT32  rvd:2;
        UINT32  dpll_reser:1;
        UINT32  rvd:3;
        UINT32  dpll_ldosel:2;
        UINT32  rvd:2;
    };
}pll_disp2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  plt_cmu_macpll_divn:3;
        UINT32  rvd:1;
        UINT32  plt_cmu_macpll_divm:3;
        UINT32  rvd:25;
    };
}pll_vby1_mac1_RBUS;

    typedef union
    {
    UINT32 regValue;
    struct{
        UINT32  reg_tx_pll_rs:3;
        UINT32  reg_tx_pll_icp:3;
        UINT32  reg_tx_pll_edge:1;
        UINT32  reg_tx_set_vc:2;
        UINT32  reg_tx_force_vc:1;
        UINT32  reg_tx_en_emph:1;
        UINT32  reg_tx_emph:3;
        UINT32  reg_tx_ibias:2;
        UINT32  reg_tx_amp:4;
        UINT32  reg_tx_ck5xn_duty:2;
        UINT32  reg_tx_ck5xp_duty:2;
        UINT32  reg_tv_cs:2;
        UINT32  reg_tv_cp:2;
        UINT32  reg_tvkvco:1;
        UINT32  reg_tv_wdmode:2;
        UINT32  rvd:1;
    };
    }tmds_scr1_RBUS;
    
    typedef union
    {
    UINT32 regValue;
    struct{
        UINT32  reg_bypass_din:1;
        UINT32  reg_pll_vco_scale:2;
        UINT32  reg_tx_rt_sel:2;
        UINT32  reg_tx_rt_en:1;
        UINT32  reg_tx_bypass_pll:1;
        UINT32  reg_tst_sel:2;
        UINT32  reg_pll_tst_en:1;
        UINT32  reg_tx_vgate:3;
        UINT32  reg_tx_tst_en:1;
        UINT32  reg_tx_slew:2;
        UINT32  reg_tx_driver:2;
        UINT32  reg_tx_pu:4;
        UINT32  reg_tx_pll_pu:1;
        UINT32  reg_tx_pll_kvco:1;
        UINT32  reg_tx_pll_cs:2;
        UINT32  reg_tx_pll_cp:2;
        UINT32  reg_tx_pdrv_isel:2;
        UINT32  rvd:2;
    };
    }tmds_scr2_RBUS;
    
    typedef union
    {
    UINT32 regValue;
    struct{
        UINT32  reg_ldo_tmds_capsel:1;
        UINT32  reg_ldo_tmds_vsel:3;
        UINT32  reg_ldo_tmds_pu:1;
        UINT32  reg_cable_det_en:1;
        UINT32  reg_hpd_en:1;
        UINT32  reg_cec_rpu_en:1;
        UINT32  reg_cec_rsel:3;
        UINT32  reg_cec_enb:1;
        UINT32  reg_diff_rt_en:1;
        UINT32  reg_mhl_vcm:2;
        UINT32  reg_mhl_div:1;
        UINT32  reg_rxsense:2;
        UINT32  reg_force_rxsense:1;
        UINT32  reg_en_mhl:1;
        UINT32  reg_ldo_pll_vsel:3;
        UINT32  reg_ldo_pll_pu:1;
        UINT32  reg_ldo_cco_vsel:2;
        UINT32  reg_ldo_cco_pu:1;
        UINT32  reg_tx_v1p05_sel:2;
        UINT32  reg_tx_pll_wdmode:2;
        UINT32  rvd:1;
    };
    }tmds_scr3_RBUS;
    
    typedef union
    {
    UINT32 regValue;
    struct{
        UINT32  reg_tmds_div16:3;
        UINT32  reg_tmds_div5:1;
        UINT32  reg_pixel_div16:3;
        UINT32  reg_pixel_div5:1;
        UINT32  reg_pixel_div3:1;
        UINT32  reg_hdmi_ck_en:1;
        UINT32  reg_tv_pstep:3;
        UINT32  reg_tv_pstep_en:1;
        UINT32  reg_tv_ldiv:6;
        UINT32  reg_tv_pre_div:1;
        UINT32  rvd:11;
    };
    }tvpll_ctrl1_RBUS;
    
    typedef union
    {
    UINT32 regValue;
    struct{
        UINT32  reg_tv_tst_en:1;
        UINT32  reg_tv_set_vc:2;
        UINT32  reg_tv_force_vc:1;
        UINT32  reg_tv_bypass_pll:1;
        UINT32  reg_tv_rs:3;
        UINT32  reg_tv_icp:3;
        UINT32  reg_tv_pll_pu:1;
        UINT32  reg_reserve:16;
        UINT32  reg_sel_ref_clk27:1;
        UINT32  rvd:3;
    };
    }tvpll_ctrl2_RBUS;
    
    typedef union
    {
    UINT32 regValue;
    struct{
        UINT32  rvd:9;
        UINT32  reg_tvpll_stop:1;
        UINT32  reg_tvpll_reserve:1;
        UINT32  reg_tvpll_fupdn:1;
        UINT32  reg_shuffle_en:1;
        UINT32  rvd:4;
        UINT32  reg_plldds_ddsen:1;
        UINT32  reg_plldds_fupdn:1;
        UINT32  rvd:1;
        UINT32  reg_pcr_ctl_en:1;
        UINT32  rvd:1;
        UINT32  reg_pcr_phase_sel:1;
        UINT32  rvd:1;
        UINT32  reg_pcr_smooth_en:1;
        UINT32  rvd:7;
    };
    }tvpll_ctrl3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_plldds_pcr_overflow:16;
        UINT32  reg_plldds_pcr_acc:16;
    };
}tvpll_ctrl4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pcr_a_n_nxt_add_period:16;
        UINT32  reg_pcr_a_n_nxt_add:8;
        UINT32  rvd:8;
    };
}tvpll_ctrl5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pcr_a_n_nxt:16;
        UINT32  reg_n_pcr_a_n_nxt:16;
    };
}tvpll_ctrl5_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllgpu_tst:1;
        UINT32  rvd:4;
        UINT32  reg_pllgpu_wdmode:2;
        UINT32  reg_pllgpu_k:2;
        UINT32  reg_pllgpu_ip:3;
        UINT32  reg_pllgpu_m:7;
        UINT32  reg_pllgpu_n:2;
        UINT32  rvd:11;
    };
}pll_gpu1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllgpu_pow:1;
        UINT32  reg_pllgpu_rstb:1;
        UINT32  reg_pllgpu_oeb:1;
        UINT32  rvd:1;
        UINT32  reg_pllgpu_cs:2;
        UINT32  rvd:2;
        UINT32  reg_pllgpu_rs:3;
        UINT32  rvd:21;
    };
}pll_gpu2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllgpu_tst_2:1;
        UINT32  rvd:4;
        UINT32  reg_pllgpu_wdmode_2:2;
        UINT32  reg_pllgpu_k_2:2;
        UINT32  reg_pllgpu_ip_2:3;
        UINT32  reg_pllgpu_m_2:7;
        UINT32  reg_pllgpu_n_2:2;
        UINT32  rvd:11;
    };
}pll_gpu3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_pllgpu_pow_2:1;
        UINT32  reg_pllgpu_rstb_2:1;
        UINT32  reg_pllgpu_oeb_2:1;
        UINT32  rvd:1;
        UINT32  reg_pllgpu_cs_2:2;
        UINT32  rvd:2;
        UINT32  reg_pllgpu_rs_2:3;
        UINT32  rvd:21;
    };
}pll_gpu4_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  reg_trng_pow:1;
        UINT32  reg_trng_tst:1;
        UINT32  rvd:2;
        UINT32  reg_trng_d:4;
        UINT32  reg_trng_div:2;
        UINT32  reg_trng_fs:2;
        UINT32  reg_trng_gain:2;
        UINT32  reg_trng_res:2;
        UINT32  rvd:16;
    };
}trng1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  crt_dbg_sel1:6;
        UINT32  crt_dbg_sel0:6;
        UINT32  crt_dbg_en:1;
        UINT32  rvd:15;
        UINT32  crt_dbg0_div_sel:2;
        UINT32  crt_dbg1_div_sel:2;
    };
}crt_debug_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ejtag_hif_det:1;
        UINT32  dummy_reg:31;
    };
}dummy_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  cp_bist_en:1;
        UINT32  cr_nf1_bist_en:1;
        UINT32  ae_bist_en:1;
        UINT32  ae_rom_bist_en:1;
        UINT32  dc2_bist_en:1;
        UINT32  dc3_bist_en:1;
        UINT32  vde_bist_en:1;
        UINT32  hdmi1_bist_en:1;
        UINT32  hdmi0_bist_en:1;
        UINT32  rvd:2;
        UINT32  tp_bist_en:1;
        UINT32  sce_bist_mode:1;
        UINT32  rvd:17;
        UINT32  sb2_rom_bist_en:1;
    };
}crt_bist_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  ve1_bist_en:1;
        UINT32  ve2_bist_en:1;
        UINT32  ve3_bist_en:1;
        UINT32  ve4_bist_en:1;
        UINT32  ve5_bist_en:1;
        UINT32  ve6_bist_en:1;
        UINT32  ve7_bist_en:1;
        UINT32  ve8_bist_en:1;
        UINT32  ve9_bist_en:1;
        UINT32  ve10_bist_en:1;
        UINT32  ve11_bist_en:1;
        UINT32  ve12_bist_en:1;
        UINT32  ve13_bist_en:1;
        UINT32  ve14_bist_en:1;
        UINT32  ve15_bist_en:1;
        UINT32  ve16_bist_en:1;
        UINT32  ve17_bist_en:1;
        UINT32  rvd:14;
    };
}crt_bist_en2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_bist_en:1;
        UINT32  vcpu_bist_en:1;
        UINT32  rvd:2;
        UINT32  kcpu1_bist_en:1;
        UINT32  rvd:2;
        UINT32  usb1_bist_en:1;
        UINT32  usb2_bist_en:1;
        UINT32  md_bist_en:1;
        UINT32  rvd:2;
        UINT32  etn2_bist_en:1;
        UINT32  rvd:18;
    };
}crt_bist_en3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  cp_drf_bist_en:1;
        UINT32  cr_nf1_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  dc2_drf_bist_en:1;
        UINT32  dc3_drf_bist_en:1;
        UINT32  vde_drf_bist_en:1;
        UINT32  hdmi1_drf_bist_en:1;
        UINT32  hdmi0_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  tp_drf_bist_en:1;
        UINT32  sce_drf_bist_mode:1;
        UINT32  rvd:18;
    };
}crt_drf_bist_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  ve1_drf_bist_en:1;
        UINT32  ve2_drf_bist_en:1;
        UINT32  ve3_drf_bist_en:1;
        UINT32  ve4_drf_bist_en:1;
        UINT32  ve5_drf_bist_en:1;
        UINT32  ve6_drf_bist_en:1;
        UINT32  ve7_drf_bist_en:1;
        UINT32  ve8_drf_bist_en:1;
        UINT32  ve9_drf_bist_en:1;
        UINT32  ve10_drf_bist_en:1;
        UINT32  ve11_drf_bist_en:1;
        UINT32  ve12_drf_bist_en:1;
        UINT32  ve13_drf_bist_en:1;
        UINT32  ve14_drf_bist_en:1;
        UINT32  ve15_drf_bist_en:1;
        UINT32  ve16_drf_bist_en:1;
        UINT32  ve17_drf_bist_en:1;
        UINT32  rvd:14;
    };
}crt_drf_bist_en2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_drf_bist_en:1;
        UINT32  vcpu_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  kcpu1_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  usb1_drf_bist_en:1;
        UINT32  usb2_drf_bist_en:1;
        UINT32  md_drf_bist_en:1;
        UINT32  rvd:2;
        UINT32  etn2_drf_bist_en:1;
        UINT32  ae_drf_bist_en:1;
        UINT32  rvd:17;
    };
}crt_drf_bist_en3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  cp_drf_test_resume:1;
        UINT32  cr_nf1_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  dc2_drf_test_resume:1;
        UINT32  dc3_drf_test_resume:1;
        UINT32  vde_drf_test_resume:1;
        UINT32  hdmi1_drf_test_resume:1;
        UINT32  hdmi0_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  tp_drf_test_resume:1;
        UINT32  sce_drf_test_resume:1;
        UINT32  rvd:18;
    };
}crt_drf_test_resume1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  ve1_drf_test_resume:1;
        UINT32  ve2_drf_test_resume:1;
        UINT32  ve3_drf_test_resume:1;
        UINT32  ve4_drf_test_resume:1;
        UINT32  ve5_drf_test_resume:1;
        UINT32  ve6_drf_test_resume:1;
        UINT32  ve7_drf_test_resume:1;
        UINT32  ve8_drf_test_resume:1;
        UINT32  ve9_drf_test_resume:1;
        UINT32  ve10_drf_test_resume:1;
        UINT32  ve11_drf_test_resume:1;
        UINT32  ve12_drf_test_resume:1;
        UINT32  ve13_drf_test_resume:1;
        UINT32  ve14_drf_test_resume:1;
        UINT32  ve15_drf_test_resume:1;
        UINT32  ve16_drf_test_resume:1;
        UINT32  ve17_drf_test_resume:1;
        UINT32  rvd:14;
    };
}crt_drf_test_resume2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_drf_test_resume:1;
        UINT32  vcpu_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  kcpu1_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  usb1_drf_test_resume:1;
        UINT32  usb2_drf_test_resume:1;
        UINT32  md_drf_test_resume:1;
        UINT32  rvd:2;
        UINT32  etn2_drf_test_resume:1;
        UINT32  ae_drf_test_resume:1;
        UINT32  rvd:17;
    };
}crt_drf_test_resume3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  vde_drf_start_pause:1;
        UINT32  rvd:30;
    };
}crt_drf_start_pause1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  vcpu_drf_start_pause:1;
        UINT32  etn2_drf_start_pause:1;
        UINT32  rvd:29;
    };
}crt_drf_start_pause3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_bisr_en:1;
        UINT32  vcpu_bisr_en:1;
        UINT32  kcpu_bisr_en:1;
        UINT32  rvd:28;
    };
}crt_bisr_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_bisr_rstn:1;
        UINT32  vcpu_bisr_rstn:1;
        UINT32  kcpu_bisr_rstn:1;
        UINT32  cp42k_bisr_rstn:1;
        UINT32  rvd:27;
    };
}crt_bisr_rstn1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_bisr_pwr_rstn:1;
        UINT32  vcpu_bisr_pwr_rstn:1;
        UINT32  kcpu_bisr_pwr_rstn:1;
        UINT32  cp42k_bisr_pwr_rstn:1;
        UINT32  rvd:27;
    };
}crt_bisr_pwr_rstn1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_bisr_hold_remap:1;
        UINT32  vcpu_bisr_hold_remap:1;
        UINT32  kcpu_bisr_hold_remap:1;
        UINT32  cp42k_bisr_hold_remap:1;
        UINT32  rvd:27;
    };
}crt_bisr_hold_remap1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ich1_bisr_sdnr_remap:1;
        UINT32  iuzd_bisr_remap:1;
        UINT32  rvd:1;
        UINT32  spnr_bisr_remap:1;
        UINT32  rvd:28;
    };
}crt_bisr_hold_remap2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_bisr_second_run_en:1;
        UINT32  vcpu_bisr_second_run_en:1;
        UINT32  kcpu_bisr_second_run_en:1;
        UINT32  cp42k_bisr_second_run_en:1;
        UINT32  rvd:27;
    };
}crt_bisr_2nd_run_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_drf_bisr_en:1;
        UINT32  vcpu_drf_bisr_en:1;
        UINT32  kcpu_drf_bisr_en:1;
        UINT32  cp42k_drf_bisr_en:1;
        UINT32  rvd:27;
    };
}crt_drf_bisr_en1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_drf_bisr_test_resume:1;
        UINT32  vcpu_drf_bisr_test_resume:1;
        UINT32  kcpu_drf_bisr_test_resume:1;
        UINT32  cp42k_drf_bisr_test_resume:1;
        UINT32  rvd:27;
    };
}crt_drf_bisr_test_resume1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  acpu_sleepsys_r:1;
        UINT32  vcpu_sleepsys_r:1;
        UINT32  rvd:29;
    };
}crt_sleep_ack1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_sleepreq_r:1;
        UINT32  vcpu_sleepreq_r:1;
        UINT32  rvd:29;
    };
}crt_sleep_req1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  write_data:1;
        UINT32  acpu_light_sleep:1;
        UINT32  vcpu_light_sleep:1;
        UINT32  kcpu_light_sleep:1;
        UINT32  sb2_rom_light_sleep:1;
        UINT32  ve_light_sleep:1;
        UINT32  sb2_light_sleep:1;
        UINT32  dc_sb_light_sleep:1;
        UINT32  hdmitx_light_sleep:1;
        UINT32  cp_light_sleep:1;
        UINT32  etn_light_sleep:1;
        UINT32  md_light_sleep:1;
        UINT32  nf_light_sleep:1;
        UINT32  rvd:19;
    };
}crt_light_sleep1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ich1_bisr_sdnr_rstn:1;
        UINT32  iuzd_bisr_rstn:1;
        UINT32  rvd:1;
        UINT32  spnr_bisr_rstn:1;
        UINT32  rvd:28;
    };
}crt_bisr_rstn2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  mbist_acpu_st:1;
        UINT32  mbist_hdmi_st:1;
        UINT32  mbist_md_st:1;
        UINT32  mbist_tp_st:1;
        UINT32  mbist_ve_st:1;
        UINT32  rvd:27;
    };
}bist_st1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ae_bist_fail:1;
        UINT32  cp_bist_fail:1;
        UINT32  rvd:2;
        UINT32  dc2_bist_fail:1;
        UINT32  dc3_bist_fail:1;
        UINT32  rvd:2;
        UINT32  me_bist_fail0:1;
        UINT32  me_bist_fail1:1;
        UINT32  nf1_bist_fail:1;
        UINT32  etn_bist2_fail:1;
        UINT32  kcpu_bist_fail:1;
        UINT32  sce_bist_fail:1;
        UINT32  vde_bist_fail0:1;
        UINT32  rvd:9;
        UINT32  vcpu_bist_fail:1;
        UINT32  rvd:7;
    };
}bist_st2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ve_bist1_fail:1;
        UINT32  ve_bist2_fail:1;
        UINT32  ve_bist3_fail:1;
        UINT32  ve_bist4_fail:1;
        UINT32  ve_bist5_fail:1;
        UINT32  ve_bist6_fail:1;
        UINT32  ve_bist7_fail:1;
        UINT32  ve_bist8_fail:1;
        UINT32  ve_bist9_fail:1;
        UINT32  ve_bist10_fail:1;
        UINT32  ve_bist11_fail:1;
        UINT32  ve_bist12_fail:1;
        UINT32  ve_bist13_fail:1;
        UINT32  ve_bist14_fail:1;
        UINT32  ve_bist15_fail:1;
        UINT32  ve_bist16_fail:1;
        UINT32  ve_bist17_fail:1;
        UINT32  rvd:15;
    };
}bist_st3_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ae_drf_bist_fail:1;
        UINT32  cp_drf_bist_fail:1;
        UINT32  rvd:2;
        UINT32  dc2_drf_bist_fail:1;
        UINT32  dc3_drf_bist_fail:1;
        UINT32  rvd:2;
        UINT32  me_drf_bist_fail0:1;
        UINT32  me_drf_bist_fail1:1;
        UINT32  nf1_drf_bist_fail:1;
        UINT32  sce_drf_bist_fail:1;
        UINT32  etn_drf_bist2_fail:1;
        UINT32  rvd:10;
        UINT32  vde_drf_bist_fail:1;
        UINT32  vcpu_drf_bist_fail:1;
        UINT32  rvd:7;
    };
}drf_st1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  ve_drf_bist1_fail:1;
        UINT32  ve_drf_bist2_fail:1;
        UINT32  ve_drf_bist3_fail:1;
        UINT32  ve_drf_bist4_fail:1;
        UINT32  ve_drf_bist5_fail:1;
        UINT32  ve_drf_bist6_fail:1;
        UINT32  ve_drf_bist7_fail:1;
        UINT32  ve_drf_bist8_fail:1;
        UINT32  ve_drf_bist9_fail:1;
        UINT32  ve_drf_bist10_fail:1;
        UINT32  ve_drf_bist11_fail:1;
        UINT32  ve_drf_bist12_fail:1;
        UINT32  ve_drf_bist13_fail:1;
        UINT32  ve_drf_bist14_fail:1;
        UINT32  ve_drf_bist15_fail:1;
        UINT32  ve_drf_bist16_fail:1;
        UINT32  ve_drf_bist17_fail:1;
        UINT32  rvd:15;
    };
}drf_st2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:1;
        UINT32  vcpu_bisr_done:1;
        UINT32  kcpu_bisr_done:1;
        UINT32  cp42k_bisr_done:1;
        UINT32  rvd:20;
        UINT32  ich1_bisr_sdnr_done:1;
        UINT32  i3ddma_uzd_bisr_done:1;
        UINT32  rvd:1;
        UINT32  spnr_bisr_done:1;
        UINT32  rvd:4;
    };
}crt_bisr_done1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  acpu_bisr_st:1;
        UINT32  rvd:1;
        UINT32  kcpu_bisr_st:1;
        UINT32  cp42k_bisr_fail:1;
        UINT32  rvd:24;
        UINT32  vcpu_bisr_fail:1;
        UINT32  rvd:3;
    };
}crt_bisr_st1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  acpu_bisr_repaired:1;
        UINT32  vcpu_bisr_repaired:1;
        UINT32  kcpu_bisr_repaired:1;
        UINT32  cp42k_bisr_repaired:1;
        UINT32  rvd:28;
    };
}crt_bisr_repaired1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  vcpu_bisr_out:28;
        UINT32  rvd:4;
    };
}crt_bisr_out1_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  cp42k_bisr_out:7;
        UINT32  rvd:25;
    };
}crt_bisr_out2_RBUS;

typedef union
{
    UINT32 regValue;
    struct{
        UINT32  rvd:2;
        UINT32  cp42k_drf_bisr_done:1;
        UINT32  cp42k_drf_bisr_fail:1;
        UINT32  rvd:24;
        UINT32  vcpu_drf_bisr_fail:1;
        UINT32  rvd:3;
    };
}crt_drf_bisr_st1_RBUS;


#endif


#endif //_HDMI_CRT_REG_H_

