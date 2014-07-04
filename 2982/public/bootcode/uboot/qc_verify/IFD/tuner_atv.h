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

#ifndef _TUNER_ATV_H
#define _TUNER_ATV_H

#ifdef __cplusplus
extern "C" {
#endif

#if 0
//#include <rtd_types.h>
#ifndef UINT8
typedef  unsigned char UINT8;
#endif
#ifndef UINT16
typedef  unsigned short UINT16;
#endif
#ifndef UINT32
typedef  unsigned int UINT32;
#endif
//#ifndef bool
//typedef int bool;
//#endif
#endif

#define Set_ActiveTunerID(x)					(gTunerActiveID=x)
#define Get_ActiveTunerID()					(gTunerActiveID)



#define _TUNER_NUM	1

//Please update to tuner_name_table@ifd_factorymode.cpp
typedef enum _TUNER_ID {
	TUNER_NULL = 0,
	TUNER_XUGUANG_DFT_96H_116CW_DIF,
	TUNER_XUGUANG_TDQ6K_T116CW,
	TUNER_XUGUANG_TDQ_6FT_W116H,
	TUNER_XUGUANG_TDQ_6FT_W116H_BJT,
	TUNER_XUGUANG_TDQ_6ID_GW115HR,
	TUNER_XUGUANG_TDQ_6ID_GW115HR_BJT,
	TUNER_XUGUANG_TDQ_6PD_LW115CWADC,
	TUNER_XUGUANG_HFT_98H_115CW_BJT,
	TUNER_XUGUANG_HFT3_86H_115CW_BJT,
	TUNER_XUGUANG_TDQ_B6_116H_BJT,
	TUNER_XUGUANG_HFT8B_115CW,
	TUNER_XUGUANG_HFT3_86H_115CW,
	TUNER_XUGUANG_HFT8B1_V116CW_BJT,
	TUNER_XUGUANG_DVT_8ADC1_T41F0HS,
	TUNER_XUGUANG_DVT_8ADC1_W41F9,
	TUNER_XUGUANG_DMCT_6A111S_BJT,
	TUNER_XUGUANG_HFT2_8F_115CW,
	TUNER_XUGUANG_HFT_86H_115HR,
	TUNER_ALPS_TDAG4_D01A,
	TUNER_ALPS_TDAU3XD01A,
	TUNER_LG_TDTK_C842D_DIF,
	TUNER_LG_TDTC_G29D,
	TUNER_LG_TDTK_H801F,
	TUNER_LG_TDTR_T032D,          
	TUNER_LG_TDTR_T032D_DIF,
	TUNER_KEH_FTDC3S20V04,
	TUNER_KEH_FTDC3S20V04_BJT2,
	TUNER_KEH_FTDC3S20BV04,
	TUNER_KEH_FTDC3S20BV04_BJT,
	TUNER_KEH_FTDC3S20BV04_BJT2,
	TUNER_KEH_TDQ_6FT_W116H_BJT,
	TUNER_TCL_F17CT_2DA_E,
	TUNER_TCL_F25WT_13NXR_E,
	TUNER_TCL_F25WT_13NXR_E_BJT2,
	TUNER_TCL_F25WT_3DXR_E,
	TUNER_TCL_F25WT_3DXR_E_BJT2,
	TUNER_TCL_F25WT_3BXR_E_BJT2,
	TUNER_TCL_F41CT_2_E,
	TUNER_TCL_F41CT_2_E_BJT,
	TUNER_TCL_F41CT_2_E_TIamp,
	TUNER_TCL_F41CT_2B_E,
	TUNER_TCL_F21WT_3DKR_BJT,
	TUNER_TCL_F41CT_6N_E,
	TUNER_TCL_F41CT_6N_E_BJT,
	TUNER_TCL_F86WT_2_E_BJT,
	TUNER_TCL_F86WT_17_E_DIF,
	TUNER_TCL_F86WT_13N_E_BJT,
	TUNER_TCL_DA89CT_6_E_BJT,
	TUNER_TCL_F35CT_6N_E_BJT,
	TUNER_TCL_F35CT_2_E_BJT,
	TUNER_TCL_F13WP_2DP_E,
	TUNER_TCL_DTC86WT_2_E_DIF,
	TUNER_LINGHUA_TDP_1H1E,
	TUNER_LINGHUA_TDP_1H1E_BJT,
	TUNER_LINGHUA_TDP_2A1RE_BJT,
	TUNER_QINGJIA_AFT7_W000G,
	TUNER_QINGJIA_AFT7_W305G,
	TUNER_CDT_3FC2I2,
	TUNER_CDT_3FC2I2_BJT,
	TUNER_SHARP_2403,
	TUNER_SHARP_2403_BJT,
	TUNER_SHARP_2403_DIF,
	TUNER_SHARP_2406,
	TUNER_SHARP_8402,
	TUNER_CHANGHONG_DTI1_E4I12VH,
	TUNER_CHANGHONG_TAF8_C4I13VH,   
	TUNER_CHANGHONG_TAF8_C4I13VH_BJT,	
	TUNER_NUTUNE_TH2603_BJT,
	TUNER_NUTUNE_FH2608,
	TUNER_NUTUNE_FA2333_RFAGC,
	TUNER_NUTUNE_TT2124,	
	TUNER_PANASONIC_ENV56XXXD8F,
	TUNER_PANASONIC_ENV56XXXD8F_RFAGC,
	TUNER_GDC_ET_9K2E_C01WK,
	TUNER_NXP_TDA18272,
	TUNER_NXP_TDA18273,
	TUNER_RAFAEL_RT810,
	TUNER_SONY_RX201,
	TUNER_MAXLINEAR_MXL301RF,
	TUNER_MAXIM_MAX3543,
	TUNER_XCEIVE_XC5200,
	TUNER_ENTR_EN402X,
	TUNER_FRESCO_FM2150,
	TUNER_SILICONLABS_SI2156,
}TUNER_ID;

//=================================================================
//structure of TV tuner
//=================================================================

//struct _StructTunerObject;
//typedef struct _StructTunerObject StructTunerObject;

//struct _StructTunerObject {
//	UINT8 	addr;
//	UINT8 	if_addr;
//	void 	(*Init)(void);
//	UINT8	(*IsLocked)(UINT8 *afc);
//	UINT8 	(*SetFreq)(UINT32 freq);
//	INT32 	(*GetAFCOffset)(UINT8 afc);
//};
//extern StructTunerObject ObjTuner[];

//=================================================================
//Driver
//=================================================================
/*=============================================================*/
/**
	This routine will set init.
	@param			
	@return 			
*/
//void CTunerGlobalVarInit(void);
/*=============================================================*/
/**
	This routine will set TV to specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
//UINT8 CTunerSetFreq(UINT32 freq);

/*=============================================================*/
/**
	This routine will set TV to specific frequency  in Search mode
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
//UINT8 CTunerSetFreqSearch(UINT32 freq);
/*=============================================================*/
/**
	This routine will get TV to current frequency.
	@param			void
	@return 			Return the freq	frequency
*/
//UINT32 CTunerGetFreq(void);
/*=============================================================*/
/**
	This routine will get divider ratio for specific frequency.
	@param			freq					frequency
	@return 			Return the status code	_TURE,_FALSE
*/
//UINT16 CTunerGeDiverRatio(UINT32 freq);
/*=============================================================*/
/**
	This routine will check tuner receiving frequency band(VHF Low¡BVHF High¡BUHF).
	@param 			freq	       					tuner receiving frequency(divider)
	@return 			Return tuner receiving frequency band(01¡B02 or 04)
*/
//UINT8 CTunerCheckBand(UINT32 freq);

/*=============================================================*/
//UINT32 CTunerNToFrequencyNum(UINT16 N);
//UINT32 CTunerGetRatioInStepSize(void);
//UINT32 CTunerGetPictureInterFreq(void);
UINT32 CTunerGetChanelMaxFreq(void);
UINT32 CTunerGetChanelMinFreq(void);
//UINT32 CTunerGetVHF_LowFreq(void);
//UINT32 CTunerGetVHF_HighFreq(void);

#ifdef __cplusplus
}
#endif


#endif
/**
 *
 * @}
 */
