#ifndef _HDMI_TX_STRUCT_DEF_H_INCLUDED_
#define _HDMI_TX_STRUCT_DEF_H_INCLUDED_

#define VSIF_VIDEO_FORMAT_BIT 5
#define VSIF_3D_FORMAT_BIT 4

typedef struct {
	unsigned int blank;
	unsigned int active;
	unsigned int sync;
	unsigned int front;
	unsigned int back;
} cea_timing_h_param_st;

typedef struct {
	unsigned int space;
	unsigned int blank;
	unsigned int act_video;
	unsigned int active;
	unsigned int sync;
	unsigned int front;
	unsigned int back;
} cea_timing_v_param_st;

typedef struct {
	unsigned int synci;
	unsigned int blanki;
	unsigned int backi;
	unsigned int fronti;
} cea_timing_v_i_param_st;

typedef struct {
	unsigned char  vfch_num;
	unsigned char  fp_swen;
	unsigned char  fp;
	unsigned char  pp_swen;
	unsigned char  swen;
	unsigned char  default_ph;
} deep_color_param_st;

typedef struct {
	unsigned char  dly_nor_h;
	unsigned char  dly_nor_v;
	unsigned char  dly_disp_h;
	unsigned char  dly_disp_v;
} disp_timing_param_st;

typedef struct {
	unsigned int video_code;
	cea_timing_h_param_st h;
	cea_timing_v_param_st v;
	cea_timing_v_i_param_st vi;
} hdmi_tx_timing_gen_st;

typedef struct {
	deep_color_param_st dpc;
	disp_timing_param_st disp;
} hdmi_tx_timing_dpc_disp_st;

typedef struct {
	unsigned int tv_ldiv;
	unsigned int tv_pre_div;
	unsigned int pix_div3;
	unsigned int pix_div5;
	unsigned int pix_div16;
	unsigned int tmds_div5;
	unsigned int tmds_div16;
} pll_disp_param_st;

typedef struct {
	pll_disp_param_st disp;
	//pll_ddsa_param_st *ddsa
	//pll_hdmi_tx_param_st *hdmi;
} pll_div_param_st;

typedef struct {
	unsigned int tv_kvco;
	unsigned int tv_cp;
	unsigned int tv_cs;
	unsigned int tv_icp;
	unsigned int tv_rs;
	unsigned int tv_pstep;
} pll_disp_analog_st;

typedef struct {
	unsigned int tx_pll_kvco;
	unsigned int tx_pll_icp;
	unsigned int tx_pll_rs;
	unsigned int tx_pll_cp;
	unsigned int tx_pll_cs;
} pll_hdmi_analog_st;

typedef struct {
	unsigned int pll_vco_scal;
	unsigned int ldo_cco_vsel;
	unsigned int ldo_pll_vsel;
	unsigned int ldo_tmds_vsel;
} pll_others_analog_st;

typedef struct {
	pll_disp_analog_st disp;
	pll_hdmi_analog_st hdmi;
	pll_others_analog_st others;
} pll_analog_param_st;

typedef struct {
	unsigned int hpos;
	unsigned int hs_st;
	unsigned int hs_end;
	unsigned int hpos_st;
	unsigned int hpos_end;
} tve_timing_h_param_st;

typedef struct {
	unsigned int vpos;
	unsigned int st_pos1v;
	unsigned int st_pos1h;
	unsigned int end_pos1v;
	unsigned int end_pos1h;
	unsigned int st_pos2v;
	unsigned int st_pos2h;
	unsigned int end_pos2v;
	unsigned int end_pos2h;
} tve_timing_v_param_st;

typedef struct {
	tve_timing_h_param_st h;
	tve_timing_v_param_st v;
	deep_color_param_st dpc;
	disp_timing_param_st disp;
	bool interlace;
} hdmi_tx_tve_timing_gen_st;

typedef struct {
	unsigned char v_max;
	unsigned char h_max;
} hdmi_tx_max_packet_num_st;

enum hdmi_tx_vsif_video_format {
	HDMI_TX_NO_ADDITIONAL_VIDEO_FORMAT = 0x0,
	HDMI_TX_EXTENDED_RESOLUTION_4K2K_FORMAT = 0x1,
	HDMI_TX_EXTENDED_RESOLUTION_3D_FORMAT = 0x2,
};

enum hdmi_tx_vsif_4k2k_vic {
	HDMI_TX_2160P30_VIC = 0x1,
	HDMI_TX_2160P24_VIC = 0x3,
};

#endif // _HDMI_TX_STRUCT_DEF_H_INCLUDED_