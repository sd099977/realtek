/**
* @file rbusColor_icmReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/12/31
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_COLOR_ICM_REG_H_
#define _RBUS_COLOR_ICM_REG_H_

#include "rbusTypes.h"



//  COLOR_ICM Register Address



#define  COLOR_ICM_DM_ICM_CTRL_VADDR 		(0xb802a100)
#define  COLOR_ICM_DM_ICM_CM0_HUE_RANGE_VADDR 		(0xb802a104)
#define  COLOR_ICM_DM_ICM_CM0_DEL_HUE_CENTER_VADDR 		(0xb802a108)
#define  COLOR_ICM_DM_ICM_CM0_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a10c)
#define  COLOR_ICM_DM_ICM_CM0_DEL_SAT_ITN_VADDR 		(0xb802a110)
#define  COLOR_ICM_DM_ICM_CM1_HUE_RANGE_VADDR 		(0xb802a114)
#define  COLOR_ICM_DM_ICM_CM1_DEL_HUE_CENTER_VADDR 		(0xb802a118)
#define  COLOR_ICM_DM_ICM_CM1_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a11c)
#define  COLOR_ICM_DM_ICM_CM1_DEL_SAT_ITN_VADDR 		(0xb802a120)
#define  COLOR_ICM_DM_ICM_CM2_HUE_RANGE_VADDR 		(0xb802a124)
#define  COLOR_ICM_DM_ICM_CM2_DEL_HUE_CENTER_VADDR 		(0xb802a128)
#define  COLOR_ICM_DM_ICM_CM2_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a12c)
#define  COLOR_ICM_DM_ICM_CM2_DEL_SAT_ITN_VADDR 		(0xb802a130)
#define  COLOR_ICM_DM_ICM_CM3_HUE_RANGE_VADDR 		(0xb802a134)
#define  COLOR_ICM_DM_ICM_CM3_DEL_HUE_CENTER_VADDR 		(0xb802a138)
#define  COLOR_ICM_DM_ICM_CM3_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a13c)
#define  COLOR_ICM_DM_ICM_CM3_DEL_SAT_ITN_VADDR 		(0xb802a140)
#define  COLOR_ICM_DM_ICM_CM4_HUE_RANGE_VADDR 		(0xb802a144)
#define  COLOR_ICM_DM_ICM_CM4_DEL_HUE_CENTER_VADDR 		(0xb802a148)
#define  COLOR_ICM_DM_ICM_CM4_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a14c)
#define  COLOR_ICM_DM_ICM_CM4_DEL_SAT_ITN_VADDR 		(0xb802a150)
#define  COLOR_ICM_DM_ICM_CM5_HUE_RANGE_VADDR 		(0xb802a154)
#define  COLOR_ICM_DM_ICM_CM5_DEL_HUE_CENTER_VADDR 		(0xb802a158)
#define  COLOR_ICM_DM_ICM_CM5_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a15c)
#define  COLOR_ICM_DM_ICM_CM5_DEL_SAT_ITN_VADDR 		(0xb802a160)
#define  COLOR_ICM_DM_ICM_CM6_HUE_RANGE_VADDR 		(0xb802a164)
#define  COLOR_ICM_DM_ICM_CM6_DEL_HUE_CENTER_VADDR 		(0xb802a168)
#define  COLOR_ICM_DM_ICM_CM6_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a16c)
#define  COLOR_ICM_DM_ICM_CM6_DEL_SAT_ITN_VADDR 		(0xb802a170)
#define  COLOR_ICM_DM_ICM_CM0_DEL_HUE_KERNEL_VADDR 		(0xb802a400)
#define  COLOR_ICM_DM_ICM_CM0_DEL_SAT_LEFT_VADDR 		(0xb802a404)
#define  COLOR_ICM_DM_ICM_CM0_DEL_SAT_RIGHT_VADDR 		(0xb802a408)
#define  COLOR_ICM_DM_ICM_CM1_DEL_HUE_KERNEL_VADDR 		(0xb802a40c)
#define  COLOR_ICM_DM_ICM_CM1_DEL_SAT_LEFT_VADDR 		(0xb802a410)
#define  COLOR_ICM_DM_ICM_CM1_DEL_SAT_RIGHT_VADDR 		(0xb802a414)
#define  COLOR_ICM_DM_ICM_CM2_DEL_HUE_KERNEL_VADDR 		(0xb802a418)
#define  COLOR_ICM_DM_ICM_CM2_DEL_SAT_LEFT_VADDR 		(0xb802a41c)
#define  COLOR_ICM_DM_ICM_CM2_DEL_SAT_RIGHT_VADDR 		(0xb802a420)
#define  COLOR_ICM_DM_ICM_CM3_DEL_HUE_KERNEL_VADDR 		(0xb802a424)
#define  COLOR_ICM_DM_ICM_CM3_DEL_SAT_LEFT_VADDR 		(0xb802a428)
#define  COLOR_ICM_DM_ICM_CM3_DEL_SAT_RIGHT_VADDR 		(0xb802a42c)
#define  COLOR_ICM_DM_ICM_CM4_DEL_HUE_KERNEL_VADDR 		(0xb802a430)
#define  COLOR_ICM_DM_ICM_CM4_DEL_SAT_LEFT_VADDR 		(0xb802a434)
#define  COLOR_ICM_DM_ICM_CM4_DEL_SAT_RIGHT_VADDR 		(0xb802a438)
#define  COLOR_ICM_DM_ICM_CM5_DEL_HUE_KERNEL_VADDR 		(0xb802a43c)
#define  COLOR_ICM_DM_ICM_CM5_DEL_SAT_LEFT_VADDR 		(0xb802a440)
#define  COLOR_ICM_DM_ICM_CM5_DEL_SAT_RIGHT_VADDR 		(0xb802a444)
#define  COLOR_ICM_DM_ICM_CM6_DEL_HUE_KERNEL_VADDR 		(0xb802a448)
#define  COLOR_ICM_DM_ICM_CM6_DEL_SAT_LEFT_VADDR 		(0xb802a44c)
#define  COLOR_ICM_DM_ICM_CM6_DEL_SAT_RIGHT_VADDR 		(0xb802a450)
#define  COLOR_ICM_DM_UV_CORING_VADDR 		(0xb802a174)
#define  COLOR_ICM_DM_HUE_ALL_VADDR 		(0xb802a178)
#define  COLOR_ICM_DM_SAT_ALL_VADDR 		(0xb802a17c)
#define  COLOR_ICM_DM_ITN_ALL_VADDR 		(0xb802a180)
#define  COLOR_ICM_DM_SOFT_CLAMP_CTRL_VADDR 		(0xb802a184)
#define  COLOR_ICM_DM_SOFT_CLAMP_SAT_VADDR 		(0xb802a188)
#define  COLOR_ICM_DM_SOFT_CLAMP_ITN_VADDR 		(0xb802a18c)
#define  COLOR_ICM_D_AUTO_SAT_CTRL_VADDR 		(0xb802a190)
#define  COLOR_ICM_D_AUTO_SAT_ITN_VADDR 		(0xb802a194)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CTRL_STATUS_VADDR 		(0xb802a198)
#define  COLOR_ICM_D_AUTO_SAT_PRE_COUNT_VADDR 		(0xb802a1b0)
#define  COLOR_ICM_D_AUTO_SAT_AFTER_COUNT_VADDR 		(0xb802a19c)
#define  COLOR_ICM_D_AUTO_SAT_HIST1_THRD_VADDR 		(0xb802a1a0)
#define  COLOR_ICM_D_AUTO_SAT_HIST2_THRD_VADDR 		(0xb802a1a4)
#define  COLOR_ICM_D_AUTO_SAT_HIST3_THRD_VADDR 		(0xb802a1a8)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CTRL_VADDR 		(0xb802a1ac)
#define  COLOR_ICM_D_AUTO_SAT_HIST_READ_CTRL_VADDR 		(0xb802a1b4)
#define  COLOR_ICM_D_AUTO_SAT_HIST_READ_FLAG_VADDR 		(0xb802a1b8)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_00_OR_16_VADDR 		(0xb802a920)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_01_OR_17_VADDR 		(0xb802a924)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_02_OR_18_VADDR 		(0xb802a928)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_03_OR_19_VADDR 		(0xb802a92c)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_04_OR_20_VADDR 		(0xb802a930)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_05_OR_21_VADDR 		(0xb802a934)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_06_OR_22_VADDR 		(0xb802a938)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_07_OR_23_VADDR 		(0xb802a93c)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_08_OR_24_VADDR 		(0xb802a940)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_09_OR_25_VADDR 		(0xb802a944)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_10_OR_26_VADDR 		(0xb802a948)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_11_OR_27_VADDR 		(0xb802a94c)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_12_OR_28_VADDR 		(0xb802a950)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_13_OR_29_VADDR 		(0xb802a954)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_14_OR_30_VADDR 		(0xb802a958)
#define  COLOR_ICM_D_AUTO_SAT_HIST_CNT_15_OR_31_VADDR 		(0xb802a95c)
#define  COLOR_ICM_ICM_AUTO_CTRL_VADDR 		(0xb802a1c8)
#define  COLOR_ICM_HUE_HIST_SETTINGS_VADDR 		(0xb802a1cc)
#define  COLOR_ICM_HUE_COUNT_00_VADDR 		(0xb802a1d0)
#define  COLOR_ICM_HUE_COUNT_01_VADDR 		(0xb802a1d4)
#define  COLOR_ICM_HUE_COUNT_02_VADDR 		(0xb802a1d8)
#define  COLOR_ICM_HUE_COUNT_03_VADDR 		(0xb802a1dc)
#define  COLOR_ICM_HUE_COUNT_04_VADDR 		(0xb802a1e0)
#define  COLOR_ICM_HUE_COUNT_05_VADDR 		(0xb802a1e4)
#define  COLOR_ICM_HUE_COUNT_06_VADDR 		(0xb802a1e8)
#define  COLOR_ICM_HUE_COUNT_07_VADDR 		(0xb802a1ec)
#define  COLOR_ICM_HUE_COUNT_08_VADDR 		(0xb802a1f0)
#define  COLOR_ICM_HUE_COUNT_09_VADDR 		(0xb802a1f4)
#define  COLOR_ICM_HUE_COUNT_0A_VADDR 		(0xb802a1f8)
#define  COLOR_ICM_HUE_COUNT_0B_VADDR 		(0xb802a1fc)
#define  COLOR_ICM_HUE_COUNT_0C_VADDR 		(0xb802a200)
#define  COLOR_ICM_HUE_COUNT_0D_VADDR 		(0xb802a204)
#define  COLOR_ICM_HUE_COUNT_0E_VADDR 		(0xb802a208)
#define  COLOR_ICM_HUE_COUNT_0F_VADDR 		(0xb802a20c)
#define  COLOR_ICM_HUE_COUNT_10_VADDR 		(0xb802a210)
#define  COLOR_ICM_HUE_COUNT_11_VADDR 		(0xb802a214)
#define  COLOR_ICM_HUE_COUNT_12_VADDR 		(0xb802a218)
#define  COLOR_ICM_HUE_COUNT_13_VADDR 		(0xb802a21c)
#define  COLOR_ICM_HUE_COUNT_14_VADDR 		(0xb802a220)
#define  COLOR_ICM_HUE_COUNT_15_VADDR 		(0xb802a224)
#define  COLOR_ICM_HUE_COUNT_16_VADDR 		(0xb802a228)
#define  COLOR_ICM_HUE_COUNT_17_VADDR 		(0xb802a22c)
#define  COLOR_ICM_HUE_SUM_00_VADDR 		(0xb802a230)
#define  COLOR_ICM_HUE_SUM_01_VADDR 		(0xb802a234)
#define  COLOR_ICM_HUE_SUM_02_VADDR 		(0xb802a238)
#define  COLOR_ICM_HUE_SUM_03_VADDR 		(0xb802a23c)
#define  COLOR_ICM_HUE_SUM_04_VADDR 		(0xb802a240)
#define  COLOR_ICM_HUE_SUM_05_VADDR 		(0xb802a244)
#define  COLOR_ICM_DM_ADJ_BYITN_CTRL_VADDR 		(0xb802a248)
#define  COLOR_ICM_DM_ADJ_BYITN_LB_CM0_3_VADDR 		(0xb802a24c)
#define  COLOR_ICM_DM_ADJ_BYITN_LB_CM4_6_VADDR 		(0xb802a250)
#define  COLOR_ICM_DM_ADJ_BYITN_BUF_VADDR 		(0xb802a254)
#define  COLOR_ICM_DM_ADJ_BYITN_DSAT_DHUE_CM0_VADDR 		(0xb802a258)
#define  COLOR_ICM_DM_ADJ_BYITN_DSAT_DHUE_CM1_VADDR 		(0xb802a25c)
#define  COLOR_ICM_DM_ADJ_BYITN_DSAT_DHUE_CM2_VADDR 		(0xb802a260)
#define  COLOR_ICM_DM_ADJ_BYITN_DSAT_DHUE_CM3_VADDR 		(0xb802a264)
#define  COLOR_ICM_DM_ADJ_BYITN_DSAT_DHUE_CM4_VADDR 		(0xb802a268)
#define  COLOR_ICM_DM_ADJ_BYITN_DSAT_DHUE_CM5_VADDR 		(0xb802a26c)
#define  COLOR_ICM_DM_ADJ_BYITN_DSAT_DHUE_CM6_VADDR 		(0xb802a270)
#define  COLOR_ICM_DM_ICM_MERGE_H_CM01_VADDR 		(0xb802a4b0)
#define  COLOR_ICM_DM_ICM_MERGE_SI_CM01_VADDR 		(0xb802a4b4)
#define  COLOR_ICM_DM_ICM_MERGE_H_CM12_VADDR 		(0xb802a4b8)
#define  COLOR_ICM_DM_ICM_MERGE_SI_CM12_VADDR 		(0xb802a4bc)
#define  COLOR_ICM_DM_ICM_MERGE_H_CM23_VADDR 		(0xb802a4c0)
#define  COLOR_ICM_DM_ICM_MERGE_SI_CM23_VADDR 		(0xb802a4c4)
#define  COLOR_ICM_DM_ICM_MERGE_H_CM34_VADDR 		(0xb802a4c8)
#define  COLOR_ICM_DM_ICM_MERGE_SI_CM34_VADDR 		(0xb802a4cc)
#define  COLOR_ICM_DM_ICM_MERGE_H_CM45_VADDR 		(0xb802a4d0)
#define  COLOR_ICM_DM_ICM_MERGE_SI_CM45_VADDR 		(0xb802a4d4)
#define  COLOR_ICM_DM_ICM_MERGE_H_CM56_VADDR 		(0xb802a4d8)
#define  COLOR_ICM_DM_ICM_MERGE_SI_CM56_VADDR 		(0xb802a4dc)
#define  COLOR_ICM_DM_ICM_MERGE_H_CM60_VADDR 		(0xb802a4e0)
#define  COLOR_ICM_DM_ICM_MERGE_SI_CM60_VADDR 		(0xb802a4e4)
#define  COLOR_ICM_DM_ICM_SI_CLIP_VADDR 		(0xb802a4e8)
#define  COLOR_ICM_DM_ICM_SI_CLIP_THRESHOLD_VADDR 		(0xb802a4ec)
#define  COLOR_ICM_DS_ICM_CTRL_VADDR 		(0xb802a2a0)
#define  COLOR_ICM_DS_ICM_CM0_HUE_RANGE_VADDR 		(0xb802a2a4)
#define  COLOR_ICM_DS_ICM_CM0_DEL_HUE_CENTER_VADDR 		(0xb802a2a8)
#define  COLOR_ICM_DS_ICM_CM0_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a2ac)
#define  COLOR_ICM_DS_ICM_CM0_DEL_SAT_ITN_VADDR 		(0xb802a2b0)
#define  COLOR_ICM_DS_ICM_CM1_HUE_RANGE_VADDR 		(0xb802a2b4)
#define  COLOR_ICM_DS_ICM_CM1_DEL_HUE_CENTER_VADDR 		(0xb802a2b8)
#define  COLOR_ICM_DS_ICM_CM1_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a2bc)
#define  COLOR_ICM_DS_ICM_CM1_DEL_SAT_ITN_VADDR 		(0xb802a2c0)
#define  COLOR_ICM_DS_ICM_CM2_HUE_RANGE_VADDR 		(0xb802a2c4)
#define  COLOR_ICM_DS_ICM_CM2_DEL_HUE_CENTER_VADDR 		(0xb802a2c8)
#define  COLOR_ICM_DS_ICM_CM2_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a2cc)
#define  COLOR_ICM_DS_ICM_CM2_DEL_SAT_ITN_VADDR 		(0xb802a2d0)
#define  COLOR_ICM_DS_ICM_CM3_HUE_RANGE_VADDR 		(0xb802a2d4)
#define  COLOR_ICM_DS_ICM_CM3_DEL_HUE_CENTER_VADDR 		(0xb802a2d8)
#define  COLOR_ICM_DS_ICM_CM3_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a2dc)
#define  COLOR_ICM_DS_ICM_CM3_DEL_SAT_ITN_VADDR 		(0xb802a2e0)
#define  COLOR_ICM_DS_ICM_CM4_HUE_RANGE_VADDR 		(0xb802a2e4)
#define  COLOR_ICM_DS_ICM_CM4_DEL_HUE_CENTER_VADDR 		(0xb802a2e8)
#define  COLOR_ICM_DS_ICM_CM4_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a2ec)
#define  COLOR_ICM_DS_ICM_CM4_DEL_SAT_ITN_VADDR 		(0xb802a2f0)
#define  COLOR_ICM_DS_ICM_CM5_HUE_RANGE_VADDR 		(0xb802a2f4)
#define  COLOR_ICM_DS_ICM_CM5_DEL_HUE_CENTER_VADDR 		(0xb802a2f8)
#define  COLOR_ICM_DS_ICM_CM5_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a2fc)
#define  COLOR_ICM_DS_ICM_CM5_DEL_SAT_ITN_VADDR 		(0xb802a300)
#define  COLOR_ICM_DS_ICM_CM6_HUE_RANGE_VADDR 		(0xb802a304)
#define  COLOR_ICM_DS_ICM_CM6_DEL_HUE_CENTER_VADDR 		(0xb802a308)
#define  COLOR_ICM_DS_ICM_CM6_DEL_HUE_LEFT_RIGHT_VADDR 		(0xb802a30c)
#define  COLOR_ICM_DS_ICM_CM6_DEL_SAT_ITN_VADDR 		(0xb802a310)
#define  COLOR_ICM_DS_ICM_CM0_DEL_HUE_KERNEL_VADDR 		(0xb802a9a0)
#define  COLOR_ICM_DS_ICM_CM0_DEL_SAT_LEFT_VADDR 		(0xb802a9a4)
#define  COLOR_ICM_DS_ICM_CM0_DEL_SAT_RIGHT_VADDR 		(0xb802a9a8)
#define  COLOR_ICM_DS_ICM_CM1_DEL_HUE_KERNEL_VADDR 		(0xb802a9ac)
#define  COLOR_ICM_DS_ICM_CM1_DEL_SAT_LEFT_VADDR 		(0xb802a9b0)
#define  COLOR_ICM_DS_ICM_CM1_DEL_SAT_RIGHT_VADDR 		(0xb802a9b4)
#define  COLOR_ICM_DS_ICM_CM2_DEL_HUE_KERNEL_VADDR 		(0xb802a9b8)
#define  COLOR_ICM_DS_ICM_CM2_DEL_SAT_LEFT_VADDR 		(0xb802a9bc)
#define  COLOR_ICM_DS_ICM_CM2_DEL_SAT_RIGHT_VADDR 		(0xb802a9c0)
#define  COLOR_ICM_DS_ICM_CM3_DEL_HUE_KERNEL_VADDR 		(0xb802a9c4)
#define  COLOR_ICM_DS_ICM_CM3_DEL_SAT_LEFT_VADDR 		(0xb802a9c8)
#define  COLOR_ICM_DS_ICM_CM3_DEL_SAT_RIGHT_VADDR 		(0xb802a9cc)
#define  COLOR_ICM_DS_ICM_CM4_DEL_HUE_KERNEL_VADDR 		(0xb802a9d0)
#define  COLOR_ICM_DS_ICM_CM4_DEL_SAT_LEFT_VADDR 		(0xb802a9d4)
#define  COLOR_ICM_DS_ICM_CM4_DEL_SAT_RIGHT_VADDR 		(0xb802a9d8)
#define  COLOR_ICM_DS_ICM_CM5_DEL_HUE_KERNEL_VADDR 		(0xb802a9dc)
#define  COLOR_ICM_DS_ICM_CM5_DEL_SAT_LEFT_VADDR 		(0xb802a9e0)
#define  COLOR_ICM_DS_ICM_CM5_DEL_SAT_RIGHT_VADDR 		(0xb802a9e4)
#define  COLOR_ICM_DS_ICM_CM6_DEL_HUE_KERNEL_VADDR 		(0xb802a9e8)
#define  COLOR_ICM_DS_ICM_CM6_DEL_SAT_LEFT_VADDR 		(0xb802a9ec)
#define  COLOR_ICM_DS_ICM_CM6_DEL_SAT_RIGHT_VADDR 		(0xb802a9f0)
#define  COLOR_ICM_DS_UV_CORING_VADDR 		(0xb802a314)
#define  COLOR_ICM_DS_HUE_ALL_VADDR 		(0xb802a318)
#define  COLOR_ICM_DS_SAT_ALL_VADDR 		(0xb802a31c)
#define  COLOR_ICM_DS_ITN_ALL_VADDR 		(0xb802a320)
#define  COLOR_ICM_DS_SOFT_CLAMP_CTRL_VADDR 		(0xb802a324)
#define  COLOR_ICM_DS_SOFT_CLAMP_SAT_VADDR 		(0xb802a328)
#define  COLOR_ICM_DS_SOFT_CLAMP_ITN_VADDR 		(0xb802a32c)
#define  COLOR_ICM_DS_ICM_MERGE_H_CM01_VADDR 		(0xb802a340)
#define  COLOR_ICM_DS_ICM_MERGE_SI_CM01_VADDR 		(0xb802a344)
#define  COLOR_ICM_DS_ICM_MERGE_H_CM12_VADDR 		(0xb802a348)
#define  COLOR_ICM_DS_ICM_MERGE_SI_CM12_VADDR 		(0xb802a34c)
#define  COLOR_ICM_DS_ICM_MERGE_H_CM23_VADDR 		(0xb802a350)
#define  COLOR_ICM_DS_ICM_MERGE_SI_CM23_VADDR 		(0xb802a354)
#define  COLOR_ICM_DS_ICM_MERGE_H_CM34_VADDR 		(0xb802a358)
#define  COLOR_ICM_DS_ICM_MERGE_SI_CM34_VADDR 		(0xb802a35c)
#define  COLOR_ICM_DS_ICM_MERGE_H_CM45_VADDR 		(0xb802a900)
#define  COLOR_ICM_DS_ICM_MERGE_SI_CM45_VADDR 		(0xb802a904)
#define  COLOR_ICM_DS_ICM_MERGE_H_CM56_VADDR 		(0xb802a908)
#define  COLOR_ICM_DS_ICM_MERGE_SI_CM56_VADDR 		(0xb802a90c)
#define  COLOR_ICM_DS_ICM_MERGE_H_CM60_VADDR 		(0xb802a910)
#define  COLOR_ICM_DS_ICM_MERGE_SI_CM60_VADDR 		(0xb802a914)
#define  COLOR_ICM_DS_ICM_SI_CLIP_VADDR 		(0xb802a918)
#define  COLOR_ICM_DS_ICM_SI_CLIP_THRESHOLD_VADDR 		(0xb802a91c)
#define  COLOR_ICM_DM_SEG_SHY_ADJ_CTRL_VADDR 		(0xb802a360)
#define  COLOR_ICM_DM_SEG_SHY_SRAM_CTRL_VADDR 		(0xb802a364)
#define  COLOR_ICM_DM_SEG_SHY_SRAM_BIST1_VADDR 		(0xb802a330)
#define  COLOR_ICM_DM_SEG_SHY_SRAM_BIST2_VADDR 		(0xb802a334)
#define  COLOR_ICM_DM_SEG_SHY_SRAM_BIST3_VADDR 		(0xb802a338)
#define  COLOR_ICM_DM_SEG_SHY_SRAM_BIST0_VADDR 		(0xb802a368)
#define  COLOR_ICM_DM_SEG_SHY_SRAM_BIST_2_VADDR 		(0xb802a36c)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_0_VADDR 		(0xb802a370)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_1_VADDR 		(0xb802a374)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_2_VADDR 		(0xb802a378)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_3_VADDR 		(0xb802a37c)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_4_VADDR 		(0xb802a380)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_5_VADDR 		(0xb802a384)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_6_VADDR 		(0xb802a388)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_7_VADDR 		(0xb802a38c)
#define  COLOR_ICM_DM_SEG_SHY_WRITE_SEG_RANDOM_VADDR 		(0xb802a390)
#define  COLOR_ICM_DM_SEG_SHY_READ_SEG_RANDOM_VADDR 		(0xb802a394)
#define  COLOR_ICM_ICM_CRC_CTRL_VADDR 		(0xb802a3d0)
#define  COLOR_ICM_ICM_CRC_RESULT_VADDR 		(0xb802a3d4)



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======COLOR_ICM register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_ctrl:1;
        RBus_UInt32  bypass_yuv2rgb_enable:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  icm_dummy1:4;
        RBus_UInt32  icm_overlay:1;
        RBus_UInt32  merge_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  delta_i_smooth_enable:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  cm_debug:3;
        RBus_UInt32  icm_dummy2:9;
        RBus_UInt32  cm0_enable:1;
        RBus_UInt32  cm1_enable:1;
        RBus_UInt32  cm2_enable:1;
        RBus_UInt32  cm3_enable:1;
        RBus_UInt32  cm4_enable:1;
        RBus_UInt32  cm5_enable:1;
        RBus_UInt32  cm6_enable:1;
    };
}dm_icm_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}dm_icm_cm0_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}dm_icm_cm0_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}dm_icm_cm0_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}dm_icm_cm0_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}dm_icm_cm1_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}dm_icm_cm1_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}dm_icm_cm1_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}dm_icm_cm1_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}dm_icm_cm2_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}dm_icm_cm2_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}dm_icm_cm2_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}dm_icm_cm2_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}dm_icm_cm3_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}dm_icm_cm3_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}dm_icm_cm3_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}dm_icm_cm3_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}dm_icm_cm4_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}dm_icm_cm4_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}dm_icm_cm4_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}dm_icm_cm4_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}dm_icm_cm5_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}dm_icm_cm5_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}dm_icm_cm5_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}dm_icm_cm5_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}dm_icm_cm6_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}dm_icm_cm6_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}dm_icm_cm6_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}dm_icm_cm6_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}dm_icm_cm0_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm0_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm0_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}dm_icm_cm1_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm1_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm1_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}dm_icm_cm2_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm2_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm2_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}dm_icm_cm3_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm3_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm3_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}dm_icm_cm4_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm4_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm4_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}dm_icm_cm5_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm5_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm5_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}dm_icm_cm6_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm6_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}dm_icm_cm6_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  u_coring:8;
        RBus_UInt32  v_coring:8;
    };
}dm_uv_coring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1802a178_31_11:21;
        RBus_UInt32  hue_all:11;
    };
}dm_hue_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  sat_all:12;
    };
}dm_sat_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  itn_all:12;
    };
}dm_itn_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_clip_sel:1;
        RBus_UInt32  sat_multi_clip_sel:1;
        RBus_UInt32  int_clip_sel:1;
        RBus_UInt32  int_multi_clip_sel:1;
        RBus_UInt32  res1:25;
        RBus_UInt32  neg_int_flag_en:1;
        RBus_UInt32  sat_enable:1;
        RBus_UInt32  itn_enable:1;
    };
}dm_soft_clamp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_slope:4;
        RBus_UInt32  sat_thd:12;
        RBus_UInt32  res1:3;
        RBus_UInt32  sat_max:13;
    };
}dm_soft_clamp_sat_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_slope:4;
        RBus_UInt32  itn_thd:12;
        RBus_UInt32  res1:3;
        RBus_UInt32  itn_max:13;
    };
}dm_soft_clamp_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  auto_sat_i_u_thre0:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  auto_sat_i_l_thre0:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  auto_sat_s_thre0:7;
        RBus_UInt32  res4:1;
        RBus_UInt32  auto_sat_new_mode:2;
        RBus_UInt32  sat_hist_mode_sel:1;
        RBus_UInt32  hist_sat_ok:1;
        RBus_UInt32  sat_enable:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  auto_sat_select:1;
    };
}d_auto_sat_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  l_bound:4;
        RBus_UInt32  u_bound:4;
        RBus_UInt32  gain_lo:4;
        RBus_UInt32  gain_hi:4;
        RBus_UInt32  sat_offset:8;
    };
}d_auto_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_hist0_ctrl_status:8;
        RBus_UInt32  sat_hist1_ctrl_status:8;
        RBus_UInt32  sat_hist2_ctrl_status:8;
        RBus_UInt32  sat_hist3_ctrl_status:8;
    };
}d_auto_sat_hist_ctrl_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  pre_cnt:24;
    };
}d_auto_sat_pre_count_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  aft_cnt:24;
    };
}d_auto_sat_after_count_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  auto_sat_i_u_thre1:7;
        RBus_UInt32  auto_sat_i_l_thre1:7;
        RBus_UInt32  auto_sat_s_thre1:7;
    };
}d_auto_sat_hist1_thrd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  auto_sat_i_u_thre2:7;
        RBus_UInt32  auto_sat_i_l_thre2:7;
        RBus_UInt32  auto_sat_s_thre2:7;
    };
}d_auto_sat_hist2_thrd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  auto_sat_i_u_thre3:7;
        RBus_UInt32  auto_sat_i_l_thre3:7;
        RBus_UInt32  auto_sat_s_thre3:7;
    };
}d_auto_sat_hist3_thrd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_hist0_ctrl:8;
        RBus_UInt32  sat_hist1_ctrl:8;
        RBus_UInt32  sat_hist2_ctrl:8;
        RBus_UInt32  sat_hist3_ctrl:8;
    };
}d_auto_sat_hist_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sram_read:1;
        RBus_UInt32  hist_ctrl:2;
        RBus_UInt32  cnt_block:1;
        RBus_UInt32  res1:28;
    };
}d_auto_sat_hist_read_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_hist_sram_read_consistent_flag:1;
        RBus_UInt32  res1:31;
    };
}d_auto_sat_hist_read_flag_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_00_or_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_01_or_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_02_or_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_03_or_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_04_or_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_05_or_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_06_or_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_07_or_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_08_or_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_09_or_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_10_or_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_11_or_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_12_or_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_13_or_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_14_or_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cnt_data:24;
    };
}d_auto_sat_hist_cnt_15_or_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  hue_hist_mode_sel:1;
        RBus_UInt32  hue_hist_select:1;
        RBus_UInt32  hist_hue_ok:1;
        RBus_UInt32  hue_enable:1;
        RBus_UInt32  inside_enable:1;
    };
}icm_auto_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hue_hist_offset_add:8;
        RBus_UInt32  hue_hist_sat_lb:8;
        RBus_UInt32  hue_hist_itn_hb:8;
        RBus_UInt32  hue_hist_itn_lb:8;
    };
}hue_hist_settings_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut0:24;
    };
}hue_count_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut1:24;
    };
}hue_count_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut2:24;
    };
}hue_count_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut3:24;
    };
}hue_count_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut4:24;
    };
}hue_count_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut5:24;
    };
}hue_count_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut6:24;
    };
}hue_count_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut7:24;
    };
}hue_count_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut8:24;
    };
}hue_count_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut9:24;
    };
}hue_count_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut10:24;
    };
}hue_count_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut11:24;
    };
}hue_count_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut12:24;
    };
}hue_count_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut13:24;
    };
}hue_count_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut14:24;
    };
}hue_count_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut15:24;
    };
}hue_count_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut16:24;
    };
}hue_count_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut17:24;
    };
}hue_count_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut18:24;
    };
}hue_count_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut19:24;
    };
}hue_count_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut20:24;
    };
}hue_count_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut21:24;
    };
}hue_count_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut22:24;
    };
}hue_count_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  lut23:24;
    };
}hue_count_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut0:32;
    };
}hue_sum_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut1:32;
    };
}hue_sum_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut2:32;
    };
}hue_sum_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut3:32;
    };
}hue_sum_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut4:32;
    };
}hue_sum_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut5:32;
    };
}hue_sum_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  itnlevel_debug_satlevel_sel:2;
        RBus_UInt32  itnlevel_debug_cm_sel:3;
        RBus_UInt32  itnlevel_debug_enable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dhuebyitn_cm0_enable:1;
        RBus_UInt32  dhuebyitn_cm1_enable:1;
        RBus_UInt32  dhuebyitn_cm2_enable:1;
        RBus_UInt32  dhuebyitn_cm3_enable:1;
        RBus_UInt32  dhuebyitn_cm4_enable:1;
        RBus_UInt32  dhuebyitn_cm5_enable:1;
        RBus_UInt32  dhuebyitn_cm6_enable:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  dsatbyitn_cm0_enable:1;
        RBus_UInt32  dsatbyitn_cm1_enable:1;
        RBus_UInt32  dsatbyitn_cm2_enable:1;
        RBus_UInt32  dsatbyitn_cm3_enable:1;
        RBus_UInt32  dsatbyitn_cm4_enable:1;
        RBus_UInt32  dsatbyitn_cm5_enable:1;
        RBus_UInt32  dsatbyitn_cm6_enable:1;
    };
}dm_adj_byitn_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm3_itn_lb:8;
        RBus_UInt32  cm2_itn_lb:8;
        RBus_UInt32  cm1_itn_lb:8;
        RBus_UInt32  cm0_itn_lb:8;
    };
}dm_adj_byitn_lb_cm0_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  cm6_itn_lb:8;
        RBus_UInt32  cm5_itn_lb:8;
        RBus_UInt32  cm4_itn_lb:8;
    };
}dm_adj_byitn_lb_cm4_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  cm6_itn_buffer:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  cm5_itn_buffer:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  cm4_itn_buffer:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  cm3_itn_buffer:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  cm2_itn_buffer:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  cm1_itn_buffer:3;
        RBus_UInt32  res7:1;
        RBus_UInt32  cm0_itn_buffer:3;
    };
}dm_adj_byitn_buf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  cm0_dhue:11;
        RBus_UInt32  cm0_dsat:12;
    };
}dm_adj_byitn_dsat_dhue_cm0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  cm1_dhue:11;
        RBus_UInt32  cm1_dsat:12;
    };
}dm_adj_byitn_dsat_dhue_cm1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  cm2_dhue:11;
        RBus_UInt32  cm2_dsat:12;
    };
}dm_adj_byitn_dsat_dhue_cm2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  cm3_dhue:11;
        RBus_UInt32  cm3_dsat:12;
    };
}dm_adj_byitn_dsat_dhue_cm3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  cm4_dhue:11;
        RBus_UInt32  cm4_dsat:12;
    };
}dm_adj_byitn_dsat_dhue_cm4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  cm5_dhue:11;
        RBus_UInt32  cm5_dsat:12;
    };
}dm_adj_byitn_dsat_dhue_cm5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:9;
        RBus_UInt32  cm6_dhue:11;
        RBus_UInt32  cm6_dsat:12;
    };
}dm_adj_byitn_dsat_dhue_cm6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  merge_01_en:1;
        RBus_UInt32  merge_12_en:1;
        RBus_UInt32  merge_23_en:1;
        RBus_UInt32  merge_34_en:1;
        RBus_UInt32  merge_45_en:1;
        RBus_UInt32  merge_56_en:1;
        RBus_UInt32  merge_60_en:1;
        RBus_UInt32  del_hue_01:11;
    };
}dm_icm_merge_h_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_01:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_01:12;
    };
}dm_icm_merge_si_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_12:11;
    };
}dm_icm_merge_h_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_12:12;
    };
}dm_icm_merge_si_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_23:11;
    };
}dm_icm_merge_h_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_23:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_23:12;
    };
}dm_icm_merge_si_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_34:11;
    };
}dm_icm_merge_h_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_34:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_34:12;
    };
}dm_icm_merge_si_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_45:11;
    };
}dm_icm_merge_h_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_45:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_45:12;
    };
}dm_icm_merge_si_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_56:11;
    };
}dm_icm_merge_h_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_56:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_56:12;
    };
}dm_icm_merge_si_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_60:11;
    };
}dm_icm_merge_h_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_60:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_60:12;
    };
}dm_icm_merge_si_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  si_clip_en:1;
        RBus_UInt32  si_clip_left_mode:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  si_clip_right_mode:3;
        RBus_UInt32  si_clip_slope_mode:2;
        RBus_UInt32  res2:9;
        RBus_UInt32  sat_threshold:13;
    };
}dm_icm_si_clip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  itn_top_threshold:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  itn_bottom_threshold:14;
    };
}dm_icm_si_clip_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_ctrl:1;
        RBus_UInt32  bypass_yuv2rgb_enable:1;
        RBus_UInt32  icm_dummy1:6;
        RBus_UInt32  merge_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  delta_i_smooth_enable:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  cm_debug:3;
        RBus_UInt32  icm_dummy2:9;
        RBus_UInt32  cm0_enable:1;
        RBus_UInt32  cm1_enable:1;
        RBus_UInt32  cm2_enable:1;
        RBus_UInt32  cm3_enable:1;
        RBus_UInt32  cm4_enable:1;
        RBus_UInt32  cm5_enable:1;
        RBus_UInt32  cm6_enable:1;
    };
}ds_icm_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}ds_icm_cm0_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}ds_icm_cm0_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}ds_icm_cm0_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}ds_icm_cm0_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}ds_icm_cm1_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}ds_icm_cm1_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}ds_icm_cm1_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}ds_icm_cm1_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}ds_icm_cm2_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}ds_icm_cm2_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}ds_icm_cm2_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}ds_icm_cm2_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}ds_icm_cm3_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}ds_icm_cm3_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}ds_icm_cm3_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}ds_icm_cm3_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}ds_icm_cm4_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}ds_icm_cm4_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}ds_icm_cm4_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}ds_icm_cm4_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}ds_icm_cm5_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}ds_icm_cm5_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}ds_icm_cm5_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}ds_icm_cm5_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  l_kernel:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  center:11;
    };
}ds_icm_cm6_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_center:11;
    };
}ds_icm_cm6_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left:11;
        RBus_UInt32  del_right:11;
    };
}ds_icm_cm6_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  del_itn:12;
    };
}ds_icm_cm6_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}ds_icm_cm0_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm0_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm0_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}ds_icm_cm1_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm1_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm1_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}ds_icm_cm2_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm2_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm2_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}ds_icm_cm3_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm3_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm3_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}ds_icm_cm4_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm4_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm4_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}ds_icm_cm5_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm5_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm5_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  del_right_kernel:11;
    };
}ds_icm_cm6_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm6_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  del_sat_range:12;
    };
}ds_icm_cm6_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  u_coring:8;
        RBus_UInt32  v_coring:8;
    };
}ds_uv_coring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  hue_all:11;
    };
}ds_hue_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  sat_all:12;
    };
}ds_sat_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  itn_all:12;
    };
}ds_itn_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_clip_sel:1;
        RBus_UInt32  sat_multi_clip_sel:1;
        RBus_UInt32  int_clip_sel:1;
        RBus_UInt32  int_multi_clip_sel:1;
        RBus_UInt32  res1:25;
        RBus_UInt32  neg_int_flag_en:1;
        RBus_UInt32  sat_enable:1;
        RBus_UInt32  itn_enable:1;
    };
}ds_soft_clamp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_slope:4;
        RBus_UInt32  sat_thd:12;
        RBus_UInt32  res1:3;
        RBus_UInt32  sat_max:13;
    };
}ds_soft_clamp_sat_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_slope:4;
        RBus_UInt32  itn_thd:12;
        RBus_UInt32  res1:3;
        RBus_UInt32  itn_max:13;
    };
}ds_soft_clamp_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  merge_01_en:1;
        RBus_UInt32  merge_12_en:1;
        RBus_UInt32  merge_23_en:1;
        RBus_UInt32  merge_34_en:1;
        RBus_UInt32  merge_45_en:1;
        RBus_UInt32  merge_56_en:1;
        RBus_UInt32  merge_60_en:1;
        RBus_UInt32  del_hue_01:11;
    };
}ds_icm_merge_h_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_01:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_01:12;
    };
}ds_icm_merge_si_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_12:11;
    };
}ds_icm_merge_h_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_12:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_12:12;
    };
}ds_icm_merge_si_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_23:11;
    };
}ds_icm_merge_h_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_23:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_23:12;
    };
}ds_icm_merge_si_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_34:11;
    };
}ds_icm_merge_h_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_34:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_34:12;
    };
}ds_icm_merge_si_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_45:11;
    };
}ds_icm_merge_h_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_45:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_45:12;
    };
}ds_icm_merge_si_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_56:11;
    };
}ds_icm_merge_h_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_56:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_56:12;
    };
}ds_icm_merge_si_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  del_hue_60:11;
    };
}ds_icm_merge_h_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_60:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  del_itn_60:12;
    };
}ds_icm_merge_si_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_icm_si_clip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_icm_si_clip_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sha_s_byi_enable:1;
        RBus_UInt32  ssa_s_byi_enable:1;
        RBus_UInt32  sha_m_byi_enable:1;
        RBus_UInt32  ssa_m_byi_enable:1;
        RBus_UInt32  delta_i_new_mode_m_enable:1;
        RBus_UInt32  delta_i_new_mode_s_enable:1;
        RBus_UInt32  res1:9;
        RBus_UInt32  dsat_alpha_shift:2;
        RBus_UInt32  dhue_alpha_shift:1;
        RBus_UInt32  seg_debug_enable:1;
        RBus_UInt32  seg_debug_type_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg_debug_cm_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  seg_debug_seg_sel:3;
        RBus_UInt32  sha_s_enable:1;
        RBus_UInt32  ssa_s_enable:1;
        RBus_UInt32  sha_m_enable:1;
        RBus_UInt32  ssa_m_enable:1;
    };
}dm_seg_shy_adj_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  shy_address_sub_cm_sel:3;
        RBus_UInt32  shy_address_type_sel:3;
        RBus_UInt32  shy_m_s_sel:1;
        RBus_UInt32  shy_address_cm_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  shy_address_seg_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  write_random_access_en:1;
        RBus_UInt32  write_en:1;
        RBus_UInt32  read_en:1;
    };
}dm_seg_shy_sram_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  dvs_6:4;
        RBus_UInt32  dvs_5:4;
        RBus_UInt32  dvs_4:4;
        RBus_UInt32  dvs_3:4;
        RBus_UInt32  dvs_2:4;
        RBus_UInt32  dvs_1:4;
        RBus_UInt32  dvs_0:4;
    };
}dm_seg_shy_sram_bist1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  dvs_10_b:4;
        RBus_UInt32  dvs_10_a:4;
        RBus_UInt32  dvs_9:4;
        RBus_UInt32  dvs_8:4;
        RBus_UInt32  dvs_7:4;
    };
}dm_seg_shy_sram_bist2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  dvs_13_b:4;
        RBus_UInt32  dvs_13_a:4;
        RBus_UInt32  dvs_12_b:4;
        RBus_UInt32  dvs_12_a:4;
        RBus_UInt32  dvs_11_b:4;
        RBus_UInt32  dvs_11_a:4;
    };
}dm_seg_shy_sram_bist3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  dvse_13_b:1;
        RBus_UInt32  dvse_13_a:1;
        RBus_UInt32  dvse_12_b:1;
        RBus_UInt32  dvse_12_a:1;
        RBus_UInt32  dvse_11_b:1;
        RBus_UInt32  dvse_11_a:1;
        RBus_UInt32  dvse_10_b:1;
        RBus_UInt32  dvse_10_a:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dvse_9:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  dvse_8:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  dvse_7:1;
        RBus_UInt32  res5:1;
        RBus_UInt32  dvse_6:1;
        RBus_UInt32  dvse_5:1;
        RBus_UInt32  dvse_4:1;
        RBus_UInt32  dvse_3:1;
        RBus_UInt32  dvse_2:1;
        RBus_UInt32  dvse_1:1;
        RBus_UInt32  dvse_0:1;
    };
}dm_seg_shy_sram_bist0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  drf_fail_13:1;
        RBus_UInt32  drf_fail_12:1;
        RBus_UInt32  drf_fail_11:1;
        RBus_UInt32  drf_fail_10:1;
        RBus_UInt32  drf_fail_9:1;
        RBus_UInt32  drf_fail_8:1;
        RBus_UInt32  drf_fail_7:1;
        RBus_UInt32  drf_fail_6:1;
        RBus_UInt32  drf_fail_5:1;
        RBus_UInt32  drf_fail_4:1;
        RBus_UInt32  drf_fail_3:1;
        RBus_UInt32  drf_fail_2:1;
        RBus_UInt32  drf_fail_1:1;
        RBus_UInt32  drf_fail_0:1;
        RBus_UInt32  bist_fail_13:1;
        RBus_UInt32  bist_fail_12:1;
        RBus_UInt32  bist_fail_11:1;
        RBus_UInt32  bist_fail_10:1;
        RBus_UInt32  bist_fail_9:1;
        RBus_UInt32  bist_fail_8:1;
        RBus_UInt32  bist_fail_7:1;
        RBus_UInt32  bist_fail_6:1;
        RBus_UInt32  bist_fail_5:1;
        RBus_UInt32  bist_fail_4:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_0:1;
    };
}dm_seg_shy_sram_bist_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  d2:10;
    };
}dm_seg_shy_write_seg_random_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  value:12;
        RBus_UInt32  res2:6;
        RBus_UInt32  delta:10;
    };
}dm_seg_shy_read_seg_random_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  icm_crc_channel:1;
        RBus_UInt32  icm_crc_conti:1;
        RBus_UInt32  icm_crc_start:1;
    };
}icm_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  icm_crc_result:32;
    };
}icm_crc_result_RBUS;

#else //apply LITTLE_ENDIAN

//======COLOR_ICM register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm6_enable:1;
        RBus_UInt32  cm5_enable:1;
        RBus_UInt32  cm4_enable:1;
        RBus_UInt32  cm3_enable:1;
        RBus_UInt32  cm2_enable:1;
        RBus_UInt32  cm1_enable:1;
        RBus_UInt32  cm0_enable:1;
        RBus_UInt32  icm_dummy2:9;
        RBus_UInt32  cm_debug:3;
        RBus_UInt32  res1:2;
        RBus_UInt32  delta_i_smooth_enable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  merge_en:1;
        RBus_UInt32  icm_overlay:1;
        RBus_UInt32  icm_dummy1:4;
        RBus_UInt32  res3:1;
        RBus_UInt32  bypass_yuv2rgb_enable:1;
        RBus_UInt32  y_ctrl:1;
    };
}dm_icm_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}dm_icm_cm0_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_cm0_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm0_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm0_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}dm_icm_cm1_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_cm1_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm1_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm1_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}dm_icm_cm2_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_cm2_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm2_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm2_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}dm_icm_cm3_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_cm3_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm3_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm3_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}dm_icm_cm4_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_cm4_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm4_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm4_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}dm_icm_cm5_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_cm5_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm5_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm5_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}dm_icm_cm6_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_cm6_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm6_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm6_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm0_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm0_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm0_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm1_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm1_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm1_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm2_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm2_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm2_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm3_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm3_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm3_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm4_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm4_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm4_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm5_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm5_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm5_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}dm_icm_cm6_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm6_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}dm_icm_cm6_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_coring:8;
        RBus_UInt32  u_coring:8;
        RBus_UInt32  res1:16;
    };
}dm_uv_coring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hue_all:11;
        RBus_UInt32  dummy1802a178_31_11:21;
    };
}dm_hue_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_all:12;
        RBus_UInt32  res1:20;
    };
}dm_sat_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_all:12;
        RBus_UInt32  res1:20;
    };
}dm_itn_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_enable:1;
        RBus_UInt32  sat_enable:1;
        RBus_UInt32  neg_int_flag_en:1;
        RBus_UInt32  res1:25;
        RBus_UInt32  int_multi_clip_sel:1;
        RBus_UInt32  int_clip_sel:1;
        RBus_UInt32  sat_multi_clip_sel:1;
        RBus_UInt32  sat_clip_sel:1;
    };
}dm_soft_clamp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_max:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  sat_thd:12;
        RBus_UInt32  sat_slope:4;
    };
}dm_soft_clamp_sat_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_max:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  itn_thd:12;
        RBus_UInt32  itn_slope:4;
    };
}dm_soft_clamp_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_sat_select:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  sat_enable:1;
        RBus_UInt32  hist_sat_ok:1;
        RBus_UInt32  sat_hist_mode_sel:1;
        RBus_UInt32  auto_sat_new_mode:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  auto_sat_s_thre0:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  auto_sat_i_l_thre0:7;
        RBus_UInt32  res4:1;
        RBus_UInt32  auto_sat_i_u_thre0:7;
        RBus_UInt32  res5:1;
    };
}d_auto_sat_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_offset:8;
        RBus_UInt32  gain_hi:4;
        RBus_UInt32  gain_lo:4;
        RBus_UInt32  u_bound:4;
        RBus_UInt32  l_bound:4;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_hist3_ctrl_status:8;
        RBus_UInt32  sat_hist2_ctrl_status:8;
        RBus_UInt32  sat_hist1_ctrl_status:8;
        RBus_UInt32  sat_hist0_ctrl_status:8;
    };
}d_auto_sat_hist_ctrl_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pre_cnt:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_pre_count_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aft_cnt:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_after_count_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_sat_s_thre1:7;
        RBus_UInt32  auto_sat_i_l_thre1:7;
        RBus_UInt32  auto_sat_i_u_thre1:7;
        RBus_UInt32  res1:11;
    };
}d_auto_sat_hist1_thrd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_sat_s_thre2:7;
        RBus_UInt32  auto_sat_i_l_thre2:7;
        RBus_UInt32  auto_sat_i_u_thre2:7;
        RBus_UInt32  res1:11;
    };
}d_auto_sat_hist2_thrd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_sat_s_thre3:7;
        RBus_UInt32  auto_sat_i_l_thre3:7;
        RBus_UInt32  auto_sat_i_u_thre3:7;
        RBus_UInt32  res1:11;
    };
}d_auto_sat_hist3_thrd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_hist3_ctrl:8;
        RBus_UInt32  sat_hist2_ctrl:8;
        RBus_UInt32  sat_hist1_ctrl:8;
        RBus_UInt32  sat_hist0_ctrl:8;
    };
}d_auto_sat_hist_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  cnt_block:1;
        RBus_UInt32  hist_ctrl:2;
        RBus_UInt32  sram_read:1;
    };
}d_auto_sat_hist_read_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  sat_hist_sram_read_consistent_flag:1;
    };
}d_auto_sat_hist_read_flag_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_00_or_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_01_or_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_02_or_18_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_03_or_19_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_04_or_20_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_05_or_21_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_06_or_22_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_07_or_23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_08_or_24_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_09_or_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_10_or_26_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_11_or_27_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_12_or_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_13_or_29_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_14_or_30_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cnt_data:24;
        RBus_UInt32  res1:8;
    };
}d_auto_sat_hist_cnt_15_or_31_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  inside_enable:1;
        RBus_UInt32  hue_enable:1;
        RBus_UInt32  hist_hue_ok:1;
        RBus_UInt32  hue_hist_select:1;
        RBus_UInt32  hue_hist_mode_sel:1;
        RBus_UInt32  res1:27;
    };
}icm_auto_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hue_hist_itn_lb:8;
        RBus_UInt32  hue_hist_itn_hb:8;
        RBus_UInt32  hue_hist_sat_lb:8;
        RBus_UInt32  hue_hist_offset_add:8;
    };
}hue_hist_settings_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut0:24;
        RBus_UInt32  res1:8;
    };
}hue_count_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut1:24;
        RBus_UInt32  res1:8;
    };
}hue_count_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut2:24;
        RBus_UInt32  res1:8;
    };
}hue_count_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut3:24;
        RBus_UInt32  res1:8;
    };
}hue_count_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut4:24;
        RBus_UInt32  res1:8;
    };
}hue_count_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut5:24;
        RBus_UInt32  res1:8;
    };
}hue_count_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut6:24;
        RBus_UInt32  res1:8;
    };
}hue_count_06_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut7:24;
        RBus_UInt32  res1:8;
    };
}hue_count_07_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut8:24;
        RBus_UInt32  res1:8;
    };
}hue_count_08_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut9:24;
        RBus_UInt32  res1:8;
    };
}hue_count_09_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut10:24;
        RBus_UInt32  res1:8;
    };
}hue_count_0a_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut11:24;
        RBus_UInt32  res1:8;
    };
}hue_count_0b_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut12:24;
        RBus_UInt32  res1:8;
    };
}hue_count_0c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut13:24;
        RBus_UInt32  res1:8;
    };
}hue_count_0d_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut14:24;
        RBus_UInt32  res1:8;
    };
}hue_count_0e_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut15:24;
        RBus_UInt32  res1:8;
    };
}hue_count_0f_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut16:24;
        RBus_UInt32  res1:8;
    };
}hue_count_10_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut17:24;
        RBus_UInt32  res1:8;
    };
}hue_count_11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut18:24;
        RBus_UInt32  res1:8;
    };
}hue_count_12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut19:24;
        RBus_UInt32  res1:8;
    };
}hue_count_13_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut20:24;
        RBus_UInt32  res1:8;
    };
}hue_count_14_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut21:24;
        RBus_UInt32  res1:8;
    };
}hue_count_15_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut22:24;
        RBus_UInt32  res1:8;
    };
}hue_count_16_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut23:24;
        RBus_UInt32  res1:8;
    };
}hue_count_17_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut0:32;
    };
}hue_sum_00_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut1:32;
    };
}hue_sum_01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut2:32;
    };
}hue_sum_02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut3:32;
    };
}hue_sum_03_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut4:32;
    };
}hue_sum_04_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lut5:32;
    };
}hue_sum_05_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dsatbyitn_cm6_enable:1;
        RBus_UInt32  dsatbyitn_cm5_enable:1;
        RBus_UInt32  dsatbyitn_cm4_enable:1;
        RBus_UInt32  dsatbyitn_cm3_enable:1;
        RBus_UInt32  dsatbyitn_cm2_enable:1;
        RBus_UInt32  dsatbyitn_cm1_enable:1;
        RBus_UInt32  dsatbyitn_cm0_enable:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  dhuebyitn_cm6_enable:1;
        RBus_UInt32  dhuebyitn_cm5_enable:1;
        RBus_UInt32  dhuebyitn_cm4_enable:1;
        RBus_UInt32  dhuebyitn_cm3_enable:1;
        RBus_UInt32  dhuebyitn_cm2_enable:1;
        RBus_UInt32  dhuebyitn_cm1_enable:1;
        RBus_UInt32  dhuebyitn_cm0_enable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  itnlevel_debug_enable:1;
        RBus_UInt32  itnlevel_debug_cm_sel:3;
        RBus_UInt32  itnlevel_debug_satlevel_sel:2;
        RBus_UInt32  res3:10;
    };
}dm_adj_byitn_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm0_itn_lb:8;
        RBus_UInt32  cm1_itn_lb:8;
        RBus_UInt32  cm2_itn_lb:8;
        RBus_UInt32  cm3_itn_lb:8;
    };
}dm_adj_byitn_lb_cm0_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm4_itn_lb:8;
        RBus_UInt32  cm5_itn_lb:8;
        RBus_UInt32  cm6_itn_lb:8;
        RBus_UInt32  res1:8;
    };
}dm_adj_byitn_lb_cm4_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm0_itn_buffer:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  cm1_itn_buffer:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  cm2_itn_buffer:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  cm3_itn_buffer:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  cm4_itn_buffer:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  cm5_itn_buffer:3;
        RBus_UInt32  res6:1;
        RBus_UInt32  cm6_itn_buffer:3;
        RBus_UInt32  res7:5;
    };
}dm_adj_byitn_buf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm0_dsat:12;
        RBus_UInt32  cm0_dhue:11;
        RBus_UInt32  res1:9;
    };
}dm_adj_byitn_dsat_dhue_cm0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm1_dsat:12;
        RBus_UInt32  cm1_dhue:11;
        RBus_UInt32  res1:9;
    };
}dm_adj_byitn_dsat_dhue_cm1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm2_dsat:12;
        RBus_UInt32  cm2_dhue:11;
        RBus_UInt32  res1:9;
    };
}dm_adj_byitn_dsat_dhue_cm2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm3_dsat:12;
        RBus_UInt32  cm3_dhue:11;
        RBus_UInt32  res1:9;
    };
}dm_adj_byitn_dsat_dhue_cm3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm4_dsat:12;
        RBus_UInt32  cm4_dhue:11;
        RBus_UInt32  res1:9;
    };
}dm_adj_byitn_dsat_dhue_cm4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm5_dsat:12;
        RBus_UInt32  cm5_dhue:11;
        RBus_UInt32  res1:9;
    };
}dm_adj_byitn_dsat_dhue_cm5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm6_dsat:12;
        RBus_UInt32  cm6_dhue:11;
        RBus_UInt32  res1:9;
    };
}dm_adj_byitn_dsat_dhue_cm6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_01:11;
        RBus_UInt32  merge_60_en:1;
        RBus_UInt32  merge_56_en:1;
        RBus_UInt32  merge_45_en:1;
        RBus_UInt32  merge_34_en:1;
        RBus_UInt32  merge_23_en:1;
        RBus_UInt32  merge_12_en:1;
        RBus_UInt32  merge_01_en:1;
        RBus_UInt32  res1:14;
    };
}dm_icm_merge_h_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_01:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_01:12;
        RBus_UInt32  res2:4;
    };
}dm_icm_merge_si_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_12:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_merge_h_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_12:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_12:12;
        RBus_UInt32  res2:4;
    };
}dm_icm_merge_si_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_23:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_merge_h_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_23:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_23:12;
        RBus_UInt32  res2:4;
    };
}dm_icm_merge_si_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_34:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_merge_h_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_34:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_34:12;
        RBus_UInt32  res2:4;
    };
}dm_icm_merge_si_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_45:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_merge_h_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_45:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_45:12;
        RBus_UInt32  res2:4;
    };
}dm_icm_merge_si_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_56:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_merge_h_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_56:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_56:12;
        RBus_UInt32  res2:4;
    };
}dm_icm_merge_si_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_60:11;
        RBus_UInt32  res1:21;
    };
}dm_icm_merge_h_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_60:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_60:12;
        RBus_UInt32  res2:4;
    };
}dm_icm_merge_si_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_threshold:13;
        RBus_UInt32  res1:9;
        RBus_UInt32  si_clip_slope_mode:2;
        RBus_UInt32  si_clip_right_mode:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  si_clip_left_mode:3;
        RBus_UInt32  si_clip_en:1;
    };
}dm_icm_si_clip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_bottom_threshold:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  itn_top_threshold:14;
        RBus_UInt32  res2:2;
    };
}dm_icm_si_clip_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cm6_enable:1;
        RBus_UInt32  cm5_enable:1;
        RBus_UInt32  cm4_enable:1;
        RBus_UInt32  cm3_enable:1;
        RBus_UInt32  cm2_enable:1;
        RBus_UInt32  cm1_enable:1;
        RBus_UInt32  cm0_enable:1;
        RBus_UInt32  icm_dummy2:9;
        RBus_UInt32  cm_debug:3;
        RBus_UInt32  res1:2;
        RBus_UInt32  delta_i_smooth_enable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  merge_en:1;
        RBus_UInt32  icm_dummy1:6;
        RBus_UInt32  bypass_yuv2rgb_enable:1;
        RBus_UInt32  y_ctrl:1;
    };
}ds_icm_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}ds_icm_cm0_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_cm0_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm0_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm0_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}ds_icm_cm1_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_cm1_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm1_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm1_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}ds_icm_cm2_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_cm2_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm2_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm2_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}ds_icm_cm3_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_cm3_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm3_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm3_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}ds_icm_cm4_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_cm4_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm4_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm4_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}ds_icm_cm5_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_cm5_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm5_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm5_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  center:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  r_buffer:3;
        RBus_UInt32  r_range:3;
        RBus_UInt32  r_kernel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  l_buffer:3;
        RBus_UInt32  l_range:3;
        RBus_UInt32  l_kernel:3;
    };
}ds_icm_cm6_hue_range_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_center:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_cm6_del_hue_center_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right:11;
        RBus_UInt32  del_left:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm6_del_hue_left_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn:12;
        RBus_UInt32  del_sat:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm6_del_sat_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm0_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm0_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm0_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm1_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm1_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm1_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm2_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm2_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm2_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm3_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm3_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm3_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm4_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm4_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm4_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm5_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm5_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm5_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_right_kernel:11;
        RBus_UInt32  del_left_kernel:11;
        RBus_UInt32  res1:10;
    };
}ds_icm_cm6_del_hue_kernel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm6_del_sat_left_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_sat_range:12;
        RBus_UInt32  del_sat_kernel:12;
        RBus_UInt32  res1:8;
    };
}ds_icm_cm6_del_sat_right_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_coring:8;
        RBus_UInt32  u_coring:8;
        RBus_UInt32  res1:16;
    };
}ds_uv_coring_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hue_all:11;
        RBus_UInt32  res1:21;
    };
}ds_hue_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_all:12;
        RBus_UInt32  res1:20;
    };
}ds_sat_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_all:12;
        RBus_UInt32  res1:20;
    };
}ds_itn_all_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_enable:1;
        RBus_UInt32  sat_enable:1;
        RBus_UInt32  neg_int_flag_en:1;
        RBus_UInt32  res1:25;
        RBus_UInt32  int_multi_clip_sel:1;
        RBus_UInt32  int_clip_sel:1;
        RBus_UInt32  sat_multi_clip_sel:1;
        RBus_UInt32  sat_clip_sel:1;
    };
}ds_soft_clamp_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sat_max:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  sat_thd:12;
        RBus_UInt32  sat_slope:4;
    };
}ds_soft_clamp_sat_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  itn_max:13;
        RBus_UInt32  res1:3;
        RBus_UInt32  itn_thd:12;
        RBus_UInt32  itn_slope:4;
    };
}ds_soft_clamp_itn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_01:11;
        RBus_UInt32  merge_60_en:1;
        RBus_UInt32  merge_56_en:1;
        RBus_UInt32  merge_45_en:1;
        RBus_UInt32  merge_34_en:1;
        RBus_UInt32  merge_23_en:1;
        RBus_UInt32  merge_12_en:1;
        RBus_UInt32  merge_01_en:1;
        RBus_UInt32  res1:14;
    };
}ds_icm_merge_h_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_01:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_01:12;
        RBus_UInt32  res2:4;
    };
}ds_icm_merge_si_cm01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_12:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_merge_h_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_12:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_12:12;
        RBus_UInt32  res2:4;
    };
}ds_icm_merge_si_cm12_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_23:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_merge_h_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_23:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_23:12;
        RBus_UInt32  res2:4;
    };
}ds_icm_merge_si_cm23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_34:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_merge_h_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_34:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_34:12;
        RBus_UInt32  res2:4;
    };
}ds_icm_merge_si_cm34_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_45:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_merge_h_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_45:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_45:12;
        RBus_UInt32  res2:4;
    };
}ds_icm_merge_si_cm45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_56:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_merge_h_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_56:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_56:12;
        RBus_UInt32  res2:4;
    };
}ds_icm_merge_si_cm56_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_hue_60:11;
        RBus_UInt32  res1:21;
    };
}ds_icm_merge_h_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  del_itn_60:12;
        RBus_UInt32  res1:4;
        RBus_UInt32  del_sat_60:12;
        RBus_UInt32  res2:4;
    };
}ds_icm_merge_si_cm60_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_icm_si_clip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}ds_icm_si_clip_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ssa_m_enable:1;
        RBus_UInt32  sha_m_enable:1;
        RBus_UInt32  ssa_s_enable:1;
        RBus_UInt32  sha_s_enable:1;
        RBus_UInt32  seg_debug_seg_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  seg_debug_cm_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  seg_debug_type_sel:1;
        RBus_UInt32  seg_debug_enable:1;
        RBus_UInt32  dhue_alpha_shift:1;
        RBus_UInt32  dsat_alpha_shift:2;
        RBus_UInt32  res3:9;
        RBus_UInt32  delta_i_new_mode_s_enable:1;
        RBus_UInt32  delta_i_new_mode_m_enable:1;
        RBus_UInt32  ssa_m_byi_enable:1;
        RBus_UInt32  sha_m_byi_enable:1;
        RBus_UInt32  ssa_s_byi_enable:1;
        RBus_UInt32  sha_s_byi_enable:1;
    };
}dm_seg_shy_adj_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  read_en:1;
        RBus_UInt32  write_en:1;
        RBus_UInt32  write_random_access_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  shy_address_seg_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  shy_address_cm_sel:3;
        RBus_UInt32  shy_m_s_sel:1;
        RBus_UInt32  shy_address_type_sel:3;
        RBus_UInt32  shy_address_sub_cm_sel:3;
        RBus_UInt32  res3:14;
    };
}dm_seg_shy_sram_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dvs_0:4;
        RBus_UInt32  dvs_1:4;
        RBus_UInt32  dvs_2:4;
        RBus_UInt32  dvs_3:4;
        RBus_UInt32  dvs_4:4;
        RBus_UInt32  dvs_5:4;
        RBus_UInt32  dvs_6:4;
        RBus_UInt32  res1:4;
    };
}dm_seg_shy_sram_bist1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dvs_7:4;
        RBus_UInt32  dvs_8:4;
        RBus_UInt32  dvs_9:4;
        RBus_UInt32  dvs_10_a:4;
        RBus_UInt32  dvs_10_b:4;
        RBus_UInt32  res1:12;
    };
}dm_seg_shy_sram_bist2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dvs_11_a:4;
        RBus_UInt32  dvs_11_b:4;
        RBus_UInt32  dvs_12_a:4;
        RBus_UInt32  dvs_12_b:4;
        RBus_UInt32  dvs_13_a:4;
        RBus_UInt32  dvs_13_b:4;
        RBus_UInt32  res1:8;
    };
}dm_seg_shy_sram_bist3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dvse_0:1;
        RBus_UInt32  dvse_1:1;
        RBus_UInt32  dvse_2:1;
        RBus_UInt32  dvse_3:1;
        RBus_UInt32  dvse_4:1;
        RBus_UInt32  dvse_5:1;
        RBus_UInt32  dvse_6:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  dvse_7:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dvse_8:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  dvse_9:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  dvse_10_a:1;
        RBus_UInt32  dvse_10_b:1;
        RBus_UInt32  dvse_11_a:1;
        RBus_UInt32  dvse_11_b:1;
        RBus_UInt32  dvse_12_a:1;
        RBus_UInt32  dvse_12_b:1;
        RBus_UInt32  dvse_13_a:1;
        RBus_UInt32  dvse_13_b:1;
        RBus_UInt32  res5:10;
    };
}dm_seg_shy_sram_bist0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail_0:1;
        RBus_UInt32  bist_fail_1:1;
        RBus_UInt32  bist_fail_2:1;
        RBus_UInt32  bist_fail_3:1;
        RBus_UInt32  bist_fail_4:1;
        RBus_UInt32  bist_fail_5:1;
        RBus_UInt32  bist_fail_6:1;
        RBus_UInt32  bist_fail_7:1;
        RBus_UInt32  bist_fail_8:1;
        RBus_UInt32  bist_fail_9:1;
        RBus_UInt32  bist_fail_10:1;
        RBus_UInt32  bist_fail_11:1;
        RBus_UInt32  bist_fail_12:1;
        RBus_UInt32  bist_fail_13:1;
        RBus_UInt32  drf_fail_0:1;
        RBus_UInt32  drf_fail_1:1;
        RBus_UInt32  drf_fail_2:1;
        RBus_UInt32  drf_fail_3:1;
        RBus_UInt32  drf_fail_4:1;
        RBus_UInt32  drf_fail_5:1;
        RBus_UInt32  drf_fail_6:1;
        RBus_UInt32  drf_fail_7:1;
        RBus_UInt32  drf_fail_8:1;
        RBus_UInt32  drf_fail_9:1;
        RBus_UInt32  drf_fail_10:1;
        RBus_UInt32  drf_fail_11:1;
        RBus_UInt32  drf_fail_12:1;
        RBus_UInt32  drf_fail_13:1;
        RBus_UInt32  res1:4;
    };
}dm_seg_shy_sram_bist_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  d2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  v2:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_write_seg_random_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  delta:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  value:12;
        RBus_UInt32  res2:4;
    };
}dm_seg_shy_read_seg_random_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  icm_crc_start:1;
        RBus_UInt32  icm_crc_conti:1;
        RBus_UInt32  icm_crc_channel:1;
        RBus_UInt32  res1:29;
    };
}icm_crc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  icm_crc_result:32;
    };
}icm_crc_result_RBUS;




#endif 


#endif 
