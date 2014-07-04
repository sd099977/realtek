#ifndef _HDMI_TX_TABLE_H_INCLUDED_
#define _HDMI_TX_TABLE_H_INCLUDED_

#include "hdmi_tx_struct_def.h"

enum hdmi_tx_video_format_index {
	HDMI_TX_720_1440_480I_60HZ = 0,
	HDMI_TX_720_480P_60HZ,
	HDMI_TX_720_1440_576I_50HZ,
	HDMI_TX_720_576P_50HZ,
	HDMI_TX_1280_720P_60HZ,
	HDMI_TX_1920_1080I_50HZ,
	HDMI_TX_1920_1080I_60HZ,
	HDMI_TX_1920_1080P_24HZ,
	HDMI_TX_1280_720P_50HZ,
	HDMI_TX_1920_1080P_50HZ,
	HDMI_TX_1920_1080P_60HZ,
	HDMI_TX_3840_2160P_30HZ,
	HDMI_TX_1600_1200P_85HZ,
	HDMI_TX_800_600P_72HZ,
    HDMI_TX_VIDEO_TIMING_NUM
};

hdmi_tx_timing_gen_st cea_timing_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : video timing info. table when selecting hdmi timing gen.
	 * Table format : {x, {set1}, {set2}, {set3}} every row (video format)
	 *  		x   : vic
	 *  	{set1}	: {blank, active, sync, front, back} for h
	 *  	{set2}  : {space, blank, act_video, active, sync, front, back} for v
	 *  	{set3}  : {synci, blanki, backi, fronti} for vi
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{6, {276, 1440, 124, 38, 114}, {1, 22, 240, 240, 4, 5, 15}, {4, 23, 17, 5}},
	{2, {138, 720, 62, 16, 60}, {1, 45, 480, 480, 7, 10, 30}, {1, 1, 1, 1}},
	{21, {288, 1440, 126, 24, 138}, {1, 24, 288, 288, 4, 3, 19}, {4, 25, 20, 3}},
	{17, {144, 720, 64, 12, 68}, {1, 49, 576, 576, 6, 6, 39}, {1, 1, 1, 1}},
	{4, {370, 1280, 40, 110, 220}, {1, 30, 720, 720, 6, 6, 20}, {1, 1, 1, 1}},
	{20, {720, 1920, 44, 528, 148}, {1, 22, 540, 540, 6, 3, 15}, {6, 23, 16, 3}},
	{5, {280, 1920, 44, 88, 148}, {1, 22, 540, 540, 6, 3, 15}, {6, 23, 16, 3}},
	{32, {830, 1920, 44, 638, 148}, {1, 45, 1080, 1080, 6, 5, 36}, {1, 1, 1, 1}},
	{19, {700, 1280, 40, 440, 220}, {1, 30, 720, 720, 6, 6, 20}, {1, 1, 1, 1}},
	{31, {720, 1920, 44, 528, 148}, {1, 45, 1080, 1080, 6, 5, 36}, {1, 1, 1, 1}},
	{16, {280, 1920, 44, 87, 148}, {1, 45, 1080, 1080, 6, 5, 36}, {1, 1, 1, 1}}, //HDMI_TX_1920_1080P_60HZ
	{95, {560, 3840, 88, 176, 296}, {1, 90, 2160, 2160, 10, 8, 72}, {1, 1, 1, 1}},
	{0, {560, 1600, 192, 64, 304}, {1, 50, 1200, 1200, 3, 1, 46}, {1, 1, 1, 1}},
	{0, {200, 800, 80, 16, 104}, {1, 75, 600, 600, 3, 1, 71}, {1, 1, 1, 1}},
};

hdmi_tx_timing_dpc_disp_st dpc_8bit_disp_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : video 8bit deep color info. table when selecting hdmi timing gen.
	 * Table format : {{set1}, {set2}} every row (video format)
	 *  		x   : vic
	 *  	{set1}	: {vfch_num, fp_swen, fp, pp_swen, swen, default_ph}
	 *  	{set2}  : {dly_nor_h, dly_nor_v, dly_disp_h, dly_disp_v}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
};

hdmi_tx_timing_dpc_disp_st dpc_10bit_disp_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : video 10bit deep color info. table when selecting hdmi timing gen.
	 * Table format : {{set1}, {set2}} every row (video format)
	 *  		x   : vic
	 *  	{set1}	: {vfch_num, fp_swen, fp, pp_swen, swen, default_ph}
	 *  	{set2}  : {dly_nor_h, dly_nor_v, dly_disp_h, dly_disp_v}
	 * Table index  :
	 * 	    HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{3, 1, 2, 0, 1, 0}, {0, 0, 0, 0}},
	{{3, 1, 0, 0, 1, 0}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{3, 1, 2, 0, 1, 0}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{3, 1, 0, 0, 1, 0}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
};

hdmi_tx_timing_dpc_disp_st dpc_12bit_disp_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : video 12bit deep color info. table when selecting hdmi timing gen.
	 * Table format : {{set1}, {set2}} every row (video format)
	 *  		x   : vic
	 *  	{set1}	: {vfch_num, fp_swen, fp, pp_swen, swen, default_ph}
	 *  	{set2}  : {dly_nor_h, dly_nor_v, dly_disp_h, dly_disp_v}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
	{{1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}},
};

enum hdmi_tx_pll_disp_freq_index {

	PLL_DISP_FREQ_27M = 0,
	PLL_DISP_FREQ_54M,
	PLL_DISP_FREQ_74M25,
    PLL_DISP_FREQ_108M,
    PLL_DISP_FREQ_148M5,
    PLL_DISP_FREQ_297M,
    PLL_DISP_FREQ_NUM
};

enum hdmi_tx_deep_color_index {
	DEEP_COLOR_8BIT_MODE = 0,
	DEEP_COLOR_10BIT_MODE,
	DEEP_COLOR_12BIT_MODE,
    DEEP_COLOR_MODE_NUM
};

pll_disp_param_st pll_disp_table[PLL_DISP_FREQ_NUM][DEEP_COLOR_MODE_NUM] = {
	/*
	 * Discription : disp pll div table
	 * Table format : {
	 * 					{set1},
	 * 					{set2},
	 * 					{set3},
	 *                }
	 *                => every frequcecy has three deep color needed to be adjusted
	 *  	{set1}	: {tv_ldiv, tv_pre_div, pix_div3, pix_div5, pix_div16, tmds_div5, tmds_div16}
	 *  	{set2}  : the same with {set1}
	 *      {set3}  : the same with {set1}
	 * Table index  :
	 *      PLL_DISP_FREQ_NUM : frequecy index (see hdmi_tx_pll_disp_freq_index)
	 *      DEEP_COLOR_MODE_NUM : deep color index (see hdmi_tx_deep_color_index)
	 */
	{
		{14, 0, 0, 0, 4, 0, 4},
		{38, 1, 0, 1, 2, 0, 4},
		{22, 0, 1, 0, 3, 0, 4},
	},

	{
		{14, 0, 0, 0, 3, 0, 3},
		{38, 1, 0, 1, 1, 0, 3},
		{22, 0, 1, 0, 2, 0, 3},
	},

	{
		{20, 0, 0, 0, 3, 0, 3},
		{53, 1, 0, 1, 1, 0, 3},
		{31, 1, 1, 0, 1, 0, 2},
	},

	{
		{14, 0, 0, 0, 2, 0, 2},
		{38, 1, 0, 1, 0, 0, 2},
		{22, 0, 1, 0, 1, 0, 2},
	},

	{
		{20, 0, 0, 0, 2, 0, 2},
		{53, 1, 0, 1, 0, 0, 2},
		{31, 1, 1, 0, 0, 0, 1},
	},

	{
		{20, 0, 0, 0, 1, 0, 1},
		{53, 0, 0, 1, 0, 0, 2},
		{31, 0, 1, 0, 0, 0, 1},
	},
};


pll_div_param_st pll_div_deep_color_8bit_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll div table for 8bit deep color
	 * Table format : {{set1}}
	 *  	{set1}	: {tv_ldiv, tv_pre_div, pix_div3, pix_div5, pix_div16, tmds_div5, tmds_div16}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{14, 0, 0, 0, 4, 0, 4}},
	{{14, 0, 0, 0, 4, 0, 4}},
	{{14, 0, 0, 0, 4, 0, 4}},
	{{14, 0, 0, 0, 4, 0, 4}},
	{{20, 0, 0, 0, 3, 0, 3}},
	{{20, 0, 0, 0, 3, 0, 3}},
	{{20, 0, 0, 0, 3, 0, 3}},
	{{20, 0, 0, 0, 3, 0, 3}},
	{{20, 0, 0, 0, 3, 0, 3}},
	{{20, 0, 0, 0, 2, 0, 2}},
	{{20, 0, 0, 0, 2, 0, 2}},
	{{20, 0, 0, 0, 1, 0, 1}},
	{{15, 0, 0, 0, 1, 0, 1}},
	{{34, 1, 0, 1, 1, 1, 1}},
};

pll_div_param_st pll_div_deep_color_10bit_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll div table for 10bit deep color
	 * Table format : {{set1}}
	 *  	{set1}	: {tv_ldiv, tv_pre_div, pix_div3, pix_div5, pix_div16, tmds_div5, tmds_div16}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{38, 1, 0, 1, 2, 0, 4}},
	{{38, 1, 0, 1, 2, 0, 4}},
	{{38, 1, 0, 1, 2, 0, 4}},
	{{38, 1, 0, 1, 2, 0, 4}},
	{{53, 1, 0, 1, 1, 0, 3}},
	{{53, 1, 0, 1, 1, 0, 3}},
	{{53, 1, 0, 1, 1, 0, 3}},
	{{53, 1, 0, 1, 1, 0, 3}},
	{{53, 1, 0, 1, 1, 0, 3}},
	{{53, 1, 0, 1, 0, 0, 2}},
	{{53, 1, 0, 1, 0, 0, 2}},
	{{53, 0, 0, 1, 0, 0, 2}},
	{{0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0}},
};

pll_div_param_st pll_div_deep_color_12bit_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll div table for 12bit deep color
	 * Table format : {{set1}}
	 *  	{set1}	: {tv_ldiv, tv_pre_div, pix_div3, pix_div5, pix_div16, tmds_div5, tmds_div16}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{22, 0, 1, 0, 3, 0, 4}},
	{{22, 0, 1, 0, 3, 0, 4}},
	{{22, 0, 1, 0, 3, 0, 4}},
	{{22, 0, 1, 0, 3, 0, 4}},
	{{31, 1, 1, 0, 1, 0, 2}},
	{{31, 1, 1, 0, 1, 0, 2}},
	{{31, 1, 1, 0, 1, 0, 2}},
	{{31, 1, 1, 0, 1, 0, 2}},
	{{31, 1, 1, 0, 1, 0, 2}},
	{{31, 1, 1, 0, 0, 0, 1}},
	{{31, 1, 1, 0, 0, 0, 1}},
	{{31, 0, 1, 0, 0, 0, 1}},
	{{0, 0, 0, 0, 0, 0, 0}},
	{{0, 0, 0, 0, 0, 0, 0}},
};

pll_analog_param_st pll_analog_deep_color_8bit_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll analog param table for 8bit deep color
	 * Table format : {{set1}, {set2}, {set3}} every row (video format)
	 *  	{set1}	: {tv_kvco, tv_cp, tv_cs, tv_icp, tv_rs, tv_pstep}
	 *  	{set2}  : {tx_pll_kvco, tx_pll_icp, tx_pll_rs, tx_pll_cp, tx_pll_cs}
	 *  	{set3}  : {pll_vco_scal, ldo_cco_vsel, ldo_pll_vsel, ldo_tmds_vsel}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x2, 0x2, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x1, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x1, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
};

pll_analog_param_st pll_analog_deep_color_10bit_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll analog param table for 10bit deep color
	 * Table format : {{set1}, {set2}, {set3}} every row (video format)
	 *  	{set1}	: {tv_kvco, tv_cp, tv_cs, tv_icp, tv_rs, tv_pstep}
	 *  	{set2}  : {tx_pll_kvco, tx_pll_icp, tx_pll_rs, tx_pll_cp, tx_pll_cs}
	 *  	{set3}  : {pll_vco_scal, ldo_cco_vsel, ldo_pll_vsel, ldo_tmds_vsel}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x2, 0x2, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x1, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, {0x0, 0x0, 0x0, 0x0, 0x0}, {0, 0x0, 0, 0}},
	{{0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, {0x0, 0x0, 0x0, 0x0, 0x0}, {0, 0x0, 0, 0}},
};

pll_analog_param_st pll_analog_deep_color_12bit_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll analog param table for 12bit deep color
	 * Table format : {{set1}, {set2}, {set3}} every row (video format)
	 *  	{set1}	: {tv_kvco, tv_cp, tv_cs, tv_icp, tv_rs, tv_pstep}
	 *  	{set2}  : {tx_pll_kvco, tx_pll_icp, tx_pll_rs, tx_pll_cp, tx_pll_cs}
	 *  	{set3}  : {pll_vco_scal, ldo_cco_vsel, ldo_pll_vsel, ldo_tmds_vsel}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x2, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x1, 0x5, 0x2, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x1, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, {0x0, 0x0, 0x0, 0x0, 0x0}, {0, 0x0, 0, 0}},
	{{0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, {0x0, 0x0, 0x0, 0x0, 0x0}, {0, 0x0, 0, 0}},

};

hdmi_tx_tve_timing_gen_st tve_timg_8bit_dpc_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : video timing info. table when selecting tve timing gen. for 8bit deep color
	 * Table format : {{set1}, {set2}, {set3}, {set4}, x} every row (video format)
	 *  	{set1}	: {hpos, hs_st, hs_end, hpos_st, hpos_end} for h
	 *  	{set2}  : {vpos, st_pos1v, st_pos1h, end_pos1v, end_pos1h, st_pos2v, st_pos2h, end_pos2v, end_pos2h} for v
	 *  	{set3}  : {vfch_num, fp_swen, fp, pp_swen, swen, default_ph} for dcp
	 *  	{set4}  : {dly_nor_h, dly_nor_v, dly_disp_h, dly_disp_v} for disp param
	 *  	x       : 0:progressive, 1:interlace
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{0, 18, 80, 124, 851}, {0, 3, 18, 6, 18, 265, 447, 268, 447}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 1},
	{{0, 15, 77, 116, 850}, {0, 6, 15, 12, 15, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 798, 861, 54, 781}, {0, 624, 798, 2, 798, 312, 366, 315, 366}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 1},
	{{0, 863, 63, 110, 844}, {0, 624, 863, 4, 863, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 110, 150, 355, 1649}, {0, 0, 110, 5, 110, 0, 0, 0, 0}, {3, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 34, 56, 127, 1094}, {0, 0, 34, 5, 34, 562, 694, 567, 694}, {1, 0, 0, 0, 1, 1}, {0, 0, 3, 3}, 1},
	{{0, 34, 56, 127, 1094}, {0, 0, 34, 5, 34, 562, 584, 567, 584}, {1, 0, 0, 0, 1, 1}, {0, 0, 3, 3}, 1},
	{{0, 124, 168, 295, 2229}, {0, 0, 124, 5, 124, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 116, 156, 355, 1649}, {0, 0, 116, 5, 116, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 124, 168, 301, 2235}, {0, 0, 124, 5, 124, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 88, 132, 265, 2199}, {0, 0, 88, 5, 88, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
};

hdmi_tx_tve_timing_gen_st tve_timg_10bit_dpc_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : video timing info. table when selecting tve timing gen. for 10bit deep color
	 * Table format : {{set1}, {set2}, {set3}, {set4}, x} every row (video format)
	 *  	{set1}	: {hpos, hs_st, hs_end, hpos_st, hpos_end} for h
	 *  	{set2}  : {vpos, st_pos1v, st_pos1h, end_pos1v, end_pos1h, st_pos2v, st_pos2h, end_pos2v, end_pos2h} for v
	 *  	{set3}  : {vfch_num, fp_swen, fp, pp_swen, swen, default_ph} for dcp
	 *  	{set4}  : {dly_nor_h, dly_nor_v, dly_disp_h, dly_disp_v} for disp param
	 *  	x       : 0:progressive, 1:interlace
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{0, 17, 79, 124, 851}, {0, 3, 17, 6, 17, 265, 446, 268, 446}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 1},
	{{0, 15, 77, 116, 850}, {0, 6, 15, 12, 15, 0, 0, 0, 0}, {3, 1, 2, 0, 1, 0}, {0, 0, 2, 2}, 0},
	{{0, 798, 861, 54, 781}, {0, 624, 798, 2, 798, 312, 366, 315, 366}, {3, 1, 0, 0, 1, 0}, {0, 0, 2, 2}, 1},
	{{0, 863, 63, 110, 844}, {0, 624, 863, 4, 863, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 110, 150, 355, 1649}, {0, 0, 110, 5, 110, 0, 0, 0, 0}, {3, 1, 2, 0, 1, 0}, {0, 0, 2, 2}, 0},
	{{0, 35, 57, 127, 1094}, {0, 0, 35, 5, 35, 562, 695, 567, 695}, {1, 0, 0, 0, 1, 1}, {0, 0, 1, 1}, 1},
	{{0, 35, 57, 127, 1094}, {0, 0, 35, 5, 35, 562, 585, 567, 585}, {1, 0, 0, 0, 1, 1}, {0, 0, 1, 1}, 1},
	{{0, 124, 168, 295, 2229}, {0, 0, 124, 5, 124, 0, 0, 0, 0}, {3, 1, 2, 0, 1, 0}, {0, 0, 2, 2}, 0},
	{{0, 116, 156, 355, 1649}, {0, 0, 116, 5, 116, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 125, 169, 301, 2235}, {0, 0, 125, 5, 125, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 0, 0}, 0},
	{{0, 89, 133, 265, 2199}, {0, 0, 89, 5, 89, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 1, 1}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
};

hdmi_tx_tve_timing_gen_st tve_timg_12bit_dpc_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : video timing info. table when selecting tve timing gen. for 10bit deep color
	 * Table format : {{set1}, {set2}, {set3}, {set4}, x} every row (video format)
	 *  	{set1}	: {hpos, hs_st, hs_end, hpos_st, hpos_end} for h
	 *  	{set2}  : {vpos, st_pos1v, st_pos1h, end_pos1v, end_pos1h, st_pos2v, st_pos2h, end_pos2v, end_pos2h} for v
	 *  	{set3}  : {vfch_num, fp_swen, fp, pp_swen, swen, default_ph} for dcp
	 *  	{set4}  : {dly_nor_h, dly_nor_v, dly_disp_h, dly_disp_v} for disp param
	 *  	x       : 0:progressive, 1:interlace
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{0, 17, 79, 124, 851}, {0, 3, 17, 6, 17, 265, 446, 268, 446}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 1},
	{{0, 15, 77, 116, 850}, {0, 6, 15, 12, 15, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 798, 861, 54, 781}, {0, 624, 798, 2, 798, 312, 366, 315, 366}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 1},
	{{0, 863, 63, 110, 844}, {0, 624, 863, 4, 863, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 110, 150, 355, 1649}, {0, 0, 110, 5, 110, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 2, 2}, 0},
	{{0, 35, 57, 127, 1094}, {0, 0, 35, 5, 35, 562, 695, 567, 695}, {1, 0, 0, 0, 1, 1}, {0, 0, 1, 1}, 1},
	{{0, 35, 57, 127, 1094}, {0, 0, 35, 5, 35, 562, 585, 567, 585}, {1, 0, 0, 0, 1, 1}, {0, 0, 1, 1}, 1},
	{{0, 125, 168, 295, 2229}, {0, 0, 125, 5, 125, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 1, 1}, 0},
	{{0, 117, 157, 355, 1649}, {0, 0, 117, 5, 117, 0, 0, 0, 0}, {1, 0, 0, 0, 1, 1}, {0, 0, 1, 1}, 0},
	{{0, 125, 169, 301, 2235}, {0, 0, 125, 5, 125, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 89, 133, 265, 2199}, {0, 0, 89, 5, 89, 0, 0, 0, 0}, {1, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
	{{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0}, 0},
};

hdmi_tx_max_packet_num_st packet_num_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : packet number table
	 * Table format : {set} every row (video format)
	 *  	{set}	: {v_max, h_max}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 * Note         :
	 * 	    h_max = max(int((h blank - reg(0x0f0) - 10(circuit process time) - island preamble - island GB*2 - video preamble)/32), 18)
	 *      ex: max(int((280 - 42 - 10 - 8 - 2*2 -8)/32), 18)
	 */
	{18, 6},
	{18, 2},
	{18, 6},
	{18, 2},
	{18, 9},
	{18, 18},
	{18, 6},
	{18, 18},
	{18, 18},
	{18, 18},
	{18, 6},
	{18, 15},
	{18, 15},
	{18, 15},
};

#endif