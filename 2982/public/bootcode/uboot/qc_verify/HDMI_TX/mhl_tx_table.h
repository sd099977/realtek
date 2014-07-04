#ifndef _MHL_TX_TABLE_H_INCLUDED_
#define _MHL_TX_TABLE_H_INCLUDED_

#include "hdmi_tx_struct_def.h"

pll_div_param_st pll_div_8bit_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll div table for 8bit deep color
	 * Table format : {{set1}}
	 *  	{set1}	: {tv_ldiv, tv_pre_div, pix_div3, pix_div5, pix_div16, tmds_div5, tmds_div16}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{22, 0, 1, 0, 3, 0, 3}},
	{{22, 0, 1, 0, 3, 0, 3}},
	{{22, 0, 1, 0, 3, 0, 3}},
	{{22, 0, 1, 0, 3, 0, 3}},
	{{31, 1, 1, 0, 1, 0, 1}},
	{{31, 1, 1, 0, 1, 0, 1}},
	{{31, 1, 1, 0, 1, 0, 1}},
	{{31, 1, 1, 0, 1, 0, 1}},
	{{31, 1, 1, 0, 1, 0, 1}},
	{{0, 0, 0, 0, 0, 0, 0}}, // 1080P@50 needs to change to pp mode
	{{0, 0, 0, 0, 0, 0, 0}}, // 1080P@60 needs to change to pp mode
	{{0, 0, 0, 0, 0, 0, 0}}, // 2160P@30 doesn't support
};

pll_div_param_st pll_div_pp_mode_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll div table for 8bit deep color
	 * Table format : {{set1}}
	 *  	{set1}	: {tv_ldiv, tv_pre_div, pix_div3, pix_div5, pix_div16, tmds_div5, tmds_div16}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{14, 0, 0, 0, 4, 0, 3}},
	{{14, 0, 0, 0, 4, 0, 3}},
	{{14, 0, 0, 0, 4, 0, 3}},
	{{14, 0, 0, 0, 4, 0, 3}},
	{{20, 0, 0, 0, 3, 0, 2}},
	{{20, 0, 0, 0, 3, 0, 2}},
	{{20, 0, 0, 0, 3, 0, 2}},
	{{20, 0, 0, 0, 3, 0, 2}},
	{{20, 0, 0, 0, 3, 0, 2}},
	{{20, 0, 0, 0, 2, 0, 1}},
	{{20, 0, 0, 0, 2, 0, 1}},
	{{0, 0, 0, 0, 0, 0, 0}}, // 2160P@30 doesn't support
};

pll_analog_param_st pll_analog_mhl_table[HDMI_TX_VIDEO_TIMING_NUM] = {
	/*
	 * Discription : pll analog param table for 8bit deep color
	 * Table format : {{set1}, {set2}, {set3}} every row (video format)
	 *  	{set1}	: {tv_kvco, tv_cp, tv_cs, tv_icp, tv_rs, tv_pstep}
	 *  	{set2}  : {tx_pll_kvco, tx_pll_icp, tx_pll_rs, tx_pll_cp, tx_pll_cs}
	 *  	{set3}  : {pll_vco_scal, ldo_cco_vsel, ldo_pll_vsel, ldo_tmds_vsel}
	 * Table index  :
	 *      HDMI_TX_VIDEO_TIMING_NUM : see hdmi_tx_video_format_index
	 */
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x1, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x1, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x1, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x0, 0x5, 0x2, 0x1, 0x1}, {0x1, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x0, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x1, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x1, 0x2, 0x5}, {0x1, 0x2, 0x2, 0x1, 0x1}, {0, 0x3, 0, 0}},
	{{0x1, 0x1, 0x1, 0x6, 0x1, 0x5}, {0x1, 0x2, 0x1, 0x1, 0x1}, {0, 0x3, 0, 0}},
};

#endif