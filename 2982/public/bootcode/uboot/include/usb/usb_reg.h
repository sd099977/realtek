/**************************************************************
// Spec Version                  : 0.1.5
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Register_Name
// Naming Rule                   : Module_Register_Name_reg
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2013/7/16 16:20:28
***************************************************************/


#ifndef _USB_REG_H_INCLUDED_
#define _USB_REG_H_INCLUDED_
#ifdef  _USB_USE_STRUCT
typedef struct 
{
unsigned int     Status_err:2;
unsigned int     reserved_0:23;
unsigned int     suspend_r:1;
unsigned int     Debug_mux:5;
unsigned int     packing:1;
}MAC0_WRAPP_REG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Vstatus_out:8;
}MAC0_VSTATUS_REG;

typedef struct 
{
unsigned int     pwr_mux:1;
unsigned int     ovrcur_mux:1;
unsigned int     ss_resume_utmi_pls_dis_I:1;
unsigned int     ss_utmi_backward_enb_i:1;
unsigned int     utmi_suspend_mux:1;
unsigned int     host_disc_mux:1;
unsigned int     sys_interrupt_i:1;
unsigned int     ohci_0_app_irq12_i:1;
unsigned int     ohci_0_app_irq1_i:1;
unsigned int     ohci_0_app_io_hit_i:1;
unsigned int     ss_nxt_power_state_valid_I:1;
unsigned int     ss_next_power_state_i:2;
unsigned int     ss_power_state_i:2;
unsigned int     ohci_0_cntsel_i_n:1;
unsigned int     ohci_0_clkcktrst_i_n:1;
unsigned int     ehci_chirp_k_quick_resp_i:1;
unsigned int     ss_fladj_val_5_i:1;
unsigned int     ss_fladj_val_4_i:1;
unsigned int     ss_fladj_val_3_i:1;
unsigned int     ss_fladj_val_2_i:1;
unsigned int     ss_fladj_val_1_i:1;
unsigned int     ss_fladj_val_0_i:1;
unsigned int     ss_fladj_val_host_i:6;
unsigned int     ss_simulation_mode_i:1;
unsigned int     ss_word_if_i:1;
}MAC0_USBIPINPUT_REG;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     Test_rst:1;
unsigned int     Test_en:1;
unsigned int     Reset_UTMI:1;
}MAC0_RESET_UTMI_REG;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     Force_test_opmode_en:1;
unsigned int     test_opmode:2;
unsigned int     Force_test_txvalid_en:1;
unsigned int     test_txvalid:1;
unsigned int     Simulation_mode:1;
unsigned int     Force_hs_mode:1;
unsigned int     reserved_1:2;
unsigned int     Test_done:1;
unsigned int     Test_fail:1;
unsigned int     Test_speed:2;
unsigned int     Test_seed:8;
unsigned int     Test_psl:2;
}MAC0_SELF_LOOP_BACK_REG;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     trans_flag_host:1;
unsigned int     trans_flag_otg:1;
unsigned int     Dummy_reg:8;
unsigned int     Nouse_done:1;
unsigned int     Wrap_version:1;
}MAC0_VERSION_REG;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     suspend_r:1;
unsigned int     reserved_1:6;
}MAC0_WRAPP_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Vstatus_out:8;
}MAC0_VSTATUS_2PORT_REG;

typedef struct 
{
unsigned int     pwr_mux:1;
unsigned int     ovrcur_mux:1;
unsigned int     reserved_0:2;
unsigned int     utmi_suspend_mux:1;
unsigned int     host_disc_mux:1;
unsigned int     reserved_1:12;
unsigned int     ss_fladj_val_5_i:1;
unsigned int     ss_fladj_val_4_i:1;
unsigned int     ss_fladj_val_3_i:1;
unsigned int     ss_fladj_val_2_i:1;
unsigned int     ss_fladj_val_1_i:1;
unsigned int     ss_fladj_val_0_i:1;
unsigned int     reserved_2:8;
}MAC0_USBIPINPUT_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     Test_rst:1;
unsigned int     Test_en:1;
unsigned int     Reset_UTMI:1;
}MAC0_RESET_UTMI_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     Force_test_opmode_en:1;
unsigned int     test_opmode:2;
unsigned int     Force_test_txvalid_en:1;
unsigned int     test_txvalid:1;
unsigned int     Simulation_mode:1;
unsigned int     Force_hs_mode:1;
unsigned int     reserved_1:2;
unsigned int     Test_done:1;
unsigned int     Test_fail:1;
unsigned int     Test_speed:2;
unsigned int     Test_seed:8;
unsigned int     Test_psl:2;
}MAC0_SELF_LOOP_BACK_2PORT_REG;

typedef struct 
{
unsigned int     p1_app_prt_ovrcur_i:1;
unsigned int     P0_app_prt_ovrcur_i:1;
unsigned int     reserved_0:26;
unsigned int     ss_ulpi_pp2vbus_i:1;
unsigned int     ss_autoppd_on_overcur_en_i:1;
unsigned int     ss_power_state_valid_i:1;
unsigned int     reg_usb_ck27m_sel:1;
}MAC0_IPNEWINPUT_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usbphy_slb_done:1;
unsigned int     usbphy_slb_fail:1;
unsigned int     usbphy_slb_hs:1;
unsigned int     usbphy_force_slb:1;
}MAC0_USBPHY_SLB0_REG;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usbphy_slb_done:1;
unsigned int     usbphy_slb_fail:1;
unsigned int     usbphy_slb_hs:1;
unsigned int     usbphy_force_slb:1;
}MAC0_USBPHY_SLB1_REG;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     iopdcr_reserved_12:1;
unsigned int     ss_scaledown_mode:2;
unsigned int     m_hbigendian:1;
unsigned int     s_hbigendian:1;
unsigned int     from_frchs:1;
unsigned int     otg_enable:1;
}MAC0_USB_OTG_REG;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     data_value8:1;
unsigned int     data_value7:1;
unsigned int     data_value6:1;
unsigned int     data_value5:1;
unsigned int     data_value4:1;
unsigned int     data_value3:1;
unsigned int     data_value2:1;
unsigned int     data_value1:1;
unsigned int     data_value0:1;
unsigned int     reserved_1:7;
unsigned int     data_mux8:1;
unsigned int     data_mux7:1;
unsigned int     data_mux6:1;
unsigned int     data_mux5:1;
unsigned int     data_mux4:1;
unsigned int     data_mux3:1;
unsigned int     data_mux2:1;
unsigned int     data_mux1:1;
unsigned int     data_mux0:1;
}MAC0_USB_OTGMUX_REG;

typedef struct 
{
unsigned int     reg3848_dummy:23;
unsigned int     prt_pwren_reg_ds:2;
unsigned int     prt_pwren_ctrl:2;
unsigned int     prt_ovrcur_reg_ds:2;
unsigned int     prt_ovrcur_ctrl:2;
unsigned int     usb_dbg_ctrl:1;
}MAC0_USB_CTR0;

typedef struct 
{
unsigned int     Reg384c_dummy:23;
unsigned int     eco_option0_dis:1;
unsigned int     Reg384c_dummy_7:1;
unsigned int     usb_top_dbg_ctrl:3;
unsigned int     cmd_full_number:2;
unsigned int     dbus_arb_priority:1;
unsigned int     dbus_robin_enable:1;
}MAC0_USB_CTR1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_bist_mode_host_ram:1;
unsigned int     usb_bist_mode_wrap:1;
}MAC0_USB_BIST0;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_bist_done_host_ram:1;
unsigned int     usb_bist_done_wrap:1;
}MAC0_USB_BIST1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_bist_fail_host_ram:1;
unsigned int     usb_bist_fail_wrap:1;
}MAC0_USB_BIST2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_mode_host_ram:1;
unsigned int     usb_drf_mode_wrap:1;
}MAC0_USB_DRF0;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_resume_host_ram:1;
unsigned int     usb_drf_resume_wrap:1;
}MAC0_USB_DRF1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_done_host_ram:1;
unsigned int     usb_drf_done_wrap:1;
}MAC0_USB_DRF2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_pause_host_ram:1;
unsigned int     usb_drf_pause_wrap:1;
}MAC0_USB_DRF3;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_fail_host_ram:1;
unsigned int     usb_drf_fail_wrap:1;
}MAC0_USB_DRF4;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     usb_bist_wrap_ls0:1;
unsigned int     usb_bist_wrap_rme0:1;
unsigned int     usb_bist_wrap_rm0:4;
}MAC0_USB_BIST_OPTION0;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     usb_usb_host_ram_ls0:1;
unsigned int     usb_usb_host_ram_rme0:1;
unsigned int     usb_usb_host_ram_rm0:4;
}MAC0_USB_BIST_OPTION1;

typedef struct 
{
unsigned int     Status_err:2;
unsigned int     reserved_0:23;
unsigned int     suspend_r:1;
unsigned int     Debug_mux:5;
unsigned int     packing:1;
}MAC1_WRAPP_REG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Vstatus_out:8;
}MAC1_VSTATUS_REG;

typedef struct 
{
unsigned int     pwr_mux:1;
unsigned int     ovrcur_mux:1;
unsigned int     ss_resume_utmi_pls_dis_I:1;
unsigned int     ss_utmi_backward_enb_i:1;
unsigned int     utmi_suspend_mux:1;
unsigned int     host_disc_mux:1;
unsigned int     sys_interrupt_i:1;
unsigned int     ohci_0_app_irq12_i:1;
unsigned int     ohci_0_app_irq1_i:1;
unsigned int     ohci_0_app_io_hit_i:1;
unsigned int     ss_nxt_power_state_valid_I:1;
unsigned int     ss_next_power_state_i:2;
unsigned int     ss_power_state_i:2;
unsigned int     ohci_0_cntsel_i_n:1;
unsigned int     ohci_0_clkcktrst_i_n:1;
unsigned int     ehci_chirp_k_quick_resp_i:1;
unsigned int     ss_fladj_val_5_i:1;
unsigned int     ss_fladj_val_4_i:1;
unsigned int     ss_fladj_val_3_i:1;
unsigned int     ss_fladj_val_2_i:1;
unsigned int     ss_fladj_val_1_i:1;
unsigned int     ss_fladj_val_0_i:1;
unsigned int     ss_fladj_val_host_i:6;
unsigned int     ss_simulation_mode_i:1;
unsigned int     ss_word_if_i:1;
}MAC1_USBIPINPUT_REG;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     Test_rst:1;
unsigned int     Test_en:1;
unsigned int     Reset_UTMI:1;
}MAC1_RESET_UTMI_REG;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     Force_test_opmode_en:1;
unsigned int     test_opmode:2;
unsigned int     Force_test_txvalid_en:1;
unsigned int     test_txvalid:1;
unsigned int     Simulation_mode:1;
unsigned int     Force_hs_mode:1;
unsigned int     reserved_1:2;
unsigned int     Test_done:1;
unsigned int     Test_fail:1;
unsigned int     Test_speed:2;
unsigned int     Test_seed:8;
unsigned int     Test_psl:2;
}MAC1_SELF_LOOP_BACK_REG;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     trans_flag_host:1;
unsigned int     trans_flag_otg:1;
unsigned int     Dummy_reg:8;
unsigned int     Nouse_done:1;
unsigned int     Wrap_version:1;
}MAC1_VERSION_REG;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     suspend_r:1;
unsigned int     reserved_1:6;
}MAC1_WRAPP_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     Vstatus_out:8;
}MAC1_VSTATUS_2PORT_REG;

typedef struct 
{
unsigned int     pwr_mux:1;
unsigned int     ovrcur_mux:1;
unsigned int     reserved_0:2;
unsigned int     utmi_suspend_mux:1;
unsigned int     host_disc_mux:1;
unsigned int     reserved_1:12;
unsigned int     ss_fladj_val_5_i:1;
unsigned int     ss_fladj_val_4_i:1;
unsigned int     ss_fladj_val_3_i:1;
unsigned int     ss_fladj_val_2_i:1;
unsigned int     ss_fladj_val_1_i:1;
unsigned int     ss_fladj_val_0_i:1;
unsigned int     reserved_2:8;
}MAC1_USBIPINPUT_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     Test_rst:1;
unsigned int     Test_en:1;
unsigned int     Reset_UTMI:1;
}MAC1_RESET_UTMI_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     Force_test_opmode_en:1;
unsigned int     test_opmode:2;
unsigned int     Force_test_txvalid_en:1;
unsigned int     test_txvalid:1;
unsigned int     Simulation_mode:1;
unsigned int     Force_hs_mode:1;
unsigned int     reserved_1:2;
unsigned int     Test_done:1;
unsigned int     Test_fail:1;
unsigned int     Test_speed:2;
unsigned int     Test_seed:8;
unsigned int     Test_psl:2;
}MAC1_SELF_LOOP_BACK_2PORT_REG;

typedef struct 
{
unsigned int     p1_app_prt_ovrcur_i:1;
unsigned int     P0_app_prt_ovrcur_i:1;
unsigned int     reserved_0:26;
unsigned int     ss_ulpi_pp2vbus_i:1;
unsigned int     ss_autoppd_on_overcur_en_i:1;
unsigned int     ss_power_state_valid_i:1;
unsigned int     reg_usb_ck27m_sel:1;
}MAC1_IPNEWINPUT_2PORT_REG;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usbphy_slb_done:1;
unsigned int     usbphy_slb_fail:1;
unsigned int     usbphy_slb_hs:1;
unsigned int     usbphy_force_slb:1;
}MAC1_USBPHY_SLB0_REG;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     usbphy_slb_done:1;
unsigned int     usbphy_slb_fail:1;
unsigned int     usbphy_slb_hs:1;
unsigned int     usbphy_force_slb:1;
}MAC1_USBPHY_SLB1_REG;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     iopdcr_reserved_12:1;
unsigned int     ss_scaledown_mode:2;
unsigned int     m_hbigendian:1;
unsigned int     s_hbigendian:1;
unsigned int     from_frchs:1;
unsigned int     otg_enable:1;
}MAC1_USB_OTG_REG;

typedef struct 
{
unsigned int     reserved_0:7;
unsigned int     data_value8:1;
unsigned int     data_value7:1;
unsigned int     data_value6:1;
unsigned int     data_value5:1;
unsigned int     data_value4:1;
unsigned int     data_value3:1;
unsigned int     data_value2:1;
unsigned int     data_value1:1;
unsigned int     data_value0:1;
unsigned int     reserved_1:7;
unsigned int     data_mux8:1;
unsigned int     data_mux7:1;
unsigned int     data_mux6:1;
unsigned int     data_mux5:1;
unsigned int     data_mux4:1;
unsigned int     data_mux3:1;
unsigned int     data_mux2:1;
unsigned int     data_mux1:1;
unsigned int     data_mux0:1;
}MAC1_USB_OTGMUX_REG;

typedef struct 
{
unsigned int     reg3848_dummy:23;
unsigned int     prt_pwren_reg_ds:2;
unsigned int     prt_pwren_ctrl:2;
unsigned int     prt_ovrcur_reg_ds:2;
unsigned int     prt_ovrcur_ctrl:2;
unsigned int     usb_dbg_ctrl:1;
}MAC1_USB_CTR0;

typedef struct 
{
unsigned int     Reg384c_dummy:23;
unsigned int     eco_option0_dis:1;
unsigned int     Reg384c_dummy_7:1;
unsigned int     usb_top_dbg_ctrl:3;
unsigned int     cmd_full_number:2;
unsigned int     dbus_arb_priority:1;
unsigned int     dbus_robin_enable:1;
}MAC1_USB_CTR1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_bist_mode_host_ram:1;
unsigned int     usb_bist_mode_wrap:1;
}MAC1_USB_BIST0;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_bist_done_host_ram:1;
unsigned int     usb_bist_done_wrap:1;
}MAC1_USB_BIST1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_bist_fail_host_ram:1;
unsigned int     usb_bist_fail_wrap:1;
}MAC1_USB_BIST2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_mode_host_ram:1;
unsigned int     usb_drf_mode_wrap:1;
}MAC1_USB_DRF0;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_resume_host_ram:1;
unsigned int     usb_drf_resume_wrap:1;
}MAC1_USB_DRF1;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_done_host_ram:1;
unsigned int     usb_drf_done_wrap:1;
}MAC1_USB_DRF2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_pause_host_ram:1;
unsigned int     usb_drf_pause_wrap:1;
}MAC1_USB_DRF3;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     usb_drf_fail_host_ram:1;
unsigned int     usb_drf_fail_wrap:1;
}MAC1_USB_DRF4;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     usb_bist_wrap_ls0:1;
unsigned int     usb_bist_wrap_rme0:1;
unsigned int     usb_bist_wrap_rm0:4;
}MAC1_USB_BIST_OPTION0;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     usb_usb_host_ram_ls0:1;
unsigned int     usb_usb_host_ram_rme0:1;
unsigned int     usb_usb_host_ram_rm0:4;
}MAC1_USB_BIST_OPTION1;

#endif

#define MAC0_WRAPP_REG                                                               0x18013800
#define MAC0_WRAPP_REG_reg_addr                                                      "0xB8013800"
#define MAC0_WRAPP_REG_reg                                                           0xB8013800
#define set_MAC0_WRAPP_REG_reg(data)   (*((volatile unsigned int*) MAC0_WRAPP_REG_reg)=data)
#define get_MAC0_WRAPP_REG_reg   (*((volatile unsigned int*) MAC0_WRAPP_REG_reg))
#define MAC0_WRAPP_REG_inst_adr                                                      "0x0000"
#define MAC0_WRAPP_REG_inst                                                          0x0000
#define MAC0_WRAPP_REG_Status_err_shift                                              (30)
#define MAC0_WRAPP_REG_Status_err_mask                                               (0xC0000000)
#define MAC0_WRAPP_REG_Status_err(data)                                              (0xC0000000&((data)<<30))
#define MAC0_WRAPP_REG_Status_err_src(data)                                          ((0xC0000000&(data))>>30)
#define MAC0_WRAPP_REG_get_Status_err(data)                                          ((0xC0000000&(data))>>30)
#define MAC0_WRAPP_REG_suspend_r_shift                                               (6)
#define MAC0_WRAPP_REG_suspend_r_mask                                                (0x00000040)
#define MAC0_WRAPP_REG_suspend_r(data)                                               (0x00000040&((data)<<6))
#define MAC0_WRAPP_REG_suspend_r_src(data)                                           ((0x00000040&(data))>>6)
#define MAC0_WRAPP_REG_get_suspend_r(data)                                           ((0x00000040&(data))>>6)
#define MAC0_WRAPP_REG_Debug_mux_shift                                               (1)
#define MAC0_WRAPP_REG_Debug_mux_mask                                                (0x0000003E)
#define MAC0_WRAPP_REG_Debug_mux(data)                                               (0x0000003E&((data)<<1))
#define MAC0_WRAPP_REG_Debug_mux_src(data)                                           ((0x0000003E&(data))>>1)
#define MAC0_WRAPP_REG_get_Debug_mux(data)                                           ((0x0000003E&(data))>>1)
#define MAC0_WRAPP_REG_packing_shift                                                 (0)
#define MAC0_WRAPP_REG_packing_mask                                                  (0x00000001)
#define MAC0_WRAPP_REG_packing(data)                                                 (0x00000001&((data)<<0))
#define MAC0_WRAPP_REG_packing_src(data)                                             ((0x00000001&(data))>>0)
#define MAC0_WRAPP_REG_get_packing(data)                                             ((0x00000001&(data))>>0)


#define MAC0_VSTATUS_REG                                                             0x18013804
#define MAC0_VSTATUS_REG_reg_addr                                                    "0xB8013804"
#define MAC0_VSTATUS_REG_reg                                                         0xB8013804
#define set_MAC0_VSTATUS_REG_reg(data)   (*((volatile unsigned int*) MAC0_VSTATUS_REG_reg)=data)
#define get_MAC0_VSTATUS_REG_reg   (*((volatile unsigned int*) MAC0_VSTATUS_REG_reg))
#define MAC0_VSTATUS_REG_inst_adr                                                    "0x0001"
#define MAC0_VSTATUS_REG_inst                                                        0x0001
#define MAC0_VSTATUS_REG_Vstatus_out_shift                                           (0)
#define MAC0_VSTATUS_REG_Vstatus_out_mask                                            (0x000000FF)
#define MAC0_VSTATUS_REG_Vstatus_out(data)                                           (0x000000FF&((data)<<0))
#define MAC0_VSTATUS_REG_Vstatus_out_src(data)                                       ((0x000000FF&(data))>>0)
#define MAC0_VSTATUS_REG_get_Vstatus_out(data)                                       ((0x000000FF&(data))>>0)


#define MAC0_USBIPINPUT_REG                                                          0x18013808
#define MAC0_USBIPINPUT_REG_reg_addr                                                 "0xB8013808"
#define MAC0_USBIPINPUT_REG_reg                                                      0xB8013808
#define set_MAC0_USBIPINPUT_REG_reg(data)   (*((volatile unsigned int*) MAC0_USBIPINPUT_REG_reg)=data)
#define get_MAC0_USBIPINPUT_REG_reg   (*((volatile unsigned int*) MAC0_USBIPINPUT_REG_reg))
#define MAC0_USBIPINPUT_REG_inst_adr                                                 "0x0002"
#define MAC0_USBIPINPUT_REG_inst                                                     0x0002
#define MAC0_USBIPINPUT_REG_pwr_mux_shift                                            (31)
#define MAC0_USBIPINPUT_REG_pwr_mux_mask                                             (0x80000000)
#define MAC0_USBIPINPUT_REG_pwr_mux(data)                                            (0x80000000&((data)<<31))
#define MAC0_USBIPINPUT_REG_pwr_mux_src(data)                                        ((0x80000000&(data))>>31)
#define MAC0_USBIPINPUT_REG_get_pwr_mux(data)                                        ((0x80000000&(data))>>31)
#define MAC0_USBIPINPUT_REG_ovrcur_mux_shift                                         (30)
#define MAC0_USBIPINPUT_REG_ovrcur_mux_mask                                          (0x40000000)
#define MAC0_USBIPINPUT_REG_ovrcur_mux(data)                                         (0x40000000&((data)<<30))
#define MAC0_USBIPINPUT_REG_ovrcur_mux_src(data)                                     ((0x40000000&(data))>>30)
#define MAC0_USBIPINPUT_REG_get_ovrcur_mux(data)                                     ((0x40000000&(data))>>30)
#define MAC0_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I_shift                           (29)
#define MAC0_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I_mask                            (0x20000000)
#define MAC0_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I(data)                           (0x20000000&((data)<<29))
#define MAC0_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I_src(data)                       ((0x20000000&(data))>>29)
#define MAC0_USBIPINPUT_REG_get_ss_resume_utmi_pls_dis_I(data)                       ((0x20000000&(data))>>29)
#define MAC0_USBIPINPUT_REG_ss_utmi_backward_enb_i_shift                             (28)
#define MAC0_USBIPINPUT_REG_ss_utmi_backward_enb_i_mask                              (0x10000000)
#define MAC0_USBIPINPUT_REG_ss_utmi_backward_enb_i(data)                             (0x10000000&((data)<<28))
#define MAC0_USBIPINPUT_REG_ss_utmi_backward_enb_i_src(data)                         ((0x10000000&(data))>>28)
#define MAC0_USBIPINPUT_REG_get_ss_utmi_backward_enb_i(data)                         ((0x10000000&(data))>>28)
#define MAC0_USBIPINPUT_REG_utmi_suspend_mux_shift                                   (27)
#define MAC0_USBIPINPUT_REG_utmi_suspend_mux_mask                                    (0x08000000)
#define MAC0_USBIPINPUT_REG_utmi_suspend_mux(data)                                   (0x08000000&((data)<<27))
#define MAC0_USBIPINPUT_REG_utmi_suspend_mux_src(data)                               ((0x08000000&(data))>>27)
#define MAC0_USBIPINPUT_REG_get_utmi_suspend_mux(data)                               ((0x08000000&(data))>>27)
#define MAC0_USBIPINPUT_REG_host_disc_mux_shift                                      (26)
#define MAC0_USBIPINPUT_REG_host_disc_mux_mask                                       (0x04000000)
#define MAC0_USBIPINPUT_REG_host_disc_mux(data)                                      (0x04000000&((data)<<26))
#define MAC0_USBIPINPUT_REG_host_disc_mux_src(data)                                  ((0x04000000&(data))>>26)
#define MAC0_USBIPINPUT_REG_get_host_disc_mux(data)                                  ((0x04000000&(data))>>26)
#define MAC0_USBIPINPUT_REG_sys_interrupt_i_shift                                    (25)
#define MAC0_USBIPINPUT_REG_sys_interrupt_i_mask                                     (0x02000000)
#define MAC0_USBIPINPUT_REG_sys_interrupt_i(data)                                    (0x02000000&((data)<<25))
#define MAC0_USBIPINPUT_REG_sys_interrupt_i_src(data)                                ((0x02000000&(data))>>25)
#define MAC0_USBIPINPUT_REG_get_sys_interrupt_i(data)                                ((0x02000000&(data))>>25)
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq12_i_shift                                 (24)
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq12_i_mask                                  (0x01000000)
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq12_i(data)                                 (0x01000000&((data)<<24))
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq12_i_src(data)                             ((0x01000000&(data))>>24)
#define MAC0_USBIPINPUT_REG_get_ohci_0_app_irq12_i(data)                             ((0x01000000&(data))>>24)
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq1_i_shift                                  (23)
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq1_i_mask                                   (0x00800000)
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq1_i(data)                                  (0x00800000&((data)<<23))
#define MAC0_USBIPINPUT_REG_ohci_0_app_irq1_i_src(data)                              ((0x00800000&(data))>>23)
#define MAC0_USBIPINPUT_REG_get_ohci_0_app_irq1_i(data)                              ((0x00800000&(data))>>23)
#define MAC0_USBIPINPUT_REG_ohci_0_app_io_hit_i_shift                                (22)
#define MAC0_USBIPINPUT_REG_ohci_0_app_io_hit_i_mask                                 (0x00400000)
#define MAC0_USBIPINPUT_REG_ohci_0_app_io_hit_i(data)                                (0x00400000&((data)<<22))
#define MAC0_USBIPINPUT_REG_ohci_0_app_io_hit_i_src(data)                            ((0x00400000&(data))>>22)
#define MAC0_USBIPINPUT_REG_get_ohci_0_app_io_hit_i(data)                            ((0x00400000&(data))>>22)
#define MAC0_USBIPINPUT_REG_ss_nxt_power_state_valid_I_shift                         (21)
#define MAC0_USBIPINPUT_REG_ss_nxt_power_state_valid_I_mask                          (0x00200000)
#define MAC0_USBIPINPUT_REG_ss_nxt_power_state_valid_I(data)                         (0x00200000&((data)<<21))
#define MAC0_USBIPINPUT_REG_ss_nxt_power_state_valid_I_src(data)                     ((0x00200000&(data))>>21)
#define MAC0_USBIPINPUT_REG_get_ss_nxt_power_state_valid_I(data)                     ((0x00200000&(data))>>21)
#define MAC0_USBIPINPUT_REG_ss_next_power_state_i_shift                              (19)
#define MAC0_USBIPINPUT_REG_ss_next_power_state_i_mask                               (0x00180000)
#define MAC0_USBIPINPUT_REG_ss_next_power_state_i(data)                              (0x00180000&((data)<<19))
#define MAC0_USBIPINPUT_REG_ss_next_power_state_i_src(data)                          ((0x00180000&(data))>>19)
#define MAC0_USBIPINPUT_REG_get_ss_next_power_state_i(data)                          ((0x00180000&(data))>>19)
#define MAC0_USBIPINPUT_REG_ss_power_state_i_shift                                   (17)
#define MAC0_USBIPINPUT_REG_ss_power_state_i_mask                                    (0x00060000)
#define MAC0_USBIPINPUT_REG_ss_power_state_i(data)                                   (0x00060000&((data)<<17))
#define MAC0_USBIPINPUT_REG_ss_power_state_i_src(data)                               ((0x00060000&(data))>>17)
#define MAC0_USBIPINPUT_REG_get_ss_power_state_i(data)                               ((0x00060000&(data))>>17)
#define MAC0_USBIPINPUT_REG_ohci_0_cntsel_i_n_shift                                  (16)
#define MAC0_USBIPINPUT_REG_ohci_0_cntsel_i_n_mask                                   (0x00010000)
#define MAC0_USBIPINPUT_REG_ohci_0_cntsel_i_n(data)                                  (0x00010000&((data)<<16))
#define MAC0_USBIPINPUT_REG_ohci_0_cntsel_i_n_src(data)                              ((0x00010000&(data))>>16)
#define MAC0_USBIPINPUT_REG_get_ohci_0_cntsel_i_n(data)                              ((0x00010000&(data))>>16)
#define MAC0_USBIPINPUT_REG_ohci_0_clkcktrst_i_n_shift                               (15)
#define MAC0_USBIPINPUT_REG_ohci_0_clkcktrst_i_n_mask                                (0x00008000)
#define MAC0_USBIPINPUT_REG_ohci_0_clkcktrst_i_n(data)                               (0x00008000&((data)<<15))
#define MAC0_USBIPINPUT_REG_ohci_0_clkcktrst_i_n_src(data)                           ((0x00008000&(data))>>15)
#define MAC0_USBIPINPUT_REG_get_ohci_0_clkcktrst_i_n(data)                           ((0x00008000&(data))>>15)
#define MAC0_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i_shift                          (14)
#define MAC0_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i_mask                           (0x00004000)
#define MAC0_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i(data)                          (0x00004000&((data)<<14))
#define MAC0_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i_src(data)                      ((0x00004000&(data))>>14)
#define MAC0_USBIPINPUT_REG_get_ehci_chirp_k_quick_resp_i(data)                      ((0x00004000&(data))>>14)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_5_i_shift                                   (13)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_5_i_mask                                    (0x00002000)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_5_i(data)                                   (0x00002000&((data)<<13))
#define MAC0_USBIPINPUT_REG_ss_fladj_val_5_i_src(data)                               ((0x00002000&(data))>>13)
#define MAC0_USBIPINPUT_REG_get_ss_fladj_val_5_i(data)                               ((0x00002000&(data))>>13)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_4_i_shift                                   (12)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_4_i_mask                                    (0x00001000)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_4_i(data)                                   (0x00001000&((data)<<12))
#define MAC0_USBIPINPUT_REG_ss_fladj_val_4_i_src(data)                               ((0x00001000&(data))>>12)
#define MAC0_USBIPINPUT_REG_get_ss_fladj_val_4_i(data)                               ((0x00001000&(data))>>12)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_3_i_shift                                   (11)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_3_i_mask                                    (0x00000800)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_3_i(data)                                   (0x00000800&((data)<<11))
#define MAC0_USBIPINPUT_REG_ss_fladj_val_3_i_src(data)                               ((0x00000800&(data))>>11)
#define MAC0_USBIPINPUT_REG_get_ss_fladj_val_3_i(data)                               ((0x00000800&(data))>>11)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_2_i_shift                                   (10)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_2_i_mask                                    (0x00000400)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_2_i(data)                                   (0x00000400&((data)<<10))
#define MAC0_USBIPINPUT_REG_ss_fladj_val_2_i_src(data)                               ((0x00000400&(data))>>10)
#define MAC0_USBIPINPUT_REG_get_ss_fladj_val_2_i(data)                               ((0x00000400&(data))>>10)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_1_i_shift                                   (9)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_1_i_mask                                    (0x00000200)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_1_i(data)                                   (0x00000200&((data)<<9))
#define MAC0_USBIPINPUT_REG_ss_fladj_val_1_i_src(data)                               ((0x00000200&(data))>>9)
#define MAC0_USBIPINPUT_REG_get_ss_fladj_val_1_i(data)                               ((0x00000200&(data))>>9)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_0_i_shift                                   (8)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_0_i_mask                                    (0x00000100)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_0_i(data)                                   (0x00000100&((data)<<8))
#define MAC0_USBIPINPUT_REG_ss_fladj_val_0_i_src(data)                               ((0x00000100&(data))>>8)
#define MAC0_USBIPINPUT_REG_get_ss_fladj_val_0_i(data)                               ((0x00000100&(data))>>8)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_host_i_shift                                (2)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_host_i_mask                                 (0x000000FC)
#define MAC0_USBIPINPUT_REG_ss_fladj_val_host_i(data)                                (0x000000FC&((data)<<2))
#define MAC0_USBIPINPUT_REG_ss_fladj_val_host_i_src(data)                            ((0x000000FC&(data))>>2)
#define MAC0_USBIPINPUT_REG_get_ss_fladj_val_host_i(data)                            ((0x000000FC&(data))>>2)
#define MAC0_USBIPINPUT_REG_ss_simulation_mode_i_shift                               (1)
#define MAC0_USBIPINPUT_REG_ss_simulation_mode_i_mask                                (0x00000002)
#define MAC0_USBIPINPUT_REG_ss_simulation_mode_i(data)                               (0x00000002&((data)<<1))
#define MAC0_USBIPINPUT_REG_ss_simulation_mode_i_src(data)                           ((0x00000002&(data))>>1)
#define MAC0_USBIPINPUT_REG_get_ss_simulation_mode_i(data)                           ((0x00000002&(data))>>1)
#define MAC0_USBIPINPUT_REG_ss_word_if_i_shift                                       (0)
#define MAC0_USBIPINPUT_REG_ss_word_if_i_mask                                        (0x00000001)
#define MAC0_USBIPINPUT_REG_ss_word_if_i(data)                                       (0x00000001&((data)<<0))
#define MAC0_USBIPINPUT_REG_ss_word_if_i_src(data)                                   ((0x00000001&(data))>>0)
#define MAC0_USBIPINPUT_REG_get_ss_word_if_i(data)                                   ((0x00000001&(data))>>0)


#define MAC0_RESET_UTMI_REG                                                          0x1801380c
#define MAC0_RESET_UTMI_REG_reg_addr                                                 "0xB801380C"
#define MAC0_RESET_UTMI_REG_reg                                                      0xB801380C
#define set_MAC0_RESET_UTMI_REG_reg(data)   (*((volatile unsigned int*) MAC0_RESET_UTMI_REG_reg)=data)
#define get_MAC0_RESET_UTMI_REG_reg   (*((volatile unsigned int*) MAC0_RESET_UTMI_REG_reg))
#define MAC0_RESET_UTMI_REG_inst_adr                                                 "0x0003"
#define MAC0_RESET_UTMI_REG_inst                                                     0x0003
#define MAC0_RESET_UTMI_REG_Test_rst_shift                                           (2)
#define MAC0_RESET_UTMI_REG_Test_rst_mask                                            (0x00000004)
#define MAC0_RESET_UTMI_REG_Test_rst(data)                                           (0x00000004&((data)<<2))
#define MAC0_RESET_UTMI_REG_Test_rst_src(data)                                       ((0x00000004&(data))>>2)
#define MAC0_RESET_UTMI_REG_get_Test_rst(data)                                       ((0x00000004&(data))>>2)
#define MAC0_RESET_UTMI_REG_Test_en_shift                                            (1)
#define MAC0_RESET_UTMI_REG_Test_en_mask                                             (0x00000002)
#define MAC0_RESET_UTMI_REG_Test_en(data)                                            (0x00000002&((data)<<1))
#define MAC0_RESET_UTMI_REG_Test_en_src(data)                                        ((0x00000002&(data))>>1)
#define MAC0_RESET_UTMI_REG_get_Test_en(data)                                        ((0x00000002&(data))>>1)
#define MAC0_RESET_UTMI_REG_Reset_UTMI_shift                                         (0)
#define MAC0_RESET_UTMI_REG_Reset_UTMI_mask                                          (0x00000001)
#define MAC0_RESET_UTMI_REG_Reset_UTMI(data)                                         (0x00000001&((data)<<0))
#define MAC0_RESET_UTMI_REG_Reset_UTMI_src(data)                                     ((0x00000001&(data))>>0)
#define MAC0_RESET_UTMI_REG_get_Reset_UTMI(data)                                     ((0x00000001&(data))>>0)


#define MAC0_SELF_LOOP_BACK_REG                                                      0x18013810
#define MAC0_SELF_LOOP_BACK_REG_reg_addr                                             "0xB8013810"
#define MAC0_SELF_LOOP_BACK_REG_reg                                                  0xB8013810
#define set_MAC0_SELF_LOOP_BACK_REG_reg(data)   (*((volatile unsigned int*) MAC0_SELF_LOOP_BACK_REG_reg)=data)
#define get_MAC0_SELF_LOOP_BACK_REG_reg   (*((volatile unsigned int*) MAC0_SELF_LOOP_BACK_REG_reg))
#define MAC0_SELF_LOOP_BACK_REG_inst_adr                                             "0x0004"
#define MAC0_SELF_LOOP_BACK_REG_inst                                                 0x0004
#define MAC0_SELF_LOOP_BACK_REG_Force_test_opmode_en_shift                           (22)
#define MAC0_SELF_LOOP_BACK_REG_Force_test_opmode_en_mask                            (0x00400000)
#define MAC0_SELF_LOOP_BACK_REG_Force_test_opmode_en(data)                           (0x00400000&((data)<<22))
#define MAC0_SELF_LOOP_BACK_REG_Force_test_opmode_en_src(data)                       ((0x00400000&(data))>>22)
#define MAC0_SELF_LOOP_BACK_REG_get_Force_test_opmode_en(data)                       ((0x00400000&(data))>>22)
#define MAC0_SELF_LOOP_BACK_REG_test_opmode_shift                                    (20)
#define MAC0_SELF_LOOP_BACK_REG_test_opmode_mask                                     (0x00300000)
#define MAC0_SELF_LOOP_BACK_REG_test_opmode(data)                                    (0x00300000&((data)<<20))
#define MAC0_SELF_LOOP_BACK_REG_test_opmode_src(data)                                ((0x00300000&(data))>>20)
#define MAC0_SELF_LOOP_BACK_REG_get_test_opmode(data)                                ((0x00300000&(data))>>20)
#define MAC0_SELF_LOOP_BACK_REG_Force_test_txvalid_en_shift                          (19)
#define MAC0_SELF_LOOP_BACK_REG_Force_test_txvalid_en_mask                           (0x00080000)
#define MAC0_SELF_LOOP_BACK_REG_Force_test_txvalid_en(data)                          (0x00080000&((data)<<19))
#define MAC0_SELF_LOOP_BACK_REG_Force_test_txvalid_en_src(data)                      ((0x00080000&(data))>>19)
#define MAC0_SELF_LOOP_BACK_REG_get_Force_test_txvalid_en(data)                      ((0x00080000&(data))>>19)
#define MAC0_SELF_LOOP_BACK_REG_test_txvalid_shift                                   (18)
#define MAC0_SELF_LOOP_BACK_REG_test_txvalid_mask                                    (0x00040000)
#define MAC0_SELF_LOOP_BACK_REG_test_txvalid(data)                                   (0x00040000&((data)<<18))
#define MAC0_SELF_LOOP_BACK_REG_test_txvalid_src(data)                               ((0x00040000&(data))>>18)
#define MAC0_SELF_LOOP_BACK_REG_get_test_txvalid(data)                               ((0x00040000&(data))>>18)
#define MAC0_SELF_LOOP_BACK_REG_Simulation_mode_shift                                (17)
#define MAC0_SELF_LOOP_BACK_REG_Simulation_mode_mask                                 (0x00020000)
#define MAC0_SELF_LOOP_BACK_REG_Simulation_mode(data)                                (0x00020000&((data)<<17))
#define MAC0_SELF_LOOP_BACK_REG_Simulation_mode_src(data)                            ((0x00020000&(data))>>17)
#define MAC0_SELF_LOOP_BACK_REG_get_Simulation_mode(data)                            ((0x00020000&(data))>>17)
#define MAC0_SELF_LOOP_BACK_REG_Force_hs_mode_shift                                  (16)
#define MAC0_SELF_LOOP_BACK_REG_Force_hs_mode_mask                                   (0x00010000)
#define MAC0_SELF_LOOP_BACK_REG_Force_hs_mode(data)                                  (0x00010000&((data)<<16))
#define MAC0_SELF_LOOP_BACK_REG_Force_hs_mode_src(data)                              ((0x00010000&(data))>>16)
#define MAC0_SELF_LOOP_BACK_REG_get_Force_hs_mode(data)                              ((0x00010000&(data))>>16)
#define MAC0_SELF_LOOP_BACK_REG_Test_done_shift                                      (13)
#define MAC0_SELF_LOOP_BACK_REG_Test_done_mask                                       (0x00002000)
#define MAC0_SELF_LOOP_BACK_REG_Test_done(data)                                      (0x00002000&((data)<<13))
#define MAC0_SELF_LOOP_BACK_REG_Test_done_src(data)                                  ((0x00002000&(data))>>13)
#define MAC0_SELF_LOOP_BACK_REG_get_Test_done(data)                                  ((0x00002000&(data))>>13)
#define MAC0_SELF_LOOP_BACK_REG_Test_fail_shift                                      (12)
#define MAC0_SELF_LOOP_BACK_REG_Test_fail_mask                                       (0x00001000)
#define MAC0_SELF_LOOP_BACK_REG_Test_fail(data)                                      (0x00001000&((data)<<12))
#define MAC0_SELF_LOOP_BACK_REG_Test_fail_src(data)                                  ((0x00001000&(data))>>12)
#define MAC0_SELF_LOOP_BACK_REG_get_Test_fail(data)                                  ((0x00001000&(data))>>12)
#define MAC0_SELF_LOOP_BACK_REG_Test_speed_shift                                     (10)
#define MAC0_SELF_LOOP_BACK_REG_Test_speed_mask                                      (0x00000C00)
#define MAC0_SELF_LOOP_BACK_REG_Test_speed(data)                                     (0x00000C00&((data)<<10))
#define MAC0_SELF_LOOP_BACK_REG_Test_speed_src(data)                                 ((0x00000C00&(data))>>10)
#define MAC0_SELF_LOOP_BACK_REG_get_Test_speed(data)                                 ((0x00000C00&(data))>>10)
#define MAC0_SELF_LOOP_BACK_REG_Test_seed_shift                                      (2)
#define MAC0_SELF_LOOP_BACK_REG_Test_seed_mask                                       (0x000003FC)
#define MAC0_SELF_LOOP_BACK_REG_Test_seed(data)                                      (0x000003FC&((data)<<2))
#define MAC0_SELF_LOOP_BACK_REG_Test_seed_src(data)                                  ((0x000003FC&(data))>>2)
#define MAC0_SELF_LOOP_BACK_REG_get_Test_seed(data)                                  ((0x000003FC&(data))>>2)
#define MAC0_SELF_LOOP_BACK_REG_Test_psl_shift                                       (0)
#define MAC0_SELF_LOOP_BACK_REG_Test_psl_mask                                        (0x00000003)
#define MAC0_SELF_LOOP_BACK_REG_Test_psl(data)                                       (0x00000003&((data)<<0))
#define MAC0_SELF_LOOP_BACK_REG_Test_psl_src(data)                                   ((0x00000003&(data))>>0)
#define MAC0_SELF_LOOP_BACK_REG_get_Test_psl(data)                                   ((0x00000003&(data))>>0)


#define MAC0_VERSION_REG                                                             0x18013814
#define MAC0_VERSION_REG_reg_addr                                                    "0xB8013814"
#define MAC0_VERSION_REG_reg                                                         0xB8013814
#define set_MAC0_VERSION_REG_reg(data)   (*((volatile unsigned int*) MAC0_VERSION_REG_reg)=data)
#define get_MAC0_VERSION_REG_reg   (*((volatile unsigned int*) MAC0_VERSION_REG_reg))
#define MAC0_VERSION_REG_inst_adr                                                    "0x0005"
#define MAC0_VERSION_REG_inst                                                        0x0005
#define MAC0_VERSION_REG_trans_flag_host_shift                                       (11)
#define MAC0_VERSION_REG_trans_flag_host_mask                                        (0x00000800)
#define MAC0_VERSION_REG_trans_flag_host(data)                                       (0x00000800&((data)<<11))
#define MAC0_VERSION_REG_trans_flag_host_src(data)                                   ((0x00000800&(data))>>11)
#define MAC0_VERSION_REG_get_trans_flag_host(data)                                   ((0x00000800&(data))>>11)
#define MAC0_VERSION_REG_trans_flag_otg_shift                                        (10)
#define MAC0_VERSION_REG_trans_flag_otg_mask                                         (0x00000400)
#define MAC0_VERSION_REG_trans_flag_otg(data)                                        (0x00000400&((data)<<10))
#define MAC0_VERSION_REG_trans_flag_otg_src(data)                                    ((0x00000400&(data))>>10)
#define MAC0_VERSION_REG_get_trans_flag_otg(data)                                    ((0x00000400&(data))>>10)
#define MAC0_VERSION_REG_Dummy_reg_shift                                             (2)
#define MAC0_VERSION_REG_Dummy_reg_mask                                              (0x000003FC)
#define MAC0_VERSION_REG_Dummy_reg(data)                                             (0x000003FC&((data)<<2))
#define MAC0_VERSION_REG_Dummy_reg_src(data)                                         ((0x000003FC&(data))>>2)
#define MAC0_VERSION_REG_get_Dummy_reg(data)                                         ((0x000003FC&(data))>>2)
#define MAC0_VERSION_REG_Nouse_done_shift                                            (1)
#define MAC0_VERSION_REG_Nouse_done_mask                                             (0x00000002)
#define MAC0_VERSION_REG_Nouse_done(data)                                            (0x00000002&((data)<<1))
#define MAC0_VERSION_REG_Nouse_done_src(data)                                        ((0x00000002&(data))>>1)
#define MAC0_VERSION_REG_get_Nouse_done(data)                                        ((0x00000002&(data))>>1)
#define MAC0_VERSION_REG_Wrap_version_shift                                          (0)
#define MAC0_VERSION_REG_Wrap_version_mask                                           (0x00000001)
#define MAC0_VERSION_REG_Wrap_version(data)                                          (0x00000001&((data)<<0))
#define MAC0_VERSION_REG_Wrap_version_src(data)                                      ((0x00000001&(data))>>0)
#define MAC0_VERSION_REG_get_Wrap_version(data)                                      ((0x00000001&(data))>>0)


#define MAC0_WRAPP_2PORT_REG                                                         0x18013820
#define MAC0_WRAPP_2PORT_REG_reg_addr                                                "0xB8013820"
#define MAC0_WRAPP_2PORT_REG_reg                                                     0xB8013820
#define set_MAC0_WRAPP_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC0_WRAPP_2PORT_REG_reg)=data)
#define get_MAC0_WRAPP_2PORT_REG_reg   (*((volatile unsigned int*) MAC0_WRAPP_2PORT_REG_reg))
#define MAC0_WRAPP_2PORT_REG_inst_adr                                                "0x0008"
#define MAC0_WRAPP_2PORT_REG_inst                                                    0x0008
#define MAC0_WRAPP_2PORT_REG_suspend_r_shift                                         (6)
#define MAC0_WRAPP_2PORT_REG_suspend_r_mask                                          (0x00000040)
#define MAC0_WRAPP_2PORT_REG_suspend_r(data)                                         (0x00000040&((data)<<6))
#define MAC0_WRAPP_2PORT_REG_suspend_r_src(data)                                     ((0x00000040&(data))>>6)
#define MAC0_WRAPP_2PORT_REG_get_suspend_r(data)                                     ((0x00000040&(data))>>6)


#define MAC0_VSTATUS_2PORT_REG                                                       0x18013824
#define MAC0_VSTATUS_2PORT_REG_reg_addr                                              "0xB8013824"
#define MAC0_VSTATUS_2PORT_REG_reg                                                   0xB8013824
#define set_MAC0_VSTATUS_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC0_VSTATUS_2PORT_REG_reg)=data)
#define get_MAC0_VSTATUS_2PORT_REG_reg   (*((volatile unsigned int*) MAC0_VSTATUS_2PORT_REG_reg))
#define MAC0_VSTATUS_2PORT_REG_inst_adr                                              "0x0009"
#define MAC0_VSTATUS_2PORT_REG_inst                                                  0x0009
#define MAC0_VSTATUS_2PORT_REG_Vstatus_out_shift                                     (0)
#define MAC0_VSTATUS_2PORT_REG_Vstatus_out_mask                                      (0x000000FF)
#define MAC0_VSTATUS_2PORT_REG_Vstatus_out(data)                                     (0x000000FF&((data)<<0))
#define MAC0_VSTATUS_2PORT_REG_Vstatus_out_src(data)                                 ((0x000000FF&(data))>>0)
#define MAC0_VSTATUS_2PORT_REG_get_Vstatus_out(data)                                 ((0x000000FF&(data))>>0)


#define MAC0_USBIPINPUT_2PORT_REG                                                    0x18013828
#define MAC0_USBIPINPUT_2PORT_REG_reg_addr                                           "0xB8013828"
#define MAC0_USBIPINPUT_2PORT_REG_reg                                                0xB8013828
#define set_MAC0_USBIPINPUT_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC0_USBIPINPUT_2PORT_REG_reg)=data)
#define get_MAC0_USBIPINPUT_2PORT_REG_reg   (*((volatile unsigned int*) MAC0_USBIPINPUT_2PORT_REG_reg))
#define MAC0_USBIPINPUT_2PORT_REG_inst_adr                                           "0x000A"
#define MAC0_USBIPINPUT_2PORT_REG_inst                                               0x000A
#define MAC0_USBIPINPUT_2PORT_REG_pwr_mux_shift                                      (31)
#define MAC0_USBIPINPUT_2PORT_REG_pwr_mux_mask                                       (0x80000000)
#define MAC0_USBIPINPUT_2PORT_REG_pwr_mux(data)                                      (0x80000000&((data)<<31))
#define MAC0_USBIPINPUT_2PORT_REG_pwr_mux_src(data)                                  ((0x80000000&(data))>>31)
#define MAC0_USBIPINPUT_2PORT_REG_get_pwr_mux(data)                                  ((0x80000000&(data))>>31)
#define MAC0_USBIPINPUT_2PORT_REG_ovrcur_mux_shift                                   (30)
#define MAC0_USBIPINPUT_2PORT_REG_ovrcur_mux_mask                                    (0x40000000)
#define MAC0_USBIPINPUT_2PORT_REG_ovrcur_mux(data)                                   (0x40000000&((data)<<30))
#define MAC0_USBIPINPUT_2PORT_REG_ovrcur_mux_src(data)                               ((0x40000000&(data))>>30)
#define MAC0_USBIPINPUT_2PORT_REG_get_ovrcur_mux(data)                               ((0x40000000&(data))>>30)
#define MAC0_USBIPINPUT_2PORT_REG_utmi_suspend_mux_shift                             (27)
#define MAC0_USBIPINPUT_2PORT_REG_utmi_suspend_mux_mask                              (0x08000000)
#define MAC0_USBIPINPUT_2PORT_REG_utmi_suspend_mux(data)                             (0x08000000&((data)<<27))
#define MAC0_USBIPINPUT_2PORT_REG_utmi_suspend_mux_src(data)                         ((0x08000000&(data))>>27)
#define MAC0_USBIPINPUT_2PORT_REG_get_utmi_suspend_mux(data)                         ((0x08000000&(data))>>27)
#define MAC0_USBIPINPUT_2PORT_REG_host_disc_mux_shift                                (26)
#define MAC0_USBIPINPUT_2PORT_REG_host_disc_mux_mask                                 (0x04000000)
#define MAC0_USBIPINPUT_2PORT_REG_host_disc_mux(data)                                (0x04000000&((data)<<26))
#define MAC0_USBIPINPUT_2PORT_REG_host_disc_mux_src(data)                            ((0x04000000&(data))>>26)
#define MAC0_USBIPINPUT_2PORT_REG_get_host_disc_mux(data)                            ((0x04000000&(data))>>26)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i_shift                             (13)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i_mask                              (0x00002000)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i(data)                             (0x00002000&((data)<<13))
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i_src(data)                         ((0x00002000&(data))>>13)
#define MAC0_USBIPINPUT_2PORT_REG_get_ss_fladj_val_5_i(data)                         ((0x00002000&(data))>>13)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i_shift                             (12)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i_mask                              (0x00001000)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i(data)                             (0x00001000&((data)<<12))
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i_src(data)                         ((0x00001000&(data))>>12)
#define MAC0_USBIPINPUT_2PORT_REG_get_ss_fladj_val_4_i(data)                         ((0x00001000&(data))>>12)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i_shift                             (11)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i_mask                              (0x00000800)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i(data)                             (0x00000800&((data)<<11))
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i_src(data)                         ((0x00000800&(data))>>11)
#define MAC0_USBIPINPUT_2PORT_REG_get_ss_fladj_val_3_i(data)                         ((0x00000800&(data))>>11)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i_shift                             (10)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i_mask                              (0x00000400)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i(data)                             (0x00000400&((data)<<10))
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i_src(data)                         ((0x00000400&(data))>>10)
#define MAC0_USBIPINPUT_2PORT_REG_get_ss_fladj_val_2_i(data)                         ((0x00000400&(data))>>10)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i_shift                             (9)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i_mask                              (0x00000200)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i(data)                             (0x00000200&((data)<<9))
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i_src(data)                         ((0x00000200&(data))>>9)
#define MAC0_USBIPINPUT_2PORT_REG_get_ss_fladj_val_1_i(data)                         ((0x00000200&(data))>>9)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i_shift                             (8)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i_mask                              (0x00000100)
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i(data)                             (0x00000100&((data)<<8))
#define MAC0_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i_src(data)                         ((0x00000100&(data))>>8)
#define MAC0_USBIPINPUT_2PORT_REG_get_ss_fladj_val_0_i(data)                         ((0x00000100&(data))>>8)


#define MAC0_RESET_UTMI_2PORT_REG                                                    0x1801382c
#define MAC0_RESET_UTMI_2PORT_REG_reg_addr                                           "0xB801382C"
#define MAC0_RESET_UTMI_2PORT_REG_reg                                                0xB801382C
#define set_MAC0_RESET_UTMI_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC0_RESET_UTMI_2PORT_REG_reg)=data)
#define get_MAC0_RESET_UTMI_2PORT_REG_reg   (*((volatile unsigned int*) MAC0_RESET_UTMI_2PORT_REG_reg))
#define MAC0_RESET_UTMI_2PORT_REG_inst_adr                                           "0x000B"
#define MAC0_RESET_UTMI_2PORT_REG_inst                                               0x000B
#define MAC0_RESET_UTMI_2PORT_REG_Test_rst_shift                                     (2)
#define MAC0_RESET_UTMI_2PORT_REG_Test_rst_mask                                      (0x00000004)
#define MAC0_RESET_UTMI_2PORT_REG_Test_rst(data)                                     (0x00000004&((data)<<2))
#define MAC0_RESET_UTMI_2PORT_REG_Test_rst_src(data)                                 ((0x00000004&(data))>>2)
#define MAC0_RESET_UTMI_2PORT_REG_get_Test_rst(data)                                 ((0x00000004&(data))>>2)
#define MAC0_RESET_UTMI_2PORT_REG_Test_en_shift                                      (1)
#define MAC0_RESET_UTMI_2PORT_REG_Test_en_mask                                       (0x00000002)
#define MAC0_RESET_UTMI_2PORT_REG_Test_en(data)                                      (0x00000002&((data)<<1))
#define MAC0_RESET_UTMI_2PORT_REG_Test_en_src(data)                                  ((0x00000002&(data))>>1)
#define MAC0_RESET_UTMI_2PORT_REG_get_Test_en(data)                                  ((0x00000002&(data))>>1)
#define MAC0_RESET_UTMI_2PORT_REG_Reset_UTMI_shift                                   (0)
#define MAC0_RESET_UTMI_2PORT_REG_Reset_UTMI_mask                                    (0x00000001)
#define MAC0_RESET_UTMI_2PORT_REG_Reset_UTMI(data)                                   (0x00000001&((data)<<0))
#define MAC0_RESET_UTMI_2PORT_REG_Reset_UTMI_src(data)                               ((0x00000001&(data))>>0)
#define MAC0_RESET_UTMI_2PORT_REG_get_Reset_UTMI(data)                               ((0x00000001&(data))>>0)


#define MAC0_SELF_LOOP_BACK_2PORT_REG                                                0x18013830
#define MAC0_SELF_LOOP_BACK_2PORT_REG_reg_addr                                       "0xB8013830"
#define MAC0_SELF_LOOP_BACK_2PORT_REG_reg                                            0xB8013830
#define set_MAC0_SELF_LOOP_BACK_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC0_SELF_LOOP_BACK_2PORT_REG_reg)=data)
#define get_MAC0_SELF_LOOP_BACK_2PORT_REG_reg   (*((volatile unsigned int*) MAC0_SELF_LOOP_BACK_2PORT_REG_reg))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_inst_adr                                       "0x000C"
#define MAC0_SELF_LOOP_BACK_2PORT_REG_inst                                           0x000C
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en_shift                     (22)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en_mask                      (0x00400000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en(data)                     (0x00400000&((data)<<22))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en_src(data)                 ((0x00400000&(data))>>22)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Force_test_opmode_en(data)                 ((0x00400000&(data))>>22)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_opmode_shift                              (20)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_opmode_mask                               (0x00300000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_opmode(data)                              (0x00300000&((data)<<20))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_opmode_src(data)                          ((0x00300000&(data))>>20)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_test_opmode(data)                          ((0x00300000&(data))>>20)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en_shift                    (19)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en_mask                     (0x00080000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en(data)                    (0x00080000&((data)<<19))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en_src(data)                ((0x00080000&(data))>>19)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Force_test_txvalid_en(data)                ((0x00080000&(data))>>19)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_txvalid_shift                             (18)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_txvalid_mask                              (0x00040000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_txvalid(data)                             (0x00040000&((data)<<18))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_test_txvalid_src(data)                         ((0x00040000&(data))>>18)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_test_txvalid(data)                         ((0x00040000&(data))>>18)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Simulation_mode_shift                          (17)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Simulation_mode_mask                           (0x00020000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Simulation_mode(data)                          (0x00020000&((data)<<17))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Simulation_mode_src(data)                      ((0x00020000&(data))>>17)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Simulation_mode(data)                      ((0x00020000&(data))>>17)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode_shift                            (16)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode_mask                             (0x00010000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode(data)                            (0x00010000&((data)<<16))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode_src(data)                        ((0x00010000&(data))>>16)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Force_hs_mode(data)                        ((0x00010000&(data))>>16)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_done_shift                                (13)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_done_mask                                 (0x00002000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_done(data)                                (0x00002000&((data)<<13))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_done_src(data)                            ((0x00002000&(data))>>13)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Test_done(data)                            ((0x00002000&(data))>>13)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_fail_shift                                (12)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_fail_mask                                 (0x00001000)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_fail(data)                                (0x00001000&((data)<<12))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_fail_src(data)                            ((0x00001000&(data))>>12)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Test_fail(data)                            ((0x00001000&(data))>>12)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_speed_shift                               (10)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_speed_mask                                (0x00000C00)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_speed(data)                               (0x00000C00&((data)<<10))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_speed_src(data)                           ((0x00000C00&(data))>>10)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Test_speed(data)                           ((0x00000C00&(data))>>10)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_seed_shift                                (2)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_seed_mask                                 (0x000003FC)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_seed(data)                                (0x000003FC&((data)<<2))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_seed_src(data)                            ((0x000003FC&(data))>>2)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Test_seed(data)                            ((0x000003FC&(data))>>2)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_psl_shift                                 (0)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_psl_mask                                  (0x00000003)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_psl(data)                                 (0x00000003&((data)<<0))
#define MAC0_SELF_LOOP_BACK_2PORT_REG_Test_psl_src(data)                             ((0x00000003&(data))>>0)
#define MAC0_SELF_LOOP_BACK_2PORT_REG_get_Test_psl(data)                             ((0x00000003&(data))>>0)


#define MAC0_IPNEWINPUT_2PORT_REG                                                    0x18013834
#define MAC0_IPNEWINPUT_2PORT_REG_reg_addr                                           "0xB8013834"
#define MAC0_IPNEWINPUT_2PORT_REG_reg                                                0xB8013834
#define set_MAC0_IPNEWINPUT_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC0_IPNEWINPUT_2PORT_REG_reg)=data)
#define get_MAC0_IPNEWINPUT_2PORT_REG_reg   (*((volatile unsigned int*) MAC0_IPNEWINPUT_2PORT_REG_reg))
#define MAC0_IPNEWINPUT_2PORT_REG_inst_adr                                           "0x000D"
#define MAC0_IPNEWINPUT_2PORT_REG_inst                                               0x000D
#define MAC0_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i_shift                          (31)
#define MAC0_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i_mask                           (0x80000000)
#define MAC0_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i(data)                          (0x80000000&((data)<<31))
#define MAC0_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i_src(data)                      ((0x80000000&(data))>>31)
#define MAC0_IPNEWINPUT_2PORT_REG_get_p1_app_prt_ovrcur_i(data)                      ((0x80000000&(data))>>31)
#define MAC0_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i_shift                          (30)
#define MAC0_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i_mask                           (0x40000000)
#define MAC0_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i(data)                          (0x40000000&((data)<<30))
#define MAC0_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i_src(data)                      ((0x40000000&(data))>>30)
#define MAC0_IPNEWINPUT_2PORT_REG_get_P0_app_prt_ovrcur_i(data)                      ((0x40000000&(data))>>30)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i_shift                            (3)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i_mask                             (0x00000008)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i(data)                            (0x00000008&((data)<<3))
#define MAC0_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i_src(data)                        ((0x00000008&(data))>>3)
#define MAC0_IPNEWINPUT_2PORT_REG_get_ss_ulpi_pp2vbus_i(data)                        ((0x00000008&(data))>>3)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i_shift                   (2)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i_mask                    (0x00000004)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i(data)                   (0x00000004&((data)<<2))
#define MAC0_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i_src(data)               ((0x00000004&(data))>>2)
#define MAC0_IPNEWINPUT_2PORT_REG_get_ss_autoppd_on_overcur_en_i(data)               ((0x00000004&(data))>>2)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i_shift                       (1)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i_mask                        (0x00000002)
#define MAC0_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i(data)                       (0x00000002&((data)<<1))
#define MAC0_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i_src(data)                   ((0x00000002&(data))>>1)
#define MAC0_IPNEWINPUT_2PORT_REG_get_ss_power_state_valid_i(data)                   ((0x00000002&(data))>>1)
#define MAC0_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel_shift                            (0)
#define MAC0_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel_mask                             (0x00000001)
#define MAC0_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel(data)                            (0x00000001&((data)<<0))
#define MAC0_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel_src(data)                        ((0x00000001&(data))>>0)
#define MAC0_IPNEWINPUT_2PORT_REG_get_reg_usb_ck27m_sel(data)                        ((0x00000001&(data))>>0)


#define MAC0_USBPHY_SLB0_REG                                                         0x18013838
#define MAC0_USBPHY_SLB0_REG_reg_addr                                                "0xB8013838"
#define MAC0_USBPHY_SLB0_REG_reg                                                     0xB8013838
#define set_MAC0_USBPHY_SLB0_REG_reg(data)   (*((volatile unsigned int*) MAC0_USBPHY_SLB0_REG_reg)=data)
#define get_MAC0_USBPHY_SLB0_REG_reg   (*((volatile unsigned int*) MAC0_USBPHY_SLB0_REG_reg))
#define MAC0_USBPHY_SLB0_REG_inst_adr                                                "0x000E"
#define MAC0_USBPHY_SLB0_REG_inst                                                    0x000E
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_done_shift                                   (3)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_done_mask                                    (0x00000008)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_done(data)                                   (0x00000008&((data)<<3))
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_done_src(data)                               ((0x00000008&(data))>>3)
#define MAC0_USBPHY_SLB0_REG_get_usbphy_slb_done(data)                               ((0x00000008&(data))>>3)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_fail_shift                                   (2)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_fail_mask                                    (0x00000004)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_fail(data)                                   (0x00000004&((data)<<2))
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_fail_src(data)                               ((0x00000004&(data))>>2)
#define MAC0_USBPHY_SLB0_REG_get_usbphy_slb_fail(data)                               ((0x00000004&(data))>>2)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_hs_shift                                     (1)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_hs_mask                                      (0x00000002)
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_hs(data)                                     (0x00000002&((data)<<1))
#define MAC0_USBPHY_SLB0_REG_usbphy_slb_hs_src(data)                                 ((0x00000002&(data))>>1)
#define MAC0_USBPHY_SLB0_REG_get_usbphy_slb_hs(data)                                 ((0x00000002&(data))>>1)
#define MAC0_USBPHY_SLB0_REG_usbphy_force_slb_shift                                  (0)
#define MAC0_USBPHY_SLB0_REG_usbphy_force_slb_mask                                   (0x00000001)
#define MAC0_USBPHY_SLB0_REG_usbphy_force_slb(data)                                  (0x00000001&((data)<<0))
#define MAC0_USBPHY_SLB0_REG_usbphy_force_slb_src(data)                              ((0x00000001&(data))>>0)
#define MAC0_USBPHY_SLB0_REG_get_usbphy_force_slb(data)                              ((0x00000001&(data))>>0)


#define MAC0_USBPHY_SLB1_REG                                                         0x1801383c
#define MAC0_USBPHY_SLB1_REG_reg_addr                                                "0xB801383C"
#define MAC0_USBPHY_SLB1_REG_reg                                                     0xB801383C
#define set_MAC0_USBPHY_SLB1_REG_reg(data)   (*((volatile unsigned int*) MAC0_USBPHY_SLB1_REG_reg)=data)
#define get_MAC0_USBPHY_SLB1_REG_reg   (*((volatile unsigned int*) MAC0_USBPHY_SLB1_REG_reg))
#define MAC0_USBPHY_SLB1_REG_inst_adr                                                "0x000F"
#define MAC0_USBPHY_SLB1_REG_inst                                                    0x000F
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_done_shift                                   (3)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_done_mask                                    (0x00000008)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_done(data)                                   (0x00000008&((data)<<3))
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_done_src(data)                               ((0x00000008&(data))>>3)
#define MAC0_USBPHY_SLB1_REG_get_usbphy_slb_done(data)                               ((0x00000008&(data))>>3)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_fail_shift                                   (2)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_fail_mask                                    (0x00000004)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_fail(data)                                   (0x00000004&((data)<<2))
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_fail_src(data)                               ((0x00000004&(data))>>2)
#define MAC0_USBPHY_SLB1_REG_get_usbphy_slb_fail(data)                               ((0x00000004&(data))>>2)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_hs_shift                                     (1)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_hs_mask                                      (0x00000002)
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_hs(data)                                     (0x00000002&((data)<<1))
#define MAC0_USBPHY_SLB1_REG_usbphy_slb_hs_src(data)                                 ((0x00000002&(data))>>1)
#define MAC0_USBPHY_SLB1_REG_get_usbphy_slb_hs(data)                                 ((0x00000002&(data))>>1)
#define MAC0_USBPHY_SLB1_REG_usbphy_force_slb_shift                                  (0)
#define MAC0_USBPHY_SLB1_REG_usbphy_force_slb_mask                                   (0x00000001)
#define MAC0_USBPHY_SLB1_REG_usbphy_force_slb(data)                                  (0x00000001&((data)<<0))
#define MAC0_USBPHY_SLB1_REG_usbphy_force_slb_src(data)                              ((0x00000001&(data))>>0)
#define MAC0_USBPHY_SLB1_REG_get_usbphy_force_slb(data)                              ((0x00000001&(data))>>0)


#define MAC0_USB_OTG_REG                                                             0x18013840
#define MAC0_USB_OTG_REG_reg_addr                                                    "0xB8013840"
#define MAC0_USB_OTG_REG_reg                                                         0xB8013840
#define set_MAC0_USB_OTG_REG_reg(data)   (*((volatile unsigned int*) MAC0_USB_OTG_REG_reg)=data)
#define get_MAC0_USB_OTG_REG_reg   (*((volatile unsigned int*) MAC0_USB_OTG_REG_reg))
#define MAC0_USB_OTG_REG_inst_adr                                                    "0x0010"
#define MAC0_USB_OTG_REG_inst                                                        0x0010
#define MAC0_USB_OTG_REG_iopdcr_reserved_12_shift                                    (6)
#define MAC0_USB_OTG_REG_iopdcr_reserved_12_mask                                     (0x00000040)
#define MAC0_USB_OTG_REG_iopdcr_reserved_12(data)                                    (0x00000040&((data)<<6))
#define MAC0_USB_OTG_REG_iopdcr_reserved_12_src(data)                                ((0x00000040&(data))>>6)
#define MAC0_USB_OTG_REG_get_iopdcr_reserved_12(data)                                ((0x00000040&(data))>>6)
#define MAC0_USB_OTG_REG_ss_scaledown_mode_shift                                     (4)
#define MAC0_USB_OTG_REG_ss_scaledown_mode_mask                                      (0x00000030)
#define MAC0_USB_OTG_REG_ss_scaledown_mode(data)                                     (0x00000030&((data)<<4))
#define MAC0_USB_OTG_REG_ss_scaledown_mode_src(data)                                 ((0x00000030&(data))>>4)
#define MAC0_USB_OTG_REG_get_ss_scaledown_mode(data)                                 ((0x00000030&(data))>>4)
#define MAC0_USB_OTG_REG_m_hbigendian_shift                                          (3)
#define MAC0_USB_OTG_REG_m_hbigendian_mask                                           (0x00000008)
#define MAC0_USB_OTG_REG_m_hbigendian(data)                                          (0x00000008&((data)<<3))
#define MAC0_USB_OTG_REG_m_hbigendian_src(data)                                      ((0x00000008&(data))>>3)
#define MAC0_USB_OTG_REG_get_m_hbigendian(data)                                      ((0x00000008&(data))>>3)
#define MAC0_USB_OTG_REG_s_hbigendian_shift                                          (2)
#define MAC0_USB_OTG_REG_s_hbigendian_mask                                           (0x00000004)
#define MAC0_USB_OTG_REG_s_hbigendian(data)                                          (0x00000004&((data)<<2))
#define MAC0_USB_OTG_REG_s_hbigendian_src(data)                                      ((0x00000004&(data))>>2)
#define MAC0_USB_OTG_REG_get_s_hbigendian(data)                                      ((0x00000004&(data))>>2)
#define MAC0_USB_OTG_REG_from_frchs_shift                                            (1)
#define MAC0_USB_OTG_REG_from_frchs_mask                                             (0x00000002)
#define MAC0_USB_OTG_REG_from_frchs(data)                                            (0x00000002&((data)<<1))
#define MAC0_USB_OTG_REG_from_frchs_src(data)                                        ((0x00000002&(data))>>1)
#define MAC0_USB_OTG_REG_get_from_frchs(data)                                        ((0x00000002&(data))>>1)
#define MAC0_USB_OTG_REG_otg_enable_shift                                            (0)
#define MAC0_USB_OTG_REG_otg_enable_mask                                             (0x00000001)
#define MAC0_USB_OTG_REG_otg_enable(data)                                            (0x00000001&((data)<<0))
#define MAC0_USB_OTG_REG_otg_enable_src(data)                                        ((0x00000001&(data))>>0)
#define MAC0_USB_OTG_REG_get_otg_enable(data)                                        ((0x00000001&(data))>>0)


#define MAC0_USB_OTGMUX_REG                                                          0x18013844
#define MAC0_USB_OTGMUX_REG_reg_addr                                                 "0xB8013844"
#define MAC0_USB_OTGMUX_REG_reg                                                      0xB8013844
#define set_MAC0_USB_OTGMUX_REG_reg(data)   (*((volatile unsigned int*) MAC0_USB_OTGMUX_REG_reg)=data)
#define get_MAC0_USB_OTGMUX_REG_reg   (*((volatile unsigned int*) MAC0_USB_OTGMUX_REG_reg))
#define MAC0_USB_OTGMUX_REG_inst_adr                                                 "0x0011"
#define MAC0_USB_OTGMUX_REG_inst                                                     0x0011
#define MAC0_USB_OTGMUX_REG_data_value8_shift                                        (24)
#define MAC0_USB_OTGMUX_REG_data_value8_mask                                         (0x01000000)
#define MAC0_USB_OTGMUX_REG_data_value8(data)                                        (0x01000000&((data)<<24))
#define MAC0_USB_OTGMUX_REG_data_value8_src(data)                                    ((0x01000000&(data))>>24)
#define MAC0_USB_OTGMUX_REG_get_data_value8(data)                                    ((0x01000000&(data))>>24)
#define MAC0_USB_OTGMUX_REG_data_value7_shift                                        (23)
#define MAC0_USB_OTGMUX_REG_data_value7_mask                                         (0x00800000)
#define MAC0_USB_OTGMUX_REG_data_value7(data)                                        (0x00800000&((data)<<23))
#define MAC0_USB_OTGMUX_REG_data_value7_src(data)                                    ((0x00800000&(data))>>23)
#define MAC0_USB_OTGMUX_REG_get_data_value7(data)                                    ((0x00800000&(data))>>23)
#define MAC0_USB_OTGMUX_REG_data_value6_shift                                        (22)
#define MAC0_USB_OTGMUX_REG_data_value6_mask                                         (0x00400000)
#define MAC0_USB_OTGMUX_REG_data_value6(data)                                        (0x00400000&((data)<<22))
#define MAC0_USB_OTGMUX_REG_data_value6_src(data)                                    ((0x00400000&(data))>>22)
#define MAC0_USB_OTGMUX_REG_get_data_value6(data)                                    ((0x00400000&(data))>>22)
#define MAC0_USB_OTGMUX_REG_data_value5_shift                                        (21)
#define MAC0_USB_OTGMUX_REG_data_value5_mask                                         (0x00200000)
#define MAC0_USB_OTGMUX_REG_data_value5(data)                                        (0x00200000&((data)<<21))
#define MAC0_USB_OTGMUX_REG_data_value5_src(data)                                    ((0x00200000&(data))>>21)
#define MAC0_USB_OTGMUX_REG_get_data_value5(data)                                    ((0x00200000&(data))>>21)
#define MAC0_USB_OTGMUX_REG_data_value4_shift                                        (20)
#define MAC0_USB_OTGMUX_REG_data_value4_mask                                         (0x00100000)
#define MAC0_USB_OTGMUX_REG_data_value4(data)                                        (0x00100000&((data)<<20))
#define MAC0_USB_OTGMUX_REG_data_value4_src(data)                                    ((0x00100000&(data))>>20)
#define MAC0_USB_OTGMUX_REG_get_data_value4(data)                                    ((0x00100000&(data))>>20)
#define MAC0_USB_OTGMUX_REG_data_value3_shift                                        (19)
#define MAC0_USB_OTGMUX_REG_data_value3_mask                                         (0x00080000)
#define MAC0_USB_OTGMUX_REG_data_value3(data)                                        (0x00080000&((data)<<19))
#define MAC0_USB_OTGMUX_REG_data_value3_src(data)                                    ((0x00080000&(data))>>19)
#define MAC0_USB_OTGMUX_REG_get_data_value3(data)                                    ((0x00080000&(data))>>19)
#define MAC0_USB_OTGMUX_REG_data_value2_shift                                        (18)
#define MAC0_USB_OTGMUX_REG_data_value2_mask                                         (0x00040000)
#define MAC0_USB_OTGMUX_REG_data_value2(data)                                        (0x00040000&((data)<<18))
#define MAC0_USB_OTGMUX_REG_data_value2_src(data)                                    ((0x00040000&(data))>>18)
#define MAC0_USB_OTGMUX_REG_get_data_value2(data)                                    ((0x00040000&(data))>>18)
#define MAC0_USB_OTGMUX_REG_data_value1_shift                                        (17)
#define MAC0_USB_OTGMUX_REG_data_value1_mask                                         (0x00020000)
#define MAC0_USB_OTGMUX_REG_data_value1(data)                                        (0x00020000&((data)<<17))
#define MAC0_USB_OTGMUX_REG_data_value1_src(data)                                    ((0x00020000&(data))>>17)
#define MAC0_USB_OTGMUX_REG_get_data_value1(data)                                    ((0x00020000&(data))>>17)
#define MAC0_USB_OTGMUX_REG_data_value0_shift                                        (16)
#define MAC0_USB_OTGMUX_REG_data_value0_mask                                         (0x00010000)
#define MAC0_USB_OTGMUX_REG_data_value0(data)                                        (0x00010000&((data)<<16))
#define MAC0_USB_OTGMUX_REG_data_value0_src(data)                                    ((0x00010000&(data))>>16)
#define MAC0_USB_OTGMUX_REG_get_data_value0(data)                                    ((0x00010000&(data))>>16)
#define MAC0_USB_OTGMUX_REG_data_mux8_shift                                          (8)
#define MAC0_USB_OTGMUX_REG_data_mux8_mask                                           (0x00000100)
#define MAC0_USB_OTGMUX_REG_data_mux8(data)                                          (0x00000100&((data)<<8))
#define MAC0_USB_OTGMUX_REG_data_mux8_src(data)                                      ((0x00000100&(data))>>8)
#define MAC0_USB_OTGMUX_REG_get_data_mux8(data)                                      ((0x00000100&(data))>>8)
#define MAC0_USB_OTGMUX_REG_data_mux7_shift                                          (7)
#define MAC0_USB_OTGMUX_REG_data_mux7_mask                                           (0x00000080)
#define MAC0_USB_OTGMUX_REG_data_mux7(data)                                          (0x00000080&((data)<<7))
#define MAC0_USB_OTGMUX_REG_data_mux7_src(data)                                      ((0x00000080&(data))>>7)
#define MAC0_USB_OTGMUX_REG_get_data_mux7(data)                                      ((0x00000080&(data))>>7)
#define MAC0_USB_OTGMUX_REG_data_mux6_shift                                          (6)
#define MAC0_USB_OTGMUX_REG_data_mux6_mask                                           (0x00000040)
#define MAC0_USB_OTGMUX_REG_data_mux6(data)                                          (0x00000040&((data)<<6))
#define MAC0_USB_OTGMUX_REG_data_mux6_src(data)                                      ((0x00000040&(data))>>6)
#define MAC0_USB_OTGMUX_REG_get_data_mux6(data)                                      ((0x00000040&(data))>>6)
#define MAC0_USB_OTGMUX_REG_data_mux5_shift                                          (5)
#define MAC0_USB_OTGMUX_REG_data_mux5_mask                                           (0x00000020)
#define MAC0_USB_OTGMUX_REG_data_mux5(data)                                          (0x00000020&((data)<<5))
#define MAC0_USB_OTGMUX_REG_data_mux5_src(data)                                      ((0x00000020&(data))>>5)
#define MAC0_USB_OTGMUX_REG_get_data_mux5(data)                                      ((0x00000020&(data))>>5)
#define MAC0_USB_OTGMUX_REG_data_mux4_shift                                          (4)
#define MAC0_USB_OTGMUX_REG_data_mux4_mask                                           (0x00000010)
#define MAC0_USB_OTGMUX_REG_data_mux4(data)                                          (0x00000010&((data)<<4))
#define MAC0_USB_OTGMUX_REG_data_mux4_src(data)                                      ((0x00000010&(data))>>4)
#define MAC0_USB_OTGMUX_REG_get_data_mux4(data)                                      ((0x00000010&(data))>>4)
#define MAC0_USB_OTGMUX_REG_data_mux3_shift                                          (3)
#define MAC0_USB_OTGMUX_REG_data_mux3_mask                                           (0x00000008)
#define MAC0_USB_OTGMUX_REG_data_mux3(data)                                          (0x00000008&((data)<<3))
#define MAC0_USB_OTGMUX_REG_data_mux3_src(data)                                      ((0x00000008&(data))>>3)
#define MAC0_USB_OTGMUX_REG_get_data_mux3(data)                                      ((0x00000008&(data))>>3)
#define MAC0_USB_OTGMUX_REG_data_mux2_shift                                          (2)
#define MAC0_USB_OTGMUX_REG_data_mux2_mask                                           (0x00000004)
#define MAC0_USB_OTGMUX_REG_data_mux2(data)                                          (0x00000004&((data)<<2))
#define MAC0_USB_OTGMUX_REG_data_mux2_src(data)                                      ((0x00000004&(data))>>2)
#define MAC0_USB_OTGMUX_REG_get_data_mux2(data)                                      ((0x00000004&(data))>>2)
#define MAC0_USB_OTGMUX_REG_data_mux1_shift                                          (1)
#define MAC0_USB_OTGMUX_REG_data_mux1_mask                                           (0x00000002)
#define MAC0_USB_OTGMUX_REG_data_mux1(data)                                          (0x00000002&((data)<<1))
#define MAC0_USB_OTGMUX_REG_data_mux1_src(data)                                      ((0x00000002&(data))>>1)
#define MAC0_USB_OTGMUX_REG_get_data_mux1(data)                                      ((0x00000002&(data))>>1)
#define MAC0_USB_OTGMUX_REG_data_mux0_shift                                          (0)
#define MAC0_USB_OTGMUX_REG_data_mux0_mask                                           (0x00000001)
#define MAC0_USB_OTGMUX_REG_data_mux0(data)                                          (0x00000001&((data)<<0))
#define MAC0_USB_OTGMUX_REG_data_mux0_src(data)                                      ((0x00000001&(data))>>0)
#define MAC0_USB_OTGMUX_REG_get_data_mux0(data)                                      ((0x00000001&(data))>>0)


#define MAC0_USB_CTR0                                                                0x18013848
#define MAC0_USB_CTR0_reg_addr                                                       "0xB8013848"
#define MAC0_USB_CTR0_reg                                                            0xB8013848
#define set_MAC0_USB_CTR0_reg(data)   (*((volatile unsigned int*) MAC0_USB_CTR0_reg)=data)
#define get_MAC0_USB_CTR0_reg   (*((volatile unsigned int*) MAC0_USB_CTR0_reg))
#define MAC0_USB_CTR0_inst_adr                                                       "0x0012"
#define MAC0_USB_CTR0_inst                                                           0x0012
#define MAC0_USB_CTR0_reg3848_dummy_shift                                            (9)
#define MAC0_USB_CTR0_reg3848_dummy_mask                                             (0xFFFFFE00)
#define MAC0_USB_CTR0_reg3848_dummy(data)                                            (0xFFFFFE00&((data)<<9))
#define MAC0_USB_CTR0_reg3848_dummy_src(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC0_USB_CTR0_get_reg3848_dummy(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC0_USB_CTR0_prt_pwren_reg_ds_shift                                         (7)
#define MAC0_USB_CTR0_prt_pwren_reg_ds_mask                                          (0x00000180)
#define MAC0_USB_CTR0_prt_pwren_reg_ds(data)                                         (0x00000180&((data)<<7))
#define MAC0_USB_CTR0_prt_pwren_reg_ds_src(data)                                     ((0x00000180&(data))>>7)
#define MAC0_USB_CTR0_get_prt_pwren_reg_ds(data)                                     ((0x00000180&(data))>>7)
#define MAC0_USB_CTR0_prt_pwren_ctrl_shift                                           (5)
#define MAC0_USB_CTR0_prt_pwren_ctrl_mask                                            (0x00000060)
#define MAC0_USB_CTR0_prt_pwren_ctrl(data)                                           (0x00000060&((data)<<5))
#define MAC0_USB_CTR0_prt_pwren_ctrl_src(data)                                       ((0x00000060&(data))>>5)
#define MAC0_USB_CTR0_get_prt_pwren_ctrl(data)                                       ((0x00000060&(data))>>5)
#define MAC0_USB_CTR0_prt_ovrcur_reg_ds_shift                                        (3)
#define MAC0_USB_CTR0_prt_ovrcur_reg_ds_mask                                         (0x00000018)
#define MAC0_USB_CTR0_prt_ovrcur_reg_ds(data)                                        (0x00000018&((data)<<3))
#define MAC0_USB_CTR0_prt_ovrcur_reg_ds_src(data)                                    ((0x00000018&(data))>>3)
#define MAC0_USB_CTR0_get_prt_ovrcur_reg_ds(data)                                    ((0x00000018&(data))>>3)
#define MAC0_USB_CTR0_prt_ovrcur_ctrl_shift                                          (1)
#define MAC0_USB_CTR0_prt_ovrcur_ctrl_mask                                           (0x00000006)
#define MAC0_USB_CTR0_prt_ovrcur_ctrl(data)                                          (0x00000006&((data)<<1))
#define MAC0_USB_CTR0_prt_ovrcur_ctrl_src(data)                                      ((0x00000006&(data))>>1)
#define MAC0_USB_CTR0_get_prt_ovrcur_ctrl(data)                                      ((0x00000006&(data))>>1)
#define MAC0_USB_CTR0_usb_dbg_ctrl_shift                                             (0)
#define MAC0_USB_CTR0_usb_dbg_ctrl_mask                                              (0x00000001)
#define MAC0_USB_CTR0_usb_dbg_ctrl(data)                                             (0x00000001&((data)<<0))
#define MAC0_USB_CTR0_usb_dbg_ctrl_src(data)                                         ((0x00000001&(data))>>0)
#define MAC0_USB_CTR0_get_usb_dbg_ctrl(data)                                         ((0x00000001&(data))>>0)


#define MAC0_USB_CTR1                                                                0x1801384c
#define MAC0_USB_CTR1_reg_addr                                                       "0xB801384C"
#define MAC0_USB_CTR1_reg                                                            0xB801384C
#define set_MAC0_USB_CTR1_reg(data)   (*((volatile unsigned int*) MAC0_USB_CTR1_reg)=data)
#define get_MAC0_USB_CTR1_reg   (*((volatile unsigned int*) MAC0_USB_CTR1_reg))
#define MAC0_USB_CTR1_inst_adr                                                       "0x0013"
#define MAC0_USB_CTR1_inst                                                           0x0013
#define MAC0_USB_CTR1_Reg384c_dummy_shift                                            (9)
#define MAC0_USB_CTR1_Reg384c_dummy_mask                                             (0xFFFFFE00)
#define MAC0_USB_CTR1_Reg384c_dummy(data)                                            (0xFFFFFE00&((data)<<9))
#define MAC0_USB_CTR1_Reg384c_dummy_src(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC0_USB_CTR1_get_Reg384c_dummy(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC0_USB_CTR1_eco_option0_dis_shift                                          (8)
#define MAC0_USB_CTR1_eco_option0_dis_mask                                           (0x00000100)
#define MAC0_USB_CTR1_eco_option0_dis(data)                                          (0x00000100&((data)<<8))
#define MAC0_USB_CTR1_eco_option0_dis_src(data)                                      ((0x00000100&(data))>>8)
#define MAC0_USB_CTR1_get_eco_option0_dis(data)                                      ((0x00000100&(data))>>8)
#define MAC0_USB_CTR1_Reg384c_dummy_7_shift                                          (7)
#define MAC0_USB_CTR1_Reg384c_dummy_7_mask                                           (0x00000080)
#define MAC0_USB_CTR1_Reg384c_dummy_7(data)                                          (0x00000080&((data)<<7))
#define MAC0_USB_CTR1_Reg384c_dummy_7_src(data)                                      ((0x00000080&(data))>>7)
#define MAC0_USB_CTR1_get_Reg384c_dummy_7(data)                                      ((0x00000080&(data))>>7)
#define MAC0_USB_CTR1_usb_top_dbg_ctrl_shift                                         (4)
#define MAC0_USB_CTR1_usb_top_dbg_ctrl_mask                                          (0x00000070)
#define MAC0_USB_CTR1_usb_top_dbg_ctrl(data)                                         (0x00000070&((data)<<4))
#define MAC0_USB_CTR1_usb_top_dbg_ctrl_src(data)                                     ((0x00000070&(data))>>4)
#define MAC0_USB_CTR1_get_usb_top_dbg_ctrl(data)                                     ((0x00000070&(data))>>4)
#define MAC0_USB_CTR1_cmd_full_number_shift                                          (2)
#define MAC0_USB_CTR1_cmd_full_number_mask                                           (0x0000000C)
#define MAC0_USB_CTR1_cmd_full_number(data)                                          (0x0000000C&((data)<<2))
#define MAC0_USB_CTR1_cmd_full_number_src(data)                                      ((0x0000000C&(data))>>2)
#define MAC0_USB_CTR1_get_cmd_full_number(data)                                      ((0x0000000C&(data))>>2)
#define MAC0_USB_CTR1_dbus_arb_priority_shift                                        (1)
#define MAC0_USB_CTR1_dbus_arb_priority_mask                                         (0x00000002)
#define MAC0_USB_CTR1_dbus_arb_priority(data)                                        (0x00000002&((data)<<1))
#define MAC0_USB_CTR1_dbus_arb_priority_src(data)                                    ((0x00000002&(data))>>1)
#define MAC0_USB_CTR1_get_dbus_arb_priority(data)                                    ((0x00000002&(data))>>1)
#define MAC0_USB_CTR1_dbus_robin_enable_shift                                        (0)
#define MAC0_USB_CTR1_dbus_robin_enable_mask                                         (0x00000001)
#define MAC0_USB_CTR1_dbus_robin_enable(data)                                        (0x00000001&((data)<<0))
#define MAC0_USB_CTR1_dbus_robin_enable_src(data)                                    ((0x00000001&(data))>>0)
#define MAC0_USB_CTR1_get_dbus_robin_enable(data)                                    ((0x00000001&(data))>>0)


#define MAC0_USB_BIST0                                                               0x18013900
#define MAC0_USB_BIST0_reg_addr                                                      "0xB8013900"
#define MAC0_USB_BIST0_reg                                                           0xB8013900
#define set_MAC0_USB_BIST0_reg(data)   (*((volatile unsigned int*) MAC0_USB_BIST0_reg)=data)
#define get_MAC0_USB_BIST0_reg   (*((volatile unsigned int*) MAC0_USB_BIST0_reg))
#define MAC0_USB_BIST0_inst_adr                                                      "0x0040"
#define MAC0_USB_BIST0_inst                                                          0x0040
#define MAC0_USB_BIST0_usb_bist_mode_host_ram_shift                                  (1)
#define MAC0_USB_BIST0_usb_bist_mode_host_ram_mask                                   (0x00000002)
#define MAC0_USB_BIST0_usb_bist_mode_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC0_USB_BIST0_usb_bist_mode_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_BIST0_get_usb_bist_mode_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_BIST0_usb_bist_mode_wrap_shift                                      (0)
#define MAC0_USB_BIST0_usb_bist_mode_wrap_mask                                       (0x00000001)
#define MAC0_USB_BIST0_usb_bist_mode_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC0_USB_BIST0_usb_bist_mode_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC0_USB_BIST0_get_usb_bist_mode_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC0_USB_BIST1                                                               0x18013904
#define MAC0_USB_BIST1_reg_addr                                                      "0xB8013904"
#define MAC0_USB_BIST1_reg                                                           0xB8013904
#define set_MAC0_USB_BIST1_reg(data)   (*((volatile unsigned int*) MAC0_USB_BIST1_reg)=data)
#define get_MAC0_USB_BIST1_reg   (*((volatile unsigned int*) MAC0_USB_BIST1_reg))
#define MAC0_USB_BIST1_inst_adr                                                      "0x0041"
#define MAC0_USB_BIST1_inst                                                          0x0041
#define MAC0_USB_BIST1_usb_bist_done_host_ram_shift                                  (1)
#define MAC0_USB_BIST1_usb_bist_done_host_ram_mask                                   (0x00000002)
#define MAC0_USB_BIST1_usb_bist_done_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC0_USB_BIST1_usb_bist_done_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_BIST1_get_usb_bist_done_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_BIST1_usb_bist_done_wrap_shift                                      (0)
#define MAC0_USB_BIST1_usb_bist_done_wrap_mask                                       (0x00000001)
#define MAC0_USB_BIST1_usb_bist_done_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC0_USB_BIST1_usb_bist_done_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC0_USB_BIST1_get_usb_bist_done_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC0_USB_BIST2                                                               0x18013908
#define MAC0_USB_BIST2_reg_addr                                                      "0xB8013908"
#define MAC0_USB_BIST2_reg                                                           0xB8013908
#define set_MAC0_USB_BIST2_reg(data)   (*((volatile unsigned int*) MAC0_USB_BIST2_reg)=data)
#define get_MAC0_USB_BIST2_reg   (*((volatile unsigned int*) MAC0_USB_BIST2_reg))
#define MAC0_USB_BIST2_inst_adr                                                      "0x0042"
#define MAC0_USB_BIST2_inst                                                          0x0042
#define MAC0_USB_BIST2_usb_bist_fail_host_ram_shift                                  (1)
#define MAC0_USB_BIST2_usb_bist_fail_host_ram_mask                                   (0x00000002)
#define MAC0_USB_BIST2_usb_bist_fail_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC0_USB_BIST2_usb_bist_fail_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_BIST2_get_usb_bist_fail_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_BIST2_usb_bist_fail_wrap_shift                                      (0)
#define MAC0_USB_BIST2_usb_bist_fail_wrap_mask                                       (0x00000001)
#define MAC0_USB_BIST2_usb_bist_fail_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC0_USB_BIST2_usb_bist_fail_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC0_USB_BIST2_get_usb_bist_fail_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC0_USB_DRF0                                                                0x18013918
#define MAC0_USB_DRF0_reg_addr                                                       "0xB8013918"
#define MAC0_USB_DRF0_reg                                                            0xB8013918
#define set_MAC0_USB_DRF0_reg(data)   (*((volatile unsigned int*) MAC0_USB_DRF0_reg)=data)
#define get_MAC0_USB_DRF0_reg   (*((volatile unsigned int*) MAC0_USB_DRF0_reg))
#define MAC0_USB_DRF0_inst_adr                                                       "0x0046"
#define MAC0_USB_DRF0_inst                                                           0x0046
#define MAC0_USB_DRF0_usb_drf_mode_host_ram_shift                                    (1)
#define MAC0_USB_DRF0_usb_drf_mode_host_ram_mask                                     (0x00000002)
#define MAC0_USB_DRF0_usb_drf_mode_host_ram(data)                                    (0x00000002&((data)<<1))
#define MAC0_USB_DRF0_usb_drf_mode_host_ram_src(data)                                ((0x00000002&(data))>>1)
#define MAC0_USB_DRF0_get_usb_drf_mode_host_ram(data)                                ((0x00000002&(data))>>1)
#define MAC0_USB_DRF0_usb_drf_mode_wrap_shift                                        (0)
#define MAC0_USB_DRF0_usb_drf_mode_wrap_mask                                         (0x00000001)
#define MAC0_USB_DRF0_usb_drf_mode_wrap(data)                                        (0x00000001&((data)<<0))
#define MAC0_USB_DRF0_usb_drf_mode_wrap_src(data)                                    ((0x00000001&(data))>>0)
#define MAC0_USB_DRF0_get_usb_drf_mode_wrap(data)                                    ((0x00000001&(data))>>0)


#define MAC0_USB_DRF1                                                                0x1801391c
#define MAC0_USB_DRF1_reg_addr                                                       "0xB801391C"
#define MAC0_USB_DRF1_reg                                                            0xB801391C
#define set_MAC0_USB_DRF1_reg(data)   (*((volatile unsigned int*) MAC0_USB_DRF1_reg)=data)
#define get_MAC0_USB_DRF1_reg   (*((volatile unsigned int*) MAC0_USB_DRF1_reg))
#define MAC0_USB_DRF1_inst_adr                                                       "0x0047"
#define MAC0_USB_DRF1_inst                                                           0x0047
#define MAC0_USB_DRF1_usb_drf_resume_host_ram_shift                                  (1)
#define MAC0_USB_DRF1_usb_drf_resume_host_ram_mask                                   (0x00000002)
#define MAC0_USB_DRF1_usb_drf_resume_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC0_USB_DRF1_usb_drf_resume_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_DRF1_get_usb_drf_resume_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC0_USB_DRF1_usb_drf_resume_wrap_shift                                      (0)
#define MAC0_USB_DRF1_usb_drf_resume_wrap_mask                                       (0x00000001)
#define MAC0_USB_DRF1_usb_drf_resume_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC0_USB_DRF1_usb_drf_resume_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC0_USB_DRF1_get_usb_drf_resume_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC0_USB_DRF2                                                                0x18013920
#define MAC0_USB_DRF2_reg_addr                                                       "0xB8013920"
#define MAC0_USB_DRF2_reg                                                            0xB8013920
#define set_MAC0_USB_DRF2_reg(data)   (*((volatile unsigned int*) MAC0_USB_DRF2_reg)=data)
#define get_MAC0_USB_DRF2_reg   (*((volatile unsigned int*) MAC0_USB_DRF2_reg))
#define MAC0_USB_DRF2_inst_adr                                                       "0x0048"
#define MAC0_USB_DRF2_inst                                                           0x0048
#define MAC0_USB_DRF2_usb_drf_done_host_ram_shift                                    (1)
#define MAC0_USB_DRF2_usb_drf_done_host_ram_mask                                     (0x00000002)
#define MAC0_USB_DRF2_usb_drf_done_host_ram(data)                                    (0x00000002&((data)<<1))
#define MAC0_USB_DRF2_usb_drf_done_host_ram_src(data)                                ((0x00000002&(data))>>1)
#define MAC0_USB_DRF2_get_usb_drf_done_host_ram(data)                                ((0x00000002&(data))>>1)
#define MAC0_USB_DRF2_usb_drf_done_wrap_shift                                        (0)
#define MAC0_USB_DRF2_usb_drf_done_wrap_mask                                         (0x00000001)
#define MAC0_USB_DRF2_usb_drf_done_wrap(data)                                        (0x00000001&((data)<<0))
#define MAC0_USB_DRF2_usb_drf_done_wrap_src(data)                                    ((0x00000001&(data))>>0)
#define MAC0_USB_DRF2_get_usb_drf_done_wrap(data)                                    ((0x00000001&(data))>>0)


#define MAC0_USB_DRF3                                                                0x18013924
#define MAC0_USB_DRF3_reg_addr                                                       "0xB8013924"
#define MAC0_USB_DRF3_reg                                                            0xB8013924
#define set_MAC0_USB_DRF3_reg(data)   (*((volatile unsigned int*) MAC0_USB_DRF3_reg)=data)
#define get_MAC0_USB_DRF3_reg   (*((volatile unsigned int*) MAC0_USB_DRF3_reg))
#define MAC0_USB_DRF3_inst_adr                                                       "0x0049"
#define MAC0_USB_DRF3_inst                                                           0x0049
#define MAC0_USB_DRF3_usb_drf_pause_host_ram_shift                                   (1)
#define MAC0_USB_DRF3_usb_drf_pause_host_ram_mask                                    (0x00000002)
#define MAC0_USB_DRF3_usb_drf_pause_host_ram(data)                                   (0x00000002&((data)<<1))
#define MAC0_USB_DRF3_usb_drf_pause_host_ram_src(data)                               ((0x00000002&(data))>>1)
#define MAC0_USB_DRF3_get_usb_drf_pause_host_ram(data)                               ((0x00000002&(data))>>1)
#define MAC0_USB_DRF3_usb_drf_pause_wrap_shift                                       (0)
#define MAC0_USB_DRF3_usb_drf_pause_wrap_mask                                        (0x00000001)
#define MAC0_USB_DRF3_usb_drf_pause_wrap(data)                                       (0x00000001&((data)<<0))
#define MAC0_USB_DRF3_usb_drf_pause_wrap_src(data)                                   ((0x00000001&(data))>>0)
#define MAC0_USB_DRF3_get_usb_drf_pause_wrap(data)                                   ((0x00000001&(data))>>0)


#define MAC0_USB_DRF4                                                                0x18013928
#define MAC0_USB_DRF4_reg_addr                                                       "0xB8013928"
#define MAC0_USB_DRF4_reg                                                            0xB8013928
#define set_MAC0_USB_DRF4_reg(data)   (*((volatile unsigned int*) MAC0_USB_DRF4_reg)=data)
#define get_MAC0_USB_DRF4_reg   (*((volatile unsigned int*) MAC0_USB_DRF4_reg))
#define MAC0_USB_DRF4_inst_adr                                                       "0x004A"
#define MAC0_USB_DRF4_inst                                                           0x004A
#define MAC0_USB_DRF4_usb_drf_fail_host_ram_shift                                    (1)
#define MAC0_USB_DRF4_usb_drf_fail_host_ram_mask                                     (0x00000002)
#define MAC0_USB_DRF4_usb_drf_fail_host_ram(data)                                    (0x00000002&((data)<<1))
#define MAC0_USB_DRF4_usb_drf_fail_host_ram_src(data)                                ((0x00000002&(data))>>1)
#define MAC0_USB_DRF4_get_usb_drf_fail_host_ram(data)                                ((0x00000002&(data))>>1)
#define MAC0_USB_DRF4_usb_drf_fail_wrap_shift                                        (0)
#define MAC0_USB_DRF4_usb_drf_fail_wrap_mask                                         (0x00000001)
#define MAC0_USB_DRF4_usb_drf_fail_wrap(data)                                        (0x00000001&((data)<<0))
#define MAC0_USB_DRF4_usb_drf_fail_wrap_src(data)                                    ((0x00000001&(data))>>0)
#define MAC0_USB_DRF4_get_usb_drf_fail_wrap(data)                                    ((0x00000001&(data))>>0)


#define MAC0_USB_BIST_OPTION0                                                        0x18013938
#define MAC0_USB_BIST_OPTION0_reg_addr                                               "0xB8013938"
#define MAC0_USB_BIST_OPTION0_reg                                                    0xB8013938
#define set_MAC0_USB_BIST_OPTION0_reg(data)   (*((volatile unsigned int*) MAC0_USB_BIST_OPTION0_reg)=data)
#define get_MAC0_USB_BIST_OPTION0_reg   (*((volatile unsigned int*) MAC0_USB_BIST_OPTION0_reg))
#define MAC0_USB_BIST_OPTION0_inst_adr                                               "0x004E"
#define MAC0_USB_BIST_OPTION0_inst                                                   0x004E
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_ls0_shift                                (5)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_ls0_mask                                 (0x00000020)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_ls0(data)                                (0x00000020&((data)<<5))
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_ls0_src(data)                            ((0x00000020&(data))>>5)
#define MAC0_USB_BIST_OPTION0_get_usb_bist_wrap_ls0(data)                            ((0x00000020&(data))>>5)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rme0_shift                               (4)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rme0_mask                                (0x00000010)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rme0(data)                               (0x00000010&((data)<<4))
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rme0_src(data)                           ((0x00000010&(data))>>4)
#define MAC0_USB_BIST_OPTION0_get_usb_bist_wrap_rme0(data)                           ((0x00000010&(data))>>4)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rm0_shift                                (0)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rm0_mask                                 (0x0000000F)
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rm0(data)                                (0x0000000F&((data)<<0))
#define MAC0_USB_BIST_OPTION0_usb_bist_wrap_rm0_src(data)                            ((0x0000000F&(data))>>0)
#define MAC0_USB_BIST_OPTION0_get_usb_bist_wrap_rm0(data)                            ((0x0000000F&(data))>>0)


#define MAC0_USB_BIST_OPTION1                                                        0x1801393c
#define MAC0_USB_BIST_OPTION1_reg_addr                                               "0xB801393C"
#define MAC0_USB_BIST_OPTION1_reg                                                    0xB801393C
#define set_MAC0_USB_BIST_OPTION1_reg(data)   (*((volatile unsigned int*) MAC0_USB_BIST_OPTION1_reg)=data)
#define get_MAC0_USB_BIST_OPTION1_reg   (*((volatile unsigned int*) MAC0_USB_BIST_OPTION1_reg))
#define MAC0_USB_BIST_OPTION1_inst_adr                                               "0x004F"
#define MAC0_USB_BIST_OPTION1_inst                                                   0x004F
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_ls0_shift                             (5)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_ls0_mask                              (0x00000020)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_ls0(data)                             (0x00000020&((data)<<5))
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_ls0_src(data)                         ((0x00000020&(data))>>5)
#define MAC0_USB_BIST_OPTION1_get_usb_usb_host_ram_ls0(data)                         ((0x00000020&(data))>>5)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rme0_shift                            (4)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rme0_mask                             (0x00000010)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rme0(data)                            (0x00000010&((data)<<4))
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rme0_src(data)                        ((0x00000010&(data))>>4)
#define MAC0_USB_BIST_OPTION1_get_usb_usb_host_ram_rme0(data)                        ((0x00000010&(data))>>4)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rm0_shift                             (0)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rm0_mask                              (0x0000000F)
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rm0(data)                             (0x0000000F&((data)<<0))
#define MAC0_USB_BIST_OPTION1_usb_usb_host_ram_rm0_src(data)                         ((0x0000000F&(data))>>0)
#define MAC0_USB_BIST_OPTION1_get_usb_usb_host_ram_rm0(data)                         ((0x0000000F&(data))>>0)


#define MAC1_WRAPP_REG                                                               0x18012800
#define MAC1_WRAPP_REG_reg_addr                                                      "0xB8012800"
#define MAC1_WRAPP_REG_reg                                                           0xB8012800
#define set_MAC1_WRAPP_REG_reg(data)   (*((volatile unsigned int*) MAC1_WRAPP_REG_reg)=data)
#define get_MAC1_WRAPP_REG_reg   (*((volatile unsigned int*) MAC1_WRAPP_REG_reg))
#define MAC1_WRAPP_REG_inst_adr                                                      "0x0000"
#define MAC1_WRAPP_REG_inst                                                          0x0000
#define MAC1_WRAPP_REG_Status_err_shift                                              (30)
#define MAC1_WRAPP_REG_Status_err_mask                                               (0xC0000000)
#define MAC1_WRAPP_REG_Status_err(data)                                              (0xC0000000&((data)<<30))
#define MAC1_WRAPP_REG_Status_err_src(data)                                          ((0xC0000000&(data))>>30)
#define MAC1_WRAPP_REG_get_Status_err(data)                                          ((0xC0000000&(data))>>30)
#define MAC1_WRAPP_REG_suspend_r_shift                                               (6)
#define MAC1_WRAPP_REG_suspend_r_mask                                                (0x00000040)
#define MAC1_WRAPP_REG_suspend_r(data)                                               (0x00000040&((data)<<6))
#define MAC1_WRAPP_REG_suspend_r_src(data)                                           ((0x00000040&(data))>>6)
#define MAC1_WRAPP_REG_get_suspend_r(data)                                           ((0x00000040&(data))>>6)
#define MAC1_WRAPP_REG_Debug_mux_shift                                               (1)
#define MAC1_WRAPP_REG_Debug_mux_mask                                                (0x0000003E)
#define MAC1_WRAPP_REG_Debug_mux(data)                                               (0x0000003E&((data)<<1))
#define MAC1_WRAPP_REG_Debug_mux_src(data)                                           ((0x0000003E&(data))>>1)
#define MAC1_WRAPP_REG_get_Debug_mux(data)                                           ((0x0000003E&(data))>>1)
#define MAC1_WRAPP_REG_packing_shift                                                 (0)
#define MAC1_WRAPP_REG_packing_mask                                                  (0x00000001)
#define MAC1_WRAPP_REG_packing(data)                                                 (0x00000001&((data)<<0))
#define MAC1_WRAPP_REG_packing_src(data)                                             ((0x00000001&(data))>>0)
#define MAC1_WRAPP_REG_get_packing(data)                                             ((0x00000001&(data))>>0)


#define MAC1_VSTATUS_REG                                                             0x18012804
#define MAC1_VSTATUS_REG_reg_addr                                                    "0xB8012804"
#define MAC1_VSTATUS_REG_reg                                                         0xB8012804
#define set_MAC1_VSTATUS_REG_reg(data)   (*((volatile unsigned int*) MAC1_VSTATUS_REG_reg)=data)
#define get_MAC1_VSTATUS_REG_reg   (*((volatile unsigned int*) MAC1_VSTATUS_REG_reg))
#define MAC1_VSTATUS_REG_inst_adr                                                    "0x0001"
#define MAC1_VSTATUS_REG_inst                                                        0x0001
#define MAC1_VSTATUS_REG_Vstatus_out_shift                                           (0)
#define MAC1_VSTATUS_REG_Vstatus_out_mask                                            (0x000000FF)
#define MAC1_VSTATUS_REG_Vstatus_out(data)                                           (0x000000FF&((data)<<0))
#define MAC1_VSTATUS_REG_Vstatus_out_src(data)                                       ((0x000000FF&(data))>>0)
#define MAC1_VSTATUS_REG_get_Vstatus_out(data)                                       ((0x000000FF&(data))>>0)


#define MAC1_USBIPINPUT_REG                                                          0x18012808
#define MAC1_USBIPINPUT_REG_reg_addr                                                 "0xB8012808"
#define MAC1_USBIPINPUT_REG_reg                                                      0xB8012808
#define set_MAC1_USBIPINPUT_REG_reg(data)   (*((volatile unsigned int*) MAC1_USBIPINPUT_REG_reg)=data)
#define get_MAC1_USBIPINPUT_REG_reg   (*((volatile unsigned int*) MAC1_USBIPINPUT_REG_reg))
#define MAC1_USBIPINPUT_REG_inst_adr                                                 "0x0002"
#define MAC1_USBIPINPUT_REG_inst                                                     0x0002
#define MAC1_USBIPINPUT_REG_pwr_mux_shift                                            (31)
#define MAC1_USBIPINPUT_REG_pwr_mux_mask                                             (0x80000000)
#define MAC1_USBIPINPUT_REG_pwr_mux(data)                                            (0x80000000&((data)<<31))
#define MAC1_USBIPINPUT_REG_pwr_mux_src(data)                                        ((0x80000000&(data))>>31)
#define MAC1_USBIPINPUT_REG_get_pwr_mux(data)                                        ((0x80000000&(data))>>31)
#define MAC1_USBIPINPUT_REG_ovrcur_mux_shift                                         (30)
#define MAC1_USBIPINPUT_REG_ovrcur_mux_mask                                          (0x40000000)
#define MAC1_USBIPINPUT_REG_ovrcur_mux(data)                                         (0x40000000&((data)<<30))
#define MAC1_USBIPINPUT_REG_ovrcur_mux_src(data)                                     ((0x40000000&(data))>>30)
#define MAC1_USBIPINPUT_REG_get_ovrcur_mux(data)                                     ((0x40000000&(data))>>30)
#define MAC1_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I_shift                           (29)
#define MAC1_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I_mask                            (0x20000000)
#define MAC1_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I(data)                           (0x20000000&((data)<<29))
#define MAC1_USBIPINPUT_REG_ss_resume_utmi_pls_dis_I_src(data)                       ((0x20000000&(data))>>29)
#define MAC1_USBIPINPUT_REG_get_ss_resume_utmi_pls_dis_I(data)                       ((0x20000000&(data))>>29)
#define MAC1_USBIPINPUT_REG_ss_utmi_backward_enb_i_shift                             (28)
#define MAC1_USBIPINPUT_REG_ss_utmi_backward_enb_i_mask                              (0x10000000)
#define MAC1_USBIPINPUT_REG_ss_utmi_backward_enb_i(data)                             (0x10000000&((data)<<28))
#define MAC1_USBIPINPUT_REG_ss_utmi_backward_enb_i_src(data)                         ((0x10000000&(data))>>28)
#define MAC1_USBIPINPUT_REG_get_ss_utmi_backward_enb_i(data)                         ((0x10000000&(data))>>28)
#define MAC1_USBIPINPUT_REG_utmi_suspend_mux_shift                                   (27)
#define MAC1_USBIPINPUT_REG_utmi_suspend_mux_mask                                    (0x08000000)
#define MAC1_USBIPINPUT_REG_utmi_suspend_mux(data)                                   (0x08000000&((data)<<27))
#define MAC1_USBIPINPUT_REG_utmi_suspend_mux_src(data)                               ((0x08000000&(data))>>27)
#define MAC1_USBIPINPUT_REG_get_utmi_suspend_mux(data)                               ((0x08000000&(data))>>27)
#define MAC1_USBIPINPUT_REG_host_disc_mux_shift                                      (26)
#define MAC1_USBIPINPUT_REG_host_disc_mux_mask                                       (0x04000000)
#define MAC1_USBIPINPUT_REG_host_disc_mux(data)                                      (0x04000000&((data)<<26))
#define MAC1_USBIPINPUT_REG_host_disc_mux_src(data)                                  ((0x04000000&(data))>>26)
#define MAC1_USBIPINPUT_REG_get_host_disc_mux(data)                                  ((0x04000000&(data))>>26)
#define MAC1_USBIPINPUT_REG_sys_interrupt_i_shift                                    (25)
#define MAC1_USBIPINPUT_REG_sys_interrupt_i_mask                                     (0x02000000)
#define MAC1_USBIPINPUT_REG_sys_interrupt_i(data)                                    (0x02000000&((data)<<25))
#define MAC1_USBIPINPUT_REG_sys_interrupt_i_src(data)                                ((0x02000000&(data))>>25)
#define MAC1_USBIPINPUT_REG_get_sys_interrupt_i(data)                                ((0x02000000&(data))>>25)
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq12_i_shift                                 (24)
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq12_i_mask                                  (0x01000000)
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq12_i(data)                                 (0x01000000&((data)<<24))
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq12_i_src(data)                             ((0x01000000&(data))>>24)
#define MAC1_USBIPINPUT_REG_get_ohci_0_app_irq12_i(data)                             ((0x01000000&(data))>>24)
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq1_i_shift                                  (23)
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq1_i_mask                                   (0x00800000)
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq1_i(data)                                  (0x00800000&((data)<<23))
#define MAC1_USBIPINPUT_REG_ohci_0_app_irq1_i_src(data)                              ((0x00800000&(data))>>23)
#define MAC1_USBIPINPUT_REG_get_ohci_0_app_irq1_i(data)                              ((0x00800000&(data))>>23)
#define MAC1_USBIPINPUT_REG_ohci_0_app_io_hit_i_shift                                (22)
#define MAC1_USBIPINPUT_REG_ohci_0_app_io_hit_i_mask                                 (0x00400000)
#define MAC1_USBIPINPUT_REG_ohci_0_app_io_hit_i(data)                                (0x00400000&((data)<<22))
#define MAC1_USBIPINPUT_REG_ohci_0_app_io_hit_i_src(data)                            ((0x00400000&(data))>>22)
#define MAC1_USBIPINPUT_REG_get_ohci_0_app_io_hit_i(data)                            ((0x00400000&(data))>>22)
#define MAC1_USBIPINPUT_REG_ss_nxt_power_state_valid_I_shift                         (21)
#define MAC1_USBIPINPUT_REG_ss_nxt_power_state_valid_I_mask                          (0x00200000)
#define MAC1_USBIPINPUT_REG_ss_nxt_power_state_valid_I(data)                         (0x00200000&((data)<<21))
#define MAC1_USBIPINPUT_REG_ss_nxt_power_state_valid_I_src(data)                     ((0x00200000&(data))>>21)
#define MAC1_USBIPINPUT_REG_get_ss_nxt_power_state_valid_I(data)                     ((0x00200000&(data))>>21)
#define MAC1_USBIPINPUT_REG_ss_next_power_state_i_shift                              (19)
#define MAC1_USBIPINPUT_REG_ss_next_power_state_i_mask                               (0x00180000)
#define MAC1_USBIPINPUT_REG_ss_next_power_state_i(data)                              (0x00180000&((data)<<19))
#define MAC1_USBIPINPUT_REG_ss_next_power_state_i_src(data)                          ((0x00180000&(data))>>19)
#define MAC1_USBIPINPUT_REG_get_ss_next_power_state_i(data)                          ((0x00180000&(data))>>19)
#define MAC1_USBIPINPUT_REG_ss_power_state_i_shift                                   (17)
#define MAC1_USBIPINPUT_REG_ss_power_state_i_mask                                    (0x00060000)
#define MAC1_USBIPINPUT_REG_ss_power_state_i(data)                                   (0x00060000&((data)<<17))
#define MAC1_USBIPINPUT_REG_ss_power_state_i_src(data)                               ((0x00060000&(data))>>17)
#define MAC1_USBIPINPUT_REG_get_ss_power_state_i(data)                               ((0x00060000&(data))>>17)
#define MAC1_USBIPINPUT_REG_ohci_0_cntsel_i_n_shift                                  (16)
#define MAC1_USBIPINPUT_REG_ohci_0_cntsel_i_n_mask                                   (0x00010000)
#define MAC1_USBIPINPUT_REG_ohci_0_cntsel_i_n(data)                                  (0x00010000&((data)<<16))
#define MAC1_USBIPINPUT_REG_ohci_0_cntsel_i_n_src(data)                              ((0x00010000&(data))>>16)
#define MAC1_USBIPINPUT_REG_get_ohci_0_cntsel_i_n(data)                              ((0x00010000&(data))>>16)
#define MAC1_USBIPINPUT_REG_ohci_0_clkcktrst_i_n_shift                               (15)
#define MAC1_USBIPINPUT_REG_ohci_0_clkcktrst_i_n_mask                                (0x00008000)
#define MAC1_USBIPINPUT_REG_ohci_0_clkcktrst_i_n(data)                               (0x00008000&((data)<<15))
#define MAC1_USBIPINPUT_REG_ohci_0_clkcktrst_i_n_src(data)                           ((0x00008000&(data))>>15)
#define MAC1_USBIPINPUT_REG_get_ohci_0_clkcktrst_i_n(data)                           ((0x00008000&(data))>>15)
#define MAC1_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i_shift                          (14)
#define MAC1_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i_mask                           (0x00004000)
#define MAC1_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i(data)                          (0x00004000&((data)<<14))
#define MAC1_USBIPINPUT_REG_ehci_chirp_k_quick_resp_i_src(data)                      ((0x00004000&(data))>>14)
#define MAC1_USBIPINPUT_REG_get_ehci_chirp_k_quick_resp_i(data)                      ((0x00004000&(data))>>14)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_5_i_shift                                   (13)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_5_i_mask                                    (0x00002000)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_5_i(data)                                   (0x00002000&((data)<<13))
#define MAC1_USBIPINPUT_REG_ss_fladj_val_5_i_src(data)                               ((0x00002000&(data))>>13)
#define MAC1_USBIPINPUT_REG_get_ss_fladj_val_5_i(data)                               ((0x00002000&(data))>>13)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_4_i_shift                                   (12)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_4_i_mask                                    (0x00001000)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_4_i(data)                                   (0x00001000&((data)<<12))
#define MAC1_USBIPINPUT_REG_ss_fladj_val_4_i_src(data)                               ((0x00001000&(data))>>12)
#define MAC1_USBIPINPUT_REG_get_ss_fladj_val_4_i(data)                               ((0x00001000&(data))>>12)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_3_i_shift                                   (11)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_3_i_mask                                    (0x00000800)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_3_i(data)                                   (0x00000800&((data)<<11))
#define MAC1_USBIPINPUT_REG_ss_fladj_val_3_i_src(data)                               ((0x00000800&(data))>>11)
#define MAC1_USBIPINPUT_REG_get_ss_fladj_val_3_i(data)                               ((0x00000800&(data))>>11)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_2_i_shift                                   (10)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_2_i_mask                                    (0x00000400)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_2_i(data)                                   (0x00000400&((data)<<10))
#define MAC1_USBIPINPUT_REG_ss_fladj_val_2_i_src(data)                               ((0x00000400&(data))>>10)
#define MAC1_USBIPINPUT_REG_get_ss_fladj_val_2_i(data)                               ((0x00000400&(data))>>10)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_1_i_shift                                   (9)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_1_i_mask                                    (0x00000200)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_1_i(data)                                   (0x00000200&((data)<<9))
#define MAC1_USBIPINPUT_REG_ss_fladj_val_1_i_src(data)                               ((0x00000200&(data))>>9)
#define MAC1_USBIPINPUT_REG_get_ss_fladj_val_1_i(data)                               ((0x00000200&(data))>>9)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_0_i_shift                                   (8)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_0_i_mask                                    (0x00000100)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_0_i(data)                                   (0x00000100&((data)<<8))
#define MAC1_USBIPINPUT_REG_ss_fladj_val_0_i_src(data)                               ((0x00000100&(data))>>8)
#define MAC1_USBIPINPUT_REG_get_ss_fladj_val_0_i(data)                               ((0x00000100&(data))>>8)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_host_i_shift                                (2)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_host_i_mask                                 (0x000000FC)
#define MAC1_USBIPINPUT_REG_ss_fladj_val_host_i(data)                                (0x000000FC&((data)<<2))
#define MAC1_USBIPINPUT_REG_ss_fladj_val_host_i_src(data)                            ((0x000000FC&(data))>>2)
#define MAC1_USBIPINPUT_REG_get_ss_fladj_val_host_i(data)                            ((0x000000FC&(data))>>2)
#define MAC1_USBIPINPUT_REG_ss_simulation_mode_i_shift                               (1)
#define MAC1_USBIPINPUT_REG_ss_simulation_mode_i_mask                                (0x00000002)
#define MAC1_USBIPINPUT_REG_ss_simulation_mode_i(data)                               (0x00000002&((data)<<1))
#define MAC1_USBIPINPUT_REG_ss_simulation_mode_i_src(data)                           ((0x00000002&(data))>>1)
#define MAC1_USBIPINPUT_REG_get_ss_simulation_mode_i(data)                           ((0x00000002&(data))>>1)
#define MAC1_USBIPINPUT_REG_ss_word_if_i_shift                                       (0)
#define MAC1_USBIPINPUT_REG_ss_word_if_i_mask                                        (0x00000001)
#define MAC1_USBIPINPUT_REG_ss_word_if_i(data)                                       (0x00000001&((data)<<0))
#define MAC1_USBIPINPUT_REG_ss_word_if_i_src(data)                                   ((0x00000001&(data))>>0)
#define MAC1_USBIPINPUT_REG_get_ss_word_if_i(data)                                   ((0x00000001&(data))>>0)


#define MAC1_RESET_UTMI_REG                                                          0x1801280c
#define MAC1_RESET_UTMI_REG_reg_addr                                                 "0xB801280C"
#define MAC1_RESET_UTMI_REG_reg                                                      0xB801280C
#define set_MAC1_RESET_UTMI_REG_reg(data)   (*((volatile unsigned int*) MAC1_RESET_UTMI_REG_reg)=data)
#define get_MAC1_RESET_UTMI_REG_reg   (*((volatile unsigned int*) MAC1_RESET_UTMI_REG_reg))
#define MAC1_RESET_UTMI_REG_inst_adr                                                 "0x0003"
#define MAC1_RESET_UTMI_REG_inst                                                     0x0003
#define MAC1_RESET_UTMI_REG_Test_rst_shift                                           (2)
#define MAC1_RESET_UTMI_REG_Test_rst_mask                                            (0x00000004)
#define MAC1_RESET_UTMI_REG_Test_rst(data)                                           (0x00000004&((data)<<2))
#define MAC1_RESET_UTMI_REG_Test_rst_src(data)                                       ((0x00000004&(data))>>2)
#define MAC1_RESET_UTMI_REG_get_Test_rst(data)                                       ((0x00000004&(data))>>2)
#define MAC1_RESET_UTMI_REG_Test_en_shift                                            (1)
#define MAC1_RESET_UTMI_REG_Test_en_mask                                             (0x00000002)
#define MAC1_RESET_UTMI_REG_Test_en(data)                                            (0x00000002&((data)<<1))
#define MAC1_RESET_UTMI_REG_Test_en_src(data)                                        ((0x00000002&(data))>>1)
#define MAC1_RESET_UTMI_REG_get_Test_en(data)                                        ((0x00000002&(data))>>1)
#define MAC1_RESET_UTMI_REG_Reset_UTMI_shift                                         (0)
#define MAC1_RESET_UTMI_REG_Reset_UTMI_mask                                          (0x00000001)
#define MAC1_RESET_UTMI_REG_Reset_UTMI(data)                                         (0x00000001&((data)<<0))
#define MAC1_RESET_UTMI_REG_Reset_UTMI_src(data)                                     ((0x00000001&(data))>>0)
#define MAC1_RESET_UTMI_REG_get_Reset_UTMI(data)                                     ((0x00000001&(data))>>0)


#define MAC1_SELF_LOOP_BACK_REG                                                      0x18012810
#define MAC1_SELF_LOOP_BACK_REG_reg_addr                                             "0xB8012810"
#define MAC1_SELF_LOOP_BACK_REG_reg                                                  0xB8012810
#define set_MAC1_SELF_LOOP_BACK_REG_reg(data)   (*((volatile unsigned int*) MAC1_SELF_LOOP_BACK_REG_reg)=data)
#define get_MAC1_SELF_LOOP_BACK_REG_reg   (*((volatile unsigned int*) MAC1_SELF_LOOP_BACK_REG_reg))
#define MAC1_SELF_LOOP_BACK_REG_inst_adr                                             "0x0004"
#define MAC1_SELF_LOOP_BACK_REG_inst                                                 0x0004
#define MAC1_SELF_LOOP_BACK_REG_Force_test_opmode_en_shift                           (22)
#define MAC1_SELF_LOOP_BACK_REG_Force_test_opmode_en_mask                            (0x00400000)
#define MAC1_SELF_LOOP_BACK_REG_Force_test_opmode_en(data)                           (0x00400000&((data)<<22))
#define MAC1_SELF_LOOP_BACK_REG_Force_test_opmode_en_src(data)                       ((0x00400000&(data))>>22)
#define MAC1_SELF_LOOP_BACK_REG_get_Force_test_opmode_en(data)                       ((0x00400000&(data))>>22)
#define MAC1_SELF_LOOP_BACK_REG_test_opmode_shift                                    (20)
#define MAC1_SELF_LOOP_BACK_REG_test_opmode_mask                                     (0x00300000)
#define MAC1_SELF_LOOP_BACK_REG_test_opmode(data)                                    (0x00300000&((data)<<20))
#define MAC1_SELF_LOOP_BACK_REG_test_opmode_src(data)                                ((0x00300000&(data))>>20)
#define MAC1_SELF_LOOP_BACK_REG_get_test_opmode(data)                                ((0x00300000&(data))>>20)
#define MAC1_SELF_LOOP_BACK_REG_Force_test_txvalid_en_shift                          (19)
#define MAC1_SELF_LOOP_BACK_REG_Force_test_txvalid_en_mask                           (0x00080000)
#define MAC1_SELF_LOOP_BACK_REG_Force_test_txvalid_en(data)                          (0x00080000&((data)<<19))
#define MAC1_SELF_LOOP_BACK_REG_Force_test_txvalid_en_src(data)                      ((0x00080000&(data))>>19)
#define MAC1_SELF_LOOP_BACK_REG_get_Force_test_txvalid_en(data)                      ((0x00080000&(data))>>19)
#define MAC1_SELF_LOOP_BACK_REG_test_txvalid_shift                                   (18)
#define MAC1_SELF_LOOP_BACK_REG_test_txvalid_mask                                    (0x00040000)
#define MAC1_SELF_LOOP_BACK_REG_test_txvalid(data)                                   (0x00040000&((data)<<18))
#define MAC1_SELF_LOOP_BACK_REG_test_txvalid_src(data)                               ((0x00040000&(data))>>18)
#define MAC1_SELF_LOOP_BACK_REG_get_test_txvalid(data)                               ((0x00040000&(data))>>18)
#define MAC1_SELF_LOOP_BACK_REG_Simulation_mode_shift                                (17)
#define MAC1_SELF_LOOP_BACK_REG_Simulation_mode_mask                                 (0x00020000)
#define MAC1_SELF_LOOP_BACK_REG_Simulation_mode(data)                                (0x00020000&((data)<<17))
#define MAC1_SELF_LOOP_BACK_REG_Simulation_mode_src(data)                            ((0x00020000&(data))>>17)
#define MAC1_SELF_LOOP_BACK_REG_get_Simulation_mode(data)                            ((0x00020000&(data))>>17)
#define MAC1_SELF_LOOP_BACK_REG_Force_hs_mode_shift                                  (16)
#define MAC1_SELF_LOOP_BACK_REG_Force_hs_mode_mask                                   (0x00010000)
#define MAC1_SELF_LOOP_BACK_REG_Force_hs_mode(data)                                  (0x00010000&((data)<<16))
#define MAC1_SELF_LOOP_BACK_REG_Force_hs_mode_src(data)                              ((0x00010000&(data))>>16)
#define MAC1_SELF_LOOP_BACK_REG_get_Force_hs_mode(data)                              ((0x00010000&(data))>>16)
#define MAC1_SELF_LOOP_BACK_REG_Test_done_shift                                      (13)
#define MAC1_SELF_LOOP_BACK_REG_Test_done_mask                                       (0x00002000)
#define MAC1_SELF_LOOP_BACK_REG_Test_done(data)                                      (0x00002000&((data)<<13))
#define MAC1_SELF_LOOP_BACK_REG_Test_done_src(data)                                  ((0x00002000&(data))>>13)
#define MAC1_SELF_LOOP_BACK_REG_get_Test_done(data)                                  ((0x00002000&(data))>>13)
#define MAC1_SELF_LOOP_BACK_REG_Test_fail_shift                                      (12)
#define MAC1_SELF_LOOP_BACK_REG_Test_fail_mask                                       (0x00001000)
#define MAC1_SELF_LOOP_BACK_REG_Test_fail(data)                                      (0x00001000&((data)<<12))
#define MAC1_SELF_LOOP_BACK_REG_Test_fail_src(data)                                  ((0x00001000&(data))>>12)
#define MAC1_SELF_LOOP_BACK_REG_get_Test_fail(data)                                  ((0x00001000&(data))>>12)
#define MAC1_SELF_LOOP_BACK_REG_Test_speed_shift                                     (10)
#define MAC1_SELF_LOOP_BACK_REG_Test_speed_mask                                      (0x00000C00)
#define MAC1_SELF_LOOP_BACK_REG_Test_speed(data)                                     (0x00000C00&((data)<<10))
#define MAC1_SELF_LOOP_BACK_REG_Test_speed_src(data)                                 ((0x00000C00&(data))>>10)
#define MAC1_SELF_LOOP_BACK_REG_get_Test_speed(data)                                 ((0x00000C00&(data))>>10)
#define MAC1_SELF_LOOP_BACK_REG_Test_seed_shift                                      (2)
#define MAC1_SELF_LOOP_BACK_REG_Test_seed_mask                                       (0x000003FC)
#define MAC1_SELF_LOOP_BACK_REG_Test_seed(data)                                      (0x000003FC&((data)<<2))
#define MAC1_SELF_LOOP_BACK_REG_Test_seed_src(data)                                  ((0x000003FC&(data))>>2)
#define MAC1_SELF_LOOP_BACK_REG_get_Test_seed(data)                                  ((0x000003FC&(data))>>2)
#define MAC1_SELF_LOOP_BACK_REG_Test_psl_shift                                       (0)
#define MAC1_SELF_LOOP_BACK_REG_Test_psl_mask                                        (0x00000003)
#define MAC1_SELF_LOOP_BACK_REG_Test_psl(data)                                       (0x00000003&((data)<<0))
#define MAC1_SELF_LOOP_BACK_REG_Test_psl_src(data)                                   ((0x00000003&(data))>>0)
#define MAC1_SELF_LOOP_BACK_REG_get_Test_psl(data)                                   ((0x00000003&(data))>>0)


#define MAC1_VERSION_REG                                                             0x18012814
#define MAC1_VERSION_REG_reg_addr                                                    "0xB8012814"
#define MAC1_VERSION_REG_reg                                                         0xB8012814
#define set_MAC1_VERSION_REG_reg(data)   (*((volatile unsigned int*) MAC1_VERSION_REG_reg)=data)
#define get_MAC1_VERSION_REG_reg   (*((volatile unsigned int*) MAC1_VERSION_REG_reg))
#define MAC1_VERSION_REG_inst_adr                                                    "0x0005"
#define MAC1_VERSION_REG_inst                                                        0x0005
#define MAC1_VERSION_REG_trans_flag_host_shift                                       (11)
#define MAC1_VERSION_REG_trans_flag_host_mask                                        (0x00000800)
#define MAC1_VERSION_REG_trans_flag_host(data)                                       (0x00000800&((data)<<11))
#define MAC1_VERSION_REG_trans_flag_host_src(data)                                   ((0x00000800&(data))>>11)
#define MAC1_VERSION_REG_get_trans_flag_host(data)                                   ((0x00000800&(data))>>11)
#define MAC1_VERSION_REG_trans_flag_otg_shift                                        (10)
#define MAC1_VERSION_REG_trans_flag_otg_mask                                         (0x00000400)
#define MAC1_VERSION_REG_trans_flag_otg(data)                                        (0x00000400&((data)<<10))
#define MAC1_VERSION_REG_trans_flag_otg_src(data)                                    ((0x00000400&(data))>>10)
#define MAC1_VERSION_REG_get_trans_flag_otg(data)                                    ((0x00000400&(data))>>10)
#define MAC1_VERSION_REG_Dummy_reg_shift                                             (2)
#define MAC1_VERSION_REG_Dummy_reg_mask                                              (0x000003FC)
#define MAC1_VERSION_REG_Dummy_reg(data)                                             (0x000003FC&((data)<<2))
#define MAC1_VERSION_REG_Dummy_reg_src(data)                                         ((0x000003FC&(data))>>2)
#define MAC1_VERSION_REG_get_Dummy_reg(data)                                         ((0x000003FC&(data))>>2)
#define MAC1_VERSION_REG_Nouse_done_shift                                            (1)
#define MAC1_VERSION_REG_Nouse_done_mask                                             (0x00000002)
#define MAC1_VERSION_REG_Nouse_done(data)                                            (0x00000002&((data)<<1))
#define MAC1_VERSION_REG_Nouse_done_src(data)                                        ((0x00000002&(data))>>1)
#define MAC1_VERSION_REG_get_Nouse_done(data)                                        ((0x00000002&(data))>>1)
#define MAC1_VERSION_REG_Wrap_version_shift                                          (0)
#define MAC1_VERSION_REG_Wrap_version_mask                                           (0x00000001)
#define MAC1_VERSION_REG_Wrap_version(data)                                          (0x00000001&((data)<<0))
#define MAC1_VERSION_REG_Wrap_version_src(data)                                      ((0x00000001&(data))>>0)
#define MAC1_VERSION_REG_get_Wrap_version(data)                                      ((0x00000001&(data))>>0)


#define MAC1_WRAPP_2PORT_REG                                                         0x18012820
#define MAC1_WRAPP_2PORT_REG_reg_addr                                                "0xB8012820"
#define MAC1_WRAPP_2PORT_REG_reg                                                     0xB8012820
#define set_MAC1_WRAPP_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC1_WRAPP_2PORT_REG_reg)=data)
#define get_MAC1_WRAPP_2PORT_REG_reg   (*((volatile unsigned int*) MAC1_WRAPP_2PORT_REG_reg))
#define MAC1_WRAPP_2PORT_REG_inst_adr                                                "0x0008"
#define MAC1_WRAPP_2PORT_REG_inst                                                    0x0008
#define MAC1_WRAPP_2PORT_REG_suspend_r_shift                                         (6)
#define MAC1_WRAPP_2PORT_REG_suspend_r_mask                                          (0x00000040)
#define MAC1_WRAPP_2PORT_REG_suspend_r(data)                                         (0x00000040&((data)<<6))
#define MAC1_WRAPP_2PORT_REG_suspend_r_src(data)                                     ((0x00000040&(data))>>6)
#define MAC1_WRAPP_2PORT_REG_get_suspend_r(data)                                     ((0x00000040&(data))>>6)


#define MAC1_VSTATUS_2PORT_REG                                                       0x18012824
#define MAC1_VSTATUS_2PORT_REG_reg_addr                                              "0xB8012824"
#define MAC1_VSTATUS_2PORT_REG_reg                                                   0xB8012824
#define set_MAC1_VSTATUS_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC1_VSTATUS_2PORT_REG_reg)=data)
#define get_MAC1_VSTATUS_2PORT_REG_reg   (*((volatile unsigned int*) MAC1_VSTATUS_2PORT_REG_reg))
#define MAC1_VSTATUS_2PORT_REG_inst_adr                                              "0x0009"
#define MAC1_VSTATUS_2PORT_REG_inst                                                  0x0009
#define MAC1_VSTATUS_2PORT_REG_Vstatus_out_shift                                     (0)
#define MAC1_VSTATUS_2PORT_REG_Vstatus_out_mask                                      (0x000000FF)
#define MAC1_VSTATUS_2PORT_REG_Vstatus_out(data)                                     (0x000000FF&((data)<<0))
#define MAC1_VSTATUS_2PORT_REG_Vstatus_out_src(data)                                 ((0x000000FF&(data))>>0)
#define MAC1_VSTATUS_2PORT_REG_get_Vstatus_out(data)                                 ((0x000000FF&(data))>>0)


#define MAC1_USBIPINPUT_2PORT_REG                                                    0x18012828
#define MAC1_USBIPINPUT_2PORT_REG_reg_addr                                           "0xB8012828"
#define MAC1_USBIPINPUT_2PORT_REG_reg                                                0xB8012828
#define set_MAC1_USBIPINPUT_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC1_USBIPINPUT_2PORT_REG_reg)=data)
#define get_MAC1_USBIPINPUT_2PORT_REG_reg   (*((volatile unsigned int*) MAC1_USBIPINPUT_2PORT_REG_reg))
#define MAC1_USBIPINPUT_2PORT_REG_inst_adr                                           "0x000A"
#define MAC1_USBIPINPUT_2PORT_REG_inst                                               0x000A
#define MAC1_USBIPINPUT_2PORT_REG_pwr_mux_shift                                      (31)
#define MAC1_USBIPINPUT_2PORT_REG_pwr_mux_mask                                       (0x80000000)
#define MAC1_USBIPINPUT_2PORT_REG_pwr_mux(data)                                      (0x80000000&((data)<<31))
#define MAC1_USBIPINPUT_2PORT_REG_pwr_mux_src(data)                                  ((0x80000000&(data))>>31)
#define MAC1_USBIPINPUT_2PORT_REG_get_pwr_mux(data)                                  ((0x80000000&(data))>>31)
#define MAC1_USBIPINPUT_2PORT_REG_ovrcur_mux_shift                                   (30)
#define MAC1_USBIPINPUT_2PORT_REG_ovrcur_mux_mask                                    (0x40000000)
#define MAC1_USBIPINPUT_2PORT_REG_ovrcur_mux(data)                                   (0x40000000&((data)<<30))
#define MAC1_USBIPINPUT_2PORT_REG_ovrcur_mux_src(data)                               ((0x40000000&(data))>>30)
#define MAC1_USBIPINPUT_2PORT_REG_get_ovrcur_mux(data)                               ((0x40000000&(data))>>30)
#define MAC1_USBIPINPUT_2PORT_REG_utmi_suspend_mux_shift                             (27)
#define MAC1_USBIPINPUT_2PORT_REG_utmi_suspend_mux_mask                              (0x08000000)
#define MAC1_USBIPINPUT_2PORT_REG_utmi_suspend_mux(data)                             (0x08000000&((data)<<27))
#define MAC1_USBIPINPUT_2PORT_REG_utmi_suspend_mux_src(data)                         ((0x08000000&(data))>>27)
#define MAC1_USBIPINPUT_2PORT_REG_get_utmi_suspend_mux(data)                         ((0x08000000&(data))>>27)
#define MAC1_USBIPINPUT_2PORT_REG_host_disc_mux_shift                                (26)
#define MAC1_USBIPINPUT_2PORT_REG_host_disc_mux_mask                                 (0x04000000)
#define MAC1_USBIPINPUT_2PORT_REG_host_disc_mux(data)                                (0x04000000&((data)<<26))
#define MAC1_USBIPINPUT_2PORT_REG_host_disc_mux_src(data)                            ((0x04000000&(data))>>26)
#define MAC1_USBIPINPUT_2PORT_REG_get_host_disc_mux(data)                            ((0x04000000&(data))>>26)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i_shift                             (13)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i_mask                              (0x00002000)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i(data)                             (0x00002000&((data)<<13))
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_5_i_src(data)                         ((0x00002000&(data))>>13)
#define MAC1_USBIPINPUT_2PORT_REG_get_ss_fladj_val_5_i(data)                         ((0x00002000&(data))>>13)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i_shift                             (12)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i_mask                              (0x00001000)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i(data)                             (0x00001000&((data)<<12))
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_4_i_src(data)                         ((0x00001000&(data))>>12)
#define MAC1_USBIPINPUT_2PORT_REG_get_ss_fladj_val_4_i(data)                         ((0x00001000&(data))>>12)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i_shift                             (11)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i_mask                              (0x00000800)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i(data)                             (0x00000800&((data)<<11))
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_3_i_src(data)                         ((0x00000800&(data))>>11)
#define MAC1_USBIPINPUT_2PORT_REG_get_ss_fladj_val_3_i(data)                         ((0x00000800&(data))>>11)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i_shift                             (10)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i_mask                              (0x00000400)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i(data)                             (0x00000400&((data)<<10))
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_2_i_src(data)                         ((0x00000400&(data))>>10)
#define MAC1_USBIPINPUT_2PORT_REG_get_ss_fladj_val_2_i(data)                         ((0x00000400&(data))>>10)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i_shift                             (9)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i_mask                              (0x00000200)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i(data)                             (0x00000200&((data)<<9))
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_1_i_src(data)                         ((0x00000200&(data))>>9)
#define MAC1_USBIPINPUT_2PORT_REG_get_ss_fladj_val_1_i(data)                         ((0x00000200&(data))>>9)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i_shift                             (8)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i_mask                              (0x00000100)
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i(data)                             (0x00000100&((data)<<8))
#define MAC1_USBIPINPUT_2PORT_REG_ss_fladj_val_0_i_src(data)                         ((0x00000100&(data))>>8)
#define MAC1_USBIPINPUT_2PORT_REG_get_ss_fladj_val_0_i(data)                         ((0x00000100&(data))>>8)


#define MAC1_RESET_UTMI_2PORT_REG                                                    0x1801282c
#define MAC1_RESET_UTMI_2PORT_REG_reg_addr                                           "0xB801282C"
#define MAC1_RESET_UTMI_2PORT_REG_reg                                                0xB801282C
#define set_MAC1_RESET_UTMI_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC1_RESET_UTMI_2PORT_REG_reg)=data)
#define get_MAC1_RESET_UTMI_2PORT_REG_reg   (*((volatile unsigned int*) MAC1_RESET_UTMI_2PORT_REG_reg))
#define MAC1_RESET_UTMI_2PORT_REG_inst_adr                                           "0x000B"
#define MAC1_RESET_UTMI_2PORT_REG_inst                                               0x000B
#define MAC1_RESET_UTMI_2PORT_REG_Test_rst_shift                                     (2)
#define MAC1_RESET_UTMI_2PORT_REG_Test_rst_mask                                      (0x00000004)
#define MAC1_RESET_UTMI_2PORT_REG_Test_rst(data)                                     (0x00000004&((data)<<2))
#define MAC1_RESET_UTMI_2PORT_REG_Test_rst_src(data)                                 ((0x00000004&(data))>>2)
#define MAC1_RESET_UTMI_2PORT_REG_get_Test_rst(data)                                 ((0x00000004&(data))>>2)
#define MAC1_RESET_UTMI_2PORT_REG_Test_en_shift                                      (1)
#define MAC1_RESET_UTMI_2PORT_REG_Test_en_mask                                       (0x00000002)
#define MAC1_RESET_UTMI_2PORT_REG_Test_en(data)                                      (0x00000002&((data)<<1))
#define MAC1_RESET_UTMI_2PORT_REG_Test_en_src(data)                                  ((0x00000002&(data))>>1)
#define MAC1_RESET_UTMI_2PORT_REG_get_Test_en(data)                                  ((0x00000002&(data))>>1)
#define MAC1_RESET_UTMI_2PORT_REG_Reset_UTMI_shift                                   (0)
#define MAC1_RESET_UTMI_2PORT_REG_Reset_UTMI_mask                                    (0x00000001)
#define MAC1_RESET_UTMI_2PORT_REG_Reset_UTMI(data)                                   (0x00000001&((data)<<0))
#define MAC1_RESET_UTMI_2PORT_REG_Reset_UTMI_src(data)                               ((0x00000001&(data))>>0)
#define MAC1_RESET_UTMI_2PORT_REG_get_Reset_UTMI(data)                               ((0x00000001&(data))>>0)


#define MAC1_SELF_LOOP_BACK_2PORT_REG                                                0x18012830
#define MAC1_SELF_LOOP_BACK_2PORT_REG_reg_addr                                       "0xB8012830"
#define MAC1_SELF_LOOP_BACK_2PORT_REG_reg                                            0xB8012830
#define set_MAC1_SELF_LOOP_BACK_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC1_SELF_LOOP_BACK_2PORT_REG_reg)=data)
#define get_MAC1_SELF_LOOP_BACK_2PORT_REG_reg   (*((volatile unsigned int*) MAC1_SELF_LOOP_BACK_2PORT_REG_reg))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_inst_adr                                       "0x000C"
#define MAC1_SELF_LOOP_BACK_2PORT_REG_inst                                           0x000C
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en_shift                     (22)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en_mask                      (0x00400000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en(data)                     (0x00400000&((data)<<22))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_opmode_en_src(data)                 ((0x00400000&(data))>>22)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Force_test_opmode_en(data)                 ((0x00400000&(data))>>22)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_opmode_shift                              (20)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_opmode_mask                               (0x00300000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_opmode(data)                              (0x00300000&((data)<<20))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_opmode_src(data)                          ((0x00300000&(data))>>20)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_test_opmode(data)                          ((0x00300000&(data))>>20)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en_shift                    (19)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en_mask                     (0x00080000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en(data)                    (0x00080000&((data)<<19))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_test_txvalid_en_src(data)                ((0x00080000&(data))>>19)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Force_test_txvalid_en(data)                ((0x00080000&(data))>>19)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_txvalid_shift                             (18)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_txvalid_mask                              (0x00040000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_txvalid(data)                             (0x00040000&((data)<<18))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_test_txvalid_src(data)                         ((0x00040000&(data))>>18)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_test_txvalid(data)                         ((0x00040000&(data))>>18)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Simulation_mode_shift                          (17)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Simulation_mode_mask                           (0x00020000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Simulation_mode(data)                          (0x00020000&((data)<<17))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Simulation_mode_src(data)                      ((0x00020000&(data))>>17)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Simulation_mode(data)                      ((0x00020000&(data))>>17)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode_shift                            (16)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode_mask                             (0x00010000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode(data)                            (0x00010000&((data)<<16))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Force_hs_mode_src(data)                        ((0x00010000&(data))>>16)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Force_hs_mode(data)                        ((0x00010000&(data))>>16)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_done_shift                                (13)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_done_mask                                 (0x00002000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_done(data)                                (0x00002000&((data)<<13))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_done_src(data)                            ((0x00002000&(data))>>13)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Test_done(data)                            ((0x00002000&(data))>>13)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_fail_shift                                (12)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_fail_mask                                 (0x00001000)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_fail(data)                                (0x00001000&((data)<<12))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_fail_src(data)                            ((0x00001000&(data))>>12)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Test_fail(data)                            ((0x00001000&(data))>>12)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_speed_shift                               (10)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_speed_mask                                (0x00000C00)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_speed(data)                               (0x00000C00&((data)<<10))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_speed_src(data)                           ((0x00000C00&(data))>>10)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Test_speed(data)                           ((0x00000C00&(data))>>10)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_seed_shift                                (2)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_seed_mask                                 (0x000003FC)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_seed(data)                                (0x000003FC&((data)<<2))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_seed_src(data)                            ((0x000003FC&(data))>>2)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Test_seed(data)                            ((0x000003FC&(data))>>2)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_psl_shift                                 (0)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_psl_mask                                  (0x00000003)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_psl(data)                                 (0x00000003&((data)<<0))
#define MAC1_SELF_LOOP_BACK_2PORT_REG_Test_psl_src(data)                             ((0x00000003&(data))>>0)
#define MAC1_SELF_LOOP_BACK_2PORT_REG_get_Test_psl(data)                             ((0x00000003&(data))>>0)


#define MAC1_IPNEWINPUT_2PORT_REG                                                    0x18012834
#define MAC1_IPNEWINPUT_2PORT_REG_reg_addr                                           "0xB8012834"
#define MAC1_IPNEWINPUT_2PORT_REG_reg                                                0xB8012834
#define set_MAC1_IPNEWINPUT_2PORT_REG_reg(data)   (*((volatile unsigned int*) MAC1_IPNEWINPUT_2PORT_REG_reg)=data)
#define get_MAC1_IPNEWINPUT_2PORT_REG_reg   (*((volatile unsigned int*) MAC1_IPNEWINPUT_2PORT_REG_reg))
#define MAC1_IPNEWINPUT_2PORT_REG_inst_adr                                           "0x000D"
#define MAC1_IPNEWINPUT_2PORT_REG_inst                                               0x000D
#define MAC1_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i_shift                          (31)
#define MAC1_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i_mask                           (0x80000000)
#define MAC1_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i(data)                          (0x80000000&((data)<<31))
#define MAC1_IPNEWINPUT_2PORT_REG_p1_app_prt_ovrcur_i_src(data)                      ((0x80000000&(data))>>31)
#define MAC1_IPNEWINPUT_2PORT_REG_get_p1_app_prt_ovrcur_i(data)                      ((0x80000000&(data))>>31)
#define MAC1_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i_shift                          (30)
#define MAC1_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i_mask                           (0x40000000)
#define MAC1_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i(data)                          (0x40000000&((data)<<30))
#define MAC1_IPNEWINPUT_2PORT_REG_P0_app_prt_ovrcur_i_src(data)                      ((0x40000000&(data))>>30)
#define MAC1_IPNEWINPUT_2PORT_REG_get_P0_app_prt_ovrcur_i(data)                      ((0x40000000&(data))>>30)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i_shift                            (3)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i_mask                             (0x00000008)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i(data)                            (0x00000008&((data)<<3))
#define MAC1_IPNEWINPUT_2PORT_REG_ss_ulpi_pp2vbus_i_src(data)                        ((0x00000008&(data))>>3)
#define MAC1_IPNEWINPUT_2PORT_REG_get_ss_ulpi_pp2vbus_i(data)                        ((0x00000008&(data))>>3)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i_shift                   (2)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i_mask                    (0x00000004)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i(data)                   (0x00000004&((data)<<2))
#define MAC1_IPNEWINPUT_2PORT_REG_ss_autoppd_on_overcur_en_i_src(data)               ((0x00000004&(data))>>2)
#define MAC1_IPNEWINPUT_2PORT_REG_get_ss_autoppd_on_overcur_en_i(data)               ((0x00000004&(data))>>2)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i_shift                       (1)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i_mask                        (0x00000002)
#define MAC1_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i(data)                       (0x00000002&((data)<<1))
#define MAC1_IPNEWINPUT_2PORT_REG_ss_power_state_valid_i_src(data)                   ((0x00000002&(data))>>1)
#define MAC1_IPNEWINPUT_2PORT_REG_get_ss_power_state_valid_i(data)                   ((0x00000002&(data))>>1)
#define MAC1_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel_shift                            (0)
#define MAC1_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel_mask                             (0x00000001)
#define MAC1_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel(data)                            (0x00000001&((data)<<0))
#define MAC1_IPNEWINPUT_2PORT_REG_reg_usb_ck27m_sel_src(data)                        ((0x00000001&(data))>>0)
#define MAC1_IPNEWINPUT_2PORT_REG_get_reg_usb_ck27m_sel(data)                        ((0x00000001&(data))>>0)


#define MAC1_USBPHY_SLB0_REG                                                         0x18012838
#define MAC1_USBPHY_SLB0_REG_reg_addr                                                "0xB8012838"
#define MAC1_USBPHY_SLB0_REG_reg                                                     0xB8012838
#define set_MAC1_USBPHY_SLB0_REG_reg(data)   (*((volatile unsigned int*) MAC1_USBPHY_SLB0_REG_reg)=data)
#define get_MAC1_USBPHY_SLB0_REG_reg   (*((volatile unsigned int*) MAC1_USBPHY_SLB0_REG_reg))
#define MAC1_USBPHY_SLB0_REG_inst_adr                                                "0x000E"
#define MAC1_USBPHY_SLB0_REG_inst                                                    0x000E
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_done_shift                                   (3)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_done_mask                                    (0x00000008)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_done(data)                                   (0x00000008&((data)<<3))
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_done_src(data)                               ((0x00000008&(data))>>3)
#define MAC1_USBPHY_SLB0_REG_get_usbphy_slb_done(data)                               ((0x00000008&(data))>>3)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_fail_shift                                   (2)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_fail_mask                                    (0x00000004)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_fail(data)                                   (0x00000004&((data)<<2))
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_fail_src(data)                               ((0x00000004&(data))>>2)
#define MAC1_USBPHY_SLB0_REG_get_usbphy_slb_fail(data)                               ((0x00000004&(data))>>2)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_hs_shift                                     (1)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_hs_mask                                      (0x00000002)
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_hs(data)                                     (0x00000002&((data)<<1))
#define MAC1_USBPHY_SLB0_REG_usbphy_slb_hs_src(data)                                 ((0x00000002&(data))>>1)
#define MAC1_USBPHY_SLB0_REG_get_usbphy_slb_hs(data)                                 ((0x00000002&(data))>>1)
#define MAC1_USBPHY_SLB0_REG_usbphy_force_slb_shift                                  (0)
#define MAC1_USBPHY_SLB0_REG_usbphy_force_slb_mask                                   (0x00000001)
#define MAC1_USBPHY_SLB0_REG_usbphy_force_slb(data)                                  (0x00000001&((data)<<0))
#define MAC1_USBPHY_SLB0_REG_usbphy_force_slb_src(data)                              ((0x00000001&(data))>>0)
#define MAC1_USBPHY_SLB0_REG_get_usbphy_force_slb(data)                              ((0x00000001&(data))>>0)


#define MAC1_USBPHY_SLB1_REG                                                         0x1801283c
#define MAC1_USBPHY_SLB1_REG_reg_addr                                                "0xB801283C"
#define MAC1_USBPHY_SLB1_REG_reg                                                     0xB801283C
#define set_MAC1_USBPHY_SLB1_REG_reg(data)   (*((volatile unsigned int*) MAC1_USBPHY_SLB1_REG_reg)=data)
#define get_MAC1_USBPHY_SLB1_REG_reg   (*((volatile unsigned int*) MAC1_USBPHY_SLB1_REG_reg))
#define MAC1_USBPHY_SLB1_REG_inst_adr                                                "0x000F"
#define MAC1_USBPHY_SLB1_REG_inst                                                    0x000F
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_done_shift                                   (3)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_done_mask                                    (0x00000008)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_done(data)                                   (0x00000008&((data)<<3))
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_done_src(data)                               ((0x00000008&(data))>>3)
#define MAC1_USBPHY_SLB1_REG_get_usbphy_slb_done(data)                               ((0x00000008&(data))>>3)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_fail_shift                                   (2)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_fail_mask                                    (0x00000004)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_fail(data)                                   (0x00000004&((data)<<2))
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_fail_src(data)                               ((0x00000004&(data))>>2)
#define MAC1_USBPHY_SLB1_REG_get_usbphy_slb_fail(data)                               ((0x00000004&(data))>>2)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_hs_shift                                     (1)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_hs_mask                                      (0x00000002)
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_hs(data)                                     (0x00000002&((data)<<1))
#define MAC1_USBPHY_SLB1_REG_usbphy_slb_hs_src(data)                                 ((0x00000002&(data))>>1)
#define MAC1_USBPHY_SLB1_REG_get_usbphy_slb_hs(data)                                 ((0x00000002&(data))>>1)
#define MAC1_USBPHY_SLB1_REG_usbphy_force_slb_shift                                  (0)
#define MAC1_USBPHY_SLB1_REG_usbphy_force_slb_mask                                   (0x00000001)
#define MAC1_USBPHY_SLB1_REG_usbphy_force_slb(data)                                  (0x00000001&((data)<<0))
#define MAC1_USBPHY_SLB1_REG_usbphy_force_slb_src(data)                              ((0x00000001&(data))>>0)
#define MAC1_USBPHY_SLB1_REG_get_usbphy_force_slb(data)                              ((0x00000001&(data))>>0)


#define MAC1_USB_OTG_REG                                                             0x18012840
#define MAC1_USB_OTG_REG_reg_addr                                                    "0xB8012840"
#define MAC1_USB_OTG_REG_reg                                                         0xB8012840
#define set_MAC1_USB_OTG_REG_reg(data)   (*((volatile unsigned int*) MAC1_USB_OTG_REG_reg)=data)
#define get_MAC1_USB_OTG_REG_reg   (*((volatile unsigned int*) MAC1_USB_OTG_REG_reg))
#define MAC1_USB_OTG_REG_inst_adr                                                    "0x0010"
#define MAC1_USB_OTG_REG_inst                                                        0x0010
#define MAC1_USB_OTG_REG_iopdcr_reserved_12_shift                                    (6)
#define MAC1_USB_OTG_REG_iopdcr_reserved_12_mask                                     (0x00000040)
#define MAC1_USB_OTG_REG_iopdcr_reserved_12(data)                                    (0x00000040&((data)<<6))
#define MAC1_USB_OTG_REG_iopdcr_reserved_12_src(data)                                ((0x00000040&(data))>>6)
#define MAC1_USB_OTG_REG_get_iopdcr_reserved_12(data)                                ((0x00000040&(data))>>6)
#define MAC1_USB_OTG_REG_ss_scaledown_mode_shift                                     (4)
#define MAC1_USB_OTG_REG_ss_scaledown_mode_mask                                      (0x00000030)
#define MAC1_USB_OTG_REG_ss_scaledown_mode(data)                                     (0x00000030&((data)<<4))
#define MAC1_USB_OTG_REG_ss_scaledown_mode_src(data)                                 ((0x00000030&(data))>>4)
#define MAC1_USB_OTG_REG_get_ss_scaledown_mode(data)                                 ((0x00000030&(data))>>4)
#define MAC1_USB_OTG_REG_m_hbigendian_shift                                          (3)
#define MAC1_USB_OTG_REG_m_hbigendian_mask                                           (0x00000008)
#define MAC1_USB_OTG_REG_m_hbigendian(data)                                          (0x00000008&((data)<<3))
#define MAC1_USB_OTG_REG_m_hbigendian_src(data)                                      ((0x00000008&(data))>>3)
#define MAC1_USB_OTG_REG_get_m_hbigendian(data)                                      ((0x00000008&(data))>>3)
#define MAC1_USB_OTG_REG_s_hbigendian_shift                                          (2)
#define MAC1_USB_OTG_REG_s_hbigendian_mask                                           (0x00000004)
#define MAC1_USB_OTG_REG_s_hbigendian(data)                                          (0x00000004&((data)<<2))
#define MAC1_USB_OTG_REG_s_hbigendian_src(data)                                      ((0x00000004&(data))>>2)
#define MAC1_USB_OTG_REG_get_s_hbigendian(data)                                      ((0x00000004&(data))>>2)
#define MAC1_USB_OTG_REG_from_frchs_shift                                            (1)
#define MAC1_USB_OTG_REG_from_frchs_mask                                             (0x00000002)
#define MAC1_USB_OTG_REG_from_frchs(data)                                            (0x00000002&((data)<<1))
#define MAC1_USB_OTG_REG_from_frchs_src(data)                                        ((0x00000002&(data))>>1)
#define MAC1_USB_OTG_REG_get_from_frchs(data)                                        ((0x00000002&(data))>>1)
#define MAC1_USB_OTG_REG_otg_enable_shift                                            (0)
#define MAC1_USB_OTG_REG_otg_enable_mask                                             (0x00000001)
#define MAC1_USB_OTG_REG_otg_enable(data)                                            (0x00000001&((data)<<0))
#define MAC1_USB_OTG_REG_otg_enable_src(data)                                        ((0x00000001&(data))>>0)
#define MAC1_USB_OTG_REG_get_otg_enable(data)                                        ((0x00000001&(data))>>0)


#define MAC1_USB_OTGMUX_REG                                                          0x18012844
#define MAC1_USB_OTGMUX_REG_reg_addr                                                 "0xB8012844"
#define MAC1_USB_OTGMUX_REG_reg                                                      0xB8012844
#define set_MAC1_USB_OTGMUX_REG_reg(data)   (*((volatile unsigned int*) MAC1_USB_OTGMUX_REG_reg)=data)
#define get_MAC1_USB_OTGMUX_REG_reg   (*((volatile unsigned int*) MAC1_USB_OTGMUX_REG_reg))
#define MAC1_USB_OTGMUX_REG_inst_adr                                                 "0x0011"
#define MAC1_USB_OTGMUX_REG_inst                                                     0x0011
#define MAC1_USB_OTGMUX_REG_data_value8_shift                                        (24)
#define MAC1_USB_OTGMUX_REG_data_value8_mask                                         (0x01000000)
#define MAC1_USB_OTGMUX_REG_data_value8(data)                                        (0x01000000&((data)<<24))
#define MAC1_USB_OTGMUX_REG_data_value8_src(data)                                    ((0x01000000&(data))>>24)
#define MAC1_USB_OTGMUX_REG_get_data_value8(data)                                    ((0x01000000&(data))>>24)
#define MAC1_USB_OTGMUX_REG_data_value7_shift                                        (23)
#define MAC1_USB_OTGMUX_REG_data_value7_mask                                         (0x00800000)
#define MAC1_USB_OTGMUX_REG_data_value7(data)                                        (0x00800000&((data)<<23))
#define MAC1_USB_OTGMUX_REG_data_value7_src(data)                                    ((0x00800000&(data))>>23)
#define MAC1_USB_OTGMUX_REG_get_data_value7(data)                                    ((0x00800000&(data))>>23)
#define MAC1_USB_OTGMUX_REG_data_value6_shift                                        (22)
#define MAC1_USB_OTGMUX_REG_data_value6_mask                                         (0x00400000)
#define MAC1_USB_OTGMUX_REG_data_value6(data)                                        (0x00400000&((data)<<22))
#define MAC1_USB_OTGMUX_REG_data_value6_src(data)                                    ((0x00400000&(data))>>22)
#define MAC1_USB_OTGMUX_REG_get_data_value6(data)                                    ((0x00400000&(data))>>22)
#define MAC1_USB_OTGMUX_REG_data_value5_shift                                        (21)
#define MAC1_USB_OTGMUX_REG_data_value5_mask                                         (0x00200000)
#define MAC1_USB_OTGMUX_REG_data_value5(data)                                        (0x00200000&((data)<<21))
#define MAC1_USB_OTGMUX_REG_data_value5_src(data)                                    ((0x00200000&(data))>>21)
#define MAC1_USB_OTGMUX_REG_get_data_value5(data)                                    ((0x00200000&(data))>>21)
#define MAC1_USB_OTGMUX_REG_data_value4_shift                                        (20)
#define MAC1_USB_OTGMUX_REG_data_value4_mask                                         (0x00100000)
#define MAC1_USB_OTGMUX_REG_data_value4(data)                                        (0x00100000&((data)<<20))
#define MAC1_USB_OTGMUX_REG_data_value4_src(data)                                    ((0x00100000&(data))>>20)
#define MAC1_USB_OTGMUX_REG_get_data_value4(data)                                    ((0x00100000&(data))>>20)
#define MAC1_USB_OTGMUX_REG_data_value3_shift                                        (19)
#define MAC1_USB_OTGMUX_REG_data_value3_mask                                         (0x00080000)
#define MAC1_USB_OTGMUX_REG_data_value3(data)                                        (0x00080000&((data)<<19))
#define MAC1_USB_OTGMUX_REG_data_value3_src(data)                                    ((0x00080000&(data))>>19)
#define MAC1_USB_OTGMUX_REG_get_data_value3(data)                                    ((0x00080000&(data))>>19)
#define MAC1_USB_OTGMUX_REG_data_value2_shift                                        (18)
#define MAC1_USB_OTGMUX_REG_data_value2_mask                                         (0x00040000)
#define MAC1_USB_OTGMUX_REG_data_value2(data)                                        (0x00040000&((data)<<18))
#define MAC1_USB_OTGMUX_REG_data_value2_src(data)                                    ((0x00040000&(data))>>18)
#define MAC1_USB_OTGMUX_REG_get_data_value2(data)                                    ((0x00040000&(data))>>18)
#define MAC1_USB_OTGMUX_REG_data_value1_shift                                        (17)
#define MAC1_USB_OTGMUX_REG_data_value1_mask                                         (0x00020000)
#define MAC1_USB_OTGMUX_REG_data_value1(data)                                        (0x00020000&((data)<<17))
#define MAC1_USB_OTGMUX_REG_data_value1_src(data)                                    ((0x00020000&(data))>>17)
#define MAC1_USB_OTGMUX_REG_get_data_value1(data)                                    ((0x00020000&(data))>>17)
#define MAC1_USB_OTGMUX_REG_data_value0_shift                                        (16)
#define MAC1_USB_OTGMUX_REG_data_value0_mask                                         (0x00010000)
#define MAC1_USB_OTGMUX_REG_data_value0(data)                                        (0x00010000&((data)<<16))
#define MAC1_USB_OTGMUX_REG_data_value0_src(data)                                    ((0x00010000&(data))>>16)
#define MAC1_USB_OTGMUX_REG_get_data_value0(data)                                    ((0x00010000&(data))>>16)
#define MAC1_USB_OTGMUX_REG_data_mux8_shift                                          (8)
#define MAC1_USB_OTGMUX_REG_data_mux8_mask                                           (0x00000100)
#define MAC1_USB_OTGMUX_REG_data_mux8(data)                                          (0x00000100&((data)<<8))
#define MAC1_USB_OTGMUX_REG_data_mux8_src(data)                                      ((0x00000100&(data))>>8)
#define MAC1_USB_OTGMUX_REG_get_data_mux8(data)                                      ((0x00000100&(data))>>8)
#define MAC1_USB_OTGMUX_REG_data_mux7_shift                                          (7)
#define MAC1_USB_OTGMUX_REG_data_mux7_mask                                           (0x00000080)
#define MAC1_USB_OTGMUX_REG_data_mux7(data)                                          (0x00000080&((data)<<7))
#define MAC1_USB_OTGMUX_REG_data_mux7_src(data)                                      ((0x00000080&(data))>>7)
#define MAC1_USB_OTGMUX_REG_get_data_mux7(data)                                      ((0x00000080&(data))>>7)
#define MAC1_USB_OTGMUX_REG_data_mux6_shift                                          (6)
#define MAC1_USB_OTGMUX_REG_data_mux6_mask                                           (0x00000040)
#define MAC1_USB_OTGMUX_REG_data_mux6(data)                                          (0x00000040&((data)<<6))
#define MAC1_USB_OTGMUX_REG_data_mux6_src(data)                                      ((0x00000040&(data))>>6)
#define MAC1_USB_OTGMUX_REG_get_data_mux6(data)                                      ((0x00000040&(data))>>6)
#define MAC1_USB_OTGMUX_REG_data_mux5_shift                                          (5)
#define MAC1_USB_OTGMUX_REG_data_mux5_mask                                           (0x00000020)
#define MAC1_USB_OTGMUX_REG_data_mux5(data)                                          (0x00000020&((data)<<5))
#define MAC1_USB_OTGMUX_REG_data_mux5_src(data)                                      ((0x00000020&(data))>>5)
#define MAC1_USB_OTGMUX_REG_get_data_mux5(data)                                      ((0x00000020&(data))>>5)
#define MAC1_USB_OTGMUX_REG_data_mux4_shift                                          (4)
#define MAC1_USB_OTGMUX_REG_data_mux4_mask                                           (0x00000010)
#define MAC1_USB_OTGMUX_REG_data_mux4(data)                                          (0x00000010&((data)<<4))
#define MAC1_USB_OTGMUX_REG_data_mux4_src(data)                                      ((0x00000010&(data))>>4)
#define MAC1_USB_OTGMUX_REG_get_data_mux4(data)                                      ((0x00000010&(data))>>4)
#define MAC1_USB_OTGMUX_REG_data_mux3_shift                                          (3)
#define MAC1_USB_OTGMUX_REG_data_mux3_mask                                           (0x00000008)
#define MAC1_USB_OTGMUX_REG_data_mux3(data)                                          (0x00000008&((data)<<3))
#define MAC1_USB_OTGMUX_REG_data_mux3_src(data)                                      ((0x00000008&(data))>>3)
#define MAC1_USB_OTGMUX_REG_get_data_mux3(data)                                      ((0x00000008&(data))>>3)
#define MAC1_USB_OTGMUX_REG_data_mux2_shift                                          (2)
#define MAC1_USB_OTGMUX_REG_data_mux2_mask                                           (0x00000004)
#define MAC1_USB_OTGMUX_REG_data_mux2(data)                                          (0x00000004&((data)<<2))
#define MAC1_USB_OTGMUX_REG_data_mux2_src(data)                                      ((0x00000004&(data))>>2)
#define MAC1_USB_OTGMUX_REG_get_data_mux2(data)                                      ((0x00000004&(data))>>2)
#define MAC1_USB_OTGMUX_REG_data_mux1_shift                                          (1)
#define MAC1_USB_OTGMUX_REG_data_mux1_mask                                           (0x00000002)
#define MAC1_USB_OTGMUX_REG_data_mux1(data)                                          (0x00000002&((data)<<1))
#define MAC1_USB_OTGMUX_REG_data_mux1_src(data)                                      ((0x00000002&(data))>>1)
#define MAC1_USB_OTGMUX_REG_get_data_mux1(data)                                      ((0x00000002&(data))>>1)
#define MAC1_USB_OTGMUX_REG_data_mux0_shift                                          (0)
#define MAC1_USB_OTGMUX_REG_data_mux0_mask                                           (0x00000001)
#define MAC1_USB_OTGMUX_REG_data_mux0(data)                                          (0x00000001&((data)<<0))
#define MAC1_USB_OTGMUX_REG_data_mux0_src(data)                                      ((0x00000001&(data))>>0)
#define MAC1_USB_OTGMUX_REG_get_data_mux0(data)                                      ((0x00000001&(data))>>0)


#define MAC1_USB_CTR0                                                                0x18012848
#define MAC1_USB_CTR0_reg_addr                                                       "0xB8012848"
#define MAC1_USB_CTR0_reg                                                            0xB8012848
#define set_MAC1_USB_CTR0_reg(data)   (*((volatile unsigned int*) MAC1_USB_CTR0_reg)=data)
#define get_MAC1_USB_CTR0_reg   (*((volatile unsigned int*) MAC1_USB_CTR0_reg))
#define MAC1_USB_CTR0_inst_adr                                                       "0x0012"
#define MAC1_USB_CTR0_inst                                                           0x0012
#define MAC1_USB_CTR0_reg3848_dummy_shift                                            (9)
#define MAC1_USB_CTR0_reg3848_dummy_mask                                             (0xFFFFFE00)
#define MAC1_USB_CTR0_reg3848_dummy(data)                                            (0xFFFFFE00&((data)<<9))
#define MAC1_USB_CTR0_reg3848_dummy_src(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC1_USB_CTR0_get_reg3848_dummy(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC1_USB_CTR0_prt_pwren_reg_ds_shift                                         (7)
#define MAC1_USB_CTR0_prt_pwren_reg_ds_mask                                          (0x00000180)
#define MAC1_USB_CTR0_prt_pwren_reg_ds(data)                                         (0x00000180&((data)<<7))
#define MAC1_USB_CTR0_prt_pwren_reg_ds_src(data)                                     ((0x00000180&(data))>>7)
#define MAC1_USB_CTR0_get_prt_pwren_reg_ds(data)                                     ((0x00000180&(data))>>7)
#define MAC1_USB_CTR0_prt_pwren_ctrl_shift                                           (5)
#define MAC1_USB_CTR0_prt_pwren_ctrl_mask                                            (0x00000060)
#define MAC1_USB_CTR0_prt_pwren_ctrl(data)                                           (0x00000060&((data)<<5))
#define MAC1_USB_CTR0_prt_pwren_ctrl_src(data)                                       ((0x00000060&(data))>>5)
#define MAC1_USB_CTR0_get_prt_pwren_ctrl(data)                                       ((0x00000060&(data))>>5)
#define MAC1_USB_CTR0_prt_ovrcur_reg_ds_shift                                        (3)
#define MAC1_USB_CTR0_prt_ovrcur_reg_ds_mask                                         (0x00000018)
#define MAC1_USB_CTR0_prt_ovrcur_reg_ds(data)                                        (0x00000018&((data)<<3))
#define MAC1_USB_CTR0_prt_ovrcur_reg_ds_src(data)                                    ((0x00000018&(data))>>3)
#define MAC1_USB_CTR0_get_prt_ovrcur_reg_ds(data)                                    ((0x00000018&(data))>>3)
#define MAC1_USB_CTR0_prt_ovrcur_ctrl_shift                                          (1)
#define MAC1_USB_CTR0_prt_ovrcur_ctrl_mask                                           (0x00000006)
#define MAC1_USB_CTR0_prt_ovrcur_ctrl(data)                                          (0x00000006&((data)<<1))
#define MAC1_USB_CTR0_prt_ovrcur_ctrl_src(data)                                      ((0x00000006&(data))>>1)
#define MAC1_USB_CTR0_get_prt_ovrcur_ctrl(data)                                      ((0x00000006&(data))>>1)
#define MAC1_USB_CTR0_usb_dbg_ctrl_shift                                             (0)
#define MAC1_USB_CTR0_usb_dbg_ctrl_mask                                              (0x00000001)
#define MAC1_USB_CTR0_usb_dbg_ctrl(data)                                             (0x00000001&((data)<<0))
#define MAC1_USB_CTR0_usb_dbg_ctrl_src(data)                                         ((0x00000001&(data))>>0)
#define MAC1_USB_CTR0_get_usb_dbg_ctrl(data)                                         ((0x00000001&(data))>>0)


#define MAC1_USB_CTR1                                                                0x1801284c
#define MAC1_USB_CTR1_reg_addr                                                       "0xB801284C"
#define MAC1_USB_CTR1_reg                                                            0xB801284C
#define set_MAC1_USB_CTR1_reg(data)   (*((volatile unsigned int*) MAC1_USB_CTR1_reg)=data)
#define get_MAC1_USB_CTR1_reg   (*((volatile unsigned int*) MAC1_USB_CTR1_reg))
#define MAC1_USB_CTR1_inst_adr                                                       "0x0013"
#define MAC1_USB_CTR1_inst                                                           0x0013
#define MAC1_USB_CTR1_Reg384c_dummy_shift                                            (9)
#define MAC1_USB_CTR1_Reg384c_dummy_mask                                             (0xFFFFFE00)
#define MAC1_USB_CTR1_Reg384c_dummy(data)                                            (0xFFFFFE00&((data)<<9))
#define MAC1_USB_CTR1_Reg384c_dummy_src(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC1_USB_CTR1_get_Reg384c_dummy(data)                                        ((0xFFFFFE00&(data))>>9)
#define MAC1_USB_CTR1_eco_option0_dis_shift                                          (8)
#define MAC1_USB_CTR1_eco_option0_dis_mask                                           (0x00000100)
#define MAC1_USB_CTR1_eco_option0_dis(data)                                          (0x00000100&((data)<<8))
#define MAC1_USB_CTR1_eco_option0_dis_src(data)                                      ((0x00000100&(data))>>8)
#define MAC1_USB_CTR1_get_eco_option0_dis(data)                                      ((0x00000100&(data))>>8)
#define MAC1_USB_CTR1_Reg384c_dummy_7_shift                                          (7)
#define MAC1_USB_CTR1_Reg384c_dummy_7_mask                                           (0x00000080)
#define MAC1_USB_CTR1_Reg384c_dummy_7(data)                                          (0x00000080&((data)<<7))
#define MAC1_USB_CTR1_Reg384c_dummy_7_src(data)                                      ((0x00000080&(data))>>7)
#define MAC1_USB_CTR1_get_Reg384c_dummy_7(data)                                      ((0x00000080&(data))>>7)
#define MAC1_USB_CTR1_usb_top_dbg_ctrl_shift                                         (4)
#define MAC1_USB_CTR1_usb_top_dbg_ctrl_mask                                          (0x00000070)
#define MAC1_USB_CTR1_usb_top_dbg_ctrl(data)                                         (0x00000070&((data)<<4))
#define MAC1_USB_CTR1_usb_top_dbg_ctrl_src(data)                                     ((0x00000070&(data))>>4)
#define MAC1_USB_CTR1_get_usb_top_dbg_ctrl(data)                                     ((0x00000070&(data))>>4)
#define MAC1_USB_CTR1_cmd_full_number_shift                                          (2)
#define MAC1_USB_CTR1_cmd_full_number_mask                                           (0x0000000C)
#define MAC1_USB_CTR1_cmd_full_number(data)                                          (0x0000000C&((data)<<2))
#define MAC1_USB_CTR1_cmd_full_number_src(data)                                      ((0x0000000C&(data))>>2)
#define MAC1_USB_CTR1_get_cmd_full_number(data)                                      ((0x0000000C&(data))>>2)
#define MAC1_USB_CTR1_dbus_arb_priority_shift                                        (1)
#define MAC1_USB_CTR1_dbus_arb_priority_mask                                         (0x00000002)
#define MAC1_USB_CTR1_dbus_arb_priority(data)                                        (0x00000002&((data)<<1))
#define MAC1_USB_CTR1_dbus_arb_priority_src(data)                                    ((0x00000002&(data))>>1)
#define MAC1_USB_CTR1_get_dbus_arb_priority(data)                                    ((0x00000002&(data))>>1)
#define MAC1_USB_CTR1_dbus_robin_enable_shift                                        (0)
#define MAC1_USB_CTR1_dbus_robin_enable_mask                                         (0x00000001)
#define MAC1_USB_CTR1_dbus_robin_enable(data)                                        (0x00000001&((data)<<0))
#define MAC1_USB_CTR1_dbus_robin_enable_src(data)                                    ((0x00000001&(data))>>0)
#define MAC1_USB_CTR1_get_dbus_robin_enable(data)                                    ((0x00000001&(data))>>0)


#define MAC1_USB_BIST0                                                               0x18012900
#define MAC1_USB_BIST0_reg_addr                                                      "0xB8012900"
#define MAC1_USB_BIST0_reg                                                           0xB8012900
#define set_MAC1_USB_BIST0_reg(data)   (*((volatile unsigned int*) MAC1_USB_BIST0_reg)=data)
#define get_MAC1_USB_BIST0_reg   (*((volatile unsigned int*) MAC1_USB_BIST0_reg))
#define MAC1_USB_BIST0_inst_adr                                                      "0x0040"
#define MAC1_USB_BIST0_inst                                                          0x0040
#define MAC1_USB_BIST0_usb_bist_mode_host_ram_shift                                  (1)
#define MAC1_USB_BIST0_usb_bist_mode_host_ram_mask                                   (0x00000002)
#define MAC1_USB_BIST0_usb_bist_mode_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC1_USB_BIST0_usb_bist_mode_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_BIST0_get_usb_bist_mode_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_BIST0_usb_bist_mode_wrap_shift                                      (0)
#define MAC1_USB_BIST0_usb_bist_mode_wrap_mask                                       (0x00000001)
#define MAC1_USB_BIST0_usb_bist_mode_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC1_USB_BIST0_usb_bist_mode_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC1_USB_BIST0_get_usb_bist_mode_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC1_USB_BIST1                                                               0x18012904
#define MAC1_USB_BIST1_reg_addr                                                      "0xB8012904"
#define MAC1_USB_BIST1_reg                                                           0xB8012904
#define set_MAC1_USB_BIST1_reg(data)   (*((volatile unsigned int*) MAC1_USB_BIST1_reg)=data)
#define get_MAC1_USB_BIST1_reg   (*((volatile unsigned int*) MAC1_USB_BIST1_reg))
#define MAC1_USB_BIST1_inst_adr                                                      "0x0041"
#define MAC1_USB_BIST1_inst                                                          0x0041
#define MAC1_USB_BIST1_usb_bist_done_host_ram_shift                                  (1)
#define MAC1_USB_BIST1_usb_bist_done_host_ram_mask                                   (0x00000002)
#define MAC1_USB_BIST1_usb_bist_done_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC1_USB_BIST1_usb_bist_done_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_BIST1_get_usb_bist_done_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_BIST1_usb_bist_done_wrap_shift                                      (0)
#define MAC1_USB_BIST1_usb_bist_done_wrap_mask                                       (0x00000001)
#define MAC1_USB_BIST1_usb_bist_done_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC1_USB_BIST1_usb_bist_done_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC1_USB_BIST1_get_usb_bist_done_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC1_USB_BIST2                                                               0x18012908
#define MAC1_USB_BIST2_reg_addr                                                      "0xB8012908"
#define MAC1_USB_BIST2_reg                                                           0xB8012908
#define set_MAC1_USB_BIST2_reg(data)   (*((volatile unsigned int*) MAC1_USB_BIST2_reg)=data)
#define get_MAC1_USB_BIST2_reg   (*((volatile unsigned int*) MAC1_USB_BIST2_reg))
#define MAC1_USB_BIST2_inst_adr                                                      "0x0042"
#define MAC1_USB_BIST2_inst                                                          0x0042
#define MAC1_USB_BIST2_usb_bist_fail_host_ram_shift                                  (1)
#define MAC1_USB_BIST2_usb_bist_fail_host_ram_mask                                   (0x00000002)
#define MAC1_USB_BIST2_usb_bist_fail_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC1_USB_BIST2_usb_bist_fail_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_BIST2_get_usb_bist_fail_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_BIST2_usb_bist_fail_wrap_shift                                      (0)
#define MAC1_USB_BIST2_usb_bist_fail_wrap_mask                                       (0x00000001)
#define MAC1_USB_BIST2_usb_bist_fail_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC1_USB_BIST2_usb_bist_fail_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC1_USB_BIST2_get_usb_bist_fail_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC1_USB_DRF0                                                                0x18012918
#define MAC1_USB_DRF0_reg_addr                                                       "0xB8012918"
#define MAC1_USB_DRF0_reg                                                            0xB8012918
#define set_MAC1_USB_DRF0_reg(data)   (*((volatile unsigned int*) MAC1_USB_DRF0_reg)=data)
#define get_MAC1_USB_DRF0_reg   (*((volatile unsigned int*) MAC1_USB_DRF0_reg))
#define MAC1_USB_DRF0_inst_adr                                                       "0x0046"
#define MAC1_USB_DRF0_inst                                                           0x0046
#define MAC1_USB_DRF0_usb_drf_mode_host_ram_shift                                    (1)
#define MAC1_USB_DRF0_usb_drf_mode_host_ram_mask                                     (0x00000002)
#define MAC1_USB_DRF0_usb_drf_mode_host_ram(data)                                    (0x00000002&((data)<<1))
#define MAC1_USB_DRF0_usb_drf_mode_host_ram_src(data)                                ((0x00000002&(data))>>1)
#define MAC1_USB_DRF0_get_usb_drf_mode_host_ram(data)                                ((0x00000002&(data))>>1)
#define MAC1_USB_DRF0_usb_drf_mode_wrap_shift                                        (0)
#define MAC1_USB_DRF0_usb_drf_mode_wrap_mask                                         (0x00000001)
#define MAC1_USB_DRF0_usb_drf_mode_wrap(data)                                        (0x00000001&((data)<<0))
#define MAC1_USB_DRF0_usb_drf_mode_wrap_src(data)                                    ((0x00000001&(data))>>0)
#define MAC1_USB_DRF0_get_usb_drf_mode_wrap(data)                                    ((0x00000001&(data))>>0)


#define MAC1_USB_DRF1                                                                0x1801291c
#define MAC1_USB_DRF1_reg_addr                                                       "0xB801291C"
#define MAC1_USB_DRF1_reg                                                            0xB801291C
#define set_MAC1_USB_DRF1_reg(data)   (*((volatile unsigned int*) MAC1_USB_DRF1_reg)=data)
#define get_MAC1_USB_DRF1_reg   (*((volatile unsigned int*) MAC1_USB_DRF1_reg))
#define MAC1_USB_DRF1_inst_adr                                                       "0x0047"
#define MAC1_USB_DRF1_inst                                                           0x0047
#define MAC1_USB_DRF1_usb_drf_resume_host_ram_shift                                  (1)
#define MAC1_USB_DRF1_usb_drf_resume_host_ram_mask                                   (0x00000002)
#define MAC1_USB_DRF1_usb_drf_resume_host_ram(data)                                  (0x00000002&((data)<<1))
#define MAC1_USB_DRF1_usb_drf_resume_host_ram_src(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_DRF1_get_usb_drf_resume_host_ram(data)                              ((0x00000002&(data))>>1)
#define MAC1_USB_DRF1_usb_drf_resume_wrap_shift                                      (0)
#define MAC1_USB_DRF1_usb_drf_resume_wrap_mask                                       (0x00000001)
#define MAC1_USB_DRF1_usb_drf_resume_wrap(data)                                      (0x00000001&((data)<<0))
#define MAC1_USB_DRF1_usb_drf_resume_wrap_src(data)                                  ((0x00000001&(data))>>0)
#define MAC1_USB_DRF1_get_usb_drf_resume_wrap(data)                                  ((0x00000001&(data))>>0)


#define MAC1_USB_DRF2                                                                0x18012920
#define MAC1_USB_DRF2_reg_addr                                                       "0xB8012920"
#define MAC1_USB_DRF2_reg                                                            0xB8012920
#define set_MAC1_USB_DRF2_reg(data)   (*((volatile unsigned int*) MAC1_USB_DRF2_reg)=data)
#define get_MAC1_USB_DRF2_reg   (*((volatile unsigned int*) MAC1_USB_DRF2_reg))
#define MAC1_USB_DRF2_inst_adr                                                       "0x0048"
#define MAC1_USB_DRF2_inst                                                           0x0048
#define MAC1_USB_DRF2_usb_drf_done_host_ram_shift                                    (1)
#define MAC1_USB_DRF2_usb_drf_done_host_ram_mask                                     (0x00000002)
#define MAC1_USB_DRF2_usb_drf_done_host_ram(data)                                    (0x00000002&((data)<<1))
#define MAC1_USB_DRF2_usb_drf_done_host_ram_src(data)                                ((0x00000002&(data))>>1)
#define MAC1_USB_DRF2_get_usb_drf_done_host_ram(data)                                ((0x00000002&(data))>>1)
#define MAC1_USB_DRF2_usb_drf_done_wrap_shift                                        (0)
#define MAC1_USB_DRF2_usb_drf_done_wrap_mask                                         (0x00000001)
#define MAC1_USB_DRF2_usb_drf_done_wrap(data)                                        (0x00000001&((data)<<0))
#define MAC1_USB_DRF2_usb_drf_done_wrap_src(data)                                    ((0x00000001&(data))>>0)
#define MAC1_USB_DRF2_get_usb_drf_done_wrap(data)                                    ((0x00000001&(data))>>0)


#define MAC1_USB_DRF3                                                                0x18012924
#define MAC1_USB_DRF3_reg_addr                                                       "0xB8012924"
#define MAC1_USB_DRF3_reg                                                            0xB8012924
#define set_MAC1_USB_DRF3_reg(data)   (*((volatile unsigned int*) MAC1_USB_DRF3_reg)=data)
#define get_MAC1_USB_DRF3_reg   (*((volatile unsigned int*) MAC1_USB_DRF3_reg))
#define MAC1_USB_DRF3_inst_adr                                                       "0x0049"
#define MAC1_USB_DRF3_inst                                                           0x0049
#define MAC1_USB_DRF3_usb_drf_pause_host_ram_shift                                   (1)
#define MAC1_USB_DRF3_usb_drf_pause_host_ram_mask                                    (0x00000002)
#define MAC1_USB_DRF3_usb_drf_pause_host_ram(data)                                   (0x00000002&((data)<<1))
#define MAC1_USB_DRF3_usb_drf_pause_host_ram_src(data)                               ((0x00000002&(data))>>1)
#define MAC1_USB_DRF3_get_usb_drf_pause_host_ram(data)                               ((0x00000002&(data))>>1)
#define MAC1_USB_DRF3_usb_drf_pause_wrap_shift                                       (0)
#define MAC1_USB_DRF3_usb_drf_pause_wrap_mask                                        (0x00000001)
#define MAC1_USB_DRF3_usb_drf_pause_wrap(data)                                       (0x00000001&((data)<<0))
#define MAC1_USB_DRF3_usb_drf_pause_wrap_src(data)                                   ((0x00000001&(data))>>0)
#define MAC1_USB_DRF3_get_usb_drf_pause_wrap(data)                                   ((0x00000001&(data))>>0)


#define MAC1_USB_DRF4                                                                0x18012928
#define MAC1_USB_DRF4_reg_addr                                                       "0xB8012928"
#define MAC1_USB_DRF4_reg                                                            0xB8012928
#define set_MAC1_USB_DRF4_reg(data)   (*((volatile unsigned int*) MAC1_USB_DRF4_reg)=data)
#define get_MAC1_USB_DRF4_reg   (*((volatile unsigned int*) MAC1_USB_DRF4_reg))
#define MAC1_USB_DRF4_inst_adr                                                       "0x004A"
#define MAC1_USB_DRF4_inst                                                           0x004A
#define MAC1_USB_DRF4_usb_drf_fail_host_ram_shift                                    (1)
#define MAC1_USB_DRF4_usb_drf_fail_host_ram_mask                                     (0x00000002)
#define MAC1_USB_DRF4_usb_drf_fail_host_ram(data)                                    (0x00000002&((data)<<1))
#define MAC1_USB_DRF4_usb_drf_fail_host_ram_src(data)                                ((0x00000002&(data))>>1)
#define MAC1_USB_DRF4_get_usb_drf_fail_host_ram(data)                                ((0x00000002&(data))>>1)
#define MAC1_USB_DRF4_usb_drf_fail_wrap_shift                                        (0)
#define MAC1_USB_DRF4_usb_drf_fail_wrap_mask                                         (0x00000001)
#define MAC1_USB_DRF4_usb_drf_fail_wrap(data)                                        (0x00000001&((data)<<0))
#define MAC1_USB_DRF4_usb_drf_fail_wrap_src(data)                                    ((0x00000001&(data))>>0)
#define MAC1_USB_DRF4_get_usb_drf_fail_wrap(data)                                    ((0x00000001&(data))>>0)


#define MAC1_USB_BIST_OPTION0                                                        0x18012938
#define MAC1_USB_BIST_OPTION0_reg_addr                                               "0xB8012938"
#define MAC1_USB_BIST_OPTION0_reg                                                    0xB8012938
#define set_MAC1_USB_BIST_OPTION0_reg(data)   (*((volatile unsigned int*) MAC1_USB_BIST_OPTION0_reg)=data)
#define get_MAC1_USB_BIST_OPTION0_reg   (*((volatile unsigned int*) MAC1_USB_BIST_OPTION0_reg))
#define MAC1_USB_BIST_OPTION0_inst_adr                                               "0x004E"
#define MAC1_USB_BIST_OPTION0_inst                                                   0x004E
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_ls0_shift                                (5)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_ls0_mask                                 (0x00000020)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_ls0(data)                                (0x00000020&((data)<<5))
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_ls0_src(data)                            ((0x00000020&(data))>>5)
#define MAC1_USB_BIST_OPTION0_get_usb_bist_wrap_ls0(data)                            ((0x00000020&(data))>>5)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rme0_shift                               (4)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rme0_mask                                (0x00000010)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rme0(data)                               (0x00000010&((data)<<4))
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rme0_src(data)                           ((0x00000010&(data))>>4)
#define MAC1_USB_BIST_OPTION0_get_usb_bist_wrap_rme0(data)                           ((0x00000010&(data))>>4)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rm0_shift                                (0)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rm0_mask                                 (0x0000000F)
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rm0(data)                                (0x0000000F&((data)<<0))
#define MAC1_USB_BIST_OPTION0_usb_bist_wrap_rm0_src(data)                            ((0x0000000F&(data))>>0)
#define MAC1_USB_BIST_OPTION0_get_usb_bist_wrap_rm0(data)                            ((0x0000000F&(data))>>0)


#define MAC1_USB_BIST_OPTION1                                                        0x1801293c
#define MAC1_USB_BIST_OPTION1_reg_addr                                               "0xB801293C"
#define MAC1_USB_BIST_OPTION1_reg                                                    0xB801293C
#define set_MAC1_USB_BIST_OPTION1_reg(data)   (*((volatile unsigned int*) MAC1_USB_BIST_OPTION1_reg)=data)
#define get_MAC1_USB_BIST_OPTION1_reg   (*((volatile unsigned int*) MAC1_USB_BIST_OPTION1_reg))
#define MAC1_USB_BIST_OPTION1_inst_adr                                               "0x004F"
#define MAC1_USB_BIST_OPTION1_inst                                                   0x004F
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_ls0_shift                             (5)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_ls0_mask                              (0x00000020)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_ls0(data)                             (0x00000020&((data)<<5))
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_ls0_src(data)                         ((0x00000020&(data))>>5)
#define MAC1_USB_BIST_OPTION1_get_usb_usb_host_ram_ls0(data)                         ((0x00000020&(data))>>5)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rme0_shift                            (4)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rme0_mask                             (0x00000010)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rme0(data)                            (0x00000010&((data)<<4))
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rme0_src(data)                        ((0x00000010&(data))>>4)
#define MAC1_USB_BIST_OPTION1_get_usb_usb_host_ram_rme0(data)                        ((0x00000010&(data))>>4)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rm0_shift                             (0)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rm0_mask                              (0x0000000F)
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rm0(data)                             (0x0000000F&((data)<<0))
#define MAC1_USB_BIST_OPTION1_usb_usb_host_ram_rm0_src(data)                         ((0x0000000F&(data))>>0)
#define MAC1_USB_BIST_OPTION1_get_usb_usb_host_ram_rm0(data)                         ((0x0000000F&(data))>>0)


#endif
