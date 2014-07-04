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

 /**
 * @addtogroup
 * @
 */
#ifndef _TUNER_H
#define _TUNER_H
#include "qc_verify.h"



#define IFD_TUNER_BAND_MAX 24
#define IFD_TUNER_REG_MAX 4
#define IFD_TUNER_REG_BAND_MAX IFD_TUNER_BAND_MAX*IFD_TUNER_REG_MAX


typedef struct {
	UINT8	tunerI2C_ADD;
	UINT32	tunerMinFreq;
	UINT32	tunerVHF_LowFreq;
	UINT32	tunerVHF_HighFreq;
	UINT32	tunerMaxFreq;
	UINT32	tunerPIF;
	UINT32	tunerPIF_MN;
	UINT32 	tunerPIF_B;
	UINT32	tunerPIF_GH;
	UINT32	tunerPIF_I;
	UINT32	tunerPIF_DK;
	UINT32	tunerPIF_L;
	UINT32	tunerPIF_LA;
	UINT32	tunerPIF_SCAN;
	bool	tunerIFType;
	UINT32	tunerRATIOStepSize;
	UINT32	tunerBandFreq[IFD_TUNER_BAND_MAX];
	UINT8	tunerRegisterByte[IFD_TUNER_REG_BAND_MAX];
	UINT8	tunerRegisterByteSearch[IFD_TUNER_REG_BAND_MAX];
	UINT8	tunerRfInputSwitchUsedTag;
	UINT8	tunerRfInputByte;
	UINT8	tunerRfInputLocation;
	UINT8	tunerFLStatusBit;
	UINT8	tunerBandNo;
	UINT8	tunerRegNoPerBand;
	UINT8	tunerUsedTag;
	UINT8	tunerAGCtype;
	UINT8	tunerAGCpolarity;
	UINT8	tunerType;
	UINT32	tunerSpecificTag;
	UINT8	tunerID;
	//ATV_TUNER_MODULE *pTuner;
} StructTunerDataType;


typedef enum _TUNER_ID {
	TUNER_NULL = 0,	
	TUNER_SHARP_2403,
	TUNER_SHARP_2403_DIF,
	TUNER_XUGUANG_HFT3_86H_115CW,
}TUNER_ID;


/*==================== Definitions ================ */

void CTunerInit(void);
UINT8 CTunerSetFreq(UINT32 freq);
UINT8 CTunerSetFreqSearch(UINT32 freq);
UINT16 CTunerGeDiverRatio(UINT32 freq);
UINT8 CTunerCheckBand(UINT32 freq);
UINT32 CTunerNToFrequencyNum(UINT16 N);
UINT32 CTunerGetRatioInStepSize(void);
UINT32 CTunerGetPictureInterFreq(void);
UINT32 CTunerGetChanelMaxFreq(void);
UINT32 CTunerGetChanelMinFreq(void);
UINT32 CTunerGetVHF_LowFreq(void);
UINT32 CTunerGetVHF_HighFreq(void);
UINT8 CTunerGetTunerType(void);


typedef struct I2C_MODULE_TAG I2C_MODULE;

typedef enum {
	I2C_NOADDR=0,
	I2C_ADDR_8=1,
	I2C_ADDR_16=2,
} I2C_ADDR_TYPE;

struct I2C_MODULE_TAG
{
	UINT8 master_id;
	UINT8 device_id;
	UINT16 slave_addr;
	UINT8 len;
	UINT8 addrtype;//0: no addr 1: 8bit 2:16bit
};



#endif // #ifdef _TUNER_H


#if 0
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

 /**
 * @addtogroup
 * @
 */
#ifndef _TUNER_H
#define _TUNER_H
#include "qc_verify.h"

/*==================== Definitions ================ */



//void drv_tuner_TunerAudioStdInit(UINT8 mode);
//UINT8 drv_tuner_SetFreq(UINT32 freq);
//UINT8 drv_tuner_CheckBand(UINT32 freq);
//UINT32 drv_tuner_GetChanelMaxFreq(void);
//UINT32 drv_tuner_GetChanelMinFreq(void);

//UINT16 drv_tuner_GeDiverRatio(UINT32 freq);
//UINT32 drv_tuner_GetRatioInStepSize(void);

//UINT32 drv_tuner_GetPictureInterFreq(void);


UINT8 CTunerSetFreq(UINT32 freq);

UINT16 CTunerGeDiverRatio(UINT32 freq);

UINT8 CTunerCheckBand(UINT32 freq);

UINT32 CTunerNToFrequencyNum(UINT16 N);

UINT32 CTunerGetRatioInStepSize(void);

UINT32 CTunerGetPictureInterFreq(void);

UINT32 CTunerGetChanelMaxFreq(void);

UINT32 CTunerGetChanelMinFreq(void);

UINT32 CTunerGetVHF_LowFreq(void);
UINT32 CTunerGetVHF_HighFreq(void);


#endif // #ifdef _TUNER_H
#endif
