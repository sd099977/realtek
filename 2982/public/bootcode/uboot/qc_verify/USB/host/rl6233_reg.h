
#ifndef _RL6233_REG_H_
#define _RL6233_REG_H_

//#define TVE_SLEW_CTTL_get_p_slewrate(data)                            ((0x00000600&(data))>>9)
#define USBPHY_NUM                           0x02

#define USBPHY_20                            0xC0   //E0
#define USBPHY_21                            0xC1
#define USBPHY_22                            0xC2
#define USBPHY_23                            0xC3
#define USBPHY_24                            0xC4
#define USBPHY_25                            0xC5
#define USBPHY_26                            0xC6
#define USBPHY_28                            0xD0  //F0
#define USBPHY_29                            0xD1  //F1

#define USBPHY_30                            0xE0


#define USBPHY_30_set_z0_autok(data)       (0x80&((data)<<7))
#define USBPHY_30_set_z0_adjr(data)          (0x78&((data)<<3))
#define USBPHY_30_set_z0_en(data)          (0x04&((data)<<2))
#define USBPHY_30_set_z0_IBX_BOOSTER(data)          (0x03&(data))

#define USBPHY_31                            0xE1
#define USBPHY_31_set_pll_cp(data)   (0xe0&((data)<<5))
#define USBPHY_31_set_pll_pllsd(data)   (0x18&((data)<<3))
#define USBPHY_31_set_pll_pllsr(data)       (0x07&((data)))


#define USBPHY_32                            0xE2
#define USBPHY_32_set_pll_pllsc(data)              
#define USBPHY_32_set_pll_prediv(data)              


#define USBPHY_33                            0xE3
#define USBPHY_33_set_pll_div(data)      
#define USBPHY_33_set_pll_lb_booster(data)         


#define USBPHY_34                            0xE4
#define USBPHY_34_set_debug_TEST_EN(data)          
#define USBPHY_34_set_debug_ts(data)           
#define USBPHY_34_set_debug_rpu(data)          
#define USBPHY_34_set_debug_rpd(data)        

#define USBPHY_35                            0xE5
#define USBPHY_35_set_lf_txrx_lvl(data)           (0x80&((data)<<7))
#define USBPHY_35_set_lf_txrx_lf_src(data)          (0x60&((data)<<5))
#define USBPHY_35_set_hs_tx_src(data)         (0x16&((data)<<2))
#define USBPHY_35_set_hs_tx_ref_sel(data)         (0x02&((data)<<1))
#define USBPHY_35_set_hs_tx_hs_cksel(data)      (0x01&(data))

#define USBPHY_36                            0xE6
#define USBPHY_36_set_hs_tx_sh(data)        (0xF0&((data)<<4))
#define USBPHY_36_set_hs_tx_hsxmtpden(data)        (0x08&(data)<<3)
#define USBPHY_36_set_hs_rx_boost(data)        (0x06&(data)<<1)
#define USBPHY_36_set_hs_rx_cal(data)        (0x01&(data))

#define USBPHY_37                            0xE7
#define USBPHY_37_set_hs_rx_sen_hst(data)  (0xF0&((data)<<4))
#define USBPHY_37_set_hs_rx_sen(data)  (0x0F&((data)))

#define USBPHY_38                            0xF0



#define USBPHY_39				   0xF1
#define USBPHY_39_set_utmi_pos_out(data)  (0x80&((data)<<7))
#define USBPHY_39_set_slb_rst(data)	(0x40&((data)<<6))
#define USBPHY_39_set_slb_sel(data)	(0x30&((data)<<4))
#define USBPHY_39_set_slb_auto_sel(data)	(0x08&((data)<<3))
#define USBPHY_39_set_slb_tx_delay(data)	(0x06&((data)<<1))
#define USBPHY_39_set_slb_slb_fs(data)	(0x01&((data)))


#endif


