/**************************************************************
// Spec Version                  : 0.0.4
// Parser Version                : DVR_Parser_6.11(120105)
// CModelGen Version             : 5.1 2012.01.05
// Naming Rule                   :  Module_Register_Name
// Naming Rule                   : Module_Register_Name
// Parse Option                  : Only Parse _op1
// Parse Address Region          : All Address Region 
// Decode bit number             : 12 bits
// Firmware Header Generate Date : 2012/3/15 22:44:57
***************************************************************/


#ifndef _ISO_REG_H_INCLUDED_
#define _ISO_REG_H_INCLUDED_
#ifdef  _ISO_USE_STRUCT
typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     cec_int:1;
unsigned int     reserved_1:1;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     vfd_ardswda_int:1;
unsigned int     vfd_ardswa_int:1;
unsigned int     vfd_ardkpadda_int:1;
unsigned int     vfd_ardkpada_int:1;
unsigned int     vfd_wdone_int:1;
unsigned int     rtc_alarm_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     reserved_2:5;
unsigned int     ur1_to_int:1;
unsigned int     irda_int:1;
unsigned int     ur2_int:1;
unsigned int     ur1_int:1;
unsigned int     ur0_int:1;
unsigned int     tc3_int:1;
unsigned int     write_data:1;
}ISO_ISR;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     gpioda_int:1;
unsigned int     gpioa_int:1;
unsigned int     vfd_ardswda_int:1;
unsigned int     vfd_ardswa_int:1;
unsigned int     vfd_ardkpadda_int:1;
unsigned int     vfd_ardkpada_int:1;
unsigned int     vfd_wdone_int:1;
unsigned int     rtc_alarm_int:1;
unsigned int     rtc_hsec_int:1;
unsigned int     reserved_1:5;
unsigned int     ur1_to_int:1;
unsigned int     irda_int:1;
unsigned int     reserved_2:3;
unsigned int     tc3_int:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     int19_a:1;
unsigned int     int18_a:1;
unsigned int     int17_a:1;
unsigned int     int16_a:1;
unsigned int     int15_a:1;
unsigned int     int14_a:1;
unsigned int     int13_a:1;
unsigned int     int12_a:1;
unsigned int     int11_a:1;
unsigned int     int10_a:1;
unsigned int     int9_a:1;
unsigned int     int8_a:1;
unsigned int     int7_a:1;
unsigned int     int6_a:1;
unsigned int     int5_a:1;
unsigned int     int4_a:1;
unsigned int     int3_a:1;
unsigned int     int2_a:1;
unsigned int     int1_a:1;
unsigned int     int0_a:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPA;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     int19_da:1;
unsigned int     int18_da:1;
unsigned int     int17_da:1;
unsigned int     int16_da:1;
unsigned int     int15_da:1;
unsigned int     int14_da:1;
unsigned int     int13_da:1;
unsigned int     int12_da:1;
unsigned int     int11_da:1;
unsigned int     int10_da:1;
unsigned int     int9_da:1;
unsigned int     int8_da:1;
unsigned int     int7_da:1;
unsigned int     int6_da:1;
unsigned int     int5_da:1;
unsigned int     int4_da:1;
unsigned int     int3_da:1;
unsigned int     int2_da:1;
unsigned int     int1_da:1;
unsigned int     int0_da:1;
unsigned int     write_data:1;
}ISO_UMSK_ISR_GPDA;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     int47:1;
unsigned int     int46:1;
unsigned int     int45:1;
unsigned int     int44:1;
unsigned int     int43:1;
unsigned int     int42:1;
unsigned int     int41:1;
unsigned int     int40:1;
unsigned int     int39:1;
unsigned int     int38:1;
unsigned int     int37:1;
unsigned int     int36:1;
unsigned int     int35:1;
unsigned int     int34:1;
unsigned int     int33:1;
unsigned int     int32:1;
unsigned int     int31:1;
unsigned int     int30:1;
unsigned int     int29:1;
unsigned int     int28:1;
unsigned int     reserved_1:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADAH;

typedef struct 
{
unsigned int     int27:1;
unsigned int     int26:1;
unsigned int     int25:1;
unsigned int     int24:1;
unsigned int     int23:1;
unsigned int     int22:1;
unsigned int     int21:1;
unsigned int     int20:1;
unsigned int     int19:1;
unsigned int     int18:1;
unsigned int     int17:1;
unsigned int     int16:1;
unsigned int     int15:1;
unsigned int     int14:1;
unsigned int     int13:1;
unsigned int     int12:1;
unsigned int     int11:1;
unsigned int     int10:1;
unsigned int     int9:1;
unsigned int     int8:1;
unsigned int     int7:1;
unsigned int     int6:1;
unsigned int     int5:1;
unsigned int     int4:1;
unsigned int     int3:1;
unsigned int     int2:1;
unsigned int     int1:1;
unsigned int     int0:1;
unsigned int     reserved_0:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADAL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     int47:1;
unsigned int     int46:1;
unsigned int     int45:1;
unsigned int     int44:1;
unsigned int     int43:1;
unsigned int     int42:1;
unsigned int     int41:1;
unsigned int     int40:1;
unsigned int     int39:1;
unsigned int     int38:1;
unsigned int     int37:1;
unsigned int     int36:1;
unsigned int     int35:1;
unsigned int     int34:1;
unsigned int     int33:1;
unsigned int     int32:1;
unsigned int     int31:1;
unsigned int     int30:1;
unsigned int     int29:1;
unsigned int     int28:1;
unsigned int     reserved_1:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADDAH;

typedef struct 
{
unsigned int     int27:1;
unsigned int     int26:1;
unsigned int     int25:1;
unsigned int     int24:1;
unsigned int     int23:1;
unsigned int     int22:1;
unsigned int     int21:1;
unsigned int     int20:1;
unsigned int     int19:1;
unsigned int     int18:1;
unsigned int     int17:1;
unsigned int     int16:1;
unsigned int     int15:1;
unsigned int     int14:1;
unsigned int     int13:1;
unsigned int     int12:1;
unsigned int     int11:1;
unsigned int     int10:1;
unsigned int     int9:1;
unsigned int     int8:1;
unsigned int     int7:1;
unsigned int     int6:1;
unsigned int     int5:1;
unsigned int     int4:1;
unsigned int     int3:1;
unsigned int     int2:1;
unsigned int     int1:1;
unsigned int     int0:1;
unsigned int     reserved_0:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_KPADDAL;

typedef struct 
{
unsigned int     reserved_0:20;
unsigned int     da_int3:1;
unsigned int     da_int2:1;
unsigned int     da_int1:1;
unsigned int     da_int0:1;
unsigned int     a_int3:1;
unsigned int     a_int2:1;
unsigned int     a_int1:1;
unsigned int     a_int0:1;
unsigned int     reserved_1:3;
unsigned int     write_data:1;
}ISO_UMSK_ISR_SW;

typedef struct 
{
unsigned int     write_en5:1;
unsigned int     reserved_0:2;
unsigned int     standby_dbg_sel:5;
unsigned int     write_en4:1;
unsigned int     reserved_1:2;
unsigned int     standby_dbg_en:1;
unsigned int     write_en3:1;
unsigned int     reserved_2:3;
unsigned int     sel1:4;
unsigned int     write_en2:1;
unsigned int     reserved_3:3;
unsigned int     sel0:4;
unsigned int     write_en1:1;
unsigned int     reserved_4:2;
unsigned int     enable:1;
}ISO_DBG;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     testmode:1;
unsigned int     nf_sel:1;
unsigned int     bound_opt:11;
}ISO_CHIP_INFO1;

typedef struct 
{
unsigned int     reserved_0:13;
unsigned int     pow_latch:19;
}ISO_CHIP_INFO2;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     A_RTCSEC:7;
}A_RTCSEC;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     A_RTCMIN:6;
}A_RTCMIN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     A_RTCHR:5;
}A_RTCHR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     A_RTCDATE1:8;
}A_RTCDATE1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     A_RTCDATE2:7;
}A_RTCDATE2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     A_ALMMIN:6;
}A_ALMMIN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     A_ALMHR:5;
}A_ALMHR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     A_ALMDATE1:8;
}A_ALMDATE1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     A_ALMDATE2:7;
}A_ALMDATE2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     27Mclk_en:1;
unsigned int     VREF:2;
unsigned int     A_RTCSTOP:1;
}A_RTCSTOP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     A_RTCPWR:1;
unsigned int     CO:2;
unsigned int     CI:2;
unsigned int     CLKSEL:1;
unsigned int     BC:2;
}A_RTCACR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     A_RTCEN:8;
}A_RTCEN;

typedef struct 
{
unsigned int     rtc_alarm_int_status:1;
unsigned int     rtc_date_int_status:1;
unsigned int     rtc_hour_int_status:1;
unsigned int     rtc_min_int_status:1;
unsigned int     rtc_hsec_int_status:1;
unsigned int     reserved_0:20;
unsigned int     RTCRST:1;
unsigned int     reserved_1:1;
unsigned int     ALARMINTE:1;
unsigned int     DAINTE:1;
unsigned int     HUINTE:1;
unsigned int     MUINTE:1;
unsigned int     HSUINTE:1;
}A_RTCCR;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     D_RTCSEC:7;
}D_RTCSEC;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     D_RTCMIN:6;
}D_RTCMIN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     D_RTCHR:5;
}D_RTCHR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     D_RTCDATE1:8;
}D_RTCDATE1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     D_RTCDATE2:7;
}D_RTCDATE2;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     D_ALMMIN:6;
}D_ALMMIN;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     D_ALMHR:5;
}D_ALMHR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     D_ALMDATE1:8;
}D_ALMDATE1;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     D_ALMDATE2:7;
}D_ALMDATE2;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     27Mclk_en:1;
unsigned int     VREF:2;
unsigned int     D_RTCSTOP:1;
}D_RTCSTOP;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     D_RTCPWR:1;
unsigned int     CO:2;
unsigned int     CI:2;
unsigned int     CLKSEL:1;
unsigned int     BC:2;
}D_RTCACR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     D_RTCEN:8;
}D_RTCEN;

typedef struct 
{
unsigned int     rtc_alarm_int_status:1;
unsigned int     rtc_date_int_status:1;
unsigned int     rtc_hour_int_status:1;
unsigned int     rtc_min_int_status:1;
unsigned int     rtc_hsec_int_status:1;
unsigned int     reserved_0:20;
unsigned int     RTCRST:1;
unsigned int     reserved_1:1;
unsigned int     ALARMINTE:1;
unsigned int     DAINTE:1;
unsigned int     HUINTE:1;
unsigned int     MUINTE:1;
unsigned int     HSUINTE:1;
}D_RTCCR;

typedef struct 
{
unsigned int     reserved_0:14;
unsigned int     write_en9:1;
unsigned int     iso_rst_wd_mask:1;
unsigned int     write_en8:1;
unsigned int     dc_phy_cke_pd:1;
unsigned int     write_en7:1;
unsigned int     iso_mis_clk_en:1;
unsigned int     write_en6:1;
unsigned int     iso_rbus_sel:1;
unsigned int     write_en5:1;
unsigned int     iso_rst_mask:1;
unsigned int     write_en4:1;
unsigned int     clk_osc_on_en:1;
unsigned int     write_en3:1;
unsigned int     crt_sw_rstn:1;
unsigned int     write_en2:1;
unsigned int     iso_clk_sel:1;
unsigned int     write_en1:1;
unsigned int     ejtag_en:1;
}ISO_CTRL;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     hsec_int_en:1;
unsigned int     alarm_int_en:1;
}ISO_RTC;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     iso_ctrl_en1:1;
unsigned int     iso_ctrl_en0:1;
}ISO_CELL;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     v1_on:1;
}ISO_POWER;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     cec:1;
unsigned int     reserved_1:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     vfd_ardswda:1;
unsigned int     vfd_ardswa:1;
unsigned int     vfd_ardkpadda:1;
unsigned int     vfd_ardkpada:1;
unsigned int     vfd_wdone:1;
unsigned int     rtc_alarm:1;
unsigned int     rtc_hsec:1;
unsigned int     reserved_2:5;
unsigned int     ur1_to:1;
unsigned int     irda:1;
unsigned int     ur2:1;
unsigned int     ur1:1;
unsigned int     ur0:1;
unsigned int     reserved_3:2;
}ISO_SCPU_INT_EN;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     cec:1;
unsigned int     reserved_1:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     vfd_ardswda:1;
unsigned int     vfd_ardswa:1;
unsigned int     vfd_ardkpadda:1;
unsigned int     vfd_ardkpada:1;
unsigned int     vfd_wdone:1;
unsigned int     rtc_alarm:1;
unsigned int     rtc_hsec:1;
unsigned int     reserved_2:5;
unsigned int     ur1_to:1;
unsigned int     irda:1;
unsigned int     ur2:1;
unsigned int     ur1:1;
unsigned int     ur0:1;
unsigned int     reserved_3:2;
}ISO_KCPU_INT_EN;

typedef struct 
{
unsigned int     reserved_0:9;
unsigned int     cec:1;
unsigned int     reserved_1:1;
unsigned int     gpioda:1;
unsigned int     gpioa:1;
unsigned int     vfd_ardswda:1;
unsigned int     vfd_ardswa:1;
unsigned int     vfd_ardkpadda:1;
unsigned int     vfd_ardkpada:1;
unsigned int     vfd_wdone:1;
unsigned int     rtc_alarm:1;
unsigned int     rtc_hsec:1;
unsigned int     reserved_2:5;
unsigned int     ur1_to:1;
unsigned int     irda:1;
unsigned int     ur2:1;
unsigned int     ur1:1;
unsigned int     ur0:1;
unsigned int     reserved_3:2;
}ISO_ACPU_INT_EN;

typedef struct 
{
unsigned int     acpu_boot_info:32;
}ISO_CPU_ST1;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     acpu_boot_info_valid:1;
}ISO_CPU_ST1V;

typedef struct 
{
unsigned int     rvd31:1;
unsigned int     rvd30:1;
unsigned int     rvd29:1;
unsigned int     rvd28:1;
unsigned int     rvd27:1;
unsigned int     rvd26:1;
unsigned int     rvd25:1;
unsigned int     rvd24:1;
unsigned int     rvd23:1;
unsigned int     rvd22:1;
unsigned int     rvd21:1;
unsigned int     rvd20:1;
unsigned int     rvd19:1;
unsigned int     rvd18:1;
unsigned int     rvd17:1;
unsigned int     rvd16:1;
unsigned int     rvd15:1;
unsigned int     rvd14:1;
unsigned int     rvd13:1;
unsigned int     rvd12:1;
unsigned int     rvd11:1;
unsigned int     rvd10:1;
unsigned int     rvd9:1;
unsigned int     rvd8:1;
unsigned int     rvd7:1;
unsigned int     rvd6:1;
unsigned int     rvd5:1;
unsigned int     rvd4:1;
unsigned int     rvd3:1;
unsigned int     rvd2:1;
unsigned int     rvd1:1;
unsigned int     rvd0:1;
}ISO_DUMMY1;

typedef struct 
{
unsigned int     rvd31:1;
unsigned int     rvd30:1;
unsigned int     rvd29:1;
unsigned int     rvd28:1;
unsigned int     rvd27:1;
unsigned int     rvd26:1;
unsigned int     rvd25:1;
unsigned int     rvd24:1;
unsigned int     rvd23:1;
unsigned int     rvd22:1;
unsigned int     rvd21:1;
unsigned int     rvd20:1;
unsigned int     rvd19:1;
unsigned int     rvd18:1;
unsigned int     rvd17:1;
unsigned int     rvd16:1;
unsigned int     rvd15:1;
unsigned int     rvd14:1;
unsigned int     rvd13:1;
unsigned int     rvd12:1;
unsigned int     rvd11:1;
unsigned int     rvd10:1;
unsigned int     rvd9:1;
unsigned int     rvd8:1;
unsigned int     rvd7:1;
unsigned int     rvd6:1;
unsigned int     rvd5:1;
unsigned int     rvd4:1;
unsigned int     rvd3:1;
unsigned int     rvd2:1;
unsigned int     rvd1:1;
unsigned int     rvd0:1;
}ISO_DUMMY2;

typedef struct 
{
unsigned int     rvd3:3;
unsigned int     ur2_flow_pol:1;
unsigned int     to_len:8;
unsigned int     to_int_en:1;
unsigned int     toauareq:1;
unsigned int     ur1_flow_pol:1;
unsigned int     mdifen:1;
unsigned int     reserved_0:2;
unsigned int     txempthr:6;
unsigned int     reserved_1:2;
unsigned int     rxfulthr:6;
}ISO_UR_CTRL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     rx_wrd_count:5;
unsigned int     reserved_1:3;
unsigned int     tx_wrd_count:5;
}ISO_UR_STS;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     ir_tx:1;
unsigned int     ir_raw:1;
}ISO_LPI;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cnt_wait_pwr:16;
}ISO_WD;

typedef struct 
{
unsigned int     sc_key_3:8;
unsigned int     sc_key_2:8;
unsigned int     sc_key_1:8;
unsigned int     sc_key_0:8;
}ISO_SC_KEY03;

typedef struct 
{
unsigned int     sc_key_7:8;
unsigned int     sc_key_6:8;
unsigned int     sc_key_5:8;
unsigned int     sc_key_4:8;
}ISO_SC_KEY47;

typedef struct 
{
unsigned int     sc_key_b:8;
unsigned int     sc_key_a:8;
unsigned int     sc_key_9:8;
unsigned int     sc_key_8:8;
}ISO_SC_KEY8B;

typedef struct 
{
unsigned int     sc_key_f:8;
unsigned int     sc_key_e:8;
unsigned int     sc_key_d:8;
unsigned int     sc_key_c:8;
}ISO_SC_KEYCF;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     reboot_from_ddr:3;
}ISO_OTP;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpdir:20;
}ISO_GPDIR;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpdir:20;
}ISO_GPDIR_1;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpdato:20;
}ISO_GPDATO;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpdato:20;
}ISO_GPDATO_1;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpdati:20;
}ISO_GPDATI;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpdati:20;
}ISO_GPDATI_1;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gp:20;
}ISO_GPIE;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gp:20;
}ISO_GPIE_1;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpha:20;
}ISO_GPDP;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpha:20;
}ISO_GPDP_1;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     write_en1:1;
unsigned int     clk1:3;
}ISO_GPDEB;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpha:20;
}ISO_ISR_GP0A;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpha:20;
}ISO_ISR_GP1A;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpha:20;
}ISO_ISR_GP0DA;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     gpha:20;
}ISO_ISR_GP1DA;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     kpaden:1;
unsigned int     swen:1;
unsigned int     clksel:1;
unsigned int     envfd:1;
}ISO_VFD_CTL;

typedef struct 
{
unsigned int     reserved_0:19;
unsigned int     nact_csn:1;
unsigned int     b3c:1;
unsigned int     b2c:1;
unsigned int     b1c:1;
unsigned int     b0c:1;
unsigned int     enb3:1;
unsigned int     enb2:1;
unsigned int     enb1:1;
unsigned int     enb0:1;
unsigned int     reserved_1:2;
unsigned int     wd:1;
unsigned int     wdie:1;
}ISO_VFD_WRCTL;

typedef struct 
{
unsigned int     byte3:8;
unsigned int     byte2:8;
unsigned int     byte1:8;
unsigned int     byte0:8;
}ISO_VFDO;

typedef struct 
{
unsigned int     reserved_0:21;
unsigned int     kpadbn:3;
unsigned int     reserved_1:2;
unsigned int     swha:1;
unsigned int     kpadha:1;
unsigned int     reserved_2:2;
unsigned int     ardp:2;
}ISO_VFD_ARDCTL;

typedef struct 
{
unsigned int     kpadie:32;
}ISO_VFD_KPADLIE;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     kpadie:16;
}ISO_VFD_KPADHIE;

typedef struct 
{
unsigned int     reserved_0:28;
unsigned int     swie:4;
}ISO_VFD_SWIE;

typedef struct 
{
unsigned int     st_31_24:8;
unsigned int     st_23_16:8;
unsigned int     st_15_8:8;
unsigned int     st_7_0:8;
}ISO_VFD_ARDKPADL;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     st_15_8:8;
unsigned int     st_7_0:8;
}ISO_VFD_ARDKPADH;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     rvda:12;
unsigned int     st:4;
}ISO_VFD_ARDSW;

typedef struct 
{
unsigned int     reserved_0:15;
unsigned int     clksel_1:1;
unsigned int     tclk_csn:8;
unsigned int     twait1:8;
}ISO_VFD_CTL1;

typedef struct 
{
unsigned int     reserved_0:4;
unsigned int     standby_smt:1;
unsigned int     standby_e2:1;
unsigned int     standby_pud_en:1;
unsigned int     standby_pud_sel:1;
unsigned int     vfd_d_smt:1;
unsigned int     vfd_d_e2:1;
unsigned int     vfd_d_pud_en:1;
unsigned int     vfd_d_pud_sel:1;
unsigned int     vfd_clk_smt:1;
unsigned int     vfd_clk_e2:1;
unsigned int     vfd_clk_pud_en:1;
unsigned int     vfd_clk_pud_sel:1;
unsigned int     vfd_cs_n_smt:1;
unsigned int     vfd_cs_n_e2:1;
unsigned int     vfd_cs_n_pud_en:1;
unsigned int     vfd_cs_n_pud_sel:1;
unsigned int     ir_in_smt:1;
unsigned int     ir_in_e2:1;
unsigned int     ir_in_pud_en:1;
unsigned int     ir_in_pud_sel:1;
unsigned int     usb_ovrcur_flag_n_1_smt:1;
unsigned int     usb_ovrcur_flag_n_1_e2:1;
unsigned int     usb_ovrcur_flag_n_1_pud_en:1;
unsigned int     usb_ovrcur_flag_n_1_pud_sel:1;
unsigned int     usb_ovrcur_flag_n_0_smt:1;
unsigned int     usb_ovrcur_flag_n_0_e2:1;
unsigned int     usb_ovrcur_flag_n_0_pud_en:1;
unsigned int     usb_ovrcur_flag_n_0_pud_sel:1;
}ISO_PFUNC1;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ur0_tx_smt:1;
unsigned int     ur0_tx_e2:1;
unsigned int     ur0_tx_pud_en:1;
unsigned int     ur0_tx_pud_sel:1;
unsigned int     ur0_rx_smt:1;
unsigned int     ur0_rx_e2:1;
unsigned int     ur0_rx_pud_en:1;
unsigned int     ur0_rx_pud_sel:1;
unsigned int     ur1_cts_n_smt:1;
unsigned int     ur1_cts_n_e2:1;
unsigned int     ur1_cts_n_pud_en:1;
unsigned int     ur1_cts_n_pud_sel:1;
unsigned int     ur1_rts_n_smt:1;
unsigned int     ur1_rts_n_e2:1;
unsigned int     ur1_rts_n_pud_en:1;
unsigned int     ur1_rts_n_pud_sel:1;
unsigned int     ur1_tx_smt:1;
unsigned int     ur1_tx_e2:1;
unsigned int     ur1_tx_pud_en:1;
unsigned int     ur1_tx_pud_sel:1;
unsigned int     ur1_rx_smt:1;
unsigned int     ur1_rx_e2:1;
unsigned int     ur1_rx_pud_en:1;
unsigned int     ur1_rx_pud_sel:1;
}ISO_PFUNC2;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     ur0_tx:2;
unsigned int     ur0_rx:2;
unsigned int     ur1_cts_n:2;
unsigned int     ur1_rts_n:2;
unsigned int     ur1_tx:2;
unsigned int     ur1_rx:2;
unsigned int     usb1:2;
unsigned int     usb0:2;
unsigned int     ir_in:2;
unsigned int     vfd_cs_n:2;
unsigned int     vfd_clk:2;
unsigned int     vfd_d:2;
}ISO_MUXPAD;

typedef struct 
{
unsigned int     irrbl:8;
unsigned int     irrml:8;
unsigned int     irrdzl:8;
unsigned int     irrdol:8;
}ISO_IR_PSR;

typedef struct 
{
unsigned int     reserved_0:10;
unsigned int     irrdl:6;
unsigned int     irrrl:8;
unsigned int     irrsl:8;
}ISO_IR_PER;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irfd:16;
}ISO_IR_SF;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     iriotcdp:16;
}ISO_IR_DPIR;

typedef struct 
{
unsigned int     irsr:1;
unsigned int     reserved_0:5;
unsigned int     rcmm_en:1;
unsigned int     toshiba_en:1;
unsigned int     irednm:1;
unsigned int     reserved_1:1;
unsigned int     iredn:6;
unsigned int     reserved_2:1;
unsigned int     raw_fifo_ov:1;
unsigned int     raw_fifo_val:1;
unsigned int     raw_en:1;
unsigned int     mlae:1;
unsigned int     irie:1;
unsigned int     irres:1;
unsigned int     irue:1;
unsigned int     ircm:1;
unsigned int     irbme:1;
unsigned int     irdpm:1;
unsigned int     irdn:5;
}ISO_IR_CR;

typedef struct 
{
unsigned int     irrp:32;
}ISO_IR_RP;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rmt_big:1;
unsigned int     raw_fifo_ov:1;
unsigned int     raw_fifo_val:1;
unsigned int     irrf:1;
unsigned int     irdvf:1;
}ISO_IR_SR;

typedef struct 
{
unsigned int     reserved_0:6;
unsigned int     write_en2:1;
unsigned int     stop_sample:1;
unsigned int     stop_time:16;
unsigned int     reserved_1:1;
unsigned int     write_en1:1;
unsigned int     fifo_thr:6;
}ISO_IR_RAW_CTRL;

typedef struct 
{
unsigned int     dat:32;
}ISO_IR_RAW_FF;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     cnt:16;
}ISO_IR_RAW_SAMPLE_TIME;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     val:6;
}ISO_IR_RAW_WL;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     len:8;
unsigned int     clk:16;
}ISO_IR_RAW_DEB;

typedef struct 
{
unsigned int     irrbl:8;
unsigned int     irrml:8;
unsigned int     irrdzl:8;
unsigned int     irrdol:8;
}ISO_IR_PSR_UP;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irrrl:8;
unsigned int     irrsl:8;
}ISO_IR_PER_UP;

typedef struct 
{
unsigned int     reserved_0:23;
unsigned int     rc6_en:1;
unsigned int     irtr:8;
}ISO_IR_CTRL_RC6;

typedef struct 
{
unsigned int     irrp:32;
}ISO_IR_RP2;

typedef struct 
{
unsigned int     irtx_en:1;
unsigned int     reserved_0:20;
unsigned int     iact_lvl:1;
unsigned int     modulation:1;
unsigned int     endian:1;
unsigned int     dummy:2;
unsigned int     fifoout_inv:1;
unsigned int     irtxout_inv:1;
unsigned int     reserved_1:3;
unsigned int     start:1;
}ISO_IRTX_CFG;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     irtx_fd:16;
}ISO_IRTX_TIM;

typedef struct 
{
unsigned int     reserved_0:12;
unsigned int     pwm_clksrc_div:4;
unsigned int     pwm_clk_duty:8;
unsigned int     pwm_clk_div:8;
}ISO_IRTX_PWM_SETTING;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     data_thr:6;
unsigned int     reserved_1:6;
unsigned int     emp_en:1;
unsigned int     req_en:1;
}ISO_IRTX_INT_EN;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     emp_flag:1;
unsigned int     req_flag:1;
}ISO_IRTX_INT_ST;

typedef struct 
{
unsigned int     fifo_rst:1;
unsigned int     reserved_0:19;
unsigned int     valid_len:4;
unsigned int     wrp:4;
unsigned int     rdp:4;
}ISO_IRTX_FIFO_ST;

typedef struct 
{
unsigned int     data:32;
}ISO_IRTX_FIFO;

typedef struct 
{
unsigned int     len_11:8;
unsigned int     len_10:8;
unsigned int     len_01:8;
unsigned int     len_00:8;
}ISO_IRRCMM_TIMING;

typedef struct 
{
unsigned int     cec_mode:2;
unsigned int     reserved_0:1;
unsigned int     test_mode_pad_en:1;
unsigned int     logical_addr0:4;
unsigned int     timer_div:8;
unsigned int     pre_div:8;
unsigned int     unreg_ack_en:1;
unsigned int     reserved_1:1;
unsigned int     cdc_arbitration_en:1;
unsigned int     test_mode_pad_data:5;
}ISO_CEC_CR0;

typedef struct 
{
unsigned int     cec_pad_in:1;
unsigned int     dummy0:3;
unsigned int     logical_addr3:4;
unsigned int     logical_addr2:4;
unsigned int     logical_addr1:4;
unsigned int     dummy1:4;
unsigned int     clear_cec_int:1;
unsigned int     wt_cnt:6;
unsigned int     lattest:1;
unsigned int     retry_no:4;
}ISO_CEC_RTCR0;

typedef struct 
{
unsigned int     broadcast_addr:1;
unsigned int     reserved_0:11;
unsigned int     dest_addr:4;
unsigned int     rx_en:1;
unsigned int     rx_rst:1;
unsigned int     rx_continuous:1;
unsigned int     rx_int_en:1;
unsigned int     init_addr:4;
unsigned int     rx_eom:1;
unsigned int     rx_int:1;
unsigned int     rx_fifo_ov:1;
unsigned int     rx_fifo_cnt:5;
}ISO_CEC_RXCR0;

typedef struct 
{
unsigned int     reserved_0:11;
unsigned int     tx_addr_en:1;
unsigned int     tx_addr:4;
unsigned int     tx_en:1;
unsigned int     tx_rst:1;
unsigned int     tx_continuous:1;
unsigned int     tx_int_en:1;
unsigned int     dest_addr:4;
unsigned int     tx_eom:1;
unsigned int     tx_int:1;
unsigned int     tx_fifo_ud:1;
unsigned int     tx_fifo_cnt:5;
}ISO_CEC_TXCR0;

typedef struct 
{
unsigned int     reserved_0:25;
unsigned int     tx_add_cnt:1;
unsigned int     rx_sub_cnt:1;
unsigned int     fifo_cnt:5;
}ISO_CEC_TXDR0;

typedef struct 
{
unsigned int     tx_fifo_0:8;
unsigned int     tx_fifo_1:8;
unsigned int     tx_fifo_2:8;
unsigned int     tx_fifo_3:8;
}ISO_CEC_TXDR1;

typedef struct 
{
unsigned int     tx_fifo_4:8;
unsigned int     tx_fifo_5:8;
unsigned int     tx_fifo_6:8;
unsigned int     tx_fifo_7:8;
}ISO_CEC_TXDR2;

typedef struct 
{
unsigned int     tx_fifo_8:8;
unsigned int     tx_fifo_9:8;
unsigned int     tx_fifo_a:8;
unsigned int     tx_fifo_b:8;
}ISO_CEC_TXDR3;

typedef struct 
{
unsigned int     tx_fifo_c:8;
unsigned int     tx_fifo_d:8;
unsigned int     tx_fifo_e:8;
unsigned int     tx_fifo_f:8;
}ISO_CEC_TXDR4;

typedef struct 
{
unsigned int     rx_fifo_0:8;
unsigned int     rx_fifo_1:8;
unsigned int     rx_fifo_2:8;
unsigned int     rx_fifo_3:8;
}ISO_CEC_RXDR1;

typedef struct 
{
unsigned int     rx_fifo_4:8;
unsigned int     rx_fifo_5:8;
unsigned int     rx_fifo_6:8;
unsigned int     rx_fifo_7:8;
}ISO_CEC_RXDR2;

typedef struct 
{
unsigned int     rx_fifo_8:8;
unsigned int     rx_fifo_9:8;
unsigned int     rx_fifo_a:8;
unsigned int     rx_fifo_b:8;
}ISO_CEC_RXDR3;

typedef struct 
{
unsigned int     rx_fifo_c:8;
unsigned int     rx_fifo_d:8;
unsigned int     rx_fifo_e:8;
unsigned int     rx_fifo_f:8;
}ISO_CEC_RXDR4;

typedef struct 
{
unsigned int     rx_start_low:8;
unsigned int     rx_start_period:8;
unsigned int     rx_data_sample:8;
unsigned int     rx_data_period:8;
}ISO_CEC_RXTCR0;

typedef struct 
{
unsigned int     reserved_0:16;
unsigned int     tx_start_low:8;
unsigned int     tx_start_high:8;
}ISO_CEC_TXTCR0;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     tx_data_low:8;
unsigned int     tx_data_01:8;
unsigned int     tx_data_high:8;
}ISO_CEC_TXTCR1;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_01:8;
}ISO_GDI_CEC_COMPARE_OPCODE_01;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_01:8;
}ISO_GDI_CEC_SEND_OPCODE_01;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_01:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_01;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_01:8;
}ISO_GDI_CEC_OPRAND_01;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_02:8;
}ISO_GDI_CEC_OPRAND_02;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_03:8;
}ISO_GDI_CEC_OPRAND_03;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_02:8;
}ISO_GDI_CEC_COMPARE_OPCODE_02;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_02:8;
}ISO_GDI_CEC_SEND_OPCODE_02;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_02:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_02;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_04:8;
}ISO_GDI_CEC_OPRAND_04;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_05:8;
}ISO_GDI_CEC_OPRAND_05;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_06:8;
}ISO_GDI_CEC_OPRAND_06;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_03:8;
}ISO_GDI_CEC_COMPARE_OPCODE_03;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_03:8;
}ISO_GDI_CEC_SEND_OPCODE_03;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_03:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_03;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_07:8;
}ISO_GDI_CEC_OPRAND_07;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_08:8;
}ISO_GDI_CEC_OPRAND_08;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_09:8;
}ISO_GDI_CEC_OPRAND_09;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_04:8;
}ISO_GDI_CEC_COMPARE_OPCODE_04;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     send_opcode_04:8;
}ISO_GDI_CEC_SEND_OPCODE_04;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     operand_number_04:2;
}ISO_GDI_CEC_SEND_OPRAND_NUMBER_04;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_10:8;
}ISO_GDI_CEC_OPRAND_10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_11:8;
}ISO_GDI_CEC_OPRAND_11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     operand_12:8;
}ISO_GDI_CEC_OPRAND_12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_05:8;
}ISO_GDI_CEC_COMPARE_OPCODE_05;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_06:8;
}ISO_GDI_CEC_COMPARE_OPCODE_06;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_07:8;
}ISO_GDI_CEC_COMPARE_OPCODE_07;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_08:8;
}ISO_GDI_CEC_COMPARE_OPCODE_08;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_09:8;
}ISO_GDI_CEC_COMPARE_OPCODE_09;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_10:8;
}ISO_GDI_CEC_COMPARE_OPCODE_10;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_11:8;
}ISO_GDI_CEC_COMPARE_OPCODE_11;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_12:8;
}ISO_GDI_CEC_COMPARE_OPCODE_12;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_13:8;
}ISO_GDI_CEC_COMPARE_OPCODE_13;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_14:8;
}ISO_GDI_CEC_COMPARE_OPCODE_14;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     compare_opcode_15:8;
}ISO_GDI_CEC_COMPARE_OPCODE_15;

typedef struct 
{
unsigned int     reserved_0:17;
unsigned int     en_compare_opcode_15:1;
unsigned int     en_compare_opcode_14:1;
unsigned int     en_compare_opcode_13:1;
unsigned int     en_compare_opcode_12:1;
unsigned int     en_compare_opcode_11:1;
unsigned int     en_compare_opcode_10:1;
unsigned int     en_compare_opcode_09:1;
unsigned int     en_compare_opcode_08:1;
unsigned int     en_compare_opcode_07:1;
unsigned int     en_compare_opcode_06:1;
unsigned int     en_compare_opcode_05:1;
unsigned int     en_compare_opcode_04:1;
unsigned int     en_compare_opcode_03:1;
unsigned int     en_compare_opcode_02:1;
unsigned int     en_compare_opcode_01:1;
}ISO_GDI_CEC_OPCODE_ENABLE;

typedef struct 
{
unsigned int     irq_pending:1;
unsigned int     reserved_0:5;
unsigned int     cec_msg_status_01:1;
unsigned int     cec_msg_status_02:1;
unsigned int     reserved_1:15;
unsigned int     irq_by_cec_receive_special_cmd:1;
unsigned int     reserved_2:8;
}ISO_GDI_POWER_SAVING_MODE;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     set:1;
}ISO_DRM_ST;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_SECURE_CLK;

typedef struct 
{
unsigned int     val:32;
}ISO_DRM_ELAPSED;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST1;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST2;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     clk_div_en:1;
unsigned int     clk_sel:1;
}ISO_DRM_CTRL;

typedef struct 
{
unsigned int     init:32;
}ISO_DRM_CLK_DIV;

typedef struct 
{
unsigned int     tc3tvr:32;
}ISO_TC3TVR;

typedef struct 
{
unsigned int     tc3cvr:32;
}ISO_TC3CVR;

typedef struct 
{
unsigned int     tc3en:1;
unsigned int     tc3mode:1;
unsigned int     tc3pause:1;
unsigned int     rvda:5;
unsigned int     reserved_0:24;
}ISO_TC3CR;

typedef struct 
{
unsigned int     tc3ie:1;
unsigned int     reserved_0:31;
}ISO_TC3ICR;

typedef struct 
{
unsigned int     dat:32;
}ISO_NORST;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST3;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST4;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST5;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST6;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST7;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST8;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST9;

typedef struct 
{
unsigned int     val:32;
}ISO_COLD_RST10;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     kcpu_boot_info_valid:1;
}ISO_CPU_ST2V;

typedef struct 
{
unsigned int     kcpu_boot_info:32;
}ISO_CPU_ST2;

typedef struct 
{
unsigned int     reserved_0:18;
unsigned int     write_enable3:1;
unsigned int     sel1:5;
unsigned int     write_enable2:1;
unsigned int     sel0:5;
unsigned int     write_enable1:1;
unsigned int     enable:1;
}ISO_ACPU_DBG;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     analogy_mode_in:1;
}ISO_ANLG;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dll:8;
}ISO_U0RBR_THR_DLL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlh:8;
}ISO_U0IER_DLH;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fifo16:2;
unsigned int     reserved_1:2;
unsigned int     iid:4;
}ISO_U0IIR_FCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlab:1;
unsigned int     brk:1;
unsigned int     reserved_1:1;
unsigned int     eps:1;
unsigned int     pen:1;
unsigned int     stb:1;
unsigned int     wls:2;
}ISO_U0LCR;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     afce:1;
unsigned int     loop:1;
unsigned int     reserved_1:2;
unsigned int     rts:1;
unsigned int     dtr:1;
}ISO_U0MCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfe:1;
unsigned int     temt:1;
unsigned int     thre:1;
unsigned int     bi:1;
unsigned int     fe:1;
unsigned int     pe:1;
unsigned int     oe:1;
unsigned int     dr:1;
}ISO_U0LSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dcd:1;
unsigned int     ri:1;
unsigned int     dsr:1;
unsigned int     cts:1;
unsigned int     ddcd:1;
unsigned int     teri:1;
unsigned int     ddsr:1;
unsigned int     dcts:1;
}ISO_U0MSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     scr:8;
}ISO_U0SCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rbd:8;
}ISO_U0SRBR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     far:1;
}ISO_U0FAR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     far:8;
}ISO_U0TFR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     rffe:1;
unsigned int     rfpf:1;
unsigned int     rfwd:8;
}ISO_U0RFW;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     busy:1;
}ISO_U0USR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tfl:8;
}ISO_U0TFL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfl:8;
}ISO_U0RFL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     xfr:1;
unsigned int     rfr:1;
unsigned int     ur:1;
}ISO_U0SRR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sbcr:1;
}ISO_U0SBCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sdmam:1;
}ISO_U0SDMAM;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sfe:1;
}ISO_U0SFE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     srt:2;
}ISO_U0SRT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     stet:2;
}ISO_U0STET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     htx:1;
}ISO_U0HTX;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dmasa:1;
}ISO_U0DMASA;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     fifo_mode:8;
unsigned int     reserved_1:2;
unsigned int     dma_extra:1;
unsigned int     uart_add_encoded_params:1;
unsigned int     shadow:1;
unsigned int     fifo_stat:1;
unsigned int     fifo_access:1;
unsigned int     additional_feat:1;
unsigned int     sir_lp_mode:1;
unsigned int     sir_mode:1;
unsigned int     thre_mode:1;
unsigned int     afce_mode:1;
unsigned int     reserved_2:2;
unsigned int     apb_data_width:2;
}ISO_U0CPR;

typedef struct 
{
unsigned int     ucv:32;
}ISO_U0UCV;

typedef struct 
{
unsigned int     ctr:32;
}ISO_U0CTR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dll:8;
}ISO_U1RBR_THR_DLL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlh:8;
}ISO_U1IER_DLH;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fifo16:2;
unsigned int     reserved_1:2;
unsigned int     iid:4;
}ISO_U1IIR_FCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlab:1;
unsigned int     brk:1;
unsigned int     reserved_1:1;
unsigned int     eps:1;
unsigned int     pen:1;
unsigned int     stb:1;
unsigned int     wls:2;
}ISO_U1LCR;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     afce:1;
unsigned int     loop:1;
unsigned int     reserved_1:2;
unsigned int     rts:1;
unsigned int     dtr:1;
}ISO_U1MCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfe:1;
unsigned int     temt:1;
unsigned int     thre:1;
unsigned int     bi:1;
unsigned int     fe:1;
unsigned int     pe:1;
unsigned int     oe:1;
unsigned int     dr:1;
}ISO_U1LSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dcd:1;
unsigned int     ri:1;
unsigned int     dsr:1;
unsigned int     cts:1;
unsigned int     ddcd:1;
unsigned int     teri:1;
unsigned int     ddsr:1;
unsigned int     dcts:1;
}ISO_U1MSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     scr:8;
}ISO_U1SCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rbd:8;
}ISO_U1SRBR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     far:1;
}ISO_U1FAR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     far:8;
}ISO_U1TFR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     rffe:1;
unsigned int     rfpf:1;
unsigned int     rfwd:8;
}ISO_U1RFW;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     busy:1;
}ISO_U1USR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tfl:8;
}ISO_U1TFL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfl:8;
}ISO_U1RFL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     xfr:1;
unsigned int     rfr:1;
unsigned int     ur:1;
}ISO_U1SRR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sbcr:1;
}ISO_U1SBCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sdmam:1;
}ISO_U1SDMAM;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sfe:1;
}ISO_U1SFE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     srt:2;
}ISO_U1SRT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     stet:2;
}ISO_U1STET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     htx:1;
}ISO_U1HTX;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dmasa:1;
}ISO_U1DMASA;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     fifo_mode:8;
unsigned int     reserved_1:2;
unsigned int     dma_extra:1;
unsigned int     uart_add_encoded_params:1;
unsigned int     shadow:1;
unsigned int     fifo_stat:1;
unsigned int     fifo_access:1;
unsigned int     additional_feat:1;
unsigned int     sir_lp_mode:1;
unsigned int     sir_mode:1;
unsigned int     thre_mode:1;
unsigned int     afce_mode:1;
unsigned int     reserved_2:2;
unsigned int     apb_data_width:2;
}ISO_U1CPR;

typedef struct 
{
unsigned int     ucv:32;
}ISO_U1UCV;

typedef struct 
{
unsigned int     ctr:32;
}ISO_U1CTR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dll:8;
}ISO_U2RBR_THR_DLL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlh:8;
}ISO_U2IER_DLH;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     fifo16:2;
unsigned int     reserved_1:2;
unsigned int     iid:4;
}ISO_U2IIR_FCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dlab:1;
unsigned int     brk:1;
unsigned int     reserved_1:1;
unsigned int     eps:1;
unsigned int     pen:1;
unsigned int     stb:1;
unsigned int     wls:2;
}ISO_U2LCR;

typedef struct 
{
unsigned int     reserved_0:26;
unsigned int     afce:1;
unsigned int     loop:1;
unsigned int     reserved_1:2;
unsigned int     rts:1;
unsigned int     dtr:1;
}ISO_U2MCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfe:1;
unsigned int     temt:1;
unsigned int     thre:1;
unsigned int     bi:1;
unsigned int     fe:1;
unsigned int     pe:1;
unsigned int     oe:1;
unsigned int     dr:1;
}ISO_U2LSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     dcd:1;
unsigned int     ri:1;
unsigned int     dsr:1;
unsigned int     cts:1;
unsigned int     ddcd:1;
unsigned int     teri:1;
unsigned int     ddsr:1;
unsigned int     dcts:1;
}ISO_U2MSR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     scr:8;
}ISO_U2SCR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rbd:8;
}ISO_U2SRBR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     far:1;
}ISO_U2FAR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     far:8;
}ISO_U2TFR;

typedef struct 
{
unsigned int     reserved_0:22;
unsigned int     rffe:1;
unsigned int     rfpf:1;
unsigned int     rfwd:8;
}ISO_U2RFW;

typedef struct 
{
unsigned int     reserved_0:27;
unsigned int     rff:1;
unsigned int     rfne:1;
unsigned int     tfe:1;
unsigned int     tfnf:1;
unsigned int     busy:1;
}ISO_U2USR;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     tfl:8;
}ISO_U2TFL;

typedef struct 
{
unsigned int     reserved_0:24;
unsigned int     rfl:8;
}ISO_U2RFL;

typedef struct 
{
unsigned int     reserved_0:29;
unsigned int     xfr:1;
unsigned int     rfr:1;
unsigned int     ur:1;
}ISO_U2SRR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sbcr:1;
}ISO_U2SBCR;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sdmam:1;
}ISO_U2SDMAM;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     sfe:1;
}ISO_U2SFE;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     srt:2;
}ISO_U2SRT;

typedef struct 
{
unsigned int     reserved_0:30;
unsigned int     stet:2;
}ISO_U2STET;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     htx:1;
}ISO_U2HTX;

typedef struct 
{
unsigned int     reserved_0:31;
unsigned int     dmasa:1;
}ISO_U2DMASA;

typedef struct 
{
unsigned int     reserved_0:8;
unsigned int     fifo_mode:8;
unsigned int     reserved_1:2;
unsigned int     dma_extra:1;
unsigned int     uart_add_encoded_params:1;
unsigned int     shadow:1;
unsigned int     fifo_stat:1;
unsigned int     fifo_access:1;
unsigned int     additional_feat:1;
unsigned int     sir_lp_mode:1;
unsigned int     sir_mode:1;
unsigned int     thre_mode:1;
unsigned int     afce_mode:1;
unsigned int     reserved_2:2;
unsigned int     apb_data_width:2;
}ISO_U2CPR;

typedef struct 
{
unsigned int     ucv:32;
}ISO_U2UCV;

typedef struct 
{
unsigned int     ctr:32;
}ISO_U2CTR;

#endif

#define ISO_ISR                                                                      0x18061000
#define ISO_ISR_reg_addr                                                             "0xB8061000"
#define ISO_ISR_reg                                                                  0xB8061000
#define set_ISO_ISR_reg(data)   (*((volatile unsigned int*) ISO_ISR_reg)=data)
#define get_ISO_ISR_reg   (*((volatile unsigned int*) ISO_ISR_reg))
#define ISO_ISR_inst_adr                                                             "0x0000"
#define ISO_ISR_inst                                                                 0x0000
#define ISO_ISR_cec_int_shift                                                        (22)
#define ISO_ISR_cec_int_mask                                                         (0x00400000)
#define ISO_ISR_cec_int(data)                                                        (0x00400000&((data)<<22))
#define ISO_ISR_cec_int_src(data)                                                    ((0x00400000&(data))>>22)
#define ISO_ISR_get_cec_int(data)                                                    ((0x00400000&(data))>>22)
#define ISO_ISR_gpioda_int_shift                                                     (20)
#define ISO_ISR_gpioda_int_mask                                                      (0x00100000)
#define ISO_ISR_gpioda_int(data)                                                     (0x00100000&((data)<<20))
#define ISO_ISR_gpioda_int_src(data)                                                 ((0x00100000&(data))>>20)
#define ISO_ISR_get_gpioda_int(data)                                                 ((0x00100000&(data))>>20)
#define ISO_ISR_gpioa_int_shift                                                      (19)
#define ISO_ISR_gpioa_int_mask                                                       (0x00080000)
#define ISO_ISR_gpioa_int(data)                                                      (0x00080000&((data)<<19))
#define ISO_ISR_gpioa_int_src(data)                                                  ((0x00080000&(data))>>19)
#define ISO_ISR_get_gpioa_int(data)                                                  ((0x00080000&(data))>>19)
#define ISO_ISR_vfd_ardswda_int_shift                                                (18)
#define ISO_ISR_vfd_ardswda_int_mask                                                 (0x00040000)
#define ISO_ISR_vfd_ardswda_int(data)                                                (0x00040000&((data)<<18))
#define ISO_ISR_vfd_ardswda_int_src(data)                                            ((0x00040000&(data))>>18)
#define ISO_ISR_get_vfd_ardswda_int(data)                                            ((0x00040000&(data))>>18)
#define ISO_ISR_vfd_ardswa_int_shift                                                 (17)
#define ISO_ISR_vfd_ardswa_int_mask                                                  (0x00020000)
#define ISO_ISR_vfd_ardswa_int(data)                                                 (0x00020000&((data)<<17))
#define ISO_ISR_vfd_ardswa_int_src(data)                                             ((0x00020000&(data))>>17)
#define ISO_ISR_get_vfd_ardswa_int(data)                                             ((0x00020000&(data))>>17)
#define ISO_ISR_vfd_ardkpadda_int_shift                                              (16)
#define ISO_ISR_vfd_ardkpadda_int_mask                                               (0x00010000)
#define ISO_ISR_vfd_ardkpadda_int(data)                                              (0x00010000&((data)<<16))
#define ISO_ISR_vfd_ardkpadda_int_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_ISR_get_vfd_ardkpadda_int(data)                                          ((0x00010000&(data))>>16)
#define ISO_ISR_vfd_ardkpada_int_shift                                               (15)
#define ISO_ISR_vfd_ardkpada_int_mask                                                (0x00008000)
#define ISO_ISR_vfd_ardkpada_int(data)                                               (0x00008000&((data)<<15))
#define ISO_ISR_vfd_ardkpada_int_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_ISR_get_vfd_ardkpada_int(data)                                           ((0x00008000&(data))>>15)
#define ISO_ISR_vfd_wdone_int_shift                                                  (14)
#define ISO_ISR_vfd_wdone_int_mask                                                   (0x00004000)
#define ISO_ISR_vfd_wdone_int(data)                                                  (0x00004000&((data)<<14))
#define ISO_ISR_vfd_wdone_int_src(data)                                              ((0x00004000&(data))>>14)
#define ISO_ISR_get_vfd_wdone_int(data)                                              ((0x00004000&(data))>>14)
#define ISO_ISR_rtc_alarm_int_shift                                                  (13)
#define ISO_ISR_rtc_alarm_int_mask                                                   (0x00002000)
#define ISO_ISR_rtc_alarm_int(data)                                                  (0x00002000&((data)<<13))
#define ISO_ISR_rtc_alarm_int_src(data)                                              ((0x00002000&(data))>>13)
#define ISO_ISR_get_rtc_alarm_int(data)                                              ((0x00002000&(data))>>13)
#define ISO_ISR_rtc_hsec_int_shift                                                   (12)
#define ISO_ISR_rtc_hsec_int_mask                                                    (0x00001000)
#define ISO_ISR_rtc_hsec_int(data)                                                   (0x00001000&((data)<<12))
#define ISO_ISR_rtc_hsec_int_src(data)                                               ((0x00001000&(data))>>12)
#define ISO_ISR_get_rtc_hsec_int(data)                                               ((0x00001000&(data))>>12)
#define ISO_ISR_ur1_to_int_shift                                                     (6)
#define ISO_ISR_ur1_to_int_mask                                                      (0x00000040)
#define ISO_ISR_ur1_to_int(data)                                                     (0x00000040&((data)<<6))
#define ISO_ISR_ur1_to_int_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_ISR_get_ur1_to_int(data)                                                 ((0x00000040&(data))>>6)
#define ISO_ISR_irda_int_shift                                                       (5)
#define ISO_ISR_irda_int_mask                                                        (0x00000020)
#define ISO_ISR_irda_int(data)                                                       (0x00000020&((data)<<5))
#define ISO_ISR_irda_int_src(data)                                                   ((0x00000020&(data))>>5)
#define ISO_ISR_get_irda_int(data)                                                   ((0x00000020&(data))>>5)
#define ISO_ISR_ur2_int_shift                                                        (4)
#define ISO_ISR_ur2_int_mask                                                         (0x00000010)
#define ISO_ISR_ur2_int(data)                                                        (0x00000010&((data)<<4))
#define ISO_ISR_ur2_int_src(data)                                                    ((0x00000010&(data))>>4)
#define ISO_ISR_get_ur2_int(data)                                                    ((0x00000010&(data))>>4)
#define ISO_ISR_ur1_int_shift                                                        (3)
#define ISO_ISR_ur1_int_mask                                                         (0x00000008)
#define ISO_ISR_ur1_int(data)                                                        (0x00000008&((data)<<3))
#define ISO_ISR_ur1_int_src(data)                                                    ((0x00000008&(data))>>3)
#define ISO_ISR_get_ur1_int(data)                                                    ((0x00000008&(data))>>3)
#define ISO_ISR_ur0_int_shift                                                        (2)
#define ISO_ISR_ur0_int_mask                                                         (0x00000004)
#define ISO_ISR_ur0_int(data)                                                        (0x00000004&((data)<<2))
#define ISO_ISR_ur0_int_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_ISR_get_ur0_int(data)                                                    ((0x00000004&(data))>>2)
#define ISO_ISR_tc3_int_shift                                                        (1)
#define ISO_ISR_tc3_int_mask                                                         (0x00000002)
#define ISO_ISR_tc3_int(data)                                                        (0x00000002&((data)<<1))
#define ISO_ISR_tc3_int_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_ISR_get_tc3_int(data)                                                    ((0x00000002&(data))>>1)
#define ISO_ISR_write_data_shift                                                     (0)
#define ISO_ISR_write_data_mask                                                      (0x00000001)
#define ISO_ISR_write_data(data)                                                     (0x00000001&((data)<<0))
#define ISO_ISR_write_data_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_ISR_get_write_data(data)                                                 ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR                                                                 0x18007004
#define ISO_UMSK_ISR_reg_addr                                                        "0xB8007004"
#define ISO_UMSK_ISR_reg                                                             0xB8007004
#define set_ISO_UMSK_ISR_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_reg)=data)
#define get_ISO_UMSK_ISR_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_reg))
#define ISO_UMSK_ISR_inst_adr                                                        "0x0001"
#define ISO_UMSK_ISR_inst                                                            0x0001
#define ISO_UMSK_ISR_gpioda_int_shift                                                (20)
#define ISO_UMSK_ISR_gpioda_int_mask                                                 (0x00100000)
#define ISO_UMSK_ISR_gpioda_int(data)                                                (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_gpioda_int_src(data)                                            ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_get_gpioda_int(data)                                            ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_gpioa_int_shift                                                 (19)
#define ISO_UMSK_ISR_gpioa_int_mask                                                  (0x00080000)
#define ISO_UMSK_ISR_gpioa_int(data)                                                 (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_gpioa_int_src(data)                                             ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_get_gpioa_int(data)                                             ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_vfd_ardswda_int_shift                                           (18)
#define ISO_UMSK_ISR_vfd_ardswda_int_mask                                            (0x00040000)
#define ISO_UMSK_ISR_vfd_ardswda_int(data)                                           (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_vfd_ardswda_int_src(data)                                       ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_get_vfd_ardswda_int(data)                                       ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_vfd_ardswa_int_shift                                            (17)
#define ISO_UMSK_ISR_vfd_ardswa_int_mask                                             (0x00020000)
#define ISO_UMSK_ISR_vfd_ardswa_int(data)                                            (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_vfd_ardswa_int_src(data)                                        ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_get_vfd_ardswa_int(data)                                        ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_vfd_ardkpadda_int_shift                                         (16)
#define ISO_UMSK_ISR_vfd_ardkpadda_int_mask                                          (0x00010000)
#define ISO_UMSK_ISR_vfd_ardkpadda_int(data)                                         (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_vfd_ardkpadda_int_src(data)                                     ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_get_vfd_ardkpadda_int(data)                                     ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_vfd_ardkpada_int_shift                                          (15)
#define ISO_UMSK_ISR_vfd_ardkpada_int_mask                                           (0x00008000)
#define ISO_UMSK_ISR_vfd_ardkpada_int(data)                                          (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_vfd_ardkpada_int_src(data)                                      ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_get_vfd_ardkpada_int(data)                                      ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_vfd_wdone_int_shift                                             (14)
#define ISO_UMSK_ISR_vfd_wdone_int_mask                                              (0x00004000)
#define ISO_UMSK_ISR_vfd_wdone_int(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_vfd_wdone_int_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_get_vfd_wdone_int(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_rtc_alarm_int_shift                                             (13)
#define ISO_UMSK_ISR_rtc_alarm_int_mask                                              (0x00002000)
#define ISO_UMSK_ISR_rtc_alarm_int(data)                                             (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_rtc_alarm_int_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_get_rtc_alarm_int(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_rtc_hsec_int_shift                                              (12)
#define ISO_UMSK_ISR_rtc_hsec_int_mask                                               (0x00001000)
#define ISO_UMSK_ISR_rtc_hsec_int(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_rtc_hsec_int_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_get_rtc_hsec_int(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_ur1_to_int_shift                                                (6)
#define ISO_UMSK_ISR_ur1_to_int_mask                                                 (0x00000040)
#define ISO_UMSK_ISR_ur1_to_int(data)                                                (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_ur1_to_int_src(data)                                            ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_get_ur1_to_int(data)                                            ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_irda_int_shift                                                  (5)
#define ISO_UMSK_ISR_irda_int_mask                                                   (0x00000020)
#define ISO_UMSK_ISR_irda_int(data)                                                  (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_irda_int_src(data)                                              ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_get_irda_int(data)                                              ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_tc3_int_shift                                                   (1)
#define ISO_UMSK_ISR_tc3_int_mask                                                    (0x00000002)
#define ISO_UMSK_ISR_tc3_int(data)                                                   (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_tc3_int_src(data)                                               ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_get_tc3_int(data)                                               ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_write_data_shift                                                (0)
#define ISO_UMSK_ISR_write_data_mask                                                 (0x00000001)
#define ISO_UMSK_ISR_write_data(data)                                                (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_write_data_src(data)                                            ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_get_write_data(data)                                            ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPA                                                             0x18007008
#define ISO_UMSK_ISR_GPA_reg_addr                                                    "0xB8007008"
#define ISO_UMSK_ISR_GPA_reg                                                         0xB8007008
#define set_ISO_UMSK_ISR_GPA_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA_reg)=data)
#define get_ISO_UMSK_ISR_GPA_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPA_reg))
#define ISO_UMSK_ISR_GPA_inst_adr                                                    "0x0002"
#define ISO_UMSK_ISR_GPA_inst                                                        0x0002
#define ISO_UMSK_ISR_GPA_int19_a_shift                                               (20)
#define ISO_UMSK_ISR_GPA_int19_a_mask                                                (0x00100000)
#define ISO_UMSK_ISR_GPA_int19_a(data)                                               (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_GPA_int19_a_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPA_get_int19_a(data)                                           ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPA_int18_a_shift                                               (19)
#define ISO_UMSK_ISR_GPA_int18_a_mask                                                (0x00080000)
#define ISO_UMSK_ISR_GPA_int18_a(data)                                               (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_GPA_int18_a_src(data)                                           ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPA_get_int18_a(data)                                           ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPA_int17_a_shift                                               (18)
#define ISO_UMSK_ISR_GPA_int17_a_mask                                                (0x00040000)
#define ISO_UMSK_ISR_GPA_int17_a(data)                                               (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_GPA_int17_a_src(data)                                           ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPA_get_int17_a(data)                                           ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPA_int16_a_shift                                               (17)
#define ISO_UMSK_ISR_GPA_int16_a_mask                                                (0x00020000)
#define ISO_UMSK_ISR_GPA_int16_a(data)                                               (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_GPA_int16_a_src(data)                                           ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPA_get_int16_a(data)                                           ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPA_int15_a_shift                                               (16)
#define ISO_UMSK_ISR_GPA_int15_a_mask                                                (0x00010000)
#define ISO_UMSK_ISR_GPA_int15_a(data)                                               (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_GPA_int15_a_src(data)                                           ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPA_get_int15_a(data)                                           ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPA_int14_a_shift                                               (15)
#define ISO_UMSK_ISR_GPA_int14_a_mask                                                (0x00008000)
#define ISO_UMSK_ISR_GPA_int14_a(data)                                               (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_GPA_int14_a_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPA_get_int14_a(data)                                           ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPA_int13_a_shift                                               (14)
#define ISO_UMSK_ISR_GPA_int13_a_mask                                                (0x00004000)
#define ISO_UMSK_ISR_GPA_int13_a(data)                                               (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_GPA_int13_a_src(data)                                           ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPA_get_int13_a(data)                                           ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPA_int12_a_shift                                               (13)
#define ISO_UMSK_ISR_GPA_int12_a_mask                                                (0x00002000)
#define ISO_UMSK_ISR_GPA_int12_a(data)                                               (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_GPA_int12_a_src(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPA_get_int12_a(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPA_int11_a_shift                                               (12)
#define ISO_UMSK_ISR_GPA_int11_a_mask                                                (0x00001000)
#define ISO_UMSK_ISR_GPA_int11_a(data)                                               (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_GPA_int11_a_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPA_get_int11_a(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPA_int10_a_shift                                               (11)
#define ISO_UMSK_ISR_GPA_int10_a_mask                                                (0x00000800)
#define ISO_UMSK_ISR_GPA_int10_a(data)                                               (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_GPA_int10_a_src(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPA_get_int10_a(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPA_int9_a_shift                                                (10)
#define ISO_UMSK_ISR_GPA_int9_a_mask                                                 (0x00000400)
#define ISO_UMSK_ISR_GPA_int9_a(data)                                                (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_GPA_int9_a_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPA_get_int9_a(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPA_int8_a_shift                                                (9)
#define ISO_UMSK_ISR_GPA_int8_a_mask                                                 (0x00000200)
#define ISO_UMSK_ISR_GPA_int8_a(data)                                                (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_GPA_int8_a_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPA_get_int8_a(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPA_int7_a_shift                                                (8)
#define ISO_UMSK_ISR_GPA_int7_a_mask                                                 (0x00000100)
#define ISO_UMSK_ISR_GPA_int7_a(data)                                                (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_GPA_int7_a_src(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPA_get_int7_a(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPA_int6_a_shift                                                (7)
#define ISO_UMSK_ISR_GPA_int6_a_mask                                                 (0x00000080)
#define ISO_UMSK_ISR_GPA_int6_a(data)                                                (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_GPA_int6_a_src(data)                                            ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPA_get_int6_a(data)                                            ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPA_int5_a_shift                                                (6)
#define ISO_UMSK_ISR_GPA_int5_a_mask                                                 (0x00000040)
#define ISO_UMSK_ISR_GPA_int5_a(data)                                                (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_GPA_int5_a_src(data)                                            ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPA_get_int5_a(data)                                            ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPA_int4_a_shift                                                (5)
#define ISO_UMSK_ISR_GPA_int4_a_mask                                                 (0x00000020)
#define ISO_UMSK_ISR_GPA_int4_a(data)                                                (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_GPA_int4_a_src(data)                                            ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPA_get_int4_a(data)                                            ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPA_int3_a_shift                                                (4)
#define ISO_UMSK_ISR_GPA_int3_a_mask                                                 (0x00000010)
#define ISO_UMSK_ISR_GPA_int3_a(data)                                                (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPA_int3_a_src(data)                                            ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA_get_int3_a(data)                                            ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPA_int2_a_shift                                                (3)
#define ISO_UMSK_ISR_GPA_int2_a_mask                                                 (0x00000008)
#define ISO_UMSK_ISR_GPA_int2_a(data)                                                (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPA_int2_a_src(data)                                            ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA_get_int2_a(data)                                            ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPA_int1_a_shift                                                (2)
#define ISO_UMSK_ISR_GPA_int1_a_mask                                                 (0x00000004)
#define ISO_UMSK_ISR_GPA_int1_a(data)                                                (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPA_int1_a_src(data)                                            ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA_get_int1_a(data)                                            ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPA_int0_a_shift                                                (1)
#define ISO_UMSK_ISR_GPA_int0_a_mask                                                 (0x00000002)
#define ISO_UMSK_ISR_GPA_int0_a(data)                                                (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPA_int0_a_src(data)                                            ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA_get_int0_a(data)                                            ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPA_write_data_shift                                            (0)
#define ISO_UMSK_ISR_GPA_write_data_mask                                             (0x00000001)
#define ISO_UMSK_ISR_GPA_write_data(data)                                            (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPA_write_data_src(data)                                        ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPA_get_write_data(data)                                        ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_GPDA                                                            0x1800700C
#define ISO_UMSK_ISR_GPDA_reg_addr                                                   "0xB800700C"
#define ISO_UMSK_ISR_GPDA_reg                                                        0xB800700C
#define set_ISO_UMSK_ISR_GPDA_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA_reg)=data)
#define get_ISO_UMSK_ISR_GPDA_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_GPDA_reg))
#define ISO_UMSK_ISR_GPDA_inst_adr                                                   "0x0003"
#define ISO_UMSK_ISR_GPDA_inst                                                       0x0003
#define ISO_UMSK_ISR_GPDA_int19_da_shift                                             (20)
#define ISO_UMSK_ISR_GPDA_int19_da_mask                                              (0x00100000)
#define ISO_UMSK_ISR_GPDA_int19_da(data)                                             (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_GPDA_int19_da_src(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPDA_get_int19_da(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_GPDA_int18_da_shift                                             (19)
#define ISO_UMSK_ISR_GPDA_int18_da_mask                                              (0x00080000)
#define ISO_UMSK_ISR_GPDA_int18_da(data)                                             (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_GPDA_int18_da_src(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPDA_get_int18_da(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_GPDA_int17_da_shift                                             (18)
#define ISO_UMSK_ISR_GPDA_int17_da_mask                                              (0x00040000)
#define ISO_UMSK_ISR_GPDA_int17_da(data)                                             (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_GPDA_int17_da_src(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPDA_get_int17_da(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_GPDA_int16_da_shift                                             (17)
#define ISO_UMSK_ISR_GPDA_int16_da_mask                                              (0x00020000)
#define ISO_UMSK_ISR_GPDA_int16_da(data)                                             (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_GPDA_int16_da_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPDA_get_int16_da(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_GPDA_int15_da_shift                                             (16)
#define ISO_UMSK_ISR_GPDA_int15_da_mask                                              (0x00010000)
#define ISO_UMSK_ISR_GPDA_int15_da(data)                                             (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_GPDA_int15_da_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPDA_get_int15_da(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_GPDA_int14_da_shift                                             (15)
#define ISO_UMSK_ISR_GPDA_int14_da_mask                                              (0x00008000)
#define ISO_UMSK_ISR_GPDA_int14_da(data)                                             (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_GPDA_int14_da_src(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPDA_get_int14_da(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_GPDA_int13_da_shift                                             (14)
#define ISO_UMSK_ISR_GPDA_int13_da_mask                                              (0x00004000)
#define ISO_UMSK_ISR_GPDA_int13_da(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_GPDA_int13_da_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPDA_get_int13_da(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_GPDA_int12_da_shift                                             (13)
#define ISO_UMSK_ISR_GPDA_int12_da_mask                                              (0x00002000)
#define ISO_UMSK_ISR_GPDA_int12_da(data)                                             (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_GPDA_int12_da_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPDA_get_int12_da(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_GPDA_int11_da_shift                                             (12)
#define ISO_UMSK_ISR_GPDA_int11_da_mask                                              (0x00001000)
#define ISO_UMSK_ISR_GPDA_int11_da(data)                                             (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_GPDA_int11_da_src(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPDA_get_int11_da(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_GPDA_int10_da_shift                                             (11)
#define ISO_UMSK_ISR_GPDA_int10_da_mask                                              (0x00000800)
#define ISO_UMSK_ISR_GPDA_int10_da(data)                                             (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_GPDA_int10_da_src(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPDA_get_int10_da(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_GPDA_int9_da_shift                                              (10)
#define ISO_UMSK_ISR_GPDA_int9_da_mask                                               (0x00000400)
#define ISO_UMSK_ISR_GPDA_int9_da(data)                                              (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_GPDA_int9_da_src(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPDA_get_int9_da(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_GPDA_int8_da_shift                                              (9)
#define ISO_UMSK_ISR_GPDA_int8_da_mask                                               (0x00000200)
#define ISO_UMSK_ISR_GPDA_int8_da(data)                                              (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_GPDA_int8_da_src(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPDA_get_int8_da(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_GPDA_int7_da_shift                                              (8)
#define ISO_UMSK_ISR_GPDA_int7_da_mask                                               (0x00000100)
#define ISO_UMSK_ISR_GPDA_int7_da(data)                                              (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_GPDA_int7_da_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPDA_get_int7_da(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_GPDA_int6_da_shift                                              (7)
#define ISO_UMSK_ISR_GPDA_int6_da_mask                                               (0x00000080)
#define ISO_UMSK_ISR_GPDA_int6_da(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_GPDA_int6_da_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPDA_get_int6_da(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_GPDA_int5_da_shift                                              (6)
#define ISO_UMSK_ISR_GPDA_int5_da_mask                                               (0x00000040)
#define ISO_UMSK_ISR_GPDA_int5_da(data)                                              (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_GPDA_int5_da_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPDA_get_int5_da(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_GPDA_int4_da_shift                                              (5)
#define ISO_UMSK_ISR_GPDA_int4_da_mask                                               (0x00000020)
#define ISO_UMSK_ISR_GPDA_int4_da(data)                                              (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_GPDA_int4_da_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPDA_get_int4_da(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_GPDA_int3_da_shift                                              (4)
#define ISO_UMSK_ISR_GPDA_int3_da_mask                                               (0x00000010)
#define ISO_UMSK_ISR_GPDA_int3_da(data)                                              (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_GPDA_int3_da_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA_get_int3_da(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_GPDA_int2_da_shift                                              (3)
#define ISO_UMSK_ISR_GPDA_int2_da_mask                                               (0x00000008)
#define ISO_UMSK_ISR_GPDA_int2_da(data)                                              (0x00000008&((data)<<3))
#define ISO_UMSK_ISR_GPDA_int2_da_src(data)                                          ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA_get_int2_da(data)                                          ((0x00000008&(data))>>3)
#define ISO_UMSK_ISR_GPDA_int1_da_shift                                              (2)
#define ISO_UMSK_ISR_GPDA_int1_da_mask                                               (0x00000004)
#define ISO_UMSK_ISR_GPDA_int1_da(data)                                              (0x00000004&((data)<<2))
#define ISO_UMSK_ISR_GPDA_int1_da_src(data)                                          ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA_get_int1_da(data)                                          ((0x00000004&(data))>>2)
#define ISO_UMSK_ISR_GPDA_int0_da_shift                                              (1)
#define ISO_UMSK_ISR_GPDA_int0_da_mask                                               (0x00000002)
#define ISO_UMSK_ISR_GPDA_int0_da(data)                                              (0x00000002&((data)<<1))
#define ISO_UMSK_ISR_GPDA_int0_da_src(data)                                          ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA_get_int0_da(data)                                          ((0x00000002&(data))>>1)
#define ISO_UMSK_ISR_GPDA_write_data_shift                                           (0)
#define ISO_UMSK_ISR_GPDA_write_data_mask                                            (0x00000001)
#define ISO_UMSK_ISR_GPDA_write_data(data)                                           (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_GPDA_write_data_src(data)                                       ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_GPDA_get_write_data(data)                                       ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADAH                                                          0x18007010
#define ISO_UMSK_ISR_KPADAH_reg_addr                                                 "0xB8007010"
#define ISO_UMSK_ISR_KPADAH_reg                                                      0xB8007010
#define set_ISO_UMSK_ISR_KPADAH_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAH_reg)=data)
#define get_ISO_UMSK_ISR_KPADAH_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAH_reg))
#define ISO_UMSK_ISR_KPADAH_inst_adr                                                 "0x0004"
#define ISO_UMSK_ISR_KPADAH_inst                                                     0x0004
#define ISO_UMSK_ISR_KPADAH_int47_shift                                              (23)
#define ISO_UMSK_ISR_KPADAH_int47_mask                                               (0x00800000)
#define ISO_UMSK_ISR_KPADAH_int47(data)                                              (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADAH_int47_src(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAH_get_int47(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAH_int46_shift                                              (22)
#define ISO_UMSK_ISR_KPADAH_int46_mask                                               (0x00400000)
#define ISO_UMSK_ISR_KPADAH_int46(data)                                              (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADAH_int46_src(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAH_get_int46(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAH_int45_shift                                              (21)
#define ISO_UMSK_ISR_KPADAH_int45_mask                                               (0x00200000)
#define ISO_UMSK_ISR_KPADAH_int45(data)                                              (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADAH_int45_src(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAH_get_int45(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAH_int44_shift                                              (20)
#define ISO_UMSK_ISR_KPADAH_int44_mask                                               (0x00100000)
#define ISO_UMSK_ISR_KPADAH_int44(data)                                              (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADAH_int44_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAH_get_int44(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAH_int43_shift                                              (19)
#define ISO_UMSK_ISR_KPADAH_int43_mask                                               (0x00080000)
#define ISO_UMSK_ISR_KPADAH_int43(data)                                              (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADAH_int43_src(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAH_get_int43(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAH_int42_shift                                              (18)
#define ISO_UMSK_ISR_KPADAH_int42_mask                                               (0x00040000)
#define ISO_UMSK_ISR_KPADAH_int42(data)                                              (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADAH_int42_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAH_get_int42(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAH_int41_shift                                              (17)
#define ISO_UMSK_ISR_KPADAH_int41_mask                                               (0x00020000)
#define ISO_UMSK_ISR_KPADAH_int41(data)                                              (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADAH_int41_src(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAH_get_int41(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAH_int40_shift                                              (16)
#define ISO_UMSK_ISR_KPADAH_int40_mask                                               (0x00010000)
#define ISO_UMSK_ISR_KPADAH_int40(data)                                              (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADAH_int40_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAH_get_int40(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAH_int39_shift                                              (15)
#define ISO_UMSK_ISR_KPADAH_int39_mask                                               (0x00008000)
#define ISO_UMSK_ISR_KPADAH_int39(data)                                              (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADAH_int39_src(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAH_get_int39(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAH_int38_shift                                              (14)
#define ISO_UMSK_ISR_KPADAH_int38_mask                                               (0x00004000)
#define ISO_UMSK_ISR_KPADAH_int38(data)                                              (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADAH_int38_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAH_get_int38(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAH_int37_shift                                              (13)
#define ISO_UMSK_ISR_KPADAH_int37_mask                                               (0x00002000)
#define ISO_UMSK_ISR_KPADAH_int37(data)                                              (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADAH_int37_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAH_get_int37(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAH_int36_shift                                              (12)
#define ISO_UMSK_ISR_KPADAH_int36_mask                                               (0x00001000)
#define ISO_UMSK_ISR_KPADAH_int36(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADAH_int36_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAH_get_int36(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAH_int35_shift                                              (11)
#define ISO_UMSK_ISR_KPADAH_int35_mask                                               (0x00000800)
#define ISO_UMSK_ISR_KPADAH_int35(data)                                              (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADAH_int35_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAH_get_int35(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAH_int34_shift                                              (10)
#define ISO_UMSK_ISR_KPADAH_int34_mask                                               (0x00000400)
#define ISO_UMSK_ISR_KPADAH_int34(data)                                              (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADAH_int34_src(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAH_get_int34(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAH_int33_shift                                              (9)
#define ISO_UMSK_ISR_KPADAH_int33_mask                                               (0x00000200)
#define ISO_UMSK_ISR_KPADAH_int33(data)                                              (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADAH_int33_src(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAH_get_int33(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAH_int32_shift                                              (8)
#define ISO_UMSK_ISR_KPADAH_int32_mask                                               (0x00000100)
#define ISO_UMSK_ISR_KPADAH_int32(data)                                              (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADAH_int32_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAH_get_int32(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAH_int31_shift                                              (7)
#define ISO_UMSK_ISR_KPADAH_int31_mask                                               (0x00000080)
#define ISO_UMSK_ISR_KPADAH_int31(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADAH_int31_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAH_get_int31(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAH_int30_shift                                              (6)
#define ISO_UMSK_ISR_KPADAH_int30_mask                                               (0x00000040)
#define ISO_UMSK_ISR_KPADAH_int30(data)                                              (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADAH_int30_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAH_get_int30(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAH_int29_shift                                              (5)
#define ISO_UMSK_ISR_KPADAH_int29_mask                                               (0x00000020)
#define ISO_UMSK_ISR_KPADAH_int29(data)                                              (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADAH_int29_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAH_get_int29(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAH_int28_shift                                              (4)
#define ISO_UMSK_ISR_KPADAH_int28_mask                                               (0x00000010)
#define ISO_UMSK_ISR_KPADAH_int28(data)                                              (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADAH_int28_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAH_get_int28(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAH_write_data_shift                                         (0)
#define ISO_UMSK_ISR_KPADAH_write_data_mask                                          (0x00000001)
#define ISO_UMSK_ISR_KPADAH_write_data(data)                                         (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADAH_write_data_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADAH_get_write_data(data)                                     ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADAL                                                          0x18007014
#define ISO_UMSK_ISR_KPADAL_reg_addr                                                 "0xB8007014"
#define ISO_UMSK_ISR_KPADAL_reg                                                      0xB8007014
#define set_ISO_UMSK_ISR_KPADAL_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAL_reg)=data)
#define get_ISO_UMSK_ISR_KPADAL_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADAL_reg))
#define ISO_UMSK_ISR_KPADAL_inst_adr                                                 "0x0005"
#define ISO_UMSK_ISR_KPADAL_inst                                                     0x0005
#define ISO_UMSK_ISR_KPADAL_int27_shift                                              (31)
#define ISO_UMSK_ISR_KPADAL_int27_mask                                               (0x80000000)
#define ISO_UMSK_ISR_KPADAL_int27(data)                                              (0x80000000&((data)<<31))
#define ISO_UMSK_ISR_KPADAL_int27_src(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADAL_get_int27(data)                                          ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADAL_int26_shift                                              (30)
#define ISO_UMSK_ISR_KPADAL_int26_mask                                               (0x40000000)
#define ISO_UMSK_ISR_KPADAL_int26(data)                                              (0x40000000&((data)<<30))
#define ISO_UMSK_ISR_KPADAL_int26_src(data)                                          ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADAL_get_int26(data)                                          ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADAL_int25_shift                                              (29)
#define ISO_UMSK_ISR_KPADAL_int25_mask                                               (0x20000000)
#define ISO_UMSK_ISR_KPADAL_int25(data)                                              (0x20000000&((data)<<29))
#define ISO_UMSK_ISR_KPADAL_int25_src(data)                                          ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADAL_get_int25(data)                                          ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADAL_int24_shift                                              (28)
#define ISO_UMSK_ISR_KPADAL_int24_mask                                               (0x10000000)
#define ISO_UMSK_ISR_KPADAL_int24(data)                                              (0x10000000&((data)<<28))
#define ISO_UMSK_ISR_KPADAL_int24_src(data)                                          ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADAL_get_int24(data)                                          ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADAL_int23_shift                                              (27)
#define ISO_UMSK_ISR_KPADAL_int23_mask                                               (0x08000000)
#define ISO_UMSK_ISR_KPADAL_int23(data)                                              (0x08000000&((data)<<27))
#define ISO_UMSK_ISR_KPADAL_int23_src(data)                                          ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADAL_get_int23(data)                                          ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADAL_int22_shift                                              (26)
#define ISO_UMSK_ISR_KPADAL_int22_mask                                               (0x04000000)
#define ISO_UMSK_ISR_KPADAL_int22(data)                                              (0x04000000&((data)<<26))
#define ISO_UMSK_ISR_KPADAL_int22_src(data)                                          ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADAL_get_int22(data)                                          ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADAL_int21_shift                                              (25)
#define ISO_UMSK_ISR_KPADAL_int21_mask                                               (0x02000000)
#define ISO_UMSK_ISR_KPADAL_int21(data)                                              (0x02000000&((data)<<25))
#define ISO_UMSK_ISR_KPADAL_int21_src(data)                                          ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADAL_get_int21(data)                                          ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADAL_int20_shift                                              (24)
#define ISO_UMSK_ISR_KPADAL_int20_mask                                               (0x01000000)
#define ISO_UMSK_ISR_KPADAL_int20(data)                                              (0x01000000&((data)<<24))
#define ISO_UMSK_ISR_KPADAL_int20_src(data)                                          ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADAL_get_int20(data)                                          ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADAL_int19_shift                                              (23)
#define ISO_UMSK_ISR_KPADAL_int19_mask                                               (0x00800000)
#define ISO_UMSK_ISR_KPADAL_int19(data)                                              (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADAL_int19_src(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAL_get_int19(data)                                          ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADAL_int18_shift                                              (22)
#define ISO_UMSK_ISR_KPADAL_int18_mask                                               (0x00400000)
#define ISO_UMSK_ISR_KPADAL_int18(data)                                              (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADAL_int18_src(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAL_get_int18(data)                                          ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADAL_int17_shift                                              (21)
#define ISO_UMSK_ISR_KPADAL_int17_mask                                               (0x00200000)
#define ISO_UMSK_ISR_KPADAL_int17(data)                                              (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADAL_int17_src(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAL_get_int17(data)                                          ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADAL_int16_shift                                              (20)
#define ISO_UMSK_ISR_KPADAL_int16_mask                                               (0x00100000)
#define ISO_UMSK_ISR_KPADAL_int16(data)                                              (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADAL_int16_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAL_get_int16(data)                                          ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADAL_int15_shift                                              (19)
#define ISO_UMSK_ISR_KPADAL_int15_mask                                               (0x00080000)
#define ISO_UMSK_ISR_KPADAL_int15(data)                                              (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADAL_int15_src(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAL_get_int15(data)                                          ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADAL_int14_shift                                              (18)
#define ISO_UMSK_ISR_KPADAL_int14_mask                                               (0x00040000)
#define ISO_UMSK_ISR_KPADAL_int14(data)                                              (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADAL_int14_src(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAL_get_int14(data)                                          ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADAL_int13_shift                                              (17)
#define ISO_UMSK_ISR_KPADAL_int13_mask                                               (0x00020000)
#define ISO_UMSK_ISR_KPADAL_int13(data)                                              (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADAL_int13_src(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAL_get_int13(data)                                          ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADAL_int12_shift                                              (16)
#define ISO_UMSK_ISR_KPADAL_int12_mask                                               (0x00010000)
#define ISO_UMSK_ISR_KPADAL_int12(data)                                              (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADAL_int12_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAL_get_int12(data)                                          ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADAL_int11_shift                                              (15)
#define ISO_UMSK_ISR_KPADAL_int11_mask                                               (0x00008000)
#define ISO_UMSK_ISR_KPADAL_int11(data)                                              (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADAL_int11_src(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAL_get_int11(data)                                          ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADAL_int10_shift                                              (14)
#define ISO_UMSK_ISR_KPADAL_int10_mask                                               (0x00004000)
#define ISO_UMSK_ISR_KPADAL_int10(data)                                              (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADAL_int10_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAL_get_int10(data)                                          ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADAL_int9_shift                                               (13)
#define ISO_UMSK_ISR_KPADAL_int9_mask                                                (0x00002000)
#define ISO_UMSK_ISR_KPADAL_int9(data)                                               (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADAL_int9_src(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAL_get_int9(data)                                           ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADAL_int8_shift                                               (12)
#define ISO_UMSK_ISR_KPADAL_int8_mask                                                (0x00001000)
#define ISO_UMSK_ISR_KPADAL_int8(data)                                               (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADAL_int8_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAL_get_int8(data)                                           ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADAL_int7_shift                                               (11)
#define ISO_UMSK_ISR_KPADAL_int7_mask                                                (0x00000800)
#define ISO_UMSK_ISR_KPADAL_int7(data)                                               (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADAL_int7_src(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAL_get_int7(data)                                           ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADAL_int6_shift                                               (10)
#define ISO_UMSK_ISR_KPADAL_int6_mask                                                (0x00000400)
#define ISO_UMSK_ISR_KPADAL_int6(data)                                               (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADAL_int6_src(data)                                           ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAL_get_int6(data)                                           ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADAL_int5_shift                                               (9)
#define ISO_UMSK_ISR_KPADAL_int5_mask                                                (0x00000200)
#define ISO_UMSK_ISR_KPADAL_int5(data)                                               (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADAL_int5_src(data)                                           ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAL_get_int5(data)                                           ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADAL_int4_shift                                               (8)
#define ISO_UMSK_ISR_KPADAL_int4_mask                                                (0x00000100)
#define ISO_UMSK_ISR_KPADAL_int4(data)                                               (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADAL_int4_src(data)                                           ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAL_get_int4(data)                                           ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADAL_int3_shift                                               (7)
#define ISO_UMSK_ISR_KPADAL_int3_mask                                                (0x00000080)
#define ISO_UMSK_ISR_KPADAL_int3(data)                                               (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADAL_int3_src(data)                                           ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAL_get_int3(data)                                           ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADAL_int2_shift                                               (6)
#define ISO_UMSK_ISR_KPADAL_int2_mask                                                (0x00000040)
#define ISO_UMSK_ISR_KPADAL_int2(data)                                               (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADAL_int2_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAL_get_int2(data)                                           ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADAL_int1_shift                                               (5)
#define ISO_UMSK_ISR_KPADAL_int1_mask                                                (0x00000020)
#define ISO_UMSK_ISR_KPADAL_int1(data)                                               (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADAL_int1_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAL_get_int1(data)                                           ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADAL_int0_shift                                               (4)
#define ISO_UMSK_ISR_KPADAL_int0_mask                                                (0x00000010)
#define ISO_UMSK_ISR_KPADAL_int0(data)                                               (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADAL_int0_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAL_get_int0(data)                                           ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADAL_write_data_shift                                         (0)
#define ISO_UMSK_ISR_KPADAL_write_data_mask                                          (0x00000001)
#define ISO_UMSK_ISR_KPADAL_write_data(data)                                         (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADAL_write_data_src(data)                                     ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADAL_get_write_data(data)                                     ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADDAH                                                         0x18007018
#define ISO_UMSK_ISR_KPADDAH_reg_addr                                                "0xB8007018"
#define ISO_UMSK_ISR_KPADDAH_reg                                                     0xB8007018
#define set_ISO_UMSK_ISR_KPADDAH_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAH_reg)=data)
#define get_ISO_UMSK_ISR_KPADDAH_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAH_reg))
#define ISO_UMSK_ISR_KPADDAH_inst_adr                                                "0x0006"
#define ISO_UMSK_ISR_KPADDAH_inst                                                    0x0006
#define ISO_UMSK_ISR_KPADDAH_int47_shift                                             (23)
#define ISO_UMSK_ISR_KPADDAH_int47_mask                                              (0x00800000)
#define ISO_UMSK_ISR_KPADDAH_int47(data)                                             (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADDAH_int47_src(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAH_get_int47(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAH_int46_shift                                             (22)
#define ISO_UMSK_ISR_KPADDAH_int46_mask                                              (0x00400000)
#define ISO_UMSK_ISR_KPADDAH_int46(data)                                             (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADDAH_int46_src(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAH_get_int46(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAH_int45_shift                                             (21)
#define ISO_UMSK_ISR_KPADDAH_int45_mask                                              (0x00200000)
#define ISO_UMSK_ISR_KPADDAH_int45(data)                                             (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADDAH_int45_src(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAH_get_int45(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAH_int44_shift                                             (20)
#define ISO_UMSK_ISR_KPADDAH_int44_mask                                              (0x00100000)
#define ISO_UMSK_ISR_KPADDAH_int44(data)                                             (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADDAH_int44_src(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAH_get_int44(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAH_int43_shift                                             (19)
#define ISO_UMSK_ISR_KPADDAH_int43_mask                                              (0x00080000)
#define ISO_UMSK_ISR_KPADDAH_int43(data)                                             (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADDAH_int43_src(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAH_get_int43(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAH_int42_shift                                             (18)
#define ISO_UMSK_ISR_KPADDAH_int42_mask                                              (0x00040000)
#define ISO_UMSK_ISR_KPADDAH_int42(data)                                             (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADDAH_int42_src(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAH_get_int42(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAH_int41_shift                                             (17)
#define ISO_UMSK_ISR_KPADDAH_int41_mask                                              (0x00020000)
#define ISO_UMSK_ISR_KPADDAH_int41(data)                                             (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADDAH_int41_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAH_get_int41(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAH_int40_shift                                             (16)
#define ISO_UMSK_ISR_KPADDAH_int40_mask                                              (0x00010000)
#define ISO_UMSK_ISR_KPADDAH_int40(data)                                             (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADDAH_int40_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAH_get_int40(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAH_int39_shift                                             (15)
#define ISO_UMSK_ISR_KPADDAH_int39_mask                                              (0x00008000)
#define ISO_UMSK_ISR_KPADDAH_int39(data)                                             (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADDAH_int39_src(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAH_get_int39(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAH_int38_shift                                             (14)
#define ISO_UMSK_ISR_KPADDAH_int38_mask                                              (0x00004000)
#define ISO_UMSK_ISR_KPADDAH_int38(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADDAH_int38_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAH_get_int38(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAH_int37_shift                                             (13)
#define ISO_UMSK_ISR_KPADDAH_int37_mask                                              (0x00002000)
#define ISO_UMSK_ISR_KPADDAH_int37(data)                                             (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADDAH_int37_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAH_get_int37(data)                                         ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAH_int36_shift                                             (12)
#define ISO_UMSK_ISR_KPADDAH_int36_mask                                              (0x00001000)
#define ISO_UMSK_ISR_KPADDAH_int36(data)                                             (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADDAH_int36_src(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAH_get_int36(data)                                         ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAH_int35_shift                                             (11)
#define ISO_UMSK_ISR_KPADDAH_int35_mask                                              (0x00000800)
#define ISO_UMSK_ISR_KPADDAH_int35(data)                                             (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADDAH_int35_src(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAH_get_int35(data)                                         ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAH_int34_shift                                             (10)
#define ISO_UMSK_ISR_KPADDAH_int34_mask                                              (0x00000400)
#define ISO_UMSK_ISR_KPADDAH_int34(data)                                             (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADDAH_int34_src(data)                                         ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAH_get_int34(data)                                         ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAH_int33_shift                                             (9)
#define ISO_UMSK_ISR_KPADDAH_int33_mask                                              (0x00000200)
#define ISO_UMSK_ISR_KPADDAH_int33(data)                                             (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADDAH_int33_src(data)                                         ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAH_get_int33(data)                                         ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAH_int32_shift                                             (8)
#define ISO_UMSK_ISR_KPADDAH_int32_mask                                              (0x00000100)
#define ISO_UMSK_ISR_KPADDAH_int32(data)                                             (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADDAH_int32_src(data)                                         ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAH_get_int32(data)                                         ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAH_int31_shift                                             (7)
#define ISO_UMSK_ISR_KPADDAH_int31_mask                                              (0x00000080)
#define ISO_UMSK_ISR_KPADDAH_int31(data)                                             (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADDAH_int31_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAH_get_int31(data)                                         ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAH_int30_shift                                             (6)
#define ISO_UMSK_ISR_KPADDAH_int30_mask                                              (0x00000040)
#define ISO_UMSK_ISR_KPADDAH_int30(data)                                             (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADDAH_int30_src(data)                                         ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAH_get_int30(data)                                         ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAH_int29_shift                                             (5)
#define ISO_UMSK_ISR_KPADDAH_int29_mask                                              (0x00000020)
#define ISO_UMSK_ISR_KPADDAH_int29(data)                                             (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADDAH_int29_src(data)                                         ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAH_get_int29(data)                                         ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAH_int28_shift                                             (4)
#define ISO_UMSK_ISR_KPADDAH_int28_mask                                              (0x00000010)
#define ISO_UMSK_ISR_KPADDAH_int28(data)                                             (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADDAH_int28_src(data)                                         ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAH_get_int28(data)                                         ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAH_write_data_shift                                        (0)
#define ISO_UMSK_ISR_KPADDAH_write_data_mask                                         (0x00000001)
#define ISO_UMSK_ISR_KPADDAH_write_data(data)                                        (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADDAH_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADDAH_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_KPADDAL                                                         0x1800701C
#define ISO_UMSK_ISR_KPADDAL_reg_addr                                                "0xB800701C"
#define ISO_UMSK_ISR_KPADDAL_reg                                                     0xB800701C
#define set_ISO_UMSK_ISR_KPADDAL_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAL_reg)=data)
#define get_ISO_UMSK_ISR_KPADDAL_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_KPADDAL_reg))
#define ISO_UMSK_ISR_KPADDAL_inst_adr                                                "0x0007"
#define ISO_UMSK_ISR_KPADDAL_inst                                                    0x0007
#define ISO_UMSK_ISR_KPADDAL_int27_shift                                             (31)
#define ISO_UMSK_ISR_KPADDAL_int27_mask                                              (0x80000000)
#define ISO_UMSK_ISR_KPADDAL_int27(data)                                             (0x80000000&((data)<<31))
#define ISO_UMSK_ISR_KPADDAL_int27_src(data)                                         ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADDAL_get_int27(data)                                         ((0x80000000&(data))>>31)
#define ISO_UMSK_ISR_KPADDAL_int26_shift                                             (30)
#define ISO_UMSK_ISR_KPADDAL_int26_mask                                              (0x40000000)
#define ISO_UMSK_ISR_KPADDAL_int26(data)                                             (0x40000000&((data)<<30))
#define ISO_UMSK_ISR_KPADDAL_int26_src(data)                                         ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADDAL_get_int26(data)                                         ((0x40000000&(data))>>30)
#define ISO_UMSK_ISR_KPADDAL_int25_shift                                             (29)
#define ISO_UMSK_ISR_KPADDAL_int25_mask                                              (0x20000000)
#define ISO_UMSK_ISR_KPADDAL_int25(data)                                             (0x20000000&((data)<<29))
#define ISO_UMSK_ISR_KPADDAL_int25_src(data)                                         ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADDAL_get_int25(data)                                         ((0x20000000&(data))>>29)
#define ISO_UMSK_ISR_KPADDAL_int24_shift                                             (28)
#define ISO_UMSK_ISR_KPADDAL_int24_mask                                              (0x10000000)
#define ISO_UMSK_ISR_KPADDAL_int24(data)                                             (0x10000000&((data)<<28))
#define ISO_UMSK_ISR_KPADDAL_int24_src(data)                                         ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADDAL_get_int24(data)                                         ((0x10000000&(data))>>28)
#define ISO_UMSK_ISR_KPADDAL_int23_shift                                             (27)
#define ISO_UMSK_ISR_KPADDAL_int23_mask                                              (0x08000000)
#define ISO_UMSK_ISR_KPADDAL_int23(data)                                             (0x08000000&((data)<<27))
#define ISO_UMSK_ISR_KPADDAL_int23_src(data)                                         ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADDAL_get_int23(data)                                         ((0x08000000&(data))>>27)
#define ISO_UMSK_ISR_KPADDAL_int22_shift                                             (26)
#define ISO_UMSK_ISR_KPADDAL_int22_mask                                              (0x04000000)
#define ISO_UMSK_ISR_KPADDAL_int22(data)                                             (0x04000000&((data)<<26))
#define ISO_UMSK_ISR_KPADDAL_int22_src(data)                                         ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADDAL_get_int22(data)                                         ((0x04000000&(data))>>26)
#define ISO_UMSK_ISR_KPADDAL_int21_shift                                             (25)
#define ISO_UMSK_ISR_KPADDAL_int21_mask                                              (0x02000000)
#define ISO_UMSK_ISR_KPADDAL_int21(data)                                             (0x02000000&((data)<<25))
#define ISO_UMSK_ISR_KPADDAL_int21_src(data)                                         ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADDAL_get_int21(data)                                         ((0x02000000&(data))>>25)
#define ISO_UMSK_ISR_KPADDAL_int20_shift                                             (24)
#define ISO_UMSK_ISR_KPADDAL_int20_mask                                              (0x01000000)
#define ISO_UMSK_ISR_KPADDAL_int20(data)                                             (0x01000000&((data)<<24))
#define ISO_UMSK_ISR_KPADDAL_int20_src(data)                                         ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADDAL_get_int20(data)                                         ((0x01000000&(data))>>24)
#define ISO_UMSK_ISR_KPADDAL_int19_shift                                             (23)
#define ISO_UMSK_ISR_KPADDAL_int19_mask                                              (0x00800000)
#define ISO_UMSK_ISR_KPADDAL_int19(data)                                             (0x00800000&((data)<<23))
#define ISO_UMSK_ISR_KPADDAL_int19_src(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAL_get_int19(data)                                         ((0x00800000&(data))>>23)
#define ISO_UMSK_ISR_KPADDAL_int18_shift                                             (22)
#define ISO_UMSK_ISR_KPADDAL_int18_mask                                              (0x00400000)
#define ISO_UMSK_ISR_KPADDAL_int18(data)                                             (0x00400000&((data)<<22))
#define ISO_UMSK_ISR_KPADDAL_int18_src(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAL_get_int18(data)                                         ((0x00400000&(data))>>22)
#define ISO_UMSK_ISR_KPADDAL_int17_shift                                             (21)
#define ISO_UMSK_ISR_KPADDAL_int17_mask                                              (0x00200000)
#define ISO_UMSK_ISR_KPADDAL_int17(data)                                             (0x00200000&((data)<<21))
#define ISO_UMSK_ISR_KPADDAL_int17_src(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAL_get_int17(data)                                         ((0x00200000&(data))>>21)
#define ISO_UMSK_ISR_KPADDAL_int16_shift                                             (20)
#define ISO_UMSK_ISR_KPADDAL_int16_mask                                              (0x00100000)
#define ISO_UMSK_ISR_KPADDAL_int16(data)                                             (0x00100000&((data)<<20))
#define ISO_UMSK_ISR_KPADDAL_int16_src(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAL_get_int16(data)                                         ((0x00100000&(data))>>20)
#define ISO_UMSK_ISR_KPADDAL_int15_shift                                             (19)
#define ISO_UMSK_ISR_KPADDAL_int15_mask                                              (0x00080000)
#define ISO_UMSK_ISR_KPADDAL_int15(data)                                             (0x00080000&((data)<<19))
#define ISO_UMSK_ISR_KPADDAL_int15_src(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAL_get_int15(data)                                         ((0x00080000&(data))>>19)
#define ISO_UMSK_ISR_KPADDAL_int14_shift                                             (18)
#define ISO_UMSK_ISR_KPADDAL_int14_mask                                              (0x00040000)
#define ISO_UMSK_ISR_KPADDAL_int14(data)                                             (0x00040000&((data)<<18))
#define ISO_UMSK_ISR_KPADDAL_int14_src(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAL_get_int14(data)                                         ((0x00040000&(data))>>18)
#define ISO_UMSK_ISR_KPADDAL_int13_shift                                             (17)
#define ISO_UMSK_ISR_KPADDAL_int13_mask                                              (0x00020000)
#define ISO_UMSK_ISR_KPADDAL_int13(data)                                             (0x00020000&((data)<<17))
#define ISO_UMSK_ISR_KPADDAL_int13_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAL_get_int13(data)                                         ((0x00020000&(data))>>17)
#define ISO_UMSK_ISR_KPADDAL_int12_shift                                             (16)
#define ISO_UMSK_ISR_KPADDAL_int12_mask                                              (0x00010000)
#define ISO_UMSK_ISR_KPADDAL_int12(data)                                             (0x00010000&((data)<<16))
#define ISO_UMSK_ISR_KPADDAL_int12_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAL_get_int12(data)                                         ((0x00010000&(data))>>16)
#define ISO_UMSK_ISR_KPADDAL_int11_shift                                             (15)
#define ISO_UMSK_ISR_KPADDAL_int11_mask                                              (0x00008000)
#define ISO_UMSK_ISR_KPADDAL_int11(data)                                             (0x00008000&((data)<<15))
#define ISO_UMSK_ISR_KPADDAL_int11_src(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAL_get_int11(data)                                         ((0x00008000&(data))>>15)
#define ISO_UMSK_ISR_KPADDAL_int10_shift                                             (14)
#define ISO_UMSK_ISR_KPADDAL_int10_mask                                              (0x00004000)
#define ISO_UMSK_ISR_KPADDAL_int10(data)                                             (0x00004000&((data)<<14))
#define ISO_UMSK_ISR_KPADDAL_int10_src(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAL_get_int10(data)                                         ((0x00004000&(data))>>14)
#define ISO_UMSK_ISR_KPADDAL_int9_shift                                              (13)
#define ISO_UMSK_ISR_KPADDAL_int9_mask                                               (0x00002000)
#define ISO_UMSK_ISR_KPADDAL_int9(data)                                              (0x00002000&((data)<<13))
#define ISO_UMSK_ISR_KPADDAL_int9_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAL_get_int9(data)                                          ((0x00002000&(data))>>13)
#define ISO_UMSK_ISR_KPADDAL_int8_shift                                              (12)
#define ISO_UMSK_ISR_KPADDAL_int8_mask                                               (0x00001000)
#define ISO_UMSK_ISR_KPADDAL_int8(data)                                              (0x00001000&((data)<<12))
#define ISO_UMSK_ISR_KPADDAL_int8_src(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAL_get_int8(data)                                          ((0x00001000&(data))>>12)
#define ISO_UMSK_ISR_KPADDAL_int7_shift                                              (11)
#define ISO_UMSK_ISR_KPADDAL_int7_mask                                               (0x00000800)
#define ISO_UMSK_ISR_KPADDAL_int7(data)                                              (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_KPADDAL_int7_src(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAL_get_int7(data)                                          ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_KPADDAL_int6_shift                                              (10)
#define ISO_UMSK_ISR_KPADDAL_int6_mask                                               (0x00000400)
#define ISO_UMSK_ISR_KPADDAL_int6(data)                                              (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_KPADDAL_int6_src(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAL_get_int6(data)                                          ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_KPADDAL_int5_shift                                              (9)
#define ISO_UMSK_ISR_KPADDAL_int5_mask                                               (0x00000200)
#define ISO_UMSK_ISR_KPADDAL_int5(data)                                              (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_KPADDAL_int5_src(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAL_get_int5(data)                                          ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_KPADDAL_int4_shift                                              (8)
#define ISO_UMSK_ISR_KPADDAL_int4_mask                                               (0x00000100)
#define ISO_UMSK_ISR_KPADDAL_int4(data)                                              (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_KPADDAL_int4_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAL_get_int4(data)                                          ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_KPADDAL_int3_shift                                              (7)
#define ISO_UMSK_ISR_KPADDAL_int3_mask                                               (0x00000080)
#define ISO_UMSK_ISR_KPADDAL_int3(data)                                              (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_KPADDAL_int3_src(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAL_get_int3(data)                                          ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_KPADDAL_int2_shift                                              (6)
#define ISO_UMSK_ISR_KPADDAL_int2_mask                                               (0x00000040)
#define ISO_UMSK_ISR_KPADDAL_int2(data)                                              (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_KPADDAL_int2_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAL_get_int2(data)                                          ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_KPADDAL_int1_shift                                              (5)
#define ISO_UMSK_ISR_KPADDAL_int1_mask                                               (0x00000020)
#define ISO_UMSK_ISR_KPADDAL_int1(data)                                              (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_KPADDAL_int1_src(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAL_get_int1(data)                                          ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_KPADDAL_int0_shift                                              (4)
#define ISO_UMSK_ISR_KPADDAL_int0_mask                                               (0x00000010)
#define ISO_UMSK_ISR_KPADDAL_int0(data)                                              (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_KPADDAL_int0_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAL_get_int0(data)                                          ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_KPADDAL_write_data_shift                                        (0)
#define ISO_UMSK_ISR_KPADDAL_write_data_mask                                         (0x00000001)
#define ISO_UMSK_ISR_KPADDAL_write_data(data)                                        (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_KPADDAL_write_data_src(data)                                    ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_KPADDAL_get_write_data(data)                                    ((0x00000001&(data))>>0)


#define ISO_UMSK_ISR_SW                                                              0x18007020
#define ISO_UMSK_ISR_SW_reg_addr                                                     "0xB8007020"
#define ISO_UMSK_ISR_SW_reg                                                          0xB8007020
#define set_ISO_UMSK_ISR_SW_reg(data)   (*((volatile unsigned int*) ISO_UMSK_ISR_SW_reg)=data)
#define get_ISO_UMSK_ISR_SW_reg   (*((volatile unsigned int*) ISO_UMSK_ISR_SW_reg))
#define ISO_UMSK_ISR_SW_inst_adr                                                     "0x0008"
#define ISO_UMSK_ISR_SW_inst                                                         0x0008
#define ISO_UMSK_ISR_SW_da_int3_shift                                                (11)
#define ISO_UMSK_ISR_SW_da_int3_mask                                                 (0x00000800)
#define ISO_UMSK_ISR_SW_da_int3(data)                                                (0x00000800&((data)<<11))
#define ISO_UMSK_ISR_SW_da_int3_src(data)                                            ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_SW_get_da_int3(data)                                            ((0x00000800&(data))>>11)
#define ISO_UMSK_ISR_SW_da_int2_shift                                                (10)
#define ISO_UMSK_ISR_SW_da_int2_mask                                                 (0x00000400)
#define ISO_UMSK_ISR_SW_da_int2(data)                                                (0x00000400&((data)<<10))
#define ISO_UMSK_ISR_SW_da_int2_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_SW_get_da_int2(data)                                            ((0x00000400&(data))>>10)
#define ISO_UMSK_ISR_SW_da_int1_shift                                                (9)
#define ISO_UMSK_ISR_SW_da_int1_mask                                                 (0x00000200)
#define ISO_UMSK_ISR_SW_da_int1(data)                                                (0x00000200&((data)<<9))
#define ISO_UMSK_ISR_SW_da_int1_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_SW_get_da_int1(data)                                            ((0x00000200&(data))>>9)
#define ISO_UMSK_ISR_SW_da_int0_shift                                                (8)
#define ISO_UMSK_ISR_SW_da_int0_mask                                                 (0x00000100)
#define ISO_UMSK_ISR_SW_da_int0(data)                                                (0x00000100&((data)<<8))
#define ISO_UMSK_ISR_SW_da_int0_src(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_SW_get_da_int0(data)                                            ((0x00000100&(data))>>8)
#define ISO_UMSK_ISR_SW_a_int3_shift                                                 (7)
#define ISO_UMSK_ISR_SW_a_int3_mask                                                  (0x00000080)
#define ISO_UMSK_ISR_SW_a_int3(data)                                                 (0x00000080&((data)<<7))
#define ISO_UMSK_ISR_SW_a_int3_src(data)                                             ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_SW_get_a_int3(data)                                             ((0x00000080&(data))>>7)
#define ISO_UMSK_ISR_SW_a_int2_shift                                                 (6)
#define ISO_UMSK_ISR_SW_a_int2_mask                                                  (0x00000040)
#define ISO_UMSK_ISR_SW_a_int2(data)                                                 (0x00000040&((data)<<6))
#define ISO_UMSK_ISR_SW_a_int2_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_SW_get_a_int2(data)                                             ((0x00000040&(data))>>6)
#define ISO_UMSK_ISR_SW_a_int1_shift                                                 (5)
#define ISO_UMSK_ISR_SW_a_int1_mask                                                  (0x00000020)
#define ISO_UMSK_ISR_SW_a_int1(data)                                                 (0x00000020&((data)<<5))
#define ISO_UMSK_ISR_SW_a_int1_src(data)                                             ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_SW_get_a_int1(data)                                             ((0x00000020&(data))>>5)
#define ISO_UMSK_ISR_SW_a_int0_shift                                                 (4)
#define ISO_UMSK_ISR_SW_a_int0_mask                                                  (0x00000010)
#define ISO_UMSK_ISR_SW_a_int0(data)                                                 (0x00000010&((data)<<4))
#define ISO_UMSK_ISR_SW_a_int0_src(data)                                             ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_SW_get_a_int0(data)                                             ((0x00000010&(data))>>4)
#define ISO_UMSK_ISR_SW_write_data_shift                                             (0)
#define ISO_UMSK_ISR_SW_write_data_mask                                              (0x00000001)
#define ISO_UMSK_ISR_SW_write_data(data)                                             (0x00000001&((data)<<0))
#define ISO_UMSK_ISR_SW_write_data_src(data)                                         ((0x00000001&(data))>>0)
#define ISO_UMSK_ISR_SW_get_write_data(data)                                         ((0x00000001&(data))>>0)


#define ISO_DBG                                                                      0x18007024
#define ISO_DBG_reg_addr                                                             "0xB8007024"
#define ISO_DBG_reg                                                                  0xB8007024
#define set_ISO_DBG_reg(data)   (*((volatile unsigned int*) ISO_DBG_reg)=data)
#define get_ISO_DBG_reg   (*((volatile unsigned int*) ISO_DBG_reg))
#define ISO_DBG_inst_adr                                                             "0x0009"
#define ISO_DBG_inst                                                                 0x0009
#define ISO_DBG_write_en5_shift                                                      (31)
#define ISO_DBG_write_en5_mask                                                       (0x80000000)
#define ISO_DBG_write_en5(data)                                                      (0x80000000&((data)<<31))
#define ISO_DBG_write_en5_src(data)                                                  ((0x80000000&(data))>>31)
#define ISO_DBG_get_write_en5(data)                                                  ((0x80000000&(data))>>31)
#define ISO_DBG_standby_dbg_sel_shift                                                (24)
#define ISO_DBG_standby_dbg_sel_mask                                                 (0x1F000000)
#define ISO_DBG_standby_dbg_sel(data)                                                (0x1F000000&((data)<<24))
#define ISO_DBG_standby_dbg_sel_src(data)                                            ((0x1F000000&(data))>>24)
#define ISO_DBG_get_standby_dbg_sel(data)                                            ((0x1F000000&(data))>>24)
#define ISO_DBG_write_en4_shift                                                      (23)
#define ISO_DBG_write_en4_mask                                                       (0x00800000)
#define ISO_DBG_write_en4(data)                                                      (0x00800000&((data)<<23))
#define ISO_DBG_write_en4_src(data)                                                  ((0x00800000&(data))>>23)
#define ISO_DBG_get_write_en4(data)                                                  ((0x00800000&(data))>>23)
#define ISO_DBG_standby_dbg_en_shift                                                 (20)
#define ISO_DBG_standby_dbg_en_mask                                                  (0x00100000)
#define ISO_DBG_standby_dbg_en(data)                                                 (0x00100000&((data)<<20))
#define ISO_DBG_standby_dbg_en_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_DBG_get_standby_dbg_en(data)                                             ((0x00100000&(data))>>20)
#define ISO_DBG_write_en3_shift                                                      (19)
#define ISO_DBG_write_en3_mask                                                       (0x00080000)
#define ISO_DBG_write_en3(data)                                                      (0x00080000&((data)<<19))
#define ISO_DBG_write_en3_src(data)                                                  ((0x00080000&(data))>>19)
#define ISO_DBG_get_write_en3(data)                                                  ((0x00080000&(data))>>19)
#define ISO_DBG_sel1_shift                                                           (12)
#define ISO_DBG_sel1_mask                                                            (0x0000F000)
#define ISO_DBG_sel1(data)                                                           (0x0000F000&((data)<<12))
#define ISO_DBG_sel1_src(data)                                                       ((0x0000F000&(data))>>12)
#define ISO_DBG_get_sel1(data)                                                       ((0x0000F000&(data))>>12)
#define ISO_DBG_write_en2_shift                                                      (11)
#define ISO_DBG_write_en2_mask                                                       (0x00000800)
#define ISO_DBG_write_en2(data)                                                      (0x00000800&((data)<<11))
#define ISO_DBG_write_en2_src(data)                                                  ((0x00000800&(data))>>11)
#define ISO_DBG_get_write_en2(data)                                                  ((0x00000800&(data))>>11)
#define ISO_DBG_sel0_shift                                                           (4)
#define ISO_DBG_sel0_mask                                                            (0x000000F0)
#define ISO_DBG_sel0(data)                                                           (0x000000F0&((data)<<4))
#define ISO_DBG_sel0_src(data)                                                       ((0x000000F0&(data))>>4)
#define ISO_DBG_get_sel0(data)                                                       ((0x000000F0&(data))>>4)
#define ISO_DBG_write_en1_shift                                                      (3)
#define ISO_DBG_write_en1_mask                                                       (0x00000008)
#define ISO_DBG_write_en1(data)                                                      (0x00000008&((data)<<3))
#define ISO_DBG_write_en1_src(data)                                                  ((0x00000008&(data))>>3)
#define ISO_DBG_get_write_en1(data)                                                  ((0x00000008&(data))>>3)
#define ISO_DBG_enable_shift                                                         (0)
#define ISO_DBG_enable_mask                                                          (0x00000001)
#define ISO_DBG_enable(data)                                                         (0x00000001&((data)<<0))
#define ISO_DBG_enable_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_DBG_get_enable(data)                                                     ((0x00000001&(data))>>0)


#define ISO_CHIP_INFO1                                                               0x18007028
#define ISO_CHIP_INFO1_reg_addr                                                      "0xB8007028"
#define ISO_CHIP_INFO1_reg                                                           0xB8007028
#define set_ISO_CHIP_INFO1_reg(data)   (*((volatile unsigned int*) ISO_CHIP_INFO1_reg)=data)
#define get_ISO_CHIP_INFO1_reg   (*((volatile unsigned int*) ISO_CHIP_INFO1_reg))
#define ISO_CHIP_INFO1_inst_adr                                                      "0x000A"
#define ISO_CHIP_INFO1_inst                                                          0x000A
#define ISO_CHIP_INFO1_testmode_shift                                                (12)
#define ISO_CHIP_INFO1_testmode_mask                                                 (0x00001000)
#define ISO_CHIP_INFO1_testmode(data)                                                (0x00001000&((data)<<12))
#define ISO_CHIP_INFO1_testmode_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CHIP_INFO1_get_testmode(data)                                            ((0x00001000&(data))>>12)
#define ISO_CHIP_INFO1_nf_sel_shift                                                  (11)
#define ISO_CHIP_INFO1_nf_sel_mask                                                   (0x00000800)
#define ISO_CHIP_INFO1_nf_sel(data)                                                  (0x00000800&((data)<<11))
#define ISO_CHIP_INFO1_nf_sel_src(data)                                              ((0x00000800&(data))>>11)
#define ISO_CHIP_INFO1_get_nf_sel(data)                                              ((0x00000800&(data))>>11)
#define ISO_CHIP_INFO1_bound_opt_shift                                               (0)
#define ISO_CHIP_INFO1_bound_opt_mask                                                (0x000007FF)
#define ISO_CHIP_INFO1_bound_opt(data)                                               (0x000007FF&((data)<<0))
#define ISO_CHIP_INFO1_bound_opt_src(data)                                           ((0x000007FF&(data))>>0)
#define ISO_CHIP_INFO1_get_bound_opt(data)                                           ((0x000007FF&(data))>>0)


#define ISO_CHIP_INFO2                                                               0x1800702C
#define ISO_CHIP_INFO2_reg_addr                                                      "0xB800702C"
#define ISO_CHIP_INFO2_reg                                                           0xB800702C
#define set_ISO_CHIP_INFO2_reg(data)   (*((volatile unsigned int*) ISO_CHIP_INFO2_reg)=data)
#define get_ISO_CHIP_INFO2_reg   (*((volatile unsigned int*) ISO_CHIP_INFO2_reg))
#define ISO_CHIP_INFO2_inst_adr                                                      "0x000B"
#define ISO_CHIP_INFO2_inst                                                          0x000B
#define ISO_CHIP_INFO2_pow_latch_shift                                               (0)
#define ISO_CHIP_INFO2_pow_latch_mask                                                (0x0007FFFF)
#define ISO_CHIP_INFO2_pow_latch(data)                                               (0x0007FFFF&((data)<<0))
#define ISO_CHIP_INFO2_pow_latch_src(data)                                           ((0x0007FFFF&(data))>>0)
#define ISO_CHIP_INFO2_get_pow_latch(data)                                           ((0x0007FFFF&(data))>>0)


#define A_RTCSEC                                                                     0x18061700
#define A_RTCSEC_reg_addr                                                            "0xB8061700"
#define A_RTCSEC_reg                                                                 0xB8061700
#define set_A_RTCSEC_reg(data)   (*((volatile unsigned int*) A_RTCSEC_reg)=data)
#define get_A_RTCSEC_reg   (*((volatile unsigned int*) A_RTCSEC_reg))
#define A_RTCSEC_inst_adr                                                            "0x00C0"
#define A_RTCSEC_inst                                                                0x00C0
#define A_RTCSEC_A_RTCSEC_shift                                                      (0)
#define A_RTCSEC_A_RTCSEC_mask                                                       (0x0000007F)
#define A_RTCSEC_A_RTCSEC(data)                                                      (0x0000007F&((data)<<0))
#define A_RTCSEC_A_RTCSEC_src(data)                                                  ((0x0000007F&(data))>>0)
#define A_RTCSEC_get_A_RTCSEC(data)                                                  ((0x0000007F&(data))>>0)


#define A_RTCMIN                                                                     0x18061704
#define A_RTCMIN_reg_addr                                                            "0xB8061704"
#define A_RTCMIN_reg                                                                 0xB8061704
#define set_A_RTCMIN_reg(data)   (*((volatile unsigned int*) A_RTCMIN_reg)=data)
#define get_A_RTCMIN_reg   (*((volatile unsigned int*) A_RTCMIN_reg))
#define A_RTCMIN_inst_adr                                                            "0x00C1"
#define A_RTCMIN_inst                                                                0x00C1
#define A_RTCMIN_A_RTCMIN_shift                                                      (0)
#define A_RTCMIN_A_RTCMIN_mask                                                       (0x0000003F)
#define A_RTCMIN_A_RTCMIN(data)                                                      (0x0000003F&((data)<<0))
#define A_RTCMIN_A_RTCMIN_src(data)                                                  ((0x0000003F&(data))>>0)
#define A_RTCMIN_get_A_RTCMIN(data)                                                  ((0x0000003F&(data))>>0)


#define A_RTCHR                                                                      0x18061708
#define A_RTCHR_reg_addr                                                             "0xB8061708"
#define A_RTCHR_reg                                                                  0xB8061708
#define set_A_RTCHR_reg(data)   (*((volatile unsigned int*) A_RTCHR_reg)=data)
#define get_A_RTCHR_reg   (*((volatile unsigned int*) A_RTCHR_reg))
#define A_RTCHR_inst_adr                                                             "0x00C2"
#define A_RTCHR_inst                                                                 0x00C2
#define A_RTCHR_A_RTCHR_shift                                                        (0)
#define A_RTCHR_A_RTCHR_mask                                                         (0x0000001F)
#define A_RTCHR_A_RTCHR(data)                                                        (0x0000001F&((data)<<0))
#define A_RTCHR_A_RTCHR_src(data)                                                    ((0x0000001F&(data))>>0)
#define A_RTCHR_get_A_RTCHR(data)                                                    ((0x0000001F&(data))>>0)


#define A_RTCDATE1                                                                   0x1806170C
#define A_RTCDATE1_reg_addr                                                          "0xB806170C"
#define A_RTCDATE1_reg                                                               0xB806170C
#define set_A_RTCDATE1_reg(data)   (*((volatile unsigned int*) A_RTCDATE1_reg)=data)
#define get_A_RTCDATE1_reg   (*((volatile unsigned int*) A_RTCDATE1_reg))
#define A_RTCDATE1_inst_adr                                                          "0x00C3"
#define A_RTCDATE1_inst                                                              0x00C3
#define A_RTCDATE1_A_RTCDATE1_shift                                                  (0)
#define A_RTCDATE1_A_RTCDATE1_mask                                                   (0x000000FF)
#define A_RTCDATE1_A_RTCDATE1(data)                                                  (0x000000FF&((data)<<0))
#define A_RTCDATE1_A_RTCDATE1_src(data)                                              ((0x000000FF&(data))>>0)
#define A_RTCDATE1_get_A_RTCDATE1(data)                                              ((0x000000FF&(data))>>0)


#define A_RTCDATE2                                                                   0x18061710
#define A_RTCDATE2_reg_addr                                                          "0xB8061710"
#define A_RTCDATE2_reg                                                               0xB8061710
#define set_A_RTCDATE2_reg(data)   (*((volatile unsigned int*) A_RTCDATE2_reg)=data)
#define get_A_RTCDATE2_reg   (*((volatile unsigned int*) A_RTCDATE2_reg))
#define A_RTCDATE2_inst_adr                                                          "0x00C4"
#define A_RTCDATE2_inst                                                              0x00C4
#define A_RTCDATE2_A_RTCDATE2_shift                                                  (0)
#define A_RTCDATE2_A_RTCDATE2_mask                                                   (0x0000007F)
#define A_RTCDATE2_A_RTCDATE2(data)                                                  (0x0000007F&((data)<<0))
#define A_RTCDATE2_A_RTCDATE2_src(data)                                              ((0x0000007F&(data))>>0)
#define A_RTCDATE2_get_A_RTCDATE2(data)                                              ((0x0000007F&(data))>>0)


#define A_ALMMIN                                                                     0x18061714
#define A_ALMMIN_reg_addr                                                            "0xB8061714"
#define A_ALMMIN_reg                                                                 0xB8061714
#define set_A_ALMMIN_reg(data)   (*((volatile unsigned int*) A_ALMMIN_reg)=data)
#define get_A_ALMMIN_reg   (*((volatile unsigned int*) A_ALMMIN_reg))
#define A_ALMMIN_inst_adr                                                            "0x00C5"
#define A_ALMMIN_inst                                                                0x00C5
#define A_ALMMIN_A_ALMMIN_shift                                                      (0)
#define A_ALMMIN_A_ALMMIN_mask                                                       (0x0000003F)
#define A_ALMMIN_A_ALMMIN(data)                                                      (0x0000003F&((data)<<0))
#define A_ALMMIN_A_ALMMIN_src(data)                                                  ((0x0000003F&(data))>>0)
#define A_ALMMIN_get_A_ALMMIN(data)                                                  ((0x0000003F&(data))>>0)


#define A_ALMHR                                                                      0x18061718
#define A_ALMHR_reg_addr                                                             "0xB8061718"
#define A_ALMHR_reg                                                                  0xB8061718
#define set_A_ALMHR_reg(data)   (*((volatile unsigned int*) A_ALMHR_reg)=data)
#define get_A_ALMHR_reg   (*((volatile unsigned int*) A_ALMHR_reg))
#define A_ALMHR_inst_adr                                                             "0x00C6"
#define A_ALMHR_inst                                                                 0x00C6
#define A_ALMHR_A_ALMHR_shift                                                        (0)
#define A_ALMHR_A_ALMHR_mask                                                         (0x0000001F)
#define A_ALMHR_A_ALMHR(data)                                                        (0x0000001F&((data)<<0))
#define A_ALMHR_A_ALMHR_src(data)                                                    ((0x0000001F&(data))>>0)
#define A_ALMHR_get_A_ALMHR(data)                                                    ((0x0000001F&(data))>>0)


#define A_ALMDATE1                                                                   0x1806171C
#define A_ALMDATE1_reg_addr                                                          "0xB806171C"
#define A_ALMDATE1_reg                                                               0xB806171C
#define set_A_ALMDATE1_reg(data)   (*((volatile unsigned int*) A_ALMDATE1_reg)=data)
#define get_A_ALMDATE1_reg   (*((volatile unsigned int*) A_ALMDATE1_reg))
#define A_ALMDATE1_inst_adr                                                          "0x00C7"
#define A_ALMDATE1_inst                                                              0x00C7
#define A_ALMDATE1_A_ALMDATE1_shift                                                  (0)
#define A_ALMDATE1_A_ALMDATE1_mask                                                   (0x000000FF)
#define A_ALMDATE1_A_ALMDATE1(data)                                                  (0x000000FF&((data)<<0))
#define A_ALMDATE1_A_ALMDATE1_src(data)                                              ((0x000000FF&(data))>>0)
#define A_ALMDATE1_get_A_ALMDATE1(data)                                              ((0x000000FF&(data))>>0)


#define A_ALMDATE2                                                                   0x18061720
#define A_ALMDATE2_reg_addr                                                          "0xB8061720"
#define A_ALMDATE2_reg                                                               0xB8061720
#define set_A_ALMDATE2_reg(data)   (*((volatile unsigned int*) A_ALMDATE2_reg)=data)
#define get_A_ALMDATE2_reg   (*((volatile unsigned int*) A_ALMDATE2_reg))
#define A_ALMDATE2_inst_adr                                                          "0x00C8"
#define A_ALMDATE2_inst                                                              0x00C8
#define A_ALMDATE2_A_ALMDATE2_shift                                                  (0)
#define A_ALMDATE2_A_ALMDATE2_mask                                                   (0x0000007F)
#define A_ALMDATE2_A_ALMDATE2(data)                                                  (0x0000007F&((data)<<0))
#define A_ALMDATE2_A_ALMDATE2_src(data)                                              ((0x0000007F&(data))>>0)
#define A_ALMDATE2_get_A_ALMDATE2(data)                                              ((0x0000007F&(data))>>0)


#define A_RTCSTOP                                                                    0x18061724
#define A_RTCSTOP_reg_addr                                                           "0xB8061724"
#define A_RTCSTOP_reg                                                                0xB8061724
#define set_A_RTCSTOP_reg(data)   (*((volatile unsigned int*) A_RTCSTOP_reg)=data)
#define get_A_RTCSTOP_reg   (*((volatile unsigned int*) A_RTCSTOP_reg))
#define A_RTCSTOP_inst_adr                                                           "0x00C9"
#define A_RTCSTOP_inst                                                               0x00C9
#define A_RTCSTOP_27Mclk_en_shift                                                    (3)
#define A_RTCSTOP_27Mclk_en_mask                                                     (0x00000008)
#define A_RTCSTOP_27Mclk_en(data)                                                    (0x00000008&((data)<<3))
#define A_RTCSTOP_27Mclk_en_src(data)                                                ((0x00000008&(data))>>3)
#define A_RTCSTOP_get_27Mclk_en(data)                                                ((0x00000008&(data))>>3)
#define A_RTCSTOP_VREF_shift                                                         (1)
#define A_RTCSTOP_VREF_mask                                                          (0x00000006)
#define A_RTCSTOP_VREF(data)                                                         (0x00000006&((data)<<1))
#define A_RTCSTOP_VREF_src(data)                                                     ((0x00000006&(data))>>1)
#define A_RTCSTOP_get_VREF(data)                                                     ((0x00000006&(data))>>1)
#define A_RTCSTOP_A_RTCSTOP_shift                                                    (0)
#define A_RTCSTOP_A_RTCSTOP_mask                                                     (0x00000001)
#define A_RTCSTOP_A_RTCSTOP(data)                                                    (0x00000001&((data)<<0))
#define A_RTCSTOP_A_RTCSTOP_src(data)                                                ((0x00000001&(data))>>0)
#define A_RTCSTOP_get_A_RTCSTOP(data)                                                ((0x00000001&(data))>>0)


#define A_RTCACR                                                                     0x18061728
#define A_RTCACR_reg_addr                                                            "0xB8061728"
#define A_RTCACR_reg                                                                 0xB8061728
#define set_A_RTCACR_reg(data)   (*((volatile unsigned int*) A_RTCACR_reg)=data)
#define get_A_RTCACR_reg   (*((volatile unsigned int*) A_RTCACR_reg))
#define A_RTCACR_inst_adr                                                            "0x00CA"
#define A_RTCACR_inst                                                                0x00CA
#define A_RTCACR_A_RTCPWR_shift                                                      (7)
#define A_RTCACR_A_RTCPWR_mask                                                       (0x00000080)
#define A_RTCACR_A_RTCPWR(data)                                                      (0x00000080&((data)<<7))
#define A_RTCACR_A_RTCPWR_src(data)                                                  ((0x00000080&(data))>>7)
#define A_RTCACR_get_A_RTCPWR(data)                                                  ((0x00000080&(data))>>7)
#define A_RTCACR_CO_shift                                                            (5)
#define A_RTCACR_CO_mask                                                             (0x00000060)
#define A_RTCACR_CO(data)                                                            (0x00000060&((data)<<5))
#define A_RTCACR_CO_src(data)                                                        ((0x00000060&(data))>>5)
#define A_RTCACR_get_CO(data)                                                        ((0x00000060&(data))>>5)
#define A_RTCACR_CI_shift                                                            (3)
#define A_RTCACR_CI_mask                                                             (0x00000018)
#define A_RTCACR_CI(data)                                                            (0x00000018&((data)<<3))
#define A_RTCACR_CI_src(data)                                                        ((0x00000018&(data))>>3)
#define A_RTCACR_get_CI(data)                                                        ((0x00000018&(data))>>3)
#define A_RTCACR_CLKSEL_shift                                                        (2)
#define A_RTCACR_CLKSEL_mask                                                         (0x00000004)
#define A_RTCACR_CLKSEL(data)                                                        (0x00000004&((data)<<2))
#define A_RTCACR_CLKSEL_src(data)                                                    ((0x00000004&(data))>>2)
#define A_RTCACR_get_CLKSEL(data)                                                    ((0x00000004&(data))>>2)
#define A_RTCACR_BC_shift                                                            (0)
#define A_RTCACR_BC_mask                                                             (0x00000003)
#define A_RTCACR_BC(data)                                                            (0x00000003&((data)<<0))
#define A_RTCACR_BC_src(data)                                                        ((0x00000003&(data))>>0)
#define A_RTCACR_get_BC(data)                                                        ((0x00000003&(data))>>0)


#define A_RTCEN                                                                      0x1806172C
#define A_RTCEN_reg_addr                                                             "0xB806172C"
#define A_RTCEN_reg                                                                  0xB806172C
#define set_A_RTCEN_reg(data)   (*((volatile unsigned int*) A_RTCEN_reg)=data)
#define get_A_RTCEN_reg   (*((volatile unsigned int*) A_RTCEN_reg))
#define A_RTCEN_inst_adr                                                             "0x00CB"
#define A_RTCEN_inst                                                                 0x00CB
#define A_RTCEN_A_RTCEN_shift                                                        (0)
#define A_RTCEN_A_RTCEN_mask                                                         (0x000000FF)
#define A_RTCEN_A_RTCEN(data)                                                        (0x000000FF&((data)<<0))
#define A_RTCEN_A_RTCEN_src(data)                                                    ((0x000000FF&(data))>>0)
#define A_RTCEN_get_A_RTCEN(data)                                                    ((0x000000FF&(data))>>0)

#define A_RTCCR                                                                      0x18061730
#define A_RTCCR_reg_addr                                                             "0xB8061730"
#define A_RTCCR_reg                                                                  0xB8061730
#define set_A_RTCCR_reg(data)   (*((volatile unsigned int*) A_RTCCR_reg)=data)
#define get_A_RTCCR_reg   (*((volatile unsigned int*) A_RTCCR_reg))
#define A_RTCCR_inst_adr                                                             "0x00CC"
#define A_RTCCR_inst                                                                 0x00CC
#define A_RTCCR_rtc_alarm_int_status_shift                                           (31)
#define A_RTCCR_rtc_alarm_int_status_mask                                            (0x80000000)
#define A_RTCCR_rtc_alarm_int_status(data)                                           (0x80000000&((data)<<31))
#define A_RTCCR_rtc_alarm_int_status_src(data)                                       ((0x80000000&(data))>>31)
#define A_RTCCR_get_rtc_alarm_int_status(data)                                       ((0x80000000&(data))>>31)
#define A_RTCCR_rtc_date_int_status_shift                                            (30)
#define A_RTCCR_rtc_date_int_status_mask                                             (0x40000000)
#define A_RTCCR_rtc_date_int_status(data)                                            (0x40000000&((data)<<30))
#define A_RTCCR_rtc_date_int_status_src(data)                                        ((0x40000000&(data))>>30)
#define A_RTCCR_get_rtc_date_int_status(data)                                        ((0x40000000&(data))>>30)
#define A_RTCCR_rtc_hour_int_status_shift                                            (29)
#define A_RTCCR_rtc_hour_int_status_mask                                             (0x20000000)
#define A_RTCCR_rtc_hour_int_status(data)                                            (0x20000000&((data)<<29))
#define A_RTCCR_rtc_hour_int_status_src(data)                                        ((0x20000000&(data))>>29)
#define A_RTCCR_get_rtc_hour_int_status(data)                                        ((0x20000000&(data))>>29)
#define A_RTCCR_rtc_min_int_status_shift                                             (28)
#define A_RTCCR_rtc_min_int_status_mask                                              (0x10000000)
#define A_RTCCR_rtc_min_int_status(data)                                             (0x10000000&((data)<<28))
#define A_RTCCR_rtc_min_int_status_src(data)                                         ((0x10000000&(data))>>28)
#define A_RTCCR_get_rtc_min_int_status(data)                                         ((0x10000000&(data))>>28)
#define A_RTCCR_rtc_hsec_int_status_shift                                            (27)
#define A_RTCCR_rtc_hsec_int_status_mask                                             (0x08000000)
#define A_RTCCR_rtc_hsec_int_status(data)                                            (0x08000000&((data)<<27))
#define A_RTCCR_rtc_hsec_int_status_src(data)                                        ((0x08000000&(data))>>27)
#define A_RTCCR_get_rtc_hsec_int_status(data)                                        ((0x08000000&(data))>>27)
#define A_RTCCR_A_RTCRST_shift                                                       (6)
#define A_RTCCR_A_RTCRST_mask                                                        (0x00000040)
#define A_RTCCR_A_RTCRST(data)                                                       (0x00000040&((data)<<6))
#define A_RTCCR_A_RTCRST_src(data)                                                   ((0x00000040&(data))>>6)
#define A_RTCCR_get_A_RTCRST(data)                                                   ((0x00000040&(data))>>6)
#define A_RTCCR_ALARMINTE_shift                                                      (4)
#define A_RTCCR_ALARMINTE_mask                                                       (0x00000010)
#define A_RTCCR_ALARMINTE(data)                                                      (0x00000010&((data)<<4))
#define A_RTCCR_ALARMINTE_src(data)                                                  ((0x00000010&(data))>>4)
#define A_RTCCR_get_ALARMINTE(data)                                                  ((0x00000010&(data))>>4)
#define A_RTCCR_DAINTE_shift                                                         (3)
#define A_RTCCR_DAINTE_mask                                                          (0x00000008)
#define A_RTCCR_DAINTE(data)                                                         (0x00000008&((data)<<3))
#define A_RTCCR_DAINTE_src(data)                                                     ((0x00000008&(data))>>3)
#define A_RTCCR_get_DAINTE(data)                                                     ((0x00000008&(data))>>3)
#define A_RTCCR_HUINTE_shift                                                         (2)
#define A_RTCCR_HUINTE_mask                                                          (0x00000004)
#define A_RTCCR_HUINTE(data)                                                         (0x00000004&((data)<<2))
#define A_RTCCR_HUINTE_src(data)                                                     ((0x00000004&(data))>>2)
#define A_RTCCR_get_HUINTE(data)                                                     ((0x00000004&(data))>>2)
#define A_RTCCR_MUINTE_shift                                                         (1)
#define A_RTCCR_MUINTE_mask                                                          (0x00000002)
#define A_RTCCR_MUINTE(data)                                                         (0x00000002&((data)<<1))
#define A_RTCCR_MUINTE_src(data)                                                     ((0x00000002&(data))>>1)
#define A_RTCCR_get_MUINTE(data)                                                     ((0x00000002&(data))>>1)
#define A_RTCCR_HSUINTE_shift                                                        (0)
#define A_RTCCR_HSUINTE_mask                                                         (0x00000001)
#define A_RTCCR_HSUINTE(data)                                                        (0x00000001&((data)<<0))
#define A_RTCCR_HSUINTE_src(data)                                                    ((0x00000001&(data))>>0)
#define A_RTCCR_get_HSUINTE(data)                                                    ((0x00000001&(data))>>0)


#define D_RTCSEC                                                                     0x18061900
#define D_RTCSEC_reg_addr                                                            "0xB8061900"
#define D_RTCSEC_reg                                                                 0xB8061900
#define set_D_RTCSEC_reg(data)   (*((volatile unsigned int*) D_RTCSEC_reg)=data)
#define get_D_RTCSEC_reg   (*((volatile unsigned int*) D_RTCSEC_reg))
//#define D_RTCSEC_inst_adr                                                            "0x00C0"
//#define D_RTCSEC_inst                                                                0x00C0
#define D_RTCSEC_D_RTCSEC_shift                                                      (0)
#define D_RTCSEC_D_RTCSEC_mask                                                       (0x0000007F)
#define D_RTCSEC_D_RTCSEC(data)                                                      (0x0000007F&((data)<<0))
#define D_RTCSEC_D_RTCSEC_src(data)                                                  ((0x0000007F&(data))>>0)
#define D_RTCSEC_get_D_RTCSEC(data)                                                  ((0x0000007F&(data))>>0)


#define D_RTCMIN                                                                     0x18061904
#define D_RTCMIN_reg_addr                                                            "0xB8061904"
#define D_RTCMIN_reg                                                                 0xB8061904
#define set_D_RTCMIN_reg(data)   (*((volatile unsigned int*) D_RTCMIN_reg)=data)
#define get_D_RTCMIN_reg   (*((volatile unsigned int*) D_RTCMIN_reg))
#define D_RTCMIN_inst_adr                                                            "0x00C1"
#define D_RTCMIN_inst                                                                0x00C1
#define D_RTCMIN_D_RTCMIN_shift                                                      (0)
#define D_RTCMIN_D_RTCMIN_mask                                                       (0x0000003F)
#define D_RTCMIN_D_RTCMIN(data)                                                      (0x0000003F&((data)<<0))
#define D_RTCMIN_D_RTCMIN_src(data)                                                  ((0x0000003F&(data))>>0)
#define D_RTCMIN_get_D_RTCMIN(data)                                                  ((0x0000003F&(data))>>0)


#define D_RTCHR                                                                      0x18061908
#define D_RTCHR_reg_addr                                                             "0xB8061908"
#define D_RTCHR_reg                                                                  0xB8061908
#define set_D_RTCHR_reg(data)   (*((volatile unsigned int*) D_RTCHR_reg)=data)
#define get_D_RTCHR_reg   (*((volatile unsigned int*) D_RTCHR_reg))
#define D_RTCHR_inst_adr                                                             "0x00C2"
#define D_RTCHR_inst                                                                 0x00C2
#define D_RTCHR_D_RTCHR_shift                                                        (0)
#define D_RTCHR_D_RTCHR_mask                                                         (0x0000001F)
#define D_RTCHR_D_RTCHR(data)                                                        (0x0000001F&((data)<<0))
#define D_RTCHR_D_RTCHR_src(data)                                                    ((0x0000001F&(data))>>0)
#define D_RTCHR_get_D_RTCHR(data)                                                    ((0x0000001F&(data))>>0)


#define D_RTCDATE1                                                                   0x1806190C
#define D_RTCDATE1_reg_addr                                                          "0xB806190C"
#define D_RTCDATE1_reg                                                               0xB806190C
#define set_D_RTCDATE1_reg(data)   (*((volatile unsigned int*) D_RTCDATE1_reg)=data)
#define get_D_RTCDATE1_reg   (*((volatile unsigned int*) D_RTCDATE1_reg))
#define D_RTCDATE1_inst_adr                                                          "0x00C3"
#define D_RTCDATE1_inst                                                              0x00C3
#define D_RTCDATE1_D_RTCDATE1_shift                                                  (0)
#define D_RTCDATE1_D_RTCDATE1_mask                                                   (0x000000FF)
#define D_RTCDATE1_D_RTCDATE1(data)                                                  (0x000000FF&((data)<<0))
#define D_RTCDATE1_D_RTCDATE1_src(data)                                              ((0x000000FF&(data))>>0)
#define D_RTCDATE1_get_D_RTCDATE1(data)                                              ((0x000000FF&(data))>>0)


#define D_RTCDATE2                                                                   0x18061910
#define D_RTCDATE2_reg_addr                                                          "0xB8061910"
#define D_RTCDATE2_reg                                                               0xB8061910
#define set_D_RTCDATE2_reg(data)   (*((volatile unsigned int*) D_RTCDATE2_reg)=data)
#define get_D_RTCDATE2_reg   (*((volatile unsigned int*) D_RTCDATE2_reg))
#define D_RTCDATE2_inst_adr                                                          "0x00C4"
#define D_RTCDATE2_inst                                                              0x00C4
#define D_RTCDATE2_D_RTCDATE2_shift                                                  (0)
#define D_RTCDATE2_D_RTCDATE2_mask                                                   (0x0000007F)
#define D_RTCDATE2_D_RTCDATE2(data)                                                  (0x0000007F&((data)<<0))
#define D_RTCDATE2_D_RTCDATE2_src(data)                                              ((0x0000007F&(data))>>0)
#define D_RTCDATE2_get_D_RTCDATE2(data)                                              ((0x0000007F&(data))>>0)


#define D_ALMMIN                                                                     0x18061914
#define D_ALMMIN_reg_addr                                                            "0xB8061914"
#define D_ALMMIN_reg                                                                 0xB8061914
#define set_D_ALMMIN_reg(data)   (*((volatile unsigned int*) D_ALMMIN_reg)=data)
#define get_D_ALMMIN_reg   (*((volatile unsigned int*) D_ALMMIN_reg))
#define D_ALMMIN_inst_adr                                                            "0x00C5"
#define D_ALMMIN_inst                                                                0x00C5
#define D_ALMMIN_D_ALMMIN_shift                                                      (0)
#define D_ALMMIN_D_ALMMIN_mask                                                       (0x0000003F)
#define D_ALMMIN_D_ALMMIN(data)                                                      (0x0000003F&((data)<<0))
#define D_ALMMIN_D_ALMMIN_src(data)                                                  ((0x0000003F&(data))>>0)
#define D_ALMMIN_get_D_ALMMIN(data)                                                  ((0x0000003F&(data))>>0)


#define D_ALMHR                                                                      0x18061918
#define D_ALMHR_reg_addr                                                             "0xB8061918"
#define D_ALMHR_reg                                                                  0xB8061918
#define set_D_ALMHR_reg(data)   (*((volatile unsigned int*) D_ALMHR_reg)=data)
#define get_D_ALMHR_reg   (*((volatile unsigned int*) D_ALMHR_reg))
#define D_ALMHR_inst_adr                                                             "0x00C6"
#define D_ALMHR_inst                                                                 0x00C6
#define D_ALMHR_D_ALMHR_shift                                                        (0)
#define D_ALMHR_D_ALMHR_mask                                                         (0x0000001F)
#define D_ALMHR_D_ALMHR(data)                                                        (0x0000001F&((data)<<0))
#define D_ALMHR_D_ALMHR_src(data)                                                    ((0x0000001F&(data))>>0)
#define D_ALMHR_get_D_ALMHR(data)                                                    ((0x0000001F&(data))>>0)


#define D_ALMDATE1                                                                   0x1806191C
#define D_ALMDATE1_reg_addr                                                          "0xB806191C"
#define D_ALMDATE1_reg                                                               0xB806191C
#define set_D_ALMDATE1_reg(data)   (*((volatile unsigned int*) D_ALMDATE1_reg)=data)
#define get_D_ALMDATE1_reg   (*((volatile unsigned int*) D_ALMDATE1_reg))
#define D_ALMDATE1_inst_adr                                                          "0x00C7"
#define D_ALMDATE1_inst                                                              0x00C7
#define D_ALMDATE1_D_ALMDATE1_shift                                                  (0)
#define D_ALMDATE1_D_ALMDATE1_mask                                                   (0x000000FF)
#define D_ALMDATE1_D_ALMDATE1(data)                                                  (0x000000FF&((data)<<0))
#define D_ALMDATE1_D_ALMDATE1_src(data)                                              ((0x000000FF&(data))>>0)
#define D_ALMDATE1_get_D_ALMDATE1(data)                                              ((0x000000FF&(data))>>0)


#define D_ALMDATE2                                                                   0x18061920
#define D_ALMDATE2_reg_addr                                                          "0xB8061920"
#define D_ALMDATE2_reg                                                               0xB8061920
#define set_D_ALMDATE2_reg(data)   (*((volatile unsigned int*) D_ALMDATE2_reg)=data)
#define get_D_ALMDATE2_reg   (*((volatile unsigned int*) D_ALMDATE2_reg))
#define D_ALMDATE2_inst_adr                                                          "0x00C8"
#define D_ALMDATE2_inst                                                              0x00C8
#define D_ALMDATE2_D_ALMDATE2_shift                                                  (0)
#define D_ALMDATE2_D_ALMDATE2_mask                                                   (0x0000007F)
#define D_ALMDATE2_D_ALMDATE2(data)                                                  (0x0000007F&((data)<<0))
#define D_ALMDATE2_D_ALMDATE2_src(data)                                              ((0x0000007F&(data))>>0)
#define D_ALMDATE2_get_D_ALMDATE2(data)                                              ((0x0000007F&(data))>>0)


#define D_RTCSTOP                                                                    0x18061924
#define D_RTCSTOP_reg_addr                                                           "0xB8061924"
#define D_RTCSTOP_reg                                                                0xB8061924
#define set_D_RTCSTOP_reg(data)   (*((volatile unsigned int*) D_RTCSTOP_reg)=data)
#define get_D_RTCSTOP_reg   (*((volatile unsigned int*) D_RTCSTOP_reg))
#define D_RTCSTOP_inst_adr                                                           "0x00C9"
#define D_RTCSTOP_inst                                                               0x00C9
#define D_RTCSTOP_27Mclk_en_shift                                                    (3)
#define D_RTCSTOP_27Mclk_en_mask                                                     (0x00000008)
#define D_RTCSTOP_27Mclk_en(data)                                                    (0x00000008&((data)<<3))
#define D_RTCSTOP_27Mclk_en_src(data)                                                ((0x00000008&(data))>>3)
#define D_RTCSTOP_get_27Mclk_en(data)                                                ((0x00000008&(data))>>3)
#define D_RTCSTOP_VREF_shift                                                         (1)
#define D_RTCSTOP_VREF_mask                                                          (0x00000006)
#define D_RTCSTOP_VREF(data)                                                         (0x00000006&((data)<<1))
#define D_RTCSTOP_VREF_src(data)                                                     ((0x00000006&(data))>>1)
#define D_RTCSTOP_get_VREF(data)                                                     ((0x00000006&(data))>>1)
#define D_RTCSTOP_D_RTCSTOP_shift                                                    (0)
#define D_RTCSTOP_D_RTCSTOP_mask                                                     (0x00000001)
#define D_RTCSTOP_D_RTCSTOP(data)                                                    (0x00000001&((data)<<0))
#define D_RTCSTOP_D_RTCSTOP_src(data)                                                ((0x00000001&(data))>>0)
#define D_RTCSTOP_get_D_RTCSTOP(data)                                                ((0x00000001&(data))>>0)


#define D_RTCACR                                                                     0x18061928
#define D_RTCACR_reg_addr                                                            "0xB8061928"
#define D_RTCACR_reg                                                                 0xB8061928
#define set_D_RTCACR_reg(data)   (*((volatile unsigned int*) D_RTCACR_reg)=data)
#define get_D_RTCACR_reg   (*((volatile unsigned int*) D_RTCACR_reg))
#define D_RTCACR_inst_adr                                                            "0x00CA"
#define D_RTCACR_inst                                                                0x00CA
#define D_RTCACR_D_RTCPWR_shift                                                      (7)
#define D_RTCACR_D_RTCPWR_mask                                                       (0x00000080)
#define D_RTCACR_D_RTCPWR(data)                                                      (0x00000080&((data)<<7))
#define D_RTCACR_D_RTCPWR_src(data)                                                  ((0x00000080&(data))>>7)
#define D_RTCACR_get_D_RTCPWR(data)                                                  ((0x00000080&(data))>>7)
#define D_RTCACR_CO_shift                                                            (5)
#define D_RTCACR_CO_mask                                                             (0x00000060)
#define D_RTCACR_CO(data)                                                            (0x00000060&((data)<<5))
#define D_RTCACR_CO_src(data)                                                        ((0x00000060&(data))>>5)
#define D_RTCACR_get_CO(data)                                                        ((0x00000060&(data))>>5)
#define D_RTCACR_CI_shift                                                            (3)
#define D_RTCACR_CI_mask                                                             (0x00000018)
#define D_RTCACR_CI(data)                                                            (0x00000018&((data)<<3))
#define D_RTCACR_CI_src(data)                                                        ((0x00000018&(data))>>3)
#define D_RTCACR_get_CI(data)                                                        ((0x00000018&(data))>>3)
#define D_RTCACR_CLKSEL_shift                                                        (2)
#define D_RTCACR_CLKSEL_mask                                                         (0x00000004)
#define D_RTCACR_CLKSEL(data)                                                        (0x00000004&((data)<<2))
#define D_RTCACR_CLKSEL_src(data)                                                    ((0x00000004&(data))>>2)
#define D_RTCACR_get_CLKSEL(data)                                                    ((0x00000004&(data))>>2)
#define D_RTCACR_BC_shift                                                            (0)
#define D_RTCACR_BC_mask                                                             (0x00000003)
#define D_RTCACR_BC(data)                                                            (0x00000003&((data)<<0))
#define D_RTCACR_BC_src(data)                                                        ((0x00000003&(data))>>0)
#define D_RTCACR_get_BC(data)                                                        ((0x00000003&(data))>>0)


#define D_RTCEN                                                                      0x1806192C
#define D_RTCEN_reg_addr                                                             "0xB806192C"
#define D_RTCEN_reg                                                                  0xB806192C
#define set_D_RTCEN_reg(data)   (*((volatile unsigned int*) D_RTCEN_reg)=data)
#define get_D_RTCEN_reg   (*((volatile unsigned int*) D_RTCEN_reg))
#define D_RTCEN_inst_adr                                                             "0x00CB"
#define D_RTCEN_inst                                                                 0x00CB
#define D_RTCEN_D_RTCEN_shift                                                        (0)
#define D_RTCEN_D_RTCEN_mask                                                         (0x000000FF)
#define D_RTCEN_D_RTCEN(data)                                                        (0x000000FF&((data)<<0))
#define D_RTCEN_D_RTCEN_src(data)                                                    ((0x000000FF&(data))>>0)
#define D_RTCEN_get_D_RTCEN(data)                                                    ((0x000000FF&(data))>>0)

#define D_RTCCR                                                                      0x18061930
#define D_RTCCR_reg_addr                                                             "0xB8061930"
#define D_RTCCR_reg                                                                  0xB8061930
#define set_D_RTCCR_reg(data)   (*((volatile unsigned int*) D_RTCCR_reg)=data)
#define get_D_RTCCR_reg   (*((volatile unsigned int*) D_RTCCR_reg))
#define D_RTCCR_inst_adr                                                             "0x00CC"
#define D_RTCCR_inst                                                                 0x00CC
#define D_RTCCR_rtc_alarm_int_status_shift                                           (31)
#define D_RTCCR_rtc_alarm_int_status_mask                                            (0x80000000)
#define D_RTCCR_rtc_alarm_int_status(data)                                           (0x80000000&((data)<<31))
#define D_RTCCR_rtc_alarm_int_status_src(data)                                       ((0x80000000&(data))>>31)
#define D_RTCCR_get_rtc_alarm_int_status(data)                                       ((0x80000000&(data))>>31)
#define D_RTCCR_rtc_date_int_status_shift                                            (30)
#define D_RTCCR_rtc_date_int_status_mask                                             (0x40000000)
#define D_RTCCR_rtc_date_int_status(data)                                            (0x40000000&((data)<<30))
#define D_RTCCR_rtc_date_int_status_src(data)                                        ((0x40000000&(data))>>30)
#define D_RTCCR_get_rtc_date_int_status(data)                                        ((0x40000000&(data))>>30)
#define D_RTCCR_rtc_hour_int_status_shift                                            (29)
#define D_RTCCR_rtc_hour_int_status_mask                                             (0x20000000)
#define D_RTCCR_rtc_hour_int_status(data)                                            (0x20000000&((data)<<29))
#define D_RTCCR_rtc_hour_int_status_src(data)                                        ((0x20000000&(data))>>29)
#define D_RTCCR_get_rtc_hour_int_status(data)                                        ((0x20000000&(data))>>29)
#define D_RTCCR_rtc_min_int_status_shift                                             (28)
#define D_RTCCR_rtc_min_int_status_mask                                              (0x10000000)
#define D_RTCCR_rtc_min_int_status(data)                                             (0x10000000&((data)<<28))
#define D_RTCCR_rtc_min_int_status_src(data)                                         ((0x10000000&(data))>>28)
#define D_RTCCR_get_rtc_min_int_status(data)                                         ((0x10000000&(data))>>28)
#define D_RTCCR_rtc_hsec_int_status_shift                                            (27)
#define D_RTCCR_rtc_hsec_int_status_mask                                             (0x08000000)
#define D_RTCCR_rtc_hsec_int_status(data)                                            (0x08000000&((data)<<27))
#define D_RTCCR_rtc_hsec_int_status_src(data)                                        ((0x08000000&(data))>>27)
#define D_RTCCR_get_rtc_hsec_int_status(data)                                        ((0x08000000&(data))>>27)
#define D_RTCCR_D_RTCRST_shift                                                       (6)
#define D_RTCCR_D_RTCRST_mask                                                        (0x00000040)
#define D_RTCCR_D_RTCRST(data)                                                       (0x00000040&((data)<<6))
#define D_RTCCR_D_RTCRST_src(data)                                                   ((0x00000040&(data))>>6)
#define D_RTCCR_get_D_RTCRST(data)                                                   ((0x00000040&(data))>>6)
#define D_RTCCR_ALARMINTE_shift                                                      (4)
#define D_RTCCR_ALARMINTE_mask                                                       (0x00000010)
#define D_RTCCR_ALARMINTE(data)                                                      (0x00000010&((data)<<4))
#define D_RTCCR_ALARMINTE_src(data)                                                  ((0x00000010&(data))>>4)
#define D_RTCCR_get_ALARMINTE(data)                                                  ((0x00000010&(data))>>4)
#define D_RTCCR_DAINTE_shift                                                         (3)
#define D_RTCCR_DAINTE_mask                                                          (0x00000008)
#define D_RTCCR_DAINTE(data)                                                         (0x00000008&((data)<<3))
#define D_RTCCR_DAINTE_src(data)                                                     ((0x00000008&(data))>>3)
#define D_RTCCR_get_DAINTE(data)                                                     ((0x00000008&(data))>>3)
#define D_RTCCR_HUINTE_shift                                                         (2)
#define D_RTCCR_HUINTE_mask                                                          (0x00000004)
#define D_RTCCR_HUINTE(data)                                                         (0x00000004&((data)<<2))
#define D_RTCCR_HUINTE_src(data)                                                     ((0x00000004&(data))>>2)
#define D_RTCCR_get_HUINTE(data)                                                     ((0x00000004&(data))>>2)
#define D_RTCCR_MUINTE_shift                                                         (1)
#define D_RTCCR_MUINTE_mask                                                          (0x00000002)
#define D_RTCCR_MUINTE(data)                                                         (0x00000002&((data)<<1))
#define D_RTCCR_MUINTE_src(data)                                                     ((0x00000002&(data))>>1)
#define D_RTCCR_get_MUINTE(data)                                                     ((0x00000002&(data))>>1)
#define D_RTCCR_HSUINTE_shift                                                        (0)
#define D_RTCCR_HSUINTE_mask                                                         (0x00000001)
#define D_RTCCR_HSUINTE(data)                                                        (0x00000001&((data)<<0))
#define D_RTCCR_HSUINTE_src(data)                                                    ((0x00000001&(data))>>0)
#define D_RTCCR_get_HSUINTE(data)                                                    ((0x00000001&(data))>>0)


#define ISO_CTRL                                                                     0x18007030
#define ISO_CTRL_reg_addr                                                            "0xB8007030"
#define ISO_CTRL_reg                                                                 0xB8007030
#define set_ISO_CTRL_reg(data)   (*((volatile unsigned int*) ISO_CTRL_reg)=data)
#define get_ISO_CTRL_reg   (*((volatile unsigned int*) ISO_CTRL_reg))
#define ISO_CTRL_inst_adr                                                            "0x000C"
#define ISO_CTRL_inst                                                                0x000C
#define ISO_CTRL_write_en9_shift                                                     (17)
#define ISO_CTRL_write_en9_mask                                                      (0x00020000)
#define ISO_CTRL_write_en9(data)                                                     (0x00020000&((data)<<17))
#define ISO_CTRL_write_en9_src(data)                                                 ((0x00020000&(data))>>17)
#define ISO_CTRL_get_write_en9(data)                                                 ((0x00020000&(data))>>17)
#define ISO_CTRL_iso_rst_wd_mask_shift                                               (16)
#define ISO_CTRL_iso_rst_wd_mask_mask                                                (0x00010000)
#define ISO_CTRL_iso_rst_wd_mask(data)                                               (0x00010000&((data)<<16))
#define ISO_CTRL_iso_rst_wd_mask_src(data)                                           ((0x00010000&(data))>>16)
#define ISO_CTRL_get_iso_rst_wd_mask(data)                                           ((0x00010000&(data))>>16)
#define ISO_CTRL_write_en8_shift                                                     (15)
#define ISO_CTRL_write_en8_mask                                                      (0x00008000)
#define ISO_CTRL_write_en8(data)                                                     (0x00008000&((data)<<15))
#define ISO_CTRL_write_en8_src(data)                                                 ((0x00008000&(data))>>15)
#define ISO_CTRL_get_write_en8(data)                                                 ((0x00008000&(data))>>15)
#define ISO_CTRL_dc_phy_cke_pd_shift                                                 (14)
#define ISO_CTRL_dc_phy_cke_pd_mask                                                  (0x00004000)
#define ISO_CTRL_dc_phy_cke_pd(data)                                                 (0x00004000&((data)<<14))
#define ISO_CTRL_dc_phy_cke_pd_src(data)                                             ((0x00004000&(data))>>14)
#define ISO_CTRL_get_dc_phy_cke_pd(data)                                             ((0x00004000&(data))>>14)
#define ISO_CTRL_write_en7_shift                                                     (13)
#define ISO_CTRL_write_en7_mask                                                      (0x00002000)
#define ISO_CTRL_write_en7(data)                                                     (0x00002000&((data)<<13))
#define ISO_CTRL_write_en7_src(data)                                                 ((0x00002000&(data))>>13)
#define ISO_CTRL_get_write_en7(data)                                                 ((0x00002000&(data))>>13)
#define ISO_CTRL_iso_mis_clk_en_shift                                                (12)
#define ISO_CTRL_iso_mis_clk_en_mask                                                 (0x00001000)
#define ISO_CTRL_iso_mis_clk_en(data)                                                (0x00001000&((data)<<12))
#define ISO_CTRL_iso_mis_clk_en_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CTRL_get_iso_mis_clk_en(data)                                            ((0x00001000&(data))>>12)
#define ISO_CTRL_write_en6_shift                                                     (11)
#define ISO_CTRL_write_en6_mask                                                      (0x00000800)
#define ISO_CTRL_write_en6(data)                                                     (0x00000800&((data)<<11))
#define ISO_CTRL_write_en6_src(data)                                                 ((0x00000800&(data))>>11)
#define ISO_CTRL_get_write_en6(data)                                                 ((0x00000800&(data))>>11)
#define ISO_CTRL_iso_rbus_sel_shift                                                  (10)
#define ISO_CTRL_iso_rbus_sel_mask                                                   (0x00000400)
#define ISO_CTRL_iso_rbus_sel(data)                                                  (0x00000400&((data)<<10))
#define ISO_CTRL_iso_rbus_sel_src(data)                                              ((0x00000400&(data))>>10)
#define ISO_CTRL_get_iso_rbus_sel(data)                                              ((0x00000400&(data))>>10)
#define ISO_CTRL_write_en5_shift                                                     (9)
#define ISO_CTRL_write_en5_mask                                                      (0x00000200)
#define ISO_CTRL_write_en5(data)                                                     (0x00000200&((data)<<9))
#define ISO_CTRL_write_en5_src(data)                                                 ((0x00000200&(data))>>9)
#define ISO_CTRL_get_write_en5(data)                                                 ((0x00000200&(data))>>9)
#define ISO_CTRL_iso_rst_mask_shift                                                  (8)
#define ISO_CTRL_iso_rst_mask_mask                                                   (0x00000100)
#define ISO_CTRL_iso_rst_mask(data)                                                  (0x00000100&((data)<<8))
#define ISO_CTRL_iso_rst_mask_src(data)                                              ((0x00000100&(data))>>8)
#define ISO_CTRL_get_iso_rst_mask(data)                                              ((0x00000100&(data))>>8)
#define ISO_CTRL_write_en4_shift                                                     (7)
#define ISO_CTRL_write_en4_mask                                                      (0x00000080)
#define ISO_CTRL_write_en4(data)                                                     (0x00000080&((data)<<7))
#define ISO_CTRL_write_en4_src(data)                                                 ((0x00000080&(data))>>7)
#define ISO_CTRL_get_write_en4(data)                                                 ((0x00000080&(data))>>7)
#define ISO_CTRL_clk_osc_on_en_shift                                                 (6)
#define ISO_CTRL_clk_osc_on_en_mask                                                  (0x00000040)
#define ISO_CTRL_clk_osc_on_en(data)                                                 (0x00000040&((data)<<6))
#define ISO_CTRL_clk_osc_on_en_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_CTRL_get_clk_osc_on_en(data)                                             ((0x00000040&(data))>>6)
#define ISO_CTRL_write_en3_shift                                                     (5)
#define ISO_CTRL_write_en3_mask                                                      (0x00000020)
#define ISO_CTRL_write_en3(data)                                                     (0x00000020&((data)<<5))
#define ISO_CTRL_write_en3_src(data)                                                 ((0x00000020&(data))>>5)
#define ISO_CTRL_get_write_en3(data)                                                 ((0x00000020&(data))>>5)
#define ISO_CTRL_crt_sw_rstn_shift                                                   (4)
#define ISO_CTRL_crt_sw_rstn_mask                                                    (0x00000010)
#define ISO_CTRL_crt_sw_rstn(data)                                                   (0x00000010&((data)<<4))
#define ISO_CTRL_crt_sw_rstn_src(data)                                               ((0x00000010&(data))>>4)
#define ISO_CTRL_get_crt_sw_rstn(data)                                               ((0x00000010&(data))>>4)
#define ISO_CTRL_write_en2_shift                                                     (3)
#define ISO_CTRL_write_en2_mask                                                      (0x00000008)
#define ISO_CTRL_write_en2(data)                                                     (0x00000008&((data)<<3))
#define ISO_CTRL_write_en2_src(data)                                                 ((0x00000008&(data))>>3)
#define ISO_CTRL_get_write_en2(data)                                                 ((0x00000008&(data))>>3)
#define ISO_CTRL_iso_clk_sel_shift                                                   (2)
#define ISO_CTRL_iso_clk_sel_mask                                                    (0x00000004)
#define ISO_CTRL_iso_clk_sel(data)                                                   (0x00000004&((data)<<2))
#define ISO_CTRL_iso_clk_sel_src(data)                                               ((0x00000004&(data))>>2)
#define ISO_CTRL_get_iso_clk_sel(data)                                               ((0x00000004&(data))>>2)
#define ISO_CTRL_write_en1_shift                                                     (1)
#define ISO_CTRL_write_en1_mask                                                      (0x00000002)
#define ISO_CTRL_write_en1(data)                                                     (0x00000002&((data)<<1))
#define ISO_CTRL_write_en1_src(data)                                                 ((0x00000002&(data))>>1)
#define ISO_CTRL_get_write_en1(data)                                                 ((0x00000002&(data))>>1)
#define ISO_CTRL_ejtag_en_shift                                                      (0)
#define ISO_CTRL_ejtag_en_mask                                                       (0x00000001)
#define ISO_CTRL_ejtag_en(data)                                                      (0x00000001&((data)<<0))
#define ISO_CTRL_ejtag_en_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_CTRL_get_ejtag_en(data)                                                  ((0x00000001&(data))>>0)


#define ISO_RTC                                                                      0x18007034
#define ISO_RTC_reg_addr                                                             "0xB8007034"
#define ISO_RTC_reg                                                                  0xB8007034
#define set_ISO_RTC_reg(data)   (*((volatile unsigned int*) ISO_RTC_reg)=data)
#define get_ISO_RTC_reg   (*((volatile unsigned int*) ISO_RTC_reg))
#define ISO_RTC_inst_adr                                                             "0x000D"
#define ISO_RTC_inst                                                                 0x000D
#define ISO_RTC_hsec_int_en_shift                                                    (1)
#define ISO_RTC_hsec_int_en_mask                                                     (0x00000002)
#define ISO_RTC_hsec_int_en(data)                                                    (0x00000002&((data)<<1))
#define ISO_RTC_hsec_int_en_src(data)                                                ((0x00000002&(data))>>1)
#define ISO_RTC_get_hsec_int_en(data)                                                ((0x00000002&(data))>>1)
#define ISO_RTC_alarm_int_en_shift                                                   (0)
#define ISO_RTC_alarm_int_en_mask                                                    (0x00000001)
#define ISO_RTC_alarm_int_en(data)                                                   (0x00000001&((data)<<0))
#define ISO_RTC_alarm_int_en_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_RTC_get_alarm_int_en(data)                                               ((0x00000001&(data))>>0)


#define ISO_CELL                                                                     0x18007038
#define ISO_CELL_reg_addr                                                            "0xB8007038"
#define ISO_CELL_reg                                                                 0xB8007038
#define set_ISO_CELL_reg(data)   (*((volatile unsigned int*) ISO_CELL_reg)=data)
#define get_ISO_CELL_reg   (*((volatile unsigned int*) ISO_CELL_reg))
#define ISO_CELL_inst_adr                                                            "0x000E"
#define ISO_CELL_inst                                                                0x000E
#define ISO_CELL_iso_ctrl_en1_shift                                                  (1)
#define ISO_CELL_iso_ctrl_en1_mask                                                   (0x00000002)
#define ISO_CELL_iso_ctrl_en1(data)                                                  (0x00000002&((data)<<1))
#define ISO_CELL_iso_ctrl_en1_src(data)                                              ((0x00000002&(data))>>1)
#define ISO_CELL_get_iso_ctrl_en1(data)                                              ((0x00000002&(data))>>1)
#define ISO_CELL_iso_ctrl_en0_shift                                                  (0)
#define ISO_CELL_iso_ctrl_en0_mask                                                   (0x00000001)
#define ISO_CELL_iso_ctrl_en0(data)                                                  (0x00000001&((data)<<0))
#define ISO_CELL_iso_ctrl_en0_src(data)                                              ((0x00000001&(data))>>0)
#define ISO_CELL_get_iso_ctrl_en0(data)                                              ((0x00000001&(data))>>0)


#define ISO_POWER                                                                    0x1800703C
#define ISO_POWER_reg_addr                                                           "0xB800703C"
#define ISO_POWER_reg                                                                0xB800703C
#define set_ISO_POWER_reg(data)   (*((volatile unsigned int*) ISO_POWER_reg)=data)
#define get_ISO_POWER_reg   (*((volatile unsigned int*) ISO_POWER_reg))
#define ISO_POWER_inst_adr                                                           "0x000F"
#define ISO_POWER_inst                                                               0x000F
#define ISO_POWER_v1_on_shift                                                        (0)
#define ISO_POWER_v1_on_mask                                                         (0x00000001)
#define ISO_POWER_v1_on(data)                                                        (0x00000001&((data)<<0))
#define ISO_POWER_v1_on_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_POWER_get_v1_on(data)                                                    ((0x00000001&(data))>>0)


#define ISO_SCPU_INT_EN                                                              0x18061004
#define ISO_SCPU_INT_EN_reg_addr                                                     "0xB8061004"
#define ISO_SCPU_INT_EN_reg                                                          0xB8061004
#define set_ISO_SCPU_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_SCPU_INT_EN_reg)=data)
#define get_ISO_SCPU_INT_EN_reg   (*((volatile unsigned int*) ISO_SCPU_INT_EN_reg))
#define ISO_SCPU_INT_EN_inst_adr                                                     "0x0010"
#define ISO_SCPU_INT_EN_inst                                                         0x0010
#define ISO_SCPU_INT_EN_cec_shift                                                    (22)
#define ISO_SCPU_INT_EN_cec_mask                                                     (0x00400000)
#define ISO_SCPU_INT_EN_cec(data)                                                    (0x00400000&((data)<<22))
#define ISO_SCPU_INT_EN_cec_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_SCPU_INT_EN_get_cec(data)                                                ((0x00400000&(data))>>22)
#define ISO_SCPU_INT_EN_gpioda_shift                                                 (20)
#define ISO_SCPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define ISO_SCPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define ISO_SCPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_SCPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define ISO_SCPU_INT_EN_gpioa_shift                                                  (19)
#define ISO_SCPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define ISO_SCPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define ISO_SCPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_SCPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define ISO_SCPU_INT_EN_vfd_ardswda_shift                                            (18)
#define ISO_SCPU_INT_EN_vfd_ardswda_mask                                             (0x00040000)
#define ISO_SCPU_INT_EN_vfd_ardswda(data)                                            (0x00040000&((data)<<18))
#define ISO_SCPU_INT_EN_vfd_ardswda_src(data)                                        ((0x00040000&(data))>>18)
#define ISO_SCPU_INT_EN_get_vfd_ardswda(data)                                        ((0x00040000&(data))>>18)
#define ISO_SCPU_INT_EN_vfd_ardswa_shift                                             (17)
#define ISO_SCPU_INT_EN_vfd_ardswa_mask                                              (0x00020000)
#define ISO_SCPU_INT_EN_vfd_ardswa(data)                                             (0x00020000&((data)<<17))
#define ISO_SCPU_INT_EN_vfd_ardswa_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_SCPU_INT_EN_get_vfd_ardswa(data)                                         ((0x00020000&(data))>>17)
#define ISO_SCPU_INT_EN_vfd_ardkpadda_shift                                          (16)
#define ISO_SCPU_INT_EN_vfd_ardkpadda_mask                                           (0x00010000)
#define ISO_SCPU_INT_EN_vfd_ardkpadda(data)                                          (0x00010000&((data)<<16))
#define ISO_SCPU_INT_EN_vfd_ardkpadda_src(data)                                      ((0x00010000&(data))>>16)
#define ISO_SCPU_INT_EN_get_vfd_ardkpadda(data)                                      ((0x00010000&(data))>>16)
#define ISO_SCPU_INT_EN_vfd_ardkpada_shift                                           (15)
#define ISO_SCPU_INT_EN_vfd_ardkpada_mask                                            (0x00008000)
#define ISO_SCPU_INT_EN_vfd_ardkpada(data)                                           (0x00008000&((data)<<15))
#define ISO_SCPU_INT_EN_vfd_ardkpada_src(data)                                       ((0x00008000&(data))>>15)
#define ISO_SCPU_INT_EN_get_vfd_ardkpada(data)                                       ((0x00008000&(data))>>15)
#define ISO_SCPU_INT_EN_vfd_wdone_shift                                              (14)
#define ISO_SCPU_INT_EN_vfd_wdone_mask                                               (0x00004000)
#define ISO_SCPU_INT_EN_vfd_wdone(data)                                              (0x00004000&((data)<<14))
#define ISO_SCPU_INT_EN_vfd_wdone_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_SCPU_INT_EN_get_vfd_wdone(data)                                          ((0x00004000&(data))>>14)
#define ISO_SCPU_INT_EN_rtc_alarm_shift                                              (13)
#define ISO_SCPU_INT_EN_rtc_alarm_mask                                               (0x00002000)
#define ISO_SCPU_INT_EN_rtc_alarm(data)                                              (0x00002000&((data)<<13))
#define ISO_SCPU_INT_EN_rtc_alarm_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_SCPU_INT_EN_get_rtc_alarm(data)                                          ((0x00002000&(data))>>13)
#define ISO_SCPU_INT_EN_rtc_hsec_shift                                               (12)
#define ISO_SCPU_INT_EN_rtc_hsec_mask                                                (0x00001000)
#define ISO_SCPU_INT_EN_rtc_hsec(data)                                               (0x00001000&((data)<<12))
#define ISO_SCPU_INT_EN_rtc_hsec_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_SCPU_INT_EN_get_rtc_hsec(data)                                           ((0x00001000&(data))>>12)
#define ISO_SCPU_INT_EN_ur1_to_shift                                                 (6)
#define ISO_SCPU_INT_EN_ur1_to_mask                                                  (0x00000040)
#define ISO_SCPU_INT_EN_ur1_to(data)                                                 (0x00000040&((data)<<6))
#define ISO_SCPU_INT_EN_ur1_to_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_SCPU_INT_EN_get_ur1_to(data)                                             ((0x00000040&(data))>>6)
#define ISO_SCPU_INT_EN_irda_shift                                                   (5)
#define ISO_SCPU_INT_EN_irda_mask                                                    (0x00000020)
#define ISO_SCPU_INT_EN_irda(data)                                                   (0x00000020&((data)<<5))
#define ISO_SCPU_INT_EN_irda_src(data)                                               ((0x00000020&(data))>>5)
#define ISO_SCPU_INT_EN_get_irda(data)                                               ((0x00000020&(data))>>5)
#define ISO_SCPU_INT_EN_ur2_shift                                                    (4)
#define ISO_SCPU_INT_EN_ur2_mask                                                     (0x00000010)
#define ISO_SCPU_INT_EN_ur2(data)                                                    (0x00000010&((data)<<4))
#define ISO_SCPU_INT_EN_ur2_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_SCPU_INT_EN_get_ur2(data)                                                ((0x00000010&(data))>>4)
#define ISO_SCPU_INT_EN_ur1_shift                                                    (3)
#define ISO_SCPU_INT_EN_ur1_mask                                                     (0x00000008)
#define ISO_SCPU_INT_EN_ur1(data)                                                    (0x00000008&((data)<<3))
#define ISO_SCPU_INT_EN_ur1_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_SCPU_INT_EN_get_ur1(data)                                                ((0x00000008&(data))>>3)
#define ISO_SCPU_INT_EN_ur0_shift                                                    (2)
#define ISO_SCPU_INT_EN_ur0_mask                                                     (0x00000004)
#define ISO_SCPU_INT_EN_ur0(data)                                                    (0x00000004&((data)<<2))
#define ISO_SCPU_INT_EN_ur0_src(data)                                                ((0x00000004&(data))>>2)
#define ISO_SCPU_INT_EN_get_ur0(data)                                                ((0x00000004&(data))>>2)


#define ISO_KCPU_INT_EN                                                              0x18007044
#define ISO_KCPU_INT_EN_reg_addr                                                     "0xB8007044"
#define ISO_KCPU_INT_EN_reg                                                          0xB8007044
#define set_ISO_KCPU_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_KCPU_INT_EN_reg)=data)
#define get_ISO_KCPU_INT_EN_reg   (*((volatile unsigned int*) ISO_KCPU_INT_EN_reg))
#define ISO_KCPU_INT_EN_inst_adr                                                     "0x0011"
#define ISO_KCPU_INT_EN_inst                                                         0x0011
#define ISO_KCPU_INT_EN_cec_shift                                                    (22)
#define ISO_KCPU_INT_EN_cec_mask                                                     (0x00400000)
#define ISO_KCPU_INT_EN_cec(data)                                                    (0x00400000&((data)<<22))
#define ISO_KCPU_INT_EN_cec_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_KCPU_INT_EN_get_cec(data)                                                ((0x00400000&(data))>>22)
#define ISO_KCPU_INT_EN_gpioda_shift                                                 (20)
#define ISO_KCPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define ISO_KCPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define ISO_KCPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_KCPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define ISO_KCPU_INT_EN_gpioa_shift                                                  (19)
#define ISO_KCPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define ISO_KCPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define ISO_KCPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_KCPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define ISO_KCPU_INT_EN_vfd_ardswda_shift                                            (18)
#define ISO_KCPU_INT_EN_vfd_ardswda_mask                                             (0x00040000)
#define ISO_KCPU_INT_EN_vfd_ardswda(data)                                            (0x00040000&((data)<<18))
#define ISO_KCPU_INT_EN_vfd_ardswda_src(data)                                        ((0x00040000&(data))>>18)
#define ISO_KCPU_INT_EN_get_vfd_ardswda(data)                                        ((0x00040000&(data))>>18)
#define ISO_KCPU_INT_EN_vfd_ardswa_shift                                             (17)
#define ISO_KCPU_INT_EN_vfd_ardswa_mask                                              (0x00020000)
#define ISO_KCPU_INT_EN_vfd_ardswa(data)                                             (0x00020000&((data)<<17))
#define ISO_KCPU_INT_EN_vfd_ardswa_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_KCPU_INT_EN_get_vfd_ardswa(data)                                         ((0x00020000&(data))>>17)
#define ISO_KCPU_INT_EN_vfd_ardkpadda_shift                                          (16)
#define ISO_KCPU_INT_EN_vfd_ardkpadda_mask                                           (0x00010000)
#define ISO_KCPU_INT_EN_vfd_ardkpadda(data)                                          (0x00010000&((data)<<16))
#define ISO_KCPU_INT_EN_vfd_ardkpadda_src(data)                                      ((0x00010000&(data))>>16)
#define ISO_KCPU_INT_EN_get_vfd_ardkpadda(data)                                      ((0x00010000&(data))>>16)
#define ISO_KCPU_INT_EN_vfd_ardkpada_shift                                           (15)
#define ISO_KCPU_INT_EN_vfd_ardkpada_mask                                            (0x00008000)
#define ISO_KCPU_INT_EN_vfd_ardkpada(data)                                           (0x00008000&((data)<<15))
#define ISO_KCPU_INT_EN_vfd_ardkpada_src(data)                                       ((0x00008000&(data))>>15)
#define ISO_KCPU_INT_EN_get_vfd_ardkpada(data)                                       ((0x00008000&(data))>>15)
#define ISO_KCPU_INT_EN_vfd_wdone_shift                                              (14)
#define ISO_KCPU_INT_EN_vfd_wdone_mask                                               (0x00004000)
#define ISO_KCPU_INT_EN_vfd_wdone(data)                                              (0x00004000&((data)<<14))
#define ISO_KCPU_INT_EN_vfd_wdone_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_KCPU_INT_EN_get_vfd_wdone(data)                                          ((0x00004000&(data))>>14)
#define ISO_KCPU_INT_EN_rtc_alarm_shift                                              (13)
#define ISO_KCPU_INT_EN_rtc_alarm_mask                                               (0x00002000)
#define ISO_KCPU_INT_EN_rtc_alarm(data)                                              (0x00002000&((data)<<13))
#define ISO_KCPU_INT_EN_rtc_alarm_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_KCPU_INT_EN_get_rtc_alarm(data)                                          ((0x00002000&(data))>>13)
#define ISO_KCPU_INT_EN_rtc_hsec_shift                                               (12)
#define ISO_KCPU_INT_EN_rtc_hsec_mask                                                (0x00001000)
#define ISO_KCPU_INT_EN_rtc_hsec(data)                                               (0x00001000&((data)<<12))
#define ISO_KCPU_INT_EN_rtc_hsec_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_KCPU_INT_EN_get_rtc_hsec(data)                                           ((0x00001000&(data))>>12)
#define ISO_KCPU_INT_EN_ur1_to_shift                                                 (6)
#define ISO_KCPU_INT_EN_ur1_to_mask                                                  (0x00000040)
#define ISO_KCPU_INT_EN_ur1_to(data)                                                 (0x00000040&((data)<<6))
#define ISO_KCPU_INT_EN_ur1_to_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_KCPU_INT_EN_get_ur1_to(data)                                             ((0x00000040&(data))>>6)
#define ISO_KCPU_INT_EN_irda_shift                                                   (5)
#define ISO_KCPU_INT_EN_irda_mask                                                    (0x00000020)
#define ISO_KCPU_INT_EN_irda(data)                                                   (0x00000020&((data)<<5))
#define ISO_KCPU_INT_EN_irda_src(data)                                               ((0x00000020&(data))>>5)
#define ISO_KCPU_INT_EN_get_irda(data)                                               ((0x00000020&(data))>>5)
#define ISO_KCPU_INT_EN_ur2_shift                                                    (4)
#define ISO_KCPU_INT_EN_ur2_mask                                                     (0x00000010)
#define ISO_KCPU_INT_EN_ur2(data)                                                    (0x00000010&((data)<<4))
#define ISO_KCPU_INT_EN_ur2_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_KCPU_INT_EN_get_ur2(data)                                                ((0x00000010&(data))>>4)
#define ISO_KCPU_INT_EN_ur1_shift                                                    (3)
#define ISO_KCPU_INT_EN_ur1_mask                                                     (0x00000008)
#define ISO_KCPU_INT_EN_ur1(data)                                                    (0x00000008&((data)<<3))
#define ISO_KCPU_INT_EN_ur1_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_KCPU_INT_EN_get_ur1(data)                                                ((0x00000008&(data))>>3)
#define ISO_KCPU_INT_EN_ur0_shift                                                    (2)
#define ISO_KCPU_INT_EN_ur0_mask                                                     (0x00000004)
#define ISO_KCPU_INT_EN_ur0(data)                                                    (0x00000004&((data)<<2))
#define ISO_KCPU_INT_EN_ur0_src(data)                                                ((0x00000004&(data))>>2)
#define ISO_KCPU_INT_EN_get_ur0(data)                                                ((0x00000004&(data))>>2)


#define ISO_ACPU_INT_EN                                                              0x18007048
#define ISO_ACPU_INT_EN_reg_addr                                                     "0xB8007048"
#define ISO_ACPU_INT_EN_reg                                                          0xB8007048
#define set_ISO_ACPU_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_ACPU_INT_EN_reg)=data)
#define get_ISO_ACPU_INT_EN_reg   (*((volatile unsigned int*) ISO_ACPU_INT_EN_reg))
#define ISO_ACPU_INT_EN_inst_adr                                                     "0x0012"
#define ISO_ACPU_INT_EN_inst                                                         0x0012
#define ISO_ACPU_INT_EN_cec_shift                                                    (22)
#define ISO_ACPU_INT_EN_cec_mask                                                     (0x00400000)
#define ISO_ACPU_INT_EN_cec(data)                                                    (0x00400000&((data)<<22))
#define ISO_ACPU_INT_EN_cec_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_ACPU_INT_EN_get_cec(data)                                                ((0x00400000&(data))>>22)
#define ISO_ACPU_INT_EN_gpioda_shift                                                 (20)
#define ISO_ACPU_INT_EN_gpioda_mask                                                  (0x00100000)
#define ISO_ACPU_INT_EN_gpioda(data)                                                 (0x00100000&((data)<<20))
#define ISO_ACPU_INT_EN_gpioda_src(data)                                             ((0x00100000&(data))>>20)
#define ISO_ACPU_INT_EN_get_gpioda(data)                                             ((0x00100000&(data))>>20)
#define ISO_ACPU_INT_EN_gpioa_shift                                                  (19)
#define ISO_ACPU_INT_EN_gpioa_mask                                                   (0x00080000)
#define ISO_ACPU_INT_EN_gpioa(data)                                                  (0x00080000&((data)<<19))
#define ISO_ACPU_INT_EN_gpioa_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_ACPU_INT_EN_get_gpioa(data)                                              ((0x00080000&(data))>>19)
#define ISO_ACPU_INT_EN_vfd_ardswda_shift                                            (18)
#define ISO_ACPU_INT_EN_vfd_ardswda_mask                                             (0x00040000)
#define ISO_ACPU_INT_EN_vfd_ardswda(data)                                            (0x00040000&((data)<<18))
#define ISO_ACPU_INT_EN_vfd_ardswda_src(data)                                        ((0x00040000&(data))>>18)
#define ISO_ACPU_INT_EN_get_vfd_ardswda(data)                                        ((0x00040000&(data))>>18)
#define ISO_ACPU_INT_EN_vfd_ardswa_shift                                             (17)
#define ISO_ACPU_INT_EN_vfd_ardswa_mask                                              (0x00020000)
#define ISO_ACPU_INT_EN_vfd_ardswa(data)                                             (0x00020000&((data)<<17))
#define ISO_ACPU_INT_EN_vfd_ardswa_src(data)                                         ((0x00020000&(data))>>17)
#define ISO_ACPU_INT_EN_get_vfd_ardswa(data)                                         ((0x00020000&(data))>>17)
#define ISO_ACPU_INT_EN_vfd_ardkpadda_shift                                          (16)
#define ISO_ACPU_INT_EN_vfd_ardkpadda_mask                                           (0x00010000)
#define ISO_ACPU_INT_EN_vfd_ardkpadda(data)                                          (0x00010000&((data)<<16))
#define ISO_ACPU_INT_EN_vfd_ardkpadda_src(data)                                      ((0x00010000&(data))>>16)
#define ISO_ACPU_INT_EN_get_vfd_ardkpadda(data)                                      ((0x00010000&(data))>>16)
#define ISO_ACPU_INT_EN_vfd_ardkpada_shift                                           (15)
#define ISO_ACPU_INT_EN_vfd_ardkpada_mask                                            (0x00008000)
#define ISO_ACPU_INT_EN_vfd_ardkpada(data)                                           (0x00008000&((data)<<15))
#define ISO_ACPU_INT_EN_vfd_ardkpada_src(data)                                       ((0x00008000&(data))>>15)
#define ISO_ACPU_INT_EN_get_vfd_ardkpada(data)                                       ((0x00008000&(data))>>15)
#define ISO_ACPU_INT_EN_vfd_wdone_shift                                              (14)
#define ISO_ACPU_INT_EN_vfd_wdone_mask                                               (0x00004000)
#define ISO_ACPU_INT_EN_vfd_wdone(data)                                              (0x00004000&((data)<<14))
#define ISO_ACPU_INT_EN_vfd_wdone_src(data)                                          ((0x00004000&(data))>>14)
#define ISO_ACPU_INT_EN_get_vfd_wdone(data)                                          ((0x00004000&(data))>>14)
#define ISO_ACPU_INT_EN_rtc_alarm_shift                                              (13)
#define ISO_ACPU_INT_EN_rtc_alarm_mask                                               (0x00002000)
#define ISO_ACPU_INT_EN_rtc_alarm(data)                                              (0x00002000&((data)<<13))
#define ISO_ACPU_INT_EN_rtc_alarm_src(data)                                          ((0x00002000&(data))>>13)
#define ISO_ACPU_INT_EN_get_rtc_alarm(data)                                          ((0x00002000&(data))>>13)
#define ISO_ACPU_INT_EN_rtc_hsec_shift                                               (12)
#define ISO_ACPU_INT_EN_rtc_hsec_mask                                                (0x00001000)
#define ISO_ACPU_INT_EN_rtc_hsec(data)                                               (0x00001000&((data)<<12))
#define ISO_ACPU_INT_EN_rtc_hsec_src(data)                                           ((0x00001000&(data))>>12)
#define ISO_ACPU_INT_EN_get_rtc_hsec(data)                                           ((0x00001000&(data))>>12)
#define ISO_ACPU_INT_EN_ur1_to_shift                                                 (6)
#define ISO_ACPU_INT_EN_ur1_to_mask                                                  (0x00000040)
#define ISO_ACPU_INT_EN_ur1_to(data)                                                 (0x00000040&((data)<<6))
#define ISO_ACPU_INT_EN_ur1_to_src(data)                                             ((0x00000040&(data))>>6)
#define ISO_ACPU_INT_EN_get_ur1_to(data)                                             ((0x00000040&(data))>>6)
#define ISO_ACPU_INT_EN_irda_shift                                                   (5)
#define ISO_ACPU_INT_EN_irda_mask                                                    (0x00000020)
#define ISO_ACPU_INT_EN_irda(data)                                                   (0x00000020&((data)<<5))
#define ISO_ACPU_INT_EN_irda_src(data)                                               ((0x00000020&(data))>>5)
#define ISO_ACPU_INT_EN_get_irda(data)                                               ((0x00000020&(data))>>5)
#define ISO_ACPU_INT_EN_ur2_shift                                                    (4)
#define ISO_ACPU_INT_EN_ur2_mask                                                     (0x00000010)
#define ISO_ACPU_INT_EN_ur2(data)                                                    (0x00000010&((data)<<4))
#define ISO_ACPU_INT_EN_ur2_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_ACPU_INT_EN_get_ur2(data)                                                ((0x00000010&(data))>>4)
#define ISO_ACPU_INT_EN_ur1_shift                                                    (3)
#define ISO_ACPU_INT_EN_ur1_mask                                                     (0x00000008)
#define ISO_ACPU_INT_EN_ur1(data)                                                    (0x00000008&((data)<<3))
#define ISO_ACPU_INT_EN_ur1_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_ACPU_INT_EN_get_ur1(data)                                                ((0x00000008&(data))>>3)
#define ISO_ACPU_INT_EN_ur0_shift                                                    (2)
#define ISO_ACPU_INT_EN_ur0_mask                                                     (0x00000004)
#define ISO_ACPU_INT_EN_ur0(data)                                                    (0x00000004&((data)<<2))
#define ISO_ACPU_INT_EN_ur0_src(data)                                                ((0x00000004&(data))>>2)
#define ISO_ACPU_INT_EN_get_ur0(data)                                                ((0x00000004&(data))>>2)


#define ISO_CPU_ST1                                                                  0x1800704C
#define ISO_CPU_ST1_reg_addr                                                         "0xB800704C"
#define ISO_CPU_ST1_reg                                                              0xB800704C
#define set_ISO_CPU_ST1_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST1_reg)=data)
#define get_ISO_CPU_ST1_reg   (*((volatile unsigned int*) ISO_CPU_ST1_reg))
#define ISO_CPU_ST1_inst_adr                                                         "0x0013"
#define ISO_CPU_ST1_inst                                                             0x0013
#define ISO_CPU_ST1_acpu_boot_info_shift                                             (0)
#define ISO_CPU_ST1_acpu_boot_info_mask                                              (0xFFFFFFFF)
#define ISO_CPU_ST1_acpu_boot_info(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_CPU_ST1_acpu_boot_info_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_CPU_ST1_get_acpu_boot_info(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_CPU_ST1V                                                                 0x18007050
#define ISO_CPU_ST1V_reg_addr                                                        "0xB8007050"
#define ISO_CPU_ST1V_reg                                                             0xB8007050
#define set_ISO_CPU_ST1V_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST1V_reg)=data)
#define get_ISO_CPU_ST1V_reg   (*((volatile unsigned int*) ISO_CPU_ST1V_reg))
#define ISO_CPU_ST1V_inst_adr                                                        "0x0014"
#define ISO_CPU_ST1V_inst                                                            0x0014
#define ISO_CPU_ST1V_acpu_boot_info_valid_shift                                      (0)
#define ISO_CPU_ST1V_acpu_boot_info_valid_mask                                       (0x00000001)
#define ISO_CPU_ST1V_acpu_boot_info_valid(data)                                      (0x00000001&((data)<<0))
#define ISO_CPU_ST1V_acpu_boot_info_valid_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_CPU_ST1V_get_acpu_boot_info_valid(data)                                  ((0x00000001&(data))>>0)


#define ISO_DUMMY1                                                                   0x18007054
#define ISO_DUMMY1_reg_addr                                                          "0xB8007054"
#define ISO_DUMMY1_reg                                                               0xB8007054
#define set_ISO_DUMMY1_reg(data)   (*((volatile unsigned int*) ISO_DUMMY1_reg)=data)
#define get_ISO_DUMMY1_reg   (*((volatile unsigned int*) ISO_DUMMY1_reg))
#define ISO_DUMMY1_inst_adr                                                          "0x0015"
#define ISO_DUMMY1_inst                                                              0x0015
#define ISO_DUMMY1_rvd31_shift                                                       (31)
#define ISO_DUMMY1_rvd31_mask                                                        (0x80000000)
#define ISO_DUMMY1_rvd31(data)                                                       (0x80000000&((data)<<31))
#define ISO_DUMMY1_rvd31_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY1_get_rvd31(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY1_rvd30_shift                                                       (30)
#define ISO_DUMMY1_rvd30_mask                                                        (0x40000000)
#define ISO_DUMMY1_rvd30(data)                                                       (0x40000000&((data)<<30))
#define ISO_DUMMY1_rvd30_src(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY1_get_rvd30(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY1_rvd29_shift                                                       (29)
#define ISO_DUMMY1_rvd29_mask                                                        (0x20000000)
#define ISO_DUMMY1_rvd29(data)                                                       (0x20000000&((data)<<29))
#define ISO_DUMMY1_rvd29_src(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY1_get_rvd29(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY1_rvd28_shift                                                       (28)
#define ISO_DUMMY1_rvd28_mask                                                        (0x10000000)
#define ISO_DUMMY1_rvd28(data)                                                       (0x10000000&((data)<<28))
#define ISO_DUMMY1_rvd28_src(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY1_get_rvd28(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY1_rvd27_shift                                                       (27)
#define ISO_DUMMY1_rvd27_mask                                                        (0x08000000)
#define ISO_DUMMY1_rvd27(data)                                                       (0x08000000&((data)<<27))
#define ISO_DUMMY1_rvd27_src(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY1_get_rvd27(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY1_rvd26_shift                                                       (26)
#define ISO_DUMMY1_rvd26_mask                                                        (0x04000000)
#define ISO_DUMMY1_rvd26(data)                                                       (0x04000000&((data)<<26))
#define ISO_DUMMY1_rvd26_src(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY1_get_rvd26(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY1_rvd25_shift                                                       (25)
#define ISO_DUMMY1_rvd25_mask                                                        (0x02000000)
#define ISO_DUMMY1_rvd25(data)                                                       (0x02000000&((data)<<25))
#define ISO_DUMMY1_rvd25_src(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY1_get_rvd25(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY1_rvd24_shift                                                       (24)
#define ISO_DUMMY1_rvd24_mask                                                        (0x01000000)
#define ISO_DUMMY1_rvd24(data)                                                       (0x01000000&((data)<<24))
#define ISO_DUMMY1_rvd24_src(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY1_get_rvd24(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY1_rvd23_shift                                                       (23)
#define ISO_DUMMY1_rvd23_mask                                                        (0x00800000)
#define ISO_DUMMY1_rvd23(data)                                                       (0x00800000&((data)<<23))
#define ISO_DUMMY1_rvd23_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY1_get_rvd23(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY1_rvd22_shift                                                       (22)
#define ISO_DUMMY1_rvd22_mask                                                        (0x00400000)
#define ISO_DUMMY1_rvd22(data)                                                       (0x00400000&((data)<<22))
#define ISO_DUMMY1_rvd22_src(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY1_get_rvd22(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY1_rvd21_shift                                                       (21)
#define ISO_DUMMY1_rvd21_mask                                                        (0x00200000)
#define ISO_DUMMY1_rvd21(data)                                                       (0x00200000&((data)<<21))
#define ISO_DUMMY1_rvd21_src(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY1_get_rvd21(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY1_rvd20_shift                                                       (20)
#define ISO_DUMMY1_rvd20_mask                                                        (0x00100000)
#define ISO_DUMMY1_rvd20(data)                                                       (0x00100000&((data)<<20))
#define ISO_DUMMY1_rvd20_src(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY1_get_rvd20(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY1_rvd19_shift                                                       (19)
#define ISO_DUMMY1_rvd19_mask                                                        (0x00080000)
#define ISO_DUMMY1_rvd19(data)                                                       (0x00080000&((data)<<19))
#define ISO_DUMMY1_rvd19_src(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY1_get_rvd19(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY1_rvd18_shift                                                       (18)
#define ISO_DUMMY1_rvd18_mask                                                        (0x00040000)
#define ISO_DUMMY1_rvd18(data)                                                       (0x00040000&((data)<<18))
#define ISO_DUMMY1_rvd18_src(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY1_get_rvd18(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY1_rvd17_shift                                                       (17)
#define ISO_DUMMY1_rvd17_mask                                                        (0x00020000)
#define ISO_DUMMY1_rvd17(data)                                                       (0x00020000&((data)<<17))
#define ISO_DUMMY1_rvd17_src(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY1_get_rvd17(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY1_rvd16_shift                                                       (16)
#define ISO_DUMMY1_rvd16_mask                                                        (0x00010000)
#define ISO_DUMMY1_rvd16(data)                                                       (0x00010000&((data)<<16))
#define ISO_DUMMY1_rvd16_src(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY1_get_rvd16(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY1_rvd15_shift                                                       (15)
#define ISO_DUMMY1_rvd15_mask                                                        (0x00008000)
#define ISO_DUMMY1_rvd15(data)                                                       (0x00008000&((data)<<15))
#define ISO_DUMMY1_rvd15_src(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY1_get_rvd15(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY1_rvd14_shift                                                       (14)
#define ISO_DUMMY1_rvd14_mask                                                        (0x00004000)
#define ISO_DUMMY1_rvd14(data)                                                       (0x00004000&((data)<<14))
#define ISO_DUMMY1_rvd14_src(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY1_get_rvd14(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY1_rvd13_shift                                                       (13)
#define ISO_DUMMY1_rvd13_mask                                                        (0x00002000)
#define ISO_DUMMY1_rvd13(data)                                                       (0x00002000&((data)<<13))
#define ISO_DUMMY1_rvd13_src(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY1_get_rvd13(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY1_rvd12_shift                                                       (12)
#define ISO_DUMMY1_rvd12_mask                                                        (0x00001000)
#define ISO_DUMMY1_rvd12(data)                                                       (0x00001000&((data)<<12))
#define ISO_DUMMY1_rvd12_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY1_get_rvd12(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY1_rvd11_shift                                                       (11)
#define ISO_DUMMY1_rvd11_mask                                                        (0x00000800)
#define ISO_DUMMY1_rvd11(data)                                                       (0x00000800&((data)<<11))
#define ISO_DUMMY1_rvd11_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY1_get_rvd11(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY1_rvd10_shift                                                       (10)
#define ISO_DUMMY1_rvd10_mask                                                        (0x00000400)
#define ISO_DUMMY1_rvd10(data)                                                       (0x00000400&((data)<<10))
#define ISO_DUMMY1_rvd10_src(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY1_get_rvd10(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY1_rvd9_shift                                                        (9)
#define ISO_DUMMY1_rvd9_mask                                                         (0x00000200)
#define ISO_DUMMY1_rvd9(data)                                                        (0x00000200&((data)<<9))
#define ISO_DUMMY1_rvd9_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY1_get_rvd9(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY1_rvd8_shift                                                        (8)
#define ISO_DUMMY1_rvd8_mask                                                         (0x00000100)
#define ISO_DUMMY1_rvd8(data)                                                        (0x00000100&((data)<<8))
#define ISO_DUMMY1_rvd8_src(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY1_get_rvd8(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY1_rvd7_shift                                                        (7)
#define ISO_DUMMY1_rvd7_mask                                                         (0x00000080)
#define ISO_DUMMY1_rvd7(data)                                                        (0x00000080&((data)<<7))
#define ISO_DUMMY1_rvd7_src(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY1_get_rvd7(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY1_rvd6_shift                                                        (6)
#define ISO_DUMMY1_rvd6_mask                                                         (0x00000040)
#define ISO_DUMMY1_rvd6(data)                                                        (0x00000040&((data)<<6))
#define ISO_DUMMY1_rvd6_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY1_get_rvd6(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY1_rvd5_shift                                                        (5)
#define ISO_DUMMY1_rvd5_mask                                                         (0x00000020)
#define ISO_DUMMY1_rvd5(data)                                                        (0x00000020&((data)<<5))
#define ISO_DUMMY1_rvd5_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY1_get_rvd5(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY1_rvd4_shift                                                        (4)
#define ISO_DUMMY1_rvd4_mask                                                         (0x00000010)
#define ISO_DUMMY1_rvd4(data)                                                        (0x00000010&((data)<<4))
#define ISO_DUMMY1_rvd4_src(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY1_get_rvd4(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY1_rvd3_shift                                                        (3)
#define ISO_DUMMY1_rvd3_mask                                                         (0x00000008)
#define ISO_DUMMY1_rvd3(data)                                                        (0x00000008&((data)<<3))
#define ISO_DUMMY1_rvd3_src(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY1_get_rvd3(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY1_rvd2_shift                                                        (2)
#define ISO_DUMMY1_rvd2_mask                                                         (0x00000004)
#define ISO_DUMMY1_rvd2(data)                                                        (0x00000004&((data)<<2))
#define ISO_DUMMY1_rvd2_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY1_get_rvd2(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY1_rvd1_shift                                                        (1)
#define ISO_DUMMY1_rvd1_mask                                                         (0x00000002)
#define ISO_DUMMY1_rvd1(data)                                                        (0x00000002&((data)<<1))
#define ISO_DUMMY1_rvd1_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY1_get_rvd1(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY1_rvd0_shift                                                        (0)
#define ISO_DUMMY1_rvd0_mask                                                         (0x00000001)
#define ISO_DUMMY1_rvd0(data)                                                        (0x00000001&((data)<<0))
#define ISO_DUMMY1_rvd0_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_DUMMY1_get_rvd0(data)                                                    ((0x00000001&(data))>>0)


#define ISO_DUMMY2                                                                   0x18007058
#define ISO_DUMMY2_reg_addr                                                          "0xB8007058"
#define ISO_DUMMY2_reg                                                               0xB8007058
#define set_ISO_DUMMY2_reg(data)   (*((volatile unsigned int*) ISO_DUMMY2_reg)=data)
#define get_ISO_DUMMY2_reg   (*((volatile unsigned int*) ISO_DUMMY2_reg))
#define ISO_DUMMY2_inst_adr                                                          "0x0016"
#define ISO_DUMMY2_inst                                                              0x0016
#define ISO_DUMMY2_rvd31_shift                                                       (31)
#define ISO_DUMMY2_rvd31_mask                                                        (0x80000000)
#define ISO_DUMMY2_rvd31(data)                                                       (0x80000000&((data)<<31))
#define ISO_DUMMY2_rvd31_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY2_get_rvd31(data)                                                   ((0x80000000&(data))>>31)
#define ISO_DUMMY2_rvd30_shift                                                       (30)
#define ISO_DUMMY2_rvd30_mask                                                        (0x40000000)
#define ISO_DUMMY2_rvd30(data)                                                       (0x40000000&((data)<<30))
#define ISO_DUMMY2_rvd30_src(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY2_get_rvd30(data)                                                   ((0x40000000&(data))>>30)
#define ISO_DUMMY2_rvd29_shift                                                       (29)
#define ISO_DUMMY2_rvd29_mask                                                        (0x20000000)
#define ISO_DUMMY2_rvd29(data)                                                       (0x20000000&((data)<<29))
#define ISO_DUMMY2_rvd29_src(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY2_get_rvd29(data)                                                   ((0x20000000&(data))>>29)
#define ISO_DUMMY2_rvd28_shift                                                       (28)
#define ISO_DUMMY2_rvd28_mask                                                        (0x10000000)
#define ISO_DUMMY2_rvd28(data)                                                       (0x10000000&((data)<<28))
#define ISO_DUMMY2_rvd28_src(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY2_get_rvd28(data)                                                   ((0x10000000&(data))>>28)
#define ISO_DUMMY2_rvd27_shift                                                       (27)
#define ISO_DUMMY2_rvd27_mask                                                        (0x08000000)
#define ISO_DUMMY2_rvd27(data)                                                       (0x08000000&((data)<<27))
#define ISO_DUMMY2_rvd27_src(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY2_get_rvd27(data)                                                   ((0x08000000&(data))>>27)
#define ISO_DUMMY2_rvd26_shift                                                       (26)
#define ISO_DUMMY2_rvd26_mask                                                        (0x04000000)
#define ISO_DUMMY2_rvd26(data)                                                       (0x04000000&((data)<<26))
#define ISO_DUMMY2_rvd26_src(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY2_get_rvd26(data)                                                   ((0x04000000&(data))>>26)
#define ISO_DUMMY2_rvd25_shift                                                       (25)
#define ISO_DUMMY2_rvd25_mask                                                        (0x02000000)
#define ISO_DUMMY2_rvd25(data)                                                       (0x02000000&((data)<<25))
#define ISO_DUMMY2_rvd25_src(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY2_get_rvd25(data)                                                   ((0x02000000&(data))>>25)
#define ISO_DUMMY2_rvd24_shift                                                       (24)
#define ISO_DUMMY2_rvd24_mask                                                        (0x01000000)
#define ISO_DUMMY2_rvd24(data)                                                       (0x01000000&((data)<<24))
#define ISO_DUMMY2_rvd24_src(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY2_get_rvd24(data)                                                   ((0x01000000&(data))>>24)
#define ISO_DUMMY2_rvd23_shift                                                       (23)
#define ISO_DUMMY2_rvd23_mask                                                        (0x00800000)
#define ISO_DUMMY2_rvd23(data)                                                       (0x00800000&((data)<<23))
#define ISO_DUMMY2_rvd23_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY2_get_rvd23(data)                                                   ((0x00800000&(data))>>23)
#define ISO_DUMMY2_rvd22_shift                                                       (22)
#define ISO_DUMMY2_rvd22_mask                                                        (0x00400000)
#define ISO_DUMMY2_rvd22(data)                                                       (0x00400000&((data)<<22))
#define ISO_DUMMY2_rvd22_src(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY2_get_rvd22(data)                                                   ((0x00400000&(data))>>22)
#define ISO_DUMMY2_rvd21_shift                                                       (21)
#define ISO_DUMMY2_rvd21_mask                                                        (0x00200000)
#define ISO_DUMMY2_rvd21(data)                                                       (0x00200000&((data)<<21))
#define ISO_DUMMY2_rvd21_src(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY2_get_rvd21(data)                                                   ((0x00200000&(data))>>21)
#define ISO_DUMMY2_rvd20_shift                                                       (20)
#define ISO_DUMMY2_rvd20_mask                                                        (0x00100000)
#define ISO_DUMMY2_rvd20(data)                                                       (0x00100000&((data)<<20))
#define ISO_DUMMY2_rvd20_src(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY2_get_rvd20(data)                                                   ((0x00100000&(data))>>20)
#define ISO_DUMMY2_rvd19_shift                                                       (19)
#define ISO_DUMMY2_rvd19_mask                                                        (0x00080000)
#define ISO_DUMMY2_rvd19(data)                                                       (0x00080000&((data)<<19))
#define ISO_DUMMY2_rvd19_src(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY2_get_rvd19(data)                                                   ((0x00080000&(data))>>19)
#define ISO_DUMMY2_rvd18_shift                                                       (18)
#define ISO_DUMMY2_rvd18_mask                                                        (0x00040000)
#define ISO_DUMMY2_rvd18(data)                                                       (0x00040000&((data)<<18))
#define ISO_DUMMY2_rvd18_src(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY2_get_rvd18(data)                                                   ((0x00040000&(data))>>18)
#define ISO_DUMMY2_rvd17_shift                                                       (17)
#define ISO_DUMMY2_rvd17_mask                                                        (0x00020000)
#define ISO_DUMMY2_rvd17(data)                                                       (0x00020000&((data)<<17))
#define ISO_DUMMY2_rvd17_src(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY2_get_rvd17(data)                                                   ((0x00020000&(data))>>17)
#define ISO_DUMMY2_rvd16_shift                                                       (16)
#define ISO_DUMMY2_rvd16_mask                                                        (0x00010000)
#define ISO_DUMMY2_rvd16(data)                                                       (0x00010000&((data)<<16))
#define ISO_DUMMY2_rvd16_src(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY2_get_rvd16(data)                                                   ((0x00010000&(data))>>16)
#define ISO_DUMMY2_rvd15_shift                                                       (15)
#define ISO_DUMMY2_rvd15_mask                                                        (0x00008000)
#define ISO_DUMMY2_rvd15(data)                                                       (0x00008000&((data)<<15))
#define ISO_DUMMY2_rvd15_src(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY2_get_rvd15(data)                                                   ((0x00008000&(data))>>15)
#define ISO_DUMMY2_rvd14_shift                                                       (14)
#define ISO_DUMMY2_rvd14_mask                                                        (0x00004000)
#define ISO_DUMMY2_rvd14(data)                                                       (0x00004000&((data)<<14))
#define ISO_DUMMY2_rvd14_src(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY2_get_rvd14(data)                                                   ((0x00004000&(data))>>14)
#define ISO_DUMMY2_rvd13_shift                                                       (13)
#define ISO_DUMMY2_rvd13_mask                                                        (0x00002000)
#define ISO_DUMMY2_rvd13(data)                                                       (0x00002000&((data)<<13))
#define ISO_DUMMY2_rvd13_src(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY2_get_rvd13(data)                                                   ((0x00002000&(data))>>13)
#define ISO_DUMMY2_rvd12_shift                                                       (12)
#define ISO_DUMMY2_rvd12_mask                                                        (0x00001000)
#define ISO_DUMMY2_rvd12(data)                                                       (0x00001000&((data)<<12))
#define ISO_DUMMY2_rvd12_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY2_get_rvd12(data)                                                   ((0x00001000&(data))>>12)
#define ISO_DUMMY2_rvd11_shift                                                       (11)
#define ISO_DUMMY2_rvd11_mask                                                        (0x00000800)
#define ISO_DUMMY2_rvd11(data)                                                       (0x00000800&((data)<<11))
#define ISO_DUMMY2_rvd11_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY2_get_rvd11(data)                                                   ((0x00000800&(data))>>11)
#define ISO_DUMMY2_rvd10_shift                                                       (10)
#define ISO_DUMMY2_rvd10_mask                                                        (0x00000400)
#define ISO_DUMMY2_rvd10(data)                                                       (0x00000400&((data)<<10))
#define ISO_DUMMY2_rvd10_src(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY2_get_rvd10(data)                                                   ((0x00000400&(data))>>10)
#define ISO_DUMMY2_rvd9_shift                                                        (9)
#define ISO_DUMMY2_rvd9_mask                                                         (0x00000200)
#define ISO_DUMMY2_rvd9(data)                                                        (0x00000200&((data)<<9))
#define ISO_DUMMY2_rvd9_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY2_get_rvd9(data)                                                    ((0x00000200&(data))>>9)
#define ISO_DUMMY2_rvd8_shift                                                        (8)
#define ISO_DUMMY2_rvd8_mask                                                         (0x00000100)
#define ISO_DUMMY2_rvd8(data)                                                        (0x00000100&((data)<<8))
#define ISO_DUMMY2_rvd8_src(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY2_get_rvd8(data)                                                    ((0x00000100&(data))>>8)
#define ISO_DUMMY2_rvd7_shift                                                        (7)
#define ISO_DUMMY2_rvd7_mask                                                         (0x00000080)
#define ISO_DUMMY2_rvd7(data)                                                        (0x00000080&((data)<<7))
#define ISO_DUMMY2_rvd7_src(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY2_get_rvd7(data)                                                    ((0x00000080&(data))>>7)
#define ISO_DUMMY2_rvd6_shift                                                        (6)
#define ISO_DUMMY2_rvd6_mask                                                         (0x00000040)
#define ISO_DUMMY2_rvd6(data)                                                        (0x00000040&((data)<<6))
#define ISO_DUMMY2_rvd6_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY2_get_rvd6(data)                                                    ((0x00000040&(data))>>6)
#define ISO_DUMMY2_rvd5_shift                                                        (5)
#define ISO_DUMMY2_rvd5_mask                                                         (0x00000020)
#define ISO_DUMMY2_rvd5(data)                                                        (0x00000020&((data)<<5))
#define ISO_DUMMY2_rvd5_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY2_get_rvd5(data)                                                    ((0x00000020&(data))>>5)
#define ISO_DUMMY2_rvd4_shift                                                        (4)
#define ISO_DUMMY2_rvd4_mask                                                         (0x00000010)
#define ISO_DUMMY2_rvd4(data)                                                        (0x00000010&((data)<<4))
#define ISO_DUMMY2_rvd4_src(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY2_get_rvd4(data)                                                    ((0x00000010&(data))>>4)
#define ISO_DUMMY2_rvd3_shift                                                        (3)
#define ISO_DUMMY2_rvd3_mask                                                         (0x00000008)
#define ISO_DUMMY2_rvd3(data)                                                        (0x00000008&((data)<<3))
#define ISO_DUMMY2_rvd3_src(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY2_get_rvd3(data)                                                    ((0x00000008&(data))>>3)
#define ISO_DUMMY2_rvd2_shift                                                        (2)
#define ISO_DUMMY2_rvd2_mask                                                         (0x00000004)
#define ISO_DUMMY2_rvd2(data)                                                        (0x00000004&((data)<<2))
#define ISO_DUMMY2_rvd2_src(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY2_get_rvd2(data)                                                    ((0x00000004&(data))>>2)
#define ISO_DUMMY2_rvd1_shift                                                        (1)
#define ISO_DUMMY2_rvd1_mask                                                         (0x00000002)
#define ISO_DUMMY2_rvd1(data)                                                        (0x00000002&((data)<<1))
#define ISO_DUMMY2_rvd1_src(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY2_get_rvd1(data)                                                    ((0x00000002&(data))>>1)
#define ISO_DUMMY2_rvd0_shift                                                        (0)
#define ISO_DUMMY2_rvd0_mask                                                         (0x00000001)
#define ISO_DUMMY2_rvd0(data)                                                        (0x00000001&((data)<<0))
#define ISO_DUMMY2_rvd0_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_DUMMY2_get_rvd0(data)                                                    ((0x00000001&(data))>>0)


#define ISO_UR_CTRL                                                                  0x18007060
#define ISO_UR_CTRL_reg_addr                                                         "0xB8007060"
#define ISO_UR_CTRL_reg                                                              0xB8007060
#define set_ISO_UR_CTRL_reg(data)   (*((volatile unsigned int*) ISO_UR_CTRL_reg)=data)
#define get_ISO_UR_CTRL_reg   (*((volatile unsigned int*) ISO_UR_CTRL_reg))
#define ISO_UR_CTRL_inst_adr                                                         "0x0018"
#define ISO_UR_CTRL_inst                                                             0x0018
#define ISO_UR_CTRL_rvd3_shift                                                       (29)
#define ISO_UR_CTRL_rvd3_mask                                                        (0xE0000000)
#define ISO_UR_CTRL_rvd3(data)                                                       (0xE0000000&((data)<<29))
#define ISO_UR_CTRL_rvd3_src(data)                                                   ((0xE0000000&(data))>>29)
#define ISO_UR_CTRL_get_rvd3(data)                                                   ((0xE0000000&(data))>>29)
#define ISO_UR_CTRL_ur2_flow_pol_shift                                               (28)
#define ISO_UR_CTRL_ur2_flow_pol_mask                                                (0x10000000)
#define ISO_UR_CTRL_ur2_flow_pol(data)                                               (0x10000000&((data)<<28))
#define ISO_UR_CTRL_ur2_flow_pol_src(data)                                           ((0x10000000&(data))>>28)
#define ISO_UR_CTRL_get_ur2_flow_pol(data)                                           ((0x10000000&(data))>>28)
#define ISO_UR_CTRL_to_len_shift                                                     (20)
#define ISO_UR_CTRL_to_len_mask                                                      (0x0FF00000)
#define ISO_UR_CTRL_to_len(data)                                                     (0x0FF00000&((data)<<20))
#define ISO_UR_CTRL_to_len_src(data)                                                 ((0x0FF00000&(data))>>20)
#define ISO_UR_CTRL_get_to_len(data)                                                 ((0x0FF00000&(data))>>20)
#define ISO_UR_CTRL_to_int_en_shift                                                  (19)
#define ISO_UR_CTRL_to_int_en_mask                                                   (0x00080000)
#define ISO_UR_CTRL_to_int_en(data)                                                  (0x00080000&((data)<<19))
#define ISO_UR_CTRL_to_int_en_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_UR_CTRL_get_to_int_en(data)                                              ((0x00080000&(data))>>19)
#define ISO_UR_CTRL_toauareq_shift                                                   (18)
#define ISO_UR_CTRL_toauareq_mask                                                    (0x00040000)
#define ISO_UR_CTRL_toauareq(data)                                                   (0x00040000&((data)<<18))
#define ISO_UR_CTRL_toauareq_src(data)                                               ((0x00040000&(data))>>18)
#define ISO_UR_CTRL_get_toauareq(data)                                               ((0x00040000&(data))>>18)
#define ISO_UR_CTRL_ur1_flow_pol_shift                                               (17)
#define ISO_UR_CTRL_ur1_flow_pol_mask                                                (0x00020000)
#define ISO_UR_CTRL_ur1_flow_pol(data)                                               (0x00020000&((data)<<17))
#define ISO_UR_CTRL_ur1_flow_pol_src(data)                                           ((0x00020000&(data))>>17)
#define ISO_UR_CTRL_get_ur1_flow_pol(data)                                           ((0x00020000&(data))>>17)
#define ISO_UR_CTRL_mdifen_shift                                                     (16)
#define ISO_UR_CTRL_mdifen_mask                                                      (0x00010000)
#define ISO_UR_CTRL_mdifen(data)                                                     (0x00010000&((data)<<16))
#define ISO_UR_CTRL_mdifen_src(data)                                                 ((0x00010000&(data))>>16)
#define ISO_UR_CTRL_get_mdifen(data)                                                 ((0x00010000&(data))>>16)
#define ISO_UR_CTRL_txempthr_shift                                                   (8)
#define ISO_UR_CTRL_txempthr_mask                                                    (0x00003F00)
#define ISO_UR_CTRL_txempthr(data)                                                   (0x00003F00&((data)<<8))
#define ISO_UR_CTRL_txempthr_src(data)                                               ((0x00003F00&(data))>>8)
#define ISO_UR_CTRL_get_txempthr(data)                                               ((0x00003F00&(data))>>8)
#define ISO_UR_CTRL_rxfulthr_shift                                                   (0)
#define ISO_UR_CTRL_rxfulthr_mask                                                    (0x0000003F)
#define ISO_UR_CTRL_rxfulthr(data)                                                   (0x0000003F&((data)<<0))
#define ISO_UR_CTRL_rxfulthr_src(data)                                               ((0x0000003F&(data))>>0)
#define ISO_UR_CTRL_get_rxfulthr(data)                                               ((0x0000003F&(data))>>0)


#define ISO_UR_STS                                                                   0x18007064
#define ISO_UR_STS_reg_addr                                                          "0xB8007064"
#define ISO_UR_STS_reg                                                               0xB8007064
#define set_ISO_UR_STS_reg(data)   (*((volatile unsigned int*) ISO_UR_STS_reg)=data)
#define get_ISO_UR_STS_reg   (*((volatile unsigned int*) ISO_UR_STS_reg))
#define ISO_UR_STS_inst_adr                                                          "0x0019"
#define ISO_UR_STS_inst                                                              0x0019
#define ISO_UR_STS_rx_wrd_count_shift                                                (8)
#define ISO_UR_STS_rx_wrd_count_mask                                                 (0x00001F00)
#define ISO_UR_STS_rx_wrd_count(data)                                                (0x00001F00&((data)<<8))
#define ISO_UR_STS_rx_wrd_count_src(data)                                            ((0x00001F00&(data))>>8)
#define ISO_UR_STS_get_rx_wrd_count(data)                                            ((0x00001F00&(data))>>8)
#define ISO_UR_STS_tx_wrd_count_shift                                                (0)
#define ISO_UR_STS_tx_wrd_count_mask                                                 (0x0000001F)
#define ISO_UR_STS_tx_wrd_count(data)                                                (0x0000001F&((data)<<0))
#define ISO_UR_STS_tx_wrd_count_src(data)                                            ((0x0000001F&(data))>>0)
#define ISO_UR_STS_get_tx_wrd_count(data)                                            ((0x0000001F&(data))>>0)


#define ISO_LPI                                                                      0x18007068
#define ISO_LPI_reg_addr                                                             "0xB8007068"
#define ISO_LPI_reg                                                                  0xB8007068
#define set_ISO_LPI_reg(data)   (*((volatile unsigned int*) ISO_LPI_reg)=data)
#define get_ISO_LPI_reg   (*((volatile unsigned int*) ISO_LPI_reg))
#define ISO_LPI_inst_adr                                                             "0x001A"
#define ISO_LPI_inst                                                                 0x001A
#define ISO_LPI_ir_tx_shift                                                          (1)
#define ISO_LPI_ir_tx_mask                                                           (0x00000002)
#define ISO_LPI_ir_tx(data)                                                          (0x00000002&((data)<<1))
#define ISO_LPI_ir_tx_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_LPI_get_ir_tx(data)                                                      ((0x00000002&(data))>>1)
#define ISO_LPI_ir_raw_shift                                                         (0)
#define ISO_LPI_ir_raw_mask                                                          (0x00000001)
#define ISO_LPI_ir_raw(data)                                                         (0x00000001&((data)<<0))
#define ISO_LPI_ir_raw_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_LPI_get_ir_raw(data)                                                     ((0x00000001&(data))>>0)


#define ISO_WD                                                                       0x1800706C
#define ISO_WD_reg_addr                                                              "0xB800706C"
#define ISO_WD_reg                                                                   0xB800706C
#define set_ISO_WD_reg(data)   (*((volatile unsigned int*) ISO_WD_reg)=data)
#define get_ISO_WD_reg   (*((volatile unsigned int*) ISO_WD_reg))
#define ISO_WD_inst_adr                                                              "0x001B"
#define ISO_WD_inst                                                                  0x001B
#define ISO_WD_cnt_wait_pwr_shift                                                    (0)
#define ISO_WD_cnt_wait_pwr_mask                                                     (0x0000FFFF)
#define ISO_WD_cnt_wait_pwr(data)                                                    (0x0000FFFF&((data)<<0))
#define ISO_WD_cnt_wait_pwr_src(data)                                                ((0x0000FFFF&(data))>>0)
#define ISO_WD_get_cnt_wait_pwr(data)                                                ((0x0000FFFF&(data))>>0)


#define ISO_SC_KEY03                                                                 0x18007070
#define ISO_SC_KEY03_reg_addr                                                        "0xB8007070"
#define ISO_SC_KEY03_reg                                                             0xB8007070
#define set_ISO_SC_KEY03_reg(data)   (*((volatile unsigned int*) ISO_SC_KEY03_reg)=data)
#define get_ISO_SC_KEY03_reg   (*((volatile unsigned int*) ISO_SC_KEY03_reg))
#define ISO_SC_KEY03_inst_adr                                                        "0x001C"
#define ISO_SC_KEY03_inst                                                            0x001C
#define ISO_SC_KEY03_sc_key_3_shift                                                  (24)
#define ISO_SC_KEY03_sc_key_3_mask                                                   (0xFF000000)
#define ISO_SC_KEY03_sc_key_3(data)                                                  (0xFF000000&((data)<<24))
#define ISO_SC_KEY03_sc_key_3_src(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEY03_get_sc_key_3(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEY03_sc_key_2_shift                                                  (16)
#define ISO_SC_KEY03_sc_key_2_mask                                                   (0x00FF0000)
#define ISO_SC_KEY03_sc_key_2(data)                                                  (0x00FF0000&((data)<<16))
#define ISO_SC_KEY03_sc_key_2_src(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEY03_get_sc_key_2(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEY03_sc_key_1_shift                                                  (8)
#define ISO_SC_KEY03_sc_key_1_mask                                                   (0x0000FF00)
#define ISO_SC_KEY03_sc_key_1(data)                                                  (0x0000FF00&((data)<<8))
#define ISO_SC_KEY03_sc_key_1_src(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEY03_get_sc_key_1(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEY03_sc_key_0_shift                                                  (0)
#define ISO_SC_KEY03_sc_key_0_mask                                                   (0x000000FF)
#define ISO_SC_KEY03_sc_key_0(data)                                                  (0x000000FF&((data)<<0))
#define ISO_SC_KEY03_sc_key_0_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_SC_KEY03_get_sc_key_0(data)                                              ((0x000000FF&(data))>>0)


#define ISO_SC_KEY47                                                                 0x18007074
#define ISO_SC_KEY47_reg_addr                                                        "0xB8007074"
#define ISO_SC_KEY47_reg                                                             0xB8007074
#define set_ISO_SC_KEY47_reg(data)   (*((volatile unsigned int*) ISO_SC_KEY47_reg)=data)
#define get_ISO_SC_KEY47_reg   (*((volatile unsigned int*) ISO_SC_KEY47_reg))
#define ISO_SC_KEY47_inst_adr                                                        "0x001D"
#define ISO_SC_KEY47_inst                                                            0x001D
#define ISO_SC_KEY47_sc_key_7_shift                                                  (24)
#define ISO_SC_KEY47_sc_key_7_mask                                                   (0xFF000000)
#define ISO_SC_KEY47_sc_key_7(data)                                                  (0xFF000000&((data)<<24))
#define ISO_SC_KEY47_sc_key_7_src(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEY47_get_sc_key_7(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEY47_sc_key_6_shift                                                  (16)
#define ISO_SC_KEY47_sc_key_6_mask                                                   (0x00FF0000)
#define ISO_SC_KEY47_sc_key_6(data)                                                  (0x00FF0000&((data)<<16))
#define ISO_SC_KEY47_sc_key_6_src(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEY47_get_sc_key_6(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEY47_sc_key_5_shift                                                  (8)
#define ISO_SC_KEY47_sc_key_5_mask                                                   (0x0000FF00)
#define ISO_SC_KEY47_sc_key_5(data)                                                  (0x0000FF00&((data)<<8))
#define ISO_SC_KEY47_sc_key_5_src(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEY47_get_sc_key_5(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEY47_sc_key_4_shift                                                  (0)
#define ISO_SC_KEY47_sc_key_4_mask                                                   (0x000000FF)
#define ISO_SC_KEY47_sc_key_4(data)                                                  (0x000000FF&((data)<<0))
#define ISO_SC_KEY47_sc_key_4_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_SC_KEY47_get_sc_key_4(data)                                              ((0x000000FF&(data))>>0)


#define ISO_SC_KEY8B                                                                 0x18007078
#define ISO_SC_KEY8B_reg_addr                                                        "0xB8007078"
#define ISO_SC_KEY8B_reg                                                             0xB8007078
#define set_ISO_SC_KEY8B_reg(data)   (*((volatile unsigned int*) ISO_SC_KEY8B_reg)=data)
#define get_ISO_SC_KEY8B_reg   (*((volatile unsigned int*) ISO_SC_KEY8B_reg))
#define ISO_SC_KEY8B_inst_adr                                                        "0x001E"
#define ISO_SC_KEY8B_inst                                                            0x001E
#define ISO_SC_KEY8B_sc_key_b_shift                                                  (24)
#define ISO_SC_KEY8B_sc_key_b_mask                                                   (0xFF000000)
#define ISO_SC_KEY8B_sc_key_b(data)                                                  (0xFF000000&((data)<<24))
#define ISO_SC_KEY8B_sc_key_b_src(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEY8B_get_sc_key_b(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEY8B_sc_key_a_shift                                                  (16)
#define ISO_SC_KEY8B_sc_key_a_mask                                                   (0x00FF0000)
#define ISO_SC_KEY8B_sc_key_a(data)                                                  (0x00FF0000&((data)<<16))
#define ISO_SC_KEY8B_sc_key_a_src(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEY8B_get_sc_key_a(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEY8B_sc_key_9_shift                                                  (8)
#define ISO_SC_KEY8B_sc_key_9_mask                                                   (0x0000FF00)
#define ISO_SC_KEY8B_sc_key_9(data)                                                  (0x0000FF00&((data)<<8))
#define ISO_SC_KEY8B_sc_key_9_src(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEY8B_get_sc_key_9(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEY8B_sc_key_8_shift                                                  (0)
#define ISO_SC_KEY8B_sc_key_8_mask                                                   (0x000000FF)
#define ISO_SC_KEY8B_sc_key_8(data)                                                  (0x000000FF&((data)<<0))
#define ISO_SC_KEY8B_sc_key_8_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_SC_KEY8B_get_sc_key_8(data)                                              ((0x000000FF&(data))>>0)


#define ISO_SC_KEYCF                                                                 0x1800707C
#define ISO_SC_KEYCF_reg_addr                                                        "0xB800707C"
#define ISO_SC_KEYCF_reg                                                             0xB800707C
#define set_ISO_SC_KEYCF_reg(data)   (*((volatile unsigned int*) ISO_SC_KEYCF_reg)=data)
#define get_ISO_SC_KEYCF_reg   (*((volatile unsigned int*) ISO_SC_KEYCF_reg))
#define ISO_SC_KEYCF_inst_adr                                                        "0x001F"
#define ISO_SC_KEYCF_inst                                                            0x001F
#define ISO_SC_KEYCF_sc_key_f_shift                                                  (24)
#define ISO_SC_KEYCF_sc_key_f_mask                                                   (0xFF000000)
#define ISO_SC_KEYCF_sc_key_f(data)                                                  (0xFF000000&((data)<<24))
#define ISO_SC_KEYCF_sc_key_f_src(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEYCF_get_sc_key_f(data)                                              ((0xFF000000&(data))>>24)
#define ISO_SC_KEYCF_sc_key_e_shift                                                  (16)
#define ISO_SC_KEYCF_sc_key_e_mask                                                   (0x00FF0000)
#define ISO_SC_KEYCF_sc_key_e(data)                                                  (0x00FF0000&((data)<<16))
#define ISO_SC_KEYCF_sc_key_e_src(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEYCF_get_sc_key_e(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_SC_KEYCF_sc_key_d_shift                                                  (8)
#define ISO_SC_KEYCF_sc_key_d_mask                                                   (0x0000FF00)
#define ISO_SC_KEYCF_sc_key_d(data)                                                  (0x0000FF00&((data)<<8))
#define ISO_SC_KEYCF_sc_key_d_src(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEYCF_get_sc_key_d(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_SC_KEYCF_sc_key_c_shift                                                  (0)
#define ISO_SC_KEYCF_sc_key_c_mask                                                   (0x000000FF)
#define ISO_SC_KEYCF_sc_key_c(data)                                                  (0x000000FF&((data)<<0))
#define ISO_SC_KEYCF_sc_key_c_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_SC_KEYCF_get_sc_key_c(data)                                              ((0x000000FF&(data))>>0)


#define ISO_OTP                                                                      0x18007080
#define ISO_OTP_reg_addr                                                             "0xB8007080"
#define ISO_OTP_reg                                                                  0xB8007080
#define set_ISO_OTP_reg(data)   (*((volatile unsigned int*) ISO_OTP_reg)=data)
#define get_ISO_OTP_reg   (*((volatile unsigned int*) ISO_OTP_reg))
#define ISO_OTP_inst_adr                                                             "0x0020"
#define ISO_OTP_inst                                                                 0x0020
#define ISO_OTP_reboot_from_ddr_shift                                                (0)
#define ISO_OTP_reboot_from_ddr_mask                                                 (0x00000007)
#define ISO_OTP_reboot_from_ddr(data)                                                (0x00000007&((data)<<0))
#define ISO_OTP_reboot_from_ddr_src(data)                                            ((0x00000007&(data))>>0)
#define ISO_OTP_get_reboot_from_ddr(data)                                            ((0x00000007&(data))>>0)


#define ISO_GPDIR                                                                    0x18061100
#define ISO_GPDIR_reg_addr                                                           "0xB8061100"
#define ISO_GPDIR_reg                                                                0xB8061100
#define set_ISO_GPDIR_reg(data)   (*((volatile unsigned int*) ISO_GPDIR_reg)=data)
#define get_ISO_GPDIR_reg   (*((volatile unsigned int*) ISO_GPDIR_reg))
#define ISO_GPDIR_inst_adr                                                           "0x0040"
#define ISO_GPDIR_inst                                                               0x0040
#define ISO_GPDIR_gpdir_shift                                                        (0)
#define ISO_GPDIR_gpdir_mask                                                         (0x000FFFFF)
#define ISO_GPDIR_gpdir(data)                                                        (0x000FFFFF&((data)<<0))
#define ISO_GPDIR_gpdir_src(data)                                                    ((0x000FFFFF&(data))>>0)
#define ISO_GPDIR_get_gpdir(data)                                                    ((0x000FFFFF&(data))>>0)

#define ISO_GPDIR_1                                                                    0x18061104
#define ISO_GPDIR_1_reg_addr                                                           "0xB8061104"
#define ISO_GPDIR_1_reg                                                                0xB8061104
#define set_ISO_GPDIR_1_reg(data)   (*((volatile unsigned int*) ISO_GPDIR_1_reg)=data)
#define get_ISO_GPDIR_1_reg   (*((volatile unsigned int*) ISO_GPDIR_1_reg))
#define ISO_GPDIR_1_inst_adr                                                           "0x0040"
#define ISO_GPDIR_1_inst                                                               0x0040
#define ISO_GPDIR_1_gpdir_shift                                                        (0)
#define ISO_GPDIR_1_gpdir_mask                                                         (0x000FFFFF)
#define ISO_GPDIR_1_gpdir(data)                                                        (0x000FFFFF&((data)<<0))
#define ISO_GPDIR_1_gpdir_src(data)                                                    ((0x000FFFFF&(data))>>0)
#define ISO_GPDIR_1_get_gpdir(data)                                                    ((0x000FFFFF&(data))>>0)

#define ISO_GPDATO                                                                   0x18061108
#define ISO_GPDATO_reg_addr                                                          "0xB8061108"
#define ISO_GPDATO_reg                                                               0xB8061108
#define set_ISO_GPDATO_reg(data)   (*((volatile unsigned int*) ISO_GPDATO_reg)=data)
#define get_ISO_GPDATO_reg   (*((volatile unsigned int*) ISO_GPDATO_reg))
#define ISO_GPDATO_inst_adr                                                          "0x0041"
#define ISO_GPDATO_inst                                                              0x0041
#define ISO_GPDATO_gpdato_shift                                                      (0)
#define ISO_GPDATO_gpdato_mask                                                       (0x000FFFFF)
#define ISO_GPDATO_gpdato(data)                                                      (0x000FFFFF&((data)<<0))
#define ISO_GPDATO_gpdato_src(data)                                                  ((0x000FFFFF&(data))>>0)
#define ISO_GPDATO_get_gpdato(data)                                                  ((0x000FFFFF&(data))>>0)

#define ISO_GPDATO_1                                                                   0x1806110C
#define ISO_GPDATO_1_reg_addr                                                          "0xB806110C"
#define ISO_GPDATO_1_reg                                                               0xB806110C
#define set_ISO_GPDATO_1_reg(data)   (*((volatile unsigned int*) ISO_GPDATO_1_reg)=data)
#define get_ISO_GPDATO_1_reg   (*((volatile unsigned int*) ISO_GPDATO_1_reg))
#define ISO_GPDATO_1_inst_adr                                                          "0x0041"
#define ISO_GPDATO_1_inst                                                              0x0041
#define ISO_GPDATO_1_gpdato_shift                                                      (0)
#define ISO_GPDATO_1_gpdato_mask                                                       (0x000FFFFF)
#define ISO_GPDATO_1_gpdato(data)                                                      (0x000FFFFF&((data)<<0))
#define ISO_GPDATO_1_gpdato_src(data)                                                  ((0x000FFFFF&(data))>>0)
#define ISO_GPDATO_1_get_gpdato(data)                                                  ((0x000FFFFF&(data))>>0)

#define ISO_GPDATI                                                                   0x18061110
#define ISO_GPDATI_reg_addr                                                          "0xB8061110"
#define ISO_GPDATI_reg                                                               0xB8061110
#define set_ISO_GPDATI_reg(data)   (*((volatile unsigned int*) ISO_GPDATI_reg)=data)
#define get_ISO_GPDATI_reg   (*((volatile unsigned int*) ISO_GPDATI_reg))
#define ISO_GPDATI_inst_adr                                                          "0x0042"
#define ISO_GPDATI_inst                                                              0x0042
#define ISO_GPDATI_gpdati_shift                                                      (0)
#define ISO_GPDATI_gpdati_mask                                                       (0x000FFFFF)
#define ISO_GPDATI_gpdati(data)                                                      (0x000FFFFF&((data)<<0))
#define ISO_GPDATI_gpdati_src(data)                                                  ((0x000FFFFF&(data))>>0)
#define ISO_GPDATI_get_gpdati(data)                                                  ((0x000FFFFF&(data))>>0)

#define ISO_GPDATI_1                                                                   0x18061114
#define ISO_GPDATI_1_reg_addr                                                          "0xB8061114"
#define ISO_GPDATI_1_reg                                                               0xB8061114
#define set_ISO_GPDATI_1_reg(data)   (*((volatile unsigned int*) ISO_GPDATI_1_reg)=data)
#define get_ISO_GPDATI_1_reg   (*((volatile unsigned int*) ISO_GPDATI_1_reg))
#define ISO_GPDATI_1_inst_adr                                                          "0x0042"
#define ISO_GPDATI_1_inst                                                              0x0042
#define ISO_GPDATI_1_gpdati_shift                                                      (0)
#define ISO_GPDATI_1_gpdati_mask                                                       (0x000FFFFF)
#define ISO_GPDATI_1_gpdati(data)                                                      (0x000FFFFF&((data)<<0))
#define ISO_GPDATI_1_gpdati_src(data)                                                  ((0x000FFFFF&(data))>>0)
#define ISO_GPDATI_1_get_gpdati(data)                                                  ((0x000FFFFF&(data))>>0)

#define ISO_GPIE                                                                     0x18061118
#define ISO_GPIE_reg_addr                                                            "0xB8061118"
#define ISO_GPIE_reg                                                                 0xB8061118
#define set_ISO_GPIE_reg(data)   (*((volatile unsigned int*) ISO_GPIE_reg)=data)
#define get_ISO_GPIE_reg   (*((volatile unsigned int*) ISO_GPIE_reg))
#define ISO_GPIE_inst_adr                                                            "0x0043"
#define ISO_GPIE_inst                                                                0x0043
#define ISO_GPIE_gp_shift                                                            (0)
#define ISO_GPIE_gp_mask                                                             (0x000FFFFF)
#define ISO_GPIE_gp(data)                                                            (0x000FFFFF&((data)<<0))
#define ISO_GPIE_gp_src(data)                                                        ((0x000FFFFF&(data))>>0)
#define ISO_GPIE_get_gp(data)                                                        ((0x000FFFFF&(data))>>0)

#define ISO_GPIE_1                                                                     0x1806111C
#define ISO_GPIE_1_reg_addr                                                            "0xB806111C"
#define ISO_GPIE_1_reg                                                                 0xB806111C
#define set_ISO_GPIE_1_reg(data)   (*((volatile unsigned int*) ISO_GPIE_1_reg)=data)
#define get_ISO_GPIE_1_reg   (*((volatile unsigned int*) ISO_GPIE_1_reg))
#define ISO_GPIE_1_inst_adr                                                            "0x0043"
#define ISO_GPIE_1_inst                                                                0x0043
#define ISO_GPIE_1_gp_shift                                                            (0)
#define ISO_GPIE_1_gp_mask                                                             (0x000FFFFF)
#define ISO_GPIE_1_gp(data)                                                            (0x000FFFFF&((data)<<0))
#define ISO_GPIE_1_gp_src(data)                                                        ((0x000FFFFF&(data))>>0)
#define ISO_GPIE_1_get_gp(data)                                                        ((0x000FFFFF&(data))>>0)

#define ISO_GPDP                                                                     0x18061120
#define ISO_GPDP_reg_addr                                                            "0xB8061120"
#define ISO_GPDP_reg                                                                 0xB8061120
#define set_ISO_GPDP_reg(data)   (*((volatile unsigned int*) ISO_GPDP_reg)=data)
#define get_ISO_GPDP_reg   (*((volatile unsigned int*) ISO_GPDP_reg))
#define ISO_GPDP_inst_adr                                                            "0x0044"
#define ISO_GPDP_inst                                                                0x0044
#define ISO_GPDP_gpha_shift                                                          (0)
#define ISO_GPDP_gpha_mask                                                           (0x000FFFFF)
#define ISO_GPDP_gpha(data)                                                          (0x000FFFFF&((data)<<0))
#define ISO_GPDP_gpha_src(data)                                                      ((0x000FFFFF&(data))>>0)
#define ISO_GPDP_get_gpha(data)                                                      ((0x000FFFFF&(data))>>0)

#define ISO_GPDP_1                                                                     0x18061124
#define ISO_GPDP_1_reg_addr                                                            "0xB8061124"
#define ISO_GPDP_1_reg                                                                 0xB8061124
#define set_ISO_GPDP_1_reg(data)   (*((volatile unsigned int*) ISO_GPDP_1_reg)=data)
#define get_ISO_GPDP_1_reg   (*((volatile unsigned int*) ISO_GPDP_1_reg))
#define ISO_GPDP_1_inst_adr                                                            "0x0044"
#define ISO_GPDP_1_inst                                                                0x0044
#define ISO_GPDP_1_gpha_shift                                                          (0)
#define ISO_GPDP_1_gpha_mask                                                           (0x000FFFFF)
#define ISO_GPDP_1_gpha(data)                                                          (0x000FFFFF&((data)<<0))
#define ISO_GPDP_1_gpha_src(data)                                                      ((0x000FFFFF&(data))>>0)
#define ISO_GPDP_1_get_gpha(data)                                                      ((0x000FFFFF&(data))>>0)


#define ISO_GPDEB                                                                    0x18061128
#define ISO_GPDEB_reg_addr                                                           "0xB8061128"
#define ISO_GPDEB_reg                                                                0xB8061128
#define set_ISO_GPDEB_reg(data)   (*((volatile unsigned int*) ISO_GPDEB_reg)=data)
#define get_ISO_GPDEB_reg   (*((volatile unsigned int*) ISO_GPDEB_reg))
#define ISO_GPDEB_inst_adr                                                           "0x0045"
#define ISO_GPDEB_inst                                                               0x0045
#define ISO_GPDEB_write_en1_shift                                                    (3)
#define ISO_GPDEB_write_en1_mask                                                     (0x00000008)
#define ISO_GPDEB_write_en1(data)                                                    (0x00000008&((data)<<3))
#define ISO_GPDEB_write_en1_src(data)                                                ((0x00000008&(data))>>3)
#define ISO_GPDEB_get_write_en1(data)                                                ((0x00000008&(data))>>3)
#define ISO_GPDEB_clk1_shift                                                         (0)
#define ISO_GPDEB_clk1_mask                                                          (0x00000007)
#define ISO_GPDEB_clk1(data)                                                         (0x00000007&((data)<<0))
#define ISO_GPDEB_clk1_src(data)                                                     ((0x00000007&(data))>>0)
#define ISO_GPDEB_get_clk1(data)                                                     ((0x00000007&(data))>>0)

#define ISO_ISR_GP0A                                                                 0x18061130
#define ISO_ISR_GP0A_reg_addr                                                        "0xB8061130"
#define ISO_ISR_GP0A_reg                                                             0xB8061130

#define ISO_ISR_GP1A                                                                 0x18061134
#define ISO_ISR_GP1A_reg_addr                                                        "0xB8061134"
#define ISO_ISR_GP1A_reg                                                             0xB8061134

#define ISO_ISR_GP0DA                                                                0x18061138
#define ISO_ISR_GP0DA_reg_addr                                                       "0xB8061138"
#define ISO_ISR_GP0DA_reg                                                            0xB8061138

#define ISO_ISR_GP1DA                                                                0x1806113C
#define ISO_ISR_GP1DA_reg_addr                                                       "0xB806113C"
#define ISO_ISR_GP1DA_reg                                                            0xB806113C

#define ISO_VFD_CTL                                                                  0x18007200
#define ISO_VFD_CTL_reg_addr                                                         "0xB8007200"
#define ISO_VFD_CTL_reg                                                              0xB8007200
#define set_ISO_VFD_CTL_reg(data)   (*((volatile unsigned int*) ISO_VFD_CTL_reg)=data)
#define get_ISO_VFD_CTL_reg   (*((volatile unsigned int*) ISO_VFD_CTL_reg))
#define ISO_VFD_CTL_inst_adr                                                         "0x0080"
#define ISO_VFD_CTL_inst                                                             0x0080
#define ISO_VFD_CTL_kpaden_shift                                                     (3)
#define ISO_VFD_CTL_kpaden_mask                                                      (0x00000008)
#define ISO_VFD_CTL_kpaden(data)                                                     (0x00000008&((data)<<3))
#define ISO_VFD_CTL_kpaden_src(data)                                                 ((0x00000008&(data))>>3)
#define ISO_VFD_CTL_get_kpaden(data)                                                 ((0x00000008&(data))>>3)
#define ISO_VFD_CTL_swen_shift                                                       (2)
#define ISO_VFD_CTL_swen_mask                                                        (0x00000004)
#define ISO_VFD_CTL_swen(data)                                                       (0x00000004&((data)<<2))
#define ISO_VFD_CTL_swen_src(data)                                                   ((0x00000004&(data))>>2)
#define ISO_VFD_CTL_get_swen(data)                                                   ((0x00000004&(data))>>2)
#define ISO_VFD_CTL_clksel_shift                                                     (1)
#define ISO_VFD_CTL_clksel_mask                                                      (0x00000002)
#define ISO_VFD_CTL_clksel(data)                                                     (0x00000002&((data)<<1))
#define ISO_VFD_CTL_clksel_src(data)                                                 ((0x00000002&(data))>>1)
#define ISO_VFD_CTL_get_clksel(data)                                                 ((0x00000002&(data))>>1)
#define ISO_VFD_CTL_envfd_shift                                                      (0)
#define ISO_VFD_CTL_envfd_mask                                                       (0x00000001)
#define ISO_VFD_CTL_envfd(data)                                                      (0x00000001&((data)<<0))
#define ISO_VFD_CTL_envfd_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_VFD_CTL_get_envfd(data)                                                  ((0x00000001&(data))>>0)


#define ISO_VFD_WRCTL                                                                0x18007204
#define ISO_VFD_WRCTL_reg_addr                                                       "0xB8007204"
#define ISO_VFD_WRCTL_reg                                                            0xB8007204
#define set_ISO_VFD_WRCTL_reg(data)   (*((volatile unsigned int*) ISO_VFD_WRCTL_reg)=data)
#define get_ISO_VFD_WRCTL_reg   (*((volatile unsigned int*) ISO_VFD_WRCTL_reg))
#define ISO_VFD_WRCTL_inst_adr                                                       "0x0081"
#define ISO_VFD_WRCTL_inst                                                           0x0081
#define ISO_VFD_WRCTL_nact_csn_shift                                                 (12)
#define ISO_VFD_WRCTL_nact_csn_mask                                                  (0x00001000)
#define ISO_VFD_WRCTL_nact_csn(data)                                                 (0x00001000&((data)<<12))
#define ISO_VFD_WRCTL_nact_csn_src(data)                                             ((0x00001000&(data))>>12)
#define ISO_VFD_WRCTL_get_nact_csn(data)                                             ((0x00001000&(data))>>12)
#define ISO_VFD_WRCTL_b3c_shift                                                      (11)
#define ISO_VFD_WRCTL_b3c_mask                                                       (0x00000800)
#define ISO_VFD_WRCTL_b3c(data)                                                      (0x00000800&((data)<<11))
#define ISO_VFD_WRCTL_b3c_src(data)                                                  ((0x00000800&(data))>>11)
#define ISO_VFD_WRCTL_get_b3c(data)                                                  ((0x00000800&(data))>>11)
#define ISO_VFD_WRCTL_b2c_shift                                                      (10)
#define ISO_VFD_WRCTL_b2c_mask                                                       (0x00000400)
#define ISO_VFD_WRCTL_b2c(data)                                                      (0x00000400&((data)<<10))
#define ISO_VFD_WRCTL_b2c_src(data)                                                  ((0x00000400&(data))>>10)
#define ISO_VFD_WRCTL_get_b2c(data)                                                  ((0x00000400&(data))>>10)
#define ISO_VFD_WRCTL_b1c_shift                                                      (9)
#define ISO_VFD_WRCTL_b1c_mask                                                       (0x00000200)
#define ISO_VFD_WRCTL_b1c(data)                                                      (0x00000200&((data)<<9))
#define ISO_VFD_WRCTL_b1c_src(data)                                                  ((0x00000200&(data))>>9)
#define ISO_VFD_WRCTL_get_b1c(data)                                                  ((0x00000200&(data))>>9)
#define ISO_VFD_WRCTL_b0c_shift                                                      (8)
#define ISO_VFD_WRCTL_b0c_mask                                                       (0x00000100)
#define ISO_VFD_WRCTL_b0c(data)                                                      (0x00000100&((data)<<8))
#define ISO_VFD_WRCTL_b0c_src(data)                                                  ((0x00000100&(data))>>8)
#define ISO_VFD_WRCTL_get_b0c(data)                                                  ((0x00000100&(data))>>8)
#define ISO_VFD_WRCTL_enb3_shift                                                     (7)
#define ISO_VFD_WRCTL_enb3_mask                                                      (0x00000080)
#define ISO_VFD_WRCTL_enb3(data)                                                     (0x00000080&((data)<<7))
#define ISO_VFD_WRCTL_enb3_src(data)                                                 ((0x00000080&(data))>>7)
#define ISO_VFD_WRCTL_get_enb3(data)                                                 ((0x00000080&(data))>>7)
#define ISO_VFD_WRCTL_enb2_shift                                                     (6)
#define ISO_VFD_WRCTL_enb2_mask                                                      (0x00000040)
#define ISO_VFD_WRCTL_enb2(data)                                                     (0x00000040&((data)<<6))
#define ISO_VFD_WRCTL_enb2_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_VFD_WRCTL_get_enb2(data)                                                 ((0x00000040&(data))>>6)
#define ISO_VFD_WRCTL_enb1_shift                                                     (5)
#define ISO_VFD_WRCTL_enb1_mask                                                      (0x00000020)
#define ISO_VFD_WRCTL_enb1(data)                                                     (0x00000020&((data)<<5))
#define ISO_VFD_WRCTL_enb1_src(data)                                                 ((0x00000020&(data))>>5)
#define ISO_VFD_WRCTL_get_enb1(data)                                                 ((0x00000020&(data))>>5)
#define ISO_VFD_WRCTL_enb0_shift                                                     (4)
#define ISO_VFD_WRCTL_enb0_mask                                                      (0x00000010)
#define ISO_VFD_WRCTL_enb0(data)                                                     (0x00000010&((data)<<4))
#define ISO_VFD_WRCTL_enb0_src(data)                                                 ((0x00000010&(data))>>4)
#define ISO_VFD_WRCTL_get_enb0(data)                                                 ((0x00000010&(data))>>4)
#define ISO_VFD_WRCTL_wd_shift                                                       (1)
#define ISO_VFD_WRCTL_wd_mask                                                        (0x00000002)
#define ISO_VFD_WRCTL_wd(data)                                                       (0x00000002&((data)<<1))
#define ISO_VFD_WRCTL_wd_src(data)                                                   ((0x00000002&(data))>>1)
#define ISO_VFD_WRCTL_get_wd(data)                                                   ((0x00000002&(data))>>1)
#define ISO_VFD_WRCTL_wdie_shift                                                     (0)
#define ISO_VFD_WRCTL_wdie_mask                                                      (0x00000001)
#define ISO_VFD_WRCTL_wdie(data)                                                     (0x00000001&((data)<<0))
#define ISO_VFD_WRCTL_wdie_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_VFD_WRCTL_get_wdie(data)                                                 ((0x00000001&(data))>>0)


#define ISO_VFDO                                                                     0x18007208
#define ISO_VFDO_reg_addr                                                            "0xB8007208"
#define ISO_VFDO_reg                                                                 0xB8007208
#define set_ISO_VFDO_reg(data)   (*((volatile unsigned int*) ISO_VFDO_reg)=data)
#define get_ISO_VFDO_reg   (*((volatile unsigned int*) ISO_VFDO_reg))
#define ISO_VFDO_inst_adr                                                            "0x0082"
#define ISO_VFDO_inst                                                                0x0082
#define ISO_VFDO_byte3_shift                                                         (24)
#define ISO_VFDO_byte3_mask                                                          (0xFF000000)
#define ISO_VFDO_byte3(data)                                                         (0xFF000000&((data)<<24))
#define ISO_VFDO_byte3_src(data)                                                     ((0xFF000000&(data))>>24)
#define ISO_VFDO_get_byte3(data)                                                     ((0xFF000000&(data))>>24)
#define ISO_VFDO_byte2_shift                                                         (16)
#define ISO_VFDO_byte2_mask                                                          (0x00FF0000)
#define ISO_VFDO_byte2(data)                                                         (0x00FF0000&((data)<<16))
#define ISO_VFDO_byte2_src(data)                                                     ((0x00FF0000&(data))>>16)
#define ISO_VFDO_get_byte2(data)                                                     ((0x00FF0000&(data))>>16)
#define ISO_VFDO_byte1_shift                                                         (8)
#define ISO_VFDO_byte1_mask                                                          (0x0000FF00)
#define ISO_VFDO_byte1(data)                                                         (0x0000FF00&((data)<<8))
#define ISO_VFDO_byte1_src(data)                                                     ((0x0000FF00&(data))>>8)
#define ISO_VFDO_get_byte1(data)                                                     ((0x0000FF00&(data))>>8)
#define ISO_VFDO_byte0_shift                                                         (0)
#define ISO_VFDO_byte0_mask                                                          (0x000000FF)
#define ISO_VFDO_byte0(data)                                                         (0x000000FF&((data)<<0))
#define ISO_VFDO_byte0_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_VFDO_get_byte0(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_VFD_ARDCTL                                                               0x1800720C
#define ISO_VFD_ARDCTL_reg_addr                                                      "0xB800720C"
#define ISO_VFD_ARDCTL_reg                                                           0xB800720C
#define set_ISO_VFD_ARDCTL_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDCTL_reg)=data)
#define get_ISO_VFD_ARDCTL_reg   (*((volatile unsigned int*) ISO_VFD_ARDCTL_reg))
#define ISO_VFD_ARDCTL_inst_adr                                                      "0x0083"
#define ISO_VFD_ARDCTL_inst                                                          0x0083
#define ISO_VFD_ARDCTL_kpadbn_shift                                                  (8)
#define ISO_VFD_ARDCTL_kpadbn_mask                                                   (0x00000700)
#define ISO_VFD_ARDCTL_kpadbn(data)                                                  (0x00000700&((data)<<8))
#define ISO_VFD_ARDCTL_kpadbn_src(data)                                              ((0x00000700&(data))>>8)
#define ISO_VFD_ARDCTL_get_kpadbn(data)                                              ((0x00000700&(data))>>8)
#define ISO_VFD_ARDCTL_swha_shift                                                    (5)
#define ISO_VFD_ARDCTL_swha_mask                                                     (0x00000020)
#define ISO_VFD_ARDCTL_swha(data)                                                    (0x00000020&((data)<<5))
#define ISO_VFD_ARDCTL_swha_src(data)                                                ((0x00000020&(data))>>5)
#define ISO_VFD_ARDCTL_get_swha(data)                                                ((0x00000020&(data))>>5)
#define ISO_VFD_ARDCTL_kpadha_shift                                                  (4)
#define ISO_VFD_ARDCTL_kpadha_mask                                                   (0x00000010)
#define ISO_VFD_ARDCTL_kpadha(data)                                                  (0x00000010&((data)<<4))
#define ISO_VFD_ARDCTL_kpadha_src(data)                                              ((0x00000010&(data))>>4)
#define ISO_VFD_ARDCTL_get_kpadha(data)                                              ((0x00000010&(data))>>4)
#define ISO_VFD_ARDCTL_ardp_shift                                                    (0)
#define ISO_VFD_ARDCTL_ardp_mask                                                     (0x00000003)
#define ISO_VFD_ARDCTL_ardp(data)                                                    (0x00000003&((data)<<0))
#define ISO_VFD_ARDCTL_ardp_src(data)                                                ((0x00000003&(data))>>0)
#define ISO_VFD_ARDCTL_get_ardp(data)                                                ((0x00000003&(data))>>0)


#define ISO_VFD_KPADLIE                                                              0x18007210
#define ISO_VFD_KPADLIE_reg_addr                                                     "0xB8007210"
#define ISO_VFD_KPADLIE_reg                                                          0xB8007210
#define set_ISO_VFD_KPADLIE_reg(data)   (*((volatile unsigned int*) ISO_VFD_KPADLIE_reg)=data)
#define get_ISO_VFD_KPADLIE_reg   (*((volatile unsigned int*) ISO_VFD_KPADLIE_reg))
#define ISO_VFD_KPADLIE_inst_adr                                                     "0x0084"
#define ISO_VFD_KPADLIE_inst                                                         0x0084
#define ISO_VFD_KPADLIE_kpadie_shift                                                 (0)
#define ISO_VFD_KPADLIE_kpadie_mask                                                  (0xFFFFFFFF)
#define ISO_VFD_KPADLIE_kpadie(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_VFD_KPADLIE_kpadie_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_VFD_KPADLIE_get_kpadie(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_VFD_KPADHIE                                                              0x18007214
#define ISO_VFD_KPADHIE_reg_addr                                                     "0xB8007214"
#define ISO_VFD_KPADHIE_reg                                                          0xB8007214
#define set_ISO_VFD_KPADHIE_reg(data)   (*((volatile unsigned int*) ISO_VFD_KPADHIE_reg)=data)
#define get_ISO_VFD_KPADHIE_reg   (*((volatile unsigned int*) ISO_VFD_KPADHIE_reg))
#define ISO_VFD_KPADHIE_inst_adr                                                     "0x0085"
#define ISO_VFD_KPADHIE_inst                                                         0x0085
#define ISO_VFD_KPADHIE_kpadie_shift                                                 (0)
#define ISO_VFD_KPADHIE_kpadie_mask                                                  (0x0000FFFF)
#define ISO_VFD_KPADHIE_kpadie(data)                                                 (0x0000FFFF&((data)<<0))
#define ISO_VFD_KPADHIE_kpadie_src(data)                                             ((0x0000FFFF&(data))>>0)
#define ISO_VFD_KPADHIE_get_kpadie(data)                                             ((0x0000FFFF&(data))>>0)


#define ISO_VFD_SWIE                                                                 0x18007218
#define ISO_VFD_SWIE_reg_addr                                                        "0xB8007218"
#define ISO_VFD_SWIE_reg                                                             0xB8007218
#define set_ISO_VFD_SWIE_reg(data)   (*((volatile unsigned int*) ISO_VFD_SWIE_reg)=data)
#define get_ISO_VFD_SWIE_reg   (*((volatile unsigned int*) ISO_VFD_SWIE_reg))
#define ISO_VFD_SWIE_inst_adr                                                        "0x0086"
#define ISO_VFD_SWIE_inst                                                            0x0086
#define ISO_VFD_SWIE_swie_shift                                                      (0)
#define ISO_VFD_SWIE_swie_mask                                                       (0x0000000F)
#define ISO_VFD_SWIE_swie(data)                                                      (0x0000000F&((data)<<0))
#define ISO_VFD_SWIE_swie_src(data)                                                  ((0x0000000F&(data))>>0)
#define ISO_VFD_SWIE_get_swie(data)                                                  ((0x0000000F&(data))>>0)


#define ISO_VFD_ARDKPADL                                                             0x1800721C
#define ISO_VFD_ARDKPADL_reg_addr                                                    "0xB800721C"
#define ISO_VFD_ARDKPADL_reg                                                         0xB800721C
#define set_ISO_VFD_ARDKPADL_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDKPADL_reg)=data)
#define get_ISO_VFD_ARDKPADL_reg   (*((volatile unsigned int*) ISO_VFD_ARDKPADL_reg))
#define ISO_VFD_ARDKPADL_inst_adr                                                    "0x0087"
#define ISO_VFD_ARDKPADL_inst                                                        0x0087
#define ISO_VFD_ARDKPADL_st_31_24_shift                                              (24)
#define ISO_VFD_ARDKPADL_st_31_24_mask                                               (0xFF000000)
#define ISO_VFD_ARDKPADL_st_31_24(data)                                              (0xFF000000&((data)<<24))
#define ISO_VFD_ARDKPADL_st_31_24_src(data)                                          ((0xFF000000&(data))>>24)
#define ISO_VFD_ARDKPADL_get_st_31_24(data)                                          ((0xFF000000&(data))>>24)
#define ISO_VFD_ARDKPADL_st_23_16_shift                                              (16)
#define ISO_VFD_ARDKPADL_st_23_16_mask                                               (0x00FF0000)
#define ISO_VFD_ARDKPADL_st_23_16(data)                                              (0x00FF0000&((data)<<16))
#define ISO_VFD_ARDKPADL_st_23_16_src(data)                                          ((0x00FF0000&(data))>>16)
#define ISO_VFD_ARDKPADL_get_st_23_16(data)                                          ((0x00FF0000&(data))>>16)
#define ISO_VFD_ARDKPADL_st_15_8_shift                                               (8)
#define ISO_VFD_ARDKPADL_st_15_8_mask                                                (0x0000FF00)
#define ISO_VFD_ARDKPADL_st_15_8(data)                                               (0x0000FF00&((data)<<8))
#define ISO_VFD_ARDKPADL_st_15_8_src(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADL_get_st_15_8(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADL_st_7_0_shift                                                (0)
#define ISO_VFD_ARDKPADL_st_7_0_mask                                                 (0x000000FF)
#define ISO_VFD_ARDKPADL_st_7_0(data)                                                (0x000000FF&((data)<<0))
#define ISO_VFD_ARDKPADL_st_7_0_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_VFD_ARDKPADL_get_st_7_0(data)                                            ((0x000000FF&(data))>>0)


#define ISO_VFD_ARDKPADH                                                             0x18007220
#define ISO_VFD_ARDKPADH_reg_addr                                                    "0xB8007220"
#define ISO_VFD_ARDKPADH_reg                                                         0xB8007220
#define set_ISO_VFD_ARDKPADH_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDKPADH_reg)=data)
#define get_ISO_VFD_ARDKPADH_reg   (*((volatile unsigned int*) ISO_VFD_ARDKPADH_reg))
#define ISO_VFD_ARDKPADH_inst_adr                                                    "0x0088"
#define ISO_VFD_ARDKPADH_inst                                                        0x0088
#define ISO_VFD_ARDKPADH_st_15_8_shift                                               (8)
#define ISO_VFD_ARDKPADH_st_15_8_mask                                                (0x0000FF00)
#define ISO_VFD_ARDKPADH_st_15_8(data)                                               (0x0000FF00&((data)<<8))
#define ISO_VFD_ARDKPADH_st_15_8_src(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADH_get_st_15_8(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_VFD_ARDKPADH_st_7_0_shift                                                (0)
#define ISO_VFD_ARDKPADH_st_7_0_mask                                                 (0x000000FF)
#define ISO_VFD_ARDKPADH_st_7_0(data)                                                (0x000000FF&((data)<<0))
#define ISO_VFD_ARDKPADH_st_7_0_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_VFD_ARDKPADH_get_st_7_0(data)                                            ((0x000000FF&(data))>>0)


#define ISO_VFD_ARDSW                                                                0x18007224
#define ISO_VFD_ARDSW_reg_addr                                                       "0xB8007224"
#define ISO_VFD_ARDSW_reg                                                            0xB8007224
#define set_ISO_VFD_ARDSW_reg(data)   (*((volatile unsigned int*) ISO_VFD_ARDSW_reg)=data)
#define get_ISO_VFD_ARDSW_reg   (*((volatile unsigned int*) ISO_VFD_ARDSW_reg))
#define ISO_VFD_ARDSW_inst_adr                                                       "0x0089"
#define ISO_VFD_ARDSW_inst                                                           0x0089
#define ISO_VFD_ARDSW_rvda_shift                                                     (4)
#define ISO_VFD_ARDSW_rvda_mask                                                      (0x0000FFF0)
#define ISO_VFD_ARDSW_rvda(data)                                                     (0x0000FFF0&((data)<<4))
#define ISO_VFD_ARDSW_rvda_src(data)                                                 ((0x0000FFF0&(data))>>4)
#define ISO_VFD_ARDSW_get_rvda(data)                                                 ((0x0000FFF0&(data))>>4)
#define ISO_VFD_ARDSW_st_shift                                                       (0)
#define ISO_VFD_ARDSW_st_mask                                                        (0x0000000F)
#define ISO_VFD_ARDSW_st(data)                                                       (0x0000000F&((data)<<0))
#define ISO_VFD_ARDSW_st_src(data)                                                   ((0x0000000F&(data))>>0)
#define ISO_VFD_ARDSW_get_st(data)                                                   ((0x0000000F&(data))>>0)


#define ISO_VFD_CTL1                                                                 0x18007228
#define ISO_VFD_CTL1_reg_addr                                                        "0xB8007228"
#define ISO_VFD_CTL1_reg                                                             0xB8007228
#define set_ISO_VFD_CTL1_reg(data)   (*((volatile unsigned int*) ISO_VFD_CTL1_reg)=data)
#define get_ISO_VFD_CTL1_reg   (*((volatile unsigned int*) ISO_VFD_CTL1_reg))
#define ISO_VFD_CTL1_inst_adr                                                        "0x008A"
#define ISO_VFD_CTL1_inst                                                            0x008A
#define ISO_VFD_CTL1_clksel_1_shift                                                  (16)
#define ISO_VFD_CTL1_clksel_1_mask                                                   (0x00010000)
#define ISO_VFD_CTL1_clksel_1(data)                                                  (0x00010000&((data)<<16))
#define ISO_VFD_CTL1_clksel_1_src(data)                                              ((0x00010000&(data))>>16)
#define ISO_VFD_CTL1_get_clksel_1(data)                                              ((0x00010000&(data))>>16)
#define ISO_VFD_CTL1_tclk_csn_shift                                                  (8)
#define ISO_VFD_CTL1_tclk_csn_mask                                                   (0x0000FF00)
#define ISO_VFD_CTL1_tclk_csn(data)                                                  (0x0000FF00&((data)<<8))
#define ISO_VFD_CTL1_tclk_csn_src(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_VFD_CTL1_get_tclk_csn(data)                                              ((0x0000FF00&(data))>>8)
#define ISO_VFD_CTL1_twait1_shift                                                    (0)
#define ISO_VFD_CTL1_twait1_mask                                                     (0x000000FF)
#define ISO_VFD_CTL1_twait1(data)                                                    (0x000000FF&((data)<<0))
#define ISO_VFD_CTL1_twait1_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_VFD_CTL1_get_twait1(data)                                                ((0x000000FF&(data))>>0)


#define ISO_PFUNC1                                                                   0x18007300
#define ISO_PFUNC1_reg_addr                                                          "0xB8007300"
#define ISO_PFUNC1_reg                                                               0xB8007300
#define set_ISO_PFUNC1_reg(data)   (*((volatile unsigned int*) ISO_PFUNC1_reg)=data)
#define get_ISO_PFUNC1_reg   (*((volatile unsigned int*) ISO_PFUNC1_reg))
#define ISO_PFUNC1_inst_adr                                                          "0x00C0"
#define ISO_PFUNC1_inst                                                              0x00C0
#define ISO_PFUNC1_standby_smt_shift                                                 (27)
#define ISO_PFUNC1_standby_smt_mask                                                  (0x08000000)
#define ISO_PFUNC1_standby_smt(data)                                                 (0x08000000&((data)<<27))
#define ISO_PFUNC1_standby_smt_src(data)                                             ((0x08000000&(data))>>27)
#define ISO_PFUNC1_get_standby_smt(data)                                             ((0x08000000&(data))>>27)
#define ISO_PFUNC1_standby_e2_shift                                                  (26)
#define ISO_PFUNC1_standby_e2_mask                                                   (0x04000000)
#define ISO_PFUNC1_standby_e2(data)                                                  (0x04000000&((data)<<26))
#define ISO_PFUNC1_standby_e2_src(data)                                              ((0x04000000&(data))>>26)
#define ISO_PFUNC1_get_standby_e2(data)                                              ((0x04000000&(data))>>26)
#define ISO_PFUNC1_standby_pud_en_shift                                              (25)
#define ISO_PFUNC1_standby_pud_en_mask                                               (0x02000000)
#define ISO_PFUNC1_standby_pud_en(data)                                              (0x02000000&((data)<<25))
#define ISO_PFUNC1_standby_pud_en_src(data)                                          ((0x02000000&(data))>>25)
#define ISO_PFUNC1_get_standby_pud_en(data)                                          ((0x02000000&(data))>>25)
#define ISO_PFUNC1_standby_pud_sel_shift                                             (24)
#define ISO_PFUNC1_standby_pud_sel_mask                                              (0x01000000)
#define ISO_PFUNC1_standby_pud_sel(data)                                             (0x01000000&((data)<<24))
#define ISO_PFUNC1_standby_pud_sel_src(data)                                         ((0x01000000&(data))>>24)
#define ISO_PFUNC1_get_standby_pud_sel(data)                                         ((0x01000000&(data))>>24)
#define ISO_PFUNC1_vfd_d_smt_shift                                                   (23)
#define ISO_PFUNC1_vfd_d_smt_mask                                                    (0x00800000)
#define ISO_PFUNC1_vfd_d_smt(data)                                                   (0x00800000&((data)<<23))
#define ISO_PFUNC1_vfd_d_smt_src(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC1_get_vfd_d_smt(data)                                               ((0x00800000&(data))>>23)
#define ISO_PFUNC1_vfd_d_e2_shift                                                    (22)
#define ISO_PFUNC1_vfd_d_e2_mask                                                     (0x00400000)
#define ISO_PFUNC1_vfd_d_e2(data)                                                    (0x00400000&((data)<<22))
#define ISO_PFUNC1_vfd_d_e2_src(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC1_get_vfd_d_e2(data)                                                ((0x00400000&(data))>>22)
#define ISO_PFUNC1_vfd_d_pud_en_shift                                                (21)
#define ISO_PFUNC1_vfd_d_pud_en_mask                                                 (0x00200000)
#define ISO_PFUNC1_vfd_d_pud_en(data)                                                (0x00200000&((data)<<21))
#define ISO_PFUNC1_vfd_d_pud_en_src(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC1_get_vfd_d_pud_en(data)                                            ((0x00200000&(data))>>21)
#define ISO_PFUNC1_vfd_d_pud_sel_shift                                               (20)
#define ISO_PFUNC1_vfd_d_pud_sel_mask                                                (0x00100000)
#define ISO_PFUNC1_vfd_d_pud_sel(data)                                               (0x00100000&((data)<<20))
#define ISO_PFUNC1_vfd_d_pud_sel_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC1_get_vfd_d_pud_sel(data)                                           ((0x00100000&(data))>>20)
#define ISO_PFUNC1_vfd_clk_smt_shift                                                 (19)
#define ISO_PFUNC1_vfd_clk_smt_mask                                                  (0x00080000)
#define ISO_PFUNC1_vfd_clk_smt(data)                                                 (0x00080000&((data)<<19))
#define ISO_PFUNC1_vfd_clk_smt_src(data)                                             ((0x00080000&(data))>>19)
#define ISO_PFUNC1_get_vfd_clk_smt(data)                                             ((0x00080000&(data))>>19)
#define ISO_PFUNC1_vfd_clk_e2_shift                                                  (18)
#define ISO_PFUNC1_vfd_clk_e2_mask                                                   (0x00040000)
#define ISO_PFUNC1_vfd_clk_e2(data)                                                  (0x00040000&((data)<<18))
#define ISO_PFUNC1_vfd_clk_e2_src(data)                                              ((0x00040000&(data))>>18)
#define ISO_PFUNC1_get_vfd_clk_e2(data)                                              ((0x00040000&(data))>>18)
#define ISO_PFUNC1_vfd_clk_pud_en_shift                                              (17)
#define ISO_PFUNC1_vfd_clk_pud_en_mask                                               (0x00020000)
#define ISO_PFUNC1_vfd_clk_pud_en(data)                                              (0x00020000&((data)<<17))
#define ISO_PFUNC1_vfd_clk_pud_en_src(data)                                          ((0x00020000&(data))>>17)
#define ISO_PFUNC1_get_vfd_clk_pud_en(data)                                          ((0x00020000&(data))>>17)
#define ISO_PFUNC1_vfd_clk_pud_sel_shift                                             (16)
#define ISO_PFUNC1_vfd_clk_pud_sel_mask                                              (0x00010000)
#define ISO_PFUNC1_vfd_clk_pud_sel(data)                                             (0x00010000&((data)<<16))
#define ISO_PFUNC1_vfd_clk_pud_sel_src(data)                                         ((0x00010000&(data))>>16)
#define ISO_PFUNC1_get_vfd_clk_pud_sel(data)                                         ((0x00010000&(data))>>16)
#define ISO_PFUNC1_vfd_cs_n_smt_shift                                                (15)
#define ISO_PFUNC1_vfd_cs_n_smt_mask                                                 (0x00008000)
#define ISO_PFUNC1_vfd_cs_n_smt(data)                                                (0x00008000&((data)<<15))
#define ISO_PFUNC1_vfd_cs_n_smt_src(data)                                            ((0x00008000&(data))>>15)
#define ISO_PFUNC1_get_vfd_cs_n_smt(data)                                            ((0x00008000&(data))>>15)
#define ISO_PFUNC1_vfd_cs_n_e2_shift                                                 (14)
#define ISO_PFUNC1_vfd_cs_n_e2_mask                                                  (0x00004000)
#define ISO_PFUNC1_vfd_cs_n_e2(data)                                                 (0x00004000&((data)<<14))
#define ISO_PFUNC1_vfd_cs_n_e2_src(data)                                             ((0x00004000&(data))>>14)
#define ISO_PFUNC1_get_vfd_cs_n_e2(data)                                             ((0x00004000&(data))>>14)
#define ISO_PFUNC1_vfd_cs_n_pud_en_shift                                             (13)
#define ISO_PFUNC1_vfd_cs_n_pud_en_mask                                              (0x00002000)
#define ISO_PFUNC1_vfd_cs_n_pud_en(data)                                             (0x00002000&((data)<<13))
#define ISO_PFUNC1_vfd_cs_n_pud_en_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_PFUNC1_get_vfd_cs_n_pud_en(data)                                         ((0x00002000&(data))>>13)
#define ISO_PFUNC1_vfd_cs_n_pud_sel_shift                                            (12)
#define ISO_PFUNC1_vfd_cs_n_pud_sel_mask                                             (0x00001000)
#define ISO_PFUNC1_vfd_cs_n_pud_sel(data)                                            (0x00001000&((data)<<12))
#define ISO_PFUNC1_vfd_cs_n_pud_sel_src(data)                                        ((0x00001000&(data))>>12)
#define ISO_PFUNC1_get_vfd_cs_n_pud_sel(data)                                        ((0x00001000&(data))>>12)
#define ISO_PFUNC1_ir_in_smt_shift                                                   (11)
#define ISO_PFUNC1_ir_in_smt_mask                                                    (0x00000800)
#define ISO_PFUNC1_ir_in_smt(data)                                                   (0x00000800&((data)<<11))
#define ISO_PFUNC1_ir_in_smt_src(data)                                               ((0x00000800&(data))>>11)
#define ISO_PFUNC1_get_ir_in_smt(data)                                               ((0x00000800&(data))>>11)
#define ISO_PFUNC1_ir_in_e2_shift                                                    (10)
#define ISO_PFUNC1_ir_in_e2_mask                                                     (0x00000400)
#define ISO_PFUNC1_ir_in_e2(data)                                                    (0x00000400&((data)<<10))
#define ISO_PFUNC1_ir_in_e2_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_PFUNC1_get_ir_in_e2(data)                                                ((0x00000400&(data))>>10)
#define ISO_PFUNC1_ir_in_pud_en_shift                                                (9)
#define ISO_PFUNC1_ir_in_pud_en_mask                                                 (0x00000200)
#define ISO_PFUNC1_ir_in_pud_en(data)                                                (0x00000200&((data)<<9))
#define ISO_PFUNC1_ir_in_pud_en_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_PFUNC1_get_ir_in_pud_en(data)                                            ((0x00000200&(data))>>9)
#define ISO_PFUNC1_ir_in_pud_sel_shift                                               (8)
#define ISO_PFUNC1_ir_in_pud_sel_mask                                                (0x00000100)
#define ISO_PFUNC1_ir_in_pud_sel(data)                                               (0x00000100&((data)<<8))
#define ISO_PFUNC1_ir_in_pud_sel_src(data)                                           ((0x00000100&(data))>>8)
#define ISO_PFUNC1_get_ir_in_pud_sel(data)                                           ((0x00000100&(data))>>8)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_smt_shift                                     (7)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_smt_mask                                      (0x00000080)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_smt(data)                                     (0x00000080&((data)<<7))
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_smt_src(data)                                 ((0x00000080&(data))>>7)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_1_smt(data)                                 ((0x00000080&(data))>>7)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_e2_shift                                      (6)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_e2_mask                                       (0x00000040)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_e2(data)                                      (0x00000040&((data)<<6))
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_e2_src(data)                                  ((0x00000040&(data))>>6)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_1_e2(data)                                  ((0x00000040&(data))>>6)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_en_shift                                  (5)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_en_mask                                   (0x00000020)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_en(data)                                  (0x00000020&((data)<<5))
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_en_src(data)                              ((0x00000020&(data))>>5)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_1_pud_en(data)                              ((0x00000020&(data))>>5)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_sel_shift                                 (4)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_sel_mask                                  (0x00000010)
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_sel(data)                                 (0x00000010&((data)<<4))
#define ISO_PFUNC1_usb_ovrcur_flag_n_1_pud_sel_src(data)                             ((0x00000010&(data))>>4)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_1_pud_sel(data)                             ((0x00000010&(data))>>4)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_smt_shift                                     (3)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_smt_mask                                      (0x00000008)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_smt(data)                                     (0x00000008&((data)<<3))
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_smt_src(data)                                 ((0x00000008&(data))>>3)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_0_smt(data)                                 ((0x00000008&(data))>>3)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_e2_shift                                      (2)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_e2_mask                                       (0x00000004)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_e2(data)                                      (0x00000004&((data)<<2))
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_e2_src(data)                                  ((0x00000004&(data))>>2)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_0_e2(data)                                  ((0x00000004&(data))>>2)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_en_shift                                  (1)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_en_mask                                   (0x00000002)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_en(data)                                  (0x00000002&((data)<<1))
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_en_src(data)                              ((0x00000002&(data))>>1)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_0_pud_en(data)                              ((0x00000002&(data))>>1)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_sel_shift                                 (0)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_sel_mask                                  (0x00000001)
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_sel(data)                                 (0x00000001&((data)<<0))
#define ISO_PFUNC1_usb_ovrcur_flag_n_0_pud_sel_src(data)                             ((0x00000001&(data))>>0)
#define ISO_PFUNC1_get_usb_ovrcur_flag_n_0_pud_sel(data)                             ((0x00000001&(data))>>0)


#define ISO_PFUNC2                                                                   0x18007304
#define ISO_PFUNC2_reg_addr                                                          "0xB8007304"
#define ISO_PFUNC2_reg                                                               0xB8007304
#define set_ISO_PFUNC2_reg(data)   (*((volatile unsigned int*) ISO_PFUNC2_reg)=data)
#define get_ISO_PFUNC2_reg   (*((volatile unsigned int*) ISO_PFUNC2_reg))
#define ISO_PFUNC2_inst_adr                                                          "0x00C1"
#define ISO_PFUNC2_inst                                                              0x00C1
#define ISO_PFUNC2_ur0_tx_smt_shift                                                  (23)
#define ISO_PFUNC2_ur0_tx_smt_mask                                                   (0x00800000)
#define ISO_PFUNC2_ur0_tx_smt(data)                                                  (0x00800000&((data)<<23))
#define ISO_PFUNC2_ur0_tx_smt_src(data)                                              ((0x00800000&(data))>>23)
#define ISO_PFUNC2_get_ur0_tx_smt(data)                                              ((0x00800000&(data))>>23)
#define ISO_PFUNC2_ur0_tx_e2_shift                                                   (22)
#define ISO_PFUNC2_ur0_tx_e2_mask                                                    (0x00400000)
#define ISO_PFUNC2_ur0_tx_e2(data)                                                   (0x00400000&((data)<<22))
#define ISO_PFUNC2_ur0_tx_e2_src(data)                                               ((0x00400000&(data))>>22)
#define ISO_PFUNC2_get_ur0_tx_e2(data)                                               ((0x00400000&(data))>>22)
#define ISO_PFUNC2_ur0_tx_pud_en_shift                                               (21)
#define ISO_PFUNC2_ur0_tx_pud_en_mask                                                (0x00200000)
#define ISO_PFUNC2_ur0_tx_pud_en(data)                                               (0x00200000&((data)<<21))
#define ISO_PFUNC2_ur0_tx_pud_en_src(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC2_get_ur0_tx_pud_en(data)                                           ((0x00200000&(data))>>21)
#define ISO_PFUNC2_ur0_tx_pud_sel_shift                                              (20)
#define ISO_PFUNC2_ur0_tx_pud_sel_mask                                               (0x00100000)
#define ISO_PFUNC2_ur0_tx_pud_sel(data)                                              (0x00100000&((data)<<20))
#define ISO_PFUNC2_ur0_tx_pud_sel_src(data)                                          ((0x00100000&(data))>>20)
#define ISO_PFUNC2_get_ur0_tx_pud_sel(data)                                          ((0x00100000&(data))>>20)
#define ISO_PFUNC2_ur0_rx_smt_shift                                                  (19)
#define ISO_PFUNC2_ur0_rx_smt_mask                                                   (0x00080000)
#define ISO_PFUNC2_ur0_rx_smt(data)                                                  (0x00080000&((data)<<19))
#define ISO_PFUNC2_ur0_rx_smt_src(data)                                              ((0x00080000&(data))>>19)
#define ISO_PFUNC2_get_ur0_rx_smt(data)                                              ((0x00080000&(data))>>19)
#define ISO_PFUNC2_ur0_rx_e2_shift                                                   (18)
#define ISO_PFUNC2_ur0_rx_e2_mask                                                    (0x00040000)
#define ISO_PFUNC2_ur0_rx_e2(data)                                                   (0x00040000&((data)<<18))
#define ISO_PFUNC2_ur0_rx_e2_src(data)                                               ((0x00040000&(data))>>18)
#define ISO_PFUNC2_get_ur0_rx_e2(data)                                               ((0x00040000&(data))>>18)
#define ISO_PFUNC2_ur0_rx_pud_en_shift                                               (17)
#define ISO_PFUNC2_ur0_rx_pud_en_mask                                                (0x00020000)
#define ISO_PFUNC2_ur0_rx_pud_en(data)                                               (0x00020000&((data)<<17))
#define ISO_PFUNC2_ur0_rx_pud_en_src(data)                                           ((0x00020000&(data))>>17)
#define ISO_PFUNC2_get_ur0_rx_pud_en(data)                                           ((0x00020000&(data))>>17)
#define ISO_PFUNC2_ur0_rx_pud_sel_shift                                              (16)
#define ISO_PFUNC2_ur0_rx_pud_sel_mask                                               (0x00010000)
#define ISO_PFUNC2_ur0_rx_pud_sel(data)                                              (0x00010000&((data)<<16))
#define ISO_PFUNC2_ur0_rx_pud_sel_src(data)                                          ((0x00010000&(data))>>16)
#define ISO_PFUNC2_get_ur0_rx_pud_sel(data)                                          ((0x00010000&(data))>>16)
#define ISO_PFUNC2_ur1_cts_n_smt_shift                                               (15)
#define ISO_PFUNC2_ur1_cts_n_smt_mask                                                (0x00008000)
#define ISO_PFUNC2_ur1_cts_n_smt(data)                                               (0x00008000&((data)<<15))
#define ISO_PFUNC2_ur1_cts_n_smt_src(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC2_get_ur1_cts_n_smt(data)                                           ((0x00008000&(data))>>15)
#define ISO_PFUNC2_ur1_cts_n_e2_shift                                                (14)
#define ISO_PFUNC2_ur1_cts_n_e2_mask                                                 (0x00004000)
#define ISO_PFUNC2_ur1_cts_n_e2(data)                                                (0x00004000&((data)<<14))
#define ISO_PFUNC2_ur1_cts_n_e2_src(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC2_get_ur1_cts_n_e2(data)                                            ((0x00004000&(data))>>14)
#define ISO_PFUNC2_ur1_cts_n_pud_en_shift                                            (13)
#define ISO_PFUNC2_ur1_cts_n_pud_en_mask                                             (0x00002000)
#define ISO_PFUNC2_ur1_cts_n_pud_en(data)                                            (0x00002000&((data)<<13))
#define ISO_PFUNC2_ur1_cts_n_pud_en_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC2_get_ur1_cts_n_pud_en(data)                                        ((0x00002000&(data))>>13)
#define ISO_PFUNC2_ur1_cts_n_pud_sel_shift                                           (12)
#define ISO_PFUNC2_ur1_cts_n_pud_sel_mask                                            (0x00001000)
#define ISO_PFUNC2_ur1_cts_n_pud_sel(data)                                           (0x00001000&((data)<<12))
#define ISO_PFUNC2_ur1_cts_n_pud_sel_src(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC2_get_ur1_cts_n_pud_sel(data)                                       ((0x00001000&(data))>>12)
#define ISO_PFUNC2_ur1_rts_n_smt_shift                                               (11)
#define ISO_PFUNC2_ur1_rts_n_smt_mask                                                (0x00000800)
#define ISO_PFUNC2_ur1_rts_n_smt(data)                                               (0x00000800&((data)<<11))
#define ISO_PFUNC2_ur1_rts_n_smt_src(data)                                           ((0x00000800&(data))>>11)
#define ISO_PFUNC2_get_ur1_rts_n_smt(data)                                           ((0x00000800&(data))>>11)
#define ISO_PFUNC2_ur1_rts_n_e2_shift                                                (10)
#define ISO_PFUNC2_ur1_rts_n_e2_mask                                                 (0x00000400)
#define ISO_PFUNC2_ur1_rts_n_e2(data)                                                (0x00000400&((data)<<10))
#define ISO_PFUNC2_ur1_rts_n_e2_src(data)                                            ((0x00000400&(data))>>10)
#define ISO_PFUNC2_get_ur1_rts_n_e2(data)                                            ((0x00000400&(data))>>10)
#define ISO_PFUNC2_ur1_rts_n_pud_en_shift                                            (9)
#define ISO_PFUNC2_ur1_rts_n_pud_en_mask                                             (0x00000200)
#define ISO_PFUNC2_ur1_rts_n_pud_en(data)                                            (0x00000200&((data)<<9))
#define ISO_PFUNC2_ur1_rts_n_pud_en_src(data)                                        ((0x00000200&(data))>>9)
#define ISO_PFUNC2_get_ur1_rts_n_pud_en(data)                                        ((0x00000200&(data))>>9)
#define ISO_PFUNC2_ur1_rts_n_pud_sel_shift                                           (8)
#define ISO_PFUNC2_ur1_rts_n_pud_sel_mask                                            (0x00000100)
#define ISO_PFUNC2_ur1_rts_n_pud_sel(data)                                           (0x00000100&((data)<<8))
#define ISO_PFUNC2_ur1_rts_n_pud_sel_src(data)                                       ((0x00000100&(data))>>8)
#define ISO_PFUNC2_get_ur1_rts_n_pud_sel(data)                                       ((0x00000100&(data))>>8)
#define ISO_PFUNC2_ur1_tx_smt_shift                                                  (7)
#define ISO_PFUNC2_ur1_tx_smt_mask                                                   (0x00000080)
#define ISO_PFUNC2_ur1_tx_smt(data)                                                  (0x00000080&((data)<<7))
#define ISO_PFUNC2_ur1_tx_smt_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_PFUNC2_get_ur1_tx_smt(data)                                              ((0x00000080&(data))>>7)
#define ISO_PFUNC2_ur1_tx_e2_shift                                                   (6)
#define ISO_PFUNC2_ur1_tx_e2_mask                                                    (0x00000040)
#define ISO_PFUNC2_ur1_tx_e2(data)                                                   (0x00000040&((data)<<6))
#define ISO_PFUNC2_ur1_tx_e2_src(data)                                               ((0x00000040&(data))>>6)
#define ISO_PFUNC2_get_ur1_tx_e2(data)                                               ((0x00000040&(data))>>6)
#define ISO_PFUNC2_ur1_tx_pud_en_shift                                               (5)
#define ISO_PFUNC2_ur1_tx_pud_en_mask                                                (0x00000020)
#define ISO_PFUNC2_ur1_tx_pud_en(data)                                               (0x00000020&((data)<<5))
#define ISO_PFUNC2_ur1_tx_pud_en_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_PFUNC2_get_ur1_tx_pud_en(data)                                           ((0x00000020&(data))>>5)
#define ISO_PFUNC2_ur1_tx_pud_sel_shift                                              (4)
#define ISO_PFUNC2_ur1_tx_pud_sel_mask                                               (0x00000010)
#define ISO_PFUNC2_ur1_tx_pud_sel(data)                                              (0x00000010&((data)<<4))
#define ISO_PFUNC2_ur1_tx_pud_sel_src(data)                                          ((0x00000010&(data))>>4)
#define ISO_PFUNC2_get_ur1_tx_pud_sel(data)                                          ((0x00000010&(data))>>4)
#define ISO_PFUNC2_ur1_rx_smt_shift                                                  (3)
#define ISO_PFUNC2_ur1_rx_smt_mask                                                   (0x00000008)
#define ISO_PFUNC2_ur1_rx_smt(data)                                                  (0x00000008&((data)<<3))
#define ISO_PFUNC2_ur1_rx_smt_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_PFUNC2_get_ur1_rx_smt(data)                                              ((0x00000008&(data))>>3)
#define ISO_PFUNC2_ur1_rx_e2_shift                                                   (2)
#define ISO_PFUNC2_ur1_rx_e2_mask                                                    (0x00000004)
#define ISO_PFUNC2_ur1_rx_e2(data)                                                   (0x00000004&((data)<<2))
#define ISO_PFUNC2_ur1_rx_e2_src(data)                                               ((0x00000004&(data))>>2)
#define ISO_PFUNC2_get_ur1_rx_e2(data)                                               ((0x00000004&(data))>>2)
#define ISO_PFUNC2_ur1_rx_pud_en_shift                                               (1)
#define ISO_PFUNC2_ur1_rx_pud_en_mask                                                (0x00000002)
#define ISO_PFUNC2_ur1_rx_pud_en(data)                                               (0x00000002&((data)<<1))
#define ISO_PFUNC2_ur1_rx_pud_en_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_PFUNC2_get_ur1_rx_pud_en(data)                                           ((0x00000002&(data))>>1)
#define ISO_PFUNC2_ur1_rx_pud_sel_shift                                              (0)
#define ISO_PFUNC2_ur1_rx_pud_sel_mask                                               (0x00000001)
#define ISO_PFUNC2_ur1_rx_pud_sel(data)                                              (0x00000001&((data)<<0))
#define ISO_PFUNC2_ur1_rx_pud_sel_src(data)                                          ((0x00000001&(data))>>0)
#define ISO_PFUNC2_get_ur1_rx_pud_sel(data)                                          ((0x00000001&(data))>>0)


#define ISO_MUXPAD                                                                   0x18007308
#define ISO_MUXPAD_reg_addr                                                          "0xB8007308"
#define ISO_MUXPAD_reg                                                               0xB8007308
#define set_ISO_MUXPAD_reg(data)   (*((volatile unsigned int*) ISO_MUXPAD_reg)=data)
#define get_ISO_MUXPAD_reg   (*((volatile unsigned int*) ISO_MUXPAD_reg))
#define ISO_MUXPAD_inst_adr                                                          "0x00C2"
#define ISO_MUXPAD_inst                                                              0x00C2
#define ISO_MUXPAD_ur0_tx_shift                                                      (22)
#define ISO_MUXPAD_ur0_tx_mask                                                       (0x00C00000)
#define ISO_MUXPAD_ur0_tx(data)                                                      (0x00C00000&((data)<<22))
#define ISO_MUXPAD_ur0_tx_src(data)                                                  ((0x00C00000&(data))>>22)
#define ISO_MUXPAD_get_ur0_tx(data)                                                  ((0x00C00000&(data))>>22)
#define ISO_MUXPAD_ur0_rx_shift                                                      (20)
#define ISO_MUXPAD_ur0_rx_mask                                                       (0x00300000)
#define ISO_MUXPAD_ur0_rx(data)                                                      (0x00300000&((data)<<20))
#define ISO_MUXPAD_ur0_rx_src(data)                                                  ((0x00300000&(data))>>20)
#define ISO_MUXPAD_get_ur0_rx(data)                                                  ((0x00300000&(data))>>20)
#define ISO_MUXPAD_ur1_cts_n_shift                                                   (18)
#define ISO_MUXPAD_ur1_cts_n_mask                                                    (0x000C0000)
#define ISO_MUXPAD_ur1_cts_n(data)                                                   (0x000C0000&((data)<<18))
#define ISO_MUXPAD_ur1_cts_n_src(data)                                               ((0x000C0000&(data))>>18)
#define ISO_MUXPAD_get_ur1_cts_n(data)                                               ((0x000C0000&(data))>>18)
#define ISO_MUXPAD_ur1_rts_n_shift                                                   (16)
#define ISO_MUXPAD_ur1_rts_n_mask                                                    (0x00030000)
#define ISO_MUXPAD_ur1_rts_n(data)                                                   (0x00030000&((data)<<16))
#define ISO_MUXPAD_ur1_rts_n_src(data)                                               ((0x00030000&(data))>>16)
#define ISO_MUXPAD_get_ur1_rts_n(data)                                               ((0x00030000&(data))>>16)
#define ISO_MUXPAD_ur1_tx_shift                                                      (14)
#define ISO_MUXPAD_ur1_tx_mask                                                       (0x0000C000)
#define ISO_MUXPAD_ur1_tx(data)                                                      (0x0000C000&((data)<<14))
#define ISO_MUXPAD_ur1_tx_src(data)                                                  ((0x0000C000&(data))>>14)
#define ISO_MUXPAD_get_ur1_tx(data)                                                  ((0x0000C000&(data))>>14)
#define ISO_MUXPAD_ur1_rx_shift                                                      (12)
#define ISO_MUXPAD_ur1_rx_mask                                                       (0x00003000)
#define ISO_MUXPAD_ur1_rx(data)                                                      (0x00003000&((data)<<12))
#define ISO_MUXPAD_ur1_rx_src(data)                                                  ((0x00003000&(data))>>12)
#define ISO_MUXPAD_get_ur1_rx(data)                                                  ((0x00003000&(data))>>12)
#define ISO_MUXPAD_usb1_shift                                                        (10)
#define ISO_MUXPAD_usb1_mask                                                         (0x00000C00)
#define ISO_MUXPAD_usb1(data)                                                        (0x00000C00&((data)<<10))
#define ISO_MUXPAD_usb1_src(data)                                                    ((0x00000C00&(data))>>10)
#define ISO_MUXPAD_get_usb1(data)                                                    ((0x00000C00&(data))>>10)
#define ISO_MUXPAD_usb0_shift                                                        (8)
#define ISO_MUXPAD_usb0_mask                                                         (0x00000300)
#define ISO_MUXPAD_usb0(data)                                                        (0x00000300&((data)<<8))
#define ISO_MUXPAD_usb0_src(data)                                                    ((0x00000300&(data))>>8)
#define ISO_MUXPAD_get_usb0(data)                                                    ((0x00000300&(data))>>8)
#define ISO_MUXPAD_ir_in_shift                                                       (6)
#define ISO_MUXPAD_ir_in_mask                                                        (0x000000C0)
#define ISO_MUXPAD_ir_in(data)                                                       (0x000000C0&((data)<<6))
#define ISO_MUXPAD_ir_in_src(data)                                                   ((0x000000C0&(data))>>6)
#define ISO_MUXPAD_get_ir_in(data)                                                   ((0x000000C0&(data))>>6)
#define ISO_MUXPAD_vfd_cs_n_shift                                                    (4)
#define ISO_MUXPAD_vfd_cs_n_mask                                                     (0x00000030)
#define ISO_MUXPAD_vfd_cs_n(data)                                                    (0x00000030&((data)<<4))
#define ISO_MUXPAD_vfd_cs_n_src(data)                                                ((0x00000030&(data))>>4)
#define ISO_MUXPAD_get_vfd_cs_n(data)                                                ((0x00000030&(data))>>4)
#define ISO_MUXPAD_vfd_clk_shift                                                     (2)
#define ISO_MUXPAD_vfd_clk_mask                                                      (0x0000000C)
#define ISO_MUXPAD_vfd_clk(data)                                                     (0x0000000C&((data)<<2))
#define ISO_MUXPAD_vfd_clk_src(data)                                                 ((0x0000000C&(data))>>2)
#define ISO_MUXPAD_get_vfd_clk(data)                                                 ((0x0000000C&(data))>>2)
#define ISO_MUXPAD_vfd_d_shift                                                       (0)
#define ISO_MUXPAD_vfd_d_mask                                                        (0x00000003)
#define ISO_MUXPAD_vfd_d(data)                                                       (0x00000003&((data)<<0))
#define ISO_MUXPAD_vfd_d_src(data)                                                   ((0x00000003&(data))>>0)
#define ISO_MUXPAD_get_vfd_d(data)                                                   ((0x00000003&(data))>>0)


#define ISO_IR_PSR                                                                   0x18007400
#define ISO_IR_PSR_reg_addr                                                          "0xB8007400"
#define ISO_IR_PSR_reg                                                               0xB8007400
#define set_ISO_IR_PSR_reg(data)   (*((volatile unsigned int*) ISO_IR_PSR_reg)=data)
#define get_ISO_IR_PSR_reg   (*((volatile unsigned int*) ISO_IR_PSR_reg))
#define ISO_IR_PSR_inst_adr                                                          "0x0000"
#define ISO_IR_PSR_inst                                                              0x0000
#define ISO_IR_PSR_irrbl_shift                                                       (24)
#define ISO_IR_PSR_irrbl_mask                                                        (0xFF000000)
#define ISO_IR_PSR_irrbl(data)                                                       (0xFF000000&((data)<<24))
#define ISO_IR_PSR_irrbl_src(data)                                                   ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_get_irrbl(data)                                                   ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_irrml_shift                                                       (16)
#define ISO_IR_PSR_irrml_mask                                                        (0x00FF0000)
#define ISO_IR_PSR_irrml(data)                                                       (0x00FF0000&((data)<<16))
#define ISO_IR_PSR_irrml_src(data)                                                   ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_get_irrml(data)                                                   ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_irrdzl_shift                                                      (8)
#define ISO_IR_PSR_irrdzl_mask                                                       (0x0000FF00)
#define ISO_IR_PSR_irrdzl(data)                                                      (0x0000FF00&((data)<<8))
#define ISO_IR_PSR_irrdzl_src(data)                                                  ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_get_irrdzl(data)                                                  ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_irrdol_shift                                                      (0)
#define ISO_IR_PSR_irrdol_mask                                                       (0x000000FF)
#define ISO_IR_PSR_irrdol(data)                                                      (0x000000FF&((data)<<0))
#define ISO_IR_PSR_irrdol_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_IR_PSR_get_irrdol(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_IR_PER                                                                   0x18007404
#define ISO_IR_PER_reg_addr                                                          "0xB8007404"
#define ISO_IR_PER_reg                                                               0xB8007404
#define set_ISO_IR_PER_reg(data)   (*((volatile unsigned int*) ISO_IR_PER_reg)=data)
#define get_ISO_IR_PER_reg   (*((volatile unsigned int*) ISO_IR_PER_reg))
#define ISO_IR_PER_inst_adr                                                          "0x0001"
#define ISO_IR_PER_inst                                                              0x0001
#define ISO_IR_PER_irrdl_shift                                                       (16)
#define ISO_IR_PER_irrdl_mask                                                        (0x003F0000)
#define ISO_IR_PER_irrdl(data)                                                       (0x003F0000&((data)<<16))
#define ISO_IR_PER_irrdl_src(data)                                                   ((0x003F0000&(data))>>16)
#define ISO_IR_PER_get_irrdl(data)                                                   ((0x003F0000&(data))>>16)
#define ISO_IR_PER_irrrl_shift                                                       (8)
#define ISO_IR_PER_irrrl_mask                                                        (0x0000FF00)
#define ISO_IR_PER_irrrl(data)                                                       (0x0000FF00&((data)<<8))
#define ISO_IR_PER_irrrl_src(data)                                                   ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_get_irrrl(data)                                                   ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_irrsl_shift                                                       (0)
#define ISO_IR_PER_irrsl_mask                                                        (0x000000FF)
#define ISO_IR_PER_irrsl(data)                                                       (0x000000FF&((data)<<0))
#define ISO_IR_PER_irrsl_src(data)                                                   ((0x000000FF&(data))>>0)
#define ISO_IR_PER_get_irrsl(data)                                                   ((0x000000FF&(data))>>0)


#define ISO_IR_SF                                                                    0x18007408
#define ISO_IR_SF_reg_addr                                                           "0xB8007408"
#define ISO_IR_SF_reg                                                                0xB8007408
#define set_ISO_IR_SF_reg(data)   (*((volatile unsigned int*) ISO_IR_SF_reg)=data)
#define get_ISO_IR_SF_reg   (*((volatile unsigned int*) ISO_IR_SF_reg))
#define ISO_IR_SF_inst_adr                                                           "0x0002"
#define ISO_IR_SF_inst                                                               0x0002
#define ISO_IR_SF_irfd_shift                                                         (0)
#define ISO_IR_SF_irfd_mask                                                          (0x0000FFFF)
#define ISO_IR_SF_irfd(data)                                                         (0x0000FFFF&((data)<<0))
#define ISO_IR_SF_irfd_src(data)                                                     ((0x0000FFFF&(data))>>0)
#define ISO_IR_SF_get_irfd(data)                                                     ((0x0000FFFF&(data))>>0)


#define ISO_IR_DPIR                                                                  0x1800740C
#define ISO_IR_DPIR_reg_addr                                                         "0xB800740C"
#define ISO_IR_DPIR_reg                                                              0xB800740C
#define set_ISO_IR_DPIR_reg(data)   (*((volatile unsigned int*) ISO_IR_DPIR_reg)=data)
#define get_ISO_IR_DPIR_reg   (*((volatile unsigned int*) ISO_IR_DPIR_reg))
#define ISO_IR_DPIR_inst_adr                                                         "0x0003"
#define ISO_IR_DPIR_inst                                                             0x0003
#define ISO_IR_DPIR_iriotcdp_shift                                                   (0)
#define ISO_IR_DPIR_iriotcdp_mask                                                    (0x0000FFFF)
#define ISO_IR_DPIR_iriotcdp(data)                                                   (0x0000FFFF&((data)<<0))
#define ISO_IR_DPIR_iriotcdp_src(data)                                               ((0x0000FFFF&(data))>>0)
#define ISO_IR_DPIR_get_iriotcdp(data)                                               ((0x0000FFFF&(data))>>0)


#define ISO_IR_CR                                                                    0x18007410
#define ISO_IR_CR_reg_addr                                                           "0xB8007410"
#define ISO_IR_CR_reg                                                                0xB8007410
#define set_ISO_IR_CR_reg(data)   (*((volatile unsigned int*) ISO_IR_CR_reg)=data)
#define get_ISO_IR_CR_reg   (*((volatile unsigned int*) ISO_IR_CR_reg))
#define ISO_IR_CR_inst_adr                                                           "0x0004"
#define ISO_IR_CR_inst                                                               0x0004
#define ISO_IR_CR_irsr_shift                                                         (31)
#define ISO_IR_CR_irsr_mask                                                          (0x80000000)
#define ISO_IR_CR_irsr(data)                                                         (0x80000000&((data)<<31))
#define ISO_IR_CR_irsr_src(data)                                                     ((0x80000000&(data))>>31)
#define ISO_IR_CR_get_irsr(data)                                                     ((0x80000000&(data))>>31)
#define ISO_IR_CR_rcmm_en_shift                                                      (25)
#define ISO_IR_CR_rcmm_en_mask                                                       (0x02000000)
#define ISO_IR_CR_rcmm_en(data)                                                      (0x02000000&((data)<<25))
#define ISO_IR_CR_rcmm_en_src(data)                                                  ((0x02000000&(data))>>25)
#define ISO_IR_CR_get_rcmm_en(data)                                                  ((0x02000000&(data))>>25)
#define ISO_IR_CR_toshiba_en_shift                                                   (24)
#define ISO_IR_CR_toshiba_en_mask                                                    (0x01000000)
#define ISO_IR_CR_toshiba_en(data)                                                   (0x01000000&((data)<<24))
#define ISO_IR_CR_toshiba_en_src(data)                                               ((0x01000000&(data))>>24)
#define ISO_IR_CR_get_toshiba_en(data)                                               ((0x01000000&(data))>>24)
#define ISO_IR_CR_irednm_shift                                                       (23)
#define ISO_IR_CR_irednm_mask                                                        (0x00800000)
#define ISO_IR_CR_irednm(data)                                                       (0x00800000&((data)<<23))
#define ISO_IR_CR_irednm_src(data)                                                   ((0x00800000&(data))>>23)
#define ISO_IR_CR_get_irednm(data)                                                   ((0x00800000&(data))>>23)
#define ISO_IR_CR_iredn_shift                                                        (16)
#define ISO_IR_CR_iredn_mask                                                         (0x003F0000)
#define ISO_IR_CR_iredn(data)                                                        (0x003F0000&((data)<<16))
#define ISO_IR_CR_iredn_src(data)                                                    ((0x003F0000&(data))>>16)
#define ISO_IR_CR_get_iredn(data)                                                    ((0x003F0000&(data))>>16)
#define ISO_IR_CR_raw_fifo_ov_shift                                                  (14)
#define ISO_IR_CR_raw_fifo_ov_mask                                                   (0x00004000)
#define ISO_IR_CR_raw_fifo_ov(data)                                                  (0x00004000&((data)<<14))
#define ISO_IR_CR_raw_fifo_ov_src(data)                                              ((0x00004000&(data))>>14)
#define ISO_IR_CR_get_raw_fifo_ov(data)                                              ((0x00004000&(data))>>14)
#define ISO_IR_CR_raw_fifo_val_shift                                                 (13)
#define ISO_IR_CR_raw_fifo_val_mask                                                  (0x00002000)
#define ISO_IR_CR_raw_fifo_val(data)                                                 (0x00002000&((data)<<13))
#define ISO_IR_CR_raw_fifo_val_src(data)                                             ((0x00002000&(data))>>13)
#define ISO_IR_CR_get_raw_fifo_val(data)                                             ((0x00002000&(data))>>13)
#define ISO_IR_CR_raw_en_shift                                                       (12)
#define ISO_IR_CR_raw_en_mask                                                        (0x00001000)
#define ISO_IR_CR_raw_en(data)                                                       (0x00001000&((data)<<12))
#define ISO_IR_CR_raw_en_src(data)                                                   ((0x00001000&(data))>>12)
#define ISO_IR_CR_get_raw_en(data)                                                   ((0x00001000&(data))>>12)
#define ISO_IR_CR_mlae_shift                                                         (11)
#define ISO_IR_CR_mlae_mask                                                          (0x00000800)
#define ISO_IR_CR_mlae(data)                                                         (0x00000800&((data)<<11))
#define ISO_IR_CR_mlae_src(data)                                                     ((0x00000800&(data))>>11)
#define ISO_IR_CR_get_mlae(data)                                                     ((0x00000800&(data))>>11)
#define ISO_IR_CR_irie_shift                                                         (10)
#define ISO_IR_CR_irie_mask                                                          (0x00000400)
#define ISO_IR_CR_irie(data)                                                         (0x00000400&((data)<<10))
#define ISO_IR_CR_irie_src(data)                                                     ((0x00000400&(data))>>10)
#define ISO_IR_CR_get_irie(data)                                                     ((0x00000400&(data))>>10)
#define ISO_IR_CR_irres_shift                                                        (9)
#define ISO_IR_CR_irres_mask                                                         (0x00000200)
#define ISO_IR_CR_irres(data)                                                        (0x00000200&((data)<<9))
#define ISO_IR_CR_irres_src(data)                                                    ((0x00000200&(data))>>9)
#define ISO_IR_CR_get_irres(data)                                                    ((0x00000200&(data))>>9)
#define ISO_IR_CR_irue_shift                                                         (8)
#define ISO_IR_CR_irue_mask                                                          (0x00000100)
#define ISO_IR_CR_irue(data)                                                         (0x00000100&((data)<<8))
#define ISO_IR_CR_irue_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_IR_CR_get_irue(data)                                                     ((0x00000100&(data))>>8)
#define ISO_IR_CR_ircm_shift                                                         (7)
#define ISO_IR_CR_ircm_mask                                                          (0x00000080)
#define ISO_IR_CR_ircm(data)                                                         (0x00000080&((data)<<7))
#define ISO_IR_CR_ircm_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_IR_CR_get_ircm(data)                                                     ((0x00000080&(data))>>7)
#define ISO_IR_CR_irbme_shift                                                        (6)
#define ISO_IR_CR_irbme_mask                                                         (0x00000040)
#define ISO_IR_CR_irbme(data)                                                        (0x00000040&((data)<<6))
#define ISO_IR_CR_irbme_src(data)                                                    ((0x00000040&(data))>>6)
#define ISO_IR_CR_get_irbme(data)                                                    ((0x00000040&(data))>>6)
#define ISO_IR_CR_irdpm_shift                                                        (5)
#define ISO_IR_CR_irdpm_mask                                                         (0x00000020)
#define ISO_IR_CR_irdpm(data)                                                        (0x00000020&((data)<<5))
#define ISO_IR_CR_irdpm_src(data)                                                    ((0x00000020&(data))>>5)
#define ISO_IR_CR_get_irdpm(data)                                                    ((0x00000020&(data))>>5)
#define ISO_IR_CR_irdn_shift                                                         (0)
#define ISO_IR_CR_irdn_mask                                                          (0x0000001F)
#define ISO_IR_CR_irdn(data)                                                         (0x0000001F&((data)<<0))
#define ISO_IR_CR_irdn_src(data)                                                     ((0x0000001F&(data))>>0)
#define ISO_IR_CR_get_irdn(data)                                                     ((0x0000001F&(data))>>0)


#define ISO_IR_RP                                                                    0x18007414
#define ISO_IR_RP_reg_addr                                                           "0xB8007414"
#define ISO_IR_RP_reg                                                                0xB8007414
#define set_ISO_IR_RP_reg(data)   (*((volatile unsigned int*) ISO_IR_RP_reg)=data)
#define get_ISO_IR_RP_reg   (*((volatile unsigned int*) ISO_IR_RP_reg))
#define ISO_IR_RP_inst_adr                                                           "0x0005"
#define ISO_IR_RP_inst                                                               0x0005
#define ISO_IR_RP_irrp_shift                                                         (0)
#define ISO_IR_RP_irrp_mask                                                          (0xFFFFFFFF)
#define ISO_IR_RP_irrp(data)                                                         (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RP_irrp_src(data)                                                     ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RP_get_irrp(data)                                                     ((0xFFFFFFFF&(data))>>0)


#define ISO_IR_SR                                                                    0x18007418
#define ISO_IR_SR_reg_addr                                                           "0xB8007418"
#define ISO_IR_SR_reg                                                                0xB8007418
#define set_ISO_IR_SR_reg(data)   (*((volatile unsigned int*) ISO_IR_SR_reg)=data)
#define get_ISO_IR_SR_reg   (*((volatile unsigned int*) ISO_IR_SR_reg))
#define ISO_IR_SR_inst_adr                                                           "0x0006"
#define ISO_IR_SR_inst                                                               0x0006
#define ISO_IR_SR_rmt_big_shift                                                      (4)
#define ISO_IR_SR_rmt_big_mask                                                       (0x00000010)
#define ISO_IR_SR_rmt_big(data)                                                      (0x00000010&((data)<<4))
#define ISO_IR_SR_rmt_big_src(data)                                                  ((0x00000010&(data))>>4)
#define ISO_IR_SR_get_rmt_big(data)                                                  ((0x00000010&(data))>>4)
#define ISO_IR_SR_raw_fifo_ov_shift                                                  (3)
#define ISO_IR_SR_raw_fifo_ov_mask                                                   (0x00000008)
#define ISO_IR_SR_raw_fifo_ov(data)                                                  (0x00000008&((data)<<3))
#define ISO_IR_SR_raw_fifo_ov_src(data)                                              ((0x00000008&(data))>>3)
#define ISO_IR_SR_get_raw_fifo_ov(data)                                              ((0x00000008&(data))>>3)
#define ISO_IR_SR_raw_fifo_val_shift                                                 (2)
#define ISO_IR_SR_raw_fifo_val_mask                                                  (0x00000004)
#define ISO_IR_SR_raw_fifo_val(data)                                                 (0x00000004&((data)<<2))
#define ISO_IR_SR_raw_fifo_val_src(data)                                             ((0x00000004&(data))>>2)
#define ISO_IR_SR_get_raw_fifo_val(data)                                             ((0x00000004&(data))>>2)
#define ISO_IR_SR_irrf_shift                                                         (1)
#define ISO_IR_SR_irrf_mask                                                          (0x00000002)
#define ISO_IR_SR_irrf(data)                                                         (0x00000002&((data)<<1))
#define ISO_IR_SR_irrf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_IR_SR_get_irrf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_IR_SR_irdvf_shift                                                        (0)
#define ISO_IR_SR_irdvf_mask                                                         (0x00000001)
#define ISO_IR_SR_irdvf(data)                                                        (0x00000001&((data)<<0))
#define ISO_IR_SR_irdvf_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_IR_SR_get_irdvf(data)                                                    ((0x00000001&(data))>>0)


#define ISO_IR_RAW_CTRL                                                              0x1800741C
#define ISO_IR_RAW_CTRL_reg_addr                                                     "0xB800741C"
#define ISO_IR_RAW_CTRL_reg                                                          0xB800741C
#define set_ISO_IR_RAW_CTRL_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_CTRL_reg)=data)
#define get_ISO_IR_RAW_CTRL_reg   (*((volatile unsigned int*) ISO_IR_RAW_CTRL_reg))
#define ISO_IR_RAW_CTRL_inst_adr                                                     "0x0007"
#define ISO_IR_RAW_CTRL_inst                                                         0x0007
#define ISO_IR_RAW_CTRL_write_en2_shift                                              (25)
#define ISO_IR_RAW_CTRL_write_en2_mask                                               (0x02000000)
#define ISO_IR_RAW_CTRL_write_en2(data)                                              (0x02000000&((data)<<25))
#define ISO_IR_RAW_CTRL_write_en2_src(data)                                          ((0x02000000&(data))>>25)
#define ISO_IR_RAW_CTRL_get_write_en2(data)                                          ((0x02000000&(data))>>25)
#define ISO_IR_RAW_CTRL_stop_sample_shift                                            (24)
#define ISO_IR_RAW_CTRL_stop_sample_mask                                             (0x01000000)
#define ISO_IR_RAW_CTRL_stop_sample(data)                                            (0x01000000&((data)<<24))
#define ISO_IR_RAW_CTRL_stop_sample_src(data)                                        ((0x01000000&(data))>>24)
#define ISO_IR_RAW_CTRL_get_stop_sample(data)                                        ((0x01000000&(data))>>24)
#define ISO_IR_RAW_CTRL_stop_time_shift                                              (8)
#define ISO_IR_RAW_CTRL_stop_time_mask                                               (0x00FFFF00)
#define ISO_IR_RAW_CTRL_stop_time(data)                                              (0x00FFFF00&((data)<<8))
#define ISO_IR_RAW_CTRL_stop_time_src(data)                                          ((0x00FFFF00&(data))>>8)
#define ISO_IR_RAW_CTRL_get_stop_time(data)                                          ((0x00FFFF00&(data))>>8)
#define ISO_IR_RAW_CTRL_write_en1_shift                                              (6)
#define ISO_IR_RAW_CTRL_write_en1_mask                                               (0x00000040)
#define ISO_IR_RAW_CTRL_write_en1(data)                                              (0x00000040&((data)<<6))
#define ISO_IR_RAW_CTRL_write_en1_src(data)                                          ((0x00000040&(data))>>6)
#define ISO_IR_RAW_CTRL_get_write_en1(data)                                          ((0x00000040&(data))>>6)
#define ISO_IR_RAW_CTRL_fifo_thr_shift                                               (0)
#define ISO_IR_RAW_CTRL_fifo_thr_mask                                                (0x0000003F)
#define ISO_IR_RAW_CTRL_fifo_thr(data)                                               (0x0000003F&((data)<<0))
#define ISO_IR_RAW_CTRL_fifo_thr_src(data)                                           ((0x0000003F&(data))>>0)
#define ISO_IR_RAW_CTRL_get_fifo_thr(data)                                           ((0x0000003F&(data))>>0)


#define ISO_IR_RAW_FF                                                                0x18007420
#define ISO_IR_RAW_FF_reg_addr                                                       "0xB8007420"
#define ISO_IR_RAW_FF_reg                                                            0xB8007420
#define set_ISO_IR_RAW_FF_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_FF_reg)=data)
#define get_ISO_IR_RAW_FF_reg   (*((volatile unsigned int*) ISO_IR_RAW_FF_reg))
#define ISO_IR_RAW_FF_inst_adr                                                       "0x0008"
#define ISO_IR_RAW_FF_inst                                                           0x0008
#define ISO_IR_RAW_FF_dat_shift                                                      (0)
#define ISO_IR_RAW_FF_dat_mask                                                       (0xFFFFFFFF)
#define ISO_IR_RAW_FF_dat(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RAW_FF_dat_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RAW_FF_get_dat(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_IR_RAW_SAMPLE_TIME                                                       0x18007424
#define ISO_IR_RAW_SAMPLE_TIME_reg_addr                                              "0xB8007424"
#define ISO_IR_RAW_SAMPLE_TIME_reg                                                   0xB8007424
#define set_ISO_IR_RAW_SAMPLE_TIME_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_SAMPLE_TIME_reg)=data)
#define get_ISO_IR_RAW_SAMPLE_TIME_reg   (*((volatile unsigned int*) ISO_IR_RAW_SAMPLE_TIME_reg))
#define ISO_IR_RAW_SAMPLE_TIME_inst_adr                                              "0x0009"
#define ISO_IR_RAW_SAMPLE_TIME_inst                                                  0x0009
#define ISO_IR_RAW_SAMPLE_TIME_cnt_shift                                             (0)
#define ISO_IR_RAW_SAMPLE_TIME_cnt_mask                                              (0x0000FFFF)
#define ISO_IR_RAW_SAMPLE_TIME_cnt(data)                                             (0x0000FFFF&((data)<<0))
#define ISO_IR_RAW_SAMPLE_TIME_cnt_src(data)                                         ((0x0000FFFF&(data))>>0)
#define ISO_IR_RAW_SAMPLE_TIME_get_cnt(data)                                         ((0x0000FFFF&(data))>>0)


#define ISO_IR_RAW_WL                                                                0x18007428
#define ISO_IR_RAW_WL_reg_addr                                                       "0xB8007428"
#define ISO_IR_RAW_WL_reg                                                            0xB8007428
#define set_ISO_IR_RAW_WL_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_WL_reg)=data)
#define get_ISO_IR_RAW_WL_reg   (*((volatile unsigned int*) ISO_IR_RAW_WL_reg))
#define ISO_IR_RAW_WL_inst_adr                                                       "0x000A"
#define ISO_IR_RAW_WL_inst                                                           0x000A
#define ISO_IR_RAW_WL_val_shift                                                      (0)
#define ISO_IR_RAW_WL_val_mask                                                       (0x0000003F)
#define ISO_IR_RAW_WL_val(data)                                                      (0x0000003F&((data)<<0))
#define ISO_IR_RAW_WL_val_src(data)                                                  ((0x0000003F&(data))>>0)
#define ISO_IR_RAW_WL_get_val(data)                                                  ((0x0000003F&(data))>>0)


#define ISO_IR_RAW_DEB                                                               0x1800742C
#define ISO_IR_RAW_DEB_reg_addr                                                      "0xB800742C"
#define ISO_IR_RAW_DEB_reg                                                           0xB800742C
#define set_ISO_IR_RAW_DEB_reg(data)   (*((volatile unsigned int*) ISO_IR_RAW_DEB_reg)=data)
#define get_ISO_IR_RAW_DEB_reg   (*((volatile unsigned int*) ISO_IR_RAW_DEB_reg))
#define ISO_IR_RAW_DEB_inst_adr                                                      "0x000B"
#define ISO_IR_RAW_DEB_inst                                                          0x000B
#define ISO_IR_RAW_DEB_len_shift                                                     (16)
#define ISO_IR_RAW_DEB_len_mask                                                      (0x00FF0000)
#define ISO_IR_RAW_DEB_len(data)                                                     (0x00FF0000&((data)<<16))
#define ISO_IR_RAW_DEB_len_src(data)                                                 ((0x00FF0000&(data))>>16)
#define ISO_IR_RAW_DEB_get_len(data)                                                 ((0x00FF0000&(data))>>16)
#define ISO_IR_RAW_DEB_clk_shift                                                     (0)
#define ISO_IR_RAW_DEB_clk_mask                                                      (0x0000FFFF)
#define ISO_IR_RAW_DEB_clk(data)                                                     (0x0000FFFF&((data)<<0))
#define ISO_IR_RAW_DEB_clk_src(data)                                                 ((0x0000FFFF&(data))>>0)
#define ISO_IR_RAW_DEB_get_clk(data)                                                 ((0x0000FFFF&(data))>>0)


#define ISO_IR_PSR_UP                                                                0x18007430
#define ISO_IR_PSR_UP_reg_addr                                                       "0xB8007430"
#define ISO_IR_PSR_UP_reg                                                            0xB8007430
#define set_ISO_IR_PSR_UP_reg(data)   (*((volatile unsigned int*) ISO_IR_PSR_UP_reg)=data)
#define get_ISO_IR_PSR_UP_reg   (*((volatile unsigned int*) ISO_IR_PSR_UP_reg))
#define ISO_IR_PSR_UP_inst_adr                                                       "0x000C"
#define ISO_IR_PSR_UP_inst                                                           0x000C
#define ISO_IR_PSR_UP_irrbl_shift                                                    (24)
#define ISO_IR_PSR_UP_irrbl_mask                                                     (0xFF000000)
#define ISO_IR_PSR_UP_irrbl(data)                                                    (0xFF000000&((data)<<24))
#define ISO_IR_PSR_UP_irrbl_src(data)                                                ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_UP_get_irrbl(data)                                                ((0xFF000000&(data))>>24)
#define ISO_IR_PSR_UP_irrml_shift                                                    (16)
#define ISO_IR_PSR_UP_irrml_mask                                                     (0x00FF0000)
#define ISO_IR_PSR_UP_irrml(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_IR_PSR_UP_irrml_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_UP_get_irrml(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_IR_PSR_UP_irrdzl_shift                                                   (8)
#define ISO_IR_PSR_UP_irrdzl_mask                                                    (0x0000FF00)
#define ISO_IR_PSR_UP_irrdzl(data)                                                   (0x0000FF00&((data)<<8))
#define ISO_IR_PSR_UP_irrdzl_src(data)                                               ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_UP_get_irrdzl(data)                                               ((0x0000FF00&(data))>>8)
#define ISO_IR_PSR_UP_irrdol_shift                                                   (0)
#define ISO_IR_PSR_UP_irrdol_mask                                                    (0x000000FF)
#define ISO_IR_PSR_UP_irrdol(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IR_PSR_UP_irrdol_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IR_PSR_UP_get_irrdol(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IR_PER_UP                                                                0x18007434
#define ISO_IR_PER_UP_reg_addr                                                       "0xB8007434"
#define ISO_IR_PER_UP_reg                                                            0xB8007434
#define set_ISO_IR_PER_UP_reg(data)   (*((volatile unsigned int*) ISO_IR_PER_UP_reg)=data)
#define get_ISO_IR_PER_UP_reg   (*((volatile unsigned int*) ISO_IR_PER_UP_reg))
#define ISO_IR_PER_UP_inst_adr                                                       "0x000D"
#define ISO_IR_PER_UP_inst                                                           0x000D
#define ISO_IR_PER_UP_irrrl_shift                                                    (8)
#define ISO_IR_PER_UP_irrrl_mask                                                     (0x0000FF00)
#define ISO_IR_PER_UP_irrrl(data)                                                    (0x0000FF00&((data)<<8))
#define ISO_IR_PER_UP_irrrl_src(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_UP_get_irrrl(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_IR_PER_UP_irrsl_shift                                                    (0)
#define ISO_IR_PER_UP_irrsl_mask                                                     (0x000000FF)
#define ISO_IR_PER_UP_irrsl(data)                                                    (0x000000FF&((data)<<0))
#define ISO_IR_PER_UP_irrsl_src(data)                                                ((0x000000FF&(data))>>0)
#define ISO_IR_PER_UP_get_irrsl(data)                                                ((0x000000FF&(data))>>0)


#define ISO_IR_CTRL_RC6                                                              0x18007438
#define ISO_IR_CTRL_RC6_reg_addr                                                     "0xB8007438"
#define ISO_IR_CTRL_RC6_reg                                                          0xB8007438
#define set_ISO_IR_CTRL_RC6_reg(data)   (*((volatile unsigned int*) ISO_IR_CTRL_RC6_reg)=data)
#define get_ISO_IR_CTRL_RC6_reg   (*((volatile unsigned int*) ISO_IR_CTRL_RC6_reg))
#define ISO_IR_CTRL_RC6_inst_adr                                                     "0x000E"
#define ISO_IR_CTRL_RC6_inst                                                         0x000E
#define ISO_IR_CTRL_RC6_rc6_en_shift                                                 (8)
#define ISO_IR_CTRL_RC6_rc6_en_mask                                                  (0x00000100)
#define ISO_IR_CTRL_RC6_rc6_en(data)                                                 (0x00000100&((data)<<8))
#define ISO_IR_CTRL_RC6_rc6_en_src(data)                                             ((0x00000100&(data))>>8)
#define ISO_IR_CTRL_RC6_get_rc6_en(data)                                             ((0x00000100&(data))>>8)
#define ISO_IR_CTRL_RC6_irtr_shift                                                   (0)
#define ISO_IR_CTRL_RC6_irtr_mask                                                    (0x000000FF)
#define ISO_IR_CTRL_RC6_irtr(data)                                                   (0x000000FF&((data)<<0))
#define ISO_IR_CTRL_RC6_irtr_src(data)                                               ((0x000000FF&(data))>>0)
#define ISO_IR_CTRL_RC6_get_irtr(data)                                               ((0x000000FF&(data))>>0)


#define ISO_IR_RP2                                                                   0x1800743C
#define ISO_IR_RP2_reg_addr                                                          "0xB800743C"
#define ISO_IR_RP2_reg                                                               0xB800743C
#define set_ISO_IR_RP2_reg(data)   (*((volatile unsigned int*) ISO_IR_RP2_reg)=data)
#define get_ISO_IR_RP2_reg   (*((volatile unsigned int*) ISO_IR_RP2_reg))
#define ISO_IR_RP2_inst_adr                                                          "0x000F"
#define ISO_IR_RP2_inst                                                              0x000F
#define ISO_IR_RP2_irrp_shift                                                        (0)
#define ISO_IR_RP2_irrp_mask                                                         (0xFFFFFFFF)
#define ISO_IR_RP2_irrp(data)                                                        (0xFFFFFFFF&((data)<<0))
#define ISO_IR_RP2_irrp_src(data)                                                    ((0xFFFFFFFF&(data))>>0)
#define ISO_IR_RP2_get_irrp(data)                                                    ((0xFFFFFFFF&(data))>>0)


#define ISO_IRTX_CFG                                                                 0x18007440
#define ISO_IRTX_CFG_reg_addr                                                        "0xB8007440"
#define ISO_IRTX_CFG_reg                                                             0xB8007440
#define set_ISO_IRTX_CFG_reg(data)   (*((volatile unsigned int*) ISO_IRTX_CFG_reg)=data)
#define get_ISO_IRTX_CFG_reg   (*((volatile unsigned int*) ISO_IRTX_CFG_reg))
#define ISO_IRTX_CFG_inst_adr                                                        "0x0010"
#define ISO_IRTX_CFG_inst                                                            0x0010
#define ISO_IRTX_CFG_irtx_en_shift                                                   (31)
#define ISO_IRTX_CFG_irtx_en_mask                                                    (0x80000000)
#define ISO_IRTX_CFG_irtx_en(data)                                                   (0x80000000&((data)<<31))
#define ISO_IRTX_CFG_irtx_en_src(data)                                               ((0x80000000&(data))>>31)
#define ISO_IRTX_CFG_get_irtx_en(data)                                               ((0x80000000&(data))>>31)
#define ISO_IRTX_CFG_iact_lvl_shift                                                  (10)
#define ISO_IRTX_CFG_iact_lvl_mask                                                   (0x00000400)
#define ISO_IRTX_CFG_iact_lvl(data)                                                  (0x00000400&((data)<<10))
#define ISO_IRTX_CFG_iact_lvl_src(data)                                              ((0x00000400&(data))>>10)
#define ISO_IRTX_CFG_get_iact_lvl(data)                                              ((0x00000400&(data))>>10)
#define ISO_IRTX_CFG_modulation_shift                                                (9)
#define ISO_IRTX_CFG_modulation_mask                                                 (0x00000200)
#define ISO_IRTX_CFG_modulation(data)                                                (0x00000200&((data)<<9))
#define ISO_IRTX_CFG_modulation_src(data)                                            ((0x00000200&(data))>>9)
#define ISO_IRTX_CFG_get_modulation(data)                                            ((0x00000200&(data))>>9)
#define ISO_IRTX_CFG_endian_shift                                                    (8)
#define ISO_IRTX_CFG_endian_mask                                                     (0x00000100)
#define ISO_IRTX_CFG_endian(data)                                                    (0x00000100&((data)<<8))
#define ISO_IRTX_CFG_endian_src(data)                                                ((0x00000100&(data))>>8)
#define ISO_IRTX_CFG_get_endian(data)                                                ((0x00000100&(data))>>8)
#define ISO_IRTX_CFG_dummy_shift                                                     (6)
#define ISO_IRTX_CFG_dummy_mask                                                      (0x000000C0)
#define ISO_IRTX_CFG_dummy(data)                                                     (0x000000C0&((data)<<6))
#define ISO_IRTX_CFG_dummy_src(data)                                                 ((0x000000C0&(data))>>6)
#define ISO_IRTX_CFG_get_dummy(data)                                                 ((0x000000C0&(data))>>6)
#define ISO_IRTX_CFG_fifoout_inv_shift                                               (5)
#define ISO_IRTX_CFG_fifoout_inv_mask                                                (0x00000020)
#define ISO_IRTX_CFG_fifoout_inv(data)                                               (0x00000020&((data)<<5))
#define ISO_IRTX_CFG_fifoout_inv_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_IRTX_CFG_get_fifoout_inv(data)                                           ((0x00000020&(data))>>5)
#define ISO_IRTX_CFG_irtxout_inv_shift                                               (4)
#define ISO_IRTX_CFG_irtxout_inv_mask                                                (0x00000010)
#define ISO_IRTX_CFG_irtxout_inv(data)                                               (0x00000010&((data)<<4))
#define ISO_IRTX_CFG_irtxout_inv_src(data)                                           ((0x00000010&(data))>>4)
#define ISO_IRTX_CFG_get_irtxout_inv(data)                                           ((0x00000010&(data))>>4)
#define ISO_IRTX_CFG_start_shift                                                     (0)
#define ISO_IRTX_CFG_start_mask                                                      (0x00000001)
#define ISO_IRTX_CFG_start(data)                                                     (0x00000001&((data)<<0))
#define ISO_IRTX_CFG_start_src(data)                                                 ((0x00000001&(data))>>0)
#define ISO_IRTX_CFG_get_start(data)                                                 ((0x00000001&(data))>>0)


#define ISO_IRTX_TIM                                                                 0x18007444
#define ISO_IRTX_TIM_reg_addr                                                        "0xB8007444"
#define ISO_IRTX_TIM_reg                                                             0xB8007444
#define set_ISO_IRTX_TIM_reg(data)   (*((volatile unsigned int*) ISO_IRTX_TIM_reg)=data)
#define get_ISO_IRTX_TIM_reg   (*((volatile unsigned int*) ISO_IRTX_TIM_reg))
#define ISO_IRTX_TIM_inst_adr                                                        "0x0011"
#define ISO_IRTX_TIM_inst                                                            0x0011
#define ISO_IRTX_TIM_irtx_fd_shift                                                   (0)
#define ISO_IRTX_TIM_irtx_fd_mask                                                    (0x0000FFFF)
#define ISO_IRTX_TIM_irtx_fd(data)                                                   (0x0000FFFF&((data)<<0))
#define ISO_IRTX_TIM_irtx_fd_src(data)                                               ((0x0000FFFF&(data))>>0)
#define ISO_IRTX_TIM_get_irtx_fd(data)                                               ((0x0000FFFF&(data))>>0)


#define ISO_IRTX_PWM_SETTING                                                         0x18007448
#define ISO_IRTX_PWM_SETTING_reg_addr                                                "0xB8007448"
#define ISO_IRTX_PWM_SETTING_reg                                                     0xB8007448
#define set_ISO_IRTX_PWM_SETTING_reg(data)   (*((volatile unsigned int*) ISO_IRTX_PWM_SETTING_reg)=data)
#define get_ISO_IRTX_PWM_SETTING_reg   (*((volatile unsigned int*) ISO_IRTX_PWM_SETTING_reg))
#define ISO_IRTX_PWM_SETTING_inst_adr                                                "0x0012"
#define ISO_IRTX_PWM_SETTING_inst                                                    0x0012
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_shift                                    (16)
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_mask                                     (0x000F0000)
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div(data)                                    (0x000F0000&((data)<<16))
#define ISO_IRTX_PWM_SETTING_pwm_clksrc_div_src(data)                                ((0x000F0000&(data))>>16)
#define ISO_IRTX_PWM_SETTING_get_pwm_clksrc_div(data)                                ((0x000F0000&(data))>>16)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_shift                                      (8)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_mask                                       (0x0000FF00)
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty(data)                                      (0x0000FF00&((data)<<8))
#define ISO_IRTX_PWM_SETTING_pwm_clk_duty_src(data)                                  ((0x0000FF00&(data))>>8)
#define ISO_IRTX_PWM_SETTING_get_pwm_clk_duty(data)                                  ((0x0000FF00&(data))>>8)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_shift                                       (0)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_mask                                        (0x000000FF)
#define ISO_IRTX_PWM_SETTING_pwm_clk_div(data)                                       (0x000000FF&((data)<<0))
#define ISO_IRTX_PWM_SETTING_pwm_clk_div_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_IRTX_PWM_SETTING_get_pwm_clk_div(data)                                   ((0x000000FF&(data))>>0)


#define ISO_IRTX_INT_EN                                                              0x1800744C
#define ISO_IRTX_INT_EN_reg_addr                                                     "0xB800744C"
#define ISO_IRTX_INT_EN_reg                                                          0xB800744C
#define set_ISO_IRTX_INT_EN_reg(data)   (*((volatile unsigned int*) ISO_IRTX_INT_EN_reg)=data)
#define get_ISO_IRTX_INT_EN_reg   (*((volatile unsigned int*) ISO_IRTX_INT_EN_reg))
#define ISO_IRTX_INT_EN_inst_adr                                                     "0x0013"
#define ISO_IRTX_INT_EN_inst                                                         0x0013
#define ISO_IRTX_INT_EN_data_thr_shift                                               (8)
#define ISO_IRTX_INT_EN_data_thr_mask                                                (0x00003F00)
#define ISO_IRTX_INT_EN_data_thr(data)                                               (0x00003F00&((data)<<8))
#define ISO_IRTX_INT_EN_data_thr_src(data)                                           ((0x00003F00&(data))>>8)
#define ISO_IRTX_INT_EN_get_data_thr(data)                                           ((0x00003F00&(data))>>8)
#define ISO_IRTX_INT_EN_emp_en_shift                                                 (1)
#define ISO_IRTX_INT_EN_emp_en_mask                                                  (0x00000002)
#define ISO_IRTX_INT_EN_emp_en(data)                                                 (0x00000002&((data)<<1))
#define ISO_IRTX_INT_EN_emp_en_src(data)                                             ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_EN_get_emp_en(data)                                             ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_EN_req_en_shift                                                 (0)
#define ISO_IRTX_INT_EN_req_en_mask                                                  (0x00000001)
#define ISO_IRTX_INT_EN_req_en(data)                                                 (0x00000001&((data)<<0))
#define ISO_IRTX_INT_EN_req_en_src(data)                                             ((0x00000001&(data))>>0)
#define ISO_IRTX_INT_EN_get_req_en(data)                                             ((0x00000001&(data))>>0)


#define ISO_IRTX_INT_ST                                                              0x18007450
#define ISO_IRTX_INT_ST_reg_addr                                                     "0xB8007450"
#define ISO_IRTX_INT_ST_reg                                                          0xB8007450
#define set_ISO_IRTX_INT_ST_reg(data)   (*((volatile unsigned int*) ISO_IRTX_INT_ST_reg)=data)
#define get_ISO_IRTX_INT_ST_reg   (*((volatile unsigned int*) ISO_IRTX_INT_ST_reg))
#define ISO_IRTX_INT_ST_inst_adr                                                     "0x0014"
#define ISO_IRTX_INT_ST_inst                                                         0x0014
#define ISO_IRTX_INT_ST_emp_flag_shift                                               (1)
#define ISO_IRTX_INT_ST_emp_flag_mask                                                (0x00000002)
#define ISO_IRTX_INT_ST_emp_flag(data)                                               (0x00000002&((data)<<1))
#define ISO_IRTX_INT_ST_emp_flag_src(data)                                           ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_ST_get_emp_flag(data)                                           ((0x00000002&(data))>>1)
#define ISO_IRTX_INT_ST_req_flag_shift                                               (0)
#define ISO_IRTX_INT_ST_req_flag_mask                                                (0x00000001)
#define ISO_IRTX_INT_ST_req_flag(data)                                               (0x00000001&((data)<<0))
#define ISO_IRTX_INT_ST_req_flag_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_IRTX_INT_ST_get_req_flag(data)                                           ((0x00000001&(data))>>0)


#define ISO_IRTX_FIFO_ST                                                             0x18007454
#define ISO_IRTX_FIFO_ST_reg_addr                                                    "0xB8007454"
#define ISO_IRTX_FIFO_ST_reg                                                         0xB8007454
#define set_ISO_IRTX_FIFO_ST_reg(data)   (*((volatile unsigned int*) ISO_IRTX_FIFO_ST_reg)=data)
#define get_ISO_IRTX_FIFO_ST_reg   (*((volatile unsigned int*) ISO_IRTX_FIFO_ST_reg))
#define ISO_IRTX_FIFO_ST_inst_adr                                                    "0x0015"
#define ISO_IRTX_FIFO_ST_inst                                                        0x0015
#define ISO_IRTX_FIFO_ST_fifo_rst_shift                                              (31)
#define ISO_IRTX_FIFO_ST_fifo_rst_mask                                               (0x80000000)
#define ISO_IRTX_FIFO_ST_fifo_rst(data)                                              (0x80000000&((data)<<31))
#define ISO_IRTX_FIFO_ST_fifo_rst_src(data)                                          ((0x80000000&(data))>>31)
#define ISO_IRTX_FIFO_ST_get_fifo_rst(data)                                          ((0x80000000&(data))>>31)
#define ISO_IRTX_FIFO_ST_valid_len_shift                                             (8)
#define ISO_IRTX_FIFO_ST_valid_len_mask                                              (0x00000F00)
#define ISO_IRTX_FIFO_ST_valid_len(data)                                             (0x00000F00&((data)<<8))
#define ISO_IRTX_FIFO_ST_valid_len_src(data)                                         ((0x00000F00&(data))>>8)
#define ISO_IRTX_FIFO_ST_get_valid_len(data)                                         ((0x00000F00&(data))>>8)
#define ISO_IRTX_FIFO_ST_wrp_shift                                                   (4)
#define ISO_IRTX_FIFO_ST_wrp_mask                                                    (0x000000F0)
#define ISO_IRTX_FIFO_ST_wrp(data)                                                   (0x000000F0&((data)<<4))
#define ISO_IRTX_FIFO_ST_wrp_src(data)                                               ((0x000000F0&(data))>>4)
#define ISO_IRTX_FIFO_ST_get_wrp(data)                                               ((0x000000F0&(data))>>4)
#define ISO_IRTX_FIFO_ST_rdp_shift                                                   (0)
#define ISO_IRTX_FIFO_ST_rdp_mask                                                    (0x0000000F)
#define ISO_IRTX_FIFO_ST_rdp(data)                                                   (0x0000000F&((data)<<0))
#define ISO_IRTX_FIFO_ST_rdp_src(data)                                               ((0x0000000F&(data))>>0)
#define ISO_IRTX_FIFO_ST_get_rdp(data)                                               ((0x0000000F&(data))>>0)


#define ISO_IRTX_FIFO                                                                0x18007458
#define ISO_IRTX_FIFO_reg_addr                                                       "0xB8007458"
#define ISO_IRTX_FIFO_reg                                                            0xB8007458
#define set_ISO_IRTX_FIFO_reg(data)   (*((volatile unsigned int*) ISO_IRTX_FIFO_reg)=data)
#define get_ISO_IRTX_FIFO_reg   (*((volatile unsigned int*) ISO_IRTX_FIFO_reg))
#define ISO_IRTX_FIFO_inst_adr                                                       "0x0016"
#define ISO_IRTX_FIFO_inst                                                           0x0016
#define ISO_IRTX_FIFO_data_shift                                                     (0)
#define ISO_IRTX_FIFO_data_mask                                                      (0xFFFFFFFF)
#define ISO_IRTX_FIFO_data(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_IRTX_FIFO_data_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_IRTX_FIFO_get_data(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_IRRCMM_TIMING                                                            0x18007460
#define ISO_IRRCMM_TIMING_reg_addr                                                   "0xB8007460"
#define ISO_IRRCMM_TIMING_reg                                                        0xB8007460
#define set_ISO_IRRCMM_TIMING_reg(data)   (*((volatile unsigned int*) ISO_IRRCMM_TIMING_reg)=data)
#define get_ISO_IRRCMM_TIMING_reg   (*((volatile unsigned int*) ISO_IRRCMM_TIMING_reg))
#define ISO_IRRCMM_TIMING_inst_adr                                                   "0x0018"
#define ISO_IRRCMM_TIMING_inst                                                       0x0018
#define ISO_IRRCMM_TIMING_len_11_shift                                               (24)
#define ISO_IRRCMM_TIMING_len_11_mask                                                (0xFF000000)
#define ISO_IRRCMM_TIMING_len_11(data)                                               (0xFF000000&((data)<<24))
#define ISO_IRRCMM_TIMING_len_11_src(data)                                           ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_TIMING_get_len_11(data)                                           ((0xFF000000&(data))>>24)
#define ISO_IRRCMM_TIMING_len_10_shift                                               (16)
#define ISO_IRRCMM_TIMING_len_10_mask                                                (0x00FF0000)
#define ISO_IRRCMM_TIMING_len_10(data)                                               (0x00FF0000&((data)<<16))
#define ISO_IRRCMM_TIMING_len_10_src(data)                                           ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_TIMING_get_len_10(data)                                           ((0x00FF0000&(data))>>16)
#define ISO_IRRCMM_TIMING_len_01_shift                                               (8)
#define ISO_IRRCMM_TIMING_len_01_mask                                                (0x0000FF00)
#define ISO_IRRCMM_TIMING_len_01(data)                                               (0x0000FF00&((data)<<8))
#define ISO_IRRCMM_TIMING_len_01_src(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_TIMING_get_len_01(data)                                           ((0x0000FF00&(data))>>8)
#define ISO_IRRCMM_TIMING_len_00_shift                                               (0)
#define ISO_IRRCMM_TIMING_len_00_mask                                                (0x000000FF)
#define ISO_IRRCMM_TIMING_len_00(data)                                               (0x000000FF&((data)<<0))
#define ISO_IRRCMM_TIMING_len_00_src(data)                                           ((0x000000FF&(data))>>0)
#define ISO_IRRCMM_TIMING_get_len_00(data)                                           ((0x000000FF&(data))>>0)


#define ISO_CEC_CR0                                                                  0x18007500
#define ISO_CEC_CR0_reg_addr                                                         "0xB8007500"
#define ISO_CEC_CR0_reg                                                              0xB8007500
#define set_ISO_CEC_CR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_CR0_reg)=data)
#define get_ISO_CEC_CR0_reg   (*((volatile unsigned int*) ISO_CEC_CR0_reg))
#define ISO_CEC_CR0_inst_adr                                                         "0x0040"
#define ISO_CEC_CR0_inst                                                             0x0040
#define ISO_CEC_CR0_cec_mode_shift                                                   (30)
#define ISO_CEC_CR0_cec_mode_mask                                                    (0xC0000000)
#define ISO_CEC_CR0_cec_mode(data)                                                   (0xC0000000&((data)<<30))
#define ISO_CEC_CR0_cec_mode_src(data)                                               ((0xC0000000&(data))>>30)
#define ISO_CEC_CR0_get_cec_mode(data)                                               ((0xC0000000&(data))>>30)
#define ISO_CEC_CR0_test_mode_pad_en_shift                                           (28)
#define ISO_CEC_CR0_test_mode_pad_en_mask                                            (0x10000000)
#define ISO_CEC_CR0_test_mode_pad_en(data)                                           (0x10000000&((data)<<28))
#define ISO_CEC_CR0_test_mode_pad_en_src(data)                                       ((0x10000000&(data))>>28)
#define ISO_CEC_CR0_get_test_mode_pad_en(data)                                       ((0x10000000&(data))>>28)
#define ISO_CEC_CR0_logical_addr0_shift                                              (24)
#define ISO_CEC_CR0_logical_addr0_mask                                               (0x0F000000)
#define ISO_CEC_CR0_logical_addr0(data)                                              (0x0F000000&((data)<<24))
#define ISO_CEC_CR0_logical_addr0_src(data)                                          ((0x0F000000&(data))>>24)
#define ISO_CEC_CR0_get_logical_addr0(data)                                          ((0x0F000000&(data))>>24)
#define ISO_CEC_CR0_timer_div_shift                                                  (16)
#define ISO_CEC_CR0_timer_div_mask                                                   (0x00FF0000)
#define ISO_CEC_CR0_timer_div(data)                                                  (0x00FF0000&((data)<<16))
#define ISO_CEC_CR0_timer_div_src(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_CEC_CR0_get_timer_div(data)                                              ((0x00FF0000&(data))>>16)
#define ISO_CEC_CR0_pre_div_shift                                                    (8)
#define ISO_CEC_CR0_pre_div_mask                                                     (0x0000FF00)
#define ISO_CEC_CR0_pre_div(data)                                                    (0x0000FF00&((data)<<8))
#define ISO_CEC_CR0_pre_div_src(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_CEC_CR0_get_pre_div(data)                                                ((0x0000FF00&(data))>>8)
#define ISO_CEC_CR0_unreg_ack_en_shift                                               (7)
#define ISO_CEC_CR0_unreg_ack_en_mask                                                (0x00000080)
#define ISO_CEC_CR0_unreg_ack_en(data)                                               (0x00000080&((data)<<7))
#define ISO_CEC_CR0_unreg_ack_en_src(data)                                           ((0x00000080&(data))>>7)
#define ISO_CEC_CR0_get_unreg_ack_en(data)                                           ((0x00000080&(data))>>7)
#define ISO_CEC_CR0_cdc_arbitration_en_shift                                         (5)
#define ISO_CEC_CR0_cdc_arbitration_en_mask                                          (0x00000020)
#define ISO_CEC_CR0_cdc_arbitration_en(data)                                         (0x00000020&((data)<<5))
#define ISO_CEC_CR0_cdc_arbitration_en_src(data)                                     ((0x00000020&(data))>>5)
#define ISO_CEC_CR0_get_cdc_arbitration_en(data)                                     ((0x00000020&(data))>>5)
#define ISO_CEC_CR0_test_mode_pad_data_shift                                         (0)
#define ISO_CEC_CR0_test_mode_pad_data_mask                                          (0x0000001F)
#define ISO_CEC_CR0_test_mode_pad_data(data)                                         (0x0000001F&((data)<<0))
#define ISO_CEC_CR0_test_mode_pad_data_src(data)                                     ((0x0000001F&(data))>>0)
#define ISO_CEC_CR0_get_test_mode_pad_data(data)                                     ((0x0000001F&(data))>>0)


#define ISO_CEC_RTCR0                                                                0x18007504
#define ISO_CEC_RTCR0_reg_addr                                                       "0xB8007504"
#define ISO_CEC_RTCR0_reg                                                            0xB8007504
#define set_ISO_CEC_RTCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_RTCR0_reg)=data)
#define get_ISO_CEC_RTCR0_reg   (*((volatile unsigned int*) ISO_CEC_RTCR0_reg))
#define ISO_CEC_RTCR0_inst_adr                                                       "0x0041"
#define ISO_CEC_RTCR0_inst                                                           0x0041
#define ISO_CEC_RTCR0_cec_pad_in_shift                                               (31)
#define ISO_CEC_RTCR0_cec_pad_in_mask                                                (0x80000000)
#define ISO_CEC_RTCR0_cec_pad_in(data)                                               (0x80000000&((data)<<31))
#define ISO_CEC_RTCR0_cec_pad_in_src(data)                                           ((0x80000000&(data))>>31)
#define ISO_CEC_RTCR0_get_cec_pad_in(data)                                           ((0x80000000&(data))>>31)
#define ISO_CEC_RTCR0_dummy0_shift                                                   (28)
#define ISO_CEC_RTCR0_dummy0_mask                                                    (0x70000000)
#define ISO_CEC_RTCR0_dummy0(data)                                                   (0x70000000&((data)<<28))
#define ISO_CEC_RTCR0_dummy0_src(data)                                               ((0x70000000&(data))>>28)
#define ISO_CEC_RTCR0_get_dummy0(data)                                               ((0x70000000&(data))>>28)
#define ISO_CEC_RTCR0_logical_addr3_shift                                            (24)
#define ISO_CEC_RTCR0_logical_addr3_mask                                             (0x0F000000)
#define ISO_CEC_RTCR0_logical_addr3(data)                                            (0x0F000000&((data)<<24))
#define ISO_CEC_RTCR0_logical_addr3_src(data)                                        ((0x0F000000&(data))>>24)
#define ISO_CEC_RTCR0_get_logical_addr3(data)                                        ((0x0F000000&(data))>>24)
#define ISO_CEC_RTCR0_logical_addr2_shift                                            (20)
#define ISO_CEC_RTCR0_logical_addr2_mask                                             (0x00F00000)
#define ISO_CEC_RTCR0_logical_addr2(data)                                            (0x00F00000&((data)<<20))
#define ISO_CEC_RTCR0_logical_addr2_src(data)                                        ((0x00F00000&(data))>>20)
#define ISO_CEC_RTCR0_get_logical_addr2(data)                                        ((0x00F00000&(data))>>20)
#define ISO_CEC_RTCR0_logical_addr1_shift                                            (16)
#define ISO_CEC_RTCR0_logical_addr1_mask                                             (0x000F0000)
#define ISO_CEC_RTCR0_logical_addr1(data)                                            (0x000F0000&((data)<<16))
#define ISO_CEC_RTCR0_logical_addr1_src(data)                                        ((0x000F0000&(data))>>16)
#define ISO_CEC_RTCR0_get_logical_addr1(data)                                        ((0x000F0000&(data))>>16)
#define ISO_CEC_RTCR0_dummy1_shift                                                   (12)
#define ISO_CEC_RTCR0_dummy1_mask                                                    (0x0000F000)
#define ISO_CEC_RTCR0_dummy1(data)                                                   (0x0000F000&((data)<<12))
#define ISO_CEC_RTCR0_dummy1_src(data)                                               ((0x0000F000&(data))>>12)
#define ISO_CEC_RTCR0_get_dummy1(data)                                               ((0x0000F000&(data))>>12)
#define ISO_CEC_RTCR0_clear_cec_int_shift                                            (11)
#define ISO_CEC_RTCR0_clear_cec_int_mask                                             (0x00000800)
#define ISO_CEC_RTCR0_clear_cec_int(data)                                            (0x00000800&((data)<<11))
#define ISO_CEC_RTCR0_clear_cec_int_src(data)                                        ((0x00000800&(data))>>11)
#define ISO_CEC_RTCR0_get_clear_cec_int(data)                                        ((0x00000800&(data))>>11)
#define ISO_CEC_RTCR0_wt_cnt_shift                                                   (5)
#define ISO_CEC_RTCR0_wt_cnt_mask                                                    (0x000007E0)
#define ISO_CEC_RTCR0_wt_cnt(data)                                                   (0x000007E0&((data)<<5))
#define ISO_CEC_RTCR0_wt_cnt_src(data)                                               ((0x000007E0&(data))>>5)
#define ISO_CEC_RTCR0_get_wt_cnt(data)                                               ((0x000007E0&(data))>>5)
#define ISO_CEC_RTCR0_lattest_shift                                                  (4)
#define ISO_CEC_RTCR0_lattest_mask                                                   (0x00000010)
#define ISO_CEC_RTCR0_lattest(data)                                                  (0x00000010&((data)<<4))
#define ISO_CEC_RTCR0_lattest_src(data)                                              ((0x00000010&(data))>>4)
#define ISO_CEC_RTCR0_get_lattest(data)                                              ((0x00000010&(data))>>4)
#define ISO_CEC_RTCR0_retry_no_shift                                                 (0)
#define ISO_CEC_RTCR0_retry_no_mask                                                  (0x0000000F)
#define ISO_CEC_RTCR0_retry_no(data)                                                 (0x0000000F&((data)<<0))
#define ISO_CEC_RTCR0_retry_no_src(data)                                             ((0x0000000F&(data))>>0)
#define ISO_CEC_RTCR0_get_retry_no(data)                                             ((0x0000000F&(data))>>0)


#define ISO_CEC_RXCR0                                                                0x18007508
#define ISO_CEC_RXCR0_reg_addr                                                       "0xB8007508"
#define ISO_CEC_RXCR0_reg                                                            0xB8007508
#define set_ISO_CEC_RXCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXCR0_reg)=data)
#define get_ISO_CEC_RXCR0_reg   (*((volatile unsigned int*) ISO_CEC_RXCR0_reg))
#define ISO_CEC_RXCR0_inst_adr                                                       "0x0042"
#define ISO_CEC_RXCR0_inst                                                           0x0042
#define ISO_CEC_RXCR0_broadcast_addr_shift                                           (31)
#define ISO_CEC_RXCR0_broadcast_addr_mask                                            (0x80000000)
#define ISO_CEC_RXCR0_broadcast_addr(data)                                           (0x80000000&((data)<<31))
#define ISO_CEC_RXCR0_broadcast_addr_src(data)                                       ((0x80000000&(data))>>31)
#define ISO_CEC_RXCR0_get_broadcast_addr(data)                                       ((0x80000000&(data))>>31)
#define ISO_CEC_RXCR0_dest_addr_shift                                                (16)
#define ISO_CEC_RXCR0_dest_addr_mask                                                 (0x000F0000)
#define ISO_CEC_RXCR0_dest_addr(data)                                                (0x000F0000&((data)<<16))
#define ISO_CEC_RXCR0_dest_addr_src(data)                                            ((0x000F0000&(data))>>16)
#define ISO_CEC_RXCR0_get_dest_addr(data)                                            ((0x000F0000&(data))>>16)
#define ISO_CEC_RXCR0_rx_en_shift                                                    (15)
#define ISO_CEC_RXCR0_rx_en_mask                                                     (0x00008000)
#define ISO_CEC_RXCR0_rx_en(data)                                                    (0x00008000&((data)<<15))
#define ISO_CEC_RXCR0_rx_en_src(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_RXCR0_get_rx_en(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_RXCR0_rx_rst_shift                                                   (14)
#define ISO_CEC_RXCR0_rx_rst_mask                                                    (0x00004000)
#define ISO_CEC_RXCR0_rx_rst(data)                                                   (0x00004000&((data)<<14))
#define ISO_CEC_RXCR0_rx_rst_src(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_RXCR0_get_rx_rst(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_RXCR0_rx_continuous_shift                                            (13)
#define ISO_CEC_RXCR0_rx_continuous_mask                                             (0x00002000)
#define ISO_CEC_RXCR0_rx_continuous(data)                                            (0x00002000&((data)<<13))
#define ISO_CEC_RXCR0_rx_continuous_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_RXCR0_get_rx_continuous(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_RXCR0_rx_int_en_shift                                                (12)
#define ISO_CEC_RXCR0_rx_int_en_mask                                                 (0x00001000)
#define ISO_CEC_RXCR0_rx_int_en(data)                                                (0x00001000&((data)<<12))
#define ISO_CEC_RXCR0_rx_int_en_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_RXCR0_get_rx_int_en(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_RXCR0_init_addr_shift                                                (8)
#define ISO_CEC_RXCR0_init_addr_mask                                                 (0x00000F00)
#define ISO_CEC_RXCR0_init_addr(data)                                                (0x00000F00&((data)<<8))
#define ISO_CEC_RXCR0_init_addr_src(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_RXCR0_get_init_addr(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_RXCR0_rx_eom_shift                                                   (7)
#define ISO_CEC_RXCR0_rx_eom_mask                                                    (0x00000080)
#define ISO_CEC_RXCR0_rx_eom(data)                                                   (0x00000080&((data)<<7))
#define ISO_CEC_RXCR0_rx_eom_src(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_RXCR0_get_rx_eom(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_RXCR0_rx_int_shift                                                   (6)
#define ISO_CEC_RXCR0_rx_int_mask                                                    (0x00000040)
#define ISO_CEC_RXCR0_rx_int(data)                                                   (0x00000040&((data)<<6))
#define ISO_CEC_RXCR0_rx_int_src(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_RXCR0_get_rx_int(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_RXCR0_rx_fifo_ov_shift                                               (5)
#define ISO_CEC_RXCR0_rx_fifo_ov_mask                                                (0x00000020)
#define ISO_CEC_RXCR0_rx_fifo_ov(data)                                               (0x00000020&((data)<<5))
#define ISO_CEC_RXCR0_rx_fifo_ov_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_RXCR0_get_rx_fifo_ov(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_RXCR0_rx_fifo_cnt_shift                                              (0)
#define ISO_CEC_RXCR0_rx_fifo_cnt_mask                                               (0x0000001F)
#define ISO_CEC_RXCR0_rx_fifo_cnt(data)                                              (0x0000001F&((data)<<0))
#define ISO_CEC_RXCR0_rx_fifo_cnt_src(data)                                          ((0x0000001F&(data))>>0)
#define ISO_CEC_RXCR0_get_rx_fifo_cnt(data)                                          ((0x0000001F&(data))>>0)


#define ISO_CEC_TXCR0                                                                0x1800750C
#define ISO_CEC_TXCR0_reg_addr                                                       "0xB800750C"
#define ISO_CEC_TXCR0_reg                                                            0xB800750C
#define set_ISO_CEC_TXCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXCR0_reg)=data)
#define get_ISO_CEC_TXCR0_reg   (*((volatile unsigned int*) ISO_CEC_TXCR0_reg))
#define ISO_CEC_TXCR0_inst_adr                                                       "0x0043"
#define ISO_CEC_TXCR0_inst                                                           0x0043
#define ISO_CEC_TXCR0_tx_addr_en_shift                                               (20)
#define ISO_CEC_TXCR0_tx_addr_en_mask                                                (0x00100000)
#define ISO_CEC_TXCR0_tx_addr_en(data)                                               (0x00100000&((data)<<20))
#define ISO_CEC_TXCR0_tx_addr_en_src(data)                                           ((0x00100000&(data))>>20)
#define ISO_CEC_TXCR0_get_tx_addr_en(data)                                           ((0x00100000&(data))>>20)
#define ISO_CEC_TXCR0_tx_addr_shift                                                  (16)
#define ISO_CEC_TXCR0_tx_addr_mask                                                   (0x000F0000)
#define ISO_CEC_TXCR0_tx_addr(data)                                                  (0x000F0000&((data)<<16))
#define ISO_CEC_TXCR0_tx_addr_src(data)                                              ((0x000F0000&(data))>>16)
#define ISO_CEC_TXCR0_get_tx_addr(data)                                              ((0x000F0000&(data))>>16)
#define ISO_CEC_TXCR0_tx_en_shift                                                    (15)
#define ISO_CEC_TXCR0_tx_en_mask                                                     (0x00008000)
#define ISO_CEC_TXCR0_tx_en(data)                                                    (0x00008000&((data)<<15))
#define ISO_CEC_TXCR0_tx_en_src(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_TXCR0_get_tx_en(data)                                                ((0x00008000&(data))>>15)
#define ISO_CEC_TXCR0_tx_rst_shift                                                   (14)
#define ISO_CEC_TXCR0_tx_rst_mask                                                    (0x00004000)
#define ISO_CEC_TXCR0_tx_rst(data)                                                   (0x00004000&((data)<<14))
#define ISO_CEC_TXCR0_tx_rst_src(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_TXCR0_get_tx_rst(data)                                               ((0x00004000&(data))>>14)
#define ISO_CEC_TXCR0_tx_continuous_shift                                            (13)
#define ISO_CEC_TXCR0_tx_continuous_mask                                             (0x00002000)
#define ISO_CEC_TXCR0_tx_continuous(data)                                            (0x00002000&((data)<<13))
#define ISO_CEC_TXCR0_tx_continuous_src(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_TXCR0_get_tx_continuous(data)                                        ((0x00002000&(data))>>13)
#define ISO_CEC_TXCR0_tx_int_en_shift                                                (12)
#define ISO_CEC_TXCR0_tx_int_en_mask                                                 (0x00001000)
#define ISO_CEC_TXCR0_tx_int_en(data)                                                (0x00001000&((data)<<12))
#define ISO_CEC_TXCR0_tx_int_en_src(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_TXCR0_get_tx_int_en(data)                                            ((0x00001000&(data))>>12)
#define ISO_CEC_TXCR0_dest_addr_shift                                                (8)
#define ISO_CEC_TXCR0_dest_addr_mask                                                 (0x00000F00)
#define ISO_CEC_TXCR0_dest_addr(data)                                                (0x00000F00&((data)<<8))
#define ISO_CEC_TXCR0_dest_addr_src(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_TXCR0_get_dest_addr(data)                                            ((0x00000F00&(data))>>8)
#define ISO_CEC_TXCR0_tx_eom_shift                                                   (7)
#define ISO_CEC_TXCR0_tx_eom_mask                                                    (0x00000080)
#define ISO_CEC_TXCR0_tx_eom(data)                                                   (0x00000080&((data)<<7))
#define ISO_CEC_TXCR0_tx_eom_src(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_TXCR0_get_tx_eom(data)                                               ((0x00000080&(data))>>7)
#define ISO_CEC_TXCR0_tx_int_shift                                                   (6)
#define ISO_CEC_TXCR0_tx_int_mask                                                    (0x00000040)
#define ISO_CEC_TXCR0_tx_int(data)                                                   (0x00000040&((data)<<6))
#define ISO_CEC_TXCR0_tx_int_src(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_TXCR0_get_tx_int(data)                                               ((0x00000040&(data))>>6)
#define ISO_CEC_TXCR0_tx_fifo_ud_shift                                               (5)
#define ISO_CEC_TXCR0_tx_fifo_ud_mask                                                (0x00000020)
#define ISO_CEC_TXCR0_tx_fifo_ud(data)                                               (0x00000020&((data)<<5))
#define ISO_CEC_TXCR0_tx_fifo_ud_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXCR0_get_tx_fifo_ud(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXCR0_tx_fifo_cnt_shift                                              (0)
#define ISO_CEC_TXCR0_tx_fifo_cnt_mask                                               (0x0000001F)
#define ISO_CEC_TXCR0_tx_fifo_cnt(data)                                              (0x0000001F&((data)<<0))
#define ISO_CEC_TXCR0_tx_fifo_cnt_src(data)                                          ((0x0000001F&(data))>>0)
#define ISO_CEC_TXCR0_get_tx_fifo_cnt(data)                                          ((0x0000001F&(data))>>0)


#define ISO_CEC_TXDR0                                                                0x18007510
#define ISO_CEC_TXDR0_reg_addr                                                       "0xB8007510"
#define ISO_CEC_TXDR0_reg                                                            0xB8007510
#define set_ISO_CEC_TXDR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR0_reg)=data)
#define get_ISO_CEC_TXDR0_reg   (*((volatile unsigned int*) ISO_CEC_TXDR0_reg))
#define ISO_CEC_TXDR0_inst_adr                                                       "0x0044"
#define ISO_CEC_TXDR0_inst                                                           0x0044
#define ISO_CEC_TXDR0_tx_add_cnt_shift                                               (6)
#define ISO_CEC_TXDR0_tx_add_cnt_mask                                                (0x00000040)
#define ISO_CEC_TXDR0_tx_add_cnt(data)                                               (0x00000040&((data)<<6))
#define ISO_CEC_TXDR0_tx_add_cnt_src(data)                                           ((0x00000040&(data))>>6)
#define ISO_CEC_TXDR0_get_tx_add_cnt(data)                                           ((0x00000040&(data))>>6)
#define ISO_CEC_TXDR0_rx_sub_cnt_shift                                               (5)
#define ISO_CEC_TXDR0_rx_sub_cnt_mask                                                (0x00000020)
#define ISO_CEC_TXDR0_rx_sub_cnt(data)                                               (0x00000020&((data)<<5))
#define ISO_CEC_TXDR0_rx_sub_cnt_src(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXDR0_get_rx_sub_cnt(data)                                           ((0x00000020&(data))>>5)
#define ISO_CEC_TXDR0_fifo_cnt_shift                                                 (0)
#define ISO_CEC_TXDR0_fifo_cnt_mask                                                  (0x0000001F)
#define ISO_CEC_TXDR0_fifo_cnt(data)                                                 (0x0000001F&((data)<<0))
#define ISO_CEC_TXDR0_fifo_cnt_src(data)                                             ((0x0000001F&(data))>>0)
#define ISO_CEC_TXDR0_get_fifo_cnt(data)                                             ((0x0000001F&(data))>>0)


#define ISO_CEC_TXDR1                                                                0x18007514
#define ISO_CEC_TXDR1_reg_addr                                                       "0xB8007514"
#define ISO_CEC_TXDR1_reg                                                            0xB8007514
#define set_ISO_CEC_TXDR1_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR1_reg)=data)
#define get_ISO_CEC_TXDR1_reg   (*((volatile unsigned int*) ISO_CEC_TXDR1_reg))
#define ISO_CEC_TXDR1_inst_adr                                                       "0x0045"
#define ISO_CEC_TXDR1_inst                                                           0x0045
#define ISO_CEC_TXDR1_tx_fifo_0_shift                                                (24)
#define ISO_CEC_TXDR1_tx_fifo_0_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR1_tx_fifo_0(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR1_tx_fifo_0_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR1_get_tx_fifo_0(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR1_tx_fifo_1_shift                                                (16)
#define ISO_CEC_TXDR1_tx_fifo_1_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR1_tx_fifo_1(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR1_tx_fifo_1_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR1_get_tx_fifo_1(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR1_tx_fifo_2_shift                                                (8)
#define ISO_CEC_TXDR1_tx_fifo_2_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR1_tx_fifo_2(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR1_tx_fifo_2_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR1_get_tx_fifo_2(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR1_tx_fifo_3_shift                                                (0)
#define ISO_CEC_TXDR1_tx_fifo_3_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR1_tx_fifo_3(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR1_tx_fifo_3_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR1_get_tx_fifo_3(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_TXDR2                                                                0x18007518
#define ISO_CEC_TXDR2_reg_addr                                                       "0xB8007518"
#define ISO_CEC_TXDR2_reg                                                            0xB8007518
#define set_ISO_CEC_TXDR2_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR2_reg)=data)
#define get_ISO_CEC_TXDR2_reg   (*((volatile unsigned int*) ISO_CEC_TXDR2_reg))
#define ISO_CEC_TXDR2_inst_adr                                                       "0x0046"
#define ISO_CEC_TXDR2_inst                                                           0x0046
#define ISO_CEC_TXDR2_tx_fifo_4_shift                                                (24)
#define ISO_CEC_TXDR2_tx_fifo_4_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR2_tx_fifo_4(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR2_tx_fifo_4_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR2_get_tx_fifo_4(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR2_tx_fifo_5_shift                                                (16)
#define ISO_CEC_TXDR2_tx_fifo_5_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR2_tx_fifo_5(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR2_tx_fifo_5_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR2_get_tx_fifo_5(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR2_tx_fifo_6_shift                                                (8)
#define ISO_CEC_TXDR2_tx_fifo_6_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR2_tx_fifo_6(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR2_tx_fifo_6_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR2_get_tx_fifo_6(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR2_tx_fifo_7_shift                                                (0)
#define ISO_CEC_TXDR2_tx_fifo_7_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR2_tx_fifo_7(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR2_tx_fifo_7_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR2_get_tx_fifo_7(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_TXDR3                                                                0x1800751C
#define ISO_CEC_TXDR3_reg_addr                                                       "0xB800751C"
#define ISO_CEC_TXDR3_reg                                                            0xB800751C
#define set_ISO_CEC_TXDR3_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR3_reg)=data)
#define get_ISO_CEC_TXDR3_reg   (*((volatile unsigned int*) ISO_CEC_TXDR3_reg))
#define ISO_CEC_TXDR3_inst_adr                                                       "0x0047"
#define ISO_CEC_TXDR3_inst                                                           0x0047
#define ISO_CEC_TXDR3_tx_fifo_8_shift                                                (24)
#define ISO_CEC_TXDR3_tx_fifo_8_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR3_tx_fifo_8(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR3_tx_fifo_8_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR3_get_tx_fifo_8(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR3_tx_fifo_9_shift                                                (16)
#define ISO_CEC_TXDR3_tx_fifo_9_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR3_tx_fifo_9(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR3_tx_fifo_9_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR3_get_tx_fifo_9(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR3_tx_fifo_a_shift                                                (8)
#define ISO_CEC_TXDR3_tx_fifo_a_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR3_tx_fifo_a(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR3_tx_fifo_a_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR3_get_tx_fifo_a(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR3_tx_fifo_b_shift                                                (0)
#define ISO_CEC_TXDR3_tx_fifo_b_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR3_tx_fifo_b(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR3_tx_fifo_b_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR3_get_tx_fifo_b(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_TXDR4                                                                0x18007520
#define ISO_CEC_TXDR4_reg_addr                                                       "0xB8007520"
#define ISO_CEC_TXDR4_reg                                                            0xB8007520
#define set_ISO_CEC_TXDR4_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXDR4_reg)=data)
#define get_ISO_CEC_TXDR4_reg   (*((volatile unsigned int*) ISO_CEC_TXDR4_reg))
#define ISO_CEC_TXDR4_inst_adr                                                       "0x0048"
#define ISO_CEC_TXDR4_inst                                                           0x0048
#define ISO_CEC_TXDR4_tx_fifo_c_shift                                                (24)
#define ISO_CEC_TXDR4_tx_fifo_c_mask                                                 (0xFF000000)
#define ISO_CEC_TXDR4_tx_fifo_c(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_TXDR4_tx_fifo_c_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR4_get_tx_fifo_c(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_TXDR4_tx_fifo_d_shift                                                (16)
#define ISO_CEC_TXDR4_tx_fifo_d_mask                                                 (0x00FF0000)
#define ISO_CEC_TXDR4_tx_fifo_d(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_TXDR4_tx_fifo_d_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR4_get_tx_fifo_d(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXDR4_tx_fifo_e_shift                                                (8)
#define ISO_CEC_TXDR4_tx_fifo_e_mask                                                 (0x0000FF00)
#define ISO_CEC_TXDR4_tx_fifo_e(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_TXDR4_tx_fifo_e_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR4_get_tx_fifo_e(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXDR4_tx_fifo_f_shift                                                (0)
#define ISO_CEC_TXDR4_tx_fifo_f_mask                                                 (0x000000FF)
#define ISO_CEC_TXDR4_tx_fifo_f(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_TXDR4_tx_fifo_f_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_TXDR4_get_tx_fifo_f(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR1                                                                0x18007524
#define ISO_CEC_RXDR1_reg_addr                                                       "0xB8007524"
#define ISO_CEC_RXDR1_reg                                                            0xB8007524
#define set_ISO_CEC_RXDR1_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR1_reg)=data)
#define get_ISO_CEC_RXDR1_reg   (*((volatile unsigned int*) ISO_CEC_RXDR1_reg))
#define ISO_CEC_RXDR1_inst_adr                                                       "0x0049"
#define ISO_CEC_RXDR1_inst                                                           0x0049
#define ISO_CEC_RXDR1_rx_fifo_0_shift                                                (24)
#define ISO_CEC_RXDR1_rx_fifo_0_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR1_rx_fifo_0(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR1_rx_fifo_0_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR1_get_rx_fifo_0(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR1_rx_fifo_1_shift                                                (16)
#define ISO_CEC_RXDR1_rx_fifo_1_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR1_rx_fifo_1(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR1_rx_fifo_1_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR1_get_rx_fifo_1(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR1_rx_fifo_2_shift                                                (8)
#define ISO_CEC_RXDR1_rx_fifo_2_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR1_rx_fifo_2(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR1_rx_fifo_2_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR1_get_rx_fifo_2(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR1_rx_fifo_3_shift                                                (0)
#define ISO_CEC_RXDR1_rx_fifo_3_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR1_rx_fifo_3(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR1_rx_fifo_3_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR1_get_rx_fifo_3(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR2                                                                0x18007528
#define ISO_CEC_RXDR2_reg_addr                                                       "0xB8007528"
#define ISO_CEC_RXDR2_reg                                                            0xB8007528
#define set_ISO_CEC_RXDR2_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR2_reg)=data)
#define get_ISO_CEC_RXDR2_reg   (*((volatile unsigned int*) ISO_CEC_RXDR2_reg))
#define ISO_CEC_RXDR2_inst_adr                                                       "0x004A"
#define ISO_CEC_RXDR2_inst                                                           0x004A
#define ISO_CEC_RXDR2_rx_fifo_4_shift                                                (24)
#define ISO_CEC_RXDR2_rx_fifo_4_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR2_rx_fifo_4(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR2_rx_fifo_4_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR2_get_rx_fifo_4(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR2_rx_fifo_5_shift                                                (16)
#define ISO_CEC_RXDR2_rx_fifo_5_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR2_rx_fifo_5(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR2_rx_fifo_5_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR2_get_rx_fifo_5(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR2_rx_fifo_6_shift                                                (8)
#define ISO_CEC_RXDR2_rx_fifo_6_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR2_rx_fifo_6(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR2_rx_fifo_6_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR2_get_rx_fifo_6(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR2_rx_fifo_7_shift                                                (0)
#define ISO_CEC_RXDR2_rx_fifo_7_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR2_rx_fifo_7(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR2_rx_fifo_7_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR2_get_rx_fifo_7(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR3                                                                0x1800752C
#define ISO_CEC_RXDR3_reg_addr                                                       "0xB800752C"
#define ISO_CEC_RXDR3_reg                                                            0xB800752C
#define set_ISO_CEC_RXDR3_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR3_reg)=data)
#define get_ISO_CEC_RXDR3_reg   (*((volatile unsigned int*) ISO_CEC_RXDR3_reg))
#define ISO_CEC_RXDR3_inst_adr                                                       "0x004B"
#define ISO_CEC_RXDR3_inst                                                           0x004B
#define ISO_CEC_RXDR3_rx_fifo_8_shift                                                (24)
#define ISO_CEC_RXDR3_rx_fifo_8_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR3_rx_fifo_8(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR3_rx_fifo_8_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR3_get_rx_fifo_8(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR3_rx_fifo_9_shift                                                (16)
#define ISO_CEC_RXDR3_rx_fifo_9_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR3_rx_fifo_9(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR3_rx_fifo_9_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR3_get_rx_fifo_9(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR3_rx_fifo_a_shift                                                (8)
#define ISO_CEC_RXDR3_rx_fifo_a_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR3_rx_fifo_a(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR3_rx_fifo_a_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR3_get_rx_fifo_a(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR3_rx_fifo_b_shift                                                (0)
#define ISO_CEC_RXDR3_rx_fifo_b_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR3_rx_fifo_b(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR3_rx_fifo_b_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR3_get_rx_fifo_b(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXDR4                                                                0x18007530
#define ISO_CEC_RXDR4_reg_addr                                                       "0xB8007530"
#define ISO_CEC_RXDR4_reg                                                            0xB8007530
#define set_ISO_CEC_RXDR4_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXDR4_reg)=data)
#define get_ISO_CEC_RXDR4_reg   (*((volatile unsigned int*) ISO_CEC_RXDR4_reg))
#define ISO_CEC_RXDR4_inst_adr                                                       "0x004C"
#define ISO_CEC_RXDR4_inst                                                           0x004C
#define ISO_CEC_RXDR4_rx_fifo_c_shift                                                (24)
#define ISO_CEC_RXDR4_rx_fifo_c_mask                                                 (0xFF000000)
#define ISO_CEC_RXDR4_rx_fifo_c(data)                                                (0xFF000000&((data)<<24))
#define ISO_CEC_RXDR4_rx_fifo_c_src(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR4_get_rx_fifo_c(data)                                            ((0xFF000000&(data))>>24)
#define ISO_CEC_RXDR4_rx_fifo_d_shift                                                (16)
#define ISO_CEC_RXDR4_rx_fifo_d_mask                                                 (0x00FF0000)
#define ISO_CEC_RXDR4_rx_fifo_d(data)                                                (0x00FF0000&((data)<<16))
#define ISO_CEC_RXDR4_rx_fifo_d_src(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR4_get_rx_fifo_d(data)                                            ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXDR4_rx_fifo_e_shift                                                (8)
#define ISO_CEC_RXDR4_rx_fifo_e_mask                                                 (0x0000FF00)
#define ISO_CEC_RXDR4_rx_fifo_e(data)                                                (0x0000FF00&((data)<<8))
#define ISO_CEC_RXDR4_rx_fifo_e_src(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR4_get_rx_fifo_e(data)                                            ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXDR4_rx_fifo_f_shift                                                (0)
#define ISO_CEC_RXDR4_rx_fifo_f_mask                                                 (0x000000FF)
#define ISO_CEC_RXDR4_rx_fifo_f(data)                                                (0x000000FF&((data)<<0))
#define ISO_CEC_RXDR4_rx_fifo_f_src(data)                                            ((0x000000FF&(data))>>0)
#define ISO_CEC_RXDR4_get_rx_fifo_f(data)                                            ((0x000000FF&(data))>>0)


#define ISO_CEC_RXTCR0                                                               0x18007534
#define ISO_CEC_RXTCR0_reg_addr                                                      "0xB8007534"
#define ISO_CEC_RXTCR0_reg                                                           0xB8007534
#define set_ISO_CEC_RXTCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_RXTCR0_reg)=data)
#define get_ISO_CEC_RXTCR0_reg   (*((volatile unsigned int*) ISO_CEC_RXTCR0_reg))
#define ISO_CEC_RXTCR0_inst_adr                                                      "0x004D"
#define ISO_CEC_RXTCR0_inst                                                          0x004D
#define ISO_CEC_RXTCR0_rx_start_low_shift                                            (24)
#define ISO_CEC_RXTCR0_rx_start_low_mask                                             (0xFF000000)
#define ISO_CEC_RXTCR0_rx_start_low(data)                                            (0xFF000000&((data)<<24))
#define ISO_CEC_RXTCR0_rx_start_low_src(data)                                        ((0xFF000000&(data))>>24)
#define ISO_CEC_RXTCR0_get_rx_start_low(data)                                        ((0xFF000000&(data))>>24)
#define ISO_CEC_RXTCR0_rx_start_period_shift                                         (16)
#define ISO_CEC_RXTCR0_rx_start_period_mask                                          (0x00FF0000)
#define ISO_CEC_RXTCR0_rx_start_period(data)                                         (0x00FF0000&((data)<<16))
#define ISO_CEC_RXTCR0_rx_start_period_src(data)                                     ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXTCR0_get_rx_start_period(data)                                     ((0x00FF0000&(data))>>16)
#define ISO_CEC_RXTCR0_rx_data_sample_shift                                          (8)
#define ISO_CEC_RXTCR0_rx_data_sample_mask                                           (0x0000FF00)
#define ISO_CEC_RXTCR0_rx_data_sample(data)                                          (0x0000FF00&((data)<<8))
#define ISO_CEC_RXTCR0_rx_data_sample_src(data)                                      ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXTCR0_get_rx_data_sample(data)                                      ((0x0000FF00&(data))>>8)
#define ISO_CEC_RXTCR0_rx_data_period_shift                                          (0)
#define ISO_CEC_RXTCR0_rx_data_period_mask                                           (0x000000FF)
#define ISO_CEC_RXTCR0_rx_data_period(data)                                          (0x000000FF&((data)<<0))
#define ISO_CEC_RXTCR0_rx_data_period_src(data)                                      ((0x000000FF&(data))>>0)
#define ISO_CEC_RXTCR0_get_rx_data_period(data)                                      ((0x000000FF&(data))>>0)


#define ISO_CEC_TXTCR0                                                               0x18007538
#define ISO_CEC_TXTCR0_reg_addr                                                      "0xB8007538"
#define ISO_CEC_TXTCR0_reg                                                           0xB8007538
#define set_ISO_CEC_TXTCR0_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXTCR0_reg)=data)
#define get_ISO_CEC_TXTCR0_reg   (*((volatile unsigned int*) ISO_CEC_TXTCR0_reg))
#define ISO_CEC_TXTCR0_inst_adr                                                      "0x004E"
#define ISO_CEC_TXTCR0_inst                                                          0x004E
#define ISO_CEC_TXTCR0_tx_start_low_shift                                            (8)
#define ISO_CEC_TXTCR0_tx_start_low_mask                                             (0x0000FF00)
#define ISO_CEC_TXTCR0_tx_start_low(data)                                            (0x0000FF00&((data)<<8))
#define ISO_CEC_TXTCR0_tx_start_low_src(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR0_get_tx_start_low(data)                                        ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR0_tx_start_high_shift                                           (0)
#define ISO_CEC_TXTCR0_tx_start_high_mask                                            (0x000000FF)
#define ISO_CEC_TXTCR0_tx_start_high(data)                                           (0x000000FF&((data)<<0))
#define ISO_CEC_TXTCR0_tx_start_high_src(data)                                       ((0x000000FF&(data))>>0)
#define ISO_CEC_TXTCR0_get_tx_start_high(data)                                       ((0x000000FF&(data))>>0)


#define ISO_CEC_TXTCR1                                                               0x1800753C
#define ISO_CEC_TXTCR1_reg_addr                                                      "0xB800753C"
#define ISO_CEC_TXTCR1_reg                                                           0xB800753C
#define set_ISO_CEC_TXTCR1_reg(data)   (*((volatile unsigned int*) ISO_CEC_TXTCR1_reg)=data)
#define get_ISO_CEC_TXTCR1_reg   (*((volatile unsigned int*) ISO_CEC_TXTCR1_reg))
#define ISO_CEC_TXTCR1_inst_adr                                                      "0x004F"
#define ISO_CEC_TXTCR1_inst                                                          0x004F
#define ISO_CEC_TXTCR1_tx_data_low_shift                                             (16)
#define ISO_CEC_TXTCR1_tx_data_low_mask                                              (0x00FF0000)
#define ISO_CEC_TXTCR1_tx_data_low(data)                                             (0x00FF0000&((data)<<16))
#define ISO_CEC_TXTCR1_tx_data_low_src(data)                                         ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXTCR1_get_tx_data_low(data)                                         ((0x00FF0000&(data))>>16)
#define ISO_CEC_TXTCR1_tx_data_01_shift                                              (8)
#define ISO_CEC_TXTCR1_tx_data_01_mask                                               (0x0000FF00)
#define ISO_CEC_TXTCR1_tx_data_01(data)                                              (0x0000FF00&((data)<<8))
#define ISO_CEC_TXTCR1_tx_data_01_src(data)                                          ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR1_get_tx_data_01(data)                                          ((0x0000FF00&(data))>>8)
#define ISO_CEC_TXTCR1_tx_data_high_shift                                            (0)
#define ISO_CEC_TXTCR1_tx_data_high_mask                                             (0x000000FF)
#define ISO_CEC_TXTCR1_tx_data_high(data)                                            (0x000000FF&((data)<<0))
#define ISO_CEC_TXTCR1_tx_data_high_src(data)                                        ((0x000000FF&(data))>>0)
#define ISO_CEC_TXTCR1_get_tx_data_high(data)                                        ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_01                                                0x18007540
#define ISO_GDI_CEC_COMPARE_OPCODE_01_reg_addr                                       "0xB8007540"
#define ISO_GDI_CEC_COMPARE_OPCODE_01_reg                                            0xB8007540
#define set_ISO_GDI_CEC_COMPARE_OPCODE_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_01_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_01_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_01_inst_adr                                       "0x0050"
#define ISO_GDI_CEC_COMPARE_OPCODE_01_inst                                           0x0050
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_01_compare_opcode_01_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_01_get_compare_opcode_01(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_01                                                   0x18007544
#define ISO_GDI_CEC_SEND_OPCODE_01_reg_addr                                          "0xB8007544"
#define ISO_GDI_CEC_SEND_OPCODE_01_reg                                               0xB8007544
#define set_ISO_GDI_CEC_SEND_OPCODE_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_01_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_01_reg))
#define ISO_GDI_CEC_SEND_OPCODE_01_inst_adr                                          "0x0051"
#define ISO_GDI_CEC_SEND_OPCODE_01_inst                                              0x0051
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_01_send_opcode_01_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_01_get_send_opcode_01(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01                                            0x18007548
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg_addr                                   "0xB8007548"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg                                        0xB8007548
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_inst_adr                                   "0x0052"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_inst                                       0x0052
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_operand_number_01_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_01_get_operand_number_01(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_01                                                        0x1800754C
#define ISO_GDI_CEC_OPRAND_01_reg_addr                                               "0xB800754C"
#define ISO_GDI_CEC_OPRAND_01_reg                                                    0xB800754C
#define set_ISO_GDI_CEC_OPRAND_01_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_01_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_01_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_01_reg))
#define ISO_GDI_CEC_OPRAND_01_inst_adr                                               "0x0053"
#define ISO_GDI_CEC_OPRAND_01_inst                                                   0x0053
#define ISO_GDI_CEC_OPRAND_01_operand_01_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_01_operand_01_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_01_operand_01(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_01_operand_01_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_01_get_operand_01(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_02                                                        0x18007550
#define ISO_GDI_CEC_OPRAND_02_reg_addr                                               "0xB8007550"
#define ISO_GDI_CEC_OPRAND_02_reg                                                    0xB8007550
#define set_ISO_GDI_CEC_OPRAND_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_02_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_02_reg))
#define ISO_GDI_CEC_OPRAND_02_inst_adr                                               "0x0054"
#define ISO_GDI_CEC_OPRAND_02_inst                                                   0x0054
#define ISO_GDI_CEC_OPRAND_02_operand_02_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_02_operand_02_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_02_operand_02(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_02_operand_02_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_02_get_operand_02(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_03                                                        0x18007554
#define ISO_GDI_CEC_OPRAND_03_reg_addr                                               "0xB8007554"
#define ISO_GDI_CEC_OPRAND_03_reg                                                    0xB8007554
#define set_ISO_GDI_CEC_OPRAND_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_03_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_03_reg))
#define ISO_GDI_CEC_OPRAND_03_inst_adr                                               "0x0055"
#define ISO_GDI_CEC_OPRAND_03_inst                                                   0x0055
#define ISO_GDI_CEC_OPRAND_03_operand_03_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_03_operand_03_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_03_operand_03(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_03_operand_03_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_03_get_operand_03(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_02                                                0x18007558
#define ISO_GDI_CEC_COMPARE_OPCODE_02_reg_addr                                       "0xB8007558"
#define ISO_GDI_CEC_COMPARE_OPCODE_02_reg                                            0xB8007558
#define set_ISO_GDI_CEC_COMPARE_OPCODE_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_02_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_02_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_02_inst_adr                                       "0x0056"
#define ISO_GDI_CEC_COMPARE_OPCODE_02_inst                                           0x0056
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_02_compare_opcode_02_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_02_get_compare_opcode_02(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_02                                                   0x1800755C
#define ISO_GDI_CEC_SEND_OPCODE_02_reg_addr                                          "0xB800755C"
#define ISO_GDI_CEC_SEND_OPCODE_02_reg                                               0xB800755C
#define set_ISO_GDI_CEC_SEND_OPCODE_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_02_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_02_reg))
#define ISO_GDI_CEC_SEND_OPCODE_02_inst_adr                                          "0x0057"
#define ISO_GDI_CEC_SEND_OPCODE_02_inst                                              0x0057
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_02_send_opcode_02_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_02_get_send_opcode_02(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02                                            0x18007560
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg_addr                                   "0xB8007560"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg                                        0xB8007560
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_inst_adr                                   "0x0058"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_inst                                       0x0058
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_operand_number_02_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_02_get_operand_number_02(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_04                                                        0x18007564
#define ISO_GDI_CEC_OPRAND_04_reg_addr                                               "0xB8007564"
#define ISO_GDI_CEC_OPRAND_04_reg                                                    0xB8007564
#define set_ISO_GDI_CEC_OPRAND_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_04_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_04_reg))
#define ISO_GDI_CEC_OPRAND_04_inst_adr                                               "0x0059"
#define ISO_GDI_CEC_OPRAND_04_inst                                                   0x0059
#define ISO_GDI_CEC_OPRAND_04_operand_04_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_04_operand_04_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_04_operand_04(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_04_operand_04_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_04_get_operand_04(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_05                                                        0x18007568
#define ISO_GDI_CEC_OPRAND_05_reg_addr                                               "0xB8007568"
#define ISO_GDI_CEC_OPRAND_05_reg                                                    0xB8007568
#define set_ISO_GDI_CEC_OPRAND_05_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_05_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_05_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_05_reg))
#define ISO_GDI_CEC_OPRAND_05_inst_adr                                               "0x005A"
#define ISO_GDI_CEC_OPRAND_05_inst                                                   0x005A
#define ISO_GDI_CEC_OPRAND_05_operand_05_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_05_operand_05_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_05_operand_05(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_05_operand_05_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_05_get_operand_05(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_06                                                        0x1800756C
#define ISO_GDI_CEC_OPRAND_06_reg_addr                                               "0xB800756C"
#define ISO_GDI_CEC_OPRAND_06_reg                                                    0xB800756C
#define set_ISO_GDI_CEC_OPRAND_06_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_06_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_06_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_06_reg))
#define ISO_GDI_CEC_OPRAND_06_inst_adr                                               "0x005B"
#define ISO_GDI_CEC_OPRAND_06_inst                                                   0x005B
#define ISO_GDI_CEC_OPRAND_06_operand_06_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_06_operand_06_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_06_operand_06(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_06_operand_06_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_06_get_operand_06(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_03                                                0x18007570
#define ISO_GDI_CEC_COMPARE_OPCODE_03_reg_addr                                       "0xB8007570"
#define ISO_GDI_CEC_COMPARE_OPCODE_03_reg                                            0xB8007570
#define set_ISO_GDI_CEC_COMPARE_OPCODE_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_03_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_03_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_03_inst_adr                                       "0x005C"
#define ISO_GDI_CEC_COMPARE_OPCODE_03_inst                                           0x005C
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_03_compare_opcode_03_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_03_get_compare_opcode_03(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_03                                                   0x18007574
#define ISO_GDI_CEC_SEND_OPCODE_03_reg_addr                                          "0xB8007574"
#define ISO_GDI_CEC_SEND_OPCODE_03_reg                                               0xB8007574
#define set_ISO_GDI_CEC_SEND_OPCODE_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_03_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_03_reg))
#define ISO_GDI_CEC_SEND_OPCODE_03_inst_adr                                          "0x005D"
#define ISO_GDI_CEC_SEND_OPCODE_03_inst                                              0x005D
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_03_send_opcode_03_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_03_get_send_opcode_03(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03                                            0x18007578
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg_addr                                   "0xB8007578"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg                                        0xB8007578
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_inst_adr                                   "0x005E"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_inst                                       0x005E
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_operand_number_03_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_03_get_operand_number_03(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_07                                                        0x1800757C
#define ISO_GDI_CEC_OPRAND_07_reg_addr                                               "0xB800757C"
#define ISO_GDI_CEC_OPRAND_07_reg                                                    0xB800757C
#define set_ISO_GDI_CEC_OPRAND_07_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_07_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_07_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_07_reg))
#define ISO_GDI_CEC_OPRAND_07_inst_adr                                               "0x005F"
#define ISO_GDI_CEC_OPRAND_07_inst                                                   0x005F
#define ISO_GDI_CEC_OPRAND_07_operand_07_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_07_operand_07_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_07_operand_07(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_07_operand_07_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_07_get_operand_07(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_08                                                        0x18007580
#define ISO_GDI_CEC_OPRAND_08_reg_addr                                               "0xB8007580"
#define ISO_GDI_CEC_OPRAND_08_reg                                                    0xB8007580
#define set_ISO_GDI_CEC_OPRAND_08_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_08_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_08_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_08_reg))
#define ISO_GDI_CEC_OPRAND_08_inst_adr                                               "0x0060"
#define ISO_GDI_CEC_OPRAND_08_inst                                                   0x0060
#define ISO_GDI_CEC_OPRAND_08_operand_08_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_08_operand_08_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_08_operand_08(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_08_operand_08_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_08_get_operand_08(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_09                                                        0x18007584
#define ISO_GDI_CEC_OPRAND_09_reg_addr                                               "0xB8007584"
#define ISO_GDI_CEC_OPRAND_09_reg                                                    0xB8007584
#define set_ISO_GDI_CEC_OPRAND_09_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_09_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_09_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_09_reg))
#define ISO_GDI_CEC_OPRAND_09_inst_adr                                               "0x0061"
#define ISO_GDI_CEC_OPRAND_09_inst                                                   0x0061
#define ISO_GDI_CEC_OPRAND_09_operand_09_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_09_operand_09_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_09_operand_09(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_09_operand_09_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_09_get_operand_09(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_04                                                0x18007588
#define ISO_GDI_CEC_COMPARE_OPCODE_04_reg_addr                                       "0xB8007588"
#define ISO_GDI_CEC_COMPARE_OPCODE_04_reg                                            0xB8007588
#define set_ISO_GDI_CEC_COMPARE_OPCODE_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_04_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_04_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_04_inst_adr                                       "0x0062"
#define ISO_GDI_CEC_COMPARE_OPCODE_04_inst                                           0x0062
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_04_compare_opcode_04_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_04_get_compare_opcode_04(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPCODE_04                                                   0x1800758C
#define ISO_GDI_CEC_SEND_OPCODE_04_reg_addr                                          "0xB800758C"
#define ISO_GDI_CEC_SEND_OPCODE_04_reg                                               0xB800758C
#define set_ISO_GDI_CEC_SEND_OPCODE_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_04_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPCODE_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPCODE_04_reg))
#define ISO_GDI_CEC_SEND_OPCODE_04_inst_adr                                          "0x0063"
#define ISO_GDI_CEC_SEND_OPCODE_04_inst                                              0x0063
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04_shift                              (0)
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04_mask                               (0x000000FF)
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04(data)                              (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_SEND_OPCODE_04_send_opcode_04_src(data)                          ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_SEND_OPCODE_04_get_send_opcode_04(data)                          ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04                                            0x18007590
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg_addr                                   "0xB8007590"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg                                        0xB8007590
#define set_ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg)=data)
#define get_ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg   (*((volatile unsigned int*) ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_reg))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_inst_adr                                   "0x0064"
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_inst                                       0x0064
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04_shift                    (0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04_mask                     (0x00000003)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04(data)                    (0x00000003&((data)<<0))
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_operand_number_04_src(data)                ((0x00000003&(data))>>0)
#define ISO_GDI_CEC_SEND_OPRAND_NUMBER_04_get_operand_number_04(data)                ((0x00000003&(data))>>0)


#define ISO_GDI_CEC_OPRAND_10                                                        0x18007594
#define ISO_GDI_CEC_OPRAND_10_reg_addr                                               "0xB8007594"
#define ISO_GDI_CEC_OPRAND_10_reg                                                    0xB8007594
#define set_ISO_GDI_CEC_OPRAND_10_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_10_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_10_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_10_reg))
#define ISO_GDI_CEC_OPRAND_10_inst_adr                                               "0x0065"
#define ISO_GDI_CEC_OPRAND_10_inst                                                   0x0065
#define ISO_GDI_CEC_OPRAND_10_operand_10_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_10_operand_10_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_10_operand_10(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_10_operand_10_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_10_get_operand_10(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_11                                                        0x18007598
#define ISO_GDI_CEC_OPRAND_11_reg_addr                                               "0xB8007598"
#define ISO_GDI_CEC_OPRAND_11_reg                                                    0xB8007598
#define set_ISO_GDI_CEC_OPRAND_11_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_11_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_11_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_11_reg))
#define ISO_GDI_CEC_OPRAND_11_inst_adr                                               "0x0066"
#define ISO_GDI_CEC_OPRAND_11_inst                                                   0x0066
#define ISO_GDI_CEC_OPRAND_11_operand_11_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_11_operand_11_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_11_operand_11(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_11_operand_11_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_11_get_operand_11(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPRAND_12                                                        0x1800759C
#define ISO_GDI_CEC_OPRAND_12_reg_addr                                               "0xB800759C"
#define ISO_GDI_CEC_OPRAND_12_reg                                                    0xB800759C
#define set_ISO_GDI_CEC_OPRAND_12_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_12_reg)=data)
#define get_ISO_GDI_CEC_OPRAND_12_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPRAND_12_reg))
#define ISO_GDI_CEC_OPRAND_12_inst_adr                                               "0x0067"
#define ISO_GDI_CEC_OPRAND_12_inst                                                   0x0067
#define ISO_GDI_CEC_OPRAND_12_operand_12_shift                                       (0)
#define ISO_GDI_CEC_OPRAND_12_operand_12_mask                                        (0x000000FF)
#define ISO_GDI_CEC_OPRAND_12_operand_12(data)                                       (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_OPRAND_12_operand_12_src(data)                                   ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_OPRAND_12_get_operand_12(data)                                   ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_05                                                0x180075A0
#define ISO_GDI_CEC_COMPARE_OPCODE_05_reg_addr                                       "0xB80075A0"
#define ISO_GDI_CEC_COMPARE_OPCODE_05_reg                                            0xB80075A0
#define set_ISO_GDI_CEC_COMPARE_OPCODE_05_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_05_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_05_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_05_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_05_inst_adr                                       "0x0068"
#define ISO_GDI_CEC_COMPARE_OPCODE_05_inst                                           0x0068
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_05_compare_opcode_05_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_05_get_compare_opcode_05(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_06                                                0x180075A4
#define ISO_GDI_CEC_COMPARE_OPCODE_06_reg_addr                                       "0xB80075A4"
#define ISO_GDI_CEC_COMPARE_OPCODE_06_reg                                            0xB80075A4
#define set_ISO_GDI_CEC_COMPARE_OPCODE_06_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_06_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_06_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_06_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_06_inst_adr                                       "0x0069"
#define ISO_GDI_CEC_COMPARE_OPCODE_06_inst                                           0x0069
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_06_compare_opcode_06_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_06_get_compare_opcode_06(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_07                                                0x180075A8
#define ISO_GDI_CEC_COMPARE_OPCODE_07_reg_addr                                       "0xB80075A8"
#define ISO_GDI_CEC_COMPARE_OPCODE_07_reg                                            0xB80075A8
#define set_ISO_GDI_CEC_COMPARE_OPCODE_07_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_07_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_07_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_07_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_07_inst_adr                                       "0x006A"
#define ISO_GDI_CEC_COMPARE_OPCODE_07_inst                                           0x006A
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_07_compare_opcode_07_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_07_get_compare_opcode_07(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_08                                                0x180075AC
#define ISO_GDI_CEC_COMPARE_OPCODE_08_reg_addr                                       "0xB80075AC"
#define ISO_GDI_CEC_COMPARE_OPCODE_08_reg                                            0xB80075AC
#define set_ISO_GDI_CEC_COMPARE_OPCODE_08_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_08_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_08_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_08_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_08_inst_adr                                       "0x006B"
#define ISO_GDI_CEC_COMPARE_OPCODE_08_inst                                           0x006B
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_08_compare_opcode_08_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_08_get_compare_opcode_08(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_09                                                0x180075B0
#define ISO_GDI_CEC_COMPARE_OPCODE_09_reg_addr                                       "0xB80075B0"
#define ISO_GDI_CEC_COMPARE_OPCODE_09_reg                                            0xB80075B0
#define set_ISO_GDI_CEC_COMPARE_OPCODE_09_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_09_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_09_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_09_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_09_inst_adr                                       "0x006C"
#define ISO_GDI_CEC_COMPARE_OPCODE_09_inst                                           0x006C
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_09_compare_opcode_09_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_09_get_compare_opcode_09(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_10                                                0x180075B4
#define ISO_GDI_CEC_COMPARE_OPCODE_10_reg_addr                                       "0xB80075B4"
#define ISO_GDI_CEC_COMPARE_OPCODE_10_reg                                            0xB80075B4
#define set_ISO_GDI_CEC_COMPARE_OPCODE_10_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_10_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_10_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_10_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_10_inst_adr                                       "0x006D"
#define ISO_GDI_CEC_COMPARE_OPCODE_10_inst                                           0x006D
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_10_compare_opcode_10_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_10_get_compare_opcode_10(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_11                                                0x180075B8
#define ISO_GDI_CEC_COMPARE_OPCODE_11_reg_addr                                       "0xB80075B8"
#define ISO_GDI_CEC_COMPARE_OPCODE_11_reg                                            0xB80075B8
#define set_ISO_GDI_CEC_COMPARE_OPCODE_11_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_11_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_11_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_11_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_11_inst_adr                                       "0x006E"
#define ISO_GDI_CEC_COMPARE_OPCODE_11_inst                                           0x006E
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_11_compare_opcode_11_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_11_get_compare_opcode_11(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_12                                                0x180075BC
#define ISO_GDI_CEC_COMPARE_OPCODE_12_reg_addr                                       "0xB80075BC"
#define ISO_GDI_CEC_COMPARE_OPCODE_12_reg                                            0xB80075BC
#define set_ISO_GDI_CEC_COMPARE_OPCODE_12_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_12_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_12_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_12_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_12_inst_adr                                       "0x006F"
#define ISO_GDI_CEC_COMPARE_OPCODE_12_inst                                           0x006F
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_12_compare_opcode_12_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_12_get_compare_opcode_12(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_13                                                0x180075C0
#define ISO_GDI_CEC_COMPARE_OPCODE_13_reg_addr                                       "0xB80075C0"
#define ISO_GDI_CEC_COMPARE_OPCODE_13_reg                                            0xB80075C0
#define set_ISO_GDI_CEC_COMPARE_OPCODE_13_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_13_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_13_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_13_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_13_inst_adr                                       "0x0070"
#define ISO_GDI_CEC_COMPARE_OPCODE_13_inst                                           0x0070
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_13_compare_opcode_13_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_13_get_compare_opcode_13(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_14                                                0x180075C4
#define ISO_GDI_CEC_COMPARE_OPCODE_14_reg_addr                                       "0xB80075C4"
#define ISO_GDI_CEC_COMPARE_OPCODE_14_reg                                            0xB80075C4
#define set_ISO_GDI_CEC_COMPARE_OPCODE_14_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_14_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_14_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_14_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_14_inst_adr                                       "0x0071"
#define ISO_GDI_CEC_COMPARE_OPCODE_14_inst                                           0x0071
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_14_compare_opcode_14_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_14_get_compare_opcode_14(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_COMPARE_OPCODE_15                                                0x180075C8
#define ISO_GDI_CEC_COMPARE_OPCODE_15_reg_addr                                       "0xB80075C8"
#define ISO_GDI_CEC_COMPARE_OPCODE_15_reg                                            0xB80075C8
#define set_ISO_GDI_CEC_COMPARE_OPCODE_15_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_15_reg)=data)
#define get_ISO_GDI_CEC_COMPARE_OPCODE_15_reg   (*((volatile unsigned int*) ISO_GDI_CEC_COMPARE_OPCODE_15_reg))
#define ISO_GDI_CEC_COMPARE_OPCODE_15_inst_adr                                       "0x0072"
#define ISO_GDI_CEC_COMPARE_OPCODE_15_inst                                           0x0072
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_shift                        (0)
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_mask                         (0x000000FF)
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15(data)                        (0x000000FF&((data)<<0))
#define ISO_GDI_CEC_COMPARE_OPCODE_15_compare_opcode_15_src(data)                    ((0x000000FF&(data))>>0)
#define ISO_GDI_CEC_COMPARE_OPCODE_15_get_compare_opcode_15(data)                    ((0x000000FF&(data))>>0)


#define ISO_GDI_CEC_OPCODE_ENABLE                                                    0x180075CC
#define ISO_GDI_CEC_OPCODE_ENABLE_reg_addr                                           "0xB80075CC"
#define ISO_GDI_CEC_OPCODE_ENABLE_reg                                                0xB80075CC
#define set_ISO_GDI_CEC_OPCODE_ENABLE_reg(data)   (*((volatile unsigned int*) ISO_GDI_CEC_OPCODE_ENABLE_reg)=data)
#define get_ISO_GDI_CEC_OPCODE_ENABLE_reg   (*((volatile unsigned int*) ISO_GDI_CEC_OPCODE_ENABLE_reg))
#define ISO_GDI_CEC_OPCODE_ENABLE_inst_adr                                           "0x0073"
#define ISO_GDI_CEC_OPCODE_ENABLE_inst                                               0x0073
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_shift                         (14)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_mask                          (0x00004000)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15(data)                         (0x00004000&((data)<<14))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_15_src(data)                     ((0x00004000&(data))>>14)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_15(data)                     ((0x00004000&(data))>>14)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_shift                         (13)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_mask                          (0x00002000)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14(data)                         (0x00002000&((data)<<13))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_14_src(data)                     ((0x00002000&(data))>>13)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_14(data)                     ((0x00002000&(data))>>13)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_shift                         (12)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_mask                          (0x00001000)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13(data)                         (0x00001000&((data)<<12))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_13_src(data)                     ((0x00001000&(data))>>12)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_13(data)                     ((0x00001000&(data))>>12)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_shift                         (11)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_mask                          (0x00000800)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12(data)                         (0x00000800&((data)<<11))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_12_src(data)                     ((0x00000800&(data))>>11)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_12(data)                     ((0x00000800&(data))>>11)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_shift                         (10)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_mask                          (0x00000400)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11(data)                         (0x00000400&((data)<<10))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_11_src(data)                     ((0x00000400&(data))>>10)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_11(data)                     ((0x00000400&(data))>>10)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_shift                         (9)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_mask                          (0x00000200)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10(data)                         (0x00000200&((data)<<9))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_10_src(data)                     ((0x00000200&(data))>>9)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_10(data)                     ((0x00000200&(data))>>9)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_shift                         (8)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_mask                          (0x00000100)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09(data)                         (0x00000100&((data)<<8))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_09_src(data)                     ((0x00000100&(data))>>8)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_09(data)                     ((0x00000100&(data))>>8)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_shift                         (7)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_mask                          (0x00000080)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08(data)                         (0x00000080&((data)<<7))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_08_src(data)                     ((0x00000080&(data))>>7)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_08(data)                     ((0x00000080&(data))>>7)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_shift                         (6)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_mask                          (0x00000040)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07(data)                         (0x00000040&((data)<<6))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_07_src(data)                     ((0x00000040&(data))>>6)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_07(data)                     ((0x00000040&(data))>>6)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_shift                         (5)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_mask                          (0x00000020)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06(data)                         (0x00000020&((data)<<5))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_06_src(data)                     ((0x00000020&(data))>>5)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_06(data)                     ((0x00000020&(data))>>5)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_shift                         (4)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_mask                          (0x00000010)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05(data)                         (0x00000010&((data)<<4))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_05_src(data)                     ((0x00000010&(data))>>4)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_05(data)                     ((0x00000010&(data))>>4)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_shift                         (3)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_mask                          (0x00000008)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04(data)                         (0x00000008&((data)<<3))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_04_src(data)                     ((0x00000008&(data))>>3)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_04(data)                     ((0x00000008&(data))>>3)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_shift                         (2)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_mask                          (0x00000004)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03(data)                         (0x00000004&((data)<<2))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_03_src(data)                     ((0x00000004&(data))>>2)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_03(data)                     ((0x00000004&(data))>>2)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_shift                         (1)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_mask                          (0x00000002)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02(data)                         (0x00000002&((data)<<1))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_02_src(data)                     ((0x00000002&(data))>>1)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_02(data)                     ((0x00000002&(data))>>1)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_shift                         (0)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_mask                          (0x00000001)
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01(data)                         (0x00000001&((data)<<0))
#define ISO_GDI_CEC_OPCODE_ENABLE_en_compare_opcode_01_src(data)                     ((0x00000001&(data))>>0)
#define ISO_GDI_CEC_OPCODE_ENABLE_get_en_compare_opcode_01(data)                     ((0x00000001&(data))>>0)


#define ISO_GDI_POWER_SAVING_MODE                                                    0x180075D0
#define ISO_GDI_POWER_SAVING_MODE_reg_addr                                           "0xB80075D0"
#define ISO_GDI_POWER_SAVING_MODE_reg                                                0xB80075D0
#define set_ISO_GDI_POWER_SAVING_MODE_reg(data)   (*((volatile unsigned int*) ISO_GDI_POWER_SAVING_MODE_reg)=data)
#define get_ISO_GDI_POWER_SAVING_MODE_reg   (*((volatile unsigned int*) ISO_GDI_POWER_SAVING_MODE_reg))
#define ISO_GDI_POWER_SAVING_MODE_inst_adr                                           "0x0074"
#define ISO_GDI_POWER_SAVING_MODE_inst                                               0x0074
#define ISO_GDI_POWER_SAVING_MODE_irq_pending_shift                                  (31)
#define ISO_GDI_POWER_SAVING_MODE_irq_pending_mask                                   (0x80000000)
#define ISO_GDI_POWER_SAVING_MODE_irq_pending(data)                                  (0x80000000&((data)<<31))
#define ISO_GDI_POWER_SAVING_MODE_irq_pending_src(data)                              ((0x80000000&(data))>>31)
#define ISO_GDI_POWER_SAVING_MODE_get_irq_pending(data)                              ((0x80000000&(data))>>31)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01_shift                            (25)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01_mask                             (0x02000000)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01(data)                            (0x02000000&((data)<<25))
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_01_src(data)                        ((0x02000000&(data))>>25)
#define ISO_GDI_POWER_SAVING_MODE_get_cec_msg_status_01(data)                        ((0x02000000&(data))>>25)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02_shift                            (24)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02_mask                             (0x01000000)
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02(data)                            (0x01000000&((data)<<24))
#define ISO_GDI_POWER_SAVING_MODE_cec_msg_status_02_src(data)                        ((0x01000000&(data))>>24)
#define ISO_GDI_POWER_SAVING_MODE_get_cec_msg_status_02(data)                        ((0x01000000&(data))>>24)
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_shift               (8)
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_mask                (0x00000100)
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd(data)               (0x00000100&((data)<<8))
#define ISO_GDI_POWER_SAVING_MODE_irq_by_cec_receive_special_cmd_src(data)           ((0x00000100&(data))>>8)
#define ISO_GDI_POWER_SAVING_MODE_get_irq_by_cec_receive_special_cmd(data)           ((0x00000100&(data))>>8)


#define ISO_DRM_ST                                                                   0x18007600
#define ISO_DRM_ST_reg_addr                                                          "0xB8007600"
#define ISO_DRM_ST_reg                                                               0xB8007600
#define set_ISO_DRM_ST_reg(data)   (*((volatile unsigned int*) ISO_DRM_ST_reg)=data)
#define get_ISO_DRM_ST_reg   (*((volatile unsigned int*) ISO_DRM_ST_reg))
#define ISO_DRM_ST_inst_adr                                                          "0x0080"
#define ISO_DRM_ST_inst                                                              0x0080
#define ISO_DRM_ST_set_shift                                                         (0)
#define ISO_DRM_ST_set_mask                                                          (0x00000001)
#define ISO_DRM_ST_set(data)                                                         (0x00000001&((data)<<0))
#define ISO_DRM_ST_set_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_DRM_ST_get_set(data)                                                     ((0x00000001&(data))>>0)


#define ISO_DRM_SECURE_CLK                                                           0x18007604
#define ISO_DRM_SECURE_CLK_reg_addr                                                  "0xB8007604"
#define ISO_DRM_SECURE_CLK_reg                                                       0xB8007604
#define set_ISO_DRM_SECURE_CLK_reg(data)   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_reg)=data)
#define get_ISO_DRM_SECURE_CLK_reg   (*((volatile unsigned int*) ISO_DRM_SECURE_CLK_reg))
#define ISO_DRM_SECURE_CLK_inst_adr                                                  "0x0081"
#define ISO_DRM_SECURE_CLK_inst                                                      0x0081
#define ISO_DRM_SECURE_CLK_val_shift                                                 (0)
#define ISO_DRM_SECURE_CLK_val_mask                                                  (0xFFFFFFFF)
#define ISO_DRM_SECURE_CLK_val(data)                                                 (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_SECURE_CLK_val_src(data)                                             ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_SECURE_CLK_get_val(data)                                             ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_ELAPSED                                                              0x18007608
#define ISO_DRM_ELAPSED_reg_addr                                                     "0xB8007608"
#define ISO_DRM_ELAPSED_reg                                                          0xB8007608
#define set_ISO_DRM_ELAPSED_reg(data)   (*((volatile unsigned int*) ISO_DRM_ELAPSED_reg)=data)
#define get_ISO_DRM_ELAPSED_reg   (*((volatile unsigned int*) ISO_DRM_ELAPSED_reg))
#define ISO_DRM_ELAPSED_inst_adr                                                     "0x0082"
#define ISO_DRM_ELAPSED_inst                                                         0x0082
#define ISO_DRM_ELAPSED_val_shift                                                    (0)
#define ISO_DRM_ELAPSED_val_mask                                                     (0xFFFFFFFF)
#define ISO_DRM_ELAPSED_val(data)                                                    (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_ELAPSED_val_src(data)                                                ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_ELAPSED_get_val(data)                                                ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST                                                                 0x1800760C
#define ISO_COLD_RST_reg_addr                                                        "0xB800760C"
#define ISO_COLD_RST_reg                                                             0xB800760C
#define set_ISO_COLD_RST_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST_reg)=data)
#define get_ISO_COLD_RST_reg   (*((volatile unsigned int*) ISO_COLD_RST_reg))
#define ISO_COLD_RST_inst_adr                                                        "0x0083"
#define ISO_COLD_RST_inst                                                            0x0083
#define ISO_COLD_RST_val_shift                                                       (0)
#define ISO_COLD_RST_val_mask                                                        (0xFFFFFFFF)
#define ISO_COLD_RST_val(data)                                                       (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST_val_src(data)                                                   ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST_get_val(data)                                                   ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST1                                                                0x18007610
#define ISO_COLD_RST1_reg_addr                                                       "0xB8007610"
#define ISO_COLD_RST1_reg                                                            0xB8007610
#define set_ISO_COLD_RST1_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST1_reg)=data)
#define get_ISO_COLD_RST1_reg   (*((volatile unsigned int*) ISO_COLD_RST1_reg))
#define ISO_COLD_RST1_inst_adr                                                       "0x0084"
#define ISO_COLD_RST1_inst                                                           0x0084
#define ISO_COLD_RST1_val_shift                                                      (0)
#define ISO_COLD_RST1_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST1_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST1_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST1_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST2                                                                0x18007614
#define ISO_COLD_RST2_reg_addr                                                       "0xB8007614"
#define ISO_COLD_RST2_reg                                                            0xB8007614
#define set_ISO_COLD_RST2_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST2_reg)=data)
#define get_ISO_COLD_RST2_reg   (*((volatile unsigned int*) ISO_COLD_RST2_reg))
#define ISO_COLD_RST2_inst_adr                                                       "0x0085"
#define ISO_COLD_RST2_inst                                                           0x0085
#define ISO_COLD_RST2_val_shift                                                      (0)
#define ISO_COLD_RST2_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST2_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST2_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST2_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_DRM_CTRL                                                                 0x18007618
#define ISO_DRM_CTRL_reg_addr                                                        "0xB8007618"
#define ISO_DRM_CTRL_reg                                                             0xB8007618
#define set_ISO_DRM_CTRL_reg(data)   (*((volatile unsigned int*) ISO_DRM_CTRL_reg)=data)
#define get_ISO_DRM_CTRL_reg   (*((volatile unsigned int*) ISO_DRM_CTRL_reg))
#define ISO_DRM_CTRL_inst_adr                                                        "0x0086"
#define ISO_DRM_CTRL_inst                                                            0x0086
#define ISO_DRM_CTRL_clk_div_en_shift                                                (1)
#define ISO_DRM_CTRL_clk_div_en_mask                                                 (0x00000002)
#define ISO_DRM_CTRL_clk_div_en(data)                                                (0x00000002&((data)<<1))
#define ISO_DRM_CTRL_clk_div_en_src(data)                                            ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_get_clk_div_en(data)                                            ((0x00000002&(data))>>1)
#define ISO_DRM_CTRL_clk_sel_shift                                                   (0)
#define ISO_DRM_CTRL_clk_sel_mask                                                    (0x00000001)
#define ISO_DRM_CTRL_clk_sel(data)                                                   (0x00000001&((data)<<0))
#define ISO_DRM_CTRL_clk_sel_src(data)                                               ((0x00000001&(data))>>0)
#define ISO_DRM_CTRL_get_clk_sel(data)                                               ((0x00000001&(data))>>0)


#define ISO_DRM_CLK_DIV                                                              0x1800761c
#define ISO_DRM_CLK_DIV_reg_addr                                                     "0xB800761C"
#define ISO_DRM_CLK_DIV_reg                                                          0xB800761C
#define set_ISO_DRM_CLK_DIV_reg(data)   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_reg)=data)
#define get_ISO_DRM_CLK_DIV_reg   (*((volatile unsigned int*) ISO_DRM_CLK_DIV_reg))
#define ISO_DRM_CLK_DIV_inst_adr                                                     "0x0087"
#define ISO_DRM_CLK_DIV_inst                                                         0x0087
#define ISO_DRM_CLK_DIV_init_shift                                                   (0)
#define ISO_DRM_CLK_DIV_init_mask                                                    (0xFFFFFFFF)
#define ISO_DRM_CLK_DIV_init(data)                                                   (0xFFFFFFFF&((data)<<0))
#define ISO_DRM_CLK_DIV_init_src(data)                                               ((0xFFFFFFFF&(data))>>0)
#define ISO_DRM_CLK_DIV_get_init(data)                                               ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3TVR                                                                   0x18007620
#define ISO_TC3TVR_reg_addr                                                          "0xB8007620"
#define ISO_TC3TVR_reg                                                               0xB8007620
#define set_ISO_TC3TVR_reg(data)   (*((volatile unsigned int*) ISO_TC3TVR_reg)=data)
#define get_ISO_TC3TVR_reg   (*((volatile unsigned int*) ISO_TC3TVR_reg))
#define ISO_TC3TVR_inst_adr                                                          "0x0088"
#define ISO_TC3TVR_inst                                                              0x0088
#define ISO_TC3TVR_tc3tvr_shift                                                      (0)
#define ISO_TC3TVR_tc3tvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC3TVR_tc3tvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC3TVR_tc3tvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC3TVR_get_tc3tvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3CVR                                                                   0x18007624
#define ISO_TC3CVR_reg_addr                                                          "0xB8007624"
#define ISO_TC3CVR_reg                                                               0xB8007624
#define set_ISO_TC3CVR_reg(data)   (*((volatile unsigned int*) ISO_TC3CVR_reg)=data)
#define get_ISO_TC3CVR_reg   (*((volatile unsigned int*) ISO_TC3CVR_reg))
#define ISO_TC3CVR_inst_adr                                                          "0x0089"
#define ISO_TC3CVR_inst                                                              0x0089
#define ISO_TC3CVR_tc3cvr_shift                                                      (0)
#define ISO_TC3CVR_tc3cvr_mask                                                       (0xFFFFFFFF)
#define ISO_TC3CVR_tc3cvr(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_TC3CVR_tc3cvr_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_TC3CVR_get_tc3cvr(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_TC3CR                                                                    0x18007628
#define ISO_TC3CR_reg_addr                                                           "0xB8007628"
#define ISO_TC3CR_reg                                                                0xB8007628
#define set_ISO_TC3CR_reg(data)   (*((volatile unsigned int*) ISO_TC3CR_reg)=data)
#define get_ISO_TC3CR_reg   (*((volatile unsigned int*) ISO_TC3CR_reg))
#define ISO_TC3CR_inst_adr                                                           "0x008A"
#define ISO_TC3CR_inst                                                               0x008A
#define ISO_TC3CR_tc3en_shift                                                        (31)
#define ISO_TC3CR_tc3en_mask                                                         (0x80000000)
#define ISO_TC3CR_tc3en(data)                                                        (0x80000000&((data)<<31))
#define ISO_TC3CR_tc3en_src(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC3CR_get_tc3en(data)                                                    ((0x80000000&(data))>>31)
#define ISO_TC3CR_tc3mode_shift                                                      (30)
#define ISO_TC3CR_tc3mode_mask                                                       (0x40000000)
#define ISO_TC3CR_tc3mode(data)                                                      (0x40000000&((data)<<30))
#define ISO_TC3CR_tc3mode_src(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC3CR_get_tc3mode(data)                                                  ((0x40000000&(data))>>30)
#define ISO_TC3CR_tc3pause_shift                                                     (29)
#define ISO_TC3CR_tc3pause_mask                                                      (0x20000000)
#define ISO_TC3CR_tc3pause(data)                                                     (0x20000000&((data)<<29))
#define ISO_TC3CR_tc3pause_src(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC3CR_get_tc3pause(data)                                                 ((0x20000000&(data))>>29)
#define ISO_TC3CR_rvda_shift                                                         (24)
#define ISO_TC3CR_rvda_mask                                                          (0x1F000000)
#define ISO_TC3CR_rvda(data)                                                         (0x1F000000&((data)<<24))
#define ISO_TC3CR_rvda_src(data)                                                     ((0x1F000000&(data))>>24)
#define ISO_TC3CR_get_rvda(data)                                                     ((0x1F000000&(data))>>24)


#define ISO_TC3ICR                                                                   0x1800762C
#define ISO_TC3ICR_reg_addr                                                          "0xB800762C"
#define ISO_TC3ICR_reg                                                               0xB800762C
#define set_ISO_TC3ICR_reg(data)   (*((volatile unsigned int*) ISO_TC3ICR_reg)=data)
#define get_ISO_TC3ICR_reg   (*((volatile unsigned int*) ISO_TC3ICR_reg))
#define ISO_TC3ICR_inst_adr                                                          "0x008B"
#define ISO_TC3ICR_inst                                                              0x008B
#define ISO_TC3ICR_tc3ie_shift                                                       (31)
#define ISO_TC3ICR_tc3ie_mask                                                        (0x80000000)
#define ISO_TC3ICR_tc3ie(data)                                                       (0x80000000&((data)<<31))
#define ISO_TC3ICR_tc3ie_src(data)                                                   ((0x80000000&(data))>>31)
#define ISO_TC3ICR_get_tc3ie(data)                                                   ((0x80000000&(data))>>31)


#define ISO_NORST_0                                                                  0x18007640
#define ISO_NORST_1                                                                  0x18007644
#define ISO_NORST_2                                                                  0x18007648
#define ISO_NORST_3                                                                  0x1800764C
#define ISO_NORST_4                                                                  0x18007650
#define ISO_NORST_5                                                                  0x18007654
#define ISO_NORST_6                                                                  0x18007658
#define ISO_NORST_7                                                                  0x1800765C
#define ISO_NORST_0_reg_addr                                                         "0xB8007640"
#define ISO_NORST_1_reg_addr                                                         "0xB8007644"
#define ISO_NORST_2_reg_addr                                                         "0xB8007648"
#define ISO_NORST_3_reg_addr                                                         "0xB800764C"
#define ISO_NORST_4_reg_addr                                                         "0xB8007650"
#define ISO_NORST_5_reg_addr                                                         "0xB8007654"
#define ISO_NORST_6_reg_addr                                                         "0xB8007658"
#define ISO_NORST_7_reg_addr                                                         "0xB800765C"
#define ISO_NORST_0_reg                                                              0xB8007640
#define ISO_NORST_1_reg                                                              0xB8007644
#define ISO_NORST_2_reg                                                              0xB8007648
#define ISO_NORST_3_reg                                                              0xB800764C
#define ISO_NORST_4_reg                                                              0xB8007650
#define ISO_NORST_5_reg                                                              0xB8007654
#define ISO_NORST_6_reg                                                              0xB8007658
#define ISO_NORST_7_reg                                                              0xB800765C
#define set_ISO_NORST_0_reg(data)   (*((volatile unsigned int*) ISO_NORST_0_reg)=data)
#define set_ISO_NORST_1_reg(data)   (*((volatile unsigned int*) ISO_NORST_1_reg)=data)
#define set_ISO_NORST_2_reg(data)   (*((volatile unsigned int*) ISO_NORST_2_reg)=data)
#define set_ISO_NORST_3_reg(data)   (*((volatile unsigned int*) ISO_NORST_3_reg)=data)
#define set_ISO_NORST_4_reg(data)   (*((volatile unsigned int*) ISO_NORST_4_reg)=data)
#define set_ISO_NORST_5_reg(data)   (*((volatile unsigned int*) ISO_NORST_5_reg)=data)
#define set_ISO_NORST_6_reg(data)   (*((volatile unsigned int*) ISO_NORST_6_reg)=data)
#define set_ISO_NORST_7_reg(data)   (*((volatile unsigned int*) ISO_NORST_7_reg)=data)
#define get_ISO_NORST_0_reg   (*((volatile unsigned int*) ISO_NORST_0_reg))
#define get_ISO_NORST_1_reg   (*((volatile unsigned int*) ISO_NORST_1_reg))
#define get_ISO_NORST_2_reg   (*((volatile unsigned int*) ISO_NORST_2_reg))
#define get_ISO_NORST_3_reg   (*((volatile unsigned int*) ISO_NORST_3_reg))
#define get_ISO_NORST_4_reg   (*((volatile unsigned int*) ISO_NORST_4_reg))
#define get_ISO_NORST_5_reg   (*((volatile unsigned int*) ISO_NORST_5_reg))
#define get_ISO_NORST_6_reg   (*((volatile unsigned int*) ISO_NORST_6_reg))
#define get_ISO_NORST_7_reg   (*((volatile unsigned int*) ISO_NORST_7_reg))
#define ISO_NORST_0_inst_adr                                                         "0x0090"
#define ISO_NORST_1_inst_adr                                                         "0x0091"
#define ISO_NORST_2_inst_adr                                                         "0x0092"
#define ISO_NORST_3_inst_adr                                                         "0x0093"
#define ISO_NORST_4_inst_adr                                                         "0x0094"
#define ISO_NORST_5_inst_adr                                                         "0x0095"
#define ISO_NORST_6_inst_adr                                                         "0x0096"
#define ISO_NORST_7_inst_adr                                                         "0x0097"
#define ISO_NORST_0_inst                                                             0x0090
#define ISO_NORST_1_inst                                                             0x0091
#define ISO_NORST_2_inst                                                             0x0092
#define ISO_NORST_3_inst                                                             0x0093
#define ISO_NORST_4_inst                                                             0x0094
#define ISO_NORST_5_inst                                                             0x0095
#define ISO_NORST_6_inst                                                             0x0096
#define ISO_NORST_7_inst                                                             0x0097
#define ISO_NORST_dat_shift                                                          (0)
#define ISO_NORST_dat_mask                                                           (0xFFFFFFFF)
#define ISO_NORST_dat(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_NORST_dat_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_NORST_get_dat(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST3                                                                0x18007660
#define ISO_COLD_RST3_reg_addr                                                       "0xB8007660"
#define ISO_COLD_RST3_reg                                                            0xB8007660
#define set_ISO_COLD_RST3_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST3_reg)=data)
#define get_ISO_COLD_RST3_reg   (*((volatile unsigned int*) ISO_COLD_RST3_reg))
#define ISO_COLD_RST3_inst_adr                                                       "0x0098"
#define ISO_COLD_RST3_inst                                                           0x0098
#define ISO_COLD_RST3_val_shift                                                      (0)
#define ISO_COLD_RST3_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST3_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST3_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST3_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST4                                                                0x18007664
#define ISO_COLD_RST4_reg_addr                                                       "0xB8007664"
#define ISO_COLD_RST4_reg                                                            0xB8007664
#define set_ISO_COLD_RST4_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST4_reg)=data)
#define get_ISO_COLD_RST4_reg   (*((volatile unsigned int*) ISO_COLD_RST4_reg))
#define ISO_COLD_RST4_inst_adr                                                       "0x0099"
#define ISO_COLD_RST4_inst                                                           0x0099
#define ISO_COLD_RST4_val_shift                                                      (0)
#define ISO_COLD_RST4_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST4_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST4_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST4_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST5                                                                0x18007668
#define ISO_COLD_RST5_reg_addr                                                       "0xB8007668"
#define ISO_COLD_RST5_reg                                                            0xB8007668
#define set_ISO_COLD_RST5_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST5_reg)=data)
#define get_ISO_COLD_RST5_reg   (*((volatile unsigned int*) ISO_COLD_RST5_reg))
#define ISO_COLD_RST5_inst_adr                                                       "0x009A"
#define ISO_COLD_RST5_inst                                                           0x009A
#define ISO_COLD_RST5_val_shift                                                      (0)
#define ISO_COLD_RST5_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST5_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST5_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST5_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST6                                                                0x1800766C
#define ISO_COLD_RST6_reg_addr                                                       "0xB800766C"
#define ISO_COLD_RST6_reg                                                            0xB800766C
#define set_ISO_COLD_RST6_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST6_reg)=data)
#define get_ISO_COLD_RST6_reg   (*((volatile unsigned int*) ISO_COLD_RST6_reg))
#define ISO_COLD_RST6_inst_adr                                                       "0x009B"
#define ISO_COLD_RST6_inst                                                           0x009B
#define ISO_COLD_RST6_val_shift                                                      (0)
#define ISO_COLD_RST6_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST6_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST6_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST6_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST7                                                                0x18007670
#define ISO_COLD_RST7_reg_addr                                                       "0xB8007670"
#define ISO_COLD_RST7_reg                                                            0xB8007670
#define set_ISO_COLD_RST7_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST7_reg)=data)
#define get_ISO_COLD_RST7_reg   (*((volatile unsigned int*) ISO_COLD_RST7_reg))
#define ISO_COLD_RST7_inst_adr                                                       "0x009C"
#define ISO_COLD_RST7_inst                                                           0x009C
#define ISO_COLD_RST7_val_shift                                                      (0)
#define ISO_COLD_RST7_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST7_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST7_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST7_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST8                                                                0x18007674
#define ISO_COLD_RST8_reg_addr                                                       "0xB8007674"
#define ISO_COLD_RST8_reg                                                            0xB8007674
#define set_ISO_COLD_RST8_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST8_reg)=data)
#define get_ISO_COLD_RST8_reg   (*((volatile unsigned int*) ISO_COLD_RST8_reg))
#define ISO_COLD_RST8_inst_adr                                                       "0x009D"
#define ISO_COLD_RST8_inst                                                           0x009D
#define ISO_COLD_RST8_val_shift                                                      (0)
#define ISO_COLD_RST8_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST8_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST8_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST8_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST9                                                                0x18007678
#define ISO_COLD_RST9_reg_addr                                                       "0xB8007678"
#define ISO_COLD_RST9_reg                                                            0xB8007678
#define set_ISO_COLD_RST9_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST9_reg)=data)
#define get_ISO_COLD_RST9_reg   (*((volatile unsigned int*) ISO_COLD_RST9_reg))
#define ISO_COLD_RST9_inst_adr                                                       "0x009E"
#define ISO_COLD_RST9_inst                                                           0x009E
#define ISO_COLD_RST9_val_shift                                                      (0)
#define ISO_COLD_RST9_val_mask                                                       (0xFFFFFFFF)
#define ISO_COLD_RST9_val(data)                                                      (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST9_val_src(data)                                                  ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST9_get_val(data)                                                  ((0xFFFFFFFF&(data))>>0)


#define ISO_COLD_RST10                                                               0x1800767C
#define ISO_COLD_RST10_reg_addr                                                      "0xB800767C"
#define ISO_COLD_RST10_reg                                                           0xB800767C
#define set_ISO_COLD_RST10_reg(data)   (*((volatile unsigned int*) ISO_COLD_RST10_reg)=data)
#define get_ISO_COLD_RST10_reg   (*((volatile unsigned int*) ISO_COLD_RST10_reg))
#define ISO_COLD_RST10_inst_adr                                                      "0x009F"
#define ISO_COLD_RST10_inst                                                          0x009F
#define ISO_COLD_RST10_val_shift                                                     (0)
#define ISO_COLD_RST10_val_mask                                                      (0xFFFFFFFF)
#define ISO_COLD_RST10_val(data)                                                     (0xFFFFFFFF&((data)<<0))
#define ISO_COLD_RST10_val_src(data)                                                 ((0xFFFFFFFF&(data))>>0)
#define ISO_COLD_RST10_get_val(data)                                                 ((0xFFFFFFFF&(data))>>0)


#define ISO_CPU_ST2V                                                                 0x18007738
#define ISO_CPU_ST2V_reg_addr                                                        "0xB8007738"
#define ISO_CPU_ST2V_reg                                                             0xB8007738
#define set_ISO_CPU_ST2V_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST2V_reg)=data)
#define get_ISO_CPU_ST2V_reg   (*((volatile unsigned int*) ISO_CPU_ST2V_reg))
#define ISO_CPU_ST2V_inst_adr                                                        "0x00CE"
#define ISO_CPU_ST2V_inst                                                            0x00CE
#define ISO_CPU_ST2V_kcpu_boot_info_valid_shift                                      (0)
#define ISO_CPU_ST2V_kcpu_boot_info_valid_mask                                       (0x00000001)
#define ISO_CPU_ST2V_kcpu_boot_info_valid(data)                                      (0x00000001&((data)<<0))
#define ISO_CPU_ST2V_kcpu_boot_info_valid_src(data)                                  ((0x00000001&(data))>>0)
#define ISO_CPU_ST2V_get_kcpu_boot_info_valid(data)                                  ((0x00000001&(data))>>0)


#define ISO_CPU_ST2                                                                  0x1800773C
#define ISO_CPU_ST2_reg_addr                                                         "0xB800773C"
#define ISO_CPU_ST2_reg                                                              0xB800773C
#define set_ISO_CPU_ST2_reg(data)   (*((volatile unsigned int*) ISO_CPU_ST2_reg)=data)
#define get_ISO_CPU_ST2_reg   (*((volatile unsigned int*) ISO_CPU_ST2_reg))
#define ISO_CPU_ST2_inst_adr                                                         "0x00CF"
#define ISO_CPU_ST2_inst                                                             0x00CF
#define ISO_CPU_ST2_kcpu_boot_info_shift                                             (0)
#define ISO_CPU_ST2_kcpu_boot_info_mask                                              (0xFFFFFFFF)
#define ISO_CPU_ST2_kcpu_boot_info(data)                                             (0xFFFFFFFF&((data)<<0))
#define ISO_CPU_ST2_kcpu_boot_info_src(data)                                         ((0xFFFFFFFF&(data))>>0)
#define ISO_CPU_ST2_get_kcpu_boot_info(data)                                         ((0xFFFFFFFF&(data))>>0)


#define ISO_ACPU_DBG                                                                 0x18007740
#define ISO_ACPU_DBG_reg_addr                                                        "0xB8007740"
#define ISO_ACPU_DBG_reg                                                             0xB8007740
#define set_ISO_ACPU_DBG_reg(data)   (*((volatile unsigned int*) ISO_ACPU_DBG_reg)=data)
#define get_ISO_ACPU_DBG_reg   (*((volatile unsigned int*) ISO_ACPU_DBG_reg))
#define ISO_ACPU_DBG_inst_adr                                                        "0x00D0"
#define ISO_ACPU_DBG_inst                                                            0x00D0
#define ISO_ACPU_DBG_write_enable3_shift                                             (13)
#define ISO_ACPU_DBG_write_enable3_mask                                              (0x00002000)
#define ISO_ACPU_DBG_write_enable3(data)                                             (0x00002000&((data)<<13))
#define ISO_ACPU_DBG_write_enable3_src(data)                                         ((0x00002000&(data))>>13)
#define ISO_ACPU_DBG_get_write_enable3(data)                                         ((0x00002000&(data))>>13)
#define ISO_ACPU_DBG_sel1_shift                                                      (8)
#define ISO_ACPU_DBG_sel1_mask                                                       (0x00001F00)
#define ISO_ACPU_DBG_sel1(data)                                                      (0x00001F00&((data)<<8))
#define ISO_ACPU_DBG_sel1_src(data)                                                  ((0x00001F00&(data))>>8)
#define ISO_ACPU_DBG_get_sel1(data)                                                  ((0x00001F00&(data))>>8)
#define ISO_ACPU_DBG_write_enable2_shift                                             (7)
#define ISO_ACPU_DBG_write_enable2_mask                                              (0x00000080)
#define ISO_ACPU_DBG_write_enable2(data)                                             (0x00000080&((data)<<7))
#define ISO_ACPU_DBG_write_enable2_src(data)                                         ((0x00000080&(data))>>7)
#define ISO_ACPU_DBG_get_write_enable2(data)                                         ((0x00000080&(data))>>7)
#define ISO_ACPU_DBG_sel0_shift                                                      (2)
#define ISO_ACPU_DBG_sel0_mask                                                       (0x0000007C)
#define ISO_ACPU_DBG_sel0(data)                                                      (0x0000007C&((data)<<2))
#define ISO_ACPU_DBG_sel0_src(data)                                                  ((0x0000007C&(data))>>2)
#define ISO_ACPU_DBG_get_sel0(data)                                                  ((0x0000007C&(data))>>2)
#define ISO_ACPU_DBG_write_enable1_shift                                             (1)
#define ISO_ACPU_DBG_write_enable1_mask                                              (0x00000002)
#define ISO_ACPU_DBG_write_enable1(data)                                             (0x00000002&((data)<<1))
#define ISO_ACPU_DBG_write_enable1_src(data)                                         ((0x00000002&(data))>>1)
#define ISO_ACPU_DBG_get_write_enable1(data)                                         ((0x00000002&(data))>>1)
#define ISO_ACPU_DBG_enable_shift                                                    (0)
#define ISO_ACPU_DBG_enable_mask                                                     (0x00000001)
#define ISO_ACPU_DBG_enable(data)                                                    (0x00000001&((data)<<0))
#define ISO_ACPU_DBG_enable_src(data)                                                ((0x00000001&(data))>>0)
#define ISO_ACPU_DBG_get_enable(data)                                                ((0x00000001&(data))>>0)


#define ISO_ANLG                                                                     0x18007744
#define ISO_ANLG_reg_addr                                                            "0xB8007744"
#define ISO_ANLG_reg                                                                 0xB8007744
#define set_ISO_ANLG_reg(data)   (*((volatile unsigned int*) ISO_ANLG_reg)=data)
#define get_ISO_ANLG_reg   (*((volatile unsigned int*) ISO_ANLG_reg))
#define ISO_ANLG_inst_adr                                                            "0x00D1"
#define ISO_ANLG_inst                                                                0x00D1
#define ISO_ANLG_analogy_mode_in_shift                                               (0)
#define ISO_ANLG_analogy_mode_in_mask                                                (0x00000001)
#define ISO_ANLG_analogy_mode_in(data)                                               (0x00000001&((data)<<0))
#define ISO_ANLG_analogy_mode_in_src(data)                                           ((0x00000001&(data))>>0)
#define ISO_ANLG_get_analogy_mode_in(data)                                           ((0x00000001&(data))>>0)


#define ISO_U0RBR_THR_DLL                                                            0x18007800
#define ISO_U0RBR_THR_DLL_reg_addr                                                   "0xB8007800"
#define ISO_U0RBR_THR_DLL_reg                                                        0xB8007800
#define set_ISO_U0RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) ISO_U0RBR_THR_DLL_reg)=data)
#define get_ISO_U0RBR_THR_DLL_reg   (*((volatile unsigned int*) ISO_U0RBR_THR_DLL_reg))
#define ISO_U0RBR_THR_DLL_inst_adr                                                   "0x0000"
#define ISO_U0RBR_THR_DLL_inst                                                       0x0000
#define ISO_U0RBR_THR_DLL_dll_shift                                                  (0)
#define ISO_U0RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define ISO_U0RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define ISO_U0RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_U0RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define ISO_U0IER_DLH                                                                0x18007804
#define ISO_U0IER_DLH_reg_addr                                                       "0xB8007804"
#define ISO_U0IER_DLH_reg                                                            0xB8007804
#define set_ISO_U0IER_DLH_reg(data)   (*((volatile unsigned int*) ISO_U0IER_DLH_reg)=data)
#define get_ISO_U0IER_DLH_reg   (*((volatile unsigned int*) ISO_U0IER_DLH_reg))
#define ISO_U0IER_DLH_inst_adr                                                       "0x0001"
#define ISO_U0IER_DLH_inst                                                           0x0001
#define ISO_U0IER_DLH_dlh_shift                                                      (0)
#define ISO_U0IER_DLH_dlh_mask                                                       (0x000000FF)
#define ISO_U0IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define ISO_U0IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_U0IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_U0IIR_FCR                                                                0x18007808
#define ISO_U0IIR_FCR_reg_addr                                                       "0xB8007808"
#define ISO_U0IIR_FCR_reg                                                            0xB8007808
#define set_ISO_U0IIR_FCR_reg(data)   (*((volatile unsigned int*) ISO_U0IIR_FCR_reg)=data)
#define get_ISO_U0IIR_FCR_reg   (*((volatile unsigned int*) ISO_U0IIR_FCR_reg))
#define ISO_U0IIR_FCR_inst_adr                                                       "0x0002"
#define ISO_U0IIR_FCR_inst                                                           0x0002
#define ISO_U0IIR_FCR_fifo16_shift                                                   (6)
#define ISO_U0IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define ISO_U0IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define ISO_U0IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U0IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U0IIR_FCR_iid_shift                                                      (0)
#define ISO_U0IIR_FCR_iid_mask                                                       (0x0000000F)
#define ISO_U0IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define ISO_U0IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define ISO_U0IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define ISO_U0LCR                                                                    0x1800780C
#define ISO_U0LCR_reg_addr                                                           "0xB800780C"
#define ISO_U0LCR_reg                                                                0xB800780C
#define set_ISO_U0LCR_reg(data)   (*((volatile unsigned int*) ISO_U0LCR_reg)=data)
#define get_ISO_U0LCR_reg   (*((volatile unsigned int*) ISO_U0LCR_reg))
#define ISO_U0LCR_inst_adr                                                           "0x0003"
#define ISO_U0LCR_inst                                                               0x0003
#define ISO_U0LCR_dlab_shift                                                         (7)
#define ISO_U0LCR_dlab_mask                                                          (0x00000080)
#define ISO_U0LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define ISO_U0LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U0LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U0LCR_brk_shift                                                          (6)
#define ISO_U0LCR_brk_mask                                                           (0x00000040)
#define ISO_U0LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define ISO_U0LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U0LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U0LCR_eps_shift                                                          (4)
#define ISO_U0LCR_eps_mask                                                           (0x00000010)
#define ISO_U0LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0LCR_pen_shift                                                          (3)
#define ISO_U0LCR_pen_mask                                                           (0x00000008)
#define ISO_U0LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define ISO_U0LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U0LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U0LCR_stb_shift                                                          (2)
#define ISO_U0LCR_stb_mask                                                           (0x00000004)
#define ISO_U0LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0LCR_wls_shift                                                          (0)
#define ISO_U0LCR_wls_mask                                                           (0x00000003)
#define ISO_U0LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define ISO_U0LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U0LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U0MCR                                                                    0x18007810
#define ISO_U0MCR_reg_addr                                                           "0xB8007810"
#define ISO_U0MCR_reg                                                                0xB8007810
#define set_ISO_U0MCR_reg(data)   (*((volatile unsigned int*) ISO_U0MCR_reg)=data)
#define get_ISO_U0MCR_reg   (*((volatile unsigned int*) ISO_U0MCR_reg))
#define ISO_U0MCR_inst_adr                                                           "0x0004"
#define ISO_U0MCR_inst                                                               0x0004
#define ISO_U0MCR_afce_shift                                                         (5)
#define ISO_U0MCR_afce_mask                                                          (0x00000020)
#define ISO_U0MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define ISO_U0MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0MCR_loop_shift                                                         (4)
#define ISO_U0MCR_loop_mask                                                          (0x00000010)
#define ISO_U0MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define ISO_U0MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U0MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U0MCR_rts_shift                                                          (1)
#define ISO_U0MCR_rts_mask                                                           (0x00000002)
#define ISO_U0MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define ISO_U0MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0MCR_dtr_shift                                                          (0)
#define ISO_U0MCR_dtr_mask                                                           (0x00000001)
#define ISO_U0MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0LSR                                                                    0x18007814
#define ISO_U0LSR_reg_addr                                                           "0xB8007814"
#define ISO_U0LSR_reg                                                                0xB8007814
#define set_ISO_U0LSR_reg(data)   (*((volatile unsigned int*) ISO_U0LSR_reg)=data)
#define get_ISO_U0LSR_reg   (*((volatile unsigned int*) ISO_U0LSR_reg))
#define ISO_U0LSR_inst_adr                                                           "0x0005"
#define ISO_U0LSR_inst                                                               0x0005
#define ISO_U0LSR_rfe_shift                                                          (7)
#define ISO_U0LSR_rfe_mask                                                           (0x00000080)
#define ISO_U0LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define ISO_U0LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0LSR_temt_shift                                                         (6)
#define ISO_U0LSR_temt_mask                                                          (0x00000040)
#define ISO_U0LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define ISO_U0LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U0LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U0LSR_thre_shift                                                         (5)
#define ISO_U0LSR_thre_mask                                                          (0x00000020)
#define ISO_U0LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define ISO_U0LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U0LSR_bi_shift                                                           (4)
#define ISO_U0LSR_bi_mask                                                            (0x00000010)
#define ISO_U0LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define ISO_U0LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U0LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U0LSR_fe_shift                                                           (3)
#define ISO_U0LSR_fe_mask                                                            (0x00000008)
#define ISO_U0LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define ISO_U0LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U0LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U0LSR_pe_shift                                                           (2)
#define ISO_U0LSR_pe_mask                                                            (0x00000004)
#define ISO_U0LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define ISO_U0LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U0LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U0LSR_oe_shift                                                           (1)
#define ISO_U0LSR_oe_mask                                                            (0x00000002)
#define ISO_U0LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define ISO_U0LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U0LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U0LSR_dr_shift                                                           (0)
#define ISO_U0LSR_dr_mask                                                            (0x00000001)
#define ISO_U0LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define ISO_U0LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U0LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U0MSR                                                                    0x18007818
#define ISO_U0MSR_reg_addr                                                           "0xB8007818"
#define ISO_U0MSR_reg                                                                0xB8007818
#define set_ISO_U0MSR_reg(data)   (*((volatile unsigned int*) ISO_U0MSR_reg)=data)
#define get_ISO_U0MSR_reg   (*((volatile unsigned int*) ISO_U0MSR_reg))
#define ISO_U0MSR_inst_adr                                                           "0x0006"
#define ISO_U0MSR_inst                                                               0x0006
#define ISO_U0MSR_dcd_shift                                                          (7)
#define ISO_U0MSR_dcd_mask                                                           (0x00000080)
#define ISO_U0MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define ISO_U0MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U0MSR_ri_shift                                                           (6)
#define ISO_U0MSR_ri_mask                                                            (0x00000040)
#define ISO_U0MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define ISO_U0MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U0MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U0MSR_dsr_shift                                                          (5)
#define ISO_U0MSR_dsr_mask                                                           (0x00000020)
#define ISO_U0MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define ISO_U0MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U0MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U0MSR_cts_shift                                                          (4)
#define ISO_U0MSR_cts_mask                                                           (0x00000010)
#define ISO_U0MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0MSR_ddcd_shift                                                         (3)
#define ISO_U0MSR_ddcd_mask                                                          (0x00000008)
#define ISO_U0MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define ISO_U0MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0MSR_teri_shift                                                         (2)
#define ISO_U0MSR_teri_mask                                                          (0x00000004)
#define ISO_U0MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define ISO_U0MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U0MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U0MSR_ddsr_shift                                                         (1)
#define ISO_U0MSR_ddsr_mask                                                          (0x00000002)
#define ISO_U0MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define ISO_U0MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0MSR_dcts_shift                                                         (0)
#define ISO_U0MSR_dcts_mask                                                          (0x00000001)
#define ISO_U0MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define ISO_U0MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U0MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U0SCR                                                                    0x1800781C
#define ISO_U0SCR_reg_addr                                                           "0xB800781C"
#define ISO_U0SCR_reg                                                                0xB800781C
#define set_ISO_U0SCR_reg(data)   (*((volatile unsigned int*) ISO_U0SCR_reg)=data)
#define get_ISO_U0SCR_reg   (*((volatile unsigned int*) ISO_U0SCR_reg))
#define ISO_U0SCR_inst_adr                                                           "0x0007"
#define ISO_U0SCR_inst                                                               0x0007
#define ISO_U0SCR_scr_shift                                                          (0)
#define ISO_U0SCR_scr_mask                                                           (0x000000FF)
#define ISO_U0SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0SRBR_0                                                                 0x18007830
#define ISO_U0SRBR_1                                                                 0x18007834
#define ISO_U0SRBR_2                                                                 0x18007838
#define ISO_U0SRBR_3                                                                 0x1800783C
#define ISO_U0SRBR_4                                                                 0x18007840
#define ISO_U0SRBR_5                                                                 0x18007844
#define ISO_U0SRBR_6                                                                 0x18007848
#define ISO_U0SRBR_7                                                                 0x1800784C
#define ISO_U0SRBR_8                                                                 0x18007850
#define ISO_U0SRBR_9                                                                 0x18007854
#define ISO_U0SRBR_10                                                                 0x18007858
#define ISO_U0SRBR_11                                                                 0x1800785C
#define ISO_U0SRBR_12                                                                 0x18007860
#define ISO_U0SRBR_13                                                                 0x18007864
#define ISO_U0SRBR_14                                                                 0x18007868
#define ISO_U0SRBR_15                                                                 0x1800786C
#define ISO_U0SRBR_0_reg_addr                                                        "0xB8007830"
#define ISO_U0SRBR_1_reg_addr                                                        "0xB8007834"
#define ISO_U0SRBR_2_reg_addr                                                        "0xB8007838"
#define ISO_U0SRBR_3_reg_addr                                                        "0xB800783C"
#define ISO_U0SRBR_4_reg_addr                                                        "0xB8007840"
#define ISO_U0SRBR_5_reg_addr                                                        "0xB8007844"
#define ISO_U0SRBR_6_reg_addr                                                        "0xB8007848"
#define ISO_U0SRBR_7_reg_addr                                                        "0xB800784C"
#define ISO_U0SRBR_8_reg_addr                                                        "0xB8007850"
#define ISO_U0SRBR_9_reg_addr                                                        "0xB8007854"
#define ISO_U0SRBR_10_reg_addr                                                        "0xB8007858"
#define ISO_U0SRBR_11_reg_addr                                                        "0xB800785C"
#define ISO_U0SRBR_12_reg_addr                                                        "0xB8007860"
#define ISO_U0SRBR_13_reg_addr                                                        "0xB8007864"
#define ISO_U0SRBR_14_reg_addr                                                        "0xB8007868"
#define ISO_U0SRBR_15_reg_addr                                                        "0xB800786C"
#define ISO_U0SRBR_0_reg                                                             0xB8007830
#define ISO_U0SRBR_1_reg                                                             0xB8007834
#define ISO_U0SRBR_2_reg                                                             0xB8007838
#define ISO_U0SRBR_3_reg                                                             0xB800783C
#define ISO_U0SRBR_4_reg                                                             0xB8007840
#define ISO_U0SRBR_5_reg                                                             0xB8007844
#define ISO_U0SRBR_6_reg                                                             0xB8007848
#define ISO_U0SRBR_7_reg                                                             0xB800784C
#define ISO_U0SRBR_8_reg                                                             0xB8007850
#define ISO_U0SRBR_9_reg                                                             0xB8007854
#define ISO_U0SRBR_10_reg                                                             0xB8007858
#define ISO_U0SRBR_11_reg                                                             0xB800785C
#define ISO_U0SRBR_12_reg                                                             0xB8007860
#define ISO_U0SRBR_13_reg                                                             0xB8007864
#define ISO_U0SRBR_14_reg                                                             0xB8007868
#define ISO_U0SRBR_15_reg                                                             0xB800786C
#define set_ISO_U0SRBR_0_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_0_reg)=data)
#define set_ISO_U0SRBR_1_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_1_reg)=data)
#define set_ISO_U0SRBR_2_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_2_reg)=data)
#define set_ISO_U0SRBR_3_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_3_reg)=data)
#define set_ISO_U0SRBR_4_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_4_reg)=data)
#define set_ISO_U0SRBR_5_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_5_reg)=data)
#define set_ISO_U0SRBR_6_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_6_reg)=data)
#define set_ISO_U0SRBR_7_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_7_reg)=data)
#define set_ISO_U0SRBR_8_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_8_reg)=data)
#define set_ISO_U0SRBR_9_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_9_reg)=data)
#define set_ISO_U0SRBR_10_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_10_reg)=data)
#define set_ISO_U0SRBR_11_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_11_reg)=data)
#define set_ISO_U0SRBR_12_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_12_reg)=data)
#define set_ISO_U0SRBR_13_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_13_reg)=data)
#define set_ISO_U0SRBR_14_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_14_reg)=data)
#define set_ISO_U0SRBR_15_reg(data)   (*((volatile unsigned int*) ISO_U0SRBR_15_reg)=data)
#define get_ISO_U0SRBR_0_reg   (*((volatile unsigned int*) ISO_U0SRBR_0_reg))
#define get_ISO_U0SRBR_1_reg   (*((volatile unsigned int*) ISO_U0SRBR_1_reg))
#define get_ISO_U0SRBR_2_reg   (*((volatile unsigned int*) ISO_U0SRBR_2_reg))
#define get_ISO_U0SRBR_3_reg   (*((volatile unsigned int*) ISO_U0SRBR_3_reg))
#define get_ISO_U0SRBR_4_reg   (*((volatile unsigned int*) ISO_U0SRBR_4_reg))
#define get_ISO_U0SRBR_5_reg   (*((volatile unsigned int*) ISO_U0SRBR_5_reg))
#define get_ISO_U0SRBR_6_reg   (*((volatile unsigned int*) ISO_U0SRBR_6_reg))
#define get_ISO_U0SRBR_7_reg   (*((volatile unsigned int*) ISO_U0SRBR_7_reg))
#define get_ISO_U0SRBR_8_reg   (*((volatile unsigned int*) ISO_U0SRBR_8_reg))
#define get_ISO_U0SRBR_9_reg   (*((volatile unsigned int*) ISO_U0SRBR_9_reg))
#define get_ISO_U0SRBR_10_reg   (*((volatile unsigned int*) ISO_U0SRBR_10_reg))
#define get_ISO_U0SRBR_11_reg   (*((volatile unsigned int*) ISO_U0SRBR_11_reg))
#define get_ISO_U0SRBR_12_reg   (*((volatile unsigned int*) ISO_U0SRBR_12_reg))
#define get_ISO_U0SRBR_13_reg   (*((volatile unsigned int*) ISO_U0SRBR_13_reg))
#define get_ISO_U0SRBR_14_reg   (*((volatile unsigned int*) ISO_U0SRBR_14_reg))
#define get_ISO_U0SRBR_15_reg   (*((volatile unsigned int*) ISO_U0SRBR_15_reg))
#define ISO_U0SRBR_0_inst_adr                                                        "0x000C"
#define ISO_U0SRBR_1_inst_adr                                                        "0x000D"
#define ISO_U0SRBR_2_inst_adr                                                        "0x000E"
#define ISO_U0SRBR_3_inst_adr                                                        "0x000F"
#define ISO_U0SRBR_4_inst_adr                                                        "0x0010"
#define ISO_U0SRBR_5_inst_adr                                                        "0x0011"
#define ISO_U0SRBR_6_inst_adr                                                        "0x0012"
#define ISO_U0SRBR_7_inst_adr                                                        "0x0013"
#define ISO_U0SRBR_8_inst_adr                                                        "0x0014"
#define ISO_U0SRBR_9_inst_adr                                                        "0x0015"
#define ISO_U0SRBR_10_inst_adr                                                        "0x0016"
#define ISO_U0SRBR_11_inst_adr                                                        "0x0017"
#define ISO_U0SRBR_12_inst_adr                                                        "0x0018"
#define ISO_U0SRBR_13_inst_adr                                                        "0x0019"
#define ISO_U0SRBR_14_inst_adr                                                        "0x001A"
#define ISO_U0SRBR_15_inst_adr                                                        "0x001B"
#define ISO_U0SRBR_0_inst                                                            0x000C
#define ISO_U0SRBR_1_inst                                                            0x000D
#define ISO_U0SRBR_2_inst                                                            0x000E
#define ISO_U0SRBR_3_inst                                                            0x000F
#define ISO_U0SRBR_4_inst                                                            0x0010
#define ISO_U0SRBR_5_inst                                                            0x0011
#define ISO_U0SRBR_6_inst                                                            0x0012
#define ISO_U0SRBR_7_inst                                                            0x0013
#define ISO_U0SRBR_8_inst                                                            0x0014
#define ISO_U0SRBR_9_inst                                                            0x0015
#define ISO_U0SRBR_10_inst                                                            0x0016
#define ISO_U0SRBR_11_inst                                                            0x0017
#define ISO_U0SRBR_12_inst                                                            0x0018
#define ISO_U0SRBR_13_inst                                                            0x0019
#define ISO_U0SRBR_14_inst                                                            0x001A
#define ISO_U0SRBR_15_inst                                                            0x001B
#define ISO_U0SRBR_rbd_shift                                                         (0)
#define ISO_U0SRBR_rbd_mask                                                          (0x000000FF)
#define ISO_U0SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U0SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U0SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U0FAR                                                                    0x18007870
#define ISO_U0FAR_reg_addr                                                           "0xB8007870"
#define ISO_U0FAR_reg                                                                0xB8007870
#define set_ISO_U0FAR_reg(data)   (*((volatile unsigned int*) ISO_U0FAR_reg)=data)
#define get_ISO_U0FAR_reg   (*((volatile unsigned int*) ISO_U0FAR_reg))
#define ISO_U0FAR_inst_adr                                                           "0x001C"
#define ISO_U0FAR_inst                                                               0x001C
#define ISO_U0FAR_far_shift                                                          (0)
#define ISO_U0FAR_far_mask                                                           (0x00000001)
#define ISO_U0FAR_far(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0TFR                                                                    0x18007874
#define ISO_U0TFR_reg_addr                                                           "0xB8007874"
#define ISO_U0TFR_reg                                                                0xB8007874
#define set_ISO_U0TFR_reg(data)   (*((volatile unsigned int*) ISO_U0TFR_reg)=data)
#define get_ISO_U0TFR_reg   (*((volatile unsigned int*) ISO_U0TFR_reg))
#define ISO_U0TFR_inst_adr                                                           "0x001D"
#define ISO_U0TFR_inst                                                               0x001D
#define ISO_U0TFR_far_shift                                                          (0)
#define ISO_U0TFR_far_mask                                                           (0x000000FF)
#define ISO_U0TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0RFW                                                                    0x18007878
#define ISO_U0RFW_reg_addr                                                           "0xB8007878"
#define ISO_U0RFW_reg                                                                0xB8007878
#define set_ISO_U0RFW_reg(data)   (*((volatile unsigned int*) ISO_U0RFW_reg)=data)
#define get_ISO_U0RFW_reg   (*((volatile unsigned int*) ISO_U0RFW_reg))
#define ISO_U0RFW_inst_adr                                                           "0x001E"
#define ISO_U0RFW_inst                                                               0x001E
#define ISO_U0RFW_rffe_shift                                                         (9)
#define ISO_U0RFW_rffe_mask                                                          (0x00000200)
#define ISO_U0RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define ISO_U0RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U0RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U0RFW_rfpf_shift                                                         (8)
#define ISO_U0RFW_rfpf_mask                                                          (0x00000100)
#define ISO_U0RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define ISO_U0RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U0RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U0RFW_rfwd_shift                                                         (0)
#define ISO_U0RFW_rfwd_mask                                                          (0x000000FF)
#define ISO_U0RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U0RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U0RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U0USR                                                                    0x1800787C
#define ISO_U0USR_reg_addr                                                           "0xB800787C"
#define ISO_U0USR_reg                                                                0xB800787C
#define set_ISO_U0USR_reg(data)   (*((volatile unsigned int*) ISO_U0USR_reg)=data)
#define get_ISO_U0USR_reg   (*((volatile unsigned int*) ISO_U0USR_reg))
#define ISO_U0USR_inst_adr                                                           "0x001F"
#define ISO_U0USR_inst                                                               0x001F
#define ISO_U0USR_rff_shift                                                          (4)
#define ISO_U0USR_rff_mask                                                           (0x00000010)
#define ISO_U0USR_rff(data)                                                          (0x00000010&((data)<<4))
#define ISO_U0USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U0USR_rfne_shift                                                         (3)
#define ISO_U0USR_rfne_mask                                                          (0x00000008)
#define ISO_U0USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define ISO_U0USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U0USR_tfe_shift                                                          (2)
#define ISO_U0USR_tfe_mask                                                           (0x00000004)
#define ISO_U0USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0USR_tfnf_shift                                                         (1)
#define ISO_U0USR_tfnf_mask                                                          (0x00000002)
#define ISO_U0USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define ISO_U0USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U0USR_busy_shift                                                         (0)
#define ISO_U0USR_busy_mask                                                          (0x00000001)
#define ISO_U0USR_busy(data)                                                         (0x00000001&((data)<<0))
#define ISO_U0USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U0USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U0TFL                                                                    0x18007880
#define ISO_U0TFL_reg_addr                                                           "0xB8007880"
#define ISO_U0TFL_reg                                                                0xB8007880
#define set_ISO_U0TFL_reg(data)   (*((volatile unsigned int*) ISO_U0TFL_reg)=data)
#define get_ISO_U0TFL_reg   (*((volatile unsigned int*) ISO_U0TFL_reg))
#define ISO_U0TFL_inst_adr                                                           "0x0020"
#define ISO_U0TFL_inst                                                               0x0020
#define ISO_U0TFL_tfl_shift                                                          (0)
#define ISO_U0TFL_tfl_mask                                                           (0x000000FF)
#define ISO_U0TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0RFL                                                                    0x18007884
#define ISO_U0RFL_reg_addr                                                           "0xB8007884"
#define ISO_U0RFL_reg                                                                0xB8007884
#define set_ISO_U0RFL_reg(data)   (*((volatile unsigned int*) ISO_U0RFL_reg)=data)
#define get_ISO_U0RFL_reg   (*((volatile unsigned int*) ISO_U0RFL_reg))
#define ISO_U0RFL_inst_adr                                                           "0x0021"
#define ISO_U0RFL_inst                                                               0x0021
#define ISO_U0RFL_rfl_shift                                                          (0)
#define ISO_U0RFL_rfl_mask                                                           (0x000000FF)
#define ISO_U0RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U0RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U0RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U0SRR                                                                    0x18007888
#define ISO_U0SRR_reg_addr                                                           "0xB8007888"
#define ISO_U0SRR_reg                                                                0xB8007888
#define set_ISO_U0SRR_reg(data)   (*((volatile unsigned int*) ISO_U0SRR_reg)=data)
#define get_ISO_U0SRR_reg   (*((volatile unsigned int*) ISO_U0SRR_reg))
#define ISO_U0SRR_inst_adr                                                           "0x0022"
#define ISO_U0SRR_inst                                                               0x0022
#define ISO_U0SRR_xfr_shift                                                          (2)
#define ISO_U0SRR_xfr_mask                                                           (0x00000004)
#define ISO_U0SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define ISO_U0SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U0SRR_rfr_shift                                                          (1)
#define ISO_U0SRR_rfr_mask                                                           (0x00000002)
#define ISO_U0SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define ISO_U0SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U0SRR_ur_shift                                                           (0)
#define ISO_U0SRR_ur_mask                                                            (0x00000001)
#define ISO_U0SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define ISO_U0SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U0SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U0SBCR                                                                   0x18007890
#define ISO_U0SBCR_reg_addr                                                          "0xB8007890"
#define ISO_U0SBCR_reg                                                               0xB8007890
#define set_ISO_U0SBCR_reg(data)   (*((volatile unsigned int*) ISO_U0SBCR_reg)=data)
#define get_ISO_U0SBCR_reg   (*((volatile unsigned int*) ISO_U0SBCR_reg))
#define ISO_U0SBCR_inst_adr                                                          "0x0024"
#define ISO_U0SBCR_inst                                                              0x0024
#define ISO_U0SBCR_sbcr_shift                                                        (0)
#define ISO_U0SBCR_sbcr_mask                                                         (0x00000001)
#define ISO_U0SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define ISO_U0SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_U0SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define ISO_U0SDMAM                                                                  0x18007894
#define ISO_U0SDMAM_reg_addr                                                         "0xB8007894"
#define ISO_U0SDMAM_reg                                                              0xB8007894
#define set_ISO_U0SDMAM_reg(data)   (*((volatile unsigned int*) ISO_U0SDMAM_reg)=data)
#define get_ISO_U0SDMAM_reg   (*((volatile unsigned int*) ISO_U0SDMAM_reg))
#define ISO_U0SDMAM_inst_adr                                                         "0x0025"
#define ISO_U0SDMAM_inst                                                             0x0025
#define ISO_U0SDMAM_sdmam_shift                                                      (0)
#define ISO_U0SDMAM_sdmam_mask                                                       (0x00000001)
#define ISO_U0SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define ISO_U0SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U0SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U0SFE                                                                    0x18007898
#define ISO_U0SFE_reg_addr                                                           "0xB8007898"
#define ISO_U0SFE_reg                                                                0xB8007898
#define set_ISO_U0SFE_reg(data)   (*((volatile unsigned int*) ISO_U0SFE_reg)=data)
#define get_ISO_U0SFE_reg   (*((volatile unsigned int*) ISO_U0SFE_reg))
#define ISO_U0SFE_inst_adr                                                           "0x0026"
#define ISO_U0SFE_inst                                                               0x0026
#define ISO_U0SFE_sfe_shift                                                          (0)
#define ISO_U0SFE_sfe_mask                                                           (0x00000001)
#define ISO_U0SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0SRT                                                                    0x1800789C
#define ISO_U0SRT_reg_addr                                                           "0xB800789C"
#define ISO_U0SRT_reg                                                                0xB800789C
#define set_ISO_U0SRT_reg(data)   (*((volatile unsigned int*) ISO_U0SRT_reg)=data)
#define get_ISO_U0SRT_reg   (*((volatile unsigned int*) ISO_U0SRT_reg))
#define ISO_U0SRT_inst_adr                                                           "0x0027"
#define ISO_U0SRT_inst                                                               0x0027
#define ISO_U0SRT_srt_shift                                                          (0)
#define ISO_U0SRT_srt_mask                                                           (0x00000003)
#define ISO_U0SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define ISO_U0SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U0SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U0STET                                                                   0x180078A0
#define ISO_U0STET_reg_addr                                                          "0xB80078A0"
#define ISO_U0STET_reg                                                               0xB80078A0
#define set_ISO_U0STET_reg(data)   (*((volatile unsigned int*) ISO_U0STET_reg)=data)
#define get_ISO_U0STET_reg   (*((volatile unsigned int*) ISO_U0STET_reg))
#define ISO_U0STET_inst_adr                                                          "0x0028"
#define ISO_U0STET_inst                                                              0x0028
#define ISO_U0STET_stet_shift                                                        (0)
#define ISO_U0STET_stet_mask                                                         (0x00000003)
#define ISO_U0STET_stet(data)                                                        (0x00000003&((data)<<0))
#define ISO_U0STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define ISO_U0STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define ISO_U0HTX                                                                    0x180078A4
#define ISO_U0HTX_reg_addr                                                           "0xB80078A4"
#define ISO_U0HTX_reg                                                                0xB80078A4
#define set_ISO_U0HTX_reg(data)   (*((volatile unsigned int*) ISO_U0HTX_reg)=data)
#define get_ISO_U0HTX_reg   (*((volatile unsigned int*) ISO_U0HTX_reg))
#define ISO_U0HTX_inst_adr                                                           "0x0029"
#define ISO_U0HTX_inst                                                               0x0029
#define ISO_U0HTX_htx_shift                                                          (0)
#define ISO_U0HTX_htx_mask                                                           (0x00000001)
#define ISO_U0HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define ISO_U0HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U0HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U0DMASA                                                                  0x180078A8
#define ISO_U0DMASA_reg_addr                                                         "0xB80078A8"
#define ISO_U0DMASA_reg                                                              0xB80078A8
#define set_ISO_U0DMASA_reg(data)   (*((volatile unsigned int*) ISO_U0DMASA_reg)=data)
#define get_ISO_U0DMASA_reg   (*((volatile unsigned int*) ISO_U0DMASA_reg))
#define ISO_U0DMASA_inst_adr                                                         "0x002A"
#define ISO_U0DMASA_inst                                                             0x002A
#define ISO_U0DMASA_dmasa_shift                                                      (0)
#define ISO_U0DMASA_dmasa_mask                                                       (0x00000001)
#define ISO_U0DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define ISO_U0DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U0DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U0CPR                                                                    0x180078F4
#define ISO_U0CPR_reg_addr                                                           "0xB80078F4"
#define ISO_U0CPR_reg                                                                0xB80078F4
#define set_ISO_U0CPR_reg(data)   (*((volatile unsigned int*) ISO_U0CPR_reg)=data)
#define get_ISO_U0CPR_reg   (*((volatile unsigned int*) ISO_U0CPR_reg))
#define ISO_U0CPR_inst_adr                                                           "0x003D"
#define ISO_U0CPR_inst                                                               0x003D
#define ISO_U0CPR_fifo_mode_shift                                                    (16)
#define ISO_U0CPR_fifo_mode_mask                                                     (0x00FF0000)
#define ISO_U0CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_U0CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U0CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U0CPR_dma_extra_shift                                                    (13)
#define ISO_U0CPR_dma_extra_mask                                                     (0x00002000)
#define ISO_U0CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define ISO_U0CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define ISO_U0CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define ISO_U0CPR_uart_add_encoded_params_shift                                      (12)
#define ISO_U0CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define ISO_U0CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define ISO_U0CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define ISO_U0CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define ISO_U0CPR_shadow_shift                                                       (11)
#define ISO_U0CPR_shadow_mask                                                        (0x00000800)
#define ISO_U0CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define ISO_U0CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U0CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U0CPR_fifo_stat_shift                                                    (10)
#define ISO_U0CPR_fifo_stat_mask                                                     (0x00000400)
#define ISO_U0CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define ISO_U0CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_U0CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define ISO_U0CPR_fifo_access_shift                                                  (9)
#define ISO_U0CPR_fifo_access_mask                                                   (0x00000200)
#define ISO_U0CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define ISO_U0CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_U0CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define ISO_U0CPR_additional_feat_shift                                              (8)
#define ISO_U0CPR_additional_feat_mask                                               (0x00000100)
#define ISO_U0CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define ISO_U0CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_U0CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define ISO_U0CPR_sir_lp_mode_shift                                                  (7)
#define ISO_U0CPR_sir_lp_mode_mask                                                   (0x00000080)
#define ISO_U0CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define ISO_U0CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_U0CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define ISO_U0CPR_sir_mode_shift                                                     (6)
#define ISO_U0CPR_sir_mode_mask                                                      (0x00000040)
#define ISO_U0CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define ISO_U0CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U0CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U0CPR_thre_mode_shift                                                    (5)
#define ISO_U0CPR_thre_mode_mask                                                     (0x00000020)
#define ISO_U0CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define ISO_U0CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define ISO_U0CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define ISO_U0CPR_afce_mode_shift                                                    (4)
#define ISO_U0CPR_afce_mode_mask                                                     (0x00000010)
#define ISO_U0CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define ISO_U0CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_U0CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define ISO_U0CPR_apb_data_width_shift                                               (0)
#define ISO_U0CPR_apb_data_width_mask                                                (0x00000003)
#define ISO_U0CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define ISO_U0CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define ISO_U0CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define ISO_U0UCV                                                                    0x180078F8
#define ISO_U0UCV_reg_addr                                                           "0xB80078F8"
#define ISO_U0UCV_reg                                                                0xB80078F8
#define set_ISO_U0UCV_reg(data)   (*((volatile unsigned int*) ISO_U0UCV_reg)=data)
#define get_ISO_U0UCV_reg   (*((volatile unsigned int*) ISO_U0UCV_reg))
#define ISO_U0UCV_inst_adr                                                           "0x003E"
#define ISO_U0UCV_inst                                                               0x003E
#define ISO_U0UCV_ucv_shift                                                          (0)
#define ISO_U0UCV_ucv_mask                                                           (0xFFFFFFFF)
#define ISO_U0UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U0UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U0UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_U0CTR                                                                    0x180078FC
#define ISO_U0CTR_reg_addr                                                           "0xB80078FC"
#define ISO_U0CTR_reg                                                                0xB80078FC
#define set_ISO_U0CTR_reg(data)   (*((volatile unsigned int*) ISO_U0CTR_reg)=data)
#define get_ISO_U0CTR_reg   (*((volatile unsigned int*) ISO_U0CTR_reg))
#define ISO_U0CTR_inst_adr                                                           "0x003F"
#define ISO_U0CTR_inst                                                               0x003F
#define ISO_U0CTR_ctr_shift                                                          (0)
#define ISO_U0CTR_ctr_mask                                                           (0xFFFFFFFF)
#define ISO_U0CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U0CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U0CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_U1RBR_THR_DLL                                                            0x18007900
#define ISO_U1RBR_THR_DLL_reg_addr                                                   "0xB8007900"
#define ISO_U1RBR_THR_DLL_reg                                                        0xB8007900
#define set_ISO_U1RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) ISO_U1RBR_THR_DLL_reg)=data)
#define get_ISO_U1RBR_THR_DLL_reg   (*((volatile unsigned int*) ISO_U1RBR_THR_DLL_reg))
#define ISO_U1RBR_THR_DLL_inst_adr                                                   "0x0040"
#define ISO_U1RBR_THR_DLL_inst                                                       0x0040
#define ISO_U1RBR_THR_DLL_dll_shift                                                  (0)
#define ISO_U1RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define ISO_U1RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define ISO_U1RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_U1RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define ISO_U1IER_DLH                                                                0x18007904
#define ISO_U1IER_DLH_reg_addr                                                       "0xB8007904"
#define ISO_U1IER_DLH_reg                                                            0xB8007904
#define set_ISO_U1IER_DLH_reg(data)   (*((volatile unsigned int*) ISO_U1IER_DLH_reg)=data)
#define get_ISO_U1IER_DLH_reg   (*((volatile unsigned int*) ISO_U1IER_DLH_reg))
#define ISO_U1IER_DLH_inst_adr                                                       "0x0041"
#define ISO_U1IER_DLH_inst                                                           0x0041
#define ISO_U1IER_DLH_dlh_shift                                                      (0)
#define ISO_U1IER_DLH_dlh_mask                                                       (0x000000FF)
#define ISO_U1IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define ISO_U1IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_U1IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_U1IIR_FCR                                                                0x18007908
#define ISO_U1IIR_FCR_reg_addr                                                       "0xB8007908"
#define ISO_U1IIR_FCR_reg                                                            0xB8007908
#define set_ISO_U1IIR_FCR_reg(data)   (*((volatile unsigned int*) ISO_U1IIR_FCR_reg)=data)
#define get_ISO_U1IIR_FCR_reg   (*((volatile unsigned int*) ISO_U1IIR_FCR_reg))
#define ISO_U1IIR_FCR_inst_adr                                                       "0x0042"
#define ISO_U1IIR_FCR_inst                                                           0x0042
#define ISO_U1IIR_FCR_fifo16_shift                                                   (6)
#define ISO_U1IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define ISO_U1IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define ISO_U1IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U1IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U1IIR_FCR_iid_shift                                                      (0)
#define ISO_U1IIR_FCR_iid_mask                                                       (0x0000000F)
#define ISO_U1IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define ISO_U1IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define ISO_U1IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define ISO_U1LCR                                                                    0x1800790C
#define ISO_U1LCR_reg_addr                                                           "0xB800790C"
#define ISO_U1LCR_reg                                                                0xB800790C
#define set_ISO_U1LCR_reg(data)   (*((volatile unsigned int*) ISO_U1LCR_reg)=data)
#define get_ISO_U1LCR_reg   (*((volatile unsigned int*) ISO_U1LCR_reg))
#define ISO_U1LCR_inst_adr                                                           "0x0043"
#define ISO_U1LCR_inst                                                               0x0043
#define ISO_U1LCR_dlab_shift                                                         (7)
#define ISO_U1LCR_dlab_mask                                                          (0x00000080)
#define ISO_U1LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define ISO_U1LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U1LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U1LCR_brk_shift                                                          (6)
#define ISO_U1LCR_brk_mask                                                           (0x00000040)
#define ISO_U1LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define ISO_U1LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U1LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U1LCR_eps_shift                                                          (4)
#define ISO_U1LCR_eps_mask                                                           (0x00000010)
#define ISO_U1LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define ISO_U1LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U1LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U1LCR_pen_shift                                                          (3)
#define ISO_U1LCR_pen_mask                                                           (0x00000008)
#define ISO_U1LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define ISO_U1LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U1LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U1LCR_stb_shift                                                          (2)
#define ISO_U1LCR_stb_mask                                                           (0x00000004)
#define ISO_U1LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define ISO_U1LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U1LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U1LCR_wls_shift                                                          (0)
#define ISO_U1LCR_wls_mask                                                           (0x00000003)
#define ISO_U1LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define ISO_U1LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U1LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U1MCR                                                                    0x18007910
#define ISO_U1MCR_reg_addr                                                           "0xB8007910"
#define ISO_U1MCR_reg                                                                0xB8007910
#define set_ISO_U1MCR_reg(data)   (*((volatile unsigned int*) ISO_U1MCR_reg)=data)
#define get_ISO_U1MCR_reg   (*((volatile unsigned int*) ISO_U1MCR_reg))
#define ISO_U1MCR_inst_adr                                                           "0x0044"
#define ISO_U1MCR_inst                                                               0x0044
#define ISO_U1MCR_afce_shift                                                         (5)
#define ISO_U1MCR_afce_mask                                                          (0x00000020)
#define ISO_U1MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define ISO_U1MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U1MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U1MCR_loop_shift                                                         (4)
#define ISO_U1MCR_loop_mask                                                          (0x00000010)
#define ISO_U1MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define ISO_U1MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U1MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U1MCR_rts_shift                                                          (1)
#define ISO_U1MCR_rts_mask                                                           (0x00000002)
#define ISO_U1MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define ISO_U1MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U1MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U1MCR_dtr_shift                                                          (0)
#define ISO_U1MCR_dtr_mask                                                           (0x00000001)
#define ISO_U1MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define ISO_U1MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U1MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U1LSR                                                                    0x18007914
#define ISO_U1LSR_reg_addr                                                           "0xB8007914"
#define ISO_U1LSR_reg                                                                0xB8007914
#define set_ISO_U1LSR_reg(data)   (*((volatile unsigned int*) ISO_U1LSR_reg)=data)
#define get_ISO_U1LSR_reg   (*((volatile unsigned int*) ISO_U1LSR_reg))
#define ISO_U1LSR_inst_adr                                                           "0x0045"
#define ISO_U1LSR_inst                                                               0x0045
#define ISO_U1LSR_rfe_shift                                                          (7)
#define ISO_U1LSR_rfe_mask                                                           (0x00000080)
#define ISO_U1LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define ISO_U1LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U1LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U1LSR_temt_shift                                                         (6)
#define ISO_U1LSR_temt_mask                                                          (0x00000040)
#define ISO_U1LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define ISO_U1LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U1LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U1LSR_thre_shift                                                         (5)
#define ISO_U1LSR_thre_mask                                                          (0x00000020)
#define ISO_U1LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define ISO_U1LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U1LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U1LSR_bi_shift                                                           (4)
#define ISO_U1LSR_bi_mask                                                            (0x00000010)
#define ISO_U1LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define ISO_U1LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U1LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U1LSR_fe_shift                                                           (3)
#define ISO_U1LSR_fe_mask                                                            (0x00000008)
#define ISO_U1LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define ISO_U1LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U1LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U1LSR_pe_shift                                                           (2)
#define ISO_U1LSR_pe_mask                                                            (0x00000004)
#define ISO_U1LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define ISO_U1LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U1LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U1LSR_oe_shift                                                           (1)
#define ISO_U1LSR_oe_mask                                                            (0x00000002)
#define ISO_U1LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define ISO_U1LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U1LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U1LSR_dr_shift                                                           (0)
#define ISO_U1LSR_dr_mask                                                            (0x00000001)
#define ISO_U1LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define ISO_U1LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U1LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U1MSR                                                                    0x18007918
#define ISO_U1MSR_reg_addr                                                           "0xB8007918"
#define ISO_U1MSR_reg                                                                0xB8007918
#define set_ISO_U1MSR_reg(data)   (*((volatile unsigned int*) ISO_U1MSR_reg)=data)
#define get_ISO_U1MSR_reg   (*((volatile unsigned int*) ISO_U1MSR_reg))
#define ISO_U1MSR_inst_adr                                                           "0x0046"
#define ISO_U1MSR_inst                                                               0x0046
#define ISO_U1MSR_dcd_shift                                                          (7)
#define ISO_U1MSR_dcd_mask                                                           (0x00000080)
#define ISO_U1MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define ISO_U1MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U1MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U1MSR_ri_shift                                                           (6)
#define ISO_U1MSR_ri_mask                                                            (0x00000040)
#define ISO_U1MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define ISO_U1MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U1MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U1MSR_dsr_shift                                                          (5)
#define ISO_U1MSR_dsr_mask                                                           (0x00000020)
#define ISO_U1MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define ISO_U1MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U1MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U1MSR_cts_shift                                                          (4)
#define ISO_U1MSR_cts_mask                                                           (0x00000010)
#define ISO_U1MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define ISO_U1MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U1MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U1MSR_ddcd_shift                                                         (3)
#define ISO_U1MSR_ddcd_mask                                                          (0x00000008)
#define ISO_U1MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define ISO_U1MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U1MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U1MSR_teri_shift                                                         (2)
#define ISO_U1MSR_teri_mask                                                          (0x00000004)
#define ISO_U1MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define ISO_U1MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U1MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U1MSR_ddsr_shift                                                         (1)
#define ISO_U1MSR_ddsr_mask                                                          (0x00000002)
#define ISO_U1MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define ISO_U1MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U1MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U1MSR_dcts_shift                                                         (0)
#define ISO_U1MSR_dcts_mask                                                          (0x00000001)
#define ISO_U1MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define ISO_U1MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U1MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U1SCR                                                                    0x1800791C
#define ISO_U1SCR_reg_addr                                                           "0xB800791C"
#define ISO_U1SCR_reg                                                                0xB800791C
#define set_ISO_U1SCR_reg(data)   (*((volatile unsigned int*) ISO_U1SCR_reg)=data)
#define get_ISO_U1SCR_reg   (*((volatile unsigned int*) ISO_U1SCR_reg))
#define ISO_U1SCR_inst_adr                                                           "0x0047"
#define ISO_U1SCR_inst                                                               0x0047
#define ISO_U1SCR_scr_shift                                                          (0)
#define ISO_U1SCR_scr_mask                                                           (0x000000FF)
#define ISO_U1SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U1SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U1SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U1SRBR_0                                                                 0x18007930
#define ISO_U1SRBR_1                                                                 0x18007934
#define ISO_U1SRBR_2                                                                 0x18007938
#define ISO_U1SRBR_3                                                                 0x1800793C
#define ISO_U1SRBR_4                                                                 0x18007940
#define ISO_U1SRBR_5                                                                 0x18007944
#define ISO_U1SRBR_6                                                                 0x18007948
#define ISO_U1SRBR_7                                                                 0x1800794C
#define ISO_U1SRBR_8                                                                 0x18007950
#define ISO_U1SRBR_9                                                                 0x18007954
#define ISO_U1SRBR_10                                                                 0x18007958
#define ISO_U1SRBR_11                                                                 0x1800795C
#define ISO_U1SRBR_12                                                                 0x18007960
#define ISO_U1SRBR_13                                                                 0x18007964
#define ISO_U1SRBR_14                                                                 0x18007968
#define ISO_U1SRBR_15                                                                 0x1800796C
#define ISO_U1SRBR_0_reg_addr                                                        "0xB8007930"
#define ISO_U1SRBR_1_reg_addr                                                        "0xB8007934"
#define ISO_U1SRBR_2_reg_addr                                                        "0xB8007938"
#define ISO_U1SRBR_3_reg_addr                                                        "0xB800793C"
#define ISO_U1SRBR_4_reg_addr                                                        "0xB8007940"
#define ISO_U1SRBR_5_reg_addr                                                        "0xB8007944"
#define ISO_U1SRBR_6_reg_addr                                                        "0xB8007948"
#define ISO_U1SRBR_7_reg_addr                                                        "0xB800794C"
#define ISO_U1SRBR_8_reg_addr                                                        "0xB8007950"
#define ISO_U1SRBR_9_reg_addr                                                        "0xB8007954"
#define ISO_U1SRBR_10_reg_addr                                                        "0xB8007958"
#define ISO_U1SRBR_11_reg_addr                                                        "0xB800795C"
#define ISO_U1SRBR_12_reg_addr                                                        "0xB8007960"
#define ISO_U1SRBR_13_reg_addr                                                        "0xB8007964"
#define ISO_U1SRBR_14_reg_addr                                                        "0xB8007968"
#define ISO_U1SRBR_15_reg_addr                                                        "0xB800796C"
#define ISO_U1SRBR_0_reg                                                             0xB8007930
#define ISO_U1SRBR_1_reg                                                             0xB8007934
#define ISO_U1SRBR_2_reg                                                             0xB8007938
#define ISO_U1SRBR_3_reg                                                             0xB800793C
#define ISO_U1SRBR_4_reg                                                             0xB8007940
#define ISO_U1SRBR_5_reg                                                             0xB8007944
#define ISO_U1SRBR_6_reg                                                             0xB8007948
#define ISO_U1SRBR_7_reg                                                             0xB800794C
#define ISO_U1SRBR_8_reg                                                             0xB8007950
#define ISO_U1SRBR_9_reg                                                             0xB8007954
#define ISO_U1SRBR_10_reg                                                             0xB8007958
#define ISO_U1SRBR_11_reg                                                             0xB800795C
#define ISO_U1SRBR_12_reg                                                             0xB8007960
#define ISO_U1SRBR_13_reg                                                             0xB8007964
#define ISO_U1SRBR_14_reg                                                             0xB8007968
#define ISO_U1SRBR_15_reg                                                             0xB800796C
#define set_ISO_U1SRBR_0_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_0_reg)=data)
#define set_ISO_U1SRBR_1_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_1_reg)=data)
#define set_ISO_U1SRBR_2_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_2_reg)=data)
#define set_ISO_U1SRBR_3_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_3_reg)=data)
#define set_ISO_U1SRBR_4_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_4_reg)=data)
#define set_ISO_U1SRBR_5_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_5_reg)=data)
#define set_ISO_U1SRBR_6_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_6_reg)=data)
#define set_ISO_U1SRBR_7_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_7_reg)=data)
#define set_ISO_U1SRBR_8_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_8_reg)=data)
#define set_ISO_U1SRBR_9_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_9_reg)=data)
#define set_ISO_U1SRBR_10_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_10_reg)=data)
#define set_ISO_U1SRBR_11_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_11_reg)=data)
#define set_ISO_U1SRBR_12_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_12_reg)=data)
#define set_ISO_U1SRBR_13_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_13_reg)=data)
#define set_ISO_U1SRBR_14_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_14_reg)=data)
#define set_ISO_U1SRBR_15_reg(data)   (*((volatile unsigned int*) ISO_U1SRBR_15_reg)=data)
#define get_ISO_U1SRBR_0_reg   (*((volatile unsigned int*) ISO_U1SRBR_0_reg))
#define get_ISO_U1SRBR_1_reg   (*((volatile unsigned int*) ISO_U1SRBR_1_reg))
#define get_ISO_U1SRBR_2_reg   (*((volatile unsigned int*) ISO_U1SRBR_2_reg))
#define get_ISO_U1SRBR_3_reg   (*((volatile unsigned int*) ISO_U1SRBR_3_reg))
#define get_ISO_U1SRBR_4_reg   (*((volatile unsigned int*) ISO_U1SRBR_4_reg))
#define get_ISO_U1SRBR_5_reg   (*((volatile unsigned int*) ISO_U1SRBR_5_reg))
#define get_ISO_U1SRBR_6_reg   (*((volatile unsigned int*) ISO_U1SRBR_6_reg))
#define get_ISO_U1SRBR_7_reg   (*((volatile unsigned int*) ISO_U1SRBR_7_reg))
#define get_ISO_U1SRBR_8_reg   (*((volatile unsigned int*) ISO_U1SRBR_8_reg))
#define get_ISO_U1SRBR_9_reg   (*((volatile unsigned int*) ISO_U1SRBR_9_reg))
#define get_ISO_U1SRBR_10_reg   (*((volatile unsigned int*) ISO_U1SRBR_10_reg))
#define get_ISO_U1SRBR_11_reg   (*((volatile unsigned int*) ISO_U1SRBR_11_reg))
#define get_ISO_U1SRBR_12_reg   (*((volatile unsigned int*) ISO_U1SRBR_12_reg))
#define get_ISO_U1SRBR_13_reg   (*((volatile unsigned int*) ISO_U1SRBR_13_reg))
#define get_ISO_U1SRBR_14_reg   (*((volatile unsigned int*) ISO_U1SRBR_14_reg))
#define get_ISO_U1SRBR_15_reg   (*((volatile unsigned int*) ISO_U1SRBR_15_reg))
#define ISO_U1SRBR_0_inst_adr                                                        "0x004C"
#define ISO_U1SRBR_1_inst_adr                                                        "0x004D"
#define ISO_U1SRBR_2_inst_adr                                                        "0x004E"
#define ISO_U1SRBR_3_inst_adr                                                        "0x004F"
#define ISO_U1SRBR_4_inst_adr                                                        "0x0050"
#define ISO_U1SRBR_5_inst_adr                                                        "0x0051"
#define ISO_U1SRBR_6_inst_adr                                                        "0x0052"
#define ISO_U1SRBR_7_inst_adr                                                        "0x0053"
#define ISO_U1SRBR_8_inst_adr                                                        "0x0054"
#define ISO_U1SRBR_9_inst_adr                                                        "0x0055"
#define ISO_U1SRBR_10_inst_adr                                                        "0x0056"
#define ISO_U1SRBR_11_inst_adr                                                        "0x0057"
#define ISO_U1SRBR_12_inst_adr                                                        "0x0058"
#define ISO_U1SRBR_13_inst_adr                                                        "0x0059"
#define ISO_U1SRBR_14_inst_adr                                                        "0x005A"
#define ISO_U1SRBR_15_inst_adr                                                        "0x005B"
#define ISO_U1SRBR_0_inst                                                            0x004C
#define ISO_U1SRBR_1_inst                                                            0x004D
#define ISO_U1SRBR_2_inst                                                            0x004E
#define ISO_U1SRBR_3_inst                                                            0x004F
#define ISO_U1SRBR_4_inst                                                            0x0050
#define ISO_U1SRBR_5_inst                                                            0x0051
#define ISO_U1SRBR_6_inst                                                            0x0052
#define ISO_U1SRBR_7_inst                                                            0x0053
#define ISO_U1SRBR_8_inst                                                            0x0054
#define ISO_U1SRBR_9_inst                                                            0x0055
#define ISO_U1SRBR_10_inst                                                            0x0056
#define ISO_U1SRBR_11_inst                                                            0x0057
#define ISO_U1SRBR_12_inst                                                            0x0058
#define ISO_U1SRBR_13_inst                                                            0x0059
#define ISO_U1SRBR_14_inst                                                            0x005A
#define ISO_U1SRBR_15_inst                                                            0x005B
#define ISO_U1SRBR_rbd_shift                                                         (0)
#define ISO_U1SRBR_rbd_mask                                                          (0x000000FF)
#define ISO_U1SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U1SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U1SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U1FAR                                                                    0x18007970
#define ISO_U1FAR_reg_addr                                                           "0xB8007970"
#define ISO_U1FAR_reg                                                                0xB8007970
#define set_ISO_U1FAR_reg(data)   (*((volatile unsigned int*) ISO_U1FAR_reg)=data)
#define get_ISO_U1FAR_reg   (*((volatile unsigned int*) ISO_U1FAR_reg))
#define ISO_U1FAR_inst_adr                                                           "0x005C"
#define ISO_U1FAR_inst                                                               0x005C
#define ISO_U1FAR_far_shift                                                          (0)
#define ISO_U1FAR_far_mask                                                           (0x00000001)
#define ISO_U1FAR_far(data)                                                          (0x00000001&((data)<<0))
#define ISO_U1FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U1FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U1TFR                                                                    0x18007974
#define ISO_U1TFR_reg_addr                                                           "0xB8007974"
#define ISO_U1TFR_reg                                                                0xB8007974
#define set_ISO_U1TFR_reg(data)   (*((volatile unsigned int*) ISO_U1TFR_reg)=data)
#define get_ISO_U1TFR_reg   (*((volatile unsigned int*) ISO_U1TFR_reg))
#define ISO_U1TFR_inst_adr                                                           "0x005D"
#define ISO_U1TFR_inst                                                               0x005D
#define ISO_U1TFR_far_shift                                                          (0)
#define ISO_U1TFR_far_mask                                                           (0x000000FF)
#define ISO_U1TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U1TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U1TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U1RFW                                                                    0x18007978
#define ISO_U1RFW_reg_addr                                                           "0xB8007978"
#define ISO_U1RFW_reg                                                                0xB8007978
#define set_ISO_U1RFW_reg(data)   (*((volatile unsigned int*) ISO_U1RFW_reg)=data)
#define get_ISO_U1RFW_reg   (*((volatile unsigned int*) ISO_U1RFW_reg))
#define ISO_U1RFW_inst_adr                                                           "0x005E"
#define ISO_U1RFW_inst                                                               0x005E
#define ISO_U1RFW_rffe_shift                                                         (9)
#define ISO_U1RFW_rffe_mask                                                          (0x00000200)
#define ISO_U1RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define ISO_U1RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U1RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U1RFW_rfpf_shift                                                         (8)
#define ISO_U1RFW_rfpf_mask                                                          (0x00000100)
#define ISO_U1RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define ISO_U1RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U1RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U1RFW_rfwd_shift                                                         (0)
#define ISO_U1RFW_rfwd_mask                                                          (0x000000FF)
#define ISO_U1RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U1RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U1RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U1USR                                                                    0x1800797C
#define ISO_U1USR_reg_addr                                                           "0xB800797C"
#define ISO_U1USR_reg                                                                0xB800797C
#define set_ISO_U1USR_reg(data)   (*((volatile unsigned int*) ISO_U1USR_reg)=data)
#define get_ISO_U1USR_reg   (*((volatile unsigned int*) ISO_U1USR_reg))
#define ISO_U1USR_inst_adr                                                           "0x005F"
#define ISO_U1USR_inst                                                               0x005F
#define ISO_U1USR_rff_shift                                                          (4)
#define ISO_U1USR_rff_mask                                                           (0x00000010)
#define ISO_U1USR_rff(data)                                                          (0x00000010&((data)<<4))
#define ISO_U1USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U1USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U1USR_rfne_shift                                                         (3)
#define ISO_U1USR_rfne_mask                                                          (0x00000008)
#define ISO_U1USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define ISO_U1USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U1USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U1USR_tfe_shift                                                          (2)
#define ISO_U1USR_tfe_mask                                                           (0x00000004)
#define ISO_U1USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define ISO_U1USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U1USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U1USR_tfnf_shift                                                         (1)
#define ISO_U1USR_tfnf_mask                                                          (0x00000002)
#define ISO_U1USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define ISO_U1USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U1USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U1USR_busy_shift                                                         (0)
#define ISO_U1USR_busy_mask                                                          (0x00000001)
#define ISO_U1USR_busy(data)                                                         (0x00000001&((data)<<0))
#define ISO_U1USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U1USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U1TFL                                                                    0x18007980
#define ISO_U1TFL_reg_addr                                                           "0xB8007980"
#define ISO_U1TFL_reg                                                                0xB8007980
#define set_ISO_U1TFL_reg(data)   (*((volatile unsigned int*) ISO_U1TFL_reg)=data)
#define get_ISO_U1TFL_reg   (*((volatile unsigned int*) ISO_U1TFL_reg))
#define ISO_U1TFL_inst_adr                                                           "0x0060"
#define ISO_U1TFL_inst                                                               0x0060
#define ISO_U1TFL_tfl_shift                                                          (0)
#define ISO_U1TFL_tfl_mask                                                           (0x000000FF)
#define ISO_U1TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U1TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U1TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U1RFL                                                                    0x18007984
#define ISO_U1RFL_reg_addr                                                           "0xB8007984"
#define ISO_U1RFL_reg                                                                0xB8007984
#define set_ISO_U1RFL_reg(data)   (*((volatile unsigned int*) ISO_U1RFL_reg)=data)
#define get_ISO_U1RFL_reg   (*((volatile unsigned int*) ISO_U1RFL_reg))
#define ISO_U1RFL_inst_adr                                                           "0x0061"
#define ISO_U1RFL_inst                                                               0x0061
#define ISO_U1RFL_rfl_shift                                                          (0)
#define ISO_U1RFL_rfl_mask                                                           (0x000000FF)
#define ISO_U1RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U1RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U1RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U1SRR                                                                    0x18007988
#define ISO_U1SRR_reg_addr                                                           "0xB8007988"
#define ISO_U1SRR_reg                                                                0xB8007988
#define set_ISO_U1SRR_reg(data)   (*((volatile unsigned int*) ISO_U1SRR_reg)=data)
#define get_ISO_U1SRR_reg   (*((volatile unsigned int*) ISO_U1SRR_reg))
#define ISO_U1SRR_inst_adr                                                           "0x0062"
#define ISO_U1SRR_inst                                                               0x0062
#define ISO_U1SRR_xfr_shift                                                          (2)
#define ISO_U1SRR_xfr_mask                                                           (0x00000004)
#define ISO_U1SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define ISO_U1SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U1SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U1SRR_rfr_shift                                                          (1)
#define ISO_U1SRR_rfr_mask                                                           (0x00000002)
#define ISO_U1SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define ISO_U1SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U1SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U1SRR_ur_shift                                                           (0)
#define ISO_U1SRR_ur_mask                                                            (0x00000001)
#define ISO_U1SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define ISO_U1SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U1SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U1SBCR                                                                   0x18007990
#define ISO_U1SBCR_reg_addr                                                          "0xB8007990"
#define ISO_U1SBCR_reg                                                               0xB8007990
#define set_ISO_U1SBCR_reg(data)   (*((volatile unsigned int*) ISO_U1SBCR_reg)=data)
#define get_ISO_U1SBCR_reg   (*((volatile unsigned int*) ISO_U1SBCR_reg))
#define ISO_U1SBCR_inst_adr                                                          "0x0064"
#define ISO_U1SBCR_inst                                                              0x0064
#define ISO_U1SBCR_sbcr_shift                                                        (0)
#define ISO_U1SBCR_sbcr_mask                                                         (0x00000001)
#define ISO_U1SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define ISO_U1SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_U1SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define ISO_U1SDMAM                                                                  0x18007994
#define ISO_U1SDMAM_reg_addr                                                         "0xB8007994"
#define ISO_U1SDMAM_reg                                                              0xB8007994
#define set_ISO_U1SDMAM_reg(data)   (*((volatile unsigned int*) ISO_U1SDMAM_reg)=data)
#define get_ISO_U1SDMAM_reg   (*((volatile unsigned int*) ISO_U1SDMAM_reg))
#define ISO_U1SDMAM_inst_adr                                                         "0x0065"
#define ISO_U1SDMAM_inst                                                             0x0065
#define ISO_U1SDMAM_sdmam_shift                                                      (0)
#define ISO_U1SDMAM_sdmam_mask                                                       (0x00000001)
#define ISO_U1SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define ISO_U1SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U1SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U1SFE                                                                    0x18007998
#define ISO_U1SFE_reg_addr                                                           "0xB8007998"
#define ISO_U1SFE_reg                                                                0xB8007998
#define set_ISO_U1SFE_reg(data)   (*((volatile unsigned int*) ISO_U1SFE_reg)=data)
#define get_ISO_U1SFE_reg   (*((volatile unsigned int*) ISO_U1SFE_reg))
#define ISO_U1SFE_inst_adr                                                           "0x0066"
#define ISO_U1SFE_inst                                                               0x0066
#define ISO_U1SFE_sfe_shift                                                          (0)
#define ISO_U1SFE_sfe_mask                                                           (0x00000001)
#define ISO_U1SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define ISO_U1SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U1SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U1SRT                                                                    0x1800799C
#define ISO_U1SRT_reg_addr                                                           "0xB800799C"
#define ISO_U1SRT_reg                                                                0xB800799C
#define set_ISO_U1SRT_reg(data)   (*((volatile unsigned int*) ISO_U1SRT_reg)=data)
#define get_ISO_U1SRT_reg   (*((volatile unsigned int*) ISO_U1SRT_reg))
#define ISO_U1SRT_inst_adr                                                           "0x0067"
#define ISO_U1SRT_inst                                                               0x0067
#define ISO_U1SRT_srt_shift                                                          (0)
#define ISO_U1SRT_srt_mask                                                           (0x00000003)
#define ISO_U1SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define ISO_U1SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U1SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U1STET                                                                   0x180079A0
#define ISO_U1STET_reg_addr                                                          "0xB80079A0"
#define ISO_U1STET_reg                                                               0xB80079A0
#define set_ISO_U1STET_reg(data)   (*((volatile unsigned int*) ISO_U1STET_reg)=data)
#define get_ISO_U1STET_reg   (*((volatile unsigned int*) ISO_U1STET_reg))
#define ISO_U1STET_inst_adr                                                          "0x0068"
#define ISO_U1STET_inst                                                              0x0068
#define ISO_U1STET_stet_shift                                                        (0)
#define ISO_U1STET_stet_mask                                                         (0x00000003)
#define ISO_U1STET_stet(data)                                                        (0x00000003&((data)<<0))
#define ISO_U1STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define ISO_U1STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define ISO_U1HTX                                                                    0x180079A4
#define ISO_U1HTX_reg_addr                                                           "0xB80079A4"
#define ISO_U1HTX_reg                                                                0xB80079A4
#define set_ISO_U1HTX_reg(data)   (*((volatile unsigned int*) ISO_U1HTX_reg)=data)
#define get_ISO_U1HTX_reg   (*((volatile unsigned int*) ISO_U1HTX_reg))
#define ISO_U1HTX_inst_adr                                                           "0x0069"
#define ISO_U1HTX_inst                                                               0x0069
#define ISO_U1HTX_htx_shift                                                          (0)
#define ISO_U1HTX_htx_mask                                                           (0x00000001)
#define ISO_U1HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define ISO_U1HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U1HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U1DMASA                                                                  0x180079A8
#define ISO_U1DMASA_reg_addr                                                         "0xB80079A8"
#define ISO_U1DMASA_reg                                                              0xB80079A8
#define set_ISO_U1DMASA_reg(data)   (*((volatile unsigned int*) ISO_U1DMASA_reg)=data)
#define get_ISO_U1DMASA_reg   (*((volatile unsigned int*) ISO_U1DMASA_reg))
#define ISO_U1DMASA_inst_adr                                                         "0x006A"
#define ISO_U1DMASA_inst                                                             0x006A
#define ISO_U1DMASA_dmasa_shift                                                      (0)
#define ISO_U1DMASA_dmasa_mask                                                       (0x00000001)
#define ISO_U1DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define ISO_U1DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U1DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U1CPR                                                                    0x180079F4
#define ISO_U1CPR_reg_addr                                                           "0xB80079F4"
#define ISO_U1CPR_reg                                                                0xB80079F4
#define set_ISO_U1CPR_reg(data)   (*((volatile unsigned int*) ISO_U1CPR_reg)=data)
#define get_ISO_U1CPR_reg   (*((volatile unsigned int*) ISO_U1CPR_reg))
#define ISO_U1CPR_inst_adr                                                           "0x007D"
#define ISO_U1CPR_inst                                                               0x007D
#define ISO_U1CPR_fifo_mode_shift                                                    (16)
#define ISO_U1CPR_fifo_mode_mask                                                     (0x00FF0000)
#define ISO_U1CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_U1CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U1CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U1CPR_dma_extra_shift                                                    (13)
#define ISO_U1CPR_dma_extra_mask                                                     (0x00002000)
#define ISO_U1CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define ISO_U1CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define ISO_U1CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define ISO_U1CPR_uart_add_encoded_params_shift                                      (12)
#define ISO_U1CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define ISO_U1CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define ISO_U1CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define ISO_U1CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define ISO_U1CPR_shadow_shift                                                       (11)
#define ISO_U1CPR_shadow_mask                                                        (0x00000800)
#define ISO_U1CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define ISO_U1CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U1CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U1CPR_fifo_stat_shift                                                    (10)
#define ISO_U1CPR_fifo_stat_mask                                                     (0x00000400)
#define ISO_U1CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define ISO_U1CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_U1CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define ISO_U1CPR_fifo_access_shift                                                  (9)
#define ISO_U1CPR_fifo_access_mask                                                   (0x00000200)
#define ISO_U1CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define ISO_U1CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_U1CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define ISO_U1CPR_additional_feat_shift                                              (8)
#define ISO_U1CPR_additional_feat_mask                                               (0x00000100)
#define ISO_U1CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define ISO_U1CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_U1CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define ISO_U1CPR_sir_lp_mode_shift                                                  (7)
#define ISO_U1CPR_sir_lp_mode_mask                                                   (0x00000080)
#define ISO_U1CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define ISO_U1CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_U1CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define ISO_U1CPR_sir_mode_shift                                                     (6)
#define ISO_U1CPR_sir_mode_mask                                                      (0x00000040)
#define ISO_U1CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define ISO_U1CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U1CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U1CPR_thre_mode_shift                                                    (5)
#define ISO_U1CPR_thre_mode_mask                                                     (0x00000020)
#define ISO_U1CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define ISO_U1CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define ISO_U1CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define ISO_U1CPR_afce_mode_shift                                                    (4)
#define ISO_U1CPR_afce_mode_mask                                                     (0x00000010)
#define ISO_U1CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define ISO_U1CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_U1CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define ISO_U1CPR_apb_data_width_shift                                               (0)
#define ISO_U1CPR_apb_data_width_mask                                                (0x00000003)
#define ISO_U1CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define ISO_U1CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define ISO_U1CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define ISO_U1UCV                                                                    0x180079F8
#define ISO_U1UCV_reg_addr                                                           "0xB80079F8"
#define ISO_U1UCV_reg                                                                0xB80079F8
#define set_ISO_U1UCV_reg(data)   (*((volatile unsigned int*) ISO_U1UCV_reg)=data)
#define get_ISO_U1UCV_reg   (*((volatile unsigned int*) ISO_U1UCV_reg))
#define ISO_U1UCV_inst_adr                                                           "0x007E"
#define ISO_U1UCV_inst                                                               0x007E
#define ISO_U1UCV_ucv_shift                                                          (0)
#define ISO_U1UCV_ucv_mask                                                           (0xFFFFFFFF)
#define ISO_U1UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U1UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U1UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_U1CTR                                                                    0x180079FC
#define ISO_U1CTR_reg_addr                                                           "0xB80079FC"
#define ISO_U1CTR_reg                                                                0xB80079FC
#define set_ISO_U1CTR_reg(data)   (*((volatile unsigned int*) ISO_U1CTR_reg)=data)
#define get_ISO_U1CTR_reg   (*((volatile unsigned int*) ISO_U1CTR_reg))
#define ISO_U1CTR_inst_adr                                                           "0x007F"
#define ISO_U1CTR_inst                                                               0x007F
#define ISO_U1CTR_ctr_shift                                                          (0)
#define ISO_U1CTR_ctr_mask                                                           (0xFFFFFFFF)
#define ISO_U1CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U1CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U1CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_U2RBR_THR_DLL                                                            0x18007A00
#define ISO_U2RBR_THR_DLL_reg_addr                                                   "0xB8007A00"
#define ISO_U2RBR_THR_DLL_reg                                                        0xB8007A00
#define set_ISO_U2RBR_THR_DLL_reg(data)   (*((volatile unsigned int*) ISO_U2RBR_THR_DLL_reg)=data)
#define get_ISO_U2RBR_THR_DLL_reg   (*((volatile unsigned int*) ISO_U2RBR_THR_DLL_reg))
#define ISO_U2RBR_THR_DLL_inst_adr                                                   "0x0080"
#define ISO_U2RBR_THR_DLL_inst                                                       0x0080
#define ISO_U2RBR_THR_DLL_dll_shift                                                  (0)
#define ISO_U2RBR_THR_DLL_dll_mask                                                   (0x000000FF)
#define ISO_U2RBR_THR_DLL_dll(data)                                                  (0x000000FF&((data)<<0))
#define ISO_U2RBR_THR_DLL_dll_src(data)                                              ((0x000000FF&(data))>>0)
#define ISO_U2RBR_THR_DLL_get_dll(data)                                              ((0x000000FF&(data))>>0)


#define ISO_U2IER_DLH                                                                0x18007A04
#define ISO_U2IER_DLH_reg_addr                                                       "0xB8007A04"
#define ISO_U2IER_DLH_reg                                                            0xB8007A04
#define set_ISO_U2IER_DLH_reg(data)   (*((volatile unsigned int*) ISO_U2IER_DLH_reg)=data)
#define get_ISO_U2IER_DLH_reg   (*((volatile unsigned int*) ISO_U2IER_DLH_reg))
#define ISO_U2IER_DLH_inst_adr                                                       "0x0081"
#define ISO_U2IER_DLH_inst                                                           0x0081
#define ISO_U2IER_DLH_dlh_shift                                                      (0)
#define ISO_U2IER_DLH_dlh_mask                                                       (0x000000FF)
#define ISO_U2IER_DLH_dlh(data)                                                      (0x000000FF&((data)<<0))
#define ISO_U2IER_DLH_dlh_src(data)                                                  ((0x000000FF&(data))>>0)
#define ISO_U2IER_DLH_get_dlh(data)                                                  ((0x000000FF&(data))>>0)


#define ISO_U2IIR_FCR                                                                0x18007A08
#define ISO_U2IIR_FCR_reg_addr                                                       "0xB8007A08"
#define ISO_U2IIR_FCR_reg                                                            0xB8007A08
#define set_ISO_U2IIR_FCR_reg(data)   (*((volatile unsigned int*) ISO_U2IIR_FCR_reg)=data)
#define get_ISO_U2IIR_FCR_reg   (*((volatile unsigned int*) ISO_U2IIR_FCR_reg))
#define ISO_U2IIR_FCR_inst_adr                                                       "0x0082"
#define ISO_U2IIR_FCR_inst                                                           0x0082
#define ISO_U2IIR_FCR_fifo16_shift                                                   (6)
#define ISO_U2IIR_FCR_fifo16_mask                                                    (0x000000C0)
#define ISO_U2IIR_FCR_fifo16(data)                                                   (0x000000C0&((data)<<6))
#define ISO_U2IIR_FCR_fifo16_src(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U2IIR_FCR_get_fifo16(data)                                               ((0x000000C0&(data))>>6)
#define ISO_U2IIR_FCR_iid_shift                                                      (0)
#define ISO_U2IIR_FCR_iid_mask                                                       (0x0000000F)
#define ISO_U2IIR_FCR_iid(data)                                                      (0x0000000F&((data)<<0))
#define ISO_U2IIR_FCR_iid_src(data)                                                  ((0x0000000F&(data))>>0)
#define ISO_U2IIR_FCR_get_iid(data)                                                  ((0x0000000F&(data))>>0)


#define ISO_U2LCR                                                                    0x18007A0C
#define ISO_U2LCR_reg_addr                                                           "0xB8007A0C"
#define ISO_U2LCR_reg                                                                0xB8007A0C
#define set_ISO_U2LCR_reg(data)   (*((volatile unsigned int*) ISO_U2LCR_reg)=data)
#define get_ISO_U2LCR_reg   (*((volatile unsigned int*) ISO_U2LCR_reg))
#define ISO_U2LCR_inst_adr                                                           "0x0083"
#define ISO_U2LCR_inst                                                               0x0083
#define ISO_U2LCR_dlab_shift                                                         (7)
#define ISO_U2LCR_dlab_mask                                                          (0x00000080)
#define ISO_U2LCR_dlab(data)                                                         (0x00000080&((data)<<7))
#define ISO_U2LCR_dlab_src(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U2LCR_get_dlab(data)                                                     ((0x00000080&(data))>>7)
#define ISO_U2LCR_brk_shift                                                          (6)
#define ISO_U2LCR_brk_mask                                                           (0x00000040)
#define ISO_U2LCR_brk(data)                                                          (0x00000040&((data)<<6))
#define ISO_U2LCR_brk_src(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U2LCR_get_brk(data)                                                      ((0x00000040&(data))>>6)
#define ISO_U2LCR_eps_shift                                                          (4)
#define ISO_U2LCR_eps_mask                                                           (0x00000010)
#define ISO_U2LCR_eps(data)                                                          (0x00000010&((data)<<4))
#define ISO_U2LCR_eps_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U2LCR_get_eps(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U2LCR_pen_shift                                                          (3)
#define ISO_U2LCR_pen_mask                                                           (0x00000008)
#define ISO_U2LCR_pen(data)                                                          (0x00000008&((data)<<3))
#define ISO_U2LCR_pen_src(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U2LCR_get_pen(data)                                                      ((0x00000008&(data))>>3)
#define ISO_U2LCR_stb_shift                                                          (2)
#define ISO_U2LCR_stb_mask                                                           (0x00000004)
#define ISO_U2LCR_stb(data)                                                          (0x00000004&((data)<<2))
#define ISO_U2LCR_stb_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U2LCR_get_stb(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U2LCR_wls_shift                                                          (0)
#define ISO_U2LCR_wls_mask                                                           (0x00000003)
#define ISO_U2LCR_wls(data)                                                          (0x00000003&((data)<<0))
#define ISO_U2LCR_wls_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U2LCR_get_wls(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U2MCR                                                                    0x18007A10
#define ISO_U2MCR_reg_addr                                                           "0xB8007A10"
#define ISO_U2MCR_reg                                                                0xB8007A10
#define set_ISO_U2MCR_reg(data)   (*((volatile unsigned int*) ISO_U2MCR_reg)=data)
#define get_ISO_U2MCR_reg   (*((volatile unsigned int*) ISO_U2MCR_reg))
#define ISO_U2MCR_inst_adr                                                           "0x0084"
#define ISO_U2MCR_inst                                                               0x0084
#define ISO_U2MCR_afce_shift                                                         (5)
#define ISO_U2MCR_afce_mask                                                          (0x00000020)
#define ISO_U2MCR_afce(data)                                                         (0x00000020&((data)<<5))
#define ISO_U2MCR_afce_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U2MCR_get_afce(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U2MCR_loop_shift                                                         (4)
#define ISO_U2MCR_loop_mask                                                          (0x00000010)
#define ISO_U2MCR_loop(data)                                                         (0x00000010&((data)<<4))
#define ISO_U2MCR_loop_src(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U2MCR_get_loop(data)                                                     ((0x00000010&(data))>>4)
#define ISO_U2MCR_rts_shift                                                          (1)
#define ISO_U2MCR_rts_mask                                                           (0x00000002)
#define ISO_U2MCR_rts(data)                                                          (0x00000002&((data)<<1))
#define ISO_U2MCR_rts_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U2MCR_get_rts(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U2MCR_dtr_shift                                                          (0)
#define ISO_U2MCR_dtr_mask                                                           (0x00000001)
#define ISO_U2MCR_dtr(data)                                                          (0x00000001&((data)<<0))
#define ISO_U2MCR_dtr_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U2MCR_get_dtr(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U2LSR                                                                    0x18007A14
#define ISO_U2LSR_reg_addr                                                           "0xB8007A14"
#define ISO_U2LSR_reg                                                                0xB8007A14
#define set_ISO_U2LSR_reg(data)   (*((volatile unsigned int*) ISO_U2LSR_reg)=data)
#define get_ISO_U2LSR_reg   (*((volatile unsigned int*) ISO_U2LSR_reg))
#define ISO_U2LSR_inst_adr                                                           "0x0085"
#define ISO_U2LSR_inst                                                               0x0085
#define ISO_U2LSR_rfe_shift                                                          (7)
#define ISO_U2LSR_rfe_mask                                                           (0x00000080)
#define ISO_U2LSR_rfe(data)                                                          (0x00000080&((data)<<7))
#define ISO_U2LSR_rfe_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U2LSR_get_rfe(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U2LSR_temt_shift                                                         (6)
#define ISO_U2LSR_temt_mask                                                          (0x00000040)
#define ISO_U2LSR_temt(data)                                                         (0x00000040&((data)<<6))
#define ISO_U2LSR_temt_src(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U2LSR_get_temt(data)                                                     ((0x00000040&(data))>>6)
#define ISO_U2LSR_thre_shift                                                         (5)
#define ISO_U2LSR_thre_mask                                                          (0x00000020)
#define ISO_U2LSR_thre(data)                                                         (0x00000020&((data)<<5))
#define ISO_U2LSR_thre_src(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U2LSR_get_thre(data)                                                     ((0x00000020&(data))>>5)
#define ISO_U2LSR_bi_shift                                                           (4)
#define ISO_U2LSR_bi_mask                                                            (0x00000010)
#define ISO_U2LSR_bi(data)                                                           (0x00000010&((data)<<4))
#define ISO_U2LSR_bi_src(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U2LSR_get_bi(data)                                                       ((0x00000010&(data))>>4)
#define ISO_U2LSR_fe_shift                                                           (3)
#define ISO_U2LSR_fe_mask                                                            (0x00000008)
#define ISO_U2LSR_fe(data)                                                           (0x00000008&((data)<<3))
#define ISO_U2LSR_fe_src(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U2LSR_get_fe(data)                                                       ((0x00000008&(data))>>3)
#define ISO_U2LSR_pe_shift                                                           (2)
#define ISO_U2LSR_pe_mask                                                            (0x00000004)
#define ISO_U2LSR_pe(data)                                                           (0x00000004&((data)<<2))
#define ISO_U2LSR_pe_src(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U2LSR_get_pe(data)                                                       ((0x00000004&(data))>>2)
#define ISO_U2LSR_oe_shift                                                           (1)
#define ISO_U2LSR_oe_mask                                                            (0x00000002)
#define ISO_U2LSR_oe(data)                                                           (0x00000002&((data)<<1))
#define ISO_U2LSR_oe_src(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U2LSR_get_oe(data)                                                       ((0x00000002&(data))>>1)
#define ISO_U2LSR_dr_shift                                                           (0)
#define ISO_U2LSR_dr_mask                                                            (0x00000001)
#define ISO_U2LSR_dr(data)                                                           (0x00000001&((data)<<0))
#define ISO_U2LSR_dr_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U2LSR_get_dr(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U2MSR                                                                    0x18007A18
#define ISO_U2MSR_reg_addr                                                           "0xB8007A18"
#define ISO_U2MSR_reg                                                                0xB8007A18
#define set_ISO_U2MSR_reg(data)   (*((volatile unsigned int*) ISO_U2MSR_reg)=data)
#define get_ISO_U2MSR_reg   (*((volatile unsigned int*) ISO_U2MSR_reg))
#define ISO_U2MSR_inst_adr                                                           "0x0086"
#define ISO_U2MSR_inst                                                               0x0086
#define ISO_U2MSR_dcd_shift                                                          (7)
#define ISO_U2MSR_dcd_mask                                                           (0x00000080)
#define ISO_U2MSR_dcd(data)                                                          (0x00000080&((data)<<7))
#define ISO_U2MSR_dcd_src(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U2MSR_get_dcd(data)                                                      ((0x00000080&(data))>>7)
#define ISO_U2MSR_ri_shift                                                           (6)
#define ISO_U2MSR_ri_mask                                                            (0x00000040)
#define ISO_U2MSR_ri(data)                                                           (0x00000040&((data)<<6))
#define ISO_U2MSR_ri_src(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U2MSR_get_ri(data)                                                       ((0x00000040&(data))>>6)
#define ISO_U2MSR_dsr_shift                                                          (5)
#define ISO_U2MSR_dsr_mask                                                           (0x00000020)
#define ISO_U2MSR_dsr(data)                                                          (0x00000020&((data)<<5))
#define ISO_U2MSR_dsr_src(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U2MSR_get_dsr(data)                                                      ((0x00000020&(data))>>5)
#define ISO_U2MSR_cts_shift                                                          (4)
#define ISO_U2MSR_cts_mask                                                           (0x00000010)
#define ISO_U2MSR_cts(data)                                                          (0x00000010&((data)<<4))
#define ISO_U2MSR_cts_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U2MSR_get_cts(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U2MSR_ddcd_shift                                                         (3)
#define ISO_U2MSR_ddcd_mask                                                          (0x00000008)
#define ISO_U2MSR_ddcd(data)                                                         (0x00000008&((data)<<3))
#define ISO_U2MSR_ddcd_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U2MSR_get_ddcd(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U2MSR_teri_shift                                                         (2)
#define ISO_U2MSR_teri_mask                                                          (0x00000004)
#define ISO_U2MSR_teri(data)                                                         (0x00000004&((data)<<2))
#define ISO_U2MSR_teri_src(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U2MSR_get_teri(data)                                                     ((0x00000004&(data))>>2)
#define ISO_U2MSR_ddsr_shift                                                         (1)
#define ISO_U2MSR_ddsr_mask                                                          (0x00000002)
#define ISO_U2MSR_ddsr(data)                                                         (0x00000002&((data)<<1))
#define ISO_U2MSR_ddsr_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U2MSR_get_ddsr(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U2MSR_dcts_shift                                                         (0)
#define ISO_U2MSR_dcts_mask                                                          (0x00000001)
#define ISO_U2MSR_dcts(data)                                                         (0x00000001&((data)<<0))
#define ISO_U2MSR_dcts_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U2MSR_get_dcts(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U2SCR                                                                    0x18007A1C
#define ISO_U2SCR_reg_addr                                                           "0xB8007A1C"
#define ISO_U2SCR_reg                                                                0xB8007A1C
#define set_ISO_U2SCR_reg(data)   (*((volatile unsigned int*) ISO_U2SCR_reg)=data)
#define get_ISO_U2SCR_reg   (*((volatile unsigned int*) ISO_U2SCR_reg))
#define ISO_U2SCR_inst_adr                                                           "0x0087"
#define ISO_U2SCR_inst                                                               0x0087
#define ISO_U2SCR_scr_shift                                                          (0)
#define ISO_U2SCR_scr_mask                                                           (0x000000FF)
#define ISO_U2SCR_scr(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U2SCR_scr_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U2SCR_get_scr(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U2SRBR_0                                                                 0x18007A30
#define ISO_U2SRBR_1                                                                 0x18007A34
#define ISO_U2SRBR_2                                                                 0x18007A38
#define ISO_U2SRBR_3                                                                 0x18007A3C
#define ISO_U2SRBR_4                                                                 0x18007A40
#define ISO_U2SRBR_5                                                                 0x18007A44
#define ISO_U2SRBR_6                                                                 0x18007A48
#define ISO_U2SRBR_7                                                                 0x18007A4C
#define ISO_U2SRBR_8                                                                 0x18007A50
#define ISO_U2SRBR_9                                                                 0x18007A54
#define ISO_U2SRBR_10                                                                 0x18007A58
#define ISO_U2SRBR_11                                                                 0x18007A5C
#define ISO_U2SRBR_12                                                                 0x18007A60
#define ISO_U2SRBR_13                                                                 0x18007A64
#define ISO_U2SRBR_14                                                                 0x18007A68
#define ISO_U2SRBR_15                                                                 0x18007A6C
#define ISO_U2SRBR_0_reg_addr                                                        "0xB8007A30"
#define ISO_U2SRBR_1_reg_addr                                                        "0xB8007A34"
#define ISO_U2SRBR_2_reg_addr                                                        "0xB8007A38"
#define ISO_U2SRBR_3_reg_addr                                                        "0xB8007A3C"
#define ISO_U2SRBR_4_reg_addr                                                        "0xB8007A40"
#define ISO_U2SRBR_5_reg_addr                                                        "0xB8007A44"
#define ISO_U2SRBR_6_reg_addr                                                        "0xB8007A48"
#define ISO_U2SRBR_7_reg_addr                                                        "0xB8007A4C"
#define ISO_U2SRBR_8_reg_addr                                                        "0xB8007A50"
#define ISO_U2SRBR_9_reg_addr                                                        "0xB8007A54"
#define ISO_U2SRBR_10_reg_addr                                                        "0xB8007A58"
#define ISO_U2SRBR_11_reg_addr                                                        "0xB8007A5C"
#define ISO_U2SRBR_12_reg_addr                                                        "0xB8007A60"
#define ISO_U2SRBR_13_reg_addr                                                        "0xB8007A64"
#define ISO_U2SRBR_14_reg_addr                                                        "0xB8007A68"
#define ISO_U2SRBR_15_reg_addr                                                        "0xB8007A6C"
#define ISO_U2SRBR_0_reg                                                             0xB8007A30
#define ISO_U2SRBR_1_reg                                                             0xB8007A34
#define ISO_U2SRBR_2_reg                                                             0xB8007A38
#define ISO_U2SRBR_3_reg                                                             0xB8007A3C
#define ISO_U2SRBR_4_reg                                                             0xB8007A40
#define ISO_U2SRBR_5_reg                                                             0xB8007A44
#define ISO_U2SRBR_6_reg                                                             0xB8007A48
#define ISO_U2SRBR_7_reg                                                             0xB8007A4C
#define ISO_U2SRBR_8_reg                                                             0xB8007A50
#define ISO_U2SRBR_9_reg                                                             0xB8007A54
#define ISO_U2SRBR_10_reg                                                             0xB8007A58
#define ISO_U2SRBR_11_reg                                                             0xB8007A5C
#define ISO_U2SRBR_12_reg                                                             0xB8007A60
#define ISO_U2SRBR_13_reg                                                             0xB8007A64
#define ISO_U2SRBR_14_reg                                                             0xB8007A68
#define ISO_U2SRBR_15_reg                                                             0xB8007A6C
#define set_ISO_U2SRBR_0_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_0_reg)=data)
#define set_ISO_U2SRBR_1_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_1_reg)=data)
#define set_ISO_U2SRBR_2_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_2_reg)=data)
#define set_ISO_U2SRBR_3_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_3_reg)=data)
#define set_ISO_U2SRBR_4_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_4_reg)=data)
#define set_ISO_U2SRBR_5_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_5_reg)=data)
#define set_ISO_U2SRBR_6_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_6_reg)=data)
#define set_ISO_U2SRBR_7_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_7_reg)=data)
#define set_ISO_U2SRBR_8_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_8_reg)=data)
#define set_ISO_U2SRBR_9_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_9_reg)=data)
#define set_ISO_U2SRBR_10_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_10_reg)=data)
#define set_ISO_U2SRBR_11_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_11_reg)=data)
#define set_ISO_U2SRBR_12_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_12_reg)=data)
#define set_ISO_U2SRBR_13_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_13_reg)=data)
#define set_ISO_U2SRBR_14_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_14_reg)=data)
#define set_ISO_U2SRBR_15_reg(data)   (*((volatile unsigned int*) ISO_U2SRBR_15_reg)=data)
#define get_ISO_U2SRBR_0_reg   (*((volatile unsigned int*) ISO_U2SRBR_0_reg))
#define get_ISO_U2SRBR_1_reg   (*((volatile unsigned int*) ISO_U2SRBR_1_reg))
#define get_ISO_U2SRBR_2_reg   (*((volatile unsigned int*) ISO_U2SRBR_2_reg))
#define get_ISO_U2SRBR_3_reg   (*((volatile unsigned int*) ISO_U2SRBR_3_reg))
#define get_ISO_U2SRBR_4_reg   (*((volatile unsigned int*) ISO_U2SRBR_4_reg))
#define get_ISO_U2SRBR_5_reg   (*((volatile unsigned int*) ISO_U2SRBR_5_reg))
#define get_ISO_U2SRBR_6_reg   (*((volatile unsigned int*) ISO_U2SRBR_6_reg))
#define get_ISO_U2SRBR_7_reg   (*((volatile unsigned int*) ISO_U2SRBR_7_reg))
#define get_ISO_U2SRBR_8_reg   (*((volatile unsigned int*) ISO_U2SRBR_8_reg))
#define get_ISO_U2SRBR_9_reg   (*((volatile unsigned int*) ISO_U2SRBR_9_reg))
#define get_ISO_U2SRBR_10_reg   (*((volatile unsigned int*) ISO_U2SRBR_10_reg))
#define get_ISO_U2SRBR_11_reg   (*((volatile unsigned int*) ISO_U2SRBR_11_reg))
#define get_ISO_U2SRBR_12_reg   (*((volatile unsigned int*) ISO_U2SRBR_12_reg))
#define get_ISO_U2SRBR_13_reg   (*((volatile unsigned int*) ISO_U2SRBR_13_reg))
#define get_ISO_U2SRBR_14_reg   (*((volatile unsigned int*) ISO_U2SRBR_14_reg))
#define get_ISO_U2SRBR_15_reg   (*((volatile unsigned int*) ISO_U2SRBR_15_reg))
#define ISO_U2SRBR_0_inst_adr                                                        "0x008C"
#define ISO_U2SRBR_1_inst_adr                                                        "0x008D"
#define ISO_U2SRBR_2_inst_adr                                                        "0x008E"
#define ISO_U2SRBR_3_inst_adr                                                        "0x008F"
#define ISO_U2SRBR_4_inst_adr                                                        "0x0090"
#define ISO_U2SRBR_5_inst_adr                                                        "0x0091"
#define ISO_U2SRBR_6_inst_adr                                                        "0x0092"
#define ISO_U2SRBR_7_inst_adr                                                        "0x0093"
#define ISO_U2SRBR_8_inst_adr                                                        "0x0094"
#define ISO_U2SRBR_9_inst_adr                                                        "0x0095"
#define ISO_U2SRBR_10_inst_adr                                                        "0x0096"
#define ISO_U2SRBR_11_inst_adr                                                        "0x0097"
#define ISO_U2SRBR_12_inst_adr                                                        "0x0098"
#define ISO_U2SRBR_13_inst_adr                                                        "0x0099"
#define ISO_U2SRBR_14_inst_adr                                                        "0x009A"
#define ISO_U2SRBR_15_inst_adr                                                        "0x009B"
#define ISO_U2SRBR_0_inst                                                            0x008C
#define ISO_U2SRBR_1_inst                                                            0x008D
#define ISO_U2SRBR_2_inst                                                            0x008E
#define ISO_U2SRBR_3_inst                                                            0x008F
#define ISO_U2SRBR_4_inst                                                            0x0090
#define ISO_U2SRBR_5_inst                                                            0x0091
#define ISO_U2SRBR_6_inst                                                            0x0092
#define ISO_U2SRBR_7_inst                                                            0x0093
#define ISO_U2SRBR_8_inst                                                            0x0094
#define ISO_U2SRBR_9_inst                                                            0x0095
#define ISO_U2SRBR_10_inst                                                            0x0096
#define ISO_U2SRBR_11_inst                                                            0x0097
#define ISO_U2SRBR_12_inst                                                            0x0098
#define ISO_U2SRBR_13_inst                                                            0x0099
#define ISO_U2SRBR_14_inst                                                            0x009A
#define ISO_U2SRBR_15_inst                                                            0x009B
#define ISO_U2SRBR_rbd_shift                                                         (0)
#define ISO_U2SRBR_rbd_mask                                                          (0x000000FF)
#define ISO_U2SRBR_rbd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U2SRBR_rbd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U2SRBR_get_rbd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U2FAR                                                                    0x18007A70
#define ISO_U2FAR_reg_addr                                                           "0xB8007A70"
#define ISO_U2FAR_reg                                                                0xB8007A70
#define set_ISO_U2FAR_reg(data)   (*((volatile unsigned int*) ISO_U2FAR_reg)=data)
#define get_ISO_U2FAR_reg   (*((volatile unsigned int*) ISO_U2FAR_reg))
#define ISO_U2FAR_inst_adr                                                           "0x009C"
#define ISO_U2FAR_inst                                                               0x009C
#define ISO_U2FAR_far_shift                                                          (0)
#define ISO_U2FAR_far_mask                                                           (0x00000001)
#define ISO_U2FAR_far(data)                                                          (0x00000001&((data)<<0))
#define ISO_U2FAR_far_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U2FAR_get_far(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U2TFR                                                                    0x18007A74
#define ISO_U2TFR_reg_addr                                                           "0xB8007A74"
#define ISO_U2TFR_reg                                                                0xB8007A74
#define set_ISO_U2TFR_reg(data)   (*((volatile unsigned int*) ISO_U2TFR_reg)=data)
#define get_ISO_U2TFR_reg   (*((volatile unsigned int*) ISO_U2TFR_reg))
#define ISO_U2TFR_inst_adr                                                           "0x009D"
#define ISO_U2TFR_inst                                                               0x009D
#define ISO_U2TFR_far_shift                                                          (0)
#define ISO_U2TFR_far_mask                                                           (0x000000FF)
#define ISO_U2TFR_far(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U2TFR_far_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U2TFR_get_far(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U2RFW                                                                    0x18007A78
#define ISO_U2RFW_reg_addr                                                           "0xB8007A78"
#define ISO_U2RFW_reg                                                                0xB8007A78
#define set_ISO_U2RFW_reg(data)   (*((volatile unsigned int*) ISO_U2RFW_reg)=data)
#define get_ISO_U2RFW_reg   (*((volatile unsigned int*) ISO_U2RFW_reg))
#define ISO_U2RFW_inst_adr                                                           "0x009E"
#define ISO_U2RFW_inst                                                               0x009E
#define ISO_U2RFW_rffe_shift                                                         (9)
#define ISO_U2RFW_rffe_mask                                                          (0x00000200)
#define ISO_U2RFW_rffe(data)                                                         (0x00000200&((data)<<9))
#define ISO_U2RFW_rffe_src(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U2RFW_get_rffe(data)                                                     ((0x00000200&(data))>>9)
#define ISO_U2RFW_rfpf_shift                                                         (8)
#define ISO_U2RFW_rfpf_mask                                                          (0x00000100)
#define ISO_U2RFW_rfpf(data)                                                         (0x00000100&((data)<<8))
#define ISO_U2RFW_rfpf_src(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U2RFW_get_rfpf(data)                                                     ((0x00000100&(data))>>8)
#define ISO_U2RFW_rfwd_shift                                                         (0)
#define ISO_U2RFW_rfwd_mask                                                          (0x000000FF)
#define ISO_U2RFW_rfwd(data)                                                         (0x000000FF&((data)<<0))
#define ISO_U2RFW_rfwd_src(data)                                                     ((0x000000FF&(data))>>0)
#define ISO_U2RFW_get_rfwd(data)                                                     ((0x000000FF&(data))>>0)


#define ISO_U2USR                                                                    0x18007A7C
#define ISO_U2USR_reg_addr                                                           "0xB8007A7C"
#define ISO_U2USR_reg                                                                0xB8007A7C
#define set_ISO_U2USR_reg(data)   (*((volatile unsigned int*) ISO_U2USR_reg)=data)
#define get_ISO_U2USR_reg   (*((volatile unsigned int*) ISO_U2USR_reg))
#define ISO_U2USR_inst_adr                                                           "0x009F"
#define ISO_U2USR_inst                                                               0x009F
#define ISO_U2USR_rff_shift                                                          (4)
#define ISO_U2USR_rff_mask                                                           (0x00000010)
#define ISO_U2USR_rff(data)                                                          (0x00000010&((data)<<4))
#define ISO_U2USR_rff_src(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U2USR_get_rff(data)                                                      ((0x00000010&(data))>>4)
#define ISO_U2USR_rfne_shift                                                         (3)
#define ISO_U2USR_rfne_mask                                                          (0x00000008)
#define ISO_U2USR_rfne(data)                                                         (0x00000008&((data)<<3))
#define ISO_U2USR_rfne_src(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U2USR_get_rfne(data)                                                     ((0x00000008&(data))>>3)
#define ISO_U2USR_tfe_shift                                                          (2)
#define ISO_U2USR_tfe_mask                                                           (0x00000004)
#define ISO_U2USR_tfe(data)                                                          (0x00000004&((data)<<2))
#define ISO_U2USR_tfe_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U2USR_get_tfe(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U2USR_tfnf_shift                                                         (1)
#define ISO_U2USR_tfnf_mask                                                          (0x00000002)
#define ISO_U2USR_tfnf(data)                                                         (0x00000002&((data)<<1))
#define ISO_U2USR_tfnf_src(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U2USR_get_tfnf(data)                                                     ((0x00000002&(data))>>1)
#define ISO_U2USR_busy_shift                                                         (0)
#define ISO_U2USR_busy_mask                                                          (0x00000001)
#define ISO_U2USR_busy(data)                                                         (0x00000001&((data)<<0))
#define ISO_U2USR_busy_src(data)                                                     ((0x00000001&(data))>>0)
#define ISO_U2USR_get_busy(data)                                                     ((0x00000001&(data))>>0)


#define ISO_U2TFL                                                                    0x18007A80
#define ISO_U2TFL_reg_addr                                                           "0xB8007A80"
#define ISO_U2TFL_reg                                                                0xB8007A80
#define set_ISO_U2TFL_reg(data)   (*((volatile unsigned int*) ISO_U2TFL_reg)=data)
#define get_ISO_U2TFL_reg   (*((volatile unsigned int*) ISO_U2TFL_reg))
#define ISO_U2TFL_inst_adr                                                           "0x00A0"
#define ISO_U2TFL_inst                                                               0x00A0
#define ISO_U2TFL_tfl_shift                                                          (0)
#define ISO_U2TFL_tfl_mask                                                           (0x000000FF)
#define ISO_U2TFL_tfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U2TFL_tfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U2TFL_get_tfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U2RFL                                                                    0x18007A84
#define ISO_U2RFL_reg_addr                                                           "0xB8007A84"
#define ISO_U2RFL_reg                                                                0xB8007A84
#define set_ISO_U2RFL_reg(data)   (*((volatile unsigned int*) ISO_U2RFL_reg)=data)
#define get_ISO_U2RFL_reg   (*((volatile unsigned int*) ISO_U2RFL_reg))
#define ISO_U2RFL_inst_adr                                                           "0x00A1"
#define ISO_U2RFL_inst                                                               0x00A1
#define ISO_U2RFL_rfl_shift                                                          (0)
#define ISO_U2RFL_rfl_mask                                                           (0x000000FF)
#define ISO_U2RFL_rfl(data)                                                          (0x000000FF&((data)<<0))
#define ISO_U2RFL_rfl_src(data)                                                      ((0x000000FF&(data))>>0)
#define ISO_U2RFL_get_rfl(data)                                                      ((0x000000FF&(data))>>0)


#define ISO_U2SRR                                                                    0x18007A88
#define ISO_U2SRR_reg_addr                                                           "0xB8007A88"
#define ISO_U2SRR_reg                                                                0xB8007A88
#define set_ISO_U2SRR_reg(data)   (*((volatile unsigned int*) ISO_U2SRR_reg)=data)
#define get_ISO_U2SRR_reg   (*((volatile unsigned int*) ISO_U2SRR_reg))
#define ISO_U2SRR_inst_adr                                                           "0x00A2"
#define ISO_U2SRR_inst                                                               0x00A2
#define ISO_U2SRR_xfr_shift                                                          (2)
#define ISO_U2SRR_xfr_mask                                                           (0x00000004)
#define ISO_U2SRR_xfr(data)                                                          (0x00000004&((data)<<2))
#define ISO_U2SRR_xfr_src(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U2SRR_get_xfr(data)                                                      ((0x00000004&(data))>>2)
#define ISO_U2SRR_rfr_shift                                                          (1)
#define ISO_U2SRR_rfr_mask                                                           (0x00000002)
#define ISO_U2SRR_rfr(data)                                                          (0x00000002&((data)<<1))
#define ISO_U2SRR_rfr_src(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U2SRR_get_rfr(data)                                                      ((0x00000002&(data))>>1)
#define ISO_U2SRR_ur_shift                                                           (0)
#define ISO_U2SRR_ur_mask                                                            (0x00000001)
#define ISO_U2SRR_ur(data)                                                           (0x00000001&((data)<<0))
#define ISO_U2SRR_ur_src(data)                                                       ((0x00000001&(data))>>0)
#define ISO_U2SRR_get_ur(data)                                                       ((0x00000001&(data))>>0)


#define ISO_U2SBCR                                                                   0x18007A90
#define ISO_U2SBCR_reg_addr                                                          "0xB8007A90"
#define ISO_U2SBCR_reg                                                               0xB8007A90
#define set_ISO_U2SBCR_reg(data)   (*((volatile unsigned int*) ISO_U2SBCR_reg)=data)
#define get_ISO_U2SBCR_reg   (*((volatile unsigned int*) ISO_U2SBCR_reg))
#define ISO_U2SBCR_inst_adr                                                          "0x00A4"
#define ISO_U2SBCR_inst                                                              0x00A4
#define ISO_U2SBCR_sbcr_shift                                                        (0)
#define ISO_U2SBCR_sbcr_mask                                                         (0x00000001)
#define ISO_U2SBCR_sbcr(data)                                                        (0x00000001&((data)<<0))
#define ISO_U2SBCR_sbcr_src(data)                                                    ((0x00000001&(data))>>0)
#define ISO_U2SBCR_get_sbcr(data)                                                    ((0x00000001&(data))>>0)


#define ISO_U2SDMAM                                                                  0x18007A94
#define ISO_U2SDMAM_reg_addr                                                         "0xB8007A94"
#define ISO_U2SDMAM_reg                                                              0xB8007A94
#define set_ISO_U2SDMAM_reg(data)   (*((volatile unsigned int*) ISO_U2SDMAM_reg)=data)
#define get_ISO_U2SDMAM_reg   (*((volatile unsigned int*) ISO_U2SDMAM_reg))
#define ISO_U2SDMAM_inst_adr                                                         "0x00A5"
#define ISO_U2SDMAM_inst                                                             0x00A5
#define ISO_U2SDMAM_sdmam_shift                                                      (0)
#define ISO_U2SDMAM_sdmam_mask                                                       (0x00000001)
#define ISO_U2SDMAM_sdmam(data)                                                      (0x00000001&((data)<<0))
#define ISO_U2SDMAM_sdmam_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U2SDMAM_get_sdmam(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U2SFE                                                                    0x18007A98
#define ISO_U2SFE_reg_addr                                                           "0xB8007A98"
#define ISO_U2SFE_reg                                                                0xB8007A98
#define set_ISO_U2SFE_reg(data)   (*((volatile unsigned int*) ISO_U2SFE_reg)=data)
#define get_ISO_U2SFE_reg   (*((volatile unsigned int*) ISO_U2SFE_reg))
#define ISO_U2SFE_inst_adr                                                           "0x00A6"
#define ISO_U2SFE_inst                                                               0x00A6
#define ISO_U2SFE_sfe_shift                                                          (0)
#define ISO_U2SFE_sfe_mask                                                           (0x00000001)
#define ISO_U2SFE_sfe(data)                                                          (0x00000001&((data)<<0))
#define ISO_U2SFE_sfe_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U2SFE_get_sfe(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U2SRT                                                                    0x18007A9C
#define ISO_U2SRT_reg_addr                                                           "0xB8007A9C"
#define ISO_U2SRT_reg                                                                0xB8007A9C
#define set_ISO_U2SRT_reg(data)   (*((volatile unsigned int*) ISO_U2SRT_reg)=data)
#define get_ISO_U2SRT_reg   (*((volatile unsigned int*) ISO_U2SRT_reg))
#define ISO_U2SRT_inst_adr                                                           "0x00A7"
#define ISO_U2SRT_inst                                                               0x00A7
#define ISO_U2SRT_srt_shift                                                          (0)
#define ISO_U2SRT_srt_mask                                                           (0x00000003)
#define ISO_U2SRT_srt(data)                                                          (0x00000003&((data)<<0))
#define ISO_U2SRT_srt_src(data)                                                      ((0x00000003&(data))>>0)
#define ISO_U2SRT_get_srt(data)                                                      ((0x00000003&(data))>>0)


#define ISO_U2STET                                                                   0x18007AA0
#define ISO_U2STET_reg_addr                                                          "0xB8007AA0"
#define ISO_U2STET_reg                                                               0xB8007AA0
#define set_ISO_U2STET_reg(data)   (*((volatile unsigned int*) ISO_U2STET_reg)=data)
#define get_ISO_U2STET_reg   (*((volatile unsigned int*) ISO_U2STET_reg))
#define ISO_U2STET_inst_adr                                                          "0x00A8"
#define ISO_U2STET_inst                                                              0x00A8
#define ISO_U2STET_stet_shift                                                        (0)
#define ISO_U2STET_stet_mask                                                         (0x00000003)
#define ISO_U2STET_stet(data)                                                        (0x00000003&((data)<<0))
#define ISO_U2STET_stet_src(data)                                                    ((0x00000003&(data))>>0)
#define ISO_U2STET_get_stet(data)                                                    ((0x00000003&(data))>>0)


#define ISO_U2HTX                                                                    0x18007AA4
#define ISO_U2HTX_reg_addr                                                           "0xB8007AA4"
#define ISO_U2HTX_reg                                                                0xB8007AA4
#define set_ISO_U2HTX_reg(data)   (*((volatile unsigned int*) ISO_U2HTX_reg)=data)
#define get_ISO_U2HTX_reg   (*((volatile unsigned int*) ISO_U2HTX_reg))
#define ISO_U2HTX_inst_adr                                                           "0x00A9"
#define ISO_U2HTX_inst                                                               0x00A9
#define ISO_U2HTX_htx_shift                                                          (0)
#define ISO_U2HTX_htx_mask                                                           (0x00000001)
#define ISO_U2HTX_htx(data)                                                          (0x00000001&((data)<<0))
#define ISO_U2HTX_htx_src(data)                                                      ((0x00000001&(data))>>0)
#define ISO_U2HTX_get_htx(data)                                                      ((0x00000001&(data))>>0)


#define ISO_U2DMASA                                                                  0x18007AA8
#define ISO_U2DMASA_reg_addr                                                         "0xB8007AA8"
#define ISO_U2DMASA_reg                                                              0xB8007AA8
#define set_ISO_U2DMASA_reg(data)   (*((volatile unsigned int*) ISO_U2DMASA_reg)=data)
#define get_ISO_U2DMASA_reg   (*((volatile unsigned int*) ISO_U2DMASA_reg))
#define ISO_U2DMASA_inst_adr                                                         "0x00AA"
#define ISO_U2DMASA_inst                                                             0x00AA
#define ISO_U2DMASA_dmasa_shift                                                      (0)
#define ISO_U2DMASA_dmasa_mask                                                       (0x00000001)
#define ISO_U2DMASA_dmasa(data)                                                      (0x00000001&((data)<<0))
#define ISO_U2DMASA_dmasa_src(data)                                                  ((0x00000001&(data))>>0)
#define ISO_U2DMASA_get_dmasa(data)                                                  ((0x00000001&(data))>>0)


#define ISO_U2CPR                                                                    0x18007AF4
#define ISO_U2CPR_reg_addr                                                           "0xB8007AF4"
#define ISO_U2CPR_reg                                                                0xB8007AF4
#define set_ISO_U2CPR_reg(data)   (*((volatile unsigned int*) ISO_U2CPR_reg)=data)
#define get_ISO_U2CPR_reg   (*((volatile unsigned int*) ISO_U2CPR_reg))
#define ISO_U2CPR_inst_adr                                                           "0x00BD"
#define ISO_U2CPR_inst                                                               0x00BD
#define ISO_U2CPR_fifo_mode_shift                                                    (16)
#define ISO_U2CPR_fifo_mode_mask                                                     (0x00FF0000)
#define ISO_U2CPR_fifo_mode(data)                                                    (0x00FF0000&((data)<<16))
#define ISO_U2CPR_fifo_mode_src(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U2CPR_get_fifo_mode(data)                                                ((0x00FF0000&(data))>>16)
#define ISO_U2CPR_dma_extra_shift                                                    (13)
#define ISO_U2CPR_dma_extra_mask                                                     (0x00002000)
#define ISO_U2CPR_dma_extra(data)                                                    (0x00002000&((data)<<13))
#define ISO_U2CPR_dma_extra_src(data)                                                ((0x00002000&(data))>>13)
#define ISO_U2CPR_get_dma_extra(data)                                                ((0x00002000&(data))>>13)
#define ISO_U2CPR_uart_add_encoded_params_shift                                      (12)
#define ISO_U2CPR_uart_add_encoded_params_mask                                       (0x00001000)
#define ISO_U2CPR_uart_add_encoded_params(data)                                      (0x00001000&((data)<<12))
#define ISO_U2CPR_uart_add_encoded_params_src(data)                                  ((0x00001000&(data))>>12)
#define ISO_U2CPR_get_uart_add_encoded_params(data)                                  ((0x00001000&(data))>>12)
#define ISO_U2CPR_shadow_shift                                                       (11)
#define ISO_U2CPR_shadow_mask                                                        (0x00000800)
#define ISO_U2CPR_shadow(data)                                                       (0x00000800&((data)<<11))
#define ISO_U2CPR_shadow_src(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U2CPR_get_shadow(data)                                                   ((0x00000800&(data))>>11)
#define ISO_U2CPR_fifo_stat_shift                                                    (10)
#define ISO_U2CPR_fifo_stat_mask                                                     (0x00000400)
#define ISO_U2CPR_fifo_stat(data)                                                    (0x00000400&((data)<<10))
#define ISO_U2CPR_fifo_stat_src(data)                                                ((0x00000400&(data))>>10)
#define ISO_U2CPR_get_fifo_stat(data)                                                ((0x00000400&(data))>>10)
#define ISO_U2CPR_fifo_access_shift                                                  (9)
#define ISO_U2CPR_fifo_access_mask                                                   (0x00000200)
#define ISO_U2CPR_fifo_access(data)                                                  (0x00000200&((data)<<9))
#define ISO_U2CPR_fifo_access_src(data)                                              ((0x00000200&(data))>>9)
#define ISO_U2CPR_get_fifo_access(data)                                              ((0x00000200&(data))>>9)
#define ISO_U2CPR_additional_feat_shift                                              (8)
#define ISO_U2CPR_additional_feat_mask                                               (0x00000100)
#define ISO_U2CPR_additional_feat(data)                                              (0x00000100&((data)<<8))
#define ISO_U2CPR_additional_feat_src(data)                                          ((0x00000100&(data))>>8)
#define ISO_U2CPR_get_additional_feat(data)                                          ((0x00000100&(data))>>8)
#define ISO_U2CPR_sir_lp_mode_shift                                                  (7)
#define ISO_U2CPR_sir_lp_mode_mask                                                   (0x00000080)
#define ISO_U2CPR_sir_lp_mode(data)                                                  (0x00000080&((data)<<7))
#define ISO_U2CPR_sir_lp_mode_src(data)                                              ((0x00000080&(data))>>7)
#define ISO_U2CPR_get_sir_lp_mode(data)                                              ((0x00000080&(data))>>7)
#define ISO_U2CPR_sir_mode_shift                                                     (6)
#define ISO_U2CPR_sir_mode_mask                                                      (0x00000040)
#define ISO_U2CPR_sir_mode(data)                                                     (0x00000040&((data)<<6))
#define ISO_U2CPR_sir_mode_src(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U2CPR_get_sir_mode(data)                                                 ((0x00000040&(data))>>6)
#define ISO_U2CPR_thre_mode_shift                                                    (5)
#define ISO_U2CPR_thre_mode_mask                                                     (0x00000020)
#define ISO_U2CPR_thre_mode(data)                                                    (0x00000020&((data)<<5))
#define ISO_U2CPR_thre_mode_src(data)                                                ((0x00000020&(data))>>5)
#define ISO_U2CPR_get_thre_mode(data)                                                ((0x00000020&(data))>>5)
#define ISO_U2CPR_afce_mode_shift                                                    (4)
#define ISO_U2CPR_afce_mode_mask                                                     (0x00000010)
#define ISO_U2CPR_afce_mode(data)                                                    (0x00000010&((data)<<4))
#define ISO_U2CPR_afce_mode_src(data)                                                ((0x00000010&(data))>>4)
#define ISO_U2CPR_get_afce_mode(data)                                                ((0x00000010&(data))>>4)
#define ISO_U2CPR_apb_data_width_shift                                               (0)
#define ISO_U2CPR_apb_data_width_mask                                                (0x00000003)
#define ISO_U2CPR_apb_data_width(data)                                               (0x00000003&((data)<<0))
#define ISO_U2CPR_apb_data_width_src(data)                                           ((0x00000003&(data))>>0)
#define ISO_U2CPR_get_apb_data_width(data)                                           ((0x00000003&(data))>>0)


#define ISO_U2UCV                                                                    0x18007AF8
#define ISO_U2UCV_reg_addr                                                           "0xB8007AF8"
#define ISO_U2UCV_reg                                                                0xB8007AF8
#define set_ISO_U2UCV_reg(data)   (*((volatile unsigned int*) ISO_U2UCV_reg)=data)
#define get_ISO_U2UCV_reg   (*((volatile unsigned int*) ISO_U2UCV_reg))
#define ISO_U2UCV_inst_adr                                                           "0x00BE"
#define ISO_U2UCV_inst                                                               0x00BE
#define ISO_U2UCV_ucv_shift                                                          (0)
#define ISO_U2UCV_ucv_mask                                                           (0xFFFFFFFF)
#define ISO_U2UCV_ucv(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U2UCV_ucv_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U2UCV_get_ucv(data)                                                      ((0xFFFFFFFF&(data))>>0)


#define ISO_U2CTR                                                                    0x18007AFC
#define ISO_U2CTR_reg_addr                                                           "0xB8007AFC"
#define ISO_U2CTR_reg                                                                0xB8007AFC
#define set_ISO_U2CTR_reg(data)   (*((volatile unsigned int*) ISO_U2CTR_reg)=data)
#define get_ISO_U2CTR_reg   (*((volatile unsigned int*) ISO_U2CTR_reg))
#define ISO_U2CTR_inst_adr                                                           "0x00BF"
#define ISO_U2CTR_inst                                                               0x00BF
#define ISO_U2CTR_ctr_shift                                                          (0)
#define ISO_U2CTR_ctr_mask                                                           (0xFFFFFFFF)
#define ISO_U2CTR_ctr(data)                                                          (0xFFFFFFFF&((data)<<0))
#define ISO_U2CTR_ctr_src(data)                                                      ((0xFFFFFFFF&(data))>>0)
#define ISO_U2CTR_get_ctr(data)                                                      ((0xFFFFFFFF&(data))>>0)

#define ST_PAD0                                                                      0x18061500
#define ST_PAD0_reg_addr                                                             "0xB8061500"
#define ST_PAD0_reg                                                                  0xB8061500
#define set_ST_PAD0_reg(data)   (*((volatile unsigned int*) ST_PAD0_reg)=data)
#define get_ST_PAD0_reg   (*((volatile unsigned int*) ST_PAD0_reg))

#define ST_LSADC_ANALOG_CTRL                                                         0x18061528
#define ST_LSADC_ANALOG_CTRL_reg_addr                                                "0xB8061528"
#define ST_LSADC_ANALOG_CTRL_reg                                                     0xB8061528
#define set_ST_LSADC_ANALOG_CTRL_reg(data)   (*((volatile unsigned int*) ST_LSADC_ANALOG_CTRL_reg)=data)
#define get_ST_LSADC_ANALOG_CTRL_reg   (*((volatile unsigned int*) ST_LSADC_ANALOG_CTRL_reg))

#define ST_LSADC_CTRL                                                                0x18061520
#define ST_LSADC_CTRL_reg_addr                                                       "0xB8061520"
#define ST_LSADC_CTRL_reg                                                            0xB8061520
#define set_ST_LSADC_CTRL_reg(data)   (*((volatile unsigned int*) ST_LSADC_CTRL_reg)=data)
#define get_ST_LSADC_CTRL_reg   (*((volatile unsigned int*) ST_LSADC_CTRL_reg))



#endif
