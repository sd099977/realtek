/**
* @file rbusSirius_DesignSpec_AUDIOReg.h
* RBus systemc program.
*
* @author RS_MM2_SD
* @email jason9.ccc@realtek.com
 * @date 2013/12/26
* @ingroup model_rbus
 * @version { 1.0 }
 **
 */

#ifndef _RBUS_AUDIO_REG_H_
#define _RBUS_AUDIO_REG_H_

#include "rbusTypes.h"



//  SIRIUS_DESIGNSPEC_AUDIO Register Address



#define  AUDIO_GLOBAL_CTRL_0_VADDR                  (0xb8006000)
#define  AUDIO_GLOBAL_CTRL_1_VADDR                  (0xb8006004)
#define  AUDIO_TCON0_ASRC_IP_VADDR                  (0xb8006008)
#define  AUDIO_TCON1_ASRC_IP_VADDR                  (0xb800600c)
#define  AUDIO_PLLCG_SPDIF_GAIN_CR0_VADDR           (0xb8006010)
#define  AUDIO_PLLCG_SPDIF_GAIN_CR1_VADDR           (0xb8006014)
#define  AUDIO_PLLCG_SPDIF_GAIN_CR2_VADDR           (0xb8006018)
#define  AUDIO_PLLCG_SPDIF_NUMBER_VADDR             (0xb800601c)
#define  AUDIO_PLLCG_SPDIF_BOUND_VADDR              (0xb8006020)
#define  AUDIO_GLOBAL_DUMMY_VADDR                   (0xb8006024)
#define  AUDIO_AO_HDMI_FS_SEL_VADDR                 (0xb8006028)
#define  AUDIO_INTERRUPT_EN_VADDR                   (0xb8006050)
#define  AUDIO_INTERRUPT_STATUS_VADDR               (0xb8006054)
#define  AUDIO_AIO_TIMER_EN_VADDR                   (0xb8006058)
#define  AUDIO_AIN_COUNTER_VADDR                    (0xb800605c)
#define  AUDIO_AIN_COMPARE_VADDR                    (0xb8006060)
#define  AUDIO_AOUT_COUNTER_VADDR                   (0xb8006064)
#define  AUDIO_AOUT_COMPARE_VADDR                   (0xb8006068)
#define  AUDIO_SW_DBG_REG_0_VADDR                   (0xb8006070)
#define  AUDIO_SW_DBG_REG_1_VADDR                   (0xb8006074)
#define  AUDIO_SW_DBG_REG_2_VADDR                   (0xb8006078)
#define  AUDIO_SW_DBG_REG_3_VADDR                   (0xb800607c)
#define  AUDIO_I2S_IN_PRIMARY_VADDR                 (0xb8006100)
#define  AUDIO_SPDIF_IN_VADDR                       (0xb8006130)
#define  AUDIO_SPDIF_IN_CS_VADDR                    (0xb8006134)
#define  AUDIO_SPDIF_IN_CS_2_VADDR                  (0xb8006138)
#define  AUDIO_SPDIF_IN_CS_3_VADDR                  (0xb800613c)
#define  AUDIO_I2S_OUT_VADDR                        (0xb8006150)
#define  AUDIO_I2S_OUT_SEL_VADDR                    (0xb8006154)
#define  AUDIO_SPDIF_OUT_VADDR                      (0xb8006170)
#define  AUDIO_SPDIF_OUT_2_VADDR                    (0xb800617c)
#define  AUDIO_SPDIF_OUT_CS_VADDR                   (0xb8006174)
#define  AUDIO_SPDIF_OUT_CS_2_VADDR                 (0xb8006178)
#define  AUDIO_SIF_AGC_EVAL_CNT_VADDR               (0xb8006180)
#define  AUDIO_SIF_AGC_OPTIMAL_VADDR                (0xb8006184)
#define  AUDIO_SIF_AGC_THRESHOLD_VADDR              (0xb8006188)
#define  AUDIO_SIF_AGC_STATUS_VADDR                 (0xb800618c)
#define  AUDIO_SIF_AGC2_CTRL_VADDR                  (0xb8006190)
#define  AUDIO_SIF_AGC2_STATUS_VADDR                (0xb8006194)
#define  AUDIO_PEAK_CONTORL_VADDR                   (0xb80061a0)
#define  AUDIO_PEAK_CONTORL_L_0_VADDR               (0xb80061b0)
#define  AUDIO_PEAK_CONTROL_L_1_VADDR               (0xb80061b4)
#define  AUDIO_PEAK_STATUS_L_VADDR                  (0xb80061b8)
#define  AUDIO_PEAK_STATUS_L_2_VADDR                (0xb80061bc)
#define  AUDIO_PEAK_CONTORL_R_0_VADDR               (0xb80061c0)
#define  AUDIO_PEAK_CONTORL_R_1_VADDR               (0xb80061c4)
#define  AUDIO_PEAK_STATUS_R_VADDR                  (0xb80061c8)
#define  AUDIO_PEAK_STATUS_R_2_VADDR                (0xb80061cc)
#define  AUDIO_POST_PEAK_CONTORL_VADDR              (0xb80061d0)
#define  AUDIO_POST_PEAK_CONTORL_L_0_VADDR          (0xb80061e0)
#define  AUDIO_POST_PEAK_CONTROL_L_1_VADDR          (0xb80061e4)
#define  AUDIO_POST_PEAK_STATUS_L_VADDR             (0xb80061e8)
#define  AUDIO_POST_PEAK_STATUS_L_2_VADDR           (0xb80061ec)
#define  AUDIO_POST_PEAK_CONTORL_R_0_VADDR          (0xb80061f0)
#define  AUDIO_POST_PEAK_CONTORL_R_1_VADDR          (0xb80061f4)
#define  AUDIO_POST_PEAK_STATUS_R_VADDR             (0xb80061f8)
#define  AUDIO_POST_PEAK_STATUS_R_2_VADDR           (0xb80061fc)
#define  AUDIO_MSD_CRTL_WORD_VADDR                  (0xb8006200)
#define  AUDIO_MSD_RESULT_VADDR                     (0xb8006204)
#define  AUDIO_MSD_STATUS_VADDR                     (0xb8006208)
#define  AUDIO_MAIN_TONE_THRESHOLD_VADDR            (0xb800620c)
#define  AUDIO_MAIN_TONE_THRESHOLD_HD_VADDR         (0xb8006210)
#define  AUDIO_BW_THRESHOLD_VADDR                   (0xb8006214)
#define  AUDIO_MAIN_SUB_RATIO_VADDR                 (0xb8006218)
#define  AUDIO_MSD_MAG_4_5_VADDR                    (0xb800621c)
#define  AUDIO_MSD_MAG_4_28_VADDR                   (0xb8006220)
#define  AUDIO_MSD_MAG_4_72_VADDR                   (0xb8006224)
#define  AUDIO_MSD_MAG_5_5_VADDR                    (0xb8006228)
#define  AUDIO_MSD_MAG_5_25_VADDR                   (0xb800622c)
#define  AUDIO_MSD_MAG_5_74_VADDR                   (0xb8006230)
#define  AUDIO_MSD_CARRIER_5_85_VADDR               (0xb8006234)
#define  AUDIO_MSD_CARRIER_5_95_VADDR               (0xb8006238)
#define  AUDIO_MSD_MAG_6_VADDR                      (0xb800623c)
#define  AUDIO_MSD_MAG_6_25_VADDR                   (0xb8006240)
#define  AUDIO_MSD_CARRIER_6_5_VADDR                (0xb8006244)
#define  AUDIO_MSD_MAG_6_552_VADDR                  (0xb8006248)
#define  AUDIO_MSD_CARRIER_6_74_VADDR               (0xb800624c)
#define  AUDIO_MSD_FLAGS_VADDR                      (0xb8006250)
#define  AUDIO_MSD_PROGRAMMABLE_FREQ_VADDR          (0xb8006254)
#define  AUDIO_THRESHOLD_MSD_CARRIER_FW_VADDR       (0xb8006258)
#define  AUDIO_MSD_PROGRAMMABLE_FREQ_1_VADDR        (0xb800625c)
#define  AUDIO_THRESHOLD_MSD_CARRIER_FW_1_VADDR     (0xb8006260)
#define  AUDIO_MSD_PROGRAMMABLE_FREQ_2_VADDR        (0xb8006264)
#define  AUDIO_THRESHOLD_MSD_CARRIER_FW_2_VADDR     (0xb8006268)
#define  AUDIO_MSD_PROGRAMMABLE_FREQ_3_VADDR        (0xb800626c)
#define  AUDIO_THRESHOLD_MSD_CARRIER_FW_3_VADDR     (0xb8006270)
#define  AUDIO_MSD_PROGRAMMABLE_FREQ_4_VADDR        (0xb8006274)
#define  AUDIO_THRESHOLD_MSD_CARRIER_FW_4_VADDR     (0xb8006278)
#define  AUDIO_MSD_SECOND_REG_STD_VADDR             (0xb800627c)
#define  AUDIO_SECOND_MAIN_TONE_THRESHOLD_VADDR     (0xb8006280)
#define  AUDIO_MSD_BIST_VADDR                       (0xb8006284)
#define  AUDIO_MSD_MAIN_MAG_ORI1_VADDR              (0xb8006288)
#define  AUDIO_MSD_MAIN_MAG_ORI2_VADDR              (0xb800628c)
#define  AUDIO_MSD_GAIN_CTRL_VADDR                  (0xb8006290)
#define  AUDIO_MSD_UPDATE_COUNT_VADDR               (0xb8006294)
#define  AUDIO_MODE_DETECT_VADDR                    (0xb8006300)
#define  AUDIO_MD_CTRL_VADDR                        (0xb8006310)
#define  AUDIO_MD_STATUS_1_VADDR                    (0xb8006314)
#define  AUDIO_MD_STATUS_2_VADDR                    (0xb8006318)
#define  AUDIO_CARRIER_FREQ_DEVIATION_CTRL_VADDR    (0xb8006350)
#define  AUDIO_CARRIER_PHASE_DELTA_VADDR            (0xb8006354)
#define  AUDIO_A2_EIAJ_DC_FILTER_VADDR              (0xb8006358)
#define  AUDIO_AM_VADDR                             (0xb8006360)
#define  AUDIO_BIST_AM_VADDR                        (0xb8006364)
#define  AUDIO_SAP_BPF_STAGE1_1_VADDR               (0xb80063d0)
#define  AUDIO_SAP_BPF_STAGE1_2_VADDR               (0xb80063d4)
#define  AUDIO_SAP_BPF_STAGE1_3_VADDR               (0xb80063d8)
#define  AUDIO_SAP_BPF_STAGE2_1_VADDR               (0xb80063e0)
#define  AUDIO_SAP_BPF_STAGE2_2_VADDR               (0xb80063e4)
#define  AUDIO_SAP_BPF_STAGE2_3_VADDR               (0xb80063e8)
#define  AUDIO_SAP_BPF_STAGE3_1_VADDR               (0xb80063f0)
#define  AUDIO_SAP_BPF_STAGE3_2_VADDR               (0xb80063f4)
#define  AUDIO_SAP_BPF_STAGE3_3_VADDR               (0xb80063f8)
#define  AUDIO_BTSC_PILOT_THRES_VADDR               (0xb8006400)
#define  AUDIO_BTSC_PILOT_STATUS_VADDR              (0xb8006404)
#define  AUDIO_BTSC_SAP_THRESH_VADDR                (0xb8006408)
#define  AUDIO_BTSC_SAP_NOISE_TH_VADDR              (0xb800640c)
#define  AUDIO_BTSC_SAP_NOISE_VADDR                 (0xb8006410)
#define  AUDIO_BTSC_SAP_STATUS_VADDR                (0xb8006414)
#define  AUDIO_BTSC_SAP_DEBOUNCE_VADDR              (0xb8006418)
#define  AUDIO_BTSC_SIF_FM_MAGNITUDE_VADDR          (0xb800641c)
#define  AUDIO_BTSC_TEST_MUX_SEL_VADDR              (0xb8006420)
#define  AUDIO_BTSC_DUMMY_VADDR                     (0xb8006424)
#define  AUDIO_BTSC_PILOT_PHASE_DELTA_VADDR         (0xb8006428)
#define  AUDIO_PHASE_ERROR_PI_GAIN_VADDR            (0xb800642c)
#define  AUDIO_PHASE_ERR_THRESHOLD_VADDR            (0xb8006430)
#define  AUDIO_PHASE_ERR_THRESHOLD2_VADDR           (0xb8006434)
#define  AUDIO_FREQ_CORRECTION_VADDR                (0xb8006438)
#define  AUDIO_PHASE_ERROR_VADDR                    (0xb800643c)
#define  AUDIO_A2_EIAJ_DEMOD_VADDR                  (0xb8006450)
#define  AUDIO_A2_EIAJ_MAG_NOISE_SUB_VADDR          (0xb8006454)
#define  AUDIO_A2_EIAJ_MAG_NOISE_VADDR              (0xb8006458)
#define  AUDIO_MBIST_A2_EIAJ_DEMOD_RM_0_VADDR       (0xb800645c)
#define  AUDIO_MBIST_A2_EIAJ_DEMOD_RM_1_VADDR       (0xb8006460)
#define  AUDIO_MBIST_A2_EIAJ_DEMOD_RME_VADDR        (0xb8006464)
#define  AUDIO_NICAM_DEMOD_VADDR                    (0xb8006500)
#define  AUDIO_NICAM_DAGC_CTRL_VADDR                (0xb8006504)
#define  AUDIO_NICAM_DAGC_THRESHOLD_VADDR           (0xb8006508)
#define  AUDIO_NICAM_DAGC_MAG_VADDR                 (0xb800650c)
#define  AUDIO_NICAM_DECODE_CTRL_VADDR              (0xb8006510)
#define  AUDIO_NICAM_DECODE_STATUS_VADDR            (0xb8006514)
#define  AUDIO_NICAM_AUTO_SWITCH_VADDR              (0xb8006518)
#define  AUDIO_NICAM_DEMOD_AUTO_RECOVERY_VADDR      (0xb800651c)
#define  AUDIO_NICAM_BIT_ERROR_RATE_VADDR           (0xb8006520)
#define  AUDIO_NICAM_BER_WINDOW_VADDR               (0xb8006524)
#define  AUDIO_DOWN_SAMPLE_CONTROL_FOR_PLAYBACK_VADDR    (0xb8006550)
#define  AUDIO_DOWN_SAMPLE_FIFO_SOURCE_SEL_VADDR    (0xb8006554)
#define  AUDIO_DOWN_SAMPLE_MBIST_RECODING_VADDR     (0xb8006558)
#define  AUDIO_DOWN_SAMPLE_FIFO_PRE_SCALE_VADDR     (0xb800655c)
#define  AUDIO_DOWN_SAMPLE_MBIST_RM_VADDR           (0xb8006560)
#define  AUDIO_DOWN_SAMPLE_MBIST_RME_VADDR          (0xb8006568)
#define  AUDIO_DOWN_SAMPLE_CONTROL_FOR_TS_VADDR     (0xb80065a0)
#define  AUDIO_TS_DS_FIFO_MBIST_RM_VADDR            (0xb80065a4)
#define  AUDIO_TS_DS_FIFO_MBIST_RME_VADDR           (0xb80065a8)
#define  AUDIO_ADMA_CSR_VADDR                       (0xb8006600)
#define  AUDIO_ADMA_WCONF_VADDR                     (0xb8006604)
#define  AUDIO_ADMA_WSADR0_VADDR                    (0xb8006608)
#define  AUDIO_ADMA_WSADR1_VADDR                    (0xb800660c)
#define  AUDIO_ADMA_RCONF_VADDR                     (0xb8006628)
#define  AUDIO_ADMA_WRCONF_VADDR                    (0xb800662c)
#define  AUDIO_ADMA_RSADR0_VADDR                    (0xb8006630)
#define  AUDIO_ADMA_RSADR1_VADDR                    (0xb8006634)
#define  AUDIO_ADMA_RSADR2_VADDR                    (0xb8006638)
#define  AUDIO_ADMA_RSADR3_VADDR                    (0xb800663c)
#define  AUDIO_ADMA_CHCONF_VADDR                    (0xb8006650)
#define  AUDIO_AUDIO_DMA_BIST_CONTROL_INDICATE_VADDR    (0xb8006654)
#define  AUDIO_TSADMA_CSR_VADDR                     (0xb80066a0)
#define  AUDIO_TS_ADMA_WCONF_VADDR                  (0xb80066a4)
#define  AUDIO_TS_ADMA_WSADR0_VADDR                 (0xb80066a8)
#define  AUDIO_TS_ADMA_WSADR1_VADDR                 (0xb80066ac)
#define  AUDIO_TS_ADMA_RCONF_VADDR                  (0xb80066b0)
#define  AUDIO_TS_ADMA_WRCONF_VADDR                 (0xb80066b4)
#define  AUDIO_TS_ADMA_RSADR0_VADDR                 (0xb80066b8)
#define  AUDIO_TS_ADMA_RSADR1_VADDR                 (0xb80066bc)
#define  AUDIO_TS_ADMA_RSADR2_VADDR                 (0xb80066c0)
#define  AUDIO_TS_ADMA_CHCONF_VADDR                 (0xb80066c4)
#define  AUDIO_TS_DMA_BIST_CONTROL_INDICATE_VADDR   (0xb80066c8)
#define  AUDIO_TEST_DMA_CONTROL_REGISTER_VADDR      (0xb80066e0)
#define  AUDIO_TEST_DMA_START_ADDRESS_VADDR         (0xb80066e4)
#define  AUDIO_TEST_DMA_STOP_ADDRESS_VADDR          (0xb80066e8)
#define  AUDIO_TEST_MODE_SELECT_VADDR               (0xb80066ec)
#define  AUDIO_TEST_CUR_ADDRESS_VADDR               (0xb80066f0)
#define  AUDIO_HW_PROCESS_CONTROL_VADDR             (0xb8006700)
#define  AUDIO_AUTO_VOLUME_CONTROL_0_VADDR          (0xb8006704)
#define  AUDIO_AVC_VOLUME_CONTROL_1_VADDR           (0xb8006708)
#define  AUDIO_AVC_VOLUME_CONTROL_2_VADDR           (0xb800670c)
#define  AUDIO_AVC_VOLUME_CONTROL_3_VADDR           (0xb8006820)
#define  AUDIO_SPATIAL_EFFECT_CONTROL_0_VADDR       (0xb8006710)
#define  AUDIO_SPATIAL_EFFECT_CONTROL_1_VADDR       (0xb8006714)
#define  AUDIO_EQ_HP_VADDR                          (0xb8006718)
#define  AUDIO_EQ_LP_VADDR                          (0xb800671c)
#define  AUDIO_EQ_BP1_1_VADDR                       (0xb8006720)
#define  AUDIO_EQ_BP1_2_VADDR                       (0xb8006724)
#define  AUDIO_EQ_BP2_1_VADDR                       (0xb8006728)
#define  AUDIO_EQ_BP2_2_VADDR                       (0xb800672c)
#define  AUDIO_EQ_BP3_1_VADDR                       (0xb8006730)
#define  AUDIO_EQ_BP3_2_VADDR                       (0xb8006734)
#define  AUDIO_EQ_BP4_1_VADDR                       (0xb8006738)
#define  AUDIO_EQ_BP4_2_VADDR                       (0xb800673c)
#define  AUDIO_EQ_BP5_1_VADDR                       (0xb8006740)
#define  AUDIO_EQ_BP5_2_VADDR                       (0xb8006744)
#define  AUDIO_EQ_BP6_1_VADDR                       (0xb8006748)
#define  AUDIO_EQ_BP6_2_VADDR                       (0xb800674c)
#define  AUDIO_EQ_BP7_1_VADDR                       (0xb8006750)
#define  AUDIO_EQ_BP7_2_VADDR                       (0xb8006754)
#define  AUDIO_EQ_BP8_1_VADDR                       (0xb8006758)
#define  AUDIO_EQ_BP8_2_VADDR                       (0xb800675c)
#define  AUDIO_EQ_BP9_1_VADDR                       (0xb8006760)
#define  AUDIO_EQ_BP9_2_VADDR                       (0xb8006764)
#define  AUDIO_EQ_CONTROL_REGISTER_VADDR            (0xb8006768)
#define  AUDIO_EQ_STATUS_REGISTER_VADDR             (0xb800676c)
#define  AUDIO_LR_LOUD_LP_VADDR                     (0xb8006770)
#define  AUDIO_LR_LOUD_BP1_1_VADDR                  (0xb8006774)
#define  AUDIO_LR_LOUD_BP1_2_VADDR                  (0xb8006778)
#define  AUDIO_LR_LOUD_BP2_1_VADDR                  (0xb800677c)
#define  AUDIO_LR_LOUD_BP2_2_VADDR                  (0xb8006780)
#define  AUDIO_LSRS_LOUD_LP_VADDR                   (0xb8006784)
#define  AUDIO_LSRS_LOUD_BP1_1_VADDR                (0xb8006788)
#define  AUDIO_LSRS_LOUD_BP1_2_VADDR                (0xb800678c)
#define  AUDIO_LSRS_LOUD_BP2_1_VADDR                (0xb8006790)
#define  AUDIO_LSRS_LOUD_BP2_2_VADDR                (0xb8006794)
#define  AUDIO_CSW_LOUD_LP_VADDR                    (0xb8006798)
#define  AUDIO_CSW_LOUD_BP1_1_VADDR                 (0xb800679c)
#define  AUDIO_CSW_LOUD_BP1_2_VADDR                 (0xb80067a0)
#define  AUDIO_CSW_LOUD_BP2_1_VADDR                 (0xb80067a4)
#define  AUDIO_CSW_LOUD_BP2_2_VADDR                 (0xb80067a8)
#define  AUDIO_LOUDNESS_CONTROL_REGISTER_VADDR      (0xb80067ac)
#define  AUDIO_LOUDNESS_STATUS_REGISTER_VADDR       (0xb80067b0)
#define  AUDIO_DIGITAL_VOLUME_CONTROL_0_VADDR       (0xb80067b4)
#define  AUDIO_DIGITAL_VOLUME_CONTROL_1_VADDR       (0xb80067b8)
#define  AUDIO_LR_DIGITAL_VOLUME_CONTROL_VADDR      (0xb80067bc)
#define  AUDIO_SUBWOOFER_DIGITAL_VOLUME_CONTROL_VADDR    (0xb80067c0)
#define  AUDIO_CSW_DIGITAL_VOLUME_CONTROL_VADDR     (0xb80067c4)
#define  AUDIO_DOUBLE_BUFFER_ACK_VADDR              (0xb80067c8)
#define  AUDIO_AVC2_CONTROL_1_CH01_VADDR            (0xb80067cc)
#define  AUDIO_AVC2_CONTROL_2_CH01_VADDR            (0xb80067d0)
#define  AUDIO_AVC2_CONTROL_3_CH01_VADDR            (0xb80067d4)
#define  AUDIO_AVC2_CONTROL_4_CH01_VADDR            (0xb80067d8)
#define  AUDIO_AVC2_CONTROL_5_CH01_VADDR            (0xb8006824)
#define  AUDIO_AVC2_CONTROL_6_CH01_VADDR            (0xb8006828)
#define  AUDIO_AVC2_CONTROL_7_CH01_VADDR            (0xb800682c)
#define  AUDIO_AVC2_CONTROL_1_CH23_VADDR            (0xb80067dc)
#define  AUDIO_AVC2_CONTROL_2_CH23_VADDR            (0xb80067e0)
#define  AUDIO_AVC2_CONTROL_3_CH23_VADDR            (0xb80067e4)
#define  AUDIO_AVC2_CONTROL_4_CH23_VADDR            (0xb80067e8)
#define  AUDIO_AVC2_CONTROL_1_CH45_VADDR            (0xb80067ec)
#define  AUDIO_AVC2_CONTROL_2_CH45_VADDR            (0xb80067f0)
#define  AUDIO_AVC2_CONTROL_3_CH45_VADDR            (0xb80067f4)
#define  AUDIO_AVC2_CONTROL_4_CH45_VADDR            (0xb80067f8)
#define  AUDIO_AVC2_CONTROL_1_CH67_VADDR            (0xb80067fc)
#define  AUDIO_AVC2_CONTROL_2_CH67_VADDR            (0xb8006800)
#define  AUDIO_AVC2_CONTROL_3_CH67_VADDR            (0xb8006804)
#define  AUDIO_AVC2_CONTROL_4_CH67_VADDR            (0xb8006808)
#define  AUDIO_HW_OUT_TRANS_VADDR                   (0xb800680c)
#define  AUDIO_SYSTEM_INT_EN_VADDR                  (0xb8006810)
#define  AUDIO_AVC_LP_OUT_CONTROL_VADDR             (0xb8006814)
#define  AUDIO_DUMMY_6718_VADDR                     (0xb8006818)
#define  AUDIO_DUMMY_671C_VADDR                     (0xb800681c)
#define  AUDIO_HW_IN_PRE_SCALE_VADDR                (0xb8006830)
#define  AUDIO_HW_DISTORTION_CONTROL_0_VADDR        (0xb8006834)
#define  AUDIO_HW_DISTORTION_CONTROL_1_VADDR        (0xb8006838)
#define  AUDIO_LRRR_DIGITAL_VOLUME_CONTROL_0_VADDR  (0xb8006900)
#define  AUDIO_LRRR_DIGITAL_VOLUME_CONTROL_1_VADDR  (0xb8006904)
#define  AUDIO_LRRR_DIGITAL_VOLUME_CONTROL_2_VADDR  (0xb8006908)
#define  AUDIO_TS_DS_MBIST_RECODING_VADDR           (0xb800690c)
#define  AUDIO_DVOL_CONTROL_VADDR                   (0xb8006910)
#define  AUDIO_AUTO_VOLUME_CONTROL_TS_0_VADDR       (0xb8006914)
#define  AUDIO_AUTO_VOLUME_CONTROL_TS_1_VADDR       (0xb8006918)
#define  AUDIO_AUTO_VOLUME_CONTROL_TS_2_VADDR       (0xb800691c)
#define  AUDIO_AUTO_VOLUME_CONTROL_TS_3_VADDR       (0xb8006920)
#define  AUDIO_TEST_PATTERN_GEN_VADDR               (0xb8006a00)
#define  AUDIO_CRC_HEADER_VADDR                     (0xb8006a04)
#define  AUDIO_CRC_CONTORL_VADDR                    (0xb8006a08)
#define  AUDIO_CRC_STATUS_VADDR                     (0xb8006a0c)
#define  AUDIO_SINE_AUTO_CHK_VADDR                  (0xb8006a10)
#define  AUDIO_SINE_WAVE_VALUE_VADDR                (0xb8006a14)
#define  AUDIO_PATTERN_GEN_DUMMY_VADDR              (0xb8006a18)
#define  AUDIO_RBUS_ACK_CTRL_VADDR                  (0xb8006a50)
#define  AUDIO_ACK_FAIL_INFO_VADDR                  (0xb8006a54)
#define  AUDIO_AIO_O_HDMI_GCTL_VADDR                (0xb8006d00)
#define  AUDIO_AIO_O_HDMI_FCNT_VADDR                (0xb8006d04)
#define  AUDIO_AIO_O_HDMI_CS1_VADDR                 (0xb8006d08)
#define  AUDIO_AIO_O_HDMI_CS2_VADDR                 (0xb8006d0c)
#define  AUDIO_AIO_O_HDMI_INFO_VADDR                (0xb8006d10)
#define  AUDIO_AIO_O_FIFOCTL_VADDR                  (0xb8006d14)
#define  AUDIO_AIO_O_FIFO_STATUS_VADDR              (0xb8006d18)
#define  AUDIO_AIO_O_SA_0_VADDR                     (0xb8006d1c)
#define  AUDIO_AIO_O_SA_1_VADDR                     (0xb8006d20)
#define  AUDIO_AIO_O_SA_2_VADDR                     (0xb8006d24)
#define  AUDIO_AIO_O_SA_3_VADDR                     (0xb8006d28)
#define  AUDIO_AIO_O_SA_4_VADDR                     (0xb8006d2c)
#define  AUDIO_AIO_O_SA_5_VADDR                     (0xb8006d30)
#define  AUDIO_AIO_O_SA_6_VADDR                     (0xb8006d34)
#define  AUDIO_AIO_O_SA_7_VADDR                     (0xb8006d38)
#define  AUDIO_AIO_O_EA_0_VADDR                     (0xb8006d3c)
#define  AUDIO_AIO_O_EA_1_VADDR                     (0xb8006d40)
#define  AUDIO_AIO_O_EA_2_VADDR                     (0xb8006d44)
#define  AUDIO_AIO_O_EA_3_VADDR                     (0xb8006d48)
#define  AUDIO_AIO_O_EA_4_VADDR                     (0xb8006d4c)
#define  AUDIO_AIO_O_EA_5_VADDR                     (0xb8006d50)
#define  AUDIO_AIO_O_EA_6_VADDR                     (0xb8006d54)
#define  AUDIO_AIO_O_EA_7_VADDR                     (0xb8006d58)
#define  AUDIO_AIO_O_RP_0_VADDR                     (0xb8006d5c)
#define  AUDIO_AIO_O_RP_1_VADDR                     (0xb8006d60)
#define  AUDIO_AIO_O_RP_2_VADDR                     (0xb8006d64)
#define  AUDIO_AIO_O_RP_3_VADDR                     (0xb8006d68)
#define  AUDIO_AIO_O_RP_4_VADDR                     (0xb8006d6c)
#define  AUDIO_AIO_O_RP_5_VADDR                     (0xb8006d70)
#define  AUDIO_AIO_O_RP_6_VADDR                     (0xb8006d74)
#define  AUDIO_AIO_O_RP_7_VADDR                     (0xb8006d78)
#define  AUDIO_AIO_O_WP_0_VADDR                     (0xb8006d7c)
#define  AUDIO_AIO_O_WP_1_VADDR                     (0xb8006d80)
#define  AUDIO_AIO_O_WP_2_VADDR                     (0xb8006d84)
#define  AUDIO_AIO_O_WP_3_VADDR                     (0xb8006d88)
#define  AUDIO_AIO_O_WP_4_VADDR                     (0xb8006d8c)
#define  AUDIO_AIO_O_WP_5_VADDR                     (0xb8006d90)
#define  AUDIO_AIO_O_WP_6_VADDR                     (0xb8006d94)
#define  AUDIO_AIO_O_WP_7_VADDR                     (0xb8006d98)
#define  AUDIO_AIO_O_GO_VADDR                       (0xb8006d9c)
#define  AUDIO_AIO_O_PAUSE_VADDR                    (0xb8006da0)
#define  AUDIO_AIO_O_HDMI_DDRTHD_VADDR              (0xb8006da4)
#define  AUDIO_AIO_O_HDMI_TIMCNT_VADDR              (0xb8006da8)
#define  AUDIO_AIO_O_HDMI_TIMTHD_VADDR              (0xb8006dac)
#define  AUDIO_AIO_GATING_EN_VADDR                  (0xb8006db0)
#define  AUDIO_AIO_O_INTE_VADDR                     (0xb8006db4)
#define  AUDIO_AIO_O_INTS_VADDR                     (0xb8006db8)
#define  AUDIO_AIO_HDMI_OUT_SOURCE_SEL_VADDR        (0xb8006dbc)
#define  AUDIO_AUDIO_BIST_MODE_VADDR                (0xb8006c00)
#define  AUDIO_AUDIO_BIST_DONE_VADDR                (0xb8006c04)
#define  AUDIO_AUDIO_BIST_FAIL_GROUP_VADDR          (0xb8006c08)
#define  AUDIO_AUDIO_BIST_A2_EIAJ_FAIL_VADDR        (0xb8006c0c)
#define  AUDIO_AUDIO_DRF_MODE_VADDR                 (0xb8006c10)
#define  AUDIO_AUDIO_DRF_RESUME_VADDR               (0xb8006c14)
#define  AUDIO_AUDIO_DRF_DONE_VADDR                 (0xb8006c18)
#define  AUDIO_AUDIO_DRF_PAUSE_VADDR                (0xb8006c1c)
#define  AUDIO_AUDIO_DRF_FAIL_GROUP_VADDR           (0xb8006c20)
#define  AUDIO_AUDIO_DRF_A2_EIAJ_FAIL_VADDR         (0xb8006c24)
#define  AUDIO_AD_ASRC_IP_VADDR                     (0xb8006b00)
#define  AUDIO_DA0_ASRC_IP_VADDR                    (0xb8006b04)
#define  AUDIO_DA1_ASRC_IP_VADDR                    (0xb8006b08)
#define  AUDIO_DAC0_1_SRC_SEL_VADDR                 (0xb8006b10)
#define  AUDIO_ANALOG_OUT_COPY_SWAP_VADDR           (0xb8006b14)
#define  AUDIO_ANALOG_FRONTEND_MUTE_VADDR           (0xb8006b18)
#define  AUDIO_ANALOG_AIO_HPOUT_LINEOUT_L_VADDR     (0xb8006b1c)
#define  AUDIO_ANALOG_AIO_HPOUT_LINEOUT_R_VADDR     (0xb8006b20)
#define  AUDIO_ADC_VOLUME_GAIN_CONTROL_VADDR        (0xb8006b24)
#define  AUDIO_ANALOG_POWER_VADDR                   (0xb8006b28)
#define  AUDIO_ANALOG_PGA_VADDR                     (0xb8006b2c)
#define  AUDIO_ANALOG_CI01_VADDR                    (0xb8006b30)
#define  AUDIO_ANALOG_CI02_VADDR                    (0xb8006b34)
#define  AUDIO_ANALOG_DUMMY2_VADDR                  (0xb8006b38)
#define  AUDIO_ANALOG_DEPOP1_VADDR                  (0xb8006b3c)
#define  AUDIO_ANALOG_DEPOP2_VADDR                  (0xb8006b40)
#define  AUDIO_ANALOG_POST_GAIN_VADDR               (0xb8006b44)
#define  AUDIO_DRF_BIST_VADDR                       (0xb8006b48)
#define  AUDIO_AMIC1_VADDR                          (0xb8006b4c)
#define  AUDIO_ANALOG_CAPLESS_LINEOUT_DEPOP_VADDR   (0xb8006b50)
#define  AUDIO_ANALOG_CAPLESS_LINEOUT_CONTROL_VADDR (0xb8006b54)

#define AUDIO_SYS_PLL_AUD1_VADDR                    (0xb8000260)
#define AUDIO_SYS_PLL_AUD3_VADDR                    (0xb8000264)
#define AUDIO_SYS_PLL_PSAUD1_VADDR                  (0xb8000280)
#define AUDIO_SYS_PLL_PSAUD2_VADDR                  (0xb8000284)
#define AUDIO_SYS_PLL_512FS1_VADDR                  (0xb8000200)
#define AUDIO_SYS_PLL_512FS2_VADDR                  (0xb8000204)
#define VDAC_VADDR                                  (0xb8033004)	// TVSB1_Analog.doc



#ifndef LITTLE_ENDIAN //apply BIG_ENDIAN

//======SIRIUS_DESIGNSPEC_AUDIO register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  inv_ad_128fs:1;
        RBus_UInt32  inv_ad_256fs:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  div_pre_512fs_ts:2;
        RBus_UInt32  sel_clk_spdif_out:1;
        RBus_UInt32  sel_clk_i2s_out:1;
        RBus_UInt32  div_dma_r_512fs:2;
        RBus_UInt32  div_tsdma_r_512fs:2;
        RBus_UInt32  tcon0_div_fs:2;
        RBus_UInt32  tcon1_div_fs:2;
        RBus_UInt32  res2:12;
        RBus_UInt32  sel_clk_dac0_out:1;
        RBus_UInt32  sel_clk_dac1_out:1;
        RBus_UInt32  res3:2;
    };
}global_ctrl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adc_sram_on:1;
        RBus_UInt32  dac_sram_on:1;
        RBus_UInt32  am_sram_on:1;
        RBus_UInt32  a2_eiaj_sram_on:1;
        RBus_UInt32  inv_da_128fs:1;
        RBus_UInt32  inv_da_128fs_ts:1;
        RBus_UInt32  src_da_128fs:1;
        RBus_UInt32  src_da_128fs_ts:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  sif_adc_clk_sel:2;
        RBus_UInt32  sif_adc_clk_en:1;
        RBus_UInt32  sel_i2s_spdif:1;
        RBus_UInt32  sel_i2s_hdmi:2;
        RBus_UInt32  spdif_nicam:1;
        RBus_UInt32  adc_512fs_sel_ts:2;
        RBus_UInt32  sel_ts_ck_source:2;
        RBus_UInt32  back_end_ts_sample_rate:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  adc_512fs_sel:2;
        RBus_UInt32  sel_play_ck_source:2;
        RBus_UInt32  back_end_play_sample_rate:2;
        RBus_UInt32  res3:2;
    };
}global_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  asrcin0_fsi_rate_manual:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_tcon0_rst_n:1;
        RBus_UInt32  asrcin0_ftk_loop_filter_mode:1;
        RBus_UInt32  asrcin0_ftk_loop_gain_sel:1;
        RBus_UInt32  tcon0_fsi_sel:2;
        RBus_UInt32  asrcin0_ftk_sdm_ini:22;
    };
}tcon0_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  asrcin1_fsi_rate_manual:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  reg_tcon1_rst_n:1;
        RBus_UInt32  asrcin1_ftk_loop_filter_mode:1;
        RBus_UInt32  asrcin1_ftk_loop_gain_sel:1;
        RBus_UInt32  tcon1_fsi_sel:2;
        RBus_UInt32  asrcin1_ftk_sdm_ini:22;
    };
}tcon1_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  contword_inv:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  div_2fs:2;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_para_e:3;
        RBus_UInt32  res3:2;
        RBus_UInt32  ps_testmode:1;
        RBus_UInt32  ps_contword:5;
        RBus_UInt32  pll_spdif_dtrack_en:1;
        RBus_UInt32  reg_smooth_en:1;
        RBus_UInt32  pll_spdif_auto_mode:1;
        RBus_UInt32  mod_acc_rst:1;
        RBus_UInt32  reg_para_d:4;
        RBus_UInt32  res4:2;
        RBus_UInt32  reg_para_a:6;
    };
}pllcg_spdif_gain_cr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  p_gain_set:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  p_gain_set2:10;
    };
}pllcg_spdif_gain_cr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  i_gain_set:10;
    };
}pllcg_spdif_gain_cr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:25;
        RBus_UInt32  reach_time_num:3;
        RBus_UInt32  max_correct_range:4;
    };
}pllcg_spdif_number_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  high_bound1:8;
        RBus_UInt32  low_bound1:8;
        RBus_UInt32  high_bound2:8;
        RBus_UInt32  low_bound2:8;
    };
}pllcg_spdif_bound_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006024_31_16:16;
        RBus_UInt32  res1:13;
        RBus_UInt32  wdog_switch_en:1;
        RBus_UInt32  freq_sel:2;
    };
}global_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  aio_o_raw2_fs:4;
        RBus_UInt32  aio_o_raw2_clken:1;
    };
}ao_hdmi_fs_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  int_nicam_true_detect_en:1;
        RBus_UInt32  int_fifo0_ts_full_en:1;
        RBus_UInt32  int_fifo0_ts_empty_en:1;
        RBus_UInt32  int_pll64512_wd_en:1;
        RBus_UInt32  int_msd_decision_done_en:1;
        RBus_UInt32  int_msd_fw_scan_done_en:1;
        RBus_UInt32  int_rbus_timeout_en:1;
        RBus_UInt32  int_btsc_mode_chg_en:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  int_fifo0_full_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  int_fifo0_empty_en:1;
        RBus_UInt32  int_nicam_level_status_en:1;
        RBus_UInt32  int_ain_timer_en:1;
        RBus_UInt32  int_aout_timer_en:1;
        RBus_UInt32  int_spi_in_datatype_change_en:1;
        RBus_UInt32  int_spi_in_lock_change_en:1;
        RBus_UInt32  int_nicam_hierr_change_en:1;
        RBus_UInt32  int_i2s_pri_sample_rate_chg_en:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  int_spi_sample_rate_chg_en:1;
        RBus_UInt32  int_i2s_pri_word_length_change_en:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  int_sif_nopt_en:1;
        RBus_UInt32  int_msd_change_en:1;
        RBus_UInt32  int_msd_timeout_en:1;
        RBus_UInt32  int_mode_det_status_change_en:1;
        RBus_UInt32  int_sif_ovf_en:1;
    };
}interrupt_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  int_nicam_true_detect:1;
        RBus_UInt32  int_fifo0_ts_full:1;
        RBus_UInt32  int_fifo0_ts_empty:1;
        RBus_UInt32  int_pll64512_wd:1;
        RBus_UInt32  int_msd_decision_done:1;
        RBus_UInt32  int_msd_fw_scan_done:1;
        RBus_UInt32  int_rbus_timeout:1;
        RBus_UInt32  int_btsc_mode_chg:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  int_fifo0_full:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  int_fifo0_empty:1;
        RBus_UInt32  int_nicam_level_status:1;
        RBus_UInt32  int_ain_timer:1;
        RBus_UInt32  int_aout_timer:1;
        RBus_UInt32  int_spi_in_datatype_change:1;
        RBus_UInt32  int_spi_in_lock_change:1;
        RBus_UInt32  int_nicam_hierr_change:1;
        RBus_UInt32  int_i2s_pri_sample_rate_chg:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  int_spi_sample_rate_chg:1;
        RBus_UInt32  int_i2s_pri_word_length_change:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  int_sif_nopt:1;
        RBus_UInt32  int_msd_change:1;
        RBus_UInt32  int_msd_timeout:1;
        RBus_UInt32  int_mode_det_status_change:1;
        RBus_UInt32  int_sif_ovf:1;
    };
}interrupt_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  ain_timer_en:1;
        RBus_UInt32  aout_timer_en:1;
    };
}aio_timer_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ain_timer:32;
    };
}ain_counter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ain_compare:32;
    };
}ain_compare_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aout_timer:32;
    };
}aout_counter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aout_compare:32;
    };
}aout_compare_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_0:32;
    };
}sw_dbg_reg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_1:32;
    };
}sw_dbg_reg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_2:32;
    };
}sw_dbg_reg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_3:32;
    };
}sw_dbg_reg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  source_sel:2;
        RBus_UInt32  left_right:2;
        RBus_UInt32  mode_sel:1;
        RBus_UInt32  debounce_en:1;
        RBus_UInt32  sclk_inv:1;
        RBus_UInt32  dummy18006100_24_16:9;
        RBus_UInt32  res1:4;
        RBus_UInt32  sampling_rate:4;
        RBus_UInt32  res2:1;
        RBus_UInt32  pcm_width:7;
    };
}i2s_in_primary_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  source_sel:2;
        RBus_UInt32  req_after_lock:1;
        RBus_UInt32  debounce_en:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  dummy18006130_15_5:11;
        RBus_UInt32  spdif_in_2fs_sel:1;
        RBus_UInt32  sampling_rate:4;
    };
}spdif_in_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hw_locked:1;
        RBus_UInt32  invalid_bit:1;
        RBus_UInt32  clock_accuracy_r:2;
        RBus_UInt32  sampling_freq_r:4;
        RBus_UInt32  channel_number_r:4;
        RBus_UInt32  source_number_r:4;
        RBus_UInt32  category_code_r:8;
        RBus_UInt32  mode_r:2;
        RBus_UInt32  pre_emphasis:3;
        RBus_UInt32  copyright:1;
        RBus_UInt32  data_type:1;
        RBus_UInt32  professional:1;
    };
}spdif_in_cs_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  cgms_a_l:2;
        RBus_UInt32  cgms_a_r:2;
        RBus_UInt32  original_sampling_freq_r:4;
        RBus_UInt32  word_length_r:4;
    };
}spdif_in_cs_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  original_sampling_freq_l:4;
        RBus_UInt32  word_length_l:4;
        RBus_UInt32  clock_accuracy_l:2;
        RBus_UInt32  sampling_freq_l:4;
        RBus_UInt32  channel_number_l:4;
        RBus_UInt32  source_number_l:4;
        RBus_UInt32  category_code_l:8;
        RBus_UInt32  mode_l:2;
    };
}spdif_in_cs_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  output_sel:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  mclk_sel:2;
        RBus_UInt32  res3:6;
        RBus_UInt32  wclk_inv:1;
        RBus_UInt32  sclk_inv:1;
        RBus_UInt32  dummy18006150_15_0:16;
    };
}i2s_out_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  pcm_source_sel_ch01:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  pcm_source_sel_ch23:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  hw_limit_en_ch23:1;
        RBus_UInt32  hw_limit_ch23:7;
        RBus_UInt32  swap_sel_ch01:2;
        RBus_UInt32  res4:6;
        RBus_UInt32  hw_limit_en_ch01:1;
        RBus_UInt32  hw_limit_ch01:7;
    };
}i2s_out_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  output_sel:2;
        RBus_UInt32  wait_en:1;
        RBus_UInt32  validity_ctrl:1;
        RBus_UInt32  spdif_out_null_burst:1;
        RBus_UInt32  pcm_source_sel:4;
        RBus_UInt32  res1:5;
        RBus_UInt32  swap_sel:2;
        RBus_UInt32  dummy18006170_15_0:16;
    };
}spdif_out_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  hw_limit_en:1;
        RBus_UInt32  hw_limit:7;
    };
}spdif_out_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  clock_accuracy:2;
        RBus_UInt32  sampling_freq:4;
        RBus_UInt32  channel_number:4;
        RBus_UInt32  source_number:4;
        RBus_UInt32  category_code:8;
        RBus_UInt32  mode:2;
        RBus_UInt32  pre_emphasis:3;
        RBus_UInt32  copyright:1;
        RBus_UInt32  data_type:1;
        RBus_UInt32  professional:1;
    };
}spdif_out_cs_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  cgms_a:2;
        RBus_UInt32  original_sampling_freq:4;
        RBus_UInt32  word_length:4;
    };
}spdif_out_cs_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  dummy18006180_19_17:3;
        RBus_UInt32  hw_agc_en:1;
        RBus_UInt32  ob_time:16;
    };
}sif_agc_eval_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  non_opt_cnt_th:3;
        RBus_UInt32  non_opt_cnt_under:8;
        RBus_UInt32  non_opt_cnt_ovf:8;
    };
}sif_agc_optimal_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  ovf_th:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  opt_th:10;
    };
}sif_agc_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  ovf:1;
        RBus_UInt32  opt:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  abs_peak:10;
    };
}sif_agc_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  agc2_debounce_cnt:3;
        RBus_UInt32  agc2_stepsize:2;
        RBus_UInt32  agc2_gain_a:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  agc2_gain_b:6;
        RBus_UInt32  agc2_obtime:16;
    };
}sif_agc2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc2_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  agc2_overflow:1;
        RBus_UInt32  agc2_underflow:1;
        RBus_UInt32  res2:18;
        RBus_UInt32  agc2_sif_mag:10;
    };
}sif_agc2_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  pdetect_enable:1;
        RBus_UInt32  detect_source_sel:4;
    };
}peak_contorl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  opt_th_l:16;
        RBus_UInt32  ovf_th_l:16;
    };
}peak_contorl_l_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy180061b4_31_19:13;
        RBus_UInt32  nonopt_cnt_tr_l:3;
        RBus_UInt32  res1:2;
        RBus_UInt32  vpp_eval_cnt_l:14;
    };
}peak_control_l_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  optimize_l_irq_en:1;
        RBus_UInt32  overflow_l_irq_en:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  optimize_l:1;
        RBus_UInt32  overflow_l:1;
        RBus_UInt32  pk_adj_l:6;
        RBus_UInt32  magnitude_l:16;
    };
}peak_status_l_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  toggle_cnt:8;
        RBus_UInt32  pcm_l_monitor:24;
    };
}peak_status_l_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  opt_th_r:16;
        RBus_UInt32  ovf_th_r:16;
    };
}peak_contorl_r_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy180061c4_31_19:13;
        RBus_UInt32  nonopt_cnt_tr_r:3;
        RBus_UInt32  res1:2;
        RBus_UInt32  vpp_eval_cnt_r:14;
    };
}peak_contorl_r_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  optimize_r_irq_en:1;
        RBus_UInt32  overflow_r_irq_en:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  optimize_r:1;
        RBus_UInt32  overflow_r:1;
        RBus_UInt32  pk_adj_r:6;
        RBus_UInt32  magnitude_r:16;
    };
}peak_status_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  pcm_r_monitor:24;
    };
}peak_status_r_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  post_detect_enable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  post_detect_source_sel:3;
    };
}post_peak_contorl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_opt_th_l:16;
        RBus_UInt32  post_ovf_th_l:16;
    };
}post_peak_contorl_l_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  post_nonopt_cnt_tr_l:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  post_vpp_eval_cnt_l:14;
    };
}post_peak_control_l_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_optimize_l_irq_en:1;
        RBus_UInt32  post_overflow_l_irq_en:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  post_optimize_l:1;
        RBus_UInt32  post_overflow_l:1;
        RBus_UInt32  post_pk_adj_l:6;
        RBus_UInt32  post_magnitude_l:16;
    };
}post_peak_status_l_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_toggle_cnt:8;
        RBus_UInt32  post_pcm_l_monitor:24;
    };
}post_peak_status_l_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_opt_th_r:16;
        RBus_UInt32  post_ovf_th_r:16;
    };
}post_peak_contorl_r_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  post_nonopt_cnt_tr_r:3;
        RBus_UInt32  res2:2;
        RBus_UInt32  post_vpp_eval_cnt_r:14;
    };
}post_peak_contorl_r_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_optimize_r_irq_en:1;
        RBus_UInt32  post_overflow_r_irq_en:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  post_optimize_r:1;
        RBus_UInt32  post_overflow_r:1;
        RBus_UInt32  post_pk_adj_r:6;
        RBus_UInt32  post_magnitude_r:16;
    };
}post_peak_status_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  post_pcm_r_monitor:24;
    };
}post_peak_status_r_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  msd_en:1;
        RBus_UInt32  update_en:1;
        RBus_UInt32  carrier_shift_scan_en:1;
        RBus_UInt32  carrier_phase_delta:3;
        RBus_UInt32  msd_reset_n:1;
        RBus_UInt32  msd_debounce_cnt:3;
        RBus_UInt32  reg_scan_cnt:8;
        RBus_UInt32  res2:1;
        RBus_UInt32  mn_priority:2;
        RBus_UInt32  dkl_priority:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  calc_time_sel:1;
        RBus_UInt32  sound_select:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  fw_scan_freq:3;
    };
}msd_crtl_word_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  deviation_unnormal:2;
        RBus_UInt32  case_subtomain:4;
        RBus_UInt32  res2:1;
        RBus_UInt32  flag_unnormal:1;
        RBus_UInt32  flag_subtomain:1;
        RBus_UInt32  h_dv_th_sel:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  hw_detected_std:5;
        RBus_UInt32  res4:3;
        RBus_UInt32  reg_std:5;
    };
}msd_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  bw_cnt_max:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  bw_cnt_min:5;
        RBus_UInt32  res3:4;
        RBus_UInt32  shift_value:4;
        RBus_UInt32  res4:1;
        RBus_UInt32  main_cari_idx:3;
        RBus_UInt32  deviation:4;
    };
}msd_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  main_thresh:16;
        RBus_UInt32  main_thresh_low:16;
    };
}main_tone_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  main_thresh_hd:16;
        RBus_UInt32  main_thresh_hd_low:16;
    };
}main_tone_threshold_hd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bw_dev_thresh_hd:16;
        RBus_UInt32  bw_dev_thresh:16;
    };
}bw_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bw_dev_thresh_low:16;
        RBus_UInt32  main_sub_ratio:16;
    };
}main_sub_ratio_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_4_5:16;
    };
}msd_mag_4_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_4_28:16;
    };
}msd_mag_4_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_4_72:16;
    };
}msd_mag_4_72_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_5_5:16;
    };
}msd_mag_5_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_5_25:16;
    };
}msd_mag_5_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_5_74:16;
    };
}msd_mag_5_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_5_85:16;
    };
}msd_carrier_5_85_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_5_95:16;
    };
}msd_carrier_5_95_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_6:16;
    };
}msd_mag_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_6_25:16;
    };
}msd_mag_6_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_6_5:16;
    };
}msd_carrier_6_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_6_552:16;
    };
}msd_mag_6_552_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  reg_mag_6_74:16;
    };
}msd_carrier_6_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  flag_fw_4:1;
        RBus_UInt32  flag_fw_3:1;
        RBus_UInt32  flag_fw_2:1;
        RBus_UInt32  flag_fw_1:1;
        RBus_UInt32  flag_fw:1;
        RBus_UInt32  flag_4_5:1;
        RBus_UInt32  flag_5_5:1;
        RBus_UInt32  flag_6:1;
        RBus_UInt32  flag_6_5:1;
        RBus_UInt32  flag_4_72:1;
        RBus_UInt32  flag_5_74:1;
        RBus_UInt32  flag_5_85:1;
        RBus_UInt32  flag_6_25:1;
        RBus_UInt32  flag_6_552:1;
        RBus_UInt32  flag_6_74:1;
    };
}msd_flags_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  fw_phase_delta:14;
        RBus_UInt32  reg_mag_fw:16;
    };
}msd_programmable_freq_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh:16;
        RBus_UInt32  fw_thresh_low:16;
    };
}threshold_msd_carrier_fw_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  fw_phase_delta_1:14;
        RBus_UInt32  reg_mag_fw_1:16;
    };
}msd_programmable_freq_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_1:16;
        RBus_UInt32  fw_thresh_1_low:16;
    };
}threshold_msd_carrier_fw_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  fw_phase_delta_2:14;
        RBus_UInt32  reg_mag_fw_2:16;
    };
}msd_programmable_freq_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_2:16;
        RBus_UInt32  fw_thresh_2_low:16;
    };
}threshold_msd_carrier_fw_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  fw_phase_delta_3:14;
        RBus_UInt32  reg_mag_fw_3:16;
    };
}msd_programmable_freq_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_3:16;
        RBus_UInt32  fw_thresh_3_low:16;
    };
}threshold_msd_carrier_fw_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  fw_phase_delta_4:14;
        RBus_UInt32  reg_mag_fw_4:16;
    };
}msd_programmable_freq_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_4:16;
        RBus_UInt32  fw_thresh_4_low:16;
    };
}threshold_msd_carrier_fw_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  reg_cari_sft_detect_en:1;
        RBus_UInt32  reg_bw_detect_en:1;
        RBus_UInt32  mono_std_sel:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  second_reg_std:5;
    };
}msd_second_reg_std_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sec_thresh:16;
        RBus_UInt32  sec_thresh_low:16;
    };
}second_main_tone_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rm_0:4;
    };
}msd_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_45_fix:16;
        RBus_UInt32  reg_mag_55_fix:16;
    };
}msd_main_mag_ori1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_60_fix:16;
        RBus_UInt32  reg_mag_65_fix:16;
    };
}msd_main_mag_ori2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  msd_gain_en:1;
        RBus_UInt32  msd_gain_result:4;
    };
}msd_gain_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_update_count:16;
        RBus_UInt32  msd_update_count:16;
    };
}msd_update_count_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  md_update_count:16;
        RBus_UInt32  res1:13;
        RBus_UInt32  hw_mode_en:1;
        RBus_UInt32  mode_result:2;
    };
}mode_detect_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  enable:1;
        RBus_UInt32  lpf_coef_sel:2;
        RBus_UInt32  bpf_sel:1;
        RBus_UInt32  high_threshold:2;
        RBus_UInt32  low_threshold:2;
        RBus_UInt32  lpf_coef_sel_lock:2;
        RBus_UInt32  res1:3;
        RBus_UInt32  debounce_time:3;
        RBus_UInt32  max_threshold:16;
    };
}md_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_other:16;
        RBus_UInt32  dummy18006314_15_8:8;
        RBus_UInt32  gain_result:4;
        RBus_UInt32  res1:2;
        RBus_UInt32  mode_result:2;
    };
}md_status_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_stereo:16;
        RBus_UInt32  max_dual:16;
    };
}md_status_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sif_data_source:1;
        RBus_UInt32  res1:29;
        RBus_UInt32  force_nicam_en:1;
        RBus_UInt32  carrier_freq_correct_en:1;
    };
}carrier_freq_deviation_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  main_phase_delta:14;
        RBus_UInt32  res2:2;
        RBus_UInt32  sub_phase_delta:14;
    };
}carrier_phase_delta_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fm_magnitude:16;
        RBus_UInt32  dummy18006358_15_0:16;
    };
}a2_eiaj_dc_filter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  dummy18006360_7_4:4;
        RBus_UInt32  am_bpf_bw:1;
        RBus_UInt32  am_path_sel:1;
        RBus_UInt32  hw_am_prescale:2;
    };
}am_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rm_0:4;
    };
}bist_am_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage1_b0:16;
        RBus_UInt32  sap_bpf_stage1_b1:16;
    };
}sap_bpf_stage1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  sap_bpf_stage1_b2:16;
    };
}sap_bpf_stage1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage1_a1:16;
        RBus_UInt32  sap_bpf_stage1_a2:16;
    };
}sap_bpf_stage1_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage2_b0:16;
        RBus_UInt32  sap_bpf_stage2_b1:16;
    };
}sap_bpf_stage2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  sap_bpf_stage2_b2:16;
    };
}sap_bpf_stage2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage2_a1:16;
        RBus_UInt32  sap_bpf_stage2_a2:16;
    };
}sap_bpf_stage2_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage3_b0:16;
        RBus_UInt32  sap_bpf_stage3_b1:16;
    };
}sap_bpf_stage3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  sap_bpf_stage3_b2:16;
    };
}sap_bpf_stage3_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage3_a1:16;
        RBus_UInt32  sap_bpf_stage3_a2:16;
    };
}sap_bpf_stage3_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lock_reference:1;
        RBus_UInt32  res1:5;
        RBus_UInt32  pilot_hithresh:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  pilot_lothresh:10;
    };
}btsc_pilot_thres_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:13;
        RBus_UInt32  pilot_lock_reset:1;
        RBus_UInt32  out_hpf_en:1;
        RBus_UInt32  w1pilotpresent:1;
        RBus_UInt32  w1pilotlocked:1;
        RBus_UInt32  pilot_level_pass:1;
        RBus_UInt32  pilot_hi_pass:1;
        RBus_UInt32  pilot_lo_refuse:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  w10pilotmagnitude:10;
    };
}btsc_pilot_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  sap_hithresh:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  sap_lothresh:10;
    };
}btsc_sap_thresh_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  sap_noise_hi_thresh:10;
        RBus_UInt32  res2:6;
        RBus_UInt32  sap_noise_lo_thresh:10;
    };
}btsc_sap_noise_th_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  w10sapnoise:10;
    };
}btsc_sap_noise_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  w1sapqualitygood:1;
        RBus_UInt32  sap_hi_pass:1;
        RBus_UInt32  sap_lo_refuse:1;
        RBus_UInt32  sap_noise_flag:1;
        RBus_UInt32  sap_normalize_en:1;
        RBus_UInt32  w10sapmagnitude:10;
    };
}btsc_sap_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  sap_debounce_en:1;
        RBus_UInt32  sap_debounce:4;
    };
}btsc_sap_debounce_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  fm_mag_overflow:1;
        RBus_UInt32  fm_mag_optimize:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  w10fmmagnitude:10;
    };
}btsc_sif_fm_magnitude_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  testoutputselect:4;
    };
}btsc_test_mux_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  dummy_6424:16;
    };
}btsc_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pilot_phase_delta:32;
    };
}btsc_pilot_phase_delta_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  unlock_p_gain:4;
        RBus_UInt32  unlock_i_gain:4;
        RBus_UInt32  locked_p_gain:4;
        RBus_UInt32  locked_i_gain:4;
    };
}phase_error_pi_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_hpf_en:1;
        RBus_UInt32  res1:7;
        RBus_UInt32  phase_err_threshold:24;
    };
}phase_err_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  phase_err_high_threshold:24;
    };
}phase_err_threshold2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:10;
        RBus_UInt32  freq_correction:22;
    };
}freq_correction_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  average_movement:24;
    };
}phase_error_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  a2_bw_sel:2;
        RBus_UInt32  de_emphasis_time:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  ultra_hdv_mode:1;
        RBus_UInt32  normalize_en:1;
        RBus_UInt32  hdv_bpf_sel:2;
        RBus_UInt32  res2:12;
        RBus_UInt32  fm1_deviation_gain:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  fm2_deviation_gain:3;
        RBus_UInt32  res4:4;
    };
}a2_eiaj_demod_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  magnitude_sub:10;
        RBus_UInt32  noise_sub:10;
    };
}a2_eiaj_mag_noise_sub_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  magnitude:10;
        RBus_UInt32  noise:10;
    };
}a2_eiaj_mag_noise_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_7:4;
        RBus_UInt32  rm_6:4;
        RBus_UInt32  rm_5:4;
        RBus_UInt32  rm_4:4;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_0:4;
    };
}mbist_a2_eiaj_demod_rm_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  rm_8:4;
    };
}mbist_a2_eiaj_demod_rm_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  rme_8:1;
        RBus_UInt32  rme_7:1;
        RBus_UInt32  rme_6:1;
        RBus_UInt32  rme_5:1;
        RBus_UInt32  rme_4:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_0:1;
    };
}mbist_a2_eiaj_demod_rme_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  psf_sel:1;
        RBus_UInt32  tr_lpf_kp:3;
        RBus_UInt32  psf_bg_sel:1;
        RBus_UInt32  cr_lpf_kp:3;
        RBus_UInt32  res1:2;
        RBus_UInt32  cr_lpf_ki:2;
        RBus_UInt32  tr_timing_step:20;
    };
}nicam_demod_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  enable:1;
        RBus_UInt32  debounce_cnt:3;
        RBus_UInt32  res1:2;
        RBus_UInt32  window_size:10;
        RBus_UInt32  res2:10;
        RBus_UInt32  gain_adjust:6;
    };
}nicam_dagc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  high:16;
        RBus_UInt32  low:16;
    };
}nicam_dagc_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  magnitude:16;
    };
}nicam_dagc_mag_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  resample_en:1;
        RBus_UInt32  data_channel_sel:1;
        RBus_UInt32  pcm_l_out_sel:1;
        RBus_UInt32  pcm_r_out_sel:1;
        RBus_UInt32  cib_1:1;
        RBus_UInt32  cib_0:1;
        RBus_UInt32  cib_mask:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  status_debounce_cnt:4;
        RBus_UInt32  bypass_interpol:1;
        RBus_UInt32  sat_en:1;
        RBus_UInt32  de_em_by_pass:1;
        RBus_UInt32  level_sel:2;
        RBus_UInt32  dummy18006510_14_0:15;
    };
}nicam_decode_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  c0:1;
        RBus_UInt32  c1c2c3:3;
        RBus_UInt32  c4:1;
        RBus_UInt32  additional_data:11;
        RBus_UInt32  res1:2;
        RBus_UInt32  bit_cnt_sync:1;
        RBus_UInt32  true_detect:1;
        RBus_UInt32  bit_error_rate:12;
    };
}nicam_decode_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  enable:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  c4_hi_ber:2;
        RBus_UInt32  analog_flag:1;
        RBus_UInt32  hi_ber_debounce:3;
        RBus_UInt32  high_threshold:12;
        RBus_UInt32  low_threshold:12;
    };
}nicam_auto_switch_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  enable:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  duration:2;
        RBus_UInt32  res2:5;
        RBus_UInt32  ted_error_threshold:3;
        RBus_UInt32  res3:2;
        RBus_UInt32  ted_error:18;
    };
}nicam_demod_auto_recovery_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  bit_error_rate_l:12;
        RBus_UInt32  bit_error_rate_r:12;
    };
}nicam_bit_error_rate_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  window_en:1;
        RBus_UInt32  l_start:6;
        RBus_UInt32  l_end:6;
        RBus_UInt32  r_start:6;
        RBus_UInt32  r_end:6;
    };
}nicam_ber_window_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  fifo_ch1_source:2;
        RBus_UInt32  fifo_ch0_source:2;
        RBus_UInt32  res2:13;
        RBus_UInt32  backend_play_en:1;
        RBus_UInt32  downsample_en:1;
        RBus_UInt32  down_rate:1;
    };
}down_sample_control_for_playback_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  fifo_ch01_sel:4;
    };
}down_sample_fifo_source_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006558_31_14:18;
        RBus_UInt32  res1:14;
    };
}down_sample_mbist_recoding_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}down_sample_fifo_pre_scale_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_0:4;
    };
}down_sample_mbist_rm_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_0:1;
    };
}down_sample_mbist_rme_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  fifo_ch0_source:2;
        RBus_UInt32  fifo_ch1_source:2;
        RBus_UInt32  fifo_ch01_sel:4;
        RBus_UInt32  res2:9;
        RBus_UInt32  backend_play_en:1;
        RBus_UInt32  downsample_en:1;
        RBus_UInt32  down_rate:1;
    };
}down_sample_control_for_ts_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy180065a4_31_16:16;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_0:4;
    };
}ts_ds_fifo_mbist_rm_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_0:1;
    };
}ts_ds_fifo_mbist_rme_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dma_wr_src_sel:2;
        RBus_UInt32  dma_output_src_sel:2;
        RBus_UInt32  dma_w_format:1;
        RBus_UInt32  dma_r_format:1;
        RBus_UInt32  ls_on:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  output_hold_en:1;
        RBus_UInt32  pcm_random:1;
        RBus_UInt32  hbr_wr_channel_no:2;
        RBus_UInt32  wr_channel_no:3;
        RBus_UInt32  aidmatype:1;
        RBus_UInt32  rd_channel_no:3;
        RBus_UInt32  aodmatype:1;
        RBus_UInt32  dma_mode:1;
        RBus_UInt32  int_rd_en:1;
        RBus_UInt32  int_wr_en:1;
        RBus_UInt32  dma_int_en:1;
        RBus_UInt32  dma_soft_rd_rst:1;
        RBus_UInt32  dma_soft_wr_rst:1;
        RBus_UInt32  dma_read_enable:1;
        RBus_UInt32  dma_write_enable:1;
        RBus_UInt32  overflow_dma_status:1;
        RBus_UInt32  unflow_dma_status:1;
        RBus_UInt32  wr_intr_dma_status:1;
        RBus_UInt32  rd_intr_dma_status:1;
    };
}adma_csr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  write_len:15;
        RBus_UInt32  res2:1;
        RBus_UInt32  wr_intr_point:15;
    };
}adma_wconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wr_start_addr0:26;
        RBus_UInt32  res1:6;
    };
}adma_wsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wr_start_addr1:26;
        RBus_UInt32  res1:6;
    };
}adma_wsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  read_len:15;
        RBus_UInt32  res2:1;
        RBus_UInt32  read_intr_point:15;
    };
}adma_rconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  load_wr:1;
        RBus_UInt32  avail_length:15;
        RBus_UInt32  load_rd:1;
        RBus_UInt32  read_length:15;
    };
}adma_wrconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rd_start_addr0:26;
        RBus_UInt32  res1:6;
    };
}adma_rsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rd_start_addr1:26;
        RBus_UInt32  res1:6;
    };
}adma_rsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rd_start_addr2:26;
        RBus_UInt32  res1:6;
    };
}adma_rsadr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rd_start_addr3:26;
        RBus_UInt32  res1:6;
    };
}adma_rsadr3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  wr_buffer_length:15;
        RBus_UInt32  res2:1;
        RBus_UInt32  rd_buffer_length:15;
    };
}adma_chconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rm_0:4;
    };
}audio_dma_bist_control_indicate_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_dma_wr_src_sel:2;
        RBus_UInt32  ts_dma_output_src_sel:2;
        RBus_UInt32  ts_dma_w_format:1;
        RBus_UInt32  ts_dma_r_format:1;
        RBus_UInt32  ts_ls_on:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_output_hold_en:1;
        RBus_UInt32  ts_pcm_random:1;
        RBus_UInt32  ts_hbr_wr_channel_no:2;
        RBus_UInt32  ts_wr_channel_no:3;
        RBus_UInt32  ts_aidmatype:1;
        RBus_UInt32  ts_rd_channel_no:3;
        RBus_UInt32  ts_aodmatype:1;
        RBus_UInt32  ts_dma_mode:1;
        RBus_UInt32  ts_int_rd_en:1;
        RBus_UInt32  ts_int_wr_en:1;
        RBus_UInt32  ts_dma_int_en:1;
        RBus_UInt32  ts_dma_soft_rd_rst:1;
        RBus_UInt32  ts_dma_soft_wr_rst:1;
        RBus_UInt32  ts_dma_read_enable:1;
        RBus_UInt32  ts_dma_write_enable:1;
        RBus_UInt32  ts_overflow_dma_status:1;
        RBus_UInt32  ts_unflow_dma_status:1;
        RBus_UInt32  ts_wr_intr_dma_status:1;
        RBus_UInt32  ts_rd_intr_dma_status:1;
    };
}tsadma_csr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_write_len:15;
        RBus_UInt32  res2:1;
        RBus_UInt32  ts_wr_intr_point:15;
    };
}ts_adma_wconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_wr_start_addr0:26;
        RBus_UInt32  res1:6;
    };
}ts_adma_wsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_wr_start_addr1:26;
        RBus_UInt32  res1:6;
    };
}ts_adma_wsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_read_len:15;
        RBus_UInt32  res2:1;
        RBus_UInt32  ts_read_intr_point:15;
    };
}ts_adma_rconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_load_wr:1;
        RBus_UInt32  ts_avail_length:15;
        RBus_UInt32  ts_load_rd:1;
        RBus_UInt32  ts_read_length:15;
    };
}ts_adma_wrconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_rd_start_addr0:26;
        RBus_UInt32  res1:6;
    };
}ts_adma_rsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_rd_start_addr1:26;
        RBus_UInt32  res1:6;
    };
}ts_adma_rsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_rd_start_addr2:26;
        RBus_UInt32  res1:6;
    };
}ts_adma_rsadr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_wr_buffer_length:15;
        RBus_UInt32  res2:1;
        RBus_UInt32  ts_rd_buffer_length:15;
    };
}ts_adma_chconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  rme_0_ts:1;
        RBus_UInt32  rm_0_ts:4;
    };
}ts_dma_bist_control_indicate_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  test_dma_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  test_dma_rw_mode:1;
        RBus_UInt32  test_dma_in_sel:3;
        RBus_UInt32  test_dma_ring:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  test_dma_over_read:1;
        RBus_UInt32  test_dma_over_write:1;
    };
}test_dma_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  test_dma_start_addr:20;
        RBus_UInt32  res2:5;
    };
}test_dma_start_address_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  test_dma_stop_addr:20;
        RBus_UInt32  res2:5;
    };
}test_dma_stop_address_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy180066ec_31_2:30;
        RBus_UInt32  eco_ifd_inv:1;
        RBus_UInt32  dma_sel:1;
    };
}test_mode_select_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  test_dma_cur_addr:20;
        RBus_UInt32  res2:5;
    };
}test_cur_address_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  distortion_enable:1;
        RBus_UInt32  avc2_enable:1;
        RBus_UInt32  basic_premium_sel:1;
        RBus_UInt32  dvol_enable:1;
        RBus_UInt32  loud_enable:1;
        RBus_UInt32  deq_enable:1;
        RBus_UInt32  spatial_ctrlenable:1;
        RBus_UInt32  auto_volenable:1;
    };
}hw_process_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_vol_detect:2;
        RBus_UInt32  avc_noise_gain:2;
        RBus_UInt32  avc_noise_thre:8;
        RBus_UInt32  avc_level_max:8;
        RBus_UInt32  avc_level_min:8;
        RBus_UInt32  avc_down_db:2;
        RBus_UInt32  avc_up_db:2;
    };
}auto_volume_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_cnt_thre:8;
        RBus_UInt32  avc_zc_win:12;
        RBus_UInt32  avc_mon_win:12;
    };
}avc_volume_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_vol_amplif_enable:1;
        RBus_UInt32  avc1_coef:3;
        RBus_UInt32  avc_small_level_max:8;
        RBus_UInt32  avc_small_level_min:8;
        RBus_UInt32  avc_small_down_db:2;
        RBus_UInt32  avc_small_up_db:2;
        RBus_UInt32  avc_small_cnt_thre:8;
    };
}avc_volume_control_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  avc_small_level:16;
    };
}avc_volume_control_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  spatial_zc_win:12;
        RBus_UInt32  spatial_zc_apply:1;
        RBus_UInt32  apf_en:1;
        RBus_UInt32  psb_en:1;
        RBus_UInt32  seb_en:1;
        RBus_UInt32  spatial_in_l_sel:1;
        RBus_UInt32  spatial_in_r_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  f_coef:9;
    };
}spatial_effect_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  depth1:9;
        RBus_UInt32  res2:7;
        RBus_UInt32  depth2:9;
    };
}spatial_effect_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  eq_hp_slope:1;
        RBus_UInt32  eq_hp_a1:16;
    };
}eq_hp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_lp_a1:16;
        RBus_UInt32  eq_lp_h0:16;
    };
}eq_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp1_a1:16;
        RBus_UInt32  eq_bp1_a2:16;
    };
}eq_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  eq_bp1_h0:16;
    };
}eq_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp2_a1:16;
        RBus_UInt32  eq_bp2_a2:16;
    };
}eq_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  eq_bp2_h0:16;
    };
}eq_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp3_a1:16;
        RBus_UInt32  eq_bp3_a2:16;
    };
}eq_bp3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  eq_bp3_h0:16;
    };
}eq_bp3_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp4_a1:16;
        RBus_UInt32  eq_bp4_a2:16;
    };
}eq_bp4_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  eq_bp4_h0:16;
    };
}eq_bp4_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp5_a1:16;
        RBus_UInt32  eq_bp5_a2:16;
    };
}eq_bp5_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  eq_bp5_h0:16;
    };
}eq_bp5_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp6_a1:16;
        RBus_UInt32  eq_bp6_a2:16;
    };
}eq_bp6_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  eq_bp6_h0:16;
    };
}eq_bp6_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp7_a1:16;
        RBus_UInt32  eq_bp7_a2:16;
    };
}eq_bp7_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  eq_bp7_h0:16;
    };
}eq_bp7_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp8_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp8_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp9_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp9_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  eq_band7_enable:1;
        RBus_UInt32  eq_band6_enable:1;
        RBus_UInt32  eq_band5_enable:1;
        RBus_UInt32  eq_band4_enable:1;
        RBus_UInt32  eq_band3_enable:1;
        RBus_UInt32  eq_band2_enable:1;
        RBus_UInt32  eq_band1_enable:1;
        RBus_UInt32  eq_lp_enable:1;
        RBus_UInt32  eq_hp_enable:1;
    };
}eq_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  eq_band7_of:1;
        RBus_UInt32  eq_band6_of:1;
        RBus_UInt32  eq_band5_of:1;
        RBus_UInt32  eq_band4_of:1;
        RBus_UInt32  eq_band3_of:1;
        RBus_UInt32  eq_band2_of:1;
        RBus_UInt32  eq_band1_of:1;
        RBus_UInt32  eq_lp_of:1;
        RBus_UInt32  eq_hp_of:1;
    };
}eq_status_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_lp0_a1:16;
        RBus_UInt32  lr_loud_lp0_h0:16;
    };
}lr_loud_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_bp1_a1:16;
        RBus_UInt32  lr_loud_bp1_a2:16;
    };
}lr_loud_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  lr_loud_bp1_h0:16;
    };
}lr_loud_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_bp2_a1:16;
        RBus_UInt32  lr_loud_bp2_a2:16;
    };
}lr_loud_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  lr_loud_bp2_h0:16;
    };
}lr_loud_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  ld_lpf_en_lr:1;
        RBus_UInt32  ld_bpf1_en_lr:1;
        RBus_UInt32  ld_bpf2_en_lr:1;
    };
}loudness_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  ld_lpf_of_lr:1;
        RBus_UInt32  ld_bpf1_of_lr:1;
        RBus_UInt32  ld_bpf2_of_lr:1;
    };
}loudness_status_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  reg_in_thre:5;
        RBus_UInt32  reg_zero_in_en:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  zcth:5;
        RBus_UInt32  res3:2;
        RBus_UInt32  dvcm:2;
    };
}digital_volume_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dvol_apply:1;
        RBus_UInt32  zcto:3;
        RBus_UInt32  ramp_step:2;
        RBus_UInt32  delay_ctrl:10;
        RBus_UInt32  mute_apply:1;
        RBus_UInt32  zcto_mute:3;
        RBus_UInt32  ramp_step_mute:2;
        RBus_UInt32  delay_ctrl_mute:10;
    };
}digital_volume_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mute_l:1;
        RBus_UInt32  rep_l_status:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  hpf_l_enable:1;
        RBus_UInt32  vol_l_ready:1;
        RBus_UInt32  vol_l_a:5;
        RBus_UInt32  vol_l_b:6;
        RBus_UInt32  mute_r:1;
        RBus_UInt32  rep_r_status:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  hpf_r_enable:1;
        RBus_UInt32  vol_r_ready:1;
        RBus_UInt32  vol_r_a:5;
        RBus_UInt32  vol_r_b:6;
    };
}lr_digital_volume_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mute_swf_l:1;
        RBus_UInt32  rep_swf_l_status:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  hpf_swf_l_enable:1;
        RBus_UInt32  vol_swf_l_ready:1;
        RBus_UInt32  vol_swf_l_a:5;
        RBus_UInt32  vol_swf_l_b:6;
        RBus_UInt32  mute_swf_r:1;
        RBus_UInt32  rep_swf_r_status:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  hpf_swf_r_enable:1;
        RBus_UInt32  vol_swf_r_ready:1;
        RBus_UInt32  vol_swf_r_a:5;
        RBus_UInt32  vol_swf_r_b:6;
    };
}subwoofer_digital_volume_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_digital_volume_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:30;
        RBus_UInt32  zcto_status:1;
        RBus_UInt32  double_buffer_ack:1;
    };
}double_buffer_ack_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  avc2_vol_amplif_enable:1;
        RBus_UInt32  avc2_lpf_coef:3;
        RBus_UInt32  avc2_vol_detect:2;
        RBus_UInt32  fast_recov_ctrl:1;
        RBus_UInt32  slow_up_db:2;
        RBus_UInt32  fast_up_db:2;
        RBus_UInt32  down_db:2;
        RBus_UInt32  avc2_noise_gain:2;
        RBus_UInt32  avc2_noise_thre:16;
    };
}avc2_control_1_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_cnt_thre:8;
        RBus_UInt32  avc2_zc_win:12;
        RBus_UInt32  avc2_mon_win:12;
    };
}avc2_control_2_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  recov_win_max:8;
        RBus_UInt32  recov_win_min:8;
    };
}avc2_control_3_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_level_max:16;
        RBus_UInt32  avc2_level_min:16;
    };
}avc2_control_4_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  avc2_small_up_db:2;
        RBus_UInt32  avc2_small_down_db:2;
        RBus_UInt32  avc2_small_cnt_thre:8;
    };
}avc2_control_5_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_small_level_max:16;
        RBus_UInt32  avc2_small_level_min:16;
    };
}avc2_control_6_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  avc2_small_level:31;
    };
}avc2_control_7_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_1_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_2_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_3_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_4_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_1_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_2_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_3_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_4_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_1_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_2_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_3_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_4_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hw_mixing_sel:1;
        RBus_UInt32  res1:31;
    };
}hw_out_trans_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  eq_ovf_en:1;
        RBus_UInt32  loudness_ovf_en:1;
        RBus_UInt32  dvol_int_en:1;
        RBus_UInt32  res2:12;
        RBus_UInt32  dvol_done:1;
        RBus_UInt32  eq_ovf:1;
        RBus_UInt32  loudness_ovf:1;
    };
}system_int_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  avc_lp_out:24;
    };
}avc_lp_out_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006818_31_0:32;
    };
}dummy_6718_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1800681c_31_0:32;
    };
}dummy_671c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  ch01_scale_a:4;
        RBus_UInt32  res2:1;
        RBus_UInt32  ch01_scale_b:3;
    };
}hw_in_pre_scale_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dist_vol_detect:2;
        RBus_UInt32  res1:7;
        RBus_UInt32  dist_coef:3;
        RBus_UInt32  dist_high_thre:8;
        RBus_UInt32  dist_low_thre:8;
        RBus_UInt32  dist_down_db:2;
        RBus_UInt32  dist_up_db:2;
    };
}hw_distortion_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dist_cnt_thre:8;
        RBus_UInt32  dist_zc_win:12;
        RBus_UInt32  dist_mon_win:12;
    };
}hw_distortion_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lrrr_dvol_apply:1;
        RBus_UInt32  lrrr_zcto:3;
        RBus_UInt32  lrrr_ramp_step:2;
        RBus_UInt32  lrrr_delay_ctrl:10;
        RBus_UInt32  lrrr_mute_apply:1;
        RBus_UInt32  lrrr_zcto_mute:3;
        RBus_UInt32  lrrr_ramp_step_mute:2;
        RBus_UInt32  lrrr_delay_ctrl_mute:10;
    };
}lrrr_digital_volume_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  lrrr_dvol_enable:1;
        RBus_UInt32  lrrr_zcto_status:1;
        RBus_UInt32  lrrr_zcth:5;
        RBus_UInt32  res2:2;
        RBus_UInt32  lrrr_dvcm:2;
    };
}lrrr_digital_volume_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mute_lr:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  hpf_lr_enable:1;
        RBus_UInt32  vol_lr_ready:1;
        RBus_UInt32  vol_lr_a:5;
        RBus_UInt32  vol_lr_b:6;
        RBus_UInt32  mute_rr:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hpf_rr_enable:1;
        RBus_UInt32  vol_rr_ready:1;
        RBus_UInt32  vol_rr_a:5;
        RBus_UInt32  vol_rr_b:6;
    };
}lrrr_digital_volume_control_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1800690c_31_0:32;
    };
}ts_ds_mbist_recoding_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  down_sample_rate:2;
        RBus_UInt32  vol_source_sel:1;
    };
}dvol_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_vol_ts_enable:1;
        RBus_UInt32  avc_vol_amplif_ts_enable:1;
        RBus_UInt32  avc_vol_ts_detect:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  avc1_ts_coef:3;
        RBus_UInt32  avc_ts_zc_win:12;
        RBus_UInt32  avc_ts_mon_win:12;
    };
}auto_volume_control_ts_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reversed:2;
        RBus_UInt32  avc_ts_noise_gain:2;
        RBus_UInt32  avc_ts_noise_thre:8;
        RBus_UInt32  avc_ts_level_max:8;
        RBus_UInt32  avc_ts_level_min:8;
        RBus_UInt32  avc_ts_down_db:2;
        RBus_UInt32  avc_ts_up_db:2;
    };
}auto_volume_control_ts_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  avc_ts_cnt_thre:8;
        RBus_UInt32  avc_ts_small_level:16;
    };
}auto_volume_control_ts_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  avc_ts_small_level_max:8;
        RBus_UInt32  avc_ts_small_level_min:8;
        RBus_UInt32  avc_ts_small_down_db:2;
        RBus_UInt32  avc_ts_small_up_db:2;
        RBus_UInt32  avc_ts_small_cnt_thre:8;
    };
}auto_volume_control_ts_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:18;
        RBus_UInt32  sif_adc_in_test_en:1;
        RBus_UInt32  sif_adc_in_test_sel:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  debug_mode_sel:9;
    };
}test_pattern_gen_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:8;
        RBus_UInt32  audio_crc_header:24;
    };
}crc_header_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  audio_crc_en:1;
        RBus_UInt32  audio_crc_ch_sel:3;
        RBus_UInt32  audio_crc_frame_length:16;
    };
}crc_contorl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:7;
        RBus_UInt32  audio_crc_done:1;
        RBus_UInt32  audio_crc:24;
    };
}crc_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sine_auto_chk_en:1;
        RBus_UInt32  sine_channel_select:3;
        RBus_UInt32  res1:3;
        RBus_UInt32  auto_chk_result:1;
        RBus_UInt32  half_sine_num:2;
        RBus_UInt32  amplitude_low_threshold:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  zc_sample_cnt_threshold:6;
        RBus_UInt32  zc_sample_cnt_golden:12;
    };
}sine_auto_chk_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:12;
        RBus_UInt32  sine_amplitude:8;
        RBus_UInt32  zc_sample_cnt:12;
    };
}sine_wave_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006a18_31_0:32;
    };
}pattern_gen_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  dummy18006a50_3_1:3;
        RBus_UInt32  to_ack_en:1;
    };
}rbus_ack_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:19;
        RBus_UInt32  ack_fail_rw:1;
        RBus_UInt32  ack_fail_addr:12;
    };
}ack_fail_info_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  clk_sel:3;
        RBus_UInt32  pcmsync:1;
        RBus_UInt32  pkt:1;
        RBus_UInt32  sample_flat:4;
        RBus_UInt32  rmute3:1;
        RBus_UInt32  lmute3:1;
        RBus_UInt32  rmute2:1;
        RBus_UInt32  lmute2:1;
        RBus_UInt32  rmute1:1;
        RBus_UInt32  lmute1:1;
        RBus_UInt32  pcm_8ch:1;
        RBus_UInt32  bit:3;
        RBus_UInt32  wait_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  rmute:1;
        RBus_UInt32  lmute:1;
        RBus_UInt32  switch_wait_en:1;
        RBus_UInt32  sel:2;
        RBus_UInt32  en:1;
    };
}aio_o_hdmi_gctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  realgo:1;
        RBus_UInt32  fcnt:8;
    };
}aio_o_hdmi_fcnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cs1:32;
    };
}aio_o_hdmi_cs1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:24;
        RBus_UInt32  cs2:8;
    };
}aio_o_hdmi_cs2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:16;
        RBus_UInt32  userdata:8;
        RBus_UInt32  valid:8;
    };
}aio_o_hdmi_info_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:15;
        RBus_UInt32  en10:1;
        RBus_UInt32  en9:1;
        RBus_UInt32  en8:1;
        RBus_UInt32  en7:1;
        RBus_UInt32  en6:1;
        RBus_UInt32  emptystopen:1;
        RBus_UInt32  thd:5;
        RBus_UInt32  en5:1;
        RBus_UInt32  en4:1;
        RBus_UInt32  en3:1;
        RBus_UInt32  en2:1;
        RBus_UInt32  res2:2;
    };
}aio_o_fifoctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:20;
        RBus_UInt32  empty11:1;
        RBus_UInt32  empty10:1;
        RBus_UInt32  empty9:1;
        RBus_UInt32  empty8:1;
        RBus_UInt32  empty7:1;
        RBus_UInt32  empty6:1;
        RBus_UInt32  empty5:1;
        RBus_UInt32  empty4:1;
        RBus_UInt32  empty3:1;
        RBus_UInt32  res2:3;
    };
}aio_o_fifo_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_sa_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_ea_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_rp_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:3;
    };
}aio_o_wp_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  gohdmi:1;
        RBus_UInt32  res2:2;
    };
}aio_o_go_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:29;
        RBus_UInt32  pause2:1;
        RBus_UInt32  res2:2;
    };
}aio_o_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  thd:28;
        RBus_UInt32  res2:3;
    };
}aio_o_hdmi_ddrthd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  count:32;
    };
}aio_o_hdmi_timcnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  thd:32;
    };
}aio_o_hdmi_timthd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006db0_31_2:30;
        RBus_UInt32  aodma:1;
        RBus_UInt32  hdmio:1;
    };
}aio_gating_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  draminte11:1;
        RBus_UInt32  draminte10:1;
        RBus_UInt32  draminte9:1;
        RBus_UInt32  draminte8:1;
        RBus_UInt32  draminte7:1;
        RBus_UInt32  draminte6:1;
        RBus_UInt32  draminte5:1;
        RBus_UInt32  draminte4:1;
        RBus_UInt32  fifointe11:1;
        RBus_UInt32  fifointe10:1;
        RBus_UInt32  fifointe9:1;
        RBus_UInt32  fifointe8:1;
        RBus_UInt32  fifointe7:1;
        RBus_UInt32  fifointe6:1;
        RBus_UInt32  fifointe5:1;
        RBus_UInt32  fifointe4:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hdmitiminte:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  hdmithdinte:1;
        RBus_UInt32  draminte3:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  fifointe3:1;
        RBus_UInt32  res5:4;
    };
}aio_o_inte_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  dramints11:1;
        RBus_UInt32  dramints10:1;
        RBus_UInt32  dramints9:1;
        RBus_UInt32  dramints8:1;
        RBus_UInt32  dramints7:1;
        RBus_UInt32  dramints6:1;
        RBus_UInt32  dramints5:1;
        RBus_UInt32  dramints4:1;
        RBus_UInt32  fifoints11:1;
        RBus_UInt32  fifoints10:1;
        RBus_UInt32  fifoints9:1;
        RBus_UInt32  fifoints8:1;
        RBus_UInt32  fifoints7:1;
        RBus_UInt32  fifoints6:1;
        RBus_UInt32  fifoints5:1;
        RBus_UInt32  fifoints4:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  hdmitimints:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  hdmithdints:1;
        RBus_UInt32  dramints3:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  fifoints3:1;
        RBus_UInt32  res5:4;
    };
}aio_o_ints_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:21;
        RBus_UInt32  ao_dma_ls_en:1;
        RBus_UInt32  rm:4;
        RBus_UInt32  rme:1;
        RBus_UInt32  dma_pcm_sel:1;
        RBus_UInt32  pcm_source_sel:4;
    };
}aio_hdmi_out_source_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_bist_mode_ao_dma:1;
        RBus_UInt32  audio_bist_mode_ts_ds:1;
        RBus_UInt32  audio_bist_mode_ds:1;
        RBus_UInt32  audio_bist_mode_adc:1;
        RBus_UInt32  audio_bist_mode_dac:1;
        RBus_UInt32  audio_bist_mode_dma_ts:1;
        RBus_UInt32  audio_bist_mode_dma:1;
        RBus_UInt32  audio_bist_mode_a2_eiaj:1;
        RBus_UInt32  audio_bist_mode_am:1;
        RBus_UInt32  audio_bist_mode_msd:1;
    };
}audio_bist_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_bist_done_ao_dma:1;
        RBus_UInt32  audio_bist_done_ts_ds:1;
        RBus_UInt32  audio_bist_done_ds:1;
        RBus_UInt32  audio_bist_done_adc:1;
        RBus_UInt32  audio_bist_done_dac:1;
        RBus_UInt32  audio_bist_done_dma_ts:1;
        RBus_UInt32  audio_bist_done_dma:1;
        RBus_UInt32  audio_bist_done_a2_eiaj:1;
        RBus_UInt32  audio_bist_done_am:1;
        RBus_UInt32  audio_bist_done_msd:1;
    };
}audio_bist_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_bist_fail_group_ao_dma:1;
        RBus_UInt32  audio_bist_fail_group_ts_ds:1;
        RBus_UInt32  audio_bist_fail_group_ds:1;
        RBus_UInt32  audio_bist_fail_group_adc:1;
        RBus_UInt32  audio_bist_fail_group_dac:1;
        RBus_UInt32  audio_bist_fail_group_dma_ts:1;
        RBus_UInt32  audio_bist_fail_group_dma:1;
        RBus_UInt32  audio_bist_fail_group_a2_eiaj:1;
        RBus_UInt32  audio_bist_fail_group_am:1;
        RBus_UInt32  audio_bist_fail_group_msd:1;
    };
}audio_bist_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  audio_bist_dac_fail_1:1;
        RBus_UInt32  audio_bist_dac_fail_0:1;
        RBus_UInt32  audio_bist_down_ts_fail_3:1;
        RBus_UInt32  audio_bist_down_ts_fail_2:1;
        RBus_UInt32  audio_bist_down_ts_fail_1:1;
        RBus_UInt32  audio_bist_down_ts_fail_0:1;
        RBus_UInt32  res2:12;
        RBus_UInt32  audio_bist_down_fail_3:1;
        RBus_UInt32  audio_bist_down_fail_2:1;
        RBus_UInt32  audio_bist_down_fail_1:1;
        RBus_UInt32  audio_bist_down_fail_0:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_8:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_7:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_6:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_5:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_4:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_3:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_2:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_1:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_0:1;
    };
}audio_bist_a2_eiaj_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_drf_mode_ao_dma:1;
        RBus_UInt32  audio_drf_mode_ts_ds:1;
        RBus_UInt32  audio_drf_mode_ds:1;
        RBus_UInt32  audio_drf_mode_adc:1;
        RBus_UInt32  audio_drf_mode_dac:1;
        RBus_UInt32  audio_drf_mode_dma_ts:1;
        RBus_UInt32  audio_drf_mode_dma:1;
        RBus_UInt32  audio_drf_mode_a2_eiaj:1;
        RBus_UInt32  audio_drf_mode_am:1;
        RBus_UInt32  audio_drf_mode_msd:1;
    };
}audio_drf_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_drf_resume_ao_dma:1;
        RBus_UInt32  audio_drf_resume_ts_ds:1;
        RBus_UInt32  audio_drf_resume_ds:1;
        RBus_UInt32  audio_drf_resume_adc:1;
        RBus_UInt32  audio_drf_resume_dac:1;
        RBus_UInt32  audio_drf_resume_dma_ts:1;
        RBus_UInt32  audio_drf_resume_dma:1;
        RBus_UInt32  audio_drf_resume_a2_eiaj:1;
        RBus_UInt32  audio_drf_resume_am:1;
        RBus_UInt32  audio_drf_resume_msd:1;
    };
}audio_drf_resume_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_drf_done_ao_dma:1;
        RBus_UInt32  audio_drf_done_ts_ds:1;
        RBus_UInt32  audio_drf_done_ds:1;
        RBus_UInt32  audio_drf_done_adc:1;
        RBus_UInt32  audio_drf_done_dac:1;
        RBus_UInt32  audio_drf_done_dma_ts:1;
        RBus_UInt32  audio_drf_done_dma:1;
        RBus_UInt32  audio_drf_done_a2_eiaj:1;
        RBus_UInt32  audio_drf_done_am:1;
        RBus_UInt32  audio_drf_done_msd:1;
    };
}audio_drf_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_drf_pause_ao_dma:1;
        RBus_UInt32  audio_drf_pause_ts_ds:1;
        RBus_UInt32  audio_drf_pause_ds:1;
        RBus_UInt32  audio_drf_pause_adc:1;
        RBus_UInt32  audio_drf_pause_dac:1;
        RBus_UInt32  audio_drf_pause_dma_ts:1;
        RBus_UInt32  audio_drf_pause_dma:1;
        RBus_UInt32  audio_drf_pause_a2_eiaj:1;
        RBus_UInt32  audio_drf_pause_am:1;
        RBus_UInt32  audio_drf_pause_msd:1;
    };
}audio_drf_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  audio_drf_fail_group_ao_dma:1;
        RBus_UInt32  audio_drf_fail_group_ts_ds:1;
        RBus_UInt32  audio_drf_fail_group_ds:1;
        RBus_UInt32  audio_drf_fail_group_adc:1;
        RBus_UInt32  audio_drf_fail_group_dac:1;
        RBus_UInt32  audio_drf_fail_group_dma_ts:1;
        RBus_UInt32  audio_drf_fail_group_dma:1;
        RBus_UInt32  audio_drf_fail_group_a2_eiaj:1;
        RBus_UInt32  audio_drf_fail_group_am:1;
        RBus_UInt32  audio_drf_fail_group_msd:1;
    };
}audio_drf_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:1;
        RBus_UInt32  audio_drf_dac_fail_1:1;
        RBus_UInt32  audio_drf_dac_fail_0:1;
        RBus_UInt32  audio_drf_down_ts_fail_3:1;
        RBus_UInt32  audio_drf_down_ts_fail_2:1;
        RBus_UInt32  audio_drf_down_ts_fail_1:1;
        RBus_UInt32  audio_drf_down_ts_fail_0:1;
        RBus_UInt32  res2:12;
        RBus_UInt32  audio_drf_down_fail_3:1;
        RBus_UInt32  audio_drf_down_fail_2:1;
        RBus_UInt32  audio_drf_down_fail_1:1;
        RBus_UInt32  audio_drf_down_fail_0:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_8:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_7:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_6:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_5:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_4:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_3:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_2:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_1:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_0:1;
    };
}audio_drf_a2_eiaj_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  daad_lp_en:1;
        RBus_UInt32  src_op_sel:1;
        RBus_UInt32  src_ad_lpf1st_fc_sel:2;
        RBus_UInt32  ad_hpf_en:1;
        RBus_UInt32  ad_comp_gain:3;
        RBus_UInt32  ad_zdet_tout:2;
        RBus_UInt32  ad_zdet_func:2;
        RBus_UInt32  adc_src_lpf_disable:1;
        RBus_UInt32  ad_lp_sel:1;
        RBus_UInt32  ad_mute_l:1;
        RBus_UInt32  ad_mute_r:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ad_gain_l:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  ad_gain_r:7;
    };
}ad_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adda_lp_en_0:1;
        RBus_UInt32  src_en_0:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  da0_hpf_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  da0_dither_sel:2;
        RBus_UInt32  da0_zdet_tout:2;
        RBus_UInt32  da0_zdet_func:2;
        RBus_UInt32  da0_fifo_empty:1;
        RBus_UInt32  da0_fifo_full:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  da0_gain_l:7;
        RBus_UInt32  res4:1;
        RBus_UInt32  da0_gain_r:7;
    };
}da0_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  adda_lp_en_1:1;
        RBus_UInt32  src_en_1:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  da1_hpf_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  da1_dither_sel:2;
        RBus_UInt32  da1_zdet_tout:2;
        RBus_UInt32  da1_zdet_func:2;
        RBus_UInt32  da1_fifo_empty:1;
        RBus_UInt32  da1_fifo_full:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  da1_gain_l:7;
        RBus_UInt32  res4:1;
        RBus_UInt32  da1_gain_r:7;
    };
}da1_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dac1_hw_l_inverter_en:1;
        RBus_UInt32  dac1_hw_r_inverter_en:1;
        RBus_UInt32  dac1_hw_out_limiter_en:1;
        RBus_UInt32  dac1_hw_out_limiter:7;
        RBus_UInt32  dac1_pcm_source_sel:3;
        RBus_UInt32  res1:2;
        RBus_UInt32  dac0_swap_sel:2;
        RBus_UInt32  dac1_swap_sel:2;
        RBus_UInt32  dac0_hw_l_inverter_en:1;
        RBus_UInt32  dac0_hw_r_inverter_en:1;
        RBus_UInt32  dac0_hw_out_limiter_en:1;
        RBus_UInt32  dac0_hw_out_limiter:7;
        RBus_UInt32  dac0_pcm_source_sel:3;
    };
}dac0_1_src_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_bb_hpo_encopy:2;
        RBus_UInt32  reg_bb_aio1_encopy:2;
        RBus_UInt32  reg_bb_aio1_engl:1;
        RBus_UInt32  reg_bb_aio1_engr:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_bb_aio1_gsell:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_bb_aio1_gselr:3;
        RBus_UInt32  reg_bb_aio2_encopy:2;
        RBus_UInt32  reg_bb_aio2_engl:1;
        RBus_UInt32  reg_bb_aio2_engr:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_bb_aio2_gsell:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_bb_aio2_gselr:3;
        RBus_UInt32  reg_bb_adcsel:1;
        RBus_UInt32  res6:3;
    };
}analog_out_copy_swap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bb_aio1_mutel:4;
        RBus_UInt32  reg_bb_aio1_muter:4;
        RBus_UInt32  reg_bb_aio2_mutel:4;
        RBus_UInt32  reg_bb_aio2_muter:4;
        RBus_UInt32  res1:4;
        RBus_UInt32  reg_bb_adcfe_mute_l:6;
        RBus_UInt32  reg_bb_adcfe_mute_r:6;
    };
}analog_frontend_mute_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:22;
        RBus_UInt32  reg_bb_hpo_mutel:5;
        RBus_UInt32  reg_bb_hpo_muter:5;
    };
}analog_aio_hpout_lineout_l_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}analog_aio_hpout_lineout_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:28;
        RBus_UInt32  reg_bb_adcfe_gsell:2;
        RBus_UInt32  reg_bb_adcfe_gselr:2;
    };
}adc_volume_gain_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:17;
        RBus_UInt32  reg_bb_powaio1:1;
        RBus_UInt32  reg_bb_powaio2:1;
        RBus_UInt32  reg_bb_powadcfe:1;
        RBus_UInt32  reg_bb_powadc:2;
        RBus_UInt32  reg_bb_powdac:2;
        RBus_UInt32  reg_bb_powmbias:1;
        RBus_UInt32  reg_bb_powvref:1;
        RBus_UInt32  reg_bb_powdf2se:2;
        RBus_UInt32  reg_bb_powhpo:1;
        RBus_UInt32  res2:3;
    };
}analog_power_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  afe_pga_vol:9;
    };
}analog_pga_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_bb_isel_vref:2;
        RBus_UInt32  reg_bb_isel_aio1:2;
        RBus_UInt32  reg_bb_isel_aio2:2;
        RBus_UInt32  reg_bb_isel_hpo:2;
        RBus_UInt32  reg_bb_isel_df2se:2;
        RBus_UInt32  reg_bb_isel_depop:2;
        RBus_UInt32  reg_bb_isel_dacref:2;
        RBus_UInt32  reg_bb_isel_dacop:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_bb_isel_adcst2:2;
        RBus_UInt32  reg_bb_isel_adcst1:2;
        RBus_UInt32  reg_bb_isel_adcref:2;
        RBus_UInt32  reg_bb_isel_adcfe:2;
        RBus_UInt32  reg_bb_isel_adccomp:2;
        RBus_UInt32  reg_bb_isel_adcaa:2;
    };
}analog_ci01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  reg_bb_adc_refset:1;
        RBus_UInt32  reg_bb_adc_ckxen:1;
        RBus_UInt32  reg_bb_adc_fset:1;
        RBus_UInt32  reg_bb_vref_vrefsel:2;
    };
}analog_ci02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy_692c:32;
    };
}analog_dummy2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:27;
        RBus_UInt32  reg_bb_dpramp_enramp:1;
        RBus_UInt32  bb_ck_depop_en:1;
        RBus_UInt32  sel_bb_ck_depop:3;
    };
}analog_depop1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:23;
        RBus_UInt32  reg_bb_aio2_normal:1;
        RBus_UInt32  reg_bb_aio1_normal:1;
        RBus_UInt32  reg_bb_powdepop:1;
        RBus_UInt32  reg_bb_dpramp_csel:2;
        RBus_UInt32  reg_bb_hpo_normal:1;
        RBus_UInt32  res2:3;
    };
}analog_depop2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  reg_bb_hpo_engl:1;
        RBus_UInt32  reg_bb_hpo_engr:1;
        RBus_UInt32  res2:20;
        RBus_UInt32  reg_bb_hpo_gsell:2;
        RBus_UInt32  reg_bb_hpo_gselr:2;
    };
}analog_post_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:11;
        RBus_UInt32  rme_1_dac:1;
        RBus_UInt32  rm_1_dac:4;
        RBus_UInt32  res2:3;
        RBus_UInt32  rme_0_dac:1;
        RBus_UInt32  rm_0_dac:4;
        RBus_UInt32  res3:3;
        RBus_UInt32  rme_0_adc:1;
        RBus_UInt32  rm_0_adc:4;
    };
}drf_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}amic1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}analog_capless_lineout_depop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}analog_capless_lineout_control_RBUS;



#else //apply LITTLE_ENDIAN

//======SIRIUS_DESIGNSPEC_AUDIO register structure define==========

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  sel_clk_dac1_out:1;
        RBus_UInt32  sel_clk_dac0_out:1;
        RBus_UInt32  res2:12;
        RBus_UInt32  tcon1_div_fs:2;
        RBus_UInt32  tcon0_div_fs:2;
        RBus_UInt32  div_tsdma_r_512fs:2;
        RBus_UInt32  div_dma_r_512fs:2;
        RBus_UInt32  sel_clk_i2s_out:1;
        RBus_UInt32  sel_clk_spdif_out:1;
        RBus_UInt32  div_pre_512fs_ts:2;
        RBus_UInt32  res3:2;
        RBus_UInt32  inv_ad_256fs:1;
        RBus_UInt32  inv_ad_128fs:1;
    };
}global_ctrl_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  back_end_play_sample_rate:2;
        RBus_UInt32  sel_play_ck_source:2;
        RBus_UInt32  adc_512fs_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  back_end_ts_sample_rate:2;
        RBus_UInt32  sel_ts_ck_source:2;
        RBus_UInt32  adc_512fs_sel_ts:2;
        RBus_UInt32  spdif_nicam:1;
        RBus_UInt32  sel_i2s_hdmi:2;
        RBus_UInt32  sel_i2s_spdif:1;
        RBus_UInt32  sif_adc_clk_en:1;
        RBus_UInt32  sif_adc_clk_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  src_da_128fs_ts:1;
        RBus_UInt32  src_da_128fs:1;
        RBus_UInt32  inv_da_128fs_ts:1;
        RBus_UInt32  inv_da_128fs:1;
        RBus_UInt32  a2_eiaj_sram_on:1;
        RBus_UInt32  am_sram_on:1;
        RBus_UInt32  dac_sram_on:1;
        RBus_UInt32  adc_sram_on:1;
    };
}global_ctrl_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  asrcin0_ftk_sdm_ini:22;
        RBus_UInt32  tcon0_fsi_sel:2;
        RBus_UInt32  asrcin0_ftk_loop_gain_sel:1;
        RBus_UInt32  asrcin0_ftk_loop_filter_mode:1;
        RBus_UInt32  reg_tcon0_rst_n:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  asrcin0_fsi_rate_manual:4;
    };
}tcon0_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  asrcin1_ftk_sdm_ini:22;
        RBus_UInt32  tcon1_fsi_sel:2;
        RBus_UInt32  asrcin1_ftk_loop_gain_sel:1;
        RBus_UInt32  asrcin1_ftk_loop_filter_mode:1;
        RBus_UInt32  reg_tcon1_rst_n:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  asrcin1_fsi_rate_manual:4;
    };
}tcon1_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_para_a:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_para_d:4;
        RBus_UInt32  mod_acc_rst:1;
        RBus_UInt32  pll_spdif_auto_mode:1;
        RBus_UInt32  reg_smooth_en:1;
        RBus_UInt32  pll_spdif_dtrack_en:1;
        RBus_UInt32  ps_contword:5;
        RBus_UInt32  ps_testmode:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  reg_para_e:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  div_2fs:2;
        RBus_UInt32  res4:1;
        RBus_UInt32  contword_inv:1;
    };
}pllcg_spdif_gain_cr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  p_gain_set2:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  p_gain_set:10;
        RBus_UInt32  res2:6;
    };
}pllcg_spdif_gain_cr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  i_gain_set:10;
        RBus_UInt32  res1:22;
    };
}pllcg_spdif_gain_cr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_correct_range:4;
        RBus_UInt32  reach_time_num:3;
        RBus_UInt32  res1:25;
    };
}pllcg_spdif_number_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  low_bound2:8;
        RBus_UInt32  high_bound2:8;
        RBus_UInt32  low_bound1:8;
        RBus_UInt32  high_bound1:8;
    };
}pllcg_spdif_bound_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  freq_sel:2;
        RBus_UInt32  wdog_switch_en:1;
        RBus_UInt32  res1:13;
        RBus_UInt32  dummy18006024_31_16:16;
    };
}global_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aio_o_raw2_clken:1;
        RBus_UInt32  aio_o_raw2_fs:4;
        RBus_UInt32  res1:27;
    };
}ao_hdmi_fs_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  int_sif_ovf_en:1;
        RBus_UInt32  int_mode_det_status_change_en:1;
        RBus_UInt32  int_msd_timeout_en:1;
        RBus_UInt32  int_msd_change_en:1;
        RBus_UInt32  int_sif_nopt_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  int_i2s_pri_word_length_change_en:1;
        RBus_UInt32  int_spi_sample_rate_chg_en:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  int_i2s_pri_sample_rate_chg_en:1;
        RBus_UInt32  int_nicam_hierr_change_en:1;
        RBus_UInt32  int_spi_in_lock_change_en:1;
        RBus_UInt32  int_spi_in_datatype_change_en:1;
        RBus_UInt32  int_aout_timer_en:1;
        RBus_UInt32  int_ain_timer_en:1;
        RBus_UInt32  int_nicam_level_status_en:1;
        RBus_UInt32  int_fifo0_empty_en:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  int_fifo0_full_en:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  int_btsc_mode_chg_en:1;
        RBus_UInt32  int_rbus_timeout_en:1;
        RBus_UInt32  int_msd_fw_scan_done_en:1;
        RBus_UInt32  int_msd_decision_done_en:1;
        RBus_UInt32  int_pll64512_wd_en:1;
        RBus_UInt32  int_fifo0_ts_empty_en:1;
        RBus_UInt32  int_fifo0_ts_full_en:1;
        RBus_UInt32  int_nicam_true_detect_en:1;
    };
}interrupt_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  int_sif_ovf:1;
        RBus_UInt32  int_mode_det_status_change:1;
        RBus_UInt32  int_msd_timeout:1;
        RBus_UInt32  int_msd_change:1;
        RBus_UInt32  int_sif_nopt:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  int_i2s_pri_word_length_change:1;
        RBus_UInt32  int_spi_sample_rate_chg:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  int_i2s_pri_sample_rate_chg:1;
        RBus_UInt32  int_nicam_hierr_change:1;
        RBus_UInt32  int_spi_in_lock_change:1;
        RBus_UInt32  int_spi_in_datatype_change:1;
        RBus_UInt32  int_aout_timer:1;
        RBus_UInt32  int_ain_timer:1;
        RBus_UInt32  int_nicam_level_status:1;
        RBus_UInt32  int_fifo0_empty:1;
        RBus_UInt32  res3:3;
        RBus_UInt32  int_fifo0_full:1;
        RBus_UInt32  res4:3;
        RBus_UInt32  int_btsc_mode_chg:1;
        RBus_UInt32  int_rbus_timeout:1;
        RBus_UInt32  int_msd_fw_scan_done:1;
        RBus_UInt32  int_msd_decision_done:1;
        RBus_UInt32  int_pll64512_wd:1;
        RBus_UInt32  int_fifo0_ts_empty:1;
        RBus_UInt32  int_fifo0_ts_full:1;
        RBus_UInt32  int_nicam_true_detect:1;
    };
}interrupt_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aout_timer_en:1;
        RBus_UInt32  ain_timer_en:1;
        RBus_UInt32  res1:30;
    };
}aio_timer_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ain_timer:32;
    };
}ain_counter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ain_compare:32;
    };
}ain_compare_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aout_timer:32;
    };
}aout_counter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  aout_compare:32;
    };
}aout_compare_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_0:32;
    };
}sw_dbg_reg_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_1:32;
    };
}sw_dbg_reg_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_2:32;
    };
}sw_dbg_reg_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sw_dbg_reg_3:32;
    };
}sw_dbg_reg_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcm_width:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  sampling_rate:4;
        RBus_UInt32  res2:4;
        RBus_UInt32  dummy18006100_24_16:9;
        RBus_UInt32  sclk_inv:1;
        RBus_UInt32  debounce_en:1;
        RBus_UInt32  mode_sel:1;
        RBus_UInt32  left_right:2;
        RBus_UInt32  source_sel:2;
    };
}i2s_in_primary_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sampling_rate:4;
        RBus_UInt32  spdif_in_2fs_sel:1;
        RBus_UInt32  dummy18006130_15_5:11;
        RBus_UInt32  res1:12;
        RBus_UInt32  debounce_en:1;
        RBus_UInt32  req_after_lock:1;
        RBus_UInt32  source_sel:2;
    };
}spdif_in_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  professional:1;
        RBus_UInt32  data_type:1;
        RBus_UInt32  copyright:1;
        RBus_UInt32  pre_emphasis:3;
        RBus_UInt32  mode_r:2;
        RBus_UInt32  category_code_r:8;
        RBus_UInt32  source_number_r:4;
        RBus_UInt32  channel_number_r:4;
        RBus_UInt32  sampling_freq_r:4;
        RBus_UInt32  clock_accuracy_r:2;
        RBus_UInt32  invalid_bit:1;
        RBus_UInt32  hw_locked:1;
    };
}spdif_in_cs_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  word_length_r:4;
        RBus_UInt32  original_sampling_freq_r:4;
        RBus_UInt32  cgms_a_r:2;
        RBus_UInt32  cgms_a_l:2;
        RBus_UInt32  res1:20;
    };
}spdif_in_cs_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mode_l:2;
        RBus_UInt32  category_code_l:8;
        RBus_UInt32  source_number_l:4;
        RBus_UInt32  channel_number_l:4;
        RBus_UInt32  sampling_freq_l:4;
        RBus_UInt32  clock_accuracy_l:2;
        RBus_UInt32  word_length_l:4;
        RBus_UInt32  original_sampling_freq_l:4;
    };
}spdif_in_cs_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006150_15_0:16;
        RBus_UInt32  sclk_inv:1;
        RBus_UInt32  wclk_inv:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  mclk_sel:2;
        RBus_UInt32  res2:2;
        RBus_UInt32  output_sel:3;
        RBus_UInt32  res3:1;
    };
}i2s_out_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hw_limit_ch01:7;
        RBus_UInt32  hw_limit_en_ch01:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  swap_sel_ch01:2;
        RBus_UInt32  hw_limit_ch23:7;
        RBus_UInt32  hw_limit_en_ch23:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  pcm_source_sel_ch23:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  pcm_source_sel_ch01:3;
        RBus_UInt32  res4:1;
    };
}i2s_out_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006170_15_0:16;
        RBus_UInt32  swap_sel:2;
        RBus_UInt32  res1:5;
        RBus_UInt32  pcm_source_sel:4;
        RBus_UInt32  spdif_out_null_burst:1;
        RBus_UInt32  validity_ctrl:1;
        RBus_UInt32  wait_en:1;
        RBus_UInt32  output_sel:2;
    };
}spdif_out_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hw_limit:7;
        RBus_UInt32  hw_limit_en:1;
        RBus_UInt32  res1:24;
    };
}spdif_out_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  professional:1;
        RBus_UInt32  data_type:1;
        RBus_UInt32  copyright:1;
        RBus_UInt32  pre_emphasis:3;
        RBus_UInt32  mode:2;
        RBus_UInt32  category_code:8;
        RBus_UInt32  source_number:4;
        RBus_UInt32  channel_number:4;
        RBus_UInt32  sampling_freq:4;
        RBus_UInt32  clock_accuracy:2;
        RBus_UInt32  res1:2;
    };
}spdif_out_cs_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  word_length:4;
        RBus_UInt32  original_sampling_freq:4;
        RBus_UInt32  cgms_a:2;
        RBus_UInt32  res1:22;
    };
}spdif_out_cs_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ob_time:16;
        RBus_UInt32  hw_agc_en:1;
        RBus_UInt32  dummy18006180_19_17:3;
        RBus_UInt32  res1:12;
    };
}sif_agc_eval_cnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  non_opt_cnt_ovf:8;
        RBus_UInt32  non_opt_cnt_under:8;
        RBus_UInt32  non_opt_cnt_th:3;
        RBus_UInt32  res1:13;
    };
}sif_agc_optimal_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  opt_th:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  ovf_th:10;
        RBus_UInt32  res2:6;
    };
}sif_agc_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  abs_peak:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  opt:1;
        RBus_UInt32  ovf:1;
        RBus_UInt32  res2:18;
    };
}sif_agc_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc2_obtime:16;
        RBus_UInt32  agc2_gain_b:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  agc2_gain_a:2;
        RBus_UInt32  agc2_stepsize:2;
        RBus_UInt32  agc2_debounce_cnt:3;
        RBus_UInt32  res2:1;
    };
}sif_agc2_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  agc2_sif_mag:10;
        RBus_UInt32  res1:18;
        RBus_UInt32  agc2_underflow:1;
        RBus_UInt32  agc2_overflow:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  agc2_en:1;
    };
}sif_agc2_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  detect_source_sel:4;
        RBus_UInt32  pdetect_enable:1;
        RBus_UInt32  res1:27;
    };
}peak_contorl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ovf_th_l:16;
        RBus_UInt32  opt_th_l:16;
    };
}peak_contorl_l_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpp_eval_cnt_l:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  nonopt_cnt_tr_l:3;
        RBus_UInt32  dummy180061b4_31_19:13;
    };
}peak_control_l_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  magnitude_l:16;
        RBus_UInt32  pk_adj_l:6;
        RBus_UInt32  overflow_l:1;
        RBus_UInt32  optimize_l:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  overflow_l_irq_en:1;
        RBus_UInt32  optimize_l_irq_en:1;
    };
}peak_status_l_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcm_l_monitor:24;
        RBus_UInt32  toggle_cnt:8;
    };
}peak_status_l_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ovf_th_r:16;
        RBus_UInt32  opt_th_r:16;
    };
}peak_contorl_r_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vpp_eval_cnt_r:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  nonopt_cnt_tr_r:3;
        RBus_UInt32  dummy180061c4_31_19:13;
    };
}peak_contorl_r_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  magnitude_r:16;
        RBus_UInt32  pk_adj_r:6;
        RBus_UInt32  overflow_r:1;
        RBus_UInt32  optimize_r:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  overflow_r_irq_en:1;
        RBus_UInt32  optimize_r_irq_en:1;
    };
}peak_status_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcm_r_monitor:24;
        RBus_UInt32  res1:8;
    };
}peak_status_r_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_detect_source_sel:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  post_detect_enable:1;
        RBus_UInt32  res2:27;
    };
}post_peak_contorl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_ovf_th_l:16;
        RBus_UInt32  post_opt_th_l:16;
    };
}post_peak_contorl_l_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_vpp_eval_cnt_l:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  post_nonopt_cnt_tr_l:3;
        RBus_UInt32  res2:13;
    };
}post_peak_control_l_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_magnitude_l:16;
        RBus_UInt32  post_pk_adj_l:6;
        RBus_UInt32  post_overflow_l:1;
        RBus_UInt32  post_optimize_l:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  post_overflow_l_irq_en:1;
        RBus_UInt32  post_optimize_l_irq_en:1;
    };
}post_peak_status_l_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_pcm_l_monitor:24;
        RBus_UInt32  post_toggle_cnt:8;
    };
}post_peak_status_l_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_ovf_th_r:16;
        RBus_UInt32  post_opt_th_r:16;
    };
}post_peak_contorl_r_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_vpp_eval_cnt_r:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  post_nonopt_cnt_tr_r:3;
        RBus_UInt32  res2:13;
    };
}post_peak_contorl_r_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_magnitude_r:16;
        RBus_UInt32  post_pk_adj_r:6;
        RBus_UInt32  post_overflow_r:1;
        RBus_UInt32  post_optimize_r:1;
        RBus_UInt32  res1:6;
        RBus_UInt32  post_overflow_r_irq_en:1;
        RBus_UInt32  post_optimize_r_irq_en:1;
    };
}post_peak_status_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  post_pcm_r_monitor:24;
        RBus_UInt32  res1:8;
    };
}post_peak_status_r_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_scan_freq:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  sound_select:2;
        RBus_UInt32  calc_time_sel:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  dkl_priority:1;
        RBus_UInt32  mn_priority:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_scan_cnt:8;
        RBus_UInt32  msd_debounce_cnt:3;
        RBus_UInt32  msd_reset_n:1;
        RBus_UInt32  carrier_phase_delta:3;
        RBus_UInt32  carrier_shift_scan_en:1;
        RBus_UInt32  update_en:1;
        RBus_UInt32  msd_en:1;
        RBus_UInt32  res4:2;
    };
}msd_crtl_word_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_std:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  hw_detected_std:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  h_dv_th_sel:1;
        RBus_UInt32  flag_subtomain:1;
        RBus_UInt32  flag_unnormal:1;
        RBus_UInt32  res3:1;
        RBus_UInt32  case_subtomain:4;
        RBus_UInt32  deviation_unnormal:2;
        RBus_UInt32  res4:6;
    };
}msd_result_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  deviation:4;
        RBus_UInt32  main_cari_idx:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  shift_value:4;
        RBus_UInt32  res2:4;
        RBus_UInt32  bw_cnt_min:5;
        RBus_UInt32  res3:3;
        RBus_UInt32  bw_cnt_max:5;
        RBus_UInt32  res4:3;
    };
}msd_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  main_thresh_low:16;
        RBus_UInt32  main_thresh:16;
    };
}main_tone_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  main_thresh_hd_low:16;
        RBus_UInt32  main_thresh_hd:16;
    };
}main_tone_threshold_hd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bw_dev_thresh:16;
        RBus_UInt32  bw_dev_thresh_hd:16;
    };
}bw_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  main_sub_ratio:16;
        RBus_UInt32  bw_dev_thresh_low:16;
    };
}main_sub_ratio_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_4_5:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_4_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_4_28:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_4_28_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_4_72:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_4_72_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_5_5:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_5_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_5_25:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_5_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_5_74:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_5_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_5_85:16;
        RBus_UInt32  res1:16;
    };
}msd_carrier_5_85_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_5_95:16;
        RBus_UInt32  res1:16;
    };
}msd_carrier_5_95_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_6:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_6_25:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_6_25_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_6_5:16;
        RBus_UInt32  res1:16;
    };
}msd_carrier_6_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_6_552:16;
        RBus_UInt32  res1:16;
    };
}msd_mag_6_552_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_6_74:16;
        RBus_UInt32  res1:16;
    };
}msd_carrier_6_74_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  flag_6_74:1;
        RBus_UInt32  flag_6_552:1;
        RBus_UInt32  flag_6_25:1;
        RBus_UInt32  flag_5_85:1;
        RBus_UInt32  flag_5_74:1;
        RBus_UInt32  flag_4_72:1;
        RBus_UInt32  flag_6_5:1;
        RBus_UInt32  flag_6:1;
        RBus_UInt32  flag_5_5:1;
        RBus_UInt32  flag_4_5:1;
        RBus_UInt32  flag_fw:1;
        RBus_UInt32  flag_fw_1:1;
        RBus_UInt32  flag_fw_2:1;
        RBus_UInt32  flag_fw_3:1;
        RBus_UInt32  flag_fw_4:1;
        RBus_UInt32  res1:17;
    };
}msd_flags_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_fw:16;
        RBus_UInt32  fw_phase_delta:14;
        RBus_UInt32  res1:2;
    };
}msd_programmable_freq_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_low:16;
        RBus_UInt32  fw_thresh:16;
    };
}threshold_msd_carrier_fw_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_fw_1:16;
        RBus_UInt32  fw_phase_delta_1:14;
        RBus_UInt32  res1:2;
    };
}msd_programmable_freq_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_1_low:16;
        RBus_UInt32  fw_thresh_1:16;
    };
}threshold_msd_carrier_fw_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_fw_2:16;
        RBus_UInt32  fw_phase_delta_2:14;
        RBus_UInt32  res1:2;
    };
}msd_programmable_freq_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_2_low:16;
        RBus_UInt32  fw_thresh_2:16;
    };
}threshold_msd_carrier_fw_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_fw_3:16;
        RBus_UInt32  fw_phase_delta_3:14;
        RBus_UInt32  res1:2;
    };
}msd_programmable_freq_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_3_low:16;
        RBus_UInt32  fw_thresh_3:16;
    };
}threshold_msd_carrier_fw_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_fw_4:16;
        RBus_UInt32  fw_phase_delta_4:14;
        RBus_UInt32  res1:2;
    };
}msd_programmable_freq_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fw_thresh_4_low:16;
        RBus_UInt32  fw_thresh_4:16;
    };
}threshold_msd_carrier_fw_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  second_reg_std:5;
        RBus_UInt32  res1:3;
        RBus_UInt32  mono_std_sel:1;
        RBus_UInt32  reg_bw_detect_en:1;
        RBus_UInt32  reg_cari_sft_detect_en:1;
        RBus_UInt32  res2:21;
    };
}msd_second_reg_std_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sec_thresh_low:16;
        RBus_UInt32  sec_thresh:16;
    };
}second_main_tone_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  res1:27;
    };
}msd_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_55_fix:16;
        RBus_UInt32  reg_mag_45_fix:16;
    };
}msd_main_mag_ori1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_mag_65_fix:16;
        RBus_UInt32  reg_mag_60_fix:16;
    };
}msd_main_mag_ori2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msd_gain_result:4;
        RBus_UInt32  msd_gain_en:1;
        RBus_UInt32  res1:27;
    };
}msd_gain_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  msd_update_count:16;
        RBus_UInt32  fw_update_count:16;
    };
}msd_update_count_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mode_result:2;
        RBus_UInt32  hw_mode_en:1;
        RBus_UInt32  res1:13;
        RBus_UInt32  md_update_count:16;
    };
}mode_detect_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_threshold:16;
        RBus_UInt32  debounce_time:3;
        RBus_UInt32  res1:3;
        RBus_UInt32  lpf_coef_sel_lock:2;
        RBus_UInt32  low_threshold:2;
        RBus_UInt32  high_threshold:2;
        RBus_UInt32  bpf_sel:1;
        RBus_UInt32  lpf_coef_sel:2;
        RBus_UInt32  enable:1;
    };
}md_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  mode_result:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  gain_result:4;
        RBus_UInt32  dummy18006314_15_8:8;
        RBus_UInt32  max_other:16;
    };
}md_status_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  max_dual:16;
        RBus_UInt32  max_stereo:16;
    };
}md_status_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  carrier_freq_correct_en:1;
        RBus_UInt32  force_nicam_en:1;
        RBus_UInt32  res1:29;
        RBus_UInt32  sif_data_source:1;
    };
}carrier_freq_deviation_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sub_phase_delta:14;
        RBus_UInt32  res1:2;
        RBus_UInt32  main_phase_delta:14;
        RBus_UInt32  res2:2;
    };
}carrier_phase_delta_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006358_15_0:16;
        RBus_UInt32  fm_magnitude:16;
    };
}a2_eiaj_dc_filter_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hw_am_prescale:2;
        RBus_UInt32  am_path_sel:1;
        RBus_UInt32  am_bpf_bw:1;
        RBus_UInt32  dummy18006360_7_4:4;
        RBus_UInt32  res1:24;
    };
}am_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  res1:27;
    };
}bist_am_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage1_b1:16;
        RBus_UInt32  sap_bpf_stage1_b0:16;
    };
}sap_bpf_stage1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage1_b2:16;
        RBus_UInt32  res1:16;
    };
}sap_bpf_stage1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage1_a2:16;
        RBus_UInt32  sap_bpf_stage1_a1:16;
    };
}sap_bpf_stage1_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage2_b1:16;
        RBus_UInt32  sap_bpf_stage2_b0:16;
    };
}sap_bpf_stage2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage2_b2:16;
        RBus_UInt32  res1:16;
    };
}sap_bpf_stage2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage2_a2:16;
        RBus_UInt32  sap_bpf_stage2_a1:16;
    };
}sap_bpf_stage2_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage3_b1:16;
        RBus_UInt32  sap_bpf_stage3_b0:16;
    };
}sap_bpf_stage3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage3_b2:16;
        RBus_UInt32  res1:16;
    };
}sap_bpf_stage3_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_bpf_stage3_a2:16;
        RBus_UInt32  sap_bpf_stage3_a1:16;
    };
}sap_bpf_stage3_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pilot_lothresh:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  pilot_hithresh:10;
        RBus_UInt32  res2:5;
        RBus_UInt32  lock_reference:1;
    };
}btsc_pilot_thres_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  w10pilotmagnitude:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  pilot_lo_refuse:1;
        RBus_UInt32  pilot_hi_pass:1;
        RBus_UInt32  pilot_level_pass:1;
        RBus_UInt32  w1pilotlocked:1;
        RBus_UInt32  w1pilotpresent:1;
        RBus_UInt32  out_hpf_en:1;
        RBus_UInt32  pilot_lock_reset:1;
        RBus_UInt32  res2:13;
    };
}btsc_pilot_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_lothresh:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  sap_hithresh:10;
        RBus_UInt32  res2:6;
    };
}btsc_sap_thresh_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_noise_lo_thresh:10;
        RBus_UInt32  res1:6;
        RBus_UInt32  sap_noise_hi_thresh:10;
        RBus_UInt32  res2:6;
    };
}btsc_sap_noise_th_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  w10sapnoise:10;
        RBus_UInt32  res1:22;
    };
}btsc_sap_noise_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  w10sapmagnitude:10;
        RBus_UInt32  sap_normalize_en:1;
        RBus_UInt32  sap_noise_flag:1;
        RBus_UInt32  sap_lo_refuse:1;
        RBus_UInt32  sap_hi_pass:1;
        RBus_UInt32  w1sapqualitygood:1;
        RBus_UInt32  res1:17;
    };
}btsc_sap_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sap_debounce:4;
        RBus_UInt32  sap_debounce_en:1;
        RBus_UInt32  res1:27;
    };
}btsc_sap_debounce_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  w10fmmagnitude:10;
        RBus_UInt32  res1:2;
        RBus_UInt32  fm_mag_optimize:1;
        RBus_UInt32  fm_mag_overflow:1;
        RBus_UInt32  res2:18;
    };
}btsc_sif_fm_magnitude_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  testoutputselect:4;
        RBus_UInt32  res1:28;
    };
}btsc_test_mux_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy_6424:16;
        RBus_UInt32  res1:16;
    };
}btsc_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pilot_phase_delta:32;
    };
}btsc_pilot_phase_delta_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  locked_i_gain:4;
        RBus_UInt32  locked_p_gain:4;
        RBus_UInt32  unlock_i_gain:4;
        RBus_UInt32  unlock_p_gain:4;
        RBus_UInt32  res1:16;
    };
}phase_error_pi_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  phase_err_threshold:24;
        RBus_UInt32  res1:7;
        RBus_UInt32  sap_hpf_en:1;
    };
}phase_err_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  phase_err_high_threshold:24;
        RBus_UInt32  res1:8;
    };
}phase_err_threshold2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  freq_correction:22;
        RBus_UInt32  res1:10;
    };
}freq_correction_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  average_movement:24;
        RBus_UInt32  res1:8;
    };
}phase_error_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  fm2_deviation_gain:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  fm1_deviation_gain:3;
        RBus_UInt32  res3:12;
        RBus_UInt32  hdv_bpf_sel:2;
        RBus_UInt32  normalize_en:1;
        RBus_UInt32  ultra_hdv_mode:1;
        RBus_UInt32  res4:1;
        RBus_UInt32  de_emphasis_time:2;
        RBus_UInt32  a2_bw_sel:2;
    };
}a2_eiaj_demod_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  noise_sub:10;
        RBus_UInt32  magnitude_sub:10;
        RBus_UInt32  res1:12;
    };
}a2_eiaj_mag_noise_sub_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  noise:10;
        RBus_UInt32  magnitude:10;
        RBus_UInt32  res1:12;
    };
}a2_eiaj_mag_noise_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  rm_4:4;
        RBus_UInt32  rm_5:4;
        RBus_UInt32  rm_6:4;
        RBus_UInt32  rm_7:4;
    };
}mbist_a2_eiaj_demod_rm_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_8:4;
        RBus_UInt32  res1:28;
    };
}mbist_a2_eiaj_demod_rm_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  rme_4:1;
        RBus_UInt32  rme_5:1;
        RBus_UInt32  rme_6:1;
        RBus_UInt32  rme_7:1;
        RBus_UInt32  rme_8:1;
        RBus_UInt32  res1:23;
    };
}mbist_a2_eiaj_demod_rme_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  tr_timing_step:20;
        RBus_UInt32  cr_lpf_ki:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  cr_lpf_kp:3;
        RBus_UInt32  psf_bg_sel:1;
        RBus_UInt32  tr_lpf_kp:3;
        RBus_UInt32  psf_sel:1;
    };
}nicam_demod_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  gain_adjust:6;
        RBus_UInt32  res1:10;
        RBus_UInt32  window_size:10;
        RBus_UInt32  res2:2;
        RBus_UInt32  debounce_cnt:3;
        RBus_UInt32  enable:1;
    };
}nicam_dagc_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  low:16;
        RBus_UInt32  high:16;
    };
}nicam_dagc_threshold_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  magnitude:16;
        RBus_UInt32  res1:16;
    };
}nicam_dagc_mag_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006510_14_0:15;
        RBus_UInt32  level_sel:2;
        RBus_UInt32  de_em_by_pass:1;
        RBus_UInt32  sat_en:1;
        RBus_UInt32  bypass_interpol:1;
        RBus_UInt32  status_debounce_cnt:4;
        RBus_UInt32  res1:1;
        RBus_UInt32  cib_mask:1;
        RBus_UInt32  cib_0:1;
        RBus_UInt32  cib_1:1;
        RBus_UInt32  pcm_r_out_sel:1;
        RBus_UInt32  pcm_l_out_sel:1;
        RBus_UInt32  data_channel_sel:1;
        RBus_UInt32  resample_en:1;
    };
}nicam_decode_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bit_error_rate:12;
        RBus_UInt32  true_detect:1;
        RBus_UInt32  bit_cnt_sync:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  additional_data:11;
        RBus_UInt32  c4:1;
        RBus_UInt32  c1c2c3:3;
        RBus_UInt32  c0:1;
    };
}nicam_decode_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  low_threshold:12;
        RBus_UInt32  high_threshold:12;
        RBus_UInt32  hi_ber_debounce:3;
        RBus_UInt32  analog_flag:1;
        RBus_UInt32  c4_hi_ber:2;
        RBus_UInt32  res1:1;
        RBus_UInt32  enable:1;
    };
}nicam_auto_switch_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ted_error:18;
        RBus_UInt32  res1:2;
        RBus_UInt32  ted_error_threshold:3;
        RBus_UInt32  res2:5;
        RBus_UInt32  duration:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  enable:1;
    };
}nicam_demod_auto_recovery_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  bit_error_rate_r:12;
        RBus_UInt32  bit_error_rate_l:12;
        RBus_UInt32  res1:8;
    };
}nicam_bit_error_rate_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  r_end:6;
        RBus_UInt32  r_start:6;
        RBus_UInt32  l_end:6;
        RBus_UInt32  l_start:6;
        RBus_UInt32  window_en:1;
        RBus_UInt32  res1:7;
    };
}nicam_ber_window_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  down_rate:1;
        RBus_UInt32  downsample_en:1;
        RBus_UInt32  backend_play_en:1;
        RBus_UInt32  res1:13;
        RBus_UInt32  fifo_ch0_source:2;
        RBus_UInt32  fifo_ch1_source:2;
        RBus_UInt32  res2:12;
    };
}down_sample_control_for_playback_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fifo_ch01_sel:4;
        RBus_UInt32  res1:28;
    };
}down_sample_fifo_source_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:14;
        RBus_UInt32  dummy18006558_31_14:18;
    };
}down_sample_mbist_recoding_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}down_sample_fifo_pre_scale_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  res1:16;
    };
}down_sample_mbist_rm_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  res1:28;
    };
}down_sample_mbist_rme_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  down_rate:1;
        RBus_UInt32  downsample_en:1;
        RBus_UInt32  backend_play_en:1;
        RBus_UInt32  res1:9;
        RBus_UInt32  fifo_ch01_sel:4;
        RBus_UInt32  fifo_ch1_source:2;
        RBus_UInt32  fifo_ch0_source:2;
        RBus_UInt32  res2:12;
    };
}down_sample_control_for_ts_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rm_1:4;
        RBus_UInt32  rm_2:4;
        RBus_UInt32  rm_3:4;
        RBus_UInt32  dummy180065a4_31_16:16;
    };
}ts_ds_fifo_mbist_rm_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rme_0:1;
        RBus_UInt32  rme_1:1;
        RBus_UInt32  rme_2:1;
        RBus_UInt32  rme_3:1;
        RBus_UInt32  res1:28;
    };
}ts_ds_fifo_mbist_rme_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rd_intr_dma_status:1;
        RBus_UInt32  wr_intr_dma_status:1;
        RBus_UInt32  unflow_dma_status:1;
        RBus_UInt32  overflow_dma_status:1;
        RBus_UInt32  dma_write_enable:1;
        RBus_UInt32  dma_read_enable:1;
        RBus_UInt32  dma_soft_wr_rst:1;
        RBus_UInt32  dma_soft_rd_rst:1;
        RBus_UInt32  dma_int_en:1;
        RBus_UInt32  int_wr_en:1;
        RBus_UInt32  int_rd_en:1;
        RBus_UInt32  dma_mode:1;
        RBus_UInt32  aodmatype:1;
        RBus_UInt32  rd_channel_no:3;
        RBus_UInt32  aidmatype:1;
        RBus_UInt32  wr_channel_no:3;
        RBus_UInt32  hbr_wr_channel_no:2;
        RBus_UInt32  pcm_random:1;
        RBus_UInt32  output_hold_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ls_on:1;
        RBus_UInt32  dma_r_format:1;
        RBus_UInt32  dma_w_format:1;
        RBus_UInt32  dma_output_src_sel:2;
        RBus_UInt32  dma_wr_src_sel:2;
    };
}adma_csr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  wr_intr_point:15;
        RBus_UInt32  res1:1;
        RBus_UInt32  write_len:15;
        RBus_UInt32  res2:1;
    };
}adma_wconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  wr_start_addr0:26;
    };
}adma_wsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  wr_start_addr1:26;
    };
}adma_wsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  read_intr_point:15;
        RBus_UInt32  res1:1;
        RBus_UInt32  read_len:15;
        RBus_UInt32  res2:1;
    };
}adma_rconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  read_length:15;
        RBus_UInt32  load_rd:1;
        RBus_UInt32  avail_length:15;
        RBus_UInt32  load_wr:1;
    };
}adma_wrconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  rd_start_addr0:26;
    };
}adma_rsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  rd_start_addr1:26;
    };
}adma_rsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  rd_start_addr2:26;
    };
}adma_rsadr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  rd_start_addr3:26;
    };
}adma_rsadr3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rd_buffer_length:15;
        RBus_UInt32  res1:1;
        RBus_UInt32  wr_buffer_length:15;
        RBus_UInt32  res2:1;
    };
}adma_chconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0:4;
        RBus_UInt32  rme_0:1;
        RBus_UInt32  res1:27;
    };
}audio_dma_bist_control_indicate_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_rd_intr_dma_status:1;
        RBus_UInt32  ts_wr_intr_dma_status:1;
        RBus_UInt32  ts_unflow_dma_status:1;
        RBus_UInt32  ts_overflow_dma_status:1;
        RBus_UInt32  ts_dma_write_enable:1;
        RBus_UInt32  ts_dma_read_enable:1;
        RBus_UInt32  ts_dma_soft_wr_rst:1;
        RBus_UInt32  ts_dma_soft_rd_rst:1;
        RBus_UInt32  ts_dma_int_en:1;
        RBus_UInt32  ts_int_wr_en:1;
        RBus_UInt32  ts_int_rd_en:1;
        RBus_UInt32  ts_dma_mode:1;
        RBus_UInt32  ts_aodmatype:1;
        RBus_UInt32  ts_rd_channel_no:3;
        RBus_UInt32  ts_aidmatype:1;
        RBus_UInt32  ts_wr_channel_no:3;
        RBus_UInt32  ts_hbr_wr_channel_no:2;
        RBus_UInt32  ts_pcm_random:1;
        RBus_UInt32  ts_output_hold_en:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_ls_on:1;
        RBus_UInt32  ts_dma_r_format:1;
        RBus_UInt32  ts_dma_w_format:1;
        RBus_UInt32  ts_dma_output_src_sel:2;
        RBus_UInt32  ts_dma_wr_src_sel:2;
    };
}tsadma_csr_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_wr_intr_point:15;
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_write_len:15;
        RBus_UInt32  res2:1;
    };
}ts_adma_wconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  ts_wr_start_addr0:26;
    };
}ts_adma_wsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  ts_wr_start_addr1:26;
    };
}ts_adma_wsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_read_intr_point:15;
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_read_len:15;
        RBus_UInt32  res2:1;
    };
}ts_adma_rconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_read_length:15;
        RBus_UInt32  ts_load_rd:1;
        RBus_UInt32  ts_avail_length:15;
        RBus_UInt32  ts_load_wr:1;
    };
}ts_adma_wrconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  ts_rd_start_addr0:26;
    };
}ts_adma_rsadr0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  ts_rd_start_addr1:26;
    };
}ts_adma_rsadr1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:6;
        RBus_UInt32  ts_rd_start_addr2:26;
    };
}ts_adma_rsadr2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ts_rd_buffer_length:15;
        RBus_UInt32  res1:1;
        RBus_UInt32  ts_wr_buffer_length:15;
        RBus_UInt32  res2:1;
    };
}ts_adma_chconf_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0_ts:4;
        RBus_UInt32  rme_0_ts:1;
        RBus_UInt32  res1:27;
    };
}ts_dma_bist_control_indicate_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  test_dma_over_write:1;
        RBus_UInt32  test_dma_over_read:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  test_dma_ring:1;
        RBus_UInt32  test_dma_in_sel:3;
        RBus_UInt32  test_dma_rw_mode:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  test_dma_en:1;
        RBus_UInt32  res3:19;
    };
}test_dma_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  test_dma_start_addr:20;
        RBus_UInt32  res2:7;
    };
}test_dma_start_address_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  test_dma_stop_addr:20;
        RBus_UInt32  res2:7;
    };
}test_dma_stop_address_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dma_sel:1;
        RBus_UInt32  eco_ifd_inv:1;
        RBus_UInt32  dummy180066ec_31:30;
    };
}test_mode_select_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:5;
        RBus_UInt32  test_dma_cur_addr:20;
        RBus_UInt32  res2:7;
    };
}test_cur_address_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  auto_volenable:1;
        RBus_UInt32  spatial_ctrlenable:1;
        RBus_UInt32  deq_enable:1;
        RBus_UInt32  loud_enable:1;
        RBus_UInt32  dvol_enable:1;
        RBus_UInt32  basic_premium_sel:1;
        RBus_UInt32  avc2_enable:1;
        RBus_UInt32  distortion_enable:1;
        RBus_UInt32  res1:24;
    };
}hw_process_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_up_db:2;
        RBus_UInt32  avc_down_db:2;
        RBus_UInt32  avc_level_min:8;
        RBus_UInt32  avc_level_max:8;
        RBus_UInt32  avc_noise_thre:8;
        RBus_UInt32  avc_noise_gain:2;
        RBus_UInt32  avc_vol_detect:2;
    };
}auto_volume_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_mon_win:12;
        RBus_UInt32  avc_zc_win:12;
        RBus_UInt32  avc_cnt_thre:8;
    };
}avc_volume_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_small_cnt_thre:8;
        RBus_UInt32  avc_small_up_db:2;
        RBus_UInt32  avc_small_down_db:2;
        RBus_UInt32  avc_small_level_min:8;
        RBus_UInt32  avc_small_level_max:8;
        RBus_UInt32  avc1_coef:3;
        RBus_UInt32  avc_vol_amplif_enable:1;
    };
}avc_volume_control_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_small_level:16;
        RBus_UInt32  res1:16;
    };
}avc_volume_control_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  f_coef:9;
        RBus_UInt32  res1:1;
        RBus_UInt32  spatial_in_r_sel:1;
        RBus_UInt32  spatial_in_l_sel:1;
        RBus_UInt32  seb_en:1;
        RBus_UInt32  psb_en:1;
        RBus_UInt32  apf_en:1;
        RBus_UInt32  spatial_zc_apply:1;
        RBus_UInt32  spatial_zc_win:12;
        RBus_UInt32  res2:4;
    };
}spatial_effect_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  depth2:9;
        RBus_UInt32  res1:7;
        RBus_UInt32  depth1:9;
        RBus_UInt32  res2:7;
    };
}spatial_effect_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_hp_a1:16;
        RBus_UInt32  eq_hp_slope:1;
        RBus_UInt32  res1:15;
    };
}eq_hp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_lp_h0:16;
        RBus_UInt32  eq_lp_a1:16;
    };
}eq_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp1_a2:16;
        RBus_UInt32  eq_bp1_a1:16;
    };
}eq_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp1_h0:16;
        RBus_UInt32  res1:16;
    };
}eq_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp2_a2:16;
        RBus_UInt32  eq_bp2_a1:16;
    };
}eq_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp2_h0:16;
        RBus_UInt32  res1:16;
    };
}eq_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp3_a2:16;
        RBus_UInt32  eq_bp3_a1:16;
    };
}eq_bp3_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp3_h0:16;
        RBus_UInt32  res1:16;
    };
}eq_bp3_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp4_a2:16;
        RBus_UInt32  eq_bp4_a1:16;
    };
}eq_bp4_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp4_h0:16;
        RBus_UInt32  res1:16;
    };
}eq_bp4_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp5_a2:16;
        RBus_UInt32  eq_bp5_a1:16;
    };
}eq_bp5_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp5_h0:16;
        RBus_UInt32  res1:16;
    };
}eq_bp5_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp6_a2:16;
        RBus_UInt32  eq_bp6_a1:16;
    };
}eq_bp6_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp6_h0:16;
        RBus_UInt32  res1:16;
    };
}eq_bp6_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp7_a2:16;
        RBus_UInt32  eq_bp7_a1:16;
    };
}eq_bp7_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_bp7_h0:16;
        RBus_UInt32  res1:16;
    };
}eq_bp7_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp8_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp8_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp9_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}eq_bp9_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_hp_enable:1;
        RBus_UInt32  eq_lp_enable:1;
        RBus_UInt32  eq_band1_enable:1;
        RBus_UInt32  eq_band2_enable:1;
        RBus_UInt32  eq_band3_enable:1;
        RBus_UInt32  eq_band4_enable:1;
        RBus_UInt32  eq_band5_enable:1;
        RBus_UInt32  eq_band6_enable:1;
        RBus_UInt32  eq_band7_enable:1;
        RBus_UInt32  res1:23;
    };
}eq_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  eq_hp_of:1;
        RBus_UInt32  eq_lp_of:1;
        RBus_UInt32  eq_band1_of:1;
        RBus_UInt32  eq_band2_of:1;
        RBus_UInt32  eq_band3_of:1;
        RBus_UInt32  eq_band4_of:1;
        RBus_UInt32  eq_band5_of:1;
        RBus_UInt32  eq_band6_of:1;
        RBus_UInt32  eq_band7_of:1;
        RBus_UInt32  res1:23;
    };
}eq_status_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_lp0_h0:16;
        RBus_UInt32  lr_loud_lp0_a1:16;
    };
}lr_loud_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_bp1_a2:16;
        RBus_UInt32  lr_loud_bp1_a1:16;
    };
}lr_loud_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_bp1_h0:16;
        RBus_UInt32  res1:16;
    };
}lr_loud_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_bp2_a2:16;
        RBus_UInt32  lr_loud_bp2_a1:16;
    };
}lr_loud_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lr_loud_bp2_h0:16;
        RBus_UInt32  res1:16;
    };
}lr_loud_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}lsrs_loud_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_lp_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp1_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp1_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp2_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_loud_bp2_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ld_bpf2_en_lr:1;
        RBus_UInt32  ld_bpf1_en_lr:1;
        RBus_UInt32  ld_lpf_en_lr:1;
        RBus_UInt32  res1:29;
    };
}loudness_control_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ld_bpf2_of_lr:1;
        RBus_UInt32  ld_bpf1_of_lr:1;
        RBus_UInt32  ld_lpf_of_lr:1;
        RBus_UInt32  res1:29;
    };
}loudness_status_register_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dvcm:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  zcth:5;
        RBus_UInt32  res2:3;
        RBus_UInt32  reg_zero_in_en:1;
        RBus_UInt32  reg_in_thre:5;
        RBus_UInt32  res3:14;
    };
}digital_volume_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  delay_ctrl_mute:10;
        RBus_UInt32  ramp_step_mute:2;
        RBus_UInt32  zcto_mute:3;
        RBus_UInt32  mute_apply:1;
        RBus_UInt32  delay_ctrl:10;
        RBus_UInt32  ramp_step:2;
        RBus_UInt32  zcto:3;
        RBus_UInt32  dvol_apply:1;
    };
}digital_volume_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vol_r_b:6;
        RBus_UInt32  vol_r_a:5;
        RBus_UInt32  vol_r_ready:1;
        RBus_UInt32  hpf_r_enable:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  rep_r_status:1;
        RBus_UInt32  mute_r:1;
        RBus_UInt32  vol_l_b:6;
        RBus_UInt32  vol_l_a:5;
        RBus_UInt32  vol_l_ready:1;
        RBus_UInt32  hpf_l_enable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  rep_l_status:1;
        RBus_UInt32  mute_l:1;
    };
}lr_digital_volume_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vol_swf_r_b:6;
        RBus_UInt32  vol_swf_r_a:5;
        RBus_UInt32  vol_swf_r_ready:1;
        RBus_UInt32  hpf_swf_r_enable:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  rep_swf_r_status:1;
        RBus_UInt32  mute_swf_r:1;
        RBus_UInt32  vol_swf_l_b:6;
        RBus_UInt32  vol_swf_l_a:5;
        RBus_UInt32  vol_swf_l_ready:1;
        RBus_UInt32  hpf_swf_l_enable:1;
        RBus_UInt32  res2:1;
        RBus_UInt32  rep_swf_l_status:1;
        RBus_UInt32  mute_swf_l:1;
    };
}subwoofer_digital_volume_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}csw_digital_volume_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  double_buffer_ack:1;
        RBus_UInt32  zcto_status:1;
        RBus_UInt32  res1:30;
    };
}double_buffer_ack_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_noise_thre:16;
        RBus_UInt32  avc2_noise_gain:2;
        RBus_UInt32  down_db:2;
        RBus_UInt32  fast_up_db:2;
        RBus_UInt32  slow_up_db:2;
        RBus_UInt32  fast_recov_ctrl:1;
        RBus_UInt32  avc2_vol_detect:2;
        RBus_UInt32  avc2_lpf_coef:3;
        RBus_UInt32  avc2_vol_amplif_enable:1;
        RBus_UInt32  res1:1;
    };
}avc2_control_1_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_mon_win:12;
        RBus_UInt32  avc2_zc_win:12;
        RBus_UInt32  avc2_cnt_thre:8;
    };
}avc2_control_2_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  recov_win_min:8;
        RBus_UInt32  recov_win_max:8;
        RBus_UInt32  res1:16;
    };
}avc2_control_3_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_level_min:16;
        RBus_UInt32  avc2_level_max:16;
    };
}avc2_control_4_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_small_cnt_thre:8;
        RBus_UInt32  avc2_small_down_db:2;
        RBus_UInt32  avc2_small_up_db:2;
        RBus_UInt32  res1:20;
    };
}avc2_control_5_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_small_level_min:16;
        RBus_UInt32  avc2_small_level_max:16;
    };
}avc2_control_6_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc2_small_level:31;
        RBus_UInt32  res1:1;
    };
}avc2_control_7_ch01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_1_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_2_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_3_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_4_ch23_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_1_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_2_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_3_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_4_ch45_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_1_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_2_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_3_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}avc2_control_4_ch67_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:31;
        RBus_UInt32  hw_mixing_sel:1;
    };
}hw_out_trans_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  loudness_ovf:1;
        RBus_UInt32  eq_ovf:1;
        RBus_UInt32  dvol_done:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  dvol_int_en:1;
        RBus_UInt32  loudness_ovf_en:1;
        RBus_UInt32  eq_ovf_en:1;
        RBus_UInt32  res2:14;
    };
}system_int_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_lp_out:24;
        RBus_UInt32  res1:8;
    };
}avc_lp_out_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006818_31_0:32;
    };
}dummy_6718_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1800681c_31_0:32;
    };
}dummy_671c_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ch01_scale_b:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  ch01_scale_a:4;
        RBus_UInt32  res2:24;
    };
}hw_in_pre_scale_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dist_up_db:2;
        RBus_UInt32  dist_down_db:2;
        RBus_UInt32  dist_low_thre:8;
        RBus_UInt32  dist_high_thre:8;
        RBus_UInt32  dist_coef:3;
        RBus_UInt32  res1:7;
        RBus_UInt32  dist_vol_detect:2;
    };
}hw_distortion_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dist_mon_win:12;
        RBus_UInt32  dist_zc_win:12;
        RBus_UInt32  dist_cnt_thre:8;
    };
}hw_distortion_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lrrr_delay_ctrl_mute:10;
        RBus_UInt32  lrrr_ramp_step_mute:2;
        RBus_UInt32  lrrr_zcto_mute:3;
        RBus_UInt32  lrrr_mute_apply:1;
        RBus_UInt32  lrrr_delay_ctrl:10;
        RBus_UInt32  lrrr_ramp_step:2;
        RBus_UInt32  lrrr_zcto:3;
        RBus_UInt32  lrrr_dvol_apply:1;
    };
}lrrr_digital_volume_control_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  lrrr_dvcm:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  lrrr_zcth:5;
        RBus_UInt32  lrrr_zcto_status:1;
        RBus_UInt32  lrrr_dvol_enable:1;
        RBus_UInt32  res2:21;
    };
}lrrr_digital_volume_control_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vol_rr_b:6;
        RBus_UInt32  vol_rr_a:5;
        RBus_UInt32  vol_rr_ready:1;
        RBus_UInt32  hpf_rr_enable:1;
        RBus_UInt32  res1:2;
        RBus_UInt32  mute_rr:1;
        RBus_UInt32  vol_lr_b:6;
        RBus_UInt32  vol_lr_a:5;
        RBus_UInt32  vol_lr_ready:1;
        RBus_UInt32  hpf_lr_enable:1;
        RBus_UInt32  res2:2;
        RBus_UInt32  mute_lr:1;
    };
}lrrr_digital_volume_control_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy1800690c_31_0:32;
    };
}ts_ds_mbist_recoding_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  vol_source_sel:1;
        RBus_UInt32  down_sample_rate:2;
        RBus_UInt32  res1:29;
    };
}dvol_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_ts_mon_win:12;
        RBus_UInt32  avc_ts_zc_win:12;
        RBus_UInt32  avc1_ts_coef:3;
        RBus_UInt32  res1:1;
        RBus_UInt32  avc_vol_ts_detect:2;
        RBus_UInt32  avc_vol_amplif_ts_enable:1;
        RBus_UInt32  auto_vol_ts_enable:1;
    };
}auto_volume_control_ts_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_ts_up_db:2;
        RBus_UInt32  avc_ts_down_db:2;
        RBus_UInt32  avc_ts_level_min:8;
        RBus_UInt32  avc_ts_level_max:8;
        RBus_UInt32  avc_ts_noise_thre:8;
        RBus_UInt32  avc_ts_noise_gain:2;
        RBus_UInt32  reversed:2;
    };
}auto_volume_control_ts_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_ts_small_level:16;
        RBus_UInt32  avc_ts_cnt_thre:8;
        RBus_UInt32  res1:8;
    };
}auto_volume_control_ts_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  avc_ts_small_cnt_thre:8;
        RBus_UInt32  avc_ts_small_up_db:2;
        RBus_UInt32  avc_ts_small_down_db:2;
        RBus_UInt32  avc_ts_small_level_min:8;
        RBus_UInt32  avc_ts_small_level_max:8;
        RBus_UInt32  res1:4;
    };
}auto_volume_control_ts_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  debug_mode_sel:9;
        RBus_UInt32  res1:3;
        RBus_UInt32  sif_adc_in_test_sel:1;
        RBus_UInt32  sif_adc_in_test_en:1;
        RBus_UInt32  res2:18;
    };
}test_pattern_gen_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_crc_header:24;
        RBus_UInt32  res1:8;
    };
}crc_header_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_crc_frame_length:16;
        RBus_UInt32  audio_crc_ch_sel:3;
        RBus_UInt32  audio_crc_en:1;
        RBus_UInt32  res1:12;
    };
}crc_contorl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_crc:24;
        RBus_UInt32  audio_crc_done:1;
        RBus_UInt32  res1:7;
    };
}crc_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  zc_sample_cnt_golden:12;
        RBus_UInt32  zc_sample_cnt_threshold:6;
        RBus_UInt32  res1:2;
        RBus_UInt32  amplitude_low_threshold:2;
        RBus_UInt32  half_sine_num:2;
        RBus_UInt32  auto_chk_result:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  sine_channel_select:3;
        RBus_UInt32  sine_auto_chk_en:1;
    };
}sine_auto_chk_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  zc_sample_cnt:12;
        RBus_UInt32  sine_amplitude:8;
        RBus_UInt32  res1:12;
    };
}sine_wave_value_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy18006a18_31_0:32;
    };
}pattern_gen_dummy_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  to_ack_en:1;
        RBus_UInt32  dummy18006a50_3:3;
        RBus_UInt32  res1:28;
    };
}rbus_ack_ctrl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ack_fail_addr:12;
        RBus_UInt32  ack_fail_rw:1;
        RBus_UInt32  res1:19;
    };
}ack_fail_info_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  en:1;
        RBus_UInt32  sel:2;
        RBus_UInt32  switch_wait_en:1;
        RBus_UInt32  lmute:1;
        RBus_UInt32  rmute:1;
        RBus_UInt32  res1:1;
        RBus_UInt32  wait_en:1;
        RBus_UInt32  bit:3;
        RBus_UInt32  pcm_8ch:1;
        RBus_UInt32  lmute1:1;
        RBus_UInt32  rmute1:1;
        RBus_UInt32  lmute2:1;
        RBus_UInt32  rmute2:1;
        RBus_UInt32  lmute3:1;
        RBus_UInt32  rmute3:1;
        RBus_UInt32  sample_flat:4;
        RBus_UInt32  pkt:1;
        RBus_UInt32  pcmsync:1;
        RBus_UInt32  clk_sel:3;
        RBus_UInt32  res2:5;
    };
}aio_o_hdmi_gctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  fcnt:8;
        RBus_UInt32  realgo:1;
        RBus_UInt32  res1:23;
    };
}aio_o_hdmi_fcnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cs1:32;
    };
}aio_o_hdmi_cs1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  cs2:8;
        RBus_UInt32  res1:24;
    };
}aio_o_hdmi_cs2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  valid:8;
        RBus_UInt32  userdata:8;
        RBus_UInt32  res1:16;
    };
}aio_o_hdmi_info_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  en2:1;
        RBus_UInt32  en3:1;
        RBus_UInt32  en4:1;
        RBus_UInt32  en5:1;
        RBus_UInt32  thd:5;
        RBus_UInt32  emptystopen:1;
        RBus_UInt32  en6:1;
        RBus_UInt32  en7:1;
        RBus_UInt32  en8:1;
        RBus_UInt32  en9:1;
        RBus_UInt32  en10:1;
        RBus_UInt32  res2:15;
    };
}aio_o_fifoctl_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  empty3:1;
        RBus_UInt32  empty4:1;
        RBus_UInt32  empty5:1;
        RBus_UInt32  empty6:1;
        RBus_UInt32  empty7:1;
        RBus_UInt32  empty8:1;
        RBus_UInt32  empty9:1;
        RBus_UInt32  empty10:1;
        RBus_UInt32  empty11:1;
        RBus_UInt32  res2:20;
    };
}aio_o_fifo_status_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_sa_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_ea_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_rp_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_0_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_3_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_4_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_5_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_6_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  addr:28;
        RBus_UInt32  res2:1;
    };
}aio_o_wp_7_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  gohdmi:1;
        RBus_UInt32  res2:29;
    };
}aio_o_go_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:2;
        RBus_UInt32  pause2:1;
        RBus_UInt32  res2:29;
    };
}aio_o_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  thd:28;
        RBus_UInt32  res2:1;
    };
}aio_o_hdmi_ddrthd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  count:32;
    };
}aio_o_hdmi_timcnt_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  thd:32;
    };
}aio_o_hdmi_timthd_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  hdmio:1;
        RBus_UInt32  aodma:1;
        RBus_UInt32  dummy18006db0_31:30;
    };
}aio_gating_en_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  fifointe3:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  draminte3:1;
        RBus_UInt32  hdmithdinte:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  hdmitiminte:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  fifointe4:1;
        RBus_UInt32  fifointe5:1;
        RBus_UInt32  fifointe6:1;
        RBus_UInt32  fifointe7:1;
        RBus_UInt32  fifointe8:1;
        RBus_UInt32  fifointe9:1;
        RBus_UInt32  fifointe10:1;
        RBus_UInt32  fifointe11:1;
        RBus_UInt32  draminte4:1;
        RBus_UInt32  draminte5:1;
        RBus_UInt32  draminte6:1;
        RBus_UInt32  draminte7:1;
        RBus_UInt32  draminte8:1;
        RBus_UInt32  draminte9:1;
        RBus_UInt32  draminte10:1;
        RBus_UInt32  draminte11:1;
        RBus_UInt32  res5:1;
    };
}aio_o_inte_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:4;
        RBus_UInt32  fifoints3:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  dramints3:1;
        RBus_UInt32  hdmithdints:1;
        RBus_UInt32  res3:2;
        RBus_UInt32  hdmitimints:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  fifoints4:1;
        RBus_UInt32  fifoints5:1;
        RBus_UInt32  fifoints6:1;
        RBus_UInt32  fifoints7:1;
        RBus_UInt32  fifoints8:1;
        RBus_UInt32  fifoints9:1;
        RBus_UInt32  fifoints10:1;
        RBus_UInt32  fifoints11:1;
        RBus_UInt32  dramints4:1;
        RBus_UInt32  dramints5:1;
        RBus_UInt32  dramints6:1;
        RBus_UInt32  dramints7:1;
        RBus_UInt32  dramints8:1;
        RBus_UInt32  dramints9:1;
        RBus_UInt32  dramints10:1;
        RBus_UInt32  dramints11:1;
        RBus_UInt32  res5:1;
    };
}aio_o_ints_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  pcm_source_sel:4;
        RBus_UInt32  dma_pcm_sel:1;
        RBus_UInt32  rme:1;
        RBus_UInt32  rm:4;
        RBus_UInt32  ao_dma_ls_en:1;
        RBus_UInt32  res1:21;
    };
}aio_hdmi_out_source_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_bist_mode_msd:1;
        RBus_UInt32  audio_bist_mode_am:1;
        RBus_UInt32  audio_bist_mode_a2_eiaj:1;
        RBus_UInt32  audio_bist_mode_dma:1;
        RBus_UInt32  audio_bist_mode_dma_ts:1;
        RBus_UInt32  audio_bist_mode_dac:1;
        RBus_UInt32  audio_bist_mode_adc:1;
        RBus_UInt32  audio_bist_mode_ds:1;
        RBus_UInt32  audio_bist_mode_ts_ds:1;
        RBus_UInt32  audio_bist_mode_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_bist_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_bist_done_msd:1;
        RBus_UInt32  audio_bist_done_am:1;
        RBus_UInt32  audio_bist_done_a2_eiaj:1;
        RBus_UInt32  audio_bist_done_dma:1;
        RBus_UInt32  audio_bist_done_dma_ts:1;
        RBus_UInt32  audio_bist_done_dac:1;
        RBus_UInt32  audio_bist_done_adc:1;
        RBus_UInt32  audio_bist_done_ds:1;
        RBus_UInt32  audio_bist_done_ts_ds:1;
        RBus_UInt32  audio_bist_done_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_bist_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_bist_fail_group_msd:1;
        RBus_UInt32  audio_bist_fail_group_am:1;
        RBus_UInt32  audio_bist_fail_group_a2_eiaj:1;
        RBus_UInt32  audio_bist_fail_group_dma:1;
        RBus_UInt32  audio_bist_fail_group_dma_ts:1;
        RBus_UInt32  audio_bist_fail_group_dac:1;
        RBus_UInt32  audio_bist_fail_group_adc:1;
        RBus_UInt32  audio_bist_fail_group_ds:1;
        RBus_UInt32  audio_bist_fail_group_ts_ds:1;
        RBus_UInt32  audio_bist_fail_group_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_bist_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_bist_a2_eiaj_fail_0:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_1:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_2:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_3:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_4:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_5:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_6:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_7:1;
        RBus_UInt32  audio_bist_a2_eiaj_fail_8:1;
        RBus_UInt32  audio_bist_down_fail_0:1;
        RBus_UInt32  audio_bist_down_fail_1:1;
        RBus_UInt32  audio_bist_down_fail_2:1;
        RBus_UInt32  audio_bist_down_fail_3:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  audio_bist_down_ts_fail_0:1;
        RBus_UInt32  audio_bist_down_ts_fail_1:1;
        RBus_UInt32  audio_bist_down_ts_fail_2:1;
        RBus_UInt32  audio_bist_down_ts_fail_3:1;
        RBus_UInt32  audio_bist_dac_fail_0:1;
        RBus_UInt32  audio_bist_dac_fail_1:1;
        RBus_UInt32  res2:1;
    };
}audio_bist_a2_eiaj_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_drf_mode_msd:1;
        RBus_UInt32  audio_drf_mode_am:1;
        RBus_UInt32  audio_drf_mode_a2_eiaj:1;
        RBus_UInt32  audio_drf_mode_dma:1;
        RBus_UInt32  audio_drf_mode_dma_ts:1;
        RBus_UInt32  audio_drf_mode_dac:1;
        RBus_UInt32  audio_drf_mode_adc:1;
        RBus_UInt32  audio_drf_mode_ds:1;
        RBus_UInt32  audio_drf_mode_ts_ds:1;
        RBus_UInt32  audio_drf_mode_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_drf_mode_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_drf_resume_msd:1;
        RBus_UInt32  audio_drf_resume_am:1;
        RBus_UInt32  audio_drf_resume_a2_eiaj:1;
        RBus_UInt32  audio_drf_resume_dma:1;
        RBus_UInt32  audio_drf_resume_dma_ts:1;
        RBus_UInt32  audio_drf_resume_dac:1;
        RBus_UInt32  audio_drf_resume_adc:1;
        RBus_UInt32  audio_drf_resume_ds:1;
        RBus_UInt32  audio_drf_resume_ts_ds:1;
        RBus_UInt32  audio_drf_resume_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_drf_resume_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_drf_done_msd:1;
        RBus_UInt32  audio_drf_done_am:1;
        RBus_UInt32  audio_drf_done_a2_eiaj:1;
        RBus_UInt32  audio_drf_done_dma:1;
        RBus_UInt32  audio_drf_done_dma_ts:1;
        RBus_UInt32  audio_drf_done_dac:1;
        RBus_UInt32  audio_drf_done_adc:1;
        RBus_UInt32  audio_drf_done_ds:1;
        RBus_UInt32  audio_drf_done_ts_ds:1;
        RBus_UInt32  audio_drf_done_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_drf_done_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_drf_pause_msd:1;
        RBus_UInt32  audio_drf_pause_am:1;
        RBus_UInt32  audio_drf_pause_a2_eiaj:1;
        RBus_UInt32  audio_drf_pause_dma:1;
        RBus_UInt32  audio_drf_pause_dma_ts:1;
        RBus_UInt32  audio_drf_pause_dac:1;
        RBus_UInt32  audio_drf_pause_adc:1;
        RBus_UInt32  audio_drf_pause_ds:1;
        RBus_UInt32  audio_drf_pause_ts_ds:1;
        RBus_UInt32  audio_drf_pause_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_drf_pause_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_drf_fail_group_msd:1;
        RBus_UInt32  audio_drf_fail_group_am:1;
        RBus_UInt32  audio_drf_fail_group_a2_eiaj:1;
        RBus_UInt32  audio_drf_fail_group_dma:1;
        RBus_UInt32  audio_drf_fail_group_dma_ts:1;
        RBus_UInt32  audio_drf_fail_group_dac:1;
        RBus_UInt32  audio_drf_fail_group_adc:1;
        RBus_UInt32  audio_drf_fail_group_ds:1;
        RBus_UInt32  audio_drf_fail_group_ts_ds:1;
        RBus_UInt32  audio_drf_fail_group_ao_dma:1;
        RBus_UInt32  res1:22;
    };
}audio_drf_fail_group_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  audio_drf_a2_eiaj_fail_0:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_1:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_2:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_3:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_4:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_5:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_6:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_7:1;
        RBus_UInt32  audio_drf_a2_eiaj_fail_8:1;
        RBus_UInt32  audio_drf_down_fail_0:1;
        RBus_UInt32  audio_drf_down_fail_1:1;
        RBus_UInt32  audio_drf_down_fail_2:1;
        RBus_UInt32  audio_drf_down_fail_3:1;
        RBus_UInt32  res1:12;
        RBus_UInt32  audio_drf_down_ts_fail_0:1;
        RBus_UInt32  audio_drf_down_ts_fail_1:1;
        RBus_UInt32  audio_drf_down_ts_fail_2:1;
        RBus_UInt32  audio_drf_down_ts_fail_3:1;
        RBus_UInt32  audio_drf_dac_fail_0:1;
        RBus_UInt32  audio_drf_dac_fail_1:1;
        RBus_UInt32  res2:1;
    };
}audio_drf_a2_eiaj_fail_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  ad_gain_r:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  ad_gain_l:7;
        RBus_UInt32  res2:1;
        RBus_UInt32  ad_mute_r:1;
        RBus_UInt32  ad_mute_l:1;
        RBus_UInt32  ad_lp_sel:1;
        RBus_UInt32  adc_src_lpf_disable:1;
        RBus_UInt32  ad_zdet_func:2;
        RBus_UInt32  ad_zdet_tout:2;
        RBus_UInt32  ad_comp_gain:3;
        RBus_UInt32  ad_hpf_en:1;
        RBus_UInt32  src_ad_lpf1st_fc_sel:2;
        RBus_UInt32  src_op_sel:1;
        RBus_UInt32  daad_lp_en:1;
    };
}ad_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  da0_gain_r:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  da0_gain_l:7;
        RBus_UInt32  res2:3;
        RBus_UInt32  da0_fifo_full:1;
        RBus_UInt32  da0_fifo_empty:1;
        RBus_UInt32  da0_zdet_func:2;
        RBus_UInt32  da0_zdet_tout:2;
        RBus_UInt32  da0_dither_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  da0_hpf_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  src_en_0:1;
        RBus_UInt32  adda_lp_en_0:1;
    };
}da0_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  da1_gain_r:7;
        RBus_UInt32  res1:1;
        RBus_UInt32  da1_gain_l:7;
        RBus_UInt32  res2:3;
        RBus_UInt32  da1_fifo_full:1;
        RBus_UInt32  da1_fifo_empty:1;
        RBus_UInt32  da1_zdet_func:2;
        RBus_UInt32  da1_zdet_tout:2;
        RBus_UInt32  da1_dither_sel:2;
        RBus_UInt32  res3:1;
        RBus_UInt32  da1_hpf_en:1;
        RBus_UInt32  res4:2;
        RBus_UInt32  src_en_1:1;
        RBus_UInt32  adda_lp_en_1:1;
    };
}da1_asrc_ip_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dac0_pcm_source_sel:3;
        RBus_UInt32  dac0_hw_out_limiter:7;
        RBus_UInt32  dac0_hw_out_limiter_en:1;
        RBus_UInt32  dac0_hw_r_inverter_en:1;
        RBus_UInt32  dac0_hw_l_inverter_en:1;
        RBus_UInt32  dac1_swap_sel:2;
        RBus_UInt32  dac0_swap_sel:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  dac1_pcm_source_sel:3;
        RBus_UInt32  dac1_hw_out_limiter:7;
        RBus_UInt32  dac1_hw_out_limiter_en:1;
        RBus_UInt32  dac1_hw_r_inverter_en:1;
        RBus_UInt32  dac1_hw_l_inverter_en:1;
    };
}dac0_1_src_sel_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_bb_adcsel:1;
        RBus_UInt32  reg_bb_aio2_gselr:3;
        RBus_UInt32  res2:1;
        RBus_UInt32  reg_bb_aio2_gsell:3;
        RBus_UInt32  res3:1;
        RBus_UInt32  reg_bb_aio2_engr:1;
        RBus_UInt32  reg_bb_aio2_engl:1;
        RBus_UInt32  reg_bb_aio2_encopy:2;
        RBus_UInt32  reg_bb_aio1_gselr:3;
        RBus_UInt32  res4:1;
        RBus_UInt32  reg_bb_aio1_gsell:3;
        RBus_UInt32  res5:1;
        RBus_UInt32  reg_bb_aio1_engr:1;
        RBus_UInt32  reg_bb_aio1_engl:1;
        RBus_UInt32  reg_bb_aio1_encopy:2;
        RBus_UInt32  reg_bb_hpo_encopy:2;
        RBus_UInt32  res6:2;
    };
}analog_out_copy_swap_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bb_adcfe_mute_r:6;
        RBus_UInt32  reg_bb_adcfe_mute_l:6;
        RBus_UInt32  res1:4;
        RBus_UInt32  reg_bb_aio2_muter:4;
        RBus_UInt32  reg_bb_aio2_mutel:4;
        RBus_UInt32  reg_bb_aio1_muter:4;
        RBus_UInt32  reg_bb_aio1_mutel:4;
    };
}analog_frontend_mute_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bb_hpo_muter:5;
        RBus_UInt32  reg_bb_hpo_mutel:5;
        RBus_UInt32  res1:22;
    };
}analog_aio_hpout_lineout_l_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}analog_aio_hpout_lineout_r_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bb_adcfe_gselr:2;
        RBus_UInt32  reg_bb_adcfe_gsell:2;
        RBus_UInt32  res1:28;
    };
}adc_volume_gain_control_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_bb_powhpo:1;
        RBus_UInt32  reg_bb_powdf2se:2;
        RBus_UInt32  reg_bb_powvref:1;
        RBus_UInt32  reg_bb_powmbias:1;
        RBus_UInt32  reg_bb_powdac:2;
        RBus_UInt32  reg_bb_powadc:2;
        RBus_UInt32  reg_bb_powadcfe:1;
        RBus_UInt32  reg_bb_powaio2:1;
        RBus_UInt32  reg_bb_powaio1:1;
        RBus_UInt32  res2:17;
    };
}analog_power_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  afe_pga_vol:9;
        RBus_UInt32  res1:23;
    };
}analog_pga_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bb_isel_adcaa:2;
        RBus_UInt32  reg_bb_isel_adccomp:2;
        RBus_UInt32  reg_bb_isel_adcfe:2;
        RBus_UInt32  reg_bb_isel_adcref:2;
        RBus_UInt32  reg_bb_isel_adcst1:2;
        RBus_UInt32  reg_bb_isel_adcst2:2;
        RBus_UInt32  res1:2;
        RBus_UInt32  reg_bb_isel_dacop:2;
        RBus_UInt32  reg_bb_isel_dacref:2;
        RBus_UInt32  reg_bb_isel_depop:2;
        RBus_UInt32  reg_bb_isel_df2se:2;
        RBus_UInt32  reg_bb_isel_hpo:2;
        RBus_UInt32  reg_bb_isel_aio2:2;
        RBus_UInt32  reg_bb_isel_aio1:2;
        RBus_UInt32  reg_bb_isel_vref:2;
        RBus_UInt32  res2:2;
    };
}analog_ci01_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bb_vref_vrefsel:2;
        RBus_UInt32  reg_bb_adc_fset:1;
        RBus_UInt32  reg_bb_adc_ckxen:1;
        RBus_UInt32  reg_bb_adc_refset:1;
        RBus_UInt32  res1:27;
    };
}analog_ci02_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  dummy_692c:32;
    };
}analog_dummy2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  sel_bb_ck_depop:3;
        RBus_UInt32  bb_ck_depop_en:1;
        RBus_UInt32  reg_bb_dpramp_enramp:1;
        RBus_UInt32  res1:27;
    };
}analog_depop1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:3;
        RBus_UInt32  reg_bb_hpo_normal:1;
        RBus_UInt32  reg_bb_dpramp_csel:2;
        RBus_UInt32  reg_bb_powdepop:1;
        RBus_UInt32  reg_bb_aio1_normal:1;
        RBus_UInt32  reg_bb_aio2_normal:1;
        RBus_UInt32  res2:23;
    };
}analog_depop2_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  reg_bb_hpo_gselr:2;
        RBus_UInt32  reg_bb_hpo_gsell:2;
        RBus_UInt32  res1:20;
        RBus_UInt32  reg_bb_hpo_engr:1;
        RBus_UInt32  reg_bb_hpo_engl:1;
        RBus_UInt32  res2:6;
    };
}analog_post_gain_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  rm_0_adc:4;
        RBus_UInt32  rme_0_adc:1;
        RBus_UInt32  res1:3;
        RBus_UInt32  rm_0_dac:4;
        RBus_UInt32  rme_0_dac:1;
        RBus_UInt32  res2:3;
        RBus_UInt32  rm_1_dac:4;
        RBus_UInt32  rme_1_dac:1;
        RBus_UInt32  res3:11;
    };
}drf_bist_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}amic1_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}analog_capless_lineout_depop_RBUS;

typedef union
{
    RBus_UInt32 regValue;
    struct{
        RBus_UInt32  res1:32;
    };
}analog_capless_lineout_control_RBUS;




#endif 


#endif 

