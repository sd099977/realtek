/**************************************************************
// Spec Version                  : 0.55
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/12 18:31:12
***************************************************************/


#ifndef _SYS_REG_H_INCLUDED_
#define _SYS_REG_H_INCLUDED_
#ifdef  _SYS_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     rstn_demod:1;
unsigned int     rstn_nf:1;
unsigned int     rstn_ae:1;
unsigned int     rstn_tp:1;
unsigned int     rstn_md:1;
unsigned int     rstn_cp:1;
unsigned int     rstn_dc_phy:1;
unsigned int     rstn_dcu:1;
unsigned int     rstn_se:1;
unsigned int     rstn_gpu:1;
unsigned int     rstn_vo:1;
unsigned int     rstn_tve:1;
unsigned int     rstn_ve:1;
unsigned int     rstn_ve_p2:1;
unsigned int     rstn_me1:1;
unsigned int     rstn_aio:1;
unsigned int     rstn_etn_phy:1;
unsigned int     rstn_etn:1;
unsigned int     rstn_hdmi:1;
unsigned int     RSTN_DDC:1;
unsigned int     rstn_usb_phy2:1;
unsigned int     rstn_usb_phy1:1;
unsigned int     rstn_usb_phy0:1;
unsigned int     reserved_1:1;
unsigned int     rstn_usb_mac0:1;
unsigned int     rstn_usb_mac1:1;
unsigned int     rstn_usb_arb:1;
unsigned int     rstn_gspi:1;
unsigned int     reserved_2:1;
unsigned int     rstn_rng:1;
unsigned int     rstn_misc:1;
}SYS_SOFT_RESET1;

typedef struct 
{
unsigned int     rstn_ur2:1;
unsigned int     reserved_0:2;
unsigned int     rstn_ur1:1;
unsigned int     rstn_i2c_0:1;
unsigned int     rstn_i2c_1:1;
unsigned int     rstn_i2c_2:1;
unsigned int     rstn_pcmcia:1;
unsigned int     rstn_sc:1;
unsigned int     rstn_ir:1;
unsigned int     rstn_cec:1;
unsigned int     reserved_1:1;
unsigned int     rstn_tve_clkgen:1;
unsigned int     RSTN_TM:1;
unsigned int     RSTN_ATVIN2:1;
unsigned int     RSTN_ATVIN:1;
unsigned int     RSTN_BISTREG:1;
unsigned int     RSTN_USB_MAC:1;
unsigned int     RSTN_PADMUX:1;
unsigned int     RSTN_DTV_DEMOD:1;
unsigned int     rstn_emmc:1;
unsigned int     rstn_cr:1;
unsigned int     rstn_pcr_cnt:1;
unsigned int     rstn_scpu_wrap:1;
unsigned int     RSTN_PWM:1;
unsigned int     RSTN_GPIO:1;
unsigned int     RSTN_PLLREG:1;
unsigned int     RSTN_SCPU:1;
unsigned int     rstn_vde:1;
unsigned int     reserved_2:1;
unsigned int     rstn_vcpu:1;
unsigned int     rstn_acpu:1;
}SYS_SOFT_RESET2;

typedef struct 
{
unsigned int     rstn_akl:1;
unsigned int     rstn_nd:1;
unsigned int     rstn_dsc:1;
unsigned int     rstn_sce:1;
unsigned int     rstn_kt:1;
unsigned int     rstn_scpu_dbg:1;
unsigned int     rstn_scpu_l2:1;
unsigned int     reserved_0:4;
unsigned int     RSTN_TVSB1_TVE:1;
unsigned int     RSTN_VDEC:1;
unsigned int     rstn_kcpu:1;
unsigned int     rstn_hdmirx:1;
unsigned int     RSTN_TV_TVE:1;
unsigned int     RSTN_OSDCOMP:1;
unsigned int     RSTN_TVSB3:1;
unsigned int     RSTN_TVSB1:1;
unsigned int     RSTN_TVSB2:1;
unsigned int     RSTN_IF_DEMOD:1;
unsigned int     RSTN_VDEC2:1;
unsigned int     RSTN_VBIS0:1;
unsigned int     RSTN_AUDIO2_DAC:1;
unsigned int     RSTN_AUDIO_ADC:1;
unsigned int     RSTN_AUDIO_DAC:1;
unsigned int     RSTN_IFADC:1;
unsigned int     RSTN_APLL_ADC:1;
unsigned int     RSTN_VODMA:1;
unsigned int     RSTN_DISPIM:1;
unsigned int     RSTN_DISP:1;
unsigned int     rstn_sb2:1;
}SYS_SOFT_RESET3;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     CLKEN_TVSB1_TVE:1;
unsigned int     clk_en_demod:1;
unsigned int     CLKEN_VDEC:1;
unsigned int     clk_en_cr:1;
unsigned int     clk_en_emmc:1;
unsigned int     clk_en_nf:1;
unsigned int     clk_en_ae:1;
unsigned int     clk_en_tp:1;
unsigned int     clk_en_md:1;
unsigned int     clk_en_cp:1;
unsigned int     clk_en_dcu:1;
unsigned int     clk_en_se:1;
unsigned int     CLKEN_TV_TVE:1;
unsigned int     clken_tve_clkgen:1;
unsigned int     clk_en_tve:1;
unsigned int     clk_en_ve:1;
unsigned int     clk_en_ve_p2:1;
unsigned int     clk_en_tve_sys:1;
unsigned int     clk_en_aio:1;
unsigned int     clk_en_etn:1;
unsigned int     clk_en_hdmi:1;
unsigned int     reg_clken_3d_gde:1;
unsigned int     clk_en_iso_misc:1;
unsigned int     clk_en_pcr:1;
unsigned int     clk_en_usb0:1;
unsigned int     clk_en_gspi:1;
unsigned int     clk_en_usb1:1;
unsigned int     clk_en_hdmirx:1;
unsigned int     clk_en_misc:1;
}SYS_CLOCK_ENABLE1;

typedef struct 
{
unsigned int     clk_en_ur2:1;
unsigned int     reserved_0:2;
unsigned int     clk_en_ur1:1;
unsigned int     reserved_1:2;
unsigned int     clk_en_pwm:1;
unsigned int     clk_en_misc_i2c_2:1;
unsigned int     reserved_2:6;
unsigned int     clk_en_iso_mis:1;
unsigned int     clk_en_misc_i2c_0:1;
unsigned int     clk_en_misc_i2c_1:1;
unsigned int     clk_en_misc_pcmcia:1;
unsigned int     clk_en_misc_sc:1;
unsigned int     clk_en_misc_ir:1;
unsigned int     clk_en_misc_cec:1;
unsigned int     clk_en_misc_rtc:1;
unsigned int     clk_en_misc_vfd:1;
unsigned int     clk_en_me1:1;
unsigned int     clk_en_vde:1;
unsigned int     clk_en_ade:1;
unsigned int     clk_en_vcpu:1;
unsigned int     clk_en_acpu:1;
unsigned int     clk_en_scpu_wrap:1;
unsigned int     clk_en_scpu:1;
unsigned int     reg_clken_scpu_cssys:1;
unsigned int     reserved_3:1;
}SYS_CLOCK_ENABLE2;

typedef struct 
{
unsigned int     CLKEN_TVSB1:1;
unsigned int     CLKEN_TVSB2:1;
unsigned int     CLKEN_TVSB3:1;
unsigned int     CLKEN_TM:1;
unsigned int     CLKEN_ATVIN_VD:1;
unsigned int     CLKEN_ATVIN_IFD:1;
unsigned int     CLKEN_OSDCOMP:1;
unsigned int     CLKEN_APLL_ADC:1;
unsigned int     CLKEN_IF_DEMOD:1;
unsigned int     CLKEN_DISP2TVE:1;
unsigned int     CLKEN_BISTREG:1;
unsigned int     CLKEN_VBIS0:1;
unsigned int     CLKEN_AUDIO_DAAD_128FS:1;
unsigned int     CLKEN_AUDIO_DAAD_256FS:1;
unsigned int     CLKEN_AUDIO_PRE512FS:1;
unsigned int     CLKEN_IFADC:1;
unsigned int     CLKEN_AUDIO2_512FS:1;
unsigned int     CLKEN_AUDIO2_DAAD_256FS:1;
unsigned int     CLKEN_AUDIO2_DAAD_128FS:1;
unsigned int     CLKEN_PADMUX:1;
unsigned int     CLKEN_DTV_DEMOD:1;
unsigned int     clk_en_akl:1;
unsigned int     clk_en_dsc:1;
unsigned int     clk_en_sce:1;
unsigned int     clk_en_kt:1;
unsigned int     CLKEN_DDC:1;
unsigned int     CLKEN_VODMA:1;
unsigned int     CLKEN_DISPIM:1;
unsigned int     CLKEN_DISP:1;
unsigned int     CLKEN_PLLREG:1;
unsigned int     clk_en_kcpu:1;
unsigned int     clk_en_sb2:1;
}SYS_GROUP1_CK_EN;

typedef struct 
{
unsigned int     reserved_0:5;
unsigned int     ve_rif_use_p2clk:1;
unsigned int     EPI_DBG_CLKSEL:1;
unsigned int     EPI_DIV_CLKSEL:2;
unsigned int     reserved_1:5;
unsigned int     ATVIN_CLK_SEL:1;
unsigned int     ATVIN_VD_CLK_SEL:1;
unsigned int     ATVIN_VDADC_TVE_CLK_SEL:1;
unsigned int     reserved_2:6;
unsigned int     VDEC_X27_CLKSEL:1;
unsigned int     reserved_3:2;
unsigned int     VBIS0_YPPSEL:1;
unsigned int     INV_VBIS0_CLK:1;
unsigned int     reserved_4:3;
unsigned int     sclk_sel:1;
}SYS_GROUP1_CK_SEL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     write_en5:1;
unsigned int     clk_tve_p_vo_clk_sel2:1;
unsigned int     write_en4:1;
unsigned int     clk_tve_p_vo_clk_sel:1;
unsigned int     write_en3:1;
unsigned int     hdmi_phy_ckinv:1;
unsigned int     write_en2:1;
unsigned int     reserved_1:2;
unsigned int     dac2_ckinv:1;
unsigned int     dac1_ckinv:1;
unsigned int     write_en1:1;
unsigned int     tveck_mix_sel:1;
}SYS_TVE_CK_SEL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     write_en2:1;
unsigned int     dac2_div:5;
unsigned int     write_en1:1;
unsigned int     dac1_div:5;
}SYS_DISP_PLL_DIV;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     write_en11:1;
unsigned int     hdmi_deep_clk_sel:1;
unsigned int     write_en10:1;
unsigned int     tve_i_div:2;
unsigned int     write_en9:1;
unsigned int     hdmi_tmds_div:2;
unsigned int     write_en8:1;
unsigned int     sel_plldisp_clk2:1;
unsigned int     write_en7:1;
unsigned int     sel_pllhdmi_clk:1;
unsigned int     write_en6:1;
unsigned int     hdmi_pxl_repeat:1;
unsigned int     write_en5:1;
unsigned int     hdmi_phy_clk_sel:1;
unsigned int     write_en4:1;
unsigned int     hdmi_div:3;
unsigned int     write_en3:1;
unsigned int     tve_div:4;
}SYS_DISP_PLL_DIV2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     reg_hdmi_tmds_div:2;
unsigned int     reg_tve_hdmi_div_sel:2;
unsigned int     reg_dac1_clk_sel:2;
unsigned int     reg_tve_pclk_sel:2;
unsigned int     reg_dac2_clk_sel:2;
unsigned int     reg_tve_iclk_sel:2;
unsigned int     reg_dac1_phy_clk_inv:1;
unsigned int     reg_dac2_phy_clk_inv:1;
}SYS_DISP_PLL_DIV3;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     audio_use_sysclk:1;
}SYS_AUDIO_CLK_CTL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     scpu_freq_sel:2;
unsigned int     vcpu_freq_sel:2;
unsigned int     acpu_freq_sel:2;
unsigned int     ddr_freq_sel:2;
unsigned int     bus_freq_sel:1;
}SYS_PLL_DIV;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     nf_div:3;
}SYS_NF_CKSEL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     nds_sc_div:3;
}SYS_NDS_SC_CKSEL;

typedef struct 
{
unsigned int     write_en3:1;
unsigned int     cremmc_clk_sel:1;
unsigned int     reserved_0:22;
unsigned int     write_en2:1;
unsigned int     emmc_div:3;
unsigned int     write_en1:1;
unsigned int     cr_div:3;
}SYS_CR_CKSEL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     DTV_DEMOD_MULTI_REQ_DISABLE:1;
unsigned int     reserved_1:1;
unsigned int     AUD_DTV_FREQ_SEL:3;
}SYS_CLKDIV;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     SCPU_WD_EN:1;
unsigned int     reserved_1:4;
unsigned int     SCPU_WD_CNT:12;
}SYS_ARM_WD;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     ATV_ISO_EN:1;
unsigned int     reserved_1:1;
unsigned int     ATV_STR_STATUS:1;
unsigned int     reserved_2:1;
unsigned int     ATV_STR_POW:1;
unsigned int     reserved_3:3;
unsigned int     DTV_ISO_EN:1;
unsigned int     reserved_4:1;
unsigned int     DTV_STR_STATUS:1;
unsigned int     reserved_5:1;
unsigned int     DTV_STR_POW:1;
}SYS_POWER_CTRL0;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     PLL27X_WDOUT:1;
unsigned int     REG_PLLVODMA_WDOUT:1;
unsigned int     PLLGPU_WDOUT:1;
unsigned int     PLLGPU_WDOUT_2:1;
unsigned int     PLLAUD_STATUS:1;
unsigned int     PLL512FS_WDOUT:1;
unsigned int     REG_PLLBUSH_WDOUT:1;
unsigned int     reserved_1:1;
unsigned int     PLLDIF_WDOUT:1;
unsigned int     PLLBUS2_WDOUT:1;
unsigned int     PLLETN_WDOUT:1;
unsigned int     reserved_2:1;
unsigned int     REG_PLLBUS_WDOUT:1;
unsigned int     PLLDISP_WDOUT:1;
unsigned int     reserved_3:1;
unsigned int     PLLDDS_WDOUT:1;
unsigned int     REG_PLLVCPU_WDOUT:1;
unsigned int     REG_PLLACPU_WDOUT:1;
unsigned int     REG_PLLSCPU_WDOUT:1;
}SYS_PLL_WDOUT;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     TM_ENABLE:1;
unsigned int     TM_DATA_VALID:1;
unsigned int     TM_DATA_SAMPLED:1;
unsigned int     TM_REVERSE_CMP_OUT:1;
unsigned int     reserved_1:1;
unsigned int     TM_DATA_OUT:7;
unsigned int     TM_PWRON_DLY:16;
}SYS_TM_CTRL0;

typedef struct 
{
unsigned int     TM_COMPARE_DLY:16;
unsigned int     TM_SAMPLE_DLY:16;
}SYS_TM_CTRL1;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     REG_TM_SBG:3;
unsigned int     REG_TM_SOS:3;
unsigned int     REG_TM_SINL:2;
unsigned int     REG_TM_POW:1;
unsigned int     reserved_1:1;
}SYS_TM_CTRL2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35d5_speed_en:1;
unsigned int     dss_c35d5_data_in:20;
unsigned int     dss_c35d5_wire_sel:1;
unsigned int     dss_c35d5_ro_sel:3;
unsigned int     dss_c35d5_dss_rst_n:1;
}SYS_DSS00_DSS_GPU0;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35d5_wsort_go:1;
unsigned int     dss_c35d5_count_out:20;
unsigned int     dss_c35d5_ready:1;
}SYS_DSS01_DSS_GPU0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35d5_dbgo:16;
}SYS_DSS02_DSS_GPU0;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35_speed_en:1;
unsigned int     dss_c35_data_in:20;
unsigned int     dss_c35_wire_sel:1;
unsigned int     dss_c35_ro_sel:3;
unsigned int     dss_c35_dss_rst_n:1;
}SYS_DSS03_DSS_GPU1;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35_wsort_go:1;
unsigned int     dss_c35_count_out:20;
unsigned int     dss_c35_ready:1;
}SYS_DSS04_DSS_GPU1;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35_dbgo:16;
}SYS_DSS05_DSS_GPU1;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35d5_speed_en:1;
unsigned int     dss_c35d5_data_in:20;
unsigned int     dss_c35d5_wire_sel:1;
unsigned int     dss_c35d5_ro_sel:3;
unsigned int     dss_c35d5_dss_rst_n:1;
}SYS_DSS06_DSS_GPU2;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35d5_wsort_go:1;
unsigned int     dss_c35d5_count_out:20;
unsigned int     dss_c35d5_ready:1;
}SYS_DSS07_DSS_GPU2;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35d5_dbgo:16;
}SYS_DSS08_DSS_GPU2;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35_speed_en:1;
unsigned int     dss_c35_data_in:20;
unsigned int     dss_c35_wire_sel:1;
unsigned int     dss_c35_ro_sel:3;
unsigned int     dss_c35_dss_rst_n:1;
}SYS_DSS09_DSS_GPU3;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35_wsort_go:1;
unsigned int     dss_c35_count_out:20;
unsigned int     dss_c35_ready:1;
}SYS_DSS10_DSS_GPU3;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35_dbgo:16;
}SYS_DSS11_DSS_GPU3;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35_speed_en:1;
unsigned int     dss_c35_data_in:20;
unsigned int     dss_c35_wire_sel:1;
unsigned int     dss_c35_ro_sel:3;
unsigned int     dss_c35_dss_rst_n:1;
}SYS_DSS12_DSS_TOP0;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35_wsort_go:1;
unsigned int     dss_c35_count_out:20;
unsigned int     dss_c35_ready:1;
}SYS_DSS13_DSS_TOP0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35_dbgo:16;
}SYS_DSS14_DSS_TOP0;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35_speed_en:1;
unsigned int     dss_c35_data_in:20;
unsigned int     dss_c35_wire_sel:1;
unsigned int     dss_c35_ro_sel:3;
unsigned int     dss_c35_dss_rst_n:1;
}SYS_DSS15_DSS_TVSB10;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35_wsort_go:1;
unsigned int     dss_c35_count_out:20;
unsigned int     dss_c35_ready:1;
}SYS_DSS16_DSS_TVSB10;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35_dbgo:16;
}SYS_DSS17_DSS_TVSB10;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35d5_speed_en:1;
unsigned int     dss_c35d5_data_in:20;
unsigned int     dss_c35d5_wire_sel:1;
unsigned int     dss_c35d5_ro_sel:3;
unsigned int     dss_c35d5_dss_rst_n:1;
}SYS_DSS18_DSS_TVSB11;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35d5_wsort_go:1;
unsigned int     dss_c35d5_count_out:20;
unsigned int     dss_c35d5_ready:1;
}SYS_DSS19_DSS_TVSB11;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35d5_dbgo:16;
}SYS_DSS20_DSS_TVSB11;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     dss_c35_speed_en:1;
unsigned int     dss_c35_data_in:20;
unsigned int     dss_c35_wire_sel:1;
unsigned int     dss_c35_ro_sel:3;
unsigned int     dss_c35_dss_rst_n:1;
}SYS_DSS21_DSS_TVSB30;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     dss_c35_wsort_go:1;
unsigned int     dss_c35_count_out:20;
unsigned int     dss_c35_ready:1;
}SYS_DSS22_DSS_TVSB30;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     dss_c35_dbgo:16;
}SYS_DSS23_DSS_TVSB30;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     csm0_data_sel:2;
unsigned int     csm0_addr:4;
unsigned int     csm0_read_en:1;
unsigned int     csm0_hold:1;
unsigned int     csm0_acc_mode:1;
unsigned int     csm0_in_sel:2;
unsigned int     csm0_csm_en:1;
unsigned int     csm0_rstn:1;
}SYS_CSM00_CSM_DDR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     csm0_ready:1;
}SYS_CSM01_CSM_DDR;

typedef struct 
{
unsigned int     csm0_data:32;
}SYS_CSM02_CSM_DDR;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     csm1_data_sel:2;
unsigned int     csm1_addr:4;
unsigned int     csm1_read_en:1;
unsigned int     csm1_hold:1;
unsigned int     csm1_acc_mode:1;
unsigned int     csm1_in_sel:2;
unsigned int     csm1_csm_en:1;
unsigned int     csm1_rstn:1;
}SYS_CSM03_CSM_DDR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     csm1_ready:1;
}SYS_CSM04_CSM_DDR;

typedef struct 
{
unsigned int     csm1_data:32;
}SYS_CSM05_CSM_DDR;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     rme_rom:1;
unsigned int     rm_rom:4;
unsigned int     rme_800:1;
unsigned int     rm_800:4;
unsigned int     rme_600:1;
unsigned int     rm_600:4;
unsigned int     rme_400:1;
unsigned int     rm_400:4;
unsigned int     rme_300:1;
unsigned int     rm_300:4;
unsigned int     rme_200:1;
unsigned int     rm_200:4;
}SYS_CHIP_SRAM_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     resume_cycle_sel:1;
}SYS_CHIP_MISC_CTRL;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     clk_na_fail:1;
unsigned int     reserved_1:5;
unsigned int     testmode:1;
unsigned int     nf_sel:1;
unsigned int     sf_sel:1;
}SYS_CHIP_INFO2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     write_en2:1;
unsigned int     dds_rstn:1;
}SYS_APS_CTL;

typedef struct 
{
unsigned int     kcpu_boot_info:32;
}SYS_PWDN_CTRL;

typedef struct 
{
unsigned int     acpu_boot_info:32;
}SYS_PWDN_CTRL2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     kcpu_boot_info_valid:1;
unsigned int     write_en1:1;
unsigned int     kcpu_sw_rst:1;
}SYS_PWDN_CTRL3;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     acpu_boot_info_valid:1;
}SYS_PWDN_CTRL4;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     dac_test:1;
unsigned int     write_en1:1;
unsigned int     scpu_config_done:1;
}SYS_AT_SPEED;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en2:1;
unsigned int     etn_phy_gpio_en:1;
unsigned int     write_en1:1;
unsigned int     etn_phy_125m_en:1;
}SYS_ANA_CTRL;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     demod_i2c_saddr:1;
unsigned int     demod_i2c_sel:1;
unsigned int     tp2_dm_sel:1;
unsigned int     tp1_dm_sel:1;
unsigned int     tp0_dm_sel:1;
}SYS_TP_DEMOD_CTRL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sf_en:1;
}SYS_CONTROL0;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     akl_busy:1;
}SYS_SECURITY_ST;

typedef struct 
{
unsigned int     Rvd1:32;
}SYS_DMY2;

typedef struct 
{
unsigned int     bus_ssc_sse:1;
unsigned int     bus_ssc_ckinv:1;
unsigned int     bus_ssc_sss:6;
unsigned int     reserved_0:1;
unsigned int     bus_ssc_ssn:7;
unsigned int     bus_ssc_ssfpv:8;
unsigned int     reserved_1:6;
unsigned int     bus_ssc_stms:2;
}SYS_BUS_PLL_SSC;

typedef struct 
{
unsigned int     dcsb_ssc_sse:1;
unsigned int     dcsb_ssc_ckinv:1;
unsigned int     dcsb_ssc_sss:6;
unsigned int     reserved_0:1;
unsigned int     dcsb_ssc_ssn:7;
unsigned int     dcsb_ssc_ssfpv:8;
unsigned int     reserved_1:6;
unsigned int     dcsb_ssc_stms:2;
}SYS_DCSB_PLL_SSC;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     REG_PLLSCPU_N:2;
unsigned int     REG_PLLSCPU_M:8;
unsigned int     REG_PLLSCPU_IP:3;
unsigned int     REG_PLLSCPU_O:2;
unsigned int     REG_PLLSCPU_WDRST:1;
unsigned int     REG_PLLSCPU_WDSET:1;
unsigned int     reserved_1:4;
unsigned int     REG_PLLSCPU_TST:1;
}SYS_PLL_SCPU1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     REG_PLLSCPU_RS:3;
unsigned int     reserved_1:2;
unsigned int     REG_PLLSCPU_CS:2;
unsigned int     REG_PLLSCPU_CP:1;
unsigned int     REG_PLLSCPU_OEB:1;
unsigned int     PLLSCPU_RSTB:1;
unsigned int     REG_PLLSCPU_POW:1;
}SYS_PLL_SCPU2;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     REG_PLLACPU_N:2;
unsigned int     REG_PLLACPU_M:7;
unsigned int     REG_PLLACPU_IP:3;
unsigned int     REG_PLLACPU_O:2;
unsigned int     REG_PLLACPU_WDRST:1;
unsigned int     REG_PLLACPU_WDSET:1;
unsigned int     reserved_1:4;
unsigned int     REG_PLLACPU_TST:1;
}SYS_PLL_ACPU1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     REG_PLLACPU_RS:3;
unsigned int     reserved_1:2;
unsigned int     REG_PLLACPU_CS:2;
unsigned int     reserved_2:1;
unsigned int     REG_PLLACPU_OEB:1;
unsigned int     PLLACPU_RSTB:1;
unsigned int     REG_PLLACPU_POW:1;
}SYS_PLL_ACPU2;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     REG_PLLVCPU_IP:3;
unsigned int     REG_PLLVCPU_N:2;
unsigned int     REG_PLLVCPU_M:7;
unsigned int     reserved_1:2;
unsigned int     REG_PLLVCPU_O:2;
unsigned int     REG_PLLVCPU_WDRST:1;
unsigned int     REG_PLLVCPU_WDSET:1;
unsigned int     reserved_2:4;
unsigned int     REG_PLLVCPU_TST:1;
}SYS_PLL_VCPU1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     REG_PLLVCPU_RS:3;
unsigned int     reserved_1:2;
unsigned int     REG_PLLVCPU_CS:2;
unsigned int     reserved_2:1;
unsigned int     REG_PLLVCPU_OEB:1;
unsigned int     PLLVCPU_RSTB:1;
unsigned int     REG_PLLVCPU_POW:1;
}SYS_PLL_VCPU2;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_PLLBUS_O:2;
unsigned int     reserved_1:1;
unsigned int     REG_PLLBUS_N:2;
unsigned int     REG_PLLBUS_M:7;
unsigned int     REG_PLLBUS_IP:3;
unsigned int     reserved_2:1;
unsigned int     REG_PLLBUS_RS:3;
unsigned int     reserved_3:1;
unsigned int     REG_PLLBUS_CS:2;
unsigned int     reserved_4:1;
unsigned int     REG_PLLBUS_CP:2;
unsigned int     REG_PLLBUS_R3:3;
unsigned int     REG_PLLBUS_C3:2;
}SYS_PLL_BUS1;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     write_en5:1;
unsigned int     REG_PLLBUS_PI_RL:2;
unsigned int     REG_PLLBUS_PI_RS:2;
unsigned int     REG_PLLBUS_PI_BIAS:2;
unsigned int     write_en4:1;
unsigned int     REG_PLLBUS_WDMODE:2;
unsigned int     reserved_1:2;
unsigned int     write_en3:1;
unsigned int     REG_PLLBUS_FUPDN:1;
unsigned int     REG_PLLBUS_PSEN:1;
unsigned int     REG_PLLBUS_VCORB:1;
unsigned int     write_en1:1;
unsigned int     REG_PLLBUS_TST:1;
unsigned int     REG_PLLBUS_PSTST:1;
}SYS_PLL_BUS2;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLBUS_OEB:1;
unsigned int     REG_PLLBUS_RSTB:1;
unsigned int     REG_PLLBUS_POW:1;
}SYS_PLL_BUS3;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_PLLBUS_O_H:2;
unsigned int     reserved_1:1;
unsigned int     REG_PLLBUS_N_H:2;
unsigned int     REG_PLLBUS_M_H:7;
unsigned int     REG_PLLBUS_IP_H:3;
unsigned int     reserved_2:1;
unsigned int     REG_PLLBUS_RS_H:3;
unsigned int     reserved_3:1;
unsigned int     REG_PLLBUS_CS_H:2;
unsigned int     reserved_4:1;
unsigned int     REG_PLLBUS_CP_H:2;
unsigned int     REG_PLLBUS_R3_H:3;
unsigned int     REG_PLLBUS_C3_H:2;
}SYS_PLL_DCSB1;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     write_en5:1;
unsigned int     REG_PLLBUS_PI_RL_H:2;
unsigned int     REG_PLLBUS_PI_RS_H:2;
unsigned int     REG_PLLBUS_PI_BIAS_H:2;
unsigned int     write_en4:1;
unsigned int     REG_PLLBUS_WDMODE_H:2;
unsigned int     reserved_1:2;
unsigned int     write_en3:1;
unsigned int     REG_PLLBUS_FUPDN_H:1;
unsigned int     REG_PLLBUS_PSEN_H:1;
unsigned int     REG_PLLBUS_VCORB_H:1;
unsigned int     write_en1:1;
unsigned int     REG_PLLBUS_TST_H:1;
unsigned int     REG_PLLBUS_PSTST_H:1;
}SYS_PLL_DCSB2;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     REG_PLLBUS_OEB_H:1;
unsigned int     REG_PLLBUS_RSTB_H:1;
unsigned int     REG_PLLBUS_POW_H:1;
}SYS_PLL_DCSB3;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     REG_PLLVODMA_N:2;
unsigned int     reserved_1:1;
unsigned int     REG_PLLVODMA_M:7;
unsigned int     REG_PLLVODMA_IP:3;
unsigned int     REG_PLLVODMA_O:2;
unsigned int     REG_PLLVODMA_WDSET:1;
unsigned int     REG_PLLVODMA_WDRST:1;
unsigned int     REG_PLLVODMA_CS:2;
unsigned int     REG_PLLVODMA_RS:3;
}SYS_PLL_VODMA1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     REG_PLLVODMA_TST:1;
unsigned int     REG_PLLVODMA_OEB:1;
unsigned int     REG_PLLVODMA_RSTB:1;
unsigned int     REG_PLLVODMA_POW:1;
}SYS_PLL_VODMA2;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     REG_PLLCPU_REG:2;
unsigned int     REG_PLLBUS_RESER:4;
unsigned int     reserved_1:2;
unsigned int     REG_PLLBUS_REG:2;
unsigned int     reserved_2:2;
unsigned int     REG_PLLTST_DIV:2;
unsigned int     reserved_3:3;
unsigned int     REG_PLLTST_SEL:5;
}SYS_PLLBUS_TST;

typedef struct 
{
unsigned int     REG_PLLDDS_N:2;
unsigned int     REG_PLLDDS_M:7;
unsigned int     REG_PLLDDS_IP:3;
unsigned int     REG_PLLDDS_RS:3;
unsigned int     REG_PLLDDS_CS:2;
unsigned int     REG_PLLDDS_CP:2;
unsigned int     REG_PLLDDS_R3:3;
unsigned int     REG_PLLDDS_C3:2;
unsigned int     REG_PLLDDS_PI_RL:2;
unsigned int     REG_PLLDDS_PI_RS:2;
unsigned int     REG_PLLDDS_PI_BIAS:2;
unsigned int     REG_PLLDDS_WDMODE:2;
}SYS_PLL_DISP_SD1;

typedef struct 
{
unsigned int     REG_PLLDDS_O:2;
unsigned int     reserved_0:2;
unsigned int     psaud_1a_phase_sel:1;
unsigned int     psaud_2a_phase_sel:1;
unsigned int     reserved_1:1;
unsigned int     pcr_a_smooth_en:1;
unsigned int     reserved_2:1;
unsigned int     pcr_a_phase_sel:1;
unsigned int     reserved_3:1;
unsigned int     pcr_a_ctl_en:1;
unsigned int     reserved_4:1;
unsigned int     REG_PLLDDS_FUPDN:1;
unsigned int     reserved_5:1;
unsigned int     REG_PLLDDS_DDSEN:1;
unsigned int     reserved_6:1;
unsigned int     REG_PLLDDS_VCORB:1;
unsigned int     reserved_7:1;
unsigned int     REG_PLLDDS_TST:1;
unsigned int     REG_PLLDDS_PSTST:1;
unsigned int     reserved_8:1;
unsigned int     reserved_9:10;
}SYS_PLL_DISP_SD2;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     reserved_1:1;
unsigned int     REG_PSAUD1_FUPDN:1;
unsigned int     REG_PSAUD1_DIV:1;
unsigned int     reserved_2:1;
unsigned int     REG_PSAUD1_TST:1;
unsigned int     REG_PSAUD1_PSEN:1;
unsigned int     reserved_3:1;
unsigned int     REG_PSAUD2_FUPDN:1;
unsigned int     REG_PSAUD2_DIV:1;
unsigned int     REG_PSAUD2_TST:1;
unsigned int     REG_PSAUD2_PSEN:1;
unsigned int     reserved_4:16;
unsigned int     REG_PSAUD1_OEB:1;
unsigned int     REG_PSAUD1_RSTB:1;
unsigned int     REG_PSAUD2_OEB:1;
unsigned int     REG_PSAUD2_RSTB:1;
}SYS_PLL_DISP_SD3;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     REG_PLLDDS_O:2;
unsigned int     reserved_1:1;
unsigned int     REG_PLLDDS_OEB:1;
unsigned int     REG_PLLDDS_RSTB:1;
unsigned int     REG_PLLDDS_POW:1;
}SYS_PLL_DISP_SD4;

typedef struct 
{
unsigned int     PLLDDS_PCR_ACC:16;
unsigned int     PLLDDS_PCR_OVERFLOW:16;
}SYS_PLL_DISP_SD5;

typedef struct 
{
unsigned int     n_PCR_A_N_nxt:16;
unsigned int     PCR_A_N_nxt:16;
}SYS_PLL_DISP_SD6;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     PCR_A_N_nxt_add:8;
unsigned int     PCR_A_N_nxt_add_period:16;
}SYS_PLL_DISP_SD7;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     DPLL_M:8;
unsigned int     reserved_1:5;
unsigned int     DPLL_N:3;
unsigned int     reserved_2:1;
unsigned int     DPLL_IP:3;
unsigned int     reserved_3:1;
unsigned int     DPLL_RS:3;
unsigned int     DPLL_CP:2;
unsigned int     DPLL_CS:2;
}SYS_PLL_DISP1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     DPLL_LDOSEL:2;
unsigned int     reserved_1:3;
unsigned int     DPLL_RESER:1;
unsigned int     reserved_2:2;
unsigned int     DPLL_FUPDN:1;
unsigned int     DPLL_STOP:1;
unsigned int     reserved_3:2;
unsigned int     DPLL_RESERVE:1;
unsigned int     DPLL_BPPHS:1;
unsigned int     reserved_4:1;
unsigned int     DPLL_BPN:1;
unsigned int     DPLL_O:2;
unsigned int     reserved_5:5;
unsigned int     DPLL_RSTB:1;
unsigned int     DPLL_WDRST:1;
unsigned int     DPLL_WDSET:1;
unsigned int     DPLL_CLKSEL:1;
unsigned int     DPLL_FREEZE:1;
unsigned int     DPLL_VCORSTB:1;
unsigned int     DPLL_POW:1;
}SYS_PLL_DISP2;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     PLT_CMU_MACPLL_DIVM:3;
unsigned int     reserved_1:1;
unsigned int     PLT_CMU_MACPLL_DIVN:3;
}SYS_PLL_VBY1_MAC1;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     REG_TV_WDMODE:2;
unsigned int     REG_TVKVCO:1;
unsigned int     REG_TV_CP:2;
unsigned int     REG_TV_CS:2;
unsigned int     REG_TX_CK5XP_DUTY:2;
unsigned int     REG_TX_CK5XN_DUTY:2;
unsigned int     REG_TX_AMP:4;
unsigned int     REG_TX_IBIAS:2;
unsigned int     REG_TX_EMPH:3;
unsigned int     REG_TX_EN_EMPH:1;
unsigned int     REG_TX_FORCE_VC:1;
unsigned int     REG_TX_SET_VC:2;
unsigned int     REG_TX_PLL_EDGE:1;
unsigned int     REG_TX_PLL_ICP:3;
unsigned int     REG_TX_PLL_RS:3;
}SYS_TMDS_SCR1;

typedef struct 
{
unsigned int     reserved_0:2;
unsigned int     REG_TX_PDRV_ISEL:2;
unsigned int     REG_TX_PLL_CP:2;
unsigned int     REG_TX_PLL_CS:2;
unsigned int     REG_TX_PLL_KVCO:1;
unsigned int     REG_TX_PLL_PU:1;
unsigned int     REG_TX_PU:4;
unsigned int     REG_TX_DRIVER:2;
unsigned int     REG_TX_SLEW:2;
unsigned int     REG_TX_TST_EN:1;
unsigned int     REG_TX_VGATE:3;
unsigned int     REG_PLL_TST_EN:1;
unsigned int     REG_TST_SEL:2;
unsigned int     REG_TX_BYPASS_PLL:1;
unsigned int     REG_TX_RT_EN:1;
unsigned int     REG_TX_RT_SEL:2;
unsigned int     REG_PLL_VCO_SCALE:2;
unsigned int     REG_BYPASS_DIN:1;
}SYS_TMDS_SCR2;

typedef struct 
{
unsigned int     reserved_0:1;
unsigned int     REG_TX_PLL_WDMODE:2;
unsigned int     REG_TX_V1P05_SEL:2;
unsigned int     REG_LDO_CCO_PU:1;
unsigned int     REG_LDO_CCO_VSEL:2;
unsigned int     REG_LDO_PLL_PU:1;
unsigned int     REG_LDO_PLL_VSEL:3;
unsigned int     REG_EN_MHL:1;
unsigned int     REG_FORCE_RXSENSE:1;
unsigned int     REG_RXSENSE:2;
unsigned int     REG_MHL_DIV:1;
unsigned int     REG_MHL_VCM:2;
unsigned int     REG_DIFF_RT_EN:1;
unsigned int     REG_CEC_ENB:1;
unsigned int     REG_CEC_RSEL:3;
unsigned int     REG_CEC_RPU_EN:1;
unsigned int     REG_HPD_EN:1;
unsigned int     REG_CABLE_DET_EN:1;
unsigned int     REG_LDO_TMDS_PU:1;
unsigned int     REG_LDO_TMDS_VSEL:3;
unsigned int     REG_LDO_TMDS_CAPSEL:1;
}SYS_TMDS_SCR3;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     REG_TV_PRE_DIV:1;
unsigned int     REG_TV_LDIV:6;
unsigned int     REG_TV_PSTEP_EN:1;
unsigned int     REG_TV_PSTEP:3;
unsigned int     REG_HDMI_CK_EN:1;
unsigned int     REG_PIXEL_DIV3:1;
unsigned int     REG_PIXEL_DIV5:1;
unsigned int     REG_PIXEL_DIV16:3;
unsigned int     REG_TMDS_DIV5:1;
unsigned int     REG_TMDS_DIV16:3;
}SYS_TVPLL_CTRL1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     REG_SEL_REF_CLK27:1;
unsigned int     REG_RESERVE:16;
unsigned int     REG_TV_PLL_PU:1;
unsigned int     REG_TV_ICP:3;
unsigned int     REG_TV_RS:3;
unsigned int     REG_TV_BYPASS_PLL:1;
unsigned int     REG_TV_FORCE_VC:1;
unsigned int     REG_TV_SET_VC:2;
unsigned int     REG_TV_TST_EN:1;
}SYS_TVPLL_CTRL2;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     reg_pcr_smooth_en:1;
unsigned int     reserved_1:1;
unsigned int     reg_pcr_phase_sel:1;
unsigned int     reserved_2:1;
unsigned int     reg_pcr_ctl_en:1;
unsigned int     reserved_3:1;
unsigned int     REG_PLLDDS_FUPDN:1;
unsigned int     REG_PLLDDS_DDSEN:1;
unsigned int     reserved_4:4;
unsigned int     reg_shuffle_en:1;
unsigned int     REG_TVPLL_FUPDN:1;
unsigned int     REG_TVPLL_RESERVE:1;
unsigned int     REG_TVPLL_STOP:1;
unsigned int     reserved_5:9;
}SYS_TVPLL_CTRL3;

typedef struct 
{
unsigned int     reg_PLLDDS_PCR_ACC:16;
unsigned int     reg_PLLDDS_PCR_OVERFLOW:16;
}SYS_TVPLL_CTRL4;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     REG_PCR_A_N_nxt_add:8;
unsigned int     REG_PCR_A_N_nxt_add_period:16;
}SYS_TVPLL_CTRL5;

typedef struct 
{
unsigned int     reg_n_PCR_A_N_nxt:16;
unsigned int     reg_PCR_A_N_nxt:16;
}SYS_TVPLL_CTRL6;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     REG_PLLGPU_N:2;
unsigned int     REG_PLLGPU_M:7;
unsigned int     REG_PLLGPU_IP:3;
unsigned int     REG_PLLGPU_K:2;
unsigned int     REG_PLLGPU_WDMODE:2;
unsigned int     reserved_1:4;
unsigned int     REG_PLLGPU_TST:1;
}SYS_PLL_GPU1;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     REG_PLLGPU_RS:3;
unsigned int     reserved_1:2;
unsigned int     REG_PLLGPU_CS:2;
unsigned int     reserved_2:1;
unsigned int     REG_PLLGPU_OEB:1;
unsigned int     REG_PLLGPU_RSTB:1;
unsigned int     REG_PLLGPU_POW:1;
}SYS_PLL_GPU2;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     REG_PLLGPU_N_2:2;
unsigned int     REG_PLLGPU_M_2:7;
unsigned int     REG_PLLGPU_IP_2:3;
unsigned int     REG_PLLGPU_K_2:2;
unsigned int     REG_PLLGPU_WDMODE_2:2;
unsigned int     reserved_1:4;
unsigned int     REG_PLLGPU_TST_2:1;
}SYS_PLL_GPU3;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     REG_PLLGPU_RS_2:3;
unsigned int     reserved_1:2;
unsigned int     REG_PLLGPU_CS_2:2;
unsigned int     reserved_2:1;
unsigned int     REG_PLLGPU_OEB_2:1;
unsigned int     REG_PLLGPU_RSTB_2:1;
unsigned int     REG_PLLGPU_POW_2:1;
}SYS_PLL_GPU4;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     REG_TRNG_RES:2;
unsigned int     REG_TRNG_GAIN:2;
unsigned int     REG_TRNG_FS:2;
unsigned int     REG_TRNG_DIV:2;
unsigned int     REG_TRNG_D:4;
unsigned int     reserved_1:2;
unsigned int     REG_TRNG_TST:1;
unsigned int     REG_TRNG_POW:1;
}SYS_TRNG1;

typedef struct 
{
unsigned int     crt_dbg1_div_sel:2;
unsigned int     crt_dbg0_div_sel:2;
unsigned int     reserved_0:15;
unsigned int     crt_dbg_en:1;
unsigned int     crt_dbg_sel0:6;
unsigned int     crt_dbg_sel1:6;
}SYS_CRT_DEBUG;

typedef struct 
{
unsigned int     dummy_reg:32;
}SYS_DUMMY;

typedef struct 
{
unsigned int     sb2_rom_bist_en:1;
unsigned int     reserved_0:17;
unsigned int     sce_bist_mode:1;
unsigned int     tp_bist_en:1;
unsigned int     reserved_1:2;
unsigned int     hdmi0_bist_en:1;
unsigned int     hdmi1_bist_en:1;
unsigned int     vde_bist_en:1;
unsigned int     dc3_bist_en:1;
unsigned int     dc2_bist_en:1;
unsigned int     ae_rom_bist_en:1;
unsigned int     ae_bist_en:1;
unsigned int     cr_nf1_bist_en:1;
unsigned int     cp_bist_en:1;
unsigned int     write_data:1;
}SYS_CRT_BIST_EN1;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     ve17_bist_en:1;
unsigned int     ve16_bist_en:1;
unsigned int     ve15_bist_en:1;
unsigned int     ve14_bist_en:1;
unsigned int     ve13_bist_en:1;
unsigned int     ve12_bist_en:1;
unsigned int     ve11_bist_en:1;
unsigned int     ve10_bist_en:1;
unsigned int     ve9_bist_en:1;
unsigned int     ve8_bist_en:1;
unsigned int     ve7_bist_en:1;
unsigned int     ve6_bist_en:1;
unsigned int     ve5_bist_en:1;
unsigned int     ve4_bist_en:1;
unsigned int     ve3_bist_en:1;
unsigned int     ve2_bist_en:1;
unsigned int     ve1_bist_en:1;
unsigned int     write_data:1;
}SYS_CRT_BIST_EN2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     etn2_bist_en:1;
unsigned int     reserved_1:2;
unsigned int     md_bist_en:1;
unsigned int     usb2_bist_en:1;
unsigned int     usb1_bist_en:1;
unsigned int     reserved_2:2;
unsigned int     kcpu1_bist_en:1;
unsigned int     reserved_3:2;
unsigned int     vcpu_bist_en:1;
unsigned int     acpu_bist_en:1;
unsigned int     write_data:1;
}SYS_CRT_BIST_EN3;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     sce_drf_bist_mode:1;
unsigned int     tp_drf_bist_en:1;
unsigned int     reserved_1:2;
unsigned int     hdmi0_drf_bist_en:1;
unsigned int     hdmi1_drf_bist_en:1;
unsigned int     vde_drf_bist_en:1;
unsigned int     dc3_drf_bist_en:1;
unsigned int     dc2_drf_bist_en:1;
unsigned int     reserved_2:2;
unsigned int     cr_nf1_drf_bist_en:1;
unsigned int     cp_drf_bist_en:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_BIST_EN1;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     ve17_drf_bist_en:1;
unsigned int     ve16_drf_bist_en:1;
unsigned int     ve15_drf_bist_en:1;
unsigned int     ve14_drf_bist_en:1;
unsigned int     ve13_drf_bist_en:1;
unsigned int     ve12_drf_bist_en:1;
unsigned int     ve11_drf_bist_en:1;
unsigned int     ve10_drf_bist_en:1;
unsigned int     ve9_drf_bist_en:1;
unsigned int     ve8_drf_bist_en:1;
unsigned int     ve7_drf_bist_en:1;
unsigned int     ve6_drf_bist_en:1;
unsigned int     ve5_drf_bist_en:1;
unsigned int     ve4_drf_bist_en:1;
unsigned int     ve3_drf_bist_en:1;
unsigned int     ve2_drf_bist_en:1;
unsigned int     ve1_drf_bist_en:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_BIST_EN2;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     ae_drf_bist_en:1;
unsigned int     etn2_drf_bist_en:1;
unsigned int     reserved_1:2;
unsigned int     md_drf_bist_en:1;
unsigned int     usb2_drf_bist_en:1;
unsigned int     usb1_drf_bist_en:1;
unsigned int     reserved_2:2;
unsigned int     kcpu1_drf_bist_en:1;
unsigned int     reserved_3:2;
unsigned int     vcpu_drf_bist_en:1;
unsigned int     acpu_drf_bist_en:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_BIST_EN3;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     sce_drf_test_resume:1;
unsigned int     tp_drf_test_resume:1;
unsigned int     reserved_1:2;
unsigned int     hdmi0_drf_test_resume:1;
unsigned int     hdmi1_drf_test_resume:1;
unsigned int     vde_drf_test_resume:1;
unsigned int     dc3_drf_test_resume:1;
unsigned int     dc2_drf_test_resume:1;
unsigned int     reserved_2:2;
unsigned int     cr_nf1_drf_test_resume:1;
unsigned int     cp_drf_test_resume:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_TEST_RESUME1;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     ve17_drf_test_resume:1;
unsigned int     ve16_drf_test_resume:1;
unsigned int     ve15_drf_test_resume:1;
unsigned int     ve14_drf_test_resume:1;
unsigned int     ve13_drf_test_resume:1;
unsigned int     ve12_drf_test_resume:1;
unsigned int     ve11_drf_test_resume:1;
unsigned int     ve10_drf_test_resume:1;
unsigned int     ve9_drf_test_resume:1;
unsigned int     ve8_drf_test_resume:1;
unsigned int     ve7_drf_test_resume:1;
unsigned int     ve6_drf_test_resume:1;
unsigned int     ve5_drf_test_resume:1;
unsigned int     ve4_drf_test_resume:1;
unsigned int     ve3_drf_test_resume:1;
unsigned int     ve2_drf_test_resume:1;
unsigned int     ve1_drf_test_resume:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_TEST_RESUME2;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     ae_drf_test_resume:1;
unsigned int     etn2_drf_test_resume:1;
unsigned int     reserved_1:2;
unsigned int     md_drf_test_resume:1;
unsigned int     usb2_drf_test_resume:1;
unsigned int     usb1_drf_test_resume:1;
unsigned int     reserved_2:2;
unsigned int     kcpu1_drf_test_resume:1;
unsigned int     reserved_3:2;
unsigned int     vcpu_drf_test_resume:1;
unsigned int     acpu_drf_test_resume:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_TEST_RESUME3;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     vde_drf_start_pause:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_START_PAUSE1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     etn2_drf_start_pause:1;
unsigned int     vcpu_drf_start_pause:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_START_PAUSE3;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     kcpu_bisr_en:1;
unsigned int     vcpu_bisr_en:1;
unsigned int     acpu_bisr_en:1;
unsigned int     write_data:1;
}SYS_CRT_BISR_EN1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cp42k_bisr_rstn:1;
unsigned int     kcpu_bisr_rstn:1;
unsigned int     vcpu_bisr_rstn:1;
unsigned int     acpu_bisr_rstn:1;
unsigned int     write_data:1;
}SYS_CRT_BISR_RSTN1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cp42k_bisr_pwr_rstn:1;
unsigned int     kcpu_bisr_pwr_rstn:1;
unsigned int     vcpu_bisr_pwr_rstn:1;
unsigned int     acpu_bisr_pwr_rstn:1;
unsigned int     write_data:1;
}SYS_CRT_BISR_PWR_RSTN1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cp42k_bisr_hold_remap:1;
unsigned int     kcpu_bisr_hold_remap:1;
unsigned int     vcpu_bisr_hold_remap:1;
unsigned int     acpu_bisr_hold_remap:1;
unsigned int     write_data:1;
}SYS_CRT_BISR_HOLD_REMAP1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     spnr_bisr_remap:1;
unsigned int     reserved_1:1;
unsigned int     iuzd_bisr_remap:1;
unsigned int     ich1_bisr_sdnr_remap:1;
}SYS_CRT_BISR_HOLD_REMAP2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cp42k_bisr_second_run_en:1;
unsigned int     kcpu_bisr_second_run_en:1;
unsigned int     vcpu_bisr_second_run_en:1;
unsigned int     acpu_bisr_second_run_en:1;
unsigned int     write_data:1;
}SYS_CRT_BISR_2ND_RUN_EN1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cp42k_drf_bisr_en:1;
unsigned int     kcpu_drf_bisr_en:1;
unsigned int     vcpu_drf_bisr_en:1;
unsigned int     acpu_drf_bisr_en:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_BISR_EN1;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     cp42k_drf_bisr_test_resume:1;
unsigned int     kcpu_drf_bisr_test_resume:1;
unsigned int     vcpu_drf_bisr_test_resume:1;
unsigned int     acpu_drf_bisr_test_resume:1;
unsigned int     write_data:1;
}SYS_CRT_DRF_BISR_TEST_RESUME1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     vcpu_sleepsys_r:1;
unsigned int     acpu_sleepsys_r:1;
unsigned int     reserved_1:1;
}SYS_CRT_SLEEP_ACK1;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     vcpu_sleepreq_r:1;
unsigned int     acpu_sleepreq_r:1;
unsigned int     write_data:1;
}SYS_CRT_SLEEP_REQ1;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     nf_light_sleep:1;
unsigned int     md_light_sleep:1;
unsigned int     etn_light_sleep:1;
unsigned int     cp_light_sleep:1;
unsigned int     hdmitx_light_sleep:1;
unsigned int     dc_sb_light_sleep:1;
unsigned int     sb2_light_sleep:1;
unsigned int     ve_light_sleep:1;
unsigned int     sb2_rom_light_sleep:1;
unsigned int     kcpu_light_sleep:1;
unsigned int     vcpu_light_sleep:1;
unsigned int     acpu_light_sleep:1;
unsigned int     write_data:1;
}SYS_CRT_LIGHT_SLEEP1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     spnr_bisr_rstn:1;
unsigned int     reserved_1:1;
unsigned int     iuzd_bisr_rstn:1;
unsigned int     ich1_bisr_sdnr_rstn:1;
}SYS_CRT_BISR_RSTN2;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     mbist_ve_st:1;
unsigned int     mbist_tp_st:1;
unsigned int     mbist_md_st:1;
unsigned int     mbist_hdmi_st:1;
unsigned int     mbist_acpu_st:1;
}SYS_BIST_ST1;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     vcpu_bist_fail:1;
unsigned int     reserved_1:9;
unsigned int     vde_bist_fail0:1;
unsigned int     sce_bist_fail:1;
unsigned int     kcpu_bist_fail:1;
unsigned int     etn_bist2_fail:1;
unsigned int     nf1_bist_fail:1;
unsigned int     me_bist_fail1:1;
unsigned int     me_bist_fail0:1;
unsigned int     reserved_2:2;
unsigned int     dc3_bist_fail:1;
unsigned int     dc2_bist_fail:1;
unsigned int     reserved_3:2;
unsigned int     cp_bist_fail:1;
unsigned int     ae_bist_fail:1;
}SYS_BIST_ST2;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     ve_bist17_fail:1;
unsigned int     ve_bist16_fail:1;
unsigned int     ve_bist15_fail:1;
unsigned int     ve_bist14_fail:1;
unsigned int     ve_bist13_fail:1;
unsigned int     ve_bist12_fail:1;
unsigned int     ve_bist11_fail:1;
unsigned int     ve_bist10_fail:1;
unsigned int     ve_bist9_fail:1;
unsigned int     ve_bist8_fail:1;
unsigned int     ve_bist7_fail:1;
unsigned int     ve_bist6_fail:1;
unsigned int     ve_bist5_fail:1;
unsigned int     ve_bist4_fail:1;
unsigned int     ve_bist3_fail:1;
unsigned int     ve_bist2_fail:1;
unsigned int     ve_bist1_fail:1;
}SYS_BIST_ST3;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     vcpu_drf_bist_fail:1;
unsigned int     reserved_1:11;
unsigned int     etn_drf_bist2_fail:1;
unsigned int     sce_drf_bist_fail:1;
unsigned int     nf1_drf_bist_fail:1;
unsigned int     me_drf_bist_fail1:1;
unsigned int     me_drf_bist_fail0:1;
unsigned int     reserved_2:2;
unsigned int     dc3_drf_bist_fail:1;
unsigned int     dc2_drf_bist_fail:1;
unsigned int     reserved_3:2;
unsigned int     cp_drf_bist_fail:1;
unsigned int     ae_drf_bist_fail:1;
}SYS_DRF_ST1;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     ve_drf_bist17_fail:1;
unsigned int     ve_drf_bist16_fail:1;
unsigned int     ve_drf_bist15_fail:1;
unsigned int     ve_drf_bist14_fail:1;
unsigned int     ve_drf_bist13_fail:1;
unsigned int     ve_drf_bist12_fail:1;
unsigned int     ve_drf_bist11_fail:1;
unsigned int     ve_drf_bist10_fail:1;
unsigned int     ve_drf_bist9_fail:1;
unsigned int     ve_drf_bist8_fail:1;
unsigned int     ve_drf_bist7_fail:1;
unsigned int     ve_drf_bist6_fail:1;
unsigned int     ve_drf_bist5_fail:1;
unsigned int     ve_drf_bist4_fail:1;
unsigned int     ve_drf_bist3_fail:1;
unsigned int     ve_drf_bist2_fail:1;
unsigned int     ve_drf_bist1_fail:1;
}SYS_DRF_ST2;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     spnr_bisr_done:1;
unsigned int     reserved_1:1;
unsigned int     i3ddma_uzd_bisr_done:1;
unsigned int     ich1_bisr_sdnr_done:1;
unsigned int     reserved_2:20;
unsigned int     cp42k_bisr_done:1;
unsigned int     kcpu_bisr_done:1;
unsigned int     vcpu_bisr_done:1;
unsigned int     reserved_3:1;
}SYS_CRT_BISR_DONE1;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     vcpu_bisr_fail:1;
unsigned int     reserved_1:24;
unsigned int     cp42k_bisr_fail:1;
unsigned int     kcpu_bisr_st:1;
unsigned int     reserved_2:1;
unsigned int     acpu_bisr_st:1;
}SYS_CRT_BISR_ST1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     cp42k_bisr_repaired:1;
unsigned int     kcpu_bisr_repaired:1;
unsigned int     vcpu_bisr_repaired:1;
unsigned int     acpu_bisr_repaired:1;
}SYS_CRT_BISR_REPAIRED1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     vcpu_bisr_out:28;
}SYS_CRT_BISR_OUT1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     cp42k_bisr_out:7;
}SYS_CRT_BISR_OUT2;

typedef struct 
{
unsigned int     reserved_0:3;
unsigned int     vcpu_drf_bisr_fail:1;
unsigned int     reserved_1:24;
unsigned int     cp42k_drf_bisr_fail:1;
unsigned int     reserved_2:3;
}SYS_CRT_DRF_BISR_ST1;

#endif

#define SYS_SOFT_RESET1                                                              0x18000000
#define SYS_SOFT_RESET1_reg_addr                                                     "0xB8000000"
#define SYS_SOFT_RESET1_reg                                                          0xB8000000
#define set_SYS_SOFT_RESET1_reg(data)   (*((volatile unsigned int*) SYS_SOFT_RESET1_reg)=data)
#define get_SYS_SOFT_RESET1_reg   (*((volatile unsigned int*) SYS_SOFT_RESET1_reg))
#define SYS_SOFT_RESET1_inst_adr                                                     "0x0000"
#define SYS_SOFT_RESET1_inst                                                         0x0000
#define SYS_SOFT_RESET1_rstn_demod_shift                                             (30)
#define SYS_SOFT_RESET1_rstn_demod_mask                                              (0x40000000)
#define SYS_SOFT_RESET1_rstn_demod(data)                                             (0x40000000&((data)<<30))
#define SYS_SOFT_RESET1_rstn_demod_src(data)                                         ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET1_get_rstn_demod(data)                                         ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET1_rstn_nf_shift                                                (29)
#define SYS_SOFT_RESET1_rstn_nf_mask                                                 (0x20000000)
#define SYS_SOFT_RESET1_rstn_nf(data)                                                (0x20000000&((data)<<29))
#define SYS_SOFT_RESET1_rstn_nf_src(data)                                            ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET1_get_rstn_nf(data)                                            ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET1_rstn_ae_shift                                                (28)
#define SYS_SOFT_RESET1_rstn_ae_mask                                                 (0x10000000)
#define SYS_SOFT_RESET1_rstn_ae(data)                                                (0x10000000&((data)<<28))
#define SYS_SOFT_RESET1_rstn_ae_src(data)                                            ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET1_get_rstn_ae(data)                                            ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET1_rstn_tp_shift                                                (27)
#define SYS_SOFT_RESET1_rstn_tp_mask                                                 (0x08000000)
#define SYS_SOFT_RESET1_rstn_tp(data)                                                (0x08000000&((data)<<27))
#define SYS_SOFT_RESET1_rstn_tp_src(data)                                            ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET1_get_rstn_tp(data)                                            ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET1_rstn_md_shift                                                (26)
#define SYS_SOFT_RESET1_rstn_md_mask                                                 (0x04000000)
#define SYS_SOFT_RESET1_rstn_md(data)                                                (0x04000000&((data)<<26))
#define SYS_SOFT_RESET1_rstn_md_src(data)                                            ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET1_get_rstn_md(data)                                            ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET1_rstn_cp_shift                                                (25)
#define SYS_SOFT_RESET1_rstn_cp_mask                                                 (0x02000000)
#define SYS_SOFT_RESET1_rstn_cp(data)                                                (0x02000000&((data)<<25))
#define SYS_SOFT_RESET1_rstn_cp_src(data)                                            ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET1_get_rstn_cp(data)                                            ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET1_rstn_dc_phy_shift                                            (24)
#define SYS_SOFT_RESET1_rstn_dc_phy_mask                                             (0x01000000)
#define SYS_SOFT_RESET1_rstn_dc_phy(data)                                            (0x01000000&((data)<<24))
#define SYS_SOFT_RESET1_rstn_dc_phy_src(data)                                        ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET1_get_rstn_dc_phy(data)                                        ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET1_rstn_dcu_shift                                               (23)
#define SYS_SOFT_RESET1_rstn_dcu_mask                                                (0x00800000)
#define SYS_SOFT_RESET1_rstn_dcu(data)                                               (0x00800000&((data)<<23))
#define SYS_SOFT_RESET1_rstn_dcu_src(data)                                           ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET1_get_rstn_dcu(data)                                           ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET1_rstn_se_shift                                                (22)
#define SYS_SOFT_RESET1_rstn_se_mask                                                 (0x00400000)
#define SYS_SOFT_RESET1_rstn_se(data)                                                (0x00400000&((data)<<22))
#define SYS_SOFT_RESET1_rstn_se_src(data)                                            ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET1_get_rstn_se(data)                                            ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET1_rstn_gpu_shift                                               (21)
#define SYS_SOFT_RESET1_rstn_gpu_mask                                                (0x00200000)
#define SYS_SOFT_RESET1_rstn_gpu(data)                                               (0x00200000&((data)<<21))
#define SYS_SOFT_RESET1_rstn_gpu_src(data)                                           ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET1_get_rstn_gpu(data)                                           ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET1_rstn_vo_shift                                                (20)
#define SYS_SOFT_RESET1_rstn_vo_mask                                                 (0x00100000)
#define SYS_SOFT_RESET1_rstn_vo(data)                                                (0x00100000&((data)<<20))
#define SYS_SOFT_RESET1_rstn_vo_src(data)                                            ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET1_get_rstn_vo(data)                                            ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET1_rstn_tve_shift                                               (19)
#define SYS_SOFT_RESET1_rstn_tve_mask                                                (0x00080000)
#define SYS_SOFT_RESET1_rstn_tve(data)                                               (0x00080000&((data)<<19))
#define SYS_SOFT_RESET1_rstn_tve_src(data)                                           ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET1_get_rstn_tve(data)                                           ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET1_rstn_ve_shift                                                (18)
#define SYS_SOFT_RESET1_rstn_ve_mask                                                 (0x00040000)
#define SYS_SOFT_RESET1_rstn_ve(data)                                                (0x00040000&((data)<<18))
#define SYS_SOFT_RESET1_rstn_ve_src(data)                                            ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET1_get_rstn_ve(data)                                            ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET1_rstn_ve_p2_shift                                             (17)
#define SYS_SOFT_RESET1_rstn_ve_p2_mask                                              (0x00020000)
#define SYS_SOFT_RESET1_rstn_ve_p2(data)                                             (0x00020000&((data)<<17))
#define SYS_SOFT_RESET1_rstn_ve_p2_src(data)                                         ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET1_get_rstn_ve_p2(data)                                         ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET1_rstn_me1_shift                                               (16)
#define SYS_SOFT_RESET1_rstn_me1_mask                                                (0x00010000)
#define SYS_SOFT_RESET1_rstn_me1(data)                                               (0x00010000&((data)<<16))
#define SYS_SOFT_RESET1_rstn_me1_src(data)                                           ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET1_get_rstn_me1(data)                                           ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET1_rstn_aio_shift                                               (15)
#define SYS_SOFT_RESET1_rstn_aio_mask                                                (0x00008000)
#define SYS_SOFT_RESET1_rstn_aio(data)                                               (0x00008000&((data)<<15))
#define SYS_SOFT_RESET1_rstn_aio_src(data)                                           ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET1_get_rstn_aio(data)                                           ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET1_rstn_etn_phy_shift                                           (14)
#define SYS_SOFT_RESET1_rstn_etn_phy_mask                                            (0x00004000)
#define SYS_SOFT_RESET1_rstn_etn_phy(data)                                           (0x00004000&((data)<<14))
#define SYS_SOFT_RESET1_rstn_etn_phy_src(data)                                       ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET1_get_rstn_etn_phy(data)                                       ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET1_rstn_etn_shift                                               (13)
#define SYS_SOFT_RESET1_rstn_etn_mask                                                (0x00002000)
#define SYS_SOFT_RESET1_rstn_etn(data)                                               (0x00002000&((data)<<13))
#define SYS_SOFT_RESET1_rstn_etn_src(data)                                           ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET1_get_rstn_etn(data)                                           ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET1_rstn_hdmi_shift                                              (12)
#define SYS_SOFT_RESET1_rstn_hdmi_mask                                               (0x00001000)
#define SYS_SOFT_RESET1_rstn_hdmi(data)                                              (0x00001000&((data)<<12))
#define SYS_SOFT_RESET1_rstn_hdmi_src(data)                                          ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET1_get_rstn_hdmi(data)                                          ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET1_RSTN_DDC_shift                                               (11)
#define SYS_SOFT_RESET1_RSTN_DDC_mask                                                (0x00000800)
#define SYS_SOFT_RESET1_RSTN_DDC(data)                                               (0x00000800&((data)<<11))
#define SYS_SOFT_RESET1_RSTN_DDC_src(data)                                           ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET1_get_RSTN_DDC(data)                                           ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET1_rstn_usb_phy2_shift                                          (10)
#define SYS_SOFT_RESET1_rstn_usb_phy2_mask                                           (0x00000400)
#define SYS_SOFT_RESET1_rstn_usb_phy2(data)                                          (0x00000400&((data)<<10))
#define SYS_SOFT_RESET1_rstn_usb_phy2_src(data)                                      ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET1_get_rstn_usb_phy2(data)                                      ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET1_rstn_usb_phy1_shift                                          (9)
#define SYS_SOFT_RESET1_rstn_usb_phy1_mask                                           (0x00000200)
#define SYS_SOFT_RESET1_rstn_usb_phy1(data)                                          (0x00000200&((data)<<9))
#define SYS_SOFT_RESET1_rstn_usb_phy1_src(data)                                      ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET1_get_rstn_usb_phy1(data)                                      ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET1_rstn_usb_phy0_shift                                          (8)
#define SYS_SOFT_RESET1_rstn_usb_phy0_mask                                           (0x00000100)
#define SYS_SOFT_RESET1_rstn_usb_phy0(data)                                          (0x00000100&((data)<<8))
#define SYS_SOFT_RESET1_rstn_usb_phy0_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET1_get_rstn_usb_phy0(data)                                      ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET1_rstn_usb_mac0_shift                                          (6)
#define SYS_SOFT_RESET1_rstn_usb_mac0_mask                                           (0x00000040)
#define SYS_SOFT_RESET1_rstn_usb_mac0(data)                                          (0x00000040&((data)<<6))
#define SYS_SOFT_RESET1_rstn_usb_mac0_src(data)                                      ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET1_get_rstn_usb_mac0(data)                                      ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET1_rstn_usb_mac1_shift                                          (5)
#define SYS_SOFT_RESET1_rstn_usb_mac1_mask                                           (0x00000020)
#define SYS_SOFT_RESET1_rstn_usb_mac1(data)                                          (0x00000020&((data)<<5))
#define SYS_SOFT_RESET1_rstn_usb_mac1_src(data)                                      ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET1_get_rstn_usb_mac1(data)                                      ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET1_rstn_usb_arb_shift                                           (4)
#define SYS_SOFT_RESET1_rstn_usb_arb_mask                                            (0x00000010)
#define SYS_SOFT_RESET1_rstn_usb_arb(data)                                           (0x00000010&((data)<<4))
#define SYS_SOFT_RESET1_rstn_usb_arb_src(data)                                       ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET1_get_rstn_usb_arb(data)                                       ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET1_rstn_gspi_shift                                              (3)
#define SYS_SOFT_RESET1_rstn_gspi_mask                                               (0x00000008)
#define SYS_SOFT_RESET1_rstn_gspi(data)                                              (0x00000008&((data)<<3))
#define SYS_SOFT_RESET1_rstn_gspi_src(data)                                          ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET1_get_rstn_gspi(data)                                          ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET1_rstn_rng_shift                                               (1)
#define SYS_SOFT_RESET1_rstn_rng_mask                                                (0x00000002)
#define SYS_SOFT_RESET1_rstn_rng(data)                                               (0x00000002&((data)<<1))
#define SYS_SOFT_RESET1_rstn_rng_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET1_get_rstn_rng(data)                                           ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET1_rstn_misc_shift                                              (0)
#define SYS_SOFT_RESET1_rstn_misc_mask                                               (0x00000001)
#define SYS_SOFT_RESET1_rstn_misc(data)                                              (0x00000001&((data)<<0))
#define SYS_SOFT_RESET1_rstn_misc_src(data)                                          ((0x00000001&(data))>>0)
#define SYS_SOFT_RESET1_get_rstn_misc(data)                                          ((0x00000001&(data))>>0)


#define SYS_SOFT_RESET2                                                              0x18000004
#define SYS_SOFT_RESET2_reg_addr                                                     "0xB8000004"
#define SYS_SOFT_RESET2_reg                                                          0xB8000004
#define set_SYS_SOFT_RESET2_reg(data)   (*((volatile unsigned int*) SYS_SOFT_RESET2_reg)=data)
#define get_SYS_SOFT_RESET2_reg   (*((volatile unsigned int*) SYS_SOFT_RESET2_reg))
#define SYS_SOFT_RESET2_inst_adr                                                     "0x0001"
#define SYS_SOFT_RESET2_inst                                                         0x0001
#define SYS_SOFT_RESET2_rstn_ur2_shift                                               (31)
#define SYS_SOFT_RESET2_rstn_ur2_mask                                                (0x80000000)
#define SYS_SOFT_RESET2_rstn_ur2(data)                                               (0x80000000&((data)<<31))
#define SYS_SOFT_RESET2_rstn_ur2_src(data)                                           ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET2_get_rstn_ur2(data)                                           ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET2_rstn_ur1_shift                                               (28)
#define SYS_SOFT_RESET2_rstn_ur1_mask                                                (0x10000000)
#define SYS_SOFT_RESET2_rstn_ur1(data)                                               (0x10000000&((data)<<28))
#define SYS_SOFT_RESET2_rstn_ur1_src(data)                                           ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET2_get_rstn_ur1(data)                                           ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET2_rstn_i2c_0_shift                                             (27)
#define SYS_SOFT_RESET2_rstn_i2c_0_mask                                              (0x08000000)
#define SYS_SOFT_RESET2_rstn_i2c_0(data)                                             (0x08000000&((data)<<27))
#define SYS_SOFT_RESET2_rstn_i2c_0_src(data)                                         ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET2_get_rstn_i2c_0(data)                                         ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET2_rstn_i2c_1_shift                                             (26)
#define SYS_SOFT_RESET2_rstn_i2c_1_mask                                              (0x04000000)
#define SYS_SOFT_RESET2_rstn_i2c_1(data)                                             (0x04000000&((data)<<26))
#define SYS_SOFT_RESET2_rstn_i2c_1_src(data)                                         ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET2_get_rstn_i2c_1(data)                                         ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET2_rstn_i2c_2_shift                                             (25)
#define SYS_SOFT_RESET2_rstn_i2c_2_mask                                              (0x02000000)
#define SYS_SOFT_RESET2_rstn_i2c_2(data)                                             (0x02000000&((data)<<25))
#define SYS_SOFT_RESET2_rstn_i2c_2_src(data)                                         ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET2_get_rstn_i2c_2(data)                                         ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET2_rstn_pcmcia_shift                                            (24)
#define SYS_SOFT_RESET2_rstn_pcmcia_mask                                             (0x01000000)
#define SYS_SOFT_RESET2_rstn_pcmcia(data)                                            (0x01000000&((data)<<24))
#define SYS_SOFT_RESET2_rstn_pcmcia_src(data)                                        ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET2_get_rstn_pcmcia(data)                                        ((0x01000000&(data))>>24)
#define SYS_SOFT_RESET2_rstn_sc_shift                                                (23)
#define SYS_SOFT_RESET2_rstn_sc_mask                                                 (0x00800000)
#define SYS_SOFT_RESET2_rstn_sc(data)                                                (0x00800000&((data)<<23))
#define SYS_SOFT_RESET2_rstn_sc_src(data)                                            ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET2_get_rstn_sc(data)                                            ((0x00800000&(data))>>23)
#define SYS_SOFT_RESET2_rstn_ir_shift                                                (22)
#define SYS_SOFT_RESET2_rstn_ir_mask                                                 (0x00400000)
#define SYS_SOFT_RESET2_rstn_ir(data)                                                (0x00400000&((data)<<22))
#define SYS_SOFT_RESET2_rstn_ir_src(data)                                            ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET2_get_rstn_ir(data)                                            ((0x00400000&(data))>>22)
#define SYS_SOFT_RESET2_rstn_cec_shift                                               (21)
#define SYS_SOFT_RESET2_rstn_cec_mask                                                (0x00200000)
#define SYS_SOFT_RESET2_rstn_cec(data)                                               (0x00200000&((data)<<21))
#define SYS_SOFT_RESET2_rstn_cec_src(data)                                           ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET2_get_rstn_cec(data)                                           ((0x00200000&(data))>>21)
#define SYS_SOFT_RESET2_rstn_tve_clkgen_shift                                        (19)
#define SYS_SOFT_RESET2_rstn_tve_clkgen_mask                                         (0x00080000)
#define SYS_SOFT_RESET2_rstn_tve_clkgen(data)                                        (0x00080000&((data)<<19))
#define SYS_SOFT_RESET2_rstn_tve_clkgen_src(data)                                    ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET2_get_rstn_tve_clkgen(data)                                    ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET2_RSTN_TM_shift                                                (18)
#define SYS_SOFT_RESET2_RSTN_TM_mask                                                 (0x00040000)
#define SYS_SOFT_RESET2_RSTN_TM(data)                                                (0x00040000&((data)<<18))
#define SYS_SOFT_RESET2_RSTN_TM_src(data)                                            ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET2_get_RSTN_TM(data)                                            ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET2_RSTN_ATVIN2_shift                                            (17)
#define SYS_SOFT_RESET2_RSTN_ATVIN2_mask                                             (0x00020000)
#define SYS_SOFT_RESET2_RSTN_ATVIN2(data)                                            (0x00020000&((data)<<17))
#define SYS_SOFT_RESET2_RSTN_ATVIN2_src(data)                                        ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET2_get_RSTN_ATVIN2(data)                                        ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET2_RSTN_ATVIN_shift                                             (16)
#define SYS_SOFT_RESET2_RSTN_ATVIN_mask                                              (0x00010000)
#define SYS_SOFT_RESET2_RSTN_ATVIN(data)                                             (0x00010000&((data)<<16))
#define SYS_SOFT_RESET2_RSTN_ATVIN_src(data)                                         ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET2_get_RSTN_ATVIN(data)                                         ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET2_RSTN_BISTREG_shift                                           (15)
#define SYS_SOFT_RESET2_RSTN_BISTREG_mask                                            (0x00008000)
#define SYS_SOFT_RESET2_RSTN_BISTREG(data)                                           (0x00008000&((data)<<15))
#define SYS_SOFT_RESET2_RSTN_BISTREG_src(data)                                       ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET2_get_RSTN_BISTREG(data)                                       ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET2_RSTN_USB_MAC_shift                                           (14)
#define SYS_SOFT_RESET2_RSTN_USB_MAC_mask                                            (0x00004000)
#define SYS_SOFT_RESET2_RSTN_USB_MAC(data)                                           (0x00004000&((data)<<14))
#define SYS_SOFT_RESET2_RSTN_USB_MAC_src(data)                                       ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET2_get_RSTN_USB_MAC(data)                                       ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET2_RSTN_PADMUX_shift                                            (13)
#define SYS_SOFT_RESET2_RSTN_PADMUX_mask                                             (0x00002000)
#define SYS_SOFT_RESET2_RSTN_PADMUX(data)                                            (0x00002000&((data)<<13))
#define SYS_SOFT_RESET2_RSTN_PADMUX_src(data)                                        ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET2_get_RSTN_PADMUX(data)                                        ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET2_RSTN_DTV_DEMOD_shift                                         (12)
#define SYS_SOFT_RESET2_RSTN_DTV_DEMOD_mask                                          (0x00001000)
#define SYS_SOFT_RESET2_RSTN_DTV_DEMOD(data)                                         (0x00001000&((data)<<12))
#define SYS_SOFT_RESET2_RSTN_DTV_DEMOD_src(data)                                     ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET2_get_RSTN_DTV_DEMOD(data)                                     ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET2_rstn_emmc_shift                                              (11)
#define SYS_SOFT_RESET2_rstn_emmc_mask                                               (0x00000800)
#define SYS_SOFT_RESET2_rstn_emmc(data)                                              (0x00000800&((data)<<11))
#define SYS_SOFT_RESET2_rstn_emmc_src(data)                                          ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET2_get_rstn_emmc(data)                                          ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET2_rstn_cr_shift                                                (10)
#define SYS_SOFT_RESET2_rstn_cr_mask                                                 (0x00000400)
#define SYS_SOFT_RESET2_rstn_cr(data)                                                (0x00000400&((data)<<10))
#define SYS_SOFT_RESET2_rstn_cr_src(data)                                            ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET2_get_rstn_cr(data)                                            ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET2_rstn_pcr_cnt_shift                                           (9)
#define SYS_SOFT_RESET2_rstn_pcr_cnt_mask                                            (0x00000200)
#define SYS_SOFT_RESET2_rstn_pcr_cnt(data)                                           (0x00000200&((data)<<9))
#define SYS_SOFT_RESET2_rstn_pcr_cnt_src(data)                                       ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET2_get_rstn_pcr_cnt(data)                                       ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET2_rstn_scpu_wrap_shift                                         (8)
#define SYS_SOFT_RESET2_rstn_scpu_wrap_mask                                          (0x00000100)
#define SYS_SOFT_RESET2_rstn_scpu_wrap(data)                                         (0x00000100&((data)<<8))
#define SYS_SOFT_RESET2_rstn_scpu_wrap_src(data)                                     ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET2_get_rstn_scpu_wrap(data)                                     ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET2_RSTN_PWM_shift                                               (7)
#define SYS_SOFT_RESET2_RSTN_PWM_mask                                                (0x00000080)
#define SYS_SOFT_RESET2_RSTN_PWM(data)                                               (0x00000080&((data)<<7))
#define SYS_SOFT_RESET2_RSTN_PWM_src(data)                                           ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET2_get_RSTN_PWM(data)                                           ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET2_RSTN_GPIO_shift                                              (6)
#define SYS_SOFT_RESET2_RSTN_GPIO_mask                                               (0x00000040)
#define SYS_SOFT_RESET2_RSTN_GPIO(data)                                              (0x00000040&((data)<<6))
#define SYS_SOFT_RESET2_RSTN_GPIO_src(data)                                          ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET2_get_RSTN_GPIO(data)                                          ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET2_RSTN_PLLREG_shift                                            (5)
#define SYS_SOFT_RESET2_RSTN_PLLREG_mask                                             (0x00000020)
#define SYS_SOFT_RESET2_RSTN_PLLREG(data)                                            (0x00000020&((data)<<5))
#define SYS_SOFT_RESET2_RSTN_PLLREG_src(data)                                        ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET2_get_RSTN_PLLREG(data)                                        ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET2_RSTN_SCPU_shift                                              (4)
#define SYS_SOFT_RESET2_RSTN_SCPU_mask                                               (0x00000010)
#define SYS_SOFT_RESET2_RSTN_SCPU(data)                                              (0x00000010&((data)<<4))
#define SYS_SOFT_RESET2_RSTN_SCPU_src(data)                                          ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET2_get_RSTN_SCPU(data)                                          ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET2_rstn_vde_shift                                               (3)
#define SYS_SOFT_RESET2_rstn_vde_mask                                                (0x00000008)
#define SYS_SOFT_RESET2_rstn_vde(data)                                               (0x00000008&((data)<<3))
#define SYS_SOFT_RESET2_rstn_vde_src(data)                                           ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET2_get_rstn_vde(data)                                           ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET2_rstn_vcpu_shift                                              (1)
#define SYS_SOFT_RESET2_rstn_vcpu_mask                                               (0x00000002)
#define SYS_SOFT_RESET2_rstn_vcpu(data)                                              (0x00000002&((data)<<1))
#define SYS_SOFT_RESET2_rstn_vcpu_src(data)                                          ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET2_get_rstn_vcpu(data)                                          ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET2_rstn_acpu_shift                                              (0)
#define SYS_SOFT_RESET2_rstn_acpu_mask                                               (0x00000001)
#define SYS_SOFT_RESET2_rstn_acpu(data)                                              (0x00000001&((data)<<0))
#define SYS_SOFT_RESET2_rstn_acpu_src(data)                                          ((0x00000001&(data))>>0)
#define SYS_SOFT_RESET2_get_rstn_acpu(data)                                          ((0x00000001&(data))>>0)


#define SYS_SOFT_RESET3                                                              0x18000008
#define SYS_SOFT_RESET3_reg_addr                                                     "0xB8000008"
#define SYS_SOFT_RESET3_reg                                                          0xB8000008
#define set_SYS_SOFT_RESET3_reg(data)   (*((volatile unsigned int*) SYS_SOFT_RESET3_reg)=data)
#define get_SYS_SOFT_RESET3_reg   (*((volatile unsigned int*) SYS_SOFT_RESET3_reg))
#define SYS_SOFT_RESET3_inst_adr                                                     "0x0002"
#define SYS_SOFT_RESET3_inst                                                         0x0002
#define SYS_SOFT_RESET3_rstn_akl_shift                                               (31)
#define SYS_SOFT_RESET3_rstn_akl_mask                                                (0x80000000)
#define SYS_SOFT_RESET3_rstn_akl(data)                                               (0x80000000&((data)<<31))
#define SYS_SOFT_RESET3_rstn_akl_src(data)                                           ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET3_get_rstn_akl(data)                                           ((0x80000000&(data))>>31)
#define SYS_SOFT_RESET3_rstn_nd_shift                                                (30)
#define SYS_SOFT_RESET3_rstn_nd_mask                                                 (0x40000000)
#define SYS_SOFT_RESET3_rstn_nd(data)                                                (0x40000000&((data)<<30))
#define SYS_SOFT_RESET3_rstn_nd_src(data)                                            ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET3_get_rstn_nd(data)                                            ((0x40000000&(data))>>30)
#define SYS_SOFT_RESET3_rstn_dsc_shift                                               (29)
#define SYS_SOFT_RESET3_rstn_dsc_mask                                                (0x20000000)
#define SYS_SOFT_RESET3_rstn_dsc(data)                                               (0x20000000&((data)<<29))
#define SYS_SOFT_RESET3_rstn_dsc_src(data)                                           ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET3_get_rstn_dsc(data)                                           ((0x20000000&(data))>>29)
#define SYS_SOFT_RESET3_rstn_sce_shift                                               (28)
#define SYS_SOFT_RESET3_rstn_sce_mask                                                (0x10000000)
#define SYS_SOFT_RESET3_rstn_sce(data)                                               (0x10000000&((data)<<28))
#define SYS_SOFT_RESET3_rstn_sce_src(data)                                           ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET3_get_rstn_sce(data)                                           ((0x10000000&(data))>>28)
#define SYS_SOFT_RESET3_rstn_kt_shift                                                (27)
#define SYS_SOFT_RESET3_rstn_kt_mask                                                 (0x08000000)
#define SYS_SOFT_RESET3_rstn_kt(data)                                                (0x08000000&((data)<<27))
#define SYS_SOFT_RESET3_rstn_kt_src(data)                                            ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET3_get_rstn_kt(data)                                            ((0x08000000&(data))>>27)
#define SYS_SOFT_RESET3_rstn_scpu_dbg_shift                                          (26)
#define SYS_SOFT_RESET3_rstn_scpu_dbg_mask                                           (0x04000000)
#define SYS_SOFT_RESET3_rstn_scpu_dbg(data)                                          (0x04000000&((data)<<26))
#define SYS_SOFT_RESET3_rstn_scpu_dbg_src(data)                                      ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET3_get_rstn_scpu_dbg(data)                                      ((0x04000000&(data))>>26)
#define SYS_SOFT_RESET3_rstn_scpu_l2_shift                                           (25)
#define SYS_SOFT_RESET3_rstn_scpu_l2_mask                                            (0x02000000)
#define SYS_SOFT_RESET3_rstn_scpu_l2(data)                                           (0x02000000&((data)<<25))
#define SYS_SOFT_RESET3_rstn_scpu_l2_src(data)                                       ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET3_get_rstn_scpu_l2(data)                                       ((0x02000000&(data))>>25)
#define SYS_SOFT_RESET3_RSTN_TVSB1_TVE_shift                                         (20)
#define SYS_SOFT_RESET3_RSTN_TVSB1_TVE_mask                                          (0x00100000)
#define SYS_SOFT_RESET3_RSTN_TVSB1_TVE(data)                                         (0x00100000&((data)<<20))
#define SYS_SOFT_RESET3_RSTN_TVSB1_TVE_src(data)                                     ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET3_get_RSTN_TVSB1_TVE(data)                                     ((0x00100000&(data))>>20)
#define SYS_SOFT_RESET3_RSTN_VDEC_shift                                              (19)
#define SYS_SOFT_RESET3_RSTN_VDEC_mask                                               (0x00080000)
#define SYS_SOFT_RESET3_RSTN_VDEC(data)                                              (0x00080000&((data)<<19))
#define SYS_SOFT_RESET3_RSTN_VDEC_src(data)                                          ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET3_get_RSTN_VDEC(data)                                          ((0x00080000&(data))>>19)
#define SYS_SOFT_RESET3_rstn_kcpu_shift                                              (18)
#define SYS_SOFT_RESET3_rstn_kcpu_mask                                               (0x00040000)
#define SYS_SOFT_RESET3_rstn_kcpu(data)                                              (0x00040000&((data)<<18))
#define SYS_SOFT_RESET3_rstn_kcpu_src(data)                                          ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET3_get_rstn_kcpu(data)                                          ((0x00040000&(data))>>18)
#define SYS_SOFT_RESET3_rstn_hdmirx_shift                                            (17)
#define SYS_SOFT_RESET3_rstn_hdmirx_mask                                             (0x00020000)
#define SYS_SOFT_RESET3_rstn_hdmirx(data)                                            (0x00020000&((data)<<17))
#define SYS_SOFT_RESET3_rstn_hdmirx_src(data)                                        ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET3_get_rstn_hdmirx(data)                                        ((0x00020000&(data))>>17)
#define SYS_SOFT_RESET3_RSTN_TV_TVE_shift                                            (16)
#define SYS_SOFT_RESET3_RSTN_TV_TVE_mask                                             (0x00010000)
#define SYS_SOFT_RESET3_RSTN_TV_TVE(data)                                            (0x00010000&((data)<<16))
#define SYS_SOFT_RESET3_RSTN_TV_TVE_src(data)                                        ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET3_get_RSTN_TV_TVE(data)                                        ((0x00010000&(data))>>16)
#define SYS_SOFT_RESET3_RSTN_OSDCOMP_shift                                           (15)
#define SYS_SOFT_RESET3_RSTN_OSDCOMP_mask                                            (0x00008000)
#define SYS_SOFT_RESET3_RSTN_OSDCOMP(data)                                           (0x00008000&((data)<<15))
#define SYS_SOFT_RESET3_RSTN_OSDCOMP_src(data)                                       ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET3_get_RSTN_OSDCOMP(data)                                       ((0x00008000&(data))>>15)
#define SYS_SOFT_RESET3_RSTN_TVSB3_shift                                             (14)
#define SYS_SOFT_RESET3_RSTN_TVSB3_mask                                              (0x00004000)
#define SYS_SOFT_RESET3_RSTN_TVSB3(data)                                             (0x00004000&((data)<<14))
#define SYS_SOFT_RESET3_RSTN_TVSB3_src(data)                                         ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET3_get_RSTN_TVSB3(data)                                         ((0x00004000&(data))>>14)
#define SYS_SOFT_RESET3_RSTN_TVSB1_shift                                             (13)
#define SYS_SOFT_RESET3_RSTN_TVSB1_mask                                              (0x00002000)
#define SYS_SOFT_RESET3_RSTN_TVSB1(data)                                             (0x00002000&((data)<<13))
#define SYS_SOFT_RESET3_RSTN_TVSB1_src(data)                                         ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET3_get_RSTN_TVSB1(data)                                         ((0x00002000&(data))>>13)
#define SYS_SOFT_RESET3_RSTN_TVSB2_shift                                             (12)
#define SYS_SOFT_RESET3_RSTN_TVSB2_mask                                              (0x00001000)
#define SYS_SOFT_RESET3_RSTN_TVSB2(data)                                             (0x00001000&((data)<<12))
#define SYS_SOFT_RESET3_RSTN_TVSB2_src(data)                                         ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET3_get_RSTN_TVSB2(data)                                         ((0x00001000&(data))>>12)
#define SYS_SOFT_RESET3_RSTN_IF_DEMOD_shift                                          (11)
#define SYS_SOFT_RESET3_RSTN_IF_DEMOD_mask                                           (0x00000800)
#define SYS_SOFT_RESET3_RSTN_IF_DEMOD(data)                                          (0x00000800&((data)<<11))
#define SYS_SOFT_RESET3_RSTN_IF_DEMOD_src(data)                                      ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET3_get_RSTN_IF_DEMOD(data)                                      ((0x00000800&(data))>>11)
#define SYS_SOFT_RESET3_RSTN_VDEC2_shift                                             (10)
#define SYS_SOFT_RESET3_RSTN_VDEC2_mask                                              (0x00000400)
#define SYS_SOFT_RESET3_RSTN_VDEC2(data)                                             (0x00000400&((data)<<10))
#define SYS_SOFT_RESET3_RSTN_VDEC2_src(data)                                         ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET3_get_RSTN_VDEC2(data)                                         ((0x00000400&(data))>>10)
#define SYS_SOFT_RESET3_RSTN_VBIS0_shift                                             (9)
#define SYS_SOFT_RESET3_RSTN_VBIS0_mask                                              (0x00000200)
#define SYS_SOFT_RESET3_RSTN_VBIS0(data)                                             (0x00000200&((data)<<9))
#define SYS_SOFT_RESET3_RSTN_VBIS0_src(data)                                         ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET3_get_RSTN_VBIS0(data)                                         ((0x00000200&(data))>>9)
#define SYS_SOFT_RESET3_RSTN_AUDIO2_DAC_shift                                        (8)
#define SYS_SOFT_RESET3_RSTN_AUDIO2_DAC_mask                                         (0x00000100)
#define SYS_SOFT_RESET3_RSTN_AUDIO2_DAC(data)                                        (0x00000100&((data)<<8))
#define SYS_SOFT_RESET3_RSTN_AUDIO2_DAC_src(data)                                    ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET3_get_RSTN_AUDIO2_DAC(data)                                    ((0x00000100&(data))>>8)
#define SYS_SOFT_RESET3_RSTN_AUDIO_ADC_shift                                         (7)
#define SYS_SOFT_RESET3_RSTN_AUDIO_ADC_mask                                          (0x00000080)
#define SYS_SOFT_RESET3_RSTN_AUDIO_ADC(data)                                         (0x00000080&((data)<<7))
#define SYS_SOFT_RESET3_RSTN_AUDIO_ADC_src(data)                                     ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET3_get_RSTN_AUDIO_ADC(data)                                     ((0x00000080&(data))>>7)
#define SYS_SOFT_RESET3_RSTN_AUDIO_DAC_shift                                         (6)
#define SYS_SOFT_RESET3_RSTN_AUDIO_DAC_mask                                          (0x00000040)
#define SYS_SOFT_RESET3_RSTN_AUDIO_DAC(data)                                         (0x00000040&((data)<<6))
#define SYS_SOFT_RESET3_RSTN_AUDIO_DAC_src(data)                                     ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET3_get_RSTN_AUDIO_DAC(data)                                     ((0x00000040&(data))>>6)
#define SYS_SOFT_RESET3_RSTN_IFADC_shift                                             (5)
#define SYS_SOFT_RESET3_RSTN_IFADC_mask                                              (0x00000020)
#define SYS_SOFT_RESET3_RSTN_IFADC(data)                                             (0x00000020&((data)<<5))
#define SYS_SOFT_RESET3_RSTN_IFADC_src(data)                                         ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET3_get_RSTN_IFADC(data)                                         ((0x00000020&(data))>>5)
#define SYS_SOFT_RESET3_RSTN_APLL_ADC_shift                                          (4)
#define SYS_SOFT_RESET3_RSTN_APLL_ADC_mask                                           (0x00000010)
#define SYS_SOFT_RESET3_RSTN_APLL_ADC(data)                                          (0x00000010&((data)<<4))
#define SYS_SOFT_RESET3_RSTN_APLL_ADC_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET3_get_RSTN_APLL_ADC(data)                                      ((0x00000010&(data))>>4)
#define SYS_SOFT_RESET3_RSTN_VODMA_shift                                             (3)
#define SYS_SOFT_RESET3_RSTN_VODMA_mask                                              (0x00000008)
#define SYS_SOFT_RESET3_RSTN_VODMA(data)                                             (0x00000008&((data)<<3))
#define SYS_SOFT_RESET3_RSTN_VODMA_src(data)                                         ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET3_get_RSTN_VODMA(data)                                         ((0x00000008&(data))>>3)
#define SYS_SOFT_RESET3_RSTN_DISPIM_shift                                            (2)
#define SYS_SOFT_RESET3_RSTN_DISPIM_mask                                             (0x00000004)
#define SYS_SOFT_RESET3_RSTN_DISPIM(data)                                            (0x00000004&((data)<<2))
#define SYS_SOFT_RESET3_RSTN_DISPIM_src(data)                                        ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET3_get_RSTN_DISPIM(data)                                        ((0x00000004&(data))>>2)
#define SYS_SOFT_RESET3_RSTN_DISP_shift                                              (1)
#define SYS_SOFT_RESET3_RSTN_DISP_mask                                               (0x00000002)
#define SYS_SOFT_RESET3_RSTN_DISP(data)                                              (0x00000002&((data)<<1))
#define SYS_SOFT_RESET3_RSTN_DISP_src(data)                                          ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET3_get_RSTN_DISP(data)                                          ((0x00000002&(data))>>1)
#define SYS_SOFT_RESET3_rstn_sb2_shift                                               (0)
#define SYS_SOFT_RESET3_rstn_sb2_mask                                                (0x00000001)
#define SYS_SOFT_RESET3_rstn_sb2(data)                                               (0x00000001&((data)<<0))
#define SYS_SOFT_RESET3_rstn_sb2_src(data)                                           ((0x00000001&(data))>>0)
#define SYS_SOFT_RESET3_get_rstn_sb2(data)                                           ((0x00000001&(data))>>0)


#define SYS_CLOCK_ENABLE1                                                            0x1800000C
#define SYS_CLOCK_ENABLE1_reg_addr                                                   "0xB800000C"
#define SYS_CLOCK_ENABLE1_reg                                                        0xB800000C
#define set_SYS_CLOCK_ENABLE1_reg(data)   (*((volatile unsigned int*) SYS_CLOCK_ENABLE1_reg)=data)
#define get_SYS_CLOCK_ENABLE1_reg   (*((volatile unsigned int*) SYS_CLOCK_ENABLE1_reg))
#define SYS_CLOCK_ENABLE1_inst_adr                                                   "0x0003"
#define SYS_CLOCK_ENABLE1_inst                                                       0x0003
#define SYS_CLOCK_ENABLE1_CLKEN_TVSB1_TVE_shift                                      (28)
#define SYS_CLOCK_ENABLE1_CLKEN_TVSB1_TVE_mask                                       (0x10000000)
#define SYS_CLOCK_ENABLE1_CLKEN_TVSB1_TVE(data)                                      (0x10000000&((data)<<28))
#define SYS_CLOCK_ENABLE1_CLKEN_TVSB1_TVE_src(data)                                  ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE1_get_CLKEN_TVSB1_TVE(data)                                  ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE1_clk_en_demod_shift                                         (27)
#define SYS_CLOCK_ENABLE1_clk_en_demod_mask                                          (0x08000000)
#define SYS_CLOCK_ENABLE1_clk_en_demod(data)                                         (0x08000000&((data)<<27))
#define SYS_CLOCK_ENABLE1_clk_en_demod_src(data)                                     ((0x08000000&(data))>>27)
#define SYS_CLOCK_ENABLE1_get_clk_en_demod(data)                                     ((0x08000000&(data))>>27)
#define SYS_CLOCK_ENABLE1_CLKEN_VDEC_shift                                           (26)
#define SYS_CLOCK_ENABLE1_CLKEN_VDEC_mask                                            (0x04000000)
#define SYS_CLOCK_ENABLE1_CLKEN_VDEC(data)                                           (0x04000000&((data)<<26))
#define SYS_CLOCK_ENABLE1_CLKEN_VDEC_src(data)                                       ((0x04000000&(data))>>26)
#define SYS_CLOCK_ENABLE1_get_CLKEN_VDEC(data)                                       ((0x04000000&(data))>>26)
#define SYS_CLOCK_ENABLE1_clk_en_cr_shift                                            (25)
#define SYS_CLOCK_ENABLE1_clk_en_cr_mask                                             (0x02000000)
#define SYS_CLOCK_ENABLE1_clk_en_cr(data)                                            (0x02000000&((data)<<25))
#define SYS_CLOCK_ENABLE1_clk_en_cr_src(data)                                        ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE1_get_clk_en_cr(data)                                        ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE1_clk_en_emmc_shift                                          (24)
#define SYS_CLOCK_ENABLE1_clk_en_emmc_mask                                           (0x01000000)
#define SYS_CLOCK_ENABLE1_clk_en_emmc(data)                                          (0x01000000&((data)<<24))
#define SYS_CLOCK_ENABLE1_clk_en_emmc_src(data)                                      ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE1_get_clk_en_emmc(data)                                      ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE1_clk_en_nf_shift                                            (23)
#define SYS_CLOCK_ENABLE1_clk_en_nf_mask                                             (0x00800000)
#define SYS_CLOCK_ENABLE1_clk_en_nf(data)                                            (0x00800000&((data)<<23))
#define SYS_CLOCK_ENABLE1_clk_en_nf_src(data)                                        ((0x00800000&(data))>>23)
#define SYS_CLOCK_ENABLE1_get_clk_en_nf(data)                                        ((0x00800000&(data))>>23)
#define SYS_CLOCK_ENABLE1_clk_en_ae_shift                                            (22)
#define SYS_CLOCK_ENABLE1_clk_en_ae_mask                                             (0x00400000)
#define SYS_CLOCK_ENABLE1_clk_en_ae(data)                                            (0x00400000&((data)<<22))
#define SYS_CLOCK_ENABLE1_clk_en_ae_src(data)                                        ((0x00400000&(data))>>22)
#define SYS_CLOCK_ENABLE1_get_clk_en_ae(data)                                        ((0x00400000&(data))>>22)
#define SYS_CLOCK_ENABLE1_clk_en_tp_shift                                            (21)
#define SYS_CLOCK_ENABLE1_clk_en_tp_mask                                             (0x00200000)
#define SYS_CLOCK_ENABLE1_clk_en_tp(data)                                            (0x00200000&((data)<<21))
#define SYS_CLOCK_ENABLE1_clk_en_tp_src(data)                                        ((0x00200000&(data))>>21)
#define SYS_CLOCK_ENABLE1_get_clk_en_tp(data)                                        ((0x00200000&(data))>>21)
#define SYS_CLOCK_ENABLE1_clk_en_md_shift                                            (20)
#define SYS_CLOCK_ENABLE1_clk_en_md_mask                                             (0x00100000)
#define SYS_CLOCK_ENABLE1_clk_en_md(data)                                            (0x00100000&((data)<<20))
#define SYS_CLOCK_ENABLE1_clk_en_md_src(data)                                        ((0x00100000&(data))>>20)
#define SYS_CLOCK_ENABLE1_get_clk_en_md(data)                                        ((0x00100000&(data))>>20)
#define SYS_CLOCK_ENABLE1_clk_en_cp_shift                                            (19)
#define SYS_CLOCK_ENABLE1_clk_en_cp_mask                                             (0x00080000)
#define SYS_CLOCK_ENABLE1_clk_en_cp(data)                                            (0x00080000&((data)<<19))
#define SYS_CLOCK_ENABLE1_clk_en_cp_src(data)                                        ((0x00080000&(data))>>19)
#define SYS_CLOCK_ENABLE1_get_clk_en_cp(data)                                        ((0x00080000&(data))>>19)
#define SYS_CLOCK_ENABLE1_clk_en_dcu_shift                                           (18)
#define SYS_CLOCK_ENABLE1_clk_en_dcu_mask                                            (0x00040000)
#define SYS_CLOCK_ENABLE1_clk_en_dcu(data)                                           (0x00040000&((data)<<18))
#define SYS_CLOCK_ENABLE1_clk_en_dcu_src(data)                                       ((0x00040000&(data))>>18)
#define SYS_CLOCK_ENABLE1_get_clk_en_dcu(data)                                       ((0x00040000&(data))>>18)
#define SYS_CLOCK_ENABLE1_clk_en_se_shift                                            (17)
#define SYS_CLOCK_ENABLE1_clk_en_se_mask                                             (0x00020000)
#define SYS_CLOCK_ENABLE1_clk_en_se(data)                                            (0x00020000&((data)<<17))
#define SYS_CLOCK_ENABLE1_clk_en_se_src(data)                                        ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE1_get_clk_en_se(data)                                        ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE1_CLKEN_TV_TVE_shift                                         (16)
#define SYS_CLOCK_ENABLE1_CLKEN_TV_TVE_mask                                          (0x00010000)
#define SYS_CLOCK_ENABLE1_CLKEN_TV_TVE(data)                                         (0x00010000&((data)<<16))
#define SYS_CLOCK_ENABLE1_CLKEN_TV_TVE_src(data)                                     ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE1_get_CLKEN_TV_TVE(data)                                     ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE1_clken_tve_clkgen_shift                                     (15)
#define SYS_CLOCK_ENABLE1_clken_tve_clkgen_mask                                      (0x00008000)
#define SYS_CLOCK_ENABLE1_clken_tve_clkgen(data)                                     (0x00008000&((data)<<15))
#define SYS_CLOCK_ENABLE1_clken_tve_clkgen_src(data)                                 ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE1_get_clken_tve_clkgen(data)                                 ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE1_clk_en_tve_shift                                           (14)
#define SYS_CLOCK_ENABLE1_clk_en_tve_mask                                            (0x00004000)
#define SYS_CLOCK_ENABLE1_clk_en_tve(data)                                           (0x00004000&((data)<<14))
#define SYS_CLOCK_ENABLE1_clk_en_tve_src(data)                                       ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE1_get_clk_en_tve(data)                                       ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE1_clk_en_ve_shift                                            (13)
#define SYS_CLOCK_ENABLE1_clk_en_ve_mask                                             (0x00002000)
#define SYS_CLOCK_ENABLE1_clk_en_ve(data)                                            (0x00002000&((data)<<13))
#define SYS_CLOCK_ENABLE1_clk_en_ve_src(data)                                        ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE1_get_clk_en_ve(data)                                        ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE1_clk_en_ve_p2_shift                                         (12)
#define SYS_CLOCK_ENABLE1_clk_en_ve_p2_mask                                          (0x00001000)
#define SYS_CLOCK_ENABLE1_clk_en_ve_p2(data)                                         (0x00001000&((data)<<12))
#define SYS_CLOCK_ENABLE1_clk_en_ve_p2_src(data)                                     ((0x00001000&(data))>>12)
#define SYS_CLOCK_ENABLE1_get_clk_en_ve_p2(data)                                     ((0x00001000&(data))>>12)
#define SYS_CLOCK_ENABLE1_clk_en_tve_sys_shift                                       (11)
#define SYS_CLOCK_ENABLE1_clk_en_tve_sys_mask                                        (0x00000800)
#define SYS_CLOCK_ENABLE1_clk_en_tve_sys(data)                                       (0x00000800&((data)<<11))
#define SYS_CLOCK_ENABLE1_clk_en_tve_sys_src(data)                                   ((0x00000800&(data))>>11)
#define SYS_CLOCK_ENABLE1_get_clk_en_tve_sys(data)                                   ((0x00000800&(data))>>11)
#define SYS_CLOCK_ENABLE1_clk_en_aio_shift                                           (10)
#define SYS_CLOCK_ENABLE1_clk_en_aio_mask                                            (0x00000400)
#define SYS_CLOCK_ENABLE1_clk_en_aio(data)                                           (0x00000400&((data)<<10))
#define SYS_CLOCK_ENABLE1_clk_en_aio_src(data)                                       ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE1_get_clk_en_aio(data)                                       ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE1_clk_en_etn_shift                                           (9)
#define SYS_CLOCK_ENABLE1_clk_en_etn_mask                                            (0x00000200)
#define SYS_CLOCK_ENABLE1_clk_en_etn(data)                                           (0x00000200&((data)<<9))
#define SYS_CLOCK_ENABLE1_clk_en_etn_src(data)                                       ((0x00000200&(data))>>9)
#define SYS_CLOCK_ENABLE1_get_clk_en_etn(data)                                       ((0x00000200&(data))>>9)
#define SYS_CLOCK_ENABLE1_clk_en_hdmi_shift                                          (8)
#define SYS_CLOCK_ENABLE1_clk_en_hdmi_mask                                           (0x00000100)
#define SYS_CLOCK_ENABLE1_clk_en_hdmi(data)                                          (0x00000100&((data)<<8))
#define SYS_CLOCK_ENABLE1_clk_en_hdmi_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_CLOCK_ENABLE1_get_clk_en_hdmi(data)                                      ((0x00000100&(data))>>8)
#define SYS_CLOCK_ENABLE1_reg_clken_3d_gde_shift                                     (7)
#define SYS_CLOCK_ENABLE1_reg_clken_3d_gde_mask                                      (0x00000080)
#define SYS_CLOCK_ENABLE1_reg_clken_3d_gde(data)                                     (0x00000080&((data)<<7))
#define SYS_CLOCK_ENABLE1_reg_clken_3d_gde_src(data)                                 ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE1_get_reg_clken_3d_gde(data)                                 ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc_shift                                      (6)
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc_mask                                       (0x00000040)
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc(data)                                      (0x00000040&((data)<<6))
#define SYS_CLOCK_ENABLE1_clk_en_iso_misc_src(data)                                  ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE1_get_clk_en_iso_misc(data)                                  ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE1_clk_en_pcr_shift                                           (5)
#define SYS_CLOCK_ENABLE1_clk_en_pcr_mask                                            (0x00000020)
#define SYS_CLOCK_ENABLE1_clk_en_pcr(data)                                           (0x00000020&((data)<<5))
#define SYS_CLOCK_ENABLE1_clk_en_pcr_src(data)                                       ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE1_get_clk_en_pcr(data)                                       ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE1_clk_en_usb0_shift                                          (4)
#define SYS_CLOCK_ENABLE1_clk_en_usb0_mask                                           (0x00000010)
#define SYS_CLOCK_ENABLE1_clk_en_usb0(data)                                          (0x00000010&((data)<<4))
#define SYS_CLOCK_ENABLE1_clk_en_usb0_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE1_get_clk_en_usb0(data)                                      ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE1_clk_en_gspi_shift                                          (3)
#define SYS_CLOCK_ENABLE1_clk_en_gspi_mask                                           (0x00000008)
#define SYS_CLOCK_ENABLE1_clk_en_gspi(data)                                          (0x00000008&((data)<<3))
#define SYS_CLOCK_ENABLE1_clk_en_gspi_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE1_get_clk_en_gspi(data)                                      ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE1_clk_en_usb1_shift                                          (2)
#define SYS_CLOCK_ENABLE1_clk_en_usb1_mask                                           (0x00000004)
#define SYS_CLOCK_ENABLE1_clk_en_usb1(data)                                          (0x00000004&((data)<<2))
#define SYS_CLOCK_ENABLE1_clk_en_usb1_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE1_get_clk_en_usb1(data)                                      ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE1_clk_en_hdmirx_shift                                        (1)
#define SYS_CLOCK_ENABLE1_clk_en_hdmirx_mask                                         (0x00000002)
#define SYS_CLOCK_ENABLE1_clk_en_hdmirx(data)                                        (0x00000002&((data)<<1))
#define SYS_CLOCK_ENABLE1_clk_en_hdmirx_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_CLOCK_ENABLE1_get_clk_en_hdmirx(data)                                    ((0x00000002&(data))>>1)
#define SYS_CLOCK_ENABLE1_clk_en_misc_shift                                          (0)
#define SYS_CLOCK_ENABLE1_clk_en_misc_mask                                           (0x00000001)
#define SYS_CLOCK_ENABLE1_clk_en_misc(data)                                          (0x00000001&((data)<<0))
#define SYS_CLOCK_ENABLE1_clk_en_misc_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_CLOCK_ENABLE1_get_clk_en_misc(data)                                      ((0x00000001&(data))>>0)


#define SYS_CLOCK_ENABLE2                                                            0x18000010
#define SYS_CLOCK_ENABLE2_reg_addr                                                   "0xB8000010"
#define SYS_CLOCK_ENABLE2_reg                                                        0xB8000010
#define set_SYS_CLOCK_ENABLE2_reg(data)   (*((volatile unsigned int*) SYS_CLOCK_ENABLE2_reg)=data)
#define get_SYS_CLOCK_ENABLE2_reg   (*((volatile unsigned int*) SYS_CLOCK_ENABLE2_reg))
#define SYS_CLOCK_ENABLE2_inst_adr                                                   "0x0004"
#define SYS_CLOCK_ENABLE2_inst                                                       0x0004
#define SYS_CLOCK_ENABLE2_clk_en_ur2_shift                                           (31)
#define SYS_CLOCK_ENABLE2_clk_en_ur2_mask                                            (0x80000000)
#define SYS_CLOCK_ENABLE2_clk_en_ur2(data)                                           (0x80000000&((data)<<31))
#define SYS_CLOCK_ENABLE2_clk_en_ur2_src(data)                                       ((0x80000000&(data))>>31)
#define SYS_CLOCK_ENABLE2_get_clk_en_ur2(data)                                       ((0x80000000&(data))>>31)
#define SYS_CLOCK_ENABLE2_clk_en_ur1_shift                                           (28)
#define SYS_CLOCK_ENABLE2_clk_en_ur1_mask                                            (0x10000000)
#define SYS_CLOCK_ENABLE2_clk_en_ur1(data)                                           (0x10000000&((data)<<28))
#define SYS_CLOCK_ENABLE2_clk_en_ur1_src(data)                                       ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE2_get_clk_en_ur1(data)                                       ((0x10000000&(data))>>28)
#define SYS_CLOCK_ENABLE2_clk_en_pwm_shift                                           (25)
#define SYS_CLOCK_ENABLE2_clk_en_pwm_mask                                            (0x02000000)
#define SYS_CLOCK_ENABLE2_clk_en_pwm(data)                                           (0x02000000&((data)<<25))
#define SYS_CLOCK_ENABLE2_clk_en_pwm_src(data)                                       ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE2_get_clk_en_pwm(data)                                       ((0x02000000&(data))>>25)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2_shift                                    (24)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2_mask                                     (0x01000000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2(data)                                    (0x01000000&((data)<<24))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_2_src(data)                                ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_2(data)                                ((0x01000000&(data))>>24)
#define SYS_CLOCK_ENABLE2_clk_en_iso_mis_shift                                       (17)
#define SYS_CLOCK_ENABLE2_clk_en_iso_mis_mask                                        (0x00020000)
#define SYS_CLOCK_ENABLE2_clk_en_iso_mis(data)                                       (0x00020000&((data)<<17))
#define SYS_CLOCK_ENABLE2_clk_en_iso_mis_src(data)                                   ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE2_get_clk_en_iso_mis(data)                                   ((0x00020000&(data))>>17)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_0_shift                                    (16)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_0_mask                                     (0x00010000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_0(data)                                    (0x00010000&((data)<<16))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_0_src(data)                                ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_0(data)                                ((0x00010000&(data))>>16)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1_shift                                    (15)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1_mask                                     (0x00008000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1(data)                                    (0x00008000&((data)<<15))
#define SYS_CLOCK_ENABLE2_clk_en_misc_i2c_1_src(data)                                ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_i2c_1(data)                                ((0x00008000&(data))>>15)
#define SYS_CLOCK_ENABLE2_clk_en_misc_pcmcia_shift                                   (14)
#define SYS_CLOCK_ENABLE2_clk_en_misc_pcmcia_mask                                    (0x00004000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_pcmcia(data)                                   (0x00004000&((data)<<14))
#define SYS_CLOCK_ENABLE2_clk_en_misc_pcmcia_src(data)                               ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_pcmcia(data)                               ((0x00004000&(data))>>14)
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc_shift                                       (13)
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc_mask                                        (0x00002000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc(data)                                       (0x00002000&((data)<<13))
#define SYS_CLOCK_ENABLE2_clk_en_misc_sc_src(data)                                   ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_sc(data)                                   ((0x00002000&(data))>>13)
#define SYS_CLOCK_ENABLE2_clk_en_misc_ir_shift                                       (12)
#define SYS_CLOCK_ENABLE2_clk_en_misc_ir_mask                                        (0x00001000)
#define SYS_CLOCK_ENABLE2_clk_en_misc_ir(data)                                       (0x00001000&((data)<<12))
#define SYS_CLOCK_ENABLE2_clk_en_misc_ir_src(data)                                   ((0x00001000&(data))>>12)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_ir(data)                                   ((0x00001000&(data))>>12)
#define SYS_CLOCK_ENABLE2_clk_en_misc_cec_shift                                      (11)
#define SYS_CLOCK_ENABLE2_clk_en_misc_cec_mask                                       (0x00000800)
#define SYS_CLOCK_ENABLE2_clk_en_misc_cec(data)                                      (0x00000800&((data)<<11))
#define SYS_CLOCK_ENABLE2_clk_en_misc_cec_src(data)                                  ((0x00000800&(data))>>11)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_cec(data)                                  ((0x00000800&(data))>>11)
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc_shift                                      (10)
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc_mask                                       (0x00000400)
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc(data)                                      (0x00000400&((data)<<10))
#define SYS_CLOCK_ENABLE2_clk_en_misc_rtc_src(data)                                  ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_rtc(data)                                  ((0x00000400&(data))>>10)
#define SYS_CLOCK_ENABLE2_clk_en_misc_vfd_shift                                      (9)
#define SYS_CLOCK_ENABLE2_clk_en_misc_vfd_mask                                       (0x00000200)
#define SYS_CLOCK_ENABLE2_clk_en_misc_vfd(data)                                      (0x00000200&((data)<<9))
#define SYS_CLOCK_ENABLE2_clk_en_misc_vfd_src(data)                                  ((0x00000200&(data))>>9)
#define SYS_CLOCK_ENABLE2_get_clk_en_misc_vfd(data)                                  ((0x00000200&(data))>>9)
#define SYS_CLOCK_ENABLE2_clk_en_me1_shift                                           (8)
#define SYS_CLOCK_ENABLE2_clk_en_me1_mask                                            (0x00000100)
#define SYS_CLOCK_ENABLE2_clk_en_me1(data)                                           (0x00000100&((data)<<8))
#define SYS_CLOCK_ENABLE2_clk_en_me1_src(data)                                       ((0x00000100&(data))>>8)
#define SYS_CLOCK_ENABLE2_get_clk_en_me1(data)                                       ((0x00000100&(data))>>8)
#define SYS_CLOCK_ENABLE2_clk_en_vde_shift                                           (7)
#define SYS_CLOCK_ENABLE2_clk_en_vde_mask                                            (0x00000080)
#define SYS_CLOCK_ENABLE2_clk_en_vde(data)                                           (0x00000080&((data)<<7))
#define SYS_CLOCK_ENABLE2_clk_en_vde_src(data)                                       ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE2_get_clk_en_vde(data)                                       ((0x00000080&(data))>>7)
#define SYS_CLOCK_ENABLE2_clk_en_ade_shift                                           (6)
#define SYS_CLOCK_ENABLE2_clk_en_ade_mask                                            (0x00000040)
#define SYS_CLOCK_ENABLE2_clk_en_ade(data)                                           (0x00000040&((data)<<6))
#define SYS_CLOCK_ENABLE2_clk_en_ade_src(data)                                       ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE2_get_clk_en_ade(data)                                       ((0x00000040&(data))>>6)
#define SYS_CLOCK_ENABLE2_clk_en_vcpu_shift                                          (5)
#define SYS_CLOCK_ENABLE2_clk_en_vcpu_mask                                           (0x00000020)
#define SYS_CLOCK_ENABLE2_clk_en_vcpu(data)                                          (0x00000020&((data)<<5))
#define SYS_CLOCK_ENABLE2_clk_en_vcpu_src(data)                                      ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE2_get_clk_en_vcpu(data)                                      ((0x00000020&(data))>>5)
#define SYS_CLOCK_ENABLE2_clk_en_acpu_shift                                          (4)
#define SYS_CLOCK_ENABLE2_clk_en_acpu_mask                                           (0x00000010)
#define SYS_CLOCK_ENABLE2_clk_en_acpu(data)                                          (0x00000010&((data)<<4))
#define SYS_CLOCK_ENABLE2_clk_en_acpu_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE2_get_clk_en_acpu(data)                                      ((0x00000010&(data))>>4)
#define SYS_CLOCK_ENABLE2_clk_en_scpu_wrap_shift                                     (3)
#define SYS_CLOCK_ENABLE2_clk_en_scpu_wrap_mask                                      (0x00000008)
#define SYS_CLOCK_ENABLE2_clk_en_scpu_wrap(data)                                     (0x00000008&((data)<<3))
#define SYS_CLOCK_ENABLE2_clk_en_scpu_wrap_src(data)                                 ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE2_get_clk_en_scpu_wrap(data)                                 ((0x00000008&(data))>>3)
#define SYS_CLOCK_ENABLE2_clk_en_scpu_shift                                          (2)
#define SYS_CLOCK_ENABLE2_clk_en_scpu_mask                                           (0x00000004)
#define SYS_CLOCK_ENABLE2_clk_en_scpu(data)                                          (0x00000004&((data)<<2))
#define SYS_CLOCK_ENABLE2_clk_en_scpu_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE2_get_clk_en_scpu(data)                                      ((0x00000004&(data))>>2)
#define SYS_CLOCK_ENABLE2_reg_clken_scpu_cssys_shift                                 (1)
#define SYS_CLOCK_ENABLE2_reg_clken_scpu_cssys_mask                                  (0x00000002)
#define SYS_CLOCK_ENABLE2_reg_clken_scpu_cssys(data)                                 (0x00000002&((data)<<1))
#define SYS_CLOCK_ENABLE2_reg_clken_scpu_cssys_src(data)                             ((0x00000002&(data))>>1)
#define SYS_CLOCK_ENABLE2_get_reg_clken_scpu_cssys(data)                             ((0x00000002&(data))>>1)


#define SYS_GROUP1_CK_EN                                                             0x18000014
#define SYS_GROUP1_CK_EN_reg_addr                                                    "0xB8000014"
#define SYS_GROUP1_CK_EN_reg                                                         0xB8000014
#define set_SYS_GROUP1_CK_EN_reg(data)   (*((volatile unsigned int*) SYS_GROUP1_CK_EN_reg)=data)
#define get_SYS_GROUP1_CK_EN_reg   (*((volatile unsigned int*) SYS_GROUP1_CK_EN_reg))
#define SYS_GROUP1_CK_EN_inst_adr                                                    "0x0005"
#define SYS_GROUP1_CK_EN_inst                                                        0x0005
#define SYS_GROUP1_CK_EN_CLKEN_TVSB1_shift                                           (31)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB1_mask                                            (0x80000000)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB1(data)                                           (0x80000000&((data)<<31))
#define SYS_GROUP1_CK_EN_CLKEN_TVSB1_src(data)                                       ((0x80000000&(data))>>31)
#define SYS_GROUP1_CK_EN_get_CLKEN_TVSB1(data)                                       ((0x80000000&(data))>>31)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB2_shift                                           (30)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB2_mask                                            (0x40000000)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB2(data)                                           (0x40000000&((data)<<30))
#define SYS_GROUP1_CK_EN_CLKEN_TVSB2_src(data)                                       ((0x40000000&(data))>>30)
#define SYS_GROUP1_CK_EN_get_CLKEN_TVSB2(data)                                       ((0x40000000&(data))>>30)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB3_shift                                           (29)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB3_mask                                            (0x20000000)
#define SYS_GROUP1_CK_EN_CLKEN_TVSB3(data)                                           (0x20000000&((data)<<29))
#define SYS_GROUP1_CK_EN_CLKEN_TVSB3_src(data)                                       ((0x20000000&(data))>>29)
#define SYS_GROUP1_CK_EN_get_CLKEN_TVSB3(data)                                       ((0x20000000&(data))>>29)
#define SYS_GROUP1_CK_EN_CLKEN_TM_shift                                              (28)
#define SYS_GROUP1_CK_EN_CLKEN_TM_mask                                               (0x10000000)
#define SYS_GROUP1_CK_EN_CLKEN_TM(data)                                              (0x10000000&((data)<<28))
#define SYS_GROUP1_CK_EN_CLKEN_TM_src(data)                                          ((0x10000000&(data))>>28)
#define SYS_GROUP1_CK_EN_get_CLKEN_TM(data)                                          ((0x10000000&(data))>>28)
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_VD_shift                                        (27)
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_VD_mask                                         (0x08000000)
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_VD(data)                                        (0x08000000&((data)<<27))
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_VD_src(data)                                    ((0x08000000&(data))>>27)
#define SYS_GROUP1_CK_EN_get_CLKEN_ATVIN_VD(data)                                    ((0x08000000&(data))>>27)
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_IFD_shift                                       (26)
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_IFD_mask                                        (0x04000000)
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_IFD(data)                                       (0x04000000&((data)<<26))
#define SYS_GROUP1_CK_EN_CLKEN_ATVIN_IFD_src(data)                                   ((0x04000000&(data))>>26)
#define SYS_GROUP1_CK_EN_get_CLKEN_ATVIN_IFD(data)                                   ((0x04000000&(data))>>26)
#define SYS_GROUP1_CK_EN_CLKEN_OSDCOMP_shift                                         (25)
#define SYS_GROUP1_CK_EN_CLKEN_OSDCOMP_mask                                          (0x02000000)
#define SYS_GROUP1_CK_EN_CLKEN_OSDCOMP(data)                                         (0x02000000&((data)<<25))
#define SYS_GROUP1_CK_EN_CLKEN_OSDCOMP_src(data)                                     ((0x02000000&(data))>>25)
#define SYS_GROUP1_CK_EN_get_CLKEN_OSDCOMP(data)                                     ((0x02000000&(data))>>25)
#define SYS_GROUP1_CK_EN_CLKEN_APLL_ADC_shift                                        (24)
#define SYS_GROUP1_CK_EN_CLKEN_APLL_ADC_mask                                         (0x01000000)
#define SYS_GROUP1_CK_EN_CLKEN_APLL_ADC(data)                                        (0x01000000&((data)<<24))
#define SYS_GROUP1_CK_EN_CLKEN_APLL_ADC_src(data)                                    ((0x01000000&(data))>>24)
#define SYS_GROUP1_CK_EN_get_CLKEN_APLL_ADC(data)                                    ((0x01000000&(data))>>24)
#define SYS_GROUP1_CK_EN_CLKEN_IF_DEMOD_shift                                        (23)
#define SYS_GROUP1_CK_EN_CLKEN_IF_DEMOD_mask                                         (0x00800000)
#define SYS_GROUP1_CK_EN_CLKEN_IF_DEMOD(data)                                        (0x00800000&((data)<<23))
#define SYS_GROUP1_CK_EN_CLKEN_IF_DEMOD_src(data)                                    ((0x00800000&(data))>>23)
#define SYS_GROUP1_CK_EN_get_CLKEN_IF_DEMOD(data)                                    ((0x00800000&(data))>>23)
#define SYS_GROUP1_CK_EN_CLKEN_DISP2TVE_shift                                        (22)
#define SYS_GROUP1_CK_EN_CLKEN_DISP2TVE_mask                                         (0x00400000)
#define SYS_GROUP1_CK_EN_CLKEN_DISP2TVE(data)                                        (0x00400000&((data)<<22))
#define SYS_GROUP1_CK_EN_CLKEN_DISP2TVE_src(data)                                    ((0x00400000&(data))>>22)
#define SYS_GROUP1_CK_EN_get_CLKEN_DISP2TVE(data)                                    ((0x00400000&(data))>>22)
#define SYS_GROUP1_CK_EN_CLKEN_BISTREG_shift                                         (21)
#define SYS_GROUP1_CK_EN_CLKEN_BISTREG_mask                                          (0x00200000)
#define SYS_GROUP1_CK_EN_CLKEN_BISTREG(data)                                         (0x00200000&((data)<<21))
#define SYS_GROUP1_CK_EN_CLKEN_BISTREG_src(data)                                     ((0x00200000&(data))>>21)
#define SYS_GROUP1_CK_EN_get_CLKEN_BISTREG(data)                                     ((0x00200000&(data))>>21)
#define SYS_GROUP1_CK_EN_CLKEN_VBIS0_shift                                           (20)
#define SYS_GROUP1_CK_EN_CLKEN_VBIS0_mask                                            (0x00100000)
#define SYS_GROUP1_CK_EN_CLKEN_VBIS0(data)                                           (0x00100000&((data)<<20))
#define SYS_GROUP1_CK_EN_CLKEN_VBIS0_src(data)                                       ((0x00100000&(data))>>20)
#define SYS_GROUP1_CK_EN_get_CLKEN_VBIS0(data)                                       ((0x00100000&(data))>>20)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_128FS_shift                                (19)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_128FS_mask                                 (0x00080000)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_128FS(data)                                (0x00080000&((data)<<19))
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_128FS_src(data)                            ((0x00080000&(data))>>19)
#define SYS_GROUP1_CK_EN_get_CLKEN_AUDIO_DAAD_128FS(data)                            ((0x00080000&(data))>>19)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_256FS_shift                                (18)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_256FS_mask                                 (0x00040000)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_256FS(data)                                (0x00040000&((data)<<18))
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_DAAD_256FS_src(data)                            ((0x00040000&(data))>>18)
#define SYS_GROUP1_CK_EN_get_CLKEN_AUDIO_DAAD_256FS(data)                            ((0x00040000&(data))>>18)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_PRE512FS_shift                                  (17)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_PRE512FS_mask                                   (0x00020000)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_PRE512FS(data)                                  (0x00020000&((data)<<17))
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO_PRE512FS_src(data)                              ((0x00020000&(data))>>17)
#define SYS_GROUP1_CK_EN_get_CLKEN_AUDIO_PRE512FS(data)                              ((0x00020000&(data))>>17)
#define SYS_GROUP1_CK_EN_CLKEN_IFADC_shift                                           (16)
#define SYS_GROUP1_CK_EN_CLKEN_IFADC_mask                                            (0x00010000)
#define SYS_GROUP1_CK_EN_CLKEN_IFADC(data)                                           (0x00010000&((data)<<16))
#define SYS_GROUP1_CK_EN_CLKEN_IFADC_src(data)                                       ((0x00010000&(data))>>16)
#define SYS_GROUP1_CK_EN_get_CLKEN_IFADC(data)                                       ((0x00010000&(data))>>16)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_512FS_shift                                    (15)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_512FS_mask                                     (0x00008000)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_512FS(data)                                    (0x00008000&((data)<<15))
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_512FS_src(data)                                ((0x00008000&(data))>>15)
#define SYS_GROUP1_CK_EN_get_CLKEN_AUDIO2_512FS(data)                                ((0x00008000&(data))>>15)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_256FS_shift                               (14)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_256FS_mask                                (0x00004000)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_256FS(data)                               (0x00004000&((data)<<14))
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_256FS_src(data)                           ((0x00004000&(data))>>14)
#define SYS_GROUP1_CK_EN_get_CLKEN_AUDIO2_DAAD_256FS(data)                           ((0x00004000&(data))>>14)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_128FS_shift                               (13)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_128FS_mask                                (0x00002000)
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_128FS(data)                               (0x00002000&((data)<<13))
#define SYS_GROUP1_CK_EN_CLKEN_AUDIO2_DAAD_128FS_src(data)                           ((0x00002000&(data))>>13)
#define SYS_GROUP1_CK_EN_get_CLKEN_AUDIO2_DAAD_128FS(data)                           ((0x00002000&(data))>>13)
#define SYS_GROUP1_CK_EN_CLKEN_PADMUX_shift                                          (12)
#define SYS_GROUP1_CK_EN_CLKEN_PADMUX_mask                                           (0x00001000)
#define SYS_GROUP1_CK_EN_CLKEN_PADMUX(data)                                          (0x00001000&((data)<<12))
#define SYS_GROUP1_CK_EN_CLKEN_PADMUX_src(data)                                      ((0x00001000&(data))>>12)
#define SYS_GROUP1_CK_EN_get_CLKEN_PADMUX(data)                                      ((0x00001000&(data))>>12)
#define SYS_GROUP1_CK_EN_CLKEN_DTV_DEMOD_shift                                       (11)
#define SYS_GROUP1_CK_EN_CLKEN_DTV_DEMOD_mask                                        (0x00000800)
#define SYS_GROUP1_CK_EN_CLKEN_DTV_DEMOD(data)                                       (0x00000800&((data)<<11))
#define SYS_GROUP1_CK_EN_CLKEN_DTV_DEMOD_src(data)                                   ((0x00000800&(data))>>11)
#define SYS_GROUP1_CK_EN_get_CLKEN_DTV_DEMOD(data)                                   ((0x00000800&(data))>>11)
#define SYS_GROUP1_CK_EN_clk_en_akl_shift                                            (10)
#define SYS_GROUP1_CK_EN_clk_en_akl_mask                                             (0x00000400)
#define SYS_GROUP1_CK_EN_clk_en_akl(data)                                            (0x00000400&((data)<<10))
#define SYS_GROUP1_CK_EN_clk_en_akl_src(data)                                        ((0x00000400&(data))>>10)
#define SYS_GROUP1_CK_EN_get_clk_en_akl(data)                                        ((0x00000400&(data))>>10)
#define SYS_GROUP1_CK_EN_clk_en_dsc_shift                                            (9)
#define SYS_GROUP1_CK_EN_clk_en_dsc_mask                                             (0x00000200)
#define SYS_GROUP1_CK_EN_clk_en_dsc(data)                                            (0x00000200&((data)<<9))
#define SYS_GROUP1_CK_EN_clk_en_dsc_src(data)                                        ((0x00000200&(data))>>9)
#define SYS_GROUP1_CK_EN_get_clk_en_dsc(data)                                        ((0x00000200&(data))>>9)
#define SYS_GROUP1_CK_EN_clk_en_sce_shift                                            (8)
#define SYS_GROUP1_CK_EN_clk_en_sce_mask                                             (0x00000100)
#define SYS_GROUP1_CK_EN_clk_en_sce(data)                                            (0x00000100&((data)<<8))
#define SYS_GROUP1_CK_EN_clk_en_sce_src(data)                                        ((0x00000100&(data))>>8)
#define SYS_GROUP1_CK_EN_get_clk_en_sce(data)                                        ((0x00000100&(data))>>8)
#define SYS_GROUP1_CK_EN_clk_en_kt_shift                                             (7)
#define SYS_GROUP1_CK_EN_clk_en_kt_mask                                              (0x00000080)
#define SYS_GROUP1_CK_EN_clk_en_kt(data)                                             (0x00000080&((data)<<7))
#define SYS_GROUP1_CK_EN_clk_en_kt_src(data)                                         ((0x00000080&(data))>>7)
#define SYS_GROUP1_CK_EN_get_clk_en_kt(data)                                         ((0x00000080&(data))>>7)
#define SYS_GROUP1_CK_EN_CLKEN_DDC_shift                                             (6)
#define SYS_GROUP1_CK_EN_CLKEN_DDC_mask                                              (0x00000040)
#define SYS_GROUP1_CK_EN_CLKEN_DDC(data)                                             (0x00000040&((data)<<6))
#define SYS_GROUP1_CK_EN_CLKEN_DDC_src(data)                                         ((0x00000040&(data))>>6)
#define SYS_GROUP1_CK_EN_get_CLKEN_DDC(data)                                         ((0x00000040&(data))>>6)
#define SYS_GROUP1_CK_EN_CLKEN_VODMA_shift                                           (5)
#define SYS_GROUP1_CK_EN_CLKEN_VODMA_mask                                            (0x00000020)
#define SYS_GROUP1_CK_EN_CLKEN_VODMA(data)                                           (0x00000020&((data)<<5))
#define SYS_GROUP1_CK_EN_CLKEN_VODMA_src(data)                                       ((0x00000020&(data))>>5)
#define SYS_GROUP1_CK_EN_get_CLKEN_VODMA(data)                                       ((0x00000020&(data))>>5)
#define SYS_GROUP1_CK_EN_CLKEN_DISPIM_shift                                          (4)
#define SYS_GROUP1_CK_EN_CLKEN_DISPIM_mask                                           (0x00000010)
#define SYS_GROUP1_CK_EN_CLKEN_DISPIM(data)                                          (0x00000010&((data)<<4))
#define SYS_GROUP1_CK_EN_CLKEN_DISPIM_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_GROUP1_CK_EN_get_CLKEN_DISPIM(data)                                      ((0x00000010&(data))>>4)
#define SYS_GROUP1_CK_EN_CLKEN_DISP_shift                                            (3)
#define SYS_GROUP1_CK_EN_CLKEN_DISP_mask                                             (0x00000008)
#define SYS_GROUP1_CK_EN_CLKEN_DISP(data)                                            (0x00000008&((data)<<3))
#define SYS_GROUP1_CK_EN_CLKEN_DISP_src(data)                                        ((0x00000008&(data))>>3)
#define SYS_GROUP1_CK_EN_get_CLKEN_DISP(data)                                        ((0x00000008&(data))>>3)
#define SYS_GROUP1_CK_EN_CLKEN_PLLREG_shift                                          (2)
#define SYS_GROUP1_CK_EN_CLKEN_PLLREG_mask                                           (0x00000004)
#define SYS_GROUP1_CK_EN_CLKEN_PLLREG(data)                                          (0x00000004&((data)<<2))
#define SYS_GROUP1_CK_EN_CLKEN_PLLREG_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_GROUP1_CK_EN_get_CLKEN_PLLREG(data)                                      ((0x00000004&(data))>>2)
#define SYS_GROUP1_CK_EN_clk_en_kcpu_shift                                           (1)
#define SYS_GROUP1_CK_EN_clk_en_kcpu_mask                                            (0x00000002)
#define SYS_GROUP1_CK_EN_clk_en_kcpu(data)                                           (0x00000002&((data)<<1))
#define SYS_GROUP1_CK_EN_clk_en_kcpu_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_GROUP1_CK_EN_get_clk_en_kcpu(data)                                       ((0x00000002&(data))>>1)
#define SYS_GROUP1_CK_EN_clk_en_sb2_shift                                            (0)
#define SYS_GROUP1_CK_EN_clk_en_sb2_mask                                             (0x00000001)
#define SYS_GROUP1_CK_EN_clk_en_sb2(data)                                            (0x00000001&((data)<<0))
#define SYS_GROUP1_CK_EN_clk_en_sb2_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_GROUP1_CK_EN_get_clk_en_sb2(data)                                        ((0x00000001&(data))>>0)


#define SYS_GROUP1_CK_SEL                                                            0x18000018
#define SYS_GROUP1_CK_SEL_reg_addr                                                   "0xB8000018"
#define SYS_GROUP1_CK_SEL_reg                                                        0xB8000018
#define set_SYS_GROUP1_CK_SEL_reg(data)   (*((volatile unsigned int*) SYS_GROUP1_CK_SEL_reg)=data)
#define get_SYS_GROUP1_CK_SEL_reg   (*((volatile unsigned int*) SYS_GROUP1_CK_SEL_reg))
#define SYS_GROUP1_CK_SEL_inst_adr                                                   "0x0006"
#define SYS_GROUP1_CK_SEL_inst                                                       0x0006
#define SYS_GROUP1_CK_SEL_ve_rif_use_p2clk_shift                                     (26)
#define SYS_GROUP1_CK_SEL_ve_rif_use_p2clk_mask                                      (0x04000000)
#define SYS_GROUP1_CK_SEL_ve_rif_use_p2clk(data)                                     (0x04000000&((data)<<26))
#define SYS_GROUP1_CK_SEL_ve_rif_use_p2clk_src(data)                                 ((0x04000000&(data))>>26)
#define SYS_GROUP1_CK_SEL_get_ve_rif_use_p2clk(data)                                 ((0x04000000&(data))>>26)
#define SYS_GROUP1_CK_SEL_EPI_DBG_CLKSEL_shift                                       (25)
#define SYS_GROUP1_CK_SEL_EPI_DBG_CLKSEL_mask                                        (0x02000000)
#define SYS_GROUP1_CK_SEL_EPI_DBG_CLKSEL(data)                                       (0x02000000&((data)<<25))
#define SYS_GROUP1_CK_SEL_EPI_DBG_CLKSEL_src(data)                                   ((0x02000000&(data))>>25)
#define SYS_GROUP1_CK_SEL_get_EPI_DBG_CLKSEL(data)                                   ((0x02000000&(data))>>25)
#define SYS_GROUP1_CK_SEL_EPI_DIV_CLKSEL_shift                                       (23)
#define SYS_GROUP1_CK_SEL_EPI_DIV_CLKSEL_mask                                        (0x01800000)
#define SYS_GROUP1_CK_SEL_EPI_DIV_CLKSEL(data)                                       (0x01800000&((data)<<23))
#define SYS_GROUP1_CK_SEL_EPI_DIV_CLKSEL_src(data)                                   ((0x01800000&(data))>>23)
#define SYS_GROUP1_CK_SEL_get_EPI_DIV_CLKSEL(data)                                   ((0x01800000&(data))>>23)
#define SYS_GROUP1_CK_SEL_ATVIN_CLK_SEL_shift                                        (17)
#define SYS_GROUP1_CK_SEL_ATVIN_CLK_SEL_mask                                         (0x00020000)
#define SYS_GROUP1_CK_SEL_ATVIN_CLK_SEL(data)                                        (0x00020000&((data)<<17))
#define SYS_GROUP1_CK_SEL_ATVIN_CLK_SEL_src(data)                                    ((0x00020000&(data))>>17)
#define SYS_GROUP1_CK_SEL_get_ATVIN_CLK_SEL(data)                                    ((0x00020000&(data))>>17)
#define SYS_GROUP1_CK_SEL_ATVIN_VD_CLK_SEL_shift                                     (16)
#define SYS_GROUP1_CK_SEL_ATVIN_VD_CLK_SEL_mask                                      (0x00010000)
#define SYS_GROUP1_CK_SEL_ATVIN_VD_CLK_SEL(data)                                     (0x00010000&((data)<<16))
#define SYS_GROUP1_CK_SEL_ATVIN_VD_CLK_SEL_src(data)                                 ((0x00010000&(data))>>16)
#define SYS_GROUP1_CK_SEL_get_ATVIN_VD_CLK_SEL(data)                                 ((0x00010000&(data))>>16)
#define SYS_GROUP1_CK_SEL_ATVIN_VDADC_TVE_CLK_SEL_shift                              (15)
#define SYS_GROUP1_CK_SEL_ATVIN_VDADC_TVE_CLK_SEL_mask                               (0x00008000)
#define SYS_GROUP1_CK_SEL_ATVIN_VDADC_TVE_CLK_SEL(data)                              (0x00008000&((data)<<15))
#define SYS_GROUP1_CK_SEL_ATVIN_VDADC_TVE_CLK_SEL_src(data)                          ((0x00008000&(data))>>15)
#define SYS_GROUP1_CK_SEL_get_ATVIN_VDADC_TVE_CLK_SEL(data)                          ((0x00008000&(data))>>15)
#define SYS_GROUP1_CK_SEL_VDEC_X27_CLKSEL_shift                                      (8)
#define SYS_GROUP1_CK_SEL_VDEC_X27_CLKSEL_mask                                       (0x00000100)
#define SYS_GROUP1_CK_SEL_VDEC_X27_CLKSEL(data)                                      (0x00000100&((data)<<8))
#define SYS_GROUP1_CK_SEL_VDEC_X27_CLKSEL_src(data)                                  ((0x00000100&(data))>>8)
#define SYS_GROUP1_CK_SEL_get_VDEC_X27_CLKSEL(data)                                  ((0x00000100&(data))>>8)
#define SYS_GROUP1_CK_SEL_VBIS0_YPPSEL_shift                                         (5)
#define SYS_GROUP1_CK_SEL_VBIS0_YPPSEL_mask                                          (0x00000020)
#define SYS_GROUP1_CK_SEL_VBIS0_YPPSEL(data)                                         (0x00000020&((data)<<5))
#define SYS_GROUP1_CK_SEL_VBIS0_YPPSEL_src(data)                                     ((0x00000020&(data))>>5)
#define SYS_GROUP1_CK_SEL_get_VBIS0_YPPSEL(data)                                     ((0x00000020&(data))>>5)
#define SYS_GROUP1_CK_SEL_INV_VBIS0_CLK_shift                                        (4)
#define SYS_GROUP1_CK_SEL_INV_VBIS0_CLK_mask                                         (0x00000010)
#define SYS_GROUP1_CK_SEL_INV_VBIS0_CLK(data)                                        (0x00000010&((data)<<4))
#define SYS_GROUP1_CK_SEL_INV_VBIS0_CLK_src(data)                                    ((0x00000010&(data))>>4)
#define SYS_GROUP1_CK_SEL_get_INV_VBIS0_CLK(data)                                    ((0x00000010&(data))>>4)
#define SYS_GROUP1_CK_SEL_sclk_sel_shift                                             (0)
#define SYS_GROUP1_CK_SEL_sclk_sel_mask                                              (0x00000001)
#define SYS_GROUP1_CK_SEL_sclk_sel(data)                                             (0x00000001&((data)<<0))
#define SYS_GROUP1_CK_SEL_sclk_sel_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_GROUP1_CK_SEL_get_sclk_sel(data)                                         ((0x00000001&(data))>>0)


#define SYS_TVE_CK_SEL                                                               0x1800001C
#define SYS_TVE_CK_SEL_reg_addr                                                      "0xB800001C"
#define SYS_TVE_CK_SEL_reg                                                           0xB800001C
#define set_SYS_TVE_CK_SEL_reg(data)   (*((volatile unsigned int*) SYS_TVE_CK_SEL_reg)=data)
#define get_SYS_TVE_CK_SEL_reg   (*((volatile unsigned int*) SYS_TVE_CK_SEL_reg))
#define SYS_TVE_CK_SEL_inst_adr                                                      "0x0007"
#define SYS_TVE_CK_SEL_inst                                                          0x0007
#define SYS_TVE_CK_SEL_write_en5_shift                                               (12)
#define SYS_TVE_CK_SEL_write_en5_mask                                                (0x00001000)
#define SYS_TVE_CK_SEL_write_en5(data)                                               (0x00001000&((data)<<12))
#define SYS_TVE_CK_SEL_write_en5_src(data)                                           ((0x00001000&(data))>>12)
#define SYS_TVE_CK_SEL_get_write_en5(data)                                           ((0x00001000&(data))>>12)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2_shift                                   (11)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2_mask                                    (0x00000800)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2(data)                                   (0x00000800&((data)<<11))
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel2_src(data)                               ((0x00000800&(data))>>11)
#define SYS_TVE_CK_SEL_get_clk_tve_p_vo_clk_sel2(data)                               ((0x00000800&(data))>>11)
#define SYS_TVE_CK_SEL_write_en4_shift                                               (10)
#define SYS_TVE_CK_SEL_write_en4_mask                                                (0x00000400)
#define SYS_TVE_CK_SEL_write_en4(data)                                               (0x00000400&((data)<<10))
#define SYS_TVE_CK_SEL_write_en4_src(data)                                           ((0x00000400&(data))>>10)
#define SYS_TVE_CK_SEL_get_write_en4(data)                                           ((0x00000400&(data))>>10)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel_shift                                    (9)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel_mask                                     (0x00000200)
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel(data)                                    (0x00000200&((data)<<9))
#define SYS_TVE_CK_SEL_clk_tve_p_vo_clk_sel_src(data)                                ((0x00000200&(data))>>9)
#define SYS_TVE_CK_SEL_get_clk_tve_p_vo_clk_sel(data)                                ((0x00000200&(data))>>9)
#define SYS_TVE_CK_SEL_write_en3_shift                                               (8)
#define SYS_TVE_CK_SEL_write_en3_mask                                                (0x00000100)
#define SYS_TVE_CK_SEL_write_en3(data)                                               (0x00000100&((data)<<8))
#define SYS_TVE_CK_SEL_write_en3_src(data)                                           ((0x00000100&(data))>>8)
#define SYS_TVE_CK_SEL_get_write_en3(data)                                           ((0x00000100&(data))>>8)
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv_shift                                          (7)
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv_mask                                           (0x00000080)
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv(data)                                          (0x00000080&((data)<<7))
#define SYS_TVE_CK_SEL_hdmi_phy_ckinv_src(data)                                      ((0x00000080&(data))>>7)
#define SYS_TVE_CK_SEL_get_hdmi_phy_ckinv(data)                                      ((0x00000080&(data))>>7)
#define SYS_TVE_CK_SEL_write_en2_shift                                               (6)
#define SYS_TVE_CK_SEL_write_en2_mask                                                (0x00000040)
#define SYS_TVE_CK_SEL_write_en2(data)                                               (0x00000040&((data)<<6))
#define SYS_TVE_CK_SEL_write_en2_src(data)                                           ((0x00000040&(data))>>6)
#define SYS_TVE_CK_SEL_get_write_en2(data)                                           ((0x00000040&(data))>>6)
#define SYS_TVE_CK_SEL_dac2_ckinv_shift                                              (3)
#define SYS_TVE_CK_SEL_dac2_ckinv_mask                                               (0x00000008)
#define SYS_TVE_CK_SEL_dac2_ckinv(data)                                              (0x00000008&((data)<<3))
#define SYS_TVE_CK_SEL_dac2_ckinv_src(data)                                          ((0x00000008&(data))>>3)
#define SYS_TVE_CK_SEL_get_dac2_ckinv(data)                                          ((0x00000008&(data))>>3)
#define SYS_TVE_CK_SEL_dac1_ckinv_shift                                              (2)
#define SYS_TVE_CK_SEL_dac1_ckinv_mask                                               (0x00000004)
#define SYS_TVE_CK_SEL_dac1_ckinv(data)                                              (0x00000004&((data)<<2))
#define SYS_TVE_CK_SEL_dac1_ckinv_src(data)                                          ((0x00000004&(data))>>2)
#define SYS_TVE_CK_SEL_get_dac1_ckinv(data)                                          ((0x00000004&(data))>>2)
#define SYS_TVE_CK_SEL_write_en1_shift                                               (1)
#define SYS_TVE_CK_SEL_write_en1_mask                                                (0x00000002)
#define SYS_TVE_CK_SEL_write_en1(data)                                               (0x00000002&((data)<<1))
#define SYS_TVE_CK_SEL_write_en1_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_TVE_CK_SEL_get_write_en1(data)                                           ((0x00000002&(data))>>1)
#define SYS_TVE_CK_SEL_tveck_mix_sel_shift                                           (0)
#define SYS_TVE_CK_SEL_tveck_mix_sel_mask                                            (0x00000001)
#define SYS_TVE_CK_SEL_tveck_mix_sel(data)                                           (0x00000001&((data)<<0))
#define SYS_TVE_CK_SEL_tveck_mix_sel_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_TVE_CK_SEL_get_tveck_mix_sel(data)                                       ((0x00000001&(data))>>0)


#define SYS_DISP_PLL_DIV                                                             0x18000020
#define SYS_DISP_PLL_DIV_reg_addr                                                    "0xB8000020"
#define SYS_DISP_PLL_DIV_reg                                                         0xB8000020
#define set_SYS_DISP_PLL_DIV_reg(data)   (*((volatile unsigned int*) SYS_DISP_PLL_DIV_reg)=data)
#define get_SYS_DISP_PLL_DIV_reg   (*((volatile unsigned int*) SYS_DISP_PLL_DIV_reg))
#define SYS_DISP_PLL_DIV_inst_adr                                                    "0x0008"
#define SYS_DISP_PLL_DIV_inst                                                        0x0008
#define SYS_DISP_PLL_DIV_write_en2_shift                                             (11)
#define SYS_DISP_PLL_DIV_write_en2_mask                                              (0x00000800)
#define SYS_DISP_PLL_DIV_write_en2(data)                                             (0x00000800&((data)<<11))
#define SYS_DISP_PLL_DIV_write_en2_src(data)                                         ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV_get_write_en2(data)                                         ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV_dac2_div_shift                                              (6)
#define SYS_DISP_PLL_DIV_dac2_div_mask                                               (0x000007C0)
#define SYS_DISP_PLL_DIV_dac2_div(data)                                              (0x000007C0&((data)<<6))
#define SYS_DISP_PLL_DIV_dac2_div_src(data)                                          ((0x000007C0&(data))>>6)
#define SYS_DISP_PLL_DIV_get_dac2_div(data)                                          ((0x000007C0&(data))>>6)
#define SYS_DISP_PLL_DIV_write_en1_shift                                             (5)
#define SYS_DISP_PLL_DIV_write_en1_mask                                              (0x00000020)
#define SYS_DISP_PLL_DIV_write_en1(data)                                             (0x00000020&((data)<<5))
#define SYS_DISP_PLL_DIV_write_en1_src(data)                                         ((0x00000020&(data))>>5)
#define SYS_DISP_PLL_DIV_get_write_en1(data)                                         ((0x00000020&(data))>>5)
#define SYS_DISP_PLL_DIV_dac1_div_shift                                              (0)
#define SYS_DISP_PLL_DIV_dac1_div_mask                                               (0x0000001F)
#define SYS_DISP_PLL_DIV_dac1_div(data)                                              (0x0000001F&((data)<<0))
#define SYS_DISP_PLL_DIV_dac1_div_src(data)                                          ((0x0000001F&(data))>>0)
#define SYS_DISP_PLL_DIV_get_dac1_div(data)                                          ((0x0000001F&(data))>>0)


#define SYS_DISP_PLL_DIV2                                                            0x18000024
#define SYS_DISP_PLL_DIV2_reg_addr                                                   "0xB8000024"
#define SYS_DISP_PLL_DIV2_reg                                                        0xB8000024
#define set_SYS_DISP_PLL_DIV2_reg(data)   (*((volatile unsigned int*) SYS_DISP_PLL_DIV2_reg)=data)
#define get_SYS_DISP_PLL_DIV2_reg   (*((volatile unsigned int*) SYS_DISP_PLL_DIV2_reg))
#define SYS_DISP_PLL_DIV2_inst_adr                                                   "0x0009"
#define SYS_DISP_PLL_DIV2_inst                                                       0x0009
#define SYS_DISP_PLL_DIV2_write_en11_shift                                           (24)
#define SYS_DISP_PLL_DIV2_write_en11_mask                                            (0x01000000)
#define SYS_DISP_PLL_DIV2_write_en11(data)                                           (0x01000000&((data)<<24))
#define SYS_DISP_PLL_DIV2_write_en11_src(data)                                       ((0x01000000&(data))>>24)
#define SYS_DISP_PLL_DIV2_get_write_en11(data)                                       ((0x01000000&(data))>>24)
#define SYS_DISP_PLL_DIV2_hdmi_deep_clk_sel_shift                                    (23)
#define SYS_DISP_PLL_DIV2_hdmi_deep_clk_sel_mask                                     (0x00800000)
#define SYS_DISP_PLL_DIV2_hdmi_deep_clk_sel(data)                                    (0x00800000&((data)<<23))
#define SYS_DISP_PLL_DIV2_hdmi_deep_clk_sel_src(data)                                ((0x00800000&(data))>>23)
#define SYS_DISP_PLL_DIV2_get_hdmi_deep_clk_sel(data)                                ((0x00800000&(data))>>23)
#define SYS_DISP_PLL_DIV2_write_en10_shift                                           (22)
#define SYS_DISP_PLL_DIV2_write_en10_mask                                            (0x00400000)
#define SYS_DISP_PLL_DIV2_write_en10(data)                                           (0x00400000&((data)<<22))
#define SYS_DISP_PLL_DIV2_write_en10_src(data)                                       ((0x00400000&(data))>>22)
#define SYS_DISP_PLL_DIV2_get_write_en10(data)                                       ((0x00400000&(data))>>22)
#define SYS_DISP_PLL_DIV2_tve_i_div_shift                                            (20)
#define SYS_DISP_PLL_DIV2_tve_i_div_mask                                             (0x00300000)
#define SYS_DISP_PLL_DIV2_tve_i_div(data)                                            (0x00300000&((data)<<20))
#define SYS_DISP_PLL_DIV2_tve_i_div_src(data)                                        ((0x00300000&(data))>>20)
#define SYS_DISP_PLL_DIV2_get_tve_i_div(data)                                        ((0x00300000&(data))>>20)
#define SYS_DISP_PLL_DIV2_write_en9_shift                                            (19)
#define SYS_DISP_PLL_DIV2_write_en9_mask                                             (0x00080000)
#define SYS_DISP_PLL_DIV2_write_en9(data)                                            (0x00080000&((data)<<19))
#define SYS_DISP_PLL_DIV2_write_en9_src(data)                                        ((0x00080000&(data))>>19)
#define SYS_DISP_PLL_DIV2_get_write_en9(data)                                        ((0x00080000&(data))>>19)
#define SYS_DISP_PLL_DIV2_hdmi_tmds_div_shift                                        (17)
#define SYS_DISP_PLL_DIV2_hdmi_tmds_div_mask                                         (0x00060000)
#define SYS_DISP_PLL_DIV2_hdmi_tmds_div(data)                                        (0x00060000&((data)<<17))
#define SYS_DISP_PLL_DIV2_hdmi_tmds_div_src(data)                                    ((0x00060000&(data))>>17)
#define SYS_DISP_PLL_DIV2_get_hdmi_tmds_div(data)                                    ((0x00060000&(data))>>17)
#define SYS_DISP_PLL_DIV2_write_en8_shift                                            (16)
#define SYS_DISP_PLL_DIV2_write_en8_mask                                             (0x00010000)
#define SYS_DISP_PLL_DIV2_write_en8(data)                                            (0x00010000&((data)<<16))
#define SYS_DISP_PLL_DIV2_write_en8_src(data)                                        ((0x00010000&(data))>>16)
#define SYS_DISP_PLL_DIV2_get_write_en8(data)                                        ((0x00010000&(data))>>16)
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2_shift                                     (15)
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2_mask                                      (0x00008000)
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2(data)                                     (0x00008000&((data)<<15))
#define SYS_DISP_PLL_DIV2_sel_plldisp_clk2_src(data)                                 ((0x00008000&(data))>>15)
#define SYS_DISP_PLL_DIV2_get_sel_plldisp_clk2(data)                                 ((0x00008000&(data))>>15)
#define SYS_DISP_PLL_DIV2_write_en7_shift                                            (14)
#define SYS_DISP_PLL_DIV2_write_en7_mask                                             (0x00004000)
#define SYS_DISP_PLL_DIV2_write_en7(data)                                            (0x00004000&((data)<<14))
#define SYS_DISP_PLL_DIV2_write_en7_src(data)                                        ((0x00004000&(data))>>14)
#define SYS_DISP_PLL_DIV2_get_write_en7(data)                                        ((0x00004000&(data))>>14)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk_shift                                      (13)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk_mask                                       (0x00002000)
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk(data)                                      (0x00002000&((data)<<13))
#define SYS_DISP_PLL_DIV2_sel_pllhdmi_clk_src(data)                                  ((0x00002000&(data))>>13)
#define SYS_DISP_PLL_DIV2_get_sel_pllhdmi_clk(data)                                  ((0x00002000&(data))>>13)
#define SYS_DISP_PLL_DIV2_write_en6_shift                                            (12)
#define SYS_DISP_PLL_DIV2_write_en6_mask                                             (0x00001000)
#define SYS_DISP_PLL_DIV2_write_en6(data)                                            (0x00001000&((data)<<12))
#define SYS_DISP_PLL_DIV2_write_en6_src(data)                                        ((0x00001000&(data))>>12)
#define SYS_DISP_PLL_DIV2_get_write_en6(data)                                        ((0x00001000&(data))>>12)
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat_shift                                      (11)
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat_mask                                       (0x00000800)
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat(data)                                      (0x00000800&((data)<<11))
#define SYS_DISP_PLL_DIV2_hdmi_pxl_repeat_src(data)                                  ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV2_get_hdmi_pxl_repeat(data)                                  ((0x00000800&(data))>>11)
#define SYS_DISP_PLL_DIV2_write_en5_shift                                            (10)
#define SYS_DISP_PLL_DIV2_write_en5_mask                                             (0x00000400)
#define SYS_DISP_PLL_DIV2_write_en5(data)                                            (0x00000400&((data)<<10))
#define SYS_DISP_PLL_DIV2_write_en5_src(data)                                        ((0x00000400&(data))>>10)
#define SYS_DISP_PLL_DIV2_get_write_en5(data)                                        ((0x00000400&(data))>>10)
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel_shift                                     (9)
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel_mask                                      (0x00000200)
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel(data)                                     (0x00000200&((data)<<9))
#define SYS_DISP_PLL_DIV2_hdmi_phy_clk_sel_src(data)                                 ((0x00000200&(data))>>9)
#define SYS_DISP_PLL_DIV2_get_hdmi_phy_clk_sel(data)                                 ((0x00000200&(data))>>9)
#define SYS_DISP_PLL_DIV2_write_en4_shift                                            (8)
#define SYS_DISP_PLL_DIV2_write_en4_mask                                             (0x00000100)
#define SYS_DISP_PLL_DIV2_write_en4(data)                                            (0x00000100&((data)<<8))
#define SYS_DISP_PLL_DIV2_write_en4_src(data)                                        ((0x00000100&(data))>>8)
#define SYS_DISP_PLL_DIV2_get_write_en4(data)                                        ((0x00000100&(data))>>8)
#define SYS_DISP_PLL_DIV2_hdmi_div_shift                                             (5)
#define SYS_DISP_PLL_DIV2_hdmi_div_mask                                              (0x000000E0)
#define SYS_DISP_PLL_DIV2_hdmi_div(data)                                             (0x000000E0&((data)<<5))
#define SYS_DISP_PLL_DIV2_hdmi_div_src(data)                                         ((0x000000E0&(data))>>5)
#define SYS_DISP_PLL_DIV2_get_hdmi_div(data)                                         ((0x000000E0&(data))>>5)
#define SYS_DISP_PLL_DIV2_write_en3_shift                                            (4)
#define SYS_DISP_PLL_DIV2_write_en3_mask                                             (0x00000010)
#define SYS_DISP_PLL_DIV2_write_en3(data)                                            (0x00000010&((data)<<4))
#define SYS_DISP_PLL_DIV2_write_en3_src(data)                                        ((0x00000010&(data))>>4)
#define SYS_DISP_PLL_DIV2_get_write_en3(data)                                        ((0x00000010&(data))>>4)
#define SYS_DISP_PLL_DIV2_tve_div_shift                                              (0)
#define SYS_DISP_PLL_DIV2_tve_div_mask                                               (0x0000000F)
#define SYS_DISP_PLL_DIV2_tve_div(data)                                              (0x0000000F&((data)<<0))
#define SYS_DISP_PLL_DIV2_tve_div_src(data)                                          ((0x0000000F&(data))>>0)
#define SYS_DISP_PLL_DIV2_get_tve_div(data)                                          ((0x0000000F&(data))>>0)


#define SYS_DISP_PLL_DIV3                                                            0x18000028
#define SYS_DISP_PLL_DIV3_reg_addr                                                   "0xB8000028"
#define SYS_DISP_PLL_DIV3_reg                                                        0xB8000028
#define set_SYS_DISP_PLL_DIV3_reg(data)   (*((volatile unsigned int*) SYS_DISP_PLL_DIV3_reg)=data)
#define get_SYS_DISP_PLL_DIV3_reg   (*((volatile unsigned int*) SYS_DISP_PLL_DIV3_reg))
#define SYS_DISP_PLL_DIV3_inst_adr                                                   "0x000A"
#define SYS_DISP_PLL_DIV3_inst                                                       0x000A
#define SYS_DISP_PLL_DIV3_reg_hdmi_tmds_div_shift                                    (12)
#define SYS_DISP_PLL_DIV3_reg_hdmi_tmds_div_mask                                     (0x00003000)
#define SYS_DISP_PLL_DIV3_reg_hdmi_tmds_div(data)                                    (0x00003000&((data)<<12))
#define SYS_DISP_PLL_DIV3_reg_hdmi_tmds_div_src(data)                                ((0x00003000&(data))>>12)
#define SYS_DISP_PLL_DIV3_get_reg_hdmi_tmds_div(data)                                ((0x00003000&(data))>>12)
#define SYS_DISP_PLL_DIV3_reg_tve_hdmi_div_sel_shift                                 (10)
#define SYS_DISP_PLL_DIV3_reg_tve_hdmi_div_sel_mask                                  (0x00000C00)
#define SYS_DISP_PLL_DIV3_reg_tve_hdmi_div_sel(data)                                 (0x00000C00&((data)<<10))
#define SYS_DISP_PLL_DIV3_reg_tve_hdmi_div_sel_src(data)                             ((0x00000C00&(data))>>10)
#define SYS_DISP_PLL_DIV3_get_reg_tve_hdmi_div_sel(data)                             ((0x00000C00&(data))>>10)
#define SYS_DISP_PLL_DIV3_reg_dac1_clk_sel_shift                                     (8)
#define SYS_DISP_PLL_DIV3_reg_dac1_clk_sel_mask                                      (0x00000300)
#define SYS_DISP_PLL_DIV3_reg_dac1_clk_sel(data)                                     (0x00000300&((data)<<8))
#define SYS_DISP_PLL_DIV3_reg_dac1_clk_sel_src(data)                                 ((0x00000300&(data))>>8)
#define SYS_DISP_PLL_DIV3_get_reg_dac1_clk_sel(data)                                 ((0x00000300&(data))>>8)
#define SYS_DISP_PLL_DIV3_reg_tve_pclk_sel_shift                                     (6)
#define SYS_DISP_PLL_DIV3_reg_tve_pclk_sel_mask                                      (0x000000C0)
#define SYS_DISP_PLL_DIV3_reg_tve_pclk_sel(data)                                     (0x000000C0&((data)<<6))
#define SYS_DISP_PLL_DIV3_reg_tve_pclk_sel_src(data)                                 ((0x000000C0&(data))>>6)
#define SYS_DISP_PLL_DIV3_get_reg_tve_pclk_sel(data)                                 ((0x000000C0&(data))>>6)
#define SYS_DISP_PLL_DIV3_reg_dac2_clk_sel_shift                                     (4)
#define SYS_DISP_PLL_DIV3_reg_dac2_clk_sel_mask                                      (0x00000030)
#define SYS_DISP_PLL_DIV3_reg_dac2_clk_sel(data)                                     (0x00000030&((data)<<4))
#define SYS_DISP_PLL_DIV3_reg_dac2_clk_sel_src(data)                                 ((0x00000030&(data))>>4)
#define SYS_DISP_PLL_DIV3_get_reg_dac2_clk_sel(data)                                 ((0x00000030&(data))>>4)
#define SYS_DISP_PLL_DIV3_reg_tve_iclk_sel_shift                                     (2)
#define SYS_DISP_PLL_DIV3_reg_tve_iclk_sel_mask                                      (0x0000000C)
#define SYS_DISP_PLL_DIV3_reg_tve_iclk_sel(data)                                     (0x0000000C&((data)<<2))
#define SYS_DISP_PLL_DIV3_reg_tve_iclk_sel_src(data)                                 ((0x0000000C&(data))>>2)
#define SYS_DISP_PLL_DIV3_get_reg_tve_iclk_sel(data)                                 ((0x0000000C&(data))>>2)
#define SYS_DISP_PLL_DIV3_reg_dac1_phy_clk_inv_shift                                 (1)
#define SYS_DISP_PLL_DIV3_reg_dac1_phy_clk_inv_mask                                  (0x00000002)
#define SYS_DISP_PLL_DIV3_reg_dac1_phy_clk_inv(data)                                 (0x00000002&((data)<<1))
#define SYS_DISP_PLL_DIV3_reg_dac1_phy_clk_inv_src(data)                             ((0x00000002&(data))>>1)
#define SYS_DISP_PLL_DIV3_get_reg_dac1_phy_clk_inv(data)                             ((0x00000002&(data))>>1)
#define SYS_DISP_PLL_DIV3_reg_dac2_phy_clk_inv_shift                                 (0)
#define SYS_DISP_PLL_DIV3_reg_dac2_phy_clk_inv_mask                                  (0x00000001)
#define SYS_DISP_PLL_DIV3_reg_dac2_phy_clk_inv(data)                                 (0x00000001&((data)<<0))
#define SYS_DISP_PLL_DIV3_reg_dac2_phy_clk_inv_src(data)                             ((0x00000001&(data))>>0)
#define SYS_DISP_PLL_DIV3_get_reg_dac2_phy_clk_inv(data)                             ((0x00000001&(data))>>0)


#define SYS_AUDIO_CLK_CTL                                                            0x1800002C
#define SYS_AUDIO_CLK_CTL_reg_addr                                                   "0xB800002C"
#define SYS_AUDIO_CLK_CTL_reg                                                        0xB800002C
#define set_SYS_AUDIO_CLK_CTL_reg(data)   (*((volatile unsigned int*) SYS_AUDIO_CLK_CTL_reg)=data)
#define get_SYS_AUDIO_CLK_CTL_reg   (*((volatile unsigned int*) SYS_AUDIO_CLK_CTL_reg))
#define SYS_AUDIO_CLK_CTL_inst_adr                                                   "0x000B"
#define SYS_AUDIO_CLK_CTL_inst                                                       0x000B
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk_shift                                     (0)
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk_mask                                      (0x00000001)
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk(data)                                     (0x00000001&((data)<<0))
#define SYS_AUDIO_CLK_CTL_audio_use_sysclk_src(data)                                 ((0x00000001&(data))>>0)
#define SYS_AUDIO_CLK_CTL_get_audio_use_sysclk(data)                                 ((0x00000001&(data))>>0)


#define SYS_PLL_DIV                                                                  0x18000030
#define SYS_PLL_DIV_reg_addr                                                         "0xB8000030"
#define SYS_PLL_DIV_reg                                                              0xB8000030
#define set_SYS_PLL_DIV_reg(data)   (*((volatile unsigned int*) SYS_PLL_DIV_reg)=data)
#define get_SYS_PLL_DIV_reg   (*((volatile unsigned int*) SYS_PLL_DIV_reg))
#define SYS_PLL_DIV_inst_adr                                                         "0x000C"
#define SYS_PLL_DIV_inst                                                             0x000C
#define SYS_PLL_DIV_scpu_freq_sel_shift                                              (7)
#define SYS_PLL_DIV_scpu_freq_sel_mask                                               (0x00000180)
#define SYS_PLL_DIV_scpu_freq_sel(data)                                              (0x00000180&((data)<<7))
#define SYS_PLL_DIV_scpu_freq_sel_src(data)                                          ((0x00000180&(data))>>7)
#define SYS_PLL_DIV_get_scpu_freq_sel(data)                                          ((0x00000180&(data))>>7)
#define SYS_PLL_DIV_vcpu_freq_sel_shift                                              (5)
#define SYS_PLL_DIV_vcpu_freq_sel_mask                                               (0x00000060)
#define SYS_PLL_DIV_vcpu_freq_sel(data)                                              (0x00000060&((data)<<5))
#define SYS_PLL_DIV_vcpu_freq_sel_src(data)                                          ((0x00000060&(data))>>5)
#define SYS_PLL_DIV_get_vcpu_freq_sel(data)                                          ((0x00000060&(data))>>5)
#define SYS_PLL_DIV_acpu_freq_sel_shift                                              (3)
#define SYS_PLL_DIV_acpu_freq_sel_mask                                               (0x00000018)
#define SYS_PLL_DIV_acpu_freq_sel(data)                                              (0x00000018&((data)<<3))
#define SYS_PLL_DIV_acpu_freq_sel_src(data)                                          ((0x00000018&(data))>>3)
#define SYS_PLL_DIV_get_acpu_freq_sel(data)                                          ((0x00000018&(data))>>3)
#define SYS_PLL_DIV_ddr_freq_sel_shift                                               (1)
#define SYS_PLL_DIV_ddr_freq_sel_mask                                                (0x00000006)
#define SYS_PLL_DIV_ddr_freq_sel(data)                                               (0x00000006&((data)<<1))
#define SYS_PLL_DIV_ddr_freq_sel_src(data)                                           ((0x00000006&(data))>>1)
#define SYS_PLL_DIV_get_ddr_freq_sel(data)                                           ((0x00000006&(data))>>1)
#define SYS_PLL_DIV_bus_freq_sel_shift                                               (0)
#define SYS_PLL_DIV_bus_freq_sel_mask                                                (0x00000001)
#define SYS_PLL_DIV_bus_freq_sel(data)                                               (0x00000001&((data)<<0))
#define SYS_PLL_DIV_bus_freq_sel_src(data)                                           ((0x00000001&(data))>>0)
#define SYS_PLL_DIV_get_bus_freq_sel(data)                                           ((0x00000001&(data))>>0)


#define SYS_NF_CKSEL                                                                 0x18000038
#define SYS_NF_CKSEL_reg_addr                                                        "0xB8000038"
#define SYS_NF_CKSEL_reg                                                             0xB8000038
#define set_SYS_NF_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_NF_CKSEL_reg)=data)
#define get_SYS_NF_CKSEL_reg   (*((volatile unsigned int*) SYS_NF_CKSEL_reg))
#define SYS_NF_CKSEL_inst_adr                                                        "0x000E"
#define SYS_NF_CKSEL_inst                                                            0x000E
#define SYS_NF_CKSEL_nf_div_shift                                                    (0)
#define SYS_NF_CKSEL_nf_div_mask                                                     (0x00000007)
#define SYS_NF_CKSEL_nf_div(data)                                                    (0x00000007&((data)<<0))
#define SYS_NF_CKSEL_nf_div_src(data)                                                ((0x00000007&(data))>>0)
#define SYS_NF_CKSEL_get_nf_div(data)                                                ((0x00000007&(data))>>0)


#define SYS_NDS_SC_CKSEL                                                             0x1800003C
#define SYS_NDS_SC_CKSEL_reg_addr                                                    "0xB800003C"
#define SYS_NDS_SC_CKSEL_reg                                                         0xB800003C
#define set_SYS_NDS_SC_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_NDS_SC_CKSEL_reg)=data)
#define get_SYS_NDS_SC_CKSEL_reg   (*((volatile unsigned int*) SYS_NDS_SC_CKSEL_reg))
#define SYS_NDS_SC_CKSEL_inst_adr                                                    "0x000F"
#define SYS_NDS_SC_CKSEL_inst                                                        0x000F
#define SYS_NDS_SC_CKSEL_nds_sc_div_shift                                            (0)
#define SYS_NDS_SC_CKSEL_nds_sc_div_mask                                             (0x00000007)
#define SYS_NDS_SC_CKSEL_nds_sc_div(data)                                            (0x00000007&((data)<<0))
#define SYS_NDS_SC_CKSEL_nds_sc_div_src(data)                                        ((0x00000007&(data))>>0)
#define SYS_NDS_SC_CKSEL_get_nds_sc_div(data)                                        ((0x00000007&(data))>>0)


#define SYS_CR_CKSEL                                                                 0x18000040
#define SYS_CR_CKSEL_reg_addr                                                        "0xB8000040"
#define SYS_CR_CKSEL_reg                                                             0xB8000040
#define set_SYS_CR_CKSEL_reg(data)   (*((volatile unsigned int*) SYS_CR_CKSEL_reg)=data)
#define get_SYS_CR_CKSEL_reg   (*((volatile unsigned int*) SYS_CR_CKSEL_reg))
#define SYS_CR_CKSEL_inst_adr                                                        "0x0010"
#define SYS_CR_CKSEL_inst                                                            0x0010
#define SYS_CR_CKSEL_write_en3_shift                                                 (31)
#define SYS_CR_CKSEL_write_en3_mask                                                  (0x80000000)
#define SYS_CR_CKSEL_write_en3(data)                                                 (0x80000000&((data)<<31))
#define SYS_CR_CKSEL_write_en3_src(data)                                             ((0x80000000&(data))>>31)
#define SYS_CR_CKSEL_get_write_en3(data)                                             ((0x80000000&(data))>>31)
#define SYS_CR_CKSEL_cremmc_clk_sel_shift                                            (30)
#define SYS_CR_CKSEL_cremmc_clk_sel_mask                                             (0x40000000)
#define SYS_CR_CKSEL_cremmc_clk_sel(data)                                            (0x40000000&((data)<<30))
#define SYS_CR_CKSEL_cremmc_clk_sel_src(data)                                        ((0x40000000&(data))>>30)
#define SYS_CR_CKSEL_get_cremmc_clk_sel(data)                                        ((0x40000000&(data))>>30)
#define SYS_CR_CKSEL_write_en2_shift                                                 (7)
#define SYS_CR_CKSEL_write_en2_mask                                                  (0x00000080)
#define SYS_CR_CKSEL_write_en2(data)                                                 (0x00000080&((data)<<7))
#define SYS_CR_CKSEL_write_en2_src(data)                                             ((0x00000080&(data))>>7)
#define SYS_CR_CKSEL_get_write_en2(data)                                             ((0x00000080&(data))>>7)
#define SYS_CR_CKSEL_emmc_div_shift                                                  (4)
#define SYS_CR_CKSEL_emmc_div_mask                                                   (0x00000070)
#define SYS_CR_CKSEL_emmc_div(data)                                                  (0x00000070&((data)<<4))
#define SYS_CR_CKSEL_emmc_div_src(data)                                              ((0x00000070&(data))>>4)
#define SYS_CR_CKSEL_get_emmc_div(data)                                              ((0x00000070&(data))>>4)
#define SYS_CR_CKSEL_write_en1_shift                                                 (3)
#define SYS_CR_CKSEL_write_en1_mask                                                  (0x00000008)
#define SYS_CR_CKSEL_write_en1(data)                                                 (0x00000008&((data)<<3))
#define SYS_CR_CKSEL_write_en1_src(data)                                             ((0x00000008&(data))>>3)
#define SYS_CR_CKSEL_get_write_en1(data)                                             ((0x00000008&(data))>>3)
#define SYS_CR_CKSEL_cr_div_shift                                                    (0)
#define SYS_CR_CKSEL_cr_div_mask                                                     (0x00000007)
#define SYS_CR_CKSEL_cr_div(data)                                                    (0x00000007&((data)<<0))
#define SYS_CR_CKSEL_cr_div_src(data)                                                ((0x00000007&(data))>>0)
#define SYS_CR_CKSEL_get_cr_div(data)                                                ((0x00000007&(data))>>0)


#define SYS_CLKDIV                                                                   0x18000044
#define SYS_CLKDIV_reg_addr                                                          "0xB8000044"
#define SYS_CLKDIV_reg                                                               0xB8000044
#define set_SYS_CLKDIV_reg(data)   (*((volatile unsigned int*) SYS_CLKDIV_reg)=data)
#define get_SYS_CLKDIV_reg   (*((volatile unsigned int*) SYS_CLKDIV_reg))
#define SYS_CLKDIV_inst_adr                                                          "0x0011"
#define SYS_CLKDIV_inst                                                              0x0011
#define SYS_CLKDIV_DTV_DEMOD_MULTI_REQ_DISABLE_shift                                 (4)
#define SYS_CLKDIV_DTV_DEMOD_MULTI_REQ_DISABLE_mask                                  (0x00000010)
#define SYS_CLKDIV_DTV_DEMOD_MULTI_REQ_DISABLE(data)                                 (0x00000010&((data)<<4))
#define SYS_CLKDIV_DTV_DEMOD_MULTI_REQ_DISABLE_src(data)                             ((0x00000010&(data))>>4)
#define SYS_CLKDIV_get_DTV_DEMOD_MULTI_REQ_DISABLE(data)                             ((0x00000010&(data))>>4)
#define SYS_CLKDIV_AUD_DTV_FREQ_SEL_shift                                            (0)
#define SYS_CLKDIV_AUD_DTV_FREQ_SEL_mask                                             (0x00000007)
#define SYS_CLKDIV_AUD_DTV_FREQ_SEL(data)                                            (0x00000007&((data)<<0))
#define SYS_CLKDIV_AUD_DTV_FREQ_SEL_src(data)                                        ((0x00000007&(data))>>0)
#define SYS_CLKDIV_get_AUD_DTV_FREQ_SEL(data)                                        ((0x00000007&(data))>>0)


#define SYS_ARM_WD                                                                   0x18000048
#define SYS_ARM_WD_reg_addr                                                          "0xB8000048"
#define SYS_ARM_WD_reg                                                               0xB8000048
#define set_SYS_ARM_WD_reg(data)   (*((volatile unsigned int*) SYS_ARM_WD_reg)=data)
#define get_SYS_ARM_WD_reg   (*((volatile unsigned int*) SYS_ARM_WD_reg))
#define SYS_ARM_WD_inst_adr                                                          "0x0012"
#define SYS_ARM_WD_inst                                                              0x0012
#define SYS_ARM_WD_SCPU_WD_EN_shift                                                  (16)
#define SYS_ARM_WD_SCPU_WD_EN_mask                                                   (0x00010000)
#define SYS_ARM_WD_SCPU_WD_EN(data)                                                  (0x00010000&((data)<<16))
#define SYS_ARM_WD_SCPU_WD_EN_src(data)                                              ((0x00010000&(data))>>16)
#define SYS_ARM_WD_get_SCPU_WD_EN(data)                                              ((0x00010000&(data))>>16)
#define SYS_ARM_WD_SCPU_WD_CNT_shift                                                 (0)
#define SYS_ARM_WD_SCPU_WD_CNT_mask                                                  (0x00000FFF)
#define SYS_ARM_WD_SCPU_WD_CNT(data)                                                 (0x00000FFF&((data)<<0))
#define SYS_ARM_WD_SCPU_WD_CNT_src(data)                                             ((0x00000FFF&(data))>>0)
#define SYS_ARM_WD_get_SCPU_WD_CNT(data)                                             ((0x00000FFF&(data))>>0)


#define SYS_POWER_CTRL0                                                              0x1800004C
#define SYS_POWER_CTRL0_reg_addr                                                     "0xB800004C"
#define SYS_POWER_CTRL0_reg                                                          0xB800004C
#define set_SYS_POWER_CTRL0_reg(data)   (*((volatile unsigned int*) SYS_POWER_CTRL0_reg)=data)
#define get_SYS_POWER_CTRL0_reg   (*((volatile unsigned int*) SYS_POWER_CTRL0_reg))
#define SYS_POWER_CTRL0_inst_adr                                                     "0x0013"
#define SYS_POWER_CTRL0_inst                                                         0x0013
#define SYS_POWER_CTRL0_ATV_ISO_EN_shift                                             (12)
#define SYS_POWER_CTRL0_ATV_ISO_EN_mask                                              (0x00001000)
#define SYS_POWER_CTRL0_ATV_ISO_EN(data)                                             (0x00001000&((data)<<12))
#define SYS_POWER_CTRL0_ATV_ISO_EN_src(data)                                         ((0x00001000&(data))>>12)
#define SYS_POWER_CTRL0_get_ATV_ISO_EN(data)                                         ((0x00001000&(data))>>12)
#define SYS_POWER_CTRL0_ATV_STR_STATUS_shift                                         (10)
#define SYS_POWER_CTRL0_ATV_STR_STATUS_mask                                          (0x00000400)
#define SYS_POWER_CTRL0_ATV_STR_STATUS(data)                                         (0x00000400&((data)<<10))
#define SYS_POWER_CTRL0_ATV_STR_STATUS_src(data)                                     ((0x00000400&(data))>>10)
#define SYS_POWER_CTRL0_get_ATV_STR_STATUS(data)                                     ((0x00000400&(data))>>10)
#define SYS_POWER_CTRL0_ATV_STR_POW_shift                                            (8)
#define SYS_POWER_CTRL0_ATV_STR_POW_mask                                             (0x00000100)
#define SYS_POWER_CTRL0_ATV_STR_POW(data)                                            (0x00000100&((data)<<8))
#define SYS_POWER_CTRL0_ATV_STR_POW_src(data)                                        ((0x00000100&(data))>>8)
#define SYS_POWER_CTRL0_get_ATV_STR_POW(data)                                        ((0x00000100&(data))>>8)
#define SYS_POWER_CTRL0_DTV_ISO_EN_shift                                             (4)
#define SYS_POWER_CTRL0_DTV_ISO_EN_mask                                              (0x00000010)
#define SYS_POWER_CTRL0_DTV_ISO_EN(data)                                             (0x00000010&((data)<<4))
#define SYS_POWER_CTRL0_DTV_ISO_EN_src(data)                                         ((0x00000010&(data))>>4)
#define SYS_POWER_CTRL0_get_DTV_ISO_EN(data)                                         ((0x00000010&(data))>>4)
#define SYS_POWER_CTRL0_DTV_STR_STATUS_shift                                         (2)
#define SYS_POWER_CTRL0_DTV_STR_STATUS_mask                                          (0x00000004)
#define SYS_POWER_CTRL0_DTV_STR_STATUS(data)                                         (0x00000004&((data)<<2))
#define SYS_POWER_CTRL0_DTV_STR_STATUS_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_POWER_CTRL0_get_DTV_STR_STATUS(data)                                     ((0x00000004&(data))>>2)
#define SYS_POWER_CTRL0_DTV_STR_POW_shift                                            (0)
#define SYS_POWER_CTRL0_DTV_STR_POW_mask                                             (0x00000001)
#define SYS_POWER_CTRL0_DTV_STR_POW(data)                                            (0x00000001&((data)<<0))
#define SYS_POWER_CTRL0_DTV_STR_POW_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_POWER_CTRL0_get_DTV_STR_POW(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_WDOUT                                                                0x18000050
#define SYS_PLL_WDOUT_reg_addr                                                       "0xB8000050"
#define SYS_PLL_WDOUT_reg                                                            0xB8000050
#define set_SYS_PLL_WDOUT_reg(data)   (*((volatile unsigned int*) SYS_PLL_WDOUT_reg)=data)
#define get_SYS_PLL_WDOUT_reg   (*((volatile unsigned int*) SYS_PLL_WDOUT_reg))
#define SYS_PLL_WDOUT_inst_adr                                                       "0x0014"
#define SYS_PLL_WDOUT_inst                                                           0x0014
#define SYS_PLL_WDOUT_PLL27X_WDOUT_shift                                             (18)
#define SYS_PLL_WDOUT_PLL27X_WDOUT_mask                                              (0x00040000)
#define SYS_PLL_WDOUT_PLL27X_WDOUT(data)                                             (0x00040000&((data)<<18))
#define SYS_PLL_WDOUT_PLL27X_WDOUT_src(data)                                         ((0x00040000&(data))>>18)
#define SYS_PLL_WDOUT_get_PLL27X_WDOUT(data)                                         ((0x00040000&(data))>>18)
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT_shift                                       (17)
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT_mask                                        (0x00020000)
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT(data)                                       (0x00020000&((data)<<17))
#define SYS_PLL_WDOUT_REG_PLLVODMA_WDOUT_src(data)                                   ((0x00020000&(data))>>17)
#define SYS_PLL_WDOUT_get_REG_PLLVODMA_WDOUT(data)                                   ((0x00020000&(data))>>17)
#define SYS_PLL_WDOUT_PLLGPU_WDOUT_shift                                             (16)
#define SYS_PLL_WDOUT_PLLGPU_WDOUT_mask                                              (0x00010000)
#define SYS_PLL_WDOUT_PLLGPU_WDOUT(data)                                             (0x00010000&((data)<<16))
#define SYS_PLL_WDOUT_PLLGPU_WDOUT_src(data)                                         ((0x00010000&(data))>>16)
#define SYS_PLL_WDOUT_get_PLLGPU_WDOUT(data)                                         ((0x00010000&(data))>>16)
#define SYS_PLL_WDOUT_PLLGPU_WDOUT_2_shift                                           (15)
#define SYS_PLL_WDOUT_PLLGPU_WDOUT_2_mask                                            (0x00008000)
#define SYS_PLL_WDOUT_PLLGPU_WDOUT_2(data)                                           (0x00008000&((data)<<15))
#define SYS_PLL_WDOUT_PLLGPU_WDOUT_2_src(data)                                       ((0x00008000&(data))>>15)
#define SYS_PLL_WDOUT_get_PLLGPU_WDOUT_2(data)                                       ((0x00008000&(data))>>15)
#define SYS_PLL_WDOUT_PLLAUD_STATUS_shift                                            (14)
#define SYS_PLL_WDOUT_PLLAUD_STATUS_mask                                             (0x00004000)
#define SYS_PLL_WDOUT_PLLAUD_STATUS(data)                                            (0x00004000&((data)<<14))
#define SYS_PLL_WDOUT_PLLAUD_STATUS_src(data)                                        ((0x00004000&(data))>>14)
#define SYS_PLL_WDOUT_get_PLLAUD_STATUS(data)                                        ((0x00004000&(data))>>14)
#define SYS_PLL_WDOUT_PLL512FS_WDOUT_shift                                           (13)
#define SYS_PLL_WDOUT_PLL512FS_WDOUT_mask                                            (0x00002000)
#define SYS_PLL_WDOUT_PLL512FS_WDOUT(data)                                           (0x00002000&((data)<<13))
#define SYS_PLL_WDOUT_PLL512FS_WDOUT_src(data)                                       ((0x00002000&(data))>>13)
#define SYS_PLL_WDOUT_get_PLL512FS_WDOUT(data)                                       ((0x00002000&(data))>>13)
#define SYS_PLL_WDOUT_REG_PLLBUSH_WDOUT_shift                                        (12)
#define SYS_PLL_WDOUT_REG_PLLBUSH_WDOUT_mask                                         (0x00001000)
#define SYS_PLL_WDOUT_REG_PLLBUSH_WDOUT(data)                                        (0x00001000&((data)<<12))
#define SYS_PLL_WDOUT_REG_PLLBUSH_WDOUT_src(data)                                    ((0x00001000&(data))>>12)
#define SYS_PLL_WDOUT_get_REG_PLLBUSH_WDOUT(data)                                    ((0x00001000&(data))>>12)
#define SYS_PLL_WDOUT_PLLDIF_WDOUT_shift                                             (10)
#define SYS_PLL_WDOUT_PLLDIF_WDOUT_mask                                              (0x00000400)
#define SYS_PLL_WDOUT_PLLDIF_WDOUT(data)                                             (0x00000400&((data)<<10))
#define SYS_PLL_WDOUT_PLLDIF_WDOUT_src(data)                                         ((0x00000400&(data))>>10)
#define SYS_PLL_WDOUT_get_PLLDIF_WDOUT(data)                                         ((0x00000400&(data))>>10)
#define SYS_PLL_WDOUT_PLLBUS2_WDOUT_shift                                            (9)
#define SYS_PLL_WDOUT_PLLBUS2_WDOUT_mask                                             (0x00000200)
#define SYS_PLL_WDOUT_PLLBUS2_WDOUT(data)                                            (0x00000200&((data)<<9))
#define SYS_PLL_WDOUT_PLLBUS2_WDOUT_src(data)                                        ((0x00000200&(data))>>9)
#define SYS_PLL_WDOUT_get_PLLBUS2_WDOUT(data)                                        ((0x00000200&(data))>>9)
#define SYS_PLL_WDOUT_PLLETN_WDOUT_shift                                             (8)
#define SYS_PLL_WDOUT_PLLETN_WDOUT_mask                                              (0x00000100)
#define SYS_PLL_WDOUT_PLLETN_WDOUT(data)                                             (0x00000100&((data)<<8))
#define SYS_PLL_WDOUT_PLLETN_WDOUT_src(data)                                         ((0x00000100&(data))>>8)
#define SYS_PLL_WDOUT_get_PLLETN_WDOUT(data)                                         ((0x00000100&(data))>>8)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_shift                                         (6)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_mask                                          (0x00000040)
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT(data)                                         (0x00000040&((data)<<6))
#define SYS_PLL_WDOUT_REG_PLLBUS_WDOUT_src(data)                                     ((0x00000040&(data))>>6)
#define SYS_PLL_WDOUT_get_REG_PLLBUS_WDOUT(data)                                     ((0x00000040&(data))>>6)
#define SYS_PLL_WDOUT_PLLDISP_WDOUT_shift                                            (5)
#define SYS_PLL_WDOUT_PLLDISP_WDOUT_mask                                             (0x00000020)
#define SYS_PLL_WDOUT_PLLDISP_WDOUT(data)                                            (0x00000020&((data)<<5))
#define SYS_PLL_WDOUT_PLLDISP_WDOUT_src(data)                                        ((0x00000020&(data))>>5)
#define SYS_PLL_WDOUT_get_PLLDISP_WDOUT(data)                                        ((0x00000020&(data))>>5)
#define SYS_PLL_WDOUT_PLLDDS_WDOUT_shift                                             (3)
#define SYS_PLL_WDOUT_PLLDDS_WDOUT_mask                                              (0x00000008)
#define SYS_PLL_WDOUT_PLLDDS_WDOUT(data)                                             (0x00000008&((data)<<3))
#define SYS_PLL_WDOUT_PLLDDS_WDOUT_src(data)                                         ((0x00000008&(data))>>3)
#define SYS_PLL_WDOUT_get_PLLDDS_WDOUT(data)                                         ((0x00000008&(data))>>3)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_shift                                        (2)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_mask                                         (0x00000004)
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_WDOUT_REG_PLLVCPU_WDOUT_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_WDOUT_get_REG_PLLVCPU_WDOUT(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT_shift                                        (1)
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT_mask                                         (0x00000002)
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_WDOUT_REG_PLLACPU_WDOUT_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_WDOUT_get_REG_PLLACPU_WDOUT(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_WDOUT_REG_PLLSCPU_WDOUT_shift                                        (0)
#define SYS_PLL_WDOUT_REG_PLLSCPU_WDOUT_mask                                         (0x00000001)
#define SYS_PLL_WDOUT_REG_PLLSCPU_WDOUT(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_WDOUT_REG_PLLSCPU_WDOUT_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_WDOUT_get_REG_PLLSCPU_WDOUT(data)                                    ((0x00000001&(data))>>0)


#define SYS_TM_CTRL0                                                                 0x18000054
#define SYS_TM_CTRL0_reg_addr                                                        "0xB8000054"
#define SYS_TM_CTRL0_reg                                                             0xB8000054
#define set_SYS_TM_CTRL0_reg(data)   (*((volatile unsigned int*) SYS_TM_CTRL0_reg)=data)
#define get_SYS_TM_CTRL0_reg   (*((volatile unsigned int*) SYS_TM_CTRL0_reg))
#define SYS_TM_CTRL0_inst_adr                                                        "0x0015"
#define SYS_TM_CTRL0_inst                                                            0x0015
#define SYS_TM_CTRL0_TM_ENABLE_shift                                                 (27)
#define SYS_TM_CTRL0_TM_ENABLE_mask                                                  (0x08000000)
#define SYS_TM_CTRL0_TM_ENABLE(data)                                                 (0x08000000&((data)<<27))
#define SYS_TM_CTRL0_TM_ENABLE_src(data)                                             ((0x08000000&(data))>>27)
#define SYS_TM_CTRL0_get_TM_ENABLE(data)                                             ((0x08000000&(data))>>27)
#define SYS_TM_CTRL0_TM_DATA_VALID_shift                                             (26)
#define SYS_TM_CTRL0_TM_DATA_VALID_mask                                              (0x04000000)
#define SYS_TM_CTRL0_TM_DATA_VALID(data)                                             (0x04000000&((data)<<26))
#define SYS_TM_CTRL0_TM_DATA_VALID_src(data)                                         ((0x04000000&(data))>>26)
#define SYS_TM_CTRL0_get_TM_DATA_VALID(data)                                         ((0x04000000&(data))>>26)
#define SYS_TM_CTRL0_TM_DATA_SAMPLED_shift                                           (25)
#define SYS_TM_CTRL0_TM_DATA_SAMPLED_mask                                            (0x02000000)
#define SYS_TM_CTRL0_TM_DATA_SAMPLED(data)                                           (0x02000000&((data)<<25))
#define SYS_TM_CTRL0_TM_DATA_SAMPLED_src(data)                                       ((0x02000000&(data))>>25)
#define SYS_TM_CTRL0_get_TM_DATA_SAMPLED(data)                                       ((0x02000000&(data))>>25)
#define SYS_TM_CTRL0_TM_REVERSE_CMP_OUT_shift                                        (24)
#define SYS_TM_CTRL0_TM_REVERSE_CMP_OUT_mask                                         (0x01000000)
#define SYS_TM_CTRL0_TM_REVERSE_CMP_OUT(data)                                        (0x01000000&((data)<<24))
#define SYS_TM_CTRL0_TM_REVERSE_CMP_OUT_src(data)                                    ((0x01000000&(data))>>24)
#define SYS_TM_CTRL0_get_TM_REVERSE_CMP_OUT(data)                                    ((0x01000000&(data))>>24)
#define SYS_TM_CTRL0_TM_DATA_OUT_shift                                               (16)
#define SYS_TM_CTRL0_TM_DATA_OUT_mask                                                (0x007F0000)
#define SYS_TM_CTRL0_TM_DATA_OUT(data)                                               (0x007F0000&((data)<<16))
#define SYS_TM_CTRL0_TM_DATA_OUT_src(data)                                           ((0x007F0000&(data))>>16)
#define SYS_TM_CTRL0_get_TM_DATA_OUT(data)                                           ((0x007F0000&(data))>>16)
#define SYS_TM_CTRL0_TM_PWRON_DLY_shift                                              (0)
#define SYS_TM_CTRL0_TM_PWRON_DLY_mask                                               (0x0000FFFF)
#define SYS_TM_CTRL0_TM_PWRON_DLY(data)                                              (0x0000FFFF&((data)<<0))
#define SYS_TM_CTRL0_TM_PWRON_DLY_src(data)                                          ((0x0000FFFF&(data))>>0)
#define SYS_TM_CTRL0_get_TM_PWRON_DLY(data)                                          ((0x0000FFFF&(data))>>0)


#define SYS_TM_CTRL1                                                                 0x18000058
#define SYS_TM_CTRL1_reg_addr                                                        "0xB8000058"
#define SYS_TM_CTRL1_reg                                                             0xB8000058
#define set_SYS_TM_CTRL1_reg(data)   (*((volatile unsigned int*) SYS_TM_CTRL1_reg)=data)
#define get_SYS_TM_CTRL1_reg   (*((volatile unsigned int*) SYS_TM_CTRL1_reg))
#define SYS_TM_CTRL1_inst_adr                                                        "0x0016"
#define SYS_TM_CTRL1_inst                                                            0x0016
#define SYS_TM_CTRL1_TM_COMPARE_DLY_shift                                            (16)
#define SYS_TM_CTRL1_TM_COMPARE_DLY_mask                                             (0xFFFF0000)
#define SYS_TM_CTRL1_TM_COMPARE_DLY(data)                                            (0xFFFF0000&((data)<<16))
#define SYS_TM_CTRL1_TM_COMPARE_DLY_src(data)                                        ((0xFFFF0000&(data))>>16)
#define SYS_TM_CTRL1_get_TM_COMPARE_DLY(data)                                        ((0xFFFF0000&(data))>>16)
#define SYS_TM_CTRL1_TM_SAMPLE_DLY_shift                                             (0)
#define SYS_TM_CTRL1_TM_SAMPLE_DLY_mask                                              (0x0000FFFF)
#define SYS_TM_CTRL1_TM_SAMPLE_DLY(data)                                             (0x0000FFFF&((data)<<0))
#define SYS_TM_CTRL1_TM_SAMPLE_DLY_src(data)                                         ((0x0000FFFF&(data))>>0)
#define SYS_TM_CTRL1_get_TM_SAMPLE_DLY(data)                                         ((0x0000FFFF&(data))>>0)


#define SYS_TM_CTRL2                                                                 0x1800005C
#define SYS_TM_CTRL2_reg_addr                                                        "0xB800005C"
#define SYS_TM_CTRL2_reg                                                             0xB800005C
#define set_SYS_TM_CTRL2_reg(data)   (*((volatile unsigned int*) SYS_TM_CTRL2_reg)=data)
#define get_SYS_TM_CTRL2_reg   (*((volatile unsigned int*) SYS_TM_CTRL2_reg))
#define SYS_TM_CTRL2_inst_adr                                                        "0x0017"
#define SYS_TM_CTRL2_inst                                                            0x0017
#define SYS_TM_CTRL2_REG_TM_SBG_shift                                                (7)
#define SYS_TM_CTRL2_REG_TM_SBG_mask                                                 (0x00000380)
#define SYS_TM_CTRL2_REG_TM_SBG(data)                                                (0x00000380&((data)<<7))
#define SYS_TM_CTRL2_REG_TM_SBG_src(data)                                            ((0x00000380&(data))>>7)
#define SYS_TM_CTRL2_get_REG_TM_SBG(data)                                            ((0x00000380&(data))>>7)
#define SYS_TM_CTRL2_REG_TM_SOS_shift                                                (4)
#define SYS_TM_CTRL2_REG_TM_SOS_mask                                                 (0x00000070)
#define SYS_TM_CTRL2_REG_TM_SOS(data)                                                (0x00000070&((data)<<4))
#define SYS_TM_CTRL2_REG_TM_SOS_src(data)                                            ((0x00000070&(data))>>4)
#define SYS_TM_CTRL2_get_REG_TM_SOS(data)                                            ((0x00000070&(data))>>4)
#define SYS_TM_CTRL2_REG_TM_SINL_shift                                               (2)
#define SYS_TM_CTRL2_REG_TM_SINL_mask                                                (0x0000000C)
#define SYS_TM_CTRL2_REG_TM_SINL(data)                                               (0x0000000C&((data)<<2))
#define SYS_TM_CTRL2_REG_TM_SINL_src(data)                                           ((0x0000000C&(data))>>2)
#define SYS_TM_CTRL2_get_REG_TM_SINL(data)                                           ((0x0000000C&(data))>>2)
#define SYS_TM_CTRL2_REG_TM_POW_shift                                                (1)
#define SYS_TM_CTRL2_REG_TM_POW_mask                                                 (0x00000002)
#define SYS_TM_CTRL2_REG_TM_POW(data)                                                (0x00000002&((data)<<1))
#define SYS_TM_CTRL2_REG_TM_POW_src(data)                                            ((0x00000002&(data))>>1)
#define SYS_TM_CTRL2_get_REG_TM_POW(data)                                            ((0x00000002&(data))>>1)


#define SYS_DSS00_DSS_GPU0                                                           0x18000060
#define SYS_DSS00_DSS_GPU0_reg_addr                                                  "0xB8000060"
#define SYS_DSS00_DSS_GPU0_reg                                                       0xB8000060
#define set_SYS_DSS00_DSS_GPU0_reg(data)   (*((volatile unsigned int*) SYS_DSS00_DSS_GPU0_reg)=data)
#define get_SYS_DSS00_DSS_GPU0_reg   (*((volatile unsigned int*) SYS_DSS00_DSS_GPU0_reg))
#define SYS_DSS00_DSS_GPU0_inst_adr                                                  "0x0018"
#define SYS_DSS00_DSS_GPU0_inst                                                      0x0018
#define SYS_DSS00_DSS_GPU0_dss_c35d5_speed_en_shift                                  (25)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_speed_en_mask                                   (0x02000000)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_speed_en(data)                                  (0x02000000&((data)<<25))
#define SYS_DSS00_DSS_GPU0_dss_c35d5_speed_en_src(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS00_DSS_GPU0_get_dss_c35d5_speed_en(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_data_in_shift                                   (5)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_data_in_mask                                    (0x01FFFFE0)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_data_in(data)                                   (0x01FFFFE0&((data)<<5))
#define SYS_DSS00_DSS_GPU0_dss_c35d5_data_in_src(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS00_DSS_GPU0_get_dss_c35d5_data_in(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_wire_sel_shift                                  (4)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_wire_sel_mask                                   (0x00000010)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_wire_sel(data)                                  (0x00000010&((data)<<4))
#define SYS_DSS00_DSS_GPU0_dss_c35d5_wire_sel_src(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS00_DSS_GPU0_get_dss_c35d5_wire_sel(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_ro_sel_shift                                    (1)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_ro_sel_mask                                     (0x0000000E)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_ro_sel(data)                                    (0x0000000E&((data)<<1))
#define SYS_DSS00_DSS_GPU0_dss_c35d5_ro_sel_src(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS00_DSS_GPU0_get_dss_c35d5_ro_sel(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_dss_rst_n_shift                                 (0)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_dss_rst_n_mask                                  (0x00000001)
#define SYS_DSS00_DSS_GPU0_dss_c35d5_dss_rst_n(data)                                 (0x00000001&((data)<<0))
#define SYS_DSS00_DSS_GPU0_dss_c35d5_dss_rst_n_src(data)                             ((0x00000001&(data))>>0)
#define SYS_DSS00_DSS_GPU0_get_dss_c35d5_dss_rst_n(data)                             ((0x00000001&(data))>>0)


#define SYS_DSS01_DSS_GPU0                                                           0x18000064
#define SYS_DSS01_DSS_GPU0_reg_addr                                                  "0xB8000064"
#define SYS_DSS01_DSS_GPU0_reg                                                       0xB8000064
#define set_SYS_DSS01_DSS_GPU0_reg(data)   (*((volatile unsigned int*) SYS_DSS01_DSS_GPU0_reg)=data)
#define get_SYS_DSS01_DSS_GPU0_reg   (*((volatile unsigned int*) SYS_DSS01_DSS_GPU0_reg))
#define SYS_DSS01_DSS_GPU0_inst_adr                                                  "0x0019"
#define SYS_DSS01_DSS_GPU0_inst                                                      0x0019
#define SYS_DSS01_DSS_GPU0_dss_c35d5_wsort_go_shift                                  (21)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_wsort_go_mask                                   (0x00200000)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_wsort_go(data)                                  (0x00200000&((data)<<21))
#define SYS_DSS01_DSS_GPU0_dss_c35d5_wsort_go_src(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS01_DSS_GPU0_get_dss_c35d5_wsort_go(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_count_out_shift                                 (1)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_count_out_mask                                  (0x001FFFFE)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_count_out(data)                                 (0x001FFFFE&((data)<<1))
#define SYS_DSS01_DSS_GPU0_dss_c35d5_count_out_src(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS01_DSS_GPU0_get_dss_c35d5_count_out(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_ready_shift                                     (0)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_ready_mask                                      (0x00000001)
#define SYS_DSS01_DSS_GPU0_dss_c35d5_ready(data)                                     (0x00000001&((data)<<0))
#define SYS_DSS01_DSS_GPU0_dss_c35d5_ready_src(data)                                 ((0x00000001&(data))>>0)
#define SYS_DSS01_DSS_GPU0_get_dss_c35d5_ready(data)                                 ((0x00000001&(data))>>0)


#define SYS_DSS02_DSS_GPU0                                                           0x18000068
#define SYS_DSS02_DSS_GPU0_reg_addr                                                  "0xB8000068"
#define SYS_DSS02_DSS_GPU0_reg                                                       0xB8000068
#define set_SYS_DSS02_DSS_GPU0_reg(data)   (*((volatile unsigned int*) SYS_DSS02_DSS_GPU0_reg)=data)
#define get_SYS_DSS02_DSS_GPU0_reg   (*((volatile unsigned int*) SYS_DSS02_DSS_GPU0_reg))
#define SYS_DSS02_DSS_GPU0_inst_adr                                                  "0x001A"
#define SYS_DSS02_DSS_GPU0_inst                                                      0x001A
#define SYS_DSS02_DSS_GPU0_dss_c35d5_dbgo_shift                                      (0)
#define SYS_DSS02_DSS_GPU0_dss_c35d5_dbgo_mask                                       (0x0000FFFF)
#define SYS_DSS02_DSS_GPU0_dss_c35d5_dbgo(data)                                      (0x0000FFFF&((data)<<0))
#define SYS_DSS02_DSS_GPU0_dss_c35d5_dbgo_src(data)                                  ((0x0000FFFF&(data))>>0)
#define SYS_DSS02_DSS_GPU0_get_dss_c35d5_dbgo(data)                                  ((0x0000FFFF&(data))>>0)


#define SYS_DSS03_DSS_GPU1                                                           0x1800006C
#define SYS_DSS03_DSS_GPU1_reg_addr                                                  "0xB800006C"
#define SYS_DSS03_DSS_GPU1_reg                                                       0xB800006C
#define set_SYS_DSS03_DSS_GPU1_reg(data)   (*((volatile unsigned int*) SYS_DSS03_DSS_GPU1_reg)=data)
#define get_SYS_DSS03_DSS_GPU1_reg   (*((volatile unsigned int*) SYS_DSS03_DSS_GPU1_reg))
#define SYS_DSS03_DSS_GPU1_inst_adr                                                  "0x001B"
#define SYS_DSS03_DSS_GPU1_inst                                                      0x001B
#define SYS_DSS03_DSS_GPU1_dss_c35_speed_en_shift                                    (25)
#define SYS_DSS03_DSS_GPU1_dss_c35_speed_en_mask                                     (0x02000000)
#define SYS_DSS03_DSS_GPU1_dss_c35_speed_en(data)                                    (0x02000000&((data)<<25))
#define SYS_DSS03_DSS_GPU1_dss_c35_speed_en_src(data)                                ((0x02000000&(data))>>25)
#define SYS_DSS03_DSS_GPU1_get_dss_c35_speed_en(data)                                ((0x02000000&(data))>>25)
#define SYS_DSS03_DSS_GPU1_dss_c35_data_in_shift                                     (5)
#define SYS_DSS03_DSS_GPU1_dss_c35_data_in_mask                                      (0x01FFFFE0)
#define SYS_DSS03_DSS_GPU1_dss_c35_data_in(data)                                     (0x01FFFFE0&((data)<<5))
#define SYS_DSS03_DSS_GPU1_dss_c35_data_in_src(data)                                 ((0x01FFFFE0&(data))>>5)
#define SYS_DSS03_DSS_GPU1_get_dss_c35_data_in(data)                                 ((0x01FFFFE0&(data))>>5)
#define SYS_DSS03_DSS_GPU1_dss_c35_wire_sel_shift                                    (4)
#define SYS_DSS03_DSS_GPU1_dss_c35_wire_sel_mask                                     (0x00000010)
#define SYS_DSS03_DSS_GPU1_dss_c35_wire_sel(data)                                    (0x00000010&((data)<<4))
#define SYS_DSS03_DSS_GPU1_dss_c35_wire_sel_src(data)                                ((0x00000010&(data))>>4)
#define SYS_DSS03_DSS_GPU1_get_dss_c35_wire_sel(data)                                ((0x00000010&(data))>>4)
#define SYS_DSS03_DSS_GPU1_dss_c35_ro_sel_shift                                      (1)
#define SYS_DSS03_DSS_GPU1_dss_c35_ro_sel_mask                                       (0x0000000E)
#define SYS_DSS03_DSS_GPU1_dss_c35_ro_sel(data)                                      (0x0000000E&((data)<<1))
#define SYS_DSS03_DSS_GPU1_dss_c35_ro_sel_src(data)                                  ((0x0000000E&(data))>>1)
#define SYS_DSS03_DSS_GPU1_get_dss_c35_ro_sel(data)                                  ((0x0000000E&(data))>>1)
#define SYS_DSS03_DSS_GPU1_dss_c35_dss_rst_n_shift                                   (0)
#define SYS_DSS03_DSS_GPU1_dss_c35_dss_rst_n_mask                                    (0x00000001)
#define SYS_DSS03_DSS_GPU1_dss_c35_dss_rst_n(data)                                   (0x00000001&((data)<<0))
#define SYS_DSS03_DSS_GPU1_dss_c35_dss_rst_n_src(data)                               ((0x00000001&(data))>>0)
#define SYS_DSS03_DSS_GPU1_get_dss_c35_dss_rst_n(data)                               ((0x00000001&(data))>>0)


#define SYS_DSS04_DSS_GPU1                                                           0x18000070
#define SYS_DSS04_DSS_GPU1_reg_addr                                                  "0xB8000070"
#define SYS_DSS04_DSS_GPU1_reg                                                       0xB8000070
#define set_SYS_DSS04_DSS_GPU1_reg(data)   (*((volatile unsigned int*) SYS_DSS04_DSS_GPU1_reg)=data)
#define get_SYS_DSS04_DSS_GPU1_reg   (*((volatile unsigned int*) SYS_DSS04_DSS_GPU1_reg))
#define SYS_DSS04_DSS_GPU1_inst_adr                                                  "0x001C"
#define SYS_DSS04_DSS_GPU1_inst                                                      0x001C
#define SYS_DSS04_DSS_GPU1_dss_c35_wsort_go_shift                                    (21)
#define SYS_DSS04_DSS_GPU1_dss_c35_wsort_go_mask                                     (0x00200000)
#define SYS_DSS04_DSS_GPU1_dss_c35_wsort_go(data)                                    (0x00200000&((data)<<21))
#define SYS_DSS04_DSS_GPU1_dss_c35_wsort_go_src(data)                                ((0x00200000&(data))>>21)
#define SYS_DSS04_DSS_GPU1_get_dss_c35_wsort_go(data)                                ((0x00200000&(data))>>21)
#define SYS_DSS04_DSS_GPU1_dss_c35_count_out_shift                                   (1)
#define SYS_DSS04_DSS_GPU1_dss_c35_count_out_mask                                    (0x001FFFFE)
#define SYS_DSS04_DSS_GPU1_dss_c35_count_out(data)                                   (0x001FFFFE&((data)<<1))
#define SYS_DSS04_DSS_GPU1_dss_c35_count_out_src(data)                               ((0x001FFFFE&(data))>>1)
#define SYS_DSS04_DSS_GPU1_get_dss_c35_count_out(data)                               ((0x001FFFFE&(data))>>1)
#define SYS_DSS04_DSS_GPU1_dss_c35_ready_shift                                       (0)
#define SYS_DSS04_DSS_GPU1_dss_c35_ready_mask                                        (0x00000001)
#define SYS_DSS04_DSS_GPU1_dss_c35_ready(data)                                       (0x00000001&((data)<<0))
#define SYS_DSS04_DSS_GPU1_dss_c35_ready_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_DSS04_DSS_GPU1_get_dss_c35_ready(data)                                   ((0x00000001&(data))>>0)


#define SYS_DSS05_DSS_GPU1                                                           0x18000074
#define SYS_DSS05_DSS_GPU1_reg_addr                                                  "0xB8000074"
#define SYS_DSS05_DSS_GPU1_reg                                                       0xB8000074
#define set_SYS_DSS05_DSS_GPU1_reg(data)   (*((volatile unsigned int*) SYS_DSS05_DSS_GPU1_reg)=data)
#define get_SYS_DSS05_DSS_GPU1_reg   (*((volatile unsigned int*) SYS_DSS05_DSS_GPU1_reg))
#define SYS_DSS05_DSS_GPU1_inst_adr                                                  "0x001D"
#define SYS_DSS05_DSS_GPU1_inst                                                      0x001D
#define SYS_DSS05_DSS_GPU1_dss_c35_dbgo_shift                                        (0)
#define SYS_DSS05_DSS_GPU1_dss_c35_dbgo_mask                                         (0x0000FFFF)
#define SYS_DSS05_DSS_GPU1_dss_c35_dbgo(data)                                        (0x0000FFFF&((data)<<0))
#define SYS_DSS05_DSS_GPU1_dss_c35_dbgo_src(data)                                    ((0x0000FFFF&(data))>>0)
#define SYS_DSS05_DSS_GPU1_get_dss_c35_dbgo(data)                                    ((0x0000FFFF&(data))>>0)


#define SYS_DSS06_DSS_GPU2                                                           0x18000078
#define SYS_DSS06_DSS_GPU2_reg_addr                                                  "0xB8000078"
#define SYS_DSS06_DSS_GPU2_reg                                                       0xB8000078
#define set_SYS_DSS06_DSS_GPU2_reg(data)   (*((volatile unsigned int*) SYS_DSS06_DSS_GPU2_reg)=data)
#define get_SYS_DSS06_DSS_GPU2_reg   (*((volatile unsigned int*) SYS_DSS06_DSS_GPU2_reg))
#define SYS_DSS06_DSS_GPU2_inst_adr                                                  "0x001E"
#define SYS_DSS06_DSS_GPU2_inst                                                      0x001E
#define SYS_DSS06_DSS_GPU2_dss_c35d5_speed_en_shift                                  (25)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_speed_en_mask                                   (0x02000000)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_speed_en(data)                                  (0x02000000&((data)<<25))
#define SYS_DSS06_DSS_GPU2_dss_c35d5_speed_en_src(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS06_DSS_GPU2_get_dss_c35d5_speed_en(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_data_in_shift                                   (5)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_data_in_mask                                    (0x01FFFFE0)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_data_in(data)                                   (0x01FFFFE0&((data)<<5))
#define SYS_DSS06_DSS_GPU2_dss_c35d5_data_in_src(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS06_DSS_GPU2_get_dss_c35d5_data_in(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_wire_sel_shift                                  (4)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_wire_sel_mask                                   (0x00000010)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_wire_sel(data)                                  (0x00000010&((data)<<4))
#define SYS_DSS06_DSS_GPU2_dss_c35d5_wire_sel_src(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS06_DSS_GPU2_get_dss_c35d5_wire_sel(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_ro_sel_shift                                    (1)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_ro_sel_mask                                     (0x0000000E)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_ro_sel(data)                                    (0x0000000E&((data)<<1))
#define SYS_DSS06_DSS_GPU2_dss_c35d5_ro_sel_src(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS06_DSS_GPU2_get_dss_c35d5_ro_sel(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_dss_rst_n_shift                                 (0)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_dss_rst_n_mask                                  (0x00000001)
#define SYS_DSS06_DSS_GPU2_dss_c35d5_dss_rst_n(data)                                 (0x00000001&((data)<<0))
#define SYS_DSS06_DSS_GPU2_dss_c35d5_dss_rst_n_src(data)                             ((0x00000001&(data))>>0)
#define SYS_DSS06_DSS_GPU2_get_dss_c35d5_dss_rst_n(data)                             ((0x00000001&(data))>>0)


#define SYS_DSS07_DSS_GPU2                                                           0x1800007C
#define SYS_DSS07_DSS_GPU2_reg_addr                                                  "0xB800007C"
#define SYS_DSS07_DSS_GPU2_reg                                                       0xB800007C
#define set_SYS_DSS07_DSS_GPU2_reg(data)   (*((volatile unsigned int*) SYS_DSS07_DSS_GPU2_reg)=data)
#define get_SYS_DSS07_DSS_GPU2_reg   (*((volatile unsigned int*) SYS_DSS07_DSS_GPU2_reg))
#define SYS_DSS07_DSS_GPU2_inst_adr                                                  "0x001F"
#define SYS_DSS07_DSS_GPU2_inst                                                      0x001F
#define SYS_DSS07_DSS_GPU2_dss_c35d5_wsort_go_shift                                  (21)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_wsort_go_mask                                   (0x00200000)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_wsort_go(data)                                  (0x00200000&((data)<<21))
#define SYS_DSS07_DSS_GPU2_dss_c35d5_wsort_go_src(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS07_DSS_GPU2_get_dss_c35d5_wsort_go(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_count_out_shift                                 (1)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_count_out_mask                                  (0x001FFFFE)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_count_out(data)                                 (0x001FFFFE&((data)<<1))
#define SYS_DSS07_DSS_GPU2_dss_c35d5_count_out_src(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS07_DSS_GPU2_get_dss_c35d5_count_out(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_ready_shift                                     (0)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_ready_mask                                      (0x00000001)
#define SYS_DSS07_DSS_GPU2_dss_c35d5_ready(data)                                     (0x00000001&((data)<<0))
#define SYS_DSS07_DSS_GPU2_dss_c35d5_ready_src(data)                                 ((0x00000001&(data))>>0)
#define SYS_DSS07_DSS_GPU2_get_dss_c35d5_ready(data)                                 ((0x00000001&(data))>>0)


#define SYS_DSS08_DSS_GPU2                                                           0x18000080
#define SYS_DSS08_DSS_GPU2_reg_addr                                                  "0xB8000080"
#define SYS_DSS08_DSS_GPU2_reg                                                       0xB8000080
#define set_SYS_DSS08_DSS_GPU2_reg(data)   (*((volatile unsigned int*) SYS_DSS08_DSS_GPU2_reg)=data)
#define get_SYS_DSS08_DSS_GPU2_reg   (*((volatile unsigned int*) SYS_DSS08_DSS_GPU2_reg))
#define SYS_DSS08_DSS_GPU2_inst_adr                                                  "0x0020"
#define SYS_DSS08_DSS_GPU2_inst                                                      0x0020
#define SYS_DSS08_DSS_GPU2_dss_c35d5_dbgo_shift                                      (0)
#define SYS_DSS08_DSS_GPU2_dss_c35d5_dbgo_mask                                       (0x0000FFFF)
#define SYS_DSS08_DSS_GPU2_dss_c35d5_dbgo(data)                                      (0x0000FFFF&((data)<<0))
#define SYS_DSS08_DSS_GPU2_dss_c35d5_dbgo_src(data)                                  ((0x0000FFFF&(data))>>0)
#define SYS_DSS08_DSS_GPU2_get_dss_c35d5_dbgo(data)                                  ((0x0000FFFF&(data))>>0)


#define SYS_DSS09_DSS_GPU3                                                           0x18000084
#define SYS_DSS09_DSS_GPU3_reg_addr                                                  "0xB8000084"
#define SYS_DSS09_DSS_GPU3_reg                                                       0xB8000084
#define set_SYS_DSS09_DSS_GPU3_reg(data)   (*((volatile unsigned int*) SYS_DSS09_DSS_GPU3_reg)=data)
#define get_SYS_DSS09_DSS_GPU3_reg   (*((volatile unsigned int*) SYS_DSS09_DSS_GPU3_reg))
#define SYS_DSS09_DSS_GPU3_inst_adr                                                  "0x0021"
#define SYS_DSS09_DSS_GPU3_inst                                                      0x0021
#define SYS_DSS09_DSS_GPU3_dss_c35_speed_en_shift                                    (25)
#define SYS_DSS09_DSS_GPU3_dss_c35_speed_en_mask                                     (0x02000000)
#define SYS_DSS09_DSS_GPU3_dss_c35_speed_en(data)                                    (0x02000000&((data)<<25))
#define SYS_DSS09_DSS_GPU3_dss_c35_speed_en_src(data)                                ((0x02000000&(data))>>25)
#define SYS_DSS09_DSS_GPU3_get_dss_c35_speed_en(data)                                ((0x02000000&(data))>>25)
#define SYS_DSS09_DSS_GPU3_dss_c35_data_in_shift                                     (5)
#define SYS_DSS09_DSS_GPU3_dss_c35_data_in_mask                                      (0x01FFFFE0)
#define SYS_DSS09_DSS_GPU3_dss_c35_data_in(data)                                     (0x01FFFFE0&((data)<<5))
#define SYS_DSS09_DSS_GPU3_dss_c35_data_in_src(data)                                 ((0x01FFFFE0&(data))>>5)
#define SYS_DSS09_DSS_GPU3_get_dss_c35_data_in(data)                                 ((0x01FFFFE0&(data))>>5)
#define SYS_DSS09_DSS_GPU3_dss_c35_wire_sel_shift                                    (4)
#define SYS_DSS09_DSS_GPU3_dss_c35_wire_sel_mask                                     (0x00000010)
#define SYS_DSS09_DSS_GPU3_dss_c35_wire_sel(data)                                    (0x00000010&((data)<<4))
#define SYS_DSS09_DSS_GPU3_dss_c35_wire_sel_src(data)                                ((0x00000010&(data))>>4)
#define SYS_DSS09_DSS_GPU3_get_dss_c35_wire_sel(data)                                ((0x00000010&(data))>>4)
#define SYS_DSS09_DSS_GPU3_dss_c35_ro_sel_shift                                      (1)
#define SYS_DSS09_DSS_GPU3_dss_c35_ro_sel_mask                                       (0x0000000E)
#define SYS_DSS09_DSS_GPU3_dss_c35_ro_sel(data)                                      (0x0000000E&((data)<<1))
#define SYS_DSS09_DSS_GPU3_dss_c35_ro_sel_src(data)                                  ((0x0000000E&(data))>>1)
#define SYS_DSS09_DSS_GPU3_get_dss_c35_ro_sel(data)                                  ((0x0000000E&(data))>>1)
#define SYS_DSS09_DSS_GPU3_dss_c35_dss_rst_n_shift                                   (0)
#define SYS_DSS09_DSS_GPU3_dss_c35_dss_rst_n_mask                                    (0x00000001)
#define SYS_DSS09_DSS_GPU3_dss_c35_dss_rst_n(data)                                   (0x00000001&((data)<<0))
#define SYS_DSS09_DSS_GPU3_dss_c35_dss_rst_n_src(data)                               ((0x00000001&(data))>>0)
#define SYS_DSS09_DSS_GPU3_get_dss_c35_dss_rst_n(data)                               ((0x00000001&(data))>>0)


#define SYS_DSS10_DSS_GPU3                                                           0x18000088
#define SYS_DSS10_DSS_GPU3_reg_addr                                                  "0xB8000088"
#define SYS_DSS10_DSS_GPU3_reg                                                       0xB8000088
#define set_SYS_DSS10_DSS_GPU3_reg(data)   (*((volatile unsigned int*) SYS_DSS10_DSS_GPU3_reg)=data)
#define get_SYS_DSS10_DSS_GPU3_reg   (*((volatile unsigned int*) SYS_DSS10_DSS_GPU3_reg))
#define SYS_DSS10_DSS_GPU3_inst_adr                                                  "0x0022"
#define SYS_DSS10_DSS_GPU3_inst                                                      0x0022
#define SYS_DSS10_DSS_GPU3_dss_c35_wsort_go_shift                                    (21)
#define SYS_DSS10_DSS_GPU3_dss_c35_wsort_go_mask                                     (0x00200000)
#define SYS_DSS10_DSS_GPU3_dss_c35_wsort_go(data)                                    (0x00200000&((data)<<21))
#define SYS_DSS10_DSS_GPU3_dss_c35_wsort_go_src(data)                                ((0x00200000&(data))>>21)
#define SYS_DSS10_DSS_GPU3_get_dss_c35_wsort_go(data)                                ((0x00200000&(data))>>21)
#define SYS_DSS10_DSS_GPU3_dss_c35_count_out_shift                                   (1)
#define SYS_DSS10_DSS_GPU3_dss_c35_count_out_mask                                    (0x001FFFFE)
#define SYS_DSS10_DSS_GPU3_dss_c35_count_out(data)                                   (0x001FFFFE&((data)<<1))
#define SYS_DSS10_DSS_GPU3_dss_c35_count_out_src(data)                               ((0x001FFFFE&(data))>>1)
#define SYS_DSS10_DSS_GPU3_get_dss_c35_count_out(data)                               ((0x001FFFFE&(data))>>1)
#define SYS_DSS10_DSS_GPU3_dss_c35_ready_shift                                       (0)
#define SYS_DSS10_DSS_GPU3_dss_c35_ready_mask                                        (0x00000001)
#define SYS_DSS10_DSS_GPU3_dss_c35_ready(data)                                       (0x00000001&((data)<<0))
#define SYS_DSS10_DSS_GPU3_dss_c35_ready_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_DSS10_DSS_GPU3_get_dss_c35_ready(data)                                   ((0x00000001&(data))>>0)


#define SYS_DSS11_DSS_GPU3                                                           0x1800008C
#define SYS_DSS11_DSS_GPU3_reg_addr                                                  "0xB800008C"
#define SYS_DSS11_DSS_GPU3_reg                                                       0xB800008C
#define set_SYS_DSS11_DSS_GPU3_reg(data)   (*((volatile unsigned int*) SYS_DSS11_DSS_GPU3_reg)=data)
#define get_SYS_DSS11_DSS_GPU3_reg   (*((volatile unsigned int*) SYS_DSS11_DSS_GPU3_reg))
#define SYS_DSS11_DSS_GPU3_inst_adr                                                  "0x0023"
#define SYS_DSS11_DSS_GPU3_inst                                                      0x0023
#define SYS_DSS11_DSS_GPU3_dss_c35_dbgo_shift                                        (0)
#define SYS_DSS11_DSS_GPU3_dss_c35_dbgo_mask                                         (0x0000FFFF)
#define SYS_DSS11_DSS_GPU3_dss_c35_dbgo(data)                                        (0x0000FFFF&((data)<<0))
#define SYS_DSS11_DSS_GPU3_dss_c35_dbgo_src(data)                                    ((0x0000FFFF&(data))>>0)
#define SYS_DSS11_DSS_GPU3_get_dss_c35_dbgo(data)                                    ((0x0000FFFF&(data))>>0)


#define SYS_DSS12_DSS_TOP0                                                           0x18000090
#define SYS_DSS12_DSS_TOP0_reg_addr                                                  "0xB8000090"
#define SYS_DSS12_DSS_TOP0_reg                                                       0xB8000090
#define set_SYS_DSS12_DSS_TOP0_reg(data)   (*((volatile unsigned int*) SYS_DSS12_DSS_TOP0_reg)=data)
#define get_SYS_DSS12_DSS_TOP0_reg   (*((volatile unsigned int*) SYS_DSS12_DSS_TOP0_reg))
#define SYS_DSS12_DSS_TOP0_inst_adr                                                  "0x0024"
#define SYS_DSS12_DSS_TOP0_inst                                                      0x0024
#define SYS_DSS12_DSS_TOP0_dss_c35_speed_en_shift                                    (25)
#define SYS_DSS12_DSS_TOP0_dss_c35_speed_en_mask                                     (0x02000000)
#define SYS_DSS12_DSS_TOP0_dss_c35_speed_en(data)                                    (0x02000000&((data)<<25))
#define SYS_DSS12_DSS_TOP0_dss_c35_speed_en_src(data)                                ((0x02000000&(data))>>25)
#define SYS_DSS12_DSS_TOP0_get_dss_c35_speed_en(data)                                ((0x02000000&(data))>>25)
#define SYS_DSS12_DSS_TOP0_dss_c35_data_in_shift                                     (5)
#define SYS_DSS12_DSS_TOP0_dss_c35_data_in_mask                                      (0x01FFFFE0)
#define SYS_DSS12_DSS_TOP0_dss_c35_data_in(data)                                     (0x01FFFFE0&((data)<<5))
#define SYS_DSS12_DSS_TOP0_dss_c35_data_in_src(data)                                 ((0x01FFFFE0&(data))>>5)
#define SYS_DSS12_DSS_TOP0_get_dss_c35_data_in(data)                                 ((0x01FFFFE0&(data))>>5)
#define SYS_DSS12_DSS_TOP0_dss_c35_wire_sel_shift                                    (4)
#define SYS_DSS12_DSS_TOP0_dss_c35_wire_sel_mask                                     (0x00000010)
#define SYS_DSS12_DSS_TOP0_dss_c35_wire_sel(data)                                    (0x00000010&((data)<<4))
#define SYS_DSS12_DSS_TOP0_dss_c35_wire_sel_src(data)                                ((0x00000010&(data))>>4)
#define SYS_DSS12_DSS_TOP0_get_dss_c35_wire_sel(data)                                ((0x00000010&(data))>>4)
#define SYS_DSS12_DSS_TOP0_dss_c35_ro_sel_shift                                      (1)
#define SYS_DSS12_DSS_TOP0_dss_c35_ro_sel_mask                                       (0x0000000E)
#define SYS_DSS12_DSS_TOP0_dss_c35_ro_sel(data)                                      (0x0000000E&((data)<<1))
#define SYS_DSS12_DSS_TOP0_dss_c35_ro_sel_src(data)                                  ((0x0000000E&(data))>>1)
#define SYS_DSS12_DSS_TOP0_get_dss_c35_ro_sel(data)                                  ((0x0000000E&(data))>>1)
#define SYS_DSS12_DSS_TOP0_dss_c35_dss_rst_n_shift                                   (0)
#define SYS_DSS12_DSS_TOP0_dss_c35_dss_rst_n_mask                                    (0x00000001)
#define SYS_DSS12_DSS_TOP0_dss_c35_dss_rst_n(data)                                   (0x00000001&((data)<<0))
#define SYS_DSS12_DSS_TOP0_dss_c35_dss_rst_n_src(data)                               ((0x00000001&(data))>>0)
#define SYS_DSS12_DSS_TOP0_get_dss_c35_dss_rst_n(data)                               ((0x00000001&(data))>>0)


#define SYS_DSS13_DSS_TOP0                                                           0x18000094
#define SYS_DSS13_DSS_TOP0_reg_addr                                                  "0xB8000094"
#define SYS_DSS13_DSS_TOP0_reg                                                       0xB8000094
#define set_SYS_DSS13_DSS_TOP0_reg(data)   (*((volatile unsigned int*) SYS_DSS13_DSS_TOP0_reg)=data)
#define get_SYS_DSS13_DSS_TOP0_reg   (*((volatile unsigned int*) SYS_DSS13_DSS_TOP0_reg))
#define SYS_DSS13_DSS_TOP0_inst_adr                                                  "0x0025"
#define SYS_DSS13_DSS_TOP0_inst                                                      0x0025
#define SYS_DSS13_DSS_TOP0_dss_c35_wsort_go_shift                                    (21)
#define SYS_DSS13_DSS_TOP0_dss_c35_wsort_go_mask                                     (0x00200000)
#define SYS_DSS13_DSS_TOP0_dss_c35_wsort_go(data)                                    (0x00200000&((data)<<21))
#define SYS_DSS13_DSS_TOP0_dss_c35_wsort_go_src(data)                                ((0x00200000&(data))>>21)
#define SYS_DSS13_DSS_TOP0_get_dss_c35_wsort_go(data)                                ((0x00200000&(data))>>21)
#define SYS_DSS13_DSS_TOP0_dss_c35_count_out_shift                                   (1)
#define SYS_DSS13_DSS_TOP0_dss_c35_count_out_mask                                    (0x001FFFFE)
#define SYS_DSS13_DSS_TOP0_dss_c35_count_out(data)                                   (0x001FFFFE&((data)<<1))
#define SYS_DSS13_DSS_TOP0_dss_c35_count_out_src(data)                               ((0x001FFFFE&(data))>>1)
#define SYS_DSS13_DSS_TOP0_get_dss_c35_count_out(data)                               ((0x001FFFFE&(data))>>1)
#define SYS_DSS13_DSS_TOP0_dss_c35_ready_shift                                       (0)
#define SYS_DSS13_DSS_TOP0_dss_c35_ready_mask                                        (0x00000001)
#define SYS_DSS13_DSS_TOP0_dss_c35_ready(data)                                       (0x00000001&((data)<<0))
#define SYS_DSS13_DSS_TOP0_dss_c35_ready_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_DSS13_DSS_TOP0_get_dss_c35_ready(data)                                   ((0x00000001&(data))>>0)


#define SYS_DSS14_DSS_TOP0                                                           0x18000098
#define SYS_DSS14_DSS_TOP0_reg_addr                                                  "0xB8000098"
#define SYS_DSS14_DSS_TOP0_reg                                                       0xB8000098
#define set_SYS_DSS14_DSS_TOP0_reg(data)   (*((volatile unsigned int*) SYS_DSS14_DSS_TOP0_reg)=data)
#define get_SYS_DSS14_DSS_TOP0_reg   (*((volatile unsigned int*) SYS_DSS14_DSS_TOP0_reg))
#define SYS_DSS14_DSS_TOP0_inst_adr                                                  "0x0026"
#define SYS_DSS14_DSS_TOP0_inst                                                      0x0026
#define SYS_DSS14_DSS_TOP0_dss_c35_dbgo_shift                                        (0)
#define SYS_DSS14_DSS_TOP0_dss_c35_dbgo_mask                                         (0x0000FFFF)
#define SYS_DSS14_DSS_TOP0_dss_c35_dbgo(data)                                        (0x0000FFFF&((data)<<0))
#define SYS_DSS14_DSS_TOP0_dss_c35_dbgo_src(data)                                    ((0x0000FFFF&(data))>>0)
#define SYS_DSS14_DSS_TOP0_get_dss_c35_dbgo(data)                                    ((0x0000FFFF&(data))>>0)


#define SYS_DSS15_DSS_TVSB10                                                         0x1800009C
#define SYS_DSS15_DSS_TVSB10_reg_addr                                                "0xB800009C"
#define SYS_DSS15_DSS_TVSB10_reg                                                     0xB800009C
#define set_SYS_DSS15_DSS_TVSB10_reg(data)   (*((volatile unsigned int*) SYS_DSS15_DSS_TVSB10_reg)=data)
#define get_SYS_DSS15_DSS_TVSB10_reg   (*((volatile unsigned int*) SYS_DSS15_DSS_TVSB10_reg))
#define SYS_DSS15_DSS_TVSB10_inst_adr                                                "0x0027"
#define SYS_DSS15_DSS_TVSB10_inst                                                    0x0027
#define SYS_DSS15_DSS_TVSB10_dss_c35_speed_en_shift                                  (25)
#define SYS_DSS15_DSS_TVSB10_dss_c35_speed_en_mask                                   (0x02000000)
#define SYS_DSS15_DSS_TVSB10_dss_c35_speed_en(data)                                  (0x02000000&((data)<<25))
#define SYS_DSS15_DSS_TVSB10_dss_c35_speed_en_src(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS15_DSS_TVSB10_get_dss_c35_speed_en(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS15_DSS_TVSB10_dss_c35_data_in_shift                                   (5)
#define SYS_DSS15_DSS_TVSB10_dss_c35_data_in_mask                                    (0x01FFFFE0)
#define SYS_DSS15_DSS_TVSB10_dss_c35_data_in(data)                                   (0x01FFFFE0&((data)<<5))
#define SYS_DSS15_DSS_TVSB10_dss_c35_data_in_src(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS15_DSS_TVSB10_get_dss_c35_data_in(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS15_DSS_TVSB10_dss_c35_wire_sel_shift                                  (4)
#define SYS_DSS15_DSS_TVSB10_dss_c35_wire_sel_mask                                   (0x00000010)
#define SYS_DSS15_DSS_TVSB10_dss_c35_wire_sel(data)                                  (0x00000010&((data)<<4))
#define SYS_DSS15_DSS_TVSB10_dss_c35_wire_sel_src(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS15_DSS_TVSB10_get_dss_c35_wire_sel(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS15_DSS_TVSB10_dss_c35_ro_sel_shift                                    (1)
#define SYS_DSS15_DSS_TVSB10_dss_c35_ro_sel_mask                                     (0x0000000E)
#define SYS_DSS15_DSS_TVSB10_dss_c35_ro_sel(data)                                    (0x0000000E&((data)<<1))
#define SYS_DSS15_DSS_TVSB10_dss_c35_ro_sel_src(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS15_DSS_TVSB10_get_dss_c35_ro_sel(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS15_DSS_TVSB10_dss_c35_dss_rst_n_shift                                 (0)
#define SYS_DSS15_DSS_TVSB10_dss_c35_dss_rst_n_mask                                  (0x00000001)
#define SYS_DSS15_DSS_TVSB10_dss_c35_dss_rst_n(data)                                 (0x00000001&((data)<<0))
#define SYS_DSS15_DSS_TVSB10_dss_c35_dss_rst_n_src(data)                             ((0x00000001&(data))>>0)
#define SYS_DSS15_DSS_TVSB10_get_dss_c35_dss_rst_n(data)                             ((0x00000001&(data))>>0)


#define SYS_DSS16_DSS_TVSB10                                                         0x180000A0
#define SYS_DSS16_DSS_TVSB10_reg_addr                                                "0xB80000A0"
#define SYS_DSS16_DSS_TVSB10_reg                                                     0xB80000A0
#define set_SYS_DSS16_DSS_TVSB10_reg(data)   (*((volatile unsigned int*) SYS_DSS16_DSS_TVSB10_reg)=data)
#define get_SYS_DSS16_DSS_TVSB10_reg   (*((volatile unsigned int*) SYS_DSS16_DSS_TVSB10_reg))
#define SYS_DSS16_DSS_TVSB10_inst_adr                                                "0x0028"
#define SYS_DSS16_DSS_TVSB10_inst                                                    0x0028
#define SYS_DSS16_DSS_TVSB10_dss_c35_wsort_go_shift                                  (21)
#define SYS_DSS16_DSS_TVSB10_dss_c35_wsort_go_mask                                   (0x00200000)
#define SYS_DSS16_DSS_TVSB10_dss_c35_wsort_go(data)                                  (0x00200000&((data)<<21))
#define SYS_DSS16_DSS_TVSB10_dss_c35_wsort_go_src(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS16_DSS_TVSB10_get_dss_c35_wsort_go(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS16_DSS_TVSB10_dss_c35_count_out_shift                                 (1)
#define SYS_DSS16_DSS_TVSB10_dss_c35_count_out_mask                                  (0x001FFFFE)
#define SYS_DSS16_DSS_TVSB10_dss_c35_count_out(data)                                 (0x001FFFFE&((data)<<1))
#define SYS_DSS16_DSS_TVSB10_dss_c35_count_out_src(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS16_DSS_TVSB10_get_dss_c35_count_out(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS16_DSS_TVSB10_dss_c35_ready_shift                                     (0)
#define SYS_DSS16_DSS_TVSB10_dss_c35_ready_mask                                      (0x00000001)
#define SYS_DSS16_DSS_TVSB10_dss_c35_ready(data)                                     (0x00000001&((data)<<0))
#define SYS_DSS16_DSS_TVSB10_dss_c35_ready_src(data)                                 ((0x00000001&(data))>>0)
#define SYS_DSS16_DSS_TVSB10_get_dss_c35_ready(data)                                 ((0x00000001&(data))>>0)


#define SYS_DSS17_DSS_TVSB10                                                         0x180000A4
#define SYS_DSS17_DSS_TVSB10_reg_addr                                                "0xB80000A4"
#define SYS_DSS17_DSS_TVSB10_reg                                                     0xB80000A4
#define set_SYS_DSS17_DSS_TVSB10_reg(data)   (*((volatile unsigned int*) SYS_DSS17_DSS_TVSB10_reg)=data)
#define get_SYS_DSS17_DSS_TVSB10_reg   (*((volatile unsigned int*) SYS_DSS17_DSS_TVSB10_reg))
#define SYS_DSS17_DSS_TVSB10_inst_adr                                                "0x0029"
#define SYS_DSS17_DSS_TVSB10_inst                                                    0x0029
#define SYS_DSS17_DSS_TVSB10_dss_c35_dbgo_shift                                      (0)
#define SYS_DSS17_DSS_TVSB10_dss_c35_dbgo_mask                                       (0x0000FFFF)
#define SYS_DSS17_DSS_TVSB10_dss_c35_dbgo(data)                                      (0x0000FFFF&((data)<<0))
#define SYS_DSS17_DSS_TVSB10_dss_c35_dbgo_src(data)                                  ((0x0000FFFF&(data))>>0)
#define SYS_DSS17_DSS_TVSB10_get_dss_c35_dbgo(data)                                  ((0x0000FFFF&(data))>>0)


#define SYS_DSS18_DSS_TVSB11                                                         0x180000A8
#define SYS_DSS18_DSS_TVSB11_reg_addr                                                "0xB80000A8"
#define SYS_DSS18_DSS_TVSB11_reg                                                     0xB80000A8
#define set_SYS_DSS18_DSS_TVSB11_reg(data)   (*((volatile unsigned int*) SYS_DSS18_DSS_TVSB11_reg)=data)
#define get_SYS_DSS18_DSS_TVSB11_reg   (*((volatile unsigned int*) SYS_DSS18_DSS_TVSB11_reg))
#define SYS_DSS18_DSS_TVSB11_inst_adr                                                "0x002A"
#define SYS_DSS18_DSS_TVSB11_inst                                                    0x002A
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_speed_en_shift                                (25)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_speed_en_mask                                 (0x02000000)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_speed_en(data)                                (0x02000000&((data)<<25))
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_speed_en_src(data)                            ((0x02000000&(data))>>25)
#define SYS_DSS18_DSS_TVSB11_get_dss_c35d5_speed_en(data)                            ((0x02000000&(data))>>25)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_data_in_shift                                 (5)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_data_in_mask                                  (0x01FFFFE0)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_data_in(data)                                 (0x01FFFFE0&((data)<<5))
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_data_in_src(data)                             ((0x01FFFFE0&(data))>>5)
#define SYS_DSS18_DSS_TVSB11_get_dss_c35d5_data_in(data)                             ((0x01FFFFE0&(data))>>5)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_wire_sel_shift                                (4)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_wire_sel_mask                                 (0x00000010)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_wire_sel(data)                                (0x00000010&((data)<<4))
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_wire_sel_src(data)                            ((0x00000010&(data))>>4)
#define SYS_DSS18_DSS_TVSB11_get_dss_c35d5_wire_sel(data)                            ((0x00000010&(data))>>4)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_ro_sel_shift                                  (1)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_ro_sel_mask                                   (0x0000000E)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_ro_sel(data)                                  (0x0000000E&((data)<<1))
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_ro_sel_src(data)                              ((0x0000000E&(data))>>1)
#define SYS_DSS18_DSS_TVSB11_get_dss_c35d5_ro_sel(data)                              ((0x0000000E&(data))>>1)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_dss_rst_n_shift                               (0)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_dss_rst_n_mask                                (0x00000001)
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_dss_rst_n(data)                               (0x00000001&((data)<<0))
#define SYS_DSS18_DSS_TVSB11_dss_c35d5_dss_rst_n_src(data)                           ((0x00000001&(data))>>0)
#define SYS_DSS18_DSS_TVSB11_get_dss_c35d5_dss_rst_n(data)                           ((0x00000001&(data))>>0)


#define SYS_DSS19_DSS_TVSB11                                                         0x180000AC
#define SYS_DSS19_DSS_TVSB11_reg_addr                                                "0xB80000AC"
#define SYS_DSS19_DSS_TVSB11_reg                                                     0xB80000AC
#define set_SYS_DSS19_DSS_TVSB11_reg(data)   (*((volatile unsigned int*) SYS_DSS19_DSS_TVSB11_reg)=data)
#define get_SYS_DSS19_DSS_TVSB11_reg   (*((volatile unsigned int*) SYS_DSS19_DSS_TVSB11_reg))
#define SYS_DSS19_DSS_TVSB11_inst_adr                                                "0x002B"
#define SYS_DSS19_DSS_TVSB11_inst                                                    0x002B
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_wsort_go_shift                                (21)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_wsort_go_mask                                 (0x00200000)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_wsort_go(data)                                (0x00200000&((data)<<21))
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_wsort_go_src(data)                            ((0x00200000&(data))>>21)
#define SYS_DSS19_DSS_TVSB11_get_dss_c35d5_wsort_go(data)                            ((0x00200000&(data))>>21)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_count_out_shift                               (1)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_count_out_mask                                (0x001FFFFE)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_count_out(data)                               (0x001FFFFE&((data)<<1))
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_count_out_src(data)                           ((0x001FFFFE&(data))>>1)
#define SYS_DSS19_DSS_TVSB11_get_dss_c35d5_count_out(data)                           ((0x001FFFFE&(data))>>1)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_ready_shift                                   (0)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_ready_mask                                    (0x00000001)
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_ready(data)                                   (0x00000001&((data)<<0))
#define SYS_DSS19_DSS_TVSB11_dss_c35d5_ready_src(data)                               ((0x00000001&(data))>>0)
#define SYS_DSS19_DSS_TVSB11_get_dss_c35d5_ready(data)                               ((0x00000001&(data))>>0)


#define SYS_DSS20_DSS_TVSB11                                                         0x180000B0
#define SYS_DSS20_DSS_TVSB11_reg_addr                                                "0xB80000B0"
#define SYS_DSS20_DSS_TVSB11_reg                                                     0xB80000B0
#define set_SYS_DSS20_DSS_TVSB11_reg(data)   (*((volatile unsigned int*) SYS_DSS20_DSS_TVSB11_reg)=data)
#define get_SYS_DSS20_DSS_TVSB11_reg   (*((volatile unsigned int*) SYS_DSS20_DSS_TVSB11_reg))
#define SYS_DSS20_DSS_TVSB11_inst_adr                                                "0x002C"
#define SYS_DSS20_DSS_TVSB11_inst                                                    0x002C
#define SYS_DSS20_DSS_TVSB11_dss_c35d5_dbgo_shift                                    (0)
#define SYS_DSS20_DSS_TVSB11_dss_c35d5_dbgo_mask                                     (0x0000FFFF)
#define SYS_DSS20_DSS_TVSB11_dss_c35d5_dbgo(data)                                    (0x0000FFFF&((data)<<0))
#define SYS_DSS20_DSS_TVSB11_dss_c35d5_dbgo_src(data)                                ((0x0000FFFF&(data))>>0)
#define SYS_DSS20_DSS_TVSB11_get_dss_c35d5_dbgo(data)                                ((0x0000FFFF&(data))>>0)


#define SYS_DSS21_DSS_TVSB30                                                         0x180000B4
#define SYS_DSS21_DSS_TVSB30_reg_addr                                                "0xB80000B4"
#define SYS_DSS21_DSS_TVSB30_reg                                                     0xB80000B4
#define set_SYS_DSS21_DSS_TVSB30_reg(data)   (*((volatile unsigned int*) SYS_DSS21_DSS_TVSB30_reg)=data)
#define get_SYS_DSS21_DSS_TVSB30_reg   (*((volatile unsigned int*) SYS_DSS21_DSS_TVSB30_reg))
#define SYS_DSS21_DSS_TVSB30_inst_adr                                                "0x002D"
#define SYS_DSS21_DSS_TVSB30_inst                                                    0x002D
#define SYS_DSS21_DSS_TVSB30_dss_c35_speed_en_shift                                  (25)
#define SYS_DSS21_DSS_TVSB30_dss_c35_speed_en_mask                                   (0x02000000)
#define SYS_DSS21_DSS_TVSB30_dss_c35_speed_en(data)                                  (0x02000000&((data)<<25))
#define SYS_DSS21_DSS_TVSB30_dss_c35_speed_en_src(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS21_DSS_TVSB30_get_dss_c35_speed_en(data)                              ((0x02000000&(data))>>25)
#define SYS_DSS21_DSS_TVSB30_dss_c35_data_in_shift                                   (5)
#define SYS_DSS21_DSS_TVSB30_dss_c35_data_in_mask                                    (0x01FFFFE0)
#define SYS_DSS21_DSS_TVSB30_dss_c35_data_in(data)                                   (0x01FFFFE0&((data)<<5))
#define SYS_DSS21_DSS_TVSB30_dss_c35_data_in_src(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS21_DSS_TVSB30_get_dss_c35_data_in(data)                               ((0x01FFFFE0&(data))>>5)
#define SYS_DSS21_DSS_TVSB30_dss_c35_wire_sel_shift                                  (4)
#define SYS_DSS21_DSS_TVSB30_dss_c35_wire_sel_mask                                   (0x00000010)
#define SYS_DSS21_DSS_TVSB30_dss_c35_wire_sel(data)                                  (0x00000010&((data)<<4))
#define SYS_DSS21_DSS_TVSB30_dss_c35_wire_sel_src(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS21_DSS_TVSB30_get_dss_c35_wire_sel(data)                              ((0x00000010&(data))>>4)
#define SYS_DSS21_DSS_TVSB30_dss_c35_ro_sel_shift                                    (1)
#define SYS_DSS21_DSS_TVSB30_dss_c35_ro_sel_mask                                     (0x0000000E)
#define SYS_DSS21_DSS_TVSB30_dss_c35_ro_sel(data)                                    (0x0000000E&((data)<<1))
#define SYS_DSS21_DSS_TVSB30_dss_c35_ro_sel_src(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS21_DSS_TVSB30_get_dss_c35_ro_sel(data)                                ((0x0000000E&(data))>>1)
#define SYS_DSS21_DSS_TVSB30_dss_c35_dss_rst_n_shift                                 (0)
#define SYS_DSS21_DSS_TVSB30_dss_c35_dss_rst_n_mask                                  (0x00000001)
#define SYS_DSS21_DSS_TVSB30_dss_c35_dss_rst_n(data)                                 (0x00000001&((data)<<0))
#define SYS_DSS21_DSS_TVSB30_dss_c35_dss_rst_n_src(data)                             ((0x00000001&(data))>>0)
#define SYS_DSS21_DSS_TVSB30_get_dss_c35_dss_rst_n(data)                             ((0x00000001&(data))>>0)


#define SYS_DSS22_DSS_TVSB30                                                         0x180000B8
#define SYS_DSS22_DSS_TVSB30_reg_addr                                                "0xB80000B8"
#define SYS_DSS22_DSS_TVSB30_reg                                                     0xB80000B8
#define set_SYS_DSS22_DSS_TVSB30_reg(data)   (*((volatile unsigned int*) SYS_DSS22_DSS_TVSB30_reg)=data)
#define get_SYS_DSS22_DSS_TVSB30_reg   (*((volatile unsigned int*) SYS_DSS22_DSS_TVSB30_reg))
#define SYS_DSS22_DSS_TVSB30_inst_adr                                                "0x002E"
#define SYS_DSS22_DSS_TVSB30_inst                                                    0x002E
#define SYS_DSS22_DSS_TVSB30_dss_c35_wsort_go_shift                                  (21)
#define SYS_DSS22_DSS_TVSB30_dss_c35_wsort_go_mask                                   (0x00200000)
#define SYS_DSS22_DSS_TVSB30_dss_c35_wsort_go(data)                                  (0x00200000&((data)<<21))
#define SYS_DSS22_DSS_TVSB30_dss_c35_wsort_go_src(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS22_DSS_TVSB30_get_dss_c35_wsort_go(data)                              ((0x00200000&(data))>>21)
#define SYS_DSS22_DSS_TVSB30_dss_c35_count_out_shift                                 (1)
#define SYS_DSS22_DSS_TVSB30_dss_c35_count_out_mask                                  (0x001FFFFE)
#define SYS_DSS22_DSS_TVSB30_dss_c35_count_out(data)                                 (0x001FFFFE&((data)<<1))
#define SYS_DSS22_DSS_TVSB30_dss_c35_count_out_src(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS22_DSS_TVSB30_get_dss_c35_count_out(data)                             ((0x001FFFFE&(data))>>1)
#define SYS_DSS22_DSS_TVSB30_dss_c35_ready_shift                                     (0)
#define SYS_DSS22_DSS_TVSB30_dss_c35_ready_mask                                      (0x00000001)
#define SYS_DSS22_DSS_TVSB30_dss_c35_ready(data)                                     (0x00000001&((data)<<0))
#define SYS_DSS22_DSS_TVSB30_dss_c35_ready_src(data)                                 ((0x00000001&(data))>>0)
#define SYS_DSS22_DSS_TVSB30_get_dss_c35_ready(data)                                 ((0x00000001&(data))>>0)


#define SYS_DSS23_DSS_TVSB30                                                         0x180000BC
#define SYS_DSS23_DSS_TVSB30_reg_addr                                                "0xB80000BC"
#define SYS_DSS23_DSS_TVSB30_reg                                                     0xB80000BC
#define set_SYS_DSS23_DSS_TVSB30_reg(data)   (*((volatile unsigned int*) SYS_DSS23_DSS_TVSB30_reg)=data)
#define get_SYS_DSS23_DSS_TVSB30_reg   (*((volatile unsigned int*) SYS_DSS23_DSS_TVSB30_reg))
#define SYS_DSS23_DSS_TVSB30_inst_adr                                                "0x002F"
#define SYS_DSS23_DSS_TVSB30_inst                                                    0x002F
#define SYS_DSS23_DSS_TVSB30_dss_c35_dbgo_shift                                      (0)
#define SYS_DSS23_DSS_TVSB30_dss_c35_dbgo_mask                                       (0x0000FFFF)
#define SYS_DSS23_DSS_TVSB30_dss_c35_dbgo(data)                                      (0x0000FFFF&((data)<<0))
#define SYS_DSS23_DSS_TVSB30_dss_c35_dbgo_src(data)                                  ((0x0000FFFF&(data))>>0)
#define SYS_DSS23_DSS_TVSB30_get_dss_c35_dbgo(data)                                  ((0x0000FFFF&(data))>>0)


#define SYS_CSM00_CSM_DDR                                                            0x180007E8
#define SYS_CSM00_CSM_DDR_reg_addr                                                   "0xB80007E8"
#define SYS_CSM00_CSM_DDR_reg                                                        0xB80007E8
#define set_SYS_CSM00_CSM_DDR_reg(data)   (*((volatile unsigned int*) SYS_CSM00_CSM_DDR_reg)=data)
#define get_SYS_CSM00_CSM_DDR_reg   (*((volatile unsigned int*) SYS_CSM00_CSM_DDR_reg))
#define SYS_CSM00_CSM_DDR_inst_adr                                                   "0x00FA"
#define SYS_CSM00_CSM_DDR_inst                                                       0x00FA
#define SYS_CSM00_CSM_DDR_csm0_data_sel_shift                                        (11)
#define SYS_CSM00_CSM_DDR_csm0_data_sel_mask                                         (0x00001800)
#define SYS_CSM00_CSM_DDR_csm0_data_sel(data)                                        (0x00001800&((data)<<11))
#define SYS_CSM00_CSM_DDR_csm0_data_sel_src(data)                                    ((0x00001800&(data))>>11)
#define SYS_CSM00_CSM_DDR_get_csm0_data_sel(data)                                    ((0x00001800&(data))>>11)
#define SYS_CSM00_CSM_DDR_csm0_addr_shift                                            (7)
#define SYS_CSM00_CSM_DDR_csm0_addr_mask                                             (0x00000780)
#define SYS_CSM00_CSM_DDR_csm0_addr(data)                                            (0x00000780&((data)<<7))
#define SYS_CSM00_CSM_DDR_csm0_addr_src(data)                                        ((0x00000780&(data))>>7)
#define SYS_CSM00_CSM_DDR_get_csm0_addr(data)                                        ((0x00000780&(data))>>7)
#define SYS_CSM00_CSM_DDR_csm0_read_en_shift                                         (6)
#define SYS_CSM00_CSM_DDR_csm0_read_en_mask                                          (0x00000040)
#define SYS_CSM00_CSM_DDR_csm0_read_en(data)                                         (0x00000040&((data)<<6))
#define SYS_CSM00_CSM_DDR_csm0_read_en_src(data)                                     ((0x00000040&(data))>>6)
#define SYS_CSM00_CSM_DDR_get_csm0_read_en(data)                                     ((0x00000040&(data))>>6)
#define SYS_CSM00_CSM_DDR_csm0_hold_shift                                            (5)
#define SYS_CSM00_CSM_DDR_csm0_hold_mask                                             (0x00000020)
#define SYS_CSM00_CSM_DDR_csm0_hold(data)                                            (0x00000020&((data)<<5))
#define SYS_CSM00_CSM_DDR_csm0_hold_src(data)                                        ((0x00000020&(data))>>5)
#define SYS_CSM00_CSM_DDR_get_csm0_hold(data)                                        ((0x00000020&(data))>>5)
#define SYS_CSM00_CSM_DDR_csm0_acc_mode_shift                                        (4)
#define SYS_CSM00_CSM_DDR_csm0_acc_mode_mask                                         (0x00000010)
#define SYS_CSM00_CSM_DDR_csm0_acc_mode(data)                                        (0x00000010&((data)<<4))
#define SYS_CSM00_CSM_DDR_csm0_acc_mode_src(data)                                    ((0x00000010&(data))>>4)
#define SYS_CSM00_CSM_DDR_get_csm0_acc_mode(data)                                    ((0x00000010&(data))>>4)
#define SYS_CSM00_CSM_DDR_csm0_in_sel_shift                                          (2)
#define SYS_CSM00_CSM_DDR_csm0_in_sel_mask                                           (0x0000000C)
#define SYS_CSM00_CSM_DDR_csm0_in_sel(data)                                          (0x0000000C&((data)<<2))
#define SYS_CSM00_CSM_DDR_csm0_in_sel_src(data)                                      ((0x0000000C&(data))>>2)
#define SYS_CSM00_CSM_DDR_get_csm0_in_sel(data)                                      ((0x0000000C&(data))>>2)
#define SYS_CSM00_CSM_DDR_csm0_csm_en_shift                                          (1)
#define SYS_CSM00_CSM_DDR_csm0_csm_en_mask                                           (0x00000002)
#define SYS_CSM00_CSM_DDR_csm0_csm_en(data)                                          (0x00000002&((data)<<1))
#define SYS_CSM00_CSM_DDR_csm0_csm_en_src(data)                                      ((0x00000002&(data))>>1)
#define SYS_CSM00_CSM_DDR_get_csm0_csm_en(data)                                      ((0x00000002&(data))>>1)
#define SYS_CSM00_CSM_DDR_csm0_rstn_shift                                            (0)
#define SYS_CSM00_CSM_DDR_csm0_rstn_mask                                             (0x00000001)
#define SYS_CSM00_CSM_DDR_csm0_rstn(data)                                            (0x00000001&((data)<<0))
#define SYS_CSM00_CSM_DDR_csm0_rstn_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_CSM00_CSM_DDR_get_csm0_rstn(data)                                        ((0x00000001&(data))>>0)


#define SYS_CSM01_CSM_DDR                                                            0x180007EC
#define SYS_CSM01_CSM_DDR_reg_addr                                                   "0xB80007EC"
#define SYS_CSM01_CSM_DDR_reg                                                        0xB80007EC
#define set_SYS_CSM01_CSM_DDR_reg(data)   (*((volatile unsigned int*) SYS_CSM01_CSM_DDR_reg)=data)
#define get_SYS_CSM01_CSM_DDR_reg   (*((volatile unsigned int*) SYS_CSM01_CSM_DDR_reg))
#define SYS_CSM01_CSM_DDR_inst_adr                                                   "0x00FB"
#define SYS_CSM01_CSM_DDR_inst                                                       0x00FB
#define SYS_CSM01_CSM_DDR_csm0_ready_shift                                           (0)
#define SYS_CSM01_CSM_DDR_csm0_ready_mask                                            (0x00000001)
#define SYS_CSM01_CSM_DDR_csm0_ready(data)                                           (0x00000001&((data)<<0))
#define SYS_CSM01_CSM_DDR_csm0_ready_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_CSM01_CSM_DDR_get_csm0_ready(data)                                       ((0x00000001&(data))>>0)


#define SYS_CSM02_CSM_DDR                                                            0x180007F0
#define SYS_CSM02_CSM_DDR_reg_addr                                                   "0xB80007F0"
#define SYS_CSM02_CSM_DDR_reg                                                        0xB80007F0
#define set_SYS_CSM02_CSM_DDR_reg(data)   (*((volatile unsigned int*) SYS_CSM02_CSM_DDR_reg)=data)
#define get_SYS_CSM02_CSM_DDR_reg   (*((volatile unsigned int*) SYS_CSM02_CSM_DDR_reg))
#define SYS_CSM02_CSM_DDR_inst_adr                                                   "0x00FC"
#define SYS_CSM02_CSM_DDR_inst                                                       0x00FC
#define SYS_CSM02_CSM_DDR_csm0_data_shift                                            (0)
#define SYS_CSM02_CSM_DDR_csm0_data_mask                                             (0xFFFFFFFF)
#define SYS_CSM02_CSM_DDR_csm0_data(data)                                            (0xFFFFFFFF&((data)<<0))
#define SYS_CSM02_CSM_DDR_csm0_data_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define SYS_CSM02_CSM_DDR_get_csm0_data(data)                                        ((0xFFFFFFFF&(data))>>0)


#define SYS_CSM03_CSM_DDR                                                            0x180007F4
#define SYS_CSM03_CSM_DDR_reg_addr                                                   "0xB80007F4"
#define SYS_CSM03_CSM_DDR_reg                                                        0xB80007F4
#define set_SYS_CSM03_CSM_DDR_reg(data)   (*((volatile unsigned int*) SYS_CSM03_CSM_DDR_reg)=data)
#define get_SYS_CSM03_CSM_DDR_reg   (*((volatile unsigned int*) SYS_CSM03_CSM_DDR_reg))
#define SYS_CSM03_CSM_DDR_inst_adr                                                   "0x00FD"
#define SYS_CSM03_CSM_DDR_inst                                                       0x00FD
#define SYS_CSM03_CSM_DDR_csm1_data_sel_shift                                        (11)
#define SYS_CSM03_CSM_DDR_csm1_data_sel_mask                                         (0x00001800)
#define SYS_CSM03_CSM_DDR_csm1_data_sel(data)                                        (0x00001800&((data)<<11))
#define SYS_CSM03_CSM_DDR_csm1_data_sel_src(data)                                    ((0x00001800&(data))>>11)
#define SYS_CSM03_CSM_DDR_get_csm1_data_sel(data)                                    ((0x00001800&(data))>>11)
#define SYS_CSM03_CSM_DDR_csm1_addr_shift                                            (7)
#define SYS_CSM03_CSM_DDR_csm1_addr_mask                                             (0x00000780)
#define SYS_CSM03_CSM_DDR_csm1_addr(data)                                            (0x00000780&((data)<<7))
#define SYS_CSM03_CSM_DDR_csm1_addr_src(data)                                        ((0x00000780&(data))>>7)
#define SYS_CSM03_CSM_DDR_get_csm1_addr(data)                                        ((0x00000780&(data))>>7)
#define SYS_CSM03_CSM_DDR_csm1_read_en_shift                                         (6)
#define SYS_CSM03_CSM_DDR_csm1_read_en_mask                                          (0x00000040)
#define SYS_CSM03_CSM_DDR_csm1_read_en(data)                                         (0x00000040&((data)<<6))
#define SYS_CSM03_CSM_DDR_csm1_read_en_src(data)                                     ((0x00000040&(data))>>6)
#define SYS_CSM03_CSM_DDR_get_csm1_read_en(data)                                     ((0x00000040&(data))>>6)
#define SYS_CSM03_CSM_DDR_csm1_hold_shift                                            (5)
#define SYS_CSM03_CSM_DDR_csm1_hold_mask                                             (0x00000020)
#define SYS_CSM03_CSM_DDR_csm1_hold(data)                                            (0x00000020&((data)<<5))
#define SYS_CSM03_CSM_DDR_csm1_hold_src(data)                                        ((0x00000020&(data))>>5)
#define SYS_CSM03_CSM_DDR_get_csm1_hold(data)                                        ((0x00000020&(data))>>5)
#define SYS_CSM03_CSM_DDR_csm1_acc_mode_shift                                        (4)
#define SYS_CSM03_CSM_DDR_csm1_acc_mode_mask                                         (0x00000010)
#define SYS_CSM03_CSM_DDR_csm1_acc_mode(data)                                        (0x00000010&((data)<<4))
#define SYS_CSM03_CSM_DDR_csm1_acc_mode_src(data)                                    ((0x00000010&(data))>>4)
#define SYS_CSM03_CSM_DDR_get_csm1_acc_mode(data)                                    ((0x00000010&(data))>>4)
#define SYS_CSM03_CSM_DDR_csm1_in_sel_shift                                          (2)
#define SYS_CSM03_CSM_DDR_csm1_in_sel_mask                                           (0x0000000C)
#define SYS_CSM03_CSM_DDR_csm1_in_sel(data)                                          (0x0000000C&((data)<<2))
#define SYS_CSM03_CSM_DDR_csm1_in_sel_src(data)                                      ((0x0000000C&(data))>>2)
#define SYS_CSM03_CSM_DDR_get_csm1_in_sel(data)                                      ((0x0000000C&(data))>>2)
#define SYS_CSM03_CSM_DDR_csm1_csm_en_shift                                          (1)
#define SYS_CSM03_CSM_DDR_csm1_csm_en_mask                                           (0x00000002)
#define SYS_CSM03_CSM_DDR_csm1_csm_en(data)                                          (0x00000002&((data)<<1))
#define SYS_CSM03_CSM_DDR_csm1_csm_en_src(data)                                      ((0x00000002&(data))>>1)
#define SYS_CSM03_CSM_DDR_get_csm1_csm_en(data)                                      ((0x00000002&(data))>>1)
#define SYS_CSM03_CSM_DDR_csm1_rstn_shift                                            (0)
#define SYS_CSM03_CSM_DDR_csm1_rstn_mask                                             (0x00000001)
#define SYS_CSM03_CSM_DDR_csm1_rstn(data)                                            (0x00000001&((data)<<0))
#define SYS_CSM03_CSM_DDR_csm1_rstn_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_CSM03_CSM_DDR_get_csm1_rstn(data)                                        ((0x00000001&(data))>>0)


#define SYS_CSM04_CSM_DDR                                                            0x180007F8
#define SYS_CSM04_CSM_DDR_reg_addr                                                   "0xB80007F8"
#define SYS_CSM04_CSM_DDR_reg                                                        0xB80007F8
#define set_SYS_CSM04_CSM_DDR_reg(data)   (*((volatile unsigned int*) SYS_CSM04_CSM_DDR_reg)=data)
#define get_SYS_CSM04_CSM_DDR_reg   (*((volatile unsigned int*) SYS_CSM04_CSM_DDR_reg))
#define SYS_CSM04_CSM_DDR_inst_adr                                                   "0x00FE"
#define SYS_CSM04_CSM_DDR_inst                                                       0x00FE
#define SYS_CSM04_CSM_DDR_csm1_ready_shift                                           (0)
#define SYS_CSM04_CSM_DDR_csm1_ready_mask                                            (0x00000001)
#define SYS_CSM04_CSM_DDR_csm1_ready(data)                                           (0x00000001&((data)<<0))
#define SYS_CSM04_CSM_DDR_csm1_ready_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_CSM04_CSM_DDR_get_csm1_ready(data)                                       ((0x00000001&(data))>>0)


#define SYS_CSM05_CSM_DDR                                                            0x180007FC
#define SYS_CSM05_CSM_DDR_reg_addr                                                   "0xB80007FC"
#define SYS_CSM05_CSM_DDR_reg                                                        0xB80007FC
#define set_SYS_CSM05_CSM_DDR_reg(data)   (*((volatile unsigned int*) SYS_CSM05_CSM_DDR_reg)=data)
#define get_SYS_CSM05_CSM_DDR_reg   (*((volatile unsigned int*) SYS_CSM05_CSM_DDR_reg))
#define SYS_CSM05_CSM_DDR_inst_adr                                                   "0x00FF"
#define SYS_CSM05_CSM_DDR_inst                                                       0x00FF
#define SYS_CSM05_CSM_DDR_csm1_data_shift                                            (0)
#define SYS_CSM05_CSM_DDR_csm1_data_mask                                             (0xFFFFFFFF)
#define SYS_CSM05_CSM_DDR_csm1_data(data)                                            (0xFFFFFFFF&((data)<<0))
#define SYS_CSM05_CSM_DDR_csm1_data_src(data)                                        ((0xFFFFFFFF&(data))>>0)
#define SYS_CSM05_CSM_DDR_get_csm1_data(data)                                        ((0xFFFFFFFF&(data))>>0)


#define SYS_CHIP_SRAM_CTRL                                                           0x180000C0
#define SYS_CHIP_SRAM_CTRL_reg_addr                                                  "0xB80000C0"
#define SYS_CHIP_SRAM_CTRL_reg                                                       0xB80000C0
#define set_SYS_CHIP_SRAM_CTRL_reg(data)   (*((volatile unsigned int*) SYS_CHIP_SRAM_CTRL_reg)=data)
#define get_SYS_CHIP_SRAM_CTRL_reg   (*((volatile unsigned int*) SYS_CHIP_SRAM_CTRL_reg))
#define SYS_CHIP_SRAM_CTRL_inst_adr                                                  "0x0030"
#define SYS_CHIP_SRAM_CTRL_inst                                                      0x0030
#define SYS_CHIP_SRAM_CTRL_rme_rom_shift                                             (29)
#define SYS_CHIP_SRAM_CTRL_rme_rom_mask                                              (0x20000000)
#define SYS_CHIP_SRAM_CTRL_rme_rom(data)                                             (0x20000000&((data)<<29))
#define SYS_CHIP_SRAM_CTRL_rme_rom_src(data)                                         ((0x20000000&(data))>>29)
#define SYS_CHIP_SRAM_CTRL_get_rme_rom(data)                                         ((0x20000000&(data))>>29)
#define SYS_CHIP_SRAM_CTRL_rm_rom_shift                                              (25)
#define SYS_CHIP_SRAM_CTRL_rm_rom_mask                                               (0x1E000000)
#define SYS_CHIP_SRAM_CTRL_rm_rom(data)                                              (0x1E000000&((data)<<25))
#define SYS_CHIP_SRAM_CTRL_rm_rom_src(data)                                          ((0x1E000000&(data))>>25)
#define SYS_CHIP_SRAM_CTRL_get_rm_rom(data)                                          ((0x1E000000&(data))>>25)
#define SYS_CHIP_SRAM_CTRL_rme_800_shift                                             (24)
#define SYS_CHIP_SRAM_CTRL_rme_800_mask                                              (0x01000000)
#define SYS_CHIP_SRAM_CTRL_rme_800(data)                                             (0x01000000&((data)<<24))
#define SYS_CHIP_SRAM_CTRL_rme_800_src(data)                                         ((0x01000000&(data))>>24)
#define SYS_CHIP_SRAM_CTRL_get_rme_800(data)                                         ((0x01000000&(data))>>24)
#define SYS_CHIP_SRAM_CTRL_rm_800_shift                                              (20)
#define SYS_CHIP_SRAM_CTRL_rm_800_mask                                               (0x00F00000)
#define SYS_CHIP_SRAM_CTRL_rm_800(data)                                              (0x00F00000&((data)<<20))
#define SYS_CHIP_SRAM_CTRL_rm_800_src(data)                                          ((0x00F00000&(data))>>20)
#define SYS_CHIP_SRAM_CTRL_get_rm_800(data)                                          ((0x00F00000&(data))>>20)
#define SYS_CHIP_SRAM_CTRL_rme_600_shift                                             (19)
#define SYS_CHIP_SRAM_CTRL_rme_600_mask                                              (0x00080000)
#define SYS_CHIP_SRAM_CTRL_rme_600(data)                                             (0x00080000&((data)<<19))
#define SYS_CHIP_SRAM_CTRL_rme_600_src(data)                                         ((0x00080000&(data))>>19)
#define SYS_CHIP_SRAM_CTRL_get_rme_600(data)                                         ((0x00080000&(data))>>19)
#define SYS_CHIP_SRAM_CTRL_rm_600_shift                                              (15)
#define SYS_CHIP_SRAM_CTRL_rm_600_mask                                               (0x00078000)
#define SYS_CHIP_SRAM_CTRL_rm_600(data)                                              (0x00078000&((data)<<15))
#define SYS_CHIP_SRAM_CTRL_rm_600_src(data)                                          ((0x00078000&(data))>>15)
#define SYS_CHIP_SRAM_CTRL_get_rm_600(data)                                          ((0x00078000&(data))>>15)
#define SYS_CHIP_SRAM_CTRL_rme_400_shift                                             (14)
#define SYS_CHIP_SRAM_CTRL_rme_400_mask                                              (0x00004000)
#define SYS_CHIP_SRAM_CTRL_rme_400(data)                                             (0x00004000&((data)<<14))
#define SYS_CHIP_SRAM_CTRL_rme_400_src(data)                                         ((0x00004000&(data))>>14)
#define SYS_CHIP_SRAM_CTRL_get_rme_400(data)                                         ((0x00004000&(data))>>14)
#define SYS_CHIP_SRAM_CTRL_rm_400_shift                                              (10)
#define SYS_CHIP_SRAM_CTRL_rm_400_mask                                               (0x00003C00)
#define SYS_CHIP_SRAM_CTRL_rm_400(data)                                              (0x00003C00&((data)<<10))
#define SYS_CHIP_SRAM_CTRL_rm_400_src(data)                                          ((0x00003C00&(data))>>10)
#define SYS_CHIP_SRAM_CTRL_get_rm_400(data)                                          ((0x00003C00&(data))>>10)
#define SYS_CHIP_SRAM_CTRL_rme_300_shift                                             (9)
#define SYS_CHIP_SRAM_CTRL_rme_300_mask                                              (0x00000200)
#define SYS_CHIP_SRAM_CTRL_rme_300(data)                                             (0x00000200&((data)<<9))
#define SYS_CHIP_SRAM_CTRL_rme_300_src(data)                                         ((0x00000200&(data))>>9)
#define SYS_CHIP_SRAM_CTRL_get_rme_300(data)                                         ((0x00000200&(data))>>9)
#define SYS_CHIP_SRAM_CTRL_rm_300_shift                                              (5)
#define SYS_CHIP_SRAM_CTRL_rm_300_mask                                               (0x000001E0)
#define SYS_CHIP_SRAM_CTRL_rm_300(data)                                              (0x000001E0&((data)<<5))
#define SYS_CHIP_SRAM_CTRL_rm_300_src(data)                                          ((0x000001E0&(data))>>5)
#define SYS_CHIP_SRAM_CTRL_get_rm_300(data)                                          ((0x000001E0&(data))>>5)
#define SYS_CHIP_SRAM_CTRL_rme_200_shift                                             (4)
#define SYS_CHIP_SRAM_CTRL_rme_200_mask                                              (0x00000010)
#define SYS_CHIP_SRAM_CTRL_rme_200(data)                                             (0x00000010&((data)<<4))
#define SYS_CHIP_SRAM_CTRL_rme_200_src(data)                                         ((0x00000010&(data))>>4)
#define SYS_CHIP_SRAM_CTRL_get_rme_200(data)                                         ((0x00000010&(data))>>4)
#define SYS_CHIP_SRAM_CTRL_rm_200_shift                                              (0)
#define SYS_CHIP_SRAM_CTRL_rm_200_mask                                               (0x0000000F)
#define SYS_CHIP_SRAM_CTRL_rm_200(data)                                              (0x0000000F&((data)<<0))
#define SYS_CHIP_SRAM_CTRL_rm_200_src(data)                                          ((0x0000000F&(data))>>0)
#define SYS_CHIP_SRAM_CTRL_get_rm_200(data)                                          ((0x0000000F&(data))>>0)


#define SYS_CHIP_MISC_CTRL                                                           0x180000C4
#define SYS_CHIP_MISC_CTRL_reg_addr                                                  "0xB80000C4"
#define SYS_CHIP_MISC_CTRL_reg                                                       0xB80000C4
#define set_SYS_CHIP_MISC_CTRL_reg(data)   (*((volatile unsigned int*) SYS_CHIP_MISC_CTRL_reg)=data)
#define get_SYS_CHIP_MISC_CTRL_reg   (*((volatile unsigned int*) SYS_CHIP_MISC_CTRL_reg))
#define SYS_CHIP_MISC_CTRL_inst_adr                                                  "0x0031"
#define SYS_CHIP_MISC_CTRL_inst                                                      0x0031
#define SYS_CHIP_MISC_CTRL_resume_cycle_sel_shift                                    (0)
#define SYS_CHIP_MISC_CTRL_resume_cycle_sel_mask                                     (0x00000001)
#define SYS_CHIP_MISC_CTRL_resume_cycle_sel(data)                                    (0x00000001&((data)<<0))
#define SYS_CHIP_MISC_CTRL_resume_cycle_sel_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CHIP_MISC_CTRL_get_resume_cycle_sel(data)                                ((0x00000001&(data))>>0)


#define SYS_CHIP_INFO2                                                               0x180000C8
#define SYS_CHIP_INFO2_reg_addr                                                      "0xB80000C8"
#define SYS_CHIP_INFO2_reg                                                           0xB80000C8
#define set_SYS_CHIP_INFO2_reg(data)   (*((volatile unsigned int*) SYS_CHIP_INFO2_reg)=data)
#define get_SYS_CHIP_INFO2_reg   (*((volatile unsigned int*) SYS_CHIP_INFO2_reg))
#define SYS_CHIP_INFO2_inst_adr                                                      "0x0032"
#define SYS_CHIP_INFO2_inst                                                          0x0032
#define SYS_CHIP_INFO2_clk_na_fail_shift                                             (8)
#define SYS_CHIP_INFO2_clk_na_fail_mask                                              (0x00000100)
#define SYS_CHIP_INFO2_clk_na_fail(data)                                             (0x00000100&((data)<<8))
#define SYS_CHIP_INFO2_clk_na_fail_src(data)                                         ((0x00000100&(data))>>8)
#define SYS_CHIP_INFO2_get_clk_na_fail(data)                                         ((0x00000100&(data))>>8)
#define SYS_CHIP_INFO2_testmode_shift                                                (2)
#define SYS_CHIP_INFO2_testmode_mask                                                 (0x00000004)
#define SYS_CHIP_INFO2_testmode(data)                                                (0x00000004&((data)<<2))
#define SYS_CHIP_INFO2_testmode_src(data)                                            ((0x00000004&(data))>>2)
#define SYS_CHIP_INFO2_get_testmode(data)                                            ((0x00000004&(data))>>2)
#define SYS_CHIP_INFO2_nf_sel_shift                                                  (1)
#define SYS_CHIP_INFO2_nf_sel_mask                                                   (0x00000002)
#define SYS_CHIP_INFO2_nf_sel(data)                                                  (0x00000002&((data)<<1))
#define SYS_CHIP_INFO2_nf_sel_src(data)                                              ((0x00000002&(data))>>1)
#define SYS_CHIP_INFO2_get_nf_sel(data)                                              ((0x00000002&(data))>>1)
#define SYS_CHIP_INFO2_sf_sel_shift                                                  (0)
#define SYS_CHIP_INFO2_sf_sel_mask                                                   (0x00000001)
#define SYS_CHIP_INFO2_sf_sel(data)                                                  (0x00000001&((data)<<0))
#define SYS_CHIP_INFO2_sf_sel_src(data)                                              ((0x00000001&(data))>>0)
#define SYS_CHIP_INFO2_get_sf_sel(data)                                              ((0x00000001&(data))>>0)


#define SYS_APS_CTL                                                                  0x180000CC
#define SYS_APS_CTL_reg_addr                                                         "0xB80000CC"
#define SYS_APS_CTL_reg                                                              0xB80000CC
#define set_SYS_APS_CTL_reg(data)   (*((volatile unsigned int*) SYS_APS_CTL_reg)=data)
#define get_SYS_APS_CTL_reg   (*((volatile unsigned int*) SYS_APS_CTL_reg))
#define SYS_APS_CTL_inst_adr                                                         "0x0033"
#define SYS_APS_CTL_inst                                                             0x0033
#define SYS_APS_CTL_write_en2_shift                                                  (1)
#define SYS_APS_CTL_write_en2_mask                                                   (0x00000002)
#define SYS_APS_CTL_write_en2(data)                                                  (0x00000002&((data)<<1))
#define SYS_APS_CTL_write_en2_src(data)                                              ((0x00000002&(data))>>1)
#define SYS_APS_CTL_get_write_en2(data)                                              ((0x00000002&(data))>>1)
#define SYS_APS_CTL_dds_rstn_shift                                                   (0)
#define SYS_APS_CTL_dds_rstn_mask                                                    (0x00000001)
#define SYS_APS_CTL_dds_rstn(data)                                                   (0x00000001&((data)<<0))
#define SYS_APS_CTL_dds_rstn_src(data)                                               ((0x00000001&(data))>>0)
#define SYS_APS_CTL_get_dds_rstn(data)                                               ((0x00000001&(data))>>0)


#define SYS_PWDN_CTRL                                                                0x180000D0
#define SYS_PWDN_CTRL_reg_addr                                                       "0xB80000D0"
#define SYS_PWDN_CTRL_reg                                                            0xB80000D0
#define set_SYS_PWDN_CTRL_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL_reg)=data)
#define get_SYS_PWDN_CTRL_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL_reg))
#define SYS_PWDN_CTRL_inst_adr                                                       "0x0034"
#define SYS_PWDN_CTRL_inst                                                           0x0034
#define SYS_PWDN_CTRL_kcpu_boot_info_shift                                           (0)
#define SYS_PWDN_CTRL_kcpu_boot_info_mask                                            (0xFFFFFFFF)
#define SYS_PWDN_CTRL_kcpu_boot_info(data)                                           (0xFFFFFFFF&((data)<<0))
#define SYS_PWDN_CTRL_kcpu_boot_info_src(data)                                       ((0xFFFFFFFF&(data))>>0)
#define SYS_PWDN_CTRL_get_kcpu_boot_info(data)                                       ((0xFFFFFFFF&(data))>>0)


#define SYS_PWDN_CTRL2                                                               0x180000D4
#define SYS_PWDN_CTRL2_reg_addr                                                      "0xB80000D4"
#define SYS_PWDN_CTRL2_reg                                                           0xB80000D4
#define set_SYS_PWDN_CTRL2_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL2_reg)=data)
#define get_SYS_PWDN_CTRL2_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL2_reg))
#define SYS_PWDN_CTRL2_inst_adr                                                      "0x0035"
#define SYS_PWDN_CTRL2_inst                                                          0x0035
#define SYS_PWDN_CTRL2_acpu_boot_info_shift                                          (0)
#define SYS_PWDN_CTRL2_acpu_boot_info_mask                                           (0xFFFFFFFF)
#define SYS_PWDN_CTRL2_acpu_boot_info(data)                                          (0xFFFFFFFF&((data)<<0))
#define SYS_PWDN_CTRL2_acpu_boot_info_src(data)                                      ((0xFFFFFFFF&(data))>>0)
#define SYS_PWDN_CTRL2_get_acpu_boot_info(data)                                      ((0xFFFFFFFF&(data))>>0)


#define SYS_PWDN_CTRL3                                                               0x180000D8
#define SYS_PWDN_CTRL3_reg_addr                                                      "0xB80000D8"
#define SYS_PWDN_CTRL3_reg                                                           0xB80000D8
#define set_SYS_PWDN_CTRL3_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL3_reg)=data)
#define get_SYS_PWDN_CTRL3_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL3_reg))
#define SYS_PWDN_CTRL3_inst_adr                                                      "0x0036"
#define SYS_PWDN_CTRL3_inst                                                          0x0036
#define SYS_PWDN_CTRL3_write_en2_shift                                               (3)
#define SYS_PWDN_CTRL3_write_en2_mask                                                (0x00000008)
#define SYS_PWDN_CTRL3_write_en2(data)                                               (0x00000008&((data)<<3))
#define SYS_PWDN_CTRL3_write_en2_src(data)                                           ((0x00000008&(data))>>3)
#define SYS_PWDN_CTRL3_get_write_en2(data)                                           ((0x00000008&(data))>>3)
#define SYS_PWDN_CTRL3_kcpu_boot_info_valid_shift                                    (2)
#define SYS_PWDN_CTRL3_kcpu_boot_info_valid_mask                                     (0x00000004)
#define SYS_PWDN_CTRL3_kcpu_boot_info_valid(data)                                    (0x00000004&((data)<<2))
#define SYS_PWDN_CTRL3_kcpu_boot_info_valid_src(data)                                ((0x00000004&(data))>>2)
#define SYS_PWDN_CTRL3_get_kcpu_boot_info_valid(data)                                ((0x00000004&(data))>>2)
#define SYS_PWDN_CTRL3_write_en1_shift                                               (1)
#define SYS_PWDN_CTRL3_write_en1_mask                                                (0x00000002)
#define SYS_PWDN_CTRL3_write_en1(data)                                               (0x00000002&((data)<<1))
#define SYS_PWDN_CTRL3_write_en1_src(data)                                           ((0x00000002&(data))>>1)
#define SYS_PWDN_CTRL3_get_write_en1(data)                                           ((0x00000002&(data))>>1)
#define SYS_PWDN_CTRL3_kcpu_sw_rst_shift                                             (0)
#define SYS_PWDN_CTRL3_kcpu_sw_rst_mask                                              (0x00000001)
#define SYS_PWDN_CTRL3_kcpu_sw_rst(data)                                             (0x00000001&((data)<<0))
#define SYS_PWDN_CTRL3_kcpu_sw_rst_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_PWDN_CTRL3_get_kcpu_sw_rst(data)                                         ((0x00000001&(data))>>0)


#define SYS_PWDN_CTRL4                                                               0x180000DC
#define SYS_PWDN_CTRL4_reg_addr                                                      "0xB80000DC"
#define SYS_PWDN_CTRL4_reg                                                           0xB80000DC
#define set_SYS_PWDN_CTRL4_reg(data)   (*((volatile unsigned int*) SYS_PWDN_CTRL4_reg)=data)
#define get_SYS_PWDN_CTRL4_reg   (*((volatile unsigned int*) SYS_PWDN_CTRL4_reg))
#define SYS_PWDN_CTRL4_inst_adr                                                      "0x0037"
#define SYS_PWDN_CTRL4_inst                                                          0x0037
#define SYS_PWDN_CTRL4_acpu_boot_info_valid_shift                                    (0)
#define SYS_PWDN_CTRL4_acpu_boot_info_valid_mask                                     (0x00000001)
#define SYS_PWDN_CTRL4_acpu_boot_info_valid(data)                                    (0x00000001&((data)<<0))
#define SYS_PWDN_CTRL4_acpu_boot_info_valid_src(data)                                ((0x00000001&(data))>>0)
#define SYS_PWDN_CTRL4_get_acpu_boot_info_valid(data)                                ((0x00000001&(data))>>0)


#define SYS_AT_SPEED                                                                 0x180000E0
#define SYS_AT_SPEED_reg_addr                                                        "0xB80000E0"
#define SYS_AT_SPEED_reg                                                             0xB80000E0
#define set_SYS_AT_SPEED_reg(data)   (*((volatile unsigned int*) SYS_AT_SPEED_reg)=data)
#define get_SYS_AT_SPEED_reg   (*((volatile unsigned int*) SYS_AT_SPEED_reg))
#define SYS_AT_SPEED_inst_adr                                                        "0x0038"
#define SYS_AT_SPEED_inst                                                            0x0038
#define SYS_AT_SPEED_write_en2_shift                                                 (3)
#define SYS_AT_SPEED_write_en2_mask                                                  (0x00000008)
#define SYS_AT_SPEED_write_en2(data)                                                 (0x00000008&((data)<<3))
#define SYS_AT_SPEED_write_en2_src(data)                                             ((0x00000008&(data))>>3)
#define SYS_AT_SPEED_get_write_en2(data)                                             ((0x00000008&(data))>>3)
#define SYS_AT_SPEED_dac_test_shift                                                  (2)
#define SYS_AT_SPEED_dac_test_mask                                                   (0x00000004)
#define SYS_AT_SPEED_dac_test(data)                                                  (0x00000004&((data)<<2))
#define SYS_AT_SPEED_dac_test_src(data)                                              ((0x00000004&(data))>>2)
#define SYS_AT_SPEED_get_dac_test(data)                                              ((0x00000004&(data))>>2)
#define SYS_AT_SPEED_write_en1_shift                                                 (1)
#define SYS_AT_SPEED_write_en1_mask                                                  (0x00000002)
#define SYS_AT_SPEED_write_en1(data)                                                 (0x00000002&((data)<<1))
#define SYS_AT_SPEED_write_en1_src(data)                                             ((0x00000002&(data))>>1)
#define SYS_AT_SPEED_get_write_en1(data)                                             ((0x00000002&(data))>>1)
#define SYS_AT_SPEED_scpu_config_done_shift                                          (0)
#define SYS_AT_SPEED_scpu_config_done_mask                                           (0x00000001)
#define SYS_AT_SPEED_scpu_config_done(data)                                          (0x00000001&((data)<<0))
#define SYS_AT_SPEED_scpu_config_done_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_AT_SPEED_get_scpu_config_done(data)                                      ((0x00000001&(data))>>0)


#define SYS_ANA_CTRL                                                                 0x180000E4
#define SYS_ANA_CTRL_reg_addr                                                        "0xB80000E4"
#define SYS_ANA_CTRL_reg                                                             0xB80000E4
#define set_SYS_ANA_CTRL_reg(data)   (*((volatile unsigned int*) SYS_ANA_CTRL_reg)=data)
#define get_SYS_ANA_CTRL_reg   (*((volatile unsigned int*) SYS_ANA_CTRL_reg))
#define SYS_ANA_CTRL_inst_adr                                                        "0x0039"
#define SYS_ANA_CTRL_inst                                                            0x0039
#define SYS_ANA_CTRL_write_en2_shift                                                 (3)
#define SYS_ANA_CTRL_write_en2_mask                                                  (0x00000008)
#define SYS_ANA_CTRL_write_en2(data)                                                 (0x00000008&((data)<<3))
#define SYS_ANA_CTRL_write_en2_src(data)                                             ((0x00000008&(data))>>3)
#define SYS_ANA_CTRL_get_write_en2(data)                                             ((0x00000008&(data))>>3)
#define SYS_ANA_CTRL_etn_phy_gpio_en_shift                                           (2)
#define SYS_ANA_CTRL_etn_phy_gpio_en_mask                                            (0x00000004)
#define SYS_ANA_CTRL_etn_phy_gpio_en(data)                                           (0x00000004&((data)<<2))
#define SYS_ANA_CTRL_etn_phy_gpio_en_src(data)                                       ((0x00000004&(data))>>2)
#define SYS_ANA_CTRL_get_etn_phy_gpio_en(data)                                       ((0x00000004&(data))>>2)
#define SYS_ANA_CTRL_write_en1_shift                                                 (1)
#define SYS_ANA_CTRL_write_en1_mask                                                  (0x00000002)
#define SYS_ANA_CTRL_write_en1(data)                                                 (0x00000002&((data)<<1))
#define SYS_ANA_CTRL_write_en1_src(data)                                             ((0x00000002&(data))>>1)
#define SYS_ANA_CTRL_get_write_en1(data)                                             ((0x00000002&(data))>>1)
#define SYS_ANA_CTRL_etn_phy_125m_en_shift                                           (0)
#define SYS_ANA_CTRL_etn_phy_125m_en_mask                                            (0x00000001)
#define SYS_ANA_CTRL_etn_phy_125m_en(data)                                           (0x00000001&((data)<<0))
#define SYS_ANA_CTRL_etn_phy_125m_en_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_ANA_CTRL_get_etn_phy_125m_en(data)                                       ((0x00000001&(data))>>0)


#define SYS_TP_DEMOD_CTRL                                                            0x180000E8
#define SYS_TP_DEMOD_CTRL_reg_addr                                                   "0xB80000E8"
#define SYS_TP_DEMOD_CTRL_reg                                                        0xB80000E8
#define set_SYS_TP_DEMOD_CTRL_reg(data)   (*((volatile unsigned int*) SYS_TP_DEMOD_CTRL_reg)=data)
#define get_SYS_TP_DEMOD_CTRL_reg   (*((volatile unsigned int*) SYS_TP_DEMOD_CTRL_reg))
#define SYS_TP_DEMOD_CTRL_inst_adr                                                   "0x003A"
#define SYS_TP_DEMOD_CTRL_inst                                                       0x003A
#define SYS_TP_DEMOD_CTRL_demod_i2c_saddr_shift                                      (4)
#define SYS_TP_DEMOD_CTRL_demod_i2c_saddr_mask                                       (0x00000010)
#define SYS_TP_DEMOD_CTRL_demod_i2c_saddr(data)                                      (0x00000010&((data)<<4))
#define SYS_TP_DEMOD_CTRL_demod_i2c_saddr_src(data)                                  ((0x00000010&(data))>>4)
#define SYS_TP_DEMOD_CTRL_get_demod_i2c_saddr(data)                                  ((0x00000010&(data))>>4)
#define SYS_TP_DEMOD_CTRL_demod_i2c_sel_shift                                        (3)
#define SYS_TP_DEMOD_CTRL_demod_i2c_sel_mask                                         (0x00000008)
#define SYS_TP_DEMOD_CTRL_demod_i2c_sel(data)                                        (0x00000008&((data)<<3))
#define SYS_TP_DEMOD_CTRL_demod_i2c_sel_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_TP_DEMOD_CTRL_get_demod_i2c_sel(data)                                    ((0x00000008&(data))>>3)
#define SYS_TP_DEMOD_CTRL_tp2_dm_sel_shift                                           (2)
#define SYS_TP_DEMOD_CTRL_tp2_dm_sel_mask                                            (0x00000004)
#define SYS_TP_DEMOD_CTRL_tp2_dm_sel(data)                                           (0x00000004&((data)<<2))
#define SYS_TP_DEMOD_CTRL_tp2_dm_sel_src(data)                                       ((0x00000004&(data))>>2)
#define SYS_TP_DEMOD_CTRL_get_tp2_dm_sel(data)                                       ((0x00000004&(data))>>2)
#define SYS_TP_DEMOD_CTRL_tp1_dm_sel_shift                                           (1)
#define SYS_TP_DEMOD_CTRL_tp1_dm_sel_mask                                            (0x00000002)
#define SYS_TP_DEMOD_CTRL_tp1_dm_sel(data)                                           (0x00000002&((data)<<1))
#define SYS_TP_DEMOD_CTRL_tp1_dm_sel_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_TP_DEMOD_CTRL_get_tp1_dm_sel(data)                                       ((0x00000002&(data))>>1)
#define SYS_TP_DEMOD_CTRL_tp0_dm_sel_shift                                           (0)
#define SYS_TP_DEMOD_CTRL_tp0_dm_sel_mask                                            (0x00000001)
#define SYS_TP_DEMOD_CTRL_tp0_dm_sel(data)                                           (0x00000001&((data)<<0))
#define SYS_TP_DEMOD_CTRL_tp0_dm_sel_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_TP_DEMOD_CTRL_get_tp0_dm_sel(data)                                       ((0x00000001&(data))>>0)


#define SYS_CONTROL0                                                                 0x180000EC
#define SYS_CONTROL0_reg_addr                                                        "0xB80000EC"
#define SYS_CONTROL0_reg                                                             0xB80000EC
#define set_SYS_CONTROL0_reg(data)   (*((volatile unsigned int*) SYS_CONTROL0_reg)=data)
#define get_SYS_CONTROL0_reg   (*((volatile unsigned int*) SYS_CONTROL0_reg))
#define SYS_CONTROL0_inst_adr                                                        "0x003B"
#define SYS_CONTROL0_inst                                                            0x003B
#define SYS_CONTROL0_sf_en_shift                                                     (0)
#define SYS_CONTROL0_sf_en_mask                                                      (0x00000001)
#define SYS_CONTROL0_sf_en(data)                                                     (0x00000001&((data)<<0))
#define SYS_CONTROL0_sf_en_src(data)                                                 ((0x00000001&(data))>>0)
#define SYS_CONTROL0_get_sf_en(data)                                                 ((0x00000001&(data))>>0)


#define SYS_SECURITY_ST                                                              0x180000F0
#define SYS_SECURITY_ST_reg_addr                                                     "0xB80000F0"
#define SYS_SECURITY_ST_reg                                                          0xB80000F0
#define set_SYS_SECURITY_ST_reg(data)   (*((volatile unsigned int*) SYS_SECURITY_ST_reg)=data)
#define get_SYS_SECURITY_ST_reg   (*((volatile unsigned int*) SYS_SECURITY_ST_reg))
#define SYS_SECURITY_ST_inst_adr                                                     "0x003C"
#define SYS_SECURITY_ST_inst                                                         0x003C
#define SYS_SECURITY_ST_akl_busy_shift                                               (0)
#define SYS_SECURITY_ST_akl_busy_mask                                                (0x00000001)
#define SYS_SECURITY_ST_akl_busy(data)                                               (0x00000001&((data)<<0))
#define SYS_SECURITY_ST_akl_busy_src(data)                                           ((0x00000001&(data))>>0)
#define SYS_SECURITY_ST_get_akl_busy(data)                                           ((0x00000001&(data))>>0)


#define SYS_DMY2                                                                     0x180000F4
#define SYS_DMY2_reg_addr                                                            "0xB80000F4"
#define SYS_DMY2_reg                                                                 0xB80000F4
#define set_SYS_DMY2_reg(data)   (*((volatile unsigned int*) SYS_DMY2_reg)=data)
#define get_SYS_DMY2_reg   (*((volatile unsigned int*) SYS_DMY2_reg))
#define SYS_DMY2_inst_adr                                                            "0x003D"
#define SYS_DMY2_inst                                                                0x003D
#define SYS_DMY2_Rvd1_shift                                                          (0)
#define SYS_DMY2_Rvd1_mask                                                           (0xFFFFFFFF)
#define SYS_DMY2_Rvd1(data)                                                          (0xFFFFFFFF&((data)<<0))
#define SYS_DMY2_Rvd1_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define SYS_DMY2_get_Rvd1(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define SYS_BUS_PLL_SSC                                                              0x180000F8
#define SYS_BUS_PLL_SSC_reg_addr                                                     "0xB80000F8"
#define SYS_BUS_PLL_SSC_reg                                                          0xB80000F8
#define set_SYS_BUS_PLL_SSC_reg(data)   (*((volatile unsigned int*) SYS_BUS_PLL_SSC_reg)=data)
#define get_SYS_BUS_PLL_SSC_reg   (*((volatile unsigned int*) SYS_BUS_PLL_SSC_reg))
#define SYS_BUS_PLL_SSC_inst_adr                                                     "0x003E"
#define SYS_BUS_PLL_SSC_inst                                                         0x003E
#define SYS_BUS_PLL_SSC_bus_ssc_sse_shift                                            (31)
#define SYS_BUS_PLL_SSC_bus_ssc_sse_mask                                             (0x80000000)
#define SYS_BUS_PLL_SSC_bus_ssc_sse(data)                                            (0x80000000&((data)<<31))
#define SYS_BUS_PLL_SSC_bus_ssc_sse_src(data)                                        ((0x80000000&(data))>>31)
#define SYS_BUS_PLL_SSC_get_bus_ssc_sse(data)                                        ((0x80000000&(data))>>31)
#define SYS_BUS_PLL_SSC_bus_ssc_ckinv_shift                                          (30)
#define SYS_BUS_PLL_SSC_bus_ssc_ckinv_mask                                           (0x40000000)
#define SYS_BUS_PLL_SSC_bus_ssc_ckinv(data)                                          (0x40000000&((data)<<30))
#define SYS_BUS_PLL_SSC_bus_ssc_ckinv_src(data)                                      ((0x40000000&(data))>>30)
#define SYS_BUS_PLL_SSC_get_bus_ssc_ckinv(data)                                      ((0x40000000&(data))>>30)
#define SYS_BUS_PLL_SSC_bus_ssc_sss_shift                                            (24)
#define SYS_BUS_PLL_SSC_bus_ssc_sss_mask                                             (0x3F000000)
#define SYS_BUS_PLL_SSC_bus_ssc_sss(data)                                            (0x3F000000&((data)<<24))
#define SYS_BUS_PLL_SSC_bus_ssc_sss_src(data)                                        ((0x3F000000&(data))>>24)
#define SYS_BUS_PLL_SSC_get_bus_ssc_sss(data)                                        ((0x3F000000&(data))>>24)
#define SYS_BUS_PLL_SSC_bus_ssc_ssn_shift                                            (16)
#define SYS_BUS_PLL_SSC_bus_ssc_ssn_mask                                             (0x007F0000)
#define SYS_BUS_PLL_SSC_bus_ssc_ssn(data)                                            (0x007F0000&((data)<<16))
#define SYS_BUS_PLL_SSC_bus_ssc_ssn_src(data)                                        ((0x007F0000&(data))>>16)
#define SYS_BUS_PLL_SSC_get_bus_ssc_ssn(data)                                        ((0x007F0000&(data))>>16)
#define SYS_BUS_PLL_SSC_bus_ssc_ssfpv_shift                                          (8)
#define SYS_BUS_PLL_SSC_bus_ssc_ssfpv_mask                                           (0x0000FF00)
#define SYS_BUS_PLL_SSC_bus_ssc_ssfpv(data)                                          (0x0000FF00&((data)<<8))
#define SYS_BUS_PLL_SSC_bus_ssc_ssfpv_src(data)                                      ((0x0000FF00&(data))>>8)
#define SYS_BUS_PLL_SSC_get_bus_ssc_ssfpv(data)                                      ((0x0000FF00&(data))>>8)
#define SYS_BUS_PLL_SSC_bus_ssc_stms_shift                                           (0)
#define SYS_BUS_PLL_SSC_bus_ssc_stms_mask                                            (0x00000003)
#define SYS_BUS_PLL_SSC_bus_ssc_stms(data)                                           (0x00000003&((data)<<0))
#define SYS_BUS_PLL_SSC_bus_ssc_stms_src(data)                                       ((0x00000003&(data))>>0)
#define SYS_BUS_PLL_SSC_get_bus_ssc_stms(data)                                       ((0x00000003&(data))>>0)


#define SYS_DCSB_PLL_SSC                                                             0x180000FC
#define SYS_DCSB_PLL_SSC_reg_addr                                                    "0xB80000FC"
#define SYS_DCSB_PLL_SSC_reg                                                         0xB80000FC
#define set_SYS_DCSB_PLL_SSC_reg(data)   (*((volatile unsigned int*) SYS_DCSB_PLL_SSC_reg)=data)
#define get_SYS_DCSB_PLL_SSC_reg   (*((volatile unsigned int*) SYS_DCSB_PLL_SSC_reg))
#define SYS_DCSB_PLL_SSC_inst_adr                                                    "0x003F"
#define SYS_DCSB_PLL_SSC_inst                                                        0x003F
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sse_shift                                          (31)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sse_mask                                           (0x80000000)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sse(data)                                          (0x80000000&((data)<<31))
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sse_src(data)                                      ((0x80000000&(data))>>31)
#define SYS_DCSB_PLL_SSC_get_dcsb_ssc_sse(data)                                      ((0x80000000&(data))>>31)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ckinv_shift                                        (30)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ckinv_mask                                         (0x40000000)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ckinv(data)                                        (0x40000000&((data)<<30))
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ckinv_src(data)                                    ((0x40000000&(data))>>30)
#define SYS_DCSB_PLL_SSC_get_dcsb_ssc_ckinv(data)                                    ((0x40000000&(data))>>30)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sss_shift                                          (24)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sss_mask                                           (0x3F000000)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sss(data)                                          (0x3F000000&((data)<<24))
#define SYS_DCSB_PLL_SSC_dcsb_ssc_sss_src(data)                                      ((0x3F000000&(data))>>24)
#define SYS_DCSB_PLL_SSC_get_dcsb_ssc_sss(data)                                      ((0x3F000000&(data))>>24)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssn_shift                                          (16)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssn_mask                                           (0x007F0000)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssn(data)                                          (0x007F0000&((data)<<16))
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssn_src(data)                                      ((0x007F0000&(data))>>16)
#define SYS_DCSB_PLL_SSC_get_dcsb_ssc_ssn(data)                                      ((0x007F0000&(data))>>16)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssfpv_shift                                        (8)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssfpv_mask                                         (0x0000FF00)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssfpv(data)                                        (0x0000FF00&((data)<<8))
#define SYS_DCSB_PLL_SSC_dcsb_ssc_ssfpv_src(data)                                    ((0x0000FF00&(data))>>8)
#define SYS_DCSB_PLL_SSC_get_dcsb_ssc_ssfpv(data)                                    ((0x0000FF00&(data))>>8)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_stms_shift                                         (0)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_stms_mask                                          (0x00000003)
#define SYS_DCSB_PLL_SSC_dcsb_ssc_stms(data)                                         (0x00000003&((data)<<0))
#define SYS_DCSB_PLL_SSC_dcsb_ssc_stms_src(data)                                     ((0x00000003&(data))>>0)
#define SYS_DCSB_PLL_SSC_get_dcsb_ssc_stms(data)                                     ((0x00000003&(data))>>0)


#define SYS_PLL_SCPU1                                                                0x18000100
#define SYS_PLL_SCPU1_reg_addr                                                       "0xB8000100"
#define SYS_PLL_SCPU1_reg                                                            0xB8000100
#define set_SYS_PLL_SCPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_SCPU1_reg)=data)
#define get_SYS_PLL_SCPU1_reg   (*((volatile unsigned int*) SYS_PLL_SCPU1_reg))
#define SYS_PLL_SCPU1_inst_adr                                                       "0x0040"
#define SYS_PLL_SCPU1_inst                                                           0x0040
#define SYS_PLL_SCPU1_REG_PLLSCPU_N_shift                                            (20)
#define SYS_PLL_SCPU1_REG_PLLSCPU_N_mask                                             (0x00300000)
#define SYS_PLL_SCPU1_REG_PLLSCPU_N(data)                                            (0x00300000&((data)<<20))
#define SYS_PLL_SCPU1_REG_PLLSCPU_N_src(data)                                        ((0x00300000&(data))>>20)
#define SYS_PLL_SCPU1_get_REG_PLLSCPU_N(data)                                        ((0x00300000&(data))>>20)
#define SYS_PLL_SCPU1_REG_PLLSCPU_M_shift                                            (12)
#define SYS_PLL_SCPU1_REG_PLLSCPU_M_mask                                             (0x000FF000)
#define SYS_PLL_SCPU1_REG_PLLSCPU_M(data)                                            (0x000FF000&((data)<<12))
#define SYS_PLL_SCPU1_REG_PLLSCPU_M_src(data)                                        ((0x000FF000&(data))>>12)
#define SYS_PLL_SCPU1_get_REG_PLLSCPU_M(data)                                        ((0x000FF000&(data))>>12)
#define SYS_PLL_SCPU1_REG_PLLSCPU_IP_shift                                           (9)
#define SYS_PLL_SCPU1_REG_PLLSCPU_IP_mask                                            (0x00000E00)
#define SYS_PLL_SCPU1_REG_PLLSCPU_IP(data)                                           (0x00000E00&((data)<<9))
#define SYS_PLL_SCPU1_REG_PLLSCPU_IP_src(data)                                       ((0x00000E00&(data))>>9)
#define SYS_PLL_SCPU1_get_REG_PLLSCPU_IP(data)                                       ((0x00000E00&(data))>>9)
#define SYS_PLL_SCPU1_REG_PLLSCPU_O_shift                                            (7)
#define SYS_PLL_SCPU1_REG_PLLSCPU_O_mask                                             (0x00000180)
#define SYS_PLL_SCPU1_REG_PLLSCPU_O(data)                                            (0x00000180&((data)<<7))
#define SYS_PLL_SCPU1_REG_PLLSCPU_O_src(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_SCPU1_get_REG_PLLSCPU_O(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDRST_shift                                        (6)
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDRST_mask                                         (0x00000040)
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDRST(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDRST_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_SCPU1_get_REG_PLLSCPU_WDRST(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDSET_shift                                        (5)
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDSET_mask                                         (0x00000020)
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDSET(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_SCPU1_REG_PLLSCPU_WDSET_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_SCPU1_get_REG_PLLSCPU_WDSET(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_SCPU1_REG_PLLSCPU_TST_shift                                          (0)
#define SYS_PLL_SCPU1_REG_PLLSCPU_TST_mask                                           (0x00000001)
#define SYS_PLL_SCPU1_REG_PLLSCPU_TST(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_SCPU1_REG_PLLSCPU_TST_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_SCPU1_get_REG_PLLSCPU_TST(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_SCPU2                                                                0x18000104
#define SYS_PLL_SCPU2_reg_addr                                                       "0xB8000104"
#define SYS_PLL_SCPU2_reg                                                            0xB8000104
#define set_SYS_PLL_SCPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_SCPU2_reg)=data)
#define get_SYS_PLL_SCPU2_reg   (*((volatile unsigned int*) SYS_PLL_SCPU2_reg))
#define SYS_PLL_SCPU2_inst_adr                                                       "0x0041"
#define SYS_PLL_SCPU2_inst                                                           0x0041
#define SYS_PLL_SCPU2_REG_PLLSCPU_RS_shift                                           (8)
#define SYS_PLL_SCPU2_REG_PLLSCPU_RS_mask                                            (0x00000700)
#define SYS_PLL_SCPU2_REG_PLLSCPU_RS(data)                                           (0x00000700&((data)<<8))
#define SYS_PLL_SCPU2_REG_PLLSCPU_RS_src(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_SCPU2_get_REG_PLLSCPU_RS(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_SCPU2_REG_PLLSCPU_CS_shift                                           (4)
#define SYS_PLL_SCPU2_REG_PLLSCPU_CS_mask                                            (0x00000030)
#define SYS_PLL_SCPU2_REG_PLLSCPU_CS(data)                                           (0x00000030&((data)<<4))
#define SYS_PLL_SCPU2_REG_PLLSCPU_CS_src(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_SCPU2_get_REG_PLLSCPU_CS(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_SCPU2_REG_PLLSCPU_CP_shift                                           (3)
#define SYS_PLL_SCPU2_REG_PLLSCPU_CP_mask                                            (0x00000008)
#define SYS_PLL_SCPU2_REG_PLLSCPU_CP(data)                                           (0x00000008&((data)<<3))
#define SYS_PLL_SCPU2_REG_PLLSCPU_CP_src(data)                                       ((0x00000008&(data))>>3)
#define SYS_PLL_SCPU2_get_REG_PLLSCPU_CP(data)                                       ((0x00000008&(data))>>3)
#define SYS_PLL_SCPU2_REG_PLLSCPU_OEB_shift                                          (2)
#define SYS_PLL_SCPU2_REG_PLLSCPU_OEB_mask                                           (0x00000004)
#define SYS_PLL_SCPU2_REG_PLLSCPU_OEB(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_SCPU2_REG_PLLSCPU_OEB_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SCPU2_get_REG_PLLSCPU_OEB(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_SCPU2_PLLSCPU_RSTB_shift                                             (1)
#define SYS_PLL_SCPU2_PLLSCPU_RSTB_mask                                              (0x00000002)
#define SYS_PLL_SCPU2_PLLSCPU_RSTB(data)                                             (0x00000002&((data)<<1))
#define SYS_PLL_SCPU2_PLLSCPU_RSTB_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_SCPU2_get_PLLSCPU_RSTB(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_SCPU2_REG_PLLSCPU_POW_shift                                          (0)
#define SYS_PLL_SCPU2_REG_PLLSCPU_POW_mask                                           (0x00000001)
#define SYS_PLL_SCPU2_REG_PLLSCPU_POW(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_SCPU2_REG_PLLSCPU_POW_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_SCPU2_get_REG_PLLSCPU_POW(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_ACPU1                                                                0x18000108
#define SYS_PLL_ACPU1_reg_addr                                                       "0xB8000108"
#define SYS_PLL_ACPU1_reg                                                            0xB8000108
#define set_SYS_PLL_ACPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_ACPU1_reg)=data)
#define get_SYS_PLL_ACPU1_reg   (*((volatile unsigned int*) SYS_PLL_ACPU1_reg))
#define SYS_PLL_ACPU1_inst_adr                                                       "0x0042"
#define SYS_PLL_ACPU1_inst                                                           0x0042
#define SYS_PLL_ACPU1_REG_PLLACPU_N_shift                                            (19)
#define SYS_PLL_ACPU1_REG_PLLACPU_N_mask                                             (0x00180000)
#define SYS_PLL_ACPU1_REG_PLLACPU_N(data)                                            (0x00180000&((data)<<19))
#define SYS_PLL_ACPU1_REG_PLLACPU_N_src(data)                                        ((0x00180000&(data))>>19)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_N(data)                                        ((0x00180000&(data))>>19)
#define SYS_PLL_ACPU1_REG_PLLACPU_M_shift                                            (12)
#define SYS_PLL_ACPU1_REG_PLLACPU_M_mask                                             (0x0007F000)
#define SYS_PLL_ACPU1_REG_PLLACPU_M(data)                                            (0x0007F000&((data)<<12))
#define SYS_PLL_ACPU1_REG_PLLACPU_M_src(data)                                        ((0x0007F000&(data))>>12)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_M(data)                                        ((0x0007F000&(data))>>12)
#define SYS_PLL_ACPU1_REG_PLLACPU_IP_shift                                           (9)
#define SYS_PLL_ACPU1_REG_PLLACPU_IP_mask                                            (0x00000E00)
#define SYS_PLL_ACPU1_REG_PLLACPU_IP(data)                                           (0x00000E00&((data)<<9))
#define SYS_PLL_ACPU1_REG_PLLACPU_IP_src(data)                                       ((0x00000E00&(data))>>9)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_IP(data)                                       ((0x00000E00&(data))>>9)
#define SYS_PLL_ACPU1_REG_PLLACPU_O_shift                                            (7)
#define SYS_PLL_ACPU1_REG_PLLACPU_O_mask                                             (0x00000180)
#define SYS_PLL_ACPU1_REG_PLLACPU_O(data)                                            (0x00000180&((data)<<7))
#define SYS_PLL_ACPU1_REG_PLLACPU_O_src(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_O(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST_shift                                        (6)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST_mask                                         (0x00000040)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_ACPU1_REG_PLLACPU_WDRST_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_WDRST(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET_shift                                        (5)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET_mask                                         (0x00000020)
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_ACPU1_REG_PLLACPU_WDSET_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_WDSET(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_ACPU1_REG_PLLACPU_TST_shift                                          (0)
#define SYS_PLL_ACPU1_REG_PLLACPU_TST_mask                                           (0x00000001)
#define SYS_PLL_ACPU1_REG_PLLACPU_TST(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_ACPU1_REG_PLLACPU_TST_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_ACPU1_get_REG_PLLACPU_TST(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_ACPU2                                                                0x1800010C
#define SYS_PLL_ACPU2_reg_addr                                                       "0xB800010C"
#define SYS_PLL_ACPU2_reg                                                            0xB800010C
#define set_SYS_PLL_ACPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_ACPU2_reg)=data)
#define get_SYS_PLL_ACPU2_reg   (*((volatile unsigned int*) SYS_PLL_ACPU2_reg))
#define SYS_PLL_ACPU2_inst_adr                                                       "0x0043"
#define SYS_PLL_ACPU2_inst                                                           0x0043
#define SYS_PLL_ACPU2_REG_PLLACPU_RS_shift                                           (8)
#define SYS_PLL_ACPU2_REG_PLLACPU_RS_mask                                            (0x00000700)
#define SYS_PLL_ACPU2_REG_PLLACPU_RS(data)                                           (0x00000700&((data)<<8))
#define SYS_PLL_ACPU2_REG_PLLACPU_RS_src(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_ACPU2_get_REG_PLLACPU_RS(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_ACPU2_REG_PLLACPU_CS_shift                                           (4)
#define SYS_PLL_ACPU2_REG_PLLACPU_CS_mask                                            (0x00000030)
#define SYS_PLL_ACPU2_REG_PLLACPU_CS(data)                                           (0x00000030&((data)<<4))
#define SYS_PLL_ACPU2_REG_PLLACPU_CS_src(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_ACPU2_get_REG_PLLACPU_CS(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB_shift                                          (2)
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB_mask                                           (0x00000004)
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_ACPU2_REG_PLLACPU_OEB_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_ACPU2_get_REG_PLLACPU_OEB(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_ACPU2_PLLACPU_RSTB_shift                                             (1)
#define SYS_PLL_ACPU2_PLLACPU_RSTB_mask                                              (0x00000002)
#define SYS_PLL_ACPU2_PLLACPU_RSTB(data)                                             (0x00000002&((data)<<1))
#define SYS_PLL_ACPU2_PLLACPU_RSTB_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_ACPU2_get_PLLACPU_RSTB(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_ACPU2_REG_PLLACPU_POW_shift                                          (0)
#define SYS_PLL_ACPU2_REG_PLLACPU_POW_mask                                           (0x00000001)
#define SYS_PLL_ACPU2_REG_PLLACPU_POW(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_ACPU2_REG_PLLACPU_POW_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_ACPU2_get_REG_PLLACPU_POW(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_VCPU1                                                                0x18000110
#define SYS_PLL_VCPU1_reg_addr                                                       "0xB8000110"
#define SYS_PLL_VCPU1_reg                                                            0xB8000110
#define set_SYS_PLL_VCPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_VCPU1_reg)=data)
#define get_SYS_PLL_VCPU1_reg   (*((volatile unsigned int*) SYS_PLL_VCPU1_reg))
#define SYS_PLL_VCPU1_inst_adr                                                       "0x0044"
#define SYS_PLL_VCPU1_inst                                                           0x0044
#define SYS_PLL_VCPU1_REG_PLLVCPU_IP_shift                                           (20)
#define SYS_PLL_VCPU1_REG_PLLVCPU_IP_mask                                            (0x00700000)
#define SYS_PLL_VCPU1_REG_PLLVCPU_IP(data)                                           (0x00700000&((data)<<20))
#define SYS_PLL_VCPU1_REG_PLLVCPU_IP_src(data)                                       ((0x00700000&(data))>>20)
#define SYS_PLL_VCPU1_get_REG_PLLVCPU_IP(data)                                       ((0x00700000&(data))>>20)
#define SYS_PLL_VCPU1_REG_PLLVCPU_N_shift                                            (18)
#define SYS_PLL_VCPU1_REG_PLLVCPU_N_mask                                             (0x000C0000)
#define SYS_PLL_VCPU1_REG_PLLVCPU_N(data)                                            (0x000C0000&((data)<<18))
#define SYS_PLL_VCPU1_REG_PLLVCPU_N_src(data)                                        ((0x000C0000&(data))>>18)
#define SYS_PLL_VCPU1_get_REG_PLLVCPU_N(data)                                        ((0x000C0000&(data))>>18)
#define SYS_PLL_VCPU1_REG_PLLVCPU_M_shift                                            (11)
#define SYS_PLL_VCPU1_REG_PLLVCPU_M_mask                                             (0x0003F800)
#define SYS_PLL_VCPU1_REG_PLLVCPU_M(data)                                            (0x0003F800&((data)<<11))
#define SYS_PLL_VCPU1_REG_PLLVCPU_M_src(data)                                        ((0x0003F800&(data))>>11)
#define SYS_PLL_VCPU1_get_REG_PLLVCPU_M(data)                                        ((0x0003F800&(data))>>11)
#define SYS_PLL_VCPU1_REG_PLLVCPU_O_shift                                            (7)
#define SYS_PLL_VCPU1_REG_PLLVCPU_O_mask                                             (0x00000180)
#define SYS_PLL_VCPU1_REG_PLLVCPU_O(data)                                            (0x00000180&((data)<<7))
#define SYS_PLL_VCPU1_REG_PLLVCPU_O_src(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_VCPU1_get_REG_PLLVCPU_O(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDRST_shift                                        (6)
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDRST_mask                                         (0x00000040)
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDRST(data)                                        (0x00000040&((data)<<6))
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDRST_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_VCPU1_get_REG_PLLVCPU_WDRST(data)                                    ((0x00000040&(data))>>6)
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDSET_shift                                        (5)
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDSET_mask                                         (0x00000020)
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDSET(data)                                        (0x00000020&((data)<<5))
#define SYS_PLL_VCPU1_REG_PLLVCPU_WDSET_src(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_VCPU1_get_REG_PLLVCPU_WDSET(data)                                    ((0x00000020&(data))>>5)
#define SYS_PLL_VCPU1_REG_PLLVCPU_TST_shift                                          (0)
#define SYS_PLL_VCPU1_REG_PLLVCPU_TST_mask                                           (0x00000001)
#define SYS_PLL_VCPU1_REG_PLLVCPU_TST(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_VCPU1_REG_PLLVCPU_TST_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_VCPU1_get_REG_PLLVCPU_TST(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_VCPU2                                                                0x18000114
#define SYS_PLL_VCPU2_reg_addr                                                       "0xB8000114"
#define SYS_PLL_VCPU2_reg                                                            0xB8000114
#define set_SYS_PLL_VCPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_VCPU2_reg)=data)
#define get_SYS_PLL_VCPU2_reg   (*((volatile unsigned int*) SYS_PLL_VCPU2_reg))
#define SYS_PLL_VCPU2_inst_adr                                                       "0x0045"
#define SYS_PLL_VCPU2_inst                                                           0x0045
#define SYS_PLL_VCPU2_REG_PLLVCPU_RS_shift                                           (8)
#define SYS_PLL_VCPU2_REG_PLLVCPU_RS_mask                                            (0x00000700)
#define SYS_PLL_VCPU2_REG_PLLVCPU_RS(data)                                           (0x00000700&((data)<<8))
#define SYS_PLL_VCPU2_REG_PLLVCPU_RS_src(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_VCPU2_get_REG_PLLVCPU_RS(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_VCPU2_REG_PLLVCPU_CS_shift                                           (4)
#define SYS_PLL_VCPU2_REG_PLLVCPU_CS_mask                                            (0x00000030)
#define SYS_PLL_VCPU2_REG_PLLVCPU_CS(data)                                           (0x00000030&((data)<<4))
#define SYS_PLL_VCPU2_REG_PLLVCPU_CS_src(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_VCPU2_get_REG_PLLVCPU_CS(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_VCPU2_REG_PLLVCPU_OEB_shift                                          (2)
#define SYS_PLL_VCPU2_REG_PLLVCPU_OEB_mask                                           (0x00000004)
#define SYS_PLL_VCPU2_REG_PLLVCPU_OEB(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_VCPU2_REG_PLLVCPU_OEB_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_VCPU2_get_REG_PLLVCPU_OEB(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_VCPU2_PLLVCPU_RSTB_shift                                             (1)
#define SYS_PLL_VCPU2_PLLVCPU_RSTB_mask                                              (0x00000002)
#define SYS_PLL_VCPU2_PLLVCPU_RSTB(data)                                             (0x00000002&((data)<<1))
#define SYS_PLL_VCPU2_PLLVCPU_RSTB_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_VCPU2_get_PLLVCPU_RSTB(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_VCPU2_REG_PLLVCPU_POW_shift                                          (0)
#define SYS_PLL_VCPU2_REG_PLLVCPU_POW_mask                                           (0x00000001)
#define SYS_PLL_VCPU2_REG_PLLVCPU_POW(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_VCPU2_REG_PLLVCPU_POW_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_VCPU2_get_REG_PLLVCPU_POW(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_BUS1                                                                 0x18000130
#define SYS_PLL_BUS1_reg_addr                                                        "0xB8000130"
#define SYS_PLL_BUS1_reg                                                             0xB8000130
#define set_SYS_PLL_BUS1_reg(data)   (*((volatile unsigned int*) SYS_PLL_BUS1_reg)=data)
#define get_SYS_PLL_BUS1_reg   (*((volatile unsigned int*) SYS_PLL_BUS1_reg))
#define SYS_PLL_BUS1_inst_adr                                                        "0x004C"
#define SYS_PLL_BUS1_inst                                                            0x004C
#define SYS_PLL_BUS1_REG_PLLBUS_O_shift                                              (28)
#define SYS_PLL_BUS1_REG_PLLBUS_O_mask                                               (0x30000000)
#define SYS_PLL_BUS1_REG_PLLBUS_O(data)                                              (0x30000000&((data)<<28))
#define SYS_PLL_BUS1_REG_PLLBUS_O_src(data)                                          ((0x30000000&(data))>>28)
#define SYS_PLL_BUS1_get_REG_PLLBUS_O(data)                                          ((0x30000000&(data))>>28)
#define SYS_PLL_BUS1_REG_PLLBUS_N_shift                                              (25)
#define SYS_PLL_BUS1_REG_PLLBUS_N_mask                                               (0x06000000)
#define SYS_PLL_BUS1_REG_PLLBUS_N(data)                                              (0x06000000&((data)<<25))
#define SYS_PLL_BUS1_REG_PLLBUS_N_src(data)                                          ((0x06000000&(data))>>25)
#define SYS_PLL_BUS1_get_REG_PLLBUS_N(data)                                          ((0x06000000&(data))>>25)
#define SYS_PLL_BUS1_REG_PLLBUS_M_shift                                              (18)
#define SYS_PLL_BUS1_REG_PLLBUS_M_mask                                               (0x01FC0000)
#define SYS_PLL_BUS1_REG_PLLBUS_M(data)                                              (0x01FC0000&((data)<<18))
#define SYS_PLL_BUS1_REG_PLLBUS_M_src(data)                                          ((0x01FC0000&(data))>>18)
#define SYS_PLL_BUS1_get_REG_PLLBUS_M(data)                                          ((0x01FC0000&(data))>>18)
#define SYS_PLL_BUS1_REG_PLLBUS_IP_shift                                             (15)
#define SYS_PLL_BUS1_REG_PLLBUS_IP_mask                                              (0x00038000)
#define SYS_PLL_BUS1_REG_PLLBUS_IP(data)                                             (0x00038000&((data)<<15))
#define SYS_PLL_BUS1_REG_PLLBUS_IP_src(data)                                         ((0x00038000&(data))>>15)
#define SYS_PLL_BUS1_get_REG_PLLBUS_IP(data)                                         ((0x00038000&(data))>>15)
#define SYS_PLL_BUS1_REG_PLLBUS_RS_shift                                             (11)
#define SYS_PLL_BUS1_REG_PLLBUS_RS_mask                                              (0x00003800)
#define SYS_PLL_BUS1_REG_PLLBUS_RS(data)                                             (0x00003800&((data)<<11))
#define SYS_PLL_BUS1_REG_PLLBUS_RS_src(data)                                         ((0x00003800&(data))>>11)
#define SYS_PLL_BUS1_get_REG_PLLBUS_RS(data)                                         ((0x00003800&(data))>>11)
#define SYS_PLL_BUS1_REG_PLLBUS_CS_shift                                             (8)
#define SYS_PLL_BUS1_REG_PLLBUS_CS_mask                                              (0x00000300)
#define SYS_PLL_BUS1_REG_PLLBUS_CS(data)                                             (0x00000300&((data)<<8))
#define SYS_PLL_BUS1_REG_PLLBUS_CS_src(data)                                         ((0x00000300&(data))>>8)
#define SYS_PLL_BUS1_get_REG_PLLBUS_CS(data)                                         ((0x00000300&(data))>>8)
#define SYS_PLL_BUS1_REG_PLLBUS_CP_shift                                             (5)
#define SYS_PLL_BUS1_REG_PLLBUS_CP_mask                                              (0x00000060)
#define SYS_PLL_BUS1_REG_PLLBUS_CP(data)                                             (0x00000060&((data)<<5))
#define SYS_PLL_BUS1_REG_PLLBUS_CP_src(data)                                         ((0x00000060&(data))>>5)
#define SYS_PLL_BUS1_get_REG_PLLBUS_CP(data)                                         ((0x00000060&(data))>>5)
#define SYS_PLL_BUS1_REG_PLLBUS_R3_shift                                             (2)
#define SYS_PLL_BUS1_REG_PLLBUS_R3_mask                                              (0x0000001C)
#define SYS_PLL_BUS1_REG_PLLBUS_R3(data)                                             (0x0000001C&((data)<<2))
#define SYS_PLL_BUS1_REG_PLLBUS_R3_src(data)                                         ((0x0000001C&(data))>>2)
#define SYS_PLL_BUS1_get_REG_PLLBUS_R3(data)                                         ((0x0000001C&(data))>>2)
#define SYS_PLL_BUS1_REG_PLLBUS_C3_shift                                             (0)
#define SYS_PLL_BUS1_REG_PLLBUS_C3_mask                                              (0x00000003)
#define SYS_PLL_BUS1_REG_PLLBUS_C3(data)                                             (0x00000003&((data)<<0))
#define SYS_PLL_BUS1_REG_PLLBUS_C3_src(data)                                         ((0x00000003&(data))>>0)
#define SYS_PLL_BUS1_get_REG_PLLBUS_C3(data)                                         ((0x00000003&(data))>>0)


#define SYS_PLL_BUS2                                                                 0x18000134
#define SYS_PLL_BUS2_reg_addr                                                        "0xB8000134"
#define SYS_PLL_BUS2_reg                                                             0xB8000134
#define set_SYS_PLL_BUS2_reg(data)   (*((volatile unsigned int*) SYS_PLL_BUS2_reg)=data)
#define get_SYS_PLL_BUS2_reg   (*((volatile unsigned int*) SYS_PLL_BUS2_reg))
#define SYS_PLL_BUS2_inst_adr                                                        "0x004D"
#define SYS_PLL_BUS2_inst                                                            0x004D
#define SYS_PLL_BUS2_write_en5_shift                                                 (18)
#define SYS_PLL_BUS2_write_en5_mask                                                  (0x00040000)
#define SYS_PLL_BUS2_write_en5(data)                                                 (0x00040000&((data)<<18))
#define SYS_PLL_BUS2_write_en5_src(data)                                             ((0x00040000&(data))>>18)
#define SYS_PLL_BUS2_get_write_en5(data)                                             ((0x00040000&(data))>>18)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RL_shift                                          (16)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RL_mask                                           (0x00030000)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RL(data)                                          (0x00030000&((data)<<16))
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RL_src(data)                                      ((0x00030000&(data))>>16)
#define SYS_PLL_BUS2_get_REG_PLLBUS_PI_RL(data)                                      ((0x00030000&(data))>>16)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RS_shift                                          (14)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RS_mask                                           (0x0000C000)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RS(data)                                          (0x0000C000&((data)<<14))
#define SYS_PLL_BUS2_REG_PLLBUS_PI_RS_src(data)                                      ((0x0000C000&(data))>>14)
#define SYS_PLL_BUS2_get_REG_PLLBUS_PI_RS(data)                                      ((0x0000C000&(data))>>14)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_BIAS_shift                                        (12)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_BIAS_mask                                         (0x00003000)
#define SYS_PLL_BUS2_REG_PLLBUS_PI_BIAS(data)                                        (0x00003000&((data)<<12))
#define SYS_PLL_BUS2_REG_PLLBUS_PI_BIAS_src(data)                                    ((0x00003000&(data))>>12)
#define SYS_PLL_BUS2_get_REG_PLLBUS_PI_BIAS(data)                                    ((0x00003000&(data))>>12)
#define SYS_PLL_BUS2_write_en4_shift                                                 (11)
#define SYS_PLL_BUS2_write_en4_mask                                                  (0x00000800)
#define SYS_PLL_BUS2_write_en4(data)                                                 (0x00000800&((data)<<11))
#define SYS_PLL_BUS2_write_en4_src(data)                                             ((0x00000800&(data))>>11)
#define SYS_PLL_BUS2_get_write_en4(data)                                             ((0x00000800&(data))>>11)
#define SYS_PLL_BUS2_REG_PLLBUS_WDMODE_shift                                         (9)
#define SYS_PLL_BUS2_REG_PLLBUS_WDMODE_mask                                          (0x00000600)
#define SYS_PLL_BUS2_REG_PLLBUS_WDMODE(data)                                         (0x00000600&((data)<<9))
#define SYS_PLL_BUS2_REG_PLLBUS_WDMODE_src(data)                                     ((0x00000600&(data))>>9)
#define SYS_PLL_BUS2_get_REG_PLLBUS_WDMODE(data)                                     ((0x00000600&(data))>>9)
#define SYS_PLL_BUS2_write_en3_shift                                                 (6)
#define SYS_PLL_BUS2_write_en3_mask                                                  (0x00000040)
#define SYS_PLL_BUS2_write_en3(data)                                                 (0x00000040&((data)<<6))
#define SYS_PLL_BUS2_write_en3_src(data)                                             ((0x00000040&(data))>>6)
#define SYS_PLL_BUS2_get_write_en3(data)                                             ((0x00000040&(data))>>6)
#define SYS_PLL_BUS2_REG_PLLBUS_FUPDN_shift                                          (5)
#define SYS_PLL_BUS2_REG_PLLBUS_FUPDN_mask                                           (0x00000020)
#define SYS_PLL_BUS2_REG_PLLBUS_FUPDN(data)                                          (0x00000020&((data)<<5))
#define SYS_PLL_BUS2_REG_PLLBUS_FUPDN_src(data)                                      ((0x00000020&(data))>>5)
#define SYS_PLL_BUS2_get_REG_PLLBUS_FUPDN(data)                                      ((0x00000020&(data))>>5)
#define SYS_PLL_BUS2_REG_PLLBUS_PSEN_shift                                           (4)
#define SYS_PLL_BUS2_REG_PLLBUS_PSEN_mask                                            (0x00000010)
#define SYS_PLL_BUS2_REG_PLLBUS_PSEN(data)                                           (0x00000010&((data)<<4))
#define SYS_PLL_BUS2_REG_PLLBUS_PSEN_src(data)                                       ((0x00000010&(data))>>4)
#define SYS_PLL_BUS2_get_REG_PLLBUS_PSEN(data)                                       ((0x00000010&(data))>>4)
#define SYS_PLL_BUS2_REG_PLLBUS_VCORB_shift                                          (3)
#define SYS_PLL_BUS2_REG_PLLBUS_VCORB_mask                                           (0x00000008)
#define SYS_PLL_BUS2_REG_PLLBUS_VCORB(data)                                          (0x00000008&((data)<<3))
#define SYS_PLL_BUS2_REG_PLLBUS_VCORB_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_PLL_BUS2_get_REG_PLLBUS_VCORB(data)                                      ((0x00000008&(data))>>3)
#define SYS_PLL_BUS2_write_en1_shift                                                 (2)
#define SYS_PLL_BUS2_write_en1_mask                                                  (0x00000004)
#define SYS_PLL_BUS2_write_en1(data)                                                 (0x00000004&((data)<<2))
#define SYS_PLL_BUS2_write_en1_src(data)                                             ((0x00000004&(data))>>2)
#define SYS_PLL_BUS2_get_write_en1(data)                                             ((0x00000004&(data))>>2)
#define SYS_PLL_BUS2_REG_PLLBUS_TST_shift                                            (1)
#define SYS_PLL_BUS2_REG_PLLBUS_TST_mask                                             (0x00000002)
#define SYS_PLL_BUS2_REG_PLLBUS_TST(data)                                            (0x00000002&((data)<<1))
#define SYS_PLL_BUS2_REG_PLLBUS_TST_src(data)                                        ((0x00000002&(data))>>1)
#define SYS_PLL_BUS2_get_REG_PLLBUS_TST(data)                                        ((0x00000002&(data))>>1)
#define SYS_PLL_BUS2_REG_PLLBUS_PSTST_shift                                          (0)
#define SYS_PLL_BUS2_REG_PLLBUS_PSTST_mask                                           (0x00000001)
#define SYS_PLL_BUS2_REG_PLLBUS_PSTST(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_BUS2_REG_PLLBUS_PSTST_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_BUS2_get_REG_PLLBUS_PSTST(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_BUS3                                                                 0x18000138
#define SYS_PLL_BUS3_reg_addr                                                        "0xB8000138"
#define SYS_PLL_BUS3_reg                                                             0xB8000138
#define set_SYS_PLL_BUS3_reg(data)   (*((volatile unsigned int*) SYS_PLL_BUS3_reg)=data)
#define get_SYS_PLL_BUS3_reg   (*((volatile unsigned int*) SYS_PLL_BUS3_reg))
#define SYS_PLL_BUS3_inst_adr                                                        "0x004E"
#define SYS_PLL_BUS3_inst                                                            0x004E
#define SYS_PLL_BUS3_REG_PLLBUS_OEB_shift                                            (2)
#define SYS_PLL_BUS3_REG_PLLBUS_OEB_mask                                             (0x00000004)
#define SYS_PLL_BUS3_REG_PLLBUS_OEB(data)                                            (0x00000004&((data)<<2))
#define SYS_PLL_BUS3_REG_PLLBUS_OEB_src(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_BUS3_get_REG_PLLBUS_OEB(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_BUS3_REG_PLLBUS_RSTB_shift                                           (1)
#define SYS_PLL_BUS3_REG_PLLBUS_RSTB_mask                                            (0x00000002)
#define SYS_PLL_BUS3_REG_PLLBUS_RSTB(data)                                           (0x00000002&((data)<<1))
#define SYS_PLL_BUS3_REG_PLLBUS_RSTB_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_BUS3_get_REG_PLLBUS_RSTB(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_BUS3_REG_PLLBUS_POW_shift                                            (0)
#define SYS_PLL_BUS3_REG_PLLBUS_POW_mask                                             (0x00000001)
#define SYS_PLL_BUS3_REG_PLLBUS_POW(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_BUS3_REG_PLLBUS_POW_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_BUS3_get_REG_PLLBUS_POW(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_DCSB1                                                                0x18000140
#define SYS_PLL_DCSB1_reg_addr                                                       "0xB8000140"
#define SYS_PLL_DCSB1_reg                                                            0xB8000140
#define set_SYS_PLL_DCSB1_reg(data)   (*((volatile unsigned int*) SYS_PLL_DCSB1_reg)=data)
#define get_SYS_PLL_DCSB1_reg   (*((volatile unsigned int*) SYS_PLL_DCSB1_reg))
#define SYS_PLL_DCSB1_inst_adr                                                       "0x0050"
#define SYS_PLL_DCSB1_inst                                                           0x0050
#define SYS_PLL_DCSB1_REG_PLLBUS_O_H_shift                                           (28)
#define SYS_PLL_DCSB1_REG_PLLBUS_O_H_mask                                            (0x30000000)
#define SYS_PLL_DCSB1_REG_PLLBUS_O_H(data)                                           (0x30000000&((data)<<28))
#define SYS_PLL_DCSB1_REG_PLLBUS_O_H_src(data)                                       ((0x30000000&(data))>>28)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_O_H(data)                                       ((0x30000000&(data))>>28)
#define SYS_PLL_DCSB1_REG_PLLBUS_N_H_shift                                           (25)
#define SYS_PLL_DCSB1_REG_PLLBUS_N_H_mask                                            (0x06000000)
#define SYS_PLL_DCSB1_REG_PLLBUS_N_H(data)                                           (0x06000000&((data)<<25))
#define SYS_PLL_DCSB1_REG_PLLBUS_N_H_src(data)                                       ((0x06000000&(data))>>25)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_N_H(data)                                       ((0x06000000&(data))>>25)
#define SYS_PLL_DCSB1_REG_PLLBUS_M_H_shift                                           (18)
#define SYS_PLL_DCSB1_REG_PLLBUS_M_H_mask                                            (0x01FC0000)
#define SYS_PLL_DCSB1_REG_PLLBUS_M_H(data)                                           (0x01FC0000&((data)<<18))
#define SYS_PLL_DCSB1_REG_PLLBUS_M_H_src(data)                                       ((0x01FC0000&(data))>>18)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_M_H(data)                                       ((0x01FC0000&(data))>>18)
#define SYS_PLL_DCSB1_REG_PLLBUS_IP_H_shift                                          (15)
#define SYS_PLL_DCSB1_REG_PLLBUS_IP_H_mask                                           (0x00038000)
#define SYS_PLL_DCSB1_REG_PLLBUS_IP_H(data)                                          (0x00038000&((data)<<15))
#define SYS_PLL_DCSB1_REG_PLLBUS_IP_H_src(data)                                      ((0x00038000&(data))>>15)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_IP_H(data)                                      ((0x00038000&(data))>>15)
#define SYS_PLL_DCSB1_REG_PLLBUS_RS_H_shift                                          (11)
#define SYS_PLL_DCSB1_REG_PLLBUS_RS_H_mask                                           (0x00003800)
#define SYS_PLL_DCSB1_REG_PLLBUS_RS_H(data)                                          (0x00003800&((data)<<11))
#define SYS_PLL_DCSB1_REG_PLLBUS_RS_H_src(data)                                      ((0x00003800&(data))>>11)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_RS_H(data)                                      ((0x00003800&(data))>>11)
#define SYS_PLL_DCSB1_REG_PLLBUS_CS_H_shift                                          (8)
#define SYS_PLL_DCSB1_REG_PLLBUS_CS_H_mask                                           (0x00000300)
#define SYS_PLL_DCSB1_REG_PLLBUS_CS_H(data)                                          (0x00000300&((data)<<8))
#define SYS_PLL_DCSB1_REG_PLLBUS_CS_H_src(data)                                      ((0x00000300&(data))>>8)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_CS_H(data)                                      ((0x00000300&(data))>>8)
#define SYS_PLL_DCSB1_REG_PLLBUS_CP_H_shift                                          (5)
#define SYS_PLL_DCSB1_REG_PLLBUS_CP_H_mask                                           (0x00000060)
#define SYS_PLL_DCSB1_REG_PLLBUS_CP_H(data)                                          (0x00000060&((data)<<5))
#define SYS_PLL_DCSB1_REG_PLLBUS_CP_H_src(data)                                      ((0x00000060&(data))>>5)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_CP_H(data)                                      ((0x00000060&(data))>>5)
#define SYS_PLL_DCSB1_REG_PLLBUS_R3_H_shift                                          (2)
#define SYS_PLL_DCSB1_REG_PLLBUS_R3_H_mask                                           (0x0000001C)
#define SYS_PLL_DCSB1_REG_PLLBUS_R3_H(data)                                          (0x0000001C&((data)<<2))
#define SYS_PLL_DCSB1_REG_PLLBUS_R3_H_src(data)                                      ((0x0000001C&(data))>>2)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_R3_H(data)                                      ((0x0000001C&(data))>>2)
#define SYS_PLL_DCSB1_REG_PLLBUS_C3_H_shift                                          (0)
#define SYS_PLL_DCSB1_REG_PLLBUS_C3_H_mask                                           (0x00000003)
#define SYS_PLL_DCSB1_REG_PLLBUS_C3_H(data)                                          (0x00000003&((data)<<0))
#define SYS_PLL_DCSB1_REG_PLLBUS_C3_H_src(data)                                      ((0x00000003&(data))>>0)
#define SYS_PLL_DCSB1_get_REG_PLLBUS_C3_H(data)                                      ((0x00000003&(data))>>0)


#define SYS_PLL_DCSB2                                                                0x18000144
#define SYS_PLL_DCSB2_reg_addr                                                       "0xB8000144"
#define SYS_PLL_DCSB2_reg                                                            0xB8000144
#define set_SYS_PLL_DCSB2_reg(data)   (*((volatile unsigned int*) SYS_PLL_DCSB2_reg)=data)
#define get_SYS_PLL_DCSB2_reg   (*((volatile unsigned int*) SYS_PLL_DCSB2_reg))
#define SYS_PLL_DCSB2_inst_adr                                                       "0x0051"
#define SYS_PLL_DCSB2_inst                                                           0x0051
#define SYS_PLL_DCSB2_write_en5_shift                                                (18)
#define SYS_PLL_DCSB2_write_en5_mask                                                 (0x00040000)
#define SYS_PLL_DCSB2_write_en5(data)                                                (0x00040000&((data)<<18))
#define SYS_PLL_DCSB2_write_en5_src(data)                                            ((0x00040000&(data))>>18)
#define SYS_PLL_DCSB2_get_write_en5(data)                                            ((0x00040000&(data))>>18)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RL_H_shift                                       (16)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RL_H_mask                                        (0x00030000)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RL_H(data)                                       (0x00030000&((data)<<16))
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RL_H_src(data)                                   ((0x00030000&(data))>>16)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_PI_RL_H(data)                                   ((0x00030000&(data))>>16)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RS_H_shift                                       (14)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RS_H_mask                                        (0x0000C000)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RS_H(data)                                       (0x0000C000&((data)<<14))
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_RS_H_src(data)                                   ((0x0000C000&(data))>>14)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_PI_RS_H(data)                                   ((0x0000C000&(data))>>14)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_BIAS_H_shift                                     (12)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_BIAS_H_mask                                      (0x00003000)
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_BIAS_H(data)                                     (0x00003000&((data)<<12))
#define SYS_PLL_DCSB2_REG_PLLBUS_PI_BIAS_H_src(data)                                 ((0x00003000&(data))>>12)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_PI_BIAS_H(data)                                 ((0x00003000&(data))>>12)
#define SYS_PLL_DCSB2_write_en4_shift                                                (11)
#define SYS_PLL_DCSB2_write_en4_mask                                                 (0x00000800)
#define SYS_PLL_DCSB2_write_en4(data)                                                (0x00000800&((data)<<11))
#define SYS_PLL_DCSB2_write_en4_src(data)                                            ((0x00000800&(data))>>11)
#define SYS_PLL_DCSB2_get_write_en4(data)                                            ((0x00000800&(data))>>11)
#define SYS_PLL_DCSB2_REG_PLLBUS_WDMODE_H_shift                                      (9)
#define SYS_PLL_DCSB2_REG_PLLBUS_WDMODE_H_mask                                       (0x00000600)
#define SYS_PLL_DCSB2_REG_PLLBUS_WDMODE_H(data)                                      (0x00000600&((data)<<9))
#define SYS_PLL_DCSB2_REG_PLLBUS_WDMODE_H_src(data)                                  ((0x00000600&(data))>>9)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_WDMODE_H(data)                                  ((0x00000600&(data))>>9)
#define SYS_PLL_DCSB2_write_en3_shift                                                (6)
#define SYS_PLL_DCSB2_write_en3_mask                                                 (0x00000040)
#define SYS_PLL_DCSB2_write_en3(data)                                                (0x00000040&((data)<<6))
#define SYS_PLL_DCSB2_write_en3_src(data)                                            ((0x00000040&(data))>>6)
#define SYS_PLL_DCSB2_get_write_en3(data)                                            ((0x00000040&(data))>>6)
#define SYS_PLL_DCSB2_REG_PLLBUS_FUPDN_H_shift                                       (5)
#define SYS_PLL_DCSB2_REG_PLLBUS_FUPDN_H_mask                                        (0x00000020)
#define SYS_PLL_DCSB2_REG_PLLBUS_FUPDN_H(data)                                       (0x00000020&((data)<<5))
#define SYS_PLL_DCSB2_REG_PLLBUS_FUPDN_H_src(data)                                   ((0x00000020&(data))>>5)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_FUPDN_H(data)                                   ((0x00000020&(data))>>5)
#define SYS_PLL_DCSB2_REG_PLLBUS_PSEN_H_shift                                        (4)
#define SYS_PLL_DCSB2_REG_PLLBUS_PSEN_H_mask                                         (0x00000010)
#define SYS_PLL_DCSB2_REG_PLLBUS_PSEN_H(data)                                        (0x00000010&((data)<<4))
#define SYS_PLL_DCSB2_REG_PLLBUS_PSEN_H_src(data)                                    ((0x00000010&(data))>>4)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_PSEN_H(data)                                    ((0x00000010&(data))>>4)
#define SYS_PLL_DCSB2_REG_PLLBUS_VCORB_H_shift                                       (3)
#define SYS_PLL_DCSB2_REG_PLLBUS_VCORB_H_mask                                        (0x00000008)
#define SYS_PLL_DCSB2_REG_PLLBUS_VCORB_H(data)                                       (0x00000008&((data)<<3))
#define SYS_PLL_DCSB2_REG_PLLBUS_VCORB_H_src(data)                                   ((0x00000008&(data))>>3)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_VCORB_H(data)                                   ((0x00000008&(data))>>3)
#define SYS_PLL_DCSB2_write_en1_shift                                                (2)
#define SYS_PLL_DCSB2_write_en1_mask                                                 (0x00000004)
#define SYS_PLL_DCSB2_write_en1(data)                                                (0x00000004&((data)<<2))
#define SYS_PLL_DCSB2_write_en1_src(data)                                            ((0x00000004&(data))>>2)
#define SYS_PLL_DCSB2_get_write_en1(data)                                            ((0x00000004&(data))>>2)
#define SYS_PLL_DCSB2_REG_PLLBUS_TST_H_shift                                         (1)
#define SYS_PLL_DCSB2_REG_PLLBUS_TST_H_mask                                          (0x00000002)
#define SYS_PLL_DCSB2_REG_PLLBUS_TST_H(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_DCSB2_REG_PLLBUS_TST_H_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_TST_H(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_DCSB2_REG_PLLBUS_PSTST_H_shift                                       (0)
#define SYS_PLL_DCSB2_REG_PLLBUS_PSTST_H_mask                                        (0x00000001)
#define SYS_PLL_DCSB2_REG_PLLBUS_PSTST_H(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_DCSB2_REG_PLLBUS_PSTST_H_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_DCSB2_get_REG_PLLBUS_PSTST_H(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_DCSB3                                                                0x18000148
#define SYS_PLL_DCSB3_reg_addr                                                       "0xB8000148"
#define SYS_PLL_DCSB3_reg                                                            0xB8000148
#define set_SYS_PLL_DCSB3_reg(data)   (*((volatile unsigned int*) SYS_PLL_DCSB3_reg)=data)
#define get_SYS_PLL_DCSB3_reg   (*((volatile unsigned int*) SYS_PLL_DCSB3_reg))
#define SYS_PLL_DCSB3_inst_adr                                                       "0x0052"
#define SYS_PLL_DCSB3_inst                                                           0x0052
#define SYS_PLL_DCSB3_REG_PLLBUS_OEB_H_shift                                         (2)
#define SYS_PLL_DCSB3_REG_PLLBUS_OEB_H_mask                                          (0x00000004)
#define SYS_PLL_DCSB3_REG_PLLBUS_OEB_H(data)                                         (0x00000004&((data)<<2))
#define SYS_PLL_DCSB3_REG_PLLBUS_OEB_H_src(data)                                     ((0x00000004&(data))>>2)
#define SYS_PLL_DCSB3_get_REG_PLLBUS_OEB_H(data)                                     ((0x00000004&(data))>>2)
#define SYS_PLL_DCSB3_REG_PLLBUS_RSTB_H_shift                                        (1)
#define SYS_PLL_DCSB3_REG_PLLBUS_RSTB_H_mask                                         (0x00000002)
#define SYS_PLL_DCSB3_REG_PLLBUS_RSTB_H(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_DCSB3_REG_PLLBUS_RSTB_H_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_DCSB3_get_REG_PLLBUS_RSTB_H(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_DCSB3_REG_PLLBUS_POW_H_shift                                         (0)
#define SYS_PLL_DCSB3_REG_PLLBUS_POW_H_mask                                          (0x00000001)
#define SYS_PLL_DCSB3_REG_PLLBUS_POW_H(data)                                         (0x00000001&((data)<<0))
#define SYS_PLL_DCSB3_REG_PLLBUS_POW_H_src(data)                                     ((0x00000001&(data))>>0)
#define SYS_PLL_DCSB3_get_REG_PLLBUS_POW_H(data)                                     ((0x00000001&(data))>>0)


#define SYS_PLL_VODMA1                                                               0x18000160
#define SYS_PLL_VODMA1_reg_addr                                                      "0xB8000160"
#define SYS_PLL_VODMA1_reg                                                           0xB8000160
#define set_SYS_PLL_VODMA1_reg(data)   (*((volatile unsigned int*) SYS_PLL_VODMA1_reg)=data)
#define get_SYS_PLL_VODMA1_reg   (*((volatile unsigned int*) SYS_PLL_VODMA1_reg))
#define SYS_PLL_VODMA1_inst_adr                                                      "0x0058"
#define SYS_PLL_VODMA1_inst                                                          0x0058
#define SYS_PLL_VODMA1_REG_PLLVODMA_N_shift                                          (20)
#define SYS_PLL_VODMA1_REG_PLLVODMA_N_mask                                           (0x00300000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_N(data)                                          (0x00300000&((data)<<20))
#define SYS_PLL_VODMA1_REG_PLLVODMA_N_src(data)                                      ((0x00300000&(data))>>20)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_N(data)                                      ((0x00300000&(data))>>20)
#define SYS_PLL_VODMA1_REG_PLLVODMA_M_shift                                          (12)
#define SYS_PLL_VODMA1_REG_PLLVODMA_M_mask                                           (0x0007F000)
#define SYS_PLL_VODMA1_REG_PLLVODMA_M(data)                                          (0x0007F000&((data)<<12))
#define SYS_PLL_VODMA1_REG_PLLVODMA_M_src(data)                                      ((0x0007F000&(data))>>12)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_M(data)                                      ((0x0007F000&(data))>>12)
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP_shift                                         (9)
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP_mask                                          (0x00000E00)
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP(data)                                         (0x00000E00&((data)<<9))
#define SYS_PLL_VODMA1_REG_PLLVODMA_IP_src(data)                                     ((0x00000E00&(data))>>9)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_IP(data)                                     ((0x00000E00&(data))>>9)
#define SYS_PLL_VODMA1_REG_PLLVODMA_O_shift                                          (7)
#define SYS_PLL_VODMA1_REG_PLLVODMA_O_mask                                           (0x00000180)
#define SYS_PLL_VODMA1_REG_PLLVODMA_O(data)                                          (0x00000180&((data)<<7))
#define SYS_PLL_VODMA1_REG_PLLVODMA_O_src(data)                                      ((0x00000180&(data))>>7)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_O(data)                                      ((0x00000180&(data))>>7)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET_shift                                      (6)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET_mask                                       (0x00000040)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET(data)                                      (0x00000040&((data)<<6))
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDSET_src(data)                                  ((0x00000040&(data))>>6)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_WDSET(data)                                  ((0x00000040&(data))>>6)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST_shift                                      (5)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST_mask                                       (0x00000020)
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST(data)                                      (0x00000020&((data)<<5))
#define SYS_PLL_VODMA1_REG_PLLVODMA_WDRST_src(data)                                  ((0x00000020&(data))>>5)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_WDRST(data)                                  ((0x00000020&(data))>>5)
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS_shift                                         (3)
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS_mask                                          (0x00000018)
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS(data)                                         (0x00000018&((data)<<3))
#define SYS_PLL_VODMA1_REG_PLLVODMA_CS_src(data)                                     ((0x00000018&(data))>>3)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_CS(data)                                     ((0x00000018&(data))>>3)
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS_shift                                         (0)
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS_mask                                          (0x00000007)
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS(data)                                         (0x00000007&((data)<<0))
#define SYS_PLL_VODMA1_REG_PLLVODMA_RS_src(data)                                     ((0x00000007&(data))>>0)
#define SYS_PLL_VODMA1_get_REG_PLLVODMA_RS(data)                                     ((0x00000007&(data))>>0)


#define SYS_PLL_VODMA2                                                               0x18000164
#define SYS_PLL_VODMA2_reg_addr                                                      "0xB8000164"
#define SYS_PLL_VODMA2_reg                                                           0xB8000164
#define set_SYS_PLL_VODMA2_reg(data)   (*((volatile unsigned int*) SYS_PLL_VODMA2_reg)=data)
#define get_SYS_PLL_VODMA2_reg   (*((volatile unsigned int*) SYS_PLL_VODMA2_reg))
#define SYS_PLL_VODMA2_inst_adr                                                      "0x0059"
#define SYS_PLL_VODMA2_inst                                                          0x0059
#define SYS_PLL_VODMA2_REG_PLLVODMA_TST_shift                                        (3)
#define SYS_PLL_VODMA2_REG_PLLVODMA_TST_mask                                         (0x00000008)
#define SYS_PLL_VODMA2_REG_PLLVODMA_TST(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_VODMA2_REG_PLLVODMA_TST_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_VODMA2_get_REG_PLLVODMA_TST(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB_shift                                        (2)
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB_mask                                         (0x00000004)
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_VODMA2_REG_PLLVODMA_OEB_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_VODMA2_get_REG_PLLVODMA_OEB(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB_shift                                       (1)
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB_mask                                        (0x00000002)
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB(data)                                       (0x00000002&((data)<<1))
#define SYS_PLL_VODMA2_REG_PLLVODMA_RSTB_src(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_VODMA2_get_REG_PLLVODMA_RSTB(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW_shift                                        (0)
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW_mask                                         (0x00000001)
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_VODMA2_REG_PLLVODMA_POW_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_VODMA2_get_REG_PLLVODMA_POW(data)                                    ((0x00000001&(data))>>0)


#define SYS_PLLBUS_TST                                                               0x18000168
#define SYS_PLLBUS_TST_reg_addr                                                      "0xB8000168"
#define SYS_PLLBUS_TST_reg                                                           0xB8000168
#define set_SYS_PLLBUS_TST_reg(data)   (*((volatile unsigned int*) SYS_PLLBUS_TST_reg)=data)
#define get_SYS_PLLBUS_TST_reg   (*((volatile unsigned int*) SYS_PLLBUS_TST_reg))
#define SYS_PLLBUS_TST_inst_adr                                                      "0x005A"
#define SYS_PLLBUS_TST_inst                                                          0x005A
#define SYS_PLLBUS_TST_REG_PLLCPU_REG_shift                                          (20)
#define SYS_PLLBUS_TST_REG_PLLCPU_REG_mask                                           (0x00300000)
#define SYS_PLLBUS_TST_REG_PLLCPU_REG(data)                                          (0x00300000&((data)<<20))
#define SYS_PLLBUS_TST_REG_PLLCPU_REG_src(data)                                      ((0x00300000&(data))>>20)
#define SYS_PLLBUS_TST_get_REG_PLLCPU_REG(data)                                      ((0x00300000&(data))>>20)
#define SYS_PLLBUS_TST_REG_PLLBUS_RESER_shift                                        (16)
#define SYS_PLLBUS_TST_REG_PLLBUS_RESER_mask                                         (0x000F0000)
#define SYS_PLLBUS_TST_REG_PLLBUS_RESER(data)                                        (0x000F0000&((data)<<16))
#define SYS_PLLBUS_TST_REG_PLLBUS_RESER_src(data)                                    ((0x000F0000&(data))>>16)
#define SYS_PLLBUS_TST_get_REG_PLLBUS_RESER(data)                                    ((0x000F0000&(data))>>16)
#define SYS_PLLBUS_TST_REG_PLLBUS_REG_shift                                          (12)
#define SYS_PLLBUS_TST_REG_PLLBUS_REG_mask                                           (0x00003000)
#define SYS_PLLBUS_TST_REG_PLLBUS_REG(data)                                          (0x00003000&((data)<<12))
#define SYS_PLLBUS_TST_REG_PLLBUS_REG_src(data)                                      ((0x00003000&(data))>>12)
#define SYS_PLLBUS_TST_get_REG_PLLBUS_REG(data)                                      ((0x00003000&(data))>>12)
#define SYS_PLLBUS_TST_REG_PLLTST_DIV_shift                                          (8)
#define SYS_PLLBUS_TST_REG_PLLTST_DIV_mask                                           (0x00000300)
#define SYS_PLLBUS_TST_REG_PLLTST_DIV(data)                                          (0x00000300&((data)<<8))
#define SYS_PLLBUS_TST_REG_PLLTST_DIV_src(data)                                      ((0x00000300&(data))>>8)
#define SYS_PLLBUS_TST_get_REG_PLLTST_DIV(data)                                      ((0x00000300&(data))>>8)
#define SYS_PLLBUS_TST_REG_PLLTST_SEL_shift                                          (0)
#define SYS_PLLBUS_TST_REG_PLLTST_SEL_mask                                           (0x0000001F)
#define SYS_PLLBUS_TST_REG_PLLTST_SEL(data)                                          (0x0000001F&((data)<<0))
#define SYS_PLLBUS_TST_REG_PLLTST_SEL_src(data)                                      ((0x0000001F&(data))>>0)
#define SYS_PLLBUS_TST_get_REG_PLLTST_SEL(data)                                      ((0x0000001F&(data))>>0)


#define SYS_PLL_DISP_SD1                                                             0x18000170
#define SYS_PLL_DISP_SD1_reg_addr                                                    "0xB8000170"
#define SYS_PLL_DISP_SD1_reg                                                         0xB8000170
#define set_SYS_PLL_DISP_SD1_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_SD1_reg)=data)
#define get_SYS_PLL_DISP_SD1_reg   (*((volatile unsigned int*) SYS_PLL_DISP_SD1_reg))
#define SYS_PLL_DISP_SD1_inst_adr                                                    "0x005C"
#define SYS_PLL_DISP_SD1_inst                                                        0x005C
#define SYS_PLL_DISP_SD1_REG_PLLDDS_N_shift                                          (30)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_N_mask                                           (0xC0000000)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_N(data)                                          (0xC0000000&((data)<<30))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_N_src(data)                                      ((0xC0000000&(data))>>30)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_N(data)                                      ((0xC0000000&(data))>>30)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_M_shift                                          (23)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_M_mask                                           (0x3F800000)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_M(data)                                          (0x3F800000&((data)<<23))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_M_src(data)                                      ((0x3F800000&(data))>>23)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_M(data)                                      ((0x3F800000&(data))>>23)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_IP_shift                                         (20)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_IP_mask                                          (0x00700000)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_IP(data)                                         (0x00700000&((data)<<20))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_IP_src(data)                                     ((0x00700000&(data))>>20)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_IP(data)                                     ((0x00700000&(data))>>20)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_RS_shift                                         (17)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_RS_mask                                          (0x000E0000)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_RS(data)                                         (0x000E0000&((data)<<17))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_RS_src(data)                                     ((0x000E0000&(data))>>17)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_RS(data)                                     ((0x000E0000&(data))>>17)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CS_shift                                         (15)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CS_mask                                          (0x00018000)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CS(data)                                         (0x00018000&((data)<<15))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CS_src(data)                                     ((0x00018000&(data))>>15)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_CS(data)                                     ((0x00018000&(data))>>15)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CP_shift                                         (13)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CP_mask                                          (0x00006000)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CP(data)                                         (0x00006000&((data)<<13))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_CP_src(data)                                     ((0x00006000&(data))>>13)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_CP(data)                                     ((0x00006000&(data))>>13)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_R3_shift                                         (10)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_R3_mask                                          (0x00001C00)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_R3(data)                                         (0x00001C00&((data)<<10))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_R3_src(data)                                     ((0x00001C00&(data))>>10)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_R3(data)                                     ((0x00001C00&(data))>>10)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_C3_shift                                         (8)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_C3_mask                                          (0x00000300)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_C3(data)                                         (0x00000300&((data)<<8))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_C3_src(data)                                     ((0x00000300&(data))>>8)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_C3(data)                                     ((0x00000300&(data))>>8)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RL_shift                                      (6)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RL_mask                                       (0x000000C0)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RL(data)                                      (0x000000C0&((data)<<6))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RL_src(data)                                  ((0x000000C0&(data))>>6)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_PI_RL(data)                                  ((0x000000C0&(data))>>6)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RS_shift                                      (4)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RS_mask                                       (0x00000030)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RS(data)                                      (0x00000030&((data)<<4))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_RS_src(data)                                  ((0x00000030&(data))>>4)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_PI_RS(data)                                  ((0x00000030&(data))>>4)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_BIAS_shift                                    (2)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_BIAS_mask                                     (0x0000000C)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_BIAS(data)                                    (0x0000000C&((data)<<2))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_PI_BIAS_src(data)                                ((0x0000000C&(data))>>2)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_PI_BIAS(data)                                ((0x0000000C&(data))>>2)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_WDMODE_shift                                     (0)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_WDMODE_mask                                      (0x00000003)
#define SYS_PLL_DISP_SD1_REG_PLLDDS_WDMODE(data)                                     (0x00000003&((data)<<0))
#define SYS_PLL_DISP_SD1_REG_PLLDDS_WDMODE_src(data)                                 ((0x00000003&(data))>>0)
#define SYS_PLL_DISP_SD1_get_REG_PLLDDS_WDMODE(data)                                 ((0x00000003&(data))>>0)


#define SYS_PLL_DISP_SD2                                                             0x18000174
#define SYS_PLL_DISP_SD2_reg_addr                                                    "0xB8000174"
#define SYS_PLL_DISP_SD2_reg                                                         0xB8000174
#define set_SYS_PLL_DISP_SD2_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_SD2_reg)=data)
#define get_SYS_PLL_DISP_SD2_reg   (*((volatile unsigned int*) SYS_PLL_DISP_SD2_reg))
#define SYS_PLL_DISP_SD2_inst_adr                                                    "0x005D"
#define SYS_PLL_DISP_SD2_inst                                                        0x005D
#define SYS_PLL_DISP_SD2_REG_PLLDDS_O_shift                                          (30)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_O_mask                                           (0xC0000000)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_O(data)                                          (0xC0000000&((data)<<30))
#define SYS_PLL_DISP_SD2_REG_PLLDDS_O_src(data)                                      ((0xC0000000&(data))>>30)
#define SYS_PLL_DISP_SD2_get_REG_PLLDDS_O(data)                                      ((0xC0000000&(data))>>30)
#define SYS_PLL_DISP_SD2_psaud_1a_phase_sel_shift                                    (27)
#define SYS_PLL_DISP_SD2_psaud_1a_phase_sel_mask                                     (0x08000000)
#define SYS_PLL_DISP_SD2_psaud_1a_phase_sel(data)                                    (0x08000000&((data)<<27))
#define SYS_PLL_DISP_SD2_psaud_1a_phase_sel_src(data)                                ((0x08000000&(data))>>27)
#define SYS_PLL_DISP_SD2_get_psaud_1a_phase_sel(data)                                ((0x08000000&(data))>>27)
#define SYS_PLL_DISP_SD2_psaud_2a_phase_sel_shift                                    (26)
#define SYS_PLL_DISP_SD2_psaud_2a_phase_sel_mask                                     (0x04000000)
#define SYS_PLL_DISP_SD2_psaud_2a_phase_sel(data)                                    (0x04000000&((data)<<26))
#define SYS_PLL_DISP_SD2_psaud_2a_phase_sel_src(data)                                ((0x04000000&(data))>>26)
#define SYS_PLL_DISP_SD2_get_psaud_2a_phase_sel(data)                                ((0x04000000&(data))>>26)
#define SYS_PLL_DISP_SD2_pcr_a_smooth_en_shift                                       (24)
#define SYS_PLL_DISP_SD2_pcr_a_smooth_en_mask                                        (0x01000000)
#define SYS_PLL_DISP_SD2_pcr_a_smooth_en(data)                                       (0x01000000&((data)<<24))
#define SYS_PLL_DISP_SD2_pcr_a_smooth_en_src(data)                                   ((0x01000000&(data))>>24)
#define SYS_PLL_DISP_SD2_get_pcr_a_smooth_en(data)                                   ((0x01000000&(data))>>24)
#define SYS_PLL_DISP_SD2_pcr_a_phase_sel_shift                                       (22)
#define SYS_PLL_DISP_SD2_pcr_a_phase_sel_mask                                        (0x00400000)
#define SYS_PLL_DISP_SD2_pcr_a_phase_sel(data)                                       (0x00400000&((data)<<22))
#define SYS_PLL_DISP_SD2_pcr_a_phase_sel_src(data)                                   ((0x00400000&(data))>>22)
#define SYS_PLL_DISP_SD2_get_pcr_a_phase_sel(data)                                   ((0x00400000&(data))>>22)
#define SYS_PLL_DISP_SD2_pcr_a_ctl_en_shift                                          (20)
#define SYS_PLL_DISP_SD2_pcr_a_ctl_en_mask                                           (0x00100000)
#define SYS_PLL_DISP_SD2_pcr_a_ctl_en(data)                                          (0x00100000&((data)<<20))
#define SYS_PLL_DISP_SD2_pcr_a_ctl_en_src(data)                                      ((0x00100000&(data))>>20)
#define SYS_PLL_DISP_SD2_get_pcr_a_ctl_en(data)                                      ((0x00100000&(data))>>20)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_FUPDN_shift                                      (18)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_FUPDN_mask                                       (0x00040000)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_FUPDN(data)                                      (0x00040000&((data)<<18))
#define SYS_PLL_DISP_SD2_REG_PLLDDS_FUPDN_src(data)                                  ((0x00040000&(data))>>18)
#define SYS_PLL_DISP_SD2_get_REG_PLLDDS_FUPDN(data)                                  ((0x00040000&(data))>>18)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_DDSEN_shift                                      (16)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_DDSEN_mask                                       (0x00010000)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_DDSEN(data)                                      (0x00010000&((data)<<16))
#define SYS_PLL_DISP_SD2_REG_PLLDDS_DDSEN_src(data)                                  ((0x00010000&(data))>>16)
#define SYS_PLL_DISP_SD2_get_REG_PLLDDS_DDSEN(data)                                  ((0x00010000&(data))>>16)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_VCORB_shift                                      (14)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_VCORB_mask                                       (0x00004000)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_VCORB(data)                                      (0x00004000&((data)<<14))
#define SYS_PLL_DISP_SD2_REG_PLLDDS_VCORB_src(data)                                  ((0x00004000&(data))>>14)
#define SYS_PLL_DISP_SD2_get_REG_PLLDDS_VCORB(data)                                  ((0x00004000&(data))>>14)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_TST_shift                                        (12)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_TST_mask                                         (0x00001000)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_TST(data)                                        (0x00001000&((data)<<12))
#define SYS_PLL_DISP_SD2_REG_PLLDDS_TST_src(data)                                    ((0x00001000&(data))>>12)
#define SYS_PLL_DISP_SD2_get_REG_PLLDDS_TST(data)                                    ((0x00001000&(data))>>12)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_PSTST_shift                                      (11)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_PSTST_mask                                       (0x00000800)
#define SYS_PLL_DISP_SD2_REG_PLLDDS_PSTST(data)                                      (0x00000800&((data)<<11))
#define SYS_PLL_DISP_SD2_REG_PLLDDS_PSTST_src(data)                                  ((0x00000800&(data))>>11)
#define SYS_PLL_DISP_SD2_get_REG_PLLDDS_PSTST(data)                                  ((0x00000800&(data))>>11)


#define SYS_PLL_DISP_SD3                                                             0x18000178
#define SYS_PLL_DISP_SD3_reg_addr                                                    "0xB8000178"
#define SYS_PLL_DISP_SD3_reg                                                         0xB8000178
#define set_SYS_PLL_DISP_SD3_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_SD3_reg)=data)
#define get_SYS_PLL_DISP_SD3_reg   (*((volatile unsigned int*) SYS_PLL_DISP_SD3_reg))
#define SYS_PLL_DISP_SD3_inst_adr                                                    "0x005E"
#define SYS_PLL_DISP_SD3_inst                                                        0x005E
#define SYS_PLL_DISP_SD3_REG_PSAUD1_FUPDN_shift                                      (29)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_FUPDN_mask                                       (0x20000000)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_FUPDN(data)                                      (0x20000000&((data)<<29))
#define SYS_PLL_DISP_SD3_REG_PSAUD1_FUPDN_src(data)                                  ((0x20000000&(data))>>29)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD1_FUPDN(data)                                  ((0x20000000&(data))>>29)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_DIV_shift                                        (28)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_DIV_mask                                         (0x10000000)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_DIV(data)                                        (0x10000000&((data)<<28))
#define SYS_PLL_DISP_SD3_REG_PSAUD1_DIV_src(data)                                    ((0x10000000&(data))>>28)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD1_DIV(data)                                    ((0x10000000&(data))>>28)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_TST_shift                                        (26)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_TST_mask                                         (0x04000000)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_TST(data)                                        (0x04000000&((data)<<26))
#define SYS_PLL_DISP_SD3_REG_PSAUD1_TST_src(data)                                    ((0x04000000&(data))>>26)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD1_TST(data)                                    ((0x04000000&(data))>>26)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_PSEN_shift                                       (25)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_PSEN_mask                                        (0x02000000)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_PSEN(data)                                       (0x02000000&((data)<<25))
#define SYS_PLL_DISP_SD3_REG_PSAUD1_PSEN_src(data)                                   ((0x02000000&(data))>>25)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD1_PSEN(data)                                   ((0x02000000&(data))>>25)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_FUPDN_shift                                      (23)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_FUPDN_mask                                       (0x00800000)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_FUPDN(data)                                      (0x00800000&((data)<<23))
#define SYS_PLL_DISP_SD3_REG_PSAUD2_FUPDN_src(data)                                  ((0x00800000&(data))>>23)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD2_FUPDN(data)                                  ((0x00800000&(data))>>23)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_DIV_shift                                        (22)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_DIV_mask                                         (0x00400000)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_DIV(data)                                        (0x00400000&((data)<<22))
#define SYS_PLL_DISP_SD3_REG_PSAUD2_DIV_src(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD2_DIV(data)                                    ((0x00400000&(data))>>22)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_TST_shift                                        (21)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_TST_mask                                         (0x00200000)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_TST(data)                                        (0x00200000&((data)<<21))
#define SYS_PLL_DISP_SD3_REG_PSAUD2_TST_src(data)                                    ((0x00200000&(data))>>21)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD2_TST(data)                                    ((0x00200000&(data))>>21)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_PSEN_shift                                       (20)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_PSEN_mask                                        (0x00100000)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_PSEN(data)                                       (0x00100000&((data)<<20))
#define SYS_PLL_DISP_SD3_REG_PSAUD2_PSEN_src(data)                                   ((0x00100000&(data))>>20)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD2_PSEN(data)                                   ((0x00100000&(data))>>20)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_OEB_shift                                        (3)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_OEB_mask                                         (0x00000008)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_OEB(data)                                        (0x00000008&((data)<<3))
#define SYS_PLL_DISP_SD3_REG_PSAUD1_OEB_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD1_OEB(data)                                    ((0x00000008&(data))>>3)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_RSTB_shift                                       (2)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_RSTB_mask                                        (0x00000004)
#define SYS_PLL_DISP_SD3_REG_PSAUD1_RSTB(data)                                       (0x00000004&((data)<<2))
#define SYS_PLL_DISP_SD3_REG_PSAUD1_RSTB_src(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD1_RSTB(data)                                   ((0x00000004&(data))>>2)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_OEB_shift                                        (1)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_OEB_mask                                         (0x00000002)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_OEB(data)                                        (0x00000002&((data)<<1))
#define SYS_PLL_DISP_SD3_REG_PSAUD2_OEB_src(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD2_OEB(data)                                    ((0x00000002&(data))>>1)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_RSTB_shift                                       (0)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_RSTB_mask                                        (0x00000001)
#define SYS_PLL_DISP_SD3_REG_PSAUD2_RSTB(data)                                       (0x00000001&((data)<<0))
#define SYS_PLL_DISP_SD3_REG_PSAUD2_RSTB_src(data)                                   ((0x00000001&(data))>>0)
#define SYS_PLL_DISP_SD3_get_REG_PSAUD2_RSTB(data)                                   ((0x00000001&(data))>>0)


#define SYS_PLL_DISP_SD4                                                             0x1800017C
#define SYS_PLL_DISP_SD4_reg_addr                                                    "0xB800017C"
#define SYS_PLL_DISP_SD4_reg                                                         0xB800017C
#define set_SYS_PLL_DISP_SD4_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_SD4_reg)=data)
#define get_SYS_PLL_DISP_SD4_reg   (*((volatile unsigned int*) SYS_PLL_DISP_SD4_reg))
#define SYS_PLL_DISP_SD4_inst_adr                                                    "0x005F"
#define SYS_PLL_DISP_SD4_inst                                                        0x005F
#define SYS_PLL_DISP_SD4_REG_PLLDDS_O_shift                                          (4)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_O_mask                                           (0x00000030)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_O(data)                                          (0x00000030&((data)<<4))
#define SYS_PLL_DISP_SD4_REG_PLLDDS_O_src(data)                                      ((0x00000030&(data))>>4)
#define SYS_PLL_DISP_SD4_get_REG_PLLDDS_O(data)                                      ((0x00000030&(data))>>4)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_OEB_shift                                        (2)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_OEB_mask                                         (0x00000004)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_OEB(data)                                        (0x00000004&((data)<<2))
#define SYS_PLL_DISP_SD4_REG_PLLDDS_OEB_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_DISP_SD4_get_REG_PLLDDS_OEB(data)                                    ((0x00000004&(data))>>2)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_RSTB_shift                                       (1)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_RSTB_mask                                        (0x00000002)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_RSTB(data)                                       (0x00000002&((data)<<1))
#define SYS_PLL_DISP_SD4_REG_PLLDDS_RSTB_src(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_DISP_SD4_get_REG_PLLDDS_RSTB(data)                                   ((0x00000002&(data))>>1)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_POW_shift                                        (0)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_POW_mask                                         (0x00000001)
#define SYS_PLL_DISP_SD4_REG_PLLDDS_POW(data)                                        (0x00000001&((data)<<0))
#define SYS_PLL_DISP_SD4_REG_PLLDDS_POW_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_PLL_DISP_SD4_get_REG_PLLDDS_POW(data)                                    ((0x00000001&(data))>>0)


#define SYS_PLL_DISP_SD5                                                             0x18000180
#define SYS_PLL_DISP_SD5_reg_addr                                                    "0xB8000180"
#define SYS_PLL_DISP_SD5_reg                                                         0xB8000180
#define set_SYS_PLL_DISP_SD5_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_SD5_reg)=data)
#define get_SYS_PLL_DISP_SD5_reg   (*((volatile unsigned int*) SYS_PLL_DISP_SD5_reg))
#define SYS_PLL_DISP_SD5_inst_adr                                                    "0x0060"
#define SYS_PLL_DISP_SD5_inst                                                        0x0060
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_ACC_shift                                        (16)
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_ACC_mask                                         (0xFFFF0000)
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_ACC(data)                                        (0xFFFF0000&((data)<<16))
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_ACC_src(data)                                    ((0xFFFF0000&(data))>>16)
#define SYS_PLL_DISP_SD5_get_PLLDDS_PCR_ACC(data)                                    ((0xFFFF0000&(data))>>16)
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_OVERFLOW_shift                                   (0)
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_OVERFLOW_mask                                    (0x0000FFFF)
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_OVERFLOW(data)                                   (0x0000FFFF&((data)<<0))
#define SYS_PLL_DISP_SD5_PLLDDS_PCR_OVERFLOW_src(data)                               ((0x0000FFFF&(data))>>0)
#define SYS_PLL_DISP_SD5_get_PLLDDS_PCR_OVERFLOW(data)                               ((0x0000FFFF&(data))>>0)


#define SYS_PLL_DISP_SD6                                                             0x18000184
#define SYS_PLL_DISP_SD6_reg_addr                                                    "0xB8000184"
#define SYS_PLL_DISP_SD6_reg                                                         0xB8000184
#define set_SYS_PLL_DISP_SD6_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_SD6_reg)=data)
#define get_SYS_PLL_DISP_SD6_reg   (*((volatile unsigned int*) SYS_PLL_DISP_SD6_reg))
#define SYS_PLL_DISP_SD6_inst_adr                                                    "0x0061"
#define SYS_PLL_DISP_SD6_inst                                                        0x0061
#define SYS_PLL_DISP_SD6_n_PCR_A_N_nxt_shift                                         (16)
#define SYS_PLL_DISP_SD6_n_PCR_A_N_nxt_mask                                          (0xFFFF0000)
#define SYS_PLL_DISP_SD6_n_PCR_A_N_nxt(data)                                         (0xFFFF0000&((data)<<16))
#define SYS_PLL_DISP_SD6_n_PCR_A_N_nxt_src(data)                                     ((0xFFFF0000&(data))>>16)
#define SYS_PLL_DISP_SD6_get_n_PCR_A_N_nxt(data)                                     ((0xFFFF0000&(data))>>16)
#define SYS_PLL_DISP_SD6_PCR_A_N_nxt_shift                                           (0)
#define SYS_PLL_DISP_SD6_PCR_A_N_nxt_mask                                            (0x0000FFFF)
#define SYS_PLL_DISP_SD6_PCR_A_N_nxt(data)                                           (0x0000FFFF&((data)<<0))
#define SYS_PLL_DISP_SD6_PCR_A_N_nxt_src(data)                                       ((0x0000FFFF&(data))>>0)
#define SYS_PLL_DISP_SD6_get_PCR_A_N_nxt(data)                                       ((0x0000FFFF&(data))>>0)


#define SYS_PLL_DISP_SD7                                                             0x18000188
#define SYS_PLL_DISP_SD7_reg_addr                                                    "0xB8000188"
#define SYS_PLL_DISP_SD7_reg                                                         0xB8000188
#define set_SYS_PLL_DISP_SD7_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP_SD7_reg)=data)
#define get_SYS_PLL_DISP_SD7_reg   (*((volatile unsigned int*) SYS_PLL_DISP_SD7_reg))
#define SYS_PLL_DISP_SD7_inst_adr                                                    "0x0062"
#define SYS_PLL_DISP_SD7_inst                                                        0x0062
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add_shift                                       (16)
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add_mask                                        (0x00FF0000)
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add(data)                                       (0x00FF0000&((data)<<16))
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add_src(data)                                   ((0x00FF0000&(data))>>16)
#define SYS_PLL_DISP_SD7_get_PCR_A_N_nxt_add(data)                                   ((0x00FF0000&(data))>>16)
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add_period_shift                                (0)
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add_period_mask                                 (0x0000FFFF)
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add_period(data)                                (0x0000FFFF&((data)<<0))
#define SYS_PLL_DISP_SD7_PCR_A_N_nxt_add_period_src(data)                            ((0x0000FFFF&(data))>>0)
#define SYS_PLL_DISP_SD7_get_PCR_A_N_nxt_add_period(data)                            ((0x0000FFFF&(data))>>0)


#define SYS_PLL_DISP1                                                                0x18000190
#define SYS_PLL_DISP1_reg_addr                                                       "0xB8000190"
#define SYS_PLL_DISP1_reg                                                            0xB8000190
#define set_SYS_PLL_DISP1_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP1_reg)=data)
#define get_SYS_PLL_DISP1_reg   (*((volatile unsigned int*) SYS_PLL_DISP1_reg))
#define SYS_PLL_DISP1_inst_adr                                                       "0x0064"
#define SYS_PLL_DISP1_inst                                                           0x0064
#define SYS_PLL_DISP1_DPLL_M_shift                                                   (20)
#define SYS_PLL_DISP1_DPLL_M_mask                                                    (0x0FF00000)
#define SYS_PLL_DISP1_DPLL_M(data)                                                   (0x0FF00000&((data)<<20))
#define SYS_PLL_DISP1_DPLL_M_src(data)                                               ((0x0FF00000&(data))>>20)
#define SYS_PLL_DISP1_get_DPLL_M(data)                                               ((0x0FF00000&(data))>>20)
#define SYS_PLL_DISP1_DPLL_N_shift                                                   (12)
#define SYS_PLL_DISP1_DPLL_N_mask                                                    (0x00007000)
#define SYS_PLL_DISP1_DPLL_N(data)                                                   (0x00007000&((data)<<12))
#define SYS_PLL_DISP1_DPLL_N_src(data)                                               ((0x00007000&(data))>>12)
#define SYS_PLL_DISP1_get_DPLL_N(data)                                               ((0x00007000&(data))>>12)
#define SYS_PLL_DISP1_DPLL_IP_shift                                                  (8)
#define SYS_PLL_DISP1_DPLL_IP_mask                                                   (0x00000700)
#define SYS_PLL_DISP1_DPLL_IP(data)                                                  (0x00000700&((data)<<8))
#define SYS_PLL_DISP1_DPLL_IP_src(data)                                              ((0x00000700&(data))>>8)
#define SYS_PLL_DISP1_get_DPLL_IP(data)                                              ((0x00000700&(data))>>8)
#define SYS_PLL_DISP1_DPLL_RS_shift                                                  (4)
#define SYS_PLL_DISP1_DPLL_RS_mask                                                   (0x00000070)
#define SYS_PLL_DISP1_DPLL_RS(data)                                                  (0x00000070&((data)<<4))
#define SYS_PLL_DISP1_DPLL_RS_src(data)                                              ((0x00000070&(data))>>4)
#define SYS_PLL_DISP1_get_DPLL_RS(data)                                              ((0x00000070&(data))>>4)
#define SYS_PLL_DISP1_DPLL_CP_shift                                                  (2)
#define SYS_PLL_DISP1_DPLL_CP_mask                                                   (0x0000000C)
#define SYS_PLL_DISP1_DPLL_CP(data)                                                  (0x0000000C&((data)<<2))
#define SYS_PLL_DISP1_DPLL_CP_src(data)                                              ((0x0000000C&(data))>>2)
#define SYS_PLL_DISP1_get_DPLL_CP(data)                                              ((0x0000000C&(data))>>2)
#define SYS_PLL_DISP1_DPLL_CS_shift                                                  (0)
#define SYS_PLL_DISP1_DPLL_CS_mask                                                   (0x00000003)
#define SYS_PLL_DISP1_DPLL_CS(data)                                                  (0x00000003&((data)<<0))
#define SYS_PLL_DISP1_DPLL_CS_src(data)                                              ((0x00000003&(data))>>0)
#define SYS_PLL_DISP1_get_DPLL_CS(data)                                              ((0x00000003&(data))>>0)


#define SYS_PLL_DISP2                                                                0x18000194
#define SYS_PLL_DISP2_reg_addr                                                       "0xB8000194"
#define SYS_PLL_DISP2_reg                                                            0xB8000194
#define set_SYS_PLL_DISP2_reg(data)   (*((volatile unsigned int*) SYS_PLL_DISP2_reg)=data)
#define get_SYS_PLL_DISP2_reg   (*((volatile unsigned int*) SYS_PLL_DISP2_reg))
#define SYS_PLL_DISP2_inst_adr                                                       "0x0065"
#define SYS_PLL_DISP2_inst                                                           0x0065
#define SYS_PLL_DISP2_DPLL_LDOSEL_shift                                              (28)
#define SYS_PLL_DISP2_DPLL_LDOSEL_mask                                               (0x30000000)
#define SYS_PLL_DISP2_DPLL_LDOSEL(data)                                              (0x30000000&((data)<<28))
#define SYS_PLL_DISP2_DPLL_LDOSEL_src(data)                                          ((0x30000000&(data))>>28)
#define SYS_PLL_DISP2_get_DPLL_LDOSEL(data)                                          ((0x30000000&(data))>>28)
#define SYS_PLL_DISP2_DPLL_RESER_shift                                               (24)
#define SYS_PLL_DISP2_DPLL_RESER_mask                                                (0x01000000)
#define SYS_PLL_DISP2_DPLL_RESER(data)                                               (0x01000000&((data)<<24))
#define SYS_PLL_DISP2_DPLL_RESER_src(data)                                           ((0x01000000&(data))>>24)
#define SYS_PLL_DISP2_get_DPLL_RESER(data)                                           ((0x01000000&(data))>>24)
#define SYS_PLL_DISP2_DPLL_FUPDN_shift                                               (21)
#define SYS_PLL_DISP2_DPLL_FUPDN_mask                                                (0x00200000)
#define SYS_PLL_DISP2_DPLL_FUPDN(data)                                               (0x00200000&((data)<<21))
#define SYS_PLL_DISP2_DPLL_FUPDN_src(data)                                           ((0x00200000&(data))>>21)
#define SYS_PLL_DISP2_get_DPLL_FUPDN(data)                                           ((0x00200000&(data))>>21)
#define SYS_PLL_DISP2_DPLL_STOP_shift                                                (20)
#define SYS_PLL_DISP2_DPLL_STOP_mask                                                 (0x00100000)
#define SYS_PLL_DISP2_DPLL_STOP(data)                                                (0x00100000&((data)<<20))
#define SYS_PLL_DISP2_DPLL_STOP_src(data)                                            ((0x00100000&(data))>>20)
#define SYS_PLL_DISP2_get_DPLL_STOP(data)                                            ((0x00100000&(data))>>20)
#define SYS_PLL_DISP2_DPLL_RESERVE_shift                                             (17)
#define SYS_PLL_DISP2_DPLL_RESERVE_mask                                              (0x00020000)
#define SYS_PLL_DISP2_DPLL_RESERVE(data)                                             (0x00020000&((data)<<17))
#define SYS_PLL_DISP2_DPLL_RESERVE_src(data)                                         ((0x00020000&(data))>>17)
#define SYS_PLL_DISP2_get_DPLL_RESERVE(data)                                         ((0x00020000&(data))>>17)
#define SYS_PLL_DISP2_DPLL_BPPHS_shift                                               (16)
#define SYS_PLL_DISP2_DPLL_BPPHS_mask                                                (0x00010000)
#define SYS_PLL_DISP2_DPLL_BPPHS(data)                                               (0x00010000&((data)<<16))
#define SYS_PLL_DISP2_DPLL_BPPHS_src(data)                                           ((0x00010000&(data))>>16)
#define SYS_PLL_DISP2_get_DPLL_BPPHS(data)                                           ((0x00010000&(data))>>16)
#define SYS_PLL_DISP2_DPLL_BPN_shift                                                 (14)
#define SYS_PLL_DISP2_DPLL_BPN_mask                                                  (0x00004000)
#define SYS_PLL_DISP2_DPLL_BPN(data)                                                 (0x00004000&((data)<<14))
#define SYS_PLL_DISP2_DPLL_BPN_src(data)                                             ((0x00004000&(data))>>14)
#define SYS_PLL_DISP2_get_DPLL_BPN(data)                                             ((0x00004000&(data))>>14)
#define SYS_PLL_DISP2_DPLL_O_shift                                                   (12)
#define SYS_PLL_DISP2_DPLL_O_mask                                                    (0x00003000)
#define SYS_PLL_DISP2_DPLL_O(data)                                                   (0x00003000&((data)<<12))
#define SYS_PLL_DISP2_DPLL_O_src(data)                                               ((0x00003000&(data))>>12)
#define SYS_PLL_DISP2_get_DPLL_O(data)                                               ((0x00003000&(data))>>12)
#define SYS_PLL_DISP2_DPLL_RSTB_shift                                                (6)
#define SYS_PLL_DISP2_DPLL_RSTB_mask                                                 (0x00000040)
#define SYS_PLL_DISP2_DPLL_RSTB(data)                                                (0x00000040&((data)<<6))
#define SYS_PLL_DISP2_DPLL_RSTB_src(data)                                            ((0x00000040&(data))>>6)
#define SYS_PLL_DISP2_get_DPLL_RSTB(data)                                            ((0x00000040&(data))>>6)
#define SYS_PLL_DISP2_DPLL_WDRST_shift                                               (5)
#define SYS_PLL_DISP2_DPLL_WDRST_mask                                                (0x00000020)
#define SYS_PLL_DISP2_DPLL_WDRST(data)                                               (0x00000020&((data)<<5))
#define SYS_PLL_DISP2_DPLL_WDRST_src(data)                                           ((0x00000020&(data))>>5)
#define SYS_PLL_DISP2_get_DPLL_WDRST(data)                                           ((0x00000020&(data))>>5)
#define SYS_PLL_DISP2_DPLL_WDSET_shift                                               (4)
#define SYS_PLL_DISP2_DPLL_WDSET_mask                                                (0x00000010)
#define SYS_PLL_DISP2_DPLL_WDSET(data)                                               (0x00000010&((data)<<4))
#define SYS_PLL_DISP2_DPLL_WDSET_src(data)                                           ((0x00000010&(data))>>4)
#define SYS_PLL_DISP2_get_DPLL_WDSET(data)                                           ((0x00000010&(data))>>4)
#define SYS_PLL_DISP2_DPLL_CLKSEL_shift                                              (3)
#define SYS_PLL_DISP2_DPLL_CLKSEL_mask                                               (0x00000008)
#define SYS_PLL_DISP2_DPLL_CLKSEL(data)                                              (0x00000008&((data)<<3))
#define SYS_PLL_DISP2_DPLL_CLKSEL_src(data)                                          ((0x00000008&(data))>>3)
#define SYS_PLL_DISP2_get_DPLL_CLKSEL(data)                                          ((0x00000008&(data))>>3)
#define SYS_PLL_DISP2_DPLL_FREEZE_shift                                              (2)
#define SYS_PLL_DISP2_DPLL_FREEZE_mask                                               (0x00000004)
#define SYS_PLL_DISP2_DPLL_FREEZE(data)                                              (0x00000004&((data)<<2))
#define SYS_PLL_DISP2_DPLL_FREEZE_src(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_DISP2_get_DPLL_FREEZE(data)                                          ((0x00000004&(data))>>2)
#define SYS_PLL_DISP2_DPLL_VCORSTB_shift                                             (1)
#define SYS_PLL_DISP2_DPLL_VCORSTB_mask                                              (0x00000002)
#define SYS_PLL_DISP2_DPLL_VCORSTB(data)                                             (0x00000002&((data)<<1))
#define SYS_PLL_DISP2_DPLL_VCORSTB_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_DISP2_get_DPLL_VCORSTB(data)                                         ((0x00000002&(data))>>1)
#define SYS_PLL_DISP2_DPLL_POW_shift                                                 (0)
#define SYS_PLL_DISP2_DPLL_POW_mask                                                  (0x00000001)
#define SYS_PLL_DISP2_DPLL_POW(data)                                                 (0x00000001&((data)<<0))
#define SYS_PLL_DISP2_DPLL_POW_src(data)                                             ((0x00000001&(data))>>0)
#define SYS_PLL_DISP2_get_DPLL_POW(data)                                             ((0x00000001&(data))>>0)


#define SYS_PLL_VBY1_MAC1                                                            0x18000198
#define SYS_PLL_VBY1_MAC1_reg_addr                                                   "0xB8000198"
#define SYS_PLL_VBY1_MAC1_reg                                                        0xB8000198
#define set_SYS_PLL_VBY1_MAC1_reg(data)   (*((volatile unsigned int*) SYS_PLL_VBY1_MAC1_reg)=data)
#define get_SYS_PLL_VBY1_MAC1_reg   (*((volatile unsigned int*) SYS_PLL_VBY1_MAC1_reg))
#define SYS_PLL_VBY1_MAC1_inst_adr                                                   "0x0066"
#define SYS_PLL_VBY1_MAC1_inst                                                       0x0066
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVM_shift                                  (4)
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVM_mask                                   (0x00000070)
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVM(data)                                  (0x00000070&((data)<<4))
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVM_src(data)                              ((0x00000070&(data))>>4)
#define SYS_PLL_VBY1_MAC1_get_PLT_CMU_MACPLL_DIVM(data)                              ((0x00000070&(data))>>4)
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVN_shift                                  (0)
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVN_mask                                   (0x00000007)
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVN(data)                                  (0x00000007&((data)<<0))
#define SYS_PLL_VBY1_MAC1_PLT_CMU_MACPLL_DIVN_src(data)                              ((0x00000007&(data))>>0)
#define SYS_PLL_VBY1_MAC1_get_PLT_CMU_MACPLL_DIVN(data)                              ((0x00000007&(data))>>0)


#define SYS_TMDS_SCR1                                                                0x180001C0
#define SYS_TMDS_SCR1_reg_addr                                                       "0xB80001C0"
#define SYS_TMDS_SCR1_reg                                                            0xB80001C0
#define set_SYS_TMDS_SCR1_reg(data)   (*((volatile unsigned int*) SYS_TMDS_SCR1_reg)=data)
#define get_SYS_TMDS_SCR1_reg   (*((volatile unsigned int*) SYS_TMDS_SCR1_reg))
#define SYS_TMDS_SCR1_inst_adr                                                       "0x0070"
#define SYS_TMDS_SCR1_inst                                                           0x0070
#define SYS_TMDS_SCR1_REG_TV_WDMODE_shift                                            (29)
#define SYS_TMDS_SCR1_REG_TV_WDMODE_mask                                             (0x60000000)
#define SYS_TMDS_SCR1_REG_TV_WDMODE(data)                                            (0x60000000&((data)<<29))
#define SYS_TMDS_SCR1_REG_TV_WDMODE_src(data)                                        ((0x60000000&(data))>>29)
#define SYS_TMDS_SCR1_get_REG_TV_WDMODE(data)                                        ((0x60000000&(data))>>29)
#define SYS_TMDS_SCR1_REG_TVKVCO_shift                                               (28)
#define SYS_TMDS_SCR1_REG_TVKVCO_mask                                                (0x10000000)
#define SYS_TMDS_SCR1_REG_TVKVCO(data)                                               (0x10000000&((data)<<28))
#define SYS_TMDS_SCR1_REG_TVKVCO_src(data)                                           ((0x10000000&(data))>>28)
#define SYS_TMDS_SCR1_get_REG_TVKVCO(data)                                           ((0x10000000&(data))>>28)
#define SYS_TMDS_SCR1_REG_TV_CP_shift                                                (26)
#define SYS_TMDS_SCR1_REG_TV_CP_mask                                                 (0x0C000000)
#define SYS_TMDS_SCR1_REG_TV_CP(data)                                                (0x0C000000&((data)<<26))
#define SYS_TMDS_SCR1_REG_TV_CP_src(data)                                            ((0x0C000000&(data))>>26)
#define SYS_TMDS_SCR1_get_REG_TV_CP(data)                                            ((0x0C000000&(data))>>26)
#define SYS_TMDS_SCR1_REG_TV_CS_shift                                                (24)
#define SYS_TMDS_SCR1_REG_TV_CS_mask                                                 (0x03000000)
#define SYS_TMDS_SCR1_REG_TV_CS(data)                                                (0x03000000&((data)<<24))
#define SYS_TMDS_SCR1_REG_TV_CS_src(data)                                            ((0x03000000&(data))>>24)
#define SYS_TMDS_SCR1_get_REG_TV_CS(data)                                            ((0x03000000&(data))>>24)
#define SYS_TMDS_SCR1_REG_TX_CK5XP_DUTY_shift                                        (22)
#define SYS_TMDS_SCR1_REG_TX_CK5XP_DUTY_mask                                         (0x00C00000)
#define SYS_TMDS_SCR1_REG_TX_CK5XP_DUTY(data)                                        (0x00C00000&((data)<<22))
#define SYS_TMDS_SCR1_REG_TX_CK5XP_DUTY_src(data)                                    ((0x00C00000&(data))>>22)
#define SYS_TMDS_SCR1_get_REG_TX_CK5XP_DUTY(data)                                    ((0x00C00000&(data))>>22)
#define SYS_TMDS_SCR1_REG_TX_CK5XN_DUTY_shift                                        (20)
#define SYS_TMDS_SCR1_REG_TX_CK5XN_DUTY_mask                                         (0x00300000)
#define SYS_TMDS_SCR1_REG_TX_CK5XN_DUTY(data)                                        (0x00300000&((data)<<20))
#define SYS_TMDS_SCR1_REG_TX_CK5XN_DUTY_src(data)                                    ((0x00300000&(data))>>20)
#define SYS_TMDS_SCR1_get_REG_TX_CK5XN_DUTY(data)                                    ((0x00300000&(data))>>20)
#define SYS_TMDS_SCR1_REG_TX_AMP_shift                                               (16)
#define SYS_TMDS_SCR1_REG_TX_AMP_mask                                                (0x000F0000)
#define SYS_TMDS_SCR1_REG_TX_AMP(data)                                               (0x000F0000&((data)<<16))
#define SYS_TMDS_SCR1_REG_TX_AMP_src(data)                                           ((0x000F0000&(data))>>16)
#define SYS_TMDS_SCR1_get_REG_TX_AMP(data)                                           ((0x000F0000&(data))>>16)
#define SYS_TMDS_SCR1_REG_TX_IBIAS_shift                                             (14)
#define SYS_TMDS_SCR1_REG_TX_IBIAS_mask                                              (0x0000C000)
#define SYS_TMDS_SCR1_REG_TX_IBIAS(data)                                             (0x0000C000&((data)<<14))
#define SYS_TMDS_SCR1_REG_TX_IBIAS_src(data)                                         ((0x0000C000&(data))>>14)
#define SYS_TMDS_SCR1_get_REG_TX_IBIAS(data)                                         ((0x0000C000&(data))>>14)
#define SYS_TMDS_SCR1_REG_TX_EMPH_shift                                              (11)
#define SYS_TMDS_SCR1_REG_TX_EMPH_mask                                               (0x00003800)
#define SYS_TMDS_SCR1_REG_TX_EMPH(data)                                              (0x00003800&((data)<<11))
#define SYS_TMDS_SCR1_REG_TX_EMPH_src(data)                                          ((0x00003800&(data))>>11)
#define SYS_TMDS_SCR1_get_REG_TX_EMPH(data)                                          ((0x00003800&(data))>>11)
#define SYS_TMDS_SCR1_REG_TX_EN_EMPH_shift                                           (10)
#define SYS_TMDS_SCR1_REG_TX_EN_EMPH_mask                                            (0x00000400)
#define SYS_TMDS_SCR1_REG_TX_EN_EMPH(data)                                           (0x00000400&((data)<<10))
#define SYS_TMDS_SCR1_REG_TX_EN_EMPH_src(data)                                       ((0x00000400&(data))>>10)
#define SYS_TMDS_SCR1_get_REG_TX_EN_EMPH(data)                                       ((0x00000400&(data))>>10)
#define SYS_TMDS_SCR1_REG_TX_FORCE_VC_shift                                          (9)
#define SYS_TMDS_SCR1_REG_TX_FORCE_VC_mask                                           (0x00000200)
#define SYS_TMDS_SCR1_REG_TX_FORCE_VC(data)                                          (0x00000200&((data)<<9))
#define SYS_TMDS_SCR1_REG_TX_FORCE_VC_src(data)                                      ((0x00000200&(data))>>9)
#define SYS_TMDS_SCR1_get_REG_TX_FORCE_VC(data)                                      ((0x00000200&(data))>>9)
#define SYS_TMDS_SCR1_REG_TX_SET_VC_shift                                            (7)
#define SYS_TMDS_SCR1_REG_TX_SET_VC_mask                                             (0x00000180)
#define SYS_TMDS_SCR1_REG_TX_SET_VC(data)                                            (0x00000180&((data)<<7))
#define SYS_TMDS_SCR1_REG_TX_SET_VC_src(data)                                        ((0x00000180&(data))>>7)
#define SYS_TMDS_SCR1_get_REG_TX_SET_VC(data)                                        ((0x00000180&(data))>>7)
#define SYS_TMDS_SCR1_REG_TX_PLL_EDGE_shift                                          (6)
#define SYS_TMDS_SCR1_REG_TX_PLL_EDGE_mask                                           (0x00000040)
#define SYS_TMDS_SCR1_REG_TX_PLL_EDGE(data)                                          (0x00000040&((data)<<6))
#define SYS_TMDS_SCR1_REG_TX_PLL_EDGE_src(data)                                      ((0x00000040&(data))>>6)
#define SYS_TMDS_SCR1_get_REG_TX_PLL_EDGE(data)                                      ((0x00000040&(data))>>6)
#define SYS_TMDS_SCR1_REG_TX_PLL_ICP_shift                                           (3)
#define SYS_TMDS_SCR1_REG_TX_PLL_ICP_mask                                            (0x00000038)
#define SYS_TMDS_SCR1_REG_TX_PLL_ICP(data)                                           (0x00000038&((data)<<3))
#define SYS_TMDS_SCR1_REG_TX_PLL_ICP_src(data)                                       ((0x00000038&(data))>>3)
#define SYS_TMDS_SCR1_get_REG_TX_PLL_ICP(data)                                       ((0x00000038&(data))>>3)
#define SYS_TMDS_SCR1_REG_TX_PLL_RS_shift                                            (0)
#define SYS_TMDS_SCR1_REG_TX_PLL_RS_mask                                             (0x00000007)
#define SYS_TMDS_SCR1_REG_TX_PLL_RS(data)                                            (0x00000007&((data)<<0))
#define SYS_TMDS_SCR1_REG_TX_PLL_RS_src(data)                                        ((0x00000007&(data))>>0)
#define SYS_TMDS_SCR1_get_REG_TX_PLL_RS(data)                                        ((0x00000007&(data))>>0)


#define SYS_TMDS_SCR2                                                                0x180001C4
#define SYS_TMDS_SCR2_reg_addr                                                       "0xB80001C4"
#define SYS_TMDS_SCR2_reg                                                            0xB80001C4
#define set_SYS_TMDS_SCR2_reg(data)   (*((volatile unsigned int*) SYS_TMDS_SCR2_reg)=data)
#define get_SYS_TMDS_SCR2_reg   (*((volatile unsigned int*) SYS_TMDS_SCR2_reg))
#define SYS_TMDS_SCR2_inst_adr                                                       "0x0071"
#define SYS_TMDS_SCR2_inst                                                           0x0071
#define SYS_TMDS_SCR2_REG_TX_PDRV_ISEL_shift                                         (28)
#define SYS_TMDS_SCR2_REG_TX_PDRV_ISEL_mask                                          (0x30000000)
#define SYS_TMDS_SCR2_REG_TX_PDRV_ISEL(data)                                         (0x30000000&((data)<<28))
#define SYS_TMDS_SCR2_REG_TX_PDRV_ISEL_src(data)                                     ((0x30000000&(data))>>28)
#define SYS_TMDS_SCR2_get_REG_TX_PDRV_ISEL(data)                                     ((0x30000000&(data))>>28)
#define SYS_TMDS_SCR2_REG_TX_PLL_CP_shift                                            (26)
#define SYS_TMDS_SCR2_REG_TX_PLL_CP_mask                                             (0x0C000000)
#define SYS_TMDS_SCR2_REG_TX_PLL_CP(data)                                            (0x0C000000&((data)<<26))
#define SYS_TMDS_SCR2_REG_TX_PLL_CP_src(data)                                        ((0x0C000000&(data))>>26)
#define SYS_TMDS_SCR2_get_REG_TX_PLL_CP(data)                                        ((0x0C000000&(data))>>26)
#define SYS_TMDS_SCR2_REG_TX_PLL_CS_shift                                            (24)
#define SYS_TMDS_SCR2_REG_TX_PLL_CS_mask                                             (0x03000000)
#define SYS_TMDS_SCR2_REG_TX_PLL_CS(data)                                            (0x03000000&((data)<<24))
#define SYS_TMDS_SCR2_REG_TX_PLL_CS_src(data)                                        ((0x03000000&(data))>>24)
#define SYS_TMDS_SCR2_get_REG_TX_PLL_CS(data)                                        ((0x03000000&(data))>>24)
#define SYS_TMDS_SCR2_REG_TX_PLL_KVCO_shift                                          (23)
#define SYS_TMDS_SCR2_REG_TX_PLL_KVCO_mask                                           (0x00800000)
#define SYS_TMDS_SCR2_REG_TX_PLL_KVCO(data)                                          (0x00800000&((data)<<23))
#define SYS_TMDS_SCR2_REG_TX_PLL_KVCO_src(data)                                      ((0x00800000&(data))>>23)
#define SYS_TMDS_SCR2_get_REG_TX_PLL_KVCO(data)                                      ((0x00800000&(data))>>23)
#define SYS_TMDS_SCR2_REG_TX_PLL_PU_shift                                            (22)
#define SYS_TMDS_SCR2_REG_TX_PLL_PU_mask                                             (0x00400000)
#define SYS_TMDS_SCR2_REG_TX_PLL_PU(data)                                            (0x00400000&((data)<<22))
#define SYS_TMDS_SCR2_REG_TX_PLL_PU_src(data)                                        ((0x00400000&(data))>>22)
#define SYS_TMDS_SCR2_get_REG_TX_PLL_PU(data)                                        ((0x00400000&(data))>>22)
#define SYS_TMDS_SCR2_REG_TX_PU_shift                                                (18)
#define SYS_TMDS_SCR2_REG_TX_PU_mask                                                 (0x003C0000)
#define SYS_TMDS_SCR2_REG_TX_PU(data)                                                (0x003C0000&((data)<<18))
#define SYS_TMDS_SCR2_REG_TX_PU_src(data)                                            ((0x003C0000&(data))>>18)
#define SYS_TMDS_SCR2_get_REG_TX_PU(data)                                            ((0x003C0000&(data))>>18)
#define SYS_TMDS_SCR2_REG_TX_DRIVER_shift                                            (16)
#define SYS_TMDS_SCR2_REG_TX_DRIVER_mask                                             (0x00030000)
#define SYS_TMDS_SCR2_REG_TX_DRIVER(data)                                            (0x00030000&((data)<<16))
#define SYS_TMDS_SCR2_REG_TX_DRIVER_src(data)                                        ((0x00030000&(data))>>16)
#define SYS_TMDS_SCR2_get_REG_TX_DRIVER(data)                                        ((0x00030000&(data))>>16)
#define SYS_TMDS_SCR2_REG_TX_SLEW_shift                                              (14)
#define SYS_TMDS_SCR2_REG_TX_SLEW_mask                                               (0x0000C000)
#define SYS_TMDS_SCR2_REG_TX_SLEW(data)                                              (0x0000C000&((data)<<14))
#define SYS_TMDS_SCR2_REG_TX_SLEW_src(data)                                          ((0x0000C000&(data))>>14)
#define SYS_TMDS_SCR2_get_REG_TX_SLEW(data)                                          ((0x0000C000&(data))>>14)
#define SYS_TMDS_SCR2_REG_TX_TST_EN_shift                                            (13)
#define SYS_TMDS_SCR2_REG_TX_TST_EN_mask                                             (0x00002000)
#define SYS_TMDS_SCR2_REG_TX_TST_EN(data)                                            (0x00002000&((data)<<13))
#define SYS_TMDS_SCR2_REG_TX_TST_EN_src(data)                                        ((0x00002000&(data))>>13)
#define SYS_TMDS_SCR2_get_REG_TX_TST_EN(data)                                        ((0x00002000&(data))>>13)
#define SYS_TMDS_SCR2_REG_TX_VGATE_shift                                             (10)
#define SYS_TMDS_SCR2_REG_TX_VGATE_mask                                              (0x00001C00)
#define SYS_TMDS_SCR2_REG_TX_VGATE(data)                                             (0x00001C00&((data)<<10))
#define SYS_TMDS_SCR2_REG_TX_VGATE_src(data)                                         ((0x00001C00&(data))>>10)
#define SYS_TMDS_SCR2_get_REG_TX_VGATE(data)                                         ((0x00001C00&(data))>>10)
#define SYS_TMDS_SCR2_REG_PLL_TST_EN_shift                                           (9)
#define SYS_TMDS_SCR2_REG_PLL_TST_EN_mask                                            (0x00000200)
#define SYS_TMDS_SCR2_REG_PLL_TST_EN(data)                                           (0x00000200&((data)<<9))
#define SYS_TMDS_SCR2_REG_PLL_TST_EN_src(data)                                       ((0x00000200&(data))>>9)
#define SYS_TMDS_SCR2_get_REG_PLL_TST_EN(data)                                       ((0x00000200&(data))>>9)
#define SYS_TMDS_SCR2_REG_TST_SEL_shift                                              (7)
#define SYS_TMDS_SCR2_REG_TST_SEL_mask                                               (0x00000180)
#define SYS_TMDS_SCR2_REG_TST_SEL(data)                                              (0x00000180&((data)<<7))
#define SYS_TMDS_SCR2_REG_TST_SEL_src(data)                                          ((0x00000180&(data))>>7)
#define SYS_TMDS_SCR2_get_REG_TST_SEL(data)                                          ((0x00000180&(data))>>7)
#define SYS_TMDS_SCR2_REG_TX_BYPASS_PLL_shift                                        (6)
#define SYS_TMDS_SCR2_REG_TX_BYPASS_PLL_mask                                         (0x00000040)
#define SYS_TMDS_SCR2_REG_TX_BYPASS_PLL(data)                                        (0x00000040&((data)<<6))
#define SYS_TMDS_SCR2_REG_TX_BYPASS_PLL_src(data)                                    ((0x00000040&(data))>>6)
#define SYS_TMDS_SCR2_get_REG_TX_BYPASS_PLL(data)                                    ((0x00000040&(data))>>6)
#define SYS_TMDS_SCR2_REG_TX_RT_EN_shift                                             (5)
#define SYS_TMDS_SCR2_REG_TX_RT_EN_mask                                              (0x00000020)
#define SYS_TMDS_SCR2_REG_TX_RT_EN(data)                                             (0x00000020&((data)<<5))
#define SYS_TMDS_SCR2_REG_TX_RT_EN_src(data)                                         ((0x00000020&(data))>>5)
#define SYS_TMDS_SCR2_get_REG_TX_RT_EN(data)                                         ((0x00000020&(data))>>5)
#define SYS_TMDS_SCR2_REG_TX_RT_SEL_shift                                            (3)
#define SYS_TMDS_SCR2_REG_TX_RT_SEL_mask                                             (0x00000018)
#define SYS_TMDS_SCR2_REG_TX_RT_SEL(data)                                            (0x00000018&((data)<<3))
#define SYS_TMDS_SCR2_REG_TX_RT_SEL_src(data)                                        ((0x00000018&(data))>>3)
#define SYS_TMDS_SCR2_get_REG_TX_RT_SEL(data)                                        ((0x00000018&(data))>>3)
#define SYS_TMDS_SCR2_REG_PLL_VCO_SCALE_shift                                        (1)
#define SYS_TMDS_SCR2_REG_PLL_VCO_SCALE_mask                                         (0x00000006)
#define SYS_TMDS_SCR2_REG_PLL_VCO_SCALE(data)                                        (0x00000006&((data)<<1))
#define SYS_TMDS_SCR2_REG_PLL_VCO_SCALE_src(data)                                    ((0x00000006&(data))>>1)
#define SYS_TMDS_SCR2_get_REG_PLL_VCO_SCALE(data)                                    ((0x00000006&(data))>>1)
#define SYS_TMDS_SCR2_REG_BYPASS_DIN_shift                                           (0)
#define SYS_TMDS_SCR2_REG_BYPASS_DIN_mask                                            (0x00000001)
#define SYS_TMDS_SCR2_REG_BYPASS_DIN(data)                                           (0x00000001&((data)<<0))
#define SYS_TMDS_SCR2_REG_BYPASS_DIN_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_TMDS_SCR2_get_REG_BYPASS_DIN(data)                                       ((0x00000001&(data))>>0)


#define SYS_TMDS_SCR3                                                                0x180001C8
#define SYS_TMDS_SCR3_reg_addr                                                       "0xB80001C8"
#define SYS_TMDS_SCR3_reg                                                            0xB80001C8
#define set_SYS_TMDS_SCR3_reg(data)   (*((volatile unsigned int*) SYS_TMDS_SCR3_reg)=data)
#define get_SYS_TMDS_SCR3_reg   (*((volatile unsigned int*) SYS_TMDS_SCR3_reg))
#define SYS_TMDS_SCR3_inst_adr                                                       "0x0072"
#define SYS_TMDS_SCR3_inst                                                           0x0072
#define SYS_TMDS_SCR3_REG_TX_PLL_WDMODE_shift                                        (29)
#define SYS_TMDS_SCR3_REG_TX_PLL_WDMODE_mask                                         (0x60000000)
#define SYS_TMDS_SCR3_REG_TX_PLL_WDMODE(data)                                        (0x60000000&((data)<<29))
#define SYS_TMDS_SCR3_REG_TX_PLL_WDMODE_src(data)                                    ((0x60000000&(data))>>29)
#define SYS_TMDS_SCR3_get_REG_TX_PLL_WDMODE(data)                                    ((0x60000000&(data))>>29)
#define SYS_TMDS_SCR3_REG_TX_V1P05_SEL_shift                                         (27)
#define SYS_TMDS_SCR3_REG_TX_V1P05_SEL_mask                                          (0x18000000)
#define SYS_TMDS_SCR3_REG_TX_V1P05_SEL(data)                                         (0x18000000&((data)<<27))
#define SYS_TMDS_SCR3_REG_TX_V1P05_SEL_src(data)                                     ((0x18000000&(data))>>27)
#define SYS_TMDS_SCR3_get_REG_TX_V1P05_SEL(data)                                     ((0x18000000&(data))>>27)
#define SYS_TMDS_SCR3_REG_LDO_CCO_PU_shift                                           (26)
#define SYS_TMDS_SCR3_REG_LDO_CCO_PU_mask                                            (0x04000000)
#define SYS_TMDS_SCR3_REG_LDO_CCO_PU(data)                                           (0x04000000&((data)<<26))
#define SYS_TMDS_SCR3_REG_LDO_CCO_PU_src(data)                                       ((0x04000000&(data))>>26)
#define SYS_TMDS_SCR3_get_REG_LDO_CCO_PU(data)                                       ((0x04000000&(data))>>26)
#define SYS_TMDS_SCR3_REG_LDO_CCO_VSEL_shift                                         (24)
#define SYS_TMDS_SCR3_REG_LDO_CCO_VSEL_mask                                          (0x03000000)
#define SYS_TMDS_SCR3_REG_LDO_CCO_VSEL(data)                                         (0x03000000&((data)<<24))
#define SYS_TMDS_SCR3_REG_LDO_CCO_VSEL_src(data)                                     ((0x03000000&(data))>>24)
#define SYS_TMDS_SCR3_get_REG_LDO_CCO_VSEL(data)                                     ((0x03000000&(data))>>24)
#define SYS_TMDS_SCR3_REG_LDO_PLL_PU_shift                                           (23)
#define SYS_TMDS_SCR3_REG_LDO_PLL_PU_mask                                            (0x00800000)
#define SYS_TMDS_SCR3_REG_LDO_PLL_PU(data)                                           (0x00800000&((data)<<23))
#define SYS_TMDS_SCR3_REG_LDO_PLL_PU_src(data)                                       ((0x00800000&(data))>>23)
#define SYS_TMDS_SCR3_get_REG_LDO_PLL_PU(data)                                       ((0x00800000&(data))>>23)
#define SYS_TMDS_SCR3_REG_LDO_PLL_VSEL_shift                                         (20)
#define SYS_TMDS_SCR3_REG_LDO_PLL_VSEL_mask                                          (0x00700000)
#define SYS_TMDS_SCR3_REG_LDO_PLL_VSEL(data)                                         (0x00700000&((data)<<20))
#define SYS_TMDS_SCR3_REG_LDO_PLL_VSEL_src(data)                                     ((0x00700000&(data))>>20)
#define SYS_TMDS_SCR3_get_REG_LDO_PLL_VSEL(data)                                     ((0x00700000&(data))>>20)
#define SYS_TMDS_SCR3_REG_EN_MHL_shift                                               (19)
#define SYS_TMDS_SCR3_REG_EN_MHL_mask                                                (0x00080000)
#define SYS_TMDS_SCR3_REG_EN_MHL(data)                                               (0x00080000&((data)<<19))
#define SYS_TMDS_SCR3_REG_EN_MHL_src(data)                                           ((0x00080000&(data))>>19)
#define SYS_TMDS_SCR3_get_REG_EN_MHL(data)                                           ((0x00080000&(data))>>19)
#define SYS_TMDS_SCR3_REG_FORCE_RXSENSE_shift                                        (18)
#define SYS_TMDS_SCR3_REG_FORCE_RXSENSE_mask                                         (0x00040000)
#define SYS_TMDS_SCR3_REG_FORCE_RXSENSE(data)                                        (0x00040000&((data)<<18))
#define SYS_TMDS_SCR3_REG_FORCE_RXSENSE_src(data)                                    ((0x00040000&(data))>>18)
#define SYS_TMDS_SCR3_get_REG_FORCE_RXSENSE(data)                                    ((0x00040000&(data))>>18)
#define SYS_TMDS_SCR3_REG_RXSENSE_shift                                              (16)
#define SYS_TMDS_SCR3_REG_RXSENSE_mask                                               (0x00030000)
#define SYS_TMDS_SCR3_REG_RXSENSE(data)                                              (0x00030000&((data)<<16))
#define SYS_TMDS_SCR3_REG_RXSENSE_src(data)                                          ((0x00030000&(data))>>16)
#define SYS_TMDS_SCR3_get_REG_RXSENSE(data)                                          ((0x00030000&(data))>>16)
#define SYS_TMDS_SCR3_REG_MHL_DIV_shift                                              (15)
#define SYS_TMDS_SCR3_REG_MHL_DIV_mask                                               (0x00008000)
#define SYS_TMDS_SCR3_REG_MHL_DIV(data)                                              (0x00008000&((data)<<15))
#define SYS_TMDS_SCR3_REG_MHL_DIV_src(data)                                          ((0x00008000&(data))>>15)
#define SYS_TMDS_SCR3_get_REG_MHL_DIV(data)                                          ((0x00008000&(data))>>15)
#define SYS_TMDS_SCR3_REG_MHL_VCM_shift                                              (13)
#define SYS_TMDS_SCR3_REG_MHL_VCM_mask                                               (0x00006000)
#define SYS_TMDS_SCR3_REG_MHL_VCM(data)                                              (0x00006000&((data)<<13))
#define SYS_TMDS_SCR3_REG_MHL_VCM_src(data)                                          ((0x00006000&(data))>>13)
#define SYS_TMDS_SCR3_get_REG_MHL_VCM(data)                                          ((0x00006000&(data))>>13)
#define SYS_TMDS_SCR3_REG_DIFF_RT_EN_shift                                           (12)
#define SYS_TMDS_SCR3_REG_DIFF_RT_EN_mask                                            (0x00001000)
#define SYS_TMDS_SCR3_REG_DIFF_RT_EN(data)                                           (0x00001000&((data)<<12))
#define SYS_TMDS_SCR3_REG_DIFF_RT_EN_src(data)                                       ((0x00001000&(data))>>12)
#define SYS_TMDS_SCR3_get_REG_DIFF_RT_EN(data)                                       ((0x00001000&(data))>>12)
#define SYS_TMDS_SCR3_REG_CEC_ENB_shift                                              (11)
#define SYS_TMDS_SCR3_REG_CEC_ENB_mask                                               (0x00000800)
#define SYS_TMDS_SCR3_REG_CEC_ENB(data)                                              (0x00000800&((data)<<11))
#define SYS_TMDS_SCR3_REG_CEC_ENB_src(data)                                          ((0x00000800&(data))>>11)
#define SYS_TMDS_SCR3_get_REG_CEC_ENB(data)                                          ((0x00000800&(data))>>11)
#define SYS_TMDS_SCR3_REG_CEC_RSEL_shift                                             (8)
#define SYS_TMDS_SCR3_REG_CEC_RSEL_mask                                              (0x00000700)
#define SYS_TMDS_SCR3_REG_CEC_RSEL(data)                                             (0x00000700&((data)<<8))
#define SYS_TMDS_SCR3_REG_CEC_RSEL_src(data)                                         ((0x00000700&(data))>>8)
#define SYS_TMDS_SCR3_get_REG_CEC_RSEL(data)                                         ((0x00000700&(data))>>8)
#define SYS_TMDS_SCR3_REG_CEC_RPU_EN_shift                                           (7)
#define SYS_TMDS_SCR3_REG_CEC_RPU_EN_mask                                            (0x00000080)
#define SYS_TMDS_SCR3_REG_CEC_RPU_EN(data)                                           (0x00000080&((data)<<7))
#define SYS_TMDS_SCR3_REG_CEC_RPU_EN_src(data)                                       ((0x00000080&(data))>>7)
#define SYS_TMDS_SCR3_get_REG_CEC_RPU_EN(data)                                       ((0x00000080&(data))>>7)
#define SYS_TMDS_SCR3_REG_HPD_EN_shift                                               (6)
#define SYS_TMDS_SCR3_REG_HPD_EN_mask                                                (0x00000040)
#define SYS_TMDS_SCR3_REG_HPD_EN(data)                                               (0x00000040&((data)<<6))
#define SYS_TMDS_SCR3_REG_HPD_EN_src(data)                                           ((0x00000040&(data))>>6)
#define SYS_TMDS_SCR3_get_REG_HPD_EN(data)                                           ((0x00000040&(data))>>6)
#define SYS_TMDS_SCR3_REG_CABLE_DET_EN_shift                                         (5)
#define SYS_TMDS_SCR3_REG_CABLE_DET_EN_mask                                          (0x00000020)
#define SYS_TMDS_SCR3_REG_CABLE_DET_EN(data)                                         (0x00000020&((data)<<5))
#define SYS_TMDS_SCR3_REG_CABLE_DET_EN_src(data)                                     ((0x00000020&(data))>>5)
#define SYS_TMDS_SCR3_get_REG_CABLE_DET_EN(data)                                     ((0x00000020&(data))>>5)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_PU_shift                                          (4)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_PU_mask                                           (0x00000010)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_PU(data)                                          (0x00000010&((data)<<4))
#define SYS_TMDS_SCR3_REG_LDO_TMDS_PU_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_TMDS_SCR3_get_REG_LDO_TMDS_PU(data)                                      ((0x00000010&(data))>>4)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_VSEL_shift                                        (1)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_VSEL_mask                                         (0x0000000E)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_VSEL(data)                                        (0x0000000E&((data)<<1))
#define SYS_TMDS_SCR3_REG_LDO_TMDS_VSEL_src(data)                                    ((0x0000000E&(data))>>1)
#define SYS_TMDS_SCR3_get_REG_LDO_TMDS_VSEL(data)                                    ((0x0000000E&(data))>>1)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_CAPSEL_shift                                      (0)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_CAPSEL_mask                                       (0x00000001)
#define SYS_TMDS_SCR3_REG_LDO_TMDS_CAPSEL(data)                                      (0x00000001&((data)<<0))
#define SYS_TMDS_SCR3_REG_LDO_TMDS_CAPSEL_src(data)                                  ((0x00000001&(data))>>0)
#define SYS_TMDS_SCR3_get_REG_LDO_TMDS_CAPSEL(data)                                  ((0x00000001&(data))>>0)


#define SYS_TVPLL_CTRL1                                                              0x180001CC
#define SYS_TVPLL_CTRL1_reg_addr                                                     "0xB80001CC"
#define SYS_TVPLL_CTRL1_reg                                                          0xB80001CC
#define set_SYS_TVPLL_CTRL1_reg(data)   (*((volatile unsigned int*) SYS_TVPLL_CTRL1_reg)=data)
#define get_SYS_TVPLL_CTRL1_reg   (*((volatile unsigned int*) SYS_TVPLL_CTRL1_reg))
#define SYS_TVPLL_CTRL1_inst_adr                                                     "0x0073"
#define SYS_TVPLL_CTRL1_inst                                                         0x0073
#define SYS_TVPLL_CTRL1_REG_TV_PRE_DIV_shift                                         (20)
#define SYS_TVPLL_CTRL1_REG_TV_PRE_DIV_mask                                          (0x00100000)
#define SYS_TVPLL_CTRL1_REG_TV_PRE_DIV(data)                                         (0x00100000&((data)<<20))
#define SYS_TVPLL_CTRL1_REG_TV_PRE_DIV_src(data)                                     ((0x00100000&(data))>>20)
#define SYS_TVPLL_CTRL1_get_REG_TV_PRE_DIV(data)                                     ((0x00100000&(data))>>20)
#define SYS_TVPLL_CTRL1_REG_TV_LDIV_shift                                            (14)
#define SYS_TVPLL_CTRL1_REG_TV_LDIV_mask                                             (0x000FC000)
#define SYS_TVPLL_CTRL1_REG_TV_LDIV(data)                                            (0x000FC000&((data)<<14))
#define SYS_TVPLL_CTRL1_REG_TV_LDIV_src(data)                                        ((0x000FC000&(data))>>14)
#define SYS_TVPLL_CTRL1_get_REG_TV_LDIV(data)                                        ((0x000FC000&(data))>>14)
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP_EN_shift                                        (13)
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP_EN_mask                                         (0x00002000)
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP_EN(data)                                        (0x00002000&((data)<<13))
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP_EN_src(data)                                    ((0x00002000&(data))>>13)
#define SYS_TVPLL_CTRL1_get_REG_TV_PSTEP_EN(data)                                    ((0x00002000&(data))>>13)
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP_shift                                           (10)
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP_mask                                            (0x00001C00)
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP(data)                                           (0x00001C00&((data)<<10))
#define SYS_TVPLL_CTRL1_REG_TV_PSTEP_src(data)                                       ((0x00001C00&(data))>>10)
#define SYS_TVPLL_CTRL1_get_REG_TV_PSTEP(data)                                       ((0x00001C00&(data))>>10)
#define SYS_TVPLL_CTRL1_REG_HDMI_CK_EN_shift                                         (9)
#define SYS_TVPLL_CTRL1_REG_HDMI_CK_EN_mask                                          (0x00000200)
#define SYS_TVPLL_CTRL1_REG_HDMI_CK_EN(data)                                         (0x00000200&((data)<<9))
#define SYS_TVPLL_CTRL1_REG_HDMI_CK_EN_src(data)                                     ((0x00000200&(data))>>9)
#define SYS_TVPLL_CTRL1_get_REG_HDMI_CK_EN(data)                                     ((0x00000200&(data))>>9)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV3_shift                                         (8)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV3_mask                                          (0x00000100)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV3(data)                                         (0x00000100&((data)<<8))
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV3_src(data)                                     ((0x00000100&(data))>>8)
#define SYS_TVPLL_CTRL1_get_REG_PIXEL_DIV3(data)                                     ((0x00000100&(data))>>8)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV5_shift                                         (7)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV5_mask                                          (0x00000080)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV5(data)                                         (0x00000080&((data)<<7))
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV5_src(data)                                     ((0x00000080&(data))>>7)
#define SYS_TVPLL_CTRL1_get_REG_PIXEL_DIV5(data)                                     ((0x00000080&(data))>>7)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV16_shift                                        (4)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV16_mask                                         (0x00000070)
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV16(data)                                        (0x00000070&((data)<<4))
#define SYS_TVPLL_CTRL1_REG_PIXEL_DIV16_src(data)                                    ((0x00000070&(data))>>4)
#define SYS_TVPLL_CTRL1_get_REG_PIXEL_DIV16(data)                                    ((0x00000070&(data))>>4)
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV5_shift                                          (3)
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV5_mask                                           (0x00000008)
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV5(data)                                          (0x00000008&((data)<<3))
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV5_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_TVPLL_CTRL1_get_REG_TMDS_DIV5(data)                                      ((0x00000008&(data))>>3)
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV16_shift                                         (0)
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV16_mask                                          (0x00000007)
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV16(data)                                         (0x00000007&((data)<<0))
#define SYS_TVPLL_CTRL1_REG_TMDS_DIV16_src(data)                                     ((0x00000007&(data))>>0)
#define SYS_TVPLL_CTRL1_get_REG_TMDS_DIV16(data)                                     ((0x00000007&(data))>>0)


#define SYS_TVPLL_CTRL2                                                              0x180001D0
#define SYS_TVPLL_CTRL2_reg_addr                                                     "0xB80001D0"
#define SYS_TVPLL_CTRL2_reg                                                          0xB80001D0
#define set_SYS_TVPLL_CTRL2_reg(data)   (*((volatile unsigned int*) SYS_TVPLL_CTRL2_reg)=data)
#define get_SYS_TVPLL_CTRL2_reg   (*((volatile unsigned int*) SYS_TVPLL_CTRL2_reg))
#define SYS_TVPLL_CTRL2_inst_adr                                                     "0x0074"
#define SYS_TVPLL_CTRL2_inst                                                         0x0074
#define SYS_TVPLL_CTRL2_REG_SEL_REF_CLK27_shift                                      (28)
#define SYS_TVPLL_CTRL2_REG_SEL_REF_CLK27_mask                                       (0x10000000)
#define SYS_TVPLL_CTRL2_REG_SEL_REF_CLK27(data)                                      (0x10000000&((data)<<28))
#define SYS_TVPLL_CTRL2_REG_SEL_REF_CLK27_src(data)                                  ((0x10000000&(data))>>28)
#define SYS_TVPLL_CTRL2_get_REG_SEL_REF_CLK27(data)                                  ((0x10000000&(data))>>28)
#define SYS_TVPLL_CTRL2_REG_RESERVE_shift                                            (12)
#define SYS_TVPLL_CTRL2_REG_RESERVE_mask                                             (0x0FFFF000)
#define SYS_TVPLL_CTRL2_REG_RESERVE(data)                                            (0x0FFFF000&((data)<<12))
#define SYS_TVPLL_CTRL2_REG_RESERVE_src(data)                                        ((0x0FFFF000&(data))>>12)
#define SYS_TVPLL_CTRL2_get_REG_RESERVE(data)                                        ((0x0FFFF000&(data))>>12)
#define SYS_TVPLL_CTRL2_REG_TV_PLL_PU_shift                                          (11)
#define SYS_TVPLL_CTRL2_REG_TV_PLL_PU_mask                                           (0x00000800)
#define SYS_TVPLL_CTRL2_REG_TV_PLL_PU(data)                                          (0x00000800&((data)<<11))
#define SYS_TVPLL_CTRL2_REG_TV_PLL_PU_src(data)                                      ((0x00000800&(data))>>11)
#define SYS_TVPLL_CTRL2_get_REG_TV_PLL_PU(data)                                      ((0x00000800&(data))>>11)
#define SYS_TVPLL_CTRL2_REG_TV_ICP_shift                                             (8)
#define SYS_TVPLL_CTRL2_REG_TV_ICP_mask                                              (0x00000700)
#define SYS_TVPLL_CTRL2_REG_TV_ICP(data)                                             (0x00000700&((data)<<8))
#define SYS_TVPLL_CTRL2_REG_TV_ICP_src(data)                                         ((0x00000700&(data))>>8)
#define SYS_TVPLL_CTRL2_get_REG_TV_ICP(data)                                         ((0x00000700&(data))>>8)
#define SYS_TVPLL_CTRL2_REG_TV_RS_shift                                              (5)
#define SYS_TVPLL_CTRL2_REG_TV_RS_mask                                               (0x000000E0)
#define SYS_TVPLL_CTRL2_REG_TV_RS(data)                                              (0x000000E0&((data)<<5))
#define SYS_TVPLL_CTRL2_REG_TV_RS_src(data)                                          ((0x000000E0&(data))>>5)
#define SYS_TVPLL_CTRL2_get_REG_TV_RS(data)                                          ((0x000000E0&(data))>>5)
#define SYS_TVPLL_CTRL2_REG_TV_BYPASS_PLL_shift                                      (4)
#define SYS_TVPLL_CTRL2_REG_TV_BYPASS_PLL_mask                                       (0x00000010)
#define SYS_TVPLL_CTRL2_REG_TV_BYPASS_PLL(data)                                      (0x00000010&((data)<<4))
#define SYS_TVPLL_CTRL2_REG_TV_BYPASS_PLL_src(data)                                  ((0x00000010&(data))>>4)
#define SYS_TVPLL_CTRL2_get_REG_TV_BYPASS_PLL(data)                                  ((0x00000010&(data))>>4)
#define SYS_TVPLL_CTRL2_REG_TV_FORCE_VC_shift                                        (3)
#define SYS_TVPLL_CTRL2_REG_TV_FORCE_VC_mask                                         (0x00000008)
#define SYS_TVPLL_CTRL2_REG_TV_FORCE_VC(data)                                        (0x00000008&((data)<<3))
#define SYS_TVPLL_CTRL2_REG_TV_FORCE_VC_src(data)                                    ((0x00000008&(data))>>3)
#define SYS_TVPLL_CTRL2_get_REG_TV_FORCE_VC(data)                                    ((0x00000008&(data))>>3)
#define SYS_TVPLL_CTRL2_REG_TV_SET_VC_shift                                          (1)
#define SYS_TVPLL_CTRL2_REG_TV_SET_VC_mask                                           (0x00000006)
#define SYS_TVPLL_CTRL2_REG_TV_SET_VC(data)                                          (0x00000006&((data)<<1))
#define SYS_TVPLL_CTRL2_REG_TV_SET_VC_src(data)                                      ((0x00000006&(data))>>1)
#define SYS_TVPLL_CTRL2_get_REG_TV_SET_VC(data)                                      ((0x00000006&(data))>>1)
#define SYS_TVPLL_CTRL2_REG_TV_TST_EN_shift                                          (0)
#define SYS_TVPLL_CTRL2_REG_TV_TST_EN_mask                                           (0x00000001)
#define SYS_TVPLL_CTRL2_REG_TV_TST_EN(data)                                          (0x00000001&((data)<<0))
#define SYS_TVPLL_CTRL2_REG_TV_TST_EN_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_TVPLL_CTRL2_get_REG_TV_TST_EN(data)                                      ((0x00000001&(data))>>0)


#define SYS_TVPLL_CTRL3                                                              0x180001D4
#define SYS_TVPLL_CTRL3_reg_addr                                                     "0xB80001D4"
#define SYS_TVPLL_CTRL3_reg                                                          0xB80001D4
#define set_SYS_TVPLL_CTRL3_reg(data)   (*((volatile unsigned int*) SYS_TVPLL_CTRL3_reg)=data)
#define get_SYS_TVPLL_CTRL3_reg   (*((volatile unsigned int*) SYS_TVPLL_CTRL3_reg))
#define SYS_TVPLL_CTRL3_inst_adr                                                     "0x0075"
#define SYS_TVPLL_CTRL3_inst                                                         0x0075
#define SYS_TVPLL_CTRL3_reg_pcr_smooth_en_shift                                      (24)
#define SYS_TVPLL_CTRL3_reg_pcr_smooth_en_mask                                       (0x01000000)
#define SYS_TVPLL_CTRL3_reg_pcr_smooth_en(data)                                      (0x01000000&((data)<<24))
#define SYS_TVPLL_CTRL3_reg_pcr_smooth_en_src(data)                                  ((0x01000000&(data))>>24)
#define SYS_TVPLL_CTRL3_get_reg_pcr_smooth_en(data)                                  ((0x01000000&(data))>>24)
#define SYS_TVPLL_CTRL3_reg_pcr_phase_sel_shift                                      (22)
#define SYS_TVPLL_CTRL3_reg_pcr_phase_sel_mask                                       (0x00400000)
#define SYS_TVPLL_CTRL3_reg_pcr_phase_sel(data)                                      (0x00400000&((data)<<22))
#define SYS_TVPLL_CTRL3_reg_pcr_phase_sel_src(data)                                  ((0x00400000&(data))>>22)
#define SYS_TVPLL_CTRL3_get_reg_pcr_phase_sel(data)                                  ((0x00400000&(data))>>22)
#define SYS_TVPLL_CTRL3_reg_pcr_ctl_en_shift                                         (20)
#define SYS_TVPLL_CTRL3_reg_pcr_ctl_en_mask                                          (0x00100000)
#define SYS_TVPLL_CTRL3_reg_pcr_ctl_en(data)                                         (0x00100000&((data)<<20))
#define SYS_TVPLL_CTRL3_reg_pcr_ctl_en_src(data)                                     ((0x00100000&(data))>>20)
#define SYS_TVPLL_CTRL3_get_reg_pcr_ctl_en(data)                                     ((0x00100000&(data))>>20)
#define SYS_TVPLL_CTRL3_REG_PLLDDS_FUPDN_shift                                       (18)
#define SYS_TVPLL_CTRL3_REG_PLLDDS_FUPDN_mask                                        (0x00040000)
#define SYS_TVPLL_CTRL3_REG_PLLDDS_FUPDN(data)                                       (0x00040000&((data)<<18))
#define SYS_TVPLL_CTRL3_REG_PLLDDS_FUPDN_src(data)                                   ((0x00040000&(data))>>18)
#define SYS_TVPLL_CTRL3_get_REG_PLLDDS_FUPDN(data)                                   ((0x00040000&(data))>>18)
#define SYS_TVPLL_CTRL3_REG_PLLDDS_DDSEN_shift                                       (17)
#define SYS_TVPLL_CTRL3_REG_PLLDDS_DDSEN_mask                                        (0x00020000)
#define SYS_TVPLL_CTRL3_REG_PLLDDS_DDSEN(data)                                       (0x00020000&((data)<<17))
#define SYS_TVPLL_CTRL3_REG_PLLDDS_DDSEN_src(data)                                   ((0x00020000&(data))>>17)
#define SYS_TVPLL_CTRL3_get_REG_PLLDDS_DDSEN(data)                                   ((0x00020000&(data))>>17)
#define SYS_TVPLL_CTRL3_reg_shuffle_en_shift                                         (12)
#define SYS_TVPLL_CTRL3_reg_shuffle_en_mask                                          (0x00001000)
#define SYS_TVPLL_CTRL3_reg_shuffle_en(data)                                         (0x00001000&((data)<<12))
#define SYS_TVPLL_CTRL3_reg_shuffle_en_src(data)                                     ((0x00001000&(data))>>12)
#define SYS_TVPLL_CTRL3_get_reg_shuffle_en(data)                                     ((0x00001000&(data))>>12)
#define SYS_TVPLL_CTRL3_REG_TVPLL_FUPDN_shift                                        (11)
#define SYS_TVPLL_CTRL3_REG_TVPLL_FUPDN_mask                                         (0x00000800)
#define SYS_TVPLL_CTRL3_REG_TVPLL_FUPDN(data)                                        (0x00000800&((data)<<11))
#define SYS_TVPLL_CTRL3_REG_TVPLL_FUPDN_src(data)                                    ((0x00000800&(data))>>11)
#define SYS_TVPLL_CTRL3_get_REG_TVPLL_FUPDN(data)                                    ((0x00000800&(data))>>11)
#define SYS_TVPLL_CTRL3_REG_TVPLL_RESERVE_shift                                      (10)
#define SYS_TVPLL_CTRL3_REG_TVPLL_RESERVE_mask                                       (0x00000400)
#define SYS_TVPLL_CTRL3_REG_TVPLL_RESERVE(data)                                      (0x00000400&((data)<<10))
#define SYS_TVPLL_CTRL3_REG_TVPLL_RESERVE_src(data)                                  ((0x00000400&(data))>>10)
#define SYS_TVPLL_CTRL3_get_REG_TVPLL_RESERVE(data)                                  ((0x00000400&(data))>>10)
#define SYS_TVPLL_CTRL3_REG_TVPLL_STOP_shift                                         (9)
#define SYS_TVPLL_CTRL3_REG_TVPLL_STOP_mask                                          (0x00000200)
#define SYS_TVPLL_CTRL3_REG_TVPLL_STOP(data)                                         (0x00000200&((data)<<9))
#define SYS_TVPLL_CTRL3_REG_TVPLL_STOP_src(data)                                     ((0x00000200&(data))>>9)
#define SYS_TVPLL_CTRL3_get_REG_TVPLL_STOP(data)                                     ((0x00000200&(data))>>9)


#define SYS_TVPLL_CTRL4                                                              0x180001D8
#define SYS_TVPLL_CTRL4_reg_addr                                                     "0xB80001D8"
#define SYS_TVPLL_CTRL4_reg                                                          0xB80001D8
#define set_SYS_TVPLL_CTRL4_reg(data)   (*((volatile unsigned int*) SYS_TVPLL_CTRL4_reg)=data)
#define get_SYS_TVPLL_CTRL4_reg   (*((volatile unsigned int*) SYS_TVPLL_CTRL4_reg))
#define SYS_TVPLL_CTRL4_inst_adr                                                     "0x0076"
#define SYS_TVPLL_CTRL4_inst                                                         0x0076
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_ACC_shift                                     (16)
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_ACC_mask                                      (0xFFFF0000)
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_ACC(data)                                     (0xFFFF0000&((data)<<16))
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_ACC_src(data)                                 ((0xFFFF0000&(data))>>16)
#define SYS_TVPLL_CTRL4_get_reg_PLLDDS_PCR_ACC(data)                                 ((0xFFFF0000&(data))>>16)
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_OVERFLOW_shift                                (0)
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_OVERFLOW_mask                                 (0x0000FFFF)
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_OVERFLOW(data)                                (0x0000FFFF&((data)<<0))
#define SYS_TVPLL_CTRL4_reg_PLLDDS_PCR_OVERFLOW_src(data)                            ((0x0000FFFF&(data))>>0)
#define SYS_TVPLL_CTRL4_get_reg_PLLDDS_PCR_OVERFLOW(data)                            ((0x0000FFFF&(data))>>0)


#define SYS_TVPLL_CTRL5                                                              0x180001DC
#define SYS_TVPLL_CTRL5_reg_addr                                                     "0xB80001DC"
#define SYS_TVPLL_CTRL5_reg                                                          0xB80001DC
#define set_SYS_TVPLL_CTRL5_reg(data)   (*((volatile unsigned int*) SYS_TVPLL_CTRL5_reg)=data)
#define get_SYS_TVPLL_CTRL5_reg   (*((volatile unsigned int*) SYS_TVPLL_CTRL5_reg))
#define SYS_TVPLL_CTRL5_inst_adr                                                     "0x0077"
#define SYS_TVPLL_CTRL5_inst                                                         0x0077
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add_shift                                    (16)
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add_mask                                     (0x00FF0000)
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add(data)                                    (0x00FF0000&((data)<<16))
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add_src(data)                                ((0x00FF0000&(data))>>16)
#define SYS_TVPLL_CTRL5_get_REG_PCR_A_N_nxt_add(data)                                ((0x00FF0000&(data))>>16)
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add_period_shift                             (0)
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add_period_mask                              (0x0000FFFF)
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add_period(data)                             (0x0000FFFF&((data)<<0))
#define SYS_TVPLL_CTRL5_REG_PCR_A_N_nxt_add_period_src(data)                         ((0x0000FFFF&(data))>>0)
#define SYS_TVPLL_CTRL5_get_REG_PCR_A_N_nxt_add_period(data)                         ((0x0000FFFF&(data))>>0)


#define SYS_TVPLL_CTRL6                                                              0x180001F0
#define SYS_TVPLL_CTRL6_reg_addr                                                     "0xB80001F0"
#define SYS_TVPLL_CTRL6_reg                                                          0xB80001F0
#define set_SYS_TVPLL_CTRL6_reg(data)   (*((volatile unsigned int*) SYS_TVPLL_CTRL6_reg)=data)
#define get_SYS_TVPLL_CTRL6_reg   (*((volatile unsigned int*) SYS_TVPLL_CTRL6_reg))
#define SYS_TVPLL_CTRL6_inst_adr                                                     "0x007C"
#define SYS_TVPLL_CTRL6_inst                                                         0x007C
#define SYS_TVPLL_CTRL6_reg_n_PCR_A_N_nxt_shift                                      (16)
#define SYS_TVPLL_CTRL6_reg_n_PCR_A_N_nxt_mask                                       (0xFFFF0000)
#define SYS_TVPLL_CTRL6_reg_n_PCR_A_N_nxt(data)                                      (0xFFFF0000&((data)<<16))
#define SYS_TVPLL_CTRL6_reg_n_PCR_A_N_nxt_src(data)                                  ((0xFFFF0000&(data))>>16)
#define SYS_TVPLL_CTRL6_get_reg_n_PCR_A_N_nxt(data)                                  ((0xFFFF0000&(data))>>16)
#define SYS_TVPLL_CTRL6_reg_PCR_A_N_nxt_shift                                        (0)
#define SYS_TVPLL_CTRL6_reg_PCR_A_N_nxt_mask                                         (0x0000FFFF)
#define SYS_TVPLL_CTRL6_reg_PCR_A_N_nxt(data)                                        (0x0000FFFF&((data)<<0))
#define SYS_TVPLL_CTRL6_reg_PCR_A_N_nxt_src(data)                                    ((0x0000FFFF&(data))>>0)
#define SYS_TVPLL_CTRL6_get_reg_PCR_A_N_nxt(data)                                    ((0x0000FFFF&(data))>>0)


#define SYS_PLL_GPU1                                                                 0x180001E0
#define SYS_PLL_GPU1_reg_addr                                                        "0xB80001E0"
#define SYS_PLL_GPU1_reg                                                             0xB80001E0
#define set_SYS_PLL_GPU1_reg(data)   (*((volatile unsigned int*) SYS_PLL_GPU1_reg)=data)
#define get_SYS_PLL_GPU1_reg   (*((volatile unsigned int*) SYS_PLL_GPU1_reg))
#define SYS_PLL_GPU1_inst_adr                                                        "0x0078"
#define SYS_PLL_GPU1_inst                                                            0x0078
#define SYS_PLL_GPU1_REG_PLLGPU_N_shift                                              (19)
#define SYS_PLL_GPU1_REG_PLLGPU_N_mask                                               (0x00180000)
#define SYS_PLL_GPU1_REG_PLLGPU_N(data)                                              (0x00180000&((data)<<19))
#define SYS_PLL_GPU1_REG_PLLGPU_N_src(data)                                          ((0x00180000&(data))>>19)
#define SYS_PLL_GPU1_get_REG_PLLGPU_N(data)                                          ((0x00180000&(data))>>19)
#define SYS_PLL_GPU1_REG_PLLGPU_M_shift                                              (12)
#define SYS_PLL_GPU1_REG_PLLGPU_M_mask                                               (0x0007F000)
#define SYS_PLL_GPU1_REG_PLLGPU_M(data)                                              (0x0007F000&((data)<<12))
#define SYS_PLL_GPU1_REG_PLLGPU_M_src(data)                                          ((0x0007F000&(data))>>12)
#define SYS_PLL_GPU1_get_REG_PLLGPU_M(data)                                          ((0x0007F000&(data))>>12)
#define SYS_PLL_GPU1_REG_PLLGPU_IP_shift                                             (9)
#define SYS_PLL_GPU1_REG_PLLGPU_IP_mask                                              (0x00000E00)
#define SYS_PLL_GPU1_REG_PLLGPU_IP(data)                                             (0x00000E00&((data)<<9))
#define SYS_PLL_GPU1_REG_PLLGPU_IP_src(data)                                         ((0x00000E00&(data))>>9)
#define SYS_PLL_GPU1_get_REG_PLLGPU_IP(data)                                         ((0x00000E00&(data))>>9)
#define SYS_PLL_GPU1_REG_PLLGPU_K_shift                                              (7)
#define SYS_PLL_GPU1_REG_PLLGPU_K_mask                                               (0x00000180)
#define SYS_PLL_GPU1_REG_PLLGPU_K(data)                                              (0x00000180&((data)<<7))
#define SYS_PLL_GPU1_REG_PLLGPU_K_src(data)                                          ((0x00000180&(data))>>7)
#define SYS_PLL_GPU1_get_REG_PLLGPU_K(data)                                          ((0x00000180&(data))>>7)
#define SYS_PLL_GPU1_REG_PLLGPU_WDMODE_shift                                         (5)
#define SYS_PLL_GPU1_REG_PLLGPU_WDMODE_mask                                          (0x00000060)
#define SYS_PLL_GPU1_REG_PLLGPU_WDMODE(data)                                         (0x00000060&((data)<<5))
#define SYS_PLL_GPU1_REG_PLLGPU_WDMODE_src(data)                                     ((0x00000060&(data))>>5)
#define SYS_PLL_GPU1_get_REG_PLLGPU_WDMODE(data)                                     ((0x00000060&(data))>>5)
#define SYS_PLL_GPU1_REG_PLLGPU_TST_shift                                            (0)
#define SYS_PLL_GPU1_REG_PLLGPU_TST_mask                                             (0x00000001)
#define SYS_PLL_GPU1_REG_PLLGPU_TST(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_GPU1_REG_PLLGPU_TST_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_GPU1_get_REG_PLLGPU_TST(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_GPU2                                                                 0x180001E4
#define SYS_PLL_GPU2_reg_addr                                                        "0xB80001E4"
#define SYS_PLL_GPU2_reg                                                             0xB80001E4
#define set_SYS_PLL_GPU2_reg(data)   (*((volatile unsigned int*) SYS_PLL_GPU2_reg)=data)
#define get_SYS_PLL_GPU2_reg   (*((volatile unsigned int*) SYS_PLL_GPU2_reg))
#define SYS_PLL_GPU2_inst_adr                                                        "0x0079"
#define SYS_PLL_GPU2_inst                                                            0x0079
#define SYS_PLL_GPU2_REG_PLLGPU_RS_shift                                             (8)
#define SYS_PLL_GPU2_REG_PLLGPU_RS_mask                                              (0x00000700)
#define SYS_PLL_GPU2_REG_PLLGPU_RS(data)                                             (0x00000700&((data)<<8))
#define SYS_PLL_GPU2_REG_PLLGPU_RS_src(data)                                         ((0x00000700&(data))>>8)
#define SYS_PLL_GPU2_get_REG_PLLGPU_RS(data)                                         ((0x00000700&(data))>>8)
#define SYS_PLL_GPU2_REG_PLLGPU_CS_shift                                             (4)
#define SYS_PLL_GPU2_REG_PLLGPU_CS_mask                                              (0x00000030)
#define SYS_PLL_GPU2_REG_PLLGPU_CS(data)                                             (0x00000030&((data)<<4))
#define SYS_PLL_GPU2_REG_PLLGPU_CS_src(data)                                         ((0x00000030&(data))>>4)
#define SYS_PLL_GPU2_get_REG_PLLGPU_CS(data)                                         ((0x00000030&(data))>>4)
#define SYS_PLL_GPU2_REG_PLLGPU_OEB_shift                                            (2)
#define SYS_PLL_GPU2_REG_PLLGPU_OEB_mask                                             (0x00000004)
#define SYS_PLL_GPU2_REG_PLLGPU_OEB(data)                                            (0x00000004&((data)<<2))
#define SYS_PLL_GPU2_REG_PLLGPU_OEB_src(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_GPU2_get_REG_PLLGPU_OEB(data)                                        ((0x00000004&(data))>>2)
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB_shift                                           (1)
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB_mask                                            (0x00000002)
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB(data)                                           (0x00000002&((data)<<1))
#define SYS_PLL_GPU2_REG_PLLGPU_RSTB_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_GPU2_get_REG_PLLGPU_RSTB(data)                                       ((0x00000002&(data))>>1)
#define SYS_PLL_GPU2_REG_PLLGPU_POW_shift                                            (0)
#define SYS_PLL_GPU2_REG_PLLGPU_POW_mask                                             (0x00000001)
#define SYS_PLL_GPU2_REG_PLLGPU_POW(data)                                            (0x00000001&((data)<<0))
#define SYS_PLL_GPU2_REG_PLLGPU_POW_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_PLL_GPU2_get_REG_PLLGPU_POW(data)                                        ((0x00000001&(data))>>0)


#define SYS_PLL_GPU3                                                                 0x180001E8
#define SYS_PLL_GPU3_reg_addr                                                        "0xB80001E8"
#define SYS_PLL_GPU3_reg                                                             0xB80001E8
#define set_SYS_PLL_GPU3_reg(data)   (*((volatile unsigned int*) SYS_PLL_GPU3_reg)=data)
#define get_SYS_PLL_GPU3_reg   (*((volatile unsigned int*) SYS_PLL_GPU3_reg))
#define SYS_PLL_GPU3_inst_adr                                                        "0x007A"
#define SYS_PLL_GPU3_inst                                                            0x007A
#define SYS_PLL_GPU3_REG_PLLGPU_N_2_shift                                            (19)
#define SYS_PLL_GPU3_REG_PLLGPU_N_2_mask                                             (0x00180000)
#define SYS_PLL_GPU3_REG_PLLGPU_N_2(data)                                            (0x00180000&((data)<<19))
#define SYS_PLL_GPU3_REG_PLLGPU_N_2_src(data)                                        ((0x00180000&(data))>>19)
#define SYS_PLL_GPU3_get_REG_PLLGPU_N_2(data)                                        ((0x00180000&(data))>>19)
#define SYS_PLL_GPU3_REG_PLLGPU_M_2_shift                                            (12)
#define SYS_PLL_GPU3_REG_PLLGPU_M_2_mask                                             (0x0007F000)
#define SYS_PLL_GPU3_REG_PLLGPU_M_2(data)                                            (0x0007F000&((data)<<12))
#define SYS_PLL_GPU3_REG_PLLGPU_M_2_src(data)                                        ((0x0007F000&(data))>>12)
#define SYS_PLL_GPU3_get_REG_PLLGPU_M_2(data)                                        ((0x0007F000&(data))>>12)
#define SYS_PLL_GPU3_REG_PLLGPU_IP_2_shift                                           (9)
#define SYS_PLL_GPU3_REG_PLLGPU_IP_2_mask                                            (0x00000E00)
#define SYS_PLL_GPU3_REG_PLLGPU_IP_2(data)                                           (0x00000E00&((data)<<9))
#define SYS_PLL_GPU3_REG_PLLGPU_IP_2_src(data)                                       ((0x00000E00&(data))>>9)
#define SYS_PLL_GPU3_get_REG_PLLGPU_IP_2(data)                                       ((0x00000E00&(data))>>9)
#define SYS_PLL_GPU3_REG_PLLGPU_K_2_shift                                            (7)
#define SYS_PLL_GPU3_REG_PLLGPU_K_2_mask                                             (0x00000180)
#define SYS_PLL_GPU3_REG_PLLGPU_K_2(data)                                            (0x00000180&((data)<<7))
#define SYS_PLL_GPU3_REG_PLLGPU_K_2_src(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_GPU3_get_REG_PLLGPU_K_2(data)                                        ((0x00000180&(data))>>7)
#define SYS_PLL_GPU3_REG_PLLGPU_WDMODE_2_shift                                       (5)
#define SYS_PLL_GPU3_REG_PLLGPU_WDMODE_2_mask                                        (0x00000060)
#define SYS_PLL_GPU3_REG_PLLGPU_WDMODE_2(data)                                       (0x00000060&((data)<<5))
#define SYS_PLL_GPU3_REG_PLLGPU_WDMODE_2_src(data)                                   ((0x00000060&(data))>>5)
#define SYS_PLL_GPU3_get_REG_PLLGPU_WDMODE_2(data)                                   ((0x00000060&(data))>>5)
#define SYS_PLL_GPU3_REG_PLLGPU_TST_2_shift                                          (0)
#define SYS_PLL_GPU3_REG_PLLGPU_TST_2_mask                                           (0x00000001)
#define SYS_PLL_GPU3_REG_PLLGPU_TST_2(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_GPU3_REG_PLLGPU_TST_2_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_GPU3_get_REG_PLLGPU_TST_2(data)                                      ((0x00000001&(data))>>0)


#define SYS_PLL_GPU4                                                                 0x180001EC
#define SYS_PLL_GPU4_reg_addr                                                        "0xB80001EC"
#define SYS_PLL_GPU4_reg                                                             0xB80001EC
#define set_SYS_PLL_GPU4_reg(data)   (*((volatile unsigned int*) SYS_PLL_GPU4_reg)=data)
#define get_SYS_PLL_GPU4_reg   (*((volatile unsigned int*) SYS_PLL_GPU4_reg))
#define SYS_PLL_GPU4_inst_adr                                                        "0x007B"
#define SYS_PLL_GPU4_inst                                                            0x007B
#define SYS_PLL_GPU4_REG_PLLGPU_RS_2_shift                                           (8)
#define SYS_PLL_GPU4_REG_PLLGPU_RS_2_mask                                            (0x00000700)
#define SYS_PLL_GPU4_REG_PLLGPU_RS_2(data)                                           (0x00000700&((data)<<8))
#define SYS_PLL_GPU4_REG_PLLGPU_RS_2_src(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_GPU4_get_REG_PLLGPU_RS_2(data)                                       ((0x00000700&(data))>>8)
#define SYS_PLL_GPU4_REG_PLLGPU_CS_2_shift                                           (4)
#define SYS_PLL_GPU4_REG_PLLGPU_CS_2_mask                                            (0x00000030)
#define SYS_PLL_GPU4_REG_PLLGPU_CS_2(data)                                           (0x00000030&((data)<<4))
#define SYS_PLL_GPU4_REG_PLLGPU_CS_2_src(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_GPU4_get_REG_PLLGPU_CS_2(data)                                       ((0x00000030&(data))>>4)
#define SYS_PLL_GPU4_REG_PLLGPU_OEB_2_shift                                          (2)
#define SYS_PLL_GPU4_REG_PLLGPU_OEB_2_mask                                           (0x00000004)
#define SYS_PLL_GPU4_REG_PLLGPU_OEB_2(data)                                          (0x00000004&((data)<<2))
#define SYS_PLL_GPU4_REG_PLLGPU_OEB_2_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_GPU4_get_REG_PLLGPU_OEB_2(data)                                      ((0x00000004&(data))>>2)
#define SYS_PLL_GPU4_REG_PLLGPU_RSTB_2_shift                                         (1)
#define SYS_PLL_GPU4_REG_PLLGPU_RSTB_2_mask                                          (0x00000002)
#define SYS_PLL_GPU4_REG_PLLGPU_RSTB_2(data)                                         (0x00000002&((data)<<1))
#define SYS_PLL_GPU4_REG_PLLGPU_RSTB_2_src(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_GPU4_get_REG_PLLGPU_RSTB_2(data)                                     ((0x00000002&(data))>>1)
#define SYS_PLL_GPU4_REG_PLLGPU_POW_2_shift                                          (0)
#define SYS_PLL_GPU4_REG_PLLGPU_POW_2_mask                                           (0x00000001)
#define SYS_PLL_GPU4_REG_PLLGPU_POW_2(data)                                          (0x00000001&((data)<<0))
#define SYS_PLL_GPU4_REG_PLLGPU_POW_2_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_PLL_GPU4_get_REG_PLLGPU_POW_2(data)                                      ((0x00000001&(data))>>0)


#define SYS_TRNG1                                                                    0x180001FC
#define SYS_TRNG1_reg_addr                                                           "0xB80001FC"
#define SYS_TRNG1_reg                                                                0xB80001FC
#define set_SYS_TRNG1_reg(data)   (*((volatile unsigned int*) SYS_TRNG1_reg)=data)
#define get_SYS_TRNG1_reg   (*((volatile unsigned int*) SYS_TRNG1_reg))
#define SYS_TRNG1_inst_adr                                                           "0x007F"
#define SYS_TRNG1_inst                                                               0x007F
#define SYS_TRNG1_REG_TRNG_RES_shift                                                 (14)
#define SYS_TRNG1_REG_TRNG_RES_mask                                                  (0x0000C000)
#define SYS_TRNG1_REG_TRNG_RES(data)                                                 (0x0000C000&((data)<<14))
#define SYS_TRNG1_REG_TRNG_RES_src(data)                                             ((0x0000C000&(data))>>14)
#define SYS_TRNG1_get_REG_TRNG_RES(data)                                             ((0x0000C000&(data))>>14)
#define SYS_TRNG1_REG_TRNG_GAIN_shift                                                (12)
#define SYS_TRNG1_REG_TRNG_GAIN_mask                                                 (0x00003000)
#define SYS_TRNG1_REG_TRNG_GAIN(data)                                                (0x00003000&((data)<<12))
#define SYS_TRNG1_REG_TRNG_GAIN_src(data)                                            ((0x00003000&(data))>>12)
#define SYS_TRNG1_get_REG_TRNG_GAIN(data)                                            ((0x00003000&(data))>>12)
#define SYS_TRNG1_REG_TRNG_FS_shift                                                  (10)
#define SYS_TRNG1_REG_TRNG_FS_mask                                                   (0x00000C00)
#define SYS_TRNG1_REG_TRNG_FS(data)                                                  (0x00000C00&((data)<<10))
#define SYS_TRNG1_REG_TRNG_FS_src(data)                                              ((0x00000C00&(data))>>10)
#define SYS_TRNG1_get_REG_TRNG_FS(data)                                              ((0x00000C00&(data))>>10)
#define SYS_TRNG1_REG_TRNG_DIV_shift                                                 (8)
#define SYS_TRNG1_REG_TRNG_DIV_mask                                                  (0x00000300)
#define SYS_TRNG1_REG_TRNG_DIV(data)                                                 (0x00000300&((data)<<8))
#define SYS_TRNG1_REG_TRNG_DIV_src(data)                                             ((0x00000300&(data))>>8)
#define SYS_TRNG1_get_REG_TRNG_DIV(data)                                             ((0x00000300&(data))>>8)
#define SYS_TRNG1_REG_TRNG_D_shift                                                   (4)
#define SYS_TRNG1_REG_TRNG_D_mask                                                    (0x000000F0)
#define SYS_TRNG1_REG_TRNG_D(data)                                                   (0x000000F0&((data)<<4))
#define SYS_TRNG1_REG_TRNG_D_src(data)                                               ((0x000000F0&(data))>>4)
#define SYS_TRNG1_get_REG_TRNG_D(data)                                               ((0x000000F0&(data))>>4)
#define SYS_TRNG1_REG_TRNG_TST_shift                                                 (1)
#define SYS_TRNG1_REG_TRNG_TST_mask                                                  (0x00000002)
#define SYS_TRNG1_REG_TRNG_TST(data)                                                 (0x00000002&((data)<<1))
#define SYS_TRNG1_REG_TRNG_TST_src(data)                                             ((0x00000002&(data))>>1)
#define SYS_TRNG1_get_REG_TRNG_TST(data)                                             ((0x00000002&(data))>>1)
#define SYS_TRNG1_REG_TRNG_POW_shift                                                 (0)
#define SYS_TRNG1_REG_TRNG_POW_mask                                                  (0x00000001)
#define SYS_TRNG1_REG_TRNG_POW(data)                                                 (0x00000001&((data)<<0))
#define SYS_TRNG1_REG_TRNG_POW_src(data)                                             ((0x00000001&(data))>>0)
#define SYS_TRNG1_get_REG_TRNG_POW(data)                                             ((0x00000001&(data))>>0)


#define SYS_CRT_DEBUG                                                                0x18000400
#define SYS_CRT_DEBUG_reg_addr                                                       "0xB8000400"
#define SYS_CRT_DEBUG_reg                                                            0xB8000400
#define set_SYS_CRT_DEBUG_reg(data)   (*((volatile unsigned int*) SYS_CRT_DEBUG_reg)=data)
#define get_SYS_CRT_DEBUG_reg   (*((volatile unsigned int*) SYS_CRT_DEBUG_reg))
#define SYS_CRT_DEBUG_inst_adr                                                       "0x0000"
#define SYS_CRT_DEBUG_inst                                                           0x0000
#define SYS_CRT_DEBUG_crt_dbg1_div_sel_shift                                         (30)
#define SYS_CRT_DEBUG_crt_dbg1_div_sel_mask                                          (0xC0000000)
#define SYS_CRT_DEBUG_crt_dbg1_div_sel(data)                                         (0xC0000000&((data)<<30))
#define SYS_CRT_DEBUG_crt_dbg1_div_sel_src(data)                                     ((0xC0000000&(data))>>30)
#define SYS_CRT_DEBUG_get_crt_dbg1_div_sel(data)                                     ((0xC0000000&(data))>>30)
#define SYS_CRT_DEBUG_crt_dbg0_div_sel_shift                                         (28)
#define SYS_CRT_DEBUG_crt_dbg0_div_sel_mask                                          (0x30000000)
#define SYS_CRT_DEBUG_crt_dbg0_div_sel(data)                                         (0x30000000&((data)<<28))
#define SYS_CRT_DEBUG_crt_dbg0_div_sel_src(data)                                     ((0x30000000&(data))>>28)
#define SYS_CRT_DEBUG_get_crt_dbg0_div_sel(data)                                     ((0x30000000&(data))>>28)
#define SYS_CRT_DEBUG_crt_dbg_en_shift                                               (12)
#define SYS_CRT_DEBUG_crt_dbg_en_mask                                                (0x00001000)
#define SYS_CRT_DEBUG_crt_dbg_en(data)                                               (0x00001000&((data)<<12))
#define SYS_CRT_DEBUG_crt_dbg_en_src(data)                                           ((0x00001000&(data))>>12)
#define SYS_CRT_DEBUG_get_crt_dbg_en(data)                                           ((0x00001000&(data))>>12)
#define SYS_CRT_DEBUG_crt_dbg_sel0_shift                                             (6)
#define SYS_CRT_DEBUG_crt_dbg_sel0_mask                                              (0x00000FC0)
#define SYS_CRT_DEBUG_crt_dbg_sel0(data)                                             (0x00000FC0&((data)<<6))
#define SYS_CRT_DEBUG_crt_dbg_sel0_src(data)                                         ((0x00000FC0&(data))>>6)
#define SYS_CRT_DEBUG_get_crt_dbg_sel0(data)                                         ((0x00000FC0&(data))>>6)
#define SYS_CRT_DEBUG_crt_dbg_sel1_shift                                             (0)
#define SYS_CRT_DEBUG_crt_dbg_sel1_mask                                              (0x0000003F)
#define SYS_CRT_DEBUG_crt_dbg_sel1(data)                                             (0x0000003F&((data)<<0))
#define SYS_CRT_DEBUG_crt_dbg_sel1_src(data)                                         ((0x0000003F&(data))>>0)
#define SYS_CRT_DEBUG_get_crt_dbg_sel1(data)                                         ((0x0000003F&(data))>>0)


#define SYS_DUMMY                                                                    0x18000450
#define SYS_DUMMY_reg_addr                                                           "0xB8000450"
#define SYS_DUMMY_reg                                                                0xB8000450
#define set_SYS_DUMMY_reg(data)   (*((volatile unsigned int*) SYS_DUMMY_reg)=data)
#define get_SYS_DUMMY_reg   (*((volatile unsigned int*) SYS_DUMMY_reg))
#define SYS_DUMMY_inst_adr                                                           "0x0014"
#define SYS_DUMMY_inst                                                               0x0014
#define SYS_DUMMY_dummy_reg_shift                                                    (0)
#define SYS_DUMMY_dummy_reg_mask                                                     (0xFFFFFFFF)
#define SYS_DUMMY_dummy_reg(data)                                                    (0xFFFFFFFF&((data)<<0))
#define SYS_DUMMY_dummy_reg_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define SYS_DUMMY_get_dummy_reg(data)                                                ((0xFFFFFFFF&(data))>>0)


#define SYS_CRT_BIST_EN1                                                             0x18000500
#define SYS_CRT_BIST_EN1_reg_addr                                                    "0xB8000500"
#define SYS_CRT_BIST_EN1_reg                                                         0xB8000500
#define set_SYS_CRT_BIST_EN1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BIST_EN1_reg)=data)
#define get_SYS_CRT_BIST_EN1_reg   (*((volatile unsigned int*) SYS_CRT_BIST_EN1_reg))
#define SYS_CRT_BIST_EN1_inst_adr                                                    "0x0040"
#define SYS_CRT_BIST_EN1_inst                                                        0x0040
#define SYS_CRT_BIST_EN1_sb2_rom_bist_en_shift                                       (31)
#define SYS_CRT_BIST_EN1_sb2_rom_bist_en_mask                                        (0x80000000)
#define SYS_CRT_BIST_EN1_sb2_rom_bist_en(data)                                       (0x80000000&((data)<<31))
#define SYS_CRT_BIST_EN1_sb2_rom_bist_en_src(data)                                   ((0x80000000&(data))>>31)
#define SYS_CRT_BIST_EN1_get_sb2_rom_bist_en(data)                                   ((0x80000000&(data))>>31)
#define SYS_CRT_BIST_EN1_sce_bist_mode_shift                                         (13)
#define SYS_CRT_BIST_EN1_sce_bist_mode_mask                                          (0x00002000)
#define SYS_CRT_BIST_EN1_sce_bist_mode(data)                                         (0x00002000&((data)<<13))
#define SYS_CRT_BIST_EN1_sce_bist_mode_src(data)                                     ((0x00002000&(data))>>13)
#define SYS_CRT_BIST_EN1_get_sce_bist_mode(data)                                     ((0x00002000&(data))>>13)
#define SYS_CRT_BIST_EN1_tp_bist_en_shift                                            (12)
#define SYS_CRT_BIST_EN1_tp_bist_en_mask                                             (0x00001000)
#define SYS_CRT_BIST_EN1_tp_bist_en(data)                                            (0x00001000&((data)<<12))
#define SYS_CRT_BIST_EN1_tp_bist_en_src(data)                                        ((0x00001000&(data))>>12)
#define SYS_CRT_BIST_EN1_get_tp_bist_en(data)                                        ((0x00001000&(data))>>12)
#define SYS_CRT_BIST_EN1_hdmi0_bist_en_shift                                         (9)
#define SYS_CRT_BIST_EN1_hdmi0_bist_en_mask                                          (0x00000200)
#define SYS_CRT_BIST_EN1_hdmi0_bist_en(data)                                         (0x00000200&((data)<<9))
#define SYS_CRT_BIST_EN1_hdmi0_bist_en_src(data)                                     ((0x00000200&(data))>>9)
#define SYS_CRT_BIST_EN1_get_hdmi0_bist_en(data)                                     ((0x00000200&(data))>>9)
#define SYS_CRT_BIST_EN1_hdmi1_bist_en_shift                                         (8)
#define SYS_CRT_BIST_EN1_hdmi1_bist_en_mask                                          (0x00000100)
#define SYS_CRT_BIST_EN1_hdmi1_bist_en(data)                                         (0x00000100&((data)<<8))
#define SYS_CRT_BIST_EN1_hdmi1_bist_en_src(data)                                     ((0x00000100&(data))>>8)
#define SYS_CRT_BIST_EN1_get_hdmi1_bist_en(data)                                     ((0x00000100&(data))>>8)
#define SYS_CRT_BIST_EN1_vde_bist_en_shift                                           (7)
#define SYS_CRT_BIST_EN1_vde_bist_en_mask                                            (0x00000080)
#define SYS_CRT_BIST_EN1_vde_bist_en(data)                                           (0x00000080&((data)<<7))
#define SYS_CRT_BIST_EN1_vde_bist_en_src(data)                                       ((0x00000080&(data))>>7)
#define SYS_CRT_BIST_EN1_get_vde_bist_en(data)                                       ((0x00000080&(data))>>7)
#define SYS_CRT_BIST_EN1_dc3_bist_en_shift                                           (6)
#define SYS_CRT_BIST_EN1_dc3_bist_en_mask                                            (0x00000040)
#define SYS_CRT_BIST_EN1_dc3_bist_en(data)                                           (0x00000040&((data)<<6))
#define SYS_CRT_BIST_EN1_dc3_bist_en_src(data)                                       ((0x00000040&(data))>>6)
#define SYS_CRT_BIST_EN1_get_dc3_bist_en(data)                                       ((0x00000040&(data))>>6)
#define SYS_CRT_BIST_EN1_dc2_bist_en_shift                                           (5)
#define SYS_CRT_BIST_EN1_dc2_bist_en_mask                                            (0x00000020)
#define SYS_CRT_BIST_EN1_dc2_bist_en(data)                                           (0x00000020&((data)<<5))
#define SYS_CRT_BIST_EN1_dc2_bist_en_src(data)                                       ((0x00000020&(data))>>5)
#define SYS_CRT_BIST_EN1_get_dc2_bist_en(data)                                       ((0x00000020&(data))>>5)
#define SYS_CRT_BIST_EN1_ae_rom_bist_en_shift                                        (4)
#define SYS_CRT_BIST_EN1_ae_rom_bist_en_mask                                         (0x00000010)
#define SYS_CRT_BIST_EN1_ae_rom_bist_en(data)                                        (0x00000010&((data)<<4))
#define SYS_CRT_BIST_EN1_ae_rom_bist_en_src(data)                                    ((0x00000010&(data))>>4)
#define SYS_CRT_BIST_EN1_get_ae_rom_bist_en(data)                                    ((0x00000010&(data))>>4)
#define SYS_CRT_BIST_EN1_ae_bist_en_shift                                            (3)
#define SYS_CRT_BIST_EN1_ae_bist_en_mask                                             (0x00000008)
#define SYS_CRT_BIST_EN1_ae_bist_en(data)                                            (0x00000008&((data)<<3))
#define SYS_CRT_BIST_EN1_ae_bist_en_src(data)                                        ((0x00000008&(data))>>3)
#define SYS_CRT_BIST_EN1_get_ae_bist_en(data)                                        ((0x00000008&(data))>>3)
#define SYS_CRT_BIST_EN1_cr_nf1_bist_en_shift                                        (2)
#define SYS_CRT_BIST_EN1_cr_nf1_bist_en_mask                                         (0x00000004)
#define SYS_CRT_BIST_EN1_cr_nf1_bist_en(data)                                        (0x00000004&((data)<<2))
#define SYS_CRT_BIST_EN1_cr_nf1_bist_en_src(data)                                    ((0x00000004&(data))>>2)
#define SYS_CRT_BIST_EN1_get_cr_nf1_bist_en(data)                                    ((0x00000004&(data))>>2)
#define SYS_CRT_BIST_EN1_cp_bist_en_shift                                            (1)
#define SYS_CRT_BIST_EN1_cp_bist_en_mask                                             (0x00000002)
#define SYS_CRT_BIST_EN1_cp_bist_en(data)                                            (0x00000002&((data)<<1))
#define SYS_CRT_BIST_EN1_cp_bist_en_src(data)                                        ((0x00000002&(data))>>1)
#define SYS_CRT_BIST_EN1_get_cp_bist_en(data)                                        ((0x00000002&(data))>>1)
#define SYS_CRT_BIST_EN1_write_data_shift                                            (0)
#define SYS_CRT_BIST_EN1_write_data_mask                                             (0x00000001)
#define SYS_CRT_BIST_EN1_write_data(data)                                            (0x00000001&((data)<<0))
#define SYS_CRT_BIST_EN1_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_CRT_BIST_EN1_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define SYS_CRT_BIST_EN2                                                             0x18000504
#define SYS_CRT_BIST_EN2_reg_addr                                                    "0xB8000504"
#define SYS_CRT_BIST_EN2_reg                                                         0xB8000504
#define set_SYS_CRT_BIST_EN2_reg(data)   (*((volatile unsigned int*) SYS_CRT_BIST_EN2_reg)=data)
#define get_SYS_CRT_BIST_EN2_reg   (*((volatile unsigned int*) SYS_CRT_BIST_EN2_reg))
#define SYS_CRT_BIST_EN2_inst_adr                                                    "0x0041"
#define SYS_CRT_BIST_EN2_inst                                                        0x0041
#define SYS_CRT_BIST_EN2_ve17_bist_en_shift                                          (17)
#define SYS_CRT_BIST_EN2_ve17_bist_en_mask                                           (0x00020000)
#define SYS_CRT_BIST_EN2_ve17_bist_en(data)                                          (0x00020000&((data)<<17))
#define SYS_CRT_BIST_EN2_ve17_bist_en_src(data)                                      ((0x00020000&(data))>>17)
#define SYS_CRT_BIST_EN2_get_ve17_bist_en(data)                                      ((0x00020000&(data))>>17)
#define SYS_CRT_BIST_EN2_ve16_bist_en_shift                                          (16)
#define SYS_CRT_BIST_EN2_ve16_bist_en_mask                                           (0x00010000)
#define SYS_CRT_BIST_EN2_ve16_bist_en(data)                                          (0x00010000&((data)<<16))
#define SYS_CRT_BIST_EN2_ve16_bist_en_src(data)                                      ((0x00010000&(data))>>16)
#define SYS_CRT_BIST_EN2_get_ve16_bist_en(data)                                      ((0x00010000&(data))>>16)
#define SYS_CRT_BIST_EN2_ve15_bist_en_shift                                          (15)
#define SYS_CRT_BIST_EN2_ve15_bist_en_mask                                           (0x00008000)
#define SYS_CRT_BIST_EN2_ve15_bist_en(data)                                          (0x00008000&((data)<<15))
#define SYS_CRT_BIST_EN2_ve15_bist_en_src(data)                                      ((0x00008000&(data))>>15)
#define SYS_CRT_BIST_EN2_get_ve15_bist_en(data)                                      ((0x00008000&(data))>>15)
#define SYS_CRT_BIST_EN2_ve14_bist_en_shift                                          (14)
#define SYS_CRT_BIST_EN2_ve14_bist_en_mask                                           (0x00004000)
#define SYS_CRT_BIST_EN2_ve14_bist_en(data)                                          (0x00004000&((data)<<14))
#define SYS_CRT_BIST_EN2_ve14_bist_en_src(data)                                      ((0x00004000&(data))>>14)
#define SYS_CRT_BIST_EN2_get_ve14_bist_en(data)                                      ((0x00004000&(data))>>14)
#define SYS_CRT_BIST_EN2_ve13_bist_en_shift                                          (13)
#define SYS_CRT_BIST_EN2_ve13_bist_en_mask                                           (0x00002000)
#define SYS_CRT_BIST_EN2_ve13_bist_en(data)                                          (0x00002000&((data)<<13))
#define SYS_CRT_BIST_EN2_ve13_bist_en_src(data)                                      ((0x00002000&(data))>>13)
#define SYS_CRT_BIST_EN2_get_ve13_bist_en(data)                                      ((0x00002000&(data))>>13)
#define SYS_CRT_BIST_EN2_ve12_bist_en_shift                                          (12)
#define SYS_CRT_BIST_EN2_ve12_bist_en_mask                                           (0x00001000)
#define SYS_CRT_BIST_EN2_ve12_bist_en(data)                                          (0x00001000&((data)<<12))
#define SYS_CRT_BIST_EN2_ve12_bist_en_src(data)                                      ((0x00001000&(data))>>12)
#define SYS_CRT_BIST_EN2_get_ve12_bist_en(data)                                      ((0x00001000&(data))>>12)
#define SYS_CRT_BIST_EN2_ve11_bist_en_shift                                          (11)
#define SYS_CRT_BIST_EN2_ve11_bist_en_mask                                           (0x00000800)
#define SYS_CRT_BIST_EN2_ve11_bist_en(data)                                          (0x00000800&((data)<<11))
#define SYS_CRT_BIST_EN2_ve11_bist_en_src(data)                                      ((0x00000800&(data))>>11)
#define SYS_CRT_BIST_EN2_get_ve11_bist_en(data)                                      ((0x00000800&(data))>>11)
#define SYS_CRT_BIST_EN2_ve10_bist_en_shift                                          (10)
#define SYS_CRT_BIST_EN2_ve10_bist_en_mask                                           (0x00000400)
#define SYS_CRT_BIST_EN2_ve10_bist_en(data)                                          (0x00000400&((data)<<10))
#define SYS_CRT_BIST_EN2_ve10_bist_en_src(data)                                      ((0x00000400&(data))>>10)
#define SYS_CRT_BIST_EN2_get_ve10_bist_en(data)                                      ((0x00000400&(data))>>10)
#define SYS_CRT_BIST_EN2_ve9_bist_en_shift                                           (9)
#define SYS_CRT_BIST_EN2_ve9_bist_en_mask                                            (0x00000200)
#define SYS_CRT_BIST_EN2_ve9_bist_en(data)                                           (0x00000200&((data)<<9))
#define SYS_CRT_BIST_EN2_ve9_bist_en_src(data)                                       ((0x00000200&(data))>>9)
#define SYS_CRT_BIST_EN2_get_ve9_bist_en(data)                                       ((0x00000200&(data))>>9)
#define SYS_CRT_BIST_EN2_ve8_bist_en_shift                                           (8)
#define SYS_CRT_BIST_EN2_ve8_bist_en_mask                                            (0x00000100)
#define SYS_CRT_BIST_EN2_ve8_bist_en(data)                                           (0x00000100&((data)<<8))
#define SYS_CRT_BIST_EN2_ve8_bist_en_src(data)                                       ((0x00000100&(data))>>8)
#define SYS_CRT_BIST_EN2_get_ve8_bist_en(data)                                       ((0x00000100&(data))>>8)
#define SYS_CRT_BIST_EN2_ve7_bist_en_shift                                           (7)
#define SYS_CRT_BIST_EN2_ve7_bist_en_mask                                            (0x00000080)
#define SYS_CRT_BIST_EN2_ve7_bist_en(data)                                           (0x00000080&((data)<<7))
#define SYS_CRT_BIST_EN2_ve7_bist_en_src(data)                                       ((0x00000080&(data))>>7)
#define SYS_CRT_BIST_EN2_get_ve7_bist_en(data)                                       ((0x00000080&(data))>>7)
#define SYS_CRT_BIST_EN2_ve6_bist_en_shift                                           (6)
#define SYS_CRT_BIST_EN2_ve6_bist_en_mask                                            (0x00000040)
#define SYS_CRT_BIST_EN2_ve6_bist_en(data)                                           (0x00000040&((data)<<6))
#define SYS_CRT_BIST_EN2_ve6_bist_en_src(data)                                       ((0x00000040&(data))>>6)
#define SYS_CRT_BIST_EN2_get_ve6_bist_en(data)                                       ((0x00000040&(data))>>6)
#define SYS_CRT_BIST_EN2_ve5_bist_en_shift                                           (5)
#define SYS_CRT_BIST_EN2_ve5_bist_en_mask                                            (0x00000020)
#define SYS_CRT_BIST_EN2_ve5_bist_en(data)                                           (0x00000020&((data)<<5))
#define SYS_CRT_BIST_EN2_ve5_bist_en_src(data)                                       ((0x00000020&(data))>>5)
#define SYS_CRT_BIST_EN2_get_ve5_bist_en(data)                                       ((0x00000020&(data))>>5)
#define SYS_CRT_BIST_EN2_ve4_bist_en_shift                                           (4)
#define SYS_CRT_BIST_EN2_ve4_bist_en_mask                                            (0x00000010)
#define SYS_CRT_BIST_EN2_ve4_bist_en(data)                                           (0x00000010&((data)<<4))
#define SYS_CRT_BIST_EN2_ve4_bist_en_src(data)                                       ((0x00000010&(data))>>4)
#define SYS_CRT_BIST_EN2_get_ve4_bist_en(data)                                       ((0x00000010&(data))>>4)
#define SYS_CRT_BIST_EN2_ve3_bist_en_shift                                           (3)
#define SYS_CRT_BIST_EN2_ve3_bist_en_mask                                            (0x00000008)
#define SYS_CRT_BIST_EN2_ve3_bist_en(data)                                           (0x00000008&((data)<<3))
#define SYS_CRT_BIST_EN2_ve3_bist_en_src(data)                                       ((0x00000008&(data))>>3)
#define SYS_CRT_BIST_EN2_get_ve3_bist_en(data)                                       ((0x00000008&(data))>>3)
#define SYS_CRT_BIST_EN2_ve2_bist_en_shift                                           (2)
#define SYS_CRT_BIST_EN2_ve2_bist_en_mask                                            (0x00000004)
#define SYS_CRT_BIST_EN2_ve2_bist_en(data)                                           (0x00000004&((data)<<2))
#define SYS_CRT_BIST_EN2_ve2_bist_en_src(data)                                       ((0x00000004&(data))>>2)
#define SYS_CRT_BIST_EN2_get_ve2_bist_en(data)                                       ((0x00000004&(data))>>2)
#define SYS_CRT_BIST_EN2_ve1_bist_en_shift                                           (1)
#define SYS_CRT_BIST_EN2_ve1_bist_en_mask                                            (0x00000002)
#define SYS_CRT_BIST_EN2_ve1_bist_en(data)                                           (0x00000002&((data)<<1))
#define SYS_CRT_BIST_EN2_ve1_bist_en_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_CRT_BIST_EN2_get_ve1_bist_en(data)                                       ((0x00000002&(data))>>1)
#define SYS_CRT_BIST_EN2_write_data_shift                                            (0)
#define SYS_CRT_BIST_EN2_write_data_mask                                             (0x00000001)
#define SYS_CRT_BIST_EN2_write_data(data)                                            (0x00000001&((data)<<0))
#define SYS_CRT_BIST_EN2_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_CRT_BIST_EN2_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define SYS_CRT_BIST_EN3                                                             0x18000508
#define SYS_CRT_BIST_EN3_reg_addr                                                    "0xB8000508"
#define SYS_CRT_BIST_EN3_reg                                                         0xB8000508
#define set_SYS_CRT_BIST_EN3_reg(data)   (*((volatile unsigned int*) SYS_CRT_BIST_EN3_reg)=data)
#define get_SYS_CRT_BIST_EN3_reg   (*((volatile unsigned int*) SYS_CRT_BIST_EN3_reg))
#define SYS_CRT_BIST_EN3_inst_adr                                                    "0x0042"
#define SYS_CRT_BIST_EN3_inst                                                        0x0042
#define SYS_CRT_BIST_EN3_etn2_bist_en_shift                                          (13)
#define SYS_CRT_BIST_EN3_etn2_bist_en_mask                                           (0x00002000)
#define SYS_CRT_BIST_EN3_etn2_bist_en(data)                                          (0x00002000&((data)<<13))
#define SYS_CRT_BIST_EN3_etn2_bist_en_src(data)                                      ((0x00002000&(data))>>13)
#define SYS_CRT_BIST_EN3_get_etn2_bist_en(data)                                      ((0x00002000&(data))>>13)
#define SYS_CRT_BIST_EN3_md_bist_en_shift                                            (10)
#define SYS_CRT_BIST_EN3_md_bist_en_mask                                             (0x00000400)
#define SYS_CRT_BIST_EN3_md_bist_en(data)                                            (0x00000400&((data)<<10))
#define SYS_CRT_BIST_EN3_md_bist_en_src(data)                                        ((0x00000400&(data))>>10)
#define SYS_CRT_BIST_EN3_get_md_bist_en(data)                                        ((0x00000400&(data))>>10)
#define SYS_CRT_BIST_EN3_usb2_bist_en_shift                                          (9)
#define SYS_CRT_BIST_EN3_usb2_bist_en_mask                                           (0x00000200)
#define SYS_CRT_BIST_EN3_usb2_bist_en(data)                                          (0x00000200&((data)<<9))
#define SYS_CRT_BIST_EN3_usb2_bist_en_src(data)                                      ((0x00000200&(data))>>9)
#define SYS_CRT_BIST_EN3_get_usb2_bist_en(data)                                      ((0x00000200&(data))>>9)
#define SYS_CRT_BIST_EN3_usb1_bist_en_shift                                          (8)
#define SYS_CRT_BIST_EN3_usb1_bist_en_mask                                           (0x00000100)
#define SYS_CRT_BIST_EN3_usb1_bist_en(data)                                          (0x00000100&((data)<<8))
#define SYS_CRT_BIST_EN3_usb1_bist_en_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_CRT_BIST_EN3_get_usb1_bist_en(data)                                      ((0x00000100&(data))>>8)
#define SYS_CRT_BIST_EN3_kcpu1_bist_en_shift                                         (5)
#define SYS_CRT_BIST_EN3_kcpu1_bist_en_mask                                          (0x00000020)
#define SYS_CRT_BIST_EN3_kcpu1_bist_en(data)                                         (0x00000020&((data)<<5))
#define SYS_CRT_BIST_EN3_kcpu1_bist_en_src(data)                                     ((0x00000020&(data))>>5)
#define SYS_CRT_BIST_EN3_get_kcpu1_bist_en(data)                                     ((0x00000020&(data))>>5)
#define SYS_CRT_BIST_EN3_vcpu_bist_en_shift                                          (2)
#define SYS_CRT_BIST_EN3_vcpu_bist_en_mask                                           (0x00000004)
#define SYS_CRT_BIST_EN3_vcpu_bist_en(data)                                          (0x00000004&((data)<<2))
#define SYS_CRT_BIST_EN3_vcpu_bist_en_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_CRT_BIST_EN3_get_vcpu_bist_en(data)                                      ((0x00000004&(data))>>2)
#define SYS_CRT_BIST_EN3_acpu_bist_en_shift                                          (1)
#define SYS_CRT_BIST_EN3_acpu_bist_en_mask                                           (0x00000002)
#define SYS_CRT_BIST_EN3_acpu_bist_en(data)                                          (0x00000002&((data)<<1))
#define SYS_CRT_BIST_EN3_acpu_bist_en_src(data)                                      ((0x00000002&(data))>>1)
#define SYS_CRT_BIST_EN3_get_acpu_bist_en(data)                                      ((0x00000002&(data))>>1)
#define SYS_CRT_BIST_EN3_write_data_shift                                            (0)
#define SYS_CRT_BIST_EN3_write_data_mask                                             (0x00000001)
#define SYS_CRT_BIST_EN3_write_data(data)                                            (0x00000001&((data)<<0))
#define SYS_CRT_BIST_EN3_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_CRT_BIST_EN3_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_BIST_EN1                                                         0x18000520
#define SYS_CRT_DRF_BIST_EN1_reg_addr                                                "0xB8000520"
#define SYS_CRT_DRF_BIST_EN1_reg                                                     0xB8000520
#define set_SYS_CRT_DRF_BIST_EN1_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_BIST_EN1_reg)=data)
#define get_SYS_CRT_DRF_BIST_EN1_reg   (*((volatile unsigned int*) SYS_CRT_DRF_BIST_EN1_reg))
#define SYS_CRT_DRF_BIST_EN1_inst_adr                                                "0x0048"
#define SYS_CRT_DRF_BIST_EN1_inst                                                    0x0048
#define SYS_CRT_DRF_BIST_EN1_sce_drf_bist_mode_shift                                 (13)
#define SYS_CRT_DRF_BIST_EN1_sce_drf_bist_mode_mask                                  (0x00002000)
#define SYS_CRT_DRF_BIST_EN1_sce_drf_bist_mode(data)                                 (0x00002000&((data)<<13))
#define SYS_CRT_DRF_BIST_EN1_sce_drf_bist_mode_src(data)                             ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_BIST_EN1_get_sce_drf_bist_mode(data)                             ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_BIST_EN1_tp_drf_bist_en_shift                                    (12)
#define SYS_CRT_DRF_BIST_EN1_tp_drf_bist_en_mask                                     (0x00001000)
#define SYS_CRT_DRF_BIST_EN1_tp_drf_bist_en(data)                                    (0x00001000&((data)<<12))
#define SYS_CRT_DRF_BIST_EN1_tp_drf_bist_en_src(data)                                ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_BIST_EN1_get_tp_drf_bist_en(data)                                ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_BIST_EN1_hdmi0_drf_bist_en_shift                                 (9)
#define SYS_CRT_DRF_BIST_EN1_hdmi0_drf_bist_en_mask                                  (0x00000200)
#define SYS_CRT_DRF_BIST_EN1_hdmi0_drf_bist_en(data)                                 (0x00000200&((data)<<9))
#define SYS_CRT_DRF_BIST_EN1_hdmi0_drf_bist_en_src(data)                             ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_BIST_EN1_get_hdmi0_drf_bist_en(data)                             ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_BIST_EN1_hdmi1_drf_bist_en_shift                                 (8)
#define SYS_CRT_DRF_BIST_EN1_hdmi1_drf_bist_en_mask                                  (0x00000100)
#define SYS_CRT_DRF_BIST_EN1_hdmi1_drf_bist_en(data)                                 (0x00000100&((data)<<8))
#define SYS_CRT_DRF_BIST_EN1_hdmi1_drf_bist_en_src(data)                             ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_BIST_EN1_get_hdmi1_drf_bist_en(data)                             ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_BIST_EN1_vde_drf_bist_en_shift                                   (7)
#define SYS_CRT_DRF_BIST_EN1_vde_drf_bist_en_mask                                    (0x00000080)
#define SYS_CRT_DRF_BIST_EN1_vde_drf_bist_en(data)                                   (0x00000080&((data)<<7))
#define SYS_CRT_DRF_BIST_EN1_vde_drf_bist_en_src(data)                               ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_BIST_EN1_get_vde_drf_bist_en(data)                               ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_BIST_EN1_dc3_drf_bist_en_shift                                   (6)
#define SYS_CRT_DRF_BIST_EN1_dc3_drf_bist_en_mask                                    (0x00000040)
#define SYS_CRT_DRF_BIST_EN1_dc3_drf_bist_en(data)                                   (0x00000040&((data)<<6))
#define SYS_CRT_DRF_BIST_EN1_dc3_drf_bist_en_src(data)                               ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_BIST_EN1_get_dc3_drf_bist_en(data)                               ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_BIST_EN1_dc2_drf_bist_en_shift                                   (5)
#define SYS_CRT_DRF_BIST_EN1_dc2_drf_bist_en_mask                                    (0x00000020)
#define SYS_CRT_DRF_BIST_EN1_dc2_drf_bist_en(data)                                   (0x00000020&((data)<<5))
#define SYS_CRT_DRF_BIST_EN1_dc2_drf_bist_en_src(data)                               ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_BIST_EN1_get_dc2_drf_bist_en(data)                               ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_BIST_EN1_cr_nf1_drf_bist_en_shift                                (2)
#define SYS_CRT_DRF_BIST_EN1_cr_nf1_drf_bist_en_mask                                 (0x00000004)
#define SYS_CRT_DRF_BIST_EN1_cr_nf1_drf_bist_en(data)                                (0x00000004&((data)<<2))
#define SYS_CRT_DRF_BIST_EN1_cr_nf1_drf_bist_en_src(data)                            ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BIST_EN1_get_cr_nf1_drf_bist_en(data)                            ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BIST_EN1_cp_drf_bist_en_shift                                    (1)
#define SYS_CRT_DRF_BIST_EN1_cp_drf_bist_en_mask                                     (0x00000002)
#define SYS_CRT_DRF_BIST_EN1_cp_drf_bist_en(data)                                    (0x00000002&((data)<<1))
#define SYS_CRT_DRF_BIST_EN1_cp_drf_bist_en_src(data)                                ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BIST_EN1_get_cp_drf_bist_en(data)                                ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BIST_EN1_write_data_shift                                        (0)
#define SYS_CRT_DRF_BIST_EN1_write_data_mask                                         (0x00000001)
#define SYS_CRT_DRF_BIST_EN1_write_data(data)                                        (0x00000001&((data)<<0))
#define SYS_CRT_DRF_BIST_EN1_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_BIST_EN1_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_BIST_EN2                                                         0x18000524
#define SYS_CRT_DRF_BIST_EN2_reg_addr                                                "0xB8000524"
#define SYS_CRT_DRF_BIST_EN2_reg                                                     0xB8000524
#define set_SYS_CRT_DRF_BIST_EN2_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_BIST_EN2_reg)=data)
#define get_SYS_CRT_DRF_BIST_EN2_reg   (*((volatile unsigned int*) SYS_CRT_DRF_BIST_EN2_reg))
#define SYS_CRT_DRF_BIST_EN2_inst_adr                                                "0x0049"
#define SYS_CRT_DRF_BIST_EN2_inst                                                    0x0049
#define SYS_CRT_DRF_BIST_EN2_ve17_drf_bist_en_shift                                  (17)
#define SYS_CRT_DRF_BIST_EN2_ve17_drf_bist_en_mask                                   (0x00020000)
#define SYS_CRT_DRF_BIST_EN2_ve17_drf_bist_en(data)                                  (0x00020000&((data)<<17))
#define SYS_CRT_DRF_BIST_EN2_ve17_drf_bist_en_src(data)                              ((0x00020000&(data))>>17)
#define SYS_CRT_DRF_BIST_EN2_get_ve17_drf_bist_en(data)                              ((0x00020000&(data))>>17)
#define SYS_CRT_DRF_BIST_EN2_ve16_drf_bist_en_shift                                  (16)
#define SYS_CRT_DRF_BIST_EN2_ve16_drf_bist_en_mask                                   (0x00010000)
#define SYS_CRT_DRF_BIST_EN2_ve16_drf_bist_en(data)                                  (0x00010000&((data)<<16))
#define SYS_CRT_DRF_BIST_EN2_ve16_drf_bist_en_src(data)                              ((0x00010000&(data))>>16)
#define SYS_CRT_DRF_BIST_EN2_get_ve16_drf_bist_en(data)                              ((0x00010000&(data))>>16)
#define SYS_CRT_DRF_BIST_EN2_ve15_drf_bist_en_shift                                  (15)
#define SYS_CRT_DRF_BIST_EN2_ve15_drf_bist_en_mask                                   (0x00008000)
#define SYS_CRT_DRF_BIST_EN2_ve15_drf_bist_en(data)                                  (0x00008000&((data)<<15))
#define SYS_CRT_DRF_BIST_EN2_ve15_drf_bist_en_src(data)                              ((0x00008000&(data))>>15)
#define SYS_CRT_DRF_BIST_EN2_get_ve15_drf_bist_en(data)                              ((0x00008000&(data))>>15)
#define SYS_CRT_DRF_BIST_EN2_ve14_drf_bist_en_shift                                  (14)
#define SYS_CRT_DRF_BIST_EN2_ve14_drf_bist_en_mask                                   (0x00004000)
#define SYS_CRT_DRF_BIST_EN2_ve14_drf_bist_en(data)                                  (0x00004000&((data)<<14))
#define SYS_CRT_DRF_BIST_EN2_ve14_drf_bist_en_src(data)                              ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_BIST_EN2_get_ve14_drf_bist_en(data)                              ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_BIST_EN2_ve13_drf_bist_en_shift                                  (13)
#define SYS_CRT_DRF_BIST_EN2_ve13_drf_bist_en_mask                                   (0x00002000)
#define SYS_CRT_DRF_BIST_EN2_ve13_drf_bist_en(data)                                  (0x00002000&((data)<<13))
#define SYS_CRT_DRF_BIST_EN2_ve13_drf_bist_en_src(data)                              ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_BIST_EN2_get_ve13_drf_bist_en(data)                              ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_BIST_EN2_ve12_drf_bist_en_shift                                  (12)
#define SYS_CRT_DRF_BIST_EN2_ve12_drf_bist_en_mask                                   (0x00001000)
#define SYS_CRT_DRF_BIST_EN2_ve12_drf_bist_en(data)                                  (0x00001000&((data)<<12))
#define SYS_CRT_DRF_BIST_EN2_ve12_drf_bist_en_src(data)                              ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_BIST_EN2_get_ve12_drf_bist_en(data)                              ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_BIST_EN2_ve11_drf_bist_en_shift                                  (11)
#define SYS_CRT_DRF_BIST_EN2_ve11_drf_bist_en_mask                                   (0x00000800)
#define SYS_CRT_DRF_BIST_EN2_ve11_drf_bist_en(data)                                  (0x00000800&((data)<<11))
#define SYS_CRT_DRF_BIST_EN2_ve11_drf_bist_en_src(data)                              ((0x00000800&(data))>>11)
#define SYS_CRT_DRF_BIST_EN2_get_ve11_drf_bist_en(data)                              ((0x00000800&(data))>>11)
#define SYS_CRT_DRF_BIST_EN2_ve10_drf_bist_en_shift                                  (10)
#define SYS_CRT_DRF_BIST_EN2_ve10_drf_bist_en_mask                                   (0x00000400)
#define SYS_CRT_DRF_BIST_EN2_ve10_drf_bist_en(data)                                  (0x00000400&((data)<<10))
#define SYS_CRT_DRF_BIST_EN2_ve10_drf_bist_en_src(data)                              ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_BIST_EN2_get_ve10_drf_bist_en(data)                              ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_BIST_EN2_ve9_drf_bist_en_shift                                   (9)
#define SYS_CRT_DRF_BIST_EN2_ve9_drf_bist_en_mask                                    (0x00000200)
#define SYS_CRT_DRF_BIST_EN2_ve9_drf_bist_en(data)                                   (0x00000200&((data)<<9))
#define SYS_CRT_DRF_BIST_EN2_ve9_drf_bist_en_src(data)                               ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_BIST_EN2_get_ve9_drf_bist_en(data)                               ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_BIST_EN2_ve8_drf_bist_en_shift                                   (8)
#define SYS_CRT_DRF_BIST_EN2_ve8_drf_bist_en_mask                                    (0x00000100)
#define SYS_CRT_DRF_BIST_EN2_ve8_drf_bist_en(data)                                   (0x00000100&((data)<<8))
#define SYS_CRT_DRF_BIST_EN2_ve8_drf_bist_en_src(data)                               ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_BIST_EN2_get_ve8_drf_bist_en(data)                               ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_BIST_EN2_ve7_drf_bist_en_shift                                   (7)
#define SYS_CRT_DRF_BIST_EN2_ve7_drf_bist_en_mask                                    (0x00000080)
#define SYS_CRT_DRF_BIST_EN2_ve7_drf_bist_en(data)                                   (0x00000080&((data)<<7))
#define SYS_CRT_DRF_BIST_EN2_ve7_drf_bist_en_src(data)                               ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_BIST_EN2_get_ve7_drf_bist_en(data)                               ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_BIST_EN2_ve6_drf_bist_en_shift                                   (6)
#define SYS_CRT_DRF_BIST_EN2_ve6_drf_bist_en_mask                                    (0x00000040)
#define SYS_CRT_DRF_BIST_EN2_ve6_drf_bist_en(data)                                   (0x00000040&((data)<<6))
#define SYS_CRT_DRF_BIST_EN2_ve6_drf_bist_en_src(data)                               ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_BIST_EN2_get_ve6_drf_bist_en(data)                               ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_BIST_EN2_ve5_drf_bist_en_shift                                   (5)
#define SYS_CRT_DRF_BIST_EN2_ve5_drf_bist_en_mask                                    (0x00000020)
#define SYS_CRT_DRF_BIST_EN2_ve5_drf_bist_en(data)                                   (0x00000020&((data)<<5))
#define SYS_CRT_DRF_BIST_EN2_ve5_drf_bist_en_src(data)                               ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_BIST_EN2_get_ve5_drf_bist_en(data)                               ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_BIST_EN2_ve4_drf_bist_en_shift                                   (4)
#define SYS_CRT_DRF_BIST_EN2_ve4_drf_bist_en_mask                                    (0x00000010)
#define SYS_CRT_DRF_BIST_EN2_ve4_drf_bist_en(data)                                   (0x00000010&((data)<<4))
#define SYS_CRT_DRF_BIST_EN2_ve4_drf_bist_en_src(data)                               ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_BIST_EN2_get_ve4_drf_bist_en(data)                               ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_BIST_EN2_ve3_drf_bist_en_shift                                   (3)
#define SYS_CRT_DRF_BIST_EN2_ve3_drf_bist_en_mask                                    (0x00000008)
#define SYS_CRT_DRF_BIST_EN2_ve3_drf_bist_en(data)                                   (0x00000008&((data)<<3))
#define SYS_CRT_DRF_BIST_EN2_ve3_drf_bist_en_src(data)                               ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_BIST_EN2_get_ve3_drf_bist_en(data)                               ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_BIST_EN2_ve2_drf_bist_en_shift                                   (2)
#define SYS_CRT_DRF_BIST_EN2_ve2_drf_bist_en_mask                                    (0x00000004)
#define SYS_CRT_DRF_BIST_EN2_ve2_drf_bist_en(data)                                   (0x00000004&((data)<<2))
#define SYS_CRT_DRF_BIST_EN2_ve2_drf_bist_en_src(data)                               ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BIST_EN2_get_ve2_drf_bist_en(data)                               ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BIST_EN2_ve1_drf_bist_en_shift                                   (1)
#define SYS_CRT_DRF_BIST_EN2_ve1_drf_bist_en_mask                                    (0x00000002)
#define SYS_CRT_DRF_BIST_EN2_ve1_drf_bist_en(data)                                   (0x00000002&((data)<<1))
#define SYS_CRT_DRF_BIST_EN2_ve1_drf_bist_en_src(data)                               ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BIST_EN2_get_ve1_drf_bist_en(data)                               ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BIST_EN2_write_data_shift                                        (0)
#define SYS_CRT_DRF_BIST_EN2_write_data_mask                                         (0x00000001)
#define SYS_CRT_DRF_BIST_EN2_write_data(data)                                        (0x00000001&((data)<<0))
#define SYS_CRT_DRF_BIST_EN2_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_BIST_EN2_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_BIST_EN3                                                         0x18000528
#define SYS_CRT_DRF_BIST_EN3_reg_addr                                                "0xB8000528"
#define SYS_CRT_DRF_BIST_EN3_reg                                                     0xB8000528
#define set_SYS_CRT_DRF_BIST_EN3_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_BIST_EN3_reg)=data)
#define get_SYS_CRT_DRF_BIST_EN3_reg   (*((volatile unsigned int*) SYS_CRT_DRF_BIST_EN3_reg))
#define SYS_CRT_DRF_BIST_EN3_inst_adr                                                "0x004A"
#define SYS_CRT_DRF_BIST_EN3_inst                                                    0x004A
#define SYS_CRT_DRF_BIST_EN3_ae_drf_bist_en_shift                                    (14)
#define SYS_CRT_DRF_BIST_EN3_ae_drf_bist_en_mask                                     (0x00004000)
#define SYS_CRT_DRF_BIST_EN3_ae_drf_bist_en(data)                                    (0x00004000&((data)<<14))
#define SYS_CRT_DRF_BIST_EN3_ae_drf_bist_en_src(data)                                ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_BIST_EN3_get_ae_drf_bist_en(data)                                ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_BIST_EN3_etn2_drf_bist_en_shift                                  (13)
#define SYS_CRT_DRF_BIST_EN3_etn2_drf_bist_en_mask                                   (0x00002000)
#define SYS_CRT_DRF_BIST_EN3_etn2_drf_bist_en(data)                                  (0x00002000&((data)<<13))
#define SYS_CRT_DRF_BIST_EN3_etn2_drf_bist_en_src(data)                              ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_BIST_EN3_get_etn2_drf_bist_en(data)                              ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_BIST_EN3_md_drf_bist_en_shift                                    (10)
#define SYS_CRT_DRF_BIST_EN3_md_drf_bist_en_mask                                     (0x00000400)
#define SYS_CRT_DRF_BIST_EN3_md_drf_bist_en(data)                                    (0x00000400&((data)<<10))
#define SYS_CRT_DRF_BIST_EN3_md_drf_bist_en_src(data)                                ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_BIST_EN3_get_md_drf_bist_en(data)                                ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_BIST_EN3_usb2_drf_bist_en_shift                                  (9)
#define SYS_CRT_DRF_BIST_EN3_usb2_drf_bist_en_mask                                   (0x00000200)
#define SYS_CRT_DRF_BIST_EN3_usb2_drf_bist_en(data)                                  (0x00000200&((data)<<9))
#define SYS_CRT_DRF_BIST_EN3_usb2_drf_bist_en_src(data)                              ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_BIST_EN3_get_usb2_drf_bist_en(data)                              ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_BIST_EN3_usb1_drf_bist_en_shift                                  (8)
#define SYS_CRT_DRF_BIST_EN3_usb1_drf_bist_en_mask                                   (0x00000100)
#define SYS_CRT_DRF_BIST_EN3_usb1_drf_bist_en(data)                                  (0x00000100&((data)<<8))
#define SYS_CRT_DRF_BIST_EN3_usb1_drf_bist_en_src(data)                              ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_BIST_EN3_get_usb1_drf_bist_en(data)                              ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_BIST_EN3_kcpu1_drf_bist_en_shift                                 (5)
#define SYS_CRT_DRF_BIST_EN3_kcpu1_drf_bist_en_mask                                  (0x00000020)
#define SYS_CRT_DRF_BIST_EN3_kcpu1_drf_bist_en(data)                                 (0x00000020&((data)<<5))
#define SYS_CRT_DRF_BIST_EN3_kcpu1_drf_bist_en_src(data)                             ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_BIST_EN3_get_kcpu1_drf_bist_en(data)                             ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_BIST_EN3_vcpu_drf_bist_en_shift                                  (2)
#define SYS_CRT_DRF_BIST_EN3_vcpu_drf_bist_en_mask                                   (0x00000004)
#define SYS_CRT_DRF_BIST_EN3_vcpu_drf_bist_en(data)                                  (0x00000004&((data)<<2))
#define SYS_CRT_DRF_BIST_EN3_vcpu_drf_bist_en_src(data)                              ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BIST_EN3_get_vcpu_drf_bist_en(data)                              ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BIST_EN3_acpu_drf_bist_en_shift                                  (1)
#define SYS_CRT_DRF_BIST_EN3_acpu_drf_bist_en_mask                                   (0x00000002)
#define SYS_CRT_DRF_BIST_EN3_acpu_drf_bist_en(data)                                  (0x00000002&((data)<<1))
#define SYS_CRT_DRF_BIST_EN3_acpu_drf_bist_en_src(data)                              ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BIST_EN3_get_acpu_drf_bist_en(data)                              ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BIST_EN3_write_data_shift                                        (0)
#define SYS_CRT_DRF_BIST_EN3_write_data_mask                                         (0x00000001)
#define SYS_CRT_DRF_BIST_EN3_write_data(data)                                        (0x00000001&((data)<<0))
#define SYS_CRT_DRF_BIST_EN3_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_BIST_EN3_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_TEST_RESUME1                                                     0x18000540
#define SYS_CRT_DRF_TEST_RESUME1_reg_addr                                            "0xB8000540"
#define SYS_CRT_DRF_TEST_RESUME1_reg                                                 0xB8000540
#define set_SYS_CRT_DRF_TEST_RESUME1_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_TEST_RESUME1_reg)=data)
#define get_SYS_CRT_DRF_TEST_RESUME1_reg   (*((volatile unsigned int*) SYS_CRT_DRF_TEST_RESUME1_reg))
#define SYS_CRT_DRF_TEST_RESUME1_inst_adr                                            "0x0050"
#define SYS_CRT_DRF_TEST_RESUME1_inst                                                0x0050
#define SYS_CRT_DRF_TEST_RESUME1_sce_drf_test_resume_shift                           (13)
#define SYS_CRT_DRF_TEST_RESUME1_sce_drf_test_resume_mask                            (0x00002000)
#define SYS_CRT_DRF_TEST_RESUME1_sce_drf_test_resume(data)                           (0x00002000&((data)<<13))
#define SYS_CRT_DRF_TEST_RESUME1_sce_drf_test_resume_src(data)                       ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_TEST_RESUME1_get_sce_drf_test_resume(data)                       ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_TEST_RESUME1_tp_drf_test_resume_shift                            (12)
#define SYS_CRT_DRF_TEST_RESUME1_tp_drf_test_resume_mask                             (0x00001000)
#define SYS_CRT_DRF_TEST_RESUME1_tp_drf_test_resume(data)                            (0x00001000&((data)<<12))
#define SYS_CRT_DRF_TEST_RESUME1_tp_drf_test_resume_src(data)                        ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_TEST_RESUME1_get_tp_drf_test_resume(data)                        ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_TEST_RESUME1_hdmi0_drf_test_resume_shift                         (9)
#define SYS_CRT_DRF_TEST_RESUME1_hdmi0_drf_test_resume_mask                          (0x00000200)
#define SYS_CRT_DRF_TEST_RESUME1_hdmi0_drf_test_resume(data)                         (0x00000200&((data)<<9))
#define SYS_CRT_DRF_TEST_RESUME1_hdmi0_drf_test_resume_src(data)                     ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_TEST_RESUME1_get_hdmi0_drf_test_resume(data)                     ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_TEST_RESUME1_hdmi1_drf_test_resume_shift                         (8)
#define SYS_CRT_DRF_TEST_RESUME1_hdmi1_drf_test_resume_mask                          (0x00000100)
#define SYS_CRT_DRF_TEST_RESUME1_hdmi1_drf_test_resume(data)                         (0x00000100&((data)<<8))
#define SYS_CRT_DRF_TEST_RESUME1_hdmi1_drf_test_resume_src(data)                     ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_TEST_RESUME1_get_hdmi1_drf_test_resume(data)                     ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_TEST_RESUME1_vde_drf_test_resume_shift                           (7)
#define SYS_CRT_DRF_TEST_RESUME1_vde_drf_test_resume_mask                            (0x00000080)
#define SYS_CRT_DRF_TEST_RESUME1_vde_drf_test_resume(data)                           (0x00000080&((data)<<7))
#define SYS_CRT_DRF_TEST_RESUME1_vde_drf_test_resume_src(data)                       ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_TEST_RESUME1_get_vde_drf_test_resume(data)                       ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_TEST_RESUME1_dc3_drf_test_resume_shift                           (6)
#define SYS_CRT_DRF_TEST_RESUME1_dc3_drf_test_resume_mask                            (0x00000040)
#define SYS_CRT_DRF_TEST_RESUME1_dc3_drf_test_resume(data)                           (0x00000040&((data)<<6))
#define SYS_CRT_DRF_TEST_RESUME1_dc3_drf_test_resume_src(data)                       ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_TEST_RESUME1_get_dc3_drf_test_resume(data)                       ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_TEST_RESUME1_dc2_drf_test_resume_shift                           (5)
#define SYS_CRT_DRF_TEST_RESUME1_dc2_drf_test_resume_mask                            (0x00000020)
#define SYS_CRT_DRF_TEST_RESUME1_dc2_drf_test_resume(data)                           (0x00000020&((data)<<5))
#define SYS_CRT_DRF_TEST_RESUME1_dc2_drf_test_resume_src(data)                       ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_TEST_RESUME1_get_dc2_drf_test_resume(data)                       ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_TEST_RESUME1_cr_nf1_drf_test_resume_shift                        (2)
#define SYS_CRT_DRF_TEST_RESUME1_cr_nf1_drf_test_resume_mask                         (0x00000004)
#define SYS_CRT_DRF_TEST_RESUME1_cr_nf1_drf_test_resume(data)                        (0x00000004&((data)<<2))
#define SYS_CRT_DRF_TEST_RESUME1_cr_nf1_drf_test_resume_src(data)                    ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_TEST_RESUME1_get_cr_nf1_drf_test_resume(data)                    ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_TEST_RESUME1_cp_drf_test_resume_shift                            (1)
#define SYS_CRT_DRF_TEST_RESUME1_cp_drf_test_resume_mask                             (0x00000002)
#define SYS_CRT_DRF_TEST_RESUME1_cp_drf_test_resume(data)                            (0x00000002&((data)<<1))
#define SYS_CRT_DRF_TEST_RESUME1_cp_drf_test_resume_src(data)                        ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_TEST_RESUME1_get_cp_drf_test_resume(data)                        ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_TEST_RESUME1_write_data_shift                                    (0)
#define SYS_CRT_DRF_TEST_RESUME1_write_data_mask                                     (0x00000001)
#define SYS_CRT_DRF_TEST_RESUME1_write_data(data)                                    (0x00000001&((data)<<0))
#define SYS_CRT_DRF_TEST_RESUME1_write_data_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_TEST_RESUME1_get_write_data(data)                                ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_TEST_RESUME2                                                     0x18000544
#define SYS_CRT_DRF_TEST_RESUME2_reg_addr                                            "0xB8000544"
#define SYS_CRT_DRF_TEST_RESUME2_reg                                                 0xB8000544
#define set_SYS_CRT_DRF_TEST_RESUME2_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_TEST_RESUME2_reg)=data)
#define get_SYS_CRT_DRF_TEST_RESUME2_reg   (*((volatile unsigned int*) SYS_CRT_DRF_TEST_RESUME2_reg))
#define SYS_CRT_DRF_TEST_RESUME2_inst_adr                                            "0x0051"
#define SYS_CRT_DRF_TEST_RESUME2_inst                                                0x0051
#define SYS_CRT_DRF_TEST_RESUME2_ve17_drf_test_resume_shift                          (17)
#define SYS_CRT_DRF_TEST_RESUME2_ve17_drf_test_resume_mask                           (0x00020000)
#define SYS_CRT_DRF_TEST_RESUME2_ve17_drf_test_resume(data)                          (0x00020000&((data)<<17))
#define SYS_CRT_DRF_TEST_RESUME2_ve17_drf_test_resume_src(data)                      ((0x00020000&(data))>>17)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve17_drf_test_resume(data)                      ((0x00020000&(data))>>17)
#define SYS_CRT_DRF_TEST_RESUME2_ve16_drf_test_resume_shift                          (16)
#define SYS_CRT_DRF_TEST_RESUME2_ve16_drf_test_resume_mask                           (0x00010000)
#define SYS_CRT_DRF_TEST_RESUME2_ve16_drf_test_resume(data)                          (0x00010000&((data)<<16))
#define SYS_CRT_DRF_TEST_RESUME2_ve16_drf_test_resume_src(data)                      ((0x00010000&(data))>>16)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve16_drf_test_resume(data)                      ((0x00010000&(data))>>16)
#define SYS_CRT_DRF_TEST_RESUME2_ve15_drf_test_resume_shift                          (15)
#define SYS_CRT_DRF_TEST_RESUME2_ve15_drf_test_resume_mask                           (0x00008000)
#define SYS_CRT_DRF_TEST_RESUME2_ve15_drf_test_resume(data)                          (0x00008000&((data)<<15))
#define SYS_CRT_DRF_TEST_RESUME2_ve15_drf_test_resume_src(data)                      ((0x00008000&(data))>>15)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve15_drf_test_resume(data)                      ((0x00008000&(data))>>15)
#define SYS_CRT_DRF_TEST_RESUME2_ve14_drf_test_resume_shift                          (14)
#define SYS_CRT_DRF_TEST_RESUME2_ve14_drf_test_resume_mask                           (0x00004000)
#define SYS_CRT_DRF_TEST_RESUME2_ve14_drf_test_resume(data)                          (0x00004000&((data)<<14))
#define SYS_CRT_DRF_TEST_RESUME2_ve14_drf_test_resume_src(data)                      ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve14_drf_test_resume(data)                      ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_TEST_RESUME2_ve13_drf_test_resume_shift                          (13)
#define SYS_CRT_DRF_TEST_RESUME2_ve13_drf_test_resume_mask                           (0x00002000)
#define SYS_CRT_DRF_TEST_RESUME2_ve13_drf_test_resume(data)                          (0x00002000&((data)<<13))
#define SYS_CRT_DRF_TEST_RESUME2_ve13_drf_test_resume_src(data)                      ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve13_drf_test_resume(data)                      ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_TEST_RESUME2_ve12_drf_test_resume_shift                          (12)
#define SYS_CRT_DRF_TEST_RESUME2_ve12_drf_test_resume_mask                           (0x00001000)
#define SYS_CRT_DRF_TEST_RESUME2_ve12_drf_test_resume(data)                          (0x00001000&((data)<<12))
#define SYS_CRT_DRF_TEST_RESUME2_ve12_drf_test_resume_src(data)                      ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve12_drf_test_resume(data)                      ((0x00001000&(data))>>12)
#define SYS_CRT_DRF_TEST_RESUME2_ve11_drf_test_resume_shift                          (11)
#define SYS_CRT_DRF_TEST_RESUME2_ve11_drf_test_resume_mask                           (0x00000800)
#define SYS_CRT_DRF_TEST_RESUME2_ve11_drf_test_resume(data)                          (0x00000800&((data)<<11))
#define SYS_CRT_DRF_TEST_RESUME2_ve11_drf_test_resume_src(data)                      ((0x00000800&(data))>>11)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve11_drf_test_resume(data)                      ((0x00000800&(data))>>11)
#define SYS_CRT_DRF_TEST_RESUME2_ve10_drf_test_resume_shift                          (10)
#define SYS_CRT_DRF_TEST_RESUME2_ve10_drf_test_resume_mask                           (0x00000400)
#define SYS_CRT_DRF_TEST_RESUME2_ve10_drf_test_resume(data)                          (0x00000400&((data)<<10))
#define SYS_CRT_DRF_TEST_RESUME2_ve10_drf_test_resume_src(data)                      ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve10_drf_test_resume(data)                      ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_TEST_RESUME2_ve9_drf_test_resume_shift                           (9)
#define SYS_CRT_DRF_TEST_RESUME2_ve9_drf_test_resume_mask                            (0x00000200)
#define SYS_CRT_DRF_TEST_RESUME2_ve9_drf_test_resume(data)                           (0x00000200&((data)<<9))
#define SYS_CRT_DRF_TEST_RESUME2_ve9_drf_test_resume_src(data)                       ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve9_drf_test_resume(data)                       ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_TEST_RESUME2_ve8_drf_test_resume_shift                           (8)
#define SYS_CRT_DRF_TEST_RESUME2_ve8_drf_test_resume_mask                            (0x00000100)
#define SYS_CRT_DRF_TEST_RESUME2_ve8_drf_test_resume(data)                           (0x00000100&((data)<<8))
#define SYS_CRT_DRF_TEST_RESUME2_ve8_drf_test_resume_src(data)                       ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve8_drf_test_resume(data)                       ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_TEST_RESUME2_ve7_drf_test_resume_shift                           (7)
#define SYS_CRT_DRF_TEST_RESUME2_ve7_drf_test_resume_mask                            (0x00000080)
#define SYS_CRT_DRF_TEST_RESUME2_ve7_drf_test_resume(data)                           (0x00000080&((data)<<7))
#define SYS_CRT_DRF_TEST_RESUME2_ve7_drf_test_resume_src(data)                       ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve7_drf_test_resume(data)                       ((0x00000080&(data))>>7)
#define SYS_CRT_DRF_TEST_RESUME2_ve6_drf_test_resume_shift                           (6)
#define SYS_CRT_DRF_TEST_RESUME2_ve6_drf_test_resume_mask                            (0x00000040)
#define SYS_CRT_DRF_TEST_RESUME2_ve6_drf_test_resume(data)                           (0x00000040&((data)<<6))
#define SYS_CRT_DRF_TEST_RESUME2_ve6_drf_test_resume_src(data)                       ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve6_drf_test_resume(data)                       ((0x00000040&(data))>>6)
#define SYS_CRT_DRF_TEST_RESUME2_ve5_drf_test_resume_shift                           (5)
#define SYS_CRT_DRF_TEST_RESUME2_ve5_drf_test_resume_mask                            (0x00000020)
#define SYS_CRT_DRF_TEST_RESUME2_ve5_drf_test_resume(data)                           (0x00000020&((data)<<5))
#define SYS_CRT_DRF_TEST_RESUME2_ve5_drf_test_resume_src(data)                       ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve5_drf_test_resume(data)                       ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_TEST_RESUME2_ve4_drf_test_resume_shift                           (4)
#define SYS_CRT_DRF_TEST_RESUME2_ve4_drf_test_resume_mask                            (0x00000010)
#define SYS_CRT_DRF_TEST_RESUME2_ve4_drf_test_resume(data)                           (0x00000010&((data)<<4))
#define SYS_CRT_DRF_TEST_RESUME2_ve4_drf_test_resume_src(data)                       ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve4_drf_test_resume(data)                       ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_TEST_RESUME2_ve3_drf_test_resume_shift                           (3)
#define SYS_CRT_DRF_TEST_RESUME2_ve3_drf_test_resume_mask                            (0x00000008)
#define SYS_CRT_DRF_TEST_RESUME2_ve3_drf_test_resume(data)                           (0x00000008&((data)<<3))
#define SYS_CRT_DRF_TEST_RESUME2_ve3_drf_test_resume_src(data)                       ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve3_drf_test_resume(data)                       ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_TEST_RESUME2_ve2_drf_test_resume_shift                           (2)
#define SYS_CRT_DRF_TEST_RESUME2_ve2_drf_test_resume_mask                            (0x00000004)
#define SYS_CRT_DRF_TEST_RESUME2_ve2_drf_test_resume(data)                           (0x00000004&((data)<<2))
#define SYS_CRT_DRF_TEST_RESUME2_ve2_drf_test_resume_src(data)                       ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve2_drf_test_resume(data)                       ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_TEST_RESUME2_ve1_drf_test_resume_shift                           (1)
#define SYS_CRT_DRF_TEST_RESUME2_ve1_drf_test_resume_mask                            (0x00000002)
#define SYS_CRT_DRF_TEST_RESUME2_ve1_drf_test_resume(data)                           (0x00000002&((data)<<1))
#define SYS_CRT_DRF_TEST_RESUME2_ve1_drf_test_resume_src(data)                       ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_TEST_RESUME2_get_ve1_drf_test_resume(data)                       ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_TEST_RESUME2_write_data_shift                                    (0)
#define SYS_CRT_DRF_TEST_RESUME2_write_data_mask                                     (0x00000001)
#define SYS_CRT_DRF_TEST_RESUME2_write_data(data)                                    (0x00000001&((data)<<0))
#define SYS_CRT_DRF_TEST_RESUME2_write_data_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_TEST_RESUME2_get_write_data(data)                                ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_TEST_RESUME3                                                     0x18000548
#define SYS_CRT_DRF_TEST_RESUME3_reg_addr                                            "0xB8000548"
#define SYS_CRT_DRF_TEST_RESUME3_reg                                                 0xB8000548
#define set_SYS_CRT_DRF_TEST_RESUME3_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_TEST_RESUME3_reg)=data)
#define get_SYS_CRT_DRF_TEST_RESUME3_reg   (*((volatile unsigned int*) SYS_CRT_DRF_TEST_RESUME3_reg))
#define SYS_CRT_DRF_TEST_RESUME3_inst_adr                                            "0x0052"
#define SYS_CRT_DRF_TEST_RESUME3_inst                                                0x0052
#define SYS_CRT_DRF_TEST_RESUME3_ae_drf_test_resume_shift                            (14)
#define SYS_CRT_DRF_TEST_RESUME3_ae_drf_test_resume_mask                             (0x00004000)
#define SYS_CRT_DRF_TEST_RESUME3_ae_drf_test_resume(data)                            (0x00004000&((data)<<14))
#define SYS_CRT_DRF_TEST_RESUME3_ae_drf_test_resume_src(data)                        ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_TEST_RESUME3_get_ae_drf_test_resume(data)                        ((0x00004000&(data))>>14)
#define SYS_CRT_DRF_TEST_RESUME3_etn2_drf_test_resume_shift                          (13)
#define SYS_CRT_DRF_TEST_RESUME3_etn2_drf_test_resume_mask                           (0x00002000)
#define SYS_CRT_DRF_TEST_RESUME3_etn2_drf_test_resume(data)                          (0x00002000&((data)<<13))
#define SYS_CRT_DRF_TEST_RESUME3_etn2_drf_test_resume_src(data)                      ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_TEST_RESUME3_get_etn2_drf_test_resume(data)                      ((0x00002000&(data))>>13)
#define SYS_CRT_DRF_TEST_RESUME3_md_drf_test_resume_shift                            (10)
#define SYS_CRT_DRF_TEST_RESUME3_md_drf_test_resume_mask                             (0x00000400)
#define SYS_CRT_DRF_TEST_RESUME3_md_drf_test_resume(data)                            (0x00000400&((data)<<10))
#define SYS_CRT_DRF_TEST_RESUME3_md_drf_test_resume_src(data)                        ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_TEST_RESUME3_get_md_drf_test_resume(data)                        ((0x00000400&(data))>>10)
#define SYS_CRT_DRF_TEST_RESUME3_usb2_drf_test_resume_shift                          (9)
#define SYS_CRT_DRF_TEST_RESUME3_usb2_drf_test_resume_mask                           (0x00000200)
#define SYS_CRT_DRF_TEST_RESUME3_usb2_drf_test_resume(data)                          (0x00000200&((data)<<9))
#define SYS_CRT_DRF_TEST_RESUME3_usb2_drf_test_resume_src(data)                      ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_TEST_RESUME3_get_usb2_drf_test_resume(data)                      ((0x00000200&(data))>>9)
#define SYS_CRT_DRF_TEST_RESUME3_usb1_drf_test_resume_shift                          (8)
#define SYS_CRT_DRF_TEST_RESUME3_usb1_drf_test_resume_mask                           (0x00000100)
#define SYS_CRT_DRF_TEST_RESUME3_usb1_drf_test_resume(data)                          (0x00000100&((data)<<8))
#define SYS_CRT_DRF_TEST_RESUME3_usb1_drf_test_resume_src(data)                      ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_TEST_RESUME3_get_usb1_drf_test_resume(data)                      ((0x00000100&(data))>>8)
#define SYS_CRT_DRF_TEST_RESUME3_kcpu1_drf_test_resume_shift                         (5)
#define SYS_CRT_DRF_TEST_RESUME3_kcpu1_drf_test_resume_mask                          (0x00000020)
#define SYS_CRT_DRF_TEST_RESUME3_kcpu1_drf_test_resume(data)                         (0x00000020&((data)<<5))
#define SYS_CRT_DRF_TEST_RESUME3_kcpu1_drf_test_resume_src(data)                     ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_TEST_RESUME3_get_kcpu1_drf_test_resume(data)                     ((0x00000020&(data))>>5)
#define SYS_CRT_DRF_TEST_RESUME3_vcpu_drf_test_resume_shift                          (2)
#define SYS_CRT_DRF_TEST_RESUME3_vcpu_drf_test_resume_mask                           (0x00000004)
#define SYS_CRT_DRF_TEST_RESUME3_vcpu_drf_test_resume(data)                          (0x00000004&((data)<<2))
#define SYS_CRT_DRF_TEST_RESUME3_vcpu_drf_test_resume_src(data)                      ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_TEST_RESUME3_get_vcpu_drf_test_resume(data)                      ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_TEST_RESUME3_acpu_drf_test_resume_shift                          (1)
#define SYS_CRT_DRF_TEST_RESUME3_acpu_drf_test_resume_mask                           (0x00000002)
#define SYS_CRT_DRF_TEST_RESUME3_acpu_drf_test_resume(data)                          (0x00000002&((data)<<1))
#define SYS_CRT_DRF_TEST_RESUME3_acpu_drf_test_resume_src(data)                      ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_TEST_RESUME3_get_acpu_drf_test_resume(data)                      ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_TEST_RESUME3_write_data_shift                                    (0)
#define SYS_CRT_DRF_TEST_RESUME3_write_data_mask                                     (0x00000001)
#define SYS_CRT_DRF_TEST_RESUME3_write_data(data)                                    (0x00000001&((data)<<0))
#define SYS_CRT_DRF_TEST_RESUME3_write_data_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_TEST_RESUME3_get_write_data(data)                                ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_START_PAUSE1                                                     0x18000560
#define SYS_CRT_DRF_START_PAUSE1_reg_addr                                            "0xB8000560"
#define SYS_CRT_DRF_START_PAUSE1_reg                                                 0xB8000560
#define set_SYS_CRT_DRF_START_PAUSE1_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_START_PAUSE1_reg)=data)
#define get_SYS_CRT_DRF_START_PAUSE1_reg   (*((volatile unsigned int*) SYS_CRT_DRF_START_PAUSE1_reg))
#define SYS_CRT_DRF_START_PAUSE1_inst_adr                                            "0x0058"
#define SYS_CRT_DRF_START_PAUSE1_inst                                                0x0058
#define SYS_CRT_DRF_START_PAUSE1_vde_drf_start_pause_shift                           (1)
#define SYS_CRT_DRF_START_PAUSE1_vde_drf_start_pause_mask                            (0x00000002)
#define SYS_CRT_DRF_START_PAUSE1_vde_drf_start_pause(data)                           (0x00000002&((data)<<1))
#define SYS_CRT_DRF_START_PAUSE1_vde_drf_start_pause_src(data)                       ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_START_PAUSE1_get_vde_drf_start_pause(data)                       ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_START_PAUSE1_write_data_shift                                    (0)
#define SYS_CRT_DRF_START_PAUSE1_write_data_mask                                     (0x00000001)
#define SYS_CRT_DRF_START_PAUSE1_write_data(data)                                    (0x00000001&((data)<<0))
#define SYS_CRT_DRF_START_PAUSE1_write_data_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_START_PAUSE1_get_write_data(data)                                ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_START_PAUSE3                                                     0x18000568
#define SYS_CRT_DRF_START_PAUSE3_reg_addr                                            "0xB8000568"
#define SYS_CRT_DRF_START_PAUSE3_reg                                                 0xB8000568
#define set_SYS_CRT_DRF_START_PAUSE3_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_START_PAUSE3_reg)=data)
#define get_SYS_CRT_DRF_START_PAUSE3_reg   (*((volatile unsigned int*) SYS_CRT_DRF_START_PAUSE3_reg))
#define SYS_CRT_DRF_START_PAUSE3_inst_adr                                            "0x005A"
#define SYS_CRT_DRF_START_PAUSE3_inst                                                0x005A
#define SYS_CRT_DRF_START_PAUSE3_etn2_drf_start_pause_shift                          (2)
#define SYS_CRT_DRF_START_PAUSE3_etn2_drf_start_pause_mask                           (0x00000004)
#define SYS_CRT_DRF_START_PAUSE3_etn2_drf_start_pause(data)                          (0x00000004&((data)<<2))
#define SYS_CRT_DRF_START_PAUSE3_etn2_drf_start_pause_src(data)                      ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_START_PAUSE3_get_etn2_drf_start_pause(data)                      ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_START_PAUSE3_vcpu_drf_start_pause_shift                          (1)
#define SYS_CRT_DRF_START_PAUSE3_vcpu_drf_start_pause_mask                           (0x00000002)
#define SYS_CRT_DRF_START_PAUSE3_vcpu_drf_start_pause(data)                          (0x00000002&((data)<<1))
#define SYS_CRT_DRF_START_PAUSE3_vcpu_drf_start_pause_src(data)                      ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_START_PAUSE3_get_vcpu_drf_start_pause(data)                      ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_START_PAUSE3_write_data_shift                                    (0)
#define SYS_CRT_DRF_START_PAUSE3_write_data_mask                                     (0x00000001)
#define SYS_CRT_DRF_START_PAUSE3_write_data(data)                                    (0x00000001&((data)<<0))
#define SYS_CRT_DRF_START_PAUSE3_write_data_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_START_PAUSE3_get_write_data(data)                                ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_EN1                                                             0x18000580
#define SYS_CRT_BISR_EN1_reg_addr                                                    "0xB8000580"
#define SYS_CRT_BISR_EN1_reg                                                         0xB8000580
#define set_SYS_CRT_BISR_EN1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_EN1_reg)=data)
#define get_SYS_CRT_BISR_EN1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_EN1_reg))
#define SYS_CRT_BISR_EN1_inst_adr                                                    "0x0060"
#define SYS_CRT_BISR_EN1_inst                                                        0x0060
#define SYS_CRT_BISR_EN1_kcpu_bisr_en_shift                                          (3)
#define SYS_CRT_BISR_EN1_kcpu_bisr_en_mask                                           (0x00000008)
#define SYS_CRT_BISR_EN1_kcpu_bisr_en(data)                                          (0x00000008&((data)<<3))
#define SYS_CRT_BISR_EN1_kcpu_bisr_en_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_EN1_get_kcpu_bisr_en(data)                                      ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_EN1_vcpu_bisr_en_shift                                          (2)
#define SYS_CRT_BISR_EN1_vcpu_bisr_en_mask                                           (0x00000004)
#define SYS_CRT_BISR_EN1_vcpu_bisr_en(data)                                          (0x00000004&((data)<<2))
#define SYS_CRT_BISR_EN1_vcpu_bisr_en_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_EN1_get_vcpu_bisr_en(data)                                      ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_EN1_acpu_bisr_en_shift                                          (1)
#define SYS_CRT_BISR_EN1_acpu_bisr_en_mask                                           (0x00000002)
#define SYS_CRT_BISR_EN1_acpu_bisr_en(data)                                          (0x00000002&((data)<<1))
#define SYS_CRT_BISR_EN1_acpu_bisr_en_src(data)                                      ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_EN1_get_acpu_bisr_en(data)                                      ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_EN1_write_data_shift                                            (0)
#define SYS_CRT_BISR_EN1_write_data_mask                                             (0x00000001)
#define SYS_CRT_BISR_EN1_write_data(data)                                            (0x00000001&((data)<<0))
#define SYS_CRT_BISR_EN1_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_EN1_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_RSTN1                                                           0x18000588
#define SYS_CRT_BISR_RSTN1_reg_addr                                                  "0xB8000588"
#define SYS_CRT_BISR_RSTN1_reg                                                       0xB8000588
#define set_SYS_CRT_BISR_RSTN1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_RSTN1_reg)=data)
#define get_SYS_CRT_BISR_RSTN1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_RSTN1_reg))
#define SYS_CRT_BISR_RSTN1_inst_adr                                                  "0x0062"
#define SYS_CRT_BISR_RSTN1_inst                                                      0x0062
#define SYS_CRT_BISR_RSTN1_cp42k_bisr_rstn_shift                                     (4)
#define SYS_CRT_BISR_RSTN1_cp42k_bisr_rstn_mask                                      (0x00000010)
#define SYS_CRT_BISR_RSTN1_cp42k_bisr_rstn(data)                                     (0x00000010&((data)<<4))
#define SYS_CRT_BISR_RSTN1_cp42k_bisr_rstn_src(data)                                 ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_RSTN1_get_cp42k_bisr_rstn(data)                                 ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_RSTN1_kcpu_bisr_rstn_shift                                      (3)
#define SYS_CRT_BISR_RSTN1_kcpu_bisr_rstn_mask                                       (0x00000008)
#define SYS_CRT_BISR_RSTN1_kcpu_bisr_rstn(data)                                      (0x00000008&((data)<<3))
#define SYS_CRT_BISR_RSTN1_kcpu_bisr_rstn_src(data)                                  ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_RSTN1_get_kcpu_bisr_rstn(data)                                  ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_RSTN1_vcpu_bisr_rstn_shift                                      (2)
#define SYS_CRT_BISR_RSTN1_vcpu_bisr_rstn_mask                                       (0x00000004)
#define SYS_CRT_BISR_RSTN1_vcpu_bisr_rstn(data)                                      (0x00000004&((data)<<2))
#define SYS_CRT_BISR_RSTN1_vcpu_bisr_rstn_src(data)                                  ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_RSTN1_get_vcpu_bisr_rstn(data)                                  ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_RSTN1_acpu_bisr_rstn_shift                                      (1)
#define SYS_CRT_BISR_RSTN1_acpu_bisr_rstn_mask                                       (0x00000002)
#define SYS_CRT_BISR_RSTN1_acpu_bisr_rstn(data)                                      (0x00000002&((data)<<1))
#define SYS_CRT_BISR_RSTN1_acpu_bisr_rstn_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_RSTN1_get_acpu_bisr_rstn(data)                                  ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_RSTN1_write_data_shift                                          (0)
#define SYS_CRT_BISR_RSTN1_write_data_mask                                           (0x00000001)
#define SYS_CRT_BISR_RSTN1_write_data(data)                                          (0x00000001&((data)<<0))
#define SYS_CRT_BISR_RSTN1_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_RSTN1_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_PWR_RSTN1                                                       0x18000590
#define SYS_CRT_BISR_PWR_RSTN1_reg_addr                                              "0xB8000590"
#define SYS_CRT_BISR_PWR_RSTN1_reg                                                   0xB8000590
#define set_SYS_CRT_BISR_PWR_RSTN1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_PWR_RSTN1_reg)=data)
#define get_SYS_CRT_BISR_PWR_RSTN1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_PWR_RSTN1_reg))
#define SYS_CRT_BISR_PWR_RSTN1_inst_adr                                              "0x0064"
#define SYS_CRT_BISR_PWR_RSTN1_inst                                                  0x0064
#define SYS_CRT_BISR_PWR_RSTN1_cp42k_bisr_pwr_rstn_shift                             (4)
#define SYS_CRT_BISR_PWR_RSTN1_cp42k_bisr_pwr_rstn_mask                              (0x00000010)
#define SYS_CRT_BISR_PWR_RSTN1_cp42k_bisr_pwr_rstn(data)                             (0x00000010&((data)<<4))
#define SYS_CRT_BISR_PWR_RSTN1_cp42k_bisr_pwr_rstn_src(data)                         ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_PWR_RSTN1_get_cp42k_bisr_pwr_rstn(data)                         ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_PWR_RSTN1_kcpu_bisr_pwr_rstn_shift                              (3)
#define SYS_CRT_BISR_PWR_RSTN1_kcpu_bisr_pwr_rstn_mask                               (0x00000008)
#define SYS_CRT_BISR_PWR_RSTN1_kcpu_bisr_pwr_rstn(data)                              (0x00000008&((data)<<3))
#define SYS_CRT_BISR_PWR_RSTN1_kcpu_bisr_pwr_rstn_src(data)                          ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_PWR_RSTN1_get_kcpu_bisr_pwr_rstn(data)                          ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_PWR_RSTN1_vcpu_bisr_pwr_rstn_shift                              (2)
#define SYS_CRT_BISR_PWR_RSTN1_vcpu_bisr_pwr_rstn_mask                               (0x00000004)
#define SYS_CRT_BISR_PWR_RSTN1_vcpu_bisr_pwr_rstn(data)                              (0x00000004&((data)<<2))
#define SYS_CRT_BISR_PWR_RSTN1_vcpu_bisr_pwr_rstn_src(data)                          ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_PWR_RSTN1_get_vcpu_bisr_pwr_rstn(data)                          ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_PWR_RSTN1_acpu_bisr_pwr_rstn_shift                              (1)
#define SYS_CRT_BISR_PWR_RSTN1_acpu_bisr_pwr_rstn_mask                               (0x00000002)
#define SYS_CRT_BISR_PWR_RSTN1_acpu_bisr_pwr_rstn(data)                              (0x00000002&((data)<<1))
#define SYS_CRT_BISR_PWR_RSTN1_acpu_bisr_pwr_rstn_src(data)                          ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_PWR_RSTN1_get_acpu_bisr_pwr_rstn(data)                          ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_PWR_RSTN1_write_data_shift                                      (0)
#define SYS_CRT_BISR_PWR_RSTN1_write_data_mask                                       (0x00000001)
#define SYS_CRT_BISR_PWR_RSTN1_write_data(data)                                      (0x00000001&((data)<<0))
#define SYS_CRT_BISR_PWR_RSTN1_write_data_src(data)                                  ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_PWR_RSTN1_get_write_data(data)                                  ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_HOLD_REMAP1                                                     0x18000598
#define SYS_CRT_BISR_HOLD_REMAP1_reg_addr                                            "0xB8000598"
#define SYS_CRT_BISR_HOLD_REMAP1_reg                                                 0xB8000598
#define set_SYS_CRT_BISR_HOLD_REMAP1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_HOLD_REMAP1_reg)=data)
#define get_SYS_CRT_BISR_HOLD_REMAP1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_HOLD_REMAP1_reg))
#define SYS_CRT_BISR_HOLD_REMAP1_inst_adr                                            "0x0066"
#define SYS_CRT_BISR_HOLD_REMAP1_inst                                                0x0066
#define SYS_CRT_BISR_HOLD_REMAP1_cp42k_bisr_hold_remap_shift                         (4)
#define SYS_CRT_BISR_HOLD_REMAP1_cp42k_bisr_hold_remap_mask                          (0x00000010)
#define SYS_CRT_BISR_HOLD_REMAP1_cp42k_bisr_hold_remap(data)                         (0x00000010&((data)<<4))
#define SYS_CRT_BISR_HOLD_REMAP1_cp42k_bisr_hold_remap_src(data)                     ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_HOLD_REMAP1_get_cp42k_bisr_hold_remap(data)                     ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_HOLD_REMAP1_kcpu_bisr_hold_remap_shift                          (3)
#define SYS_CRT_BISR_HOLD_REMAP1_kcpu_bisr_hold_remap_mask                           (0x00000008)
#define SYS_CRT_BISR_HOLD_REMAP1_kcpu_bisr_hold_remap(data)                          (0x00000008&((data)<<3))
#define SYS_CRT_BISR_HOLD_REMAP1_kcpu_bisr_hold_remap_src(data)                      ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_HOLD_REMAP1_get_kcpu_bisr_hold_remap(data)                      ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_HOLD_REMAP1_vcpu_bisr_hold_remap_shift                          (2)
#define SYS_CRT_BISR_HOLD_REMAP1_vcpu_bisr_hold_remap_mask                           (0x00000004)
#define SYS_CRT_BISR_HOLD_REMAP1_vcpu_bisr_hold_remap(data)                          (0x00000004&((data)<<2))
#define SYS_CRT_BISR_HOLD_REMAP1_vcpu_bisr_hold_remap_src(data)                      ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_HOLD_REMAP1_get_vcpu_bisr_hold_remap(data)                      ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_HOLD_REMAP1_acpu_bisr_hold_remap_shift                          (1)
#define SYS_CRT_BISR_HOLD_REMAP1_acpu_bisr_hold_remap_mask                           (0x00000002)
#define SYS_CRT_BISR_HOLD_REMAP1_acpu_bisr_hold_remap(data)                          (0x00000002&((data)<<1))
#define SYS_CRT_BISR_HOLD_REMAP1_acpu_bisr_hold_remap_src(data)                      ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_HOLD_REMAP1_get_acpu_bisr_hold_remap(data)                      ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_HOLD_REMAP1_write_data_shift                                    (0)
#define SYS_CRT_BISR_HOLD_REMAP1_write_data_mask                                     (0x00000001)
#define SYS_CRT_BISR_HOLD_REMAP1_write_data(data)                                    (0x00000001&((data)<<0))
#define SYS_CRT_BISR_HOLD_REMAP1_write_data_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_HOLD_REMAP1_get_write_data(data)                                ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_HOLD_REMAP2                                                     0x1800059C
#define SYS_CRT_BISR_HOLD_REMAP2_reg_addr                                            "0xB800059C"
#define SYS_CRT_BISR_HOLD_REMAP2_reg                                                 0xB800059C
#define set_SYS_CRT_BISR_HOLD_REMAP2_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_HOLD_REMAP2_reg)=data)
#define get_SYS_CRT_BISR_HOLD_REMAP2_reg   (*((volatile unsigned int*) SYS_CRT_BISR_HOLD_REMAP2_reg))
#define SYS_CRT_BISR_HOLD_REMAP2_inst_adr                                            "0x0067"
#define SYS_CRT_BISR_HOLD_REMAP2_inst                                                0x0067
#define SYS_CRT_BISR_HOLD_REMAP2_spnr_bisr_remap_shift                               (3)
#define SYS_CRT_BISR_HOLD_REMAP2_spnr_bisr_remap_mask                                (0x00000008)
#define SYS_CRT_BISR_HOLD_REMAP2_spnr_bisr_remap(data)                               (0x00000008&((data)<<3))
#define SYS_CRT_BISR_HOLD_REMAP2_spnr_bisr_remap_src(data)                           ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_HOLD_REMAP2_get_spnr_bisr_remap(data)                           ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_HOLD_REMAP2_iuzd_bisr_remap_shift                               (1)
#define SYS_CRT_BISR_HOLD_REMAP2_iuzd_bisr_remap_mask                                (0x00000002)
#define SYS_CRT_BISR_HOLD_REMAP2_iuzd_bisr_remap(data)                               (0x00000002&((data)<<1))
#define SYS_CRT_BISR_HOLD_REMAP2_iuzd_bisr_remap_src(data)                           ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_HOLD_REMAP2_get_iuzd_bisr_remap(data)                           ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_HOLD_REMAP2_ich1_bisr_sdnr_remap_shift                          (0)
#define SYS_CRT_BISR_HOLD_REMAP2_ich1_bisr_sdnr_remap_mask                           (0x00000001)
#define SYS_CRT_BISR_HOLD_REMAP2_ich1_bisr_sdnr_remap(data)                          (0x00000001&((data)<<0))
#define SYS_CRT_BISR_HOLD_REMAP2_ich1_bisr_sdnr_remap_src(data)                      ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_HOLD_REMAP2_get_ich1_bisr_sdnr_remap(data)                      ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_2ND_RUN_EN1                                                     0x180005A0
#define SYS_CRT_BISR_2ND_RUN_EN1_reg_addr                                            "0xB80005A0"
#define SYS_CRT_BISR_2ND_RUN_EN1_reg                                                 0xB80005A0
#define set_SYS_CRT_BISR_2ND_RUN_EN1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_2ND_RUN_EN1_reg)=data)
#define get_SYS_CRT_BISR_2ND_RUN_EN1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_2ND_RUN_EN1_reg))
#define SYS_CRT_BISR_2ND_RUN_EN1_inst_adr                                            "0x0068"
#define SYS_CRT_BISR_2ND_RUN_EN1_inst                                                0x0068
#define SYS_CRT_BISR_2ND_RUN_EN1_cp42k_bisr_second_run_en_shift                      (4)
#define SYS_CRT_BISR_2ND_RUN_EN1_cp42k_bisr_second_run_en_mask                       (0x00000010)
#define SYS_CRT_BISR_2ND_RUN_EN1_cp42k_bisr_second_run_en(data)                      (0x00000010&((data)<<4))
#define SYS_CRT_BISR_2ND_RUN_EN1_cp42k_bisr_second_run_en_src(data)                  ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_2ND_RUN_EN1_get_cp42k_bisr_second_run_en(data)                  ((0x00000010&(data))>>4)
#define SYS_CRT_BISR_2ND_RUN_EN1_kcpu_bisr_second_run_en_shift                       (3)
#define SYS_CRT_BISR_2ND_RUN_EN1_kcpu_bisr_second_run_en_mask                        (0x00000008)
#define SYS_CRT_BISR_2ND_RUN_EN1_kcpu_bisr_second_run_en(data)                       (0x00000008&((data)<<3))
#define SYS_CRT_BISR_2ND_RUN_EN1_kcpu_bisr_second_run_en_src(data)                   ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_2ND_RUN_EN1_get_kcpu_bisr_second_run_en(data)                   ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_2ND_RUN_EN1_vcpu_bisr_second_run_en_shift                       (2)
#define SYS_CRT_BISR_2ND_RUN_EN1_vcpu_bisr_second_run_en_mask                        (0x00000004)
#define SYS_CRT_BISR_2ND_RUN_EN1_vcpu_bisr_second_run_en(data)                       (0x00000004&((data)<<2))
#define SYS_CRT_BISR_2ND_RUN_EN1_vcpu_bisr_second_run_en_src(data)                   ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_2ND_RUN_EN1_get_vcpu_bisr_second_run_en(data)                   ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_2ND_RUN_EN1_acpu_bisr_second_run_en_shift                       (1)
#define SYS_CRT_BISR_2ND_RUN_EN1_acpu_bisr_second_run_en_mask                        (0x00000002)
#define SYS_CRT_BISR_2ND_RUN_EN1_acpu_bisr_second_run_en(data)                       (0x00000002&((data)<<1))
#define SYS_CRT_BISR_2ND_RUN_EN1_acpu_bisr_second_run_en_src(data)                   ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_2ND_RUN_EN1_get_acpu_bisr_second_run_en(data)                   ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_2ND_RUN_EN1_write_data_shift                                    (0)
#define SYS_CRT_BISR_2ND_RUN_EN1_write_data_mask                                     (0x00000001)
#define SYS_CRT_BISR_2ND_RUN_EN1_write_data(data)                                    (0x00000001&((data)<<0))
#define SYS_CRT_BISR_2ND_RUN_EN1_write_data_src(data)                                ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_2ND_RUN_EN1_get_write_data(data)                                ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_BISR_EN1                                                         0x180005A8
#define SYS_CRT_DRF_BISR_EN1_reg_addr                                                "0xB80005A8"
#define SYS_CRT_DRF_BISR_EN1_reg                                                     0xB80005A8
#define set_SYS_CRT_DRF_BISR_EN1_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_BISR_EN1_reg)=data)
#define get_SYS_CRT_DRF_BISR_EN1_reg   (*((volatile unsigned int*) SYS_CRT_DRF_BISR_EN1_reg))
#define SYS_CRT_DRF_BISR_EN1_inst_adr                                                "0x006A"
#define SYS_CRT_DRF_BISR_EN1_inst                                                    0x006A
#define SYS_CRT_DRF_BISR_EN1_cp42k_drf_bisr_en_shift                                 (4)
#define SYS_CRT_DRF_BISR_EN1_cp42k_drf_bisr_en_mask                                  (0x00000010)
#define SYS_CRT_DRF_BISR_EN1_cp42k_drf_bisr_en(data)                                 (0x00000010&((data)<<4))
#define SYS_CRT_DRF_BISR_EN1_cp42k_drf_bisr_en_src(data)                             ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_BISR_EN1_get_cp42k_drf_bisr_en(data)                             ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_BISR_EN1_kcpu_drf_bisr_en_shift                                  (3)
#define SYS_CRT_DRF_BISR_EN1_kcpu_drf_bisr_en_mask                                   (0x00000008)
#define SYS_CRT_DRF_BISR_EN1_kcpu_drf_bisr_en(data)                                  (0x00000008&((data)<<3))
#define SYS_CRT_DRF_BISR_EN1_kcpu_drf_bisr_en_src(data)                              ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_BISR_EN1_get_kcpu_drf_bisr_en(data)                              ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_BISR_EN1_vcpu_drf_bisr_en_shift                                  (2)
#define SYS_CRT_DRF_BISR_EN1_vcpu_drf_bisr_en_mask                                   (0x00000004)
#define SYS_CRT_DRF_BISR_EN1_vcpu_drf_bisr_en(data)                                  (0x00000004&((data)<<2))
#define SYS_CRT_DRF_BISR_EN1_vcpu_drf_bisr_en_src(data)                              ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BISR_EN1_get_vcpu_drf_bisr_en(data)                              ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BISR_EN1_acpu_drf_bisr_en_shift                                  (1)
#define SYS_CRT_DRF_BISR_EN1_acpu_drf_bisr_en_mask                                   (0x00000002)
#define SYS_CRT_DRF_BISR_EN1_acpu_drf_bisr_en(data)                                  (0x00000002&((data)<<1))
#define SYS_CRT_DRF_BISR_EN1_acpu_drf_bisr_en_src(data)                              ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BISR_EN1_get_acpu_drf_bisr_en(data)                              ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BISR_EN1_write_data_shift                                        (0)
#define SYS_CRT_DRF_BISR_EN1_write_data_mask                                         (0x00000001)
#define SYS_CRT_DRF_BISR_EN1_write_data(data)                                        (0x00000001&((data)<<0))
#define SYS_CRT_DRF_BISR_EN1_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_BISR_EN1_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define SYS_CRT_DRF_BISR_TEST_RESUME1                                                0x180005B0
#define SYS_CRT_DRF_BISR_TEST_RESUME1_reg_addr                                       "0xB80005B0"
#define SYS_CRT_DRF_BISR_TEST_RESUME1_reg                                            0xB80005B0
#define set_SYS_CRT_DRF_BISR_TEST_RESUME1_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_BISR_TEST_RESUME1_reg)=data)
#define get_SYS_CRT_DRF_BISR_TEST_RESUME1_reg   (*((volatile unsigned int*) SYS_CRT_DRF_BISR_TEST_RESUME1_reg))
#define SYS_CRT_DRF_BISR_TEST_RESUME1_inst_adr                                       "0x006C"
#define SYS_CRT_DRF_BISR_TEST_RESUME1_inst                                           0x006C
#define SYS_CRT_DRF_BISR_TEST_RESUME1_cp42k_drf_bisr_test_resume_shift               (4)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_cp42k_drf_bisr_test_resume_mask                (0x00000010)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_cp42k_drf_bisr_test_resume(data)               (0x00000010&((data)<<4))
#define SYS_CRT_DRF_BISR_TEST_RESUME1_cp42k_drf_bisr_test_resume_src(data)           ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_get_cp42k_drf_bisr_test_resume(data)           ((0x00000010&(data))>>4)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_kcpu_drf_bisr_test_resume_shift                (3)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_kcpu_drf_bisr_test_resume_mask                 (0x00000008)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_kcpu_drf_bisr_test_resume(data)                (0x00000008&((data)<<3))
#define SYS_CRT_DRF_BISR_TEST_RESUME1_kcpu_drf_bisr_test_resume_src(data)            ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_get_kcpu_drf_bisr_test_resume(data)            ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_vcpu_drf_bisr_test_resume_shift                (2)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_vcpu_drf_bisr_test_resume_mask                 (0x00000004)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_vcpu_drf_bisr_test_resume(data)                (0x00000004&((data)<<2))
#define SYS_CRT_DRF_BISR_TEST_RESUME1_vcpu_drf_bisr_test_resume_src(data)            ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_get_vcpu_drf_bisr_test_resume(data)            ((0x00000004&(data))>>2)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_acpu_drf_bisr_test_resume_shift                (1)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_acpu_drf_bisr_test_resume_mask                 (0x00000002)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_acpu_drf_bisr_test_resume(data)                (0x00000002&((data)<<1))
#define SYS_CRT_DRF_BISR_TEST_RESUME1_acpu_drf_bisr_test_resume_src(data)            ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_get_acpu_drf_bisr_test_resume(data)            ((0x00000002&(data))>>1)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_write_data_shift                               (0)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_write_data_mask                                (0x00000001)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_write_data(data)                               (0x00000001&((data)<<0))
#define SYS_CRT_DRF_BISR_TEST_RESUME1_write_data_src(data)                           ((0x00000001&(data))>>0)
#define SYS_CRT_DRF_BISR_TEST_RESUME1_get_write_data(data)                           ((0x00000001&(data))>>0)


#define SYS_CRT_SLEEP_ACK1                                                           0x180005B4
#define SYS_CRT_SLEEP_ACK1_reg_addr                                                  "0xB80005B4"
#define SYS_CRT_SLEEP_ACK1_reg                                                       0xB80005B4
#define set_SYS_CRT_SLEEP_ACK1_reg(data)   (*((volatile unsigned int*) SYS_CRT_SLEEP_ACK1_reg)=data)
#define get_SYS_CRT_SLEEP_ACK1_reg   (*((volatile unsigned int*) SYS_CRT_SLEEP_ACK1_reg))
#define SYS_CRT_SLEEP_ACK1_inst_adr                                                  "0x006D"
#define SYS_CRT_SLEEP_ACK1_inst                                                      0x006D
#define SYS_CRT_SLEEP_ACK1_vcpu_sleepsys_r_shift                                     (2)
#define SYS_CRT_SLEEP_ACK1_vcpu_sleepsys_r_mask                                      (0x00000004)
#define SYS_CRT_SLEEP_ACK1_vcpu_sleepsys_r(data)                                     (0x00000004&((data)<<2))
#define SYS_CRT_SLEEP_ACK1_vcpu_sleepsys_r_src(data)                                 ((0x00000004&(data))>>2)
#define SYS_CRT_SLEEP_ACK1_get_vcpu_sleepsys_r(data)                                 ((0x00000004&(data))>>2)
#define SYS_CRT_SLEEP_ACK1_acpu_sleepsys_r_shift                                     (1)
#define SYS_CRT_SLEEP_ACK1_acpu_sleepsys_r_mask                                      (0x00000002)
#define SYS_CRT_SLEEP_ACK1_acpu_sleepsys_r(data)                                     (0x00000002&((data)<<1))
#define SYS_CRT_SLEEP_ACK1_acpu_sleepsys_r_src(data)                                 ((0x00000002&(data))>>1)
#define SYS_CRT_SLEEP_ACK1_get_acpu_sleepsys_r(data)                                 ((0x00000002&(data))>>1)


#define SYS_CRT_SLEEP_REQ1                                                           0x180005B8
#define SYS_CRT_SLEEP_REQ1_reg_addr                                                  "0xB80005B8"
#define SYS_CRT_SLEEP_REQ1_reg                                                       0xB80005B8
#define set_SYS_CRT_SLEEP_REQ1_reg(data)   (*((volatile unsigned int*) SYS_CRT_SLEEP_REQ1_reg)=data)
#define get_SYS_CRT_SLEEP_REQ1_reg   (*((volatile unsigned int*) SYS_CRT_SLEEP_REQ1_reg))
#define SYS_CRT_SLEEP_REQ1_inst_adr                                                  "0x006E"
#define SYS_CRT_SLEEP_REQ1_inst                                                      0x006E
#define SYS_CRT_SLEEP_REQ1_vcpu_sleepreq_r_shift                                     (2)
#define SYS_CRT_SLEEP_REQ1_vcpu_sleepreq_r_mask                                      (0x00000004)
#define SYS_CRT_SLEEP_REQ1_vcpu_sleepreq_r(data)                                     (0x00000004&((data)<<2))
#define SYS_CRT_SLEEP_REQ1_vcpu_sleepreq_r_src(data)                                 ((0x00000004&(data))>>2)
#define SYS_CRT_SLEEP_REQ1_get_vcpu_sleepreq_r(data)                                 ((0x00000004&(data))>>2)
#define SYS_CRT_SLEEP_REQ1_acpu_sleepreq_r_shift                                     (1)
#define SYS_CRT_SLEEP_REQ1_acpu_sleepreq_r_mask                                      (0x00000002)
#define SYS_CRT_SLEEP_REQ1_acpu_sleepreq_r(data)                                     (0x00000002&((data)<<1))
#define SYS_CRT_SLEEP_REQ1_acpu_sleepreq_r_src(data)                                 ((0x00000002&(data))>>1)
#define SYS_CRT_SLEEP_REQ1_get_acpu_sleepreq_r(data)                                 ((0x00000002&(data))>>1)
#define SYS_CRT_SLEEP_REQ1_write_data_shift                                          (0)
#define SYS_CRT_SLEEP_REQ1_write_data_mask                                           (0x00000001)
#define SYS_CRT_SLEEP_REQ1_write_data(data)                                          (0x00000001&((data)<<0))
#define SYS_CRT_SLEEP_REQ1_write_data_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_CRT_SLEEP_REQ1_get_write_data(data)                                      ((0x00000001&(data))>>0)


#define SYS_CRT_LIGHT_SLEEP1                                                         0x180005C0
#define SYS_CRT_LIGHT_SLEEP1_reg_addr                                                "0xB80005C0"
#define SYS_CRT_LIGHT_SLEEP1_reg                                                     0xB80005C0
#define set_SYS_CRT_LIGHT_SLEEP1_reg(data)   (*((volatile unsigned int*) SYS_CRT_LIGHT_SLEEP1_reg)=data)
#define get_SYS_CRT_LIGHT_SLEEP1_reg   (*((volatile unsigned int*) SYS_CRT_LIGHT_SLEEP1_reg))
#define SYS_CRT_LIGHT_SLEEP1_inst_adr                                                "0x0070"
#define SYS_CRT_LIGHT_SLEEP1_inst                                                    0x0070
#define SYS_CRT_LIGHT_SLEEP1_nf_light_sleep_shift                                    (12)
#define SYS_CRT_LIGHT_SLEEP1_nf_light_sleep_mask                                     (0x00001000)
#define SYS_CRT_LIGHT_SLEEP1_nf_light_sleep(data)                                    (0x00001000&((data)<<12))
#define SYS_CRT_LIGHT_SLEEP1_nf_light_sleep_src(data)                                ((0x00001000&(data))>>12)
#define SYS_CRT_LIGHT_SLEEP1_get_nf_light_sleep(data)                                ((0x00001000&(data))>>12)
#define SYS_CRT_LIGHT_SLEEP1_md_light_sleep_shift                                    (11)
#define SYS_CRT_LIGHT_SLEEP1_md_light_sleep_mask                                     (0x00000800)
#define SYS_CRT_LIGHT_SLEEP1_md_light_sleep(data)                                    (0x00000800&((data)<<11))
#define SYS_CRT_LIGHT_SLEEP1_md_light_sleep_src(data)                                ((0x00000800&(data))>>11)
#define SYS_CRT_LIGHT_SLEEP1_get_md_light_sleep(data)                                ((0x00000800&(data))>>11)
#define SYS_CRT_LIGHT_SLEEP1_etn_light_sleep_shift                                   (10)
#define SYS_CRT_LIGHT_SLEEP1_etn_light_sleep_mask                                    (0x00000400)
#define SYS_CRT_LIGHT_SLEEP1_etn_light_sleep(data)                                   (0x00000400&((data)<<10))
#define SYS_CRT_LIGHT_SLEEP1_etn_light_sleep_src(data)                               ((0x00000400&(data))>>10)
#define SYS_CRT_LIGHT_SLEEP1_get_etn_light_sleep(data)                               ((0x00000400&(data))>>10)
#define SYS_CRT_LIGHT_SLEEP1_cp_light_sleep_shift                                    (9)
#define SYS_CRT_LIGHT_SLEEP1_cp_light_sleep_mask                                     (0x00000200)
#define SYS_CRT_LIGHT_SLEEP1_cp_light_sleep(data)                                    (0x00000200&((data)<<9))
#define SYS_CRT_LIGHT_SLEEP1_cp_light_sleep_src(data)                                ((0x00000200&(data))>>9)
#define SYS_CRT_LIGHT_SLEEP1_get_cp_light_sleep(data)                                ((0x00000200&(data))>>9)
#define SYS_CRT_LIGHT_SLEEP1_hdmitx_light_sleep_shift                                (8)
#define SYS_CRT_LIGHT_SLEEP1_hdmitx_light_sleep_mask                                 (0x00000100)
#define SYS_CRT_LIGHT_SLEEP1_hdmitx_light_sleep(data)                                (0x00000100&((data)<<8))
#define SYS_CRT_LIGHT_SLEEP1_hdmitx_light_sleep_src(data)                            ((0x00000100&(data))>>8)
#define SYS_CRT_LIGHT_SLEEP1_get_hdmitx_light_sleep(data)                            ((0x00000100&(data))>>8)
#define SYS_CRT_LIGHT_SLEEP1_dc_sb_light_sleep_shift                                 (7)
#define SYS_CRT_LIGHT_SLEEP1_dc_sb_light_sleep_mask                                  (0x00000080)
#define SYS_CRT_LIGHT_SLEEP1_dc_sb_light_sleep(data)                                 (0x00000080&((data)<<7))
#define SYS_CRT_LIGHT_SLEEP1_dc_sb_light_sleep_src(data)                             ((0x00000080&(data))>>7)
#define SYS_CRT_LIGHT_SLEEP1_get_dc_sb_light_sleep(data)                             ((0x00000080&(data))>>7)
#define SYS_CRT_LIGHT_SLEEP1_sb2_light_sleep_shift                                   (6)
#define SYS_CRT_LIGHT_SLEEP1_sb2_light_sleep_mask                                    (0x00000040)
#define SYS_CRT_LIGHT_SLEEP1_sb2_light_sleep(data)                                   (0x00000040&((data)<<6))
#define SYS_CRT_LIGHT_SLEEP1_sb2_light_sleep_src(data)                               ((0x00000040&(data))>>6)
#define SYS_CRT_LIGHT_SLEEP1_get_sb2_light_sleep(data)                               ((0x00000040&(data))>>6)
#define SYS_CRT_LIGHT_SLEEP1_ve_light_sleep_shift                                    (5)
#define SYS_CRT_LIGHT_SLEEP1_ve_light_sleep_mask                                     (0x00000020)
#define SYS_CRT_LIGHT_SLEEP1_ve_light_sleep(data)                                    (0x00000020&((data)<<5))
#define SYS_CRT_LIGHT_SLEEP1_ve_light_sleep_src(data)                                ((0x00000020&(data))>>5)
#define SYS_CRT_LIGHT_SLEEP1_get_ve_light_sleep(data)                                ((0x00000020&(data))>>5)
#define SYS_CRT_LIGHT_SLEEP1_sb2_rom_light_sleep_shift                               (4)
#define SYS_CRT_LIGHT_SLEEP1_sb2_rom_light_sleep_mask                                (0x00000010)
#define SYS_CRT_LIGHT_SLEEP1_sb2_rom_light_sleep(data)                               (0x00000010&((data)<<4))
#define SYS_CRT_LIGHT_SLEEP1_sb2_rom_light_sleep_src(data)                           ((0x00000010&(data))>>4)
#define SYS_CRT_LIGHT_SLEEP1_get_sb2_rom_light_sleep(data)                           ((0x00000010&(data))>>4)
#define SYS_CRT_LIGHT_SLEEP1_kcpu_light_sleep_shift                                  (3)
#define SYS_CRT_LIGHT_SLEEP1_kcpu_light_sleep_mask                                   (0x00000008)
#define SYS_CRT_LIGHT_SLEEP1_kcpu_light_sleep(data)                                  (0x00000008&((data)<<3))
#define SYS_CRT_LIGHT_SLEEP1_kcpu_light_sleep_src(data)                              ((0x00000008&(data))>>3)
#define SYS_CRT_LIGHT_SLEEP1_get_kcpu_light_sleep(data)                              ((0x00000008&(data))>>3)
#define SYS_CRT_LIGHT_SLEEP1_vcpu_light_sleep_shift                                  (2)
#define SYS_CRT_LIGHT_SLEEP1_vcpu_light_sleep_mask                                   (0x00000004)
#define SYS_CRT_LIGHT_SLEEP1_vcpu_light_sleep(data)                                  (0x00000004&((data)<<2))
#define SYS_CRT_LIGHT_SLEEP1_vcpu_light_sleep_src(data)                              ((0x00000004&(data))>>2)
#define SYS_CRT_LIGHT_SLEEP1_get_vcpu_light_sleep(data)                              ((0x00000004&(data))>>2)
#define SYS_CRT_LIGHT_SLEEP1_acpu_light_sleep_shift                                  (1)
#define SYS_CRT_LIGHT_SLEEP1_acpu_light_sleep_mask                                   (0x00000002)
#define SYS_CRT_LIGHT_SLEEP1_acpu_light_sleep(data)                                  (0x00000002&((data)<<1))
#define SYS_CRT_LIGHT_SLEEP1_acpu_light_sleep_src(data)                              ((0x00000002&(data))>>1)
#define SYS_CRT_LIGHT_SLEEP1_get_acpu_light_sleep(data)                              ((0x00000002&(data))>>1)
#define SYS_CRT_LIGHT_SLEEP1_write_data_shift                                        (0)
#define SYS_CRT_LIGHT_SLEEP1_write_data_mask                                         (0x00000001)
#define SYS_CRT_LIGHT_SLEEP1_write_data(data)                                        (0x00000001&((data)<<0))
#define SYS_CRT_LIGHT_SLEEP1_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define SYS_CRT_LIGHT_SLEEP1_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_RSTN2                                                           0x180005D0
#define SYS_CRT_BISR_RSTN2_reg_addr                                                  "0xB80005D0"
#define SYS_CRT_BISR_RSTN2_reg                                                       0xB80005D0
#define set_SYS_CRT_BISR_RSTN2_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_RSTN2_reg)=data)
#define get_SYS_CRT_BISR_RSTN2_reg   (*((volatile unsigned int*) SYS_CRT_BISR_RSTN2_reg))
#define SYS_CRT_BISR_RSTN2_inst_adr                                                  "0x0074"
#define SYS_CRT_BISR_RSTN2_inst                                                      0x0074
#define SYS_CRT_BISR_RSTN2_spnr_bisr_rstn_shift                                      (3)
#define SYS_CRT_BISR_RSTN2_spnr_bisr_rstn_mask                                       (0x00000008)
#define SYS_CRT_BISR_RSTN2_spnr_bisr_rstn(data)                                      (0x00000008&((data)<<3))
#define SYS_CRT_BISR_RSTN2_spnr_bisr_rstn_src(data)                                  ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_RSTN2_get_spnr_bisr_rstn(data)                                  ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_RSTN2_iuzd_bisr_rstn_shift                                      (1)
#define SYS_CRT_BISR_RSTN2_iuzd_bisr_rstn_mask                                       (0x00000002)
#define SYS_CRT_BISR_RSTN2_iuzd_bisr_rstn(data)                                      (0x00000002&((data)<<1))
#define SYS_CRT_BISR_RSTN2_iuzd_bisr_rstn_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_RSTN2_get_iuzd_bisr_rstn(data)                                  ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_RSTN2_ich1_bisr_sdnr_rstn_shift                                 (0)
#define SYS_CRT_BISR_RSTN2_ich1_bisr_sdnr_rstn_mask                                  (0x00000001)
#define SYS_CRT_BISR_RSTN2_ich1_bisr_sdnr_rstn(data)                                 (0x00000001&((data)<<0))
#define SYS_CRT_BISR_RSTN2_ich1_bisr_sdnr_rstn_src(data)                             ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_RSTN2_get_ich1_bisr_sdnr_rstn(data)                             ((0x00000001&(data))>>0)


#define SYS_BIST_ST1                                                                 0x18000600
#define SYS_BIST_ST1_reg_addr                                                        "0xB8000600"
#define SYS_BIST_ST1_reg                                                             0xB8000600
#define set_SYS_BIST_ST1_reg(data)   (*((volatile unsigned int*) SYS_BIST_ST1_reg)=data)
#define get_SYS_BIST_ST1_reg   (*((volatile unsigned int*) SYS_BIST_ST1_reg))
#define SYS_BIST_ST1_inst_adr                                                        "0x0080"
#define SYS_BIST_ST1_inst                                                            0x0080
#define SYS_BIST_ST1_mbist_ve_st_shift                                               (4)
#define SYS_BIST_ST1_mbist_ve_st_mask                                                (0x00000010)
#define SYS_BIST_ST1_mbist_ve_st(data)                                               (0x00000010&((data)<<4))
#define SYS_BIST_ST1_mbist_ve_st_src(data)                                           ((0x00000010&(data))>>4)
#define SYS_BIST_ST1_get_mbist_ve_st(data)                                           ((0x00000010&(data))>>4)
#define SYS_BIST_ST1_mbist_tp_st_shift                                               (3)
#define SYS_BIST_ST1_mbist_tp_st_mask                                                (0x00000008)
#define SYS_BIST_ST1_mbist_tp_st(data)                                               (0x00000008&((data)<<3))
#define SYS_BIST_ST1_mbist_tp_st_src(data)                                           ((0x00000008&(data))>>3)
#define SYS_BIST_ST1_get_mbist_tp_st(data)                                           ((0x00000008&(data))>>3)
#define SYS_BIST_ST1_mbist_md_st_shift                                               (2)
#define SYS_BIST_ST1_mbist_md_st_mask                                                (0x00000004)
#define SYS_BIST_ST1_mbist_md_st(data)                                               (0x00000004&((data)<<2))
#define SYS_BIST_ST1_mbist_md_st_src(data)                                           ((0x00000004&(data))>>2)
#define SYS_BIST_ST1_get_mbist_md_st(data)                                           ((0x00000004&(data))>>2)
#define SYS_BIST_ST1_mbist_hdmi_st_shift                                             (1)
#define SYS_BIST_ST1_mbist_hdmi_st_mask                                              (0x00000002)
#define SYS_BIST_ST1_mbist_hdmi_st(data)                                             (0x00000002&((data)<<1))
#define SYS_BIST_ST1_mbist_hdmi_st_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_BIST_ST1_get_mbist_hdmi_st(data)                                         ((0x00000002&(data))>>1)
#define SYS_BIST_ST1_mbist_acpu_st_shift                                             (0)
#define SYS_BIST_ST1_mbist_acpu_st_mask                                              (0x00000001)
#define SYS_BIST_ST1_mbist_acpu_st(data)                                             (0x00000001&((data)<<0))
#define SYS_BIST_ST1_mbist_acpu_st_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_BIST_ST1_get_mbist_acpu_st(data)                                         ((0x00000001&(data))>>0)


#define SYS_BIST_ST2                                                                 0x18000610
#define SYS_BIST_ST2_reg_addr                                                        "0xB8000610"
#define SYS_BIST_ST2_reg                                                             0xB8000610
#define set_SYS_BIST_ST2_reg(data)   (*((volatile unsigned int*) SYS_BIST_ST2_reg)=data)
#define get_SYS_BIST_ST2_reg   (*((volatile unsigned int*) SYS_BIST_ST2_reg))
#define SYS_BIST_ST2_inst_adr                                                        "0x0084"
#define SYS_BIST_ST2_inst                                                            0x0084
#define SYS_BIST_ST2_vcpu_bist_fail_shift                                            (24)
#define SYS_BIST_ST2_vcpu_bist_fail_mask                                             (0x01000000)
#define SYS_BIST_ST2_vcpu_bist_fail(data)                                            (0x01000000&((data)<<24))
#define SYS_BIST_ST2_vcpu_bist_fail_src(data)                                        ((0x01000000&(data))>>24)
#define SYS_BIST_ST2_get_vcpu_bist_fail(data)                                        ((0x01000000&(data))>>24)
#define SYS_BIST_ST2_vde_bist_fail0_shift                                            (14)
#define SYS_BIST_ST2_vde_bist_fail0_mask                                             (0x00004000)
#define SYS_BIST_ST2_vde_bist_fail0(data)                                            (0x00004000&((data)<<14))
#define SYS_BIST_ST2_vde_bist_fail0_src(data)                                        ((0x00004000&(data))>>14)
#define SYS_BIST_ST2_get_vde_bist_fail0(data)                                        ((0x00004000&(data))>>14)
#define SYS_BIST_ST2_sce_bist_fail_shift                                             (13)
#define SYS_BIST_ST2_sce_bist_fail_mask                                              (0x00002000)
#define SYS_BIST_ST2_sce_bist_fail(data)                                             (0x00002000&((data)<<13))
#define SYS_BIST_ST2_sce_bist_fail_src(data)                                         ((0x00002000&(data))>>13)
#define SYS_BIST_ST2_get_sce_bist_fail(data)                                         ((0x00002000&(data))>>13)
#define SYS_BIST_ST2_kcpu_bist_fail_shift                                            (12)
#define SYS_BIST_ST2_kcpu_bist_fail_mask                                             (0x00001000)
#define SYS_BIST_ST2_kcpu_bist_fail(data)                                            (0x00001000&((data)<<12))
#define SYS_BIST_ST2_kcpu_bist_fail_src(data)                                        ((0x00001000&(data))>>12)
#define SYS_BIST_ST2_get_kcpu_bist_fail(data)                                        ((0x00001000&(data))>>12)
#define SYS_BIST_ST2_etn_bist2_fail_shift                                            (11)
#define SYS_BIST_ST2_etn_bist2_fail_mask                                             (0x00000800)
#define SYS_BIST_ST2_etn_bist2_fail(data)                                            (0x00000800&((data)<<11))
#define SYS_BIST_ST2_etn_bist2_fail_src(data)                                        ((0x00000800&(data))>>11)
#define SYS_BIST_ST2_get_etn_bist2_fail(data)                                        ((0x00000800&(data))>>11)
#define SYS_BIST_ST2_nf1_bist_fail_shift                                             (10)
#define SYS_BIST_ST2_nf1_bist_fail_mask                                              (0x00000400)
#define SYS_BIST_ST2_nf1_bist_fail(data)                                             (0x00000400&((data)<<10))
#define SYS_BIST_ST2_nf1_bist_fail_src(data)                                         ((0x00000400&(data))>>10)
#define SYS_BIST_ST2_get_nf1_bist_fail(data)                                         ((0x00000400&(data))>>10)
#define SYS_BIST_ST2_me_bist_fail1_shift                                             (9)
#define SYS_BIST_ST2_me_bist_fail1_mask                                              (0x00000200)
#define SYS_BIST_ST2_me_bist_fail1(data)                                             (0x00000200&((data)<<9))
#define SYS_BIST_ST2_me_bist_fail1_src(data)                                         ((0x00000200&(data))>>9)
#define SYS_BIST_ST2_get_me_bist_fail1(data)                                         ((0x00000200&(data))>>9)
#define SYS_BIST_ST2_me_bist_fail0_shift                                             (8)
#define SYS_BIST_ST2_me_bist_fail0_mask                                              (0x00000100)
#define SYS_BIST_ST2_me_bist_fail0(data)                                             (0x00000100&((data)<<8))
#define SYS_BIST_ST2_me_bist_fail0_src(data)                                         ((0x00000100&(data))>>8)
#define SYS_BIST_ST2_get_me_bist_fail0(data)                                         ((0x00000100&(data))>>8)
#define SYS_BIST_ST2_dc3_bist_fail_shift                                             (5)
#define SYS_BIST_ST2_dc3_bist_fail_mask                                              (0x00000020)
#define SYS_BIST_ST2_dc3_bist_fail(data)                                             (0x00000020&((data)<<5))
#define SYS_BIST_ST2_dc3_bist_fail_src(data)                                         ((0x00000020&(data))>>5)
#define SYS_BIST_ST2_get_dc3_bist_fail(data)                                         ((0x00000020&(data))>>5)
#define SYS_BIST_ST2_dc2_bist_fail_shift                                             (4)
#define SYS_BIST_ST2_dc2_bist_fail_mask                                              (0x00000010)
#define SYS_BIST_ST2_dc2_bist_fail(data)                                             (0x00000010&((data)<<4))
#define SYS_BIST_ST2_dc2_bist_fail_src(data)                                         ((0x00000010&(data))>>4)
#define SYS_BIST_ST2_get_dc2_bist_fail(data)                                         ((0x00000010&(data))>>4)
#define SYS_BIST_ST2_cp_bist_fail_shift                                              (1)
#define SYS_BIST_ST2_cp_bist_fail_mask                                               (0x00000002)
#define SYS_BIST_ST2_cp_bist_fail(data)                                              (0x00000002&((data)<<1))
#define SYS_BIST_ST2_cp_bist_fail_src(data)                                          ((0x00000002&(data))>>1)
#define SYS_BIST_ST2_get_cp_bist_fail(data)                                          ((0x00000002&(data))>>1)
#define SYS_BIST_ST2_ae_bist_fail_shift                                              (0)
#define SYS_BIST_ST2_ae_bist_fail_mask                                               (0x00000001)
#define SYS_BIST_ST2_ae_bist_fail(data)                                              (0x00000001&((data)<<0))
#define SYS_BIST_ST2_ae_bist_fail_src(data)                                          ((0x00000001&(data))>>0)
#define SYS_BIST_ST2_get_ae_bist_fail(data)                                          ((0x00000001&(data))>>0)


#define SYS_BIST_ST3                                                                 0x18000614
#define SYS_BIST_ST3_reg_addr                                                        "0xB8000614"
#define SYS_BIST_ST3_reg                                                             0xB8000614
#define set_SYS_BIST_ST3_reg(data)   (*((volatile unsigned int*) SYS_BIST_ST3_reg)=data)
#define get_SYS_BIST_ST3_reg   (*((volatile unsigned int*) SYS_BIST_ST3_reg))
#define SYS_BIST_ST3_inst_adr                                                        "0x0085"
#define SYS_BIST_ST3_inst                                                            0x0085
#define SYS_BIST_ST3_ve_bist17_fail_shift                                            (16)
#define SYS_BIST_ST3_ve_bist17_fail_mask                                             (0x00010000)
#define SYS_BIST_ST3_ve_bist17_fail(data)                                            (0x00010000&((data)<<16))
#define SYS_BIST_ST3_ve_bist17_fail_src(data)                                        ((0x00010000&(data))>>16)
#define SYS_BIST_ST3_get_ve_bist17_fail(data)                                        ((0x00010000&(data))>>16)
#define SYS_BIST_ST3_ve_bist16_fail_shift                                            (15)
#define SYS_BIST_ST3_ve_bist16_fail_mask                                             (0x00008000)
#define SYS_BIST_ST3_ve_bist16_fail(data)                                            (0x00008000&((data)<<15))
#define SYS_BIST_ST3_ve_bist16_fail_src(data)                                        ((0x00008000&(data))>>15)
#define SYS_BIST_ST3_get_ve_bist16_fail(data)                                        ((0x00008000&(data))>>15)
#define SYS_BIST_ST3_ve_bist15_fail_shift                                            (14)
#define SYS_BIST_ST3_ve_bist15_fail_mask                                             (0x00004000)
#define SYS_BIST_ST3_ve_bist15_fail(data)                                            (0x00004000&((data)<<14))
#define SYS_BIST_ST3_ve_bist15_fail_src(data)                                        ((0x00004000&(data))>>14)
#define SYS_BIST_ST3_get_ve_bist15_fail(data)                                        ((0x00004000&(data))>>14)
#define SYS_BIST_ST3_ve_bist14_fail_shift                                            (13)
#define SYS_BIST_ST3_ve_bist14_fail_mask                                             (0x00002000)
#define SYS_BIST_ST3_ve_bist14_fail(data)                                            (0x00002000&((data)<<13))
#define SYS_BIST_ST3_ve_bist14_fail_src(data)                                        ((0x00002000&(data))>>13)
#define SYS_BIST_ST3_get_ve_bist14_fail(data)                                        ((0x00002000&(data))>>13)
#define SYS_BIST_ST3_ve_bist13_fail_shift                                            (12)
#define SYS_BIST_ST3_ve_bist13_fail_mask                                             (0x00001000)
#define SYS_BIST_ST3_ve_bist13_fail(data)                                            (0x00001000&((data)<<12))
#define SYS_BIST_ST3_ve_bist13_fail_src(data)                                        ((0x00001000&(data))>>12)
#define SYS_BIST_ST3_get_ve_bist13_fail(data)                                        ((0x00001000&(data))>>12)
#define SYS_BIST_ST3_ve_bist12_fail_shift                                            (11)
#define SYS_BIST_ST3_ve_bist12_fail_mask                                             (0x00000800)
#define SYS_BIST_ST3_ve_bist12_fail(data)                                            (0x00000800&((data)<<11))
#define SYS_BIST_ST3_ve_bist12_fail_src(data)                                        ((0x00000800&(data))>>11)
#define SYS_BIST_ST3_get_ve_bist12_fail(data)                                        ((0x00000800&(data))>>11)
#define SYS_BIST_ST3_ve_bist11_fail_shift                                            (10)
#define SYS_BIST_ST3_ve_bist11_fail_mask                                             (0x00000400)
#define SYS_BIST_ST3_ve_bist11_fail(data)                                            (0x00000400&((data)<<10))
#define SYS_BIST_ST3_ve_bist11_fail_src(data)                                        ((0x00000400&(data))>>10)
#define SYS_BIST_ST3_get_ve_bist11_fail(data)                                        ((0x00000400&(data))>>10)
#define SYS_BIST_ST3_ve_bist10_fail_shift                                            (9)
#define SYS_BIST_ST3_ve_bist10_fail_mask                                             (0x00000200)
#define SYS_BIST_ST3_ve_bist10_fail(data)                                            (0x00000200&((data)<<9))
#define SYS_BIST_ST3_ve_bist10_fail_src(data)                                        ((0x00000200&(data))>>9)
#define SYS_BIST_ST3_get_ve_bist10_fail(data)                                        ((0x00000200&(data))>>9)
#define SYS_BIST_ST3_ve_bist9_fail_shift                                             (8)
#define SYS_BIST_ST3_ve_bist9_fail_mask                                              (0x00000100)
#define SYS_BIST_ST3_ve_bist9_fail(data)                                             (0x00000100&((data)<<8))
#define SYS_BIST_ST3_ve_bist9_fail_src(data)                                         ((0x00000100&(data))>>8)
#define SYS_BIST_ST3_get_ve_bist9_fail(data)                                         ((0x00000100&(data))>>8)
#define SYS_BIST_ST3_ve_bist8_fail_shift                                             (7)
#define SYS_BIST_ST3_ve_bist8_fail_mask                                              (0x00000080)
#define SYS_BIST_ST3_ve_bist8_fail(data)                                             (0x00000080&((data)<<7))
#define SYS_BIST_ST3_ve_bist8_fail_src(data)                                         ((0x00000080&(data))>>7)
#define SYS_BIST_ST3_get_ve_bist8_fail(data)                                         ((0x00000080&(data))>>7)
#define SYS_BIST_ST3_ve_bist7_fail_shift                                             (6)
#define SYS_BIST_ST3_ve_bist7_fail_mask                                              (0x00000040)
#define SYS_BIST_ST3_ve_bist7_fail(data)                                             (0x00000040&((data)<<6))
#define SYS_BIST_ST3_ve_bist7_fail_src(data)                                         ((0x00000040&(data))>>6)
#define SYS_BIST_ST3_get_ve_bist7_fail(data)                                         ((0x00000040&(data))>>6)
#define SYS_BIST_ST3_ve_bist6_fail_shift                                             (5)
#define SYS_BIST_ST3_ve_bist6_fail_mask                                              (0x00000020)
#define SYS_BIST_ST3_ve_bist6_fail(data)                                             (0x00000020&((data)<<5))
#define SYS_BIST_ST3_ve_bist6_fail_src(data)                                         ((0x00000020&(data))>>5)
#define SYS_BIST_ST3_get_ve_bist6_fail(data)                                         ((0x00000020&(data))>>5)
#define SYS_BIST_ST3_ve_bist5_fail_shift                                             (4)
#define SYS_BIST_ST3_ve_bist5_fail_mask                                              (0x00000010)
#define SYS_BIST_ST3_ve_bist5_fail(data)                                             (0x00000010&((data)<<4))
#define SYS_BIST_ST3_ve_bist5_fail_src(data)                                         ((0x00000010&(data))>>4)
#define SYS_BIST_ST3_get_ve_bist5_fail(data)                                         ((0x00000010&(data))>>4)
#define SYS_BIST_ST3_ve_bist4_fail_shift                                             (3)
#define SYS_BIST_ST3_ve_bist4_fail_mask                                              (0x00000008)
#define SYS_BIST_ST3_ve_bist4_fail(data)                                             (0x00000008&((data)<<3))
#define SYS_BIST_ST3_ve_bist4_fail_src(data)                                         ((0x00000008&(data))>>3)
#define SYS_BIST_ST3_get_ve_bist4_fail(data)                                         ((0x00000008&(data))>>3)
#define SYS_BIST_ST3_ve_bist3_fail_shift                                             (2)
#define SYS_BIST_ST3_ve_bist3_fail_mask                                              (0x00000004)
#define SYS_BIST_ST3_ve_bist3_fail(data)                                             (0x00000004&((data)<<2))
#define SYS_BIST_ST3_ve_bist3_fail_src(data)                                         ((0x00000004&(data))>>2)
#define SYS_BIST_ST3_get_ve_bist3_fail(data)                                         ((0x00000004&(data))>>2)
#define SYS_BIST_ST3_ve_bist2_fail_shift                                             (1)
#define SYS_BIST_ST3_ve_bist2_fail_mask                                              (0x00000002)
#define SYS_BIST_ST3_ve_bist2_fail(data)                                             (0x00000002&((data)<<1))
#define SYS_BIST_ST3_ve_bist2_fail_src(data)                                         ((0x00000002&(data))>>1)
#define SYS_BIST_ST3_get_ve_bist2_fail(data)                                         ((0x00000002&(data))>>1)
#define SYS_BIST_ST3_ve_bist1_fail_shift                                             (0)
#define SYS_BIST_ST3_ve_bist1_fail_mask                                              (0x00000001)
#define SYS_BIST_ST3_ve_bist1_fail(data)                                             (0x00000001&((data)<<0))
#define SYS_BIST_ST3_ve_bist1_fail_src(data)                                         ((0x00000001&(data))>>0)
#define SYS_BIST_ST3_get_ve_bist1_fail(data)                                         ((0x00000001&(data))>>0)


#define SYS_DRF_ST1                                                                  0x18000620
#define SYS_DRF_ST1_reg_addr                                                         "0xB8000620"
#define SYS_DRF_ST1_reg                                                              0xB8000620
#define set_SYS_DRF_ST1_reg(data)   (*((volatile unsigned int*) SYS_DRF_ST1_reg)=data)
#define get_SYS_DRF_ST1_reg   (*((volatile unsigned int*) SYS_DRF_ST1_reg))
#define SYS_DRF_ST1_inst_adr                                                         "0x0088"
#define SYS_DRF_ST1_inst                                                             0x0088
#define SYS_DRF_ST1_vcpu_drf_bist_fail_shift                                         (24)
#define SYS_DRF_ST1_vcpu_drf_bist_fail_mask                                          (0x01000000)
#define SYS_DRF_ST1_vcpu_drf_bist_fail(data)                                         (0x01000000&((data)<<24))
#define SYS_DRF_ST1_vcpu_drf_bist_fail_src(data)                                     ((0x01000000&(data))>>24)
#define SYS_DRF_ST1_get_vcpu_drf_bist_fail(data)                                     ((0x01000000&(data))>>24)
#define SYS_DRF_ST1_etn_drf_bist2_fail_shift                                         (12)
#define SYS_DRF_ST1_etn_drf_bist2_fail_mask                                          (0x00001000)
#define SYS_DRF_ST1_etn_drf_bist2_fail(data)                                         (0x00001000&((data)<<12))
#define SYS_DRF_ST1_etn_drf_bist2_fail_src(data)                                     ((0x00001000&(data))>>12)
#define SYS_DRF_ST1_get_etn_drf_bist2_fail(data)                                     ((0x00001000&(data))>>12)
#define SYS_DRF_ST1_sce_drf_bist_fail_shift                                          (11)
#define SYS_DRF_ST1_sce_drf_bist_fail_mask                                           (0x00000800)
#define SYS_DRF_ST1_sce_drf_bist_fail(data)                                          (0x00000800&((data)<<11))
#define SYS_DRF_ST1_sce_drf_bist_fail_src(data)                                      ((0x00000800&(data))>>11)
#define SYS_DRF_ST1_get_sce_drf_bist_fail(data)                                      ((0x00000800&(data))>>11)
#define SYS_DRF_ST1_nf1_drf_bist_fail_shift                                          (10)
#define SYS_DRF_ST1_nf1_drf_bist_fail_mask                                           (0x00000400)
#define SYS_DRF_ST1_nf1_drf_bist_fail(data)                                          (0x00000400&((data)<<10))
#define SYS_DRF_ST1_nf1_drf_bist_fail_src(data)                                      ((0x00000400&(data))>>10)
#define SYS_DRF_ST1_get_nf1_drf_bist_fail(data)                                      ((0x00000400&(data))>>10)
#define SYS_DRF_ST1_me_drf_bist_fail1_shift                                          (9)
#define SYS_DRF_ST1_me_drf_bist_fail1_mask                                           (0x00000200)
#define SYS_DRF_ST1_me_drf_bist_fail1(data)                                          (0x00000200&((data)<<9))
#define SYS_DRF_ST1_me_drf_bist_fail1_src(data)                                      ((0x00000200&(data))>>9)
#define SYS_DRF_ST1_get_me_drf_bist_fail1(data)                                      ((0x00000200&(data))>>9)
#define SYS_DRF_ST1_me_drf_bist_fail0_shift                                          (8)
#define SYS_DRF_ST1_me_drf_bist_fail0_mask                                           (0x00000100)
#define SYS_DRF_ST1_me_drf_bist_fail0(data)                                          (0x00000100&((data)<<8))
#define SYS_DRF_ST1_me_drf_bist_fail0_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_DRF_ST1_get_me_drf_bist_fail0(data)                                      ((0x00000100&(data))>>8)
#define SYS_DRF_ST1_dc3_drf_bist_fail_shift                                          (5)
#define SYS_DRF_ST1_dc3_drf_bist_fail_mask                                           (0x00000020)
#define SYS_DRF_ST1_dc3_drf_bist_fail(data)                                          (0x00000020&((data)<<5))
#define SYS_DRF_ST1_dc3_drf_bist_fail_src(data)                                      ((0x00000020&(data))>>5)
#define SYS_DRF_ST1_get_dc3_drf_bist_fail(data)                                      ((0x00000020&(data))>>5)
#define SYS_DRF_ST1_dc2_drf_bist_fail_shift                                          (4)
#define SYS_DRF_ST1_dc2_drf_bist_fail_mask                                           (0x00000010)
#define SYS_DRF_ST1_dc2_drf_bist_fail(data)                                          (0x00000010&((data)<<4))
#define SYS_DRF_ST1_dc2_drf_bist_fail_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_DRF_ST1_get_dc2_drf_bist_fail(data)                                      ((0x00000010&(data))>>4)
#define SYS_DRF_ST1_cp_drf_bist_fail_shift                                           (1)
#define SYS_DRF_ST1_cp_drf_bist_fail_mask                                            (0x00000002)
#define SYS_DRF_ST1_cp_drf_bist_fail(data)                                           (0x00000002&((data)<<1))
#define SYS_DRF_ST1_cp_drf_bist_fail_src(data)                                       ((0x00000002&(data))>>1)
#define SYS_DRF_ST1_get_cp_drf_bist_fail(data)                                       ((0x00000002&(data))>>1)
#define SYS_DRF_ST1_ae_drf_bist_fail_shift                                           (0)
#define SYS_DRF_ST1_ae_drf_bist_fail_mask                                            (0x00000001)
#define SYS_DRF_ST1_ae_drf_bist_fail(data)                                           (0x00000001&((data)<<0))
#define SYS_DRF_ST1_ae_drf_bist_fail_src(data)                                       ((0x00000001&(data))>>0)
#define SYS_DRF_ST1_get_ae_drf_bist_fail(data)                                       ((0x00000001&(data))>>0)


#define SYS_DRF_ST2                                                                  0x18000624
#define SYS_DRF_ST2_reg_addr                                                         "0xB8000624"
#define SYS_DRF_ST2_reg                                                              0xB8000624
#define set_SYS_DRF_ST2_reg(data)   (*((volatile unsigned int*) SYS_DRF_ST2_reg)=data)
#define get_SYS_DRF_ST2_reg   (*((volatile unsigned int*) SYS_DRF_ST2_reg))
#define SYS_DRF_ST2_inst_adr                                                         "0x0089"
#define SYS_DRF_ST2_inst                                                             0x0089
#define SYS_DRF_ST2_ve_drf_bist17_fail_shift                                         (16)
#define SYS_DRF_ST2_ve_drf_bist17_fail_mask                                          (0x00010000)
#define SYS_DRF_ST2_ve_drf_bist17_fail(data)                                         (0x00010000&((data)<<16))
#define SYS_DRF_ST2_ve_drf_bist17_fail_src(data)                                     ((0x00010000&(data))>>16)
#define SYS_DRF_ST2_get_ve_drf_bist17_fail(data)                                     ((0x00010000&(data))>>16)
#define SYS_DRF_ST2_ve_drf_bist16_fail_shift                                         (15)
#define SYS_DRF_ST2_ve_drf_bist16_fail_mask                                          (0x00008000)
#define SYS_DRF_ST2_ve_drf_bist16_fail(data)                                         (0x00008000&((data)<<15))
#define SYS_DRF_ST2_ve_drf_bist16_fail_src(data)                                     ((0x00008000&(data))>>15)
#define SYS_DRF_ST2_get_ve_drf_bist16_fail(data)                                     ((0x00008000&(data))>>15)
#define SYS_DRF_ST2_ve_drf_bist15_fail_shift                                         (14)
#define SYS_DRF_ST2_ve_drf_bist15_fail_mask                                          (0x00004000)
#define SYS_DRF_ST2_ve_drf_bist15_fail(data)                                         (0x00004000&((data)<<14))
#define SYS_DRF_ST2_ve_drf_bist15_fail_src(data)                                     ((0x00004000&(data))>>14)
#define SYS_DRF_ST2_get_ve_drf_bist15_fail(data)                                     ((0x00004000&(data))>>14)
#define SYS_DRF_ST2_ve_drf_bist14_fail_shift                                         (13)
#define SYS_DRF_ST2_ve_drf_bist14_fail_mask                                          (0x00002000)
#define SYS_DRF_ST2_ve_drf_bist14_fail(data)                                         (0x00002000&((data)<<13))
#define SYS_DRF_ST2_ve_drf_bist14_fail_src(data)                                     ((0x00002000&(data))>>13)
#define SYS_DRF_ST2_get_ve_drf_bist14_fail(data)                                     ((0x00002000&(data))>>13)
#define SYS_DRF_ST2_ve_drf_bist13_fail_shift                                         (12)
#define SYS_DRF_ST2_ve_drf_bist13_fail_mask                                          (0x00001000)
#define SYS_DRF_ST2_ve_drf_bist13_fail(data)                                         (0x00001000&((data)<<12))
#define SYS_DRF_ST2_ve_drf_bist13_fail_src(data)                                     ((0x00001000&(data))>>12)
#define SYS_DRF_ST2_get_ve_drf_bist13_fail(data)                                     ((0x00001000&(data))>>12)
#define SYS_DRF_ST2_ve_drf_bist12_fail_shift                                         (11)
#define SYS_DRF_ST2_ve_drf_bist12_fail_mask                                          (0x00000800)
#define SYS_DRF_ST2_ve_drf_bist12_fail(data)                                         (0x00000800&((data)<<11))
#define SYS_DRF_ST2_ve_drf_bist12_fail_src(data)                                     ((0x00000800&(data))>>11)
#define SYS_DRF_ST2_get_ve_drf_bist12_fail(data)                                     ((0x00000800&(data))>>11)
#define SYS_DRF_ST2_ve_drf_bist11_fail_shift                                         (10)
#define SYS_DRF_ST2_ve_drf_bist11_fail_mask                                          (0x00000400)
#define SYS_DRF_ST2_ve_drf_bist11_fail(data)                                         (0x00000400&((data)<<10))
#define SYS_DRF_ST2_ve_drf_bist11_fail_src(data)                                     ((0x00000400&(data))>>10)
#define SYS_DRF_ST2_get_ve_drf_bist11_fail(data)                                     ((0x00000400&(data))>>10)
#define SYS_DRF_ST2_ve_drf_bist10_fail_shift                                         (9)
#define SYS_DRF_ST2_ve_drf_bist10_fail_mask                                          (0x00000200)
#define SYS_DRF_ST2_ve_drf_bist10_fail(data)                                         (0x00000200&((data)<<9))
#define SYS_DRF_ST2_ve_drf_bist10_fail_src(data)                                     ((0x00000200&(data))>>9)
#define SYS_DRF_ST2_get_ve_drf_bist10_fail(data)                                     ((0x00000200&(data))>>9)
#define SYS_DRF_ST2_ve_drf_bist9_fail_shift                                          (8)
#define SYS_DRF_ST2_ve_drf_bist9_fail_mask                                           (0x00000100)
#define SYS_DRF_ST2_ve_drf_bist9_fail(data)                                          (0x00000100&((data)<<8))
#define SYS_DRF_ST2_ve_drf_bist9_fail_src(data)                                      ((0x00000100&(data))>>8)
#define SYS_DRF_ST2_get_ve_drf_bist9_fail(data)                                      ((0x00000100&(data))>>8)
#define SYS_DRF_ST2_ve_drf_bist8_fail_shift                                          (7)
#define SYS_DRF_ST2_ve_drf_bist8_fail_mask                                           (0x00000080)
#define SYS_DRF_ST2_ve_drf_bist8_fail(data)                                          (0x00000080&((data)<<7))
#define SYS_DRF_ST2_ve_drf_bist8_fail_src(data)                                      ((0x00000080&(data))>>7)
#define SYS_DRF_ST2_get_ve_drf_bist8_fail(data)                                      ((0x00000080&(data))>>7)
#define SYS_DRF_ST2_ve_drf_bist7_fail_shift                                          (6)
#define SYS_DRF_ST2_ve_drf_bist7_fail_mask                                           (0x00000040)
#define SYS_DRF_ST2_ve_drf_bist7_fail(data)                                          (0x00000040&((data)<<6))
#define SYS_DRF_ST2_ve_drf_bist7_fail_src(data)                                      ((0x00000040&(data))>>6)
#define SYS_DRF_ST2_get_ve_drf_bist7_fail(data)                                      ((0x00000040&(data))>>6)
#define SYS_DRF_ST2_ve_drf_bist6_fail_shift                                          (5)
#define SYS_DRF_ST2_ve_drf_bist6_fail_mask                                           (0x00000020)
#define SYS_DRF_ST2_ve_drf_bist6_fail(data)                                          (0x00000020&((data)<<5))
#define SYS_DRF_ST2_ve_drf_bist6_fail_src(data)                                      ((0x00000020&(data))>>5)
#define SYS_DRF_ST2_get_ve_drf_bist6_fail(data)                                      ((0x00000020&(data))>>5)
#define SYS_DRF_ST2_ve_drf_bist5_fail_shift                                          (4)
#define SYS_DRF_ST2_ve_drf_bist5_fail_mask                                           (0x00000010)
#define SYS_DRF_ST2_ve_drf_bist5_fail(data)                                          (0x00000010&((data)<<4))
#define SYS_DRF_ST2_ve_drf_bist5_fail_src(data)                                      ((0x00000010&(data))>>4)
#define SYS_DRF_ST2_get_ve_drf_bist5_fail(data)                                      ((0x00000010&(data))>>4)
#define SYS_DRF_ST2_ve_drf_bist4_fail_shift                                          (3)
#define SYS_DRF_ST2_ve_drf_bist4_fail_mask                                           (0x00000008)
#define SYS_DRF_ST2_ve_drf_bist4_fail(data)                                          (0x00000008&((data)<<3))
#define SYS_DRF_ST2_ve_drf_bist4_fail_src(data)                                      ((0x00000008&(data))>>3)
#define SYS_DRF_ST2_get_ve_drf_bist4_fail(data)                                      ((0x00000008&(data))>>3)
#define SYS_DRF_ST2_ve_drf_bist3_fail_shift                                          (2)
#define SYS_DRF_ST2_ve_drf_bist3_fail_mask                                           (0x00000004)
#define SYS_DRF_ST2_ve_drf_bist3_fail(data)                                          (0x00000004&((data)<<2))
#define SYS_DRF_ST2_ve_drf_bist3_fail_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_DRF_ST2_get_ve_drf_bist3_fail(data)                                      ((0x00000004&(data))>>2)
#define SYS_DRF_ST2_ve_drf_bist2_fail_shift                                          (1)
#define SYS_DRF_ST2_ve_drf_bist2_fail_mask                                           (0x00000002)
#define SYS_DRF_ST2_ve_drf_bist2_fail(data)                                          (0x00000002&((data)<<1))
#define SYS_DRF_ST2_ve_drf_bist2_fail_src(data)                                      ((0x00000002&(data))>>1)
#define SYS_DRF_ST2_get_ve_drf_bist2_fail(data)                                      ((0x00000002&(data))>>1)
#define SYS_DRF_ST2_ve_drf_bist1_fail_shift                                          (0)
#define SYS_DRF_ST2_ve_drf_bist1_fail_mask                                           (0x00000001)
#define SYS_DRF_ST2_ve_drf_bist1_fail(data)                                          (0x00000001&((data)<<0))
#define SYS_DRF_ST2_ve_drf_bist1_fail_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_DRF_ST2_get_ve_drf_bist1_fail(data)                                      ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_DONE1                                                           0x18000700
#define SYS_CRT_BISR_DONE1_reg_addr                                                  "0xB8000700"
#define SYS_CRT_BISR_DONE1_reg                                                       0xB8000700
#define set_SYS_CRT_BISR_DONE1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_DONE1_reg)=data)
#define get_SYS_CRT_BISR_DONE1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_DONE1_reg))
#define SYS_CRT_BISR_DONE1_inst_adr                                                  "0x00C0"
#define SYS_CRT_BISR_DONE1_inst                                                      0x00C0
#define SYS_CRT_BISR_DONE1_spnr_bisr_done_shift                                      (27)
#define SYS_CRT_BISR_DONE1_spnr_bisr_done_mask                                       (0x08000000)
#define SYS_CRT_BISR_DONE1_spnr_bisr_done(data)                                      (0x08000000&((data)<<27))
#define SYS_CRT_BISR_DONE1_spnr_bisr_done_src(data)                                  ((0x08000000&(data))>>27)
#define SYS_CRT_BISR_DONE1_get_spnr_bisr_done(data)                                  ((0x08000000&(data))>>27)
#define SYS_CRT_BISR_DONE1_i3ddma_uzd_bisr_done_shift                                (25)
#define SYS_CRT_BISR_DONE1_i3ddma_uzd_bisr_done_mask                                 (0x02000000)
#define SYS_CRT_BISR_DONE1_i3ddma_uzd_bisr_done(data)                                (0x02000000&((data)<<25))
#define SYS_CRT_BISR_DONE1_i3ddma_uzd_bisr_done_src(data)                            ((0x02000000&(data))>>25)
#define SYS_CRT_BISR_DONE1_get_i3ddma_uzd_bisr_done(data)                            ((0x02000000&(data))>>25)
#define SYS_CRT_BISR_DONE1_ich1_bisr_sdnr_done_shift                                 (24)
#define SYS_CRT_BISR_DONE1_ich1_bisr_sdnr_done_mask                                  (0x01000000)
#define SYS_CRT_BISR_DONE1_ich1_bisr_sdnr_done(data)                                 (0x01000000&((data)<<24))
#define SYS_CRT_BISR_DONE1_ich1_bisr_sdnr_done_src(data)                             ((0x01000000&(data))>>24)
#define SYS_CRT_BISR_DONE1_get_ich1_bisr_sdnr_done(data)                             ((0x01000000&(data))>>24)
#define SYS_CRT_BISR_DONE1_cp42k_bisr_done_shift                                     (3)
#define SYS_CRT_BISR_DONE1_cp42k_bisr_done_mask                                      (0x00000008)
#define SYS_CRT_BISR_DONE1_cp42k_bisr_done(data)                                     (0x00000008&((data)<<3))
#define SYS_CRT_BISR_DONE1_cp42k_bisr_done_src(data)                                 ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_DONE1_get_cp42k_bisr_done(data)                                 ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_DONE1_kcpu_bisr_done_shift                                      (2)
#define SYS_CRT_BISR_DONE1_kcpu_bisr_done_mask                                       (0x00000004)
#define SYS_CRT_BISR_DONE1_kcpu_bisr_done(data)                                      (0x00000004&((data)<<2))
#define SYS_CRT_BISR_DONE1_kcpu_bisr_done_src(data)                                  ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_DONE1_get_kcpu_bisr_done(data)                                  ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_DONE1_vcpu_bisr_done_shift                                      (1)
#define SYS_CRT_BISR_DONE1_vcpu_bisr_done_mask                                       (0x00000002)
#define SYS_CRT_BISR_DONE1_vcpu_bisr_done(data)                                      (0x00000002&((data)<<1))
#define SYS_CRT_BISR_DONE1_vcpu_bisr_done_src(data)                                  ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_DONE1_get_vcpu_bisr_done(data)                                  ((0x00000002&(data))>>1)


#define SYS_CRT_BISR_ST1                                                             0x18000710
#define SYS_CRT_BISR_ST1_reg_addr                                                    "0xB8000710"
#define SYS_CRT_BISR_ST1_reg                                                         0xB8000710
#define set_SYS_CRT_BISR_ST1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_ST1_reg)=data)
#define get_SYS_CRT_BISR_ST1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_ST1_reg))
#define SYS_CRT_BISR_ST1_inst_adr                                                    "0x00C4"
#define SYS_CRT_BISR_ST1_inst                                                        0x00C4
#define SYS_CRT_BISR_ST1_vcpu_bisr_fail_shift                                        (28)
#define SYS_CRT_BISR_ST1_vcpu_bisr_fail_mask                                         (0x10000000)
#define SYS_CRT_BISR_ST1_vcpu_bisr_fail(data)                                        (0x10000000&((data)<<28))
#define SYS_CRT_BISR_ST1_vcpu_bisr_fail_src(data)                                    ((0x10000000&(data))>>28)
#define SYS_CRT_BISR_ST1_get_vcpu_bisr_fail(data)                                    ((0x10000000&(data))>>28)
#define SYS_CRT_BISR_ST1_cp42k_bisr_fail_shift                                       (3)
#define SYS_CRT_BISR_ST1_cp42k_bisr_fail_mask                                        (0x00000008)
#define SYS_CRT_BISR_ST1_cp42k_bisr_fail(data)                                       (0x00000008&((data)<<3))
#define SYS_CRT_BISR_ST1_cp42k_bisr_fail_src(data)                                   ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_ST1_get_cp42k_bisr_fail(data)                                   ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_ST1_kcpu_bisr_st_shift                                          (2)
#define SYS_CRT_BISR_ST1_kcpu_bisr_st_mask                                           (0x00000004)
#define SYS_CRT_BISR_ST1_kcpu_bisr_st(data)                                          (0x00000004&((data)<<2))
#define SYS_CRT_BISR_ST1_kcpu_bisr_st_src(data)                                      ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_ST1_get_kcpu_bisr_st(data)                                      ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_ST1_acpu_bisr_st_shift                                          (0)
#define SYS_CRT_BISR_ST1_acpu_bisr_st_mask                                           (0x00000001)
#define SYS_CRT_BISR_ST1_acpu_bisr_st(data)                                          (0x00000001&((data)<<0))
#define SYS_CRT_BISR_ST1_acpu_bisr_st_src(data)                                      ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_ST1_get_acpu_bisr_st(data)                                      ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_REPAIRED1                                                       0x18000720
#define SYS_CRT_BISR_REPAIRED1_reg_addr                                              "0xB8000720"
#define SYS_CRT_BISR_REPAIRED1_reg                                                   0xB8000720
#define set_SYS_CRT_BISR_REPAIRED1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_REPAIRED1_reg)=data)
#define get_SYS_CRT_BISR_REPAIRED1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_REPAIRED1_reg))
#define SYS_CRT_BISR_REPAIRED1_inst_adr                                              "0x00C8"
#define SYS_CRT_BISR_REPAIRED1_inst                                                  0x00C8
#define SYS_CRT_BISR_REPAIRED1_cp42k_bisr_repaired_shift                             (3)
#define SYS_CRT_BISR_REPAIRED1_cp42k_bisr_repaired_mask                              (0x00000008)
#define SYS_CRT_BISR_REPAIRED1_cp42k_bisr_repaired(data)                             (0x00000008&((data)<<3))
#define SYS_CRT_BISR_REPAIRED1_cp42k_bisr_repaired_src(data)                         ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_REPAIRED1_get_cp42k_bisr_repaired(data)                         ((0x00000008&(data))>>3)
#define SYS_CRT_BISR_REPAIRED1_kcpu_bisr_repaired_shift                              (2)
#define SYS_CRT_BISR_REPAIRED1_kcpu_bisr_repaired_mask                               (0x00000004)
#define SYS_CRT_BISR_REPAIRED1_kcpu_bisr_repaired(data)                              (0x00000004&((data)<<2))
#define SYS_CRT_BISR_REPAIRED1_kcpu_bisr_repaired_src(data)                          ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_REPAIRED1_get_kcpu_bisr_repaired(data)                          ((0x00000004&(data))>>2)
#define SYS_CRT_BISR_REPAIRED1_vcpu_bisr_repaired_shift                              (1)
#define SYS_CRT_BISR_REPAIRED1_vcpu_bisr_repaired_mask                               (0x00000002)
#define SYS_CRT_BISR_REPAIRED1_vcpu_bisr_repaired(data)                              (0x00000002&((data)<<1))
#define SYS_CRT_BISR_REPAIRED1_vcpu_bisr_repaired_src(data)                          ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_REPAIRED1_get_vcpu_bisr_repaired(data)                          ((0x00000002&(data))>>1)
#define SYS_CRT_BISR_REPAIRED1_acpu_bisr_repaired_shift                              (0)
#define SYS_CRT_BISR_REPAIRED1_acpu_bisr_repaired_mask                               (0x00000001)
#define SYS_CRT_BISR_REPAIRED1_acpu_bisr_repaired(data)                              (0x00000001&((data)<<0))
#define SYS_CRT_BISR_REPAIRED1_acpu_bisr_repaired_src(data)                          ((0x00000001&(data))>>0)
#define SYS_CRT_BISR_REPAIRED1_get_acpu_bisr_repaired(data)                          ((0x00000001&(data))>>0)


#define SYS_CRT_BISR_OUT1                                                            0x18000730
#define SYS_CRT_BISR_OUT1_reg_addr                                                   "0xB8000730"
#define SYS_CRT_BISR_OUT1_reg                                                        0xB8000730
#define set_SYS_CRT_BISR_OUT1_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_OUT1_reg)=data)
#define get_SYS_CRT_BISR_OUT1_reg   (*((volatile unsigned int*) SYS_CRT_BISR_OUT1_reg))
#define SYS_CRT_BISR_OUT1_inst_adr                                                   "0x00CC"
#define SYS_CRT_BISR_OUT1_inst                                                       0x00CC
#define SYS_CRT_BISR_OUT1_vcpu_bisr_out_shift                                        (0)
#define SYS_CRT_BISR_OUT1_vcpu_bisr_out_mask                                         (0x0FFFFFFF)
#define SYS_CRT_BISR_OUT1_vcpu_bisr_out(data)                                        (0x0FFFFFFF&((data)<<0))
#define SYS_CRT_BISR_OUT1_vcpu_bisr_out_src(data)                                    ((0x0FFFFFFF&(data))>>0)
#define SYS_CRT_BISR_OUT1_get_vcpu_bisr_out(data)                                    ((0x0FFFFFFF&(data))>>0)


#define SYS_CRT_BISR_OUT2                                                            0x18000734
#define SYS_CRT_BISR_OUT2_reg_addr                                                   "0xB8000734"
#define SYS_CRT_BISR_OUT2_reg                                                        0xB8000734
#define set_SYS_CRT_BISR_OUT2_reg(data)   (*((volatile unsigned int*) SYS_CRT_BISR_OUT2_reg)=data)
#define get_SYS_CRT_BISR_OUT2_reg   (*((volatile unsigned int*) SYS_CRT_BISR_OUT2_reg))
#define SYS_CRT_BISR_OUT2_inst_adr                                                   "0x00CD"
#define SYS_CRT_BISR_OUT2_inst                                                       0x00CD
#define SYS_CRT_BISR_OUT2_cp42k_bisr_out_shift                                       (0)
#define SYS_CRT_BISR_OUT2_cp42k_bisr_out_mask                                        (0x0000007F)
#define SYS_CRT_BISR_OUT2_cp42k_bisr_out(data)                                       (0x0000007F&((data)<<0))
#define SYS_CRT_BISR_OUT2_cp42k_bisr_out_src(data)                                   ((0x0000007F&(data))>>0)
#define SYS_CRT_BISR_OUT2_get_cp42k_bisr_out(data)                                   ((0x0000007F&(data))>>0)


#define SYS_CRT_DRF_BISR_ST1                                                         0x18000750
#define SYS_CRT_DRF_BISR_ST1_reg_addr                                                "0xB8000750"
#define SYS_CRT_DRF_BISR_ST1_reg                                                     0xB8000750
#define set_SYS_CRT_DRF_BISR_ST1_reg(data)   (*((volatile unsigned int*) SYS_CRT_DRF_BISR_ST1_reg)=data)
#define get_SYS_CRT_DRF_BISR_ST1_reg   (*((volatile unsigned int*) SYS_CRT_DRF_BISR_ST1_reg))
#define SYS_CRT_DRF_BISR_ST1_inst_adr                                                "0x00D4"
#define SYS_CRT_DRF_BISR_ST1_inst                                                    0x00D4
#define SYS_CRT_DRF_BISR_ST1_vcpu_drf_bisr_fail_shift                                (28)
#define SYS_CRT_DRF_BISR_ST1_vcpu_drf_bisr_fail_mask                                 (0x10000000)
#define SYS_CRT_DRF_BISR_ST1_vcpu_drf_bisr_fail(data)                                (0x10000000&((data)<<28))
#define SYS_CRT_DRF_BISR_ST1_vcpu_drf_bisr_fail_src(data)                            ((0x10000000&(data))>>28)
#define SYS_CRT_DRF_BISR_ST1_get_vcpu_drf_bisr_fail(data)                            ((0x10000000&(data))>>28)
#define SYS_CRT_DRF_BISR_ST1_cp42k_drf_bisr_fail_shift                               (3)
#define SYS_CRT_DRF_BISR_ST1_cp42k_drf_bisr_fail_mask                                (0x00000008)
#define SYS_CRT_DRF_BISR_ST1_cp42k_drf_bisr_fail(data)                               (0x00000008&((data)<<3))
#define SYS_CRT_DRF_BISR_ST1_cp42k_drf_bisr_fail_src(data)                           ((0x00000008&(data))>>3)
#define SYS_CRT_DRF_BISR_ST1_get_cp42k_drf_bisr_fail(data)                           ((0x00000008&(data))>>3)


#endif

// This file is generated using the spec version 1.39, firmware template version 1.39and SRIF Parser                                                                                source code SVN rev:802                    Version flow no.:1.1.68
#ifndef _CRT_REG_H_INCLUDED_
#define _CRT_REG_H_INCLUDED_

//#define  _CRT_USE_STRUCT
#ifdef _CRT_USE_STRUCT

typedef struct
{
    unsigned int    reserved_0:1;
    unsigned int    pll512fs_n:3;
    unsigned int    reserved_1:1;
    unsigned int    pll512fs_m:7;
    unsigned int    pll512fs_bpn:1;
    unsigned int    pll512fs_bps:1;
    unsigned int    pll512fs_cs:2;
    unsigned int    reserved_2:1;
    unsigned int    pll512fs_ip:3;
    unsigned int    pll512fs_s:3;
    unsigned int    pll512fs_q:3;
    unsigned int    pll512fs_rs:3;
    unsigned int    pll512fs_tst:1;
    unsigned int    pll512fs_wdrst:1;
    unsigned int    pll512fs_wdset:1;
}SYS_pll_512fs1;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    pll512fs_oeb:1;
    unsigned int    pll512fs_rstb:1;
    unsigned int    pll512fs_pow:1;
}SYS_pll_512fs2;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    plldif_n:2;
    unsigned int    reserved_1:1;
    unsigned int    plldif_m:7;
    unsigned int    reserved_2:1;
    unsigned int    plldif_ip:3;
    unsigned int    plldif_lf_rs:2;
    unsigned int    plldif_lf_cp:2;
    unsigned int    reserved_3:1;
    unsigned int    reserved_4:11;
}SYS_pll_dif1;

typedef struct
{
    unsigned int    reserved_0:19;
    unsigned int    reserved_1:1;
    unsigned int    reserved_2:2;
    unsigned int    plldif_wdmode:2;
    unsigned int    reserved_3:1;
    unsigned int    plldif_divdig_sel:3;
    unsigned int    reserved_4:1;
    unsigned int    plldif_divadc_sel:3;
}SYS_pll_dif2;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    plldif_vco_rstb:1;
    unsigned int    plldif_rstb:1;
    unsigned int    plldif_pow:1;
}SYS_pll_dif3;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    pll27x_wdmode:2;
    unsigned int    reserved_1:2;
    unsigned int    pll27x_lf_cp:2;
    unsigned int    reserved_2:2;
    unsigned int    pll27x_lf_rs:2;
    unsigned int    reserved_3:1;
    unsigned int    pll27x_ip:3;
    unsigned int    reserved_4:6;
    unsigned int    pll27x_n:2;
    unsigned int    reserved_5:1;
    unsigned int    pll27x_m:7;
}SYS_pll_27x1;

typedef struct
{
    unsigned int    reserved_0:10;
    unsigned int    pll_ldo_xtal_sel:2;
    unsigned int    reserved_1:1;
    unsigned int    pll_xixo_load:1;
    unsigned int    pll_xixo_drive_sel:2;
    unsigned int    reserved_2:1;
    unsigned int    pll_pow_ldo11v:1;
    unsigned int    pll_ldo11v_sel:2;
    unsigned int    reserved_3:1;
    unsigned int    pll_pow_ldo:1;
    unsigned int    pll_ldo_sel:2;
    unsigned int    reserved_4:2;
    unsigned int    pll27x_ps_54m_delay:2;
    unsigned int    reserved_5:2;
    unsigned int    pll27x_ps_psel_pulse_w:1;
    unsigned int    pll27x_ps_duty_sel:1;
}SYS_pll_27x2;

typedef struct
{
    unsigned int    reserved_0:16;
    unsigned int    pll_reserve:8;
    unsigned int    reserved_1:3;
    unsigned int    pll27x_ps_en:1;
    unsigned int    pll27x_ps_div2:1;
    unsigned int    pll27x_vcorstb:1;
    unsigned int    pll27x_rstb:1;
    unsigned int    pll27x_pow:1;
}SYS_pll_27x3;

typedef struct
{
    unsigned int    reserved_0:1;
    unsigned int    pll27x_ifadc_duty:2;
    unsigned int    pll_yppadc_cko_54m_polar:1;
    unsigned int    pll_yppadc_cko_polar:1;
    unsigned int    pll_ifadc_cko_polar:1;
    unsigned int    pll_l2h_cml_pow:1;
    unsigned int    pll27x_d16_en:1;
    unsigned int    pll27x_pll_tst:3;
    unsigned int    pll27x_en_tst:1;
    unsigned int    pll_rssi_cko_en:1;
    unsigned int    pll27x_ck108m_en:1;
    unsigned int    pll27x_ck108m_div:2;
    unsigned int    pll27x_yppadc_cko_sel:2;
    unsigned int    pll27x_yppadc_cko_en:1;
    unsigned int    pll27x_yppadc_ck54m_en:1;
    unsigned int    pll27x_ifadc_cko_sel:2;
    unsigned int    pll27x_ifadc_div:1;
    unsigned int    pll27x_ifadc_cko_en:1;
    unsigned int    reserved_1:2;
    unsigned int    reserved_2:1;
    unsigned int    pllaud_ckin_mux:1;
    unsigned int    reserved_3:1;
    unsigned int    pll27x_dvb_s2_demod_324m_div:1;
    unsigned int    pll27x_dvb_s2_demod_324m_en:1;
    unsigned int    pll_ck_ifadc_mux:1;
}SYS_pll_27x4;

typedef struct
{
    unsigned int    reserved_0:14;
    unsigned int    pllaud_ip:3;
    unsigned int    reserved_1:1;
    unsigned int    pllaud_rs:3;
    unsigned int    reserved_2:1;
    unsigned int    pllaud_cs:2;
    unsigned int    reserved_3:3;
    unsigned int    reserved_4:1;
    unsigned int    reserved_5:1;
    unsigned int    pllaud_wdrst:1;
    unsigned int    pllaud_wdset:1;
    unsigned int    pllaud_tst:1;
}SYS_pll_aud1;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    pllaud_rstb:1;
    unsigned int    pllaud_oeb1:1;
    unsigned int    pllaud_oeb2:1;
    unsigned int    pllaud_pwdn:1;
}SYS_pll_aud3;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    psaud_psen:1;
    unsigned int    psaud_en:1;
    unsigned int    psaud_tst:1;
    unsigned int    psaud_ctrl:1;
}SYS_pll_psaud1;

typedef struct
{
    unsigned int    reserved_0:28;
    unsigned int    psaud_div:4;
}SYS_pll_psaud2;

typedef struct
{
    unsigned int    reg_dpi_pll_dbug_en:1;
    unsigned int    reserved_0:1;
    unsigned int    reg_dpi_oesync_op_sel:10;
    unsigned int    reg_dpi_pdiv:2;
    unsigned int    reg_dpi_clk_oe:10;
    unsigned int    reserved_1:1;
    unsigned int    reg_dpi_mck_clk_en:7;
}SYS_pll_ddr1;

typedef struct
{
    unsigned int    reg_dpi_en_post_pi:10;
    unsigned int    reserved_0:1;
    unsigned int    reg_dpi_post_pi_rs:1;
    unsigned int    reg_dpi_pll_sel_cpmode:1;
    unsigned int    reg_dpi_cco_band:2;
    unsigned int    reg_dpi_cco_kvco:1;
    unsigned int    reg_dpi_icp:4;
    unsigned int    reg_dpi_post_pi_bias:2;
    unsigned int    reg_dpi_post_pi_rl:2;
    unsigned int    reg_dpi_pll_ldo_vsel:2;
    unsigned int    reg_dpi_lpf_sr:3;
    unsigned int    reg_dpi_lpf_cp:1;
    unsigned int    reg_dpi_loop_pi_isel:2;
}SYS_pll_ddr2;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    reg_dpi_post_pi_sel3:6;
    unsigned int    reserved_1:2;
    unsigned int    reg_dpi_post_pi_sel2:6;
    unsigned int    reserved_2:2;
    unsigned int    reg_dpi_post_pi_sel1:6;
    unsigned int    reserved_3:2;
    unsigned int    reg_dpi_post_pi_sel0:6;
}SYS_pll_ddr3;

typedef struct
{
    unsigned int    reserved_0:2;
    unsigned int    reg_dpi_post_pi_sel7:6;
    unsigned int    reserved_1:2;
    unsigned int    reg_dpi_post_pi_sel6:6;
    unsigned int    reserved_2:2;
    unsigned int    reg_dpi_post_pi_sel5:6;
    unsigned int    reserved_3:2;
    unsigned int    reg_dpi_post_pi_sel4:6;
}SYS_pll_ddr4;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    reg_dpi_post_pi_sel9:6;
    unsigned int    reserved_1:2;
    unsigned int    reg_dpi_post_pi_sel8:6;
    unsigned int    reserved_2:2;
    unsigned int    reg_dpi_f390k:2;
    unsigned int    reg_dpi_wd_enable:1;
    unsigned int    reg_dpi_time2_rst_width:2;
    unsigned int    reg_dpi_time_rdy_ckout:2;
    unsigned int    reg_dpi_time0_ck:3;
}SYS_pll_ddr_ssc1;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    reg_dpi_sel_mode:1;
    unsigned int    reg_dpi_n_code:8;
    unsigned int    reserved_1:3;
    unsigned int    reg_dpi_f_code:13;
    unsigned int    reserved_2:1;
    unsigned int    reg_dpi_en_ssc:1;
    unsigned int    reg_dpi_bypass_pi:1;
    unsigned int    reg_dpi_en_center_in:1;
}SYS_pll_ddr_ssc2;

typedef struct
{
    unsigned int    reg_dpi_weighting_sel:3;
    unsigned int    reg_dpi_order:1;
    unsigned int    reg_dpi_tbase:12;
    unsigned int    reserved_0:3;
    unsigned int    reg_dpi_step_in:13;
}SYS_pll_ddr_ssc3;

typedef struct
{
    unsigned int    reserved_0:24;
    unsigned int    reg_dpi_pll_dum:8;
}SYS_pll_ddr5;

typedef struct
{
    unsigned int    reserved_0:31;
    unsigned int    pll_stable:1;
}SYS_pll_ddr5_1;

typedef struct
{
    unsigned int    dpi_dummy_in_dll:32;
}SYS_pll_dummy_in;

typedef struct
{
    unsigned int    dpi_dummy_out_dll:32;
}SYS_pll_dummy_out;

typedef struct
{
    unsigned int    dclk_field_flag_mode_en:1;
    unsigned int    dclk_filed_flag_slt:3;
    unsigned int    dclk_offset:12;
    unsigned int    dclk_new_en:1;
    unsigned int    dclk_ss_test:1;
    unsigned int    dclk_freq_syn_slt:6;
    unsigned int    dclk_ss_rag:4;
    unsigned int    dummy300_3:1;
    unsigned int    dclk_ss_load:1;
    unsigned int    dummy300_1:1;
    unsigned int    dclk_ss_en:1;
}SYS_dclkss;

typedef struct
{
    unsigned int    sscg_mcode_slow_modify_valid:1;
    unsigned int    sscg_mcode_slow_modify_stable:1;
    unsigned int    sscg_mcode_slow_modify_pixel:12;
    unsigned int    sscg_offset_slow_modify_valid:1;
    unsigned int    sscg_offset_slow_modify_stable:1;
    unsigned int    sscg_offset_slow_modify_pixel:12;
    unsigned int    in_frame_tracking_offset_inverse:1;
    unsigned int    in_frame_tracking_ypbpr_en:1;
    unsigned int    in_frame_tracking_vd_dec_en:1;
    unsigned int    in_frame_tracking_general_en:1;
}DPLL_in_fsync_tracking_ctrl;

typedef struct
{
    unsigned int    in_frame_tracking_neg_th:12;
    unsigned int    in_frame_tracking_pos_th:12;
    unsigned int    in_frame_tracking_mul:8;
}DPLL_in_fsync_tracking_ctrl2;

typedef struct
{
    unsigned int    sscg_offset_over_flag:1;
    unsigned int    sscg_profile_over_underflow_flag:1;
    unsigned int    sscg_profile_protection:1;
    unsigned int    sscg_offset_over_th_max:13;
    unsigned int    dpll_mcode_protection:1;
    unsigned int    dpll_mcode_protection_ready_width:2;
    unsigned int    sscg_offset_over_th_value:13;
}DPLL_in_fsync_tracking_debug;

typedef struct
{
    unsigned int    reserved_0:13;
    unsigned int    frc2fsync_speedup_m_code:3;
    unsigned int    reserved_1:5;
    unsigned int    frc2fsync_speedup_offset:11;
}DCLK_frc2fsync_speedup;

typedef struct
{
    unsigned int    reserved_0:6;
    unsigned int    final_m_code:10;
    unsigned int    reserved_1:3;
    unsigned int    final_profile:13;
}DPLL_status_ro;

typedef struct
{
    unsigned int    final_profile_force_64n_en:2;
    unsigned int    dclk_ss_async_protection:1;
    unsigned int    reserved_0:14;
    unsigned int    dclk_ss_fmdiv:7;
    unsigned int    reserved_1:1;
    unsigned int    dclk_ss_protection_cnt_max:7;
}DCLKSS_freq;

typedef struct
{
    unsigned int    dummy31c_31_30:2;
    unsigned int    dclk_ss_shuffle_en:1;
    unsigned int    dclk_profile_remap_en:1;
    unsigned int    dclk_profile_remap_1:12;
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_0:12;
}DCLKSS_profile0;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_3:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_2:12;
}DCLKSS_profile1;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_5:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_4:12;
}DCLKSS_profile2;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_7:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_6:12;
}DCLKSS_profile3;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_9:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_8:12;
}DCLKSS_profile4;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_11:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_10:12;
}DCLKSS_profile5;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_13:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_12:12;
}DCLKSS_profile6;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_15:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_14:12;
}DCLKSS_profile7;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_17:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_16:12;
}DCLKSS_profile8;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_19:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_18:12;
}DCLKSS_profile9;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_21:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_20:12;
}DCLKSS_profile10;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_23:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_22:12;
}DCLKSS_profile11;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_25:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_24:12;
}DCLKSS_profile12;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_27:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_26:12;
}DCLKSS_profile13;

typedef struct
{
    unsigned int    reserved_0:4;
    unsigned int    dclk_profile_remap_29:12;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_28:12;
}DCLKSS_profile14;

typedef struct
{
    unsigned int    reserved_0:3;
    unsigned int    dclk_profile_remap_31:13;
    unsigned int    reserved_1:4;
    unsigned int    dclk_profile_remap_30:12;
}DCLKSS_profile15;

typedef struct
{
    unsigned int    reserved_0:29;
    unsigned int    double_buf_en:1;
    unsigned int    double_buf_read_sel:1;
    unsigned int    double_buf_apply:1;
}DPLL_double_buffer_ctrl;
#endif


#define SYS_PLL_512FS1                                                0x18000200
#define SYS_PLL_512FS1_reg_addr                                       "0xb8000200"
#define SYS_PLL_512FS1_reg                                            0xb8000200
#define SYS_PLL_512FS1_inst_addr                                      "0x0080"
#define SYS_PLL_512FS1_inst                                           0x0080
#define SYS_PLL_512FS1_pll512fs_n_shift                               (28)
#define SYS_PLL_512FS1_pll512fs_m_shift                               (20)
#define SYS_PLL_512FS1_pll512fs_bpn_shift                             (19)
#define SYS_PLL_512FS1_pll512fs_bps_shift                             (18)
#define SYS_PLL_512FS1_pll512fs_cs_shift                              (16)
#define SYS_PLL_512FS1_pll512fs_ip_shift                              (12)
#define SYS_PLL_512FS1_pll512fs_s_shift                               (9)
#define SYS_PLL_512FS1_pll512fs_q_shift                               (6)
#define SYS_PLL_512FS1_pll512fs_rs_shift                              (3)
#define SYS_PLL_512FS1_pll512fs_tst_shift                             (2)
#define SYS_PLL_512FS1_pll512fs_wdrst_shift                           (1)
#define SYS_PLL_512FS1_pll512fs_wdset_shift                           (0)
#define SYS_PLL_512FS1_pll512fs_n_mask                                (0x70000000)
#define SYS_PLL_512FS1_pll512fs_m_mask                                (0x07F00000)
#define SYS_PLL_512FS1_pll512fs_bpn_mask                              (0x00080000)
#define SYS_PLL_512FS1_pll512fs_bps_mask                              (0x00040000)
#define SYS_PLL_512FS1_pll512fs_cs_mask                               (0x00030000)
#define SYS_PLL_512FS1_pll512fs_ip_mask                               (0x00007000)
#define SYS_PLL_512FS1_pll512fs_s_mask                                (0x00000E00)
#define SYS_PLL_512FS1_pll512fs_q_mask                                (0x000001C0)
#define SYS_PLL_512FS1_pll512fs_rs_mask                               (0x00000038)
#define SYS_PLL_512FS1_pll512fs_tst_mask                              (0x00000004)
#define SYS_PLL_512FS1_pll512fs_wdrst_mask                            (0x00000002)
#define SYS_PLL_512FS1_pll512fs_wdset_mask                            (0x00000001)
#define SYS_PLL_512FS1_pll512fs_n(data)                               (0x70000000&((data)<<28))
#define SYS_PLL_512FS1_pll512fs_m(data)                               (0x07F00000&((data)<<20))
#define SYS_PLL_512FS1_pll512fs_bpn(data)                             (0x00080000&((data)<<19))
#define SYS_PLL_512FS1_pll512fs_bps(data)                             (0x00040000&((data)<<18))
#define SYS_PLL_512FS1_pll512fs_cs(data)                              (0x00030000&((data)<<16))
#define SYS_PLL_512FS1_pll512fs_ip(data)                              (0x00007000&((data)<<12))
#define SYS_PLL_512FS1_pll512fs_s(data)                               (0x00000E00&((data)<<9))
#define SYS_PLL_512FS1_pll512fs_q(data)                               (0x000001C0&((data)<<6))
#define SYS_PLL_512FS1_pll512fs_rs(data)                              (0x00000038&((data)<<3))
#define SYS_PLL_512FS1_pll512fs_tst(data)                             (0x00000004&((data)<<2))
#define SYS_PLL_512FS1_pll512fs_wdrst(data)                           (0x00000002&((data)<<1))
#define SYS_PLL_512FS1_pll512fs_wdset(data)                           (0x00000001&(data))
#define SYS_PLL_512FS1_get_pll512fs_n(data)                           ((0x70000000&(data))>>28)
#define SYS_PLL_512FS1_get_pll512fs_m(data)                           ((0x07F00000&(data))>>20)
#define SYS_PLL_512FS1_get_pll512fs_bpn(data)                         ((0x00080000&(data))>>19)
#define SYS_PLL_512FS1_get_pll512fs_bps(data)                         ((0x00040000&(data))>>18)
#define SYS_PLL_512FS1_get_pll512fs_cs(data)                          ((0x00030000&(data))>>16)
#define SYS_PLL_512FS1_get_pll512fs_ip(data)                          ((0x00007000&(data))>>12)
#define SYS_PLL_512FS1_get_pll512fs_s(data)                           ((0x00000E00&(data))>>9)
#define SYS_PLL_512FS1_get_pll512fs_q(data)                           ((0x000001C0&(data))>>6)
#define SYS_PLL_512FS1_get_pll512fs_rs(data)                          ((0x00000038&(data))>>3)
#define SYS_PLL_512FS1_get_pll512fs_tst(data)                         ((0x00000004&(data))>>2)
#define SYS_PLL_512FS1_get_pll512fs_wdrst(data)                       ((0x00000002&(data))>>1)
#define SYS_PLL_512FS1_get_pll512fs_wdset(data)                       (0x00000001&(data))


#define SYS_PLL_512FS2                                                0x18000204
#define SYS_PLL_512FS2_reg_addr                                       "0xb8000204"
#define SYS_PLL_512FS2_reg                                            0xb8000204
#define SYS_PLL_512FS2_inst_addr                                      "0x0081"
#define SYS_PLL_512FS2_inst                                           0x0081
#define SYS_PLL_512FS2_pll512fs_oeb_shift                             (2)
#define SYS_PLL_512FS2_pll512fs_rstb_shift                            (1)
#define SYS_PLL_512FS2_pll512fs_pow_shift                             (0)
#define SYS_PLL_512FS2_pll512fs_oeb_mask                              (0x00000004)
#define SYS_PLL_512FS2_pll512fs_rstb_mask                             (0x00000002)
#define SYS_PLL_512FS2_pll512fs_pow_mask                              (0x00000001)
#define SYS_PLL_512FS2_pll512fs_oeb(data)                             (0x00000004&((data)<<2))
#define SYS_PLL_512FS2_pll512fs_rstb(data)                            (0x00000002&((data)<<1))
#define SYS_PLL_512FS2_pll512fs_pow(data)                             (0x00000001&(data))
#define SYS_PLL_512FS2_get_pll512fs_oeb(data)                         ((0x00000004&(data))>>2)
#define SYS_PLL_512FS2_get_pll512fs_rstb(data)                        ((0x00000002&(data))>>1)
#define SYS_PLL_512FS2_get_pll512fs_pow(data)                         (0x00000001&(data))


#define SYS_PLL_DIF1                                                  0x18000220
#define SYS_PLL_DIF1_reg_addr                                         "0xb8000220"
#define SYS_PLL_DIF1_reg                                              0xb8000220
#define SYS_PLL_DIF1_inst_addr                                        "0x0088"
#define SYS_PLL_DIF1_inst                                             0x0088
#define SYS_PLL_DIF1_plldif_n_shift                                   (28)
#define SYS_PLL_DIF1_plldif_m_shift                                   (20)
#define SYS_PLL_DIF1_plldif_ip_shift                                  (16)
#define SYS_PLL_DIF1_plldif_lf_rs_shift                               (14)
#define SYS_PLL_DIF1_plldif_lf_cp_shift                               (12)
#define SYS_PLL_DIF1_plldif_n_mask                                    (0x30000000)
#define SYS_PLL_DIF1_plldif_m_mask                                    (0x07F00000)
#define SYS_PLL_DIF1_plldif_ip_mask                                   (0x00070000)
#define SYS_PLL_DIF1_plldif_lf_rs_mask                                (0x0000C000)
#define SYS_PLL_DIF1_plldif_lf_cp_mask                                (0x00003000)
#define SYS_PLL_DIF1_plldif_n(data)                                   (0x30000000&((data)<<28))
#define SYS_PLL_DIF1_plldif_m(data)                                   (0x07F00000&((data)<<20))
#define SYS_PLL_DIF1_plldif_ip(data)                                  (0x00070000&((data)<<16))
#define SYS_PLL_DIF1_plldif_lf_rs(data)                               (0x0000C000&((data)<<14))
#define SYS_PLL_DIF1_plldif_lf_cp(data)                               (0x00003000&((data)<<12))
#define SYS_PLL_DIF1_get_plldif_n(data)                               ((0x30000000&(data))>>28)
#define SYS_PLL_DIF1_get_plldif_m(data)                               ((0x07F00000&(data))>>20)
#define SYS_PLL_DIF1_get_plldif_ip(data)                              ((0x00070000&(data))>>16)
#define SYS_PLL_DIF1_get_plldif_lf_rs(data)                           ((0x0000C000&(data))>>14)
#define SYS_PLL_DIF1_get_plldif_lf_cp(data)                           ((0x00003000&(data))>>12)


#define SYS_PLL_DIF2                                                  0x18000224
#define SYS_PLL_DIF2_reg_addr                                         "0xb8000224"
#define SYS_PLL_DIF2_reg                                              0xb8000224
#define SYS_PLL_DIF2_inst_addr                                        "0x0089"
#define SYS_PLL_DIF2_inst                                             0x0089
#define SYS_PLL_DIF2_plldif_wdmode_shift                              (8)
#define SYS_PLL_DIF2_plldif_divdig_sel_shift                          (4)
#define SYS_PLL_DIF2_plldif_divadc_sel_shift                          (0)
#define SYS_PLL_DIF2_plldif_wdmode_mask                               (0x00000300)
#define SYS_PLL_DIF2_plldif_divdig_sel_mask                           (0x00000070)
#define SYS_PLL_DIF2_plldif_divadc_sel_mask                           (0x00000007)
#define SYS_PLL_DIF2_plldif_wdmode(data)                              (0x00000300&((data)<<8))
#define SYS_PLL_DIF2_plldif_divdig_sel(data)                          (0x00000070&((data)<<4))
#define SYS_PLL_DIF2_plldif_divadc_sel(data)                          (0x00000007&(data))
#define SYS_PLL_DIF2_get_plldif_wdmode(data)                          ((0x00000300&(data))>>8)
#define SYS_PLL_DIF2_get_plldif_divdig_sel(data)                      ((0x00000070&(data))>>4)
#define SYS_PLL_DIF2_get_plldif_divadc_sel(data)                      (0x00000007&(data))


#define SYS_PLL_DIF3                                                  0x18000228
#define SYS_PLL_DIF3_reg_addr                                         "0xb8000228"
#define SYS_PLL_DIF3_reg                                              0xb8000228
#define SYS_PLL_DIF3_inst_addr                                        "0x008A"
#define SYS_PLL_DIF3_inst                                             0x008A
#define SYS_PLL_DIF3_plldif_vco_rstb_shift                            (2)
#define SYS_PLL_DIF3_plldif_rstb_shift                                (1)
#define SYS_PLL_DIF3_plldif_pow_shift                                 (0)
#define SYS_PLL_DIF3_plldif_vco_rstb_mask                             (0x00000004)
#define SYS_PLL_DIF3_plldif_rstb_mask                                 (0x00000002)
#define SYS_PLL_DIF3_plldif_pow_mask                                  (0x00000001)
#define SYS_PLL_DIF3_plldif_vco_rstb(data)                            (0x00000004&((data)<<2))
#define SYS_PLL_DIF3_plldif_rstb(data)                                (0x00000002&((data)<<1))
#define SYS_PLL_DIF3_plldif_pow(data)                                 (0x00000001&(data))
#define SYS_PLL_DIF3_get_plldif_vco_rstb(data)                        ((0x00000004&(data))>>2)
#define SYS_PLL_DIF3_get_plldif_rstb(data)                            ((0x00000002&(data))>>1)
#define SYS_PLL_DIF3_get_plldif_pow(data)                             (0x00000001&(data))


#define SYS_PLL_27X1                                                  0x18000240
#define SYS_PLL_27X1_reg_addr                                         "0xb8000240"
#define SYS_PLL_27X1_reg                                              0xb8000240
#define SYS_PLL_27X1_inst_addr                                        "0x0090"
#define SYS_PLL_27X1_inst                                             0x0090
#define SYS_PLL_27X1_pll27x_wdmode_shift                              (28)
#define SYS_PLL_27X1_pll27x_lf_cp_shift                               (24)
#define SYS_PLL_27X1_pll27x_lf_rs_shift                               (20)
#define SYS_PLL_27X1_pll27x_ip_shift                                  (16)
#define SYS_PLL_27X1_pll27x_n_shift                                   (8)
#define SYS_PLL_27X1_pll27x_m_shift                                   (0)
#define SYS_PLL_27X1_pll27x_wdmode_mask                               (0x30000000)
#define SYS_PLL_27X1_pll27x_lf_cp_mask                                (0x03000000)
#define SYS_PLL_27X1_pll27x_lf_rs_mask                                (0x00300000)
#define SYS_PLL_27X1_pll27x_ip_mask                                   (0x00070000)
#define SYS_PLL_27X1_pll27x_n_mask                                    (0x00000300)
#define SYS_PLL_27X1_pll27x_m_mask                                    (0x0000007F)
#define SYS_PLL_27X1_pll27x_wdmode(data)                              (0x30000000&((data)<<28))
#define SYS_PLL_27X1_pll27x_lf_cp(data)                               (0x03000000&((data)<<24))
#define SYS_PLL_27X1_pll27x_lf_rs(data)                               (0x00300000&((data)<<20))
#define SYS_PLL_27X1_pll27x_ip(data)                                  (0x00070000&((data)<<16))
#define SYS_PLL_27X1_pll27x_n(data)                                   (0x00000300&((data)<<8))
#define SYS_PLL_27X1_pll27x_m(data)                                   (0x0000007F&(data))
#define SYS_PLL_27X1_get_pll27x_wdmode(data)                          ((0x30000000&(data))>>28)
#define SYS_PLL_27X1_get_pll27x_lf_cp(data)                           ((0x03000000&(data))>>24)
#define SYS_PLL_27X1_get_pll27x_lf_rs(data)                           ((0x00300000&(data))>>20)
#define SYS_PLL_27X1_get_pll27x_ip(data)                              ((0x00070000&(data))>>16)
#define SYS_PLL_27X1_get_pll27x_n(data)                               ((0x00000300&(data))>>8)
#define SYS_PLL_27X1_get_pll27x_m(data)                               (0x0000007F&(data))


#define SYS_PLL_27X2                                                  0x18000244
#define SYS_PLL_27X2_reg_addr                                         "0xb8000244"
#define SYS_PLL_27X2_reg                                              0xb8000244
#define SYS_PLL_27X2_inst_addr                                        "0x0091"
#define SYS_PLL_27X2_inst                                             0x0091
#define SYS_PLL_27X2_pll_ldo_xtal_sel_shift                           (20)
#define SYS_PLL_27X2_pll_xixo_load_shift                              (18)
#define SYS_PLL_27X2_pll_xixo_drive_sel_shift                         (16)
#define SYS_PLL_27X2_pll_pow_ldo11v_shift                             (14)
#define SYS_PLL_27X2_pll_ldo11v_sel_shift                             (12)
#define SYS_PLL_27X2_pll_pow_ldo_shift                                (10)
#define SYS_PLL_27X2_pll_ldo_sel_shift                                (8)
#define SYS_PLL_27X2_pll27x_ps_54m_delay_shift                        (4)
#define SYS_PLL_27X2_pll27x_ps_psel_pulse_w_shift                     (1)
#define SYS_PLL_27X2_pll27x_ps_duty_sel_shift                         (0)
#define SYS_PLL_27X2_pll_ldo_xtal_sel_mask                            (0x00300000)
#define SYS_PLL_27X2_pll_xixo_load_mask                               (0x00040000)
#define SYS_PLL_27X2_pll_xixo_drive_sel_mask                          (0x00030000)
#define SYS_PLL_27X2_pll_pow_ldo11v_mask                              (0x00004000)
#define SYS_PLL_27X2_pll_ldo11v_sel_mask                              (0x00003000)
#define SYS_PLL_27X2_pll_pow_ldo_mask                                 (0x00000400)
#define SYS_PLL_27X2_pll_ldo_sel_mask                                 (0x00000300)
#define SYS_PLL_27X2_pll27x_ps_54m_delay_mask                         (0x00000030)
#define SYS_PLL_27X2_pll27x_ps_psel_pulse_w_mask                      (0x00000002)
#define SYS_PLL_27X2_pll27x_ps_duty_sel_mask                          (0x00000001)
#define SYS_PLL_27X2_pll_ldo_xtal_sel(data)                           (0x00300000&((data)<<20))
#define SYS_PLL_27X2_pll_xixo_load(data)                              (0x00040000&((data)<<18))
#define SYS_PLL_27X2_pll_xixo_drive_sel(data)                         (0x00030000&((data)<<16))
#define SYS_PLL_27X2_pll_pow_ldo11v(data)                             (0x00004000&((data)<<14))
#define SYS_PLL_27X2_pll_ldo11v_sel(data)                             (0x00003000&((data)<<12))
#define SYS_PLL_27X2_pll_pow_ldo(data)                                (0x00000400&((data)<<10))
#define SYS_PLL_27X2_pll_ldo_sel(data)                                (0x00000300&((data)<<8))
#define SYS_PLL_27X2_pll27x_ps_54m_delay(data)                        (0x00000030&((data)<<4))
#define SYS_PLL_27X2_pll27x_ps_psel_pulse_w(data)                     (0x00000002&((data)<<1))
#define SYS_PLL_27X2_pll27x_ps_duty_sel(data)                         (0x00000001&(data))
#define SYS_PLL_27X2_get_pll_ldo_xtal_sel(data)                       ((0x00300000&(data))>>20)
#define SYS_PLL_27X2_get_pll_xixo_load(data)                          ((0x00040000&(data))>>18)
#define SYS_PLL_27X2_get_pll_xixo_drive_sel(data)                     ((0x00030000&(data))>>16)
#define SYS_PLL_27X2_get_pll_pow_ldo11v(data)                         ((0x00004000&(data))>>14)
#define SYS_PLL_27X2_get_pll_ldo11v_sel(data)                         ((0x00003000&(data))>>12)
#define SYS_PLL_27X2_get_pll_pow_ldo(data)                            ((0x00000400&(data))>>10)
#define SYS_PLL_27X2_get_pll_ldo_sel(data)                            ((0x00000300&(data))>>8)
#define SYS_PLL_27X2_get_pll27x_ps_54m_delay(data)                    ((0x00000030&(data))>>4)
#define SYS_PLL_27X2_get_pll27x_ps_psel_pulse_w(data)                 ((0x00000002&(data))>>1)
#define SYS_PLL_27X2_get_pll27x_ps_duty_sel(data)                     (0x00000001&(data))


#define SYS_PLL_27X3                                                  0x18000248
#define SYS_PLL_27X3_reg_addr                                         "0xb8000248"
#define SYS_PLL_27X3_reg                                              0xb8000248
#define SYS_PLL_27X3_inst_addr                                        "0x0092"
#define SYS_PLL_27X3_inst                                             0x0092
#define SYS_PLL_27X3_pll_reserve_shift                                (8)
#define SYS_PLL_27X3_pll27x_ps_en_shift                               (4)
#define SYS_PLL_27X3_pll27x_ps_div2_shift                             (3)
#define SYS_PLL_27X3_pll27x_vcorstb_shift                             (2)
#define SYS_PLL_27X3_pll27x_rstb_shift                                (1)
#define SYS_PLL_27X3_pll27x_pow_shift                                 (0)
#define SYS_PLL_27X3_pll_reserve_mask                                 (0x0000FF00)
#define SYS_PLL_27X3_pll27x_ps_en_mask                                (0x00000010)
#define SYS_PLL_27X3_pll27x_ps_div2_mask                              (0x00000008)
#define SYS_PLL_27X3_pll27x_vcorstb_mask                              (0x00000004)
#define SYS_PLL_27X3_pll27x_rstb_mask                                 (0x00000002)
#define SYS_PLL_27X3_pll27x_pow_mask                                  (0x00000001)
#define SYS_PLL_27X3_pll_reserve(data)                                (0x0000FF00&((data)<<8))
#define SYS_PLL_27X3_pll27x_ps_en(data)                               (0x00000010&((data)<<4))
#define SYS_PLL_27X3_pll27x_ps_div2(data)                             (0x00000008&((data)<<3))
#define SYS_PLL_27X3_pll27x_vcorstb(data)                             (0x00000004&((data)<<2))
#define SYS_PLL_27X3_pll27x_rstb(data)                                (0x00000002&((data)<<1))
#define SYS_PLL_27X3_pll27x_pow(data)                                 (0x00000001&(data))
#define SYS_PLL_27X3_get_pll_reserve(data)                            ((0x0000FF00&(data))>>8)
#define SYS_PLL_27X3_get_pll27x_ps_en(data)                           ((0x00000010&(data))>>4)
#define SYS_PLL_27X3_get_pll27x_ps_div2(data)                         ((0x00000008&(data))>>3)
#define SYS_PLL_27X3_get_pll27x_vcorstb(data)                         ((0x00000004&(data))>>2)
#define SYS_PLL_27X3_get_pll27x_rstb(data)                            ((0x00000002&(data))>>1)
#define SYS_PLL_27X3_get_pll27x_pow(data)                             (0x00000001&(data))


#define SYS_PLL_27X4                                                  0x1800024c
#define SYS_PLL_27X4_reg_addr                                         "0xb800024c"
#define SYS_PLL_27X4_reg                                              0xb800024c
#define SYS_PLL_27X4_inst_addr                                        "0x0093"
#define SYS_PLL_27X4_inst                                             0x0093
#define SYS_PLL_27X4_pll27x_ifadc_duty_shift                          (29)
#define SYS_PLL_27X4_pll_yppadc_cko_54m_polar_shift                   (28)
#define SYS_PLL_27X4_pll_yppadc_cko_polar_shift                       (27)
#define SYS_PLL_27X4_pll_ifadc_cko_polar_shift                        (26)
#define SYS_PLL_27X4_pll_l2h_cml_pow_shift                            (25)
#define SYS_PLL_27X4_pll27x_d16_en_shift                              (24)
#define SYS_PLL_27X4_pll27x_pll_tst_shift                             (21)
#define SYS_PLL_27X4_pll27x_en_tst_shift                              (20)
#define SYS_PLL_27X4_pll_rssi_cko_en_shift                            (19)
#define SYS_PLL_27X4_pll27x_ck108m_en_shift                           (18)
#define SYS_PLL_27X4_pll27x_ck108m_div_shift                          (16)
#define SYS_PLL_27X4_pll27x_yppadc_cko_sel_shift                      (14)
#define SYS_PLL_27X4_pll27x_yppadc_cko_en_shift                       (13)
#define SYS_PLL_27X4_pll27x_yppadc_ck54m_en_shift                     (12)
#define SYS_PLL_27X4_pll27x_ifadc_cko_sel_shift                       (10)
#define SYS_PLL_27X4_pll27x_ifadc_div_shift                           (9)
#define SYS_PLL_27X4_pll27x_ifadc_cko_en_shift                        (8)
#define SYS_PLL_27X4_pllaud_ckin_mux_shift                            (4)
#define SYS_PLL_27X4_pll27x_dvb_s2_demod_324m_div_shift               (2)
#define SYS_PLL_27X4_pll27x_dvb_s2_demod_324m_en_shift                (1)
#define SYS_PLL_27X4_pll_ck_ifadc_mux_shift                           (0)
#define SYS_PLL_27X4_pll27x_ifadc_duty_mask                           (0x60000000)
#define SYS_PLL_27X4_pll_yppadc_cko_54m_polar_mask                    (0x10000000)
#define SYS_PLL_27X4_pll_yppadc_cko_polar_mask                        (0x08000000)
#define SYS_PLL_27X4_pll_ifadc_cko_polar_mask                         (0x04000000)
#define SYS_PLL_27X4_pll_l2h_cml_pow_mask                             (0x02000000)
#define SYS_PLL_27X4_pll27x_d16_en_mask                               (0x01000000)
#define SYS_PLL_27X4_pll27x_pll_tst_mask                              (0x00E00000)
#define SYS_PLL_27X4_pll27x_en_tst_mask                               (0x00100000)
#define SYS_PLL_27X4_pll_rssi_cko_en_mask                             (0x00080000)
#define SYS_PLL_27X4_pll27x_ck108m_en_mask                            (0x00040000)
#define SYS_PLL_27X4_pll27x_ck108m_div_mask                           (0x00030000)
#define SYS_PLL_27X4_pll27x_yppadc_cko_sel_mask                       (0x0000C000)
#define SYS_PLL_27X4_pll27x_yppadc_cko_en_mask                        (0x00002000)
#define SYS_PLL_27X4_pll27x_yppadc_ck54m_en_mask                      (0x00001000)
#define SYS_PLL_27X4_pll27x_ifadc_cko_sel_mask                        (0x00000C00)
#define SYS_PLL_27X4_pll27x_ifadc_div_mask                            (0x00000200)
#define SYS_PLL_27X4_pll27x_ifadc_cko_en_mask                         (0x00000100)
#define SYS_PLL_27X4_pllaud_ckin_mux_mask                             (0x00000010)
#define SYS_PLL_27X4_pll27x_dvb_s2_demod_324m_div_mask                (0x00000004)
#define SYS_PLL_27X4_pll27x_dvb_s2_demod_324m_en_mask                 (0x00000002)
#define SYS_PLL_27X4_pll_ck_ifadc_mux_mask                            (0x00000001)
#define SYS_PLL_27X4_pll27x_ifadc_duty(data)                          (0x60000000&((data)<<29))
#define SYS_PLL_27X4_pll_yppadc_cko_54m_polar(data)                   (0x10000000&((data)<<28))
#define SYS_PLL_27X4_pll_yppadc_cko_polar(data)                       (0x08000000&((data)<<27))
#define SYS_PLL_27X4_pll_ifadc_cko_polar(data)                        (0x04000000&((data)<<26))
#define SYS_PLL_27X4_pll_l2h_cml_pow(data)                            (0x02000000&((data)<<25))
#define SYS_PLL_27X4_pll27x_d16_en(data)                              (0x01000000&((data)<<24))
#define SYS_PLL_27X4_pll27x_pll_tst(data)                             (0x00E00000&((data)<<21))
#define SYS_PLL_27X4_pll27x_en_tst(data)                              (0x00100000&((data)<<20))
#define SYS_PLL_27X4_pll_rssi_cko_en(data)                            (0x00080000&((data)<<19))
#define SYS_PLL_27X4_pll27x_ck108m_en(data)                           (0x00040000&((data)<<18))
#define SYS_PLL_27X4_pll27x_ck108m_div(data)                          (0x00030000&((data)<<16))
#define SYS_PLL_27X4_pll27x_yppadc_cko_sel(data)                      (0x0000C000&((data)<<14))
#define SYS_PLL_27X4_pll27x_yppadc_cko_en(data)                       (0x00002000&((data)<<13))
#define SYS_PLL_27X4_pll27x_yppadc_ck54m_en(data)                     (0x00001000&((data)<<12))
#define SYS_PLL_27X4_pll27x_ifadc_cko_sel(data)                       (0x00000C00&((data)<<10))
#define SYS_PLL_27X4_pll27x_ifadc_div(data)                           (0x00000200&((data)<<9))
#define SYS_PLL_27X4_pll27x_ifadc_cko_en(data)                        (0x00000100&((data)<<8))
#define SYS_PLL_27X4_pllaud_ckin_mux(data)                            (0x00000010&((data)<<4))
#define SYS_PLL_27X4_pll27x_dvb_s2_demod_324m_div(data)               (0x00000004&((data)<<2))
#define SYS_PLL_27X4_pll27x_dvb_s2_demod_324m_en(data)                (0x00000002&((data)<<1))
#define SYS_PLL_27X4_pll_ck_ifadc_mux(data)                           (0x00000001&(data))
#define SYS_PLL_27X4_get_pll27x_ifadc_duty(data)                      ((0x60000000&(data))>>29)
#define SYS_PLL_27X4_get_pll_yppadc_cko_54m_polar(data)               ((0x10000000&(data))>>28)
#define SYS_PLL_27X4_get_pll_yppadc_cko_polar(data)                   ((0x08000000&(data))>>27)
#define SYS_PLL_27X4_get_pll_ifadc_cko_polar(data)                    ((0x04000000&(data))>>26)
#define SYS_PLL_27X4_get_pll_l2h_cml_pow(data)                        ((0x02000000&(data))>>25)
#define SYS_PLL_27X4_get_pll27x_d16_en(data)                          ((0x01000000&(data))>>24)
#define SYS_PLL_27X4_get_pll27x_pll_tst(data)                         ((0x00E00000&(data))>>21)
#define SYS_PLL_27X4_get_pll27x_en_tst(data)                          ((0x00100000&(data))>>20)
#define SYS_PLL_27X4_get_pll_rssi_cko_en(data)                        ((0x00080000&(data))>>19)
#define SYS_PLL_27X4_get_pll27x_ck108m_en(data)                       ((0x00040000&(data))>>18)
#define SYS_PLL_27X4_get_pll27x_ck108m_div(data)                      ((0x00030000&(data))>>16)
#define SYS_PLL_27X4_get_pll27x_yppadc_cko_sel(data)                  ((0x0000C000&(data))>>14)
#define SYS_PLL_27X4_get_pll27x_yppadc_cko_en(data)                   ((0x00002000&(data))>>13)
#define SYS_PLL_27X4_get_pll27x_yppadc_ck54m_en(data)                 ((0x00001000&(data))>>12)
#define SYS_PLL_27X4_get_pll27x_ifadc_cko_sel(data)                   ((0x00000C00&(data))>>10)
#define SYS_PLL_27X4_get_pll27x_ifadc_div(data)                       ((0x00000200&(data))>>9)
#define SYS_PLL_27X4_get_pll27x_ifadc_cko_en(data)                    ((0x00000100&(data))>>8)
#define SYS_PLL_27X4_get_pllaud_ckin_mux(data)                        ((0x00000010&(data))>>4)
#define SYS_PLL_27X4_get_pll27x_dvb_s2_demod_324m_div(data)           ((0x00000004&(data))>>2)
#define SYS_PLL_27X4_get_pll27x_dvb_s2_demod_324m_en(data)            ((0x00000002&(data))>>1)
#define SYS_PLL_27X4_get_pll_ck_ifadc_mux(data)                       (0x00000001&(data))


#define SYS_PLL_AUD1                                                  0x18000260
#define SYS_PLL_AUD1_reg_addr                                         "0xb8000260"
#define SYS_PLL_AUD1_reg                                              0xb8000260
#define SYS_PLL_AUD1_inst_addr                                        "0x0098"
#define SYS_PLL_AUD1_inst                                             0x0098
#define SYS_PLL_AUD1_pllaud_ip_shift                                  (15)
#define SYS_PLL_AUD1_pllaud_rs_shift                                  (11)
#define SYS_PLL_AUD1_pllaud_cs_shift                                  (8)
#define SYS_PLL_AUD1_pllaud_wdrst_shift                               (2)
#define SYS_PLL_AUD1_pllaud_wdset_shift                               (1)
#define SYS_PLL_AUD1_pllaud_tst_shift                                 (0)
#define SYS_PLL_AUD1_pllaud_ip_mask                                   (0x00038000)
#define SYS_PLL_AUD1_pllaud_rs_mask                                   (0x00003800)
#define SYS_PLL_AUD1_pllaud_cs_mask                                   (0x00000300)
#define SYS_PLL_AUD1_pllaud_wdrst_mask                                (0x00000004)
#define SYS_PLL_AUD1_pllaud_wdset_mask                                (0x00000002)
#define SYS_PLL_AUD1_pllaud_tst_mask                                  (0x00000001)
#define SYS_PLL_AUD1_pllaud_ip(data)                                  (0x00038000&((data)<<15))
#define SYS_PLL_AUD1_pllaud_rs(data)                                  (0x00003800&((data)<<11))
#define SYS_PLL_AUD1_pllaud_cs(data)                                  (0x00000300&((data)<<8))
#define SYS_PLL_AUD1_pllaud_wdrst(data)                               (0x00000004&((data)<<2))
#define SYS_PLL_AUD1_pllaud_wdset(data)                               (0x00000002&((data)<<1))
#define SYS_PLL_AUD1_pllaud_tst(data)                                 (0x00000001&(data))
#define SYS_PLL_AUD1_get_pllaud_ip(data)                              ((0x00038000&(data))>>15)
#define SYS_PLL_AUD1_get_pllaud_rs(data)                              ((0x00003800&(data))>>11)
#define SYS_PLL_AUD1_get_pllaud_cs(data)                              ((0x00000300&(data))>>8)
#define SYS_PLL_AUD1_get_pllaud_wdrst(data)                           ((0x00000004&(data))>>2)
#define SYS_PLL_AUD1_get_pllaud_wdset(data)                           ((0x00000002&(data))>>1)
#define SYS_PLL_AUD1_get_pllaud_tst(data)                             (0x00000001&(data))


#define SYS_PLL_AUD3                                                  0x18000264
#define SYS_PLL_AUD3_reg_addr                                         "0xb8000264"
#define SYS_PLL_AUD3_reg                                              0xb8000264
#define SYS_PLL_AUD3_inst_addr                                        "0x0099"
#define SYS_PLL_AUD3_inst                                             0x0099
#define SYS_PLL_AUD3_pllaud_rstb_shift                                (3)
#define SYS_PLL_AUD3_pllaud_oeb1_shift                                (2)
#define SYS_PLL_AUD3_pllaud_oeb2_shift                                (1)
#define SYS_PLL_AUD3_pllaud_pwdn_shift                                (0)
#define SYS_PLL_AUD3_pllaud_rstb_mask                                 (0x00000008)
#define SYS_PLL_AUD3_pllaud_oeb1_mask                                 (0x00000004)
#define SYS_PLL_AUD3_pllaud_oeb2_mask                                 (0x00000002)
#define SYS_PLL_AUD3_pllaud_pwdn_mask                                 (0x00000001)
#define SYS_PLL_AUD3_pllaud_rstb(data)                                (0x00000008&((data)<<3))
#define SYS_PLL_AUD3_pllaud_oeb1(data)                                (0x00000004&((data)<<2))
#define SYS_PLL_AUD3_pllaud_oeb2(data)                                (0x00000002&((data)<<1))
#define SYS_PLL_AUD3_pllaud_pwdn(data)                                (0x00000001&(data))
#define SYS_PLL_AUD3_get_pllaud_rstb(data)                            ((0x00000008&(data))>>3)
#define SYS_PLL_AUD3_get_pllaud_oeb1(data)                            ((0x00000004&(data))>>2)
#define SYS_PLL_AUD3_get_pllaud_oeb2(data)                            ((0x00000002&(data))>>1)
#define SYS_PLL_AUD3_get_pllaud_pwdn(data)                            (0x00000001&(data))


#define SYS_PLL_PSAUD1                                                0x18000280
#define SYS_PLL_PSAUD1_reg_addr                                       "0xb8000280"
#define SYS_PLL_PSAUD1_reg                                            0xb8000280
#define SYS_PLL_PSAUD1_inst_addr                                      "0x00A0"
#define SYS_PLL_PSAUD1_inst                                           0x00A0
#define SYS_PLL_PSAUD1_psaud_psen_shift                               (3)
#define SYS_PLL_PSAUD1_psaud_en_shift                                 (2)
#define SYS_PLL_PSAUD1_psaud_tst_shift                                (1)
#define SYS_PLL_PSAUD1_psaud_ctrl_shift                               (0)
#define SYS_PLL_PSAUD1_psaud_psen_mask                                (0x00000008)
#define SYS_PLL_PSAUD1_psaud_en_mask                                  (0x00000004)
#define SYS_PLL_PSAUD1_psaud_tst_mask                                 (0x00000002)
#define SYS_PLL_PSAUD1_psaud_ctrl_mask                                (0x00000001)
#define SYS_PLL_PSAUD1_psaud_psen(data)                               (0x00000008&((data)<<3))
#define SYS_PLL_PSAUD1_psaud_en(data)                                 (0x00000004&((data)<<2))
#define SYS_PLL_PSAUD1_psaud_tst(data)                                (0x00000002&((data)<<1))
#define SYS_PLL_PSAUD1_psaud_ctrl(data)                               (0x00000001&(data))
#define SYS_PLL_PSAUD1_get_psaud_psen(data)                           ((0x00000008&(data))>>3)
#define SYS_PLL_PSAUD1_get_psaud_en(data)                             ((0x00000004&(data))>>2)
#define SYS_PLL_PSAUD1_get_psaud_tst(data)                            ((0x00000002&(data))>>1)
#define SYS_PLL_PSAUD1_get_psaud_ctrl(data)                           (0x00000001&(data))


#define SYS_PLL_PSAUD2                                                0x18000284
#define SYS_PLL_PSAUD2_reg_addr                                       "0xb8000284"
#define SYS_PLL_PSAUD2_reg                                            0xb8000284
#define SYS_PLL_PSAUD2_inst_addr                                      "0x00A1"
#define SYS_PLL_PSAUD2_inst                                           0x00A1
#define SYS_PLL_PSAUD2_psaud_div_shift                                (0)
#define SYS_PLL_PSAUD2_psaud_div_mask                                 (0x0000000F)
#define SYS_PLL_PSAUD2_psaud_div(data)                                (0x0000000F&(data))
#define SYS_PLL_PSAUD2_get_psaud_div(data)                            (0x0000000F&(data))


#define SYS_PLL_DDR1                                                  0x180002c0
#define SYS_PLL_DDR1_reg_addr                                         "0xb80002c0"
#define SYS_PLL_DDR1_reg                                              0xb80002c0
#define SYS_PLL_DDR1_inst_addr                                        "0x00B0"
#define SYS_PLL_DDR1_inst                                             0x00B0
#define SYS_PLL_DDR1_reg_dpi_pll_dbug_en_shift                        (31)
#define SYS_PLL_DDR1_reg_dpi_oesync_op_sel_shift                      (20)
#define SYS_PLL_DDR1_reg_dpi_pdiv_shift                               (18)
#define SYS_PLL_DDR1_reg_dpi_clk_oe_shift                             (8)
#define SYS_PLL_DDR1_reg_dpi_mck_clk_en_shift                         (0)
#define SYS_PLL_DDR1_reg_dpi_pll_dbug_en_mask                         (0x80000000)
#define SYS_PLL_DDR1_reg_dpi_oesync_op_sel_mask                       (0x3FF00000)
#define SYS_PLL_DDR1_reg_dpi_pdiv_mask                                (0x000C0000)
#define SYS_PLL_DDR1_reg_dpi_clk_oe_mask                              (0x0003FF00)
#define SYS_PLL_DDR1_reg_dpi_mck_clk_en_mask                          (0x0000007F)
#define SYS_PLL_DDR1_reg_dpi_pll_dbug_en(data)                        (0x80000000&((data)<<31))
#define SYS_PLL_DDR1_reg_dpi_oesync_op_sel(data)                      (0x3FF00000&((data)<<20))
#define SYS_PLL_DDR1_reg_dpi_pdiv(data)                               (0x000C0000&((data)<<18))
#define SYS_PLL_DDR1_reg_dpi_clk_oe(data)                             (0x0003FF00&((data)<<8))
#define SYS_PLL_DDR1_reg_dpi_mck_clk_en(data)                         (0x0000007F&(data))
#define SYS_PLL_DDR1_get_reg_dpi_pll_dbug_en(data)                    ((0x80000000&(data))>>31)
#define SYS_PLL_DDR1_get_reg_dpi_oesync_op_sel(data)                  ((0x3FF00000&(data))>>20)
#define SYS_PLL_DDR1_get_reg_dpi_pdiv(data)                           ((0x000C0000&(data))>>18)
#define SYS_PLL_DDR1_get_reg_dpi_clk_oe(data)                         ((0x0003FF00&(data))>>8)
#define SYS_PLL_DDR1_get_reg_dpi_mck_clk_en(data)                     (0x0000007F&(data))


#define SYS_PLL_DDR2                                                  0x180002c4
#define SYS_PLL_DDR2_reg_addr                                         "0xb80002c4"
#define SYS_PLL_DDR2_reg                                              0xb80002c4
#define SYS_PLL_DDR2_inst_addr                                        "0x00B1"
#define SYS_PLL_DDR2_inst                                             0x00B1
#define SYS_PLL_DDR2_reg_dpi_en_post_pi_shift                         (22)
#define SYS_PLL_DDR2_reg_dpi_post_pi_rs_shift                         (20)
#define SYS_PLL_DDR2_reg_dpi_pll_sel_cpmode_shift                     (19)
#define SYS_PLL_DDR2_reg_dpi_cco_band_shift                           (17)
#define SYS_PLL_DDR2_reg_dpi_cco_kvco_shift                           (16)
#define SYS_PLL_DDR2_reg_dpi_icp_shift                                (12)
#define SYS_PLL_DDR2_reg_dpi_post_pi_bias_shift                       (10)
#define SYS_PLL_DDR2_reg_dpi_post_pi_rl_shift                         (8)
#define SYS_PLL_DDR2_reg_dpi_pll_ldo_vsel_shift                       (6)
#define SYS_PLL_DDR2_reg_dpi_lpf_sr_shift                             (3)
#define SYS_PLL_DDR2_reg_dpi_lpf_cp_shift                             (2)
#define SYS_PLL_DDR2_reg_dpi_loop_pi_isel_shift                       (0)
#define SYS_PLL_DDR2_reg_dpi_en_post_pi_mask                          (0xFFC00000)
#define SYS_PLL_DDR2_reg_dpi_post_pi_rs_mask                          (0x00100000)
#define SYS_PLL_DDR2_reg_dpi_pll_sel_cpmode_mask                      (0x00080000)
#define SYS_PLL_DDR2_reg_dpi_cco_band_mask                            (0x00060000)
#define SYS_PLL_DDR2_reg_dpi_cco_kvco_mask                            (0x00010000)
#define SYS_PLL_DDR2_reg_dpi_icp_mask                                 (0x0000F000)
#define SYS_PLL_DDR2_reg_dpi_post_pi_bias_mask                        (0x00000C00)
#define SYS_PLL_DDR2_reg_dpi_post_pi_rl_mask                          (0x00000300)
#define SYS_PLL_DDR2_reg_dpi_pll_ldo_vsel_mask                        (0x000000C0)
#define SYS_PLL_DDR2_reg_dpi_lpf_sr_mask                              (0x00000038)
#define SYS_PLL_DDR2_reg_dpi_lpf_cp_mask                              (0x00000004)
#define SYS_PLL_DDR2_reg_dpi_loop_pi_isel_mask                        (0x00000003)
#define SYS_PLL_DDR2_reg_dpi_en_post_pi(data)                         (0xFFC00000&((data)<<22))
#define SYS_PLL_DDR2_reg_dpi_post_pi_rs(data)                         (0x00100000&((data)<<20))
#define SYS_PLL_DDR2_reg_dpi_pll_sel_cpmode(data)                     (0x00080000&((data)<<19))
#define SYS_PLL_DDR2_reg_dpi_cco_band(data)                           (0x00060000&((data)<<17))
#define SYS_PLL_DDR2_reg_dpi_cco_kvco(data)                           (0x00010000&((data)<<16))
#define SYS_PLL_DDR2_reg_dpi_icp(data)                                (0x0000F000&((data)<<12))
#define SYS_PLL_DDR2_reg_dpi_post_pi_bias(data)                       (0x00000C00&((data)<<10))
#define SYS_PLL_DDR2_reg_dpi_post_pi_rl(data)                         (0x00000300&((data)<<8))
#define SYS_PLL_DDR2_reg_dpi_pll_ldo_vsel(data)                       (0x000000C0&((data)<<6))
#define SYS_PLL_DDR2_reg_dpi_lpf_sr(data)                             (0x00000038&((data)<<3))
#define SYS_PLL_DDR2_reg_dpi_lpf_cp(data)                             (0x00000004&((data)<<2))
#define SYS_PLL_DDR2_reg_dpi_loop_pi_isel(data)                       (0x00000003&(data))
#define SYS_PLL_DDR2_get_reg_dpi_en_post_pi(data)                     ((0xFFC00000&(data))>>22)
#define SYS_PLL_DDR2_get_reg_dpi_post_pi_rs(data)                     ((0x00100000&(data))>>20)
#define SYS_PLL_DDR2_get_reg_dpi_pll_sel_cpmode(data)                 ((0x00080000&(data))>>19)
#define SYS_PLL_DDR2_get_reg_dpi_cco_band(data)                       ((0x00060000&(data))>>17)
#define SYS_PLL_DDR2_get_reg_dpi_cco_kvco(data)                       ((0x00010000&(data))>>16)
#define SYS_PLL_DDR2_get_reg_dpi_icp(data)                            ((0x0000F000&(data))>>12)
#define SYS_PLL_DDR2_get_reg_dpi_post_pi_bias(data)                   ((0x00000C00&(data))>>10)
#define SYS_PLL_DDR2_get_reg_dpi_post_pi_rl(data)                     ((0x00000300&(data))>>8)
#define SYS_PLL_DDR2_get_reg_dpi_pll_ldo_vsel(data)                   ((0x000000C0&(data))>>6)
#define SYS_PLL_DDR2_get_reg_dpi_lpf_sr(data)                         ((0x00000038&(data))>>3)
#define SYS_PLL_DDR2_get_reg_dpi_lpf_cp(data)                         ((0x00000004&(data))>>2)
#define SYS_PLL_DDR2_get_reg_dpi_loop_pi_isel(data)                   (0x00000003&(data))


#define SYS_PLL_DDR3                                                  0x180002c8
#define SYS_PLL_DDR3_reg_addr                                         "0xb80002c8"
#define SYS_PLL_DDR3_reg                                              0xb80002c8
#define SYS_PLL_DDR3_inst_addr                                        "0x00B2"
#define SYS_PLL_DDR3_inst                                             0x00B2
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel3_shift                       (24)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel2_shift                       (16)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel1_shift                       (8)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel0_shift                       (0)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel3_mask                        (0x3F000000)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel2_mask                        (0x003F0000)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel1_mask                        (0x00003F00)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel0_mask                        (0x0000003F)
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel3(data)                       (0x3F000000&((data)<<24))
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel2(data)                       (0x003F0000&((data)<<16))
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel1(data)                       (0x00003F00&((data)<<8))
#define SYS_PLL_DDR3_reg_dpi_post_pi_sel0(data)                       (0x0000003F&(data))
#define SYS_PLL_DDR3_get_reg_dpi_post_pi_sel3(data)                   ((0x3F000000&(data))>>24)
#define SYS_PLL_DDR3_get_reg_dpi_post_pi_sel2(data)                   ((0x003F0000&(data))>>16)
#define SYS_PLL_DDR3_get_reg_dpi_post_pi_sel1(data)                   ((0x00003F00&(data))>>8)
#define SYS_PLL_DDR3_get_reg_dpi_post_pi_sel0(data)                   (0x0000003F&(data))


#define SYS_PLL_DDR4                                                  0x180002cc
#define SYS_PLL_DDR4_reg_addr                                         "0xb80002cc"
#define SYS_PLL_DDR4_reg                                              0xb80002cc
#define SYS_PLL_DDR4_inst_addr                                        "0x00B3"
#define SYS_PLL_DDR4_inst                                             0x00B3
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel7_shift                       (24)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel6_shift                       (16)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel5_shift                       (8)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel4_shift                       (0)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel7_mask                        (0x3F000000)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel6_mask                        (0x003F0000)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel5_mask                        (0x00003F00)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel4_mask                        (0x0000003F)
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel7(data)                       (0x3F000000&((data)<<24))
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel6(data)                       (0x003F0000&((data)<<16))
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel5(data)                       (0x00003F00&((data)<<8))
#define SYS_PLL_DDR4_reg_dpi_post_pi_sel4(data)                       (0x0000003F&(data))
#define SYS_PLL_DDR4_get_reg_dpi_post_pi_sel7(data)                   ((0x3F000000&(data))>>24)
#define SYS_PLL_DDR4_get_reg_dpi_post_pi_sel6(data)                   ((0x003F0000&(data))>>16)
#define SYS_PLL_DDR4_get_reg_dpi_post_pi_sel5(data)                   ((0x00003F00&(data))>>8)
#define SYS_PLL_DDR4_get_reg_dpi_post_pi_sel4(data)                   (0x0000003F&(data))


#define SYS_PLL_DDR_SSC1                                              0x180002d0
#define SYS_PLL_DDR_SSC1_reg_addr                                     "0xb80002d0"
#define SYS_PLL_DDR_SSC1_reg                                          0xb80002d0
#define SYS_PLL_DDR_SSC1_inst_addr                                    "0x00B4"
#define SYS_PLL_DDR_SSC1_inst                                         0x00B4
#define SYS_PLL_DDR_SSC1_reg_dpi_post_pi_sel9_shift                   (20)
#define SYS_PLL_DDR_SSC1_reg_dpi_post_pi_sel8_shift                   (12)
#define SYS_PLL_DDR_SSC1_reg_dpi_f390k_shift                          (8)
#define SYS_PLL_DDR_SSC1_reg_dpi_wd_enable_shift                      (7)
#define SYS_PLL_DDR_SSC1_reg_dpi_time2_rst_width_shift                (5)
#define SYS_PLL_DDR_SSC1_reg_dpi_time_rdy_ckout_shift                 (3)
#define SYS_PLL_DDR_SSC1_reg_dpi_time0_ck_shift                       (0)
#define SYS_PLL_DDR_SSC1_reg_dpi_post_pi_sel9_mask                    (0x03F00000)
#define SYS_PLL_DDR_SSC1_reg_dpi_post_pi_sel8_mask                    (0x0003F000)
#define SYS_PLL_DDR_SSC1_reg_dpi_f390k_mask                           (0x00000300)
#define SYS_PLL_DDR_SSC1_reg_dpi_wd_enable_mask                       (0x00000080)
#define SYS_PLL_DDR_SSC1_reg_dpi_time2_rst_width_mask                 (0x00000060)
#define SYS_PLL_DDR_SSC1_reg_dpi_time_rdy_ckout_mask                  (0x00000018)
#define SYS_PLL_DDR_SSC1_reg_dpi_time0_ck_mask                        (0x00000007)
#define SYS_PLL_DDR_SSC1_reg_dpi_post_pi_sel9(data)                   (0x03F00000&((data)<<20))
#define SYS_PLL_DDR_SSC1_reg_dpi_post_pi_sel8(data)                   (0x0003F000&((data)<<12))
#define SYS_PLL_DDR_SSC1_reg_dpi_f390k(data)                          (0x00000300&((data)<<8))
#define SYS_PLL_DDR_SSC1_reg_dpi_wd_enable(data)                      (0x00000080&((data)<<7))
#define SYS_PLL_DDR_SSC1_reg_dpi_time2_rst_width(data)                (0x00000060&((data)<<5))
#define SYS_PLL_DDR_SSC1_reg_dpi_time_rdy_ckout(data)                 (0x00000018&((data)<<3))
#define SYS_PLL_DDR_SSC1_reg_dpi_time0_ck(data)                       (0x00000007&(data))
#define SYS_PLL_DDR_SSC1_get_reg_dpi_post_pi_sel9(data)               ((0x03F00000&(data))>>20)
#define SYS_PLL_DDR_SSC1_get_reg_dpi_post_pi_sel8(data)               ((0x0003F000&(data))>>12)
#define SYS_PLL_DDR_SSC1_get_reg_dpi_f390k(data)                      ((0x00000300&(data))>>8)
#define SYS_PLL_DDR_SSC1_get_reg_dpi_wd_enable(data)                  ((0x00000080&(data))>>7)
#define SYS_PLL_DDR_SSC1_get_reg_dpi_time2_rst_width(data)            ((0x00000060&(data))>>5)
#define SYS_PLL_DDR_SSC1_get_reg_dpi_time_rdy_ckout(data)             ((0x00000018&(data))>>3)
#define SYS_PLL_DDR_SSC1_get_reg_dpi_time0_ck(data)                   (0x00000007&(data))


#define SYS_PLL_DDR_SSC2                                              0x180002d4
#define SYS_PLL_DDR_SSC2_reg_addr                                     "0xb80002d4"
#define SYS_PLL_DDR_SSC2_reg                                          0xb80002d4
#define SYS_PLL_DDR_SSC2_inst_addr                                    "0x00B5"
#define SYS_PLL_DDR_SSC2_inst                                         0x00B5
#define SYS_PLL_DDR_SSC2_reg_dpi_sel_mode_shift                       (28)
#define SYS_PLL_DDR_SSC2_reg_dpi_n_code_shift                         (20)
#define SYS_PLL_DDR_SSC2_reg_dpi_f_code_shift                         (4)
#define SYS_PLL_DDR_SSC2_reg_dpi_en_ssc_shift                         (2)
#define SYS_PLL_DDR_SSC2_reg_dpi_bypass_pi_shift                      (1)
#define SYS_PLL_DDR_SSC2_reg_dpi_en_center_in_shift                   (0)
#define SYS_PLL_DDR_SSC2_reg_dpi_sel_mode_mask                        (0x10000000)
#define SYS_PLL_DDR_SSC2_reg_dpi_n_code_mask                          (0x0FF00000)
#define SYS_PLL_DDR_SSC2_reg_dpi_f_code_mask                          (0x0001FFF0)
#define SYS_PLL_DDR_SSC2_reg_dpi_en_ssc_mask                          (0x00000004)
#define SYS_PLL_DDR_SSC2_reg_dpi_bypass_pi_mask                       (0x00000002)
#define SYS_PLL_DDR_SSC2_reg_dpi_en_center_in_mask                    (0x00000001)
#define SYS_PLL_DDR_SSC2_reg_dpi_sel_mode(data)                       (0x10000000&((data)<<28))
#define SYS_PLL_DDR_SSC2_reg_dpi_n_code(data)                         (0x0FF00000&((data)<<20))
#define SYS_PLL_DDR_SSC2_reg_dpi_f_code(data)                         (0x0001FFF0&((data)<<4))
#define SYS_PLL_DDR_SSC2_reg_dpi_en_ssc(data)                         (0x00000004&((data)<<2))
#define SYS_PLL_DDR_SSC2_reg_dpi_bypass_pi(data)                      (0x00000002&((data)<<1))
#define SYS_PLL_DDR_SSC2_reg_dpi_en_center_in(data)                   (0x00000001&(data))
#define SYS_PLL_DDR_SSC2_get_reg_dpi_sel_mode(data)                   ((0x10000000&(data))>>28)
#define SYS_PLL_DDR_SSC2_get_reg_dpi_n_code(data)                     ((0x0FF00000&(data))>>20)
#define SYS_PLL_DDR_SSC2_get_reg_dpi_f_code(data)                     ((0x0001FFF0&(data))>>4)
#define SYS_PLL_DDR_SSC2_get_reg_dpi_en_ssc(data)                     ((0x00000004&(data))>>2)
#define SYS_PLL_DDR_SSC2_get_reg_dpi_bypass_pi(data)                  ((0x00000002&(data))>>1)
#define SYS_PLL_DDR_SSC2_get_reg_dpi_en_center_in(data)               (0x00000001&(data))


#define SYS_PLL_DDR_SSC3                                              0x180002d8
#define SYS_PLL_DDR_SSC3_reg_addr                                     "0xb80002d8"
#define SYS_PLL_DDR_SSC3_reg                                          0xb80002d8
#define SYS_PLL_DDR_SSC3_inst_addr                                    "0x00B6"
#define SYS_PLL_DDR_SSC3_inst                                         0x00B6
#define SYS_PLL_DDR_SSC3_reg_dpi_weighting_sel_shift                  (29)
#define SYS_PLL_DDR_SSC3_reg_dpi_order_shift                          (28)
#define SYS_PLL_DDR_SSC3_reg_dpi_tbase_shift                          (16)
#define SYS_PLL_DDR_SSC3_reg_dpi_step_in_shift                        (0)
#define SYS_PLL_DDR_SSC3_reg_dpi_weighting_sel_mask                   (0xE0000000)
#define SYS_PLL_DDR_SSC3_reg_dpi_order_mask                           (0x10000000)
#define SYS_PLL_DDR_SSC3_reg_dpi_tbase_mask                           (0x0FFF0000)
#define SYS_PLL_DDR_SSC3_reg_dpi_step_in_mask                         (0x00001FFF)
#define SYS_PLL_DDR_SSC3_reg_dpi_weighting_sel(data)                  (0xE0000000&((data)<<29))
#define SYS_PLL_DDR_SSC3_reg_dpi_order(data)                          (0x10000000&((data)<<28))
#define SYS_PLL_DDR_SSC3_reg_dpi_tbase(data)                          (0x0FFF0000&((data)<<16))
#define SYS_PLL_DDR_SSC3_reg_dpi_step_in(data)                        (0x00001FFF&(data))
#define SYS_PLL_DDR_SSC3_get_reg_dpi_weighting_sel(data)              ((0xE0000000&(data))>>29)
#define SYS_PLL_DDR_SSC3_get_reg_dpi_order(data)                      ((0x10000000&(data))>>28)
#define SYS_PLL_DDR_SSC3_get_reg_dpi_tbase(data)                      ((0x0FFF0000&(data))>>16)
#define SYS_PLL_DDR_SSC3_get_reg_dpi_step_in(data)                    (0x00001FFF&(data))


#define SYS_PLL_DDR5                                                  0x180002dc
#define SYS_PLL_DDR5_reg_addr                                         "0xb80002dc"
#define SYS_PLL_DDR5_reg                                              0xb80002dc
#define SYS_PLL_DDR5_inst_addr                                        "0x00B7"
#define SYS_PLL_DDR5_inst                                             0x00B7
#define SYS_PLL_DDR5_reg_dpi_pll_dum_shift                            (0)
#define SYS_PLL_DDR5_reg_dpi_pll_dum_mask                             (0x000000FF)
#define SYS_PLL_DDR5_reg_dpi_pll_dum(data)                            (0x000000FF&(data))
#define SYS_PLL_DDR5_get_reg_dpi_pll_dum(data)                        (0x000000FF&(data))


#define SYS_PLL_DDR5_1                                                0x180002e0
#define SYS_PLL_DDR5_1_reg_addr                                       "0xb80002e0"
#define SYS_PLL_DDR5_1_reg                                            0xb80002e0
#define SYS_PLL_DDR5_1_inst_addr                                      "0x00B8"
#define SYS_PLL_DDR5_1_inst                                           0x00B8
#define SYS_PLL_DDR5_1_pll_stable_shift                               (0)
#define SYS_PLL_DDR5_1_pll_stable_mask                                (0x00000001)
#define SYS_PLL_DDR5_1_pll_stable(data)                               (0x00000001&(data))
#define SYS_PLL_DDR5_1_get_pll_stable(data)                           (0x00000001&(data))


#define SYS_PLL_DUMMY_IN                                              0x180002e4
#define SYS_PLL_DUMMY_IN_reg_addr                                     "0xb80002e4"
#define SYS_PLL_DUMMY_IN_reg                                          0xb80002e4
#define SYS_PLL_DUMMY_IN_inst_addr                                    "0x00B9"
#define SYS_PLL_DUMMY_IN_inst                                         0x00B9
#define SYS_PLL_DUMMY_IN_dpi_dummy_in_dll_shift                       (0)
#define SYS_PLL_DUMMY_IN_dpi_dummy_in_dll_mask                        (0xFFFFFFFF)
#define SYS_PLL_DUMMY_IN_dpi_dummy_in_dll(data)                       (0xFFFFFFFF&(data))
#define SYS_PLL_DUMMY_IN_get_dpi_dummy_in_dll(data)                   (0xFFFFFFFF&(data))


#define SYS_PLL_DUMMY_OUT                                             0x180002e8
#define SYS_PLL_DUMMY_OUT_reg_addr                                    "0xb80002e8"
#define SYS_PLL_DUMMY_OUT_reg                                         0xb80002e8
#define SYS_PLL_DUMMY_OUT_inst_addr                                   "0x00BA"
#define SYS_PLL_DUMMY_OUT_inst                                        0x00BA
#define SYS_PLL_DUMMY_OUT_dpi_dummy_out_dll_shift                     (0)
#define SYS_PLL_DUMMY_OUT_dpi_dummy_out_dll_mask                      (0xFFFFFFFF)
#define SYS_PLL_DUMMY_OUT_dpi_dummy_out_dll(data)                     (0xFFFFFFFF&(data))
#define SYS_PLL_DUMMY_OUT_get_dpi_dummy_out_dll(data)                 (0xFFFFFFFF&(data))


#define SYS_DCLKSS                                                    0x18000300
#define SYS_DCLKSS_reg_addr                                           "0xb8000300"
#define SYS_DCLKSS_reg                                                0xb8000300
#define SYS_DCLKSS_inst_addr                                          "0x00C0"
#define SYS_DCLKSS_inst                                               0x00C0
#define SYS_DCLKSS_dclk_field_flag_mode_en_shift                      (31)
#define SYS_DCLKSS_dclk_filed_flag_slt_shift                          (28)
#define SYS_DCLKSS_dclk_offset_shift                                  (16)
#define SYS_DCLKSS_dclk_new_en_shift                                  (15)
#define SYS_DCLKSS_dclk_ss_test_shift                                 (14)
#define SYS_DCLKSS_dclk_freq_syn_slt_shift                            (8)
#define SYS_DCLKSS_dclk_ss_rag_shift                                  (4)
#define SYS_DCLKSS_dummy300_3_shift                                   (3)
#define SYS_DCLKSS_dclk_ss_load_shift                                 (2)
#define SYS_DCLKSS_dummy300_1_shift                                   (1)
#define SYS_DCLKSS_dclk_ss_en_shift                                   (0)
#define SYS_DCLKSS_dclk_field_flag_mode_en_mask                       (0x80000000)
#define SYS_DCLKSS_dclk_filed_flag_slt_mask                           (0x70000000)
#define SYS_DCLKSS_dclk_offset_mask                                   (0x0FFF0000)
#define SYS_DCLKSS_dclk_new_en_mask                                   (0x00008000)
#define SYS_DCLKSS_dclk_ss_test_mask                                  (0x00004000)
#define SYS_DCLKSS_dclk_freq_syn_slt_mask                             (0x00003F00)
#define SYS_DCLKSS_dclk_ss_rag_mask                                   (0x000000F0)
#define SYS_DCLKSS_dummy300_3_mask                                    (0x00000008)
#define SYS_DCLKSS_dclk_ss_load_mask                                  (0x00000004)
#define SYS_DCLKSS_dummy300_1_mask                                    (0x00000002)
#define SYS_DCLKSS_dclk_ss_en_mask                                    (0x00000001)
#define SYS_DCLKSS_dclk_field_flag_mode_en(data)                      (0x80000000&((data)<<31))
#define SYS_DCLKSS_dclk_filed_flag_slt(data)                          (0x70000000&((data)<<28))
#define SYS_DCLKSS_dclk_offset(data)                                  (0x0FFF0000&((data)<<16))
#define SYS_DCLKSS_dclk_new_en(data)                                  (0x00008000&((data)<<15))
#define SYS_DCLKSS_dclk_ss_test(data)                                 (0x00004000&((data)<<14))
#define SYS_DCLKSS_dclk_freq_syn_slt(data)                            (0x00003F00&((data)<<8))
#define SYS_DCLKSS_dclk_ss_rag(data)                                  (0x000000F0&((data)<<4))
#define SYS_DCLKSS_dummy300_3(data)                                   (0x00000008&((data)<<3))
#define SYS_DCLKSS_dclk_ss_load(data)                                 (0x00000004&((data)<<2))
#define SYS_DCLKSS_dummy300_1(data)                                   (0x00000002&((data)<<1))
#define SYS_DCLKSS_dclk_ss_en(data)                                   (0x00000001&(data))
#define SYS_DCLKSS_get_dclk_field_flag_mode_en(data)                  ((0x80000000&(data))>>31)
#define SYS_DCLKSS_get_dclk_filed_flag_slt(data)                      ((0x70000000&(data))>>28)
#define SYS_DCLKSS_get_dclk_offset(data)                              ((0x0FFF0000&(data))>>16)
#define SYS_DCLKSS_get_dclk_new_en(data)                              ((0x00008000&(data))>>15)
#define SYS_DCLKSS_get_dclk_ss_test(data)                             ((0x00004000&(data))>>14)
#define SYS_DCLKSS_get_dclk_freq_syn_slt(data)                        ((0x00003F00&(data))>>8)
#define SYS_DCLKSS_get_dclk_ss_rag(data)                              ((0x000000F0&(data))>>4)
#define SYS_DCLKSS_get_dummy300_3(data)                               ((0x00000008&(data))>>3)
#define SYS_DCLKSS_get_dclk_ss_load(data)                             ((0x00000004&(data))>>2)
#define SYS_DCLKSS_get_dummy300_1(data)                               ((0x00000002&(data))>>1)
#define SYS_DCLKSS_get_dclk_ss_en(data)                               (0x00000001&(data))


#define DPLL_IN_FSYNC_TRACKING_CTRL                                   0x18000304
#define DPLL_IN_FSYNC_TRACKING_CTRL_reg_addr                          "0xb8000304"
#define DPLL_IN_FSYNC_TRACKING_CTRL_reg                               0xb8000304
#define DPLL_IN_FSYNC_TRACKING_CTRL_inst_addr                         "0x00C1"
#define DPLL_IN_FSYNC_TRACKING_CTRL_inst                              0x00C1
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_valid_shift  (31)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_stable_shift  (30)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_pixel_shift  (18)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_valid_shift  (17)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_stable_shift  (16)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_pixel_shift  (4)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_offset_inverse_shift  (3)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_ypbpr_en_shift  (2)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_vd_dec_en_shift (1)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_general_en_shift  (0)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_valid_mask (0x80000000)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_stable_mask  (0x40000000)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_pixel_mask (0x3FFC0000)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_valid_mask  (0x00020000)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_stable_mask  (0x00010000)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_pixel_mask  (0x0000FFF0)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_offset_inverse_mask  (0x00000008)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_ypbpr_en_mask   (0x00000004)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_vd_dec_en_mask  (0x00000002)
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_general_en_mask (0x00000001)
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_valid(data)  (0x80000000&((data)<<31))
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_stable(data)  (0x40000000&((data)<<30))
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_mcode_slow_modify_pixel(data)  (0x3FFC0000&((data)<<18))
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_valid(data)  (0x00020000&((data)<<17))
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_stable(data)  (0x00010000&((data)<<16))
#define DPLL_IN_FSYNC_TRACKING_CTRL_sscg_offset_slow_modify_pixel(data)  (0x0000FFF0&((data)<<4))
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_offset_inverse(data)  (0x00000008&((data)<<3))
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_ypbpr_en(data)  (0x00000004&((data)<<2))
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_vd_dec_en(data) (0x00000002&((data)<<1))
#define DPLL_IN_FSYNC_TRACKING_CTRL_in_frame_tracking_general_en(data)  (0x00000001&(data))
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_sscg_mcode_slow_modify_valid(data)  ((0x80000000&(data))>>31)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_sscg_mcode_slow_modify_stable(data)  ((0x40000000&(data))>>30)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_sscg_mcode_slow_modify_pixel(data)  ((0x3FFC0000&(data))>>18)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_sscg_offset_slow_modify_valid(data)  ((0x00020000&(data))>>17)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_sscg_offset_slow_modify_stable(data)  ((0x00010000&(data))>>16)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_sscg_offset_slow_modify_pixel(data)  ((0x0000FFF0&(data))>>4)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_in_frame_tracking_offset_inverse(data)  ((0x00000008&(data))>>3)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_in_frame_tracking_ypbpr_en(data)  ((0x00000004&(data))>>2)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_in_frame_tracking_vd_dec_en(data)  ((0x00000002&(data))>>1)
#define DPLL_IN_FSYNC_TRACKING_CTRL_get_in_frame_tracking_general_en(data)  (0x00000001&(data))


#define DPLL_IN_FSYNC_TRACKING_CTRL2                                  0x18000308
#define DPLL_IN_FSYNC_TRACKING_CTRL2_reg_addr                         "0xb8000308"
#define DPLL_IN_FSYNC_TRACKING_CTRL2_reg                              0xb8000308
#define DPLL_IN_FSYNC_TRACKING_CTRL2_inst_addr                        "0x00C2"
#define DPLL_IN_FSYNC_TRACKING_CTRL2_inst                             0x00C2
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_neg_th_shift   (20)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_pos_th_shift   (8)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_mul_shift      (0)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_neg_th_mask    (0xFFF00000)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_pos_th_mask    (0x000FFF00)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_mul_mask       (0x000000FF)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_neg_th(data)   (0xFFF00000&((data)<<20))
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_pos_th(data)   (0x000FFF00&((data)<<8))
#define DPLL_IN_FSYNC_TRACKING_CTRL2_in_frame_tracking_mul(data)      (0x000000FF&(data))
#define DPLL_IN_FSYNC_TRACKING_CTRL2_get_in_frame_tracking_neg_th(data)  ((0xFFF00000&(data))>>20)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_get_in_frame_tracking_pos_th(data)  ((0x000FFF00&(data))>>8)
#define DPLL_IN_FSYNC_TRACKING_CTRL2_get_in_frame_tracking_mul(data)  (0x000000FF&(data))


#define DPLL_IN_FSYNC_TRACKING_DEBUG                                  0x1800030c
#define DPLL_IN_FSYNC_TRACKING_DEBUG_reg_addr                         "0xb800030c"
#define DPLL_IN_FSYNC_TRACKING_DEBUG_reg                              0xb800030c
#define DPLL_IN_FSYNC_TRACKING_DEBUG_inst_addr                        "0x00C3"
#define DPLL_IN_FSYNC_TRACKING_DEBUG_inst                             0x00C3
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_flag_shift      (31)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_profile_over_underflow_flag_shift  (30)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_profile_protection_shift    (29)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_th_max_shift    (16)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_dpll_mcode_protection_shift      (15)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_dpll_mcode_protection_ready_width_shift  (13)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_th_value_shift  (0)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_flag_mask       (0x80000000)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_profile_over_underflow_flag_mask  (0x40000000)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_profile_protection_mask     (0x20000000)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_th_max_mask     (0x1FFF0000)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_dpll_mcode_protection_mask       (0x00008000)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_dpll_mcode_protection_ready_width_mask  (0x00006000)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_th_value_mask   (0x00001FFF)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_flag(data)      (0x80000000&((data)<<31))
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_profile_over_underflow_flag(data)  (0x40000000&((data)<<30))
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_profile_protection(data)    (0x20000000&((data)<<29))
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_th_max(data)    (0x1FFF0000&((data)<<16))
#define DPLL_IN_FSYNC_TRACKING_DEBUG_dpll_mcode_protection(data)      (0x00008000&((data)<<15))
#define DPLL_IN_FSYNC_TRACKING_DEBUG_dpll_mcode_protection_ready_width(data)  (0x00006000&((data)<<13))
#define DPLL_IN_FSYNC_TRACKING_DEBUG_sscg_offset_over_th_value(data)  (0x00001FFF&(data))
#define DPLL_IN_FSYNC_TRACKING_DEBUG_get_sscg_offset_over_flag(data)  ((0x80000000&(data))>>31)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_get_sscg_profile_over_underflow_flag(data)  ((0x40000000&(data))>>30)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_get_sscg_profile_protection(data)  ((0x20000000&(data))>>29)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_get_sscg_offset_over_th_max(data)  ((0x1FFF0000&(data))>>16)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_get_dpll_mcode_protection(data)  ((0x00008000&(data))>>15)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_get_dpll_mcode_protection_ready_width(data)  ((0x00006000&(data))>>13)
#define DPLL_IN_FSYNC_TRACKING_DEBUG_get_sscg_offset_over_th_value(data)  (0x00001FFF&(data))


#define DCLK_FRC2FSYNC_SPEEDUP                                        0x18000310
#define DCLK_FRC2FSYNC_SPEEDUP_reg_addr                               "0xb8000310"
#define DCLK_FRC2FSYNC_SPEEDUP_reg                                    0xb8000310
#define DCLK_FRC2FSYNC_SPEEDUP_inst_addr                              "0x00C4"
#define DCLK_FRC2FSYNC_SPEEDUP_inst                                   0x00C4
#define DCLK_FRC2FSYNC_SPEEDUP_frc2fsync_speedup_m_code_shift         (16)
#define DCLK_FRC2FSYNC_SPEEDUP_frc2fsync_speedup_offset_shift         (0)
#define DCLK_FRC2FSYNC_SPEEDUP_frc2fsync_speedup_m_code_mask          (0x00070000)
#define DCLK_FRC2FSYNC_SPEEDUP_frc2fsync_speedup_offset_mask          (0x000007FF)
#define DCLK_FRC2FSYNC_SPEEDUP_frc2fsync_speedup_m_code(data)         (0x00070000&((data)<<16))
#define DCLK_FRC2FSYNC_SPEEDUP_frc2fsync_speedup_offset(data)         (0x000007FF&(data))
#define DCLK_FRC2FSYNC_SPEEDUP_get_frc2fsync_speedup_m_code(data)     ((0x00070000&(data))>>16)
#define DCLK_FRC2FSYNC_SPEEDUP_get_frc2fsync_speedup_offset(data)     (0x000007FF&(data))


#define DPLL_STATUS_RO                                                0x18000314
#define DPLL_STATUS_RO_reg_addr                                       "0xb8000314"
#define DPLL_STATUS_RO_reg                                            0xb8000314
#define DPLL_STATUS_RO_inst_addr                                      "0x00C5"
#define DPLL_STATUS_RO_inst                                           0x00C5
#define DPLL_STATUS_RO_final_m_code_shift                             (16)
#define DPLL_STATUS_RO_final_profile_shift                            (0)
#define DPLL_STATUS_RO_final_m_code_mask                              (0x03FF0000)
#define DPLL_STATUS_RO_final_profile_mask                             (0x00001FFF)
#define DPLL_STATUS_RO_final_m_code(data)                             (0x03FF0000&((data)<<16))
#define DPLL_STATUS_RO_final_profile(data)                            (0x00001FFF&(data))
#define DPLL_STATUS_RO_get_final_m_code(data)                         ((0x03FF0000&(data))>>16)
#define DPLL_STATUS_RO_get_final_profile(data)                        (0x00001FFF&(data))


#define DCLKSS_FREQ                                                   0x18000318
#define DCLKSS_FREQ_reg_addr                                          "0xb8000318"
#define DCLKSS_FREQ_reg                                               0xb8000318
#define DCLKSS_FREQ_inst_addr                                         "0x00C6"
#define DCLKSS_FREQ_inst                                              0x00C6
#define DCLKSS_FREQ_final_profile_force_64n_en_shift                  (30)
#define DCLKSS_FREQ_dclk_ss_async_protection_shift                    (29)
#define DCLKSS_FREQ_dclk_ss_fmdiv_shift                               (8)
#define DCLKSS_FREQ_dclk_ss_protection_cnt_max_shift                  (0)
#define DCLKSS_FREQ_final_profile_force_64n_en_mask                   (0xC0000000)
#define DCLKSS_FREQ_dclk_ss_async_protection_mask                     (0x20000000)
#define DCLKSS_FREQ_dclk_ss_fmdiv_mask                                (0x00007F00)
#define DCLKSS_FREQ_dclk_ss_protection_cnt_max_mask                   (0x0000007F)
#define DCLKSS_FREQ_final_profile_force_64n_en(data)                  (0xC0000000&((data)<<30))
#define DCLKSS_FREQ_dclk_ss_async_protection(data)                    (0x20000000&((data)<<29))
#define DCLKSS_FREQ_dclk_ss_fmdiv(data)                               (0x00007F00&((data)<<8))
#define DCLKSS_FREQ_dclk_ss_protection_cnt_max(data)                  (0x0000007F&(data))
#define DCLKSS_FREQ_get_final_profile_force_64n_en(data)              ((0xC0000000&(data))>>30)
#define DCLKSS_FREQ_get_dclk_ss_async_protection(data)                ((0x20000000&(data))>>29)
#define DCLKSS_FREQ_get_dclk_ss_fmdiv(data)                           ((0x00007F00&(data))>>8)
#define DCLKSS_FREQ_get_dclk_ss_protection_cnt_max(data)              (0x0000007F&(data))


#define DCLKSS_PROFILE0                                               0x1800031c
#define DCLKSS_PROFILE0_reg_addr                                      "0xb800031c"
#define DCLKSS_PROFILE0_reg                                           0xb800031c
#define DCLKSS_PROFILE0_inst_addr                                     "0x00C7"
#define DCLKSS_PROFILE0_inst                                          0x00C7
#define DCLKSS_PROFILE0_dummy31c_31_30_shift                          (30)
#define DCLKSS_PROFILE0_dclk_ss_shuffle_en_shift                      (29)
#define DCLKSS_PROFILE0_dclk_profile_remap_en_shift                   (28)
#define DCLKSS_PROFILE0_dclk_profile_remap_1_shift                    (16)
#define DCLKSS_PROFILE0_dclk_profile_remap_0_shift                    (0)
#define DCLKSS_PROFILE0_dummy31c_31_30_mask                           (0xC0000000)
#define DCLKSS_PROFILE0_dclk_ss_shuffle_en_mask                       (0x20000000)
#define DCLKSS_PROFILE0_dclk_profile_remap_en_mask                    (0x10000000)
#define DCLKSS_PROFILE0_dclk_profile_remap_1_mask                     (0x0FFF0000)
#define DCLKSS_PROFILE0_dclk_profile_remap_0_mask                     (0x00000FFF)
#define DCLKSS_PROFILE0_dummy31c_31_30(data)                          (0xC0000000&((data)<<30))
#define DCLKSS_PROFILE0_dclk_ss_shuffle_en(data)                      (0x20000000&((data)<<29))
#define DCLKSS_PROFILE0_dclk_profile_remap_en(data)                   (0x10000000&((data)<<28))
#define DCLKSS_PROFILE0_dclk_profile_remap_1(data)                    (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE0_dclk_profile_remap_0(data)                    (0x00000FFF&(data))
#define DCLKSS_PROFILE0_get_dummy31c_31_30(data)                      ((0xC0000000&(data))>>30)
#define DCLKSS_PROFILE0_get_dclk_ss_shuffle_en(data)                  ((0x20000000&(data))>>29)
#define DCLKSS_PROFILE0_get_dclk_profile_remap_en(data)               ((0x10000000&(data))>>28)
#define DCLKSS_PROFILE0_get_dclk_profile_remap_1(data)                ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE0_get_dclk_profile_remap_0(data)                (0x00000FFF&(data))


#define DCLKSS_PROFILE1                                               0x18000320
#define DCLKSS_PROFILE1_reg_addr                                      "0xb8000320"
#define DCLKSS_PROFILE1_reg                                           0xb8000320
#define DCLKSS_PROFILE1_inst_addr                                     "0x00C8"
#define DCLKSS_PROFILE1_inst                                          0x00C8
#define DCLKSS_PROFILE1_dclk_profile_remap_3_shift                    (16)
#define DCLKSS_PROFILE1_dclk_profile_remap_2_shift                    (0)
#define DCLKSS_PROFILE1_dclk_profile_remap_3_mask                     (0x0FFF0000)
#define DCLKSS_PROFILE1_dclk_profile_remap_2_mask                     (0x00000FFF)
#define DCLKSS_PROFILE1_dclk_profile_remap_3(data)                    (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE1_dclk_profile_remap_2(data)                    (0x00000FFF&(data))
#define DCLKSS_PROFILE1_get_dclk_profile_remap_3(data)                ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE1_get_dclk_profile_remap_2(data)                (0x00000FFF&(data))


#define DCLKSS_PROFILE2                                               0x18000324
#define DCLKSS_PROFILE2_reg_addr                                      "0xb8000324"
#define DCLKSS_PROFILE2_reg                                           0xb8000324
#define DCLKSS_PROFILE2_inst_addr                                     "0x00C9"
#define DCLKSS_PROFILE2_inst                                          0x00C9
#define DCLKSS_PROFILE2_dclk_profile_remap_5_shift                    (16)
#define DCLKSS_PROFILE2_dclk_profile_remap_4_shift                    (0)
#define DCLKSS_PROFILE2_dclk_profile_remap_5_mask                     (0x0FFF0000)
#define DCLKSS_PROFILE2_dclk_profile_remap_4_mask                     (0x00000FFF)
#define DCLKSS_PROFILE2_dclk_profile_remap_5(data)                    (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE2_dclk_profile_remap_4(data)                    (0x00000FFF&(data))
#define DCLKSS_PROFILE2_get_dclk_profile_remap_5(data)                ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE2_get_dclk_profile_remap_4(data)                (0x00000FFF&(data))


#define DCLKSS_PROFILE3                                               0x18000328
#define DCLKSS_PROFILE3_reg_addr                                      "0xb8000328"
#define DCLKSS_PROFILE3_reg                                           0xb8000328
#define DCLKSS_PROFILE3_inst_addr                                     "0x00CA"
#define DCLKSS_PROFILE3_inst                                          0x00CA
#define DCLKSS_PROFILE3_dclk_profile_remap_7_shift                    (16)
#define DCLKSS_PROFILE3_dclk_profile_remap_6_shift                    (0)
#define DCLKSS_PROFILE3_dclk_profile_remap_7_mask                     (0x0FFF0000)
#define DCLKSS_PROFILE3_dclk_profile_remap_6_mask                     (0x00000FFF)
#define DCLKSS_PROFILE3_dclk_profile_remap_7(data)                    (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE3_dclk_profile_remap_6(data)                    (0x00000FFF&(data))
#define DCLKSS_PROFILE3_get_dclk_profile_remap_7(data)                ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE3_get_dclk_profile_remap_6(data)                (0x00000FFF&(data))


#define DCLKSS_PROFILE4                                               0x1800032c
#define DCLKSS_PROFILE4_reg_addr                                      "0xb800032c"
#define DCLKSS_PROFILE4_reg                                           0xb800032c
#define DCLKSS_PROFILE4_inst_addr                                     "0x00CB"
#define DCLKSS_PROFILE4_inst                                          0x00CB
#define DCLKSS_PROFILE4_dclk_profile_remap_9_shift                    (16)
#define DCLKSS_PROFILE4_dclk_profile_remap_8_shift                    (0)
#define DCLKSS_PROFILE4_dclk_profile_remap_9_mask                     (0x0FFF0000)
#define DCLKSS_PROFILE4_dclk_profile_remap_8_mask                     (0x00000FFF)
#define DCLKSS_PROFILE4_dclk_profile_remap_9(data)                    (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE4_dclk_profile_remap_8(data)                    (0x00000FFF&(data))
#define DCLKSS_PROFILE4_get_dclk_profile_remap_9(data)                ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE4_get_dclk_profile_remap_8(data)                (0x00000FFF&(data))


#define DCLKSS_PROFILE5                                               0x18000330
#define DCLKSS_PROFILE5_reg_addr                                      "0xb8000330"
#define DCLKSS_PROFILE5_reg                                           0xb8000330
#define DCLKSS_PROFILE5_inst_addr                                     "0x00CC"
#define DCLKSS_PROFILE5_inst                                          0x00CC
#define DCLKSS_PROFILE5_dclk_profile_remap_11_shift                   (16)
#define DCLKSS_PROFILE5_dclk_profile_remap_10_shift                   (0)
#define DCLKSS_PROFILE5_dclk_profile_remap_11_mask                    (0x0FFF0000)
#define DCLKSS_PROFILE5_dclk_profile_remap_10_mask                    (0x00000FFF)
#define DCLKSS_PROFILE5_dclk_profile_remap_11(data)                   (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE5_dclk_profile_remap_10(data)                   (0x00000FFF&(data))
#define DCLKSS_PROFILE5_get_dclk_profile_remap_11(data)               ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE5_get_dclk_profile_remap_10(data)               (0x00000FFF&(data))


#define DCLKSS_PROFILE6                                               0x18000334
#define DCLKSS_PROFILE6_reg_addr                                      "0xb8000334"
#define DCLKSS_PROFILE6_reg                                           0xb8000334
#define DCLKSS_PROFILE6_inst_addr                                     "0x00CD"
#define DCLKSS_PROFILE6_inst                                          0x00CD
#define DCLKSS_PROFILE6_dclk_profile_remap_13_shift                   (16)
#define DCLKSS_PROFILE6_dclk_profile_remap_12_shift                   (0)
#define DCLKSS_PROFILE6_dclk_profile_remap_13_mask                    (0x0FFF0000)
#define DCLKSS_PROFILE6_dclk_profile_remap_12_mask                    (0x00000FFF)
#define DCLKSS_PROFILE6_dclk_profile_remap_13(data)                   (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE6_dclk_profile_remap_12(data)                   (0x00000FFF&(data))
#define DCLKSS_PROFILE6_get_dclk_profile_remap_13(data)               ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE6_get_dclk_profile_remap_12(data)               (0x00000FFF&(data))


#define DCLKSS_PROFILE7                                               0x18000338
#define DCLKSS_PROFILE7_reg_addr                                      "0xb8000338"
#define DCLKSS_PROFILE7_reg                                           0xb8000338
#define DCLKSS_PROFILE7_inst_addr                                     "0x00CE"
#define DCLKSS_PROFILE7_inst                                          0x00CE
#define DCLKSS_PROFILE7_dclk_profile_remap_15_shift                   (16)
#define DCLKSS_PROFILE7_dclk_profile_remap_14_shift                   (0)
#define DCLKSS_PROFILE7_dclk_profile_remap_15_mask                    (0x0FFF0000)
#define DCLKSS_PROFILE7_dclk_profile_remap_14_mask                    (0x00000FFF)
#define DCLKSS_PROFILE7_dclk_profile_remap_15(data)                   (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE7_dclk_profile_remap_14(data)                   (0x00000FFF&(data))
#define DCLKSS_PROFILE7_get_dclk_profile_remap_15(data)               ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE7_get_dclk_profile_remap_14(data)               (0x00000FFF&(data))


#define DCLKSS_PROFILE8                                               0x1800033c
#define DCLKSS_PROFILE8_reg_addr                                      "0xb800033c"
#define DCLKSS_PROFILE8_reg                                           0xb800033c
#define DCLKSS_PROFILE8_inst_addr                                     "0x00CF"
#define DCLKSS_PROFILE8_inst                                          0x00CF
#define DCLKSS_PROFILE8_dclk_profile_remap_17_shift                   (16)
#define DCLKSS_PROFILE8_dclk_profile_remap_16_shift                   (0)
#define DCLKSS_PROFILE8_dclk_profile_remap_17_mask                    (0x0FFF0000)
#define DCLKSS_PROFILE8_dclk_profile_remap_16_mask                    (0x00000FFF)
#define DCLKSS_PROFILE8_dclk_profile_remap_17(data)                   (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE8_dclk_profile_remap_16(data)                   (0x00000FFF&(data))
#define DCLKSS_PROFILE8_get_dclk_profile_remap_17(data)               ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE8_get_dclk_profile_remap_16(data)               (0x00000FFF&(data))


#define DCLKSS_PROFILE9                                               0x18000340
#define DCLKSS_PROFILE9_reg_addr                                      "0xb8000340"
#define DCLKSS_PROFILE9_reg                                           0xb8000340
#define DCLKSS_PROFILE9_inst_addr                                     "0x00D0"
#define DCLKSS_PROFILE9_inst                                          0x00D0
#define DCLKSS_PROFILE9_dclk_profile_remap_19_shift                   (16)
#define DCLKSS_PROFILE9_dclk_profile_remap_18_shift                   (0)
#define DCLKSS_PROFILE9_dclk_profile_remap_19_mask                    (0x0FFF0000)
#define DCLKSS_PROFILE9_dclk_profile_remap_18_mask                    (0x00000FFF)
#define DCLKSS_PROFILE9_dclk_profile_remap_19(data)                   (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE9_dclk_profile_remap_18(data)                   (0x00000FFF&(data))
#define DCLKSS_PROFILE9_get_dclk_profile_remap_19(data)               ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE9_get_dclk_profile_remap_18(data)               (0x00000FFF&(data))


#define DCLKSS_PROFILE10                                              0x18000344
#define DCLKSS_PROFILE10_reg_addr                                     "0xb8000344"
#define DCLKSS_PROFILE10_reg                                          0xb8000344
#define DCLKSS_PROFILE10_inst_addr                                    "0x00D1"
#define DCLKSS_PROFILE10_inst                                         0x00D1
#define DCLKSS_PROFILE10_dclk_profile_remap_21_shift                  (16)
#define DCLKSS_PROFILE10_dclk_profile_remap_20_shift                  (0)
#define DCLKSS_PROFILE10_dclk_profile_remap_21_mask                   (0x0FFF0000)
#define DCLKSS_PROFILE10_dclk_profile_remap_20_mask                   (0x00000FFF)
#define DCLKSS_PROFILE10_dclk_profile_remap_21(data)                  (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE10_dclk_profile_remap_20(data)                  (0x00000FFF&(data))
#define DCLKSS_PROFILE10_get_dclk_profile_remap_21(data)              ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE10_get_dclk_profile_remap_20(data)              (0x00000FFF&(data))


#define DCLKSS_PROFILE11                                              0x18000348
#define DCLKSS_PROFILE11_reg_addr                                     "0xb8000348"
#define DCLKSS_PROFILE11_reg                                          0xb8000348
#define DCLKSS_PROFILE11_inst_addr                                    "0x00D2"
#define DCLKSS_PROFILE11_inst                                         0x00D2
#define DCLKSS_PROFILE11_dclk_profile_remap_23_shift                  (16)
#define DCLKSS_PROFILE11_dclk_profile_remap_22_shift                  (0)
#define DCLKSS_PROFILE11_dclk_profile_remap_23_mask                   (0x0FFF0000)
#define DCLKSS_PROFILE11_dclk_profile_remap_22_mask                   (0x00000FFF)
#define DCLKSS_PROFILE11_dclk_profile_remap_23(data)                  (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE11_dclk_profile_remap_22(data)                  (0x00000FFF&(data))
#define DCLKSS_PROFILE11_get_dclk_profile_remap_23(data)              ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE11_get_dclk_profile_remap_22(data)              (0x00000FFF&(data))


#define DCLKSS_PROFILE12                                              0x1800034c
#define DCLKSS_PROFILE12_reg_addr                                     "0xb800034c"
#define DCLKSS_PROFILE12_reg                                          0xb800034c
#define DCLKSS_PROFILE12_inst_addr                                    "0x00D3"
#define DCLKSS_PROFILE12_inst                                         0x00D3
#define DCLKSS_PROFILE12_dclk_profile_remap_25_shift                  (16)
#define DCLKSS_PROFILE12_dclk_profile_remap_24_shift                  (0)
#define DCLKSS_PROFILE12_dclk_profile_remap_25_mask                   (0x0FFF0000)
#define DCLKSS_PROFILE12_dclk_profile_remap_24_mask                   (0x00000FFF)
#define DCLKSS_PROFILE12_dclk_profile_remap_25(data)                  (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE12_dclk_profile_remap_24(data)                  (0x00000FFF&(data))
#define DCLKSS_PROFILE12_get_dclk_profile_remap_25(data)              ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE12_get_dclk_profile_remap_24(data)              (0x00000FFF&(data))


#define DCLKSS_PROFILE13                                              0x18000350
#define DCLKSS_PROFILE13_reg_addr                                     "0xb8000350"
#define DCLKSS_PROFILE13_reg                                          0xb8000350
#define DCLKSS_PROFILE13_inst_addr                                    "0x00D4"
#define DCLKSS_PROFILE13_inst                                         0x00D4
#define DCLKSS_PROFILE13_dclk_profile_remap_27_shift                  (16)
#define DCLKSS_PROFILE13_dclk_profile_remap_26_shift                  (0)
#define DCLKSS_PROFILE13_dclk_profile_remap_27_mask                   (0x0FFF0000)
#define DCLKSS_PROFILE13_dclk_profile_remap_26_mask                   (0x00000FFF)
#define DCLKSS_PROFILE13_dclk_profile_remap_27(data)                  (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE13_dclk_profile_remap_26(data)                  (0x00000FFF&(data))
#define DCLKSS_PROFILE13_get_dclk_profile_remap_27(data)              ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE13_get_dclk_profile_remap_26(data)              (0x00000FFF&(data))


#define DCLKSS_PROFILE14                                              0x18000354
#define DCLKSS_PROFILE14_reg_addr                                     "0xb8000354"
#define DCLKSS_PROFILE14_reg                                          0xb8000354
#define DCLKSS_PROFILE14_inst_addr                                    "0x00D5"
#define DCLKSS_PROFILE14_inst                                         0x00D5
#define DCLKSS_PROFILE14_dclk_profile_remap_29_shift                  (16)
#define DCLKSS_PROFILE14_dclk_profile_remap_28_shift                  (0)
#define DCLKSS_PROFILE14_dclk_profile_remap_29_mask                   (0x0FFF0000)
#define DCLKSS_PROFILE14_dclk_profile_remap_28_mask                   (0x00000FFF)
#define DCLKSS_PROFILE14_dclk_profile_remap_29(data)                  (0x0FFF0000&((data)<<16))
#define DCLKSS_PROFILE14_dclk_profile_remap_28(data)                  (0x00000FFF&(data))
#define DCLKSS_PROFILE14_get_dclk_profile_remap_29(data)              ((0x0FFF0000&(data))>>16)
#define DCLKSS_PROFILE14_get_dclk_profile_remap_28(data)              (0x00000FFF&(data))


#define DCLKSS_PROFILE15                                              0x18000358
#define DCLKSS_PROFILE15_reg_addr                                     "0xb8000358"
#define DCLKSS_PROFILE15_reg                                          0xb8000358
#define DCLKSS_PROFILE15_inst_addr                                    "0x00D6"
#define DCLKSS_PROFILE15_inst                                         0x00D6
#define DCLKSS_PROFILE15_dclk_profile_remap_31_shift                  (16)
#define DCLKSS_PROFILE15_dclk_profile_remap_30_shift                  (0)
#define DCLKSS_PROFILE15_dclk_profile_remap_31_mask                   (0x1FFF0000)
#define DCLKSS_PROFILE15_dclk_profile_remap_30_mask                   (0x00000FFF)
#define DCLKSS_PROFILE15_dclk_profile_remap_31(data)                  (0x1FFF0000&((data)<<16))
#define DCLKSS_PROFILE15_dclk_profile_remap_30(data)                  (0x00000FFF&(data))
#define DCLKSS_PROFILE15_get_dclk_profile_remap_31(data)              ((0x1FFF0000&(data))>>16)
#define DCLKSS_PROFILE15_get_dclk_profile_remap_30(data)              (0x00000FFF&(data))


#define DPLL_DOUBLE_BUFFER_CTRL                                       0x1800035c
#define DPLL_DOUBLE_BUFFER_CTRL_reg_addr                              "0xb800035c"
#define DPLL_DOUBLE_BUFFER_CTRL_reg                                   0xb800035c
#define DPLL_DOUBLE_BUFFER_CTRL_inst_addr                             "0x00D7"
#define DPLL_DOUBLE_BUFFER_CTRL_inst                                  0x00D7
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_en_shift                   (2)
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_read_sel_shift             (1)
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_apply_shift                (0)
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_en_mask                    (0x00000004)
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_read_sel_mask              (0x00000002)
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_apply_mask                 (0x00000001)
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_en(data)                   (0x00000004&((data)<<2))
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_read_sel(data)             (0x00000002&((data)<<1))
#define DPLL_DOUBLE_BUFFER_CTRL_double_buf_apply(data)                (0x00000001&(data))
#define DPLL_DOUBLE_BUFFER_CTRL_get_double_buf_en(data)               ((0x00000004&(data))>>2)
#define DPLL_DOUBLE_BUFFER_CTRL_get_double_buf_read_sel(data)         ((0x00000002&(data))>>1)
#define DPLL_DOUBLE_BUFFER_CTRL_get_double_buf_apply(data)            (0x00000001&(data))
#endif

