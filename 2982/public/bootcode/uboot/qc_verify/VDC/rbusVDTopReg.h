/**
* @file rbusVDTopReg.h
* RBus systemc program.
*
* @author Yu-Cheng Huang
* @email timhuang@realtek.com.tw
* @date 2013/12/23
* @version 802
* @ingroup model_rbus
*
*/

#ifndef _RBUS_VDTOP_REG_H_
#define _RBUS_VDTOP_REG_H_

#include "rbusTypes.h"




// VDTOP Register Address
#define VDC_VIDEO_CONTROL0_VADDR                 (0xb8003000)
#define VDC_VIDEO_CONTROL1_VADDR                 (0xb8003004)
#define VDC_VIDEO_STATUS_REG1_VADDR              (0xb8003008)
#define VDC_VIDEO_STATUS_REG2_VADDR              (0xb800300c)
#define VDC_VIDEO_STATUS_REG3_VADDR              (0xb8003010)
#define VDC_HDTO_INC_STATUS_VADDR                (0xb8003014)
#define VDC_CDTO_INC_STATUS_VADDR                (0xb8003018)
#define VDC_AVG_BURST_MAG_STATUS_VADDR           (0xb800301c)
#define VDC_AGC_DGAIN_STATUS_VADDR               (0xb8003020)
#define VDC_CMAG_STATUS_VADDR                    (0xb8003024)
#define VDC_CGAIN_STATUS_VADDR                   (0xb8003028)
#define VDC_CORDIC_FREQ_STATUS_VADDR             (0xb800302c)
#define VDC_MEASURE_FIRST_V_VADDR                (0xb8003030)
#define VDC_MEASURE_SECOND_V_VADDR               (0xb8003034)
#define VDC_PORCH_HEIGHT_M_VADDR                 (0xb8003038)
#define VDC_NOISE_STATUS_VADDR                   (0xb800303c)
#define VDC_NOISE_THRESHOLD_VADDR                (0xb8003040)
#define VDC_HSYNC_DTO_INC_VADDR                  (0xb8003050)
#define VDC_CHROMA_DTO_INC_VADDR                 (0xb8003054)
#define VDC_CHIP_VER_VADDR                       (0xb8003058)
#define VDC_BLANK_VID_OFFSET_VALUE_VADDR         (0xb800305c)
#define VDC_LUMA_CONTRAST_ADJ_VADDR              (0xb8003060)
#define VDC_LUMA_BRIGHTNESS_ADJ_VADDR            (0xb8003064)
#define VDC_CHROMA_SATURATION_ADJ_VADDR          (0xb8003068)
#define VDC_CHROMA_HUE_PHASE_ADJ_VADDR           (0xb800306c)
#define VDC_BLUE_SCREEN_Y_VADDR                  (0xb8003070)
#define VDC_BLUE_SCREEN_CB_VADDR                 (0xb8003074)
#define VDC_BLUE_SCREEN_CR_VADDR                 (0xb8003078)
#define VDC_OUTPUT_CONTROL_VADDR                 (0xb800307c)
#define VDC_INOUT_CTRL_VADDR                     (0xb8003080)
#define VDC_AVOUT_FIFO_STATUS_VADDR              (0xb8003084)
#define VDC_AVOUT_IFDEBUG_VADDR                  (0xb8003088)
#define VDC_AGC_PEAK_NOMINAL_VADDR               (0xb8003090)
#define VDC_AGC_PEAK_AND_GATE_CTRL_VADDR         (0xb8003094)
#define VDC_AGC_PEAK_CTRL_VADDR                  (0xb8003098)
#define VDC_VIDEO_CONTROL2_VADDR                 (0xb800309c)
#define VDC_LUMA_AGC_VALUE_VADDR                 (0xb80030a0)
#define VDC_AGC_GATE_START_VADDR                 (0xb80030a4)
#define VDC_AGC_GATE_WIDTH_VADDR                 (0xb80030a8)
#define VDC_AGC_BP_DELAY_VADDR                   (0xb80030ac)
#define VDC_CLAMPAGC_COMPLUMA_NEW_THRESHOLD2_VADDR  (0xb80030b0)
#define VDC_CLAMPAGC_COMPLUMA_NEW_THRESHOLD1_VADDR  (0xb80030b4)
#define VDC_CLAMPAGC_COMPLUMA_NEW_CONTROL_VADDR  (0xb80030b8)
#define VDC_VSYNC_AGC_MIN_VADDR                  (0xb80030bc)
#define VDC_VSYNC_AGC_LOCKOUT_END_VADDR          (0xb80030c0)
#define VDC_CHARGE_PUMP_DELAY_CONTROL_VADDR      (0xb80030c4)
#define VDC_CHARGE_PUMP_ADJUSTMENT_VADDR         (0xb80030c8)
#define VDC_CHARGE_PUMP_DELAY_VADDR              (0xb80030cc)
#define VDC_AGC_GATE_TH_SWAP_VADDR               (0xb80030d0)
#define VDC_NEW_CLAMPAGC_CTRL_VADDR              (0xb80030d4)
#define VDC_MEASURE_DC_ROUGH_DN_VADDR            (0xb80030d8)
#define VDC_MEASURE_DC_ROUGH_UP_VADDR            (0xb80030dc)
#define VDC_MEASURE_DC_TH_DN_VADDR               (0xb80030e0)
#define VDC_MEASURE_DC_TH_UP_VADDR               (0xb80030e4)
#define VDC_VSAG_CNTL_1_VADDR                    (0xb80030e8)
#define VDC_PEAK_VSAG_VADDR                      (0xb80030ec)
#define VDC_KILL_FIELD_VADDR                     (0xb80030f0)
#define VDC_FIELD_KILL_MUN_VADDR                 (0xb80030f4)
#define VDC_KILL_GATE_UP_VADDR                   (0xb80030f8)
#define VDC_KILL_GATE_DN_VADDR                   (0xb80030fc)
#define VDC_SYNCMIDPT_VADDR                      (0xb8003100)
#define VDC_SYNCMIDPT_FIX_ADD_VALUE_VADDR        (0xb8003104)
#define VDC_LPFSYNC_VADDR                        (0xb8003108)
#define VDC_SPIKE_MIN_VADDR                      (0xb800310c)
#define VDC_SPIKE_MAX_VADDR                      (0xb8003110)
#define VDC_SPIKE_DETECTED_UP_VADDR              (0xb8003114)
#define VDC_SPIKE_DETECTED_DN_VADDR              (0xb8003118)
#define VDC_LPFSYNC_PLUS_DC_VADDR                (0xb800311c)
#define VDC_HDETECT_ERR_VAR_CTRL_VADDR           (0xb8003128)
#define VDC_HDETECT_ERR_VAR_STATUS_VADDR         (0xb800312c)
#define VDC_LOCK_COUNT_VADDR                     (0xb8003130)
#define VDC_H_LOOP_MAXSTATE_VADDR                (0xb8003134)
#define VDC_CLAMPAGC_CTRL0_VADDR                 (0xb8003138)
#define VDC_CLAMPAGC_NEW_SYNC_START_VADDR        (0xb800313c)
#define VDC_CLAMPAGC_NEW_SYNC_END_VADDR          (0xb8003140)
#define VDC_CLAMPAGC_NEW_BACKPORCH_START_VADDR   (0xb8003144)
#define VDC_CLAMPAGC_NEW_BACKPORCH_END_VADDR     (0xb8003148)
#define VDC_HDETECT_PHASE_SEL_VADDR              (0xb800314c)
#define VDC_HDETECT_COUNTER_TIP_START_VADDR      (0xb8003150)
#define VDC_HDETECT_COUNTER_TIP_END_VADDR        (0xb8003154)
#define VDC_HDETECT_COUNTER_BACKPORCH_START_VADDR  (0xb8003158)
#define VDC_HDETECT_COUNTER_BACKPORCH_END_VADDR  (0xb800315c)
#define VDC_HPLL_INTEGRAL_CTRL_VADDR             (0xb8003160)
#define VDC_HDETECT_LOOPFILTER_SW_VADDR          (0xb8003164)
#define VDC_HDETECT_LOOPFILTER_DCTRL_VADDR       (0xb8003168)
#define VDC_HSYNC_PULSE_START_VADDR              (0xb800316c)
#define VDC_HSYNC_PULSE_WIDTH_VADDR              (0xb8003170)
#define VDC_CHROMA_HRESAMPLER_CONTROL_VADDR      (0xb8003174)
#define VDC_HPLL_KP_0_VADDR                      (0xb8003178)
#define VDC_HPLL_KP_1_VADDR                      (0xb800317c)
#define VDC_HPLL_KP_2_VADDR                      (0xb8003180)
#define VDC_HPLL_KP_3_VADDR                      (0xb8003184)
#define VDC_HPLL_KP_4_VADDR                      (0xb8003188)
#define VDC_HPLL_KP_5_VADDR                      (0xb800318c)
#define VDC_HPLL_KI_0_VADDR                      (0xb8003190)
#define VDC_HPLL_KI_1_VADDR                      (0xb8003194)
#define VDC_HPLL_KI_2_VADDR                      (0xb8003198)
#define VDC_HPLL_KI_3_VADDR                      (0xb800319c)
#define VDC_HPLL_KI_4_VADDR                      (0xb80031a0)
#define VDC_HPLL_KI_5_VADDR                      (0xb80031a4)
#define VDC_SECOND_PLL_GAIN_VADDR                (0xb80031a8)
#define VDC_SECOND_PLL_GAIN1_VADDR               (0xb80031ac)
#define VDC_SECOND_PLL_GAIN2_VADDR               (0xb80031b0)
#define VDC_SECOND_PLL_GAIN3_VADDR               (0xb80031b4)
#define VDC_SECOND_PLL_GAIN4_VADDR               (0xb80031b8)
#define VDC_UNDER_NEW_TH1_VADDR                  (0xb80031bc)
#define VDC_UNDER_NEW_TH2_VADDR                  (0xb80031c0)
#define VDC_UNDER_NEW_TH3_VADDR                  (0xb80031c4)
#define VDC_DC_COCH_SEPERATE_1_VADDR             (0xb80031c8)
#define VDC_DC_COCH_SEPERATE_2_VADDR             (0xb80031cc)
#define VDC_HSYNC_RISING_VADDR                   (0xb80031d0)
#define VDC_HSYNC_PHASE_OFFSET_VADDR             (0xb80031d4)
#define VDC_HSYNC_GATE_START_VADDR               (0xb80031d8)
#define VDC_HSYNC_GATE_END_VADDR                 (0xb80031dc)
#define VDC_HSYNC_TIP_START_VADDR                (0xb80031e0)
#define VDC_HSYNC_TIP_END_VADDR                  (0xb80031e4)
#define VDC_HSYNC_RISING_START_VADDR             (0xb80031e8)
#define VDC_HSYNC_RISING_END_VADDR               (0xb80031ec)
#define VDC_BACKPROCH_START_VADDR                (0xb80031f0)
#define VDC_BACKPORCH_END_VADDR                  (0xb80031f4)
#define VDC_HBLANK_START_VADDR                   (0xb80031f8)
#define VDC_HBLANK_END_VADDR                     (0xb80031fc)
#define VDC_BURST_GATE_START_VADDR               (0xb8003200)
#define VDC_BURST_GATE_END_VADDR                 (0xb8003204)
#define VDC_HACTIVE_START_VADDR                  (0xb8003208)
#define VDC_HACTIVE_WIDTH_VADDR                  (0xb800320c)
#define VDC_HDETECT_ERR_TH1_VADDR                (0xb8003210)
#define VDC_HDETECT_ERR_TH2_VADDR                (0xb8003214)
#define VDC_CSTATE_STATUS_VADDR                  (0xb8003218)
#define VDC_HDETECT_GATE_CTRL_VADDR              (0xb800321c)
#define VDC_HDETECT_GATE_COEF1_VADDR             (0xb8003220)
#define VDC_HDETECT_GATE_COEF2_VADDR             (0xb8003224)
#define VDC_HDETECT_VPHASE_STATUS_VADDR          (0xb8003228)
#define VDC_HDETECT_VPHASEDIFF_STATUS_VADDR      (0xb800322c)
#define VDC_NOISE_VBI_THRESHOLD_VADDR            (0xb8003230)
#define VDC_VBI_CO_CH_CTRL0_VADDR                (0xb8003234)
#define VDC_VBI_CO_CH_CTRL1_VADDR                (0xb8003238)
#define VDC_VBI_CO_CH_CTRL2_VADDR                (0xb800323c)
#define VDC_MV_DETECT_WINDOW_VADDR               (0xb8003240)
#define VDC_MV_BURSTGATE_START_VADDR             (0xb8003244)
#define VDC_MV_BURSTGATE_END_VADDR               (0xb8003248)
#define VDC_COLOR_INVERSE_CONTROL_VADDR          (0xb800324c)
#define VDC_H_ERR_CONSTRAINT_1_VADDR             (0xb8003250)
#define VDC_H_ERR_CONSTRAINT_2_VADDR             (0xb8003254)
#define VDC_H_RESTORE_HDTO_1_VADDR               (0xb8003258)
#define VDC_H_RESTORE_HDTO_2_VADDR               (0xb800325c)
#define VDC_IF_WRONG_PC_VADDR                    (0xb8003260)
#define VDC_CPLL_STABILITY_OBSERVE_1_VADDR       (0xb8003264)
#define VDC_CPLL_STABILITY_OBSERVE_2_VADDR       (0xb8003268)
#define VDC_CPLL_STABILITY_OBSERVE_3_VADDR       (0xb800326c)
#define VDC_HPLL_STABILITY_OBSERVE_1_VADDR       (0xb8003270)
#define VDC_HPLL_STABILITY_OBSERVE_2_VADDR       (0xb8003274)
#define VDC_HPLL_STABILITY_OBSERVE_3_VADDR       (0xb8003278)
#define VDC_H_PHASE_DIFF_STATISTICS_SET_1_VADDR  (0xb800327c)
#define VDC_H_PHASE_DIFF_STATISTICS_SET_2_VADDR  (0xb8003280)
#define VDC_H_PHASE_DIFF_STATISTICS_SET_3_VADDR  (0xb8003284)
#define VDC_H_PHASE_DIFF_STATISTICS_SET_4_VADDR  (0xb8003288)
#define VDC_H_PHASE_DIFF_STATISTICS_SET_5_VADDR  (0xb800328c)
#define VDC_H_PHASE_DIFF_SEC1_HISTOGRAM_1_VADDR  (0xb8003290)
#define VDC_H_PHASE_DIFF_SEC1_HISTOGRAM_2_VADDR  (0xb8003294)
#define VDC_H_PHASE_DIFF_SEC2_HISTOGRAM_1_VADDR  (0xb8003298)
#define VDC_H_PHASE_DIFF_SEC2_HISTOGRAM_2_VADDR  (0xb800329c)
#define VDC_DATA_LEVEL_STATISTICS_SET_1_VADDR    (0xb80032a0)
#define VDC_DATA_LEVEL_STATISTICS_SEC1_VADDR     (0xb80032a4)
#define VDC_DATA_LEVEL_STATISTICS_SEC2_VADDR     (0xb80032a8)
#define VDC_DATA_LEVEL_STATISTICS_SEC3_VADDR     (0xb80032ac)
#define VDC_DATA_LEVEL_STATISTICS_SEC4_VADDR     (0xb80032b0)
#define VDC_DATA_LEVEL_STATISTICS_SEC5_VADDR     (0xb80032b4)
#define VDC_DATA_LEVEL_STATISTICS_SEC6_VADDR     (0xb80032b8)
#define VDC_DATA_LEVEL_STATISTICS_SEC7_VADDR     (0xb80032bc)
#define VDC_DATA_LEVEL_STATISTICS_SEC8_VADDR     (0xb80032c0)
#define VDC_VSYNC_CNTL_VADDR                     (0xb8003300)
#define VDC_VSYNC_TIME_CONST_VADDR               (0xb8003304)
#define VDC_VSYNC_TIME_CONST2_VADDR              (0xb8003308)
#define VDC_VSYNC_TIME_CONST1_VADDR              (0xb800330c)
#define VDC_SERRATION_TH_VADDR                   (0xb8003310)
#define VDC_NO_SIGNAL_DEC_VADDR                  (0xb8003314)
#define VDC_VACTIVE_START_VADDR                  (0xb8003318)
#define VDC_VACTIVE_HEIGHT_VADDR                 (0xb800331c)
#define VDC_VSYNC_H_MIN_VADDR                    (0xb8003320)
#define VDC_VSYNC_H_MAX_VADDR                    (0xb8003324)
#define VDC_VSYNC_VBI_MIN_VADDR                  (0xb8003328)
#define VDC_VSYNC_VBI_LOCKOUT_END_VADDR          (0xb800332c)
#define VDC_MIDPT_CTRL_VADDR                     (0xb8003330)
#define VDC_MIDPT_FIX_ADD_VALUE_VADDR            (0xb8003334)
#define VDC_MIDPT_625_DC_TH_VADDR                (0xb8003338)
#define VDC_SYNC_DC_OFFSET_TH1_VADDR             (0xb800333c)
#define VDC_SYNC_DC_OFFSET_TH_VADDR              (0xb8003340)
#define VDC_SYNC_MIDPT_H_VADDR                   (0xb8003344)
#define VDC_SYNC_MIDPT_V_VADDR                   (0xb8003348)
#define VDC_SYNC_MIDPT_V2_VADDR                  (0xb800334c)
#define VDC_ADC_27_LPF_COEF_1_VADDR              (0xb8003350)
#define VDC_ADC_27_LPF_COEF_2_VADDR              (0xb8003354)
#define VDC_ADC_27_LPF_COEF_3_VADDR              (0xb8003358)
#define VDC_ADC_27_LPF_COEF_4_VADDR              (0xb800335c)
#define VDC_ADC_27_LPF_COEF_5_VADDR              (0xb8003360)
#define VDC_ADC_27_LPF_COEF_6_VADDR              (0xb8003364)
#define VDC_VDETECT_LINE_LENGHT_VADDR            (0xb8003368)
#define VDC_VDETECT_WINDOW_CTRL_VADDR            (0xb800336c)
#define VDC_VDETECT_WINDOW_TH_VADDR              (0xb8003370)
#define VDC_NEW_VDETECT_CTRL_VADDR               (0xb8003374)
#define VDC_NEW_VDETECT_LOOP_TH2_VADDR           (0xb8003378)
#define VDC_NEW_VDETECT_LOOP_TH1_VADDR           (0xb800337c)
#define VDC_NEW_VDETECT_DIFF_OFFSET_VADDR        (0xb8003380)
#define VDC_VSYNC_FINE_START_VADDR               (0xb8003384)
#define VDC_VSYNC_FINE_END_VADDR                 (0xb8003388)
#define VDC_NO_VSYNC_TH_VADDR                    (0xb800338c)
#define VDC_NEW_VDETECT_VPHASE_TH_VADDR          (0xb8003390)
#define VDC_NEW_VDETECT_TH1_VADDR                (0xb8003394)
#define VDC_NEW_VDETECT_TH2_VADDR                (0xb8003398)
#define VDC_NEW_VDETECT_TH3_VADDR                (0xb800339c)
#define VDC_NEW_VDETECT_TH4_VADDR                (0xb80033a0)
#define VDC_VSTATE_CTRL0_VADDR                   (0xb80033b0)
#define VDC_VSTATE_CTRL1_VADDR                   (0xb80033b4)
#define VDC_VSTATE_CTRL2_VADDR                   (0xb80033b8)
#define VDC_VSTATE_CTRL3_VADDR                   (0xb80033bc)
#define VDC_VLOOP0_TC1_VADDR                     (0xb80033c0)
#define VDC_VLOOP0_TC2_VADDR                     (0xb80033c4)
#define VDC_VLOOP2_TC1_VADDR                     (0xb80033c8)
#define VDC_VLOOP2_TC2_VADDR                     (0xb80033cc)
#define VDC_VLOOP3_TC1_VADDR                     (0xb80033d0)
#define VDC_VLOOP3_TC2_VADDR                     (0xb80033d4)
#define VDC_VLOOP_TC3_VADDR                      (0xb80033d8)
#define VDC_VLOCK_COUNT_VADDR                    (0xb80033dc)
#define VDC_VLOCK_WINDOW_VADDR                   (0xb80033e0)
#define VDC_VLOCK_PHASE_PLUS_VADDR               (0xb80033e4)
#define VDC_VLINE_ADJ_CNT_A_VADDR                (0xb80033e8)
#define VDC_VLINE_ADJ_CNT_B_VADDR                (0xb80033ec)
#define VDC_TABLE_HACTIVE_WIDTH_VADDR            (0xb80033f0)
#define VDC_VSYNC_PLL_FREERUN_MUX_VADDR          (0xb80033f4)
#define VDC_CHROMA_AGC_VADDR                     (0xb8003400)
#define VDC_CHROMA_KILL_VADDR                    (0xb8003404)
#define VDC_CHROMA_LOCK_CONFIG_VADDR             (0xb8003408)
#define VDC_CHROMA_LOOPFILTER_GAIN_VADDR         (0xb800340c)
#define VDC_CHROMA_LOOPFILTER_STATE_VADDR        (0xb8003410)
#define VDC_CHROMA_AUTOPOS_VADDR                 (0xb8003414)
#define VDC_CKILL_LB_SEL_VADDR                   (0xb8003418)
#define VDC_CKILL_GAIN_KILL_THL_VADDR            (0xb800341c)
#define VDC_CSTATE_CTRL_VADDR                    (0xb8003420)
#define VDC_BADEDIT_TH_VADDR                     (0xb8003424)
#define VDC_BADPHASE_TH_VADDR                    (0xb8003428)
#define VDC_CSTATE_LINE_NUM_VADDR                (0xb800342c)
#define VDC_CHROMA_AGC_PEAK_CTRL_VADDR           (0xb8003430)
#define VDC_CHROMA_AGC_PEAK_NOMINAL_VADDR        (0xb8003434)
#define VDC_CLOSE_CKILL_LOOPFILTER_VADDR         (0xb8003438)
#define VDC_CAGC_PEAK_CTRL1_VADDR                (0xb800343c)
#define VDC_CAGC_PEAK_CTRL2_VADDR                (0xb8003440)
#define VDC_CAGC_PEAK_CTRL3_VADDR                (0xb8003444)
#define VDC_CHROMA_DELAY_CTRL_VADDR              (0xb8003448)
#define VDC_BURST_CGAIN_CTRL_VADDR               (0xb800344c)
#define VDC_BURST_CGAIN_MAG_TH_VADDR             (0xb8003450)
#define VDC_FLAG358_CDTO_INC4_VADDR              (0xb8003454)
#define VDC_SEPARATE_443_358_NEW_FUNCTION_1_VADDR  (0xb8003458)
#define VDC_SEPARATE_443_358_NEW_FUNCTION_2_VADDR  (0xb800345c)
#define VDC_SEPARATE_443_358_NEW_FUNCTION_3_VADDR  (0xb8003460)
#define VDC_BURST_LOCATION_STATUS_1_VADDR        (0xb8003464)
#define VDC_BURST_LOCATION_STATUS_2_VADDR        (0xb8003468)
#define VDC_BURST_LOCATION_HSYNC_VADDR           (0xb800346c)
#define VDC_BURST_LOCATION_FW_CNTL_VADDR         (0xb8003470)
#define VDC_Y_PATH_EQ_FILTER_VADDR               (0xb8003474)
#define VDC_Y_PATH_EQ_FILTER_R_VADDR             (0xb8003478)
#define VDC_PALM_FLAG_COMPENSATION1_VADDR        (0xb8003490)
#define VDC_PALM_FLAG_COMPENSATION2_VADDR        (0xb8003494)
#define VDC_MANUAL_MODE_VADDR                    (0xb80034a0)
#define VDC_MODE_DETECTION_STATUS_VADDR          (0xb80034a4)
#define VDC_STATISTIC_AND_DISABLE_MODE_VADDR     (0xb80034a8)
#define VDC_PREFER_MODE_VADDR                    (0xb80034ac)
#define VDC_STATE_MACHINE_FIX_MODE_VADDR         (0xb80034b0)
#define VDC_VD_BASIC_REGISTER_ENABLE_VADDR       (0xb80034b4)
#define VDC_AUTO_MODE_S_M_STATISTIC_VADDR        (0xb80034b8)
#define VDC_AUTO_POS_CTRL_VADDR                  (0xb80034c0)
#define VDC_AUTO_POS_CTRL_2_VADDR                (0xb80034c4)
#define VDC_FLAG358_CTRL_VADDR                   (0xb80034c8)
#define VDC_NO_BURST_MAG_TH_VADDR                (0xb80034cc)
#define VDC_NO_BURST_MAG_FILTER_TH_VADDR         (0xb80034d0)
#define VDC_NO_BURST_443_CTRL_VADDR              (0xb80034d4)
#define VDC_FLAG358_SECAM_HCOUNT_RESET_CTRL_VADDR  (0xb80034d8)
#define VDC_FLAG358_SECAM_PHASE_DIFF_DR_VADDR    (0xb80034dc)
#define VDC_FLAG358_SECAM_PHASE_DIFF_DB_VADDR    (0xb80034e0)
#define VDC_BURST_MAG_TH_358_VADDR               (0xb80034e4)
#define VDC_AUTO_MODE_TABLE1_VADDR               (0xb80034f0)
#define VDC_AUTO_MODE_TABLE2_VADDR               (0xb80034f4)
#define VDC_AUTO_MODE_TABLE3_VADDR               (0xb80034f8)
#define VDC_AUTO_MODE_TABLE4_VADDR               (0xb80034fc)
#define VDC_AUTO_MODE_TABLE5_VADDR               (0xb8003500)
#define VDC_AUTO_MODE_TABLE6_VADDR               (0xb8003504)
#define VDC_FLAG_625_COUNTER_VADDR               (0xb8003508)
#define VDC_FLAG_443_COUNTER_VADDR               (0xb800350c)
#define VDC_SECAM_FLAG_COUNTER_VADDR             (0xb8003510)
#define VDC_PALM_FLAG_COUNTER_VADDR              (0xb8003514)
#define VDC_BURST_VALID_COUNTER_VADDR            (0xb8003518)
#define VDC_MIDPOINT_ADJ_VADDR                   (0xb800351c)
#define VDC_FREQ_FLAG_THRESHOLD_VADDR            (0xb8003520)
#define VDC_FREQ_VALID_MAX_VADDR                 (0xb8003524)
#define VDC_FREQ_VALID_INNER_VADDR               (0xb8003528)
#define VDC_FREQ_VALID_MIN_VADDR                 (0xb800352c)
#define VDC_SECAM_FLAG_COUNTER_MAX_VADDR         (0xb8003530)
#define VDC_SECAM_FLAG_COUNTER_MIN_VADDR         (0xb8003534)
#define VDC_PALM_FLAG_PHASE_ADJ_VADDR            (0xb8003538)
#define VDC_BURST_LOWER_LIMIT_VADDR              (0xb800353c)
#define VDC_BURST_MAG_CHOICE_VADDR               (0xb8003540)
#define VDC_NEW_358_CTRL_VADDR                   (0xb8003550)
#define VDC_NEW_358_CNT_UP_VADDR                 (0xb8003554)
#define VDC_NEW_358_CNT_DN_VADDR                 (0xb8003558)
#define VDC_SEP_COUNT_TH_VADDR                   (0xb800355c)
#define VDC_SEP_BURST_START0_VADDR               (0xb8003560)
#define VDC_SEP_BURST_END0_VADDR                 (0xb8003564)
#define VDC_SEP_BURST_RO1_VADDR                  (0xb8003568)
#define VDC_SEP_BURST_RO2_VADDR                  (0xb800356c)
#define VDC_SEP_BURST_RO3_VADDR                  (0xb8003570)
#define VDC_SEP_BURST_TH1_VADDR                  (0xb8003574)
#define VDC_SEP_BURST_FLAG1_VADDR                (0xb8003578)
#define VDC_AUTOMODE_443358PK_CTRL_VADDR         (0xb800357c)
#define VDC_DARK_CPLL_CDETECT_1_VADDR            (0xb8003580)
#define VDC_DARK_CPLL_CDETECT_2_VADDR            (0xb8003584)
#define VDC_DARK_CPLL_PAL_VADDR                  (0xb8003588)
#define VDC_DARK_CPLL_CHROMALOCK_VADDR           (0xb800358c)
#define VDC_DARK_CPLL_CONTROLL_VADDR             (0xb8003590)
#define VDC_DARK_CPLL_RESULT_VADDR               (0xb8003594)
#define VDC_IRQ_MASK1_VADDR                      (0xb80035a0)
#define VDC_IRQ_MASK2_VADDR                      (0xb80035a4)
#define VDC_IRQ_MASK3_VADDR                      (0xb80035a8)
#define VDC_IRQ_STATUS1_VADDR                    (0xb80035ac)
#define VDC_IRQ_STATUS2_VADDR                    (0xb80035b0)
#define VDC_IRQ_STATUS3_VADDR                    (0xb80035b4)
#define VDC_ADC_LIMIT_THRESHOLD_VADDR            (0xb80035b8)
#define VDC_LDPAUSE_CTRL_VADDR                   (0xb80035e0)
#define VDC_VCR_OPTION_VADDR                     (0xb80035e4)
#define VDC_CENABLE_LINE_COUNT_VADDR             (0xb80035e8)
#define VDC_SIGNAL_STM_CONTROL_VADDR             (0xb80035ec)
#define VDC_CDETECT_PHASE_ERR_STATUS_VADDR       (0xb80035f0)
#define VDC_AD_SW_CTRL0_VADDR                    (0xb8003608)
#define VDC_CLAMP_UPDN_EN_VADDR                  (0xb800360c)
#define VDC_CLAMP_RGB_UPDN_EN_VADDR              (0xb8003610)
#define VDC_FSW_CTRL0_VADDR                      (0xb8003618)
#define VDC_FSW_CTRL1_VADDR                      (0xb800361c)
#define VDC_FSW_CTRL2_VADDR                      (0xb8003620)
#define VDC_FSW_CTRL3_VADDR                      (0xb8003624)
#define VDC_LUMA_CONTRAST2_ADJ_VADDR             (0xb8003628)
#define VDC_LUMA_BRIGHTNESS2_ADJ_VADDR           (0xb800362c)
#define VDC_CHROMA_SATURATION2_ADJ_VADDR         (0xb8003630)
#define VDC_CB_SAT_ADJ_VADDR                     (0xb8003634)
#define VDC_LUMA_PEAKING2_VADDR                  (0xb8003638)
#define VDC_FSW_GAIN_CTRL_VADDR                  (0xb800363c)
#define VDC_FSW_INPUT_STATUS_VADDR               (0xb8003640)
#define VDC_ADCR_CALI_STATUS_VADDR               (0xb8003650)
#define VDC_ADCG_CALI_STATUS_VADDR               (0xb8003654)
#define VDC_ADCB_CALI_STATUS_VADDR               (0xb8003658)
#define VDC_ADC_GAIN_R1_VADDR                    (0xb800365c)
#define VDC_ADC_GAIN_R_VADDR                     (0xb8003660)
#define VDC_ADC_GAIN_G_VADDR                     (0xb8003664)
#define VDC_ADC_GAIN_B_VADDR                     (0xb8003668)
#define VDC_ADC_OFFSET_R_VADDR                   (0xb800366c)
#define VDC_ADC_OFFSET_G_VADDR                   (0xb8003670)
#define VDC_ADC_OFFSET_B_VADDR                   (0xb8003674)
#define VDC_CLAMP_TEST_REG0_VADDR                (0xb8003680)
#define VDC_CLAMP_TEST_REG2_VADDR                (0xb8003684)
#define VDC_CLAMP_TEST_REG4_VADDR                (0xb8003688)
#define VDC_CLAMP_TEST_REG6_VADDR                (0xb800368c)
#define VDC_CLAMP_TEST_REG8_VADDR                (0xb8003690)
#define VDC_CLAMP_TEST_REG11_VADDR               (0xb8003694)
#define VDC_HDETECT_PHASE_ERR_STATUS2_VADDR      (0xb8003698)
#define VDC_AVOUT_FIFO_RD_PTR_VADDR              (0xb800369c)
#define VDC_BLANK_LEVEL_MANU_COMP_VALUE_VADDR    (0xb80036a0)
#define VDC_BLANK_LEVEL_MANU_C_R_VALUE_VADDR     (0xb80036a4)
#define VDC_BLANK_LEVEL_MANU_G_B_VALUE_VADDR     (0xb80036a8)
#define VDC_FPGA_TEST_REG1_VADDR                 (0xb80036b0)
#define VDC_FPGA_TEST_REG2_VADDR                 (0xb80036b4)
#define VDC_FPGA_TEST_REG3_VADDR                 (0xb80036b8)
#define VDC_FPGA_TEST_REG4_VADDR                 (0xb80036bc)
#define VDC_FPGA_TEST_REG5_VADDR                 (0xb80036c0)
#define VDC_FPGA_TEST_REG6_VADDR                 (0xb80036c4)
#define VDC_FPGA_TEST_REG7_VADDR                 (0xb80036c8)
#define VDC_FPGA_TEST_REG8_VADDR                 (0xb80036cc)
#define VDC_SECAM_CTRL_VADDR                     (0xb8003700)
#define VDC_SECAM_DRFREQ_OFFSET_VADDR            (0xb8003704)
#define VDC_SECAM_DBFREQ_OFFSET_VADDR            (0xb8003708)
#define VDC_SECAM_HCOUNT_RESET_CTRL_VADDR        (0xb800370c)
#define VDC_PHASE_DIFF_DR_RST_VADDR              (0xb8003710)
#define VDC_PHASE_DIFF_DB_RST_VADDR              (0xb8003714)
#define VDC_DRDB_GAIN_TABLE_CTRL_VADDR           (0xb8003718)
#define VDC_Y_GAIN_TABLE_CTRL_VADDR              (0xb800371c)
#define VDC_SECAM_GAIN_DLY_VADDR                 (0xb8003720)
#define VDC_SECAM_GAIN_TABLE_DEBUG_VADDR         (0xb8003724)
#define VDC_NEW_SECAM_HCOUNT_RESET_CTRL_VADDR    (0xb8003734)
#define VDC_NEW_SECAM_PHASE_DIFF_DR_VADDR        (0xb8003738)
#define VDC_NEW_SECAM_PHASE_DIFF_DB_VADDR        (0xb800373c)
#define VDC_NEW_SECAM_CDTO_INC_VADDR             (0xb8003740)
#define VDC_SECAM_GP_RM_VADDR                    (0xb8003744)
#define VDC_FIFO_CTRL_VADDR                      (0xb8003758)
#define VDC_FIFO_STATUS_VADDR                    (0xb800375c)
#define VDC_I_GAIN_CONTROL_VADDR                 (0xb8003760)
#define VDC_MISC_CONTROL_VADDR                   (0xb8003764)
#define VDC_FIFO_DEPTH_MIN_STATUS_VADDR          (0xb8003768)
#define VDC_FIFO_DEPTH_MAX_STATUS_VADDR          (0xb800376c)
#define VDC_PLL_DEBUG_CTRL1_VADDR                (0xb8003770)
#define VDC_PLL_DEBUG_CTRL2_VADDR                (0xb8003774)
#define VDC_DISP_FSYNC_CONTROL_VADDR             (0xb8003778)
#define VDC_FIFO_WO_PS_FUNC_VADDR                (0xb800377c)
#define VDC_FIFO_WO_PS_CLK_STATE_PARAMETER_VADDR (0xb8003780)
#define VDC_FIFO_STATUS_NO_PLL_VADDR             (0xb8003784)
#define VDC_DEBUG_MUX_VADDR                      (0xb8003788)
#define VDC_VIDEO_DEBUG_ANALOG_VADDR             (0xb800378c)
#define VDC_VIDEO_DEBUG_DIGITAL_VADDR            (0xb8003790)
#define VDC_PATTERN_CONTROL_VADDR                (0xb8003794)
#define VDC_CRC_RESULT3_VADDR                    (0xb8003798)
#define VDC_PATGEN_CTRL_VADDR                    (0xb800379c)
#define VDC_BIST_MODE_VADDR                      (0xb80037a0)
#define VDC_BIST_DONE_VADDR                      (0xb80037a4)
#define VDC_BIST_FAIL_VADDR                      (0xb80037a8)
#define VDC_BIST_DRF_MODE_VADDR                  (0xb80037ac)
#define VDC_BIST_DRF_RESUME_VADDR                (0xb80037b0)
#define VDC_BIST_DRF_DONE_VADDR                  (0xb80037b4)
#define VDC_BIST_DRF_PAUSE_VADDR                 (0xb80037b8)
#define VDC_BIST_DRF_FAIL_VADDR                  (0xb80037bc)
#define VDC_BIST_FAIL_27_1_VADDR                 (0xb80037c0)
#define VDC_BIST_FAIL_27_2_VADDR                 (0xb80037c4)
#define VDC_BIST_FAIL_DMA_VADDR                  (0xb80037c8)
#define VDC_BIST_FAIL_FIFO_VADDR                 (0xb80037cc)
#define VDC_BIST_FAIL_OUT_VADDR                  (0xb80037d0)
#define VDC_BIST_DRF_FAIL_27_1_VADDR             (0xb80037d4)
#define VDC_BIST_DRF_FAIL_27_2_VADDR             (0xb80037d8)
#define VDC_BIST_DRF_FAIL_DMA_VADDR              (0xb80037dc)
#define VDC_BIST_DRF_FAIL_FIFO_VADDR             (0xb80037e0)
#define VDC_BIST_DRF_FAIL_OUT_VADDR              (0xb80037e4)
#define VDC_BIST_DVSE_DVS_VADDR                  (0xb80037e8)
#define VDC_BIST_DVSE_DVS2_VADDR                 (0xb80037ec)
#define VDC_ADC_UPDN_CTRL_VADDR                  (0xb80037fc)




#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN


//======VDTOP register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hv_delay:1;
        RBus_UInt32  hpixel:2;
        RBus_UInt32  vline_625:1;
        RBus_UInt32  colour_mode:3;
        RBus_UInt32  res2:1;
    };
}VIDEO_CONTROL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  ycsepdata_burstin_en:1;
        RBus_UInt32  vd_pq_bypass_en:1;
        RBus_UInt32  cv_inv:1;
        RBus_UInt32  cv_src:1;
        RBus_UInt32  yc_src:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  ped:1;
    };
}VIDEO_CONTROL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  hvlock_longtime:1;
        RBus_UInt32  vlock_longtime:1;
        RBus_UInt32  hlock_longtime:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  chromalock_acc:1;
        RBus_UInt32  h_fine_lock:1;
        RBus_UInt32  mv_colour_inverse:3;
        RBus_UInt32  mv_vbi_detected:1;
        RBus_UInt32  chomalock:1;
        RBus_UInt32  vlock:1;
        RBus_UInt32  hlock:1;
        RBus_UInt32  no_signal:1;
    };
}VIDEO_STATUS_REG1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  firtst_vsync_detected:1;
        RBus_UInt32  v_detect_flag:1;
        RBus_UInt32  detect358_flag:1;
        RBus_UInt32  vlock_new:1;
        RBus_UInt32  noisy_vbi:1;
        RBus_UInt32  detect443_flag:1;
        RBus_UInt32  burst_detect:1;
        RBus_UInt32  palor_flag:1;
        RBus_UInt32  palm_flag:1;
        RBus_UInt32  proscan_detected:1;
    };
}VIDEO_STATUS_REG2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vcr_rew:1;
        RBus_UInt32  vcr_ff:1;
        RBus_UInt32  vcr_trick:1;
        RBus_UInt32  vcr:1;
        RBus_UInt32  noisy:1;
        RBus_UInt32  lines_625_detected:1;
        RBus_UInt32  secam_detected:1;
        RBus_UInt32  pal_detected:1;
    };
}VIDEO_STATUS_REG3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  hdto_inc_status:30;
    };
}HDTO_INC_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  cdto_inc_status:30;
    };
}CDTO_INC_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_magnitude:8;
    };
}AVG_BURST_MAG_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  agc_dgain:12;
    };
}AGC_DGAIN_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  status_cmag:8;
    };
}CMAG_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  status_cgain_data:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  status_cgain:14;
    };
}CGAIN_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  status_cordiq_freq:8;
    };
}CORDIC_FREQ_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  v_1st_line:10;
    };
}MEASURE_FIRST_V_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  v_2nd_line:10;
    };
}MEASURE_SECOND_V_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  porch_h:13;
    };
}PORCH_HEIGHT_M_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  status_noise:8;
    };
}NOISE_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  noise_thresh:8;
    };
}NOISE_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdto_fixed:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  hdto_inc:30;
    };
}HSYNC_DTO_INC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cdto_fixed:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  cdto_inc:30;
    };
}CHROMA_DTO_INC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  chip_ver:16;
    };
}CHIP_VER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  blank_vid_offset_manu_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  blank_vid_offset_value:11;
    };
}BLANK_VID_OFFSET_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  contrast:8;
    };
}LUMA_CONTRAST_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  brightness:8;
    };
}LUMA_BRIGHTNESS_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  saturation:8;
    };
}CHROMA_SATURATION_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hue:8;
    };
}CHROMA_HUE_PHASE_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  blue_screen_y:8;
    };
}BLUE_SCREEN_Y_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  blue_screen_cb:8;
    };
}BLUE_SCREEN_CB_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  blue_screen_cr:8;
    };
}BLUE_SCREEN_CR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  motion_delay:4;
        RBus_UInt32  snow_freerun_en:1;
        RBus_UInt32  cbcr_swap:1;
        RBus_UInt32  blue_mode:2;
        RBus_UInt32  yc_delay:4;
    };
}OUTPUT_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  avout_hsync_start:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  avout_hsync_end:10;
        RBus_UInt32  res3:3;
        RBus_UInt32  fe_bypass_sel:1;
        RBus_UInt32  sw_tu_cvbs:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  clamp_if_up_en:1;
        RBus_UInt32  clamp_if_dn_en:1;
    };
}INOUT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  output_fifo_full:1;
        RBus_UInt32  output_fifo_empty:1;
        RBus_UInt32  output_delay_0_180_sw:1;
        RBus_UInt32  avout_test_in:12;
        RBus_UInt32  res2:3;
        RBus_UInt32  avout_mixer_sel:4;
        RBus_UInt32  res3:3;
        RBus_UInt32  avout_fifo_status_full:1;
        RBus_UInt32  avout_fifo_status_empty:1;
    };
}AVOUT_FIFO_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avout_ifdebug_inv:12;
        RBus_UInt32  avout_ifdebug_mask:12;
        RBus_UInt32  avout_ifdebug_shift:4;
        RBus_UInt32  res1:3;
        RBus_UInt32  avout_ifdebug_sel:1;
    };
}AVOUT_IFDEBUG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  peak_deb_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  peak_diff_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  peak_data_sel:1;
        RBus_UInt32  peak_deb_limit:9;
        RBus_UInt32  peak_deb_thl:8;
        RBus_UInt32  hagc_err_coring_en:1;
        RBus_UInt32  agc_peak_nominal:7;
    };
}AGC_PEAK_NOMINAL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  chroma_path_dgain_after_en:1;
        RBus_UInt32  ycsep_data_offset_div2_en:1;
        RBus_UInt32  ycsep_data_decrease_en:1;
        RBus_UInt32  ycsep_data_decrease_ratio:3;
        RBus_UInt32  agc_peak_nominal_ycsep:12;
        RBus_UInt32  res2:1;
        RBus_UInt32  agc_gate_kill_mode_sel:2;
        RBus_UInt32  agc_gate_kill_w_hlock:1;
        RBus_UInt32  agc_gate_vsync_coarse:1;
        RBus_UInt32  agc_gate_vsync_stip:1;
        RBus_UInt32  agc_gate_kill_mode:2;
        RBus_UInt32  agc_peak_en:1;
        RBus_UInt32  agc_peak_cntl:3;
    };
}AGC_PEAK_AND_GATE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  peak_gain:12;
        RBus_UInt32  diff_level:12;
        RBus_UInt32  unlock_peakrst_en:1;
        RBus_UInt32  hagc_err_coring_th:5;
        RBus_UInt32  agc_peak_loop_gain:2;
    };
}AGC_PEAK_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  fix_dgain:1;
        RBus_UInt32  res2:6;
        RBus_UInt32  dgain_state:2;
        RBus_UInt32  under_gain:12;
        RBus_UInt32  hagc_field_mode:1;
        RBus_UInt32  mv_hagc_mode:1;
        RBus_UInt32  dc_clamp_mode:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  bgate_raw_sel:1;
        RBus_UInt32  cagc_en:1;
        RBus_UInt32  hagc_en:1;
    };
}VIDEO_CONTROL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  dgain_status_triger:1;
        RBus_UInt32  peak_under_round_en:1;
        RBus_UInt32  peak_under_round_thl:8;
        RBus_UInt32  dgain_status_counter:12;
        RBus_UInt32  hagc:8;
    };
}LUMA_AGC_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  agc_gate_start:11;
    };
}AGC_GATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  agc_gate_width:7;
    };
}AGC_GATE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  agc_bp_delay:8;
    };
}AGC_BP_DELAY_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  clampagc_under_th2:6;
    };
}CLAMPAGC_COMPLUMA_NEW_THRESHOLD2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  data_path_dgain_div2_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  agc_under_loop_gain:3;
        RBus_UInt32  under_flag:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  clampagc_under_th1:4;
    };
}CLAMPAGC_COMPLUMA_NEW_THRESHOLD1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  under_deb_en:1;
        RBus_UInt32  under_gate_en:1;
        RBus_UInt32  under_diff_sel:2;
        RBus_UInt32  res1:3;
        RBus_UInt32  under_deb_limit:9;
        RBus_UInt32  under_deb_thl:8;
        RBus_UInt32  clampagc_under_cntl:6;
        RBus_UInt32  clampagc_under_en:1;
        RBus_UInt32  blank_vid_offset:1;
    };
}CLAMPAGC_COMPLUMA_NEW_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  under_gate_end:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  under_gate_st:10;
        RBus_UInt32  res3:1;
        RBus_UInt32  vsync_agc_min:7;
    };
}VSYNC_AGC_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vsync_clamp_mode:2;
        RBus_UInt32  vsync_agc_max:6;
    };
}VSYNC_AGC_LOCKOUT_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  auto_dc_restore_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  auto_dc_restore_en2:1;
        RBus_UInt32  auto_dc_restore_en1:1;
        RBus_UInt32  auto_dc_restore_en0:1;
        RBus_UInt32  auto_dc_restore_disable_ad4_updn:1;
        RBus_UInt32  auto_dc_restore_disable_ad3_updn:1;
        RBus_UInt32  auto_dc_restore_disable_ad2_updn:1;
        RBus_UInt32  auto_dc_restore_disable_ad1_updn:1;
        RBus_UInt32  cpump_adjust_delay:6;
        RBus_UInt32  cpump_adjust_polarity:1;
        RBus_UInt32  cpump_delay_en:1;
    };
}CHARGE_PUMP_DELAY_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cpump_adjust:8;
    };
}CHARGE_PUMP_ADJUSTMENT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cpump_delay:8;
    };
}CHARGE_PUMP_DELAY_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  adc_updn_swap:1;
        RBus_UInt32  adc_input_swap:1;
        RBus_UInt32  adc_cbcr_pump_swap:1;
        RBus_UInt32  agc_gate_thresh:5;
    };
}AGC_GATE_TH_SWAP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  measure_dc_128_64_sel:1;
        RBus_UInt32  dgain_ignore_fine_lock:1;
        RBus_UInt32  measure_dc_rough:1;
        RBus_UInt32  new_clamp_rc_rate_en:1;
        RBus_UInt32  clampagc_rc_rate:4;
    };
}NEW_CLAMPAGC_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  measure_dc_rough_dn:8;
    };
}MEASURE_DC_ROUGH_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  measure_dc_rough_up:8;
    };
}MEASURE_DC_ROUGH_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  measure_dc_th_dn:12;
    };
}MEASURE_DC_TH_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  measure_dc_th_up:12;
    };
}MEASURE_DC_TH_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vsag_rc_input:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  vsag_agc_peak_cntl:6;
    };
}VSAG_CNTL_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  peak_vsag:13;
    };
}PEAK_VSAG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  new_total_under_en:1;
        RBus_UInt32  new_under_gain_en:1;
        RBus_UInt32  new_under_th2_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  lose_sgate_flag:1;
        RBus_UInt32  lose_bgate_flag:1;
        RBus_UInt32  field_kill_rst:1;
    };
}KILL_FIELD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  field_kill_num:10;
    };
}FIELD_KILL_MUN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  kill_gate_up:11;
    };
}KILL_GATE_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  kill_gate_dn:11;
    };
}KILL_GATE_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  syncmidpt_add_level_h:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  sync_midpt_lowest_en:1;
        RBus_UInt32  res3:1;
    };
}syncmidpt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  syncmidpt_fix_add_value_h:8;
    };
}syncmidpt_fix_add_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  lpfsync_plus_w_hlock:2;
        RBus_UInt32  lpfsync_plus_rm:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  lpfsync_plus_diff:6;
    };
}lpfsync_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  spike_min_thresh:8;
    };
}spike_min_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  spike_max_thresh:8;
    };
}spike_max_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  spike_detected:1;
        RBus_UInt32  spike_detected_up:10;
    };
}spike_detected_up_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  spike_detected_dn:10;
    };
}spike_detected_dn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  lpfsync_plus_dc:8;
    };
}lpfsync_plus_dc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  hstate_error_thl:8;
        RBus_UInt32  hstate_error_dn_count:8;
        RBus_UInt32  hstate_error_rst:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  hdetect_error_avg_interval:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  hdetect_error_avg_length:3;
        RBus_UInt32  res4:3;
        RBus_UInt32  hdetect_error_avg_sel:1;
    };
}HDETECT_ERR_VAR_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_error_var:16;
        RBus_UInt32  hdetect_error_mean:16;
    };
}HDETECT_ERR_VAR_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hstate_vsync_error_num_thr:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  hstate_vsync_error_end:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  hstate_vsync_error_start:7;
        RBus_UInt32  locked_count_vcrtrick_max:4;
        RBus_UInt32  locked_count_noisy_max:4;
        RBus_UInt32  locked_count_clean_max:4;
    };
}LOCK_COUNT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  hstate_vsync_error_unbalance_status:1;
        RBus_UInt32  hstate_vsync_error_unbalance_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hstate_vsync_error_sel:2;
        RBus_UInt32  res3:3;
        RBus_UInt32  hstate_vsync_error_value_en:1;
        RBus_UInt32  hstate_vsync_error_num_en:1;
        RBus_UInt32  hstate_vsync_error_noisy_en:1;
        RBus_UInt32  hstate_vsync_error_vlock_en:1;
        RBus_UInt32  hstate_vsync_error_hlock_en:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  hstate_vsync_error_unbalance:3;
        RBus_UInt32  hlock_vsync_mode:2;
        RBus_UInt32  hstate_fixed:1;
        RBus_UInt32  disable_hfine:1;
        RBus_UInt32  hstate_unlocked:1;
        RBus_UInt32  hstate_max:3;
    };
}H_LOOP_MAXSTATE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  fine_phase_error_thl:10;
        RBus_UInt32  cpll_hpll_use_front_vactive:1;
        RBus_UInt32  hstate_hlock_sel:1;
        RBus_UInt32  hstate_ignore_err:1;
        RBus_UInt32  auto_fine_phase_sel:1;
        RBus_UInt32  fine_hstate_to_5:1;
        RBus_UInt32  auto_fine_phase_sel_en:1;
        RBus_UInt32  hpll_fine_lock_data_sel:1;
        RBus_UInt32  coarse_phase_rising_en:1;
        RBus_UInt32  fine_src_sel:1;
        RBus_UInt32  coarse_src_sel:1;
        RBus_UInt32  fine_gate_sel:1;
        RBus_UInt32  gate_end_thresh:5;
    };
}CLAMPAGC_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  hstate_vsync_error_noisy_lower_th:8;
        RBus_UInt32  hstate_vsync_error_noisy_upper_th:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  coarse_sync_start:7;
    };
}CLAMPAGC_NEW_SYNC_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  hstate_vsync_error_value_thr:8;
        RBus_UInt32  hstate_vsync_error_abs_thr:8;
        RBus_UInt32  coarse_sync_end:8;
    };
}CLAMPAGC_NEW_SYNC_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  hstate_err:14;
        RBus_UInt32  agc_trailing_sel:1;
        RBus_UInt32  coarse_backporch_start:7;
    };
}CLAMPAGC_NEW_BACKPORCH_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  hstate_err_in_vcount:10;
        RBus_UInt32  coarse_backporch_end:8;
    };
}CLAMPAGC_NEW_BACKPORCH_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  lpfsync_force_blank_en:1;
        RBus_UInt32  nosignal_hlock_check_en:1;
        RBus_UInt32  agc_clamping_trailing_sel:1;
        RBus_UInt32  killgate_sel:1;
        RBus_UInt32  coarse_phase_sel:1;
        RBus_UInt32  fine_phase_sel:1;
    };
}HDETECT_PHASE_SEL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  lsync_tip_start:8;
    };
}HDETECT_COUNTER_TIP_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  lsync_tip_end:8;
    };
}HDETECT_COUNTER_TIP_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  lporch_start:8;
    };
}HDETECT_COUNTER_BACKPORCH_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  lporch_end:8;
    };
}HDETECT_COUNTER_BACKPORCH_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  hpll_integral_rst:1;
        RBus_UInt32  hpll_integral_ext:1;
    };
}HPLL_INTEGRAL_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_gate_kill_mode_status:2;
        RBus_UInt32  new_hpll_lpf_sel_status:1;
        RBus_UInt32  gate_iir_h_sel_status:1;
        RBus_UInt32  gate_iir_v_sel_status:1;
        RBus_UInt32  dgain_ignore_fine_lock_status:1;
        RBus_UInt32  second_pll_en_status:1;
        RBus_UInt32  vsync_freerun_when_unstable_en_status:1;
        RBus_UInt32  agc_gate_kill_mode_vcr:2;
        RBus_UInt32  new_hpll_lpf_sel_vcr:1;
        RBus_UInt32  gate_iir_h_sel_vcr:1;
        RBus_UInt32  gate_iir_v_sel_vcr:1;
        RBus_UInt32  dgain_ignore_fine_lock_vcr:1;
        RBus_UInt32  second_pll_en_vcr:1;
        RBus_UInt32  vsync_freerun_when_unstable_en_vcr:1;
        RBus_UInt32  impulsive_noise_disable_pll_en:1;
        RBus_UInt32  cstate_impn_max:3;
        RBus_UInt32  mode_vcr_setting_change_en:1;
        RBus_UInt32  hstate_impn_max:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  hstate_vcr_max:3;
        RBus_UInt32  hstate_loopfilter_sw:1;
        RBus_UInt32  hstate_status:3;
    };
}HDETECT_LOOPFILTER_SW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hdetect_loopfilter_dctrl1:4;
        RBus_UInt32  hdetect_loopfilter_dctrl2:4;
    };
}HDETECT_LOOPFILTER_DCTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hsync_start:8;
    };
}HSYNC_PULSE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hsync_width:8;
    };
}HSYNC_PULSE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  hresampler_app_alpha_sel:1;
        RBus_UInt32  hresampler_app_sel:1;
        RBus_UInt32  hresampler_2up:1;
    };
}CHROMA_HRESAMPLER_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hpll_manu_mode_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  hpll_kp_coef_0:6;
    };
}HPLL_KP_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  hpll_kp_coef_1:6;
    };
}HPLL_KP_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  hpll_kp_coef_2:6;
    };
}HPLL_KP_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  hpll_kp_coef_3:6;
    };
}HPLL_KP_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  hpll_kp_coef_4:6;
    };
}HPLL_KP_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  hpll_kp_coef_5:6;
    };
}HPLL_KP_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hpll_ki_coef_0:8;
    };
}HPLL_KI_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hpll_ki_coef_1:8;
    };
}HPLL_KI_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hpll_ki_coef_2:8;
    };
}HPLL_KI_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hpll_ki_coef_3:8;
    };
}HPLL_KI_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hpll_ki_coef_4:8;
    };
}HPLL_KI_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hpll_ki_coef_5:8;
    };
}HPLL_KI_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  second_pll_level_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  second_pll_gain_sel:2;
        RBus_UInt32  second_pll_clampgate_sel:1;
        RBus_UInt32  second_pll_phase_sel:1;
        RBus_UInt32  second_pll_w_hlock:1;
        RBus_UInt32  second_pll_en:1;
    };
}Second_pll_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_pll_sync_level:8;
        RBus_UInt32  second_pll_dc_add:12;
        RBus_UInt32  second_pll_dc_rm:12;
    };
}Second_pll_gain1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  second_comp_blevel:12;
        RBus_UInt32  second_comp_slevel:12;
    };
}Second_pll_gain2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  second_trailing:8;
        RBus_UInt32  second_dgain:12;
    };
}Second_pll_gain3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_backporch_start:8;
        RBus_UInt32  second_backporch_end:8;
        RBus_UInt32  second_hsync_tip_start:8;
        RBus_UInt32  second_hsync_tip_end:8;
    };
}Second_pll_gain4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  headswitch_debounce_en:1;
        RBus_UInt32  second_pll_kill_en:1;
        RBus_UInt32  under_detected_flag:1;
        RBus_UInt32  under_count_reset:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  under_line_err_thl:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  under_min_err_thl:10;
    };
}under_new_th1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  under_field_err_thl:10;
    };
}under_new_th2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  under_debounce_thl:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  under_debounce_max:10;
    };
}under_new_th3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coch_detected_by_check_dc:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  coch_avg_line1_diff_thre_up:12;
        RBus_UInt32  coch_avg_line1_diff_thre_lo:12;
    };
}DC_COCH_SEPERATE_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coch_detect_lpf_reset:1;
        RBus_UInt32  res1:9;
        RBus_UInt32  coch_detect_counter_up_thre:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  coch_detect_counter_lo_thre:10;
    };
}DC_COCH_SEPERATE_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hsync_rising:8;
    };
}HSYNC_RISING_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hsync_phase_offset:8;
    };
}HSYNC_PHASE_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  secam_gp_hcount_start:10;
        RBus_UInt32  res2:4;
        RBus_UInt32  hsync_gate_start:8;
    };
}HSYNC_GATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  secam_gp_hcount_end:10;
        RBus_UInt32  res2:4;
        RBus_UInt32  hsync_gate_end:8;
    };
}HSYNC_GATE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  secam_gp_vcount_start_o:10;
        RBus_UInt32  res2:4;
        RBus_UInt32  hsync_tip_start:8;
    };
}HSYNC_TIP_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  secam_gp_vcount_end_o:10;
        RBus_UInt32  res2:4;
        RBus_UInt32  hsync_tip_end:8;
    };
}HSYNC_TIP_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  secam_gp_vcount_start_e:10;
        RBus_UInt32  res2:4;
        RBus_UInt32  hsync_rising_start:8;
    };
}HSYNC_RISING_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  secam_gp_vcount_end_e:10;
        RBus_UInt32  res2:4;
        RBus_UInt32  hsync_rising_end:8;
    };
}HSYNC_RISING_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  backporch_start:8;
    };
}BACKPROCH_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  backporch_end:8;
    };
}BACKPORCH_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hblank_start:8;
    };
}HBLANK_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hblank_end:8;
    };
}HBLANK_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_gate_start:8;
    };
}BURST_GATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_gate_end:8;
    };
}BURST_GATE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hactive_start:8;
    };
}HACTIVE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hactive_width:8;
    };
}HACTIVE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_hstate_phase_max_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  hdetect_hstate_3_phase_max:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  hdetect_hstate_4_phase_max:13;
    };
}HDETECT_ERR_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  hdetect_hstate_5_phase_max:13;
        RBus_UInt32  hdetect_err04_th:8;
        RBus_UInt32  hdetect_err00_th:8;
    };
}HDETECT_ERR_TH2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  cpll_use_fine_or_final_hlock:1;
        RBus_UInt32  new_c_state_i:1;
        RBus_UInt32  new_cstate:1;
        RBus_UInt32  cstate_cntl:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  cstate_status:3;
    };
}CSTATE_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  s_b_level_fir_en:1;
        RBus_UInt32  level_fir_num_32_64_blevel:1;
        RBus_UInt32  level_fir_num_32_64_slevel:1;
        RBus_UInt32  coef_syncmidpt_fir_in:8;
        RBus_UInt32  res2:5;
        RBus_UInt32  new_hpll_lpf_sel:1;
        RBus_UInt32  gate_iir_h_sel:1;
        RBus_UInt32  gate_iir_v_sel:1;
    };
}HDETECT_GATE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  headswitch_err_sel:2;
        RBus_UInt32  hsync_refind_mask_err:1;
        RBus_UInt32  hsync_refind:1;
        RBus_UInt32  gate_iir_coef1:8;
    };
}HDETECT_GATE_COEF1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  hdetect_err07_th:8;
        RBus_UInt32  gate_iir_coef2:8;
    };
}HDETECT_GATE_COEF2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  hstate_err_thl:14;
        RBus_UInt32  res2:6;
        RBus_UInt32  hstate_err_counter:2;
        RBus_UInt32  vphase_status:8;
    };
}HDETECT_VPHASE_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_err05_th:8;
        RBus_UInt32  hdetect_err10_th:8;
        RBus_UInt32  hdetect_err01_th:8;
        RBus_UInt32  vphasediff_status:8;
    };
}HDETECT_VPHASEDIFF_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  noise_vbi_thresh:8;
    };
}NOISE_VBI_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  coch_detected_status:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  coch_detected_frame:6;
    };
}VBI_CO_CH_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  coch_bp_diff_th:4;
    };
}VBI_CO_CH_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  coch_line_count_th:8;
    };
}VBI_CO_CH_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  mv_window2_value:8;
    };
}MV_DETECT_WINDOW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ad_burst_gate_start:8;
    };
}MV_BURSTGATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ad_burst_gate_end:8;
    };
}MV_BURSTGATE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  cinverse_detect_control:3;
    };
}COLOR_INVERSE_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_err_constraint_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  h_err_constraint_high_th:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  h_err_constraint_low_th:14;
    };
}H_ERR_CONSTRAINT_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  h_err_constraint_hstate:3;
        RBus_UInt32  h_err_constraint_val:13;
    };
}H_ERR_CONSTRAINT_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_restore_hdto_en:1;
        RBus_UInt32  hdetect_set_new_hdto_n:3;
        RBus_UInt32  hdetect_restore_hdto_status:1;
        RBus_UInt32  hdetect_force_hdto_en:1;
        RBus_UInt32  hdetect_set_hdto_start:10;
        RBus_UInt32  res1:3;
        RBus_UInt32  hdetect_restore_vcr_enable:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hdetect_save_stable_hdto_start:10;
    };
}H_RESTORE_HDTO_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  hdetect_set_hdto_phase_err_th:14;
    };
}H_RESTORE_HDTO_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wrong_if_pc_detect_th:8;
        RBus_UInt32  sync_level_manu:8;
        RBus_UInt32  res1:7;
        RBus_UInt32  sync_level_manu_en:1;
        RBus_UInt32  res2:7;
        RBus_UInt32  wrong_if_pc_detect:1;
    };
}IF_WRONG_PC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  cpll_phase_thr_up:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  cpll_phase_thr_dn:14;
    };
}CPLL_STABILITY_OBSERVE_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  cpll_ampl_thr:7;
        RBus_UInt32  res2:2;
        RBus_UInt32  cerror_continune_same_sign_thr:6;
        RBus_UInt32  res3:13;
        RBus_UInt32  cpll_ampl_neg_flag:1;
        RBus_UInt32  cpll_phase_small_flag:1;
        RBus_UInt32  cpll_stable_flag:1;
    };
}CPLL_STABILITY_OBSERVE_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  ampl_out_line_iir:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  phase_out_line_iir:14;
    };
}CPLL_STABILITY_OBSERVE_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  herror_pos_neg_value_diff_thr:16;
        RBus_UInt32  res1:2;
        RBus_UInt32  herror_continune_same_sign_thr:6;
        RBus_UInt32  herror_neg_pos_num_total_thr:4;
        RBus_UInt32  herror_neg_pos_value_total_thr:4;
    };
}HPLL_STABILITY_OBSERVE_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  herror_neg_value:16;
        RBus_UInt32  herror_pos_value:16;
    };
}HPLL_STABILITY_OBSERVE_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  herror_neg_pos_err_th:13;
        RBus_UInt32  res2:1;
        RBus_UInt32  herror_neg_pos_num_win_thr:7;
        RBus_UInt32  res3:5;
        RBus_UInt32  herror_pos_neg_num_even:1;
        RBus_UInt32  herror_pos_neg_value_even:1;
        RBus_UInt32  herror_stable_state_hold_en:1;
    };
}HPLL_STABILITY_OBSERVE_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  statistic_h_phase_diff_sec1_end:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  statistic_h_phase_diff_sec1_start:9;
    };
}H_PHASE_DIFF_STATISTICS_SET_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  statistic_h_phase_diff_sec2_end:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  statistic_h_phase_diff_sec2_start:9;
    };
}H_PHASE_DIFF_STATISTICS_SET_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  statistic_h_phase_diff_hitso_level2:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  statistic_h_phase_diff_hitso_level1:13;
    };
}H_PHASE_DIFF_STATISTICS_SET_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  statistic_h_phase_diff_hitso_level4:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  statistic_h_phase_diff_hitso_level3:13;
    };
}H_PHASE_DIFF_STATISTICS_SET_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  statistic_h_phase_diff_hitso_level5:13;
    };
}H_PHASE_DIFF_STATISTICS_SET_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_ready:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_2:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_1:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_0:10;
    };
}H_PHASE_DIFF_SEC1_HISTOGRAM_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_5:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_4:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_3:10;
    };
}H_PHASE_DIFF_SEC1_HISTOGRAM_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_ready:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_2:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_1:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_0:10;
    };
}H_PHASE_DIFF_SEC2_HISTOGRAM_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_5:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_4:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_3:10;
    };
}H_PHASE_DIFF_SEC2_HISTOGRAM_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  iir_up_speed_on:1;
        RBus_UInt32  data_level_diff_iir_en:1;
        RBus_UInt32  statistic_data_level_diff_th:14;
        RBus_UInt32  res1:10;
        RBus_UInt32  statistic_data_level_line_num:6;
    };
}DATA_LEVEL_STATISTICS_SET_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_ready:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  statistic_data_level_sec1_min:12;
        RBus_UInt32  statistic_data_level_sec1_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  statistic_data_level_sec2_min:12;
        RBus_UInt32  statistic_data_level_sec2_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  statistic_data_level_sec3_min:12;
        RBus_UInt32  statistic_data_level_sec3_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  statistic_data_level_sec4_min:12;
        RBus_UInt32  statistic_data_level_sec4_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  statistic_data_level_sec5_min:12;
        RBus_UInt32  statistic_data_level_sec5_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  statistic_data_level_sec6_min:12;
        RBus_UInt32  statistic_data_level_sec6_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  statistic_data_level_sec7_min:12;
        RBus_UInt32  statistic_data_level_sec7_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  statistic_data_level_sec8_min:12;
        RBus_UInt32  statistic_data_level_sec8_max:12;
    };
}DATA_LEVEL_STATISTICS_SEC8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vsync_cntl:2;
        RBus_UInt32  vsync_threshold:6;
    };
}VSYNC_CNTL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  field_polarity:1;
        RBus_UInt32  flip_field:1;
        RBus_UInt32  veven_delayed:1;
        RBus_UInt32  vodd_delayed:1;
        RBus_UInt32  field_detect_mode:2;
        RBus_UInt32  vloop_tc3:2;
    };
}VSYNC_TIME_CONST_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  vloop_tc2:7;
    };
}VSYNC_TIME_CONST2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vloop_tc1:8;
    };
}VSYNC_TIME_CONST1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  serration_threshold:8;
    };
}SERRATION_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hvlock_field_cnt:4;
        RBus_UInt32  vlock_field_cnt:4;
        RBus_UInt32  hlock_field_cnt:4;
        RBus_UInt32  res1:2;
        RBus_UInt32  vsync_delay_sel:1;
        RBus_UInt32  vsync_delay_en:1;
        RBus_UInt32  vsync_delay_1d:4;
        RBus_UInt32  vsync_delay_2d:4;
        RBus_UInt32  res2:5;
        RBus_UInt32  no_signal_dec:3;
    };
}NO_SIGNAL_DEC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vactive_start:8;
    };
}VACTIVE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vactive_height:8;
    };
}VACTIVE_HEIGHT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  vsync_h_min:7;
    };
}VSYNC_H_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  vsync_h_max:7;
    };
}VSYNC_H_MAX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  vsync_vbi_min:7;
    };
}VSYNC_VBI_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vlock_wide_range:1;
        RBus_UInt32  vsync_vbi_max:7;
    };
}VSYNC_VBI_LOCKOUT_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  vsync_ser_num_bigger_10_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  vsync_ser_num_max_def:6;
        RBus_UInt32  syncmidpt_dc_rough:1;
        RBus_UInt32  midpt_625_dc_th_en:1;
        RBus_UInt32  midpt_rough_vdetect_en:1;
        RBus_UInt32  vsync_625_midpt_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  syncmidpt_add_level:2;
    };
}MIDPT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  syncmidpt_fix_add_value:8;
    };
}MIDPT_FIX_ADD_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  midpt_625_dc_th:8;
    };
}MIDPT_625_DC_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  sync_dc_offset_th:12;
    };
}SYNC_DC_OFFSET_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  sync_midpt_625:12;
    };
}SYNC_DC_OFFSET_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  sync_midpt_h:12;
    };
}SYNC_MIDPT_H_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  sync_midpt_v:12;
    };
}SYNC_MIDPT_V_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  raw_vdetect_max_sel:2;
        RBus_UInt32  res2:3;
        RBus_UInt32  no_signal_hpll_out:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  no_signal_to_0_sel:1;
        RBus_UInt32  hpll_no_signal_sel:1;
        RBus_UInt32  vlock_sel:1;
        RBus_UInt32  vdetect_pattern_sel:2;
        RBus_UInt32  res4:2;
        RBus_UInt32  adc_lpf_sel:3;
        RBus_UInt32  new_vdetect_line_length_en:1;
    };
}SYNC_MIDPT_V2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_lpf_coef1:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef2:10;
    };
}ADC_27_LPF_COEF_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_lpf_coef3:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef4:10;
    };
}ADC_27_LPF_COEF_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_lpf_coef5:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef6:10;
    };
}ADC_27_LPF_COEF_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_lpf_coef7:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef8:10;
    };
}ADC_27_LPF_COEF_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_lpf_coef9:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coefa:10;
    };
}ADC_27_LPF_COEF_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  adc_lpf_coefb:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coefc:10;
    };
}ADC_27_LPF_COEF_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  new_vdetect_line_length:8;
    };
}VDETECT_LINE_LENGHT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  new_vdetect_force_en:1;
        RBus_UInt32  no_vsync_flag_en:1;
        RBus_UInt32  new_vdetect_window_en:1;
        RBus_UInt32  new_vdetect_window_manu_en:1;
    };
}VDETECT_WINDOW_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  new_vdetect_window:12;
    };
}VDETECT_WINDOW_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  new_vdetect_max_limit_value:12;
        RBus_UInt32  res2:2;
        RBus_UInt32  new_vdetect_max_limit_en:1;
        RBus_UInt32  new_vdetect_coch_en:1;
        RBus_UInt32  new_vdetect_en:1;
        RBus_UInt32  gate_sel:1;
        RBus_UInt32  vloss_detect_en:1;
        RBus_UInt32  new_vdetect_vcount_window_en:1;
        RBus_UInt32  new_vsync_offset_manul_mode_en:1;
        RBus_UInt32  new_vsync_offset_manul:3;
    };
}NEW_VDETECT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  old_hdetect_lpf_en:1;
        RBus_UInt32  new_vdetect_feature_th_manul_en:1;
        RBus_UInt32  no_vsync_flag:1;
        RBus_UInt32  new_vloss_flag:1;
        RBus_UInt32  force_new_vdetect_fine_window:1;
        RBus_UInt32  vsync_fine_window_state1_en:1;
        RBus_UInt32  res2:2;
    };
}NEW_VDETECT_LOOP_TH2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  new_vdetect_loop_core_th:10;
    };
}NEW_VDETECT_LOOP_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  new_vdetect_diff_offset:12;
    };
}NEW_VDETECT_DIFF_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  vsync_fine_start1:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  new_vdetect_loss_max:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  vsync_fine_start:10;
    };
}VSYNC_FINE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  vsync_fine_end1:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  new_vdetect_loss_up:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  vsync_fine_end:10;
    };
}VSYNC_FINE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  no_vsync_th_hi:4;
        RBus_UInt32  no_vsync_th_lo:4;
    };
}NO_VSYNC_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  new_vdetect_loss_dn:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  new_vdetect_fine_vphase_th:10;
    };
}NEW_VDETECT_VPHASE_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  new_vdetect_feature_th1:8;
    };
}NEW_VDETECT_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  new_vdetect_feature_th2:8;
    };
}NEW_VDETECT_TH2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  new_vdetect_feature_th3:8;
    };
}NEW_VDETECT_TH3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_feature_th7:8;
        RBus_UInt32  new_vdetect_feature_th6:8;
        RBus_UInt32  new_vdetect_feature_th5:8;
        RBus_UInt32  new_vdetect_feature_th4:8;
    };
}NEW_VDETECT_TH4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpll_kp_ki_div4:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  vstate0_direct_vsync:1;
        RBus_UInt32  vstate0_counter_num:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  vsync_stable_en:1;
        RBus_UInt32  vstate_reset:2;
        RBus_UInt32  vsync_refind_con_sel:2;
        RBus_UInt32  res3:3;
        RBus_UInt32  vsync_refind:1;
        RBus_UInt32  res4:4;
        RBus_UInt32  vstate_2to3_er:4;
    };
}VSTATE_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vstate_2to3_th:8;
        RBus_UInt32  vstate_new2to3_en:1;
        RBus_UInt32  hsync_refind_min:7;
        RBus_UInt32  vstate1_err_sel:1;
        RBus_UInt32  hsync_refind_max:7;
        RBus_UInt32  vstate_1to2_er:4;
        RBus_UInt32  vstate_back1_er:4;
    };
}VSTATE_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  hsync_reset_for_vsync:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  hsync_reset_for_data:10;
        RBus_UInt32  vstate_counter_num:8;
    };
}VSTATE_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vphase_error_window:8;
        RBus_UInt32  res1:3;
        RBus_UInt32  vstate3_err_adjust_en:1;
        RBus_UInt32  vstate3_err_adjust_th:4;
        RBus_UInt32  res2:3;
        RBus_UInt32  vsync_vertical_sum_num:5;
        RBus_UInt32  res3:2;
        RBus_UInt32  vstate_status:2;
        RBus_UInt32  vstate_sw_en:1;
        RBus_UInt32  vstate_sw:2;
        RBus_UInt32  vcr_back_en:1;
    };
}VSTATE_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vloop0_tc1:8;
    };
}VLOOP0_TC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  vloop0_tc2:7;
    };
}VLOOP0_TC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vloop2_tc1:8;
    };
}VLOOP2_TC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  vloop2_tc2:7;
    };
}VLOOP2_TC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vloop3_tc1:8;
    };
}VLOOP3_TC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  vloop3_tc2:7;
    };
}VLOOP3_TC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  vloop0_tc3:2;
        RBus_UInt32  vloop2_tc3:2;
        RBus_UInt32  vloop3_tc3:2;
    };
}VLOOP_TC3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  flag_chrmaunlock_kill:1;
        RBus_UInt32  flag_user_kill:1;
        RBus_UInt32  flag_cgain_too_big_kill:1;
        RBus_UInt32  new_vdetect_lock_en:1;
        RBus_UInt32  vlock_count:3;
    };
}VLOCK_COUNT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_detect_rst:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  vsync_detect_crlock_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  vsync_detect_count_thl:6;
        RBus_UInt32  res3:1;
        RBus_UInt32  vsync_detect_core_thl:11;
        RBus_UInt32  vlock_window:8;
    };
}VLOCK_WINDOW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vlock_phase_plus:8;
    };
}VLOCK_PHASE_PLUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vline_adj_cnt_a:8;
    };
}VLINE_ADJ_CNT_A_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vline_adj_cnt_b:8;
    };
}VLINE_ADJ_CNT_B_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  table_hactive_width:8;
    };
}TABLE_HACTIVE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  vlines_the_same_cnt_thr:4;
        RBus_UInt32  res2:1;
        RBus_UInt32  vsync_freerun_when_unstable_en:1;
        RBus_UInt32  vlines_the_same_flag:1;
        RBus_UInt32  vlines_diff_flag:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  vlines_freerun:10;
    };
}VSYNC_PLL_FREERUN_MUX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  fix_cgain:1;
        RBus_UInt32  res2:16;
        RBus_UInt32  cagc_pll_input_sel:2;
        RBus_UInt32  cagc_data_input_sel:2;
        RBus_UInt32  cagc:8;
    };
}CHROMA_AGC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  ckill_sel:1;
        RBus_UInt32  user_ckill_mode:2;
        RBus_UInt32  vbi_ckill:1;
        RBus_UInt32  hlock_ckill:1;
        RBus_UInt32  chroma_kill:4;
    };
}CHROMA_KILL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  lose_acc_chromalock_level:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  chromalock_input_acc_en:1;
        RBus_UInt32  chromalock_input_acc_num:2;
        RBus_UInt32  lose_chromalock_count:4;
        RBus_UInt32  lose_chromalock_level:3;
        RBus_UInt32  lose_chromalock_ckill:1;
    };
}CHROMA_LOCK_CONFIG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cnew_gate_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  flag358_cresample_lpf_sel:2;
        RBus_UInt32  cagc_igain:2;
    };
}CHROMA_LOOPFILTER_GAIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  cresample_signed_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  cloop_freq_offset_limit_en:1;
        RBus_UInt32  cloop_freq_offset_limit:12;
        RBus_UInt32  secam_cresample_lpf_sel:2;
        RBus_UInt32  cresample_lpf_sel:2;
        RBus_UInt32  cstate:3;
        RBus_UInt32  fixed_cstate:1;
    };
}CHROMA_LOOPFILTER_STATE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  chroma_burst5or10:1;
        RBus_UInt32  fixed_burstgate:1;
        RBus_UInt32  cautopos:5;
    };
}CHROMA_AUTOPOS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chromalock_cstate_en:1;
        RBus_UInt32  chromalock_cstate:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  ckill_vsync_delay_en:1;
        RBus_UInt32  ckill_lb_sel:1;
    };
}CKILL_LB_SEL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ckill_level_user_offset_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ckill_level_user_offset:14;
        RBus_UInt32  ckill_level_user_mode_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  ckill_level_user_mode_value:14;
    };
}CKILL_GAIN_KILL_THL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  badedit_noisy_off_en:1;
        RBus_UInt32  badedit_in_noise_thr:8;
        RBus_UInt32  badedit_out_noise_thr:8;
        RBus_UInt32  fast_lock_en:1;
        RBus_UInt32  phase_fast_lock_en:1;
        RBus_UInt32  badedit_phase_lock_en:1;
        RBus_UInt32  badedit_pulse_detect:1;
        RBus_UInt32  bad_phase_detect:1;
        RBus_UInt32  badedit_line_num:3;
    };
}CSTATE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  badedit_th:8;
    };
}BADEDIT_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  badphase_th:8;
    };
}BADPHASE_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cstate_line_num:8;
    };
}CSTATE_LINE_NUM_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  cpeak_noisy_act_en_pll:1;
        RBus_UInt32  cpeak_noisy_act_en:1;
        RBus_UInt32  cpeak_noise_thr2:8;
        RBus_UInt32  cpeak_noise_thr1:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  chroma_peak_en_pll:1;
        RBus_UInt32  new_cgain_level_en:1;
        RBus_UInt32  chroma_peak_en:1;
        RBus_UInt32  chroma_agc_peak_cnt:6;
    };
}CHROMA_AGC_PEAK_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  chroma_agc_peak_nominal:8;
    };
}CHROMA_AGC_PEAK_NOMINAL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  close_ckill_loopfilter:1;
        RBus_UInt32  cagc_upper_xroot2_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  cagc_upper:14;
    };
}CLOSE_CKILL_LOOPFILTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cagc_peak_err_adj_en:1;
        RBus_UInt32  cagc_burst_err_adj_en:1;
        RBus_UInt32  cagc_peak_err_diff_sel:6;
    };
}CAGC_PEAK_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  cagc_burst_err_diff_sel:6;
    };
}CAGC_PEAK_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  cagc_peak_luma_ratio:6;
    };
}CAGC_PEAK_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  cb_delay:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  cr_delay:3;
    };
}CHROMA_DELAY_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  flag_burst_x4:1;
        RBus_UInt32  burst_cgain_x4_en:1;
    };
}BURST_CGAIN_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_cgain_mag_th:8;
    };
}BURST_CGAIN_MAG_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag358_iir_en:1;
        RBus_UInt32  flag358_iir_cunlock_en:1;
        RBus_UInt32  flag358_cdto_inc:30;
    };
}FLAG358_CDTO_INC4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_location_fix_en:1;
        RBus_UInt32  burst_location_sel_clock:1;
        RBus_UInt32  burst_location_selreg_en:1;
        RBus_UInt32  normal_burst_locationreg_en:1;
        RBus_UInt32  burst_location_sel_modify_sel:3;
        RBus_UInt32  burst_location_sel_modify_en:1;
        RBus_UInt32  burst_location_center_modify_sel:3;
        RBus_UInt32  burst_location_center_modify_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  burst_location_fix:11;
        RBus_UInt32  res2:2;
        RBus_UInt32  burst_location_sel:2;
        RBus_UInt32  burst_location_lpf_reset:1;
        RBus_UInt32  burst_location_rst_en:1;
        RBus_UInt32  auto_burst_location_en:1;
        RBus_UInt32  new_coef_sel:1;
    };
}SEPARATE_443_358_NEW_FUNCTION_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  burst_location_result:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  normal_burst_location:11;
    };
}SEPARATE_443_358_NEW_FUNCTION_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wide_burst_location_modify_sel:3;
        RBus_UInt32  wide_burst_location_modify_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  wide_burst_location_end:11;
        RBus_UInt32  res2:2;
        RBus_UInt32  wide_burst_location_endreg_en:1;
        RBus_UInt32  wide_burst_location_startreg_en:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  wide_burst_location_start:11;
    };
}SEPARATE_443_358_NEW_FUNCTION_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  burst_location_sel_status:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  normal_burst_location_status:11;
    };
}BURST_LOCATION_STATUS_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  wide_burst_location_end_status:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  wide_burst_location_start_status:11;
    };
}BURST_LOCATION_STATUS_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  sep_hsync_start:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  sep_hsync_end:11;
    };
}BURST_LOCATION_HSYNC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  burst_location_auto_en:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  burst_location_enable_mode:8;
        RBus_UInt32  burst_location_magnitude_thr:8;
        RBus_UInt32  burst_location_auto_thr:8;
    };
}BURST_LOCATION_FW_CNTL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_path_eq_en:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  y_path_coef_num:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  y_path_coef_value:11;
    };
}Y_PATH_EQ_FILTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  y_path_coef_num_r:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  y_path_coef_value_r:11;
    };
}Y_PATH_EQ_FILTER_R_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  flag625_vsync_l_sel:1;
        RBus_UInt32  flag625_vsync_l_th:1;
        RBus_UInt32  palm_atone_counter:6;
    };
}PALM_FLAG_COMPENSATION1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  palm_atone_threshold:8;
    };
}PALM_FLAG_COMPENSATION2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  colour_mode_dark_check:1;
        RBus_UInt32  colour_mode_dark_set:3;
        RBus_UInt32  auto_mode_en:1;
        RBus_UInt32  auto_625only_en:1;
        RBus_UInt32  auto_burst_switch_625only:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  state_machine_reset:1;
        RBus_UInt32  manual_mode_select:3;
    };
}MANUAL_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  set_mode_status:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  decision_mode_status:3;
    };
}MODE_DETECTION_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  disable_mode_en:1;
        RBus_UInt32  disable_mode:1;
        RBus_UInt32  statistic_number:6;
    };
}STATISTIC_AND_DISABLE_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  prefer_ntsc50_paln:1;
        RBus_UInt32  prefer_ntsc443_pal60:1;
        RBus_UInt32  prefer_secam_pali:1;
        RBus_UInt32  prefer_ntsc_palm:1;
        RBus_UInt32  prefer_ntsc50_paln_en:1;
        RBus_UInt32  prefer_ntsc443_pal60_en:1;
        RBus_UInt32  prefer_secam_pali_en:1;
        RBus_UInt32  prefer_ntsc_palm_en:1;
    };
}PREFER_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fix_625flag_en:1;
        RBus_UInt32  fix_443flag_en:1;
        RBus_UInt32  fix_palorflag_en:1;
        RBus_UInt32  fix_secamflag_en:1;
        RBus_UInt32  fix_625_h:1;
        RBus_UInt32  fix_443_h:1;
        RBus_UInt32  fix_palor_h:1;
        RBus_UInt32  fix_secam_h:1;
    };
}STATE_MACHINE_FIX_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hactivestartreg_en:1;
        RBus_UInt32  hpixelreg_en:1;
        RBus_UInt32  colourmodereg_en:1;
        RBus_UInt32  hagcreg_en:1;
        RBus_UInt32  vline625reg_en:1;
        RBus_UInt32  cdtomem_reg_en:1;
        RBus_UInt32  vsyncreg_en:1;
        RBus_UInt32  ped_reg_en:1;
    };
}VD_BASIC_REGISTER_ENABLE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  switch_palo_palm_method:2;
        RBus_UInt32  auto_secam_pali_method:2;
        RBus_UInt32  secam_flag_freq_disable:1;
        RBus_UInt32  statistic_multiplier:3;
    };
}AUTO_MODE_S_M_STATISTIC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  new_cr1delay_en:1;
        RBus_UInt32  new_cb1delay_en:1;
        RBus_UInt32  new_y1delay_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  cr1delayreg_en:1;
        RBus_UInt32  cb1delayreg_en:1;
        RBus_UInt32  y1delayreg_en:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  cr1delay:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  cb1delay:6;
        RBus_UInt32  res5:2;
        RBus_UInt32  y1delay:6;
    };
}AUTO_POS_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_pos_modify_en:1;
        RBus_UInt32  auto_pos_mode_sel:3;
        RBus_UInt32  auto_ycdelay_modify_en:1;
        RBus_UInt32  auto_ycdelay_mode_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  ckill_cr1delayreg_en:1;
        RBus_UInt32  ckill_cb1delayreg_en:1;
        RBus_UInt32  ckill_y1delayreg_en:1;
        RBus_UInt32  ckill_cr1delay:6;
        RBus_UInt32  ckill_cb1delay:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  ckill_y1delay:6;
    };
}AUTO_POS_CTRL_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fix_358flag_en:1;
        RBus_UInt32  fix_358_h:1;
        RBus_UInt32  auto_443_358_method_625:2;
        RBus_UInt32  auto_443_358_method_525:2;
        RBus_UInt32  auto_sel_no_burst_625:2;
    };
}FLAG358_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  no_burst_mag_th:8;
    };
}NO_BURST_MAG_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  no_burst_mag_filter_th:8;
    };
}NO_BURST_MAG_FILTER_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_mag_trig_offset:4;
        RBus_UInt32  no_burst_flag:1;
        RBus_UInt32  paln_flag_new:1;
        RBus_UInt32  burst_win_error:1;
        RBus_UInt32  no_burst_443_en:1;
    };
}NO_BURST_443_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  flag358_secam_phase_diff_hcount_en:1;
        RBus_UInt32  flag358_phase_diff_hcount:7;
    };
}FLAG358_SECAM_HCOUNT_RESET_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  flag358_secam_phase_diff_dr:8;
    };
}FLAG358_SECAM_PHASE_DIFF_DR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  flag358_secam_phase_diff_db:8;
    };
}FLAG358_SECAM_PHASE_DIFF_DB_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_mag_th_358:8;
    };
}BURST_MAG_TH_358_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  table_cagc_en:1;
        RBus_UInt32  table_vline_625:1;
        RBus_UInt32  table_hpixel:2;
        RBus_UInt32  table_ped:1;
        RBus_UInt32  table_colour_mode:3;
    };
}AUTO_MODE_TABLE1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  table_hagc:8;
    };
}AUTO_MODE_TABLE2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  table_hactive_start:8;
    };
}AUTO_MODE_TABLE3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  table_vactive_start:8;
    };
}AUTO_MODE_TABLE4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  table_vactive_height:8;
    };
}AUTO_MODE_TABLE5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  table_cdto:30;
    };
}AUTO_MODE_TABLE6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vline_625_vloop_clr_en:1;
        RBus_UInt32  vline_625_src_sel:1;
        RBus_UInt32  new_625flag_window:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  new_625flag_div_thr:10;
        RBus_UInt32  flag_625_counter:8;
    };
}FLAG_625_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  flag_443_counter:8;
    };
}FLAG_443_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_flag_counter:8;
    };
}SECAM_FLAG_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  palm_flag_counter:8;
    };
}PALM_FLAG_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_valid_counter:8;
    };
}BURST_VALID_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  midpoint_adjustment:8;
    };
}MIDPOINT_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  freq_flag_threshold_tune:8;
    };
}FREQ_FLAG_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  frequency_valid_upper_limit:8;
    };
}FREQ_VALID_MAX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  condition_enable:1;
        RBus_UInt32  frequency_valid_inner_limit:7;
    };
}FREQ_VALID_INNER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  frequency_valid_lower_limit:8;
    };
}FREQ_VALID_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_flag_frequency_upper_limit:8;
    };
}SECAM_FLAG_COUNTER_MAX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_flag_frequency_lower_limit:8;
    };
}SECAM_FLAG_COUNTER_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  palm_flag_limit_en:1;
        RBus_UInt32  pal_sw_acc_input_polar:1;
        RBus_UInt32  pal_sw_input_sel:1;
        RBus_UInt32  palm_sw_acc_input_polar:1;
        RBus_UInt32  palm_sw_input_sel:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  pal_flag_threshold:13;
        RBus_UInt32  palm_flag_phase_adjust:8;
    };
}PALM_FLAG_PHASE_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  burst_mag_trigger:4;
        RBus_UInt32  burst_mag_threshold:4;
    };
}BURST_LOWER_LIMIT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vsync_select:1;
        RBus_UInt32  secam_frequency_valid_enable:1;
        RBus_UInt32  auto_noburst_palflag_off:1;
        RBus_UInt32  burst_noise_weighting_auto:1;
        RBus_UInt32  burst_noise_weighting:4;
    };
}BURST_MAG_CHOICE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  agc_gate_kill_sync_white_en:1;
        RBus_UInt32  new_358_flag_cordic:1;
        RBus_UInt32  new_358_flag_cos_sin:1;
        RBus_UInt32  res2:5;
    };
}NEW_358_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  new_dto_358_cnt_up:11;
    };
}NEW_358_CNT_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  new_dto_358_cnt_dn:11;
    };
}NEW_358_CNT_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  sep_count_th:10;
    };
}SEP_COUNT_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  sep_burst_start:11;
    };
}SEP_BURST_START0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  sep_burst_end:11;
    };
}SEP_BURST_END0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  sep_core_burst_rst:1;
        RBus_UInt32  sep_core_burst_rst_en:1;
        RBus_UInt32  res2:8;
    };
}SEP_BURST_RO1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_443_core_burst_hsync:8;
        RBus_UInt32  sep_358_core_burst_hsync:8;
        RBus_UInt32  sep_443_core_burst:8;
        RBus_UInt32  sep_358_core_burst:8;
    };
}SEP_BURST_RO2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  sep_pal_secam_core_burst_rst:1;
        RBus_UInt32  sep_pal_secam_core_burst_rst_en:1;
        RBus_UInt32  sep_pal_secam_core_burst:8;
    };
}SEP_BURST_RO3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  sep_443_thl:8;
        RBus_UInt32  sep_358_thl:8;
    };
}SEP_BURST_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  secam_new_condition:1;
        RBus_UInt32  sep_secam_f_sel:1;
        RBus_UInt32  sep_secam_thl:8;
        RBus_UInt32  sep_secam_thl_ratio:8;
        RBus_UInt32  res2:5;
        RBus_UInt32  power_secam_flag:1;
        RBus_UInt32  power_443_flag:1;
        RBus_UInt32  power_358_flag:1;
    };
}SEP_BURST_FLAG1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  pk_foraudio:1;
        RBus_UInt32  mode_secam2_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  mode_443358pk_sel:2;
    };
}AUTOMODE_443358PK_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dark_badedit_noisy_off_en:1;
        RBus_UInt32  dark_badedit_phase_lock_en:1;
        RBus_UInt32  dark_fast_lock_en:1;
        RBus_UInt32  dark_phase_fast_lock_en:1;
        RBus_UInt32  dark_fixed_cstate:1;
        RBus_UInt32  dark_cstate:3;
        RBus_UInt32  dark_chromalock_cstate_en:1;
        RBus_UInt32  dark_chromalock_cstate:3;
        RBus_UInt32  res1:3;
        RBus_UInt32  dark_cresample_signed_en:1;
        RBus_UInt32  dark_cagc:8;
        RBus_UInt32  dark_cagc_pll_input_sel:2;
        RBus_UInt32  dark_cagc_en:1;
        RBus_UInt32  dark_fix_cgain:1;
        RBus_UInt32  dark_cpll_cdto_change_en:1;
        RBus_UInt32  dark_cpll_cdto_change_mode:3;
    };
}dark_cpll_cdetect_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  dark_cpll_cdto_change_value:30;
    };
}dark_cpll_cdetect_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  dark_palm_flag_counter:8;
        RBus_UInt32  dark_palm_flag_phase_adjust:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_palsw_level:2;
        RBus_UInt32  dark_palm_flag_limit_en:1;
        RBus_UInt32  dark_pal_sw_acc_input_polar:1;
        RBus_UInt32  dark_pal_sw_input_sel:1;
        RBus_UInt32  dark_palm_sw_acc_input_polar:1;
        RBus_UInt32  dark_palm_sw_input_sel:1;
    };
}dark_cpll_pal_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  dark_pal_flag_threshold:13;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_chromalock_input_acc_en:1;
        RBus_UInt32  dark_chromalock_input_acc_num:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  dark_lose_acc_chromalock_level:3;
        RBus_UInt32  dark_lose_chromalock_count:4;
        RBus_UInt32  res4:1;
        RBus_UInt32  dark_lose_chromalock_level:3;
    };
}dark_cpll_chromalock_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  dark_cpll_decide_mode_error:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_cpll_decide_mode:3;
        RBus_UInt32  dark_cpll_vsync_num:8;
        RBus_UInt32  dark_cpll_chromalock_sel:1;
        RBus_UInt32  dark_cpll_mode_en_pali:1;
        RBus_UInt32  dark_cpll_mode_en_pal60:1;
        RBus_UInt32  dark_cpll_mode_en_ntsc443:1;
        RBus_UInt32  dark_cpll_mode_en_paln:1;
        RBus_UInt32  dark_cpll_mode_en_ntsc50:1;
        RBus_UInt32  dark_cpll_mode_en_palm:1;
        RBus_UInt32  dark_cpll_mode_en_ntsc:1;
        RBus_UInt32  dark_cpll_fix_mode_en:1;
        RBus_UInt32  dark_cpll_user_mode:3;
        RBus_UInt32  dark_cpll_mode:2;
        RBus_UInt32  dark_cpll_auto_run:1;
        RBus_UInt32  dark_cpll_start:1;
    };
}dark_cpll_controll_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chromalock_acc_dark:1;
        RBus_UInt32  chromalock_dark:1;
        RBus_UInt32  pal_flag_dark:1;
        RBus_UInt32  palm_flag_dark:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  dark_cpll_loop_done:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_cpll_pali_palm_flag:1;
        RBus_UInt32  dark_cpll_pal60_palm_flag:1;
        RBus_UInt32  dark_cpll_ntsc443_palm_flag:1;
        RBus_UInt32  dark_cpll_paln_palm_flag:1;
        RBus_UInt32  dark_cpll_ntsc50_palm_flag:1;
        RBus_UInt32  dark_cpll_palm_palm_flag:1;
        RBus_UInt32  dark_cpll_ntsc_palm_flag:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  dark_cpll_pali_pal_flag:1;
        RBus_UInt32  dark_cpll_pal60_pal_flag:1;
        RBus_UInt32  dark_cpll_ntsc443_pal_flag:1;
        RBus_UInt32  dark_cpll_paln_pal_flag:1;
        RBus_UInt32  dark_cpll_ntsc50_pal_flag:1;
        RBus_UInt32  dark_cpll_palm_pal_flag:1;
        RBus_UInt32  dark_cpll_ntsc_pal_flag:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  dark_cpll_pali_lock:1;
        RBus_UInt32  dark_cpll_pal60_lock:1;
        RBus_UInt32  dark_cpll_ntsc443_lock:1;
        RBus_UInt32  dark_cpll_paln_lock:1;
        RBus_UInt32  dark_cpll_ntsc50_lock:1;
        RBus_UInt32  dark_cpll_palm_lock:1;
        RBus_UInt32  dark_cpll_ntsc_lock:1;
    };
}dark_cpll_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  hstate_err_irq_en:1;
        RBus_UInt32  vd_irq_en:1;
        RBus_UInt32  vcr_irq_en:1;
        RBus_UInt32  nosig_irq_en:1;
        RBus_UInt32  mode_irq_en:1;
        RBus_UInt32  proscan_irq_en:1;
        RBus_UInt32  noisy_irq_en:1;
        RBus_UInt32  chromalock_irq_en:1;
        RBus_UInt32  vlock_irq_en:1;
        RBus_UInt32  hlock_irq_en:1;
    };
}IRQ_MASK1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  vd_scene_change_irq_en:1;
        RBus_UInt32  ddr_addr_irq_en:1;
        RBus_UInt32  noisy_vbi_irq_en:1;
        RBus_UInt32  coch_irq_en:1;
        RBus_UInt32  mv_irq_en:1;
        RBus_UInt32  field_irq_en:1;
    };
}IRQ_MASK2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ad1_over_irq_en:1;
        RBus_UInt32  ad1_under_irq_en:1;
        RBus_UInt32  ad2_over_irq_en:1;
        RBus_UInt32  ad2_under_irq_en:1;
        RBus_UInt32  ad3_over_irq_en:1;
        RBus_UInt32  ad3_under_irq_en:1;
        RBus_UInt32  ad4_over_irq_en:1;
        RBus_UInt32  ad4_under_irq_en:1;
    };
}IRQ_MASK3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  vcr_irq:1;
        RBus_UInt32  nosig_irq:1;
        RBus_UInt32  mode_irq:1;
        RBus_UInt32  proscan_irq:1;
        RBus_UInt32  noisy_irq:1;
        RBus_UInt32  chromalock_irq:1;
        RBus_UInt32  vlock_irq:1;
        RBus_UInt32  hlock_irq:1;
    };
}IRQ_STATUS1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  hstate_err_irg:1;
        RBus_UInt32  vd_scene_change_irq:1;
        RBus_UInt32  ddr_addr_irq:1;
        RBus_UInt32  noisy_vbi_irq:1;
        RBus_UInt32  coch_irq:1;
        RBus_UInt32  mv_irq:1;
        RBus_UInt32  field_irq:1;
    };
}IRQ_STATUS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ad1_overflow_irq:1;
        RBus_UInt32  ad1_underflow_irq:1;
        RBus_UInt32  ad2_overflow_irq:1;
        RBus_UInt32  ad2_underflow_irq:1;
        RBus_UInt32  ad3_overflow_irq:1;
        RBus_UInt32  ad3_underflow_irq:1;
        RBus_UInt32  ad4_overflow_irq:1;
        RBus_UInt32  ad4_underflow_irq:1;
    };
}IRQ_STATUS3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  adc_over_threh:4;
        RBus_UInt32  adc_under_threh:4;
    };
}ADC_LIMIT_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ld_pause_detect:1;
        RBus_UInt32  ldp_det_en:1;
        RBus_UInt32  ldp_switch_en:1;
        RBus_UInt32  ldpaus_th:5;
    };
}LDPAUSE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  coch_en:1;
        RBus_UInt32  disp_freerun_sel:1;
        RBus_UInt32  vd_out_dvalid_sel_d1:1;
        RBus_UInt32  vcr_disable:1;
        RBus_UInt32  freerun_sel:1;
        RBus_UInt32  lock_h_on_no_signal:1;
        RBus_UInt32  disable_blue_screen_when_vcr:1;
        RBus_UInt32  detect_vcr_when_h_unlock:1;
    };
}VCR_OPTION_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cenable_line_count:8;
    };
}CENABLE_LINE_COUNT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  auto_3dchange_vcr:1;
        RBus_UInt32  auto_3dchange_noisy:1;
        RBus_UInt32  field_toggle_en:1;
        RBus_UInt32  cbcr_ini_mux:1;
        RBus_UInt32  res2:2;
    };
}SIGNAL_STM_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  cdet_phase_err_status:14;
    };
}CDETECT_PHASE_ERR_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  sw_comp:2;
        RBus_UInt32  sw_pr_r:2;
        RBus_UInt32  sw_pb_b:2;
        RBus_UInt32  sw_g:2;
    };
}AD_SW_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  clamp_ad1:2;
        RBus_UInt32  clamp_ad2:2;
        RBus_UInt32  clamp_ad3:2;
        RBus_UInt32  clamp_ad4:2;
    };
}CLAMP_UPDN_EN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  clamp_a_up_en:1;
        RBus_UInt32  clamp_a_dn_en:1;
        RBus_UInt32  clamp_b_up_en:1;
        RBus_UInt32  clamp_b_dn_en:1;
        RBus_UInt32  clamp_c_up_en:1;
        RBus_UInt32  clamp_c_dn_en:1;
        RBus_UInt32  clamp_d_up_en:1;
        RBus_UInt32  clamp_d_dn_en:1;
    };
}CLAMP_RGB_UPDN_EN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  aa3_en:1;
        RBus_UInt32  fb_th:3;
        RBus_UInt32  fb_delay:4;
    };
}FSW_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  fb2rgb_dly:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  rgb2cvbs_dly:6;
    };
}FSW_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  outfifo_444_sel:1;
        RBus_UInt32  scart_en:1;
        RBus_UInt32  yout_limit:1;
        RBus_UInt32  fb_inv:1;
        RBus_UInt32  cout_limit:1;
        RBus_UInt32  out444_sel:1;
        RBus_UInt32  aa422_en:1;
        RBus_UInt32  fb_sw:1;
        RBus_UInt32  fb_en:1;
    };
}FSW_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fb_thmax:4;
        RBus_UInt32  fb_thmin:4;
    };
}FSW_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  contrast2:8;
    };
}LUMA_CONTRAST2_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  brightness2:8;
    };
}LUMA_BRIGHTNESS2_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cr_saturation:8;
    };
}CHROMA_SATURATION2_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cb_saturation:8;
    };
}CB_SAT_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  peak_range2:2;
        RBus_UInt32  peak_gain2:3;
        RBus_UInt32  peak_en2:1;
    };
}LUMA_PEAKING2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  fbgain_en:1;
        RBus_UInt32  fbgain:7;
    };
}FSW_GAIN_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  scart_vbi_rgb_sel:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  fb_status:3;
    };
}FSW_INPUT_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  yorr_in_offset_status:12;
    };
}ADCR_CALI_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  uorg_in_offset_status:12;
    };
}ADCG_CALI_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  vorb_in_offset_status:12;
    };
}ADCB_CALI_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  rgb_output_en:1;
        RBus_UInt32  res2:7;
    };
}ADC_GAIN_R1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  gain_r:10;
    };
}ADC_GAIN_R_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  gain_g:10;
    };
}ADC_GAIN_G_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  gain_b:10;
    };
}ADC_GAIN_B_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  offset_r:8;
    };
}ADC_OFFSET_R_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  offset_g:8;
    };
}ADC_OFFSET_G_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  offset_b:8;
    };
}ADC_OFFSET_B_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  r_prblevel:12;
    };
}CLAMP_TEST_REG0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  g_blevel:12;
    };
}CLAMP_TEST_REG2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  b_pbblevel:12;
    };
}CLAMP_TEST_REG4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  comp_blevel:12;
    };
}CLAMP_TEST_REG6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  comp_slevel:12;
    };
}CLAMP_TEST_REG8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  vbi_blevel:12;
    };
}CLAMP_TEST_REG11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  hphase_err_status:14;
    };
}HDETECT_PHASE_ERR_STATUS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  avout_fifo_sel:1;
        RBus_UInt32  avout_fifo_rd_ptr:11;
    };
}AVOUT_FIFO_RD_PTR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  blank_level_comp_manu_add:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  blank_level_comp_manu:12;
    };
}BLANK_LEVEL_MANU_COMP_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  blank_level_c_manu:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  blank_level_r_manu:12;
    };
}BLANK_LEVEL_MANU_C_R_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  blank_level_g_manu:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  blank_level_b_manu:12;
    };
}BLANK_LEVEL_MANU_G_B_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test1:31;
        RBus_UInt32  factory_flag:1;
    };
}FPGA_TEST_REG1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test2:32;
    };
}FPGA_TEST_REG2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test3:32;
    };
}FPGA_TEST_REG3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test4:32;
    };
}FPGA_TEST_REG4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test5:32;
    };
}FPGA_TEST_REG5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test6:32;
    };
}FPGA_TEST_REG6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test7:32;
    };
}FPGA_TEST_REG7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test8:32;
    };
}FPGA_TEST_REG8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  secam_y_fir_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  secam_y_hpf_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  secam_y_lpf_sel:3;
        RBus_UInt32  drdb_freq_const:1;
        RBus_UInt32  drdb_vlpf_en:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  secam_flag_sel:1;
        RBus_UInt32  res5:2;
        RBus_UInt32  secam_notch_filter:2;
    };
}SECAM_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dr_offset:8;
    };
}SECAM_DRFREQ_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  db_offset:8;
    };
}SECAM_DBFREQ_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_phase_diff_hcount_en:1;
        RBus_UInt32  secam_phase_diff_hcount:7;
    };
}SECAM_HCOUNT_RESET_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_phase_diff_dr:8;
    };
}PHASE_DIFF_DR_RST_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_phase_diff_db:8;
    };
}PHASE_DIFF_DB_RST_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_gain_drdb_en:1;
        RBus_UInt32  secam_gain_drdb:7;
    };
}DRDB_GAIN_TABLE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_gain_y_en:1;
        RBus_UInt32  secam_gain_y:7;
    };
}Y_GAIN_TABLE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  secam_gain_delay:5;
    };
}SECAM_GAIN_DLY_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  secam_gain_debug_en:1;
        RBus_UInt32  secam_gain_debug:7;
    };
}SECAM_GAIN_TABLE_DEBUG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  new_secam_phase_diff_hcount_en:1;
        RBus_UInt32  new_secam_phase_diff_hcount:7;
    };
}NEW_SECAM_HCOUNT_RESET_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  new_secam_phase_diff_dr:8;
    };
}NEW_SECAM_PHASE_DIFF_DR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  new_secam_phase_diff_db:8;
    };
}NEW_SECAM_PHASE_DIFF_DB_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  new_secam_cdto_inc:30;
    };
}NEW_SECAM_CDTO_INC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_gp_en:1;
        RBus_UInt32  res1:9;
        RBus_UInt32  secam_gp_step:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  secam_gp_thl:10;
    };
}SECAM_GP_RM_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vdec_ps_disp_27_en:1;
        RBus_UInt32  hresampler_combi_delay:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  vd_output_135_sel:1;
        RBus_UInt32  vd_output_27_repeat_sel:1;
        RBus_UInt32  vd_output_27_repeat_en:1;
        RBus_UInt32  res2:16;
        RBus_UInt32  v8format_sel:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  ps_updn_swap:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  fifo_initialization:1;
    };
}FIFO_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  ps_540_coe_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  ps_540_select_tap:5;
        RBus_UInt32  res3:1;
        RBus_UInt32  ps_540_coe_modify:7;
        RBus_UInt32  res4:6;
        RBus_UInt32  fifo_full_status:1;
        RBus_UInt32  fifo_empty_status:1;
    };
}FIFO_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  pll_i_gain:8;
    };
}I_GAIN_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  fifo_wo_ps:1;
        RBus_UInt32  fifo_depth_wo_ps:8;
        RBus_UInt32  res2:2;
        RBus_UInt32  swallow_freq_sel:2;
        RBus_UInt32  swallow_on_vsync:1;
        RBus_UInt32  ndivload_en:1;
        RBus_UInt32  ps_up_en:1;
        RBus_UInt32  ps_dn_en:1;
        RBus_UInt32  pll_div:4;
    };
}MISC_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  fifo_depth_min_clr:1;
        RBus_UInt32  fifo_depth_min_status:8;
    };
}FIFO_DEPTH_MIN_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  fifo_depth_max_clr:1;
        RBus_UInt32  fifo_depth_max_status:8;
    };
}FIFO_DEPTH_MAX_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ps_up_i:1;
        RBus_UInt32  ps_dn_i:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  ps_divload:1;
        RBus_UInt32  ps_pselload:1;
    };
}PLL_DEBUG_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  pll_debug_en:1;
        RBus_UInt32  ps_psel:3;
        RBus_UInt32  ps_ndiv:4;
    };
}PLL_DEBUG_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  ps_fix_en:1;
        RBus_UInt32  ps_fix_value:8;
        RBus_UInt32  ps_new_kikp:1;
        RBus_UInt32  ps_new_kp:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  cnt_en:1;
        RBus_UInt32  period_sel:2;
        RBus_UInt32  lpf_en:1;
        RBus_UInt32  k_sel:2;
    };
}DISP_FSYNC_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_wo_ps_read_repeat_en:1;
        RBus_UInt32  fifo_wo_ps_clk_jump:1;
        RBus_UInt32  fifo_wo_ps_err_act:1;
        RBus_UInt32  fifo_wo_ps_adapt:1;
        RBus_UInt32  fifo_wo_ps_hlen_min:12;
        RBus_UInt32  fifo_depth_wo_ps_min:8;
        RBus_UInt32  fifo_depth_wo_ps_max:8;
    };
}FIFO_WO_PS_FUNC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  fifo_wo_ps_ps_up_i1:1;
        RBus_UInt32  fifo_wo_ps_ps_dn_i1:1;
        RBus_UInt32  fifo_wo_ps_ps_pselload1:1;
        RBus_UInt32  fifo_wo_ps_ps_divload1:1;
        RBus_UInt32  fifo_wo_ps_ps_psel1:3;
        RBus_UInt32  fifo_wo_ps_ps_ndiv1:5;
        RBus_UInt32  fifo_wo_ps_ps_up_i0:1;
        RBus_UInt32  fifo_wo_ps_ps_dn_i0:1;
        RBus_UInt32  fifo_wo_ps_ps_pselload0:1;
        RBus_UInt32  fifo_wo_ps_ps_divload0:1;
        RBus_UInt32  fifo_wo_ps_ps_psel0:3;
        RBus_UInt32  fifo_wo_ps_ps_ndiv0:5;
    };
}FIFO_WO_PS_CLK_STATE_PARAMETER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  stable_fifo_depth:8;
        RBus_UInt32  res2:3;
        RBus_UInt32  fifo_clk_state:1;
        RBus_UInt32  fifo_out_line_len:12;
    };
}FIFO_STATUS_NO_PLL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  debug_test_enable:1;
        RBus_UInt32  debug_test:7;
    };
}DEBUG_MUX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  muxanalogb:4;
        RBus_UInt32  muxanaloga:4;
    };
}VIDEO_DEBUG_ANALOG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  clk_dac_polarity:1;
        RBus_UInt32  clk_sct_polarity:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  debug_test_dac_en:1;
        RBus_UInt32  muxdigital:4;
    };
}VIDEO_DEBUG_DIGITAL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  patgen_vline_vactive_end:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  patgen_vline:10;
        RBus_UInt32  patgen_vline_en:1;
        RBus_UInt32  fifo_out_pattern_gen_en:1;
        RBus_UInt32  pattern_gen_scart_en:1;
        RBus_UInt32  crc_chk_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  pattern_gen_input_mode_sel:1;
        RBus_UInt32  pattern_gen_cvbs_mode:1;
        RBus_UInt32  pattern_generator_enable:1;
    };
}PATTERN_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_result:32;
    };
}CRC_RESULT3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  clk_vdadc_polarity:1;
        RBus_UInt32  clk_polarity:1;
        RBus_UInt32  patgen_sync_gain:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  patgen_burst_gain:3;
    };
}PATGEN_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_mode_out:1;
        RBus_UInt32  bist_mode_fifo:1;
        RBus_UInt32  bist_mode_dma:1;
        RBus_UInt32  bist_mode_27_2:1;
        RBus_UInt32  bist_mode_27_1:1;
    };
}BIST_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_done_out:1;
        RBus_UInt32  bist_done_fifo:1;
        RBus_UInt32  bist_done_dma:1;
        RBus_UInt32  bist_done_27_2:1;
        RBus_UInt32  bist_done_27_1:1;
    };
}BIST_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_fail_out:1;
        RBus_UInt32  bist_fail_fifo:1;
        RBus_UInt32  bist_fail_dma:1;
        RBus_UInt32  bist_fail_27_2:1;
        RBus_UInt32  bist_fail_27_1:1;
    };
}BIST_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_drf_mode_out:1;
        RBus_UInt32  bist_drf_mode_fifo:1;
        RBus_UInt32  bist_drf_mode_dma:1;
        RBus_UInt32  bist_drf_mode_27_2:1;
        RBus_UInt32  bist_drf_mode_27_1:1;
    };
}BIST_DRF_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_drf_resume_out:1;
        RBus_UInt32  bist_drf_resume_fifo:1;
        RBus_UInt32  bist_drf_resume_dma:1;
        RBus_UInt32  bist_drf_resume_27_2:1;
        RBus_UInt32  bist_drf_resume_27_1:1;
    };
}BIST_DRF_RESUME_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_drf_done_out:1;
        RBus_UInt32  bist_drf_done_fifo:1;
        RBus_UInt32  bist_drf_done_dma:1;
        RBus_UInt32  bist_drf_done_27_2:1;
        RBus_UInt32  bist_drf_done_27_1:1;
    };
}BIST_DRF_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_drf_pause_out:1;
        RBus_UInt32  bist_drf_pause_fifo:1;
        RBus_UInt32  bist_drf_pause_dma:1;
        RBus_UInt32  bist_drf_pause_27_2:1;
        RBus_UInt32  bist_drf_pause_27_1:1;
    };
}BIST_DRF_PAUSE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_drf_fail_out:1;
        RBus_UInt32  bist_drf_fail_fifo:1;
        RBus_UInt32  bist_drf_fail_dma:1;
        RBus_UInt32  bist_drf_fail_27_2:1;
        RBus_UInt32  bist_drf_fail_27_1:1;
    };
}BIST_DRF_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  bist_mem_fail_27_1:6;
    };
}BIST_FAIL_27_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  bist_mem_fail_27_2:10;
    };
}BIST_FAIL_27_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_mem_fail_dma:5;
    };
}BIST_FAIL_DMA_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_mem_fail_fifo:1;
    };
}BIST_FAIL_FIFO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  bist_mem_fail_out:4;
    };
}BIST_FAIL_OUT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:26;
        RBus_UInt32  bist_drf_mem_fail_27_1:6;
    };
}BIST_DRF_FAIL_27_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  bist_drf_mem_fail_27_2:10;
    };
}BIST_DRF_FAIL_27_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  bist_drf_mem_fail_dma:5;
    };
}BIST_DRF_FAIL_DMA_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  bist_drf_mem_fail_fifo:1;
    };
}BIST_DRF_FAIL_FIFO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  bist_drf_mem_fail_out:4;
    };
}BIST_DRF_FAIL_OUT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  mbist_dvs_out:4;
        RBus_UInt32  mbist_dvse_out:1;
        RBus_UInt32  mbist_dvs_fifo:4;
        RBus_UInt32  mbist_dvse_fifo:1;
        RBus_UInt32  mbist_dvs_dma:4;
        RBus_UInt32  mbist_dvse_dma:1;
        RBus_UInt32  mbist_dvs_27_2:4;
        RBus_UInt32  mbist_dvse_27_2:1;
        RBus_UInt32  mbist_dvs_27_1:4;
        RBus_UInt32  mbist_dvse_27_1:1;
    };
}BIST_DVSE_DVS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  mbist_ls_cntl:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  mbist_dvs_fifo_2:4;
        RBus_UInt32  mbist_dvse_fifo_2:1;
        RBus_UInt32  mbist_dvs_dma_2:4;
        RBus_UInt32  mbist_dvse_dma_2:1;
    };
}BIST_DVSE_DVS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  adc_updn_debug_en:1;
        RBus_UInt32  adc_updn_debug_up:1;
        RBus_UInt32  adc_updn_debug_dn:1;
    };
}ADC_UPDN_CTRL_RBUS;





#else //apply LITTLE_ENDIAN


//======VDTOP register structure define==========
typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:1;
        RBus_UInt32  colour_mode:3;
        RBus_UInt32  vline_625:1;
        RBus_UInt32  hpixel:2;
        RBus_UInt32  hv_delay:1;
        RBus_UInt32  res1:24;
    };
}VIDEO_CONTROL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ped:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  yc_src:1;
        RBus_UInt32  cv_src:1;
        RBus_UInt32  cv_inv:1;
        RBus_UInt32  vd_pq_bypass_en:1;
        RBus_UInt32  ycsepdata_burstin_en:1;
        RBus_UInt32  res1:22;
    };
}VIDEO_CONTROL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  no_signal:1;
        RBus_UInt32  hlock:1;
        RBus_UInt32  vlock:1;
        RBus_UInt32  chomalock:1;
        RBus_UInt32  mv_vbi_detected:1;
        RBus_UInt32  mv_colour_inverse:3;
        RBus_UInt32  h_fine_lock:1;
        RBus_UInt32  chromalock_acc:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hlock_longtime:1;
        RBus_UInt32  vlock_longtime:1;
        RBus_UInt32  hvlock_longtime:1;
        RBus_UInt32  res1:17;
    };
}VIDEO_STATUS_REG1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  proscan_detected:1;
        RBus_UInt32  palm_flag:1;
        RBus_UInt32  palor_flag:1;
        RBus_UInt32  burst_detect:1;
        RBus_UInt32  detect443_flag:1;
        RBus_UInt32  noisy_vbi:1;
        RBus_UInt32  vlock_new:1;
        RBus_UInt32  detect358_flag:1;
        RBus_UInt32  v_detect_flag:1;
        RBus_UInt32  firtst_vsync_detected:1;
        RBus_UInt32  res1:22;
    };
}VIDEO_STATUS_REG2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pal_detected:1;
        RBus_UInt32  secam_detected:1;
        RBus_UInt32  lines_625_detected:1;
        RBus_UInt32  noisy:1;
        RBus_UInt32  vcr:1;
        RBus_UInt32  vcr_trick:1;
        RBus_UInt32  vcr_ff:1;
        RBus_UInt32  vcr_rew:1;
        RBus_UInt32  res1:24;
    };
}VIDEO_STATUS_REG3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdto_inc_status:30;
        RBus_UInt32  res1:2;
    };
}HDTO_INC_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cdto_inc_status:30;
        RBus_UInt32  res1:2;
    };
}CDTO_INC_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_magnitude:8;
        RBus_UInt32  res1:24;
    };
}AVG_BURST_MAG_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_dgain:12;
        RBus_UInt32  res1:20;
    };
}AGC_DGAIN_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  status_cmag:8;
        RBus_UInt32  res1:24;
    };
}CMAG_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  status_cgain:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  status_cgain_data:14;
        RBus_UInt32  res1:2;
    };
}CGAIN_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  status_cordiq_freq:8;
        RBus_UInt32  res1:24;
    };
}CORDIC_FREQ_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_1st_line:10;
        RBus_UInt32  res1:22;
    };
}MEASURE_FIRST_V_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  v_2nd_line:10;
        RBus_UInt32  res1:22;
    };
}MEASURE_SECOND_V_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  porch_h:13;
        RBus_UInt32  res1:19;
    };
}PORCH_HEIGHT_M_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  status_noise:8;
        RBus_UInt32  res1:24;
    };
}NOISE_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  noise_thresh:8;
        RBus_UInt32  res1:24;
    };
}NOISE_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdto_inc:30;
        RBus_UInt32  res1:1;
        RBus_UInt32  hdto_fixed:1;
    };
}HSYNC_DTO_INC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cdto_inc:30;
        RBus_UInt32  res1:1;
        RBus_UInt32  cdto_fixed:1;
    };
}CHROMA_DTO_INC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chip_ver:16;
        RBus_UInt32  res1:16;
    };
}CHIP_VER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blank_vid_offset_value:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  blank_vid_offset_manu_en:1;
        RBus_UInt32  res1:19;
    };
}BLANK_VID_OFFSET_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  contrast:8;
        RBus_UInt32  res1:24;
    };
}LUMA_CONTRAST_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  brightness:8;
        RBus_UInt32  res1:24;
    };
}LUMA_BRIGHTNESS_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  saturation:8;
        RBus_UInt32  res1:24;
    };
}CHROMA_SATURATION_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hue:8;
        RBus_UInt32  res1:24;
    };
}CHROMA_HUE_PHASE_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blue_screen_y:8;
        RBus_UInt32  res1:24;
    };
}BLUE_SCREEN_Y_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blue_screen_cb:8;
        RBus_UInt32  res1:24;
    };
}BLUE_SCREEN_CB_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blue_screen_cr:8;
        RBus_UInt32  res1:24;
    };
}BLUE_SCREEN_CR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  yc_delay:4;
        RBus_UInt32  blue_mode:2;
        RBus_UInt32  cbcr_swap:1;
        RBus_UInt32  snow_freerun_en:1;
        RBus_UInt32  motion_delay:4;
        RBus_UInt32  res1:20;
    };
}OUTPUT_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clamp_if_dn_en:1;
        RBus_UInt32  clamp_if_up_en:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  sw_tu_cvbs:1;
        RBus_UInt32  fe_bypass_sel:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  avout_hsync_end:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  avout_hsync_start:10;
        RBus_UInt32  res1:2;
    };
}INOUT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avout_fifo_status_empty:1;
        RBus_UInt32  avout_fifo_status_full:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  avout_mixer_sel:4;
        RBus_UInt32  res2:3;
        RBus_UInt32  avout_test_in:12;
        RBus_UInt32  output_delay_0_180_sw:1;
        RBus_UInt32  output_fifo_empty:1;
        RBus_UInt32  output_fifo_full:1;
        RBus_UInt32  res1:5;
    };
}AVOUT_FIFO_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avout_ifdebug_sel:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  avout_ifdebug_shift:4;
        RBus_UInt32  avout_ifdebug_mask:12;
        RBus_UInt32  avout_ifdebug_inv:12;
    };
}AVOUT_IFDEBUG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_peak_nominal:7;
        RBus_UInt32  hagc_err_coring_en:1;
        RBus_UInt32  peak_deb_thl:8;
        RBus_UInt32  peak_deb_limit:9;
        RBus_UInt32  peak_data_sel:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  peak_diff_sel:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  peak_deb_en:1;
    };
}AGC_PEAK_NOMINAL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_peak_cntl:3;
        RBus_UInt32  agc_peak_en:1;
        RBus_UInt32  agc_gate_kill_mode:2;
        RBus_UInt32  agc_gate_vsync_stip:1;
        RBus_UInt32  agc_gate_vsync_coarse:1;
        RBus_UInt32  agc_gate_kill_w_hlock:1;
        RBus_UInt32  agc_gate_kill_mode_sel:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  agc_peak_nominal_ycsep:12;
        RBus_UInt32  ycsep_data_decrease_ratio:3;
        RBus_UInt32  ycsep_data_decrease_en:1;
        RBus_UInt32  ycsep_data_offset_div2_en:1;
        RBus_UInt32  chroma_path_dgain_after_en:1;
        RBus_UInt32  res1:2;
    };
}AGC_PEAK_AND_GATE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_peak_loop_gain:2;
        RBus_UInt32  hagc_err_coring_th:5;
        RBus_UInt32  unlock_peakrst_en:1;
        RBus_UInt32  diff_level:12;
        RBus_UInt32  peak_gain:12;
    };
}AGC_PEAK_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hagc_en:1;
        RBus_UInt32  cagc_en:1;
        RBus_UInt32  bgate_raw_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  dc_clamp_mode:2;
        RBus_UInt32  mv_hagc_mode:1;
        RBus_UInt32  hagc_field_mode:1;
        RBus_UInt32  under_gain:12;
        RBus_UInt32  dgain_state:2;
        RBus_UInt32  res2:6;
        RBus_UInt32  fix_dgain:1;
        RBus_UInt32  res1:3;
    };
}VIDEO_CONTROL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hagc:8;
        RBus_UInt32  dgain_status_counter:12;
        RBus_UInt32  peak_under_round_thl:8;
        RBus_UInt32  peak_under_round_en:1;
        RBus_UInt32  dgain_status_triger:1;
        RBus_UInt32  res1:2;
    };
}LUMA_AGC_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_gate_start:11;
        RBus_UInt32  res1:21;
    };
}AGC_GATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_gate_width:7;
        RBus_UInt32  res1:25;
    };
}AGC_GATE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_bp_delay:8;
        RBus_UInt32  res1:24;
    };
}AGC_BP_DELAY_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clampagc_under_th2:6;
        RBus_UInt32  res1:26;
    };
}CLAMPAGC_COMPLUMA_NEW_THRESHOLD2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clampagc_under_th1:4;
        RBus_UInt32  res3:3;
        RBus_UInt32  under_flag:1;
        RBus_UInt32  agc_under_loop_gain:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  data_path_dgain_div2_en:1;
        RBus_UInt32  res1:19;
    };
}CLAMPAGC_COMPLUMA_NEW_THRESHOLD1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blank_vid_offset:1;
        RBus_UInt32  clampagc_under_en:1;
        RBus_UInt32  clampagc_under_cntl:6;
        RBus_UInt32  under_deb_thl:8;
        RBus_UInt32  under_deb_limit:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  under_diff_sel:2;
        RBus_UInt32  under_gate_en:1;
        RBus_UInt32  under_deb_en:1;
    };
}CLAMPAGC_COMPLUMA_NEW_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_agc_min:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  under_gate_st:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  under_gate_end:10;
        RBus_UInt32  res1:2;
    };
}VSYNC_AGC_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_agc_max:6;
        RBus_UInt32  vsync_clamp_mode:2;
        RBus_UInt32  res1:24;
    };
}VSYNC_AGC_LOCKOUT_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cpump_delay_en:1;
        RBus_UInt32  cpump_adjust_polarity:1;
        RBus_UInt32  cpump_adjust_delay:6;
        RBus_UInt32  auto_dc_restore_disable_ad1_updn:1;
        RBus_UInt32  auto_dc_restore_disable_ad2_updn:1;
        RBus_UInt32  auto_dc_restore_disable_ad3_updn:1;
        RBus_UInt32  auto_dc_restore_disable_ad4_updn:1;
        RBus_UInt32  auto_dc_restore_en0:1;
        RBus_UInt32  auto_dc_restore_en1:1;
        RBus_UInt32  auto_dc_restore_en2:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  auto_dc_restore_sel:3;
        RBus_UInt32  res1:13;
    };
}CHARGE_PUMP_DELAY_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cpump_adjust:8;
        RBus_UInt32  res1:24;
    };
}CHARGE_PUMP_ADJUSTMENT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cpump_delay:8;
        RBus_UInt32  res1:24;
    };
}CHARGE_PUMP_DELAY_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc_gate_thresh:5;
        RBus_UInt32  adc_cbcr_pump_swap:1;
        RBus_UInt32  adc_input_swap:1;
        RBus_UInt32  adc_updn_swap:1;
        RBus_UInt32  res1:24;
    };
}AGC_GATE_TH_SWAP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clampagc_rc_rate:4;
        RBus_UInt32  new_clamp_rc_rate_en:1;
        RBus_UInt32  measure_dc_rough:1;
        RBus_UInt32  dgain_ignore_fine_lock:1;
        RBus_UInt32  measure_dc_128_64_sel:1;
        RBus_UInt32  res1:24;
    };
}NEW_CLAMPAGC_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  measure_dc_rough_dn:8;
        RBus_UInt32  res1:24;
    };
}MEASURE_DC_ROUGH_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  measure_dc_rough_up:8;
        RBus_UInt32  res1:24;
    };
}MEASURE_DC_ROUGH_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  measure_dc_th_dn:12;
        RBus_UInt32  res1:20;
    };
}MEASURE_DC_TH_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  measure_dc_th_up:12;
        RBus_UInt32  res1:20;
    };
}MEASURE_DC_TH_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsag_agc_peak_cntl:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  vsag_rc_input:1;
        RBus_UInt32  res1:24;
    };
}VSAG_CNTL_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  peak_vsag:13;
        RBus_UInt32  res1:19;
    };
}PEAK_VSAG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  field_kill_rst:1;
        RBus_UInt32  lose_bgate_flag:1;
        RBus_UInt32  lose_sgate_flag:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  new_under_th2_en:1;
        RBus_UInt32  new_under_gain_en:1;
        RBus_UInt32  new_total_under_en:1;
        RBus_UInt32  res1:25;
    };
}KILL_FIELD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  field_kill_num:10;
        RBus_UInt32  res1:22;
    };
}FIELD_KILL_MUN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  kill_gate_up:11;
        RBus_UInt32  res1:21;
    };
}KILL_GATE_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  kill_gate_dn:11;
        RBus_UInt32  res1:21;
    };
}KILL_GATE_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res3:1;
        RBus_UInt32  sync_midpt_lowest_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  syncmidpt_add_level_h:2;
        RBus_UInt32  res1:26;
    };
}syncmidpt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  syncmidpt_fix_add_value_h:8;
        RBus_UInt32  res1:24;
    };
}syncmidpt_fix_add_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lpfsync_plus_diff:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  lpfsync_plus_rm:1;
        RBus_UInt32  lpfsync_plus_w_hlock:2;
        RBus_UInt32  res1:22;
    };
}lpfsync_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  spike_min_thresh:8;
        RBus_UInt32  res1:24;
    };
}spike_min_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  spike_max_thresh:8;
        RBus_UInt32  res1:24;
    };
}spike_max_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  spike_detected_up:10;
        RBus_UInt32  spike_detected:1;
        RBus_UInt32  res1:21;
    };
}spike_detected_up_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  spike_detected_dn:10;
        RBus_UInt32  res1:22;
    };
}spike_detected_dn_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lpfsync_plus_dc:8;
        RBus_UInt32  res1:24;
    };
}lpfsync_plus_dc_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_error_avg_sel:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  hdetect_error_avg_length:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  hdetect_error_avg_interval:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  hstate_error_rst:1;
        RBus_UInt32  hstate_error_dn_count:8;
        RBus_UInt32  hstate_error_thl:8;
        RBus_UInt32  res1:4;
    };
}HDETECT_ERR_VAR_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_error_mean:16;
        RBus_UInt32  hdetect_error_var:16;
    };
}HDETECT_ERR_VAR_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  locked_count_clean_max:4;
        RBus_UInt32  locked_count_noisy_max:4;
        RBus_UInt32  locked_count_vcrtrick_max:4;
        RBus_UInt32  hstate_vsync_error_start:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  hstate_vsync_error_end:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  hstate_vsync_error_num_thr:4;
    };
}LOCK_COUNT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hstate_max:3;
        RBus_UInt32  hstate_unlocked:1;
        RBus_UInt32  disable_hfine:1;
        RBus_UInt32  hstate_fixed:1;
        RBus_UInt32  hlock_vsync_mode:2;
        RBus_UInt32  hstate_vsync_error_unbalance:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  hstate_vsync_error_hlock_en:1;
        RBus_UInt32  hstate_vsync_error_vlock_en:1;
        RBus_UInt32  hstate_vsync_error_noisy_en:1;
        RBus_UInt32  hstate_vsync_error_num_en:1;
        RBus_UInt32  hstate_vsync_error_value_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  hstate_vsync_error_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  hstate_vsync_error_unbalance_en:1;
        RBus_UInt32  hstate_vsync_error_unbalance_status:1;
        RBus_UInt32  res1:6;
    };
}H_LOOP_MAXSTATE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gate_end_thresh:5;
        RBus_UInt32  fine_gate_sel:1;
        RBus_UInt32  coarse_src_sel:1;
        RBus_UInt32  fine_src_sel:1;
        RBus_UInt32  coarse_phase_rising_en:1;
        RBus_UInt32  hpll_fine_lock_data_sel:1;
        RBus_UInt32  auto_fine_phase_sel_en:1;
        RBus_UInt32  fine_hstate_to_5:1;
        RBus_UInt32  auto_fine_phase_sel:1;
        RBus_UInt32  hstate_ignore_err:1;
        RBus_UInt32  hstate_hlock_sel:1;
        RBus_UInt32  cpll_hpll_use_front_vactive:1;
        RBus_UInt32  fine_phase_error_thl:10;
        RBus_UInt32  res1:6;
    };
}CLAMPAGC_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coarse_sync_start:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  hstate_vsync_error_noisy_upper_th:8;
        RBus_UInt32  hstate_vsync_error_noisy_lower_th:8;
        RBus_UInt32  res1:8;
    };
}CLAMPAGC_NEW_SYNC_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coarse_sync_end:8;
        RBus_UInt32  hstate_vsync_error_abs_thr:8;
        RBus_UInt32  hstate_vsync_error_value_thr:8;
        RBus_UInt32  res1:8;
    };
}CLAMPAGC_NEW_SYNC_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coarse_backporch_start:7;
        RBus_UInt32  agc_trailing_sel:1;
        RBus_UInt32  hstate_err:14;
        RBus_UInt32  res1:10;
    };
}CLAMPAGC_NEW_BACKPORCH_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coarse_backporch_end:8;
        RBus_UInt32  hstate_err_in_vcount:10;
        RBus_UInt32  res1:14;
    };
}CLAMPAGC_NEW_BACKPORCH_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fine_phase_sel:1;
        RBus_UInt32  coarse_phase_sel:1;
        RBus_UInt32  killgate_sel:1;
        RBus_UInt32  agc_clamping_trailing_sel:1;
        RBus_UInt32  nosignal_hlock_check_en:1;
        RBus_UInt32  lpfsync_force_blank_en:1;
        RBus_UInt32  res1:26;
    };
}HDETECT_PHASE_SEL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lsync_tip_start:8;
        RBus_UInt32  res1:24;
    };
}HDETECT_COUNTER_TIP_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lsync_tip_end:8;
        RBus_UInt32  res1:24;
    };
}HDETECT_COUNTER_TIP_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lporch_start:8;
        RBus_UInt32  res1:24;
    };
}HDETECT_COUNTER_BACKPORCH_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lporch_end:8;
        RBus_UInt32  res1:24;
    };
}HDETECT_COUNTER_BACKPORCH_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_integral_ext:1;
        RBus_UInt32  hpll_integral_rst:1;
        RBus_UInt32  res1:30;
    };
}HPLL_INTEGRAL_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hstate_status:3;
        RBus_UInt32  hstate_loopfilter_sw:1;
        RBus_UInt32  hstate_vcr_max:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  hstate_impn_max:3;
        RBus_UInt32  mode_vcr_setting_change_en:1;
        RBus_UInt32  cstate_impn_max:3;
        RBus_UInt32  impulsive_noise_disable_pll_en:1;
        RBus_UInt32  vsync_freerun_when_unstable_en_vcr:1;
        RBus_UInt32  second_pll_en_vcr:1;
        RBus_UInt32  dgain_ignore_fine_lock_vcr:1;
        RBus_UInt32  gate_iir_v_sel_vcr:1;
        RBus_UInt32  gate_iir_h_sel_vcr:1;
        RBus_UInt32  new_hpll_lpf_sel_vcr:1;
        RBus_UInt32  agc_gate_kill_mode_vcr:2;
        RBus_UInt32  vsync_freerun_when_unstable_en_status:1;
        RBus_UInt32  second_pll_en_status:1;
        RBus_UInt32  dgain_ignore_fine_lock_status:1;
        RBus_UInt32  gate_iir_v_sel_status:1;
        RBus_UInt32  gate_iir_h_sel_status:1;
        RBus_UInt32  new_hpll_lpf_sel_status:1;
        RBus_UInt32  agc_gate_kill_mode_status:2;
    };
}HDETECT_LOOPFILTER_SW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_loopfilter_dctrl2:4;
        RBus_UInt32  hdetect_loopfilter_dctrl1:4;
        RBus_UInt32  res1:24;
    };
}HDETECT_LOOPFILTER_DCTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_start:8;
        RBus_UInt32  res1:24;
    };
}HSYNC_PULSE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_width:8;
        RBus_UInt32  res1:24;
    };
}HSYNC_PULSE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hresampler_2up:1;
        RBus_UInt32  hresampler_app_sel:1;
        RBus_UInt32  hresampler_app_alpha_sel:1;
        RBus_UInt32  res1:29;
    };
}CHROMA_HRESAMPLER_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_kp_coef_0:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  hpll_manu_mode_en:1;
        RBus_UInt32  res1:24;
    };
}HPLL_KP_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_kp_coef_1:6;
        RBus_UInt32  res1:26;
    };
}HPLL_KP_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_kp_coef_2:6;
        RBus_UInt32  res1:26;
    };
}HPLL_KP_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_kp_coef_3:6;
        RBus_UInt32  res1:26;
    };
}HPLL_KP_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_kp_coef_4:6;
        RBus_UInt32  res1:26;
    };
}HPLL_KP_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_kp_coef_5:6;
        RBus_UInt32  res1:26;
    };
}HPLL_KP_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_ki_coef_0:8;
        RBus_UInt32  res1:24;
    };
}HPLL_KI_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_ki_coef_1:8;
        RBus_UInt32  res1:24;
    };
}HPLL_KI_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_ki_coef_2:8;
        RBus_UInt32  res1:24;
    };
}HPLL_KI_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_ki_coef_3:8;
        RBus_UInt32  res1:24;
    };
}HPLL_KI_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_ki_coef_4:8;
        RBus_UInt32  res1:24;
    };
}HPLL_KI_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hpll_ki_coef_5:8;
        RBus_UInt32  res1:24;
    };
}HPLL_KI_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_pll_en:1;
        RBus_UInt32  second_pll_w_hlock:1;
        RBus_UInt32  second_pll_phase_sel:1;
        RBus_UInt32  second_pll_clampgate_sel:1;
        RBus_UInt32  second_pll_gain_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  second_pll_level_sel:2;
        RBus_UInt32  res1:22;
    };
}Second_pll_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_pll_dc_rm:12;
        RBus_UInt32  second_pll_dc_add:12;
        RBus_UInt32  second_pll_sync_level:8;
    };
}Second_pll_gain1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_comp_slevel:12;
        RBus_UInt32  second_comp_blevel:12;
        RBus_UInt32  res1:8;
    };
}Second_pll_gain2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_dgain:12;
        RBus_UInt32  second_trailing:8;
        RBus_UInt32  res1:12;
    };
}Second_pll_gain3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_hsync_tip_end:8;
        RBus_UInt32  second_hsync_tip_start:8;
        RBus_UInt32  second_backporch_end:8;
        RBus_UInt32  second_backporch_start:8;
    };
}Second_pll_gain4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  under_min_err_thl:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  under_line_err_thl:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  under_count_reset:1;
        RBus_UInt32  under_detected_flag:1;
        RBus_UInt32  second_pll_kill_en:1;
        RBus_UInt32  headswitch_debounce_en:1;
        RBus_UInt32  res1:4;
    };
}under_new_th1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  under_field_err_thl:10;
        RBus_UInt32  res1:22;
    };
}under_new_th2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  under_debounce_max:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  under_debounce_thl:10;
        RBus_UInt32  res1:10;
    };
}under_new_th3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coch_avg_line1_diff_thre_lo:12;
        RBus_UInt32  coch_avg_line1_diff_thre_up:12;
        RBus_UInt32  res1:7;
        RBus_UInt32  coch_detected_by_check_dc:1;
    };
}DC_COCH_SEPERATE_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coch_detect_counter_lo_thre:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  coch_detect_counter_up_thre:10;
        RBus_UInt32  res1:9;
        RBus_UInt32  coch_detect_lpf_reset:1;
    };
}DC_COCH_SEPERATE_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_rising:8;
        RBus_UInt32  res1:24;
    };
}HSYNC_RISING_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_phase_offset:8;
        RBus_UInt32  res1:24;
    };
}HSYNC_PHASE_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_gate_start:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  secam_gp_hcount_start:10;
        RBus_UInt32  res1:10;
    };
}HSYNC_GATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_gate_end:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  secam_gp_hcount_end:10;
        RBus_UInt32  res1:10;
    };
}HSYNC_GATE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_tip_start:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  secam_gp_vcount_start_o:10;
        RBus_UInt32  res1:10;
    };
}HSYNC_TIP_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_tip_end:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  secam_gp_vcount_end_o:10;
        RBus_UInt32  res1:10;
    };
}HSYNC_TIP_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_rising_start:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  secam_gp_vcount_start_e:10;
        RBus_UInt32  res1:10;
    };
}HSYNC_RISING_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hsync_rising_end:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  secam_gp_vcount_end_e:10;
        RBus_UInt32  res1:10;
    };
}HSYNC_RISING_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  backporch_start:8;
        RBus_UInt32  res1:24;
    };
}BACKPROCH_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  backporch_end:8;
        RBus_UInt32  res1:24;
    };
}BACKPORCH_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hblank_start:8;
        RBus_UInt32  res1:24;
    };
}HBLANK_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hblank_end:8;
        RBus_UInt32  res1:24;
    };
}HBLANK_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_gate_start:8;
        RBus_UInt32  res1:24;
    };
}BURST_GATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_gate_end:8;
        RBus_UInt32  res1:24;
    };
}BURST_GATE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hactive_start:8;
        RBus_UInt32  res1:24;
    };
}HACTIVE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hactive_width:8;
        RBus_UInt32  res1:24;
    };
}HACTIVE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_hstate_4_phase_max:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  hdetect_hstate_3_phase_max:13;
        RBus_UInt32  res1:2;
        RBus_UInt32  hdetect_hstate_phase_max_en:1;
    };
}HDETECT_ERR_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_err00_th:8;
        RBus_UInt32  hdetect_err04_th:8;
        RBus_UInt32  hdetect_hstate_5_phase_max:13;
        RBus_UInt32  res1:3;
    };
}HDETECT_ERR_TH2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cstate_status:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  cstate_cntl:2;
        RBus_UInt32  new_cstate:1;
        RBus_UInt32  new_c_state_i:1;
        RBus_UInt32  cpll_use_fine_or_final_hlock:1;
        RBus_UInt32  res1:23;
    };
}CSTATE_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gate_iir_v_sel:1;
        RBus_UInt32  gate_iir_h_sel:1;
        RBus_UInt32  new_hpll_lpf_sel:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  coef_syncmidpt_fir_in:8;
        RBus_UInt32  level_fir_num_32_64_slevel:1;
        RBus_UInt32  level_fir_num_32_64_blevel:1;
        RBus_UInt32  s_b_level_fir_en:1;
        RBus_UInt32  res1:13;
    };
}HDETECT_GATE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gate_iir_coef1:8;
        RBus_UInt32  hsync_refind:1;
        RBus_UInt32  hsync_refind_mask_err:1;
        RBus_UInt32  headswitch_err_sel:2;
        RBus_UInt32  res1:20;
    };
}HDETECT_GATE_COEF1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gate_iir_coef2:8;
        RBus_UInt32  hdetect_err07_th:8;
        RBus_UInt32  res1:16;
    };
}HDETECT_GATE_COEF2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vphase_status:8;
        RBus_UInt32  hstate_err_counter:2;
        RBus_UInt32  res2:6;
        RBus_UInt32  hstate_err_thl:14;
        RBus_UInt32  res1:2;
    };
}HDETECT_VPHASE_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vphasediff_status:8;
        RBus_UInt32  hdetect_err01_th:8;
        RBus_UInt32  hdetect_err10_th:8;
        RBus_UInt32  hdetect_err05_th:8;
    };
}HDETECT_VPHASEDIFF_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  noise_vbi_thresh:8;
        RBus_UInt32  res1:24;
    };
}NOISE_VBI_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coch_detected_frame:6;
        RBus_UInt32  res2:1;
        RBus_UInt32  coch_detected_status:1;
        RBus_UInt32  res1:24;
    };
}VBI_CO_CH_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coch_bp_diff_th:4;
        RBus_UInt32  res1:28;
    };
}VBI_CO_CH_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  coch_line_count_th:8;
        RBus_UInt32  res1:24;
    };
}VBI_CO_CH_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mv_window2_value:8;
        RBus_UInt32  res1:24;
    };
}MV_DETECT_WINDOW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad_burst_gate_start:8;
        RBus_UInt32  res1:24;
    };
}MV_BURSTGATE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad_burst_gate_end:8;
        RBus_UInt32  res1:24;
    };
}MV_BURSTGATE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cinverse_detect_control:3;
        RBus_UInt32  res1:29;
    };
}COLOR_INVERSE_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_err_constraint_low_th:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  h_err_constraint_high_th:14;
        RBus_UInt32  res1:1;
        RBus_UInt32  h_err_constraint_en:1;
    };
}H_ERR_CONSTRAINT_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  h_err_constraint_val:13;
        RBus_UInt32  h_err_constraint_hstate:3;
        RBus_UInt32  res1:16;
    };
}H_ERR_CONSTRAINT_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_save_stable_hdto_start:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  hdetect_restore_vcr_enable:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  hdetect_set_hdto_start:10;
        RBus_UInt32  hdetect_force_hdto_en:1;
        RBus_UInt32  hdetect_restore_hdto_status:1;
        RBus_UInt32  hdetect_set_new_hdto_n:3;
        RBus_UInt32  hdetect_restore_hdto_en:1;
    };
}H_RESTORE_HDTO_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdetect_set_hdto_phase_err_th:14;
        RBus_UInt32  res1:18;
    };
}H_RESTORE_HDTO_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wrong_if_pc_detect:1;
        RBus_UInt32  res2:7;
        RBus_UInt32  sync_level_manu_en:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  sync_level_manu:8;
        RBus_UInt32  wrong_if_pc_detect_th:8;
    };
}IF_WRONG_PC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cpll_phase_thr_dn:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  cpll_phase_thr_up:14;
        RBus_UInt32  res1:2;
    };
}CPLL_STABILITY_OBSERVE_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cpll_stable_flag:1;
        RBus_UInt32  cpll_phase_small_flag:1;
        RBus_UInt32  cpll_ampl_neg_flag:1;
        RBus_UInt32  res3:13;
        RBus_UInt32  cerror_continune_same_sign_thr:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  cpll_ampl_thr:7;
        RBus_UInt32  res1:1;
    };
}CPLL_STABILITY_OBSERVE_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  phase_out_line_iir:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  ampl_out_line_iir:14;
        RBus_UInt32  res1:2;
    };
}CPLL_STABILITY_OBSERVE_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  herror_neg_pos_value_total_thr:4;
        RBus_UInt32  herror_neg_pos_num_total_thr:4;
        RBus_UInt32  herror_continune_same_sign_thr:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  herror_pos_neg_value_diff_thr:16;
    };
}HPLL_STABILITY_OBSERVE_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  herror_pos_value:16;
        RBus_UInt32  herror_neg_value:16;
    };
}HPLL_STABILITY_OBSERVE_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  herror_stable_state_hold_en:1;
        RBus_UInt32  herror_pos_neg_value_even:1;
        RBus_UInt32  herror_pos_neg_num_even:1;
        RBus_UInt32  res3:5;
        RBus_UInt32  herror_neg_pos_num_win_thr:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  herror_neg_pos_err_th:13;
        RBus_UInt32  res1:3;
    };
}HPLL_STABILITY_OBSERVE_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec1_start:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  statistic_h_phase_diff_sec1_end:9;
        RBus_UInt32  res1:7;
    };
}H_PHASE_DIFF_STATISTICS_SET_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec2_start:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  statistic_h_phase_diff_sec2_end:9;
        RBus_UInt32  res1:7;
    };
}H_PHASE_DIFF_STATISTICS_SET_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_hitso_level1:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  statistic_h_phase_diff_hitso_level2:13;
        RBus_UInt32  res1:3;
    };
}H_PHASE_DIFF_STATISTICS_SET_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_hitso_level3:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  statistic_h_phase_diff_hitso_level4:13;
        RBus_UInt32  res1:3;
    };
}H_PHASE_DIFF_STATISTICS_SET_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_hitso_level5:13;
        RBus_UInt32  res1:19;
    };
}H_PHASE_DIFF_STATISTICS_SET_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_0:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_1:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_2:10;
        RBus_UInt32  res1:1;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_ready:1;
    };
}H_PHASE_DIFF_SEC1_HISTOGRAM_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_3:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_4:10;
        RBus_UInt32  statistic_h_phase_diff_sec1_histo_5:10;
        RBus_UInt32  res1:2;
    };
}H_PHASE_DIFF_SEC1_HISTOGRAM_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_0:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_1:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_2:10;
        RBus_UInt32  res1:1;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_ready:1;
    };
}H_PHASE_DIFF_SEC2_HISTOGRAM_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_3:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_4:10;
        RBus_UInt32  statistic_h_phase_diff_sec2_histo_5:10;
        RBus_UInt32  res1:2;
    };
}H_PHASE_DIFF_SEC2_HISTOGRAM_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_line_num:6;
        RBus_UInt32  res1:10;
        RBus_UInt32  statistic_data_level_diff_th:14;
        RBus_UInt32  data_level_diff_iir_en:1;
        RBus_UInt32  iir_up_speed_on:1;
    };
}DATA_LEVEL_STATISTICS_SET_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec1_max:12;
        RBus_UInt32  statistic_data_level_sec1_min:12;
        RBus_UInt32  res1:7;
        RBus_UInt32  statistic_data_level_ready:1;
    };
}DATA_LEVEL_STATISTICS_SEC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec2_max:12;
        RBus_UInt32  statistic_data_level_sec2_min:12;
        RBus_UInt32  res1:8;
    };
}DATA_LEVEL_STATISTICS_SEC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec3_max:12;
        RBus_UInt32  statistic_data_level_sec3_min:12;
        RBus_UInt32  res1:8;
    };
}DATA_LEVEL_STATISTICS_SEC3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec4_max:12;
        RBus_UInt32  statistic_data_level_sec4_min:12;
        RBus_UInt32  res1:8;
    };
}DATA_LEVEL_STATISTICS_SEC4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec5_max:12;
        RBus_UInt32  statistic_data_level_sec5_min:12;
        RBus_UInt32  res1:8;
    };
}DATA_LEVEL_STATISTICS_SEC5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec6_max:12;
        RBus_UInt32  statistic_data_level_sec6_min:12;
        RBus_UInt32  res1:8;
    };
}DATA_LEVEL_STATISTICS_SEC6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec7_max:12;
        RBus_UInt32  statistic_data_level_sec7_min:12;
        RBus_UInt32  res1:8;
    };
}DATA_LEVEL_STATISTICS_SEC7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_data_level_sec8_max:12;
        RBus_UInt32  statistic_data_level_sec8_min:12;
        RBus_UInt32  res1:8;
    };
}DATA_LEVEL_STATISTICS_SEC8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_threshold:6;
        RBus_UInt32  vsync_cntl:2;
        RBus_UInt32  res1:24;
    };
}VSYNC_CNTL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop_tc3:2;
        RBus_UInt32  field_detect_mode:2;
        RBus_UInt32  vodd_delayed:1;
        RBus_UInt32  veven_delayed:1;
        RBus_UInt32  flip_field:1;
        RBus_UInt32  field_polarity:1;
        RBus_UInt32  res1:24;
    };
}VSYNC_TIME_CONST_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop_tc2:7;
        RBus_UInt32  res1:25;
    };
}VSYNC_TIME_CONST2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop_tc1:8;
        RBus_UInt32  res1:24;
    };
}VSYNC_TIME_CONST1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  serration_threshold:8;
        RBus_UInt32  res1:24;
    };
}SERRATION_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  no_signal_dec:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  vsync_delay_2d:4;
        RBus_UInt32  vsync_delay_1d:4;
        RBus_UInt32  vsync_delay_en:1;
        RBus_UInt32  vsync_delay_sel:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  hlock_field_cnt:4;
        RBus_UInt32  vlock_field_cnt:4;
        RBus_UInt32  hvlock_field_cnt:4;
    };
}NO_SIGNAL_DEC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vactive_start:8;
        RBus_UInt32  res1:24;
    };
}VACTIVE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vactive_height:8;
        RBus_UInt32  res1:24;
    };
}VACTIVE_HEIGHT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_h_min:7;
        RBus_UInt32  res1:25;
    };
}VSYNC_H_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_h_max:7;
        RBus_UInt32  res1:25;
    };
}VSYNC_H_MAX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_vbi_min:7;
        RBus_UInt32  res1:25;
    };
}VSYNC_VBI_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_vbi_max:7;
        RBus_UInt32  vlock_wide_range:1;
        RBus_UInt32  res1:24;
    };
}VSYNC_VBI_LOCKOUT_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  syncmidpt_add_level:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  vsync_625_midpt_en:1;
        RBus_UInt32  midpt_rough_vdetect_en:1;
        RBus_UInt32  midpt_625_dc_th_en:1;
        RBus_UInt32  syncmidpt_dc_rough:1;
        RBus_UInt32  vsync_ser_num_max_def:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  vsync_ser_num_bigger_10_en:1;
        RBus_UInt32  res1:15;
    };
}MIDPT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  syncmidpt_fix_add_value:8;
        RBus_UInt32  res1:24;
    };
}MIDPT_FIX_ADD_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  midpt_625_dc_th:8;
        RBus_UInt32  res1:24;
    };
}MIDPT_625_DC_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sync_dc_offset_th:12;
        RBus_UInt32  res1:20;
    };
}SYNC_DC_OFFSET_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sync_midpt_625:12;
        RBus_UInt32  res1:20;
    };
}SYNC_DC_OFFSET_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sync_midpt_h:12;
        RBus_UInt32  res1:20;
    };
}SYNC_MIDPT_H_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sync_midpt_v:12;
        RBus_UInt32  res1:20;
    };
}SYNC_MIDPT_V_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_line_length_en:1;
        RBus_UInt32  adc_lpf_sel:3;
        RBus_UInt32  res4:2;
        RBus_UInt32  vdetect_pattern_sel:2;
        RBus_UInt32  vlock_sel:1;
        RBus_UInt32  hpll_no_signal_sel:1;
        RBus_UInt32  no_signal_to_0_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  no_signal_hpll_out:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  raw_vdetect_max_sel:2;
        RBus_UInt32  res1:14;
    };
}SYNC_MIDPT_V2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_lpf_coef2:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef1:10;
        RBus_UInt32  res1:6;
    };
}ADC_27_LPF_COEF_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_lpf_coef4:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef3:10;
        RBus_UInt32  res1:6;
    };
}ADC_27_LPF_COEF_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_lpf_coef6:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef5:10;
        RBus_UInt32  res1:6;
    };
}ADC_27_LPF_COEF_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_lpf_coef8:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef7:10;
        RBus_UInt32  res1:6;
    };
}ADC_27_LPF_COEF_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_lpf_coefa:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coef9:10;
        RBus_UInt32  res1:6;
    };
}ADC_27_LPF_COEF_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_lpf_coefc:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  adc_lpf_coefb:10;
        RBus_UInt32  res1:6;
    };
}ADC_27_LPF_COEF_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_line_length:8;
        RBus_UInt32  res1:24;
    };
}VDETECT_LINE_LENGHT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_window_manu_en:1;
        RBus_UInt32  new_vdetect_window_en:1;
        RBus_UInt32  no_vsync_flag_en:1;
        RBus_UInt32  new_vdetect_force_en:1;
        RBus_UInt32  res1:28;
    };
}VDETECT_WINDOW_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_window:12;
        RBus_UInt32  res1:20;
    };
}VDETECT_WINDOW_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vsync_offset_manul:3;
        RBus_UInt32  new_vsync_offset_manul_mode_en:1;
        RBus_UInt32  new_vdetect_vcount_window_en:1;
        RBus_UInt32  vloss_detect_en:1;
        RBus_UInt32  gate_sel:1;
        RBus_UInt32  new_vdetect_en:1;
        RBus_UInt32  new_vdetect_coch_en:1;
        RBus_UInt32  new_vdetect_max_limit_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  new_vdetect_max_limit_value:12;
        RBus_UInt32  res1:8;
    };
}NEW_VDETECT_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:2;
        RBus_UInt32  vsync_fine_window_state1_en:1;
        RBus_UInt32  force_new_vdetect_fine_window:1;
        RBus_UInt32  new_vloss_flag:1;
        RBus_UInt32  no_vsync_flag:1;
        RBus_UInt32  new_vdetect_feature_th_manul_en:1;
        RBus_UInt32  old_hdetect_lpf_en:1;
        RBus_UInt32  res1:24;
    };
}NEW_VDETECT_LOOP_TH2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_loop_core_th:10;
        RBus_UInt32  res1:22;
    };
}NEW_VDETECT_LOOP_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_diff_offset:12;
        RBus_UInt32  res1:20;
    };
}NEW_VDETECT_DIFF_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_fine_start:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  new_vdetect_loss_max:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  vsync_fine_start1:10;
        RBus_UInt32  res1:2;
    };
}VSYNC_FINE_START_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vsync_fine_end:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  new_vdetect_loss_up:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  vsync_fine_end1:10;
        RBus_UInt32  res1:2;
    };
}VSYNC_FINE_END_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  no_vsync_th_lo:4;
        RBus_UInt32  no_vsync_th_hi:4;
        RBus_UInt32  res1:24;
    };
}NO_VSYNC_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_fine_vphase_th:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  new_vdetect_loss_dn:6;
        RBus_UInt32  res1:14;
    };
}NEW_VDETECT_VPHASE_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_feature_th1:8;
        RBus_UInt32  res1:24;
    };
}NEW_VDETECT_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_feature_th2:8;
        RBus_UInt32  res1:24;
    };
}NEW_VDETECT_TH2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_feature_th3:8;
        RBus_UInt32  res1:24;
    };
}NEW_VDETECT_TH3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_vdetect_feature_th4:8;
        RBus_UInt32  new_vdetect_feature_th5:8;
        RBus_UInt32  new_vdetect_feature_th6:8;
        RBus_UInt32  new_vdetect_feature_th7:8;
    };
}NEW_VDETECT_TH4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vstate_2to3_er:4;
        RBus_UInt32  res4:4;
        RBus_UInt32  vsync_refind:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  vsync_refind_con_sel:2;
        RBus_UInt32  vstate_reset:2;
        RBus_UInt32  vsync_stable_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  vstate0_counter_num:8;
        RBus_UInt32  vstate0_direct_vsync:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  vpll_kp_ki_div4:1;
    };
}VSTATE_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vstate_back1_er:4;
        RBus_UInt32  vstate_1to2_er:4;
        RBus_UInt32  hsync_refind_max:7;
        RBus_UInt32  vstate1_err_sel:1;
        RBus_UInt32  hsync_refind_min:7;
        RBus_UInt32  vstate_new2to3_en:1;
        RBus_UInt32  vstate_2to3_th:8;
    };
}VSTATE_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vstate_counter_num:8;
        RBus_UInt32  hsync_reset_for_data:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  hsync_reset_for_vsync:10;
        RBus_UInt32  res1:2;
    };
}VSTATE_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vcr_back_en:1;
        RBus_UInt32  vstate_sw:2;
        RBus_UInt32  vstate_sw_en:1;
        RBus_UInt32  vstate_status:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  vsync_vertical_sum_num:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  vstate3_err_adjust_th:4;
        RBus_UInt32  vstate3_err_adjust_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  vphase_error_window:8;
    };
}VSTATE_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop0_tc1:8;
        RBus_UInt32  res1:24;
    };
}VLOOP0_TC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop0_tc2:7;
        RBus_UInt32  res1:25;
    };
}VLOOP0_TC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop2_tc1:8;
        RBus_UInt32  res1:24;
    };
}VLOOP2_TC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop2_tc2:7;
        RBus_UInt32  res1:25;
    };
}VLOOP2_TC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop3_tc1:8;
        RBus_UInt32  res1:24;
    };
}VLOOP3_TC1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop3_tc2:7;
        RBus_UInt32  res1:25;
    };
}VLOOP3_TC2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vloop3_tc3:2;
        RBus_UInt32  vloop2_tc3:2;
        RBus_UInt32  vloop0_tc3:2;
        RBus_UInt32  res1:26;
    };
}VLOOP_TC3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vlock_count:3;
        RBus_UInt32  new_vdetect_lock_en:1;
        RBus_UInt32  flag_cgain_too_big_kill:1;
        RBus_UInt32  flag_user_kill:1;
        RBus_UInt32  flag_chrmaunlock_kill:1;
        RBus_UInt32  res1:25;
    };
}VLOCK_COUNT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vlock_window:8;
        RBus_UInt32  vsync_detect_core_thl:11;
        RBus_UInt32  res3:1;
        RBus_UInt32  vsync_detect_count_thl:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  vsync_detect_crlock_en:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  vsync_detect_rst:1;
    };
}VLOCK_WINDOW_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vlock_phase_plus:8;
        RBus_UInt32  res1:24;
    };
}VLOCK_PHASE_PLUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vline_adj_cnt_a:8;
        RBus_UInt32  res1:24;
    };
}VLINE_ADJ_CNT_A_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vline_adj_cnt_b:8;
        RBus_UInt32  res1:24;
    };
}VLINE_ADJ_CNT_B_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  table_hactive_width:8;
        RBus_UInt32  res1:24;
    };
}TABLE_HACTIVE_WIDTH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vlines_freerun:10;
        RBus_UInt32  res3:2;
        RBus_UInt32  vlines_diff_flag:1;
        RBus_UInt32  vlines_the_same_flag:1;
        RBus_UInt32  vsync_freerun_when_unstable_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  vlines_the_same_cnt_thr:4;
        RBus_UInt32  res1:12;
    };
}VSYNC_PLL_FREERUN_MUX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cagc:8;
        RBus_UInt32  cagc_data_input_sel:2;
        RBus_UInt32  cagc_pll_input_sel:2;
        RBus_UInt32  res2:16;
        RBus_UInt32  fix_cgain:1;
        RBus_UInt32  res1:3;
    };
}CHROMA_AGC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_kill:4;
        RBus_UInt32  hlock_ckill:1;
        RBus_UInt32  vbi_ckill:1;
        RBus_UInt32  user_ckill_mode:2;
        RBus_UInt32  ckill_sel:1;
        RBus_UInt32  res1:23;
    };
}CHROMA_KILL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lose_chromalock_ckill:1;
        RBus_UInt32  lose_chromalock_level:3;
        RBus_UInt32  lose_chromalock_count:4;
        RBus_UInt32  chromalock_input_acc_num:2;
        RBus_UInt32  chromalock_input_acc_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  lose_acc_chromalock_level:3;
        RBus_UInt32  res1:17;
    };
}CHROMA_LOCK_CONFIG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cagc_igain:2;
        RBus_UInt32  flag358_cresample_lpf_sel:2;
        RBus_UInt32  res2:3;
        RBus_UInt32  cnew_gate_en:1;
        RBus_UInt32  res1:24;
    };
}CHROMA_LOOPFILTER_GAIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fixed_cstate:1;
        RBus_UInt32  cstate:3;
        RBus_UInt32  cresample_lpf_sel:2;
        RBus_UInt32  secam_cresample_lpf_sel:2;
        RBus_UInt32  cloop_freq_offset_limit:12;
        RBus_UInt32  cloop_freq_offset_limit_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  cresample_signed_en:1;
        RBus_UInt32  res1:7;
    };
}CHROMA_LOOPFILTER_STATE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cautopos:5;
        RBus_UInt32  fixed_burstgate:1;
        RBus_UInt32  chroma_burst5or10:1;
        RBus_UInt32  res1:25;
    };
}CHROMA_AUTOPOS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ckill_lb_sel:1;
        RBus_UInt32  ckill_vsync_delay_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  chromalock_cstate:3;
        RBus_UInt32  chromalock_cstate_en:1;
        RBus_UInt32  res1:24;
    };
}CKILL_LB_SEL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ckill_level_user_mode_value:14;
        RBus_UInt32  res2:1;
        RBus_UInt32  ckill_level_user_mode_en:1;
        RBus_UInt32  ckill_level_user_offset:14;
        RBus_UInt32  res1:1;
        RBus_UInt32  ckill_level_user_offset_en:1;
    };
}CKILL_GAIN_KILL_THL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  badedit_line_num:3;
        RBus_UInt32  bad_phase_detect:1;
        RBus_UInt32  badedit_pulse_detect:1;
        RBus_UInt32  badedit_phase_lock_en:1;
        RBus_UInt32  phase_fast_lock_en:1;
        RBus_UInt32  fast_lock_en:1;
        RBus_UInt32  badedit_out_noise_thr:8;
        RBus_UInt32  badedit_in_noise_thr:8;
        RBus_UInt32  badedit_noisy_off_en:1;
        RBus_UInt32  res1:7;
    };
}CSTATE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  badedit_th:8;
        RBus_UInt32  res1:24;
    };
}BADEDIT_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  badphase_th:8;
        RBus_UInt32  res1:24;
    };
}BADPHASE_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cstate_line_num:8;
        RBus_UInt32  res1:24;
    };
}CSTATE_LINE_NUM_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_agc_peak_cnt:6;
        RBus_UInt32  chroma_peak_en:1;
        RBus_UInt32  new_cgain_level_en:1;
        RBus_UInt32  chroma_peak_en_pll:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  cpeak_noise_thr1:8;
        RBus_UInt32  cpeak_noise_thr2:8;
        RBus_UInt32  cpeak_noisy_act_en:1;
        RBus_UInt32  cpeak_noisy_act_en_pll:1;
        RBus_UInt32  res1:2;
    };
}CHROMA_AGC_PEAK_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  chroma_agc_peak_nominal:8;
        RBus_UInt32  res1:24;
    };
}CHROMA_AGC_PEAK_NOMINAL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cagc_upper:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  cagc_upper_xroot2_en:1;
        RBus_UInt32  close_ckill_loopfilter:1;
        RBus_UInt32  res1:14;
    };
}CLOSE_CKILL_LOOPFILTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cagc_peak_err_diff_sel:6;
        RBus_UInt32  cagc_burst_err_adj_en:1;
        RBus_UInt32  cagc_peak_err_adj_en:1;
        RBus_UInt32  res1:24;
    };
}CAGC_PEAK_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cagc_burst_err_diff_sel:6;
        RBus_UInt32  res1:26;
    };
}CAGC_PEAK_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cagc_peak_luma_ratio:6;
        RBus_UInt32  res1:26;
    };
}CAGC_PEAK_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cr_delay:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  cb_delay:3;
        RBus_UInt32  res1:25;
    };
}CHROMA_DELAY_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_cgain_x4_en:1;
        RBus_UInt32  flag_burst_x4:1;
        RBus_UInt32  res1:30;
    };
}BURST_CGAIN_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_cgain_mag_th:8;
        RBus_UInt32  res1:24;
    };
}BURST_CGAIN_MAG_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag358_cdto_inc:30;
        RBus_UInt32  flag358_iir_cunlock_en:1;
        RBus_UInt32  flag358_iir_en:1;
    };
}FLAG358_CDTO_INC4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_coef_sel:1;
        RBus_UInt32  auto_burst_location_en:1;
        RBus_UInt32  burst_location_rst_en:1;
        RBus_UInt32  burst_location_lpf_reset:1;
        RBus_UInt32  burst_location_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  burst_location_fix:11;
        RBus_UInt32  res1:1;
        RBus_UInt32  burst_location_center_modify_en:1;
        RBus_UInt32  burst_location_center_modify_sel:3;
        RBus_UInt32  burst_location_sel_modify_en:1;
        RBus_UInt32  burst_location_sel_modify_sel:3;
        RBus_UInt32  normal_burst_locationreg_en:1;
        RBus_UInt32  burst_location_selreg_en:1;
        RBus_UInt32  burst_location_sel_clock:1;
        RBus_UInt32  burst_location_fix_en:1;
    };
}SEPARATE_443_358_NEW_FUNCTION_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  normal_burst_location:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  burst_location_result:11;
        RBus_UInt32  res1:5;
    };
}SEPARATE_443_358_NEW_FUNCTION_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wide_burst_location_start:11;
        RBus_UInt32  res3:1;
        RBus_UInt32  wide_burst_location_startreg_en:1;
        RBus_UInt32  wide_burst_location_endreg_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  wide_burst_location_end:11;
        RBus_UInt32  res1:1;
        RBus_UInt32  wide_burst_location_modify_en:1;
        RBus_UInt32  wide_burst_location_modify_sel:3;
    };
}SEPARATE_443_358_NEW_FUNCTION_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  normal_burst_location_status:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  burst_location_sel_status:2;
        RBus_UInt32  res1:18;
    };
}BURST_LOCATION_STATUS_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wide_burst_location_start_status:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  wide_burst_location_end_status:11;
        RBus_UInt32  res1:5;
    };
}BURST_LOCATION_STATUS_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_hsync_end:11;
        RBus_UInt32  res2:5;
        RBus_UInt32  sep_hsync_start:11;
        RBus_UInt32  res1:5;
    };
}BURST_LOCATION_HSYNC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_location_auto_thr:8;
        RBus_UInt32  burst_location_magnitude_thr:8;
        RBus_UInt32  burst_location_enable_mode:8;
        RBus_UInt32  res2:4;
        RBus_UInt32  burst_location_auto_en:1;
        RBus_UInt32  res1:3;
    };
}BURST_LOCATION_FW_CNTL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_path_coef_value:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  y_path_coef_num:7;
        RBus_UInt32  res1:12;
        RBus_UInt32  y_path_eq_en:1;
    };
}Y_PATH_EQ_FILTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y_path_coef_value_r:11;
        RBus_UInt32  res2:1;
        RBus_UInt32  y_path_coef_num_r:7;
        RBus_UInt32  res1:13;
    };
}Y_PATH_EQ_FILTER_R_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  palm_atone_counter:6;
        RBus_UInt32  flag625_vsync_l_th:1;
        RBus_UInt32  flag625_vsync_l_sel:1;
        RBus_UInt32  res1:24;
    };
}PALM_FLAG_COMPENSATION1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  palm_atone_threshold:8;
        RBus_UInt32  res1:24;
    };
}PALM_FLAG_COMPENSATION2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  manual_mode_select:3;
        RBus_UInt32  state_machine_reset:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  auto_burst_switch_625only:1;
        RBus_UInt32  auto_625only_en:1;
        RBus_UInt32  auto_mode_en:1;
        RBus_UInt32  colour_mode_dark_set:3;
        RBus_UInt32  colour_mode_dark_check:1;
        RBus_UInt32  res1:20;
    };
}MANUAL_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  decision_mode_status:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  set_mode_status:3;
        RBus_UInt32  res1:25;
    };
}MODE_DETECTION_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_number:6;
        RBus_UInt32  disable_mode:1;
        RBus_UInt32  disable_mode_en:1;
        RBus_UInt32  res1:24;
    };
}STATISTIC_AND_DISABLE_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  prefer_ntsc_palm_en:1;
        RBus_UInt32  prefer_secam_pali_en:1;
        RBus_UInt32  prefer_ntsc443_pal60_en:1;
        RBus_UInt32  prefer_ntsc50_paln_en:1;
        RBus_UInt32  prefer_ntsc_palm:1;
        RBus_UInt32  prefer_secam_pali:1;
        RBus_UInt32  prefer_ntsc443_pal60:1;
        RBus_UInt32  prefer_ntsc50_paln:1;
        RBus_UInt32  res1:24;
    };
}PREFER_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fix_secam_h:1;
        RBus_UInt32  fix_palor_h:1;
        RBus_UInt32  fix_443_h:1;
        RBus_UInt32  fix_625_h:1;
        RBus_UInt32  fix_secamflag_en:1;
        RBus_UInt32  fix_palorflag_en:1;
        RBus_UInt32  fix_443flag_en:1;
        RBus_UInt32  fix_625flag_en:1;
        RBus_UInt32  res1:24;
    };
}STATE_MACHINE_FIX_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ped_reg_en:1;
        RBus_UInt32  vsyncreg_en:1;
        RBus_UInt32  cdtomem_reg_en:1;
        RBus_UInt32  vline625reg_en:1;
        RBus_UInt32  hagcreg_en:1;
        RBus_UInt32  colourmodereg_en:1;
        RBus_UInt32  hpixelreg_en:1;
        RBus_UInt32  hactivestartreg_en:1;
        RBus_UInt32  res1:24;
    };
}VD_BASIC_REGISTER_ENABLE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  statistic_multiplier:3;
        RBus_UInt32  secam_flag_freq_disable:1;
        RBus_UInt32  auto_secam_pali_method:2;
        RBus_UInt32  switch_palo_palm_method:2;
        RBus_UInt32  res1:24;
    };
}AUTO_MODE_S_M_STATISTIC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  y1delay:6;
        RBus_UInt32  res5:2;
        RBus_UInt32  cb1delay:6;
        RBus_UInt32  res4:2;
        RBus_UInt32  cr1delay:6;
        RBus_UInt32  res3:2;
        RBus_UInt32  y1delayreg_en:1;
        RBus_UInt32  cb1delayreg_en:1;
        RBus_UInt32  cr1delayreg_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  new_y1delay_en:1;
        RBus_UInt32  new_cb1delay_en:1;
        RBus_UInt32  new_cr1delay_en:1;
        RBus_UInt32  res1:1;
    };
}AUTO_POS_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ckill_y1delay:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  ckill_cb1delay:6;
        RBus_UInt32  ckill_cr1delay:6;
        RBus_UInt32  ckill_y1delayreg_en:1;
        RBus_UInt32  ckill_cb1delayreg_en:1;
        RBus_UInt32  ckill_cr1delayreg_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  auto_ycdelay_mode_sel:3;
        RBus_UInt32  auto_ycdelay_modify_en:1;
        RBus_UInt32  auto_pos_mode_sel:3;
        RBus_UInt32  auto_pos_modify_en:1;
    };
}AUTO_POS_CTRL_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_sel_no_burst_625:2;
        RBus_UInt32  auto_443_358_method_525:2;
        RBus_UInt32  auto_443_358_method_625:2;
        RBus_UInt32  fix_358_h:1;
        RBus_UInt32  fix_358flag_en:1;
        RBus_UInt32  res1:24;
    };
}FLAG358_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  no_burst_mag_th:8;
        RBus_UInt32  res1:24;
    };
}NO_BURST_MAG_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  no_burst_mag_filter_th:8;
        RBus_UInt32  res1:24;
    };
}NO_BURST_MAG_FILTER_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  no_burst_443_en:1;
        RBus_UInt32  burst_win_error:1;
        RBus_UInt32  paln_flag_new:1;
        RBus_UInt32  no_burst_flag:1;
        RBus_UInt32  burst_mag_trig_offset:4;
        RBus_UInt32  res1:24;
    };
}NO_BURST_443_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag358_phase_diff_hcount:7;
        RBus_UInt32  flag358_secam_phase_diff_hcount_en:1;
        RBus_UInt32  res1:24;
    };
}FLAG358_SECAM_HCOUNT_RESET_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag358_secam_phase_diff_dr:8;
        RBus_UInt32  res1:24;
    };
}FLAG358_SECAM_PHASE_DIFF_DR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag358_secam_phase_diff_db:8;
        RBus_UInt32  res1:24;
    };
}FLAG358_SECAM_PHASE_DIFF_DB_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_mag_th_358:8;
        RBus_UInt32  res1:24;
    };
}BURST_MAG_TH_358_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  table_colour_mode:3;
        RBus_UInt32  table_ped:1;
        RBus_UInt32  table_hpixel:2;
        RBus_UInt32  table_vline_625:1;
        RBus_UInt32  table_cagc_en:1;
        RBus_UInt32  res1:24;
    };
}AUTO_MODE_TABLE1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  table_hagc:8;
        RBus_UInt32  res1:24;
    };
}AUTO_MODE_TABLE2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  table_hactive_start:8;
        RBus_UInt32  res1:24;
    };
}AUTO_MODE_TABLE3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  table_vactive_start:8;
        RBus_UInt32  res1:24;
    };
}AUTO_MODE_TABLE4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  table_vactive_height:8;
        RBus_UInt32  res1:24;
    };
}AUTO_MODE_TABLE5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  table_cdto:30;
        RBus_UInt32  res1:2;
    };
}AUTO_MODE_TABLE6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag_625_counter:8;
        RBus_UInt32  new_625flag_div_thr:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  new_625flag_window:10;
        RBus_UInt32  vline_625_src_sel:1;
        RBus_UInt32  vline_625_vloop_clr_en:1;
    };
}FLAG_625_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag_443_counter:8;
        RBus_UInt32  res1:24;
    };
}FLAG_443_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_flag_counter:8;
        RBus_UInt32  res1:24;
    };
}SECAM_FLAG_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  palm_flag_counter:8;
        RBus_UInt32  res1:24;
    };
}PALM_FLAG_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_valid_counter:8;
        RBus_UInt32  res1:24;
    };
}BURST_VALID_COUNTER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  midpoint_adjustment:8;
        RBus_UInt32  res1:24;
    };
}MIDPOINT_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  freq_flag_threshold_tune:8;
        RBus_UInt32  res1:24;
    };
}FREQ_FLAG_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  frequency_valid_upper_limit:8;
        RBus_UInt32  res1:24;
    };
}FREQ_VALID_MAX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  frequency_valid_inner_limit:7;
        RBus_UInt32  condition_enable:1;
        RBus_UInt32  res1:24;
    };
}FREQ_VALID_INNER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  frequency_valid_lower_limit:8;
        RBus_UInt32  res1:24;
    };
}FREQ_VALID_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_flag_frequency_upper_limit:8;
        RBus_UInt32  res1:24;
    };
}SECAM_FLAG_COUNTER_MAX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_flag_frequency_lower_limit:8;
        RBus_UInt32  res1:24;
    };
}SECAM_FLAG_COUNTER_MIN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  palm_flag_phase_adjust:8;
        RBus_UInt32  pal_flag_threshold:13;
        RBus_UInt32  res2:3;
        RBus_UInt32  palm_sw_input_sel:1;
        RBus_UInt32  palm_sw_acc_input_polar:1;
        RBus_UInt32  pal_sw_input_sel:1;
        RBus_UInt32  pal_sw_acc_input_polar:1;
        RBus_UInt32  palm_flag_limit_en:1;
        RBus_UInt32  res1:3;
    };
}PALM_FLAG_PHASE_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_mag_threshold:4;
        RBus_UInt32  burst_mag_trigger:4;
        RBus_UInt32  res1:24;
    };
}BURST_LOWER_LIMIT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  burst_noise_weighting:4;
        RBus_UInt32  burst_noise_weighting_auto:1;
        RBus_UInt32  auto_noburst_palflag_off:1;
        RBus_UInt32  secam_frequency_valid_enable:1;
        RBus_UInt32  vsync_select:1;
        RBus_UInt32  res1:24;
    };
}BURST_MAG_CHOICE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:5;
        RBus_UInt32  new_358_flag_cos_sin:1;
        RBus_UInt32  new_358_flag_cordic:1;
        RBus_UInt32  agc_gate_kill_sync_white_en:1;
        RBus_UInt32  res1:24;
    };
}NEW_358_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_dto_358_cnt_up:11;
        RBus_UInt32  res1:21;
    };
}NEW_358_CNT_UP_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_dto_358_cnt_dn:11;
        RBus_UInt32  res1:21;
    };
}NEW_358_CNT_DN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_count_th:10;
        RBus_UInt32  res1:22;
    };
}SEP_COUNT_TH_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_burst_start:11;
        RBus_UInt32  res1:21;
    };
}SEP_BURST_START0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_burst_end:11;
        RBus_UInt32  res1:21;
    };
}SEP_BURST_END0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:8;
        RBus_UInt32  sep_core_burst_rst_en:1;
        RBus_UInt32  sep_core_burst_rst:1;
        RBus_UInt32  res1:22;
    };
}SEP_BURST_RO1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_358_core_burst:8;
        RBus_UInt32  sep_443_core_burst:8;
        RBus_UInt32  sep_358_core_burst_hsync:8;
        RBus_UInt32  sep_443_core_burst_hsync:8;
    };
}SEP_BURST_RO2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_pal_secam_core_burst:8;
        RBus_UInt32  sep_pal_secam_core_burst_rst_en:1;
        RBus_UInt32  sep_pal_secam_core_burst_rst:1;
        RBus_UInt32  res1:22;
    };
}SEP_BURST_RO3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sep_358_thl:8;
        RBus_UInt32  sep_443_thl:8;
        RBus_UInt32  res1:16;
    };
}SEP_BURST_TH1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  power_358_flag:1;
        RBus_UInt32  power_443_flag:1;
        RBus_UInt32  power_secam_flag:1;
        RBus_UInt32  res2:5;
        RBus_UInt32  sep_secam_thl_ratio:8;
        RBus_UInt32  sep_secam_thl:8;
        RBus_UInt32  sep_secam_f_sel:1;
        RBus_UInt32  secam_new_condition:1;
        RBus_UInt32  res1:6;
    };
}SEP_BURST_FLAG1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mode_443358pk_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  mode_secam2_sel:2;
        RBus_UInt32  pk_foraudio:1;
        RBus_UInt32  res1:25;
    };
}AUTOMODE_443358PK_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dark_cpll_cdto_change_mode:3;
        RBus_UInt32  dark_cpll_cdto_change_en:1;
        RBus_UInt32  dark_fix_cgain:1;
        RBus_UInt32  dark_cagc_en:1;
        RBus_UInt32  dark_cagc_pll_input_sel:2;
        RBus_UInt32  dark_cagc:8;
        RBus_UInt32  dark_cresample_signed_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  dark_chromalock_cstate:3;
        RBus_UInt32  dark_chromalock_cstate_en:1;
        RBus_UInt32  dark_cstate:3;
        RBus_UInt32  dark_fixed_cstate:1;
        RBus_UInt32  dark_phase_fast_lock_en:1;
        RBus_UInt32  dark_fast_lock_en:1;
        RBus_UInt32  dark_badedit_phase_lock_en:1;
        RBus_UInt32  dark_badedit_noisy_off_en:1;
    };
}dark_cpll_cdetect_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dark_cpll_cdto_change_value:30;
        RBus_UInt32  res1:2;
    };
}dark_cpll_cdetect_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dark_palm_sw_input_sel:1;
        RBus_UInt32  dark_palm_sw_acc_input_polar:1;
        RBus_UInt32  dark_pal_sw_input_sel:1;
        RBus_UInt32  dark_pal_sw_acc_input_polar:1;
        RBus_UInt32  dark_palm_flag_limit_en:1;
        RBus_UInt32  dark_palsw_level:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_palm_flag_phase_adjust:8;
        RBus_UInt32  dark_palm_flag_counter:8;
        RBus_UInt32  res1:8;
    };
}dark_cpll_pal_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dark_lose_chromalock_level:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  dark_lose_chromalock_count:4;
        RBus_UInt32  dark_lose_acc_chromalock_level:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  dark_chromalock_input_acc_num:2;
        RBus_UInt32  dark_chromalock_input_acc_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_pal_flag_threshold:13;
        RBus_UInt32  res1:3;
    };
}dark_cpll_chromalock_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dark_cpll_start:1;
        RBus_UInt32  dark_cpll_auto_run:1;
        RBus_UInt32  dark_cpll_mode:2;
        RBus_UInt32  dark_cpll_user_mode:3;
        RBus_UInt32  dark_cpll_fix_mode_en:1;
        RBus_UInt32  dark_cpll_mode_en_ntsc:1;
        RBus_UInt32  dark_cpll_mode_en_palm:1;
        RBus_UInt32  dark_cpll_mode_en_ntsc50:1;
        RBus_UInt32  dark_cpll_mode_en_paln:1;
        RBus_UInt32  dark_cpll_mode_en_ntsc443:1;
        RBus_UInt32  dark_cpll_mode_en_pal60:1;
        RBus_UInt32  dark_cpll_mode_en_pali:1;
        RBus_UInt32  dark_cpll_chromalock_sel:1;
        RBus_UInt32  dark_cpll_vsync_num:8;
        RBus_UInt32  dark_cpll_decide_mode:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_cpll_decide_mode_error:2;
        RBus_UInt32  res1:2;
    };
}dark_cpll_controll_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dark_cpll_ntsc_lock:1;
        RBus_UInt32  dark_cpll_palm_lock:1;
        RBus_UInt32  dark_cpll_ntsc50_lock:1;
        RBus_UInt32  dark_cpll_paln_lock:1;
        RBus_UInt32  dark_cpll_ntsc443_lock:1;
        RBus_UInt32  dark_cpll_pal60_lock:1;
        RBus_UInt32  dark_cpll_pali_lock:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  dark_cpll_ntsc_pal_flag:1;
        RBus_UInt32  dark_cpll_palm_pal_flag:1;
        RBus_UInt32  dark_cpll_ntsc50_pal_flag:1;
        RBus_UInt32  dark_cpll_paln_pal_flag:1;
        RBus_UInt32  dark_cpll_ntsc443_pal_flag:1;
        RBus_UInt32  dark_cpll_pal60_pal_flag:1;
        RBus_UInt32  dark_cpll_pali_pal_flag:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  dark_cpll_ntsc_palm_flag:1;
        RBus_UInt32  dark_cpll_palm_palm_flag:1;
        RBus_UInt32  dark_cpll_ntsc50_palm_flag:1;
        RBus_UInt32  dark_cpll_paln_palm_flag:1;
        RBus_UInt32  dark_cpll_ntsc443_palm_flag:1;
        RBus_UInt32  dark_cpll_pal60_palm_flag:1;
        RBus_UInt32  dark_cpll_pali_palm_flag:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dark_cpll_loop_done:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  palm_flag_dark:1;
        RBus_UInt32  pal_flag_dark:1;
        RBus_UInt32  chromalock_dark:1;
        RBus_UInt32  chromalock_acc_dark:1;
    };
}dark_cpll_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hlock_irq_en:1;
        RBus_UInt32  vlock_irq_en:1;
        RBus_UInt32  chromalock_irq_en:1;
        RBus_UInt32  noisy_irq_en:1;
        RBus_UInt32  proscan_irq_en:1;
        RBus_UInt32  mode_irq_en:1;
        RBus_UInt32  nosig_irq_en:1;
        RBus_UInt32  vcr_irq_en:1;
        RBus_UInt32  vd_irq_en:1;
        RBus_UInt32  hstate_err_irq_en:1;
        RBus_UInt32  res1:22;
    };
}IRQ_MASK1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  field_irq_en:1;
        RBus_UInt32  mv_irq_en:1;
        RBus_UInt32  coch_irq_en:1;
        RBus_UInt32  noisy_vbi_irq_en:1;
        RBus_UInt32  ddr_addr_irq_en:1;
        RBus_UInt32  vd_scene_change_irq_en:1;
        RBus_UInt32  res1:26;
    };
}IRQ_MASK2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad4_under_irq_en:1;
        RBus_UInt32  ad4_over_irq_en:1;
        RBus_UInt32  ad3_under_irq_en:1;
        RBus_UInt32  ad3_over_irq_en:1;
        RBus_UInt32  ad2_under_irq_en:1;
        RBus_UInt32  ad2_over_irq_en:1;
        RBus_UInt32  ad1_under_irq_en:1;
        RBus_UInt32  ad1_over_irq_en:1;
        RBus_UInt32  res1:24;
    };
}IRQ_MASK3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hlock_irq:1;
        RBus_UInt32  vlock_irq:1;
        RBus_UInt32  chromalock_irq:1;
        RBus_UInt32  noisy_irq:1;
        RBus_UInt32  proscan_irq:1;
        RBus_UInt32  mode_irq:1;
        RBus_UInt32  nosig_irq:1;
        RBus_UInt32  vcr_irq:1;
        RBus_UInt32  res1:24;
    };
}IRQ_STATUS1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  field_irq:1;
        RBus_UInt32  mv_irq:1;
        RBus_UInt32  coch_irq:1;
        RBus_UInt32  noisy_vbi_irq:1;
        RBus_UInt32  ddr_addr_irq:1;
        RBus_UInt32  vd_scene_change_irq:1;
        RBus_UInt32  hstate_err_irg:1;
        RBus_UInt32  res1:25;
    };
}IRQ_STATUS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad4_underflow_irq:1;
        RBus_UInt32  ad4_overflow_irq:1;
        RBus_UInt32  ad3_underflow_irq:1;
        RBus_UInt32  ad3_overflow_irq:1;
        RBus_UInt32  ad2_underflow_irq:1;
        RBus_UInt32  ad2_overflow_irq:1;
        RBus_UInt32  ad1_underflow_irq:1;
        RBus_UInt32  ad1_overflow_irq:1;
        RBus_UInt32  res1:24;
    };
}IRQ_STATUS3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_under_threh:4;
        RBus_UInt32  adc_over_threh:4;
        RBus_UInt32  res1:24;
    };
}ADC_LIMIT_THRESHOLD_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ldpaus_th:5;
        RBus_UInt32  ldp_switch_en:1;
        RBus_UInt32  ldp_det_en:1;
        RBus_UInt32  ld_pause_detect:1;
        RBus_UInt32  res1:24;
    };
}LDPAUSE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  detect_vcr_when_h_unlock:1;
        RBus_UInt32  disable_blue_screen_when_vcr:1;
        RBus_UInt32  lock_h_on_no_signal:1;
        RBus_UInt32  freerun_sel:1;
        RBus_UInt32  vcr_disable:1;
        RBus_UInt32  vd_out_dvalid_sel_d1:1;
        RBus_UInt32  disp_freerun_sel:1;
        RBus_UInt32  coch_en:1;
        RBus_UInt32  res1:24;
    };
}VCR_OPTION_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cenable_line_count:8;
        RBus_UInt32  res1:24;
    };
}CENABLE_LINE_COUNT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:2;
        RBus_UInt32  cbcr_ini_mux:1;
        RBus_UInt32  field_toggle_en:1;
        RBus_UInt32  auto_3dchange_noisy:1;
        RBus_UInt32  auto_3dchange_vcr:1;
        RBus_UInt32  res1:26;
    };
}SIGNAL_STM_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cdet_phase_err_status:14;
        RBus_UInt32  res1:18;
    };
}CDETECT_PHASE_ERR_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_g:2;
        RBus_UInt32  sw_pb_b:2;
        RBus_UInt32  sw_pr_r:2;
        RBus_UInt32  sw_comp:2;
        RBus_UInt32  res1:24;
    };
}AD_SW_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clamp_ad4:2;
        RBus_UInt32  clamp_ad3:2;
        RBus_UInt32  clamp_ad2:2;
        RBus_UInt32  clamp_ad1:2;
        RBus_UInt32  res1:24;
    };
}CLAMP_UPDN_EN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  clamp_d_dn_en:1;
        RBus_UInt32  clamp_d_up_en:1;
        RBus_UInt32  clamp_c_dn_en:1;
        RBus_UInt32  clamp_c_up_en:1;
        RBus_UInt32  clamp_b_dn_en:1;
        RBus_UInt32  clamp_b_up_en:1;
        RBus_UInt32  clamp_a_dn_en:1;
        RBus_UInt32  clamp_a_up_en:1;
        RBus_UInt32  res1:24;
    };
}CLAMP_RGB_UPDN_EN_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fb_delay:4;
        RBus_UInt32  fb_th:3;
        RBus_UInt32  aa3_en:1;
        RBus_UInt32  res1:24;
    };
}FSW_CTRL0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rgb2cvbs_dly:6;
        RBus_UInt32  res2:2;
        RBus_UInt32  fb2rgb_dly:3;
        RBus_UInt32  res1:21;
    };
}FSW_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fb_en:1;
        RBus_UInt32  fb_sw:1;
        RBus_UInt32  aa422_en:1;
        RBus_UInt32  out444_sel:1;
        RBus_UInt32  cout_limit:1;
        RBus_UInt32  fb_inv:1;
        RBus_UInt32  yout_limit:1;
        RBus_UInt32  scart_en:1;
        RBus_UInt32  outfifo_444_sel:1;
        RBus_UInt32  res1:23;
    };
}FSW_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fb_thmin:4;
        RBus_UInt32  fb_thmax:4;
        RBus_UInt32  res1:24;
    };
}FSW_CTRL3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  contrast2:8;
        RBus_UInt32  res1:24;
    };
}LUMA_CONTRAST2_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  brightness2:8;
        RBus_UInt32  res1:24;
    };
}LUMA_BRIGHTNESS2_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cr_saturation:8;
        RBus_UInt32  res1:24;
    };
}CHROMA_SATURATION2_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cb_saturation:8;
        RBus_UInt32  res1:24;
    };
}CB_SAT_ADJ_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  peak_en2:1;
        RBus_UInt32  peak_gain2:3;
        RBus_UInt32  peak_range2:2;
        RBus_UInt32  res1:26;
    };
}LUMA_PEAKING2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fbgain:7;
        RBus_UInt32  fbgain_en:1;
        RBus_UInt32  res1:24;
    };
}FSW_GAIN_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fb_status:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  scart_vbi_rgb_sel:2;
        RBus_UInt32  res1:26;
    };
}FSW_INPUT_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  yorr_in_offset_status:12;
        RBus_UInt32  res1:20;
    };
}ADCR_CALI_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  uorg_in_offset_status:12;
        RBus_UInt32  res1:20;
    };
}ADCG_CALI_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vorb_in_offset_status:12;
        RBus_UInt32  res1:20;
    };
}ADCB_CALI_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res2:7;
        RBus_UInt32  rgb_output_en:1;
        RBus_UInt32  res1:24;
    };
}ADC_GAIN_R1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_r:10;
        RBus_UInt32  res1:22;
    };
}ADC_GAIN_R_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_g:10;
        RBus_UInt32  res1:22;
    };
}ADC_GAIN_G_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_b:10;
        RBus_UInt32  res1:22;
    };
}ADC_GAIN_B_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  offset_r:8;
        RBus_UInt32  res1:24;
    };
}ADC_OFFSET_R_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  offset_g:8;
        RBus_UInt32  res1:24;
    };
}ADC_OFFSET_G_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  offset_b:8;
        RBus_UInt32  res1:24;
    };
}ADC_OFFSET_B_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_prblevel:12;
        RBus_UInt32  res1:20;
    };
}CLAMP_TEST_REG0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  g_blevel:12;
        RBus_UInt32  res1:20;
    };
}CLAMP_TEST_REG2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  b_pbblevel:12;
        RBus_UInt32  res1:20;
    };
}CLAMP_TEST_REG4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  comp_blevel:12;
        RBus_UInt32  res1:20;
    };
}CLAMP_TEST_REG6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  comp_slevel:12;
        RBus_UInt32  res1:20;
    };
}CLAMP_TEST_REG8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vbi_blevel:12;
        RBus_UInt32  res1:20;
    };
}CLAMP_TEST_REG11_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hphase_err_status:14;
        RBus_UInt32  res1:18;
    };
}HDETECT_PHASE_ERR_STATUS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avout_fifo_rd_ptr:11;
        RBus_UInt32  avout_fifo_sel:1;
        RBus_UInt32  res1:20;
    };
}AVOUT_FIFO_RD_PTR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blank_level_comp_manu:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  blank_level_comp_manu_add:12;
        RBus_UInt32  res1:4;
    };
}BLANK_LEVEL_MANU_COMP_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blank_level_r_manu:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  blank_level_c_manu:12;
        RBus_UInt32  res1:4;
    };
}BLANK_LEVEL_MANU_C_R_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  blank_level_b_manu:12;
        RBus_UInt32  res2:4;
        RBus_UInt32  blank_level_g_manu:12;
        RBus_UInt32  res1:4;
    };
}BLANK_LEVEL_MANU_G_B_VALUE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  factory_flag:1;
        RBus_UInt32  fpga_test1:31;
    };
}FPGA_TEST_REG1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test2:32;
    };
}FPGA_TEST_REG2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test3:32;
    };
}FPGA_TEST_REG3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test4:32;
    };
}FPGA_TEST_REG4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test5:32;
    };
}FPGA_TEST_REG5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test6:32;
    };
}FPGA_TEST_REG6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test7:32;
    };
}FPGA_TEST_REG7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fpga_test8:32;
    };
}FPGA_TEST_REG8_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_notch_filter:2;
        RBus_UInt32  res5:2;
        RBus_UInt32  secam_flag_sel:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  drdb_vlpf_en:1;
        RBus_UInt32  drdb_freq_const:1;
        RBus_UInt32  secam_y_lpf_sel:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  secam_y_hpf_sel:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  secam_y_fir_en:1;
        RBus_UInt32  res1:15;
    };
}SECAM_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dr_offset:8;
        RBus_UInt32  res1:24;
    };
}SECAM_DRFREQ_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  db_offset:8;
        RBus_UInt32  res1:24;
    };
}SECAM_DBFREQ_OFFSET_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_phase_diff_hcount:7;
        RBus_UInt32  secam_phase_diff_hcount_en:1;
        RBus_UInt32  res1:24;
    };
}SECAM_HCOUNT_RESET_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_phase_diff_dr:8;
        RBus_UInt32  res1:24;
    };
}PHASE_DIFF_DR_RST_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_phase_diff_db:8;
        RBus_UInt32  res1:24;
    };
}PHASE_DIFF_DB_RST_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_gain_drdb:7;
        RBus_UInt32  secam_gain_drdb_en:1;
        RBus_UInt32  res1:24;
    };
}DRDB_GAIN_TABLE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_gain_y:7;
        RBus_UInt32  secam_gain_y_en:1;
        RBus_UInt32  res1:24;
    };
}Y_GAIN_TABLE_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_gain_delay:5;
        RBus_UInt32  res1:27;
    };
}SECAM_GAIN_DLY_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_gain_debug:7;
        RBus_UInt32  secam_gain_debug_en:1;
        RBus_UInt32  res1:24;
    };
}SECAM_GAIN_TABLE_DEBUG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_secam_phase_diff_hcount:7;
        RBus_UInt32  new_secam_phase_diff_hcount_en:1;
        RBus_UInt32  res1:24;
    };
}NEW_SECAM_HCOUNT_RESET_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_secam_phase_diff_dr:8;
        RBus_UInt32  res1:24;
    };
}NEW_SECAM_PHASE_DIFF_DR_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_secam_phase_diff_db:8;
        RBus_UInt32  res1:24;
    };
}NEW_SECAM_PHASE_DIFF_DB_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  new_secam_cdto_inc:30;
        RBus_UInt32  res1:2;
    };
}NEW_SECAM_CDTO_INC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  secam_gp_thl:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  secam_gp_step:10;
        RBus_UInt32  res1:9;
        RBus_UInt32  secam_gp_en:1;
    };
}SECAM_GP_RM_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_initialization:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  ps_updn_swap:1;
        RBus_UInt32  res3:4;
        RBus_UInt32  v8format_sel:1;
        RBus_UInt32  res2:16;
        RBus_UInt32  vd_output_27_repeat_en:1;
        RBus_UInt32  vd_output_27_repeat_sel:1;
        RBus_UInt32  vd_output_135_sel:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  hresampler_combi_delay:3;
        RBus_UInt32  vdec_ps_disp_27_en:1;
    };
}FIFO_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_empty_status:1;
        RBus_UInt32  fifo_full_status:1;
        RBus_UInt32  res4:6;
        RBus_UInt32  ps_540_coe_modify:7;
        RBus_UInt32  res3:1;
        RBus_UInt32  ps_540_select_tap:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  ps_540_coe_en:1;
        RBus_UInt32  res1:7;
    };
}FIFO_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll_i_gain:8;
        RBus_UInt32  res1:24;
    };
}I_GAIN_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pll_div:4;
        RBus_UInt32  ps_dn_en:1;
        RBus_UInt32  ps_up_en:1;
        RBus_UInt32  ndivload_en:1;
        RBus_UInt32  swallow_on_vsync:1;
        RBus_UInt32  swallow_freq_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  fifo_depth_wo_ps:8;
        RBus_UInt32  fifo_wo_ps:1;
        RBus_UInt32  res1:11;
    };
}MISC_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_depth_min_status:8;
        RBus_UInt32  fifo_depth_min_clr:1;
        RBus_UInt32  res1:23;
    };
}FIFO_DEPTH_MIN_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_depth_max_status:8;
        RBus_UInt32  fifo_depth_max_clr:1;
        RBus_UInt32  res1:23;
    };
}FIFO_DEPTH_MAX_STATUS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ps_pselload:1;
        RBus_UInt32  ps_divload:1;
        RBus_UInt32  res2:4;
        RBus_UInt32  ps_dn_i:1;
        RBus_UInt32  ps_up_i:1;
        RBus_UInt32  res1:24;
    };
}PLL_DEBUG_CTRL1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ps_ndiv:4;
        RBus_UInt32  ps_psel:3;
        RBus_UInt32  pll_debug_en:1;
        RBus_UInt32  res1:24;
    };
}PLL_DEBUG_CTRL2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  k_sel:2;
        RBus_UInt32  lpf_en:1;
        RBus_UInt32  period_sel:2;
        RBus_UInt32  cnt_en:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  ps_new_kp:3;
        RBus_UInt32  ps_new_kikp:1;
        RBus_UInt32  ps_fix_value:8;
        RBus_UInt32  ps_fix_en:1;
        RBus_UInt32  res1:11;
    };
}DISP_FSYNC_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_depth_wo_ps_max:8;
        RBus_UInt32  fifo_depth_wo_ps_min:8;
        RBus_UInt32  fifo_wo_ps_hlen_min:12;
        RBus_UInt32  fifo_wo_ps_adapt:1;
        RBus_UInt32  fifo_wo_ps_err_act:1;
        RBus_UInt32  fifo_wo_ps_clk_jump:1;
        RBus_UInt32  fifo_wo_ps_read_repeat_en:1;
    };
}FIFO_WO_PS_FUNC_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_wo_ps_ps_ndiv0:5;
        RBus_UInt32  fifo_wo_ps_ps_psel0:3;
        RBus_UInt32  fifo_wo_ps_ps_divload0:1;
        RBus_UInt32  fifo_wo_ps_ps_pselload0:1;
        RBus_UInt32  fifo_wo_ps_ps_dn_i0:1;
        RBus_UInt32  fifo_wo_ps_ps_up_i0:1;
        RBus_UInt32  fifo_wo_ps_ps_ndiv1:5;
        RBus_UInt32  fifo_wo_ps_ps_psel1:3;
        RBus_UInt32  fifo_wo_ps_ps_divload1:1;
        RBus_UInt32  fifo_wo_ps_ps_pselload1:1;
        RBus_UInt32  fifo_wo_ps_ps_dn_i1:1;
        RBus_UInt32  fifo_wo_ps_ps_up_i1:1;
        RBus_UInt32  res1:8;
    };
}FIFO_WO_PS_CLK_STATE_PARAMETER_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_out_line_len:12;
        RBus_UInt32  fifo_clk_state:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  stable_fifo_depth:8;
        RBus_UInt32  res1:8;
    };
}FIFO_STATUS_NO_PLL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  debug_test:7;
        RBus_UInt32  debug_test_enable:1;
        RBus_UInt32  res1:24;
    };
}DEBUG_MUX_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  muxanaloga:4;
        RBus_UInt32  muxanalogb:4;
        RBus_UInt32  res1:24;
    };
}VIDEO_DEBUG_ANALOG_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  muxdigital:4;
        RBus_UInt32  debug_test_dac_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  clk_sct_polarity:1;
        RBus_UInt32  clk_dac_polarity:1;
        RBus_UInt32  res1:24;
    };
}VIDEO_DEBUG_DIGITAL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pattern_generator_enable:1;
        RBus_UInt32  pattern_gen_cvbs_mode:1;
        RBus_UInt32  pattern_gen_input_mode_sel:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  crc_chk_sel:1;
        RBus_UInt32  pattern_gen_scart_en:1;
        RBus_UInt32  fifo_out_pattern_gen_en:1;
        RBus_UInt32  patgen_vline_en:1;
        RBus_UInt32  patgen_vline:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  patgen_vline_vactive_end:10;
        RBus_UInt32  res1:2;
    };
}PATTERN_CONTROL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  crc_result:32;
    };
}CRC_RESULT3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  patgen_burst_gain:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  patgen_sync_gain:3;
        RBus_UInt32  clk_polarity:1;
        RBus_UInt32  clk_vdadc_polarity:1;
        RBus_UInt32  res1:23;
    };
}PATGEN_CTRL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mode_27_1:1;
        RBus_UInt32  bist_mode_27_2:1;
        RBus_UInt32  bist_mode_dma:1;
        RBus_UInt32  bist_mode_fifo:1;
        RBus_UInt32  bist_mode_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_done_27_1:1;
        RBus_UInt32  bist_done_27_2:1;
        RBus_UInt32  bist_done_dma:1;
        RBus_UInt32  bist_done_fifo:1;
        RBus_UInt32  bist_done_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_fail_27_1:1;
        RBus_UInt32  bist_fail_27_2:1;
        RBus_UInt32  bist_fail_dma:1;
        RBus_UInt32  bist_fail_fifo:1;
        RBus_UInt32  bist_fail_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_mode_27_1:1;
        RBus_UInt32  bist_drf_mode_27_2:1;
        RBus_UInt32  bist_drf_mode_dma:1;
        RBus_UInt32  bist_drf_mode_fifo:1;
        RBus_UInt32  bist_drf_mode_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_DRF_MODE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_resume_27_1:1;
        RBus_UInt32  bist_drf_resume_27_2:1;
        RBus_UInt32  bist_drf_resume_dma:1;
        RBus_UInt32  bist_drf_resume_fifo:1;
        RBus_UInt32  bist_drf_resume_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_DRF_RESUME_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_done_27_1:1;
        RBus_UInt32  bist_drf_done_27_2:1;
        RBus_UInt32  bist_drf_done_dma:1;
        RBus_UInt32  bist_drf_done_fifo:1;
        RBus_UInt32  bist_drf_done_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_DRF_DONE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_pause_27_1:1;
        RBus_UInt32  bist_drf_pause_27_2:1;
        RBus_UInt32  bist_drf_pause_dma:1;
        RBus_UInt32  bist_drf_pause_fifo:1;
        RBus_UInt32  bist_drf_pause_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_DRF_PAUSE_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_fail_27_1:1;
        RBus_UInt32  bist_drf_fail_27_2:1;
        RBus_UInt32  bist_drf_fail_dma:1;
        RBus_UInt32  bist_drf_fail_fifo:1;
        RBus_UInt32  bist_drf_fail_out:1;
        RBus_UInt32  res1:27;
    };
}BIST_DRF_FAIL_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mem_fail_27_1:6;
        RBus_UInt32  res1:26;
    };
}BIST_FAIL_27_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mem_fail_27_2:10;
        RBus_UInt32  res1:22;
    };
}BIST_FAIL_27_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mem_fail_dma:5;
        RBus_UInt32  res1:27;
    };
}BIST_FAIL_DMA_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mem_fail_fifo:1;
        RBus_UInt32  res1:31;
    };
}BIST_FAIL_FIFO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_mem_fail_out:4;
        RBus_UInt32  res1:28;
    };
}BIST_FAIL_OUT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_mem_fail_27_1:6;
        RBus_UInt32  res1:26;
    };
}BIST_DRF_FAIL_27_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_mem_fail_27_2:10;
        RBus_UInt32  res1:22;
    };
}BIST_DRF_FAIL_27_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_mem_fail_dma:5;
        RBus_UInt32  res1:27;
    };
}BIST_DRF_FAIL_DMA_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_mem_fail_fifo:1;
        RBus_UInt32  res1:31;
    };
}BIST_DRF_FAIL_FIFO_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bist_drf_mem_fail_out:4;
        RBus_UInt32  res1:28;
    };
}BIST_DRF_FAIL_OUT_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mbist_dvse_27_1:1;
        RBus_UInt32  mbist_dvs_27_1:4;
        RBus_UInt32  mbist_dvse_27_2:1;
        RBus_UInt32  mbist_dvs_27_2:4;
        RBus_UInt32  mbist_dvse_dma:1;
        RBus_UInt32  mbist_dvs_dma:4;
        RBus_UInt32  mbist_dvse_fifo:1;
        RBus_UInt32  mbist_dvs_fifo:4;
        RBus_UInt32  mbist_dvse_out:1;
        RBus_UInt32  mbist_dvs_out:4;
        RBus_UInt32  res1:7;
    };
}BIST_DVSE_DVS_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mbist_dvse_dma_2:1;
        RBus_UInt32  mbist_dvs_dma_2:4;
        RBus_UInt32  mbist_dvse_fifo_2:1;
        RBus_UInt32  mbist_dvs_fifo_2:4;
        RBus_UInt32  res2:2;
        RBus_UInt32  mbist_ls_cntl:1;
        RBus_UInt32  res1:19;
    };
}BIST_DVSE_DVS2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_updn_debug_dn:1;
        RBus_UInt32  adc_updn_debug_up:1;
        RBus_UInt32  adc_updn_debug_en:1;
        RBus_UInt32  res1:29;
    };
}ADC_UPDN_CTRL_RBUS;


#endif







#endif //_RBUS_VDTOP_REG_H_

