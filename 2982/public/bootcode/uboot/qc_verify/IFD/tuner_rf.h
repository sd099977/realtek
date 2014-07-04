/*=============================================
  * Copyright (c)      Realtek Semiconductor Corporation, 2005
  * All rights reserved.
  * ============================================ */

/*================= File Description ================= */
/**
 * @file
 * The file is a declaration and definition header file
 *
 * @author 	$Author:  $
 * @date 	$Date:  $
 * @version 	$Revision:  $
 * @ingroup
 */

#ifndef _TUNER_RF_H
#define _TUNER_RF_H

#ifdef __cplusplus
extern "C" {
#endif

//#include "../include/ifd/tuner_atv_base.h"
#include "tuner_atv_base.h"//by Lee



//-------------------------------------------------------------
// Global Variables
//-------------------------------------------------------------
#define SECAM_LA_FREQ_OFFSET -58000
//-------------------------------------------------------------
// Core Function
//-------------------------------------------------------------
void BuildRFTuner(ATV_TUNER_MODULE **ppTuner,
	ATV_TUNER_MODULE *pTunerModuleMemory,
	SYS_MODULE *pSysModuleMemory,
	I2C_MODULE *pI2cModuleMemory,
	UINT8 DeviceAddr,
	UINT32 CrystalFreqHz,
	UINT32 RfFreqHz_Max,
	UINT32 RfFreqHz_Min,
	UINT8 UnitNo,
	UINT8 IfOutputVppMode);
/*=============================================================*/
/**
	This routine will set init.
	@param			
	@return 			
*/

UINT8 RFTunerInit(ATV_TUNER_MODULE *pTuner);
/*=============================================================*/
/**
	This routine will get tuner type.
	@param			
	@return 			
*/
void RFTunerGetTunerType(ATV_TUNER_MODULE *pTuner, UINT8 *pTunerType);
/*=============================================================*/
/**
	This routine will get device address.
	@param			
	@return 			
*/
void RFTunerGetDeviceAddress(ATV_TUNER_MODULE *pTuner, UINT8 *pDeviceAddr);
/*=============================================================*/
/**
	This routine will set TV to specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/

UINT8 RFTunerSetFreq(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz);
/*=============================================================*/
/**
	This routine will set TV to specific frequency  in Search mode
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 RFTunerSetFreqSearch(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz);
/*=============================================================*/
/**
	This routine will get TV to current frequency.
	@param			void
	@return 			Return the freq	frequency
*/
UINT8 RFTunerGetFreq(ATV_TUNER_MODULE *pTuner, UINT32 *pRfFreqHz);
/*=============================================================*/
/**
	This routine will get TV to current frequency.
	@param			void
	@return 			Return the freq	frequency
*/

UINT8 RFTunerGetFreqSearch(ATV_TUNER_MODULE *pTuner, UINT32 *pRfFreqHz);
/*=============================================================*/
/**
	This routine will set TV standard mode
	@param			video_mode/audio_mode		TUNER_ATV_VIDEO_MODE/TUNER_ATV_AUDIO_MODE
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 RFTunerSetStandardMode(ATV_TUNER_MODULE *pTuner, TUNER_ATV_VIDEO_MODE video_mode, TUNER_ATV_AUDIO_MODE audio_mode);
/*=============================================================*/
/**
	This routine will get TV standard mode
	@param			none
	@return 			Return video_mode/audio_mode		TUNER_ATV_VIDEO_MODE/TUNER_ATV_AUDIO_MODE
*/
UINT8 RFTunerGetStandardMode(ATV_TUNER_MODULE *pTuner, TUNER_ATV_VIDEO_MODE* video_mode, TUNER_ATV_AUDIO_MODE* audio_mode);
/*=============================================================*/
/**
	This routine will get divider ratio for specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
UINT8 RFTunerGetDiverRatio(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz, UINT16 *DiverRatio);
/*=============================================================*/
/**
	This routine will check tuner receiving frequency band(VHF Low¡BVHF High¡BUHF).
	@param 			freq	       					tuner receiving frequency(divider)
	@return 			Return tuner receiving frequency band(01¡B02 or 04)
*/
UINT8 RFTunerCheckBand(ATV_TUNER_MODULE *pTuner, UINT32 RfFreqHz, UINT8 *Band);

/*=============================================================*/
UINT32 RFTunerNToFrequencyNum(UINT16 N);
/*=============== Read Tuner I2C data ===========================*/
UINT8 RFTunerReadStatus(ATV_TUNER_MODULE *pTuner);
/*=============================================================*/
UINT8 RFTunerGetRatioInStepSize(ATV_TUNER_MODULE *pTuner, UINT16 *RatioInStepSize);
/*=============================================================*/
UINT8 RFTunerGetPictureInterFreq(ATV_TUNER_MODULE *pTuner, UINT32 *pIfFreqHz);
/*=============================================================*/
UINT32 RFTunerGetChanelMaxFreq(void);
/*=============================================================*/
UINT32 RFTunerGetChanelMinFreq(void);
/*=============================================================*/
UINT32 RFTunerGetVHF_LowFreq(void);
/*=============================================================*/
UINT32 RFTunerGetVHF_HighFreq(void);

#ifdef __cplusplus
}
#endif


#endif
/**
 *
 * @}
 */
